// ==== 800ba3b4  FUN_800ba3b4 ====

void FUN_800ba3b4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0xf);
  return;
}



// ==== 800ba3ec  FUN_800ba3ec ====

void FUN_800ba3ec(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x78);
  return;
}



// ==== 800ba418  FUN_800ba418 ====

void FUN_800ba418(int param_1)

{
  (*(code *)(&PTR_FUN_803003a8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800ba454  FUN_800ba454 ====

void FUN_800ba454(int param_1)

{
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) -
                           DOUBLE_804384f0) * FLOAT_804384ec);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803003b4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ba4d4  FUN_800ba4d4 ====

void FUN_800ba4d4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803003c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ba51c  FUN_800ba51c ====

void FUN_800ba51c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804384f8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  FUN_800bae3c(param_1);
  fVar1 = FLOAT_804384fc;
  *(float *)(param_1 + 0x50) = FLOAT_804384fc;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804384fc;
  return;
}



// ==== 800ba61c  FUN_800ba61c ====

/* WARNING: Removing unreachable block (ram,0x800ba700) */
/* WARNING: Removing unreachable block (ram,0x800ba62c) */

void FUN_800ba61c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804384fc;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804384fc;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bae68(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438504 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ba71c  FUN_800ba71c ====

void FUN_800ba71c(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_804384fc) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_804384fc) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_804384f8;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
        zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_800ba850;
    }
    *(float *)(param_1 + 0x55c) = FLOAT_804384fc;
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_80438504) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_800ba850:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800ba8c8  FUN_800ba8c8 ====

void FUN_800ba8c8(int param_1)

{
  (*(code *)(&PTR_FUN_803003d4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ba904  FUN_800ba904 ====

void FUN_800ba904(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 9;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 3;
  }
  if ((uVar1 & 0x20) != 0) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_804384f8,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  FUN_800bae3c(param_1);
  return;
}



// ==== 800ba994  FUN_800ba994 ====

void FUN_800ba994(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804384fc;
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
      FUN_800bae68(param_1);
    }
  }
  return;
}



// ==== 800baa68  FUN_800baa68 ====

void FUN_800baa68(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_804384fc) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804384fc) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          zz_004beb8_((double)FLOAT_804384f8,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_804384f8;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,4,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          dVar3 = (double)FLOAT_804384f8;
          *(undefined1 *)(param_9 + 0x581) = 2;
          zz_004beb8_(dVar3,param_9,1,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_800babfc;
    }
    *(float *)(param_9 + 0x55c) = FLOAT_804384fc;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800babfc:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800bac30  FUN_800bac30 ====

void FUN_800bac30(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803003e0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bac78  FUN_800bac78 ====

void FUN_800bac78(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80438508;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_804384f8,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x16')) {
    zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0x16,0xffffffff,0xffffffff);
  }
  FUN_800bae3c(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804384fc;
  return;
}



// ==== 800bad4c  FUN_800bad4c ====

/* WARNING: Removing unreachable block (ram,0x800bae20) */
/* WARNING: Removing unreachable block (ram,0x800bad5c) */

void FUN_800bad4c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804384fc;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_80438508,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_804384fc;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bae68(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800bae3c  FUN_800bae3c ====

void FUN_800bae3c(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438510;
  fVar1 = FLOAT_8043850c;
  *(float *)(param_1 + 0x560) = FLOAT_8043850c;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 100;
  return;
}



// ==== 800bae68  FUN_800bae68 ====

/* WARNING: Removing unreachable block (ram,0x800bafe4) */
/* WARNING: Removing unreachable block (ram,0x800bae78) */

void FUN_800bae68(int param_1)

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
  
  fVar2 = FLOAT_80438510;
  fVar1 = FLOAT_8043850c;
  *(float *)(param_1 + 0x560) = FLOAT_8043850c;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1918) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xae4);
      dVar5 = (double)*(float *)(param_1 + 0xaf4);
      local_20 = *(undefined4 *)(param_1 + 0xb04);
      local_24 = FLOAT_804384fc;
      dVar6 = gnt4_PSVECMag_bl(&local_28);
      iVar3 = FUN_800452a0(dVar5,dVar6);
      local_28 = *(float *)(param_1 + 0xaf0);
      local_24 = *(float *)(param_1 + 0xb00);
      local_20 = *(undefined4 *)(param_1 + 0xb10);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar6 = (double)local_24;
      local_24 = FLOAT_804384fc;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar6,dVar5);
      *(short *)(param_1 + 0x1918) = (short)iVar3 + (short)iVar4;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19c2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xae4),(short *)(param_1 + 0x1916),
                  (undefined4 *)(param_1 + 0x1358),(float *)(param_1 + 0xf84),
                  (float *)(param_1 + 0x1658));
    }
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
      FUN_801177d0(param_1,*(undefined1 *)(param_1 + 0x172));
      *(char *)(param_1 + 0x172) = *(char *)(param_1 + 0x172) + '\x01';
      *(byte *)(param_1 + 0x172) = *(byte *)(param_1 + 0x172) & 3;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}



// ==== 800bb004  FUN_800bb004 ====

void FUN_800bb004(int param_1)

{
  (*(code *)(&PTR_FUN_803003ec)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800bb040  FUN_800bb040 ====

void FUN_800bb040(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 800bb064  FUN_800bb064 ====

void FUN_800bb064(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}



// ==== 800bb088  FUN_800bb088 ====

void FUN_800bb088(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}



// ==== 800bb0ac  FUN_800bb0ac ====

void FUN_800bb0ac(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 800bb0d0  FUN_800bb0d0 ====

void FUN_800bb0d0(int param_1)

{
  (*(code *)(&PTR_FUN_80300400)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800bb10c  FUN_800bb10c ====

void FUN_800bb10c(int param_1)

{
  *(undefined1 *)(param_1 + 0x171) = 4;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (**(code **)(&DAT_80433ae0 + *(char *)(param_1 + 0x540) * 4))();
  return;
}



// ==== 800bb160  FUN_800bb160 ====

void FUN_800bb160(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_804384fc;
  *(float *)(param_1 + 0x50) = FLOAT_804384fc;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_804384f8,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800bb220  FUN_800bb220 ====

void FUN_800bb220(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc1);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_0085638_(param_1,2);
    }
    zz_0066530_(param_1,0x2d);
    fVar1 = FLOAT_804384f8;
    *(float *)(param_1 + 0x44) = FLOAT_80438514;
    fVar2 = FLOAT_8043850c;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_80438508,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  iVar3 = zz_00679d0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438508 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80438508 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800bb4bc  FUN_800bb4bc ====

void FUN_800bb4bc(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x208) {
    FUN_800be58c(param_1,0);
    FUN_800f1b28(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x20e) {
    FUN_800be58c(param_1,1);
    FUN_800f1b28(param_1,1);
  }
  *(undefined1 *)(param_1 + 0x144) = 0;
  zz_00c74ec_(param_1,3);
  return;
}



// ==== 800bb53c  FUN_800bb53c ====

void FUN_800bb53c(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(short *)(param_1 + 0x1dfc) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000) -
                             DOUBLE_80438520) * FLOAT_80438518);
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
    *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
    *(short *)(param_1 + 0x1918) = *(short *)(param_1 + 0x1918) >> 1;
    *(short *)(param_1 + 0x18fe) = *(short *)(param_1 + 0x18fe) >> 1;
    *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  }
  return;
}



// ==== 800bb5f4  FUN_800bb5f4 ====

void FUN_800bb5f4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803018b0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800bb638  FUN_800bb638 ====

void FUN_800bb638(int param_1,int param_2)

{
  zz_0137540_(param_1,(char)*(undefined4 *)(&DAT_80433ae8 + param_2 * 4));
  return;
}



// ==== 800bb66c  FUN_800bb66c ====

void FUN_800bb66c(int param_1)

{
  (*(code *)(&PTR_FUN_803018c4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800bb6a8  FUN_800bb6a8 ====

void FUN_800bb6a8(int param_1)

{
  (*(code *)(&PTR_FUN_803018d0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800bb6e4  FUN_800bb6e4 ====

void FUN_800bb6e4(int param_1)

{
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) -
                           DOUBLE_80438520) * FLOAT_80438528);
  (*(code *)(&PTR_FUN_803018dc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800bb758  FUN_800bb758 ====

void FUN_800bb758(int param_1)

{
  (*(code *)(&PTR_FUN_80301904)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bb794  FUN_800bb794 ====

void FUN_800bb794(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_006e004_(param_1);
  if ((int)uVar1 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',3,2);
    }
  }
  else {
    zz_006dee8_(param_1,1);
    FUN_800bbff0(param_1);
  }
  return;
}



// ==== 800bb818  FUN_800bb818 ====

void FUN_800bb818(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  fVar2 = FLOAT_8043852c;
  if ((iVar3 < 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',3,2);
    }
    return;
  }
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
    return;
  }
  if (iVar3 < 1) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  FUN_800bc428(param_1);
  return;
}



// ==== 800bb8e8  FUN_800bb8e8 ====

void FUN_800bb8e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043852c) {
    if (((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) && ('\0' < *(char *)(param_9 + 0x6eb))) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        FUN_800bc2d8(param_9);
        return;
      }
      goto LAB_800bb9b8;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
    iVar1 = zz_006dee8_(param_9,1);
    if ((iVar1 < 0) &&
       ((*(char *)(param_9 + 0x5db) == '\x01' || (*(char *)(param_9 + 0x5db) == '\a')))) {
      param_11 = 0;
      dVar2 = (double)zz_006d0dc_(param_9,0x81,0);
    }
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800bb9b8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800bb9ec  FUN_800bb9ec ====

void FUN_800bb9ec(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80301910)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bba34  FUN_800bba34 ====

void FUN_800bba34(int param_1)

{
  float fVar1;
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffcf;
  FUN_800bbff0(param_1);
  fVar1 = FLOAT_8043852c;
  *(float *)(param_1 + 0x50) = FLOAT_8043852c;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043852c;
  return;
}



// ==== 800bbae0  FUN_800bbae0 ====

/* WARNING: Removing unreachable block (ram,0x800bbba4) */
/* WARNING: Removing unreachable block (ram,0x800bbaf0) */

void FUN_800bbae0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043852c;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043852c;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bc428(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_00b22f4_(param_1);
  return;
}



// ==== 800bbbc0  FUN_800bbbc0 ====

void FUN_800bbbc0(int param_1)

{
  float fVar1;
  
  zz_006d0dc_(param_1,0xc1,0);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043852c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar1 < *(float *)(param_1 + 0x558)) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    zz_00b22f4_(param_1);
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800bbc90  FUN_800bbc90 ====

void FUN_800bbc90(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  zz_004cd24_(param_9,1);
  if (((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) || (*(char *)(param_9 + 0x6eb) < '\x01')) {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
      return;
    }
  }
  else {
    param_11 = 1;
    param_12 = 0;
    iVar1 = zz_006dbe0_(param_9,0,1,0);
    if (iVar1 != 0) {
      FUN_800bc2d8(param_9);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800bbd38  FUN_800bbd38 ====

void FUN_800bbd38(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80301920)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bbd80  FUN_800bbd80 ====

void FUN_800bbd80(int param_1)

{
  double dVar1;
  
  FUN_800bbff0(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80438534;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043852c;
  return;
}



// ==== 800bbde8  FUN_800bbde8 ====

/* WARNING: Removing unreachable block (ram,0x800bbecc) */
/* WARNING: Removing unreachable block (ram,0x800bbdf8) */

void FUN_800bbde8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043852c;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043852c;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bc428(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  else {
    FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
    zz_00679d0_(param_1);
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800bbee8  FUN_800bbee8 ====

void FUN_800bbee8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  fVar1 = FLOAT_8043852c;
  if (((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) && (*(char *)(param_9 + 0x5db) != '\a')) {
    *(float *)(param_9 + 0x4c) = FLOAT_8043852c;
    *(float *)(param_9 + 0x44) = fVar1;
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_8043852c) {
    if (((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) && ('\0' < *(char *)(param_9 + 0x6eb))) {
      param_11 = 1;
      param_12 = 0;
      iVar2 = zz_006dbe0_(param_9,0,1,0);
      if (iVar2 != 0) {
        FUN_800bc2d8(param_9);
        return;
      }
      goto LAB_800bbfbc;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(char *)(param_9 + 0x5db) == '\a') {
      param_11 = 0;
      dVar3 = (double)zz_006d0dc_(param_9,0x81,0);
    }
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800bbfbc:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800bbff0  FUN_800bbff0 ====

void FUN_800bbff0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80438538;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6eb) = 3;
  if (*(short *)(param_1 + 1000) == 0x20e) {
    *(float *)(param_1 + 0x558) = FLOAT_8043853c;
    *(undefined1 *)(param_1 + 0x6eb) = 4;
  }
  (*(code *)(&PTR_FUN_8030192c)[*(char *)(param_1 + 0x581)])(param_1,0);
  return;
}



// ==== 800bc070  FUN_800bc070 ====

void FUN_800bc070(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc0e0  FUN_800bc0e0 ====

void FUN_800bc0e0(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 3;
  if (*(char *)(param_1 + 0x5db) == '\x02') {
    iVar1 = 0;
  }
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc168  FUN_800bc168 ====

void FUN_800bc168(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc1dc  FUN_800bc1dc ====

void FUN_800bc1dc(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,param_2 + 9,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc250  FUN_800bc250 ====

void FUN_800bc250(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (*(char *)(param_1 + 0x5db) != '\x0f') {
    iVar1 = 0xc;
  }
  zz_004beb8_((double)FLOAT_80438540,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    zz_004beb8_((double)FLOAT_80438540,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc2d8  FUN_800bc2d8 ====

void FUN_800bc2d8(int param_1)

{
  float fVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 uVar4;
  
  uVar2 = *(uint *)(param_1 + 0x5e0);
  if ((uVar2 & 0x100) == 0) {
    if ((uVar2 & 0x80) == 0) {
      if ((uVar2 & 0x20) == 0) {
        if ((uVar2 & 0x40) == 0) {
          if (*(char *)(param_1 + 0x5e4) == '\x04') {
            uVar4 = 3;
          }
          else if ((uVar2 & 0x10) == 0) {
            uVar4 = 0;
          }
          else {
            uVar4 = 1;
          }
        }
        else {
          uVar4 = 3;
        }
      }
      else if (*(char *)(param_1 + 0x7cc) == '\0') {
        if ((uVar2 & 0x40) == 0) {
          uVar4 = 0;
        }
        else {
          uVar4 = 3;
        }
      }
      else {
        uVar4 = 2;
      }
    }
    else {
      uVar4 = 4;
    }
  }
  else {
    uVar4 = 5;
  }
  uVar3 = zz_006c674_(param_1);
  zz_006a3d0_(param_1,'\0',uVar4,(char)uVar3);
  if ((*(uint *)(param_1 + 0x5e0) & 2) != 0) {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  }
  *(undefined1 *)(param_1 + 0x540) = 1;
  fVar1 = FLOAT_80438538;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar1;
  if (*(short *)(param_1 + 1000) == 0x20e) {
    *(float *)(param_1 + 0x558) = FLOAT_8043853c;
  }
  (*(code *)(&PTR_FUN_80301954)[*(char *)(param_1 + 0x581)])(param_1,1);
  return;
}



// ==== 800bc428  FUN_800bc428 ====

/* WARNING: Removing unreachable block (ram,0x800bc5b0) */
/* WARNING: Removing unreachable block (ram,0x800bc438) */

void FUN_800bc428(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  *(undefined2 *)(param_1 + 0x1918) = 0;
  zz_0046698_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    local_2c = *(float *)(param_1 + 0xae4);
    dVar3 = (double)*(float *)(param_1 + 0xaf4);
    local_24 = *(undefined4 *)(param_1 + 0xb04);
    local_28 = FLOAT_8043852c;
    dVar4 = gnt4_PSVECMag_bl(&local_2c);
    iVar1 = FUN_800452a0(dVar3,dVar4);
    local_2c = *(float *)(param_1 + 0xaf0);
    local_28 = *(float *)(param_1 + 0xb00);
    local_24 = *(undefined4 *)(param_1 + 0xb10);
    local_38 = *(float *)(param_1 + 0x518);
    local_34 = *(float *)(param_1 + 0x51c);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_38);
    dVar4 = (double)local_34;
    local_34 = FLOAT_8043852c;
    dVar3 = gnt4_PSVECMag_bl(&local_38);
    iVar2 = FUN_800452a0(dVar4,dVar3);
    *(short *)(param_1 + 0x1918) = (short)iVar1 + (short)iVar2;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19c2) * 0x30 + 0x8d4),
                (float *)(param_1 + 0xae4),(short *)(param_1 + 0x1916),
                (undefined4 *)(param_1 + 0x1358),(float *)(param_1 + 0xf84),
                (float *)(param_1 + 0x1658));
  }
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x6eb) = *(char *)(param_1 + 0x6eb) + -1;
    if (*(short *)(param_1 + 1000) == 0x208) {
      zz_00c3be0_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x20e) {
      FUN_80128df8(param_1,*(char *)(param_1 + 0x144) + '\x04',2,0x3c);
      *(char *)(param_1 + 0x144) = *(char *)(param_1 + 0x144) + '\x01';
      *(byte *)(param_1 + 0x144) = *(byte *)(param_1 + 0x144) & 3;
    }
  }
  return;
}



// ==== 800bc5d0  FUN_800bc5d0 ====

void FUN_800bc5d0(int param_1)

{
  (*(code *)(&PTR_FUN_8030197c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800bc60c  FUN_800bc60c ====

void FUN_800bc60c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80301994)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bc65c  FUN_800bc65c ====

void FUN_800bc65c(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_80438544;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 10;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,9,0xffffffff,0xffffffff);
  return;
}



// ==== 800bc72c  FUN_800bc72c ====

void FUN_800bc72c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80438538;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_8043852c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438538;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800bc81c  FUN_800bc81c ====

void FUN_800bc81c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80438548,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043853c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 800bc8ac  FUN_800bc8ac ====

void FUN_800bc8ac(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  bVar3 = fVar1 < FLOAT_8043852c;
  *(float *)(param_1 + 0x558) = fVar1;
  if (bVar3) {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_004beb8_(dVar4,param_1,0xf,3,10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bc930  FUN_800bc930 ====

void FUN_800bc930(int param_1)

{
  short sVar2;
  uint uVar1;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043854c,param_1);
  if (*(float *)(param_1 + 0x764) < FLOAT_80438548) {
    zz_006ed8c_((double)FLOAT_8043854c,param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ((*(char *)(param_1 + 0x1cef) != '\0') && ('\0' < *(char *)(param_1 + 0x746))) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    sVar2 = *(short *)(param_1 + 0x54a) + -1;
    *(short *)(param_1 + 0x54a) = sVar2;
    if (0 < sVar2) {
      if (*(int *)(param_1 + 0xcc) == 0) {
        *(float *)(param_1 + 0x44) = FLOAT_80438558;
      }
      else {
        *(float *)(param_1 + 0x44) = (float)(DOUBLE_80438550 * (double)*(float *)(param_1 + 0x764));
      }
      uVar1 = zz_00055fc_();
      iVar3 = (uVar1 & 1) * 2;
      zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,
                  (int)*(char *)(*(char *)(param_1 + 0x542) * 4 + -0x7fcfe654 + iVar3),0xffffffff,
                  0xffffffff);
      *(undefined1 *)(param_1 + 0x542) =
           *(undefined1 *)(*(char *)(param_1 + 0x542) * 4 + iVar3 + -0x7fcfe653);
      uVar1 = zz_00055fc_();
      *(short *)(param_1 + 0x18e2) = (short)(char)(&DAT_80433af0)[uVar1 & 3];
      zz_00b2190_(param_1,0);
      return;
    }
    zz_006a3d0_(param_1,'\x01',1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x18e2) = 0;
    zz_004beb8_(dVar4,param_1,0xf,3,0xe,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bcb08  FUN_800bcb08 ====

void FUN_800bcb08(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800bcb60  FUN_800bcb60 ====

void FUN_800bcb60(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803019b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bcbb0  FUN_800bcbb0 ====

void FUN_800bcbb0(int param_1)

{
  float fVar1;
  uint uVar2;
  float local_18;
  float local_14;
  float local_10;
  
  fVar1 = FLOAT_80438538;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    local_18 = FLOAT_8043852c;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    local_10 = FLOAT_80438560;
    local_14 = FLOAT_8043855c;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),&local_18,(float *)(param_1 + 0x38));
  }
  else {
    local_18 = *(float *)(param_1 + 0x518);
    local_10 = *(float *)(param_1 + 0x520);
    local_14 = FLOAT_8043855c * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    *(float *)(param_1 + 0x38) = local_18;
    *(float *)(param_1 + 0x3c) = local_14;
    *(float *)(param_1 + 0x40) = local_10;
  }
  zz_006d144_(param_1,0xc0);
  zz_0092dcc_(param_1,0);
  zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,5,0xffffffff,0xffffffff);
  return;
}



// ==== 800bcce8  FUN_800bcce8 ====

void FUN_800bcce8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_0046588_((double)(FLOAT_80438564 * *(float *)(param_1 + 0x1dc8)),(float *)(param_1 + 0x38),
              (float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  uVar3 = FUN_80066838((double)FLOAT_80438568,param_1);
  fVar2 = FLOAT_8043852c;
  if (((int)uVar3 < 1) &&
     (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 800bcd88  FUN_800bcd88 ====

void FUN_800bcd88(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043856c;
  fVar1 = FLOAT_8043852c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80438570;
    *(float *)(param_1 + 0x44) = fVar1;
    dVar4 = (double)FLOAT_80438540;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    zz_004beb8_(dVar4,param_1,0xf,3,6,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bce18  FUN_800bce18 ====

void FUN_800bce18(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    dVar2 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,7,0xffffffff,0xffffffff);
    zz_00b2190_(param_1,2);
  }
  return;
}



// ==== 800bcea0  FUN_800bcea0 ====

void FUN_800bcea0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_80438574;
  fVar2 = FLOAT_80438540;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_80438538;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    zz_004beb8_(dVar4,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800bcf48  FUN_800bcf48 ====

void FUN_800bcf48(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_8043852c) {
    *(float *)(param_1 + 0x44) = FLOAT_8043852c;
  }
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
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
    *(float *)(param_1 + 0x694) = FLOAT_80438534 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800bd008  FUN_800bd008 ====

void FUN_800bd008(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 800bd02c  FUN_800bd02c ====

void FUN_800bd02c(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}



// ==== 800bd050  FUN_800bd050 ====

void FUN_800bd050(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 800bd074  FUN_800bd074 ====

void FUN_800bd074(int param_1)

{
  (*(code *)(&PTR_FUN_803019d0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800bd0b0  FUN_800bd0b0 ====

void FUN_800bd0b0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803019e4)[*(char *)(param_1 + 0x540)])(param_1);
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(undefined2 *)(param_1 + 0x18fe) = 0xfe80;
    *(undefined2 *)(param_1 + 0x1900) = 0x100;
  }
  return;
}



// ==== 800bd12c  FUN_800bd12c ====

void FUN_800bd12c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar1 = FLOAT_80438574;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0x1e;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  fVar2 = FLOAT_80438578;
  fVar1 = FLOAT_8043852c;
  *(float *)(param_1 + 0x4c) = FLOAT_8043852c;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar3 = (double)FLOAT_80438540;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  zz_004beb8_(dVar3,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043852c;
  return;
}



// ==== 800bd220  FUN_800bd220 ====

void FUN_800bd220(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    *(undefined1 *)(param_1 + 0x6ea) = 1;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      *(undefined1 *)(param_1 + 0x6ea) = 3;
    }
    zz_004beb8_((double)FLOAT_80438540,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                0xffffffff);
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    fVar1 = FLOAT_8043852c;
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(undefined1 *)(param_1 + 0x6e8) = 0;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
      *(float *)(param_1 + 0x694) = FLOAT_8043857c + *(float *)(param_1 + 0x1dc8);
      return;
    }
    zz_00e19a8_(param_1,0,param_1 + 0x6f7);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800bd3a8  FUN_800bd3a8 ====

void FUN_800bd3a8(int param_1)

{
  double dVar1;
  float fVar2;
  uint uVar3;
  
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_80438520;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar1);
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\x01') {
    zz_004cd24_(param_1,0xf);
  }
  else if (*(float *)(param_1 + 0x560) <= FLOAT_8043852c) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438520) * FLOAT_80438518);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(char *)(param_1 + 0x542) == '\0') {
    *(undefined1 *)(param_1 + 0x6f7) = 2;
  }
  fVar2 = FLOAT_8043852c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800bd5a4  FUN_800bd5a4 ====

void FUN_800bd5a4(int param_1)

{
  zz_00bd5c4_(param_1);
  return;
}



// ==== 800bd5c4  zz_00bd5c4_ ====

void zz_00bd5c4_(int param_1)

{
  (*(code *)(&PTR_FUN_803019f0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800bd600  FUN_800bd600 ====

void FUN_800bd600(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043852c;
  *(float *)(param_1 + 0x50) = FLOAT_8043852c;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0xf;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 0x10;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438540;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800bd708  FUN_800bd708 ====

uint FUN_800bd708(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  uVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    uVar1 = 0;
    if (iVar2 != 0) {
      zz_00f036c_(param_1,0xeb);
      iVar2 = 0;
      do {
        bVar3 = zz_00e058c_(param_1,1,(char)iVar2 + '\x04');
        uVar1 = (uint)bVar3;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 6);
    }
  }
  return uVar1;
}



// ==== 800bd7e4  FUN_800bd7e4 ====

void FUN_800bd7e4(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x54a));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438520) * FLOAT_80438518);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  fVar1 = FLOAT_8043852c;
  if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_1 + 0x1cee) == '\0')) {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  *(float *)(param_1 + 0x694) = FLOAT_80438580 + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 800bd918  zz_00bd918_ ====

void zz_00bd918_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (*(short *)(param_1 + 1000) == 0x800) {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = param_2;
      puVar1[0x83] = 0x18;
      *(code **)(puVar1 + 0xc) = FUN_800bda24;
      *(code **)(puVar1 + 0x10c) = FUN_800bdd1c;
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
    puVar1[0x144] = 3;
  }
  return;
}



// ==== 800bda24  FUN_800bda24 ====

void FUN_800bda24(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80301a00)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800bda78  FUN_800bda78 ====

void FUN_800bda78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  undefined8 uVar5;
  
  fVar1 = FLOAT_80438588;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined *)(param_9 + 0x89) = (&DAT_80433af8)[*(char *)(param_9 + 0x13)];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80433afc + *(char *)(param_9 + 0x13) * 4),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_80433afc + *(char *)(param_9 + 0x13) * 4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043858c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00bdb80_(param_9);
  return;
}



// ==== 800bdb80  zz_00bdb80_ ====

void zz_00bdb80_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x90) + 0x6e8);
  if (cVar1 == '\x01') {
    if (*(char *)(param_1 + 0x144) != '\x01') {
      *(undefined1 *)(param_1 + 0x144) = 1;
      *(undefined1 *)(param_1 + 0x84) = 200;
      if (*(char *)(param_1 + 0x13) == '\0') {
        *(undefined2 *)(param_1 + 0x146) = 0x1000;
      }
      else {
        *(undefined2 *)(param_1 + 0x146) = 0xf000;
      }
    }
  }
  else if (cVar1 == '\0') {
    if (*(char *)(param_1 + 0x144) == '\x01') {
      *(undefined1 *)(param_1 + 0x144) = 2;
      *(undefined1 *)(param_1 + 0x84) = 200;
      if (*(char *)(param_1 + 0x13) == '\0') {
        *(undefined2 *)(param_1 + 0x146) = 0xfb00;
      }
      else {
        *(undefined2 *)(param_1 + 0x146) = 0x500;
      }
    }
    else if (*(char *)(param_1 + 0x144) == '\x03') {
      *(undefined1 *)(param_1 + 0x84) = 0xc0;
    }
  }
  if (*(char *)(param_1 + 0x144) != '\x01') {
    if (*(char *)(param_1 + 0x144) != '\x02') {
      return;
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x146);
    if (*(char *)(param_1 + 0x13) == '\0') {
      if (-1 < *(short *)(param_1 + 0x74)) {
        return;
      }
      *(undefined2 *)(param_1 + 0x74) = 0;
      *(undefined1 *)(param_1 + 0x144) = 3;
      return;
    }
    if (*(short *)(param_1 + 0x74) < 1) {
      return;
    }
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x144) = 3;
    return;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x146);
  if (*(char *)(param_1 + 0x13) != '\0') {
    if (-0x4001 < *(short *)(param_1 + 0x74)) {
      return;
    }
    *(undefined2 *)(param_1 + 0x74) = 0xc000;
    return;
  }
  if (*(short *)(param_1 + 0x74) < 0x4001) {
    return;
  }
  *(undefined2 *)(param_1 + 0x74) = 0x4000;
  return;
}



// ==== 800bdcfc  FUN_800bdcfc ====

void FUN_800bdcfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800bdd1c  FUN_800bdd1c ====

void FUN_800bdd1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = 0;
    uVar2 = 1;
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 800bdd9c  zz_00bdd9c_ ====

uint zz_00bdd9c_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_008893c_(3,8,1,5);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x49;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    *(code **)(puVar1 + 0xc) = FUN_800bdec4;
    *(code **)(puVar1 + 0x10c) = FUN_800be23c;
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
  return (-(int)puVar1 | (uint)puVar1) >> 0x1f;
}



// ==== 800bdec4  FUN_800bdec4 ====

void FUN_800bdec4(int param_1)

{
  (*(code *)(&PTR_FUN_80301a98)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800bdf00  FUN_800bdf00 ====

void FUN_800bdf00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  iVar2 = -((int)(char)(&DAT_80301a11)[iVar5] >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ae10_(param_9,(&DAT_80301a11)[iVar5]);
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar2 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    piVar3 = zz_0006dc8_(0xa0);
    *(int **)(param_9 + 0xdc) = piVar3;
    *(undefined1 *)(param_9 + 0x13) = 0x10;
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0xb4);
    *(float *)(param_9 + 0x148) = *(float *)(&DAT_80301a14 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x14c) = *(float *)(&DAT_80301a18 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x150) = *(float *)(&DAT_80301a1c + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x154) = *(float *)(&DAT_80301a20 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x158) = *(float *)(&DAT_80301a24 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x15c) = *(float *)(&DAT_80301a28 + iVar5) * *(float *)(param_9 + 0x144);
    *(int *)(param_9 + 0x160) = (int)*(short *)(&DAT_80301a12 + iVar5);
    uVar4 = zz_00055fc_();
    *(short *)(param_9 + 0x72) = (short)(uVar4 << 8);
    uVar1 = *(undefined4 *)(param_9 + 0x148);
    uVar6 = 1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0xb4) = uVar1;
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(code **)(param_9 + 0x100) = FUN_800be314;
    uVar7 = zz_0089100_(param_9,1,1);
    zz_00be36c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar6,
                param_12,param_13,param_14,param_15,param_16);
    uVar7 = zz_0040d64_((int)*(char *)(iVar2 + 0x3e4),1);
    zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xf0),(uint)(byte)(&DAT_80301a10)[iVar5],param_12,param_13,
                param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f0468_(0,0xfd,(int)*(char *)(param_9 + 0x96));
  }
  return;
}



// ==== 800be0a4  FUN_800be0a4 ====

void FUN_800be0a4(int param_1)

{
  undefined4 uVar1;
  
  (*(code *)(&PTR_LAB_80433b08)[*(char *)(param_1 + 0x19)])();
  uVar1 = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  *(undefined4 *)(param_1 + 0xc0) = uVar1;
  zz_00be484_(param_1);
  return;
}



// ==== 800be184  FUN_800be184 ====

void FUN_800be184(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 0;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x13) = 0;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800be1cc  FUN_800be1cc ====

void FUN_800be1cc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}



// ==== 800be1f4  FUN_800be1f4 ====

void FUN_800be1f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800be23c  FUN_800be23c ====

void FUN_800be23c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
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
  float afStack_48 [13];
  
  if ((*(byte *)(param_9 + 0x13) & 0x10) != 0) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xf0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xf0),0x44);
  }
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar3 = 0;
    iVar5 = 0;
    iVar4 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar3) != 0) {
        iVar1 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        dVar7 = (double)*(float *)(param_9 + 0x24);
        dVar8 = (double)*(float *)(param_9 + 0x28);
        gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),dVar7,dVar8,afStack_48);
        pfVar2 = (float *)(iVar1 + iVar5 + 0x10);
        uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0xe0)
                    ,afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
      iVar5 = iVar5 + 0x28;
    } while (iVar3 < 4);
  }
  return;
}



// ==== 800be314  FUN_800be314 ====

void FUN_800be314(int param_1)

{
  if ((*(byte *)(param_1 + 0x13) & 0x10) != 0) {
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                       (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
    zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  }
  return;
}



// ==== 800be36c  zz_00be36c_ ====

void zz_00be36c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined8 uVar4;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar3 = 0;
    while( true ) {
      if (3 < iVar3) break;
      if (((int)(char)*(byte *)(param_9 + 0x13) & 1 << iVar3) == 0) {
        iVar1 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) | (byte)(1 << iVar3);
        piVar2 = (int *)(iVar1 + iVar3 * 0x28);
        *(undefined2 *)(piVar2 + 9) = 0;
        *(undefined2 *)((int)piVar2 + 0x26) = *(undefined2 *)(&DAT_80301a8e + param_10 * 0xc);
        piVar2[8] = param_10;
        zz_0018f88_(piVar2,(int)(&PTR_DAT_80301a90)[param_10 * 3],(float *)(piVar2 + 4));
        gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x144),(float *)(piVar2 + 4),
                            (float *)(piVar2 + 4));
        if (piVar2[8] != 0) {
          iVar1 = *(int *)(param_9 + 0x148);
          piVar2[6] = iVar1;
          piVar2[4] = iVar1;
        }
        uVar4 = zz_0019338_(piVar2 + 2,(int)(&PTR_DAT_80301a94)[param_10 * 3],(float *)(piVar2 + 7))
        ;
        iVar3 = iVar3 * 4 + 0xe0;
        zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + iVar3),(int)*(short *)(&DAT_80301a8c + param_10 * 0xc),
                    param_12,param_13,param_14,param_15,param_16);
        zz_0007cac_((double)(float)piVar2[7],*(int *)(param_9 + iVar3));
        iVar3 = 4;
      }
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 800be484  zz_00be484_ ====

uint zz_00be484_(int param_1)

{
  int iVar1;
  short sVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  
  uVar7 = 0;
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar8 = 0;
    iVar6 = 0;
    iVar5 = param_1;
    do {
      uVar4 = 1 << iVar8;
      if (((int)*(char *)(param_1 + 0x13) & uVar4) != 0) {
        piVar3 = (int *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar6);
        sVar2 = *(short *)(piVar3 + 9);
        *(short *)(piVar3 + 9) = sVar2 + 1;
        if (*(short *)((int)piVar3 + 0x26) <= (short)(sVar2 + 1)) {
          *(byte *)(param_1 + 0x13) = *(byte *)(param_1 + 0x13) & ~(byte)uVar4;
        }
        zz_0018fd8_(piVar3,(int)*(short *)(piVar3 + 9),(float *)(piVar3 + 4));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x144),(float *)(piVar3 + 4),
                            (float *)(piVar3 + 4));
        if (piVar3[8] != 0) {
          iVar1 = *(int *)(param_1 + 0x148);
          piVar3[6] = iVar1;
          piVar3[4] = iVar1;
        }
        zz_0019370_(piVar3 + 2,(int)*(short *)(piVar3 + 9),(float *)(piVar3 + 7));
        zz_0007cac_((double)(float)piVar3[7],*(int *)(iVar5 + 0xe0));
      }
      iVar8 = iVar8 + 1;
      uVar7 = uVar7 | uVar4;
      iVar6 = iVar6 + 0x28;
      iVar5 = iVar5 + 4;
    } while (iVar8 < 4);
  }
  return (int)*(char *)(param_1 + 0x13) & uVar7;
}



// ==== 800be58c  FUN_800be58c ====

void FUN_800be58c(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x208) || (*(short *)(param_1 + 1000) == 0x20e)) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800be69c;
    *(code **)(puVar1 + 0x10c) = FUN_800be8ec;
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



// ==== 800be69c  FUN_800be69c ====

void FUN_800be69c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80301ad8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800be6f0  FUN_800be6f0 ====

void FUN_800be6f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  uVar6 = (uint)*(byte *)(param_9 + 0x11);
  iVar7 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar3 = (char)*(byte *)(param_9 + 0x11) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80438590;
  *(undefined1 *)(param_9 + 0x84) = 0x49;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80301aaa + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80301ab8 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80301ab4 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80301abc + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80301aae + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80301ab2 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar7 = zz_0006f98_(iVar7);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80301aa8 + iVar3),iVar7 + 0xc28,uVar6,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar7 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_80301aa8 + iVar3);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,uVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438594,*(int *)(param_9 + 0xe4));
  iVar7 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80301aac + iVar3));
  if (iVar7 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
    *(undefined2 *)(param_9 + 0x1c6) = 10000;
    *(undefined2 *)(param_9 + 0x1c8) = 10000;
    *(undefined2 *)(param_9 + 0x1c4) = 10000;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 2;
    zz_00be860_(param_9);
  }
  return;
}



// ==== 800be860  zz_00be860_ ====

void zz_00be860_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0) ||
     ((*(uint *)(iVar1 + 0x5e0) & 0x10000000) != 0)) {
    *(undefined2 *)(param_1 + 0x272) = *(undefined2 *)(iVar1 + 0x272);
  }
  else {
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
  }
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar1 + 0xc0);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  return;
}



// ==== 800be8a0  FUN_800be8a0 ====

void FUN_800be8a0(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 800be8cc  FUN_800be8cc ====

void FUN_800be8cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800be8ec  FUN_800be8ec ====

void FUN_800be8ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}



// ==== 800be948  zz_00be948_ ====

void zz_00be948_(int param_1,undefined1 param_2)

{
  char cVar1;
  short sVar2;
  undefined1 *puVar3;
  int iVar4;
  
  sVar2 = *(short *)(param_1 + 1000);
  if (((((sVar2 == 0x500) || (sVar2 == 0x509)) || (sVar2 == 0x50a)) ||
      (((sVar2 == 0x50c || (sVar2 == 0x515)) || (sVar2 == 0x516)))) &&
     (puVar3 = zz_0088aa0_(param_1,3,8,0,6), puVar3 != (undefined1 *)0x0)) {
    *puVar3 = 1;
    puVar3[0x83] = 0x10;
    puVar3[0x10] = 0x2f;
    puVar3[0x11] = param_2;
    *(code **)(puVar3 + 0xc) = FUN_800bec20;
    *(code **)(puVar3 + 0x10c) = FUN_800bf26c;
    *(int *)(puVar3 + 0x8c) = param_1;
    *(undefined4 *)(puVar3 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar3 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar3[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar3[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar3[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar3 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar3 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar3 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar3 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar3 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar3[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    iVar4 = (uint)(byte)puVar3[0x11] * 0x30;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcfe514),(float *)(puVar3 + 0x20));
    if (*(char *)(param_1 + 0x587) == '\x02') {
      cVar1 = (&DAT_80301b14)[iVar4];
      if (cVar1 == '\x01') {
        *(undefined4 *)(puVar3 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d8);
        *(undefined4 *)(puVar3 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8e8);
        *(undefined4 *)(puVar3 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8f8);
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined4 *)(puVar3 + 0x38) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8d4);
          *(undefined4 *)(puVar3 + 0x3c) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8e4);
          *(undefined4 *)(puVar3 + 0x40) =
               *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8f4);
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined4 *)(puVar3 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8dc);
        *(undefined4 *)(puVar3 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8ec);
        *(undefined4 *)(puVar3 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_80301aea)[iVar4] * 0x30 + 0x8fc);
      }
      if ((&DAT_80301b15)[iVar4] == '\x01') {
        gnt4_PSQUATScale_bl((double)FLOAT_80438598,(float *)(puVar3 + 0x38),(float *)(puVar3 + 0x38)
                           );
      }
    }
    else {
      zz_0083d60_((int)puVar3,param_1,0);
    }
    gnt4_PSVECNormalize_bl((float *)(puVar3 + 0x38),(float *)(puVar3 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80301af8 + iVar4),(float *)(puVar3 + 0x38),
                        (float *)(puVar3 + 0x38));
  }
  return;
}



// ==== 800bec20  FUN_800bec20 ====

void FUN_800bec20(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80301c08)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800becb8  FUN_800becb8 ====

void FUN_800becb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  
  puVar5 = &DAT_80301ae8;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar7 = iVar6;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar1 = FLOAT_8043859c;
  *(undefined1 *)(param_9 + 0x98) = 3;
  fVar2 = FLOAT_804385a0;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa4) = fVar2;
  uVar9 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_80301aeb)[iVar6]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar4 = zz_0006f78_(param_9);
    iVar8 = 0;
    iVar3 = param_9;
    do {
      uVar9 = zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                          *(int *)(iVar3 + 0xe0),(uint)(byte)(&DAT_80301ae8)[iVar6],puVar5,iVar7,
                          in_r8,in_r9,in_r10);
      iVar8 = iVar8 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar8 < 5);
    zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xf4),(uint)(byte)(&DAT_80301ae9)[iVar6],puVar5,iVar7,in_r8,in_r9
                ,in_r10);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80301af8 + iVar6),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    fVar1 = FLOAT_8043859c;
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80301af8 + iVar6);
    dVar10 = (double)FLOAT_804385a4;
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_80301afc + iVar6);
    *(undefined2 *)(param_9 + 0x72) = 0;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined1 *)(param_9 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x145) = 0;
    *(float *)(param_9 + 0x148) = fVar1;
    zz_00f061c_(dVar10,param_9,199);
    FUN_800bee1c(param_9);
  }
  return;
}



// ==== 800bee1c  FUN_800bee1c ====

/* WARNING: Removing unreachable block (ram,0x800bf128) */
/* WARNING: Removing unreachable block (ram,0x800bf120) */
/* WARNING: Removing unreachable block (ram,0x800bee34) */
/* WARNING: Removing unreachable block (ram,0x800bee2c) */

uint FUN_800bee1c(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
  iVar4 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0xccc;
  if (*(char *)(param_1 + 0x145) != '\0') {
    dVar10 = (double)FLOAT_804385a0;
    dVar11 = (double)FLOAT_804385a8;
    iVar8 = *(char *)(param_1 + 0x144) + 4;
    iVar9 = iVar8 / 5 + (iVar8 >> 0x1f);
    iVar8 = iVar8 + (iVar9 - (iVar9 >> 0x1f)) * -5;
    for (iVar9 = 0; iVar9 < *(char *)(param_1 + 0x145); iVar9 = iVar9 + 1) {
      iVar5 = param_1 + iVar8 * 0x14;
      fVar1 = (float)((double)*(float *)(iVar5 + 0x158) + dVar10);
      *(float *)(iVar5 + 0x158) = fVar1;
      if ((double)fVar1 <= dVar11) {
        FUN_800bf144((float *)(iVar5 + 0x14c));
      }
      else {
        *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + -1;
      }
      iVar8 = iVar8 + 4;
      iVar5 = iVar8 / 5 + (iVar8 >> 0x1f);
      iVar8 = iVar8 + (iVar5 - (iVar5 >> 0x1f)) * -5;
    }
  }
  fVar3 = FLOAT_8043859c;
  fVar1 = *(float *)(param_1 + 0x148) - FLOAT_804385a0;
  *(float *)(param_1 + 0x148) = fVar1;
  if ((fVar1 <= fVar3) && (*(char *)(param_1 + 0x145) < '\x05')) {
    *(float *)(param_1 + 0x148) = FLOAT_804385ac;
    cVar2 = *(char *)(param_1 + 0x144);
    iVar9 = param_1 + cVar2 * 0x14;
    *(float *)(iVar9 + 0x158) = fVar3;
    uVar6 = zz_00055fc_();
    *(short *)(iVar9 + 0x15c) = (short)(uVar6 << 0xb);
    *(undefined1 *)(iVar9 + 0x15e) = 0;
    FUN_800bf144((float *)(iVar9 + 0x14c));
    iVar8 = cVar2 + 1;
    iVar9 = iVar8 / 5 + (iVar8 >> 0x1f);
    *(char *)(param_1 + 0x144) = (char)iVar8 + ((char)iVar9 - (char)(iVar9 >> 0x1f)) * -5;
    *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + '\x01';
  }
  if ((0 < *(short *)(param_1 + 0x1c)) &&
     (iVar9 = zz_0083244_((float *)(param_1 + 0x20)), iVar9 == 0)) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_80083874((double)*(float *)(&DAT_80301b04 + iVar4),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_80301b00 + iVar4),param_1,
                   (char)*(undefined4 *)(&DAT_80301afc + iVar4));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar9 = zz_0083714_(param_1);
      if (iVar9 == 0) {
        iVar9 = zz_0084170_(param_1);
        if (iVar9 == 0) {
          return 0;
        }
        *(undefined1 *)(param_1 + 0x18) = 2;
        uVar6 = zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_80301b16)[iVar4]);
        cVar2 = (&DAT_80301b17)[iVar4];
        if (cVar2 == '\x02') {
          bVar7 = zz_0183730_(param_1,3,0xff);
          return (uint)bVar7;
        }
        if ('\x01' < cVar2) {
          return uVar6;
        }
        if (cVar2 < '\x01') {
          return uVar6;
        }
        bVar7 = zz_0183730_(param_1,2,0xff);
        return (uint)bVar7;
      }
    }
    else {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_80301b16)[iVar4]);
      cVar2 = (&DAT_80301b17)[iVar4];
      if (cVar2 == '\x02') {
        zz_0183730_(param_1,3,0xff);
      }
      else if ((cVar2 < '\x02') && ('\0' < cVar2)) {
        zz_0183730_(param_1,2,0xff);
      }
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  uVar6 = zz_008aff0_(param_1);
  return uVar6;
}



// ==== 800bf144  FUN_800bf144 ====

void FUN_800bf144(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_804385b0;
  iVar5 = *(char *)((int)param_1 + 0x12) * 0x10;
  fVar4 = *(float *)(&DAT_80301c18 + iVar5);
  fVar1 = *(float *)(&DAT_80301c1c + iVar5);
  fVar2 = *(float *)(&DAT_80301c20 + iVar5);
  fVar3 = *(float *)(&DAT_80301c24 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_804385b0 == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)((int)param_1 + 0x12) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_80301c18 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_80301c1c + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_80301c20 + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_80301c24 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_80301c18 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)((int)param_1 + 0x12) = *(char *)((int)param_1 + 0x12) + '\x01';
  return;
}



// ==== 800bf210  FUN_800bf210 ====

void FUN_800bf210(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800bf24c  FUN_800bf24c ====

void FUN_800bf24c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800bf26c  FUN_800bf26c ====

/* WARNING: Removing unreachable block (ram,0x800bf3f0) */
/* WARNING: Removing unreachable block (ram,0x800bf3e8) */
/* WARNING: Removing unreachable block (ram,0x800bf284) */
/* WARNING: Removing unreachable block (ram,0x800bf27c) */

void FUN_800bf26c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
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
  
  dVar9 = (double)FLOAT_804385b4;
  iVar1 = *(char *)(param_9 + 0x144) + 4;
  iVar5 = iVar1 / 5 + (iVar1 >> 0x1f);
  iVar1 = iVar1 + (iVar5 - (iVar5 >> 0x1f)) * -5;
  dVar8 = DOUBLE_804385b8;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x145); iVar5 = iVar5 + 1) {
    local_48 = 0x43300000;
    iVar4 = param_9 + iVar1 * 0x14;
    iVar3 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    uStack_44 = (int)*(short *)(iVar4 + 0x15c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(float)(dVar9 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_44) - dVar8)
                                       ),afStack_78,0x79);
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
  uStack_44 = (int)*(short *)(param_9 + 0x72) ^ 0x80000000;
  dVar8 = (double)FLOAT_804385b4;
  iVar5 = *(int *)(param_9 + 0xf4);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_44)
                                                             - DOUBLE_804385b8)),afStack_78,0x79);
  pfVar2 = afStack_78;
  uVar6 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar6,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_78,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar5,0x44);
  return;
}



// ==== 800bf40c  zz_00bf40c_ ====

void zz_00bf40c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x204) || (*(short *)(param_1 + 1000) == 0x20d)) {
    iVar2 = 0;
    do {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x13] = (char)iVar2;
        puVar1[0x11] = param_2;
        *(code **)(puVar1 + 0xc) = FUN_800bf530;
        *(code **)(puVar1 + 0x10c) = FUN_800bf844;
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
    } while (iVar2 < 2);
  }
  return;
}



// ==== 800bf530  FUN_800bf530 ====

void FUN_800bf530(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80301cb8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800bf584  FUN_800bf584 ====

void FUN_800bf584(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804385c0;
  psVar5 = (short *)(*(char *)(param_9 + 0x11) * 0x30 + -0x7fcfe3a8 +
                    *(char *)(param_9 + 0x13) * 0x18);
  *(char *)(param_9 + 0x89) = (char)psVar5[1];
  uVar2 = *(undefined4 *)(psVar5 + 4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(psVar5 + 2);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(psVar5 + 6);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(psVar5 + 8);
  *(short *)(param_9 + 0x74) = psVar5[10];
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x144) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),(int)*psVar5,iVar6 + 0xc28,
                      in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*psVar5;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804385c4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_800bf6bc(param_9);
  return;
}



// ==== 800bf6bc  FUN_800bf6bc ====

void FUN_800bf6bc(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if ((*(uint *)(iVar3 + 0x5e0) & 0x20000000) == 0) {
    fVar2 = (float)(DOUBLE_804385c8 *
                    (double)(float)((double)*(float *)(param_1 + 0x144) -
                                   (double)*(float *)(param_1 + 0x58)) +
                   (double)*(float *)(param_1 + 0x58));
    if (*(char *)(iVar3 + 0x144) == '\x01') {
      fVar2 = FLOAT_804385d0;
    }
    dVar5 = (double)fVar2;
    if ((((*(char *)(param_1 + 0x13) == '\0') && (*(char *)(iVar3 + 0x144) == '\x02')) &&
        (dVar4 = (double)FLOAT_804385c0, dVar4 == (double)*(float *)(param_1 + 0x144))) &&
       (dVar5 < (double)FLOAT_804385d4)) {
      *(undefined1 *)(iVar3 + 0x144) = 0;
      dVar5 = dVar4;
    }
    *(float *)(param_1 + 0x60) = (float)dVar5;
    fVar2 = FLOAT_804385c0;
    *(float *)(param_1 + 0x5c) = (float)dVar5;
    *(float *)(param_1 + 0x58) = (float)dVar5;
    if (*(float *)(param_1 + 0x58) < fVar2) {
      *(float *)(param_1 + 0x144) = FLOAT_804385d8;
    }
    if (DOUBLE_804385e0 <= (double)*(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x144) = FLOAT_804385c0;
    }
    if (*(char *)(param_1 + 0x13) == '\x01') {
      cVar1 = *(char *)(param_1 + 0x19);
      if (cVar1 == '\x01') {
        *(short *)(param_1 + 0x74) =
             (short)(int)((float)((double)CONCAT44(0x43300000,
                                                   (int)*(short *)(param_1 + 0x74) ^ 0x80000000) -
                                 DOUBLE_804385f0) - FLOAT_804385e8);
        if (*(char *)(iVar3 + 0x144) == '\0') {
          *(undefined1 *)(param_1 + 0x19) = 0;
        }
      }
      else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
              (*(undefined2 *)(param_1 + 0x74) = 0x4000, *(char *)(iVar3 + 0x144) == '\x02')) {
        *(undefined1 *)(param_1 + 0x19) = 1;
      }
    }
  }
  return;
}



// ==== 800bf824  FUN_800bf824 ====

void FUN_800bf824(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800bf844  FUN_800bf844 ====

void FUN_800bf844(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((double)FLOAT_804385d0 < (double)*(float *)(param_9 + 0x58)) {
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
    zz_00076d0_((double)*(float *)(param_9 + 0x58),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,iVar1,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 800bf8d4  FUN_800bf8d4 ====

void FUN_800bf8d4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  uVar2 = zz_008c098_();
  if ((char)PTR_DAT_80433930[1] < '\x01') {
    gnt4_memset(PTR_DAT_80433940,0,0x20);
    *(undefined2 *)(PTR_DAT_80433940 + 8) = 0x708;
    if ((char)PTR_DAT_80433930[1] < '\0') {
      *(undefined2 *)PTR_DAT_80433940 = 1;
      PTR_DAT_80433940[0x18] = 1;
      PTR_DAT_80433930[1] = 2;
    }
    else {
      *(undefined2 *)PTR_DAT_80433940 = 0;
      puVar1 = PTR_DAT_80433940;
      PTR_DAT_80433940[0x18] = 0;
      zz_00e99c8_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0e8,
                  puVar1,in_r7,in_r8,in_r9,in_r10);
      PTR_DAT_80433930[1] = 1;
    }
    gnt4_memset(PTR_DAT_80433934,0,0x18b8);
    zz_01ae8a8_();
    *(float *)(PTR_DAT_80433940 + 0x14) = FLOAT_804385f8;
    zz_008c3a0_(7);
  }
  (*(code *)(&PTR_FUN_80301cc8)[*(short *)PTR_DAT_80433940])();
  zz_0027ae8_();
  return;
}



// ==== 800bf9d8  FUN_800bf9d8 ====

void FUN_800bf9d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  undefined *puVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  float *pfVar4;
  float *in_r6;
  int in_r7;
  undefined *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  undefined8 extraout_f1;
  
  if (*(short *)(PTR_DAT_80433940 + 2) == 0) {
    iVar2 = zz_000a3c4_();
    in_r8 = PTR_DAT_80433940;
    if (iVar2 != 0) {
      return;
    }
    in_r7 = (int)*(short *)(PTR_DAT_80433940 + 2);
    in_r6 = (float *)0x0;
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    zz_002a5f4_(0,0,0,0);
    uVar5 = zz_0027c1c_();
    zz_0009e08_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_0197854_(1);
    uVar3 = 0;
    zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0);
    zz_0087718_(DAT_803c71e0);
    uVar5 = zz_007fd5c_();
    zz_007fd6c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_800c0358,0,uVar3,
                in_r6,in_r7,in_r8,in_r9,in_r10);
    zz_00059b8_();
    gnt4_memset(PTR_DAT_80433934,0,0x18b8);
    PTR_DAT_80433934[0x1d] = 0;
    PTR_DAT_80433934[0x1c] = 0x11;
    param_1 = zz_00429ec_();
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    uVar5 = zz_0044848_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
    uVar5 = zz_0044848_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x13);
    pfVar4 = (float *)0x1;
    *(undefined2 *)PTR_DAT_80433940 = 1;
    *(undefined2 *)(PTR_DAT_80433940 + 2) = 0;
    puVar1 = PTR_DAT_80433934;
    PTR_DAT_80433934[0x45] = 4;
    zz_00424cc_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,0,
                (undefined *)0x1,in_r6,in_r7,in_r8,in_r9,in_r10);
    zz_0040940_();
    zz_003d4a0_();
    *(float *)(PTR_DAT_80433940 + 0x10) = FLOAT_804385fc;
    uVar5 = zz_00088a4_((double)*(float *)(PTR_DAT_80433940 + 0x10),param_2,param_3,param_4,param_5,
                        param_6,param_7,param_8,DAT_803bb470,PTR_DAT_80433940,pfVar4,in_r6,in_r7,
                        in_r8,in_r9,in_r10);
    uVar5 = zz_007fd6c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0008924_,0,
                        pfVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
    zz_0008948_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(float *)&DAT_803c7380
                ,extraout_r4,(undefined *)pfVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
    zz_01c84a8_();
    FUN_801cd90c();
    uVar5 = zz_00ff5f0_();
    FUN_800c0390(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 (int)((ulonglong)uVar5 >> 0x20),(int)uVar5,(undefined *)pfVar4,in_r6,in_r7,in_r8,
                 in_r9,in_r10);
  }
  return;
}



// ==== 800bfb54  FUN_800bfb54 ====

/* WARNING: Removing unreachable block (ram,0x800bfd48) */
/* WARNING: Removing unreachable block (ram,0x800bfd4c) */

void FUN_800bfb54(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,undefined4 param_9,
                 undefined4 param_10,float *param_11,float *param_12,undefined4 param_13,
                 uint param_14,uint param_15,undefined4 param_16)

{
  uint *puVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  byte bVar7;
  short sVar8;
  float fVar9;
  uint uVar10;
  undefined *puVar11;
  undefined *puVar12;
  undefined4 *puVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  char unaff_r31;
  int iVar17;
  double dVar18;
  double dVar19;
  undefined8 uVar20;
  double extraout_f1;
  double dVar21;
  
  fVar9 = FLOAT_80438604;
  dVar18 = (double)FLOAT_80438604;
  dVar21 = (double)*(float *)(PTR_DAT_80433940 + 0x14);
  *(float *)(PTR_DAT_80433940 + 0x14) = (float)(dVar21 + (double)FLOAT_80438600);
  puVar11 = PTR_DAT_80433940;
  dVar19 = (double)*(float *)(PTR_DAT_80433940 + 0x14);
  if (dVar18 < dVar19) {
    *(float *)(PTR_DAT_80433940 + 0x14) = fVar9;
  }
  uVar20 = CONCAT44(puVar11,PTR_DAT_80433940);
  if (*(short *)(PTR_DAT_80433940 + 2) == 0) {
    if ((PTR_DAT_80433940[0x18] == '\0') || (*(short *)(PTR_DAT_80433940 + 4) != 0)) {
      *(float *)(PTR_DAT_80433940 + 0x10) =
           *(float *)(PTR_DAT_80433940 + 0x10) + *(float *)(PTR_DAT_80433940 + 0x14);
    }
    else {
      *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
      uVar20 = zz_0044848_(dVar19,dVar21,param_3,param_4,param_5,param_6,param_7,param_8,0);
      zz_0044848_(uVar20,dVar21,param_3,param_4,param_5,param_6,param_7,param_8,0x13);
      *(float *)(PTR_DAT_80433940 + 0x10) = FLOAT_804385fc;
      FUN_801cd90c();
      zz_00ff5f0_();
      PTR_DAT_80433940[0x18] = 0;
    }
    if (FLOAT_80438608 <= *(float *)(PTR_DAT_80433940 + 0x10)) {
      *(float *)(PTR_DAT_80433940 + 0x10) = FLOAT_80438608;
      *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
      PTR_DAT_80433940[0x1a] = 1;
    }
    uVar20 = zz_00088a4_((double)*(float *)(PTR_DAT_80433940 + 0x10),dVar21,param_3,param_4,param_5,
                         param_6,param_7,param_8,DAT_803bb470,PTR_DAT_80433940,param_11,param_12,
                         param_13,param_14,param_15,param_16);
    dVar19 = extraout_f1;
  }
  uVar20 = FUN_800c0390(dVar19,dVar21,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar20 >> 0x20),(int)uVar20,(undefined *)param_11,param_12,
                        param_13,param_14,param_15,param_16);
  if ((*(short *)(PTR_DAT_80433940 + 2) != 0) && (PTR_DAT_80433940[0x1a] != '\0')) {
    sVar8 = *(short *)(PTR_DAT_80433940 + 8);
    *(short *)(PTR_DAT_80433940 + 8) = sVar8 + -1;
    if ((short)(sVar8 + -1) < 1) {
      PTR_DAT_80433940[0x1a] = 0;
      *(undefined2 *)PTR_DAT_80433940 = 4;
      zz_0027aac_(0,0x20,1);
      zz_00e9b60_((double)FLOAT_804385f8,2,0x20,2);
    }
    else {
      uVar16 = 0;
      puVar13 = &DAT_803c727c;
      iVar17 = 1;
      do {
        puVar1 = puVar13 + 4;
        puVar2 = puVar13 + 2;
        puVar3 = puVar13 + 10;
        puVar4 = puVar13 + 0xc;
        puVar5 = puVar13 + 0x14;
        puVar6 = puVar13 + 0x12;
        uVar15 = puVar13[0x1c];
        uVar14 = puVar13[0x1a];
        puVar13 = puVar13 + 0x20;
        uVar16 = uVar16 | *puVar1 >> 0x10 & 0xf | *puVar2 >> 0x10 & 0xf | *puVar2 | *puVar1 |
                 *puVar4 >> 0x10 & 0xf | *puVar3 >> 0x10 & 0xf | *puVar3 | *puVar4 |
                 *puVar5 >> 0x10 & 0xf | *puVar6 >> 0x10 & 0xf | *puVar6 | *puVar5 |
                 uVar15 >> 0x10 & 0xf | uVar14 >> 0x10 & 0xf | uVar14 | uVar15;
        iVar17 = iVar17 + -1;
      } while (iVar17 != 0);
      zz_008bab0_(0xf,3,1);
      bVar7 = PTR_DAT_80433930[0x32];
      puVar12 = PTR_DAT_80433930;
      uVar10 = zz_008bab0_(0xf,3,1);
      uVar10 = FUN_800c0454(uVar10,(uint)bVar7);
      puVar11 = PTR_DAT_80433930;
      PTR_DAT_80433930[0x32] = (char)uVar10;
      if (bVar7 != PTR_DAT_80433930[0x32]) {
        puVar11 = (undefined *)0x0;
        uVar20 = zz_00f0468_(0,0x77,0);
        *(undefined2 *)(PTR_DAT_80433940 + 8) = 0x708;
      }
      puVar13 = (undefined4 *)PTR_DAT_80433940;
      uVar10 = 0;
      if (*(short *)(PTR_DAT_80433940 + 10) == 0) {
        unaff_r31 = '\0';
        puVar12 = (undefined *)0x0;
        uVar10 = 0;
        puVar11 = (undefined *)0x0;
        iVar17 = 4;
        puVar13 = &DAT_803c727c;
        do {
          if ((puVar13[2] & 0x1100) != 0) {
            unaff_r31 = unaff_r31 + '\x01';
            uVar10 = uVar10 | 1 << (int)puVar12;
          }
          puVar13 = puVar13 + 8;
          puVar12 = puVar12 + 1;
          iVar17 = iVar17 + -1;
        } while (iVar17 != 0);
      }
      else {
        *(short *)(PTR_DAT_80433940 + 10) = *(short *)(PTR_DAT_80433940 + 10) + -1;
      }
      if (uVar10 != 0) {
        if (PTR_DAT_80433930[0x32] == '\x05') {
          *(undefined2 *)PTR_DAT_80433940 = 2;
          *(undefined2 *)(PTR_DAT_80433940 + 2) = 0;
          *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
          zz_00f0468_(0,0x7a,0);
        }
        else {
          *(undefined2 *)PTR_DAT_80433940 = 3;
          PTR_DAT_80433930[2] = (char)uVar10;
          PTR_DAT_80433930[3] = unaff_r31;
          if (PTR_DAT_80433930[0x32] == '\x02') {
            zz_004369c_(uVar20,dVar21,param_3,param_4,param_5,param_6,param_7,param_8,0,puVar13,
                        puVar11,puVar12,uVar10,uVar14,uVar15,uVar16);
          }
          zz_0027aac_(0xe0e0e0ff,0x20,1);
          zz_00e9b60_((double)FLOAT_804385f8,2,0x20,2);
          zz_00f0468_(0,0x7c,0);
        }
        PTR_DAT_80433940[0x1a] = 0;
      }
    }
  }
  return;
}



// ==== 800bff70  FUN_800bff70 ====

void FUN_800bff70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  
  iVar2 = zz_000a3c4_();
  if ((iVar2 == 0) && (iVar2 = zz_0027adc_(), iVar2 == 0)) {
    zz_008a16c_();
    uVar3 = zz_008c098_();
    *PTR_DAT_80433930 = 3;
    puVar1 = PTR_DAT_80433930;
    PTR_DAT_80433930[1] = 0;
    uVar3 = FUN_800c0358(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,3,
                         param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_007fd5c_();
  }
  else {
    FUN_800c0390(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800bffd8  FUN_800bffd8 ====

void FUN_800bffd8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    zz_008a16c_();
    uVar3 = zz_008c098_();
    *PTR_DAT_80433930 = 1;
    puVar1 = PTR_DAT_80433930;
    PTR_DAT_80433930[1] = 0xff;
    uVar3 = FUN_800c0358(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,1,
                         param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_007fd5c_();
    PTR_DAT_80433930[0x32] = 0;
    PTR_DAT_80433930[0x32] = 0;
  }
  else {
    FUN_800c0390(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800c0048  FUN_800c0048 ====

void FUN_800c0048(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  undefined *puVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar2;
  
  puVar1 = PTR_DAT_80433940;
  uVar2 = (*(code *)(&PTR_FUN_80301cdc)[*(short *)(PTR_DAT_80433940 + 2)])(PTR_DAT_80433940 + 0x1c);
  FUN_800c0390(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               (int)((ulonglong)uVar2 >> 0x20),(int)uVar2,puVar1,in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800c008c  FUN_800c008c ====

void FUN_800c008c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,
                 float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar5;
  undefined4 auStack_28 [3];
  undefined4 auStack_1c [6];
  
  fVar2 = FLOAT_8043860c;
  puVar4 = PTR_DAT_80433940;
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    *param_9 = fVar2;
  }
  else {
    *param_9 = *param_9 + FLOAT_80438604;
  }
  if (FLOAT_80438610 <= *param_9) {
    *param_9 = FLOAT_80438610;
    iVar3 = zz_000a3c4_();
    puVar1 = PTR_DAT_80433940;
    if (iVar3 == 0) {
      *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
      *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
      *PTR_DAT_80433934 = 0;
      puVar4 = puVar1;
    }
  }
  uVar5 = zz_00088a4_((double)*param_9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      DAT_803bb470,puVar4,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0008970_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_28,
                      extraout_r4,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16
                     );
  cCameraManager__HasCamera_cBaseCamera
            (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_1c,extraout_r4_00
             ,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800c0154  FUN_800c0154 ====

void FUN_800c0154(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    zz_01b1e08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  iVar1 = zz_01b1eac_();
  if (iVar1 != 1) {
    if (iVar1 == 0) {
      zz_00e9c78_((double)FLOAT_80438614,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
    }
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
  }
  return;
}



// ==== 800c01c8  FUN_800c01c8 ====

void FUN_800c01c8(void)

{
  int iVar1;
  
  iVar1 = zz_00ff618_();
  if (iVar1 != 0) {
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
  }
  return;
}



// ==== 800c020c  FUN_800c020c ====

void FUN_800c020c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x80;
    zz_01b1f10_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  iVar1 = zz_01b1fb8_();
  if (iVar1 != 1) {
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
  }
  return;
}



// ==== 800c028c  FUN_800c028c ====

void FUN_800c028c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,
                 float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined *extraout_r4;
  undefined *puVar2;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar3;
  undefined4 auStack_28 [3];
  undefined4 auStack_1c [6];
  
  fVar1 = FLOAT_80438610;
  puVar2 = PTR_DAT_80433940;
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    *param_9 = fVar1;
  }
  else {
    *param_9 = *param_9 - FLOAT_80438604;
  }
  if (*param_9 <= FLOAT_8043860c) {
    param_11 = (float *)0x708;
    *param_9 = FLOAT_80438608;
    *(undefined2 *)(PTR_DAT_80433940 + 8) = 0x708;
    *(undefined2 *)PTR_DAT_80433940 = 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433940 + 2) = 0;
    zz_01ae8a8_();
    puVar2 = extraout_r4;
  }
  uVar3 = zz_00088a4_((double)*param_9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      DAT_803bb470,puVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar3 = zz_0008970_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_28,
                      extraout_r4_00,(undefined *)param_11,param_12,param_13,param_14,param_15,
                      param_16);
  cCameraManager__HasCamera_cBaseCamera
            (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_1c,extraout_r4_01
             ,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800c0358  FUN_800c0358 ====

void FUN_800c0358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  zz_0008b58_();
  zz_0008cf4_();
  zz_01978d0_();
  zz_0040910_();
  uVar1 = zz_0005984_(0);
  zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  return;
}



// ==== 800c0390  FUN_800c0390 ====

void FUN_800c0390(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  FUN_800c03b4(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  FUN_800c03fc();
  return;
}



// ==== 800c03b4  FUN_800c03b4 ====

void FUN_800c03b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  zz_0087cf0_();
  zz_0089898_(0x28);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  uVar1 = zz_0040b94_();
  zz_0008948_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(float *)&DAT_803c7380,
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800c03fc  FUN_800c03fc ====

void FUN_800c03fc(void)

{
  zz_008a16c_();
  zz_0089c00_(0x28);
  zz_0089c00_(0x38);
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  zz_008c12c_(FUN_80089f9c);
  return;
}



// ==== 800c0454  FUN_800c0454 ====

uint FUN_800c0454(uint param_1,uint param_2)

{
  char cVar1;
  
  cVar1 = -1;
  if ((param_1 & 8) == 0) {
    if ((param_1 & 4) == 0) {
      if ((param_1 & 1) == 0) {
        if ((param_1 & 2) != 0) {
          cVar1 = '\x03';
        }
      }
      else {
        cVar1 = '\x02';
      }
    }
    else {
      cVar1 = '\x01';
    }
  }
  else {
    cVar1 = '\0';
  }
  if (-1 < cVar1) {
    param_2 = (uint)(byte)(&DAT_80301cf0)[(int)cVar1 + (char)param_2 * 4];
  }
  return param_2;
}



// ==== 800c05bc  FUN_800c05bc ====

void FUN_800c05bc(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x144) = 2;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x30b) {
    FUN_8004e580(param_1,1);
    FUN_800fb83c(param_1,1);
    zz_00c74ec_(param_1,4);
  }
  else if ((sVar1 < 0x30b) && (sVar1 == 0x300)) {
    FUN_8004e580(param_1,0);
    FUN_800fb83c(param_1,0);
    zz_00c74ec_(param_1,4);
  }
  return;
}



// ==== 800c064c  FUN_800c064c ====

void FUN_800c064c(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}



// ==== 800c066c  FUN_800c066c ====

void FUN_800c066c(int param_1)

{
  bool bVar1;
  char cVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x300) || (*(short *)(param_1 + 1000) == 0x30b)) {
    cVar2 = *(char *)(param_1 + 0x6e8);
    if (cVar2 == '\x03') {
      bVar1 = *(char *)(param_1 + 0x144) != '\x03';
      *(undefined1 *)(param_1 + 0x144) = 3;
      cVar2 = *(char *)(param_1 + 0x6e9);
      if (cVar2 == '\x02') {
        *(undefined1 *)(param_1 + 0x145) = 2;
      }
      else if (cVar2 < '\x02') {
        if ('\0' < cVar2) {
          if (bVar1) {
            *(undefined1 *)(param_1 + 0x145) = 2;
          }
          else {
            *(undefined1 *)(param_1 + 0x145) = 1;
          }
        }
      }
      else if (cVar2 < '\x04') {
        if (bVar1) {
          *(undefined1 *)(param_1 + 0x145) = 3;
        }
        else {
          *(undefined1 *)(param_1 + 0x145) = 1;
        }
      }
    }
    else if (cVar2 < '\x03') {
      if (cVar2 == '\x01') {
        *(undefined1 *)(param_1 + 0x144) = 1;
        cVar2 = *(char *)(param_1 + 0x6e9);
        if (cVar2 == '\x02') {
          *(undefined1 *)(param_1 + 0xaf) = 0xff;
        }
        else if ((cVar2 < '\x02') && ('\0' < cVar2)) {
          *(undefined1 *)(param_1 + 0xaf) = 1;
          if (*(short *)(param_1 + 1000) == 0x300) {
            zz_001ab6c_(param_1,0x10);
          }
          else if (*(short *)(param_1 + 1000) == 0x30b) {
            zz_001ab6c_(param_1,0x4e);
          }
        }
      }
      else if ('\0' < cVar2) {
        *(undefined1 *)(param_1 + 0x144) = 2;
      }
    }
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0x6e9) = 0;
    if (*(char *)(param_1 + 0x144) == '\x01') {
      *(undefined1 *)(param_1 + 0x1d94) = 0;
    }
  }
  return;
}



// ==== 800c0800  FUN_800c0800 ====

void FUN_800c0800(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80433b10)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800c086c  FUN_800c086c ====

void FUN_800c086c(int param_1)

{
  (*(code *)(&PTR_FUN_80302988)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800c08a8  FUN_800c08a8 ====

void FUN_800c08a8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80302994)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c08f0  FUN_800c08f0 ====

void FUN_800c08f0(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 800c0914  FUN_800c0914 ====

void FUN_800c0914(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 800c0938  FUN_800c0938 ====

void FUN_800c0938(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 800c095c  FUN_800c095c ====

void FUN_800c095c(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 800c0980  FUN_800c0980 ====

void FUN_800c0980(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 800c09a4  FUN_800c09a4 ====

void FUN_800c09a4(int param_1)

{
  (*(code *)(&PTR_FUN_803029a8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c09e0  FUN_800c09e0 ====

void FUN_800c09e0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80433b18)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c0a2c  FUN_800c0a2c ====

void FUN_800c0a2c(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_006d144_(param_1,0xc0);
  if ((*(short *)(param_1 + 1000) == 0x30b) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar1 = FLOAT_80438618;
  *(float *)(param_1 + 0x50) = FLOAT_80438618;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043861c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_80438620,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),8,1);
  return;
}



