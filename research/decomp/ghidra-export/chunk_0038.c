// ==== 80145b00  FUN_80145b00 ====

void FUN_80145b00(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043a2b8;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_80145b80;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01464c0_(param_1);
  }
LAB_80145b80:
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043a2c8 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80145bd8  FUN_80145bd8 ====

void FUN_80145bd8(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043a2b8) {
    if (((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) &&
       (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        zz_006a3d0_(param_1,'\0',3,0);
        return;
      }
      zz_006bf80_(param_1);
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      if (*(char *)(param_1 + 0x6ed) == '\0') {
        if (*(short *)(param_1 + 0x1dfc) < -0x7ff) {
          *(undefined1 *)(param_1 + 0x6ec) = 2;
          dVar2 = (double)FLOAT_8043a2c0;
          *(undefined1 *)(param_1 + 0x6ed) = 1;
          zz_004beb8_(dVar2,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,8,1);
          return;
        }
      }
      else if (0x7ff < *(short *)(param_1 + 0x1dfc)) {
        dVar2 = (double)FLOAT_8043a2c0;
        *(undefined1 *)(param_1 + 0x6ec) = 0;
        *(undefined1 *)(param_1 + 0x6ed) = 0;
        zz_004beb8_(dVar2,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,8,1);
        return;
      }
      zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,0xffffffff,
                  0xffffffff);
      return;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) {
    if (*(char *)(param_1 + 0x1cf2) != '\0') {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x10) == 0) {
          zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,2,0x20,0xffffffff,0xffffffff);
        }
        else {
          zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,2,0x22,0xffffffff,0xffffffff);
        }
      }
      else {
        zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,2,0x21,0xffffffff,0xffffffff);
      }
    }
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38)
                         );
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20)
                      );
      zz_00679d0_(param_1);
      dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
      if (dVar2 <= (double)FLOAT_8043a2c8) {
        return;
      }
      zz_00b22f4_(param_1);
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80145e5c  FUN_80145e5c ====

void FUN_80145e5c(int param_1)

{
  (*(code *)(&PTR_FUN_8033e524)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80145e98  FUN_80145e98 ====

void FUN_80145e98(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043a2cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  uVar2 = *(uint *)(param_1 + 0x5e0);
  iVar3 = 8;
  if ((uVar2 & 0x80) != 0) {
    iVar3 = 0xc;
  }
  if ((uVar2 & 0x10) != 0) {
    iVar3 = 4;
  }
  if (((uVar2 & 0x20) != 0) &&
     (iVar3 = *(char *)(param_1 + 0x1d10) + 0x10, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar3 = 0;
  }
  *(undefined1 *)(param_1 + 0x6ed) = 0;
  if (*(short *)(param_1 + 0x1dfc) < 0) {
    iVar3 = iVar3 + 2;
    *(undefined1 *)(param_1 + 0x6ed) = 1;
  }
  *(char *)(param_1 + 0x6ec) = (char)iVar3;
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xd,2,iVar3 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80145f6c  FUN_80145f6c ====

void FUN_80145f6c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xd);
  }
  fVar2 = FLOAT_8043a2b8;
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
      zz_01464c0_(param_1);
    }
  }
  return;
}



// ==== 80146048  FUN_80146048 ====

void FUN_80146048(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined1 uVar3;
  double dVar4;
  
  zz_004cd24_(param_9,0xd);
  dVar4 = (double)*(float *)(param_9 + 0x558);
  if (dVar4 <= (double)FLOAT_8043a2b8) {
    if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((uVar2 & 0x10) == 0) {
            if ((uVar2 & 0x20) == 0) {
              zz_006a3d0_(param_9,'\0',0,2);
              return;
            }
            uVar3 = 2;
            *(undefined1 *)(param_9 + 0x581) = 2;
            iVar1 = *(char *)(param_9 + 0x1d10) + 0x11;
            if (*(char *)(param_9 + 0x5db) == '\x0f') {
              iVar1 = 1;
            }
          }
          else {
            uVar3 = 1;
            *(undefined1 *)(param_9 + 0x581) = 1;
            iVar1 = 5;
          }
        }
        else {
          uVar3 = 3;
          *(undefined1 *)(param_9 + 0x581) = 3;
          iVar1 = 9;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 0xd;
          }
        }
        if (*(char *)(param_9 + 0x6ed) == '\0') {
          if (*(short *)(param_9 + 0x1dfc) < -0x7ff) {
            zz_006a3d0_(param_9,'\0',uVar3,0);
            return;
          }
        }
        else {
          if (0x7ff < *(short *)(param_9 + 0x1dfc)) {
            zz_006a3d0_(param_9,'\0',uVar3,0);
            return;
          }
          iVar1 = iVar1 + 2;
        }
        *(char *)(param_9 + 0x6ec) = (char)iVar1;
        zz_004beb8_((double)FLOAT_8043a2c0,param_9,0xd,2,iVar1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80146290;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar4 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) &&
     (uVar2 = *(uint *)(param_9 + 0x5e0), (uVar2 & 0x200) == 0)) {
    if (*(char *)(param_9 + 0x1cf2) != '\0') {
      if ((uVar2 & 0x40) == 0) {
        if ((uVar2 & 0x10) == 0) {
          param_11 = 2;
          param_12 = 0x20;
          param_13 = 0xffffffff;
          param_14 = 0xffffffff;
          dVar4 = (double)zz_004beb8_((double)FLOAT_8043a2c0,param_9,0xd,2,0x20,0xffffffff,
                                      0xffffffff);
        }
        else {
          param_11 = 2;
          param_12 = 0x22;
          param_13 = 0xffffffff;
          param_14 = 0xffffffff;
          dVar4 = (double)zz_004beb8_((double)FLOAT_8043a2c0,param_9,0xd,2,0x22,0xffffffff,
                                      0xffffffff);
        }
      }
      else {
        param_11 = 2;
        param_12 = 0x21;
        param_13 = 0xffffffff;
        param_14 = 0xffffffff;
        dVar4 = (double)zz_004beb8_((double)FLOAT_8043a2c0,param_9,0xd,2,0x21,0xffffffff,0xffffffff)
        ;
      }
    }
    if (*(char *)(param_9 + 0x1cee) == '\0') {
      return;
    }
  }
LAB_80146290:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801462c4  FUN_801462c4 ====

void FUN_801462c4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8033e530)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014630c  FUN_8014630c ====

void FUN_8014630c(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a2bc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(short *)(param_1 + 0x5aa) < 0) {
    iVar2 = 0xe;
    *(undefined1 *)(param_1 + 0x6ed) = 0;
  }
  else {
    iVar2 = 0xc;
    *(undefined1 *)(param_1 + 0x6ed) = 0;
  }
  *(char *)(param_1 + 0x6ec) = (char)iVar2;
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xd,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a2b8;
  return;
}



// ==== 801463e8  FUN_801463e8 ====

void FUN_801463e8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d0dc_(param_1,0x81,0);
    if (iVar3 == 0) goto LAB_80146494;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01464c0_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
LAB_80146494:
  if (FLOAT_8043a2c8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801464c0  zz_01464c0_ ====

void zz_01464c0_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a2d4;
  *(float *)(param_1 + 0x560) = FLOAT_8043a2cc;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    if (*(short *)(param_1 + 1000) == 5) {
      FUN_80099e94(param_1,0x25,*(short *)(param_1 + 0x1dfc));
      FUN_80099e94(param_1,0x26,*(short *)(param_1 + 0x1dfc));
    }
    else if (*(short *)(param_1 + 1000) == 9) {
      FUN_80099e94(param_1,0x31,*(short *)(param_1 + 0x1dfc));
    }
  }
  return;
}



// ==== 80146560  FUN_80146560 ====

void FUN_80146560(int param_1)

{
  if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
    *(float *)(param_1 + 0x144) = FLOAT_8043a2d8;
  }
  (*(code *)(&PTR_FUN_8033e53c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801465b0  FUN_801465b0 ====

void FUN_801465b0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00fed6c_(param_1);
  return;
}



// ==== 801465e4  FUN_801465e4 ====

void FUN_801465e4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033e568)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80146640  FUN_80146640 ====

void FUN_80146640(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  fVar1 = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x558) = FLOAT_8043a2dc;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2e0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80146764  FUN_80146764 ====

void FUN_80146764(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2e0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a2bc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_8043a2e4;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043a2bc;
    if (fVar2 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 80146888  FUN_80146888 ====

void FUN_80146888(int param_1)

{
  uint uVar1;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_8043a2c4,param_1);
  uVar1 = FUN_80066838((double)FLOAT_8043a2e4,param_1);
  if (0 < (int)uVar1) {
    *(float *)(param_1 + 0x44) = FLOAT_8043a2b8;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / FLOAT_8043a2bc;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8014697c  FUN_8014697c ====

void FUN_8014697c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033e574)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801469cc  FUN_801469cc ====

void FUN_801469cc(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043a2dc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x50) = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,3,9,0xffffffff,0xffffffff);
  return;
}



// ==== 80146af8  FUN_80146af8 ====

void FUN_80146af8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a2cc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80146bc4  FUN_80146bc4 ====

void FUN_80146bc4(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a2e8 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a2e8 * -dVar1);
  }
  return;
}



// ==== 80146c54  FUN_80146c54 ====

void FUN_80146c54(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  fVar3 = FLOAT_8043a2ec;
  fVar1 = FLOAT_8043a2b8;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x44) = FLOAT_8043a2b8;
    fVar2 = FLOAT_8043a2c0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a2d8 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043a2d0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80146d5c  FUN_80146d5c ====

void FUN_80146d5c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 9) {
    zz_0147130_(param_1);
  }
  else {
    zz_0146d90_(param_1);
  }
  return;
}



// ==== 80146d90  zz_0146d90_ ====

void zz_0146d90_(int param_1)

{
  (*(code *)(&PTR_FUN_8033e584)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80146dcc  FUN_80146dcc ====

void FUN_80146dcc(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a2f0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(ushort *)(param_1 + 0x54a) = (ushort)*(undefined4 *)(param_1 + 0x5e0) & 0x40;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  if ((*(float *)(param_1 + 0x144) <= FLOAT_8043a2b8) || (*(int *)(param_1 + 0xcc) == 0)) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a2f8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x9c));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x9c),(float *)(param_1 + 0x9c));
  }
  else {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),(float *)(param_1 + 0x9c));
    zz_006ebb4_((float *)(param_1 + 0x9c),(float *)(param_1 + 0x9c));
    gnt4_PSQUATScale_bl((double)(FLOAT_8043a2f4 * *(float *)(param_1 + 0xb4)),
                        (float *)(param_1 + 0x9c),(float *)(param_1 + 0x9c));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x9c),(float *)(param_1 + 0x9c));
    *(undefined2 *)(param_1 + 0x54a) = 0x40;
  }
  zz_0066530_(param_1,0x2d);
  zz_006dbe0_(param_1,2,1,1);
  zz_0146ed8_(param_1);
  return;
}



// ==== 80146ed8  zz_0146ed8_ ====

void zz_0146ed8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  FUN_800061a8(param_1,9);
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  fVar3 = FLOAT_8043a2fc;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 80146f6c  FUN_80146f6c ====

void FUN_80146f6c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  FUN_800061a8(param_1,9);
  fVar1 = FLOAT_8043a300;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_0046588_((double)(fVar1 * *(float *)(param_1 + 0x1dc8)),(float *)(param_1 + 0x9c),
              (float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  fVar3 = FLOAT_8043a304;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    if (*(short *)(param_1 + 0x54a) == 0) {
      zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,0,0,2,1);
    }
    else {
      zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,0,0xd,2,1);
    }
    FUN_800061a8(param_1,10);
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 80147094  FUN_80147094 ====

void FUN_80147094(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffd;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80147130  zz_0147130_ ====

void zz_0147130_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033e594)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80147180  FUN_80147180 ====

void FUN_80147180(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x50) = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 5;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a2c0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a2b8;
  return;
}



// ==== 80147280  FUN_80147280 ====

void FUN_80147280(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if ((iVar1 != 0) && (*(short *)(param_1 + 1000) == 9)) {
      zz_01e29fc_(param_1,0);
    }
  }
  dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043a2c8 < dVar2) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8014734c  FUN_8014734c ====

void FUN_8014734c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a2d8 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a2d8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80147428  FUN_80147428 ====

void FUN_80147428(int param_1)

{
  (*(code *)(&PTR_FUN_8033e5a0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80147464  FUN_80147464 ====

void FUN_80147464(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033e5b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801474b4  FUN_801474b4 ====

void FUN_801474b4(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a2dc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x50) = FLOAT_8043a2b8;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a2c0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,6,1);
  return;
}



// ==== 801475f8  FUN_801475f8 ====

void FUN_801475f8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a2b8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801476b0  FUN_801476b0 ====

void FUN_801476b0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
    FUN_800061a8(param_1,9);
  }
  fVar2 = FLOAT_8043a2ec;
  fVar1 = FLOAT_8043a2d0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043a308;
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x55c) = fVar1;
    *(float *)(param_1 + 0x560) = fVar3;
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a30c * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
    fVar1 = FLOAT_8043a2b8;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a30c * -dVar4);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
    zz_00b2190_(param_1,0);
    *(float *)(param_1 + 0x80c) = FLOAT_8043a2b8;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 801477e4  FUN_801477e4 ====

void FUN_801477e4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  dVar4 = (double)FLOAT_8043a2c4;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_006ed8c_(dVar4,param_1);
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_8043a2b8;
  fVar2 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x55c) = fVar2;
  if (fVar2 <= fVar3) {
    FUN_8016c810((double)*(float *)(param_1 + 0x560),param_1,3,0);
    fVar2 = FLOAT_8043a2d0;
    *(float *)(param_1 + 0x55c) = FLOAT_8043a2d0;
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - fVar2;
  }
  fVar3 = FLOAT_8043a2b8;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_8043a2c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined2 *)(param_1 + 0x272) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    FUN_800061a8(param_1,10);
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 80147924  FUN_80147924 ====

void FUN_80147924(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a310) * FLOAT_8043a2e0);
  if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
    zz_00107a0_(param_1,0x10);
  }
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a2d0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a2fc + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x18da) = 0;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a2f0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80147a54  zz_0147a54_ ====

void zz_0147a54_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0xb00) || (*(short *)(param_1 + 1000) == 0xb06)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80147b6c;
    *(code **)(puVar1 + 0x10c) = FUN_80147db4;
    puVar1[0x144] = 0;
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



// ==== 80147b6c  FUN_80147b6c ====

void FUN_80147b6c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8033eca8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80147bc0  FUN_80147bc0 ====

void FUN_80147bc0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar5 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar5;
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar3 = *(char *)(param_9 + 0x13) * 0x14;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043a318;
  *(undefined *)(param_9 + 0x84) = (&DAT_8033ec5a)[iVar3];
  *(undefined *)(param_9 + 0x89) = (&DAT_8033ec59)[iVar3];
  uVar2 = *(undefined4 *)(&DAT_8033ec64 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8033ec60 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033ec68 + iVar3);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_8033ec58)[iVar3],iVar6 + 0xc28,iVar5,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)(char)(&DAT_8033ec58)[iVar3];
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,iVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a31c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0147d74_(param_9);
  return;
}



// ==== 80147ce4  zz_0147d74_ ====

void zz_0147d74_(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = *(char *)(param_1 + 0x13) * 0x14;
  if ((*(uint *)(*(int *)(param_1 + 0x90) + 0x5e0) & 0x20000000) != 0) {
    return;
  }
  if (*(float *)(*(int *)(param_1 + 0x90) + 0x648) <= FLOAT_8043a320) {
    sVar2 = *(short *)(&DAT_8033ec5c + iVar3);
  }
  else {
    sVar2 = *(short *)(&DAT_8033ec5e + iVar3);
  }
  cVar1 = (&DAT_8033ec5b)[iVar3];
  if (cVar1 == '\x01') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar2;
    return;
  }
  if ('\0' < cVar1) {
    if ('\x02' < cVar1) {
      return;
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + sVar2;
    return;
  }
  if (cVar1 < '\0') {
    return;
  }
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar2;
  return;
}



// ==== 80147d94  FUN_80147d94 ====

void FUN_80147d94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80147db4  FUN_80147db4 ====

void FUN_80147db4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80147e34  zz_0147e34_ ====

void zz_0147e34_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ecb8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80147e90  FUN_80147e90 ====

void FUN_80147e90(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  dVar3 = (double)FLOAT_8043a32c;
  *(float *)(param_1 + 0x558) = FLOAT_8043a328;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined4 *)(param_1 + 0x3c) =
       *(undefined4 *)(&DAT_8033ecc8 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,5,1);
  return;
}



// ==== 80147f7c  FUN_80147f7c ====

void FUN_80147f7c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a330;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a334;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_80148288(param_1);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80148014  FUN_80148014 ====

void FUN_80148014(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043a338;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a330;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_1 + 0x3c),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801480fc  FUN_801480fc ====

void FUN_801480fc(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  fVar2 = FLOAT_8043a334;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar4 = (double)FLOAT_8043a32c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    FUN_80148288(param_1);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    FUN_80148288(param_1);
  }
  zz_006ed8c_((double)FLOAT_8043a33c,param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_1 + 0x3c)) {
    zz_006ed8c_((double)FLOAT_8043a340,param_1);
  }
  FUN_80067310((double)FLOAT_8043a338,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 80148288  FUN_80148288 ====

/* WARNING: Removing unreachable block (ram,0x80148368) */
/* WARNING: Removing unreachable block (ram,0x80148298) */

void FUN_80148288(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_8043a348) * FLOAT_8043a344;
  }
  dVar3 = (double)(fVar1 / FLOAT_8043a334);
  *(float *)(param_1 + 0x38) = fVar1 / FLOAT_8043a334;
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
  if (fVar1 < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = fVar1;
  }
  dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar3 * dVar2);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x48) = (float)(dVar3 * -dVar2);
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 80148384  zz_0148384_ ====

void zz_0148384_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (**(code **)(&DAT_804346a0 + *(char *)(param_1 + 0x540) * 4))();
  return;
}



// ==== 801483d0  FUN_801483d0 ====

void FUN_801483d0(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043a330;
  *(float *)(param_1 + 0x50) = FLOAT_8043a330;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a350,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_0067a28_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a32c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801484c0  FUN_801484c0 ====

void FUN_801484c0(int param_1)

{
  short sVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\x01') goto LAB_80148544;
  *(undefined1 *)(param_1 + 0x1cef) = 0;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 != 0xa03) {
    if (sVar1 < 0xa03) {
      if (sVar1 == 0xa01) {
        zz_0085638_(param_1,0);
      }
      else if (0xa00 < sVar1) {
        zz_0154e28_(param_1);
      }
      goto LAB_80148544;
    }
    if (sVar1 != 0xa06) goto LAB_80148544;
  }
  zz_0085638_(param_1,1);
LAB_80148544:
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a350,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_0067a28_(param_1);
  fVar2 = FLOAT_8043a330;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801485e8  zz_01485e8_ ====

void zz_01485e8_(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
    if (*(char *)((int)param_2 + 7) != *(char *)(param_1 + 0x6e9)) {
      *(char *)((int)param_2 + 6) = *(char *)(param_1 + 0x6e9);
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined1 *)(param_1 + 0x1d4f) = 0;
    }
    fVar1 = FLOAT_8043a330;
    if ((char)*(byte *)((int)param_2 + 6) < '\0') {
      *(byte *)((int)param_2 + 6) = *(byte *)((int)param_2 + 6) & 0x7f;
      *param_2 = fVar1;
      *(undefined2 *)(param_2 + 1) = 0;
    }
    fVar2 = FLOAT_8043a338;
    fVar1 = FLOAT_8043a330;
    if (*(char *)((int)param_2 + 6) == '\0') {
      if ((FLOAT_8043a330 < *param_2) && (*param_2 = *param_2 - FLOAT_8043a354, *param_2 < fVar1)) {
        *param_2 = fVar1;
      }
    }
    else {
      if ((*param_2 < FLOAT_8043a338) && (*param_2 = *param_2 + FLOAT_8043a354, fVar2 < *param_2)) {
        *param_2 = fVar2;
      }
      *(short *)(param_2 + 1) = *(short *)(param_2 + 1) + 0x300;
    }
    dVar3 = zz_0045204_(*(short *)(param_2 + 1));
    *(float *)(param_1 + 0x1dc0) =
         *param_2 * (float)((double)FLOAT_8043a35c * dVar3) + FLOAT_8043a358;
    *(undefined1 *)((int)param_2 + 7) = *(undefined1 *)((int)param_2 + 6);
  }
  return;
}



// ==== 80148718  zz_0148718_ ====

void zz_0148718_(int param_1,byte *param_2)

{
  if (param_2[1] != *(byte *)(param_1 + 0x6e8)) {
    *param_2 = *(byte *)(param_1 + 0x6e8) & 0x7f;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    if (*param_2 != 0) {
      zz_004beb8_((double)FLOAT_8043a32c,param_1,4,2,(uint)(byte)(&DAT_804346a8)[(char)*param_2],0xc
                  ,2);
    }
  }
  if (*param_2 != 0) {
    zz_004cd24_(param_1,4);
  }
  param_2[1] = *param_2;
  return;
}



// ==== 801487c4  FUN_801487c4 ====

void FUN_801487c4(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a368) * FLOAT_8043a360);
  (*(code *)(&PTR_FUN_8033ecf8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80148838  FUN_80148838 ====

void FUN_80148838(int param_1)

{
  (*(code *)(&PTR_FUN_8033ed0c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80148874  FUN_80148874 ====

void FUN_80148874(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043a370;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  fVar2 = FLOAT_8043a374;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a374;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  dVar3 = (double)FLOAT_8043a378;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 3;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a37c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a374;
  return;
}



// ==== 80148968  FUN_80148968 ====

/* WARNING: Removing unreachable block (ram,0x80148a00) */
/* WARNING: Removing unreachable block (ram,0x80148a58) */

void FUN_80148968(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  zz_006e1ac_(param_1,0xc1,1);
  iVar4 = zz_006d144_(param_1,0xc1);
  fVar3 = FLOAT_8043a374;
  if (((iVar4 == 0) &&
      (fVar2 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar2, fVar3 < fVar2)) || (*(char *)(param_1 + 0x1cee) == '\0'))
  {
    if (FLOAT_8043a380 < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    dVar5 = (double)FLOAT_8043a37c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80148ab0  FUN_80148ab0 ====

void FUN_80148ab0(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a384;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (iVar3 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x544) = 1;
      *(float *)(param_1 + 0x558) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    else {
      dVar4 = (double)FLOAT_8043a37c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    }
  }
  if (FLOAT_8043a380 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80148ba0  FUN_80148ba0 ====

void FUN_80148ba0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)FLOAT_8043a378;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a368) * FLOAT_8043a360);
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a374;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      if (FLOAT_8043a380 < *(float *)(param_1 + 0x44)) {
        zz_00b22f4_(param_1);
      }
    }
    else {
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a388 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80148cb0  FUN_80148cb0 ====

void FUN_80148cb0(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043a38c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a368) * FLOAT_8043a360);
  zz_006ed8c_(dVar2,param_1);
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a374;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80148d74  zz_0148d74_ ====

void zz_0148d74_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ed20)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80148dc4  FUN_80148dc4 ====

void FUN_80148dc4(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043a384;
  fVar2 = FLOAT_8043a374;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_8043a37c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80148ea8  FUN_80148ea8 ====

void FUN_80148ea8(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a374;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) &&
     (*(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01',
     *(float *)(param_2 + 4) < *(float *)(param_1 + 0x764))) {
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80148f4c  FUN_80148f4c ====

void FUN_80148f4c(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    if (*(float *)(param_2 + 4) < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_8043a37c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(undefined4 *)(param_1 + 0x44) =
           *(undefined4 *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    }
    else {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x764) *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                  DOUBLE_8043a368) * FLOAT_8043a390;
    }
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * *(float *)(param_2 + 8);
    fVar2 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
    if (fVar2 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(float *)(param_1 + 0x4c) =
         *(float *)(param_1 + 0x44) *
         (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                DOUBLE_8043a368) * FLOAT_8043a390;
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
  }
  if (*(float *)(param_1 + 0x764) < *(float *)(param_2 + 4)) {
    zz_006ed8c_((double)*(float *)(param_2 + 0x10),param_1);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80149178  zz_0149178_ ====

void zz_0149178_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ed2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801491c8  FUN_801491c8 ====

void FUN_801491c8(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043a374;
  *(float *)(param_1 + 0x558) = FLOAT_8043a384;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  *(float *)(param_1 + 0x50) = fVar2;
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
  gnt4_PSQUATScale_bl((double)(float)param_2[5],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a37c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80149318  FUN_80149318 ====

void FUN_80149318(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x14),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar3 = FLOAT_8043a374;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar2 = DOUBLE_8043a368;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043a374;
    *(undefined4 *)(param_1 + 0x38) =
         *(undefined4 *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c);
    fVar1 = (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 4) ^ 0x80000000) - dVar2);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar3 != fVar1) {
      *(float *)(param_1 + 0x38) =
           *(float *)(param_1 + 0x38) /
           (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 4) ^ 0x80000000) - dVar2);
    }
    fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
    if (fVar1 < *(float *)(param_1 + 0x38)) {
      *(float *)(param_1 + 0x38) = fVar1;
    }
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80149484  FUN_80149484 ====

/* WARNING: Removing unreachable block (ram,0x8014959c) */
/* WARNING: Removing unreachable block (ram,0x80149494) */

void FUN_80149484(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar6 = (double)*(float *)(param_1 + 0x38);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar6 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043a378;
  *(float *)(param_1 + 0x48) = (float)(dVar6 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a374;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 8),param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = *(float *)(param_2 + 0xc);
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar1;
  }
  return;
}



// ==== 801495bc  FUN_801495bc ====

/* WARNING: Removing unreachable block (ram,0x801496e8) */
/* WARNING: Removing unreachable block (ram,0x801495cc) */

void FUN_801495bc(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    dVar3 = (double)*(float *)(param_1 + 0x38);
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)(dVar3 * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)(dVar3 * -dVar2);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x10),param_1);
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 == 0) || (-1 < *(char *)(param_1 + 0x1cef))) {
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
    *(float *)(param_1 + 0x694) = FLOAT_8043a378 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80149708  zz_0149708_ ====

void zz_0149708_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ed3c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80149758  FUN_80149758 ====

void FUN_80149758(int param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(char *)(param_1 + 0x6ea) = (char)param_2[1];
  }
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a384;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[3],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a37c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a374;
  return;
}



// ==== 8014989c  FUN_8014989c ====

void FUN_8014989c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0xc),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a374;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80149954  FUN_80149954 ====

void FUN_80149954(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0xc),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  fVar2 = FLOAT_8043a374;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(short *)(param_1 + 0x548) = *(short *)(param_2 + 0x10) * 10;
    *(short *)(param_1 + 0x54a) = *(short *)(param_2 + 0x12) * 10;
    *(undefined2 *)(param_1 + 0x54c) = *(undefined2 *)(param_2 + 0x14);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_2 + 0x16);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x18);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_2 + 0x1c);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x20);
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0066530_(param_1,0x2d);
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_8043a37c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80149a7c  FUN_80149a7c ====

void FUN_80149a7c(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  short sVar3;
  double dVar4;
  double dVar5;
  
  iVar2 = zz_006de44_(param_1,0xf0f00);
  if (iVar2 != 0) {
    sVar3 = *(short *)(param_1 + 0x54c);
    *(short *)(param_1 + 0x54c) = sVar3 + -1;
    if (*(short *)(param_1 + 0x54c) < *(short *)(param_2 + 0x16)) {
      *(short *)(param_1 + 0x54c) = *(short *)(param_2 + 0x16);
    }
    if (*(short *)(param_1 + 0x54a) < sVar3) {
      sVar3 = *(short *)(param_1 + 0x54a);
    }
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) - sVar3;
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + sVar3;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x3c);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a378;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1b01) != '\0') &&
     (*(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -10,
     *(short *)(param_1 + 0x548) < 0)) {
    dVar4 = (double)FLOAT_8043a37c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80149c08  FUN_80149c08 ====

/* WARNING: Removing unreachable block (ram,0x80149d98) */
/* WARNING: Removing unreachable block (ram,0x80149c18) */

void FUN_80149c08(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_8043a360;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)
                                   - DOUBLE_8043a368) * dVar3);
  zz_006ed8c_(dVar3,param_1);
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_8043a3a0;
  if (DOUBLE_8043a398 <= (double)*(float *)(param_1 + 0x44)) {
    if (*(char *)(param_1 + 0x1cef) < '\0') {
      dVar3 = (double)*(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x1dc8) = FLOAT_8043a3a4;
      zz_004cd24_(param_1,0xf);
      *(float *)(param_1 + 0x1dc8) = (float)dVar3;
    }
    else {
      zz_004cd24_(param_1,0xf);
    }
    zz_00b22f4_(param_1);
  }
  else if (iVar2 == 0) {
    dVar3 = (double)FLOAT_8043a37c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_004beb8_(dVar3,param_1,0xf,0,0xd,0x14,1);
  }
  else {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (-1 < *(int *)(param_2 + 8)) {
      zz_004beb8_((double)FLOAT_8043a37c,param_1,0xf,4,*(int *)(param_2 + 8),0xffffffff,0xffffffff);
    }
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_006a474_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043a388 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80149db8  FUN_80149db8 ====

void FUN_80149db8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a368) * FLOAT_8043a360);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a378,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a374;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_8043a388 + *(float *)(param_1 + 0x1dc8);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a388 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80149ec8  zz_0149ec8_ ====

void zz_0149ec8_(int param_1,undefined4 param_2)

{
  if ((*(char *)(param_1 + 0x7ce) == '\x0f') || (*(char *)(param_1 + 0x7ce) == '\x10')) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
    (*(code *)(&PTR_FUN_8033ed58)[*(char *)(param_1 + 0x540)])(param_1);
    zz_014a1a4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 2;
    *(undefined1 *)(param_1 + 0x540) = 0;
    zz_014a200_(param_1,param_2);
  }
  return;
}



// ==== 80149f58  FUN_80149f58 ====

void FUN_80149f58(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043a3a8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,7,2,0xf,0xffffffff,0xffffffff);
  return;
}



// ==== 80149f9c  FUN_80149f9c ====

void FUN_80149f9c(int param_1,int param_2)

{
  int iVar1;
  
  zz_004cd24_(param_1,7);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_014a890_(param_1,param_2);
    }
    zz_004beb8_((double)FLOAT_8043a3a8,param_1,7,2,0x10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8014a038  FUN_8014a038 ====

void FUN_8014a038(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,7);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (((*(uint *)(param_1 + 0x5bc) & 0x200) == 0) ||
       (iVar1 = zz_006dbe0_(param_1,0,1,1), iVar1 == 0)) {
      dVar2 = (double)FLOAT_8043a3a8;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_004beb8_(dVar2,param_1,7,2,0x11,0xffffffff,0xffffffff);
    }
    else {
      zz_014a890_(param_1,param_2);
      zz_004beb8_((double)FLOAT_8043a3a8,param_1,7,2,0x10,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8014a104  FUN_8014a104 ====

void FUN_8014a104(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a6fc_(param_1,0x10);
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_006a750_(param_1,0x10);
    *(undefined1 *)(param_1 + 0x544) = 2;
    dVar1 = (double)FLOAT_8043a3ac;
    *(undefined1 *)(param_1 + 0x588) = 1;
    zz_004beb8_(dVar1,param_1,7,0,0xb,4,2);
  }
  return;
}



// ==== 8014a1a4  zz_014a1a4_ ====

void zz_014a1a4_(int param_1)

{
  double dVar1;
  
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  dVar1 = (double)FLOAT_8043a3b0;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8014a200  zz_014a200_ ====

void zz_014a200_(int param_1,undefined4 param_2)

{
  zz_014a7f8_(param_1);
  (*(code *)(&PTR_FUN_804346b0)[*(char *)(param_1 + 0x544)])(param_1,param_2);
  (*(code *)(&PTR_FUN_8033ed68)[*(char *)(param_1 + 0x540)])(param_1,param_2);
  return;
}



// ==== 8014a284  FUN_8014a284 ====

void FUN_8014a284(int param_1,undefined2 *param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  fVar1 = FLOAT_8043a3b4;
  *(undefined1 *)(param_1 + 0x540) = 1;
  dVar2 = DOUBLE_8043a3b8;
  *(undefined1 *)(param_1 + 0x745) = 0;
  dVar3 = (double)FLOAT_8043a3a8;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  *(char *)(param_1 + 0x6ec) = (char)*param_2;
  *(float *)(param_1 + 0x558) =
       (float)((double)CONCAT44(0x43300000,(int)(short)param_2[1] ^ 0x80000000) - dVar2);
  zz_004beb8_(dVar3,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),4,2);
  return;
}



// ==== 8014a308  FUN_8014a308 ====

void FUN_8014a308(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a3c0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if ((*(float *)(param_1 + 0x560) < fVar1) ||
     ((*(char *)(param_1 + 0x1cef) != '\0' && (*(short *)(param_1 + 0x54a) != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
    *(undefined1 *)(param_1 + 0x587) = 0;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_014a890_(param_1,param_2);
    }
    *(undefined2 *)(param_1 + 0x54c) = 5;
  }
  return;
}



// ==== 8014a3bc  FUN_8014a3bc ====

void FUN_8014a3bc(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar1 = FLOAT_8043a3c0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    if ('\0' < *(char *)(param_1 + 0x6ec)) {
      *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
      *(float *)(param_1 + 0x558) =
           (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 2) ^ 0x80000000) -
                  DOUBLE_8043a3b8);
      *(undefined1 *)(param_1 + 0x587) = 0;
      iVar2 = zz_006dbe0_(param_1,0,1,1);
      if (iVar2 != 0) {
        zz_006bf80_(param_1);
        zz_014a890_(param_1,param_2);
        goto LAB_8014a4c8;
      }
    }
    fVar1 = FLOAT_8043a3c4;
    dVar3 = (double)FLOAT_8043a3a8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x55c) = fVar1;
    *(undefined2 *)(param_1 + 0x54c) = 10;
    zz_004beb8_(dVar3,param_1,0xf,2,*(char *)(param_1 + 0x6ea) + 10,4,2);
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
LAB_8014a4c8:
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



// ==== 8014a534  FUN_8014a534 ====

void FUN_8014a534(int param_1,undefined2 *param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  *(undefined2 *)(param_1 + 0x54c) = 10;
  if ((*(char *)(param_1 + 0x745) != '\0') &&
     (iVar4 = zz_006dbe0_(param_1,0,1,1), dVar2 = DOUBLE_8043a3b8, iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(char *)(param_1 + 0x6ec) = (char)*param_2 + -1;
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)(short)param_2[1] ^ 0x80000000) - dVar2);
    zz_006bf80_(param_1);
    zz_014a890_(param_1,(int)param_2);
    zz_004beb8_((double)FLOAT_8043a3a8,param_1,0xf,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                0xffffffff);
    return;
  }
  fVar3 = FLOAT_8043a3c0;
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) &&
      (fVar1 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x55c) = fVar1, fVar3 < fVar1)) && (*(char *)(param_1 + 0x1cee) == '\0'))
  {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 == 0) {
    zz_006a4f4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8014a6a0  FUN_8014a6a0 ====

void FUN_8014a6a0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a3c0;
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 10;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_014a700_(param_1);
  return;
}



// ==== 8014a700  zz_014a700_ ====

void zz_014a700_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_8043a3c8,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_8043a3c0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043a3a8;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_8043a3c0;
  }
  FUN_80067310((double)FLOAT_8043a3b0,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)*(float *)(param_1 + 0x1ae0),param_1,0xf,2,
                  *(short *)(param_1 + 0x54c) + iVar3,6,2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 8014a7f8  zz_014a7f8_ ====

void zz_014a7f8_(int param_1)

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



// ==== 8014a890  zz_014a890_ ====

void zz_014a890_(undefined4 param_1,int param_2)

{
  if (*(code **)(param_2 + 4) != (code *)0x0) {
    (**(code **)(param_2 + 4))();
  }
  return;
}



// ==== 8014a8c0  zz_014a8c0_ ====

void zz_014a8c0_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ed78)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014a91c  FUN_8014a91c ====

void FUN_8014a91c(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  dVar3 = (double)FLOAT_8043a3a8;
  *(float *)(param_1 + 0x558) = FLOAT_8043a3c4;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,5,1);
  return;
}



// ==== 8014a9f0  FUN_8014a9f0 ====

void FUN_8014a9f0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a3c0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a3cc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_8014acdc(param_1);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 8014aa88  FUN_8014aa88 ====

void FUN_8014aa88(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043a3b0;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a3c0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043a3d0,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8014ab64  FUN_8014ab64 ====

void FUN_8014ab64(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a3cc;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar4 = (double)FLOAT_8043a3a8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    FUN_8014acdc(param_1);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    FUN_8014acdc(param_1);
  }
  zz_006ed8c_((double)FLOAT_8043a3d4,param_1);
  if (*(float *)(param_1 + 0x760) < FLOAT_8043a3d0) {
    zz_006ed8c_((double)FLOAT_8043a3d8,param_1);
  }
  FUN_80067310((double)FLOAT_8043a3b0,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 8014acdc  FUN_8014acdc ====

/* WARNING: Removing unreachable block (ram,0x8014ad78) */
/* WARNING: Removing unreachable block (ram,0x8014acec) */

void FUN_8014acdc(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  fVar1 = FLOAT_8043a3c0;
  if (*(int *)(param_1 + 0xcc) != 0) {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_8043a3b8) * FLOAT_8043a3dc;
  }
  dVar3 = (double)(fVar1 / FLOAT_8043a3cc);
  *(float *)(param_1 + 0x38) = fVar1 / FLOAT_8043a3cc;
  dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar3 * dVar2);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x48) = (float)(dVar3 * -dVar2);
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 8014ad94  zz_014ad94_ ====

void zz_014ad94_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033ed88)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014ade4  FUN_8014ade4 ====

void FUN_8014ade4(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a3c4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a3c8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a3a8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8014aef8  FUN_8014aef8 ====

void FUN_8014aef8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a3c8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a3c0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_8043a3e0;
    fVar1 = FLOAT_8043a3c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(undefined2 *)(param_1 + 0x54e) = 0xf;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8014afd8  FUN_8014afd8 ====

void FUN_8014afd8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar4 = DOUBLE_8043a3b8;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x558) =
         *(float *)(param_1 + 0x558) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar4);
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a3b4 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a3b0;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a3b4 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a3c0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(float *)(param_1 + 0x558) = fVar2;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar4 = (double)FLOAT_8043a3a8;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar4,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8014b130  FUN_8014b130 ====

void FUN_8014b130(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a3b8) * FLOAT_8043a3d4);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a3c8,param_1);
  FUN_80067310((double)FLOAT_8043a3b0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a3b0 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8014b22c  zz_014b22c_ ====

void zz_014b22c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_804346b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014b278  FUN_8014b278 ====

void FUN_8014b278(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(undefined1 *)(param_1 + 0x6f2) = 0;
  *(undefined1 *)(param_1 + 0x6f3) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043a3c0;
  *(float *)(param_1 + 0x50) = FLOAT_8043a3c0;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a3e4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_0067a28_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a3a8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8014b378  FUN_8014b378 ====

void FUN_8014b378(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  if ((*(byte *)(param_1 + 0x1d10) & 1) != 0) {
    zz_006d144_(param_1,0xc1);
  }
  if ((*(byte *)(param_1 + 0x1d10) & 2) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043a3b0,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a3e4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar3 = zz_0067a28_(param_1);
  if (*(short *)(param_1 + 1000) == 0xb03) {
    if (*(char *)(param_1 + 0x1cf0) != '\0') {
      *(undefined1 *)(param_1 + 0x6f2) = 2;
      *(undefined1 *)(param_1 + 0x6f3) = 2;
    }
    if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
      *(undefined1 *)(param_1 + 0x745) = 1;
    }
    if (*(char *)(param_1 + 0x1cf2) != '\0') {
      if (*(char *)(param_1 + 0x745) == '\0') {
        cVar1 = *(char *)(param_1 + 0x6ea);
        dVar4 = (double)FLOAT_8043a3a8;
        *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
        zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
        return;
      }
      *(undefined1 *)(param_1 + 0x745) = 0;
    }
  }
  fVar2 = FLOAT_8043a3c0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 8014b504  zz_014b504_ ====

void zz_014b504_(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
    if (*(char *)((int)param_2 + 7) != *(char *)(param_1 + 0x6e9)) {
      *(char *)((int)param_2 + 6) = *(char *)(param_1 + 0x6e9);
      *(undefined2 *)(param_2 + 1) = 0;
      *(undefined1 *)(param_1 + 0x1d4f) = 0;
    }
    fVar1 = FLOAT_8043a3c0;
    if ((char)*(byte *)((int)param_2 + 6) < '\0') {
      *(byte *)((int)param_2 + 6) = *(byte *)((int)param_2 + 6) & 0x7f;
      *param_2 = fVar1;
      *(undefined2 *)(param_2 + 1) = 0;
    }
    fVar2 = FLOAT_8043a3c0;
    fVar1 = FLOAT_8043a3b0;
    if (*(char *)((int)param_2 + 6) == '\0') {
      if ((FLOAT_8043a3c0 < *param_2) && (*param_2 = *param_2 - FLOAT_8043a3e8, *param_2 < fVar2)) {
        *param_2 = fVar2;
      }
    }
    else {
      if ((*param_2 < FLOAT_8043a3b0) && (*param_2 = *param_2 + FLOAT_8043a3e8, fVar1 < *param_2)) {
        *param_2 = fVar1;
      }
      *(short *)(param_2 + 1) = *(short *)(param_2 + 1) + 0x180;
    }
    dVar3 = zz_0045204_(*(short *)(param_2 + 1));
    *(float *)(param_1 + 0x1dc0) =
         *param_2 * (float)((double)FLOAT_8043a3f0 * dVar3) + FLOAT_8043a3ec;
    *(undefined1 *)((int)param_2 + 7) = *(undefined1 *)((int)param_2 + 6);
  }
  return;
}



// ==== 8014b634  zz_014b634_ ====

void zz_014b634_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x43;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8014b734;
    *(code **)(puVar1 + 0x10c) = FUN_8014bc2c;
    puVar1[0x13] = 3;
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



// ==== 8014b734  FUN_8014b734 ====

void FUN_8014b734(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8033edc4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8014b784  FUN_8014b784 ====

void FUN_8014b784(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x2c;
  iVar4 = -((int)*(short *)(&DAT_8033ed9a + iVar5) >> 0x1f);
  if (iVar4 == 0) {
    iVar4 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8033ed9a + iVar5));
  }
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar4 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar4 + *(short *)(&DAT_8033ed98 + iVar5) * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fcc1264),(float *)(param_9 + 0x20));
    zz_0083d60_(param_9,iVar4,0);
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8033edb8 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8033edb8 + iVar5);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8033edac + iVar5);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033edae + iVar5);
    uVar3 = (undefined2)*(undefined4 *)(&DAT_8033eda8 + iVar5);
    *(undefined2 *)(param_9 + 0x1c4) = uVar3;
    *(undefined2 *)(param_9 + 0x1c8) = uVar3;
    *(undefined2 *)(param_9 + 0x1c6) = uVar3;
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    *(undefined1 *)(param_9 + 0x84) = 0x10;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    uVar6 = zz_0089100_(param_9,0,1);
    iVar4 = zz_0006f98_(iVar4);
    uVar6 = zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),(float *)0x9,
                        (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    uVar6 = zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),(float *)0xa,
                        (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),(float *)0xb,
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    fVar2 = FLOAT_8043a3fc;
    fVar1 = FLOAT_8043a3f8;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined2 *)(param_9 + 0x144) = 0;
    *(undefined2 *)(param_9 + 0x146) = 0;
    *(float *)(param_9 + 0x148) = fVar1;
    *(float *)(param_9 + 0x14c) = fVar2;
    *(float *)(param_9 + 0x150) = fVar1;
    *(float *)(param_9 + 0x154) = fVar2;
    *(float *)(param_9 + 0x158) = fVar1;
    *(float *)(param_9 + 0x15c) = fVar2;
    *(float *)(param_9 + 0x160) = fVar1;
    *(float *)(param_9 + 0x164) = fVar2;
    *(float *)(param_9 + 0x168) = fVar1;
    zz_00f036c_(param_9,0xee);
  }
  return;
}



// ==== 8014b948  FUN_8014b948 ====

void FUN_8014b948(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  short sVar8;
  uint uVar9;
  
  fVar3 = FLOAT_8043a40c;
  fVar2 = FLOAT_8043a408;
  fVar1 = FLOAT_8043a404;
  iVar4 = (uint)*(byte *)(param_1 + 0x11) * 0x2c;
  if (*(char *)(param_1 + 0x19) == '\0') {
    uVar9 = (uint)*(char *)(param_1 + 0x1d9);
    if (uVar9 == 0) {
      if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_8033edbc + iVar4)) {
        fVar1 = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8033edc0 + iVar4);
        *(float *)(param_1 + 0x44) = fVar1;
        if (*(float *)(&DAT_8033edbc + iVar4) < fVar1) {
          *(float *)(param_1 + 0x44) = *(float *)(&DAT_8033edbc + iVar4);
        }
      }
      *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + 0x3333;
      *(short *)(param_1 + 0x146) = *(short *)(param_1 + 0x146) + 0x1999;
      fVar3 = FLOAT_8043a400;
      fVar2 = FLOAT_8043a3fc;
      fVar1 = FLOAT_8043a3f8;
      if (*(char *)(param_1 + 0x1a) == '\0') {
        *(float *)(param_1 + 0x160) = *(float *)(param_1 + 0x160) - FLOAT_8043a400;
        *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + fVar3;
        fVar1 = FLOAT_8043a3f8;
        if (*(float *)(param_1 + 0x160) <= fVar2) {
          *(undefined1 *)(param_1 + 0x1a) = 1;
          *(float *)(param_1 + 0x160) = fVar2;
          *(float *)(param_1 + 0x164) = fVar1;
        }
      }
      else {
        *(float *)(param_1 + 0x160) = *(float *)(param_1 + 0x160) + FLOAT_8043a400;
        *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) - fVar3;
        fVar2 = FLOAT_8043a3fc;
        if (fVar1 <= *(float *)(param_1 + 0x160)) {
          *(undefined1 *)(param_1 + 0x1a) = 0;
          *(float *)(param_1 + 0x160) = fVar1;
          *(float *)(param_1 + 0x164) = fVar2;
        }
      }
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x160);
      *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x164);
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x160);
      *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x164);
      *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x160);
      *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x164);
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_8033edb4 + iVar4),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8033edb0 + iVar4),param_1,
                   (char)*(undefined2 *)(&DAT_8033edae + iVar4));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      uVar5 = zz_0084170_(param_1);
      uVar6 = zz_0083714_(param_1);
      uVar7 = zz_0083244_((float *)(param_1 + 0x20));
      sVar8 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar8;
      uVar9 = countLeadingZeros((int)sVar8);
      uVar9 = uVar5 | uVar6 | uVar7 | (1 << (uVar9 & 0x1f) | 1U >> 0x20 - (uVar9 & 0x1f)) & 1;
    }
    if (uVar9 != 0) {
      *(undefined1 *)(param_1 + 0x19) = 1;
      zz_008aff0_(param_1);
      fVar1 = FLOAT_8043a3f8;
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      *(float *)(param_1 + 0x148) = fVar1;
      *(float *)(param_1 + 0x14c) = fVar1;
      *(float *)(param_1 + 0x150) = fVar1;
    }
  }
  else {
    *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) + FLOAT_8043a404;
    *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + fVar1;
    *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) - fVar2;
    if (*(float *)(param_1 + 0x168) <= fVar3) {
      *(float *)(param_1 + 0x168) = fVar3;
    }
    zz_0007cac_((double)*(float *)(param_1 + 0x168),*(int *)(param_1 + 0xe8));
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    if (*(short *)(param_1 + 0x1c) < 1) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return;
}



// ==== 8014bc0c  FUN_8014bc0c ====

void FUN_8014bc0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8014bc2c  FUN_8014bc2c ====

/* WARNING: Removing unreachable block (ram,0x8014bcb0) */
/* WARNING: Removing unreachable block (ram,0x8014bc4c) */

void FUN_8014bc2c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  float afStack_68 [12];
  float afStack_38 [13];
  
  if (*(char *)(param_1 + 0x19) == '\0') {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043a410 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x144) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,afStack_38);
    dVar3 = (double)*(float *)(param_1 + 0x14c);
    dVar4 = (double)*(float *)(param_1 + 0x150);
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x148),dVar3,dVar4,afStack_68);
    pfVar1 = afStack_38;
    uVar2 = gnt4_PSMTXConcat_bl(pfVar1,afStack_68,pfVar1);
    zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_38,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043a410 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x146) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,afStack_38);
    dVar3 = (double)*(float *)(param_1 + 0x158);
    dVar4 = (double)*(float *)(param_1 + 0x15c);
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x154),dVar3,dVar4,afStack_68);
    pfVar1 = afStack_38;
    uVar2 = gnt4_PSMTXConcat_bl(pfVar1,afStack_68,pfVar1);
    zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),afStack_38,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe4),0x44);
  }
  else {
    dVar3 = (double)*(float *)(param_1 + 0x14c);
    dVar4 = (double)*(float *)(param_1 + 0x150);
    gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x148),dVar3,dVar4,afStack_68);
    pfVar1 = afStack_38;
    uVar2 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_68,pfVar1);
    zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe8),afStack_38,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe8),0x44);
  }
  return;
}



// ==== 8014be88  FUN_8014be88 ====

void FUN_8014be88(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  if (*(short *)(param_1 + 1000) == 0xa02) {
    FUN_80139d14(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0xa07) {
    FUN_80139d14(param_1,1);
  }
  *(undefined1 *)(param_1 + 0x150) = 0;
  return;
}



// ==== 8014bef8  FUN_8014bef8 ====

void FUN_8014bef8(int param_1)

{
  zz_0148718_(param_1,(byte *)(param_1 + 0x14c));
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a420) * FLOAT_8043a418);
  }
  if (*(short *)(param_1 + 1000) == 0xa02) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xf4;
    if ((*(byte *)(param_1 + 0x7d2) & 8) == 0) {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 0xb;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 8;
    }
  }
  else if (*(short *)(param_1 + 1000) == 0xa07) {
    *(undefined1 *)(param_1 + 0x748) = 2;
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  }
  return;
}



// ==== 8014bfe0  FUN_8014bfe0 ====

uint FUN_8014bfe0(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  uVar1 = zz_006ab9c_(param_1);
  if (((uVar1 != 0) && ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) &&
     (*(short *)(param_1 + 1000) == 0xa02)) {
    if (*(float *)(param_1 + 0x694) <= FLOAT_8043a428) {
      iVar2 = zz_006dbe0_(param_1,0,1,1);
      if (iVar2 == 0) {
        uVar1 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),0);
      }
      else {
        zz_006bf80_(param_1);
        bVar3 = zz_0154e28_(param_1);
        uVar1 = (uint)bVar3;
        *(float *)(param_1 + 0x694) = FLOAT_8043a42c + *(float *)(param_1 + 0x1dc8);
      }
    }
  }
  return uVar1;
}



// ==== 8014c098  FUN_8014c098 ====

void FUN_8014c098(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8033f900)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8014c0d8  FUN_8014c0d8 ====

void FUN_8014c0d8(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0xa02) {
    zz_001ab6c_(param_1,0x3f);
  }
  else if (*(short *)(param_1 + 1000) == 0xa07) {
    zz_001ab6c_(param_1,0x4d);
  }
  return;
}



// ==== 8014c130  FUN_8014c130 ====

void FUN_8014c130(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xa07) {
    zz_006bf80_(param_1);
    zz_0046698_(param_1);
    zz_0176294_(param_1,1);
  }
  return;
}



// ==== 8014c17c  FUN_8014c17c ====

void FUN_8014c17c(int param_1)

{
  int iVar1;
  
  if (((*(short *)(param_1 + 1000) == 0xa07) &&
      (zz_006bf80_(param_1), *(int *)(param_1 + 0xcc) != 0)) && (*(int *)(param_1 + 200) != 0)) {
    iVar1 = 0;
    do {
      FUN_80176328(param_1,*(undefined1 *)(param_1 + 0x150));
      iVar1 = iVar1 + 1;
      *(char *)(param_1 + 0x150) = *(char *)(param_1 + 0x150) + '\x01';
      *(byte *)(param_1 + 0x150) = *(byte *)(param_1 + 0x150) & 7;
    } while (iVar1 < 3);
  }
  return;
}



// ==== 8014c20c  FUN_8014c20c ====

void FUN_8014c20c(int param_1)

{
  (*(code *)(&PTR_FUN_8033f914)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8014c248  FUN_8014c248 ====

void FUN_8014c248(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xa02) {
    (*(code *)(&PTR_FUN_8033f920)[*(char *)(param_1 + 0x581)])();
  }
  else {
    (*(code *)(&PTR_FUN_8033f934)[*(char *)(param_1 + 0x581)])();
  }
  return;
}



// ==== 8014c2b4  FUN_8014c2b4 ====

void FUN_8014c2b4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8014c2e4  FUN_8014c2e4 ====

void FUN_8014c2e4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8014c314  FUN_8014c314 ====

void FUN_8014c314(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8014c344  FUN_8014c344 ====

void FUN_8014c344(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033f948)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014c394  FUN_8014c394 ====

void FUN_8014c394(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a430;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = 0x14;
  *(undefined1 *)(param_1 + 0x6ea) = 5;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a434,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a438;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a428;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 8014c4c8  FUN_8014c4c8 ====

void FUN_8014c4c8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a434,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a428;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_8043a43c;
    fVar1 = FLOAT_8043a428;
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



// ==== 8014c5b8  FUN_8014c5b8 ====

void FUN_8014c5b8(int param_1)

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
    zz_006e1ac_(param_1,0xc0,1);
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a43c * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    dVar4 = (double)FLOAT_8043a440;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a43c * -dVar3);
    FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    zz_004cd24_(param_1,0xf);
    fVar2 = FLOAT_8043a428;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if ((fVar1 <= fVar2) || (*(short *)(param_1 + 0x54a) < 1)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8014c6b0  FUN_8014c6b0 ====

void FUN_8014c6b0(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a420) * FLOAT_8043a418);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x544) == '\0') {
      if (*(char *)(param_1 + 0x1b01) != '\0') {
        dVar3 = (double)FLOAT_8043a438;
        *(undefined1 *)(param_1 + 0x544) = 1;
        zz_004beb8_(dVar3,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
      }
    }
    else {
      zz_006ed8c_((double)FLOAT_8043a434,param_1);
    }
    FUN_80067310((double)FLOAT_8043a440,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a428;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a428) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a428;
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



// ==== 8014c7ec  FUN_8014c7ec ====

void FUN_8014c7ec(int param_1)

{
  zz_0148384_(param_1);
  return;
}



// ==== 8014c810  FUN_8014c810 ====

void FUN_8014c810(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1d;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8014c90c;
    *(code **)(puVar1 + 0x10c) = FUN_8014cb70;
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



// ==== 8014c90c  FUN_8014c90c ====

void FUN_8014c90c(int param_1)

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
  (*(code *)(&PTR_FUN_8033fe6c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8014c998  FUN_8014c998 ====

void FUN_8014c998(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  
  cVar1 = *(char *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = cVar1 * 0x14;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_8033fe5a + iVar3);
  uVar2 = *(undefined4 *)(&DAT_8033fe60 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8033fe5c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033fe64 + iVar3);
  uVar4 = zz_00055fc_();
  *(short *)(param_9 + 0x74) = (short)(uVar4 << 8);
  zz_0018f88_((int *)(param_9 + 0x174),(int)(&PTR_DAT_8033fe68)[cVar1 * 5],(float *)(param_9 + 0x58)
             );
  *(code **)(param_9 + 0x100) = FUN_8014caf0;
  uVar6 = zz_0089100_(param_9,1,1);
  iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
  zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8033fe58 + iVar3),param_12,param_13,
              param_14,param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 8014ca68  FUN_8014ca68 ====

void FUN_8014ca68(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  zz_0018fd8_((int *)(param_1 + 0x174),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 8014cabc  FUN_8014cabc ====

void FUN_8014cabc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8014cad0  FUN_8014cad0 ====

void FUN_8014cad0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8014caf0  FUN_8014caf0 ====

void FUN_8014caf0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x8c);
  zz_00455fc_((float *)(iVar1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 100));
  zz_00457d4_('z',(float *)(iVar1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  return;
}



// ==== 8014cb70  FUN_8014cb70 ====

void FUN_8014cb70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  return;
}



// ==== 8014cbb0  FUN_8014cbb0 ====

undefined1 * FUN_8014cbb0(int param_1,char param_2,char param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  uint uVar2;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x3e;
    puVar1[0x13] = param_4;
    puVar1[0x11] = param_3 + param_2 * '\x04' & 0x3f;
    uVar2 = zz_00055fc_();
    puVar1[0x12] = (char)uVar2 + (char)(uVar2 / 0xe) * -0xe;
    *(code **)(puVar1 + 0xc) = FUN_8014ccf4;
    *(code **)(puVar1 + 0x10c) = FUN_8014d1c0;
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
    FUN_8014ccf4((int)puVar1);
  }
  return puVar1;
}



// ==== 8014ccf4  FUN_8014ccf4 ====

void FUN_8014ccf4(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8033feec)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8014cd44  FUN_8014cd44 ====

void FUN_8014cd44(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  double dVar7;
  
  uVar5 = (uint)*(byte *)(param_9 + 0x12);
  iVar4 = (char)*(byte *)(param_9 + 0x12) * 4;
  iVar3 = -((int)*(short *)(&DAT_8033fe82 + iVar4) >> 0x1f);
  if (iVar3 == 0) {
    iVar3 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8033fe82 + iVar4));
  }
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114));
    gnt4_PSMTXMultVec_bl
              ((float *)(param_9 + 0x114),(float *)&DAT_8033feb8,(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x11c);
    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 300);
    *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x13c);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)DAT_8033fed0,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    fVar2 = FLOAT_8043a448;
    *(float *)(param_9 + 0x44) = DAT_8033fed0;
    *(undefined2 *)(param_9 + 0x1c) = DAT_8033fedc;
    *(char *)(param_9 + 0x1cb) = (char)DAT_8033fede;
    *(undefined2 *)(param_9 + 0x144) = 0;
    *(char *)(param_9 + 0x12) = (char)DAT_8033fec4;
    *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0xb4);
    dVar7 = (double)*(float *)(param_9 + 0x148);
    fVar1 = (float)(dVar7 * (double)DAT_8033fec8);
    *(float *)(param_9 + 0xb4) = fVar1;
    *(float *)(param_9 + 0xc0) = fVar1;
    *(float *)(param_9 + 0x60) = fVar1;
    *(float *)(param_9 + 0x5c) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    *(float *)(param_9 + 0x60) = fVar2;
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    *(code **)(param_9 + 0x100) = FUN_8014d0fc;
    uVar6 = zz_0089100_(param_9,1,1);
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar4 = (int)*(short *)(&DAT_8033fe80 + iVar4);
    zz_0006fb4_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                *(int *)(param_9 + 0xe0),iVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
    zz_00086b8_((double)FLOAT_8043a44c,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                *(int *)(param_9 + 0xe0),iVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    if (*(char *)(param_9 + 0x13) == '\0') {
      zz_00f036c_(param_9,0x11a);
    }
    else {
      zz_00f036c_(param_9,0x11b);
    }
  }
  return;
}



// ==== 8014cf0c  FUN_8014cf0c ====

void FUN_8014cf0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  float fVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  
  uVar7 = (uint)*(char *)(param_9 + 0x1d9);
  if (uVar7 == 0) {
    zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15,
                param_16);
    *(short *)(param_9 + 0x144) = *(short *)(param_9 + 0x144) + 0x400;
    if (*(float *)(param_9 + 0xb4) < *(float *)(param_9 + 0x14c)) {
      *(float *)(param_9 + 0xb4) =
           FLOAT_8043a450 * *(float *)(param_9 + 0x148) + *(float *)(param_9 + 0xb4);
      if (*(float *)(param_9 + 0x14c) < *(float *)(param_9 + 0xb4)) {
        *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0x14c);
      }
    }
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + 0x500;
    if (*(float *)(param_9 + 0x44) < DAT_8033fed8) {
      fVar2 = *(float *)(param_9 + 0x44) + DAT_8033fed4;
      *(float *)(param_9 + 0x44) = fVar2;
      if (DAT_8033fed8 < fVar2) {
        *(float *)(param_9 + 0x44) = DAT_8033fed8;
      }
    }
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    FUN_80083874((double)DAT_8033fee4,param_9);
    FUN_80083ad4((double)DAT_8033fee0,param_9,(char)DAT_8033fede);
    zz_00833ec_(param_9);
    zz_0083524_(param_9);
    uVar3 = zz_0084170_(param_9);
    uVar4 = zz_0083714_(param_9);
    uVar5 = zz_0083244_((float *)(param_9 + 0x20));
    sVar6 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar6;
    uVar7 = countLeadingZeros((int)sVar6);
    uVar7 = uVar3 | uVar4 | uVar5 | (1 << (uVar7 & 0x1f) | 1U >> 0x20 - (uVar7 & 0x1f)) & 1;
  }
  if (uVar7 != 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 8014d0a0  FUN_8014d0a0 ====

void FUN_8014d0a0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8014d0dc  FUN_8014d0dc ====

void FUN_8014d0dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8014d0fc  FUN_8014d0fc ====

/* WARNING: Removing unreachable block (ram,0x8014d1a4) */
/* WARNING: Removing unreachable block (ram,0x8014d10c) */

void FUN_8014d0fc(int param_1)

{
  bool bVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,param_1 + 0x38,&DAT_802b0ca8);
  }
  dVar4 = (double)*(float *)(param_1 + 0x20);
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x144));
  dVar2 = (double)FLOAT_8043a454;
  *(float *)(param_1 + 0x120) = (float)dVar4;
  *(float *)(param_1 + 0x130) =
       *(float *)(param_1 + 0xb4) * (float)(dVar2 * dVar3) + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 8014d1c0  FUN_8014d1c0 ====

void FUN_8014d1c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  return;
}



// ==== 8014d2fc  FUN_8014d2fc ====

void FUN_8014d2fc(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0x174);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e3758_(param_1,-0x7fcbf3b8,3,puVar3 + 3,(float *)(puVar3 + 0x21));
    zz_00e3758_(param_1,-0x7fcbf328,3,puVar3 + 0xc,(float *)(puVar3 + 0x2a));
    zz_00e3758_(param_1,-0x7fcbf298,2,puVar3 + 0x15,(float *)(puVar3 + 0x33));
    zz_00e3758_(param_1,-0x7fcbf238,1,puVar3 + 0x1b,(float *)(puVar3 + 0x39));
    zz_00e3758_(param_1,-0x7fcbf208,1,puVar3 + 0x1e,(float *)(puVar3 + 0x3c));
  }
  *(undefined2 *)(param_1 + 0x195a) = 0xf000;
  *(undefined2 *)(param_1 + 0x1972) = 0x1000;
  return;
}



// ==== 8014d3fc  FUN_8014d3fc ====

void FUN_8014d3fc(int param_1)

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
      zz_00e38a4_(param_1,(float *)&DAT_80340c48,3,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      zz_00e38a4_(param_1,(float *)&DAT_80340cd8,3,(float *)(puVar2 + 0xc),(float *)(puVar2 + 0x2a))
      ;
      zz_00e38a4_(param_1,(float *)&DAT_80340d68,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x33)
                 );
      zz_00e38a4_(param_1,(float *)&DAT_80340dc8,1,(float *)(puVar2 + 0x1b),(float *)(puVar2 + 0x39)
                 );
      zz_00e38a4_(param_1,(float *)&DAT_80340df8,1,(float *)(puVar2 + 0x1e),(float *)(puVar2 + 0x3c)
                 );
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcbf3b8,3,(float *)(puVar2 + 3),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcbf328,3,(float *)(puVar2 + 0xc),(float *)(puVar2 + 0x48));
      FUN_800e4f9c(param_1,-0x7fcbf298,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x51));
      FUN_800e4f9c(param_1,-0x7fcbf238,1,(float *)(puVar2 + 0x1b),(float *)(puVar2 + 0x57));
      FUN_800e4f9c(param_1,-0x7fcbf208,1,(float *)(puVar2 + 0x1e),(float *)(puVar2 + 0x5a));
    }
  }
  return;
}



