// ==== 8019d0d8  FUN_8019d0d8 ====

uint FUN_8019d0d8(uint param_1)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  uVar2 = param_1;
  if (*(short *)(param_1 + 1000) == 0xa0a) {
    zz_00c627c_(param_1,1,param_1 + 0x168);
    bVar3 = zz_01fcc50_(param_1,0,param_1 + 0x150,param_1 + 0x169);
    uVar2 = (uint)bVar3;
    if ('\b' < *(char *)(param_1 + 0x3ee)) {
      bVar3 = zz_01fcc50_(param_1,0,param_1 + 0x15c,param_1 + 0x16a);
      uVar2 = (uint)bVar3;
    }
  }
  fVar1 = FLOAT_8043b468;
  *(undefined1 *)(param_1 + 0x168) = 1;
  *(undefined1 *)(param_1 + 0x169) = 1;
  *(undefined1 *)(param_1 + 0x16a) = 1;
  *(undefined1 *)(param_1 + 0x16b) = 1;
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x154) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x160) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x28);
  return uVar2;
}



// ==== 8019d1b8  FUN_8019d1b8 ====

/* WARNING: Removing unreachable block (ram,0x8019d2dc) */
/* WARNING: Removing unreachable block (ram,0x8019d1c8) */

void FUN_8019d1b8(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  float afStack_3c [3];
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  zz_0148718_(param_1,(byte *)(param_1 + 0x14c));
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    local_30 = 0x43300000;
    uStack_2c = (int)*(short *)(param_1 + 0x18da) ^ 0x80000000;
    iVar4 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043b478) * FLOAT_8043b46c
                 );
    local_28 = (longlong)iVar4;
    *(short *)(param_1 + 0x18da) = (short)iVar4;
  }
  if (*(short *)(param_1 + 1000) == 0xa0a) {
    local_48 = *(float *)(param_1 + 0xb20);
    dVar6 = (double)FLOAT_8043b470;
    iVar4 = 0;
    local_44 = *(undefined4 *)(param_1 + 0xb30);
    local_40 = *(undefined4 *)(param_1 + 0xb40);
    pfVar1 = (float *)(param_1 + 0x150);
    pfVar3 = &local_48;
    do {
      pfVar2 = pfVar1;
      gnt4_PSVECSubtract_bl(pfVar2,pfVar3,afStack_3c);
      dVar5 = gnt4_PSVECMag_bl(afStack_3c);
      if ((double)(float)(dVar6 * (double)*(float *)(param_1 + 0xb4)) < dVar5) {
        zz_006ebb4_(afStack_3c,afStack_3c);
        gnt4_PSQUATScale_bl((double)(FLOAT_8043b470 * *(float *)(param_1 + 0xb4)),afStack_3c,
                            afStack_3c);
        gnt4_PSVECAdd_bl(afStack_3c,pfVar3,pfVar2);
      }
      iVar4 = iVar4 + 1;
      pfVar1 = pfVar2 + 3;
      pfVar3 = pfVar2;
    } while (iVar4 < 2);
  }
  return;
}



// ==== 8019d314  FUN_8019d314 ====

void FUN_8019d314(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80373dc0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8019d354  FUN_8019d354 ====

void FUN_8019d354(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0xa05) {
    zz_001ab6c_(param_1,0x3e);
  }
  else if (*(short *)(param_1 + 1000) == 0xa0a) {
    zz_001ab6c_(param_1,0x74);
  }
  return;
}



// ==== 8019d3b0  FUN_8019d3b0 ====

void FUN_8019d3b0(int param_1)

{
  (*(code *)(&PTR_FUN_80373dd0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019d3ec  FUN_8019d3ec ====

void FUN_8019d3ec(int param_1)

{
  (*(code *)(&PTR_zz_019d770__80373ddc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019d428  FUN_8019d428 ====

void FUN_8019d428(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80373df0)[*(char *)(param_1 + 0x544)])();
  return;
}



// ==== 8019d470  FUN_8019d470 ====

void FUN_8019d470(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b480;
  if ((*(char *)(param_1 + 0x7ce) == '\x0f') || (*(char *)(param_1 + 0x7ce) == '\x10')) {
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    zz_019d6fc_(param_1);
    zz_019d4fc_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 2;
    zz_019d770_(param_1);
  }
  return;
}



// ==== 8019d4fc  zz_019d4fc_ ====

void zz_019d4fc_(int param_1)

{
  *(undefined1 *)(param_1 + 0x544) = 1;
  zz_019de44_(param_1);
  zz_004beb8_((double)FLOAT_8043b484,param_1,1,2,0xf,0xc,2);
  zz_004beb8_((double)FLOAT_8043b484,param_1,6,2,0x1b,0xc,2);
  return;
}



// ==== 8019d570  FUN_8019d570 ====

void FUN_8019d570(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_019d6fc_(param_1);
  if ((*(char *)(param_1 + 0x1cee) == '\0') && (FLOAT_8043b480 < *(float *)(param_1 + 0x558))) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x6ec) < '\x01') {
    dVar1 = (double)FLOAT_8043b484;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    zz_004beb8_(dVar1,param_1,1,2,0x11,0xffffffff,0xffffffff);
  }
  else {
    zz_019de60_(param_1);
    zz_004beb8_((double)FLOAT_8043b484,param_1,1,2,0x10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019d63c  FUN_8019d63c ====

void FUN_8019d63c(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_019d6fc_(param_1);
  if ((*(uint *)(param_1 + 0x5d4) & 0x20) == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a6fc_(param_1,0x10);
      dVar1 = (double)FLOAT_8043b488;
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_004beb8_(dVar1,param_1,1,0,0xb,0xffffffff,0xffffffff);
      zz_006a750_(param_1,0x10);
      *(undefined1 *)(param_1 + 0x544) = 2;
      *(undefined1 *)(param_1 + 0x588) = 1;
    }
  }
  else {
    zz_019d4fc_(param_1);
  }
  return;
}



// ==== 8019d6fc  zz_019d6fc_ ====

void zz_019d6fc_(int param_1)

{
  float fVar1;
  
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  fVar1 = FLOAT_8043b480;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043b48c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8019d770  zz_019d770_ ====

void zz_019d770_(int param_1)

{
  zz_019ddbc_(param_1);
  (*(code *)(&PTR_FUN_80435738)[*(char *)(param_1 + 0x545)])(param_1);
  (*(code *)(&PTR_FUN_80435730)[*(char *)(param_1 + 0x544)])(param_1);
  (*(code *)(&PTR_FUN_80373dfc)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 8019d800  FUN_8019d800 ====

void FUN_8019d800(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043b484;
  *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  zz_004beb8_(dVar1,param_1,4,2,0x1a,4,2);
  return;
}



// ==== 8019d844  FUN_8019d844 ====

void FUN_8019d844(int param_1)

{
  zz_004cd24_(param_1,4);
  return;
}



// ==== 8019d868  FUN_8019d868 ====

void FUN_8019d868(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b490;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  zz_019de44_(param_1);
  zz_004beb8_((double)FLOAT_8043b484,param_1,1,2,(int)*(char *)(param_1 + 0x6ea),4,2);
  return;
}



// ==== 8019d8d0  FUN_8019d8d0 ====

void FUN_8019d8d0(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043b480;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if ((*(float *)(param_1 + 0x560) < fVar1) ||
     ((*(char *)(param_1 + 0x1cee) != '\0' && (*(short *)(param_1 + 0x54a) != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019de60_(param_1);
    dVar2 = (double)FLOAT_8043b484;
    *(undefined2 *)(param_1 + 0x54c) = 5;
    zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019d96c  FUN_8019d96c ====

void FUN_8019d96c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar1 = FLOAT_8043b480;
  *(undefined2 *)(param_1 + 0x54c) = 5;
  fVar2 = FLOAT_8043b494;
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    if (*(char *)(param_1 + 0x6ec) < '\x01') {
      dVar4 = (double)FLOAT_8043b484;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x55c) = fVar2;
      *(undefined2 *)(param_1 + 0x54c) = 10;
      zz_004beb8_(dVar4,param_1,7,2,*(char *)(param_1 + 0x6ea) + 10,4,2);
    }
    else {
      zz_006bf80_(param_1);
      zz_019de60_(param_1);
      zz_004beb8_((double)FLOAT_8043b484,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                  0xffffffff);
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = *(float *)(param_1 + 0x558) + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8019dab0  FUN_8019dab0 ====

void FUN_8019dab0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  *(undefined2 *)(param_1 + 0x54c) = 10;
  if ((*(char *)(param_1 + 0x745) != '\0') && (iVar3 = zz_006dbe0_(param_1,0,1,0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    zz_019de44_(param_1);
    zz_006bf80_(param_1);
    zz_019de60_(param_1);
    zz_004beb8_((double)FLOAT_8043b484,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                0xffffffff);
    return;
  }
  fVar2 = FLOAT_8043b480;
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) &&
      (fVar1 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x55c) = fVar1, fVar2 < fVar1)) && (*(char *)(param_1 + 0x1cee) == '\0'))
  {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 0) {
    zz_006a4f4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8019dbdc  FUN_8019dbdc ====

void FUN_8019dbdc(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  fVar1 = FLOAT_8043b480;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043b480;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_8043b484,param_1,2,2,*(char *)(param_1 + 0x6eb) + 0x15,0xc,2);
  zz_019dc70_(param_1);
  return;
}



// ==== 8019dc70  zz_019dc70_ ====

void zz_019dc70_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_8043b498,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_8043b480;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043b484;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_8043b480;
  }
  FUN_80067310((double)FLOAT_8043b48c,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,3);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)*(float *)(param_1 + 0x1ae0),param_1,1,2,
                  *(short *)(param_1 + 0x54c) + iVar3,
                  (int)(FLOAT_8043b49c +
                       (float)((double)(float)((double)CONCAT44(0x43300000,
                                                                (int)*(short *)(param_1 + 0x1af8) ^
                                                                0x80000000) - DOUBLE_8043b478) -
                              (double)*(float *)(param_1 + 0x1ae0))),2);
      zz_004beb8_((double)FLOAT_8043b484,param_1,2,2,iVar3 + 0x15,0xc,2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 8019ddbc  zz_019ddbc_ ====

void zz_019ddbc_(int param_1)

{
  undefined2 uVar2;
  int iVar1;
  int iVar3;
  char cVar4;
  
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



// ==== 8019de44  zz_019de44_ ====

void zz_019de44_(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x745) = 0;
  fVar1 = FLOAT_8043b494;
  *(undefined1 *)(param_1 + 0x6ec) = 1;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 8019de60  zz_019de60_ ====

void zz_019de60_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043b4a0;
  *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x587) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    if (*(short *)(param_1 + 1000) == 0xa05) {
      zz_00c3be0_(param_1,0x1d);
    }
    else if (*(short *)(param_1 + 1000) == 0xa0a) {
      zz_00c3be0_(param_1,0x1c);
      *(byte *)(param_1 + 0x168) = *(byte *)(param_1 + 0x168) | 0x80;
      *(byte *)(param_1 + 0x169) = *(byte *)(param_1 + 0x169) | 0x80;
      *(byte *)(param_1 + 0x16a) = *(byte *)(param_1 + 0x16a) | 0x80;
      *(byte *)(param_1 + 0x16b) = *(byte *)(param_1 + 0x16b) | 0x80;
    }
  }
  return;
}



// ==== 8019df20  zz_019df20_ ====

void zz_019df20_(int param_1)

{
  (*(code *)(&PTR_zz_019df5c__80373e0c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019df5c  zz_019df5c_ ====

void zz_019df5c_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8019df8c  zz_019df8c_ ====

void zz_019df8c_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 8019dfbc  zz_019dfbc_ ====

void zz_019dfbc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_019e00c__80373e20)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019e00c  zz_019e00c_ ====

void zz_019e00c_(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043b494;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b498,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043b484;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b480;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 8019e138  zz_019e138_ ====

void zz_019e138_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043b498,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043b480;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043b494;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 8019e1f4  zz_019e1f4_ ====

void zz_019e1f4_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b490 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043b48c;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b490 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043b480;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar4 = (double)FLOAT_8043b484;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8019e310  zz_019e310_ ====

void zz_019e310_(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b478) * FLOAT_8043b46c);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043b46c,param_1);
  FUN_80067310((double)FLOAT_8043b48c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
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
  zz_00b22f4_(param_1);
  return;
}



// ==== 8019e3e0  zz_019e3e0_ ====

void zz_019e3e0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8019e414  zz_019e414_ ====

void zz_019e414_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_019e7dc__80375070;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_019e510__80375074;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_019e5ec__80375078;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_019e5f0__8037507c;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_019e730__80375080;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_019e734__80375084;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_019e738__80375088;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_019e73c__8037508c;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80375090;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_019e740__80375094;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80375098;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_8037509c;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_803750a0;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_803750a4;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_803750a8;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_803750ac;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80375128;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80375480;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80375c60;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bb714;
  *(undefined **)(param_1 + 0x27c) = &DAT_80375390;
  return;
}



// ==== 8019e510  zz_019e510_ ====

uint zz_019e510_(uint param_1)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  uVar2 = param_1;
  if (*(short *)(param_1 + 1000) == 0xb07) {
    zz_00c627c_(param_1,2,param_1 + 0x168);
    bVar3 = zz_01fcc50_(param_1,1,param_1 + 0x150,param_1 + 0x169);
    uVar2 = (uint)bVar3;
    if ('\b' < *(char *)(param_1 + 0x3ee)) {
      bVar3 = zz_01fcc50_(param_1,1,param_1 + 0x15c,param_1 + 0x16a);
      uVar2 = (uint)bVar3;
    }
  }
  fVar1 = FLOAT_8043b4a8;
  *(undefined1 *)(param_1 + 0x168) = 1;
  *(undefined1 *)(param_1 + 0x169) = 1;
  *(undefined1 *)(param_1 + 0x16a) = 1;
  *(undefined1 *)(param_1 + 0x16b) = 1;
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x154) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x160) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x28);
  return uVar2;
}



// ==== 8019e5ec  zz_019e5ec_ ====

void zz_019e5ec_(void)

{
  return;
}



// ==== 8019e5f0  zz_019e5f0_ ====

/* WARNING: Removing unreachable block (ram,0x8019e708) */
/* WARNING: Removing unreachable block (ram,0x8019e600) */

void zz_019e5f0_(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  float afStack_3c [3];
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    local_30 = 0x43300000;
    uStack_2c = (int)*(short *)(param_1 + 0x18da) ^ 0x80000000;
    iVar4 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043b4b8) * FLOAT_8043b4ac
                 );
    local_28 = (longlong)iVar4;
    *(short *)(param_1 + 0x18da) = (short)iVar4;
  }
  if (*(short *)(param_1 + 1000) == 0xb07) {
    local_48 = *(float *)(param_1 + 0xb20);
    dVar6 = (double)FLOAT_8043b4b0;
    iVar4 = 0;
    local_44 = *(undefined4 *)(param_1 + 0xb30);
    local_40 = *(undefined4 *)(param_1 + 0xb40);
    pfVar1 = (float *)(param_1 + 0x150);
    pfVar3 = &local_48;
    do {
      pfVar2 = pfVar1;
      gnt4_PSVECSubtract_bl(pfVar2,pfVar3,afStack_3c);
      dVar5 = gnt4_PSVECMag_bl(afStack_3c);
      if ((double)(float)(dVar6 * (double)*(float *)(param_1 + 0xb4)) < dVar5) {
        zz_006ebb4_(afStack_3c,afStack_3c);
        gnt4_PSQUATScale_bl((double)(FLOAT_8043b4b0 * *(float *)(param_1 + 0xb4)),afStack_3c,
                            afStack_3c);
        gnt4_PSVECAdd_bl(afStack_3c,pfVar3,pfVar2);
      }
      iVar4 = iVar4 + 1;
      pfVar1 = pfVar2 + 3;
      pfVar3 = pfVar2;
    } while (iVar4 < 2);
  }
  return;
}



// ==== 8019e730  zz_019e730_ ====

void zz_019e730_(void)

{
  return;
}



// ==== 8019e734  zz_019e734_ ====

void zz_019e734_(void)

{
  return;
}



// ==== 8019e738  zz_019e738_ ====

void zz_019e738_(void)

{
  return;
}



// ==== 8019e73c  zz_019e73c_ ====

void zz_019e73c_(void)

{
  return;
}



// ==== 8019e740  zz_019e740_ ====

void zz_019e740_(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_zz_019e77c__803750b0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8019e77c  zz_019e77c_ ====

void zz_019e77c_(void)

{
  return;
}



// ==== 8019e780  zz_019e780_ ====

void zz_019e780_(void)

{
  return;
}



// ==== 8019e784  zz_019e784_ ====

void zz_019e784_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0xb05) {
    zz_001ab6c_(param_1,0x44);
  }
  else if (*(short *)(param_1 + 1000) == 0xb07) {
    zz_001ab6c_(param_1,0x75);
  }
  return;
}



// ==== 8019e7d0  zz_019e7d0_ ====

void zz_019e7d0_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 0xff;
  return;
}



// ==== 8019e7dc  zz_019e7dc_ ====

void zz_019e7dc_(int param_1)

{
  (*(code *)(&PTR_zz_019e818__803750c0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019e818  zz_019e818_ ====

void zz_019e818_(int param_1)

{
  (*(code *)(&PTR_zz_019e854__803750cc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019e854  zz_019e854_ ====

void zz_019e854_(int param_1)

{
  zz_014a200_(param_1,&DAT_80435740);
  return;
}



// ==== 8019e878  zz_019e878_ ====

void zz_019e878_(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80435748);
  return;
}



// ==== 8019e89c  zz_019e89c_ ====

void zz_019e89c_(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xb05) {
    zz_0082824_(param_1,0x40);
  }
  else if (*(short *)(param_1 + 1000) == 0xb07) {
    zz_0082824_(param_1,0x71);
    *(byte *)(param_1 + 0x168) = *(byte *)(param_1 + 0x168) | 0x80;
    *(byte *)(param_1 + 0x169) = *(byte *)(param_1 + 0x169) | 0x80;
    *(byte *)(param_1 + 0x16a) = *(byte *)(param_1 + 0x16a) | 0x80;
    *(byte *)(param_1 + 0x16b) = *(byte *)(param_1 + 0x16b) | 0x80;
  }
  return;
}



// ==== 8019e91c  zz_019e91c_ ====

void zz_019e91c_(int param_1)

{
  (*(code *)(&PTR_zz_019e958__803750e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019e958  zz_019e958_ ====

void zz_019e958_(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 8019e97c  zz_019e97c_ ====

void zz_019e97c_(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 8019e9a0  zz_019e9a0_ ====

void zz_019e9a0_(void)

{
  return;
}



// ==== 8019e9a4  zz_019e9a4_ ====

void zz_019e9a4_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_019edbc__803763e8;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_019eab8__803763ec;
  *(undefined **)(param_1 + 0x4bc) = PTR_LAB_803763f0;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_019ebc8__803763f4;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_019ecbc__803763f8;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_019ecc0__803763fc;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_019ecc4__80376400;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_019ecc8__80376404;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80376408;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_019eccc__8037640c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80376410;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80376414;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80376418;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_8037641c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80376420;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80376424;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_803765e0;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80376a60;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80377240;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_80376960;
  if (*(short *)(param_1 + 1000) == 0xc) {
    *(undefined **)(param_1 + 0x4b0) = &DAT_803766f8;
    return;
  }
  return;
}



// ==== 8019eab8  zz_019eab8_ ====

uint zz_019eab8_(uint param_1)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = param_1;
  if (*(short *)(param_1 + 1000) == 0xc) {
    zz_00c627c_(param_1,4,param_1 + 0x168);
    zz_004d6dc_(param_1,9);
    bVar3 = zz_01fcc50_(param_1,2,param_1 + 0x150,param_1 + 0x169);
    uVar2 = (uint)bVar3;
    if ('\b' < *(char *)(param_1 + 0x3ee)) {
      bVar3 = zz_01fcc50_(param_1,2,param_1 + 0x15c,param_1 + 0x16a);
      uVar2 = (uint)bVar3;
    }
  }
  fVar1 = FLOAT_8043b4c0;
  *(undefined1 *)(param_1 + 0x168) = 1;
  *(undefined1 *)(param_1 + 0x169) = 1;
  *(undefined1 *)(param_1 + 0x16a) = 1;
  *(undefined1 *)(param_1 + 0x16b) = 1;
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x154) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x160) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x28);
  return uVar2;
}



// ==== 8019ebc8  zz_019ebc8_ ====

/* WARNING: Removing unreachable block (ram,0x8019ec94) */
/* WARNING: Removing unreachable block (ram,0x8019ebd8) */

void zz_019ebc8_(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float afStack_2c [3];
  
  if (*(short *)(param_1 + 1000) == 0xc) {
    local_38 = *(float *)(param_1 + 0xb20);
    dVar6 = (double)FLOAT_8043b4c4;
    iVar4 = 0;
    local_34 = *(undefined4 *)(param_1 + 0xb30);
    local_30 = *(undefined4 *)(param_1 + 0xb40);
    pfVar1 = (float *)(param_1 + 0x150);
    pfVar3 = &local_38;
    do {
      pfVar2 = pfVar1;
      gnt4_PSVECSubtract_bl(pfVar2,pfVar3,afStack_2c);
      dVar5 = gnt4_PSVECMag_bl(afStack_2c);
      if ((double)(float)(dVar6 * (double)*(float *)(param_1 + 0xb4)) < dVar5) {
        zz_006ebb4_(afStack_2c,afStack_2c);
        gnt4_PSQUATScale_bl((double)(FLOAT_8043b4c4 * *(float *)(param_1 + 0xb4)),afStack_2c,
                            afStack_2c);
        gnt4_PSVECAdd_bl(afStack_2c,pfVar3,pfVar2);
      }
      iVar4 = iVar4 + 1;
      pfVar1 = pfVar2 + 3;
      pfVar3 = pfVar2;
    } while (iVar4 < 2);
  }
  return;
}



// ==== 8019ecbc  zz_019ecbc_ ====

void zz_019ecbc_(void)

{
  return;
}



// ==== 8019ecc0  zz_019ecc0_ ====

void zz_019ecc0_(void)

{
  return;
}



// ==== 8019ecc4  zz_019ecc4_ ====

void zz_019ecc4_(void)

{
  return;
}



// ==== 8019ecc8  zz_019ecc8_ ====

void zz_019ecc8_(void)

{
  return;
}



// ==== 8019eccc  zz_019eccc_ ====

void zz_019eccc_(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_zz_019ed08__80376428)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8019ed08  zz_019ed08_ ====

void zz_019ed08_(void)

{
  return;
}



// ==== 8019ed0c  zz_019ed0c_ ====

void zz_019ed0c_(int param_1,int param_2)

{
  undefined4 local_8;
  
  local_8 = DAT_8043b4c8;
  if ('\b' < *(char *)(param_1 + 0x3ee)) {
    if (*(short *)(param_1 + 1000) == 8) {
      zz_0099e70_(param_1,*(undefined1 *)((int)&local_8 + param_2 * 2));
    }
    else if (*(short *)(param_1 + 1000) == 0xc) {
      zz_0099e70_(param_1,*(undefined1 *)((int)&local_8 + param_2 * 2 + 1));
    }
  }
  return;
}



// ==== 8019ed80  zz_019ed80_ ====

void zz_019ed80_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x3c);
  return;
}



// ==== 8019edac  zz_019edac_ ====

void zz_019edac_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 0xff;
  return;
}



// ==== 8019edb8  zz_019edb8_ ====

void zz_019edb8_(void)

{
  return;
}



// ==== 8019edbc  zz_019edbc_ ====

void zz_019edbc_(int param_1)

{
  (*(code *)(&PTR_zz_019edf8__8037643c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019edf8  zz_019edf8_ ====

void zz_019edf8_(int param_1)

{
  (*(code *)(&PTR_zz_019ee34__80376448)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019ee34  zz_019ee34_ ====

void zz_019ee34_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_zz_019ee7c__80376470)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019ee7c  zz_019ee7c_ ====

void zz_019ee7c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043b4cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_8043b4cc,param_1,2,2,9,0xffffffff,0xffffffff);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_019f820_(param_1);
  fVar1 = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x4c) = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x44) = fVar1;
  return;
}



// ==== 8019ef14  zz_019ef14_ ====

void zz_019ef14_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043b4d0;
  if ((iVar3 == 0) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019f850_(param_1);
  }
  return;
}



// ==== 8019efa8  zz_019efa8_ ====

void zz_019efa8_(int param_1)

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
      dVar2 = (double)FLOAT_8043b4cc;
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



// ==== 8019f0a8  zz_019f0a8_ ====

void zz_019f0a8_(int param_1)

{
  (*(code *)(&PTR_zz_019f0e4__8037647c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019f0e4  zz_019f0e4_ ====

void zz_019f0e4_(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043b4cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  zz_019f820_(param_1);
  return;
}



// ==== 8019f144  zz_019f144_ ====

void zz_019f144_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_8043b4d0;
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
      zz_019f850_(param_1);
    }
  }
  return;
}



// ==== 8019f1f0  zz_019f1f0_ ====

void zz_019f1f0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_8019f2e0;
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
      if (((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
        if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
          zz_006bf80_(param_9);
          dVar2 = (double)FLOAT_8043b4cc;
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006a3d0_(param_9,'\0',3,2);
      return;
    }
  }
  if (*(char *)(param_9 + 0x1cee) == '\0') {
    return;
  }
LAB_8019f2e0:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8019f314  zz_019f314_ ====

void zz_019f314_(int param_1)

{
  (*(code *)(&PTR_zz_019f350__80376488)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019f350  zz_019f350_ ====

void zz_019f350_(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043b4cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) {
    zz_006a5a4_(param_1);
    zz_004beb8_((double)FLOAT_8043b4cc,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_019f820_(param_1);
  return;
}



// ==== 8019f3e4  zz_019f3e4_ ====

void zz_019f3e4_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_8043b4d0;
  if ((iVar3 < 1) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019f850_(param_1);
  }
  return;
}



// ==== 8019f478  zz_019f478_ ====

void zz_019f478_(double param_1,double param_2,double param_3,double param_4,double param_5,
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
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006bf80_(param_9);
      dVar2 = (double)FLOAT_8043b4cc;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8019f570  zz_019f570_ ====

void zz_019f570_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_zz_019f5b8__80376494)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019f5b8  zz_019f5b8_ ====

void zz_019f5b8_(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_8043b4d4;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b4cc,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043b4cc,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_019f820_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b4d0;
  return;
}



// ==== 8019f68c  zz_019f68c_ ====

void zz_019f68c_(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_8043b4d4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019f850_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8019f720  zz_019f720_ ====

void zz_019f720_(double param_1,double param_2,double param_3,double param_4,double param_5,
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
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006bf80_(param_9);
      dVar2 = (double)FLOAT_8043b4cc;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      *(undefined1 *)(param_9 + 0x581) = 3;
      zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8019f820  zz_019f820_ ====

void zz_019f820_(int param_1)

{
  float fVar1;
  float fVar2;
  
  if (*(char *)(param_1 + 0x6ee) == '\0') {
    *(undefined1 *)(param_1 + 0x6ef) = 5;
  }
  fVar1 = FLOAT_8043b4d8;
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  fVar2 = FLOAT_8043b4dc;
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x560) = fVar2;
  return;
}



// ==== 8019f850  zz_019f850_ ====

void zz_019f850_(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if ((iVar1 != 0) && (zz_006ee14_(param_1,0), *(short *)(param_1 + 1000) == 0xc)) {
    *(byte *)(param_1 + 0x168) = *(byte *)(param_1 + 0x168) | 0x80;
    *(byte *)(param_1 + 0x169) = *(byte *)(param_1 + 0x169) | 0x80;
    *(byte *)(param_1 + 0x16a) = *(byte *)(param_1 + 0x16a) | 0x80;
    *(byte *)(param_1 + 0x16b) = *(byte *)(param_1 + 0x16b) | 0x80;
  }
  return;
}



// ==== 8019f8ec  zz_019f8ec_ ====

void zz_019f8ec_(int param_1)

{
  (*(code *)(&PTR_zz_019f928__803764a0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019f928  zz_019f928_ ====

void zz_019f928_(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 8019f950  zz_019f950_ ====

void zz_019f950_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_019f9a0__803764cc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019f9a0  zz_019f9a0_ ====

void zz_019f9a0_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043b4e0;
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
  fVar1 = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x50) = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_019fa70_(param_1);
  return;
}



// ==== 8019fa70  zz_019fa70_ ====

void zz_019fa70_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b4e4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043b4d0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar5 = zz_006d144_(param_1,0xc0), iVar5 != 0)) {
    fVar1 = FLOAT_8043b4dc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x48) = FLOAT_8043b4ec;
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / fVar1;
    }
    else {
      iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
      local_1c = *(float *)(iVar5 + 0x8e0);
      local_18 = *(float *)(iVar5 + 0x8f0);
      local_14 = *(undefined4 *)(iVar5 + 0x900);
      local_28 = *(float *)(param_1 + 0x518);
      local_20 = *(undefined4 *)(param_1 + 0x520);
      local_24 = FLOAT_8043b4e8 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
      gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
      fVar1 = FLOAT_8043b4d0;
      *(float *)(param_1 + 0x48) = local_18 / FLOAT_8043b4dc;
      local_18 = fVar1;
      dVar6 = gnt4_PSVECMag_bl(&local_1c);
      *(float *)(param_1 + 0x44) = (float)(dVar6 / (double)FLOAT_8043b4dc);
    }
    fVar4 = FLOAT_8043b4fc;
    fVar3 = FLOAT_8043b4f8;
    fVar2 = FLOAT_8043b4dc;
    fVar1 = FLOAT_8043b4d0;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_8043b4f0);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar3 * (-*(float *)(param_1 + 0x48) / fVar2);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x50);
    if (fVar4 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b4cc,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019fc70  zz_019fc70_ ====

void zz_019fc70_(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b4d4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(float *)(param_1 + 0x48) < FLOAT_8043b4f8) {
    dVar1 = (double)FLOAT_8043b4cc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar1,param_1,0xf,3,6,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019fd00  zz_019fd00_ ====

void zz_019fd00_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_8043b500;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) = (float)(DOUBLE_8043b508 * (double)*(float *)(param_1 + 0x38));
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_8043b4dc;
    }
    *(float *)(param_1 + 0x48) = FLOAT_8043b510;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 8019fda4  zz_019fda4_ ====

void zz_019fda4_(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  uVar2 = FUN_80066838((double)FLOAT_8043b514,param_1);
  fVar1 = FLOAT_8043b4d0;
  if (0 < (int)uVar2) {
    *(float *)(param_1 + 0x4c) = FLOAT_8043b4d0;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006eddc_((double)FLOAT_8043b518,param_1,(float *)(param_1 + 0x44));
  FUN_80067310((double)FLOAT_8043b4d4,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar1 <= *(float *)(param_1 + 0x558)) {
    iVar3 = zz_00677b0_(param_1);
    fVar1 = FLOAT_8043b51c;
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar1;
      zz_0066530_(param_1,0x2c);
      zz_004beb8_((double)FLOAT_8043b4cc,param_1,0xf,3,7,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,2);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8019febc  zz_019febc_ ====

void zz_019febc_(int param_1)

{
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043b4d0) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8019ff34  zz_019ff34_ ====

void zz_019ff34_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_019ff84__803764e4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019ff84  zz_019ff84_ ====

void zz_019ff84_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    iVar4 = FUN_800667a0(param_1);
    if ((float)((double)CONCAT44(0x43300000,(int)(short)iVar4 ^ 0x80000000) - DOUBLE_8043b528) <
        FLOAT_8043b520) {
      *(undefined1 *)(param_1 + 0x581) = 4;
      zz_019f950_(param_1);
      return;
    }
  }
  fVar2 = FLOAT_8043b524;
  fVar1 = FLOAT_8043b4d0;
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
  zz_004beb8_((double)FLOAT_8043b4cc,param_1,0xf,3,8,0xffffffff,0xffffffff);
  return;
}



// ==== 801a00b8  zz_01a00b8_ ====

void zz_01a00b8_(int param_1)

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
  gnt4_PSQUATScale_bl((double)(FLOAT_8043b4c4 * *(float *)(param_1 + 0xb4)),&local_18,&local_18);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x518),&local_18,&local_18);
  zz_006e6c4_(param_1,0xc0,(short *)(param_1 + 0x54e),&local_18);
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b4dc * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_8043b4d4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b4dc * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043b4d0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043b530,param_1), 0 < (int)uVar3)) {
    fVar2 = FLOAT_8043b534;
    fVar1 = FLOAT_8043b51c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / fVar2;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) / fVar2;
  }
  return;
}



// ==== 801a022c  zz_01a022c_ ====

void zz_01a022c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b4d4,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043b4d0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b4dc * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b4dc * -dVar2);
  }
  return;
}



// ==== 801a02e8  zz_01a02e8_ ====

void zz_01a02e8_(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar1 = FLOAT_8043b4d0;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043b518,param_1);
  FUN_80067310((double)FLOAT_8043b4d4,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043b4d4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043b4d4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801a0414  zz_01a0414_ ====

void zz_01a0414_(int param_1)

{
  zz_01a0434_(param_1);
  return;
}



// ==== 801a0434  zz_01a0434_ ====

void zz_01a0434_(int param_1)

{
  zz_00ff2bc_(param_1);
  return;
}



// ==== 801a0458  zz_01a0458_ ====

void zz_01a0458_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  fVar4 = FLOAT_8043b538;
  fVar3 = FLOAT_8043b51c;
  fVar2 = FLOAT_8043b4d0;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    fVar1 = FLOAT_8043b4cc;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar4;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  iVar5 = zz_006dbe0_(param_1,2,1,1);
  if ((iVar5 != 0) && (*(short *)(param_1 + 1000) == 0xc)) {
    zz_007db5c_(param_1,5);
  }
  return;
}



// ==== 801a04f0  zz_01a04f0_ ====

void zz_01a04f0_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01a061c__80377808;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01a05ec__8037780c;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_01a05f0__80377810;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01a05f4__80377814;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01a060c__80377818;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01a0610__8037781c;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01a0614__80377820;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01a0618__80377824;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80377828;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_8037782c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80377830;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80377834;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80377838;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_8037783c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80377840;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80377844;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80377918;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80377b80;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80377fc0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_80377ac0;
  return;
}



// ==== 801a05ec  zz_01a05ec_ ====

void zz_01a05ec_(void)

{
  return;
}



// ==== 801a05f0  zz_01a05f0_ ====

void zz_01a05f0_(void)

{
  return;
}



// ==== 801a05f4  zz_01a05f4_ ====

void zz_01a05f4_(int param_1)

{
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  return;
}



// ==== 801a060c  zz_01a060c_ ====

void zz_01a060c_(void)

{
  return;
}



// ==== 801a0610  zz_01a0610_ ====

void zz_01a0610_(void)

{
  return;
}



// ==== 801a0614  zz_01a0614_ ====

void zz_01a0614_(void)

{
  return;
}



// ==== 801a0618  zz_01a0618_ ====

void zz_01a0618_(void)

{
  return;
}



// ==== 801a061c  zz_01a061c_ ====

void zz_01a061c_(int param_1)

{
  (*(code *)(&PTR_zz_01a0658__80377848)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801a0658  zz_01a0658_ ====

void zz_01a0658_(int param_1)

{
  (*(code *)(&PTR_zz_01a0694__80377854)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801a0694  zz_01a0694_ ====

void zz_01a0694_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00fed6c_(param_1);
  return;
}



// ==== 801a06c8  zz_01a06c8_ ====

void zz_01a06c8_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a0724__80377880)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a0724  zz_01a0724_ ====

void zz_01a0724_(int param_1)

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
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043b540;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b544,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043b548;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801a082c  zz_01a082c_ ====

void zz_01a082c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043b544,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_8043b54c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar1) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_8043b550;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    fVar2 = FLOAT_8043b54c;
    if (*(int *)(param_1 + 0xcc) == 0) {
      fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    }
    else {
      fVar1 = *(float *)(param_1 + 0x760) *
              (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                     DOUBLE_8043b558) * FLOAT_8043b554;
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043b550;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x80c) = fVar2;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801a097c  zz_01a097c_ ====

void zz_01a097c_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043b544,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043b54c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043b560,param_1), uVar3 != 0)) {
    fVar1 = FLOAT_8043b564;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801a0a44  zz_01a0a44_ ====

void zz_01a0a44_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    zz_006ed8c_((double)FLOAT_8043b544,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    fVar2 = FLOAT_8043b54c;
    fVar1 = FLOAT_8043b540;
    if (*(char *)(param_1 + 0x1cf0) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      fVar3 = FLOAT_8043b568;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x48) = fVar1;
      *(float *)(param_1 + 0x50) = fVar3;
      zz_0066530_(param_1,0x2d);
      zz_00b2190_(param_1,0);
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801a0aec  zz_01a0aec_ ====

void zz_01a0aec_(int param_1)

{
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043b56c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801a0b5c  zz_01a0b5c_ ====

void zz_01a0b5c_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00fed6c_(param_1);
  return;
}



// ==== 801a0b90  zz_01a0b90_ ====

void zz_01a0b90_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a0be0__803778ac)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a0be0  zz_01a0be0_ ====

void zz_01a0be0_(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043b540;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 4;
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
  gnt4_PSQUATScale_bl((double)FLOAT_8043b544,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043b548;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801a0cf8  zz_01a0cf8_ ====

void zz_01a0cf8_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b544,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043b54c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043b550;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 801a0dc4  zz_01a0dc4_ ====

void zz_01a0dc4_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b540 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar6 = (double)FLOAT_8043b56c;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b540 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_8043b54c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_800668cc((double)FLOAT_8043b570,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043b574;
    dVar5 = (double)FLOAT_8043b548;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801a0ec8  zz_01a0ec8_ ====

void zz_01a0ec8_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  zz_006ed8c_((double)FLOAT_8043b578,param_1);
  FUN_80067310((double)FLOAT_8043b56c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043b54c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043b540 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043b540 * -dVar3);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 801a0fa8  zz_01a0fa8_ ====

void zz_01a0fa8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b57c;
  fVar1 = FLOAT_8043b54c;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x44) = FLOAT_8043b54c;
    fVar3 = FLOAT_8043b580;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  }
  zz_006ed8c_((double)FLOAT_8043b584,param_1);
  FUN_80067310((double)FLOAT_8043b56c,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043b558) * FLOAT_8043b588);
  }
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043b56c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801a10e8  zz_01a10e8_ ====

void zz_01a10e8_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01a1290__803786a8;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01a11fc__803786ac;
  *(undefined **)(param_1 + 0x4bc) = PTR_LAB_803786b0;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01a1220__803786b4;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01a1228__803786b8;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01a122c__803786bc;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01a1230__803786c0;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01a1234__803786c4;
  *(undefined **)(param_1 + 0x4d4) = PTR_zz_01a1238__803786c8;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_01a123c__803786cc;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_803786d0;
  *(undefined **)(param_1 + 0x4e0) = PTR_zz_01a1224__803786d4;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_803786d8;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_803786dc;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_803786e0;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_803786e4;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_803782b0;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80378b80;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_803787c0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_803785e8;
  if (*(short *)(param_1 + 1000) == 0x90b) {
    *(undefined **)(param_1 + 0x4b0) = &DAT_803783c8;
    return;
  }
  return;
}



// ==== 801a11fc  zz_01a11fc_ ====

void zz_01a11fc_(void)

{
  return;
}



// ==== 801a1204  zz_01a1204_ ====

void zz_01a1204_(int param_1)

{
  uint in_r0;
  
  if ((in_r0 & 1) != 0) {
    return;
  }
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  *(undefined1 *)(param_1 + 0x6ed) = 0;
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  return;
}



// ==== 801a1220  zz_01a1220_ ====

void zz_01a1220_(void)

{
  return;
}



// ==== 801a1224  zz_01a1224_ ====

void zz_01a1224_(void)

{
  return;
}



// ==== 801a1228  zz_01a1228_ ====

void zz_01a1228_(void)

{
  return;
}



// ==== 801a122c  zz_01a122c_ ====

void zz_01a122c_(void)

{
  return;
}



// ==== 801a1230  zz_01a1230_ ====

void zz_01a1230_(void)

{
  return;
}



// ==== 801a1234  zz_01a1234_ ====

void zz_01a1234_(void)

{
  return;
}



// ==== 801a1238  zz_01a1238_ ====

void zz_01a1238_(void)

{
  return;
}



// ==== 801a123c  zz_01a123c_ ====

void zz_01a123c_(int param_1,char param_2)

{
  if (param_2 == '\x01') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((param_2 < '\x01') && (-1 < param_2)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    zz_001ab6c_(param_1,0x47);
  }
  return;
}



// ==== 801a1290  zz_01a1290_ ====

void zz_01a1290_(int param_1)

{
  (*(code *)(&PTR_zz_01a12cc__803786e8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801a12cc  zz_01a12cc_ ====

void zz_01a12cc_(int param_1)

{
  (*(code *)(&PTR_zz_01a1308__803786f4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801a1308  zz_01a1308_ ====

void zz_01a1308_(int param_1)

{
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  (*(code *)(&PTR_zz_01a134c__80378708)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a134c  zz_01a134c_ ====

void zz_01a134c_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = FLOAT_8043b590;
  dVar3 = (double)FLOAT_8043b598;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar3,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}



// ==== 801a142c  zz_01a142c_ ====

void zz_01a142c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043b594;
  if (iVar3 != 1) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) goto LAB_801a14e4;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01a1af0_(param_1);
  }
LAB_801a14e4:
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043b5a0 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801a1514  zz_01a1514_ ====

void zz_01a1514_(int param_1)

{
  int iVar1;
  double dVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  iVar1 = zz_01a1bbc_(param_1);
  if (iVar1 == 0) {
    iVar1 = zz_004cd24_(param_1,0xf);
    if ((iVar1 == 1) || ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0)) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a474_(param_1);
    }
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_8043b5a0 < dVar2) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    zz_006bf80_(param_1);
    dVar2 = (double)FLOAT_8043b598;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    zz_004beb8_(dVar2,param_1,0xf,2,3,0xffffffff,0xffffffff);
    if (*(short *)(param_1 + 1000) == 0x90b) {
      zz_00f0104_(param_1,0x24,2);
    }
  }
  return;
}



// ==== 801a1620  zz_01a1620_ ====

void zz_01a1620_(int param_1)

{
  (*(code *)(&PTR_zz_01a165c__80378714)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a165c  zz_01a165c_ ====

void zz_01a165c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043b5a4;
  dVar2 = (double)FLOAT_8043b598;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  return;
}



// ==== 801a16b0  zz_01a16b0_ ====

void zz_01a16b0_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_8043b594;
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
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_01a1af0_(param_1);
    }
  }
  return;
}



// ==== 801a1798  zz_01a1798_ ====

void zz_01a1798_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  iVar1 = zz_01a1bbc_(param_9);
  if (iVar1 == 0) {
    zz_004cd24_(param_9,1);
    if ((*(char *)(param_9 + 0x1cee) != '\0') || ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0)) {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  else {
    zz_006bf80_(param_9);
    *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
    if (*(short *)(param_9 + 1000) == 0x90b) {
      zz_00f0104_(param_9,0x24,2);
    }
    uVar2 = *(uint *)(param_9 + 0x5e0);
    if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
      if ((uVar2 & 0x10) != 0) {
        dVar3 = (double)FLOAT_8043b598;
        *(undefined1 *)(param_9 + 0x581) = 1;
        zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
        return;
      }
      if ((uVar2 & 0x20) != 0) {
        dVar3 = (double)FLOAT_8043b598;
        *(undefined1 *)(param_9 + 0x581) = 3;
        zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
        return;
      }
      zz_006a3d0_(param_9,'\0',0,2);
      return;
    }
    dVar3 = (double)FLOAT_8043b598;
    *(undefined1 *)(param_9 + 0x581) = 2;
    zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
  }
  return;
}



