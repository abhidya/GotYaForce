// ==== 800d05a8  FUN_800d05a8 ====

void FUN_800d05a8(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) == 0) {
    if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
       (*(char *)(param_1 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        zz_006a3d0_(param_1,'\0',3,0);
        return;
      }
      zz_006bf80_(param_1);
      dVar2 = (double)FLOAT_80438a20;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800d06a8  FUN_800d06a8 ====

void FUN_800d06a8(int param_1)

{
  (*(code *)(&PTR_FUN_8030de10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d06e4  FUN_800d06e4 ====

void FUN_800d06e4(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438a20;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 3,0xffffffff,0xffffffff);
  FUN_800d0c20(param_1);
  return;
}



// ==== 800d0744  FUN_800d0744 ====

void FUN_800d0744(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804389f4;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if (iVar3 < 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      if ((iVar3 < 1) &&
         (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
         *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
        return;
      }
      if (*(char *)(param_1 + 0x1cef) != '\0') {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        FUN_800d0c50(param_1);
      }
    }
  }
  else {
    zz_006a3d0_(param_1,'\0',3,2);
  }
  return;
}



// ==== 800d0814  FUN_800d0814 ====

void FUN_800d0814(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
        zz_006a3d0_(param_9,'\0',3,2);
        return;
      }
      if (((*(uint *)(param_9 + 0x5e0) & 0x10) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006bf80_(param_9);
      dVar2 = (double)FLOAT_80438a20;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      zz_004beb8_(dVar2,param_9,1,2,4,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xf,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800d0938  FUN_800d0938 ====

void FUN_800d0938(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030de1c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d0980  FUN_800d0980 ====

void FUN_800d0980(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_804389f0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80438a20,param_1,0xf,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  FUN_800d0c20(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804389f4;
  return;
}



// ==== 800d0a28  FUN_800d0a28 ====

void FUN_800d0a28(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_800d0c50(param_1);
    }
    zz_00b22f4_(param_1);
  }
  else {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  return;
}



// ==== 800d0ac8  FUN_800d0ac8 ====

void FUN_800d0ac8(int param_1)

{
  int iVar1;
  double dVar2;
  
  FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    zz_004cd24_(param_1,0xf);
    if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
      zz_006d0dc_(param_1,0x81,0);
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
          zz_006a3d0_(param_1,'\0',0,2);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_80438a20;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,0xf,2,7,0xffffffff,0xffffffff);
        return;
      }
    }
    if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) || (*(char *)(param_1 + 0x1cee) != '\0')) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438a24 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800d0c20  FUN_800d0c20 ====

void FUN_800d0c20(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x6ee) == '\0') {
    *(undefined1 *)(param_1 + 0x6ef) = 5;
  }
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  fVar1 = FLOAT_80438a28;
  *(undefined1 *)(param_1 + 0x6ed) = 7;
  *(float *)(param_1 + 0x560) = fVar1;
  return;
}



// ==== 800d0c50  FUN_800d0c50 ====

void FUN_800d0c50(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_006ee14_(param_1,1);
  }
  return;
}



// ==== 800d0cb0  FUN_800d0cb0 ====

void FUN_800d0cb0(int param_1)

{
  (*(code *)(&PTR_FUN_8030de28)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d0cec  FUN_800d0cec ====

void FUN_800d0cec(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 800d0d14  FUN_800d0d14 ====

void FUN_800d0d14(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030de54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d0d64  FUN_800d0d64 ====

void FUN_800d0d64(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80438a2c;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438a30,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438a20;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804389f4;
  return;
}



// ==== 800d0e7c  FUN_800d0e7c ====

void FUN_800d0e7c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438a30,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804389f4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80438a34;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_804389f4;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (*(float *)(param_1 + 0x764) < fVar1)) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438a34;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438a38 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800d0fb0  FUN_800d0fb0 ====

void FUN_800d0fb0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  double dVar6;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ac));
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar3 = FLOAT_804389f4;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar5 = FUN_800668cc((double)FLOAT_80438a3c,param_1), uVar5 != 0)) {
    fVar3 = FLOAT_80438a20;
    fVar2 = FLOAT_80438a10;
    dVar6 = (double)FLOAT_80438a20;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_80438a28;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar4;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  if (FLOAT_80438a38 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800d10b4  FUN_800d10b4 ====

void FUN_800d10b4(int param_1)

{
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    zz_006ed8c_((double)FLOAT_80438a40,param_1);
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ac));
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      if (FLOAT_80438a38 < *(float *)(param_1 + 0x44)) {
        zz_00b22f4_(param_1);
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_80438a44 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 800d117c  FUN_800d117c ====

void FUN_800d117c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030de64)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d11cc  FUN_800d11cc ====

void FUN_800d11cc(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_80438a28;
  fVar1 = FLOAT_804389f4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  zz_0092dcc_(param_1,0);
  zz_004beb8_((double)FLOAT_80438a20,param_1,0xf,3,2,0xffffffff,0xffffffff);
  return;
}



// ==== 800d12b4  FUN_800d12b4 ====

void FUN_800d12b4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  zz_006d144_(param_1,0xc0);
  iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
  local_18 = *(float *)(iVar4 + 0x8e0);
  local_14 = *(undefined4 *)(iVar4 + 0x8f0);
  local_10 = *(undefined4 *)(iVar4 + 0x900);
  gnt4_PSVECSubtract_bl(&local_18,(float *)(param_1 + 0x518),&local_18);
  zz_006ec1c_(&local_18,&local_18);
  gnt4_PSQUATScale_bl((double)(FLOAT_80438a48 * *(float *)(param_1 + 0xb4)),&local_18,&local_18);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x518),&local_18,&local_18);
  zz_006e6c4_(param_1,0xc0,(short *)(param_1 + 0x54e),&local_18);
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80438a28 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_804389f0;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80438a28 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804389f4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80438a4c,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  return;
}



// ==== 800d1404  FUN_800d1404 ====

void FUN_800d1404(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804389f4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80438a28 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80438a28 * -dVar3);
  }
  return;
}



// ==== 800d14bc  FUN_800d14bc ====

void FUN_800d14bc(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804389f4;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80438a30,param_1);
  FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804389f0 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804389f0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800d15d0  FUN_800d15d0 ====

void FUN_800d15d0(int param_1)

{
  (*(code *)(&PTR_FUN_8030de74)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d160c  FUN_800d160c ====

void FUN_800d160c(int param_1)

{
  (*(code *)(&PTR_FUN_8030de88)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d1648  FUN_800d1648 ====

void FUN_800d1648(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_804389f4;
  *(float *)(param_1 + 0x50) = FLOAT_804389f4;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438a30,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438a20;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804389f4;
  return;
}



// ==== 800d1748  FUN_800d1748 ====

void FUN_800d1748(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  gnt4_PSQUATScale_bl((double)FLOAT_80438a30,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_80438a50;
    fVar3 = FLOAT_80438a44;
    fVar1 = FLOAT_804389f4;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
      fVar2 = FLOAT_80438a20;
      *(float *)(param_1 + 0x44) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar3;
      *(float *)(param_1 + 0x50) = fVar2;
    }
    iVar5 = zz_006dbe0_(param_1,2,1,1);
    if (iVar5 != 0) {
      if (*(short *)(param_1 + 1000) == 2) {
        zz_00a2684_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0xb) {
        zz_00a2684_(param_1,1);
      }
    }
  }
  dVar6 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438a38 < dVar6) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800d1868  FUN_800d1868 ====

void FUN_800d1868(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804389f0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (((iVar1 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438a44 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80438a44 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800d195c  zz_00d195c_ ====

bool zz_00d195c_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      *(code **)(puVar1 + 0xc) = FUN_800d1a74;
      *(code **)(puVar1 + 0x10c) = FUN_800d1c24;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800d1a74  FUN_800d1a74 ====

void FUN_800d1a74(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8030e308)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800d1ac8  FUN_800d1ac8 ====

void FUN_800d1ac8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_80438a58;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_8030e2b0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8030e2ac + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8030e2b4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8030e2b8 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8030e2bc + iVar3);
  *(undefined *)(param_9 + 0x89) = (&DAT_8030e2aa)[iVar3];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_8030e2a8 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_8030e2a8 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438a5c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00d1bf4_();
  return;
}



// ==== 800d1bf4  zz_00d1bf4_ ====

void zz_00d1bf4_(void)

{
  return;
}



// ==== 800d1c04  FUN_800d1c04 ====

void FUN_800d1c04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800d1c24  FUN_800d1c24 ====

void FUN_800d1c24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x174) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
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
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800d1cbc  zz_00d1cbc_ ====

int zz_00d1cbc_(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  for (; (*param_1 <= param_2 && (*param_1 != -1)); param_1 = param_1 + 2) {
    iVar1 = param_1[1];
  }
  return iVar1;
}



// ==== 800d1ce8  zz_00d1ce8_ ====

undefined4 zz_00d1ce8_(double param_1,int param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  
  if ((double)FLOAT_80438a60 < param_1) {
    param_1 = (double)FLOAT_80438a60;
  }
  do {
    pfVar1 = (float *)(param_2 + 8);
    puVar2 = (undefined4 *)(param_2 + 4);
    param_2 = param_2 + 8;
    if ((double)*pfVar1 <= param_1) {
      return *puVar2;
    }
  } while ((double)FLOAT_80438a64 <= (double)*pfVar1);
  return *puVar2;
}



// ==== 800d1d24  zz_00d1d24_ ====

void zz_00d1d24_(undefined4 *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (((uint)(byte)PTR_DAT_80433934[0x15db] & 1 << (int)*(char *)(param_2 + 0x3e4)) != 0) {
    *param_1 = 1;
    iVar2 = 0;
    param_1[1] = (int)*(char *)(param_2 + 0x88);
    param_1[4] = *(undefined4 *)(PTR_DAT_80433934 + param_1[1] * 0x3c + 0x114);
    param_1[5] = 0;
    for (iVar3 = 0; iVar3 < (char)PTR_DAT_80433934[0x53]; iVar3 = iVar3 + 1) {
      if ((int)(char)PTR_DAT_80433934[iVar2 + 0xf4] != param_1[1]) {
        param_1[5] = param_1[5] + *(int *)(PTR_DAT_80433934 + iVar2 + 0x114);
      }
      iVar2 = iVar2 + 0x3c;
    }
    param_1[2] = *(undefined4 *)(param_2 + 0x404);
    if ((*(int *)(param_2 + 0x408) == 0) || (*(int *)(param_2 + 0x404) == 0)) {
      param_1[3] = FLOAT_80438a64;
    }
    else {
      param_1[3] = (FLOAT_80438a60 *
                   (float)((double)CONCAT44(0x43300000,*(int *)(param_2 + 0x408)) - DOUBLE_80438a68)
                   ) / (float)((double)CONCAT44(0x43300000,*(int *)(param_2 + 0x404)) -
                              DOUBLE_80438a68);
    }
    iVar2 = *(int *)(param_2 + 0x40c) - *(int *)(param_2 + 0x410);
    param_1[7] = iVar2;
    if (iVar2 < 0) {
      param_1[7] = 0;
    }
    iVar2 = *(int *)(param_2 + 0x40c);
    param_1[6] = iVar2;
    if (iVar2 == 0) {
      param_1[8] = FLOAT_80438a64;
    }
    else {
      param_1[8] = (FLOAT_80438a60 *
                   (float)((double)CONCAT44(0x43300000,
                                            *(int *)(param_2 + 0x40c) - *(int *)(param_2 + 0x410)) -
                          DOUBLE_80438a68)) /
                   (float)((double)CONCAT44(0x43300000,
                                            *(int *)(param_2 + 0x40c) + *(int *)(param_2 + 0x414)) -
                          DOUBLE_80438a68);
    }
    param_1[9] = (uint)*(byte *)(param_2 + 0x434);
    param_1[10] = *(undefined4 *)(param_2 + 0x420);
    param_1[0xb] = (uint)*(byte *)(param_2 + 0x435);
    param_1[0xc] = *(undefined4 *)(param_2 + 0x424);
    param_1[0xd] = *(undefined4 *)(param_2 + 0x418);
    param_1[0xe] = *(undefined4 *)(param_2 + 0x41c);
    param_1[0xf] = (uint)*(byte *)(param_2 + 0x437);
    param_1[0x10] = *(undefined4 *)(param_2 + 0x430);
    param_1[0x11] = *(undefined4 *)(param_2 + 0x428);
    param_1[0x12] = *(undefined4 *)(param_2 + 0x42c);
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e318,param_1[2]);
    param_1[0x13] = iVar2;
    uVar1 = zz_00d1ce8_((double)(float)param_1[3],-0x7fcf1c80);
    param_1[0x14] = uVar1;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e3e8,param_1[7]);
    param_1[0x15] = iVar2;
    uVar1 = zz_00d1ce8_((double)(float)param_1[8],-0x7fcf1bb0);
    param_1[0x16] = uVar1;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e4b8,param_1[10]);
    param_1[0x18] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e6a8,param_1[0xc]);
    param_1[0x1a] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e710,param_1[0xd]);
    param_1[0x1b] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e780,param_1[0xe]);
    param_1[0x1c] = iVar2;
    uVar1 = DAT_80433b58;
    if (*(char *)(param_2 + 0x436) == '\0') {
      uVar1 = 0;
    }
    param_1[0x1d] = uVar1;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e7e8,param_1[0x10]);
    param_1[0x1f] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e850,param_1[0x11]);
    param_1[0x20] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e8b8,param_1[0x12]);
    param_1[0x21] = iVar2;
    iVar2 = zz_00d1cbc_((int *)&DAT_8030e920,(uint)*(ushort *)(param_2 + 0x4fc));
    param_1[0x22] = iVar2;
    param_1[0x23] = 0;
    param_1[0x23] = param_1[0x23] + param_1[0x18];
    param_1[0x23] = param_1[0x23] + param_1[0x1a];
    param_1[0x23] = param_1[0x23] + param_1[0x1d];
    *(int *)(PTR_DAT_80433934 + *(char *)(param_2 + 0x3e4) * 4 + 0x17e0) =
         *(int *)(PTR_DAT_80433934 + *(char *)(param_2 + 0x3e4) * 4 + 0x17e0) + param_1[0x23];
  }
  return;
}



// ==== 800d2094  zz_00d2094_ ====

void zz_00d2094_(void)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  piVar3 = &DAT_803ccda0;
  uVar5 = 0;
  iVar4 = 0;
  iVar6 = 3;
  fVar2 = FLOAT_80438a64;
  do {
    if ((*piVar3 != 0) && (99 < piVar3[2])) {
      fVar1 = (float)piVar3[3];
      if ((FLOAT_80438a70 <= fVar1) && ((fVar2 <= fVar1 && (fVar2 <= fVar1)))) {
        if (fVar1 != fVar2) {
          uVar5 = 0;
        }
        uVar5 = uVar5 | 1 << iVar4 & 0xffU;
        fVar2 = fVar1;
      }
    }
    if ((piVar3[0x25] != 0) && (99 < piVar3[0x27])) {
      fVar1 = (float)piVar3[0x28];
      if ((FLOAT_80438a70 <= fVar1) && ((fVar2 <= fVar1 && (fVar2 <= fVar1)))) {
        if (fVar1 != fVar2) {
          uVar5 = 0;
        }
        uVar5 = uVar5 | 1 << iVar4 + 1 & 0xffU;
        fVar2 = fVar1;
      }
    }
    piVar3 = piVar3 + 0x4a;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar4 = 0;
  while( true ) {
    if (uVar5 == 0) {
      return;
    }
    if (5 < iVar4) break;
    if ((uVar5 & 1 << iVar4) != 0) {
      (&DAT_803cce30)[iVar4 * 0x25] = (&DAT_803cce30)[iVar4 * 0x25] | 1;
      return;
    }
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 800d21dc  zz_00d21dc_ ====

void zz_00d21dc_(void)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  
  piVar3 = &DAT_803ccda0;
  iVar6 = 0x7fffffff;
  uVar7 = 0;
  iVar5 = 0;
  iVar8 = 3;
  fVar2 = FLOAT_80438a60;
  do {
    if (((((*piVar3 != 0) && (iVar4 = piVar3[2], 99 < iVar4)) &&
         (fVar1 = (float)piVar3[3], fVar1 < FLOAT_80438a70)) &&
        ((fVar1 <= fVar2 && ((piVar3[0x24] & 1U) == 0)))) && ((iVar4 < iVar6 && (fVar1 < fVar2)))) {
      if ((iVar4 != iVar6) || (fVar1 != fVar2)) {
        uVar7 = 0;
      }
      uVar7 = uVar7 | 1 << iVar5 & 0xffU;
      iVar6 = iVar4;
      fVar2 = fVar1;
    }
    if ((((piVar3[0x25] != 0) && (iVar4 = piVar3[0x27], 99 < iVar4)) &&
        (fVar1 = (float)piVar3[0x28], fVar1 < FLOAT_80438a70)) &&
       (((fVar1 <= fVar2 && ((piVar3[0x49] & 1U) == 0)) && ((iVar4 < iVar6 && (fVar1 < fVar2)))))) {
      if ((iVar4 != iVar6) || (fVar1 != fVar2)) {
        uVar7 = 0;
      }
      uVar7 = uVar7 | 1 << iVar5 + 1 & 0xffU;
      iVar6 = iVar4;
      fVar2 = fVar1;
    }
    piVar3 = piVar3 + 0x4a;
    iVar5 = iVar5 + 2;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  iVar6 = 0;
  while( true ) {
    if (uVar7 == 0) {
      return;
    }
    if (5 < iVar6) break;
    if ((uVar7 & 1 << iVar6) != 0) {
      (&DAT_803cce30)[iVar6 * 0x25] = (&DAT_803cce30)[iVar6 * 0x25] | 2;
      return;
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 800d235c  zz_00d235c_ ====

void zz_00d235c_(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  
  piVar4 = &DAT_803ccda0;
  uVar9 = 0;
  iVar7 = 0;
  iVar8 = 0;
  iVar6 = 0;
  iVar10 = 6;
  fVar2 = FLOAT_80438a60;
  do {
    if (*piVar4 != 0) {
      iVar5 = piVar4[0xc];
      if ((((*(int *)(PTR_DAT_80433934 + piVar4[1] * 0x3c + 0x114) / 2 <= iVar5) &&
           (iVar3 = piVar4[0xb], iVar7 <= iVar3)) && (iVar8 <= iVar5)) &&
         (fVar1 = (float)piVar4[8], fVar1 <= fVar2)) {
        if (((iVar7 != iVar3) || (fVar2 != fVar1)) || (iVar8 != iVar5)) {
          uVar9 = 0;
        }
        uVar9 = uVar9 | 1 << iVar6 & 0xffU;
        iVar7 = iVar3;
        iVar8 = iVar5;
        fVar2 = fVar1;
      }
    }
    piVar4 = piVar4 + 0x25;
    iVar6 = iVar6 + 1;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  iVar7 = 0;
  while( true ) {
    if (uVar9 == 0) {
      return;
    }
    if (5 < iVar7) break;
    if ((uVar9 & 1 << iVar7) != 0) {
      (&DAT_803cce30)[iVar7 * 0x25] = (&DAT_803cce30)[iVar7 * 0x25] | 0x20;
      return;
    }
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 800d2474  zz_00d2474_ ====

void zz_00d2474_(void)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  
  piVar3 = &DAT_803ccda0;
  uVar5 = 0;
  iVar4 = 0;
  iVar6 = 3;
  fVar2 = FLOAT_80438a64;
  do {
    if ((*piVar3 != 0) && (99 < piVar3[6])) {
      fVar1 = (float)piVar3[8];
      if ((FLOAT_80438a70 <= fVar1) && ((fVar2 <= fVar1 && ((piVar3[0x24] & 0x20U) == 0)))) {
        if (fVar1 != fVar2) {
          uVar5 = 0;
        }
        uVar5 = uVar5 | 1 << iVar4 & 0xffU;
        fVar2 = fVar1;
      }
    }
    if ((piVar3[0x25] != 0) && (99 < piVar3[0x2b])) {
      fVar1 = (float)piVar3[0x2d];
      if ((FLOAT_80438a70 <= fVar1) && ((fVar2 <= fVar1 && ((piVar3[0x49] & 0x20U) == 0)))) {
        if (fVar1 != fVar2) {
          uVar5 = 0;
        }
        uVar5 = uVar5 | 1 << iVar4 + 1 & 0xffU;
        fVar2 = fVar1;
      }
    }
    piVar3 = piVar3 + 0x4a;
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  iVar4 = 0;
  while( true ) {
    if (uVar5 == 0) {
      return;
    }
    if (5 < iVar4) break;
    if ((uVar5 & 1 << iVar4) != 0) {
      (&DAT_803cce30)[iVar4 * 0x25] = (&DAT_803cce30)[iVar4 * 0x25] | 4;
      return;
    }
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 800d25bc  zz_00d25bc_ ====

void zz_00d25bc_(void)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  
  piVar3 = &DAT_803ccda0;
  iVar6 = 0x7fffffff;
  uVar7 = 0;
  iVar5 = 0;
  iVar8 = 3;
  fVar2 = FLOAT_80438a60;
  do {
    if ((((*piVar3 != 0) && (99 < piVar3[6])) && (fVar1 = (float)piVar3[8], fVar1 < FLOAT_80438a70))
       && ((fVar1 <= fVar2 && (iVar4 = piVar3[7], iVar4 <= iVar6)))) {
      if ((fVar1 != fVar2) || (iVar4 != iVar6)) {
        uVar7 = 0;
      }
      uVar7 = uVar7 | 1 << iVar5 & 0xffU;
      iVar6 = iVar4;
      fVar2 = fVar1;
    }
    if (((piVar3[0x25] != 0) && (99 < piVar3[0x2b])) &&
       ((fVar1 = (float)piVar3[0x2d], fVar1 < FLOAT_80438a70 &&
        ((fVar1 <= fVar2 && (iVar4 = piVar3[0x2c], iVar4 <= iVar6)))))) {
      if ((fVar1 != fVar2) || (iVar4 != iVar6)) {
        uVar7 = 0;
      }
      uVar7 = uVar7 | 1 << iVar5 + 1 & 0xffU;
      iVar6 = iVar4;
      fVar2 = fVar1;
    }
    piVar3 = piVar3 + 0x4a;
    iVar5 = iVar5 + 2;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  iVar6 = 0;
  while( true ) {
    if (uVar7 == 0) {
      return;
    }
    if (5 < iVar6) break;
    if ((uVar7 & 1 << iVar6) != 0) {
      (&DAT_803cce30)[iVar6 * 0x25] = (&DAT_803cce30)[iVar6 * 0x25] | 8;
      return;
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 800d271c  zz_00d271c_ ====

void zz_00d271c_(void)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  
  piVar5 = &DAT_803ccda0;
  uVar10 = 0;
  iVar9 = 0;
  iVar7 = 0;
  iVar8 = 0;
  fVar2 = FLOAT_80438a64;
  do {
    if (*piVar5 != 0) {
      iVar6 = 0;
      iVar3 = (int)(char)PTR_DAT_80433934[0x53];
      puVar4 = PTR_DAT_80433934;
      if (0 < iVar3) {
        do {
          if (piVar5[1] != (int)(char)puVar4[0xf4]) {
            iVar6 = iVar6 + *(int *)(puVar4 + 0x114);
          }
          puVar4 = puVar4 + 0x3c;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      iVar3 = piVar5[10];
      if ((((iVar6 / 2 <= iVar3) && (iVar6 = piVar5[9], iVar9 <= iVar6)) && (iVar7 <= iVar3)) &&
         (fVar1 = (float)piVar5[3], fVar2 <= fVar1)) {
        if (((iVar6 != iVar9) || (iVar3 != iVar7)) || (fVar1 != fVar2)) {
          uVar10 = 0;
        }
        uVar10 = uVar10 | 1 << iVar8 & 0xffU;
        iVar7 = iVar3;
        iVar9 = iVar6;
        fVar2 = fVar1;
      }
    }
    iVar8 = iVar8 + 1;
    piVar5 = piVar5 + 0x25;
  } while (iVar8 < 6);
  iVar7 = 0;
  while( true ) {
    if (uVar10 == 0) {
      return;
    }
    if (5 < iVar7) break;
    if ((uVar10 & 1 << iVar7) != 0) {
      (&DAT_803cce30)[iVar7 * 0x25] = (&DAT_803cce30)[iVar7 * 0x25] | 0x10;
      return;
    }
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 800d285c  zz_00d285c_ ====

void zz_00d285c_(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  ushort uVar9;
  uint uVar10;
  int iVar11;
  char *unaff_r28;
  int *piVar12;
  uint uVar13;
  undefined8 local_28;
  double local_20;
  
  PTR_DAT_80433934[0xf0] = 0;
  cVar1 = PTR_DAT_80433930[0x29];
  if (cVar1 == '\0') {
    unaff_r28 = &DAT_80433b5c;
  }
  else if (cVar1 == '\x01') {
    unaff_r28 = &DAT_8030e990;
  }
  else if (cVar1 == '\x02') {
    unaff_r28 = &DAT_8030e9a0;
  }
  while( true ) {
    if (*unaff_r28 < '\0') break;
    zz_00d309c_(unaff_r28);
    unaff_r28 = unaff_r28 + 4;
  }
  iVar11 = 0;
  piVar12 = &DAT_803c4e84;
  piVar4 = &DAT_803ccda0;
  do {
    iVar5 = *piVar12;
    *piVar4 = 0;
    piVar4[0x24] = 0;
    if (iVar5 != 0) {
      zz_00d1d24_(piVar4,iVar5);
    }
    iVar11 = iVar11 + 1;
    piVar12 = piVar12 + 1;
    piVar4 = piVar4 + 0x25;
  } while (iVar11 < 6);
  zz_00d2094_();
  zz_00d21dc_();
  zz_00d235c_();
  zz_00d2474_();
  zz_00d25bc_();
  zz_00d271c_();
  if ((PTR_DAT_80433934[0x51] == '\x02') || (PTR_DAT_80433934[0x51] == '\x01')) {
    iVar5 = 0;
    iVar11 = (int)(char)PTR_DAT_80433934[0x53];
    if (0 < iVar11) {
      if ((8 < iVar11) && (uVar13 = iVar11 - 1U >> 3, 0 < iVar11 + -8)) {
        do {
          iVar5 = iVar5 + 8;
          uVar13 = uVar13 - 1;
        } while (uVar13 != 0);
      }
      iVar3 = iVar11 - iVar5;
      if (iVar5 < iVar11) {
        do {
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    uVar13 = 0;
    iVar5 = 0;
    iVar11 = 0;
    piVar4 = &DAT_803ccda0;
    do {
      if (*piVar4 != 0) {
        uVar10 = 0;
        iVar3 = 0;
        iVar6 = (int)(char)PTR_DAT_80433934[0x53];
        puVar8 = PTR_DAT_80433934;
        if (0 < iVar6) {
          do {
            if (piVar4[1] != (int)(char)puVar8[0xf4]) {
              uVar10 = uVar10 + *(int *)(puVar8 + 0x114);
            }
            if (piVar4[1] == (int)(char)puVar8[0xf4]) {
              iVar3 = iVar3 + *(int *)(puVar8 + 0x114);
            }
            puVar8 = puVar8 + 0x3c;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
        }
        if (((int)(char)PTR_DAT_80433934[0x1f] == 1 << piVar4[1]) && (1999 < piVar4[0xd])) {
          local_28 = (double)CONCAT44(0x43300000,uVar10 ^ 0x80000000);
          if ((int)((float)(local_28 - DOUBLE_80438a80) * FLOAT_80438a74) <= piVar4[10]) {
            local_20 = (double)(CONCAT44(0x43300000,iVar3) ^ 0x80000000);
            if ((piVar4[0xc] < (int)((float)(local_20 - DOUBLE_80438a80) * FLOAT_80438a78)) &&
               (piVar4[0xe] < 5000)) {
              iVar5 = iVar5 + 1;
              uVar13 = uVar13 | 1 << iVar11 & 0xffU;
            }
          }
        }
      }
      iVar11 = iVar11 + 1;
      piVar4 = piVar4 + 0x25;
    } while (iVar11 < 6);
    piVar4 = &DAT_803ccda0;
    for (iVar11 = 0; iVar11 < 6; iVar11 = iVar11 + 1) {
      if (iVar5 < 1) break;
      if ((uVar13 & 1 << iVar11) != 0) {
        piVar4[0x24] = piVar4[0x24] | 0x40;
      }
      piVar4 = piVar4 + 0x25;
    }
    uVar13 = 0;
    iVar5 = 0;
    iVar11 = 0;
    iVar3 = 2;
    piVar4 = &DAT_803ccda0;
    do {
      if ((((*piVar4 != 0) && (piVar4[0xd] < 1000)) && (piVar4[2] < 100)) && (piVar4[6] < 0x32)) {
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 & 0xffU;
      }
      if (((piVar4[0x25] != 0) && (piVar4[0x32] < 1000)) &&
         ((piVar4[0x27] < 100 && (piVar4[0x2b] < 0x32)))) {
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 + 1 & 0xffU;
      }
      if (((piVar4[0x4a] != 0) && (piVar4[0x57] < 1000)) &&
         ((piVar4[0x4c] < 100 && (piVar4[0x50] < 0x32)))) {
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 + 2 & 0xffU;
      }
      piVar4 = piVar4 + 0x6f;
      iVar11 = iVar11 + 3;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    piVar4 = &DAT_803ccda0;
    for (iVar11 = 0; iVar11 < 6; iVar11 = iVar11 + 1) {
      if (iVar5 < 1) break;
      if ((uVar13 & 1 << iVar11) != 0) {
        piVar4[0x24] = piVar4[0x24] | 0x80;
      }
      piVar4 = piVar4 + 0x25;
    }
    uVar13 = 0;
    iVar5 = 0;
    iVar11 = 0;
    iVar3 = 2;
    piVar4 = &DAT_803ccda0;
    do {
      if (((*piVar4 != 0) && (iVar6 = piVar4[0x12], 999 < iVar6)) && (-1 < iVar6)) {
        if (iVar6 != 0) {
          uVar13 = 0;
          iVar5 = 0;
        }
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 & 0xffU;
      }
      if (((piVar4[0x25] != 0) && (iVar6 = piVar4[0x37], 999 < iVar6)) && (-1 < iVar6)) {
        if (iVar6 != 0) {
          uVar13 = 0;
          iVar5 = 0;
        }
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 + 1 & 0xffU;
      }
      if (((piVar4[0x4a] != 0) && (iVar6 = piVar4[0x5c], 999 < iVar6)) && (-1 < iVar6)) {
        if (iVar6 != 0) {
          uVar13 = 0;
          iVar5 = 0;
        }
        iVar5 = iVar5 + 1;
        uVar13 = uVar13 | 1 << iVar11 + 2 & 0xffU;
      }
      piVar4 = piVar4 + 0x6f;
      iVar11 = iVar11 + 3;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    piVar4 = &DAT_803ccda0;
    for (iVar11 = 0; iVar11 < 6; iVar11 = iVar11 + 1) {
      if (iVar5 < 1) break;
      if ((uVar13 & 1 << iVar11) != 0) {
        piVar4[0x24] = piVar4[0x24] | 0x100;
      }
      piVar4 = piVar4 + 0x25;
    }
    iVar11 = 0;
    piVar4 = &DAT_803ccda0;
    do {
      if (*piVar4 != 0) {
        if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << piVar4[1]) {
          uVar9 = 0;
          iVar5 = -1;
          iVar6 = (int)(char)PTR_DAT_80433934[0x53];
          iVar7 = 0;
          puVar8 = PTR_DAT_80433934;
          iVar3 = iVar6;
          if (0 < iVar6) {
            do {
              if (uVar9 <= *(ushort *)(puVar8 + 0x12a)) {
                iVar5 = iVar7;
                uVar9 = *(ushort *)(puVar8 + 0x12a);
              }
              puVar8 = puVar8 + 0x3c;
              iVar7 = iVar7 + 1;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
          }
          if (piVar4[1] == iVar5) {
            iVar5 = 0;
            puVar8 = PTR_DAT_80433934;
            if (0 < iVar6) {
              do {
                if (piVar4[1] == (int)(char)puVar8[0xf4]) {
                  iVar5 = *(int *)(puVar8 + 0x114);
                  break;
                }
                puVar8 = puVar8 + 0x3c;
                iVar6 = iVar6 + -1;
              } while (iVar6 != 0);
            }
            iVar5 = iVar5 / 2;
            bVar2 = false;
            iVar3 = 2;
            piVar12 = &DAT_803ccda0;
            do {
              if (((*piVar12 != 0) && (piVar12[1] == piVar4[1])) &&
                 ((199 < piVar12[0x12] || (iVar5 < piVar12[0xc])))) {
                bVar2 = true;
                break;
              }
              if (((piVar12[0x25] != 0) && (piVar12[0x26] == piVar4[1])) &&
                 ((199 < piVar12[0x37] || (iVar5 < piVar12[0x31])))) {
                bVar2 = true;
                break;
              }
              if (((piVar12[0x4a] != 0) && (piVar12[0x4b] == piVar4[1])) &&
                 ((199 < piVar12[0x5c] || (iVar5 < piVar12[0x56])))) {
                bVar2 = true;
                break;
              }
              piVar12 = piVar12 + 0x6f;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
            if (!bVar2) {
              piVar4[0x24] = piVar4[0x24] | 0x200;
            }
          }
        }
      }
      iVar11 = iVar11 + 1;
      piVar4 = piVar4 + 0x25;
    } while (iVar11 < 6);
    iVar11 = 0;
    piVar4 = &DAT_803ccda0;
    do {
      if (*piVar4 != 0) {
        if ((int)(char)PTR_DAT_80433934[0x1f] != 1 << piVar4[1]) {
          uVar13 = 0x7fffffff;
          iVar5 = -1;
          iVar3 = (int)(char)PTR_DAT_80433934[0x53];
          iVar6 = 0;
          puVar8 = PTR_DAT_80433934;
          if (0 < iVar3) {
            do {
              if (*(ushort *)(puVar8 + 0x12a) <= uVar13) {
                uVar13 = (uint)*(ushort *)(puVar8 + 0x12a);
                iVar5 = iVar6;
              }
              puVar8 = puVar8 + 0x3c;
              iVar6 = iVar6 + 1;
              iVar3 = iVar3 + -1;
            } while (iVar3 != 0);
          }
          if (piVar4[1] == iVar5) {
            bVar2 = false;
            iVar5 = 2;
            piVar12 = &DAT_803ccda0;
            do {
              if (((*piVar12 != 0) && (piVar12[1] == piVar4[1])) && (piVar12[0x12] < 200)) {
                bVar2 = true;
                break;
              }
              if (((piVar12[0x25] != 0) && (piVar12[0x26] == piVar4[1])) && (piVar12[0x37] < 200)) {
                bVar2 = true;
                break;
              }
              if (((piVar12[0x4a] != 0) && (piVar12[0x4b] == piVar4[1])) && (piVar12[0x5c] < 200)) {
                bVar2 = true;
                break;
              }
              piVar12 = piVar12 + 0x6f;
              iVar5 = iVar5 + -1;
            } while (iVar5 != 0);
            if (!bVar2) {
              piVar4[0x24] = piVar4[0x24] | 0x400;
            }
          }
        }
      }
      iVar11 = iVar11 + 1;
      piVar4 = piVar4 + 0x25;
    } while (iVar11 < 6);
  }
  return;
}



// ==== 800d309c  zz_00d309c_ ====

undefined1 * zz_00d309c_(undefined1 *param_1)

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
  puVar2 = zz_008893c_(2,0x38,1,iVar1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x83] = 0x14;
    puVar5 = (undefined4 *)(puVar2 + 0x144);
    iVar1 = 0;
    puVar2[0x11] = *param_1;
    puVar2[0x12] = param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_800d317c;
    *(code **)(puVar2 + 0x10c) = FUN_800d6238;
    puVar2[0x169] = param_1[3];
    do {
      if (iVar4 == 0) {
        *puVar5 = 0;
      }
      else {
        uVar3 = zz_0006d4c_();
        *puVar5 = uVar3;
        iVar4 = iVar4 + -1;
      }
      iVar1 = iVar1 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar1 < 8);
  }
  return puVar2;
}



// ==== 800d317c  FUN_800d317c ====

void FUN_800d317c(int param_1)

{
  (*(code *)(&PTR_FUN_8030ea2c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800d31b8  FUN_800d31b8 ====

void FUN_800d31b8(int param_1)

{
  char cVar1;
  
  cVar1 = PTR_DAT_80433930[0x29];
  if (cVar1 == '\0') {
    (*(code *)(&PTR_FUN_8030ea3c)[*(char *)(param_1 + 0x11)])();
  }
  else if (cVar1 == '\x01') {
    (*(code *)(&PTR_FUN_8030ea74)[*(char *)(param_1 + 0x11)])();
  }
  else if (cVar1 == '\x02') {
    (*(code *)(&PTR_FUN_8030eaac)[*(char *)(param_1 + 0x11)])();
  }
  return;
}



// ==== 800d3260  FUN_800d3260 ====

void FUN_800d3260(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_r4;
  int iVar5;
  undefined4 extraout_r4_00;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  undefined8 local_30;
  
  puVar7 = &DAT_803ccda0;
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar11 = *(int *)(param_1 + 0x90);
  iVar8 = (int)*(char *)(iVar11 + 0x3e4);
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  iVar3 = iVar8 * 0x94;
  zz_0089100_(param_1,0x20,1);
  *(undefined1 *)(param_1 + 0x84) = 0x21;
  if (PTR_DAT_80433930[0x29] == '\x01') {
    dVar16 = (double)FLOAT_80438a8c;
    *(float *)(param_1 + 0x3c) =
         (float)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(char *)(param_1 + 0x13) ^
                                                           0x80000000) - DOUBLE_80438a80) +
                (double)FLOAT_80438a88);
  }
  else {
    dVar16 = (double)FLOAT_80438a90;
    *(float *)(param_1 + 0x3c) =
         (float)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(char *)(param_1 + 0x13) ^
                                                           0x80000000) - DOUBLE_80438a80) +
                (double)FLOAT_80438a88);
  }
  fVar2 = FLOAT_80438a94;
  *(float *)(param_1 + 0x60) = FLOAT_80438a94;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  fVar2 = FLOAT_80438a64;
  if (PTR_DAT_80433930[0x29] == '\0') {
    if (*(char *)(param_1 + 0x168) == '\0') {
      *(float *)(param_1 + 100) = FLOAT_80438a98;
    }
    else {
      *(float *)(param_1 + 100) = FLOAT_80438a9c;
    }
    *(float *)(param_1 + 100) = FLOAT_80438a64;
  }
  else {
    *(float *)(param_1 + 0x5c) = FLOAT_80438aa0;
    *(float *)(param_1 + 100) = fVar2;
  }
  fVar2 = FLOAT_80438a64;
  dVar15 = (double)*(float *)(param_1 + 0x3c);
  dVar13 = (double)FLOAT_80438aa4;
  *(float *)(param_1 + 0x68) = (float)(dVar15 - dVar13);
  *(float *)(param_1 + 0x6c) = fVar2;
  *(short *)(param_1 + 0x1c) = (short)*(char *)(param_1 + 0x12) << 2;
  uVar14 = zz_0006fb4_((double)(float)(dVar15 - dVar13),dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,
                       DAT_804361fc,*(int *)(param_1 + 0xe0),1,puVar7,iVar8,in_r8,in_r9,in_r10);
  zz_0006fb4_(uVar14,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
              *(int *)(param_1 + 0xe4),
              (int)*(short *)(&DAT_8030e9d8 + *(char *)(param_1 + 0x12) * 2),puVar7,iVar8,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_1 + 0x16c) = 0xff;
  uVar4 = 0;
  dVar13 = (double)FLOAT_80438a64;
  iVar10 = 0;
  *(undefined1 *)(param_1 + 0x16e) = 0;
  switch(*(undefined1 *)(param_1 + 0x12)) {
  case 0:
    uVar4 = *(uint *)(iVar11 + 0x404);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    break;
  case 1:
    fVar2 = FLOAT_80438a64;
    if ((*(int *)(iVar11 + 0x408) != 0) && (*(int *)(iVar11 + 0x404) != 0)) {
      dVar16 = (double)FLOAT_80438a60;
      local_30 = (double)CONCAT44(0x43300000,*(int *)(iVar11 + 0x404));
      dVar15 = DOUBLE_80438a68;
      fVar2 = (float)(dVar16 * (double)(float)((double)CONCAT44(0x43300000,*(int *)(iVar11 + 0x408))
                                              - DOUBLE_80438a68)) /
              (float)(local_30 - DOUBLE_80438a68);
    }
    dVar13 = (double)fVar2;
    *(undefined1 *)(param_1 + 0x16c) = 1;
    *(undefined1 *)(param_1 + 0x16d) = 2;
    break;
  case 2:
    puVar7 = *(undefined4 **)(iVar11 + 0x40c);
    if (puVar7 != (undefined4 *)0x0) {
      local_30 = (double)CONCAT44(0x43300000,(int)puVar7 - *(int *)(iVar11 + 0x410));
      dVar16 = (double)FLOAT_80438a60;
      dVar13 = (double)((float)(dVar16 * (double)(float)(local_30 - DOUBLE_80438a68)) /
                       (float)((double)CONCAT44(0x43300000,(int)puVar7 + *(int *)(iVar11 + 0x414)) -
                              DOUBLE_80438a68));
      dVar15 = DOUBLE_80438a68;
    }
    *(undefined1 *)(param_1 + 0x16c) = 1;
    *(undefined1 *)(param_1 + 0x16d) = 2;
    break;
  case 3:
    uVar4 = (uint)*(byte *)(iVar11 + 0x434);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    break;
  case 4:
    uVar4 = *(uint *)(iVar11 + 0x420);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    iVar10 = *(int *)(&DAT_803cce00 + iVar3);
    *(undefined1 *)(param_1 + 0x16e) = 1;
    break;
  case 5:
    uVar4 = (uint)*(byte *)(iVar11 + 0x435);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    break;
  case 6:
    uVar4 = *(uint *)(iVar11 + 0x424);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    iVar10 = *(int *)(&DAT_803cce08 + iVar3);
    *(undefined1 *)(param_1 + 0x16e) = 1;
    break;
  case 7:
    uVar4 = (uint)*(byte *)(iVar11 + 0x437);
    *(undefined1 *)(param_1 + 0x16c) = 0;
    *(undefined1 *)(param_1 + 0x16d) = 5;
    break;
  case 8:
    iVar10 = *(int *)(&DAT_803cce14 + iVar3);
    *(undefined1 *)(param_1 + 0x16e) = 1;
    break;
  case 9:
    iVar10 = *(int *)(&DAT_803cce2c + iVar3);
    *(undefined1 *)(param_1 + 0x16e) = 1;
    break;
  default:
    *(undefined1 *)(param_1 + 0x16c) = 0xff;
    uVar4 = 0;
    dVar13 = (double)FLOAT_80438a64;
    iVar10 = 0;
    *(undefined1 *)(param_1 + 0x16e) = 0;
  }
  if (-1 < *(char *)(param_1 + 0x16c)) {
    if (*(char *)(param_1 + 0x16c) == '\0') {
      iVar3 = ((int)uVar4 >> 0x1f ^ uVar4) - ((int)uVar4 >> 0x1f);
      if (99999 < iVar3) {
        iVar3 = 99999;
      }
      iVar11 = 4;
    }
    else {
      iVar11 = 2;
      iVar3 = (int)((double)FLOAT_80438a60 * dVar13);
    }
    uVar4 = 10000;
    iVar9 = 0;
    iVar12 = param_1;
    do {
      if ((iVar3 / (int)uVar4 == 0) && (0 < iVar11)) {
        *(undefined4 *)(*(int *)(iVar12 + 0xe8) + 0x14) = 0xffffffff;
      }
      else {
        iVar11 = -1;
        pfVar6 = (float *)0x1e;
        zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                    *(int *)(iVar12 + 0xe8),0x1e,puVar7,iVar8,in_r8,in_r9,in_r10);
        local_30 = (double)CONCAT44(0x43300000,iVar3 / (int)uVar4);
        uVar14 = zz_00086b8_((double)(float)(local_30 - DOUBLE_80438a68),dVar15,dVar16,in_f4,in_f5,
                             in_f6,in_f7,in_f8,DAT_804361fc,*(int *)(iVar12 + 0xe8),pfVar6,puVar7,
                             iVar8,in_r8,in_r9,in_r10);
        dVar13 = (double)zz_0007c30_(uVar14,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,
                                     *(int *)(iVar12 + 0xe8),extraout_r4,pfVar6,puVar7,iVar8,in_r8,
                                     in_r9,in_r10);
      }
      iVar9 = iVar9 + 1;
      iVar12 = iVar12 + 4;
      iVar11 = iVar11 + -1;
      iVar5 = (iVar3 / (int)uVar4) * uVar4;
      uVar4 = uVar4 / 10;
      iVar3 = iVar3 - iVar5;
    } while (iVar9 < 5);
    sVar1 = *(short *)(&DAT_8030e9ec + *(char *)(param_1 + 0x16d) * 2);
    *(int *)(*(int *)(param_1 + 0xfc) + 0x14) = (int)sVar1;
    if (0 < sVar1) {
      dVar13 = (double)zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                                   *(int *)(param_1 + 0xfc),
                                   *(int *)(*(int *)(param_1 + 0xfc) + 0x14),puVar7,iVar8,in_r8,
                                   in_r9,in_r10);
    }
    if (*(char *)(param_1 + 0x16c) == '\x01') {
      dVar13 = (double)zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                                   *(int *)(param_1 + 0x144),0x1d,puVar7,iVar8,in_r8,in_r9,in_r10);
    }
  }
  if (*(char *)(param_1 + 0x16e) != '\0') {
    if (99999 < iVar10) {
      iVar10 = 99999;
    }
    if (iVar10 < 0) {
      iVar10 = -iVar10;
      *(undefined1 *)(param_1 + 0x16e) = 0xff;
    }
    iVar11 = param_1 + 0x144;
    iVar3 = 4;
    uVar4 = 10000;
    iVar12 = 0;
    do {
      iVar9 = iVar10 / (int)uVar4;
      iVar5 = *(int *)(iVar11 + 4);
      if ((iVar9 == 0) && (0 < iVar3)) {
        *(undefined4 *)(iVar5 + 0x14) = 0xffffffff;
      }
      else {
        iVar3 = -1;
        pfVar6 = (float *)0x1e;
        zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,iVar5,0x1e,
                    puVar7,iVar8,in_r8,in_r9,in_r10);
        if (*(char *)(param_1 + 0x16e) < '\0') {
          local_30 = (double)CONCAT44(0x43300000,iVar9);
          dVar15 = DOUBLE_80438a68;
          iVar9 = gnt4___cvt_fp2unsigned_bl
                            ((double)((float)(local_30 - DOUBLE_80438a68) + FLOAT_80438aa8));
        }
        uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,iVar9) - DOUBLE_80438a68),
                             dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,iVar5,pfVar6,
                             puVar7,iVar8,in_r8,in_r9,in_r10);
        dVar13 = (double)zz_0007c30_(uVar14,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,iVar5,
                                     extraout_r4_00,pfVar6,puVar7,iVar8,in_r8,in_r9,in_r10);
      }
      iVar12 = iVar12 + 1;
      iVar11 = iVar11 + 4;
      iVar3 = iVar3 + -1;
      iVar9 = (iVar10 / (int)uVar4) * uVar4;
      uVar4 = uVar4 / 10;
      iVar10 = iVar10 - iVar9;
    } while (iVar12 < 5);
    iVar3 = (int)DAT_8030e9f4;
    *(int *)(*(int *)(param_1 + 0x15c) + 0x14) = iVar3;
    if (0 < iVar3) {
      dVar13 = (double)zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                                   *(int *)(param_1 + 0x15c),
                                   *(int *)(*(int *)(param_1 + 0x15c) + 0x14),puVar7,iVar8,in_r8,
                                   in_r9,in_r10);
    }
    iVar3 = (int)DAT_8030e9f8;
    *(int *)(*(int *)(param_1 + 0x160) + 0x14) = iVar3;
    if (0 < iVar3) {
      zz_0006fb4_(dVar13,dVar15,dVar16,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                  *(int *)(param_1 + 0x160),*(int *)(*(int *)(param_1 + 0x160) + 0x14),puVar7,iVar8,
                  in_r8,in_r9,in_r10);
    }
  }
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x169) + '\x11';
  return;
}



// ==== 800d3914  FUN_800d3914 ====

void FUN_800d3914(int param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  char *pcVar7;
  
  iVar6 = 0;
  *(undefined1 *)(param_1 + 0x18) = 1;
  bVar1 = PTR_DAT_80433930[2];
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) == 0) {
      if ((bVar1 & 4) == 0) {
        if ((bVar1 & 8) == 0) {
          if ((bVar1 & 0x10) == 0) {
            if ((bVar1 & 0x20) != 0) {
              iVar6 = 5;
            }
          }
          else {
            iVar6 = 4;
          }
        }
        else {
          iVar6 = 3;
        }
      }
      else {
        iVar6 = 2;
      }
    }
    else {
      iVar6 = 1;
    }
  }
  else {
    iVar6 = 0;
  }
  iVar6 = (&DAT_803c4e84)[iVar6];
  *(int *)(param_1 + 0x90) = iVar6;
  *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(iVar6 + 0x3e4);
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  fVar2 = FLOAT_80438a64;
  *(undefined1 *)(param_1 + 0x84) = 1;
  fVar3 = FLOAT_80438ab0;
  *(float *)(param_1 + 100) = fVar2;
  fVar2 = FLOAT_80438ab4;
  *(float *)(param_1 + 0x3c) = fVar3;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar2;
  if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)*(char *)(iVar6 + 0x88)) {
    *(undefined1 *)(param_1 + 0x168) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x168) = 1;
  }
  fVar2 = FLOAT_80438a64;
  iVar6 = 0;
  *(undefined2 *)(param_1 + 0x16c) = 0;
  fVar3 = FLOAT_80438a90;
  *(undefined2 *)(param_1 + 0x16e) = 0;
  *(undefined1 *)(param_1 + 0x17d) = 0;
  *(undefined1 *)(param_1 + 0x17e) = 0;
  *(float *)(param_1 + 0x164) = fVar2;
  *(float *)(param_1 + 0x178) = fVar3;
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(undefined1 *)(param_1 + 0x180) = 0;
  PTR_DAT_80433934[0xef] = 0;
  if (PTR_DAT_80433930[0x32] == '\0') {
    pcVar7 = (char *)0x0;
    iVar4 = (int)(char)PTR_DAT_80433934[0x53];
    puVar5 = PTR_DAT_80433934;
    if (0 < iVar4) {
      do {
        if (puVar5[0xf6] == '\0') {
          pcVar7 = PTR_DAT_80433934 + iVar6 * 0x3c + 0xf4;
          break;
        }
        puVar5 = puVar5 + 0x3c;
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    *(undefined1 *)(param_1 + 0x17f) = 1;
    if (pcVar7 != (char *)0x0) {
      iVar6 = 2;
      puVar5 = PTR_DAT_80433934;
      do {
        if (((puVar5[0xcb] == *pcVar7) && ('\0' < (char)puVar5[0x20])) &&
           ((char)puVar5[0x20] < '\x0e')) {
          *(undefined1 *)(param_1 + 0x17f) = 2;
          return;
        }
        if (((puVar5[0xcc] == *pcVar7) && ('\0' < (char)puVar5[0x21])) &&
           ((char)puVar5[0x21] < '\x0e')) {
          *(undefined1 *)(param_1 + 0x17f) = 2;
          return;
        }
        if (((puVar5[0xcd] == *pcVar7) && ('\0' < (char)puVar5[0x22])) &&
           ((char)puVar5[0x22] < '\x0e')) {
          *(undefined1 *)(param_1 + 0x17f) = 2;
          return;
        }
        puVar5 = puVar5 + 3;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x17f) = 0;
  }
  return;
}



// ==== 800d3be4  FUN_800d3be4 ====

void FUN_800d3be4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar3 = (&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x169) + 0xc0]];
  *(int *)(param_1 + 0x90) = iVar3;
  *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(iVar3 + 0x3e4);
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  fVar1 = FLOAT_80438a64;
  *(undefined1 *)(param_1 + 0x84) = 1;
  fVar2 = FLOAT_80438ab0;
  *(float *)(param_1 + 100) = fVar1;
  fVar1 = FLOAT_80438ab4;
  *(float *)(param_1 + 0x3c) = fVar2;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar1;
  if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)*(char *)(iVar3 + 0x88)) {
    *(undefined1 *)(param_1 + 0x168) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x168) = 0;
  }
  fVar2 = FLOAT_80438a8c;
  *(undefined2 *)(param_1 + 0x16c) = 0;
  fVar1 = FLOAT_80438a64;
  *(undefined2 *)(param_1 + 0x16e) = 0;
  *(undefined1 *)(param_1 + 0x17d) = 0;
  *(undefined1 *)(param_1 + 0x17e) = 0;
  *(float *)(param_1 + 0x178) = fVar2;
  *(float *)(param_1 + 0x164) = fVar1;
  *(undefined4 *)(param_1 + 0x170) = 0;
  *(undefined1 *)(param_1 + 0x180) = 0;
  PTR_DAT_80433934[0xef] = 0;
  return;
}



// ==== 800d3cf0  FUN_800d3cf0 ====

void FUN_800d3cf0(int param_1)

{
  float fVar1;
  float fVar2;
  char *pcVar3;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  pcVar3 = (char *)(&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x169) + 0xc0]];
  if (*pcVar3 == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(char **)(param_1 + 0x90) = pcVar3;
    *(char *)(param_1 + 0x96) = pcVar3[0x3e4];
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0x20,1);
    fVar1 = FLOAT_80438a64;
    *(undefined1 *)(param_1 + 0x84) = 1;
    fVar2 = FLOAT_80438ab0;
    *(float *)(param_1 + 100) = fVar1;
    fVar1 = FLOAT_80438ab4;
    *(float *)(param_1 + 0x3c) = fVar2;
    *(float *)(param_1 + 0x68) = fVar2;
    *(float *)(param_1 + 0x6c) = fVar1;
    if ((int)(char)PTR_DAT_80433934[0x1f] == 1 << (int)pcVar3[0x88]) {
      *(undefined1 *)(param_1 + 0x168) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x168) = 0;
    }
    fVar2 = FLOAT_80438ab8;
    *(undefined2 *)(param_1 + 0x16c) = 0;
    fVar1 = FLOAT_80438a64;
    *(undefined2 *)(param_1 + 0x16e) = 0;
    *(undefined1 *)(param_1 + 0x17d) = 0;
    *(undefined1 *)(param_1 + 0x17e) = 0;
    *(float *)(param_1 + 0x178) = fVar2;
    *(float *)(param_1 + 0x164) = fVar1;
    *(undefined4 *)(param_1 + 0x170) = 0;
    *(undefined1 *)(param_1 + 0x180) = 0;
    PTR_DAT_80433934[0xef] = 0;
  }
  return;
}



// ==== 800d3e14  FUN_800d3e14 ====

void FUN_800d3e14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  double dVar6;
  undefined8 uVar7;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = *(char *)(param_9 + 0x12) * 0x18;
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(undefined1 *)(param_9 + 0x13) = 1;
  }
  else {
    *(undefined1 *)(param_9 + 0x13) = 0;
  }
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar2 = FLOAT_80438a94;
  dVar6 = (double)FLOAT_80438a94;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  fVar1 = FLOAT_80438a64;
  uVar4 = *(undefined4 *)(&DAT_8030ea0c + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8030ea08 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar4;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8030ea10 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8030ea00 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8030ea04 + iVar3);
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(char *)(param_9 + 0x17d) = (char)*(undefined2 *)(&DAT_8030e9fe + iVar3);
  *(undefined1 *)(param_9 + 0x17c) = 0;
  *(float *)(param_9 + 0x178) = fVar1;
  zz_00d60b4_((float *)(param_9 + 0x16c));
  pfVar5 = (float *)(int)(char)(&DAT_8030e9fc)[iVar3];
  zz_0006fb4_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),(int)pfVar5,param_12,param_13,param_14,param_15,param_16);
  uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)(char)(&DAT_8030e9fd)[iVar3] ^
                                                       0x80000000) - DOUBLE_80438a80),param_2,
                      param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),pfVar5,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar5,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 0x11;
  return;
}



// ==== 800d3f4c  FUN_800d3f4c ====

void FUN_800d3f4c(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar4 = *(int *)(param_1 + 0x8c);
  if (cVar1 == '\x01') {
    iVar4 = zz_00d602c_(param_1);
    fVar2 = FLOAT_80438a64;
    if (*(char *)(param_1 + 0x13) != iVar4) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(float *)(param_1 + 0x178) = fVar2;
      *(undefined1 *)(param_1 + 0x17c) = 0;
      *(undefined1 *)(param_1 + 0x17d) = 2;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(float *)(param_1 + 0x178) = *(float *)(param_1 + 0x178) + FLOAT_80438a94;
      iVar3 = zz_00d60b4_((float *)(param_1 + 0x16c));
      if (iVar3 != 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(short *)(iVar4 + 0x1c) = *(short *)(iVar4 + 0x1c) + -1;
      }
    }
  }
  else if (cVar1 < '\x03') {
    *(float *)(param_1 + 0x178) = *(float *)(param_1 + 0x178) + FLOAT_80438a94;
    iVar4 = zz_00d60b4_((float *)(param_1 + 0x16c));
    if (iVar4 != 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  return;
}



// ==== 800d404c  FUN_800d404c ====

void FUN_800d404c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined8 uVar5;
  
  fVar2 = FLOAT_80438abc;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(float *)(param_9 + 0x6c) = fVar2;
  fVar4 = FLOAT_80438ad4;
  fVar3 = FLOAT_80438ac8;
  fVar2 = FLOAT_80438a64;
  cVar1 = PTR_DAT_80433930[0x29];
  if (cVar1 == '\0') {
    if (PTR_DAT_80433930[0x32] == '\0') {
      if (*(char *)(param_9 + 0x12) == '\0') {
        if (*(char *)(param_9 + 0x168) == '\0') {
          *(float *)(param_9 + 100) = FLOAT_80438ac0;
        }
        else {
          *(float *)(param_9 + 100) = FLOAT_80438ac4;
        }
      }
      else if (*(char *)(param_9 + 0x168) == '\0') {
        *(float *)(param_9 + 100) = FLOAT_80438ac4;
      }
      else {
        *(float *)(param_9 + 100) = FLOAT_80438ac0;
      }
      fVar2 = FLOAT_80438ac8;
      *(float *)(param_9 + 100) = FLOAT_80438a64;
      *(float *)(param_9 + 0x38) = fVar2;
    }
    else {
      *(float *)(param_9 + 100) = FLOAT_80438a64;
      *(float *)(param_9 + 0x38) = fVar3;
    }
    *(float *)(param_9 + 0x68) = FLOAT_80438acc;
  }
  else if (cVar1 == '\x01') {
    *(float *)(param_9 + 100) = FLOAT_80438a64;
    if (*(char *)(param_9 + 0x169) == '\0') {
      *(float *)(param_9 + 0x68) = fVar2;
    }
    else {
      *(float *)(param_9 + 0x68) = FLOAT_80438ad0;
    }
  }
  else if (cVar1 == '\x02') {
    *(float *)(param_9 + 100) = FLOAT_80438a64;
    *(float *)(param_9 + 0x68) = fVar4;
  }
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1d;
  *(float *)(param_9 + 0x178) = FLOAT_80438a64;
  *(undefined1 *)(param_9 + 0x17c) = 0;
  *(undefined1 *)(param_9 + 0x17d) = 1;
  zz_00d60b4_((float *)(param_9 + 0x16c));
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x16c);
  *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0x170);
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0x174);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),0x24 - *(char *)(param_9 + 0x12),param_12,param_13,param_14,
              param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  return;
}



// ==== 800d41f8  FUN_800d41f8 ====

void FUN_800d41f8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined1 *puVar5;
  short sVar6;
  double dVar7;
  undefined1 local_28;
  char local_27;
  undefined1 local_26;
  undefined1 local_25;
  longlong local_20;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(param_1 + 0x7c);
    if (*(char *)(param_1 + 0x12) == '\x01') {
      dVar7 = zz_0045204_(*(short *)(param_1 + 0x70));
      *(float *)(param_1 + 0x58) =
           (float)((double)FLOAT_80438ad8 * dVar7 + (double)*(float *)(param_1 + 0x16c));
      dVar7 = zz_0045204_(*(short *)(param_1 + 0x70));
      *(float *)(param_1 + 0x5c) =
           -(float)((double)FLOAT_80438ad8 * dVar7 - (double)*(float *)(param_1 + 0x170));
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x174);
      fVar2 = FLOAT_80438aa0;
      if (PTR_DAT_80433930[0x29] == '\x02') {
        *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * FLOAT_80438aa0;
        *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * fVar2;
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * fVar2;
      }
      else if (PTR_DAT_80433930[0x29] == '\x01') {
        *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * FLOAT_80438aa0;
      }
      sVar6 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar6;
      if ((sVar6 < 1) && (*(short *)(param_1 + 0x1e) < 3)) {
        *(undefined2 *)(param_1 + 0x1c) = 4;
        local_28 = 4;
        local_27 = 0;
        local_26 = 1;
        local_25 = *(undefined1 *)(param_1 + 0x169);
        puVar5 = zz_00d309c_(&local_28);
        if (puVar5 != (undefined1 *)0x0) {
          *(int *)(puVar5 + 0x8c) = param_1;
          *(undefined4 *)(puVar5 + 0x90) = *(undefined4 *)(param_1 + 0x90);
          *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
        }
      }
    }
    else {
      dVar7 = zz_0045204_(*(short *)(param_1 + 0x70));
      iVar4 = (int)(FLOAT_80438adc * (float)((double)FLOAT_80438aa8 * dVar7));
      local_20 = (longlong)iVar4;
      *(short *)(param_1 + 0x72) = (short)iVar4;
      dVar7 = zz_0045204_(*(short *)(param_1 + 0x70));
      *(short *)(param_1 + 0x74) =
           (short)(int)(FLOAT_80438adc * (float)((double)FLOAT_80438ae0 * dVar7));
    }
    fVar3 = FLOAT_80438ae8;
    fVar2 = FLOAT_80438ae4;
    if (('\x01' < (char)PTR_DAT_80433934[0xef]) &&
       (*(float *)(param_1 + 100) = *(float *)(param_1 + 100) + *(float *)(param_1 + 0x38),
       fVar3 <= fVar2 + *(float *)(param_1 + 100))) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(float *)(param_1 + 0x178) = *(float *)(param_1 + 0x178) + FLOAT_80438a94;
    iVar4 = zz_00d60b4_((float *)(param_1 + 0x16c));
    if (iVar4 != 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined2 *)(param_1 + 0x7c) = 0x444;
      *(undefined2 *)(param_1 + 0x70) = 0;
      *(undefined2 *)(param_1 + 0x1c) = 4;
      *(undefined2 *)(param_1 + 0x1e) = 0;
      if (*(char *)(param_1 + 0x12) == '\0') {
        local_28 = 5;
        iVar4 = 0;
        local_27 = '\0';
        local_26 = 1;
        local_25 = *(undefined1 *)(param_1 + 0x169);
        do {
          puVar5 = zz_00d309c_(&local_28);
          if (puVar5 != (undefined1 *)0x0) {
            *(int *)(puVar5 + 0x8c) = param_1;
            *(undefined4 *)(puVar5 + 0x90) = *(undefined4 *)(param_1 + 0x90);
          }
          iVar4 = iVar4 + 1;
          local_27 = local_27 + '\x01';
        } while (iVar4 < 3);
      }
    }
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x16c);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x170);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x174);
    fVar2 = FLOAT_80438aa0;
    if (PTR_DAT_80433930[0x29] == '\x02') {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * FLOAT_80438aa0;
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * fVar2;
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * fVar2;
    }
    else if (PTR_DAT_80433930[0x29] == '\x01') {
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * FLOAT_80438aa0;
    }
  }
  return;
}



// ==== 800d4524  FUN_800d4524 ====

void FUN_800d4524(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(code **)(param_1 + 0x100) = FUN_800d6b5c;
  zz_0089100_(param_1,0x21,1);
  *(undefined1 *)(param_1 + 0x84) = 0x11;
  uVar4 = zz_00055fc_();
  dVar5 = zz_0045204_((short)(uVar4 << 8));
  *(float *)(param_1 + 100) = (float)((double)FLOAT_80438aec * dVar5);
  uVar4 = zz_00055fc_();
  dVar6 = zz_0045204_((short)(uVar4 << 8));
  fVar3 = FLOAT_80438af4;
  fVar2 = FLOAT_80438aa0;
  fVar1 = FLOAT_80438a94;
  dVar5 = (double)FLOAT_80438af0;
  dVar8 = (double)FLOAT_80438af4;
  dVar7 = (double)FLOAT_80438aa0;
  *(float *)(param_1 + 0x68) = (float)(dVar5 * dVar6);
  *(float *)(param_1 + 0x6c) = fVar3;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  *(float *)(param_1 + 0x60) = fVar1;
  if (PTR_DAT_80433930[0x29] == '\x02') {
    *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 100) * dVar7);
    *(float *)(param_1 + 0x68) = (float)((double)*(float *)(param_1 + 0x68) * dVar7);
    *(float *)(param_1 + 0x58) = (float)((double)*(float *)(param_1 + 0x58) * dVar7);
    *(float *)(param_1 + 0x5c) = (float)((double)*(float *)(param_1 + 0x5c) * dVar7);
  }
  else if (PTR_DAT_80433930[0x29] == '\x01') {
    *(float *)(param_1 + 0x68) = (float)((double)*(float *)(param_1 + 0x68) * dVar7);
    *(float *)(param_1 + 0x5c) = (float)((double)*(float *)(param_1 + 0x5c) * dVar7);
  }
  zz_0006fb4_(dVar7,dVar8,(double)(float)(dVar5 * dVar6),in_f4,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
              *(int *)(param_1 + 0xe0),0x37,param_4,param_5,param_6,param_7,param_8);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x169) + '\x11';
  return;
}



// ==== 800d46a0  FUN_800d46a0 ====

void FUN_800d46a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_800d6bd0;
  zz_0089100_(param_9,0x21,1);
  *(undefined1 *)(param_9 + 0x84) = 0x21;
  *(short *)(param_9 + 0x70) = *(char *)(param_9 + 0x12) * 0x5555;
  *(short *)(param_9 + 0x72) = *(char *)(param_9 + 0x12) * 0x4000 + -0x4000;
  *(short *)(param_9 + 0x74) = (short)*(char *)(param_9 + 0x12) << 0xc;
  uVar1 = zz_00d4794_(param_9);
  zz_0006fb4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),0x36,param_12,param_13,param_14,param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  return;
}



// ==== 800d474c  FUN_800d474c ====

void FUN_800d474c(int param_1)

{
  if ('\x01' < *(char *)(*(int *)(param_1 + 0x8c) + 0x18)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x400;
  zz_00d4794_(param_1);
  return;
}



// ==== 800d4794  zz_00d4794_ ====

void zz_00d4794_(int param_1)

{
  double dVar1;
  
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x200;
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x800;
  dVar1 = zz_0045204_(*(short *)(param_1 + 0x70));
  *(float *)(param_1 + 100) = (float)((double)FLOAT_80438afc * dVar1);
  dVar1 = zz_0045238_(*(short *)(param_1 + 0x70));
  *(float *)(param_1 + 0x6c) = (float)((double)FLOAT_80438b00 * dVar1);
  dVar1 = zz_0045204_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x68) = (float)((double)FLOAT_80438b04 * dVar1);
  return;
}



// ==== 800d4810  FUN_800d4810 ====

void FUN_800d4810(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  double dVar8;
  
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    fVar1 = FLOAT_80438a94;
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    *(float *)(param_9 + 0x60) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    fVar4 = FLOAT_80438b10;
    fVar3 = FLOAT_80438b08;
    fVar2 = FLOAT_80438aa0;
    if (PTR_DAT_80433930[0x29] == '\x02') {
      param_2 = (double)FLOAT_80438aa0;
      dVar8 = (double)FLOAT_80438b08;
      *(float *)(param_9 + 0x5c) = FLOAT_80438aa0;
      fVar1 = FLOAT_80438b0c;
      *(float *)(param_9 + 0x58) = fVar2;
      *(float *)(param_9 + 100) = fVar3;
      *(float *)(param_9 + 0x68) = fVar1;
    }
    else if (PTR_DAT_80433930[0x29] == '\x01') {
      dVar8 = (double)FLOAT_80438b10;
      *(float *)(param_9 + 0x5c) = FLOAT_80438aa0;
      fVar1 = FLOAT_80438b14;
      *(float *)(param_9 + 100) = fVar4;
      *(float *)(param_9 + 0x68) = fVar1;
    }
    else {
      *(float *)(param_9 + 0x5c) = fVar1;
      fVar1 = FLOAT_80438b18;
      dVar8 = (double)FLOAT_80438b10;
      *(float *)(param_9 + 100) = FLOAT_80438b10;
      *(float *)(param_9 + 0x68) = fVar1;
    }
    iVar5 = 0;
    *(float *)(param_9 + 0x6c) = FLOAT_80438b1c;
    psVar7 = (short *)&DAT_80433b64;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    iVar6 = param_9;
    do {
      dVar8 = (double)zz_0006fb4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(iVar6 + 0xe0),(int)*psVar7,param_12,param_13
                                  ,param_14,param_15,param_16);
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 4;
      psVar7 = psVar7 + 1;
    } while (iVar5 < 4);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  }
  return;
}



// ==== 800d49a8  FUN_800d49a8 ====

void FUN_800d49a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined8 uVar2;
  
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(code **)(param_9 + 0x100) = FUN_800d6c40;
    uVar2 = zz_0089100_(param_9,0x21,1);
    *(float *)(param_9 + 0x6c) = FLOAT_80438aa0;
    if (PTR_DAT_80433930[0x29] == '\0') {
      if (*(char *)(param_9 + 0x168) == '\0') {
        *(float *)(param_9 + 100) = FLOAT_80438a98;
      }
      else {
        *(float *)(param_9 + 100) = FLOAT_80438a9c;
      }
    }
    else if (*(char *)(param_9 + 0x169) == '\0') {
      *(float *)(param_9 + 100) = FLOAT_80438a64;
    }
    else {
      *(float *)(param_9 + 100) = FLOAT_80438ad0;
    }
    fVar1 = FLOAT_80438a94;
    *(float *)(param_9 + 0x60) = FLOAT_80438a94;
    *(float *)(param_9 + 0x5c) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    if (PTR_DAT_80433930[0x29] == '\x01') {
      *(float *)(param_9 + 0x5c) = FLOAT_80438aa0;
    }
    if (*(char *)(param_9 + 0x12) == '\0') {
      *(float *)(param_9 + 0x68) = FLOAT_80438b20;
      *(undefined2 *)(param_9 + 0x74) = 0;
    }
    else {
      *(float *)(param_9 + 0x68) = FLOAT_80438b24;
      *(undefined2 *)(param_9 + 0x74) = 0x8000;
    }
    *(undefined2 *)(param_9 + 0x1c) = 0;
    zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                *(int *)(param_9 + 0xe0),0x35,param_12,param_13,param_14,param_15,param_16);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  }
  return;
}



// ==== 800d4b98  FUN_800d4b98 ====

void FUN_800d4b98(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  uVar3 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80433b6c + *(char *)(param_9 + 0x12) * 2),param_12,
                      param_13,param_14,param_15,param_16);
  iVar2 = *(char *)(param_9 + 0x12) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_8030eb10 + iVar2);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_8030eb0c + iVar2);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_8030eb14 + iVar2);
  zz_0007834_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,(undefined4 *)(param_9 + 0x20),&DAT_8030eb0c + iVar2,param_12,param_13,param_14,
              param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 0x15;
  return;
}



// ==== 800d4c34  FUN_800d4c34 ====

void FUN_800d4c34(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 0x31;
  fVar2 = FLOAT_80438b28;
  *(float *)(param_9 + 100) = FLOAT_80438a64;
  fVar1 = FLOAT_80438aa8;
  *(float *)(param_9 + 0x68) = fVar2;
  fVar2 = FLOAT_80438b2c;
  *(float *)(param_9 + 0x6c) = fVar1;
  fVar3 = FLOAT_80438b30;
  dVar4 = (double)FLOAT_80438b30;
  *(float *)(param_9 + 0x58) = fVar2;
  fVar1 = FLOAT_80438a94;
  *(float *)(param_9 + 0x5c) = fVar3;
  *(float *)(param_9 + 0x60) = fVar1;
  zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),*(int *)(&DAT_8030eb24 + *(char *)(param_9 + 0x12) * 4),
              param_12,param_13,param_14,param_15,param_16);
  zz_0007cac_((double)FLOAT_80438a64,*(int *)(param_9 + 0xe0));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  return;
}



// ==== 800d4cf0  FUN_800d4cf0 ====

void FUN_800d4cf0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    if ((int)*(short *)(param_1 + 0x1e) < *(char *)(*(int *)(param_1 + 0x8c) + 0x17c) + -1) {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 0x14;
    }
    if (*(short *)(param_1 + 0x1c) != 0) {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x44);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      fVar2 = FLOAT_80438a94;
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      fVar3 = FLOAT_80438b34;
      *(float *)(param_1 + 0x38) = (fVar2 - *(float *)(param_1 + 0x58)) / FLOAT_80438b34;
      *(float *)(param_1 + 0x3c) = (fVar2 - *(float *)(param_1 + 0x5c)) / fVar3;
    }
    else if (cVar1 < '\0') {
      return;
    }
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    fVar3 = FLOAT_80438b34;
    fVar2 = FLOAT_80438a94;
    dVar5 = DOUBLE_80438a80;
    if (sVar4 < 1) {
      dVar5 = (double)FLOAT_80438a94;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(float *)(param_1 + 0x58) = fVar2;
      *(float *)(param_1 + 0x5c) = fVar2;
      zz_0007cac_(dVar5,*(int *)(param_1 + 0xe0));
      *(float *)(param_1 + 0x44) = FLOAT_80438b38;
      *(short *)(param_1 + 0x1e) = (short)*(char *)(param_1 + 0x13);
    }
    else {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x38);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x3c);
      zz_0007cac_((double)((float)((double)CONCAT44(0x43300000,
                                                    0x1eU - (int)*(short *)(param_1 + 0x1c) ^
                                                    0x80000000) - dVar5) / fVar3),
                  *(int *)(param_1 + 0xe0));
    }
  }
  return;
}



// ==== 800d4e70  FUN_800d4e70 ====

void FUN_800d4e70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  *(undefined1 *)(param_1 + 0x84) = 1;
  fVar1 = FLOAT_80438a64;
  *(undefined2 *)(param_1 + 0x72) = 0;
  fVar2 = FLOAT_80438b3c;
  *(float *)(param_1 + 100) = fVar1;
  fVar1 = FLOAT_80438b40;
  *(float *)(param_1 + 0x68) = fVar2;
  dVar7 = DOUBLE_80438a80;
  *(float *)(param_1 + 0x6c) = fVar1;
  dVar8 = (double)FLOAT_80438a70;
  dVar4 = (double)FLOAT_80438a74;
  dVar6 = (double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,
                                                                   (int)*(char *)(param_1 + 0x13) ^
                                                                   0x80000000) - dVar7));
  *(float *)(param_1 + 100) =
       (float)(dVar6 + -(double)(float)(dVar6 * dVar4 - (double)*(float *)(param_1 + 100)));
  *(short *)(param_1 + 0x1c) = (short)*(char *)(param_1 + 0x13);
  *(undefined2 *)(param_1 + 0x1e) = 0;
  uVar5 = zz_0006fb4_(dVar4,dVar6,dVar7,dVar8,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                      *(int *)(param_1 + 0xe0),
                      (int)*(short *)(&DAT_8030eb50 + *(char *)(param_1 + 0x12) * 4),param_4,param_5
                      ,param_6,param_7,param_8);
  pfVar3 = (float *)(int)*(short *)(&DAT_8030eb52 + *(char *)(param_1 + 0x12) * 4);
  zz_0006fb4_(uVar5,dVar6,dVar7,dVar8,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,*(int *)(param_1 + 0xe4),
              (int)pfVar3,param_4,param_5,param_6,param_7,param_8);
  if ((double)FLOAT_80438a64 <= (double)*(float *)(&DAT_8030eb7c + *(char *)(param_1 + 0x12) * 4)) {
    uVar5 = zz_00086b8_((double)*(float *)(&DAT_8030eb7c + *(char *)(param_1 + 0x12) * 4),dVar6,
                        dVar7,dVar8,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,*(int *)(param_1 + 0xe4),
                        pfVar3,param_4,param_5,param_6,param_7,param_8);
    zz_0007c30_(uVar5,dVar6,dVar7,dVar8,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),extraout_r4
                ,pfVar3,param_4,param_5,param_6,param_7,param_8);
  }
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x169) + '\x11';
  return;
}



// ==== 800d5054  FUN_800d5054 ====

void FUN_800d5054(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  dVar4 = (double)zz_0089100_(param_9,0x20,1);
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar2 = FLOAT_80438b0c;
  fVar1 = FLOAT_80438a64;
  if (PTR_DAT_80433930[0x29] == '\x01') {
    *(float *)(param_9 + 100) = FLOAT_80438a64;
    *(float *)(param_9 + 0x68) = fVar1;
  }
  else {
    dVar4 = (double)FLOAT_80438b4c;
    *(float *)(param_9 + 100) = FLOAT_80438b4c;
    *(float *)(param_9 + 0x68) = fVar2;
  }
  *(float *)(param_9 + 0x6c) = FLOAT_80438b50;
  uVar5 = zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),0x40,param_12,param_13,param_14,param_15,param_16);
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3e6) == '\0') {
    iVar3 = *(char *)(param_9 + 0x96) + 0x1f;
  }
  else {
    iVar3 = 0x1e;
  }
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe4),iVar3,param_12,param_13,param_14,param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
  return;
}



// ==== 800d512c  FUN_800d512c ====

void FUN_800d512c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char *pcVar1;
  undefined8 uVar2;
  
  if ((-1 < (char)PTR_DAT_80433934[*(char *)(param_9 + 0x169) + 0xc0]) &&
     (*(char *)(&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_9 + 0x169) + 0xc0]] == '\0'))
  {
    pcVar1 = (char *)0x54;
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                        ,*(int *)(param_9 + 0xe0),0x54,param_12,param_13,param_14,param_15,param_16)
    ;
    uVar2 = zz_0007908_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x20),pcVar1,param_12,
                        param_13,param_14,param_15,param_16);
    if ((*(byte *)(param_9 + 0x169) & 1) == 0) {
      *(float *)(param_9 + 0x20) = -*(float *)(param_9 + 0x20);
    }
    if ((*(byte *)(param_9 + 0x169) & 2) != 0) {
      *(float *)(param_9 + 0x24) = -*(float *)(param_9 + 0x24);
    }
    zz_0007834_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x20),pcVar1,param_12,param_13,
                param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0x15;
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 800d5208  FUN_800d5208 ====

void FUN_800d5208(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar7;
  double dVar8;
  
  cVar1 = PTR_DAT_80433934[*(char *)(param_9 + 0x169) + 0xc0];
  if (((-1 < cVar1) && (uVar5 = 1 << (int)cVar1, ((byte)PTR_DAT_80433934[0x15db] & uVar5) != 0)) &&
     (((int)(char)PTR_DAT_80433930[2] & uVar5) != 0)) {
    *(char *)(param_9 + 0x96) = cVar1;
    fVar4 = FLOAT_80438b4c;
    fVar3 = FLOAT_80438b1c;
    fVar2 = FLOAT_80438b0c;
    dVar8 = (double)FLOAT_80438b4c;
    iVar6 = *(byte *)(param_9 + 0x18) + 1;
    *(char *)(param_9 + 0x18) = (char)iVar6;
    *(float *)(param_9 + 100) = fVar4;
    *(float *)(param_9 + 0x68) = fVar2;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    uVar7 = zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 1;
    uVar7 = zz_0006fb4_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        *(int *)(param_9 + 0xe0),0x40,iVar6,in_r7,in_r8,in_r9,in_r10);
    uVar7 = zz_0006fb4_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        *(int *)(param_9 + 0xe4),*(char *)(param_9 + 0x96) + 0x1f,iVar6,in_r7,in_r8,
                        in_r9,in_r10);
    zz_0006fb4_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc44bc0,
                *(int *)(param_9 + 0xe8),(int)*(char *)(param_9 + 0x96),iVar6,in_r7,in_r8,in_r9,
                in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x169) + '\x11';
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 800d5318  FUN_800d5318 ====

void FUN_800d5318(int param_1)

{
  char cVar1;
  
  cVar1 = PTR_DAT_80433930[0x29];
  if (cVar1 == '\0') {
    (*(code *)(&PTR_LAB_8030eba8)[*(char *)(param_1 + 0x11)])();
  }
  else if (cVar1 == '\x01') {
    (*(code *)(&PTR_LAB_8030ebe0)[*(char *)(param_1 + 0x11)])();
  }
  else if (cVar1 == '\x02') {
    (*(code *)(&PTR_LAB_8030ec18)[*(char *)(param_1 + 0x11)])();
  }
  return;
}



// ==== 800d53c0  FUN_800d53c0 ====

void FUN_800d53c0(int param_1)

{
  (*(code *)(&PTR_FUN_8030ec50)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800d53fc  zz_00d53fc_ ====

void zz_00d53fc_(int param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_00d309c_(param_2);
  if (puVar1 != (undefined1 *)0x0) {
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x168] = *(undefined1 *)(param_1 + 0x168);
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  }
  return;
}



// ==== 800d545c  FUN_800d545c ====

void FUN_800d545c(int param_1)

{
  undefined1 local_18;
  byte local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0;
  local_18 = 3;
  local_16 = 1;
  local_17 = *(byte *)(param_1 + 0x168) ^ 1;
  local_15 = 0;
  zz_00d53fc_(param_1,&local_18);
  if (PTR_DAT_80433930[0x32] == '\0') {
    if (*(char *)(param_1 + 0x168) == '\0') {
      zz_00dbc74_(0);
    }
    else {
      zz_00dbb48_((int)*(char *)(param_1 + 0x168));
    }
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  return;
}



// ==== 800d5510  zz_00d5510_ ====

void zz_00d5510_(int param_1)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0;
  local_18 = 0;
  local_16 = 0x10;
  local_15 = *(undefined1 *)(param_1 + 0x169);
  bVar1 = *(char *)(*(int *)(param_1 + 0x90) + 0x436) == '\0';
  if (bVar1) {
    *(undefined1 *)(param_1 + 0x17d) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x17d) = 0;
  }
  if ((PTR_DAT_80433930[0x29] == '\x01') &&
     (*(char *)(param_1 + 0x17d) = *(char *)(param_1 + 0x17d) + '\x04', !bVar1)) {
    *(char *)(param_1 + 0x17d) = *(char *)(param_1 + 0x17d) + '\x01';
  }
  cVar3 = '\0';
  iVar4 = 0;
  do {
    if ((iVar4 != 8) || (!bVar1)) {
      local_17 = (undefined1)iVar4;
      iVar2 = zz_00d53fc_(param_1,&local_18);
      *(char *)(iVar2 + 0x13) = cVar3;
      cVar3 = cVar3 + '\x01';
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 10);
  return;
}



// ==== 800d5608  zz_00d5608_ ====

void zz_00d5608_(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  
  if (*(short *)(param_1 + 0x1c) == 0) {
    puVar2 = &DAT_8030ec74;
    uVar1 = 0;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    do {
      zz_00d53fc_(param_1,puVar2);
      uVar1 = uVar1 + 1;
      puVar2 = puVar2 + 4;
    } while (uVar1 < 3);
  }
  return;
}



// ==== 800d5680  zz_00d5680_ ====

void zz_00d5680_(int param_1,uint param_2,uint param_3)

{
  float fVar1;
  float fVar2;
  
  if (((param_2 | param_3) & 0xc000c) == 0) {
    *(undefined1 *)(param_1 + 0x16d) = 0;
  }
  if ((param_3 & 0x80008) == 0) {
    if ((param_3 & 0x40004) != 0) {
      *(short *)(param_1 + 0x16c) = *(short *)(param_1 + 0x16c) + 0x100;
      *(undefined1 *)(param_1 + 0x16d) = 0;
      *(undefined2 *)(param_1 + 0x1c) = 4;
    }
  }
  else {
    *(short *)(param_1 + 0x16c) = *(short *)(param_1 + 0x16c) + -0x100;
    *(undefined1 *)(param_1 + 0x16d) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 4;
  }
  if (*(short *)(param_1 + 0x1c) == 0) {
    if ((param_2 & 0x80008) == 0) {
      if ((param_2 & 0x40004) != 0) {
        *(short *)(param_1 + 0x16c) = *(short *)(param_1 + 0x16c) + 0x40;
      }
    }
    else {
      *(short *)(param_1 + 0x16c) = *(short *)(param_1 + 0x16c) + -0x40;
    }
  }
  else {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  if (*(char *)(param_1 + 0x16c) < *(char *)(param_1 + 0x17e)) {
    *(char *)(param_1 + 0x16c) = *(char *)(param_1 + 0x17e);
    *(undefined1 *)(param_1 + 0x16d) = 0;
  }
  else if (*(char *)(param_1 + 0x17d) < *(char *)(param_1 + 0x16c)) {
    *(char *)(param_1 + 0x16c) = *(char *)(param_1 + 0x17d);
    *(undefined1 *)(param_1 + 0x16d) = 0;
  }
  if (*(char *)(param_1 + 0x16c) != *(char *)(param_1 + 0x16e)) {
    *(char *)(param_1 + 0x16e) = *(char *)(param_1 + 0x16c);
    *(float *)(param_1 + 0x3c) =
         -((float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x16c) ^ 0x80000000) -
                  DOUBLE_80438a80) * *(float *)(param_1 + 0x178) - FLOAT_80438ab0);
  }
  fVar2 = FLOAT_80438ae0;
  if (PTR_DAT_80433930[0x29] == '\x01') {
    fVar2 = FLOAT_80438aac;
  }
  fVar1 = *(float *)(param_1 + 0x68);
  if (fVar1 != *(float *)(param_1 + 0x3c)) {
    if (fVar1 <= *(float *)(param_1 + 0x3c)) {
      *(float *)(param_1 + 0x68) = fVar1 + fVar2;
      if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x68)) {
        *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x3c);
      }
    }
    else {
      *(float *)(param_1 + 0x68) = fVar1 - fVar2;
      if (*(float *)(param_1 + 0x68) < *(float *)(param_1 + 0x3c)) {
        *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x3c);
      }
    }
  }
  return;
}



// ==== 800d5858  zz_00d5858_ ====

void zz_00d5858_(int param_1)

{
  uint uVar1;
  
  uVar1 = (&DAT_803c7204)[*(char *)(param_1 + 0x96) * 8];
  zz_00d5680_(param_1,(&DAT_803c71fc)[*(char *)(param_1 + 0x96) * 8],uVar1);
  if ((*(int *)(param_1 + 0x170) != 1) && ((uVar1 & 0x1100) != 0)) {
    if (*(char *)(param_1 + 0x17f) == '\x02') {
      if (*(char *)(param_1 + 0x168) == '\0') {
        zz_00dbb48_(0);
      }
      else {
        zz_00dbc74_((int)*(char *)(param_1 + 0x168));
      }
    }
    else {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined4 *)(param_1 + 0x170) = 1;
    PTR_DAT_80433934[0xef] = 1;
  }
  return;
}



// ==== 800d5928  FUN_800d5928 ====

void FUN_800d5928(int param_1)

{
  short sVar1;
  
  if (*(short *)(param_1 + 0x1e) != 0) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + *(float *)(param_1 + 0x44);
    sVar1 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar1;
    if (sVar1 == 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x38);
    }
  }
  zz_00d5680_(param_1,(&DAT_803c71fc)[*(char *)(param_1 + 0x96) * 8],
              (&DAT_803c7204)[*(char *)(param_1 + 0x96) * 8]);
  return;
}



// ==== 800d59ac  FUN_800d59ac ====

void FUN_800d59ac(int param_1)

{
  if (((&DAT_803c7204)[*(char *)(param_1 + 0x96) * 8] & 0x1100) != 0) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  zz_00d5680_(param_1,(&DAT_803c71fc)[*(char *)(param_1 + 0x96) * 8],
              (&DAT_803c7204)[*(char *)(param_1 + 0x96) * 8]);
  return;
}



// ==== 800d5a18  FUN_800d5a18 ====

void FUN_800d5a18(int param_1)

{
  PTR_DAT_80433934[0xef] = 2;
  if (((&DAT_803c7204)[*(char *)(param_1 + 0x96) * 8] & 0x1100) != 0) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  zz_00d5680_(param_1,0,0);
  return;
}



// ==== 800d5abc  FUN_800d5abc ====

void FUN_800d5abc(int param_1)

{
  (*(code *)(&PTR_FUN_8030ec80)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800d5af8  FUN_800d5af8 ====

void FUN_800d5af8(int param_1)

{
  zz_00d5510_(param_1);
  return;
}



// ==== 800d5b18  FUN_800d5b18 ====

void FUN_800d5b18(int param_1)

{
  uint uVar1;
  undefined1 *puVar2;
  
  if (*(short *)(param_1 + 0x1c) == 0) {
    puVar2 = &DAT_8030ec90;
    uVar1 = 0;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    do {
      if (uVar1 == 0) {
        puVar2[1] = *(undefined1 *)(param_1 + 0x168);
      }
      puVar2[3] = *(undefined1 *)(param_1 + 0x169);
      zz_00d53fc_(param_1,puVar2);
      uVar1 = uVar1 + 1;
      puVar2 = puVar2 + 4;
    } while (uVar1 < 4);
  }
  return;
}



// ==== 800d5ba8  FUN_800d5ba8 ====

void FUN_800d5ba8(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = (int)*(char *)(param_1 + 0x96);
  if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar2) != 0) {
    uVar1 = (&DAT_803c71fc)[iVar2 * 8];
    uVar3 = (&DAT_803c7204)[iVar2 * 8];
    if ((uVar3 & 0x1100) != 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      PTR_DAT_80433934[0xf0] = PTR_DAT_80433934[0xf0] | (byte)(1 << (int)*(char *)(param_1 + 0x96));
    }
    zz_00d5680_(param_1,uVar1,uVar3);
  }
  return;
}



// ==== 800d5c48  FUN_800d5c48 ====

void FUN_800d5c48(int param_1)

{
  (*(code *)(&PTR_FUN_8030eca0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800d5c84  FUN_800d5c84 ====

void FUN_800d5c84(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined1 *puVar4;
  undefined1 local_18;
  char local_17;
  undefined1 local_16;
  undefined1 local_15;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    sVar2 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar2;
    if (sVar2 < 1) {
      uVar3 = *(uint *)(param_1 + 0x174);
      while ((uVar3 != 0 && (*(char *)(param_1 + 0x13) < '\v'))) {
        if ((uVar3 & 1 << (int)*(char *)(param_1 + 0x13)) != 0) {
          *(undefined2 *)(param_1 + 0x1e) = 0x1e;
          local_17 = *(char *)(param_1 + 0x13);
          if ((1 << (int)local_17 & (&DAT_803cce30)[*(char *)(param_1 + 0x96) * 0x25]) != 0) {
            local_18 = 9;
            local_16 = 1;
            local_15 = *(undefined1 *)(param_1 + 0x169);
            puVar4 = zz_00d309c_(&local_18);
            if (puVar4 != (undefined1 *)0x0) {
              *(int *)(puVar4 + 0x8c) = param_1;
              puVar4[0x13] = *(undefined1 *)(param_1 + 0x17c);
            }
            local_18 = 10;
            local_17 = *(undefined1 *)(param_1 + 0x13);
            local_16 = 2;
            puVar4 = zz_00d309c_(&local_18);
            if (puVar4 != (undefined1 *)0x0) {
              *(int *)(puVar4 + 0x8c) = param_1;
              puVar4[0x13] = *(undefined1 *)(param_1 + 0x17c);
              puVar4[0x96] = *(undefined1 *)(param_1 + 0x96);
            }
            *(char *)(param_1 + 0x17c) = *(char *)(param_1 + 0x17c) + '\x01';
          }
          uVar3 = 0;
        }
        *(char *)(param_1 + 0x13) = *(char *)(param_1 + 0x13) + '\x01';
      }
      if (*(char *)(param_1 + 0x13) == '\v') {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x17d) = 0;
        *(undefined1 *)(param_1 + 0x17e) = 0;
        if ('\x02' < *(char *)(param_1 + 0x17c)) {
          *(char *)(param_1 + 0x17e) = -(*(char *)(param_1 + 0x17c) + -2);
        }
      }
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if (*(short *)(param_1 + 0x1c) == 0) {
        uVar3 = 0;
        *(undefined1 *)(param_1 + 0x1a) = 1;
        puVar4 = &DAT_80433b70;
        do {
          if (uVar3 == 0) {
            puVar4[1] = *(undefined1 *)(param_1 + 0x168);
          }
          puVar4[3] = *(undefined1 *)(param_1 + 0x169);
          zz_00d53fc_(param_1,puVar4);
          uVar3 = uVar3 + 1;
          puVar4 = puVar4 + 4;
        } while (uVar3 < 2);
      }
    }
    else if (-1 < cVar1) {
      *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0x13) = 0;
      *(undefined2 *)(param_1 + 0x1e) = 0;
      *(undefined1 *)(param_1 + 0x17c) = 0;
      *(undefined4 *)(param_1 + 0x174) = 0;
      if (DAT_803ccda0 != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803cce30;
      }
      if (DAT_803cce34 != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803ccec4;
      }
      if (DAT_803ccec8 != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803ccf58;
      }
      if (DAT_803ccf5c != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803ccfec;
      }
      if (DAT_803ccff0 != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803cd080;
      }
      if (DAT_803cd084 != 0) {
        *(uint *)(param_1 + 0x174) = *(uint *)(param_1 + 0x174) | DAT_803cd114;
      }
      if (*(int *)(param_1 + 0x174) == 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      }
    }
  }
  else if (cVar1 < '\x04') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  return;
}



// ==== 800d5f8c  FUN_800d5f8c ====

void FUN_800d5f8c(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = (int)*(char *)(param_1 + 0x96);
  if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar2) != 0) {
    uVar1 = (&DAT_803c71fc)[iVar2 * 8];
    uVar3 = (&DAT_803c7204)[iVar2 * 8];
    if ((uVar3 & 0x1100) != 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      PTR_DAT_80433934[0xf0] = PTR_DAT_80433934[0xf0] | (byte)(1 << (int)*(char *)(param_1 + 0x96));
    }
    zz_00d5680_(param_1,uVar1,uVar3);
  }
  return;
}



// ==== 800d602c  zz_00d602c_ ====

undefined4 zz_00d602c_(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0x170);
}



// ==== 800d604c  FUN_800d604c ====

void FUN_800d604c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  puVar2 = (undefined4 *)(param_9 + 0x144);
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      param_1 = zz_0006d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar2,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
      param_10 = extraout_r4;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800d60b4  zz_00d60b4_ ====

undefined4 zz_00d60b4_(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  undefined4 uVar8;
  
  fVar4 = *(float *)((&PTR_DAT_8030ed8c)[*(char *)((int)param_1 + 0x11)] +
                    (*(char *)(param_1 + 4) + 1) * 0x10);
  pfVar7 = (float *)((&PTR_DAT_8030ed8c)[*(char *)((int)param_1 + 0x11)] +
                    *(char *)(param_1 + 4) * 0x10);
  if ((fVar4 <= param_1[3]) || (FLOAT_80438b54 == fVar4)) {
    *(char *)(param_1 + 4) = *(char *)(param_1 + 4) + '\x01';
    pfVar7 = (float *)((&PTR_DAT_8030ed8c)[*(char *)((int)param_1 + 0x11)] +
                      *(char *)(param_1 + 4) * 0x10);
  }
  fVar6 = FLOAT_80438b54;
  fVar4 = *pfVar7;
  uVar8 = 0;
  fVar1 = pfVar7[1];
  fVar2 = pfVar7[2];
  fVar3 = pfVar7[3];
  if ((param_1[3] == fVar4) || (FLOAT_80438b54 == fVar4)) {
    *param_1 = fVar1;
    fVar1 = FLOAT_80438b54;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    if (fVar1 == fVar4) {
      uVar8 = 1;
    }
  }
  else {
    fVar5 = param_1[3] - fVar4;
    pfVar7 = (float *)((&PTR_DAT_8030ed8c)[*(char *)((int)param_1 + 0x11)] +
                      (*(char *)(param_1 + 4) + 1) * 0x10);
    fVar4 = *pfVar7 - fVar4;
    *param_1 = ((pfVar7[1] - fVar1) / fVar4) * fVar5 + fVar1;
    param_1[1] = ((pfVar7[2] - fVar2) / fVar4) * fVar5 + fVar2;
    param_1[2] = ((pfVar7[3] - fVar3) / fVar4) * fVar5 + fVar3;
    fVar4 = FLOAT_80438b54;
    if (((*pfVar7 < param_1[3]) || (fVar6 == *pfVar7)) &&
       (*(char *)(param_1 + 4) = *(char *)(param_1 + 4) + '\x01', fVar4 == *pfVar7)) {
      uVar8 = 1;
    }
  }
  return uVar8;
}



// ==== 800d6238  FUN_800d6238 ====

void FUN_800d6238(int param_1)

{
  (*(code *)(&PTR_FUN_8030ed98)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800d6274  FUN_800d6274 ====

void FUN_800d6274(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  undefined **ppuVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  float fVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined8 uVar13;
  undefined *local_38;
  undefined *local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  puVar8 = &DAT_802b1cc0;
  pfVar1 = &local_2c;
  local_2c = DAT_802b1cc0;
  local_28 = (float)DAT_802b1cc4;
  local_24 = (float)DAT_802b1cc8;
  uVar3 = DAT_802b1cc4;
  fVar6 = DAT_802b1cc0;
  uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xe0),&local_2c,(char *)pfVar1,uVar3,fVar6,puVar8,in_r9,
                       in_r10);
  local_24 = FLOAT_80438a94;
  local_28 = FLOAT_80438a94;
  local_2c = FLOAT_80438a94;
  if (PTR_DAT_80433930[0x29] == '\x01') {
    local_28 = FLOAT_80438aa0;
  }
  zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),&local_2c,(char *)pfVar1,uVar3,fVar6,puVar8,in_r9,in_r10);
  zz_0009958_(*(int *)(param_9 + 0xe0),1);
  ppuVar2 = &local_38;
  iVar4 = (char)PTR_DAT_80433930[0x29] * 0xc;
  puVar8 = (undefined4 *)(&DAT_8030ef38 + iVar4);
  puVar7 = (undefined *)*puVar8;
  puVar5 = *(undefined **)(&DAT_8030ef3c + iVar4);
  local_30 = *(float *)(&DAT_8030ef40 + iVar4);
  local_38 = puVar7;
  local_34 = puVar5;
  uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)ppuVar2,(float *)ppuVar2);
  uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xe4),&local_38,(char *)ppuVar2,puVar5,puVar7,puVar8,in_r9
                       ,in_r10);
  zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),(undefined4 *)(param_9 + 0x58),(char *)ppuVar2,puVar5,puVar7,
              puVar8,in_r9,in_r10);
  zz_0009958_(*(int *)(param_9 + 0xe4),1);
  if (-1 < *(char *)(param_9 + 0x16c)) {
    iVar9 = 0;
    iVar11 = 0;
    local_30 = FLOAT_80438a64;
    local_34 = (undefined *)FLOAT_80438a64;
    iVar4 = param_9;
    do {
      if (-1 < *(int *)(*(int *)(iVar4 + 0xe8) + 0x14)) {
        pfVar1 = &local_2c;
        puVar7 = (undefined *)((char)PTR_DAT_80433930[0x29] * 0x78);
        puVar5 = &DAT_8030edd0 + (int)(puVar7 + *(char *)(param_9 + 0x16d) * 0x14);
        local_38 = *(undefined **)(puVar5 + iVar11);
        uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
        uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(iVar4 + 0xe8),&local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,
                             in_r9,in_r10);
        zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar4 + 0xe8),(undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,
                    puVar7,puVar8,in_r9,in_r10);
        zz_0009958_(*(int *)(iVar4 + 0xe8),1);
      }
      iVar9 = iVar9 + 1;
      iVar11 = iVar11 + 4;
      iVar4 = iVar4 + 4;
    } while (iVar9 < 5);
    if (-1 < *(int *)(*(int *)(param_9 + 0xfc) + 0x14)) {
      pfVar1 = &local_2c;
      local_38 = (undefined *)FLOAT_80438b58;
      uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
      uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xfc),&local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,
                           in_r9,in_r10);
      zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xfc),(undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,
                  puVar7,puVar8,in_r9,in_r10);
      zz_0009958_(*(int *)(param_9 + 0xfc),1);
    }
    if (*(char *)(param_9 + 0x16c) == '\x01') {
      local_38 = (undefined *)FLOAT_80438b5c;
      pfVar1 = &local_2c;
      local_30 = FLOAT_80438b30;
      uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
      uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0x144),&local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,
                           in_r9,in_r10);
      zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x144),(undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,
                  puVar7,puVar8,in_r9,in_r10);
      zz_0009958_(*(int *)(param_9 + 0x144),1);
    }
  }
  if (*(char *)(param_9 + 0x16e) != '\0') {
    iVar4 = 0;
    iVar9 = 0;
    iVar11 = param_9 + 0x144;
    local_30 = FLOAT_80438a64;
    iVar12 = 0;
    local_34 = (undefined *)FLOAT_80438a64;
    do {
      iVar10 = *(int *)(iVar11 + 4);
      if (-1 < *(int *)(iVar10 + 0x14)) {
        pfVar1 = &local_2c;
        puVar5 = &DAT_8030edd0 + iVar9 + (char)PTR_DAT_80433930[0x29] * 0x78;
        local_38 = *(undefined **)(puVar5 + 0x50);
        uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
        uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                             &local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10);
        zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                    (undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10)
        ;
        zz_0009958_(iVar10,1);
        iVar12 = iVar12 + 1;
      }
      iVar4 = iVar4 + 1;
      iVar9 = iVar9 + 4;
      iVar11 = iVar11 + 4;
    } while (iVar4 < 5);
    if (*(char *)(param_9 + 0x16e) < '\0') {
      puVar7 = &DAT_8030edd0;
      pfVar1 = &local_2c;
      puVar5 = &DAT_8030edd0 + (5 - iVar12) * 4 + (char)PTR_DAT_80433930[0x29] * 0x78;
      local_38 = (undefined *)(*(float *)(puVar5 + 0x50) - FLOAT_80438b60);
      iVar4 = *(int *)(param_9 + 0x160);
      uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
      uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           &local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10);
      zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  (undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10);
      zz_0009958_(iVar4,1);
    }
    iVar4 = *(int *)(param_9 + 0x15c);
    if (-1 < *(int *)(iVar4 + 0x14)) {
      pfVar1 = &local_2c;
      local_38 = (undefined *)FLOAT_80438b64;
      uVar13 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&local_38,pfVar1);
      uVar13 = zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           &local_2c,(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10);
      zz_0007ae4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  (undefined4 *)(param_9 + 0x58),(char *)pfVar1,puVar5,puVar7,puVar8,in_r9,in_r10);
      zz_0009958_(iVar4,1);
    }
  }
  return;
}



// ==== 800d6648  FUN_800d6648 ====

void FUN_800d6648(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  
  dVar3 = (double)*(float *)(param_1 + 0x170);
  dVar4 = (double)*(float *)(param_1 + 0x174);
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x16c),dVar3,dVar4,afStack_38);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_38,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(param_1 + 0xe0),0);
  return;
}



// ==== 800d66ac  FUN_800d66ac ====

void FUN_800d66ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),2);
  return;
}



// ==== 800d66ec  FUN_800d66ec ====

void FUN_800d66ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),2);
  return;
}



// ==== 800d672c  FUN_800d672c ====

void FUN_800d672c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),2);
  return;
}



// ==== 800d676c  FUN_800d676c ====

void FUN_800d676c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  pfVar4 = (float *)&DAT_8030ef5c;
  iVar2 = 0;
  iVar3 = param_1;
  do {
    dVar6 = (double)pfVar4[1];
    dVar7 = (double)pfVar4[2];
    gnt4_PSMTXTrans_bl((double)*pfVar4,dVar6,dVar7,afStack_48);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(*(int *)(iVar3 + 0xe0),0);
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
    pfVar4 = pfVar4 + 3;
  } while (iVar2 < 2);
  iVar3 = 2;
  if ((*(ushort *)(param_1 + 0x1c) & 0x10) != 0) {
    iVar3 = 3;
  }
  dVar6 = (double)(float)(&DAT_8030ef60)[iVar3 * 3];
  dVar7 = (double)(float)(&DAT_8030ef64)[iVar3 * 3];
  gnt4_PSMTXTrans_bl((double)(float)(&DAT_8030ef5c)[iVar3 * 3],dVar6,dVar7,afStack_48);
  pfVar4 = afStack_48;
  uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar4,pfVar4);
  iVar3 = param_1 + iVar3 * 4;
  zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
              (undefined *)pfVar4,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(iVar3 + 0xe0),0);
  return;
}



// ==== 800d6874  FUN_800d6874 ====

void FUN_800d6874(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe0),2);
  }
  return;
}



// ==== 800d68c0  FUN_800d68c0 ====

void FUN_800d68c0(int param_1)

{
  if (PTR_DAT_80433930[0x33] == '\0') {
    zz_0009958_(*(int *)(param_1 + 0xe0),1);
  }
  return;
}



// ==== 800d68f8  FUN_800d68f8 ====

void FUN_800d68f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (PTR_DAT_80433930[0x33] == '\0') {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe0),1);
  }
  return;
}



// ==== 800d6948  FUN_800d6948 ====

void FUN_800d6948(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  double dVar3;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  if (PTR_DAT_80433930[0x33] == '\0') {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe4),0);
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_9 + 0x72) ^ 0x80000000;
    dVar3 = (double)FLOAT_80438b68;
    gnt4_PSMTXRotRad_bl((double)(float)(dVar3 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_14) -
                                                               DOUBLE_80438a80)),afStack_48,0x79);
    pfVar1 = afStack_48;
    uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
                ,afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe0),0);
  }
  return;
}



// ==== 800d69f4  FUN_800d69f4 ====

void FUN_800d69f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  float afStack_38 [12];
  
  if (PTR_DAT_80433930[0x33] == '\0') {
    iVar2 = *(int *)(param_9 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0009958_(iVar2,0);
    iVar2 = *(int *)(param_9 + 0xe4);
    dVar4 = (double)FLOAT_80438b70;
    dVar5 = (double)FLOAT_80438af8;
    gnt4_PSMTXTrans_bl((double)FLOAT_80438b6c,dVar4,dVar5,afStack_38);
    pfVar1 = afStack_38;
    uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar3,dVar4,dVar5,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_38,
                (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_0009958_(iVar2,1);
  }
  return;
}



// ==== 800d6a90  FUN_800d6a90 ====

void FUN_800d6a90(int param_1)

{
  if (PTR_DAT_80433930[0x33] == '\0') {
    zz_0009958_(*(int *)(param_1 + 0xe0),3);
  }
  return;
}



// ==== 800d6ac8  FUN_800d6ac8 ====

void FUN_800d6ac8(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  pfVar3 = (float *)&DAT_8030ef8c;
  iVar1 = 0;
  iVar2 = param_1;
  do {
    dVar5 = (double)pfVar3[1];
    dVar6 = (double)pfVar3[2];
    uVar4 = zz_020b4ac_((double)*pfVar3,dVar5,dVar6,(float *)(param_1 + 0x114),afStack_48);
    zz_00076d0_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar2 + 0xe0),afStack_48,
                param_3,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(*(int *)(iVar2 + 0xe0),0);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
    pfVar3 = pfVar3 + 3;
  } while (iVar1 < 3);
  return;
}



// ==== 800d6b5c  FUN_800d6b5c ====

void FUN_800d6b5c(int param_1)

{
  float afStack_38 [13];
  
  gnt4_PSVECAdd_bl((float *)(*(int *)(param_1 + 0x8c) + 0x20),(float *)(param_1 + 100),
                   (float *)(param_1 + 0x20));
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 800d6bd0  FUN_800d6bd0 ====

void FUN_800d6bd0(int param_1)

{
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  FUN_80047aa4(param_1);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80438b68 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80438a80)),
                      afStack_48,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
  return;
}



// ==== 800d6c40  FUN_800d6c40 ====

void FUN_800d6c40(int param_1)

{
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  *(float *)(param_1 + 0x20) =
       *(float *)(*(int *)(param_1 + 0x8c) + 0x20) + *(float *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x68);
  *(float *)(param_1 + 0x28) =
       *(float *)(*(int *)(param_1 + 0x8c) + 0x28) + *(float *)(param_1 + 0x6c);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80438b68 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80438a80)),
                      afStack_48,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_48);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
  return;
}



// ==== 800d6e0c  FUN_800d6e0c ====

void FUN_800d6e0c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x204) {
    zz_00bf40c_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x20d) {
    zz_00bf40c_(param_1,1);
  }
  return;
}



// ==== 800d6ea4  FUN_800d6ea4 ====

void FUN_800d6ea4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8030faa8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800d6ee4  FUN_800d6ee4 ====

void FUN_800d6ee4(int param_1,int param_2)

{
  if (*(short *)(param_1 + 1000) == 0x204) {
    zz_0099e70_(param_1,(&DAT_80433b78)[param_2]);
  }
  return;
}



// ==== 800d6f1c  FUN_800d6f1c ====

void FUN_800d6f1c(int param_1,int param_2)

{
  float afStack_18 [5];
  
  if (param_2 == 0) {
    zz_0137540_(param_1,0);
  }
  else {
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),(float *)&DAT_8030fabc,afStack_18);
    zz_00b2290_((double)FLOAT_80438b78,param_1,2,afStack_18);
  }
  return;
}



// ==== 800d6f80  FUN_800d6f80 ====

void FUN_800d6f80(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x204) {
    zz_001ab6c_(param_1,7);
  }
  else if (*(short *)(param_1 + 1000) == 0x20d) {
    zz_001ab6c_(param_1,0x5f);
  }
  return;
}



// ==== 800d6fd8  FUN_800d6fd8 ====

void FUN_800d6fd8(int param_1)

{
  (*(code *)(&PTR_FUN_8030fac8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800d7014  FUN_800d7014 ====

void FUN_800d7014(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8030fad8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d705c  FUN_800d705c ====

void FUN_800d705c(int param_1)

{
  (*(code *)(&PTR_FUN_80433b80)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d7094  FUN_800d7094 ====

void FUN_800d7094(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80438b7c;
  dVar2 = (double)FLOAT_80438b80;
  *(float *)(param_1 + 0x50) = FLOAT_80438b7c;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_00d7104_(param_1);
  return;
}



// ==== 800d7104  zz_00d7104_ ====

void zz_00d7104_(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined2 *)(param_1 + 0x548) = 0;
  zz_006660c_(param_1);
  zz_00d7ba8_(param_1,0x81);
  return;
}



// ==== 800d7154  FUN_800d7154 ====

void FUN_800d7154(int param_1)

{
  double dVar1;
  
  zz_006660c_(param_1);
  zz_00d7ba8_(param_1,0x81);
  zz_004cd24_(param_1,0xf);
  *(undefined2 *)(param_1 + 0x18dc) = 0;
  dVar1 = DOUBLE_80438b88;
  if ('\0' < *(char *)(param_1 + 0x1cf0)) {
    *(undefined2 *)(param_1 + 0x18dc) = *(undefined2 *)(param_1 + 0x548);
    *(short *)(param_1 + 0x548) =
         (short)(int)-(FLOAT_80438b84 * *(float *)(param_1 + 0x1dc8) -
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x548) ^ 0x80000000) -
                             dVar1));
  }
  zz_0067458_((double)FLOAT_80438b78,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    if (*(char *)(param_1 + 0x144) == '\0') {
      *(undefined1 *)(param_1 + 0x144) = 1;
      if (*(short *)(param_1 + 1000) == 0x204) {
        zz_00d9674_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0x20d) {
        zz_00d9674_(param_1,1);
      }
    }
  }
  if ((*(char *)(param_1 + 0x1cee) != '\0') || (*(char *)(param_1 + 0x1cf0) < '\0')) {
    if (*(char *)(param_1 + 0x144) == '\x01') {
      *(undefined1 *)(param_1 + 0x144) = 2;
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    if (*(char *)(param_1 + 0x5e4) == ',') {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800d72bc  FUN_800d72bc ====

void FUN_800d72bc(int param_1)

{
  (*(code *)(&PTR_FUN_80433b88)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d72f4  FUN_800d72f4 ====

void FUN_800d72f4(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80438b7c;
  dVar2 = (double)FLOAT_80438b80;
  *(float *)(param_1 + 0x50) = FLOAT_80438b7c;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_00d7104_(param_1);
  return;
}



// ==== 800d734c  FUN_800d734c ====

void FUN_800d734c(int param_1)

{
  (*(code *)(&PTR_FUN_80433b90)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d7384  FUN_800d7384 ====

void FUN_800d7384(int param_1)

{
  zz_004beb8_((double)FLOAT_80438b80,param_1,0xf,2,2,0xffffffff,0xffffffff);
  zz_00d7104_(param_1);
  return;
}



// ==== 800d73d0  FUN_800d73d0 ====

void FUN_800d73d0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_8030faec)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d7424  FUN_800d7424 ====

void FUN_800d7424(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 800d7448  FUN_800d7448 ====

void FUN_800d7448(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}



// ==== 800d746c  FUN_800d746c ====

void FUN_800d746c(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}



// ==== 800d7490  FUN_800d7490 ====

void FUN_800d7490(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 800d74b4  FUN_800d74b4 ====

void FUN_800d74b4(int param_1)

{
  (*(code *)(&PTR_FUN_8030fb00)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d74f0  FUN_800d74f0 ====

void FUN_800d74f0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030fb14)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d7540  FUN_800d7540 ====

void FUN_800d7540(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 3;
  }
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80438b90;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438b80;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,6,1);
  *(float *)(param_1 + 0x80c) = FLOAT_80438b7c;
  return;
}



// ==== 800d7648  FUN_800d7648 ====

void FUN_800d7648(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80438b7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800d76cc  FUN_800d76cc ====

void FUN_800d76cc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    *(undefined2 *)(param_1 + 0x54a) = 0x32;
    *(undefined2 *)(param_1 + 0x54c) = 8;
    if (*(short *)(param_1 + 1000) == 0x20d) {
      *(undefined2 *)(param_1 + 0x548) = 0;
    }
    fVar3 = FLOAT_80438b94;
    fVar2 = FLOAT_80438b7c;
    *(float *)(param_1 + 0x38) = FLOAT_80438b7c;
    fVar4 = FLOAT_80438b98;
    *(float *)(param_1 + 0x3c) = fVar3;
    *(float *)(param_1 + 0x40) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0066530_(param_1,0x2d);
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_80438b80;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800d77b8  FUN_800d77b8 ====

void FUN_800d77b8(int param_1)

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
    if (*(short *)(param_1 + 0x54c) < 2) {
      *(undefined2 *)(param_1 + 0x54c) = 2;
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
  dVar5 = (double)FLOAT_80438b78;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1b01) != '\0') &&
     (*(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -10,
     *(short *)(param_1 + 0x548) < 0)) {
    dVar4 = (double)FLOAT_80438b80;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800d7934  FUN_800d7934 ====

/* WARNING: Removing unreachable block (ram,0x800d7a7c) */
/* WARNING: Removing unreachable block (ram,0x800d7944) */

void FUN_800d7934(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_80438b9c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)
                                   - DOUBLE_80438b88) * dVar3);
  zz_006ed8c_(dVar3,param_1);
  FUN_80067310((double)FLOAT_80438b78,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_80438bac;
  if (DOUBLE_80438ba0 <= (double)*(float *)(param_1 + 0x44)) {
    if (*(char *)(param_1 + 0x1cef) < '\0') {
      dVar3 = (double)*(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_80438bb0);
      zz_004cd24_(param_1,0xf);
      *(float *)(param_1 + 0x1dc8) = (float)dVar3;
    }
    else {
      zz_004cd24_(param_1,0xf);
    }
    zz_00b22f4_(param_1);
  }
  else if (iVar2 == 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_006a474_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80438ba8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800d7a98  FUN_800d7a98 ====

void FUN_800d7a98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438b88) * FLOAT_80438b9c);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438b78,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80438b7c;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_80438ba8 + *(float *)(param_1 + 0x1dc8);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438ba8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800d7ba8  zz_00d7ba8_ ====

undefined4 zz_00d7ba8_(int param_1,uint param_2)

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
                                                0x80000000) - DOUBLE_80438b88) *
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



// ==== 800d7d78  FUN_800d7d78 ====

void FUN_800d7d78(int param_1)

{
  *(undefined1 *)(param_1 + 0x178) = 0;
  *(undefined1 *)(param_1 + 0x174) = 0;
  *(undefined1 *)(param_1 + 0x175) = 0;
  *(undefined1 *)(param_1 + 0x176) = 0;
  *(undefined1 *)(param_1 + 0x177) = 0;
  zz_00d195c_(param_1);
  zz_00c74ec_(param_1,0xe);
  return;
}



// ==== 800d7dcc  FUN_800d7dcc ====

void FUN_800d7dcc(int param_1)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  
  if ('\0' < *(char *)(param_1 + 0x6e9)) {
    pfVar3 = (float *)(param_1 + 0x144);
    pfVar1 = (float *)&DAT_80310920;
    iVar2 = 0;
    do {
      gnt4_PSMTXMultVec_bl((float *)(param_1 + (int)pfVar1[3] * 0x30 + 0x8d4),pfVar1,pfVar3);
      iVar2 = iVar2 + 1;
      pfVar1 = pfVar1 + 4;
      pfVar3 = pfVar3 + 3;
    } while (iVar2 < 4);
  }
  return;
}



// ==== 800d7e6c  FUN_800d7e6c ====

void FUN_800d7e6c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80310960)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800d7eac  FUN_800d7eac ====

uint FUN_800d7eac(int param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  
  iVar3 = 0;
  do {
    uVar1 = param_1 + iVar3;
    if (*(char *)(uVar1 + 0x174) == '\0') {
      *(undefined1 *)(uVar1 + 0x174) = 1;
      bVar2 = zz_00d85f8_(param_1,iVar3);
      uVar1 = (uint)bVar2;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  return uVar1;
}



// ==== 800d7f18  FUN_800d7f18 ====

void FUN_800d7f18(int param_1)

{
  zz_00a2bf8_(param_1,param_1,(undefined4 *)(param_1 + 0x144),(undefined4 *)(param_1 + 0x150),7,0);
  zz_00a2bf8_(param_1,param_1,(undefined4 *)(param_1 + 0x15c),(undefined4 *)(param_1 + 0x168),7,0);
  return;
}



// ==== 800d7f74  FUN_800d7f74 ====

void FUN_800d7f74(int param_1)

{
  (*(code *)(&PTR_FUN_8031096c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800d7fb0  FUN_800d7fb0 ====

void FUN_800d7fb0(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80310978);
  return;
}



// ==== 800d7fd8  FUN_800d7fd8 ====

void FUN_800d7fd8(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,10);
  }
  return;
}



// ==== 800d8024  FUN_800d8024 ====

undefined4 FUN_800d8024(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 800d808c  FUN_800d808c ====

void FUN_800d808c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438bc0;
  fVar1 = FLOAT_80438bb8;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80438bc0) * FLOAT_80438bb8);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_8031098c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d812c  FUN_800d812c ====

void FUN_800d812c(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 800d8150  FUN_800d8150 ====

void FUN_800d8150(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 800d8174  FUN_800d8174 ====

void FUN_800d8174(int param_1)

{
  zz_00f33f4_(param_1);
  return;
}



// ==== 800d8198  FUN_800d8198 ====

void FUN_800d8198(int param_1)

{
  zz_00f3738_(param_1);
  return;
}



// ==== 800d81bc  FUN_800d81bc ====

void FUN_800d81bc(int param_1)

{
  (*(code *)(&PTR_FUN_803109a0)[*(char *)(param_1 + 0x581)])();
  return;
}



