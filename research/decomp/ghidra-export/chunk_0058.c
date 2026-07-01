// ==== 801dac6c  FUN_801dac6c ====

void FUN_801dac6c(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 0x10c9) != '\x01') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined4 *)(param_1 + 0x174) = 1;
  }
  iVar4 = (&DAT_804362d8)[*(char *)(param_1 + 0x10)];
  if (*(char *)(iVar4 + 0x10c9) == '\x01') {
    iVar2 = *(char *)(iVar4 + 0x10ca) * 2;
    if (*(short *)(iVar4 + iVar2 + 0x38) != 0) {
      *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x10) + '\x01';
      *(float *)(param_1 + 0x68) =
           FLOAT_8043bfa0 *
           (float)((double)CONCAT44(0x43300000,
                                    (int)*(short *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] +
                                                    iVar2 + 0x30) ^ 0x80000000) - DOUBLE_8043bfa8) +
           *(float *)(param_1 + 0x14c);
      uVar3 = (int)*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 0x10cf) << 0x10;
      iVar4 = (int)uVar3 / 0x78 +
              ((int)(uVar3 | (uint)(int)*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] +
                                                 0x10cf) >> 0x10) >> 0x1f);
      dVar5 = zz_0045238_((short)iVar4 - (short)(iVar4 >> 0x1f));
      *(float *)(param_1 + 0x178) = (float)((double)FLOAT_8043bfc0 * dVar5 + (double)FLOAT_8043bfbc)
      ;
      return;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801dadd0  FUN_801dadd0 ====

void FUN_801dadd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  float fVar4;
  int iVar5;
  float *pfVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar10;
  double dVar11;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined4 *)(param_9 + 0x174) = 1;
  }
  fVar4 = FLOAT_8043bfb0;
  bVar2 = *(byte *)(param_9 + 0x10);
  uVar7 = (uint)bVar2;
  iVar5 = (&DAT_804362d8)[(char)bVar2];
  if ((int)*(char *)(param_9 + 0x13) < (int)*(short *)(iVar5 + 0x40)) {
    uVar9 = (uint)*(char *)(iVar5 + 0x10ca);
    iVar8 = uVar9 * 2;
    if ((int)*(char *)(param_9 + 0x13) < (int)*(short *)(iVar5 + iVar8 + 0x38)) {
      *(byte *)(param_9 + 0x82) = bVar2 + 1;
      *(float *)(param_9 + 0x178) = fVar4;
      pfVar6 = (float *)(&DAT_804362d8)[*(char *)(param_9 + 0x10)];
      uVar10 = uVar9;
      if (*(char *)((int)pfVar6 + 0x10c9) == '\x01') {
        if (*(char *)((int)pfVar6 + *(char *)(param_9 + 0x13) + 0x10bd) != '\0') {
          uVar10 = 5;
        }
        if ((int)*(char *)(param_9 + 0x13) == (int)*(short *)((int)pfVar6 + iVar8 + 0x30)) {
          uVar10 = 4;
          uVar3 = (int)*(char *)((int)pfVar6 + 0x10cf) << 0x10;
          iVar5 = (int)uVar3 / 0x78 +
                  ((int)(uVar3 | (uint)(int)*(char *)((int)pfVar6 + 0x10cf) >> 0x10) >> 0x1f);
          dVar11 = zz_0045204_((short)iVar5 - (short)(iVar5 >> 0x1f));
          *(float *)(param_9 + 0x178) =
               (float)((double)FLOAT_8043bfc4 * dVar11 + (double)FLOAT_8043bfc4);
        }
      }
      dVar11 = DOUBLE_8043bfa8;
      if (*(uint *)(param_9 + 0x180) == uVar10) {
        return;
      }
      *(uint *)(param_9 + 0x180) = uVar10;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - dVar11),param_2
                  ,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar6,uVar7,iVar8,
                  uVar9,in_r9,in_r10);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801daf58  FUN_801daf58 ====

void FUN_801daf58(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  iVar5 = (&DAT_804362d8)[*(char *)(param_9 + 0x10)];
  if (*(char *)(iVar5 + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
  else if (((int)*(char *)(param_9 + 0x13) < (int)*(short *)(iVar5 + 0x40)) &&
          (iVar2 = *(char *)(iVar5 + 0x10ca) * 2,
          (int)*(char *)(param_9 + 0x13) < (int)*(short *)(iVar5 + iVar2 + 0x38))) {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
    dVar4 = DOUBLE_8043bfa8;
    iVar6 = ((int)*(char *)(param_9 + 0x13) +
            *(short *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + iVar2 + 0x28) + 1) /
            (int)*(short *)(&DAT_80435b20 + *(char *)(param_9 + 0x12) * 2);
    iVar5 = iVar6 / 10 + (iVar6 >> 0x1f);
    pfVar3 = (float *)-(iVar5 >> 0x1f);
    uVar7 = iVar6 + (iVar5 + (int)pfVar3) * -10;
    if (*(uint *)(param_9 + 0x180) == uVar7) {
      return;
    }
    *(uint *)(param_9 + 0x180) = uVar7;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) - dVar4),param_2,
                param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar3,uVar7,
                (int)*(char *)(param_9 + 0x13),&DAT_804362d8,iVar2,in_r10);
    return;
  }
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801db0bc  FUN_801db0bc ====

void FUN_801db0bc(int param_1)

{
  char cVar1;
  byte bVar2;
  double dVar3;
  double dVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 0x10c9) == '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
  }
  bVar2 = *(byte *)(param_1 + 0x10);
  iVar5 = (&DAT_804362d8)[(char)bVar2];
  if (*(char *)(iVar5 + 0x10c9) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  else if (((*(char *)(iVar5 + 0x10cc) == '\0') &&
           ((int)*(char *)(param_1 + 0x13) < (int)*(short *)(iVar5 + 0x40))) &&
          (cVar1 = *(char *)(iVar5 + 0x10ca),
          (int)*(char *)(param_1 + 0x13) < (int)*(short *)(iVar5 + cVar1 * 2 + 0x38))) {
    *(byte *)(param_1 + 0x82) = bVar2 + 1;
    dVar3 = DOUBLE_8043bfa8;
    dVar8 = (double)FLOAT_8043bfcc;
    *(float *)(param_1 + 100) =
         (float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,
                                                          (int)*(char *)(param_1 + 0x12) ^
                                                          0x80000000) - DOUBLE_8043bfa8) +
                (double)FLOAT_8043bfc8);
    iVar5 = (int)*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] +
                           (int)*(char *)(param_1 + 0x13) + 0x10b4);
    if (iVar5 < 0) {
      iVar5 = 10;
    }
    else {
      if (iVar5 < 10) {
        if (*(char *)(param_1 + 0x12) == '\0') goto LAB_801db138;
        *(float *)(param_1 + 100) = FLOAT_8043bfd0;
      }
      iVar5 = iVar5 / (int)*(short *)(*(char *)(param_1 + 0x12) * 2 + -0x7fbca4dc);
      iVar7 = iVar5 / 10 + (iVar5 >> 0x1f);
      iVar5 = iVar5 + (iVar7 - (iVar7 >> 0x1f)) * -10;
    }
    dVar4 = DOUBLE_8043bfa8;
    iVar7 = (&DAT_804362d8)[*(char *)(param_1 + 0x10)];
    if (*(char *)(iVar7 + *(char *)(param_1 + 0x13) + 0x10bd) == '\0') {
      pfVar6 = (float *)(iVar5 + cVar1 * 0xb);
    }
    else {
      pfVar6 = (float *)(iVar5 + 0xb);
    }
    if (*(float **)(param_1 + 0x180) == pfVar6) {
      return;
    }
    *(float **)(param_1 + 0x180) = pfVar6;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar6 ^ 0x80000000) - dVar4),
                dVar3,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,0,pfVar6,iVar7,
                *(char *)(param_1 + 0x10) * 4,(uint)bVar2,in_r9,in_r10);
    return;
  }
LAB_801db138:
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801db2c4  FUN_801db2c4 ====

void FUN_801db2c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  bVar2 = *(byte *)(param_9 + 0x10);
  iVar4 = (&DAT_804362d8)[(char)bVar2];
  if (*(char *)(iVar4 + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
  else {
    iVar3 = (int)*(char *)(param_9 + 0x13);
    iVar5 = (int)*(char *)(iVar4 + iVar3 + 0x10ab);
    if (((iVar5 != 0) && (iVar3 < *(short *)(iVar4 + 0x40))) &&
       (iVar3 < *(short *)(iVar4 + *(char *)(iVar4 + 0x10ca) * 2 + 0x38))) {
      *(byte *)(param_9 + 0x82) = bVar2 + 1;
      if (*(int *)(param_9 + 0x180) == iVar5) {
        return;
      }
      *(int *)(param_9 + 0x180) = iVar5;
      *(int *)(param_9 + 0x144) = (int)(char)(&DAT_80435b28)[iVar5];
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  &DAT_80435b28,iVar4,(uint)bVar2,iVar5,in_r9,in_r10);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801db3cc  FUN_801db3cc ====

void FUN_801db3cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  bVar2 = *(byte *)(param_9 + 0x10);
  iVar3 = (&DAT_804362d8)[(char)bVar2];
  if (*(char *)(iVar3 + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
  else if (((*(char *)(iVar3 + 0x10cc) == '\x01') &&
           ((int)*(char *)(param_9 + 0x13) < (int)*(short *)(iVar3 + 0x40))) &&
          ((int)*(char *)(param_9 + 0x13) <
           (int)*(short *)(iVar3 + *(char *)(iVar3 + 0x10ca) * 2 + 0x38))) {
    *(byte *)(param_9 + 0x82) = bVar2 + 1;
    iVar4 = (&DAT_804362d8)[*(char *)(param_9 + 0x10)];
    iVar3 = (int)*(char *)(iVar4 + *(char *)(param_9 + 0x13) + 0x10b4);
    if (*(int *)(param_9 + 0x180) == iVar3) {
      return;
    }
    *(int *)(param_9 + 0x180) = iVar3;
    *(int *)(param_9 + 0x144) = iVar3 + 0x22;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar4,
                &DAT_804362d8,(uint)bVar2,in_r8,in_r9,in_r10);
    return;
  }
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801db60c  FUN_801db60c ====

void FUN_801db60c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (0x3b < sVar3) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  uVar4 = (uint)*(short *)(param_9 + 0x1c);
  iVar5 = *(int *)(param_9 + 0x144);
  iVar2 = *(int *)(param_9 + 0x180) + ((int)uVar4 >> 0x1f) + (uint)(0x1d < uVar4);
  if (iVar5 != iVar2) {
    *(int *)(param_9 + 0x144) = iVar2;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                (int)uVar4 >> 0x1f,uVar4,*(int *)(param_9 + 0x180),iVar5,in_r9,in_r10);
  }
  return;
}



// ==== 801db6c4  FUN_801db6c4 ====

void FUN_801db6c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
    dVar2 = DOUBLE_8043bfa8;
    if (*(char *)(param_9 + 0x12) < 3) {
      param_12 = (int)*(char *)(param_9 + 0x10);
      iVar4 = (int)*(short *)((&DAT_804362d8)[param_12] + *(char *)(param_9 + 0x12) * 2 + 0x42);
      iVar3 = iVar4 / 10 + (iVar4 >> 0x1f);
      pfVar5 = (float *)(iVar4 + (iVar3 - (iVar3 >> 0x1f)) * -10);
    }
    else {
      pfVar5 = (float *)0x7;
    }
    if (*(float **)(param_9 + 0x180) != pfVar5) {
      *(float **)(param_9 + 0x180) = pfVar5;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar5 ^ 0x80000000) - dVar2),
                  param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar5,param_12,
                  &DAT_804362d8,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 801db930  FUN_801db930 ====

void FUN_801db930(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801dba2c;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x12)] + 0x10d5) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  iVar3 = *(int *)(param_9 + 0xe0);
  dVar4 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000)
                         - DOUBLE_8043bfa8);
  zz_0008614_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x154),iVar3,param_11,param_12,param_13,param_14,param_15,param_16)
  ;
  zz_0007c30_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x23 < sVar2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
  if (*(short *)(param_9 + 0x1c) == 10) {
    *(undefined1 *)((&DAT_804362d8)[*(char *)(param_9 + 0x12)] + 0x10d5) = 2;
  }
LAB_801dba2c:
  if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x12)] + 0x10d5) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801dba6c  FUN_801dba6c ====

void FUN_801dba6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char cVar2;
  short sVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  
  cVar1 = *(char *)(param_9 + 0x12);
  cVar2 = *(char *)(param_9 + 0x19);
  iVar5 = (int)cVar1 / 2;
  if (cVar2 != '\x01') {
    if ('\0' < cVar2) {
      if ('\x02' < cVar2) {
        return;
      }
      goto LAB_801dbb5c;
    }
    if (cVar2 < '\0') {
      return;
    }
    if (*(char *)(DAT_804362d8 + 0x10d1) == '\0') {
      return;
    }
    if (*(char *)(iRam804362dc + 0x10d1) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar2 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (sVar3 < 10) {
    return;
  }
  dVar6 = (double)FLOAT_8043bfdc;
  *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x10) + 1;
  zz_01a76fc_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
              (float *)(uint)*(byte *)(param_9 + 0x10),param_12,param_13,param_14,param_15,param_16)
  ;
  *(undefined1 *)((&DAT_804362d8)[iVar5] + 0x10d6) = 3;
LAB_801dbb5c:
  dVar6 = DOUBLE_8043bfa8;
  if ((*(char *)(DAT_804362d8 + 0x10d1) == '\0') || (*(char *)(iRam804362dc + 0x10d1) == '\0')) {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else if ((((int)cVar1 & 1U) == (int)*(char *)((&DAT_804362d8)[iVar5] + 0x10d1) - 1U) &&
          (pfVar4 = (float *)(*(byte *)((&DAT_804362d8)[iVar5] + 0x10d2) >> 2 & 1),
          *(float **)(param_9 + 0x180) != pfVar4)) {
    *(float **)(param_9 + 0x180) = pfVar4;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar4 ^ 0x80000000) - dVar6),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4,param_12,
                param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801dbc08  FUN_801dbc08 ====

void FUN_801dbc08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801dbcdc;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)(DAT_804362d8 + 0x10d1) == '\0') {
      return;
    }
    if (*(char *)(iRam804362dc + 0x10d1) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  dVar2 = DOUBLE_8043bfa8;
  if (sVar3 < 10) {
    return;
  }
  *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(char *)(param_9 + 0x12) ^ 0x80000000) - dVar2)
              ,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,param_12,
              param_13,param_14,param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
LAB_801dbcdc:
  if ((*(char *)(DAT_804362d8 + 0x10d1) == '\0') || (*(char *)(iRam804362dc + 0x10d1) == '\0')) {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(float *)(param_9 + 100) =
         FLOAT_8043bfb4 *
         (float)((double)CONCAT44(0x43300000,
                                  (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x12)] + 0x10d1
                                                ) - 1U ^ 0x80000000) - DOUBLE_8043bfa8) +
         *(float *)(param_9 + 0x148);
    *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + -0x200;
  }
  return;
}



// ==== 801dbd78  FUN_801dbd78 ====

void FUN_801dbd78(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801dbe0c;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)(DAT_804362d8 + 0x10d1) == '\0') {
      return;
    }
    if (*(char *)(iRam804362dc + 0x10d1) == '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 10) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x10) + '\x01';
LAB_801dbe0c:
  if ((*(char *)(DAT_804362d8 + 0x10d1) == '\0') || (*(char *)(iRam804362dc + 0x10d1) == '\0')) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(float *)(param_1 + 100) =
       FLOAT_8043bfb4 *
       (float)((double)CONCAT44(0x43300000,
                                (int)*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x12)] + 0x10d1)
                                - 1U ^ 0x80000000) - DOUBLE_8043bfa8) + *(float *)(param_1 + 0x148);
  return;
}



// ==== 801dbea4  FUN_801dbea4 ====

void FUN_801dbea4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801dbec4  FUN_801dbec4 ====

/* WARNING: Removing unreachable block (ram,0x801dc268) */
/* WARNING: Removing unreachable block (ram,0x801dc260) */
/* WARNING: Removing unreachable block (ram,0x801dbedc) */
/* WARNING: Removing unreachable block (ram,0x801dbed4) */

void FUN_801dbec4(int param_1)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  int iVar6;
  byte *__s;
  undefined2 uVar8;
  uint uVar7;
  undefined2 uVar9;
  double dVar10;
  double dVar11;
  undefined2 local_78 [2];
  uint uStack_74;
  int local_70 [2];
  undefined8 local_68;
  double local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined8 local_50;
  
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 == '\r') {
    iVar3 = (int)*(char *)(param_1 + 0x10);
    dVar10 = (double)FLOAT_8043bfec;
    uVar5 = (uint)*(char *)(param_1 + 0x13);
    uStack_54 = uVar5 ^ 0x80000000;
    local_60 = (double)(CONCAT44(0x43300000,iVar3) ^ 0x80000000);
    local_58 = 0x43300000;
    uVar7 = (uint)(FLOAT_8043bfe8 * (float)(local_60 - DOUBLE_8043bfa8) + FLOAT_8043bff0);
    local_68 = (double)(longlong)(int)uVar7;
    bVar2 = *(byte *)((&DAT_804362d8)[iVar3] + uVar5 + 0x1036);
    iVar6 = (int)(FLOAT_8043bff8 * (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043bfa8)
                 + FLOAT_8043bff4);
    local_50 = (double)(longlong)iVar6;
    local_78[0] = *(undefined2 *)((&DAT_804362d8)[iVar3] + uVar5 * 2 + 0x1024);
    uVar9 = (undefined2)iVar6;
    dVar11 = dVar10;
    __s = (byte *)zz_0066270_((char *)local_78);
    if ((bVar2 & 1) != 0) {
      if (*(char *)((&DAT_804362d8)[iVar3] + 0x10d8) == '\0') {
        dVar10 = (double)FLOAT_8043bffc;
        zz_0096d0c_((double)(float)(dVar11 / (double)FLOAT_8043bfe0));
        zz_0096d14_((double)FLOAT_8043bffc);
        sVar4 = strlen((char *)__s);
        uStack_54 = uVar7 ^ 0x80000000;
        local_50 = (double)CONCAT44(0x43300000,sVar4);
        local_58 = 0x43300000;
        iVar6 = (int)(FLOAT_8043bffc * (float)(local_50 - DOUBLE_8043c000) * FLOAT_8043bfc0 +
                     (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043bfa8));
        local_60 = (double)(longlong)iVar6;
        FUN_8009718c((short)iVar6,uVar9,0x1e,
                     (byte *)((&DAT_804362d8)[iVar3] + *(char *)(param_1 + 0x13) * 0xc + 0x1047));
      }
      else {
        uVar7 = uVar7 + 0x60;
        __s = (byte *)((&DAT_804362d8)[iVar3] + *(char *)(param_1 + 0x13) * 0xc + 0x103f);
      }
    }
    uVar8 = (undefined2)uVar7;
    if ((bVar2 & 2) == 0) {
      if (*(char *)((&DAT_804362d8)[iVar3] + (int)*(char *)(param_1 + 0x13) + 0x10bd) == '\0') {
        iVar6 = *(char *)((&DAT_804362d8)[iVar3] + 0x10ca) + 10;
      }
      else {
        iVar6 = 0x17;
      }
    }
    else {
      iVar6 = 0xe;
    }
LAB_801dc238:
    zz_0096d0c_((double)(float)(dVar11 / (double)FLOAT_8043bfe0));
    zz_0096d14_(dVar10);
    FUN_8009718c(uVar8,uVar9,iVar6,__s);
  }
  else {
    if (cVar1 < '\r') {
      if (cVar1 == '\b') {
        if (*(char *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 0x10c9) == '\0') {
          return;
        }
        __s = (byte *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 100);
        dVar10 = (double)FLOAT_8043bfe0;
        uVar9 = 0x2e;
        local_68 = (double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x10) ^ 0x80000000);
        iVar6 = 0;
        iVar3 = (int)(FLOAT_8043bfe8 * (float)(local_68 - DOUBLE_8043bfa8) + FLOAT_8043bfe4);
        local_60 = (double)(longlong)iVar3;
        uVar8 = (undefined2)iVar3;
        dVar11 = dVar10;
        goto LAB_801dc238;
      }
      if ('\a' < cVar1) {
        return;
      }
      if (cVar1 < '\a') {
        return;
      }
      iVar6 = (int)*(char *)(param_1 + 0x10);
      cVar1 = *(char *)((&DAT_804362d8)[iVar6] + 0x10d4);
    }
    else {
      if (cVar1 != '\x1b') {
        return;
      }
      iVar6 = (int)*(char *)(param_1 + 0x12);
      cVar1 = *(char *)((&DAT_804362d8)[iVar6] + 0x10d5);
    }
    if (('\x01' < cVar1) && (iVar3 = (int)*(char *)((&DAT_804362d8)[iVar6] + 0x10d6), -1 < iVar3)) {
      uVar9 = *(undefined2 *)(&DAT_803909f0 + iVar3 * 2);
      iVar3 = (int)(char)(&DAT_803909e4)[iVar3];
      if ((iVar6 != 0) && (iVar3 == 3)) {
        iVar3 = 4;
      }
      zz_009749c_(1,iVar3,local_70,&uStack_74);
      zz_0096d0c_((double)FLOAT_8043bfb0);
      zz_0096d14_((double)FLOAT_8043bfe0);
      zz_00970fc_((short)iVar6 * 0x140 + (short)((local_70[0] * -10 + 0x140) / 2),uVar9,0,'\x01',
                  (short)iVar3,-1);
    }
  }
  return;
}



// ==== 801dc284  FUN_801dc284 ====

void FUN_801dc284(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801dc2a4  FUN_801dc2a4 ====

void FUN_801dc2a4(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x39,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = param_1;
    *(undefined1 **)(puVar1 + 0xc) = &LAB_801dc30c;
    *(code **)(puVar1 + 0x10c) = FUN_801dc344;
  }
  return;
}



// ==== 801dc344  FUN_801dc344 ====

void FUN_801dc344(int param_1)

{
  uRam80435b37 = *(undefined1 *)((&DAT_804362d8)[*(char *)(param_1 + 0x10)] + 0x10ce);
  DAT_80390a08 = FLOAT_8043bfe8 *
                 (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x10) ^ 0x80000000) -
                        DOUBLE_8043bfa8);
  DAT_803c1140 = &DAT_80390a08;
  DAT_803c1144 = 0;
  DAT_803c1150 = &DAT_80435b34;
  DAT_803c1154 = &DAT_80435b30;
  DAT_803c1164 = 5;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  FUN_80051998(-0x7fc3eed0);
  return;
}



// ==== 801dc3ec  FUN_801dc3ec ====

void FUN_801dc3ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(char *)(*(int *)(param_9 + 0x8c) + 0x18) < '\x02') {
    if (*(char *)(*(int *)(param_9 + 0x8c) + 0x82) == '\0') {
      param_9[0x82] = 0;
    }
    else {
      param_9[0x82] = 0x11;
    }
  }
  else {
    zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 801dc444  FUN_801dc444 ====

void FUN_801dc444(int param_1)

{
  FUN_801dbec4(*(int *)(param_1 + 0x8c));
  return;
}



// ==== 801dc468  FUN_801dc468 ====

/* WARNING: Removing unreachable block (ram,0x801dc574) */
/* WARNING: Removing unreachable block (ram,0x801dc478) */

double FUN_801dc468(double param_1,double param_2,double param_3,double param_4,double param_5,
                   double param_6,double param_7,double param_8,int param_9,int param_10,
                   undefined1 param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                   undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined1 *puVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  char cVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  undefined8 extraout_f1;
  double dVar8;
  
  piVar6 = *(int **)(param_9 + 0x10);
  DAT_80435b38 = &DAT_803d5e30;
  pfVar3 = (float *)0x14;
  gnt4_memset(&DAT_803d5e30,0,0x14);
  fVar1 = FLOAT_8043c008;
  *DAT_80435b38 = 1;
  *(float *)(DAT_80435b38 + 8) = (float)param_1;
  *(float *)(DAT_80435b38 + 0xc) = fVar1;
  uVar7 = zz_00088a4_((double)*(float *)(DAT_80435b38 + 8),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,param_9,DAT_80435b38,pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
  uVar7 = zz_0008948_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (float *)&DAT_803c7380,extraout_r4,(undefined *)pfVar3,param_12,param_13,
                      param_14,param_15,param_16);
  uVar7 = zz_01dc668_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,(undefined *)pfVar3,param_12,
                      param_13,param_14,param_15,param_16);
  dVar8 = zz_0008a1c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  cVar4 = '\0';
  *(float *)(DAT_80435b38 + 0xc) = (float)dVar8;
  *(int *)(DAT_80435b38 + 4) = param_9;
  for (iVar5 = 0; *(int *)(*piVar6 + iVar5) != 0; iVar5 = iVar5 + 4) {
    puVar2 = zz_008893c_(2,param_10,1,1);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      *(code **)(puVar2 + 0xc) = FUN_801dc744;
      *(code **)(puVar2 + 0x10c) = FUN_801dc8c0;
      *(int *)(puVar2 + 0x54) = param_9;
      puVar2[0x13] = cVar4;
      puVar2[0x10] = param_11;
    }
    cVar4 = cVar4 + '\x01';
  }
  return (double)*(float *)(DAT_80435b38 + 0xc);
}



// ==== 801dc590  zz_01dc590_ ====

void zz_01dc590_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined4 extraout_r4;
  double dVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  
  dVar2 = (double)*(float *)(DAT_80435b38 + 0xc);
  if ((param_1 <= dVar2) && (dVar2 = param_1, param_1 < (double)FLOAT_8043c008)) {
    dVar2 = (double)FLOAT_8043c008;
  }
  *(float *)(DAT_80435b38 + 8) = (float)dVar2;
  uVar3 = zz_00088a4_((double)*(float *)(DAT_80435b38 + 8),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,*(int *)(DAT_80435b38 + 4),DAT_80435b38,param_11,param_12,
                      param_13,param_14,param_15,param_16);
  uVar3 = zz_0008948_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (float *)&DAT_803c7380,extraout_r4,(undefined *)param_11,param_12,param_13,
                      param_14,param_15,param_16);
  zz_01dc668_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,(undefined *)param_11,param_12,param_13,
              param_14,param_15,param_16);
  pfVar1 = (float *)zz_000598c_(0);
  dVar2 = (double)SidelineExplodableManager__GetNumExplodables_void_();
  *pfVar1 = (float)dVar2;
  return;
}



// ==== 801dc614  zz_01dc614_ ====

void zz_01dc614_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  
  *DAT_80435b38 = 0;
  puVar1 = DAT_80435b38;
  *(undefined4 *)(DAT_80435b38 + 4) = 0;
  zz_0008924_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801dc648  zz_01dc648_ ====

double zz_01dc648_(void)

{
  if (*DAT_80435b38 != '\0') {
    return (double)*(float *)(DAT_80435b38 + 8);
  }
  return (double)FLOAT_8043c00c;
}



// ==== 801dc668  zz_01dc668_ ====

void zz_01dc668_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  float *pfVar2;
  float *pfVar3;
  undefined8 uVar4;
  float afStack_38 [3];
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar4 = zz_0008970_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_14,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_00089c0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_20,
                      extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  cCameraManager__HasCamera_cBaseCamera
            (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_2c,extraout_r4_00,
             param_11,param_12,param_13,param_14,param_15,param_16);
  DAT_803c7698 = local_14;
  DAT_803c769c = local_10;
  DAT_803c76a0 = local_c;
  DAT_803c76b0 = local_2c;
  DAT_803c76b4 = local_28;
  DAT_803c76b8 = local_24;
  DAT_803c76e0 = local_20;
  DAT_803c76e4 = local_1c;
  DAT_803c76e8 = local_18;
  uVar4 = gnt4_PSVECSubtract_bl(&local_2c,&local_14,afStack_38);
  pfVar2 = afStack_38;
  pfVar3 = &local_20;
  uVar1 = 5;
  zz_0045ef4_((float *)&DAT_803c7714,5,pfVar2,pfVar3);
  zz_0008948_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(float *)&DAT_803c7744,
              uVar1,(undefined *)pfVar2,pfVar3,local_20,local_24,local_28,local_2c);
  PTR_DAT_80433930[0xc] = 0;
  return;
}



// ==== 801dc744  FUN_801dc744 ====

void FUN_801dc744(int param_1)

{
  if (*(int *)(DAT_80435b38 + 4) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80390a18)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801dc7a0  FUN_801dc7a0 ====

void FUN_801dc7a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (int)*(char *)(param_9 + 0x13);
  uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),iVar1,param_12,param_13,
                      param_14,param_15,param_16);
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x10) + 1;
  zz_01dc7f8_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              (uint)*(byte *)(param_9 + 0x10),iVar1,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801dc7f8  zz_01dc7f8_ ====

/* WARNING: Removing unreachable block (ram,0x801dc83c) */

void zz_01dc7f8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 extraout_r4;
  uint uVar2;
  float *pfVar3;
  int *piVar4;
  undefined8 uVar5;
  
  pfVar3 = DAT_80435b38;
  uVar5 = zz_00087d4_((double)DAT_80435b38[2],param_2,param_3,param_4,param_5,param_6,param_7,
                      param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),DAT_80435b38,
                      param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
  piVar4 = *(int **)(*(int *)(param_9 + 0xe0) + 0xc);
  if (piVar4 != (int *)0x0) {
    uVar2 = piVar4[5];
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      gnt4_HSD_JObjSetupMatrixSub_bl
                (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar4,uVar2,pfVar3,
                 param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 801dc8a0  FUN_801dc8a0 ====

void FUN_801dc8a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801dc8c0  FUN_801dc8c0 ====

void FUN_801dc8c0(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x47);
  return;
}



// ==== 801dc8e8  zz_01dc8e8_ ====

void zz_01dc8e8_(undefined1 param_1,undefined1 param_2,int param_3,undefined2 *param_4)

{
  DAT_80436398 = &DAT_803d5e48;
  gnt4_memset(&DAT_803d5e48,0,0x70);
  DAT_80436398[0x14] = param_1;
  DAT_80436398[0x15] = param_2;
  zz_01dd5d4_(param_3,param_4);
  FUN_80181e78();
  return;
}



// ==== 801dc970  zz_01dc970_ ====

byte zz_01dc970_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  *(undefined4 *)(DAT_80436398 + 8) = (&DAT_803c71fc)[DAT_80436398[0x15] * 8];
  *(undefined4 *)(DAT_80436398 + 0xc) = (&DAT_803c7204)[DAT_80436398[0x15] * 8];
  *(uint *)(DAT_80436398 + 0x10) =
       *(uint *)(DAT_80436398 + 0xc) | (&DAT_803c720c)[DAT_80436398[0x15] * 8];
  uVar1 = (*(code *)(&PTR_FUN_80390a7c)[*DAT_80436398])();
  if (DAT_80436398[0x6b] != '\0') {
    zz_01dcf7c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return DAT_80436398[0x17] & 2;
}



// ==== 801dca30  FUN_801dca30 ====

void FUN_801dca30(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  float fVar4;
  int iVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar6;
  undefined4 uVar7;
  int in_r6;
  uint in_r7;
  char *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar8;
  double dVar9;
  
  cVar1 = DAT_80436398[1];
  if (cVar1 == '\x02') {
    DAT_80436398[1] = '\x03';
    if (DAT_80436398[0x67] == '\0') {
      *(undefined4 *)(DAT_80436398 + 0x20) = *(undefined4 *)(DAT_803c4e84 + 0x24);
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        iVar5 = zz_000a3c4_();
        in_r8 = DAT_80436398;
        if (iVar5 != 0) {
          return;
        }
        in_r6 = -0x7fc40000;
        uVar7 = 0x803c0000;
        in_r7 = (uint)(byte)DAT_80436398[1];
        DAT_80436398[1] = DAT_80436398[1] + 1;
        DAT_803c6e4c = 0;
        DAT_803c6e64 = 0;
        DAT_803c6e7c = 0;
        DAT_803c6e94 = 0;
        uVar8 = zz_00f0a4c_();
        uVar8 = zz_00445ac_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)DAT_80436398[0x14]);
        uVar6 = extraout_r4;
        if (DAT_80436398[0x14] != '\0') {
          uVar8 = zz_0044bec_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_80436398[0x14] + 1,1,uVar7,in_r6,in_r7,in_r8,in_r9,in_r10);
          uVar6 = extraout_r4_00;
        }
        if (DAT_80436398[0x67] == '\0') {
          in_r6 = (int)DAT_80436398[0x1a];
          zz_00416d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      DAT_80436398[0x14] + 1,0,*(short *)(DAT_80436398 + 0x18),in_r6);
          zz_0044e08_();
          zz_005809c_(DAT_803c71dc,1);
          zz_005814c_(DAT_803c4e84,*(undefined2 *)(DAT_80436398 + 0x18),DAT_80436398[0x1a]);
          fVar4 = FLOAT_8043c06c;
          *(float *)(DAT_80436398 + 0x1c) = FLOAT_8043c068;
          *(float *)(DAT_80436398 + 0x24) = fVar4;
          *(float *)(DAT_80436398 + 0x20) = fVar4;
          param_1 = zz_0057fac_(DAT_803c4e84,(undefined4 *)(DAT_80436398 + 0x1c));
        }
        else {
          uVar8 = zz_0044920_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_80436398[0x14] + 7,uVar6,DAT_80436398,in_r6,in_r7,in_r8,in_r9,
                              in_r10);
          param_1 = zz_0044cf4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,
                                *(short *)(DAT_80436398 + 0x18));
        }
      }
      else if (cVar1 < '\0') {
        return;
      }
      iVar5 = zz_000a3c4_();
      pcVar2 = DAT_80436398;
      if (iVar5 != 0) {
        return;
      }
      DAT_80436398[1] = DAT_80436398[1] + '\x01';
      pcVar3 = DAT_80436398;
      DAT_80436398[0x6b] = '\x01';
      zz_0008ca8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb354,
                  pcVar3,pcVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
      zz_008c3a0_(9);
      zz_01dd60c_();
      zz_01dd63c_();
      zz_01dd7d4_();
      if (DAT_80436398[0x67] == '\x01') {
        zz_01eee28_();
      }
      zz_002a5f4_(0x40,0xa6,0xc0,0xff);
      zz_0027aac_(0,0x10,0);
      fVar4 = FLOAT_8043c06c;
      pcVar2 = DAT_80436398;
      pcVar2[4] = '\0';
      pcVar2[5] = '\0';
      *(float *)(DAT_80436398 + 0x34) = fVar4;
      return;
    }
    if (cVar1 == '\x04') {
      iVar5 = zz_0027adc_();
      if (iVar5 != 0) {
        return;
      }
      *DAT_80436398 = *DAT_80436398 + '\x01';
      DAT_80436398[1] = '\0';
      DAT_80436398[0x6b] = '\x02';
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar5 = zz_0182040_((short *)(DAT_80436398 + 4),(float *)(DAT_80436398 + 0x34),0x10);
  if (iVar5 != 0) {
    DAT_80436398[1] = DAT_80436398[1] + '\x01';
  }
  if (DAT_80436398[0x67] == '\0') {
    dVar9 = zz_01820c4_((double)*(float *)(DAT_80436398 + 0x34),(double)FLOAT_8043c074);
    *(float *)(DAT_803c4e84 + 0x28) = (float)((double)FLOAT_8043c070 + dVar9);
  }
  return;
}



// ==== 801dcd30  FUN_801dcd30 ====

void FUN_801dcd30(void)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  
  cVar1 = DAT_80436398[0x6a];
  cVar2 = DAT_80436398[0x69];
  iVar4 = (int)DAT_80436398[0x68];
  DAT_80436398[0x6a] = cVar1 + '\x01';
  if ('F' < (char)(cVar1 + '\x01')) {
    DAT_80436398[0x6a] = '\0';
  }
  uVar3 = *(uint *)(DAT_80436398 + 0xc);
  if ((uVar3 & 0x200) == 0) {
    if ((uVar3 & 0x20002) == 0) {
      if ((uVar3 & 0x10001) == 0) {
        return;
      }
      do {
        iVar4 = iVar4 + -1;
        if (iVar4 < 0) {
          iVar4 = 3;
        }
      } while (((int)cVar2 & 1 << iVar4) == 0);
    }
    else {
      do {
        iVar4 = iVar4 + 1;
        if (3 < iVar4) {
          iVar4 = 0;
        }
      } while (((int)cVar2 & 1 << iVar4) == 0);
    }
    if (DAT_80436398[0x68] != iVar4) {
      DAT_80436398[0x68] = (char)iVar4;
      DAT_80436398[0x6a] = '\0';
      zz_00f03c0_(0,0x77);
    }
  }
  else {
    *DAT_80436398 = *DAT_80436398 + '\x01';
    DAT_80436398[1] = '\0';
    zz_00f03c0_(0,0x7b);
  }
  return;
}



// ==== 801dce4c  FUN_801dce4c ====

void FUN_801dce4c(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  
  cVar1 = *(char *)(DAT_80436398 + 1);
  if (cVar1 == '\x01') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      *(char *)(DAT_80436398 + 1) = *(char *)(DAT_80436398 + 1) + '\x01';
      *(undefined2 *)(DAT_80436398 + 4) = 4;
      *(undefined1 *)(DAT_80436398 + 0x17) = 1;
      if (*(char *)(DAT_80436398 + 0x67) == '\0') {
        *(undefined1 *)(DAT_803c4e84 + 0x18) = 2;
      }
      zz_002a5f4_(0,0,0,0xff);
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(DAT_80436398 + 1) = cVar1 + '\x01';
      zz_0027aac_(0,0x10,1);
    }
  }
  else if ((cVar1 < '\x03') &&
          (sVar3 = *(short *)(DAT_80436398 + 4) + -1, *(short *)(DAT_80436398 + 4) = sVar3,
          sVar3 < 1)) {
    zz_008c3a0_(6);
    zz_0027c1c_();
    if (*(char *)(DAT_80436398 + 0x67) == '\0') {
      zz_0041b58_(0);
    }
    else {
      zz_0044ddc_();
    }
    zz_00f0a60_();
    zz_0044630_();
    zz_0008cf4_();
    *(undefined1 *)(DAT_80436398 + 0x17) = 2;
  }
  return;
}



// ==== 801dcf7c  zz_01dcf7c_ ====

void zz_01dcf7c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  zz_01dcfa0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_01dd208_();
  return;
}



// ==== 801dcfa0  zz_01dcfa0_ ====

void zz_01dcfa0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  if ((*(uint *)(DAT_80436398 + 8) & 0x800000) != 0) {
    *(int *)(DAT_80436398 + 0x28) = *(int *)(DAT_80436398 + 0x28) + 0x180;
  }
  if ((*(uint *)(DAT_80436398 + 8) & 0x400000) != 0) {
    *(int *)(DAT_80436398 + 0x28) = *(int *)(DAT_80436398 + 0x28) + -0x180;
  }
  if ((*(uint *)(DAT_80436398 + 8) & 0x100000) != 0) {
    *(int *)(DAT_80436398 + 0x2c) = *(int *)(DAT_80436398 + 0x2c) + 0x180;
  }
  if ((*(uint *)(DAT_80436398 + 8) & 0x200000) != 0) {
    *(int *)(DAT_80436398 + 0x2c) = *(int *)(DAT_80436398 + 0x2c) + -0x180;
  }
  if (*(char *)(DAT_80436398 + 0x67) == '\0') {
    if (*(char *)(DAT_80436398 + 0x17) == '\0') {
      if (*(char *)(DAT_80436398 + 0x6b) != '\x01') {
        if ('\0' < *(char *)(DAT_80436398 + 0x6c)) {
          *(char *)(DAT_80436398 + 0x6c) = *(char *)(DAT_80436398 + 0x6c) + -1;
        }
        iVar2 = DAT_80436398;
        iVar1 = DAT_803c4e84;
        if ((*(char *)(DAT_80436398 + 0x6c) == '\0') &&
           ((*(uint *)(DAT_80436398 + 0xc) & 0x100) != 0)) {
          if ((1 << (*(byte *)(DAT_803c4e84 + 0x3e9) & 0x1f) &
              *(uint *)(*(char *)(DAT_803c4e84 + 1000) * 8 + -0x7fd22b00 +
                       (*(byte *)(DAT_803c4e84 + 0x3e9) >> 3 & 4))) != 0) {
            uVar3 = *(undefined4 *)(DAT_80436398 + 0x20);
            *(undefined4 *)(DAT_803c4e84 + 0x20) = *(undefined4 *)(DAT_80436398 + 0x1c);
            *(undefined4 *)(iVar1 + 0x24) = uVar3;
            *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(iVar2 + 0x24);
            *(undefined1 *)(DAT_803c4e84 + 0x5da) = 0x3c;
            *(undefined1 *)(DAT_803c4e84 + 0x5db) = 0x3c;
            *(undefined2 *)(DAT_803c4e84 + 0x5ae) = *(undefined2 *)(DAT_803c4e84 + 0x72);
            zz_0057ff8_(DAT_803c4e84,0,0x28);
            *(undefined1 *)(DAT_80436398 + 0x6c) = 0x3c;
          }
        }
        else if ((*(uint *)(DAT_80436398 + 0xc) & 0xc00) != 0) {
          *(undefined4 *)(DAT_80436398 + 0x28) = 0x800;
          *(undefined4 *)(DAT_80436398 + 0x2c) = 0;
          iVar2 = DAT_80436398;
          iVar1 = DAT_803c4e84;
          uVar3 = *(undefined4 *)(DAT_80436398 + 0x20);
          *(undefined4 *)(DAT_803c4e84 + 0x20) = *(undefined4 *)(DAT_80436398 + 0x1c);
          *(undefined4 *)(iVar1 + 0x24) = uVar3;
          *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(iVar2 + 0x24);
          *(undefined1 *)(DAT_803c4e84 + 0x5da) = 0;
          *(undefined1 *)(DAT_803c4e84 + 0x5db) = 0;
          zz_0057ff8_(DAT_803c4e84,0,0);
          *(undefined1 *)(DAT_80436398 + 0x6c) = 0;
        }
        *(short *)(DAT_803c4e84 + 0x72) = (short)*(undefined4 *)(DAT_80436398 + 0x2c);
      }
      FUN_801dd6b0();
    }
    zz_0058160_();
    zz_0089898_(1);
    zz_0089898_(0x39);
    *(int *)(PTR_DAT_80433934 + 0xb0) = *(int *)(PTR_DAT_80433934 + 0xb0) + 1;
    zz_0089554_();
    zz_008972c_();
    uVar4 = zz_0053a94_();
    uVar4 = zz_00897a4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,9);
    uVar4 = zz_00897a4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x19);
    zz_00897a4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x31);
    return;
  }
  zz_0089898_(0x39);
  zz_0089554_();
  return;
}



// ==== 801dd208  zz_01dd208_ ====

void zz_01dd208_(void)

{
  if (*(char *)(DAT_80436398 + 0x17) == '\0') {
    zz_008a16c_();
    if (*(char *)(DAT_80436398 + 0x67) == '\0') {
      zz_0053928_();
      zz_0089c00_(1);
      zz_0089c00_(0x39);
      zz_008c0dc_(FUN_80089eb4);
      zz_008c0dc_(FUN_8008a010);
      zz_008c0dc_(FUN_8008a0a8);
    }
    else {
      zz_0089c00_(0x39);
      zz_008c0dc_(FUN_80089eb4);
    }
  }
  return;
}



// ==== 801dd298  zz_01dd298_ ====

void zz_01dd298_(undefined2 *param_1)

{
  int iVar1;
  undefined2 local_28 [2];
  undefined2 local_24 [2];
  undefined2 local_20 [2];
  undefined2 local_1c [2];
  undefined2 local_18 [10];
  
  *(undefined1 *)(DAT_80436398 + 0x67) = 0;
  *(undefined1 *)(DAT_80436398 + 0x68) = 1;
  *(undefined1 *)(DAT_80436398 + 0x69) = 7;
  local_18[0] = *param_1;
  iVar1 = zz_00661d8_((char *)local_18);
  *(int *)(DAT_80436398 + 0x38) = iVar1;
  *(undefined2 *)(DAT_80436398 + 0x18) = *param_1;
  *(undefined1 *)(DAT_80436398 + 0x1a) = *(undefined1 *)(param_1 + 1);
  if ((&DAT_803bfe78)[*(int *)(DAT_80436398 + 0x38)] == '\0') {
    *(byte *)(DAT_80436398 + 0x69) = *(byte *)(DAT_80436398 + 0x69) & 0xfb;
  }
  local_1c[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_0066168_((char *)local_1c,(int)*(char *)(DAT_80436398 + 0x1a));
  *(int *)(DAT_80436398 + 0x3c) = iVar1;
  *(undefined1 *)(DAT_80436398 + 0x4c) = *(undefined1 *)((int)param_1 + 3);
  local_20[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_0066298_((char *)local_20);
  *(char *)(DAT_80436398 + 0x4e) = (char)iVar1;
  local_24[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_00662c0_((char *)local_24,(int)*(char *)(DAT_80436398 + 0x1a));
  *(char *)(DAT_80436398 + 0x4d) = (char)iVar1;
  local_28[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_0066198_((char *)local_28,(int)*(char *)(DAT_80436398 + 0x1a),
                      (int)*(char *)(DAT_80436398 + 0x4c));
  *(int *)(DAT_80436398 + 0x40) = iVar1;
  *(undefined4 *)(DAT_80436398 + 0x44) = *(undefined4 *)(param_1 + 4);
  return;
}



// ==== 801dd3e8  zz_01dd3e8_ ====

void zz_01dd3e8_(void)

{
  int iVar1;
  undefined *puVar2;
  undefined1 uVar4;
  undefined *puVar3;
  char *pcVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  zz_0056ce0_(DAT_803c4e84);
  iVar10 = *(int *)(DAT_803c4e84 + 0x4ac);
  *(undefined1 *)(DAT_80436398 + 0x4f) = *(undefined1 *)(iVar10 + 0x1a0);
  if (*(char *)(iVar10 + 0x1a2) == '\0') {
    uVar4 = *(undefined1 *)(iVar10 + 0x1a1);
  }
  else {
    uVar4 = 6;
  }
  cVar6 = '\0';
  iVar1 = 5;
  pcVar5 = (char *)(iVar10 + 0x1a8);
  *(undefined1 *)(DAT_80436398 + 0x50) = uVar4;
  iVar7 = 0;
  puVar2 = &DAT_80435b40;
  puVar3 = &DAT_80435b48;
  *(undefined1 *)(DAT_80436398 + 0x48) = *(undefined1 *)(iVar10 + 0x1a4);
  *(undefined1 *)(DAT_80436398 + 0x49) = *(undefined1 *)(iVar10 + 0x1a5);
  *(undefined1 *)(DAT_80436398 + 0x4a) = *(undefined1 *)(iVar10 + 0x1a6);
  *(undefined1 *)(DAT_80436398 + 0x4b) = *(undefined1 *)(iVar10 + 0x1a7);
  *(undefined1 *)(DAT_80436398 + 0x51) = *(undefined1 *)(iVar10 + 0x1a3);
  do {
    if (*pcVar5 != -1) {
      iVar9 = iVar7 + 0x58;
      iVar8 = iVar7 + 0x5d;
      *(char *)(DAT_80436398 + iVar7 + 0x53) = cVar6;
      iVar10 = iVar7 + 0x62;
      iVar7 = iVar7 + 1;
      *(undefined *)(DAT_80436398 + iVar9) = *puVar2;
      *(undefined *)(DAT_80436398 + iVar8) = *puVar3;
      *(char *)(DAT_80436398 + iVar10) = *pcVar5;
    }
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
    cVar6 = cVar6 + '\x01';
    pcVar5 = pcVar5 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(char *)(DAT_80436398 + 0x52) = (char)iVar7;
  if (iVar7 == 0) {
    *(byte *)(DAT_80436398 + 0x69) = *(byte *)(DAT_80436398 + 0x69) & 0xfb;
  }
  return;
}



// ==== 801dd530  zz_01dd530_ ====

void zz_01dd530_(undefined2 *param_1)

{
  int iVar1;
  undefined2 local_8 [2];
  undefined2 local_4 [2];
  
  *(undefined1 *)(DAT_80436398 + 0x67) = 1;
  *(undefined1 *)(DAT_80436398 + 0x68) = 3;
  *(undefined1 *)(DAT_80436398 + 0x69) = 8;
  *(undefined2 *)(DAT_80436398 + 0x18) = *param_1;
  *(undefined1 *)(DAT_80436398 + 0x1a) = *(undefined1 *)((int)param_1 + 3);
  *(undefined1 *)(DAT_80436398 + 0x1b) = *(undefined1 *)(param_1 + 1);
  local_4[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_00661d8_((char *)local_4);
  *(int *)(DAT_80436398 + 0x38) = iVar1;
  local_8[0] = *(undefined2 *)(DAT_80436398 + 0x18);
  iVar1 = zz_00662c0_((char *)local_8,(int)*(char *)(DAT_80436398 + 0x1a));
  *(char *)(DAT_80436398 + 0x4d) = (char)iVar1;
  return;
}



// ==== 801dd5d4  zz_01dd5d4_ ====

void zz_01dd5d4_(int param_1,undefined2 *param_2)

{
  if (param_1 == 0) {
    zz_01dd298_(param_2);
  }
  else {
    zz_01dd530_(param_2);
  }
  return;
}



// ==== 801dd60c  zz_01dd60c_ ====

void zz_01dd60c_(void)

{
  if (*(char *)(DAT_80436398 + 0x67) == '\0') {
    zz_01dd3e8_();
  }
  return;
}



// ==== 801dd63c  zz_01dd63c_ ====

void zz_01dd63c_(void)

{
  *(undefined4 *)(DAT_80436398 + 0x28) = 0x800;
  *(undefined4 *)(DAT_80436398 + 0x2c) = 0;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_80390a88,(float *)&DAT_80390aa0,
                      (float *)&DAT_80390a94);
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  PTR_DAT_80433930[0xe] = 0;
  return;
}



// ==== 801dd6b0  FUN_801dd6b0 ====

/* WARNING: Removing unreachable block (ram,0x801dd7b8) */
/* WARNING: Removing unreachable block (ram,0x801dd6c0) */

void FUN_801dd6b0(void)

{
  bool bVar1;
  uint uVar2;
  short sVar3;
  double dVar4;
  double dVar5;
  
  bVar1 = false;
  uVar2 = *(uint *)(DAT_80436398 + 0x28) & 0xffff;
  if ((0x3fff < uVar2) && (uVar2 < 0xc001)) {
    bVar1 = true;
  }
  DAT_80390ac8 = FLOAT_8043c07c;
  if (bVar1) {
    DAT_80390ac8 = FLOAT_8043c078;
  }
  sVar3 = (short)*(uint *)(DAT_80436398 + 0x28);
  dVar5 = (double)*(float *)(DAT_803c4e84 + 0x66c);
  dVar4 = zz_0045204_(sVar3);
  DAT_80390ab0 = (float)((double)FLOAT_8043c080 * dVar4 + dVar5);
  dVar4 = zz_0045238_(sVar3);
  DAT_80390ab4 = (float)((double)FLOAT_8043c080 * dVar4);
  DAT_80390abc = (float)dVar5;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_80390aac,(float *)&DAT_80390ac4,
                      (float *)&DAT_80390ab8);
  DAT_803c7698 = DAT_80390aac;
  DAT_803c769c = DAT_80390ab0;
  DAT_803c76a0 = DAT_80390ab4;
  DAT_803c76e0 = DAT_80390ac4;
  DAT_803c76e4 = DAT_80390ac8;
  DAT_803c76e8 = DAT_80390acc;
  return;
}



// ==== 801dd7d4  zz_01dd7d4_ ====

void zz_01dd7d4_(void)

{
  int *piVar1;
  
  for (piVar1 = &DAT_80390ad0; -1 < *piVar1; piVar1 = piVar1 + 5) {
    zz_01dd820_(piVar1);
  }
  return;
}



// ==== 801dd820  zz_01dd820_ ====

void zz_01dd820_(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,0x39,1,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0;
    puVar2[0x11] = (char)*(undefined2 *)(param_1 + 1);
    puVar2[0x12] = (char)*(undefined2 *)((int)param_1 + 6);
    *(code **)(puVar2 + 0xc) = FUN_801dd8d8;
    *(code **)(puVar2 + 0x10c) = FUN_801de9e0;
    *(undefined4 *)(puVar2 + 0x144) = *param_1;
    uVar1 = param_1[2];
    *(undefined4 *)(puVar2 + 100) = uVar1;
    *(undefined4 *)(puVar2 + 0x148) = uVar1;
    uVar1 = param_1[3];
    *(undefined4 *)(puVar2 + 0x68) = uVar1;
    *(undefined4 *)(puVar2 + 0x14c) = uVar1;
    uVar1 = param_1[4];
    *(undefined4 *)(puVar2 + 0x6c) = uVar1;
    *(undefined4 *)(puVar2 + 0x150) = uVar1;
    *(undefined4 *)(puVar2 + 0x154) = DAT_803bb354;
  }
  return;
}



// ==== 801dd8d8  FUN_801dd8d8 ====

void FUN_801dd8d8(int param_1)

{
  (*(code *)(&PTR_FUN_8039131c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801dd914  FUN_801dd914 ====

void FUN_801dd914(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043c088;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  *(undefined4 *)(param_9 + 0x17c) = 0xffffffff;
  zz_01dd9a4_(param_9);
  return;
}



// ==== 801dd9a4  zz_01dd9a4_ ====

void zz_01dd9a4_(int param_1)

{
  (*(code *)(&PTR_LAB_8039132c)[*(char *)(param_1 + 0x11)])();
  if ((*(byte *)(DAT_80436398 + 0x17) & 1) != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801ddb28  FUN_801ddb28 ====

void FUN_801ddb28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  bVar1 = *(byte *)(param_9 + 0x19);
  if (bVar1 == 1) {
    return;
  }
  if ('\0' < (char)bVar1) {
    return;
  }
  if ((char)bVar1 < '\0') {
    return;
  }
  if (*(char *)(DAT_80436398 + 0x67) != '\x01') {
    *(byte *)(param_9 + 0x19) = bVar1 + 1;
    if (*(char *)(param_9 + 0x12) < '\x03') {
      iVar3 = zz_01dea3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *(int *)(DAT_80436398 + 0x38) + 1,3,1,param_13,param_14,param_15,param_16)
      ;
      if (iVar3 == 0) {
        return;
      }
      *(float *)(param_9 + 100) =
           FLOAT_8043c098 *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12) ^ 0x80000000) -
                  DOUBLE_8043c0a0) + *(float *)(param_9 + 0x148);
      return;
    }
    uVar2 = (int)*(char *)(DAT_80436398 + 0x1a) - 1;
    if (-1 < (int)uVar2) {
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c0a0)
                  ,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  (float *)(uint)bVar1,param_12,param_13,param_14,param_15,param_16);
      *(undefined1 *)(param_9 + 0x82) = 3;
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 801ddc3c  FUN_801ddc3c ====

void FUN_801ddc3c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    return;
  }
  if ('\0' < cVar1) {
    return;
  }
  if (cVar1 < '\0') {
    return;
  }
  *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  if (*(char *)(DAT_80436398 + 0x67) != '\x01') {
    if (*(char *)(param_9 + 0x12) < '\0') {
      *(undefined1 *)(param_9 + 0x82) = 3;
      return;
    }
    iVar2 = zz_01dea3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        *(int *)(DAT_80436398 + 0x3c),6,0,in_r7,in_r8,in_r9,in_r10);
    if (iVar2 != 0) {
      *(float *)(param_9 + 100) =
           FLOAT_8043c0a8 *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12) ^ 0x80000000) -
                  DOUBLE_8043c0a0) + *(float *)(param_9 + 0x148);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 801ddd0c  FUN_801ddd0c ====

void FUN_801ddd0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    return;
  }
  if ('\0' < cVar1) {
    return;
  }
  if (cVar1 < '\0') {
    return;
  }
  *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  if (*(char *)(DAT_80436398 + 0x67) != '\x01') {
    if (*(char *)(param_9 + 0x12) < '\0') {
      *(undefined1 *)(param_9 + 0x82) = 3;
      return;
    }
    iVar2 = zz_01dea3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        *(char *)(DAT_80436398 + 0x4c) + 1,2,0,in_r7,in_r8,in_r9,in_r10);
    if (iVar2 != 0) {
      *(float *)(param_9 + 100) =
           FLOAT_8043c0a8 *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12) ^ 0x80000000) -
                  DOUBLE_8043c0a0) + *(float *)(param_9 + 0x148);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 801dde64  FUN_801dde64 ====

void FUN_801dde64(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)(DAT_80436398 + 0x67) == '\x01') {
      if ((*(char *)(param_9 + 0x12) == '\x01') || (*(char *)(param_9 + 0x12) == '\x02')) {
        *(undefined1 *)(param_9 + 0x18) = 2;
        return;
      }
      param_1 = (double)*(float *)(param_9 + 100);
      *(float *)(param_9 + 100) = (float)(param_1 + (double)FLOAT_8043c0ac);
    }
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 0x82) = 3;
  }
  if ('\x01' < *(char *)(param_9 + 0x12)) {
    sVar3 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (0x3c < sVar3) {
      *(undefined2 *)(param_9 + 0x1c) = 0;
    }
    uVar4 = (uint)*(short *)(param_9 + 0x1c);
    iVar5 = *(int *)(param_9 + 0x144);
    iVar2 = *(int *)(param_9 + 0x180) + ((int)uVar4 >> 0x1f) + (uint)(0x1d < uVar4);
    if (iVar5 != iVar2) {
      *(int *)(param_9 + 0x144) = iVar2;
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  (int)uVar4 >> 0x1f,uVar4,*(int *)(param_9 + 0x180),iVar5,in_r9,in_r10);
    }
  }
  return;
}



// ==== 801ddf70  FUN_801ddf70 ====

void FUN_801ddf70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (((cVar1 != '\x01') && (cVar1 < '\x01')) && (-1 < cVar1)) {
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    if (*(char *)(param_9 + 0x12) == '\0') {
      uVar2 = (int)*(char *)(DAT_80436398 + 0x1a) - 1;
      if ((int)uVar2 < 0) {
        *(undefined1 *)(param_9 + 0x18) = 2;
        return;
      }
      if (*(char *)(DAT_80436398 + 0x67) == '\x01') {
        *(float *)(param_9 + 100) = FLOAT_8043c0b0;
      }
    }
    else {
      uVar2 = (uint)*(char *)(DAT_80436398 + 0x4d);
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c0a0),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,param_12,
                param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 3;
  }
  return;
}



// ==== 801de040  FUN_801de040 ====

void FUN_801de040(int param_1)

{
  if (((*(char *)(param_1 + 0x19) == '\0') && (*(char *)(param_1 + 0x12) == '\x02')) &&
     (*(char *)(DAT_80436398 + 0x51) < '\0')) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    zz_01deb3c_(param_1,1);
  }
  return;
}



// ==== 801de09c  FUN_801de09c ====

void FUN_801de09c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  float *pfVar2;
  
  dVar1 = DOUBLE_8043c0a0;
  if (*(char *)(param_9 + 0x19) == '\0') {
    pfVar2 = (float *)(*(char *)(DAT_80436398 + 0x50) + -1);
    if ((int)pfVar2 < 0) {
      *(undefined1 *)(param_9 + 0x82) = 0;
      return;
    }
    if ((*(char *)(param_9 + 0x12) != '\0') && (*(float **)(param_9 + 0x180) != pfVar2)) {
      *(float **)(param_9 + 0x180) = pfVar2;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar2 ^ 0x80000000) - dVar1),
                  param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar2,param_12,
                  param_13,param_14,param_15,param_16);
    }
  }
  zz_01deb3c_(param_9,1);
  return;
}



// ==== 801de140  FUN_801de140 ====

void FUN_801de140(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (((cVar1 != '\x01') && (cVar1 < '\x01')) && (-1 < cVar1)) {
    iVar2 = 4;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    iVar3 = *(char *)(param_9 + 0x11) + -0xc;
    if (iVar3 != 0) {
      iVar2 = 6;
    }
    iVar2 = zz_01dea3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        *(int *)(DAT_80436398 + iVar3 * 4 + 0x40),iVar2,0,in_r7,in_r8,in_r9,in_r10);
    if (iVar2 == 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    *(float *)(param_9 + 100) =
         (*(float *)(param_9 + 0x148) -
         (float)((double)CONCAT44(0x43300000,((iVar2 + -1) * 0x32) / 2 ^ 0x80000000) -
                DOUBLE_8043c0a0)) +
         (float)((double)CONCAT44(0x43300000,
                                  ((iVar2 + -1) - (int)*(char *)(param_9 + 0x12)) * 0x32 ^
                                  0x80000000) - DOUBLE_8043c0a0);
  }
  zz_01deb3c_(param_9,1);
  return;
}



// ==== 801de248  FUN_801de248 ====

void FUN_801de248(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  float *pfVar2;
  
  dVar1 = DOUBLE_8043c0a0;
  if ((*(char *)(param_9 + 0x19) == '\0') &&
     (pfVar2 = (float *)(int)*(char *)(DAT_80436398 + *(char *)(param_9 + 0x12) + 0x48),
     *(float **)(param_9 + 0x180) != pfVar2)) {
    *(float **)(param_9 + 0x180) = pfVar2;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar2 ^ 0x80000000) - dVar1),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar2,param_12,
                param_13,param_14,param_15,param_16);
  }
  zz_01deb3c_(param_9,1);
  return;
}



// ==== 801de384  FUN_801de384 ====

void FUN_801de384(int param_1)

{
  if (*(char *)(param_1 + 0x19) == '\0') {
    if ((int)*(char *)(DAT_80436398 + 0x52) <= (int)*(char *)(param_1 + 0x12)) {
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    *(float *)(param_1 + 0x68) =
         *(float *)(param_1 + 0x14c) -
         (float)((double)CONCAT44(0x43300000,*(char *)(param_1 + 0x12) * 0xf0 ^ 0x80000000) -
                DOUBLE_8043c0a0);
  }
  zz_01deb3c_(param_1,2);
  return;
}



// ==== 801de40c  FUN_801de40c ====

void FUN_801de40c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801de4e0;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x144);
  }
  dVar2 = DOUBLE_8043c0a0;
  if ((int)*(char *)(DAT_80436398 + 0x52) <= (int)*(char *)(param_9 + 0x12)) {
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  *(float *)(param_9 + 0x68) =
       (float)((double)*(float *)(param_9 + 0x14c) -
              (double)(float)((double)CONCAT44(0x43300000,
                                               *(char *)(param_9 + 0x12) * 0xf0 ^ 0x80000000) -
                             DOUBLE_8043c0a0));
  iVar4 = *(int *)(param_9 + 0x144);
  iVar3 = *(int *)(param_9 + 0x180) +
          (int)*(char *)(DAT_80436398 + *(char *)(param_9 + 0x12) + 0x58);
  if (iVar4 != iVar3) {
    *(int *)(param_9 + 0x144) = iVar3;
    zz_01a7688_(dVar2,(double)*(float *)(param_9 + 0x14c),param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,iVar4,param_12,param_13,param_14,param_15,param_16);
  }
LAB_801de4e0:
  zz_01deb3c_(param_9,2);
  return;
}



// ==== 801de500  FUN_801de500 ====

void FUN_801de500(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  double dVar1;
  float *pfVar2;
  uint uVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  dVar1 = DOUBLE_8043c0a0;
  if (*(char *)(param_9 + 0x19) == '\0') {
    pfVar2 = (float *)(int)*(char *)(param_9 + 0x12);
    if (((int)*(char *)(DAT_80436398 + 0x52) <= (int)pfVar2) ||
       (uVar3 = (int)*(char *)((int)pfVar2 + DAT_80436398 + 0x5d) - 1, (int)uVar3 < 0)) {
      *(undefined1 *)(param_9 + 0x82) = 0;
      return;
    }
    *(float *)(param_9 + 0x68) =
         (float)((double)*(float *)(param_9 + 0x14c) -
                (double)(float)((double)CONCAT44(0x43300000,(int)pfVar2 * 0xf0 ^ 0x80000000) -
                               DOUBLE_8043c0a0));
    if (*(uint *)(param_9 + 0x180) != uVar3) {
      *(uint *)(param_9 + 0x180) = uVar3;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar1),
                  (double)*(float *)(param_9 + 0x14c),param_3,param_4,param_5,param_6,param_7,
                  param_8,param_9,0,pfVar2,uVar3,in_r7,in_r8,in_r9,in_r10);
    }
  }
  zz_01deb3c_(param_9,2);
  return;
}



// ==== 801de5d8  FUN_801de5d8 ====

void FUN_801de5d8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  double dVar1;
  float *pfVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  dVar1 = DOUBLE_8043c0a0;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if ((int)*(char *)(DAT_80436398 + 0x52) <= (int)*(char *)(param_9 + 0x12)) {
      *(undefined1 *)(param_9 + 0x82) = 0;
      return;
    }
    *(float *)(param_9 + 0x68) =
         (float)((double)*(float *)(param_9 + 0x14c) -
                (double)(float)((double)CONCAT44(0x43300000,
                                                 *(char *)(param_9 + 0x12) * 0xf0 ^ 0x80000000) -
                               DOUBLE_8043c0a0));
    pfVar2 = (float *)(int)*(char *)(DAT_80436398 + *(char *)(param_9 + 0x12) + 0x62);
    if (*(float **)(param_9 + 0x180) != pfVar2) {
      *(float **)(param_9 + 0x180) = pfVar2;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar2 ^ 0x80000000) - dVar1),
                  (double)*(float *)(param_9 + 0x14c),param_3,param_4,param_5,param_6,param_7,
                  param_8,param_9,0,pfVar2,0x43300000,in_r7,in_r8,in_r9,in_r10);
    }
  }
  zz_01deb3c_(param_9,2);
  return;
}



// ==== 801de6c8  FUN_801de6c8 ====

void FUN_801de6c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801de6e8  zz_01de6e8_ ====

void zz_01de6e8_(int param_1)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  byte *pbVar4;
  undefined2 local_38 [2];
  byte abStack_34 [48];
  
  switch(*(undefined1 *)(param_1 + 0x11)) {
  case 3:
    if (*(char *)(DAT_80436398 + 0x67) == '\0') {
      zz_01e19f4_(0x8c,0x20,0xe0,0x20,0xff);
    }
    else {
      zz_01e1b54_(0x8e,0x20,*(undefined2 *)(DAT_80436398 + 0x18),(int)*(char *)(DAT_80436398 + 0x1a)
                  ,(int)*(char *)(DAT_80436398 + 0x1b),0xff);
    }
    break;
  case 10:
    if (*(char *)(param_1 + 0x12) == '\x01') {
      zz_0096d0c_((double)FLOAT_8043c0b4);
      zz_0096d14_((double)FLOAT_8043c0b8);
      pbVar4 = (&PTR_DAT_803912a4)[*(char *)(DAT_80436398 + 0x4e)];
      sVar2 = strlen((char *)pbVar4);
      zz_0097144_(0x200 - (short)(sVar2 << 1),0x60,8,pbVar4);
      pbVar4 = (&PTR_DAT_803912f4)[*(char *)(DAT_80436398 + 0x4f)];
      sVar2 = strlen((char *)pbVar4);
      zz_0097144_(0x200 - (short)(sVar2 << 1),0x81,8,pbVar4);
      if (-1 < *(char *)(DAT_80436398 + 0x51)) {
        pbVar4 = (&PTR_DAT_80391308)[*(char *)(DAT_80436398 + 0x51)];
        sVar2 = strlen((char *)pbVar4);
        zz_0097144_(0x200 - (short)(sVar2 << 1),0x18d,8,pbVar4);
      }
    }
    break;
  case 0xf:
    zz_0096d0c_((double)FLOAT_8043c088);
    zz_0096d14_((double)FLOAT_8043c0bc);
    if (*(char *)(DAT_80436398 + 0x67) == '\0') {
      zz_00970b4_(0x177,0x87,9,'\0',(short)*(undefined4 *)(DAT_80436398 + 0x38),-1);
    }
    else {
      iVar1 = zz_01cee00_((int)*(short *)(DAT_80436398 + 0x18));
      sprintf((char *)abStack_34,&DAT_802b3b18,(&PTR_DAT_80390a40)[iVar1]);
      sVar2 = strlen((char *)abStack_34);
      zz_0097144_((short)((0x2c - sVar2) * 0x14 >> 3) + 0x177,0xb7,9,abStack_34);
      sprintf((char *)abStack_34,&DAT_802b3b40);
      sVar2 = strlen((char *)abStack_34);
      zz_0097144_((short)((0x2c - sVar2) * 0x14 >> 3) + 0x177,0xe7,9,abStack_34);
      local_38[0] = *(undefined2 *)(DAT_80436398 + 0x18);
      uVar3 = zz_0066270_((char *)local_38);
      sprintf((char *)abStack_34,&DAT_8043c0c0,uVar3);
      sVar2 = strlen((char *)abStack_34);
      zz_0097144_((short)((0x2e - sVar2) * 0x14 >> 3) + 0x177,0x117,9,abStack_34);
    }
    break;
  case 0x12:
    zz_0096d0c_((double)FLOAT_8043c0c8);
    zz_0096d14_((double)FLOAT_8043c0cc);
    zz_00970b4_(0x1a0,*(char *)(param_1 + 0x12) * 0x43 + 0x79,8,'\x01',
                (short)*(char *)(DAT_80436398 + *(char *)(param_1 + 0x12) + 0x53) +
                (short)*(undefined4 *)(DAT_80436398 + 0x38) * 5,-1);
  }
  return;
}



// ==== 801de9e0  FUN_801de9e0 ====

void FUN_801de9e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = zz_01de6e8_(param_9);
  if (*(char *)(param_9 + 0x11) == '\x01') {
    zz_00076d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x25);
  }
  else {
    zz_01a77e8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801dea3c  zz_01dea3c_ ====

int zz_01dea3c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
               int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  if (param_12 == 0) {
    iVar2 = param_11 + -1;
    iVar3 = 1;
    piVar4 = &DAT_80391290;
    if (1 < param_11) {
      do {
        if (param_10 < *piVar4) break;
        piVar4 = piVar4 + 1;
        iVar3 = iVar3 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    param_11 = iVar3;
    if (iVar3 <= *(char *)(param_9 + 0x12)) {
      return 0;
    }
  }
  iVar2 = *(char *)(param_9 + 0x12) * 4;
  iVar5 = param_10 / *(int *)(&DAT_8039128c + iVar2);
  iVar3 = iVar5 / 10 + (iVar5 >> 0x1f);
  pfVar1 = (float *)-(iVar3 >> 0x1f);
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               iVar5 + (iVar3 + (int)pfVar1) * -10 ^ 0x80000000) -
                             DOUBLE_8043c0a0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,pfVar1,iVar5,iVar2,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 3;
  return param_11;
}



// ==== 801deb3c  zz_01deb3c_ ====

void zz_01deb3c_(int param_1,int param_2)

{
  if (*(char *)(DAT_80436398 + 0x68) == param_2) {
    *(undefined1 *)(param_1 + 0x82) = 3;
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801deb68  zz_01deb68_ ====

void zz_01deb68_(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  undefined1 *puVar1;
  int *piVar2;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x20;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801dec90;
    *(code **)(puVar1 + 0x10c) = FUN_801df498;
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
    *(undefined4 *)(puVar1 + 0x18c) = param_3;
    *(undefined4 *)(puVar1 + 400) = param_4;
    *(undefined4 *)(puVar1 + 0x19c) = param_5;
    piVar2 = zz_0006dc8_(0x40);
    *(int **)(puVar1 + 0xdc) = piVar2;
    if (piVar2 == (int *)0x0) {
      puVar1[0x18] = 2;
    }
  }
  return;
}



// ==== 801dec90  FUN_801dec90 ====

void FUN_801dec90(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_80391648)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801dece0  FUN_801dece0 ====

void FUN_801dece0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  short *psVar12;
  int *piVar13;
  int iVar14;
  undefined8 uVar15;
  double dVar16;
  
  uVar1 = (uint)*(byte *)(param_9 + 0x11);
  iVar14 = *(int *)(param_9 + 0x90);
  iVar7 = uVar1 * 0x28;
  piVar13 = *(int **)(*(int *)(param_9 + 0xdc) + 0xc);
  psVar12 = (short *)(&DAT_803914b8 + iVar7);
  if (((&DAT_803914dc)[iVar7] == '\0') &&
     (iVar6 = zz_008ac80_(param_9,(int)(char)(&DAT_803914c6)[iVar7]), iVar6 == 0)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 1;
  fVar5 = FLOAT_8043c0d0;
  dVar16 = (double)FLOAT_8043c0d0;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(char *)(param_9 + 0x1a6) = (char)(*psVar12 >> 0xf);
  uVar9 = DAT_802b0cbc;
  uVar10 = DAT_802b0cb8;
  uVar11 = DAT_802b0cb4;
  *(char *)(param_9 + 0x1a7) = (char)((short)*(undefined2 *)(&DAT_803914ba + iVar7) >> 0xf);
  uVar2 = DAT_802b0cc0;
  *(float *)(param_9 + 0x1a8) = fVar5;
  uVar3 = DAT_802b0cc4;
  *(undefined2 *)(param_9 + 0x272) = 0xffff;
  uVar4 = DAT_802b0cc8;
  uVar8 = (int)*(short *)(&DAT_803914d4 + iVar7) ^ 0x80000000;
  *(float *)(param_9 + 0x198) = (float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_8043c0d8);
  *(float *)(param_9 + 0x1a0) = fVar5;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(code **)(param_9 + 0x100) = FUN_801df5ec;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(undefined4 *)(param_9 + 0x9c) = uVar11;
  *(undefined4 *)(param_9 + 0xa0) = uVar10;
  *(undefined4 *)(param_9 + 0xa4) = uVar9;
  *(undefined4 *)(param_9 + 0x38) = uVar2;
  *(undefined4 *)(param_9 + 0x3c) = uVar3;
  *(undefined4 *)(param_9 + 0x40) = uVar4;
  zz_0089100_(param_9,(int)*(char *)(iVar14 + 0x3e4) + 0x10,1);
  uVar15 = zz_0048288_(param_9);
  if (*(char *)(param_9 + 0x1a6) == '\0') {
    uVar15 = zz_000726c_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                         *(int *)(param_9 + 0xe0),(float *)(int)*psVar12,
                         (int)*(char *)(param_9 + 0x88),uVar8,uVar9,uVar10,uVar11);
    uVar15 = zz_000726c_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                         *(int *)(param_9 + 0xe4),(float *)(int)*psVar12,
                         (int)*(char *)(param_9 + 0x88),uVar8,uVar9,uVar10,uVar11);
  }
  if (*(char *)(param_9 + 0x1a7) == '\0') {
    uVar15 = zz_000726c_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                         *(int *)(param_9 + 0xe8),(float *)(int)*(short *)(&DAT_803914ba + iVar7),
                         (int)*(char *)(param_9 + 0x88),uVar8,uVar9,uVar10,uVar11);
    zz_000726c_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xec),(float *)(int)*(short *)(&DAT_803914ba + iVar7),
                (int)*(char *)(param_9 + 0x88),uVar8,uVar9,uVar10,uVar11);
  }
  dVar16 = DOUBLE_8043c0d8;
  fVar5 = FLOAT_8043c0d0;
  iVar14 = 0;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(float *)(param_9 + 0xd4) = fVar5;
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,-(int)(char)(&DAT_803914c4)[iVar7] ^ 0x80000000) - dVar16
              );
  *(undefined2 *)(param_9 + 0x1a4) = 0;
  do {
    zz_0018f88_(piVar13,(int)(&PTR_DAT_803914bc)[uVar1 * 10],(float *)(piVar13 + 4));
    zz_0019338_(piVar13 + 2,(int)(&PTR_DAT_803914c0)[uVar1 * 10],(float *)(piVar13 + 7));
    iVar14 = iVar14 + 1;
    piVar13 = piVar13 + 8;
  } while (iVar14 < 2);
  if ((&DAT_803914c7)[iVar7] != '\0') {
    *(undefined1 *)(param_9 + 0xaf) = 0;
    zz_001ac80_(param_9,0x7d);
  }
  if (-1 < *(short *)(&DAT_803914d6 + iVar7)) {
    zz_00f061c_((double)*(float *)(&DAT_803914d8 + iVar7),param_9,
                (int)*(short *)(&DAT_803914d6 + iVar7));
  }
  FUN_801def80(param_9);
  return;
}



// ==== 801def80  FUN_801def80 ====

/* WARNING: Removing unreachable block (ram,0x801df3e8) */
/* WARNING: Removing unreachable block (ram,0x801df3e0) */
/* WARNING: Removing unreachable block (ram,0x801df3d8) */
/* WARNING: Removing unreachable block (ram,0x801defa0) */
/* WARNING: Removing unreachable block (ram,0x801def98) */
/* WARNING: Removing unreachable block (ram,0x801def90) */

void FUN_801def80(int param_1)

{
  int iVar1;
  char cVar2;
  float fVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  float afStack_68 [4];
  double local_58;
  
  uVar4 = (uint)*(byte *)(param_1 + 0x11);
  iVar13 = uVar4 * 0x28;
  piVar15 = *(int **)(*(int *)(param_1 + 0xdc) + 0xc);
  iVar10 = (*(code *)(&PTR_FUN_80391658)[(char)*(byte *)(param_1 + 0x11)])(param_1,param_1 + 0x144);
  fVar8 = FLOAT_8043c0e0;
  fVar7 = FLOAT_8043c0d0;
  if (iVar10 != 0) {
    return;
  }
  cVar2 = *(char *)(param_1 + 0x19);
  if (cVar2 == '\x01') {
    if (**(char **)(param_1 + 0x19c) < '\x01') {
      *(undefined1 *)(param_1 + 0x19) = 2;
      local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(&DAT_803914d4 + iVar13)) ^ 0x80000000)
      ;
      *(float *)(param_1 + 0x198) = (float)(local_58 - DOUBLE_8043c0d8);
      zz_008aff0_(param_1);
    }
  }
  else if (cVar2 < '\x01') {
    if (-1 < cVar2) {
      *(float *)(param_1 + 0x198) = *(float *)(param_1 + 0x198) - FLOAT_8043c0e0;
      if (*(float *)(param_1 + 0x198) < fVar7) {
LAB_801df0f8:
        *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
        return;
      }
      *(float *)(param_1 + 0x1a8) =
           *(float *)(param_1 + 0x1a8) + fVar8 / *(float *)(param_1 + 0x198);
      if (fVar8 < *(float *)(param_1 + 0x1a8)) {
        *(float *)(param_1 + 0x1a8) = fVar8;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
  }
  else if (cVar2 < '\x03') {
    *(float *)(param_1 + 0x198) = *(float *)(param_1 + 0x198) - FLOAT_8043c0e0;
    if ((*(float *)(param_1 + 0x198) < fVar7) ||
       (*(float *)(param_1 + 0x1a8) =
             *(float *)(param_1 + 0x1a8) - fVar8 / *(float *)(param_1 + 0x198),
       *(float *)(param_1 + 0x1a8) < fVar7)) goto LAB_801df0f8;
  }
  dVar17 = (double)FLOAT_8043c0e0;
  dVar18 = (double)FLOAT_8043c0d0;
  iVar14 = 0;
  iVar10 = param_1;
  dVar16 = DOUBLE_8043c0d8;
  do {
    *(float *)(iVar10 + 0xd4) = (float)((double)*(float *)(iVar10 + 0xd4) + dVar17);
    if ((double)*(float *)(iVar10 + 0xd4) < dVar18) {
      piVar15[7] = (int)(float)dVar18;
      piVar15[6] = (int)(float)dVar18;
      piVar15[5] = (int)(float)dVar18;
      piVar15[4] = (int)(float)dVar18;
    }
    else {
      iVar1 = (int)*(float *)(iVar10 + 0xd4);
      local_58 = (double)(longlong)iVar1;
      uVar11 = zz_0018fd8_(piVar15,iVar1,(float *)(piVar15 + 4));
      if (uVar11 != 0) {
        zz_0018f88_(piVar15,(int)(&PTR_DAT_803914bc)[uVar4 * 10],(float *)(piVar15 + 4));
      }
      local_58 = (double)(longlong)(int)*(float *)(iVar10 + 0xd4);
      uVar11 = zz_0019370_(piVar15 + 2,(int)*(float *)(iVar10 + 0xd4),(float *)(piVar15 + 7));
      if (uVar11 != 0) {
        zz_0019338_(piVar15 + 2,(int)(&PTR_DAT_803914c0)[uVar4 * 10],(float *)(piVar15 + 7));
      }
    }
    local_58 = (double)(CONCAT44(0x43300000,(int)(char)(&DAT_803914c5)[iVar13]) ^ 0x80000000);
    if ((float)(local_58 - dVar16) <= *(float *)(iVar10 + 0xd4)) {
      *(float *)(iVar10 + 0xd4) = FLOAT_8043c0d0;
    }
    iVar14 = iVar14 + 1;
    piVar15 = piVar15 + 8;
    iVar10 = iVar10 + 4;
  } while (iVar14 < 2);
  puVar12 = *(undefined4 **)(param_1 + 0x18c);
  uVar9 = puVar12[1];
  *(undefined4 *)(param_1 + 0x174) = *puVar12;
  *(undefined4 *)(param_1 + 0x178) = uVar9;
  *(undefined4 *)(param_1 + 0x17c) = puVar12[2];
  puVar12 = *(undefined4 **)(param_1 + 400);
  uVar9 = puVar12[1];
  *(undefined4 *)(param_1 + 0x180) = *puVar12;
  *(undefined4 *)(param_1 + 0x184) = uVar9;
  *(undefined4 *)(param_1 + 0x188) = puVar12[2];
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x174);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x178);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x17c);
  fVar8 = FLOAT_8043c0e0;
  fVar7 = FLOAT_8043c0d0;
  if ((((*(char *)(param_1 + 0x19) == '\x01') && ('\0' < (char)(&DAT_803914dc)[iVar13])) &&
      (-1 < (char)(&DAT_803914c6)[iVar13])) &&
     (fVar3 = *(float *)(param_1 + 0x1a0) - FLOAT_8043c0e0, *(float *)(param_1 + 0x1a0) = fVar3,
     fVar3 <= fVar7)) {
    *(float *)(param_1 + 0x1a0) = fVar8;
    zz_0139a6c_(param_1,param_1 + 0x174,param_1 + 0x180,(&DAT_803914c6)[iVar13]);
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x180),(float *)(param_1 + 0x174),afStack_68);
  dVar16 = gnt4_PSVECMag_bl(afStack_68);
  uVar5 = DAT_802b0cc4;
  uVar9 = DAT_802b0cb8;
  if ((double)FLOAT_8043c0e4 <= dVar16) {
    *(undefined4 *)(param_1 + 0x9c) = DAT_802b0cb4;
    uVar5 = DAT_802b0cbc;
    *(undefined4 *)(param_1 + 0xa0) = uVar9;
    *(undefined4 *)(param_1 + 0xa4) = uVar5;
    zz_006ec1c_(afStack_68,(float *)(param_1 + 0x38));
    gnt4_PSVECCrossProduct_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x9c),afStack_68);
    dVar17 = gnt4_PSVECSquareMag_bl(afStack_68);
    uVar9 = DAT_802b0cac;
    if (dVar17 <= (double)FLOAT_8043c0e8) {
      *(undefined4 *)(param_1 + 0x9c) = DAT_802b0ca8;
      uVar5 = DAT_802b0cb0;
      *(undefined4 *)(param_1 + 0xa0) = uVar9;
      *(undefined4 *)(param_1 + 0xa4) = uVar5;
    }
    fVar7 = FLOAT_8043c0d0;
    *(float *)(param_1 + 0x194) =
         (float)(dVar16 / (double)*(float *)(&DAT_803914c8 + iVar13)) /
         *(float *)(&DAT_803914d0 + iVar13);
    if (fVar7 != *(float *)(param_1 + 0xb4)) {
      *(float *)(param_1 + 0x194) = *(float *)(param_1 + 0x194) / *(float *)(param_1 + 0xb4);
    }
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  }
  else {
    *(undefined4 *)(param_1 + 0x38) = DAT_802b0cc0;
    uVar6 = DAT_802b0cc8;
    *(undefined4 *)(param_1 + 0x3c) = uVar5;
    uVar9 = DAT_802b0cb4;
    *(undefined4 *)(param_1 + 0x40) = uVar6;
    uVar5 = DAT_802b0cb8;
    *(undefined4 *)(param_1 + 0x9c) = uVar9;
    uVar9 = DAT_802b0cbc;
    *(undefined4 *)(param_1 + 0xa0) = uVar5;
    *(undefined4 *)(param_1 + 0xa4) = uVar9;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801df404  FUN_801df404 ====

void FUN_801df404(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0xaf) = 0xff;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801df448  FUN_801df448 ====

void FUN_801df448(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  *(undefined4 *)(param_9 + 0xdc) = 0;
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801df498  FUN_801df498 ====

/* WARNING: Removing unreachable block (ram,0x801df5d0) */
/* WARNING: Removing unreachable block (ram,0x801df5c8) */
/* WARNING: Removing unreachable block (ram,0x801df4b0) */
/* WARNING: Removing unreachable block (ram,0x801df4a8) */

void FUN_801df498(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
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
  double dVar9;
  double dVar10;
  float afStack_68 [13];
  
  dVar10 = (double)*(float *)(param_1 + 0x1a8);
  iVar2 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc);
  iVar3 = 0;
  dVar9 = (double)(float)(dVar10 * (double)*(float *)(&DAT_803914cc +
                                                     (uint)*(byte *)(param_1 + 0x11) * 0x28));
  iVar5 = param_1;
  do {
    if (*(char *)(param_1 + 0x1a7) == '\0') {
      dVar7 = (double)(float)((double)*(float *)(iVar2 + 0x14) * dVar9);
      dVar8 = (double)(float)((double)*(float *)(iVar2 + 0x18) * dVar9);
      gnt4_PSMTXScale_bl((double)(float)((double)*(float *)(iVar2 + 0x10) * dVar9),dVar7,dVar8,
                         afStack_68);
      pfVar1 = afStack_68;
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x144),pfVar1,pfVar1);
      iVar4 = *(int *)(iVar5 + 0xe8);
      uVar6 = zz_0007cac_((double)*(float *)(iVar2 + 0x1c),iVar4);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,iVar4,afStack_68,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(iVar4,0x44);
    }
    if (*(char *)(param_1 + 0x1a6) == '\0') {
      dVar8 = (double)*(float *)(param_1 + 0x194);
      dVar7 = (double)(float)((double)*(float *)(iVar2 + 0x14) * dVar10);
      gnt4_PSMTXScale_bl((double)(float)((double)*(float *)(iVar2 + 0x10) * dVar10),dVar7,dVar8,
                         afStack_68);
      pfVar1 = afStack_68;
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x144),pfVar1,pfVar1);
      iVar4 = *(int *)(iVar5 + 0xe0);
      uVar6 = zz_0007cac_((double)*(float *)(iVar2 + 0x1c),iVar4);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,iVar4,afStack_68,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(iVar4,0x44);
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x20;
    iVar5 = iVar5 + 4;
  } while (iVar3 < 2);
  return;
}



// ==== 801df5ec  FUN_801df5ec ====

void FUN_801df5ec(int param_1)

{
  float afStack_38 [13];
  
  zz_0048288_(param_1);
  gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),(float *)(param_1 + 0x144));
  gnt4_PSMTXScale_bl((double)FLOAT_8043c0e0,(double)FLOAT_8043c0e0,
                     (double)*(float *)(param_1 + 0x194),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 801df648  FUN_801df648 ====

undefined4 FUN_801df648(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x19) == '\x01') {
    *(undefined2 *)(param_1 + 0x272) = 0;
    iVar1 = zz_003e6e4_(*(float **)(param_2 + 0x48),*(float **)(param_2 + 0x4c),
                        *(float **)(param_2 + 0x4c));
    if (iVar1 != 0) {
      zz_00fc6a0_(*(int *)(param_1 + 0x90),*(undefined4 **)(param_2 + 0x4c),3);
    }
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),0);
    }
  }
  return 0;
}



// ==== 801df6e0  FUN_801df6e0 ====

undefined4 FUN_801df6e0(int param_1,int param_2)

{
  short sVar1;
  
  sVar1 = *(short *)(param_2 + 0x60) + -1;
  *(short *)(param_2 + 0x60) = sVar1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_2 + 0x60) = 6;
    zz_01e3f18_(param_1,0,param_2,param_2 + 100);
  }
  return 0;
}



// ==== 801df72c  FUN_801df72c ====

undefined4 FUN_801df72c(int param_1,int param_2)

{
  short sVar1;
  
  sVar1 = *(short *)(param_2 + 0x60) + -1;
  *(short *)(param_2 + 0x60) = sVar1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_2 + 0x60) = 4;
    zz_01e3f18_(param_1,1,param_2,param_2 + 100);
  }
  return 0;
}



// ==== 801df778  FUN_801df778 ====

undefined4 FUN_801df778(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x19) == '\x01') {
    iVar1 = zz_003e6e4_(*(float **)(param_2 + 0x48),*(float **)(param_2 + 0x4c),
                        *(float **)(param_2 + 0x4c));
    if ((iVar1 != 0) && (*(char *)(param_1 + 0x1a) == '\0')) {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      zz_0085e00_(param_1,*(undefined4 **)(param_2 + 0x4c),0);
    }
  }
  return 0;
}



// ==== 801df7f8  FUN_801df7f8 ====

undefined4 FUN_801df7f8(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x19) == '\x01') {
    iVar1 = zz_003e6e4_(*(float **)(param_2 + 0x48),*(float **)(param_2 + 0x4c),
                        *(float **)(param_2 + 0x4c));
    if ((iVar1 != 0) && (*(char *)(param_1 + 0x1a) == '\0')) {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      zz_0085e00_(param_1,*(undefined4 **)(param_2 + 0x4c),3);
    }
  }
  return 0;
}



// ==== 801df878  FUN_801df878 ====

undefined4 FUN_801df878(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x19) == '\x01') {
    *(undefined2 *)(param_1 + 0x272) = 0;
    iVar1 = zz_003e6e4_(*(float **)(param_2 + 0x48),*(float **)(param_2 + 0x4c),
                        *(float **)(param_2 + 0x4c));
    if (iVar1 != 0) {
      zz_00fc6a0_(*(int *)(param_1 + 0x90),*(undefined4 **)(param_2 + 0x4c),4);
    }
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),0);
    }
  }
  return 0;
}



// ==== 801df908  zz_01df908_ ====

void zz_01df908_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x29;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = FUN_801dfa14;
    *(code **)(puVar1 + 0x10c) = FUN_801dfce0;
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



// ==== 801dfa14  FUN_801dfa14 ====

void FUN_801dfa14(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') && ('\x01' < *(char *)(*(int *)(param_1 + 0x8c) + 0x18)))
  {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_803916e0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801dfa90  FUN_801dfa90 ====

void FUN_801dfa90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
    *(undefined *)(param_9 + 0x89) = (&DAT_803916c9)[iVar3];
    uVar4 = *(undefined4 *)(&DAT_803916d0 + iVar3);
    *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803916cc + iVar3);
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803916d4 + iVar3);
    *(code **)(param_9 + 0x100) = FUN_801dfc40;
    uVar5 = zz_0089100_(param_9,1,1);
    zz_01dfd64_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801dfb8c  FUN_801dfb8c ====

void FUN_801dfb8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  short sVar2;
  
  iVar1 = zz_01dfe5c_(param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    zz_01dfd64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 801dfbe4  FUN_801dfbe4 ====

void FUN_801dfbe4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801dfbf8  FUN_801dfbf8 ====

void FUN_801dfbf8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801dfc40  FUN_801dfc40 ====

void FUN_801dfc40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [13];
  
  zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
              (float *)(param_9 + 100));
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4 + 0x10);
      uVar5 = zz_00456a0_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801dfce0  FUN_801dfce0 ====

void FUN_801dfce0(int param_1)

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



// ==== 801dfd64  zz_01dfd64_ ====

void zz_01dfd64_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    uVar4 = 1 << iVar6;
    if (((int)*(short *)(param_9 + 0x1e) & uVar4) == 0) {
      iVar3 = *(int *)(param_9 + 0x54);
      iVar2 = iVar6 * 0x24;
      iVar1 = (int)*(char *)(param_9 + 0x11);
      *(undefined2 *)(param_9 + 0x1c) = 10;
      piVar5 = (int *)(iVar3 + iVar2);
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)uVar4;
      *(undefined2 *)(piVar5 + 8) = 0;
      *(undefined2 *)((int)piVar5 + 0x22) = *(undefined2 *)(&DAT_803916ca + iVar1 * 0x18);
      zz_0018f88_(piVar5,(int)(&PTR_DAT_803916d8)[iVar1 * 6],(float *)(piVar5 + 4));
      uVar7 = zz_0019338_(piVar5 + 2,(int)(&PTR_DAT_803916dc)[iVar1 * 6],(float *)(piVar5 + 7));
      iVar6 = iVar6 * 4 + 0xe0;
      zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar6),(int)(char)(&DAT_803916c8)[iVar1 * 0x18],iVar2,iVar3,
                  uVar4,in_r9,in_r10);
      zz_0007cac_((double)(float)piVar5[7],*(int *)(param_9 + iVar6));
      iVar6 = (int)*(char *)(param_9 + 0x13);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 801dfe5c  zz_01dfe5c_ ====

int zz_01dfe5c_(int param_1)

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



// ==== 801dff24  zz_01dff24_ ====

void zz_01dff24_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0x18,1,1);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0x2a;
      puVar1[0x13] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_801e0034;
      *(code **)(puVar1 + 0x10c) = FUN_801e0430;
      puVar1[0x11] = 0;
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
  } while (iVar2 < 3);
  return;
}



// ==== 801e0034  FUN_801e0034 ====

void FUN_801e0034(int param_1)

{
  if (((*(char *)(param_1 + 0x18) < '\x02') && ('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18))
      ) || (*(short *)(*(int *)(param_1 + 0x90) + 0x6b8) == 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_80391700)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e00ac  FUN_801e00ac ====

void FUN_801e00ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = *(char *)(param_9 + 0x11) * 0x10;
  *(undefined *)(param_9 + 0x89) = (&DAT_803916f0)[iVar3];
  *(code **)(param_9 + 0x100) = FUN_801e02c8;
  iVar4 = iVar3;
  uVar5 = zz_0089100_(param_9,1,1);
  fVar1 = FLOAT_8043c0f0;
  uVar2 = *(undefined4 *)(&DAT_803916f8 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803916f4 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803916fc + iVar3);
  iVar3 = *(char *)(param_9 + 0x13) * 0x5555;
  *(short *)(param_9 + 0x72) = (short)iVar3;
  *(undefined2 *)(param_9 + 0x7e) = 0x2d8;
  *(short *)(param_9 + 0x70) = *(char *)(param_9 + 0x13) * 0x5555;
  *(undefined2 *)(param_9 + 0x7c) = 0x666;
  *(float *)(param_9 + 0x44) = fVar1;
  *(short *)(param_9 + 0x74) = *(char *)(param_9 + 0x13) * 0x5555;
  *(undefined2 *)(param_9 + 0x80) = 0x333;
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),*(char *)(param_9 + 0x13) + 0x93,iVar3,iVar4,in_r8,in_r9,
              in_r10);
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_01e01b4_(param_9);
  return;
}



// ==== 801e01b4  zz_01e01b4_ ====

void zz_01e01b4_(int param_1)

{
  short sVar1;
  double dVar2;
  
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
  *(float *)(param_1 + 0xb4) =
       *(float *)(*(int *)(param_1 + 0x90) + 0x7fc) * *(float *)(*(int *)(param_1 + 0x90) + 0xb4);
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(param_1 + 0x7c);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x70));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043c0f4 * dVar2);
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_1 + 0x1c) = 0xa2;
    zz_00f036c_(*(int *)(param_1 + 0x90),0x2a);
  }
  return;
}



// ==== 801e025c  FUN_801e025c ====

void FUN_801e025c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_00f036c_(*(int *)(param_1 + 0x90),0x2b);
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_0089444_(param_1);
  return;
}



// ==== 801e02a8  FUN_801e02a8 ====

void FUN_801e02a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e02c8  FUN_801e02c8 ====

void FUN_801e02c8(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  float local_58;
  float local_54;
  undefined4 local_50;
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  uVar1 = DAT_802b0cc4;
  *(undefined4 *)(param_1 + 0x38) = DAT_802b0cc0;
  uVar2 = DAT_802b0cc8;
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  uVar1 = DAT_802b0cb4;
  *(undefined4 *)(param_1 + 0x40) = uVar2;
  uVar2 = DAT_802b0cb8;
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  uVar1 = DAT_802b0cbc;
  *(undefined4 *)(param_1 + 0xa0) = uVar2;
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,param_1 + 0x9c);
  dVar5 = DOUBLE_8043c100;
  local_18 = 0x43300000;
  iVar4 = *(int *)(*(int *)(param_1 + 0x90) + 0x4b0);
  *(int *)(param_1 + 200) = iVar4;
  fVar3 = FLOAT_8043c0f8;
  iVar4 = *(int *)(param_1 + 0x90) + *(char *)(iVar4 + 0xf) * 0x30;
  local_58 = *(float *)(iVar4 + 0x8e0);
  local_54 = *(float *)(iVar4 + 0x8f0);
  local_50 = *(undefined4 *)(iVar4 + 0x900);
  *(float *)(param_1 + 0x120) = local_58;
  *(float *)(param_1 + 0x130) = local_54;
  *(undefined4 *)(param_1 + 0x140) = local_50;
  uStack_14 = (int)*(short *)(param_1 + 0x72) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(fVar3 * (float)((double)CONCAT44(0x43300000,uStack_14) - dVar5)),
                      afStack_4c,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_4c,(float *)(param_1 + 0x114));
  dVar5 = (double)*(float *)(param_1 + 0xb4);
  gnt4_PSMTXScale_bl(dVar5,dVar5,dVar5,afStack_4c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_4c,(float *)(param_1 + 0x114));
  local_58 = *(float *)(param_1 + 100);
  local_50 = *(undefined4 *)(param_1 + 0x6c);
  local_54 = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x44);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_58,(float *)(param_1 + 0x20));
  return;
}



// ==== 801e0430  FUN_801e0430 ====

void FUN_801e0430(int param_1,undefined4 param_2,undefined4 param_3,undefined4 *param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  bool bVar2;
  float *pfVar1;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [3];
  float afStack_40 [15];
  
  if ((char)PTR_DAT_80433930[0x28] < '\0') {
    zz_004844c_((float *)(param_1 + 0x114),(float *)(param_1 + 0x20),5);
  }
  else {
    gnt4_PSVECSubtract_bl
              ((float *)(&DAT_803c7698 + (char)PTR_DAT_80433930[0x28] * 0xf9),
               (float *)(param_1 + 0x20),afStack_4c);
    local_58 = *(undefined4 *)(param_1 + 0x118);
    param_4 = &local_58;
    local_54 = *(undefined4 *)(param_1 + 0x128);
    local_50 = *(undefined4 *)(param_1 + 0x138);
    bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),5,afStack_4c,param_4);
    if (bVar2) {
      zz_004844c_((float *)(param_1 + 0x114),(float *)(param_1 + 0x20),5);
    }
    else {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  dVar3 = (double)*(float *)(param_1 + 0xb4);
  dVar5 = dVar3;
  gnt4_PSMTXScale_bl(dVar3,dVar3,dVar3,afStack_40);
  pfVar1 = (float *)(param_1 + 0x114);
  uVar4 = gnt4_PSMTXConcat_bl(pfVar1,afStack_40,pfVar1);
  zz_00076d0_(uVar4,dVar3,dVar5,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              (float *)(param_1 + 0x114),(undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8
             );
  zz_00097b4_(*(int *)(param_1 + 0xe0),1);
  return;
}



// ==== 801e053c  zz_01e053c_ ====

void zz_01e053c_(int param_1,undefined2 param_2,undefined1 param_3,undefined1 param_4,
                undefined4 param_5)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 1;
  if (param_1 == 7) {
    iVar2 = 6;
  }
  puVar1 = zz_008893c_(2,0x28,1,iVar2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801e0650;
    *(code **)(puVar1 + 0x10c) = FUN_801e07b0;
    *(undefined4 *)(puVar1 + 0xcc) = param_5;
    puVar1[0x11] = (char)param_1;
    puVar1[0x12] = param_3;
    *(undefined2 *)(puVar1 + 0x94) = param_2;
    puVar1[0x13] = param_4;
    *(undefined4 *)(puVar1 + 0xdc) = 0;
  }
  return;
}



// ==== 801e05dc  zz_01e05dc_ ====

void zz_01e05dc_(undefined1 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < param_2; iVar1 = iVar1 + 1) {
    zz_01e053c_(1,0,param_1,(char)iVar1,param_3);
  }
  return;
}



// ==== 801e0650  FUN_801e0650 ====

void FUN_801e0650(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') && (**(char **)(param_1 + 0xcc) != '\0')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80391858)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e06bc  FUN_801e06bc ====

void FUN_801e06bc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x82) = 1;
  (*(code *)(&PTR_FUN_80391868)[*(char *)(param_1 + 0x11)])();
  zz_01e0718_(param_1);
  return;
}



// ==== 801e0718  zz_01e0718_ ====

void zz_01e0718_(int param_1)

{
  (*(code *)(&PTR_FUN_80391888)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e0754  FUN_801e0754 ====

void FUN_801e0754(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801e0768  FUN_801e0768 ====

void FUN_801e0768(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e07b0  FUN_801e07b0 ====

void FUN_801e07b0(int param_1)

{
  (*(code *)(&PTR_FUN_803918a8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e07ec  FUN_801e07ec ====

void FUN_801e07ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar2;
  int iVar1;
  undefined2 local_18 [10];
  
  cVar2 = *(char *)(param_9 + 0x13) + -1;
  *(char *)(param_9 + 0x13) = cVar2;
  if (cVar2 < '\0') {
    *(undefined1 *)(param_9 + 0x13) = 0;
  }
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),7,param_12,param_13,param_14,
              param_15,param_16);
  local_18[0] = *(undefined2 *)(param_9 + 0x94);
  iVar1 = zz_00661d8_((char *)local_18);
  *(int *)(param_9 + 0x14) = iVar1 + 1;
  return;
}



// ==== 801e0868  FUN_801e0868 ====

void FUN_801e0868(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined8 uVar2;
  double dVar3;
  
  iVar1 = DAT_803bb364;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (DAT_803bb364 != 0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      uVar2 = zz_00075cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                          *(int *)(param_9 + 0xe0),(char *)(int)*(char *)(param_9 + 0x12),param_12,
                          param_13,param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 200) = *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0xc);
      zz_01e0a74_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  else {
    dVar3 = zz_01dc648_();
    if ((double)FLOAT_8043c108 <= dVar3) {
      uVar2 = zz_0008744_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  return;
}



// ==== 801e0904  FUN_801e0904 ====

/* WARNING: Removing unreachable block (ram,0x801e0a10) */

void FUN_801e0904(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  undefined8 uVar7;
  
  uVar4 = zz_02502c4_(*(int *)(*(int *)(param_9 + 0xe0) + 0xc));
  if ((uVar4 & 0x10) == 0) {
    iVar2 = *(int *)(param_9 + 0x8c);
    if (iVar2 != 0) {
      iVar6 = *(int *)(param_9 + 200);
      if (iVar6 == 0) {
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_8043c10c,0x3e4,&DAT_8043c114,param_12,param_13,param_14,
                                   param_15,param_16);
      }
      if (param_9 == -0x20) {
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_8043c10c,0x3e5,s_translate_802b3b60,param_12,param_13,
                                   param_14,param_15,param_16);
      }
      puVar5 = *(undefined **)(iVar6 + 0x38);
      uVar3 = *(undefined4 *)(iVar6 + 0x3c);
      *(undefined **)(param_9 + 0x20) = puVar5;
      *(undefined4 *)(param_9 + 0x24) = uVar3;
      *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar6 + 0x40);
      gnt4_PSMTXInverse_bl((float *)&DAT_803c1100,(float *)(param_9 + 0x114));
      *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
      *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
      if (iVar2 == 0) {
        puVar5 = &DAT_8043c114;
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_8043c10c,0x495,&DAT_8043c114,param_12,param_13,param_14,
                                   param_15,param_16);
      }
      if (param_9 == -0x114) {
        puVar5 = &DAT_8043c11c;
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_8043c10c,0x496,&DAT_8043c11c,param_12,param_13,param_14,param_15,
                         param_16);
      }
      uVar7 = gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),(float *)(iVar2 + 0x44));
      *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
      if (iVar2 != 0) {
        uVar4 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar4,
                     puVar5,param_12,param_13,param_14,param_15,param_16);
        }
      }
    }
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  }
  return;
}



// ==== 801e0a74  zz_01e0a74_ ====

/* WARNING: Removing unreachable block (ram,0x801e0b18) */

void zz_01e0a74_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar5;
  undefined4 *puVar6;
  float *pfVar7;
  int iVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float fVar9;
  int *piVar10;
  int iVar11;
  undefined8 uVar12;
  
  iVar3 = DAT_802b3b74;
  iVar11 = DAT_802b3b70;
  iVar2 = DAT_802b3b6c;
  puVar6 = &DAT_802b3b6c;
  iVar8 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar8 == 0) {
    piVar10 = (int *)0x0;
  }
  else {
    piVar10 = *(int **)(iVar8 + 0x10);
  }
  if (piVar10 == (int *)0x0) {
    puVar6 = (undefined4 *)&DAT_8043c114;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_8043c10c,0x3a9,&DAT_8043c114,iVar8,in_r7,in_r8,in_r9,in_r10);
  }
  piVar10[0xe] = iVar2;
  piVar10[0xf] = iVar11;
  piVar10[0x10] = iVar3;
  if (((piVar10[5] & 0x2000000U) == 0) && (piVar10 != (int *)0x0)) {
    uVar4 = piVar10[5];
    bVar1 = false;
    if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                           uVar4,(undefined *)puVar6,iVar8,in_r7,in_r8,in_r9,in_r10);
    }
  }
  iVar2 = DAT_803bb364;
  pfVar7 = (float *)**(int **)(DAT_803bb364 + 0x10);
  fVar9 = pfVar7[*(char *)(param_9 + 0x12)];
  uVar12 = zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0x14,
                       pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
  uVar5 = extraout_r4;
  if (*(undefined4 **)((int)fVar9 + 8) != (undefined4 *)0x0) {
    pfVar7 = (float *)**(undefined4 **)((int)fVar9 + 8);
    iVar8 = 0;
    gnt4_HSD_JObjAddAnimAll
              (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0,pfVar7,
               (undefined4 *)0x0,in_r7,in_r8,in_r9,in_r10);
    uVar12 = gnt4_HSD_JObjReqAnimAll();
    uVar12 = gnt4_HSD_JObjAnimAll
                       (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                        extraout_r4_00,pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
    uVar12 = zz_024d570_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0x14
                         ,pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
    uVar5 = extraout_r4_01;
  }
  if (piVar10 == (int *)0x0) {
    iVar11 = 0;
  }
  else {
    iVar11 = piVar10[4];
  }
  piVar10 = gnt4_HSD_JObjLoadJoint
                      (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (int *)**(undefined4 **)(**(int **)(iVar2 + 0x10) + 0x18),uVar5,pfVar7,iVar8,
                       in_r7,in_r8,in_r9,in_r10);
  *(int **)(param_9 + 0x8c) = piVar10;
  if (piVar10 != (int *)0x0) {
    gnt4_HSD_JObjAddChild
              (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,(int)piVar10,
               (char *)pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 801e0c40  FUN_801e0c40 ====

void FUN_801e0c40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),0,param_9,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 801e0c80  FUN_801e0c80 ====

void FUN_801e0c80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_r4;
  char *pcVar5;
  undefined8 uVar6;
  double dVar7;
  
  pcVar5 = DAT_803bb364;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (DAT_803bb364 != (char *)0x0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      iVar1 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
      if ((iVar1 == 0) || (*(char *)(param_9 + 0x13) < 0)) {
        iVar4 = 0;
        iVar1 = iVar4;
      }
      else {
        if (iVar1 == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar1 + 0x10);
        }
        iVar2 = 0;
        while ((iVar1 = iVar4, iVar2 < *(char *)(param_9 + 0x13) && (iVar4 != 0))) {
          if (iVar4 == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = *(int *)(iVar4 + 8);
          }
          iVar2 = iVar2 + 1;
        }
      }
      do {
        iVar2 = iVar1;
        if (iVar2 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(iVar2 + 0x10);
        }
      } while (iVar1 != 0);
      *(int *)(param_9 + 200) = iVar2;
      if (iVar2 == 0) {
        *(undefined1 *)(param_9 + 0x18) = 2;
      }
      else {
        piVar3 = gnt4_HSD_JObjLoadJoint
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)**(undefined4 **)
                                     (**(int **)(pcVar5 + 0x10) + *(char *)(param_9 + 0x12) * 4),
                            iVar4,pcVar5,param_12,param_13,param_14,param_15,param_16);
        uVar6 = gnt4_HSD_JObjAddChild
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                           (int)piVar3,pcVar5,param_12,param_13,param_14,param_15,param_16);
        zz_01e0fec_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      }
    }
  }
  else {
    dVar7 = zz_01dc648_();
    if ((double)FLOAT_8043c108 <= dVar7) {
      uVar6 = zz_0008744_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  return;
}



// ==== 801e0de0  FUN_801e0de0 ====

/* WARNING: Removing unreachable block (ram,0x801e0e94) */
/* WARNING: Removing unreachable block (ram,0x801e0e30) */
/* WARNING: Removing unreachable block (ram,0x801e0f88) */

void FUN_801e0de0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint extraout_r4;
  uint extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined *puVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  float afStack_28 [7];
  
  uVar3 = zz_02502c4_(*(int *)(*(int *)(param_9 + 0xe0) + 0xc));
  if ((uVar3 & 0x10) == 0) {
    iVar2 = *(int *)(param_9 + 0x8c);
    if (iVar2 != 0) {
      piVar6 = *(int **)(param_9 + 200);
      if (piVar6 != (int *)0x0) {
        uVar3 = piVar6[5];
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          param_1 = gnt4_HSD_JObjSetupMatrixSub_bl
                              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               piVar6,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
        }
      }
      piVar6 = *(int **)(param_9 + 200);
      if (piVar6 == (int *)0x0) {
        param_11 = &DAT_8043c114;
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_8043c10c,0x47c,&DAT_8043c114,param_12,param_13,param_14,
                                   param_15,param_16);
        uVar3 = extraout_r4;
      }
      else {
        uVar3 = piVar6[5];
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (bVar1) {
          param_1 = gnt4_HSD_JObjSetupMatrixSub_bl
                              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               piVar6,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
          uVar3 = extraout_r4_00;
        }
      }
      *(int *)(param_9 + 0x20) = piVar6[0x14];
      *(int *)(param_9 + 0x24) = piVar6[0x18];
      *(int *)(param_9 + 0x28) = piVar6[0x1c];
      uVar7 = zz_00089c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (float *)(param_9 + 0x9c),uVar3,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      zz_0008970_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,afStack_28,
                  extraout_r4_01,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar7 = gnt4_PSVECSubtract_bl(afStack_28,(float *)(param_9 + 0x20),(float *)(param_9 + 0x38));
      puVar4 = (undefined *)(param_9 + 0x38);
      iVar5 = param_9 + 0x9c;
      zz_0045ef4_((float *)(param_9 + 0x114),5,puVar4,iVar5);
      *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
      *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
      if (iVar2 == 0) {
        puVar4 = &DAT_8043c114;
        uVar7 = gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_8043c10c,0x495,&DAT_8043c114,iVar5,param_13,param_14,param_15,
                                 param_16);
      }
      if (param_9 == -0x114) {
        puVar4 = &DAT_8043c11c;
        gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_8043c10c
                         ,0x496,&DAT_8043c11c,iVar5,param_13,param_14,param_15,param_16);
      }
      uVar7 = gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),(float *)(iVar2 + 0x44));
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
                     puVar4,iVar5,param_13,param_14,param_15,param_16);
        }
      }
    }
    zz_00097b4_(*(int *)(param_9 + 0xe0),0xf);
  }
  return;
}



// ==== 801e0fec  zz_01e0fec_ ====

/* WARNING: Removing unreachable block (ram,0x801e108c) */

void zz_01e0fec_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar5;
  undefined4 *puVar6;
  float *pfVar7;
  int iVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float fVar9;
  int *piVar10;
  int iVar11;
  undefined8 uVar12;
  
  iVar3 = DAT_802b3b80;
  iVar11 = DAT_802b3b7c;
  iVar2 = DAT_802b3b78;
  puVar6 = &DAT_802b3b78;
  iVar8 = *(int *)(param_9 + 200);
  if (iVar8 == 0) {
    piVar10 = (int *)0x0;
  }
  else {
    piVar10 = *(int **)(iVar8 + 0x10);
  }
  if (piVar10 == (int *)0x0) {
    puVar6 = (undefined4 *)&DAT_8043c114;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_8043c10c,0x3a9,&DAT_8043c114,iVar8,in_r7,in_r8,in_r9,in_r10);
  }
  piVar10[0xe] = iVar2;
  piVar10[0xf] = iVar11;
  piVar10[0x10] = iVar3;
  if (((piVar10[5] & 0x2000000U) == 0) && (piVar10 != (int *)0x0)) {
    uVar4 = piVar10[5];
    bVar1 = false;
    if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                           uVar4,(undefined *)puVar6,iVar8,in_r7,in_r8,in_r9,in_r10);
    }
  }
  iVar2 = DAT_803bb364;
  pfVar7 = (float *)**(int **)(DAT_803bb364 + 0x10);
  fVar9 = pfVar7[*(char *)(param_9 + 0x12)];
  uVar12 = zz_024d570_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0x14,
                       pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
  uVar5 = extraout_r4;
  if (*(undefined4 **)((int)fVar9 + 8) != (undefined4 *)0x0) {
    pfVar7 = (float *)**(undefined4 **)((int)fVar9 + 8);
    iVar8 = 0;
    gnt4_HSD_JObjAddAnimAll
              (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0,pfVar7,
               (undefined4 *)0x0,in_r7,in_r8,in_r9,in_r10);
    uVar12 = gnt4_HSD_JObjReqAnimAll();
    uVar12 = gnt4_HSD_JObjAnimAll
                       (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,
                        extraout_r4_00,pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
    uVar12 = zz_024d570_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar10,0x14
                         ,pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
    uVar5 = extraout_r4_01;
  }
  if (piVar10 == (int *)0x0) {
    iVar11 = 0;
  }
  else {
    iVar11 = piVar10[4];
  }
  piVar10 = gnt4_HSD_JObjLoadJoint
                      (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (int *)**(undefined4 **)(**(int **)(iVar2 + 0x10) + 0x18),uVar5,pfVar7,iVar8,
                       in_r7,in_r8,in_r9,in_r10);
  *(int **)(param_9 + 0x8c) = piVar10;
  if (piVar10 != (int *)0x0) {
    gnt4_HSD_JObjAddChild
              (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,(int)piVar10,
               (char *)pfVar7,iVar8,in_r7,in_r8,in_r9,in_r10);
    *(int *)(param_9 + 200) = iVar11;
  }
  return;
}



// ==== 801e11b8  FUN_801e11b8 ====

void FUN_801e11b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  cVar1 = *(char *)(param_9 + 0x13);
  if (cVar1 == '\x02') {
    param_11 = 6;
    *(undefined1 *)(param_9 + 0x10) = 0;
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      param_11 = 7;
      *(undefined1 *)(param_9 + 0x10) = 0;
    }
    else if (-1 < cVar1) {
      param_11 = 6;
      *(undefined1 *)(param_9 + 0x10) = 0;
    }
  }
  else if (cVar1 < '\x04') {
    param_11 = 5;
    *(undefined1 *)(param_9 + 0x10) = 1;
  }
  *(undefined4 *)(param_9 + 0x90) = (&DAT_803c4e84)[*(char *)(param_9 + 0x10)];
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,
              param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801e128c  FUN_801e128c ====

/* WARNING: Removing unreachable block (ram,0x801e14a8) */
/* WARNING: Removing unreachable block (ram,0x801e129c) */
/* WARNING: Removing unreachable block (ram,0x801e13bc) */

void FUN_801e128c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,int param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  byte bVar1;
  bool bVar2;
  undefined4 extraout_r4;
  uint uVar3;
  int *piVar4;
  double dVar5;
  undefined8 uVar6;
  undefined4 uStack_38;
  float local_34;
  longlong local_28;
  
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x1a) = 0;
    if (*(int *)(&DAT_803bbac0 + *(char *)(param_9 + 0x10) * 0xc30) != 0) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    }
    *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x82) = 0;
  }
  else {
    dVar5 = zz_01dc648_();
    if (((double)FLOAT_8043c128 < dVar5) && (*(char *)(param_9 + 0x1a) == '\0')) {
      *(undefined1 *)(param_9 + 0x1a) = 1;
      param_11 = (float *)0x1;
      param_12 = *(int *)(param_9 + 0x90);
      bVar1 = *(byte *)(param_12 + 0x3e9);
      param_13 = (uint)bVar1;
      if ((1 << (bVar1 & 0x1f) &
          *(uint *)(*(char *)(param_12 + 1000) * 8 + -0x7fd22b00 + (bVar1 >> 3 & 4))) != 0) {
        *(undefined1 *)(param_12 + 0x5da) = 0x3c;
        param_11 = (float *)0x28;
        *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x5db) = 0x3c;
        *(undefined2 *)(*(int *)(param_9 + 0x90) + 0x5ae) =
             *(undefined2 *)(*(int *)(param_9 + 0x90) + 0x72);
        zz_0057ff8_(*(int *)(param_9 + 0x90),0,0x28);
      }
    }
    uVar6 = zz_0008744_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,param_12,param_13
                        ,param_14,param_15,param_16);
    uVar6 = zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    piVar4 = *(int **)(*(int *)(param_9 + 0xe0) + 0xc);
    if (piVar4 != (int *)0x0) {
      uVar3 = piVar4[5];
      bVar2 = false;
      if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
        bVar2 = true;
      }
      if (bVar2) {
        uVar6 = gnt4_HSD_JObjSetupMatrixSub_bl
                          (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar4,
                           uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    uVar6 = zz_0007908_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x20),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    uVar6 = zz_0007a60_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),&uStack_38,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007bb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x58),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0057fac_(*(int *)(param_9 + 0x90),(undefined4 *)(param_9 + 0x20));
    local_28 = (longlong)(int)(FLOAT_8043c12c * local_34);
    zz_0057fc8_(*(int *)(param_9 + 0x90),(short)(int)(FLOAT_8043c12c * local_34));
    uVar3 = (int)*(char *)(param_9 + 0x13) ^ 2;
    zz_0057fd0_((double)*(float *)(param_9 + 0x5c),*(int *)(param_9 + 0x90),
                ((int)uVar3 >> 1) - (uVar3 & 2) >> 0x1f);
    uVar3 = zz_02502c4_(*(int *)(*(int *)(param_9 + 0xe0) + 0xc));
    if ((uVar3 & 0x10) == 0) {
      *(char *)(*(int *)(param_9 + 0x90) + 0x82) = *(char *)(*(int *)(param_9 + 0x90) + 0x96) + 'A';
    }
    else {
      *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x82) = 0;
    }
  }
  return;
}



// ==== 801e14c8  FUN_801e14c8 ====

void FUN_801e14c8(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_02502c4_(*(int *)(*(int *)(param_1 + 0xe0) + 0xc));
  if ((uVar1 & 0x10) == 0) {
    *(char *)(*(int *)(param_1 + 0x90) + 0x82) = *(char *)(*(int *)(param_1 + 0x90) + 0x96) + 'A';
  }
  return;
}



// ==== 801e1514  FUN_801e1514 ====

void FUN_801e1514(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),6,param_9,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 801e1554  FUN_801e1554 ====

void FUN_801e1554(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int *piVar3;
  float *pfVar4;
  undefined4 uVar5;
  int iVar6;
  int *piVar7;
  undefined8 uVar8;
  double dVar9;
  
  iVar6 = DAT_803bb36c;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (DAT_803bb36c != 0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      uVar8 = zz_00075cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                          *(int *)(param_9 + 0xe0),(char *)0x0,param_12,param_13,param_14,param_15,
                          param_16);
      iVar1 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
      if (iVar1 == 0) {
        piVar7 = (int *)0x0;
      }
      else {
        piVar7 = *(int **)(iVar1 + 0x10);
      }
      piVar3 = (int *)**(undefined4 **)(iVar6 + 0x10);
      iVar6 = *piVar3;
      uVar8 = zz_024d570_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar7,0x14,
                          piVar3,param_12,param_13,param_14,param_15,param_16);
      puVar2 = *(undefined4 **)(iVar6 + 8);
      if (puVar2 != (undefined4 *)0x0) {
        pfVar4 = (float *)*puVar2;
        uVar5 = 0;
        gnt4_HSD_JObjAddAnimAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar7,0,pfVar4,
                   (undefined4 *)0x0,param_13,param_14,param_15,param_16);
        uVar8 = gnt4_HSD_JObjReqAnimAll();
        gnt4_HSD_JObjAnimAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar7,extraout_r4,
                   pfVar4,uVar5,param_13,param_14,param_15,param_16);
      }
    }
  }
  else {
    dVar9 = zz_01dc648_();
    if ((double)FLOAT_8043c108 <= dVar9) {
      uVar8 = zz_0008744_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,
                  param_15,param_16);
    }
  }
  return;
}



// ==== 801e164c  FUN_801e164c ====

void FUN_801e164c(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_02502c4_(*(int *)(*(int *)(param_1 + 0xe0) + 0xc));
  if ((uVar1 & 0x10) == 0) {
    zz_00097b4_(*(int *)(param_1 + 0xe0),0xf);
  }
  return;
}



// ==== 801e1694  FUN_801e1694 ====

void FUN_801e1694(int param_1)

{
  float fVar1;
  int iVar2;
  undefined2 local_18 [10];
  
  local_18[0] = *(undefined2 *)(param_1 + 0x94);
  iVar2 = zz_00661d8_((char *)local_18);
  fVar1 = FLOAT_8043c108;
  *(int *)(param_1 + 0x14) = iVar2 + 1;
  *(float *)(param_1 + 0xd4) = fVar1;
  return;
}



// ==== 801e1720  FUN_801e1720 ====

/* WARNING: Removing unreachable block (ram,0x801e19d8) */
/* WARNING: Removing unreachable block (ram,0x801e1730) */

void FUN_801e1720(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  undefined4 local_78;
  undefined4 local_74;
  uint local_70;
  uint local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined8 local_40;
  undefined4 local_38;
  uint uStack_34;
  
  local_68 = DAT_802b3b84;
  local_64 = DAT_802b3b88;
  local_60 = DAT_802b3b8c;
  local_70 = gnt4___cvt_fp2unsigned_bl((double)(FLOAT_8043c144 * *(float *)(param_1 + 0xd4)));
  local_70 = local_70 | 0xffffff00;
  local_6c = local_70;
  if (*(char *)(param_1 + 0x13) == '\0') {
    local_78 = DAT_8043c13c;
    local_74 = DAT_8043c140;
    uVar1 = (uint)(FLOAT_8043c144 * *(float *)(param_1 + 0xd4));
    local_40 = (double)(longlong)(int)uVar1;
    zz_01e1a28_(0x60,0x14f,0x1c0,0x40,uVar1,&local_78);
  }
  else {
    uStack_34 = (int)DAT_80391716 ^ 0x80000000;
    local_40 = (double)CONCAT44(0x43300000,(int)DAT_80391714 ^ 0x80000000);
    DAT_803c1140 = &local_5c;
    DAT_803c1144 = &local_68;
    DAT_803c1150 = &local_70;
    local_38 = 0x43300000;
    local_50 = FLOAT_8043c148 + (float)(local_40 - DOUBLE_8043c120);
    local_4c = FLOAT_8043c14c + (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043c120);
    DAT_803c1160 = &DAT_803c04b0;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    DAT_803c1173 = 0x2c;
    local_48 = FLOAT_8043c138;
    local_54 = FLOAT_8043c138;
    local_5c = FLOAT_8043c148;
    local_58 = FLOAT_8043c14c;
    DAT_803c115c = &DAT_80391710;
    FUN_80051ef4(-0x7fc3eed0);
    local_50 = FLOAT_8043c150 + FLOAT_8043c158;
    local_4c = FLOAT_8043c154 + FLOAT_8043c15c;
    local_5c = FLOAT_8043c150;
    local_58 = FLOAT_8043c154;
    DAT_803c115c = &DAT_80391710 + *(int *)(&DAT_80391840 + *(char *)(param_1 + 0x12) * 4) * 8;
    FUN_80051ef4(-0x7fc3eed0);
    local_50 = FLOAT_8043c160 + FLOAT_8043c158;
    local_5c = FLOAT_8043c160;
    DAT_803c115c = &DAT_80391710 + *(char *)(param_1 + 0x13) * 8;
    FUN_80051ef4(-0x7fc3eed0);
    local_50 = FLOAT_8043c164 + FLOAT_8043c168;
    local_4c = FLOAT_8043c154 + FLOAT_8043c15c;
    dVar4 = (double)FLOAT_8043c16c;
    uVar1 = 100;
    local_5c = FLOAT_8043c164;
    iVar2 = 0;
    local_58 = FLOAT_8043c154;
    uVar3 = *(uint *)(param_1 + 0x14);
    do {
      DAT_803c115c = &DAT_80391710 + (uVar3 / uVar1 + 9) * 8;
      FUN_80051ef4(-0x7fc3eed0);
      iVar2 = iVar2 + 1;
      local_68 = (float)((double)local_68 + dVar4);
      uVar3 = uVar3 - (uVar3 / uVar1) * uVar1;
      uVar1 = uVar1 / 10;
    } while (iVar2 < 3);
  }
  return;
}



// ==== 801e19f4  zz_01e19f4_ ====

void zz_01e19f4_(short param_1,short param_2,short param_3,short param_4,uint param_5)

{
  undefined4 local_8;
  undefined4 local_4;
  
  local_8 = DAT_8043c170;
  local_4 = DAT_8043c174;
  zz_01e1a28_(param_1,param_2,param_3,param_4,param_5,&local_8);
  return;
}



// ==== 801e1a28  zz_01e1a28_ ====

void zz_01e1a28_(short param_1,short param_2,short param_3,short param_4,uint param_5,
                undefined4 param_6)

{
  uint local_58;
  uint local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  uStack_34 = (int)param_1 ^ 0x80000000;
  local_58 = param_5 & 0xff | 0xffffff00;
  uStack_1c = (int)param_4 ^ 0x80000000;
  uStack_2c = (int)param_2 ^ 0x80000000;
  uStack_24 = (int)param_3 ^ 0x80000000;
  local_38 = 0x43300000;
  DAT_803c1140 = &local_50;
  DAT_803c1150 = &local_58;
  local_50 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043c120);
  local_30 = 0x43300000;
  local_4c = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043c120);
  local_28 = 0x43300000;
  local_20 = 0x43300000;
  local_44 = local_50 + (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043c120);
  local_40 = local_4c + (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043c120);
  local_3c = FLOAT_8043c138;
  local_48 = FLOAT_8043c138;
  DAT_803c1144 = 0;
  DAT_803c1160 = &DAT_803c04b0;
  DAT_803c1164 = 3;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  DAT_803c1173 = 0x2b;
  DAT_803c115c = param_6;
  local_54 = local_58;
  FUN_80051ef4(-0x7fc3eed0);
  return;
}



// ==== 801e1b54  zz_01e1b54_ ====

/* WARNING: Removing unreachable block (ram,0x801e1e68) */
/* WARNING: Removing unreachable block (ram,0x801e1b64) */

void zz_01e1b54_(short param_1,short param_2,undefined2 param_3,int param_4,int param_5,uint param_6
                )

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  undefined2 local_c8 [2];
  undefined2 local_c4;
  uint local_c0;
  uint local_bc;
  float local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  uStack_8c = (int)param_1 ^ 0x80000000;
  local_90 = 0x43300000;
  uStack_84 = (int)param_2 ^ 0x80000000;
  uStack_7c = (int)DAT_803917ac ^ 0x80000000;
  uStack_74 = (int)DAT_803917ae ^ 0x80000000;
  local_ac = (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_8043c120);
  local_88 = 0x43300000;
  DAT_803c1140 = &local_ac;
  local_a8 = (float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8043c120);
  DAT_803c1144 = &local_b8;
  DAT_803c1150 = &local_c0;
  local_c0 = param_6 & 0xff | 0xffffff00;
  local_80 = 0x43300000;
  local_78 = 0x43300000;
  local_a0 = local_ac + (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_8043c120);
  local_9c = local_a8 + (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8043c120);
  local_b8 = DAT_802b3b90;
  local_b4 = DAT_802b3b94;
  local_b0 = DAT_802b3b98;
  DAT_803c1160 = &DAT_803c04b0;
  DAT_803c1164 = 3;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  DAT_803c1173 = 0x2c;
  local_98 = FLOAT_8043c138;
  local_a4 = FLOAT_8043c138;
  DAT_803c115c = &DAT_803917a8;
  local_bc = local_c0;
  FUN_80051ef4(-0x7fc3eed0);
  iVar3 = (int)param_1;
  uStack_6c = iVar3 + 0x9aU ^ 0x80000000;
  uStack_64 = (int)param_2 ^ 0x80000000;
  local_70 = 0x43300000;
  local_68 = 0x43300000;
  local_ac = (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8043c120);
  local_a8 = (float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8043c120);
  local_a0 = local_ac + FLOAT_8043c178;
  DAT_803c115c = &DAT_803917a8 + *(int *)(&DAT_80391840 + param_4 * 4) * 8;
  local_9c = local_a8 + FLOAT_8043c17c;
  FUN_80051ef4(-0x7fc3eed0);
  uStack_5c = iVar3 + 0xdeU ^ 0x80000000;
  local_60 = 0x43300000;
  local_ac = (float)((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_8043c120);
  DAT_803c115c = &DAT_803917a8 + (param_5 + 1) * 8;
  local_a0 = local_ac + FLOAT_8043c178;
  FUN_80051ef4(-0x7fc3eed0);
  uStack_54 = iVar3 + 0xabU ^ 0x80000000;
  uStack_4c = (int)param_2 ^ 0x80000000;
  local_58 = 0x43300000;
  local_ac = (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043c120);
  local_50 = 0x43300000;
  local_a0 = local_ac + FLOAT_8043c178;
  local_a8 = (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043c120);
  local_9c = local_a8 + FLOAT_8043c17c;
  local_c8[0] = param_3;
  local_c4 = param_3;
  iVar3 = zz_00661d8_((char *)local_c8);
  dVar4 = (double)FLOAT_8043c180;
  uVar1 = iVar3 + 1;
  uVar2 = 100;
  iVar3 = 0;
  do {
    DAT_803c115c = &DAT_803917a8 + (uVar1 / uVar2 + 9) * 8;
    FUN_80051ef4(-0x7fc3eed0);
    iVar3 = iVar3 + 1;
    local_b8 = (float)((double)local_b8 + dVar4);
    uVar1 = uVar1 - (uVar1 / uVar2) * uVar2;
    uVar2 = uVar2 / 10;
  } while (iVar3 < 3);
  return;
}



// ==== 801e1e84  FUN_801e1e84 ====

void FUN_801e1e84(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  *(undefined4 *)(param_9 + 0x90) = (&DAT_803c4e84)[*(char *)(param_9 + 0x13)];
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),4,param_12,param_13,param_14,
              param_15,param_16);
  *(undefined1 *)(param_9 + 0x84) = 0x40;
  *(undefined1 *)(param_9 + 0x89) = 0xc;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  return;
}



// ==== 801e1f14  FUN_801e1f14 ====

void FUN_801e1f14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  double dVar1;
  double dVar2;
  undefined8 uVar3;
  
  dVar2 = zz_01dc648_();
  dVar1 = (double)FLOAT_8043c184;
  *(float *)(param_9 + 0xd4) = (float)dVar2;
  if (dVar1 <= dVar2) {
    uVar3 = zz_00087d4_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    uVar3 = zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    gnt4_HSD_JObjClearFlagsAll
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0xc),0x10,(undefined *)param_11,param_12,
               param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  else {
    gnt4_HSD_JObjSetFlagsAll
              (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0xc),0x10,(undefined *)param_11,param_12,
               param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801e1f9c  FUN_801e1f9c ====

void FUN_801e1f9c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined8 uVar2;
  
  puVar1 = *(undefined **)(param_9 + 0x90);
  uVar2 = gnt4_PSMTXCopy_bl((float *)(puVar1 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
                            (float *)(param_9 + 0x114));
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,(float *)(param_9 + 0x114),puVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801e1ffc  FUN_801e1ffc ====

void FUN_801e1ffc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int *piVar2;
  int unaff_r31;
  
  piVar2 = zz_0006dc8_(0x18);
  *(int **)(param_9 + 0xdc) = piVar2;
  if (*(int *)(param_9 + 0xdc) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
    cVar1 = *(char *)(param_9 + 0x13);
    if (cVar1 == '\x01') {
      unaff_r31 = 8;
      *(undefined1 *)(param_9 + 0x10) = 0;
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      unaff_r31 = 9;
      *(undefined1 *)(param_9 + 0x10) = 0;
    }
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),unaff_r31,param_12,param_13,
                param_14,param_15,param_16);
    zz_000804c_(*(int *)(param_9 + 0xe0),DAT_803c04b8,*(int **)(*(int *)(param_9 + 0xdc) + 0xc));
  }
  return;
}



// ==== 801e20c8  FUN_801e20c8 ====

void FUN_801e20c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  double dVar1;
  double dVar2;
  undefined8 uVar3;
  
  dVar2 = zz_01dc648_();
  dVar1 = (double)FLOAT_8043c188;
  *(float *)(param_9 + 0xd4) = (float)dVar2;
  if (dVar1 <= dVar2) {
    uVar3 = zz_00087d4_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    uVar3 = zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    gnt4_HSD_JObjClearFlagsAll
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0xc),0x10,(undefined *)param_11,param_12,
               param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  else {
    gnt4_HSD_JObjSetFlagsAll
              (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0xc),0x10,(undefined *)param_11,param_12,
               param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801e2150  FUN_801e2150 ====

void FUN_801e2150(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_02502c4_(*(int *)(*(int *)(param_1 + 0xe0) + 0xc));
  if ((uVar1 & 0x10) == 0) {
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x47);
  }
  return;
}



// ==== 801e2198  FUN_801e2198 ====

/* WARNING: Removing unreachable block (ram,0x801e232c) */
/* WARNING: Removing unreachable block (ram,0x801e21a8) */

void FUN_801e2198(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int extraout_r4;
  uint uVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  undefined8 uVar7;
  double dVar8;
  undefined2 local_48 [4];
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  local_48[0] = *(undefined2 *)(param_9 + 0x94);
  iVar1 = zz_00661d8_((char *)local_48);
  *(int *)(param_9 + 0x14) = iVar1 + 1;
  psVar6 = &DAT_803918c8;
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb35c;
  iVar1 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x99); iVar4 = iVar4 + 1) {
    param_11 = (float *)(int)*psVar6;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x54),*(int *)(iVar1 + 0xe0),(int)param_11,param_12,
                          param_13,param_14,param_15,param_16);
    psVar6 = psVar6 + 1;
    iVar1 = iVar1 + 4;
  }
  local_40 = 0x43300000;
  uStack_3c = *(uint *)(&DAT_803918d4 + *(char *)(param_9 + 0x12) * 4) ^ 0x80000000;
  zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043c120),param_2,
              param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54),
              *(int *)(param_9 + 0xe4),param_11,param_12,param_13,param_14,param_15,param_16);
  local_38 = 0x43300000;
  uStack_34 = (int)*(char *)(param_9 + 0x13) - 1U ^ 0x80000000;
  zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043c120),param_2,
              param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54),
              *(int *)(param_9 + 0xf4),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = *(int *)(param_9 + 0x14);
  iVar5 = param_9 + 8;
  uVar3 = 100;
  iVar4 = 2;
  dVar8 = DOUBLE_8043c120;
  do {
    local_38 = 0x43300000;
    uStack_34 = iVar1 / (int)uVar3 ^ 0x80000000;
    uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_34) - dVar8),param_2,
                        param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54),
                        *(int *)(iVar5 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                       );
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + 4;
    iVar2 = (iVar1 / (int)uVar3) * uVar3;
    uVar3 = uVar3 / 10;
    iVar1 = iVar1 - iVar2;
  } while (iVar4 < 5);
  iVar1 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x99); iVar4 = iVar4 + 1) {
    uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar1 + 0xe0),iVar2,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    iVar1 = iVar1 + 4;
    iVar2 = extraout_r4;
  }
  return;
}



// ==== 801e2348  FUN_801e2348 ====

void FUN_801e2348(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  dVar4 = zz_01dc648_();
  dVar3 = (double)FLOAT_8043c188;
  *(float *)(param_9 + 0xd4) = (float)dVar4;
  if (dVar3 <= dVar4) {
    iVar2 = param_9;
    for (iVar1 = 0; iVar1 < *(char *)(param_9 + 0x99); iVar1 = iVar1 + 1) {
      dVar4 = (double)gnt4_HSD_JObjClearFlagsAll
                                (dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(undefined4 *)(*(int *)(iVar2 + 0xe0) + 0xc),0x10,param_11,
                                 param_12,param_13,param_14,param_15,param_16);
      iVar2 = iVar2 + 4;
    }
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  else {
    iVar2 = param_9;
    for (iVar1 = 0; iVar1 < *(char *)(param_9 + 0x99); iVar1 = iVar1 + 1) {
      dVar4 = (double)gnt4_HSD_JObjSetFlagsAll
                                (dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(undefined4 *)(*(int *)(iVar2 + 0xe0) + 0xc),0x10,param_11,
                                 param_12,param_13,param_14,param_15,param_16);
      iVar2 = iVar2 + 4;
    }
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801e2410  FUN_801e2410 ====

void FUN_801e2410(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_78 [12];
  float afStack_48 [14];
  
  gnt4_PSMTXInverse_bl((float *)&DAT_803c1100,afStack_48);
  pfVar4 = (float *)&DAT_803918ec;
  iVar3 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x99) <= iVar3) break;
    uVar1 = zz_02502c4_(*(int *)(*(int *)(iVar5 + 0xe0) + 0xc));
    if ((uVar1 & 0x10) == 0) {
      dVar7 = (double)pfVar4[1];
      dVar8 = (double)pfVar4[2];
      gnt4_PSMTXTrans_bl((double)*pfVar4,dVar7,dVar8,afStack_78);
      pfVar2 = afStack_78;
      uVar6 = gnt4_PSMTXConcat_bl(afStack_48,pfVar2,pfVar2);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_78,
                  (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar5 + 0xe0),0x47);
    }
    iVar5 = iVar5 + 4;
    pfVar4 = pfVar4 + 3;
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 801e24e0  zz_01e24e0_ ====

void zz_01e24e0_(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(DAT_80436354 + 0x68);
  for (piVar1 = &DAT_80391938; (-1 < *piVar1 && ((iVar3 != 0 || (piVar1[1] < 7))));
      piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x25,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801e2584;
      *(code **)(iVar2 + 0x10c) = FUN_801e29dc;
    }
  }
  return;
}



// ==== 801e2584  FUN_801e2584 ====

void FUN_801e2584(int param_1)

{
  (*(code *)(&PTR_FUN_80391a14)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e25c0  FUN_801e25c0 ====

void FUN_801e25c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined8 uVar2;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar2 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043c190;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  zz_01a7688_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,param_12,
              param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 4;
  zz_01e2654_(param_9);
  return;
}



// ==== 801e2654  zz_01e2654_ ====

void zz_01e2654_(int param_1)

{
  (*(code *)(&PTR_LAB_80391a24)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e26a4  FUN_801e26a4 ====

void FUN_801e26a4(int param_1)

{
  char cVar1;
  double dVar2;
  short sVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  int unaff_r31;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar10 = *(char *)(param_1 + 0x11) + -2;
  iVar4 = zz_0181c30_();
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 < '\x04') {
        *(int *)(param_1 + 0x180) = iVar4;
        sVar3 = *(short *)(param_1 + 0x1c) + 1;
        *(short *)(param_1 + 0x1c) = sVar3;
        unaff_r31 = iVar4;
        if (0xb4 < sVar3) {
          *(undefined1 *)(param_1 + 0x19) = 0;
        }
      }
      goto LAB_801e27b4;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0;
      *(int *)(param_1 + 0x180) = iVar4;
      unaff_r31 = iVar4;
      goto LAB_801e27b4;
    }
    if (cVar1 < '\0') goto LAB_801e27b4;
    if (*(int *)(param_1 + 0x180) == iVar4) {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 1;
  }
  iVar6 = (int)*(short *)(param_1 + 0x1c) * (iVar4 - *(int *)(param_1 + 0x180));
  sVar3 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar3;
  iVar6 = iVar6 / 0x78 + (iVar6 >> 0x1f);
  unaff_r31 = *(int *)(param_1 + 0x180) + (iVar6 - (iVar6 >> 0x1f));
  if (0x78 < sVar3) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
LAB_801e27b4:
  if (unaff_r31 < iVar4) {
    iVar6 = unaff_r31 + 3;
    if (iVar4 < unaff_r31 + 3) {
      iVar6 = iVar4;
    }
  }
  else {
    iVar6 = unaff_r31;
    if ((iVar4 < unaff_r31) && (iVar6 = unaff_r31 + -3, unaff_r31 + -3 < iVar4)) {
      iVar6 = iVar4;
    }
  }
  *(int *)(param_1 + 0x180) = iVar6;
  iVar4 = 1;
  if ((((DAT_80391a4e <= iVar6) && (iVar4 = 2, DAT_80391a50 <= iVar6)) &&
      (iVar4 = 3, DAT_80391a52 <= iVar6)) && (iVar4 = 4, DAT_80391a54 <= iVar6)) {
    iVar4 = 5;
  }
  if (iVar10 < iVar4) {
    iVar9 = (iVar4 + -1) * 0x32;
    *(undefined1 *)(param_1 + 0x82) = 4;
    dVar2 = DOUBLE_8043c198;
    uVar8 = iVar9 / 2 ^ 0x80000000;
    pfVar7 = (float *)(((iVar4 + -1) - iVar10) * 0x32 ^ 0x80000000);
    *(float *)(param_1 + 100) =
         (float)((double)*(float *)(param_1 + 0x148) -
                (double)(float)((double)CONCAT44(0x43300000,uVar8) - DOUBLE_8043c198)) +
         (float)((double)CONCAT44(0x43300000,pfVar7) - DOUBLE_8043c198);
    iVar6 = iVar6 / (int)*(short *)(&DAT_80391a4c + iVar10 * 2);
    iVar4 = iVar6 / 10 + (iVar6 >> 0x1f);
    uVar5 = iVar6 + (iVar4 - (iVar4 >> 0x1f)) * -10;
    if ((*(ushort *)(param_1 + 0x1c) & 4) != 0) {
      uVar5 = uVar5 + 10;
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - DOUBLE_8043c198),
                dVar2,(double)*(float *)(param_1 + 0x148),in_f4,in_f5,in_f6,in_f7,in_f8,param_1,0,
                pfVar7,uVar8,iVar9,in_r8,in_r9,in_r10);
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801e2940  FUN_801e2940 ====

void FUN_801e2940(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  float *pfVar2;
  
  dVar1 = DOUBLE_8043c198;
  pfVar2 = (float *)(*(int *)(DAT_80436354 + 100) + 1);
  if (8 < (int)pfVar2) {
    pfVar2 = (float *)0x8;
  }
  if (*(float **)(param_9 + 0x180) != pfVar2) {
    *(float **)(param_9 + 0x180) = pfVar2;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar2 ^ 0x80000000) - dVar1),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar2,param_12,
                param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801e29bc  FUN_801e29bc ====

void FUN_801e29bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e29dc  FUN_801e29dc ====

void FUN_801e29dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e29fc  zz_01e29fc_ ====

void zz_01e29fc_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x14;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801e2afc;
    *(code **)(puVar1 + 0x10c) = FUN_801e2fb4;
    puVar1[0x13] = 2;
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



// ==== 801e2afc  FUN_801e2afc ====

void FUN_801e2afc(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_80391a58)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801e2b4c  FUN_801e2b4c ====

void FUN_801e2b4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x14;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043c1a0;
  *(float *)(param_9 + 0x5c) = FLOAT_8043c1a0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0x3c;
  *(undefined2 *)(param_9 + 0x70) = 0x8000;
  *(undefined2 *)(param_9 + 0x7c) = 0x444;
  *(undefined2 *)(param_9 + 0x7e) = 0x444;
  iVar3 = *(int *)(iVar4 + 200);
  if ((iVar3 == 0) || ((*(byte *)(param_9 + 0xd0) & 4) == 0)) {
    local_18 = *(float *)(iVar4 + 0x8dc);
    local_14 = *(undefined4 *)(iVar4 + 0x8ec);
    local_10 = *(undefined4 *)(iVar4 + 0x8fc);
    gnt4_PSQUATScale_bl((double)FLOAT_8043c1a4,&local_18,&local_18);
    gnt4_PSVECAdd_bl((float *)(iVar4 + 0x20),&local_18,(float *)(param_9 + 0x20));
    if (*(float *)(DAT_8043625c + 0x3c) <= *(float *)(param_9 + 0x20)) {
      if (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_9 + 0x20)) {
        *(float *)(param_9 + 0x20) = *(float *)(DAT_8043625c + 0x38);
      }
    }
    else {
      *(float *)(param_9 + 0x20) = *(float *)(DAT_8043625c + 0x3c);
    }
    if (*(float *)(DAT_8043625c + 0x44) <= *(float *)(param_9 + 0x28)) {
      if (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_9 + 0x28)) {
        *(float *)(param_9 + 0x28) = *(float *)(DAT_8043625c + 0x40);
      }
    }
    else {
      *(float *)(param_9 + 0x28) = *(float *)(DAT_8043625c + 0x44);
    }
  }
  else {
    uVar2 = *(undefined4 *)(iVar3 + 0x68);
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar3 + 100);
    *(undefined4 *)(param_9 + 0x24) = uVar2;
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar3 + 0x6c);
  }
  uVar5 = zz_00f036c_(param_9,0x103);
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb374;
  zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54)
              ,*(int *)(param_9 + 0xe0),(float *)0x96,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 801e2cdc  FUN_801e2cdc ====

void FUN_801e2cdc(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7e);
    *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
    dVar6 = zz_0045238_(*(short *)(param_9 + 0x70));
    dVar8 = (double)FLOAT_8043c1ac;
    fVar1 = (float)(dVar8 * dVar6 + (double)FLOAT_8043c1a8);
    *(float *)(param_9 + 0x60) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    if (*(short *)(param_9 + 0x1c) < 1) {
      iVar4 = zz_008ac80_(param_9,0xc);
      fVar1 = FLOAT_8043c1a0;
      if (iVar4 != 0) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(undefined2 *)(param_9 + 0x1c) = 0x19;
        *(float *)(param_9 + 0x58) = fVar1;
        *(float *)(param_9 + 0x5c) = fVar1;
        *(float *)(param_9 + 0x60) = fVar1;
        *(undefined1 *)(param_9 + 0x154) = 0;
        *(undefined1 *)(param_9 + 0x155) = 0;
        *(float *)(param_9 + 0x144) = fVar1;
        *(float *)(param_9 + 0x148) = fVar1;
        *(undefined1 *)(param_9 + 0x156) = 0;
        *(undefined1 *)(param_9 + 0x157) = 0;
        *(float *)(param_9 + 0x14c) = fVar1;
        *(float *)(param_9 + 0x150) = fVar1;
        uVar7 = zz_000726c_(dVar6,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(float *)0x97,
                            (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
        zz_000726c_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe4),(float *)0x98,
                    (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
      }
    }
    else {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
    }
  }
  else {
    if ((*(byte *)(param_9 + 0x1d9) & 0x10) != 0) {
      *(ushort *)(param_9 + 0x272) = *(ushort *)(param_9 + 0x272) | 1;
    }
    sVar5 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar5;
    if (sVar5 < 1) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      zz_008aff0_(param_9);
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
    else {
      cVar2 = *(char *)(param_9 + 0x154);
      if (cVar2 == '\x01') {
        *(float *)(param_9 + 0x144) = *(float *)(param_9 + 0x144) - FLOAT_8043c1b4;
        *(char *)(param_9 + 0x156) = *(char *)(param_9 + 0x156) + '\x01';
        fVar1 = FLOAT_8043c1b8;
        if ('\x18' < *(char *)(param_9 + 0x156)) {
          *(undefined1 *)(param_9 + 0x154) = 2;
          *(float *)(param_9 + 0x144) = fVar1;
        }
      }
      else if ((cVar2 < '\x01') && (-1 < cVar2)) {
        *(float *)(param_9 + 0x144) = *(float *)(param_9 + 0x144) - FLOAT_8043c1b0;
        *(char *)(param_9 + 0x156) = *(char *)(param_9 + 0x156) + '\x01';
        fVar1 = FLOAT_8043c1ac;
        if ('\x02' < *(char *)(param_9 + 0x156)) {
          *(undefined1 *)(param_9 + 0x154) = 1;
          *(float *)(param_9 + 0x144) = fVar1;
        }
      }
      fVar1 = FLOAT_8043c1bc;
      cVar2 = *(char *)(param_9 + 0x155);
      if (((cVar2 != '\x01') && (cVar2 < '\x01')) && (-1 < cVar2)) {
        *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) + FLOAT_8043c1bc;
        *(float *)(param_9 + 0x150) = *(float *)(param_9 + 0x150) - fVar1;
        *(char *)(param_9 + 0x157) = *(char *)(param_9 + 0x157) + '\x01';
        fVar1 = FLOAT_8043c1c0;
        if ('\t' < *(char *)(param_9 + 0x157)) {
          *(undefined1 *)(param_9 + 0x155) = 1;
          fVar3 = FLOAT_8043c1c4;
          *(float *)(param_9 + 0x148) = fVar1;
          *(float *)(param_9 + 0x150) = fVar3;
        }
        zz_0007cac_((double)*(float *)(param_9 + 0x150),*(int *)(param_9 + 0xe4));
      }
    }
  }
  return;
}



// ==== 801e2f58  FUN_801e2f58 ====

void FUN_801e2f58(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801e2f94  FUN_801e2f94 ====

void FUN_801e2f94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e2fb4  FUN_801e2fb4 ====

void FUN_801e2fb4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  float afStack_38 [13];
  
  if (*(char *)(param_9 + 0x19) == '\0') {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  else {
    dVar2 = (double)*(float *)(param_9 + 0x144);
    dVar4 = dVar2;
    gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_38);
    pfVar1 = afStack_38;
    uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar3,dVar2,dVar4,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
                afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
    dVar2 = (double)*(float *)(param_9 + 0x148);
    dVar4 = dVar2;
    gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_38);
    pfVar1 = afStack_38;
    uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar3,dVar2,dVar4,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
                (float *)(param_9 + 0x114),(undefined *)pfVar1,param_12,param_13,param_14,param_15,
                param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



