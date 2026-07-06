// ==== 800b3018  FUN_800b3018 ====

void FUN_800b3018(int param_1)

{
  double dVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    dVar2 = DOUBLE_804383a8;
    *(undefined1 *)(param_1 + 0x6ec) = 0xff;
    dVar1 = DOUBLE_804383a0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                      dVar2) * DOUBLE_804383a0);
    *(short *)(param_1 + 0x18dc) =
         (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                      dVar2) * dVar1);
  }
  *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) & 0xfb;
  return;
}



// ==== 800b30b0  FUN_800b30b0 ====

void FUN_800b30b0(int param_1)

{
  zz_00b2d5c_(param_1,(short *)(param_1 + 0x144));
  if ('\0' < *(char *)(param_1 + 0x6f2)) {
    *(char *)(param_1 + 0x6f2) = *(char *)(param_1 + 0x6f2) + -1;
  }
  return;
}



// ==== 800b3104  FUN_800b3104 ====

void FUN_800b3104(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802fd270)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800b3144  FUN_800b3144 ====

void FUN_800b3144(int param_1,undefined1 param_2)

{
  zz_00c71c0_(param_1,param_2);
  return;
}



// ==== 800b3164  FUN_800b3164 ====

void FUN_800b3164(int param_1)

{
  zz_00c67bc_(param_1,6,0);
  zz_00c67bc_(param_1,7,0);
  return;
}



// ==== 800b31a8  FUN_800b31a8 ====

void FUN_800b31a8(int param_1)

{
  (*(code *)(&PTR_FUN_802fd27c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800b31e4  FUN_800b31e4 ====

void FUN_800b31e4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_802fd288)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b3238  FUN_800b3238 ====

void FUN_800b3238(int param_1)

{
  (*(code *)(&PTR_FUN_802fd2b0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b3274  FUN_800b3274 ====

void FUN_800b3274(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  uVar3 = zz_006e004_(param_1);
  if ((int)uVar3 < 0) {
    *(undefined1 *)(param_1 + 0x581) = 5;
  }
  fVar2 = FLOAT_804383b4;
  fVar1 = FLOAT_804383b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  dVar4 = (double)FLOAT_804383b8;
  *(float *)(param_1 + 0x560) = fVar1;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_004beb8_(dVar4,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800b3300  FUN_800b3300 ====

void FUN_800b3300(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = zz_006dee8_(param_1,1);
  uVar4 = 1;
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    uVar4 = 0xf;
  }
  zz_004cd24_(param_1,uVar4);
  fVar2 = FLOAT_804383b4;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(undefined1 *)(param_1 + 0x581) = 5;
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      *(undefined1 *)(param_1 + 0x581) = 9;
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
      zz_00b3510_(param_1);
    }
  }
  return;
}



// ==== 800b33f0  FUN_800b33f0 ====

void FUN_800b33f0(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_804383b4) {
    *(undefined1 *)(param_1 + 0x15c) = 0;
    *(undefined1 *)(param_1 + 0x15d) = 0;
    if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
      iVar2 = zz_006dbe0_(param_1,0,1,0);
      if (iVar2 != 0) {
        zz_006bf80_(param_1);
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        *(undefined1 *)(param_1 + 0x581) = 0;
        return;
      }
      goto LAB_800b34dc;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (*(char *)(param_1 + 0x581) == '\0') {
      zz_006dee8_(param_1,1);
    }
    else {
      zz_006d0dc_(param_1,0xc1,0);
    }
  }
  fVar1 = FLOAT_804383b4;
  if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) &&
     (*(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
     fVar1 < *(float *)(param_1 + 0x55c))) {
    return;
  }
LAB_800b34dc:
  *(undefined1 *)(param_1 + 0x15d) = 0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800b3510  zz_00b3510_ ====

void zz_00b3510_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_804383c0;
  *(float *)(param_1 + 0x558) = FLOAT_804383bc;
  *(float *)(param_1 + 0x55c) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    zz_00b73b4_(param_1,*(undefined1 *)(param_1 + 0x6e8));
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x6e8) + 0x15c) = 2;
  }
  return;
}



// ==== 800b3584  FUN_800b3584 ====

void FUN_800b3584(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802fd2bc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b35cc  FUN_800b35cc ====

void FUN_800b35cc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804383b4;
  if ((iVar3 == 0) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00b3510_(param_1);
  }
  return;
}



// ==== 800b3654  FUN_800b3654 ====

void FUN_800b3654(int param_1)

{
  (*(code *)(&PTR_FUN_802fd2c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b3690  FUN_800b3690 ====

void FUN_800b3690(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804383b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  if (*(short *)(param_1 + 0x1dfc) < 0) {
    *(undefined1 *)(param_1 + 0x6ec) = 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 2;
  }
  zz_004beb8_((double)FLOAT_804383b8,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),8,1);
  return;
}



// ==== 800b3718  FUN_800b3718 ====

void FUN_800b3718(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804383b4;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(undefined1 *)(param_1 + 0x581) = 5;
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      *(undefined1 *)(param_1 + 0x581) = 9;
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1b03) == '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_00b3510_(param_1);
    }
  }
  return;
}



// ==== 800b37f8  FUN_800b37f8 ====

void FUN_800b37f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804383b4) {
    *(undefined1 *)(param_9 + 0x15c) = 0;
    *(undefined1 *)(param_9 + 0x15d) = 0;
    if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        if (((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
            zz_006bf80_(param_9);
            *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
            if (*(char *)(param_9 + 0x6ec) == '\x02') {
              if (*(short *)(param_9 + 0x1dfc) < -0x7ff) {
                dVar3 = (double)FLOAT_804383b8;
                *(undefined1 *)(param_9 + 0x6ec) = 4;
                zz_004beb8_(dVar3,param_9,1,2,(int)*(char *)(param_9 + 0x6ec),8,1);
              }
            }
            else if (0x7ff < *(short *)(param_9 + 0x1dfc)) {
              dVar3 = (double)FLOAT_804383b8;
              *(undefined1 *)(param_9 + 0x6ec) = 2;
              zz_004beb8_(dVar3,param_9,1,2,(int)*(char *)(param_9 + 0x6ec),8,1);
            }
            *(undefined1 *)(param_9 + *(char *)(param_9 + 0x6e8) + 0x15c) = 2;
            return;
          }
          zz_006a3d0_(param_9,'\0',0,0);
          return;
        }
        zz_006a3d0_(param_9,'\0',3,0);
        return;
      }
      goto LAB_800b39a0;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) {
    param_2 = (double)*(float *)(param_9 + 0x55c);
    dVar2 = (double)FLOAT_804383b4;
    *(float *)(param_9 + 0x55c) = (float)(param_2 - (double)*(float *)(param_9 + 0x1dc8));
    dVar3 = (double)*(float *)(param_9 + 0x55c);
    if (dVar2 < dVar3) {
      return;
    }
  }
LAB_800b39a0:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x19,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800b39d4  FUN_800b39d4 ====

void FUN_800b39d4(int param_1)

{
  (*(code *)(&PTR_FUN_802fd2d4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b3a10  FUN_800b3a10 ====

void FUN_800b3a10(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804383b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  if (*(short *)(param_1 + 0x1dfc) < 0) {
    *(undefined1 *)(param_1 + 0x6ec) = 0x10;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 0xe;
  }
  zz_004beb8_((double)FLOAT_804383b8,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,
              0xffffffff);
  return;
}



// ==== 800b3a98  FUN_800b3a98 ====

void FUN_800b3a98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804383b4;
  if (-1 < iVar3) {
    if ((0 < iVar3) ||
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_00b3510_(param_1);
    }
    if (*(char *)(param_1 + 0x6ec) == '\x0e') {
      if (*(short *)(param_1 + 0x1dfc) < -0x7ff) {
        dVar4 = (double)FLOAT_804383b8;
        *(undefined1 *)(param_1 + 0x6ec) = 0x10;
        zz_004beb8_(dVar4,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),4,2);
      }
    }
    else if (0x7ff < *(short *)(param_1 + 0x1dfc)) {
      dVar4 = (double)FLOAT_804383b8;
      *(undefined1 *)(param_1 + 0x6ec) = 0xe;
      zz_004beb8_(dVar4,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),4,2);
    }
    return;
  }
  *(undefined1 *)(param_1 + 0x581) = 7;
  zz_006a3d0_(param_1,'\0',0,2);
  return;
}



// ==== 800b3bc0  FUN_800b3bc0 ====

void FUN_800b3bc0(int param_1)

{
  (*(code *)(&PTR_FUN_802fd2e0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b3bfc  FUN_800b3bfc ====

void FUN_800b3bfc(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804383b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  if (*(short *)(param_1 + 0x1dfc) < 0) {
    *(undefined1 *)(param_1 + 0x6ec) = 8;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 6;
  }
  zz_004beb8_((double)FLOAT_804383b8,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,
              0xffffffff);
  return;
}



// ==== 800b3c84  FUN_800b3c84 ====

void FUN_800b3c84(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804383b4;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
      zz_006d0dc_(param_1,0x81,0);
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(undefined1 *)(param_1 + 0x581) = 5;
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      *(undefined1 *)(param_1 + 0x581) = 9;
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00b3510_(param_1);
  }
  return;
}



// ==== 800b3d74  zz_00b3d74_ ====

void zz_00b3d74_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804383b4) {
    *(undefined1 *)(param_9 + 0x15c) = 0;
    *(undefined1 *)(param_9 + 0x15d) = 0;
    if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
          zz_006bf80_(param_9);
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if (*(char *)(param_9 + 0x6ec) == '\x02') {
            if (*(short *)(param_9 + 0x1dfc) < -0x7ff) {
              dVar3 = (double)FLOAT_804383b8;
              *(undefined1 *)(param_9 + 0x6ec) = 4;
              zz_004beb8_(dVar3,param_9,1,2,(int)*(char *)(param_9 + 0x6ec),8,1);
            }
          }
          else if (0x7ff < *(short *)(param_9 + 0x1dfc)) {
            dVar3 = (double)FLOAT_804383b8;
            *(undefined1 *)(param_9 + 0x6ec) = 2;
            zz_004beb8_(dVar3,param_9,1,2,(int)*(char *)(param_9 + 0x6ec),8,1);
          }
          *(undefined1 *)(param_9 + *(char *)(param_9 + 0x6e8) + 0x15c) = 2;
          return;
        }
        zz_006a3d0_(param_9,'\0',0,0);
        return;
      }
      goto LAB_800b3ef8;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) {
    param_2 = (double)*(float *)(param_9 + 0x55c);
    dVar2 = (double)FLOAT_804383b4;
    *(float *)(param_9 + 0x55c) = (float)(param_2 - (double)*(float *)(param_9 + 0x1dc8));
    dVar3 = (double)*(float *)(param_9 + 0x55c);
    if (dVar2 < dVar3) {
      return;
    }
  }
LAB_800b3ef8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x19,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800b3f2c  FUN_800b3f2c ====

void FUN_800b3f2c(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802fd2ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b3f74  FUN_800b3f74 ====

void FUN_800b3f74(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804383b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_804383c4;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  dVar2 = (double)FLOAT_804383b8;
  *(undefined1 *)(param_1 + 0x6ec) = 0xc;
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_804383b8,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  *(float *)(param_1 + 0x80c) = FLOAT_804383b4;
  return;
}



// ==== 800b404c  FUN_800b404c ====

void FUN_800b404c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d0dc_(param_1,0x81,0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00b3510_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800b40fc  FUN_800b40fc ====

void FUN_800b40fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00b3d74_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800b411c  FUN_800b411c ====

void FUN_800b411c(int param_1)

{
  (*(code *)(&PTR_FUN_802fd2f8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b4158  FUN_800b4158 ====

void FUN_800b4158(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  zz_00fed6c_(param_1);
  return;
}



// ==== 800b4198  FUN_800b4198 ====

void FUN_800b4198(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802fd324)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b41f4  FUN_800b41f4 ====

void FUN_800b41f4(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_804383c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_804383b8,param_1,0xf,3,1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b42b0  FUN_800b42b0 ====

void FUN_800b42b0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar3 = FLOAT_804383b4;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar2 = FLOAT_804383b0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    fVar3 = FLOAT_804383d0;
    fVar2 = FLOAT_804383b4;
    if (*(int *)(param_1 + 0xcc) == 0) {
      fVar1 = FLOAT_804383cc *
              *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    }
    else {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_804383b0;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800b43b0  FUN_800b43b0 ====

void FUN_800b43b0(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_804383d4,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800b4444  FUN_800b4444 ====

void FUN_800b4444(int param_1)

{
  float fVar1;
  double dVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  dVar2 = DOUBLE_804383d8;
  fVar1 = FLOAT_804383b0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_804383e4;
    fVar3 = FLOAT_804383e0;
    dVar5 = (double)FLOAT_804383b8;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar2);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar2);
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar3;
    *(undefined1 *)(param_1 + 0x542) = 4;
    *(float *)(param_1 + 0x564) = fVar4;
    zz_004beb8_(dVar5,param_1,0xf,3,2,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x6f2) = 2;
    zz_0137984_(param_1,0);
  }
  return;
}



// ==== 800b4510  FUN_800b4510 ====

void FUN_800b4510(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  char cVar4;
  double dVar5;
  
  *(undefined1 *)(param_1 + 0x6f2) = 2;
  iVar3 = zz_006de44_(param_1,0xf0f00);
  if (iVar3 != 0) {
    cVar4 = *(char *)(param_1 + 0x542) + -1;
    *(char *)(param_1 + 0x542) = cVar4;
    fVar1 = FLOAT_804383cc;
    if (cVar4 == '\0') {
      *(float *)(param_1 + 0x564) = *(float *)(param_1 + 0x564) + FLOAT_804383e4;
      *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar1;
    }
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_006d144_(param_1,0xc0);
    FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    fVar2 = FLOAT_804383b4;
    *(short *)(param_1 + 0x18dc) =
         (short)(int)(FLOAT_804383e8 * *(float *)(param_1 + 0x1dc8) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                            DOUBLE_804383a8));
    fVar1 = *(float *)(param_1 + 0x564) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x564) = fVar1;
    if (fVar1 <= fVar2) {
      dVar5 = (double)FLOAT_804383b8;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x18dc) = 0;
      zz_004beb8_(dVar5,param_1,0xf,3,3,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 800b4648  FUN_800b4648 ====

void FUN_800b4648(int param_1)

{
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800b46c8  FUN_800b46c8 ====

void FUN_800b46c8(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802fd33c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b4724  FUN_800b4724 ====

void FUN_800b4724(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_804383c0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
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
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804383b8,param_1,0xf,3,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800b4828  FUN_800b4828 ====

void FUN_800b4828(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804383c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800b4904  FUN_800b4904 ====

void FUN_800b4904(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if ((*(char *)(param_1 + 0x1cf0) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804383f0 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_804383c4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804383f0 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_804383f4,param_1), 0 < (int)uVar3)) {
    fVar2 = FLOAT_804383cc;
    fVar1 = FLOAT_804383b4;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar2;
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x54a) = 0x1e;
    *(undefined1 *)(param_1 + 0x6ea) = 0;
  }
  return;
}



// ==== 800b4a3c  FUN_800b4a3c ====

void FUN_800b4a3c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_804383a8) * FLOAT_804383f8);
  }
  fVar3 = FLOAT_804383b4;
  if (('\0' < *(char *)(param_1 + 0x1cef)) &&
     (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) {
    *(float *)(param_1 + 0x558) = FLOAT_804383c4;
    if (0 < *(short *)(param_1 + 0x54a)) {
      *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_00c67bc_(param_1,0,cVar1);
    }
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar3 = FLOAT_804383b4;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar3 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar3;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_804383ec,param_1);
  FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
    *(undefined2 *)(param_1 + 0x18da) = 0;
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800b4c1c  FUN_800b4c1c ====

void FUN_800b4c1c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802fd34c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b4c84  FUN_800b4c84 ====

void FUN_800b4c84(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_804383c0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  uVar2 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804383b8,param_1,0xf,3,4,0xffffffff,0xffffffff);
  zz_00c71c0_(param_1,3);
  return;
}



// ==== 800b4d9c  FUN_800b4d9c ====

void FUN_800b4d9c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804383c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800b4e78  FUN_800b4e78 ====

void FUN_800b4e78(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if ((*(char *)(param_1 + 0x1cf0) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804383f0 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_804383c4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804383f0 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_804383f4,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_804383cc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar1;
  }
  return;
}



// ==== 800b4f98  FUN_800b4f98 ====

void FUN_800b4f98(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  fVar1 = FLOAT_804383b4;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_804383ec,param_1);
  FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
    *(undefined2 *)(param_1 + 0x18da) = 0;
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800b50d0  FUN_800b50d0 ====

void FUN_800b50d0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_802fd35c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b5124  FUN_800b5124 ====

void FUN_800b5124(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x542)) {
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802fd370)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b518c  FUN_800b518c ====

void FUN_800b518c(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0xa0) == 0) {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_804383c8;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_804383b8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(undefined1 *)(param_1 + 0x542) = 0;
  iVar3 = zz_006dbe0_(param_1,2,1,0);
  if (iVar3 != 0) {
    *(undefined1 *)(param_1 + 0x542) = 1;
    FUN_800061a8(param_1,0x11);
    zz_01f1ea0_(param_1,0);
  }
  *(float *)(param_1 + 0x80c) = FLOAT_804383b4;
  return;
}



// ==== 800b5310  FUN_800b5310 ====

void FUN_800b5310(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438400 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800b53e4  FUN_800b53e4 ====

void FUN_800b53e4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_804383ec,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804383b4;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (*(char *)(param_1 + 0x542) == '\0') {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      if (fVar2 < *(float *)(param_1 + 0x48)) {
        *(float *)(param_1 + 0x48) = fVar2;
      }
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_80438408 + *(float *)(param_1 + 0x1dc8);
      return;
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_804383f0;
    *(undefined2 *)(param_1 + 0x548) = 0x21;
    fVar4 = FLOAT_80438404;
    *(undefined2 *)(param_1 + 0x54a) = 0x37;
    *(undefined2 *)(param_1 + 0x54c) = 6;
    *(float *)(param_1 + 0x38) = fVar2;
    *(float *)(param_1 + 0x3c) = fVar3;
    *(float *)(param_1 + 0x40) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0066530_(param_1,0x2d);
    zz_0092dcc_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_804383b8;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x6f2) = 2;
    zz_0137984_(param_1,1);
    zz_006dbe0_(param_1,2,1,1);
  }
  dVar5 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438400 < dVar5) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800b5598  FUN_800b5598 ====

void FUN_800b5598(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  double dVar6;
  double dVar7;
  
  *(undefined1 *)(param_1 + 0x6f2) = 2;
  iVar4 = zz_006de44_(param_1,0xf0f00);
  if (iVar4 != 0) {
    sVar5 = *(short *)(param_1 + 0x54c);
    *(short *)(param_1 + 0x54c) = sVar5 + -1;
    if (*(short *)(param_1 + 0x54c) < 1) {
      *(undefined2 *)(param_1 + 0x54c) = 1;
    }
    if (*(short *)(param_1 + 0x54a) < sVar5) {
      sVar5 = *(short *)(param_1 + 0x54a);
    }
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) - sVar5;
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + sVar5;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x3c);
  }
  dVar6 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar6);
  dVar6 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar7 = (double)FLOAT_804383c4;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar6);
  FUN_80067310(dVar7,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1b01) != '\0') &&
     (*(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -0xb, dVar6 = DOUBLE_80438410,
     fVar3 = FLOAT_8043840c, *(short *)(param_1 + 0x548) < 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_804383b4;
    *(float *)(param_1 + 0x558) = fVar3;
    fVar3 = FLOAT_80438418;
    dVar7 = (double)FLOAT_804383b8;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar6);
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar7,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800b5754  FUN_800b5754 ====

void FUN_800b5754(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_804383a8) * FLOAT_804383f8);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804383c4,param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804383b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_00677b0_(param_1);
    if ((iVar3 == 0) || (-1 < *(char *)(param_1 + 0x1cef))) {
      zz_00b22f4_(param_1);
    }
    else {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804383fc + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800b5878  zz_00b5878_ ====

bool zz_00b5878_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x45;
    *(code **)(puVar1 + 0xc) = FUN_800b5990;
    *(code **)(puVar1 + 0x10c) = FUN_800b5e7c;
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



// ==== 800b5990  FUN_800b5990 ====

void FUN_800b5990(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802fd86c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800b5a28  FUN_800b5a28 ====

void FUN_800b5a28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  puVar7 = &DAT_802fd850;
  puVar5 = &DAT_802fd820;
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
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fd027dc),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802fd822 + iVar2) * 0x30 + 0x8fc);
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802fd860 + iVar3),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438420,&local_28,&local_28);
  uVar9 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802fd860 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802fd852 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_802fd854 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_802fd856 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_802fd864 + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar2 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x600),
              *(int *)(param_9 + 0xe0),3,iVar1,iVar4,puVar5,iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802fd850 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x4c);
  }
  return;
}



// ==== 800b5c5c  FUN_800b5c5c ====

void FUN_800b5c5c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00b5e14_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00b5e14_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_802fd868 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_802fd85c + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_802fd858 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_802fd854 + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_00b5e14_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),2);
            }
          }
          else {
            zz_00b5e14_(param_1);
          }
        }
      }
    }
    else {
      zz_00b5e14_(param_1);
    }
  }
  else {
    zz_00b5e14_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),2);
  }
  return;
}



// ==== 800b5e14  zz_00b5e14_ ====

void zz_00b5e14_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800b5e50  FUN_800b5e50 ====

void FUN_800b5e50(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800b5e5c  FUN_800b5e5c ====

void FUN_800b5e5c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b5e7c  FUN_800b5e7c ====

void FUN_800b5e7c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800b5ed8  FUN_800b5ed8 ====

/* WARNING: Removing unreachable block (ram,0x800b6114) */
/* WARNING: Removing unreachable block (ram,0x800b5ee8) */

void FUN_800b5ed8(int param_1,undefined1 param_2,short param_3)

{
  undefined1 *puVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float fStack_68;
  float local_64;
  float afStack_5c [4];
  undefined4 auStack_4c [4];
  undefined4 auStack_3c [5];
  undefined4 local_28;
  uint uStack_24;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x10;
    puVar1[0x10] = 0x53;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800b613c;
    *(code **)(puVar1 + 0x10c) = FUN_800b64a8;
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
    iVar2 = (uint)(byte)puVar1[0x11] * 0x30;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_802fd881)[iVar2] * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fd0277c),(float *)(puVar1 + 0x20));
    uStack_24 = (int)param_3 ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80438428 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80438438)),
                        afStack_5c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + (char)(&DAT_802fd881)[iVar2] * 0x30 + 0x8d4),afStack_5c,
                        afStack_5c);
    *(float *)(puVar1 + 0x38) = afStack_5c[(char)(&DAT_802fd8ac)[iVar2]];
    *(undefined4 *)(puVar1 + 0x3c) = auStack_4c[(char)(&DAT_802fd8ac)[iVar2]];
    *(undefined4 *)(puVar1 + 0x40) = auStack_3c[(char)(&DAT_802fd8ac)[iVar2]];
    if ((&DAT_802fd8ad)[iVar2] == '\x01') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043842c,(float *)(puVar1 + 0x38),(float *)(puVar1 + 0x38));
    }
    zz_006ebb4_((float *)(puVar1 + 0x38),&fStack_68);
    dVar4 = (double)local_64;
    local_64 = FLOAT_80438430;
    dVar3 = gnt4_PSVECMag_bl(&fStack_68);
    iVar2 = FUN_800452a0(dVar4,dVar3);
    *(short *)(puVar1 + 0x70) = -(short)iVar2;
    *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(puVar1 + 0x74) = 0;
    if ((puVar1[0xd0] & 4) == 0) {
      *(undefined4 *)(puVar1 + 200) = 0;
    }
  }
  return;
}



// ==== 800b613c  FUN_800b613c ====

void FUN_800b613c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_802fd910)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800b618c  FUN_800b618c ====

void FUN_800b618c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(undefined1 *)(param_9 + 0x1b) = 3;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x98) = 5;
  uVar1 = DAT_802b0cb4;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  uVar2 = DAT_802b0cb8;
  *(undefined4 *)(param_9 + 0x9c) = uVar1;
  uVar1 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar2;
  *(undefined4 *)(param_9 + 0xa4) = uVar1;
  gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar4 + -0x7fd02760),
                      (float *)(param_9 + 0x58));
  zz_0048288_(param_9);
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_802fd882)[iVar4]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar6 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802fd890 + iVar4),(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802fd890 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_802fd894 + iVar4);
    *(undefined2 *)(param_9 + 0x1c) = 300;
    iVar3 = zz_0006f78_(param_9);
    zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_802fd880)[iVar4],
                (int)*(char *)(param_9 + 0x88),iVar5,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    if (-1 < (char)(&DAT_802fd883)[iVar4]) {
      zz_00f036c_(param_9,(int)(char)(&DAT_802fd883)[iVar4]);
    }
    if (-1 < *(short *)(&DAT_802fd8ae + iVar4)) {
      *(undefined1 *)(param_9 + 0xaf) = 0;
      zz_001ac80_(param_9,(char)*(undefined2 *)(&DAT_802fd8ae + iVar4));
    }
    FUN_800b6308(param_9);
  }
  return;
}



// ==== 800b6308  FUN_800b6308 ====

void FUN_800b6308(int param_1)

{
  int iVar1;
  char cVar2;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (*(char *)(param_1 + 0x11) == '\0') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1000;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1000;
  }
  if (((0 < *(short *)(param_1 + 0x1c)) &&
      (iVar1 = zz_0083244_((float *)(param_1 + 0x20)), iVar1 == 0)) &&
     ((iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x30, *(char *)(param_1 + 0x1d9) == '\0' ||
      (cVar2 = *(char *)(param_1 + 0x1b) + -1, *(char *)(param_1 + 0x1b) = cVar2, '\0' < cVar2)))) {
    FUN_80083874((double)*(float *)(&DAT_802fd89c + iVar1),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_802fd898 + iVar1),param_1,
                 (char)*(undefined4 *)(&DAT_802fd894 + iVar1));
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    iVar1 = zz_0083714_(param_1);
    if (iVar1 == 0) {
      iVar1 = zz_0084170_(param_1);
      if (iVar1 == 0) {
        return;
      }
      *(undefined1 *)(param_1 + 0x18) = 2;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 800b6444  FUN_800b6444 ====

void FUN_800b6444(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0xaf) = 0xff;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800b6488  FUN_800b6488 ====

void FUN_800b6488(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b64a8  FUN_800b64a8 ====

/* WARNING: Removing unreachable block (ram,0x800b64bc) */

void FUN_800b64a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438428 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 800b6510  zz_00b6510_ ====

void zz_00b6510_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x1f,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0xc;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 2;
    *(code **)(puVar1 + 0xc) = FUN_800b6610;
    *(code **)(puVar1 + 0x10c) = FUN_800b6794;
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



// ==== 800b6610  FUN_800b6610 ====

void FUN_800b6610(int param_1)

{
  (*(code *)(&PTR_FUN_802fd9f8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800b664c  FUN_800b664c ====

void FUN_800b664c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  uVar1 = 1;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 0x89) =
       *(undefined1 *)(*(int *)(*(int *)(param_9 + 0x8c) + 0x4b0) + 0xf);
  iVar3 = *(char *)(param_9 + 0x11) * 0xc;
  puVar5 = (undefined4 *)(&DAT_802fd9ec + iVar3);
  uVar4 = *puVar5;
  uVar2 = *(undefined4 *)(&DAT_802fd9f0 + iVar3);
  *(undefined4 *)(param_9 + 100) = uVar4;
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  uVar2 = *(undefined4 *)(&DAT_802fd9f4 + iVar3);
  *(undefined4 *)(param_9 + 0x6c) = uVar2;
  *(code **)(param_9 + 0x100) = FUN_800b6850;
  uVar6 = zz_0089100_(param_9,0x21,1);
  uVar6 = zz_00b68b4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar1,
                      uVar2,uVar4,puVar5,in_r9,in_r10);
  zz_00b68b4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,uVar1,uVar2,
              uVar4,puVar5,in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 800b6700  FUN_800b6700 ====

void FUN_800b6700(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  
  iVar3 = zz_00b69d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = countLeadingZeros(iVar3);
  bVar4 = zz_008b290_();
  uVar2 = countLeadingZeros((uint)bVar4);
  if (uVar1 >> 5 != 0 || uVar2 >> 5 != 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 800b6774  FUN_800b6774 ====

void FUN_800b6774(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b6794  FUN_800b6794 ====

void FUN_800b6794(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_58 [3];
  float afStack_4c [15];
  
  iVar2 = 0;
  iVar4 = param_9 + 0x144;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar2) != 0) {
      gnt4_PSQUATScale_bl((double)*(float *)(*(int *)(param_9 + 0x8c) + 0x7fc),
                          (float *)(iVar4 + 0x10),afStack_58);
      pfVar1 = afStack_58;
      uVar5 = zz_00456a0_((float *)(param_9 + 0x114),afStack_4c,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_4c,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x28;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 800b6850  FUN_800b6850 ====

void FUN_800b6850(int param_1)

{
  zz_00455fc_((float *)(*(int *)(param_1 + 0x8c) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
              (float *)(param_1 + 0x114),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  return;
}



// ==== 800b68b4  zz_00b68b4_ ====

void zz_00b68b4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    uVar3 = 1 << iVar5;
    if (((int)*(short *)(param_9 + 0x1e) & uVar3) == 0) {
      iVar4 = param_9 + iVar5 * 0x28;
      *(int *)(iVar4 + 0x168) = param_10;
      iVar1 = param_10 * 0xc;
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)uVar3;
      *(undefined2 *)(iVar4 + 0x164) = 0;
      *(undefined2 *)(iVar4 + 0x166) = *(undefined2 *)(&DAT_802fd9ca + iVar1);
      zz_0018f88_((int *)(iVar4 + 0x144),(int)(&PTR_DAT_802fd9cc)[param_10 * 3],
                  (float *)(iVar4 + 0x154));
      uVar6 = zz_0019338_((int *)(iVar4 + 0x14c),*(int *)(&DAT_802fd9d0 + iVar1),
                          (float *)(iVar4 + 0x160));
      uVar2 = (uint)*(short *)(&DAT_802fd9c8 + iVar1);
      if ((uVar2 & 0x100) == 0) {
        zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + iVar5 * 4 + 0xe0),uVar2 & 0xff,uVar3,param_13,param_14,
                    param_15,param_16);
      }
      else {
        zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + iVar5 * 4 + 0xe0),(float *)(uVar2 & 0xff),
                    (int)*(char *)(param_9 + 0x88),param_13,param_14,param_15,param_16);
      }
      zz_0007cac_((double)*(float *)(iVar4 + 0x160),*(int *)(param_9 + iVar5 * 4 + 0xe0));
      iVar5 = (int)*(char *)(param_9 + 0x13);
    }
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 800b69d8  zz_00b69d8_ ====

int zz_00b69d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  iVar2 = 0;
  piVar4 = (int *)(param_9 + 0x144);
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar2) != 0) {
      sVar1 = *(short *)(piVar4 + 8);
      *(short *)(piVar4 + 8) = sVar1 + 1;
      if ((*(short *)((int)piVar4 + 0x22) <= (short)(sVar1 + 1)) &&
         (*(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) & ~(ushort)(1 << iVar2),
         piVar4[9] == 1)) {
        zz_00b68b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,2,
                    param_11,param_12,param_13,param_14,param_15,param_16);
      }
      zz_0018fd8_(piVar4,(int)*(short *)(piVar4 + 8),(float *)(piVar4 + 4));
      param_11 = (float *)(piVar4 + 7);
      zz_0019370_(piVar4 + 2,(int)*(short *)(piVar4 + 8),param_11);
      param_1 = zz_0007cac_((double)(float)piVar4[7],*(int *)(iVar3 + 0xe0));
    }
    piVar4 = piVar4 + 10;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return (int)*(short *)(param_9 + 0x1e);
}



// ==== 800b6ac8  FUN_800b6ac8 ====

bool FUN_800b6ac8(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x48;
    *(code **)(puVar1 + 0xc) = FUN_800b6bd4;
    *(code **)(puVar1 + 0x10c) = FUN_800b7358;
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



// ==== 800b6bd4  FUN_800b6bd4 ====

void FUN_800b6bd4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802fda44)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800b6c6c  FUN_800b6c6c ====

void FUN_800b6c6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  double dVar11;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  puVar9 = &DAT_802fda20;
  puVar7 = &DAT_802fda08;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar10 = *(int *)(param_9 + 0x90);
  iVar8 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x24;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar4 = iVar8 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar2 = iVar4;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fd025f4),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar10 + (char)(&DAT_802fda0a)[iVar4] * 0x30 + 0x8fc);
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802fda28 + iVar5),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802fda28 + iVar5);
  *(short *)(param_9 + 0x1c) = (short)*(undefined4 *)(&DAT_802fda24 + iVar5);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_802fda22 + iVar5);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar3 = *(int *)(iVar10 + 200);
  if (iVar3 == 0) {
    local_28 = *(float *)(iVar10 + 0x8dc);
    local_24 = *(undefined4 *)(iVar10 + 0x8ec);
    local_20 = *(undefined4 *)(iVar10 + 0x8fc);
    gnt4_PSQUATScale_bl((double)FLOAT_80438440,&local_28,&local_28);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x144));
    if (*(float *)(DAT_8043625c + 0x3c) <= *(float *)(param_9 + 0x144)) {
      if (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_9 + 0x144)) {
        *(float *)(param_9 + 0x144) = *(float *)(DAT_8043625c + 0x38);
      }
    }
    else {
      *(float *)(param_9 + 0x144) = *(float *)(DAT_8043625c + 0x3c);
    }
    if (*(float *)(DAT_8043625c + 0x44) <= *(float *)(param_9 + 0x14c)) {
      if (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_9 + 0x14c)) {
        *(float *)(param_9 + 0x14c) = *(float *)(DAT_8043625c + 0x40);
      }
    }
    else {
      *(float *)(param_9 + 0x14c) = *(float *)(DAT_8043625c + 0x44);
    }
  }
  else {
    uVar1 = *(undefined4 *)(iVar3 + 0x68);
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(iVar3 + 100);
    *(undefined4 *)(param_9 + 0x148) = uVar1;
    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(iVar3 + 0x6c);
  }
  dVar11 = FUN_8003d964((double)FLOAT_80438444,param_9,(float *)(param_9 + 0x144));
  *(float *)(param_9 + 0x148) = (float)dVar11;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar3 = zz_0006f98_(iVar10);
  zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_802fda08 + iVar4),iVar2,iVar6,puVar7,
              iVar8,puVar9);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802fda20 + iVar5));
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x4e);
    zz_01371d0_(param_9,(undefined4 *)(param_9 + 0x144));
  }
  return;
}



// ==== 800b6f58  FUN_800b6f58 ====

void FUN_800b6f58(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float fStack_24;
  float local_20;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x24;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar3 = zz_0083334_((float *)(param_1 + 0x20));
    if (iVar3 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00b72fc_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        cVar1 = *(char *)(param_1 + 0x19);
        if (cVar1 == '\x01') {
          if (*(char *)(param_1 + 0x274) != '\0') {
            zz_00b72fc_(param_1);
            zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x20),0);
            return;
          }
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x20));
          if ((double)FLOAT_80438450 < dVar4) {
            dVar5 = 1.0 / SQRT(dVar4);
            dVar5 = DOUBLE_80438458 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438460);
            dVar5 = DOUBLE_80438458 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438460);
            dVar4 = (double)(float)(dVar4 * DOUBLE_80438458 * dVar5 *
                                            -(dVar4 * dVar5 * dVar5 - DOUBLE_80438460));
          }
          if ((dVar4 <= (double)FLOAT_80438468) || (*(short *)(param_1 + 0x1c) < 1)) {
            *(undefined1 *)(param_1 + 0x19) = 2;
          }
          zz_006c440_((double)*(float *)(&DAT_802fda34 + iVar2),param_1,(float *)(param_1 + 0x150));
        }
        else if (cVar1 < '\x01') {
          if (-1 < cVar1) {
            if ((*(byte *)(param_1 + 0x274) & 2) != 0) {
              zz_00b72fc_(param_1);
              zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x20),0);
              return;
            }
            if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_802fda2c + iVar2)) {
              *(float *)(param_1 + 0x44) =
                   *(float *)(param_1 + 0x44) + *(float *)(&DAT_802fda30 + iVar2);
            }
            else {
              *(float *)(param_1 + 0x44) = *(float *)(&DAT_802fda2c + iVar2);
            }
            gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
            gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                                (float *)(param_1 + 0x38));
            gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                             (float *)(param_1 + 0x20));
            *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
            if (*(short *)(param_1 + 0x1c) < 1) {
              *(undefined1 *)(param_1 + 0x19) = 1;
              gnt4_PSVECSubtract_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x20),&fStack_24)
              ;
              gnt4_PSQUATScale_bl((double)FLOAT_80438448,&fStack_24,&fStack_24);
              local_20 = FLOAT_8043844c;
              gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&fStack_24,(float *)(param_1 + 0x150));
              *(undefined2 *)(param_1 + 0x1c) = 300;
            }
          }
        }
        else if (cVar1 < '\x03') {
          if (*(char *)(param_1 + 0x274) != '\0') {
            zz_00b72fc_(param_1);
            zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x20),0);
            return;
          }
          dVar4 = FUN_8003d964((double)FLOAT_8043846c,param_1,(float *)(param_1 + 0x20));
          if (*(float *)(param_1 + 0x24) <= (float)((double)FLOAT_8043846c + dVar4)) {
            zz_00b72fc_(param_1);
            zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x20),0);
            return;
          }
          if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_802fda38 + iVar2)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_802fda3c + iVar2);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(&DAT_802fda38 + iVar2);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          zz_006c440_((double)*(float *)(&DAT_802fda40 + iVar2),param_1,(float *)(param_1 + 0x144));
        }
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        iVar2 = zz_0083714_(param_1);
        if (iVar2 != 0) {
          zz_00b72fc_(param_1);
        }
      }
    }
    else {
      zz_00b72fc_(param_1);
      FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    }
  }
  else {
    zz_00b72fc_(param_1);
    zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x2a0),0);
  }
  return;
}



// ==== 800b72fc  zz_00b72fc_ ====

void zz_00b72fc_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 800b732c  FUN_800b732c ====

void FUN_800b732c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800b7338  FUN_800b7338 ====

void FUN_800b7338(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b7358  FUN_800b7358 ====

void FUN_800b7358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800b73b4  zz_00b73b4_ ====

void zz_00b73b4_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,6);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x10;
    puVar1[0x10] = 0x12;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800b75ac;
    *(code **)(puVar1 + 0x10c) = FUN_800b7c18;
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
    iVar2 = (uint)(byte)puVar1[0x11] * 0x30;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_802fda5a)[iVar2] * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fd025a4),(float *)(puVar1 + 0x20));
    *(undefined4 *)(puVar1 + 0x38) =
         *(undefined4 *)
          (param_1 + (char)(&DAT_802fda5a)[iVar2] * 0x30 + (char)(&DAT_802fda84)[iVar2] * 4 + 0x8d4)
    ;
    *(undefined4 *)(puVar1 + 0x3c) =
         *(undefined4 *)
          (param_1 + (char)(&DAT_802fda5a)[iVar2] * 0x30 + (char)(&DAT_802fda84)[iVar2] * 4 + 0x8e4)
    ;
    *(undefined4 *)(puVar1 + 0x40) =
         *(undefined4 *)
          (param_1 + (char)(&DAT_802fda5a)[iVar2] * 0x30 + (char)(&DAT_802fda84)[iVar2] * 4 + 0x8f4)
    ;
    if ((&DAT_802fda85)[iVar2] == '\x01') {
      gnt4_PSQUATScale_bl((double)FLOAT_80438470,(float *)(puVar1 + 0x38),(float *)(puVar1 + 0x38));
    }
    iVar2 = FUN_8006c334((double)FLOAT_80438474,(int)puVar1,(float *)(param_1 + 0x518));
    if (iVar2 != 0) {
      zz_0083d60_((int)puVar1,param_1,0);
    }
  }
  return;
}



// ==== 800b75ac  FUN_800b75ac ====

void FUN_800b75ac(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  DAT_80436330 = param_1 + 0x144;
  (*(code *)(&PTR_FUN_802fdab8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800b764c  FUN_800b764c ====

void FUN_800b764c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438478;
  *(undefined1 *)(param_9 + 0x98) = 0;
  fVar2 = FLOAT_8043847c;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa0) = fVar2;
  uVar8 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 300;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_802fda5b)[iVar5]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar4 = zz_0006f78_(param_9);
    iVar7 = 0;
    iVar3 = param_9;
    do {
      uVar8 = zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                          *(int *)(iVar3 + 0xe0),(float *)0x8,(int)*(char *)(param_9 + 0x88),iVar6,
                          in_r8,in_r9,in_r10);
      iVar7 = iVar7 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar7 < 5);
    zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xf4),(float *)0x7,(int)*(char *)(param_9 + 0x88),iVar6,in_r8,
                in_r9,in_r10);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802fda68 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    fVar1 = FLOAT_80438478;
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802fda68 + iVar5);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_802fda6c + iVar5);
    *(undefined2 *)(param_9 + 0x72) = 0;
    *(undefined2 *)(param_9 + 0x80) = 0;
    *(undefined2 *)(param_9 + 0x70) = 0;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined1 *)(param_9 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x145) = 0;
    *(float *)(param_9 + 0x148) = fVar1;
    zz_00b77c4_(param_9);
    zz_00f036c_(param_9,199);
  }
  return;
}



// ==== 800b77c4  zz_00b77c4_ ====

/* WARNING: Removing unreachable block (ram,0x800b7ac8) */
/* WARNING: Removing unreachable block (ram,0x800b7ac0) */
/* WARNING: Removing unreachable block (ram,0x800b77dc) */
/* WARNING: Removing unreachable block (ram,0x800b77d4) */

void zz_00b77c4_(int param_1)

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
  undefined4 auStack_48 [3];
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0xccc;
  if (*(char *)(param_1 + 0x145) != '\0') {
    dVar8 = (double)FLOAT_8043847c;
    dVar9 = (double)FLOAT_80438480;
    iVar6 = *(char *)(param_1 + 0x144) + 4;
    iVar7 = iVar6 / 5 + (iVar6 >> 0x1f);
    iVar6 = iVar6 + (iVar7 - (iVar7 >> 0x1f)) * -5;
    for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x145); iVar7 = iVar7 + 1) {
      iVar4 = param_1 + iVar6 * 0x14;
      fVar1 = (float)((double)*(float *)(iVar4 + 0x158) + dVar8);
      *(float *)(iVar4 + 0x158) = fVar1;
      if ((double)fVar1 <= dVar9) {
        zz_00b7af0_((float *)(iVar4 + 0x14c));
      }
      else {
        *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + -1;
      }
      iVar6 = iVar6 + 4;
      iVar4 = iVar6 / 5 + (iVar6 >> 0x1f);
      iVar6 = iVar6 + (iVar4 - (iVar4 >> 0x1f)) * -5;
    }
  }
  fVar3 = FLOAT_80438478;
  fVar1 = *(float *)(param_1 + 0x148) - FLOAT_8043847c;
  *(float *)(param_1 + 0x148) = fVar1;
  if ((fVar1 <= fVar3) && (*(char *)(param_1 + 0x145) < '\x05')) {
    *(float *)(param_1 + 0x148) = FLOAT_80438484;
    cVar2 = *(char *)(param_1 + 0x144);
    iVar7 = param_1 + cVar2 * 0x14;
    *(float *)(iVar7 + 0x158) = fVar3;
    uVar5 = zz_00055fc_();
    *(short *)(iVar7 + 0x15c) = (short)(uVar5 << 0xb);
    *(undefined1 *)(iVar7 + 0x15e) = 0;
    zz_00b7af0_((float *)(iVar7 + 0x14c));
    iVar6 = cVar2 + 1;
    iVar7 = iVar6 / 5 + (iVar6 >> 0x1f);
    *(char *)(param_1 + 0x144) = (char)iVar6 + ((char)iVar7 - (char)(iVar7 >> 0x1f)) * -5;
    *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + '\x01';
  }
  if (*(char *)(param_1 + 0x11) == '\0') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1000;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1000;
  }
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar7 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar7 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        iVar7 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
        FUN_80083874((double)*(float *)(&DAT_802fda74 + iVar7),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_802fda70 + iVar7),param_1,
                     (char)*(undefined4 *)(&DAT_802fda6c + iVar7));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        iVar7 = zz_0083714_(param_1);
        if (iVar7 == 0) {
          iVar7 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_3c,
                              auStack_48);
          if (iVar7 != 0) {
            *(float *)(param_1 + 0x20) = local_3c;
            *(undefined4 *)(param_1 + 0x24) = local_38;
            *(undefined4 *)(param_1 + 0x28) = local_34;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_3c,auStack_48);
            zz_0019550_(param_1,&local_3c,0);
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



// ==== 800b7af0  zz_00b7af0_ ====

void zz_00b7af0_(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_80438488;
  iVar5 = *(char *)((int)param_1 + 0x12) * 0x10;
  fVar4 = *(float *)(&DAT_802fdac8 + iVar5);
  fVar1 = *(float *)(&DAT_802fdacc + iVar5);
  fVar2 = *(float *)(&DAT_802fdad0 + iVar5);
  fVar3 = *(float *)(&DAT_802fdad4 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_80438488 == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)((int)param_1 + 0x12) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_802fdac8 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_802fdacc + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_802fdad0 + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_802fdad4 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_802fdac8 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)((int)param_1 + 0x12) = *(char *)((int)param_1 + 0x12) + '\x01';
  return;
}



// ==== 800b7bbc  FUN_800b7bbc ====

void FUN_800b7bbc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800b7bf8  FUN_800b7bf8 ====

void FUN_800b7bf8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b7c18  FUN_800b7c18 ====

/* WARNING: Removing unreachable block (ram,0x800b7da4) */
/* WARNING: Removing unreachable block (ram,0x800b7d9c) */
/* WARNING: Removing unreachable block (ram,0x800b7c30) */
/* WARNING: Removing unreachable block (ram,0x800b7c28) */

void FUN_800b7c18(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
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
  
  DAT_80436330 = param_9 + 0x144;
  dVar9 = (double)FLOAT_8043848c;
  iVar1 = *(char *)(param_9 + 0x144) + 4;
  iVar5 = iVar1 / 5 + (iVar1 >> 0x1f);
  iVar1 = iVar1 + (iVar5 - (iVar5 >> 0x1f)) * -5;
  dVar8 = DOUBLE_80438490;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x145); iVar5 = iVar5 + 1) {
    local_48 = 0x43300000;
    iVar4 = param_9 + iVar1 * 0x14;
    iVar3 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    uStack_44 = (int)*(short *)(iVar4 + 0x15c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(float)(dVar9 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_44) - dVar8)
                                       ),afStack_78,0x78);
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
  uStack_44 = (int)*(short *)(param_9 + 0x70) ^ 0x80000000;
  dVar8 = (double)FLOAT_8043848c;
  iVar5 = *(int *)(param_9 + 0xf4);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_44)
                                                             - DOUBLE_80438490)),afStack_78,0x78);
  pfVar2 = afStack_78;
  uVar6 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar6,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_78,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar5,0x44);
  return;
}



// ==== 800b7dc0  zz_00b7dc0_ ====

void zz_00b7dc0_(int param_1)

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
    zz_00e48cc_(param_1,-0x7fd00fa8,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 800b7e38  zz_00b7e38_ ====

void zz_00b7e38_(int param_1)

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
      FUN_800e4a18((double)FLOAT_80438498,param_1,(float *)&DAT_802ff058,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd00fa8,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 800b7ecc  zz_00b7ecc_ ====

void zz_00b7ecc_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 800b7f04  zz_00b7f04_ ====

void zz_00b7f04_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd00fa8,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fd00fa8,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 800b7fa4  zz_00b7fa4_ ====

void zz_00b7fa4_(int param_1)

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
    zz_00e48cc_(param_1,-0x7fd00eb8,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 800b801c  zz_00b801c_ ====

void zz_00b801c_(int param_1)

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
      FUN_800e4a18((double)FLOAT_8043849c,param_1,(float *)&DAT_802ff148,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd00eb8,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 800b80b0  zz_00b80b0_ ====

void zz_00b80b0_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 800b80e8  zz_00b80e8_ ====

void zz_00b80e8_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd00eb8,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fd00eb8,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 800b839c  zz_00b839c_ ====

/* WARNING: Removing unreachable block (ram,0x800b8648) */
/* WARNING: Removing unreachable block (ram,0x800b83ac) */

void zz_00b839c_(int param_1,short *param_2)

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
  dVar6 = DOUBLE_804384a8;
  fVar1 = FLOAT_804384a0;
  uStack_3c = (int)*param_2 ^ 0x80000000;
  local_40 = 0x43300000;
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  local_30 = 0x43300000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_804384a8) * FLOAT_804384a0);
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
    local_48 = FLOAT_804384a4;
    dVar7 = gnt4_PSVECMag_bl(&local_4c);
    iVar3 = FUN_800452a0(dVar6,dVar7);
    local_58 = *(float *)(param_1 + 0xb20);
    local_54 = *(float *)(param_1 + 0xb30);
    local_50 = *(undefined4 *)(param_1 + 0xb40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x50c),&local_58,&local_58);
    dVar7 = (double)local_54;
    local_54 = FLOAT_804384a4;
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



// ==== 800b866c  FUN_800b866c ====

void FUN_800b866c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x503:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7dc0_(param_1);
    zz_00c74ec_(param_1,0x12);
    break;
  case 0x506:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4 + '\x04');
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7dc0_(param_1);
    zz_00c74ec_(param_1,0x14);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
    break;
  case 0x507:
    zz_00b7dc0_(param_1);
    zz_00c74ec_(param_1,0x12);
    *(undefined1 *)(param_1 + 0x4a8) = 1;
    break;
  case 0x508:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7dc0_(param_1);
    zz_00c74ec_(param_1,0x14);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
    break;
  case 0x50f:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4 + '\b');
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7fa4_(param_1);
    zz_00c74ec_(param_1,0x16);
    break;
  case 0x512:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4 + '\f');
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7fa4_(param_1);
    zz_00c74ec_(param_1,0x18);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
    break;
  case 0x513:
    zz_00b7fa4_(param_1);
    zz_00c74ec_(param_1,0x16);
    *(undefined1 *)(param_1 + 0x4a8) = 1;
    break;
  case 0x514:
    iVar4 = 0;
    do {
      zz_017a9e0_(param_1,(char)iVar4 + '\b');
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    zz_00b7fa4_(param_1);
    zz_00c74ec_(param_1,0x18);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
  }
  *(undefined1 *)(param_1 + 0x18c) = 0xf;
  fVar1 = FLOAT_804384b0;
  *(undefined1 *)(param_1 + 0x18d) = 0;
  fVar2 = FLOAT_804384b4;
  *(float *)(param_1 + 0x14c) = fVar1;
  fVar3 = FLOAT_804384b8;
  *(float *)(param_1 + 0x150) = fVar1;
  *(float *)(param_1 + 0x154) = fVar1;
  *(float *)(param_1 + 0x158) = fVar2;
  *(float *)(param_1 + 0x15c) = fVar3;
  *(float *)(param_1 + 0x160) = fVar2;
  return;
}



// ==== 800b889c  FUN_800b889c ====

void FUN_800b889c(int param_1)

{
  zz_0046698_(param_1);
  zz_00b839c_(param_1,(short *)(param_1 + 0x144));
  *(undefined1 *)(param_1 + 0x7de) = 1;
  return;
}



// ==== 800b88dc  FUN_800b88dc ====

void FUN_800b88dc(int param_1)

{
  short sVar1;
  
  zz_00b839c_(param_1,(short *)(param_1 + 0x144));
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0x503) || (sVar1 == 0x506)) || (sVar1 == 0x507)) {
    zz_00b7e38_(param_1);
  }
  else if (((sVar1 == 0x50f) || (sVar1 == 0x512)) || (sVar1 == 0x513)) {
    zz_00b801c_(param_1);
  }
  return;
}



// ==== 800b8968  FUN_800b8968 ====

void FUN_800b8968(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0x503) || (sVar1 == 0x506)) || (sVar1 == 0x507)) {
    zz_00b7ecc_(param_1);
  }
  else if (((sVar1 == 0x50f) || (sVar1 == 0x512)) || (sVar1 == 0x513)) {
    zz_00b80b0_(param_1);
  }
  return;
}



// ==== 800b89c4  FUN_800b89c4 ====

void FUN_800b89c4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0x503) || (sVar1 == 0x506)) || (sVar1 == 0x507)) {
    zz_00b7f04_(param_1);
  }
  else if (((sVar1 == 0x50f) || (sVar1 == 0x512)) || (sVar1 == 0x513)) {
    zz_00b80e8_(param_1);
  }
  return;
}



// ==== 800b8a20  FUN_800b8a20 ====

void FUN_800b8a20(undefined4 param_1,char param_2,char param_3)

{
  (**(code **)(&DAT_80433ac8 + param_2 * 4))(param_1,(int)param_3);
  return;
}



// ==== 800b8a5c  FUN_800b8a5c ====

void FUN_800b8a5c(int param_1)

{
  undefined1 uVar1;
  
  uVar1 = 0x17;
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar1 = 0x1a;
  }
  zz_01ef2b4_(param_1,1,uVar1);
  return;
}



// ==== 800b8a94  FUN_800b8a94 ====

void FUN_800b8a94(int param_1)

{
  (*(code *)(&PTR_FUN_802ff2fc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800b8ad0  FUN_800b8ad0 ====

void FUN_800b8ad0(int param_1)

{
  zz_00b8af0_(param_1);
  return;
}



// ==== 800b8af0  zz_00b8af0_ ====

void zz_00b8af0_(int param_1)

{
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,0);
  (*(code *)(&PTR_FUN_802ff310)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 800b8b50  FUN_800b8b50 ====

void FUN_800b8b50(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_804384a4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  FUN_80067310((double)FLOAT_804384bc,param_1,*(short *)(param_1 + 0x5ae));
  if (*(float *)(param_1 + 0x48) < FLOAT_804384c0) {
    *(float *)(param_1 + 0x48) = FLOAT_804384c0;
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804384c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_804384c8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b8c44  FUN_800b8c44 ====

void FUN_800b8c44(int param_1)

{
  float fVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_804384bc,param_1,*(short *)(param_1 + 0x5ae));
  if (*(float *)(param_1 + 0x48) < FLOAT_804384c0) {
    *(float *)(param_1 + 0x48) = FLOAT_804384c0;
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804384c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    if (((*(short *)(param_1 + 1000) == 0x506) || (*(short *)(param_1 + 1000) == 0x512)) &&
       (iVar2 = zz_006dbe0_(param_1,0,1,1), iVar2 == 0)) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
      *(float *)(param_1 + 0x694) = FLOAT_804384cc + *(float *)(param_1 + 0x1dc8);
      return;
    }
    fVar1 = FLOAT_804384a4;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6eb) = 0;
    *(float *)(param_1 + 0x558) = fVar1;
    *(byte *)(param_1 + 0x18d) = *(byte *)(param_1 + 0x18d) ^ 1;
  }
  return;
}



// ==== 800b8d6c  FUN_800b8d6c ====

void FUN_800b8d6c(int param_1)

{
  int iVar1;
  char *pcVar2;
  
  FUN_80067310((double)FLOAT_804384bc,param_1,*(short *)(param_1 + 0x5ae));
  if (*(float *)(param_1 + 0x48) < FLOAT_804384c0) {
    *(float *)(param_1 + 0x48) = FLOAT_804384c0;
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804384c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  if (FLOAT_804384a4 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_804384d0;
    switch(*(undefined2 *)(param_1 + 1000)) {
    default:
      iVar1 = 0;
      break;
    case 0x506:
    case 0x512:
      iVar1 = 1;
    }
    pcVar2 = &DAT_802ff31c + *(char *)(param_1 + 0x6eb) * 2 + iVar1 * 0x10;
    if (*pcVar2 < '\0') {
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      if (*(char *)(param_1 + 0x1cee) != '\0') {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
          zz_006a474_(param_1);
        }
        else {
          zz_006a5a4_(param_1);
        }
        *(float *)(param_1 + 0x694) = FLOAT_804384cc + *(float *)(param_1 + 0x1dc8);
      }
    }
    else {
      *(char *)(param_1 + 0x6eb) = *(char *)(param_1 + 0x6eb) + '\x01';
      zz_016cc24_(param_1,*pcVar2);
      if (-1 < pcVar2[1]) {
        zz_016cc24_(param_1,pcVar2[1]);
      }
    }
  }
  return;
}



// ==== 800b8f10  FUN_800b8f10 ====

void FUN_800b8f10(int param_1)

{
  (*(code *)(&PTR_FUN_802ff380)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b8f4c  FUN_800b8f4c ====

void FUN_800b8f4c(int param_1)

{
  (*(code *)(&PTR_FUN_802ff394)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b8f88  FUN_800b8f88 ====

void FUN_800b8f88(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804384d4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_804384a4;
  dVar2 = (double)FLOAT_804384c8;
  *(float *)(param_1 + 0x50) = FLOAT_804384a4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,0,1,10,2);
  return;
}



// ==== 800b9018  FUN_800b9018 ====

void FUN_800b9018(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804384a4;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_804384c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,2,0xffffffff,1);
  }
  return;
}



// ==== 800b90a8  FUN_800b90a8 ====

void FUN_800b90a8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_00b9378_(param_1,param_1 + 0x144);
  }
  zz_00b946c_(param_1,param_1 + 0x144);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800b9130  FUN_800b9130 ====

void FUN_800b9130(int param_1)

{
  (*(code *)(&PTR_FUN_802ff3a0)[*(char *)(param_1 + 0x540)])();
  gnt4_PSQUATScale_bl((double)FLOAT_804384c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b91a0  FUN_800b91a0 ====

void FUN_800b91a0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804384d4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d144_(param_1,0x81);
  fVar1 = FLOAT_804384a4;
  *(float *)(param_1 + 0x50) = FLOAT_804384a4;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x0f')) {
    zz_004beb8_((double)FLOAT_804384c8,param_1,0xf,0,0xf,10,2);
  }
  *(undefined1 *)(param_1 + 0x709) = 0x1f;
  return;
}



// ==== 800b9260  FUN_800b9260 ====

void FUN_800b9260(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804384a4;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0x81), iVar3 != 0)) {
    dVar4 = (double)FLOAT_804384c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,3,2,3,0xffffffff,1);
  }
  return;
}



// ==== 800b92f0  FUN_800b92f0 ====

void FUN_800b92f0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_00b9378_(param_1,param_1 + 0x144);
  }
  zz_00b946c_(param_1,param_1 + 0x144);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800b9378  zz_00b9378_ ====

void zz_00b9378_(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 uVar5;
  
  if (*(char *)(param_1 + 0x746) == '\0') {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 == 0) {
      return;
    }
    *(char *)(param_1 + 0x746) = *(char *)(param_1 + 0x746) + '\x01';
  }
  fVar1 = FLOAT_804384d8;
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
  fVar2 = FLOAT_804384dc;
  *(undefined2 *)(param_1 + 0x548) = 0x4000;
  *(undefined2 *)(param_1 + 0x54a) = 0xfd00;
  *(undefined2 *)(param_1 + 0x54c) = 0x14;
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_2 + 0x44) = fVar2 * *(float *)(param_1 + 0x814);
  if ((*(byte *)(param_1 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_2 + 0x44) = *(undefined4 *)(param_1 + 0x814);
  }
  uVar5 = 0;
  uVar3 = *(undefined4 *)(param_1 + 0x528);
  *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0x524);
  *(undefined4 *)(param_2 + 0x24) = uVar3;
  *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x52c);
  if (*(short *)(param_1 + 1000) == 0x50f) {
    uVar5 = 7;
  }
  zz_01deb68_(param_1,uVar5,param_2 + 0x2c,param_2 + 0x38,param_1 + 0x6f7);
  return;
}



// ==== 800b946c  zz_00b946c_ ====

void zz_00b946c_(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  float *pfVar4;
  float local_98;
  float local_94;
  float local_90;
  float afStack_8c [12];
  float afStack_5c [3];
  float local_50;
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_28;
  uint uStack_24;
  
  if ('\0' < *(char *)(param_1 + 0x542)) {
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    pfVar4 = (float *)&DAT_802ff3ac;
    if (*(short *)(param_1 + 1000) == 0x50f) {
      pfVar4 = (float *)&DAT_802ff3b8;
    }
    local_98 = *pfVar4;
    local_94 = pfVar4[1];
    local_90 = pfVar4[2];
    if (*(char *)(param_1 + 0x6e8) == '\0') {
      local_98 = -local_98;
    }
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xb14),&local_98,(float *)(param_2 + 0x2c));
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x2c),&local_98);
    local_94 = FLOAT_804384a4;
    gnt4_PSMTXIdentity_bl(afStack_8c);
    zz_0045ef4_(afStack_8c,5,&local_98,&DAT_802b0cb4);
    local_98 = *(float *)(param_2 + 0x2c);
    local_28 = 0x43300000;
    local_94 = *(float *)(param_2 + 0x24);
    local_90 = *(float *)(param_2 + 0x34);
    uStack_24 = (int)*(short *)(param_1 + 0x548) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_804384e0 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_804384a8)),
                        afStack_5c,0x78);
    gnt4_PSMTXConcat_bl(afStack_8c,afStack_5c,afStack_5c);
    local_50 = local_98;
    local_40 = local_94;
    local_30 = local_90;
    local_98 = FLOAT_804384a4;
    local_94 = FLOAT_804384a4;
    local_90 = *(float *)(param_2 + 0x44);
    gnt4_PSMTXMultVec_bl(afStack_5c,&local_98,(float *)(param_2 + 0x38));
    fVar2 = FLOAT_804384a4;
    if (*(short *)(param_1 + 0x54c) < 1) {
      *(short *)(param_1 + 0x548) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x54a) ^ 0x80000000) -
                               DOUBLE_804384a8) * *(float *)(param_1 + 0x1dc8) +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x548) ^ 0x80000000) -
                              DOUBLE_804384a8));
      fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar1;
      if (fVar1 <= fVar2) {
        *(undefined1 *)(param_1 + 0x542) = 0xff;
      }
    }
    else {
      *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + -1;
      uVar3 = *(undefined4 *)(param_1 + 0x528);
      *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0x524);
      *(undefined4 *)(param_2 + 0x24) = uVar3;
      *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x52c);
    }
  }
  return;
}



// ==== 800b9688  FUN_800b9688 ====

void FUN_800b9688(int param_1)

{
  (*(code *)(&PTR_FUN_802ff3c4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b96c4  FUN_800b96c4 ====

void FUN_800b96c4(int param_1)

{
  (*(code *)(&PTR_FUN_802ff3d8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b9700  FUN_800b9700 ====

void FUN_800b9700(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar3 = FLOAT_804384e4;
  fVar2 = FLOAT_804384a4;
  dVar4 = (double)FLOAT_804384c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0x78;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b9790  FUN_800b9790 ====

void FUN_800b9790(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_00b9c68_(param_1);
  zz_0066e40_(param_1,0);
  fVar3 = FLOAT_804384a4;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_804384c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800b9820  FUN_800b9820 ====

void FUN_800b9820(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
  }
  return;
}



// ==== 800b9888  FUN_800b9888 ====

void FUN_800b9888(int param_1)

{
  (*(code *)(&PTR_FUN_802ff3e4)[*(char *)(param_1 + 0x540)])();
  zz_006ed8c_((double)FLOAT_804384c4,param_1);
  zz_0067458_((double)FLOAT_804384bc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b98f4  FUN_800b98f4 ====

void FUN_800b98f4(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_804384e4;
  dVar3 = (double)FLOAT_804384c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0x78;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b9964  FUN_800b9964 ====

void FUN_800b9964(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_00b9c68_(param_1);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  fVar3 = FLOAT_804384a4;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_804384c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800b9a0c  FUN_800b9a0c ====

void FUN_800b9a0c(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
  }
  return;
}



// ==== 800b9a74  FUN_800b9a74 ====

void FUN_800b9a74(int param_1)

{
  (*(code *)(&PTR_FUN_802ff3f0)[*(char *)(param_1 + 0x540)])();
  FUN_80067310((double)FLOAT_804384bc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b9ad4  FUN_800b9ad4 ====

void FUN_800b9ad4(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_804384e4;
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = (double)FLOAT_804384c8;
    *(float *)(param_1 + 0x558) = fVar2;
    *(undefined2 *)(param_1 + 0x54e) = 0x78;
    *(undefined1 *)(param_1 + 0x6ea) = 4;
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    zz_006a3d0_(param_1,'\x02',3,0);
  }
  return;
}



// ==== 800b9b64  FUN_800b9b64 ====

void FUN_800b9b64(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_00b9c68_(param_1);
  zz_0066e40_(param_1,2);
  fVar3 = FLOAT_804384a4;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_804384c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800b9bfc  FUN_800b9bfc ====

void FUN_800b9bfc(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,0x10);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
  }
  return;
}



// ==== 800b9c68  zz_00b9c68_ ====

void zz_00b9c68_(int param_1)

{
  double dVar1;
  uint uVar2;
  
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_804384a8;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar2;
    *(float *)(param_1 + 0x558) =
         *(float *)(param_1 + 0x558) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar1);
  }
  *(undefined1 *)(param_1 + 0x6f7) = 4;
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    zz_0098dbc_(param_1,0,6);
  }
  zz_0066ac0_(param_1,0);
  return;
}



// ==== 800b9d2c  FUN_800b9d2c ====

void FUN_800b9d2c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined1 uVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  
  switch(*(undefined2 *)(param_9 + 1000)) {
  default:
    iVar5 = 0;
    uVar1 = 0;
    break;
  case 0x506:
    iVar5 = 4;
    uVar1 = 0;
    break;
  case 0x508:
    iVar5 = 0;
    uVar1 = 1;
    break;
  case 0x50f:
    iVar5 = 8;
    uVar1 = 0;
    break;
  case 0x512:
    iVar5 = 0xc;
    uVar1 = 0;
    break;
  case 0x514:
    iVar5 = 8;
    uVar1 = 1;
  }
  pbVar3 = (byte *)(param_9 + 0x18c);
  iVar4 = 0;
  iVar6 = 4;
  do {
    uVar2 = (uint)(char)*pbVar3;
    if ((uVar2 & 1 << iVar4) != 0) {
      uVar2 = iVar5 + iVar4;
      zz_0184588_(param_9,uVar1,uVar2,pbVar3);
      break;
    }
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,uVar2,pbVar3
              ,iVar4,iVar5,in_r9,in_r10);
  *(float *)(param_9 + 0x694) = FLOAT_804384cc + *(float *)(param_9 + 0x1dc8);
  return;
}



// ==== 800b9e30  zz_00b9e30_ ====

void zz_00b9e30_(int param_1,short *param_2)

{
  *(undefined1 *)(param_2 + 0x16) = 0;
  *(undefined1 *)(param_1 + 0x6e9) = 1;
  zz_00b9e60_(param_1,param_2);
  return;
}



// ==== 800b9e60  zz_00b9e60_ ====

void zz_00b9e60_(int param_1,short *param_2)

{
  short *psVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  short *psVar10;
  short *psVar11;
  short *psVar12;
  
  cVar6 = *(char *)(param_1 + 0x6e9);
  if (cVar6 == '\0') {
    cVar6 = *(char *)(param_2 + 0x16);
  }
  if ((int)cVar6 == (int)*(char *)(param_2 + 0x16)) {
    psVar11 = param_2 + 6;
    psVar12 = param_2 + 0xc;
    iVar7 = 2;
    psVar10 = param_2;
    do {
      sVar4 = *psVar12;
      sVar9 = *psVar11 - *psVar10;
      if ((int)sVar4 < (int)(short)(*psVar11 - *psVar10)) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      *psVar10 = *psVar10 + sVar9;
      sVar4 = psVar12[1];
      sVar9 = psVar11[1] - psVar10[1];
      if ((int)sVar4 < (int)(short)(psVar11[1] - psVar10[1])) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      psVar10[1] = psVar10[1] + sVar9;
      psVar1 = psVar11 + 2;
      psVar11 = psVar11 + 3;
      sVar4 = psVar12[2];
      psVar12 = psVar12 + 3;
      sVar9 = *psVar1 - psVar10[2];
      if ((int)sVar4 < (int)(short)(*psVar1 - psVar10[2])) {
        sVar9 = sVar4;
      }
      iVar8 = -(int)sVar4;
      if (sVar9 < iVar8) {
        sVar9 = (short)iVar8;
      }
      psVar10[2] = psVar10[2] + sVar9;
      psVar10 = psVar10 + 3;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  else {
    iVar7 = (cVar6 + -1) * 0x18;
    *(undefined4 *)(param_2 + 6) = *(undefined4 *)(&DAT_803002d8 + iVar7);
    param_2[8] = *(short *)(&DAT_803002dc + iVar7);
    *(undefined4 *)(param_2 + 9) = *(undefined4 *)(&DAT_803002de + iVar7);
    param_2[0xb] = *(short *)(&DAT_803002e2 + iVar7);
    *(undefined4 *)(param_2 + 0xc) = *(undefined4 *)(&DAT_803002e4 + iVar7);
    param_2[0xe] = *(short *)(&DAT_803002e8 + iVar7);
    *(undefined4 *)(param_2 + 0xf) = *(undefined4 *)(&DAT_803002ea + iVar7);
    param_2[0x11] = *(short *)(&DAT_803002ee + iVar7);
  }
  iVar7 = (cVar6 + -1) * 0x10;
  fVar2 = *(float *)(&DAT_80300324 + iVar7);
  fVar5 = *(float *)(&DAT_80300320 + iVar7) - *(float *)(param_2 + 0x12);
  if (fVar2 < *(float *)(&DAT_80300320 + iVar7) - *(float *)(param_2 + 0x12)) {
    fVar5 = fVar2;
  }
  if (fVar5 < -fVar2) {
    fVar5 = -fVar2;
  }
  *(float *)(param_2 + 0x12) = *(float *)(param_2 + 0x12) + fVar5;
  fVar2 = *(float *)(&DAT_8030032c + iVar7);
  fVar5 = *(float *)(&DAT_80300328 + iVar7) - *(float *)(param_2 + 0x14);
  if (fVar2 < *(float *)(&DAT_80300328 + iVar7) - *(float *)(param_2 + 0x14)) {
    fVar5 = fVar2;
  }
  if (fVar5 < -fVar2) {
    fVar5 = -fVar2;
  }
  *(float *)(param_2 + 0x14) = *(float *)(param_2 + 0x14) + fVar5;
  *(char *)(param_2 + 0x16) = cVar6;
  *(undefined4 *)(param_1 + 0x194c) = *(undefined4 *)param_2;
  *(short *)(param_1 + 0x1950) = param_2[2];
  *(short *)(param_1 + 0x1952) = *param_2;
  *(short *)(param_1 + 0x1954) = -param_2[1];
  *(short *)(param_1 + 0x1956) = -param_2[2];
  if (*(char *)(param_2 + 0x16) == '\x02') {
    *(undefined2 *)(param_1 + 0x194e) =
         *(undefined2 *)(&DAT_80433ad0 + (*(uint *)(PTR_DAT_80433934 + 0xb0) & 3) * 2);
    *(short *)(param_1 + 0x1954) = -*(short *)(param_1 + 0x194e);
    zz_00f0104_(param_1,0x11,6);
  }
  uVar3 = *(undefined4 *)(param_2 + 0x12);
  *(undefined4 *)(param_1 + 0x16d0) = uVar3;
  *(undefined4 *)(param_1 + 0x16c4) = uVar3;
  uVar3 = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(param_1 + 0x16d4) = uVar3;
  *(undefined4 *)(param_1 + 0x16c8) = uVar3;
  *(undefined4 *)(param_1 + 0x1958) = *(undefined4 *)(param_2 + 3);
  *(short *)(param_1 + 0x195c) = param_2[5];
  *(short *)(param_1 + 0x195e) = param_2[3];
  *(short *)(param_1 + 0x1960) = -param_2[4];
  *(short *)(param_1 + 0x1962) = -param_2[5];
  return;
}



// ==== 800ba240  FUN_800ba240 ====

void FUN_800ba240(int param_1)

{
  zz_00cbe9c_(param_1);
  zz_00b9e30_(param_1,(short *)(param_1 + 0x144));
  *(undefined1 *)(param_1 + 0x172) = 0;
  return;
}



// ==== 800ba2c4  FUN_800ba2c4 ====

void FUN_800ba2c4(int param_1)

{
  zz_00b9e60_(param_1,(short *)(param_1 + 0x144));
  if ((*(char *)(param_1 + 0x493) != '\0') && (FLOAT_804384e8 < *(float *)(param_1 + 0x12e4))) {
    *(float *)(param_1 + 0x12e4) = FLOAT_804384e8;
  }
  return;
}



// ==== 800ba324  FUN_800ba324 ====

void FUN_800ba324(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80300390)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800ba364  FUN_800ba364 ====

void FUN_800ba364(int param_1,int param_2)

{
  zz_0099e70_(param_1,(&DAT_80433ad8)[param_2]);
  return;
}



// ==== 800ba390  FUN_800ba390 ====

void FUN_800ba390(int param_1)

{
  zz_0137540_(param_1,0);
  return;
}



