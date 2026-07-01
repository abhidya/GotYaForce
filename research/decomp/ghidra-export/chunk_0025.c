// ==== 800e7ddc  FUN_800e7ddc ====

void FUN_800e7ddc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  uVar4 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80433bc8 + *(char *)(param_9 + 0x11) * 2),param_9 + 0x144
                      ,uVar4,in_r8,in_r9,in_r10);
  iVar3 = param_9 + 0x144;
  iVar2 = (int)*(short *)(&DAT_80433bc8 + *(char *)(param_9 + 0x11) * 2);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,uVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,uVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438f20,*(int *)(param_9 + 0xe4));
  fVar1 = FLOAT_80438f24;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined1 *)(param_9 + 0x14c) = 0;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  zz_00e7ee0_(param_9);
  return;
}



// ==== 800e7ee0  zz_00e7ee0_ ====

void zz_00e7ee0_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar2 = (int)(short)(*(short *)(iVar3 + 0x79e) - *(short *)(iVar3 + 0x784));
  if ((*(char *)(param_1 + 0x13) < iVar2) && (*(char *)(iVar3 + 0x15c) != '\x01')) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  if ((*(char *)(iVar3 + 0x6e8) == '\0') && (*(char *)(iVar3 + 0x6e9) == '\0')) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x14c) = 0;
  }
  if (iVar2 != *(char *)(param_1 + 0x13)) {
    zz_00e81a8_(param_1);
    goto LAB_800e8054;
  }
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
LAB_800e7ffc:
    *(undefined1 *)(param_1 + 0x84) = 0xc0;
    *(undefined1 *)(param_1 + 0x89) = uRam80433bcd;
    if ((*(char *)(iVar3 + 0x6e8) != '\x02') || (*(char *)(iVar3 + 0x6e9) != '\x01'))
    goto LAB_800e8054;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if ((*(char *)(iVar3 + 0x6e8) != '\x03') || (*(char *)(iVar3 + 0x6e9) != '\x01')) {
          zz_00e81a8_(param_1);
          goto LAB_800e8054;
        }
        *(undefined1 *)(param_1 + 0x14c) = 1;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
      else if (cVar1 < '\0') goto LAB_800e8054;
      if ((*(char *)(iVar3 + 0x6e8) != '\x01') || (*(char *)(iVar3 + 0x6e9) != '\x01')) {
        zz_00e81a8_(param_1);
        goto LAB_800e8054;
      }
      *(undefined1 *)(param_1 + 0x14c) = 0;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      goto LAB_800e7ffc;
    }
    if ('\x03' < cVar1) goto LAB_800e8054;
  }
  *(undefined1 *)(param_1 + 0x84) = 0xc0;
  *(undefined1 *)(param_1 + 0x89) = uRam80433bce;
LAB_800e8054:
  *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) | 0x10;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar3 + 0x154);
  iVar2 = zz_0006f98_(iVar3);
  if (*(char *)(param_1 + 0x14c) == '\x01') {
    *(char *)(param_1 + 0x144) = *(char *)(param_1 + 0x144) + '(';
    *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + '(';
    *(char *)(param_1 + 0x146) = *(char *)(param_1 + 0x146) + '(';
    *(undefined1 *)(param_1 + 0x148) = 0xff;
    *(undefined1 *)(param_1 + 0x149) = 0xff;
    *(undefined1 *)(param_1 + 0x14a) = 0xff;
    *(undefined1 *)(param_1 + 0x14b) = 0xff;
  }
  else {
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(iVar2 + 0xc28);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(iVar2 + 0xc2c);
  }
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  return;
}



// ==== 800e810c  FUN_800e810c ====

void FUN_800e810c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e812c  FUN_800e812c ====

void FUN_800e812c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800e81a8  zz_00e81a8_ ====

void zz_00e81a8_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x84) = 0x4b;
  *(undefined1 *)(param_1 + 0x89) = DAT_80433bcc;
  *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(&DAT_80318a40 + *(char *)(param_1 + 0x13) * 4);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_80318a42 + *(char *)(param_1 + 0x13) * 4);
  iVar2 = *(char *)(param_1 + 0x13) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_803189e4 + iVar2);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803189e0 + iVar2);
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803189e8 + iVar2);
  return;
}



// ==== 800e8220  FUN_800e8220 ====

bool FUN_800e8220(int param_1)

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
      *(code **)(puVar1 + 0xc) = FUN_800e8338;
      *(code **)(puVar1 + 0x10c) = FUN_800e855c;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800e8338  FUN_800e8338 ====

void FUN_800e8338(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80318aa0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e838c  FUN_800e838c ====

void FUN_800e838c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438f28;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80318a78 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80318a74 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80318a7c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80318a80 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80318a84 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80318a72 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80318a70 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80318a70 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438f2c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00e84b8_(param_9);
  return;
}



// ==== 800e84b8  zz_00e84b8_ ====

void zz_00e84b8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438f30;
  fVar1 = FLOAT_80438f28;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x14e) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_80438f30;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_80438f28) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80438f30;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_80438f28;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800e853c  FUN_800e853c ====

void FUN_800e853c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e855c  FUN_800e855c ====

void FUN_800e855c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x14e) == '\0') {
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



// ==== 800e85f4  FUN_800e85f4 ====

bool FUN_800e85f4(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x46;
    *(code **)(puVar1 + 0xc) = FUN_800e870c;
    *(code **)(puVar1 + 0x10c) = FUN_800e8bec;
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



// ==== 800e870c  FUN_800e870c ====

void FUN_800e870c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80318afc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e87a4  FUN_800e87a4 ====

void FUN_800e87a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  puVar7 = &DAT_80318ae0;
  puVar5 = &DAT_80318ab0;
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
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fce754c),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_80318ab2 + iVar2) * 0x30 + 0x8fc);
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80318af0 + iVar3),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438f38,&local_28,&local_28);
  uVar9 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80318af0 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80318ae2 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80318ae4 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80318ae6 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_80318af4 + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar2 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x600),
              *(int *)(param_9 + 0xe0),1,iVar1,iVar4,puVar5,iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80318ae0 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x4d);
  }
  return;
}



// ==== 800e89d8  FUN_800e89d8 ====

void FUN_800e89d8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083334_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00e8b90_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00e8b90_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_80318af8 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_80318aec + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_80318ae8 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_80318ae4 + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_00e8b90_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),5);
            }
          }
          else {
            zz_00e8b90_(param_1);
          }
        }
      }
    }
    else {
      zz_00e8b90_(param_1);
    }
  }
  else {
    zz_00e8b90_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),5);
  }
  return;
}



// ==== 800e8b90  zz_00e8b90_ ====

void zz_00e8b90_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 800e8bc0  FUN_800e8bc0 ====

void FUN_800e8bc0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800e8bcc  FUN_800e8bcc ====

void FUN_800e8bcc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e8bec  FUN_800e8bec ====

void FUN_800e8bec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800e8c48  zz_00e8c48_ ====

void zz_00e8c48_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0xa03) || (*(short *)(param_1 + 1000) == 0xa06)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800e8d58;
    *(code **)(puVar1 + 0x10c) = FUN_800e8f0c;
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



// ==== 800e8d58  FUN_800e8d58 ====

void FUN_800e8d58(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80318b40)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e8dac  FUN_800e8dac ====

void FUN_800e8dac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438f40;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80318b12 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80318b18 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80318b14 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80318b1c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80318b20 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80318b24 + iVar3);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80318b10 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80318b10 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438f44,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00e8ed8_();
  return;
}



// ==== 800e8ed8  zz_00e8ed8_ ====

void zz_00e8ed8_(void)

{
  return;
}



// ==== 800e8eec  FUN_800e8eec ====

void FUN_800e8eec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e8f0c  FUN_800e8f0c ====

void FUN_800e8f0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 800e8f84  FUN_800e8f84 ====

undefined4
FUN_800e8f84(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int *param_9
            ,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if ((&DAT_803b2980)[*param_9] != 0) {
    zz_026eea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (&DAT_803b2980)[*param_9],param_10,param_11,param_12,param_13,param_14,param_15,
                param_16);
  }
  DAT_804343fc = param_9[1];
  DAT_804343f8 = param_9[2];
  return 1;
}



// ==== 800e8fe0  FUN_800e8fe0 ====

undefined4
FUN_800e8fe0(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int *param_9
            ,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = *param_9;
  iVar1 = iVar2 * 0x44;
  if ((-1 < DAT_804343f8) && (-1 < DAT_804343fc)) {
    if ((&DAT_803b2980)[iVar2] != 0) {
      uVar3 = zz_026e4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (&DAT_803b2980)[iVar2],0,iVar2,param_12,param_13,param_14,param_15,
                          param_16);
      zz_026f9b8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (&DAT_803b2980)[*param_9],DAT_804343fc,DAT_804343f8,param_12,param_13,param_14,
                  param_15,param_16);
      (&DAT_803cd218)[iVar1] = 1;
      (&DAT_803cd21a)[iVar1] = 0;
      *(short *)(&DAT_803cd21c + iVar1) = (short)DAT_804343f8;
      *(undefined2 *)(&DAT_803cd21e + iVar1) = DAT_804343fc._2_2_;
    }
    DAT_804343fc = -1;
    DAT_804343f8 = -1;
  }
  return 1;
}



// ==== 800e90ac  FUN_800e90ac ====

undefined4
FUN_800e90ac(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int *param_9
            ,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *param_9;
  iVar3 = iVar2 * 0x44;
  if ((&DAT_803b2980)[iVar2] != 0) {
    zz_026eea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (&DAT_803b2980)[iVar2],&DAT_803d0000,iVar3,param_12,param_13,param_14,param_15,
                param_16);
  }
  fVar1 = FLOAT_80438f48;
  (&DAT_803cd218)[iVar3] = 0;
  (&DAT_803cd233)[iVar3] = 0;
  (&DAT_803cd230)[iVar3] = 0;
  (&DAT_803cd258)[iVar3] = 0;
  (&DAT_803cd21a)[iVar3] = 0;
  (&DAT_803cd234)[iVar2 * 0x11] = fVar1;
  (&DAT_803cd23b)[iVar3] = 0;
  (&DAT_803cd250)[iVar2 * 0x11] = 0;
  (&DAT_803cd231)[iVar3] = 0;
  (&DAT_803cd232)[iVar3] = 0;
  (&DAT_803cd219)[iVar3] = 0;
  return 1;
}



// ==== 800e9138  FUN_800e9138 ====

undefined4
FUN_800e9138(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int *param_9
            )

{
  int iVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  iVar1 = param_9[2];
  iVar2 = *param_9 * 0x44;
  (&DAT_803cd218 + iVar2)[param_9[1] + 0x19] = (char)iVar1;
  (&DAT_803cd219)[iVar2] = (&DAT_803cd231)[iVar2] + (&DAT_803cd232)[iVar2];
  if (((param_9[2] != 0) || ((&DAT_803cd219)[iVar2] == '\0')) && ((&DAT_803b2980)[*param_9] != 0)) {
    zz_026e4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (&DAT_803b2980)[*param_9],param_9[2],iVar1,&DAT_803cd218 + iVar2,in_r7,in_r8,in_r9,
                in_r10);
  }
  return 1;
}



// ==== 800e91d4  zz_00e91d4_ ====

void zz_00e91d4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte in_cr1;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  char local_28 [4];
  undefined1 *local_24;
  int *local_20;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  if (DAT_804361c4 != 0) {
    local_24 = &stack0x00000008;
    local_20 = &local_88;
    iVar5 = *(int *)(&DAT_80319dec + param_9 * 4);
    local_28[0] = '\x01';
    local_28[1] = '\0';
    local_28[2] = '\0';
    local_28[3] = '\0';
    iVar1 = iVar5 + -1;
    iVar4 = DAT_80436338;
    if (1 < iVar5) {
      do {
        iVar4 = iVar4 + 1;
        iVar3 = iVar4 >> 0x1f;
        if ((iVar3 * 0x40 | (uint)(iVar4 * 0x4000000 + iVar3) >> 0x1a) - iVar3 == DAT_8043633c) {
          return;
        }
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    *(int *)(&DAT_803cd118 + DAT_80436338 * 4) = param_9;
    local_88 = param_9;
    local_84 = param_10;
    local_80 = param_11;
    local_7c = param_12;
    local_78 = param_13;
    local_74 = param_14;
    local_70 = param_15;
    local_6c = param_16;
    for (iVar4 = 1; iVar4 < iVar5; iVar4 = iVar4 + 1) {
      iVar3 = DAT_80436338 + iVar4;
      iVar1 = iVar3 >> 0x1f;
      piVar2 = __va_arg(local_28,1);
      *(int *)(&DAT_803cd118 +
              ((iVar1 * 0x40 | (uint)(iVar3 * 0x4000000 + iVar1) >> 0x1a) - iVar1) * 4) = *piVar2;
    }
    iVar4 = DAT_80436338 + iVar5 >> 0x1f;
    DAT_80436338 = (iVar4 * 0x40 | (uint)((DAT_80436338 + iVar5) * 0x4000000 + iVar4) >> 0x1a) -
                   iVar4;
  }
  return;
}



// ==== 800e9340  zz_00e9340_ ====

void zz_00e9340_(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined4 local_38 [11];
  
  if (DAT_80436338 != DAT_8043633c) {
    iVar8 = 1;
    iVar3 = *(int *)(&DAT_803cd118 + DAT_8043633c * 4);
    iVar9 = *(int *)(&DAT_80319dec + iVar3 * 4);
    if (1 < iVar9) {
      if (8 < iVar9 + -1) {
        iVar5 = DAT_8043633c + 1;
        uVar10 = iVar9 - 2U >> 3;
        puVar6 = local_38 + 1;
        if (1 < iVar9 + -8) {
          do {
            iVar7 = iVar5 * 0x4000000;
            iVar1 = iVar5 >> 0x1f;
            iVar5 = iVar5 + 8;
            iVar4 = iVar8 + DAT_8043633c;
            iVar8 = iVar8 + 8;
            iVar2 = iVar4 + 1 >> 0x1f;
            puVar6[-1] = *(undefined4 *)
                          (&DAT_803cd118 +
                          ((iVar1 * 0x40 | (uint)(iVar7 + iVar1) >> 0x1a) - iVar1) * 4);
            iVar7 = iVar4 + 2 >> 0x1f;
            *puVar6 = *(undefined4 *)
                       (&DAT_803cd118 +
                       ((iVar2 * 0x40 | (uint)((iVar4 + 1) * 0x4000000 + iVar2) >> 0x1a) - iVar2) *
                       4);
            iVar1 = iVar4 + 3 >> 0x1f;
            iVar2 = iVar4 + 4 >> 0x1f;
            puVar6[1] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar7 * 0x40 | (uint)((iVar4 + 2) * 0x4000000 + iVar7) >> 0x1a) - iVar7)
                         * 4);
            puVar6[2] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar1 * 0x40 | (uint)((iVar4 + 3) * 0x4000000 + iVar1) >> 0x1a) - iVar1)
                         * 4);
            iVar7 = iVar4 + 5 >> 0x1f;
            puVar6[3] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar2 * 0x40 | (uint)((iVar4 + 4) * 0x4000000 + iVar2) >> 0x1a) - iVar2)
                         * 4);
            iVar1 = iVar4 + 6 >> 0x1f;
            iVar2 = iVar4 + 7 >> 0x1f;
            puVar6[4] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar7 * 0x40 | (uint)((iVar4 + 5) * 0x4000000 + iVar7) >> 0x1a) - iVar7)
                         * 4);
            puVar6[5] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar1 * 0x40 | (uint)((iVar4 + 6) * 0x4000000 + iVar1) >> 0x1a) - iVar1)
                         * 4);
            puVar6[6] = *(undefined4 *)
                         (&DAT_803cd118 +
                         ((iVar2 * 0x40 | (uint)((iVar4 + 7) * 0x4000000 + iVar2) >> 0x1a) - iVar2)
                         * 4);
            puVar6 = puVar6 + 8;
            uVar10 = uVar10 - 1;
          } while (uVar10 != 0);
        }
      }
      iVar5 = iVar9 - iVar8;
      iVar7 = DAT_8043633c + iVar8;
      puVar6 = local_38 + iVar8;
      if (iVar8 < iVar9) {
        do {
          iVar8 = iVar7 * 0x4000000;
          iVar1 = iVar7 >> 0x1f;
          iVar7 = iVar7 + 1;
          puVar6[-1] = *(undefined4 *)
                        (&DAT_803cd118 +
                        ((iVar1 * 0x40 | (uint)(iVar8 + iVar1) >> 0x1a) - iVar1) * 4);
          puVar6 = puVar6 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
      }
    }
    iVar3 = (*(code *)(&PTR_FUN_8031a0f4)[iVar3])(local_38);
    if (iVar3 != 0) {
      iVar3 = DAT_8043633c + iVar9 >> 0x1f;
      DAT_8043633c = (iVar3 * 0x40 | (uint)((DAT_8043633c + iVar9) * 0x4000000 + iVar3) >> 0x1a) -
                     iVar3;
    }
  }
  return;
}



// ==== 800e95a4  zz_00e95a4_ ====

void zz_00e95a4_(double param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (DAT_804361c4 != 0) {
    if ((double)(float)(&DAT_803cd228)[param_9 * 0x11] < param_1) {
      param_1 = (double)(float)(&DAT_803cd228)[param_9 * 0x11];
    }
    if (param_1 < (double)(float)(&DAT_803cd22c)[param_9 * 0x11]) {
      param_1 = (double)(float)(&DAT_803cd22c)[param_9 * 0x11];
    }
    (&DAT_803cd224)[param_9 * 0x11] = (float)param_1;
    if ((&DAT_803b2980)[param_9] != 0) {
      iVar1 = *(int *)(&DAT_80319dfc + ((int)param_1 & 0x7fU) * 4) / 10 +
              (*(int *)(&DAT_80319dfc + ((int)param_1 & 0x7fU) * 4) >> 0x1f);
      zz_026e77c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (&DAT_803b2980)[param_9],iVar1 - (iVar1 >> 0x1f),&DAT_80319dfc,param_12,param_13,
                  param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 800e9654  FUN_800e9654 ====

/* WARNING: Removing unreachable block (ram,0x800e9764) */
/* WARNING: Removing unreachable block (ram,0x800e975c) */
/* WARNING: Removing unreachable block (ram,0x800e9754) */
/* WARNING: Removing unreachable block (ram,0x800e9674) */
/* WARNING: Removing unreachable block (ram,0x800e966c) */
/* WARNING: Removing unreachable block (ram,0x800e9664) */

void FUN_800e9654(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,int param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char *pcVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar6 = (double)FLOAT_80438f48;
  pcVar1 = &DAT_803cd218;
  iVar2 = 0;
  do {
    dVar5 = (double)*(float *)(pcVar1 + 0x1c);
    if ((dVar6 != dVar5) && (*pcVar1 != '\0')) {
      dVar4 = (double)(float)((double)*(float *)(pcVar1 + 0xc) + dVar5);
      if (dVar4 < (double)*(float *)(pcVar1 + 0x10)) {
        dVar3 = (double)*(float *)(pcVar1 + 0x14);
        if (dVar4 <= dVar3) {
          if (pcVar1[0x23] == '\0') {
            param_11 = *(int *)(pcVar1 + 0x38);
            if (param_11 == 0) {
              *(float *)(pcVar1 + 0x1c) = (float)dVar6;
              dVar4 = dVar3;
            }
            else {
              zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                          (int)*(short *)(pcVar1 + 6),param_11,param_12,param_13,param_14,param_15,
                          param_16);
              *(float *)(pcVar1 + 0x1c) = (float)-dVar5;
              param_10 = extraout_r4_00;
              dVar4 = dVar3;
            }
          }
          else {
            pcVar1[0x23] = '\0';
            dVar5 = dVar6;
            zz_00e9ac0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
            *(float *)(pcVar1 + 0x1c) = FLOAT_80438f48;
            param_10 = extraout_r4;
            dVar4 = dVar6;
            dVar6 = dVar5;
          }
        }
      }
      else {
        *(float *)(pcVar1 + 0x1c) = (float)dVar6;
        dVar4 = (double)*(float *)(pcVar1 + 0x10);
      }
      param_1 = zz_00e95a4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                            param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      param_10 = extraout_r4_01;
    }
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 0x44;
  } while (iVar2 < 3);
  return;
}



// ==== 800e9784  zz_00e9784_ ====

void zz_00e9784_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  undefined2 *puVar5;
  int in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  int *piVar8;
  char *pcVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  
  iVar1 = gnt4_OSGetTick_bl();
  puVar5 = &DAT_803d0000;
  piVar3 = (int *)0x803b0000;
  pcVar9 = &DAT_803cd218;
  piVar8 = &DAT_803b2980;
  iVar7 = 0;
  uVar10 = extraout_f1;
  do {
    iVar6 = *(int *)(pcVar9 + 0x30);
    iVar2 = zz_026ee64_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar8,
                        piVar3,puVar5,in_r6,in_r7,in_r8,in_r9,in_r10);
    *(int *)(pcVar9 + 0x30) = iVar2;
    piVar3 = *(int **)(pcVar9 + 0x34);
    if ((iVar6 != iVar2) && (iVar2 == 3)) {
      *(int *)(pcVar9 + 0x24) = iVar1;
      *(undefined2 *)(pcVar9 + 8) = *(undefined2 *)(pcVar9 + 10);
      if (piVar3 == (int *)0x0) {
        pcVar9[0x20] = -1;
      }
      else {
        pcVar9[0x20] = (char)piVar3[1];
      }
    }
    puVar5 = (undefined2 *)(int)*(short *)(pcVar9 + 8);
    if (puVar5 == (undefined2 *)(int)*(short *)(pcVar9 + 10)) {
      if (iVar2 == 3) {
        in_r6 = *(int *)(pcVar9 + 0x24);
        puVar5 = (undefined2 *)((iVar1 - in_r6) * 8);
        *(uint *)(pcVar9 + 0x28) = (uint)puVar5 / (DAT_800000f8 / 500000);
        if (iVar7 != 2) {
          if (pcVar9[1] != '\0') {
            puVar5 = *(undefined2 **)(pcVar9 + 0x24);
            *(int *)(pcVar9 + 0x24) = (int)puVar5 + (iVar1 - DAT_80436340);
          }
          if (piVar3 != (int *)0x0) {
            in_r6 = 0;
            while( true ) {
              puVar5 = *(undefined2 **)(pcVar9 + 0x28);
              if (puVar5 <= (undefined2 *)*piVar3) break;
              piVar4 = piVar3 + 2;
              *(int **)(pcVar9 + 0x34) = piVar4;
              pcVar9[0x20] = (char)piVar3[3];
              piVar3 = piVar4;
              if (*piVar4 == 99000000) {
                pcVar9[0x34] = '\0';
                pcVar9[0x35] = '\0';
                pcVar9[0x36] = '\0';
                pcVar9[0x37] = '\0';
              }
            }
          }
        }
      }
      if ((*pcVar9 != '\0') && ((iVar2 == 5 || (iVar2 == 0)))) {
        *pcVar9 = '\0';
        pcVar9[0x1b] = '\0';
        pcVar9[0x18] = '\0';
        pcVar9[0x40] = '\0';
        pcVar9[0x34] = '\0';
        pcVar9[0x35] = '\0';
        pcVar9[0x36] = '\0';
        pcVar9[0x37] = '\0';
        pcVar9[0x20] = '\0';
      }
    }
    iVar7 = iVar7 + 1;
    piVar8 = piVar8 + 1;
    pcVar9 = pcVar9 + 0x44;
  } while (iVar7 < 3);
  DAT_80436340 = iVar1;
  return;
}



// ==== 800e9914  zz_00e9914_ ====

void zz_00e9914_(void)

{
  float fVar1;
  float fVar2;
  undefined1 *puVar3;
  int iVar4;
  
  fVar2 = FLOAT_80438f4c;
  fVar1 = FLOAT_80438f48;
  puVar3 = &DAT_803cd218;
  iVar4 = 3;
  do {
    *(float *)(puVar3 + 0xc) = fVar2;
    *(float *)(puVar3 + 0x10) = fVar2;
    *(float *)(puVar3 + 0x14) = fVar1;
    *(float *)(puVar3 + 0x1c) = fVar1;
    puVar3[0x23] = 0;
    *(undefined4 *)(puVar3 + 0x38) = 0;
    *puVar3 = 0;
    puVar3[0x1b] = 0;
    puVar3[0x18] = 0;
    puVar3[0x40] = 0;
    puVar3[2] = 0;
    puVar3[0x19] = 0;
    puVar3[0x1a] = 0;
    puVar3[1] = 0;
    puVar3 = puVar3 + 0x44;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  DAT_803cd244 = PTR_DAT_8043394c + 0x2e;
  DAT_803cd288 = PTR_DAT_8043394c + 0x2e;
  DAT_803cd2cc = PTR_DAT_8043394c + 0x2c;
  return;
}



// ==== 800e9994  zz_00e9994_ ====

void zz_00e9994_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,int param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (DAT_804361c4 != 0) {
    FUN_800e9654(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    uVar1 = zz_00e9340_();
    zz_00e9784_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 800e99c8  zz_00e99c8_ ====

void zz_00e99c8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,int param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  
  fVar3 = FLOAT_80438f48;
  if (-1 < param_11) {
    (&DAT_803cd228)[param_9 * 0x11] = FLOAT_80438f4c;
    iVar4 = param_9 * 0x14;
    dVar6 = (double)(float)(&DAT_803cd228)[param_9 * 0x11];
    cVar2 = *(char *)(&DAT_803cd244)[param_9 * 0x11];
    fVar1 = (float)(dVar6 * (double)*(float *)(iVar4 + -0x7fce6004 + cVar2 * 4));
    (&DAT_803cd228)[param_9 * 0x11] = fVar1;
    (&DAT_803cd22c)[param_9 * 0x11] = fVar3;
    (&DAT_803cd23b)[param_9 * 0x44] = 0;
    (&DAT_803cd250)[param_9 * 0x11] = 0;
    (&DAT_803cd234)[param_9 * 0x11] = fVar3;
    (&DAT_803cd233)[param_9 * 0x44] = 1;
    (&DAT_803cd24c)[param_9 * 0x11] = 0;
    uVar5 = zz_00e95a4_((double)fVar1,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        0,cVar2 * 4,iVar4 + -0x7fce6004,iVar4,param_14,param_15,param_16);
    (&DAT_803cd222)[param_9 * 0x22] = (&DAT_803cd222)[param_9 * 0x22] + 1;
    uVar5 = zz_00e91d4_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,0,param_9,
                        param_10,param_11,iVar4,param_14,param_15,param_16);
    zz_00e91d4_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,1,param_9,0,0,iVar4,
                param_14,param_15,param_16);
  }
  return;
}



// ==== 800e9ac0  zz_00e9ac0_ ====

void zz_00e9ac0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_00e95a4_((double)FLOAT_80438f48,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e91d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,param_9,0,0,param_13,
              param_14,param_15,param_16);
  return;
}



// ==== 800e9b08  zz_00e9b08_ ====

void zz_00e9b08_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_00e91d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3,param_9,param_10,
              param_11,param_9,param_14,param_15,param_16);
  return;
}



// ==== 800e9b44  zz_00e9b44_ ====

int zz_00e9b44_(int param_1)

{
  return (int)(char)(&DAT_803cd219)[param_1 * 0x44];
}



// ==== 800e9b60  zz_00e9b60_ ====

void zz_00e9b60_(double param_1,int param_2,uint param_3,int param_4)

{
  float fVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = param_2 * 0x44;
  cVar2 = *(char *)(&DAT_803cd244)[param_2 * 0x11];
  *(uint *)(&DAT_803cd254 + iVar3) = param_3;
  (&DAT_803cd250)[param_2 * 0x11] = 0;
  fVar1 = (float)(param_1 * (double)*(float *)(param_2 * 0x14 + -0x7fce6004 + cVar2 * 4));
  if (param_4 == 0) {
    (&DAT_803cd228)[param_2 * 0x11] = fVar1;
    fVar1 = FLOAT_80438f48;
    (&DAT_803cd234)[param_2 * 0x11] =
         ((float)(&DAT_803cd228)[param_2 * 0x11] - (float)(&DAT_803cd224)[param_2 * 0x11]) /
         (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80438f58);
    if ((float)(&DAT_803cd234)[param_2 * 0x11] <= fVar1) {
      (&DAT_803cd234)[param_2 * 0x11] = FLOAT_80438f50;
    }
  }
  else {
    (&DAT_803cd22c)[param_2 * 0x11] = fVar1;
    fVar1 = FLOAT_80438f48;
    (&DAT_803cd234)[param_2 * 0x11] =
         ((float)(&DAT_803cd22c)[param_2 * 0x11] - (float)(&DAT_803cd224)[param_2 * 0x11]) /
         (float)((double)CONCAT44(0x43300000,param_3 ^ 0x80000000) - DOUBLE_80438f58);
    if (fVar1 <= (float)(&DAT_803cd234)[param_2 * 0x11]) {
      (&DAT_803cd234)[param_2 * 0x11] = FLOAT_80438f54;
    }
    if (param_4 == 2) {
      (&DAT_803cd23b)[iVar3] = 1;
    }
    else {
      (&DAT_803cd23b)[iVar3] = 0;
    }
  }
  return;
}



// ==== 800e9c78  zz_00e9c78_ ====

void zz_00e9c78_(double param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  
  fVar2 = FLOAT_80438f48;
  cVar1 = *(char *)(&DAT_803cd244)[param_9 * 0x11];
  iVar3 = param_9 * 0x14 + -0x7fce6004;
  (&DAT_803cd23b)[param_9 * 0x44] = 0;
  dVar4 = (double)*(float *)(iVar3 + cVar1 * 4);
  (&DAT_803cd250)[param_9 * 0x11] = 0;
  (&DAT_803cd234)[param_9 * 0x11] = fVar2;
  zz_00e95a4_((double)(float)(param_1 * dVar4),dVar4,param_3,param_4,param_5,param_6,param_7,param_8
              ,param_9,cVar1 * 4,iVar3,param_9 * 0x14,&DAT_803cd218 + param_9 * 0x44,in_r8,in_r9,
              in_r10);
  return;
}



// ==== 800e9ce4  zz_00e9ce4_ ====

void zz_00e9ce4_(double param_1,int param_2,uint param_3,int param_4,undefined4 param_5)

{
  zz_00e9b60_(param_1,param_2,param_3,param_4);
  (&DAT_803cd23b)[param_2 * 0x44] = 0;
  (&DAT_803cd250)[param_2 * 0x11] = param_5;
  return;
}



// ==== 800e9d38  zz_00e9d38_ ====

void zz_00e9d38_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  uVar1 = zz_00055fc_();
  zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
              *(int *)(&DAT_8031a074 + *(int *)(&DAT_8031a038 + (uVar1 % 9) * 4) * 4),&DAT_8031a038,
              in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800e9d9c  zz_00e9d9c_ ====

void zz_00e9d9c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  uint uVar4;
  
  iVar1 = zz_0196e80_();
  if (iVar1 == 0) {
    iVar1 = param_9 / 5 + (param_9 >> 0x1f);
    if (param_9 == (iVar1 - (iVar1 >> 0x1f)) * 5) {
      uVar4 = 2;
      puVar3 = &DAT_80434400;
    }
    else {
      uVar4 = 6;
      puVar3 = (undefined *)0x8031a05c;
    }
    uVar2 = zz_00055fc_();
    zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                *(int *)(&DAT_8031a074 +
                        *(int *)(puVar3 + (uVar2 - (uVar2 / uVar4) * uVar4) * 4) * 4),param_12,
                param_13,param_14,param_15,param_16);
  }
  else {
    zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0f0,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800e9e68  zz_00e9e68_ ====

uint zz_00e9e68_(int param_1)

{
  if (DAT_803cd233 != '\0') {
    if (param_1 == DAT_803cd21b) {
      return 0;
    }
  }
  if (DAT_803cd277 != '\0') {
    if (param_1 == DAT_803cd25f) {
      return 1;
    }
  }
  if (DAT_803cd233 == '\0') {
    return 0;
  }
  if (DAT_803cd277 == '\0') {
    return 1;
  }
  return (DAT_803cd23c | ~DAT_803cd280) - (DAT_803cd23c - DAT_803cd280 >> 1) >> 0x1f;
}



// ==== 800e9f0c  zz_00e9f0c_ ====

uint zz_00e9f0c_(int param_1,int param_2)

{
  short sVar1;
  float fVar2;
  uint uVar3;
  char cVar5;
  undefined *puVar4;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  undefined8 in_f4;
  undefined8 in_f5;
  undefined8 in_f6;
  undefined8 in_f7;
  undefined8 in_f8;
  
  uVar3 = zz_00e9e68_(param_1);
  dVar14 = DOUBLE_80438f58;
  fVar2 = FLOAT_80438f48;
  iVar9 = param_1 * 4;
  iVar6 = uVar3 * 0x44;
  psVar10 = (short *)((&PTR_DAT_80388df0)[param_1] + param_2 * 4);
  cVar5 = *(char *)((int)psVar10 + 3);
  if (cVar5 == '\0') {
    cVar5 = '\x7f';
  }
  dVar11 = (double)FLOAT_80438f60;
  puVar4 = (&PTR_DAT_803890b4)[param_1];
  iVar8 = (int)((float)((double)CONCAT44(0x43300000,(int)cVar5 ^ 0x80000000) - DOUBLE_80438f58) *
               *(float *)(uVar3 * 0x14 + -0x7fce6004 + *(char *)(&DAT_803cd244)[uVar3 * 0x11] * 4));
  uVar7 = (int)(char)iVar8 ^ 0x80000000;
  (&DAT_803cd228)[uVar3 * 0x11] = (float)((double)CONCAT44(0x43300000,uVar7) - DOUBLE_80438f58);
  dVar13 = (double)(float)(&DAT_803cd228)[uVar3 * 0x11];
  (&DAT_803cd22c)[uVar3 * 0x11] = (float)(dVar13 * dVar11);
  (&DAT_803cd23b)[iVar6] = 0;
  (&DAT_803cd250)[uVar3 * 0x11] = 0;
  (&DAT_803cd234)[uVar3 * 0x11] = fVar2;
  (&DAT_803cd233)[iVar6] = 1;
  (&DAT_803cd24c)[uVar3 * 0x11] = puVar4;
  if (puVar4 != (undefined *)0x0) {
    (&DAT_803cd24c)[uVar3 * 0x11] = *(undefined4 *)(puVar4 + *(char *)(psVar10 + 1) * 4);
  }
  (&DAT_803cd21b)[iVar6] = (char)param_1;
  dVar11 = DOUBLE_80438f58;
  sVar1 = (&DAT_803cd222)[uVar3 * 0x22];
  (&DAT_803cd222)[uVar3 * 0x22] = sVar1 + 1;
  uVar12 = zz_00e95a4_((double)(float)((double)CONCAT44(0x43300000,(int)(char)iVar8 ^ 0x80000000) -
                                      dVar11),dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,uVar3,
                       &DAT_803cd218 + iVar6,(int)sVar1,uVar7,iVar8,iVar9,in_r9,in_r10);
  uVar12 = zz_00e91d4_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,0,uVar3,0,(int)*psVar10,
                       iVar8,iVar9,in_r9,in_r10);
  zz_00e91d4_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,1,uVar3,0,0,iVar8,iVar9,in_r9,
              in_r10);
  return uVar3;
}



// ==== 800ea0bc  zz_00ea0bc_ ====

int zz_00ea0bc_(int param_1)

{
  return (int)(char)(&DAT_803cd238)[param_1 * 0x44];
}



// ==== 800ea0d8  zz_00ea0d8_ ====

int zz_00ea0d8_(int param_1)

{
  return (int)(short)(&DAT_803cd222)[param_1 * 0x22];
}



// ==== 800ea0f0  zz_00ea0f0_ ====

int zz_00ea0f0_(int param_1)

{
  return (int)(char)(&DAT_803cd233)[param_1 * 0x44];
}



// ==== 800ea10c  zz_00ea10c_ ====

undefined4 zz_00ea10c_(void)

{
  if (DAT_803cd258 == '\0') {
    return 0;
  }
  if (DAT_803cd29c != '\0') {
    return 0xffffffff;
  }
  return 1;
}



// ==== 800ea140  zz_00ea140_ ====

undefined4 zz_00ea140_(void)

{
  if ((DAT_803cd258 == '\0') && (DAT_803cd29c == '\0')) {
    return 0;
  }
  return 1;
}



// ==== 800ea170  zz_00ea170_ ====

uint zz_00ea170_(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  uVar2 = zz_00055fc_();
  uVar5 = 0xffffffff;
  if (param_3 == -1) {
    uVar5 = zz_00e9f0c_(param_1,param_4);
    if (-1 < (int)uVar5) {
      (&DAT_803cd230)[uVar5 * 0x44] = 0xfe;
      (&DAT_803cd258)[uVar5 * 0x44] = 0;
    }
  }
  else {
    iVar1 = param_3 * 4;
    if ((uVar2 & 0xff) < (uint)(byte)(&DAT_80319d98)[iVar1]) {
      uVar2 = zz_00e9e68_(param_1);
      if ((byte)(&DAT_803cd230)[uVar2 * 0x44] < (byte)(&DAT_80319d9a)[iVar1]) {
        puVar4 = (uint *)(*(int *)((&PTR_PTR_80319d2c)[param_1] + param_2 * 4) + param_3 * 8);
        if (param_4 < 0) {
          uVar2 = zz_00055fc_();
          uVar3 = *puVar4;
          param_4 = uVar2 - (uVar2 / uVar3) * uVar3;
        }
        uVar2 = (uint)*(byte *)(puVar4[1] + param_4);
        if ((uVar2 != 0xff) && (uVar5 = zz_00e9f0c_(param_1,uVar2), -1 < (int)uVar5)) {
          (&DAT_803cd230)[uVar5 * 0x44] = (&DAT_80319d9a)[iVar1];
          (&DAT_803cd258)[uVar5 * 0x44] = (&DAT_80319d9b)[iVar1];
        }
      }
    }
  }
  return uVar5;
}



// ==== 800ea2c8  zz_00ea2c8_ ====

void zz_00ea2c8_(int param_1,int param_2)

{
  zz_00ea2ec_(param_1,param_2,-1);
  return;
}



// ==== 800ea2ec  zz_00ea2ec_ ====

uint zz_00ea2ec_(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  if ((char)PTR_DAT_80433934[0x45] < '\x05') {
    uVar1 = zz_00055fc_();
    uVar1 = (uVar1 & 0xff) - (uint)(byte)(&DAT_80319d99)[param_2 * 4] >> 0x1f;
    if ('\r' < *(char *)(param_1 + 0x438)) {
      uVar1 = 0;
    }
    if (PTR_DAT_80433934[0x15dd] == '\0') {
      uVar1 = 0;
    }
    if (((uint)(byte)PTR_DAT_80433934[0x1828] & 1 << (int)*(char *)(param_1 + 0x3e4)) == 0) {
      if ((char)PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x26] < 0) {
        uVar1 = 0xffffffff;
      }
      else {
        if (uVar1 == 0) {
          if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x183) != '\0') {
            return 0xffffffff;
          }
          iVar2 = 0x10;
        }
        else {
          iVar2 = (int)*(char *)(param_1 + 0x438);
        }
        uVar1 = zz_00ea170_(iVar2,(int)(char)PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x26],
                            param_2,param_3);
        if (((-1 < (int)uVar1) && (iVar2 < 0xe)) && ((&DAT_80319d9b)[param_2 * 4] != '\0')) {
          zz_00dbf04_(1,uVar1,(int)*(char *)(param_1 + 0x3e4),0);
        }
      }
    }
    else {
      uVar1 = 0xffffffff;
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}



// ==== 800ea440  zz_00ea440_ ====

uint zz_00ea440_(int param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = zz_00e9f0c_(param_1,param_2);
  if (-1 < (int)uVar1) {
    iVar3 = uVar1 * 0x44;
    (&DAT_803cd230)[iVar3] = 0xff;
    if ((param_3 != 0) && ((&DAT_803cd258)[iVar3] = 0, param_1 < 0xe)) {
      iVar4 = 0;
      iVar5 = 6;
      puVar2 = PTR_DAT_80433934;
      do {
        if ((char)puVar2[0x20] == param_1) {
          (&DAT_803cd258)[iVar3] = (char)param_3;
          zz_00dbf04_(1,uVar1,iVar4,0);
          return uVar1;
        }
        puVar2 = puVar2 + 1;
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return uVar1;
}



// ==== 800ea5fc  FUN_800ea5fc ====

void FUN_800ea5fc(int param_1)

{
  zz_0098220_(param_1);
  return;
}



// ==== 800ea61c  FUN_800ea61c ====

void FUN_800ea61c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438f70;
  fVar1 = FLOAT_80438f68;
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(short *)(param_1 + 0x1d64) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                             DOUBLE_80438f70) * FLOAT_80438f68);
    *(short *)(param_1 + 0x18dc) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(undefined1 *)(param_1 + 0x6ee) = 0;
  }
  return;
}



// ==== 800ea6c4  FUN_800ea6c4 ====

void FUN_800ea6c4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8031b0a8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800ea718  FUN_800ea718 ====

void FUN_800ea718(int param_1)

{
  zz_00aeef8_(param_1,0);
  return;
}



// ==== 800ea73c  FUN_800ea73c ====

void FUN_800ea73c(int param_1)

{
  (*(code *)(&PTR_FUN_8031b0b8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800ea778  FUN_800ea778 ====

void FUN_800ea778(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438f70;
  fVar1 = FLOAT_80438f68;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_80438f70) * FLOAT_80438f68);
  *(short *)(param_1 + 0x18dc) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_8031b0c4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ea818  FUN_800ea818 ====

void FUN_800ea818(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8031b0ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ea860  FUN_800ea860 ====

void FUN_800ea860(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80438f78;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_80438f78,param_1,2,2,9,0xffffffff,0xffffffff);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_00eb1f8_(param_1);
  fVar1 = FLOAT_80438f7c;
  *(float *)(param_1 + 0x4c) = FLOAT_80438f7c;
  *(float *)(param_1 + 0x44) = fVar1;
  return;
}



// ==== 800ea8f8  FUN_800ea8f8 ====

void FUN_800ea8f8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80438f7c;
  if ((iVar3 == 0) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00eb228_(param_1);
  }
  return;
}



// ==== 800ea98c  FUN_800ea98c ====

void FUN_800ea98c(int param_1)

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
      dVar2 = (double)FLOAT_80438f78;
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



// ==== 800eaa8c  FUN_800eaa8c ====

void FUN_800eaa8c(int param_1)

{
  (*(code *)(&PTR_FUN_8031b0f8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800eaac8  FUN_800eaac8 ====

void FUN_800eaac8(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438f78;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 3,0xffffffff,0xffffffff);
  zz_00eb1f8_(param_1);
  return;
}



// ==== 800eab28  FUN_800eab28 ====

void FUN_800eab28(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80438f7c;
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
      zz_00eb228_(param_1);
    }
  }
  return;
}



// ==== 800eabd4  FUN_800eabd4 ====

void FUN_800eabd4(double param_1,double param_2,double param_3,double param_4,double param_5,
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
      if (((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
        if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
          zz_006bf80_(param_9);
          dVar2 = (double)FLOAT_80438f78;
          *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
          zz_004beb8_(dVar2,param_9,1,2,4,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      zz_006a3d0_(param_9,'\0',3,2);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xf,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800eacf8  FUN_800eacf8 ====

void FUN_800eacf8(int param_1)

{
  (*(code *)(&PTR_FUN_8031b104)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ead34  FUN_800ead34 ====

void FUN_800ead34(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438f78;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar1,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  if ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) {
    zz_006a5a4_(param_1);
    zz_004beb8_((double)FLOAT_80438f78,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_00eb1f8_(param_1);
  return;
}



// ==== 800eadc8  FUN_800eadc8 ====

void FUN_800eadc8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80438f7c;
  if ((iVar3 < 1) &&
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
    return;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00eb228_(param_1);
  }
  return;
}



// ==== 800eae5c  FUN_800eae5c ====

void FUN_800eae5c(double param_1,double param_2,double param_3,double param_4,double param_5,
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
      dVar2 = (double)FLOAT_80438f78;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xf,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800eaf54  FUN_800eaf54 ====

void FUN_800eaf54(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8031b110)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800eaf9c  FUN_800eaf9c ====

void FUN_800eaf9c(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80438f80;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80438f78,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_80438f78,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_00eb1f8_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80438f7c;
  return;
}



// ==== 800eb070  FUN_800eb070 ====

void FUN_800eb070(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00eb228_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800eb104  FUN_800eb104 ====

void FUN_800eb104(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  if ((*(uint *)(param_9 + 0x5b4) & 0x200) == 0) {
    if (*(char *)(param_9 + 0x1cee) == '\0') {
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
      dVar2 = (double)FLOAT_80438f78;
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
      *(undefined1 *)(param_9 + 0x581) = 3;
      zz_004beb8_(dVar2,param_9,1,2,7,0xffffffff,0xffffffff);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xf,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800eb1f8  zz_00eb1f8_ ====

void zz_00eb1f8_(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x6ee) == '\0') {
    *(undefined1 *)(param_1 + 0x6ef) = 5;
  }
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  fVar1 = FLOAT_80438f84;
  *(undefined1 *)(param_1 + 0x6ed) = 7;
  *(float *)(param_1 + 0x560) = fVar1;
  return;
}



// ==== 800eb228  zz_00eb228_ ====

void zz_00eb228_(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_006ee14_(param_1,0);
  }
  return;
}



// ==== 800eb288  zz_00eb288_ ====

void zz_00eb288_(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438f70;
  fVar1 = FLOAT_80438f68;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_80438f70) * FLOAT_80438f68);
  *(short *)(param_1 + 0x18dc) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_zz_00eb328__8031b11c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800eb328  zz_00eb328_ ====

void zz_00eb328_(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 800eb350  zz_00eb350_ ====

void zz_00eb350_(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 800eb378  zz_00eb378_ ====

void zz_00eb378_(int param_1)

{
  zz_00fed6c_(param_1);
  return;
}



// ==== 800eb3a0  zz_00eb3a0_ ====

void zz_00eb3a0_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_00eb3f0__8031b178)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800eb3f0  zz_00eb3f0_ ====

void zz_00eb3f0_(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(char *)(param_1 + 0x581) == '\x03') {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80438f88;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438f8c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80438f78,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 800eb500  zz_00eb500_ ====

void zz_00eb500_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438f8c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80438f84;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_80438f90;
    fVar2 = FLOAT_80438f7c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438f84;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800eb630  zz_00eb630_ ====

void zz_00eb630_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  if (*(int *)(param_1 + 0xcc) != 0) {
    fVar1 = *(float *)(param_1 + 0x51c) -
            *(float *)(param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30 + 0x8f0);
    if (FLOAT_80438f84 < fVar1) {
      fVar1 = FLOAT_80438f84;
    }
    if (fVar1 < FLOAT_80438f94) {
      fVar1 = FLOAT_80438f94;
    }
    *(float *)(param_1 + 0x48) = fVar1;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (((fVar2 < fVar1) && (uVar3 = FUN_80066838((double)FLOAT_80438f90,param_1), (int)uVar3 < 1)) &&
     (*(char *)(param_1 + 0x1d9) == '\0')) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  return;
}



// ==== 800eb738  zz_00eb738_ ====

void zz_00eb738_(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar1 = FLOAT_80438f7c;
  if ((*(char *)(param_1 + 0x1d0f) < '\0') &&
     (*(undefined1 *)(param_1 + 0x1d0f) = 0, fVar1 < *(float *)(param_1 + 0x48))) {
    *(float *)(param_1 + 0x48) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_80438f8c,param_1);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438f80 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800eb83c  zz_00eb83c_ ====

void zz_00eb83c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_00eb88c__8031b188)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800eb88c  zz_00eb88c_ ====

void zz_00eb88c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar3 = FLOAT_80438f98;
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c);
  if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
    fVar1 = *(float *)(param_1 + 0x764);
  }
  *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438f98;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x558) = fVar3;
  zz_0092dcc_(param_1,0);
  zz_004beb8_((double)FLOAT_80438f78,param_1,0xf,3,5,0xffffffff,0xffffffff);
  zz_00eb9b8_(param_1);
  return;
}



// ==== 800eb9b8  zz_00eb9b8_ ====

void zz_00eb9b8_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  if (*(int *)(param_1 + 0xcc) != 0) {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_18 = *(float *)(iVar4 + 0x8e0);
    local_14 = *(float *)(iVar4 + 0x8f0);
    local_10 = *(undefined4 *)(iVar4 + 0x900);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_18,&local_18);
    *(float *)(param_1 + 0x48) = local_14 / FLOAT_80438f9c;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80438fa0,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800ebab4  zz_00ebab4_ ====

void zz_00ebab4_(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar1 = FLOAT_80438f7c;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80438fa4,param_1);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438f80 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800ebbd0  zz_00ebbd0_ ====

void zz_00ebbd0_(int param_1)

{
  (*(code *)(&PTR_zz_00ebc0c__8031b194)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ebc0c  zz_00ebc0c_ ====

void zz_00ebc0c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_00ebc5c__8031b1a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ebc5c  zz_00ebc5c_ ====

void zz_00ebc5c_(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80438f88;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438fa4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80438f78;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80438f7c;
  return;
}



// ==== 800ebd74  zz_00ebd74_ ====

void zz_00ebd74_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438fa4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800ebe18  zz_00ebe18_ ====

void zz_00ebe18_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  zz_006d144_(param_1,0xc0);
  gnt4_PSQUATScale_bl((double)FLOAT_80438fa4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80438fa8;
  fVar1 = FLOAT_80438f7c;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80438fac;
    *(float *)(param_1 + 0x558) = fVar2;
    fVar2 = FLOAT_80438fb0;
    *(undefined1 *)(param_1 + 0x6e9) = 6;
    fVar4 = FLOAT_80438fb4;
    *(float *)(param_1 + 0x38) = fVar1;
    *(float *)(param_1 + 0x3c) = fVar3;
    *(float *)(param_1 + 0x40) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
    if (fVar4 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800ebee0  zz_00ebee0_ ====

void zz_00ebee0_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x3c);
  }
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar6 = (double)FLOAT_80438f80;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  zz_00f0104_(param_1,3,2);
  fVar3 = FLOAT_80438f7c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  fVar4 = FLOAT_80438fb8;
  if (fVar2 <= fVar3) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar4;
    if (fVar3 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar3;
    }
    dVar5 = (double)FLOAT_80438f78;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800ec02c  zz_00ec02c_ ====

void zz_00ec02c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438f70) * FLOAT_80438f68);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438f80,param_1,*(short *)(param_1 + 0x5ae));
  zz_00f0104_(param_1,3,2);
  fVar2 = FLOAT_80438f7c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_00677b0_(param_1);
    fVar1 = FLOAT_80438f90;
    if (iVar3 != 0) {
      dVar4 = (double)FLOAT_80438f78;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar1;
      *(undefined2 *)(param_1 + 0x18da) = 0;
      zz_004beb8_(dVar4,param_1,0xf,0x82,4,0xffffffff,0);
      zz_0066530_(param_1,0x2c);
      zz_00b2190_(param_1,2);
    }
    zz_00b22f4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800ec160  zz_00ec160_ ====

void zz_00ec160_(int param_1)

{
  double dVar1;
  
  if (*(float *)(param_1 + 0x558) <= FLOAT_80438f7c) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar1 = (double)FLOAT_80438fa4;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    zz_006ed8c_(dVar1,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800ec1f4  zz_00ec1f4_ ====

void zz_00ec1f4_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x47;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = zz_00ec2ec_;
    *(code **)(puVar1 + 0x10c) = zz_00ec880_;
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



// ==== 800ec2ec  zz_00ec2ec_ ====

void zz_00ec2ec_(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_zz_00ec394__8031b200)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800ec394  zz_00ec394_ ====

void zz_00ec394_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  fVar1 = FLOAT_80438fc0;
  iVar6 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x10;
  puVar3 = &DAT_8031b1c0 + iVar4;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(undefined1 *)(param_9 + 0x12) = 1;
  *(undefined1 *)(param_9 + 0x13) = 100;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xc0) = fVar1;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031b1c2 + iVar4);
  uVar2 = *(undefined4 *)(&DAT_8031b1c8 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031b1c4 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031b1cc + iVar4);
  zz_00ecbc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  iVar5 = 0;
  do {
    zz_00eccb8_(param_9);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 5);
  *(code **)(param_9 + 0x100) = zz_00ec9f8_;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
  zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
              *(int *)(param_9 + 0xe0),3,puVar3,iVar4,in_r8,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  return;
}



// ==== 800ec4a4  zz_00ec4a4_ ====

void zz_00ec4a4_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80438fc4;
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  fVar1 = *(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)((double)fVar1 + dVar2);
  zz_00ece38_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  (**(code **)(&DAT_80434408 + *(char *)(param_9 + 0x19) * 4))(param_9);
  return;
}



// ==== 800ec50c  zz_00ec50c_ ====

void zz_00ec50c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  
  fVar2 = FLOAT_80438fc4;
  iVar4 = *(int *)(param_9 + 0x8c);
  if (*(char *)(param_9 + 0x1a) == '\0') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar5 = (double)FLOAT_80438fc8;
    *(float *)(param_9 + 0xb4) = (float)(param_2 / dVar5);
    if (fVar2 <= (float)(param_2 / dVar5)) {
      *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
      *(float *)(param_9 + 0xb4) = fVar2;
    }
  }
  fVar2 = FLOAT_80438fc0;
  if ('\0' < *(char *)(iVar4 + 0x6ea)) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(float *)(param_9 + 0xd4) = fVar2;
    *(undefined1 *)(param_9 + 0x12) = 0;
    uVar3 = zz_00055fc_();
    fVar2 = FLOAT_80438fc0;
    *(short *)(param_9 + 0x74) = (short)(uVar3 << 8);
    *(float *)(param_9 + 0xb4) = fVar2;
    uVar6 = zz_0040d64_((int)*(char *)(iVar4 + 0x3e4),4);
    iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xe0),2,param_12,param_13,param_14,param_15,param_16);
  }
  iVar4 = 0;
  do {
    zz_00eccb8_(param_9);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 5);
  uVar1 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  return;
}



// ==== 800ec60c  zz_00ec60c_ ====

void zz_00ec60c_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [16];
  
  fVar4 = FLOAT_80438fc4;
  iVar5 = *(int *)(param_1 + 0x8c);
  if (*(char *)(param_1 + 0x1a) == '\0') {
    fVar3 = *(float *)(param_1 + 0xd4) / FLOAT_80438fcc;
    *(float *)(param_1 + 0xb4) = fVar3;
    if (fVar4 <= fVar3) {
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(float *)(param_1 + 0xb4) = fVar4;
    }
  }
  if ('\x01' < *(char *)(iVar5 + 0x6ea)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    fVar4 = FLOAT_80438fc0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(float *)(param_1 + 0xd4) = fVar4;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0xb4);
  }
  local_54 = FLOAT_80438fc0;
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1000;
  *(float *)(param_1 + 0xc0) = *(float *)(iVar5 + 0xc0) * *(float *)(param_1 + 0xb4);
  uVar2 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  bVar1 = *(byte *)(param_1 + 0x11);
  local_58 = local_54;
  zz_00455fc_((float *)(iVar5 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),afStack_4c,
              (float *)(param_1 + 100));
  zz_00456a0_(afStack_4c,afStack_4c,(float *)(param_1 + 0x58));
  local_50 = FLOAT_80438fd0;
  gnt4_PSMTXMultVec_bl(afStack_4c,&local_58,(float *)(param_1 + 0x38));
  local_50 = local_50 + FLOAT_80438fd4;
  gnt4_PSMTXMultVec_bl(afStack_4c,&local_58,(float *)(param_1 + 0x9c));
  zz_0139a6c_(param_1,param_1 + 0x38,param_1 + 0x9c,
              (char)*(undefined2 *)(&DAT_8031b1c0 + (uint)bVar1 * 0x10));
  return;
}



// ==== 800ec77c  zz_00ec77c_ ====

void zz_00ec77c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar1 = FLOAT_80438fc4;
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) + fVar1;
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    zz_0040d64_((int)*(char *)(*(int *)(param_1 + 0x8c) + 0x3e4),5);
  }
  fVar2 = FLOAT_80438fc0;
  fVar1 = *(float *)(param_1 + 0x44) - *(float *)(param_1 + 0xd4) / FLOAT_80438fd8;
  *(float *)(param_1 + 0xb4) = fVar1;
  if (fVar1 <= fVar2) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1000;
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  return;
}



// ==== 800ec838  zz_00ec838_ ====

void zz_00ec838_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800ec880  zz_00ec880_ ====

/* WARNING: Removing unreachable block (ram,0x800ec958) */

void zz_00ec880_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  float afStack_48 [13];
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    uVar5 = 0;
    iVar6 = 0;
    while ((int)uVar5 < (int)*(char *)(param_9 + 0x13)) {
      if (((int)*(char *)(param_9 + ((int)uVar5 >> 3) + 0x144) & 1 << (uVar5 & 7)) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar6);
        param_2 = (double)pfVar4[1];
        param_3 = (double)pfVar4[2];
        gnt4_PSMTXTrans_bl((double)*pfVar4,param_2,param_3,afStack_48);
        param_11 = pfVar4 + 3;
        uVar7 = zz_00456a0_(afStack_48,afStack_48,param_11);
        if (iVar2 == 0) {
          param_11 = (float *)&DAT_80438fe4;
          gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80438fdc,0x495,&DAT_80438fe4,param_12,param_13,param_14,param_15,
                           param_16);
        }
        uVar7 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                       (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      iVar6 = iVar6 + 0x2c;
      uVar5 = uVar5 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    param_1 = zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),(undefined *)param_11,param_12,
              param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 800ec9f8  zz_00ec9f8_ ====

void zz_00ec9f8_(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  uint uVar4;
  int iVar5;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [2];
  float local_44;
  float local_34;
  float local_24;
  
  zz_00455fc_((float *)(*(int *)(param_1 + 0x8c) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
              (float *)(param_1 + 0x114),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  if (*(int *)(param_1 + 0xdc) != 0) {
    uVar4 = 0;
    iVar5 = 0;
    while( true ) {
      if ((int)*(char *)(param_1 + 0x13) <= (int)uVar4) break;
      if (((int)*(char *)(param_1 + ((int)uVar4 >> 3) + 0x144) & 1 << (uVar4 & 7)) != 0) {
        pfVar3 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar5);
        gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),afStack_4c);
        zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)((int)pfVar3 + 0x1a));
        zz_00457d4_('x',afStack_4c,afStack_4c,*(short *)(pfVar3 + 6));
        *pfVar3 = local_44;
        pfVar3[1] = local_34;
        pfVar3[2] = local_24;
        gnt4_PSVECNormalize_bl(pfVar3,pfVar3);
        gnt4_PSQUATScale_bl((double)pfVar3[10],pfVar3,pfVar3);
        gnt4_PSVECAdd_bl(pfVar3,(float *)(param_1 + 0x20),pfVar3);
      }
      iVar5 = iVar5 + 0x2c;
      uVar4 = uVar4 + 1;
    }
  }
  iVar5 = ((int)*(short *)(param_1 + 0x1c) & 1U) * 0xc;
  iVar1 = *(char *)(param_1 + 0x12) * 0x18 + -0x7fce4e30;
  iVar2 = iVar1 + iVar5;
  local_58 = *(float *)(param_1 + 0x58) * *(float *)(iVar1 + iVar5);
  local_54 = *(float *)(param_1 + 0x5c) * *(float *)(iVar2 + 4);
  local_50 = *(float *)(param_1 + 0x60) * *(float *)(iVar2 + 8);
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),&local_58);
  return;
}



// ==== 800ecbc8  zz_00ecbc8_ ====

void zz_00ecbc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar5;
  undefined8 uVar6;
  
  piVar2 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x2c);
  *(int **)(param_9 + 0xdc) = piVar2;
  if (piVar2 != (int *)0x0) {
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x8c));
    uVar6 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                        *(int *)(param_9 + 0xe4),(char *)0x4,(int)*(char *)(param_9 + 0x13),in_r7,
                        in_r8,in_r9,in_r10);
    uVar5 = 0;
    iVar3 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    while ((int)uVar5 < (int)*(char *)(param_9 + 0x13)) {
      iVar4 = ((int)uVar5 >> 3) + 0x144;
      bVar1 = *(byte *)(param_9 + iVar4);
      *(byte *)(param_9 + iVar4) = bVar1 & ~(byte)(1 << (uVar5 & 7));
      uVar6 = gnt4_HSD_JObjSetFlagsAll
                        (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10,
                         (undefined *)(uint)bVar1,iVar4,in_r7,in_r8,in_r9,in_r10);
      uVar5 = uVar5 + 1;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8);
      }
    }
  }
  return;
}



// ==== 800eccb8  zz_00eccb8_ ====

void zz_00eccb8_(int param_1)

{
  undefined4 uVar1;
  float fVar2;
  uint uVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    uVar10 = 0;
    while( true ) {
      if ((int)*(char *)(param_1 + 0x13) <= (int)uVar10) break;
      iVar6 = ((int)uVar10 >> 3) + 0x144;
      uVar5 = 1 << (uVar10 & 7);
      if (((int)*(char *)(param_1 + iVar6) & uVar5) == 0) {
        puVar4 = *(undefined **)(*(int *)(param_1 + 0xe4) + 0xc);
        iVar9 = *(int *)(param_1 + 0x8c);
        iVar8 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + uVar10 * 0x2c;
        if (puVar4 == (undefined *)0x0) {
          iVar7 = 0;
        }
        else {
          iVar7 = *(int *)(puVar4 + 0x10);
        }
        *(byte *)(param_1 + iVar6) = *(byte *)(param_1 + iVar6) | (byte)uVar5;
        uVar3 = zz_00055fc_();
        dVar13 = (double)(float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438ff8);
        dVar12 = (double)(float)(dVar13 / (double)FLOAT_80438ff0);
        *(float *)(iVar8 + 0x24) =
             *(float *)(iVar9 + 0xb4) * (float)((double)FLOAT_80438fec + dVar12);
        *(undefined4 *)(iVar8 + 0x28) = *(undefined4 *)(iVar8 + 0x24);
        uVar3 = zz_00055fc_();
        *(ushort *)(iVar8 + 0x18) = ((ushort)(uVar3 << 7) & 0x7f80) + 0xc000;
        uVar3 = zz_00055fc_();
        fVar2 = FLOAT_80438fc0;
        dVar11 = (double)FLOAT_80438ff4;
        *(ushort *)(iVar8 + 0x1a) = ((ushort)(uVar3 << 7) & 0x7f80) + 0xc000;
        *(float *)(iVar8 + 0x1c) = fVar2;
        *(float *)(iVar8 + 0x20) = (float)(dVar11 * (double)*(float *)(iVar9 + 0xb4));
        uVar1 = *(undefined4 *)(iVar9 + 0xb4);
        *(undefined4 *)(iVar8 + 0x14) = uVar1;
        *(undefined4 *)(iVar8 + 0x10) = uVar1;
        *(undefined4 *)(iVar8 + 0xc) = uVar1;
        if (0 < (int)uVar10) {
          do {
            if (iVar7 == 0) {
              iVar7 = 0;
            }
            else {
              iVar7 = *(int *)(iVar7 + 8);
            }
            uVar10 = uVar10 - 1;
          } while (uVar10 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  (dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,iVar7,0x10,puVar4,uVar5,iVar6,
                   in_r8,in_r9,in_r10);
        zz_00091e4_((double)*(float *)(iVar8 + 0x1c),iVar7);
        uVar10 = (uint)*(char *)(param_1 + 0x13);
      }
      uVar10 = uVar10 + 1;
    }
  }
  return;
}



// ==== 800ece38  zz_00ece38_ ====

void zz_00ece38_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  uint uVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  
  iVar3 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(iVar3 + 0x10);
  }
  if (*(int *)(param_9 + 0xdc) != 0) {
    uVar7 = 0;
    iVar8 = 0;
    while( true ) {
      fVar2 = FLOAT_80438fc4;
      if ((int)*(char *)(param_9 + 0x13) <= (int)uVar7) break;
      iVar5 = ((int)uVar7 >> 3) + 0x144;
      puVar4 = (undefined *)(1 << (uVar7 & 7));
      if (((int)*(char *)(param_9 + iVar5) & (uint)puVar4) != 0) {
        dVar9 = (double)FLOAT_80438fc4;
        iVar6 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8;
        if ((double)*(float *)(iVar6 + 0x1c) < dVar9) {
          fVar1 = (float)((double)*(float *)(iVar6 + 0x1c) + DOUBLE_80439000);
          *(float *)(iVar6 + 0x1c) = fVar1;
          if (dVar9 <= (double)fVar1) {
            *(float *)(iVar6 + 0x1c) = fVar2;
          }
        }
        fVar1 = *(float *)(iVar6 + 0x28);
        dVar9 = (double)FLOAT_80438fc4;
        fVar2 = (float)((double)fVar1 - (double)*(float *)(iVar6 + 0x20));
        dVar10 = (double)fVar2;
        *(float *)(iVar6 + 0x28) = fVar2;
        if (dVar10 < dVar9) {
          *(byte *)(param_9 + iVar5) = *(byte *)(param_9 + iVar5) & ~(byte)puVar4;
          gnt4_HSD_JObjSetFlagsAll
                    (dVar10,(double)fVar1,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10
                     ,puVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
        }
        zz_00091e4_((double)*(float *)(iVar6 + 0x1c),iVar3);
      }
      iVar8 = iVar8 + 0x2c;
      uVar7 = uVar7 + 1;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8);
      }
    }
  }
  return;
}



// ==== 800ecf60  zz_00ecf60_ ====

void zz_00ecf60_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined1 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar1;
  
  AIInit(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,param_10,param_11,
         param_12,param_13,param_14,param_15,param_16);
  DAT_803cf8ec = 0x7f;
  DAT_803cf8e9 = 0;
  DAT_803cf8ea = 0;
  DAT_803cf900 = 0;
  DAT_803cf902 = 0;
  DAT_803cf904 = 0;
  DAT_803cf908 = 0;
  DAT_803cf910 = 0;
  DAT_803cf90c = 0;
  DAT_803d3ae0 = 0;
  DAT_803d3ae4 = 0;
  DAT_803cf8ed = param_9;
  uVar1 = zz_00ed1cc_();
  uVar1 = zz_00f1500_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14
                      ,param_15,param_16);
  zz_0216d98_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_021c4c8_();
  zz_021a444_();
  zz_021c620_();
  zz_021c50c_();
  zz_0218548_(FUN_800ef390);
  DAT_803cf8f8 = zz_00f177c_();
  zz_00f18fc_();
  DAT_803cf8fc = zz_00f1924_();
  zz_0205c4c_((undefined4 *)&DAT_803d3ab0,s_Nise_Random_802b1cf8);
  zz_0205c78_(-0x7fc2c550);
  zz_010d9ac_();
  DAT_803cf8f0 = zz_0219d94_();
  DAT_803cf8f4 = 0;
  DAT_803cf8ef = 0;
  return;
}



// ==== 800ed058  zz_00ed058_ ====

void zz_00ed058_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,int param_11,undefined *param_12,
                undefined4 param_13,undefined *param_14,uint param_15,int param_16)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  undefined8 uVar7;
  
  puVar6 = &DAT_803cd2e8;
  if (DAT_803cf914 != 0) {
    param_11 = DAT_803cfb18 + 0x2f;
    iVar5 = 0;
    iVar1 = param_11 / 0x30 + (param_11 >> 0x1f);
    iVar4 = -(iVar1 >> 0x1f);
    param_16 = param_11 + (iVar1 + iVar4) * -0x30;
    iVar1 = DAT_803cfb1c;
    while( true ) {
      if (DAT_803cf914 <= iVar5) break;
      param_15 = *(uint *)(puVar6 + 0x2630);
      if ((param_15 >> 0x18 & 0x80) == 0) {
        if (iVar1 == param_16) {
          uVar7 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_802b1d04,iVar4,param_11,param_12,param_13,param_14,param_15,
                                   param_16);
          uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_802b1d30,extraout_r4,param_11,param_12,param_13,param_14,
                                   param_15,param_16);
          uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_802b1d50,extraout_r4_00,param_11,param_12,param_13,param_14,
                                   param_15,param_16);
          param_11 = -0x7fd50000;
          param_1 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     &DAT_802b1d78,(&DAT_803cf918)[iVar5 * 4],0x802b0000,param_12,
                                     param_13,param_14,param_15,param_16);
          break;
        }
        param_11 = iVar1 + 1;
        iVar1 = iVar1 * 0x10;
        uVar3 = *(undefined4 *)(puVar6 + 0x2634);
        param_14 = &DAT_803cd2e8 + iVar1;
        *(uint *)(&DAT_803cfb20 + iVar1) = param_15;
        *(undefined4 *)(&DAT_803cfb24 + iVar1) = uVar3;
        iVar2 = param_11 / 0x30 + (param_11 >> 0x1f);
        iVar4 = -(iVar2 >> 0x1f);
        param_13 = *(undefined4 *)(puVar6 + 0x2638);
        param_12 = *(undefined **)(puVar6 + 0x263c);
        *(undefined4 *)(&DAT_803cfb28 + iVar1) = param_13;
        *(undefined **)(&DAT_803cfb2c + iVar1) = param_12;
        iVar1 = param_11 + (iVar2 + iVar4) * -0x30;
      }
      puVar6 = puVar6 + 0x10;
      iVar5 = iVar5 + 1;
    }
    DAT_803cf914 = 0;
    DAT_803cfb1c = iVar1;
  }
  iVar1 = DAT_803cf90c;
  DAT_803cf90c = DAT_803cf90c + 1;
  zz_00eda40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&DAT_803cd2e8,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ed1cc  zz_00ed1cc_ ====

void zz_00ed1cc_(void)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  undefined *puVar7;
  undefined *puVar8;
  short sVar9;
  short sVar10;
  int iVar11;
  
  puVar7 = &DAT_803cd2e8;
  sVar6 = 0;
  DAT_803cfb1c = 0;
  DAT_803cfb18 = 0;
  DAT_803cf914 = 0;
  iVar11 = 8;
  puVar8 = puVar7;
  do {
    sVar10 = sVar6 + 1;
    puVar8[0x6784] = '?' - (char)sVar6;
    *(undefined4 *)(puVar7 + 0x4280) = 0;
    sVar9 = sVar6 + 2;
    sVar5 = sVar6 + 3;
    *(undefined2 *)(puVar7 + 0x42a6) = 0xffff;
    sVar4 = sVar6 + 4;
    sVar3 = sVar6 + 5;
    *(short *)(puVar7 + 0x42a8) = sVar6;
    sVar2 = sVar6 + 6;
    *(undefined2 *)(puVar7 + 0x42aa) = 0xffff;
    sVar1 = sVar6 + 7;
    sVar6 = sVar6 + 8;
    *(undefined2 *)(puVar7 + 0x42ac) = 0xffff;
    *(undefined4 *)(puVar7 + 0x4288) = 0;
    puVar8[0x6785] = '?' - (char)sVar10;
    *(undefined4 *)(puVar7 + 0x4314) = 0;
    *(undefined2 *)(puVar7 + 0x433a) = 0xffff;
    *(short *)(puVar7 + 0x433c) = sVar10;
    *(undefined2 *)(puVar7 + 0x433e) = 0xffff;
    *(undefined2 *)(puVar7 + 0x4340) = 0xffff;
    *(undefined4 *)(puVar7 + 0x431c) = 0;
    puVar8[0x6786] = '?' - (char)sVar9;
    *(undefined4 *)(puVar7 + 0x43a8) = 0;
    *(undefined2 *)(puVar7 + 0x43ce) = 0xffff;
    *(short *)(puVar7 + 0x43d0) = sVar9;
    *(undefined2 *)(puVar7 + 0x43d2) = 0xffff;
    *(undefined2 *)(puVar7 + 0x43d4) = 0xffff;
    *(undefined4 *)(puVar7 + 0x43b0) = 0;
    puVar8[0x6787] = '?' - (char)sVar5;
    *(undefined4 *)(puVar7 + 0x443c) = 0;
    *(undefined2 *)(puVar7 + 0x4462) = 0xffff;
    *(short *)(puVar7 + 0x4464) = sVar5;
    *(undefined2 *)(puVar7 + 0x4466) = 0xffff;
    *(undefined2 *)(puVar7 + 0x4468) = 0xffff;
    *(undefined4 *)(puVar7 + 0x4444) = 0;
    puVar8[0x6788] = '?' - (char)sVar4;
    *(undefined4 *)(puVar7 + 0x44d0) = 0;
    *(undefined2 *)(puVar7 + 0x44f6) = 0xffff;
    *(short *)(puVar7 + 0x44f8) = sVar4;
    *(undefined2 *)(puVar7 + 0x44fa) = 0xffff;
    *(undefined2 *)(puVar7 + 0x44fc) = 0xffff;
    *(undefined4 *)(puVar7 + 0x44d8) = 0;
    puVar8[0x6789] = '?' - (char)sVar3;
    *(undefined4 *)(puVar7 + 0x4564) = 0;
    *(undefined2 *)(puVar7 + 0x458a) = 0xffff;
    *(short *)(puVar7 + 0x458c) = sVar3;
    *(undefined2 *)(puVar7 + 0x458e) = 0xffff;
    *(undefined2 *)(puVar7 + 0x4590) = 0xffff;
    *(undefined4 *)(puVar7 + 0x456c) = 0;
    puVar8[0x678a] = '?' - (char)sVar2;
    *(undefined4 *)(puVar7 + 0x45f8) = 0;
    *(undefined2 *)(puVar7 + 0x461e) = 0xffff;
    *(short *)(puVar7 + 0x4620) = sVar2;
    *(undefined2 *)(puVar7 + 0x4622) = 0xffff;
    *(undefined2 *)(puVar7 + 0x4624) = 0xffff;
    *(undefined4 *)(puVar7 + 0x4600) = 0;
    puVar8[0x678b] = '?' - (char)sVar1;
    puVar8 = puVar8 + 8;
    *(undefined4 *)(puVar7 + 0x468c) = 0;
    *(undefined2 *)(puVar7 + 0x46b2) = 0xffff;
    *(short *)(puVar7 + 0x46b4) = sVar1;
    *(undefined2 *)(puVar7 + 0x46b6) = 0xffff;
    *(undefined2 *)(puVar7 + 0x46b8) = 0xffff;
    *(undefined4 *)(puVar7 + 0x4694) = 0;
    puVar7 = puVar7 + 0x4a0;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  sVar6 = 0;
  puVar7 = &DAT_803cd2e8;
  DAT_803d3a68 = 0x40;
  iVar11 = 8;
  puVar8 = puVar7;
  do {
    sVar9 = sVar6 + 1;
    puVar7[0x4240] = '?' - (char)sVar6;
    puVar8[0x2b38] = 0;
    sVar10 = sVar6 + 2;
    sVar5 = sVar6 + 3;
    *(undefined2 *)(puVar8 + 0x2b46) = 0xffff;
    sVar4 = sVar6 + 4;
    sVar3 = sVar6 + 5;
    *(short *)(puVar8 + 0x2b48) = sVar6;
    sVar2 = sVar6 + 6;
    *(undefined2 *)(puVar8 + 0x2b4a) = 0xffff;
    sVar1 = sVar6 + 7;
    sVar6 = sVar6 + 8;
    *(undefined2 *)(puVar8 + 0x2b4c) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2b4e) = 0xffff;
    puVar7[0x4241] = '?' - (char)sVar9;
    puVar8[0x2b94] = 0;
    *(undefined2 *)(puVar8 + 0x2ba2) = 0xffff;
    *(short *)(puVar8 + 0x2ba4) = sVar9;
    *(undefined2 *)(puVar8 + 0x2ba6) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2ba8) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2baa) = 0xffff;
    puVar7[0x4242] = '?' - (char)sVar10;
    puVar8[0x2bf0] = 0;
    *(undefined2 *)(puVar8 + 0x2bfe) = 0xffff;
    *(short *)(puVar8 + 0x2c00) = sVar10;
    *(undefined2 *)(puVar8 + 0x2c02) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2c04) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2c06) = 0xffff;
    puVar7[0x4243] = '?' - (char)sVar5;
    puVar8[0x2c4c] = 0;
    *(undefined2 *)(puVar8 + 0x2c5a) = 0xffff;
    *(short *)(puVar8 + 0x2c5c) = sVar5;
    *(undefined2 *)(puVar8 + 0x2c5e) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2c60) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2c62) = 0xffff;
    puVar7[0x4244] = '?' - (char)sVar4;
    puVar8[0x2ca8] = 0;
    *(undefined2 *)(puVar8 + 0x2cb6) = 0xffff;
    *(short *)(puVar8 + 0x2cb8) = sVar4;
    *(undefined2 *)(puVar8 + 0x2cba) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2cbc) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2cbe) = 0xffff;
    puVar7[0x4245] = '?' - (char)sVar3;
    puVar8[0x2d04] = 0;
    *(undefined2 *)(puVar8 + 0x2d12) = 0xffff;
    *(short *)(puVar8 + 0x2d14) = sVar3;
    *(undefined2 *)(puVar8 + 0x2d16) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2d18) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2d1a) = 0xffff;
    puVar7[0x4246] = '?' - (char)sVar2;
    puVar8[0x2d60] = 0;
    *(undefined2 *)(puVar8 + 0x2d6e) = 0xffff;
    *(short *)(puVar8 + 0x2d70) = sVar2;
    *(undefined2 *)(puVar8 + 0x2d72) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2d74) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2d76) = 0xffff;
    puVar7[0x4247] = '?' - (char)sVar1;
    puVar7 = puVar7 + 8;
    puVar8[0x2dbc] = 0;
    *(undefined2 *)(puVar8 + 0x2dca) = 0xffff;
    *(short *)(puVar8 + 0x2dcc) = sVar1;
    *(undefined2 *)(puVar8 + 0x2dce) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2dd0) = 0xffff;
    *(undefined2 *)(puVar8 + 0x2dd2) = 0xffff;
    puVar8 = puVar8 + 0x2e0;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  DAT_803d1524 = 0x40;
  DAT_803d1520 = 0xffff;
  DAT_803d1522 = 0xffff;
  DAT_803cf8e8 = 0;
  return;
}



// ==== 800ed4c4  zz_00ed4c4_ ====

void zz_00ed4c4_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_00ed570_();
  if (param_1 == iVar1) {
    return;
  }
  zz_010dc5c_(param_1);
  if (param_1 == 2) {
    iVar1 = 1;
    uVar2 = 2;
  }
  else {
    if (param_1 < 2) {
      if (param_1 == 0) {
        iVar1 = 0;
        uVar2 = 0;
        goto LAB_800ed53c;
      }
    }
    else if (param_1 < 4) {
      iVar1 = 2;
      uVar2 = 3;
      goto LAB_800ed53c;
    }
    iVar1 = 0;
    uVar2 = 1;
  }
LAB_800ed53c:
  zz_0217dc4_(iVar1);
  zz_021a50c_(uVar2);
  DAT_803cf900 = DAT_803cf900 | 2;
  return;
}



// ==== 800ed570  zz_00ed570_ ====

undefined4 zz_00ed570_(void)

{
  int iVar1;
  undefined4 unaff_r31;
  
  iVar1 = zz_021a514_();
  if (iVar1 == 2) {
    unaff_r31 = 2;
  }
  else if (iVar1 < 2) {
    if (iVar1 == 0) {
      unaff_r31 = 0;
    }
    else if (-1 < iVar1) {
      unaff_r31 = 1;
    }
  }
  else if (iVar1 < 4) {
    unaff_r31 = 3;
  }
  return unaff_r31;
}



// ==== 800ed5e0  zz_00ed5e0_ ====

void zz_00ed5e0_(int param_1,int param_2,uint param_3)

{
  if (param_3 == (byte)(&DAT_803cd300)[param_1 * 0x98 + param_2]) {
    return;
  }
  (&DAT_803cd300)[param_1 * 0x98 + param_2] = (byte)param_3;
  DAT_803cf900 = DAT_803cf900 | 1;
  return;
}



// ==== 800ed614  zz_00ed614_ ====

undefined4 zz_00ed614_(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_803cf914;
  if (0x1f < DAT_803cf914) {
    return 0xffffffff;
  }
  *param_1 = *param_1 & 0xffffff;
  *param_1 = *param_1 | 0x60000000;
  uVar2 = param_1[1];
  (&DAT_803cf918)[iVar1 * 4] = *param_1;
  (&DAT_803cf91c)[iVar1 * 4] = uVar2;
  uVar2 = param_1[3];
  (&DAT_803cf920)[iVar1 * 4] = param_1[2];
  (&DAT_803cf924)[iVar1 * 4] = uVar2;
  DAT_803cf914 = DAT_803cf914 + 1;
  return 0;
}



// ==== 800ed684  zz_00ed684_ ====

undefined4 zz_00ed684_(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_803cf914;
  if (0x1f < DAT_803cf914) {
    return 0xffffffff;
  }
  *param_1 = *param_1 & 0xfffffff;
  *param_1 = *param_1 | 0x30000000;
  uVar2 = param_1[1];
  (&DAT_803cf918)[iVar1 * 4] = *param_1;
  (&DAT_803cf91c)[iVar1 * 4] = uVar2;
  uVar2 = param_1[3];
  (&DAT_803cf920)[iVar1 * 4] = param_1[2];
  (&DAT_803cf924)[iVar1 * 4] = uVar2;
  DAT_803cf914 = DAT_803cf914 + 1;
  return 0;
}



// ==== 800ed6f4  zz_00ed6f4_ ====

undefined4 zz_00ed6f4_(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_803cf914;
  if (0x1f < DAT_803cf914) {
    return 0xffffffff;
  }
  *param_1 = *param_1 & 0xfffffff;
  *param_1 = *param_1 | 0x40000000;
  uVar2 = param_1[1];
  (&DAT_803cf918)[iVar1 * 4] = *param_1;
  (&DAT_803cf91c)[iVar1 * 4] = uVar2;
  uVar2 = param_1[3];
  (&DAT_803cf920)[iVar1 * 4] = param_1[2];
  (&DAT_803cf924)[iVar1 * 4] = uVar2;
  DAT_803cf914 = DAT_803cf914 + 1;
  return 0;
}



// ==== 800ed764  zz_00ed764_ ====

undefined4 zz_00ed764_(uint *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_803cf914;
  if (0x1f < DAT_803cf914) {
    return 0xffffffff;
  }
  *param_1 = *param_1 & 0xfffffff;
  *param_1 = *param_1 | 0x50000000;
  uVar2 = param_1[1];
  (&DAT_803cf918)[iVar1 * 4] = *param_1;
  (&DAT_803cf91c)[iVar1 * 4] = uVar2;
  uVar2 = param_1[3];
  (&DAT_803cf920)[iVar1 * 4] = param_1[2];
  (&DAT_803cf924)[iVar1 * 4] = uVar2;
  DAT_803cf914 = DAT_803cf914 + 1;
  return 0;
}



// ==== 800ed7d4  zz_00ed7d4_ ====

undefined4 zz_00ed7d4_(uint param_1,uint param_2,int param_3)

{
  undefined *puVar1;
  int iVar2;
  
  if (param_3 == 6) {
    puVar1 = &DAT_803cd2e8;
    if (DAT_803cf914 != 0) {
      for (iVar2 = 0; iVar2 < DAT_803cf914; iVar2 = iVar2 + 1) {
        if ((*(uint *)(puVar1 + 0x2630) & 0x7f7f00) == (param_1 & 0x7f7f00)) {
          *(undefined4 *)(puVar1 + 0x2630) = 0x80000000;
        }
        puVar1 = puVar1 + 0x10;
      }
      if (0x1f < DAT_803cf914) {
        return 0xffffffff;
      }
    }
    iVar2 = DAT_803cf914 * 4;
    DAT_803cf914 = DAT_803cf914 + 1;
    (&DAT_803cf918)[iVar2] = (param_2 | 6) << 0x18 | param_1 & 0x7f7f7f;
  }
  else {
    if (param_3 < 6) {
      if (param_3 == 4) {
        puVar1 = &DAT_803cd2e8;
        if (DAT_803cf914 != 0) {
          for (iVar2 = 0; iVar2 < DAT_803cf914; iVar2 = iVar2 + 1) {
            if ((*(uint *)(puVar1 + 0x2630) & 0x7f0000) == (param_1 & 0x7f0000)) {
              *(undefined4 *)(puVar1 + 0x2630) = 0x80000000;
            }
            puVar1 = puVar1 + 0x10;
          }
          if (0x1f < DAT_803cf914) {
            return 0xffffffff;
          }
        }
        iVar2 = DAT_803cf914 * 4;
        DAT_803cf914 = DAT_803cf914 + 1;
        (&DAT_803cf918)[iVar2] = (param_2 | 4) << 0x18 | param_1 & 0x7f7f7f;
        return 0;
      }
    }
    else if (param_3 < 8) {
      puVar1 = &DAT_803cd2e8;
      if (DAT_803cf914 != 0) {
        for (iVar2 = 0; iVar2 < DAT_803cf914; iVar2 = iVar2 + 1) {
          if ((*(uint *)(puVar1 + 0x2630) & 0x7f7f7f) == (param_1 & 0x7f7f7f)) {
            *(undefined4 *)(puVar1 + 0x2630) = 0x80000000;
          }
          puVar1 = puVar1 + 0x10;
        }
        if (0x1f < DAT_803cf914) {
          return 0xffffffff;
        }
      }
      iVar2 = DAT_803cf914 * 4;
      DAT_803cf914 = DAT_803cf914 + 1;
      (&DAT_803cf918)[iVar2] = (param_2 | 7) << 0x18 | param_1 & 0x7f7f7f;
      return 0;
    }
    puVar1 = &DAT_803cd2e8;
    if (DAT_803cf914 == 0) {
      DAT_803cf914 = 1;
      DAT_803cf918 = param_2 << 0x18;
    }
    else {
      for (iVar2 = 0; iVar2 < DAT_803cf914; iVar2 = iVar2 + 1) {
        *(undefined4 *)(puVar1 + 0x2630) = 0x80000000;
        puVar1 = puVar1 + 0x10;
      }
      (&DAT_803cf908)[iVar2 * 4] = param_2 << 0x18;
    }
  }
  return 0;
}



// ==== 800eda40  zz_00eda40_ ====

void zz_00eda40_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined *param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  
  if (DAT_803cf8e8 == '\0') {
    DAT_803cf8e8 = 1;
    if (DAT_803cfb18 != DAT_803cfb1c) {
      param_1 = zz_00ee800_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    uVar4 = zz_00ed570_();
    DAT_803cf8ee = (undefined1)uVar4;
    sVar5 = DAT_803d1520;
    while (sVar5 != -1) {
      iVar1 = (int)sVar5;
      iVar2 = iVar1 * 0x5c;
      (&DAT_803cfe23)[iVar2] = 1;
      *(undefined2 *)(&DAT_803cfe52 + iVar2) = DAT_803cf900;
      sVar5 = *(short *)(&DAT_803cfe2c + iVar2);
      if (sVar5 == 2) {
LAB_800edb74:
        if ((*(int *)(&DAT_803cfe28 + iVar2) == 0x10) || (*(int *)(&DAT_803cfe28 + iVar2) == 0x20))
        {
          (&DAT_803cfe21)[iVar2] = 1;
          *(undefined2 *)(&DAT_803cfe2c + iVar2) = 3;
          *(undefined4 *)(&DAT_803cfe24 + iVar2) = *(undefined4 *)(&DAT_803cfe28 + iVar2);
        }
LAB_800edba0:
        sVar5 = (&DAT_803cfe34)[iVar1 * 0x2e];
        *(undefined2 *)(&DAT_803cfe7a + iVar2) = 0;
        while (sVar5 != -1) {
          iVar3 = (int)sVar5;
          sVar5 = (&DAT_803d1592)[iVar3 * 0x4a];
          if ((&DAT_803d158c)[iVar3 * 0x94] == '\0') {
            *(short *)(&DAT_803cfe7a + iVar2) = *(short *)(&DAT_803cfe7a + iVar2) + 1;
          }
          else {
            param_1 = zz_00ef070_((&DAT_803cfe30)[iVar1 * 0x2e],(&DAT_803d1590)[iVar3 * 0x4a]);
          }
        }
        if ((&DAT_803cfe34)[iVar1 * 0x2e] == -1) {
          (&DAT_803cfe22)[iVar2] = 1;
        }
      }
      else if (sVar5 < 2) {
        if (sVar5 == 0) {
          if ((*(int *)(&DAT_803cfe28 + iVar2) == 0x10) || (*(int *)(&DAT_803cfe28 + iVar2) == 0x20)
             ) {
            (&DAT_803cfe21)[iVar2] = 1;
            *(undefined2 *)(&DAT_803cfe2c + iVar2) = 3;
            *(undefined4 *)(&DAT_803cfe28 + iVar2) = 0x10;
            *(undefined4 *)(&DAT_803cfe24 + iVar2) = 0x10;
          }
          else {
            param_1 = zz_00edc60_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  (int)(&DAT_803cfe20 + iVar2),1,param_11,param_12,param_13,param_14
                                  ,param_15,param_16);
            if (*(short *)(&DAT_803cfe5a + iVar2) == 0) {
              *(undefined2 *)(&DAT_803cfe2c + iVar2) = 2;
            }
            else {
              *(undefined2 *)(&DAT_803cfe2c + iVar2) = 1;
            }
          }
        }
        else if (-1 < sVar5) {
          *(short *)(&DAT_803cfe5a + iVar2) = *(short *)(&DAT_803cfe5a + iVar2) + -4;
          if (*(short *)(&DAT_803cfe5a + iVar2) < 1) {
            (&DAT_803cfe21)[iVar2] = 1;
            *(undefined2 *)(&DAT_803cfe2c + iVar2) = 3;
            *(undefined4 *)(&DAT_803cfe28 + iVar2) = 0x20;
            *(undefined4 *)(&DAT_803cfe24 + iVar2) = 0x20;
          }
          goto LAB_800edb74;
        }
      }
      else if (sVar5 < 4) goto LAB_800edba0;
      (&DAT_803cfe23)[iVar2] = 0;
      sVar5 = (&DAT_803cfe32)[iVar1 * 0x2e];
      if ((&DAT_803cfe22)[iVar2] != '\0') {
        param_1 = zz_00ef28c_((&DAT_803cfe30)[iVar1 * 0x2e]);
      }
    }
    DAT_803cf900 = 0;
    DAT_803cf8e8 = '\0';
  }
  return;
}



// ==== 800edc60  zz_00edc60_ ====

void zz_00edc60_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined *param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  undefined1 *puVar7;
  uint uVar8;
  uint uVar9;
  int *piVar10;
  
  uVar8 = (uint)*(byte *)(param_9 + 0x38);
  iVar1 = (uint)*(byte *)(param_9 + 0x35) * 0x98;
  iVar6 = *(int *)(&DAT_803cd2ec + iVar1);
  if (*(uint *)(iVar6 + 8) < uVar8) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_802b1d94,
                     iVar6,uVar8,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 2) = 1;
  }
  else {
    iVar2 = *(int *)(iVar6 + uVar8 * 4 + 0x10);
    if (iVar2 == -1) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_802b1db8
                       ,iVar6,uVar8,param_12,param_13,param_14,param_15,param_16);
      *(undefined1 *)(param_9 + 2) = 1;
    }
    else {
      *(int *)(param_9 + 0x18) = iVar6 + iVar2;
      iVar2 = 0;
      for (iVar6 = 0; iVar6 < (int)(uint)**(byte **)(param_9 + 0x18); iVar6 = iVar6 + 1) {
        *(byte **)(param_9 + 0x1c) = *(byte **)(param_9 + 0x18) + iVar2 + 8;
        iVar3 = *(int *)(param_9 + 0x1c);
        uVar9 = uVar8;
        if ((*(byte *)(iVar3 + 2) <= *(byte *)(param_9 + 0x39)) &&
           (*(byte *)(param_9 + 0x39) <= *(byte *)(iVar3 + 3))) {
          if ((uint)*(ushort *)(iVar3 + 0xc) <= *(uint *)(*(int *)(&DAT_803cd2f0 + iVar1) + 8)) {
            *(uint *)(param_9 + 0x20) =
                 *(int *)(&DAT_803cd2f0 + iVar1) + (uint)*(ushort *)(iVar3 + 0xc) * 0xc + 0x10;
            iVar3 = *(int *)(&DAT_803cd2f4 + iVar1);
            uVar4 = (uint)*(ushort *)(*(int *)(param_9 + 0x20) + 10);
            if (uVar4 <= *(uint *)(iVar3 + 8)) {
              *(uint *)(param_9 + 0x24) = iVar3 + uVar4 * 100 + 0x10;
              uVar4 = zz_00eef60_(*(short *)(param_9 + 0x10));
              uVar9 = (uint)(short)uVar4;
              if ((int)uVar9 < 0) {
                param_1 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                           param_8,&DAT_802b1de4,iVar3,uVar8,param_12,param_13,
                                           param_14,param_15,param_16);
                uVar9 = uVar8;
              }
              else {
                param_12 = &DAT_803cd2e8 + uVar9 * 0x94;
                puVar7 = &LAB_800ede48;
                piVar10 = &DAT_803d1568 + uVar9 * 0x25;
                piVar5 = zz_02170a8_((uint)**(byte **)(param_9 + 0x1c),-0x7ff121b8,uVar9);
                *piVar10 = (int)piVar5;
                if (*piVar10 == 0) {
                  gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_802b1e10,puVar7,uVar9,param_12,param_13,param_14,param_15,
                                   param_16);
                  param_1 = zz_00ef070_(*(short *)(param_9 + 0x10),(short)uVar4);
                }
                else {
                  *(short *)(param_9 + 0x58) = *(short *)(param_9 + 0x58) + 1;
                  uVar9 = (uint)*(short *)(param_9 + 0x5a);
                  *(short *)(param_9 + 0x5a) = *(short *)(param_9 + 0x5a) + 1;
                  param_1 = zz_00ede6c_(param_9,piVar10);
                }
              }
            }
          }
        }
        iVar2 = iVar2 + 0xe;
        uVar8 = uVar9;
      }
    }
  }
  return;
}



// ==== 800ede6c  zz_00ede6c_ ====

void zz_00ede6c_(int param_1,int *param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined2 local_58;
  undefined2 local_56;
  undefined2 local_54;
  short local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  int local_48;
  int local_44;
  undefined2 local_40;
  undefined2 local_3e;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  undefined4 local_18;
  int iStack_14;
  
  fVar2 = FLOAT_8043900c;
  fVar1 = FLOAT_80439008;
  piVar3 = *(int **)(param_1 + 0x24);
  local_50 = *(short *)(piVar3 + 4);
  local_4e = *(undefined2 *)((int)piVar3 + 0x12);
  local_44 = DAT_803cf8fc +
             *(int *)(&DAT_803cd2f8 + (uint)*(byte *)(param_1 + 0x35) * 0x98) + *piVar3;
  if (local_50 == 0) {
    iVar5 = DAT_803cf8f8 * 2 + 2;
  }
  else {
    local_58 = *(undefined2 *)(piVar3 + 0x12);
    local_56 = *(undefined2 *)((int)piVar3 + 0x4a);
    local_54 = *(undefined2 *)(piVar3 + 0x13);
    iVar5 = piVar3[5] + local_44 * 2;
  }
  local_4c = (undefined2)((uint)iVar5 >> 0x10);
  local_44 = local_44 * 2;
  local_4a = (undefined2)iVar5;
  local_18 = 0x43300000;
  local_48 = piVar3[6] + local_44;
  local_44 = piVar3[7] + local_44;
  local_40 = *(undefined2 *)(piVar3 + 8);
  local_3e = *(undefined2 *)((int)piVar3 + 0x22);
  local_3c = *(undefined2 *)(piVar3 + 9);
  local_3a = *(undefined2 *)((int)piVar3 + 0x26);
  local_38 = *(undefined2 *)(piVar3 + 10);
  local_36 = *(undefined2 *)((int)piVar3 + 0x2a);
  local_34 = *(undefined2 *)(piVar3 + 0xb);
  local_32 = *(undefined2 *)((int)piVar3 + 0x2e);
  local_30 = *(undefined2 *)(piVar3 + 0xc);
  local_2e = *(undefined2 *)((int)piVar3 + 0x32);
  local_2c = *(undefined2 *)(piVar3 + 0xd);
  local_2a = *(undefined2 *)((int)piVar3 + 0x36);
  local_28 = *(undefined2 *)(piVar3 + 0xe);
  local_26 = *(undefined2 *)((int)piVar3 + 0x3a);
  local_24 = *(undefined2 *)(piVar3 + 0xf);
  local_22 = *(undefined2 *)((int)piVar3 + 0x3e);
  local_20 = *(undefined2 *)(piVar3 + 0x10);
  local_1e = *(undefined2 *)((int)piVar3 + 0x42);
  local_1c = *(undefined2 *)(piVar3 + 0x11);
  local_1a = *(undefined2 *)((int)piVar3 + 0x46);
  iStack_14 = piVar3[3];
  param_2[0x16] = (int)(float)((double)CONCAT44(0x43300000,iStack_14) - DOUBLE_80439010);
  iVar5 = gnt4___cvt_fp2unsigned_bl((double)(fVar1 * ((float)param_2[0x16] / fVar2)));
  *(short *)(param_2 + 0x17) = (short)((uint)iVar5 >> 0x10);
  *(short *)((int)param_2 + 0x5e) = (short)iVar5;
  *(undefined2 *)(param_2 + 0x18) = 0;
  *(undefined2 *)((int)param_2 + 0x62) = 0;
  *(undefined2 *)(param_2 + 0x19) = 0;
  *(undefined2 *)((int)param_2 + 0x66) = 0;
  *(undefined2 *)(param_2 + 0x1a) = 0;
  zz_021962c_(*param_2,1);
  zz_0219bf8_(*param_2,(undefined2 *)(param_2 + 0x17));
  zz_021974c_(*param_2,0);
  zz_0219a44_(*param_2,(undefined4 *)&local_50);
  zz_0219b54_(*param_2,(undefined4 *)&local_40);
  zz_0219d28_(*param_2,&local_58);
  gnt4_memset((void *)((int)param_2 + 0x6a),0,0x24);
  *(undefined2 *)((int)param_2 + 0x8e) = 0;
  *(undefined2 *)(param_2 + 0x24) = 0;
  iVar5 = zz_00ee19c_(param_1);
  *(char *)((int)param_2 + 0x32) = (char)iVar5;
  uVar4 = zz_00ee614_(param_1);
  *(char *)((int)param_2 + 0x33) = (char)uVar4;
  iVar5 = zz_00ee6a4_(param_1);
  param_2[0xd] = iVar5;
  iVar5 = zz_00ee11c_(param_1,0);
  *(short *)(param_2 + 0xe) = (short)iVar5;
  iVar5 = zz_00ee11c_(param_1,1);
  *(short *)(param_2 + 0x10) = (short)iVar5;
  *(undefined2 *)(param_2 + 0x12) = *(undefined2 *)(*(int *)(param_1 + 0x1c) + 4);
  *(undefined2 *)((int)param_2 + 0x4a) = *(undefined2 *)(*(int *)(param_1 + 0x1c) + 6);
  param_2[1] = *(int *)(param_1 + 0x20);
  param_2[2] = 0;
  return;
}



// ==== 800ee11c  zz_00ee11c_ ====

int zz_00ee11c_(int param_1,int param_2)

{
  if (param_2 != 0) {
    return (int)(((int)((*(byte *)(*(int *)(param_1 + 0x18) + 1) & 0xf) * 0x7fff) >> 4) *
                (*(byte *)(*(int *)(param_1 + 0x1c) + 1) & 0xf)) >> 4;
  }
  return (int)(((int)((uint)(*(byte *)(*(int *)(param_1 + 0x18) + 1) >> 4) * 0x7fff) >> 4) *
              (uint)(*(byte *)(*(int *)(param_1 + 0x1c) + 1) >> 4)) >> 4;
}



// ==== 800ee19c  zz_00ee19c_ ====

int zz_00ee19c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x18) + 2)) -
                 DOUBLE_80439010);
  if (FLOAT_8043901c == fVar1) {
    fVar1 = FLOAT_80439018;
  }
  fVar2 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x1c) + 8)) -
                 DOUBLE_80439010);
  if (FLOAT_8043901c == fVar2) {
    fVar2 = FLOAT_80439018;
  }
  fVar3 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x20) + 6)) -
                 DOUBLE_80439010);
  if (FLOAT_8043901c == fVar3) {
    fVar3 = FLOAT_80439018;
  }
  return (int)((((fVar1 / FLOAT_80439018) * fVar2) / FLOAT_80439018) * fVar3);
}



// ==== 800ee258  zz_00ee258_ ====

void zz_00ee258_(int param_1)

{
  double dVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80439020;
  dVar1 = DOUBLE_80439010;
  *(float *)(param_1 + 0x40) =
       (float)((double)CONCAT44(0x43300000,
                                (uint)(byte)(&DAT_803cd300)
                                            [(uint)*(byte *)(param_1 + 0x35) * 0x98 +
                                             (uint)*(byte *)(param_1 + 0x38)]) - DOUBLE_80439010);
  *(float *)(param_1 + 0x44) =
       (float)((double)CONCAT44(0x43300000,
                                (uint)(byte)(&DAT_803cd2ff)[(uint)*(byte *)(param_1 + 0x35) * 0x98])
              - dVar1);
  *(float *)(param_1 + 0x48) =
       (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(param_1 + 0x28)) - dVar1);
  *(float *)(param_1 + 0x4c) = (float)((double)CONCAT44(0x43300000,(uint)DAT_803cf8ec) - dVar1);
  *(float *)(param_1 + 0x50) = (float)((double)CONCAT44(0x43300000,(uint)DAT_803cf8ed) - dVar1);
  *(float *)(param_1 + 0x54) =
       (float)((double)CONCAT44(0x43300000,(uint)(int)DAT_803cf8ea >> 6 & 0x7f ^ 0x80000000) - dVar2
              );
  return;
}



// ==== 800ee330  zz_00ee330_ ====

int zz_00ee330_(int param_1,uint param_2)

{
  return (int)(((((((((((((float)((double)CONCAT44(0x43300000,param_2 & 0xff) - DOUBLE_80439010) /
                         FLOAT_80439018) * *(float *)(param_1 + 0x40)) / FLOAT_80439018) *
                      *(float *)(param_1 + 0x44)) / FLOAT_80439018) * *(float *)(param_1 + 0x48)) /
                   FLOAT_80439018) * *(float *)(param_1 + 0x4c)) / FLOAT_80439018) *
                *(float *)(param_1 + 0x50)) / FLOAT_80439018) * *(float *)(param_1 + 0x54));
}



// ==== 800ee3b0  zz_00ee3b0_ ====

/* WARNING: Removing unreachable block (ram,0x800ee3d0) */

void zz_00ee3b0_(int param_1)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if (DAT_803cf8ee == '\x01') {
    bVar1 = *(byte *)(param_1 + 0x2f);
    if ((bVar1 & 0x40) == 0) {
      *(short *)(param_1 + 0x6e) = (short)((int)((uint)bVar1 << 0xe) >> 6);
    }
    else {
      uVar3 = bVar1 - 0x40;
      uVar2 = uVar3 * 0x4000;
      iVar4 = (int)uVar2 / 0x3f + ((int)(uVar2 | uVar3 >> 0x12) >> 0x1f);
      *(short *)(param_1 + 0x6e) = ((short)iVar4 - (short)(iVar4 >> 0x1f)) + 0x4000;
    }
    *(short *)(param_1 + 0x6a) = -0x8000 - *(short *)(param_1 + 0x6e);
  }
  else if (DAT_803cf8ee == '\0') {
    *(undefined2 *)(param_1 + 0x6e) = 0x4000;
    *(undefined2 *)(param_1 + 0x6a) = 0x4000;
  }
  *(short *)(param_1 + 0x72) =
       (short)(((((((((uint)*(ushort *)(param_1 + 0x6a) * (uint)*(ushort *)(param_1 + 0x38)) /
                    0x7fff) * (uint)*(ushort *)(param_1 + 0x3a)) / 0x7fff) *
                 (uint)*(ushort *)(param_1 + 0x3c)) / 0x7fff) * (uint)*(ushort *)(param_1 + 0x3e)) /
              0x7fff);
  *(short *)(param_1 + 0x76) =
       (short)(((((((((uint)*(ushort *)(param_1 + 0x6e) * (uint)*(ushort *)(param_1 + 0x38)) /
                    0x7fff) * (uint)*(ushort *)(param_1 + 0x3a)) / 0x7fff) *
                 (uint)*(ushort *)(param_1 + 0x3c)) / 0x7fff) * (uint)*(ushort *)(param_1 + 0x3e)) /
              0x7fff);
  *(short *)(param_1 + 0x7a) =
       (short)(((((((((uint)*(ushort *)(param_1 + 0x6a) * (uint)*(ushort *)(param_1 + 0x40)) /
                    0x7fff) * (uint)*(ushort *)(param_1 + 0x42)) / 0x7fff) *
                 (uint)*(ushort *)(param_1 + 0x44)) / 0x7fff) * (uint)*(ushort *)(param_1 + 0x46)) /
              0x7fff);
  *(short *)(param_1 + 0x7e) =
       (short)(((((((((uint)*(ushort *)(param_1 + 0x6e) * (uint)*(ushort *)(param_1 + 0x40)) /
                    0x7fff) * (uint)*(ushort *)(param_1 + 0x42)) / 0x7fff) *
                 (uint)*(ushort *)(param_1 + 0x44)) / 0x7fff) * (uint)*(ushort *)(param_1 + 0x46)) /
              0x7fff);
  return;
}



// ==== 800ee614  zz_00ee614_ ====

uint zz_00ee614_(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = (uint)*(byte *)(*(int *)(param_1 + 0x1c) + 9) +
          (uint)*(byte *)(*(int *)(param_1 + 0x18) + 3) + -0x80;
  if (iVar1 < -0x40) {
    iVar1 = -0x40;
  }
  if (0x3f < iVar1) {
    iVar1 = 0x3f;
  }
  uVar2 = iVar1 + (uint)*(byte *)(*(int *)(param_1 + 0x20) + 7);
  if ((int)uVar2 < 0) {
    uVar2 = 0;
  }
  if (0x7f < (int)uVar2) {
    uVar2 = 0x7f;
  }
  return uVar2 & 0xff;
}



// ==== 800ee66c  zz_00ee66c_ ====

uint zz_00ee66c_(int param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (uint)*(byte *)(param_1 + 0x29);
  if (uVar1 == 0xff) {
    uVar1 = 0x40;
  }
  uVar1 = (uVar1 + (param_2 & 0xff)) - 0x40;
  if ((int)uVar1 < 0) {
    uVar1 = 0;
  }
  if (0x7f < (int)uVar1) {
    uVar1 = 0x7f;
  }
  return uVar1 & 0xff;
}



// ==== 800ee6a4  zz_00ee6a4_ ====

int zz_00ee6a4_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x20);
  return (int)*(char *)(iVar1 + 9) +
         *(char *)(iVar1 + 8) * 100 +
         (int)*(char *)(*(int *)(param_1 + 0x1c) + 0xb) +
         *(char *)(*(int *)(param_1 + 0x1c) + 10) * 100 +
         (int)*(char *)(*(int *)(param_1 + 0x18) + 5) +
         *(char *)(*(int *)(param_1 + 0x18) + 4) * 100 +
         ((uint)*(byte *)(param_1 + 0x39) - (uint)*(byte *)(iVar1 + 5)) * 100;
}



// ==== 800ee71c  zz_00ee71c_ ====

void zz_00ee71c_(int param_1,uint param_2)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  dVar2 = DOUBLE_80439038;
  dVar3 = DOUBLE_80439030;
  if ((param_2 & 0x2000) == 0) {
    fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(param_1 + 0x48)) - DOUBLE_80439010
                   ) / FLOAT_8043902c;
  }
  else {
    fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(ushort *)(param_1 + 0x4a)) - DOUBLE_80439010
                   ) / FLOAT_80439028;
  }
  *(float *)(param_1 + 0x50) =
       fVar1 * (float)((double)CONCAT44(0x43300000,(param_2 & 0xffff) - 0x2000 ^ 0x80000000) -
                      DOUBLE_80439020) +
       (float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x34) ^ 0x80000000) - DOUBLE_80439020
              );
  dVar3 = (double)gnt4_pow_bl(dVar3,(double)*(float *)(param_1 + 0x50) / dVar2);
  *(float *)(param_1 + 0x54) = (float)((double)*(float *)(param_1 + 0x58) * dVar3);
  return;
}



// ==== 800ee800  zz_00ee800_ ====

void zz_00ee800_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short sVar10;
  uint *puVar11;
  
  iVar1 = DAT_803cfb1c;
  for (iVar7 = DAT_803cfb18; iVar7 != iVar1; iVar7 = iVar7 + (iVar3 - (iVar3 >> 0x1f)) * -0x30) {
    iVar3 = iVar7 * 0x10;
    puVar11 = (uint *)(&DAT_803cfb20 + iVar3);
    uVar4 = *puVar11;
    uVar2 = uVar4 >> 0x18 & 0x70;
    if (uVar2 == 0x40) {
      zz_00eee10_(uVar4,(&DAT_803cfb28)[iVar3],(&DAT_803cfb29)[iVar3],
                  *(short *)(&DAT_803cfb2a + iVar3));
    }
    else if (uVar2 < 0x40) {
      if (uVar2 == 0x20) {
        param_1 = zz_00eec5c_(uVar4,0x20);
      }
      else if (uVar2 < 0x20) {
        if (uVar2 == 0x10) {
          param_1 = zz_00eec5c_(uVar4,0x10);
        }
      }
      else if (uVar2 == 0x30) {
        param_1 = zz_00eed24_(puVar11,0x20);
      }
    }
    else if ((uVar2 == 0x60) ||
            (((uVar2 < 0x60 && (uVar2 == 0x50)) &&
             (iVar5 = zz_00eee10_(uVar4,(&DAT_803cfb28)[iVar3],(&DAT_803cfb29)[iVar3],
                                  *(short *)(&DAT_803cfb2a + iVar3)), iVar5 == 0)))) {
      uVar8 = *puVar11;
      uVar9 = (uint)(byte)(&DAT_803cfb2d)[iVar3];
      uVar6 = uVar8 >> 8 & 0x7f;
      uVar4 = uVar8 >> 7 & 1 | uVar8 >> 0x15 & 4 | uVar8 >> 0xe & 2;
      uVar2 = uVar8 & 0x7f;
      iVar3 = zz_00eeaa8_(uVar8 >> 0x10 & 0x7f,uVar6,uVar2,(byte)uVar4,(&DAT_803cfb2d)[iVar3]);
      if (iVar3 == 0) {
        uVar8 = zz_00ef1a8_();
        sVar10 = (short)uVar8;
        if (sVar10 < 0) {
          param_1 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_802b1e3c,uVar6,uVar2,uVar4,uVar9,in_r8,in_r9,in_r10);
        }
        else {
          iVar3 = sVar10 * 0x5c;
          zz_00ee9ac_(&DAT_803cfe20 + iVar3,puVar11);
          in_r8 = 0x10;
          param_1 = zz_00eeb84_(sVar10,(uint)(byte)(&DAT_803cfe55)[iVar3],
                                (uint)(byte)(&DAT_803cfe56)[iVar3],
                                (uint)(byte)(&DAT_803cfe57)[iVar3],(&DAT_803cfe54)[iVar3],0x10);
        }
      }
    }
    iVar7 = iVar7 + 1;
    iVar3 = iVar7 / 0x30 + (iVar7 >> 0x1f);
  }
  DAT_803cfb18 = iVar7;
  return;
}



// ==== 800ee9ac  zz_00ee9ac_ ====

void zz_00ee9ac_(undefined1 *param_1,uint *param_2)

{
  uint uVar1;
  
  *param_1 = 1;
  param_1[1] = 0;
  param_1[2] = 0;
  *(undefined2 *)(param_1 + 0xc) = 0;
  *(undefined2 *)(param_1 + 0x30) = 0xffff;
  *(undefined4 *)(param_1 + 4) = 0x60;
  *(undefined4 *)(param_1 + 8) = 0x60;
  param_1[0x28] = *(undefined1 *)(param_2 + 2);
  param_1[0x29] = *(undefined1 *)((int)param_2 + 9);
  *(undefined2 *)(param_1 + 0x2a) = *(undefined2 *)((int)param_2 + 10);
  *(undefined2 *)(param_1 + 0x2c) = 0x7fff;
  *(undefined2 *)(param_1 + 0x2e) = 0x7fff;
  uVar1 = *param_2;
  param_1[0x34] = (byte)(uVar1 >> 7) & 1 | (byte)(uVar1 >> 0x15) & 4 | (byte)(uVar1 >> 0xe) & 2;
  param_1[0x35] = (byte)(*param_2 >> 0x10) & 0x7f;
  param_1[0x36] = (byte)(*param_2 >> 8) & 0x7f;
  param_1[0x37] = (byte)*param_2 & 0x7f;
  param_1[0x38] = *(char *)(param_2 + 1) + *(char *)(param_2 + 3);
  param_1[0x39] = *(undefined1 *)((int)param_2 + 5);
  param_1[0x3c] = *(undefined1 *)((int)param_2 + 0xd);
  *(undefined2 *)(param_1 + 0x3a) = *(undefined2 *)((int)param_2 + 6);
  *(undefined2 *)(param_1 + 0x58) = 0;
  *(undefined2 *)(param_1 + 0x5a) = 0;
  if (param_1[0x28] == -1) {
    param_1[0x28] = 0x7f;
  }
  if (param_1[0x29] == -1) {
    param_1[0x29] = 0x40;
  }
  if (*(short *)(param_1 + 0x2a) != -1) {
    return;
  }
  *(undefined2 *)(param_1 + 0x2a) = 0x2000;
  return;
}



// ==== 800eeaa8  zz_00eeaa8_ ====

undefined4 zz_00eeaa8_(uint param_1,uint param_2,uint param_3,byte param_4,byte param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  
  if (param_4 == 0) {
    return 0;
  }
  iVar3 = (int)DAT_803d1520;
  uVar1 = countLeadingZeros(-1 - DAT_803d1522);
  uVar2 = countLeadingZeros(-1 - iVar3);
  if ((uVar2 >> 5) + (uVar1 >> 4 & 0xffffffe) == 0) {
    uVar1 = 0x7f0000;
    if ((param_4 & 1) != 0) {
      uVar1 = 0x7f007f;
    }
    if ((param_4 & 2) != 0) {
      uVar1 = uVar1 | 0x7f00;
    }
    while (sVar4 = (short)iVar3, sVar4 != -1) {
      iVar3 = sVar4 * 0x5c;
      if (((uVar1 & (param_3 & 0xff | (param_1 & 0xff) << 0x10 | (param_2 & 0xff) << 8)) ==
           (uVar1 & ((uint)(byte)(&DAT_803cfe57)[iVar3] |
                    (uint)(byte)(&DAT_803cfe55)[iVar3] << 0x10 |
                    (uint)(byte)(&DAT_803cfe56)[iVar3] << 8))) &&
         (param_5 < (byte)(&DAT_803cfe5c)[iVar3])) {
        return 1;
      }
      iVar3 = (int)(short)(&DAT_803cfe32)[sVar4 * 0x2e];
    }
  }
  return 0;
}



// ==== 800eeb84  zz_00eeb84_ ====

void zz_00eeb84_(short param_1,uint param_2,uint param_3,uint param_4,byte param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (param_5 == 0) {
    return;
  }
  iVar4 = (int)DAT_803d1520;
  uVar1 = countLeadingZeros(-1 - DAT_803d1522);
  uVar3 = countLeadingZeros(-1 - iVar4);
  if ((uVar3 >> 5) + (uVar1 >> 4 & 0xffffffe) != 0) {
    return;
  }
  uVar1 = 0x7f0000;
  if ((param_5 & 1) != 0) {
    uVar1 = 0x7f007f;
  }
  if ((param_5 & 2) != 0) {
    uVar1 = uVar1 | 0x7f00;
  }
  while ((short)iVar4 != -1) {
    iVar2 = (int)(short)iVar4;
    iVar4 = iVar2 * 0x5c;
    if (((iVar2 != param_1) &&
        ((uVar1 & (param_4 & 0xff | (param_2 & 0xff) << 0x10 | (param_3 & 0xff) << 8)) ==
         (uVar1 & ((uint)(byte)(&DAT_803cfe57)[iVar4] |
                  (uint)(byte)(&DAT_803cfe55)[iVar4] << 0x10 |
                  (uint)(byte)(&DAT_803cfe56)[iVar4] << 8)))) &&
       (param_6 < *(int *)(&DAT_803cfe28 + iVar4))) {
      *(int *)(&DAT_803cfe28 + iVar4) = param_6;
    }
    iVar4 = (int)(short)(&DAT_803cfe32)[iVar2 * 0x2e];
  }
  return;
}



// ==== 800eec5c  zz_00eec5c_ ====

void zz_00eec5c_(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  
  iVar3 = (int)DAT_803d1520;
  uVar1 = countLeadingZeros(-1 - DAT_803d1522);
  uVar2 = countLeadingZeros(-1 - iVar3);
  if ((uVar2 >> 5) + (uVar1 >> 4 & 0xffffffe) != 0) {
    return;
  }
  uVar1 = 0;
  if ((param_1 >> 0x18 & 1) != 0) {
    uVar1 = 0x7f;
  }
  if ((param_1 >> 0x18 & 2) != 0) {
    uVar1 = uVar1 | 0x7f00;
  }
  if ((param_1 >> 0x18 & 4) != 0) {
    uVar1 = uVar1 | 0x7f0000;
  }
  while (sVar4 = (short)iVar3, sVar4 != -1) {
    iVar3 = sVar4 * 0x5c;
    if (((param_1 & uVar1) ==
         (uVar1 & ((uint)(byte)(&DAT_803cfe57)[iVar3] |
                  (uint)(byte)(&DAT_803cfe55)[iVar3] << 0x10 |
                  (uint)(byte)(&DAT_803cfe56)[iVar3] << 8))) &&
       (param_2 < *(int *)(&DAT_803cfe28 + iVar3))) {
      *(int *)(&DAT_803cfe28 + iVar3) = param_2;
    }
    iVar3 = (int)(short)(&DAT_803cfe32)[sVar4 * 0x2e];
  }
  return;
}



// ==== 800eed24  zz_00eed24_ ====

void zz_00eed24_(uint *param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  short sVar6;
  
  iVar5 = (int)DAT_803d1520;
  uVar3 = countLeadingZeros(-1 - DAT_803d1522);
  uVar4 = countLeadingZeros(-1 - iVar5);
  if ((uVar4 >> 5) + (uVar3 >> 4 & 0xffffffe) != 0) {
    return;
  }
  uVar4 = *param_1;
  uVar3 = 0;
  if ((uVar4 >> 0x18 & 1) != 0) {
    uVar3 = 0x7f;
  }
  if ((uVar4 >> 0x18 & 2) != 0) {
    uVar3 = uVar3 | 0x7f7f00;
  }
  bVar1 = *(byte *)((int)param_1 + 5);
  bVar2 = *(byte *)(param_1 + 1);
  while (sVar6 = (short)iVar5, sVar6 != -1) {
    iVar5 = sVar6 * 0x5c;
    if (((((ushort)(uVar4 >> 0x10) & 0x7f) == (ushort)(byte)(&DAT_803cfe55)[iVar5]) &&
        ((uVar3 & (uVar4 & 0x7f | (uint)bVar2 << 0x10 | (uint)bVar1 << 8)) ==
         (uVar3 & ((uint)(byte)(&DAT_803cfe57)[iVar5] |
                  (uint)(byte)(&DAT_803cfe58)[iVar5] << 0x10 |
                  (uint)(byte)(&DAT_803cfe59)[iVar5] << 8)))) &&
       (param_2 < *(int *)(&DAT_803cfe28 + iVar5))) {
      *(int *)(&DAT_803cfe28 + iVar5) = param_2;
    }
    iVar5 = (int)(short)(&DAT_803cfe32)[sVar6 * 0x2e];
  }
  return;
}



// ==== 800eee10  zz_00eee10_ ====

undefined4 zz_00eee10_(uint param_1,char param_2,char param_3,short param_4)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  short sVar5;
  
  uVar2 = 0;
  iVar4 = (int)DAT_803d1520;
  uVar1 = countLeadingZeros(-1 - DAT_803d1522);
  uVar3 = countLeadingZeros(-1 - iVar4);
  if ((uVar3 >> 5) + (uVar1 >> 4 & 0xffffffe) == 0) {
    uVar1 = 0;
    if ((param_1 >> 0x18 & 1) != 0) {
      uVar1 = 0x7f;
    }
    if ((param_1 >> 0x18 & 2) != 0) {
      uVar1 = uVar1 | 0x7f00;
    }
    if ((param_1 >> 0x18 & 4) != 0) {
      uVar1 = uVar1 | 0x7f0000;
    }
    while (sVar5 = (short)iVar4, sVar5 != -1) {
      iVar4 = sVar5 * 0x5c;
      if (((param_1 & uVar1) ==
           (uVar1 & ((uint)(byte)(&DAT_803cfe57)[iVar4] |
                    (uint)(byte)(&DAT_803cfe55)[iVar4] << 0x10 |
                    (uint)(byte)(&DAT_803cfe56)[iVar4] << 8))) &&
         (0x40 < *(int *)(&DAT_803cfe28 + iVar4))) {
        if (param_2 != -1) {
          (&DAT_803cfe48)[iVar4] = param_2;
          *(ushort *)(&DAT_803cfe50 + iVar4) = *(ushort *)(&DAT_803cfe50 + iVar4) | 1;
        }
        if (param_3 != -1) {
          (&DAT_803cfe49)[iVar4] = param_3;
          *(ushort *)(&DAT_803cfe50 + iVar4) = *(ushort *)(&DAT_803cfe50 + iVar4) | 2;
        }
        if (param_4 != -1) {
          *(short *)(&DAT_803cfe4a + iVar4) = param_4;
          *(ushort *)(&DAT_803cfe50 + iVar4) = *(ushort *)(&DAT_803cfe50 + iVar4) | 4;
        }
        uVar2 = 1;
      }
      iVar4 = (int)(short)(&DAT_803cfe32)[sVar5 * 0x2e];
    }
  }
  return uVar2;
}



// ==== 800eef30  zz_00eef30_ ====

uint zz_00eef30_(void)

{
  int iVar1;
  
  iVar1 = DAT_803d3a68;
  if (DAT_803d3a68 == 0) {
    return 0xffffffff;
  }
  DAT_803d3a68 = DAT_803d3a68 + -1;
  return (uint)*(byte *)((int)&DAT_803d3a68 + iVar1 + 3);
}



// ==== 800eef60  zz_00eef60_ ====

uint zz_00eef60_(short param_1)

{
  uint uVar1;
  
  uVar1 = zz_00eef30_();
  if (-1 < (short)uVar1) {
    zz_00eefb0_(param_1,(short)uVar1);
  }
  return uVar1;
}



// ==== 800eefb0  zz_00eefb0_ ====

void zz_00eefb0_(short param_1,short param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  uint uVar5;
  int iVar6;
  
  iVar2 = (int)param_2;
  iVar6 = (int)param_1;
  (&DAT_803d1594)[iVar2 * 0x4a] = param_1;
  (&DAT_803d158c)[iVar2 * 0x94] = 0;
  (&DAT_803d158d)[iVar2 * 0x94] = 0;
  uVar3 = countLeadingZeros(-1 - (short)(&DAT_803cfe36)[iVar6 * 0x2e]);
  uVar5 = countLeadingZeros(-1 - (short)(&DAT_803cfe34)[iVar6 * 0x2e]);
  sVar4 = (short)(uVar5 >> 5) + ((ushort)(uVar3 >> 4) & 0xfffe);
  if (sVar4 == 3) {
    (&DAT_803cfe34)[iVar6 * 0x2e] = param_2;
    (&DAT_803cfe36)[iVar6 * 0x2e] = param_2;
    return;
  }
  if ((sVar4 < 3) && (sVar4 == 0)) {
    (&DAT_803d1592)[(short)(&DAT_803cfe36)[iVar6 * 0x2e] * 0x4a] = param_2;
    (&DAT_803d158e)[iVar2 * 0x4a] = (&DAT_803cfe36)[iVar6 * 0x2e];
    (&DAT_803cfe36)[iVar6 * 0x2e] = param_2;
    return;
  }
  puVar1 = &DAT_803d3a6c + DAT_803d3a68;
  DAT_803d3a68 = DAT_803d3a68 + 1;
  *puVar1 = (char)param_2;
  return;
}



// ==== 800ef070  zz_00ef070_ ====

/* WARNING: Removing unreachable block (ram,0x800ef0e8) */

void zz_00ef070_(short param_1,short param_2)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = (int)param_2;
  iVar5 = (int)param_1;
  puVar1 = &DAT_803d3a6c + DAT_803d3a68;
  DAT_803d3a68 = DAT_803d3a68 + 1;
  *puVar1 = (char)param_2;
  iVar6 = (int)(short)(&DAT_803d158e)[iVar2 * 0x4a];
  iVar7 = (int)(short)(&DAT_803d1592)[iVar2 * 0x4a];
  uVar3 = countLeadingZeros(-1 - iVar7);
  uVar4 = countLeadingZeros(-1 - iVar6);
  uVar3 = (uVar4 >> 5) + (uVar3 >> 4 & 0xffffffe);
  if (uVar3 == 2) {
    (&DAT_803d1592)[iVar6 * 0x4a] = 0xffff;
    (&DAT_803cfe36)[iVar5 * 0x2e] = (&DAT_803d158e)[iVar2 * 0x4a];
  }
  else if (uVar3 < 2) {
    if (uVar3 == 0) {
      (&DAT_803d1592)[iVar6 * 0x4a] = (&DAT_803d1590)[iVar7 * 0x4a];
      (&DAT_803d158e)[iVar7 * 0x4a] = (&DAT_803d1590)[iVar6 * 0x4a];
    }
    else {
      (&DAT_803d158e)[iVar7 * 0x4a] = 0xffff;
      (&DAT_803cfe34)[iVar5 * 0x2e] = (&DAT_803d1592)[iVar2 * 0x4a];
    }
  }
  else if (uVar3 < 4) {
    (&DAT_803cfe36)[iVar5 * 0x2e] = 0xffff;
    (&DAT_803cfe34)[iVar5 * 0x2e] = 0xffff;
  }
  (&DAT_803d1592)[iVar2 * 0x4a] = 0xffff;
  (&DAT_803d158e)[iVar2 * 0x4a] = 0xffff;
  return;
}



// ==== 800ef178  zz_00ef178_ ====

uint zz_00ef178_(void)

{
  int iVar1;
  
  iVar1 = DAT_803d1524;
  if (DAT_803d1524 == 0) {
    return 0xffffffff;
  }
  DAT_803d1524 = DAT_803d1524 + -1;
  return (uint)*(byte *)((int)&DAT_803d1524 + iVar1 + 3);
}



// ==== 800ef1a8  zz_00ef1a8_ ====

uint zz_00ef1a8_(void)

{
  uint uVar1;
  
  uVar1 = zz_00ef178_();
  if (-1 < (short)uVar1) {
    zz_00ef1e4_((short)uVar1);
  }
  return uVar1;
}



