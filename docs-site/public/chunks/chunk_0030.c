// ==== 801097ac  FUN_801097ac ====

void FUN_801097ac(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  float *pfVar4;
  int iVar5;
  bool bVar6;
  float local_18;
  float local_14;
  float local_10;
  
  if ('\0' < *(char *)(param_1 + 0x542)) {
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    pfVar4 = (float *)&DAT_80325404;
    if (*(short *)(param_1 + 1000) == 0x510) {
      pfVar4 = (float *)&DAT_80325410;
    }
    local_18 = *pfVar4;
    iVar5 = 5;
    local_14 = pfVar4[1];
    local_10 = pfVar4[2];
    if (*(char *)(param_1 + 0x6e8) == '\0') {
      iVar5 = 8;
      local_18 = -local_18;
    }
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + iVar5 * 0x30 + 0x8d4),&local_18,(float *)(param_2 + 0x14));
    fVar1 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
    bVar6 = FLOAT_8043950c < fVar1;
    *(float *)(param_1 + 0x55c) = fVar1;
    if (bVar6) {
      uVar3 = *(undefined4 *)(param_1 + 0x528);
      *(undefined4 *)(param_2 + 8) = *(undefined4 *)(param_1 + 0x524);
      *(undefined4 *)(param_2 + 0xc) = uVar3;
      *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x52c);
    }
    gnt4_PSVECSubtract_bl((float *)(param_2 + 8),(float *)(param_2 + 0x14),&local_18);
    zz_006ec1c_(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x2c),&local_18,&local_18);
    gnt4_PSVECAdd_bl(&local_18,(float *)(param_2 + 0x14),(float *)(param_2 + 0x20));
    fVar2 = FLOAT_8043950c;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x542) = 0xff;
    }
  }
  return;
}



// ==== 801098f8  FUN_801098f8 ====

void FUN_801098f8(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8010992c  FUN_8010992c ====

void FUN_8010992c(int param_1)

{
  (*(code *)(&PTR_FUN_8032541c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80109968  FUN_80109968 ====

void FUN_80109968(int param_1)

{
  (*(code *)(&PTR_FUN_80325428)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801099a4  FUN_801099a4 ====

void FUN_801099a4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar3 = FLOAT_80439538;
  fVar2 = FLOAT_8043950c;
  dVar4 = (double)FLOAT_80439520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0x78;
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



// ==== 80109a30  FUN_80109a30 ====

void FUN_80109a30(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  FUN_80109ef0(param_1);
  zz_0066e40_(param_1,0);
  fVar3 = FLOAT_8043950c;
  fVar2 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_80439520;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80109ac8  FUN_80109ac8 ====

void FUN_80109ac8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80109b20  FUN_80109b20 ====

void FUN_80109b20(int param_1)

{
  (*(code *)(&PTR_FUN_80325434)[*(char *)(param_1 + 0x540)])();
  zz_006ed8c_((double)FLOAT_80439524,param_1);
  zz_0067458_((double)FLOAT_80439528,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80109b8c  FUN_80109b8c ====

void FUN_80109b8c(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439538;
  dVar3 = (double)FLOAT_80439520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0x78;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80109bfc  FUN_80109bfc ====

void FUN_80109bfc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  FUN_80109ef0(param_1);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  zz_0066e40_(param_1,0);
  fVar3 = FLOAT_8043950c;
  fVar2 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_80439520;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80109cac  FUN_80109cac ====

void FUN_80109cac(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80109d04  FUN_80109d04 ====

void FUN_80109d04(int param_1)

{
  (*(code *)(&PTR_FUN_80325440)[*(char *)(param_1 + 0x540)])();
  FUN_80067310((double)FLOAT_80439528,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80109d64  FUN_80109d64 ====

void FUN_80109d64(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439538;
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = (double)FLOAT_80439520;
    *(float *)(param_1 + 0x560) = fVar2;
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



// ==== 80109df4  FUN_80109df4 ====

void FUN_80109df4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  FUN_80109ef0(param_1);
  zz_0066e40_(param_1,2);
  fVar3 = FLOAT_8043950c;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  fVar2 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_80439520;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80109e94  FUN_80109e94 ====

void FUN_80109e94(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,0x10);
  }
  return;
}



// ==== 80109ef0  FUN_80109ef0 ====

void FUN_80109ef0(int param_1)

{
  double dVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_80439510;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar2;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar1);
  }
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      if (*(short *)(param_1 + 1000) == 0x504) {
        zz_00e19a8_(param_1,6,param_1 + 0x6f7);
      }
      else if (*(short *)(param_1 + 1000) == 0x510) {
        zz_00e19a8_(param_1,0x12,param_1 + 0x6f7);
      }
    }
  }
  zz_0066ac0_(param_1,0);
  return;
}



// ==== 80109ff8  FUN_80109ff8 ====

void FUN_80109ff8(int param_1)

{
  (*(code *)(&PTR_FUN_8032544c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8010a034  FUN_8010a034 ====

void FUN_8010a034(int param_1)

{
  (*(code *)(&PTR_FUN_804344f0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010a06c  FUN_8010a06c ====

void FUN_8010a06c(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043950c;
  dVar2 = (double)FLOAT_80439520;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar2,param_1,0xf,4,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8010a0d4  FUN_8010a0d4 ====

void FUN_8010a0d4(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    FUN_8010a468(param_1);
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,0);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80439530 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8010a170  FUN_8010a170 ====

void FUN_8010a170(int param_1)

{
  (*(code *)(&PTR_FUN_804344f8)[*(char *)(param_1 + 0x540)])();
  gnt4_PSQUATScale_bl((double)FLOAT_80439524,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 8010a1dc  FUN_8010a1dc ====

void FUN_8010a1dc(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043950c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_004beb8_((double)FLOAT_80439520,param_1,0xf,4,7,0xffffffff,0xffffffff);
  return;
}



// ==== 8010a264  FUN_8010a264 ====

void FUN_8010a264(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    FUN_8010a468(param_1);
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80439530 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8010a300  FUN_8010a300 ====

void FUN_8010a300(int param_1)

{
  (*(code *)(&PTR_FUN_80434500)[*(char *)(param_1 + 0x540)])();
  FUN_80067310((double)FLOAT_80439528,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8010a35c  FUN_8010a35c ====

void FUN_8010a35c(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    dVar1 = (double)FLOAT_80439520;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar1,param_1,0xf,4,8,0xffffffff,0xffffffff);
  }
  else {
    zz_006a3d0_(param_1,'\x05',3,0);
  }
  return;
}



// ==== 8010a3c0  FUN_8010a3c0 ====

void FUN_8010a3c0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    FUN_8010a468(param_1);
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,0x10);
    *(float *)(param_1 + 0x694) = FLOAT_80439530 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8010a468  FUN_8010a468 ====

void FUN_8010a468(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x504) {
    zz_008672c_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x510) {
    zz_008672c_(param_1,1);
  }
  return;
}



// ==== 8010a4ac  zz_010a4ac_ ====

void zz_010a4ac_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined1 *)(param_1 + 0x6ee) = 0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80439548) * FLOAT_80439540);
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
  }
  return;
}



// ==== 8010a508  FUN_8010a508 ====

void FUN_8010a508(int param_1)

{
  double dVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439550;
  dVar1 = DOUBLE_80439548;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) - dVar1
                           ) * fVar2);
  (*(code *)(&PTR_FUN_80325a00)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8010a588  FUN_8010a588 ====

void FUN_8010a588(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80325a14)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010a5d0  FUN_8010a5d0 ====

void FUN_8010a5d0(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80439554;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),7,1);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_010afd0_(param_1);
  fVar1 = FLOAT_80439558;
  *(float *)(param_1 + 0x50) = FLOAT_80439558;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010a6b0  FUN_8010a6b0 ====

void FUN_8010a6b0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439558;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_8010a734;
  }
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_8010b02c(param_1);
  }
LAB_8010a734:
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439560 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010a78c  FUN_8010a78c ====

void FUN_8010a78c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_80439558) {
    zz_004cd24_(param_9,0xf);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  if (*(float *)(param_9 + 0x558) <= FLOAT_80439558) {
    param_11 = 1;
    param_12 = 0;
    iVar3 = zz_006dbe0_(param_9,0,1,0);
    if (iVar3 == 0) goto LAB_8010a8f8;
    sVar1 = *(short *)(param_9 + 1000);
    if (((sVar1 == 0x305) || (sVar1 == 0x309)) || (sVar1 == 0x30a)) {
      if (*(char *)(param_9 + 0x1cee) != '\0') {
        uVar2 = *(uint *)(param_9 + 0x5b4);
joined_r0x8010a834:
        if ((uVar2 & 0x200) != 0) {
LAB_8010a878:
          if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
            zz_006a3d0_(param_9,'\0',3,0);
            return;
          }
          zz_006bf80_(param_9);
          dVar4 = (double)FLOAT_80439554;
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          zz_004beb8_(dVar4,param_9,0xf,2,1,0xffffffff,0xffffffff);
          return;
        }
      }
    }
    else if (sVar1 == 0x306) {
      if (('\0' < *(char *)(param_9 + 0x6ef)) && (*(char *)(param_9 + 0x1cee) != '\0')) {
        uVar2 = *(uint *)(param_9 + 0x5b4);
        goto joined_r0x8010a834;
      }
    }
    else if ('\0' < *(char *)(param_9 + 0x6ef)) goto LAB_8010a878;
  }
  else {
    *(float *)(param_9 + 0x558) = *(float *)(param_9 + 0x558) - *(float *)(param_9 + 0x1dc8);
  }
  if ((((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_9 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_9 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
    zz_00679d0_(param_9);
    dVar4 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
    if (dVar4 <= (double)FLOAT_80439560) {
      return;
    }
    zz_00b22f4_(param_9);
    return;
  }
LAB_8010a8f8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  dVar4 = (double)zz_006a474_(param_9);
  zz_006a668_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  *(float *)(param_9 + 0x694) =
       (float)((double)CONCAT44(0x43300000,(int)*(float *)(param_9 + 0x558) ^ 0x80000000) -
              DOUBLE_80439548) + *(float *)(param_9 + 0x1dc8);
  return;
}



// ==== 8010a9b4  FUN_8010a9b4 ====

void FUN_8010a9b4(int param_1)

{
  (*(code *)(&PTR_FUN_80325a20)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010a9f0  FUN_8010a9f0 ====

void FUN_8010a9f0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 6;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 2;
  }
  if (((uVar1 & 0x20) != 0) &&
     (iVar2 = *(char *)(param_1 + 0x1d10) + 8, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_80439554,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),7,1);
  zz_010afd0_(param_1);
  return;
}



// ==== 8010aa98  FUN_8010aa98 ====

void FUN_8010aa98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80439558;
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
    if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_8010b02c(param_1);
    }
  }
  return;
}



// ==== 8010ab78  FUN_8010ab78 ====

void FUN_8010ab78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_80439558) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar4 = (double)*(float *)(param_9 + 0x558);
  if (dVar4 <= (double)FLOAT_80439558) {
    param_11 = 1;
    param_12 = 0;
    iVar3 = zz_006dbe0_(param_9,0,1,0);
    if (iVar3 == 0) goto LAB_8010ad7c;
    sVar1 = *(short *)(param_9 + 1000);
    if (((sVar1 == 0x305) || (sVar1 == 0x309)) || (sVar1 == 0x30a)) {
      if (*(char *)(param_9 + 0x1cee) != '\0') {
        uVar2 = *(uint *)(param_9 + 0x5b4);
joined_r0x8010ac20:
        if ((uVar2 & 0x200) != 0) {
LAB_8010ac64:
          zz_006bf80_(param_9);
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          uVar2 = *(uint *)(param_9 + 0x5e0);
          if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
            iVar3 = 5;
            *(undefined1 *)(param_9 + 0x581) = 3;
            if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
              iVar3 = 7;
            }
            zz_004beb8_((double)FLOAT_80439554,param_9,1,2,iVar3,0xffffffff,0xffffffff);
            return;
          }
          if ((uVar2 & 0x10) != 0) {
            dVar4 = (double)FLOAT_80439554;
            *(undefined1 *)(param_9 + 0x581) = 1;
            zz_004beb8_(dVar4,param_9,1,2,3,0xffffffff,0xffffffff);
            return;
          }
          if ((uVar2 & 0x20) != 0) {
            *(undefined1 *)(param_9 + 0x581) = 2;
            iVar3 = *(char *)(param_9 + 0x1d10) + 9;
            if (*(char *)(param_9 + 0x5db) == '\x0f') {
              iVar3 = 1;
            }
            zz_004beb8_((double)FLOAT_80439554,param_9,1,2,iVar3,0xffffffff,0xffffffff);
            return;
          }
          zz_006a3d0_(param_9,'\0',0,2);
          return;
        }
      }
    }
    else if (sVar1 == 0x306) {
      if (('\0' < *(char *)(param_9 + 0x6ef)) && (*(char *)(param_9 + 0x1cee) != '\0')) {
        uVar2 = *(uint *)(param_9 + 0x5b4);
        goto joined_r0x8010ac20;
      }
    }
    else if ('\0' < *(char *)(param_9 + 0x6ef)) goto LAB_8010ac64;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar4 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_8010ad7c:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  *(float *)(param_9 + 0x694) =
       (float)((double)CONCAT44(0x43300000,(int)*(float *)(param_9 + 0x558) ^ 0x80000000) -
              DOUBLE_80439548) + *(float *)(param_9 + 0x1dc8);
  return;
}



// ==== 8010ade8  FUN_8010ade8 ====

void FUN_8010ade8(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80325a2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010ae30  FUN_8010ae30 ====

void FUN_8010ae30(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80439564;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439554,param_1,1,2,*(char *)(param_1 + 0x6ee) + 4,7,1);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80439554,param_1,2,0,0xd,7,1);
  }
  zz_010afd0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010af04  FUN_8010af04 ====

void FUN_8010af04(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_80439558;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_8010afb4;
  }
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_8010b02c(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
LAB_8010afb4:
  zz_00b22f4_(param_1);
  return;
}



// ==== 8010afd0  zz_010afd0_ ====

void zz_010afd0_(int param_1)

{
  *(float *)(param_1 + 0x560) = FLOAT_80439568;
  *(undefined4 *)(param_1 + 0x558) =
       *(undefined4 *)(&DAT_80325990 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined4 *)(param_1 + 0x55c) =
       *(undefined4 *)(&DAT_803259c8 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined *)(param_1 + 0x6ef) = (&DAT_80325980)[*(byte *)(param_1 + 0x3e9)];
  return;
}



// ==== 8010b02c  FUN_8010b02c ====

/* WARNING: Removing unreachable block (ram,0x8010b2d4) */
/* WARNING: Removing unreachable block (ram,0x8010b03c) */

void FUN_8010b02c(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  *(float *)(param_1 + 0x560) = FLOAT_80439568;
  *(undefined4 *)(param_1 + 0x558) =
       *(undefined4 *)(&DAT_80325990 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined4 *)(param_1 + 0x55c) =
       *(undefined4 *)(&DAT_803259c8 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar3 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_80439558;
      dVar4 = gnt4_PSVECMag_bl(&local_28);
      iVar1 = FUN_800452a0(dVar3,dVar4);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar4 = (double)local_24;
      local_24 = FLOAT_80439558;
      dVar3 = gnt4_PSVECMag_bl(&local_28);
      iVar2 = FUN_800452a0(dVar4,dVar3);
      *(short *)(param_1 + 0x1900) = (short)iVar1 + (short)iVar2;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                  (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                  (float *)(param_1 + 0x1628));
    }
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      switch(*(undefined2 *)(param_1 + 1000)) {
      case 0x300:
        zz_0082824_(param_1,0xb);
        break;
      case 0x301:
        zz_0082824_(param_1,0x1b);
        break;
      case 0x302:
        zz_0082824_(param_1,0x1c);
        break;
      case 0x303:
        zz_0082824_(param_1,0x3a);
        break;
      case 0x304:
        zz_0082824_(param_1,0x23);
        break;
      case 0x305:
        zz_00c3be0_(param_1,0xe);
        zz_00c3be0_(param_1,0xf);
        zz_00c3be0_(param_1,0x10);
        zz_00c3be0_(param_1,0x11);
        break;
      case 0x306:
        zz_00c3be0_(param_1,0x5a);
        break;
      case 0x309:
        zz_00c3be0_(param_1,0x46);
        zz_00c3be0_(param_1,0x47);
        zz_00c3be0_(param_1,0x48);
        zz_00c3be0_(param_1,0x49);
        break;
      case 0x30a:
        zz_00c3be0_(param_1,0x4a);
        zz_00c3be0_(param_1,0x4b);
        zz_00c3be0_(param_1,0x4c);
        zz_00c3be0_(param_1,0x4d);
        break;
      case 0x30b:
        zz_0082824_(param_1,0x7e);
      }
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}



// ==== 8010b2f4  zz_010b2f4_ ====

void zz_010b2f4_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325a68)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010b344  FUN_8010b344 ====

void FUN_8010b344(int param_1,undefined1 param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043956c;
  fVar1 = FLOAT_80439558;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010b400  FUN_8010b400 ====

void FUN_8010b400(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  fVar3 = FLOAT_80439558;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar5 = (double)FLOAT_80439554;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    fVar2 = FLOAT_80439558;
    *(float *)(param_1 + 0x4c) = FLOAT_80439558;
    dVar5 = DOUBLE_80439548;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x558) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
    }
    else {
      *(float *)(param_1 + 0x558) = FLOAT_80439568;
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x764) *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                  dVar5) * FLOAT_80439570;
    }
    fVar2 = FLOAT_80439574;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / FLOAT_80439568;
    if (fVar2 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 8010b51c  FUN_8010b51c ====

void FUN_8010b51c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    zz_006ed8c_((double)FLOAT_8043955c,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar3 = FLOAT_80439558;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_80439574,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_80439578;
    dVar5 = (double)FLOAT_80439554;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010b610  FUN_8010b610 ====

void FUN_8010b610(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar2 = FLOAT_80439574;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    if (fVar2 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_80439554;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ((*(char *)(param_1 + 0x1b03) == '\0') && (*(char *)(param_1 + 0x1d0f) != '\0')) {
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) = FLOAT_80439558;
    }
    else {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x764) *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                  DOUBLE_80439548) * FLOAT_80439570;
    }
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / FLOAT_80439568;
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
  }
  zz_006ed8c_((double)FLOAT_8043955c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010b7ac  zz_010b7ac_ ====

void zz_010b7ac_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325a78)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010b7fc  FUN_8010b7fc ====

void FUN_8010b7fc(int param_1,undefined1 param_2)

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
  fVar2 = FLOAT_80439558;
  *(float *)(param_1 + 0x558) = FLOAT_8043956c;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
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
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439554;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8010b94c  FUN_8010b94c ====

void FUN_8010b94c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439568;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8010ba14  FUN_8010ba14 ====

void FUN_8010ba14(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043957c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043957c * -dVar4);
  fVar1 = FLOAT_80439558;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_80439558;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80439580,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8010bb18  FUN_8010bb18 ====

void FUN_8010bb18(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar2 = FLOAT_80439568;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    zz_0092dcc_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar4 = (double)FLOAT_80439554;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
           FLOAT_80439568;
    }
    else {
      *(float *)(param_1 + 0x44) =
           (float)((DOUBLE_80439588 * (double)*(float *)(param_1 + 0x760)) / DOUBLE_80439590);
    }
  }
  fVar2 = FLOAT_80439558;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar2 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar2;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043955c,param_1);
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439564 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8010bd10  zz_010bd10_ ====

void zz_010bd10_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325a88)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010bd60  FUN_8010bd60 ====

void FUN_8010bd60(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043956c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439598,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439554;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010be74  FUN_8010be74 ====

void FUN_8010be74(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439598,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\x01') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043957c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_80439574;
    fVar2 = FLOAT_80439558;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043957c;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  dVar5 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439560 < dVar5) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010bfbc  FUN_8010bfbc ====

void FUN_8010bfbc(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) < '\x01') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    uVar3 = FUN_80066838((double)FLOAT_80439574,param_1);
    if (((int)uVar3 < 1) && (*(char *)(param_1 + 0x1d9) == '\0')) goto LAB_8010c048;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
LAB_8010c048:
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010c074  FUN_8010c074 ====

void FUN_8010c074(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar2 = FLOAT_80439574;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    if (fVar2 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(undefined4 *)(param_1 + 0x44) =
           *(undefined4 *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    }
    else {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x764) *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                  DOUBLE_80439548) * FLOAT_80439570;
    }
    dVar3 = (double)FLOAT_80439554;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / FLOAT_80439568;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_8043955c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010c220  zz_010c220_ ====

void zz_010c220_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325a98)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010c270  FUN_8010c270 ====

void FUN_8010c270(int param_1,undefined1 param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043956c;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80439554,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010c354  FUN_8010c354 ====

void FUN_8010c354(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80439568;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_80439580;
    fVar2 = FLOAT_80439558;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439568;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 8010c43c  FUN_8010c43c ====

void FUN_8010c43c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043955c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    uVar3 = FUN_80066838((double)FLOAT_80439580,param_1);
    if (((int)uVar3 < 1) && (*(char *)(param_1 + 0x1d9) == '\0')) goto LAB_8010c4dc;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0xff;
LAB_8010c4dc:
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010c508  FUN_8010c508 ====

void FUN_8010c508(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439540,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_80439560 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010c590  zz_010c590_ ====

void zz_010c590_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325aa8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010c5e0  FUN_8010c5e0 ====

void FUN_8010c5e0(int param_1,undefined1 param_2)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  fVar1 = FLOAT_80439558;
  *(float *)(param_1 + 0x558) = FLOAT_8043956c;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439598,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439554,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 8010c720  FUN_8010c720 ====

void FUN_8010c720(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439598,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043957c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8010c7e8  FUN_8010c7e8 ====

void FUN_8010c7e8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043957c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_80439564;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043957c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439558;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (((fVar2 < fVar1) && (uVar3 = FUN_800668cc((double)FLOAT_80439580,param_1), (int)uVar3 < 1)) &&
     (*(char *)(param_1 + 0x1d9) == '\0')) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8010c8e0  FUN_8010c8e0 ====

void FUN_8010c8e0(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439558;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80439540,param_1);
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439564 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8010c9d8  zz_010c9d8_ ====

void zz_010c9d8_(int param_1)

{
  (*(code *)(&PTR_FUN_80434508)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010ca10  FUN_8010ca10 ====

void FUN_8010ca10(int param_1,undefined4 *param_2)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + '\x01';
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[1],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  fVar1 = FLOAT_80439558;
  *(float *)(param_1 + 0x50) = FLOAT_80439558;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(undefined4 *)(param_1 + 0x44) = param_2[2];
  }
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439554,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),8,1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439558;
  return;
}



// ==== 8010cb48  FUN_8010cb48 ====

/* WARNING: Removing unreachable block (ram,0x8010cdcc) */
/* WARNING: Removing unreachable block (ram,0x8010cb58) */

void FUN_8010cb48(int param_1,int param_2)

{
  int iVar1;
  short sVar2;
  double dVar3;
  double dVar4;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1b03) == '\0') && (*(char *)(param_1 + 0x542) == '\0')) {
    *(undefined1 *)(param_1 + 0x542) = 0xff;
    if ((*(code **)(param_2 + 0xc) != (code *)0x0) &&
       (iVar1 = (**(code **)(param_2 + 0xc))(param_1), iVar1 != 0)) {
      *(undefined1 *)(param_1 + 0x542) = 1;
    }
  }
  if ((*(char *)(param_1 + 0x1cef) < '\x01') || (-1 < *(char *)(param_1 + 0x542))) {
    if (*(char *)(param_1 + 0x1cf0) < '\0') {
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    if (*(char *)(param_1 + 0x1d10) == '\0') {
      *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
      *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
    }
    else {
      zz_006d144_(param_1,0xc0);
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        local_28 = *(float *)(param_1 + 0xa30);
        local_24 = *(float *)(param_1 + 0xa40);
        local_20 = *(undefined4 *)(param_1 + 0xa50);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
        dVar4 = (double)local_24;
        local_24 = FLOAT_80439558;
        dVar3 = gnt4_PSVECMag_bl(&local_28);
        iVar1 = FUN_800452a0(dVar4,dVar3);
        sVar2 = (short)iVar1;
        if (0x2000 < sVar2) {
          sVar2 = 0x2000;
        }
        if (sVar2 < -0x2000) {
          sVar2 = -0x2000;
        }
        *(short *)(param_1 + 0x1900) = sVar2;
      }
      else {
        zz_006e1ac_(param_1,0xc1,1);
      }
    }
    if (*(char *)(param_1 + 0x1b03) == '\0') {
      *(float *)(param_1 + 0x44) = FLOAT_80439558;
    }
    FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x72) + -0x8000);
    gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    iVar1 = zz_00677b0_(param_1);
    if (((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) &&
       ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_80439564 + *(float *)(param_1 + 0x1dc8);
      return;
    }
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        return;
      }
      zz_00b22f4_(param_1);
      return;
    }
  }
  else {
    *(float *)(param_1 + 0x694) = FLOAT_8043957c + *(float *)(param_1 + 0x1dc8);
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8010cdec  FUN_8010cdec ====

void FUN_8010cdec(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80439548) * FLOAT_80439550);
  (*(code *)(&PTR_FUN_80325ab8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8010ce60  FUN_8010ce60 ====

void FUN_8010ce60(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80325acc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010ceb0  FUN_8010ceb0 ====

void FUN_8010ceb0(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined1 *)(param_1 + 0x6ea) = 0x10;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x11;
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar1 = FLOAT_80439558;
  *(float *)(param_1 + 0x50) = FLOAT_80439558;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_80439554,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),8,1);
  return;
}



// ==== 8010cfbc  FUN_8010cfbc ====

void FUN_8010cfbc(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x302) {
      zz_0082824_(param_1,0x1f);
    }
    else if (sVar1 < 0x302) {
      if (0x300 < sVar1) {
        zz_00c3be0_(param_1,0x13);
      }
    }
    else if (sVar1 < 0x304) {
      iVar2 = zz_006dbe0_(param_1,2,1,1);
      if (iVar2 == 0) {
        FUN_8010d28c(param_1);
      }
      else {
        zz_0082824_(param_1,0x3b);
      }
    }
  }
  return;
}



// ==== 8010d0d0  FUN_8010d0d0 ====

void FUN_8010d0d0(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80439548) * FLOAT_80439540);
  }
  if ((*(short *)(param_1 + 1000) == 0x307) || (*(short *)(param_1 + 1000) == 0x30d)) {
    zz_004cd24_(param_1,0xf);
    if (('\0' < *(char *)(param_1 + 0x1cf0)) && (0 < *(short *)(param_1 + 0x784))) {
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
      *(undefined1 *)(param_1 + 0x6ea) = 0x12;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        *(undefined1 *)(param_1 + 0x6ea) = 0x13;
      }
      zz_004beb8_((double)FLOAT_80439554,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                  0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80439564,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_8043955c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  if (((iVar1 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043959c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    FUN_8010d28c(param_1);
  }
  return;
}



// ==== 8010d28c  FUN_8010d28c ====

void FUN_8010d28c(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
  *(short *)(param_1 + 0x5ae) = (short)iVar1;
  if (FLOAT_80439558 <= *(float *)(param_1 + 0x48)) {
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
  }
  if (FLOAT_80439558 < *(float *)(param_1 + 0x48)) {
    *(float *)(param_1 + 0x48) = FLOAT_80439558;
  }
  *(float *)(param_1 + 0x3c) = FLOAT_80439558;
  dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  *(float *)(param_1 + 0x44) = (float)dVar2;
  *(float *)(param_1 + 0x4c) = FLOAT_80439558;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  *(float *)(param_1 + 0x694) = FLOAT_804395a0 + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 8010d360  zz_010d360_ ====

void zz_010d360_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,int param_11,uint param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  
  zz_0213584_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  puVar1 = &DAT_803c72fc;
  puVar4 = &DAT_803c727c;
  iVar5 = 4;
  puVar2 = puVar1;
  puVar3 = puVar1;
  do {
    *puVar2 = 0;
    *(undefined1 *)(puVar2 + 1) = 0;
    *(undefined1 *)((int)puVar2 + 3) = 0;
    *(undefined1 *)(puVar2 + 2) = 0;
    *(undefined1 *)((int)puVar2 + 5) = 0;
    *(undefined1 *)(puVar2 + 3) = 0;
    *(undefined1 *)((int)puVar2 + 7) = 0;
    *(undefined1 *)(puVar2 + 4) = 0;
    *(undefined1 *)((int)puVar2 + 9) = 0;
    *puVar4 = 0;
    *(undefined1 *)(puVar2 + 5) = 0;
    puVar4[1] = 0;
    puVar2[0x18] = 0;
    puVar4[2] = 0;
    *(undefined1 *)(puVar2 + 0x19) = 0;
    puVar4[3] = 0;
    *(undefined1 *)((int)puVar2 + 0x33) = 0;
    puVar4[4] = 0;
    *(undefined1 *)(puVar2 + 0x1a) = 0;
    *(undefined1 *)(puVar4 + 5) = 0;
    *(undefined1 *)((int)puVar2 + 0x35) = 0;
    *(undefined1 *)((int)puVar4 + 0x15) = 0;
    *(undefined1 *)(puVar2 + 0x1b) = 0;
    *(undefined1 *)((int)puVar4 + 0x16) = 0;
    *(undefined1 *)((int)puVar2 + 0x37) = 0;
    *(undefined1 *)((int)puVar4 + 0x17) = 0;
    *(undefined1 *)(puVar2 + 0x1c) = 0;
    *(undefined1 *)(puVar4 + 6) = 0;
    *(undefined1 *)((int)puVar2 + 0x39) = 0;
    *(undefined1 *)(puVar2 + 0x1d) = 0;
    puVar2 = puVar2 + 6;
    *(undefined1 *)((int)puVar4 + 0x19) = 0;
    *(undefined1 *)((int)puVar4 + 0x1a) = 0;
    puVar1[0x38] = 0;
    *(undefined1 *)(puVar3 + 0x40) = 0;
    puVar3 = (undefined2 *)((int)puVar3 + 1);
    *(undefined1 *)((int)puVar4 + 0x1b) = 0;
    *(undefined1 *)(puVar4 + 7) = 0;
    puVar1[0x3c] = 0;
    puVar1 = puVar1 + 1;
    *(undefined1 *)((int)puVar4 + 0x1d) = 0;
    puVar4 = puVar4 + 8;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}



// ==== 8010d450  zz_010d450_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_010d450_(void)

{
  char cVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  ushort uVar4;
  uint uVar5;
  byte bVar7;
  int iVar6;
  ushort *puVar8;
  uint uVar9;
  int iVar10;
  ushort *puVar11;
  uint *puVar12;
  uint *puVar13;
  ushort *puVar14;
  uint *puVar15;
  ushort *puVar16;
  ushort *puVar17;
  ushort *puVar18;
  
  puVar11 = &DAT_803c72fc;
  DAT_803c732c = _DAT_803c72fc;
  DAT_803c7330 = _DAT_803c7300;
  DAT_803c7334 = DAT_803c7304;
  DAT_803c7338 = DAT_803c7308;
  DAT_803c733c = DAT_803c730c;
  DAT_803c7340 = DAT_803c7310;
  DAT_803c7344 = DAT_803c7314;
  DAT_803c7348 = DAT_803c7318;
  DAT_803c734c = DAT_803c731c;
  DAT_803c7350 = DAT_803c7320;
  DAT_803c7354 = DAT_803c7324;
  DAT_803c7358 = DAT_803c7328;
  zz_021379c_(&DAT_803c72fc);
  PADClampCircle(-0x7fc38d04);
  puVar15 = (uint *)&DAT_80325ad8;
  puVar13 = (uint *)0x80325b0c;
  puVar12 = (uint *)0x80325b1c;
  uVar9 = 0;
  iVar10 = 0;
  puVar14 = puVar11;
  puVar16 = puVar11;
  puVar17 = puVar11;
  puVar18 = puVar11;
  do {
    cVar1 = *(char *)(puVar18 + 5);
    if (cVar1 == -1) {
      uVar5 = zz_020ace4_(*puVar13);
      if ((uVar5 & 0x8000000) != 0) {
        uVar5 = *puVar12;
        puVar17[0x3c] = 0;
        uVar9 = uVar9 | uVar5;
        zz_010d97c_(iVar10);
      }
    }
    else if (cVar1 < -1) {
      if (cVar1 == -3) {
        *(undefined4 *)puVar18 = *(undefined4 *)(puVar18 + 0x18);
        *(undefined4 *)(puVar18 + 2) = *(undefined4 *)(puVar18 + 0x1a);
        *(undefined4 *)(puVar18 + 4) = *(undefined4 *)(puVar18 + 0x1c);
      }
    }
    else if (cVar1 < '\x01') {
      uVar4 = puVar17[0x3c];
      if ((short)uVar4 < 0) {
        puVar17[0x3c] = uVar4 + 1;
        zz_010d97c_(iVar10);
      }
      else if (*(int *)(puVar16 + 0x30) == 0) {
        puVar17[0x3c] = 0;
      }
      else {
        puVar17[0x3c] = uVar4 + 1;
        if ((short)(uVar4 + 1) < 0x78) {
          puVar8 = *(ushort **)(puVar16 + 0x30);
          if ((*(char *)(puVar14 + 0x40) != '\0') &&
             (uVar4 = puVar17[0x38], puVar17[0x38] = uVar4 - 1, (short)(uVar4 - 1) < 1)) {
            puVar8 = puVar8 + 1;
          }
          if ((short)puVar17[0x38] < 1) {
            uVar5 = (uint)(short)*puVar8;
            if (uVar5 == 0xffffffff) {
              gnt4_PADControlMotor_bl(*puVar15,0);
              zz_010d97c_(iVar10);
            }
            else {
              if ((uVar5 & 0x8000) == 0) {
                if ((uVar5 & 0x4000) == 0) {
                  if ((uVar5 & 0x2000) != 0) {
                    uVar5 = *puVar15;
                    *(undefined1 *)(puVar14 + 0x40) = 1;
                    gnt4_PADControlMotor_bl(uVar5,2);
                  }
                }
                else {
                  uVar5 = *puVar15;
                  *(undefined1 *)(puVar14 + 0x40) = 1;
                  gnt4_PADControlMotor_bl(uVar5,0);
                }
              }
              else {
                uVar5 = *puVar15;
                *(undefined1 *)(puVar14 + 0x40) = 1;
                gnt4_PADControlMotor_bl(uVar5,1);
              }
              *(ushort **)(puVar16 + 0x30) = puVar8;
              puVar17[0x38] = *puVar8 & 0x1fff;
            }
          }
        }
        else {
          gnt4_PADControlMotor_bl(*puVar15,0);
          puVar17[0x3c] = 0xffc4;
          zz_010d97c_(iVar10);
        }
      }
    }
    iVar10 = iVar10 + 1;
    puVar17 = puVar17 + 1;
    puVar16 = puVar16 + 2;
    puVar15 = puVar15 + 1;
    puVar14 = (ushort *)((int)puVar14 + 1);
    puVar13 = puVar13 + 1;
    puVar12 = puVar12 + 1;
    puVar18 = puVar18 + 6;
  } while (iVar10 < 4);
  if (uVar9 != 0) {
    gnt4_PADReset_bl(uVar9);
  }
  iVar10 = 0;
  puVar12 = &DAT_803c727c;
  do {
    if (*(char *)(puVar11 + 5) == -1) {
      *(undefined1 *)((int)puVar12 + 0x15) = 0;
    }
    else {
      *(undefined1 *)((int)puVar12 + 0x15) = 1;
    }
    uVar4 = *puVar11;
    puVar12[1] = *puVar12;
    uVar2 = *(undefined1 *)(puVar11 + 1);
    *puVar12 = (uint)uVar4;
    uVar3 = *(undefined1 *)((int)puVar11 + 3);
    *(undefined1 *)((int)puVar12 + 0x16) = uVar2;
    uVar2 = *(undefined1 *)(puVar11 + 2);
    *(undefined1 *)((int)puVar12 + 0x17) = uVar3;
    uVar3 = *(undefined1 *)((int)puVar11 + 5);
    *(undefined1 *)(puVar12 + 6) = uVar2;
    uVar2 = *(undefined1 *)(puVar11 + 3);
    *(undefined1 *)((int)puVar12 + 0x19) = uVar3;
    uVar3 = *(undefined1 *)((int)puVar11 + 7);
    *(undefined1 *)((int)puVar12 + 0x1a) = uVar2;
    *(undefined1 *)((int)puVar12 + 0x1b) = uVar3;
    bVar7 = FUN_8008b73c(*(char *)((int)puVar12 + 0x16),*(char *)((int)puVar12 + 0x17),0x1e);
    *puVar12 = *puVar12 | (uint)bVar7 << 0x10;
    bVar7 = FUN_8008b73c(*(char *)(puVar12 + 6),*(char *)((int)puVar12 + 0x19),0x1e);
    *puVar12 = *puVar12 | (uint)bVar7 << 0x14;
    iVar6 = (uint)*(byte *)((int)puVar12 + 0x1a) - (uint)*(byte *)(puVar12 + 7);
    if (0x1d < iVar6) {
      *puVar12 = *puVar12 | 0x40;
    }
    if (iVar6 < 0x23) {
      if (*(byte *)((int)puVar12 + 0x1a) < *(byte *)(puVar12 + 7)) {
        *(byte *)(puVar12 + 7) = *(byte *)((int)puVar12 + 0x1a);
      }
    }
    else {
      *(char *)(puVar12 + 7) = *(char *)((int)puVar12 + 0x1a) + -0x23;
    }
    iVar6 = (uint)*(byte *)((int)puVar12 + 0x1b) - (uint)*(byte *)((int)puVar12 + 0x1d);
    if (0x1d < iVar6) {
      *puVar12 = *puVar12 | 0x20;
    }
    if (iVar6 < 0x23) {
      if (*(byte *)((int)puVar12 + 0x1b) < *(byte *)((int)puVar12 + 0x1d)) {
        *(byte *)((int)puVar12 + 0x1d) = *(byte *)((int)puVar12 + 0x1b);
      }
    }
    else {
      *(char *)((int)puVar12 + 0x1d) = *(char *)((int)puVar12 + 0x1b) + -0x23;
    }
    iVar10 = iVar10 + 1;
    puVar11 = puVar11 + 6;
    puVar12[2] = *puVar12 & ~puVar12[1];
    puVar12[3] = puVar12[1] & ~*puVar12;
    puVar12[4] = 0;
    puVar12 = puVar12 + 8;
  } while (iVar10 < 4);
  return;
}



// ==== 8010d880  set_slot_action_handler ====

/* GF_ALIAS: set_slot_action_handler
 * Evidence: gates by active slot mask PTR_DAT_8043394c+0x30, then writes
 * DAT_803c735c[slot] from PTR_DAT_80325af4[mode % 6] and clears adjacent
 * per-slot state arrays.
 */

void set_slot_action_handler(int slot_index,int action_mode)

{
  if (((int)(char)PTR_DAT_8043394c[0x30] & 1 << slot_index) == 0) {
    return;
  }
  (&DAT_803c735c)[slot_index] = (&PTR_DAT_80325af4)[action_mode % 6];
  (&DAT_803c736c)[slot_index] = 0;
  (&DAT_803c737c)[slot_index] = 0;
  return;
}



// ==== 8010d8f8  zz_010d8f8_ ====

void zz_010d8f8_(int param_1,int param_2)

{
  if (param_2 == 0) {
    gnt4_PADControlMotor_bl(*(uint *)(&DAT_80325ad8 + param_1 * 4),0);
  }
  else {
    gnt4_PADControlMotor_bl(*(uint *)(&DAT_80325ad8 + param_1 * 4),2);
  }
  (&DAT_803c7374)[param_1] = 0;
  zz_010d97c_(param_1);
  return;
}



// ==== 8010d97c  zz_010d97c_ ====

void zz_010d97c_(int param_1)

{
  (&DAT_803c735c)[param_1] = 0;
  (&DAT_803c736c)[param_1] = 0;
  (&DAT_803c737c)[param_1] = 0;
  return;
}



// ==== 8010d9ac  zz_010d9ac_ ====

void zz_010d9ac_(void)

{
  DAT_803d42a0 = 0;
  DAT_803d42a6 = 0;
  DAT_803d42a4 = 0xffff;
  DAT_803d42a7 = 0;
  DAT_803d4518 = 0;
  DAT_803d451e = 0;
  DAT_803d451c = 0xffff;
  DAT_803d451f = 1;
  DAT_803d4514 = &LAB_80217694;
  DAT_803d478c = &LAB_802176a0;
  DAT_803d4790 = 0;
  DAT_803d47a4 = DAT_80435c60;
  DAT_803d4794 = gnt4_OSAllocFromHeap_bl(DAT_80435c60,0x80000);
  DAT_803d479c = DAT_803d4794 + 0x1fff8;
  DAT_803d47a0 = 0x7ffe0;
  DAT_803d4798 = DAT_803d4794;
  *DAT_803d4794 = 0;
  DAT_803d4798[1] = (int)DAT_803d479c;
  DAT_803d4798[2] = 0x20;
  *DAT_803d479c = (int)DAT_803d4798;
  DAT_803d479c[1] = 0;
  DAT_803d479c[2] = 0x20;
  zz_021a20c_(FUN_8010daa8,&LAB_8010db98);
  return;
}



// ==== 8010daa8  FUN_8010daa8 ====

int * FUN_8010daa8(int param_1)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = zz_010daf4_(param_1);
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = piVar1 + 8;
    DAT_803d47a0 = DAT_803d47a0 - piVar1[2];
  }
  return piVar2;
}



// ==== 8010daf4  zz_010daf4_ ====

int * zz_010daf4_(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = (param_1 + 0x1fU & 0xffffffe0) + 0x20;
  iVar7 = 0x7fffffff;
  iVar4 = 0;
  iVar3 = DAT_803d4798;
  do {
    iVar5 = iVar3;
    iVar3 = *(int *)(iVar5 + 4);
    iVar1 = (iVar3 - iVar5) - *(int *)(iVar5 + 8);
    if (iVar6 <= iVar1) {
      if (iVar1 == iVar6) break;
      if (iVar1 - iVar6 < iVar7) {
        iVar4 = iVar5;
        iVar7 = iVar1 - iVar6;
      }
    }
    iVar5 = iVar4;
  } while (*(int *)(iVar3 + 4) != 0);
  if (iVar5 != 0) {
    piVar2 = (int *)(iVar5 + *(int *)(iVar5 + 8));
    *piVar2 = iVar5;
    piVar2[1] = *(int *)(iVar5 + 4);
    piVar2[2] = iVar6;
    **(undefined4 **)(iVar5 + 4) = piVar2;
    *(int **)(iVar5 + 4) = piVar2;
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 8010dbcc  zz_010dbcc_ ====

uint zz_010dbcc_(void)

{
  if (DAT_803d42a0 == 0) {
    return 0;
  }
  return ((uint)DAT_803d42a6 * 0x7fff) / 0xff;
}



// ==== 8010dc14  zz_010dc14_ ====

uint zz_010dc14_(void)

{
  if (DAT_803d4518 == 0) {
    return 0;
  }
  return ((uint)DAT_803d451e * 0x7fff) / 0xff;
}



// ==== 8010dc5c  zz_010dc5c_ ====

void zz_010dc5c_(int param_1)

{
  if (DAT_803d4790 != 0) {
    if (param_1 == 3) {
      if (DAT_803d42a0 != 5) {
        zz_010dd8c_();
      }
      zz_010ddb4_();
    }
    else {
      if (DAT_803d42a0 == 5) {
        zz_010dd8c_();
      }
      if (DAT_803d4518 == 5) {
        zz_010ddb4_();
      }
    }
  }
  return;
}



// ==== 8010dcd4  zz_010dcd4_ ====

void zz_010dcd4_(int *param_1)

{
  int iVar1;
  
  (*(code *)param_1[0x9d])(0,0);
  iVar1 = *param_1;
  if (iVar1 == 3) {
    zz_021a0cc_(param_1 + 2);
  }
  else if (iVar1 < 3) {
    if (iVar1 == 1) {
      zz_021a080_((int)(param_1 + 2));
    }
    else if (0 < iVar1) {
      zz_0219f10_((int)(param_1 + 2));
    }
  }
  else if (iVar1 == 5) {
    zz_021a33c_((int)(param_1 + 2));
  }
  else if (iVar1 < 5) {
    zz_021a11c_((int)(param_1 + 2));
  }
  *param_1 = 0;
  *(undefined2 *)(param_1 + 1) = 0xffff;
  return;
}



// ==== 8010dd8c  zz_010dd8c_ ====

void zz_010dd8c_(void)

{
  zz_010dcd4_(&DAT_803d42a0);
  return;
}



// ==== 8010ddb4  zz_010ddb4_ ====

void zz_010ddb4_(void)

{
  zz_010dcd4_(&DAT_803d4518);
  return;
}



// ==== 8010dde0  zz_010dde0_ ====

void zz_010dde0_(int param_1,byte param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x402) || (*(short *)(param_1 + 1000) == 0x408)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = param_2 & 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_8010def8;
    *(code **)(puVar1 + 0x10c) = FUN_8010e0ac;
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



// ==== 8010def8  FUN_8010def8 ====

void FUN_8010def8(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80325b70)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8010df4c  FUN_8010df4c ====

void FUN_8010df4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = *(char *)(param_9 + 0x13) * 0x10;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804395a8;
  *(undefined1 *)(param_9 + 0x84) = 0x49;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(undefined *)(param_9 + 0x89) = (&DAT_80325b31)[iVar4];
  uVar2 = *(undefined4 *)(&DAT_80325b38 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80325b34 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80325b3c + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80325b32 + iVar4);
  iVar3 = zz_0006f98_(param_9);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80325b30)[iVar4],iVar3 + 0xc28,iVar6,in_r8,in_r9,in_r10);
  iVar5 = iVar3 + 0xc28;
  iVar4 = (int)(char)(&DAT_80325b30)[iVar4];
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,iVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,iVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804395ac,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_010e078_();
  return;
}



// ==== 8010e078  zz_010e078_ ====

void zz_010e078_(void)

{
  return;
}



// ==== 8010e08c  FUN_8010e08c ====

void FUN_8010e08c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8010e0ac  FUN_8010e0ac ====

void FUN_8010e0ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (param_9[0x11] == '\0') {
    if (*(short *)(iVar1 + 0x784) < 1) {
      return;
    }
  }
  else if ((param_9[0x11] == '\x01') && (*(short *)(iVar1 + 0x784) < 2)) {
    return;
  }
  if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
    iVar1 = *(int *)(param_9 + 0xe0);
    uVar2 = 1;
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 8010e158  zz_010e158_ ====

void zz_010e158_(int param_1,int param_2)

{
  int iVar1;
  undefined1 *puVar2;
  
  iVar1 = param_2 * 8;
  puVar2 = zz_0088aa0_(param_1,2,0x18,0,(int)(char)(&DAT_80325bf8)[iVar1]);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0x15;
    puVar2[0x11] = (char)param_2;
    puVar2[0x12] = (&DAT_80325bf9)[iVar1];
    puVar2[0x13] = (&DAT_80325bf8)[iVar1];
    *(code **)(puVar2 + 0xc) = FUN_8010e2a8;
    *(code **)(puVar2 + 0x10c) = FUN_8010e80c;
    *(undefined2 *)(puVar2 + 0x1c) = *(undefined2 *)(&DAT_80325bfa + iVar1);
    if ((&DAT_80325bf9)[iVar1] == '\x01') {
      *(uint *)(param_1 + 0x8c4) = *(uint *)(param_1 + 0x8c4) | 1 << param_2;
    }
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
    *(undefined **)(puVar2 + 0x54) = (&PTR_DAT_80325bfc)[param_2 * 2];
  }
  return;
}



// ==== 8010e2a8  FUN_8010e2a8 ====

void FUN_8010e2a8(int param_1)

{
  (*(code *)(&PTR_FUN_80325c10)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8010e2e4  FUN_8010e2e4 ====

void FUN_8010e2e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  short *psVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  short *psVar12;
  undefined4 *puVar13;
  undefined8 uVar14;
  
  puVar13 = (undefined4 *)(param_9 + 0x144);
  psVar12 = *(short **)(param_9 + 0x54);
  puVar4 = puVar13;
  psVar5 = psVar12;
  puVar7 = puVar13;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    *puVar4 = 0;
    *(short *)(puVar7 + 4) = psVar5[1];
    *(short *)(puVar7 + 8) = psVar5[2];
    *(short *)(puVar7 + 10) = psVar5[3];
    puVar4[0xc] = *(undefined4 *)(psVar5 + 4);
    puVar4[0x10] = *(undefined4 *)(psVar5 + 6);
    puVar4[0x14] = *(undefined4 *)(psVar5 + 8);
    if (iVar8 == 0) {
      *(undefined2 *)(puVar7 + 6) = 0;
    }
    else {
      *(short *)(puVar7 + 6) = *(short *)((int)puVar7 + 0x16) + *(short *)((int)puVar7 + 0xe);
    }
    puVar4 = puVar4 + 1;
    psVar5 = psVar5 + 10;
    puVar7 = (undefined4 *)((int)puVar7 + 2);
  }
  *(char *)(param_9 + 0x1a4) =
       (char)*(undefined2 *)((int)puVar13 + iVar8 * 2 + 0x16) +
       (char)*(undefined2 *)((int)puVar13 + iVar8 * 2 + 0xe);
  piVar1 = zz_0006dc8_(*(char *)(param_9 + 0x1a4) * 0x5c);
  *(int **)(param_9 + 0xdc) = piVar1;
  if (piVar1 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(code **)(param_9 + 0x100) = FUN_8010e62c;
    uVar14 = zz_0089100_(param_9,1,1);
    iVar11 = param_9;
    for (iVar10 = 0; iVar10 < *(char *)(param_9 + 0x13); iVar10 = iVar10 + 1) {
      pcVar6 = (char *)(int)*psVar12;
      puVar7 = (undefined4 *)(int)*(short *)(puVar13 + 4);
      uVar14 = zz_0007198_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb374,*(int *)(iVar11 + 0xe0),pcVar6,(int)puVar7,iVar8,in_r8,in_r9
                           ,in_r10);
      iVar9 = 0;
      iVar2 = *(int *)(*(int *)(iVar11 + 0xe0) + 0xc);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 0x10);
      }
      while (iVar9 < *(short *)(puVar13 + 4)) {
        uVar14 = gnt4_HSD_JObjSetFlagsAll
                           (uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                            0x10,pcVar6,puVar7,iVar8,in_r8,in_r9,in_r10);
        iVar9 = iVar9 + 1;
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 8);
        }
      }
      puVar13 = (undefined4 *)((int)puVar13 + 2);
      psVar12 = psVar12 + 10;
      iVar11 = iVar11 + 4;
    }
    uVar3 = zz_00055fc_();
    uVar3 = uVar3 & 0xff;
    zz_010ea30_(param_9,uVar3 - (uVar3 / (uint)(int)*(char *)(param_9 + 0x13)) *
                                (int)*(char *)(param_9 + 0x13),uVar3,puVar7,iVar8,in_r8,in_r9,in_r10
               );
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 8010e4d0  FUN_8010e4d0 ====

void FUN_8010e4d0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_9 + 0x8c);
  zz_010ec9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x12) == '\0') {
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    uVar1 = countLeadingZeros((int)sVar2);
    uVar1 = (1 << (uVar1 & 0x1f) | 1U >> 0x20 - (uVar1 & 0x1f)) & 1;
  }
  else if (*(char *)(param_9 + 0x12) == '\x01') {
    uVar1 = countLeadingZeros(*(uint *)(iVar3 + 0x8c4) & 1 << (int)*(char *)(param_9 + 0x11));
    uVar1 = uVar1 >> 5;
  }
  else {
    uVar1 = 0;
  }
  if (uVar1 == 0) {
    uVar1 = zz_00055fc_();
    uVar1 = uVar1 & 0xff;
    zz_010ea30_(param_9,uVar1 - (uVar1 / (uint)(int)*(char *)(param_9 + 0x13)) *
                                (int)*(char *)(param_9 + 0x13),uVar1,param_12,param_13,param_14,
                param_15,param_16);
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8010e5a0  FUN_8010e5a0 ====

void FUN_8010e5a0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  uVar1 = zz_010ec9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (uVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 3;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 8010e5e4  FUN_8010e5e4 ====

void FUN_8010e5e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8010e62c  FUN_8010e62c ====

void FUN_8010e62c(int param_1)

{
  uint *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  double dVar7;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  
  puVar1 = (uint *)(param_1 + 0x144);
  iVar5 = *(int *)(param_1 + 0x8c);
  puVar6 = puVar1;
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    if (*puVar6 != 0) {
      iVar3 = 0;
      while( true ) {
        if (*(short *)(puVar1 + 4) <= iVar3) break;
        if ((1 << iVar3 & *puVar6) != 0) {
          local_38 = *(float *)(iVar5 + 0x8e0);
          local_34 = *(float *)(iVar5 + 0x8f0);
          pfVar2 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) +
                            (*(short *)(puVar1 + 6) + iVar3) * 0x5c);
          local_30 = *(float *)(iVar5 + 0x900);
          if ((puVar1[10] & 0x20000) != 0) {
            local_34 = pfVar2[0xd];
          }
          if ((puVar1[10] & 0x10000) != 0) {
            local_38 = pfVar2[0xc];
            local_30 = pfVar2[0xe];
          }
          gnt4_PSMTXIdentity_bl(pfVar2);
          zz_00457d4_('y',pfVar2,pfVar2,*(short *)(pfVar2 + 0x16));
          local_2c = pfVar2[2];
          local_28 = pfVar2[6];
          local_24 = pfVar2[10];
          gnt4_PSQUATScale_bl((double)pfVar2[0x11],&local_2c,&local_2c);
          local_28 = pfVar2[0x12];
          gnt4_PSVECAdd_bl(&local_38,&local_2c,&local_2c);
          if ((puVar1[10] & 0x70000000) == 0) {
            gnt4_PSMTXTrans_bl((double)local_2c,(double)local_28,(double)local_24,pfVar2);
            zz_00457d4_('z',pfVar2,pfVar2,*(short *)(pfVar2 + 0x15));
            zz_00457d4_('y',pfVar2,pfVar2,*(short *)((int)pfVar2 + 0x52));
            zz_00457d4_('x',pfVar2,pfVar2,*(short *)(pfVar2 + 0x14));
            dVar7 = (double)pfVar2[0xf];
            zz_0045654_(dVar7,dVar7,dVar7,pfVar2,pfVar2);
          }
          else {
            *pfVar2 = local_2c;
            pfVar2[1] = local_28;
            pfVar2[2] = local_24;
          }
        }
        iVar3 = iVar3 + 1;
      }
    }
    puVar6 = puVar6 + 1;
    puVar1 = (uint *)((int)puVar1 + 2);
  }
  return;
}



// ==== 8010e80c  FUN_8010e80c ====

/* WARNING: Removing unreachable block (ram,0x8010e990) */

void FUN_8010e80c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  bool bVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint *puVar11;
  undefined8 uVar12;
  float afStack_58 [14];
  
  puVar3 = (uint *)(param_9 + 0x144);
  iVar10 = param_9;
  puVar11 = puVar3;
  for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
    if (*puVar11 != 0) {
      iVar8 = 0;
      iVar4 = *(int *)(*(int *)(iVar10 + 0xe0) + 0xc);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x10);
      }
      while (iVar8 < *(short *)(puVar3 + 4)) {
        if ((1 << iVar8 & *puVar11) != 0) {
          uVar1 = *(ushort *)(puVar3 + 10);
          pfVar6 = (float *)(uint)uVar1;
          pfVar7 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) +
                            (*(short *)(puVar3 + 6) + iVar8) * 0x5c);
          if ((uVar1 & 0x7000) == 0) {
            uVar12 = gnt4_PSMTXCopy_bl(pfVar7,afStack_58);
          }
          else {
            if ((uVar1 & 0x1000) != 0) {
              zz_004844c_(afStack_58,pfVar7,1);
            }
            if ((puVar3[10] & 0x20000000) != 0) {
              zz_004844c_(afStack_58,pfVar7,2);
            }
            if ((puVar3[10] & 0x40000000) != 0) {
              zz_004844c_(afStack_58,pfVar7,5);
            }
            zz_00457d4_('z',afStack_58,afStack_58,*(short *)(pfVar7 + 0x15));
            zz_00457d4_('y',afStack_58,afStack_58,*(short *)((int)pfVar7 + 0x52));
            pfVar6 = afStack_58;
            param_12 = (int)*(short *)(pfVar7 + 0x14);
            zz_00457d4_('x',pfVar6,pfVar6,*(short *)(pfVar7 + 0x14));
            param_2 = (double)pfVar7[0xf];
            param_3 = param_2;
            uVar12 = zz_0045654_(param_2,param_2,param_2,afStack_58,afStack_58);
          }
          if (iVar4 == 0) {
            pfVar6 = (float *)&DAT_804395b8;
            gnt4___assert_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_804395b0,0x495,&DAT_804395b8,param_12,param_13,param_14,param_15,
                             param_16);
          }
          uVar12 = gnt4_PSMTXCopy_bl(afStack_58,(float *)(iVar4 + 0x44));
          *(uint *)(iVar4 + 0x14) = *(uint *)(iVar4 + 0x14) | 0x3800000;
          if (iVar4 != 0) {
            uVar5 = *(uint *)(iVar4 + 0x14);
            bVar2 = false;
            if (((uVar5 & 0x800000) == 0) && ((uVar5 & 0x40) != 0)) {
              bVar2 = true;
            }
            if (!bVar2) {
              gnt4_HSD_JObjSetMtxDirtySub_bl
                        (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,uVar5,
                         (undefined *)pfVar6,param_12,param_13,param_14,param_15,param_16);
            }
          }
        }
        iVar8 = iVar8 + 1;
        if (iVar4 == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar4 + 8);
        }
      }
      zz_00097b4_(*(int *)(iVar10 + 0xe0),(int)*(short *)(puVar3 + 8));
    }
    puVar11 = puVar11 + 1;
    iVar10 = iVar10 + 4;
    puVar3 = (uint *)((int)puVar3 + 2);
  }
  return;
}



// ==== 8010ea30  zz_010ea30_ ====

void zz_010ea30_(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar6 = 0;
  puVar8 = (uint *)(param_1 + 0x144 + param_2 * 4);
  iVar9 = param_1 + 0x144 + param_2 * 2;
  iVar7 = *(int *)(param_1 + 0x8c);
  while( true ) {
    if (*(short *)(iVar9 + 0x10) <= iVar6) break;
    puVar5 = (undefined *)(1 << iVar6);
    if (((uint)puVar5 & *puVar8) == 0) {
      sVar1 = *(short *)(iVar9 + 0x18);
      iVar4 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc);
      *puVar8 = *puVar8 | (uint)puVar5;
      iVar4 = iVar4 + (sVar1 + iVar6) * 0x5c;
      if ((*(ushort *)(iVar9 + 0x28) & 3) != 0) {
        *(undefined4 *)(iVar4 + 0x30) = *(undefined4 *)(iVar7 + 0x8e0);
        *(undefined4 *)(iVar4 + 0x34) = *(undefined4 *)(iVar7 + 0x8f0);
        *(undefined4 *)(iVar4 + 0x38) = *(undefined4 *)(iVar7 + 0x900);
      }
      uVar2 = zz_00055fc_();
      *(short *)(iVar4 + 0x58) = (short)(uVar2 << 8);
      uVar2 = zz_00055fc_();
      *(float *)(iVar4 + 0x44) =
           (*(float *)(iVar7 + 0x770) *
           (float)((double)CONCAT44(0x43300000,uVar2 & 0xff) - DOUBLE_804395d0)) / FLOAT_804395c0;
      *(undefined2 *)(iVar4 + 0x54) = 0;
      *(undefined2 *)(iVar4 + 0x52) = 0;
      *(undefined2 *)(iVar4 + 0x50) = 0;
      if ((*(ushort *)(iVar9 + 0x28) & 0x10) != 0) {
        uVar2 = zz_00055fc_();
        *(short *)(iVar4 + 0x50) = (short)(uVar2 << 8);
      }
      if ((*(ushort *)(iVar9 + 0x28) & 0x20) != 0) {
        uVar2 = zz_00055fc_();
        *(short *)(iVar4 + 0x52) = (short)(uVar2 << 8);
      }
      if ((*(ushort *)(iVar9 + 0x28) & 0x40) != 0) {
        uVar2 = zz_00055fc_();
        *(short *)(iVar4 + 0x54) = (short)(uVar2 << 8);
      }
      if ((*(ushort *)(iVar9 + 0x28) & 0x700) != 0) {
        uVar2 = zz_00055fc_();
        *(ushort *)(iVar4 + 0x56) = ((ushort)(uVar2 << 2) & 0x3fc) + 0x100;
      }
      uVar2 = zz_00055fc_();
      *(float *)(iVar4 + 0x48) =
           (*(float *)(iVar7 + 0x668) *
           (float)((double)CONCAT44(0x43300000,uVar2 & 0xff) - DOUBLE_804395d0)) / FLOAT_804395c4;
      uVar2 = zz_00055fc_();
      *(float *)(iVar4 + 0x4c) =
           (float)puVar8[0xc] +
           (float)((double)CONCAT44(0x43300000,uVar2 & 0xff) - DOUBLE_804395d0) /
           (float)puVar8[0x10];
      uVar2 = zz_00055fc_();
      dVar12 = (double)(float)((double)CONCAT44(0x43300000,uVar2 & 0xff) - DOUBLE_804395d0);
      dVar11 = (double)(float)(dVar12 / (double)(float)puVar8[0x14]);
      dVar10 = (double)(float)((double)FLOAT_804395c8 + dVar11);
      *(float *)(iVar4 + 0x3c) = (float)((double)*(float *)(iVar7 + 0xb4) * dVar10);
      iVar3 = *(int *)(*(int *)(param_1 + param_2 * 4 + 0xe0) + 0xc);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 0x10);
      }
      if (0 < iVar6) {
        do {
          if (iVar3 == 0) {
            iVar3 = 0;
          }
          else {
            iVar3 = *(int *)(iVar3 + 8);
          }
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      gnt4_HSD_JObjClearFlagsAll
                (dVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,0x10,puVar5,param_4,
                 param_5,param_6,param_7,param_8);
      dVar10 = (double)FLOAT_804395cc;
      *(float *)(iVar4 + 0x40) = FLOAT_804395cc;
      zz_00091e4_(dVar10,iVar3);
      iVar6 = (int)*(short *)(iVar9 + 0x10);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 8010ec9c  zz_010ec9c_ ====

uint zz_010ec9c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint *puVar5;
  undefined *puVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint *puVar13;
  double dVar14;
  double dVar15;
  
  uVar8 = 0;
  puVar5 = (uint *)(param_9 + 0x144);
  iVar11 = *(int *)(param_9 + 0x8c);
  iVar12 = param_9;
  puVar13 = puVar5;
  for (iVar10 = 0; iVar10 < *(char *)(param_9 + 0x13); iVar10 = iVar10 + 1) {
    if (*puVar13 != 0) {
      iVar9 = 0;
      iVar4 = *(int *)(*(int *)(iVar12 + 0xe0) + 0xc);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x10);
      }
      while( true ) {
        if (*(short *)(puVar5 + 4) <= iVar9) break;
        if ((1 << iVar9 & *puVar13) != 0) {
          iVar7 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + (*(short *)(puVar5 + 6) + iVar9) * 0x5c
          ;
          if ((puVar5[10] & 0x1000000) != 0) {
            *(short *)(iVar7 + 0x50) = *(short *)(iVar7 + 0x50) + *(short *)(iVar7 + 0x56);
          }
          if ((puVar5[10] & 0x2000000) != 0) {
            *(short *)(iVar7 + 0x52) = *(short *)(iVar7 + 0x52) + *(short *)(iVar7 + 0x56);
          }
          if ((puVar5[10] & 0x4000000) != 0) {
            *(short *)(iVar7 + 0x54) = *(short *)(iVar7 + 0x54) + *(short *)(iVar7 + 0x56);
          }
          *(float *)(iVar7 + 0x48) =
               *(float *)(iVar7 + 0x4c) * *(float *)(iVar11 + 0xb4) + *(float *)(iVar7 + 0x48);
          fVar3 = FLOAT_804395cc;
          fVar1 = FLOAT_804395c8;
          if (*(float *)(iVar11 + 0x668) <= *(float *)(iVar7 + 0x48)) {
            fVar2 = *(float *)(iVar7 + 0x40);
            dVar14 = (double)FLOAT_804395cc;
            fVar1 = (float)((double)fVar2 - (double)FLOAT_804395dc);
            dVar15 = (double)fVar1;
            *(float *)(iVar7 + 0x40) = fVar1;
            if (dVar15 <= dVar14) {
              puVar6 = (undefined *)*puVar13;
              *puVar13 = (uint)puVar6 & ~(1 << iVar9);
              *(float *)(iVar7 + 0x40) = fVar3;
              gnt4_HSD_JObjSetFlagsAll
                        (dVar15,(double)fVar2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                         0x10,puVar6,param_12,param_13,param_14,param_15,param_16);
            }
          }
          else if (*(float *)(iVar7 + 0x40) < FLOAT_804395c8) {
            fVar3 = *(float *)(iVar7 + 0x40) + FLOAT_804395d8;
            *(float *)(iVar7 + 0x40) = fVar3;
            if (fVar1 <= fVar3) {
              *(float *)(iVar7 + 0x40) = fVar1;
            }
          }
          zz_00091e4_((double)*(float *)(iVar7 + 0x40),iVar4);
        }
        iVar9 = iVar9 + 1;
        if (iVar4 == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar4 + 8);
        }
      }
      uVar8 = uVar8 | *puVar13;
    }
    puVar13 = puVar13 + 1;
    iVar12 = iVar12 + 4;
    puVar5 = (uint *)((int)puVar5 + 2);
  }
  return uVar8;
}



// ==== 8010ee88  zz_010ee88_ ====

undefined4 zz_010ee88_(int param_1,undefined4 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    if ((iVar2 != 1) && (iVar2 == 2)) {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      if (puVar1 == (undefined1 *)0x0) {
        param_2 = 0;
      }
      else {
        *puVar1 = 1;
        puVar1[0x11] = 2;
        param_2 = 1;
        *(code **)(puVar1 + 0xc) = FUN_8010efa8;
        *(code **)(puVar1 + 0x10c) = FUN_8010f440;
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
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 3);
  return param_2;
}



// ==== 8010efa8  FUN_8010efa8 ====

void FUN_8010efa8(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80325c68)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8010effc  FUN_8010effc ====

void FUN_8010effc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_804395e0;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80325c28 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80325c24 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80325c2c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80325c30 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80325c34 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80325c22 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80325c20 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80325c20 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804395e4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_010f128_(param_9);
  return;
}



// ==== 8010f128  zz_010f128_ ====

void zz_010f128_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        zz_010f17c_(param_1);
      }
    }
    else if (cVar1 < '\x03') {
      zz_010f3c4_(param_1);
    }
  }
  return;
}



// ==== 8010f17c  zz_010f17c_ ====

void zz_010f17c_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  short sVar6;
  int iVar7;
  double dVar8;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar7 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x3c);
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x50);
    sVar6 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar6;
    if (sVar6 < 1) {
      dVar8 = (double)FLOAT_804395f0;
      *(undefined2 *)(param_1 + 0x1c) = 2;
      gnt4_PSMTXRotRad_bl(dVar8,afStack_48,0x78);
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,afStack_48);
      zz_00aedc0_(*(int *)(param_1 + 0x90),afStack_48,0,*(undefined1 *)(param_1 + 0x88));
    }
    sVar6 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar6;
    fVar3 = FLOAT_804395f4;
    if (sVar6 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      fVar4 = FLOAT_804395f8;
      *(code **)(param_1 + 0x10c) = FUN_8010f4d0;
      fVar5 = FLOAT_804395fc;
      *(float *)(param_1 + 100) = fVar3;
      dVar8 = DOUBLE_80439608;
      *(float *)(param_1 + 0x68) = fVar4;
      fVar3 = FLOAT_80439600;
      *(float *)(param_1 + 0x6c) = fVar5;
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      local_18 = 0x43300000;
      uStack_14 = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
      *(float *)(param_1 + 0x44) = fVar3 / (float)((double)CONCAT44(0x43300000,uStack_14) - dVar8);
      zz_0089444_(param_1);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if (('\x04' < (char)PTR_DAT_80433934[0x45]) && ('\x01' < (char)PTR_DAT_80433934[0x52])) {
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      }
    }
    else if ((-1 < cVar1) &&
            (sVar6 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar6,
            fVar4 = FLOAT_804395ec, fVar3 = FLOAT_804395e8, sVar6 < 1)) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) & 0xbf;
      *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x28);
      uVar2 = *(undefined4 *)(iVar7 + 0xb4);
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined4 *)(param_1 + 0x58) = uVar2;
      *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar7 + 0x70);
      *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar7 + 0x74);
      *(float *)(param_1 + 0x3c) = fVar3;
      *(float *)(param_1 + 0x50) = fVar4;
      *(undefined2 *)(param_1 + 0x1c) = 2;
      *(undefined2 *)(param_1 + 0x1e) = 0xb4;
    }
  }
  else if ((cVar1 != '\x04') && (cVar1 < '\x04')) {
    sVar6 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar6;
    if (sVar6 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x44);
  }
  return;
}



// ==== 8010f3c4  zz_010f3c4_ ====

void zz_010f3c4_(int param_1)

{
  short sVar1;
  
  if (*(char *)(param_1 + 0x19) == '\x01') {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) - *(short *)(param_1 + 0x7c);
    sVar1 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar1;
    if (0 < sVar1) {
      return;
    }
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x19)) {
    return;
  }
  return;
}



// ==== 8010f420  FUN_8010f420 ====

void FUN_8010f420(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8010f440  FUN_8010f440 ====

void FUN_8010f440(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  if (*(char *)(param_9 + 0x11) == '\x02') {
    uVar2 = uVar2 | 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 8010f4d0  FUN_8010f4d0 ====

void FUN_8010f4d0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar4 = *(int *)(param_1 + 0x90);
  cVar1 = PTR_DAT_80433930[0x28];
  dVar7 = (double)*(float *)(param_1 + 0x68);
  dVar8 = (double)*(float *)(param_1 + 0x6c);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 100),dVar7,dVar8,(float *)(param_1 + 0x114));
  pfVar2 = (float *)(param_1 + 0x114);
  uVar6 = gnt4_PSMTXConcat_bl((float *)(&DAT_803c74c4 + cVar1 * 0x3e4),pfVar2,pfVar2);
  if (*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') {
    iVar3 = *(int *)(param_1 + 0xe0);
    if (*(char *)(iVar4 + 0x3ec) == '\x04') {
      uVar5 = 0x44;
    }
    else {
      uVar5 = 1;
    }
  }
  else {
    iVar3 = *(int *)(param_1 + 0xe4);
    uVar5 = 0x44;
  }
  if (*(char *)(param_1 + 0x11) == '\x02') {
    uVar5 = uVar5 | 0x44;
  }
  zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,(float *)(param_1 + 0x114),
              (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(iVar3,uVar5);
  return;
}



// ==== 8010f790  FUN_8010f790 ====

void FUN_8010f790(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if ((((*(short *)(param_1 + 0x784) < 1) || ((*(uint *)(param_1 + 0x5bc) & 0x400) == 0)) ||
      (0 < *(short *)(param_1 + 0x144))) ||
     ((uVar1 = zz_006ab9c_(param_1), uVar1 == 0 || (iVar2 = zz_006dbe0_(param_1,2,1,0), iVar2 == 0))
     )) {
    if ((0 < *(short *)(param_1 + 0x144)) &&
       (*(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + -1,
       *(short *)(param_1 + 0x144) < 1)) {
      *(undefined2 *)(param_1 + 0x144) = 0;
      apply_actor_param_tier_delta_127(param_1,-4);
    }
  }
  else {
    zz_006a3d0_(param_1,'\x02',0,0);
    zz_006dbe0_(param_1,2,1,1);
  }
  return;
}



// ==== 8010f86c  FUN_8010f86c ====

void FUN_8010f86c(int param_1)

{
  (*(code *)(&PTR_FUN_80326af0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8010f8a8  FUN_8010f8a8 ====

void FUN_8010f8a8(int param_1)

{
  (*(code *)(&PTR_FUN_80326afc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8010f8e4  FUN_8010f8e4 ====

void FUN_8010f8e4(int param_1)

{
  (*(code *)(&PTR_FUN_80326b10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010f920  FUN_8010f920 ====

void FUN_8010f920(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439610;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439614,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439618;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8010fa0c  FUN_8010fa0c ====

void FUN_8010fa0c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439614,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cf0) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8010fac4  FUN_8010fac4 ====

void FUN_8010fac4(int param_1)

{
  float fVar1;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439614,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043961c;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_010fe78_(param_1);
  }
  return;
}



// ==== 8010fb74  FUN_8010fb74 ====

void FUN_8010fb74(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439628) * FLOAT_80439620);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 == 0) || ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439624 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8010fc7c  FUN_8010fc7c ====

void FUN_8010fc7c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  
  if (*(char *)(param_9 + 0x1d10) == '\0') {
    dVar1 = (double)zz_010fe78_(param_9);
    if ((*(char *)(param_9 + 0x1afc) == *(char *)(param_9 + 0x1b3c)) &&
       (*(char *)(param_9 + 0x1afd) == *(char *)(param_9 + 0x1b3d))) {
      zz_004cd24_(param_9,1);
    }
    else {
      dVar1 = (double)zz_0048d54_(dVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9,1,param_11,param_12,param_13,param_14,param_15,param_16);
    }
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(float *)(param_9 + 0x694) = FLOAT_80439630 + *(float *)(param_9 + 0x1dc8);
  }
  else {
    zz_006a3d0_(param_9,'\0',0,0);
  }
  return;
}



// ==== 8010fd44  FUN_8010fd44 ====

void FUN_8010fd44(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  
  if ((*(char *)(param_9 + 0x746) == '\0') && (*(char *)(param_9 + 0x5db) != '\x11')) {
    zz_006a3d0_(param_9,'\0',3,0);
    return;
  }
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    dVar1 = (double)FLOAT_80439618;
    *(undefined1 *)(param_9 + 0x746) = 0;
    param_11 = 2;
    param_12 = 3;
    param_13 = 0xffffffff;
    param_14 = 0xffffffff;
    param_1 = (double)zz_004beb8_(dVar1,param_9,1,2,3,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_9,1);
    if ('\0' < *(char *)(param_9 + 0x1cef)) {
      *(undefined1 *)(param_9 + 0x1cef) = 0;
      *(char *)(param_9 + 0x746) = *(char *)(param_9 + 0x746) + '\x01';
      param_1 = (double)zz_010fe78_(param_9);
    }
    if (*(char *)(param_9 + 0x1cee) != '\0') {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      *(float *)(param_9 + 0x694) = FLOAT_80439624 + *(float *)(param_9 + 0x1dc8);
      return;
    }
  }
  if ((*(uint *)(param_9 + 0x5e0) & 0xc0) == 0) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8010fe78  zz_010fe78_ ====

void zz_010fe78_(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 1000) == 0x804) {
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_00f036c_(param_1,0xa2);
      FUN_800b5ed8(param_1,2,0);
      FUN_800b5ed8(param_1,2,0x1000);
      FUN_800b5ed8(param_1,2,-0x1000);
    }
  }
  else if ((*(short *)(param_1 + 1000) == 0x80c) && (iVar1 = zz_006dbe0_(param_1,0,1,1), iVar1 != 0)
          ) {
    zz_00f036c_(param_1,0xa2);
    zz_00c3be0_(param_1,99);
    zz_00c3be0_(param_1,100);
  }
  return;
}



// ==== 8010ff48  FUN_8010ff48 ====

void FUN_8010ff48(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x804) {
    (*(code *)(&PTR_FUN_80326b20)[*(char *)(param_1 + 0x581)])();
  }
  else {
    (*(code *)(&PTR_FUN_80326b34)[*(char *)(param_1 + 0x581)])();
  }
  return;
}



// ==== 8010ffb4  FUN_8010ffb4 ====

void FUN_8010ffb4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80326b48)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80110010  FUN_80110010 ====

void FUN_80110010(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043961c;
  fVar2 = FLOAT_80439610;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(float *)(param_1 + 0x50) = fVar3;
  *(float *)(param_1 + 0x48) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar3;
  *(float *)(param_1 + 0x44) = fVar3;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_80439618;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80110118  FUN_80110118 ====

void FUN_80110118(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439634;
    fVar1 = FLOAT_8043961c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x80c) = fVar1;
  }
  return;
}



// ==== 801101f0  FUN_801101f0 ====

void FUN_801101f0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  double dVar6;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_80439634;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043961c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar5 = FUN_80066838((double)FLOAT_80439638,param_1), 0 < (int)uVar5)) {
    fVar3 = FLOAT_80439640;
    fVar2 = FLOAT_80439634;
    if (*(float *)(param_1 + 0x764) <= FLOAT_8043963c) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      fVar4 = FLOAT_80439638;
      *(float *)(param_1 + 0x558) = fVar2;
      *(float *)(param_1 + 0x44) = (fVar3 * *(float *)(param_1 + 0x764)) / fVar4;
      if (fVar3 < *(float *)(param_1 + 0x44)) {
        *(float *)(param_1 + 0x44) = fVar3;
      }
      fVar2 = FLOAT_80439644;
      *(float *)(param_1 + 0x4c) = FLOAT_8043961c;
      fVar3 = FLOAT_80439648;
      *(float *)(param_1 + 0x48) = fVar2 * *(float *)(param_1 + 0x44);
      if (*(float *)(param_1 + 0x48) < fVar3) {
        *(float *)(param_1 + 0x48) = fVar3;
      }
      *(float *)(param_1 + 0x50) = -*(float *)(param_1 + 0x48) / FLOAT_80439634;
      zz_0066530_(param_1,0x2d);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar6 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    zz_00b2190_(param_1,0);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8011038c  FUN_8011038c ====

void FUN_8011038c(int param_1)

{
  float fVar1;
  float fVar2;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_8043961c;
  if (*(float *)(param_1 + 0x48) < FLOAT_8043961c) {
    *(float *)(param_1 + 0x48) = FLOAT_8043961c;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80110440  FUN_80110440 ====

void FUN_80110440(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043964c;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(undefined2 *)(param_1 + 0x54e) = 0x2000;
    }
    if (*(short *)(param_1 + 0x54e) < 0) {
      *(undefined2 *)(param_1 + 0x54e) = 0;
    }
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439650 * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    fVar1 = FLOAT_8043961c;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439650 * -dVar2);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80110514  FUN_80110514 ====

void FUN_80110514(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439658);
  }
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x1d10) = 0;
    zz_0066530_(param_1,0x2c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_8043961c;
  }
  fVar3 = FLOAT_8043961c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80439624 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80110654  FUN_80110654 ====

void FUN_80110654(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439620,param_1);
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439610;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar3 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_80439660 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8011075c  FUN_8011075c ====

void FUN_8011075c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439664,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_80439668;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80110808  FUN_80110808 ====

void FUN_80110808(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    fVar3 = FLOAT_8043966c;
    fVar2 = FLOAT_80439640;
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      fVar4 = FLOAT_80439670;
      *(float *)(param_1 + 0x44) = fVar2;
      fVar2 = FLOAT_80439674;
      *(float *)(param_1 + 0x4c) = fVar3;
      *(float *)(param_1 + 0x48) = fVar4;
      *(float *)(param_1 + 0x50) = fVar2;
      zz_0066530_(param_1,0x2d);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar5 = (double)FLOAT_80439618;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,0);
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801108e0  FUN_801108e0 ====

void FUN_801108e0(int param_1)

{
  float fVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d10) != '\0') {
      zz_006d144_(param_1,0xc0);
    }
    FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    fVar1 = FLOAT_8043961c;
    if (*(float *)(param_1 + 0x48) < FLOAT_8043961c) {
      dVar2 = (double)FLOAT_80439618;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x44) = fVar1;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar2,param_1,0xf,0,0xd,10,1);
    }
  }
  return;
}



// ==== 801109b8  FUN_801109b8 ====

void FUN_801109b8(int param_1)

{
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439624,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80439624 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80110a50  FUN_80110a50 ====

void FUN_80110a50(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80326b78)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80110aac  FUN_80110aac ====

void FUN_80110aac(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined2 *)(param_1 + 0x54a) = 9;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439610;
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439614,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_004beb8_((double)FLOAT_80439618,param_1,0xf,3,7,0xffffffff,0xffffffff);
  return;
}



// ==== 80110b9c  FUN_80110b9c ====

void FUN_80110b9c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439634;
    fVar1 = FLOAT_8043961c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x80c) = fVar1;
  }
  else {
    zz_006ed8c_((double)FLOAT_80439614,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80110c88  FUN_80110c88 ====

void FUN_80110c88(int param_1)

{
  float fVar1;
  float fVar2;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439678,param_1);
  if (*(float *)(param_1 + 0x764) < FLOAT_8043967c) {
    zz_006ed8c_((double)FLOAT_80439680,param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (FLOAT_8043961c < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  fVar2 = FLOAT_80439634;
  fVar1 = FLOAT_8043961c;
  if ((*(float *)(param_1 + 0x558) <= FLOAT_8043961c) && ('\0' < *(char *)(param_1 + 0x1cef))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80110da0  FUN_80110da0 ====

void FUN_80110da0(int param_1)

{
  float fVar1;
  short sVar3;
  uint uVar2;
  int iVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439678,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_00b22f4_(param_1);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439688);
  }
  if ((*(char *)(param_1 + 0x1cef) < '\0') && ('\0' < *(char *)(param_1 + 0x746))) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    sVar3 = *(short *)(param_1 + 0x54a) + -1;
    *(short *)(param_1 + 0x54a) = sVar3;
    if (-1 < sVar3) {
      if (*(int *)(param_1 + 0xcc) == 0) {
        *(float *)(param_1 + 0x44) =
             *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
             FLOAT_80439610;
      }
      else {
        *(float *)(param_1 + 0x44) = (float)(DOUBLE_80439658 * (double)*(float *)(param_1 + 0x764));
      }
      *(float *)(param_1 + 0x4c) = FLOAT_8043961c;
      uVar2 = zz_00055fc_();
      *(undefined *)(param_1 + 0x542) =
           (&DAT_80434528)[*(char *)(param_1 + 0x542) * 2 + (uVar2 & 1)];
      fVar1 = FLOAT_8043961c;
      iVar4 = *(char *)(param_1 + 0x542) + 8;
      if (*(short *)(param_1 + 0x54a) < 1) {
        iVar4 = 0xd;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x44) = fVar1;
      }
      zz_004beb8_((double)FLOAT_80439618,param_1,0xf,3,iVar4,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,0);
      return;
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80110f78  FUN_80110f78 ====

void FUN_80110f78(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x44) =
         (FLOAT_80439660 * *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868)
         ) / FLOAT_80439610;
  }
  zz_006ed8c_((double)FLOAT_80439678,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_00b22f4_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80111060  FUN_80111060 ====

void FUN_80111060(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9c9c_(param_1);
  return;
}



// ==== 801110ac  FUN_801110ac ====

void FUN_801110ac(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80326ba8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80111108  FUN_80111108 ====

void FUN_80111108(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439610;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined1 *)(param_1 + 0x6ea) = 0x10;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439618;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801111e4  FUN_801111e4 ====

void FUN_801111e4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043961c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439634;
    fVar1 = FLOAT_8043961c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x80c) = fVar1;
  }
  return;
}



// ==== 80111294  FUN_80111294 ====

void FUN_80111294(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  double dVar6;
  
  zz_006d144_(param_1,0xc0);
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(float *)(param_1 + 0x44) = (FLOAT_80439644 * *(float *)(param_1 + 0x764)) / FLOAT_80439634;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043961c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar5 = FUN_80066838((double)FLOAT_8043963c,param_1), 0 < (int)uVar5)) {
    fVar4 = FLOAT_80439640;
    fVar3 = FLOAT_80439634;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_8043961c;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x44) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0066530_(param_1,0x2d);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar6 = (double)FLOAT_80439618;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    zz_00b2190_(param_1,0);
  }
  zz_00b22f4_(param_1);
  return;
}


