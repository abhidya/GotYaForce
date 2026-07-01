// ==== 800c93a0  FUN_800c93a0 ====

void FUN_800c93a0(int param_1)

{
  double dVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined1 *)(param_1 + 0x6ee) = 0;
    dVar1 = DOUBLE_80438890;
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar1) * FLOAT_80438888);
  }
  return;
}



// ==== 800c93fc  FUN_800c93fc ====

void FUN_800c93fc(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x6e9);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    sVar2 = *(short *)(param_1 + 1000);
    if (sVar2 == 0x600) {
      zz_001ab6c_(param_1,0x1f);
    }
    else if (sVar2 == 0x608) {
      zz_001ab6c_(param_1,0x60);
    }
    else if (sVar2 == 0x616) {
      zz_001ab6c_(param_1,0x61);
    }
    else if (sVar2 == 0x61c) {
      zz_001ab6c_(param_1,0x62);
    }
  }
  *(undefined1 *)(param_1 + 0x6e9) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined1 *)(param_1 + 0x1d94) = 1;
  }
  return;
}



// ==== 800c94d4  FUN_800c94d4 ====

void FUN_800c94d4(int param_1)

{
  (*(code *)(&PTR_FUN_8030a558)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800c9510  FUN_800c9510 ====

void FUN_800c9510(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80438890) * FLOAT_80438898);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8030a564)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c9590  FUN_800c9590 ====

void FUN_800c9590(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030a578)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c95d8  FUN_800c95d8 ====

void FUN_800c95d8(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043889c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0xc1,0);
  zz_004beb8_((double)FLOAT_804388a0,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  fVar1 = FLOAT_804388a4;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804388a4;
  return;
}



// ==== 800c96c0  FUN_800c96c0 ====

/* WARNING: Removing unreachable block (ram,0x800c97a0) */
/* WARNING: Removing unreachable block (ram,0x800c96d0) */

void FUN_800c96c0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804388a4;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804388a4;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800c9f40(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804388ac < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800c97bc  FUN_800c97bc ====

void FUN_800c97bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
    *(undefined1 *)(param_9 + 0x745) = 1;
  }
  zz_004cd24_(param_9,0xf);
  if (*(float *)(param_9 + 0x558) <= FLOAT_804388a4) {
    if (*(char *)(param_9 + 0x745) != '\0') {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        *(undefined1 *)(param_9 + 0x745) = 0;
        if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_9,'\0',3,0);
          return;
        }
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        if (*(char *)(param_9 + 0x1cef) < '\0') {
          zz_004beb8_((double)FLOAT_804388a0,param_9,0xf,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_804388a0,param_9,0xf,2,1,4,1);
        return;
      }
      goto LAB_800c98f0;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = *(float *)(param_9 + 0x558) - *(float *)(param_9 + 0x1dc8);
  }
  if ((((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_9 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_9 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
    zz_00679d0_(param_9);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
    if (dVar2 <= (double)FLOAT_804388ac) {
      return;
    }
    zz_00b22f4_(param_9);
    return;
  }
LAB_800c98f0:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  dVar2 = (double)zz_006a474_(param_9);
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,param_11,
              param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  return;
}



// ==== 800c997c  FUN_800c997c ====

void FUN_800c997c(int param_1)

{
  (*(code *)(&PTR_FUN_8030a584)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c99b8  FUN_800c99b8 ====

void FUN_800c99b8(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  fVar1 = FLOAT_804388b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  uVar2 = *(uint *)(param_1 + 0x5e0);
  iVar3 = 4;
  if ((uVar2 & 0x80) != 0) {
    iVar3 = 6;
  }
  if ((uVar2 & 0x10) != 0) {
    iVar3 = 2;
  }
  if (((uVar2 & 0x20) != 0) &&
     (iVar3 = *(char *)(param_1 + 0x1d10) + 8, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar3 = 0;
  }
  zz_004beb8_((double)FLOAT_804388a0,param_1,1,2,iVar3 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 800c9a70  FUN_800c9a70 ====

void FUN_800c9a70(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_804388a4;
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
      FUN_800c9f40(param_1);
    }
  }
  return;
}



// ==== 800c9b4c  FUN_800c9b4c ====

void FUN_800c9b4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
    *(undefined1 *)(param_9 + 0x745) = 1;
  }
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804388a4) {
    if (*(char *)(param_9 + 0x745) != '\0') {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(undefined1 *)(param_9 + 0x745) = 0;
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((uVar2 & 0x10) == 0) {
            if ((uVar2 & 0x20) == 0) {
              zz_006a3d0_(param_9,'\0',0,2);
              return;
            }
            *(undefined1 *)(param_9 + 0x581) = 2;
            iVar1 = *(char *)(param_9 + 0x1d10) + 9;
            if (*(char *)(param_9 + 0x5db) == '\x0f') {
              iVar1 = 1;
            }
          }
          else {
            iVar1 = 3;
            *(undefined1 *)(param_9 + 0x581) = 1;
          }
        }
        else {
          iVar1 = 5;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 7;
          }
        }
        if ((*(char *)(param_9 + 0x1cef) < '\0') &&
           (iVar1 == (int)*(char *)(param_9 + 0x1afd) + *(char *)(param_9 + 0x1afc) * 0x1000)) {
          zz_004beb8_((double)FLOAT_804388a0,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_804388a0,param_9,1,2,iVar1,4,1);
        return;
      }
      goto LAB_800c9d08;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800c9d08:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,param_11,
              param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  return;
}



// ==== 800c9d44  FUN_800c9d44 ====

void FUN_800c9d44(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030a590)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c9d8c  FUN_800c9d8c ====

void FUN_800c9d8c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043889c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804388a0,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  zz_004beb8_((double)FLOAT_804388a0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804388a4;
  return;
}



// ==== 800c9e44  FUN_800c9e44 ====

/* WARNING: Removing unreachable block (ram,0x800c9f24) */
/* WARNING: Removing unreachable block (ram,0x800c9e54) */

void FUN_800c9e44(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804388a4;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (((fVar1 <= fVar2) || (iVar3 = zz_006d0dc_(param_1,0x81,0), iVar3 != 0)) &&
     (*(char *)(param_1 + 0x1cef) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800c9f40(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  if (FLOAT_804388ac < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800c9f40  FUN_800c9f40 ====

void FUN_800c9f40(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_804388b8;
  *(float *)(param_1 + 0x560) = FLOAT_804388b0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x600) {
      zz_00c3be0_(param_1,0x15);
    }
    else if (sVar1 == 0x608) {
      zz_00c3be0_(param_1,0x33);
      zz_00c3be0_(param_1,0x34);
    }
    else if (sVar1 == 0x616) {
      zz_00c3be0_(param_1,0x3e);
    }
    else if (sVar1 == 0x61c) {
      zz_00c3be0_(param_1,0x3f);
      zz_00c3be0_(param_1,0x40);
    }
    else {
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
  }
  if (*(short *)(param_1 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x6ef) = 0;
  }
  return;
}



// ==== 800ca034  FUN_800ca034 ====

void FUN_800ca034(int param_1)

{
  (*(code *)(&PTR_FUN_8030a59c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ca070  FUN_800ca070 ====

void FUN_800ca070(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030a5b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ca0cc  FUN_800ca0cc ====

void FUN_800ca0cc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar3 = FLOAT_804388bc;
  fVar2 = FLOAT_804388a4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
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
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_804388a0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800ca218  FUN_800ca218 ====

void FUN_800ca218(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804388b0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800ca2e0  FUN_800ca2e0 ====

void FUN_800ca2e0(int param_1)

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
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804388c0 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_804388b4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804388c0 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_804388c4,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_804388c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar1;
  }
  return;
}



// ==== 800ca3f0  FUN_800ca3f0 ====

void FUN_800ca3f0(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_804388b0;
  if (((char)*(byte *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    if ((*(byte *)(param_1 + 0x1cf0) & 1) != 0) {
      dVar4 = (double)FLOAT_804388a0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      *(undefined1 *)(param_1 + 0x746) = 0;
      *(undefined1 *)(param_1 + 0x745) = 0;
      *(float *)(param_1 + 0x558) = fVar2;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      zz_0092dcc_(param_1,0);
      return;
    }
    *(undefined1 *)(param_1 + 0x581) = 3;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    zz_006a3d0_(param_1,'\x01',2,0);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_804388a8,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804388b4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800ca5dc  FUN_800ca5dc ====

void FUN_800ca5dc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030a5c4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ca638  FUN_800ca638 ====

void FUN_800ca638(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_804388bc;
  fVar2 = FLOAT_804388a4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 1;
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
  dVar5 = (double)FLOAT_804388a0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800ca71c  FUN_800ca71c ====

void FUN_800ca71c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_804388b0;
    fVar1 = FLOAT_804388a4;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x80c) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_804388a8,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 800ca7fc  FUN_800ca7fc ====

void FUN_800ca7fc(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_804388b0;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_804388cc,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800ca8b4  FUN_800ca8b4 ====

void FUN_800ca8b4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_804388d0;
  fVar1 = FLOAT_804388b0;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_804388d4;
    *(float *)(param_1 + 0x44) = fVar1;
    fVar1 = FLOAT_804388d8;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar1;
    zz_0066530_(param_1,0x2d);
    zz_00b2190_(param_1,0);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800ca954  FUN_800ca954 ====

void FUN_800ca954(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x1d10) = 0;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_804388b0;
  fVar2 = FLOAT_804388a4;
  if (FLOAT_804388a4 <= *(float *)(param_1 + 0x48)) {
    if ((*(char *)(param_1 + 0x1cee) != '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
      dVar4 = (double)FLOAT_804388a0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar3;
      *(undefined2 *)(param_1 + 0x54e) = 0;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x50) = fVar2;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      zz_0092dcc_(param_1,0);
    }
  }
  else {
    *(float *)(param_1 + 0x44) = FLOAT_804388a4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800caa94  FUN_800caa94 ====

/* WARNING: Removing unreachable block (ram,0x800cab94) */
/* WARNING: Removing unreachable block (ram,0x800caaa4) */

void FUN_800caa94(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar6 = (double)((FLOAT_804388dc * *(float *)(param_1 + 0x760)) / FLOAT_804388b0);
  if ((double)FLOAT_804388bc < dVar6) {
    dVar6 = (double)FLOAT_804388bc;
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar6 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_804388b4;
  *(float *)(param_1 + 0x48) = (float)(dVar6 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_804388cc,param_1), uVar3 != 0)) {
    fVar1 = FLOAT_8043889c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800cabb0  FUN_800cabb0 ====

void FUN_800cabb0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80438888,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = FLOAT_8043889c;
  if (iVar3 == 0) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar1;
      if (fVar1 <= fVar2) {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
      }
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar1;
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    zz_0066530_(param_1,0x2c);
  }
  return;
}



// ==== 800caca0  FUN_800caca0 ====

void FUN_800caca0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0066530_(param_1,0x2c);
  }
  return;
}



// ==== 800cad54  FUN_800cad54 ====

void FUN_800cad54(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_804388a8,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    zz_00b22f4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800caddc  FUN_800caddc ====

void FUN_800caddc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030a5e8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cae2c  FUN_800cae2c ====

void FUN_800cae2c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_804388bc;
  if ((*(uint *)(param_1 + 0x5e0) & 0x2000) == 0) {
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
    gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00677b0_(param_1);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar4 = (double)FLOAT_804388a0;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 5;
    FUN_800ca070(param_1);
  }
  return;
}



// ==== 800caf60  FUN_800caf60 ====

void FUN_800caf60(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804388b0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800cb02c  FUN_800cb02c ====

void FUN_800cb02c(int param_1)

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
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804388c0 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar6 = (double)FLOAT_804388b4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804388c0 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_804388a4;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_800668cc((double)FLOAT_804388e0,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_804388e4;
    dVar5 = (double)FLOAT_804388a0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800cb130  FUN_800cb130 ====

void FUN_800cb130(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  zz_006ed8c_((double)FLOAT_804388e8,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  fVar3 = FLOAT_804388b0;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804388c0 * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804388c0 * -dVar4);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800cb218  FUN_800cb218 ====

void FUN_800cb218(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar2 = FLOAT_804388a4;
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      zz_004cd24_(param_1,0xf);
    }
  }
  else {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_804388a4;
  fVar2 = FLOAT_8043889c;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x558) = FLOAT_804388a4;
    fVar3 = FLOAT_804388ec;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  }
  zz_006ed8c_((double)FLOAT_804388f0,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438890) * FLOAT_80438888);
  }
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804388b4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800cb394  FUN_800cb394 ====

void FUN_800cb394(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 800cb3c8  FUN_800cb3c8 ====

void FUN_800cb3c8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if ((*(short *)(param_1 + 1000) == 0x616) || (*(short *)(param_1 + 1000) == 0x61c)) {
    zz_0177dd8_(param_1);
  }
  else {
    zz_0177dd8_(param_1);
  }
  return;
}



// ==== 800cb424  FUN_800cb424 ====

void FUN_800cb424(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030a644)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cb480  FUN_800cb480 ====

void FUN_800cb480(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_804388bc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 6;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_804388a0;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800cb5a8  FUN_800cb5a8 ====

void FUN_800cb5a8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_804388a8,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_804388b0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800cb674  FUN_800cb674 ====

void FUN_800cb674(int param_1)

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
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804388f4 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_804388b4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804388f4 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_804388c4,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_804388b8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 800cb758  FUN_800cb758 ====

void FUN_800cb758(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  zz_006ed8c_((double)FLOAT_804388e8,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804388a4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  fVar3 = FLOAT_804388b0;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804388f4 * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804388f4 * -dVar4);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800cb840  FUN_800cb840 ====

void FUN_800cb840(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar3 = FLOAT_804388a4;
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar3) {
      zz_004cd24_(param_1,0xf);
    }
    if ((*(char *)(param_1 + 0x746) != '\0') && (*(char *)(param_1 + 0x745) != '\0')) {
      *(undefined1 *)(param_1 + 0x581) = 3;
      zz_006a3d0_(param_1,'\x01',2,0);
      return;
    }
  }
  else {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_804388f8;
  fVar3 = FLOAT_804388a4;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x558) = FLOAT_804388a4;
    fVar2 = FLOAT_8043889c;
    *(float *)(param_1 + 0x44) = fVar1;
    fVar1 = FLOAT_804388ec;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_006ed8c_((double)FLOAT_804388f0,param_1);
  FUN_80067310((double)FLOAT_804388b4,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804388b4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800cb9d4  FUN_800cb9d4 ====

void FUN_800cb9d4(int param_1)

{
  (*(code *)(&PTR_FUN_8030a658)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cba10  FUN_800cba10 ====

void FUN_800cba10(int param_1)

{
  zz_0179d20_(param_1);
  return;
}



// ==== 800cba38  FUN_800cba38 ====

void FUN_800cba38(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dbe0_(param_1,2,1,1);
  if (iVar4 == 0) {
    *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
  }
  else {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x600) {
      zz_016cc24_(param_1,0);
    }
    else if (sVar1 == 0x608) {
      zz_016cc24_(param_1,0xc);
    }
    else if (sVar1 == 0x616) {
      zz_016cc24_(param_1,0xd);
    }
    else if (sVar1 == 0x61c) {
      zz_016cc24_(param_1,0xe);
    }
  }
  fVar3 = FLOAT_804388fc;
  fVar2 = FLOAT_804388a4;
  *(float *)(param_1 + 0x4c) = FLOAT_804388a4;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x48) = fVar3;
  *(float *)(param_1 + 0x50) = fVar2;
  return;
}



// ==== 800cbb00  zz_00cbb00_ ====

void zz_00cbb00_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x304) || (*(short *)(param_1 + 1000) == 0x308)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800cbc10;
    *(code **)(puVar1 + 0x10c) = FUN_800cbe20;
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



// ==== 800cbc10  FUN_800cbc10 ====

void FUN_800cbc10(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8030a69c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800cbc64  FUN_800cbc64 ====

void FUN_800cbc64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80438900;
  *(float *)(param_9 + 0xb4) = FLOAT_80438900;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80433b40 + *(char *)(param_9 + 0x11) * 2),iVar4 + 0xc28,
                      in_r7,in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = (int)*(short *)(&DAT_80433b40 + *(char *)(param_9 + 0x11) * 2);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438904,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00cbd58_(param_9);
  return;
}



// ==== 800cbd58  zz_00cbd58_ ====

void zz_00cbd58_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = 1;
  if ((*(char *)(*(int *)(param_1 + 0x90) + 0x144) == '\x01') &&
     (*(char *)(*(int *)(param_1 + 0x90) + 0x145) == '\x03')) {
    iVar2 = 0;
  }
  *(undefined *)(param_1 + 0x89) = (&DAT_80433b44)[iVar2];
  uVar1 = (&DAT_8030a67c)[iVar2 * 3];
  *(undefined4 *)(param_1 + 100) = (&DAT_8030a678)[iVar2 * 3];
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = (&DAT_8030a680)[iVar2 * 3];
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)((int)&DAT_8030a690 + iVar2 * 6);
  *(undefined2 *)(param_1 + 0x74) = (&DAT_8030a694)[iVar2 * 3];
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x84) = 0x49;
    return;
  }
  *(undefined1 *)(param_1 + 0x84) = 0x4b;
  return;
}



// ==== 800cbe00  FUN_800cbe00 ====

void FUN_800cbe00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800cbe20  FUN_800cbe20 ====

void FUN_800cbe20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  
  puVar1 = (undefined *)0x0;
  uVar2 = 1;
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) != '\0') ||
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04')) {
    puVar1 = (undefined *)0x1;
    uVar2 = 0x44;
  }
  iVar3 = *(int *)(param_9 + (int)puVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),puVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar3,uVar2);
  return;
}



// ==== 800cbe9c  zz_00cbe9c_ ====

void zz_00cbe9c_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x207) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800cbf90;
    *(code **)(puVar1 + 0x10c) = FUN_800cc318;
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



// ==== 800cbf90  FUN_800cbf90 ====

void FUN_800cbf90(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8030a6b0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800cbfe4  FUN_800cbfe4 ====

void FUN_800cbfe4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x49;
  fVar1 = FLOAT_80438908;
  *(undefined1 *)(param_9 + 0x89) = 0xb;
  fVar2 = FLOAT_8043890c;
  dVar6 = (double)FLOAT_8043890c;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_80438910;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined2 *)(param_9 + 0x74) = 0xc000;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar7 = zz_0007030_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),3,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),4,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe8),3,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  uVar3 = 4;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xec),4,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  uVar7 = zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe8),extraout_r4,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438914,*(int *)(param_9 + 0xe8));
  uVar7 = zz_0007cac_((double)FLOAT_80438914,*(int *)(param_9 + 0xec));
  *(undefined4 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x148) = 0xff;
  uVar7 = FUN_800cc270(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,'\0',
                       uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  iVar5 = zz_008ac80_(param_9,8);
  if (iVar5 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    iVar5 = *(byte *)(param_9 + 0x96) + 0x41;
    *(char *)(param_9 + 0x82) = (char)iVar5;
    *(undefined2 *)(param_9 + 0x1c6) = 10000;
    *(undefined2 *)(param_9 + 0x1c8) = 10000;
    *(undefined2 *)(param_9 + 0x1c4) = 10000;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 2;
    zz_00cc180_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar5,uVar3,
                iVar4,in_r7,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 800cc180  zz_00cc180_ ====

void zz_00cc180_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0) ||
     ((*(uint *)(iVar1 + 0x5e0) & 0x10000000) != 0)) {
    *(undefined2 *)(param_9 + 0x272) = *(undefined2 *)(iVar1 + 0x272);
  }
  else {
    *(undefined2 *)(param_9 + 0x272) = 0xffff;
  }
  FUN_800cc270(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
               '\0' < *(char *)(iVar1 + 0x171),param_11,param_12,param_13,param_14,param_15,param_16
              );
  *(int *)(param_9 + 0x144) = *(int *)(param_9 + 0x144) + 0x400;
  *(uint *)(param_9 + 0x144) = *(uint *)(param_9 + 0x144) & 0x1ffff;
  *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(iVar1 + 0xc0);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  return;
}



// ==== 800cc224  FUN_800cc224 ====

void FUN_800cc224(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 800cc250  FUN_800cc250 ====

void FUN_800cc250(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800cc270  FUN_800cc270 ====

/* WARNING: Removing unreachable block (ram,0x800cc2f8) */
/* WARNING: Removing unreachable block (ram,0x800cc280) */

void FUN_800cc270(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,char param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar2;
  undefined8 uVar3;
  double dVar4;
  
  if (*(char *)(param_9 + 0x148) != param_10) {
    iVar1 = zz_0006f98_(param_9);
    *(char *)(param_9 + 0x148) = param_10;
    pfVar2 = (float *)&DAT_80433b48;
    dVar4 = (double)*(float *)(&DAT_80433b48 + *(char *)(param_9 + 0x148) * 4);
    uVar3 = zz_00086b8_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe0),&DAT_80433b48,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,param_15,
                param_16);
    uVar3 = zz_00086b8_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe4),pfVar2,param_12,param_13,
                        param_14,param_15,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4_00,pfVar2,param_12,param_13,param_14,param_15,
                param_16);
  }
  return;
}



// ==== 800cc318  FUN_800cc318 ====

void FUN_800cc318(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  float local_7c;
  float local_78;
  float local_74;
  float afStack_70 [12];
  float afStack_40 [13];
  
  uVar1 = countLeadingZeros((int)*(char *)(*(int *)(param_9 + 0x90) + 0xae));
  uVar1 = ~-(uVar1 >> 5 & 1) & 2;
  iVar3 = param_9 + uVar1 * 4;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xe0)
              ,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar3 + 0xe0),0x45);
  zz_0046470_((float *)(param_9 + 0x114),&local_7c);
  local_88 = *(float *)(param_9 + 0x120);
  local_84 = *(undefined4 *)(param_9 + 0x130);
  local_80 = *(undefined4 *)(param_9 + 0x140);
  zz_004844c_(afStack_40,&local_88,5);
  iVar3 = *(int *)(param_9 + 0x144);
  if (0xffff < iVar3) {
    iVar3 = 0;
  }
  dVar4 = zz_0045204_((short)iVar3);
  if (dVar4 < (double)FLOAT_8043890c) {
    dVar4 = -dVar4;
  }
  gnt4_PSQUATScale_bl((double)(float)(DOUBLE_80438920 * dVar4 + DOUBLE_80438918),&local_7c,&local_7c
                     );
  dVar4 = (double)local_78;
  dVar6 = (double)local_74;
  gnt4_PSMTXScale_bl((double)local_7c,dVar4,dVar6,afStack_70);
  pfVar2 = afStack_40;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar2,afStack_70,pfVar2);
  iVar3 = param_9 + (uVar1 + 1) * 4;
  zz_00076d0_(uVar5,dVar4,dVar6,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xe0),
              afStack_40,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar3 + 0xe0),0x45);
  return;
}



// ==== 800cc550  FUN_800cc550 ====

void FUN_800cc550(int param_1)

{
  short sVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x4a8) = 1;
  zz_00c74ec_(param_1,0x1b);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x602) {
    iVar2 = 4;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 7);
  }
  else if (sVar1 == 0x60a) {
    iVar2 = 9;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xc);
  }
  else if (sVar1 == 0x60c) {
    iVar2 = 0xc;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0xf);
  }
  else if (sVar1 == 0x60e) {
    iVar2 = 0xf;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x12);
  }
  return;
}



// ==== 800cc630  FUN_800cc630 ====

void FUN_800cc630(int param_1)

{
  double dVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined1 *)(param_1 + 0x6ee) = 0;
    dVar1 = DOUBLE_80438930;
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar1) * FLOAT_80438928);
  }
  return;
}



// ==== 800cc6bc  FUN_800cc6bc ====

void FUN_800cc6bc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8030cd08)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800cc6fc  FUN_800cc6fc ====

void FUN_800cc6fc(int param_1)

{
  float local_18;
  float local_14;
  float local_10;
  
  zz_00b2190_(param_1,2);
  local_18 = FLOAT_80438938;
  local_14 = FLOAT_80438938;
  local_10 = FLOAT_8043893c;
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),&local_18,&local_18);
  zz_0085e00_(param_1,&local_18,0xf);
  return;
}



// ==== 800cc760  FUN_800cc760 ====

void FUN_800cc760(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x22);
  return;
}



// ==== 800cc798  FUN_800cc798 ====

void FUN_800cc798(int param_1)

{
  (*(code *)(&PTR_FUN_8030cd18)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800cc7d4  FUN_800cc7d4 ====

void FUN_800cc7d4(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80438930) * FLOAT_80438928);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8030cd28)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cc854  FUN_800cc854 ====

void FUN_800cc854(int param_1)

{
  (*(code *)(&PTR_FUN_8030cd3c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cc890  FUN_800cc890 ====

void FUN_800cc890(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar2 = zz_00cd3ec_(param_1);
  zz_004beb8_((double)FLOAT_80438940,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_004beb8_((double)FLOAT_80438940,param_1,2,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x560) = FLOAT_80438944;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_00cd18c_(param_1);
  fVar1 = FLOAT_80438938;
  *(float *)(param_1 + 0x50) = FLOAT_80438938;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438948,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80438938;
  return;
}



// ==== 800cc99c  FUN_800cc99c ====

/* WARNING: Removing unreachable block (ram,0x800cca94) */
/* WARNING: Removing unreachable block (ram,0x800cc9ac) */

void FUN_800cc99c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006dee8_(param_1,1);
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80438938;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  fVar2 = FLOAT_80438938;
  if (iVar3 < 0) {
    zz_006d0dc_(param_1,0xc1,0);
  }
  else if (((0 < iVar3) ||
           (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
           *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
          (*(char *)(param_1 + 0x1cef) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800cd1a0(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438948,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043894c < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ccab4  FUN_800ccab4 ====

void FUN_800ccab4(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_80438938) {
    if (((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) ||
       ((*(char *)(param_1 + 0x1cef) < '\0' && ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0)))) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if (iVar1 != 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        iVar1 = zz_00cd3ec_(param_1);
        zz_004beb8_((double)FLOAT_80438940,param_1,1,2,iVar1 + 1,0xffffffff,0xffffffff);
        zz_004beb8_((double)FLOAT_80438940,param_1,2,2,1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_800ccbdc;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438948,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_8043894c) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_800ccbdc:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800ccc54  FUN_800ccc54 ====

void FUN_800ccc54(int param_1)

{
  (*(code *)(&PTR_FUN_8030cd48)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ccc90  FUN_800ccc90 ====

void FUN_800ccc90(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar1 = zz_00cd3ec_(param_1);
  zz_004beb8_((double)FLOAT_80438940,param_1,1,2,iVar1 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_00cd18c_(param_1);
  return;
}



// ==== 800cccfc  FUN_800cccfc ====

void FUN_800cccfc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80438938;
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
      FUN_800cd1a0(param_1);
    }
  }
  return;
}



// ==== 800ccdcc  FUN_800ccdcc ====

void FUN_800ccdcc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_80438938) {
    if (((*(uint *)(param_9 + 0x5bc) & 0x200) != 0) ||
       ((*(char *)(param_9 + 0x1cef) < '\0' && ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0)))) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        iVar1 = zz_00cd3ec_(param_9);
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          dVar3 = (double)FLOAT_80438940;
          *(undefined1 *)(param_9 + 0x581) = 3;
          zz_004beb8_(dVar3,param_9,1,2,iVar1 + 1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_80438940;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,iVar1 + 1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          dVar3 = (double)FLOAT_80438940;
          *(undefined1 *)(param_9 + 0x581) = 2;
          zz_004beb8_(dVar3,param_9,1,2,iVar1 + 1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_800ccf44;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800ccf44:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ccf78  FUN_800ccf78 ====

void FUN_800ccf78(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030cd54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ccfc0  FUN_800ccfc0 ====

void FUN_800ccfc0(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_80438950;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar1 = zz_00cd3ec_(param_1);
  zz_004beb8_((double)FLOAT_80438940,param_1,1,2,iVar1 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80438940,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_00cd18c_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80438938;
  return;
}



// ==== 800cd0a0  FUN_800cd0a0 ====

/* WARNING: Removing unreachable block (ram,0x800cd170) */
/* WARNING: Removing unreachable block (ram,0x800cd0b0) */

void FUN_800cd0a0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80438938;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_80438950,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_80438938;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800cd1a0(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800cd18c  zz_00cd18c_ ====

void zz_00cd18c_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80438958;
  *(float *)(param_1 + 0x560) = FLOAT_80438954;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 800cd1a0  FUN_800cd1a0 ====

/* WARNING: Removing unreachable block (ram,0x800cd3cc) */
/* WARNING: Removing unreachable block (ram,0x800cd1b0) */

void FUN_800cd1a0(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_80438958;
  *(float *)(param_1 + 0x560) = FLOAT_80438954;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(undefined2 *)(param_1 + 0x1900) = 0;
  zz_0046698_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    local_28 = *(float *)(param_1 + 0xa24);
    dVar5 = (double)*(float *)(param_1 + 0xa34);
    local_20 = *(undefined4 *)(param_1 + 0xa44);
    local_24 = FLOAT_80438938;
    dVar6 = gnt4_PSVECMag_bl(&local_28);
    iVar3 = FUN_800452a0(dVar5,dVar6);
    local_28 = *(float *)(param_1 + 0xa30);
    local_24 = *(float *)(param_1 + 0xa40);
    local_20 = *(undefined4 *)(param_1 + 0xa50);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
    dVar6 = (double)local_24;
    local_24 = FLOAT_80438938;
    dVar5 = gnt4_PSVECMag_bl(&local_28);
    iVar4 = FUN_800452a0(dVar6,dVar5);
    *(short *)(param_1 + 0x1900) = (short)iVar3 + (short)iVar4;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                (float *)(param_1 + 0x1628));
  }
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x602) {
      zz_00c3be0_(param_1,0x16);
      zz_00c3be0_(param_1,0x17);
      zz_00c3be0_(param_1,0x18);
    }
    else if (sVar1 == 0x60a) {
      zz_00c3be0_(param_1,0x69);
      zz_00c3be0_(param_1,0x6a);
      zz_00c3be0_(param_1,0x6b);
      zz_00c3be0_(param_1,0x6c);
      zz_00c3be0_(param_1,0x6d);
      zz_00c3be0_(param_1,0x6e);
    }
    else if (sVar1 == 0x60c) {
      zz_00c3be0_(param_1,0x6f);
      zz_00c3be0_(param_1,0x70);
      zz_00c3be0_(param_1,0x71);
      zz_00c3be0_(param_1,0x72);
      zz_00c3be0_(param_1,0x73);
    }
    else if (sVar1 == 0x60e) {
      zz_00c3be0_(param_1,0x74);
      zz_00c3be0_(param_1,0x75);
      zz_00c3be0_(param_1,0x76);
      zz_00c3be0_(param_1,0x77);
    }
  }
  return;
}



// ==== 800cd3ec  zz_00cd3ec_ ====

/* WARNING: Removing unreachable block (ram,0x800cd4b4) */
/* WARNING: Removing unreachable block (ram,0x800cd3fc) */

undefined4 zz_00cd3ec_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  double dVar3;
  double in_f31;
  double dVar4;
  double in_ps31_1;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_38 = *(float *)(param_1 + 0x970);
  local_34 = *(float *)(param_1 + 0x980);
  local_30 = *(undefined4 *)(param_1 + 0x990);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_38,&local_38);
  dVar4 = (double)local_34;
  local_34 = FLOAT_80438938;
  dVar3 = gnt4_PSVECMag_bl(&local_38);
  iVar1 = FUN_800452a0(dVar4,dVar3);
  uVar2 = 2;
  if (DOUBLE_80438960 <
      (double)CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000) - DOUBLE_80438930) {
    uVar2 = 0;
  }
  if ((double)CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000) - DOUBLE_80438930 <
      DOUBLE_80438968) {
    uVar2 = 6;
  }
  return uVar2;
}



// ==== 800cd4cc  FUN_800cd4cc ====

void FUN_800cd4cc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8030cd60)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cd514  FUN_800cd514 ====

void FUN_800cd514(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030cd74)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cd564  FUN_800cd564 ====

void FUN_800cd564(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_80438970;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80438940;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(undefined1 *)(param_1 + 0x1d9b) = 0;
  return;
}



// ==== 800cd644  FUN_800cd644 ====

void FUN_800cd644(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80438938;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    }
    *(float *)(param_1 + 0x558) = FLOAT_80438954;
    fVar2 = FLOAT_80438938;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438954;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    if (FLOAT_80438974 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800cd768  FUN_800cd768 ====

void FUN_800cd768(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80438938;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80438974,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6eb) = 6;
    *(undefined1 *)(param_1 + 0x1d9b) = 1;
  }
  else {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  return;
}



// ==== 800cd810  FUN_800cd810 ====

/* WARNING: Removing unreachable block (ram,0x800cd880) */
/* WARNING: Removing unreachable block (ram,0x800cd820) */

void FUN_800cd810(int param_1)

{
  float fVar1;
  char cVar2;
  double dVar3;
  
  dVar3 = (double)*(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_80438978);
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  zz_006d144_(param_1,0xc0);
  cVar2 = *(char *)(param_1 + 0x6eb) + -1;
  *(char *)(param_1 + 0x6eb) = cVar2;
  fVar1 = FLOAT_80438938;
  if (cVar2 < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 800cd89c  FUN_800cd89c ====

/* WARNING: Removing unreachable block (ram,0x800cd96c) */
/* WARNING: Removing unreachable block (ram,0x800cd8ac) */

void FUN_800cd89c(int param_1)

{
  double dVar1;
  uint uVar2;
  double dVar3;
  
  zz_006d144_(param_1,0xc0);
  uVar2 = FUN_80066838((double)FLOAT_80438988,param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x1d9b) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  dVar1 = DOUBLE_80438990;
  if ((*(float *)(param_1 + 0x558) <= FLOAT_80438938) || (*(int *)(param_1 + 0xcc) == 0)) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    dVar3 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * dVar1);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800cd988  FUN_800cd988 ====

void FUN_800cd988(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030cd88)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cd9d8  FUN_800cd9d8 ====

void FUN_800cd9d8(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80438970;
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80438948,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_004beb8_((double)FLOAT_80438940,param_1,0xf,3,1,0xffffffff,0xffffffff);
  return;
}



// ==== 800cdab4  FUN_800cdab4 ====

void FUN_800cdab4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80438938;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80438954;
    fVar1 = FLOAT_80438938;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x80c) = fVar1;
  }
  else {
    zz_006ed8c_((double)FLOAT_80438998,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800cdb88  FUN_800cdb88 ====

void FUN_800cdb88(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800cdbf8  FUN_800cdbf8 ====

void FUN_800cdbf8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030cd94)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cdc48  FUN_800cdc48 ====

void FUN_800cdc48(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80438970;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_004beb8_((double)FLOAT_80438940,param_1,0xf,3,0,0xffffffff,0xffffffff);
  FUN_800cdd1c(param_1);
  return;
}



// ==== 800cdd1c  FUN_800cdd1c ====

void FUN_800cdd1c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438948,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80438938;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80438954;
    fVar1 = FLOAT_80438938;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 800cddf0  FUN_800cddf0 ====

void FUN_800cddf0(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043899c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_80438950;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043899c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80438938;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80438988,param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_80438990;
    fVar1 = FLOAT_80438980;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6ea) = 0x10;
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar4);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar4);
  }
  return;
}



// ==== 800cdf20  FUN_800cdf20 ====

/* WARNING: Removing unreachable block (ram,0x800cdfe4) */
/* WARNING: Removing unreachable block (ram,0x800cdf30) */

void FUN_800cdf20(int param_1)

{
  char cVar1;
  double dVar2;
  double dVar3;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(float *)(param_1 + 0x558) <= FLOAT_80438938)) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar2 = (double)FLOAT_80438984;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    dVar3 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * dVar2);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  zz_0067458_((double)FLOAT_80438950,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea) + -1;
  *(char *)(param_1 + 0x6ea) = cVar1;
  if (cVar1 < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800ce000  FUN_800ce000 ====

void FUN_800ce000(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80438938;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804389a0 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804389a0 * -dVar3);
  }
  zz_006ed8c_((double)FLOAT_80438948,param_1);
  FUN_80067310((double)FLOAT_80438950,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438950 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800ce138  FUN_800ce138 ====

void FUN_800ce138(int param_1)

{
  *(undefined1 *)(param_1 + 0x594) = 2;
  *(undefined1 *)(*(int *)(param_1 + 0x4a4) + 0x594) = 2;
  (*(code *)(&PTR_FUN_8030cda8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ce184  FUN_800ce184 ====

void FUN_800ce184(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030cdbc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ce1d4  FUN_800ce1d4 ====

void FUN_800ce1d4(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438970;
  fVar1 = FLOAT_80438938;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0x3c;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  FUN_800ce534(param_1);
  zz_004beb8_((double)FLOAT_80438940,param_1,0xf,4,0,0xffffffff,0xffffffff);
  zz_00107a0_(param_1,0x14);
  zz_00107a0_(*(int *)(param_1 + 0x4a4),0x14);
  *(float *)(param_1 + 0x80c) = FLOAT_80438938;
  return;
}



// ==== 800ce298  FUN_800ce298 ====

void FUN_800ce298(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_800ce534(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar1 = (double)FLOAT_80438940;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    zz_004beb8_(dVar1,param_1,0xf,4,1,0xffffffff,0xffffffff);
    zz_00e19a8_(param_1,4,param_1 + 0x6f7);
  }
  dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043894c < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ce33c  FUN_800ce33c ====

void FUN_800ce33c(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar1 = zz_006de44_(param_1,0xf0f00);
  dVar2 = DOUBLE_80438930;
  if (uVar1 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar1) {
      uVar1 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar1;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - dVar2);
  }
  zz_004cd24_(param_1,0xf);
  FUN_800ce534(param_1);
  if (*(float *)(param_1 + 0x560) <= FLOAT_80438938) {
    dVar2 = (double)FLOAT_80438940;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    zz_004beb8_(dVar2,param_1,0xf,4,2,0xffffffff,0xffffffff);
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043894c < dVar2) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ce454  FUN_800ce454 ====

void FUN_800ce454(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80438950;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438930) * FLOAT_804389a4);
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(*(int *)(param_1 + 0x4a4) + 0x73f) = 0;
    *(uint *)(*(int *)(param_1 + 0x4a4) + 0x5e0) =
         *(uint *)(*(int *)(param_1 + 0x4a4) + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 800ce534  FUN_800ce534 ====

void FUN_800ce534(int param_1)

{
  short sVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    iVar2 = 2;
    sVar1 = 0x1555;
  }
  else {
    iVar2 = 1;
    sVar1 = 0x4000;
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,iVar2,sVar1,(float *)(param_1 + 0x524));
  gnt4_PSQUATScale_bl((double)FLOAT_80438948,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  return;
}



// ==== 800ce5dc  FUN_800ce5dc ====

void FUN_800ce5dc(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    iVar1 = zz_006dbe0_(param_9,2,1,1);
    if (iVar1 != 0) {
      zz_016cc24_(param_9,2);
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(float *)(param_9 + 0x694) = FLOAT_804389a8 + *(float *)(param_9 + 0x1dc8);
  }
  return;
}



// ==== 800ce66c  FUN_800ce66c ====

void FUN_800ce66c(undefined4 param_1,undefined2 *param_2)

{
  param_2[2] = 0;
  param_2[1] = 0;
  *param_2 = 0;
  return;
}



// ==== 800ce680  FUN_800ce680 ====

void FUN_800ce680(int param_1,short *param_2)

{
  short sVar1;
  double dVar2;
  int iVar3;
  short sVar4;
  
  dVar2 = DOUBLE_804389b0;
  iVar3 = *(char *)(param_1 + 0x6e9) * 4;
  param_2[1] = *(short *)(&DAT_8030cdd0 + iVar3);
  param_2[2] = *(short *)(&DAT_8030cdd2 + iVar3);
  sVar1 = param_2[2];
  sVar4 = (short)(int)(*(float *)(param_1 + 0x1dc8) *
                      (float)((double)CONCAT44(0x43300000,
                                               (int)param_2[1] - (int)*param_2 ^ 0x80000000) - dVar2
                             ));
  if ((int)sVar1 < (int)sVar4) {
    sVar4 = sVar1;
  }
  iVar3 = -(int)sVar1;
  if (sVar4 < iVar3) {
    sVar4 = (short)iVar3;
  }
  *param_2 = *param_2 + sVar4;
  sVar1 = *param_2;
  *(short *)(param_1 + 0x1988) = sVar1;
  *(short *)(param_1 + 0x1982) = sVar1;
  return;
}



// ==== 800ce858  FUN_800ce858 ====

void FUN_800ce858(int param_1)

{
  short sVar1;
  
  zz_00c74ec_(param_1,0x1a);
  FUN_800ce66c(param_1,(undefined2 *)(param_1 + 0x144));
  *(undefined1 *)(param_1 + 0x14b) = 0;
  *(undefined1 *)(param_1 + 0x14a) = 0;
  *(undefined4 *)(param_1 + 0x14c) = 0x1010101;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x601) {
    FUN_80136880(param_1,0);
    FUN_80136880(param_1,1);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
  }
  else if (sVar1 == 0x609) {
    zz_013833c_(param_1,0,param_1 + 0x14c);
    zz_013833c_(param_1,1,param_1 + 0x14d);
    zz_013833c_(param_1,2,param_1 + 0x14e);
    zz_013833c_(param_1,3,param_1 + 0x14f);
    *(undefined1 *)(param_1 + 0x4a8) = 2;
  }
  else if (sVar1 == 0x617) {
    FUN_80136880(param_1,2);
    FUN_80136880(param_1,3);
  }
  else if (sVar1 == 0x61d) {
    zz_013833c_(param_1,4,param_1 + 0x14c);
    zz_013833c_(param_1,5,param_1 + 0x14d);
    zz_013833c_(param_1,6,param_1 + 0x14e);
    zz_013833c_(param_1,7,param_1 + 0x14f);
  }
  return;
}



// ==== 800cea1c  FUN_800cea1c ====

void FUN_800cea1c(int param_1)

{
  FUN_800ce680(param_1,(short *)(param_1 + 0x144));
  return;
}



// ==== 800cea5c  FUN_800cea5c ====

void FUN_800cea5c(int param_1)

{
  (*(code *)(&PTR_FUN_8030ce34)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800cea98  FUN_800cea98 ====

void FUN_800cea98(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8030ce48)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ceae0  FUN_800ceae0 ====

void FUN_800ceae0(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030ce5c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ceb28  FUN_800ceb28 ====

void FUN_800ceb28(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804389b8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0xc1,0);
  if (*(short *)(param_1 + 0x5aa) < 0) {
    *(undefined1 *)(param_1 + 0x6ec) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 3;
  }
  zz_004beb8_((double)FLOAT_804389bc,param_1,0xf,2,
              (int)*(char *)(param_1 + 0x6ec) + (int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  fVar1 = FLOAT_804389c0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804389c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804389c0;
  return;
}



// ==== 800cec34  FUN_800cec34 ====

void FUN_800cec34(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804389c0;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar2 < fVar1) goto LAB_800cecb4;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800cf6fc(param_1);
  }
LAB_800cecb4:
  gnt4_PSQUATScale_bl((double)FLOAT_804389c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804389c8 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ced0c  FUN_800ced0c ====

void FUN_800ced0c(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_804389c0) {
    if ((*(short *)(param_1 + 1000) == 0x609) || (*(short *)(param_1 + 1000) == 0x61d)) {
      uVar1 = *(uint *)(param_1 + 0x5bc);
    }
    else {
      uVar1 = *(uint *)(param_1 + 0x5b4);
    }
    if ((uVar1 & 0x200) != 0) {
      iVar2 = zz_006dbe0_(param_1,0,1,0);
      if (iVar2 != 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        if (*(char *)(param_1 + 0x6ec) == '\0') {
          if (*(short *)(param_1 + 0x1dfc) < -0x7ff) {
            dVar3 = (double)FLOAT_804389bc;
            *(undefined1 *)(param_1 + 0x6ec) = 3;
            zz_004beb8_(dVar3,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,8,1);
            return;
          }
        }
        else if (0x7ff < *(short *)(param_1 + 0x1dfc)) {
          dVar3 = (double)FLOAT_804389bc;
          *(undefined1 *)(param_1 + 0x6ec) = 0;
          zz_004beb8_(dVar3,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,8,1);
          return;
        }
        zz_004beb8_((double)FLOAT_804389bc,param_1,0xf,2,*(char *)(param_1 + 0x6ec) + 1,0xffffffff,
                    0xffffffff);
        return;
      }
      goto LAB_800ceec0;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
      ((*(char *)(param_1 + 0x1cef) != -2 || ((*(uint *)(param_1 + 0x5e0) & 0x20f0) == 0)))) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_804389c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_804389c8 < dVar3) {
      zz_00b22f4_(param_1);
      return;
    }
    return;
  }
LAB_800ceec0:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800cef38  FUN_800cef38 ====

void FUN_800cef38(int param_1)

{
  (*(code *)(&PTR_FUN_8030ce68)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cef74  FUN_800cef74 ====

void FUN_800cef74(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804389cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  if (*(short *)(param_1 + 0x1dfc) < 1) {
    *(undefined1 *)(param_1 + 0x6ec) = 9;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 6;
  }
  zz_004beb8_((double)FLOAT_804389bc,param_1,1,2,(int)*(char *)(param_1 + 0x6ec),0xffffffff,
              0xffffffff);
  return;
}



// ==== 800ceffc  FUN_800ceffc ====

void FUN_800ceffc(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  dVar3 = DOUBLE_804389d0;
  fVar2 = FLOAT_804389c0;
  if (iVar4 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_804389d0);
      *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar3);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar4 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_800cf6fc(param_1);
    }
  }
  return;
}



// ==== 800cf108  FUN_800cf108 ====

void FUN_800cf108(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined1 uVar3;
  double dVar4;
  
  zz_004cd24_(param_9,1);
  dVar4 = (double)*(float *)(param_9 + 0x558);
  if (dVar4 <= (double)FLOAT_804389c0) {
    if ((*(short *)(param_9 + 1000) == 0x609) || (*(short *)(param_9 + 1000) == 0x61d)) {
      uVar1 = *(uint *)(param_9 + 0x5bc);
    }
    else {
      uVar1 = *(uint *)(param_9 + 0x5b4);
    }
    if ((uVar1 & 0x200) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar2 = zz_006dbe0_(param_9,0,1,0);
      if (iVar2 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar1 = *(uint *)(param_9 + 0x5e0);
        if (((uVar1 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((uVar1 & 0x10) == 0) {
            if ((uVar1 & 0x20) == 0) {
              zz_006a3d0_(param_9,'\0',0,2);
              return;
            }
            uVar3 = 2;
            *(undefined1 *)(param_9 + 0x581) = 2;
          }
          else {
            uVar3 = 1;
            *(undefined1 *)(param_9 + 0x581) = 1;
          }
        }
        else {
          uVar3 = 3;
          *(undefined1 *)(param_9 + 0x581) = 3;
        }
        if (*(char *)(param_9 + 0x6ec) == '\x06') {
          if (*(short *)(param_9 + 0x1dfc) < -0x7ff) {
            zz_006a3d0_(param_9,'\0',uVar3,0);
            return;
          }
        }
        else if (0x7ff < *(short *)(param_9 + 0x1dfc)) {
          zz_006a3d0_(param_9,'\0',uVar3,0);
          return;
        }
        zz_004beb8_((double)FLOAT_804389bc,param_9,1,2,*(char *)(param_9 + 0x6ec) + 1,8,1);
        return;
      }
      goto LAB_800cf2cc;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar4 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) &&
     (((*(char *)(param_9 + 0x1cef) != -2 || ((*(uint *)(param_9 + 0x5e0) & 0x20f0) == 0)) &&
      (*(char *)(param_9 + 0x1cee) == '\0')))) {
    return;
  }
LAB_800cf2cc:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800cf300  FUN_800cf300 ====

void FUN_800cf300(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030ce74)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800cf348  FUN_800cf348 ====

void FUN_800cf348(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804389b8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_804389d8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(short *)(param_1 + 0x5aa) < 0) {
    *(undefined1 *)(param_1 + 0x6ec) = 0x12;
  }
  else {
    *(undefined1 *)(param_1 + 0x6ec) = 0x14;
  }
  zz_004beb8_((double)FLOAT_804389bc,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ec),6,1);
  *(float *)(param_1 + 0x80c) = FLOAT_804389c0;
  return;
}



// ==== 800cf3f4  FUN_800cf3f4 ====

void FUN_800cf3f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_804389d8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_804389c0;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d0dc_(param_1,0x81,0);
    if (iVar3 == 0) goto LAB_800cf498;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800cf6fc(param_1);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
LAB_800cf498:
  if (FLOAT_804389c8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800cf4c4  FUN_800cf4c4 ====

void FUN_800cf4c4(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804389d8,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804389dc + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_804389c0) {
    if ((*(short *)(param_1 + 1000) == 0x609) || (*(short *)(param_1 + 1000) == 0x61d)) {
      uVar2 = *(uint *)(param_1 + 0x5bc);
    }
    else {
      uVar2 = *(uint *)(param_1 + 0x5b4);
    }
    if ((uVar2 & 0x200) != 0) {
      iVar4 = zz_006dbe0_(param_1,0,1,0);
      if (iVar4 != 0) {
        if (iVar3 != 0) {
          zz_006a3d0_(param_1,'\0',0,2);
          zz_0066530_(param_1,0x2c);
          return;
        }
        zz_006bf80_(param_1);
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_006d0dc_(param_1,0x81,0);
        uVar6 = 0xffffffff;
        uVar7 = 0xffffffff;
        cVar5 = *(char *)(param_1 + 0x6ec) + '\x01';
        if (*(char *)(param_1 + 0x6ec) == '\x12') {
          if (*(short *)(param_1 + 0x5aa) < 0x800) goto LAB_800cf650;
          cVar5 = '\x14';
        }
        else {
          if (-0x800 < *(short *)(param_1 + 0x5aa)) goto LAB_800cf650;
          cVar5 = '\x12';
        }
        *(char *)(param_1 + 0x6ec) = cVar5;
        uVar6 = 8;
        uVar7 = 1;
LAB_800cf650:
        zz_004beb8_((double)FLOAT_804389bc,param_1,0xf,2,(int)cVar5,uVar6,uVar7);
        return;
      }
      goto LAB_800cf684;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_1 + 0x1cee) == '\0')) {
    if (FLOAT_804389c8 < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
      return;
    }
    return;
  }
LAB_800cf684:
  fVar1 = FLOAT_804389c0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  if (fVar1 < *(float *)(param_1 + 0x48)) {
    *(float *)(param_1 + 0x48) = fVar1;
  }
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  zz_006a5a4_(param_1);
  return;
}



// ==== 800cf6fc  FUN_800cf6fc ====

void FUN_800cf6fc(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_804389e0;
  *(float *)(param_1 + 0x560) = FLOAT_804389cc;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x601) {
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      FUN_80128df8(param_1,*(undefined1 *)(param_1 + 0x6e8),0,-1);
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x6e8) + 0x14a) = 1;
    }
  }
  else if ((sVar1 == 0x609) || (sVar1 == 0x61d)) {
    if (*(char *)(param_1 + 0x6e8) == '\0') {
      if (((*(uint *)(param_1 + 0x14c) & 0x10001) != 0) &&
         (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
        *(uint *)(param_1 + 0x14c) = *(uint *)(param_1 + 0x14c) | 0x800080;
      }
    }
    else if (((*(uint *)(param_1 + 0x14c) & 0x1000100) != 0) &&
            (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
      *(uint *)(param_1 + 0x14c) = *(uint *)(param_1 + 0x14c) | 0x80008000;
    }
  }
  else if ((sVar1 == 0x617) && (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
    FUN_80128df8(param_1,*(char *)(param_1 + 0x6e8) + '\x02',1,-1);
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x6e8) + 0x14a) = 1;
  }
  return;
}



// ==== 800cf884  FUN_800cf884 ====

void FUN_800cf884(int param_1)

{
  (*(code *)(&PTR_FUN_8030ce80)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cf8c0  FUN_800cf8c0 ====

void FUN_800cf8c0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 800cf8f4  FUN_800cf8f4 ====

void FUN_800cf8f4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 800cf928  FUN_800cf928 ====

void FUN_800cf928(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 800cf968  FUN_800cf968 ====

void FUN_800cf968(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 800cf990  FUN_800cf990 ====

void FUN_800cf990(int param_1)

{
  (*(code *)(&PTR_FUN_8030cef8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cf9cc  FUN_800cf9cc ====

void FUN_800cf9cc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0179fcc_(param_1);
  return;
}



// ==== 800cfa00  FUN_800cfa00 ====

void FUN_800cfa00(int param_1)

{
  zz_006d144_(param_1,0xc1);
  zz_006e820_(param_1);
  return;
}



// ==== 800cfa38  FUN_800cfa38 ====

void FUN_800cfa38(int param_1)

{
  short sVar1;
  bool bVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  bVar2 = false;
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
  iVar5 = zz_006dbe0_(param_1,2,1,1);
  if (iVar5 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x601) {
      zz_0084600_(param_1,7);
      zz_0084600_(param_1,8);
    }
    else if (sVar1 == 0x609) {
      zz_00c3be0_(param_1,0x2c);
      zz_00c3be0_(param_1,0x2d);
      zz_00c3be0_(param_1,0x2e);
      zz_00c3be0_(param_1,0x2f);
    }
    else if (sVar1 == 0x617) {
      zz_0084600_(param_1,0xf);
      zz_0084600_(param_1,0x10);
    }
    else if (sVar1 == 0x61d) {
      zz_00c3be0_(param_1,0x41);
      zz_00c3be0_(param_1,0x42);
      zz_00c3be0_(param_1,0x43);
      zz_00c3be0_(param_1,0x44);
    }
    bVar2 = true;
  }
  fVar3 = FLOAT_804389bc;
  if (bVar2) {
    *(float *)(param_1 + 0x44) = FLOAT_804389e4;
    fVar4 = FLOAT_804389cc;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar4;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  fVar3 = FLOAT_804389c0;
  *(float *)(param_1 + 0x40) = FLOAT_804389c0;
  *(float *)(param_1 + 0x3c) = fVar3;
  *(float *)(param_1 + 0x38) = fVar3;
  return;
}



// ==== 800cfb94  FUN_800cfb94 ====

void FUN_800cfb94(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  
  iVar3 = 2;
  if (*(short *)(param_9 + 1000) == 0x61d) {
    iVar3 = 10;
  }
  iVar1 = 0;
  iVar4 = 4;
  do {
    iVar2 = param_9 + iVar1 + 0x14c;
    if ((*(byte *)(param_9 + iVar1 + 0x14c) & 1) != 0) {
      zz_013212c_(param_9,iVar3 + iVar1,iVar2);
      break;
    }
    iVar1 = iVar1 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,iVar2,iVar3,
              in_r7,in_r8,in_r9,in_r10);
  *(float *)(param_9 + 0x694) = FLOAT_804389d8 + *(float *)(param_9 + 0x1dc8);
  return;
}



// ==== 800cfc38  FUN_800cfc38 ====

void FUN_800cfc38(int param_1)

{
  (*(code *)(&PTR_FUN_8030cf24)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800cfc74  FUN_800cfc74 ====

void FUN_800cfc74(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    zz_006d144_(param_1,0xc1);
    zz_006e820_(param_1);
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
    dVar3 = (double)FLOAT_804389bc;
    *(undefined1 *)(param_1 + 0x6ea) = 2;
    zz_004beb8_(dVar3,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_804389c0;
  }
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_804389c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    iVar1 = 2;
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    if (*(short *)(param_1 + 1000) == 0x61d) {
      iVar1 = 10;
    }
    iVar2 = 0;
    do {
      if ((*(byte *)(param_1 + iVar2 + 0x14c) & 1) != 0) {
        zz_013212c_(param_1,iVar1 + iVar2,param_1 + iVar2 + 0x14c);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_804389e8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800cfdf0  FUN_800cfdf0 ====

void FUN_800cfdf0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 2;
  if (*(short *)(param_9 + 1000) == 0x61d) {
    iVar2 = 10;
  }
  iVar3 = 0;
  do {
    iVar1 = param_9 + iVar3 + 0x14c;
    if ((*(byte *)(param_9 + iVar3 + 0x14c) & 1) != 0) {
      zz_013212c_(param_9,iVar2 + iVar3,iVar1);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,iVar1,
              param_12,param_13,param_14,param_15,param_16);
  *(float *)(param_9 + 0x694) = FLOAT_804389d8 + *(float *)(param_9 + 0x1dc8);
  return;
}



// ==== 800cff98  FUN_800cff98 ====

void FUN_800cff98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(short *)(param_1 + 1000) == 2) {
    FUN_8009a6c4(param_1,0);
    for (iVar3 = 0; iVar3 < *(short *)(param_1 + 0x79e); iVar3 = iVar3 + 1) {
      FUN_800e7c68(param_1,(char)iVar3,0);
    }
  }
  else if (*(short *)(param_1 + 1000) == 0xb) {
    FUN_8009a6c4(param_1,1);
    for (iVar3 = 0; iVar3 < *(short *)(param_1 + 0x79e); iVar3 = iVar3 + 1) {
      FUN_800e7c68(param_1,(char)iVar3,1);
    }
  }
  fVar1 = FLOAT_804389f0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  fVar2 = FLOAT_804389f4;
  *(char *)(param_1 + 0x144) = (char)*(undefined2 *)(param_1 + 0x784);
  *(undefined1 *)(param_1 + 0x15c) = 0;
  *(float *)(param_1 + 0x154) = fVar1;
  *(float *)(param_1 + 0x158) = fVar2;
  return;
}



// ==== 800d00a4  FUN_800d00a4 ====

void FUN_800d00a4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  double local_18;
  double local_10;
  
  *(undefined1 *)(param_1 + 0x15e) = *(undefined1 *)(param_1 + 0x1afc);
  *(undefined1 *)(param_1 + 0x15f) = *(undefined1 *)(param_1 + 0x1afd);
  if ((*(short *)(param_1 + 1000) != 2) && (*(short *)(param_1 + 1000) != 0xb)) {
    return;
  }
  if ((*(char *)(param_1 + 0x144) == '\0') && (*(float *)(param_1 + 0x788) <= FLOAT_804389f4)) {
    *(undefined1 *)(param_1 + 0x15c) = 0;
    *(char *)(param_1 + 0x144) = (char)*(undefined2 *)(param_1 + 0x784);
  }
  if ((*(byte *)(param_1 + 0x145) & 1) != 0) {
    iVar7 = (int)(FLOAT_804389f8 * *(float *)(param_1 + 0x1dc8));
    iVar6 = *(int *)(param_1 + 0x148) + iVar7;
    *(int *)(param_1 + 0x148) = iVar6;
    if (0x12000 < iVar6) {
      *(undefined1 *)(param_1 + 0x145) = 0;
      iVar7 = iVar7 - (*(int *)(param_1 + 0x148) + -0x12000);
    }
    *(short *)(param_1 + 0x1950) = *(short *)(param_1 + 0x1950) - (short)iVar7;
    goto LAB_800d0260;
  }
  if ((*(byte *)(param_1 + 0x145) & 2) == 0) goto LAB_800d0260;
  fVar2 = *(float *)(param_1 + 0x150) - *(float *)(param_1 + 0x1dc8);
  bVar8 = fVar2 <= FLOAT_804389f4;
  *(float *)(param_1 + 0x150) = fVar2;
  fVar2 = FLOAT_804389f0;
  if (bVar8) {
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined2 *)(param_1 + 0x1950) = 0;
    *(float *)(param_1 + 0x154) = fVar2;
    goto LAB_800d0260;
  }
  local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1950)) ^ 0x80000000);
  *(short *)(param_1 + 0x1950) =
       (short)(int)(FLOAT_804389fc * *(float *)(param_1 + 0x1dc8) +
                   (float)(local_18 - DOUBLE_80438a18));
  cVar1 = *(char *)(param_1 + 0x14c);
  if (cVar1 == '\x01') {
LAB_800d0224:
    *(float *)(param_1 + 0x154) =
         -(FLOAT_80438a0c * *(float *)(param_1 + 0x1dc8) - *(float *)(param_1 + 0x154));
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (FLOAT_80438a00 <= *(float *)(param_1 + 0x158)) {
      *(float *)(param_1 + 0x154) = FLOAT_80438a08;
      *(char *)(param_1 + 0x14c) = *(char *)(param_1 + 0x14c) + '\x01';
      goto LAB_800d0224;
    }
    *(float *)(param_1 + 0x154) =
         FLOAT_80438a04 * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x154);
  }
  *(float *)(param_1 + 0x158) = *(float *)(param_1 + 0x158) + *(float *)(param_1 + 0x1dc8);
LAB_800d0260:
  fVar2 = FLOAT_80438a14;
  if (((*(char *)(param_1 + 0x144) == '\0') && (*(float *)(param_1 + 0x788) <= FLOAT_80438a10)) &&
     (*(char *)(param_1 + 0x15c) == '\0')) {
    fVar3 = FLOAT_80438a10 - *(float *)(param_1 + 0x788);
    *(undefined1 *)(param_1 + 0x145) = 2;
    *(undefined1 *)(param_1 + 0x14c) = 0;
    dVar5 = DOUBLE_80438a18;
    fVar4 = FLOAT_80438a04;
    *(float *)(param_1 + 0x150) = fVar2 - fVar3;
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1950)) ^ 0x80000000);
    *(short *)(param_1 + 0x1950) = (short)(int)(FLOAT_804389fc * fVar3 + (float)(local_10 - dVar5));
    *(undefined1 *)(param_1 + 0x15c) = 1;
    *(float *)(param_1 + 0x154) = fVar4 * fVar3;
    *(float *)(param_1 + 0x158) = fVar3;
  }
  if ((int)*(short *)(param_1 + 0x784) != (int)*(char *)(param_1 + 0x144)) {
    *(char *)(param_1 + 0x144) = (char)*(short *)(param_1 + 0x784);
    *(undefined1 *)(param_1 + 0x145) = 1;
    *(undefined4 *)(param_1 + 0x148) = 0;
  }
  return;
}



// ==== 800d033c  FUN_800d033c ====

void FUN_800d033c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8030ddc0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800d037c  FUN_800d037c ====

void FUN_800d037c(int param_1,int param_2)

{
  zz_0099e70_(param_1,(&DAT_80433b50)[param_2 * 2 + (uint)(*(short *)(param_1 + 1000) == 0xb)]);
  return;
}



// ==== 800d03dc  FUN_800d03dc ====

void FUN_800d03dc(int param_1)

{
  (*(code *)(&PTR_FUN_8030ddd0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800d0418  FUN_800d0418 ====

void FUN_800d0418(int param_1)

{
  (*(code *)(&PTR_FUN_8030dddc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d0454  FUN_800d0454 ====

void FUN_800d0454(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8030de04)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d049c  FUN_800d049c ====

void FUN_800d049c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80438a20;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  FUN_800d0c20(param_1);
  fVar1 = FLOAT_804389f4;
  *(float *)(param_1 + 0x4c) = FLOAT_804389f4;
  *(float *)(param_1 + 0x44) = fVar1;
  return;
}



// ==== 800d0514  FUN_800d0514 ====

void FUN_800d0514(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804389f4;
  if ((iVar3 == 0) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800d0c50(param_1);
  }
  return;
}



