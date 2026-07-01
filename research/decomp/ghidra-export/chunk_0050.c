// ==== 801a1904  zz_01a1904_ ====

void zz_01a1904_(int param_1)

{
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  (*(code *)(&PTR_zz_01a1948__80378720)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a1948  zz_01a1948_ ====

void zz_01a1948_(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_8043b5a8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b598,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043b598,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5a4;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 801a1a1c  zz_01a1a1c_ ====

void zz_01a1a1c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_8043b594;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) goto LAB_801a1ad4;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01a1af0_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
LAB_801a1ad4:
  zz_00b22f4_(param_1);
  return;
}



// ==== 801a1af0  zz_01a1af0_ ====

void zz_01a1af0_(int param_1)

{
  short sVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x6ef) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x90b) {
      zz_00c67bc_(param_1,8,*(undefined1 *)(param_1 + 0x6ed));
    }
    else if ((sVar1 < 0x90b) && (sVar1 == 0x906)) {
      zz_0082824_(param_1,0x6a);
    }
    if (*(short *)(param_1 + 1000) == 0x90b) {
      zz_00f0104_(param_1,0x24,2);
    }
    *(char *)(param_1 + 0x6ed) = *(char *)(param_1 + 0x6ed) + '\x01';
    *(byte *)(param_1 + 0x6ed) = *(byte *)(param_1 + 0x6ed) & 1;
    *(undefined1 *)(param_1 + 0x6ef) = 1;
  }
  *(undefined1 *)(param_1 + 0x6ee) = 3;
  return;
}



// ==== 801a1bbc  zz_01a1bbc_ ====

undefined4 zz_01a1bbc_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*(short *)(param_1 + 1000) == 0x90b) && ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0)) &&
     (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 801a1c14  zz_01a1c14_ ====

void zz_01a1c14_(int param_1)

{
  (*(code *)(&PTR_zz_01a1c50__8037872c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801a1c50  zz_01a1c50_ ====

void zz_01a1c50_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a1ca0__80378744)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a1ca0  zz_01a1ca0_ ====

void zz_01a1ca0_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043b5ac;
  fVar1 = FLOAT_8043b594;
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
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}



// ==== 801a1d5c  zz_01a1d5c_ ====

void zz_01a1d5c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043b590;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043b5b0 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043b5b0 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043b5b4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801a1e70  zz_01a1e70_ ====

void zz_01a1e70_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x04') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_801a1ea8;
  }
  zz_004cd24_(param_1,0xf);
LAB_801a1ea8:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    zz_006ed8c_((double)FLOAT_8043b59c,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043b5bc;
    fVar1 = FLOAT_8043b5b8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 801a1f68  zz_01a1f68_ ====

void zz_01a1f68_(int param_1)

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
          fVar1 = FLOAT_8043b5c0;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_8043b590;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_8043b5c4;
          }
          dVar3 = (double)FLOAT_8043b598;
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
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



// ==== 801a2110  zz_01a2110_ ====

void zz_01a2110_(int param_1)

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
      *(float *)(param_1 + 0x4c) = FLOAT_8043b598;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar3 = FLOAT_8043b594;
      fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar2;
      if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), 0 < (int)uVar4)
         ) {
        fVar3 = FLOAT_8043b5c8;
        fVar2 = FLOAT_8043b5bc;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043b594,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
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



// ==== 801a22c8  zz_01a22c8_ ====

void zz_01a22c8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 801a22fc  zz_01a22fc_ ====

void zz_01a22fc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a234c__8037875c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a234c  zz_01a234c_ ====

void zz_01a234c_(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  dVar2 = (double)FLOAT_8043b5d0;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  zz_006ed8c_(dVar2,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}



// ==== 801a241c  zz_01a241c_ ====

void zz_01a241c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043b5d4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043b590;
    *(float *)(param_1 + 0x558) = FLOAT_8043b590;
    fVar3 = FLOAT_8043b5b4;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 801a254c  zz_01a254c_ ====

void zz_01a254c_(int param_1)

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
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043b598;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801a2624  zz_01a2624_ ====

void zz_01a2624_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043b5a8 < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043b5d8,param_1);
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
  fVar3 = FLOAT_8043b594;
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
      goto LAB_801a27c4;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043b5dc;
      fVar3 = FLOAT_8043b5bc;
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
LAB_801a27c4:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 801a2824  zz_01a2824_ ====

void zz_01a2824_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 801a2858  zz_01a2858_ ====

void zz_01a2858_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a28a8__80378770)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a28a8  zz_01a28a8_ ====

void zz_01a28a8_(int param_1)

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
  dVar2 = (double)FLOAT_8043b598;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 801a2964  zz_01a2964_ ====

void zz_01a2964_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d144_(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801a29d8;
  }
  fVar2 = FLOAT_8043b5d8;
  fVar1 = FLOAT_8043b590;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801a29d8:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 801a2a18  zz_01a2a18_ ====

/* WARNING: Removing unreachable block (ram,0x801a2c3c) */
/* WARNING: Removing unreachable block (ram,0x801a2a28) */

void zz_01a2a18_(int param_1)

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
  fVar1 = FLOAT_8043b594;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b5b0 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b590
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
    local_34 = FLOAT_8043b590 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b594;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b5e0;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b5e4;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043b5e0);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043b5ac,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043b5e8 * (double)*(float *)(param_1 + 0x44)) goto LAB_801a2c30;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_801a2c30:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801a2c58  zz_01a2c58_ ====

void zz_01a2c58_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b594;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b594) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b594;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801a2cfc  zz_01a2cfc_ ====

void zz_01a2cfc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a2d4c__80378780)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801a2d4c  zz_01a2d4c_ ====

void zz_01a2d4c_(int param_1)

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
  dVar2 = (double)FLOAT_8043b598;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 801a2e08  zz_01a2e08_ ====

void zz_01a2e08_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d144_(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801a2e7c;
  }
  fVar2 = FLOAT_8043b5d8;
  fVar1 = FLOAT_8043b590;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801a2e7c:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 801a2ebc  zz_01a2ebc_ ====

/* WARNING: Removing unreachable block (ram,0x801a30e0) */
/* WARNING: Removing unreachable block (ram,0x801a2ecc) */

void zz_01a2ebc_(int param_1)

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
  fVar1 = FLOAT_8043b594;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b5f0 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b590
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
    local_34 = FLOAT_8043b590 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b594;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b5e0;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b5e4;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043b5e0);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043b5ac,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043b5e8 * (double)*(float *)(param_1 + 0x44)) goto LAB_801a30d4;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_801a30d4:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801a30fc  zz_01a30fc_ ====

void zz_01a30fc_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b594;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b594) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b594;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801a31a0  zz_01a31a0_ ====

void zz_01a31a0_(int param_1)

{
  (**(code **)(&DAT_80435758 + *(char *)(param_1 + 0x581) * 4))();
  return;
}



// ==== 801a31d8  zz_01a31d8_ ====

void zz_01a31d8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a324c__80378790)[*(char *)(param_1 + 0x540)])(param_1);
  if (FLOAT_8043b590 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_8043b590;
  }
  return;
}



// ==== 801a324c  zz_01a324c_ ====

/* WARNING: Removing unreachable block (ram,0x801a3450) */
/* WARNING: Removing unreachable block (ram,0x801a325c) */

void zz_01a324c_(undefined8 param_1,double param_2,double param_3,int param_4)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double in_f31;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  fVar1 = FLOAT_8043b5ac;
  *(char *)(param_4 + 0x540) = *(char *)(param_4 + 0x540) + '\x01';
  *(undefined1 *)(param_4 + 0x541) = 0;
  *(float *)(param_4 + 0x558) = fVar1;
  *(undefined1 *)(param_4 + 0x545) = 0;
  if (((*(int *)(param_4 + 0xcc) == 0) || ('\0' < *(char *)(param_4 + 0x1dc))) ||
     (*(char *)(*(int *)(param_4 + 0xcc) + 0x83) != '\0')) {
    *(undefined1 *)(param_4 + 0x541) = 1;
    *(undefined4 *)(param_4 + 0xcc) = 0;
  }
  dVar3 = (double)FLOAT_8043b5f4;
  if ((*(char *)(param_4 + 0x541) == '\0') &&
     (*(char *)(param_4 + 0x88) == *(char *)(*(int *)(param_4 + 0xcc) + 0x88))) {
    local_2c = *(float *)(param_4 + 0x8e0);
    local_28 = *(float *)(param_4 + 0x8f0);
    in_f31 = (double)(FLOAT_8043b5f8 + local_28);
    local_24 = *(undefined4 *)(param_4 + 0x900);
    local_38 = *(float *)(param_4 + 0x518);
    local_34 = *(undefined4 *)(param_4 + 0x51c);
    local_30 = *(undefined4 *)(param_4 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    dVar3 = gnt4_PSVECMag_bl(&local_2c);
    param_2 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x8f0);
    param_3 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x668);
  }
  if ((((double)FLOAT_8043b5fc <= dVar3) ||
      (in_f31 < (double)(float)(param_2 - (double)FLOAT_8043b5f8))) ||
     ((double)(float)(param_2 + param_3) < in_f31)) {
    zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,0,0xffffffff,0xffffffff);
    *(float *)(param_4 + 0x80c) = FLOAT_8043b594;
    *(undefined1 *)(param_4 + 0x544) = 0;
  }
  else {
    if (*(char *)(param_4 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,2,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_8043b598,param_4,0xf,4,5,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_4 + 0x544) = 1;
  }
  zz_01a3e54_(param_4,0xc0);
  fVar1 = FLOAT_8043b594;
  *(float *)(param_4 + 0x38) = FLOAT_8043b594;
  *(float *)(param_4 + 0x3c) = fVar1;
  *(float *)(param_4 + 0x40) = fVar1;
  iVar2 = zz_006dbe0_(param_4,2,1,1);
  if (iVar2 == 0) {
    *(undefined2 *)(param_4 + 0x548) = 0;
  }
  else {
    *(undefined2 *)(param_4 + 0x548) = 1;
  }
  return;
}



// ==== 801a346c  zz_01a346c_ ====

void zz_01a346c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_01a3e54_(param_1,0xc0), iVar3 != 0)) {
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (*(char *)(param_1 + 0x88) != *(char *)(*(int *)(param_1 + 0xcc) + 0x88))) {
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
    }
    FUN_80066958(param_1);
    fVar2 = FLOAT_8043b5a8;
    fVar1 = FLOAT_8043b590;
    if (*(char *)(param_1 + 0x544) == '\x01') {
      if (*(short *)(param_1 + 0x548) == 0) {
        if (*(char *)(param_1 + 0x581) == '\0') {
          *(undefined1 *)(param_1 + 0x73f) = 0;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
          zz_006a474_(param_1);
          return;
        }
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar2 = FLOAT_8043b5cc;
      *(float *)(param_1 + 0x558) = fVar1;
      fVar1 = FLOAT_8043b594;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(float *)(param_1 + 0x50) = fVar1;
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
    if (FLOAT_8043b5b4 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 801a35d4  zz_01a35d4_ ====

void zz_01a35d4_(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8fc);
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(short *)(param_1 + 0x548) == 0) {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\t')) {
        *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
    }
    else {
      zz_01a3e54_(param_1,0xc0);
      if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
        FUN_8006c1c8((double)FLOAT_8043b5c0,param_1,(float *)(param_1 + 0x518));
        if (FLOAT_8043b5d8 <= *(float *)(param_1 + 0x760)) {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b5a8;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b600;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
      FUN_80067610(param_1);
      if ((*(float *)(param_1 + 0x4c) < FLOAT_8043b594) &&
         (*(float *)(param_1 + 0x44) < FLOAT_8043b5cc)) {
        *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
      }
      fVar1 = FLOAT_8043b590;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\n')) {
        *(undefined1 *)(param_1 + 0x545) = 1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
      else if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_01a4000_(param_1);
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  if (*(char *)(param_1 + 0x545) == '\x01') {
    zz_00f0104_(param_1,0x1c,1);
  }
  return;
}



// ==== 801a37f0  zz_01a37f0_ ====

void zz_01a37f0_(int param_1)

{
  float fVar1;
  double dVar2;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  zz_00f0104_(param_1,0x1c,1);
  zz_01a3e54_(param_1,0xc0);
  if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
    local_18 = *(float *)(param_1 + 0x518);
    local_14 = *(float *)(param_1 + 0x51c) - FLOAT_8043b5f8;
    local_10 = *(undefined4 *)(param_1 + 0x520);
    FUN_8006c1c8((double)FLOAT_8043b5c0,param_1,&local_18);
    if (FLOAT_8043b5d8 <= *(float *)(param_1 + 0x760)) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043b5a8;
    }
    else {
      *(float *)(param_1 + 0x4c) = FLOAT_8043b600;
    }
    zz_01a3e98_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  FUN_80067610(param_1);
  if (*(float *)(param_1 + 0x4c) < FLOAT_8043b594) {
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b5cc) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
    }
  }
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar1 = FLOAT_8043b604;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(float *)(param_1 + 0x558) <= FLOAT_8043b594) {
      dVar2 = (double)FLOAT_8043b598;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x542) = 0;
      *(undefined1 *)(param_1 + 0x543) = 0;
      *(float *)(param_1 + 0x4c) = fVar1;
      zz_004beb8_(dVar2,param_1,0xf,4,1,0xffffffff,0xffffffff);
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_01a4000_(param_1);
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801a39a4  zz_01a39a4_ ====

void zz_01a39a4_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x540) = 7;
  }
  FUN_80067610(param_1);
  if (*(char *)(param_1 + 0x543) == '\x01') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x148);
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x14c);
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x150);
  }
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b610) * FLOAT_8043b608);
  *(undefined1 *)(param_1 + 0x547) = 1;
  return;
}



// ==== 801a3a68  zz_01a3a68_ ====

void zz_01a3a68_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_01a3e54_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar2 = FUN_80066838((double)FLOAT_8043b618,param_1), 0 < (int)uVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_004cff4_(param_1,0xf);
  }
  return;
}



// ==== 801a3b0c  zz_01a3b0c_ ====

void zz_01a3b0c_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bool bVar5;
  
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\b')) {
      *(undefined1 *)(param_1 + 0x542) = 99;
      if (*(char *)(param_1 + 0x581) == '\0') {
        zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_01a3e54_(param_1,0xc0);
      FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
      fVar3 = FLOAT_8043b5a4;
      fVar2 = FLOAT_8043b594;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x06')) {
        if (*(char *)(param_1 + 0x1d9) < '\x01') {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x542) = 2;
          *(float *)(param_1 + 0x558) = fVar3;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
          *(float *)(param_1 + 0x44) = fVar2;
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        }
      }
    }
  }
  else if ((cVar1 < '\x03') &&
          (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
          bVar5 = fVar2 <= FLOAT_8043b594, *(float *)(param_1 + 0x558) = fVar2, bVar5)) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_1 + 0x542) = 99;
  }
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 == 0) {
    *(undefined1 *)(param_1 + 0x547) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x547) = 0;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x540) = 8;
  }
  return;
}



// ==== 801a3d04  FUN_801a3d04 ====

/* WARNING: Removing unreachable block (ram,0x801a3ddc) */
/* WARNING: Removing unreachable block (ram,0x801a3dd4) */
/* WARNING: Removing unreachable block (ram,0x801a3d1c) */
/* WARNING: Removing unreachable block (ram,0x801a3d14) */

void FUN_801a3d04(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  *(undefined2 *)(param_1 + 0x18da) = 0;
  FUN_80067610(param_1);
  if (*(char *)(param_1 + 0x547) == '\x01') {
    iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
    dVar2 = (double)*(float *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
    dVar3 = DOUBLE_8043b610;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    dVar3 = (double)(float)((double)CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000) - dVar3);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(short *)(param_1 + 0x5ae) = (short)(int)dVar3;
    *(float *)(param_1 + 0x44) = (float)dVar2;
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 801a3df8  FUN_801a3df8 ====

void FUN_801a3df8(int param_1)

{
  *(undefined2 *)(param_1 + 0x18da) = 0;
  if (*(char *)(param_1 + 0x547) == '\x01') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 801a3e54  zz_01a3e54_ ====

void zz_01a3e54_(int param_1,uint param_2)

{
  zz_006660c_(param_1);
  FUN_800669d0(param_1,param_2);
  return;
}



// ==== 801a3e98  zz_01a3e98_ ====

void zz_01a3e98_(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  undefined4 local_14;
  double local_10;
  
  local_1c = *(float *)(param_1 + 0x38);
  local_18 = FLOAT_8043b594;
  local_14 = *(undefined4 *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),afStack_28);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_1c,afStack_28);
  dVar2 = (double)FLOAT_8043b5a8;
  if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_8043b598)) {
    dVar2 = (double)FLOAT_8043b598;
  }
  dVar3 = (double)gnt4_acos_bl(dVar2);
  dVar2 = DOUBLE_8043b610;
  if (*(float *)(param_1 + 0x3c) <= FLOAT_8043b594) {
    fVar1 = FLOAT_8043b61c * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + 0x222;
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if (fVar1 < (float)(local_10 - dVar2)) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (0x3c71 < *(short *)(param_1 + 0x18da)) {
      *(undefined2 *)(param_1 + 0x18da) = 0x3c71;
    }
  }
  else {
    fVar1 = FLOAT_8043b61c * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + -0x222;
    fVar1 = -fVar1;
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if ((float)(local_10 - dVar2) < fVar1) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (*(short *)(param_1 + 0x18da) < -0x3c71) {
      *(undefined2 *)(param_1 + 0x18da) = 0xc38f;
    }
  }
  return;
}



// ==== 801a4000  zz_01a4000_ ====

void zz_01a4000_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  
  fVar2 = FLOAT_8043b598;
  fVar1 = FLOAT_8043b594;
  pfVar4 = (float *)(param_1 + 0x148);
  *(undefined1 *)(param_1 + 0x543) = 1;
  *(float *)(param_1 + 0x148) = fVar2 * *(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0x14c) = fVar1;
  *(float *)(param_1 + 0x150) = fVar2 * *(float *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  *(float *)(param_1 + 0x14c) = FLOAT_8043b620;
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  fVar2 = FLOAT_8043b5a8;
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x38) = FLOAT_8043b594;
  fVar3 = FLOAT_8043b624;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar2 = FLOAT_8043b628;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x44) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x694) = fVar2 + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 801a40b0  zz_01a40b0_ ====

void zz_01a40b0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,1,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x23;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = zz_01a41b8_;
    *(code **)(puVar1 + 0x10c) = zz_01a44a8_;
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



// ==== 801a41b8  zz_01a41b8_ ====

void zz_01a41b8_(int param_1)

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
  (*(code *)(&PTR_zz_01a4244__80379318)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a4244  zz_01a4244_ ====

void zz_01a4244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x24;
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
    *(undefined2 *)(param_9 + 0x1e) = 0;
    iVar3 = *(char *)(param_9 + 0x11) * 0x18;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined *)(param_9 + 0x89) = (&DAT_803792b9)[iVar3];
    uVar4 = *(undefined4 *)(&DAT_803792c0 + iVar3);
    *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803792bc + iVar3);
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803792c4 + iVar3);
    *(code **)(param_9 + 0x100) = zz_01a43f8_;
    uVar5 = zz_0089100_(param_9,1,1);
    zz_01a452c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801a4344  zz_01a4344_ ====

void zz_01a4344_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  short sVar2;
  
  iVar1 = zz_01a4644_(param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    zz_01a452c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 801a439c  zz_01a439c_ ====

void zz_01a439c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a43b0  zz_01a43b0_ ====

void zz_01a43b0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a43f8  zz_01a43f8_ ====

void zz_01a43f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [13];
  
  iVar2 = *(int *)(param_9 + 0x8c);
  zz_00455fc_((float *)(iVar2 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),(float *)(param_9 + 0x114)
              ,(float *)(param_9 + 100));
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar3) != 0) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar5 + 0x10);
      uVar6 = zz_00456a0_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar4 + 0xe0),afStack_48,(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,
                  in_r10);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 801a44a8  zz_01a44a8_ ====

void zz_01a44a8_(int param_1)

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



// ==== 801a452c  zz_01a452c_ ====

void zz_01a452c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar8) break;
    uVar6 = 1 << iVar8;
    if (((int)*(short *)(param_9 + 0x1e) & uVar6) == 0) {
      iVar5 = *(int *)(param_9 + 0x54);
      iVar4 = iVar8 * 0x24;
      iVar3 = (int)*(char *)(param_9 + 0x11);
      *(undefined2 *)(param_9 + 0x1c) = 5;
      piVar7 = (int *)(iVar5 + iVar4);
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)uVar6;
      *(undefined2 *)(piVar7 + 8) = 0;
      *(undefined2 *)((int)piVar7 + 0x22) = *(undefined2 *)(&DAT_803792ba + iVar3 * 0x18);
      uVar1 = zz_00055fc_();
      zz_0018f88_(piVar7,*(int *)((&PTR_PTR_803792c8)[iVar3 * 6] + (uVar1 & 3) * 4),
                  (float *)(piVar7 + 4));
      uVar9 = zz_0019338_(piVar7 + 2,(int)(&PTR_DAT_803792cc)[iVar3 * 6],(float *)(piVar7 + 7));
      iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
      iVar8 = iVar8 * 4 + 0xe0;
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                  *(int *)(param_9 + iVar8),(int)(char)(&DAT_803792b8)[iVar3 * 0x18],iVar4,iVar5,
                  uVar6,in_r9,in_r10);
      zz_0007cac_((double)(float)piVar7[7],*(int *)(param_9 + iVar8));
      iVar8 = (int)*(char *)(param_9 + 0x13);
    }
    iVar8 = iVar8 + 1;
  }
  return;
}



// ==== 801a4644  zz_01a4644_ ====

int zz_01a4644_(int param_1)

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
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar5);
      sVar1 = *(short *)(piVar2 + 8);
      *(short *)(piVar2 + 8) = sVar1 + 1;
      if (*(short *)((int)piVar2 + 0x22) <= (short)(sVar1 + 1)) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar3);
      }
      zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 4));
      zz_0019370_(piVar2 + 2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 7));
      zz_0007cac_((double)(float)piVar2[7],*(int *)(iVar4 + 0xe0));
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 801a470c  zz_01a470c_ ====

void zz_01a470c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,7);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x24;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 7;
    *(code **)(puVar1 + 0xc) = zz_01a4818_;
    *(code **)(puVar1 + 0x10c) = zz_01a4b18_;
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



// ==== 801a4818  zz_01a4818_ ====

void zz_01a4818_(int param_1)

{
  (*(code *)(&PTR_zz_01a4854__80379358)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a4854  zz_01a4854_ ====

void zz_01a4854_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  
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
    iVar4 = *(int *)(*(int *)(param_9 + 0x8c) + 0x54);
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    uVar3 = *(undefined4 *)(iVar4 + 0x24);
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar4 + 0x20);
    *(undefined4 *)(param_9 + 0x24) = uVar3;
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar4 + 0x28);
    *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
    *(code **)(param_9 + 0x100) = zz_01a4a40_;
    uVar5 = zz_0089100_(param_9,1,1);
    zz_01a4b9c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801a4944  zz_01a4944_ ====

void zz_01a4944_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0x8c);
  iVar3 = *(int *)(iVar4 + 0x54);
  uVar1 = *(undefined4 *)(iVar3 + 0x24);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar3 + 0x20);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar3 + 0x28);
  *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(iVar3 + 0xb4);
  zz_01a4cd4_(param_9);
  sVar2 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar2;
  if (sVar2 < 1) {
    zz_01a4b9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (('\x01' < *(char *)(iVar4 + 0x18)) || (*(short *)(iVar4 + 0x94) != *(short *)(param_9 + 0x94))
     ) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801a49e4  zz_01a49e4_ ====

void zz_01a49e4_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a49f8  zz_01a49f8_ ====

void zz_01a49f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a4a40  zz_01a4a40_ ====

void zz_01a4a40_(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_58 [3];
  float afStack_4c [14];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(param_1 + 0x54) + iVar6;
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar3 + 0x14),afStack_58);
      dVar8 = (double)*(float *)(iVar3 + 0xc);
      dVar9 = (double)*(float *)(iVar3 + 0x10);
      gnt4_PSMTXTrans_bl((double)*(float *)(iVar3 + 8),dVar8,dVar9,afStack_4c);
      zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x22));
      iVar2 = (int)*(short *)(iVar3 + 0x20);
      zz_00457d4_('x',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x20));
      pfVar1 = afStack_58;
      uVar7 = zz_00456a0_(afStack_4c,afStack_4c,pfVar1);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    iVar6 = iVar6 + 0x28;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 801a4b18  zz_01a4b18_ ====

void zz_01a4b18_(int param_1)

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



// ==== 801a4b9c  zz_01a4b9c_ ====

void zz_01a4b9c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar7 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar7) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & 1 << iVar7) == 0) {
      iVar5 = *(int *)(param_9 + 0x54);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
      piVar6 = (int *)(iVar5 + iVar7 * 0x28);
      *(undefined2 *)(param_9 + 0x1e) = 3;
      iVar4 = *(char *)(param_9 + 0x11) * 8;
      *(undefined1 *)(piVar6 + 9) = 0;
      *(undefined1 *)((int)piVar6 + 0x25) = *(undefined1 *)(iVar4 + -0x7fbca89d);
      iVar2 = *(int *)(param_9 + 0x24);
      piVar6[2] = *(int *)(param_9 + 0x20);
      piVar6[3] = iVar2;
      piVar6[4] = *(int *)(param_9 + 0x28);
      uVar3 = zz_00055fc_();
      *(short *)(piVar6 + 8) = (short)(uVar3 << 8);
      uVar3 = zz_00055fc_();
      *(short *)((int)piVar6 + 0x22) = (short)(uVar3 << 8);
      uVar8 = zz_0018f88_(piVar6,*(int *)(iVar4 + -0x7fbca89c),(float *)(piVar6 + 5));
      uVar3 = zz_00055fc_();
      cVar1 = (&DAT_80435760)[uVar3 % 3 + iVar4];
      iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
      zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  *(int *)(param_9 + iVar7 * 4 + 0xe0),(int)cVar1,iVar5,in_r7,in_r8,in_r9,in_r10);
      iVar7 = (int)*(char *)(param_9 + 0x13);
    }
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 801a4cd4  zz_01a4cd4_ ====

int zz_01a4cd4_(int param_1)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar4);
      cVar1 = *(char *)(piVar2 + 9);
      *(char *)(piVar2 + 9) = cVar1 + '\x01';
      if (*(char *)((int)piVar2 + 0x25) <= (char)(cVar1 + '\x01')) {
        *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar3);
      }
      piVar2[3] = (int)((float)piVar2[3] + FLOAT_8043b630);
      zz_0018fd8_(piVar2,(int)*(char *)(piVar2 + 9),(float *)(piVar2 + 5));
    }
    iVar4 = iVar4 + 0x28;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 801a4d9c  zz_01a4d9c_ ====

void zz_01a4d9c_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x407) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = zz_01a4e90_;
    *(code **)(puVar1 + 0x10c) = zz_01a50f8_;
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



// ==== 801a4e90  zz_01a4e90_ ====

void zz_01a4e90_(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_zz_01a4ee4__80379380)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801a4ee4  zz_01a4ee4_ ====

void zz_01a4ee4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
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
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(undefined1 *)(param_9 + 0x89) = 3;
  fVar1 = FLOAT_8043b638;
  uVar2 = DAT_8037936c;
  *(undefined4 *)(param_9 + 100) = DAT_80379368;
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = DAT_80379370;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(float *)(param_9 + 0x144) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),7,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 7;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),7,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_8043b63c,*(int *)(param_9 + 0xe4));
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),8,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 8;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),8,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043b63c,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_01a5024_(param_9);
  return;
}



// ==== 801a5024  zz_01a5024_ ====

void zz_01a5024_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar1 + 0x150) == '\0') {
    *(float *)(param_1 + 0x144) = (float)((double)*(float *)(param_1 + 0x144) + DOUBLE_8043b640);
  }
  if (*(char *)(iVar1 + 0x150) == '\x02') {
    *(float *)(param_1 + 0x144) = FLOAT_8043b638;
  }
  if (*(char *)(iVar1 + 0x150) == '\x01') {
    *(float *)(param_1 + 0x144) = FLOAT_8043b648;
  }
  if (FLOAT_8043b638 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = FLOAT_8043b638;
  }
  zz_0046588_((double)FLOAT_8043b64c,(float *)(param_1 + 100),
              (float *)(&DAT_80379368 + *(char *)(iVar1 + 0x6e9) * 3),(float *)(param_1 + 100));
  return;
}



// ==== 801a50c8  zz_01a50c8_ ====

void zz_01a50c8_(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  return;
}



// ==== 801a50d8  zz_01a50d8_ ====

void zz_01a50d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a50f8  zz_01a50f8_ ====

void zz_01a50f8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar1 + 0x150) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar5 = 0;
      uVar4 = 1;
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar5 = 1;
      uVar4 = 0x44;
      uVar3 = 0x44;
    }
    dVar6 = (double)*(float *)(param_1 + 0x144);
    dVar8 = dVar6;
    gnt4_PSMTXScale_bl(dVar6,dVar6,dVar6,afStack_48);
    pfVar2 = afStack_48;
    uVar7 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
    iVar1 = param_1 + iVar5 * 4;
    zz_00076d0_(uVar7,dVar6,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar1 + 0xe0),afStack_48,
                (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
    uVar7 = zz_00097b4_(*(int *)(iVar1 + 0xe0),uVar4);
    iVar1 = param_1 + iVar5 * 4;
    zz_00076d0_(uVar7,dVar6,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar1 + 0xe8),afStack_48,
                (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar1 + 0xe8),uVar3);
  }
  return;
}



// ==== 801a51cc  zz_01a51cc_ ====

void zz_01a51cc_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01a5454__80379390;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01a52c8__80379394;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_01a5330__80379398;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01a5334__8037939c;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01a53a8__803793a0;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01a53ac__803793a4;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01a53b0__803793a8;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01a53b4__803793ac;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_803793b0;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_01a53b8__803793b4;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_803793b8;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_803793bc;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_803793c0;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_803793c4;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_803793c8;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_803793cc;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80379448;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80379780;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80379f60;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bb714;
  *(undefined **)(param_1 + 0x27c) = &DAT_803796b0;
  return;
}



// ==== 801a52c8  zz_01a52c8_ ====

void zz_01a52c8_(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  for (sVar1 = 2; sVar1 < 4; sVar1 = sVar1 + 1) {
    zz_0147a54_(param_1,(char)sVar1);
  }
  return;
}



// ==== 801a5330  zz_01a5330_ ====

void zz_01a5330_(void)

{
  return;
}



// ==== 801a5334  zz_01a5334_ ====

void zz_01a5334_(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043b658) * FLOAT_8043b650);
  }
  return;
}



// ==== 801a53a8  zz_01a53a8_ ====

void zz_01a53a8_(void)

{
  return;
}



// ==== 801a53ac  zz_01a53ac_ ====

void zz_01a53ac_(void)

{
  return;
}



// ==== 801a53b0  zz_01a53b0_ ====

void zz_01a53b0_(void)

{
  return;
}



// ==== 801a53b4  zz_01a53b4_ ====

void zz_01a53b4_(void)

{
  return;
}



// ==== 801a53b8  zz_01a53b8_ ====

void zz_01a53b8_(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_zz_01a53f4__803793d0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801a53f4  zz_01a53f4_ ====

void zz_01a53f4_(void)

{
  return;
}



// ==== 801a53f8  zz_01a53f8_ ====

void zz_01a53f8_(int param_1)

{
  zz_0144dc4_(param_1,1);
  return;
}



// ==== 801a541c  zz_01a541c_ ====

void zz_01a541c_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x45);
  return;
}



// ==== 801a5448  zz_01a5448_ ====

void zz_01a5448_(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 0xff;
  return;
}



// ==== 801a5454  zz_01a5454_ ====

void zz_01a5454_(int param_1)

{
  (*(code *)(&PTR_zz_01a5490__803793e0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801a5490  zz_01a5490_ ====

void zz_01a5490_(int param_1)

{
  (*(code *)(&PTR_zz_01a54cc__803793ec)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801a54cc  zz_01a54cc_ ====

void zz_01a54cc_(int param_1)

{
  zz_014a200_(param_1,&DAT_80435768);
  return;
}



// ==== 801a54f0  zz_01a54f0_ ====

void zz_01a54f0_(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80435770);
  return;
}



// ==== 801a5514  zz_01a5514_ ====

void zz_01a5514_(int param_1)

{
  zz_0082824_(param_1,0x41);
  return;
}



// ==== 801a5538  zz_01a5538_ ====

void zz_01a5538_(int param_1)

{
  (*(code *)(&PTR_zz_01a5574__80379400)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801a5574  zz_01a5574_ ====

void zz_01a5574_(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 801a5598  zz_01a5598_ ====

void zz_01a5598_(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 801a55bc  zz_01a55bc_ ====

void zz_01a55bc_(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 801a55e0  zz_01a55e0_ ====

void zz_01a55e0_(int param_1,int param_2)

{
  undefined1 *puVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  
  cVar3 = '\0';
  for (iVar2 = *(int *)(&DAT_80435778 + param_2 * 8); 0 < iVar2; iVar2 = iVar2 - iVar4) {
    iVar4 = 8;
    if (iVar2 < 8) {
      iVar4 = iVar2;
    }
    puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,iVar4);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0x25;
      puVar1[0x11] = (char)param_2;
      puVar1[0x12] = cVar3;
      puVar1[0x13] = (char)iVar4;
      *(code **)(puVar1 + 0xc) = zz_01a5724_;
      *(code **)(puVar1 + 0x10c) = zz_01a5a0c_;
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
      *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_2 * 8 + -0x7fbca884);
      *(undefined4 *)(puVar1 + 0x54) = 0;
    }
    cVar3 = cVar3 + '\x01';
  }
  return;
}



// ==== 801a5724  zz_01a5724_ ====

void zz_01a5724_(int param_1)

{
  (*(code *)(&PTR_zz_01a5760__8037a990)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a5760  zz_01a5760_ ====

void zz_01a5760_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int *piVar4;
  undefined8 uVar5;
  
  uVar3 = *(char *)(param_9 + 0x13) * 0x24;
  if (uVar3 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar4 = zz_0006dc8_(uVar3);
    *(int **)(param_9 + 0xdc) = piVar4;
    if (piVar4 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    fVar1 = FLOAT_8043b660;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    fVar2 = FLOAT_8043b664;
    *(float *)(param_9 + 0xd4) = fVar1;
    *(float *)(param_9 + 0x44) = fVar2;
    *(code **)(param_9 + 0x100) = zz_01a5944_;
    uVar5 = zz_0089100_(param_9,1,1);
    FUN_801a5a90(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801a5830  zz_01a5830_ ====

void zz_01a5830_(int param_1)

{
  float fVar1;
  float fVar2;
  
  if (FLOAT_8043b668 < *(float *)(param_1 + 0xd4)) {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_8043b664;
  }
  fVar1 = FLOAT_8043b66c;
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x44);
  fVar2 = FLOAT_8043b664;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xd4) / fVar1;
  fVar1 = *(float *)(param_1 + 0x44);
  if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < FLOAT_8043b668)) {
    fVar2 = FLOAT_8043b668;
  }
  *(float *)(param_1 + 0x44) = fVar2;
  zz_01a5d90_(param_1);
  if ((*(float *)(param_1 + 0xd4) <= FLOAT_8043b668) || (*(short *)(param_1 + 0x1c) == 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801a58e8  zz_01a58e8_ ====

void zz_01a58e8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a58fc  zz_01a58fc_ ====

void zz_01a58fc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a5944  zz_01a5944_ ====

void zz_01a5944_(int param_1)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
      pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      dVar7 = (double)pfVar2[1];
      dVar8 = (double)pfVar2[2];
      gnt4_PSMTXTrans_bl((double)*pfVar2,dVar7,dVar8,afStack_48);
      zz_00457d4_('y',afStack_48,afStack_48,*(short *)((int)pfVar2 + 0x1e));
      iVar1 = (int)*(short *)(pfVar2 + 7);
      zz_00457d4_('x',afStack_48,afStack_48,*(short *)(pfVar2 + 7));
      pfVar2 = (float *)(param_1 + 0x58);
      uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                  (undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,in_r10);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 801a5a0c  zz_01a5a0c_ ====

void zz_01a5a0c_(int param_1)

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



// ==== 801a5a90  FUN_801a5a90 ====

/* WARNING: Removing unreachable block (ram,0x801a5d74) */
/* WARNING: Removing unreachable block (ram,0x801a5d6c) */
/* WARNING: Removing unreachable block (ram,0x801a5d64) */
/* WARNING: Removing unreachable block (ram,0x801a5d5c) */
/* WARNING: Removing unreachable block (ram,0x801a5d54) */
/* WARNING: Removing unreachable block (ram,0x801a5d4c) */
/* WARNING: Removing unreachable block (ram,0x801a5ac8) */
/* WARNING: Removing unreachable block (ram,0x801a5ac0) */
/* WARNING: Removing unreachable block (ram,0x801a5ab8) */
/* WARNING: Removing unreachable block (ram,0x801a5ab0) */
/* WARNING: Removing unreachable block (ram,0x801a5aa8) */
/* WARNING: Removing unreachable block (ram,0x801a5aa0) */

void FUN_801a5a90(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  float fVar2;
  uint uVar3;
  float fVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int *piVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  
  iVar9 = *(int *)(param_9 + 0x8c);
  iVar7 = 0;
  *(float *)(param_9 + 0xb4) = FLOAT_8043b668;
  iVar5 = iVar9;
  do {
    *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar5 + 0x114);
    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(iVar5 + 0x124);
    *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar5 + 0x134);
    dVar11 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
    iVar7 = iVar7 + 1;
    iVar5 = iVar5 + 4;
    *(float *)(param_9 + 0xb4) = (float)((double)*(float *)(param_9 + 0xb4) + dVar11);
  } while (iVar7 < 3);
  fVar2 = *(float *)(param_9 + 0xb4) / FLOAT_8043b670;
  *(float *)(param_9 + 0xb4) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  iVar5 = FUN_800452a0((double)*(float *)(param_9 + 0x38),(double)*(float *)(param_9 + 0x40));
  *(short *)(param_9 + 0x72) = (short)iVar5;
  dVar11 = (double)(*(float *)(param_9 + 0x38) * *(float *)(param_9 + 0x38) +
                   *(float *)(param_9 + 0x40) * *(float *)(param_9 + 0x40));
  if ((double)FLOAT_8043b668 < dVar11) {
    dVar12 = 1.0 / SQRT(dVar11);
    dVar12 = DOUBLE_8043b678 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_8043b680);
    dVar12 = DOUBLE_8043b678 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_8043b680);
    dVar11 = (double)(float)(dVar11 * DOUBLE_8043b678 * dVar12 *
                                      -(dVar11 * dVar12 * dVar12 - DOUBLE_8043b680));
    param_3 = DOUBLE_8043b680;
    param_4 = DOUBLE_8043b678;
  }
  iVar5 = FUN_800452a0(-(double)*(float *)(param_9 + 0x3c),dVar11);
  *(short *)(param_9 + 0x70) = (short)iVar5;
  dVar14 = (double)FLOAT_8043b688;
  iVar10 = 0;
  dVar15 = (double)FLOAT_8043b68c;
  dVar16 = (double)FLOAT_8043b690;
  dVar17 = (double)FLOAT_8043b694;
  dVar18 = (double)FLOAT_8043b664;
  iVar5 = param_9;
  dVar12 = DOUBLE_8043b698;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    pfVar8 = (float *)(*(int *)(param_9 + 0x54) + iVar10);
    *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
    piVar6 = (int *)(*(int *)(param_9 + 0xcc) + (iVar7 + *(char *)(param_9 + 0x12) * 8) * 0x10);
    fVar4 = (float)piVar6[1];
    fVar2 = (float)piVar6[2];
    pfVar8[3] = fVar4;
    pfVar8[4] = fVar2;
    pfVar8[5] = (float)piVar6[3];
    pfVar8[7] = *(float *)(param_9 + 0x70);
    gnt4_PSMTXMultVec_bl((float *)(iVar9 + 0x114),pfVar8 + 3,pfVar8);
    pfVar8[4] = (float)((double)pfVar8[4] + dVar14);
    gnt4_PSVECNormalize_bl(pfVar8 + 3,pfVar8 + 3);
    uVar3 = zz_00055fc_();
    gnt4_PSQUATScale_bl((double)(*(float *)(param_9 + 0xb4) *
                                *(float *)(&DAT_8037a9a0 + (uVar3 & 0xf) * 4)),pfVar8 + 3,pfVar8 + 3
                       );
    pfVar8[6] = (float)dVar15;
    uVar3 = zz_00055fc_();
    dVar13 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uVar3 & 0xff ^ 0x80000000)
                                            - dVar12) / dVar16);
    iVar1 = (int)(dVar17 * dVar13);
    *(short *)(pfVar8 + 8) = (short)iVar1;
    *(short *)((int)pfVar8 + 0x22) = (short)(int)(dVar17 * (double)(float)(dVar18 - dVar13));
    if ((uVar3 & 1) != 0) {
      *(short *)(pfVar8 + 8) = -*(short *)(pfVar8 + 8);
    }
    if ((uVar3 & 2) != 0) {
      *(short *)((int)pfVar8 + 0x22) = -*(short *)((int)pfVar8 + 0x22);
    }
    zz_0006fb4_((longlong)iVar1,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(iVar5 + 0xe0),*piVar6,fVar4,in_r7,in_r8,in_r9,in_r10);
    iVar10 = iVar10 + 0x24;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 801a5d90  zz_01a5d90_ ====

int zz_01a5d90_(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  iVar4 = 0;
  iVar3 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar3);
      gnt4_PSVECAdd_bl(pfVar1,pfVar1 + 3,pfVar1);
      pfVar1[4] = pfVar1[4] + pfVar1[6];
      *(short *)(pfVar1 + 7) = *(short *)(pfVar1 + 7) + *(short *)(pfVar1 + 8);
      *(short *)((int)pfVar1 + 0x1e) =
           *(short *)((int)pfVar1 + 0x1e) + *(short *)((int)pfVar1 + 0x22);
      if ((double)*(float *)(param_1 + 0x44) != (double)*(float *)(param_1 + 0x48)) {
        zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(iVar2 + 0xe0));
      }
      dVar5 = FUN_8003d964((double)FLOAT_8043b6a0,param_1,pfVar1);
      if ((double)pfVar1[1] <= dVar5) {
        *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar4);
      }
    }
    iVar3 = iVar3 + 0x24;
    iVar2 = iVar2 + 4;
    iVar4 = iVar4 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 801a5e88  zz_01a5e88_ ====

void zz_01a5e88_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,1,3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x26;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 3;
    *(code **)(puVar1 + 0xc) = zz_01a5f90_;
    *(code **)(puVar1 + 0x10c) = zz_01a63e0_;
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



// ==== 801a5f90  zz_01a5f90_ ====

void zz_01a5f90_(int param_1)

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
  (*(code *)(&PTR_zz_01a601c__8037a9e0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a601c  zz_01a601c_ ====

void zz_01a601c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  uint uVar6;
  int *piVar7;
  undefined4 extraout_r4;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  uVar6 = *(char *)(param_1 + 0x13) * 0xc;
  if (uVar6 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar7 = zz_0006dc8_(uVar6);
    *(int **)(param_1 + 0xdc) = piVar7;
    if (piVar7 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  fVar1 = FLOAT_8043b6a8;
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    dVar15 = (double)FLOAT_8043b6a8;
    *(undefined1 *)(param_1 + 0x18) = 1;
    fVar2 = FLOAT_8043b6ac;
    dVar14 = (double)FLOAT_8043b6ac;
    uVar9 = 3;
    *(undefined1 *)(param_1 + 0x19) = 0;
    fVar3 = FLOAT_8043b6b0;
    dVar13 = (double)FLOAT_8043b6b0;
    *(float *)(param_1 + 0xd8) = fVar1;
    fVar4 = FLOAT_8043b6b4;
    *(float *)(param_1 + 0xd4) = fVar1;
    fVar5 = FLOAT_8043b6b8;
    uVar8 = 1;
    iVar11 = (int)*(char *)(*(int *)(param_1 + 0x90) + 0x1afd);
    iVar10 = iVar11 + *(char *)(*(int *)(param_1 + 0x90) + 0x1afc) * 0x1000;
    *(short *)(param_1 + 0x1c) = (short)iVar10;
    *(float *)(param_1 + 0xb4) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x58) = fVar2;
    *(float *)(param_1 + 0x44) = fVar3;
    *(undefined1 *)(param_1 + 0x89) = 3;
    *(float *)(param_1 + 100) = fVar1;
    *(float *)(param_1 + 0x68) = fVar4;
    *(float *)(param_1 + 0x6c) = fVar5;
    *(code **)(param_1 + 0x100) = zz_01a62f4_;
    uVar12 = zz_0089100_(param_1,1,1);
    zz_01a6448_(uVar12,dVar13,dVar14,dVar15,in_f5,in_f6,in_f7,in_f8,param_1,extraout_r4,uVar8,uVar9,
                iVar10,iVar11,in_r9,in_r10);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
    zz_00f036c_(param_1,0xa8);
  }
  return;
}



// ==== 801a6150  zz_01a6150_ ====

void zz_01a6150_(int param_1)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  
  fVar2 = FLOAT_8043b6bc;
  if (*(float *)(param_1 + 0xd4) < FLOAT_8043b6bc) {
    fVar3 = *(float *)(param_1 + 0xd4) + FLOAT_8043b6b0;
    bVar4 = FLOAT_8043b6bc < fVar3;
    *(float *)(param_1 + 0xd4) = fVar3;
    if (bVar4) {
      *(float *)(param_1 + 0xd4) = fVar2;
    }
    *(float *)(param_1 + 0xb4) = FLOAT_8043b6ac + *(float *)(param_1 + 0xd4) / FLOAT_8043b6bc;
  }
  fVar2 = FLOAT_8043b6c0;
  if (*(char *)(param_1 + 0x19) == '\0') {
    if ((int)*(short *)(param_1 + 0x1c) !=
        (int)*(char *)(*(int *)(param_1 + 0x90) + 0x1afd) +
        *(char *)(*(int *)(param_1 + 0x90) + 0x1afc) * 0x1000) {
      *(undefined1 *)(param_1 + 0x19) = 1;
    }
  }
  else if (*(float *)(param_1 + 0xd8) < FLOAT_8043b6c0) {
    fVar3 = *(float *)(param_1 + 0xd8) + FLOAT_8043b6b0;
    bVar4 = FLOAT_8043b6c0 < fVar3;
    *(float *)(param_1 + 0xd8) = fVar3;
    if (bVar4) {
      *(float *)(param_1 + 0xd8) = fVar2;
    }
    *(float *)(param_1 + 0x44) = FLOAT_8043b6b0 - *(float *)(param_1 + 0xd8) / FLOAT_8043b6c0;
  }
  fVar3 = FLOAT_8043b6b0;
  uVar1 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  fVar2 = *(float *)(param_1 + 0x44);
  if ((fVar2 <= fVar3) && (fVar3 = fVar2, fVar2 < FLOAT_8043b6a8)) {
    fVar3 = FLOAT_8043b6a8;
  }
  *(float *)(param_1 + 0x44) = fVar3;
  zz_01a6500_(param_1);
  if (*(float *)(param_1 + 0x44) <= FLOAT_8043b6a8) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801a6298  zz_01a6298_ ====

void zz_01a6298_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a62ac  zz_01a62ac_ ====

void zz_01a62ac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a62f4  zz_01a62f4_ ====

void zz_01a62f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  float *pfVar2;
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
  float afStack_48 [14];
  
  iVar4 = *(int *)(param_9 + 0x8c);
  zz_00455fc_((float *)(iVar4 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),(float *)(param_9 + 0x114)
              ,(float *)(param_9 + 100));
  pfVar3 = (float *)(param_9 + 0x58);
  zz_00456a0_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),pfVar3);
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    if (iVar5 == 0) {
      param_2 = (double)*pfVar2;
      param_3 = param_2;
      uVar8 = zz_0045654_(param_2,param_2,param_2,(float *)(param_9 + 0x114),afStack_48);
    }
    else {
      sVar1 = *(short *)(pfVar2 + 1);
      iVar4 = (int)sVar1;
      pfVar3 = afStack_48;
      uVar8 = zz_00457d4_('z',(float *)(param_9 + 0x114),pfVar3,sVar1);
    }
    zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0xe0)
                ,afStack_48,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    iVar7 = iVar7 + 0xc;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 801a63e0  zz_01a63e0_ ====

void zz_01a63e0_(int param_1)

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



// ==== 801a6448  zz_01a6448_ ====

void zz_01a6448_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  
  iVar8 = 0;
  pcVar7 = &DAT_80435780;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
    if (iVar5 == 0) {
      *pfVar4 = FLOAT_8043b6b0;
    }
    else {
      uVar2 = zz_00055fc_();
      *(short *)(pfVar4 + 1) = (short)(uVar2 << 8);
      uVar1 = 0xfdde;
      if (iVar5 == 1) {
        uVar1 = 0x222;
      }
      *(undefined2 *)((int)pfVar4 + 6) = uVar1;
    }
    *(undefined2 *)(pfVar4 + 2) = 0;
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                          *(int *)(iVar6 + 0xe0),(int)*pcVar7,param_12,param_13,param_14,param_15,
                          param_16);
    iVar8 = iVar8 + 0xc;
    pcVar7 = pcVar7 + 1;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 801a6500  zz_01a6500_ ====

void zz_01a6500_(int param_1)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
    *(short *)(pfVar2 + 2) = *(short *)(pfVar2 + 2) + 1;
    if (iVar3 == 0) {
      fVar1 = FLOAT_8043b6b0;
      if (((uint)pfVar2[2] & 0x10000) != 0) {
        fVar1 = FLOAT_8043b6c4;
      }
      *pfVar2 = fVar1;
    }
    else {
      *(short *)(pfVar2 + 1) = *(short *)(pfVar2 + 1) + *(short *)((int)pfVar2 + 6);
    }
    zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(iVar4 + 0xe0));
    iVar5 = iVar5 + 0xc;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 801a65c4  zz_01a65c4_ ====

void zz_01a65c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  
  if (param_10 == 0) {
    iVar1 = *(int *)(param_9 + 0xc);
    uVar2 = gnt4_HSD_JObjSetFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x10);
    }
    uVar2 = gnt4_HSD_JObjClearFlags
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 8);
    }
    while (iVar1 != 0) {
      uVar2 = gnt4_HSD_JObjSetFlags
                        (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                         param_11,param_12,param_13,param_14,param_15,param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  else {
    iVar1 = *(int *)(param_9 + 0xc);
    uVar2 = gnt4_HSD_JObjClearFlags
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x10);
    }
    uVar2 = gnt4_HSD_JObjSetFlags
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 8);
    }
    while (iVar1 != 0) {
      uVar2 = gnt4_HSD_JObjClearFlags
                        (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                         param_11,param_12,param_13,param_14,param_15,param_16);
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 801a66d4  zz_01a66d4_ ====

void zz_01a66d4_(void)

{
  float fVar1;
  float fVar2;
  undefined1 uVar4;
  undefined4 uVar3;
  undefined1 *puVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  puVar8 = &DAT_8037ab38;
  puVar7 = &DAT_8037ab50;
  iVar6 = 0;
  do {
    puVar5 = zz_008893c_(2,0x39,0,0);
    if (puVar5 != (undefined1 *)0x0) {
      *puVar5 = 1;
      uVar4 = 0x19;
      puVar5[0x10] = 1;
      puVar5[0x11] = (char)iVar6;
      if (iVar6 != 0) {
        uVar4 = 6;
      }
      puVar5[0x12] = uVar4;
      fVar1 = FLOAT_8043b6c8;
      *(code **)(puVar5 + 0xc) = zz_01a6834_;
      fVar2 = FLOAT_8043b6cc;
      uVar3 = puVar8[1];
      *(undefined4 *)(puVar5 + 0x150) = *puVar8;
      *(undefined4 *)(puVar5 + 0x154) = uVar3;
      *(undefined4 *)(puVar5 + 0x158) = puVar8[2];
      *(undefined4 *)(puVar5 + 0x144) = *(undefined4 *)(puVar5 + 0x150);
      *(undefined4 *)(puVar5 + 0x148) = *(undefined4 *)(puVar5 + 0x154);
      *(undefined4 *)(puVar5 + 0x14c) = *(undefined4 *)(puVar5 + 0x158);
      *(undefined4 *)(puVar5 + 0x20) = *(undefined4 *)(puVar5 + 0x144);
      *(undefined4 *)(puVar5 + 0x24) = *(undefined4 *)(puVar5 + 0x148);
      *(undefined4 *)(puVar5 + 0x28) = *(undefined4 *)(puVar5 + 0x14c);
      uVar3 = puVar7[1];
      *(undefined4 *)(puVar5 + 0x174) = *puVar7;
      *(undefined4 *)(puVar5 + 0x178) = uVar3;
      *(undefined4 *)(puVar5 + 0x17c) = puVar7[2];
      *(undefined4 *)(puVar5 + 0x168) = *(undefined4 *)(puVar5 + 0x174);
      *(undefined4 *)(puVar5 + 0x16c) = *(undefined4 *)(puVar5 + 0x178);
      *(undefined4 *)(puVar5 + 0x170) = *(undefined4 *)(puVar5 + 0x17c);
      *(undefined4 *)(puVar5 + 0x15c) = *(undefined4 *)(puVar5 + 0x168);
      *(undefined4 *)(puVar5 + 0x160) = *(undefined4 *)(puVar5 + 0x16c);
      *(undefined4 *)(puVar5 + 0x164) = *(undefined4 *)(puVar5 + 0x170);
      *(float *)(puVar5 + 0x9c) = fVar1;
      *(float *)(puVar5 + 0xa0) = fVar2;
      *(float *)(puVar5 + 0xa4) = fVar1;
      if (puVar5[0x11] == '\x01') {
        *(undefined1 **)(DAT_80436354 + 0x1514) = puVar5;
      }
    }
    iVar6 = iVar6 + 1;
    puVar7 = puVar7 + 3;
    puVar8 = puVar8 + 3;
  } while (iVar6 < 2);
  return;
}



// ==== 801a6834  zz_01a6834_ ====

void zz_01a6834_(int param_1)

{
  (*(code *)(&PTR_zz_01a6870__8037ac1c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a6870  zz_01a6870_ ====

void zz_01a6870_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 *param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  fVar1 = FLOAT_8043b6d0;
  if (*(char *)(param_9 + 0x11) != '\0') {
    param_10 = 0x2c2c;
    iVar3 = *(int *)(DAT_80436354 + 0x118) * 0xc;
    param_13 = (undefined4 *)(&DAT_8037ab68 + iVar3);
    uVar2 = *(undefined4 *)(&DAT_8037ab6c + iVar3);
    *(undefined4 *)(param_9 + 0x174) = *param_13;
    *(undefined4 *)(param_9 + 0x178) = uVar2;
    *(undefined4 *)(param_9 + 0x17c) = *(undefined4 *)(&DAT_8037ab70 + iVar3);
    param_12 = *(undefined4 *)(param_9 + 0x174);
    *(undefined4 *)(param_9 + 0x15c) = param_12;
    *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x178);
    param_11 = *(undefined4 *)(param_9 + 0x17c);
    *(undefined4 *)(param_9 + 0x164) = param_11;
    *(float *)(param_9 + 0x188) = fVar1;
    *(float *)(param_9 + 0x180) = fVar1;
    *(undefined2 *)(param_9 + 0x18c) = 0x2c2c;
    *(undefined2 *)(param_9 + 0x70) = 0x2c2c;
    *(undefined2 *)(param_9 + 0x18e) = 0xe000;
    *(undefined2 *)(param_9 + 0x72) = 0xe000;
  }
  zz_01a6910_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a6910  zz_01a6910_ ====

void zz_01a6910_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(param_9 + 0x11) == '\0') {
    zz_01a6a38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    zz_01a6b20_(param_9);
  }
  gnt4_C_MTXLookAt_bl((float *)(param_9 + 0x114),(float *)(param_9 + 0x20),(float *)(param_9 + 0x9c)
                      ,(float *)(param_9 + 0x15c));
  iVar1 = param_9 + 0x114;
  if ((*(byte *)(param_9 + 0x12) & 1) != 0) {
    *(int *)(PTR_DAT_80433930 + 0x14) = iVar1;
    PTR_DAT_80433930[0xc] = 0xff;
  }
  if ((*(byte *)(param_9 + 0x12) & 2) != 0) {
    *(int *)(PTR_DAT_80433930 + 0x18) = iVar1;
    PTR_DAT_80433930[0xd] = 0xff;
  }
  if ((*(byte *)(param_9 + 0x12) & 4) != 0) {
    *(int *)(PTR_DAT_80433930 + 0x1c) = iVar1;
    PTR_DAT_80433930[0xe] = 0xff;
  }
  if ((*(byte *)(param_9 + 0x12) & 8) != 0) {
    *(int *)(PTR_DAT_80433930 + 0x20) = iVar1;
    PTR_DAT_80433930[0xf] = 0xff;
  }
  if ((*(byte *)(param_9 + 0x12) & 0x10) != 0) {
    *(int *)(PTR_DAT_80433930 + 0x24) = iVar1;
    PTR_DAT_80433930[0x10] = 0xff;
  }
  return;
}



// ==== 801a6a38  zz_01a6a38_ ====

void zz_01a6a38_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + -1;
      if (*(int *)(param_9 + 0x194) != 0) {
        zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                    *(int *)(&DAT_8031a074 + *(int *)(param_9 + 0x194) * 4),param_12,param_13,
                    param_14,param_15,param_16);
      }
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (*(int *)(param_9 + 0x194) != *(int *)(DAT_80436354 + 0x5c))) {
    uVar2 = 1;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    if (*(int *)(param_9 + 0x194) != 0) {
      uVar2 = 0x3c;
    }
    *(undefined2 *)(param_9 + 0x1c) = uVar2;
    zz_00e9b60_((double)FLOAT_8043b6c8,2,(int)*(short *)(param_9 + 0x1c),2);
    *(undefined4 *)(param_9 + 0x194) = *(undefined4 *)(DAT_80436354 + 0x5c);
  }
  return;
}



// ==== 801a6b20  zz_01a6b20_ ====

void zz_01a6b20_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_01a7000_(param_1);
    if (*(int *)(DAT_80436354 + 0x128) == 2) {
      if ((*(uint *)(DAT_80436354 + 0x14) & 0x800000) != 0) {
        *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + -0x400;
      }
      if ((*(uint *)(DAT_80436354 + 0x14) & 0x400000) != 0) {
        *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x400;
      }
      if ((*(uint *)(DAT_80436354 + 0x14) & 0x100000) != 0) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x200;
      }
      if ((*(uint *)(DAT_80436354 + 0x14) & 0x200000) != 0) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x200;
      }
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    zz_01a7000_(param_1);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x18c);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(param_1 + 400);
    *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x17c);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x168);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x16c);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x170);
    *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_1 + 0x188);
    *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_1 + 0x188);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x20) =
         (float)((double)*(float *)(param_1 + 0x180) * dVar3 + (double)*(float *)(param_1 + 0x15c));
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x28) =
         (float)((double)*(float *)(param_1 + 0x180) * dVar3 + (double)*(float *)(param_1 + 0x164));
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x70));
    *(float *)(param_1 + 0x24) =
         (float)((double)*(float *)(param_1 + 0x180) * dVar3 + (double)*(float *)(param_1 + 0x160));
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
  }
  iVar2 = (int)*(short *)(param_1 + 0x18c) - (int)*(short *)(param_1 + 0x70);
  *(short *)(param_1 + 0x70) =
       *(short *)(param_1 + 0x70) +
       ((short)((ulonglong)((longlong)iVar2 * 0x2aaaaaab) >> 0x20) -
       ((short)((short)(iVar2 / 0x60000) + (short)(iVar2 >> 0x1f)) >> 0xf));
  iVar2 = (int)*(short *)(param_1 + 0x18e) - (int)*(short *)(param_1 + 0x72);
  *(short *)(param_1 + 0x72) =
       *(short *)(param_1 + 0x72) +
       ((short)((ulonglong)((longlong)iVar2 * 0x2aaaaaab) >> 0x20) -
       ((short)((short)(iVar2 / 0x60000) + (short)(iVar2 >> 0x1f)) >> 0xf));
  zz_01a6cf4_(param_1);
  return;
}



// ==== 801a6cf4  zz_01a6cf4_ ====

void zz_01a6cf4_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x150) =
       (float)((double)*(float *)(param_1 + 0x188) * dVar4 + (double)*(float *)(param_1 + 0x174));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x158) =
       (float)((double)*(float *)(param_1 + 0x188) * dVar4 + (double)*(float *)(param_1 + 0x17c));
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x70));
  *(float *)(param_1 + 0x154) =
       (float)((double)*(float *)(param_1 + 0x188) * dVar4 + (double)*(float *)(param_1 + 0x178));
  fVar2 = FLOAT_8043b6d4;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if ((*(int *)(DAT_80436354 + 0x128) == 2) ||
       (*(float *)(param_1 + 0x188) == *(float *)(param_1 + 0x184))) {
      *(float *)(param_1 + 0x20) =
           (*(float *)(param_1 + 0x150) - *(float *)(param_1 + 0x20)) * FLOAT_8043b6d4 +
           *(float *)(param_1 + 0x20);
      *(float *)(param_1 + 0x24) =
           (*(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x24)) * fVar2 +
           *(float *)(param_1 + 0x24);
      *(float *)(param_1 + 0x28) =
           (*(float *)(param_1 + 0x158) - *(float *)(param_1 + 0x28)) * fVar2 +
           *(float *)(param_1 + 0x28);
      *(float *)(param_1 + 0x15c) =
           (*(float *)(param_1 + 0x174) - *(float *)(param_1 + 0x15c)) * fVar2 +
           *(float *)(param_1 + 0x15c);
      *(float *)(param_1 + 0x160) =
           (*(float *)(param_1 + 0x178) - *(float *)(param_1 + 0x160)) * fVar2 +
           *(float *)(param_1 + 0x160);
      *(float *)(param_1 + 0x164) =
           (*(float *)(param_1 + 0x17c) - *(float *)(param_1 + 0x164)) * fVar2 +
           *(float *)(param_1 + 0x164);
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
      *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x15c);
      *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x160);
      *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x164);
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    zz_0181fbc_(param_1);
  }
  iVar3 = zz_0181fd0_(param_1,0x20);
  if (iVar3 == 0) {
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x188) - *(float *)(param_1 + 0x184)),param_1)
    ;
    *(float *)(param_1 + 0x180) = (float)((double)*(float *)(param_1 + 0x184) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x150) - *(float *)(param_1 + 0x144)),param_1)
    ;
    *(float *)(param_1 + 0x20) = (float)((double)*(float *)(param_1 + 0x144) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x148)),param_1)
    ;
    *(float *)(param_1 + 0x24) = (float)((double)*(float *)(param_1 + 0x148) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x158) - *(float *)(param_1 + 0x14c)),param_1)
    ;
    *(float *)(param_1 + 0x28) = (float)((double)*(float *)(param_1 + 0x14c) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x174) - *(float *)(param_1 + 0x168)),param_1)
    ;
    *(float *)(param_1 + 0x15c) = (float)((double)*(float *)(param_1 + 0x168) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x178) - *(float *)(param_1 + 0x16c)),param_1)
    ;
    *(float *)(param_1 + 0x160) = (float)((double)*(float *)(param_1 + 0x16c) + dVar4);
    dVar4 = zz_01820b0_((double)(*(float *)(param_1 + 0x17c) - *(float *)(param_1 + 0x170)),param_1)
    ;
    *(float *)(param_1 + 0x164) = (float)((double)*(float *)(param_1 + 0x170) + dVar4);
  }
  else {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + -1;
    *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_1 + 0x188);
    *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_1 + 0x188);
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x150);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x154);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x158);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
    *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x17c);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x168);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x16c);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x170);
  }
  return;
}



// ==== 801a6fe0  FUN_801a6fe0 ====

void FUN_801a6fe0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a7000  zz_01a7000_ ====

void zz_01a7000_(int param_1)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar3 = *(int *)(DAT_80436354 + 0x118);
  if (iVar3 != 0xc) {
    if (iVar3 < 0xc) {
      if (10 < iVar3) {
        iVar3 = 1;
        goto LAB_801a7040;
      }
    }
    else if (iVar3 < 0xe) {
      iVar3 = 2;
      goto LAB_801a7040;
    }
  }
  iVar3 = 0;
LAB_801a7040:
  uVar5 = (&DAT_8037ac2c)[iVar3];
  *(undefined2 *)(param_1 + 0x18c) = (&DAT_8037ac38)[iVar3 * 2];
  *(undefined2 *)(param_1 + 0x18e) = (&DAT_8037ac3a)[iVar3 * 2];
  iVar4 = *(int *)(DAT_80436354 + 0x128);
  if (iVar4 != 3) {
    if (2 < iVar4) {
      return;
    }
    if (iVar4 != 0) {
      if (iVar4 < 0) {
        return;
      }
      iVar3 = *(int *)(DAT_80436354 + 0x118);
      bVar1 = *(byte *)(DAT_80436354 + iVar3 * 0x40 + *(int *)(DAT_80436354 + 0x9d0) +
                        *(int *)(DAT_80436354 + 0x9d4) + 0x174);
      *(float *)(param_1 + 0x188) = FLOAT_8043b6d0;
      uVar5 = DAT_8037ac08;
      cVar2 = (&PTR_DAT_80358be4)[(uint)bVar1 * 7][1];
      if (cVar2 != '\x0e') {
        if (cVar2 < '\x0e') {
          if ('\f' < cVar2) {
            *(float *)(param_1 + 0x188) = FLOAT_8043b6d8;
            uVar5 = DAT_8037abf0;
            *(undefined4 *)(param_1 + 0x174) = DAT_8037abec;
            *(undefined4 *)(param_1 + 0x178) = uVar5;
            *(undefined4 *)(param_1 + 0x17c) = DAT_8037abf4;
            return;
          }
        }
        else if (cVar2 < '\x10') {
          *(undefined4 *)(param_1 + 0x174) = DAT_8037ac04;
          *(undefined4 *)(param_1 + 0x178) = uVar5;
          *(undefined4 *)(param_1 + 0x17c) = DAT_8037ac0c;
          *(undefined2 *)(param_1 + 0x18c) = DAT_8037ac40;
          *(undefined2 *)(param_1 + 0x18e) = DAT_8037ac42;
          return;
        }
      }
      iVar3 = iVar3 * 0xc;
      uVar5 = *(undefined4 *)(&DAT_8037ab6c + iVar3);
      *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(&DAT_8037ab68 + iVar3);
      *(undefined4 *)(param_1 + 0x178) = uVar5;
      *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(&DAT_8037ab70 + iVar3);
      return;
    }
  }
  *(undefined4 *)(param_1 + 0x188) = uVar5;
  uVar5 = (&DAT_8037ac48)[iVar3 * 3];
  *(undefined4 *)(param_1 + 0x174) = (&DAT_8037ac44)[iVar3 * 3];
  *(undefined4 *)(param_1 + 0x178) = uVar5;
  *(undefined4 *)(param_1 + 0x17c) = (&DAT_8037ac4c)[iVar3 * 3];
  return;
}



// ==== 801a71b0  zz_01a71b0_ ====

void zz_01a71b0_(void)

{
  zz_01a66d4_();
  zz_01a7208_();
  zz_01a7868_();
  zz_01a8058_();
  zz_01a8508_();
  zz_01b3a24_();
  zz_01c8e2c_();
  zz_01adc78_();
  zz_01a8d20_();
  zz_01a8880_();
  zz_01a996c_();
  zz_01a933c_();
  zz_01ac2cc_();
  zz_01e24e0_();
  zz_01a73d4_();
  return;
}



// ==== 801a7208  zz_01a7208_ ====

void zz_01a7208_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037ac68; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(2,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01a7288_;
      *(code **)(iVar2 + 0x10c) = zz_01a73b4_;
    }
  }
  return;
}



// ==== 801a7288  zz_01a7288_ ====

void zz_01a7288_(int param_1)

{
  (*(code *)(&PTR_zz_01a72c4__8037acb8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a72c4  zz_01a72c4_ ====

void zz_01a72c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b6e0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 801a7348  zz_01a7348_ ====

void zz_01a7348_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b6e8;
  if (*(char *)(param_1 + 0x11) == '\0') {
    return;
  }
  *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - FLOAT_8043b6e4;
  if (fVar1 <= *(float *)(param_1 + 100)) {
    return;
  }
  *(float *)(param_1 + 100) = FLOAT_8043b6ec;
  return;
}



// ==== 801a7380  zz_01a7380_ ====

void zz_01a7380_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a7394  zz_01a7394_ ====

void zz_01a7394_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a73b4  zz_01a73b4_ ====

void zz_01a73b4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a73d4  zz_01a73d4_ ====

void zz_01a73d4_(void)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x39,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = zz_01a7438_;
    *(code **)(puVar1 + 0x10c) = zz_01a74c4_;
  }
  *(undefined4 *)(DAT_80436354 + 0x2c) = 0;
  return;
}



// ==== 801a7438  zz_01a7438_ ====

void zz_01a7438_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x18);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x18) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined1 *)(param_1 + 0x82) = 4;
  }
  if (*(int *)(DAT_80436354 + 0x2c) == 0) {
    if (0 < *(short *)(param_1 + 0x1c)) {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -0x20;
      return;
    }
    *(undefined2 *)(param_1 + 0x1c) = 0;
    return;
  }
  if (*(short *)(param_1 + 0x1c) < 0xa0) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 0x20;
    return;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0xa0;
  return;
}



// ==== 801a74c4  zz_01a74c4_ ====

void zz_01a74c4_(int param_1)

{
  uRam8043578f = (undefined1)*(ushort *)(param_1 + 0x1c);
  if ((*(ushort *)(param_1 + 0x1c) & 0xff) != 0) {
    DAT_803c1140 = &DAT_8037acc8;
    DAT_803c1144 = 0;
    DAT_803c1150 = &DAT_8043578c;
    DAT_803c1154 = &DAT_80435788;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    FUN_80051998(-0x7fc3eed0);
  }
  return;
}



// ==== 801a7538  zz_01a7538_ ====

void zz_01a7538_(undefined1 param_1,undefined4 *param_2)

{
  zz_01a7560_(param_1,param_2,1,0xb);
  return;
}



// ==== 801a7560  zz_01a7560_ ====

void zz_01a7560_(undefined1 param_1,undefined4 *param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,0x39,1,param_3);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = param_1;
    puVar2[0x11] = (char)param_2[1];
    *(undefined4 *)(puVar2 + 0x144) = *param_2;
    uVar1 = param_2[2];
    *(undefined4 *)(puVar2 + 100) = uVar1;
    *(undefined4 *)(puVar2 + 0x148) = uVar1;
    uVar1 = param_2[3];
    *(undefined4 *)(puVar2 + 0x68) = uVar1;
    *(undefined4 *)(puVar2 + 0x14c) = uVar1;
    uVar1 = param_2[4];
    *(undefined4 *)(puVar2 + 0x6c) = uVar1;
    *(undefined4 *)(puVar2 + 0x150) = uVar1;
    *(undefined4 *)(puVar2 + 0x154) = (&DAT_803bb32c)[param_4 * 2];
    *(undefined4 *)(puVar2 + 400) = *(undefined4 *)(DAT_80436354 + 0x44);
  }
  return;
}



// ==== 801a761c  zz_01a761c_ ====

void zz_01a761c_(undefined1 param_1,undefined4 *param_2,int param_3)

{
  zz_01a7560_(param_1,param_2,param_3,0xb);
  return;
}



// ==== 801a7640  nlQSort<20AnimAudioEventLookup>(AnimAudioEventLookup ====

void nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup
               (undefined1 param_1,undefined4 *param_2,int param_3)

{
  zz_01a7560_(param_1,param_2,1,param_3);
  return;
}



// ==== 801a7668  zz_01a7668_ ====

void zz_01a7668_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x170) + 1;
  *(int *)(param_1 + 0x170) = iVar1;
  if (iVar1 < param_2) {
    return;
  }
  *(undefined4 *)(param_1 + 0x170) = 0;
  return;
}



// ==== 801a7688  zz_01a7688_ ====

void zz_01a7688_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x154),*(int *)(param_9 + param_10 * 4 + 0xe0),
              *(int *)(param_9 + 0x144),param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a76c0  zz_01a76c0_ ====

void zz_01a76c0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0x1c) = param_10;
  zz_00070e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x154),*(int *)(param_9 + 0xe0),*(int *)(param_9 + 0x144),0,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a76fc  zz_01a76fc_ ====

void zz_01a76fc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = param_9 + param_10 * 4;
  uVar2 = zz_00087d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x154),*(int *)(iVar1 + 0xe0),param_11,param_12,param_13,
                      param_14,param_15,param_16);
  uVar2 = zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007bb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0xe0),
              (undefined4 *)(param_9 + 0x58),param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a7754  zz_01a7754_ ====

void zz_01a7754_(int param_1,short param_2)

{
  int iVar1;
  float afStack_28 [7];
  
  iVar1 = *(int *)(DAT_80436354 + 0x1514);
  gnt4_PSVECSubtract_bl((float *)(iVar1 + 0x20),(float *)(param_1 + 0x20),afStack_28);
  zz_0045ef4_((float *)(param_1 + 0x114),5,afStack_28,iVar1 + 0x9c);
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),param_2);
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 801a77e8  zz_01a77e8_ ====

void zz_01a77e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(param_9 + 0xe0);
  if (*(int *)(param_9 + 0x174) == 1) {
    param_1 = zz_0007c54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x174) = 2;
  }
  if (*(int *)(param_9 + 0x174) == 2) {
    param_1 = zz_0007cac_((double)*(float *)(param_9 + 0x178),iVar1);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}



// ==== 801a7868  zz_01a7868_ ====

void zz_01a7868_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037acd8; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(10,piVar1);
    if (iVar2 != 0) {
      *(undefined1 *)(iVar2 + 0x12) = 0;
      *(code **)(iVar2 + 0xc) = zz_01a7960_;
      *(code **)(iVar2 + 0x10c) = zz_01a7e4c_;
    }
    *(int *)(DAT_80436354 + *(char *)(iVar2 + 0x11) * 4 + 0x984) = iVar2;
  }
  for (piVar1 = &DAT_8037acd8; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(10,piVar1);
    if (iVar2 != 0) {
      *(undefined1 *)(iVar2 + 0x12) = 1;
      *(code **)(iVar2 + 0xc) = zz_01a7960_;
      *(code **)(iVar2 + 0x10c) = zz_01a7e4c_;
    }
  }
  return;
}



// ==== 801a7960  zz_01a7960_ ====

void zz_01a7960_(int param_1)

{
  (*(code *)(&PTR_zz_01a799c__8037ae34)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a799c  zz_01a799c_ ====

void zz_01a799c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  float *pfVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  pfVar4 = (float *)0x1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b6f0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar5 = zz_01a7688_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4
                      ,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_01a65c4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),(int)*(char *)(param_9 + 0x12),(undefined *)pfVar4,
                      param_12,param_13,param_14,param_15,param_16);
  uVar3 = extraout_r4;
  if (*(int *)(DAT_80436354 + 0x128) != 0) {
    iVar2 = zz_01a7f10_(param_9);
    if (iVar2 == 0) {
      *(undefined1 *)(param_9 + 0x19) = 2;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      uVar5 = zz_01a7f60_(param_9);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(param_9 + 0x164);
      *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(param_9 + 0x168);
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(param_9 + 0x16c);
      uVar3 = extraout_r4_01;
    }
    else {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      uVar5 = zz_01a7e7c_(param_9);
      uVar3 = extraout_r4_00;
    }
  }
  zz_01a7a98_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,pfVar4,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a7a98  zz_01a7a98_ ====

void zz_01a7a98_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  double dVar2;
  
  if (*(char *)(param_9 + 0x11) == '\v') {
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + 0x40;
  }
  (*(code *)(&PTR_zz_01a7b70__8037ae44)[*(char *)(param_9 + 0x19)])(param_9);
  *(int *)(param_9 + 0x170) = *(int *)(param_9 + 0x170) + 0x200;
  if (*(char *)(param_9 + 0x82) != '\0') {
    fVar1 = FLOAT_8043b6f4;
    if (*(int *)(DAT_80436354 + 0x40) != 2) {
      dVar2 = zz_0045204_((short)*(undefined4 *)(param_9 + 0x170));
      param_2 = (double)FLOAT_8043b6f8;
      fVar1 = (float)(param_2 * dVar2 +
                     (double)(float)(param_2 +
                                    (double)*(float *)(&DAT_8037ae18 +
                                                      (uint)*(byte *)(DAT_80436354 +
                                                                      *(char *)(param_9 + 0x11) +
                                                                     0x130) * 4)));
    }
    zz_01a76fc_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801a7b70  zz_01a7b70_ ====

void zz_01a7b70_(int param_1)

{
  int iVar1;
  
  zz_01a7e7c_(param_1);
  if (*(int *)(DAT_80436354 + 0x128) == 1) {
    iVar1 = zz_01a7f10_(param_1);
    if (iVar1 == 0) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x02';
    }
    else {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  return;
}



// ==== 801a7be0  zz_01a7be0_ ====

void zz_01a7be0_(int param_1)

{
  char cVar1;
  short sVar2;
  
  zz_01a7e7c_(param_1);
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0x20;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 0x20;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (0 < sVar2) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined4 *)(DAT_80436354 + 0x128) = 2;
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined4 *)(DAT_80436354 + 0x128) = 0;
  }
  return;
}



// ==== 801a7cc0  zz_01a7cc0_ ====

void zz_01a7cc0_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    zz_01a7e7c_(param_1);
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        zz_01a7f60_(param_1);
        zz_0181fbc_(param_1);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_1,0x20);
      if (iVar2 != 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
      dVar3 = zz_01820b0_((double)(*(float *)(param_1 + 0x164) - *(float *)(param_1 + 0x148)),
                          param_1);
      *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
      dVar3 = zz_01820b0_((double)(*(float *)(param_1 + 0x16c) - *(float *)(param_1 + 0x150)),
                          param_1);
      *(float *)(param_1 + 0x6c) = (float)((double)*(float *)(param_1 + 0x150) + dVar3);
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_1,0x20);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  dVar3 = zz_01820b0_((double)(*(float *)(param_1 + 0x148) - *(float *)(param_1 + 0x164)),param_1);
  *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x164) + dVar3);
  dVar3 = zz_01820b0_((double)(*(float *)(param_1 + 0x150) - *(float *)(param_1 + 0x16c)),param_1);
  *(float *)(param_1 + 0x6c) = (float)((double)*(float *)(param_1 + 0x16c) + dVar3);
  return;
}



