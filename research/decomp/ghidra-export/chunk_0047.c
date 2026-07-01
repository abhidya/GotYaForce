// ==== 8018d6f0  FUN_8018d6f0 ====

void FUN_8018d6f0(int param_1)

{
  (*(code *)(&PTR_FUN_803655bc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8018d72c  FUN_8018d72c ====

void FUN_8018d72c(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043b12c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  uVar2 = *(uint *)(param_1 + 0x5e0);
  iVar3 = 4;
  if ((uVar2 & 0x80) != 0) {
    iVar3 = 6;
  }
  if ((uVar2 & 0x10) != 0) {
    iVar3 = 2;
  }
  if (((uVar2 & 0x20) != 0) &&
     (iVar3 = *(char *)(param_1 + 0x1d10) + 8, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar3 = 0;
  }
  zz_004beb8_((double)FLOAT_8043b120,param_1,1,2,iVar3 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 8018d7e4  FUN_8018d7e4 ====

void FUN_8018d7e4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_8043b110;
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
      zz_018dcb0_(param_1);
    }
  }
  return;
}



// ==== 8018d8c0  FUN_8018d8c0 ====

void FUN_8018d8c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
    *(undefined1 *)(param_9 + 0x745) = 1;
  }
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_8043b110) {
    if (*(char *)(param_9 + 0x745) != '\0') {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(undefined1 *)(param_9 + 0x745) = 0;
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((uVar2 & 0x10) == 0) {
            if ((uVar2 & 0x20) == 0) {
              zz_006a3d0_(param_9,'\0',0,2);
              return;
            }
            *(undefined1 *)(param_9 + 0x581) = 2;
            iVar1 = *(char *)(param_9 + 0x1d10) + 9;
            if (*(char *)(param_9 + 0x5db) == '\x0f') {
              iVar1 = 1;
            }
          }
          else {
            iVar1 = 3;
            *(undefined1 *)(param_9 + 0x581) = 1;
          }
        }
        else {
          iVar1 = 5;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 7;
          }
        }
        if ((*(char *)(param_9 + 0x1cef) < '\0') &&
           (iVar1 == (int)*(char *)(param_9 + 0x1afd) + *(char *)(param_9 + 0x1afc) * 0x1000)) {
          zz_004beb8_((double)FLOAT_8043b120,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_8043b120,param_9,1,2,iVar1,4,1);
        return;
      }
      goto LAB_8018da7c;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_8018da7c:
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8018dab4  FUN_8018dab4 ====

void FUN_8018dab4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803655c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8018dafc  FUN_8018dafc ====

void FUN_8018dafc(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b11c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_8043b130,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b120,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  zz_004beb8_((double)FLOAT_8043b120,param_1,2,0,0xd,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b110;
  return;
}



// ==== 8018dbb4  FUN_8018dbb4 ====

/* WARNING: Removing unreachable block (ram,0x8018dc94) */
/* WARNING: Removing unreachable block (ram,0x8018dbc4) */

void FUN_8018dbb4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043b110;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_8043b130,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043b110;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (((fVar1 <= fVar2) || (iVar3 = zz_006d0dc_(param_1,0x81,0), iVar3 != 0)) &&
     (*(char *)(param_1 + 0x1cef) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_018dcb0_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  if (FLOAT_8043b128 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8018dcb0  zz_018dcb0_ ====

void zz_018dcb0_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b134;
  *(float *)(param_1 + 0x560) = FLOAT_8043b12c;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(float *)(param_1 + 0x558) = fVar2;
  if (*(short *)(param_1 + 1000) == 0x629) {
    *(float *)(param_1 + 0x558) = FLOAT_8043b138;
  }
  else if (*(short *)(param_1 + 1000) == 0x62a) {
    *(float *)(param_1 + 0x558) = FLOAT_8043b13c;
  }
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x615) {
      zz_00c3be0_(param_1,0x2b);
    }
    else if (sVar1 == 0x629) {
      zz_00c3be0_(param_1,0x65);
    }
    else if (sVar1 == 0x62a) {
      zz_00c3be0_(param_1,0x66);
    }
    *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  }
  if (*(short *)(param_1 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x6ef) = 0;
  }
  return;
}



// ==== 8018dd9c  FUN_8018dd9c ====

void FUN_8018dd9c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x615) {
    (*(code *)(&PTR_FUN_803655d4)[*(char *)(param_1 + 0x581)])();
  }
  else if (*(short *)(param_1 + 1000) == 0x62a) {
    (*(code *)(&PTR_FUN_803655f4)[*(char *)(param_1 + 0x581)])();
  }
  else {
    (*(code *)(&PTR_FUN_80365614)[*(char *)(param_1 + 0x581)])();
  }
  return;
}



// ==== 8018de34  FUN_8018de34 ====

void FUN_8018de34(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018de68  FUN_8018de68 ====

void FUN_8018de68(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018de9c  FUN_8018de9c ====

void FUN_8018de9c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018ded0  FUN_8018ded0 ====

void FUN_8018ded0(int param_1)

{
  zz_006a3d0_(param_1,'\x01',1,0);
  *(undefined1 *)(param_1 + 0x581) = 6;
  return;
}



// ==== 8018df10  FUN_8018df10 ====

void FUN_8018df10(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0179280_(param_1);
  return;
}



// ==== 8018df44  FUN_8018df44 ====

void FUN_8018df44(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018df78  FUN_8018df78 ====

void FUN_8018df78(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0179280_(param_1);
  return;
}



// ==== 8018dfac  FUN_8018dfac ====

void FUN_8018dfac(int param_1)

{
  zz_006a3d0_(param_1,'\x01',2,0);
  *(undefined1 *)(param_1 + 0x581) = 7;
  return;
}



// ==== 8018dfec  FUN_8018dfec ====

void FUN_8018dfec(int param_1)

{
  if ((*(char *)(param_1 + 0x540) == '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x2000) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 5;
    zz_018e290_(param_1);
  }
  else {
    zz_0178b6c_(param_1);
  }
  return;
}



// ==== 8018e03c  FUN_8018e03c ====

void FUN_8018e03c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar3 = FLOAT_8043b140;
  fVar1 = FLOAT_8043b110;
  *(float *)(param_1 + 0x38) = FLOAT_8043b110;
  fVar2 = FLOAT_8043b11c;
  *(float *)(param_1 + 0x44) = fVar3;
  fVar3 = FLOAT_8043b144;
  *(float *)(param_1 + 0x4c) = fVar1;
  dVar4 = (double)FLOAT_8043b120;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar3;
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  zz_004beb8_(dVar4,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8018e0a8  FUN_8018e0a8 ====

void FUN_8018e0a8(int param_1)

{
  if ((*(char *)(param_1 + 0x540) == '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x2000) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 5;
    zz_018e290_(param_1);
  }
  else {
    zz_0178394_(param_1);
  }
  return;
}



// ==== 8018e0f8  FUN_8018e0f8 ====

void FUN_8018e0f8(int param_1)

{
  if ((*(char *)(param_1 + 0x540) == '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x2000) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 5;
    zz_018e290_(param_1);
  }
  else {
    zz_0178394_(param_1);
  }
  return;
}



// ==== 8018e148  FUN_8018e148 ====

void FUN_8018e148(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 8018e170  FUN_8018e170 ====

void FUN_8018e170(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 8018e198  FUN_8018e198 ====

void FUN_8018e198(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 8018e1c0  FUN_8018e1c0 ====

void FUN_8018e1c0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0179280_(param_1);
  return;
}



// ==== 8018e1f4  FUN_8018e1f4 ====

void FUN_8018e1f4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0179280_(param_1);
  return;
}



// ==== 8018e228  FUN_8018e228 ====

void FUN_8018e228(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018e25c  FUN_8018e25c ====

void FUN_8018e25c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018e290  zz_018e290_ ====

void zz_018e290_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80365820)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8018e2ec  FUN_8018e2ec ====

void FUN_8018e2ec(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043b148;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  if (*(short *)(param_1 + 1000) == 0x62a) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x14;
  }
  if (*(short *)(param_1 + 1000) == 0x629) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x24;
  }
  fVar2 = FLOAT_8043b110;
  *(float *)(param_1 + 0x50) = FLOAT_8043b110;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043b120;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8018e478  FUN_8018e478 ====

void FUN_8018e478(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043b110;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043b12c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8018e540  FUN_8018e540 ====

void FUN_8018e540(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b14c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043b130;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b14c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043b110;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043b150,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043b154;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar1;
  }
  return;
}



// ==== 8018e650  FUN_8018e650 ====

void FUN_8018e650(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b12c;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    dVar4 = (double)FLOAT_8043b120;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043b124,param_1);
  FUN_80067310((double)FLOAT_8043b130,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043b130 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8018e7fc  FUN_8018e7fc ====

void FUN_8018e7fc(int param_1)

{
  (*(code *)(&PTR_FUN_80365830)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8018e838  FUN_8018e838 ====

void FUN_8018e838(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80365844)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8018e888  FUN_8018e888 ====

void FUN_8018e888(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  double dVar6;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar5 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar5 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0xa0) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  zz_006d144_(param_1,0xc1);
  fVar3 = FLOAT_8043b110;
  sVar2 = *(short *)(param_1 + 1000);
  if (sVar2 == 0x629) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
    *(float *)(param_1 + 0x50) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x44) = fVar3;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
  }
  else if ((sVar2 < 0x629) || (0x62a < sVar2)) {
    *(undefined1 *)(param_1 + 0x6ea) = 0;
    fVar4 = FLOAT_8043b158;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x48) = fVar4;
    *(float *)(param_1 + 0x50) = fVar3;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ea) = 4;
    *(float *)(param_1 + 0x50) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x44) = fVar3;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar6 = (double)FLOAT_8043b120;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8018ea54  FUN_8018ea54 ====

void FUN_8018ea54(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    zz_00107a0_(param_1,0x12);
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006e1ac_(param_1,0xc1,1);
  }
  FUN_80067310((double)FLOAT_8043b130,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_8043b15c;
  fVar1 = FLOAT_8043b110;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_8043b148;
    *(float *)(param_1 + 0x38) = fVar1;
    *(float *)(param_1 + 0x3c) = fVar3;
    *(float *)(param_1 + 0x40) = fVar2;
  }
  return;
}



// ==== 8018eb2c  FUN_8018eb2c ====

void FUN_8018eb2c(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x1d10) = 0;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc1);
    zz_006e1ac_(param_1,0xc1,1);
  }
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x3c) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x40) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x40);
  }
  dVar2 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar2);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar3 = (double)FLOAT_8043b130;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar2);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_8043b160;
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 8018ec34  FUN_8018ec34 ====

void FUN_8018ec34(int param_1)

{
  float fVar1;
  int iVar2;
  bool bVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  dVar4 = (double)FLOAT_8043b130;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b108) * FLOAT_8043b100);
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 0) {
    if (*(short *)(param_1 + 1000) == 0x615) {
      if (*(char *)(param_1 + 0x1cee) == '\0') {
        return;
      }
    }
    else {
      fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      bVar3 = FLOAT_8043b110 <= fVar1;
      *(float *)(param_1 + 0x558) = fVar1;
      if (bVar3) {
        return;
      }
    }
    *(undefined2 *)(param_1 + 0x6f6) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  else {
    *(undefined2 *)(param_1 + 0x6f6) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043b130 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8018ed4c  FUN_8018ed4c ====

void FUN_8018ed4c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x62a) {
    zz_018ee08_(param_1);
  }
  else {
    zz_018ed80_(param_1);
  }
  return;
}



// ==== 8018ed80  zz_018ed80_ ====

void zz_018ed80_(int param_1)

{
  zz_0179814_(param_1);
  return;
}



// ==== 8018edc4  FUN_8018edc4 ====

void FUN_8018edc4(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x62a) {
    zz_00e19a8_(param_1,0x11,param_1 + 0x6f7);
  }
  else {
    zz_00e19a8_(param_1,0xf,param_1 + 0x6f7);
  }
  return;
}



// ==== 8018ee08  zz_018ee08_ ====

void zz_018ee08_(int param_1)

{
  zz_0179d20_(param_1);
  return;
}



// ==== 8018ee30  FUN_8018ee30 ====

void FUN_8018ee30(int param_1)

{
  float fVar1;
  float fVar2;
  
  if (*(short *)(param_1 + 1000) == 0x62a) {
    zz_016cc24_(param_1,0x10);
  }
  fVar2 = FLOAT_8043b158;
  fVar1 = FLOAT_8043b110;
  *(float *)(param_1 + 0x4c) = FLOAT_8043b110;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  return;
}



// ==== 8018ee84  FUN_8018ee84 ====

void FUN_8018ee84(int param_1)

{
  zz_018ed80_(param_1);
  return;
}



// ==== 8018eea4  zz_018eea4_ ====

void zz_018eea4_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,1,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x37;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 2;
    *(code **)(puVar1 + 0xc) = FUN_8018efa4;
    *(code **)(puVar1 + 0x10c) = FUN_8018f504;
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



// ==== 8018efa4  FUN_8018efa4 ====

void FUN_8018efa4(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8036ec64)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8018eff4  FUN_8018eff4 ====

void FUN_8018eff4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  byte *pbVar8;
  undefined8 uVar9;
  
  fVar3 = FLOAT_8043b168;
  bVar1 = *(byte *)(param_9 + 0x11);
  iVar6 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)bVar1 * 0x14;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x44) = fVar3;
  pbVar8 = &DAT_8036ec50 + iVar5;
  *(short *)(param_9 + 0x70) = *(short *)(iVar6 + 0x70) + *(short *)(iVar6 + 0x18da);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(iVar6 + 0x72);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar6 + 0x74);
  uVar2 = *(undefined4 *)(iVar6 + 0xb4);
  *(undefined4 *)(param_9 + 0xc0) = uVar2;
  *(undefined4 *)(param_9 + 0xb4) = uVar2;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + (char)(&DAT_8036ec52)[iVar5] * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fc913ac),(float *)(param_9 + 0x20));
  *(undefined2 *)(param_9 + 0x154) = 0;
  *(undefined2 *)(param_9 + 0x156) = 10;
  zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_8036ec60)[(uint)bVar1 * 5],
              (float *)(param_9 + 0x58));
  *(code **)(param_9 + 0x100) = FUN_8018f3fc;
  uVar9 = zz_0089100_(param_9,1,1);
  iVar5 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(iVar5 + 0xe0),(float *)(uint)*pbVar8,(int)*(char *)(param_9 + 0x88),iVar6,
                in_r8,in_r9,in_r10);
    uVar9 = zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar5 + 0xe0));
    iVar5 = iVar5 + 4;
    pbVar8 = pbVar8 + 1;
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  return;
}



// ==== 8018f150  FUN_8018f150 ====

void FUN_8018f150(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  (*(code *)(&PTR_FUN_804356b0)[*(char *)(param_1 + 0x19)])();
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(char *)(param_1 + 0x13); iVar1 = iVar1 + 1) {
    zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(iVar2 + 0xe0));
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 8018f1e0  FUN_8018f1e0 ====

void FUN_8018f1e0(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x154) + 1;
  *(short *)(param_1 + 0x154) = sVar1;
  if (sVar1 < *(short *)(param_1 + 0x156)) {
    zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x154),(float *)(param_1 + 0x58))
    ;
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x154) = 0;
    *(undefined2 *)(param_1 + 0x156) = 0x3c;
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fc91400,(float *)(param_1 + 0x58));
    zz_0019338_((int *)(param_1 + 0x14c),-0x7fc913d0,(float *)(param_1 + 0x44));
  }
  return;
}



// ==== 8018f28c  FUN_8018f28c ====

void FUN_8018f28c(int param_1)

{
  short sVar1;
  int iVar2;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [13];
  
  sVar1 = *(short *)(param_1 + 0x154) + 1;
  *(short *)(param_1 + 0x154) = sVar1;
  if (sVar1 < *(short *)(param_1 + 0x156)) {
    zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x154),(float *)(param_1 + 0x58))
    ;
    zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x154),(float *)(param_1 + 0x44))
    ;
    iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x14;
    local_44 = FLOAT_8043b16c;
    local_48 = FLOAT_8043b16c;
    zz_00455fc_((float *)(param_1 + 0x114),afStack_3c,(float *)(iVar2 + -0x7fc913ac));
    zz_00456a0_(afStack_3c,afStack_3c,(float *)(param_1 + 0x58));
    local_40 = FLOAT_8043b16c;
    gnt4_PSMTXMultVec_bl(afStack_3c,&local_48,(float *)(param_1 + 0x38));
    local_40 = local_40 + FLOAT_8043b170;
    gnt4_PSMTXMultVec_bl(afStack_3c,&local_48,(float *)(param_1 + 0x9c));
    zz_0139a6c_(param_1,param_1 + 0x38,param_1 + 0x9c,(&DAT_8036ec53)[iVar2]);
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 8018f3b4  FUN_8018f3b4 ====

void FUN_8018f3b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8018f3fc  FUN_8018f3fc ====

void FUN_8018f3fc(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [16];
  
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),&local_58);
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  iVar2 = (int)*(short *)(param_1 + 0x70);
  zz_00457d4_('x',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70));
  pfVar1 = &local_58;
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),pfVar1);
  local_58 = FLOAT_8043b168;
  local_54 = FLOAT_8043b174;
  local_50 = FLOAT_8043b168;
  iVar4 = param_1;
  for (uVar3 = 0; (int)uVar3 < (int)*(char *)(param_1 + 0x13); uVar3 = uVar3 + 1) {
    if (uVar3 == ((int)*(short *)(param_1 + 0x1c) & 1U)) {
      pfVar1 = &local_58;
      uVar5 = zz_00456a0_((float *)(param_1 + 0x114),afStack_4c,pfVar1);
    }
    else {
      uVar5 = gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),afStack_4c);
    }
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_4c,
                (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 8018f504  FUN_8018f504 ====

void FUN_8018f504(int param_1)

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



// ==== 8018f56c  zz_018f56c_ ====

void zz_018f56c_(void)

{
  PTR_DAT_80433934[0x45] = 0;
  (*(code *)(&PTR_FUN_8036ecb8)[*(short *)PTR_DAT_80433944])();
  return;
}



// ==== 8018f5b4  zz_018f5b4_ ====

void zz_018f5b4_(void)

{
  DAT_803bfde0 = DAT_80436238 + DAT_8036eccc;
  DAT_80436218 = DAT_80436238 + DAT_8036ecd0;
  DAT_803bfe00 = DAT_80436238 + DAT_8036ecd4;
  DAT_803bfde4 = DAT_80436238 + DAT_8036ecd8;
  iRam8043621c = DAT_80436238 + DAT_8036ecdc;
  DAT_803bfe04 = DAT_80436238 + DAT_8036ece0;
  return;
}



// ==== 8018f620  FUN_8018f620 ====

undefined4 FUN_8018f620(void)

{
  (*(code *)(&PTR_FUN_804356b8)[*(short *)(PTR_DAT_80433944 + 2)])();
  return 0;
}



// ==== 8018f65c  FUN_8018f65c ====

void FUN_8018f65c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 extraout_r4;
  undefined4 uVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
  zz_0197854_(3);
  uVar1 = 3;
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,3);
  uVar2 = zz_018f5b4_();
  uVar2 = zz_004369c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4,
                      uVar1,in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar2 = zz_00439a0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  zz_00437b0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  return;
}



// ==== 8018f6c4  FUN_8018f6c4 ====

void FUN_8018f6c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined *puVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar6;
  
  iVar1 = zz_000a3c4_();
  puVar5 = PTR_DAT_80433944;
  if (iVar1 == 0) {
    puVar2 = (undefined *)0x0;
    puVar3 = (undefined *)0x0;
    *(short *)PTR_DAT_80433944 = *(short *)PTR_DAT_80433944 + 1;
    puVar4 = PTR_DAT_80433944;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
    uVar6 = set_global_menu_mode(0);
    uVar6 = zz_004370c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar6 >> 0x20),(int)uVar6,puVar2,puVar3,puVar4,puVar5,in_r9
                        ,in_r10);
    uVar6 = zz_0008a94_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                        extraout_r4,puVar2,puVar3,puVar4,puVar5,in_r9,in_r10);
    zz_007fd6c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_016e650_,0,puVar2,
                puVar3,puVar4,puVar5,in_r9,in_r10);
    zz_0190f00_();
    if (PTR_DAT_80433944[0x17] == '\0') {
      puVar4 = (undefined *)0x0;
      PTR_DAT_80433944[0x19] = 0xff;
      PTR_DAT_80433944[0x18] = 0xff;
      for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
        if (puVar4 != (undefined *)0x0) break;
        if (((int)(char)PTR_DAT_80433930[2] & (uint)(1 << iVar1)) != 0) {
          PTR_DAT_80433944[0x18] = (char)iVar1;
          PTR_DAT_80433944[0x14] = (char)iVar1;
          puVar4 = (undefined *)(1 << iVar1);
        }
      }
      PTR_DAT_80433930[2] = (char)puVar4;
      puVar3 = PTR_DAT_80433930;
      PTR_DAT_80433930[3] = 1;
      uVar6 = zz_0027aac_(0xe0e0e000,0x1e,0);
    }
    else {
      zz_01905e0_((int)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100));
      uVar6 = zz_0027aac_(0,0x1e,0);
    }
    zz_00e99c8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0c8,
                puVar3,puVar4,puVar5,in_r9,in_r10);
  }
  return;
}



// ==== 8018f82c  FUN_8018f82c ====

undefined4 FUN_8018f82c(void)

{
  *(short *)(PTR_DAT_80433944 + 8) = *(short *)(PTR_DAT_80433944 + 8) + 1;
  (*(code *)(&PTR_FUN_8036ece4)[*(short *)(PTR_DAT_80433944 + 2)])();
  zz_0190f34_();
  zz_0191014_();
  return 0;
}



// ==== 8018f884  FUN_8018f884 ====

void FUN_8018f884(void)

{
  (*(code *)(&PTR_FUN_804356c0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8018f8bc  FUN_8018f8bc ====

void FUN_8018f8bc(void)

{
  char *pcVar1;
  
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  if (PTR_DAT_80433944[0x17] == '\0') {
    PTR_DAT_80433944[0x2c] = 8;
  }
  else {
    PTR_DAT_80433944[0x2c] = 4;
  }
  PTR_DAT_80433944[0x2d] = 0;
  pcVar1 = &DAT_8036ec78;
  PTR_DAT_80433944[0x2e] = 0;
  while( true ) {
    if (*pcVar1 < '\0') break;
    zz_0191938_((int)*pcVar1,pcVar1[1]);
    pcVar1 = pcVar1 + 2;
  }
  return;
}



// ==== 8018f954  FUN_8018f954 ====

void FUN_8018f954(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    if (PTR_DAT_80433944[0x17] == '\0') {
      *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    }
    else {
      *(undefined2 *)(PTR_DAT_80433944 + 4) = 3;
    }
    zz_0027c1c_();
  }
  return;
}



// ==== 8018f9bc  FUN_8018f9bc ====

void FUN_8018f9bc(void)

{
  (*(code *)(&PTR_FUN_8036ecf0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8018f9f8  FUN_8018f9f8 ====

void FUN_8018f9f8(void)

{
  (*(code *)(&PTR_LAB_8036ed08)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 8018facc  FUN_8018facc ====

void FUN_8018facc(void)

{
  ushort uVar1;
  int iVar2;
  
  zz_016e694_((int)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100),
              (int)(char)PTR_DAT_80433944[0x14]);
  iVar2 = (int)(char)PTR_DAT_80433944[0x15];
  uVar1 = *(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10e);
  if ((*(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10c) & 1) == 0) {
    if (((*(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10c) & 2) != 0) &&
       (iVar2 = iVar2 + 1, 2 < iVar2)) {
      iVar2 = 2;
    }
  }
  else {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
  }
  if (iVar2 != (char)PTR_DAT_80433944[0x15]) {
    PTR_DAT_80433944[0x15] = (char)iVar2;
    zz_00f0468_(0,0x77,0);
  }
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x180) != 0) {
      *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
      PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xf7;
      PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 8;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 4);
    *(undefined2 *)(PTR_DAT_80433944 + 0x12) = *(undefined2 *)(PTR_DAT_80433944 + 6);
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 5;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 2;
    zz_01904f4_();
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 8018fc98  FUN_8018fc98 ====

void FUN_8018fc98(void)

{
  (*(code *)(&PTR_LAB_8036ed18)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 8018fd6c  FUN_8018fd6c ====

void FUN_8018fd6c(void)

{
  ushort uVar1;
  int iVar2;
  
  zz_016e694_((int)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100),
              (int)(char)PTR_DAT_80433944[0x14]);
  iVar2 = (int)(char)PTR_DAT_80433944[0x16];
  uVar1 = *(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10e);
  if ((*(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10c) & 1) == 0) {
    if (((*(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10c) & 2) != 0) &&
       (iVar2 = iVar2 + 1, 1 < iVar2)) {
      iVar2 = 1;
    }
  }
  else {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) {
      iVar2 = 0;
    }
  }
  if (iVar2 != (char)PTR_DAT_80433944[0x16]) {
    PTR_DAT_80433944[0x16] = (char)iVar2;
    zz_00f0468_(0,0x77,0);
  }
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x180) != 0) {
      *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
      PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfd;
      PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 2;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xfd;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfd;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 8018ff14  FUN_8018ff14 ====

void FUN_8018ff14(void)

{
  (*(code *)(&PTR_FUN_8036ed28)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 8018ff50  FUN_8018ff50 ====

void FUN_8018ff50(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
  *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
  PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 1;
  PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfe;
  PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xfe;
  zz_00449e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  return;
}



// ==== 8018ffc0  FUN_8018ffc0 ====

void FUN_8018ffc0(void)

{
  int iVar1;
  
  if (*(short *)(PTR_DAT_80433944 + 0xe) != 0) {
    *(short *)(PTR_DAT_80433944 + 0xe) = *(short *)(PTR_DAT_80433944 + 0xe) + -1;
  }
  iVar1 = zz_000a3c4_();
  if ((iVar1 == 0) && (*(short *)(PTR_DAT_80433944 + 0xe) == 0)) {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    PTR_DAT_80433944[0x6d] = 0;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] | 1;
  }
  return;
}



// ==== 80190038  FUN_80190038 ====

void FUN_80190038(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  ushort unaff_r28;
  int iVar2;
  int iVar3;
  
  if (PTR_DAT_80433944[0x17] == '\x01') {
    zz_016e694_((int)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100),
                (int)(char)PTR_DAT_80433944[0x14]);
    unaff_r28 = *(ushort *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x10e);
  }
  else if (PTR_DAT_80433944[0x17] == '\x02') {
    unaff_r28 = 0;
    iVar3 = 0;
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      if (iVar2 == (char)PTR_DAT_80433944[0x14]) {
        *(undefined2 *)(PTR_DAT_80433944 + iVar3 + 0x10e) = 0;
      }
      else {
        zz_016e694_((int)(PTR_DAT_80433944 + iVar3 + 0x100),iVar2);
      }
      iVar1 = iVar3 + 0x10e;
      iVar3 = iVar3 + 0x80;
      unaff_r28 = unaff_r28 | *(ushort *)(PTR_DAT_80433944 + iVar1);
    }
  }
  if ((unaff_r28 & 0x200) == 0) {
    if ((unaff_r28 & 0x100) == 0) {
      if ((unaff_r28 & 0x80) != 0) {
        *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 2;
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
        PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfe;
        PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 1;
        if (PTR_DAT_80433944[0x17] == '\x02') {
          param_1 = zz_019052c_(0x80);
        }
        zz_00437b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
        zz_00f0468_(0,0x7a,0);
      }
    }
    else {
      *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
      *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 8;
      PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfe;
      if (PTR_DAT_80433944[0x17] == '\x02') {
        zz_019052c_(0x100);
      }
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 4);
    *(undefined2 *)(PTR_DAT_80433944 + 0x12) = *(undefined2 *)(PTR_DAT_80433944 + 6);
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 5;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 2;
    if (PTR_DAT_80433944[0x17] == '\x01') {
      PTR_DAT_80433944[0x6e] = PTR_DAT_80433944[0x14];
    }
    else if (PTR_DAT_80433944[0x17] == '\x02') {
      zz_01904f4_();
    }
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 8019028c  FUN_8019028c ====

void FUN_8019028c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char *pcVar1;
  short sVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 in_r10;
  
  if (*(short *)(PTR_DAT_80433944 + 0xc) == 0) {
    sVar2 = *(short *)(PTR_DAT_80433944 + 0xe);
    *(short *)(PTR_DAT_80433944 + 0xe) = sVar2 + -1;
    puVar3 = PTR_DAT_80433944;
    if ((short)(sVar2 + -1) < 1) {
      pcVar1 = PTR_DAT_80433944 + 0x17;
      *(short *)(PTR_DAT_80433944 + 0xc) = *(short *)(PTR_DAT_80433944 + 0xc) + 1;
      iVar4 = *pcVar1 + -1;
      zz_01b1cc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  (int)(char)PTR_DAT_80433944[0x14],(&DAT_803bfde0)[iVar4],(&DAT_80436218)[iVar4],
                  (&DAT_803bfe00)[iVar4],PTR_DAT_80433944,puVar3,in_r10);
    }
  }
  else {
    iVar4 = zz_01b1da4_();
    if (iVar4 < 1) {
      *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
      PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 1;
      if (iVar4 == 0) {
        PTR_DAT_80433944[0x6d] = 1;
      }
      zz_00437b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
    }
  }
  return;
}



// ==== 80190370  FUN_80190370 ====

void FUN_80190370(void)

{
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  undefined *puVar4;
  
  if (*(short *)(PTR_DAT_80433944 + 0xe) != 0) {
    *(short *)(PTR_DAT_80433944 + 0xe) = *(short *)(PTR_DAT_80433944 + 0xe) + -1;
  }
  iVar3 = zz_000a3c4_();
  puVar4 = PTR_DAT_80433944;
  if (iVar3 == 0) {
    if (*(short *)(PTR_DAT_80433944 + 0xe) == 0) {
      pcVar1 = PTR_DAT_80433944 + 0x14;
      pcVar2 = PTR_DAT_80433944 + 0x17;
      *(undefined2 *)(PTR_DAT_80433944 + 4) = 3;
      puVar4 = puVar4 + *pcVar1 * 0x80 + 0x100;
      iVar3 = *pcVar2 + -1;
      *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 0;
      PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xfe;
      if (PTR_DAT_80433944[0x6d] == '\0') {
        if (iVar3 == 0) {
          zz_01cada4_(DAT_803bfde0,DAT_80436218,DAT_803bfe00);
        }
        else {
          gnt4_memcpy((&DAT_803bfde0)[iVar3],DAT_803bfde0,600);
          gnt4_memcpy((&DAT_80436218)[iVar3],DAT_80436218,0xabe4);
          gnt4_memcpy((&DAT_803bfe00)[iVar3],DAT_803bfe00,0x2190);
        }
      }
      *(char **)(puVar4 + 0x48) = (&DAT_803bfde0)[iVar3];
      *(undefined2 **)(puVar4 + 0x44) = (&DAT_80436218)[iVar3];
      *(char **)(puVar4 + 0x40) = (&DAT_803bfe00)[iVar3];
      zz_01905e0_((int)puVar4);
    }
  }
  return;
}



// ==== 801904f4  zz_01904f4_ ====

void zz_01904f4_(void)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (3 < iVar1) break;
    if ((*(ushort *)(PTR_DAT_80433944 + iVar1 * 0x80 + 0x10e) & 0x200) != 0) {
      PTR_DAT_80433944[0x6e] = (char)iVar1;
      iVar1 = 4;
    }
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 8019052c  zz_019052c_ ====

/* WARNING: Removing unreachable block (ram,0x801905ac) */

void zz_019052c_(ushort param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    if ((iVar2 != (char)PTR_DAT_80433944[0x14]) &&
       ((*(ushort *)(PTR_DAT_80433944 + iVar2 * 0x80 + 0x10e) & param_1) != 0)) {
      PTR_DAT_80433944[0x19] = (char)iVar2;
      iVar1 = 1 << iVar2;
      PTR_DAT_80433944[0x14] = (char)iVar2;
      iVar2 = 4;
      PTR_DAT_80433930[2] = PTR_DAT_80433930[2] | (byte)iVar1;
    }
  }
  iVar1 = 0;
  iVar2 = 4;
  PTR_DAT_80433930[3] = 0;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar1) != 0) {
      PTR_DAT_80433930[3] = PTR_DAT_80433930[3] + '\x01';
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ==== 801905e0  zz_01905e0_ ====

void zz_01905e0_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  
  iVar4 = 0;
  iVar2 = 0x14;
  *(undefined1 *)(param_1 + 0x60) = 0;
  iVar3 = 0;
  cVar5 = -1;
  do {
    if (*(char *)(*(int *)(param_1 + 0x40) + iVar3 + 0x29) != '\0') {
      if (iVar4 == *(char *)(param_1 + 0x61)) {
        cVar5 = *(char *)(param_1 + 0x60);
      }
      cVar1 = *(char *)(param_1 + 0x60);
      *(char *)(param_1 + 0x60) = cVar1 + '\x01';
      *(char *)(param_1 + cVar1 + 0x4c) = (char)iVar4;
    }
    iVar3 = iVar3 + 0x6c;
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (cVar5 < '\0') {
    *(undefined1 *)(param_1 + 0x61) = 0;
    return;
  }
  *(char *)(param_1 + 0x61) = cVar5;
  return;
}



// ==== 80190670  FUN_80190670 ====

void FUN_80190670(void)

{
  (*(code *)(&PTR_LAB_8036ed3c)[*(short *)(PTR_DAT_80433944 + 6)])
            (PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100);
  return;
}



// ==== 8019074c  FUN_8019074c ====

void FUN_8019074c(int param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  
  zz_016e694_(param_1,(int)(char)PTR_DAT_80433944[0x14]);
  uVar1 = *(ushort *)(param_1 + 0xe);
  iVar3 = (int)*(char *)(param_1 + 0x61);
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar3 = iVar3 + 1; *(char *)(param_1 + 0x60) <= iVar3;
          iVar3 = iVar3 - (*(char *)(param_1 + 0x60) + 1)) {
      }
    }
  }
  else {
    for (iVar3 = iVar3 + -1; iVar3 < -1; iVar3 = *(char *)(param_1 + 0x60) + iVar3 + 1) {
    }
  }
  if (iVar3 != *(char *)(param_1 + 0x61)) {
    *(char *)(param_1 + 0x61) = (char)iVar3;
    zz_00f0468_(0,0x77,0);
  }
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x400) == 0) {
      if ((uVar1 & 0x180) != 0) {
        uVar2 = countLeadingZeros(-1 - *(char *)(param_1 + 0x61));
        uVar2 = uVar2 >> 5;
        if (uVar2 == 0) {
          uVar2 = zz_01cce38_(*(int *)(param_1 + 0x40),
                              (int)*(char *)(param_1 + *(char *)(param_1 + 0x61) + 0x4c),
                              *(int *)(PTR_DAT_80433934 + 0x120),0);
        }
        if (uVar2 == 0) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
          *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x10;
          PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfb;
          PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 4;
          zz_00f0468_(0,0x7a,0);
        }
      }
    }
    else {
      *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 4);
      *(undefined2 *)(PTR_DAT_80433944 + 0x12) = *(undefined2 *)(PTR_DAT_80433944 + 6);
      *(undefined2 *)(PTR_DAT_80433944 + 4) = 5;
      *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 1;
      PTR_DAT_80433944[0x6e] = PTR_DAT_80433944[0x14];
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 4);
    *(undefined2 *)(PTR_DAT_80433944 + 0x12) = *(undefined2 *)(PTR_DAT_80433944 + 6);
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 5;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 2;
    PTR_DAT_80433944[0x6e] = PTR_DAT_80433944[0x14];
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80190a1c  FUN_80190a1c ====

void FUN_80190a1c(void)

{
  (*(code *)(&PTR_LAB_804356c8)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 80190a74  FUN_80190a74 ====

void FUN_80190a74(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  
  sVar1 = *(short *)(PTR_DAT_80433944 + 0xe);
  *(short *)(PTR_DAT_80433944 + 0xe) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 0) {
    *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 0xc) = 3;
    zz_01910b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_0027aac_(0,0x3c,1);
    zz_00e9b60_((double)FLOAT_8043b178,2,0x3c,2);
  }
  return;
}



// ==== 80190af8  FUN_80190af8 ====

void FUN_80190af8(void)

{
  (*(code *)(&PTR_FUN_8036ed4c)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 80190b34  FUN_80190b34 ====

void FUN_80190b34(void)

{
  if ((*(short *)(PTR_DAT_80433944 + 0xc) == 2) && (PTR_DAT_80433944[0x17] != '\0')) {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
    PTR_DAT_80433944[0x6f] = 1;
    PTR_DAT_80433944[0x83] = 1;
    zz_0191938_(0xf,0);
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 4;
  }
  return;
}



// ==== 80190bdc  FUN_80190bdc ====

void FUN_80190bdc(void)

{
  undefined *puVar1;
  
  puVar1 = PTR_DAT_80433944 + (uint)(byte)PTR_DAT_80433944[0x6e] * 0x80 + 0x100;
  zz_016e694_((int)puVar1,(uint)(byte)PTR_DAT_80433944[0x6e]);
  if ((*(ushort *)(puVar1 + 0xe) & 3) != 0) {
    PTR_DAT_80433944[0x83] = PTR_DAT_80433944[0x83] ^ 1;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(ushort *)(puVar1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(puVar1 + 0xe) & 0x180) != 0) {
      *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
      if (PTR_DAT_80433944[0x83] == '\0') {
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x18;
        PTR_DAT_80433944[0x6f] = 2;
      }
      else {
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
        PTR_DAT_80433944[0x6f] = 0;
      }
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
    PTR_DAT_80433944[0x6f] = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80190d44  FUN_80190d44 ====

void FUN_80190d44(void)

{
  *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
  *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
  *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
  zz_0027aac_(0,0x1e,1);
  zz_00e9b60_((double)FLOAT_8043b178,2,0x1e,2);
  return;
}



// ==== 80190da8  FUN_80190da8 ====

void FUN_80190da8(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)PTR_DAT_80433944 = *(short *)PTR_DAT_80433944 + *(short *)(PTR_DAT_80433944 + 0xc);
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
  }
  return;
}



// ==== 80190e14  FUN_80190e14 ====

int FUN_80190e14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  
  puVar2 = PTR_DAT_80433944;
  iVar1 = (char)PTR_DAT_80433944[0x14] * 0x80;
  uVar3 = zz_0027c1c_();
  zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_007fd5c_();
  if (puVar2[iVar1 + 0x161] == -1) {
    puVar2[iVar1 + 0x161] = 0;
  }
  return (char)puVar2[(char)puVar2[iVar1 + 0x161] + iVar1 + 0x14c] + 0x8000;
}



// ==== 80190e90  FUN_80190e90 ====

undefined4
FUN_80190e90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
            undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  uVar1 = zz_0027c1c_();
  zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_007fd5c_();
  return 0xffffffff;
}



// ==== 80190ebc  FUN_80190ebc ====

bool FUN_80190ebc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 extraout_f1;
  undefined8 uVar2;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    uVar2 = zz_0027c1c_();
    zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar2 >> 0x20),(int)uVar2,param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_0029fd4_();
    zz_007fd5c_();
  }
  return iVar1 == 0;
}



// ==== 80190f00  zz_0190f00_ ====

void zz_0190f00_(void)

{
  gnt4_memset(&DAT_803c73b0,0,0x3e4);
  zz_0190f34_();
  return;
}



// ==== 80190f34  zz_0190f34_ ====

void zz_0190f34_(void)

{
  float afStack_28 [5];
  
  DAT_803c76e4 = FLOAT_8043b180;
  DAT_803c76b8 = FLOAT_8043b17c;
  DAT_803c7698 = FLOAT_8043b178;
  PTR_DAT_80433930[0xc] = 0;
  DAT_803c769c = DAT_803c7698;
  DAT_803c76a0 = DAT_803c7698;
  DAT_803c76b0 = DAT_803c7698;
  DAT_803c76b4 = DAT_803c7698;
  DAT_803c76e0 = DAT_803c7698;
  DAT_803c76e8 = DAT_803c7698;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7744,&DAT_803c7698,&DAT_803c76e0,&DAT_803c76b0);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7744;
  gnt4_PSVECSubtract_bl(&DAT_803c7698,&DAT_803c76b0,afStack_28);
  zz_0045ef4_((float *)&DAT_803c7714,5,afStack_28,&DAT_803c76e0);
  DAT_803c7720 = DAT_803c7698;
  DAT_803c7730 = DAT_803c769c;
  DAT_803c7740 = DAT_803c76a0;
  return;
}



// ==== 80191014  zz_0191014_ ====

void zz_0191014_(void)

{
  zz_0191038_();
  zz_019106c_();
  return;
}



// ==== 80191038  zz_0191038_ ====

void zz_0191038_(void)

{
  zz_0089898_(0x10);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 8019106c  zz_019106c_ ====

void zz_019106c_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x10);
  zz_0089c00_(0x38);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 801910b4  zz_01910b4_ ====

void zz_01910b4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  undefined2 uVar2;
  bool bVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char cVar11;
  short *psVar12;
  int iVar13;
  undefined2 *puVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  uint uVar20;
  undefined8 uVar21;
  undefined2 local_208 [2];
  short local_204 [2];
  undefined2 local_200 [2];
  short local_1fc [230];
  
  iVar10 = 0;
  iVar9 = 0;
  do {
    iVar19 = 5;
    iVar18 = 0;
    do {
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 0x1e8) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x1ea] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 0x204) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x206] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 0x220) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x222] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 0x23c) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x23e] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 600) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x25a] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar9 + iVar18 + 0x274) = 0xffff;
      PTR_DAT_80433934[iVar9 + iVar18 + 0x276] = 0;
      iVar19 = iVar19 + -1;
      iVar18 = iVar18 + 0xa8;
    } while (iVar19 != 0);
    iVar10 = iVar10 + 1;
    iVar9 = iVar9 + 0x348;
  } while (iVar10 < 6);
  iVar9 = 0;
  iVar19 = 0;
  iVar18 = 0;
  iVar10 = 0;
  do {
    puVar4 = PTR_DAT_80433944;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar9) != 0) {
      iVar13 = *(int *)(PTR_DAT_80433934 + 0x120);
      if ((char)PTR_DAT_80433944[iVar19 + 0x161] < '\0') {
        local_1fc[0] = -1;
        local_1fc[1] = 0xffff;
        local_1fc[2] = 0xffff;
        local_1fc[3] = 0xffff;
        local_1fc[4] = 0xffff;
        local_1fc[5] = 0xffff;
        local_1fc[6] = 0xffff;
        local_1fc[7] = 0xffff;
        local_1fc[8] = 0xffff;
        local_1fc[9] = 0xffff;
        local_1fc[10] = 0xffff;
        local_1fc[0xb] = 0xffff;
        local_1fc[0xc] = 0xffff;
        local_1fc[0xd] = 0xffff;
        local_1fc[0xe] = 0xffff;
        local_1fc[0xf] = 0xffff;
        local_1fc[0x10] = 0xffff;
        local_1fc[0x11] = 0xffff;
        local_1fc[0x12] = 0xffff;
        local_1fc[0x13] = 0xffff;
        local_1fc[0x14] = 0xffff;
        local_1fc[0x15] = 0xffff;
        local_1fc[0x16] = 0xffff;
        local_1fc[0x17] = 0xffff;
        local_1fc[0x18] = 0xffff;
        local_1fc[0x19] = 0xffff;
        local_1fc[0x1a] = 0xffff;
        local_1fc[0x1b] = 0xffff;
        local_1fc[0x1c] = 0xffff;
        local_1fc[0x1d] = 0xffff;
        iVar8 = 0;
        PTR_DAT_80433934[iVar9 + 0x5a] = 0;
        for (iVar16 = 0; iVar16 < 0x1e; iVar16 = iVar16 + 1) {
          uVar7 = 0;
          iVar5 = 0;
          iVar17 = 0;
          for (iVar15 = 0; iVar15 < 200; iVar15 = iVar15 + 1) {
            psVar12 = (short *)(*(int *)(puVar4 + iVar19 + 0x140) + iVar17 + 0x870);
            if (-1 < *psVar12) {
              local_204[0] = *psVar12;
              iVar6 = zz_0066168_((char *)local_204,(int)*(char *)(psVar12 + 1));
              if (iVar8 + iVar6 <= iVar13) {
                bVar3 = false;
                psVar12 = local_1fc;
                iVar6 = 0;
                while ((iVar6 < (char)PTR_DAT_80433934[iVar9 + 0x5a] && (!bVar3))) {
                  if (iVar15 == *psVar12) {
                    bVar3 = true;
                  }
                  psVar12 = psVar12 + 1;
                  iVar6 = iVar6 + 1;
                }
                if (!bVar3) {
                  uVar7 = uVar7 + 1;
                  *(short *)((int)local_1fc + iVar5 + 0x3c) = (short)iVar15;
                  iVar5 = iVar5 + 2;
                }
              }
            }
            iVar17 = iVar17 + 0x20;
          }
          if (uVar7 == 0) {
            iVar16 = 0x1e;
          }
          else {
            uVar20 = zz_00055fc_();
            sVar1 = local_1fc[((uVar20 & 0xff) - ((uVar20 & 0xff) / uVar7) * uVar7) + 0x1e];
            puVar14 = (undefined2 *)(*(int *)(puVar4 + iVar19 + 0x140) + sVar1 * 0x20 + 0x870);
            local_208[0] = *puVar14;
            iVar17 = zz_0066168_((char *)local_208,(int)*(char *)(puVar14 + 1));
            uVar2 = *puVar14;
            iVar8 = iVar8 + iVar17;
            cVar11 = PTR_DAT_80433934[iVar9 + 0x5a];
            local_1fc[cVar11] = sVar1;
            *(undefined2 *)(PTR_DAT_80433934 + iVar18 + cVar11 * 0x1c + 0x1e8) = uVar2;
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1ea] =
                 *(undefined1 *)(puVar14 + 1);
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1eb] =
                 *(undefined1 *)((int)puVar14 + 3);
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1ec) =
                 *(undefined4 *)(puVar14 + 4);
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 500) =
                 *(undefined4 *)(puVar14 + 2);
            PTR_DAT_80433934[iVar9 + 0x5a] = PTR_DAT_80433934[iVar9 + 0x5a] + '\x01';
          }
        }
        if (PTR_DAT_80433934[iVar9 + 0x5a] == '\0') {
          iVar13 = -1;
          cVar11 = '\x06';
          for (iVar8 = 0; iVar8 < 2000; iVar8 = iVar8 + 1) {
            psVar12 = (short *)(*(int *)(puVar4 + iVar19 + 0x144) + iVar8 * 0x10);
            if ((*psVar12 == 0x629) && (*(char *)(psVar12 + 1) == '\0')) {
              iVar13 = iVar8;
              iVar8 = 2000;
            }
            else if ((*psVar12 == 0x615) && (*(char *)(psVar12 + 1) < cVar11)) {
              iVar13 = iVar8;
              cVar11 = *(char *)(psVar12 + 1);
            }
          }
          if (iVar13 < 0) {
            iVar13 = iVar9 + 0x5a;
            *(undefined2 *)(PTR_DAT_80433934 + iVar18 + 0x1e8) = 0x615;
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar13] * 0x1c + 0x1ea] = 0;
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar13] * 0x1c + 0x1eb] = 0;
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar13] * 0x1c + 0x1ec) = 0;
            *(undefined4 *)(PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar13] * 0x1c + 500)
                 = 0;
          }
          else {
            iVar8 = iVar9 + 0x5a;
            puVar14 = (undefined2 *)(*(int *)(puVar4 + iVar19 + 0x144) + iVar13 * 0x10);
            *(undefined2 *)(PTR_DAT_80433934 + iVar18 + 0x1e8) = *puVar14;
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar8] * 0x1c + 0x1ea] =
                 *(undefined1 *)(puVar14 + 1);
            PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar8] * 0x1c + 0x1eb] =
                 *(undefined1 *)((int)puVar14 + 3);
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar8] * 0x1c + 0x1ec) =
                 *(undefined4 *)(puVar14 + 4);
            *(undefined4 *)(PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar8] * 0x1c + 500)
                 = *(undefined4 *)(puVar14 + 2);
          }
          PTR_DAT_80433934[iVar9 + 0x5a] = PTR_DAT_80433934[iVar9 + 0x5a] + '\x01';
        }
        sprintf(PTR_DAT_80433934 + iVar10 + 0x1654,&DAT_802b3600);
      }
      else {
        iVar8 = *(int *)(PTR_DAT_80433944 + iVar19 + 0x140);
        cVar11 = PTR_DAT_80433944[(int)(char)PTR_DAT_80433944[iVar19 + 0x161] + iVar19 + 0x14c];
        iVar16 = 0;
        PTR_DAT_80433934[iVar9 + 0x5a] = 0;
        iVar8 = iVar8 + cVar11 * 0x6c;
        for (iVar17 = 0; iVar17 < 0x1e; iVar17 = iVar17 + 1) {
          iVar5 = (int)*(short *)(iVar8 + iVar17 * 2 + 0x30);
          if (-1 < iVar5) {
            puVar14 = (undefined2 *)(*(int *)(puVar4 + iVar19 + 0x140) + iVar5 * 0x20 + 0x870);
            local_200[0] = *puVar14;
            iVar5 = zz_0066168_((char *)local_200,(int)*(char *)(puVar14 + 1));
            iVar16 = iVar16 + iVar5;
            if (iVar13 < iVar16) {
              iVar17 = 0x1e;
            }
            else {
              *(undefined2 *)
               (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1e8) =
                   *puVar14;
              PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1ea] =
                   *(undefined1 *)(puVar14 + 1);
              PTR_DAT_80433934[iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1eb] =
                   *(undefined1 *)((int)puVar14 + 3);
              *(undefined4 *)
               (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 0x1ec) =
                   *(undefined4 *)(puVar14 + 4);
              *(undefined4 *)
               (PTR_DAT_80433934 + iVar18 + (char)PTR_DAT_80433934[iVar9 + 0x5a] * 0x1c + 500) =
                   *(undefined4 *)(puVar14 + 2);
              PTR_DAT_80433934[iVar9 + 0x5a] = PTR_DAT_80433934[iVar9 + 0x5a] + '\x01';
            }
          }
        }
        zz_0238cbc_((int)(PTR_DAT_80433934 + iVar10 + 0x1654),iVar8,0x28);
      }
    }
    iVar9 = iVar9 + 1;
    iVar18 = iVar18 + 0x348;
    iVar10 = iVar10 + 0x29;
    iVar19 = iVar19 + 0x80;
  } while (iVar9 < 6);
  PTR_DAT_80433930[0x33] = 1;
  for (iVar9 = 0; iVar10 = (int)(char)PTR_DAT_80433930[3], iVar9 < iVar10; iVar9 = iVar9 + 1) {
    PTR_DAT_80433934[iVar9 + 0xc0] = PTR_DAT_80433944[iVar9 + 0x18];
  }
  uVar7 = 4 - iVar10;
  if (iVar10 < 4) {
    uVar20 = uVar7 >> 3;
    if (uVar20 != 0) {
      do {
        PTR_DAT_80433934[iVar10 + 0xc0] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc1] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc2] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc3] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc4] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc5] = 0xff;
        PTR_DAT_80433934[iVar10 + 0xc6] = 0xff;
        iVar9 = iVar10 + 199;
        iVar10 = iVar10 + 8;
        PTR_DAT_80433934[iVar9] = 0xff;
        uVar20 = uVar20 - 1;
      } while (uVar20 != 0);
      uVar7 = uVar7 & 7;
      if (uVar7 == 0) goto LAB_80191918;
    }
    do {
      iVar9 = iVar10 + 0xc0;
      iVar10 = iVar10 + 1;
      PTR_DAT_80433934[iVar9] = 0xff;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
LAB_80191918:
  uVar21 = zz_0196dac_();
  uVar21 = zz_0042454_(uVar21,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0042690_(uVar21,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80191938  zz_0191938_ ====

void zz_0191938_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_8036ed60)[param_1]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_80191a1c;
    *(code **)(puVar1 + 0x10c) = FUN_80191ba8;
    puVar1[0x10] = 2;
    puVar1[0x11] = (char)param_1;
    puVar1[0x12] = param_2;
    puVar1[0x13] = (&DAT_8036ed60)[(char)puVar1[0x11]];
  }
  return;
}



// ==== 801919dc  zz_01919dc_ ====

void zz_01919dc_(undefined4 param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = zz_0191938_(param_2,param_3);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x8c) = param_1;
  }
  return;
}



// ==== 80191a1c  FUN_80191a1c ====

void FUN_80191a1c(int param_1)

{
  (*(code *)(&PTR_FUN_8036ed74)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80191a58  FUN_80191a58 ====

void FUN_80191a58(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = (int)*(char *)(param_1 + 0x13) << 5;
  if (uVar1 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_1 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    (*(code *)(&PTR_FUN_8036ed84)[*(char *)(param_1 + 0x11)])(param_1);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 80191b10  FUN_80191b10 ====

void FUN_80191b10(int param_1)

{
  (*(code *)(&PTR_zz_0191c78__8036edd4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80191b60  FUN_80191b60 ====

void FUN_80191b60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80191ba8  FUN_80191ba8 ====

void FUN_80191ba8(int param_1)

{
  (*(code *)(&PTR_FUN_8036ee24)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80191be4  FUN_80191be4 ====

void FUN_80191be4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar3;
  undefined8 uVar4;
  
  fVar2 = FLOAT_8043b188;
  *(float *)(param_9 + 0xd4) = FLOAT_8043b188;
  fVar1 = FLOAT_8043b18c;
  if (PTR_DAT_80433944[0x17] == '\0') {
    fVar1 = fVar2;
  }
  *(float *)(param_9 + 0xd8) = fVar1;
  pfVar3 = (float *)0x62;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x62,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar3,param_12,param_13
                      ,param_14,param_15,param_16);
  uVar4 = zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007d40_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4_00,pfVar3,param_12,param_13,param_14,param_15,param_16);
  zz_0191c78_(param_9,extraout_r4_01,pfVar3,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80191c78  zz_0191c78_ ====

void zz_0191c78_(int param_1,undefined4 param_2,float *param_3,undefined4 param_4,undefined4 param_5
                ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  byte bVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  bVar2 = PTR_DAT_80433944[0x2c];
  if ((bVar2 & 8) == 0) {
    if ((bVar2 & 2) == 0) {
      if ((bVar2 & 1) == 0) {
        if ((bVar2 & 4) == 0) {
          dVar6 = (double)FLOAT_8043b198;
        }
        else {
          dVar6 = (double)FLOAT_8043b18c;
        }
      }
      else {
        dVar6 = (double)FLOAT_8043b194;
      }
    }
    else {
      dVar6 = (double)FLOAT_8043b190;
    }
  }
  else {
    dVar6 = (double)FLOAT_8043b188;
  }
  if ((double)FLOAT_8043b188 <= dVar6) {
    dVar5 = (double)*(float *)(param_1 + 0xd8);
    if ((dVar5 < dVar6) &&
       (dVar3 = (double)FLOAT_8043b19c, *(float *)(param_1 + 0xd8) = (float)(dVar5 + dVar3),
       dVar6 < (double)(float)(dVar5 + dVar3))) {
      *(float *)(param_1 + 0xd8) = (float)dVar6;
    }
    if ((dVar6 < (double)*(float *)(param_1 + 0xd8)) &&
       (fVar1 = (float)((double)*(float *)(param_1 + 0xd8) - (double)FLOAT_8043b19c),
       *(float *)(param_1 + 0xd8) = fVar1, (double)fVar1 < dVar6)) {
      *(float *)(param_1 + 0xd8) = (float)dVar6;
    }
    if ((double)*(float *)(param_1 + 0xd8) != dVar5) {
      uVar4 = zz_00086b8_((double)*(float *)(param_1 + 0xd8),dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,
                          in_f8,DAT_803bb384,*(int *)(param_1 + 0xe0),param_3,param_4,param_5,
                          param_6,param_7,param_8);
      uVar4 = zz_0007c30_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                          extraout_r4,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_0007d40_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                  extraout_r4_00,param_3,param_4,param_5,param_6,param_7,param_8);
    }
  }
  fVar1 = FLOAT_8043b1a0;
  dVar3 = (double)*(float *)(param_1 + 0xd4);
  dVar5 = (double)FLOAT_8043b190;
  *(float *)(param_1 + 0xd4) = (float)(dVar3 + dVar5);
  if (fVar1 <= (float)(dVar3 + dVar5)) {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - fVar1;
  }
  uVar4 = zz_0008744_((double)*(float *)(param_1 + 0xd4),dVar3,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,
                      DAT_803bb384,*(int *)(param_1 + 0xe0),param_3,param_4,param_5,param_6,param_7,
                      param_8);
  zz_0007c30_(uVar4,dVar3,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              extraout_r4_01,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80191dc0  FUN_80191dc0 ====

void FUN_80191dc0(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x25);
  return;
}



// ==== 80191de8  FUN_80191de8 ====

/* WARNING: Removing unreachable block (ram,0x80191e94) */
/* WARNING: Removing unreachable block (ram,0x80191df8) */

void FUN_80191de8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  double dVar7;
  
  dVar7 = (double)FLOAT_8043b190;
  puVar5 = &DAT_8036ee74;
  iVar6 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    puVar2[6] = (float)dVar7;
    *(undefined2 *)(puVar2 + 7) = 0;
    *(undefined2 *)((int)puVar2 + 0x1e) = *puVar5;
    uVar1 = *(undefined4 *)(puVar5 + 4);
    *puVar2 = *(undefined4 *)(puVar5 + 2);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(puVar5 + 6);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar4 + 0xe0),(int)(short)puVar5[1],param_12,
                          param_13,param_14,param_15,param_16);
    iVar6 = iVar6 + 0x20;
    puVar5 = puVar5 + 8;
    iVar4 = iVar4 + 4;
  }
  FUN_80191eb0(param_9);
  return;
}



// ==== 80191eb0  FUN_80191eb0 ====

/* WARNING: Removing unreachable block (ram,0x8019202c) */
/* WARNING: Removing unreachable block (ram,0x80192024) */
/* WARNING: Removing unreachable block (ram,0x80191ec8) */
/* WARNING: Removing unreachable block (ram,0x80191ec0) */

void FUN_80191eb0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  dVar9 = (double)FLOAT_8043b190;
  iVar6 = 0;
  iVar5 = param_1;
  for (iVar4 = 0; fVar1 = FLOAT_8043b19c, fVar2 = FLOAT_8043b190, iVar4 < *(char *)(param_1 + 0x13);
      iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(param_1 + 0x54) + iVar6;
    dVar8 = (double)*(float *)(iVar3 + 0x18);
    if (((ushort)(byte)PTR_DAT_80433944[0x2c] & *(ushort *)(iVar3 + 0x1e)) == 0) {
      if (0 < *(short *)(iVar3 + 0x1c)) {
        *(short *)(iVar3 + 0x1c) = *(short *)(iVar3 + 0x1c) + 1;
        fVar2 = FLOAT_8043b188;
        fVar1 = *(float *)(iVar3 + 0x18) - fVar1;
        *(float *)(iVar3 + 0x18) = fVar1;
        if (fVar1 <= fVar2) {
          *(float *)(iVar3 + 0x18) = FLOAT_8043b190;
          *(undefined2 *)(iVar3 + 0x1c) = 0;
        }
      }
    }
    else {
      *(short *)(iVar3 + 0x1c) = *(short *)(iVar3 + 0x1c) + 1;
      if ((*(float *)(iVar3 + 0x18) < fVar2) &&
         (fVar1 = *(float *)(iVar3 + 0x18) + FLOAT_8043b19c, *(float *)(iVar3 + 0x18) = fVar1,
         fVar2 <= fVar1)) {
        *(float *)(iVar3 + 0x18) = fVar2;
      }
    }
    while (0x7f < *(short *)(iVar3 + 0x1c)) {
      *(short *)(iVar3 + 0x1c) = *(short *)(iVar3 + 0x1c) + -0x40;
    }
    dVar7 = zz_0045238_((short)((int)*(short *)(iVar3 + 0x1c) << 10));
    fVar1 = FLOAT_8043b1a8;
    if (*(short *)(iVar3 + 0x1c) < 0x10) {
      fVar1 = FLOAT_8043b1a4;
    }
    *(float *)(iVar3 + 0xc) = (float)(dVar7 * (double)fVar1 + dVar9);
    fVar1 = FLOAT_8043b1ac;
    if (*(short *)(iVar3 + 0x1c) < 0x10) {
      fVar1 = FLOAT_8043b198;
    }
    *(float *)(iVar3 + 0x10) = (float)(dVar7 * (double)fVar1 + dVar9);
    *(float *)(iVar3 + 0x14) = (float)dVar9;
    if ((double)*(float *)(iVar3 + 0x18) != dVar8) {
      zz_0007cac_((double)*(float *)(iVar3 + 0x18),*(int *)(iVar5 + 0xe0));
    }
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 80192048  FUN_80192048 ====

void FUN_80192048(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if ((*(short *)(pfVar1 + 7) != 0) && (FLOAT_8043b188 != pfVar1[6])) {
      dVar6 = (double)pfVar1[1];
      dVar7 = (double)pfVar1[2];
      gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x24);
    }
    iVar4 = iVar4 + 0x20;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801920fc  FUN_801920fc ====

void FUN_801920fc(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  undefined2 *puVar6;
  int iVar7;
  float *pfVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar5 = FLOAT_8043b1b8;
  fVar4 = FLOAT_8043b1b4;
  fVar1 = FLOAT_8043b1b0;
  iVar11 = 0;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  iVar10 = *(char *)(param_1 + 0x12) * 0x10;
  puVar6 = (undefined2 *)(&DAT_8036eeb4 + iVar10);
  *(undefined2 *)(param_1 + 0x1e) = *puVar6;
  dVar12 = (double)*(float *)(&DAT_8036eeb8 + iVar10);
  *(float *)(param_1 + 100) = *(float *)(&DAT_8036eeb8 + iVar10);
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x3c) = fVar5;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  iVar10 = param_1;
  for (iVar9 = 0; fVar1 = FLOAT_8043b1bc, fVar4 = FLOAT_8043b188, iVar9 < *(char *)(param_1 + 0x13);
      iVar9 = iVar9 + 1) {
    pfVar8 = (float *)(*(int *)(param_1 + 0x54) + iVar11);
    if (iVar9 == 1) {
      *pfVar8 = FLOAT_8043b1c0;
      fVar1 = FLOAT_8043b1c4;
      pfVar8[1] = fVar4;
      fVar5 = FLOAT_8043b190;
      pfVar8[2] = fVar4;
      pfVar8[3] = fVar1;
      pfVar8[4] = fVar1;
      pfVar8[5] = fVar5;
    }
    else {
      pfVar8[2] = FLOAT_8043b188;
      fVar5 = FLOAT_8043b190;
      pfVar8[1] = fVar4;
      *pfVar8 = fVar4;
      pfVar8[3] = fVar1;
      pfVar8[4] = fVar1;
      pfVar8[5] = fVar5;
    }
    sVar2 = puVar6[4];
    *(short *)(pfVar8 + 6) = sVar2;
    iVar3 = DAT_803bb384;
    if (-1 < sVar2) {
      iVar7 = *(int *)(iVar10 + 0xe0);
      *(short *)((int)pfVar8 + 0x1a) = *(short *)(pfVar8 + 6);
      zz_0006fb4_((double)fVar1,(double)fVar4,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,iVar7,
                  (int)*(short *)(pfVar8 + 6),pfVar8,in_r7,in_r8,in_r9,in_r10);
    }
    iVar11 = iVar11 + 0x20;
    puVar6 = puVar6 + 1;
    iVar10 = iVar10 + 4;
  }
  return;
}



// ==== 80192258  FUN_80192258 ====

void FUN_80192258(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (((ushort)(byte)PTR_DAT_80433944[0x2d] & *(ushort *)(param_9 + 0x1e)) == 0) {
    local_1c = *(float *)(param_9 + 0x38);
    local_18 = *(undefined4 *)(param_9 + 0x3c);
    local_14 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_1c = *(float *)(param_9 + 100);
    local_18 = *(undefined4 *)(param_9 + 0x68);
    local_14 = *(undefined4 *)(param_9 + 0x6c);
  }
  local_28 = local_1c;
  local_24 = local_18;
  local_20 = local_14;
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_28,&local_28);
  uVar5 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  iVar1 = DAT_803bb384;
  iVar3 = *(int *)(param_9 + 0x54);
  iVar4 = (int)*(short *)(iVar3 + 0x58);
  if (-1 < iVar4) {
    if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
      iVar4 = iVar4 + 1;
    }
    if (*(short *)(iVar3 + 0x5a) != iVar4) {
      iVar2 = *(int *)(param_9 + 0xe8);
      *(short *)(iVar3 + 0x5a) = (short)iVar4;
      zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,iVar2,
                  (int)(short)iVar4,iVar3,iVar4,in_r8,in_r9,in_r10);
    }
  }
  return;
}



// ==== 80192364  FUN_80192364 ====

void FUN_80192364(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if (-1 < *(short *)(pfVar1 + 6)) {
      zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x24);
    }
    iVar4 = iVar4 + 0x20;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 80192418  FUN_80192418 ====

/* WARNING: Removing unreachable block (ram,0x8019253c) */
/* WARNING: Removing unreachable block (ram,0x80192428) */

void FUN_80192418(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  short *psVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  
  fVar1 = FLOAT_8043b188;
  *(float *)(param_9 + 0xd4) = FLOAT_8043b188;
  iVar7 = *(char *)(param_9 + 0x12) * 0x10;
  iVar8 = 0;
  *(float *)(param_9 + 0xd8) = fVar1;
  dVar10 = DOUBLE_8043b1c8;
  psVar3 = (short *)(&DAT_8036ef54 + iVar7);
  *(undefined2 *)(param_9 + 0x1c) = 0;
  uVar2 = *(undefined4 *)(&DAT_8036ef5c + iVar7);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_8036ef58 + iVar7);
  *(undefined4 *)(param_9 + 0x24) = uVar2;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_8036ef60 + iVar7);
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    iVar5 = *(int *)(param_9 + 0x54) + iVar8;
    *(undefined2 *)(iVar5 + 0x18) = 0;
    pfVar4 = (float *)(int)*psVar3;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar7 + 0xe0),(int)pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_9 + 0x1c) ^
                                                         0x80000000) - dVar10),param_2,param_3,
                        param_4,param_5,param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),
                        pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar7 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe0)
                ,extraout_r4_00,pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0008744_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),pfVar4,param_12,param_13
                        ,param_14,param_15,param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar7 + 0xe0),extraout_r4_01,pfVar4,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007bb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe0)
                ,(undefined4 *)(iVar5 + 0xc),pfVar4,param_12,param_13,param_14,param_15,param_16);
    param_1 = zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(iVar7 + 0xe0));
    iVar8 = iVar8 + 0x20;
    psVar3 = psVar3 + 1;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 80192558  FUN_80192558 ====

/* WARNING: Removing unreachable block (ram,0x80192710) */
/* WARNING: Removing unreachable block (ram,0x80192708) */
/* WARNING: Removing unreachable block (ram,0x80192570) */
/* WARNING: Removing unreachable block (ram,0x80192568) */

void FUN_80192558(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short sVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  
  fVar1 = FLOAT_8043b1d4;
  fVar3 = FLOAT_8043b1d0;
  dVar10 = (double)*(float *)(param_9 + 0xd4);
  dVar11 = (double)*(float *)(param_9 + 0xd8);
  sVar2 = *(short *)(param_9 + 0x1c);
  if ((PTR_DAT_80433944[0x2d] & 1) == 0) {
    dVar8 = (double)FLOAT_8043b19c;
    *(float *)(param_9 + 0xd4) = (float)(dVar10 - dVar8);
    fVar3 = FLOAT_8043b188;
    if ((float)(dVar10 - dVar8) <= fVar1) {
      *(float *)(param_9 + 0xd8) = FLOAT_8043b188;
      *(float *)(param_9 + 0xd4) = fVar3;
    }
  }
  else {
    param_2 = (double)FLOAT_8043b190;
    dVar8 = (double)FLOAT_8043b1d0;
    *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    if (((double)*(float *)(param_9 + 0xd8) < dVar8) &&
       (fVar1 = (float)((double)*(float *)(param_9 + 0xd8) + param_2),
       *(float *)(param_9 + 0xd8) = fVar1, dVar8 <= (double)fVar1)) {
      *(float *)(param_9 + 0xd8) = fVar3;
    }
  }
  if (FLOAT_8043b188 == *(float *)(param_9 + 0xd8)) {
    *(short *)(param_9 + 0x1c) = (char)PTR_DAT_80433944[0x17] + -1;
  }
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_9 + 0x54) + iVar7;
    if (iVar5 != 0) {
      *(ushort *)(iVar4 + 0x18) =
           ~((short)((ushort)((uint)-(int)(char)PTR_DAT_80433944[0x16] >> 0x10) |
                    (ushort)((char)PTR_DAT_80433944[0x16] >> 7)) >> 0xf) & 0x8000;
    }
    if ((int)*(short *)(param_9 + 0x1c) != (int)sVar2) {
      uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(short *)(param_9 + 0x1c) ^
                                                           0x80000000) - DOUBLE_8043b1c8),param_2,
                          param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                          *(int *)(iVar6 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                          param_16);
      uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                  ,param_16);
    }
    if ((double)*(float *)(param_9 + 0xd8) != dVar11) {
      uVar9 = zz_0008744_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,param_6
                          ,param_7,param_8,DAT_803bb384,*(int *)(iVar6 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xe0),extraout_r4_01,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      zz_0007bb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),(undefined4 *)(iVar4 + 0xc),param_11,param_12,param_13,
                  param_14,param_15,param_16);
    }
    if ((double)*(float *)(param_9 + 0xd4) != dVar10) {
      zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(iVar6 + 0xe0));
    }
    iVar7 = iVar7 + 0x20;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 8019272c  FUN_8019272c ====

void FUN_8019272c(int param_1)

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
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if ((FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) && (FLOAT_8043b188 < *(float *)(param_1 + 0xd8))
     ) {
    dVar9 = (double)*(float *)(param_1 + 0x24);
    dVar10 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar9,dVar10,(float *)(param_1 + 0x114));
    iVar7 = 0;
    iVar6 = param_1;
    for (iVar5 = 0; iVar5 < *(char *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
      iVar4 = *(int *)(param_1 + 0x54) + iVar7;
      sVar1 = *(short *)(iVar4 + 0x18);
      iVar3 = (int)sVar1;
      zz_00457d4_('y',(float *)(param_1 + 0x114),afStack_48,sVar1);
      pfVar2 = (float *)(iVar4 + 0xc);
      uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),afStack_48
                  ,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar6 + 0xe0),0x24);
      iVar7 = iVar7 + 0x20;
      iVar6 = iVar6 + 4;
    }
  }
  return;
}



// ==== 801927f4  FUN_801927f4 ====

void FUN_801927f4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  undefined2 *puVar7;
  undefined4 extraout_r4;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double in_f7;
  double in_f8;
  
  fVar5 = FLOAT_8043b1e0;
  fVar4 = FLOAT_8043b1dc;
  fVar3 = FLOAT_8043b190;
  fVar2 = FLOAT_8043b188;
  dVar20 = (double)FLOAT_8043b1d8;
  dVar18 = (double)FLOAT_8043b1dc;
  dVar17 = (double)FLOAT_8043b1e4;
  fVar1 = (float)(dVar20 * (double)(float)((double)CONCAT44(0x43300000,
                                                            (int)*(char *)(param_1 + 0x12) ^
                                                            0x80000000) - DOUBLE_8043b1c8) - dVar20)
  ;
  dVar19 = (double)fVar1;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar4;
  *(float *)(param_1 + 0x6c) = fVar5;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 100);
  *(float *)(param_1 + 0x3c) = (float)((double)*(float *)(param_1 + 0x68) - dVar17);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 100);
  *(float *)(param_1 + 0xa0) = (float)((double)*(float *)(param_1 + 0x68) - dVar17);
  dVar16 = (double)*(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0xa4) = *(float *)(param_1 + 0x6c);
  uVar10 = *(uint *)(param_1 + 0x38);
  *(uint *)(param_1 + 0x20) = uVar10;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(float *)(param_1 + 0xd4) = fVar3;
  *(float *)(param_1 + 0xd8) = fVar2;
  *(undefined2 *)(param_1 + 0x72) = 0;
  iVar8 = (int)*(char *)(param_1 + 0x12);
  uVar15 = zz_01919dc_(param_1,5,*(char *)(param_1 + 0x12));
  iVar14 = 0;
  uVar6 = 0x803c0000;
  iVar13 = 0;
  iVar12 = param_1;
  for (iVar11 = 0; iVar11 < *(char *)(param_1 + 0x13); iVar11 = iVar11 + 1) {
    puVar9 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar14);
    puVar7 = (undefined2 *)(&DAT_8036ef64 + iVar13 + *(char *)(param_1 + 0x12) * 0x3c);
    *(undefined2 *)(puVar9 + 6) = *puVar7;
    *(undefined2 *)((int)puVar9 + 0x1a) = puVar7[1];
    *(undefined2 *)(puVar9 + 7) = puVar7[2];
    *(undefined2 *)((int)puVar9 + 0x1e) = puVar7[3];
    uVar6 = *(undefined4 *)(puVar7 + 6);
    *puVar9 = *(undefined4 *)(puVar7 + 4);
    puVar9[1] = uVar6;
    puVar9[2] = *(undefined4 *)(puVar7 + 8);
    iVar8 = (int)*(short *)(puVar9 + 6);
    uVar15 = zz_0006fb4_(uVar15,dVar16,dVar17,dVar18,dVar19,dVar20,in_f7,in_f8,DAT_803bb384,
                         *(int *)(iVar12 + 0xe0),iVar8,uVar10,in_r7,in_r8,in_r9,in_r10);
    iVar14 = iVar14 + 0x20;
    iVar13 = iVar13 + 0x14;
    iVar12 = iVar12 + 4;
    uVar6 = extraout_r4;
  }
  zz_0192988_(uVar15,dVar16,dVar17,dVar18,dVar19,dVar20,in_f7,in_f8,param_1,uVar6,iVar8,uVar10,in_r7
              ,in_r8,in_r9,in_r10);
  return;
}



// ==== 80192988  zz_0192988_ ====

/* WARNING: Removing unreachable block (ram,0x80192ca8) */
/* WARNING: Removing unreachable block (ram,0x80192ca0) */
/* WARNING: Removing unreachable block (ram,0x801929a0) */
/* WARNING: Removing unreachable block (ram,0x80192998) */

void zz_0192988_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  undefined4 extraout_r4;
  uint extraout_r4_00;
  uint extraout_r4_01;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  double local_48;
  double local_40;
  
  fVar3 = FLOAT_8043b188;
  dVar14 = (double)*(float *)(param_9 + 0xd4);
  dVar13 = (double)*(float *)(param_9 + 0xd8);
  if (PTR_DAT_80433944[0x17] == '\0') {
    if (((PTR_DAT_80433944[0x2c] | PTR_DAT_80433944[0x2e]) & 8) == 0) {
      local_58 = *(float *)(param_9 + 0x38);
      local_54 = *(undefined4 *)(param_9 + 0x3c);
      local_50 = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    }
    else {
      if ((PTR_DAT_80433944[0x2e] & 8) != 0) {
        bVar1 = *(byte *)(param_9 + 0x12);
        param_12 = (uint)bVar1;
        if ((bVar1 != PTR_DAT_80433944[0x15]) || ((PTR_DAT_80433944[0x2c] & 8) == 0)) {
          if (bVar1 == PTR_DAT_80433944[0x15]) {
            dVar12 = (double)FLOAT_8043b188;
            if (dVar14 <= dVar12) {
              local_58 = *(float *)(param_9 + 0x38);
              local_54 = *(undefined4 *)(param_9 + 0x3c);
              local_50 = *(undefined4 *)(param_9 + 0x40);
              *(float *)(param_9 + 0x20) = local_58;
              *(undefined4 *)(param_9 + 0x24) = local_54;
              *(undefined4 *)(param_9 + 0x28) = local_50;
            }
            else {
              fVar2 = *(float *)(param_9 + 0xd4) - FLOAT_8043b1a8;
              *(float *)(param_9 + 0xd4) = fVar2;
              if ((double)fVar2 < dVar12) {
                *(float *)(param_9 + 0xd4) = fVar3;
              }
              local_58 = *(float *)(param_9 + 100);
              local_54 = *(undefined4 *)(param_9 + 0x68);
              local_50 = *(undefined4 *)(param_9 + 0x6c);
            }
          }
          else {
            local_58 = *(float *)(param_9 + 0x9c);
            local_54 = *(undefined4 *)(param_9 + 0xa0);
            local_50 = *(undefined4 *)(param_9 + 0xa4);
            *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
          }
          goto LAB_80192b1c;
        }
      }
      local_58 = *(float *)(param_9 + 100);
      local_54 = *(undefined4 *)(param_9 + 0x68);
      local_50 = *(undefined4 *)(param_9 + 0x6c);
      *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    }
  }
  else {
    local_58 = *(float *)(param_9 + 0x9c);
    local_54 = *(undefined4 *)(param_9 + 0xa0);
    local_50 = *(undefined4 *)(param_9 + 0xa4);
    *(float *)(param_9 + 0x20) = local_58;
    *(undefined4 *)(param_9 + 0x24) = local_54;
    *(undefined4 *)(param_9 + 0x28) = local_50;
    *(float *)(param_9 + 0xd4) = fVar3;
  }
LAB_80192b1c:
  gnt4_PSVECSubtract_bl(&local_58,(float *)(param_9 + 0x20),&local_58);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_58,&local_58);
  pfVar5 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar5,&local_58,pfVar5);
  dVar12 = DOUBLE_8043b1c8;
  uVar6 = (uint)*(byte *)(param_9 + 0x12);
  if (*(byte *)(param_9 + 0x12) == PTR_DAT_80433944[0x15]) {
    *(float *)(param_9 + 0xd8) = FLOAT_8043b190;
    local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x72)) ^ 0x80000000);
    iVar8 = (int)((float)(local_48 - dVar12) + FLOAT_8043b1e8);
    local_40 = (double)(longlong)iVar8;
    *(short *)(param_9 + 0x72) = (short)iVar8;
  }
  else {
    *(float *)(param_9 + 0xd8) = FLOAT_8043b188;
    local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x72)) ^ 0x80000000);
    iVar8 = (int)((float)(local_40 - dVar12) + FLOAT_8043b1ec);
    local_48 = (double)(longlong)iVar8;
    *(short *)(param_9 + 0x72) = (short)iVar8;
  }
  iVar9 = 0;
  iVar8 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    iVar4 = *(int *)(param_9 + 0x54);
    if (((double)*(float *)(param_9 + 0xd8) != dVar13) && (iVar7 == 2)) {
      uVar10 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),dVar12,param_3,param_4,param_5,param_6
                           ,param_7,param_8,DAT_803bb384,*(int *)(iVar8 + 0xe0),pfVar5,param_12,
                           param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar8 + 0xe0),extraout_r4,pfVar5,param_12,param_13,param_14,param_15,
                  param_16);
      uVar6 = extraout_r4_00;
    }
    dVar11 = (double)*(float *)(param_9 + 0xd4);
    if (dVar11 != dVar14) {
      if (iVar7 == 1) {
        if ((double)FLOAT_8043b190 == dVar14) {
          zz_0007c54_(dVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0xe0),uVar6,pfVar5,param_12,param_13,param_14,param_15,
                      param_16);
        }
        else if ((double)FLOAT_8043b190 == dVar11) {
          pfVar5 = (float *)(int)*(short *)(iVar4 + iVar9 + 0x18);
          zz_0006fb4_(dVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                      *(int *)(iVar8 + 0xe0),(int)pfVar5,param_12,param_13,param_14,param_15,
                      param_16);
        }
      }
      zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(iVar8 + 0xe0));
      uVar6 = extraout_r4_01;
    }
    iVar9 = iVar9 + 0x20;
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 80192cc4  FUN_80192cc4 ====

/* WARNING: Removing unreachable block (ram,0x80192dc4) */
/* WARNING: Removing unreachable block (ram,0x80192cd4) */

void FUN_80192cc4(int param_1)

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
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar10;
  float afStack_58 [13];
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    dVar8 = (double)*(float *)(param_1 + 0x24);
    dVar9 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
    dVar10 = (double)FLOAT_8043b190;
    iVar6 = 0;
    iVar5 = param_1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      zz_00455fc_((float *)(param_1 + 0x114),afStack_58,pfVar3);
      zz_00457d4_('z',afStack_58,afStack_58,*(short *)((int)pfVar3 + 0x1e));
      pfVar1 = afStack_58;
      iVar2 = (int)*(short *)(pfVar3 + 7);
      uVar7 = zz_00457d4_('x',pfVar1,pfVar1,*(short *)(pfVar3 + 7));
      if (iVar4 == 1) {
        pfVar1 = afStack_58;
        iVar2 = (int)*(short *)(param_1 + 0x72);
        uVar7 = zz_00457d4_('y',pfVar1,pfVar1,*(short *)(param_1 + 0x72));
      }
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_58,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      if (dVar10 == (double)*(float *)(param_1 + 0xd4)) {
        zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)((int)pfVar3 + 0x1a));
      }
      else {
        zz_00097b4_(*(int *)(iVar5 + 0xe0),0x24);
      }
      iVar6 = iVar6 + 0x20;
      iVar5 = iVar5 + 4;
    }
  }
  return;
}



// ==== 80192de0  FUN_80192de0 ====

/* WARNING: Removing unreachable block (ram,0x80192fe0) */
/* WARNING: Removing unreachable block (ram,0x80192df0) */

void FUN_80192de0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  size_t sVar5;
  int iVar6;
  undefined4 extraout_r4;
  float *pfVar7;
  undefined4 *puVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar9;
  uint uVar10;
  char *pcVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  char local_49 [9];
  undefined4 local_40;
  uint uStack_3c;
  
  iVar1 = 999999;
  *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(*(int *)(param_9 + 0x8c) + 0xd4);
  iVar3 = *(char *)(param_9 + 0x12) * 0xc;
  puVar8 = (undefined4 *)(&DAT_8036f040 + iVar3);
  uVar4 = *(undefined4 *)(&DAT_8036f044 + iVar3);
  *(undefined4 *)(param_9 + 0x20) = *puVar8;
  *(undefined4 *)(param_9 + 0x24) = uVar4;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_8036f048 + iVar3);
  if (*(int *)(&DAT_8036f554 + *(char *)(param_9 + 0x12) * 4) < 999999) {
    iVar1 = *(int *)(&DAT_8036f554 + *(char *)(param_9 + 0x12) * 4);
  }
  sprintf(local_49 + 1,&DAT_8043b1f0,iVar1);
  sVar5 = strlen(local_49 + 1);
  *(char *)(param_9 + 0x13) = (char)sVar5 + '\x01';
  dVar14 = (double)FLOAT_8043b190;
  pcVar11 = local_49;
  iVar3 = 0;
  iVar1 = param_9;
  for (uVar10 = 0; pcVar11 = pcVar11 + 1, (int)uVar10 < (int)*(char *)(param_9 + 0x13);
      uVar10 = uVar10 + 1) {
    iVar6 = (int)(-uVar10 | uVar10) >> 0x1f;
    pfVar9 = (float *)(*(int *)(param_9 + 0x54) + iVar3);
    fVar2 = (float)(&DAT_8036f01c)[iVar6 * -5];
    pfVar9[4] = fVar2;
    pfVar9[3] = fVar2;
    pfVar9[5] = (float)dVar14;
    fVar2 = (float)(&DAT_8036f024)[iVar6 * -5];
    *pfVar9 = (float)(&DAT_8036f020)[iVar6 * -5];
    pfVar9[1] = fVar2;
    pfVar9[2] = (float)(&DAT_8036f028)[iVar6 * -5];
    pfVar7 = (float *)(&DAT_8036f018)[iVar6 * -5];
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar1 + 0xe0),(int)pfVar7,puVar8,in_r7,in_r8,in_r9,in_r10);
    dVar13 = DOUBLE_8043b1c8;
    if (uVar10 != 0) {
      iVar6 = (int)pcVar11[-1];
      fVar2 = FLOAT_8043b188;
      if ((0x2f < iVar6) && (iVar6 < 0x3a)) {
        fVar2 = (float)((double)CONCAT44(0x43300000,iVar6 - 0x30U ^ 0x80000000) - DOUBLE_8043b1c8);
      }
      local_40 = 0x43300000;
      param_4 = (double)FLOAT_8043b1f4;
      uStack_3c = ((uVar10 - 1) * 2 + 1) - (*(char *)(param_9 + 0x13) + -1) ^ 0x80000000;
      param_2 = (double)(float)(param_4 *
                               (double)(float)((double)CONCAT44(0x43300000,uStack_3c) -
                                              DOUBLE_8043b1c8));
      *pfVar9 = (float)(param_2 * (double)FLOAT_8043b1c4);
      uVar12 = zz_00086b8_((double)fVar2,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar1 + 0xe0),pfVar7,puVar8,in_r7,in_r8,in_r9,
                           in_r10);
      zz_0007c30_(uVar12,param_2,dVar13,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar1 + 0xe0),extraout_r4,pfVar7,puVar8,in_r7,in_r8,in_r9,in_r10);
      param_3 = dVar13;
    }
    param_1 = zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(iVar1 + 0xe0));
    iVar3 = iVar3 + 0x20;
    iVar1 = iVar1 + 4;
  }
  zz_0192ffc_(param_9);
  return;
}



// ==== 80192ffc  zz_0192ffc_ ====

void zz_0192ffc_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  fVar1 = *(float *)(param_1 + 0xd4);
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0xd4);
  if (*(float *)(param_1 + 0xd4) != fVar1) {
    iVar3 = param_1;
    for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
      zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(iVar3 + 0xe0));
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 80193080  FUN_80193080 ====

void FUN_80193080(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  if (FLOAT_8043b188 < *(float *)(param_9 + 0xd4)) {
    zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
                (float *)(param_9 + 0x20));
    iVar4 = 0;
    iVar3 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x24);
      iVar4 = iVar4 + 0x20;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 80193138  FUN_80193138 ====

/* WARNING: Removing unreachable block (ram,0x80193218) */
/* WARNING: Removing unreachable block (ram,0x80193148) */

void FUN_80193138(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  
  *(undefined4 *)(param_9 + 0x14) = 0xffffffff;
  iVar8 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  fVar1 = FLOAT_8043b188;
  psVar7 = &DAT_8036f064;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  fVar2 = FLOAT_8043b1f8;
  dVar9 = (double)FLOAT_8043b1f8;
  *(float *)(param_9 + 0xd4) = fVar1;
  fVar1 = FLOAT_8043b1fc;
  *(float *)(param_9 + 100) = fVar2;
  dVar10 = (double)FLOAT_8043b190;
  *(float *)(param_9 + 0x38) = fVar1;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    uVar3 = *(undefined4 *)(psVar7 + 2);
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    puVar4[4] = uVar3;
    puVar4[3] = uVar3;
    puVar4[5] = (float)dVar10;
    *(short *)(puVar4 + 6) = psVar7[1];
    uVar3 = *(undefined4 *)(psVar7 + 6);
    *puVar4 = *(undefined4 *)(psVar7 + 4);
    puVar4[1] = uVar3;
    puVar4[2] = *(undefined4 *)(psVar7 + 8);
    dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_803bb384,*(int *)(iVar6 + 0xe0),(int)*psVar7,param_12,param_13,
                                param_14,param_15,param_16);
    iVar8 = iVar8 + 0x20;
    psVar7 = psVar7 + 10;
    iVar6 = iVar6 + 4;
  }
  zz_0193234_(param_9);
  return;
}



// ==== 80193234  zz_0193234_ ====

/* WARNING: Removing unreachable block (ram,0x80193410) */
/* WARNING: Removing unreachable block (ram,0x80193244) */

void zz_0193234_(int param_1)

{
  float fVar1;
  ushort uVar3;
  float *pfVar2;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  fVar1 = FLOAT_8043b188;
  dVar9 = (double)*(float *)(param_1 + 0xd4);
  if (((PTR_DAT_80433944[0x2d] | PTR_DAT_80433944[0x2c] & PTR_DAT_80433944[0x2e]) & 8) == 0) {
    dVar8 = (double)FLOAT_8043b188;
    if (dVar9 <= dVar8) {
      uVar3 = 0;
      *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
      fVar1 = *(float *)(param_1 + 0x38);
      *(float *)(param_1 + 0x20) = fVar1;
    }
    else {
      dVar7 = (double)FLOAT_8043b1a8;
      *(float *)(param_1 + 0xd4) = (float)(dVar9 - dVar7);
      if ((double)(float)(dVar9 - dVar7) < dVar8) {
        *(float *)(param_1 + 0xd4) = fVar1;
      }
      fVar1 = *(float *)(param_1 + 100);
      uVar3 = 0;
    }
  }
  else {
    *(float *)(param_1 + 0xd4) = FLOAT_8043b190;
    fVar1 = *(float *)(param_1 + 100);
    if ((PTR_DAT_80433944[0x2d] & 8) == 0) {
      uVar3 = 2;
    }
    else {
      uVar3 = 0x20;
    }
  }
  *(float *)(param_1 + 0x20) =
       FLOAT_8043b1a8 * (fVar1 - *(float *)(param_1 + 0x20)) + *(float *)(param_1 + 0x20);
  if ((int)(char)PTR_DAT_80433944[0x15] != *(int *)(param_1 + 0x14)) {
    *(int *)(param_1 + 0x14) = (int)(char)PTR_DAT_80433944[0x15];
    *(undefined2 *)(param_1 + 0x1c) = 0x20;
  }
  if ((*(ushort *)(param_1 + 0x1c) & uVar3) == 0) {
    *(undefined2 *)(param_1 + 0x1e) = 1;
  }
  else {
    *(undefined2 *)(param_1 + 0x1e) = 0x1f;
  }
  iVar6 = 0;
  *(ushort *)(param_1 + 0x1e) =
       *(ushort *)(param_1 + 0x1e) &
       (ushort)*(undefined4 *)(&DAT_8036f0c8 + (char)PTR_DAT_80433944[0x15] * 4);
  iVar5 = param_1;
  for (iVar4 = 0; dVar8 = DOUBLE_8043b1c8, iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    if (iVar4 == 0) {
      *(short *)(pfVar2 + 6) = *(short *)(pfVar2 + 6) + -0x200;
      *pfVar2 = FLOAT_8043b1d8 *
                (float)((double)CONCAT44(0x43300000,(int)(char)PTR_DAT_80433944[0x15] ^ 0x80000000)
                       - dVar8) + *(float *)(param_1 + 0x20);
    }
    if ((double)*(float *)(param_1 + 0xd4) != dVar9) {
      zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(iVar5 + 0xe0));
    }
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 80193438  FUN_80193438 ====

void FUN_80193438(int param_1)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
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
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    iVar3 = 0;
    iVar5 = 0;
    iVar4 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar3) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar3) != 0) {
        pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
        dVar7 = (double)pfVar2[1];
        dVar8 = (double)pfVar2[2];
        gnt4_PSMTXTrans_bl((double)*pfVar2,dVar7,dVar8,afStack_48);
        iVar1 = (int)*(short *)(pfVar2 + 6);
        zz_00457d4_('z',afStack_48,afStack_48,*(short *)(pfVar2 + 6));
        pfVar2 = pfVar2 + 3;
        uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),
                    afStack_48,(undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,in_r10);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),0x24);
      }
      iVar5 = iVar5 + 0x20;
      iVar4 = iVar4 + 4;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 80193508  FUN_80193508 ====

/* WARNING: Removing unreachable block (ram,0x80193654) */
/* WARNING: Removing unreachable block (ram,0x80193518) */

void FUN_80193508(int param_1,undefined4 param_2,int param_3,uint param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *extraout_r4;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar15;
  
  fVar2 = FLOAT_8043b188;
  dVar14 = (double)FLOAT_8043b188;
  iVar10 = 0;
  puVar5 = (undefined4 *)0x803c0000;
  *(float *)(param_1 + 100) = FLOAT_8043b188;
  fVar3 = FLOAT_8043b200;
  iVar9 = 0;
  *(float *)(param_1 + 0x68) = fVar2;
  dVar13 = (double)FLOAT_8043b204;
  *(float *)(param_1 + 0x6c) = fVar3;
  fVar3 = FLOAT_8043b190;
  dVar11 = (double)FLOAT_8043b208;
  dVar15 = (double)FLOAT_8043b190;
  *(float *)(param_1 + 0x38) = (float)(dVar13 + (double)*(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 100);
  dVar12 = (double)*(float *)(param_1 + 0x68);
  *(float *)(param_1 + 0xa0) = (float)(dVar12 - dVar11);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(float *)(param_1 + 0xd4) = fVar3;
  *(float *)(param_1 + 0xd8) = fVar2;
  iVar8 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    cVar1 = *(char *)(param_1 + 0x12);
    puVar5 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar10);
    puVar5[3] = (float)dVar15;
    *(undefined2 *)(puVar5 + 6) = 0;
    puVar6 = (undefined2 *)(&DAT_8036f0d4 + iVar9 + cVar1 * 0x40);
    *(undefined2 *)((int)puVar5 + 0x1a) = 0;
    *(undefined2 *)(puVar5 + 7) = *puVar6;
    *(undefined2 *)((int)puVar5 + 0x1e) = puVar6[1];
    uVar4 = *(undefined4 *)(puVar6 + 4);
    *puVar5 = *(undefined4 *)(puVar6 + 2);
    puVar5[1] = uVar4;
    puVar5[2] = *(undefined4 *)(puVar6 + 6);
    param_3 = (int)*(short *)(puVar5 + 7);
    if (-1 < *(short *)(puVar5 + 7)) {
      dVar12 = (double)zz_0006fb4_(dVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                   *(int *)(iVar8 + 0xe0),param_3,param_4,param_5,param_6,param_7,
                                   param_8);
      puVar5 = extraout_r4;
    }
    iVar10 = iVar10 + 0x20;
    iVar9 = iVar9 + 0x10;
    iVar8 = iVar8 + 4;
  }
  zz_0193670_(dVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,puVar5,param_3,param_4,
              param_5,param_6,param_7,param_8);
  return;
}



// ==== 80193670  zz_0193670_ ====

/* WARNING: Removing unreachable block (ram,0x801939f8) */
/* WARNING: Removing unreachable block (ram,0x801939f0) */
/* WARNING: Removing unreachable block (ram,0x80193688) */
/* WARNING: Removing unreachable block (ram,0x80193680) */

void zz_0193670_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  float *pfVar3;
  uint uVar4;
  uint extraout_r4;
  uint extraout_r4_00;
  undefined4 extraout_r4_01;
  uint extraout_r4_02;
  uint extraout_r4_03;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  longlong local_48;
  
  fVar2 = FLOAT_8043b188;
  if (PTR_DAT_80433944[0x17] == '\0') {
    if (((PTR_DAT_80433944[0x2c] | PTR_DAT_80433944[0x2e]) & 2) == 0) {
      local_58 = *(float *)(param_9 + 0x38);
      local_54 = *(undefined4 *)(param_9 + 0x3c);
      local_50 = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    }
    else {
      if ((PTR_DAT_80433944[0x2e] & 2) != 0) {
        bVar1 = *(byte *)(param_9 + 0x12);
        param_12 = (uint)bVar1;
        if ((bVar1 != PTR_DAT_80433944[0x16]) || ((PTR_DAT_80433944[0x2c] & 2) == 0)) {
          if (bVar1 == PTR_DAT_80433944[0x16]) {
            param_2 = (double)*(float *)(param_9 + 0xd4);
            dVar12 = (double)FLOAT_8043b188;
            if (param_2 <= dVar12) {
              local_58 = *(float *)(param_9 + 0x38);
              local_54 = *(undefined4 *)(param_9 + 0x3c);
              local_50 = *(undefined4 *)(param_9 + 0x40);
              *(float *)(param_9 + 0x20) = local_58;
              *(undefined4 *)(param_9 + 0x24) = local_54;
              *(undefined4 *)(param_9 + 0x28) = local_50;
            }
            else {
              dVar11 = (double)FLOAT_8043b1a8;
              *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar11);
              if ((double)(float)(param_2 - dVar11) < dVar12) {
                *(float *)(param_9 + 0xd4) = fVar2;
              }
              local_58 = *(float *)(param_9 + 100);
              local_54 = *(undefined4 *)(param_9 + 0x68);
              local_50 = *(undefined4 *)(param_9 + 0x6c);
            }
          }
          else {
            local_58 = *(float *)(param_9 + 0x9c);
            local_54 = *(undefined4 *)(param_9 + 0xa0);
            local_50 = *(undefined4 *)(param_9 + 0xa4);
            *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
          }
          goto LAB_801937fc;
        }
      }
      local_58 = *(float *)(param_9 + 100);
      local_54 = *(undefined4 *)(param_9 + 0x68);
      local_50 = *(undefined4 *)(param_9 + 0x6c);
      *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    }
  }
  else {
    local_58 = *(float *)(param_9 + 0x9c);
    local_54 = *(undefined4 *)(param_9 + 0xa0);
    local_50 = *(undefined4 *)(param_9 + 0xa4);
    *(float *)(param_9 + 0x20) = local_58;
    *(undefined4 *)(param_9 + 0x24) = local_54;
    *(undefined4 *)(param_9 + 0x28) = local_50;
    *(float *)(param_9 + 0xd4) = fVar2;
  }
LAB_801937fc:
  gnt4_PSVECSubtract_bl(&local_58,(float *)(param_9 + 0x20),&local_58);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_58,&local_58);
  pfVar3 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar3,&local_58,pfVar3);
  uVar4 = (uint)*(byte *)(param_9 + 0x12);
  dVar12 = (double)*(float *)(param_9 + 0xd8);
  if (*(byte *)(param_9 + 0x12) == PTR_DAT_80433944[0x16]) {
    *(float *)(param_9 + 0xd8) = FLOAT_8043b190;
  }
  else {
    *(float *)(param_9 + 0xd8) = FLOAT_8043b188;
  }
  iVar8 = 0;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    iVar5 = *(int *)(param_9 + 0x54) + iVar8;
    if (-1 < *(short *)(iVar5 + 0x1c)) {
      dVar11 = (double)*(float *)(iVar5 + 0xc);
      *(undefined4 *)(iVar5 + 0xc) = *(undefined4 *)(param_9 + 0xd4);
      if ((iVar6 == 0) &&
         (uVar4 = (uint)*(byte *)(param_9 + 0x12),
         *(byte *)(param_9 + 0x12) != PTR_DAT_80433944[0x16])) {
        *(float *)(iVar5 + 0xc) = *(float *)(iVar5 + 0xc) * FLOAT_8043b20c;
      }
      dVar9 = (double)*(float *)(iVar5 + 0xc);
      if ((dVar9 != dVar11) && (1 < iVar6)) {
        if ((double)FLOAT_8043b190 == dVar9) {
          pfVar3 = (float *)(int)*(short *)(iVar5 + 0x1c);
          zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                      *(int *)(iVar7 + 0xe0),(int)pfVar3,param_12,param_13,param_14,param_15,
                      param_16);
          uVar4 = extraout_r4;
        }
        else if ((double)FLOAT_8043b190 == dVar11) {
          zz_0007c54_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0xe0),uVar4,pfVar3,param_12,param_13,param_14,param_15,
                      param_16);
          uVar4 = extraout_r4_00;
        }
      }
      if (iVar6 == 1) {
        if ((double)*(float *)(param_9 + 0xd8) != dVar12) {
          uVar10 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),pfVar3,
                               param_12,param_13,param_14,param_15,param_16);
          zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0xe0),extraout_r4_01,pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
          uVar4 = extraout_r4_02;
        }
      }
      else if (1 < iVar6) {
        uVar4 = (uint)*(byte *)(param_9 + 0x12);
        if (*(byte *)(param_9 + 0x12) == PTR_DAT_80433944[0x16]) {
          *(short *)(iVar5 + 0x18) = *(short *)(iVar5 + 0x18) + 0x400;
        }
        else {
          *(undefined2 *)(iVar5 + 0x18) = 0;
        }
        dVar12 = zz_0045204_(*(short *)(iVar5 + 0x18));
        param_2 = (double)FLOAT_8043b210;
        dVar12 = (double)(float)(param_2 * dVar12);
        if ((dVar12 <= param_2) && (param_2 = dVar12, dVar12 < (double)FLOAT_8043b218)) {
          param_2 = (double)FLOAT_8043b218;
        }
        local_48 = (longlong)(int)((double)FLOAT_8043b214 * param_2);
        *(short *)(iVar5 + 0x1a) = (short)(int)((double)FLOAT_8043b214 * param_2);
      }
      if ((double)*(float *)(iVar5 + 0xc) != dVar11) {
        zz_0007cac_((double)*(float *)(iVar5 + 0xc),*(int *)(iVar7 + 0xe0));
        uVar4 = extraout_r4_03;
      }
    }
    iVar8 = iVar8 + 0x20;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 80193a14  FUN_80193a14 ====

void FUN_80193a14(int param_1)

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
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    dVar8 = (double)*(float *)(param_1 + 0x24);
    dVar9 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
    iVar6 = 0;
    iVar5 = param_1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      if (-1 < *(short *)(pfVar3 + 7)) {
        zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar3);
        pfVar1 = afStack_48;
        iVar2 = (int)*(short *)((int)pfVar3 + 0x1a);
        uVar7 = zz_00457d4_('z',pfVar1,pfVar1,*(short *)((int)pfVar3 + 0x1a));
        zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),
                    afStack_48,(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
        if (FLOAT_8043b190 == pfVar3[3]) {
          zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)((int)pfVar3 + 0x1e));
        }
        else {
          zz_00097b4_(*(int *)(iVar5 + 0xe0),0x24);
        }
      }
      iVar6 = iVar6 + 0x20;
      iVar5 = iVar5 + 4;
    }
  }
  return;
}



// ==== 80193afc  FUN_80193afc ====

void FUN_80193afc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  double dVar9;
  
  fVar2 = FLOAT_8043b21c;
  fVar1 = FLOAT_8043b188;
  dVar9 = (double)FLOAT_8043b21c;
  piVar7 = &DAT_8036f154;
  iVar8 = 0;
  *(undefined4 *)(param_9 + 0x14) = 0xffffffff;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  fVar1 = FLOAT_8043b220;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x38) = fVar1;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    piVar4 = (int *)(*(int *)(param_9 + 0x54) + iVar8);
    *(undefined2 *)(piVar4 + 6) = 0;
    iVar3 = piVar7[2];
    *piVar4 = piVar7[1];
    piVar4[1] = iVar3;
    piVar4[2] = piVar7[3];
    dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_803bb384,*(int *)(iVar6 + 0xe0),*piVar7,param_12,param_13,
                                param_14,param_15,param_16);
    iVar8 = iVar8 + 0x20;
    piVar7 = piVar7 + 4;
    iVar6 = iVar6 + 4;
  }
  zz_0193bd4_(param_9);
  return;
}



// ==== 80193bd4  zz_0193bd4_ ====

/* WARNING: Removing unreachable block (ram,0x80193db4) */
/* WARNING: Removing unreachable block (ram,0x80193be4) */

void zz_0193bd4_(int param_1)

{
  float fVar1;
  ushort uVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  fVar1 = FLOAT_8043b188;
  dVar9 = (double)*(float *)(param_1 + 0xd4);
  if (((PTR_DAT_80433944[0x2d] | PTR_DAT_80433944[0x2c] & PTR_DAT_80433944[0x2e]) & 2) == 0) {
    dVar8 = (double)FLOAT_8043b188;
    if (dVar9 <= dVar8) {
      uVar2 = 0;
      *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
      fVar1 = *(float *)(param_1 + 0x38);
      *(float *)(param_1 + 0x20) = fVar1;
    }
    else {
      dVar7 = (double)FLOAT_8043b1a8;
      *(float *)(param_1 + 0xd4) = (float)(dVar9 - dVar7);
      if ((double)(float)(dVar9 - dVar7) < dVar8) {
        *(float *)(param_1 + 0xd4) = fVar1;
      }
      fVar1 = *(float *)(param_1 + 100);
      uVar2 = 0;
    }
  }
  else {
    *(float *)(param_1 + 0xd4) = FLOAT_8043b190;
    fVar1 = *(float *)(param_1 + 100);
    if ((PTR_DAT_80433944[0x2d] & 2) == 0) {
      uVar2 = 2;
    }
    else {
      uVar2 = 0x20;
    }
  }
  *(float *)(param_1 + 0x20) =
       FLOAT_8043b1a8 * (fVar1 - *(float *)(param_1 + 0x20)) + *(float *)(param_1 + 0x20);
  if ((int)(char)PTR_DAT_80433944[0x16] != *(int *)(param_1 + 0x14)) {
    *(int *)(param_1 + 0x14) = (int)(char)PTR_DAT_80433944[0x16];
    *(undefined2 *)(param_1 + 0x1c) = 0x20;
  }
  if ((*(ushort *)(param_1 + 0x1c) & uVar2) == 0) {
    *(undefined2 *)(param_1 + 0x1e) = 1;
  }
  else {
    *(undefined2 *)(param_1 + 0x1e) = 3;
  }
  iVar6 = 0;
  iVar5 = param_1;
  for (iVar4 = 0; dVar8 = DOUBLE_8043b1c8, iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    if (iVar4 == 0) {
      *(short *)(pfVar3 + 6) = *(short *)(pfVar3 + 6) + -0x200;
      *pfVar3 = FLOAT_8043b224 *
                (float)((double)CONCAT44(0x43300000,(int)(char)PTR_DAT_80433944[0x16] ^ 0x80000000)
                       - dVar8) + *(float *)(param_1 + 0x20);
    }
    else {
      *(ushort *)(pfVar3 + 6) =
           (short)((ushort)((uint)-(int)(char)PTR_DAT_80433944[0x16] >> 0x10) |
                  (ushort)((char)PTR_DAT_80433944[0x16] >> 7)) >> 0xf & 0x8000;
    }
    if ((double)*(float *)(param_1 + 0xd4) != dVar9) {
      zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(iVar5 + 0xe0));
    }
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 80193ddc  FUN_80193ddc ====

void FUN_80193ddc(int param_1)

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
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    iVar4 = 0;
    iVar6 = 0;
    iVar5 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar4) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar4) != 0) {
        pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
        dVar8 = (double)pfVar3[1];
        dVar9 = (double)pfVar3[2];
        gnt4_PSMTXTrans_bl((double)*pfVar3,dVar8,dVar9,afStack_48);
        pfVar1 = afStack_48;
        iVar2 = (int)*(short *)(pfVar3 + 6);
        uVar7 = zz_00457d4_('z',pfVar1,pfVar1,*(short *)(pfVar3 + 6));
        zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),
                    afStack_48,(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
        zz_00097b4_(*(int *)(iVar5 + 0xe0),0x24);
      }
      iVar6 = iVar6 + 0x20;
      iVar5 = iVar5 + 4;
      iVar4 = iVar4 + 1;
    }
  }
  return;
}



// ==== 80193e9c  FUN_80193e9c ====

void FUN_80193e9c(int param_1,undefined4 param_2,float *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar7;
  int iVar8;
  short *psVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar3 = FLOAT_8043b22c;
  fVar2 = FLOAT_8043b228;
  fVar1 = FLOAT_8043b188;
  dVar14 = (double)FLOAT_8043b188;
  uVar5 = 0x803c0000;
  psVar9 = &DAT_8036f174;
  iVar10 = 0;
  *(float *)(param_1 + 100) = FLOAT_8043b188;
  *(float *)(param_1 + 0x68) = fVar2;
  fVar2 = FLOAT_8043b230;
  *(float *)(param_1 + 0x6c) = fVar3;
  fVar3 = FLOAT_8043b234;
  *(float *)(param_1 + 0x38) = fVar2;
  fVar2 = FLOAT_8043b198;
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x68);
  dVar13 = (double)*(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x9c) = fVar3;
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x6c);
  dVar11 = (double)*(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0xd4) = fVar1;
  *(float *)(param_1 + 0xd8) = fVar2;
  iVar8 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    uVar4 = countLeadingZeros(iVar7);
    puVar6 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar10);
    *(ushort *)(puVar6 + 6) = -((ushort)(uVar4 >> 5) & 1) & 0xc000;
    *(undefined2 *)((int)puVar6 + 0x1a) = 0;
    *(short *)((int)puVar6 + 0x1e) = psVar9[1];
    uVar5 = *(undefined4 *)(psVar9 + 6);
    *puVar6 = *(undefined4 *)(psVar9 + 4);
    puVar6[1] = uVar5;
    puVar6[2] = *(undefined4 *)(psVar9 + 8);
    uVar5 = *(undefined4 *)(psVar9 + 2);
    puVar6[5] = uVar5;
    puVar6[4] = uVar5;
    puVar6[3] = uVar5;
    param_3 = (float *)(int)*psVar9;
    dVar11 = (double)zz_0006fb4_(dVar11,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                 *(int *)(iVar8 + 0xe0),(int)param_3,param_4,param_5,param_6,param_7
                                 ,param_8);
    uVar5 = extraout_r4;
    if (iVar7 == 0) {
      uVar12 = zz_00086b8_((double)FLOAT_8043b190,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                           DAT_803bb384,*(int *)(iVar8 + 0xe0),param_3,param_4,param_5,param_6,
                           param_7,param_8);
      dVar11 = (double)zz_0007c30_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                                   *(int *)(iVar8 + 0xe0),extraout_r4_00,param_3,param_4,param_5,
                                   param_6,param_7,param_8);
      uVar5 = extraout_r4_01;
    }
    iVar10 = iVar10 + 0x20;
    psVar9 = psVar9 + 10;
    iVar8 = iVar8 + 4;
  }
  zz_0193ff4_(dVar11,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,uVar5,param_3,param_4,
              param_5,param_6,param_7,param_8);
  return;
}



// ==== 80193ff4  zz_0193ff4_ ====

void zz_0193ff4_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar4;
  double dVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  double local_18;
  undefined4 local_10;
  uint uStack_c;
  
  if ((PTR_DAT_80433944[0x2c] & 1) == 0) {
    if ((PTR_DAT_80433944[0x2e] & 1) == 0) {
      local_28 = *(float *)(param_9 + 0x38);
      local_24 = *(undefined4 *)(param_9 + 0x3c);
      local_20 = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_28;
      *(undefined4 *)(param_9 + 0x24) = local_24;
      *(undefined4 *)(param_9 + 0x28) = local_20;
    }
    else {
      local_28 = *(float *)(param_9 + 0x9c);
      local_24 = *(undefined4 *)(param_9 + 0xa0);
      local_20 = *(undefined4 *)(param_9 + 0xa4);
    }
  }
  else {
    local_28 = *(float *)(param_9 + 100);
    local_24 = *(undefined4 *)(param_9 + 0x68);
    local_20 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_28,&local_28);
  pfVar3 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar3,&local_28,pfVar3);
  fVar2 = FLOAT_8043b238;
  fVar1 = *(float *)(param_9 + 0xd4) + FLOAT_8043b1c4;
  *(float *)(param_9 + 0xd4) = fVar1;
  if (fVar2 <= fVar1) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar2;
  }
  dVar5 = (double)*(float *)(param_9 + 0xd8);
  if (PTR_DAT_80433944[0x17] != '\0') {
    local_18 = (double)(CONCAT44(0x43300000,(char)PTR_DAT_80433944[0x17] + -1) ^ 0x80000000);
    *(float *)(param_9 + 0xd8) = (float)(local_18 - DOUBLE_8043b1c8);
  }
  *(short *)(*(int *)(param_9 + 0x54) + 0x3a) = *(short *)(*(int *)(param_9 + 0x54) + 0x3a) + -0x100
  ;
  if ((double)*(float *)(param_9 + 0xd8) != dVar5) {
    uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),dVar5,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe4),pfVar3,param_12,
                        param_13,param_14,param_15,param_16);
    uVar4 = zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe4),extraout_r4,pfVar3,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
                ,extraout_r4_00,pfVar3,param_12,param_13,param_14,param_15,param_16);
  }
  local_10 = 0x43300000;
  local_18 = (double)(longlong)(int)*(float *)(param_9 + 0xd4);
  uStack_c = (int)*(float *)(param_9 + 0xd4) ^ 0x80000000;
  uVar4 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_8043b1c8),dVar5
                      ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                      *(int *)(param_9 + 0xe4),pfVar3,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4_01,pfVar3,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801941b8  FUN_801941b8 ====

void FUN_801941b8(int param_1)

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
  iVar6 = 0;
  iVar5 = param_1;
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar3);
    zz_00457d4_('y',afStack_48,afStack_48,*(short *)((int)pfVar3 + 0x1a));
    iVar2 = (int)*(short *)(pfVar3 + 6);
    zz_00457d4_('x',afStack_48,afStack_48,*(short *)(pfVar3 + 6));
    pfVar1 = pfVar3 + 3;
    uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
    zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_48,
                (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)((int)pfVar3 + 0x1e));
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 80194288  FUN_80194288 ====

void FUN_80194288(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int in_r7;
  int in_r8;
  int in_r9;
  int in_r10;
  double dVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar2 = FLOAT_8043b240;
  fVar1 = FLOAT_8043b23c;
  iVar6 = 0;
  dVar10 = (double)FLOAT_8043b240;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  fVar3 = FLOAT_8043b244;
  dVar9 = (double)FLOAT_8043b244;
  *(float *)(param_1 + 0x38) = fVar1;
  fVar1 = FLOAT_8043b188;
  dVar8 = (double)FLOAT_8043b188;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar4 = FLOAT_8043b248;
  *(float *)(param_1 + 0x40) = fVar3;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar3;
  *(float *)(param_1 + 0x9c) = fVar1;
  *(float *)(param_1 + 0xa0) = fVar4;
  *(float *)(param_1 + 0xa4) = fVar3;
  pfVar5 = *(float **)(param_1 + 0x38);
  *(float **)(param_1 + 0x20) = pfVar5;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    pfVar5 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    *(undefined2 *)(pfVar5 + 6) = 0xffff;
    *(short *)((int)pfVar5 + 0x1a) = (short)iVar7 + *(char *)(param_1 + 0x12) * 8;
    fVar2 = FLOAT_8043b190;
    fVar1 = FLOAT_8043b188;
    if (*(short *)((int)pfVar5 + 0x1a) < 0x1e) {
      pfVar5[5] = FLOAT_8043b190;
      pfVar5[4] = fVar2;
      pfVar5[3] = fVar2;
    }
    else if (*(short *)((int)pfVar5 + 0x1a) == 0x1e) {
      dVar8 = (double)FLOAT_8043b188;
      pfVar5[2] = FLOAT_8043b188;
      pfVar5[1] = fVar1;
      *pfVar5 = fVar1;
      pfVar5[5] = fVar2;
      pfVar5[4] = fVar2;
      pfVar5[3] = fVar2;
    }
    iVar6 = iVar6 + 0x20;
  }
  zz_0194388_(dVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,pfVar5,iVar6,iVar7,in_r7,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 80194388  zz_0194388_ ====

void zz_0194388_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,int param_12,int param_13,int param_14,int param_15,int param_16
                )

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  float fVar4;
  undefined *puVar5;
  int iVar6;
  char cVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  float *pfVar11;
  int unaff_r23;
  int iVar12;
  int iVar13;
  short *psVar14;
  uint uVar15;
  int iVar16;
  double dVar17;
  double dVar18;
  undefined8 uVar19;
  char local_68;
  byte bStack_67;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  double local_58;
  undefined4 local_50;
  uint uStack_4c;
  double local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  puVar5 = PTR_DAT_80433944;
  iVar3 = (char)PTR_DAT_80433944[0x14] * 0x80;
  if ((PTR_DAT_80433944[0x2c] & 4) == 0) {
    if (*(float *)(param_9 + 0x20) == *(float *)(param_9 + 0x38)) {
      local_64 = *(float *)(param_9 + 0x38);
      local_60 = *(undefined4 *)(param_9 + 0x3c);
      local_5c = *(undefined4 *)(param_9 + 0x40);
    }
    else {
      local_64 = *(float *)(param_9 + 0x9c);
      local_60 = *(undefined4 *)(param_9 + 0xa0);
      local_5c = *(undefined4 *)(param_9 + 0xa4);
    }
  }
  else {
    local_64 = *(float *)(param_9 + 100);
    local_60 = *(undefined4 *)(param_9 + 0x68);
    local_5c = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_64,(float *)(param_9 + 0x20),&local_64);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_64,&local_64);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_64,(float *)(param_9 + 0x20));
  dVar17 = gnt4_PSVECSquareDistance_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x9c));
  if (dVar17 < (double)FLOAT_8043b24c) {
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  }
  iVar8 = *(int *)(puVar5 + iVar3 + 0x140);
  if (iVar8 != 0) {
    if ((char)puVar5[iVar3 + 0x161] < '\0') {
      iVar13 = 0;
      psVar14 = (short *)0x8036f1a8;
    }
    else {
      param_14 = 0;
      param_12 = 0;
      iVar13 = iVar8 + (char)puVar5[(char)puVar5[iVar3 + 0x161] + iVar3 + 0x14c] * 0x6c;
      uVar10 = (uint)*(char *)(iVar13 + 0x29);
      param_15 = (int)uVar10 >> 0x1f;
      param_16 = param_15 + (uint)(0xf < uVar10);
      param_13 = (param_16 + param_15 + (uint)(0x17 < uVar10)) * 4;
      psVar14 = (short *)(&DAT_8036f19c + param_13);
      unaff_r23 = zz_01cce38_(iVar8,(int)(char)puVar5[(char)puVar5[iVar3 + 0x161] + iVar3 + 0x14c],
                              *(int *)(PTR_DAT_80433934 + 0x120),0);
    }
    *(short *)(param_9 + 0x70) = psVar14[1];
    iVar8 = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    iVar16 = param_9;
    for (iVar12 = 0; iVar12 < *(char *)(param_9 + 0x13); iVar12 = iVar12 + 1) {
      pfVar11 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
      if ((iVar13 == 0) || (0x1d < *(short *)((int)pfVar11 + 0x1a))) {
        if (*(short *)((int)pfVar11 + 0x1a) == 0x1e) {
          *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar12);
          iVar6 = DAT_803bb384;
          sVar1 = *psVar14;
          if ((int)*(short *)(pfVar11 + 6) != (int)sVar1) {
            iVar9 = *(int *)(iVar16 + 0xe0);
            *(short *)(pfVar11 + 6) = sVar1;
            dVar17 = (double)zz_0006fb4_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,iVar6,iVar9,(int)sVar1,param_12,param_13,param_14,
                                         param_15,param_16);
          }
        }
      }
      else {
        iVar6 = (int)*(short *)(iVar13 + *(short *)((int)pfVar11 + 0x1a) * 2 + 0x30);
        if (-1 < iVar6) {
          uVar2 = *(undefined2 *)(*(int *)(puVar5 + iVar3 + 0x140) + iVar6 * 0x20 + 0x870);
          *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar12);
          if (*(char *)(iVar13 + 0x29) < 9) {
            local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)pfVar11 + 0x1a)) ^
                               0x80000000);
            iVar6 = *(char *)(iVar13 + 0x29) * 8;
            uVar15 = 0;
            *pfVar11 = *(float *)(&DAT_8036f1b0 + iVar6) * (float)(local_58 - DOUBLE_8043b1c8) +
                       *(float *)(&DAT_8036f1ac + iVar6);
            fVar4 = FLOAT_8043b250;
            if (('\x03' < *(char *)(iVar13 + 0x29)) &&
               (fVar4 = FLOAT_8043b258, (*(ushort *)((int)pfVar11 + 0x1a) & 1) != 0)) {
              fVar4 = FLOAT_8043b254;
            }
            pfVar11[2] = fVar4;
            param_2 = DOUBLE_8043b1c8;
            param_3 = (double)FLOAT_8043b19c;
            dVar18 = (double)FLOAT_8043b25c;
            uStack_4c = 8U - (int)*(char *)(iVar13 + 0x29) ^ 0x80000000;
            param_4 = (double)FLOAT_8043b260;
            pfVar11[3] = (float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,uStack_4c) -
                                                          DOUBLE_8043b1c8) + dVar18);
            dVar17 = (double)pfVar11[3];
            if ((dVar17 <= param_4) && (param_4 = dVar17, dVar17 < dVar18)) {
              param_4 = dVar18;
            }
            pfVar11[3] = (float)param_4;
            fVar4 = FLOAT_8043b190;
            dVar17 = (double)pfVar11[3];
            pfVar11[4] = pfVar11[3];
            pfVar11[5] = fVar4;
          }
          else {
            uVar10 = (uint)*(short *)((int)pfVar11 + 0x1a);
            param_12 = (int)uVar10 >> 0x1f;
            param_15 = param_12 + (uint)(0x16 < uVar10);
            param_13 = param_12 + (uint)(7 < uVar10);
            uVar15 = param_13 + param_12 + (uint)(0xe < uVar10) + param_15;
            uStack_4c = uVar15 ^ 0x80000000;
            iVar6 = (int)(FLOAT_8043b268 *
                          (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043b1c8) +
                         FLOAT_8043b1c4);
            local_58 = (double)(longlong)iVar6;
            local_48 = (double)(CONCAT44(0x43300000,uVar10 - iVar6) ^ 0x80000000);
            fVar4 = FLOAT_8043b270;
            if ((uVar15 & 1) == 0) {
              fVar4 = FLOAT_8043b26c;
            }
            uStack_3c = uVar15 ^ 0x80000000;
            fVar4 = FLOAT_8043b264 * (float)(local_48 - DOUBLE_8043b1c8) - fVar4;
            param_4 = (double)fVar4;
            local_40 = 0x43300000;
            param_3 = (double)FLOAT_8043b1d4;
            dVar17 = (double)FLOAT_8043b274;
            param_2 = (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043b1c8);
            *pfVar11 = fVar4;
            fVar4 = FLOAT_8043b190;
            dVar17 = -(double)(float)(param_3 * param_2 - dVar17);
            pfVar11[2] = (float)dVar17;
            pfVar11[5] = fVar4;
            pfVar11[4] = fVar4;
            pfVar11[3] = fVar4;
            param_14 = param_12;
          }
          local_50 = 0x43300000;
          local_68 = (char)((ushort)uVar2 >> 8);
          pfVar11[1] = FLOAT_8043b1c4;
          bStack_67 = (byte)uVar2;
          uVar10 = *(uint *)((&PTR_DAT_80350d0c)[local_68] + (uint)bStack_67 * 4);
          if ((int)*(short *)(pfVar11 + 6) != uVar10) {
            uVar19 = zz_0006fb4_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar16 + 0xe0),0x6e,param_12,param_13,
                                 param_14,param_15,param_16);
            iVar6 = DAT_803bb334;
            iVar9 = *(int *)(iVar16 + 0xe0);
            param_12 = 0;
            *(short *)(pfVar11 + 6) = (short)uVar10;
            zz_000761c_(uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,iVar9,
                        (char *)(uVar10 & 0xff),0,param_13,param_14,param_15,param_16);
            zz_0007d8c_(*(int *)(iVar16 + 0xe0),7);
          }
          if (*(short *)((int)pfVar11 + 0x1a) < unaff_r23) {
            uStack_3c = uVar15 ^ 0x80000000;
            local_40 = 0x43300000;
            param_3 = (double)FLOAT_8043b278;
            iVar6 = (int)(param_3 *
                         (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043b1c8));
            local_48 = (double)(longlong)iVar6;
            cVar7 = -1 - (char)iVar6;
            param_2 = DOUBLE_8043b1c8;
            fVar4 = FLOAT_8043b190;
          }
          else {
            cVar7 = '\0';
            fVar4 = FLOAT_8043b27c;
          }
          *(char *)(*(int *)(iVar16 + 0xe0) + 0x1e) = cVar7;
          *(char *)(*(int *)(iVar16 + 0xe0) + 0x1d) = cVar7;
          *(char *)(*(int *)(iVar16 + 0xe0) + 0x1c) = cVar7;
          dVar17 = (double)zz_0007cac_((double)fVar4,*(int *)(iVar16 + 0xe0));
        }
      }
      iVar8 = iVar8 + 0x20;
      iVar16 = iVar16 + 4;
    }
  }
  return;
}



// ==== 801948e4  FUN_801948e4 ====

/* WARNING: Removing unreachable block (ram,0x80194a48) */

void FUN_801948e4(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if ((*(short *)(param_1 + 0x1c) != 0) &&
     (*(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x140) != 0)) {
    dVar11 = (double)*(float *)(param_1 + 0x24);
    dVar12 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar11,dVar12,(float *)(param_1 + 0x114));
    iVar5 = (int)*(short *)(param_1 + 0x70);
    zz_00457d4_('x',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70)
               );
    iVar9 = 0;
    iVar8 = param_1;
    for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
      if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar7) != 0) {
        pfVar6 = (float *)(*(int *)(param_1 + 0x54) + iVar9);
        zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar6);
        pfVar4 = pfVar6 + 3;
        uVar10 = zz_00456a0_(afStack_48,afStack_48,pfVar4);
        zz_00076d0_(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar8 + 0xe0),
                    afStack_48,(undefined *)pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
        if (*(short *)((int)pfVar6 + 0x1a) < 0x1e) {
          iVar2 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
          if (iVar2 == 0) {
            iVar2 = 0;
          }
          else {
            iVar2 = *(int *)(iVar2 + 0x10);
          }
          if (iVar2 != 0) {
            dVar11 = (double)FLOAT_8043b1c4;
            dVar12 = (double)FLOAT_8043b280;
            FUN_800455b0((double)FLOAT_8043b188,dVar11,dVar12,afStack_48,afStack_48);
            pfVar4 = afStack_48;
            iVar5 = (int)-*(short *)(param_1 + 0x70);
            uVar10 = zz_00457d4_('x',pfVar4,pfVar4,-*(short *)(param_1 + 0x70));
            if (iVar2 == 0) {
              pfVar4 = (float *)&DAT_8043b28c;
              gnt4___assert_bl(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_8043b284,
                               0x495,&DAT_8043b28c,iVar5,in_r7,in_r8,in_r9,in_r10);
            }
            uVar10 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
            *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
            if (iVar2 != 0) {
              uVar3 = *(uint *)(iVar2 + 0x14);
              bVar1 = false;
              if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
                bVar1 = true;
              }
              if (!bVar1) {
                gnt4_HSD_JObjSetMtxDirtySub_bl
                          (uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,uVar3,
                           (undefined *)pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
              }
            }
          }
          zz_00097b4_(*(int *)(iVar8 + 0xe0),0x25);
        }
        else if (*(short *)(pfVar6 + 6) == 0x91) {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),0x24);
        }
        else {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),1);
        }
      }
      iVar9 = iVar9 + 0x20;
      iVar8 = iVar8 + 4;
    }
  }
  return;
}



// ==== 80194aec  FUN_80194aec ====

void FUN_80194aec(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int *piVar6;
  undefined4 extraout_r4;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  double dVar11;
  double dVar12;
  
  fVar2 = FLOAT_8043b29c;
  fVar1 = FLOAT_8043b298;
  uVar5 = 0x80370000;
  dVar12 = (double)FLOAT_8043b298;
  dVar11 = (double)FLOAT_8043b29c;
  piVar10 = &DAT_8036f1f4;
  iVar9 = 0;
  *(float *)(param_9 + 0xd4) = FLOAT_8043b188;
  *(float *)(param_9 + 0x38) = FLOAT_8043b294;
  fVar3 = FLOAT_8043b2a0;
  *(float *)(param_9 + 0x3c) = fVar1;
  *(float *)(param_9 + 0x40) = fVar2;
  *(float *)(param_9 + 100) = fVar3;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  iVar8 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    iVar4 = piVar10[2];
    piVar6 = (int *)(*(int *)(param_9 + 0x54) + iVar9);
    *piVar6 = piVar10[1];
    piVar6[1] = iVar4;
    piVar6[2] = piVar10[3];
    param_11 = *piVar10;
    dVar11 = (double)zz_0006fb4_(dVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar8 + 0xe0),param_11,param_12,param_13,
                                 param_14,param_15,param_16);
    piVar10 = piVar10 + 4;
    iVar9 = iVar9 + 0x20;
    iVar8 = iVar8 + 4;
    uVar5 = extraout_r4;
  }
  zz_0194bd4_(dVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar5,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80194bd4  zz_0194bd4_ ====

/* WARNING: Removing unreachable block (ram,0x80194e08) */
/* WARNING: Removing unreachable block (ram,0x80194be4) */

void zz_0194bd4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char cVar2;
  float fVar3;
  undefined *puVar4;
  float *pfVar5;
  size_t sVar6;
  int iVar7;
  undefined4 extraout_r4;
  float *pfVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  char local_48 [4];
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint uStack_34;
  
  fVar3 = FLOAT_8043b188;
  puVar4 = PTR_DAT_80433944;
  dVar15 = (double)*(float *)(param_9 + 0xd4);
  cVar1 = PTR_DAT_80433944[0x14];
  if ((PTR_DAT_80433944[0x2c] & 4) == 0) {
    dVar13 = (double)FLOAT_8043b188;
    if (dVar15 <= dVar13) {
      local_44 = *(float *)(param_9 + 0x38);
      local_40 = *(undefined4 *)(param_9 + 0x3c);
      local_3c = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_44;
      *(undefined4 *)(param_9 + 0x24) = local_40;
      *(undefined4 *)(param_9 + 0x28) = local_3c;
    }
    else {
      dVar12 = (double)FLOAT_8043b19c;
      *(float *)(param_9 + 0xd4) = (float)(dVar15 - dVar12);
      if ((double)(float)(dVar15 - dVar12) < dVar13) {
        *(float *)(param_9 + 0xd4) = fVar3;
      }
      local_44 = *(float *)(param_9 + 100);
      local_40 = *(undefined4 *)(param_9 + 0x68);
      local_3c = *(undefined4 *)(param_9 + 0x6c);
    }
  }
  else {
    *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    local_44 = *(float *)(param_9 + 100);
    local_40 = *(undefined4 *)(param_9 + 0x68);
    local_3c = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_44,(float *)(param_9 + 0x20),&local_44);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_44,&local_44);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_44,(float *)(param_9 + 0x20));
  if ((double)*(float *)(param_9 + 0xd4) != dVar15) {
    iVar10 = param_9;
    for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
      fVar3 = FLOAT_8043b190;
      if (iVar9 == 0) {
        fVar3 = FLOAT_8043b2a4;
      }
      zz_0007cac_((double)(*(float *)(param_9 + 0xd4) * fVar3),*(int *)(iVar10 + 0xe0));
      iVar10 = iVar10 + 4;
    }
  }
  if ((FLOAT_8043b188 < *(float *)(param_9 + 0xd4)) &&
     (cVar2 = puVar4[cVar1 * 0x80 + 0x161], -1 < cVar2)) {
    pfVar5 = (float *)((char)puVar4[(int)cVar2 + cVar1 * 0x80 + 0x14c] + 1);
    pfVar8 = (float *)0x14;
    if ((int)pfVar5 < 0x14) {
      pfVar8 = pfVar5;
    }
    sprintf(local_48,&DAT_8043b1f0);
    sVar6 = strlen(local_48);
    *(short *)(param_9 + 0x1c) = (short)sVar6;
    pcVar11 = local_48;
    iVar10 = param_9;
    for (iVar9 = 0; iVar9 < *(short *)(param_9 + 0x1c); iVar9 = iVar9 + 1) {
      iVar7 = (int)*pcVar11;
      fVar3 = FLOAT_8043b188;
      if ((0x2f < iVar7) && (iVar7 < 0x3a)) {
        uStack_34 = iVar7 - 0x30U ^ 0x80000000;
        local_38 = 0x43300000;
        fVar3 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043b1c8);
      }
      uVar14 = zz_00086b8_((double)fVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar10 + 0xe8),pfVar8,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar10 + 0xe8),extraout_r4,pfVar8,param_12,param_13,param_14,param_15,
                  param_16);
      pcVar11 = pcVar11 + 1;
      iVar10 = iVar10 + 4;
    }
  }
  return;
}



// ==== 80194e24  FUN_80194e24 ====

void FUN_80194e24(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  undefined *puVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
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
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [14];
  
  puVar2 = PTR_DAT_80433944;
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    dVar9 = (double)*(float *)(param_1 + 0x24);
    dVar10 = (double)*(float *)(param_1 + 0x28);
    iVar1 = (char)PTR_DAT_80433944[0x14] * 0x80;
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar9,dVar10,(float *)(param_1 + 0x114));
    if ((char)puVar2[iVar1 + 0x161] < '\0') {
      iVar4 = 1;
    }
    else {
      iVar4 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -2;
    }
    iVar7 = 0;
    iVar6 = param_1;
    for (iVar5 = 0; iVar5 < iVar4; iVar5 = iVar5 + 1) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar7);
      uVar8 = zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar3);
      zz_00076d0_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),afStack_50
                  ,(undefined *)pfVar3,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar6 + 0xe0),0x24);
      iVar7 = iVar7 + 0x20;
      iVar6 = iVar6 + 4;
    }
    if (*(int *)(puVar2 + iVar1 + 0x140) != 0) {
      if ((char)puVar2[iVar1 + 0x161] < '\0') {
        sprintf(&DAT_803d5eb8,&DAT_802b3620);
      }
      else {
        strcpy(&DAT_803d5eb8,
               (char *)(*(int *)(puVar2 + iVar1 + 0x140) +
                       (char)puVar2[(char)puVar2[iVar1 + 0x161] + iVar1 + 0x14c] * 0x6c));
      }
      local_5c = FLOAT_8043b2a8;
      local_58 = FLOAT_8043b2ac;
      local_54 = FLOAT_8043b1c4;
      local_60 = FLOAT_8043b190;
      local_64 = FLOAT_8043b190;
      local_68 = FLOAT_8043b190;
      FUN_801c53dc((double)*(float *)(param_1 + 0xd4),(double)FLOAT_8043b2b0,(double)FLOAT_8043b278,
                   (float *)(param_1 + 0x114),&local_5c,&local_68,2,0x1e,(short *)&DAT_803d5eb8);
    }
  }
  return;
}



// ==== 80194fac  FUN_80194fac ====

void FUN_80194fac(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar4 = FLOAT_8043b2bc;
  fVar3 = FLOAT_8043b2b8;
  fVar2 = FLOAT_8043b2b4;
  dVar13 = (double)FLOAT_8043b2b4;
  dVar12 = (double)FLOAT_8043b2b8;
  dVar11 = (double)FLOAT_8043b2bc;
  iVar10 = 0;
  *(float *)(param_1 + 0xd4) = FLOAT_8043b188;
  fVar1 = FLOAT_8043b200;
  *(float *)(param_1 + 0x38) = fVar2;
  *(float *)(param_1 + 0x3c) = fVar3;
  *(float *)(param_1 + 0x40) = fVar4;
  *(float *)(param_1 + 100) = fVar2;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar1;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(undefined2 *)(param_1 + 0x74) = 0x9f4;
  iVar9 = param_1;
  for (uVar8 = 0; (int)uVar8 < (int)*(char *)(param_1 + 0x13); uVar8 = uVar8 + 1) {
    uVar6 = (-uVar8 | uVar8) >> 0x1b & 0x10;
    puVar7 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar10);
    uVar5 = *(undefined4 *)((int)&DAT_8036f23c + uVar6);
    *puVar7 = *(undefined4 *)((int)&DAT_8036f238 + uVar6);
    puVar7[1] = uVar5;
    puVar7[2] = *(undefined4 *)((int)&DAT_8036f240 + uVar6);
    dVar11 = (double)zz_0006fb4_(dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                 *(int *)(iVar9 + 0xe0),*(int *)((int)&DAT_8036f234 + uVar6),param_4
                                 ,param_5,param_6,param_7,param_8);
    iVar10 = iVar10 + 0x20;
    iVar9 = iVar9 + 4;
  }
  zz_01950a8_(dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,param_1);
  return;
}



// ==== 801950a8  zz_01950a8_ ====

/* WARNING: Removing unreachable block (ram,0x8019536c) */
/* WARNING: Removing unreachable block (ram,0x80195364) */
/* WARNING: Removing unreachable block (ram,0x8019535c) */
/* WARNING: Removing unreachable block (ram,0x801950c8) */
/* WARNING: Removing unreachable block (ram,0x801950c0) */
/* WARNING: Removing unreachable block (ram,0x801950b8) */

void zz_01950a8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined *puVar1;
  float fVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  undefined4 extraout_r4;
  int iVar6;
  float *pfVar7;
  int iVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  char *pcVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  char local_78 [8];
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_60;
  uint uStack_5c;
  
  fVar2 = FLOAT_8043b188;
  puVar1 = PTR_DAT_80433944;
  dVar13 = (double)*(float *)(param_9 + 0xd4);
  iVar6 = (char)PTR_DAT_80433944[0x14] * 0x80;
  if ((PTR_DAT_80433944[0x2c] & 4) == 0) {
    dVar14 = (double)FLOAT_8043b188;
    if (dVar13 <= dVar14) {
      local_70 = *(float *)(param_9 + 0x38);
      local_6c = *(undefined4 *)(param_9 + 0x3c);
      local_68 = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_70;
      *(undefined4 *)(param_9 + 0x24) = local_6c;
      *(undefined4 *)(param_9 + 0x28) = local_68;
    }
    else {
      dVar15 = (double)FLOAT_8043b19c;
      *(float *)(param_9 + 0xd4) = (float)(dVar13 - dVar15);
      if ((double)(float)(dVar13 - dVar15) < dVar14) {
        *(float *)(param_9 + 0xd4) = fVar2;
      }
      local_70 = *(float *)(param_9 + 100);
      local_6c = *(undefined4 *)(param_9 + 0x68);
      local_68 = *(undefined4 *)(param_9 + 0x6c);
    }
  }
  else {
    *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    local_70 = *(float *)(param_9 + 100);
    local_6c = *(undefined4 *)(param_9 + 0x68);
    local_68 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_70,(float *)(param_9 + 0x20),&local_70);
  gnt4_PSQUATScale_bl((double)FLOAT_8043b1a8,&local_70,&local_70);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_70,(float *)(param_9 + 0x20));
  if ((double)*(float *)(param_9 + 0xd4) != dVar13) {
    iVar3 = param_9;
    for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
      zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(iVar3 + 0xe0));
      iVar3 = iVar3 + 4;
    }
  }
  if ((FLOAT_8043b188 < *(float *)(param_9 + 0xd4)) && (*(int *)(puVar1 + iVar6 + 0x140) != 0)) {
    if ((char)puVar1[iVar6 + 0x161] < '\0') {
      sprintf(local_78,&DAT_8043b2c0);
    }
    else {
      iVar3 = 999999;
      iVar6 = *(int *)(*(int *)(puVar1 + iVar6 + 0x140) +
                       (char)puVar1[(char)puVar1[iVar6 + 0x161] + iVar6 + 0x14c] * 0x6c + 0x2c);
      if (iVar6 < 999999) {
        iVar3 = iVar6;
      }
      sprintf(local_78,&DAT_8043b1f0,iVar3);
    }
    sVar4 = strlen(local_78);
    *(short *)(param_9 + 0x1c) = (short)sVar4;
    dVar14 = (double)FLOAT_8043b2c8;
    pcVar10 = local_78;
    dVar15 = (double)FLOAT_8043b1c4;
    iVar9 = 1;
    iVar6 = param_9;
    dVar13 = DOUBLE_8043b1c8;
    for (iVar3 = 0; iVar8 = (int)*(short *)(param_9 + 0x1c), iVar3 < iVar8; iVar3 = iVar3 + 1) {
      pfVar7 = *(float **)(param_9 + 0x54);
      iVar5 = (int)*pcVar10;
      if ((iVar5 < 0x30) || (0x39 < iVar5)) {
        if (iVar5 == 0x3f) {
          dVar11 = (double)FLOAT_8043b210;
        }
        else {
          dVar11 = (double)FLOAT_8043b188;
        }
      }
      else {
        dVar11 = (double)(float)((double)CONCAT44(0x43300000,iVar5 - 0x30U ^ 0x80000000) -
                                DOUBLE_8043b1c8);
      }
      local_60 = 0x43300000;
      uStack_5c = iVar9 - iVar8 ^ 0x80000000;
      pfVar7[(iVar3 + 1) * 8] =
           (float)((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                           dVar13)) * dVar15);
      uVar12 = zz_00086b8_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar6 + 0xe4),pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10
                          );
      zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe4),extraout_r4,pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
      pcVar10 = pcVar10 + 1;
      iVar9 = iVar9 + 2;
      iVar6 = iVar6 + 4;
    }
  }
  return;
}



// ==== 80195388  FUN_80195388 ====

void FUN_80195388(int param_1)

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
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar2 = (int)*(short *)(param_1 + 0x74);
    zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74)
               );
    iVar3 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -7;
    iVar5 = iVar3 * 0x20;
    iVar4 = param_1 + iVar3 * 4;
    for (; -1 < iVar3; iVar3 = iVar3 + -1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x24);
      iVar5 = iVar5 + -0x20;
      iVar4 = iVar4 + -4;
    }
  }
  return;
}



// ==== 80195464  FUN_80195464 ====

void FUN_80195464(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043b2cc;
  fVar1 = FLOAT_8043b188;
  dVar3 = (double)FLOAT_8043b2cc;
  *(undefined2 *)(param_9 + 0x1c) = 0x1f;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(float *)(param_9 + 0x20) = fVar1;
  fVar1 = FLOAT_8043b2d0;
  *(float *)(param_9 + 0x24) = fVar2;
  *(float *)(param_9 + 0x28) = fVar1;
  zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),6,param_12,param_13,param_14,param_15,param_16);
  zz_01954d4_(param_9);
  return;
}



// ==== 801954d4  zz_01954d4_ ====

void zz_01954d4_(int param_1)

{
  if (((PTR_DAT_80433944[0x2d] | PTR_DAT_80433944[0x2c] & PTR_DAT_80433944[0x2e]) & 4) != 0) {
    if ((PTR_DAT_80433944[0x2d] & 4) == 0) {
      if ((PTR_DAT_80433944[0x2e] & 4) != 0) {
        *(undefined2 *)(param_1 + 0x1e) = 2;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x1e) = 0x20;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    return;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x1f;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  return;
}



// ==== 8019553c  FUN_8019553c ====

void FUN_8019553c(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  if ((*(ushort *)(param_1 + 0x1c) & *(ushort *)(param_1 + 0x1e)) != 0) {
    dVar2 = (double)*(float *)(param_1 + 0x24);
    dVar3 = (double)*(float *)(param_1 + 0x28);
    uVar1 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar2,dVar3,
                               (float *)(param_1 + 0x114));
    zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x24);
  }
  return;
}



// ==== 801955a0  FUN_801955a0 ====

void FUN_801955a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined8 uVar9;
  
  fVar1 = FLOAT_8043b188;
  iVar8 = 0;
  puVar7 = &DAT_8036f254;
  *(undefined2 *)(param_9 + 0x1c) = 0xffff;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar1;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *(short *)((int)puVar4 + 0x1e) = (short)*puVar7;
    uVar2 = puVar7[2];
    *puVar4 = puVar7[1];
    puVar4[1] = uVar2;
    puVar4[2] = puVar7[3];
    pfVar3 = (float *)(int)*(short *)((int)puVar4 + 0x1e);
    if (-1 < *(short *)((int)puVar4 + 0x1e)) {
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                  *(int *)(iVar6 + 0xe0),(int)pfVar3,param_12,param_13,param_14,param_15,param_16);
      uVar9 = zz_00086b8_((double)(float)puVar4[6],param_2,param_3,param_4,param_5,param_6,param_7,
                          param_8,DAT_803bb384,*(int *)(iVar6 + 0xe0),pfVar3,param_12,param_13,
                          param_14,param_15,param_16);
      param_1 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar6 + 0xe0),extraout_r4,pfVar3,param_12,param_13,param_14,
                            param_15,param_16);
    }
    iVar8 = iVar8 + 0x20;
    puVar7 = puVar7 + 4;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 80195680  FUN_80195680 ====

void FUN_80195680(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  
  if ((int)*(short *)(param_9 + 0x1c) == (int)(char)PTR_DAT_80433944[0x17]) {
    *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 1;
  }
  else {
    *(short *)(param_9 + 0x1c) = (short)(char)PTR_DAT_80433944[0x17];
    *(undefined2 *)(param_9 + 0x1e) = 0;
  }
  fVar2 = FLOAT_8043b190;
  if ((PTR_DAT_80433944[0x16] == '\0') || (cVar1 = PTR_DAT_80433944[0x17], cVar1 == '\0')) {
    *(float *)(param_9 + 0xd4) = FLOAT_8043b188;
  }
  else if (cVar1 == '\x01') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    param_1 = (double)FLOAT_8043b190;
    if (param_1 <= param_2) {
      *(float *)(param_9 + 0xd4) = FLOAT_8043b190;
    }
    else {
      dVar8 = (double)FLOAT_8043b2d4;
      *(float *)(param_9 + 0xd4) = (float)(param_2 + dVar8);
      if (param_1 < (double)(float)(param_2 + dVar8)) {
        *(float *)(param_9 + 0xd4) = fVar2;
      }
      *(undefined2 *)(param_9 + 0x1e) = 0;
    }
  }
  else if (cVar1 == '\x02') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043b18c;
  }
  iVar6 = 0;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(param_9 + 0x54) + iVar6;
    if (iVar4 == 0) {
      fVar2 = FLOAT_8043b188;
      if ((*(ushort *)(param_9 + 0x1e) & 0x20) != 0) {
        fVar2 = FLOAT_8043b190;
      }
      uVar7 = zz_00086b8_((double)(*(float *)(param_9 + 0xd4) + fVar2),param_2,param_3,param_4,
                          param_5,param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar5 + 0xe0),
                          param_11,param_12,param_13,param_14,param_15,param_16);
      param_1 = (double)zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int *)(iVar5 + 0xe0),extraout_r4,param_11,param_12,param_13,
                                    param_14,param_15,param_16);
    }
    else if (-1 < (char)PTR_DAT_80433944[iVar4 + 0x17]) {
      param_12 = (float *)(int)*(short *)(iVar3 + 0x1e);
      *(short *)(iVar3 + 0x1e) = (char)PTR_DAT_80433944[iVar4 + 0x17] + 0x31;
      param_11 = (float *)(int)*(short *)(iVar3 + 0x1e);
      if (param_11 != param_12) {
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                    *(int *)(iVar5 + 0xe0),(int)param_11,param_12,param_13,param_14,param_15,
                    param_16);
      }
      if (iVar4 == (char)PTR_DAT_80433944[0x17]) {
        if ((*(ushort *)(param_9 + 0x1e) & 0x20) == 0) {
          dVar8 = (double)FLOAT_8043b188;
        }
        else {
          dVar8 = (double)FLOAT_8043b190;
        }
      }
      else {
        dVar8 = (double)FLOAT_8043b188;
      }
      uVar7 = zz_00086b8_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384
                          ,*(int *)(iVar5 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                          param_16);
      param_1 = (double)zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(int *)(iVar5 + 0xe0),extraout_r4_00,param_11,param_12,param_13
                                    ,param_14,param_15,param_16);
    }
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 8019585c  FUN_8019585c ====

void FUN_8019585c(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if ((PTR_DAT_80433944[0x16] != '\0') && (PTR_DAT_80433944[0x17] != '\0')) {
    iVar4 = 0;
    iVar3 = param_1;
    for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
      if (-1 < *(short *)((int)pfVar1 + 0x1e)) {
        dVar6 = (double)pfVar1[1];
        dVar7 = (double)pfVar1[2];
        uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
        zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),
                    afStack_48,param_3,param_4,param_5,param_6,param_7,param_8);
        zz_00097b4_(*(int *)(iVar3 + 0xe0),0x24);
      }
      iVar4 = iVar4 + 0x20;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 80195924  FUN_80195924 ====

void FUN_80195924(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  
  fVar3 = FLOAT_8043b2dc;
  fVar2 = FLOAT_8043b2d8;
  fVar1 = FLOAT_8043b188;
  dVar12 = (double)FLOAT_8043b188;
  dVar10 = (double)FLOAT_8043b2d8;
  iVar9 = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  piVar8 = &DAT_8036f284;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar3;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    iVar4 = piVar8[2];
    piVar5 = (int *)(*(int *)(param_9 + 0x54) + iVar9);
    *piVar5 = piVar8[1];
    piVar5[1] = iVar4;
    piVar5[2] = piVar8[3];
    piVar5[6] = *piVar5;
    *(undefined2 *)(piVar5 + 7) = 0;
    param_11 = (float *)*piVar8;
    dVar10 = (double)zz_0006fb4_(dVar10,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar7 + 0xe0),(int)param_11,param_12,param_13
                                 ,param_14,param_15,param_16);
    param_10 = extraout_r4;
    if (iVar6 == 0) {
      uVar11 = zz_0008744_((double)*(float *)(param_9 + 0xd4),dVar12,param_3,param_4,param_5,param_6
                           ,param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),param_11,param_12,
                           param_13,param_14,param_15,param_16);
      uVar11 = zz_0007c30_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar7 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14
                           ,param_15,param_16);
      dVar10 = (double)zz_0007bb4_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar7 + 0xe0),piVar5 + 3,param_11,param_12,param_13,
                                   param_14,param_15,param_16);
      param_10 = extraout_r4_01;
    }
    iVar9 = iVar9 + 0x20;
    piVar8 = piVar8 + 4;
    iVar7 = iVar7 + 4;
  }
  zz_0195a2c_(dVar10,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80195a2c  zz_0195a2c_ ====

void zz_0195a2c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  undefined8 uVar10;
  
  fVar2 = FLOAT_8043b2e0;
  fVar1 = FLOAT_8043b188;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (PTR_DAT_80433944[0x6f] == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else {
      param_2 = (double)*(float *)(param_9 + 0xd8);
      if (((double)*(float *)(param_9 + 0xd4) < param_2) &&
         (fVar1 = (float)((double)*(float *)(param_9 + 0xd4) + (double)FLOAT_8043b190),
         *(float *)(param_9 + 0xd4) = fVar1, param_2 < (double)fVar1)) {
        *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(param_9 + 0xd8);
      }
    }
    fVar1 = FLOAT_8043b190;
    if (FLOAT_8043b2e0 <= *(float *)(param_9 + 0xd4)) {
      param_2 = (double)*(float *)(param_9 + 0xb4);
      dVar9 = (double)FLOAT_8043b190;
      if (param_2 < dVar9) {
        dVar8 = (double)FLOAT_8043b1a8;
        *(float *)(param_9 + 0xb4) = (float)(param_2 + dVar8);
        if (dVar9 <= (double)(float)(param_2 + dVar8)) {
          *(float *)(param_9 + 0xb4) = fVar1;
        }
      }
    }
  }
  else {
    if (FLOAT_8043b188 < *(float *)(param_9 + 0xb4)) {
      fVar2 = *(float *)(param_9 + 0xb4) - FLOAT_8043b1a8;
      *(float *)(param_9 + 0xb4) = fVar2;
      if (fVar2 <= fVar1) {
        *(float *)(param_9 + 0xb4) = fVar1;
      }
    }
    fVar1 = FLOAT_8043b188;
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar9 = (double)FLOAT_8043b190;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar9);
    if ((float)(param_2 - dVar9) <= fVar1) {
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    if (iVar5 == 0) {
      uVar10 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,
                           param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar6 + 0xe0),param_11,
                           param_12,param_13,param_14,param_15,param_16);
      uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar6 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007bb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),pfVar4 + 3,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
    else if (iVar5 < 3) {
      if (iVar5 == 1) {
        if (FLOAT_8043b190 <= *(float *)(param_9 + 0xb4)) {
          sVar3 = *(short *)(pfVar4 + 7) + -0x100;
        }
        else {
          sVar3 = 0;
        }
        *(short *)(pfVar4 + 7) = sVar3;
      }
      param_2 = DOUBLE_8043b1c8;
      param_3 = (double)FLOAT_8043b2e4;
      *pfVar4 = (float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,
                                                                   (int)(char)PTR_DAT_80433944[0x83]
                                                                   ^ 0x80000000) - DOUBLE_8043b1c8)
                       + (double)pfVar4[6]);
    }
    else if (3 < iVar5) {
      if (iVar5 + -4 == (int)(char)PTR_DAT_80433944[0x83]) {
        if ((PTR_DAT_80433944[0x6f] == '\x02') && ((*(ushort *)(PTR_DAT_80433944 + 8) & 4) != 0)) {
          dVar9 = (double)FLOAT_8043b190;
        }
        else {
          dVar9 = (double)FLOAT_8043b188;
        }
      }
      else {
        dVar9 = (double)FLOAT_8043b194;
      }
      uVar10 = zz_00086b8_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar6 + 0xe0),param_11,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                  ,param_16);
    }
    iVar7 = iVar7 + 0x20;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 80195c88  FUN_80195c88 ====

void FUN_80195c88(int param_1)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_58;
  undefined4 local_54;
  float local_50;
  float afStack_4c [14];
  
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar5 = 0;
  local_58 = FLOAT_8043b190;
  local_54 = *(undefined4 *)(param_1 + 0xb4);
  local_50 = FLOAT_8043b190;
  iVar4 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    if ((iVar3 == 0) || (FLOAT_8043b188 < *(float *)(param_1 + 0xb4))) {
      pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      zz_00455fc_((float *)(param_1 + 0x114),afStack_4c,pfVar2);
      iVar1 = (int)*(short *)(pfVar2 + 7);
      zz_00457d4_('z',afStack_4c,afStack_4c,*(short *)(pfVar2 + 7));
      if (iVar3 == 0) {
        pfVar2 = pfVar2 + 3;
        uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      }
      else {
        pfVar2 = &local_58;
        uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      }
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_4c,
                  (undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    }
    iVar5 = iVar5 + 0x20;
    iVar4 = iVar4 + 4;
  }
  return;
}



