// ==== 8013088c  FUN_8013088c ====

void FUN_8013088c(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(short *)(param_1 + 1000) == 0x103) {
    zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
                0xffffffff);
    zz_004beb8_((double)FLOAT_80439e90,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,0xc,4,1);
  }
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_013138c_(param_1);
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x50) = FLOAT_80439e78;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439e78;
  return;
}



// ==== 801309b8  FUN_801309b8 ====

/* WARNING: Removing unreachable block (ram,0x80130ab4) */
/* WARNING: Removing unreachable block (ram,0x801309c8) */

void FUN_801309b8(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80439e78;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439e78;
  if ((((iVar3 != 0) ||
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
      (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01313bc_(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439e98 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80130ad0  FUN_80130ad0 ====

void FUN_80130ad0(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439e78) {
    if ('\0' < *(char *)(param_1 + 0x6ef)) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if (iVar1 != 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        iVar1 = 1;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        if (*(short *)(param_1 + 1000) != 0x103) {
          iVar1 = 0xd;
        }
        zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,iVar1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80130be4;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_80439e98) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_80130be4:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80130c5c  FUN_80130c5c ====

void FUN_80130c5c(int param_1)

{
  (*(code *)(&PTR_FUN_80335ce8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80130c98  FUN_80130c98 ====

void FUN_80130c98(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = 0xffffffff;
  uVar3 = 0xffffffff;
  iVar1 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0) {
    iVar1 = 3;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) {
    iVar1 = 0;
  }
  if (*(short *)(param_1 + 1000) != 0x103) {
    uVar2 = 4;
    uVar3 = 1;
    iVar1 = iVar1 + 0xc;
  }
  zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,iVar1 + *(char *)(param_1 + 0x6ee),uVar2,uVar3);
  zz_013138c_(param_1);
  return;
}



// ==== 80130d34  FUN_80130d34 ====

/* WARNING: Removing unreachable block (ram,0x80130e30) */
/* WARNING: Removing unreachable block (ram,0x80130d44) */

void FUN_80130d34(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006dee8_(param_1,1);
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = (float)(dVar4 * (double)FLOAT_80439e78);
  }
  zz_004cd24_(param_1,1);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  fVar2 = FLOAT_80439e78;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if ((((0 < iVar3) ||
            (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
           (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01313bc_(param_1);
  }
  return;
}



// ==== 80130e50  FUN_80130e50 ====

void FUN_80130e50(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_80439e78) {
    if ('\0' < *(char *)(param_9 + 0x6ef)) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = iVar1 + 0xc;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          iVar1 = 4;
          *(undefined1 *)(param_9 + 0x581) = 1;
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = 0x10;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          iVar1 = 1;
          *(undefined1 *)(param_9 + 0x581) = 2;
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = 0xd;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_80131004;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_80131004:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80131038  FUN_80131038 ====

void FUN_80131038(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80335cf4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80131080  FUN_80131080 ====

void FUN_80131080(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80439e9c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(short *)(param_1 + 1000) == 0x103) {
    zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
                0xffffffff);
    if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
      zz_004beb8_((double)FLOAT_80439e90,param_1,2,0,0xd,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,0x15,4,1);
  }
  zz_013138c_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439e78;
  return;
}



// ==== 80131184  FUN_80131184 ====

/* WARNING: Removing unreachable block (ram,0x80131298) */
/* WARNING: Removing unreachable block (ram,0x80131194) */

void FUN_80131184(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80439e78;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_80439e78;
  if ((((iVar3 != 0) ||
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
      (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    zz_01313bc_(param_1);
    if (*(short *)(param_1 + 1000) == 0x103) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
      zz_006a5a4_(param_1);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801312b4  FUN_801312b4 ====

void FUN_801312b4(int param_1)

{
  int iVar1;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
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
    *(float *)(param_1 + 0x694) = FLOAT_80439ea0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8013138c  zz_013138c_ ====

void zz_013138c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439e7c;
  *(float *)(param_1 + 0x560) = FLOAT_80439ea4;
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 5;
  return;
}



// ==== 801313bc  zz_01313bc_ ====

/* WARNING: Removing unreachable block (ram,0x80131578) */
/* WARNING: Removing unreachable block (ram,0x801313cc) */

uint zz_01313bc_(uint param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  double dVar7;
  double dVar8;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_80439e7c;
  *(float *)(param_1 + 0x560) = FLOAT_80439ea4;
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  uVar3 = param_1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    uVar3 = zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar7 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_80439e78;
      dVar8 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar7,dVar8);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar8 = (double)local_24;
      local_24 = FLOAT_80439e78;
      dVar7 = gnt4_PSVECMag_bl(&local_28);
      iVar5 = FUN_800452a0(dVar8,dVar7);
      *(short *)(param_1 + 0x1900) = (short)iVar4 + (short)iVar5;
      uVar3 = zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                          (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                          (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                          (float *)(param_1 + 0x1628));
    }
    if (*(short *)(param_1 + 1000) == 0x103) {
      iVar4 = zz_006dbe0_(param_1,0,1,1);
      uVar3 = 0;
      if (iVar4 != 0) {
        zz_0082824_(param_1,0x26);
        uVar3 = (uint)*(byte *)(param_1 + 0x6ef);
        *(byte *)(param_1 + 0x6ef) = *(byte *)(param_1 + 0x6ef) - 1;
      }
      if (*(short *)(param_1 + 0x774) < 1) {
        *(undefined1 *)(param_1 + 0x6ef) = 0;
      }
    }
    else if (*(short *)(param_1 + 1000) == 0x106) {
      iVar4 = zz_006dbe0_(param_1,2,1,1);
      uVar3 = 0;
      if (iVar4 != 0) {
        *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 2;
        bVar6 = zz_00fe668_(param_1,2,2);
        uVar3 = (uint)bVar6;
      }
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return uVar3;
}



// ==== 80131598  FUN_80131598 ====

void FUN_80131598(int param_1)

{
  (*(code *)(&PTR_FUN_80335d04)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801315d4  FUN_801315d4 ====

void FUN_801315d4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80131604  FUN_80131604 ====

void FUN_80131604(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80131634  FUN_80131634 ====

void FUN_80131634(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}



// ==== 80131664  FUN_80131664 ====

void FUN_80131664(int param_1)

{
  zz_01618ac_(param_1);
  return;
}



// ==== 80131688  FUN_80131688 ====

void FUN_80131688(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  double dVar2;
  double dVar3;
  
  dVar2 = DOUBLE_80439e88;
  sVar1 = *(short *)(param_9 + 0x1900);
  dVar3 = (double)(float)((double)CONCAT44(0x43300000,(int)sVar1 ^ 0x80000000) - DOUBLE_80439e88);
  *(short *)(param_9 + 0x1900) = (short)(int)(dVar3 * (double)FLOAT_80439e80);
  zz_01316e0_(dVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(int)sVar1,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801316e0  zz_01316e0_ ====

void zz_01316e0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    if (((*(uint *)(param_9 + 0x5e0) & 0x20) == 0) || (*(char *)(param_9 + 0x1cef) == '\0')) {
      *(undefined1 *)(param_9 + 0x543) = 1;
      if (*(char *)(param_9 + 0x5db) == '\x01') {
        *(undefined1 *)(param_9 + 0x543) = 0xf;
      }
      *(undefined1 *)(param_9 + 0x6ea) = 2;
      if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
        *(undefined1 *)(param_9 + 0x6ea) = 4;
      }
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
        *(undefined1 *)(param_9 + 0x6ea) = 3;
      }
      zz_004beb8_((double)FLOAT_80439e90,param_9,(int)*(char *)(param_9 + 0x543),4,
                  (int)*(char *)(param_9 + 0x6ea),0xffffffff,0xffffffff);
    }
    else {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,param_11
                  ,param_12,param_13,param_14,param_15,param_16);
      *(float *)(param_9 + 0x694) =
           *(float *)(param_9 + 0x1dc8) +
           ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1af8) ^ 0x80000000) -
                   DOUBLE_80439e88) - *(float *)(param_9 + 0x1ae0));
    }
  }
  else {
    zz_004cd24_(param_9,1);
    if (*(char *)(param_9 + 0x1cee) != '\0') {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x1e,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80131834  FUN_80131834 ====

void FUN_80131834(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  (*(code *)(&PTR_FUN_80335d18)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801318a8  FUN_801318a8 ====

void FUN_801318a8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80335d2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801318f8  FUN_801318f8 ====

void FUN_801318f8(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x50) = FLOAT_80439e78;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),8,1);
  return;
}



// ==== 80131a00  FUN_80131a00 ====

void FUN_80131a00(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if (*(short *)(param_1 + 1000) == 0x103) {
      zz_013a954_(param_1,0);
    }
    else if ((*(short *)(param_1 + 1000) == 0x106) &&
            (iVar1 = zz_006dbe0_(param_1,2,1,1), iVar1 != 0)) {
      *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 2;
      zz_00fe668_(param_1,2,2);
      zz_00f036c_(param_1,0xeb);
    }
  }
  return;
}



// ==== 80131b0c  FUN_80131b0c ====

void FUN_80131b0c(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_80439ea8 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 80131c14  zz_0131c14_ ====

void zz_0131c14_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x305) || (sVar1 == 0x309)) || (sVar1 == 0x30a)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_80131d24;
    *(code **)(puVar2 + 0x10c) = FUN_8013204c;
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



// ==== 80131d24  FUN_80131d24 ====

void FUN_80131d24(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80336550)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80131d78  FUN_80131d78 ====

void FUN_80131d78(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  
  iVar6 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar6;
  iVar7 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = *(char *)(param_9 + 0x11) * 0x18;
  zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439eb0;
  dVar10 = (double)FLOAT_80439eb0;
  *(undefined1 *)(param_9 + 0x84) = 0x57;
  fVar2 = FLOAT_80439eb4;
  *(undefined *)(param_9 + 0x89) = (&DAT_80336461)[iVar4];
  uVar3 = *(undefined4 *)(&DAT_80336468 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80336464 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033646c + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80336470 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80336474 + iVar4);
  *(char *)(param_9 + 0x12) = (char)*(undefined2 *)(&DAT_80336476 + iVar4);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  dVar8 = (double)*(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x144) = *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x148) = fVar2;
  *(float *)(param_9 + 0x14c) = fVar2;
  *(float *)(param_9 + 0x150) = fVar1;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80336460)[iVar4],iVar7 + 0xc28,iVar6,in_r8,in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  iVar4 = (int)(char)(&DAT_80336460)[iVar4];
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,iVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4,iVar4,iVar5,iVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439eb8,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0131ecc_(param_9);
  return;
}



// ==== 80131ecc  zz_0131ecc_ ====

void zz_0131ecc_(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x11);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x03') {
LAB_80131f34:
    if (-1 < *(char *)(iVar4 + 0x6e8)) {
      if (*(char *)(iVar4 + 0x6e8) == '\x01') {
        if ((*(byte *)(iVar4 + 0x6e9) & *(byte *)(param_1 + 0x12)) == 0) {
          *(float *)(param_1 + 0x14c) = FLOAT_80439eb4;
        }
        else if (*(float *)(param_1 + 0x148) < FLOAT_80439eb0) {
          *(float *)(param_1 + 0x14c) = FLOAT_80439ec0;
        }
      }
      else {
        *(float *)(param_1 + 0x14c) = FLOAT_80439eb4;
      }
    }
    dVar3 = DOUBLE_80439ed0;
    *(float *)(param_1 + 0x148) =
         (float)(DOUBLE_80439ec8 *
                 (double)(float)((double)*(float *)(param_1 + 0x14c) -
                                (double)*(float *)(param_1 + 0x148)) +
                (double)*(float *)(param_1 + 0x148));
    if ((dVar3 <= (double)*(float *)(param_1 + 0x148)) &&
       (FLOAT_80439eb0 < *(float *)(param_1 + 0x14c))) {
      *(float *)(param_1 + 0x14c) = FLOAT_80439eb0;
    }
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 == '\0') goto LAB_80131f34;
      if (cVar1 < '\0') goto LAB_80132000;
    }
    else {
      if ('\t' < cVar1) goto LAB_80132000;
      if ('\a' < cVar1) {
        if ((*(char *)(iVar4 + 0x6e8) < '\x01') || ((*(byte *)(iVar4 + 0x6e9) & 4) == 0)) {
          *(float *)(param_1 + 0x150) = FLOAT_80439eb0;
        }
        else {
          *(float *)(param_1 + 0x150) = FLOAT_80439ebc;
        }
        goto LAB_80131f34;
      }
    }
    *(float *)(param_1 + 0x148) = FLOAT_80439eb4;
    if ((*(byte *)(iVar4 + 0x144) & *(byte *)(param_1 + 0x12)) != 0) {
      *(float *)(param_1 + 0x148) = FLOAT_80439eb0;
    }
  }
LAB_80132000:
  fVar2 = *(float *)(param_1 + 0x144) * *(float *)(param_1 + 0x148);
  *(float *)(param_1 + 0x60) = fVar2;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  return;
}



// ==== 8013202c  FUN_8013202c ====

void FUN_8013202c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013204c  FUN_8013204c ====

void FUN_8013204c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if (FLOAT_80439eb4 < *(float *)(param_1 + 0x58)) {
    cVar1 = *(char *)(param_1 + 0x11);
    if ((*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') &&
       (*(char *)(*(int *)(param_1 + 0x90) + 0x3ec) != '\x04')) {
      iVar4 = *(int *)(param_1 + 0xe0);
      iVar3 = 0;
    }
    else {
      iVar4 = *(int *)(param_1 + 0xe4);
      iVar3 = 1;
    }
    dVar5 = (double)FLOAT_80439eb0;
    dVar7 = (double)*(float *)(param_1 + 0x150);
    gnt4_PSMTXScale_bl(dVar5,dVar5,dVar7,afStack_48);
    pfVar2 = afStack_48;
    uVar6 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
    zz_00076d0_(uVar6,dVar5,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,iVar4,afStack_48,(undefined *)pfVar2
                ,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(iVar4,(int)(char)(&DAT_80336462)[cVar1 * 0x18 + iVar3]);
  }
  return;
}



// ==== 8013212c  zz_013212c_ ====

undefined4 zz_013212c_(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  
  iVar2 = param_2 * 2;
  cVar1 = (&DAT_80336b20)[iVar2];
  if (*(short *)(param_1 + 1000) == *(short *)(&DAT_80336928 + (char)(&DAT_80336b21)[iVar2] * 0x28))
  {
    puVar4 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar4 == (undefined1 *)0x0) {
      uVar3 = 0;
    }
    else {
      *puVar4 = 1;
      puVar4[0x13] = (char)param_2;
      puVar4[0x11] = (&DAT_80336b20)[iVar2];
      puVar4[0x12] = (&DAT_80336b21)[iVar2];
      puVar4[0x10] = 0x24;
      *(code **)(puVar4 + 0xc) = FUN_801322dc;
      *(code **)(puVar4 + 0x10c) = FUN_80133530;
      *(int *)(puVar4 + 0x8c) = param_1;
      *(undefined4 *)(puVar4 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(puVar4 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      puVar4[0x96] = *(undefined1 *)(param_1 + 0x96);
      puVar4[0x97] = *(undefined1 *)(param_1 + 0x97);
      puVar4[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(puVar4 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(puVar4 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(puVar4 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(puVar4 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar4 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(puVar4 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      puVar4[0xd0] = *(undefined1 *)(param_1 + 0xd0);
      *(undefined4 *)(puVar4 + 0x148) = *(undefined4 *)(puVar4 + 0xcc);
      *(undefined4 *)(puVar4 + 0x144) = *(undefined4 *)(puVar4 + 200);
      puVar4[0x16b] = puVar4[0xd0];
      zz_00f036c_(param_1,7);
      uVar3 = 0x8444;
      puVar4[0x168] = (&DAT_80336563)[cVar1 * 0x24];
      *(undefined4 *)(puVar4 + 0x164) = param_3;
      **(byte **)(puVar4 + 0x164) = **(byte **)(puVar4 + 0x164) & ~puVar4[0x168];
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 801322dc  FUN_801322dc ====

void FUN_801322dc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_01330b4_(param_1);
  }
  (*(code *)(&PTR_FUN_80336b54)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8013237c  FUN_8013237c ====

void FUN_8013237c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  float local_a8;
  float local_a4;
  float local_a0;
  float afStack_9c [12];
  float fStack_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  puVar7 = &DAT_80336908;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar10 = *(int *)(param_9 + 0x90);
  iVar5 = *(char *)(param_9 + 0x11) * 0x24;
  iVar8 = (int)*(char *)(param_9 + 0x12);
  *(undefined1 *)(param_9 + 0x84) = 0x16;
  uVar3 = (uint)(byte)(&DAT_80336561)[iVar5];
  iVar4 = iVar8 * 0x28;
  *(undefined *)(param_9 + 0x89) = (&DAT_80336561)[iVar5];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar2 = iVar4;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  pfVar9 = (float *)(iVar10 + (char)(&DAT_80336561)[iVar5] * 0x30 + 0x8d4);
  gnt4_PSMTXCopy_bl(pfVar9,(float *)(param_9 + 0x114));
  gnt4_PSMTXMultVec_bl(pfVar9,(float *)(iVar5 + -0x7fcc9a9c),(float *)(param_9 + 0x20));
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(&DAT_80336580 + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80439ee8)),
                      afStack_9c,0x7a);
  gnt4_PSMTXConcat_bl(pfVar9,afStack_9c,&fStack_6c);
  local_30 = 0x43300000;
  uStack_2c = (int)*(short *)(&DAT_8033657e + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80439ee8)),
                      afStack_9c,0x79);
  gnt4_PSMTXConcat_bl(&fStack_6c,afStack_9c,&fStack_6c);
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(&DAT_8033657c + iVar5) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80439ee8)),
                      afStack_9c,0x78);
  gnt4_PSMTXConcat_bl(&fStack_6c,afStack_9c,&fStack_6c);
  dVar11 = (double)FLOAT_80439edc;
  *(undefined4 *)(param_9 + 0x9c) = local_68;
  *(undefined4 *)(param_9 + 0xa0) = local_58;
  *(undefined4 *)(param_9 + 0xa4) = local_48;
  gnt4_PSQUATScale_bl(dVar11,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
  local_a4 = FLOAT_80439ee0;
  *(undefined4 *)(param_9 + 0x38) = local_64;
  *(undefined4 *)(param_9 + 0x3c) = local_54;
  *(undefined4 *)(param_9 + 0x40) = local_44;
  local_a8 = *(float *)(param_9 + 0x38);
  local_a0 = *(float *)(param_9 + 0x40);
  dVar11 = gnt4_PSVECMag_bl(&local_a8);
  iVar1 = FUN_800452a0(-(double)*(float *)(param_9 + 0x3c),dVar11);
  *(short *)(param_9 + 0x70) = (short)iVar1;
  dVar11 = (double)local_a0;
  iVar1 = FUN_800452a0((double)local_a8,dVar11);
  *(short *)(param_9 + 0x72) = (short)iVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar12 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80336918 + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80336918 + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033690c + iVar4);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8033690e + iVar4);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar1 = zz_0006f98_(iVar10);
  zz_0006fb4_(uVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600),
              *(int *)(param_9 + 0xe0),(int)(char)(&DAT_80336560)[iVar5],uVar3,iVar2,iVar6,puVar7,
              iVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_80336908)[iVar4]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
    zz_01330b4_(param_9);
  }
  else {
    if (-1 < (char)(&DAT_80336562)[iVar5]) {
      *(undefined1 *)(param_9 + 0xa8) = 1;
      zz_00c74ec_(param_9,(int)(char)(&DAT_80336562)[iVar5]);
    }
    if (-1 < (char)(&DAT_8033692c)[iVar4]) {
      zz_01df908_(param_9,(&DAT_8033692c)[iVar4]);
    }
  }
  return;
}



// ==== 80132674  FUN_80132674 ====

void FUN_80132674(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x169)) {
    *(char *)(param_1 + 0x169) = *(char *)(param_1 + 0x169) + -1;
  }
  if ('\0' < *(char *)(param_1 + 0x16a)) {
    *(char *)(param_1 + 0x16a) = *(char *)(param_1 + 0x16a) + -1;
  }
  (*(code *)(&PTR_FUN_80336b64)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801326d8  FUN_801326d8 ====

void FUN_801326d8(int param_1)

{
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0xff;
  *(undefined *)(param_1 + 0x1b) = (&DAT_80336909)[*(char *)(param_1 + 0x12) * 0x28];
  *(undefined2 *)(param_1 + 0x1c) = 0x14;
  zz_0132734_(param_1);
  return;
}



// ==== 80132734  zz_0132734_ ====

void zz_0132734_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x12);
  zz_01330cc_(param_1,1);
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(&DAT_8033690a + cVar1 * 0x28);
  }
  return;
}



// ==== 801327ac  FUN_801327ac ====

void FUN_801327ac(int param_1)

{
  float fVar1;
  short sVar3;
  int iVar2;
  char cVar4;
  int iVar5;
  int iVar6;
  float afStack_28 [7];
  
  iVar5 = *(char *)(param_1 + 0x12) * 0x28;
  zz_0132f30_(param_1);
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if ((0 < sVar3) && (*(int *)(param_1 + 0xcc) != 0)) {
    iVar6 = *(int *)(param_1 + 200);
    if ((iVar6 != 0) &&
       ((((*(byte *)(param_1 + 0xd0) & 4) != 0 && (0 < *(short *)(param_1 + 0x1c6))) &&
        (iVar2 = zz_0083244_((float *)(param_1 + 0x20)), iVar2 == 0)))) {
      *(float *)(param_1 + 0x44) =
           *(float *)(&DAT_80336920 + iVar5) * *(float *)(param_1 + 0xb4) +
           *(float *)(param_1 + 0x44);
      fVar1 = *(float *)(&DAT_8033691c + iVar5) * *(float *)(param_1 + 0xb4);
      if (fVar1 < *(float *)(param_1 + 0x44)) {
        *(float *)(param_1 + 0x44) = fVar1;
      }
      zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      cVar4 = *(char *)(param_1 + 0x1cb) + -1;
      *(char *)(param_1 + 0x1cb) = cVar4;
      if (cVar4 < '\x01') {
        *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033690c + iVar5);
        gnt4_PSVECSubtract_bl((float *)(iVar6 + 100),(float *)(param_1 + 0x20),afStack_28);
        zz_006ebb4_(afStack_28,afStack_28);
        gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,afStack_28,afStack_28);
        gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),afStack_28,(float *)(param_1 + 0x38));
      }
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),afStack_28);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_28,(float *)(param_1 + 0x20));
      iVar5 = FUN_80083874((double)(*(float *)(&DAT_80336914 + iVar5) * *(float *)(param_1 + 0xb4)),
                           param_1);
      if (iVar5 != 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 0x14;
        zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
        zz_01332dc_(param_1);
      }
      goto LAB_80132950;
    }
  }
  *(undefined1 *)(param_1 + 0x19) = 6;
LAB_80132950:
  zz_0132f9c_(param_1);
  return;
}



// ==== 80132974  FUN_80132974 ====

void FUN_80132974(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x12);
  zz_0132f30_(param_1);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  FUN_80133358((double)*(float *)(&DAT_80336924 + cVar1 * 0x28),param_1);
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 10;
  }
  zz_0132f9c_(param_1);
  return;
}



// ==== 80132a00  FUN_80132a00 ====

void FUN_80132a00(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  float afStack_28 [5];
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = *(char *)(param_1 + 0x12) * 0x28;
  zz_0132f30_(param_1);
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x19) = 6;
  }
  else {
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (sVar2 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      cVar1 = (&DAT_8033692a)[iVar3];
      if (cVar1 == '\x01') {
        *(undefined2 *)(param_1 + 0x1c) = 0x1e;
        iVar4 = zz_006dbe0_(iVar4,0,1,1);
        if (iVar4 == 0) {
          *(undefined1 *)(param_1 + 0x1b) = 0;
        }
        else {
          zz_00c3be0_(param_1,(&DAT_8033692b)[iVar3]);
        }
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined2 *)(param_1 + 0x1c) = 0x1e;
          iVar4 = zz_006dbe0_(iVar4,2,1,1);
          if (iVar4 == 0) {
            *(undefined1 *)(param_1 + 0x1b) = 0;
          }
          else {
            zz_00c3be0_(param_1,(&DAT_8033692b)[iVar3]);
          }
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined2 *)(param_1 + 0x1c) = 0x7d;
        iVar3 = zz_006dbe0_(iVar4,0,1,1);
        if (iVar3 != 0) {
          *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar4 + 0xa60);
          *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar4 + 0xa70);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar4 + 0xa80);
          gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x524),(float *)(param_1 + 0x20),afStack_28);
          zz_006ec1c_(afStack_28,afStack_28);
          gnt4_PSQUATScale_bl((double)*(float *)(iVar4 + 0x814),afStack_28,afStack_28);
          gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_28,(float *)(param_1 + 0x158));
          *(undefined1 *)(param_1 + 0x169) = 0x41;
          *(undefined1 *)(param_1 + 0x16a) = 0x41;
          zz_01deb68_(iVar4,1,param_1 + 0x14c,param_1 + 0x20,param_1 + 0x169);
          zz_01deb68_(iVar4,4,param_1 + 0x20,(float *)(param_1 + 0x158),param_1 + 0x16a);
        }
      }
    }
  }
  zz_0132f9c_(param_1);
  return;
}



// ==== 80132bfc  FUN_80132bfc ====

void FUN_80132bfc(int param_1)

{
  short sVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if ((&DAT_8033692a)[*(char *)(param_1 + 0x12) * 0x28] == '\x02') {
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar3 + 0xa60);
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar3 + 0xa70);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar3 + 0xa80);
  }
  if (0 < *(short *)(param_1 + 0x1c6)) {
    sVar1 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar1;
    if (0 < sVar1) {
      return;
    }
    cVar2 = *(char *)(param_1 + 0x1b) + -1;
    *(char *)(param_1 + 0x1b) = cVar2;
    if ('\0' < cVar2) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + -2;
      *(undefined2 *)(param_1 + 0x1c) = 0x14;
      zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
      zz_01332dc_(param_1);
      return;
    }
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x169) = 0;
  *(undefined1 *)(param_1 + 0x16a) = 0;
  return;
}



// ==== 80132ce0  FUN_80132ce0 ====

void FUN_80132ce0(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar2 = *(char *)(param_1 + 0x12) * 0x28;
  iVar3 = *(int *)(param_1 + 0x90);
  *(float *)(param_1 + 0x44) =
       *(float *)(&DAT_80336920 + iVar2) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x44);
  fVar1 = *(float *)(&DAT_8033691c + iVar2) * *(float *)(param_1 + 0xb4);
  if (fVar1 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = fVar1;
  }
  iVar2 = iVar3 + *(char *)(param_1 + 0x89) * 0x30;
  local_18 = *(float *)(iVar2 + 0x8e0);
  local_14 = *(undefined4 *)(iVar2 + 0x8f0);
  local_10 = *(undefined4 *)(iVar2 + 0x900);
  gnt4_PSVECSubtract_bl(&local_18,(float *)(param_1 + 0x20),&local_18);
  dVar4 = gnt4_PSVECMag_bl(&local_18);
  if (dVar4 <= (double)(FLOAT_80439ef4 * *(float *)(param_1 + 0xb4))) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x14;
  }
  else {
    zz_006ebb4_(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,&local_18,&local_18);
    zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)FLOAT_80439ef0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),&local_18,(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_18,(float *)(param_1 + 0x20));
  }
  FUN_80132fcc(param_1,(float *)(iVar3 + 0x20));
  return;
}



// ==== 80132e3c  FUN_80132e3c ====

void FUN_80132e3c(int param_1)

{
  short sVar1;
  
  zz_01330cc_(param_1,1);
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x14;
  }
  return;
}



// ==== 80132e94  FUN_80132e94 ====

void FUN_80132e94(int param_1)

{
  short sVar1;
  
  zz_01330cc_(param_1,0);
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
    zz_01330b4_(param_1);
  }
  return;
}



// ==== 80132ef4  FUN_80132ef4 ====

void FUN_80132ef4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80132f30  zz_0132f30_ ====

void zz_0132f30_(int param_1)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 0x148);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    if ((*(char **)(param_1 + 0x144) != (char *)0x0) &&
       ((**(char **)(param_1 + 0x144) != '\0' && (pcVar1[0x18] < '\x02')))) goto LAB_80132f80;
  }
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x16b) = 0;
LAB_80132f80:
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x144);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_1 + 0x16b);
  return;
}



// ==== 80132f9c  zz_0132f9c_ ====

void zz_0132f9c_(int param_1)

{
  if (*(int *)(param_1 + 200) != 0) {
    FUN_80132fcc(param_1,(float *)(*(int *)(param_1 + 200) + 100));
  }
  return;
}



// ==== 80132fcc  FUN_80132fcc ====

/* WARNING: Removing unreachable block (ram,0x80133094) */
/* WARNING: Removing unreachable block (ram,0x80132fdc) */

void FUN_80132fcc(int param_1,float *param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_28;
  float local_24;
  float local_20;
  
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x20),&local_28);
  dVar5 = (double)local_24;
  local_24 = FLOAT_80439ee0;
  dVar4 = gnt4_PSVECMag_bl(&local_28);
  iVar2 = FUN_800452a0(-dVar5,dVar4);
  iVar3 = FUN_800452a0((double)local_28,(double)local_20);
  sVar1 = (short)iVar2 - *(short *)(param_1 + 0x70);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar1;
  sVar1 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if (0x800 < sVar1) {
    sVar1 = 0x800;
  }
  if (sVar1 < -0x800) {
    sVar1 = -0x800;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar1;
  return;
}



// ==== 801330b4  zz_01330b4_ ====

void zz_01330b4_(int param_1)

{
  **(byte **)(param_1 + 0x164) = **(byte **)(param_1 + 0x164) | *(byte *)(param_1 + 0x168);
  return;
}



// ==== 801330cc  zz_01330cc_ ====

/* WARNING: Removing unreachable block (ram,0x801332b8) */
/* WARNING: Removing unreachable block (ram,0x801330dc) */

void zz_01330cc_(int param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  double dVar3;
  double dVar4;
  float local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float afStack_a0 [12];
  float afStack_70 [2];
  float local_68;
  float local_58;
  float local_48;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  uStack_3c = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
  local_40 = 0x43300000;
  iVar1 = *(char *)(param_1 + 0x11) * 0x24;
  dVar3 = (double)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80439ee8) /
                  FLOAT_80439ef8);
  pfVar2 = (float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_80336561)[iVar1] * 0x30 + 0x8d4);
  gnt4_PSMTXMultVec_bl(pfVar2,(float *)(iVar1 + param_2 * 0xc + -0x7fcc9a9c),&local_ac);
  zz_0046588_(dVar3,(float *)(param_1 + 0x20),&local_ac,(float *)(param_1 + 0x20));
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(&DAT_80336580 + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80439ee8)),
                      afStack_a0,0x7a);
  gnt4_PSMTXConcat_bl(pfVar2,afStack_a0,afStack_70);
  local_30 = 0x43300000;
  uStack_2c = (int)*(short *)(&DAT_8033657e + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80439ee8)),
                      afStack_a0,0x79);
  gnt4_PSMTXConcat_bl(afStack_70,afStack_a0,afStack_70);
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(&DAT_8033657c + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80439ee8)),
                      afStack_a0,0x78);
  gnt4_PSMTXConcat_bl(afStack_70,afStack_a0,afStack_70);
  local_ac = local_68;
  local_a8 = local_58;
  local_a4 = local_48;
  local_b8 = *(float *)(param_1 + 0x11c);
  local_b4 = *(undefined4 *)(param_1 + 300);
  local_b0 = *(undefined4 *)(param_1 + 0x13c);
  zz_0046588_(dVar3,&local_b8,&local_ac,&local_ac);
  dVar4 = (double)local_a8;
  local_a8 = FLOAT_80439ee0;
  dVar3 = gnt4_PSVECMag_bl(&local_ac);
  iVar1 = FUN_800452a0(-dVar4,dVar3);
  *(short *)(param_1 + 0x70) = (short)iVar1;
  iVar1 = FUN_800452a0((double)local_ac,(double)local_a4);
  *(short *)(param_1 + 0x72) = (short)iVar1;
  return;
}



// ==== 801332dc  zz_01332dc_ ====

void zz_01332dc_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  uVar1 = uVar1 & 0xf;
  if (uVar1 == (int)*(char *)(param_1 + 0x1a)) {
    uVar1 = uVar1 + 1 & 0xf;
  }
  *(char *)(param_1 + 0x1a) = (char)uVar1;
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 80133358  FUN_80133358 ====

/* WARNING: Removing unreachable block (ram,0x801334e8) */
/* WARNING: Removing unreachable block (ram,0x80133368) */

void FUN_80133358(double param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float local_a8;
  float local_a4;
  float local_a0;
  float afStack_9c [12];
  float afStack_6c [3];
  undefined4 local_60;
  undefined4 local_50;
  undefined4 local_40;
  undefined4 local_38;
  uint uStack_34;
  
  iVar4 = *(int *)(param_2 + 0xcc);
  iVar1 = *(char *)(param_2 + 0x12) * 0x28;
  if ((iVar4 != 0) && (iVar3 = *(int *)(param_2 + 200), iVar3 != 0)) {
    pfVar2 = (float *)((char)(&DAT_8033692d)[iVar1] * 0x80 + -0x7fcc95e0 +
                      *(char *)(param_2 + 0x1a) * 8);
    gnt4_PSMTXRotRad_bl((double)*pfVar2,afStack_6c,0x78);
    gnt4_PSMTXRotRad_bl((double)pfVar2[1],afStack_9c,0x79);
    gnt4_PSMTXConcat_bl(afStack_9c,afStack_6c,afStack_6c);
    local_a8 = FLOAT_80439ee0;
    local_a4 = FLOAT_80439ee0;
    if ((*(char *)(iVar4 + 0x83) == '\0') && (*(int *)(iVar4 + 0x4b0) != 0)) {
      local_a0 = FLOAT_80439efc * *(float *)(*(int *)(iVar4 + 0x4b0) + 0x44);
    }
    else {
      local_a0 = FLOAT_80439f00;
    }
    local_a0 = (float)((double)(local_a0 * *(float *)(iVar4 + 0xb4)) + param_1);
    if ((&DAT_8033692d)[iVar1] == '\x01') {
      iVar1 = *(int *)(param_2 + 0x90);
      local_60 = *(undefined4 *)(iVar1 + 0xa60);
      local_50 = *(undefined4 *)(iVar1 + 0xa70);
      local_40 = *(undefined4 *)(iVar1 + 0xa80);
    }
    else {
      local_60 = *(undefined4 *)(iVar3 + 100);
      local_50 = *(undefined4 *)(iVar3 + 0x68);
      local_40 = *(undefined4 *)(iVar3 + 0x6c);
    }
    gnt4_PSMTXMultVec_bl(afStack_6c,&local_a8,(float *)(param_2 + 0x158));
  }
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(param_2 + 0x1c) ^ 0x80000000;
  zz_0046588_((double)((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80439ee8) /
                      FLOAT_80439ef8),(float *)(param_2 + 0x14c),(float *)(param_2 + 0x158),
              (float *)(param_2 + 0x20));
  return;
}



// ==== 80133504  FUN_80133504 ====

void FUN_80133504(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80133510  FUN_80133510 ====

void FUN_80133510(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80133530  FUN_80133530 ====

void FUN_80133530(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8013358c  zz_013358c_ ====

void zz_013358c_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x302) || (sVar1 == 0x306)) || (sVar1 == 0x307)) || (sVar1 == 0x30d)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,6), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_801336a4;
    *(code **)(puVar2 + 0x10c) = FUN_80133cbc;
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



// ==== 801336a4  FUN_801336a4 ====

void FUN_801336a4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80336c18)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801336f8  FUN_801336f8 ====

void FUN_801336f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x84) = 0;
  *(code **)(param_9 + 0x100) = FUN_80133b04;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  if (*(char *)(param_9 + 0x11) == '\x03') {
    *(undefined1 *)(param_9 + 0x89) = 6;
  }
  else {
    *(undefined1 *)(param_9 + 0x89) = 7;
  }
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  puVar5 = (undefined4 *)(&DAT_80336ba8 + iVar3);
  uVar4 = *puVar5;
  uVar1 = *(undefined4 *)(&DAT_80336bac + iVar3);
  *(undefined4 *)(param_9 + 100) = uVar4;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80336bb0 + iVar3);
  *(int *)(param_9 + 0x174) = param_9 + 0x114;
  *(int *)(param_9 + 0x178) = param_9 + 0x144;
  *(undefined1 *)(param_9 + 0x12) = 2;
  iVar6 = zz_0006f98_(iVar6);
  if (*(char *)(param_9 + 0x11) == 3) {
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe8),(int)sRam80336ba4,
                        iVar6 + 0xc28,uVar4,puVar5,in_r9,in_r10);
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xec),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_02,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xec));
  }
  else {
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                        (int)*(short *)(&DAT_80336b90 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe8),
                        (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xf0),
                        (int)*(short *)(&DAT_80336b94 + *(char *)(param_9 + 0x11) * 6),iVar6 + 0xc28
                        ,uVar4,puVar5,in_r9,in_r10);
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b90 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xe4));
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b92 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xec),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_00,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    uVar7 = zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xec));
    iVar2 = iVar6 + 0xc28;
    iVar3 = (int)*(short *)(&DAT_80336b94 + *(char *)(param_9 + 0x11) * 6);
    uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xf4),iVar3,iVar2,uVar4,puVar5,
                        in_r9,in_r10);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xf4),extraout_r4_01,iVar3,iVar2,uVar4,puVar5,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439f08,*(int *)(param_9 + 0xf4));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0133980_(param_9);
  return;
}



// ==== 80133980  zz_0133980_ ====

void zz_0133980_(int param_1)

{
  float *pfVar1;
  int iVar2;
  float afStack_28 [4];
  double local_18;
  double local_10;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ('\0' < *(char *)(iVar2 + 0x6e8)) {
    *(char *)(param_1 + 0x12) = *(char *)(iVar2 + 0x6e8);
  }
  if ((*(uint *)(iVar2 + 0x5e0) & 0x20000000) == 0) {
    if ((*(char *)(param_1 + 0x12) == '\x01') && (*(char *)(iVar2 + 0x6e9) == '\x01')) {
      pfVar1 = (float *)(*(char *)(param_1 + 0x11) * 0x18 + -0x7fcc944c);
    }
    else {
      pfVar1 = (float *)(&DAT_80336ba8 + *(char *)(param_1 + 0x11) * 0x18);
    }
    gnt4_PSVECSubtract_bl(pfVar1,(float *)(param_1 + 100),afStack_28);
    gnt4_PSQUATScale_bl((double)FLOAT_80439f0c,afStack_28,afStack_28);
    gnt4_PSVECAdd_bl((float *)(param_1 + 100),afStack_28,(float *)(param_1 + 100));
    if (*(char *)(param_1 + 0x12) == '\x03') {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x17c)) ^ 0x80000000);
      *(short *)(param_1 + 0x17c) =
           (short)(int)-(FLOAT_80439f10 * *(float *)(iVar2 + 0x1dc8) -
                        (float)(local_18 - DOUBLE_80439f18));
    }
    else {
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x17c)) ^ 0x80000000);
      *(short *)(param_1 + 0x17c) =
           (short)(int)-(FLOAT_80439f14 * *(float *)(iVar2 + 0x1dc8) -
                        (float)(local_10 - DOUBLE_80439f18));
    }
  }
  return;
}



// ==== 80133ae4  FUN_80133ae4 ====

void FUN_80133ae4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80133b04  FUN_80133b04 ====

void FUN_80133b04(int param_1)

{
  int iVar1;
  double dVar2;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  iVar1 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXCopy_bl((float *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  if (*(char *)(param_1 + 0x11) == '\x03') {
    dVar2 = (double)*(float *)(iVar1 + 0xb4);
    gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,(float *)(param_1 + 0x114));
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(iVar1 + 0x72) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x114));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  }
  if (*(char *)(param_1 + 0x12) == '\x01') {
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_1 + 0x17c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x144));
  }
  if (*(char *)(param_1 + 0x12) == '\x03') {
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_1 + 0x17c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80439f20 *
                                (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80439f18)),
                        afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,(float *)(param_1 + 0x144));
    gnt4_PSMTXScale_bl((double)FLOAT_80439f24,(double)FLOAT_80439f28,(double)FLOAT_80439f24,
                       afStack_48);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x144),afStack_48,(float *)(param_1 + 0x144));
  }
  return;
}



// ==== 80133cbc  FUN_80133cbc ====

void FUN_80133cbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  cVar1 = *(char *)(param_9 + 0x12);
  iVar4 = *(int *)(param_9 + 0x90);
  if (cVar1 != '\0') {
    cVar2 = *(char *)(param_9 + 0x11);
    if (((cVar2 != '\x02') && (cVar2 != '\x03')) || (*(char *)(iVar4 + 0x6f6) != '\0')) {
      iVar5 = 1;
      if (cVar1 == '\x01') {
        iVar5 = 2;
      }
      if (cVar1 == '\x03') {
        iVar5 = 2;
      }
      if (cVar2 == '\x03') {
        iVar5 = 1;
      }
      iVar9 = param_9 + 0x144;
      iVar6 = 0;
      iVar8 = 0;
      while( true ) {
        if (iVar5 <= iVar6) break;
        iVar7 = 1;
        if ((*(char *)(iVar4 + 0xae) == '\0') && (*(char *)(iVar4 + 0x3ec) != '\x04')) {
          iVar7 = 0;
        }
        iVar3 = *(int *)(param_9 +
                        (iVar7 + (char)(&DAT_804345d0)[*(char *)(param_9 + 0x12) * 2 + iVar6]) * 4 +
                        0xe0);
        zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                    *(float **)(iVar9 + 0x30),param_11,param_12,param_13,param_14,param_15,param_16)
        ;
        param_1 = zz_00097b4_(iVar3,(int)(char)(&DAT_80336c08)
                                               [iVar7 + iVar8 + *(char *)(param_9 + 0x12) * 4]);
        iVar9 = iVar9 + 4;
        iVar8 = iVar8 + 2;
        iVar6 = iVar6 + 1;
      }
    }
  }
  return;
}



// ==== 80133df4  zz_0133df4_ ====

void zz_0133df4_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xc0);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e3758_(param_1,-0x7fcc93d8,2,puVar3 + 3,(float *)(puVar3 + 0x12));
    zz_00e3758_(param_1,-0x7fcc9378,3,puVar3 + 9,(float *)(puVar3 + 0x18));
  }
  return;
}



// ==== 80133e90  zz_0133e90_ ====

void zz_0133e90_(int param_1)

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
      zz_00e38a4_(param_1,(float *)&DAT_80336c28,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12));
      zz_00e38a4_(param_1,(float *)&DAT_80336c88,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x18));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcc93d8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      FUN_800e4f9c(param_1,-0x7fcc9378,3,(float *)(puVar2 + 9),(float *)(puVar2 + 0x27));
    }
  }
  return;
}



// ==== 80133f68  zz_0133f68_ ====

void zz_0133f68_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80133fa0  zz_0133fa0_ ====

void zz_0133fa0_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc93d8,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc9378,3,pfVar2 + 9,afStack_18);
    zz_00e5184_(param_1,-0x7fcc93d8,2,pfVar2 + 3,pfVar2 + 0x21);
    zz_00e5184_(param_1,-0x7fcc9378,3,pfVar2 + 9,pfVar2 + 0x27);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801341c8  FUN_801341c8 ====

void FUN_801341c8(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 1000) == 0x304) {
    zz_00cbb00_(param_1,0);
    iVar1 = 0;
    do {
      zz_01390a4_(param_1,(char)iVar1,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    zz_00c74ec_(param_1,8);
  }
  else if (*(short *)(param_1 + 1000) == 0x308) {
    zz_00cbb00_(param_1,1);
    zz_01390a4_(param_1,2,1);
    zz_01390a4_(param_1,3,1);
  }
  zz_0133df4_(param_1);
  *(undefined1 *)(param_1 + 0x144) = 2;
  return;
}



// ==== 8013427c  FUN_8013427c ====

void FUN_8013427c(int param_1)

{
  zz_010a4ac_(param_1);
  if (*(short *)(param_1 + 1000) == 0x308) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
    *(undefined1 *)(param_1 + 0x748) = 2;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
    *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  }
  return;
}



// ==== 801342ec  FUN_801342ec ====

void FUN_801342ec(int param_1)

{
  bool bVar1;
  char cVar2;
  
  switch(*(undefined1 *)(param_1 + 0x6e8)) {
  case 1:
    *(undefined1 *)(param_1 + 0x144) = 1;
    cVar2 = *(char *)(param_1 + 0x6e9);
    if (cVar2 != '\x03') {
      if (cVar2 < '\x03') {
        if (cVar2 == '\x01') {
          *(undefined1 *)(param_1 + 0x145) = 3;
          *(undefined1 *)(param_1 + 0xaf) = 1;
          zz_001ab6c_(param_1,0x11);
          break;
        }
        if ('\0' < cVar2) {
          *(undefined1 *)(param_1 + 0xaf) = 0xff;
          break;
        }
      }
      else if (cVar2 < '\x05') {
        *(undefined1 *)(param_1 + 0x145) = 4;
        break;
      }
    }
    *(undefined1 *)(param_1 + 0x145) = 3;
    break;
  case 2:
    *(undefined1 *)(param_1 + 0x144) = 2;
    break;
  case 3:
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
    break;
  case 5:
    *(undefined1 *)(param_1 + 0x144) = 5;
    *(undefined1 *)(param_1 + 0x145) = *(undefined1 *)(param_1 + 0x6e9);
    break;
  case 0xff:
    if (*(char *)(param_1 + 0x144) == '\x05') {
      *(undefined1 *)(param_1 + 0x144) = 2;
    }
  }
  *(undefined1 *)(param_1 + 0x6e8) = 0;
  *(undefined1 *)(param_1 + 0x6e9) = 0;
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x1d94) = 0;
  }
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  return;
}



// ==== 801344a8  FUN_801344a8 ====

void FUN_801344a8(int param_1)

{
  zz_0133e90_(param_1);
  return;
}



// ==== 801344d4  FUN_801344d4 ====

void FUN_801344d4(int param_1)

{
  zz_0133f68_(param_1);
  return;
}



// ==== 801344f4  FUN_801344f4 ====

void FUN_801344f4(int param_1)

{
  zz_0133fa0_(param_1);
  return;
}



// ==== 80134514  FUN_80134514 ====

void FUN_80134514(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804345d8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80134580  FUN_80134580 ====

void FUN_80134580(int param_1)

{
  (*(code *)(&PTR_FUN_80336d74)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801345bc  FUN_801345bc ====

void FUN_801345bc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80336d80)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80134604  FUN_80134604 ====

void FUN_80134604(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 80134628  FUN_80134628 ====

void FUN_80134628(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 8013464c  FUN_8013464c ====

void FUN_8013464c(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 80134670  FUN_80134670 ====

void FUN_80134670(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 80134694  FUN_80134694 ====

void FUN_80134694(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 801346b8  FUN_801346b8 ====

void FUN_801346b8(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x308) {
    zz_0134770_(param_1);
  }
  else {
    zz_01346ec_(param_1);
  }
  return;
}



// ==== 801346ec  zz_01346ec_ ====

void zz_01346ec_(int param_1)

{
  zz_010c9d8_(param_1);
  return;
}



// ==== 80134714  FUN_80134714 ====

undefined4 FUN_80134714(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    zz_016cc24_(param_1,1);
    uVar2 = 0x8444;
  }
  return uVar2;
}



// ==== 80134770  zz_0134770_ ====

void zz_0134770_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80336da4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801347c0  FUN_801347c0 ====

void FUN_801347c0(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439f34;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 4;
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_80439f30;
  *(float *)(param_1 + 0x50) = FLOAT_80439f30;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439f38,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439f3c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(undefined1 *)(param_1 + 0x1d9b) = 0;
  return;
}



// ==== 8013490c  FUN_8013490c ====

void FUN_8013490c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439f38,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439f30;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801349c4  FUN_801349c4 ====

void FUN_801349c4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_80439f38,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
    FUN_800061a8(param_1,9);
  }
  fVar2 = FLOAT_80439f44;
  fVar1 = FLOAT_80439f40;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80439f48;
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x55c) = fVar2;
    *(float *)(param_1 + 0x560) = fVar3;
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439f4c * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
    fVar1 = FLOAT_80439f30;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439f4c * -dVar4);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 4;
    zz_00b2190_(param_1,0);
    *(float *)(param_1 + 0x80c) = FLOAT_80439f30;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_00f036c_(param_1,0xf2);
  }
  return;
}



// ==== 80134af8  FUN_80134af8 ====

void FUN_80134af8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  dVar4 = (double)FLOAT_80439f38;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_006ed8c_(dVar4,param_1);
  FUN_80067310((double)FLOAT_80439f44,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_80439f30;
  fVar2 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x55c) = fVar2;
  if (fVar2 <= fVar3) {
    FUN_8016c810((double)*(float *)(param_1 + 0x560),param_1,7,0);
    fVar2 = FLOAT_80439f44;
    *(float *)(param_1 + 0x55c) = FLOAT_80439f44;
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - fVar2;
  }
  fVar3 = FLOAT_80439f30;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_80439f3c;
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



// ==== 80134c38  FUN_80134c38 ====

void FUN_80134c38(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439f60) * FLOAT_80439f50);
  if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
    zz_00107a0_(param_1,0x10);
  }
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439f44,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439f54 + *(float *)(param_1 + 0x1dc8);
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
    *(float *)(param_1 + 0x694) = FLOAT_80439f58 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80134e64  FUN_80134e64 ====

void FUN_80134e64(int param_1)

{
  zz_00960a0_(param_1);
  zz_0138d18_(param_1,0);
  return;
}



// ==== 80134ee0  FUN_80134ee0 ====

void FUN_80134ee0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_804345e0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80134f1c  FUN_80134f1c ====

void FUN_80134f1c(int param_1)

{
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float afStack_44 [3];
  float local_38;
  undefined4 local_28;
  undefined4 local_18;
  
  local_50 = *(float *)(param_1 + 0xa24);
  local_4c = *(undefined4 *)(param_1 + 0xa34);
  local_48 = *(undefined4 *)(param_1 + 0xa44);
  gnt4_PSQUATScale_bl((double)FLOAT_80439f68,&local_50,&local_50);
  local_5c = *(undefined4 *)(param_1 + 0xa2c);
  local_58 = *(undefined4 *)(param_1 + 0xa3c);
  local_54 = *(undefined4 *)(param_1 + 0xa4c);
  gnt4_PSMTXIdentity_bl(afStack_44);
  zz_0045ef4_(afStack_44,5,&local_50,&local_5c);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xa24),(float *)&DAT_80337f20,&local_68);
  local_38 = local_68;
  local_28 = local_64;
  local_18 = local_60;
  zz_00aedc0_(param_1,afStack_44,0,*(undefined1 *)(param_1 + 0x88));
  zz_00f036c_(param_1,6);
  *(undefined1 *)(param_1 + 0x6f5) = 6;
  return;
}



// ==== 80134ff8  FUN_80134ff8 ====

void FUN_80134ff8(int param_1)

{
  (*(code *)(&PTR_FUN_80337f2c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80135034  FUN_80135034 ====

void FUN_80135034(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f5) = 4;
  if (*(int *)(param_1 + 0xcc) != 0) {
    zz_006bda8_(param_1);
  }
  (*(code *)(&PTR_FUN_80337f38)[*(char *)(param_1 + 0x581)])(param_1);
  return;
}



// ==== 80135098  FUN_80135098 ====

void FUN_80135098(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_01350f0__80337f4c)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 801350f0  zz_01350f0_ ====

void zz_01350f0_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439f70;
  fVar1 = FLOAT_80439f6c;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  (*(code *)(&PTR_FUN_80337f58)[*(char *)(param_1 + 0x581)])(param_1,0);
  return;
}



// ==== 80135150  FUN_80135150 ====

void FUN_80135150(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80439f68,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\x02') || (*(char *)(param_1 + 0x1d0d) != param_2)) {
    zz_004beb8_((double)FLOAT_80439f68,param_1,2,2,param_2,4,2);
  }
  return;
}



// ==== 801351dc  FUN_801351dc ====

void FUN_801351dc(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    zz_004beb8_((double)FLOAT_80439f68,param_1,1,2,param_2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8013523c  FUN_8013523c ====

void FUN_8013523c(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x543) < '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 4;
    zz_006a3d0_(param_1,'\0',4,2);
  }
  else {
    zz_004beb8_((double)FLOAT_80439f68,param_1,1,2,param_2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801352a8  FUN_801352a8 ====

void FUN_801352a8(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80439f68,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80439f68,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80135324  FUN_80135324 ====

void FUN_80135324(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_80439f68,param_1,1,2,param_2,0xffffffff,0xffffffff);
  return;
}



// ==== 8013535c  FUN_8013535c ====

void FUN_8013535c(int param_1)

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
    zz_0135b10_(param_1);
  }
  return;
}



// ==== 80135408  FUN_80135408 ====

void FUN_80135408(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_80439f74) {
    if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_01359ec_(param_9);
        return;
      }
      goto LAB_80135490;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_80135490:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801354c4  FUN_801354c4 ====

void FUN_801354c4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80337f6c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013550c  FUN_8013550c ====

void FUN_8013550c(int param_1)

{
  zz_01350f0_(param_1);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
  return;
}



// ==== 80135554  FUN_80135554 ====

/* WARNING: Removing unreachable block (ram,0x801355f0) */
/* WARNING: Removing unreachable block (ram,0x80135564) */

void FUN_80135554(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439f74;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    zz_004cd24_(param_1,0xf);
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0135b10_(param_1);
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



// ==== 8013560c  FUN_8013560c ====

void FUN_8013560c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439f74) {
    if ((*(uint *)(param_1 + 0x5b4) & 0x200) == 0) {
      if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_1 + 0x1cee) == '\0')) {
        return;
      }
    }
    else {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if (iVar1 != 0) {
        zz_01359ec_(param_1);
        return;
      }
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    zz_006d0dc_(param_1,0xc1,0);
  }
  return;
}



// ==== 801356d4  FUN_801356d4 ====

void FUN_801356d4(int param_1)

{
  (*(code *)(&PTR_zz_01350f0__80337f78)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80135710  FUN_80135710 ====

void FUN_80135710(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(undefined1 *)(param_1 + 0x581) = 0;
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      *(undefined1 *)(param_1 + 0x581) = 4;
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    zz_006d0dc_(param_1,0x81,0);
    zz_006dee8_(param_1,1);
    zz_004cd24_(param_1,1);
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_0135b10_(param_1);
    }
  }
  return;
}



// ==== 801357cc  FUN_801357cc ====

void FUN_801357cc(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if ((*(uint *)(param_9 + 0x5e0) & 0x20) != 0) {
    param_11 = 0;
    zz_006d0dc_(param_9,0x81,0);
    zz_006dee8_(param_9,1);
    zz_004cd24_(param_9,1);
    param_1 = (double)*(float *)(param_9 + 0x558);
    if (param_1 <= (double)FLOAT_80439f74) {
      if ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) {
        param_11 = 1;
        param_12 = 0;
        iVar1 = zz_006dbe0_(param_9,0,1,0);
        if (iVar1 != 0) {
          zz_01359ec_(param_9);
          return;
        }
        goto LAB_80135870;
      }
    }
    else {
      *(float *)(param_9 + 0x558) = (float)(param_1 - (double)*(float *)(param_9 + 0x1dc8));
    }
    if (*(char *)(param_9 + 0x1cee) == '\0') {
      return;
    }
  }
LAB_80135870:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801358a4  FUN_801358a4 ====

void FUN_801358a4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80337f84)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801358ec  FUN_801358ec ====

void FUN_801358ec(int param_1)

{
  double dVar1;
  
  zz_01350f0_(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80439f78;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439f74;
  return;
}



// ==== 80135954  FUN_80135954 ====

void FUN_80135954(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0135b10_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  FUN_80067310((double)FLOAT_80439f78,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_00b22f4_(param_1);
  return;
}



// ==== 801359ec  zz_01359ec_ ====

void zz_01359ec_(int param_1)

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
      else if (*(char *)(param_1 + 0x7cc) == '\0') {
        if ((uVar3 & 0x40) == 0) {
          uVar5 = 0;
        }
        else {
          uVar5 = 3;
        }
      }
      else {
        uVar5 = 2;
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
  fVar1 = FLOAT_80439f6c;
  *(undefined1 *)(param_1 + 0x542) = 0;
  fVar2 = FLOAT_80439f70;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  (*(code *)(&PTR_FUN_80337f90)[*(char *)(param_1 + 0x581)])(param_1,1);
  return;
}



// ==== 80135b10  zz_0135b10_ ====

void zz_0135b10_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x1d);
  }
  return;
}



// ==== 80135b5c  FUN_80135b5c ====

void FUN_80135b5c(int param_1)

{
  (*(code *)(&PTR_FUN_80337fa4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80135b98  FUN_80135b98 ====

void FUN_80135b98(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80337fb8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80135be8  FUN_80135be8 ====

void FUN_80135be8(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_80439f74;
  *(float *)(param_1 + 0x50) = FLOAT_80439f74;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439f7c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439f68;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439f74;
  return;
}



// ==== 80135ce8  FUN_80135ce8 ====

void FUN_80135ce8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  gnt4_PSQUATScale_bl((double)FLOAT_80439f7c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_80439f84;
    fVar3 = FLOAT_80439f80;
    fVar2 = FLOAT_80439f74;
    if (*(char *)(param_1 + 0x1d0f) != '\0') {
      *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
      fVar1 = FLOAT_80439f68;
      *(float *)(param_1 + 0x44) = fVar3;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x48) = fVar4;
      *(float *)(param_1 + 0x50) = fVar1;
    }
    iVar5 = zz_006dbe0_(param_1,2,1,1);
    if (iVar5 != 0) {
      zz_007db5c_(param_1,4);
    }
  }
  dVar6 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439f88 < dVar6) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80135de4  FUN_80135de4 ====

void FUN_80135de4(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439f78,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (((iVar1 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439f8c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80439f8c + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80135fc8  FUN_80135fc8 ====

void FUN_80135fc8(int param_1)

{
  zz_00f8c58_(param_1);
  zz_00f8134_(param_1);
  zz_00c74ec_(param_1,0x36);
  *(undefined1 *)(param_1 + 0x14c) = 0;
  return;
}



// ==== 80136010  FUN_80136010 ====

void FUN_80136010(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  dVar4 = DOUBLE_80439fa0;
  fVar3 = FLOAT_80439f98;
  fVar2 = FLOAT_80439f94;
  fVar1 = FLOAT_80439f90;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_80439fa0) *
                   (FLOAT_80439f94 * (FLOAT_80439f98 - *(float *)(param_1 + 0x1dc8)) +
                   FLOAT_80439f90));
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) - dVar4
                           ) * (fVar2 * (fVar3 - *(float *)(param_1 + 0x1dc8)) + fVar1));
  *(short *)(param_1 + 0x18fc) = *(short *)(param_1 + 0x18fc) + 0x800;
  *(short *)(param_1 + 0x1902) = *(short *)(param_1 + 0x1902) + 0x800;
  *(short *)(param_1 + 0x190c) = *(short *)(param_1 + 0x190c) + 0x3113;
  if (0 < *(short *)(param_1 + 0x784)) {
    *(undefined1 *)(param_1 + 0x148) = 0;
    *(undefined1 *)(param_1 + 0x149) = 0;
  }
  zz_00f0104_(param_1,0x10,6);
  return;
}



// ==== 801360f8  FUN_801360f8 ====

void FUN_801360f8(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_80439fa8;
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x14b) = 0;
  }
  else {
    if (*(char *)(param_1 + 0x14b) == '\0') {
      *(undefined1 *)(param_1 + 0x14b) = 1;
      *(float *)(param_1 + 0x80c) = fVar1;
    }
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x743) != '\0') {
    if (*(char *)(param_1 + 0x14a) == '\0') {
      if (*(char *)(param_1 + 0x6f6) == '\0') {
        *(undefined1 *)(param_1 + 0x6f6) = 1;
        zz_0010784_(param_1);
      }
      *(undefined1 *)(param_1 + 0x6f7) = 0;
      *(undefined4 *)(param_1 + 0x144) = 0;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xdf;
      *(undefined1 *)(param_1 + 0x73f) = 0;
    }
    else {
      if (*(int *)(param_1 + 0x144) != 0) {
        if (*(char *)(param_1 + 0x6f7) == '\0') {
          *(undefined1 *)(param_1 + 0x6f7) = 1;
          zz_006bc74_(param_1,*(char **)(param_1 + 0x144));
          zz_00107a0_(param_1,0x17);
        }
        else {
          *(undefined1 *)(param_1 + 0x596) = 2;
        }
      }
      *(undefined1 *)(param_1 + 0x6f6) = 0;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 0x20;
      *(undefined1 *)(param_1 + 0x73f) = 1;
    }
  }
  *(short *)(param_1 + 0x18ec) = -*(short *)(param_1 + 0x1d64);
  *(short *)(param_1 + 0x18e6) = -*(short *)(param_1 + 0x1d64);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  return;
}



// ==== 8013623c  FUN_8013623c ====

void FUN_8013623c(int param_1)

{
  (*(code *)(&PTR_FUN_80338c38)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80136278  FUN_80136278 ====

void FUN_80136278(int param_1)

{
  int iVar1;
  
  (*(code *)(&PTR_LAB_80338c44)[*(char *)(param_1 + 0x540)])();
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0x81);
  iVar1 = zz_0066ac0_(param_1,0);
  if (iVar1 == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80439f90;
  }
  else {
    *(float *)(param_1 + 0x44) =
         (FLOAT_80439fac * *(float *)(param_1 + 0x44) +
         FLOAT_80439fb0 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c)) / FLOAT_80439fb4;
  }
  zz_0067458_((double)FLOAT_80439f98,param_1,*(short *)(param_1 + 0x5ac));
  return;
}



// ==== 80136354  FUN_80136354 ====

void FUN_80136354(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80439fbc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,8,1,(short *)&DAT_804345e8);
  if ((iVar1 != 0) || (*(float *)(param_1 + 0x558) < FLOAT_80439fa8)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 801363d4  FUN_801363d4 ====

void FUN_801363d4(int param_1)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 4;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (*(char *)(param_1 + 0x14c) == '\0') {
        zz_0082824_(param_1,0x12);
      }
      else {
        zz_0082824_(param_1,0x13);
      }
      *(byte *)(param_1 + 0x14c) = *(byte *)(param_1 + 0x14c) ^ 1;
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      if (1 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (0x13 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  return;
}



// ==== 801364e4  FUN_801364e4 ====

void FUN_801364e4(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80136530  FUN_80136530 ====

void FUN_80136530(int param_1)

{
  (*(code *)(&PTR_FUN_80338c54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013656c  FUN_8013656c ====

void FUN_8013656c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439fc0;
  fVar1 = FLOAT_80439fa8;
  dVar3 = (double)FLOAT_80439f98;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x548) = 0;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x709) = 0;
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 801365c8  FUN_801365c8 ====

void FUN_801365c8(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_006660c_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dcc);
  iVar2 = FUN_800669d0(param_1,0x81);
  fVar1 = FLOAT_80439fa8;
  if ((iVar2 != 0) || (*(float *)(param_1 + 0x558) < FLOAT_80439fa8)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  zz_0067458_((double)FLOAT_80439f98,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8013664c  FUN_8013664c ====

void FUN_8013664c(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 4;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 != 0) {
      *(undefined1 *)(param_1 + 0x148) = 1;
      zz_01043ac_(param_1,0);
      *(undefined1 *)(param_1 + 0x149) = 1;
      zz_01043ac_(param_1,1);
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0x1e;
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (0x13 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  zz_0067458_((double)FLOAT_80439f98,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8013673c  FUN_8013673c ====

void FUN_8013673c(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80439f98;
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  zz_0067458_(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801367a4  FUN_801367a4 ====

void FUN_801367a4(int param_1)

{
  (*(code *)(&PTR_LAB_80338c64)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801367f0  FUN_801367f0 ====

uint FUN_801367f0(int param_1)

{
  bool bVar2;
  uint uVar1;
  
  if (*(char *)(param_1 + 0x14a) == '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0xf;
    *(undefined1 *)(param_1 + 0x14a) = 1;
    bVar2 = zz_00fd3c0_(param_1);
    uVar1 = (uint)bVar2;
  }
  else {
    uVar1 = zz_006a53c_(param_1,10);
  }
  return uVar1;
}



// ==== 80136844  FUN_80136844 ====

void FUN_80136844(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 80136880  FUN_80136880 ====

void FUN_80136880(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x601) || (*(short *)(param_1 + 1000) == 0x617)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80136990;
    *(code **)(puVar1 + 0x10c) = FUN_80136bac;
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



// ==== 80136990  FUN_80136990 ====

void FUN_80136990(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80338fd8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801369e4  FUN_801369e4 ====

void FUN_801369e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439fc8;
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  *(char *)(param_9 + 0x13) = (char)*(undefined2 *)(&DAT_80338f8e + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80338f7a + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80338f80 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80338f7c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80338f84 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80338f88 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80338f8c + iVar3);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80338f78 + iVar3),iVar6 + 0xc28,iVar5,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80338f78 + iVar3);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,iVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439fcc,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0136b18_(param_9);
  return;
}



// ==== 80136b18  zz_0136b18_ ====

void zz_0136b18_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  fVar2 = FLOAT_80439fd4;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = iVar4 + *(char *)(param_1 + 0x13);
  fVar1 = FLOAT_80439fd0 + *(float *)(param_1 + 0x58);
  if (*(char *)(iVar3 + 0x14a) == '\x01') {
    *(undefined1 *)(iVar3 + 0x14a) = 0;
    fVar1 = fVar2;
  }
  if (*(short *)(iVar4 + 0x774) < 1) {
    fVar1 = FLOAT_80439fd4;
  }
  if (FLOAT_80439fc8 < fVar1) {
    fVar1 = FLOAT_80439fc8;
  }
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  return;
}



// ==== 80136b8c  FUN_80136b8c ====

void FUN_80136b8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80136bac  FUN_80136bac ====

void FUN_80136bac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((double)FLOAT_80439fd4 < (double)*(float *)(param_9 + 0x58)) {
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



// ==== 80136c40  zz_0136c40_ ====

void zz_0136c40_(int param_1,undefined1 param_2,undefined1 param_3)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x501) || (sVar1 == 0x50b)) || (sVar1 == 0x50d)) || (sVar1 == 0x517)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x13] = param_3;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80136d70;
    *(code **)(puVar2 + 0x10c) = FUN_80137140;
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



// ==== 80136d70  FUN_80136d70 ====

void FUN_80136d70(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803391a8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80136dc4  FUN_80136dc4 ====

void FUN_80136dc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 uVar10;
  
  fVar1 = FLOAT_80439fd8;
  uVar8 = 0;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined *)(param_9 + 0x84) = (&DAT_804345f8)[*(char *)(param_9 + 0x13)];
  *(undefined *)(param_9 + 0x89) = (&DAT_804345f0)[*(char *)(param_9 + 0x13)];
  iVar9 = (int)*(char *)(param_9 + 0x11) >> 0x1f;
  puVar7 = (undefined4 *)
           ((iVar9 + (uint)(1 < (uint)(int)*(char *)(param_9 + 0x11))) * 0x3c + -0x7fcc7018 +
           *(char *)(param_9 + 0x13) * 0xc);
  uVar3 = puVar7[1];
  *(undefined4 *)(param_9 + 100) = *puVar7;
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = puVar7[2];
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_80339060 + *(char *)(param_9 + 0x13) * 2);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined1 *)(param_9 + 0x150) = 0xff;
  iVar2 = zz_0006f98_(*(int *)(param_9 + 0x90));
  iVar5 = *(char *)(param_9 + 0x11) * 0x14;
  uVar10 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe0),
                       *(int *)(iVar5 + -0x7fcc6f94 + *(char *)(param_9 + 0x13) * 4),iVar2 + 0xc28,
                       iVar5,puVar7,uVar8,iVar9);
  iVar6 = *(char *)(param_9 + 0x11) * 0x14;
  iVar4 = iVar2 + 0xc28;
  iVar5 = *(int *)(iVar6 + -0x7fcc6f94 + *(char *)(param_9 + 0x13) * 4);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar4,iVar6,puVar7,
                       uVar8,iVar9);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),extraout_r4,iVar5,iVar4,iVar6,puVar7,uVar8,iVar9);
  zz_0007cac_((double)FLOAT_80439fdc,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0136f68_(param_9);
  return;
}



// ==== 80136f68  zz_0136f68_ ====

void zz_0136f68_(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  int iVar6;
  short *psVar7;
  
  iVar6 = *(int *)(param_1 + 0x90);
  cVar1 = *(char *)(iVar6 + 0x6e8);
  if ((int)*(char *)(param_1 + 0x150) != (int)cVar1) {
    *(char *)(param_1 + 0x150) = cVar1;
    fVar4 = FLOAT_80439fe0;
    *(undefined **)(param_1 + 0x148) = (&PTR_DAT_80339188)[cVar1];
    *(float *)(param_1 + 0x144) = fVar4;
  }
  fVar4 = FLOAT_80439fe0;
  if ((*(uint *)(iVar6 + 0x5e0) & 0x20001000) == 0) {
    fVar3 = *(float *)(param_1 + 0x144) - *(float *)(iVar6 + 0x1dc8);
    *(float *)(param_1 + 0x144) = fVar3;
    if (fVar3 <= fVar4) {
      psVar7 = *(short **)(param_1 + 0x148);
      if (*psVar7 < 0) {
        psVar7 = psVar7 + *psVar7 * 2;
      }
      *(float *)(param_1 + 0x144) =
           (float)((double)CONCAT44(0x43300000,(int)*psVar7 ^ 0x80000000) - DOUBLE_80439fe8);
      *(char *)(param_1 + 0x151) = (char)psVar7[1];
      *(short **)(param_1 + 0x148) = psVar7 + 2;
      *(undefined2 *)(param_1 + 0x14c) =
           *(undefined2 *)
            (*(char *)(param_1 + 0x151) * 0x14 + -0x7fcc6f44 + *(char *)(param_1 + 0x13) * 4);
      *(undefined2 *)(param_1 + 0x14e) =
           *(undefined2 *)
            (*(char *)(param_1 + 0x151) * 0x14 + *(char *)(param_1 + 0x13) * 4 + -0x7fcc6f42);
    }
    if ((*(byte *)(param_1 + 0x84) & 2) == 0) {
      psVar7 = (short *)(param_1 + 0x74);
    }
    else {
      psVar7 = (short *)(param_1 + 0x70);
    }
    sVar2 = *(short *)(param_1 + 0x14e);
    sVar5 = (short)(int)(*(float *)(iVar6 + 0x1dc8) *
                        (float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x14c) - (int)*psVar7 ^
                                                 0x80000000) - DOUBLE_80439fe8));
    if ((int)sVar2 < (int)sVar5) {
      sVar5 = sVar2;
    }
    iVar6 = -(int)sVar2;
    if (sVar5 < iVar6) {
      sVar5 = (short)iVar6;
    }
    *psVar7 = *psVar7 + sVar5;
  }
  return;
}



// ==== 80137120  FUN_80137120 ====

void FUN_80137120(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80137140  FUN_80137140 ====

void FUN_80137140(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = *(int *)(param_9 + 0x90);
  uVar3 = FUN_80047aa4(param_9);
  if ((*(char *)(iVar2 + 0xae) == '\0') && (*(char *)(iVar2 + 0x3ec) != '\x04')) {
    iVar2 = 0;
    uVar1 = 1;
  }
  else {
    iVar2 = 1;
    uVar1 = 0x44;
  }
  iVar2 = *(int *)(param_9 + iVar2 * 4 + 0xe0);
  zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 801371d0  zz_01371d0_ ====

void zz_01371d0_(int param_1,undefined4 *param_2)

{
  float fVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0x18;
    fVar1 = FLOAT_80439ff0;
    puVar2[0x11] = 0;
    *(code **)(puVar2 + 0xc) = FUN_801372f0;
    *(code **)(puVar2 + 0x10c) = FUN_80137500;
    *(undefined4 *)(puVar2 + 0x20) = *param_2;
    *(float *)(puVar2 + 0x24) = fVar1 + (float)param_2[1];
    *(undefined4 *)(puVar2 + 0x28) = param_2[2];
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



// ==== 801372f0  FUN_801372f0 ====

void FUN_801372f0(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') && ('\x01' < *(char *)(*(int *)(param_1 + 0x8c) + 0x18)))
  {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_803391b8)[*(char *)(param_1 + 0x18)])();
  return;
}



