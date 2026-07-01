// ==== 800a2ef8  FUN_800a2ef8 ====

void FUN_800a2ef8(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (('\x01' < *(char *)(param_1 + 0x18)) ||
     (((*(char *)(iVar1 + 0x18) < '\x02' && (*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94))
       ) && (*(char *)(*(int *)(param_1 + 0x15c) + 0x18) < '\x02')))) {
    if ((*(char *)(param_1 + 0x11) != '\x05') || (*(char *)(iVar1 + 0xb0) == '\0'))
    goto LAB_800a2f74;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
LAB_800a2f74:
  (*(code *)(&PTR_FUN_802f6f30)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800a2fa4  FUN_800a2fa4 ====

void FUN_800a2fa4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  uVar4 = zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  uVar1 = DAT_802b0cb4;
  *(undefined1 *)(param_9 + 0x98) = 5;
  uVar2 = DAT_802b0cb8;
  *(undefined4 *)(param_9 + 0x9c) = uVar1;
  uVar1 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar2;
  fVar3 = FLOAT_80438020;
  *(undefined4 *)(param_9 + 0xa4) = uVar1;
  *(undefined4 *)(param_9 + 0x174) = 0;
  *(float *)(param_9 + 0x178) = fVar3;
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x25,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
                in_r9,in_r10);
    fVar3 = FLOAT_80438028;
    *(float *)(param_9 + 0x168) = FLOAT_80438024;
    *(float *)(param_9 + 0x164) = fVar3;
    zz_0117ed4_(param_9,param_9 + 0x144,0);
    zz_0117ed4_(param_9,param_9 + 0x150,0);
    break;
  case 1:
  case 5:
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x25,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
                in_r9,in_r10);
    break;
  case 2:
  case 7:
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x25,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
                in_r9,in_r10);
    zz_00f036c_(param_9,0xd2);
    break;
  case 3:
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x25,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
                in_r9,in_r10);
    zz_0117ed4_(param_9,param_9 + 0x20,0);
    break;
  case 6:
    *(float *)(param_9 + 0x178) = FLOAT_8043802c;
  case 4:
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x21,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
                in_r9,in_r10);
  }
  zz_00a3160_(param_9);
  return;
}



// ==== 800a3160  zz_00a3160_ ====

void zz_00a3160_(int param_1)

{
  switch(*(undefined1 *)(param_1 + 0x11)) {
  case 0:
    zz_00a3394_(param_1);
    break;
  case 1:
  case 5:
    zz_00a35a4_(param_1);
    break;
  case 3:
    if (*(char *)(*(int *)(param_1 + 0x15c) + (int)*(char *)(param_1 + 0x12) + 0x225) == '\0') {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    zz_00a35a4_(param_1);
    break;
  case 4:
  case 6:
    zz_00a36fc_(param_1);
    break;
  case 7:
    if ((int)*(short *)(param_1 + 0x17c) !=
        (int)*(char *)(*(int *)(param_1 + 0x90) + 0x1afd) +
        *(char *)(*(int *)(param_1 + 0x90) + 0x1afc) * 0x1000) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
  case 2:
    zz_00a3624_(param_1);
  }
  zz_00a32c8_(param_1);
  return;
}



// ==== 800a3254  FUN_800a3254 ====

void FUN_800a3254(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800a3268  FUN_800a3268 ====

void FUN_800a3268(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800a3288  FUN_800a3288 ====

void FUN_800a3288(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800a32c8  zz_00a32c8_ ====

void zz_00a32c8_(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),&local_18);
  dVar5 = gnt4_PSVECMag_bl(&local_18);
  fVar3 = FLOAT_80438020;
  if ((double)FLOAT_80438030 < dVar5) {
    dVar4 = (double)FLOAT_80438038;
    *(float *)(param_1 + 0x38) = local_18;
    *(undefined4 *)(param_1 + 0x3c) = local_14;
    *(undefined4 *)(param_1 + 0x40) = local_10;
    *(float *)(param_1 + 0x60) = (float)(dVar5 / dVar4);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  else {
    *(float *)(param_1 + 0x60) = FLOAT_80438034;
    uVar1 = DAT_802b0cb4;
    *(float *)(param_1 + 0x40) = fVar3;
    uVar2 = DAT_802b0cb8;
    *(undefined4 *)(param_1 + 0x9c) = uVar1;
    uVar1 = DAT_802b0cbc;
    *(undefined4 *)(param_1 + 0xa0) = uVar2;
    *(undefined4 *)(param_1 + 0xa4) = uVar1;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800a3394  zz_00a3394_ ====

void zz_00a3394_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float afStack_34 [3];
  float afStack_28 [4];
  undefined4 local_18;
  uint uStack_14;
  
  fVar1 = FLOAT_8043803c;
  iVar3 = *(int *)(param_1 + 0x15c);
  local_18 = 0x43300000;
  uStack_14 = *(char *)(iVar3 + 0x749) * 3 ^ 0x80000000;
  *(float *)(param_1 + 0x168) =
       *(float *)(param_1 + 0x168) -
       (FLOAT_80438020 + (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80438050));
  if ((*(float *)(param_1 + 0x168) <= fVar1) || (*(char *)(iVar3 + 0x18) != '\x01')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
          (((int)*(char *)(iVar3 + 0x3e5) & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
    iVar2 = zz_0084434_(iVar3,0);
    if (iVar2 == 0) {
      *(undefined1 *)(iVar3 + 0x719) = 1;
      zz_00f0104_(iVar3,0x1b,7);
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar3 + 0x910);
      *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar3 + 0x920);
      *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(iVar3 + 0x930);
      dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x150));
      if ((double)FLOAT_8043803c < dVar4) {
        dVar5 = 1.0 / SQRT(dVar4);
        dVar5 = DOUBLE_80438040 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438048);
        dVar5 = DOUBLE_80438040 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438048);
        dVar4 = (double)(float)(dVar4 * DOUBLE_80438040 * dVar5 *
                                        -(dVar4 * dVar5 * dVar5 - DOUBLE_80438048));
      }
      *(float *)(param_1 + 0x160) = (float)dVar4;
      if (*(float *)(param_1 + 0x164) < *(float *)(param_1 + 0x160)) {
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x150),afStack_28);
        dVar4 = gnt4_PSVECSquareMag_bl(afStack_28);
        if ((double)FLOAT_8043803c < dVar4) {
          gnt4_PSVECNormalize_bl(afStack_28,afStack_34);
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x164),afStack_34,afStack_34);
          gnt4_PSVECSubtract_bl(afStack_28,afStack_34,afStack_28);
          zz_0084498_(iVar3,afStack_28);
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800a35a4  zz_00a35a4_ ====

void zz_00a35a4_(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x16c);
  puVar2 = *(undefined4 **)(param_1 + 0x170);
  *(undefined4 *)(param_1 + 0x144) = *puVar1;
  *(undefined4 *)(param_1 + 0x148) = puVar1[1];
  *(undefined4 *)(param_1 + 0x14c) = puVar1[2];
  *(undefined4 *)(param_1 + 0x150) = *puVar2;
  *(undefined4 *)(param_1 + 0x154) = puVar2[1];
  *(undefined4 *)(param_1 + 0x158) = puVar2[2];
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  return;
}



// ==== 800a3624  zz_00a3624_ ====

void zz_00a3624_(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = *(undefined4 **)(param_1 + 0x16c);
  puVar2 = *(undefined4 **)(param_1 + 0x170);
  *(undefined4 *)(param_1 + 0x144) = *puVar1;
  *(undefined4 *)(param_1 + 0x148) = puVar1[1];
  *(undefined4 *)(param_1 + 0x14c) = puVar1[2];
  *(undefined4 *)(param_1 + 0x150) = *puVar2;
  *(undefined4 *)(param_1 + 0x154) = puVar2[1];
  *(undefined4 *)(param_1 + 0x158) = puVar2[2];
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  if ((*(ushort *)(param_1 + 0x1c) & 1) == 0) {
    zz_00decc8_(param_1,(float *)(param_1 + 0x144),param_1 + 0x150,
                (char)*(undefined4 *)(param_1 + 0x174));
    *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + 1;
  }
  return;
}



// ==== 800a36fc  zz_00a36fc_ ====

void zz_00a36fc_(int param_1)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = *(undefined4 **)(param_1 + 0x16c);
  puVar3 = *(undefined4 **)(param_1 + 0x170);
  *(undefined4 *)(param_1 + 0x144) = *puVar2;
  *(undefined4 *)(param_1 + 0x148) = puVar2[1];
  *(undefined4 *)(param_1 + 0x14c) = puVar2[2];
  *(undefined4 *)(param_1 + 0x150) = *puVar3;
  *(undefined4 *)(param_1 + 0x154) = puVar3[1];
  *(undefined4 *)(param_1 + 0x158) = puVar3[2];
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  fVar1 = *(float *)(*(int *)(param_1 + 0x90) + 0xb4) * *(float *)(param_1 + 0x178);
  *(float *)(param_1 + 0xb4) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
  *(float *)(param_1 + 0xc0) = fVar1;
  if (*(char *)(param_1 + 0x12) == '\x01') {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    if ((*(ushort *)(param_1 + 0x1c) & 3) == 0) {
      zz_00dee00_(param_1,(float *)(param_1 + 0x144),(float *)(param_1 + 0x150),
                  (char)*(undefined4 *)(param_1 + 0x174));
      *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + 1;
    }
  }
  else if ((*(char *)(*(int *)(param_1 + 0x15c) + 0x13) != '\0') &&
          (*(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1,
          (*(ushort *)(param_1 + 0x1c) & 3) == 0)) {
    zz_00dee00_(param_1,(float *)(param_1 + 0x150),param_1 + 0x144,
                (char)*(undefined4 *)(param_1 + 0x174));
    *(int *)(param_1 + 0x174) = *(int *)(param_1 + 0x174) + 1;
  }
  return;
}



// ==== 800a3824  zz_00a3824_ ====

void zz_00a3824_(int param_1)

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
    zz_00e3758_(param_1,-0x7fd08310,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    zz_00e3758_(param_1,-0x7fd082b0,3,puVar3 + 9,(float *)(puVar3 + 0x21));
    zz_00e3758_(param_1,-0x7fd08220,3,puVar3 + 0x12,(float *)(puVar3 + 0x2a));
  }
  return;
}



// ==== 800a38dc  zz_00a38dc_ ====

void zz_00a38dc_(int param_1)

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
      zz_00e38a4_(param_1,(float *)&DAT_802f7cf0,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b));
      zz_00e38a4_(param_1,(float *)&DAT_802f7d50,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21));
      zz_00e38a4_(param_1,(float *)&DAT_802f7de0,3,(float *)(puVar2 + 0x12),(float *)(puVar2 + 0x2a)
                 );
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd08310,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fd082b0,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fd08220,3,(float *)(puVar2 + 0x12),(float *)(puVar2 + 0x42));
    }
  }
  return;
}



// ==== 800a39ec  zz_00a39ec_ ====

void zz_00a39ec_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 800a3a24  zz_00a3a24_ ====

void zz_00a3a24_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd08310,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd082b0,3,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd08220,3,pfVar2 + 0x12,afStack_18);
    zz_00e5184_(param_1,-0x7fd08310,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fd082b0,3,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fd08220,3,pfVar2 + 0x12,pfVar2 + 0x42);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 800a3c30  FUN_800a3c30 ====

void FUN_800a3c30(int param_1)

{
  bool bVar2;
  int iVar1;
  short sVar3;
  
  zz_00a3824_(param_1);
  *(undefined1 *)(param_1 + 0x156) = 0;
  *(int *)(param_1 + 0x158) = (int)*(short *)(param_1 + 0x79e);
  for (sVar3 = 0; (int)sVar3 < *(int *)(param_1 + 0x158); sVar3 = sVar3 + 1) {
    bVar2 = zz_00a0c88_(param_1,(char)sVar3);
    if (bVar2) {
      iVar1 = zz_01ebe10_(param_1,(char)sVar3);
      if (iVar1 == 1) {
        *(char *)(param_1 + 0x156) = *(char *)(param_1 + 0x156) + '\x01';
      }
      *(undefined1 *)(param_1 + sVar3 + 0x146) = 0;
    }
  }
  return;
}



// ==== 800a3ce4  FUN_800a3ce4 ====

void FUN_800a3ce4(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x6e9);
  if (cVar1 != '\x04') {
    if ((cVar1 < '\x04') && (cVar1 == '\0')) {
      *(undefined1 *)(param_1 + 0xaf) = 0xff;
    }
    else {
      *(undefined1 *)(param_1 + 0xaf) = 1;
      if ((*(byte *)(param_1 + 0x6e9) & 1) != 0) {
        zz_001ab6c_(param_1,0x55);
      }
      if ((*(byte *)(param_1 + 0x6e9) & 2) != 0) {
        zz_001ab6c_(param_1,0x56);
      }
      *(undefined1 *)(param_1 + 0x6e9) = 4;
    }
  }
  return;
}



// ==== 800a3d78  FUN_800a3d78 ====

void FUN_800a3d78(int param_1)

{
  zz_00a38dc_(param_1);
  return;
}



// ==== 800a3ddc  FUN_800a3ddc ====

void FUN_800a3ddc(int param_1)

{
  zz_00a39ec_(param_1);
  return;
}



// ==== 800a3dfc  FUN_800a3dfc ====

void FUN_800a3dfc(int param_1)

{
  zz_00a3a24_(param_1);
  return;
}



// ==== 800a3e1c  FUN_800a3e1c ====

void FUN_800a3e1c(int param_1)

{
  (*(code *)(&PTR_FUN_802f7eb0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800a3e58  FUN_800a3e58 ====

void FUN_800a3e58(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438060) * FLOAT_80438058);
  (*(code *)(&PTR_FUN_802f7ebc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a3ecc  FUN_800a3ecc ====

void FUN_800a3ecc(int param_1)

{
  (*(code *)(&PTR_FUN_80433a38)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a3f04  FUN_800a3f04 ====

void FUN_800a3f04(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80438068;
  dVar2 = (double)FLOAT_8043806c;
  *(float *)(param_1 + 0x50) = FLOAT_80438068;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_00a40ac_(param_1);
  return;
}



// ==== 800a3f74  FUN_800a3f74 ====

void FUN_800a3f74(int param_1)

{
  char cVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006660c_(param_1);
  zz_00a6034_(param_1,0x81);
  zz_0067458_((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x541);
  if (cVar1 == '\x01') {
    if (*(char *)(param_1 + 0x1cef) == -1) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if (((-1 < cVar1) && (*(char *)(param_1 + 0x1cef) == '\x03')) &&
       (*(char *)(param_1 + 0x1cf0) == '\x01')) {
      iVar2 = zz_006dbe0_(param_1,0,1,1);
      if (iVar2 != 0) {
        zz_0082824_(param_1,0x7d);
      }
      *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
    }
  }
  else if ((cVar1 < '\x03') && (*(char *)(param_1 + 0x1cee) != '\0')) {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800a40ac  zz_00a40ac_ ====

void zz_00a40ac_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  zz_006660c_(param_1);
  zz_00a6034_(param_1,0x81);
  return;
}



// ==== 800a4100  FUN_800a4100 ====

void FUN_800a4100(int param_1)

{
  (*(code *)(&PTR_FUN_80433a40)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a4138  FUN_800a4138 ====

void FUN_800a4138(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80438068;
  dVar2 = (double)FLOAT_8043806c;
  *(float *)(param_1 + 0x50) = FLOAT_80438068;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_00a40ac_(param_1);
  return;
}



// ==== 800a4190  FUN_800a4190 ====

void FUN_800a4190(int param_1)

{
  (*(code *)(&PTR_FUN_80433a48)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a41c8  FUN_800a41c8 ====

void FUN_800a41c8(int param_1)

{
  zz_004beb8_((double)FLOAT_8043806c,param_1,0xf,2,2,0xffffffff,0xffffffff);
  zz_00a40ac_(param_1);
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800a422c  FUN_800a422c ====

void FUN_800a422c(int param_1)

{
  char cVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006660c_(param_1);
  zz_00a6034_(param_1,0x81);
  FUN_80067310((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x541);
    if (cVar1 == '\x01') {
      if (*(char *)(param_1 + 0x1cef) == -1) {
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
        *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
      }
    }
    else if (cVar1 < '\x01') {
      if (((-1 < cVar1) && (*(char *)(param_1 + 0x1cef) == '\x03')) &&
         (*(char *)(param_1 + 0x1cf0) == '\x01')) {
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
        iVar2 = zz_006dbe0_(param_1,0,1,1);
        if (iVar2 != 0) {
          zz_0082824_(param_1,0x7d);
        }
        *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
      }
    }
    else if ((cVar1 < '\x03') && (*(char *)(param_1 + 0x1cee) != '\0')) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800a43a4  FUN_800a43a4 ====

void FUN_800a43a4(int param_1)

{
  (*(code *)(&PTR_FUN_80433a50)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a43dc  FUN_800a43dc ====

void FUN_800a43dc(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80438068;
  dVar2 = (double)FLOAT_8043806c;
  *(float *)(param_1 + 0x50) = FLOAT_80438068;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_00a40ac_(param_1);
  fVar1 = FLOAT_80438068;
  *(float *)(param_1 + 0x4c) = FLOAT_8043806c;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 800a4444  FUN_800a4444 ====

void FUN_800a4444(int param_1)

{
  int iVar1;
  
  zz_006660c_(param_1);
  zz_00a6034_(param_1,0x81);
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_80438074) {
    *(float *)(param_1 + 0x44) = FLOAT_80438074;
  }
  zz_0067458_((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00679d0_(param_1);
  if (iVar1 != 0) {
    zz_00b22f4_(param_1);
  }
  if (((*(char *)(param_1 + 0x541) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x03')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_0082824_(param_1,0x7d);
    }
    *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
  }
  if ((*(char *)(param_1 + 0x1cee) != '\0') || (*(char *)(param_1 + 0x1cef) == -1)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (*(char *)(param_1 + 0x5e4) == ',') {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800a4570  FUN_800a4570 ====

void FUN_800a4570(int param_1)

{
  if (*(char *)(param_1 + 0x581) != '\x05') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438060) * FLOAT_80438058);
  }
  (*(code *)(&PTR_FUN_802f7ed0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a45f0  FUN_800a45f0 ====

void FUN_800a45f0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7ee8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a4640  FUN_800a4640 ====

void FUN_800a4640(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80438068;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar2;
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x544) = 0;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x544);
  dVar4 = (double)FLOAT_8043806c;
  *(char *)(param_1 + 0x544) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800a4728  FUN_800a4728 ====

void FUN_800a4728(int param_1)

{
  float fVar1;
  float fVar2;
  short sVar4;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  sVar4 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar4;
  if ((sVar4 < 1) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80438078;
    fVar1 = FLOAT_80438068;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800a47bc  FUN_800a47bc ====

void FUN_800a47bc(int param_1)

{
  char cVar1;
  short sVar3;
  uint uVar2;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_00b22f4_(param_1);
  zz_004cd24_(param_1,0xf);
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if ((sVar3 < 1) || (uVar2 = FUN_80066838((double)FLOAT_8043807c,param_1), uVar2 != 0)) {
    dVar4 = (double)FLOAT_8043806c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    cVar1 = *(char *)(param_1 + 0x544);
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    *(char *)(param_1 + 0x746) = *(char *)(param_1 + 0x746) + '\x01';
    *(undefined1 *)(param_1 + 0x545) = 0;
  }
  return;
}



// ==== 800a4888  FUN_800a4888 ====

void FUN_800a4888(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  uVar2 = 1;
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    zz_00a4a34_(param_1,1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (*(char *)(param_1 + 0x1cef) == -1) {
      uVar2 = 3;
      if (*(char *)(param_1 + 0x745) < '\x01') {
        if (*(char *)(param_1 + 0x545) == '\0') {
          if (*(char *)(param_1 + 0x1cee) != '\0') {
            zz_004beb8_((double)FLOAT_8043806c,param_1,0xf,3,7,0xffffffff,0xffffffff);
            *(undefined1 *)(param_1 + 0x545) = 1;
          }
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x745) = 0;
        zz_00b2190_(param_1,0);
        if (*(char *)(param_1 + 0x746) < '\b') {
          if (*(char *)(param_1 + 0x544) == '\x06') {
            *(undefined1 *)(param_1 + 0x544) = 2;
          }
        }
        else {
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
          *(undefined1 *)(param_1 + 0x543) = 0;
          *(undefined1 *)(param_1 + 0x544) = 6;
        }
        dVar3 = (double)FLOAT_8043806c;
        *(undefined1 *)(param_1 + 0x545) = 0;
        cVar1 = *(char *)(param_1 + 0x544);
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
        *(char *)(param_1 + 0x746) = *(char *)(param_1 + 0x746) + '\x01';
      }
    }
    zz_00a4a34_(param_1,uVar2);
  }
  return;
}



// ==== 800a4a10  FUN_800a4a10 ====

void FUN_800a4a10(int param_1)

{
  zz_00a4a34_(param_1,1);
  return;
}



// ==== 800a4a34  zz_00a4a34_ ====

void zz_00a4a34_(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  
  if ((param_2 & 1) != 0) {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar2 = FLOAT_80438078;
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    fVar1 = FLOAT_80438068;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
  }
  if (FLOAT_8043807c <= *(float *)(param_1 + 0x764)) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438084;
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438080;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438080;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (((param_2 & 2) == 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800a4b4c  FUN_800a4b4c ====

void FUN_800a4b4c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7efc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a4b9c  FUN_800a4b9c ====

void FUN_800a4b9c(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043806c,param_1,0xf,3,10,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80438068;
  return;
}



// ==== 800a4c7c  FUN_800a4c7c ====

void FUN_800a4c7c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  sVar5 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar5;
  if ((sVar5 < 1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x1e;
    fVar3 = FLOAT_80438088;
    fVar2 = FLOAT_80438068;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438078;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800a4d70  FUN_800a4d70 ====

void FUN_800a4d70(int param_1)

{
  short sVar2;
  uint uVar1;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  sVar2 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar2;
  if ((sVar2 < 1) || (uVar1 = FUN_80066838((double)FLOAT_8043808c,param_1), uVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800a4e00  FUN_800a4e00 ====

void FUN_800a4e00(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1cef) == -1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
  fVar1 = FLOAT_80438058;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438058;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    zz_006a474_(param_1);
  }
  if (FLOAT_80438090 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a4ec8  FUN_800a4ec8 ====

void FUN_800a4ec8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7f0c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a4f18  FUN_800a4f18 ====

void FUN_800a4f18(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043806c;
  *(float *)(param_1 + 0x558) = FLOAT_80438094;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,8,0xffffffff,0xffffffff);
  return;
}



// ==== 800a4fc8  FUN_800a4fc8 ====

void FUN_800a4fc8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_80438068;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_80438070;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = FUN_800669d0(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80438098;
    fVar1 = FLOAT_8043808c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    if (fVar1 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800a5058  FUN_800a5058 ====

void FUN_800a5058(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_1c);
  gnt4_PSVECMag_bl(&local_1c);
  fVar1 = FLOAT_80438068;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) = FLOAT_804380a4;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar2 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_1c = *(float *)(iVar2 + 0x8e0);
    local_18 = *(float *)(iVar2 + 0x8f0);
    local_14 = *(undefined4 *)(iVar2 + 0x900);
    local_28 = *(float *)(param_1 + 0x518);
    local_20 = *(undefined4 *)(param_1 + 0x520);
    local_24 = FLOAT_80438078 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
    fVar1 = FLOAT_80438068;
    *(float *)(param_1 + 0x48) = local_18 * FLOAT_8043809c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_18 = fVar1;
    dVar3 = gnt4_PSVECMag_bl(&local_1c);
    fVar1 = FLOAT_804380a0;
    *(float *)(param_1 + 0x44) = (float)(dVar3 * (double)FLOAT_8043809c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80438068;
  if ((*(char *)(param_1 + 0x1d9) == '\0') &&
     (*(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     fVar1 < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar3 = (double)FLOAT_8043806c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,9,0xffffffff,0xffffffff);
  return;
}



// ==== 800a5204  FUN_800a5204 ====

void FUN_800a5204(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80438068;
    if (*(float *)(param_1 + 0x44) < FLOAT_80438068) {
      *(float *)(param_1 + 0x44) = FLOAT_80438068;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_804380a8 + *(float *)(param_1 + 0x1dc8);
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800a5294  FUN_800a5294 ====

void FUN_800a5294(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7f1c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a52e4  FUN_800a52e4 ====

void FUN_800a52e4(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x870),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043806c;
  *(float *)(param_1 + 0x558) = FLOAT_80438094;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,0xb,0xffffffff,0xffffffff);
  return;
}



// ==== 800a53a0  FUN_800a53a0 ====

void FUN_800a53a0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_80438068;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_80438070;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = FUN_800669d0(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80438098;
    fVar1 = FLOAT_80438078;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    if (*(float *)(param_1 + 0x44) < fVar1) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    fVar1 = FLOAT_8043808c;
    *(float *)(param_1 + 0x4c) = FLOAT_80438058;
    if (fVar1 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800a544c  FUN_800a544c ====

void FUN_800a544c(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float fStack_38;
  float local_34;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    FUN_80067310((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (*(char *)(param_1 + 0x541) == '\0') {
      zz_006660c_(param_1);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      if (*(int *)(param_1 + 0xcc) != 0) {
        iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
        local_20 = *(float *)(iVar5 + 0x8e0);
        local_1c = *(undefined4 *)(iVar5 + 0x8f0);
        local_18 = *(undefined4 *)(iVar5 + 0x900);
        local_2c = *(float *)(param_1 + 0x518);
        local_28 = *(undefined4 *)(param_1 + 0x51c);
        local_24 = *(undefined4 *)(param_1 + 0x520);
        gnt4_PSVECSubtract_bl(&local_2c,&local_20,&fStack_38);
        fVar2 = FLOAT_80438068;
        *(float *)(param_1 + 0x48) = local_34 * FLOAT_8043809c;
        *(float *)(param_1 + 0x50) = fVar2;
      }
      uVar4 = FUN_80066838((double)FLOAT_80438094,param_1);
      if (uVar4 != 0) {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
    }
    iVar5 = FUN_800452a0((double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
    sVar3 = -(short)iVar5 - *(short *)(param_1 + 0x18da);
    if ((short)-(short)iVar5 < 1) {
      if (sVar3 < -0x38e) {
        sVar3 = -0x38e;
      }
    }
    else if (0x38e < sVar3) {
      sVar3 = 0x38e;
    }
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + sVar3;
  }
  zz_004cd24_(param_1,0xf);
  if (FLOAT_804380a4 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_804380a4;
    *(float *)(param_1 + 0x4c) = FLOAT_80438068;
  }
  zz_0067458_((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80438068;
  if ((iVar5 == 1) && (*(char *)(param_1 + 0x542) == '\0')) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  fVar2 = FLOAT_80438068;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004cff4_(param_1,0xf);
  }
  return;
}



// ==== 800a5648  FUN_800a5648 ====

void FUN_800a5648(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80438070,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    fVar1 = FLOAT_804380a8;
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800a56d8  FUN_800a56d8 ====

void FUN_800a56d8(int param_1)

{
  (*(code *)(&PTR_FUN_80433a58)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a5710  FUN_800a5710 ====

void FUN_800a5710(int param_1)

{
  if (*(char *)(param_1 + 0x544) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7f2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a5760  FUN_800a5760 ====

void FUN_800a5760(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80438068;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x544) = 0;
  }
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043806c,param_1,0xf,4,0,0xffffffff,0xffffffff);
  if ('\0' < *(char *)(param_1 + 0x156)) {
    uVar2 = *(uint *)(param_1 + 0x5b4);
    if ((uVar2 & 0x10000) == 0) {
      if ((uVar2 & 0x20000) == 0) {
        if ((uVar2 & 0x80000) == 0) {
          if ((uVar2 & 0x40000) == 0) {
            *(undefined2 *)(param_1 + 0x144) = 3;
          }
          else {
            *(undefined2 *)(param_1 + 0x144) = 0;
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x144) = 3;
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x144) = 2;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x144) = 1;
    }
  }
  return;
}



// ==== 800a5864  FUN_800a5864 ====

void FUN_800a5864(int param_1)

{
  int iVar1;
  short sVar2;
  
  sVar2 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar2;
  if ((sVar2 < 1) || (iVar1 = zz_006d144_(param_1,0xc0), iVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  return;
}



// ==== 800a58c4  FUN_800a58c4 ====

void FUN_800a58c4(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  short sVar4;
  
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x1cef);
  if ((cVar1 == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x03')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    if (('\0' < *(char *)(param_1 + 0x156)) && (iVar3 = zz_006dbe0_(param_1,2,1,1), iVar3 == 1)) {
      for (sVar4 = 0; (int)sVar4 < *(int *)(param_1 + 0x158); sVar4 = sVar4 + 1) {
        if (*(char *)(param_1 + sVar4 + 0x146) == '\0') {
          *(undefined1 *)(param_1 + sVar4 + 0x146) = 1;
          *(char *)(param_1 + 0x156) = *(char *)(param_1 + 0x156) + -1;
          break;
        }
      }
    }
  }
  else if ((cVar1 == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    bVar2 = false;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    for (sVar4 = 0; (int)sVar4 < *(int *)(param_1 + 0x158); sVar4 = sVar4 + 1) {
      iVar3 = (int)sVar4;
      if (*(char *)(param_1 + iVar3 + 0x146) == '\x01') {
        *(undefined1 *)(param_1 + iVar3 + 0x146) = 2;
        sVar4 = *(short *)(param_1 + 0x144);
        if (sVar4 == 2) {
          *(short *)(param_1 + iVar3 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + -0x4000;
        }
        else if (sVar4 < 2) {
          if (sVar4 == 0) {
            *(short *)(param_1 + iVar3 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + -0x8000;
          }
          else if (-1 < sVar4) {
            *(short *)(param_1 + iVar3 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + 0x4000;
          }
        }
        else if (sVar4 < 4) {
          *(undefined2 *)(param_1 + iVar3 * 2 + 0x14a) = *(undefined2 *)(param_1 + 0x72);
        }
        bVar2 = true;
        break;
      }
    }
    if (!bVar2) {
      zz_004cff4_(param_1,0xf);
      zz_004cff4_(param_1,0xf);
    }
  }
  else if (cVar1 == -1) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  }
  if (*(char *)(param_1 + 0x1cee) == '\x01') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800a5ad8  FUN_800a5ad8 ====

void FUN_800a5ad8(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800a5b0c  FUN_800a5b0c ====

void FUN_800a5b0c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f7f3c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a5b5c  FUN_800a5b5c ====

void FUN_800a5b5c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_80438084;
  fVar1 = FLOAT_80438068;
  dVar4 = (double)FLOAT_80438070;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438084;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043806c,param_1,0xf,4,1,0xffffffff,0xffffffff);
  if ('\0' < *(char *)(param_1 + 0x156)) {
    uVar3 = *(uint *)(param_1 + 0x5b4);
    if ((uVar3 & 0x10000) == 0) {
      if ((uVar3 & 0x20000) == 0) {
        if ((uVar3 & 0x80000) == 0) {
          if ((uVar3 & 0x40000) == 0) {
            *(undefined2 *)(param_1 + 0x144) = 3;
          }
          else {
            *(undefined2 *)(param_1 + 0x144) = 0;
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x144) = 3;
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x144) = 2;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x144) = 1;
    }
  }
  return;
}



// ==== 800a5ca8  FUN_800a5ca8 ====

void FUN_800a5ca8(int param_1)

{
  float fVar1;
  short sVar3;
  int iVar2;
  double dVar4;
  
  fVar1 = FLOAT_80438058;
  dVar4 = (double)FLOAT_80438070;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438058;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if ((sVar3 < 0) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800a5d40  FUN_800a5d40 ====

void FUN_800a5d40(int param_1)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x1cef);
  if ((cVar1 == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x03')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    if (('\0' < *(char *)(param_1 + 0x156)) && (iVar5 = zz_006dbe0_(param_1,2,1,1), iVar5 == 1)) {
      iVar5 = *(int *)(param_1 + 0x158);
      iVar6 = 0;
      if (0 < iVar5) {
        do {
          if (*(char *)(param_1 + iVar6 + 0x146) == '\0') {
            *(undefined1 *)(param_1 + iVar6 + 0x146) = 1;
            *(char *)(param_1 + 0x156) = *(char *)(param_1 + 0x156) + -1;
            break;
          }
          iVar6 = iVar6 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
  }
  else if ((cVar1 == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    iVar6 = 0;
    bVar3 = false;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar5 = *(int *)(param_1 + 0x158);
    if (0 < iVar5) {
      do {
        if (*(char *)(param_1 + iVar6 + 0x146) == '\x01') {
          *(undefined1 *)(param_1 + iVar6 + 0x146) = 2;
          sVar2 = *(short *)(param_1 + 0x144);
          if (sVar2 == 2) {
            *(short *)(param_1 + iVar6 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + -0x4000;
          }
          else if (sVar2 < 2) {
            if (sVar2 == 0) {
              *(short *)(param_1 + iVar6 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + -0x8000;
            }
            else if (-1 < sVar2) {
              *(short *)(param_1 + iVar6 * 2 + 0x14a) = *(short *)(param_1 + 0x72) + 0x4000;
            }
          }
          else if (sVar2 < 4) {
            *(undefined2 *)(param_1 + iVar6 * 2 + 0x14a) = *(undefined2 *)(param_1 + 0x72);
          }
          bVar3 = true;
          break;
        }
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    fVar4 = FLOAT_80438068;
    if (!bVar3) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(float *)(param_1 + 0x4c) = fVar4;
      *(float *)(param_1 + 0x44) = fVar4;
      *(undefined2 *)(param_1 + 0x18da) = 0;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_80438094 + *(float *)(param_1 + 0x1dc8);
      return;
    }
  }
  else if (cVar1 == -1) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  }
  zz_006d144_(param_1,0xc1);
  if (*(char *)(param_1 + 0x542) == '\x01') {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar4 = FLOAT_80438058;
  dVar7 = (double)FLOAT_80438070;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438058;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar4;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar4;
  FUN_80067310(dVar7,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800a5fe4  FUN_800a5fe4 ====

void FUN_800a5fe4(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80438068;
  *(float *)(param_1 + 0x4c) = FLOAT_80438068;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x18da) = 0;
  zz_006a5a4_(param_1);
  *(float *)(param_1 + 0x694) = FLOAT_80438094 + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 800a6034  zz_00a6034_ ====

undefined4 zz_00a6034_(int param_1,uint param_2)

{
  short sVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  
  sVar1 = *(short *)(param_1 + 0x5aa);
  iVar4 = (int)sVar1;
  if (sVar1 < 0) {
    iVar4 = -iVar4;
  }
  sVar3 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) +
                                                                (param_2 & 0xf) * 2 + 0xac) ^
                                                0x80000000) - DOUBLE_80438060) *
                      *(float *)(param_1 + 0x1dc8));
  if (sVar3 < iVar4) {
    sVar1 = *(short *)(param_1 + 0x72) - sVar3;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + sVar3;
    uVar2 = 0;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x72) + sVar1;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 800a6108  FUN_800a6108 ====

void FUN_800a6108(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x23;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800a6204;
    *(code **)(puVar1 + 0x10c) = FUN_800a6860;
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
    *(undefined1 *)(param_1 + 0x146) = 1;
  }
  return;
}



// ==== 800a6204  FUN_800a6204 ====

void FUN_800a6204(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_802f7fa8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800a62a4  FUN_800a62a4 ====

void FUN_800a62a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar6 = *(int *)(param_9 + 0x90);
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x18;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined *)(param_9 + 0x89) = (&DAT_802f7f92)[iVar5];
  uVar1 = *(undefined4 *)(&DAT_802f7f98 + iVar5);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f7f94 + iVar5);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f7f9c + iVar5);
  uVar2 = (undefined2)*(undefined4 *)(&DAT_802f7fa4 + iVar5);
  *(undefined2 *)(param_9 + 0x1c4) = uVar2;
  *(undefined2 *)(param_9 + 0x1c8) = uVar2;
  *(undefined2 *)(param_9 + 0x1c6) = uVar2;
  zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_802f7fa0)[(uint)*(byte *)(param_9 + 0x11) * 6]
              ,(float *)(param_9 + 0x58));
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,0,1);
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar3 << 8);
  *(undefined2 *)(param_9 + 0x7e) = 0x888;
  iVar4 = zz_008ac80_(param_9,(int)(char)(&DAT_802f7f93)[iVar5]);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(iVar6 + 0x146) = 0;
  }
  else {
    *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0x18) = 0;
    *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0x1c) = 0xffffffff;
    iVar7 = *(int *)(param_9 + 0xe0);
    iVar4 = zz_0006f78_(iVar6);
    zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,iVar7,
                (uint)*(ushort *)(&DAT_802f7f90 + iVar5),iVar7 + 0x18,in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 8;
  }
  return;
}



// ==== 800a63f4  FUN_800a63f4 ====

void FUN_800a63f4(int param_1)

{
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
  (*(code *)(&PTR_FUN_802f7fb8)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800a6440  FUN_800a6440 ====

void FUN_800a6440(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
  }
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined2 *)(param_1 + 0x1c) = 8;
    zz_008aff0_(param_1);
  }
  else {
    if (*(char *)(iVar3 + 0x146) == '\x02') {
      *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
      *(undefined1 *)(iVar3 + 0x146) = 1;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    uVar2 = zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),
                        (float *)(param_1 + 0x58));
    if (uVar2 != 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    fVar1 = FLOAT_804380b0;
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar3 + 0xb4);
    *(float *)(param_1 + 0xb4) =
         *(float *)(param_1 + 0xb4) *
         ((*(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x5c)) /
         fVar1);
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  }
  return;
}



// ==== 800a654c  FUN_800a654c ====

void FUN_800a654c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
  }
  fVar1 = FLOAT_804380b4;
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 8;
    zz_008aff0_(param_1);
  }
  else {
    if (*(char *)(iVar4 + 0x146) == '\x02') {
      *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
      *(undefined1 *)(iVar4 + 0x146) = 1;
      *(float *)(param_1 + 0xb8) = fVar1;
    }
    else {
      *(float *)(param_1 + 0xb8) =
           ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c6) ^ 0x80000000) -
                   DOUBLE_804380c8) /
           (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c4) ^ 0x80000000) -
                  DOUBLE_804380c8)) * FLOAT_804380b8 + FLOAT_804380b8;
    }
    fVar3 = FLOAT_804380c0;
    fVar2 = FLOAT_804380bc;
    fVar1 = *(float *)(param_1 + 0x58);
    if (*(float *)(param_1 + 0xb8) <= fVar1) {
      if (*(float *)(param_1 + 0xb8) < fVar1) {
        *(float *)(param_1 + 0x58) = fVar1 * FLOAT_804380c0;
        *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * fVar3;
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * fVar3;
        if (*(float *)(param_1 + 0x58) <= *(float *)(param_1 + 0xb8)) {
          *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0xb8);
          *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb8);
          *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb8);
        }
      }
    }
    else {
      *(float *)(param_1 + 0x58) = fVar1 * FLOAT_804380bc;
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * fVar2;
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * fVar2;
      if (*(float *)(param_1 + 0xb8) <= *(float *)(param_1 + 0x58)) {
        *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0xb8);
        *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb8);
        *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb8);
      }
    }
    fVar1 = FLOAT_804380b0;
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
    *(float *)(param_1 + 0xb4) =
         *(float *)(param_1 + 0xb4) *
         ((*(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x5c)) /
         fVar1);
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  }
  return;
}



// ==== 800a6714  FUN_800a6714 ====

void FUN_800a6714(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  uVar1 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x18) + 0x20;
  if (0xff < uVar1) {
    uVar1 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x18) = (char)uVar1;
  uVar1 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x19) + 0x20;
  if (0xff < uVar1) {
    uVar1 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x19) = (char)uVar1;
  uVar1 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1a) + 0x20;
  if (0xff < uVar1) {
    uVar1 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x1a) = (char)uVar1;
  uVar1 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1b) + 0x20;
  if (0xff < uVar1) {
    uVar1 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x1b) = (char)uVar1;
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(iVar2 + 0x146) = 0;
  }
  return;
}



// ==== 800a67e0  FUN_800a67e0 ====

void FUN_800a67e0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x146) == '\0') {
    zz_00b19b4_(param_1,0,0x40);
    zz_00f036c_(param_1,0xe1);
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800a6840  FUN_800a6840 ====

void FUN_800a6840(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800a6860  FUN_800a6860 ====

void FUN_800a6860(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800a68a0  zz_00a68a0_ ====

void zz_00a68a0_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 7) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800a6994;
    *(code **)(puVar1 + 0x10c) = FUN_800a6ed4;
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



// ==== 800a6994  FUN_800a6994 ====

void FUN_800a6994(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802f801c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800a69e8  FUN_800a69e8 ====

void FUN_800a69e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 extraout_r4;
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXMultVec_bl((float *)(iVar4 + 0x964),(float *)&DAT_802f7fd4,(float *)(param_9 + 0x144));
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x89) = 3;
  uVar1 = DAT_802f7fcc;
  puVar3 = &DAT_802f7fc8;
  *(undefined4 *)(param_9 + 100) = DAT_802f7fc8;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = DAT_802f7fd0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined1 *)(param_9 + 0x84) = 0;
  uVar1 = DAT_802f7fe4;
  *(undefined4 *)(param_9 + 0x38) = DAT_802f7fe0;
  *(undefined4 *)(param_9 + 0x3c) = uVar1;
  *(undefined4 *)(param_9 + 0x40) = DAT_802f7fe8;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),7,iVar4 + 0xc28,puVar3,in_r8,
                      in_r9,in_r10);
  iVar2 = iVar4 + 0xc28;
  uVar1 = 7;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),7,iVar2,puVar3,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar1,iVar2,puVar3,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804380d0,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00c74ec_(param_9,0);
  FUN_800a6b1c(param_9);
  return;
}



// ==== 800a6b1c  FUN_800a6b1c ====

/* WARNING: Removing unreachable block (ram,0x800a6e7c) */
/* WARNING: Removing unreachable block (ram,0x800a6b2c) */

void FUN_800a6b1c(int param_1)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  double dVar4;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  iVar3 = *(int *)(param_1 + 0x90);
  pfVar2 = (float *)(param_1 + 0x144);
  gnt4_PSVECSubtract_bl((float *)(iVar3 + 0x20),(float *)(iVar3 + 0x5e8),&local_68);
  uVar1 = (uint)(FLOAT_804380d4 < local_64);
  local_5c = *(float *)(iVar3 + 0x8dc);
  local_58 = *(undefined4 *)(iVar3 + 0x8ec);
  local_54 = *(undefined4 *)(iVar3 + 0x8fc);
  dVar4 = gnt4_PSQUATDotProduct_bl(&local_68,&local_5c);
  if (dVar4 < (double)FLOAT_804380d4) {
    uVar1 = uVar1 + 2;
  }
  gnt4_PSVECSubtract_bl((float *)(&DAT_802f7fe0 + uVar1 * 3),(float *)(param_1 + 0x38),&local_68);
  if (FLOAT_804380d8 < local_64) {
    local_64 = FLOAT_804380d8;
  }
  if (local_64 < FLOAT_804380dc) {
    local_64 = FLOAT_804380dc;
  }
  if (FLOAT_804380d8 < local_60) {
    local_60 = FLOAT_804380d8;
  }
  if (local_60 < FLOAT_804380dc) {
    local_60 = FLOAT_804380dc;
  }
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),&local_68,(float *)(param_1 + 0x38));
  gnt4_PSMTXMultVecSR_bl((float *)(iVar3 + 0x8d4),(float *)(param_1 + 0x38),&local_38);
  gnt4_PSVECAdd_bl(pfVar2,&local_38,pfVar2);
  gnt4_PSMTXMultVec_bl((float *)(iVar3 + 0x8d4),(float *)&DAT_802f8010,&local_68);
  local_5c = *(float *)(iVar3 + 0x8dc);
  local_58 = *(undefined4 *)(iVar3 + 0x8ec);
  local_54 = *(undefined4 *)(iVar3 + 0x8fc);
  gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
  gnt4_PSVECSubtract_bl(pfVar2,&local_68,&local_38);
  dVar4 = gnt4_PSQUATDotProduct_bl(&local_38,&local_5c);
  if ((double)FLOAT_804380d4 < dVar4) {
    gnt4_PSQUATScale_bl(-dVar4,&local_5c,&local_5c);
    gnt4_PSVECAdd_bl(&local_5c,pfVar2,pfVar2);
  }
  gnt4_PSMTXMultVec_bl((float *)(iVar3 + 0x964),(float *)&DAT_802f7fc8,&local_38);
  gnt4_PSVECSubtract_bl(&local_38,pfVar2,&local_5c);
  gnt4_PSVECMag_bl(&local_5c);
  gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
  gnt4_PSQUATScale_bl((double)FLOAT_804380e0,&local_5c,&local_5c);
  gnt4_PSVECSubtract_bl(&local_38,&local_5c,pfVar2);
  local_44 = *(float *)(iVar3 + 0x8d4);
  local_40 = *(undefined4 *)(iVar3 + 0x8e4);
  local_3c = *(undefined4 *)(iVar3 + 0x8f4);
  gnt4_PSVECCrossProduct_bl(&local_5c,&local_44,&local_50);
  gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_44);
  local_68 = *(float *)(iVar3 + 0x8d4);
  local_64 = *(float *)(iVar3 + 0x8e4);
  local_60 = *(float *)(iVar3 + 0x8f4);
  dVar4 = gnt4_PSVECMag_bl(&local_68);
  gnt4_PSVECNormalize_bl(&local_44,&local_44);
  gnt4_PSQUATScale_bl(dVar4,&local_44,&local_44);
  local_68 = *(float *)(iVar3 + 0x8d8);
  local_64 = *(float *)(iVar3 + 0x8e8);
  local_60 = *(float *)(iVar3 + 0x8f8);
  dVar4 = gnt4_PSVECMag_bl(&local_68);
  gnt4_PSVECNormalize_bl(&local_50,&local_50);
  gnt4_PSQUATScale_bl(dVar4,&local_50,&local_50);
  local_68 = *(float *)(iVar3 + 0x8dc);
  local_64 = *(float *)(iVar3 + 0x8ec);
  local_60 = *(float *)(iVar3 + 0x8fc);
  dVar4 = gnt4_PSVECMag_bl(&local_68);
  gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
  gnt4_PSQUATScale_bl(dVar4,&local_5c,&local_5c);
  *(float *)(param_1 + 0x114) = local_44;
  *(undefined4 *)(param_1 + 0x124) = local_40;
  *(undefined4 *)(param_1 + 0x134) = local_3c;
  *(float *)(param_1 + 0x118) = local_50;
  *(undefined4 *)(param_1 + 0x128) = local_4c;
  *(undefined4 *)(param_1 + 0x138) = local_48;
  *(float *)(param_1 + 0x11c) = local_5c;
  *(undefined4 *)(param_1 + 300) = local_58;
  *(undefined4 *)(param_1 + 0x13c) = local_54;
  *(float *)(param_1 + 0x120) = local_38;
  *(undefined4 *)(param_1 + 0x130) = local_34;
  *(undefined4 *)(param_1 + 0x140) = local_30;
  *(undefined1 *)(param_1 + 0xa8) = *(undefined1 *)(iVar3 + 0xa8);
  return;
}



// ==== 800a6eb4  FUN_800a6eb4 ====

void FUN_800a6eb4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800a6ed4  FUN_800a6ed4 ====

void FUN_800a6ed4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800a7048  FUN_800a7048 ====

void FUN_800a7048(int param_1)

{
  zz_00a68a0_(param_1);
  zz_00ae630_(param_1,0);
  zz_00ae630_(param_1,1);
  zz_00c74ec_(param_1,1);
  return;
}



// ==== 800a70f0  FUN_800a70f0 ====

void FUN_800a70f0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802f8548)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800a713c  FUN_800a713c ====

void FUN_800a713c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x33);
  zz_001ab6c_(param_1,0x34);
  return;
}



// ==== 800a71a4  FUN_800a71a4 ====

void FUN_800a71a4(int param_1)

{
  (*(code *)(&PTR_FUN_802f8560)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800a71e0  FUN_800a71e0 ====

void FUN_800a71e0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802f8570)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a7228  FUN_800a7228 ====

void FUN_800a7228(int param_1)

{
  (*(code *)(&PTR_FUN_802f8584)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a7264  FUN_800a7264 ====

void FUN_800a7264(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804380e8;
  dVar2 = (double)FLOAT_804380ec;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  fVar1 = FLOAT_804380f0;
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
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804380f0;
  return;
}



// ==== 800a7340  FUN_800a7340 ====

void FUN_800a7340(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804380f0;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_800a73b4;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00a75d0_(param_1);
  }
LAB_800a73b4:
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804380f8 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a740c  FUN_800a740c ====

void FUN_800a740c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_804380f0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
      iVar2 = zz_006dbe0_(param_1,0,1,0);
      if (iVar2 != 0) {
        zz_006bf80_(param_1);
        dVar3 = (double)FLOAT_804380ec;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar3,param_1,0xf,2,1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_800a7528;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    zz_006d0dc_(param_1,0xc1,0);
  }
  fVar1 = FLOAT_804380f0;
  if ((FLOAT_804380f0 < *(float *)(param_1 + 0x55c)) &&
     (*(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x55c) <= fVar1)) {
    zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,2,2,0xffffffff,0xffffffff);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar3 <= (double)FLOAT_804380f8) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_800a7528:
  if (FLOAT_804380f0 < *(float *)(param_1 + 0x55c)) {
    zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,2,2,0xffffffff,0xffffffff);
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800a75d0  zz_00a75d0_ ====

void zz_00a75d0_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80438100;
  *(float *)(param_1 + 0x558) = FLOAT_804380fc;
  *(float *)(param_1 + 0x55c) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    zz_00c3be0_(param_1,1);
  }
  return;
}



// ==== 800a762c  FUN_800a762c ====

void FUN_800a762c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  short *psVar5;
  undefined4 uVar6;
  double dVar7;
  double dVar8;
  short local_18 [10];
  
  fVar1 = FLOAT_80438104;
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    *(float *)(param_9 + 0x558) = fVar1;
  }
  if (*(char *)(param_9 + 0x5db) != '\x0f') {
    uVar2 = zz_006e004_(param_9);
    if (-1 < (int)uVar2) {
      if (((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) && (*(char *)(param_9 + 0x5db) == '\a')) {
        zz_006a3d0_(param_9,'\0',4,2);
        return;
      }
      if ((*(char *)(param_9 + 0x1afc) == *(char *)(param_9 + 0x1b3c)) &&
         (*(char *)(param_9 + 0x1afd) == *(char *)(param_9 + 0x1b3d))) {
        zz_004cd24_(param_9,1);
      }
      else {
        zz_0048d54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,
                    param_11,param_12,param_13,param_14,param_15,param_16);
      }
      uVar6 = 0x4000;
      local_18[2] = 0xf000;
      dVar7 = (double)FLOAT_80438108;
      psVar5 = local_18;
      local_18[3] = 0x1000;
      uVar4 = 3;
      local_18[0] = 0x4000;
      local_18[1] = 0xc000;
      dVar8 = (double)*(float *)(param_9 + 0x558);
      *(float *)(param_9 + 0x558) = (float)(dVar8 - (double)*(float *)(param_9 + 0x1dc8));
      iVar3 = FUN_8006cc90(dVar7,param_9,0xc,3,psVar5);
      if ((iVar3 == 0) && (FLOAT_804380f0 < *(float *)(param_9 + 0x558))) {
        return;
      }
      dVar7 = (double)zz_00a75d0_(param_9);
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(dVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,uVar4,
                  psVar5,uVar6,param_14,param_15,param_16);
      *(float *)(param_9 + 0x694) = FLOAT_804380fc + *(float *)(param_9 + 0x1dc8);
      return;
    }
    if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
      zz_006a3d0_(param_9,'\0',4,2);
      return;
    }
  }
  zz_006a3d0_(param_9,'\0',0,2);
  return;
}



// ==== 800a77dc  FUN_800a77dc ====

void FUN_800a77dc(int param_1)

{
  (*(code *)(&PTR_FUN_802f8590)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a7818  FUN_800a7818 ====

void FUN_800a7818(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804380e8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_8043810c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,2,4,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804380f0;
  return;
}



// ==== 800a78b8  FUN_800a78b8 ====

void FUN_800a78b8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_804380f0;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_800a7960;
  }
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00a75d0_(param_1);
  }
LAB_800a7960:
  zz_00b22f4_(param_1);
  return;
}



// ==== 800a797c  FUN_800a797c ====

void FUN_800a797c(int param_1)

{
  int iVar1;
  double dVar2;
  
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    zz_004cd24_(param_1,0xf);
    if (*(float *)(param_1 + 0x558) <= FLOAT_804380f0) {
      if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
          zz_006a3d0_(param_1,'\0',0,2);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_804380ec;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,0xf,2,5,0xffffffff,0xffffffff);
        return;
      }
    }
    else {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    }
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      zz_00b22f4_(param_1);
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438104 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800a7abc  FUN_800a7abc ====

void FUN_800a7abc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802f859c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a7b04  FUN_800a7b04 ====

void FUN_800a7b04(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 800a7b2c  FUN_800a7b2c ====

void FUN_800a7b2c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f85c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a7b7c  FUN_800a7b7c ====

void FUN_800a7b7c(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_804380f0;
  *(float *)(param_1 + 0x558) = FLOAT_80438110;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 10;
  *(undefined1 *)(param_1 + 0x746) = 0;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,3,4,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804380f0;
  return;
}



// ==== 800a7c58  FUN_800a7c58 ====

void FUN_800a7c58(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804380f0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800a7cd4  FUN_800a7cd4 ====

void FUN_800a7cd4(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  uint uVar4;
  
  uVar4 = zz_006de44_(param_1,0xf0f00);
  dVar3 = DOUBLE_80438120;
  if (uVar4 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar4) {
      uVar4 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar4;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar3);
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  if (*(float *)(param_1 + 0x764) < FLOAT_80438114) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80438118;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_804380e8;
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar2;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800a7e14  FUN_800a7e14 ====

void FUN_800a7e14(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  uint uVar4;
  
  uVar4 = zz_006de44_(param_1,0xf0f00);
  dVar3 = DOUBLE_80438120;
  if (uVar4 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar4) {
      uVar4 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar4;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar3);
  }
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804380f4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804380f0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar1 <= fVar2) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      if (*(char *)(param_1 + 0x746) == '\0') {
        zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,3,5,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,3,6,0xffffffff,0xffffffff);
      }
    }
  }
  if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a7f78  FUN_800a7f78 ====

void FUN_800a7f78(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438108;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  fVar2 = FLOAT_80438118;
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if (*(int *)(param_1 + 0xcc) != 0) {
      if (fVar1 < *(float *)(param_1 + 0x764)) {
        fVar1 = *(float *)(param_1 + 0x760);
      }
    }
    *(float *)(param_1 + 0x44) = (FLOAT_80438128 * fVar1) / FLOAT_804380e8;
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar2;
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    zz_00b2190_(param_1,0);
  }
  zz_006ed8c_((double)FLOAT_804380f4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a80c8  FUN_800a80c8 ====

void FUN_800a80c8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f85dc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a8118  FUN_800a8118 ====

void FUN_800a8118(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  fVar1 = FLOAT_80438100;
  *(float *)(param_1 + 0x558) = FLOAT_80438110;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0x14;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,3,7,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804380f0;
  return;
}



// ==== 800a8224  FUN_800a8224 ====

void FUN_800a8224(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804380f0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804380e8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_804380f0;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_804380e8;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a8354  FUN_800a8354 ====

void FUN_800a8354(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  uint uVar4;
  
  uVar4 = zz_006de44_(param_1,0xf0f00);
  dVar3 = DOUBLE_80438120;
  if (uVar4 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar4) {
      uVar4 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar4;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar3);
  }
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043812c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804380f0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_80438130,param_1), 0 < (int)uVar4)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a8468  FUN_800a8468 ====

void FUN_800a8468(int param_1)

{
  uint uVar1;
  double dVar2;
  
  uVar1 = zz_006de44_(param_1,0xf0f00);
  dVar2 = DOUBLE_80438120;
  if (uVar1 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar1) {
      uVar1 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar1;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - dVar2);
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_804380f4,param_1);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80438108;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x560) <= FLOAT_804380f0) {
    dVar2 = (double)FLOAT_804380ec;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800a85a8  FUN_800a85a8 ====

void FUN_800a85a8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804380f4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (FLOAT_804380f8 < *(float *)(param_1 + 0x44)) {
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



// ==== 800a8634  FUN_800a8634 ====

void FUN_800a8634(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f85f0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a8684  FUN_800a8684 ====

void FUN_800a8684(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined2 *)(param_1 + 0x54e) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,3,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800a8788  FUN_800a8788 ====

void FUN_800a8788(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80438134;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar2 = (double)FLOAT_804380ec;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_004beb8_(dVar2,param_1,0xf,3,1,0xffffffff,0xffffffff);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800a8848  FUN_800a8848 ====

void FUN_800a8848(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80438138 * dVar3);
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar4 = (double)FLOAT_8043810c;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80438138 * -dVar3);
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804380f0;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) == 0) {
    if (((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
    dVar3 = (double)FLOAT_804380ec;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  else {
    *(float *)(param_1 + 0x44) = FLOAT_804380fc;
    fVar1 = FLOAT_80438100;
    *(float *)(param_1 + 0x4c) = fVar2;
    fVar2 = FLOAT_8043813c;
    *(float *)(param_1 + 0x48) = fVar1;
    dVar3 = (double)FLOAT_804380ec;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800a899c  FUN_800a899c ====

void FUN_800a899c(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804380f0;
  if (*(char *)(param_1 + 0x71c) == '\0') {
    if (*(float *)(param_1 + 0x44) < FLOAT_804380f0) {
      *(float *)(param_1 + 0x44) = FLOAT_804380f0;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
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
      *(float *)(param_1 + 0x694) = FLOAT_8043810c + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 800a8a6c  FUN_800a8a6c ====

void FUN_800a8a6c(int param_1)

{
  (*(code *)(&PTR_FUN_802f8600)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a8aa8  FUN_800a8aa8 ====

void FUN_800a8aa8(int param_1)

{
  (*(code *)(&PTR_FUN_802f8614)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a8ae4  FUN_800a8ae4 ====

void FUN_800a8ae4(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043810c;
  fVar1 = FLOAT_804380f0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 4;
  *(undefined1 *)(param_1 + 0x542) = 0x14;
  *(undefined1 *)(param_1 + 0x543) = 0;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  if (*(short *)(param_1 + 0x784) < 1) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,4,3,0xffffffff,0xffffffff);
  return;
}



// ==== 800a8be4  FUN_800a8be4 ====

void FUN_800a8be4(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    iVar2 = zz_006dbe0_(param_1,2,1,0);
    fVar1 = FLOAT_804380f0;
    if (iVar2 == 0) {
      *(float *)(param_1 + 0x4c) = FLOAT_804380f0;
      *(float *)(param_1 + 0x44) = fVar1;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x6e9) = 3;
      *(undefined1 *)(param_1 + 0x6e8) = 3;
    }
  }
  return;
}



// ==== 800a8cd4  FUN_800a8cd4 ====

void FUN_800a8cd4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  short *psVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc1,1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043813c;
  fVar2 = FLOAT_80438134;
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_804380e8;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    iVar4 = zz_006dbe0_(param_1,2,1,1);
    if (iVar4 != 0) {
      iVar4 = 0;
      psVar5 = (short *)&DAT_80433a60;
      do {
        FUN_800b5ed8(param_1,(byte)iVar4 & 1,*psVar5);
        iVar4 = iVar4 + 1;
        psVar5 = psVar5 + 1;
      } while (iVar4 < 4);
    }
  }
  zz_00f0104_(param_1,3,2);
  return;
}



// ==== 800a8dd0  FUN_800a8dd0 ====

void FUN_800a8dd0(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438120) * FLOAT_80438140);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_804380f0;
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043810c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804380f0;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800a8ecc  FUN_800a8ecc ====

void FUN_800a8ecc(int param_1)

{
  (*(code *)(&PTR_FUN_802f8624)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800a8f08  FUN_800a8f08 ====

void FUN_800a8f08(int param_1)

{
  (*(code *)(&PTR_FUN_802f8638)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800a8f44  FUN_800a8f44 ====

void FUN_800a8f44(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438134;
  fVar1 = FLOAT_804380f0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = 5;
  *(undefined2 *)(param_1 + 0x54c) = 3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x50) = fVar1;
  zz_006660c_(param_1);
  FUN_80066a30(param_1,0xc0,-0x8000);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,4,8,0xc,1);
  FUN_800061a8(param_1,0x11);
  zz_01e307c_(param_1);
  *(undefined1 *)(param_1 + 0x6f4) = 1;
  zz_00f036c_(param_1,0x10b);
  return;
}



// ==== 800a9040  FUN_800a9040 ====

void FUN_800a9040(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  double dVar6;
  
  *(undefined1 *)(param_1 + 0x6f4) = 1;
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_804380f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (*(float *)(param_1 + 0x48) < FLOAT_804380f0) {
      *(float *)(param_1 + 0x48) = FLOAT_804380f0;
    }
    FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_006e1ac_(param_1,0xc1,1);
    fVar2 = FLOAT_804380f0;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
      fVar2 = FLOAT_80438134;
      fVar1 = FLOAT_804380f0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      fVar3 = FLOAT_80438144;
      *(float *)(param_1 + 0x558) = fVar2;
      *(float *)(param_1 + 0x560) = fVar1;
      *(float *)(param_1 + 0x38) = fVar3;
      uVar5 = zz_00055fc_();
      dVar6 = (double)FLOAT_804380ec;
      *(byte *)(param_1 + 0x6ea) = ((byte)uVar5 & 1) + 5;
      zz_004beb8_(dVar6,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
      zz_0092dcc_(param_1,0);
      zz_00f036c_(param_1,0x10c);
    }
  }
  return;
}



// ==== 800a9188  FUN_800a9188 ====

void FUN_800a9188(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  double dVar6;
  double dVar7;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  *(undefined1 *)(param_1 + 0x6f4) = 2;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
    sVar5 = *(short *)(param_1 + 0x54c) + -1;
    *(short *)(param_1 + 0x54c) = sVar5;
    if (sVar5 < 1) {
      *(float *)(param_1 + 0x558) = FLOAT_804380f0;
    }
    else if (FLOAT_80438104 < *(float *)(param_1 + 0x558)) {
      *(float *)(param_1 + 0x558) = FLOAT_80438104;
    }
  }
  fVar1 = FLOAT_804380f0;
  *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x560) < fVar1) && (*(char *)(param_1 + 0x745) == '\0')) {
    *(float *)(param_1 + 0x560) = FLOAT_80438104;
    zz_006d144_(param_1,0xc0);
    local_18 = *(float *)(param_1 + 0x518);
    local_10 = *(undefined4 *)(param_1 + 0x520);
    local_14 = FLOAT_80438144 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    zz_006e39c_(param_1,0xc0,1,0x4000,&local_18);
  }
  zz_006eddc_((double)FLOAT_80438140,param_1,(float *)(param_1 + 0x38));
  if (*(float *)(param_1 + 0x38) < FLOAT_80438110) {
    *(float *)(param_1 + 0x38) = FLOAT_80438110;
  }
  dVar6 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar6);
  dVar6 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar7 = (double)FLOAT_8043810c;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar6);
  FUN_80067310(dVar7,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    fVar2 = FLOAT_804380f0;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    fVar4 = FLOAT_80438134;
    fVar3 = FLOAT_804380f0;
    if (fVar1 <= fVar2) {
      if ((*(char *)(param_1 + 0x745) == '\0') || (*(short *)(param_1 + 0x54a) < 1)) {
        dVar6 = (double)FLOAT_804380ec;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
        *(float *)(param_1 + 0x48) = fVar3;
        *(float *)(param_1 + 0x4c) = fVar3;
        *(float *)(param_1 + 0x44) = fVar3;
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
        zz_004beb8_(dVar6,param_1,0xf,4,9,0xffffffff,0xffffffff);
      }
      else {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined1 *)(param_1 + 0x745) = 0;
        *(float *)(param_1 + 0x558) = fVar4;
        *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
        zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,4,8,0xffffffff,0xffffffff);
      }
    }
  }
  return;
}



// ==== 800a93e0  FUN_800a93e0 ====

void FUN_800a93e0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  *(undefined1 *)(param_1 + 0x6f4) = 2;
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    *(undefined1 *)(param_1 + 0x6f4) = 1;
    if (*(char *)(param_1 + 0x1b03) != '\0') {
      *(undefined1 *)(param_1 + 0x6f4) = 2;
    }
    gnt4_PSQUATScale_bl((double)FLOAT_80438148,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00677b0_(param_1);
    iVar5 = zz_006d144_(param_1,0xc0);
    if (iVar5 != 0) {
      *(undefined1 *)(param_1 + 0x6f4) = 1;
    }
    local_18 = *(float *)(param_1 + 0x518);
    local_10 = *(undefined4 *)(param_1 + 0x520);
    local_14 = FLOAT_80438144 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    zz_006e39c_(param_1,0xc0,1,0x4000,&local_18);
    fVar3 = FLOAT_804380f0;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    fVar4 = FLOAT_80438144;
    fVar2 = FLOAT_804380e8;
    if (fVar1 <= fVar3) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      *(float *)(param_1 + 0x558) = fVar2;
      *(float *)(param_1 + 0x560) = fVar3;
      *(undefined2 *)(param_1 + 0x54c) = 3;
      *(float *)(param_1 + 0x38) = fVar4;
      *(undefined1 *)(param_1 + 0x6ea) = 7;
      if (0 < *(short *)(param_1 + 0x54a)) {
        uVar6 = zz_00055fc_();
        *(byte *)(param_1 + 0x6ea) = ((byte)uVar6 & 1) + 5;
      }
      zz_004beb8_((double)FLOAT_804380ec,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                  0xffffffff);
      *(undefined1 *)(param_1 + 0x6f4) = 1;
      zz_0092dcc_(param_1,0);
      zz_00f036c_(param_1,0x10c);
    }
  }
  return;
}



// ==== 800a9578  FUN_800a9578 ====

void FUN_800a9578(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438120) * FLOAT_80438140);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043810c,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_804380f0;
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043810c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804380f0;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800a9674  zz_00a9674_ ====

void zz_00a9674_(undefined1 *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = (int)(char)param_1[2];
  if (iVar1 < 9) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar1 + -8;
    iVar1 = 8;
  }
  puVar2 = zz_008893c_(2,(int)(char)param_1[4],0,iVar4);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x83] = 0x14;
    puVar5 = (undefined4 *)(puVar2 + 0x144);
    iVar4 = 0;
    puVar2[0x11] = *param_1;
    puVar2[0x12] = param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_800a981c;
    *(code **)(puVar2 + 0x10c) = FUN_800ad66c;
    puVar2[0x173] = param_1[3];
    puVar2[0x176] = PTR_DAT_80433930[0x29];
    puVar2[0x171] = param_1[5];
    do {
      if (iVar1 == 0) {
        *puVar5 = 0;
      }
      else {
        uVar3 = zz_0006d4c_();
        *puVar5 = uVar3;
        iVar1 = iVar1 + -1;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 8);
  }
  return;
}



// ==== 800a9768  zz_00a9768_ ====

void zz_00a9768_(void)

{
  char *pcVar1;
  
  pcVar1 = &DAT_802f9e24;
  while( true ) {
    if (*pcVar1 < '\0') break;
    zz_00a9674_(pcVar1);
    pcVar1 = pcVar1 + 6;
  }
  return;
}



// ==== 800a97b4  zz_00a97b4_ ====

undefined4 zz_00a97b4_(int param_1)

{
  char cVar1;
  
  cVar1 = (&PTR_s_CKPT01_CP000_B_802f92e8)[param_1][0xd];
  if (cVar1 == 'C') {
    return 2;
  }
  if (cVar1 < 'C') {
    if (cVar1 == 'A') {
      return 0;
    }
    if ('@' < cVar1) {
      return 1;
    }
  }
  else if (cVar1 < 'E') {
    return 3;
  }
  return 0;
}



// ==== 800a981c  FUN_800a981c ====

void FUN_800a981c(int param_1)

{
  (*(code *)(&PTR_FUN_802f9f80)[*(char *)(param_1 + 0x18)])();
  if (((*(char *)(param_1 + 0x18) < '\x02') && (PTR_DAT_80433934[0x45] == '\x05')) &&
     ('\x01' < (char)PTR_DAT_80433934[0x52])) {
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800a98a4  FUN_800a98a4 ====

void FUN_800a98a4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,uint param_12,uint *param_13,int param_14,undefined4 param_15,
                 undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *extraout_r4;
  undefined4 *extraout_r4_00;
  undefined4 *extraout_r4_01;
  undefined4 *extraout_r4_02;
  undefined4 *extraout_r4_03;
  undefined4 *extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 *extraout_r4_06;
  undefined4 *extraout_r4_07;
  undefined4 *extraout_r4_08;
  undefined4 *extraout_r4_09;
  undefined4 *extraout_r4_10;
  undefined4 *puVar8;
  undefined4 *extraout_r4_11;
  char *pcVar9;
  short *psVar10;
  int iVar11;
  int *piVar12;
  int unaff_r31;
  double dVar13;
  undefined8 uVar14;
  float local_28;
  float local_24;
  float local_20;
  
  puVar8 = (undefined4 *)PTR_DAT_80433934;
  if (('\x02' < (char)PTR_DAT_80433934[0x45]) || (*(char *)(param_9 + 0x11) == '\n')) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined1 *)(param_9 + 0x82) = 0x11;
    puVar2 = PTR_DAT_80433934;
    if (*(char *)(param_9 + 0x171) == '\0') {
      puVar8 = (undefined4 *)((char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0] * 4);
      unaff_r31 = puVar8[-0x1ff0ec5f];
      *(int *)(param_9 + 0x90) = unaff_r31;
      *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(unaff_r31 + 0x3e4);
      *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(unaff_r31 + 1000);
      *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)(unaff_r31 + 0x491);
      *(undefined1 *)(param_9 + 0x172) = 0xff;
      param_11 = (float *)puVar2;
    }
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      param_1 = (double)zz_0012308_(param_9,puVar8,param_11,param_12,param_13,param_14,param_15,
                                    param_16);
      puVar8 = extraout_r4;
      break;
    case 2:
      if (PTR_DAT_80433934[0x50] != '\0') {
        *(undefined1 *)(param_9 + 0x18) = 2;
        *(undefined1 *)(param_9 + 0x82) = 0;
        return;
      }
      *(code **)(param_9 + 0x100) = FUN_80012274;
      zz_0089100_(param_9,0x21,1);
      fVar3 = FLOAT_80438150;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_80438154;
      *(float *)(param_9 + 100) = fVar3;
      fVar3 = FLOAT_80438158;
      dVar13 = (double)FLOAT_80438158;
      *(float *)(param_9 + 0x6c) = fVar4;
      fVar4 = FLOAT_8043815c;
      *(float *)(param_9 + 0x68) = fVar3;
      *(float *)(param_9 + 0x164) = fVar4;
      *(float *)(param_9 + 0x16c) = fVar4;
      if (*(char *)(param_9 + 0x173) == '\0') {
        *(float *)(param_9 + 0x168) = fVar4;
      }
      else {
        *(float *)(param_9 + 0x168) = FLOAT_80438160;
      }
      *(undefined2 *)(param_9 + 0x74) = 0;
      *(undefined4 *)(*(int *)(param_9 + 0x14c) + 0x14) = 0xffffffff;
      *(undefined4 *)(*(int *)(param_9 + 0x148) + 0x14) = 0xffffffff;
      *(undefined4 *)(*(int *)(param_9 + 0x144) + 0x14) = 0xffffffff;
      *(undefined1 *)(param_9 + 0x192) = 0xff;
      *(undefined1 *)(param_9 + 0x191) = 0xff;
      *(undefined1 *)(param_9 + 400) = 0xff;
      uVar14 = zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x15c),0xf,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)0xe;
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x160),0xe,param_12,param_13,
                                    param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 0x188) = 0;
      puVar8 = (undefined4 *)(*(int *)(PTR_DAT_80433934 + 0x4c) - *(int *)(param_9 + 0x188));
      if ((int)puVar8 < 0x51) {
        *(undefined4 *)(param_9 + 0x18c) = 1;
      }
      else {
        iVar7 = (int)puVar8 / 0x50 + ((int)puVar8 >> 0x1f);
        *(int *)(param_9 + 0x18c) = (iVar7 - (iVar7 >> 0x1f)) + 1;
      }
      *(undefined2 *)(param_9 + 0x1c) = 0;
      break;
    case 3:
      param_12 = (uint)(byte)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_9,0x20,1);
      fVar3 = FLOAT_80438164;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_80438168;
      dVar13 = (double)FLOAT_80438168;
      *(float *)(param_9 + 100) = fVar3;
      fVar3 = FLOAT_8043816c;
      *(float *)(param_9 + 0x68) = fVar4;
      *(float *)(param_9 + 0x6c) = fVar3;
      if (*(char *)(param_9 + 0x173) == '\0') {
        pcVar9 = (char *)0x7;
        *(float *)(param_9 + 0x68) = FLOAT_80438170;
        zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                    *(int *)(param_9 + 0x144),7,param_12,param_13,param_14,param_15,param_16);
        param_2 = (double)FLOAT_80438164;
        local_28 = FLOAT_80438164;
        local_24 = FLOAT_8043815c;
        local_20 = FLOAT_8043816c;
        dVar13 = (double)zz_0007834_((double)FLOAT_8043815c,param_2,param_3,param_4,param_5,param_6,
                                     param_7,param_8,*(int *)(param_9 + 0x144),&local_28,pcVar9,
                                     param_12,param_13,param_14,param_15,param_16);
      }
      uVar14 = zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x148),8,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)0xa;
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x14c),10,param_12,param_13,
                                    param_14,param_15,param_16);
      puVar8 = extraout_r4_00;
      break;
    case 4:
      param_12 = (uint)(byte)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_9,0x20,1);
      fVar3 = FLOAT_80438164;
      *(undefined1 *)(param_9 + 0x84) = 9;
      fVar4 = FLOAT_80438168;
      dVar13 = (double)FLOAT_80438168;
      *(float *)(param_9 + 100) = fVar3;
      fVar3 = FLOAT_80438174;
      *(float *)(param_9 + 0x68) = fVar4;
      *(float *)(param_9 + 0x6c) = fVar3;
      if (*(char *)(param_9 + 0x173) == '\0') {
        *(float *)(param_9 + 0x68) = FLOAT_80438170;
      }
      *(undefined2 *)(param_9 + 0x74) = 0;
      uVar14 = zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x158),9,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)0x6;
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x15c),6,param_12,param_13,
                                    param_14,param_15,param_16);
      puVar8 = extraout_r4_01;
      break;
    case 5:
      param_12 = 0xffffffff;
      *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      param_11 = (float *)0x1;
      param_14 = *(char *)(param_9 + 0x96) * 4;
      param_13 = (uint *)(int)*(short *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 1000);
      *(short *)(param_9 + 0x94) = *(short *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 1000);
      *(undefined1 *)(param_9 + 0x172) = 0xff;
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      param_1 = (double)zz_0089100_(param_9,0x20,1);
      fVar3 = FLOAT_8043815c;
      *(float *)(param_9 + 0x6c) = FLOAT_8043815c;
      *(float *)(param_9 + 0x68) = fVar3;
      *(float *)(param_9 + 100) = fVar3;
      *(undefined1 *)(param_9 + 0x84) = 1;
      puVar8 = extraout_r4_02;
      break;
    case 6:
      *(code **)(param_9 + 0x100) = FUN_80012274;
      zz_0089100_(param_9,0x21,1);
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_80438178;
      fVar3 = FLOAT_8043815c;
      dVar13 = (double)FLOAT_80438178;
      param_11 = (float *)0x19;
      iVar7 = *(char *)(param_9 + 0x12) * 0xc;
      param_13 = (uint *)(&DAT_802f9550 + iVar7);
      param_12 = *param_13;
      uVar6 = *(undefined4 *)(&DAT_802f9554 + iVar7);
      *(uint *)(param_9 + 100) = param_12;
      *(undefined4 *)(param_9 + 0x68) = uVar6;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f9558 + iVar7);
      *(float *)(param_9 + 0x60) = fVar4;
      *(float *)(param_9 + 0x5c) = fVar4;
      *(float *)(param_9 + 0x58) = fVar4;
      *(undefined2 *)(param_9 + 0x1c) = 0;
      *(undefined2 *)(param_9 + 0x1e) = 0xffff;
      *(float *)(param_9 + 0x164) = fVar3;
      *(float *)(param_9 + 0x168) = fVar3;
      *(float *)(param_9 + 0x16c) = fVar3;
      param_1 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0xe0),0x19,param_12,param_13,
                                    param_14,param_15,param_16);
      *(undefined1 *)(param_9 + 0x1a5) = 1;
      *(undefined1 *)(param_9 + 0x1a6) = 0;
      puVar8 = extraout_r4_03;
      break;
    case 7:
      *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      *(code **)(param_9 + 0x100) = FUN_80012274;
      zz_0089100_(param_9,0x21,1);
      param_12 = 1;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_8043817c;
      param_11 = (float *)&DAT_802f97cc;
      *(undefined2 *)(param_9 + 0x1c) = 0;
      fVar3 = FLOAT_8043815c;
      *(float *)(param_9 + 0x6c) = fVar4;
      *(undefined4 *)(param_9 + 100) =
           *(undefined4 *)
            (&DAT_802f97cc + *(char *)(param_9 + 0x12) * 8 + *(char *)(param_9 + 0x173) * 0x10);
      puVar8 = (undefined4 *)(&DAT_802f97cc + *(char *)(param_9 + 0x173) * 0x10);
      param_1 = (double)(float)puVar8[*(char *)(param_9 + 0x12) * 2 + 1];
      *(undefined4 *)(param_9 + 0x68) = puVar8[*(char *)(param_9 + 0x12) * 2 + 1];
      *(float *)(param_9 + 0x164) = fVar3;
      *(float *)(param_9 + 0x168) = fVar3;
      *(float *)(param_9 + 0x16c) = fVar3;
      *(undefined2 *)(param_9 + 0x17a) = 0xffff;
      *(undefined1 *)(param_9 + 400) = 1;
      *(undefined1 *)(param_9 + 0x191) = 0xff;
      break;
    case 8:
      *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
      param_13 = (uint *)(*(char *)(param_9 + 0x96) * 4);
      param_12 = (uint)*(short *)(param_13[-0x1ff0ec5f] + 1000);
      *(short *)(param_9 + 0x94) = *(short *)(param_13[-0x1ff0ec5f] + 1000);
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_9,0x20,1);
      *(undefined1 *)(param_9 + 0x84) = 0x11;
      fVar5 = FLOAT_80438180;
      fVar3 = FLOAT_8043815c;
      iVar11 = 0;
      param_2 = (double)FLOAT_8043815c;
      param_1 = (double)FLOAT_80438180;
      piVar12 = (int *)(param_9 + 0x144);
      *(float *)(param_9 + 0x68) = FLOAT_8043815c;
      fVar4 = FLOAT_80438178;
      iVar7 = 0;
      *(float *)(param_9 + 100) = fVar3;
      *(float *)(param_9 + 0x6c) = fVar5;
      *(float *)(param_9 + 0x60) = fVar4;
      *(float *)(param_9 + 0x5c) = fVar4;
      *(float *)(param_9 + 0x58) = fVar4;
      *(undefined2 *)(param_9 + 0x70) = 0;
      *(undefined2 *)(param_9 + 0x7c) = 0x1000;
      *(float *)(param_9 + 0x17c) = fVar4;
      do {
        param_11 = (float *)(int)*(short *)(&DAT_802f95dc + iVar11 + *(char *)(param_9 + 0x12) * 8);
        param_1 = (double)zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,DAT_804361fc,*piVar12,(int)param_11,param_12,param_13,
                                      param_14,param_15,param_16);
        iVar7 = iVar7 + 1;
        piVar12 = piVar12 + 1;
        iVar11 = iVar11 + 2;
        puVar8 = extraout_r4_04;
      } while (iVar7 < 4);
      break;
    case 9:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      iVar7 = *(char *)(param_9 + 0x12) * 0x18;
      uVar14 = zz_0089100_(param_9,0x20,1);
      *(undefined1 *)(param_9 + 0x84) = 0x11;
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x144),
                                    *(int *)(&DAT_802f9ef0 + iVar7),param_12,param_13,param_14,
                                    param_15,param_16);
      param_11 = *(float **)(&DAT_802f9efc + iVar7);
      uVar6 = *(undefined4 *)(&DAT_802f9f00 + iVar7);
      *(float **)(param_9 + 100) = param_11;
      *(undefined4 *)(param_9 + 0x68) = uVar6;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f9f04 + iVar7);
      *(short *)(param_9 + 0x1c) = (short)*(undefined4 *)(&DAT_802f9ef4 + iVar7);
      puVar8 = *(undefined4 **)(&DAT_802f9ef8 + iVar7);
      *(short *)(param_9 + 0x1e) = (short)puVar8;
      *(undefined **)(param_9 + 0x54) = &DAT_802f9f50;
      *(undefined1 *)(param_9 + 0x82) = 0;
      break;
    case 10:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_9,0x20,1);
      fVar3 = FLOAT_80438184;
      dVar13 = (double)FLOAT_80438184;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_80438188;
      *(float *)(param_9 + 100) = fVar3;
      *(float *)(param_9 + 0x6c) = fVar4;
      if (*(char *)(param_9 + 0x173) == '\0') {
        *(float *)(param_9 + 0x68) = FLOAT_8043818c;
      }
      else {
        *(float *)(param_9 + 0x68) = FLOAT_80438190;
      }
      uVar14 = zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x39,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)0x3a;
      zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0x148),0x3a,param_12,param_13,param_14,param_15,param_16);
      uVar14 = zz_00086b8_((double)FLOAT_8043815c,param_2,param_3,param_4,param_5,param_6,param_7,
                           param_8,DAT_804361fc,*(int *)(param_9 + 0x148),param_11,param_12,param_13
                           ,param_14,param_15,param_16);
      param_1 = (double)zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int *)(param_9 + 0x148),extraout_r4_05,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      *(undefined2 *)(param_9 + 0x74) = 0;
      *(undefined2 *)(param_9 + 0x1c) = 0;
      puVar8 = extraout_r4_06;
      break;
    case 0xb:
      *(code **)(param_9 + 0x100) = FUN_80012274;
      zz_0089100_(param_9,0x21,1);
      fVar3 = FLOAT_80438194;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_80438198;
      *(float *)(param_9 + 100) = fVar3;
      fVar5 = FLOAT_8043819c;
      dVar13 = (double)FLOAT_8043819c;
      *(float *)(param_9 + 0x68) = fVar4;
      fVar3 = FLOAT_8043815c;
      *(float *)(param_9 + 0x6c) = fVar5;
      *(float *)(param_9 + 0x164) = fVar3;
      *(float *)(param_9 + 0x16c) = fVar3;
      if (*(char *)(param_9 + 0x173) != '\0') {
        *(float *)(param_9 + 0x168) = FLOAT_804381a0;
      }
      piVar12 = (int *)(param_9 + 0x144);
      psVar10 = &DAT_802f9d9c;
      iVar7 = 0;
      do {
        dVar13 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     DAT_804361fc,*piVar12,(int)*psVar10,param_12,param_13,param_14,
                                     param_15,param_16);
        iVar7 = iVar7 + 1;
        piVar12 = piVar12 + 1;
        psVar10 = psVar10 + 1;
      } while (iVar7 < 8);
      param_11 = (float *)0x56;
      param_1 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0xe0),0x56,param_12,param_13,
                                    param_14,param_15,param_16);
      puVar8 = extraout_r4_07;
      break;
    case 0xc:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_9,0x20,1);
      fVar3 = FLOAT_8043815c;
      dVar13 = (double)FLOAT_8043815c;
      *(undefined1 *)(param_9 + 0x84) = 1;
      fVar4 = FLOAT_804381a4;
      param_11 = (float *)0x18;
      *(float *)(param_9 + 100) = fVar3;
      *(float *)(param_9 + 0x68) = fVar3;
      *(float *)(param_9 + 0x6c) = fVar4;
      param_1 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x144),0x18,param_12,param_13,
                                    param_14,param_15,param_16);
      *(undefined1 *)(param_9 + 0x82) = 0x11;
      puVar8 = extraout_r4_08;
      break;
    case 0xd:
      *(code **)(param_9 + 0x100) = FUN_80012274;
      uVar14 = zz_0089100_(param_9,0x21,1);
      *(undefined1 *)(param_9 + 0x84) = 1;
      uVar14 = zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x5a,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)0x5b;
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x148),0x5b,param_12,param_13,
                                    param_14,param_15,param_16);
      *(undefined2 *)(param_9 + 0x1e) = 0;
      puVar8 = extraout_r4_09;
      break;
    case 0xe:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      dVar13 = (double)zz_0089100_(param_9,0x20,1);
      *(undefined1 *)(param_9 + 0x84) = 0x11;
      iVar7 = *(char *)(param_9 + 0x173) * 0xc;
      uVar6 = *(undefined4 *)(&DAT_802f9dc8 + iVar7);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f9dc4 + iVar7);
      *(undefined4 *)(param_9 + 0x68) = uVar6;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f9dcc + iVar7);
      fVar3 = FLOAT_80438178;
      if (*(char *)(unaff_r31 + 0x3e6) == '\0') {
        cVar1 = *(char *)(unaff_r31 + 0x3e4);
        *(float *)(param_9 + 0x60) = FLOAT_80438178;
        param_11 = (float *)(cVar1 + 0x3d);
        *(float *)(param_9 + 0x5c) = fVar3;
        *(float *)(param_9 + 0x58) = fVar3;
      }
      else {
        dVar13 = (double)FLOAT_804381a8;
        param_11 = (float *)0x41;
        *(float *)(param_9 + 0x58) = FLOAT_804381a8;
        *(float *)(param_9 + 0x60) = fVar3;
        *(float *)(param_9 + 0x5c) = fVar3;
      }
      param_1 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x144),(int)param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      puVar8 = extraout_r4_10;
      break;
    case 0xf:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      param_11 = (float *)0x1;
      param_1 = (double)zz_0089100_(param_9,0x20,1);
      *(undefined1 *)(param_9 + 0x84) = 1;
      iVar7 = *(char *)(param_9 + 0x173) * 0xc;
      puVar8 = (undefined4 *)(&DAT_802f9ddc + iVar7);
      uVar6 = *(undefined4 *)(&DAT_802f9de0 + iVar7);
      *(undefined4 *)(param_9 + 100) = *puVar8;
      *(undefined4 *)(param_9 + 0x68) = uVar6;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f9de4 + iVar7);
      break;
    case 0x10:
      *(code **)(param_9 + 0x100) = FUN_80047aa4;
      uVar14 = zz_0089100_(param_9,0x20,1);
      *(undefined1 *)(param_9 + 0x84) = 1;
      puVar8 = (undefined4 *)
               (*(char *)(param_9 + 0x173) * 0x18 + -0x7fd0620c + *(char *)(param_9 + 0x12) * 0xc);
      uVar6 = puVar8[1];
      *(undefined4 *)(param_9 + 100) = *puVar8;
      *(undefined4 *)(param_9 + 0x68) = uVar6;
      *(undefined4 *)(param_9 + 0x6c) = puVar8[2];
      uVar14 = zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x3c,param_12,param_13,param_14,
                           param_15,param_16);
      param_11 = (float *)(*(char *)(param_9 + 0x12) + 0x66);
      param_1 = (double)zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0x148),(int)param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      puVar8 = extraout_r4_11;
    }
    zz_00abb58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar8,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800aa2d0  FUN_800aa2d0 ====

/* WARNING: Removing unreachable block (ram,0x800aa648) */
/* WARNING: Removing unreachable block (ram,0x800aa640) */
/* WARNING: Removing unreachable block (ram,0x800aa2e8) */
/* WARNING: Removing unreachable block (ram,0x800aa2e0) */

void FUN_800aa2d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,int param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined1 uVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  char *pcVar5;
  float *pfVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int *piVar13;
  int iVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined8 uVar18;
  double dVar19;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x172) = 0;
    iVar4 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
    *(short *)(param_9 + 0x94) = (short)*(char *)(iVar4 + 0x11);
    cVar3 = *(char *)(iVar4 + 0x7cd);
    param_14 = *(int *)(iVar4 + 0x4ac);
    *(char *)(param_9 + 0x17a) = cVar3;
    dVar17 = DOUBLE_804381c0;
    uVar7 = DAT_802b1cac;
    uVar9 = DAT_802b1ca8;
    if (cVar3 == '\0') {
      local_68 = DAT_802b1ca8;
      piVar13 = (int *)(param_9 + 0x144);
      local_64 = DAT_802b1cac;
      dVar19 = (double)FLOAT_804381ac;
      local_60 = DAT_802b1cb0;
      dVar15 = (double)FLOAT_804381b0;
      uVar1 = *(undefined1 *)(param_14 + 0x9f);
      local_58 = 0x43300000;
      *(undefined1 *)(param_9 + 0x17c) = uVar1;
      *(undefined1 *)(param_9 + 0x17b) = uVar1;
      uStack_54 = (int)*(char *)(param_9 + 0x17b) - 1U ^ 0x80000000;
      dVar16 = (double)(float)(dVar19 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                       dVar17));
      dVar15 = -(double)(float)(dVar16 * dVar15 -
                               (double)*(float *)(&DAT_802f9538 + *(char *)(param_9 + 0x173) * 0xc))
      ;
      iVar4 = param_9;
      for (uVar12 = 0; (int)uVar12 < (int)*(char *)(param_9 + 0x17b); uVar12 = uVar12 + 1) {
        cVar3 = *(char *)(param_9 + 0x173);
        if ((int)uVar12 < 8) {
          iVar8 = *piVar13;
        }
        else {
          iVar8 = *(int *)(iVar4 + 0xc0);
        }
        pcVar5 = (char *)0x17;
        uVar18 = zz_0006fb4_(dVar16,dVar17,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar8,0x17,uVar7,uVar9,param_14,param_15,param_16);
        *(float *)(&DAT_802f9508 + ((uVar12 & 1) + cVar3 * 2) * 0xc) = (float)dVar15;
        uVar18 = zz_0007834_(uVar18,dVar17,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                             (undefined4 *)(&DAT_802f9508 + ((uVar12 & 1) + cVar3 * 2) * 0xc),pcVar5
                             ,uVar7,uVar9,param_14,param_15,param_16);
        zz_0007ae4_(uVar18,dVar17,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,&local_68,
                    pcVar5,uVar7,uVar9,param_14,param_15,param_16);
        fVar2 = FLOAT_804381b8;
        if ((uVar12 & 1) != 0) {
          fVar2 = FLOAT_804381b4;
        }
        dVar16 = (double)zz_0007e74_((double)fVar2,dVar17,param_3,param_4,param_5,param_6,param_7,
                                     param_8,iVar8,extraout_r4,pcVar5,uVar7,uVar9,param_14,param_15,
                                     param_16);
        dVar15 = (double)(float)(dVar15 + dVar19);
        iVar4 = iVar4 + 4;
        piVar13 = piVar13 + 1;
      }
      *(undefined1 *)(param_9 + 0x17c) = 0xff;
      param_13 = uVar9;
      param_2 = dVar17;
    }
    else {
      pcVar5 = (char *)0x16;
      uVar18 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0x144),0x16,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007834_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x144),
                  (undefined4 *)(&DAT_802f9538 + *(char *)(param_9 + 0x173) * 0xc),pcVar5,param_12,
                  param_13,param_14,param_15,param_16);
    }
  }
  iVar4 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  iVar8 = *(int *)(iVar4 + 0x4ac);
  *(undefined1 *)(param_9 + 0x170) = 0;
  dVar17 = DOUBLE_804381c0;
  if (((*(byte *)(iVar4 + 0x7d5) & 1) == 0) &&
     (pfVar6 = (float *)0x1,
     ((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) != 0)) {
    if (*(char *)(iVar4 + 0x7cd) == '\0') {
      if (*(char *)(iVar4 + 0x747) == '\0') {
        *(undefined1 *)(param_9 + 0x17c) = 0xff;
      }
      else {
        *(undefined1 *)(param_9 + 0x170) = 1;
        cVar3 = *(char *)(param_9 + 0x17b) - *(char *)(iVar4 + 0x747);
        iVar4 = (int)cVar3;
        if (iVar4 != *(char *)(param_9 + 0x17c)) {
          *(undefined1 *)(param_9 + 0x17d) = 0x1e;
          *(char *)(param_9 + 0x17c) = cVar3;
        }
        if (*(char *)(param_9 + 0x17d) != '\0') {
          *(char *)(param_9 + 0x17d) = *(char *)(param_9 + 0x17d) + -1;
        }
        piVar13 = (int *)(param_9 + 0x144);
        iVar11 = param_9;
        for (iVar10 = 0; iVar10 < *(char *)(param_9 + 0x17b); iVar10 = iVar10 + 1) {
          if (iVar10 < 8) {
            iVar14 = *piVar13;
          }
          else {
            iVar14 = *(int *)(iVar11 + 0xc0);
          }
          if (iVar4 < iVar10) {
            dVar17 = (double)FLOAT_80438178;
          }
          else if (iVar4 == iVar10) {
            dVar17 = (double)FLOAT_80438178;
          }
          else {
            dVar17 = (double)FLOAT_8043815c;
          }
          uVar18 = zz_00086b8_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar14,pfVar6,iVar8,param_13,param_14,param_15,param_16)
          ;
          zz_0007c30_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar14,
                      extraout_r4_00,pfVar6,iVar8,param_13,param_14,param_15,param_16);
          iVar11 = iVar11 + 4;
          piVar13 = piVar13 + 1;
        }
      }
    }
    else {
      uStack_54 = (int)*(short *)(iVar4 + 0x736) ^ 0x80000000;
      local_58 = 0x43300000;
      uStack_4c = (int)*(short *)(iVar8 + 4) ^ 0x80000000;
      dVar19 = (double)FLOAT_80438178;
      dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_804381c0);
      local_50 = 0x43300000;
      dVar15 = (double)(float)(dVar19 - (double)(float)(dVar16 / (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_4c) - DOUBLE_804381c0)));
      if ((double)FLOAT_8043815c != dVar15) {
        iVar4 = *(int *)(param_9 + 0x144);
        *(undefined1 *)(param_9 + 0x170) = 1;
        uVar18 = zz_00086b8_(dVar15,dVar16,dVar17,dVar19,param_5,param_6,param_7,param_8,
                             DAT_804361fc,iVar4,1,iVar8,param_13,param_14,param_15,param_16);
        zz_0007c30_(uVar18,dVar16,dVar17,dVar19,param_5,param_6,param_7,param_8,iVar4,extraout_r4_01
                    ,pfVar6,iVar8,param_13,param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 800aa664  FUN_800aa664 ====

/* WARNING: Removing unreachable block (ram,0x800aaa74) */
/* WARNING: Removing unreachable block (ram,0x800aa674) */

void FUN_800aa664(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  short sVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  undefined8 local_58;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x1a6) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x1a6) != '\0') && (*(char *)(param_9 + 0x1a5) != '\0')) {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined1 *)(param_9 + 0x1a6) = 0;
    *(undefined1 *)(param_9 + 0x172) = 1;
  }
  iVar9 = *(int *)(param_9 + 0x90);
  dVar14 = (double)zz_0013f3c_(param_9);
  if ((*(char *)(param_9 + 0x1a4) == '\0') && (*(char *)(param_9 + 0x1a6) < '\x01')) {
    if ((*(short *)(param_9 + 0x194) != *(short *)(iVar9 + 0x1c6)) ||
       (*(char *)(param_9 + 0x172) != '\0')) {
      *(short *)(param_9 + 0x194) = *(short *)(iVar9 + 0x1c6);
      param_2 = DOUBLE_804381c0;
      local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar9 + 0x1c6)) ^ 0x80000000);
      dVar14 = (double)(float)(local_58 - DOUBLE_804381c0);
      *(float *)(param_9 + 0x198) =
           (float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(iVar9 + 0x1c4) ^
                                                             0x80000000) - DOUBLE_804381c0));
    }
    sVar3 = *(short *)(param_9 + 0x194);
    if ((*(short *)(param_9 + 0x19c) != sVar3) || (*(char *)(param_9 + 0x172) != '\0')) {
      if (*(char *)(param_9 + 0x172) != '\0') {
        *(short *)(param_9 + 0x1a0) = sVar3;
        *(short *)(param_9 + 0x19c) = sVar3;
      }
      if (*(short *)(param_9 + 0x194) != *(short *)(param_9 + 0x1a0)) {
        *(short *)(param_9 + 0x1a0) = *(short *)(param_9 + 0x194);
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (sVar3 < 0) {
          sVar3 = -sVar3;
        }
        iVar9 = (int)sVar3;
        if (iVar9 < 0x1f) {
          *(undefined2 *)(param_9 + 0x19e) = 1;
        }
        else {
          iVar9 = iVar9 / 0x1e + (iVar9 >> 0x1f);
          *(short *)(param_9 + 0x19e) = ((short)iVar9 - (short)(iVar9 >> 0x1f)) + 1;
        }
      }
      if (*(short *)(param_9 + 0x194) < *(short *)(param_9 + 0x19c)) {
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) - sVar3;
      }
      if (*(short *)(param_9 + 0x19c) < *(short *)(param_9 + 0x194)) {
        sVar3 = *(short *)(param_9 + 0x194) - *(short *)(param_9 + 0x19c);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) + sVar3;
      }
      iVar9 = (int)*(short *)(param_9 + 0x19c);
      if (9999 < iVar9) {
        iVar9 = 9999;
        *(undefined2 *)(param_9 + 0x19c) = 9999;
      }
      piVar12 = &DAT_802f9598;
      piVar13 = (int *)(param_9 + 0x144);
      iVar11 = 0;
      iVar10 = 0;
      uVar6 = 1000;
      do {
        uVar5 = iVar9 / (int)uVar6;
        if (((uVar5 != 0) || (uVar6 == 1)) || (iVar10 != 0)) {
          if (iVar10 == 0) {
            *(short *)(param_9 + 0x196) = 4 - (short)iVar11;
          }
          iVar8 = *piVar13;
          iVar7 = piVar13[4];
          uVar15 = zz_0006fb4_(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar8,*piVar12,param_12,param_13,param_14,param_15,
                               param_16);
          pfVar4 = (float *)piVar12[4];
          zz_0006fb4_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      iVar7,(int)pfVar4,param_12,param_13,param_14,param_15,param_16);
          zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) -
                                     DOUBLE_804381c0),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_804361fc,iVar8,pfVar4,param_12,param_13,param_14,param_15,
                      param_16);
          local_58 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
          uVar15 = zz_00086b8_((double)(float)(local_58 - DOUBLE_804381c0),param_2,param_3,param_4,
                               param_5,param_6,param_7,param_8,DAT_804361fc,iVar7,pfVar4,param_12,
                               param_13,param_14,param_15,param_16);
          uVar15 = zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,
                               extraout_r4,pfVar4,param_12,param_13,param_14,param_15,param_16);
          dVar14 = (double)zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,iVar7,extraout_r4_00,pfVar4,param_12,param_13,
                                       param_14,param_15,param_16);
          piVar13 = piVar13 + 1;
          piVar12 = piVar12 + 1;
          iVar10 = iVar10 + 1;
          iVar9 = iVar9 - (iVar9 / (int)uVar6) * uVar6;
        }
        iVar11 = iVar11 + 1;
        uVar6 = uVar6 / 10;
      } while (iVar11 < 4);
    }
    fVar1 = FLOAT_804381c8;
    bVar2 = false;
    *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
    if (*(float *)(param_9 + 0x198) <= fVar1) {
      bVar2 = true;
      if ((*(ushort *)(param_9 + 0x1c) & 8) == 0) {
        *(undefined1 *)(param_9 + 0x1a2) = 1;
      }
      else {
        *(undefined1 *)(param_9 + 0x1a2) = 0;
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x1a2) = 0;
    }
    fVar1 = FLOAT_8043815c;
    if (bVar2) {
      fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x1a2) ^ 0x80000001) -
                     DOUBLE_804381c0);
    }
    dVar14 = (double)fVar1;
    iVar9 = *(int *)(param_9 + 0xe0);
    dVar16 = (double)(float)((double)FLOAT_804381e4 * dVar14 + (double)FLOAT_804381e0);
    zz_0007cd0_(iVar9,(int)(DOUBLE_804381d0 * dVar14) & 0xff,
                (int)(DOUBLE_804381d0 * DOUBLE_804381d8 * dVar14) & 0xff,0);
    zz_0007cac_(dVar16,iVar9);
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 800aaa90  zz_00aaa90_ ====

void zz_00aaa90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (*(short *)(param_11 + 2) == 0) {
    *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  }
  else {
    iVar1 = (int)*param_12;
    if (*(short *)(param_9 + 0x17a) != iVar1) {
      local_58 = DAT_802b1cb4;
      local_54 = DAT_802b1cb8;
      local_50 = DAT_802b1cbc;
      if (999 < iVar1) {
        iVar1 = 999;
      }
      *(short *)(param_9 + 0x17a) = (short)iVar1;
      iVar8 = 0;
      iVar7 = 0;
      uVar9 = 100;
      psVar3 = param_12;
      do {
        uVar4 = iVar1 / (int)uVar9;
        if (((uVar4 != 0) || (uVar9 == 1)) || (iVar7 != 0)) {
          if (iVar7 == 0) {
            *(short *)(param_9 + 0x17c) = 3 - (short)iVar8;
          }
          pfVar2 = (float *)0x13;
          iVar6 = param_9 + (2 - iVar8) * 4;
          iVar5 = *(int *)(iVar6 + 0xe0);
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x13,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_44 = uVar4 ^ 0x80000000;
          local_48 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_44) -
                                              DOUBLE_804381c0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                               extraout_r4,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar5 = *(int *)(iVar6 + 0xec);
          pfVar2 = (float *)0x15;
          uVar10 = zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x15,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_3c = uVar4 ^ 0x80000000;
          local_40 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) -
                                              DOUBLE_804381c0),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5
                                ,extraout_r4_00,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar7 = iVar7 + 1;
          iVar1 = iVar1 - (iVar1 / (int)uVar9) * uVar9;
        }
        iVar8 = iVar8 + 1;
        uVar9 = uVar9 / 10;
      } while (iVar8 < 3);
      if (*(char *)(param_9 + 0x172) == '\0') {
        if (*(short *)(param_11 + 4) == 1) {
          if (*param_12 < param_12[1]) {
            *(undefined2 *)(param_9 + 0x17e) = 10;
          }
        }
        else if (*param_12 < *(short *)(param_11 + 2)) {
          *(undefined2 *)(param_9 + 0x17e) = 10;
        }
      }
      else {
        *(undefined2 *)(param_9 + 0x17e) = 0;
        *(undefined2 *)(param_9 + 0x182) = 0;
      }
      pfVar2 = (float *)0x43300000;
      uStack_3c = (int)*(short *)(param_9 + 0x17a) ^ 0x80000000;
      iVar1 = *(int *)(param_9 + 0x154);
      uStack_44 = (int)*(short *)(param_11 + 2) ^ 0x80000000;
      local_40 = 0x43300000;
      dVar12 = (double)FLOAT_80438178;
      local_48 = 0x43300000;
      dVar11 = DOUBLE_804381c0;
      uVar10 = zz_00086b8_((double)(float)(dVar12 - (double)((float)((double)CONCAT44(0x43300000,
                                                                                      uStack_3c) -
                                                                    DOUBLE_804381c0) /
                                                            (float)((double)CONCAT44(0x43300000,
                                                                                     uStack_44) -
                                                                   DOUBLE_804381c0))),
                           DOUBLE_804381c0,dVar12,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar1,0x43300000,psVar3,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,dVar12,param_4,param_5,param_6,param_7,param_8,iVar1,extraout_r4_01,
                  pfVar2,psVar3,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 800aace8  zz_00aace8_ ====

void zz_00aace8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  float local_28;
  float local_24;
  float local_20;
  
  iVar5 = *(int *)(param_9 + 0x15c);
  iVar2 = *(char *)(param_9 + 399) * 4;
  iVar4 = param_10 + iVar2;
  pfVar3 = (float *)(*(int *)(param_10 + 0x4ac) + iVar2);
  uVar6 = zz_00086b8_((double)(*(float *)(iVar4 + 0x648) / pfVar3[0x61]),param_2,param_3,param_4,
                      param_5,param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar3,iVar4,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4,pfVar3
              ,iVar4,param_13,param_14,param_15,param_16);
  iVar5 = *(int *)(param_9 + 0x160);
  iVar2 = *(char *)(param_9 + 399) * 4;
  if (*(float *)(param_10 + iVar2 + 0x648) == *(float *)(*(int *)(param_10 + 0x4ac) + iVar2 + 0x184)
     ) {
    *(undefined1 *)(iVar5 + 0x10) = 1;
    if (*(char *)(param_9 + 0x18e) == '\0') {
      *(undefined2 *)(param_9 + 0x186) = 0;
      *(undefined2 *)(param_9 + 0x188) = 0;
    }
    else {
      *(short *)(param_9 + 0x186) = *(short *)(param_9 + 0x186) + 0x444;
      *(short *)(param_9 + 0x188) = *(short *)(param_9 + 0x188) + 1;
    }
    *(undefined1 *)(param_9 + 0x18e) = 1;
    fVar1 = FLOAT_804381e8;
    if ((*(ushort *)(param_9 + 0x188) & 4) != 0) {
      fVar1 = FLOAT_80438178;
    }
    uVar6 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_804361fc,iVar5,pfVar3,iVar4,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4_00,
                pfVar3,iVar4,param_13,param_14,param_15,param_16);
    local_20 = FLOAT_80438178;
    dVar7 = zz_0045238_(*(short *)(param_9 + 0x186));
    local_28 = (float)((double)FLOAT_804381f0 * dVar7 + (double)FLOAT_804381ec);
    local_24 = local_28;
    zz_0007ae4_(dVar7,(double)FLOAT_804381f0,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                &local_28,(char *)pfVar3,iVar4,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(iVar5 + 0x10) = 0;
    *(undefined1 *)(param_9 + 0x18e) = 0;
  }
  return;
}



// ==== 800aae3c  FUN_800aae3c ====

/* WARNING: Removing unreachable block (ram,0x800ab228) */
/* WARNING: Removing unreachable block (ram,0x800aae4c) */

int FUN_800aae3c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short sVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  float *pfVar4;
  char *pcVar5;
  short *psVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 auStack_58 [2];
  float local_50;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  double local_38;
  
  sVar2 = *(short *)(param_11 + 1);
  iVar9 = 0;
  if (sVar2 == 1) {
    dVar11 = (double)*(float *)(param_12 + 2);
    if ((double)FLOAT_8043815c < dVar11) {
      iVar8 = *(int *)(param_9 + 0x154);
      pfVar4 = (float *)((int)*(short *)((int)param_11 + 2) * (int)*(short *)((int)param_11 + 6));
      local_48 = (double)(CONCAT44(0x43300000,pfVar4) ^ 0x80000000);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_804381c0));
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_01
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar8 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_02
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      if (*param_12 == 0) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
        if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
          *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
        }
        iVar9 = 1;
      }
    }
  }
  else if (sVar2 < 1) {
    if (((-1 < sVar2) && (*param_12 == 0)) && (*(short *)(param_9 + 0x17e) == 0)) {
      iVar9 = *(int *)(param_9 + 0x154);
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)param_11 + 6)) ^ 0x80000000);
      dVar11 = (double)*(float *)(param_12 + 2);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_804381c0));
      pfVar4 = param_11;
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4,
                  pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar9 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4_00
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  else if (sVar2 < 4) {
    pfVar4 = (float *)0x43300000;
    iVar8 = *(int *)(param_9 + 0x154);
    uStack_3c = (int)*(short *)((int)param_11 + 2) ^ 0x80000000;
    local_48 = (double)CONCAT44(0x43300000,(int)*param_12 ^ 0x80000000);
    param_3 = (double)FLOAT_80438178;
    local_40 = 0x43300000;
    dVar12 = (double)(float)(param_3 -
                            (double)((float)(local_48 - DOUBLE_804381c0) /
                                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_804381c0
                                           )));
    psVar6 = param_12;
    dVar11 = DOUBLE_804381c0;
    uVar10 = zz_00086b8_(dVar12,DOUBLE_804381c0,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_804361fc,iVar8,0x43300000,param_12,param_13,param_14,param_15,param_16)
    ;
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_03,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    iVar8 = *(int *)(param_9 + 0x158);
    uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                         iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_04,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    if (*param_12 == 0) {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  fVar3 = FLOAT_8043815c;
  if (iVar9 != 0) {
    local_40 = 0x43300000;
    uStack_3c = (int)*(char *)(param_9 + 0x180) ^ 0x80000001;
    fVar3 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_804381c0);
  }
  dVar12 = (double)fVar3;
  uVar7 = 0;
  iVar8 = *(int *)(param_9 + 0x144);
  local_48 = (double)(longlong)(int)(DOUBLE_804381d0 * dVar12);
  uVar1 = (uint)(DOUBLE_804381d0 * DOUBLE_804381d8 * dVar12);
  local_38 = (double)(longlong)(int)uVar1;
  pcVar5 = (char *)(uVar1 & 0xff);
  dVar11 = DOUBLE_804381d0;
  zz_0007cd0_(iVar8,(int)(DOUBLE_804381d0 * dVar12) & 0xff,pcVar5,0);
  dVar12 = (double)zz_0007cac_((double)(float)((double)FLOAT_804381a8 * dVar12 +
                                              (double)FLOAT_804381f4),iVar8);
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  if (*(char *)(param_9 + 0x180) == '\0') {
    *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 1;
  }
  else {
    *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 1;
  }
  if (*(short *)(param_9 + 0x17e) == 0) {
    dVar12 = (double)*(float *)(param_12 + 2);
    if (dVar12 <= (double)FLOAT_8043815c) {
      if (*(short *)(param_9 + 0x182) != 0) {
        *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
      }
    }
    else if ((*(short *)(param_11 + 1) != 2) && (*(short *)(param_11 + 1) != 3)) {
      *(undefined2 *)(param_9 + 0x184) = 0xf000;
      *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
    }
  }
  else {
    *(short *)(param_9 + 0x17e) = *(short *)(param_9 + 0x17e) + -1;
    *(undefined2 *)(param_9 + 0x184) = 0x1000;
    *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
  }
  zz_0007a60_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16)
  ;
  local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x182)) ^ 0x80000000);
  local_50 = (float)((double)FLOAT_804381f8 * (double)(float)(local_38 - DOUBLE_804381c0));
  zz_0007988_(DOUBLE_804381c0,(double)FLOAT_804381f8,param_3,param_4,param_5,param_6,param_7,param_8
              ,*(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16
             );
  return iVar9;
}



// ==== 800ab244  zz_00ab244_ ====

void zz_00ab244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_00aaa90_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00aace8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_800aae3c(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ab2c4  zz_00ab2c4_ ====

void zz_00ab2c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_00aaa90_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_800aae3c(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ab330  zz_00ab330_ ====

void zz_00ab330_(void)

{
  return;
}



// ==== 800ab334  zz_00ab334_ ====

void zz_00ab334_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  float *pfVar5;
  int iVar6;
  short *psVar7;
  int in_r7;
  int in_r8;
  int in_r9;
  undefined4 in_r10;
  int *piVar8;
  undefined8 uVar9;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x191) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x191) == '\0') || (*(char *)(param_9 + 400) == '\0')) goto LAB_800ab5ac;
  in_r8 = *(int *)(param_9 + 0x90);
  in_r9 = 0;
  iVar6 = (int)*(short *)(in_r8 + 1000);
  iVar2 = 3;
  *(short *)(param_9 + 0x94) = *(short *)(in_r8 + 1000);
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(in_r8 + 0x3e4);
  *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 399) = 0xff;
  *(undefined1 *)(param_9 + 0x18a) = 0;
  in_r7 = in_r8;
  do {
    if (*(short *)(in_r7 + 0x78e) != 0) {
      cVar1 = *(char *)(param_9 + 0x18a);
      if (*(char *)(param_9 + 0x12) == cVar1) {
        *(char *)(param_9 + 0x13) = cVar1;
        *(char *)(param_9 + 399) = (char)in_r9;
        break;
      }
      *(char *)(param_9 + 0x18a) = cVar1 + '\x01';
    }
    in_r7 = in_r7 + 8;
    in_r9 = in_r9 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  piVar8 = (int *)(param_9 + 0x144);
  *(char *)(param_9 + 399) = *(char *)(param_9 + 0x12) << 1;
  *(undefined1 *)(param_9 + 0x18d) = *(undefined1 *)(in_r8 + *(char *)(param_9 + 0x12) + 0x8d0);
  *(undefined1 *)(*(int *)(param_9 + 0x144) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x148) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x14c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x150) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x15c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x160) + 0x10) = 0;
  cVar1 = *(char *)(param_9 + 0x18d);
  if (cVar1 == '\x03') {
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802f994c;
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      piVar3 = &DAT_802f9c0c;
      *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    }
    else if (cVar1 < '\x01') {
LAB_800ab51c:
      piVar3 = (int *)0x0;
    }
    else {
      *(undefined2 *)(param_9 + 0x17c) = 0;
      piVar3 = &DAT_802f9aac;
    }
  }
  else if (cVar1 == '\x05') {
    *(undefined2 *)(param_9 + 0x17c) = 0;
    piVar3 = &DAT_802f97ec;
  }
  else {
    if ('\x04' < cVar1) goto LAB_800ab51c;
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802f994c;
  }
  if (piVar3 != (int *)0x0) {
    iVar2 = 0;
    do {
      pcVar4 = (char *)*piVar3;
      if (-1 < (int)pcVar4) {
        if (iVar2 == 2) {
          pcVar4 = pcVar4 + *(char *)(param_9 + 0x12);
          uVar9 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_804361fc,*piVar8,(int)pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        }
        else {
          uVar9 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_804361fc,*piVar8,(int)pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        }
        uVar9 = zz_0007834_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                            piVar3 + 1,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        uVar9 = zz_0007ae4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                            piVar3 + 4,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
        param_1 = zz_0007988_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                              piVar3 + 7,pcVar4,iVar6,in_r7,in_r8,in_r9,in_r10);
      }
      iVar2 = iVar2 + 1;
      piVar8 = piVar8 + 1;
      piVar3 = piVar3 + 0xb;
    } while (iVar2 < 8);
  }
  *(undefined1 *)(param_9 + 0x191) = 0;
LAB_800ab5ac:
  iVar2 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  uVar9 = zz_0014ac4_(param_9);
  if (*(char *)(param_9 + 0x191) < '\x01') {
    cVar1 = *(char *)(param_9 + 0x18d);
    iVar6 = iVar2 + *(char *)(param_9 + 399) * 8;
    pfVar5 = (float *)(iVar6 + 0x78c);
    psVar7 = (short *)(iVar6 + 0x774);
    if (cVar1 == '\x05') {
      zz_00ab244_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x03') {
      zz_00aace8_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x02') {
      zz_00ab2c4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x01') {
      zz_00ab330_();
    }
    else if (cVar1 == '\x04') {
      zz_00aace8_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,pfVar5
                  ,psVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      *(undefined1 *)(param_9 + 0x170) = 0;
    }
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 800ab6a0  zz_00ab6a0_ ====

void zz_00ab6a0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0015cc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ab6c0  zz_00ab6c0_ ====

void zz_00ab6c0_(int param_1)

{
  zz_0016384_(param_1);
  return;
}



// ==== 800ab6e0  zz_00ab6e0_ ====

void zz_00ab6e0_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_00165ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ab700  zz_00ab700_ ====

void zz_00ab700_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (PTR_DAT_80433930[0x29] == '\x01') {
    if ((*(char *)(param_9 + 0x19) < '\x03') &&
       (*(char *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 0x486) != '\0')) {
      *(undefined1 *)(param_9 + 0x19) = 3;
    }
    fVar3 = FLOAT_8043815c;
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 == '\x04') {
      sVar4 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar4;
      fVar3 = FLOAT_804381fc;
      if (sVar4 < 1) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0xd8) = fVar3;
        *(float *)(param_9 + 0xd4) = fVar3;
      }
    }
    else if (cVar1 < '\x04') {
      if ('\x02' < cVar1) {
        *(char *)(param_9 + 0x19) = cVar1 + '\x01';
        *(undefined2 *)(param_9 + 0x1c) = 0xb4;
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                    *(int *)(param_9 + 0x148),0x2b,param_9,in_r7,in_r8,in_r9,in_r10);
      }
    }
    else if ((cVar1 != '\x06') && (cVar1 < '\x06')) {
      fVar2 = *(float *)(param_9 + 0xd4) - FLOAT_80438178;
      *(float *)(param_9 + 0xd4) = fVar2;
      if (fVar2 <= fVar3) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0xd4) = fVar3;
      }
      zz_0007cac_((double)(FLOAT_80438204 *
                           (*(float *)(param_9 + 0xd4) / *(float *)(param_9 + 0xd8)) +
                          FLOAT_80438200),*(int *)(param_9 + 0x148));
    }
  }
  return;
}



