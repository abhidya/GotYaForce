// ==== 80071d78  zz_0071d78_ ====

void zz_0071d78_(int param_1)

{
  float fVar1;
  double dVar2;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar1 = FLOAT_804376e4;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_80437774,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  dVar2 = gnt4_PSVECMag_bl(afStack_18);
  if ((double)FLOAT_80437778 < dVar2) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80071e4c  zz_0071e4c_ ====

void zz_0071e4c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (**(code **)(&DAT_80433870 + *(char *)(param_1 + 0x540) * 4))();
  return;
}



// ==== 80071e98  zz_0071e98_ ====

void zz_0071e98_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_804376e4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x564) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_804376e0,param_1,0xf,4,5,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804376e4;
  return;
}



// ==== 80071f6c  zz_0071f6c_ ====

void zz_0071f6c_(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_0067458_((double)FLOAT_804376e8,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80437764 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    zz_00b22f4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80072048  zz_0072048_ ====

void zz_0072048_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_FUN_802d4280;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_0072144__802d4284;
  *(undefined **)(param_1 + 0x4bc) = PTR_LAB_802d4288;
  *(undefined **)(param_1 + 0x4c0) = PTR_LAB_802d428c;
  *(undefined **)(param_1 + 0x4c4) = PTR_LAB_802d4290;
  *(undefined **)(param_1 + 0x4c8) = PTR_LAB_802d4294;
  *(undefined **)(param_1 + 0x4cc) = PTR_LAB_802d4298;
  *(undefined **)(param_1 + 0x4d0) = PTR_LAB_802d429c;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_802d42a0;
  *(undefined **)(param_1 + 0x4d8) = PTR_FUN_802d42a4;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_802d42a8;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_802d42ac;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_802d42b0;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_802d42b4;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_802d42b8;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_802d42bc;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_802d4478;
  *(undefined **)(param_1 + 0x1d80) = &DAT_802bf040;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_802be960;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_802d46e0;
  return;
}



// ==== 80072144  zz_0072144_ ====

void zz_0072144_(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x100) {
    zz_004dbd8_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x108) {
    zz_004dbd8_(param_1,1);
  }
  return;
}



// ==== 800721d8  FUN_800721d8 ====

void FUN_800721d8(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802d42c0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80072218  FUN_80072218 ====

void FUN_80072218(int param_1)

{
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float afStack_44 [3];
  float local_38;
  undefined4 local_28;
  undefined4 local_18;
  
  local_50 = *(float *)(param_1 + 0xa24);
  local_4c = *(undefined4 *)(param_1 + 0xa34);
  local_48 = *(undefined4 *)(param_1 + 0xa44);
  gnt4_PSQUATScale_bl((double)FLOAT_80437780,&local_50,&local_50);
  local_5c = *(undefined4 *)(param_1 + 0xa2c);
  local_58 = *(undefined4 *)(param_1 + 0xa3c);
  local_54 = *(undefined4 *)(param_1 + 0xa4c);
  gnt4_PSMTXIdentity_bl(afStack_44);
  zz_0045ef4_(afStack_44,5,&local_50,&local_5c);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xa24),(float *)&DAT_802d42d0,&local_68);
  local_38 = local_68;
  local_28 = local_64;
  local_18 = local_60;
  zz_00aedc0_(param_1,afStack_44,0,*(undefined1 *)(param_1 + 0x88));
  zz_00f036c_(param_1,6);
  return;
}



// ==== 800722f8  FUN_800722f8 ====

void FUN_800722f8(int param_1)

{
  (*(code *)(&PTR_FUN_802d42dc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80072334  FUN_80072334 ====

void FUN_80072334(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437788;
  fVar1 = FLOAT_80437784;
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80437788) * FLOAT_80437784);
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) - dVar2
                           ) * fVar1);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_zz_00729b0__802d42e8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800723e0  FUN_800723e0 ====

void FUN_800723e0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_0072438__802d4300)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 80072438  zz_0072438_ ====

void zz_0072438_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80437794;
  fVar1 = FLOAT_80437790;
  iVar3 = 0;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  if (*(short *)(param_1 + 1000) == 0x108) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      iVar3 = 1;
    }
  }
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    iVar3 = iVar3 + 0x11;
  }
  (*(code *)(&PTR_zz_00724c8__802d430c)[*(char *)(param_1 + 0x581)])(param_1,iVar3);
  return;
}



// ==== 800724c8  zz_00724c8_ ====

void zz_00724c8_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(short *)(param_1 + 1000) == 0x108) {
    iVar1 = 0xe;
  }
  iVar1 = iVar1 + param_2;
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,iVar1,0xffffffff,0xffffffff);
  if (((*(short *)(param_1 + 1000) == 0x108) || (*(char *)(param_1 + 0x1d0c) != '\x02')) ||
     (*(char *)(param_1 + 0x1d0d) != iVar1)) {
    zz_004beb8_((double)FLOAT_80437780,param_1,2,2,iVar1,4,2);
  }
  return;
}



// ==== 80072578  zz_0072578_ ====

void zz_0072578_(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    iVar1 = 3;
    if ((*(char *)(param_1 + 0x5db) == '\x02') && (*(short *)(param_1 + 1000) != 0x108)) {
      iVar1 = 0;
    }
    zz_004beb8_((double)FLOAT_80437780,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800725f8  zz_00725f8_ ====

void zz_00725f8_(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x543) < '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 4;
    zz_006a3d0_(param_1,'\0',4,2);
  }
  else {
    zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
    if ((((int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f) <= (int)*(char *)(param_1 + 0x747))
        || ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0)) && ((*(uint *)(param_1 + 0x5e0) & 2) == 0)) {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800726ac  zz_00726ac_ ====

void zz_00726ac_(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 9,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80437780,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8007272c  zz_007272c_ ====

void zz_007272c_(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
  return;
}



// ==== 80072764  zz_0072764_ ====

void zz_0072764_(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80437780,param_1,1,2,param_2 + 0xc,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\x02') || ((int)*(char *)(param_1 + 0x1d0d) != param_2 + 0xc)
     ) {
    zz_004beb8_((double)FLOAT_80437780,param_1,2,2,param_2 + 0xc,4,2);
  }
  return;
}



// ==== 800727f4  zz_00727f4_ ====

void zz_00727f4_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  if (*(char *)(param_1 + 0x543) < '\0') {
    uVar3 = *(uint *)(param_1 + 0x5e0);
    if ((uVar3 & 0x80) != 0) {
      zz_006a3d0_(param_1,'\0',4,2);
      return;
    }
    if ((uVar3 & 0x40) == 0) {
      if ((uVar3 & 0x10) != 0) {
        *(undefined1 *)(param_1 + 0x581) = 0;
        zz_006a3d0_(param_1,'\0',0,2);
        return;
      }
    }
    else {
      zz_006d0dc_(param_1,0xc1,0);
    }
  }
  fVar2 = FLOAT_80437798;
  if ((*(char *)(param_1 + 0x543) < '\x01') &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0073330_(param_1);
  }
  return;
}



// ==== 800728f0  zz_00728f0_ ====

void zz_00728f0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_80437798) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_007320c_(param_9);
        return;
      }
    }
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_80072978;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (*(char *)(param_9 + 0x1cee) == '\0') {
    return;
  }
LAB_80072978:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 800729b0  zz_00729b0_ ====

void zz_00729b0_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_zz_00729f8__802d4324)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800729f8  zz_00729f8_ ====

void zz_00729f8_(int param_1)

{
  zz_0072438_(param_1);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
  return;
}



// ==== 80072a40  FUN_80072a40 ====

/* WARNING: Removing unreachable block (ram,0x80072aec) */
/* WARNING: Removing unreachable block (ram,0x80072a50) */

void FUN_80072a40(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80437798;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    zz_004cd24_(param_1,0xf);
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0073330_(param_1);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
      zz_006a474_(param_1);
    }
  }
  else {
    dVar4 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = fVar2;
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  }
  return;
}



// ==== 80072b08  FUN_80072b08 ====

void FUN_80072b08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_80437798) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) == 0) {
      if ((*(char *)(param_9 + 0x5db) != '\x01') || ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0))
      goto LAB_80072bb8;
    }
    else {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_007320c_(param_9);
        return;
      }
    }
    if (*(char *)(param_9 + 0x1cee) == '\0') {
      return;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(char *)(param_9 + 0x5db) == '\x01') {
      zz_006d0dc_(param_9,0xc1,0);
      return;
    }
  }
LAB_80072bb8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 80072bf0  FUN_80072bf0 ====

void FUN_80072bf0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 uint param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  
  if (*(char *)(param_9 + 0x540) == '\0') {
    bVar1 = *(byte *)(param_9 + 0x1cef);
    param_11 = (uint)bVar1;
    if ('\0' < (char)bVar1) {
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xffffffdf;
      iVar2 = zz_006c674_(param_9);
      if (iVar2 != 2) {
        *(undefined1 *)(param_9 + 0x581) = 3;
        zz_006a3d0_(param_9,'\0',3,0);
        return;
      }
      *(undefined1 *)(param_9 + 0x581) = 0;
      zz_006a3d0_(param_9,'\0',0,2);
      return;
    }
    if ((char)bVar1 < '\0') {
      *(undefined1 *)(param_9 + 0x581) = 0;
      uVar3 = zz_006e004_(param_9);
      if ((int)uVar3 < 0) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006a3d0_(param_9,'\0',0,0);
      return;
    }
    *(undefined1 *)(param_9 + 0x540) = 1;
    dVar4 = (double)zz_00734d8_(param_9);
  }
  else {
    if ((*(uint *)(param_9 + 0x5d4) & 0x40) != 0) {
      *(undefined1 *)(param_9 + 0x745) = 1;
    }
    dVar4 = (double)*(float *)(param_9 + 0x558);
    if (dVar4 <= (double)FLOAT_80437798) {
      if (*(char *)(param_9 + 0x745) != '\0') {
        if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
          zz_006a3d0_(param_9,'\0',0,0);
          return;
        }
        dVar4 = (double)zz_00734d8_(param_9);
      }
    }
    else {
      *(float *)(param_9 + 0x558) = (float)(dVar4 - (double)*(float *)(param_9 + 0x1dc8));
    }
  }
  if ((*(char *)(param_9 + 0x1afc) == *(char *)(param_9 + 0x1b3c)) &&
     (*(char *)(param_9 + 0x1afd) == *(char *)(param_9 + 0x1b3d))) {
    zz_004cd24_(param_9,1);
  }
  else {
    dVar4 = (double)zz_0048d54_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,1,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if ((*(uint *)(param_9 + 0x5e0) & 0x20) == 0) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(float *)(param_9 + 0x694) =
         (float)((double)CONCAT44(0x43300000,(int)*(float *)(param_9 + 0x558) ^ 0x80000000) -
                DOUBLE_80437788) + *(float *)(param_9 + 0x1dc8);
  }
  return;
}



// ==== 80072e00  FUN_80072e00 ====

void FUN_80072e00(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d4330)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80072e48  FUN_80072e48 ====

void FUN_80072e48(int param_1)

{
  double dVar1;
  
  zz_0072438_(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_8043779c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80437798;
  return;
}



// ==== 80072eb0  FUN_80072eb0 ====

void FUN_80072eb0(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x581) = 3;
    zz_0073330_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  FUN_80067310((double)FLOAT_8043779c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_00b22f4_(param_1);
  return;
}



// ==== 80072f4c  FUN_80072f4c ====

void FUN_80072f4c(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d433c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80072f94  FUN_80072f94 ====

void FUN_80072f94(int param_1)

{
  zz_0072438_(param_1);
  zz_006d0dc_(param_1,0x81,-0x8000);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804377a0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80437798;
  return;
}



// ==== 8007301c  FUN_8007301c ====

void FUN_8007301c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804377a0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,-0x8000);
  fVar2 = FLOAT_80437798;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_800730d0;
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0073330_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a474_(param_1);
  }
LAB_800730d0:
  zz_00b22f4_(param_1);
  return;
}



// ==== 800730ec  FUN_800730ec ====

void FUN_800730ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804377a0,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
  zz_00677b0_(param_9);
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (((double)FLOAT_80437798 < dVar2) &&
     (*(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8)),
     *(char *)(param_9 + 0x5db) == '\x01')) {
    zz_006d0dc_(param_9,0xc1,-0x8000);
    return;
  }
  if ((*(uint *)(param_9 + 0x5d4) & 0x20) == 0) {
    if (((*(char *)(param_9 + 0x5db) == '\x01') && ((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0)) &&
       (*(char *)(param_9 + 0x1cee) == '\0')) {
      zz_00b22f4_(param_9);
      return;
    }
  }
  else {
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if (iVar1 != 0) {
      zz_007320c_(param_9);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 8007320c  zz_007320c_ ====

void zz_007320c_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  
  uVar3 = *(uint *)(param_1 + 0x5e0);
  if ((uVar3 & 0x100) == 0) {
    if ((uVar3 & 0x80) == 0) {
      if ((uVar3 & 0x20) == 0) {
        if ((uVar3 & 0x40) == 0) {
          if ((uVar3 & 0x10) == 0) {
            if (*(char *)(param_1 + 0x5e4) == '\x04') {
              uVar5 = 3;
            }
            else {
              uVar5 = 0;
            }
          }
          else {
            uVar5 = 1;
          }
        }
        else {
          uVar5 = 3;
        }
      }
      else if ((uVar3 & 0x40) == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = 3;
      }
    }
    else {
      uVar5 = 4;
    }
  }
  else {
    uVar5 = 5;
  }
  uVar4 = zz_006c674_(param_1);
  zz_006a3d0_(param_1,'\0',uVar5,(char)uVar4);
  *(undefined1 *)(param_1 + 0x540) = 1;
  fVar1 = FLOAT_80437790;
  uVar4 = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  fVar2 = FLOAT_80437794;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar4 = 0x12;
  }
  (*(code *)(&PTR_zz_00724c8__802d4348)[*(char *)(param_1 + 0x581)])(param_1,uVar4);
  return;
}



// ==== 80073330  zz_0073330_ ====

/* WARNING: Removing unreachable block (ram,0x800734b8) */
/* WARNING: Removing unreachable block (ram,0x80073340) */

void zz_0073330_(int param_1)

{
  short sVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  *(undefined2 *)(param_1 + 0x1900) = 0;
  *(undefined2 *)(param_1 + 0x1918) = 0;
  zz_0046698_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    iVar4 = 7;
    if (*(char *)(param_1 + 0x1b04) != '\0') {
      iVar4 = 0xb;
    }
    local_2c = *(float *)(param_1 + 0x910);
    local_28 = *(undefined4 *)(param_1 + 0x920);
    local_24 = *(undefined4 *)(param_1 + 0x930);
    local_38 = *(float *)(param_1 + 0x518);
    local_34 = *(float *)(param_1 + 0x51c);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_38);
    dVar6 = (double)local_34;
    local_34 = FLOAT_80437798;
    dVar5 = gnt4_PSVECMag_bl(&local_38);
    iVar2 = FUN_800452a0(dVar6,dVar5);
    sVar1 = (short)iVar2;
    if (iVar4 == 0xb) {
      sVar1 = -sVar1;
    }
    *(short *)(param_1 + iVar4 * 6 + 0x18d6) = sVar1;
    iVar2 = param_1 + iVar4 * 0xc;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + iVar4 * 4 + 0x1996) * 0x30 + 0x8d4),
                (float *)(param_1 + iVar4 * 0x30 + 0x8d4),(short *)(param_1 + iVar4 * 6 + 0x18d4),
                (undefined4 *)(iVar2 + 0x12d4),(float *)(param_1 + iVar4 * 0x10 + 0xed4),
                (float *)(iVar2 + 0x15d4));
  }
  iVar4 = zz_006dbe0_(param_1,0,1,1);
  if (iVar4 != 0) {
    if (*(short *)(param_1 + 1000) == 0x100) {
      pbVar3 = &DAT_80433878;
    }
    else if (*(short *)(param_1 + 1000) == 0x108) {
      pbVar3 = (byte *)0x8043387a;
    }
    else {
      pbVar3 = (byte *)0x0;
    }
    if (pbVar3 != (byte *)0x0) {
      if (*(char *)(param_1 + 0x1b04) != '\0') {
        pbVar3 = pbVar3 + 1;
      }
      zz_0082824_(param_1,(uint)*pbVar3);
    }
  }
  return;
}



// ==== 800734d8  zz_00734d8_ ====

void zz_00734d8_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437794;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    if (*(short *)(param_1 + 1000) == 0x100) {
      zz_0082824_(param_1,0x14);
    }
    else if (*(short *)(param_1 + 1000) == 0x108) {
      zz_0082824_(param_1,0x46);
    }
  }
  return;
}



// ==== 80073558  zz_0073558_ ====

void zz_0073558_(int param_1)

{
  (*(code *)(&PTR_zz_0073594__802d4360)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80073594  zz_0073594_ ====

void zz_0073594_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 800735c4  zz_00735c4_ ====

void zz_00735c4_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 800735f4  zz_00735f4_ ====

void zz_00735f4_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}



// ==== 80073624  zz_0073624_ ====

void zz_0073624_(int param_1)

{
  zz_01618ac_(param_1);
  return;
}



// ==== 80073648  zz_0073648_ ====

void zz_0073648_(int param_1)

{
  zz_0073668_(param_1);
  return;
}



// ==== 80073668  zz_0073668_ ====

void zz_0073668_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  (*(code *)(&PTR_zz_00736bc__802d4374)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800736bc  zz_00736bc_ ====

void zz_00736bc_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437798;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804377a0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00679d0_(param_1);
  if (((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) && (iVar2 != 0)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
  }
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_004beb8_((double)FLOAT_80437780,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80437798;
  return;
}



// ==== 800737d8  FUN_800737d8 ====

/* WARNING: Removing unreachable block (ram,0x80073a1c) */
/* WARNING: Removing unreachable block (ram,0x800737e8) */

void FUN_800737d8(int param_1)

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
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804377a0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cf0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    fVar2 = FLOAT_804377b4;
    fVar1 = FLOAT_804377a8;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(float *)(param_1 + 0x44) = FLOAT_804377b0;
      *(float *)(param_1 + 0x4c) = fVar2;
      if (*(char *)(param_1 + 0x1db) == '\0') {
        *(float *)(param_1 + 0x48) = FLOAT_804377ac;
      }
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    else {
      *(float *)(param_1 + 0x44) = FLOAT_804377a4;
      fVar2 = FLOAT_804377ac;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      iVar3 = zz_00853ec_(param_1,0);
      local_28 = *(float *)(param_1 + 0xa24);
      dVar5 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_80437798;
      dVar6 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar5,dVar6);
      *(short *)(param_1 + 0x1900) = (short)iVar4 - (short)iVar3;
      iVar3 = zz_00853ec_(param_1,1);
      local_28 = *(float *)(param_1 + 0xae4);
      dVar6 = (double)*(float *)(param_1 + 0xaf4);
      local_20 = *(undefined4 *)(param_1 + 0xb04);
      local_24 = FLOAT_80437798;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar6,dVar5);
      *(short *)(param_1 + 0x1918) = (short)iVar3 + (short)iVar4;
    }
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      if (*(short *)(param_1 + 1000) == 0x100) {
        zz_0084600_(param_1,0);
        zz_0084600_(param_1,1);
      }
      else if (*(short *)(param_1 + 1000) == 0x108) {
        zz_0084600_(param_1,0xd);
        zz_0084600_(param_1,0xe);
      }
    }
  }
  dVar5 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804377b8 < dVar5) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80073a3c  FUN_80073a3c ====

void FUN_80073a3c(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80437788) * FLOAT_804377bc);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043779c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
LAB_80073acc:
    if (*(char *)(param_1 + 0x1cee) == '\0') goto LAB_80073b40;
  }
  else if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_006ed8c_((double)FLOAT_804377c0,param_1);
    goto LAB_80073acc;
  }
  *(undefined2 *)(param_1 + 0x1900) = 0;
  *(undefined2 *)(param_1 + 0x1918) = 0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_1 + 0x6e8) = 0;
  if (iVar1 == 0) {
    zz_006a5a4_(param_1);
  }
  else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a750_(param_1,7);
  }
  *(float *)(param_1 + 0x694) = FLOAT_8043779c + *(float *)(param_1 + 0x1dc8);
LAB_80073b40:
  if (FLOAT_804377b8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80073c90  FUN_80073c90 ====

void FUN_80073c90(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x582) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x200) {
    zz_004e00c_(param_1,0);
  }
  else if (sVar1 == 0x20a) {
    zz_004e00c_(param_1,1);
  }
  else if (sVar1 == 0x20f) {
    zz_004e00c_(param_1,3);
  }
  return;
}



// ==== 80073d0c  FUN_80073d0c ====

void FUN_80073d0c(int param_1)

{
  if (*(char *)(param_1 + 0x144) == '\0') {
    *(undefined1 *)(param_1 + 0x582) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x582) = 1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x18dc) = 0;
  }
  if ((*(char *)(param_1 + 0x144) == '\0') && (*(short *)(param_1 + 0x784) < 1)) {
    zz_006de10_(param_1,2);
  }
  return;
}



// ==== 80073da4  FUN_80073da4 ====

void FUN_80073da4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802d47f8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80073de4  FUN_80073de4 ====

void FUN_80073de4(int param_1,int param_2)

{
  if (*(short *)(param_1 + 1000) == 0x200) {
    zz_0099e70_(param_1,(&DAT_802d4810)[param_2 * 2]);
  }
  else if ((*(short *)(param_1 + 1000) == 0x20f) && ('\b' < *(char *)(param_1 + 0x3ee))) {
    zz_0099e70_(param_1,(&DAT_802d4811)[param_2 * 2]);
  }
  return;
}



// ==== 80073e5c  FUN_80073e5c ====

void FUN_80073e5c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x200) {
    zz_0137540_(param_1,0);
  }
  return;
}



// ==== 80073e8c  FUN_80073e8c ====

void FUN_80073e8c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x200) {
    zz_001ab6c_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x20a) {
    zz_001ab6c_(param_1,2);
  }
  return;
}



// ==== 80073ee4  FUN_80073ee4 ====

void FUN_80073ee4(int param_1)

{
  if (*(char *)(param_1 + 0x144) == '\0') {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x200) {
      zz_001ab6c_(param_1,0x46);
    }
    else if (*(short *)(param_1 + 1000) == 0x20a) {
      zz_001ab6c_(param_1,0x5d);
    }
  }
  return;
}



// ==== 80073f3c  FUN_80073f3c ====

void FUN_80073f3c(int param_1)

{
  (*(code *)(&PTR_FUN_802d4820)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80073f78  FUN_80073f78 ====

void FUN_80073f78(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802d4830)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80073fc0  FUN_80073fc0 ====

void FUN_80073fc0(int param_1)

{
  (*(code *)(&PTR_FUN_80433880)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80073ff8  FUN_80073ff8 ====

void FUN_80073ff8(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804377c8;
  dVar2 = (double)FLOAT_804377cc;
  *(float *)(param_1 + 0x50) = FLOAT_804377c8;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_0074068_(param_1);
  return;
}



// ==== 80074068  zz_0074068_ ====

void zz_0074068_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  zz_006660c_(param_1);
  zz_007486c_(param_1,0x81);
  return;
}



// ==== 800740c4  zz_00740c4_ ====

void zz_00740c4_(int param_1)

{
  short sVar1;
  double dVar2;
  int iVar3;
  char *pcVar4;
  
  zz_006660c_(param_1);
  zz_007486c_(param_1,0x81);
  zz_004cd24_(param_1,0xf);
  *(undefined2 *)(param_1 + 0x18dc) = 0;
  dVar2 = DOUBLE_804377e0;
  if ('\0' < *(char *)(param_1 + 0x1cf0)) {
    *(undefined2 *)(param_1 + 0x18dc) = *(undefined2 *)(param_1 + 0x548);
    *(short *)(param_1 + 0x548) =
         (short)(int)-(FLOAT_804377d0 * *(float *)(param_1 + 0x1dc8) -
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x548) ^ 0x80000000) -
                             dVar2));
  }
  zz_0067458_((double)FLOAT_804377d4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  pcVar4 = (char *)(param_1 + 0x144);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    if (*pcVar4 == '\0') {
      *pcVar4 = '\x01';
      *(undefined1 *)(param_1 + 0x1cef) = 0;
    }
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    if (*pcVar4 < '\x02') {
      iVar3 = zz_006dbe0_(param_1,2,1,1);
      if (iVar3 == 0) {
        *pcVar4 = '\0';
      }
      else {
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        sVar1 = *(short *)(param_1 + 1000);
        if (sVar1 == 0x200) {
          zz_007e700_(param_1,0);
        }
        else if (sVar1 == 0x20a) {
          zz_007e700_(param_1,1);
        }
        else if (sVar1 == 0x20f) {
          zz_00e0e90_(param_1,6,3,pcVar4);
          zz_00f036c_(param_1,0xdb);
        }
        *pcVar4 = '\x02';
      }
    }
  }
  if ((*(char *)(param_1 + 0x1cee) != '\0') || (*(char *)(param_1 + 0x1cf0) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    if (*(char *)(param_1 + 0x5e4) == ',') {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_804377d8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800742bc  zz_00742bc_ ====

void zz_00742bc_(int param_1)

{
  (*(code *)(&PTR_zz_00742f4__80433888)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800742f4  zz_00742f4_ ====

void zz_00742f4_(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804377c8;
  dVar2 = (double)FLOAT_804377cc;
  *(float *)(param_1 + 0x50) = FLOAT_804377c8;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_0074068_(param_1);
  return;
}



// ==== 8007434c  zz_007434c_ ====

void zz_007434c_(int param_1)

{
  (*(code *)(&PTR_zz_0074384__80433890)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80074384  zz_0074384_ ====

void zz_0074384_(int param_1)

{
  zz_004beb8_((double)FLOAT_804377cc,param_1,0xf,2,2,0xffffffff,0xffffffff);
  zz_0074068_(param_1);
  return;
}



// ==== 800743d0  zz_00743d0_ ====

void zz_00743d0_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_zz_0074424__802d4844)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80074424  zz_0074424_ ====

void zz_0074424_(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 80074448  zz_0074448_ ====

void zz_0074448_(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}



// ==== 8007446c  zz_007446c_ ====

void zz_007446c_(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}



// ==== 80074490  zz_0074490_ ====

void zz_0074490_(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 800744b4  zz_00744b4_ ====

void zz_00744b4_(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_zz_00744fc__802d4858)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800744fc  zz_00744fc_ ====

void zz_00744fc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_007454c__802d486c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007454c  zz_007454c_ ====

void zz_007454c_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804377e8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar1 = FLOAT_804377c8;
  *(float *)(param_1 + 0x50) = FLOAT_804377c8;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804377ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_804377cc,param_1,0xf,4,(uint)((*(uint *)(param_1 + 0x5e0) & 0x40) != 0),
              0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804377c8;
  return;
}



// ==== 80074634  zz_0074634_ ====

void zz_0074634_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804377ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_804377c8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800746ec  zz_00746ec_ ====

void zz_00746ec_(int param_1)

{
  double dVar1;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_804377ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_804377f0 < dVar1) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 800747a4  zz_00747a4_ ====

void zz_00747a4_(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804377d4;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_804377e0) * FLOAT_804377f4);
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
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
  return;
}



// ==== 8007486c  zz_007486c_ ====

undefined4 zz_007486c_(int param_1,uint param_2)

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
                                                0x80000000) - DOUBLE_804377e0) *
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



// ==== 80074a3c  FUN_80074a3c ====

void FUN_80074a3c(int param_1)

{
  short sVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x147) = 0;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x40a) {
    iVar2 = 4;
    do {
      zz_00c0d0c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 8);
  }
  else if ((sVar1 < 0x40a) && (sVar1 == 0x400)) {
    iVar2 = 0;
    do {
      zz_00c0d0c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
  }
  zz_00c74ec_(param_1,10);
  return;
}



// ==== 80074ae8  FUN_80074ae8 ====

void FUN_80074ae8(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(short *)(param_1 + 0x78e) <= *(short *)(param_1 + 0x774)) {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined1 *)(param_1 + 0x147) = 0;
    *(undefined1 *)(param_1 + 0x148) = 0;
  }
  dVar2 = DOUBLE_80437800;
  fVar1 = FLOAT_804377f8;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80437800) * FLOAT_804377f8);
    *(short *)(param_1 + 0x18e0) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 80074bcc  FUN_80074bcc ====

void FUN_80074bcc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802d4e78)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80074c0c  FUN_80074c0c ====

void FUN_80074c0c(int param_1,uint param_2)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  
  *(undefined1 *)(param_1 + 0xaf) = 1;
  puVar1 = &DAT_802d4e84;
  if (*(short *)(param_1 + 1000) == 0x40a) {
    puVar1 = &DAT_802d4e90;
  }
  else if (*(short *)(param_1 + 1000) != 0x400) {
    return;
  }
  if ((param_2 & 1) != 0) {
    iVar2 = 0;
    puVar3 = puVar1;
    do {
      zz_001ab6c_(param_1,(char)*puVar3);
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < 3);
  }
  if ((param_2 & 2) != 0) {
    iVar2 = 3;
    puVar1 = puVar1 + 3;
    do {
      zz_001ab6c_(param_1,(char)*puVar1);
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 < 6);
  }
  return;
}



// ==== 80074ccc  FUN_80074ccc ====

void FUN_80074ccc(int param_1)

{
  (*(code *)(&PTR_FUN_802d4e9c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80074d08  FUN_80074d08 ====

void FUN_80074d08(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00f1e30_(param_1,&DAT_802d4ea8);
  return;
}



// ==== 80074d3c  FUN_80074d3c ====

void FUN_80074d3c(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x400) {
      zz_007f29c_(param_1,*(undefined1 *)(param_1 + 0x148),0);
    }
    else if (*(short *)(param_1 + 1000) == 0x40a) {
      zz_007f29c_(param_1,*(char *)(param_1 + 0x148) + '\x04',1);
    }
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x148) + 0x144) = 1;
    *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
  }
  return;
}



// ==== 80074de0  FUN_80074de0 ====

undefined4 FUN_80074de0(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 80074e48  FUN_80074e48 ====

void FUN_80074e48(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802d4ebc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80074ea8  FUN_80074ea8 ====

void FUN_80074ea8(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 80074ecc  FUN_80074ecc ====

void FUN_80074ecc(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 80074ef0  FUN_80074ef0 ====

void FUN_80074ef0(int param_1)

{
  zz_00f3028_(param_1);
  return;
}



// ==== 80074f14  FUN_80074f14 ====

void FUN_80074f14(int param_1)

{
  zz_00f3738_(param_1);
  return;
}



// ==== 80074f38  FUN_80074f38 ====

void FUN_80074f38(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437800;
  fVar1 = FLOAT_804377f8;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80437800) * FLOAT_804377f8);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  zz_00f41c4_(param_1);
  return;
}



// ==== 80074fc0  zz_0074fc0_ ====

void zz_0074fc0_(int param_1)

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
    zz_00e48cc_(param_1,-0x7fd2ad18,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80075038  zz_0075038_ ====

void zz_0075038_(int param_1)

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
      FUN_800e4a18((double)FLOAT_80437808,param_1,(float *)&DAT_802d52e8,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd2ad18,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 800750cc  zz_00750cc_ ====

void zz_00750cc_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80075104  zz_0075104_ ====

void zz_0075104_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd2ad18,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fd2ad18,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 800751a4  zz_00751a4_ ====

void zz_00751a4_(int param_1)

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
    zz_00e48cc_(param_1,-0x7fd2ac28,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 8007521c  zz_007521c_ ====

void zz_007521c_(int param_1)

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
      FUN_800e4a18((double)FLOAT_8043780c,param_1,(float *)&DAT_802d53d8,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd2ac28,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 800752b0  zz_00752b0_ ====

void zz_00752b0_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 800752e8  zz_00752e8_ ====

void zz_00752e8_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd2ac28,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fd2ac28,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80075388  zz_0075388_ ====

/* WARNING: Removing unreachable block (ram,0x80075634) */
/* WARNING: Removing unreachable block (ram,0x80075398) */

void zz_0075388_(int param_1,short *param_2)

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
  dVar6 = DOUBLE_80437818;
  fVar1 = FLOAT_80437810;
  uStack_3c = (int)*param_2 ^ 0x80000000;
  local_40 = 0x43300000;
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  local_30 = 0x43300000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80437818) * FLOAT_80437810);
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
    local_48 = FLOAT_80437814;
    dVar7 = gnt4_PSVECMag_bl(&local_4c);
    iVar3 = FUN_800452a0(dVar6,dVar7);
    local_58 = *(float *)(param_1 + 0xb20);
    local_54 = *(float *)(param_1 + 0xb30);
    local_50 = *(undefined4 *)(param_1 + 0xb40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x50c),&local_58,&local_58);
    dVar7 = (double)local_54;
    local_54 = FLOAT_80437814;
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



// ==== 8007578c  FUN_8007578c ====

void FUN_8007578c(int param_1)

{
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x500:
  case 0x509:
  case 0x50a:
    zz_0074fc0_(param_1);
    break;
  case 0x50c:
  case 0x515:
  case 0x516:
    zz_00751a4_(param_1);
  }
  return;
}



// ==== 800757f4  FUN_800757f4 ====

void FUN_800757f4(int param_1)

{
  zz_0046698_(param_1);
  zz_0075388_(param_1,(short *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) != 0) {
    *(undefined1 *)(param_1 + 0x7de) = 1;
  }
  return;
}



// ==== 80075840  FUN_80075840 ====

void FUN_80075840(int param_1)

{
  zz_0075388_(param_1,(short *)(param_1 + 0x144));
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x500:
  case 0x509:
  case 0x50a:
    zz_0075038_(param_1);
    break;
  case 0x50c:
  case 0x515:
  case 0x516:
    zz_007521c_(param_1);
  }
  return;
}



// ==== 800758b8  FUN_800758b8 ====

void FUN_800758b8(int param_1)

{
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x500:
  case 0x509:
  case 0x50a:
    zz_00750cc_(param_1);
    break;
  case 0x50c:
  case 0x515:
  case 0x516:
    zz_00752b0_(param_1);
  }
  return;
}



// ==== 80075908  FUN_80075908 ====

void FUN_80075908(int param_1)

{
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x500:
  case 0x509:
  case 0x50a:
    zz_0075104_(param_1);
    break;
  case 0x50c:
  case 0x515:
  case 0x516:
    zz_00752e8_(param_1);
  }
  return;
}



// ==== 80075958  FUN_80075958 ====

void FUN_80075958(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80433898)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80075994  FUN_80075994 ====

uint FUN_80075994(uint param_1)

{
  bool bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  
  uVar3 = 0x17;
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar3 = 0x1a;
  }
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x500:
    uVar2 = 0;
    break;
  case 0x501:
  case 0x502:
  case 0x503:
  case 0x504:
  case 0x505:
  case 0x506:
  case 0x507:
  case 0x508:
  case 0x50b:
  case 0x50d:
  case 0x50e:
  case 0x50f:
  case 0x510:
  case 0x511:
  case 0x512:
  case 0x513:
  case 0x514:
    return param_1;
  case 0x509:
    bVar1 = zz_0183730_(param_1,2,uVar3);
    return (uint)bVar1;
  case 0x50a:
    uVar2 = 4;
    break;
  case 0x50c:
    uVar2 = 5;
    break;
  case 0x515:
    bVar1 = zz_0183730_(param_1,3,uVar3);
    return (uint)bVar1;
  case 0x516:
    uVar2 = 7;
    break;
  default:
    goto switchD_800759d8_default;
  }
  param_1 = zz_01ef2b4_(param_1,uVar2,uVar3);
switchD_800759d8_default:
  return param_1;
}



// ==== 80075a2c  FUN_80075a2c ====

void FUN_80075a2c(int param_1)

{
  (*(code *)(&PTR_FUN_802d56d4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80075a68  FUN_80075a68 ====

void FUN_80075a68(int param_1)

{
  (*(code *)(&PTR_FUN_802d56e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80075aa4  FUN_80075aa4 ====

void FUN_80075aa4(int param_1)

{
  (*(code *)(&PTR_FUN_802d56ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80075ae0  FUN_80075ae0 ====

void FUN_80075ae0(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80437820;
  fVar1 = FLOAT_80437814;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc1);
  zz_004beb8_((double)FLOAT_80437824,param_1,0xf,0,0x2a,10,2);
  return;
}



// ==== 80075b68  FUN_80075b68 ====

void FUN_80075b68(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80437814;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80075bf8  FUN_80075bf8 ====

void FUN_80075bf8(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined1 uVar2;
  
  zz_004cd24_(param_9,0xf);
  if ('\0' < *(char *)(param_9 + 0x1cef)) {
    *(undefined1 *)(param_9 + 0x1cef) = 0;
    param_11 = 1;
    param_12 = 1;
    iVar1 = zz_006dbe0_(param_9,0,1,1);
    if (iVar1 != 0) {
      *(undefined1 *)(param_9 + 0x587) = 0;
      switch(*(undefined2 *)(param_9 + 1000)) {
      default:
        uVar2 = 0;
        break;
      case 0x509:
        uVar2 = 1;
        break;
      case 0x50a:
        uVar2 = 2;
        break;
      case 0x50c:
        uVar2 = 3;
        break;
      case 0x515:
        uVar2 = 4;
        break;
      case 0x516:
        uVar2 = 5;
      }
      param_1 = (double)zz_00be948_(param_9,uVar2);
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
      zz_006a750_(param_9,0x10);
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80075d20  FUN_80075d20 ====

void FUN_80075d20(int param_1)

{
  (*(code *)(&PTR_FUN_802d5754)[*(char *)(param_1 + 0x540)])();
  zz_006ed8c_((double)FLOAT_80437828,param_1);
  zz_0067458_((double)FLOAT_8043782c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80075d8c  FUN_80075d8c ====

void FUN_80075d8c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80437820;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d144_(param_1,0x81);
  zz_004beb8_((double)FLOAT_80437824,param_1,0xf,0,0xf,10,2);
  return;
}



// ==== 80075df0  FUN_80075df0 ====

void FUN_80075df0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80437814;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0x81), iVar3 != 0)) {
    dVar4 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,3,2,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80075e80  FUN_80075e80 ====

void FUN_80075e80(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80075eb4  FUN_80075eb4 ====

void FUN_80075eb4(int param_1)

{
  (*(code *)(&PTR_FUN_802d5760)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80075ef0  FUN_80075ef0 ====

void FUN_80075ef0(int param_1)

{
  (*(code *)(&PTR_FUN_802d576c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80075f2c  FUN_80075f2c ====

void FUN_80075f2c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80437830;
  fVar1 = FLOAT_80437814;
  dVar3 = (double)FLOAT_80437824;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = 0x78;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar3,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}



// ==== 80075fa4  FUN_80075fa4 ====

void FUN_80075fa4(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_0076408_(param_1);
  zz_0066e40_(param_1,0);
  fVar2 = FLOAT_80437814;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    dVar3 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80076028  FUN_80076028 ====

void FUN_80076028(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80076088  FUN_80076088 ====

void FUN_80076088(int param_1)

{
  (*(code *)(&PTR_FUN_802d5778)[*(char *)(param_1 + 0x540)])();
  zz_006ed8c_((double)FLOAT_80437834,param_1);
  zz_0067458_((double)FLOAT_8043782c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800760f4  FUN_800760f4 ====

void FUN_800760f4(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437830;
  dVar2 = (double)FLOAT_80437824;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0x78;
  zz_004beb8_(dVar2,param_1,0xf,4,2,0xffffffff,0xffffffff);
  return;
}



// ==== 80076148  FUN_80076148 ====

void FUN_80076148(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_0076408_(param_1);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  fVar2 = FLOAT_80437814;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    dVar3 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,4,3,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800761e4  FUN_800761e4 ====

void FUN_800761e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80076244  FUN_80076244 ====

void FUN_80076244(int param_1)

{
  (*(code *)(&PTR_FUN_802d5784)[*(char *)(param_1 + 0x540)])();
  FUN_80067310((double)FLOAT_8043782c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800762a4  FUN_800762a4 ====

void FUN_800762a4(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437830;
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    dVar2 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x54a) = 0x78;
    zz_004beb8_(dVar2,param_1,7,4,4,0xffffffff,0xffffffff);
  }
  else {
    zz_006a3d0_(param_1,'\x02',3,0);
  }
  return;
}



// ==== 80076318  FUN_80076318 ====

void FUN_80076318(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_0076408_(param_1);
  zz_0066e40_(param_1,2);
  fVar2 = FLOAT_80437814;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    dVar3 = (double)FLOAT_80437824;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,3,4,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800763a4  FUN_800763a4 ====

void FUN_800763a4(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,0x10);
  }
  return;
}



// ==== 80076408  zz_0076408_ ====

void zz_0076408_(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x1cef);
  if (cVar1 != '\0') {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    switch(*(undefined2 *)(param_1 + 1000)) {
    default:
      uVar4 = 0;
      break;
    case 0x509:
      uVar4 = 1;
      break;
    case 0x50a:
      uVar4 = 2;
      break;
    case 0x50c:
      uVar4 = 3;
      break;
    case 0x515:
      uVar4 = 4;
      break;
    case 0x516:
      uVar4 = 5;
    }
    if (cVar1 < '\0') {
      zz_0098dbc_(param_1,4,uVar4);
    }
    else {
      iVar2 = zz_006dbe0_(param_1,2,1,1);
      if (iVar2 != 0) {
        zz_0098dbc_(param_1,0,uVar4);
        zz_0098dbc_(param_1,3,uVar4);
      }
    }
  }
  zz_0066ac0_(param_1,0);
  if (0 < *(short *)(param_1 + 0x54a)) {
    uVar3 = zz_0076558_(param_1,(short *)(param_1 + 0x54a));
    *(float *)(param_1 + 0x558) =
         *(float *)(param_1 + 0x558) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_80437818);
  }
  return;
}



// ==== 80076558  zz_0076558_ ====

void zz_0076558_(int param_1,short *param_2)

{
  int iVar1;
  
  iVar1 = zz_006de44_(param_1,0xf0f00);
  if (*param_2 < iVar1) {
    iVar1 = (int)*param_2;
  }
  *param_2 = *param_2 - (short)iVar1;
  return;
}



// ==== 800765a8  zz_00765a8_ ====

void zz_00765a8_(int param_1)

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
    zz_00e3758_(param_1,-0x7fd2a218,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80076620  zz_0076620_ ====

void zz_0076620_(int param_1)

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
      zz_00e38a4_(param_1,(float *)&DAT_802d5de8,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd2a218,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 800766ac  zz_00766ac_ ====

void zz_00766ac_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 800766e4  zz_00766e4_ ====

void zz_00766e4_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd2a218,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fd2a218,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80076880  FUN_80076880 ====

void FUN_80076880(int param_1)

{
  char cVar1;
  
  zz_00765a8_(param_1);
  for (cVar1 = '\0'; cVar1 < '\x02'; cVar1 = cVar1 + '\x01') {
    zz_00bd918_(param_1,cVar1);
  }
  *(undefined1 *)(param_1 + 0x6eb) = 0;
  return;
}



// ==== 800768e4  FUN_800768e4 ====

void FUN_800768e4(int param_1)

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



// ==== 80076978  FUN_80076978 ====

void FUN_80076978(int param_1)

{
  zz_0076620_(param_1);
  return;
}



// ==== 800769b0  FUN_800769b0 ====

void FUN_800769b0(int param_1)

{
  zz_00766ac_(param_1);
  return;
}



// ==== 800769d0  FUN_800769d0 ====

void FUN_800769d0(int param_1)

{
  zz_00766e4_(param_1);
  return;
}



// ==== 800769f0  FUN_800769f0 ====

void FUN_800769f0(int param_1)

{
  (*(code *)(&PTR_FUN_802d5f18)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80076a2c  FUN_80076a2c ====

void FUN_80076a2c(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80437840) * FLOAT_80437838);
  (*(code *)(&PTR_FUN_802d5f24)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80076aa0  FUN_80076aa0 ====

void FUN_80076aa0(int param_1)

{
  (*(code *)(&PTR_FUN_804338a0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80076ad8  FUN_80076ad8 ====

void FUN_80076ad8(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437848;
  dVar2 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x50) = FLOAT_80437848;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_0076c80_(param_1);
  return;
}



// ==== 80076b48  FUN_80076b48 ====

void FUN_80076b48(int param_1)

{
  char cVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006660c_(param_1);
  zz_007933c_(param_1,0x81);
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
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
        zz_0082824_(param_1,0xc);
      }
      *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
    }
  }
  else if ((cVar1 < '\x03') && (*(char *)(param_1 + 0x1cee) != '\0')) {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80076c80  zz_0076c80_ ====

void zz_0076c80_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  zz_006660c_(param_1);
  zz_007933c_(param_1,0x81);
  return;
}



// ==== 80076cd4  FUN_80076cd4 ====

void FUN_80076cd4(int param_1)

{
  (*(code *)(&PTR_FUN_804338a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80076d0c  FUN_80076d0c ====

void FUN_80076d0c(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437848;
  dVar2 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x50) = FLOAT_80437848;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_0076c80_(param_1);
  return;
}



// ==== 80076d64  FUN_80076d64 ====

void FUN_80076d64(int param_1)

{
  (*(code *)(&PTR_FUN_804338b0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80076d9c  FUN_80076d9c ====

void FUN_80076d9c(int param_1)

{
  zz_004beb8_((double)FLOAT_8043784c,param_1,0xf,2,2,0xffffffff,0xffffffff);
  zz_0076c80_(param_1);
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80076e00  FUN_80076e00 ====

void FUN_80076e00(int param_1)

{
  char cVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006660c_(param_1);
  zz_007933c_(param_1,0x81);
  FUN_80067310((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
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
          zz_0082824_(param_1,0xc);
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



// ==== 80076f78  FUN_80076f78 ====

void FUN_80076f78(int param_1)

{
  (*(code *)(&PTR_FUN_804338b8)[*(char *)(param_1 + 0x540)])();
  return;
}



