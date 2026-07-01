// ==== 800d81f8  FUN_800d81f8 ====

void FUN_800d81f8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803109b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d8248  FUN_800d8248 ====

void FUN_800d8248(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80438bc8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  iVar2 = zz_006dbe0_(param_1,2,1,0);
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006ea9c_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_80438bcc,param_1,(int)*(char *)(param_1 + 0x543),4,
              (int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
  return;
}



// ==== 800d8300  FUN_800d8300 ====

void FUN_800d8300(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80438bd0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = zz_006ea9c_(param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800d836c  FUN_800d836c ====

void FUN_800d836c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar1 = zz_006dbe0_(param_1,2,1,0);
    if (iVar1 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      if (*(char *)(param_1 + 0x5db) != '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      zz_004beb8_((double)FLOAT_80438bcc,param_1,(int)*(char *)(param_1 + 0x543),4,
                  *(char *)(param_1 + 0x6ea) + 2,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x543) = 1;
      if (*(char *)(param_1 + 0x5db) == '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 0xf;
      }
      zz_004beb8_((double)FLOAT_80438bcc,param_1,(int)*(char *)(param_1 + 0x543),4,
                  *(char *)(param_1 + 0x6ea) + 1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 800d8470  FUN_800d8470 ====

uint FUN_800d8470(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  zz_004cd24_(param_1,1);
  uVar1 = zz_006ea9c_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    uVar1 = 0;
    if (iVar2 != 0) {
      bVar3 = zz_00d9fbc_(param_1);
      uVar1 = (uint)bVar3;
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(char *)(param_1 + 0x5db) != '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    uVar1 = zz_004beb8_((double)FLOAT_80438bcc,param_1,(int)*(char *)(param_1 + 0x543),4,
                        *(char *)(param_1 + 0x6ea) + 2,0xffffffff,0xffffffff);
  }
  return uVar1;
}



// ==== 800d8538  FUN_800d8538 ====

void FUN_800d8538(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = DOUBLE_80438bc0;
  dVar2 = (double)FLOAT_80438bd4;
  uVar1 = (int)*(short *)(param_9 + 0x18e0) ^ 0x80000000;
  *(short *)(param_9 + 0x18e0) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,uVar1) - DOUBLE_80438bc0) * dVar2);
  *(short *)(param_9 + 0x18e2) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_9 + 0x18e2) ^ 0x80000000)
                                   - dVar3) * dVar2);
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,uVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800d85f8  zz_00d85f8_ ====

bool zz_00d85f8_(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    *(undefined1 *)(param_1 + param_2 + 0x174) = 0;
    zz_006de10_(param_1,0);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = (char)param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x2a;
    *(code **)(puVar1 + 0xc) = FUN_800d8720;
    *(code **)(puVar1 + 0x10c) = FUN_800d8fbc;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800d8720  FUN_800d8720 ====

void FUN_800d8720(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80310e14)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800d87b8  FUN_800d87b8 ====

void FUN_800d87b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  puVar7 = &DAT_80310df8;
  puVar5 = &DAT_80310d98;
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
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fcef264),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8f4);
  if (*(char *)(param_9 + 0x13) < '\x02') {
    gnt4_PSQUATScale_bl(-(double)*(float *)(&DAT_80310e08 + iVar3),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  else {
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80310e08 + iVar3),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  zz_0083d60_(param_9,iVar8,0);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80310e08 + iVar3),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80310e08 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80310dfc + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80310dfe + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar2 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x600),
              *(int *)(param_9 + 0xe0),1,iVar1,iVar4,puVar5,iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80310df8 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(iVar8 + *(char *)(param_9 + 0x13) + 0x174) = 0;
    zz_006de10_(iVar8,0);
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x150))
    ;
    zz_00a2bf8_(iVar8,param_9,(undefined4 *)(param_9 + 0x144),(float *)(param_9 + 0x150),2,0);
  }
  return;
}



// ==== 800d8a54  FUN_800d8a54 ====

void FUN_800d8a54(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_00d8cc8_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_00d8a9c_(param_1);
  }
  return;
}



// ==== 800d8a9c  zz_00d8a9c_ ====

void zz_00d8a9c_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float afStack_28 [6];
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x18;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00d8e94_(param_1);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_80310e0c + iVar3)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_80310e10 + iVar3);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(&DAT_80310e0c + iVar3);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_80310e04 + iVar3),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_80310e00 + iVar3),param_1,
                     (char)*(undefined2 *)(&DAT_80310dfc + iVar3));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        iVar3 = zz_0083714_(param_1);
        if (iVar3 == 0) {
          iVar3 = zz_0084170_(param_1);
          if (iVar3 == 0) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(iVar4 + (char)(&DAT_80310d9a)[iVar2] * 0x30 + 0x8d4),
                       (float *)(iVar2 + -0x7fcef264),(float *)(param_1 + 0x144));
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),afStack_28);
            dVar5 = gnt4_PSVECMag_bl(afStack_28);
            if ((double)FLOAT_80438bd8 <= dVar5) {
              gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_80438bd8 / dVar5),afStack_28,
                                  afStack_28);
              gnt4_PSVECAdd_bl((float *)(param_1 + 0x144),afStack_28,(float *)(param_1 + 0x20));
              *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x20);
              *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
              *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
              zz_00d8e94_(param_1);
            }
          }
          else {
            zz_00d8e94_(param_1);
          }
        }
        else {
          zz_00d8e94_(param_1);
        }
      }
    }
    else {
      zz_00d8e94_(param_1);
    }
  }
  else {
    zz_00d8e94_(param_1);
  }
  return;
}



// ==== 800d8cc8  zz_00d8cc8_ ====

void zz_00d8cc8_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float afStack_28 [7];
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x13) * 0x18;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + (char)(&DAT_80310d9a)[iVar1] * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fcef264),afStack_28);
  dVar6 = gnt4_PSVECSquareDistance_bl(afStack_28,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80438bdc < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80438be0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438be8);
    dVar7 = DOUBLE_80438be0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438be8);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80438be0 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80438be8));
  }
  if ((double)FLOAT_80438bf0 < dVar6) {
    uVar4 = *(undefined4 *)(param_1 + 0x38);
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    uVar2 = *(undefined4 *)(param_1 + 0x40);
    dVar6 = (double)FLOAT_80438bf4;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x15c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x160);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x164);
    zz_006c440_(dVar6,param_1,afStack_28);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x38) = uVar4;
    *(undefined4 *)(param_1 + 0x3c) = uVar3;
    *(undefined4 *)(param_1 + 0x40) = uVar2;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + (char)(&DAT_80310d9a)[iVar1] * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fcef264),(float *)(param_1 + 0x144));
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    *(undefined1 *)(iVar5 + *(char *)(param_1 + 0x13) + 0x174) = 0;
    zz_006de10_(iVar5,0);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800d8e94  zz_00d8e94_ ====

void zz_00d8e94_(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [5];
  
  iVar3 = *(char *)(param_1 + 0x13) * 0x18;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_80310d9a)[iVar3] * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fcef264),afStack_1c);
  gnt4_PSVECSubtract_bl(afStack_1c,(float *)(param_1 + 0x20),&local_28);
  dVar5 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar1 = DAT_802b0cac;
  if (dVar5 <= (double)FLOAT_80438bdc) {
    *(undefined4 *)(param_1 + 0x15c) = DAT_802b0ca8;
    uVar2 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x160) = uVar1;
    *(undefined4 *)(param_1 + 0x164) = uVar2;
  }
  else {
    *(float *)(param_1 + 0x15c) = local_28;
    *(undefined4 *)(param_1 + 0x160) = local_24;
    *(undefined4 *)(param_1 + 0x164) = local_20;
  }
  pfVar4 = (float *)(param_1 + 0x15c);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar4,pfVar4);
  *(undefined1 *)(param_1 + 0x19) = 1;
  zz_008aff0_(param_1);
  return;
}



// ==== 800d8f90  FUN_800d8f90 ====

void FUN_800d8f90(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800d8f9c  FUN_800d8f9c ====

void FUN_800d8f9c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800d8fbc  FUN_800d8fbc ====

void FUN_800d8fbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800d90f8  FUN_800d90f8 ====

uint FUN_800d90f8(uint param_1)

{
  short sVar1;
  bool bVar2;
  
  *(undefined1 *)(param_1 + 0x4a8) = 2;
  *(undefined1 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x149) = 0;
  *(undefined4 *)(param_1 + 0x144) = 0x1010101;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x603) {
    bVar2 = zz_015c850_(param_1,'\0');
    param_1 = (uint)bVar2;
  }
  else if (sVar1 == 0x60b) {
    zz_013833c_(param_1,8,param_1 + 0x144);
    zz_013833c_(param_1,9,param_1 + 0x145);
    zz_013833c_(param_1,10,param_1 + 0x146);
    param_1 = zz_013833c_(param_1,0xb,param_1 + 0x147);
  }
  else if (sVar1 == 0x60d) {
    zz_013833c_(param_1,0xc,param_1 + 0x144);
    zz_013833c_(param_1,0xd,param_1 + 0x145);
    zz_013833c_(param_1,0xe,param_1 + 0x146);
    param_1 = zz_013833c_(param_1,0xf,param_1 + 0x147);
  }
  else if (sVar1 == 0x60f) {
    bVar2 = zz_015c850_(param_1,'\x01');
    param_1 = (uint)bVar2;
  }
  return param_1;
}



// ==== 800d92c8  FUN_800d92c8 ====

void FUN_800d92c8(int param_1)

{
  (*(code *)(&PTR_FUN_80310fa8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800d9304  FUN_800d9304 ====

void FUN_800d9304(int param_1)

{
  (*(code *)(&PTR_FUN_80433b98)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800d933c  FUN_800d933c ====

void FUN_800d933c(int param_1)

{
  (*(code *)(&PTR_LAB_80310fb4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d9388  FUN_800d9388 ====

void FUN_800d9388(int param_1)

{
  byte *pbVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  sVar2 = *(short *)(param_1 + 1000);
  if ((sVar2 == 0x603) || (sVar2 == 0x60f)) {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      if ((*(byte *)(param_1 + 0x14c) & 1) == 0) {
        if (*(short *)(param_1 + 1000) == 0x603) {
          zz_015cc58_(param_1,1);
        }
        else if (*(short *)(param_1 + 1000) == 0x60f) {
          zz_015cc58_(param_1,3);
        }
        *(undefined1 *)(param_1 + 0x149) = 1;
        *(undefined1 *)(param_1 + 0x14b) = 5;
      }
      else {
        if (*(short *)(param_1 + 1000) == 0x603) {
          zz_015cc58_(param_1,0);
        }
        else if (*(short *)(param_1 + 1000) == 0x60f) {
          zz_015cc58_(param_1,2);
        }
        *(undefined1 *)(param_1 + 0x148) = 1;
        *(undefined1 *)(param_1 + 0x14a) = 5;
      }
      *(char *)(param_1 + 0x14c) = *(char *)(param_1 + 0x14c) + '\x01';
      *(byte *)(param_1 + 0x14c) = *(byte *)(param_1 + 0x14c) & 1;
    }
  }
  else if ((sVar2 == 0x60d) || (sVar2 == 0x60b)) {
    iVar4 = 0xe;
    if (sVar2 == 0x60b) {
      iVar4 = 0x12;
    }
    iVar5 = 0;
    iVar6 = 4;
    do {
      pbVar1 = (byte *)(param_1 + iVar5 + 0x144);
      if ((*pbVar1 & 1) != 0) {
        zz_013212c_(param_1,iVar4 + iVar5,pbVar1);
        break;
      }
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  fVar3 = FLOAT_80438bf8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  return;
}



// ==== 800d9530  FUN_800d9530 ====

void FUN_800d9530(int param_1)

{
  (*(code *)(&PTR_FUN_80433b9c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800d9568  FUN_800d9568 ====

void FUN_800d9568(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar1 = zz_0066ac0_(param_1,0);
  if (iVar1 == 0) {
    *(undefined2 *)(param_1 + 0x5b2) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined2 *)(param_1 + 0x5b2) = *(undefined2 *)(param_1 + 0x5ac);
  }
  return;
}



// ==== 800d95c0  FUN_800d95c0 ====

void FUN_800d95c0(int param_1)

{
  short sVar1;
  int iVar2;
  
  iVar2 = zz_006dbe0_(param_1,2,1,1);
  if (iVar2 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x603) {
      zz_0150c48_(param_1,0);
    }
    else if (sVar1 == 0x60b) {
      zz_0150c48_(param_1,1);
    }
    else if (sVar1 == 0x60d) {
      zz_0150c48_(param_1,2);
    }
    else if (sVar1 == 0x60f) {
      zz_0150c48_(param_1,3);
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  return;
}



// ==== 800d9674  zz_00d9674_ ====

void zz_00d9674_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1d;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800d97d8;
    *(code **)(puVar1 + 0x10c) = FUN_800d9f60;
    *(code **)(puVar1 + 0x100) = FUN_800d9c38;
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
                        (char)(&DAT_80311222)[(uint)(byte)puVar1[0x11] * 0x20] * 0x30 + 0x8d4),
               (float *)((uint)(byte)puVar1[0x11] * 0x20 + -0x7fceeddc),(float *)(puVar1 + 0x20));
    zz_0083d60_((int)puVar1,param_1,0);
    *(undefined2 *)(puVar1 + 0x70) = 0;
    *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(puVar1 + 0x74) = 0;
  }
  return;
}



// ==== 800d97d8  FUN_800d97d8 ====

void FUN_800d97d8(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    zz_00d9b64_(param_1);
  }
  (*(code *)(&PTR_FUN_80311260)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800d9860  FUN_800d9860 ====

void FUN_800d9860(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  puVar4 = &DAT_80311220;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  uVar5 = zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = zz_0006f78_(param_9);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_80311220 + iVar1),puVar4,in_r7,in_r8,
              in_r9,in_r10);
  fVar2 = FLOAT_80438c00;
  *(undefined2 *)(param_9 + 0x148) = 0;
  *(undefined1 *)(param_9 + 0x14a) = 0;
  *(float *)(param_9 + 0x144) = fVar2;
  *(undefined1 *)(param_9 + 0x14b) = 0;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_80311223)[iVar1]);
  if (iVar3 == 0) {
    zz_00d9b64_(param_9);
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80311230 + iVar1),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80311230 + iVar1);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80311234 + iVar1);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80311236 + iVar1);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00d9958_(param_9);
  }
  return;
}



// ==== 800d9958  zz_00d9958_ ====

void zz_00d9958_(int param_1)

{
  float fVar1;
  int iVar2;
  char cVar3;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (*(short *)(param_1 + 0x1c) < 1) {
    zz_00d9b64_(param_1);
  }
  else {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x148) < 1) {
        if (*(char *)(param_1 + 0x1d9) != '\0') {
          *(undefined2 *)(param_1 + 0x148) = 0x1e;
          *(undefined1 *)(param_1 + 0x14a) = 2;
        }
        if (((*(byte *)(param_1 + 0x274) & 1) != 0) || ((*(byte *)(param_1 + 0x274) & 2) != 0)) {
          *(undefined2 *)(param_1 + 0x148) = 0x1e;
          *(undefined1 *)(param_1 + 0x14a) = 2;
          *(undefined1 *)(param_1 + 0x19) = 1;
        }
        iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x20;
        FUN_80083874((double)*(float *)(&DAT_8031123c + iVar2),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_80311238 + iVar2),param_1,
                     (char)*(undefined2 *)(&DAT_80311236 + iVar2));
        iVar2 = zz_0083714_(param_1);
        if (iVar2 != 0) {
          zz_00d9b64_(param_1);
          return;
        }
      }
      else {
        *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + -1;
        if ((*(char *)(param_1 + 0x19) != '\0') && (*(short *)(param_1 + 0x148) < 1)) {
          zz_00d9b64_(param_1);
          return;
        }
        if (*(char *)(param_1 + 0x1d9) != '\0') {
          *(undefined1 *)(param_1 + 0x14a) = 2;
        }
      }
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0084170_(param_1);
      fVar1 = FLOAT_80438c08;
      if (iVar2 == 0) {
        *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_80438c04;
        if (fVar1 < *(float *)(param_1 + 0x144)) {
          *(float *)(param_1 + 0x144) = fVar1;
        }
        fVar1 = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x144);
        *(float *)(param_1 + 0x60) = fVar1;
        *(float *)(param_1 + 0x5c) = fVar1;
        *(float *)(param_1 + 0x58) = fVar1;
        if (*(char *)(param_1 + 0x14a) < '\x01') {
          *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1800;
        }
        else {
          *(char *)(param_1 + 0x14a) = *(char *)(param_1 + 0x14a) + -1;
        }
        cVar3 = *(char *)(param_1 + 0x14b) + -1;
        *(char *)(param_1 + 0x14b) = cVar3;
        if (cVar3 < '\x01') {
          zz_00f036c_(param_1,0xdf);
          *(undefined1 *)(param_1 + 0x14b) = 0x10;
        }
      }
      else {
        zz_00d9b64_(param_1);
      }
    }
    else {
      zz_00d9b64_(param_1);
    }
  }
  return;
}



// ==== 800d9b64  zz_00d9b64_ ====

void zz_00d9b64_(int param_1)

{
  float fVar1;
  
  fVar1 = *(float *)(param_1 + 0x144);
  if (FLOAT_80438c00 < *(float *)(param_1 + 0x144)) {
    fVar1 = FLOAT_80438c00;
  }
  fVar1 = *(float *)(param_1 + 0xb4) * fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800d9bdc  FUN_800d9bdc ====

void FUN_800d9bdc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800d9c18  FUN_800d9c18 ====

void FUN_800d9c18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800d9c38  FUN_800d9c38 ====

/* WARNING: Removing unreachable block (ram,0x800d9f00) */
/* WARNING: Removing unreachable block (ram,0x800d9ed8) */

void FUN_800d9c38(int param_1)

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
  local_5c = FLOAT_80438c0c;
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  local_68 = *(float *)(param_1 + 0x38);
  local_64 = *(float *)(param_1 + 0x3c);
  local_60 = *(float *)(param_1 + 0x40);
  if (local_5c == *(float *)(param_1 + 0x3c)) {
    local_4c = local_5c;
    local_50 = FLOAT_80438c00;
    local_48 = local_5c;
    local_58 = FLOAT_80438c00;
    local_54 = local_5c;
    local_68 = local_5c;
    local_64 = local_5c;
    local_60 = FLOAT_80438c00;
  }
  else {
    if (local_60 * local_60 + local_68 * local_68 + local_64 * local_64 <= local_5c) {
      local_68 = local_5c;
      local_64 = local_5c;
      local_60 = FLOAT_80438c10;
    }
    local_5c = local_68;
    local_54 = local_60;
    local_58 = FLOAT_80438c0c;
    if (FLOAT_80438c0c < local_60 * local_60 + local_68 * local_68 + FLOAT_80438c0c * FLOAT_80438c0c
       ) {
      if (*(float *)(param_1 + 0x3c) < FLOAT_80438c0c) {
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
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= FLOAT_80438c0c) {
      local_58 = FLOAT_80438c0c;
      local_5c = FLOAT_80438c00;
      local_54 = FLOAT_80438c0c;
    }
    gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_5c);
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= FLOAT_80438c0c) {
      local_5c = FLOAT_80438c0c;
      local_58 = FLOAT_80438c00;
      local_54 = FLOAT_80438c0c;
    }
    gnt4_PSVECCrossProduct_bl(&local_5c,&local_68,&local_50);
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_80438c0c) {
      local_4c = FLOAT_80438c0c;
      local_50 = FLOAT_80438c10;
      local_48 = FLOAT_80438c0c;
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
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438c14 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                             0x3ff0000000000000)),afStack_44,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_44,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438c14 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_44,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_44,(float *)(param_1 + 0x114));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_44);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_44,(float *)(param_1 + 0x114));
  return;
}



// ==== 800d9f60  FUN_800d9f60 ====

void FUN_800d9f60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800d9fbc  zz_00d9fbc_ ====

bool zz_00d9fbc_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    zz_006de10_(param_1,2);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x2b;
    *(code **)(puVar1 + 0xc) = FUN_800da0cc;
    *(undefined **)(puVar1 + 0x10c) = &DAT_800da9f8;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800da0cc  FUN_800da0cc ====

void FUN_800da0cc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_80311298)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800da15c  FUN_800da15c ====

void FUN_800da15c(int param_1)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  iVar3 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x13) * 0x28;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  psVar2 = (short *)(&DAT_80311270 + iVar1);
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x10;
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(iVar3 + *psVar2 * 0x30 + 0x8d8);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(iVar3 + *psVar2 * 0x30 + 0x8e8);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar3 + *psVar2 * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar3 + *psVar2 * 0x30 + 0x8d4),(float *)(iVar1 + -0x7fceed8c),
             (float *)(param_1 + 0x20));
  zz_0083d60_(param_1,iVar3,0);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80311288 + iVar1),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_80311288 + iVar1);
  *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031128e + iVar1);
  iVar1 = zz_008ac80_(param_1,(int)(char)(&DAT_80311272)[iVar1]);
  if (iVar1 == 0) {
    zz_006de10_(iVar3,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x150))
    ;
    zz_00a2bf8_(iVar3,param_1,(undefined4 *)(param_1 + 0x144),(float *)(param_1 + 0x150),2,0);
  }
  return;
}



// ==== 800da2f0  FUN_800da2f0 ====

void FUN_800da2f0(int param_1)

{
  char cVar1;
  
  zz_00f0104_(*(int *)(param_1 + 0x90),7,2);
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_00da6b8_(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_00da374_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_00da7e4_(param_1);
  }
  return;
}



// ==== 800da374  zz_00da374_ ====

void zz_00da374_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x13) * 0x28;
  if (*(byte *)(param_1 + 0x1d9) == 0) {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_80311290 + iVar1)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_80311294 + iVar1);
      }
      else {
        *(float *)(param_1 + 0x44) = *(float *)(&DAT_80311290 + iVar1);
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_80311284 + iVar1),param_1);
      FUN_80083ba4((double)*(float *)(&DAT_80311280 + iVar1),param_1,
                   (char)*(undefined2 *)(&DAT_8031128e + iVar1));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0083714_(param_1);
      if (iVar2 == 0) {
        iVar2 = zz_0084170_(param_1);
        if (iVar2 == 0) {
          gnt4_PSMTXMultVec_bl
                    ((float *)(iVar3 + *(short *)(&DAT_80311270 + iVar1) * 0x30 + 0x8d4),
                     (float *)(iVar1 + -0x7fceed8c),(float *)(param_1 + 0x144));
          *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
          dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144))
          ;
          if ((double)FLOAT_80438c18 < dVar4) {
            dVar5 = 1.0 / SQRT(dVar4);
            dVar5 = DOUBLE_80438c20 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438c28);
            dVar5 = DOUBLE_80438c20 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438c28);
            dVar4 = (double)(float)(dVar4 * DOUBLE_80438c20 * dVar5 *
                                            -(dVar4 * dVar5 * dVar5 - DOUBLE_80438c28));
          }
          if ((double)FLOAT_80438c30 <= dVar4) {
            zz_006de10_(iVar3,2);
            *(undefined1 *)(param_1 + 0x18) = 2;
            zz_008aff0_(param_1);
          }
        }
        else {
          zz_006de10_(iVar3,2);
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        zz_006de10_(iVar3,2);
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      zz_006de10_(iVar3,2);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  else if ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0) {
    zz_006de10_(iVar3,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x290);
    iVar2 = *(int *)(param_1 + 0x54);
    if (*(char *)(iVar2 + 0x83) == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 10;
      zz_008aff0_(param_1);
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar3 + *(short *)(&DAT_80311270 + iVar1) * 0x30 + 0x8d4),
                 (float *)(iVar1 + -0x7fceed8c),(float *)(param_1 + 0x144));
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
      if (*(char *)(param_1 + 0x88) == *(char *)(iVar2 + 0x88)) {
        *(undefined2 *)(param_1 + 0x178) = 0x4b0;
      }
      else {
        *(undefined2 *)(param_1 + 0x178) = 2;
      }
      *(undefined1 *)(param_1 + 0x17a) = *(undefined1 *)(iVar2 + 0x71a);
      zz_0066408_(iVar2,(int)*(char *)(param_1 + 0x17a),(float *)(param_1 + 0x20),
                  (float *)(param_1 + 0x16c));
    }
    else {
      zz_006de10_(iVar3,2);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 800da6b8  zz_00da6b8_ ====

void zz_00da6b8_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar2 = *(int *)(param_1 + 0x54);
  iVar1 = *(char *)(param_1 + 0x13) * 0x28;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar3 + *(short *)(&DAT_80311270 + iVar1) * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fceed8c),(float *)(param_1 + 0x144));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar2 + *(char *)(param_1 + 0x17a) * 0x30 + 0x8d4),(float *)(param_1 + 0x16c)
             ,(float *)(param_1 + 0x150));
  if (*(char *)(iVar2 + 0x18) < '\x02') {
    iVar1 = zz_008ac80_(param_1,(int)(char)(&DAT_80311273)[iVar1]);
    if (iVar1 == 0) {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      if (*(short *)(param_1 + 0x1c) < 1) {
        zz_006de10_(iVar3,2);
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x19) = 2;
      *(undefined1 *)(param_1 + 0x1a) = 0;
    }
  }
  else {
    zz_006de10_(iVar3,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 800da7e4  zz_00da7e4_ ====

void zz_00da7e4_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x28;
  iVar3 = *(int *)(param_1 + 0x54);
  if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
     (((int)*(char *)(iVar3 + 0x3e5) & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
    if (((*(uint *)(iVar4 + 0x5e0) & 0x1000) == 0) && ((*(uint *)(iVar3 + 0x5e0) & 0x1000) == 0)) {
      if (*(char *)(iVar3 + 0x18) < '\x02') {
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar4 + *(short *)(&DAT_80311270 + iVar2) * 0x30 + 0x8d4),
                   (float *)(iVar2 + -0x7fceed8c),(float *)(param_1 + 0x144));
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar3 + *(char *)(param_1 + 0x17a) * 0x30 + 0x8d4),
                   (float *)(param_1 + 0x16c),(float *)(param_1 + 0x150));
        if (*(short *)(param_1 + 0x178) < 1) {
          zz_006de10_(iVar4,2);
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
        else {
          *(short *)(param_1 + 0x178) = *(short *)(param_1 + 0x178) + -1;
          cVar1 = *(char *)(param_1 + 0x1a);
          if (cVar1 == '\x01') {
            *(undefined1 *)(param_1 + 0x1a) = 0;
            *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x150);
            *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x154);
            *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x158);
          }
          else if ((cVar1 < '\x01') && (-1 < cVar1)) {
            *(undefined1 *)(param_1 + 0x1a) = 1;
            *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
            *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
            *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
          }
        }
      }
      else {
        zz_006de10_(iVar4,2);
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      zz_006de10_(iVar4,2);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  else {
    zz_006de10_(iVar4,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 800da9c4  FUN_800da9c4 ====

void FUN_800da9c4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800da9d8  FUN_800da9d8 ====

void FUN_800da9d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800daaf8  FUN_800daaf8 ====

void FUN_800daaf8(int param_1)

{
  zz_00c74ec_(param_1,0xf);
  return;
}



// ==== 800dab34  FUN_800dab34 ====

void FUN_800dab34(int param_1)

{
  (*(code *)(&PTR_FUN_80311c48)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800dab70  FUN_800dab70 ====

void FUN_800dab70(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(short *)(param_1 + 1000) == 0x405) {
    zz_00dabb0_(param_1);
  }
  else {
    zz_00dacc0_(param_1);
  }
  return;
}



// ==== 800dabb0  zz_00dabb0_ ====

void zz_00dabb0_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80311c54);
  return;
}



// ==== 800dabd8  FUN_800dabd8 ====

void FUN_800dabd8(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = FLOAT_80438c38;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x20);
    zz_0082824_(param_1,0x21);
  }
  return;
}



// ==== 800dac44  FUN_800dac44 ====

undefined4 FUN_800dac44(int param_1)

{
  int iVar1;
  
  if (*(float *)(param_1 + 0x558) <= FLOAT_80438c3c) {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
      return 0x8444;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  return 0;
}



// ==== 800dacc0  zz_00dacc0_ ====

void zz_00dacc0_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80311c68);
  return;
}



// ==== 800dace8  FUN_800dace8 ====

void FUN_800dace8(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,0x39);
    zz_00c3be0_(param_1,0x3a);
  }
  return;
}



// ==== 800dad40  FUN_800dad40 ====

undefined4 FUN_800dad40(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 800dada8  FUN_800dada8 ====

void FUN_800dada8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438c48;
  fVar1 = FLOAT_80438c40;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80438c48) * FLOAT_80438c40);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_80311c7c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800dae48  FUN_800dae48 ====

void FUN_800dae48(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 800dae6c  FUN_800dae6c ====

void FUN_800dae6c(int param_1)

{
  zz_00f2c3c_(param_1);
  return;
}



// ==== 800dae90  FUN_800dae90 ====

void FUN_800dae90(int param_1)

{
  zz_00f3028_(param_1);
  return;
}



// ==== 800daeb4  FUN_800daeb4 ====

void FUN_800daeb4(int param_1)

{
  zz_00f3cb4_(param_1);
  return;
}



// ==== 800daed8  FUN_800daed8 ====

void FUN_800daed8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438c48;
  fVar1 = FLOAT_80438c40;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80438c48) * FLOAT_80438c40);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_80311c90)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800daf78  FUN_800daf78 ====

void FUN_800daf78(int param_1)

{
  (*(code *)(&PTR_FUN_80311ca4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800dafb4  FUN_800dafb4 ====

void FUN_800dafb4(int param_1)

{
  char cVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d144_(param_1,0xc1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438c50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar2 = (double)FLOAT_80438c54;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800db074  FUN_800db074 ====

void FUN_800db074(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc1);
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_80438c50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      if (*(short *)(param_1 + 1000) == 0x405) {
        zz_00dd47c_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0x409) {
        zz_00dd47c_(param_1,1);
      }
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6ea) = 1;
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0x6ea) = 3;
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar4 = (double)FLOAT_80438c54;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800db1a0  FUN_800db1a0 ====

void FUN_800db1a0(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_80438c50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80438c3c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 800db250  zz_00db250_ ====

void zz_00db250_(int param_1,undefined4 *param_2,int param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_008893c_(2,0x18,1,*(int *)(&DAT_8031227c + param_3 * 8));
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0xf;
    puVar1[0x11] = (char)param_3;
    puVar1[0x13] = (char)*(undefined4 *)(&DAT_8031227c + param_3 * 8);
    *(code **)(puVar1 + 0xc) = FUN_800db378;
    *(code **)(puVar1 + 0x10c) = FUN_800db838;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
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



// ==== 800db378  FUN_800db378 ====

void FUN_800db378(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x18) < '\x02') {
    iVar1 = *(int *)(param_1 + 0x8c);
    if (('\x01' < *(char *)(iVar1 + 0x18)) ||
       ((*(char *)(iVar1 + 0x83) == '\0' && (*(short *)(iVar1 + 1000) != *(short *)(param_1 + 0x94))
        ))) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  (*(code *)(&PTR_FUN_803122c4)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800db410  FUN_800db410 ====

void FUN_800db410(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  
  uVar2 = *(char *)(param_9 + 0x13) * 0x54;
  if (uVar2 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar2);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    cVar1 = *(char *)(param_9 + 0x11);
    if ((((cVar1 == '\x02') || (cVar1 == '\x03')) || ((byte)(cVar1 - 5U) < 3)) || (cVar1 == '\x04'))
    {
      *(float *)(param_9 + 0xb4) = FLOAT_80438c58;
    }
    *(code **)(param_9 + 0x100) = FUN_800db5c8;
    uVar4 = 1;
    uVar5 = zz_0089100_(param_9,1,1);
    zz_00db940_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                (int)(&DAT_8031227c + *(char *)(param_9 + 0x11) * 8),uVar4,param_12,param_13,
                param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800db524  FUN_800db524 ====

void FUN_800db524(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  iVar1 = zz_00dba90_(param_1);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800db56c  FUN_800db56c ====

void FUN_800db56c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800db580  FUN_800db580 ====

void FUN_800db580(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800db5c8  FUN_800db5c8 ====

void FUN_800db5c8(int param_1)

{
  (*(code *)(&PTR_FUN_803122d4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800db604  FUN_800db604 ====

bool FUN_800db604(int param_1)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x118);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x128);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(iVar2 + 0x138);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(iVar2 + 0x11c);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(iVar2 + 300);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar2 + 0x13c);
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return bVar1;
}



// ==== 800db68c  FUN_800db68c ====

bool FUN_800db68c(int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [5];
  
  iVar3 = *(int *)(param_1 + 0x8c);
  local_28 = *(float *)(iVar3 + 0x120);
  local_24 = *(undefined4 *)(iVar3 + 0x130);
  local_20 = *(undefined4 *)(iVar3 + 0x140);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_28,afStack_1c);
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,afStack_1c,&DAT_802b0cb4);
  bVar2 = false;
  if (bVar1) {
    bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),4,afStack_1c,&DAT_802b0ca8);
  }
  *(float *)(param_1 + 0x120) = local_28;
  *(undefined4 *)(param_1 + 0x130) = local_24;
  *(undefined4 *)(param_1 + 0x140) = local_20;
  return bVar2;
}



// ==== 800db73c  FUN_800db73c ====

void FUN_800db73c(int param_1)

{
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
  return;
}



// ==== 800db768  FUN_800db768 ====

void FUN_800db768(int param_1)

{
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114));
  return;
}



// ==== 800db794  FUN_800db794 ====

bool FUN_800db794(int param_1)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar3 = *(int *)(param_1 + 0x8c);
  local_18 = *(float *)(iVar3 + 0x120);
  local_14 = *(undefined4 *)(iVar3 + 0x130);
  local_10 = *(undefined4 *)(iVar3 + 0x140);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_18,&local_18);
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,&local_18,&DAT_802b0cb4);
  bVar2 = false;
  if (bVar1) {
    bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),4,&local_18,&DAT_802b0ca8);
  }
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return bVar2;
}



// ==== 800db838  FUN_800db838 ====

void FUN_800db838(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [3];
  float afStack_40 [12];
  
  iVar4 = 0;
  iVar2 = 0;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar2) != 0) {
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),
                          (float *)(*(int *)(param_9 + 0x54) + iVar4 + 0x10),afStack_4c);
      if (*(char *)(param_9 + 0x11) == '\b') {
        local_58 = *(float *)(param_9 + 0x120);
        local_54 = *(undefined4 *)(param_9 + 0x130);
        local_50 = *(undefined4 *)(param_9 + 0x140);
        zz_004844c_(afStack_40,&local_58,5);
        pfVar1 = afStack_4c;
        uVar5 = zz_00456a0_(afStack_40,afStack_40,pfVar1);
      }
      else {
        pfVar1 = afStack_4c;
        uVar5 = zz_00456a0_((float *)(param_9 + 0x114),afStack_40,pfVar1);
      }
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_40,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x54;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 800db940  zz_00db940_ ====

void zz_00db940_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = 0;
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    if (((int)(short)*(ushort *)(param_9 + 0x1e) & 1 << iVar5) == 0) {
      piVar4 = (int *)(*(int *)(param_9 + 0x54) + iVar8);
      pcVar3 = (char *)(*(int *)(param_10 + 4) + iVar7);
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)(1 << iVar5);
      piVar4[0x14] = (int)*(short *)(pcVar3 + 2);
      zz_0018f88_(piVar4,*(int *)(pcVar3 + 4),(float *)(piVar4 + 4));
      uVar9 = zz_0019338_(piVar4 + 2,*(int *)(pcVar3 + 8),(float *)(piVar4 + 7));
      iVar1 = DAT_803bb374;
      if ((pcVar3[1] & 1U) != 0) {
        iVar1 = zz_0006f78_(*(int *)(param_9 + 0x90));
      }
      if ((pcVar3[1] & 2U) == 0) {
        zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                    *(int *)(iVar6 + 0xe0),(int)*pcVar3,param_12,param_13,param_14,param_15,param_16
                   );
        if ((pcVar3[1] & 4U) != 0) {
          pfVar2 = *(float **)(param_9 + 0x8c);
          uVar9 = zz_00086b8_((double)pfVar2[0x35],param_2,param_3,param_4,param_5,param_6,param_7,
                              param_8,iVar1,*(int *)(iVar6 + 0xe0),pfVar2,param_12,param_13,param_14
                              ,param_15,param_16);
          zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,param_15,
                      param_16);
        }
      }
      else {
        param_12 = (uint)*(char *)(param_9 + 0x88);
        zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                    *(int *)(iVar6 + 0xe0),(float *)(int)*pcVar3,param_12,param_13,param_14,param_15
                    ,param_16);
      }
      zz_0007cac_((double)(float)piVar4[7],*(int *)(iVar6 + 0xe0));
    }
    iVar8 = iVar8 + 0x54;
    iVar7 = iVar7 + 0xc;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 800dba90  zz_00dba90_ ====

int zz_00dba90_(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar2) break;
    if (((int)(short)*(ushort *)(param_1 + 0x1e) & 1 << iVar2) != 0) {
      piVar1 = (int *)(*(int *)(param_1 + 0x54) + iVar4);
      if (piVar1[0x14] <= (int)*(short *)(param_1 + 0x1c)) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar2);
      }
      zz_0018fd8_(piVar1,(int)*(short *)(param_1 + 0x1c),(float *)(piVar1 + 4));
      zz_0019370_(piVar1 + 2,(int)*(short *)(param_1 + 0x1c),(float *)(piVar1 + 7));
      zz_0007cac_((double)(float)piVar1[7],*(int *)(iVar3 + 0xe0));
    }
    iVar4 = iVar4 + 0x54;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 800dbb48  zz_00dbb48_ ====

void zz_00dbb48_(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (PTR_DAT_80433930[0x32] == '\0') {
    uVar3 = 0;
    iVar6 = 1;
    iVar1 = (int)(char)PTR_DAT_80433934[0x53];
    puVar2 = PTR_DAT_80433934;
    if (0 < iVar1) {
      do {
        if (puVar2[0xf6] != '\0') {
          uVar3 = puVar2[0xf4];
        }
        if (puVar2[0xf6] == '\0') {
          iVar6 = (int)(char)puVar2[0xf4];
        }
        puVar2 = puVar2 + 0x3c;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    if (param_1 == 0) {
      iVar4 = 0;
      iVar1 = 0;
      iVar5 = 0;
      while ((iVar4 < 6 && (iVar1 < 2))) {
        if ((PTR_DAT_80433934[iVar4 + 0xcb] == PTR_DAT_80433934[iVar6 * 0x3c + 0xf4]) &&
           (((-1 < *(short *)(PTR_DAT_80433934 + iVar5 + 0x10) &&
             ('\0' < (char)PTR_DAT_80433934[iVar4 + 0x20])) &&
            ((char)PTR_DAT_80433934[iVar4 + 0x20] < '\x0e')))) {
          zz_00dbf04_(2,iVar1,0,(char)iVar6);
          iVar1 = iVar1 + 1;
        }
        iVar5 = iVar5 + 2;
        iVar4 = iVar4 + 1;
      }
    }
    else {
      zz_00dbf04_(3,1,0,uVar3);
    }
  }
  return;
}



// ==== 800dbc74  zz_00dbc74_ ====

void zz_00dbc74_(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (PTR_DAT_80433930[0x32] == '\0') {
    uVar3 = 0;
    iVar6 = 1;
    iVar1 = (int)(char)PTR_DAT_80433934[0x53];
    puVar2 = PTR_DAT_80433934;
    if (0 < iVar1) {
      do {
        if (puVar2[0xf6] != '\0') {
          uVar3 = puVar2[0xf4];
        }
        if (puVar2[0xf6] == '\0') {
          iVar6 = (int)(char)puVar2[0xf4];
        }
        puVar2 = puVar2 + 0x3c;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    if (param_1 == 0) {
      zz_00dbf04_(3,0,0,uVar3);
    }
    else {
      iVar4 = 0;
      iVar1 = 0;
      iVar5 = 0;
      while ((iVar4 < 6 && (iVar1 < 2))) {
        if ((PTR_DAT_80433934[iVar4 + 0xcb] == PTR_DAT_80433934[iVar6 * 0x3c + 0xf4]) &&
           (((-1 < *(short *)(PTR_DAT_80433934 + iVar5 + 0x10) &&
             ('\0' < (char)PTR_DAT_80433934[iVar4 + 0x20])) &&
            ((char)PTR_DAT_80433934[iVar4 + 0x20] < '\x0e')))) {
          zz_00dbf04_(2,iVar1 + 2,0,(char)iVar6);
          iVar1 = iVar1 + 1;
        }
        iVar5 = iVar5 + 2;
        iVar4 = iVar4 + 1;
      }
    }
  }
  return;
}



// ==== 800dbda0  zz_00dbda0_ ====

void zz_00dbda0_(int param_1)

{
  int local_18;
  int local_14;
  undefined4 local_10;
  
  if ((PTR_DAT_80433930[0x32] == '\0') && (PTR_DAT_80433934[param_1 * 0x3c + 0xf6] != '\0')) {
    local_10 = 0xffffffff;
    local_14 = -1;
    local_18 = -1;
    zz_00dd2e4_(param_1,&local_18,0);
    if (-1 < local_18) {
      zz_00dbe44_(0,(char)local_18,(char)local_18,(char)param_1);
    }
    if (-1 < local_14) {
      zz_00dbe44_(1,(char)local_14,(char)local_14,(char)param_1);
    }
  }
  return;
}



// ==== 800dbe44  zz_00dbe44_ ====

void zz_00dbe44_(undefined1 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  
  if ((PTR_DAT_80433930[0x32] == '\0') &&
     (puVar1 = zz_008893c_(2,0x39,0,0), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = 0;
    puVar1[0x12] = param_1;
    puVar1[0x13] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800dc004;
    *(undefined **)(puVar1 + 0x10c) = (&PTR_FUN_803122f8)[(char)puVar1[0x11]];
    puVar1[0x88] = param_4;
    puVar1[0x96] = param_3;
  }
  return;
}



// ==== 800dbf04  zz_00dbf04_ ====

void zz_00dbf04_(int param_1,int param_2,int param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  int iVar2;
  
  if ((PTR_DAT_80433930[0x32] == '\0') &&
     (puVar1 = zz_008893c_(2,*(int *)(&DAT_80312318 + param_1 * 4),0,
                           *(int *)(&DAT_80312308 + param_1 * 4)), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = (char)param_1;
    puVar1[0x12] = (char)param_2;
    puVar1[0x13] = (char)param_3;
    *(code **)(puVar1 + 0xc) = FUN_800dc004;
    *(undefined **)(puVar1 + 0x10c) = (&PTR_FUN_803122f8)[(char)puVar1[0x11]];
    puVar1[0x88] = param_4;
    puVar1[0x96] = PTR_DAT_80433934[(char)puVar1[0x88] * 0x3c + 0xf8 + param_3];
    if (param_1 == 1) {
      iVar2 = zz_00ea0d8_(param_2);
      *(int *)(puVar1 + 0x14) = iVar2;
      puVar1[0x10] = PTR_DAT_80433934[(char)puVar1[0x13] + 0x2c];
    }
  }
  return;
}



// ==== 800dc004  FUN_800dc004 ====

void FUN_800dc004(int param_1)

{
  (*(code *)(&PTR_FUN_80312328)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800dc040  FUN_800dc040 ====

void FUN_800dc040(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  (*(code *)(&PTR_FUN_80312338)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800dc084  FUN_800dc084 ====

void FUN_800dc084(int param_1)

{
  (*(code *)(&PTR_FUN_80312348)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800dc0c0  FUN_800dc0c0 ====

void FUN_800dc0c0(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  
  fVar1 = FLOAT_80438c60;
  if ((*(char *)(param_1 + 0x96) < '\0') || ((&DAT_803c02c0)[*(char *)(param_1 + 0x13) * 6] == 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    iVar5 = 0;
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(&DAT_80433ba8 + *(char *)(param_1 + 0x12) * 4)
    ;
    *(float *)(param_1 + 0x24) = fVar1;
    *(float *)(param_1 + 0x28) = fVar1;
    *(undefined1 *)(param_1 + 0x82) = 0x11;
    iVar3 = (int)*(char *)(param_1 + 0x96);
    iVar2 = (int)(char)PTR_DAT_80433934[iVar3 + 0x20];
    iVar6 = 2;
    puVar4 = PTR_DAT_80433934;
    do {
      if (iVar3 != iVar5) {
        if ((puVar4[0xcb] == *(char *)(param_1 + 0x88)) &&
           (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar5) != 0)) {
          iVar2 = (int)(char)PTR_DAT_80433934[iVar5 + 0x20];
          break;
        }
      }
      if (iVar3 != iVar5 + 1) {
        if ((puVar4[0xcc] == *(char *)(param_1 + 0x88)) &&
           (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar5 + 1) != 0)) {
          iVar2 = (int)(char)PTR_DAT_80433934[iVar5 + 0x21];
          break;
        }
      }
      if (iVar3 != iVar5 + 2) {
        if ((puVar4[0xcd] == *(char *)(param_1 + 0x88)) &&
           (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar5 + 2) != 0)) {
          iVar2 = (int)(char)PTR_DAT_80433934[iVar5 + 0x22];
          break;
        }
      }
      puVar4 = puVar4 + 3;
      iVar5 = iVar5 + 3;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    *(char *)(param_1 + 0x1b) = (char)iVar2;
    if (*(char *)(param_1 + 0x12) == '\0') {
      if (PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xf5] == '\x01') {
        zz_00ea170_((int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x20],
                    (int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x26],0x13,-1);
      }
      else if (*(char *)(param_1 + 0x1b) < '\x0e') {
        zz_00ea170_((int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x20],
                    (int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x26],1,iVar2);
      }
    }
  }
  return;
}



// ==== 800dc2c4  FUN_800dc2c4 ====

void FUN_800dc2c4(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  char cVar5;
  
  fVar1 = FLOAT_80438c60;
  cVar5 = *(char *)(param_1 + 0x19);
  if (cVar5 == '\x02') {
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      uVar2 = countLeadingZeros(1 - (char)PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xf5])
      ;
      iVar3 = ((int)*(char *)(param_1 + 0x12) + (uVar2 >> 4 & 0xffffffe)) * 0x14;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(&DAT_80312358 + iVar3);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(&DAT_8031235c + iVar3);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(&DAT_80312368 + iVar3);
      if (*(char *)(param_1 + 0x12) == '\x01') {
        zz_00ea170_((int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x20],
                    (int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x96) + 0x26],0x14,-1);
      }
    }
  }
  else if (cVar5 < '\x02') {
    if (cVar5 == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      uVar2 = countLeadingZeros(1 - (char)PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xf5])
      ;
      iVar3 = ((int)*(char *)(param_1 + 0x12) + (uVar2 >> 4 & 0xffffffe)) * 0x14;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(&DAT_80312358 + iVar3);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(&DAT_8031235c + iVar3);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(&DAT_80312360 + iVar3);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(&DAT_80312364 + iVar3);
    }
    else if (cVar5 < '\0') goto LAB_800dc52c;
    fVar1 = FLOAT_80438c60;
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
    if (((fVar1 < *(float *)(param_1 + 0x38)) &&
        (*(float *)(param_1 + 0x3c) <= *(float *)(param_1 + 0x20))) ||
       ((*(float *)(param_1 + 0x38) < FLOAT_80438c60 &&
        (*(float *)(param_1 + 0x20) <= *(float *)(param_1 + 0x3c))))) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x40);
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
    }
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x4c);
  }
  else if (cVar5 < '\x04') {
    *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
    if (((fVar1 < *(float *)(param_1 + 0x38)) &&
        (*(float *)(param_1 + 0x3c) <= *(float *)(param_1 + 0x20))) ||
       ((*(float *)(param_1 + 0x38) < FLOAT_80438c60 &&
        (*(float *)(param_1 + 0x20) <= *(float *)(param_1 + 0x3c))))) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x4c);
  }
LAB_800dc52c:
  cVar5 = zz_008b290_();
  if (cVar5 == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800dc55c  FUN_800dc55c ====

void FUN_800dc55c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  undefined4 extraout_r4;
  float *pfVar9;
  int *piVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double in_f8;
  
  iVar7 = zz_00ea0d8_((int)*(char *)(param_1 + 0x12));
  if ((*(int *)(param_1 + 0x14) == iVar7) && ((char)PTR_DAT_80433934[0x45] < '\x05')) {
    if (((char)PTR_DAT_80433934[*(char *)(param_1 + 0x13) + 0x2c] < '\0') ||
       (PTR_DAT_80433934[*(char *)(param_1 + 0x13) + 0x2c] != *(char *)(param_1 + 0x10))) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
    else {
      *(code **)(param_1 + 0x100) = FUN_80047aa4;
      zz_0089100_(param_1,0x20,1);
      *(undefined1 *)(param_1 + 0x84) = 0x11;
      zz_00ea10c_();
      dVar16 = DOUBLE_80438c80;
      *(float *)(param_1 + 100) = FLOAT_80438c64;
      fVar6 = FLOAT_80438c7c;
      fVar5 = FLOAT_80438c78;
      fVar4 = FLOAT_80438c74;
      fVar3 = FLOAT_80438c70;
      fVar2 = FLOAT_80438c60;
      dVar18 = (double)FLOAT_80438c6c;
      dVar15 = (double)FLOAT_80438c70;
      dVar14 = (double)FLOAT_80438c74;
      dVar13 = (double)FLOAT_80438c78;
      dVar11 = (double)FLOAT_80438c60;
      dVar17 = (double)(float)((double)CONCAT44(0x43300000,
                                                (int)*(char *)(param_1 + 0x12) ^ 0x80000000) -
                              dVar16);
      fVar1 = (float)(dVar18 * dVar17 + (double)FLOAT_80438c68);
      dVar16 = (double)fVar1;
      *(float *)(param_1 + 0x68) = fVar1;
      *(float *)(param_1 + 0x6c) = fVar3;
      *(float *)(param_1 + 0x58) = fVar4;
      *(float *)(param_1 + 0x60) = fVar5;
      *(float *)(param_1 + 0x5c) = fVar2;
      *(float *)(param_1 + 0x3c) = fVar6;
      iVar8 = *(char *)(param_1 + 0x13) + 0x14;
      piVar10 = &DAT_803bb32c + iVar8 * 2;
      iVar7 = zz_00ea0d8_((int)*(char *)(param_1 + 0x12));
      if ((*(int *)(&DAT_803bb330 + iVar8 * 8) == 0) || (*(int *)(param_1 + 0x14) != iVar7)) {
        *(undefined1 *)(param_1 + 0x18) = 2;
      }
      else {
        pfVar9 = (float *)0x0;
        *(int *)(param_1 + 0x54) = *piVar10;
        zz_0006fb4_(dVar11,dVar13,dVar14,dVar15,dVar16,dVar17,dVar18,in_f8,*piVar10,
                    *(int *)(param_1 + 0xe0),0,param_4,param_5,param_6,param_7,param_8);
        *(undefined1 *)(param_1 + 0x144) = 0;
        dVar11 = DOUBLE_80438c80;
        *(undefined1 *)(param_1 + 0x145) = 0;
        *(undefined1 *)(param_1 + 0x146) = 1;
        uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                              (int)*(char *)(param_1 + 0x144) ^
                                                              0x80000000) - dVar11),dVar13,dVar14,
                             dVar15,dVar16,dVar17,dVar18,in_f8,*piVar10,*(int *)(param_1 + 0xe0),
                             pfVar9,param_4,param_5,param_6,param_7,param_8);
        zz_0007c30_(uVar12,dVar13,dVar14,dVar15,dVar16,dVar17,dVar18,in_f8,*(int *)(param_1 + 0xe0),
                    extraout_r4,pfVar9,param_4,param_5,param_6,param_7,param_8);
        *(undefined1 *)(param_1 + 0x82) = 0x11;
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800dc740  FUN_800dc740 ====

void FUN_800dc740(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  char cVar4;
  undefined4 extraout_r4;
  undefined8 uVar5;
  
  iVar3 = zz_00ea0d8_((int)*(char *)(param_9 + 0x12));
  fVar2 = FLOAT_80438c60;
  if ((*(int *)(param_9 + 0x14) == iVar3) && ((char)PTR_DAT_80433934[0x45] < '\x05')) {
    if (((char)PTR_DAT_80433934[*(char *)(param_9 + 0x13) + 0x2c] < '\0') ||
       (PTR_DAT_80433934[*(char *)(param_9 + 0x13) + 0x2c] != *(char *)(param_9 + 0x10))) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
    else {
      cVar1 = *(char *)(param_9 + 0x19);
      if (cVar1 != '\x02') {
        if ('\x01' < cVar1) {
          if ('\x03' < cVar1) {
            return;
          }
          *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) - *(float *)(param_9 + 0x3c);
          if (fVar2 < *(float *)(param_9 + 0x5c)) {
            return;
          }
          *(float *)(param_9 + 0x5c) = fVar2;
          *(undefined1 *)(param_9 + 0x18) = 2;
          *(undefined1 *)(param_9 + 0x82) = 0;
          return;
        }
        if (cVar1 == '\0') {
          iVar3 = zz_00ea0f0_((int)*(char *)(param_9 + 0x12));
          if (iVar3 == 0) {
            return;
          }
          *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        }
        else if (cVar1 < '\0') {
          return;
        }
        fVar2 = FLOAT_80438c74;
        param_2 = (double)*(float *)(param_9 + 0x5c);
        *(float *)(param_9 + 0x5c) = (float)(param_2 + (double)*(float *)(param_9 + 0x3c));
        if (*(float *)(param_9 + 0x5c) < fVar2) {
          return;
        }
        *(float *)(param_9 + 0x5c) = fVar2;
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      }
      cVar1 = *(char *)(param_9 + 0x144);
      iVar3 = zz_00e9b44_((int)*(char *)(param_9 + 0x12));
      if (iVar3 == 0) {
        iVar3 = zz_00ea0bc_((int)*(char *)(param_9 + 0x12));
        cVar4 = (char)iVar3;
      }
      else {
        cVar4 = *(char *)(param_9 + 0x144);
      }
      if (cVar4 == -1) {
        if (*(char *)(param_9 + 0x145) == -1) {
          cVar4 = *(char *)(param_9 + 0x147) + -1;
          *(char *)(param_9 + 0x147) = cVar4;
          if (cVar4 < '\x01') {
            *(undefined1 *)(param_9 + 0x147) = 3;
            *(char *)(param_9 + 0x144) = *(char *)(param_9 + 0x144) + *(char *)(param_9 + 0x146);
            if ((*(char *)(param_9 + 0x144) < '\x01') || ('\x01' < *(char *)(param_9 + 0x144))) {
              *(char *)(param_9 + 0x146) = -*(char *)(param_9 + 0x146);
            }
          }
        }
        else {
          *(undefined1 *)(param_9 + 0x146) = 1;
          *(undefined1 *)(param_9 + 0x147) = 3;
          *(undefined1 *)(param_9 + 0x144) = 0;
        }
        *(undefined1 *)(param_9 + 0x145) = 0xff;
        cVar4 = *(char *)(param_9 + 0x144);
      }
      else {
        *(char *)(param_9 + 0x145) = cVar4;
      }
      iVar3 = zz_00ea0f0_((int)*(char *)(param_9 + 0x12));
      if (iVar3 == 0) {
        cVar4 = '\0';
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      }
      if (cVar1 != cVar4) {
        *(char *)(param_9 + 0x144) = cVar4;
        uVar5 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(char *)(param_9 + 0x144) ^
                                                             0x80000000) - DOUBLE_80438c80),param_2,
                            param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54)
                            ,*(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                            param_16);
        zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 800dc9f0  FUN_800dc9f0 ====

void FUN_800dc9f0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  int local_38;
  int local_34;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  uVar9 = DAT_802b1ce0;
  uVar10 = DAT_802b1cdc;
  uVar11 = DAT_802b1cd8;
  uVar12 = DAT_802b1cd4;
  local_2c = DAT_802b1cd0;
  local_28 = DAT_802b1cd4;
  local_24 = DAT_802b1cd8;
  local_20 = DAT_802b1cdc;
  local_1c = DAT_802b1ce0;
  local_18 = DAT_802b1ce4;
  *(code **)(param_9 + 0x100) = FUN_800dd070;
  zz_0089100_(param_9,0x21,1);
  *(undefined1 *)(param_9 + 0x84) = 1;
  fVar3 = FLOAT_80438c8c;
  fVar2 = FLOAT_80438c88;
  fVar1 = FLOAT_80438c60;
  dVar15 = (double)FLOAT_80438c88;
  dVar13 = (double)FLOAT_80438c8c;
  iVar4 = (*(byte *)(param_9 + 0x12) & 1) * 0xc;
  uVar5 = *(undefined4 *)(&DAT_803123ac + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803123a8 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar5;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803123b0 + iVar4);
  *(float *)(param_9 + 0x38) = fVar2;
  *(undefined2 *)(param_9 + 0x1c) = 0xc;
  *(short *)(param_9 + 0x1e) = (*(short *)(param_9 + 0x1c) + -10) * 2;
  *(float *)(param_9 + 0x9c) = fVar3;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(undefined *)(param_9 + 0x144) = PTR_DAT_80433934[0xef];
  iVar6 = (*(byte *)(param_9 + 0x12) & 1) + 0x15;
  if (*(int *)(&DAT_803bb330 + iVar6 * 8) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    uVar14 = zz_0006fb4_(dVar13,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                         (&DAT_803bb32c)[iVar6 * 2],*(int *)(param_9 + 0xe0),0,&DAT_803123a8 + iVar4
                         ,uVar9,uVar10,uVar11,uVar12);
    pcVar8 = (char *)0x0;
    iVar4 = *(int *)(param_9 + 0xe4) + 0x18;
    uVar14 = zz_00070e4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                         (&DAT_803bb32c)[iVar6 * 2],*(int *)(param_9 + 0xe4),0,iVar4,uVar9,uVar10,
                         uVar11,uVar12);
    uVar14 = zz_0007ae4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xe0),&local_2c,pcVar8,iVar4,uVar9,uVar10,uVar11,uVar12)
    ;
    zz_0007ae4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),&local_2c,pcVar8,iVar4,uVar9,uVar10,uVar11,uVar12);
    zz_0007cac_((double)FLOAT_80438c90,*(int *)(param_9 + 0xe4));
    *(undefined4 *)(*(int *)(param_9 + 0xe4) + 0x18) = 0xff;
    *(undefined4 *)(*(int *)(param_9 + 0xe4) + 0x1c) = 0xff;
    if ((*(byte *)(param_9 + 0x12) & 1) == 0) {
      local_30 = -1;
      local_34 = -1;
      local_38 = -1;
      zz_00dd2e4_((int)*(char *)(param_9 + 0x88),&local_38,1);
      *(undefined1 *)(param_9 + 0x87) = 0xff;
      *(undefined1 *)(param_9 + 0x1a) = 1;
      if (-1 < local_30) {
        *(undefined *)(param_9 + 0x87) = PTR_DAT_80433934[local_30 + 0x20];
        *(undefined1 *)(param_9 + 0x1a) = 0;
      }
      iVar4 = 0x10 - (*(byte *)(param_9 + 0x12) >> 1 & 1);
      *(char *)(param_9 + 0x1b) = (char)iVar4;
      if (-1 < local_34) {
        uVar7 = zz_00ea170_((int)(char)PTR_DAT_80433934[local_34 + 0x20],0,iVar4,-1);
        *(char *)(param_9 + 0x89) = (char)uVar7;
      }
    }
    *(undefined1 *)(param_9 + 0x82) = 0x11;
  }
  return;
}



// ==== 800dcc24  FUN_800dcc24 ====

void FUN_800dcc24(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  
  if (((((*(byte *)(param_1 + 0x12) & 1) == 0) && (*(char *)(param_1 + 0x1a) == '\0')) &&
      (PTR_DAT_80433934[0xef] == '\x01')) &&
     ((-1 < *(char *)(param_1 + 0x89) &&
      (iVar4 = zz_00ea0f0_((int)*(char *)(param_1 + 0x89)), iVar4 == 0)))) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    zz_00ea170_((int)*(char *)(param_1 + 0x87),0,(int)*(char *)(param_1 + 0x1b),-1);
  }
  fVar3 = FLOAT_80438c8c;
  fVar2 = FLOAT_80438c88;
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    if ((*(char *)(param_1 + 0x11) == '\x02') && ('\x01' < (char)PTR_DAT_80433934[0xef])) {
      *(undefined1 *)(param_1 + 0x19) = 3;
      *(float *)(param_1 + 0x38) = fVar2;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(float *)(param_1 + 0x9c) = *(float *)(param_1 + 0x9c) + *(float *)(param_1 + 0x38);
      sVar5 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar5;
      fVar2 = FLOAT_80438c94;
      if (sVar5 < 1) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) * fVar2;
      }
    }
    else if (-1 < cVar1) {
      *(float *)(param_1 + 0x9c) = *(float *)(param_1 + 0x9c) - *(float *)(param_1 + 0x38);
      sVar5 = *(short *)(param_1 + 0x1e) + -1;
      *(short *)(param_1 + 0x1e) = sVar5;
      if (sVar5 < 1) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
  }
  else if ((cVar1 < '\x04') &&
          (*(float *)(param_1 + 0x9c) = *(float *)(param_1 + 0x9c) - *(float *)(param_1 + 0x38),
          fVar3 < *(float *)(param_1 + 0x9c))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800dcdbc  FUN_800dcdbc ====

void FUN_800dcdbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  int local_18;
  int local_14;
  undefined4 local_10;
  
  *(undefined *)(param_9 + 0x15c) = PTR_DAT_80433934[0xef];
  if (DAT_803bb3d0 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    pfVar2 = (float *)0x0;
    *(undefined4 *)(param_9 + 0x54) = DAT_803bb3cc;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),0,param_12,param_13,param_14,
                param_15,param_16);
    *(float *)(param_9 + 0xd4) = FLOAT_80438c60;
    uVar4 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),pfVar2,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,param_15,
                param_16);
    local_10 = 0xffffffff;
    local_14 = -1;
    local_18 = -1;
    zz_00dd2e4_((int)*(char *)(param_9 + 0x88),&local_18,1);
    *(undefined1 *)(param_9 + 0x87) = 0xff;
    *(undefined1 *)(param_9 + 0x1a) = 1;
    if (-1 < local_14) {
      *(undefined *)(param_9 + 0x87) = PTR_DAT_80433934[local_14 + 0x20];
      *(undefined1 *)(param_9 + 0x1a) = 0;
    }
    uVar1 = countLeadingZeros((int)*(char *)(param_9 + 0x12));
    iVar3 = 0x10 - (uVar1 >> 5 & 1);
    uVar1 = zz_00ea170_(0,0,iVar3,-1);
    *(char *)(param_9 + 0x89) = (char)uVar1;
    *(char *)(param_9 + 0x1b) = (char)iVar3;
    *(undefined1 *)(param_9 + 0x82) = 0x11;
  }
  return;
}



// ==== 800dcee4  FUN_800dcee4 ====

/* WARNING: Removing unreachable block (ram,0x800dd020) */
/* WARNING: Removing unreachable block (ram,0x800dcef4) */

void FUN_800dcee4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined8 uVar4;
  double dVar5;
  
  fVar2 = FLOAT_80438c9c;
  if (*(char *)(param_9 + 0x12) == '\0') {
    fVar2 = FLOAT_80438c98;
  }
  dVar5 = (double)fVar2;
  if ((((*(char *)(param_9 + 0x1a) == '\0') && (PTR_DAT_80433934[0xef] == '\0')) &&
      (-1 < *(char *)(param_9 + 0x89))) &&
     (iVar3 = zz_00ea0f0_((int)*(char *)(param_9 + 0x89)), iVar3 == 0)) {
    param_12 = 0xffffffff;
    *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    param_11 = (float *)(int)*(char *)(param_9 + 0x1b);
    zz_00ea170_((int)*(char *)(param_9 + 0x87),0,(int)param_11,-1);
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    if ('\x01' < (char)PTR_DAT_80433934[0xef]) {
      *(undefined1 *)(param_9 + 0x19) = 2;
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) &&
       (*(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + FLOAT_80438c78,
       dVar5 <= (double)*(float *)(param_9 + 0xd4))) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(float *)(param_9 + 0xd4) = (float)dVar5;
    }
  }
  else if (cVar1 < '\x03') {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + FLOAT_80438c78;
  }
  uVar4 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,
                      param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800dd050  FUN_800dd050 ====

void FUN_800dd050(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800dd070  FUN_800dd070 ====

void FUN_800dd070(int param_1)

{
  float afStack_38 [13];
  
  FUN_80047aa4(param_1);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x9c),(double)*(float *)(param_1 + 0xa0),
                     (double)*(float *)(param_1 + 0xa4),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  return;
}



// ==== 800dd0d8  FUN_800dd0d8 ====

void FUN_800dd0d8(int param_1)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  DAT_803c1140 = &local_2c;
  DAT_803c1144 = &local_38;
  DAT_803c115c = &local_40;
  DAT_803c1150 = &local_48;
  local_40 = DAT_80438ca0;
  local_3c = DAT_80438ca4;
  local_48 = DAT_80438ca8;
  local_44 = DAT_80438cac;
  local_2c = FLOAT_80438c60;
  local_28 = FLOAT_80438c60;
  local_20 = FLOAT_80438cb0;
  local_1c = FLOAT_80438cb4;
  local_18 = FLOAT_80438cb8;
  local_24 = FLOAT_80438cb8;
  local_38 = *(undefined4 *)(param_1 + 0x20);
  local_34 = *(undefined4 *)(param_1 + 0x24);
  local_30 = *(undefined4 *)(param_1 + 0x28);
  DAT_803c113c = 0;
  DAT_803c1174 = FLOAT_80438c78;
  DAT_803c1164 = 5;
  DAT_803c1168 = 0xf;
  DAT_803c1160 = &DAT_803c02c0 + *(char *)(param_1 + 0x13) * 6;
  DAT_803c1170 = 1;
  DAT_803c1173 = 0xff;
  FUN_80051ef4(-0x7fc3eed0);
  return;
}



// ==== 800dd1e8  FUN_800dd1e8 ====

void FUN_800dd1e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),1);
  return;
}



// ==== 800dd228  FUN_800dd228 ====

void FUN_800dd228(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char **ppcVar1;
  undefined4 *puVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  char *local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  puVar2 = &DAT_802b1ce8;
  local_18 = DAT_802b1ce8;
  local_14 = DAT_802b1cec;
  local_10 = DAT_802b1cf0;
  zz_0007834_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x20),DAT_802b1ce8,&DAT_802b1ce8,
              in_r7,in_r8,in_r9,in_r10);
  zz_0009958_(*(int *)(param_9 + 0xe0),0);
  ppcVar1 = &local_18;
  uVar3 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)ppcVar1,(float *)ppcVar1);
  zz_0007834_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,&local_18,(char *)ppcVar1,puVar2,in_r7,in_r8,in_r9,in_r10);
  zz_0009958_(*(int *)(param_9 + 0xe4),0);
  return;
}



// ==== 800dd2b0  FUN_800dd2b0 ====

void FUN_800dd2b0(int param_1)

{
  if (*(char *)(*(int *)(param_1 + 0xe0) + 0x10) != '\0') {
    zz_0009958_(*(int *)(param_1 + 0xe0),0);
  }
  return;
}



// ==== 800dd2e4  zz_00dd2e4_ ====

void zz_00dd2e4_(int param_1,int *param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  pcVar4 = PTR_DAT_80433934 + param_1 * 0x3c + 0xf4;
  if (param_3 != 0) {
    iVar5 = 0;
    iVar6 = 1;
    iVar2 = 4;
    iVar3 = 0;
    iVar7 = 3;
    do {
      if (PTR_DAT_80433934[iVar5 + 0xcb] == *pcVar4) {
        if (-1 < *(short *)(PTR_DAT_80433934 + iVar3 + 0x10)) {
          cVar1 = PTR_DAT_80433934[iVar5 + 0x20];
          if (cVar1 == '\0') {
            *param_2 = iVar5;
          }
          else if (((iVar6 < 3) && ('\0' < cVar1)) && (cVar1 < '\x0e')) {
            *(int *)((int)param_2 + iVar2) = iVar5;
            iVar6 = iVar6 + 1;
            iVar2 = iVar2 + 4;
          }
        }
      }
      if (PTR_DAT_80433934[iVar5 + 0xcc] == *pcVar4) {
        if (-1 < *(short *)(PTR_DAT_80433934 + iVar3 + 0x12)) {
          cVar1 = PTR_DAT_80433934[iVar5 + 0x21];
          if (cVar1 == '\0') {
            *param_2 = iVar5 + 1;
          }
          else if (((iVar6 < 3) && ('\0' < cVar1)) && (cVar1 < '\x0e')) {
            *(int *)((int)param_2 + iVar2) = iVar5 + 1;
            iVar6 = iVar6 + 1;
            iVar2 = iVar2 + 4;
          }
        }
      }
      iVar3 = iVar3 + 4;
      iVar5 = iVar5 + 2;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    return;
  }
  iVar3 = 0;
  iVar5 = 1;
  iVar2 = 4;
  while( true ) {
    if (pcVar4[1] <= iVar3) break;
    iVar6 = (int)pcVar4[iVar3 + 4];
    if (-1 < iVar6) {
      cVar1 = PTR_DAT_80433934[iVar6 + 0x20];
      if (cVar1 == '\0') {
        *param_2 = iVar6;
      }
      else if (((iVar5 < 3) && ('\0' < cVar1)) && (cVar1 < '\x0e')) {
        *(int *)((int)param_2 + iVar2) = iVar6;
        iVar5 = iVar5 + 1;
        iVar2 = iVar2 + 4;
      }
    }
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 800dd47c  zz_00dd47c_ ====

void zz_00dd47c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2d;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800dd57c;
    *(code **)(puVar1 + 0x10c) = FUN_800ddb08;
    puVar1[0x13] = 4;
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



// ==== 800dd57c  FUN_800dd57c ====

void FUN_800dd57c(int param_1)

{
  zz_00f0104_(*(int *)(param_1 + 0x90),0x15,2);
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_80312468)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800dd5e0  FUN_800dd5e0 ====

void FUN_800dd5e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar6;
  double dVar7;
  undefined8 uVar8;
  
  dVar7 = DOUBLE_80438cc8;
  fVar1 = FLOAT_80438cc0;
  uVar5 = (uint)*(byte *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = uVar5 * 0x14;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  psVar6 = (short *)(&DAT_80312440 + iVar4);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80312442 + iVar4);
  uVar2 = *(undefined4 *)(&DAT_8031244c + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80312448 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80312450 + iVar4);
  *(undefined *)(param_9 + 0x144) = (&DAT_80312444)[iVar4];
  *(undefined *)(param_9 + 0x145) = (&DAT_80312445)[iVar4];
  *(undefined *)(param_9 + 0x146) = (&DAT_80312446)[iVar4];
  *(undefined *)(param_9 + 0x147) = (&DAT_80312447)[iVar4];
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x144) ^ 0x80000000) - dVar7);
  piVar3 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x38);
  *(int **)(param_9 + 0xdc) = piVar3;
  uVar8 = zz_00ddb48_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      (char *)(int)*psVar6,iVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
  zz_00ddc20_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  *(code **)(param_9 + 0x100) = FUN_800dd97c;
  uVar2 = 1;
  uVar8 = zz_0089100_(param_9,1,1);
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x96) + 0x31;
  zz_00dd700_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              (uint)*(byte *)(param_9 + 0x96),uVar2,uVar5,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800dd700  zz_00dd700_ ====

void zz_00dd700_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short sVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  undefined8 uVar4;
  
  if ((*(uint *)(*(int *)(param_9 + 0x90) + 0x5e0) & 0x2000000) == 0) {
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x6cb) != '\0') {
      if (*(char *)(param_9 + 0x19) != '\x02') {
        *(undefined1 *)(param_9 + 0x19) = 2;
        fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x146) ^ 0x80000000) -
                       DOUBLE_80438cc8);
        *(float *)(param_9 + 0xd8) = fVar1;
        *(float *)(param_9 + 0xd4) = fVar1;
      }
    }
    (*(code *)(&PTR_FUN_80312478)[*(char *)(param_9 + 0x19)])(param_9);
    uVar4 = zz_00dde88_(param_9);
    uVar3 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0x60) = uVar3;
    *(undefined4 *)(param_9 + 0x5c) = uVar3;
    *(undefined4 *)(param_9 + 0x58) = uVar3;
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    uVar3 = extraout_r4;
    if (sVar2 < 1) {
      uVar4 = zz_00ddc20_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      uVar3 = extraout_r4_00;
    }
    zz_00ddd70_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,param_11
                ,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 800dd7fc  FUN_800dd7fc ====

void FUN_800dd7fc(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = *(float *)(param_1 + 0xd4) + FLOAT_80438cd0;
  *(float *)(param_1 + 0xd4) = fVar1;
  dVar2 = DOUBLE_80438cc8;
  if (*(float *)(param_1 + 0xd8) <= fVar1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x145) ^ 0x80000000) -
                   dVar2);
    *(float *)(param_1 + 0xd8) = fVar1;
    *(float *)(param_1 + 0xd4) = fVar1;
  }
  *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xd4) / *(float *)(param_1 + 0xd8);
  return;
}



// ==== 800dd870  FUN_800dd870 ====

void FUN_800dd870(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80438cc0;
  fVar1 = *(float *)(param_1 + 0xd4) - FLOAT_80438cd0;
  *(float *)(param_1 + 0xd4) = fVar1;
  dVar3 = DOUBLE_80438cc8;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x146) ^ 0x80000000) -
                   dVar3);
    *(float *)(param_1 + 0xd8) = fVar1;
    *(float *)(param_1 + 0xd4) = fVar1;
  }
  return;
}



// ==== 800dd8d4  FUN_800dd8d4 ====

void FUN_800dd8d4(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438cc0;
  fVar1 = *(float *)(param_1 + 0xd4) - FLOAT_80438cd0;
  *(float *)(param_1 + 0xd4) = fVar1;
  if (fVar1 <= fVar2) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(float *)(param_1 + 0xd4) = fVar2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xd4) / *(float *)(param_1 + 0xd8);
  return;
}



// ==== 800dd934  FUN_800dd934 ====

void FUN_800dd934(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800dd97c  FUN_800dd97c ====

/* WARNING: Removing unreachable block (ram,0x800dda8c) */

void FUN_800dd97c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  float afStack_48 [13];
  
  iVar4 = *(int *)(param_9 + 0x8c);
  zz_00455fc_((float *)(iVar4 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),(float *)(param_9 + 0x114)
              ,(float *)(param_9 + 100));
  zz_00456a0_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),(float *)(param_9 + 0x58));
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x120);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x130);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x140);
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar7 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar6 = 0;
    while (iVar7 < *(char *)(param_9 + 0x13)) {
      if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar7) != 0) {
        pfVar5 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar6);
        zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar5);
        pfVar5 = pfVar5 + 3;
        uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar5);
        if (iVar2 == 0) {
          pfVar5 = (float *)&DAT_80438cdc;
          gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80438cd4,0x495,&DAT_80438cdc,iVar4,in_r7,in_r8,in_r9,in_r10);
        }
        uVar8 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                       (undefined *)pfVar5,iVar4,in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
      iVar6 = iVar6 + 0x38;
      iVar7 = iVar7 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 800ddb08  FUN_800ddb08 ====

void FUN_800ddb08(int param_1)

{
  if ((*(int *)(param_1 + 0xdc) != 0) && (*(short *)(param_1 + 0x1e) != 0)) {
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 800ddb48  zz_00ddb48_ ====

void zz_00ddb48_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,char *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar3 = (int)*(char *)(param_9 + 0x13);
    uVar5 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        *(int *)(param_9 + 0xe0),param_10,iVar3,param_13,param_14,param_15,param_16)
    ;
    iVar4 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    while (iVar4 < *(char *)(param_9 + 0x13)) {
      uVar1 = *(ushort *)(param_9 + 0x1e);
      *(ushort *)(param_9 + 0x1e) = uVar1 & ~(ushort)(1 << iVar4);
      uVar5 = gnt4_HSD_JObjSetFlagsAll
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                         (undefined *)(int)(short)uVar1,iVar3,param_13,param_14,param_15,param_16);
      iVar4 = iVar4 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 800ddc20  zz_00ddc20_ ====

void zz_00ddc20_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  float *pfVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar6;
  int iVar7;
  undefined8 uVar8;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar7 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar7) break;
      uVar5 = 1 << iVar7;
      if (((int)*(short *)(param_9 + 0x1e) & uVar5) == 0) {
        iVar1 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(short *)(param_9 + 0x1c) = (short)*(char *)(param_9 + 0x147);
        uVar3 = 0;
        pfVar6 = (float *)(iVar1 + iVar7 * 0x38);
        uVar4 = (int)*(short *)(param_9 + 0x1e) | uVar5;
        *(short *)(param_9 + 0x1e) = (short)uVar4;
        *(undefined2 *)(pfVar6 + 7) = 0;
        *(undefined2 *)((int)pfVar6 + 0x1e) = 0x1e;
        zz_0018f88_((int *)(pfVar6 + 8),-0x7fcedc40,pfVar6 + 3);
        zz_0018f88_((int *)(pfVar6 + 10),-0x7fcedc10,pfVar6);
        pfVar2 = pfVar6 + 6;
        uVar8 = zz_0019338_((int *)(pfVar6 + 0xc),-0x7fcedbe0,pfVar2);
        iVar1 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(iVar1 + 0x10);
        }
        if (0 < iVar7) {
          do {
            if (iVar1 == 0) {
              iVar1 = 0;
            }
            else {
              iVar1 = *(int *)(iVar1 + 8);
            }
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                   (undefined *)pfVar2,uVar3,uVar4,uVar5,in_r9,in_r10);
        zz_00091e4_((double)pfVar6[6],iVar1);
        iVar7 = (int)*(char *)(param_9 + 0x13);
      }
      iVar7 = iVar7 + 1;
    }
  }
  return;
}



// ==== 800ddd70  zz_00ddd70_ ====

void zz_00ddd70_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar6) break;
      puVar3 = (undefined *)(1 << iVar6);
      if (((int)*(short *)(param_9 + 0x1e) & (uint)puVar3) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5);
        sVar1 = *(short *)(pfVar4 + 7);
        *(short *)(pfVar4 + 7) = sVar1 + 1;
        if (*(short *)((int)pfVar4 + 0x1e) <= (short)(sVar1 + 1)) {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) & ~(ushort)puVar3;
          gnt4_HSD_JObjSetFlagsAll
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                     puVar3,param_12,param_13,param_14,param_15,param_16);
        }
        zz_0018fd8_((int *)(pfVar4 + 8),(int)*(short *)(pfVar4 + 7),pfVar4 + 3);
        zz_0018fd8_((int *)(pfVar4 + 10),(int)*(short *)(pfVar4 + 7),pfVar4);
        zz_0019370_((int *)(pfVar4 + 0xc),(int)*(short *)(pfVar4 + 7),pfVar4 + 6);
        param_1 = zz_00091e4_((double)pfVar4[6],iVar2);
      }
      iVar5 = iVar5 + 0x38;
      iVar6 = iVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 800dde88  zz_00dde88_ ====

/* WARNING: Removing unreachable block (ram,0x800de038) */
/* WARNING: Removing unreachable block (ram,0x800dde98) */

void zz_00dde88_(int param_1)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_44;
  undefined4 local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x6cb) == '\0') {
    puVar4 = &DAT_803c4e84;
    iVar3 = 0;
    do {
      pcVar2 = (char *)*puVar4;
      if (((((pcVar2 != *(char **)(param_1 + 0x90)) && (*pcVar2 != '\0')) &&
           (pcVar2[0x18] == '\x01')) &&
          ((pcVar2[0x6cb] == '\0' && (*(float *)(pcVar2 + 0x720) <= FLOAT_80438cc0)))) &&
         (((*(ushort *)(pcVar2 + 0x272) & 2) == 0 &&
          ((*(float *)(pcVar2 + 0x204) < FLOAT_80438ce4 && (pcVar2[0x743] != '\0')))))) {
        iVar1 = *(int *)(param_1 + 0x8c);
        local_44 = *(float *)(param_1 + 100);
        local_40 = *(undefined4 *)(param_1 + 0x68);
        dVar6 = (double)(FLOAT_80438ce8 * *(float *)(param_1 + 0xb4));
        local_3c = (float)((double)*(float *)(param_1 + 0x6c) + dVar6);
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),&local_44,&local_44);
        local_38 = *(float *)(pcVar2 + 0x910);
        local_34 = *(undefined4 *)(pcVar2 + 0x920);
        local_30 = *(undefined4 *)(pcVar2 + 0x930);
        dVar7 = (double)(float)(dVar6 * (double)*(float *)(iVar1 + 0xb4));
        dVar6 = gnt4_PSVECSquareDistance_bl(&local_44,&local_38);
        if ((double)FLOAT_80438cc0 < dVar6) {
          dVar5 = 1.0 / SQRT(dVar6);
          dVar5 = DOUBLE_80438cf0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80438cf8);
          dVar5 = DOUBLE_80438cf0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80438cf8);
          dVar6 = (double)(float)(dVar6 * DOUBLE_80438cf0 * dVar5 *
                                          -(dVar6 * dVar5 * dVar5 - DOUBLE_80438cf8));
        }
        if (dVar6 <= dVar7) {
          zz_00de054_(param_1,(int)pcVar2,&local_38);
        }
      }
      iVar3 = iVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (iVar3 < 6);
  }
  return;
}



// ==== 800de054  zz_00de054_ ====

void zz_00de054_(int param_1,int param_2,float *param_3)

{
  double dVar1;
  float fStack_28;
  float local_24;
  float fStack_1c;
  float local_18;
  
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x8c) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
             (float *)(param_1 + 100),&fStack_1c);
  gnt4_PSVECSubtract_bl(&fStack_1c,param_3,&fStack_28);
  dVar1 = gnt4_PSVECMag_bl(&fStack_28);
  if ((double)FLOAT_80438d00 <= dVar1) {
    gnt4_PSVECNormalize_bl(&fStack_28,&fStack_28);
    if (*(char *)(param_2 + 0x87) == '\0') {
      local_18 = local_18 - param_3[1];
      if (local_18 < FLOAT_80438cc0) {
        local_18 = -local_18;
      }
      if (FLOAT_80438d00 <= local_18) {
        if (FLOAT_80438d04 <= local_24) {
          *(float *)(param_2 + 0x48) = FLOAT_80438cc0;
          *(byte *)(param_2 + 0x732) = *(byte *)(param_2 + 0x732) | 2;
        }
      }
    }
    else if (FLOAT_80438cc0 < local_24) {
      if (*(float *)(param_2 + 0x48) <= FLOAT_80438cc0) {
        *(float *)(param_2 + 0x48) = FLOAT_80438cc0;
      }
      *(byte *)(param_2 + 0x732) = *(byte *)(param_2 + 0x732) | 2;
    }
    gnt4_PSQUATScale_bl((double)FLOAT_80438d08,&fStack_28,&fStack_28);
    zz_0084498_(param_2,&fStack_28);
  }
  return;
}



// ==== 800de28c  FUN_800de28c ====

void FUN_800de28c(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  for (sVar1 = 0; sVar1 < 2; sVar1 = sVar1 + 1) {
    zz_0147a54_(param_1,(char)sVar1);
  }
  return;
}



// ==== 800de2f8  FUN_800de2f8 ====

void FUN_800de2f8(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438d18) * FLOAT_80438d10);
  }
  return;
}



// ==== 800de37c  FUN_800de37c ====

void FUN_800de37c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80313448)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800de3bc  FUN_800de3bc ====

void FUN_800de3bc(int param_1)

{
  zz_0144dc4_(param_1,0);
  return;
}



// ==== 800de3e0  FUN_800de3e0 ====

void FUN_800de3e0(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x40);
  return;
}



// ==== 800de418  FUN_800de418 ====

void FUN_800de418(int param_1)

{
  (*(code *)(&PTR_FUN_80313458)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800de454  FUN_800de454 ====

void FUN_800de454(int param_1)

{
  (*(code *)(&PTR_FUN_80313464)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800de490  FUN_800de490 ====

void FUN_800de490(int param_1)

{
  zz_014a200_(param_1,&DAT_80433bb0);
  return;
}



// ==== 800de4b4  FUN_800de4b4 ====

void FUN_800de4b4(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80433bb8);
  return;
}



// ==== 800de4d8  FUN_800de4d8 ====

void FUN_800de4d8(int param_1)

{
  zz_0082824_(param_1,0x1a);
  return;
}



// ==== 800de4fc  FUN_800de4fc ====

void FUN_800de4fc(int param_1)

{
  (*(code *)(&PTR_FUN_80313478)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800de538  FUN_800de538 ====

void FUN_800de538(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 800de55c  FUN_800de55c ====

void FUN_800de55c(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 800de580  FUN_800de580 ====

void FUN_800de580(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 800de5a4  zz_00de5a4_ ====

bool zz_00de5a4_(int param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800de6b4;
    *(code **)(puVar1 + 0x10c) = FUN_800de864;
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
    *(undefined4 *)(puVar1 + 0x144) = param_3;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800de6b4  FUN_800de6b4 ====

void FUN_800de6b4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80313878)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800de708  FUN_800de708 ====

void FUN_800de708(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438d20;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_803137f0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803137ec + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803137f4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803137f8 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803137fc + iVar3);
  *(undefined *)(param_9 + 0x89) = (&DAT_803137ea)[iVar3];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_803137e8 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_803137e8 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438d24,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00de834_();
  return;
}



// ==== 800de834  zz_00de834_ ====

void zz_00de834_(void)

{
  return;
}



// ==== 800de844  FUN_800de844 ====

void FUN_800de844(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800de864  FUN_800de864 ====

void FUN_800de864(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (**(char **)(param_9 + 0x144) == '\0') {
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
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 800de8f4  zz_00de8f4_ ====

bool zz_00de8f4_(int param_1)

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
      *(code **)(puVar1 + 0xc) = FUN_800dea0c;
      *(code **)(puVar1 + 0x10c) = FUN_800dec30;
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



// ==== 800dea0c  FUN_800dea0c ====

void FUN_800dea0c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803138e8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800dea60  FUN_800dea60 ====

void FUN_800dea60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438d28;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80313890 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031388c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80313894 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80313898 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031389c + iVar3);
  *(undefined *)(param_9 + 0x89) = (&DAT_8031388a)[iVar3];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80313888 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80313888 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438d2c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00deb8c_(param_9);
  return;
}



// ==== 800deb8c  zz_00deb8c_ ====

void zz_00deb8c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438d30;
  fVar1 = FLOAT_80438d28;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x146) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_80438d30;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_80438d28) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80438d30;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_80438d28;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800dec10  FUN_800dec10 ====

void FUN_800dec10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800dec30  FUN_800dec30 ====

void FUN_800dec30(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x146) == '\0') {
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



// ==== 800decc8  zz_00decc8_ ====

undefined1 * zz_00decc8_(int param_1,float *param_2,undefined4 param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x10;
    puVar1[0x11] = 0;
    puVar1[0x12] = param_4;
    puVar1[0x13] = 1;
    *(code **)(puVar1 + 0xc) = FUN_800df128;
    *(code **)(puVar1 + 0x10c) = FUN_800df248;
    *(float **)(puVar1 + 0x144) = param_2;
    *(undefined4 *)(puVar1 + 0x148) = param_3;
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
    if ((puVar1[0x12] & 3) == 0) {
      zz_00f04b4_(0xe0,param_2,(int)(char)puVar1[0x96]);
    }
  }
  return puVar1;
}



// ==== 800dee00  zz_00dee00_ ====

undefined1 * zz_00dee00_(int param_1,float *param_2,undefined4 param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x10;
    puVar1[0x11] = 1;
    puVar1[0x12] = param_4;
    puVar1[0x13] = 1;
    *(code **)(puVar1 + 0xc) = FUN_800df128;
    *(code **)(puVar1 + 0x10c) = FUN_800df248;
    *(float **)(puVar1 + 0x144) = param_2;
    *(undefined4 *)(puVar1 + 0x148) = param_3;
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
    if ((puVar1[0x12] & 3) == 0) {
      zz_00f04b4_(0xe0,param_2,(int)(char)puVar1[0x96]);
    }
  }
  return puVar1;
}



// ==== 800def38  zz_00def38_ ====

undefined1 * zz_00def38_(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  
  puVar2 = (undefined1 *)0x0;
  iVar1 = zz_00df070_(param_1);
  if (-1 < iVar1) {
    puVar2 = zz_008893c_(2,0x1f,0,1);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      *(code **)(puVar2 + 0xc) = FUN_800df128;
      *(code **)(puVar2 + 0x10c) = FUN_800df248;
      puVar2[0x11] = 2;
      puVar2[0x12] = (char)iVar1;
      puVar2[0x13] = (char)*(undefined4 *)(&DAT_80315f04 + iVar1 * 8);
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
      *(undefined4 *)(puVar2 + 0x54) = 0;
    }
    *(uint *)(param_1 + 0x8c4) = *(uint *)(param_1 + 0x8c4) | 1;
  }
  return puVar2;
}



// ==== 800df070  zz_00df070_ ====

int zz_00df070_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 1000);
  if (cVar1 == '\x05') {
    return *(byte *)(param_1 + 0x3e9) + 1;
  }
  if (cVar1 == '\n') {
    return *(byte *)(param_1 + 0x3e9) + 0x19;
  }
  if (cVar1 == '\v') {
    return *(byte *)(param_1 + 0x3e9) + 0x24;
  }
  if (cVar1 == '\f') {
    return *(byte *)(param_1 + 0x3e9) + 0x2c;
  }
  if (cVar1 == '\r') {
    return *(byte *)(param_1 + 0x3e9) + 0x33;
  }
  if (cVar1 == '\x0e') {
    return *(byte *)(param_1 + 0x3e9) + 0x3b;
  }
  if (cVar1 == '\x0f') {
    return *(byte *)(param_1 + 0x3e9) + 0x41;
  }
  if ((*(char *)(param_1 + 0x660) != '\0') && (cVar1 != '\x06')) {
    return -1;
  }
  return 0;
}



// ==== 800df128  FUN_800df128 ====

void FUN_800df128(int param_1)

{
  (*(code *)(&PTR_FUN_803161a4)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800df164  FUN_800df164 ====

void FUN_800df164(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  (*(code *)(&PTR_FUN_803161b4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800df1b0  FUN_800df1b0 ====

void FUN_800df1b0(int param_1)

{
  (*(code *)(&PTR_FUN_803161c0)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800df200  FUN_800df200 ====

void FUN_800df200(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800df248  FUN_800df248 ====

void FUN_800df248(int param_1)

{
  (*(code *)(&PTR_FUN_803161cc)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800df284  FUN_800df284 ====

void FUN_800df284(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  fVar1 = FLOAT_80438d38;
  puVar4 = *(undefined4 **)(param_9 + 0x144);
  iVar6 = *(int *)(param_9 + 0x8c);
  uVar2 = puVar4[1];
  *(undefined4 *)(param_9 + 0x20) = *puVar4;
  *(undefined4 *)(param_9 + 0x24) = uVar2;
  *(undefined4 *)(param_9 + 0x28) = puVar4[2];
  *(float *)(param_9 + 0x4c) = fVar1;
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x70) = (short)(uVar3 << 8);
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar3 << 8);
  iVar5 = *(short *)(param_9 + 0x1c) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_80316150 + iVar5);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(&DAT_8031614c + iVar5);
  *(undefined4 *)(param_9 + 0x5c) = uVar2;
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(&DAT_80316154 + iVar5);
  gnt4_PSQUATScale_bl((double)*(float *)(iVar6 + 0xb4),(float *)(param_9 + 0x58),
                      (float *)(param_9 + 0x58));
  *(undefined1 *)(param_9 + 0x84) = 0x16;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,0,1);
  zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)0x34,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



