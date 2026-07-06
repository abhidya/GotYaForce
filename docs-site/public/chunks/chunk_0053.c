// ==== 801b4708  zz_01b4708_ ====

void zz_01b4708_(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_01b4768__803816ec)[*(char *)(param_1 + 0x540)])(param_1);
  zz_01b49b4_(param_1);
  return;
}



// ==== 801b4768  zz_01b4768_ ====

void zz_01b4768_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043b98c;
  fVar1 = FLOAT_8043b988;
  dVar3 = (double)FLOAT_8043b990;
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



// ==== 801b4800  zz_01b4800_ ====

void zz_01b4800_(int param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x542) == '\0') {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    iVar1 = zz_006d0dc_(param_1,0xc1,0);
    if ((iVar1 != 1) && (FLOAT_8043b98c < *(float *)(param_1 + 0x558))) {
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



// ==== 801b48b8  zz_01b48b8_ ====

void zz_01b48b8_(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_0082824_(param_1,0x6d);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_0082824_(param_1,0x6c);
      }
    }
  }
  return;
}



// ==== 801b4960  zz_01b4960_ ====

void zz_01b4960_(int param_1)

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



// ==== 801b49b4  zz_01b49b4_ ====

void zz_01b49b4_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043b998;
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b998;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x540)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801b4a3c  zz_01b4a3c_ ====

void zz_01b4a3c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b4a8c__803816fc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b4a8c  zz_01b4a8c_ ====

void zz_01b4a8c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b9a0;
  fVar1 = FLOAT_8043b98c;
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
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801b4b34  zz_01b4b34_ ====

void zz_01b4b34_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_8043b990;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,7,0xffffffff,0xffffffff);
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_8043b9a4;
    fVar1 = FLOAT_8043b98c;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  return;
}



// ==== 801b4c04  zz_01b4c04_ ====

void zz_01b4c04_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_0082824_(param_1,0x6d);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_0082824_(param_1,0x6c);
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_8043b9a4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  }
  return;
}



// ==== 801b4d10  zz_01b4d10_ ====

void zz_01b4d10_(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
    fVar1 = FLOAT_8043b9a4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
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



// ==== 801b4dfc  zz_01b4dfc_ ====

void zz_01b4dfc_(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_01b4e54__8038170c)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 801b4e54  zz_01b4e54_ ====

void zz_01b4e54_(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043b994;
  dVar2 = (double)FLOAT_8043b990;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 801b4ea0  zz_01b4ea0_ ====

void zz_01b4ea0_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,1);
  fVar3 = FLOAT_8043b98c;
  if (*(char *)(param_1 + 0x543) < '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if (((('\0' < *(char *)(param_1 + 0x543)) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_0082824_(param_1,0x6d);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_0082824_(param_1,0x6c);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801b4fb8  zz_01b4fb8_ ====

void zz_01b4fb8_(double param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801b5010  zz_01b5010_ ====

void zz_01b5010_(int param_1)

{
  (*(code *)(&PTR_zz_01b504c__80381718)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801b504c  zz_01b504c_ ====

void zz_01b504c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b509c__80381730)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b509c  zz_01b509c_ ====

void zz_01b509c_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043b9a0;
  fVar1 = FLOAT_8043b98c;
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
  *(float *)(param_1 + 0x80c) = FLOAT_8043b98c;
  return;
}



// ==== 801b5158  zz_01b5158_ ====

void zz_01b5158_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    fVar1 = FLOAT_8043b988;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043b9a8 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043b9a8 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043b9ac;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801b5270  zz_01b5270_ ====

void zz_01b5270_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x04') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_801b52a8;
  }
  zz_004cd24_(param_1,0xf);
LAB_801b52a8:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar4 = FUN_80066838((double)FLOAT_8043b9ac,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043b9b8;
    fVar1 = FLOAT_8043b9b4;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 801b5370  zz_01b5370_ ====

void zz_01b5370_(int param_1)

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
      if ((*(char *)(param_1 + 0x1cef) == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x04') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x04' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_8043b9bc;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_8043b988;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_8043b9c0;
          }
          dVar3 = (double)FLOAT_8043b990;
          *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
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



// ==== 801b5518  zz_01b5518_ ====

void zz_01b5518_(int param_1)

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
      *(float *)(param_1 + 0x4c) = FLOAT_8043b990;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar2 = FLOAT_8043b98c;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if ((*(float *)(param_1 + 0x558) <= fVar2) ||
         (uVar4 = FUN_80066838((double)FLOAT_8043b9ac,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_8043b9c4;
        fVar2 = FLOAT_8043b9b8;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043b98c,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b9c8;
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



// ==== 801b56d4  zz_01b56d4_ ====

void zz_01b56d4_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 801b5708  zz_01b5708_ ====

void zz_01b5708_(void)

{
  return;
}



// ==== 801b570c  zz_01b570c_ ====

void zz_01b570c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b575c__80381748)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b575c  zz_01b575c_ ====

void zz_01b575c_(int param_1)

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
  fVar2 = FLOAT_8043b9cc;
  fVar1 = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x558) = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b98c;
  return;
}



// ==== 801b5840  zz_01b5840_ ====

void zz_01b5840_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043b9d0;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9d0;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043b98c;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043b98c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043b988;
    *(float *)(param_1 + 0x558) = FLOAT_8043b988;
    fVar3 = FLOAT_8043b9ac;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 801b5980  zz_01b5980_ ====

void zz_01b5980_(int param_1)

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
  fVar2 = FLOAT_8043b98c;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b9ac,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043b990;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801b5a60  zz_01b5a60_ ====

void zz_01b5a60_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043b99c < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043b9d4,param_1);
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
  fVar3 = FLOAT_8043b98c;
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
      goto LAB_801b5c00;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043b9d8;
      fVar3 = FLOAT_8043b9b8;
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
LAB_801b5c00:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 801b5c60  zz_01b5c60_ ====

void zz_01b5c60_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 801b5c94  zz_01b5c94_ ====

void zz_01b5c94_(void)

{
  return;
}



// ==== 801b5c98  zz_01b5c98_ ====

void zz_01b5c98_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b5ce8__8038175c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b5ce8  zz_01b5ce8_ ====

void zz_01b5ce8_(int param_1)

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
  dVar2 = (double)FLOAT_8043b990;
  *(float *)(param_1 + 0x558) = FLOAT_8043b9a0;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 801b5da4  zz_01b5da4_ ====

void zz_01b5da4_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_8043b98c < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801b5e24;
  }
  fVar2 = FLOAT_8043b9d4;
  fVar1 = FLOAT_8043b988;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801b5e24:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 801b5e64  zz_01b5e64_ ====

/* WARNING: Removing unreachable block (ram,0x801b6094) */
/* WARNING: Removing unreachable block (ram,0x801b5e74) */

void zz_01b5e64_(int param_1)

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
  fVar1 = FLOAT_8043b98c;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b9a8 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b988
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
    local_34 = FLOAT_8043b988 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b98c;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b9dc;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b9e0;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043b9dc);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043b9a0,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_8043b978 * (double)*(float *)(param_1 + 0x44)) goto LAB_801b6088;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_8043b98c;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_801b6088:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801b60b0  zz_01b60b0_ ====

void zz_01b60b0_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b98c;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b98c) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b98c;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b988 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801b6154  zz_01b6154_ ====

void zz_01b6154_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b61a4__8038176c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b61a4  zz_01b61a4_ ====

void zz_01b61a4_(int param_1)

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
  dVar2 = (double)FLOAT_8043b990;
  *(float *)(param_1 + 0x558) = FLOAT_8043b9a0;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 801b6260  zz_01b6260_ ====

void zz_01b6260_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_8043b98c;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801b62dc;
  }
  fVar2 = FLOAT_8043b9d4;
  fVar1 = FLOAT_8043b988;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801b62dc:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 801b631c  zz_01b631c_ ====

/* WARNING: Removing unreachable block (ram,0x801b6548) */
/* WARNING: Removing unreachable block (ram,0x801b632c) */

void zz_01b631c_(int param_1)

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
  fVar1 = FLOAT_8043b98c;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b9e4 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b988
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
    local_34 = FLOAT_8043b988 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b98c;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b9dc;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b9e0;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043b9dc);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043b9a0,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043b978 * (double)*(float *)(param_1 + 0x44)) goto LAB_801b653c;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043b98c;
    fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_801b653c:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801b6564  zz_01b6564_ ====

void zz_01b6564_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b98c;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b98c) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b98c;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b988 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801b6608  zz_01b6608_ ====

void zz_01b6608_(int param_1)

{
  (*(code *)(&PTR_zz_01b6644__8038177c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801b6644  zz_01b6644_ ====

void zz_01b6644_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b6694__8038178c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b6694  zz_01b6694_ ====

void zz_01b6694_(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  fVar2 = FLOAT_8043b9b0;
  fVar1 = FLOAT_8043b98c;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  else if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  fVar2 = FLOAT_8043b9ec;
  *(float *)(param_1 + 0x48) = FLOAT_8043b9e8;
  fVar1 = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}



// ==== 801b6798  zz_01b6798_ ====

void zz_01b6798_(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  fVar1 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 801b6868  zz_01b6868_ ====

void zz_01b6868_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_014452c_(param_1,3);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_014452c_(param_1,1);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 801b6968  zz_01b6968_ ====

void zz_01b6968_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x694) = FLOAT_8043b994 + *(float *)(param_1 + 0x1dc8);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801b6a1c  zz_01b6a1c_ ====

void zz_01b6a1c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b6a6c__8038179c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b6a6c  zz_01b6a6c_ ====

void zz_01b6a6c_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b9a0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  if (0 < *(short *)(param_1 + 0x784)) {
    if (*(char *)(param_1 + 0x581) == '\x01') {
      if (*(float *)(param_1 + 0x48) <= FLOAT_8043b98c) {
        *(float *)(param_1 + 0x48) = FLOAT_8043b9f0;
      }
      else {
        *(float *)(param_1 + 0x48) = FLOAT_8043b9c8;
      }
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_8043b9f4;
    }
    *(float *)(param_1 + 0x50) = FLOAT_8043b9ec;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,4,1,0xffffffff,0xffffffff);
  return;
}



// ==== 801b6b7c  zz_01b6b7c_ ====

void zz_01b6b7c_(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_006e1ac_(param_1,0xc1,1);
  return;
}



// ==== 801b6c2c  zz_01b6c2c_ ====

void zz_01b6c2c_(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_014452c_(param_1,3);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_014452c_(param_1,1);
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 801b6d20  zz_01b6d20_ ====

void zz_01b6d20_(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043b9b0;
  dVar3 = (double)FLOAT_8043b99c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b980) * FLOAT_8043b9f8);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x54a));
  if (*(char *)(param_1 + 0x1cef) == -1) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
  }
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801b6e0c  zz_01b6e0c_ ====

void zz_01b6e0c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x707) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = zz_01b6f18_;
    *(code **)(puVar1 + 0x10c) = zz_01b7180_;
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



// ==== 801b6f18  zz_01b6f18_ ====

void zz_01b6f18_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_01b6f6c__80382110)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801b6f6c  zz_01b6f6c_ ====

void zz_01b6f6c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x49;
  fVar1 = FLOAT_8043ba00;
  *(undefined *)(param_9 + 0x89) = (&DAT_80435a18)[*(char *)(param_9 + 0x13)];
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803820f8 + *(char *)(param_9 + 0x13) * 0xc);
  *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(&DAT_803820fc + *(char *)(param_9 + 0x13) * 0xc)
  ;
  dVar5 = (double)*(float *)(&DAT_80382100 + *(char *)(param_9 + 0x13) * 0xc);
  *(float *)(param_9 + 0x6c) = *(float *)(&DAT_80382100 + *(char *)(param_9 + 0x13) * 0xc);
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar6 = zz_0007030_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80435a1c + *(char *)(param_9 + 0x13) * 4),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_80435a1c + *(char *)(param_9 + 0x13) * 4);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043ba04,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_01b70d8_(param_9);
  return;
}



// ==== 801b70d8  zz_01b70d8_ ====

void zz_01b70d8_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(uint *)(iVar1 + 0x5e0) & 0x20000000) != 0) {
    return;
  }
  *(short *)(param_1 + 0x74) =
       *(short *)(param_1 + 0x74) +
       *(short *)(&DAT_80435a10 +
                 ((int)(*(char *)(iVar1 + 0x5db) == '\x11' ||
                       (*(char *)(iVar1 + 0x5db) == '\x0e' ||
                       FLOAT_8043ba08 < *(float *)(iVar1 + 0x650))) + *(char *)(param_1 + 0x13) * 2)
                 * 2);
  return;
}



// ==== 801b7150  zz_01b7150_ ====

void zz_01b7150_(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  return;
}



// ==== 801b7160  zz_01b7160_ ====

void zz_01b7160_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801b7180  zz_01b7180_ ====

void zz_01b7180_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar4 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar4 + 0xae) == '\0') {
    iVar2 = *(int *)(param_9 + 0xe0);
    if (*(char *)(iVar4 + 0x3ec) == '\x04') {
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
  if ((*(char *)(param_9 + 0x13) == '\0') &&
     (bVar1 = zz_008b480_(), (*(byte *)(iVar4 + 0x3e5) & bVar1) != 0)) {
    DAT_803c1140 = &local_24;
    DAT_803c1154 = &local_28;
    local_24 = DAT_802b3650;
    local_20 = DAT_802b3654;
    local_1c = DAT_802b3658;
    local_28 = DAT_8043ba0c;
    DAT_803c1144 = 0;
    DAT_803c1150 = &DAT_80435a24;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = (undefined1)DAT_80435a28;
    FUN_80051998(-0x7fc3eed0);
  }
  return;
}



// ==== 801b729c  zz_01b729c_ ====

void zz_01b729c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  uVar1 = 0x20;
  gnt4_memset(&DAT_803d4b2c,0,0x20);
  DAT_803d4b2c = FLOAT_8043ba10;
  DAT_803d4b30 = 1;
  DAT_803d4b34 = 1;
  DAT_803d4b38 = 0;
  zz_02ade34_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803d4b2c,1,uVar1,
              in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4_memset(&DAT_803d4a50,0,0xdc);
  return;
}



// ==== 801b7304  zz_01b7304_ ====

void zz_01b7304_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  int iVar13;
  char *__s;
  double dVar14;
  
  iVar8 = param_10 * 0x1c;
  if (param_9 < 1) {
    iVar9 = param_9 * 0xdc;
    __s = &DAT_803d4a50 + iVar9;
    if (*__s != '\0') {
      zz_01b74a8_(param_9);
    }
    gnt4_memset(__s,0,0xdc);
    *__s = '\x01';
    uVar3 = *(ushort *)(&DAT_80382132 + iVar8);
    uVar12 = 0x11;
    (&DAT_803d4a51)[iVar9] = (char)param_9;
    iVar10 = (uint)uVar3 * 1000;
    dVar14 = (double)FLOAT_8043ba14;
    uVar11 = (uint)*(ushort *)(&DAT_80382130 + iVar8);
    uVar3 = *(ushort *)(&DAT_80382134 + iVar8);
    uVar4 = *(ushort *)(&DAT_80382136 + iVar8);
    bVar1 = (&DAT_80382138)[iVar8];
    bVar2 = (&DAT_80382139)[iVar8];
    iVar13 = (int)(dVar14 * (double)*(float *)(&DAT_8031a024 + (char)PTR_DAT_8043394c[0x2c] * 4));
    *(int *)(&DAT_803d4b14 + iVar9) = iVar13;
    *(undefined4 *)(&DAT_803d4aa4 + iVar9) = 0x11;
    *(uint *)(&DAT_803d4a84 + iVar9) = uVar11;
    *(int *)(&DAT_803d4a88 + iVar9) = iVar10;
    *(uint *)(&DAT_803d4a8c + iVar9) = (uint)uVar3;
    *(uint *)(&DAT_803d4a90 + iVar9) = (uint)uVar4;
    *(uint *)(&DAT_803d4a94 + iVar9) = (uint)bVar1;
    *(uint *)(&DAT_803d4a98 + iVar9) = (uint)bVar2;
    iVar6 = zz_02ada60_(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int *)(&DAT_803d4a84 + iVar9),(uint)bVar1,(uint)uVar4,(uint)uVar3,iVar10,
                        uVar11,0x11,iVar13);
    uVar3 = *(ushort *)(&DAT_80382134 + iVar8);
    *(int *)(&DAT_803d4aa0 + iVar9) = iVar6;
    uVar4 = *(ushort *)(&DAT_80382136 + iVar8);
    *(int *)(&DAT_803d4a9c + iVar9) = param_11;
    iVar8 = *(int *)(&DAT_803d4aa0 + iVar9) + 0x1f;
    uVar5 = param_11 + iVar8 & 0xffffffe0;
    *(uint *)(&DAT_803d4a5c + iVar9) = uVar5;
    *(int *)(&DAT_803d4a60 + iVar9) =
         ((int)(uVar3 + 0xf) >> 4) * 0x10 * ((int)(uVar4 + 0xf) >> 4) * 0x10 * 4;
    puVar7 = zz_02ab8ec_(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         (int *)(&DAT_803d4a84 + iVar9),uVar5,iVar8,*(int *)(&DAT_803d4aa0 + iVar9),
                         iVar10,uVar11,uVar12,iVar13);
    *(undefined4 **)(&DAT_803d4ab4 + iVar9) = puVar7;
    (**(code **)(**(int **)(&DAT_803d4ab4 + iVar9) + 0x24))
              (*(int **)(&DAT_803d4ab4 + iVar9),iVar9 + -0x7fc2b4f8,iVar9 + -0x7fc2b4f4);
    uVar12 = (**(code **)(**(int **)(&DAT_803d4ab4 + iVar9) + 0x20))();
    *(undefined4 *)(&DAT_803d4ab8 + iVar9) = uVar12;
  }
  return;
}



// ==== 801b74a8  zz_01b74a8_ ====

void zz_01b74a8_(int param_1)

{
  int iVar1;
  
  if (param_1 < 1) {
    iVar1 = param_1 * 0xdc;
    if ((&DAT_803d4a50)[iVar1] != '\0') {
      (**(code **)(**(int **)(&DAT_803d4ab4 + iVar1) + 0x1c))();
      (**(code **)(**(int **)(&DAT_803d4ab4 + iVar1) + 0x14))();
      gnt4_memset(&DAT_803d4a50 + iVar1,0,0xdc);
    }
  }
  return;
}



// ==== 801b7528  zz_01b7528_ ====

undefined4 zz_01b7528_(void)

{
  zz_01b74a8_(0);
  return 0x70007;
}



// ==== 801b757c  zz_01b757c_ ====

void zz_01b757c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,uint param_11,undefined4 param_12,undefined4 param_13,
                undefined4 ***param_14,undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint **ppuVar7;
  int *piVar8;
  undefined8 uVar9;
  
  if ((param_9 < 1) && (iVar3 = param_9 * 0xdc, (&DAT_803d4a50)[iVar3] != '\0')) {
    iVar4 = param_10 * 0x1c;
    *(int *)(&DAT_803d4a54 + iVar3) = param_10;
    piVar8 = (int *)(&DAT_80382120 + iVar4);
    iVar2 = *piVar8;
    (&DAT_803d4a58)[param_9 * 0x37] = piVar8;
    if (iVar2 != 2) {
      uVar1 = *(ushort *)(&DAT_80382136 + iVar4);
      *(int *)(&DAT_803d4a74 + iVar3) =
           ((int)((*(ushort *)(&DAT_80382134 + iVar4) >> 1) + 0x1f) >> 5) * 0x20;
      *(uint *)(&DAT_803d4a78 + iVar3) = (uint)(uVar1 >> 1);
      *(uint *)(&DAT_803d4a64 + iVar3) = *(int *)(&DAT_803d4a74 + iVar3) * 2 + 0x1fU & 0xffffffe0;
      *(uint *)(&DAT_803d4a68 + iVar3) = (uint)uVar1;
      iVar2 = gnt4_GXGetTexBufferSize_bl
                        (*(uint *)(&DAT_803d4a64 + iVar3) & 0xffff,
                         *(uint *)(&DAT_803d4a68 + iVar3) & 0xffff,1,'\0',0);
      *(int *)(&DAT_803d4a6c + iVar3) = iVar2;
      ppuVar7 = (uint **)0x0;
      iVar2 = gnt4_GXGetTexBufferSize_bl
                        (*(uint *)(&DAT_803d4a74 + iVar3) & 0xffff,
                         *(uint *)(&DAT_803d4a78 + iVar3) & 0xffff,3,'\0',0);
      *(int *)(&DAT_803d4a7c + iVar3) = iVar2;
      *(undefined4 *)(&DAT_803d4a70 + iVar3) = *(undefined4 *)(&DAT_803d4a5c + iVar3);
      *(int *)(&DAT_803d4a80 + iVar3) =
           *(int *)(&DAT_803d4a70 + iVar3) + *(int *)(&DAT_803d4a6c + iVar3);
      gnt4_memset(*(void **)(&DAT_803d4a70 + iVar3),0,*(size_t *)(&DAT_803d4a6c + iVar3));
      gnt4_memset(*(void **)(&DAT_803d4a80 + iVar3),0x80,*(size_t *)(&DAT_803d4a7c + iVar3));
      *(int *)(&DAT_803d4a60 + iVar3) =
           *(int *)(&DAT_803d4a6c + iVar3) + *(int *)(&DAT_803d4a7c + iVar3);
      uVar6 = *(uint *)(&DAT_803d4a68 + iVar3);
      zz_002b27c_(*(uint *)(&DAT_803d4a70 + iVar3),*(uint *)(&DAT_803d4a80 + iVar3),
                  *(uint *)(&DAT_803d4a64 + iVar3),uVar6);
      (**(code **)(**(int **)(&DAT_803d4ab4 + iVar3) + 0x1c))();
      if ((param_11 & 4) == 0) {
        uVar5 = **(uint **)(&DAT_803d4ab4 + iVar3);
        (**(code **)(uVar5 + 0x28))(*(uint **)(&DAT_803d4ab4 + iVar3),0);
        (&DAT_803d4a52)[iVar3] = 1;
      }
      else {
        uVar5 = **(uint **)(&DAT_803d4ab4 + iVar3);
        (**(code **)(uVar5 + 0x28))(*(uint **)(&DAT_803d4ab4 + iVar3),1);
        (&DAT_803d4a52)[iVar3] = 0;
      }
      uVar9 = zz_01b7894_(param_9,*(int *)(&DAT_803d4b14 + iVar3));
      if ((param_11 & 1) == 0) {
        if (*piVar8 == 0) {
          uVar5 = *(uint *)(&DAT_80382128 + iVar4);
          uVar9 = zz_02ae1e0_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int **)(&DAT_803d4ab4 + iVar3),*(int *)(&DAT_80382124 + iVar4),uVar5
                              ,uVar6,ppuVar7,param_14,param_15,param_16);
        }
        else {
          uVar5 = **(uint **)(&DAT_803d4ab4 + iVar3);
          uVar9 = (**(code **)(uVar5 + 0x18))
                            (*(uint **)(&DAT_803d4ab4 + iVar3),
                             (&PTR_s_sfd_op_sfd_8038212c)[param_10 * 7]);
        }
      }
      else if (*piVar8 == 0) {
        uVar5 = *(uint *)(&DAT_80382128 + iVar4);
        uVar9 = zz_02aa17c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(&DAT_803d4ab4 + iVar3),*(int *)(&DAT_80382124 + iVar4),uVar5,
                            uVar6,ppuVar7,param_14,param_15,param_16);
      }
      else {
        uVar9 = zz_02aa338_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(&DAT_803d4ab4 + iVar3),
                            (int *)(&PTR_s_sfd_op_sfd_8038212c)[param_10 * 7],uVar5,uVar6,ppuVar7,
                            param_14,param_15,param_16);
      }
      if ((param_11 & 2) == 0) {
        zz_02af560_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(&DAT_803d4ab4 + iVar3),1,uVar5,uVar6,ppuVar7,param_14,param_15,param_16
                   );
      }
      else {
        zz_02af560_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(&DAT_803d4ab4 + iVar3),0,uVar5,uVar6,ppuVar7,param_14,param_15,param_16
                   );
      }
      (&DAT_803d4a53)[iVar3] = 0;
      *(undefined4 *)(&DAT_803d4afc + iVar3) = 0;
    }
  }
  return;
}



// ==== 801b77f8  zz_01b77f8_ ====

void zz_01b77f8_(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((param_1 < 1) && (iVar2 = param_1 * 0xdc, (&DAT_803d4a50)[iVar2] != '\0')) {
    (**(code **)(**(int **)(&DAT_803d4ab4 + iVar2) + 0x28))();
    uVar1 = countLeadingZeros(param_2);
    (&DAT_803d4a52)[iVar2] = (char)(uVar1 >> 5);
  }
  return;
}



// ==== 801b786c  zz_01b786c_ ====

void zz_01b786c_(undefined4 param_1)

{
  zz_01b77f8_(0,param_1);
  return;
}



// ==== 801b7894  zz_01b7894_ ====

void zz_01b7894_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 < 1) && (iVar2 = param_1 * 0xdc, (&DAT_803d4a50)[iVar2] != '\0')) {
    if (*(int *)(&DAT_803d4b14 + iVar2) < param_2) {
      param_2 = *(int *)(&DAT_803d4b14 + iVar2);
    }
    *(int *)(&DAT_803d4b18 + iVar2) = param_2;
    iVar1 = *(int *)(&DAT_80319dfc + *(int *)(&DAT_803d4b18 + iVar2) * 4) / 10 +
            (*(int *)(&DAT_80319dfc + *(int *)(&DAT_803d4b18 + iVar2) * 4) >> 0x1f);
    (**(code **)(**(int **)(&DAT_803d4ab4 + iVar2) + 0x2c))
              (*(int **)(&DAT_803d4ab4 + iVar2),iVar1 - (iVar1 >> 0x1f));
  }
  return;
}



// ==== 801b7928  zz_01b7928_ ====

void zz_01b7928_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (0 < param_1) {
    return;
  }
  iVar1 = param_1 * 0xdc;
  if ((&DAT_803d4a50)[iVar1] == '\0') {
    return;
  }
  *(undefined4 *)(&DAT_803d4b1c + iVar1) = *(undefined4 *)(&DAT_803d4b18 + iVar1);
  *(undefined4 *)(&DAT_803d4b20 + iVar1) = 0;
  *(undefined4 *)(&DAT_803d4b28 + iVar1) = param_2;
  *(undefined4 *)(&DAT_803d4b24 + iVar1) = param_2;
  return;
}



// ==== 801b7968  zz_01b7968_ ====

undefined1 zz_01b7968_(int param_1)

{
  if (0 < param_1) {
    return 0;
  }
  if ((&DAT_803d4a50)[param_1 * 0xdc] == '\0') {
    return 0;
  }
  return (&DAT_803d4a53)[param_1 * 0xdc];
}



// ==== 801b79a4  zz_01b79a4_ ====

uint zz_01b79a4_(int param_1)

{
  uint uVar1;
  
  if (0 < param_1) {
    return 1;
  }
  if ((&DAT_803d4a50)[param_1 * 0xdc] == '\0') {
    return 1;
  }
  uVar1 = countLeadingZeros(3 - *(int *)(&DAT_803d4ab8 + param_1 * 0xdc));
  return uVar1 >> 5;
}



// ==== 801b79ec  zz_01b79ec_ ====

void zz_01b79ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                char *param_9,undefined4 param_10,int param_11,int param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar5;
  char *pcVar6;
  undefined4 *puVar7;
  undefined8 uVar8;
  int local_58 [21];
  
  if (*param_9 != '\0') {
    if ((0 < *(int *)(param_9 + 0xd8)) && (*(int *)(param_9 + 0x68) == 2)) {
      *(int *)(param_9 + 0xd8) = *(int *)(param_9 + 0xd8) + -1;
      param_12 = *(int *)(param_9 + 0xd4);
      param_11 = *(int *)(param_9 + 0xcc) * 0x100;
      uVar1 = param_11 +
              ((*(int *)(param_9 + 0xd0) - *(int *)(param_9 + 0xcc)) *
               (param_12 - *(int *)(param_9 + 0xd8)) * 0x100) / param_12;
      param_1 = zz_01b7894_((uint)(byte)param_9[1],
                            ((int)uVar1 >> 8) + (uint)((int)uVar1 < 0 && (uVar1 & 0xff) != 0));
    }
    if (param_9[2] != '\0') {
      *(int *)(param_9 + 0xc0) = *(int *)(param_9 + 0xc0) + 1;
      uVar8 = zz_02a9b94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 100),local_58,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      if (local_58[0] != 0) {
        if (2 < *(int *)(param_9 + 0xc0)) {
          *(int *)(param_9 + 0xac) = *(int *)(param_9 + 0xac) + 1;
        }
        param_9[0xc0] = '\0';
        param_9[0xc1] = '\0';
        param_9[0xc2] = '\0';
        param_9[0xc3] = '\0';
        uVar8 = zz_02ab034_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 100),*(undefined4 *)(param_9 + 0x14),
                            *(undefined4 *)(param_9 + 0x18),param_12,param_13,param_14,param_15,
                            param_16);
        iVar5 = *(int *)(param_9 + 0x20);
        puVar7 = *(undefined4 **)(param_9 + 0x30);
        uVar8 = zz_02ab110_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 100),local_58,iVar5,puVar7,param_13,param_14,param_15
                            ,param_16);
        gnt4_DCFlushRangeNoSync_bl(*(uint *)(param_9 + 0x20),*(int *)(param_9 + 0x1c));
        iVar4 = *(int *)(param_9 + 0x2c);
        gnt4_DCFlushRangeNoSync_bl(*(uint *)(param_9 + 0x30),iVar4);
        zz_02a9838_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 100),iVar4,iVar5,puVar7,param_13,param_14,param_15,param_16);
        param_9[3] = '\x01';
      }
    }
    uVar2 = (**(code **)(**(int **)(param_9 + 100) + 0x20))();
    *(undefined4 *)(param_9 + 0x68) = uVar2;
    pcVar6 = param_9 + 0xbc;
    iVar4 = **(int **)(param_9 + 100);
    uVar8 = (**(code **)(iVar4 + 0x24))(*(int **)(param_9 + 100),param_9 + 0xb8);
    uVar2 = extraout_r4;
    uVar3 = zz_02af328_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 100),extraout_r4,pcVar6,iVar4,param_13,param_14,param_15,
                        param_16);
    *(undefined4 *)(param_9 + 0xa4) = uVar3;
    uVar2 = zz_02a9f94_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 100),uVar2,pcVar6,iVar4,param_13,param_14,param_15,
                        param_16);
    *(undefined4 *)(param_9 + 0xa8) = uVar2;
    uVar8 = zz_02aeda8_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 100),(int *)(param_9 + 0x6c),pcVar6,iVar4,param_13,
                        param_14,param_15,param_16);
    uVar2 = extraout_r4_00;
    uVar1 = zz_02a9710_(*(int *)(param_9 + 100));
    *(uint *)(param_9 + 0xa0) =
         uVar1 << 0x18 | (uVar1 & 0xff00) << 8 | uVar1 >> 8 & 0xff00 | uVar1 >> 0x18;
    uVar3 = zz_02af250_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 100),uVar2,pcVar6,iVar4,param_13,param_14,param_15,
                        param_16);
    *(undefined4 *)(param_9 + 0xb0) = uVar3;
    iVar4 = zz_02af2b0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 100),uVar2,pcVar6,iVar4,param_13,param_14,param_15,
                        param_16);
    *(int *)(param_9 + 0xb4) = iVar4;
  }
  return;
}



// ==== 801b7b98  zz_01b7b98_ ====

undefined4
zz_01b7b98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,int param_11,int param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_01b79ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803d4a50,
              &DAT_803d0000,param_11,param_12,param_13,param_14,param_15,param_16);
  return 0x70007;
}



// ==== 801b7bf0  FUN_801b7bf0 ====

void FUN_801b7bf0(void)

{
  int iVar1;
  char cVar2;
  
  iVar1 = DAT_803d4a58;
  if ((DAT_803d4a50 != '\0') && (cVar2 = zz_01b7968_(0), cVar2 != '\0')) {
    zz_01b7c54_((uint)*(ushort *)(iVar1 + 0x14),(uint)*(ushort *)(iVar1 + 0x16),0,0,0x280,0x1c0);
  }
  return;
}



// ==== 801b7c54  zz_01b7c54_ ====

void zz_01b7c54_(uint param_1,uint param_2,short param_3,short param_4,short param_5,short param_6)

{
  FUN_8002b7ac(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}



// ==== 801b7d70  FUN_801b7d70 ====

void FUN_801b7d70(int param_1)

{
  *(undefined1 *)(param_1 + 0x582) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  zz_00e7758_(param_1,1,0);
  zz_00e7758_(param_1,1,1);
  *(float *)(param_1 + 0x144) = FLOAT_8043ba18;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x14a) = 0;
  *(undefined1 *)(param_1 + 0x14b) = 0;
  if (*(char *)(param_1 + 0x3ec) == '\x04') {
    *(float *)(param_1 + 0x154) = FLOAT_8043ba1c;
  }
  else {
    *(float *)(param_1 + 0x154) = FLOAT_8043ba20;
  }
  *(float *)(param_1 + 0x150) = FLOAT_8043ba24;
  return;
}



// ==== 801b7ea8  FUN_801b7ea8 ====

void FUN_801b7ea8(int param_1)

{
  zz_0156a58_(param_1);
  return;
}



// ==== 801b7ef0  FUN_801b7ef0 ====

void FUN_801b7ef0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803821b8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801b7f30  FUN_801b7f30 ====

void FUN_801b7f30(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x582) == '\0') {
    zz_006bda8_(param_1);
    zz_0099e70_(param_1,(&DAT_803821d4)[param_2]);
  }
  return;
}



// ==== 801b7f8c  FUN_801b7f8c ====

void FUN_801b7f8c(int param_1)

{
  zz_0137540_(param_1,*(char *)(param_1 + 0x582) == '\x01');
  return;
}



// ==== 801b7fc0  FUN_801b7fc0 ====

void FUN_801b7fc0(int param_1,uint param_2)

{
  if ((*(char *)(param_1 + 0x582) == '\x01') && (param_2 != 3)) {
    param_2 = param_2 ^ 3;
  }
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if ((param_2 & 1) != 0) {
    zz_001ab6c_(param_1,0x58);
  }
  if ((param_2 & 2) != 0) {
    zz_001ab6c_(param_1,0x57);
  }
  return;
}



// ==== 801b804c  FUN_801b804c ====

bool FUN_801b804c(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0183730_(param_1,1,0xff);
  return bVar1;
}



// ==== 801b8074  FUN_801b8074 ====

void FUN_801b8074(int param_1)

{
  (*(code *)(&PTR_FUN_803821e0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801b80b0  FUN_801b80b0 ====

void FUN_801b80b0(int param_1)

{
  zz_00660b8_(param_1,2);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803821f0)[*(char *)(param_1 + 0x581)])(param_1);
  return;
}



// ==== 801b8110  FUN_801b8110 ====

void FUN_801b8110(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158688_(param_1,4);
  return;
}



// ==== 801b8140  FUN_801b8140 ====

void FUN_801b8140(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158a94_(param_1);
  return;
}



// ==== 801b8170  FUN_801b8170 ====

void FUN_801b8170(int param_1)

{
  zz_00660b8_(param_1,4);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80382204)[*(char *)(param_1 + 0x581)])(param_1);
  return;
}



// ==== 801b81d0  FUN_801b81d0 ====

void FUN_801b81d0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80382218)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b822c  FUN_801b822c ====

void FUN_801b822c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffd5f;
  *(undefined1 *)(param_1 + 0x6ea) = 0xb;
  if (*(char *)(param_1 + 0x584) == '\x02') {
    *(undefined1 *)(param_1 + 0x6ea) = 0;
  }
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043ba2c;
  *(float *)(param_1 + 0x558) = FLOAT_8043ba28;
  dVar4 = (double)FLOAT_8043ba30;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(float *)(param_1 + 0x3c) = fVar2;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,5,1);
  return;
}



// ==== 801b8330  FUN_801b8330 ====

void FUN_801b8330(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043ba34;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_801b8704(param_1);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 801b83c8  FUN_801b83c8 ====

void FUN_801b83c8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  if (fVar1 < *(float *)(param_1 + 0x48)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  FUN_80067310((double)FLOAT_8043ba24,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_1 + 0x3c),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801b84cc  FUN_801b84cc ====

void FUN_801b84cc(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(char *)(param_1 + 0x584) == '\x01') && ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if ((*(char *)(param_1 + 0x584) == '\x02') && ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043ba34;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar4 = (double)FLOAT_8043ba30;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    FUN_801b8704(param_1);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    FUN_801b8704(param_1);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043ba38,param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_1 + 0x3c)) {
    zz_006ed8c_((double)FLOAT_8043ba20,param_1);
  }
  FUN_80067310((double)FLOAT_8043ba24,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  if (((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ba3c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar3 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    }
  }
  return;
}



// ==== 801b8704  FUN_801b8704 ====

/* WARNING: Removing unreachable block (ram,0x801b8800) */
/* WARNING: Removing unreachable block (ram,0x801b8714) */

void FUN_801b8704(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_8043ba48) * FLOAT_8043ba40;
  }
  dVar3 = (double)(fVar1 / FLOAT_8043ba34);
  *(float *)(param_1 + 0x38) = fVar1 / FLOAT_8043ba34;
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
  if (fVar1 < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = fVar1;
  }
  dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar3 * dVar2);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = (float)(dVar3 * -dVar2);
  if (fVar1 < *(float *)(param_1 + 0x48)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 801b881c  FUN_801b881c ====

void FUN_801b881c(int param_1)

{
  zz_01b883c_(param_1);
  return;
}



// ==== 801b883c  zz_01b883c_ ====

void zz_01b883c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80382228)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b888c  FUN_801b888c ====

void FUN_801b888c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043ba34;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x50) = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043ba50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043ba30,param_1,0xf,4,1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043ba18;
  return;
}



// ==== 801b8964  FUN_801b8964 ====

void FUN_801b8964(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043ba50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801b8a1c  FUN_801b8a1c ====

void FUN_801b8a1c(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e1ac_(param_1,0xc0,1);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043ba48) * FLOAT_8043ba38);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043ba50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_8043ba24,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_8043ba54 < dVar2) {
      zz_00b22f4_(param_1);
    }
  }
  else {
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



// ==== 801b8b6c  FUN_801b8b6c ====

undefined4 FUN_801b8b6c(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if (*(short *)(param_1 + 1000) == 0x407) {
    puVar2 = zz_0088aa0_(param_1,3,8,1,1);
    if (puVar2 == (undefined1 *)0x0) {
      zz_01b9b68_(0);
      uVar1 = 0;
    }
    else {
      *puVar2 = 1;
      puVar2[0x13] = 0;
      puVar2[0x11] = param_2;
      puVar2[0x10] = 0x5b;
      *(code **)(puVar2 + 0xc) = FUN_801b8c90;
      *(code **)(puVar2 + 0x10c) = FUN_801b9adc;
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
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 801b8c90  FUN_801b8c90 ====

void FUN_801b8c90(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0x18) < '\x02') {
      if (*(short *)(*(int *)(param_1 + 0x90) + 1000) == *(short *)(param_1 + 0x94))
      goto LAB_801b8df0;
    }
    piVar2 = &DAT_803c4e6c;
    iVar1 = (int)DAT_80436260;
    if (0 < iVar1) {
      do {
        iVar3 = *piVar2;
        if ((*(short *)(iVar3 + 1000) == 0x407) && (*(char *)(iVar3 + 0x18) < '\x02')) {
          *(int *)(param_1 + 0x8c) = iVar3;
          *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(iVar3 + 0x90);
          *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(iVar3 + 0x94);
          *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(iVar3 + 0x96);
          *(undefined1 *)(param_1 + 0x97) = *(undefined1 *)(iVar3 + 0x97);
          *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(iVar3 + 0x88);
          *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar3 + 200);
          *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar3 + 0xcc);
          *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(iVar3 + 0xb8);
          *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar3 + 0xb4);
          *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(iVar3 + 0xb4);
          *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(iVar3 + 0xb4);
          *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar3 + 0xb4);
          *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar3 + 0xc0);
          *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(iVar3 + 0xc4);
          *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar3 + 0xd0);
          *(undefined4 *)(param_1 + 200) = 0;
          *(undefined2 *)(param_1 + 0x272) = 1;
          zz_0088f98_(param_1,iVar3,1);
          uVar4 = *(undefined4 *)(param_1 + 0x100);
          zz_0089444_(param_1);
          *(undefined4 *)(param_1 + 0x100) = uVar4;
          zz_0089100_(param_1,0,1);
          goto LAB_801b8df0;
        }
        piVar2 = piVar2 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801b8df0:
  (*(code *)(&PTR_FUN_80382488)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801b8e2c  FUN_801b8e2c ====

/* WARNING: Removing unreachable block (ram,0x801b8edc) */

void FUN_801b8e2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined *puVar6;
  uint uVar7;
  int iVar8;
  undefined8 uVar9;
  float afStack_44 [2];
  undefined4 local_3c;
  undefined4 local_2c;
  undefined4 local_1c;
  
  puVar6 = &DAT_80382440;
  uVar4 = 0;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  uVar7 = (uint)*(byte *)(param_9 + 0x11);
  iVar8 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar5 = (*(byte *)(param_9 + 0x11) & 0x7f) * 0x48;
  *(undefined2 *)(param_9 + 0x272) = 4;
  *(undefined2 *)(param_9 + 0x70) = 0;
  iVar3 = (int)*(short *)(iVar8 + 0x72);
  *(short *)(param_9 + 0x72) = *(short *)(iVar8 + 0x72);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar2 = iVar5;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_8038245e + iVar5) * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fc7dba0),(float *)(param_9 + 0x20));
  iVar1 = zz_01b9be0_(iVar8,(int)*(char *)(param_9 + 0x11));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043ba58 *
                                     (double)((longlong)(double)(short)iVar1 * 0x3ff0000000000000)),
                      afStack_44,0x78);
  gnt4_PSMTXConcat_bl((float *)(iVar8 + 0x8d4),afStack_44,afStack_44);
  *(undefined4 *)(param_9 + 0x38) = local_3c;
  *(undefined4 *)(param_9 + 0x3c) = local_2c;
  *(undefined4 *)(param_9 + 0x40) = local_1c;
  zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80382450 + iVar5),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  uVar9 = gnt4_PSMTXCopy_bl((float *)(iVar8 + *(short *)(&DAT_8038245e + iVar5) * 0x30 + 0x8d4),
                            (float *)(param_9 + 0x16c));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80382450 + iVar5);
  *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(&DAT_8038246c + iVar5);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80382444 + iVar5);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80382446 + iVar5);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c) = 600;
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_80382444 + iVar5);
  *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(&DAT_80382454 + iVar5);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8038245c + iVar5),iVar3,uVar4,iVar2,
              puVar6,uVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80382440 + iVar5));
  if (iVar2 == 0) {
    zz_01b9b68_(param_9);
  }
  else {
    if (*(char *)(param_9 + 0x11) < '\0') {
      zz_01b9df0_(param_9,0);
    }
    else {
      zz_00f036c_(param_9,0xdb);
    }
    zz_008458c_((float *)(param_9 + 0x20));
  }
  return;
}



// ==== 801b9028  FUN_801b9028 ====

void FUN_801b9028(int param_1)

{
  char cVar1;
  
  if (*(short *)(param_1 + 0x1c6) < 1) {
    zz_01b9b1c_(param_1);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x02') {
      zz_01b961c_(param_1);
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        zz_01b90a4_(param_1);
      }
      else if (-1 < cVar1) {
        zz_01b94e8_(param_1);
      }
    }
    else if (cVar1 < '\x04') {
      zz_01b98ec_(param_1);
    }
  }
  return;
}



// ==== 801b90a4  zz_01b90a4_ ====

/* WARNING: Removing unreachable block (ram,0x801b94c4) */
/* WARNING: Removing unreachable block (ram,0x801b94bc) */
/* WARNING: Removing unreachable block (ram,0x801b90bc) */
/* WARNING: Removing unreachable block (ram,0x801b90b4) */

void zz_01b90a4_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_78;
  float local_74;
  undefined4 local_70;
  float local_6c;
  float local_68;
  float local_64;
  float afStack_60 [3];
  float local_54;
  float local_44;
  float local_34;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  iVar3 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x48;
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  sVar4 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar4;
  if (sVar4 < 1) {
    zz_01b9df0_(param_1,0);
  }
  else {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      FUN_80083874((double)*(float *)(&DAT_8038244c + iVar3),param_1);
      fVar1 = FLOAT_8043ba64;
      iVar2 = *(int *)(param_1 + 200);
      if (iVar2 == 0) {
        *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) + FLOAT_8043ba68;
        *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
        *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
        *(float *)(param_1 + 0x24) =
             *(float *)(param_1 + 0x24) +
             -(*(float *)(param_1 + 0x50) * fVar1 - *(float *)(param_1 + 0x3c));
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
      }
      else {
        sVar4 = *(short *)(param_1 + 0x1e) + -1;
        *(short *)(param_1 + 0x1e) = sVar4;
        if (sVar4 < 1) {
          *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(&DAT_80382444 + iVar3);
          gnt4_PSMTXCopy_bl((float *)(param_1 + 0x16c),afStack_60);
          local_6c = local_54;
          local_68 = local_44;
          local_64 = local_34;
          gnt4_PSVECSubtract_bl((float *)(iVar2 + 100),&local_6c,&local_6c);
          local_54 = local_54 + local_6c;
          local_44 = local_44 + local_68;
          local_34 = local_34 + local_64;
          gnt4_PSMTXMultVec_bl(afStack_60,(float *)(iVar3 + -0x7fc7db84),&local_78);
          FUN_8006c498((double)*(float *)(&DAT_80382448 + iVar3),param_1,&local_78);
          gnt4_PSVECSubtract_bl(&local_78,(float *)(param_1 + 0x20),&local_6c);
          dVar7 = (double)local_68;
          local_68 = FLOAT_8043ba5c;
          local_78 = *(float *)(param_1 + 0x38);
          local_70 = *(undefined4 *)(param_1 + 0x40);
          local_74 = FLOAT_8043ba5c;
          dVar5 = gnt4_PSVECMag_bl(&local_78);
          dVar6 = gnt4_PSVECMag_bl(&local_6c);
          dVar5 = (double)(float)(dVar6 / dVar5);
          fVar1 = (FLOAT_8043ba60 * (float)(dVar5 * (double)*(float *)(param_1 + 0x3c) - dVar7)) /
                  (float)(dVar5 * dVar5);
          if (*(float *)(&DAT_80382474 + iVar3) < fVar1) {
            fVar1 = *(float *)(&DAT_80382474 + iVar3);
          }
          if (fVar1 < *(float *)(&DAT_80382470 + iVar3)) {
            fVar1 = *(float *)(&DAT_80382470 + iVar3);
          }
          fVar1 = fVar1 - *(float *)(param_1 + 0x50);
          if (*(float *)(&DAT_80382478 + iVar3) < ABS(fVar1)) {
            fVar1 = *(float *)(&DAT_80382478 + iVar3) * (ABS(fVar1) / fVar1);
          }
          *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) + fVar1;
        }
        else {
          *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
          *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
        }
        *(float *)(param_1 + 0x24) =
             *(float *)(param_1 + 0x24) +
             -(*(float *)(param_1 + 0x50) * FLOAT_8043ba64 - *(float *)(param_1 + 0x3c));
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
        zz_00833a4_(param_1);
      }
      zz_00833ec_(param_1);
      zz_0083610_(param_1,(float *)(param_1 + 0x50));
      dVar5 = (double)*(float *)(param_1 + 0x3c);
      zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      *(float *)(param_1 + 0x3c) = (float)dVar5;
      if (*(float *)(param_1 + 0x20) <= *(float *)(DAT_8043625c + 0x38)) {
        if (*(float *)(DAT_8043625c + 0x3c) <= *(float *)(param_1 + 0x20)) {
          if (*(float *)(param_1 + 0x28) <= *(float *)(DAT_8043625c + 0x40)) {
            if (*(float *)(DAT_8043625c + 0x44) <= *(float *)(param_1 + 0x28)) {
              iVar3 = zz_0083714_(param_1);
              if (iVar3 == 0) {
                iVar3 = zz_0084170_(param_1);
                if (iVar3 == 0) {
                  if ((*(byte *)(param_1 + 0x274) & 3) == 0) {
                    if (*(char *)(param_1 + 0x1d9) == '\0') {
                      iVar3 = zz_01b9f8c_(param_1);
                      if (iVar3 != 0) {
                        zz_01b9f0c_(param_1);
                      }
                    }
                    else {
                      zz_01b9df0_(param_1,0);
                    }
                  }
                  else {
                    zz_01b9df0_(param_1,1);
                  }
                }
                else {
                  zz_01b9df0_(param_1,1);
                }
              }
              else {
                zz_01b9df0_(param_1,0);
              }
            }
            else {
              *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x44);
              zz_01b9df0_(param_1,0);
            }
          }
          else {
            *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x40);
            zz_01b9df0_(param_1,0);
          }
        }
        else {
          *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x3c);
          zz_01b9df0_(param_1,0);
        }
      }
      else {
        *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38);
        zz_01b9df0_(param_1,0);
      }
    }
    else {
      zz_01b9b1c_(param_1);
    }
  }
  return;
}



// ==== 801b94e8  zz_01b94e8_ ====

void zz_01b94e8_(int param_1)

{
  int iVar1;
  short sVar2;
  
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    zz_01b9f0c_(param_1);
  }
  else {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20)
                      );
      if (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x20)) {
        *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38);
      }
      if (*(float *)(param_1 + 0x20) < *(float *)(DAT_8043625c + 0x3c)) {
        *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x3c);
      }
      if (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x28)) {
        *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x40);
      }
      if (*(float *)(param_1 + 0x28) < *(float *)(DAT_8043625c + 0x44)) {
        *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x44);
      }
      iVar1 = zz_0084170_(param_1);
      if (iVar1 == 0) {
        if (*(char *)(param_1 + 0x1d9) != '\0') {
          zz_01b9df0_(param_1,0);
        }
      }
      else {
        zz_01b9df0_(param_1,1);
      }
      iVar1 = zz_01b9f8c_(param_1);
      if (iVar1 != 0) {
        zz_01b9f0c_(param_1);
      }
    }
    else {
      zz_01b9b1c_(param_1);
    }
  }
  return;
}



// ==== 801b961c  zz_01b961c_ ====

void zz_01b961c_(int param_1)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  double dVar6;
  float afStack_28 [6];
  
  if (*(char *)(param_1 + 0x1db) == '\0') {
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x3c);
  }
  else {
    *(float *)(param_1 + 0x3c) = FLOAT_8043ba5c;
  }
  iVar1 = zz_01b9f8c_(param_1);
  if (iVar1 == 0) {
    zz_01b9df0_(param_1,0);
  }
  else {
    if (*(char *)(param_1 + 0x1db) == '\0') {
      *(float *)(param_1 + 0x3c) = FLOAT_8043ba5c;
    }
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (sVar2 < 1) {
      zz_01b9b1c_(param_1);
    }
    else if ((*(char *)(param_1 + 0x1de) == '\0') || (*(char *)(param_1 + 0x1db) != '\0')) {
      piVar4 = &DAT_803c4e6c;
      for (iVar1 = 0; iVar1 < DAT_80436260; iVar1 = iVar1 + 1) {
        iVar5 = *piVar4;
        if ((((*(short *)(iVar5 + 1000) == 0x407) && ((*(uint *)(iVar5 + 0x5e0) & 0x9f000000) == 0))
            && (*(char *)(iVar5 + 0x150) == '\x01')) &&
           ((*(byte *)(iVar5 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0)) {
          gnt4_PSVECSubtract_bl((float *)(iVar5 + 0x20),(float *)(param_1 + 0x20),afStack_28);
          dVar6 = gnt4_PSVECMag_bl(afStack_28);
          if (dVar6 < (double)(FLOAT_8043ba6c * *(float *)(iVar5 + 0xb4) +
                              FLOAT_8043ba70 * *(float *)(param_1 + 0xb4))) {
            *(int *)(param_1 + 0x8c) = iVar5;
            *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(iVar5 + 0x90);
            *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(iVar5 + 0x94);
            *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(iVar5 + 0x96);
            *(undefined1 *)(param_1 + 0x97) = *(undefined1 *)(iVar5 + 0x97);
            *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(iVar5 + 0x88);
            *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar5 + 200);
            *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar5 + 0xcc);
            *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(iVar5 + 0xb8);
            *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar5 + 0xb4);
            *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(iVar5 + 0xb4);
            *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(iVar5 + 0xb4);
            *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar5 + 0xb4);
            *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar5 + 0xc0);
            *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(iVar5 + 0xc4);
            *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar5 + 0xd0);
            *(undefined1 *)(param_1 + 0x19) = 3;
            *(undefined1 *)(param_1 + 0x1a) = 0;
            uVar3 = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(iVar5 + 0x144) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(iVar5 + 0x148) = uVar3;
            *(undefined4 *)(iVar5 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
            *(undefined1 *)(iVar5 + 0x150) = 2;
            *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x11c);
            *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 300);
            *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x13c);
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x118);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x128);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x138);
            *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x28);
            *(undefined4 *)(param_1 + 200) = 0;
            *(undefined2 *)(param_1 + 0x272) = 1;
            zz_0088f98_(param_1,iVar5,1);
            zz_008aff0_(param_1);
            uVar3 = *(undefined4 *)(param_1 + 0x100);
            zz_0089444_(param_1);
            *(undefined4 *)(param_1 + 0x100) = uVar3;
            zz_0089100_(param_1,0,1);
            return;
          }
        }
        piVar4 = piVar4 + 1;
      }
    }
    else {
      zz_01b9df0_(param_1,0);
    }
  }
  return;
}



// ==== 801b98ec  zz_01b98ec_ ====

/* WARNING: Removing unreachable block (ram,0x801b9a8c) */
/* WARNING: Removing unreachable block (ram,0x801b98fc) */

void zz_01b98ec_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  double dVar6;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  if (*(char *)(param_1 + 0x1a) == '\0') {
    *(undefined1 *)(param_1 + 0x1a) = 1;
    fVar1 = FLOAT_8043ba74;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(float *)(param_1 + 0xd8) = fVar1;
    zz_0089444_(param_1);
    *(undefined1 *)(param_1 + 0x98) = 5;
    *(code **)(param_1 + 0x100) = zz_0048288_;
    zz_0089100_(param_1,0,1);
  }
  iVar2 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x48;
  iVar4 = *(int *)(param_1 + 0x90);
  dVar6 = (double)(*(float *)(param_1 + 0xd8) / FLOAT_8043ba74);
  iVar3 = iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30;
  local_38 = *(float *)(iVar3 + 0x8dc);
  local_34 = *(undefined4 *)(iVar3 + 0x8ec);
  local_30 = *(undefined4 *)(iVar3 + 0x8fc);
  zz_0046588_(dVar6,(float *)(param_1 + 0x144),&local_38,(float *)(param_1 + 0x38));
  iVar3 = iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30;
  local_38 = *(float *)(iVar3 + 0x8d8);
  local_34 = *(undefined4 *)(iVar3 + 0x8e8);
  local_30 = *(undefined4 *)(iVar3 + 0x8f8);
  zz_0046588_(dVar6,(float *)(param_1 + 0x150),&local_38,(float *)(param_1 + 0x9c));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar4 + *(short *)(&DAT_8038245e + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fc7dba0),&local_38);
  zz_0046588_(dVar6,(float *)(param_1 + 0x15c),&local_38,(float *)(param_1 + 0x20));
  fVar1 = *(float *)(param_1 + 0xd8) - *(float *)(iVar4 + 0x1dc8);
  bVar5 = FLOAT_8043ba5c <= fVar1;
  *(float *)(param_1 + 0xd8) = fVar1;
  if (bVar5) {
    if ((*(char *)(param_1 + 0x1b) == '\0') && (*(float *)(param_1 + 0xd8) <= FLOAT_8043ba78)) {
      zz_00f036c_(param_1,0xdc);
      *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
    }
  }
  else {
    *(undefined1 *)(iVar4 + 0x150) = 1;
    zz_01b9b68_(param_1);
  }
  return;
}



// ==== 801b9ab0  FUN_801b9ab0 ====

void FUN_801b9ab0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 801b9abc  FUN_801b9abc ====

void FUN_801b9abc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801b9adc  FUN_801b9adc ====

void FUN_801b9adc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801b9b1c  zz_01b9b1c_ ====

void zz_01b9b1c_(int param_1)

{
  zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0);
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801b9b68  zz_01b9b68_ ====

void zz_01b9b68_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(short *)(iVar1 + 1000) == 0x407) && (*(char *)(iVar1 + 0x150) == '\x01')) {
    zz_006de10_(iVar1,2);
    *(undefined1 *)(iVar1 + 0x150) = 0;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801b9be0  zz_01b9be0_ ====

int zz_01b9be0_(int param_1,uint param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_30;
  float local_2c;
  float local_28;
  float afStack_24 [7];
  
  iVar3 = *(int *)(param_1 + 200);
  fVar1 = FLOAT_8043ba5c;
  if (iVar3 != 0) {
    iVar2 = (param_2 & 0x7f) * 0x48;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + *(short *)(&DAT_8038245e + iVar2) * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fc7dba0),afStack_24);
    local_30 = *(float *)(iVar3 + 100);
    local_2c = *(float *)(iVar3 + 0x68);
    local_28 = *(float *)(iVar3 + 0x6c);
    gnt4_PSVECSubtract_bl(&local_30,afStack_24,&local_30);
    dVar5 = (double)(local_30 * local_30 + local_28 * local_28);
    if ((double)FLOAT_8043ba5c < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar5 = (double)(float)(dVar5 * DOUBLE_8043ba80 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88));
    }
    local_30 = (float)dVar5;
    if (dVar5 < (double)FLOAT_8043ba90) {
      local_30 = FLOAT_8043ba90;
    }
    fVar1 = (*(float *)(&DAT_8038246c + iVar2) * local_30 * local_30) /
            (FLOAT_8043ba60 * *(float *)(&DAT_80382450 + iVar2) * *(float *)(&DAT_80382450 + iVar2))
    ;
    dVar5 = (double)(local_30 * local_30 - FLOAT_8043ba94 * fVar1 * (fVar1 + local_2c));
    if (dVar5 < (double)FLOAT_8043ba5c) {
      dVar5 = (double)FLOAT_8043ba5c;
    }
    if ((double)FLOAT_8043ba5c < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar4 = DOUBLE_8043ba80 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88);
      dVar5 = (double)(float)(dVar5 * DOUBLE_8043ba80 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_8043ba88));
    }
    dVar5 = gnt4_atan((double)((float)((double)local_30 - dVar5) / (FLOAT_8043ba60 * fVar1)));
    fVar1 = (float)dVar5;
    if (FLOAT_8043ba98 <= fVar1) {
      fVar1 = FLOAT_8043ba98;
    }
  }
  return (int)(short)-(short)(int)(FLOAT_8043ba9c * fVar1);
}



// ==== 801b9df0  zz_01b9df0_ ====

void zz_01b9df0_(int param_1,int param_2)

{
  byte bVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 600;
  fVar2 = FLOAT_8043ba5c;
  if (param_2 == 0) {
    *(float *)(param_1 + 0x38) = FLOAT_8043ba5c;
    *(float *)(param_1 + 0x40) = fVar2;
  }
  else {
    local_18 = *(float *)(param_1 + 0x1cc);
    local_14 = *(undefined4 *)(param_1 + 0x1d0);
    local_10 = *(undefined4 *)(param_1 + 0x1d4);
    gnt4_PSQUATScale_bl((double)FLOAT_8043baa0,&local_18,&local_18);
    dVar4 = gnt4_PSVECMag_bl(&local_18);
    dVar3 = (double)(FLOAT_8043baa4 * *(float *)(param_1 + 0xb4));
    if (dVar3 < dVar4) {
      gnt4_PSQUATScale_bl((double)(float)(dVar3 / dVar4),&local_18,&local_18);
    }
    *(float *)(param_1 + 0x38) = local_18;
    *(undefined4 *)(param_1 + 0x3c) = local_14;
    *(undefined4 *)(param_1 + 0x40) = local_10;
  }
  if (FLOAT_8043ba5c < *(float *)(param_1 + 0x3c)) {
    *(float *)(param_1 + 0x3c) = FLOAT_8043ba5c;
  }
  if (*(float *)(param_1 + 0x50) <
      FLOAT_8043ba60 * *(float *)(&DAT_8038246c + (bVar1 & 0x7f) * 0x48)) {
    *(float *)(param_1 + 0x50) = FLOAT_8043ba60 * *(float *)(&DAT_8038246c + (bVar1 & 0x7f) * 0x48);
  }
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined2 *)(param_1 + 0x272) = 1;
  return;
}



// ==== 801b9f0c  zz_01b9f0c_ ====

void zz_01b9f0c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043ba60;
  fVar1 = FLOAT_8043ba5c;
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined2 *)(param_1 + 0x1c) = 0x4b0;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x3c) = fVar1;
  *(float *)(param_1 + 0x38) = fVar1;
  *(float *)(param_1 + 0x50) =
       fVar2 * *(float *)(&DAT_8038246c + (*(byte *)(param_1 + 0x11) & 0x7f) * 0x48);
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined2 *)(param_1 + 0x272) = 1;
  zz_0019550_(param_1,(undefined4 *)(param_1 + 0x20),0);
  return;
}



// ==== 801b9f8c  zz_01b9f8c_ ====

undefined4 zz_01b9f8c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x3c) <= FLOAT_8043ba5c) {
    if (*(char *)(param_1 + 0x1db) != '\0') {
      return 0x81cd;
    }
    dVar2 = FUN_8003d964((double)(FLOAT_8043baa8 * *(float *)(param_1 + 0xb4)),param_1,
                         (float *)(param_1 + 0x20));
    fVar1 = (float)((double)FLOAT_8043baa8 * (double)*(float *)(param_1 + 0xb4) + dVar2);
    if (*(float *)(param_1 + 0x24) < fVar1) {
      *(float *)(param_1 + 0x24) = fVar1;
      return 0x8444;
    }
  }
  return 0;
}



// ==== 801ba134  FUN_801ba134 ====

void FUN_801ba134(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 3;
  if (*(short *)(param_1 + 1000) == 0x307) {
    zz_013358c_(param_1,2);
    zz_00c74ec_(param_1,6);
  }
  else if (*(short *)(param_1 + 1000) == 0x30d) {
    zz_013358c_(param_1,3);
    zz_00c74ec_(param_1,7);
  }
  *(undefined1 *)(param_1 + 0x147) = 1;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  return;
}



// ==== 801ba1b0  FUN_801ba1b0 ====

void FUN_801ba1b0(int param_1)

{
  zz_010a4ac_(param_1);
  *(undefined1 *)(param_1 + 0x748) = 2;
  if (*(char *)(param_1 + 0x147) == '\x01') {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
  }
  else {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
  }
  return;
}



// ==== 801ba23c  FUN_801ba23c ====

void FUN_801ba23c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803826c8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801ba27c  FUN_801ba27c ====

void FUN_801ba27c(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x147) == '\x01')) {
    *(undefined1 *)(param_1 + 0x147) = 0;
    if (*(short *)(param_1 + 1000) == 0x307) {
      zz_01d2ffc_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x30d) {
      zz_01d2ffc_(param_1,1);
    }
    zz_00f036c_(param_1,0xdb);
  }
  return;
}



// ==== 801ba33c  FUN_801ba33c ====

void FUN_801ba33c(int param_1)

{
  (*(code *)(&PTR_FUN_803826d4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801ba378  FUN_801ba378 ====

void FUN_801ba378(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803826e4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801ba3c0  FUN_801ba3c0 ====

void FUN_801ba3c0(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 801ba3e4  FUN_801ba3e4 ====

void FUN_801ba3e4(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 801ba408  FUN_801ba408 ====

void FUN_801ba408(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 801ba42c  FUN_801ba42c ====

void FUN_801ba42c(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 801ba450  FUN_801ba450 ====

void FUN_801ba450(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 801ba474  FUN_801ba474 ====

void FUN_801ba474(void)

{
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    PTR_DAT_80433930[0x40] = 0;
    zz_002a5f4_(0,0,0,0);
    gnt4_memset(PTR_DAT_80435a30,0,0x200);
  }
  (*(code *)(&PTR_FUN_803836b4)[*(short *)PTR_DAT_80435a30])();
  return;
}



// ==== 801ba4f8  FUN_801ba4f8 ====

void FUN_801ba4f8(void)

{
  int iVar1;
  
  *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = 0xffffffff;
  iVar1 = 0;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x24) = DAT_80436220;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x28) = DAT_80436224;
  *(undefined1 **)(PTR_DAT_80435a30 + 0x2c) = &DAT_803bfe20;
  PTR_DAT_80435a30[0x47] = 0;
  while( true ) {
    if (3 < iVar1) break;
    if (PTR_DAT_80435a30[0x47] != '\0') break;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar1) != 0) {
      PTR_DAT_80435a30[0x46] = (char)iVar1;
      PTR_DAT_80435a30[0x47] = (char)(1 << iVar1);
    }
    iVar1 = iVar1 + 1;
  }
  if (PTR_DAT_80435a30[0x47] == '\0') {
    PTR_DAT_80435a30[0x46] = 0;
    PTR_DAT_80435a30[0x47] = 1;
  }
  return;
}



// ==== 801ba5e4  FUN_801ba5e4 ====

void FUN_801ba5e4(void)

{
  int iVar1;
  
  iVar1 = zz_01f1280_();
  if (iVar1 != 0) {
    *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 2) = 0;
  }
  return;
}



// ==== 801ba638  FUN_801ba638 ====

void FUN_801ba638(void)

{
  (*(code *)(&PTR_LAB_80435a34)[*(short *)(PTR_DAT_80435a30 + 2)])();
  return;
}



// ==== 801ba69c  FUN_801ba69c ====

void FUN_801ba69c(void)

{
  int iVar1;
  
  iVar1 = zz_01ba750_();
  if (iVar1 != 0) {
    *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 2) = 0;
  }
  return;
}



// ==== 801ba6e0  FUN_801ba6e0 ====

void FUN_801ba6e0(void)

{
  int iVar1;
  
  iVar1 = zz_01f12c8_();
  if (iVar1 != 0) {
    *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 2) = 0;
  }
  return;
}



// ==== 801ba750  zz_01ba750_ ====

void zz_01ba750_(void)

{
  (*(code *)(&PTR_FUN_803836c8)[*(short *)(PTR_DAT_80435a30 + 0x10)])();
  return;
}



// ==== 801ba78c  zz_01ba78c_ ====

void zz_01ba78c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  
  zz_01978d0_();
  uVar1 = zz_0008b58_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  return;
}



// ==== 801ba7cc  FUN_801ba7cc ====

undefined4 FUN_801ba7cc(void)

{
  (*(code *)(&PTR_FUN_80435a3c)[*(short *)(PTR_DAT_80435a30 + 0x12)])();
  return 0;
}



// ==== 801ba808  FUN_801ba808 ====

void FUN_801ba808(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  
  *(short *)(PTR_DAT_80435a30 + 0x12) = *(short *)(PTR_DAT_80435a30 + 0x12) + 1;
  uVar1 = zz_0197854_(0);
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,4);
  uVar1 = zz_0044294_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  uVar1 = zz_00437b0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
  zz_00439a0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4);
  return;
}



// ==== 801ba86c  FUN_801ba86c ====

void FUN_801ba86c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  iVar1 = zz_000a3c4_();
  puVar5 = PTR_DAT_80435a30;
  if (iVar1 == 0) {
    puVar2 = (undefined *)0x0;
    uVar3 = 0;
    *(short *)(PTR_DAT_80435a30 + 0x10) = *(short *)(PTR_DAT_80435a30 + 0x10) + 1;
    puVar4 = PTR_DAT_80435a30;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 0;
    zz_002a5f4_(0,0,0,0);
    uVar6 = set_global_menu_mode(6);
    uVar6 = zz_0044318_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                        puVar2,uVar3,puVar4,puVar5,in_r9,in_r10);
    uVar6 = zz_0008a94_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                        extraout_r4_00,puVar2,uVar3,puVar4,puVar5,in_r9,in_r10);
    uVar6 = zz_007fd6c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_01ba78c_,0,
                        puVar2,uVar3,puVar4,puVar5,in_r9,in_r10);
    puVar2 = PTR_DAT_80433934;
    PTR_DAT_80433934[0x1c] = 0;
    zz_0041954_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0);
    uVar6 = zz_0087718_(DAT_803c71e0);
    uVar6 = zz_004453c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                        extraout_r4_01,puVar2,uVar3,puVar4,puVar5,in_r9,in_r10);
    uVar6 = zz_0044bec_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,2,puVar2,
                        uVar3,puVar4,puVar5,in_r9,in_r10);
    zz_01bed58_();
    zz_00e99c8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a084,uVar3
                ,puVar4,puVar5,in_r9,in_r10);
    zz_0027aac_(0,0x1e,0);
  }
  return;
}



// ==== 801ba960  FUN_801ba960 ====

undefined4 FUN_801ba960(void)

{
  if (PTR_DAT_80435a30[0x148] == '\0') {
    zz_01bef70_();
  }
  if ((char)PTR_DAT_80435a30[0x148] < '\x02') {
    *(short *)(PTR_DAT_80435a30 + 0x18) = *(short *)(PTR_DAT_80435a30 + 0x18) + 1;
    (*(code *)(&PTR_FUN_803836d4)[*(short *)(PTR_DAT_80435a30 + 0x12)])();
  }
  if (PTR_DAT_80435a30[0x16d] == '\0') {
    zz_01beda4_();
    zz_01beec0_();
  }
  return 0;
}



// ==== 801ba9ec  FUN_801ba9ec ====

void FUN_801ba9ec(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  char *pcVar6;
  int iVar7;
  
  cVar1 = PTR_DAT_80435a30[0x149];
  if (cVar1 == '\0') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 2;
  }
  else if (cVar1 == '\x01') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 3;
  }
  else if (cVar1 == '\x02') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 4;
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 1;
  }
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
  pcVar6 = &DAT_80383610;
  while( true ) {
    if (*pcVar6 < '\0') break;
    zz_01c13c8_(PTR_DAT_80435a30[0x46],(int)*pcVar6,pcVar6[1]);
    pcVar6 = pcVar6 + 2;
  }
  iVar7 = 0;
  do {
    zz_01c13c8_(PTR_DAT_80435a30[0x46],0xb,(char)iVar7);
    fVar2 = FLOAT_8043bab8;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x1e);
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
  fVar4 = FLOAT_8043bac0;
  fVar3 = FLOAT_8043babc;
  PTR_DAT_80435a30[0x53] = 0;
  fVar5 = FLOAT_8043bac4;
  PTR_DAT_80435a30[0x41] = 0;
  PTR_DAT_80435a30[0x42] = 0xff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x50) = 0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
  PTR_DAT_80435a30[0x52] = 0;
  PTR_DAT_80435a30[0x43] = 0;
  PTR_DAT_80435a30[0x44] = 0;
  *(float *)(PTR_DAT_80435a30 + 0x48) = fVar2;
  *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar3;
  *(float *)(PTR_DAT_80435a30 + 0x30) = fVar4;
  *(float *)(PTR_DAT_80435a30 + 0x34) = fVar5;
  iVar7 = zz_01cce38_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                      *(int *)(PTR_DAT_80433934 + 0x120),0);
  PTR_DAT_80435a30[0x45] = (char)iVar7;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14c) = 0x200;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14e) = 0x100;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x150) = 0x600;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x152) = 0x200;
  zz_01cc43c_(*(int *)(PTR_DAT_80435a30 + 0x2c),*(short **)(PTR_DAT_80435a30 + 0x28),
              *(int *)(PTR_DAT_80435a30 + 0x24));
  return;
}



// ==== 801babbc  FUN_801babbc ====

void FUN_801babbc(void)

{
  int iVar1;
  
  (*(code *)(&PTR_FUN_803836f4)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  iVar1 = zz_01cce38_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                      *(int *)(PTR_DAT_80433934 + 0x120),0);
  PTR_DAT_80435a30[0x45] = (char)iVar1;
  if ('\0' < (char)PTR_DAT_80435a30[0x53]) {
    PTR_DAT_80435a30[0x53] = PTR_DAT_80435a30[0x53] + -1;
  }
  if ('\0' < (char)PTR_DAT_80435a30[0x41]) {
    PTR_DAT_80435a30[0x41] = PTR_DAT_80435a30[0x41] + -1;
  }
  return;
}



// ==== 801bac50  FUN_801bac50 ====

void FUN_801bac50(void)

{
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 1;
  zz_0027aac_(0,0x1e,0);
  return;
}



// ==== 801bac88  FUN_801bac88 ====

void FUN_801bac88(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    }
    else {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
    }
    zz_0027c1c_();
  }
  return;
}



// ==== 801bacd8  FUN_801bacd8 ====

void FUN_801bacd8(void)

{
  uint uVar1;
  
  zz_01bf144_();
  uVar1 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  if ((uVar1 & 0x80) == 0) {
    if ((uVar1 & 0x40) == 0) {
      if ((uVar1 & 0x20) == 0) {
        if ((uVar1 & 0x400) == 0) {
          if ((uVar1 & 0x800) == 0) {
            if ((uVar1 & 0x100) != 0) {
              if ((char)PTR_DAT_80435a30[0x42] < '\0') {
                if (-1 < *(short *)(PTR_DAT_80435a30 + 0x50)) {
                  if ((*(uint *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                                *(short *)(PTR_DAT_80435a30 + 0x146) * 0x20 + 0x880) &
                      1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0) {
                    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
                    *(undefined2 *)(PTR_DAT_80435a30 + 0x144) =
                         *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
                    zz_00f0468_(0,0x7a,0);
                  }
                }
              }
              else if (-1 < *(short *)(PTR_DAT_80435a30 + 0x146)) {
                *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
                *(undefined2 *)(PTR_DAT_80435a30 + 0x144) =
                     *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
                *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
                zz_01ccb94_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                            (int)(char)PTR_DAT_80435a30[0x42]);
                zz_00f0468_(0,0x7a,0);
              }
              if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
                zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),
                            (int)*(short *)(PTR_DAT_80435a30 + 0x144));
              }
            }
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
            zz_00f0468_(0,0x7a,0);
          }
        }
        else if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
          PTR_DAT_80435a30[0x16c] = 0;
          zz_00f0468_(0,0x7a,0);
        }
      }
      else {
        *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 1;
        zz_0027aac_(0,0x1e,1);
        zz_00f0468_(0,0x7a,0);
      }
    }
    else {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 2;
      zz_0027aac_(0,0x1e,1);
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 6;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    zz_00f0468_(0,0x7a,0);
  }
  return;
}



// ==== 801baf6c  FUN_801baf6c ====

void FUN_801baf6c(void)

{
  short sVar1;
  uint uVar2;
  short *psVar3;
  
  zz_01bf144_();
  uVar2 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  if ((uVar2 & 0x200) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
    zz_00f0468_(0,0x7b,0);
    return;
  }
  if ((uVar2 & 0x400) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x144);
    PTR_DAT_80435a30[0x16c] = 0;
    zz_00f0468_(0,0x7a,0);
    return;
  }
  if ((uVar2 & 0x800) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    zz_00f0468_(0,0x7a,0);
    return;
  }
  if ((uVar2 & 0x100) != 0) {
    if ((char)PTR_DAT_80435a30[0x42] < '\0') {
      sVar1 = *(short *)(PTR_DAT_80435a30 + 0x50);
      if (-1 < sVar1) {
        if ((int)sVar1 == (int)*(short *)(PTR_DAT_80435a30 + 0x144)) {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
        }
        else {
          zz_01cc0a4_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)sVar1,
                      (int)*(short *)(PTR_DAT_80435a30 + 0x144));
          psVar3 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                            *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x870);
          if ((*psVar3 < 0) ||
             ((*(uint *)(psVar3 + 8) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) != 0)) {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
        }
        zz_00f0468_(0,0x7a,0);
      }
    }
    else if ((*(uint *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                        *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x880) &
             1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0) {
      if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
        *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
        zz_01ccaf8_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                    (int)(char)PTR_DAT_80435a30[0x42],(int)*(short *)(PTR_DAT_80435a30 + 0x144));
        *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_01ccc1c_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                    (int)(char)PTR_DAT_80435a30[0x42],(int)*(short *)(PTR_DAT_80435a30 + 0x144));
        *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
        *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
        zz_00f0468_(0,0x7a,0);
      }
    }
    if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
      zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x144));
    }
    return;
  }
  return;
}



// ==== 801bb1e0  FUN_801bb1e0 ====

void FUN_801bb1e0(void)

{
  (*(code *)(&PTR_FUN_8038370c)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



// ==== 801bb21c  FUN_801bb21c ====

void FUN_801bb21c(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 6;
  PTR_DAT_80435a30[0x15d] = 6;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 1;
  zz_01bfa54_();
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,0);
  return;
}



// ==== 801bb2d0  FUN_801bb2d0 ====

void FUN_801bb2d0(void)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar3 = iVar3 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar3)) {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = iVar3 + -1;
    if (iVar3 < 0) {
      iVar3 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar3 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar3;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0xa00) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      iVar3 = (int)(char)PTR_DAT_80435a30[0x15b];
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << iVar3) == 0) {
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 3;
          zz_0027aac_(0,0x1e,1);
        }
        else if (iVar3 == 1) {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 5;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        }
        else if (iVar3 == 2) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          iVar3 = zz_01cc7b4_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40]);
          if (-1 < iVar3) {
            iVar1 = iVar3 - (char)PTR_DAT_80435a30[0x40];
            if (iVar1 < 0) {
              iVar1 = iVar1 + 0x14;
            }
            uVar2 = 1;
            if (iVar1 < 0xb) {
              uVar2 = 0xff;
            }
            zz_01c13c8_(PTR_DAT_80435a30[0x46],2,uVar2);
            PTR_DAT_80435a30[0x52] = 0;
            PTR_DAT_80435a30[0x40] = (char)iVar3;
            PTR_DAT_80435a30[0x41] = 0x10;
          }
        }
        else if (iVar3 == 3) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          zz_01cc960_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40]);
        }
        else if (iVar3 == 4) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
            zz_01cbf38_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                        (int)*(short *)(PTR_DAT_80435a30 + 0x146));
            *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
          }
          else {
            zz_01cbf38_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                        (int)*(short *)(PTR_DAT_80435a30 + 0x144));
            if (*(short *)(PTR_DAT_80435a30 + 0x146) == *(short *)(PTR_DAT_80435a30 + 0x144)) {
              *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
            }
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = 2;
        }
        else if (iVar3 == 5) {
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
          }
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
          PTR_DAT_80435a30[0x15a] = 0;
          PTR_DAT_80435a30[0x15b] = 1;
          PTR_DAT_80435a30[0x15c] = 2;
          PTR_DAT_80435a30[0x15d] = 2;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0x80;
          zz_01e488c_(PTR_DAT_80435a30[0x46],7,7);
        }
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 801bb69c  FUN_801bb69c ====

void FUN_801bb69c(void)

{
  int iVar1;
  
  iVar1 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar1 = iVar1 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 < 0) {
      iVar1 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar1 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar1;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x200) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << (int)(char)PTR_DAT_80435a30[0x15b]) == 0) {
        *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cbe54_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
          }
          else {
            zz_01cbe54_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x144))
            ;
            if (*(short *)(PTR_DAT_80435a30 + 0x146) == *(short *)(PTR_DAT_80435a30 + 0x144)) {
              *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
            }
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = 2;
        }
        *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    PTR_DAT_80435a30[0x15a] = 0;
    PTR_DAT_80435a30[0x15b] = 5;
    PTR_DAT_80435a30[0x15c] = 6;
    PTR_DAT_80435a30[0x15d] = 6;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 1;
    zz_01bfa54_();
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,0);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 801bb8c8  FUN_801bb8c8 ====

void FUN_801bb8c8(void)

{
  short sVar1;
  int iVar2;
  
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    sVar1 = *(short *)(PTR_DAT_80435a30 + 0x16);
    if (sVar1 == 0) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 1;
      PTR_DAT_80435a30[0x149] = 3;
    }
    else if (sVar1 == 1) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 3;
      PTR_DAT_80435a30[0x149] = 1;
    }
    else if (sVar1 == 2) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 4;
      PTR_DAT_80435a30[0x149] = 2;
    }
    else if (sVar1 == 3) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 2;
      PTR_DAT_80435a30[0x149] = 0;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
    }
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
  }
  return;
}



// ==== 801bb990  FUN_801bb990 ====

void FUN_801bb990(void)

{
  (*(code *)(&PTR_FUN_80383724)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



// ==== 801bb9cc  FUN_801bb9cc ====

void FUN_801bb9cc(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80383648;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 1;
  while( true ) {
    if (*pcVar2 < '\0') break;
    zz_01e488c_(PTR_DAT_80435a30[0x46],(int)*pcVar2,pcVar2[1]);
    pcVar2 = pcVar2 + 2;
  }
  PTR_DAT_80435a30[0x14a] = 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) = 0xffff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x160) = 0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x15e) = 0;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x164) = 0xffffffff;
  iVar1 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      -0x7fc2b4a0,0,*(uint *)(PTR_DAT_80435a30 + 0x164));
  *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
  zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
              (short *)&DAT_803d4b60,0,PTR_DAT_80435a30 + 0x14c);
  zz_0027aac_(0,0x1e,0);
  return;
}



