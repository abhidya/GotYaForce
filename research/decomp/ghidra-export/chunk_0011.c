// ==== 80076fb0  FUN_80076fb0 ====

void FUN_80076fb0(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437848;
  dVar2 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x50) = FLOAT_80437848;
  *(float *)(param_1 + 0x48) = fVar1;
  zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
  zz_0076c80_(param_1);
  fVar1 = FLOAT_80437848;
  *(float *)(param_1 + 0x4c) = FLOAT_8043784c;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 80077018  FUN_80077018 ====

void FUN_80077018(int param_1)

{
  int iVar1;
  
  zz_006660c_(param_1);
  zz_007933c_(param_1,0x81);
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_80437854) {
    *(float *)(param_1 + 0x44) = FLOAT_80437854;
  }
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00679d0_(param_1);
  if (iVar1 != 0) {
    zz_00b22f4_(param_1);
  }
  if (((*(char *)(param_1 + 0x541) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x03')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      zz_0082824_(param_1,0xc);
    }
    *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
  }
  if ((*(char *)(param_1 + 0x1cee) != '\0') || (*(char *)(param_1 + 0x1cef) == -1)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (*(char *)(param_1 + 0x5e4) == ',') {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80077144  FUN_80077144 ====

void FUN_80077144(int param_1)

{
  if (*(char *)(param_1 + 0x581) != '\x05') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80437840) * FLOAT_80437838);
  }
  (*(code *)(&PTR_FUN_802d5f38)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800771c4  FUN_800771c4 ====

void FUN_800771c4(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5f50)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80077214  FUN_80077214 ====

void FUN_80077214(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80437848;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar2;
  *(undefined2 *)(param_1 + 0x548) = 0x14;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x544) = 0;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x544);
  dVar4 = (double)FLOAT_8043784c;
  *(char *)(param_1 + 0x544) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800772fc  FUN_800772fc ====

void FUN_800772fc(int param_1)

{
  float fVar1;
  float fVar2;
  short sVar4;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  sVar4 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar4;
  if ((sVar4 < 1) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80437858;
    fVar1 = FLOAT_80437848;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80077390  FUN_80077390 ====

void FUN_80077390(int param_1)

{
  char cVar1;
  short sVar3;
  uint uVar2;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_00b22f4_(param_1);
  zz_004cd24_(param_1,0xf);
  sVar3 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar3;
  if ((sVar3 < 1) || (uVar2 = FUN_80066838((double)FLOAT_8043785c,param_1), uVar2 != 0)) {
    dVar4 = (double)FLOAT_8043784c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    cVar1 = *(char *)(param_1 + 0x544);
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    *(char *)(param_1 + 0x746) = *(char *)(param_1 + 0x746) + '\x01';
    *(undefined1 *)(param_1 + 0x545) = 0;
  }
  return;
}



// ==== 8007745c  FUN_8007745c ====

void FUN_8007745c(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  uVar2 = 1;
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    zz_0077608_(param_1,1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (*(char *)(param_1 + 0x1cef) == -1) {
      uVar2 = 3;
      if (*(char *)(param_1 + 0x745) < '\x01') {
        if (*(char *)(param_1 + 0x545) == '\0') {
          if (*(char *)(param_1 + 0x1cee) != '\0') {
            zz_004beb8_((double)FLOAT_8043784c,param_1,0xf,3,7,0xffffffff,0xffffffff);
            *(undefined1 *)(param_1 + 0x545) = 1;
          }
        }
        else {
          uVar2 = 1;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x745) = 0;
        zz_00b2190_(param_1,0);
        if (*(char *)(param_1 + 0x746) < '\b') {
          if (*(char *)(param_1 + 0x544) == '\x06') {
            *(undefined1 *)(param_1 + 0x544) = 2;
          }
        }
        else {
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
          *(undefined1 *)(param_1 + 0x543) = 0;
          *(undefined1 *)(param_1 + 0x544) = 6;
        }
        dVar3 = (double)FLOAT_8043784c;
        *(undefined1 *)(param_1 + 0x545) = 0;
        cVar1 = *(char *)(param_1 + 0x544);
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
        *(char *)(param_1 + 0x746) = *(char *)(param_1 + 0x746) + '\x01';
      }
    }
    zz_0077608_(param_1,uVar2);
  }
  return;
}



// ==== 800775e4  FUN_800775e4 ====

void FUN_800775e4(int param_1)

{
  zz_0077608_(param_1,1);
  return;
}



// ==== 80077608  zz_0077608_ ====

void zz_0077608_(int param_1,uint param_2)

{
  float fVar1;
  float fVar2;
  
  if ((param_2 & 1) != 0) {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar2 = FLOAT_80437858;
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    fVar1 = FLOAT_80437848;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
  }
  if (FLOAT_8043785c <= *(float *)(param_1 + 0x764)) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437864;
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437860;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437860;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (((param_2 & 2) == 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80077720  FUN_80077720 ====

void FUN_80077720(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5f64)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80077770  FUN_80077770 ====

void FUN_80077770(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80437848;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_80437868;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437868;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_004beb8_((double)FLOAT_8043784c,param_1,0xf,3,0,0xffffffff,0xffffffff);
  return;
}



// ==== 80077864  FUN_80077864 ====

void FUN_80077864(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  
  fVar1 = FLOAT_80437868;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437868;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  sVar5 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar5;
  if ((sVar5 < 1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0x1e;
    fVar3 = FLOAT_80437870;
    fVar2 = FLOAT_80437848;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = (FLOAT_8043786c * fVar1) / FLOAT_80437858;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 80077970  FUN_80077970 ====

void FUN_80077970(int param_1)

{
  short sVar2;
  uint uVar1;
  double dVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  zz_00b22f4_(param_1);
  sVar2 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar2;
  if ((sVar2 < 1) || (uVar1 = FUN_80066838((double)FLOAT_80437870,param_1), 0 < (int)uVar1)) {
    dVar3 = (double)FLOAT_8043784c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80077a14  FUN_80077a14 ====

void FUN_80077a14(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437838;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x6eb) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80077a9c  FUN_80077a9c ====

void FUN_80077a9c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5f74)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80077aec  FUN_80077aec ====

void FUN_80077aec(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x558) = FLOAT_80437874;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,8,0xffffffff,0xffffffff);
  return;
}



// ==== 80077b9c  FUN_80077b9c ====

void FUN_80077b9c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_80437848;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_80437850;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = FUN_800669d0(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80437878;
    fVar1 = FLOAT_80437870;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    if (fVar1 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 80077c2c  FUN_80077c2c ====

void FUN_80077c2c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_1c);
  gnt4_PSVECMag_bl(&local_1c);
  fVar1 = FLOAT_80437848;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) = FLOAT_80437884;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar2 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_1c = *(float *)(iVar2 + 0x8e0);
    local_18 = *(float *)(iVar2 + 0x8f0);
    local_14 = *(undefined4 *)(iVar2 + 0x900);
    local_28 = *(float *)(param_1 + 0x518);
    local_20 = *(undefined4 *)(param_1 + 0x520);
    local_24 = FLOAT_80437858 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
    fVar1 = FLOAT_80437848;
    *(float *)(param_1 + 0x48) = local_18 * FLOAT_8043787c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_18 = fVar1;
    dVar3 = gnt4_PSVECMag_bl(&local_1c);
    fVar1 = FLOAT_80437880;
    *(float *)(param_1 + 0x44) = (float)(dVar3 * (double)FLOAT_8043787c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80437848;
  if ((*(char *)(param_1 + 0x1d9) == '\0') &&
     (*(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     fVar1 < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar3 = (double)FLOAT_8043784c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,9,0xffffffff,0xffffffff);
  return;
}



// ==== 80077dd8  FUN_80077dd8 ====

void FUN_80077dd8(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80437848;
    if (*(float *)(param_1 + 0x44) < FLOAT_80437848) {
      *(float *)(param_1 + 0x44) = FLOAT_80437848;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_80437888 + *(float *)(param_1 + 0x1dc8);
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80077e68  FUN_80077e68 ====

void FUN_80077e68(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5f84)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80077eb8  FUN_80077eb8 ====

void FUN_80077eb8(int param_1)

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
  dVar2 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x558) = FLOAT_80437874;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,0xb,0xffffffff,0xffffffff);
  return;
}



// ==== 80077f74  FUN_80077f74 ====

void FUN_80077f74(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_006660c_(param_1);
  fVar2 = FLOAT_80437848;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_80437850;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = FUN_800669d0(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80437878;
    fVar1 = FLOAT_80437858;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    if (*(float *)(param_1 + 0x44) < fVar1) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    fVar1 = FLOAT_80437870;
    *(float *)(param_1 + 0x4c) = FLOAT_80437838;
    if (fVar1 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 80078020  FUN_80078020 ====

void FUN_80078020(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  float fStack_38;
  float local_34;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    FUN_80067310((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (*(char *)(param_1 + 0x541) == '\0') {
      zz_006660c_(param_1);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      if (*(int *)(param_1 + 0xcc) != 0) {
        iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
        local_20 = *(float *)(iVar5 + 0x8e0);
        local_1c = *(undefined4 *)(iVar5 + 0x8f0);
        local_18 = *(undefined4 *)(iVar5 + 0x900);
        local_2c = *(float *)(param_1 + 0x518);
        local_28 = *(undefined4 *)(param_1 + 0x51c);
        local_24 = *(undefined4 *)(param_1 + 0x520);
        gnt4_PSVECSubtract_bl(&local_2c,&local_20,&fStack_38);
        fVar2 = FLOAT_80437848;
        *(float *)(param_1 + 0x48) = local_34 * FLOAT_8043787c;
        *(float *)(param_1 + 0x50) = fVar2;
      }
      uVar4 = FUN_80066838((double)FLOAT_80437874,param_1);
      if (uVar4 != 0) {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
    }
    iVar5 = FUN_800452a0((double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
    sVar3 = -(short)iVar5 - *(short *)(param_1 + 0x18da);
    if ((short)-(short)iVar5 < 1) {
      if (sVar3 < -0x38e) {
        sVar3 = -0x38e;
      }
    }
    else if (0x38e < sVar3) {
      sVar3 = 0x38e;
    }
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + sVar3;
  }
  zz_004cd24_(param_1,0xf);
  if (FLOAT_80437884 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_80437884;
    *(float *)(param_1 + 0x4c) = FLOAT_80437848;
  }
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80437848;
  if ((iVar5 == 1) && (*(char *)(param_1 + 0x542) == '\0')) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  fVar2 = FLOAT_80437848;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004cff4_(param_1,0xf);
  }
  return;
}



// ==== 8007821c  FUN_8007821c ====

void FUN_8007821c(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    fVar1 = FLOAT_80437888;
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800782ac  FUN_800782ac ====

void FUN_800782ac(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80437840) * FLOAT_80437838);
  (*(code *)(&PTR_FUN_804338c0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8007831c  FUN_8007831c ====

void FUN_8007831c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5f94)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007836c  FUN_8007836c ====

void FUN_8007836c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  
  *(float *)(param_1 + 0x80c) = FLOAT_80437848;
  fVar1 = FLOAT_80437884;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined1 *)(param_1 + 0x543) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 10;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    zz_006660c_(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  fVar1 = FLOAT_80437838;
  *(float *)(param_1 + 0x44) = FLOAT_8043788c;
  fVar2 = FLOAT_80437848;
  *(float *)(param_1 + 0x4c) = fVar1;
  fVar1 = FLOAT_80437890;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 != 0) {
    zz_00b22f4_(param_1);
  }
  dVar5 = (double)FLOAT_8043784c;
  *(undefined1 *)(param_1 + 0x544) = 0;
  zz_004beb8_(dVar5,param_1,3,4,0,0xffffffff,0xffffffff);
  return;
}



// ==== 8007849c  FUN_8007849c ====

void FUN_8007849c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x543) == '\0') && (*(char *)(param_1 + 0x1d9) != '\0')) {
    if (*(char *)(param_1 + 0x542) < '\x02') {
      zz_01005ec_(param_1,0);
      *(undefined1 *)(param_1 + 0x6f7) = 0x38;
    }
    fVar2 = FLOAT_80437848;
    *(float *)(param_1 + 0x44) = FLOAT_80437894;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined1 *)(param_1 + 0x542) = 3;
    *(undefined1 *)(param_1 + 0x543) = 1;
  }
  if (*(char *)(param_1 + 0x544) == '\x01') {
    if (*(char *)(param_1 + 0x541) == '\0') {
      zz_006660c_(param_1);
      dVar7 = (double)FLOAT_80437874;
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      uVar5 = FUN_80066838(dVar7,param_1);
      if (uVar5 != 0) {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
    }
    zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar6 = zz_00677b0_(param_1);
  if (iVar6 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_80437894;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_0067754_(param_1,(short *)(param_1 + 0x72),0x3000);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
        *(undefined1 *)(param_1 + 0x542) = 1;
        *(undefined1 *)(param_1 + 0x544) = 1;
      }
    }
    else if ((-1 < cVar1) && (*(char *)(param_1 + 0x1cee) != '\0')) {
      *(char *)(param_1 + 0x542) = cVar1 + '\x01';
      zz_01005ec_(param_1,0);
      *(undefined1 *)(param_1 + 0x6f7) = 0x38;
    }
  }
  else {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) goto LAB_80078698;
      *(char *)(param_1 + 0x542) = cVar1 + '\x01';
      fVar3 = FLOAT_80437898;
      *(float *)(param_1 + 0x48) = fVar2;
      fVar2 = FLOAT_80437848;
      *(float *)(param_1 + 0x50) = fVar3;
      *(float *)(param_1 + 0x4c) = fVar2;
    }
    if (((*(uint *)(param_1 + 0x5d4) & 0x80) != 0) && (0 < *(short *)(param_1 + 0x54a))) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) + FLOAT_80437850;
      *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
    }
    zz_0067754_(param_1,(short *)(param_1 + 0x72),0x3000);
  }
LAB_80078698:
  fVar3 = FLOAT_804378a0;
  fVar2 = FLOAT_8043789c;
  dVar7 = (double)FLOAT_80437848;
  if ((double)*(float *)(param_1 + 0x558) <= dVar7) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar8 = DOUBLE_80437840;
    *(undefined1 *)(param_1 + 0x542) = 0;
    fVar4 = FLOAT_804378a4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    fVar2 = fVar4 * (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72) ^ 0x80000000
                                            ) - dVar8);
    dVar9 = (double)fVar2;
    *(float *)(param_1 + 0x170) = fVar2;
    dVar8 = (double)(fVar4 * (float)((double)CONCAT44(0x43300000,
                                                      (int)*(short *)(param_1 + 0x5ae) ^ 0x80000000)
                                    - dVar8));
    if (dVar9 < dVar7) {
      dVar9 = (double)(float)(DOUBLE_804378a8 + dVar9);
    }
    if (dVar8 < (double)FLOAT_80437848) {
      dVar8 = (double)(float)(DOUBLE_804378a8 + dVar8);
    }
    if (dVar8 < dVar9) {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (FLOAT_804378b4 - (float)(dVar9 - dVar8));
    }
    else {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (float)(dVar8 - dVar9);
    }
    *(undefined1 *)(param_1 + 0x175) = 0;
  }
  return;
}



// ==== 80078798  FUN_80078798 ====

void FUN_80078798(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  double dVar13;
  double local_18;
  
  fVar2 = FLOAT_80437848;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 != '\x04') {
        if (('\x03' < cVar1) || (iVar11 = zz_004cd24_(param_1,0xf), iVar11 != 1)) goto LAB_80078a94;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      }
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if (*(char *)(param_1 + 0x545) == '\0') {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
    if (cVar1 == '\0') {
      *(float *)(param_1 + 0x15c) = FLOAT_80437874;
      fVar9 = FLOAT_804378b8;
      fVar4 = FLOAT_804378a4;
      dVar13 = DOUBLE_80437840;
      *(float *)(param_1 + 0x4c) = -(*(float *)(param_1 + 0x44) / *(float *)(param_1 + 0x15c));
      *(float *)(param_1 + 0x144) = fVar2;
      *(float *)(param_1 + 0x14c) = fVar2;
      *(float *)(param_1 + 0x148) = fVar2;
      *(float *)(param_1 + 0x150) = fVar2;
      *(float *)(param_1 + 0x158) = fVar9;
      *(float *)(param_1 + 0x164) = fVar2;
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72)) ^ 0x80000000);
      fVar4 = fVar4 * (float)(local_18 - dVar13);
      *(float *)(param_1 + 0x170) = fVar4;
      *(float *)(param_1 + 0x168) = fVar4;
      *(float *)(param_1 + 0x16c) = fVar4;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
    else if (cVar1 < '\0') goto LAB_80078a94;
    fVar9 = FLOAT_804378c0;
    fVar4 = FLOAT_804378bc;
    fVar2 = *(float *)(param_1 + 0x15c);
    if (*(float *)(param_1 + 0x164) < fVar2) {
      fVar3 = fVar2 - *(float *)(param_1 + 0x164);
      fVar5 = *(float *)(param_1 + 0x1dc8);
      if (fVar3 < *(float *)(param_1 + 0x1dc8)) {
        fVar5 = fVar3;
      }
      fVar3 = *(float *)(param_1 + 0x158);
      fVar6 = FLOAT_804378c0 * fVar3;
      fVar7 = FLOAT_804378c4 * fVar3;
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x14c);
      dVar13 = DOUBLE_804378d0;
      fVar10 = FLOAT_804378c8;
      fVar8 = FLOAT_80437860;
      *(float *)(param_1 + 0x14c) =
           ((fVar4 * *(float *)(param_1 + 0x154) + fVar6 * fVar2) / (fVar2 * fVar2 * fVar2)) * fVar5
           + *(float *)(param_1 + 0x14c);
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x150);
      *(float *)(param_1 + 0x150) =
           ((*(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x144)) * fVar8 +
           (fVar9 * *(float *)(param_1 + 0x154) - fVar7 * fVar2) / (fVar2 * fVar2)) * fVar5 +
           *(float *)(param_1 + 0x150);
      fVar2 = ((*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x148)) * fVar8 + fVar3) * fVar5;
      *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + fVar2;
      *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) + fVar2;
      *(short *)(param_1 + 0x72) = (short)(int)(fVar10 * *(float *)(param_1 + 0x16c));
      *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + fVar5;
      if ((double)*(float *)(param_1 + 0x164) <= (double)*(float *)(param_1 + 0x15c) * dVar13) {
        *(char *)(param_1 + 0x6f7) = (char)((uint)(int)(fVar10 * fVar2) >> 8);
      }
      else if (*(char *)(param_1 + 0x175) == '\0') {
        *(undefined1 *)(param_1 + 0x175) = 1;
        dVar13 = (double)FLOAT_8043784c;
        *(undefined1 *)(param_1 + 0x6f7) = 0;
        zz_004beb8_(dVar13,param_1,0xf,4,1,0xffffffff,0xffffffff);
      }
      goto LAB_80078a94;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
  }
  if (*(char *)(param_1 + 0x174) == '\x01') {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 1;
    zz_004beb8_(dVar13,param_1,0xf,4,2,0xffffffff,0xffffffff);
  }
  else {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 0;
    zz_004beb8_(dVar13,param_1,0xf,0,0xd,0x14,1);
  }
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_80078a94:
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  uVar12 = zz_00677b0_(param_1);
  *(char *)(param_1 + 0x174) = (char)uVar12;
  if ((char)uVar12 != '\0') {
    if ((*(char *)(param_1 + 0x542) < '\x02') || (*(char *)(param_1 + 0x545) == '\x01')) {
      zz_00b22f4_(param_1);
    }
    else if ((*(char *)(param_1 + 0x545) == '\0') && ('\x02' < *(char *)(param_1 + 0x542))) {
      *(undefined1 *)(param_1 + 0x542) = 4;
    }
  }
  return;
}



// ==== 80078b0c  FUN_80078b0c ====

void FUN_80078b0c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d5fa0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80078b5c  FUN_80078b5c ====

void FUN_80078b5c(int param_1)

{
  float fVar1;
  uint uVar2;
  double dVar3;
  
  *(float *)(param_1 + 0x80c) = FLOAT_80437848;
  fVar1 = FLOAT_80437884;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 10;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    zz_006660c_(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  fVar1 = FLOAT_80437838;
  *(float *)(param_1 + 0x44) = FLOAT_8043788c;
  *(float *)(param_1 + 0x4c) = fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_80437848;
  dVar3 = (double)FLOAT_8043784c;
  *(float *)(param_1 + 0x48) = FLOAT_80437848;
  *(float *)(param_1 + 0x50) = fVar1;
  zz_004beb8_(dVar3,param_1,3,4,3,0xffffffff,0xffffffff);
  return;
}



// ==== 80078c68  FUN_80078c68 ====

void FUN_80078c68(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar3 = FLOAT_80437848;
  if (*(char *)(param_1 + 0x541) == '\0') {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      if (*(int *)(param_1 + 0xcc) == 0) {
        *(float *)(param_1 + 0x44) =
             FLOAT_804378e0 *
             (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) /
             FLOAT_80437878);
        *(float *)(param_1 + 0x4c) = fVar3;
        *(float *)(param_1 + 0x48) = fVar3;
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      }
      else {
        iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
        local_2c = *(float *)(iVar4 + 0x8e0);
        local_28 = *(float *)(iVar4 + 0x8f0);
        local_24 = *(undefined4 *)(iVar4 + 0x900);
        local_38 = *(float *)(param_1 + 0x518);
        local_30 = *(undefined4 *)(param_1 + 0x520);
        local_34 = FLOAT_80437858 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
        gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
        dVar5 = gnt4_PSVECMag_bl(&local_2c);
        fVar3 = FLOAT_80437848;
        if (dVar5 < (double)FLOAT_804378d8) {
          *(undefined1 *)(param_1 + 0x541) = 1;
          goto LAB_80078e40;
        }
        *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043787c;
        fVar2 = *(float *)(param_1 + 0x48);
        if (fVar2 <= fVar3) {
          if (fVar2 < FLOAT_804378dc) {
            *(float *)(param_1 + 0x48) = FLOAT_804378dc;
          }
          *(float *)(param_1 + 0x50) = FLOAT_80437848;
        }
        else {
          if (FLOAT_80437884 < fVar2) {
            *(float *)(param_1 + 0x48) = FLOAT_80437884;
          }
          *(float *)(param_1 + 0x50) = FLOAT_804378a0;
        }
        local_28 = FLOAT_80437848;
        dVar5 = gnt4_PSVECMag_bl(&local_2c);
        fVar3 = FLOAT_80437880;
        *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043787c);
        *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar3;
      }
      zz_006660c_(param_1);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
  }
LAB_80078e40:
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 != 0) {
    zz_00b22f4_(param_1);
  }
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    zz_0067754_(param_1,(short *)(param_1 + 0x72),0x3000);
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x542) = cVar1 + '\x01';
    zz_01005ec_(param_1,0);
    *(undefined1 *)(param_1 + 0x6f7) = 0x38;
  }
  fVar3 = FLOAT_8043784c;
  dVar5 = DOUBLE_80437840;
  dVar6 = (double)FLOAT_80437848;
  if ((double)*(float *)(param_1 + 0x558) <= dVar6) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_804378a4;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    fVar3 = fVar2 * (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72) ^ 0x80000000
                                            ) - dVar5);
    dVar7 = (double)fVar3;
    *(float *)(param_1 + 0x170) = fVar3;
    dVar5 = (double)(fVar2 * (float)((double)CONCAT44(0x43300000,
                                                      (int)*(short *)(param_1 + 0x5ae) ^ 0x80000000)
                                    - dVar5));
    if (dVar7 < dVar6) {
      dVar7 = (double)(float)(DOUBLE_804378a8 + dVar7);
    }
    if (dVar5 < (double)FLOAT_80437848) {
      dVar5 = (double)(float)(DOUBLE_804378a8 + dVar5);
    }
    if (dVar5 < dVar7) {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (FLOAT_804378b4 - (float)(dVar7 - dVar5));
    }
    else {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (float)(dVar5 - dVar7);
    }
    *(undefined1 *)(param_1 + 0x175) = 0;
  }
  return;
}



// ==== 80078fc8  FUN_80078fc8 ====

void FUN_80078fc8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  double dVar13;
  double local_18;
  
  fVar2 = FLOAT_80437848;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 != '\x04') {
        if (('\x03' < cVar1) || (iVar11 = zz_004cd24_(param_1,0xf), iVar11 != 1)) goto LAB_800792c4;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      }
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if (*(char *)(param_1 + 0x545) == '\0') {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
    if (cVar1 == '\0') {
      *(float *)(param_1 + 0x15c) = FLOAT_80437874;
      fVar9 = FLOAT_804378b8;
      fVar4 = FLOAT_804378a4;
      dVar13 = DOUBLE_80437840;
      *(float *)(param_1 + 0x4c) = -(*(float *)(param_1 + 0x44) / *(float *)(param_1 + 0x15c));
      *(float *)(param_1 + 0x144) = fVar2;
      *(float *)(param_1 + 0x14c) = fVar2;
      *(float *)(param_1 + 0x148) = fVar2;
      *(float *)(param_1 + 0x150) = fVar2;
      *(float *)(param_1 + 0x158) = fVar9;
      *(float *)(param_1 + 0x164) = fVar2;
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72)) ^ 0x80000000);
      fVar4 = fVar4 * (float)(local_18 - dVar13);
      *(float *)(param_1 + 0x170) = fVar4;
      *(float *)(param_1 + 0x168) = fVar4;
      *(float *)(param_1 + 0x16c) = fVar4;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
    else if (cVar1 < '\0') goto LAB_800792c4;
    fVar9 = FLOAT_804378c0;
    fVar4 = FLOAT_804378bc;
    fVar2 = *(float *)(param_1 + 0x15c);
    if (*(float *)(param_1 + 0x164) < fVar2) {
      fVar3 = fVar2 - *(float *)(param_1 + 0x164);
      fVar5 = *(float *)(param_1 + 0x1dc8);
      if (fVar3 < *(float *)(param_1 + 0x1dc8)) {
        fVar5 = fVar3;
      }
      fVar3 = *(float *)(param_1 + 0x158);
      fVar6 = FLOAT_804378c0 * fVar3;
      fVar7 = FLOAT_804378c4 * fVar3;
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x14c);
      dVar13 = DOUBLE_804378d0;
      fVar10 = FLOAT_804378c8;
      fVar8 = FLOAT_80437860;
      *(float *)(param_1 + 0x14c) =
           ((fVar4 * *(float *)(param_1 + 0x154) + fVar6 * fVar2) / (fVar2 * fVar2 * fVar2)) * fVar5
           + *(float *)(param_1 + 0x14c);
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x150);
      *(float *)(param_1 + 0x150) =
           ((*(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x144)) * fVar8 +
           (fVar9 * *(float *)(param_1 + 0x154) - fVar7 * fVar2) / (fVar2 * fVar2)) * fVar5 +
           *(float *)(param_1 + 0x150);
      fVar2 = ((*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x148)) * fVar8 + fVar3) * fVar5;
      *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + fVar2;
      *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) + fVar2;
      *(short *)(param_1 + 0x72) = (short)(int)(fVar10 * *(float *)(param_1 + 0x16c));
      *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + fVar5;
      if ((double)*(float *)(param_1 + 0x164) <= (double)*(float *)(param_1 + 0x15c) * dVar13) {
        *(char *)(param_1 + 0x6f7) = (char)((uint)(int)(fVar10 * fVar2) >> 8);
      }
      else if (*(char *)(param_1 + 0x175) == '\0') {
        *(undefined1 *)(param_1 + 0x175) = 1;
        dVar13 = (double)FLOAT_8043784c;
        *(undefined1 *)(param_1 + 0x6f7) = 0;
        zz_004beb8_(dVar13,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      goto LAB_800792c4;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
  }
  if (*(char *)(param_1 + 0x174) == '\x01') {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 1;
    zz_004beb8_(dVar13,param_1,0xf,4,2,0xffffffff,0xffffffff);
  }
  else {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 0;
    zz_004beb8_(dVar13,param_1,0xf,0,0xd,0x14,1);
  }
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_800792c4:
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  uVar12 = zz_00677b0_(param_1);
  *(char *)(param_1 + 0x174) = (char)uVar12;
  if ((char)uVar12 != '\0') {
    if ((*(char *)(param_1 + 0x542) < '\x02') || (*(char *)(param_1 + 0x545) == '\x01')) {
      zz_00b22f4_(param_1);
    }
    else if ((*(char *)(param_1 + 0x545) == '\0') && ('\x02' < *(char *)(param_1 + 0x542))) {
      *(undefined1 *)(param_1 + 0x542) = 4;
    }
  }
  return;
}



// ==== 8007933c  zz_007933c_ ====

undefined4 zz_007933c_(int param_1,uint param_2)

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
                                                0x80000000) - DOUBLE_80437840) *
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



// ==== 8007950c  zz_007950c_ ====

void zz_007950c_(int param_1)

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
    FUN_800e4294(param_1,-0x7fd29c90,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fd29c30,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fd29bd0,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fd29b70,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}



// ==== 800795e0  zz_00795e0_ ====

void zz_00795e0_(int param_1)

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
      FUN_800e43e0(param_1,(float *)&DAT_802d6370,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)&DAT_802d6580);
      FUN_800e43e0(param_1,(float *)&DAT_802d63d0,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)&DAT_802d658c);
      FUN_800e43e0(param_1,(float *)&DAT_802d6430,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)&DAT_802d6598);
      FUN_800e43e0(param_1,(float *)&DAT_802d6490,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)&DAT_802d65a4);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd29c90,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fd29c30,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fd29bd0,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fd29b70,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}



// ==== 80079754  zz_0079754_ ====

void zz_0079754_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 8007978c  zz_007978c_ ====

void zz_007978c_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29c90,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29c30,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29bd0,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29b70,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fd29c90,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fd29c30,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fd29bd0,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fd29b70,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 800798d4  FUN_800798d4 ====

void FUN_800798d4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x908) {
    zz_004eb98_(param_1,1);
  }
  else if (sVar1 < 0x908) {
    if (sVar1 == 0x900) {
      zz_004eb98_(param_1,0);
    }
  }
  else if (sVar1 == 0x90d) {
    zz_004eb98_(param_1,2);
  }
  zz_007950c_(param_1);
  return;
}



// ==== 80079978  FUN_80079978 ====

void FUN_80079978(int param_1)

{
  zz_00795e0_(param_1);
  return;
}



// ==== 800799ac  FUN_800799ac ====

void FUN_800799ac(int param_1)

{
  zz_0079754_(param_1);
  return;
}



// ==== 800799cc  FUN_800799cc ====

void FUN_800799cc(int param_1)

{
  zz_007978c_(param_1);
  return;
}



// ==== 800799ec  FUN_800799ec ====

void FUN_800799ec(int param_1,char param_2)

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



// ==== 80079a40  FUN_80079a40 ====

void FUN_80079a40(int param_1)

{
  (*(code *)(&PTR_FUN_802d65b0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80079a7c  FUN_80079a7c ====

void FUN_80079a7c(int param_1)

{
  (*(code *)(&PTR_FUN_802d65bc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80079ab8  FUN_80079ab8 ====

void FUN_80079ab8(int param_1)

{
  (*(code *)(&PTR_FUN_802d65d0)[*(char *)(param_1 + 0x540)])();
  zz_0079d54_(param_1);
  return;
}



// ==== 80079b08  FUN_80079b08 ====

void FUN_80079b08(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(char *)(param_1 + 0x581) == '\x03') {
    *(float *)(param_1 + 0x80c) = FLOAT_804378e8;
  }
  *(float *)(param_1 + 0x558) = FLOAT_804378ec;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  fVar1 = FLOAT_804378e8;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,2,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  return;
}



// ==== 80079ba8  FUN_80079ba8 ====

void FUN_80079ba8(int param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_804378e8 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 80079c3c  FUN_80079c3c ====

void FUN_80079c3c(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
  }
  return;
}



// ==== 80079d00  FUN_80079d00 ====

void FUN_80079d00(int param_1)

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



// ==== 80079d54  zz_0079d54_ ====

void zz_0079d54_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804378f4;
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_804378f4;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ((*(char *)(param_1 + 0x581) == '\x03') && ('\0' < *(char *)(param_1 + 0x540))) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80079de8  FUN_80079de8 ====

void FUN_80079de8(int param_1)

{
  (*(code *)(&PTR_FUN_802d65e0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80079e24  FUN_80079e24 ====

void FUN_80079e24(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804378fc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_804378f0,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}



// ==== 80079e88  FUN_80079e88 ====

void FUN_80079e88(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar3 = FLOAT_804378e8;
  if (iVar4 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
  }
  return;
}



// ==== 80079fb4  FUN_80079fb4 ====

void FUN_80079fb4(double param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8007a010  FUN_8007a010 ====

void FUN_8007a010(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_802d65ec)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 8007a068  FUN_8007a068 ====

void FUN_8007a068(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804378fc;
  dVar2 = (double)FLOAT_804378f0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}



// ==== 8007a0b4  FUN_8007a0b4 ====

void FUN_8007a0b4(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar3 = FLOAT_804378e8;
  if (iVar4 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8007a1f8  FUN_8007a1f8 ====

void FUN_8007a1f8(double param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8007a250  FUN_8007a250 ====

void FUN_8007a250(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d65f8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007a298  FUN_8007a298 ====

void FUN_8007a298(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_804378f8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804378f0,param_1,1,2,3,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_804378f0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = FLOAT_804378fc;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 8007a364  FUN_8007a364 ====

void FUN_8007a364(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar2 = zz_006d0dc_(param_1,0x81,0);
  if ((((iVar2 != 0) || (*(float *)(param_1 + 0x558) <= FLOAT_804378e8)) &&
      (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
  }
  return;
}



// ==== 8007a498  FUN_8007a498 ====

void FUN_8007a498(int param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  iVar2 = zz_004cd24_(param_1,1);
  if ((iVar2 == 1) || (iVar1 == 1)) {
    if (iVar1 == 1) {
      *(float *)(param_1 + 0x694) = FLOAT_80437900 + *(float *)(param_1 + 0x1dc8);
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8007a530  FUN_8007a530 ====

void FUN_8007a530(int param_1)

{
  (*(code *)(&PTR_FUN_802d6604)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8007a56c  FUN_8007a56c ====

void FUN_8007a56c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d661c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007a5bc  FUN_8007a5bc ====

void FUN_8007a5bc(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_80437904;
  fVar1 = FLOAT_804378e8;
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
  *(float *)(param_1 + 0x80c) = FLOAT_804378e8;
  return;
}



// ==== 8007a678  FUN_8007a678 ====

void FUN_8007a678(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    fVar1 = FLOAT_804378ec;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_80437908 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_80437908 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043790c;
    *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8007a790  FUN_8007a790 ====

void FUN_8007a790(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x04') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_8007a7c8;
  }
  zz_004cd24_(param_1,0xf);
LAB_8007a7c8:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437910;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar4 = FUN_80066838((double)FLOAT_8043790c,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_80437918;
    fVar1 = FLOAT_80437914;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 8007a890  FUN_8007a890 ====

void FUN_8007a890(int param_1)

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
          fVar1 = FLOAT_8043791c;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_804378ec;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_80437920;
          }
          dVar3 = (double)FLOAT_804378f0;
          *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
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



// ==== 8007aa38  FUN_8007aa38 ====

void FUN_8007aa38(int param_1)

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
      *(float *)(param_1 + 0x4c) = FLOAT_804378f0;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar2 = FLOAT_804378e8;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if ((*(float *)(param_1 + 0x558) <= fVar2) ||
         (uVar4 = FUN_80066838((double)FLOAT_8043790c,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_80437924;
        fVar2 = FLOAT_80437918;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_804378e8,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_80437900;
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



// ==== 8007abf4  FUN_8007abf4 ====

void FUN_8007abf4(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8007ac2c  FUN_8007ac2c ====

void FUN_8007ac2c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6634)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007ac7c  FUN_8007ac7c ====

void FUN_8007ac7c(int param_1)

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
  fVar1 = FLOAT_80437928;
  *(float *)(param_1 + 0x558) = FLOAT_80437904;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_804378e8;
  return;
}



// ==== 8007ad5c  FUN_8007ad5c ====

void FUN_8007ad5c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043792c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043792c;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_804378e8;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_804378ec;
    *(float *)(param_1 + 0x558) = FLOAT_804378ec;
    fVar3 = FLOAT_8043790c;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 8007aea0  FUN_8007aea0 ====

void FUN_8007aea0(int param_1)

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
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar3 = FUN_80066838((double)FLOAT_8043790c,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_804378f0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8007af84  FUN_8007af84 ====

void FUN_8007af84(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_804378f8 < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_80437930,param_1);
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
  fVar3 = FLOAT_804378e8;
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
      goto LAB_8007b124;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_80437934;
      fVar3 = FLOAT_80437918;
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
LAB_8007b124:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 8007b184  FUN_8007b184 ====

void FUN_8007b184(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8007b1bc  FUN_8007b1bc ====

void FUN_8007b1bc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6648)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007b20c  FUN_8007b20c ====

void FUN_8007b20c(int param_1)

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
  dVar2 = (double)FLOAT_804378f0;
  *(float *)(param_1 + 0x558) = FLOAT_80437904;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 8007b2c8  FUN_8007b2c8 ====

void FUN_8007b2c8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_804378e8 < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8007b348;
  }
  fVar2 = FLOAT_80437930;
  fVar1 = FLOAT_804378ec;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8007b348:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8007b388  FUN_8007b388 ====

/* WARNING: Removing unreachable block (ram,0x8007b5b8) */
/* WARNING: Removing unreachable block (ram,0x8007b398) */

void FUN_8007b388(int param_1)

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
  fVar1 = FLOAT_804378e8;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_80437908 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_804378ec
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
    local_34 = FLOAT_804378ec * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_804378e8;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_80437938;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043793c;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_80437938);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_80437904,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_80437940 * (double)*(float *)(param_1 + 0x44)) goto LAB_8007b5ac;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_804378e8;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8007b5ac:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8007b5d4  FUN_8007b5d4 ====

void FUN_8007b5d4(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_804378e8;
    if (*(float *)(param_1 + 0x44) < FLOAT_804378e8) {
      *(float *)(param_1 + 0x44) = FLOAT_804378e8;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_804378ec + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8007b678  FUN_8007b678 ====

void FUN_8007b678(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6658)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007b6c8  FUN_8007b6c8 ====

void FUN_8007b6c8(int param_1)

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
  dVar2 = (double)FLOAT_804378f0;
  *(float *)(param_1 + 0x558) = FLOAT_80437904;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8007b784  FUN_8007b784 ====

void FUN_8007b784(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_804378e8 < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8007b804;
  }
  fVar2 = FLOAT_80437930;
  fVar1 = FLOAT_804378ec;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8007b804:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8007b844  FUN_8007b844 ====

/* WARNING: Removing unreachable block (ram,0x8007ba74) */
/* WARNING: Removing unreachable block (ram,0x8007b854) */

void FUN_8007b844(int param_1)

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
  fVar1 = FLOAT_804378e8;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_80437948 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_804378ec
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
    local_34 = FLOAT_804378ec * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_804378e8;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_80437938;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043793c;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_80437938);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_80437904,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_80437940 * (double)*(float *)(param_1 + 0x44)) goto LAB_8007ba68;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_804378e8;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8007ba68:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8007ba90  FUN_8007ba90 ====

void FUN_8007ba90(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_804378e8;
    if (*(float *)(param_1 + 0x44) < FLOAT_804378e8) {
      *(float *)(param_1 + 0x44) = FLOAT_804378e8;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_804378ec + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8007bb34  FUN_8007bb34 ====

void FUN_8007bb34(int param_1)

{
  (*(code *)(&PTR_FUN_804338d8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8007bb6c  FUN_8007bb6c ====

void FUN_8007bb6c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6668)[*(char *)(param_1 + 0x540)])(param_1);
  if (FLOAT_804378ec < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = FLOAT_804378ec;
  }
  return;
}



// ==== 8007bbe0  FUN_8007bbe0 ====

/* WARNING: Removing unreachable block (ram,0x8007bdec) */
/* WARNING: Removing unreachable block (ram,0x8007bbf0) */

void FUN_8007bbe0(undefined8 param_1,double param_2,double param_3,int param_4)

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
  
  fVar1 = FLOAT_80437904;
  *(char *)(param_4 + 0x540) = *(char *)(param_4 + 0x540) + '\x01';
  *(undefined1 *)(param_4 + 0x541) = 0;
  *(float *)(param_4 + 0x558) = fVar1;
  *(undefined1 *)(param_4 + 0x545) = 0;
  if (((*(int *)(param_4 + 0xcc) == 0) || ('\0' < *(char *)(param_4 + 0x1dc))) ||
     (*(char *)(*(int *)(param_4 + 0xcc) + 0x83) != '\0')) {
    *(undefined1 *)(param_4 + 0x541) = 1;
    *(undefined4 *)(param_4 + 0xcc) = 0;
  }
  dVar3 = (double)FLOAT_8043794c;
  if ((*(char *)(param_4 + 0x541) == '\0') &&
     (*(char *)(param_4 + 0x88) == *(char *)(*(int *)(param_4 + 0xcc) + 0x88))) {
    local_2c = *(float *)(param_4 + 0x8e0);
    local_28 = *(float *)(param_4 + 0x8f0);
    in_f31 = (double)(FLOAT_80437950 + local_28);
    local_24 = *(undefined4 *)(param_4 + 0x900);
    local_38 = *(float *)(param_4 + 0x518);
    local_34 = *(undefined4 *)(param_4 + 0x51c);
    local_30 = *(undefined4 *)(param_4 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    dVar3 = gnt4_PSVECMag_bl(&local_2c);
    param_2 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x8f0);
    param_3 = (double)*(float *)(*(int *)(param_4 + 0xcc) + 0x668);
  }
  if ((((double)FLOAT_80437954 <= dVar3) ||
      (in_f31 < (double)(float)(param_2 - (double)FLOAT_80437950))) ||
     ((double)(float)(param_2 + param_3) < in_f31)) {
    zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,0,0xffffffff,0xffffffff);
    *(float *)(param_4 + 0x80c) = FLOAT_804378e8;
    *(undefined1 *)(param_4 + 0x544) = 0;
  }
  else {
    if (*(char *)(param_4 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,2,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804378f0,param_4,0xf,4,5,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_4 + 0x544) = 1;
  }
  zz_007c800_(param_4,0xc0);
  fVar1 = FLOAT_804378e8;
  *(float *)(param_4 + 0x38) = FLOAT_804378e8;
  *(float *)(param_4 + 0x3c) = fVar1;
  *(float *)(param_4 + 0x40) = fVar1;
  iVar2 = zz_006dbe0_(param_4,2,1,1);
  if (iVar2 == 0) {
    *(undefined2 *)(param_4 + 0x548) = 0;
    *(undefined1 *)(param_4 + 0x6e8) = 8;
  }
  else {
    *(undefined2 *)(param_4 + 0x548) = 1;
  }
  return;
}



// ==== 8007be08  FUN_8007be08 ====

void FUN_8007be08(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_007c800_(param_1,0xc0), iVar3 != 0)) {
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (*(char *)(param_1 + 0x88) != *(char *)(*(int *)(param_1 + 0xcc) + 0x88))) {
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
    }
    FUN_80066958(param_1);
    fVar2 = FLOAT_804378f8;
    fVar1 = FLOAT_804378ec;
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
      fVar2 = FLOAT_80437900;
      *(float *)(param_1 + 0x558) = fVar1;
      fVar1 = FLOAT_804378e8;
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
    if (FLOAT_8043790c < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 8007bf70  FUN_8007bf70 ====

void FUN_8007bf70(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8fc);
  }
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804378ec;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(short *)(param_1 + 0x548) == 0) {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\t')) {
        *(undefined1 *)(param_1 + 0x6e8) = 8;
        *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
    }
    else {
      zz_007c800_(param_1,0xc0);
      if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
        FUN_8006c1c8((double)FLOAT_8043791c,param_1,(float *)(param_1 + 0x518));
        if (FLOAT_80437930 <= *(float *)(param_1 + 0x760)) {
          *(float *)(param_1 + 0x4c) = FLOAT_804378f8;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_80437958;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
      FUN_80067610(param_1);
      if ((*(float *)(param_1 + 0x4c) < FLOAT_804378e8) &&
         (*(float *)(param_1 + 0x44) < FLOAT_80437900)) {
        *(float *)(param_1 + 0x44) = FLOAT_80437900;
      }
      fVar1 = FLOAT_804378ec;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\n')) {
        *(undefined1 *)(param_1 + 0x6e8) = 2;
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
    zz_007c9ac_(param_1);
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  if (*(char *)(param_1 + 0x545) == '\x01') {
    zz_00f0104_(param_1,0x1c,1);
  }
  return;
}



// ==== 8007c19c  FUN_8007c19c ====

void FUN_8007c19c(int param_1)

{
  float fVar1;
  double dVar2;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  zz_00f0104_(param_1,0x1c,1);
  zz_007c800_(param_1,0xc0);
  if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
    local_18 = *(float *)(param_1 + 0x518);
    local_14 = *(float *)(param_1 + 0x51c) - FLOAT_80437950;
    local_10 = *(undefined4 *)(param_1 + 0x520);
    FUN_8006c1c8((double)FLOAT_8043791c,param_1,&local_18);
    if (FLOAT_80437930 <= *(float *)(param_1 + 0x760)) {
      *(float *)(param_1 + 0x4c) = FLOAT_804378f8;
    }
    else {
      *(float *)(param_1 + 0x4c) = FLOAT_80437958;
    }
    zz_007c844_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  FUN_80067610(param_1);
  if (*(float *)(param_1 + 0x4c) < FLOAT_804378e8) {
    if (*(float *)(param_1 + 0x44) < FLOAT_80437900) {
      *(float *)(param_1 + 0x44) = FLOAT_80437900;
    }
  }
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar1 = FLOAT_8043795c;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(float *)(param_1 + 0x558) <= FLOAT_804378e8) {
      dVar2 = (double)FLOAT_804378f0;
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
    zz_007c9ac_(param_1);
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8007c350  FUN_8007c350 ====

void FUN_8007c350(int param_1)

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
                           DOUBLE_80437968) * FLOAT_80437960);
  *(undefined1 *)(param_1 + 0x547) = 1;
  return;
}



// ==== 8007c414  FUN_8007c414 ====

void FUN_8007c414(int param_1)

{
  float fVar1;
  uint uVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_007c800_(param_1,0xc0);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar2 = FUN_80066838((double)FLOAT_80437970,param_1), 0 < (int)uVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_004cff4_(param_1,0xf);
  }
  return;
}



// ==== 8007c4b8  FUN_8007c4b8 ====

void FUN_8007c4b8(int param_1)

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
        zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_007c800_(param_1,0xc0);
      FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
      fVar3 = FLOAT_804378fc;
      fVar2 = FLOAT_804378e8;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x06')) {
        if (*(char *)(param_1 + 0x1d9) < '\x01') {
          *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x542) = 2;
          *(float *)(param_1 + 0x558) = fVar3;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
          *(float *)(param_1 + 0x44) = fVar2;
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        }
      }
    }
  }
  else if ((cVar1 < '\x03') &&
          (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
          bVar5 = fVar2 <= FLOAT_804378e8, *(float *)(param_1 + 0x558) = fVar2, bVar5)) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
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



// ==== 8007c6b0  FUN_8007c6b0 ====

/* WARNING: Removing unreachable block (ram,0x8007c788) */
/* WARNING: Removing unreachable block (ram,0x8007c780) */
/* WARNING: Removing unreachable block (ram,0x8007c6c8) */
/* WARNING: Removing unreachable block (ram,0x8007c6c0) */

void FUN_8007c6b0(int param_1)

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
    dVar3 = DOUBLE_80437968;
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



// ==== 8007c7a4  FUN_8007c7a4 ====

void FUN_8007c7a4(int param_1)

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



// ==== 8007c800  zz_007c800_ ====

void zz_007c800_(int param_1,uint param_2)

{
  zz_006660c_(param_1);
  FUN_800669d0(param_1,param_2);
  return;
}



// ==== 8007c844  zz_007c844_ ====

void zz_007c844_(int param_1)

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
  local_18 = FLOAT_804378e8;
  local_14 = *(undefined4 *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),afStack_28);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_1c,afStack_28);
  dVar2 = (double)FLOAT_804378f8;
  if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_804378f0)) {
    dVar2 = (double)FLOAT_804378f0;
  }
  dVar3 = (double)gnt4_acos_bl(dVar2);
  dVar2 = DOUBLE_80437968;
  if (*(float *)(param_1 + 0x3c) <= FLOAT_804378e8) {
    fVar1 = FLOAT_80437974 * (float)dVar3;
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
    fVar1 = FLOAT_80437974 * (float)dVar3;
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



// ==== 8007c9ac  zz_007c9ac_ ====

void zz_007c9ac_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  
  fVar2 = FLOAT_804378f0;
  fVar1 = FLOAT_804378e8;
  pfVar4 = (float *)(param_1 + 0x148);
  *(undefined1 *)(param_1 + 0x543) = 1;
  *(float *)(param_1 + 0x148) = fVar2 * *(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0x14c) = fVar1;
  *(float *)(param_1 + 0x150) = fVar2 * *(float *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  *(float *)(param_1 + 0x14c) = FLOAT_80437978;
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  fVar2 = FLOAT_804378f8;
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x38) = FLOAT_804378e8;
  fVar3 = FLOAT_8043797c;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar2 = FLOAT_80437980;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x44) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x694) = fVar2 + *(float *)(param_1 + 0x1dc8);
  return;
}



// ==== 8007cb58  FUN_8007cb58 ====

void FUN_8007cb58(int param_1)

{
  zz_004f1c4_(param_1);
  *(undefined2 *)(param_1 + 0x144) = 0;
  zz_00c74ec_(param_1,0x2e);
  return;
}



// ==== 8007cba4  FUN_8007cba4 ====

void FUN_8007cba4(int param_1)

{
  short sVar1;
  
  zz_006d520_(param_1,(float *)&DAT_802d6a48);
  if ((*(short *)(param_1 + 1000) == 0xc00) || (*(short *)(param_1 + 1000) == 0xc06)) {
    if (((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) && (*(char *)(param_1 + 0x146) == '\0')) {
      sVar1 = *(short *)(param_1 + 0x144);
      if (sVar1 < -0x1400) {
        *(short *)(param_1 + 0x144) = sVar1 + 0xc0;
        if (-0x1401 < *(short *)(param_1 + 0x144)) {
          *(undefined2 *)(param_1 + 0x144) = 0xec00;
        }
      }
      else if ((-0x1400 < sVar1) &&
              (*(short *)(param_1 + 0x144) = sVar1 + -0xc0, *(short *)(param_1 + 0x144) < -0x13ff))
      {
        *(undefined2 *)(param_1 + 0x144) = 0xec00;
      }
    }
    *(undefined2 *)(param_1 + 0x18f2) = *(undefined2 *)(param_1 + 0x144);
    sVar1 = *(short *)(param_1 + 0x144);
    *(short *)(param_1 + 0x18ec) =
         (short)((ulonglong)((longlong)(int)sVar1 * 0x55555556) >> 0x20) -
         ((short)((short)((int)sVar1 / 0x30000) + (sVar1 >> 0xf)) >> 0xf);
  }
  return;
}



// ==== 8007ccb0  FUN_8007ccb0 ====

void FUN_8007ccb0(int param_1)

{
  (*(code *)(&PTR_FUN_802d6a78)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8007ccec  FUN_8007ccec ====

void FUN_8007ccec(int param_1)

{
  (*(code *)(&PTR_FUN_804338e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8007cd24  FUN_8007cd24 ====

void FUN_8007cd24(int param_1)

{
  (*(code *)(&PTR_LAB_802d6a84)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007cd90  FUN_8007cd90 ====

/* WARNING: Removing unreachable block (ram,0x8007ce68) */
/* WARNING: Removing unreachable block (ram,0x8007cda0) */

void FUN_8007cd90(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa30);
    local_24 = *(undefined4 *)(param_1 + 0xa40);
    local_20 = *(undefined4 *)(param_1 + 0xa50);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0xa90);
    local_24 = *(undefined4 *)(param_1 + 0xaa0);
    local_20 = *(undefined4 *)(param_1 + 0xab0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = zz_007da18_(param_1,iVar2), uVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 8007ce84  FUN_8007ce84 ====

/* WARNING: Removing unreachable block (ram,0x8007d000) */
/* WARNING: Removing unreachable block (ram,0x8007ce94) */

void FUN_8007ce84(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa30);
    local_24 = *(undefined4 *)(param_1 + 0xa40);
    local_20 = *(undefined4 *)(param_1 + 0xa50);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0xa90);
    local_24 = *(undefined4 *)(param_1 + 0xaa0);
    local_20 = *(undefined4 *)(param_1 + 0xab0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  zz_007da18_(param_1,iVar2);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 5;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (iVar2 == 0) {
        zz_0082824_(param_1,3);
      }
      else {
        zz_0082824_(param_1,2);
      }
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      if (2 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (4 < *(short *)(param_1 + 0x54c)) {
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



// ==== 8007d020  FUN_8007d020 ====

void FUN_8007d020(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8007d070  FUN_8007d070 ====

void FUN_8007d070(int param_1)

{
  (*(code *)(&PTR_LAB_802d6a98)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007d0dc  FUN_8007d0dc ====

/* WARNING: Removing unreachable block (ram,0x8007d1b4) */
/* WARNING: Removing unreachable block (ram,0x8007d0ec) */

void FUN_8007d0dc(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa30);
    local_24 = *(undefined4 *)(param_1 + 0xa40);
    local_20 = *(undefined4 *)(param_1 + 0xa50);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0xa90);
    local_24 = *(undefined4 *)(param_1 + 0xaa0);
    local_20 = *(undefined4 *)(param_1 + 0xab0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = zz_007da18_(param_1,iVar2), uVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 8007d1d0  FUN_8007d1d0 ====

/* WARNING: Removing unreachable block (ram,0x8007d34c) */
/* WARNING: Removing unreachable block (ram,0x8007d1e0) */

void FUN_8007d1d0(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa30);
    local_24 = *(undefined4 *)(param_1 + 0xa40);
    local_20 = *(undefined4 *)(param_1 + 0xa50);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0xa90);
    local_24 = *(undefined4 *)(param_1 + 0xaa0);
    local_20 = *(undefined4 *)(param_1 + 0xab0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  zz_007da18_(param_1,iVar2);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 5;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (iVar2 == 0) {
        zz_0082824_(param_1,3);
      }
      else {
        zz_0082824_(param_1,2);
      }
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      if (2 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (4 < *(short *)(param_1 + 0x54c)) {
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



// ==== 8007d36c  FUN_8007d36c ====

void FUN_8007d36c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8007d3bc  FUN_8007d3bc ====

void FUN_8007d3bc(int param_1)

{
  (*(code *)(&PTR_FUN_804338e8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8007d3f4  FUN_8007d3f4 ====

void FUN_8007d3f4(int param_1)

{
  (*(code *)(&PTR_FUN_802d6aac)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8007d430  FUN_8007d430 ====

void FUN_8007d430(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437988;
  dVar2 = (double)FLOAT_8043798c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,3,4,0,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80437990;
  return;
}



// ==== 8007d490  FUN_8007d490 ====

void FUN_8007d490(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  byte bVar4;
  
  *(undefined1 *)(param_1 + 0x146) = 1;
  zz_006660c_(param_1);
  iVar2 = FUN_800669d0(param_1,0xc1);
  bVar4 = iVar2 != 0;
  iVar2 = zz_00853ec_(param_1,2);
  sVar3 = (short)iVar2;
  if (sVar3 < -0x3800) {
    sVar3 = -0x3800;
  }
  else if (0x1800 < sVar3) {
    sVar3 = 0x1800;
  }
  sVar1 = *(short *)(param_1 + 0x144);
  iVar2 = (int)sVar3;
  if (sVar1 < iVar2) {
    *(short *)(param_1 + 0x144) = sVar1 + 0x180;
    if (iVar2 + -0xc0 <= (int)*(short *)(param_1 + 0x144)) {
      *(short *)(param_1 + 0x144) = sVar3;
    }
  }
  else if ((iVar2 < sVar1) &&
          (*(short *)(param_1 + 0x144) = sVar1 + -0x180,
          (int)*(short *)(param_1 + 0x144) <= iVar2 + 0xc0)) {
    *(short *)(param_1 + 0x144) = sVar3;
  }
  if (*(short *)(param_1 + 0x144) == sVar3) {
    bVar4 = bVar4 | 2;
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((bVar4 == 3) || (*(float *)(param_1 + 0x558) <= FLOAT_80437990)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  return;
}



// ==== 8007d5d0  FUN_8007d5d0 ====

void FUN_8007d5d0(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 != 0) {
      zz_0084600_(param_1,2);
    }
    *(undefined1 *)(param_1 + 0x146) = 0;
  }
  if (*(char *)(param_1 + 0x1cef) == '\x01') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
  iVar1 = zz_004cd24_(param_1,3);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8007d690  FUN_8007d690 ====

void FUN_8007d690(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8007d6c4  FUN_8007d6c4 ====

void FUN_8007d6c4(int param_1)

{
  float fVar1;
  int iVar2;
  
  (*(code *)(&PTR_FUN_802d6abc)[*(char *)(param_1 + 0x540)])();
  FUN_80067310((double)FLOAT_80437994,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_80437990;
  if (*(float *)(param_1 + 0x44) < FLOAT_80437990) {
    *(float *)(param_1 + 0x4c) = FLOAT_80437990;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x709) = 1;
    if (*(char *)(param_1 + 0x541) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
    }
  }
  return;
}



// ==== 8007d778  FUN_8007d778 ====

void FUN_8007d778(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80437988;
  dVar2 = (double)FLOAT_8043798c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,3,4,0,0xffffffff,0xffffffff);
  fVar1 = FLOAT_80437990;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}



// ==== 8007d7e4  FUN_8007d7e4 ====

void FUN_8007d7e4(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  byte bVar4;
  
  *(undefined1 *)(param_1 + 0x146) = 1;
  zz_006660c_(param_1);
  iVar2 = FUN_800669d0(param_1,0xc1);
  bVar4 = iVar2 != 0;
  iVar2 = zz_00853ec_(param_1,2);
  sVar3 = (short)iVar2;
  if (sVar3 < -0x3800) {
    sVar3 = -0x3800;
  }
  else if (0x1800 < sVar3) {
    sVar3 = 0x1800;
  }
  sVar1 = *(short *)(param_1 + 0x144);
  iVar2 = (int)sVar3;
  if (sVar1 < iVar2) {
    *(short *)(param_1 + 0x144) = sVar1 + 0x180;
    if (iVar2 + -0xc0 <= (int)*(short *)(param_1 + 0x144)) {
      *(short *)(param_1 + 0x144) = sVar3;
    }
  }
  else if ((iVar2 < sVar1) &&
          (*(short *)(param_1 + 0x144) = sVar1 + -0x180,
          (int)*(short *)(param_1 + 0x144) <= iVar2 + 0xc0)) {
    *(short *)(param_1 + 0x144) = sVar3;
  }
  if (*(short *)(param_1 + 0x144) == sVar3) {
    bVar4 = bVar4 | 2;
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((bVar4 == 3) || (*(float *)(param_1 + 0x558) <= FLOAT_80437990)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  return;
}



// ==== 8007d924  FUN_8007d924 ====

void FUN_8007d924(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_80437998;
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    fVar2 = FLOAT_8043799c;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_0084600_(param_1,2);
    }
    *(undefined1 *)(param_1 + 0x146) = 0;
  }
  iVar3 = zz_004cd24_(param_1,3);
  if (iVar3 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8007d9e4  FUN_8007d9e4 ====

void FUN_8007d9e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 8007da18  zz_007da18_ ====

uint zz_007da18_(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  short local_18 [8];
  
  if (param_2 == 0) {
    local_18[0] = 0;
    local_18[1] = 0;
    local_18[2] = 0xe000;
    local_18[3] = 0x2000;
    iVar1 = FUN_8006cc90((double)FLOAT_804379a0,param_1,6,2,local_18);
    uVar2 = (uint)(iVar1 != 0);
    local_18[0] = 0x4000;
    local_18[1] = 0xe800;
    local_18[2] = 0;
    local_18[3] = 0;
    iVar1 = FUN_8006cc90((double)FLOAT_804379a0,param_1,7,6,local_18);
    if (iVar1 != 0) {
      uVar2 = uVar2 + 1;
    }
  }
  else {
    local_18[0] = 0;
    local_18[1] = 0;
    local_18[2] = 0xe000;
    local_18[3] = 0x2000;
    iVar1 = FUN_8006cc90((double)FLOAT_804379a0,param_1,8,2,local_18);
    uVar2 = (uint)(iVar1 != 0);
    local_18[0] = 0x1800;
    local_18[1] = 0xc000;
    local_18[2] = 0;
    local_18[3] = 0;
    iVar1 = FUN_8006cc90((double)FLOAT_804379a0,param_1,9,8,local_18);
    if (iVar1 != 0) {
      uVar2 = uVar2 + 1;
    }
  }
  uVar2 = countLeadingZeros(2 - uVar2);
  return uVar2 >> 5;
}



// ==== 8007db5c  zz_007db5c_ ====

void zz_007db5c_(int param_1,byte param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = (uint)param_2 * 0x38;
  if (*(short *)(param_1 + 1000) == *(short *)(&DAT_802d6d96 + iVar3)) {
    puVar2 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      puVar2[0x10] = 0xf;
      puVar2[0x11] = param_2;
      *(code **)(puVar2 + 0xc) = FUN_8007dcec;
      *(code **)(puVar2 + 0x10c) = FUN_8007e698;
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
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 + (char)(&DAT_802d6d6a)[iVar3] * 0x30 + 0x8d4),
                 (float *)(iVar3 + -0x7fd29294),(float *)(puVar2 + 0x20));
      if ((&DAT_802d6d94)[iVar3] != '\0') {
        gnt4_PSVECAdd_bl((float *)(puVar2 + 0x20),(float *)(param_1 + 0x7b0),
                         (float *)(puVar2 + 0x20));
      }
      uVar1 = *(undefined4 *)(param_1 + 0x51c);
      *(undefined4 *)(puVar2 + 0x144) = *(undefined4 *)(param_1 + 0x518);
      *(undefined4 *)(puVar2 + 0x148) = uVar1;
      *(undefined4 *)(puVar2 + 0x14c) = *(undefined4 *)(param_1 + 0x520);
      puVar2[0x150] = *(undefined1 *)(param_1 + 0x1afc);
      puVar2[0x151] = *(undefined1 *)(param_1 + 0x1afd);
    }
  }
  return;
}



// ==== 8007dcec  FUN_8007dcec ====

void FUN_8007dcec(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802d6f98)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8007dd84  FUN_8007dd84 ====

/* WARNING: Removing unreachable block (ram,0x8007e1e4) */
/* WARNING: Removing unreachable block (ram,0x8007e1dc) */
/* WARNING: Removing unreachable block (ram,0x8007dd9c) */
/* WARNING: Removing unreachable block (ram,0x8007dd94) */

void FUN_8007dd84(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  undefined4 local_100;
  float local_fc;
  float local_f8;
  float local_f4 [2];
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0;
  float afStack_dc [3];
  undefined4 local_d0;
  undefined4 local_c0;
  undefined4 local_b0;
  float afStack_ac [12];
  float afStack_7c [2];
  undefined4 local_74;
  undefined4 local_64;
  undefined4 local_54;
  undefined4 local_48;
  uint uStack_44;
  
  iVar8 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  puVar4 = &DAT_802d6d68;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x14;
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(iVar8 + 0x72);
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_802d6d6b)[iVar5]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar8 + (char)(&DAT_802d6d6a)[iVar5] * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fd29294),(float *)(param_9 + 0x20));
    if ((&DAT_802d6d94)[iVar5] != '\0') {
      gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(iVar8 + 0x7b0),(float *)(param_9 + 0x20))
      ;
    }
    uStack_44 = (int)*(short *)(iVar8 + 0x72) ^ 0x80000000;
    local_48 = 0x43300000;
    dVar10 = (double)FLOAT_804379ac;
    dVar12 = (double)FLOAT_804379a8;
    dVar11 = dVar10 * (double)(float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_804379d8);
    if (*(int *)(iVar8 + 200) != 0) {
      gnt4_PSVECSubtract_bl((float *)(param_9 + 0x144),(float *)(param_9 + 0x20),&local_e8);
      dVar11 = (double)(local_e8 * local_e8 + local_e0 * local_e0);
      if ((double)FLOAT_804379a8 < dVar11) {
        dVar12 = 1.0 / SQRT(dVar11);
        dVar12 = DOUBLE_804379b0 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_804379b8);
        dVar12 = DOUBLE_804379b0 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_804379b8);
        dVar11 = (double)(float)(dVar11 * DOUBLE_804379b0 * dVar12 *
                                          -(dVar11 * dVar12 * dVar12 - DOUBLE_804379b8));
      }
      local_e8 = (float)dVar11;
      if (dVar11 < (double)FLOAT_804379c0) {
        local_e8 = FLOAT_804379c0;
      }
      param_6 = (double)(local_e8 * local_e8);
      param_3 = (double)(FLOAT_804379c4 * *(float *)(&DAT_802d6d78 + iVar5) *
                        *(float *)(&DAT_802d6d78 + iVar5));
      param_4 = (double)(float)((double)(float)((double)*(float *)(&DAT_802d6d90 + iVar5) * param_6)
                               / param_3);
      param_5 = (double)(float)(param_6 -
                               (double)((float)((double)FLOAT_804379c8 * param_4) *
                                       (float)(param_4 + (double)local_e4)));
      if (param_5 < (double)FLOAT_804379a8) {
        param_5 = (double)FLOAT_804379a8;
      }
      dVar11 = param_5;
      if ((double)FLOAT_804379a8 < param_5) {
        dVar11 = 1.0 / SQRT(param_5);
        dVar11 = DOUBLE_804379b0 * dVar11 * -(param_5 * dVar11 * dVar11 - DOUBLE_804379b8);
        dVar11 = DOUBLE_804379b0 * dVar11 * -(param_5 * dVar11 * dVar11 - DOUBLE_804379b8);
        dVar11 = (double)(float)(param_5 *
                                DOUBLE_804379b0 * dVar11 *
                                -(param_5 * dVar11 * dVar11 - DOUBLE_804379b8));
        param_3 = DOUBLE_804379b0;
      }
      dVar11 = gnt4_atan((double)((float)((double)local_e8 - dVar11) /
                                 (float)((double)FLOAT_804379c4 * param_4)));
      dVar12 = (double)(float)dVar11;
      if ((double)FLOAT_804379cc <= (double)(float)dVar11) {
        dVar12 = (double)FLOAT_804379cc;
      }
      gnt4_PSVECSubtract_bl((float *)(param_9 + 0x144),(float *)(param_9 + 0x20),local_f4);
      dVar10 = (double)local_ec;
      dVar11 = (double)gnt4_atan2_bl((double)local_f4[0],dVar10);
    }
    dVar11 = (double)(float)dVar11;
    gnt4_PSMTXRotRad_bl(-dVar12,afStack_7c,0x78);
    gnt4_PSMTXRotRad_bl(dVar11,afStack_ac,0x79);
    gnt4_PSMTXConcat_bl(afStack_ac,afStack_7c,afStack_7c);
    *(undefined4 *)(param_9 + 0x38) = local_74;
    *(undefined4 *)(param_9 + 0x3c) = local_64;
    *(undefined4 *)(param_9 + 0x40) = local_54;
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d6d78 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    fVar1 = FLOAT_804379a8;
    dVar11 = (double)*(float *)(&DAT_802d6d78 + iVar5);
    *(float *)(param_9 + 0x44) = *(float *)(&DAT_802d6d78 + iVar5);
    *(float *)(param_9 + 0x48) = fVar1;
    *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(&DAT_802d6d90 + iVar5);
    *(short *)(param_9 + 0x1e) = (short)*(undefined4 *)(&DAT_802d6d7c + iVar5);
    *(undefined1 *)(param_9 + 0x19) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 600;
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(&DAT_802d6d98 + iVar5);
    uVar7 = (uint)*(short *)(&DAT_802d6d68 + iVar5);
    if ((uVar7 & 0x4000) == 0) {
      if ((uVar7 & 0x8000) == 0) {
        iVar2 = zz_0006f78_(param_9);
        zz_0006fb4_(dVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                    *(int *)(param_9 + 0xe0),uVar7,puVar4,iVar6,in_r8,in_r9,in_r10);
      }
      else {
        zz_0006fb4_(dVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + 0xe0),uVar7 & 0x3fff,puVar4,iVar6,in_r8,in_r9,in_r10);
      }
    }
    else {
      pfVar3 = (float *)(uVar7 & 0x3fff);
      zz_0006fb4_(dVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),(int)pfVar3,puVar4,iVar6,in_r8,in_r9,in_r10);
      fVar1 = FLOAT_804379d0;
      if (*(char *)(param_9 + 0x88) != '\0') {
        fVar1 = FLOAT_804379d4;
      }
      uVar9 = zz_00086b8_((double)fVar1,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb374,*(int *)(param_9 + 0xe0),pfVar3,puVar4,iVar6,in_r8,in_r9,
                          in_r10);
      uVar9 = zz_0007c30_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,puVar4,iVar6,in_r8,in_r9,
                          in_r10);
      zz_0007d40_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar3,puVar4,iVar6,in_r8,in_r9,in_r10);
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    if (-1 < (char)(&DAT_802d6d9c)[iVar5]) {
      local_100 = *(undefined4 *)(param_9 + 0x40);
      local_fc = FLOAT_804379a8;
      local_f8 = -*(float *)(param_9 + 0x38);
      zz_0045ef4_(afStack_dc,5,param_9 + 0x38,&local_100);
      local_d0 = *(undefined4 *)(param_9 + 0x20);
      local_c0 = *(undefined4 *)(param_9 + 0x24);
      local_b0 = *(undefined4 *)(param_9 + 0x28);
      zz_00aedc0_(iVar8,afStack_dc,(int)(char)(&DAT_802d6d9c)[iVar5],*(undefined1 *)(param_9 + 0x88)
                 );
    }
    FUN_80047aa4(param_9);
    zz_007e200_(param_9);
  }
  return;
}



// ==== 8007e200  zz_007e200_ ====

/* WARNING: Removing unreachable block (ram,0x8007e61c) */
/* WARNING: Removing unreachable block (ram,0x8007e210) */

void zz_007e200_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float fStack_34;
  float local_30;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
  if ((0 < *(short *)(param_1 + 0x1c)) &&
     (iVar4 = zz_0083244_((float *)(param_1 + 0x20)), iVar4 == 0)) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      cVar1 = (&DAT_802d6d9d)[iVar3];
      if (cVar1 == '\x01') {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1800;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x1800;
        }
      }
      else if (cVar1 < '\x03') {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1800;
      }
      pcVar5 = *(char **)(param_1 + 0xcc);
      if (((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) ||
         ((pcVar5[0x83] == '\0' && (pcVar5[0x656] != '\0')))) {
        *(undefined4 *)(param_1 + 200) = 0;
      }
      fVar2 = FLOAT_804379e4;
      if (*(int *)(param_1 + 200) == 0) {
        *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
        *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
        *(float *)(param_1 + 0x24) =
             *(float *)(param_1 + 0x24) +
             -(*(float *)(param_1 + 0x50) * fVar2 - *(float *)(param_1 + 0x3c));
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
      }
      else {
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
        if (*(short *)(param_1 + 0x1e) < 1) {
          *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_802d6d7c + iVar3);
          iVar4 = *(int *)(param_1 + 200);
          local_28 = *(float *)(iVar4 + 100);
          local_24 = *(undefined4 *)(iVar4 + 0x68);
          local_20 = *(undefined4 *)(iVar4 + 0x6c);
          gnt4_PSVECSubtract_bl(&local_28,(float *)(param_1 + 0x20),&fStack_34);
          if (((-1 < *(short *)(&DAT_802d6d9e + iVar3)) && (*(int *)(param_1 + 0xcc) != 0)) &&
             (dVar6 = gnt4_PSVECMag_bl(&fStack_34),
             dVar6 < (double)(FLOAT_804379e0 * *(float *)(*(int *)(param_1 + 0xcc) + 0xb4)))) {
            FUN_8016d584(param_1,(byte)*(undefined2 *)(&DAT_802d6d9e + iVar3),&local_28);
            *(undefined1 *)(param_1 + 0x18) = 2;
            zz_008aff0_(param_1);
            return;
          }
          dVar9 = (double)local_30;
          local_30 = FLOAT_804379a8;
          dVar6 = gnt4_PSVECMag_bl(&fStack_34);
          dVar8 = (double)(*(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x38) +
                          *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x40));
          if ((double)FLOAT_804379a8 < dVar8) {
            dVar7 = 1.0 / SQRT(dVar8);
            dVar7 = DOUBLE_804379b0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_804379b8);
            dVar7 = DOUBLE_804379b0 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_804379b8);
            dVar8 = (double)(float)(dVar8 * DOUBLE_804379b0 * dVar7 *
                                            -(dVar8 * dVar7 * dVar7 - DOUBLE_804379b8));
          }
          dVar6 = (double)(float)(dVar6 / dVar8);
          fVar2 = (FLOAT_804379c4 * (float)(dVar6 * (double)*(float *)(param_1 + 0x3c) - dVar9)) /
                  (float)(dVar6 * dVar6);
          if (fVar2 < *(float *)(&DAT_802d6d84 + iVar3)) {
            fVar2 = *(float *)(&DAT_802d6d84 + iVar3);
          }
          if (*(float *)(&DAT_802d6d88 + iVar3) < fVar2) {
            fVar2 = *(float *)(&DAT_802d6d88 + iVar3);
          }
          fVar2 = fVar2 - *(float *)(param_1 + 0x50);
          if (*(float *)(&DAT_802d6d8c + iVar3) < ABS(fVar2)) {
            fVar2 = *(float *)(&DAT_802d6d8c + iVar3) * (ABS(fVar2) / fVar2);
          }
          *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) + fVar2;
        }
        fVar2 = FLOAT_804379e4;
        *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
        *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
        *(float *)(param_1 + 0x24) =
             *(float *)(param_1 + 0x24) +
             -(*(float *)(param_1 + 0x50) * fVar2 - *(float *)(param_1 + 0x3c));
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
        zz_00833a4_(param_1);
      }
      zz_00833ec_(param_1);
      zz_0083610_(param_1,(float *)(param_1 + 0x50));
      dVar6 = (double)*(float *)(param_1 + 0x3c);
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      *(float *)(param_1 + 0x3c) = (float)dVar6;
      iVar4 = zz_0083714_(param_1);
      if (iVar4 == 0) {
        iVar4 = zz_0084170_(param_1);
        if (iVar4 == 0) {
          return;
        }
        if ((char)(&DAT_802d6d95)[iVar3] < '\0') {
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_802d6d95)[iVar3]);
        }
        *(undefined1 *)(param_1 + 0x18) = 2;
        return;
      }
    }
    else if ((char)(&DAT_802d6d95)[iVar3] < '\0') {
      FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    }
    else {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_802d6d95)[iVar3]);
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 8007e63c  FUN_8007e63c ====

void FUN_8007e63c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8007e678  FUN_8007e678 ====

void FUN_8007e678(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8007e698  FUN_8007e698 ====

void FUN_8007e698(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_38 [13];
  
  dVar3 = (double)*(float *)(param_1 + 0x154);
  dVar5 = dVar3;
  gnt4_PSMTXScale_bl(dVar3,dVar3,dVar3,afStack_38);
  pfVar1 = afStack_38;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  iVar2 = *(int *)(param_1 + 0xe0);
  zz_00076d0_(uVar4,dVar3,dVar5,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_38,(undefined *)pfVar1,
              param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(iVar2,0x47);
  return;
}



// ==== 8007e700  zz_007e700_ ====

void zz_007e700_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x200) || (*(short *)(param_1 + 1000) == 0x20a)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,2);
    if (puVar1 == (undefined1 *)0x0) {
      *(undefined1 *)(param_1 + 0x144) = 0;
    }
    else {
      *puVar1 = 1;
      puVar1[0x10] = 0x18;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_8007e894;
      *(code **)(puVar1 + 0x10c) = FUN_8007f240;
      *(code **)(puVar1 + 0x100) = FUN_8007ef40;
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
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 +
                          (char)(&DAT_802d6faa)[(uint)(byte)puVar1[0x11] * 0x38] * 0x30 + 0x8d4),
                 (float *)((uint)(byte)puVar1[0x11] * 0x38 + -0x7fd29054),(float *)(puVar1 + 0x20));
      zz_0083d60_((int)puVar1,param_1,0);
      *(undefined2 *)(puVar1 + 0x70) = 0;
      *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
      *(undefined2 *)(puVar1 + 0x74) = 0;
      zz_00f036c_((int)puVar1,0xbb);
    }
  }
  return;
}



// ==== 8007e894  FUN_8007e894 ====

void FUN_8007e894(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802d7018)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8007e934  FUN_8007e934 ====

void FUN_8007e934(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  puVar3 = &DAT_802d6fa8;
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  uVar5 = zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar2 = zz_0006f78_(param_9);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_802d6fa8 + iVar1),puVar3,in_r7,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x144) = 0;
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_802d6fab)[iVar1]);
  if (iVar2 == 0) {
    *(undefined1 *)(iVar4 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d6fb8 + iVar1),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802d6fb8 + iVar1);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802d6fbc + iVar1);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_802d6fbe + iVar1);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_007ea48_(param_9);
    *(undefined1 *)(param_9 + 0xaf) = 0;
    zz_001ac80_(param_9,(char)*(undefined2 *)(&DAT_802d6fde + iVar1));
  }
  return;
}



// ==== 8007ea48  zz_007ea48_ ====

void zz_007ea48_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_007ec0c_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_007eac0_(param_1);
  }
  if (*(char *)(param_1 + 0x144) < '\x01') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1800;
  }
  else {
    *(char *)(param_1 + 0x144) = *(char *)(param_1 + 0x144) + -1;
  }
  return;
}



// ==== 8007eac0  zz_007eac0_ ====

void zz_007eac0_(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_0083244_((float *)(param_1 + 0x20));
  fVar1 = FLOAT_804379e8;
  if (iVar2 == 0) {
    if (*(char *)(param_1 + 0x1d9) != '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(float *)(param_1 + 0x44) = fVar1;
      *(undefined2 *)(param_1 + 0x1e) = 8;
      *(undefined1 *)(param_1 + 0x144) = 8;
      zz_00f036c_(param_1,0xbc);
    }
    if (*(char *)(param_1 + 0x19) != '\0') {
      return;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
    FUN_80083874((double)*(float *)(&DAT_802d6fc4 + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_802d6fc0 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_802d6fbe + iVar2));
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    iVar2 = zz_0083714_(param_1);
    if ((iVar2 == 0) && (iVar2 = zz_0084170_(param_1), iVar2 == 0)) {
      if (0 < *(short *)(param_1 + 0x1c)) {
        return;
      }
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      zz_00f036c_(param_1,0xbc);
      return;
    }
  }
  fVar1 = FLOAT_804379e8;
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined1 *)(param_1 + 0x1a) = 1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x1e) = 0xf;
  zz_00f036c_(param_1,0xbc);
  return;
}



// ==== 8007ec0c  zz_007ec0c_ ====

void zz_007ec0c_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
  if ((*(char *)(param_1 + 0x1d9) != '\0') && (*(char *)(param_1 + 0x144) == '\0')) {
    *(undefined1 *)(param_1 + 0x144) = 3;
  }
  if (*(char *)(param_1 + 0x144) < '\x01') {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  fVar2 = FLOAT_804379e8;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_804379ec;
    if (*(float *)(&DAT_802d6fb8 + iVar3) <= *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(&DAT_802d6fb8 + iVar3);
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - FLOAT_804379ec;
        if (*(float *)(param_1 + 0x44) <= fVar2) {
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x1a) = 1;
          *(undefined2 *)(param_1 + 0x1e) = 0xf;
          return;
        }
        if ('\0' < *(char *)(param_1 + 0x144)) {
          return;
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (0 < *(short *)(param_1 + 0x1e)) {
        return;
      }
      *(undefined1 *)(param_1 + 0x1a) = 2;
      dVar6 = (double)FLOAT_804379f4;
      *(float *)(param_1 + 0x44) = FLOAT_804379f0;
      *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_802d6fd4 + iVar3);
      gnt4_PSQUATScale_bl(dVar6,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar4 = iVar5 + (char)(&DAT_802d6faa)[iVar3] * 0x30;
  local_24 = *(float *)(iVar4 + 0x8e0);
  local_20 = *(undefined4 *)(iVar4 + 0x8f0);
  local_1c = *(undefined4 *)(iVar4 + 0x900);
  dVar6 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x20));
  if ((double)FLOAT_804379e8 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_804379f8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80437a00);
    dVar7 = DOUBLE_804379f8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80437a00);
    dVar6 = (double)(float)(dVar6 * DOUBLE_804379f8 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80437a00));
  }
  if ((double)*(float *)(param_1 + 0x44) <= dVar6) {
    if (*(char *)(param_1 + 0x144) < '\x01') {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_802d6fd4 + iVar3);
        zz_006c440_((double)*(float *)(&DAT_802d6fd8 + iVar3),param_1,&local_24);
      }
      else {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
    }
  }
  else {
    *(undefined1 *)(iVar5 + 0x144) = 0;
    zz_00f036c_(param_1,0xbd);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 8007eee4  FUN_8007eee4 ====

void FUN_8007eee4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8007ef20  FUN_8007ef20 ====

void FUN_8007ef20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8007ef40  FUN_8007ef40 ====

/* WARNING: Removing unreachable block (ram,0x8007f1e0) */

void FUN_8007ef40(int param_1)

{
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float afStack_44 [16];
  
  gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
  local_5c = FLOAT_804379e8;
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  local_68 = *(float *)(param_1 + 0x38);
  local_64 = *(float *)(param_1 + 0x3c);
  local_60 = *(float *)(param_1 + 0x40);
  if (local_5c == *(float *)(param_1 + 0x3c)) {
    local_4c = local_5c;
    local_50 = FLOAT_80437a08;
    local_48 = local_5c;
    local_58 = FLOAT_80437a08;
    local_54 = local_5c;
    local_68 = local_5c;
    local_64 = local_5c;
    local_60 = FLOAT_80437a08;
  }
  else {
    if (local_60 * local_60 + local_68 * local_68 + local_64 * local_64 <= local_5c) {
      local_68 = local_5c;
      local_64 = local_5c;
      local_60 = FLOAT_804379f4;
    }
    local_5c = local_68;
    local_54 = local_60;
    local_58 = FLOAT_804379e8;
    if (FLOAT_804379e8 < local_60 * local_60 + local_68 * local_68 + FLOAT_804379e8 * FLOAT_804379e8
       ) {
      if (*(float *)(param_1 + 0x3c) < FLOAT_804379e8) {
        gnt4_PSVECCrossProduct_bl(&local_68,&local_5c,&local_5c);
      }
      else {
        gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_5c);
      }
    }
    else {
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0x20),(float *)(*(int *)(param_1 + 0x90) + 0x20),&local_5c);
      gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_5c);
    }
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= FLOAT_804379e8) {
      local_58 = FLOAT_804379e8;
      local_5c = FLOAT_80437a08;
      local_54 = FLOAT_804379e8;
    }
    gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_5c);
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= FLOAT_804379e8) {
      local_5c = FLOAT_804379e8;
      local_58 = FLOAT_80437a08;
      local_54 = FLOAT_804379e8;
    }
    gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_50);
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_804379e8) {
      local_4c = FLOAT_804379e8;
      local_50 = FLOAT_804379f4;
      local_48 = FLOAT_804379e8;
    }
    gnt4_PSVECNormalize_bl(&local_50,&local_50);
    gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
    gnt4_PSVECNormalize_bl(&local_68,&local_68);
  }
  *(float *)(param_1 + 0x114) = local_50;
  *(float *)(param_1 + 0x124) = local_4c;
  *(float *)(param_1 + 0x134) = local_48;
  *(float *)(param_1 + 0x118) = local_5c;
  *(float *)(param_1 + 0x128) = local_58;
  *(float *)(param_1 + 0x138) = local_54;
  *(float *)(param_1 + 0x11c) = local_68;
  *(float *)(param_1 + 300) = local_64;
  *(float *)(param_1 + 0x13c) = local_60;
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437a0c *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_44,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_44,(float *)(param_1 + 0x114));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_44);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_44,(float *)(param_1 + 0x114));
  return;
}



// ==== 8007f240  FUN_8007f240 ====

void FUN_8007f240(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8007f29c  zz_007f29c_ ====

bool zz_007f29c_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = param_3;
    puVar1[0x10] = 0x25;
    *(code **)(puVar1 + 0xc) = FUN_8007f3bc;
    *(code **)(puVar1 + 0x10c) = zz_007f8b8_;
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
    zz_00f036c_(param_1,7);
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 8007f3bc  FUN_8007f3bc ====

void FUN_8007f3bc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802d7120)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8007f454  FUN_8007f454 ====

void FUN_8007f454(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined8 uVar9;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  puVar7 = &DAT_802d70e8;
  puVar5 = &DAT_802d7028;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  iVar6 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar2 = iVar6 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar1 = iVar2;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fd28fd4),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802d702a + iVar2) * 0x30 + 0x8fc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_802d7038 + iVar2);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_802d703c + iVar2);
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d70f8 + iVar3),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437a10,&local_28,&local_28);
  uVar9 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802d70f8 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802d70ea + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_802d70ec + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_802d70ee + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_802d70fc + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar8 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar8 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_802d7028 + iVar2),iVar1,iVar4,puVar5,
              iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802d70e8 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x48);
  }
  return;
}



// ==== 8007f698  FUN_8007f698 ====

void FUN_8007f698(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_007f850_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_007f850_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_802d7100 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_802d70f4 + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_802d70f0 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_802d70ec + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_007f850_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),1);
            }
          }
          else {
            zz_007f850_(param_1);
          }
        }
      }
    }
    else {
      zz_007f850_(param_1);
    }
  }
  else {
    zz_007f850_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),1);
  }
  return;
}



// ==== 8007f850  zz_007f850_ ====

void zz_007f850_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8007f88c  zz_007f88c_ ====

void zz_007f88c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8007f898  zz_007f898_ ====

void zz_007f898_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



