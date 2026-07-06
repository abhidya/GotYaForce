// ==== 801a7e18  zz_01a7e18_ ====

void zz_01a7e18_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a7e2c  zz_01a7e2c_ ====

void zz_01a7e2c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a7e4c  zz_01a7e4c_ ====

void zz_01a7e4c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x11) < '\x0e') {
    zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801a7e7c  zz_01a7e7c_ ====

void zz_01a7e7c_(int param_1)

{
  uint uVar1;
  char cVar2;
  
  if (*(char *)(param_1 + 0x11) != '\r') {
    uVar1 = zz_0181ab4_();
    if ((1 << (int)*(char *)(param_1 + 0x11) & uVar1) != 0) {
      if (*(char *)(param_1 + 0x12) != '\0') {
        cVar2 = '\0';
        if (*(int *)(DAT_80436354 + 0x40) != 2) {
          cVar2 = *(char *)(DAT_80436354 + *(char *)(param_1 + 0x11) + 0x130);
        }
        if (cVar2 == '\x06') {
          *(undefined1 *)(param_1 + 0x82) = 5;
          return;
        }
      }
      *(undefined1 *)(param_1 + 0x82) = 2;
    }
  }
  return;
}



// ==== 801a7f10  zz_01a7f10_ ====

undefined4 zz_01a7f10_(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(char *)(param_1 + 0x11);
  if (iVar1 == *(int *)(DAT_80436354 + 0x118)) {
    return 1;
  }
  if (iVar1 == 0xb) {
    return 1;
  }
  if ((iVar1 == 9) && (*(int *)(DAT_80436354 + 0x118) == 0xd)) {
    return 1;
  }
  return 0;
}



// ==== 801a7f60  zz_01a7f60_ ====

void zz_01a7f60_(int param_1)

{
  float *pfVar1;
  float afStack_28 [7];
  
  pfVar1 = (float *)(*(int *)(DAT_80436354 + 0x118) * 0x14 + -0x7fc85320);
  if (*(char *)(param_1 + 0x11) == '\r') {
    gnt4_PSVECSubtract_bl((float *)&DAT_8037ad94,pfVar1,(float *)(param_1 + 0x164));
    gnt4_PSQUATScale_bl((double)FLOAT_8043b6fc,(float *)(param_1 + 0x164),(float *)(param_1 + 0x164)
                       );
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x164),pfVar1,(float *)(param_1 + 0x164));
    *(undefined4 *)(param_1 + 0x168) = DAT_8037ad98;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x148),(float *)&DAT_8037ad94,afStack_28);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x164),afStack_28,(float *)(param_1 + 0x164));
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x148),pfVar1,(float *)(param_1 + 0x164));
    gnt4_PSQUATScale_bl((double)FLOAT_8043b6fc,(float *)(param_1 + 0x164),(float *)(param_1 + 0x164)
                       );
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x164),pfVar1,(float *)(param_1 + 0x164));
    *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x14c);
  }
  return;
}



// ==== 801a8058  zz_01a8058_ ====

void zz_01a8058_(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &DAT_8037ae50;
  while( true ) {
    if (*piVar1 < 0) break;
    iVar2 = zz_01a7538_(0xb,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01a80f0_;
      *(code **)(iVar2 + 0x10c) = zz_01a84a8_;
      gnt4_PSVECSubtract_bl
                ((float *)(iVar2 + 100),
                 (float *)(*(int *)(DAT_80436354 + *(char *)(iVar2 + 0x11) * 4 + 0x984) + 100),
                 (float *)(iVar2 + 0x158));
    }
    piVar1 = piVar1 + 5;
  }
  return;
}



// ==== 801a80f0  zz_01a80f0_ ====

void zz_01a80f0_(int param_1)

{
  (*(code *)(&PTR_zz_01a812c__8037af54)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a812c  zz_01a812c_ ====

void zz_01a812c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float fVar2;
  float *pfVar3;
  undefined8 uVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  pfVar3 = (float *)0x1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar4 = zz_0089100_(param_9,0,1);
  fVar2 = FLOAT_8043b700;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  uVar4 = zz_01a7688_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar3
                      ,param_12,param_13,param_14,param_15,param_16);
  fVar2 = FLOAT_8043b704;
  *(undefined4 *)(param_9 + 0x174) = 1;
  *(float *)(param_9 + 0x178) = fVar2;
  iVar1 = DAT_80436354;
  if ((*(int *)(DAT_80436354 + 0x128) != 0) &&
     ((int)*(char *)(param_9 + 0x11) != *(int *)(DAT_80436354 + 0x118))) {
    *(undefined1 *)(param_9 + 0x19) = 2;
    *(undefined1 *)(param_9 + 0x1a) = 2;
  }
  zz_01a81f0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar1,pfVar3,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a81f0  zz_01a81f0_ ====

void zz_01a81f0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  (*(code *)(&PTR_zz_01a82b8__8037af64)[*(char *)(param_9 + 0x19)])();
  if (*(char *)(param_9 + 0x82) != '\0') {
    uVar1 = 0;
    if (*(int *)(DAT_80436354 + 0x40) != 2) {
      uVar1 = (uint)*(byte *)(DAT_80436354 + *(char *)(param_9 + 0x11) + 0x130);
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - DOUBLE_8043b708),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,param_12,
                param_13,param_14,param_15,param_16);
    gnt4_PSVECAdd_bl((float *)(*(int *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 4 + 0x984) + 100)
                     ,(float *)(param_9 + 0x158),(float *)(param_9 + 100));
  }
  return;
}



// ==== 801a82b8  zz_01a82b8_ ====

void zz_01a82b8_(int param_1)

{
  if (((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x118)) &&
     ((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x120))) {
    *(undefined1 *)(param_1 + 0x82) = 2;
    if (*(int *)(DAT_80436354 + 0x128) != 1) {
      return;
    }
    if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    else {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x02';
    }
    *(undefined1 *)(param_1 + 0x1a) = 0;
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a833c  zz_01a833c_ ====

void zz_01a833c_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 3) {
    return;
  }
  *(undefined1 *)(param_1 + 0x19) = 0;
  return;
}



// ==== 801a8358  zz_01a8358_ ====

void zz_01a8358_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 0x20;
    *(undefined1 *)(param_1 + 0x82) = 2;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0x20;
        *(undefined2 *)(param_1 + 0x1c) = 0x20;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 1) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
      goto LAB_801a83c8;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (*(short *)(param_1 + 0x1e) <= sVar2) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
LAB_801a83c8:
  *(float *)(param_1 + 0x178) =
       (FLOAT_8043b704 *
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) -
              DOUBLE_8043b708)) /
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
              DOUBLE_8043b708);
  return;
}



// ==== 801a8474  zz_01a8474_ ====

void zz_01a8474_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a8488  zz_01a8488_ ====

void zz_01a8488_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a84a8  zz_01a84a8_ ====

void zz_01a84a8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int extraout_r4;
  
  uVar1 = zz_0181ab4_();
  iVar2 = (int)*(char *)(param_9 + 0x11);
  if ((1 << iVar2 & uVar1) != 0) {
    if (iVar2 == 0xb) {
      param_1 = zz_01a7754_(param_9,0);
      iVar2 = extraout_r4;
    }
    zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801a8508  zz_01a8508_ ====

void zz_01a8508_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037af70; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0xc,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01a8588_;
      *(code **)(iVar2 + 0x10c) = zz_01a883c_;
    }
  }
  return;
}



// ==== 801a8588  zz_01a8588_ ====

void zz_01a8588_(int param_1)

{
  (*(code *)(&PTR_zz_01a85c4__8037b074)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a85c4  zz_01a85c4_ ====

void zz_01a85c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  pfVar2 = (float *)0x1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b710;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar3 = zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar2
                      ,param_12,param_13,param_14,param_15,param_16);
  zz_01a8648_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              pfVar2,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a8648  zz_01a8648_ ====

void zz_01a8648_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  (*(code *)(&PTR_zz_01a86d4__8037b084)[*(char *)(param_9 + 0x19)])();
  if (*(char *)(param_9 + 0x82) != '\0') {
    zz_01a7668_(param_9,0x1e);
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,*(uint *)(param_9 + 0x170) ^ 0x80000000)
                               - DOUBLE_8043b718),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801a86d4  zz_01a86d4_ ====

void zz_01a86d4_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
      return;
    }
    if ((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x120)) {
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
LAB_801a8760:
    *(undefined1 *)(param_1 + 0x1a) = 2;
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0xd8,0xd8,0xd8);
    *(undefined1 *)(param_1 + 0x82) = 2;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      if ((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x118)) {
        if ((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x120)) {
          return;
        }
        goto LAB_801a8760;
      }
    }
    else {
      if ('\x02' < cVar1) {
        return;
      }
      if ((int)*(char *)(param_1 + 0x11) != *(int *)(DAT_80436354 + 0x118)) {
        if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x120)) {
          return;
        }
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined1 *)(param_1 + 0x82) = 0;
        return;
      }
    }
    *(undefined1 *)(param_1 + 0x1a) = 1;
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0xcc,0,0);
    *(undefined1 *)(param_1 + 0x82) = 2;
  }
  return;
}



// ==== 801a8800  zz_01a8800_ ====

void zz_01a8800_(void)

{
  return;
}



// ==== 801a8804  zz_01a8804_ ====

void zz_01a8804_(void)

{
  return;
}



// ==== 801a8808  zz_01a8808_ ====

void zz_01a8808_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a881c  zz_01a881c_ ====

void zz_01a881c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a883c  zz_01a883c_ ====

void zz_01a883c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (*(char *)(param_9 + 0x11) == '\v') {
    param_1 = zz_01a7754_(param_9,0);
    param_10 = extraout_r4;
  }
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a8880  zz_01a8880_ ====

void zz_01a8880_(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 local_28;
  int local_24;
  
  puVar4 = &DAT_8037b090;
  iVar5 = 0;
  local_28 = 8;
  do {
    if (iVar5 != 0xb) {
      local_24 = iVar5;
      iVar3 = zz_01a7538_(0xd,&local_28);
      if (iVar3 != 0) {
        *(code **)(iVar3 + 0xc) = zz_01a8934_;
        *(code **)(iVar3 + 0x10c) = zz_01a8cb4_;
        uVar2 = puVar4[1];
        *(undefined4 *)(iVar3 + 0x158) = *puVar4;
        *(undefined4 *)(iVar3 + 0x15c) = uVar2;
        puVar1 = puVar4 + 2;
        puVar4 = puVar4 + 3;
        *(undefined4 *)(iVar3 + 0x160) = *puVar1;
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 0xe);
  return;
}



// ==== 801a8934  zz_01a8934_ ====

void zz_01a8934_(int param_1)

{
  (*(code *)(&PTR_zz_01a8970__8037b120)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a8970  zz_01a8970_ ====

void zz_01a8970_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b720;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar3 = zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,
                      param_12,param_13,param_14,param_15,param_16);
  zz_0007c54_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,uVar2,param_12,param_13,param_14,param_15,param_16);
  fVar1 = FLOAT_8043b720;
  *(undefined4 *)(param_9 + 0x174) = 2;
  *(float *)(param_9 + 0x178) = fVar1;
  if (*(int *)(DAT_80436354 + 0x128) != 0) {
    if ((int)*(char *)(param_9 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined1 *)(param_9 + 0x1a) = 1;
      *(undefined1 *)(param_9 + 0x82) = 2;
    }
    else {
      *(undefined1 *)(param_9 + 0x19) = 2;
      fVar1 = FLOAT_8043b724;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      *(float *)(param_9 + 0x178) = fVar1;
    }
  }
  zz_01a8a54_(param_9);
  return;
}



// ==== 801a8a54  zz_01a8a54_ ====

void zz_01a8a54_(int param_1)

{
  *(int *)(param_1 + 0x184) = *(int *)(param_1 + 0x184) + -0x40;
  (*(code *)(&PTR_zz_01a8ad0__8037b130)[*(char *)(param_1 + 0x19)])();
  gnt4_PSVECAdd_bl((float *)(*(int *)(DAT_80436354 + *(char *)(param_1 + 0x11) * 4 + 0x984) + 100),
                   (float *)(param_1 + 0x158),(float *)(param_1 + 100));
  return;
}



// ==== 801a8ad0  zz_01a8ad0_ ====

void zz_01a8ad0_(int param_1)

{
  if ((*(uint *)(DAT_80436354 + 0x150) & 1 << (int)*(char *)(param_1 + 0x11)) == 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 2;
  if (*(int *)(DAT_80436354 + 0x128) != 1) {
    return;
  }
  if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x02';
  }
  *(undefined1 *)(param_1 + 0x1a) = 0;
  return;
}



// ==== 801a8b50  zz_01a8b50_ ====

void zz_01a8b50_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 3) {
    return;
  }
  *(undefined1 *)(param_1 + 0x19) = 0;
  return;
}



// ==== 801a8b6c  zz_01a8b6c_ ====

void zz_01a8b6c_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 0x20;
    *(undefined1 *)(param_1 + 0x82) = 2;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0x20;
        *(undefined2 *)(param_1 + 0x1c) = 0x20;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 1) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
      goto LAB_801a8bdc;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (*(short *)(param_1 + 0x1e) <= sVar2) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
LAB_801a8bdc:
  *(float *)(param_1 + 0x178) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) -
              DOUBLE_8043b728) /
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
              DOUBLE_8043b728);
  return;
}



// ==== 801a8c80  zz_01a8c80_ ====

void zz_01a8c80_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a8c94  zz_01a8c94_ ====

void zz_01a8c94_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a8cb4  zz_01a8cb4_ ====

void zz_01a8cb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined8 uVar3;
  
  uVar1 = zz_0181ab4_();
  uVar2 = 1 << (int)*(char *)(param_9 + 0x11);
  if (((uVar2 & uVar1) != 0) && ((*(uint *)(DAT_80436354 + 0x150) & uVar2) != 0)) {
    uVar3 = zz_01a7754_(param_9,(short)*(undefined4 *)(param_9 + 0x184));
    zz_01a77e8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801a8d20  zz_01a8d20_ ====

void zz_01a8d20_(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_28;
  int local_24;
  
  iVar2 = 0;
  local_28 = 0x2f;
  do {
    local_24 = iVar2;
    iVar1 = zz_01a761c_(0x14,&local_28,2);
    if (iVar1 != 0) {
      *(code **)(iVar1 + 0xc) = zz_01a8da0_;
      *(code **)(iVar1 + 0x10c) = FUN_801a920c;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xf);
  return;
}



// ==== 801a8da0  zz_01a8da0_ ====

void zz_01a8da0_(int param_1)

{
  (*(code *)(&PTR_zz_01a8ddc__8037b140)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a8ddc  zz_01a8ddc_ ====

void zz_01a8ddc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b730;
  *(undefined2 *)(param_9 + 0x74) = 0;
  iVar3 = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar4 = param_9;
  do {
    uVar5 = zz_01a7688_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar3,
                        uVar2,param_12,param_13,param_14,param_15,param_16);
    uVar5 = zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0xe0),extraout_r4,uVar2,param_12,param_13,param_14,param_15
                        ,param_16);
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 4;
  } while (iVar3 < 2);
  *(undefined1 *)(param_9 + 0x82) = 3;
  if (*(int *)(DAT_80436354 + 0x128) != 0) {
    if ((int)*(char *)(param_9 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined1 *)(param_9 + 0x1a) = 1;
    }
    else {
      *(undefined1 *)(param_9 + 0x19) = 2;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  zz_01a8ee0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a8ee0  zz_01a8ee0_ ====

/* WARNING: Removing unreachable block (ram,0x801a8ff0) */
/* WARNING: Removing unreachable block (ram,0x801a8ef0) */

void zz_01a8ee0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
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
  double dVar9;
  
  zz_01a7668_(param_9,0x33);
  iVar7 = 0;
  cVar1 = *(char *)(DAT_80436354 + *(char *)(param_9 + 0x11) + 0x574);
  iVar6 = param_9;
  dVar9 = DOUBLE_8043b738;
  do {
    if (cVar1 <= iVar7) break;
    iVar5 = *(int *)(iVar6 + 0xe0);
    pfVar3 = (float *)(*(char *)(param_9 + 0x11) * 0x40 + iVar7);
    fVar2 = FLOAT_8043b734;
    if (*(char *)((int)pfVar3 + DAT_80436354 + 0x584) != '\0') {
      fVar2 = FLOAT_8043b730;
    }
    iVar4 = DAT_80436354;
    uVar8 = zz_00086b8_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x154),iVar5,pfVar3,DAT_80436354,in_r7,in_r8,in_r9,in_r10
                       );
    uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                        extraout_r4,pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    zz_0007d40_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4_00,
                pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    uVar8 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,
                                                         *(uint *)(param_9 + 0x170) ^ 0x80000000) -
                                       dVar9),param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0x154),iVar5,pfVar3,iVar4,in_r7,in_r8,in_r9,
                        in_r10);
    uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                        extraout_r4_01,pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    zz_0007bb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                (undefined4 *)(param_9 + 0x58),pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 4;
  } while (iVar7 < 2);
  (*(code *)(&PTR_zz_01a900c__8037b150)[*(char *)(param_9 + 0x19)])(param_9);
  return;
}



// ==== 801a900c  zz_01a900c_ ====

void zz_01a900c_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 1) {
    return;
  }
  if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x02';
  }
  *(undefined1 *)(param_1 + 0x1a) = 0;
  return;
}



// ==== 801a9058  zz_01a9058_ ====

void zz_01a9058_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 3) {
    return;
  }
  *(undefined1 *)(param_1 + 0x19) = 0;
  return;
}



// ==== 801a9074  FUN_801a9074 ====

/* WARNING: Removing unreachable block (ram,0x801a91b8) */
/* WARNING: Removing unreachable block (ram,0x801a9084) */

void FUN_801a9074(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 0x20;
    *(undefined1 *)(param_1 + 0x82) = 3;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0x20;
        *(undefined2 *)(param_1 + 0x1c) = 0x20;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 1) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
      goto LAB_801a90fc;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (*(short *)(param_1 + 0x1e) <= sVar2) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
LAB_801a90fc:
  iVar3 = 0;
  dVar4 = (double)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000)
                          - DOUBLE_8043b738) /
                  (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                         - DOUBLE_8043b738));
  do {
    zz_0007cac_(dVar4,*(int *)(param_1 + 0xe0));
    iVar3 = iVar3 + 1;
    param_1 = param_1 + 4;
  } while (iVar3 < 2);
  return;
}



// ==== 801a91ec  FUN_801a91ec ====

void FUN_801a91ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a920c  FUN_801a920c ====

/* WARNING: Removing unreachable block (ram,0x801a9320) */
/* WARNING: Removing unreachable block (ram,0x801a921c) */

void FUN_801a920c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  char cVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  float afStack_48 [3];
  float local_3c;
  float local_38;
  
  uVar3 = zz_0181ab4_();
  bVar1 = *(byte *)(param_9 + 0x11);
  pcVar4 = (char *)(uint)bVar1;
  if (((1 << (int)(char)bVar1 & uVar3) != 0) &&
     (((char)bVar1 != 0xd || (FLOAT_8043b740 <= *(float *)(*(int *)(DAT_80436354 + 0x1514) + 0x20)))
     )) {
    zz_00057f0_((float *)(*(int *)(DAT_80436354 + (char)bVar1 * 4 + 0x984) + 100),&local_3c);
    dVar10 = (double)FLOAT_8043b744;
    iVar5 = 0;
    local_3c = (float)((double)local_3c - dVar10);
    dVar8 = (double)local_3c;
    local_38 = (float)((double)local_38 - dVar10);
    dVar11 = (double)FLOAT_8043b74c;
    cVar2 = *(char *)(DAT_80436354 + *(char *)(param_9 + 0x11) + 0x574);
    iVar7 = param_9;
    do {
      if (cVar2 <= iVar5) {
        return;
      }
      iVar6 = *(int *)(iVar7 + 0xe0);
      zz_0007834_(dVar8,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_3c,
                  pcVar4,param_12,param_13,param_14,param_15,param_16);
      uVar9 = gnt4_PSQUATScale_bl((double)FLOAT_8043b748,(float *)(param_9 + 0x58),afStack_48);
      zz_0007ae4_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_48,
                  pcVar4,param_12,param_13,param_14,param_15,param_16);
      dVar8 = (double)zz_00097b4_(iVar6,0x45);
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 4;
      local_3c = (float)((double)local_3c + dVar11);
    } while (iVar5 < 2);
  }
  return;
}



// ==== 801a933c  zz_01a933c_ ====

void zz_01a933c_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037b160; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x1e,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01a93bc_;
      *(code **)(iVar2 + 0x10c) = zz_01a9824_;
    }
  }
  return;
}



// ==== 801a93bc  zz_01a93bc_ ====

void zz_01a93bc_(int param_1)

{
  (*(code *)(&PTR_zz_01a93f8__8037b270)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a93f8  zz_01a93f8_ ====

void zz_01a93f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,uint param_9,undefined4 param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  double dVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar3 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar4 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b750;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar3,param_12
              ,param_13,param_14,param_15,param_16);
  if (*(int *)(DAT_80436354 + 0x7c) == 0) {
    dVar5 = (double)FLOAT_8043b754;
    *(float *)(param_9 + 0x68) = (float)(dVar5 + (double)*(float *)(param_9 + 0x14c));
    uVar2 = extraout_r4;
  }
  else {
    *(undefined1 *)(param_9 + 0x19) = 2;
    *(char *)(param_9 + 0x13) = (char)*(undefined4 *)(DAT_80436354 + 0x7c);
    dVar5 = (double)zz_01a9844_(param_9);
    uVar2 = extraout_r4_00;
  }
  *(undefined4 *)(param_9 + 0x17c) = 0xffffffff;
  zz_01a94c4_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,uVar3,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a94c4  zz_01a94c4_ ====

uint zz_01a94c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,uint param_9,undefined4 param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  byte bVar2;
  double dVar3;
  bool bVar6;
  uint uVar4;
  short sVar5;
  float *pfVar7;
  uint uVar8;
  undefined8 extraout_f1;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x02') {
    uVar4 = (uint)*(char *)(param_9 + 0x13);
    if (uVar4 == *(uint *)(DAT_80436354 + 0x7c)) goto LAB_801a9588;
    *(undefined1 *)(param_9 + 0x19) = 3;
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
  else {
    uVar4 = param_9;
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        uVar4 = DAT_80436354;
        if (*(int *)(DAT_80436354 + 0x7c) == 0) goto LAB_801a9588;
        *(undefined1 *)(param_9 + 0x19) = 1;
        *(undefined1 *)(param_9 + 0x1a) = 0;
      }
      else if (cVar1 < '\0') goto LAB_801a9588;
      bVar6 = zz_01a96a4_(param_9);
      uVar4 = 0;
      if (bVar6) {
        bVar2 = *(byte *)(param_9 + 0x19);
        *(byte *)(param_9 + 0x19) = bVar2 + 1;
        uVar4 = (uint)bVar2;
      }
      goto LAB_801a9588;
    }
    if ('\x03' < cVar1) goto LAB_801a9588;
  }
  bVar6 = zz_01a9754_(param_9);
  uVar4 = (uint)bVar6;
  if (uVar4 != 0) {
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
LAB_801a9588:
  if (*(char *)(param_9 + 0x11) < '\x04') {
    return uVar4;
  }
  if (*(char *)(param_9 + 0x11) != '\x04') {
    uVar4 = zz_01a7668_(param_9,0x3c);
    if (*(char *)(param_9 + 0x82) == '\0') {
      return uVar4;
    }
    uVar8 = *(uint *)(param_9 + 0x170);
    uVar4 = uVar8 - 0x1e;
    param_12 = ((int)uVar8 >> 0x1f) + (uint)(0x1d < uVar8);
    if (*(int *)(param_9 + 0x180) != param_12) {
      *(int *)(param_9 + 0x180) = param_12;
      *(undefined4 *)(param_9 + 0x17c) = 0xffffffff;
      *(uint *)(param_9 + 0x144) =
           (uint)*(byte *)(*(char *)(param_9 + 0x11) + -0x7fbca875) + param_12;
      uVar4 = zz_01a7688_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          param_9,0,&DAT_80435790 + *(char *)(param_9 + 0x11),param_12,param_13,
                          param_14,param_15,param_16);
    }
    if (*(char *)(param_9 + 0x11) != '\t') {
      return uVar4;
    }
  }
  sVar5 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar5;
  if (7 < sVar5) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  dVar3 = DOUBLE_8043b758;
  if (*(int *)(DAT_80436354 + 0x54) == 0) {
    pfVar7 = (float *)0x0;
  }
  else {
    pfVar7 = (float *)((int)*(short *)(param_9 + 0x1c) >> 2);
  }
  uVar4 = DAT_80436354;
  if (*(float **)(param_9 + 0x17c) != pfVar7) {
    *(float **)(param_9 + 0x17c) = pfVar7;
    uVar4 = zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar7 ^ 0x80000000) -
                                       dVar3),param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,param_9,0,pfVar7,param_12,param_13,param_14,param_15,param_16);
  }
  return uVar4;
}



// ==== 801a96a4  zz_01a96a4_ ====

bool zz_01a96a4_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return false;
    }
    if (cVar1 < '\0') {
      return false;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(char *)(param_1 + 0x13) = (char)*(undefined4 *)(DAT_80436354 + 0x7c);
    zz_01a9844_(param_1);
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  dVar3 = zz_01820b0_((double)FLOAT_8043b760,param_1);
  *(float *)(param_1 + 0x68) =
       (float)((double)(FLOAT_8043b754 + *(float *)(param_1 + 0x14c)) + dVar3);
  return iVar2 != 0;
}



// ==== 801a9754  zz_01a9754_ ====

bool zz_01a9754_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return false;
    }
    if (cVar1 < '\0') {
      return false;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b754,param_1);
  *(float *)(param_1 + 0x68) = (float)((double)*(float *)(param_1 + 0x14c) + dVar3);
  return iVar2 != 0;
}



// ==== 801a97f0  zz_01a97f0_ ====

void zz_01a97f0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a9804  zz_01a9804_ ====

void zz_01a9804_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a9824  zz_01a9824_ ====

void zz_01a9824_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a9844  zz_01a9844_ ====

void zz_01a9844_(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(char *)(param_1 + 0x13) + -1;
  if (iVar3 < 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else if (((int)(char)(&DAT_8037b23c)[*(char *)(param_1 + 0x11)] & 1 << iVar3) == 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 4;
    uVar2 = zz_0181c70_();
    *(float *)(param_1 + 100) =
         (float)((double)CONCAT44(0x43300000,
                                  (int)*(char *)(iVar3 + ((int)(-uVar2 | uVar2) >> 0x1f & 2U) +
                                                *(char *)(param_1 + 0x11) * 4 + -0x7fc84db8) ^
                                  0x80000000) - DOUBLE_8043b758);
    iVar3 = zz_0181c70_();
    if (iVar3 == 0) {
      cVar1 = *(char *)(param_1 + 0x11);
      if ((cVar1 == '\t') || ((cVar1 < '\t' && (cVar1 == '\x04')))) {
        *(undefined1 *)(param_1 + 0x82) = 0;
        return;
      }
    }
    *(undefined4 *)(param_1 + 0x180) = 0xffffffff;
  }
  return;
}



// ==== 801a996c  zz_01a996c_ ====

void zz_01a996c_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037b280; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x1f,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01a99ec_;
      *(code **)(iVar2 + 0x10c) = zz_01a9d4c_;
    }
  }
  return;
}



// ==== 801a99ec  zz_01a99ec_ ====

void zz_01a99ec_(int param_1)

{
  (*(code *)(&PTR_zz_01a9a28__8037b2e0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801a9a28  zz_01a9a28_ ====

void zz_01a9a28_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 extraout_f1;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar4 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b768;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar6 = zz_01a7688_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar4,
                      param_12,param_13,param_14,param_15,param_16);
  uVar3 = (undefined4)uVar6;
  uVar5 = extraout_f1;
  iVar2 = zz_01a9d6c_((int)((ulonglong)uVar6 >> 0x20));
  *(int *)(param_9 + 0x180) = iVar2;
  if (*(int *)(param_9 + 400) == 0) {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a9df0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,uVar4,
                param_12,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(param_9 + 0x19) = 2;
    *(undefined1 *)(param_9 + 0x1a) = 2;
  }
  zz_01a9ae0_(param_9);
  return;
}



// ==== 801a9ae0  zz_01a9ae0_ ====

void zz_01a9ae0_(int param_1)

{
  (*(code *)(&PTR_zz_01a9b1c__8037b2f0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801a9b1c  zz_01a9b1c_ ====

void zz_01a9b1c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  bVar1 = *(byte *)(param_9 + 0x1a);
  iVar3 = param_9;
  if (bVar1 != 1) {
    if (('\0' < (char)bVar1) || ((char)bVar1 < '\0')) goto LAB_801a9bb0;
    *(byte *)(param_9 + 0x1a) = bVar1 + 1;
    zz_01a9df0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(uint)bVar1,
                param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0181fbc_(param_9);
  }
  iVar2 = zz_0181fd0_(param_9,0x10);
  if (iVar2 != 0) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined4 *)(DAT_80436354 + 300) = 0;
  }
  dVar4 = zz_01820b0_((double)FLOAT_8043b770,param_9);
  *(float *)(param_9 + 100) =
       (float)((double)(FLOAT_8043b76c + *(float *)(param_9 + 0x148)) + dVar4);
LAB_801a9bb0:
  iVar3 = zz_01a9d6c_(iVar3);
  if (*(int *)(param_9 + 0x180) != iVar3) {
    *(int *)(param_9 + 0x180) = iVar3;
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
  return;
}



// ==== 801a9be4  zz_01a9be4_ ====

void zz_01a9be4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(DAT_80436354 + 300) == 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
  else {
    iVar2 = DAT_80436354;
    iVar1 = zz_01a9d6c_(param_9);
    if (*(int *)(param_9 + 0x180) == iVar1) {
      zz_01a9df0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
    else {
      *(int *)(param_9 + 0x180) = iVar1;
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x1a) = 0;
    }
  }
  return;
}



// ==== 801a9c60  zz_01a9c60_ ====

void zz_01a9c60_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      if (*(int *)(DAT_80436354 + 300) == 1) {
        return;
      }
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b76c,param_1);
  *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
  return;
}



// ==== 801a9d18  zz_01a9d18_ ====

void zz_01a9d18_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801a9d2c  zz_01a9d2c_ ====

void zz_01a9d2c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801a9d4c  zz_01a9d4c_ ====

void zz_01a9d4c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801a9d6c  zz_01a9d6c_ ====

int zz_01a9d6c_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_80436354 + 0x128);
  if (iVar1 != 3) {
    if (2 < iVar1) {
      return param_1;
    }
    if (iVar1 != 0) {
      if (iVar1 < 0) {
        return param_1;
      }
      return (int)(char)(&DAT_8037b2cc)
                        [(char)(&PTR_DAT_80358be4)
                               [(uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40
                                                + *(int *)(DAT_80436354 + 0x9d0) +
                                                *(int *)(DAT_80436354 + 0x9d4) + 0x174) * 7][1]];
    }
  }
  return (int)(char)(&DAT_8037b2bc)[*(int *)(DAT_80436354 + 0x118)];
}



// ==== 801a9df0  zz_01a9df0_ ====

void zz_01a9df0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  
  pfVar2 = DAT_80436354;
  uVar4 = (uint)*(byte *)((int)DAT_80436354 + (int)DAT_80436354[0x46] + 0x140);
  if ((*(char *)(param_9 + 0x11) < '\x02') || (uVar4 != 0)) {
    *(undefined1 *)(param_9 + 0x82) = 4;
    cVar1 = *(char *)(param_9 + 0x11);
    if (cVar1 == '\x03') {
      if (uVar4 < 100) goto LAB_801a9e30;
      uVar3 = 100;
    }
    else {
      if (cVar1 < '\x03') {
        if (cVar1 != '\x01') {
          return;
        }
        zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                     *(uint *)(param_9 + 0x180) ^ 0x80000000) -
                                   DOUBLE_8043b778),param_2,param_3,param_4,param_5,param_6,param_7,
                    param_8,param_9,0,pfVar2,param_12,param_13,param_14,param_15,param_16);
        return;
      }
      if (cVar1 == '\x05') {
        uVar3 = 1;
      }
      else {
        if ('\x04' < cVar1) {
          return;
        }
        if (uVar4 < 10) goto LAB_801a9e30;
        uVar3 = 10;
      }
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uVar4 / uVar3) % 10 ^ 0x80000000) -
                               DOUBLE_8043b778),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,(float *)0x0,uVar4 / uVar3,param_13,param_14,param_15,param_16);
  }
  else {
LAB_801a9e30:
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801a9f18  zz_01a9f18_ ====

void zz_01a9f18_(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  
  for (piVar1 = &DAT_8037b300; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar3 = zz_01a7538_(0x21,piVar1);
    if (iVar3 != 0) {
      *(code **)(iVar3 + 0xc) = zz_01aa034_;
      *(code **)(iVar3 + 0x10c) = FUN_801aa894;
    }
  }
  iVar3 = *(int *)(DAT_80436354 + 0x9d8);
  if (5 < iVar3) {
    iVar3 = 5;
  }
  puVar6 = (undefined4 *)&DAT_8037b364;
  puVar7 = (undefined4 *)&DAT_8037b42c;
  for (iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
    iVar4 = 0;
    do {
      iVar2 = zz_01a7538_(0x21,puVar6);
      if (iVar2 != 0) {
        *(code **)(iVar2 + 0xc) = zz_01aa034_;
        *(code **)(iVar2 + 0x10c) = FUN_801aa894;
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 5;
    } while (iVar4 < 2);
    iVar4 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup(0x21,puVar7,0xc);
    if (iVar4 != 0) {
      *(code **)(iVar4 + 0xc) = zz_01aa034_;
      *(code **)(iVar4 + 0x10c) = FUN_801aa894;
    }
    puVar7 = puVar7 + 5;
  }
  return;
}



// ==== 801aa034  zz_01aa034_ ====

void zz_01aa034_(int param_1)

{
  (*(code *)(&PTR_zz_01aa070__8037b4a8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801aa070  zz_01aa070_ ====

void zz_01aa070_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b780;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar3 = zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,
                      param_12,param_13,param_14,param_15,param_16);
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  if (*(char *)(param_9 + 0x11) == '\x01') {
    *(undefined2 *)(param_9 + 0x74) = 0x8000;
  }
  zz_01aa110_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              uVar2,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801aa110  zz_01aa110_ ====

void zz_01aa110_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  
  pfVar1 = (float *)(int)*(char *)(param_9 + 0x11);
  if ((int)pfVar1 >> 4 == 0) {
    (*(code *)(&PTR_zz_01aa15c__8037b4b8)[(int)pfVar1])();
  }
  else {
    FUN_801aa364(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 pfVar1,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801aa15c  zz_01aa15c_ ====

void zz_01aa15c_(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9d8) < 6) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9cc) != 1) {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  zz_01a7668_(param_1,0x46);
  if (*(int *)(param_1 + 0x170) < 0x32) {
    *(undefined1 *)(param_1 + 0x82) = 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  iVar2 = *(int *)(DAT_80436354 + 0x9cc);
  if (iVar2 == 2) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + -1;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else if ((iVar2 < 2) && (iVar2 == -1)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801aa248  zz_01aa248_ ====

void zz_01aa248_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  int iVar2;
  float *pfVar3;
  
  iVar2 = DAT_80436354;
  bVar1 = *(byte *)(param_9 + 0x19);
  pfVar3 = (float *)(uint)bVar1;
  if (bVar1 != 1) {
    if ('\0' < (char)bVar1) {
      return;
    }
    if ((char)bVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9cc) == -1) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9cc) != 3) {
      return;
    }
    if (*(char *)(*(int *)(DAT_80436354 + 0x9d0) + *(int *)(DAT_80436354 + 0x9d4) +
                  DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 + 0x584) != '\x02') {
      return;
    }
    *(byte *)(param_9 + 0x19) = bVar1 + 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    if (*(char *)(param_9 + 0x11) == '\x03') {
      *(undefined2 *)(param_9 + 0x74) = 0xeee;
    }
    *(undefined1 *)(param_9 + 0x82) = 4;
    param_12 = iVar2;
  }
  zz_01a7668_(param_9,8);
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               *(uint *)(param_9 + 0x170) >> 2 & 1 ^ 0x80000001) -
                             DOUBLE_8043b788),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,pfVar3,param_12,param_13,param_14,param_15,param_16);
  if (*(int *)(DAT_80436354 + 0x9cc) == 4) {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801aa364  FUN_801aa364 ====

/* WARNING: Removing unreachable block (ram,0x801aa838) */
/* WARNING: Removing unreachable block (ram,0x801aa830) */
/* WARNING: Removing unreachable block (ram,0x801aa37c) */
/* WARNING: Removing unreachable block (ram,0x801aa374) */

void FUN_801aa364(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  undefined1 uVar5;
  short sVar4;
  int iVar3;
  undefined4 uVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  iVar8 = *(int *)(DAT_80436354 + 0x9d0);
  uVar2 = (int)*(char *)(param_9 + 0x11) & 0xf;
  iVar7 = ((int)*(char *)(param_9 + 0x11) >> 4) + -1;
  if (uVar2 == 2) {
    param_11 = *(float **)(param_9 + 0x144);
    if (param_11 !=
        (float *)(int)(char)(&PTR_DAT_80358be4)
                            [(uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 +
                                             iVar8 + iVar7 + 0x174) * 7][6]) {
      *(float **)(param_9 + 0x144) =
           (float *)(int)(char)(&PTR_DAT_80358be4)
                               [(uint)*(byte *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40
                                                + iVar8 + iVar7 + 0x174) * 7][6];
      *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
    }
  }
  if (*(int *)(param_9 + 0x180) != *(int *)(DAT_80436354 + 0x9d4)) {
    *(int *)(param_9 + 0x180) = *(int *)(DAT_80436354 + 0x9d4);
    uVar6 = 0x888888ff;
    if (iVar7 == *(int *)(param_9 + 0x180)) {
      uVar6 = 0xffffffff;
    }
    uVar9 = zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        uVar6,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                param_16);
    param_1 = zz_0007cac_((double)FLOAT_8043b790,*(int *)(param_9 + 0xe0));
  }
  switch(*(char *)(param_9 + 0x19)) {
  case '\0':
    if (*(int *)(param_9 + 400) != 0) {
      if (iVar7 == *(int *)(param_9 + 0x180)) {
        *(undefined1 *)(param_9 + 0x19) = 0x16;
        *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8037b490 + uVar2 * 8);
        *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(&DAT_8037b494 + uVar2 * 8);
        *(undefined1 *)(param_9 + 0x82) = 4;
        *(undefined4 *)(DAT_80436354 + 0x9cc) = 3;
      }
      else {
        *(undefined1 *)(param_9 + 0x19) = 0xc;
        *(undefined4 *)(param_9 + 400) = 0;
      }
      break;
    }
    goto LAB_801aa4e4;
  case '\x01':
    goto switchD_801aa470_caseD_1;
  case '\x02':
    iVar3 = *(int *)(DAT_80436354 + 0x9cc);
    if (iVar3 == 2) {
      uVar5 = 0x14;
      if (iVar7 != *(int *)(param_9 + 0x180)) {
        uVar5 = 10;
      }
      *(undefined1 *)(param_9 + 0x19) = uVar5;
      *(undefined2 *)(param_9 + 0x1c) = 0x1e;
    }
    else if ((iVar3 < 2) && (iVar3 == -1)) {
      *(undefined1 *)(param_9 + 0x19) = 0x1e;
      zz_0181fbc_(param_9);
    }
    break;
  case '\n':
    sVar4 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      zz_0181fbc_(param_9);
    }
    break;
  case '\v':
    iVar3 = zz_0181fd0_(param_9,0x10);
    if (iVar3 != 0) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
    dVar10 = zz_01820b0_((double)FLOAT_8043b794,param_9);
    *(float *)(param_9 + 0x68) = (float)((double)*(float *)(param_9 + 0x14c) + dVar10);
    break;
  case '\f':
    if (*(int *)(DAT_80436354 + 0x9cc) != 4) break;
LAB_801aa4e4:
    *(undefined1 *)(param_9 + 0x19) = 1;
    *(undefined1 *)(param_9 + 0x82) = 4;
    zz_0181fbc_(param_9);
switchD_801aa470_caseD_1:
    iVar3 = zz_0181fd0_(param_9,0x10);
    if (iVar3 != 0) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 1;
    }
    dVar10 = zz_01820b0_((double)FLOAT_8043b798,param_9);
    param_2 = (double)FLOAT_8043b794;
    *(float *)(param_9 + 0x68) =
         (float)((double)(float)(param_2 + (double)*(float *)(param_9 + 0x14c)) + dVar10);
    break;
  case '\x14':
    sVar4 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined4 *)(DAT_80436354 + 300) = 1;
      zz_0181fbc_(param_9);
    }
    else {
      uVar6 = 0xffffffff;
      if ((*(ushort *)(param_9 + 0x1c) & 4) != 0) {
        uVar6 = 0x888888ff;
      }
      uVar9 = zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          uVar6,param_11,param_12,param_13,param_14,param_15,param_16);
      zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,
                  param_15,param_16);
      zz_0007cac_((double)FLOAT_8043b790,*(int *)(param_9 + 0xe0));
    }
    break;
  case '\x15':
    iVar3 = zz_0181fd0_(param_9,0x10);
    if (iVar3 != 0) {
      *(undefined1 *)(param_9 + 0x19) = 0x16;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 3;
    }
    dVar11 = (double)*(float *)(&DAT_8037b494 + uVar2 * 8);
    dVar10 = zz_01820b0_((double)(*(float *)(&DAT_8037b490 + uVar2 * 8) -
                                 *(float *)(param_9 + 0x148)),param_9);
    *(float *)(param_9 + 100) = (float)((double)*(float *)(param_9 + 0x148) + dVar10);
    dVar10 = zz_01820b0_((double)(float)(dVar11 - (double)*(float *)(param_9 + 0x14c)),param_9);
    *(float *)(param_9 + 0x68) = (float)((double)*(float *)(param_9 + 0x14c) + dVar10);
    break;
  case '\x16':
    if (*(int *)(DAT_80436354 + 0x9cc) == 4) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      zz_0181fbc_(param_9);
    }
    break;
  case '\x17':
    iVar3 = zz_0181fd0_(param_9,0x10);
    if (iVar3 != 0) {
      *(undefined1 *)(param_9 + 0x19) = 2;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 1;
    }
    dVar12 = (double)*(float *)(&DAT_8037b490 + uVar2 * 8);
    dVar11 = (double)*(float *)(&DAT_8037b494 + uVar2 * 8);
    dVar10 = zz_01820b0_((double)(float)((double)*(float *)(param_9 + 0x148) - dVar12),param_9);
    *(float *)(param_9 + 100) = (float)(dVar12 + dVar10);
    dVar10 = zz_01820b0_((double)(float)((double)*(float *)(param_9 + 0x14c) - dVar11),param_9);
    *(float *)(param_9 + 0x68) = (float)(dVar11 + dVar10);
    break;
  case '\x1e':
    iVar3 = zz_0181fd0_(param_9,0x10);
    if (iVar3 != 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined4 *)(DAT_80436354 + 0x9cc) = 3;
    }
    dVar10 = zz_01820b0_((double)FLOAT_8043b794,param_9);
    *(float *)(param_9 + 0x68) = (float)((double)*(float *)(param_9 + 0x14c) + dVar10);
  }
  if (uVar2 == 1) {
    fVar1 = FLOAT_8043b79c;
    if (*(char *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 0x40 + iVar8 + iVar7 + 0x584) !=
        '\0') {
      fVar1 = FLOAT_8043b780;
    }
    zz_01a76fc_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801aa874  FUN_801aa874 ====

void FUN_801aa874(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801aa894  FUN_801aa894 ====

void FUN_801aa894(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined *param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 == '\x01') {
    param_10 = (undefined *)(*(int *)(DAT_80436354 + 0x9d0) + 5);
    param_11 = DAT_80436354;
    if (*(int *)(DAT_80436354 + 0x9d8) <= (int)param_10) {
      return;
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (param_10 = DAT_80436354, *(int *)(DAT_80436354 + 0x9d0) == 0)) {
    return;
  }
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801aa900  zz_01aa900_ ====

void zz_01aa900_(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = **(int **)(DAT_80436354 + 0x9ec);
  for (piVar2 = &DAT_8037b548; -1 < *piVar2; piVar2 = piVar2 + 5) {
    zz_01aab20_(piVar2);
  }
  iVar3 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup
                    (0x22,(undefined4 *)&DAT_8037b584,0x13);
  if (iVar3 != 0) {
    *(code **)(iVar3 + 0xc) = zz_01aab68_;
    *(code **)(iVar3 + 0x10c) = zz_01ab64c_;
  }
  if (('\x02' < *(char *)(iVar5 + 0xd)) &&
     (iVar3 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup
                        (0x22,(undefined4 *)&DAT_8037b598,0x14), iVar3 != 0)) {
    *(code **)(iVar3 + 0xc) = zz_01aab68_;
    *(code **)(iVar3 + 0x10c) = zz_01ab64c_;
  }
  piVar2 = &DAT_8037b5ac;
  while( true ) {
    if (*piVar2 < 0) break;
    zz_01aab20_(piVar2);
    piVar2 = piVar2 + 5;
  }
  zz_01aab20_((undefined4 *)&DAT_8037b5e8);
  piVar2 = &DAT_8037b5fc;
  if (*(char *)(iVar5 + 0xe) != '\0') {
    piVar2 = &DAT_8037b64c;
  }
  while( true ) {
    if (*piVar2 < 0) break;
    zz_01aab20_(piVar2);
    piVar2 = piVar2 + 5;
  }
  bVar1 = false;
  if ((((*(byte *)(iVar5 + 0x11) & 0x80) != 0) || (((int)*(char *)(iVar5 + 0x12) & 0x80U) != 0)) ||
     ((int)*(char *)(iVar5 + 0x12) == 0)) {
    bVar1 = true;
  }
  piVar2 = &DAT_8037b73c;
  if (bVar1) {
    piVar2 = &DAT_8037b6ec;
  }
  for (; -1 < *piVar2; piVar2 = piVar2 + 5) {
    zz_01aab20_(piVar2);
  }
  uVar4 = zz_00055fc_();
  *(uint *)(DAT_80436354 + 0x9f4) = uVar4 % 0x65;
  uVar4 = zz_00055fc_();
  *(uint *)(DAT_80436354 + 0x9f8) = uVar4 % 0x65;
  uVar4 = zz_00055fc_();
  *(uint *)(DAT_80436354 + 0x9fc) = uVar4 << 0xb;
  uVar4 = zz_00055fc_();
  *(uint *)(DAT_80436354 + 0xa00) = uVar4 << 0xb;
  return;
}



// ==== 801aab20  zz_01aab20_ ====

void zz_01aab20_(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = zz_01a7538_(0x22,param_1);
  if (iVar1 != 0) {
    *(code **)(iVar1 + 0xc) = zz_01aab68_;
    *(code **)(iVar1 + 0x10c) = zz_01ab64c_;
  }
  return;
}



// ==== 801aab68  zz_01aab68_ ====

void zz_01aab68_(int param_1)

{
  (*(code *)(&PTR_zz_01aaba4__8037b7d8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801aaba4  zz_01aaba4_ ====

void zz_01aaba4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  uVar6 = 1;
  uVar5 = 0x1f;
  iVar7 = **(int **)(DAT_80436354 + 0x9ec);
  uVar4 = 1;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,0,1);
  fVar2 = FLOAT_8043b7a0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  switch((int)*(char *)(param_9 + 0x11)) {
  case 0x14:
    if (*(char *)(iVar7 + 0xe) == '\x01') {
      *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_8037b7c8)[*(char *)(iVar7 + 0xf)];
    }
    break;
  case 0x17:
    *(undefined4 *)(param_9 + 0x174) = 1;
    cVar1 = *(char *)(iVar7 + 0xe);
    iVar7 = *(int *)(DAT_80436354 + 0x8c);
    if (cVar1 == '\x02') {
LAB_801aaca4:
      *(float *)(param_9 + 0x178) = FLOAT_8043b7a0;
    }
    else {
      if (cVar1 < '\x02') {
        if ('\0' < cVar1) {
          iVar7 = 0;
        }
        goto LAB_801aaca4;
      }
      if ('\x03' < cVar1) goto LAB_801aaca4;
      *(float *)(param_9 + 0x178) = FLOAT_8043b7a4;
    }
    *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_8037b7c8)[iVar7];
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
    break;
  case 0x1a:
  case 0x1d:
    uVar3 = (*(char *)(param_9 + 0x11) + -0x1a) / 3;
    if ((*(byte *)(iVar7 + uVar3 + 0x11) & 0x80) != 0) {
      uVar3 = uVar3 ^ 1;
    }
    *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_8037b7c8)[*(char *)(iVar7 + uVar3 + 0x11)];
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
  }
  zz_01a7688_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar4,uVar5,
              uVar6,in_r8,in_r9,in_r10);
  zz_01aadb4_(param_9);
  return;
}



// ==== 801aad50  zz_01aadb4_ ====

void zz_01aadb4_(int param_1)

{
  (**(code **)(&DAT_8037b810 + *(char *)(param_1 + 0x11) * 4))();
  if (*(char *)(DAT_80436354 + 1) < '\x06') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801aaec0  zz_01aaec0_ ====

void zz_01aaec0_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x9f0) != 0) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if (*(int *)(DAT_80436354 + 0x9f0) != 2) {
          return;
        }
        *(undefined1 *)(param_1 + 0x1a) = 1;
        zz_0181fbc_(param_1);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_1,0x10);
      if (iVar2 != 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      }
      dVar3 = zz_01820b0_((double)FLOAT_8043b7b0,param_1);
      *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined4 *)(DAT_80436354 + 0x9f0) = 1;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b7b4,param_1);
  *(float *)(param_1 + 100) =
       (float)((double)(FLOAT_8043b7b0 + *(float *)(param_1 + 0x148)) + dVar3);
  return;
}



// ==== 801aafd4  FUN_801aafd4 ====

void FUN_801aafd4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_9 + 0x19);
  if (bVar1 == 1) {
    zz_01aaec0_(param_9);
  }
  else if ((((char)bVar1 < '\x01') && (-1 < (char)bVar1)) && (*(int *)(DAT_80436354 + 0x9f0) != 0))
  {
    *(byte *)(param_9 + 0x19) = bVar1 + 1;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x82) = 4;
    if (*(char *)(param_9 + 0x11) == '\x04') {
      zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,
                  (uint)bVar1,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 801ab054  FUN_801ab054 ====

void FUN_801ab054(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float *pfVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    zz_01aaec0_(param_9);
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(int *)(DAT_80436354 + 0x9f0) != 0)) {
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    dVar3 = DOUBLE_8043b7c0;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    fVar2 = FLOAT_8043b7b8;
    *(undefined1 *)(param_9 + 0x82) = 4;
    pfVar4 = (float *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 4);
    zz_01a76fc_((double)((float)((double)CONCAT44(0x43300000,pfVar4[0x278]) - dVar3) / fVar2),dVar3,
                param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4,DAT_80436354,in_r7,
                in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 801ab100  FUN_801ab100 ====

void FUN_801ab100(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 in_r10;
  uint uVar7;
  
  cVar1 = *(char *)(param_9 + 0x19);
  iVar4 = *(char *)(param_9 + 0x11) + -8;
  iVar2 = iVar4 / 6;
  if (cVar1 == '\x01') {
    zz_01aaec0_(param_9);
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(int *)(DAT_80436354 + 0x9f0) != 0)) {
    iVar4 = -(iVar4 % 6);
    uVar3 = iVar4 + 5;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    uVar6 = 1;
    uVar5 = 0;
    *(undefined1 *)(param_9 + 0x82) = 4;
    if (uVar3 != 0) {
      if ((8 < uVar3) && (uVar7 = iVar4 + 4U >> 3, iVar4 != 3)) {
        do {
          uVar6 = uVar6 * 100000000;
          uVar5 = uVar5 + 8;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
      }
      iVar4 = uVar3 - uVar5;
      if (uVar5 < uVar3) {
        do {
          uVar6 = uVar6 * 10;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    uVar7 = *(uint *)(DAT_80436354 + iVar2 * 4 + 0x9fc);
    if (999999 < uVar7) {
      uVar7 = 999999;
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uVar7 / uVar6) % 10) - DOUBLE_8043b7c0)
                ,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                (float *)(uVar7 / uVar6),uVar3,uVar5,uVar6,iVar2,in_r10);
  }
  return;
}



// ==== 801ab254  zz_01ab254_ ====

void zz_01ab254_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  bVar1 = *(byte *)(param_9 + 0x19);
  iVar3 = *(char *)(param_9 + 0x11) + -0x14;
  iVar2 = iVar3 / 3;
  iVar3 = iVar3 % 3;
  if (bVar1 != 1) {
    if ('\0' < (char)bVar1) {
      return;
    }
    if ((char)bVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9f0) == 0) {
      return;
    }
    *(byte *)(param_9 + 0x19) = bVar1 + 1;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x82) = 4;
    if ((iVar3 != 0) &&
       (*(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8043579c + iVar2 * 2), iVar3 == 2)) {
      zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,
                  (uint)bVar1,iVar2,2,in_r8,in_r9,in_r10);
    }
  }
  zz_01aaec0_(param_9);
  return;
}



// ==== 801ab31c  zz_01ab31c_ ====

void zz_01ab31c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar4 = DAT_80436354;
  cVar1 = *(char *)(param_9 + 0x19);
  iVar5 = **(int **)(DAT_80436354 + 0x9ec);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9f0) == 0) {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x82) = 4;
  }
  uVar6 = zz_01ab420_(param_9);
  if (*(char *)(iVar5 + 0xe) == '\x01') {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(DAT_80436354 + 0x8c);
    if (iVar3 == 0) {
      iVar3 = 0xf;
    }
  }
  *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_8037b7c8)[iVar3];
  if (*(int *)(param_9 + 0x180) != *(int *)(param_9 + 0x144)) {
    *(int *)(param_9 + 0x180) = *(int *)(param_9 + 0x144);
    fVar2 = FLOAT_8043b7a0;
    *(undefined4 *)(param_9 + 0x174) = 1;
    *(float *)(param_9 + 0x178) = fVar2;
    zz_01a7688_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar4,
                param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(iVar5 + 0xe) != '\x03') {
    *(float *)(param_9 + 0x178) = FLOAT_8043b7a0;
  }
  return;
}



// ==== 801ab420  zz_01ab420_ ====

void zz_01ab420_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x9f0) != 0) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(float *)(param_1 + 0x178) = FLOAT_8043b7a4;
        if (*(int *)(DAT_80436354 + 0x9f0) != 2) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        zz_0181fbc_(param_1);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_1,0x10);
      if (iVar2 != 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      }
      dVar3 = zz_01820b0_((double)FLOAT_8043b7b0,param_1);
      dVar4 = (double)FLOAT_8043b7a0;
      *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
      dVar3 = zz_01820b0_(dVar4,param_1);
      *(float *)(param_1 + 0x178) = (float)dVar3;
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined4 *)(DAT_80436354 + 0x9f0) = 1;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b7b4,param_1);
  dVar4 = (double)FLOAT_8043b7a0;
  *(float *)(param_1 + 100) =
       (float)((double)(FLOAT_8043b7b0 + *(float *)(param_1 + 0x148)) + dVar3);
  dVar3 = zz_01820b0_(dVar4,param_1);
  *(float *)(param_1 + 0x178) = (float)((double)FLOAT_8043b7a0 - dVar3);
  return;
}



// ==== 801ab568  zz_01ab568_ ====

void zz_01ab568_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_80436354;
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    zz_01aaec0_(param_9);
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(int *)(DAT_80436354 + 0x9f0) != 0)) {
    iVar3 = (int)*(char *)(**(int **)(DAT_80436354 + 0x9ec) + 0xd);
    if (2 < iVar3) {
      iVar3 = 2;
    }
    *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_80435798)[iVar3];
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar2,
                param_12,param_13,param_14,param_15,param_16);
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x82) = 4;
  }
  return;
}



// ==== 801ab618  zz_01ab618_ ====

void zz_01ab618_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ab62c  zz_01ab62c_ ====

void zz_01ab62c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ab64c  zz_01ab64c_ ====

void zz_01ab64c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ab66c  zz_01ab66c_ ====

void zz_01ab66c_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037b898; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x23,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01ab6ec_;
      *(code **)(iVar2 + 0x10c) = zz_01aba08_;
    }
  }
  return;
}



// ==== 801ab6ec  zz_01ab6ec_ ====

void zz_01ab6ec_(int param_1)

{
  (*(code *)(&PTR_zz_01ab728__8037b8c0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ab728  zz_01ab728_ ====

void zz_01ab728_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043b7c8;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 4;
  zz_01ab7b4_(param_9);
  return;
}



// ==== 801ab7b4  zz_01ab7b4_ ====

void zz_01ab7b4_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
LAB_801ab7fc:
    if (*(short *)(param_1 + 0x1c) == 0x5a) {
      *(undefined4 *)(DAT_80436354 + 0x9f0) = 3;
    }
    if ((*(int *)(DAT_80436354 + 0x9f0) == 0) || (*(int *)(DAT_80436354 + 0x9f0) == 4)) {
      *(undefined2 *)(param_1 + 0x1c) = 1;
    }
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) goto LAB_801ab8ac;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x10;
    *(undefined4 *)(param_1 + 0x174) = 1;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') goto LAB_801ab8ac;
      *(char *)(param_1 + 0x19) = cVar1 + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
      goto LAB_801ab7fc;
    }
    if ('\x02' < cVar1) goto LAB_801ab8ac;
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  *(float *)(param_1 + 0x178) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) -
              DOUBLE_8043b7d0) * FLOAT_8043b7cc;
LAB_801ab8ac:
  zz_01ab8c0_(param_1);
  return;
}



// ==== 801ab8c0  zz_01ab8c0_ ====

void zz_01ab8c0_(int param_1)

{
  char cVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  double dVar6;
  double dVar7;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
      dVar6 = zz_0045238_(*(short *)(param_1 + 0x1e) << 10);
      fVar3 = FLOAT_8043b7c8 - (float)((double)FLOAT_8043b7e4 * -dVar6);
      *(float *)(param_1 + 0x58) = FLOAT_8043b7c8 + (float)((double)FLOAT_8043b7e4 * -dVar6);
      *(float *)(param_1 + 0x5c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1e) = 0;
  }
  uVar2 = (int)*(short *)(param_1 + 0x1e) << 0xe;
  iVar4 = (int)uVar2 / 0x18 + ((int)(uVar2 | (uint)(int)*(short *)(param_1 + 0x1e) >> 0x12) >> 0x1f)
  ;
  dVar7 = zz_0045204_((short)iVar4 - (short)(iVar4 >> 0x1f));
  dVar6 = (double)FLOAT_8043b7e0;
  *(float *)(param_1 + 0x58) = (float)((double)FLOAT_8043b7dc * dVar7 + (double)FLOAT_8043b7d8);
  *(float *)(param_1 + 0x5c) = (float)(dVar6 * dVar7);
  sVar5 = *(short *)(param_1 + 0x1e) + 1;
  *(short *)(param_1 + 0x1e) = sVar5;
  if (0x17 < sVar5) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1e) = 0;
  }
  return;
}



// ==== 801ab9d4  zz_01ab9d4_ ====

void zz_01ab9d4_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ab9e8  zz_01ab9e8_ ====

void zz_01ab9e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801aba08  zz_01aba08_ ====

void zz_01aba08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801aba28  zz_01aba28_ ====

void zz_01aba28_(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  for (piVar1 = &DAT_8037b8d0; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar3 = zz_01a7538_(0x24,piVar1);
    if (iVar3 != 0) {
      *(code **)(iVar3 + 0xc) = zz_01abb00_;
      *(code **)(iVar3 + 0x10c) = zz_01ac224_;
    }
  }
  iVar3 = 0;
  do {
    iVar2 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup(0x24,(undefined4 *)&DAT_8037b95c,1)
    ;
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01abb00_;
      *(code **)(iVar2 + 0x10c) = zz_01ac224_;
      *(char *)(iVar2 + 0x12) = (char)iVar3;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x1e);
  zz_01ab66c_();
  return;
}



// ==== 801abb00  zz_01abb00_ ====

void zz_01abb00_(int param_1)

{
  (*(code *)(&PTR_zz_01abb3c__8037bc40)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801abb3c  zz_01abb3c_ ====

void zz_01abb3c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar3 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar4 = zz_0089100_(param_9,0,1);
  fVar2 = FLOAT_8043b7e8;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  fVar2 = FLOAT_8043b7ec;
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 == '\x03') {
    *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      *(undefined4 *)(param_9 + 0x174) = 1;
      *(float *)(param_9 + 0x178) = fVar2;
      zz_01a76c0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,uVar3,
                  param_12,param_13,param_14,param_15,param_16);
      goto LAB_801abc0c;
    }
  }
  else if ((cVar1 < '\b') && ('\x05' < cVar1)) {
    *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
    goto LAB_801abc0c;
  }
  zz_01a7688_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar3,param_12
              ,param_13,param_14,param_15,param_16);
LAB_801abc0c:
  zz_01abc28_(param_9);
  return;
}



// ==== 801abc28  zz_01abc28_ ====

void zz_01abc28_(int param_1)

{
  (*(code *)(&PTR_zz_01abc8c__8037bc50)[*(char *)(param_1 + 0x11)])();
  if (*(char *)(DAT_80436354 + 1) < '\a') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801abc8c  zz_01abc8c_ ====

void zz_01abc8c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  float *pfVar3;
  
  dVar2 = DOUBLE_8043b7f0;
  if (*(char *)(param_9 + 0x11) == '\x03') {
    pfVar3 = (float *)(*(int *)(DAT_80436354 + 0x8c) + -1);
    if ((int)pfVar3 < 0) {
      pfVar3 = (float *)0xd;
    }
    if (*(float **)(param_9 + 0x180) != pfVar3) {
      *(float **)(param_9 + 0x180) = pfVar3;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar3 ^ 0x80000000) - dVar2),
                  param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar3,param_12,
                  param_13,param_14,param_15,param_16);
    }
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    zz_01abde4_(param_9);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_01abd40_(param_9);
  }
  return;
}



// ==== 801abd40  zz_01abd40_ ====

void zz_01abd40_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x82) = 4;
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b7fc,param_1);
  *(float *)(param_1 + 100) =
       (float)((double)(FLOAT_8043b7f8 + *(float *)(param_1 + 0x148)) + dVar3);
  return;
}



// ==== 801abde4  zz_01abde4_ ====

void zz_01abde4_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9f0) != 0) {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b7f8,param_1);
  *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
  return;
}



// ==== 801abe7c  zz_01abe7c_ ====

void zz_01abe7c_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      zz_01a7668_(param_1,4);
      if ((*(uint *)(param_1 + 0x170) & 2) != 0) {
        *(undefined1 *)(param_1 + 0x82) = 4;
        return;
      }
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0x9f0) != 3) {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    uVar2 = 0xc000;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    if (*(char *)(param_1 + 0x11) == '\x04') {
      uVar2 = 0x4000;
    }
    *(undefined2 *)(param_1 + 0x74) = uVar2;
  }
  if (*(int *)(DAT_80436354 + 0x9f0) == 4) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  zz_01a7668_(param_1,0x46);
  if (*(int *)(param_1 + 0x170) < 0x32) {
    *(undefined1 *)(param_1 + 0x82) = 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  zz_01abde4_(param_1);
  return;
}



// ==== 801abf88  zz_01abf88_ ====

void zz_01abf88_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  *(int *)(param_9 + 0x144) = *(int *)(DAT_80436354 + 0x8c) + 0x6e;
  if (*(int *)(param_9 + 0x180) != *(int *)(param_9 + 0x144)) {
    *(int *)(param_9 + 0x180) = *(int *)(param_9 + 0x144);
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  *(undefined1 *)(param_9 + 0x82) = 4;
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    zz_01abde4_(param_9);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_01abd40_(param_9);
  }
  if (*(int *)(DAT_80436354 + 0x8c) == 0) {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ac030  zz_01ac030_ ====

void zz_01ac030_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  undefined4 *puVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = *(int *)(DAT_80436354 + 0x108);
  if (*(char *)(param_9 + 0x12) < iVar9) {
    zz_01ac244_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(undefined1 *)(param_9 + 0x82) = 4;
  }
  fVar4 = FLOAT_8043b7e8;
  if (iVar9 < 0xc) {
    if (iVar9 != 0) {
      puVar5 = (undefined4 *)(*(int *)(&DAT_8037bc00 + iVar9 * 4) + *(char *)(param_9 + 0x12) * 0xc)
      ;
      *(undefined4 *)(param_9 + 100) = *puVar5;
      *(undefined4 *)(param_9 + 0x68) = puVar5[1];
      uVar2 = puVar5[2];
      *(undefined4 *)(param_9 + 0x5c) = uVar2;
      *(undefined4 *)(param_9 + 0x58) = uVar2;
    }
  }
  else {
    iVar8 = (int)*(char *)(param_9 + 0x12);
    iVar7 = iVar8 / 5 + (iVar8 >> 0x1f);
    uVar6 = iVar8 + (iVar7 - (iVar7 >> 0x1f)) * -5;
    fVar3 = FLOAT_8043b800;
    if ((10 < iVar9) && (fVar3 = FLOAT_8043b808, iVar9 < 0x15)) {
      fVar3 = FLOAT_8043b804;
    }
    fVar3 = fVar3 * (float)((double)CONCAT44(0x43300000,
                                             (iVar7 - (iVar7 >> 0x1f)) * 2 +
                                             ((int)uVar6 >> 0x1f) + (uint)(2 < uVar6) ^ 0x80000000)
                           - DOUBLE_8043b7f0) + FLOAT_8043b810;
    *(float *)(param_9 + 100) = FLOAT_8043b80c + *(float *)(&DAT_8037bc2c + uVar6 * 4);
    *(float *)(param_9 + 0x68) = fVar3;
    *(float *)(param_9 + 0x5c) = fVar4;
    *(float *)(param_9 + 0x58) = fVar4;
  }
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 100);
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    zz_01abde4_(param_9);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_01abd40_(param_9);
  }
  if (iVar9 <= *(char *)(param_9 + 0x12)) {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ac1f0  zz_01ac1f0_ ====

void zz_01ac1f0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ac204  zz_01ac204_ ====

void zz_01ac204_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ac224  zz_01ac224_ ====

void zz_01ac224_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ac244  zz_01ac244_ ====

void zz_01ac244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  uVar1 = (uint)*(short *)(DAT_80436354 + *(char *)(param_9 + 0x12) * 2 + 0xcc);
  if (-1 < (int)uVar1) {
    *(undefined4 *)(param_9 + 0x144) =
         *(undefined4 *)((&PTR_DAT_80350d0c)[(int)uVar1 >> 8] + (uVar1 & 0xff) * 4);
    if (*(int *)(param_9 + 0x180) != *(int *)(param_9 + 0x144)) {
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  ((int)uVar1 >> 8) * 4,uVar1,in_r7,in_r8,in_r9,in_r10);
      *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
    }
  }
  return;
}



// ==== 801ac2cc  zz_01ac2cc_ ====

void zz_01ac2cc_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037bc70; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x28,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01ac3e8_;
      *(code **)(iVar2 + 0x10c) = zz_01ac990_;
    }
  }
  return;
}



// ==== 801ac34c  zz_01ac34c_ ====

void zz_01ac34c_(void)

{
  zz_01ac9b0_();
  zz_01c5824_();
  zz_01acfd0_();
  zz_01c5d78_();
  *(undefined4 *)(DAT_80436354 + 0xa30) = 0;
  *(undefined1 *)(DAT_80436354 + 0xa0d) = 0xff;
  *(undefined1 *)(DAT_80436354 + 0xa0e) = 0xff;
  *(undefined1 *)(DAT_80436354 + 0xa0f) = 0xff;
  *(undefined2 *)(DAT_80436354 + 0xa14) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa16) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa18) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa1a) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa1c) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa1e) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa20) = 0xffff;
  *(undefined2 *)(DAT_80436354 + 0xa22) = 0xffff;
  *(undefined4 *)(DAT_80436354 + 0xa24) = 0xffffffff;
  return;
}



// ==== 801ac3e8  zz_01ac3e8_ ====

void zz_01ac3e8_(int param_1)

{
  (*(code *)(&PTR_zz_01ac424__8037bcc0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ac424  zz_01ac424_ ====

void zz_01ac424_(int param_1)

{
  float fVar1;
  
  if (-1 < *(char *)(DAT_80436354 + 0xa0c)) {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(undefined1 *)(param_1 + 0x84) = 0x1f;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    fVar1 = FLOAT_8043b818;
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(undefined2 *)(param_1 + 0x72) = 0;
    *(undefined2 *)(param_1 + 0x70) = 0;
    *(float *)(param_1 + 0x60) = fVar1;
    *(float *)(param_1 + 0x5c) = fVar1;
    *(float *)(param_1 + 0x58) = fVar1;
    zz_01ac4ac_(param_1);
  }
  return;
}



// ==== 801ac4ac  zz_01ac4ac_ ====

void zz_01ac4ac_(int param_1)

{
  (*(code *)(&PTR_zz_01ac4e8__8037bcd0)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801ac4e8  zz_01ac4e8_ ====

void zz_01ac4e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  zz_01ac540_(param_9);
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + -0x40;
  return;
}



// ==== 801ac540  zz_01ac540_ ====

void zz_01ac540_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x9f0) != 2) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if (*(int *)(DAT_80436354 + 0x9f0) == 2) {
          *(undefined1 *)(param_1 + 0x1a) = 4;
          return;
        }
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined1 *)(param_1 + 0x82) = 4;
        zz_0181fbc_(param_1);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_1,0x10);
      if ((iVar2 != 0) &&
         (*(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01',
         *(char *)(param_1 + 0x11) == '\x01')) {
        *(uint *)(DAT_80436354 + 0xa30) = *(uint *)(DAT_80436354 + 0xa30) & 0xfffffffe;
      }
      dVar3 = zz_01820b0_((double)FLOAT_8043b820,param_1);
      *(float *)(param_1 + 100) =
           (float)((double)(FLOAT_8043b81c + *(float *)(param_1 + 0x148)) + dVar3);
      return;
    }
    if (cVar1 == '\x04') {
      if (*(int *)(DAT_80436354 + 0x9f0) != 0) {
        return;
      }
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b81c,param_1);
  *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
  return;
}



// ==== 801ac6a0  zz_01ac6a0_ ====

void zz_01ac6a0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801ac76c;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(int *)(param_9 + 0x180) = (int)*(char *)(DAT_80436354 + 0xa0c);
    if (*(int *)(param_9 + 0x180) < 0) {
      *(undefined4 *)(param_9 + 0x180) = 0;
    }
    *(undefined4 *)(param_9 + 0x17c) = *(undefined4 *)(param_9 + 0x144);
    *(int *)(param_9 + 0x144) = *(int *)(param_9 + 0x144) + *(int *)(param_9 + 0x180);
    fVar2 = FLOAT_8043b824;
    if (*(char *)(param_9 + 0x11) == '\x02') {
      *(undefined4 *)(param_9 + 0x174) = 1;
      *(float *)(param_9 + 0x178) = fVar2;
    }
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 4;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (0 < sVar3) {
    return;
  }
  param_10 = *(byte *)(param_9 + 0x19) + 1;
  *(char *)(param_9 + 0x19) = (char)param_10;
  *(undefined1 *)(param_9 + 0x1a) = 0;
LAB_801ac76c:
  zz_01ac780_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ac780  zz_01ac780_ ====

void zz_01ac780_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 == '\x02') {
    if ((*(int *)(param_9 + 0x180) == (int)*(char *)(DAT_80436354 + 0xa0c)) &&
       (*(int *)(DAT_80436354 + 0x9f0) != 2)) {
      return;
    }
    *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    zz_0181fbc_(param_9);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if (*(int *)(DAT_80436354 + 0x9f0) == 2) {
          *(undefined1 *)(param_9 + 0x1a) = 4;
          return;
        }
        *(int *)(param_9 + 0x144) = *(int *)(param_9 + 0x17c) + *(int *)(param_9 + 0x180);
        if (*(char *)(param_9 + 0x11) == '\x01') {
          zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                      param_11,param_12,param_13,param_14,param_15,param_16);
        }
        else {
          zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,
                      param_11,param_12,param_13,param_14,param_15,param_16);
        }
        *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
        *(undefined1 *)(param_9 + 0x82) = 4;
        zz_0181fbc_(param_9);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_9,0x10);
      if ((iVar2 != 0) &&
         (*(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01',
         *(char *)(param_9 + 0x11) == '\x01')) {
        *(uint *)(DAT_80436354 + 0xa30) = *(uint *)(DAT_80436354 + 0xa30) & 0xfffffffe;
      }
      dVar3 = zz_01820b0_((double)FLOAT_8043b820,param_9);
      *(float *)(param_9 + 100) =
           (float)((double)(FLOAT_8043b81c + *(float *)(param_9 + 0x148)) + dVar3);
      return;
    }
    if (cVar1 == '\x04') {
      if (*(int *)(DAT_80436354 + 0x9f0) != 0) {
        return;
      }
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x1a) = 0;
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_9,0x10);
  if (iVar2 != 0) {
    if (*(int *)(param_9 + 0x180) == (int)*(char *)(DAT_80436354 + 0xa0c)) {
      *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    }
    else {
      *(int *)(param_9 + 0x180) = (int)*(char *)(DAT_80436354 + 0xa0c);
      *(undefined1 *)(param_9 + 0x1a) = 0;
    }
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b81c,param_9);
  *(float *)(param_9 + 100) = (float)((double)*(float *)(param_9 + 0x148) + dVar3);
  return;
}



// ==== 801ac95c  zz_01ac95c_ ====

void zz_01ac95c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ac970  zz_01ac970_ ====

void zz_01ac970_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ac990  zz_01ac990_ ====

void zz_01ac990_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ac9b0  zz_01ac9b0_ ====

void zz_01ac9b0_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8037bce0; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x29,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01aca30_;
      *(code **)(iVar2 + 0x10c) = zz_01acfb0_;
    }
  }
  return;
}



// ==== 801aca30  zz_01aca30_ ====

void zz_01aca30_(int param_1)

{
  (*(code *)(&PTR_zz_01aca6c__8037bd7c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801aca6c  zz_01aca6c_ ====

void zz_01aca6c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  double dVar4;
  
  if (*(int *)(DAT_80436354 + 0xa04) != 1) {
    if (*(int *)(DAT_80436354 + 0xa28) != 0) {
      return;
    }
    *(undefined1 *)(param_9 + 0x18) = 2;
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar3 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  dVar4 = (double)zz_0089100_(param_9,0,1);
  fVar2 = FLOAT_8043b828;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(char *)(param_9 + 0x12) = (char)*(undefined4 *)(DAT_80436354 + 0x124);
  if (*(char *)(param_9 + 0x11) == '\x01') {
    *(uint *)(param_9 + 0x144) =
         (uint)(byte)s_JKLMNOMNPQRNSNN_8037bd6c[*(int *)(DAT_80436354 + 0x118)];
  }
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 < '\x04') {
    if ('\x01' < cVar1) {
LAB_801acb70:
      if ((*(byte *)(param_9 + 0x11) & 1) == 0) {
        *(float *)(param_9 + 0x44) = FLOAT_8043b828;
        zz_01a7688_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar3,
                    param_12,param_13,param_14,param_15,param_16);
      }
      else {
        *(float *)(param_9 + 0x44) = FLOAT_8043b830;
        zz_01a76c0_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,uVar3
                    ,param_12,param_13,param_14,param_15,param_16);
      }
      *(undefined4 *)(param_9 + 0x174) = 1;
      *(undefined4 *)(param_9 + 0x178) = *(undefined4 *)(param_9 + 0x44);
      goto LAB_801acbc8;
    }
  }
  else if (cVar1 < '\x06') {
    if (s_JKLMNOMNPQRNSNN_8037bd6c[*(int *)(DAT_80436354 + 0x118)] == 'N') {
      dVar4 = (double)*(float *)(param_9 + 0x68);
      *(float *)(param_9 + 0x68) = (float)(dVar4 + (double)FLOAT_8043b82c);
    }
    goto LAB_801acb70;
  }
  zz_01a7688_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar3,param_12
              ,param_13,param_14,param_15,param_16);
LAB_801acbc8:
  zz_01acbe4_(param_9);
  return;
}



// ==== 801acbe4  zz_01acbe4_ ====

void zz_01acbe4_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0xa04) == 1) {
    (*(code *)(&PTR_zz_01acc44__8037bd8c)[*(char *)(param_1 + 0x11)])();
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801acc44  zz_01acc44_ ====

void zz_01acc44_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    if (*(char *)(param_9 + 0x11) == '\0') {
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                   (int)(char)*(byte *)(param_9 + 0x12) ^ 0x80000000
                                                  ) - DOUBLE_8043b838),param_2,param_3,param_4,
                  param_5,param_6,param_7,param_8,param_9,0,(float *)(uint)*(byte *)(param_9 + 0x12)
                  ,param_12,param_13,param_14,param_15,param_16);
    }
  }
  zz_01accdc_(param_9);
  return;
}



// ==== 801accdc  zz_01accdc_ ====

void zz_01accdc_(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0xa28) != 0) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 100);
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined1 *)(param_1 + 0x82) = 4;
        zz_0181fbc_(param_1);
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar2 = zz_0181fd0_(param_1,0x10);
      if (iVar2 != 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      }
      dVar3 = zz_01820b0_((double)FLOAT_8043b844,param_1);
      *(float *)(param_1 + 100) =
           (float)((double)(FLOAT_8043b840 + *(float *)(param_1 + 0x148)) + dVar3);
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  dVar3 = zz_01820b0_((double)FLOAT_8043b840,param_1);
  *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
  return;
}



// ==== 801acde4  zz_01acde4_ ====

void zz_01acde4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  
  if (*(int *)(DAT_80436354 + 0xa28) != 0) {
    zz_01ace88_(param_9);
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    dVar2 = DOUBLE_8043b838;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)(char)*(byte *)(param_9 + 0x12) ^ 0x80000000)
                               - dVar2),param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                param_9,0,(float *)(uint)*(byte *)(param_9 + 0x12),param_12,param_13,param_14,
                param_15,param_16);
  }
  zz_01accdc_(param_9);
  return;
}



// ==== 801ace88  zz_01ace88_ ====

void zz_01ace88_(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  
  fVar2 = FLOAT_8043b850;
  cVar1 = *(char *)(param_1 + 0x1b);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 < '\x04') {
        *(undefined1 *)(param_1 + 0x1b) = 0;
        *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + fVar2;
        *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x44);
      }
      goto LAB_801acf64;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1b) = 1;
    }
    else if (cVar1 < '\0') goto LAB_801acf64;
    if (FLOAT_8043b848 <= *(float *)(param_1 + 100)) goto LAB_801acf64;
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
    *(undefined2 *)(param_1 + 0x1e) = 0x3c;
  }
  sVar3 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar3;
  if (sVar3 < 1) {
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  }
  *(float *)(param_1 + 0x178) =
       (*(float *)(param_1 + 0x44) *
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
              DOUBLE_8043b838)) / FLOAT_8043b84c;
LAB_801acf64:
  *(float *)(param_1 + 100) = *(float *)(param_1 + 100) - FLOAT_8043b854;
  return;
}



// ==== 801acf7c  zz_01acf7c_ ====

void zz_01acf7c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801acf90  zz_01acf90_ ====

void zz_01acf90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801acfb0  zz_01acfb0_ ====

void zz_01acfb0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801acfd0  zz_01acfd0_ ====

void zz_01acfd0_(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = &DAT_8037bda8;
  piVar1 = &DAT_8037be20;
  while( true ) {
    if (*piVar4 < 0) break;
    iVar2 = zz_01a7538_(0x2a,piVar4);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01ad09c_;
      *(code **)(iVar2 + 0x10c) = zz_01ad9c0_;
    }
    piVar4 = piVar4 + 5;
    if (-1 < *piVar1) {
      iVar3 = zz_01a7538_(0x2a,piVar1);
      if (iVar3 != 0) {
        *(code **)(iVar3 + 0xc) = zz_01ad09c_;
        *(code **)(iVar3 + 0x10c) = zz_01ad9c0_;
        *(int *)(iVar3 + 0x54) = iVar2;
      }
      piVar1 = piVar1 + 5;
    }
  }
  return;
}



// ==== 801ad09c  zz_01ad09c_ ====

void zz_01ad09c_(int param_1)

{
  (*(code *)(&PTR_zz_01ad0d8__8037bfc0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ad0d8  zz_01ad0d8_ ====

void zz_01ad0d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043b858;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  zz_01ad158_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ad158  zz_01ad158_ ====

void zz_01ad158_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x11) < '\x05') {
    zz_01ad190_(param_9);
  }
  else {
    zz_01ad820_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801ad190  zz_01ad190_ ====

void zz_01ad190_(int param_1)

{
  (*(code *)(&PTR_zz_01ad1cc__8037bfd0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801ad1cc  zz_01ad1cc_ ====

void zz_01ad1cc_(int param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  int iVar6;
  short sVar7;
  
  if (*(int *)(DAT_80436354 + 0xa28) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    return;
  }
  cVar5 = *(char *)(param_1 + 0x1a);
  if (cVar5 == '\x01') {
    sVar7 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar7;
    if (0 < sVar7) {
      return;
    }
  }
  else {
    if ('\0' < cVar5) {
      return;
    }
    if (cVar5 < '\0') {
      return;
    }
    iVar6 = (int)*(short *)(DAT_80436354 + *(char *)(param_1 + 0x11) * 2 + 0xa14);
    if (*(int *)(param_1 + 0x180) == iVar6) {
      return;
    }
    *(int *)(param_1 + 0x180) = iVar6;
    if (*(char *)(param_1 + 0x11) != '\x04') {
      bVar1 = -1 < *(short *)(DAT_80436354 + 0xa14);
      if (bVar1) {
        *(undefined2 *)(DAT_80436354 + 0xa14) = 0xffff;
      }
      bVar2 = -1 < *(short *)(DAT_80436354 + 0xa16);
      if (bVar2) {
        *(undefined2 *)(DAT_80436354 + 0xa16) = 0xffff;
      }
      bVar3 = -1 < *(short *)(DAT_80436354 + 0xa18);
      if (bVar3) {
        *(undefined2 *)(DAT_80436354 + 0xa18) = 0xffff;
      }
      bVar4 = -1 < *(short *)(DAT_80436354 + 0xa1a);
      if (bVar4) {
        *(undefined2 *)(DAT_80436354 + 0xa1a) = 0xffff;
      }
      if (bVar4 || (bVar3 || (bVar2 || bVar1))) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 10;
        return;
      }
    }
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0;
  return;
}



// ==== 801ad2e8  zz_01ad2e8_ ====

/* WARNING: Removing unreachable block (ram,0x801ad55c) */
/* WARNING: Removing unreachable block (ram,0x801ad2f8) */

void zz_01ad2e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  uint local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x1a) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 8;
    uVar7 = zz_009749c_(0,*(int *)(param_9 + 0x180),&local_34,&local_38);
    *(undefined1 *)(param_9 + 0x13) = (undefined1)local_34;
    if ((int)local_38 < 2) {
      local_38 = 2;
    }
    else if (4 < (int)local_38) {
      local_38 = 4;
    }
    puVar5 = &DAT_804357a8;
    *(char *)(param_9 + 0x12) = (char)local_38 + -2;
    *(uint *)(param_9 + 0x144) = (uint)(byte)(&DAT_804357a8)[*(char *)(param_9 + 0x12)];
    uVar6 = local_38;
    uVar7 = zz_01a7688_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                        &DAT_804357a8,local_38,param_13,param_14,param_15,param_16);
    zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,puVar5,uVar6,param_13,param_14,param_15,
                param_16);
    *(undefined4 *)(param_9 + 0x174) = 2;
    dVar8 = DOUBLE_8043b868;
    param_11 = (float *)&DAT_804357ac;
    local_30 = 0x43300000;
    param_12 = (int)*(char *)(param_9 + 0x11);
    local_28 = 0x43300000;
    local_20 = 0x43300000;
    iVar4 = (param_12 + *(char *)(param_9 + 0x12) * 5) * 8;
    uStack_2c = (int)*(short *)(&DAT_8037be84 + iVar4) ^ 0x80000000;
    *(float *)(param_9 + 100) = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043b868);
    uStack_24 = (int)*(short *)(&DAT_8037be86 + iVar4) ^ 0x80000000;
    *(float *)(param_9 + 0x68) = (float)((double)CONCAT44(0x43300000,uStack_24) - dVar8);
    *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_8037be88 + iVar4);
    *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_8037be8a + iVar4);
    uStack_1c = (int)(char)(&DAT_804357ac)[*(char *)(param_9 + 0x11)] ^ 0x80000000;
    uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_1c) - dVar8),param_2,
                        param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x154),
                        *(int *)(param_9 + 0xe0),&DAT_804357ac,param_12,param_13,param_14,param_15,
                        param_16);
    uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4_01,param_11,param_12,param_13,param_14,param_15
                ,param_16);
    *(undefined1 *)(param_9 + 0x82) = 4;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (*(short *)(param_9 + 0x1e) <= sVar3) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
  fVar2 = FLOAT_8043b85c;
  if (9 < *(char *)(param_9 + 0x13)) {
    uStack_1c = (int)*(char *)(param_9 + 0x13) ^ 0x80000000;
    local_20 = 0x43300000;
    param_2 = (double)FLOAT_8043b860;
    fVar2 = (float)(param_2 *
                   (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043b868));
  }
  dVar9 = (double)fVar2;
  dVar8 = zz_0045204_((short)(((int)*(short *)(param_9 + 0x1c) << 0xe) /
                             (int)*(short *)(param_9 + 0x1e)));
  dVar8 = (double)(float)(dVar9 * dVar8);
  iVar4 = *(int *)(param_9 + 0xe0);
  zz_0008614_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x154),iVar4,param_11,param_12,param_13,param_14,param_15,param_16)
  ;
  zz_0007c30_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,iVar4,param_11,param_12,param_13,param_14,param_15,param_16);
  *(float *)(param_9 + 0x178) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
              DOUBLE_8043b868) /
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1e) ^ 0x80000000) -
              DOUBLE_8043b868);
  return;
}



// ==== 801ad578  zz_01ad578_ ====

void zz_01ad578_(int param_1)

{
  char cVar1;
  short sVar2;
  
  if (*(int *)(DAT_80436354 + 0xa28) == 0) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
    return;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    return;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 1;
      *(undefined2 *)(param_1 + 0x1e) = 2;
      *(undefined4 *)(param_1 + 0x18c) = 0;
    }
    else if (cVar1 < '\0') {
      return;
    }
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if (*(int *)(param_1 + 0x18c) == 0) {
        sVar2 = *(short *)(param_1 + 0x1c) + -1;
        *(short *)(param_1 + 0x1c) = sVar2;
        if (0 < sVar2) {
          return;
        }
        *(int *)(param_1 + 0x188) = *(int *)(param_1 + 0x188) + 1;
        *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(param_1 + 0x1e);
        return;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x188) = 0xffffffff;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 4;
    return;
  }
  if ('\x03' < cVar1) {
    return;
  }
  if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined4 *)(DAT_80436354 + 0xa30) = 0;
  return;
}



// ==== 801ad6ac  zz_01ad6ac_ ====

void zz_01ad6ac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if ((*(int *)(DAT_80436354 + 0xa28) != 0) &&
       ((int)*(short *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 2 + 0xa14) ==
        *(int *)(param_9 + 0x180))) {
      return;
    }
    param_11 = (float *)(*(byte *)(param_9 + 0x1a) + 1);
    *(char *)(param_9 + 0x1a) = (char)param_11;
    *(undefined2 *)(param_9 + 0x1e) = 8;
    *(undefined2 *)(param_9 + 0x1c) = 8;
    *(undefined4 *)(param_9 + 0x188) = 0;
    *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
    if (*(short *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 2 + 0xa14) == -2) {
      *(undefined4 *)(DAT_80436354 + 0xa30) = 0;
      *(undefined2 *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 2 + 0xa14) = 0xffff;
    }
  }
  else {
    dVar4 = zz_0045204_((short)(((int)*(short *)(param_9 + 0x1c) << 0xe) /
                               (int)*(short *)(param_9 + 0x1e)));
    iVar3 = *(int *)(param_9 + 0xe0);
    zz_0008614_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x154),iVar3,param_11,param_12,param_13,param_14,param_15,
                param_16);
    zz_0007c30_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),iVar3,param_11,param_12,param_13,param_14,param_15,param_16
               );
    *(float *)(param_9 + 0x178) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                DOUBLE_8043b868) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1e) ^ 0x80000000) -
                DOUBLE_8043b868);
  }
  return;
}



// ==== 801ad820  zz_01ad820_ ====

void zz_01ad820_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  double dVar5;
  undefined4 extraout_r4;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x54);
  cVar1 = *(char *)(param_9 + 0x11);
  if ((iVar6 == 0) || ('\x01' < *(char *)(iVar6 + 0x18))) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    cVar2 = *(char *)(param_9 + 0x19);
    if (cVar2 != '\x01') {
      if ('\0' < cVar2) {
        return;
      }
      if (cVar2 < '\0') {
        return;
      }
      *(char *)(param_9 + 0x19) = cVar2 + '\x01';
      uVar7 = zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                          param_11,param_12,param_13,param_14,param_15,param_16);
      zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                  param_16);
      *(undefined4 *)(param_9 + 0x174) = 2;
      bVar3 = *(byte *)(cVar1 + -0x7fbca859);
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(int)(char)bVar3 ^ 0x80000000) -
                                 DOUBLE_8043b868),param_2,param_3,param_4,param_5,param_6,param_7,
                  param_8,param_9,0,(float *)(uint)bVar3,param_12,param_13,param_14,param_15,
                  param_16);
    }
    dVar5 = DOUBLE_8043b868;
    *(char *)(param_9 + 0x12) = cVar1 + -5 + *(char *)(iVar6 + 0x12) * '\x05';
    iVar4 = *(char *)(param_9 + 0x12) * 2;
    *(float *)(param_9 + 100) =
         (float)((double)CONCAT44(0x43300000,(int)(char)(&DAT_8037befc)[iVar4] ^ 0x80000000) - dVar5
                );
    *(float *)(param_9 + 0x68) =
         (float)((double)CONCAT44(0x43300000,(int)(char)(&DAT_8037befd)[iVar4] ^ 0x80000000) - dVar5
                );
    *(undefined4 *)(param_9 + 0x178) = *(undefined4 *)(iVar6 + 0x178);
    *(undefined4 *)(param_9 + 0x188) = *(undefined4 *)(iVar6 + 0x188);
    *(undefined1 *)(param_9 + 0x82) = *(undefined1 *)(iVar6 + 0x82);
  }
  return;
}



// ==== 801ad98c  zz_01ad98c_ ====

void zz_01ad98c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ad9a0  zz_01ad9a0_ ====

void zz_01ad9a0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ad9c0  zz_01ad9c0_ ====

void zz_01ad9c0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x11) < '\x05') {
    zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    zz_01ada24_(param_9);
  }
  else if (*(int *)(DAT_80436354 + 0x38) != 0) {
    zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,DAT_80436354
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_01adb74_(param_9);
  }
  return;
}



