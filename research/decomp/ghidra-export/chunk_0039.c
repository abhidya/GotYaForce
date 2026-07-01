// ==== 8014d57c  FUN_8014d57c ====

void FUN_8014d57c(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 8014d5b4  FUN_8014d5b4 ====

void FUN_8014d5b4(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf3b8,3,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf328,3,pfVar2 + 0xc,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf298,2,pfVar2 + 0x15,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf238,1,pfVar2 + 0x1b,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf208,1,pfVar2 + 0x1e,afStack_18);
    zz_00e5184_(param_1,-0x7fcbf3b8,3,pfVar2 + 3,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcbf328,3,pfVar2 + 0xc,pfVar2 + 0x48);
    zz_00e5184_(param_1,-0x7fcbf298,2,pfVar2 + 0x15,pfVar2 + 0x51);
    zz_00e5184_(param_1,-0x7fcbf238,1,pfVar2 + 0x1b,pfVar2 + 0x57);
    zz_00e5184_(param_1,-0x7fcbf208,1,pfVar2 + 0x1e,pfVar2 + 0x5a);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 8014d734  FUN_8014d734 ====

void FUN_8014d734(int param_1)

{
  FUN_8014d2fc(param_1);
  FUN_801eea8c(param_1);
  return;
}



// ==== 8014d784  FUN_8014d784 ====

void FUN_8014d784(int param_1)

{
  FUN_8014d3fc(param_1);
  return;
}



// ==== 8014d7b8  FUN_8014d7b8 ====

void FUN_8014d7b8(int param_1)

{
  FUN_8014d57c(param_1);
  return;
}



// ==== 8014d7d8  FUN_8014d7d8 ====

void FUN_8014d7d8(int param_1)

{
  FUN_8014d5b4(param_1);
  return;
}



// ==== 8014d7f8  FUN_8014d7f8 ====

void FUN_8014d7f8(int param_1)

{
  (*(code *)(&PTR_FUN_80340e28)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8014d834  FUN_8014d834 ====

void FUN_8014d834(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  (*(code *)(&PTR_FUN_80340e34)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8014d878  FUN_8014d878 ====

void FUN_8014d878(int param_1)

{
  *(short *)(param_1 + 0x1dfc) =
       (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000) -
                    DOUBLE_8043a460) * DOUBLE_8043a458);
  (*(code *)(&PTR_FUN_80340e48)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014d8ec  FUN_8014d8ec ====

void FUN_8014d8ec(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a46c;
  fVar1 = FLOAT_8043a468;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006d0dc_(param_1,0xc1,0);
  return;
}



// ==== 8014d934  FUN_8014d934 ====

void FUN_8014d934(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_8043a46c < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar2 = (double)FLOAT_8043a470;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 8014d9c0  FUN_8014d9c0 ====

void FUN_8014d9c0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_0082824_(param_1,0x65);
    }
  }
  return;
}



// ==== 8014da3c  FUN_8014da3c ====

void FUN_8014da3c(int param_1)

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



// ==== 8014da90  FUN_8014da90 ====

void FUN_8014da90(int param_1)

{
  (*(code *)(&PTR_FUN_80340e58)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014dacc  FUN_8014dacc ====

void FUN_8014dacc(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a474;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_8043a470,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 8014db30  FUN_8014db30 ====

void FUN_8014db30(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_8043a46c;
  if (iVar3 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      iVar3 = zz_006dbe0_(param_1,0,1,1);
      if (iVar3 != 0) {
        zz_0082824_(param_1,0x65);
      }
    }
  }
  return;
}



// ==== 8014dc14  FUN_8014dc14 ====

void FUN_8014dc14(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar2 = DOUBLE_8043a460;
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    dVar3 = (double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1dfc) ^ 0x80000000) -
            DOUBLE_8043a460;
    iVar1 = (int)(dVar3 * DOUBLE_8043a458);
    *(short *)(param_9 + 0x1dfc) = (short)iVar1;
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,iVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8014dca8  FUN_8014dca8 ====

void FUN_8014dca8(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_80340e64)[*(char *)(param_1 + 0x540)])(param_1);
  FUN_8014df28(param_1);
  return;
}



// ==== 8014dd08  FUN_8014dd08 ====

void FUN_8014dd08(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043a46c;
  fVar1 = FLOAT_8043a468;
  dVar3 = (double)FLOAT_8043a470;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar2;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  zz_004beb8_(dVar3,param_1,0xf,2,4,0xffffffff,0xffffffff);
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_006d0dc_(param_1,0xc1,0);
  }
  else {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8014dda0  FUN_8014dda0 ====

void FUN_8014dda0(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x542) == '\0') {
    iVar1 = zz_006d0dc_(param_1,0xc1,0);
    if ((iVar1 != 1) && (FLOAT_8043a46c < *(float *)(param_1 + 0x558))) {
      return;
    }
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8014de58  FUN_8014de58 ====

void FUN_8014de58(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_0082824_(param_1,0x65);
    }
  }
  return;
}



// ==== 8014ded4  FUN_8014ded4 ====

void FUN_8014ded4(int param_1)

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



// ==== 8014df28  FUN_8014df28 ====

void FUN_8014df28(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a478;
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a478;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x540)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8014dfb0  FUN_8014dfb0 ====

void FUN_8014dfb0(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340e74)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014e000  FUN_8014e000 ====

void FUN_8014e000(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043a480;
  fVar1 = FLOAT_8043a46c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8014e0a8  FUN_8014e0a8 ====

void FUN_8014e0a8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_8043a470;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,7,0xffffffff,0xffffffff);
  }
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_8043a484;
    fVar1 = FLOAT_8043a46c;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  return;
}



// ==== 8014e178  FUN_8014e178 ====

void FUN_8014e178(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_0082824_(param_1,0x65);
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
    fVar1 = FLOAT_8043a484;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  }
  return;
}



// ==== 8014e258  FUN_8014e258 ====

void FUN_8014e258(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
    fVar1 = FLOAT_8043a484;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      return;
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8014e344  FUN_8014e344 ====

void FUN_8014e344(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_80340e84)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 8014e39c  FUN_8014e39c ====

void FUN_8014e39c(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043a474;
  dVar2 = (double)FLOAT_8043a470;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 8014e3e8  FUN_8014e3e8 ====

void FUN_8014e3e8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_8043a46c;
  if (*(char *)(param_1 + 0x543) < '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((*(char *)(param_1 + 0x543) < '\x01') &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
      iVar3 = zz_006dbe0_(param_1,0,1,1);
      if (iVar3 != 0) {
        zz_0082824_(param_1,0x65);
      }
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  return;
}



// ==== 8014e4d4  FUN_8014e4d4 ====

void FUN_8014e4d4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_9,1);
  if (iVar1 == 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8014e52c  FUN_8014e52c ====

void FUN_8014e52c(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  (*(code *)(&PTR_FUN_80340e90)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8014e570  FUN_8014e570 ====

void FUN_8014e570(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340ea8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014e5c0  FUN_8014e5c0 ====

void FUN_8014e5c0(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043a480;
  fVar1 = FLOAT_8043a46c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a46c;
  return;
}



// ==== 8014e67c  FUN_8014e67c ====

void FUN_8014e67c(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    fVar1 = FLOAT_8043a468;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043a488 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043a488 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043a48c;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8014e794  FUN_8014e794 ====

void FUN_8014e794(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x03') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_8014e7cc;
  }
  zz_004cd24_(param_1,0xf);
LAB_8014e7cc:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a490;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar4 = FUN_80066838((double)FLOAT_8043a48c,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043a498;
    fVar1 = FLOAT_8043a494;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 8014e894  FUN_8014e894 ====

void FUN_8014e894(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  if (iVar2 == 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  else {
    if (*(char *)(param_1 + 0x542) == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x03') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x03' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_8043a49c;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_8043a468;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_8043a4a0;
          }
          dVar3 = (double)FLOAT_8043a470;
          *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
          zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
        }
        else {
          *(undefined1 *)(param_1 + 0x542) = 99;
        }
      }
    }
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 8014ea3c  FUN_8014ea3c ====

void FUN_8014ea3c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x1cef) == '\x02') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a470;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar2 = FLOAT_8043a46c;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if ((*(float *)(param_1 + 0x558) <= fVar2) ||
         (uVar4 = FUN_80066838((double)FLOAT_8043a48c,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_8043a4a4;
        fVar2 = FLOAT_8043a498;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043a46c,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a4a8;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  else if ((cVar1 < '\x04') && (iVar5 = zz_004cd24_(param_1,0xf), iVar5 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    return;
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  if (iVar5 != 0) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8014ebf8  FUN_8014ebf8 ====

void FUN_8014ebf8(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8014ec30  FUN_8014ec30 ====

void FUN_8014ec30(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340ec0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014ec80  FUN_8014ec80 ====

void FUN_8014ec80(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar1 = FLOAT_8043a4ac;
  *(float *)(param_1 + 0x558) = FLOAT_8043a480;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a46c;
  return;
}



// ==== 8014ed60  FUN_8014ed60 ====

void FUN_8014ed60(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a4b0;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a4b0;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043a46c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043a468;
    *(float *)(param_1 + 0x558) = FLOAT_8043a468;
    fVar3 = FLOAT_8043a48c;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 8014eea4  FUN_8014eea4 ====

void FUN_8014eea4(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_8043a46c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar3 = FUN_80066838((double)FLOAT_8043a48c,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_8043a470;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8014ef88  FUN_8014ef88 ====

void FUN_8014ef88(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043a47c < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043a4b4,param_1);
  if (0 < (int)uVar6) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x541) == '\0') {
    uVar2 = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
    zz_006660c_(param_1);
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_800669d0(param_1,0x40);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
    *(undefined2 *)(param_1 + 0x72) = uVar2;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043a46c;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar5 = zz_004cd24_(param_1,0xf);
        if (iVar5 != 1) {
          return;
        }
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8014f128;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043a4b8;
      fVar3 = FLOAT_8043a498;
      if (*(char *)(param_1 + 0x1cef) != '\x02') {
        return;
      }
      if (*(char *)(param_1 + 0x1cf0) != '\x01') {
        return;
      }
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0;
      *(undefined2 *)(param_1 + 0x54a) = 0x1500;
      *(float *)(param_1 + 0x558) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar3 < *(float *)(param_1 + 0x558)) {
      zz_0067754_(param_1,(short *)(param_1 + 0x72),*(short *)(param_1 + 0x54a));
      return;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  zz_0066ed8_(param_1,*(ushort *)(param_1 + 0x5ae),*(undefined2 *)(param_1 + 0x54a));
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_8014f128:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 8014f188  FUN_8014f188 ====

void FUN_8014f188(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8014f1c0  FUN_8014f1c0 ====

void FUN_8014f1c0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340ed4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014f210  FUN_8014f210 ====

void FUN_8014f210(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043a470;
  *(float *)(param_1 + 0x558) = FLOAT_8043a480;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 8014f2cc  FUN_8014f2cc ====

void FUN_8014f2cc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_8043a46c < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8014f34c;
  }
  fVar2 = FLOAT_8043a4b4;
  fVar1 = FLOAT_8043a468;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8014f34c:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8014f38c  FUN_8014f38c ====

/* WARNING: Removing unreachable block (ram,0x8014f5bc) */
/* WARNING: Removing unreachable block (ram,0x8014f39c) */

void FUN_8014f38c(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a46c;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a488 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a468
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a468 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a46c;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a4bc;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a4c0;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043a4bc);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043a480,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_8043a458 * (double)*(float *)(param_1 + 0x44)) goto LAB_8014f5b0;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_8043a46c;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8014f5b0:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8014f5d8  FUN_8014f5d8 ====

void FUN_8014f5d8(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a46c;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a46c) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a46c;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a468 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8014f67c  FUN_8014f67c ====

void FUN_8014f67c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340ee4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014f6cc  FUN_8014f6cc ====

void FUN_8014f6cc(int param_1)

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
  dVar2 = (double)FLOAT_8043a470;
  *(float *)(param_1 + 0x558) = FLOAT_8043a480;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8014f788  FUN_8014f788 ====

void FUN_8014f788(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_8043a46c < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8014f808;
  }
  fVar2 = FLOAT_8043a4b4;
  fVar1 = FLOAT_8043a468;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8014f808:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8014f848  FUN_8014f848 ====

/* WARNING: Removing unreachable block (ram,0x8014fa78) */
/* WARNING: Removing unreachable block (ram,0x8014f858) */

void FUN_8014f848(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a46c;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a4c4 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a468
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a468 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a46c;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a4bc;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a4c0;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043a4bc);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043a480,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_8043a458 * (double)*(float *)(param_1 + 0x44)) goto LAB_8014fa6c;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_8043a46c;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8014fa6c:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8014fa94  FUN_8014fa94 ====

void FUN_8014fa94(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a47c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a46c;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a46c) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a46c;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a468 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8014fb38  FUN_8014fb38 ====

void FUN_8014fb38(int param_1)

{
  (*(code *)(&PTR_FUN_804346c0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8014fb70  FUN_8014fb70 ====

void FUN_8014fb70(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80340ef4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8014fbc0  FUN_8014fbc0 ====

void FUN_8014fbc0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043a490;
  fVar1 = FLOAT_8043a46c;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a46c;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a490;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  fVar1 = FLOAT_8043a46c;
  dVar4 = (double)FLOAT_8043a47c;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_8043a490;
  *(float *)(param_1 + 0x50) = fVar1;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,4,0,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,4,2,0xffffffff,0xffffffff);
  }
  *(undefined1 *)(param_1 + 0x154) = 1;
  iVar3 = zz_006dbe0_(param_1,2,1,0);
  if (iVar3 != 0) {
    *(undefined1 *)(param_1 + 0x6f7) = 1;
  }
  return;
}



// ==== 8014fd18  FUN_8014fd18 ====

void FUN_8014fd18(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x154) == '\x01') && (iVar2 = zz_006dbe0_(param_1,2,1,0), iVar2 != 0)) {
    *(undefined1 *)(param_1 + 0x6f7) = 1;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x03')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
  }
  else if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 == 1) {
      FUN_80150018(param_1,0);
    }
    *(undefined1 *)(param_1 + 0x154) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 0;
  }
  zz_006d144_(param_1,0xc1);
  if (*(char *)(param_1 + 0x542) == '\x01') {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar1 = FLOAT_8043a490;
  dVar3 = (double)FLOAT_8043a47c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a490;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,4,1,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_8043a470,param_1,0xf,4,3,0xffffffff,0xffffffff);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  return;
}



// ==== 8014fedc  FUN_8014fedc ====

void FUN_8014fedc(int param_1)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a490;
  dVar4 = (double)FLOAT_8043a47c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a460) * FLOAT_8043a4c8);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  bVar1 = false;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      bVar1 = true;
    }
  }
  else {
    iVar3 = zz_00677b0_(param_1);
    if ((iVar3 != 0) || (*(char *)(param_1 + 0x1cee) != '\0')) {
      bVar1 = true;
    }
  }
  fVar2 = FLOAT_8043a46c;
  if (bVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x18da) = 0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_8043a480 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 80150018  FUN_80150018 ====

void FUN_80150018(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x3b;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80150120;
    *(code **)(puVar1 + 0x10c) = FUN_8015068c;
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



// ==== 80150120  FUN_80150120 ====

void FUN_80150120(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_80340f2c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80150170  FUN_80150170 ====

void FUN_80150170(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  char *pcVar6;
  longlong lVar7;
  undefined8 uVar8;
  
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x2c;
  pcVar6 = &DAT_80340f00 + iVar4;
  iVar2 = -((int)*(short *)(&DAT_80340f02 + iVar4) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80340f02 + iVar4));
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
    iVar2 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + *pcVar6 * 0x30 + 0x8d4),(float *)(iVar4 + -0x7fcbf0f8),
               (float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar2 + *pcVar6 * 0x30 + (char)(&DAT_80340f01)[iVar4] * 4 + 0x8d4);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar2 + *pcVar6 * 0x30 + (char)(&DAT_80340f01)[iVar4] * 4 + 0x8e4);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar2 + *pcVar6 * 0x30 + (char)(&DAT_80340f01)[iVar4] * 4 + 0x8f4);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80340f20 + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80340f20 + iVar4);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80340f14 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80340f16 + iVar4);
    *(char *)(param_9 + 0x12) = (char)*(undefined2 *)(&DAT_80340f04 + iVar4);
    *(undefined4 *)(param_9 + 0x48) = *(undefined4 *)(&DAT_80340f24 + iVar4);
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    *(code **)(param_9 + 0x100) = FUN_80150568;
    uVar5 = 1;
    lVar7 = zz_0089100_(param_9,1,1);
    uVar8 = FUN_801506f4(lVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         extraout_r4,uVar5,param_12,param_13,param_14,param_15,param_16);
    if (-1 < *(short *)(&DAT_80340f06 + iVar4)) {
      FUN_80150568(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      zz_00aedc0_(iVar2,(float *)(param_9 + 0x114),(int)*(short *)(&DAT_80340f06 + iVar4),
                  *(undefined1 *)(param_9 + 0x12));
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00f036c_(param_9,0xef);
  }
  return;
}



// ==== 8015039c  FUN_8015039c ====

void FUN_8015039c(int param_1)

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
      fVar1 = *(float *)(param_1 + 0x44) + *(float *)(&DAT_80340f28 + iVar2);
      *(float *)(param_1 + 0x44) = fVar1;
      if (*(float *)(param_1 + 0x48) < fVar1) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x48);
      }
    }
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    FUN_80083874((double)*(float *)(&DAT_80340f1c + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_80340f18 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_80340f16 + iVar2));
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
  FUN_801508cc(param_1);
  return;
}



// ==== 801504e4  FUN_801504e4 ====

void FUN_801504e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80150520  FUN_80150520 ====

void FUN_80150520(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80150568  FUN_80150568 ====

void FUN_80150568(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
      local_50 = FLOAT_8043a4d0;
      local_54 = FLOAT_8043a4d0;
      local_58 = FLOAT_8043a4d0;
      uVar9 = zz_00456a0_(afStack_4c,afStack_4c,pfVar3);
    }
    zz_00076d0_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe0)
                ,afStack_4c,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    iVar8 = iVar8 + 8;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 8015068c  FUN_8015068c ====

void FUN_8015068c(int param_1)

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



// ==== 801506f4  FUN_801506f4 ====

/* WARNING: Removing unreachable block (ram,0x801508b0) */
/* WARNING: Removing unreachable block (ram,0x801508a8) */
/* WARNING: Removing unreachable block (ram,0x8015070c) */
/* WARNING: Removing unreachable block (ram,0x80150704) */

void FUN_801506f4(longlong param_1,double param_2,double param_3,double param_4,double param_5,
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
  short *psVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  double local_58;
  
  uVar2 = zz_00055fc_();
  uVar3 = zz_00055fc_();
  iVar13 = 0;
  iVar12 = 0;
  iVar11 = 1;
  psVar10 = (short *)&DAT_804346c8;
  iVar9 = param_9;
  dVar17 = DOUBLE_8043a4e8;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    puVar7 = (undefined2 *)(*(int *)(param_9 + 0x54) + iVar13);
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
      dVar16 = (double)((float)((double)CONCAT44(0x43300000,uVar4 & 0xff) - DOUBLE_8043a4e0) /
                       FLOAT_8043a4d4);
      uVar4 = zz_00055fc_();
      *puVar7 = (short)(uVar4 << 8);
      uVar4 = zz_00055fc_();
      dVar14 = (double)FLOAT_8043a4dc;
      param_2 = (double)FLOAT_8043a4d8;
      puVar7[1] = (short)(uVar4 << 8);
      param_1 = (longlong)(int)(param_2 * dVar16);
      puVar7[2] = (short)(int)(param_2 * dVar16);
      puVar7[3] = (short)(int)(param_2 * (double)(float)(dVar14 - dVar16));
      if ((uVar3 & 1 << iVar12) != 0) {
        puVar7[2] = -puVar7[2];
      }
      if ((uVar3 & 1 << iVar11) != 0) {
        puVar7[3] = -puVar7[3];
      }
    }
    iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
    pfVar6 = (float *)(int)*psVar10;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                *(int *)(iVar9 + 0xe0),(int)pfVar6,param_12,param_13,param_14,param_15,param_16);
    iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
    local_58 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12)) ^ 0x80000000);
    uVar15 = zz_00086b8_((double)(float)(local_58 - dVar17),param_2,param_3,param_4,param_5,param_6,
                         param_7,param_8,iVar5,*(int *)(iVar9 + 0xe0),pfVar6,param_12,param_13,
                         param_14,param_15,param_16);
    param_1 = zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar9 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,
                          param_15,param_16);
    iVar13 = iVar13 + 8;
    iVar12 = iVar12 + 2;
    iVar11 = iVar11 + 2;
    psVar10 = psVar10 + 1;
    iVar9 = iVar9 + 4;
  }
  return;
}



// ==== 801508cc  FUN_801508cc ====

void FUN_801508cc(int param_1)

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



// ==== 8015091c  zz_015091c_ ====

bool zz_015091c_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    *(code **)(puVar1 + 0xc) = FUN_80150a18;
    *(code **)(puVar1 + 0x10c) = FUN_80150bc8;
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



// ==== 80150a18  FUN_80150a18 ====

void FUN_80150a18(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80340f58)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80150a6c  FUN_80150a6c ====

void FUN_80150a6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043a4f0;
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80340f48 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80340f44 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80340f4c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80340f50 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80340f54 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80340f42 + iVar3);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80340f40 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80340f40 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a4f4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0150b98_();
  return;
}



// ==== 80150b98  zz_0150b98_ ====

void zz_0150b98_(void)

{
  return;
}



// ==== 80150ba8  FUN_80150ba8 ====

void FUN_80150ba8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80150bc8  FUN_80150bc8 ====

void FUN_80150bc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80150c48  zz_0150c48_ ====

undefined1 * zz_0150c48_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  puVar2 = (undefined1 *)0x0;
  if (((((sVar1 == 0x603) || (sVar1 == 0x60b)) || (sVar1 == 0x60d)) || (sVar1 == 0x60f)) &&
     (puVar2 = zz_0088aa0_(param_1,3,0,0,4), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x13] = 4;
    *(code **)(puVar2 + 0xc) = FUN_80150d74;
    *(code **)(puVar2 + 0x10c) = FUN_8015131c;
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
    *(undefined4 *)(puVar2 + 0x54) = 0;
  }
  return puVar2;
}



// ==== 80150d74  FUN_80150d74 ====

void FUN_80150d74(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80341028)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80150dc8  FUN_80150dc8 ====

void FUN_80150dc8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  char cVar5;
  int *piVar3;
  int iVar4;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  
  cVar5 = zz_008b290_();
  if (cVar5 == '\0') {
    iVar7 = *(int *)(param_9 + 0x90);
    piVar3 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x24);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
    iVar4 = 0;
    if ((int)(-*(uint *)(param_9 + 0x54) | *(uint *)(param_9 + 0x54)) < 0) {
      iVar4 = zz_008ac80_(param_9,*(int *)(&DAT_80340f68 + *(char *)(param_9 + 0x11) * 4));
    }
    if (iVar4 == 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 1;
      fVar1 = FLOAT_8043a4f8;
      dVar9 = (double)FLOAT_8043a4f8;
      *(undefined1 *)(param_9 + 0x19) = 0;
      fVar2 = FLOAT_8043a4fc;
      *(undefined1 *)(param_9 + 0x84) = 0xff;
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(*(int *)(param_9 + 0x90) + 0xb4);
      *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(*(int *)(param_9 + 0x90) + 0xc0);
      *(float *)(param_9 + 0x58) = fVar1;
      *(float *)(param_9 + 0x5c) = fVar2;
      *(float *)(param_9 + 0x60) = fVar1;
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                          (float *)(param_9 + 0x58));
      *(code **)(param_9 + 0x100) = FUN_801511ec;
      uVar6 = 1;
      uVar8 = zz_0089100_(param_9,1,1);
      fVar1 = FLOAT_8043a4f8;
      *(float *)(param_9 + 100) = FLOAT_8043a4f8;
      *(float *)(param_9 + 0x68) = fVar1;
      *(float *)(param_9 + 0x6c) = fVar1;
      *(undefined2 *)(param_9 + 0x1e) = 0;
      uVar8 = zz_01513a0_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                          uVar6,param_12,param_13,param_14,param_15,param_16);
      zz_01513a0_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,uVar6,
                  param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 0x144) = 0x78;
      *(undefined2 *)(param_9 + 0x148) = *(undefined2 *)(iVar7 + 0x5b2);
      *(undefined2 *)(param_9 + 0x1c4) = 0x19;
      *(undefined2 *)(param_9 + 0x1c8) = 0x19;
      *(undefined2 *)(param_9 + 0x1c6) = 0x19;
      *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
    }
  }
  return;
}



// ==== 80150f48  FUN_80150f48 ====

void FUN_80150f48(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  byte bVar6;
  double dVar7;
  double dVar8;
  
  cVar2 = *(char *)(param_9 + 0x19);
  if (cVar2 == '\x01') {
    iVar5 = zz_0151668_(param_9);
    if (iVar5 != 0) goto LAB_8015110c;
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
  else if (cVar2 < '\x01') {
    if (cVar2 < '\0') goto LAB_8015110c;
    iVar5 = *(int *)(param_9 + 0x144) + -1;
    *(int *)(param_9 + 0x144) = iVar5;
    fVar3 = FLOAT_8043a504;
    fVar1 = FLOAT_8043a500;
    if (0 < iVar5) {
      *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + FLOAT_8043a4fc;
      iVar5 = (int)-(fVar1 * ((*(float *)(param_9 + 0xd4) - fVar3) / fVar3) - fVar1);
      if (iVar5 < 0x100) {
        bVar6 = (byte)iVar5 & ~(byte)(iVar5 >> 0x1f);
      }
      else {
        bVar6 = 0xff;
      }
      *(byte *)(param_9 + 0x84) = bVar6;
      fVar4 = FLOAT_8043a4fc;
      fVar1 = *(float *)(param_9 + 0xd4) / FLOAT_8043a504;
      fVar3 = FLOAT_8043a4fc;
      if ((fVar1 <= FLOAT_8043a4fc) && (fVar3 = fVar1, fVar1 < FLOAT_8043a4f8)) {
        fVar3 = FLOAT_8043a4f8;
      }
      *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(*(int *)(param_9 + 0x90) + 0xb4);
      iVar5 = *(int *)(param_9 + 0x90);
      *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(iVar5 + 0xc0);
      *(float *)(param_9 + 0x58) = fVar3;
      *(float *)(param_9 + 0x5c) = fVar4;
      *(float *)(param_9 + 0x60) = fVar3;
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                          (float *)(param_9 + 0x58));
      fVar1 = FLOAT_8043a50c;
      *(float *)(param_9 + 0x68) = *(float *)(param_9 + 0x68) + FLOAT_8043a508;
      if (fVar1 < *(float *)(param_9 + 0x68)) {
        *(float *)(param_9 + 0x68) = fVar1;
      }
      zz_01514b8_(param_9);
      fVar3 = *(float *)(param_9 + 0xd8);
      dVar7 = (double)FLOAT_8043a4f8;
      fVar1 = (float)((double)fVar3 - (double)FLOAT_8043a4fc);
      dVar8 = (double)fVar1;
      *(float *)(param_9 + 0xd8) = fVar1;
      if (dVar8 <= dVar7) {
        zz_01513a0_(dVar8,(double)fVar3,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,
                    iVar5,param_12,param_13,param_14,param_15,param_16);
      }
      goto LAB_8015110c;
    }
    iVar5 = zz_01515b8_(param_9);
    if (iVar5 != 0) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      goto LAB_8015110c;
    }
    *(undefined1 *)(param_9 + 0x19) = 2;
  }
  else if ('\x02' < cVar2) goto LAB_8015110c;
  *(undefined1 *)(param_9 + 0x18) = 2;
  zz_008aff0_(param_9);
  *(undefined1 *)(param_9 + 0x82) = 0;
LAB_8015110c:
  if (*(short *)(param_9 + 0x1c6) < 1) {
    zz_00b19b4_(param_9,3,0x10);
    zz_00f036c_(param_9,0xe1);
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 80151160  FUN_80151160 ====

void FUN_80151160(int param_1)

{
  zz_006de10_(*(int *)(param_1 + 0x90),2);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801511a4  FUN_801511a4 ====

void FUN_801511a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801511ec  FUN_801511ec ====

void FUN_801511ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  float afStack_78 [12];
  float afStack_48 [3];
  undefined4 local_3c;
  undefined4 local_2c;
  undefined4 local_1c;
  
  iVar4 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXIdentity_bl(afStack_48);
  local_3c = *(undefined4 *)(iVar4 + 0x8e0);
  local_2c = *(undefined4 *)(iVar4 + 0x920);
  local_1c = *(undefined4 *)(iVar4 + 0x900);
  zz_00457d4_('y',afStack_48,afStack_48,*(short *)(param_9 + 0x148));
  uVar2 = 0x4000;
  zz_00457d4_('x',afStack_48,afStack_48,0x4000);
  zz_00456a0_(afStack_48,afStack_48,(float *)(param_9 + 0x58));
  iVar5 = 0;
  iVar6 = 0;
  iVar4 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar5) != 0) {
      iVar3 = *(int *)(param_9 + 0x54) + iVar6;
      if (*(short *)(iVar3 + 0x20) == 0) {
        gnt4_PSMTXCopy_bl(afStack_48,(float *)(param_9 + 0x114));
        pfVar1 = (float *)(param_9 + 100);
        uVar7 = zz_00455fc_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),pfVar1);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar4 + 0xe0),(float *)(param_9 + 0x114),(undefined *)pfVar1,uVar2,
                    in_r7,in_r8,in_r9,in_r10);
      }
      else {
        zz_00455fc_(afStack_48,afStack_78,(float *)(param_9 + 100));
        pfVar1 = (float *)(iVar3 + 8);
        uVar7 = zz_00456a0_(afStack_78,afStack_78,pfVar1);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar4 + 0xe0),afStack_78,(undefined *)pfVar1,uVar2,in_r7,in_r8,in_r9,
                    in_r10);
      }
    }
    iVar6 = iVar6 + 0x24;
    iVar4 = iVar4 + 4;
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 8015131c  FUN_8015131c ====

void FUN_8015131c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
      zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 801513a0  zz_01513a0_ ====

void zz_01513a0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined1 uVar2;
  short *psVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1e) & 1 << iVar5) == 0) {
      cVar1 = *(char *)(param_9 + 0x11);
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)(1 << iVar5);
      piVar4 = (int *)(*(int *)(param_9 + 0x54) + iVar5 * 0x24);
      *(short *)(piVar4 + 8) = (short)param_10;
      psVar3 = (short *)(cVar1 * 0x18 + -0x7fcbf038 + param_10 * 0xc);
      if ((short)param_10 != 0) {
        *(float *)(param_9 + 0xd8) = FLOAT_8043a510;
        *(undefined1 *)((int)piVar4 + 0x22) = 0;
        *(char *)((int)piVar4 + 0x23) = (char)psVar3[1];
        zz_0018f88_(piVar4,*(int *)(psVar3 + 2),(float *)(piVar4 + 2));
        param_1 = zz_0019338_(piVar4 + 5,*(int *)(psVar3 + 4),(float *)(piVar4 + 7));
      }
      uVar2 = *(undefined1 *)(param_9 + 0x84);
      iVar6 = iVar5 * 4 + 0xe0;
      *(undefined1 *)(*(int *)(param_9 + iVar6) + 0x1a) = uVar2;
      *(undefined1 *)(*(int *)(param_9 + iVar6) + 0x19) = uVar2;
      *(undefined1 *)(*(int *)(param_9 + iVar6) + 0x18) = uVar2;
      iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
      param_1 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                            *(int *)(param_9 + iVar6),(int)*psVar3,0,param_13,param_14,param_15,
                            param_16);
      iVar5 = (int)*(char *)(param_9 + 0x13);
    }
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 801514b8  zz_01514b8_ ====

int zz_01514b8_(int param_1)

{
  undefined1 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar5);
      *(char *)((int)piVar2 + 0x22) = *(char *)((int)piVar2 + 0x22) + '\x01';
      if (*(short *)(piVar2 + 8) != 0) {
        if (*(char *)((int)piVar2 + 0x23) <= *(char *)((int)piVar2 + 0x22)) {
          *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar3);
        }
        zz_0018fd8_(piVar2,(int)*(char *)((int)piVar2 + 0x22),(float *)(piVar2 + 2));
        zz_0019370_(piVar2 + 5,(int)*(char *)((int)piVar2 + 0x22),(float *)(piVar2 + 7));
        zz_0007cac_((double)(float)piVar2[7],*(int *)(iVar4 + 0xe0));
      }
      uVar1 = *(undefined1 *)(param_1 + 0x84);
      *(undefined1 *)(*(int *)(iVar4 + 0xe0) + 0x1a) = uVar1;
      *(undefined1 *)(*(int *)(iVar4 + 0xe0) + 0x19) = uVar1;
      *(undefined1 *)(*(int *)(iVar4 + 0xe0) + 0x18) = uVar1;
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 801515b8  zz_01515b8_ ====

void zz_01515b8_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = param_1 + 0x144;
  iVar6 = 0;
  iVar3 = 0;
  iVar5 = iVar4;
  while( true ) {
    fVar1 = FLOAT_8043a518;
    if (*(char *)(param_1 + 0x13) <= iVar6) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar6) != 0) {
      iVar2 = *(int *)(param_1 + 0x54) + iVar3;
      if (*(short *)(iVar2 + 0x20) == 0) {
        *(float *)(param_1 + 0x14c) = FLOAT_8043a514;
        *(float *)(iVar5 + 0xc) = fVar1;
        *(undefined2 *)(iVar4 + 0x1c) = 0xf;
      }
      else {
        *(float *)(iVar5 + 0xc) = *(float *)(iVar2 + 0x1c) / FLOAT_8043a51c;
        *(undefined2 *)(iVar4 + 0x1c) = 0x1e;
      }
    }
    iVar3 = iVar3 + 0x24;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + 1;
  }
  zz_0151668_(param_1);
  return;
}



// ==== 80151668  zz_0151668_ ====

int zz_0151668_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  
  iVar5 = 0;
  iVar4 = param_1 + 0x144;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar2) != 0) {
      iVar1 = *(int *)(param_1 + 0x54) + iVar5;
      if (*(short *)(iVar1 + 0x20) == 0) {
        dVar7 = (double)FLOAT_8043a4fc;
        *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) - *(float *)(iVar4 + 0xc);
        dVar6 = (double)*(float *)(param_1 + 0x14c);
        if ((dVar6 <= dVar7) && (dVar7 = dVar6, dVar6 < (double)FLOAT_8043a4f8)) {
          dVar7 = (double)FLOAT_8043a4f8;
        }
      }
      else {
        dVar7 = (double)FLOAT_8043a4fc;
        *(float *)(iVar1 + 0x1c) = *(float *)(iVar1 + 0x1c) - *(float *)(iVar4 + 0xc);
        dVar6 = (double)*(float *)(iVar1 + 0x1c);
        if ((dVar6 <= dVar7) && (dVar7 = dVar6, dVar6 < (double)FLOAT_8043a4f8)) {
          dVar7 = (double)FLOAT_8043a4f8;
        }
      }
      if (dVar7 <= (double)FLOAT_8043a4f8) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar2);
      }
      else {
        zz_0007cac_(dVar7,*(int *)(iVar3 + 0xe0));
      }
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 4;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 8015188c  zz_015188c_ ====

void zz_015188c_(int param_1)

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
    FUN_800e4294(param_1,-0x7fcbe318,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fcbe2b8,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fcbe258,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fcbe1f8,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}



// ==== 80151960  zz_0151960_ ====

void zz_0151960_(int param_1)

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
      FUN_800e43e0(param_1,(float *)&DAT_80341ce8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341d48,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341da8,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80341e08,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcbe318,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fcbe2b8,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fcbe258,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcbe1f8,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}



// ==== 80151ab8  zz_0151ab8_ ====

void zz_0151ab8_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80151af0  zz_0151af0_ ====

void zz_0151af0_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe318,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe2b8,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe258,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbe1f8,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fcbe318,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fcbe2b8,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fcbe258,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcbe1f8,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80151c38  FUN_80151c38 ====

void FUN_80151c38(int param_1)

{
  zz_015188c_(param_1);
  return;
}



// ==== 80151c74  FUN_80151c74 ====

void FUN_80151c74(int param_1)

{
  zz_0151960_(param_1);
  return;
}



// ==== 80151ca0  FUN_80151ca0 ====

void FUN_80151ca0(int param_1)

{
  zz_0151ab8_(param_1);
  return;
}



// ==== 80151cc0  FUN_80151cc0 ====

void FUN_80151cc0(int param_1)

{
  zz_0151af0_(param_1);
  return;
}



// ==== 80151ce0  FUN_80151ce0 ====

void FUN_80151ce0(int param_1)

{
  (*(code *)(&PTR_FUN_80341e68)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80151d1c  FUN_80151d1c ====

void FUN_80151d1c(int param_1)

{
  (*(code *)(&PTR_FUN_80341e74)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80151d58  FUN_80151d58 ====

void FUN_80151d58(int param_1)

{
  *(undefined1 *)(param_1 + 0x543) = 0xff;
  (*(code *)(&PTR_FUN_80341e88)[*(char *)(param_1 + 0x540)])();
  zz_0151fd0_(param_1);
  return;
}



// ==== 80151db0  FUN_80151db0 ====

void FUN_80151db0(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(char *)(param_1 + 0x581) == '\x03') {
    *(float *)(param_1 + 0x80c) = FLOAT_8043a520;
  }
  *(undefined2 *)(param_1 + 0x548) = 0x1e;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  fVar1 = FLOAT_8043a520;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a520;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_8043a524,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  return;
}



// ==== 80151e50  FUN_80151e50 ====

void FUN_80151e50(int param_1)

{
  int iVar1;
  short sVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) &&
     (sVar2 = *(short *)(param_1 + 0x548) + -1, *(short *)(param_1 + 0x548) = sVar2, 0 < sVar2)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 80151ed4  FUN_80151ed4 ====

void FUN_80151ed4(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90a) {
        zz_0082824_(param_1,0x69);
      }
      else if ((sVar1 < 0x90a) && (sVar1 == 0x903)) {
        zz_0082824_(param_1,0x68);
      }
    }
  }
  return;
}



// ==== 80151f7c  FUN_80151f7c ====

void FUN_80151f7c(int param_1)

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



// ==== 80151fd0  zz_0151fd0_ ====

void zz_0151fd0_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a528;
  fVar1 = FLOAT_8043a520;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a528;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ((*(char *)(param_1 + 0x581) == '\x03') && ('\0' < *(char *)(param_1 + 0x540))) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80152064  FUN_80152064 ====

void FUN_80152064(int param_1)

{
  (*(code *)(&PTR_FUN_80341e98)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801520a0  FUN_801520a0 ====

void FUN_801520a0(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_8043a524,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}



// ==== 80152104  FUN_80152104 ====

void FUN_80152104(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  if (iVar1 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else if ((((0 < iVar1) ||
            (sVar2 = *(short *)(param_1 + 0x548) + -1, *(short *)(param_1 + 0x548) = sVar2,
            sVar2 < 1)) && (*(char *)(param_1 + 0x1cef) == '\x01')) &&
          (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x90a) {
        zz_0082824_(param_1,0x69);
      }
      else if ((sVar2 < 0x90a) && (sVar2 == 0x903)) {
        zz_0082824_(param_1,0x68);
      }
    }
  }
  return;
}



// ==== 80152208  FUN_80152208 ====

void FUN_80152208(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80152264  FUN_80152264 ====

void FUN_80152264(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_80341ea4)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 801522bc  FUN_801522bc ====

void FUN_801522bc(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043a524;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  zz_004beb8_(dVar1,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}



// ==== 80152308  FUN_80152308 ====

void FUN_80152308(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  if (iVar1 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if ((((0 < iVar1) ||
            (sVar2 = *(short *)(param_1 + 0x548) + -1, *(short *)(param_1 + 0x548) = sVar2,
            sVar2 < 1)) && (*(char *)(param_1 + 0x1cef) == '\x01')) &&
          (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x90a) {
        zz_0082824_(param_1,0x69);
      }
      else if ((sVar2 < 0x90a) && (sVar2 == 0x903)) {
        zz_0082824_(param_1,0x68);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80152424  FUN_80152424 ====

void FUN_80152424(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_9,1);
  if (iVar1 == 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8015247c  FUN_8015247c ====

void FUN_8015247c(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80341eb0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801524c4  FUN_801524c4 ====

void FUN_801524c4(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_8043a52c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a524,param_1,1,2,3,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043a524,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  fVar1 = FLOAT_8043a520;
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 80152590  FUN_80152590 ====

void FUN_80152590(int param_1)

{
  int iVar1;
  short sVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 1) {
    zz_00b22f4_(param_1);
  }
  iVar1 = zz_006d0dc_(param_1,0x81,0);
  if ((((iVar1 != 0) ||
       (sVar2 = *(short *)(param_1 + 0x548) + -1, *(short *)(param_1 + 0x548) = sVar2, sVar2 < 1))
      && (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x90a) {
        zz_0082824_(param_1,0x69);
      }
      else if ((sVar2 < 0x90a) && (sVar2 == 0x903)) {
        zz_0082824_(param_1,0x68);
      }
    }
  }
  return;
}



// ==== 80152698  FUN_80152698 ====

void FUN_80152698(int param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  iVar2 = zz_004cd24_(param_1,1);
  if ((iVar2 == 1) || (iVar1 == 1)) {
    if (iVar1 == 1) {
      *(float *)(param_1 + 0x694) = FLOAT_8043a530 + *(float *)(param_1 + 0x1dc8);
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80152730  FUN_80152730 ====

void FUN_80152730(int param_1)

{
  (*(code *)(&PTR_FUN_80341ebc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015276c  FUN_8015276c ====

void FUN_8015276c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80341ed4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801527bc  FUN_801527bc ====

void FUN_801527bc(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043a520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a520;
  return;
}



// ==== 80152878  FUN_80152878 ====

void FUN_80152878(int param_1)

{
  float fVar1;
  int iVar2;
  short sVar3;
  
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if ((sVar3 < 1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x1e;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043a534 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
           FLOAT_8043a538);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043a534 * *(float *)(param_1 + 0x764)) / FLOAT_8043a538;
    }
    fVar1 = FLOAT_8043a53c;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a520;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a524,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80152988  FUN_80152988 ====

void FUN_80152988(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  short sVar5;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x03') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_801529c0;
  }
  zz_004cd24_(param_1,0xf);
LAB_801529c0:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a540;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  sVar5 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar5;
  if ((sVar5 < 1) || (uVar4 = FUN_80066838((double)FLOAT_8043a53c,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043a548;
    fVar1 = FLOAT_8043a544;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 80152a78  FUN_80152a78 ====

void FUN_80152a78(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  if (iVar2 == 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  else {
    if (*(char *)(param_1 + 0x542) == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x03') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x03' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_8043a54c;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(undefined2 *)(param_1 + 0x548) = 0x1e;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(undefined2 *)(param_1 + 0x548) = 6;
          }
          dVar3 = (double)FLOAT_8043a524;
          *(float *)(param_1 + 0x4c) = FLOAT_8043a520;
          zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
        }
        else {
          *(undefined1 *)(param_1 + 0x542) = 99;
        }
      }
    }
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 80152c20  FUN_80152c20 ====

void FUN_80152c20(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar6;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x1cef) == '\x02') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a524;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      sVar6 = *(short *)(param_1 + 0x548) + -1;
      *(short *)(param_1 + 0x548) = sVar6;
      if ((sVar6 < 1) || (uVar4 = FUN_80066838((double)FLOAT_8043a53c,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_8043a550;
        fVar2 = FLOAT_8043a548;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043a520,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a530;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  else if ((cVar1 < '\x04') && (iVar5 = zz_004cd24_(param_1,0xf), iVar5 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    return;
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  if (iVar5 != 0) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80152dcc  FUN_80152dcc ====

void FUN_80152dcc(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80152e04  FUN_80152e04 ====

void FUN_80152e04(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80341eec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80152e54  FUN_80152e54 ====

void FUN_80152e54(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar2 = FLOAT_8043a558;
  fVar1 = FLOAT_8043a554;
  *(float *)(param_1 + 0x558) = FLOAT_8043a554;
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a520;
  return;
}



// ==== 80152f38  FUN_80152f38 ====

void FUN_80152f38(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a55c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a55c;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043a520;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043a52c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043a520;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043a538;
    *(float *)(param_1 + 0x558) = FLOAT_8043a538;
    fVar3 = FLOAT_8043a53c;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a524,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 80153078  FUN_80153078 ====

void FUN_80153078(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043a520;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043a52c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043a53c,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043a524;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80153158  FUN_80153158 ====

void FUN_80153158(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043a52c < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043a560,param_1);
  if (0 < (int)uVar6) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x541) == '\0') {
    uVar2 = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
    zz_006660c_(param_1);
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_800669d0(param_1,0x40);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
    *(undefined2 *)(param_1 + 0x72) = uVar2;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043a520;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar5 = zz_004cd24_(param_1,0xf);
        if (iVar5 != 1) {
          return;
        }
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_801532f8;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043a564;
      fVar3 = FLOAT_8043a548;
      if (*(char *)(param_1 + 0x1cef) != '\x02') {
        return;
      }
      if (*(char *)(param_1 + 0x1cf0) != '\x01') {
        return;
      }
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0;
      *(undefined2 *)(param_1 + 0x54a) = 0x1500;
      *(float *)(param_1 + 0x558) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar3 < *(float *)(param_1 + 0x558)) {
      zz_0067754_(param_1,(short *)(param_1 + 0x72),*(short *)(param_1 + 0x54a));
      return;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  zz_0066ed8_(param_1,*(ushort *)(param_1 + 0x5ae),*(undefined2 *)(param_1 + 0x54a));
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_801532f8:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 80153358  FUN_80153358 ====

void FUN_80153358(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80153390  FUN_80153390 ====

void FUN_80153390(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80341f00)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801533e0  FUN_801533e0 ====

void FUN_801533e0(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  dVar2 = (double)FLOAT_8043a524;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 8015349c  FUN_8015349c ====

void FUN_8015349c(int param_1)

{
  float fVar1;
  short sVar3;
  int iVar2;
  
  zz_006660c_(param_1);
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if (0 < sVar3) {
    iVar2 = FUN_800669d0(param_1,0xc0);
    if (iVar2 == 0) goto LAB_8015350c;
  }
  fVar1 = FLOAT_8043a560;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x1e;
  if (fVar1 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8015350c:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8015354c  FUN_8015354c ====

/* WARNING: Removing unreachable block (ram,0x8015376c) */
/* WARNING: Removing unreachable block (ram,0x8015355c) */

void FUN_8015354c(int param_1)

{
  float fVar1;
  uint uVar2;
  short sVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar5 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a520;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a534 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a538
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar4 + 0x8e0);
    local_28 = *(float *)(iVar4 + 0x8f0);
    local_24 = *(undefined4 *)(iVar4 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a538 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a520;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a568;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a56c;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043a568);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043a554,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043a570 * (double)*(float *)(param_1 + 0x44)) goto LAB_80153760;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    sVar3 = *(short *)(param_1 + 0x548) + -1;
    *(short *)(param_1 + 0x548) = sVar3;
    if (0 < sVar3) {
      return;
    }
  }
LAB_80153760:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 80153788  FUN_80153788 ====

void FUN_80153788(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a520;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a520) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a520;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a538 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8015382c  FUN_8015382c ====

void FUN_8015382c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80341f10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015387c  FUN_8015387c ====

void FUN_8015387c(int param_1)

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
  dVar2 = (double)FLOAT_8043a524;
  *(float *)(param_1 + 0x558) = FLOAT_8043a554;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 80153938  FUN_80153938 ====

void FUN_80153938(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_8043a520;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043a52c;
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801539b4;
  }
  fVar2 = FLOAT_8043a560;
  fVar1 = FLOAT_8043a538;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801539b4:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 801539f4  FUN_801539f4 ====

/* WARNING: Removing unreachable block (ram,0x80153c20) */
/* WARNING: Removing unreachable block (ram,0x80153a04) */

void FUN_801539f4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar5 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a520;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a578 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a538
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar4 + 0x8e0);
    local_28 = *(float *)(iVar4 + 0x8f0);
    local_24 = *(undefined4 *)(iVar4 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a538 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a520;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a568;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a56c;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043a568);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043a554,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043a570 * (double)*(float *)(param_1 + 0x44)) goto LAB_80153c14;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043a520;
    fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043a52c;
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_80153c14:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 80153c3c  FUN_80153c3c ====

void FUN_80153c3c(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a520;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a520) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a520;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a538 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80153ce0  FUN_80153ce0 ====

void FUN_80153ce0(int param_1)

{
  (*(code *)(&PTR_FUN_80341f20)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80153d1c  FUN_80153d1c ====

void FUN_80153d1c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80341f2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80153d6c  FUN_80153d6c ====

void FUN_80153d6c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(float *)(param_1 + 0x80c) = fVar1;
  *(undefined1 *)(param_1 + 0x543) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_004beb8_((double)FLOAT_8043a524,param_1,0xf,4,0,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_8043a524,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80153e5c  FUN_80153e5c ====

void FUN_80153e5c(int param_1)

{
  float fVar1;
  short sVar3;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1cef) == '\x01') {
    if (*(char *)(param_1 + 0x1cf0) == '\x03') goto LAB_80153e94;
  }
  zz_004cd24_(param_1,0xf);
LAB_80153e94:
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if ((sVar3 < 1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    fVar1 = FLOAT_8043a530;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = fVar1;
    fVar1 = FLOAT_8043a520;
    if (*(char *)(param_1 + 0x581) == '\x02') {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a57c;
    }
    else if (*(char *)(param_1 + 0x581) == '\x01') {
      *(float *)(param_1 + 0x48) = FLOAT_8043a520;
      *(float *)(param_1 + 0x50) = fVar1;
    }
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x72) + -0x8000;
  }
  return;
}



// ==== 80153f3c  FUN_80153f3c ====

void FUN_80153f3c(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x544) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    if (*(char *)(param_1 + 0x581) == '\0') {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a580;
    }
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90a) {
        zz_01541d8_(param_1,1);
      }
      else if ((sVar1 < 0x90a) && (sVar1 == 0x903)) {
        zz_01541d8_(param_1,0);
      }
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
    else {
      if (iVar2 == 0) {
        *(float *)(param_1 + 0x694) = FLOAT_8043a554 + *(float *)(param_1 + 0x1dc8);
      }
      else {
        *(float *)(param_1 + 0x694) = FLOAT_8043a530 + *(float *)(param_1 + 0x1dc8);
      }
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80154090  FUN_80154090 ====

void FUN_80154090(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a520;
  if (iVar2 == 0) {
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a520;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    else if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x05')) {
      *(undefined1 *)(param_1 + 0x544) = 1;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  FUN_80067310((double)FLOAT_8043a52c,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    if ('\0' < *(char *)(param_1 + 0x543)) {
      zz_00b22f4_(param_1);
      *(char *)(param_1 + 0x543) = *(char *)(param_1 + 0x543) + -1;
    }
  }
  if ((*(char *)(param_1 + 0x1cee) != '\0') ||
     ((iVar2 == 0 && (*(char *)(param_1 + 0x544) == '\x01')))) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar2 == 0) {
      *(float *)(param_1 + 0x48) = FLOAT_8043a584;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_8043a554 + *(float *)(param_1 + 0x1dc8);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 801541d8  zz_01541d8_ ====

void zz_01541d8_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x3d;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801542d8;
    *(code **)(puVar1 + 0x10c) = FUN_80154de8;
    puVar1[0x13] = 0;
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



// ==== 801542d8  FUN_801542d8 ====

void FUN_801542d8(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_80341f90)[*(char *)(param_1 + 0x18)])(param_1);
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x144);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x144);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x144);
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x144);
  return;
}



// ==== 80154368  FUN_80154368 ====

void FUN_80154368(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x28;
  iVar2 = -((int)*(short *)(&DAT_80341f42 + iVar3) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_1,(int)*(short *)(&DAT_80341f42 + iVar3));
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x90);
    *(undefined1 *)(param_1 + 0x18) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + (char)(&DAT_80341f40)[iVar3] * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fcbe0bc),(float *)(param_1 + 0x20));
    zz_0083d60_(param_1,iVar2,(int)(char)(&DAT_80341f40)[iVar3]);
    dVar5 = (double)FLOAT_8043a58c;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_80341f58 + iVar3);
    dVar6 = (double)FLOAT_8043a588;
    uVar1 = *(undefined2 *)(&DAT_80341f50 + iVar3);
    *(undefined2 *)(param_1 + 0x1c4) = uVar1;
    *(undefined2 *)(param_1 + 0x1c8) = uVar1;
    *(undefined2 *)(param_1 + 0x1c6) = uVar1;
    *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(iVar2 + 0x70);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(iVar2 + 0x72);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar2 + 0x74);
    *(undefined2 *)(param_1 + 0x148) = 600;
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(&DAT_80341f5c + iVar3);
    dVar4 = (double)(float)(dVar5 - (double)*(float *)(&DAT_80341f5c + iVar3));
    *(short *)(param_1 + 0x7e) =
         (short)(int)(dVar6 / (double)(float)(dVar4 / (double)*(float *)(&DAT_80341f60 + iVar3)));
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0;
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x1c) = 0xffffffff;
    zz_0007030_(dVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb374,
                *(int *)(param_1 + 0xe0),*(int *)(&DAT_80341f64 + iVar3),
                *(int *)(param_1 + 0xe0) + 0x18,in_r7,in_r8,in_r9,in_r10);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x40;
    *(code **)(param_1 + 0x100) = FUN_80154d38;
    zz_0089100_(param_1,1,1);
    *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_80341f52 + iVar3);
    *(undefined1 *)(param_1 + 0x82) = 1;
    zz_00f036c_(param_1,0xf7);
    *(byte *)(param_1 + 0x2ac) = *(byte *)(param_1 + 0x2ac) | 0x10;
  }
  return;
}



