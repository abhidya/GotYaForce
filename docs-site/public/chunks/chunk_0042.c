// ==== 801613d8  FUN_801613d8 ====

void FUN_801613d8(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 801613fc  zz_01613fc_ ====

void zz_01613fc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034c6a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8016144c  FUN_8016144c ====

void FUN_8016144c(int param_1,undefined1 param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043a874;
  fVar1 = FLOAT_8043a870;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a874;
  return;
}



// ==== 80161508  FUN_80161508 ====

void FUN_80161508(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043a874;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_8043a878;
    fVar2 = FLOAT_8043a874;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar3;
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043a87c * *(float *)(param_1 + 0x764)) / fVar3;
    }
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_8043a880;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80161610  FUN_80161610 ====

void FUN_80161610(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    zz_006ed8c_((double)FLOAT_8043a884,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar3 = FLOAT_8043a874;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_8043a888,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043a88c;
    dVar5 = (double)FLOAT_8043a880;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  if (FLOAT_8043a890 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80161704  FUN_80161704 ====

void FUN_80161704(int param_1)

{
  char cVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar2 = (double)FLOAT_8043a880;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ((*(char *)(param_1 + 0x1b03) == '\0') && (*(char *)(param_1 + 0x1d0f) != '\0')) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
           FLOAT_8043a878;
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043a87c * *(float *)(param_1 + 0x764)) / FLOAT_8043a878;
    }
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / *(float *)(param_1 + 0xb4);
  }
  zz_006ed8c_((double)FLOAT_8043a884,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_8043a890 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801618ac  zz_01618ac_ ====

void zz_01618ac_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034c6b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801618fc  FUN_801618fc ====

void FUN_801618fc(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a870;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a884,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a880;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80161a10  FUN_80161a10 ====

void FUN_80161a10(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a884,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a874;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80161adc  FUN_80161adc ====

void FUN_80161adc(int param_1)

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
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a894 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a898;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a894 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a874;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043a89c,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043a8a0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 80161bc0  FUN_80161bc0 ====

void FUN_80161bc0(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  zz_006ed8c_((double)FLOAT_8043a8a4,param_1);
  FUN_80067310((double)FLOAT_8043a898,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a874;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a894 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a894 * -dVar3);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80161ca0  FUN_80161ca0 ====

void FUN_80161ca0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  zz_006ed8c_((double)FLOAT_8043a884,param_1);
  FUN_80067310((double)FLOAT_8043a898,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a898 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80161d7c  zz_0161d7c_ ====

void zz_0161d7c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034c6cc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80161dcc  FUN_80161dcc ====

void FUN_80161dcc(int param_1,undefined1 param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a870;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a8a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a880,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80161ec8  FUN_80161ec8 ====

void FUN_80161ec8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a8a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a874;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_8043a874;
    dVar4 = (double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (dVar4 < (double)*(float *)(param_1 + 0x764))) {
      dVar4 = (double)*(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = (float)((DOUBLE_8043a8b0 * dVar4) / DOUBLE_8043a8b8);
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80161ff0  FUN_80161ff0 ====

void FUN_80161ff0(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043a884,param_1);
  if (FLOAT_8043a8c0 < *(float *)(param_1 + 0x764)) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a874;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a8c0,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801620a0  FUN_801620a0 ====

void FUN_801620a0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_8043a884,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80162224  FUN_80162224 ====

bool FUN_80162224(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_00e2614_(param_1);
  return bVar1;
}



// ==== 80162280  FUN_80162280 ====

void FUN_80162280(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x6e9);
  if (cVar1 == '\x03') {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    zz_001ab6c_(param_1,0x24);
    zz_001ab6c_(param_1,0x23);
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      *(undefined1 *)(param_1 + 0xaf) = 1;
      zz_001ab6c_(param_1,0xb);
      zz_001ab6c_(param_1,10);
    }
    else if ('\0' < cVar1) {
      *(undefined1 *)(param_1 + 0xaf) = 1;
      zz_001ab6c_(param_1,10);
    }
  }
  else if (cVar1 < '\x05') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  *(undefined1 *)(param_1 + 0x6e9) = 0;
  return;
}



// ==== 8016234c  FUN_8016234c ====

void FUN_8016234c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8034c720)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8016238c  FUN_8016238c ====

void FUN_8016238c(int param_1,int param_2)

{
  undefined2 local_8 [4];
  
  local_8[0] = DAT_8043a8c8;
  zz_0099e70_(param_1,*(undefined1 *)((int)local_8 + param_2));
  return;
}



// ==== 801623c0  FUN_801623c0 ====

void FUN_801623c0(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0099e70_(param_1,0x21);
    zz_0099e70_(param_1,0x22);
  }
  return;
}



// ==== 80162418  FUN_80162418 ====

void FUN_80162418(int param_1)

{
  (*(code *)(&PTR_FUN_8034c72c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80162454  FUN_80162454 ====

void FUN_80162454(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_8034c73c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8016249c  FUN_8016249c ====

void FUN_8016249c(int param_1)

{
  (*(code *)(&PTR_FUN_8034c750)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801624d8  FUN_801624d8 ====

void FUN_801624d8(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  fVar1 = FLOAT_8043a8cc;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a8cc;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined1 *)(param_1 + 0x746) = 0;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a8d4,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 80162598  FUN_80162598 ====

void FUN_80162598(int param_1)

{
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80162638  FUN_80162638 ====

void FUN_80162638(int param_1)

{
  float fVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a8e0) * FLOAT_8043a8d8);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a8dc,param_1);
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_8043a8cc;
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a8d0 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if ((((-1 < *(char *)(param_1 + 0x1cef)) && (*(char *)(param_1 + 0x746) == '\0')) ||
      ((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0)) && (*(char *)(param_1 + 0x1cee) == '\0')) {
    return;
  }
  *(float *)(param_1 + 0x4c) = FLOAT_8043a8cc;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 80162780  FUN_80162780 ====

void FUN_80162780(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_8034c75c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801627c8  FUN_801627c8 ====

void FUN_801627c8(int param_1)

{
  (*(code *)(&PTR_FUN_8034c770)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80162804  FUN_80162804 ====

void FUN_80162804(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  
  fVar5 = FLOAT_8043a8f0;
  fVar4 = FLOAT_8043a8ec;
  fVar3 = FLOAT_8043a8e8;
  fVar2 = FLOAT_8043a8cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  dVar6 = (double)FLOAT_8043a8d4;
  *(float *)(param_1 + 0x55c) = fVar4;
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x38) = fVar5 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a8cc;
  zz_00b2190_(param_1,0);
  FUN_800061a8(param_1,0x10);
  zz_01628d4_(param_1);
  return;
}



// ==== 801628d4  zz_01628d4_ ====

void zz_01628d4_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bool bVar5;
  double dVar6;
  float afStack_18 [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  dVar6 = gnt4_PSVECMag_bl(afStack_18);
  if ((((double)*(float *)(param_1 + 0x5f8) *
        DOUBLE_8043a8f8 * (double)*(float *)(param_1 + 0x44) * (double)*(float *)(param_1 + 0x5f4)
        <= dVar6) ||
      (fVar2 = *(float *)(param_1 + 0x560) + *(float *)(param_1 + 0x1dc8),
      bVar5 = fVar2 <= FLOAT_8043a900, *(float *)(param_1 + 0x560) = fVar2, bVar5)) &&
     (PTR_DAT_80433934[0x1f] == '\0')) {
    zz_004cd24_(param_1,0xf);
    zz_0066ac0_(param_1,0);
    zz_0066e40_(param_1,2);
    dVar6 = (double)FLOAT_8043a8d0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x38);
    FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
    iVar4 = zz_00677b0_(param_1);
    if (iVar4 != 0) {
      *(float *)(param_1 + 0x48) = FLOAT_8043a8cc;
    }
    if (FLOAT_8043a8cc < *(float *)(param_1 + 0x55c)) {
      *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
    }
    fVar3 = FLOAT_8043a904;
    fVar2 = FLOAT_8043a8cc;
    if (*(float *)(param_1 + 0x55c) <= FLOAT_8043a8cc) {
      if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) goto LAB_80162a6c;
      if ((*(uint *)(param_1 + 0x5bc) & 0x100) != 0) {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        *(float *)(param_1 + 0x694) = fVar3 + *(float *)(param_1 + 0x1dc8);
        if (iVar4 == 0) {
          iVar4 = zz_0069210_(param_1);
        }
        else {
          iVar4 = zz_0069038_(param_1);
        }
        if (iVar4 != 0) {
          return;
        }
        zz_006a5a4_(param_1);
        return;
      }
    }
    fVar3 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar3;
    if (fVar2 < fVar3) {
      if (*(float *)(param_1 + 0x44) <= FLOAT_8043a8f0) {
        return;
      }
      zz_00b22f4_(param_1);
      zz_00f0104_(param_1,0x18,2);
      return;
    }
  }
LAB_80162a6c:
  dVar6 = (double)FLOAT_8043a8d4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80162ae4  FUN_80162ae4 ====

void FUN_80162ae4(int param_1)

{
  float fVar1;
  int iVar2;
  float afStack_28 [3];
  float afStack_1c [6];
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a8cc;
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_8043a908,param_1);
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (FLOAT_8043a8f0 < *(float *)(param_1 + 0x44)) {
      gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),(float *)&DAT_8034c77c,afStack_1c);
      gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),(float *)&DAT_8034c788,afStack_28);
      zz_00b2544_(param_1,afStack_1c,afStack_28);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a904 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80162bf4  FUN_80162bf4 ====

void FUN_80162bf4(int param_1)

{
  (*(code *)(&PTR_FUN_8034c794)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80162c30  FUN_80162c30 ====

void FUN_80162c30(int param_1)

{
  (*(code *)(&PTR_FUN_8034c7a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80162c6c  FUN_80162c6c ====

void FUN_80162c6c(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a90c;
  fVar1 = FLOAT_8043a8cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = 5;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043a900;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a908,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a8d4,param_1,0xf,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 80162d40  FUN_80162d40 ====

void FUN_80162d40(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a8cc;
  if (*(char *)(param_1 + 0x1cef) < '\x01') {
    *(undefined2 *)(param_1 + 0x18dc) = 0;
  }
  else {
    *(short *)(param_1 + 0x18dc) =
         (short)(int)-(FLOAT_8043a910 * *(float *)(param_1 + 0x1dc8) -
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                             DOUBLE_8043a8e0));
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(float *)(param_1 + 0x558) = FLOAT_8043a90c;
      zz_00f036c_(param_1,10);
      if (0 < *(short *)(param_1 + 0x54a)) {
        *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
        zz_0099e70_(param_1,0x23);
        zz_0099e70_(param_1,0x24);
      }
    }
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x5ac));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a908,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a914;
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
  }
  return;
}



// ==== 80162e9c  FUN_80162e9c ====

void FUN_80162e9c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a8d0,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a8cc;
  if ((iVar3 == 0) || (-1 < *(char *)(param_1 + 0x1cef))) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_8043a90c + *(float *)(param_1 + 0x1dc8);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a8d0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80162f78  zz_0162f78_ ====

void zz_0162f78_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x902) || (sVar1 == 0x909)) || (sVar1 == 0x907)) || (sVar1 == 0x90c)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_801630a0;
    *(code **)(puVar2 + 0x10c) = FUN_801633a4;
    puVar2[0x144] = 0;
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
  }
  return;
}



// ==== 801630a0  FUN_801630a0 ====

void FUN_801630a0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8034d43c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801630f4  FUN_801630f4 ====

void FUN_801630f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(undefined1 *)(param_9 + 0x89) = 7;
  fVar1 = FLOAT_8043a918;
  *(undefined4 *)(param_9 + 100) = DAT_8034d420;
  *(undefined4 *)(param_9 + 0x68) = DAT_8034d424;
  dVar5 = (double)DAT_8034d428;
  *(float *)(param_9 + 0x6c) = DAT_8034d428;
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
                      *(int *)(&DAT_8034d42c + *(char *)(param_9 + 0x11) * 4),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_8034d42c + *(char *)(param_9 + 0x11) * 4);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a91c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined1 *)(param_9 + 0x144) = 0;
  zz_0163238_(param_9);
  return;
}



// ==== 80163238  zz_0163238_ ====

void zz_0163238_(int param_1)

{
  char cVar1;
  int iVar2;
  float afStack_48 [3];
  float afStack_3c [13];
  
  iVar2 = *(int *)(param_1 + 0x90);
  cVar1 = *(char *)(iVar2 + 0x144);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if ((-1 < cVar1) && (*(char *)(param_1 + 0x144) != '\0')) {
        *(char *)(param_1 + 0x144) = cVar1;
        zz_0089444_(param_1);
        *(code **)(param_1 + 0x100) = FUN_80047aa4;
        zz_0089100_(param_1,(int)*(char *)(iVar2 + 0x3e4) + 0x10,1);
        *(undefined1 *)(param_1 + 0x84) = 0x41;
        *(undefined1 *)(param_1 + 0x89) = 7;
        *(undefined4 *)(param_1 + 100) = DAT_8034d420;
        *(undefined4 *)(param_1 + 0x68) = DAT_8034d424;
        *(undefined4 *)(param_1 + 0x6c) = DAT_8034d428;
        *(undefined2 *)(param_1 + 0x70) = 0;
        *(undefined2 *)(param_1 + 0x72) = 0;
        *(undefined2 *)(param_1 + 0x74) = 0;
      }
    }
    else if ((cVar1 < '\x03') && (*(char *)(param_1 + 0x144) != '\x02')) {
      *(char *)(param_1 + 0x144) = cVar1;
      *(undefined1 *)(param_1 + 0x19) = 0;
      gnt4_PSMTXMultVec_bl
                ((float *)(*(int *)(param_1 + 0x90) + 0xa24),(float *)&DAT_8034d420,afStack_48);
      gnt4_PSMTXInverse_bl((float *)(*(int *)(param_1 + 0x90) + 0x8d4),afStack_3c);
      gnt4_PSMTXMultVec_bl(afStack_3c,afStack_48,(float *)(param_1 + 0x14c));
    }
  }
  if (*(char *)(param_1 + 0x144) == '\x02') {
    zz_0163410_(param_1);
  }
  return;
}



// ==== 80163384  FUN_80163384 ====

void FUN_80163384(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801633a4  FUN_801633a4 ====

void FUN_801633a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
    uVar2 = 0x47;
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



// ==== 80163410  zz_0163410_ ====

void zz_0163410_(int param_1)

{
  (**(code **)(&DAT_80434740 + *(char *)(param_1 + 0x19) * 4))();
  return;
}



// ==== 80163448  FUN_80163448 ====

void FUN_80163448(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  zz_0089444_(param_1);
  *(code **)(param_1 + 0x100) = FUN_80163518;
  zz_0089100_(param_1,1,1);
  fVar2 = FLOAT_8043a920;
  fVar1 = FLOAT_8043a918;
  *(undefined4 *)(param_1 + 100) = DAT_8034d420;
  *(undefined4 *)(param_1 + 0x68) = DAT_8034d424;
  *(undefined4 *)(param_1 + 0x6c) = DAT_8034d428;
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(float *)(param_1 + 0x158) = fVar2;
  *(float *)(param_1 + 0x15c) = fVar1;
  zz_01634e4_(param_1);
  return;
}



// ==== 801634e4  zz_01634e4_ ====

void zz_01634e4_(int param_1)

{
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x146);
  *(short *)(param_1 + 0x146) = *(short *)(param_1 + 0x146) + 0xb0;
  if (*(short *)(param_1 + 0x146) < 0xc01) {
    return;
  }
  *(undefined2 *)(param_1 + 0x146) = 0xc00;
  return;
}



// ==== 80163518  FUN_80163518 ====

/* WARNING: Removing unreachable block (ram,0x80163634) */
/* WARNING: Removing unreachable block (ram,0x80163544) */

void FUN_80163518(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float local_84;
  undefined4 local_80;
  float local_7c;
  float afStack_78 [12];
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  longlong local_10;
  
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + 0x8d4),afStack_48);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043a924 *
                                     (double)((longlong)
                                              (double)(short)*(undefined4 *)(param_1 + 0x148) *
                                             0x3ff0000000000000)),afStack_78,0x79);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_78,afStack_48);
  fVar3 = FLOAT_8043a92c;
  fVar2 = FLOAT_8043a928;
  local_84 = *(float *)(param_1 + 0x14c) * *(float *)(param_1 + 0x158);
  local_80 = *(undefined4 *)(param_1 + 0x150);
  local_7c = *(float *)(param_1 + 0x154) * *(float *)(param_1 + 0x15c);
  *(float *)(param_1 + 0x158) = *(float *)(param_1 + 0x158) + FLOAT_8043a928;
  *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x15c) + fVar2;
  if (fVar3 < *(float *)(param_1 + 0x158)) {
    *(float *)(param_1 + 0x158) = fVar3;
  }
  if (FLOAT_8043a92c < *(float *)(param_1 + 0x15c)) {
    *(float *)(param_1 + 0x15c) = FLOAT_8043a92c;
  }
  gnt4_PSMTXMultVec_bl(afStack_48,&local_84,&local_84);
  dVar4 = DOUBLE_8043a938;
  local_18 = 0x43300000;
  *(float *)(param_1 + 0x120) = local_84;
  fVar2 = FLOAT_8043a930;
  *(undefined4 *)(param_1 + 0x130) = local_80;
  *(float *)(param_1 + 0x140) = local_7c;
  uStack_14 = *(uint *)(param_1 + 0x148) ^ 0x80000000;
  iVar1 = (int)((float)((double)CONCAT44(0x43300000,uStack_14) - dVar4) + fVar2);
  local_10 = (longlong)iVar1;
  *(int *)(param_1 + 0x148) = iVar1;
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043a924 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x146) *
                                             0x3ff0000000000000)),afStack_48,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
  return;
}



// ==== 80163670  zz_0163670_ ====

void zz_0163670_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x806) || (sVar1 == 0x809)) || (sVar1 == 0x80f)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x13] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80163790;
    *(code **)(puVar2 + 0x10c) = FUN_8016393c;
    puVar2[0x144] = 0;
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
  }
  return;
}



// ==== 80163790  FUN_80163790 ====

void FUN_80163790(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8034d450)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801637e4  FUN_801637e4 ====

void FUN_801637e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  int iVar3;
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
  fVar1 = FLOAT_8043a940;
  dVar6 = (double)FLOAT_8043a940;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar2 = FLOAT_8043a944;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined1 *)(param_9 + 0x89) = 0xc;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  iVar5 = zz_0006f98_(iVar5);
  uVar7 = zz_0007030_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80434748)[*(char *)(param_9 + 0x13)],iVar5 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)(char)(&DAT_80434748)[*(char *)(param_9 + 0x13)];
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a948,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0163908_();
  return;
}



// ==== 80163908  zz_0163908_ ====

void zz_0163908_(void)

{
  return;
}



// ==== 8016391c  FUN_8016391c ====

void FUN_8016391c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8016393c  FUN_8016393c ====

void FUN_8016393c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x144) == '\0') {
    if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
      iVar1 = *(int *)(param_9 + 0xe0);
      uVar2 = 1;
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 801639c0  zz_01639c0_ ====

bool zz_01639c0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x55;
    *(code **)(puVar1 + 0xc) = FUN_80163ad0;
    *(code **)(puVar1 + 0x10c) = FUN_801642c8;
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
    *(undefined1 *)(param_1 + 0x144) = 1;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 80163ad0  FUN_80163ad0 ====

void FUN_80163ad0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(iVar1 + 0x18) || (*(short *)(iVar1 + 1000) != *(short *)(param_1 + 0x94)))
     )) {
    *(undefined1 *)(iVar1 + 0x144) = 0;
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8034d4c8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80163b70  FUN_80163b70 ====

void FUN_80163b70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  undefined *puVar10;
  int iVar11;
  undefined8 uVar12;
  
  puVar10 = &DAT_8034d490;
  puVar8 = &DAT_8034d460;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar11 = *(int *)(param_9 + 0x90);
  iVar9 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar7 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 3;
  iVar5 = iVar9 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar4 = iVar7;
  zz_0089100_(param_9,0,1);
  uVar1 = DAT_802b0cb8;
  puVar6 = &DAT_802b0cb4;
  *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
  uVar2 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar1;
  *(undefined4 *)(param_9 + 0xa4) = uVar2;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar11 + *(short *)(&DAT_8034d462 + iVar5) * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fcb2b9c),(float *)(param_9 + 0x20));
  iVar3 = zz_0083d60_(param_9,iVar11,(int)*(short *)(&DAT_8034d462 + iVar5));
  if (iVar3 != 0) {
    *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar11 + 0x8dc);
    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(iVar11 + 0x8ec);
    *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar11 + 0x8fc);
  }
  uVar12 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8034d4a0 + iVar7),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8034d4a0 + iVar7);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8034d492 + iVar7);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8034d494 + iVar7);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8034d496 + iVar7);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(&DAT_8034d4a4 + iVar7);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar3 = zz_0006f98_(iVar11);
  zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8034d460 + iVar5),puVar6,iVar4,puVar8,
              iVar9,puVar10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar4 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8034d490 + iVar7));
  if (iVar4 == 0) {
    *(undefined1 *)(iVar11 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x28);
    zz_00a2bf8_(iVar11,param_9,(undefined4 *)(param_9 + 0x144),(undefined4 *)(param_9 + 0x150),1,0);
    zz_00f036c_(param_9,0xdb);
  }
  return;
}



// ==== 80163d90  FUN_80163d90 ====

void FUN_80163d90(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_0163ffc_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_0163e34_(param_1);
  }
  iVar2 = *(char *)(param_1 + 0x13) * 0x18;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_8034d462 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fcb2b9c),(float *)(param_1 + 0x144));
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 80163e34  zz_0163e34_ ====

void zz_0163e34_(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
      dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x150));
      if ((double)FLOAT_8043a950 < dVar3) {
        dVar4 = 1.0 / SQRT(dVar3);
        dVar4 = DOUBLE_8043a958 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043a960);
        dVar4 = DOUBLE_8043a958 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_8043a960);
        dVar3 = (double)(float)(dVar3 * DOUBLE_8043a958 * dVar4 *
                                        -(dVar3 * dVar4 * dVar4 - DOUBLE_8043a960));
      }
      if (dVar3 < (double)FLOAT_8043a968) {
        if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x168)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_8034d4a8 + iVar1);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x168);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_8034d49c + iVar1),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_8034d498 + iVar1),param_1,
                     (char)*(undefined2 *)(&DAT_8034d494 + iVar1));
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x168));
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_0084170_(param_1);
          if (iVar1 != 0) {
            zz_0164174_(param_1);
          }
        }
        else {
          zz_0164174_(param_1);
        }
      }
      else {
        zz_0164174_(param_1);
      }
    }
    else {
      zz_0164174_(param_1);
    }
  }
  else {
    zz_0164174_(param_1);
  }
  return;
}



// ==== 80163ffc  zz_0163ffc_ ====

void zz_0163ffc_(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar4 = *(int *)(param_1 + 0x90);
  local_18 = *(float *)(iVar4 + 0xb20);
  local_14 = *(undefined4 *)(iVar4 + 0xb30);
  local_10 = *(undefined4 *)(iVar4 + 0xb40);
  dVar5 = gnt4_PSVECSquareDistance_bl(&local_18,(float *)(param_1 + 0x20));
  if ((double)FLOAT_8043a950 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_8043a958 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_8043a960);
    dVar6 = DOUBLE_8043a958 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_8043a960);
    dVar5 = (double)(float)(dVar5 * DOUBLE_8043a958 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_8043a960));
  }
  if ((double)FLOAT_8043a96c < dVar5) {
    dVar5 = (double)FLOAT_8043a970;
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
    uVar3 = *(undefined4 *)(param_1 + 0x38);
    uVar2 = *(undefined4 *)(param_1 + 0x3c);
    uVar1 = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x15c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x160);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x164);
    zz_006c440_(dVar5,param_1,&local_18);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x38) = uVar3;
    *(undefined4 *)(param_1 + 0x3c) = uVar2;
    *(undefined4 *)(param_1 + 0x40) = uVar1;
  }
  else {
    *(undefined1 *)(iVar4 + 0x144) = 0;
    zz_00f036c_(param_1,0xdc);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80164174  zz_0164174_ ====

void zz_0164174_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar5 = *(int *)(param_1 + 0x90);
  bVar1 = *(byte *)(param_1 + 0x11);
  local_1c = *(float *)(iVar5 + 0xb20);
  local_18 = *(undefined4 *)(iVar5 + 0xb30);
  local_14 = *(undefined4 *)(iVar5 + 0xb40);
  gnt4_PSVECSubtract_bl(&local_1c,(float *)(param_1 + 0x20),&local_28);
  dVar6 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar2 = DAT_802b0cac;
  if (dVar6 <= (double)FLOAT_8043a950) {
    *(undefined4 *)(param_1 + 0x15c) = DAT_802b0ca8;
    uVar3 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x160) = uVar2;
    *(undefined4 *)(param_1 + 0x164) = uVar3;
  }
  else {
    *(float *)(param_1 + 0x15c) = local_28;
    *(undefined4 *)(param_1 + 0x160) = local_24;
    *(undefined4 *)(param_1 + 0x164) = local_20;
  }
  pfVar4 = (float *)(param_1 + 0x15c);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  if (*(float *)(&DAT_8034d4a4 + (uint)bVar1 * 0x1c) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8034d4a4 + (uint)bVar1 * 0x1c);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar4,pfVar4);
  *(undefined1 *)(param_1 + 0x19) = 1;
  zz_008aff0_(param_1);
  *(undefined1 *)(iVar5 + 0x144) = 2;
  return;
}



// ==== 8016429c  FUN_8016429c ====

void FUN_8016429c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 801642a8  FUN_801642a8 ====

void FUN_801642a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801642c8  FUN_801642c8 ====

void FUN_801642c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80164424  FUN_80164424 ====

void FUN_80164424(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a980) * FLOAT_8043a978);
  }
  return;
}



// ==== 80164488  FUN_80164488 ====

void FUN_80164488(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8034d518)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801644c8  FUN_801644c8 ====

void FUN_801644c8(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x1e);
  return;
}



// ==== 801644f4  FUN_801644f4 ====

void FUN_801644f4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x1d);
  return;
}



// ==== 80164520  FUN_80164520 ====

void FUN_80164520(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x1e);
  zz_001ab6c_(param_1,0x1d);
  return;
}



// ==== 80164570  FUN_80164570 ====

bool FUN_80164570(int param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  bVar2 = false;
  if (iVar1 != 0) {
    bVar2 = zz_00fbc64_(param_1,2);
  }
  return bVar2;
}



// ==== 801645bc  FUN_801645bc ====

void FUN_801645bc(int param_1)

{
  zz_016c7ec_(param_1,0,0);
  return;
}



// ==== 801645e4  FUN_801645e4 ====

void FUN_801645e4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x26);
  zz_001ab6c_(param_1,0x25);
  return;
}



// ==== 80164628  FUN_80164628 ====

void FUN_80164628(int param_1)

{
  (*(code *)(&PTR_FUN_8034d538)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80164664  FUN_80164664 ====

void FUN_80164664(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a980) * FLOAT_8043a978);
  (*(code *)(&PTR_FUN_8034d544)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801646d8  FUN_801646d8 ====

void FUN_801646d8(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80164700  FUN_80164700 ====

void FUN_80164700(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 80164728  FUN_80164728 ====

void FUN_80164728(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80164750  FUN_80164750 ====

void FUN_80164750(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034d598)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801647a0  FUN_801647a0 ====

void FUN_801647a0(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a988;
  zz_006d144_(param_1,0xc0);
  dVar3 = (double)FLOAT_8043a98c;
  *(undefined1 *)(param_1 + 0x6ea) = 6;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a990;
  return;
}



// ==== 80164878  FUN_80164878 ====

void FUN_80164878(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a990;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a994;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_8043a990;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043a994;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80164968  FUN_80164968 ====

void FUN_80164968(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a990;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a998,param_1), uVar3 != 0)) {
    fVar2 = FLOAT_8043a99c;
    fVar1 = FLOAT_8043a994;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80164a14  FUN_80164a14 ====

void FUN_80164a14(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a9a0;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006ed8c_((double)FLOAT_8043a9a4,param_1);
  if (FLOAT_8043a990 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cf2) != '\0') {
    if (*(float *)(param_1 + 0x558) <= FLOAT_8043a990) {
      zz_004beb8_((double)FLOAT_8043a98c,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                  0xffffffff);
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80164b10  FUN_80164b10 ====

void FUN_80164b10(int param_1)

{
  (*(code *)(&PTR_FUN_8034d5a8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80164b4c  FUN_80164b4c ====

void FUN_80164b4c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034d5bc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80164b9c  FUN_80164b9c ====

void FUN_80164b9c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a994;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 3;
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043a990;
  *(float *)(param_1 + 0x50) = FLOAT_8043a990;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a9a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a98c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,6,1);
  return;
}



// ==== 80164ce0  FUN_80164ce0 ====

void FUN_80164ce0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a9a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043a990;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_8043a98c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80164dac  FUN_80164dac ====

void FUN_80164dac(int param_1)

{
  float fVar1;
  double dVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a9a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a994;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a9ac * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x18da));
    fVar1 = FLOAT_8043a990;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a9ac * -dVar2);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
    zz_00b2190_(param_1,0);
    *(float *)(param_1 + 0x80c) = FLOAT_8043a990;
    FUN_800061a8(param_1,0x11);
  }
  return;
}



// ==== 80164e8c  FUN_80164e8c ====

void FUN_80164e8c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  FUN_80067310((double)FLOAT_8043a9b0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a990;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  dVar4 = DOUBLE_8043a9b8;
  fVar3 = FLOAT_8043a9b4;
  if ((fVar1 <= fVar2) || (((int)*(char *)(param_1 + 0x1d9) & 0x90U) != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
    fVar1 = FLOAT_8043a9c0;
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) + fVar3;
      *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
      *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fVar1;
      zz_00107a0_(param_1,0xd);
    }
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80164f98  FUN_80164f98 ====

void FUN_80164f98(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a980) * FLOAT_8043a978);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a978,param_1);
  FUN_80067310((double)FLOAT_8043a9b0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_8043a990;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_8043a98c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffb;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x44) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801650a8  FUN_801650a8 ====

void FUN_801650a8(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a9b0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a9c4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043a9c4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80165184  zz_0165184_ ====

void zz_0165184_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x20;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 3;
    *(code **)(puVar1 + 0xc) = FUN_8016528c;
    *(code **)(puVar1 + 0x10c) = FUN_80165584;
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



// ==== 8016528c  FUN_8016528c ====

void FUN_8016528c(int param_1)

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
  (*(code *)(&PTR_FUN_8034e568)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80165318  FUN_80165318 ====

void FUN_80165318(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  undefined8 uVar3;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x28;
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
    *(code **)(param_9 + 0x100) = FUN_801654a8;
    uVar3 = zz_0089100_(param_9,1,1);
    zz_0165608_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801653dc  FUN_801653dc ====

void FUN_801653dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  short sVar2;
  char cVar3;
  
  sVar2 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar2;
  if (sVar2 == 0) {
    cVar3 = *(char *)(*(int *)(param_9 + 0x8c) + 0x6f3) + -1;
    *(char *)(*(int *)(param_9 + 0x8c) + 0x6f3) = cVar3;
    if ('\0' < cVar3) {
      zz_0165608_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  iVar1 = zz_0165728_(param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8016544c  FUN_8016544c ====

void FUN_8016544c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80165460  FUN_80165460 ====

void FUN_80165460(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801654a8  FUN_801654a8 ====

void FUN_801654a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  int iVar2;
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
  float afStack_48 [13];
  
  iVar2 = *(char *)(param_9 + 0x11) * 0x18;
  zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + (char)(&DAT_8034e552)[iVar2] * 0x30 + 0x8d4),
              (float *)(param_9 + 0x114),(float *)(iVar2 + -0x7fcb1aac));
  iVar6 = 0;
  iVar7 = 0;
  iVar2 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar6) != 0) {
      iVar5 = *(int *)(param_9 + 0x54) + iVar7;
      sVar1 = *(short *)(iVar5 + 0x24);
      iVar4 = (int)sVar1;
      zz_00457d4_('z',(float *)(param_9 + 0x114),afStack_48,sVar1);
      pfVar3 = (float *)(iVar5 + 0x10);
      uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar3);
      zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0xe0),afStack_48,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,
                  in_r10);
    }
    iVar7 = iVar7 + 0x28;
    iVar2 = iVar2 + 4;
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 80165584  FUN_80165584 ====

void FUN_80165584(int param_1)

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



// ==== 80165608  zz_0165608_ ====

void zz_0165608_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & 1 << iVar6) == 0) {
      iVar4 = *(int *)(param_9 + 0x54);
      iVar1 = (int)*(char *)(param_9 + 0x11);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar6);
      *(undefined2 *)(param_9 + 0x1e) = 10;
      piVar5 = (int *)(iVar4 + iVar6 * 0x28);
      *(undefined2 *)(piVar5 + 8) = 0;
      *(short *)((int)piVar5 + 0x22) = (short)(char)(&DAT_8034e553)[iVar1 * 0x18];
      uVar2 = zz_00055fc_();
      *(short *)(piVar5 + 9) = (short)(uVar2 << 8);
      zz_0018f88_(piVar5,(int)(&PTR_DAT_8034e560)[iVar1 * 6],(float *)(piVar5 + 4));
      uVar7 = zz_0019338_(piVar5 + 2,(int)(&PTR_DAT_8034e564)[iVar1 * 6],(float *)(piVar5 + 7));
      iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
      iVar6 = iVar6 * 4 + 0xe0;
      zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                  *(int *)(param_9 + iVar6),
                  (int)(char)(&DAT_8034e550)[(int)*(char *)(param_9 + 0x88) + iVar1 * 0x18],iVar4,
                  in_r7,in_r8,in_r9,in_r10);
      zz_0007cac_((double)(float)piVar5[7],*(int *)(param_9 + iVar6));
      iVar6 = (int)*(char *)(param_9 + 0x13);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 80165728  zz_0165728_ ====

int zz_0165728_(int param_1)

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
    iVar5 = iVar5 + 0x28;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 801657f0  zz_01657f0_ ====

void zz_01657f0_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0x56;
      puVar1[0x11] = 0;
      puVar1[0x13] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_80165900;
      *(code **)(puVar1 + 0x10c) = FUN_80165f24;
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
  } while (iVar2 < 8);
  return;
}



// ==== 80165900  FUN_80165900 ====

void FUN_80165900(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8034e644)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80165950  FUN_80165950 ====

void FUN_80165950(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  float local_58;
  float local_54;
  undefined4 local_50;
  float afStack_4c [2];
  float local_44;
  float local_34;
  undefined4 local_24;
  
  iVar5 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  *(undefined2 *)(param_9 + 0x1c) = 300;
  iVar2 = -((int)(char)(&DAT_8034e57b)[iVar4] >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_8034e57b)[iVar4]);
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + (char)(&DAT_8034e57a)[iVar4] * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcb1a74),(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8034e5a4 + iVar4);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_8034e5a8 + iVar4);
    *(float *)(param_9 + 0xb4) = *(float *)(&DAT_8034e588 + iVar4) * *(float *)(iVar5 + 0xb4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8034e57e + iVar4);
    *(undefined2 *)(param_9 + 0x70) = 0x4000;
    *(undefined2 *)(param_9 + 0x72) = 0;
    uVar3 = zz_00055fc_();
    *(short *)(param_9 + 0x74) = (short)(uVar3 << 8);
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(&DAT_8034e5ac + iVar4);
    *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x164) = *(undefined4 *)(param_9 + 0x28);
    zz_00457d4_('y',(float *)(iVar5 + (char)(&DAT_8034e57a)[iVar4] * 0x30 + 0x8d4),afStack_4c,
                (ushort)*(byte *)(param_9 + 0x13) << 0xd);
    dVar7 = (double)local_34;
    local_58 = local_44;
    local_54 = local_34;
    local_50 = local_24;
    *(float *)(param_9 + 0x158) = FLOAT_8043a9c8;
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x158),&local_58,&local_58);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_58,(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_9 + 0x28);
    *(code **)(param_9 + 0x100) = FUN_80047f60;
    uVar6 = zz_0089100_(param_9,0,1);
    *(undefined1 *)(param_9 + 0x84) = 0x1a;
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_8034e578)[iVar4],
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 80165b40  FUN_80165b40 ====

void FUN_80165b40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  bool bVar6;
  int iVar5;
  short sVar7;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar8;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [3];
  float afStack_40 [2];
  float local_38;
  undefined4 local_34;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c);
  if (*(float *)(param_9 + 0x168) < *(float *)(param_9 + 0x44)) {
    *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x168);
  }
  gnt4_PSVECSubtract_bl((float *)(param_9 + 0x15c),(float *)(param_9 + 0x20),&local_58);
  gnt4_PSMTXIdentity_bl(afStack_40);
  bVar6 = zz_0045ef4_(afStack_40,5,&local_58,&DAT_802b0cb4);
  if (!bVar6) {
    local_34 = *(undefined4 *)(param_9 + 0x20);
    local_24 = *(undefined4 *)(param_9 + 0x24);
    local_14 = *(undefined4 *)(param_9 + 0x28);
    zz_00457d4_('y',afStack_40,afStack_40,0x4000);
    param_2 = (double)local_38;
    local_58 = local_38;
    local_54 = local_28;
    local_50 = local_18;
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),&local_58,&local_58);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_58,afStack_4c);
    gnt4_PSVECSubtract_bl(afStack_4c,(float *)(param_9 + 0x15c),&local_58);
    gnt4_PSVECNormalize_bl(&local_58,&local_58);
    *(float *)(param_9 + 0x158) = *(float *)(param_9 + 0x158) + *(float *)(&DAT_8034e5b0 + iVar4);
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x158),&local_58,&local_58);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x15c),&local_58,(float *)(param_9 + 0x20));
  }
  if (*(int *)(param_9 + 200) != 0) {
    fVar1 = *(float *)(param_9 + 0x24);
    if (*(float *)(*(int *)(param_9 + 200) + 0x68) < fVar1) {
      *(float *)(param_9 + 0x24) = fVar1 - FLOAT_8043a9cc;
    }
    else {
      *(float *)(param_9 + 0x24) = fVar1 + FLOAT_8043a9cc;
    }
  }
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x2000;
  uVar2 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0xc0) = uVar2;
  *(undefined4 *)(param_9 + 0x60) = uVar2;
  *(undefined4 *)(param_9 + 0x5c) = uVar2;
  *(undefined4 *)(param_9 + 0x58) = uVar2;
  iVar5 = zz_0083714_(param_9);
  sVar7 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar7;
  uVar3 = countLeadingZeros((int)sVar7);
  if (iVar5 == 0 && ((1 << (uVar3 & 0x1f) | 1U >> 0x20 - (uVar3 & 0x1f)) & 1) == 0) {
    if (((((int)*(char *)(param_9 + 0x1d9) & 0x80U) != 0) ||
        (((int)*(char *)(param_9 + 0x1d9) & 2U) != 0)) || (iVar4 = zz_0084170_(param_9), iVar4 != 0)
       ) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x19) = 1;
      zz_008aff0_(param_9);
    }
  }
  else {
    iVar5 = (int)(char)(&DAT_8034e579)[iVar4];
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x19) = 0;
    zz_008aff0_(param_9);
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_8034e63a + iVar5 * 0xc);
    zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_8034e63c)[iVar5 * 3],
                (float *)(param_9 + 0x58));
    zz_0019338_((int *)(param_9 + 0x14c),(int)(&PTR_DAT_8034e640)[iVar5 * 3],
                (float *)(param_9 + 0x154));
    uVar8 = gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                                (float *)(param_9 + 0x58));
    iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xe0),(float *)(int)*(short *)(&DAT_8034e638 + iVar5 * 0xc),
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)*(float *)(param_9 + 0x154),*(int *)(param_9 + 0xe0));
  }
  zz_00833ec_(param_9);
  zz_0083610_(param_9,(float *)(param_9 + 0x168));
  return;
}



// ==== 80165e18  FUN_80165e18 ====

void FUN_80165e18(int param_1)

{
  (*(code *)(&PTR_FUN_80434750)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80165e50  FUN_80165e50 ====

void FUN_80165e50(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < *(short *)(param_1 + 0x1e)) {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x2000;
    zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
    zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x154))
    ;
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),
                        (float *)(param_1 + 0x58));
    zz_0007cac_((double)*(float *)(param_1 + 0x154),*(int *)(param_1 + 0xe0));
  }
  else {
    zz_0165ef0_(param_1);
  }
  return;
}



// ==== 80165ef0  zz_0165ef0_ ====

void zz_0165ef0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80165f04  FUN_80165f04 ====

void FUN_80165f04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80165f24  FUN_80165f24 ====

void FUN_80165f24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80166060  FUN_80166060 ====

void FUN_80166060(int param_1)

{
  zz_009880c_(param_1);
  return;
}



// ==== 801660d0  FUN_801660d0 ====

void FUN_801660d0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80434758)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80166110  FUN_80166110 ====

void FUN_80166110(int param_1)

{
  (*(code *)(&PTR_FUN_8034e698)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8016614c  FUN_8016614c ====

void FUN_8016614c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043a9d8;
  fVar1 = FLOAT_8043a9d0;
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_8043a9d8) * FLOAT_8043a9d0);
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) - dVar2
                           ) * fVar1);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8034e6a8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801661f8  FUN_801661f8 ====

void FUN_801661f8(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_0166250__8034e6c0)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 80166250  zz_0166250_ ====

void zz_0166250_(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  
  fVar2 = FLOAT_8043a9e4;
  fVar1 = FLOAT_8043a9e0;
  uVar3 = 0;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar3 = 0xe;
  }
  (*(code *)(&PTR_FUN_8034e6cc)[*(char *)(param_1 + 0x581)])(param_1,uVar3);
  return;
}



// ==== 801662c4  FUN_801662c4 ====

void FUN_801662c4(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043a9e8,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\x02') || (*(char *)(param_1 + 0x1d0d) != param_2)) {
    zz_004beb8_((double)FLOAT_8043a9e8,param_1,2,2,param_2,4,2);
  }
  return;
}



// ==== 80166350  FUN_80166350 ====

void FUN_80166350(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    iVar1 = 3;
    if (*(char *)(param_1 + 0x5db) == '\x02') {
      iVar1 = 0;
    }
    zz_004beb8_((double)FLOAT_8043a9e8,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801663c4  FUN_801663c4 ====

void FUN_801663c4(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x543) < '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 4;
    zz_006a3d0_(param_1,'\0',4,2);
  }
  else {
    zz_004beb8_((double)FLOAT_8043a9e8,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
    if ((((int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f) <= (int)*(char *)(param_1 + 0x747))
        || ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0)) && ((*(uint *)(param_1 + 0x5e0) & 2) == 0)) {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80166478  FUN_80166478 ====

void FUN_80166478(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043a9e8,param_1,1,2,param_2 + 9,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043a9e8,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801664f8  FUN_801664f8 ====

void FUN_801664f8(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043a9e8,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
  return;
}



// ==== 80166530  FUN_80166530 ====

void FUN_80166530(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    uVar1 = *(uint *)(param_1 + 0x5e0);
    if ((uVar1 & 0x40) == 0) {
      if ((uVar1 & 0x10) != 0) {
        *(undefined1 *)(param_1 + 0x581) = 0;
        zz_006a3d0_(param_1,'\0',0,2);
        return;
      }
    }
    else if ((uVar1 & 0x80) == 0) {
      zz_006d0dc_(param_1,0xc1,0);
    }
  }
  zz_004cd24_(param_1,1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0166bbc_(param_1);
  }
  return;
}



// ==== 801665d8  FUN_801665d8 ====

void FUN_801665d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043a9ec) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_0166a98_(param_9);
        return;
      }
      goto LAB_80166660;
    }
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_80166660;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (*(char *)(param_9 + 0x1cee) == '\0') {
    return;
  }
LAB_80166660:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 80166698  FUN_80166698 ====

void FUN_80166698(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8034e6e4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801666e0  FUN_801666e0 ====

void FUN_801666e0(int param_1)

{
  zz_0166250_(param_1);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
  return;
}



// ==== 80166728  FUN_80166728 ====

/* WARNING: Removing unreachable block (ram,0x801667d4) */
/* WARNING: Removing unreachable block (ram,0x80166738) */

void FUN_80166728(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043a9ec;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    zz_004cd24_(param_1,0xf);
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0166bbc_(param_1);
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



// ==== 801667f0  FUN_801667f0 ====

void FUN_801667f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043a9ec) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) == 0) {
      if (((*(char *)(param_9 + 0x5db) == '\x01') && ((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0))
         && (*(char *)(param_9 + 0x1cee) == '\0')) {
        return;
      }
    }
    else {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_0166a98_(param_9);
        return;
      }
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(char *)(param_9 + 0x5db) == '\x01') {
      zz_006d0dc_(param_9,0xc1,0);
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



// ==== 801668d8  FUN_801668d8 ====

void FUN_801668d8(int param_1)

{
  int iVar1;
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffdf;
  iVar1 = zz_006c674_(param_1);
  if (iVar1 == 2) {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 3;
    zz_006a3d0_(param_1,'\0',3,0);
  }
  return;
}



// ==== 80166954  FUN_80166954 ====

void FUN_80166954(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8034e6f0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8016699c  FUN_8016699c ====

void FUN_8016699c(int param_1)

{
  double dVar1;
  
  zz_0166250_(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_8043a9f0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a9ec;
  return;
}



// ==== 80166a04  FUN_80166a04 ====

void FUN_80166a04(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0166bbc_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  FUN_80067310((double)FLOAT_8043a9f0,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_00b22f4_(param_1);
  return;
}



// ==== 80166a98  zz_0166a98_ ====

void zz_0166a98_(int param_1)

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
  fVar1 = FLOAT_8043a9e0;
  uVar4 = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  fVar2 = FLOAT_8043a9e4;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar4 = 0xf;
  }
  (*(code *)(&PTR_FUN_8034e6fc)[*(char *)(param_1 + 0x581)])(param_1,uVar4);
  return;
}



// ==== 80166bbc  zz_0166bbc_ ====

/* WARNING: Removing unreachable block (ram,0x80166d20) */
/* WARNING: Removing unreachable block (ram,0x80166bcc) */

void zz_0166bbc_(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
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
    iVar3 = 7;
    if (*(char *)(param_1 + 0x1b04) != '\0') {
      iVar3 = 0xb;
    }
    local_2c = *(float *)(param_1 + 0x910);
    local_28 = *(undefined4 *)(param_1 + 0x920);
    local_24 = *(undefined4 *)(param_1 + 0x930);
    local_38 = *(float *)(param_1 + 0x518);
    local_34 = *(float *)(param_1 + 0x51c);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_38);
    dVar6 = (double)local_34;
    local_34 = FLOAT_8043a9ec;
    dVar5 = gnt4_PSVECMag_bl(&local_38);
    iVar2 = FUN_800452a0(dVar6,dVar5);
    sVar1 = (short)iVar2;
    if (iVar3 == 0xb) {
      sVar1 = -sVar1;
    }
    *(short *)(param_1 + iVar3 * 6 + 0x18d6) = sVar1;
    iVar2 = param_1 + iVar3 * 0xc;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + iVar3 * 4 + 0x1996) * 0x30 + 0x8d4),
                (float *)(param_1 + iVar3 * 0x30 + 0x8d4),(short *)(param_1 + iVar3 * 6 + 0x18d4),
                (undefined4 *)(iVar2 + 0x12d4),(float *)(param_1 + iVar3 * 0x10 + 0xed4),
                (float *)(iVar2 + 0x15d4));
  }
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    uVar4 = 0x27;
    if (*(char *)(param_1 + 0x1b04) != '\0') {
      uVar4 = 0x29;
    }
    zz_0082824_(param_1,uVar4);
    zz_0082824_(param_1,uVar4 + 1);
  }
  return;
}



// ==== 80166d40  FUN_80166d40 ====

void FUN_80166d40(int param_1)

{
  (*(code *)(&PTR_FUN_8034e714)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80166d7c  FUN_80166d7c ====

void FUN_80166d7c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80166dac  FUN_80166dac ====

void FUN_80166dac(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80166ddc  FUN_80166ddc ====

void FUN_80166ddc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}



// ==== 80166e0c  FUN_80166e0c ====

void FUN_80166e0c(int param_1)

{
  zz_01618ac_(param_1);
  return;
}



// ==== 80166e30  FUN_80166e30 ====

void FUN_80166e30(int param_1)

{
  zz_0166e50_(param_1);
  return;
}



// ==== 80166e50  zz_0166e50_ ====

void zz_0166e50_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  (*(code *)(&PTR_FUN_8034e728)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80166ea4  FUN_80166ea4 ====

void FUN_80166ea4(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  fVar1 = FLOAT_8043a9ec;
  *(float *)(param_1 + 0x50) = FLOAT_8043a9ec;
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
  gnt4_PSQUATScale_bl((double)FLOAT_8043a9f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043a9e8,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a9ec;
  return;
}



// ==== 80166fa8  FUN_80166fa8 ====

/* WARNING: Removing unreachable block (ram,0x801671e0) */
/* WARNING: Removing unreachable block (ram,0x80166fb8) */

void FUN_80166fa8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  double dVar7;
  double dVar8;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a9f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  fVar2 = FLOAT_8043a9fc;
  fVar1 = FLOAT_8043a9f8;
  if ('\0' < *(char *)(param_1 + 0x1cf0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043aa00;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar7 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_8043a9ec;
      dVar8 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar7,dVar8);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar8 = (double)local_24;
      local_24 = FLOAT_8043a9ec;
      dVar7 = gnt4_PSVECMag_bl(&local_28);
      iVar5 = FUN_800452a0(dVar8,dVar7);
      sVar6 = (short)iVar4 + (short)iVar5;
      *(short *)(param_1 + 0x1900) = sVar6;
      *(short *)(param_1 + 0x1918) = -sVar6;
    }
    zz_0046698_(param_1);
    if (*(char *)(param_1 + 0x580) == '\x02') {
      iVar4 = zz_006dbe0_(param_1,2,1,1);
      if (iVar4 != 0) {
        FUN_8016d584(param_1,0,(float *)(param_1 + 0x518));
        FUN_8016d584(param_1,1,(float *)(param_1 + 0x518));
        FUN_8016d584(param_1,2,(float *)(param_1 + 0x518));
        FUN_8016d584(param_1,3,(float *)(param_1 + 0x518));
      }
    }
    else {
      zz_007db5c_(param_1,8);
      zz_007db5c_(param_1,9);
      zz_007db5c_(param_1,6);
      zz_007db5c_(param_1,7);
      zz_00f036c_(param_1,6);
    }
  }
  dVar7 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043aa04 < dVar7) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80167200  FUN_80167200 ====

void FUN_80167200(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a9d8) * FLOAT_8043aa08);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a9f0,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
LAB_80167290:
    if (*(char *)(param_1 + 0x1cee) == '\0') goto LAB_80167304;
  }
  else if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_006ed8c_((double)FLOAT_8043aa08,param_1);
    goto LAB_80167290;
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
  *(float *)(param_1 + 0x694) = FLOAT_8043a9f0 + *(float *)(param_1 + 0x1dc8);
LAB_80167304:
  if (FLOAT_8043aa04 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80167334  zz_0167334_ ====

void zz_0167334_(undefined1 param_1,int param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_8034fd20)[param_2]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_8016743c;
    *(code **)(puVar1 + 0x10c) = FUN_80167614;
    puVar1[0x10] = 1;
    puVar1[0x11] = (char)param_2;
    puVar1[0x12] = param_3;
    puVar1[0x96] = param_1;
    puVar1[0x13] = (&DAT_8034fd20)[(char)puVar1[0x11]];
  }
  return;
}



// ==== 801673e4  zz_01673e4_ ====

void zz_01673e4_(int param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = zz_0167334_(*(undefined1 *)(param_1 + 0x96),0xb,param_2);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x8c) = param_1;
    *(undefined4 *)(iVar1 + 0xcc) = param_3;
  }
  return;
}



// ==== 8016743c  FUN_8016743c ====

void FUN_8016743c(int param_1)

{
  (*(code *)(&PTR_FUN_8034fd34)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80167478  FUN_80167478 ====

void FUN_80167478(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = *(char *)(param_1 + 0x13) * 0x24;
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
    (*(code *)(&PTR_FUN_8034fd44)[*(char *)(param_1 + 0x11)])
              (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
    *(undefined *)(param_1 + 0x82) =
         (&DAT_80434760)[(char)PTR_DAT_80433944[*(char *)(param_1 + 0x96) + 0x28]];
  }
  return;
}



// ==== 80167564  FUN_80167564 ====

void FUN_80167564(int param_1)

{
  (*(code *)(&PTR_zz_0167760__8034fd94)[*(char *)(param_1 + 0x11)])
            (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
  return;
}



// ==== 801675cc  FUN_801675cc ====

void FUN_801675cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80167614  FUN_80167614 ====

void FUN_80167614(int param_1)

{
  (*(code *)(&PTR_FUN_8034fde4)[*(char *)(param_1 + 0x11)])
            (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
  return;
}



// ==== 80167668  FUN_80167668 ====

void FUN_80167668(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  
  if (*(char *)(param_9 + 0x12) == '\x01') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043aa10;
  }
  else if (*(char *)(param_9 + 0x12) == '\x02') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043aa14;
  }
  else {
    *(float *)(param_9 + 0xd4) = FLOAT_8043aa18;
  }
  piVar6 = &DAT_8034fe34;
  iVar5 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    iVar1 = piVar6[2];
    piVar2 = (int *)(*(int *)(param_9 + 0x54) + iVar5);
    *piVar2 = piVar6[1];
    piVar2[1] = iVar1;
    piVar2[2] = piVar6[3];
    param_11 = (float *)*piVar6;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar4 + 0xe0),(int)param_11,param_12,param_13,param_14,param_15,param_16);
    uVar7 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(iVar4 + 0xe0),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    param_1 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar4 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                          param_15,param_16);
    piVar6 = piVar6 + 4;
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  zz_0167760_(param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



