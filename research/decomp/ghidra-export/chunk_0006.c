// ==== 80049e58  zz_0049e58_ ====

int zz_0049e58_(int param_1,int param_2)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 0x1d88) == 0) || (*(int *)(param_1 + 0x1d8c) == 0)) {
    iVar1 = 1;
  }
  else if ((param_2 == 1) &&
          ((*(char *)(param_1 + 0x578) == '\x01' && (*(char *)(param_1 + 0x1db3) == '\x01')))) {
    iVar1 = 0;
  }
  else {
    iVar1 = param_1 + param_2 * 0x40 + 0x1ad4;
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(iVar1 + 8);
    *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(iVar1 + 0xc);
    (*(code *)(&PTR_FUN_802d0d84)[*(char *)(iVar1 + 0x2f)])(param_1,iVar1);
    iVar1 = (int)*(char *)(iVar1 + 0x2e);
  }
  return iVar1;
}



// ==== 80049f10  FUN_80049f10 ====

void FUN_80049f10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                 undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  float *pfVar5;
  undefined1 uStack_18;
  char local_17 [3];
  undefined1 uStack_14;
  char local_13 [3];
  float local_10 [2];
  
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  fVar1 = *(float *)(param_10 + 0xc);
  *(float *)(param_10 + 0xc) = (float)((double)fVar1 + (double)*(float *)(param_9 + 0x1dc8));
  if (*(char *)(param_10 + 0x36) == '\0') {
    zz_004a830_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                param_11,2,param_14,param_15,param_16);
  }
  else {
    pcVar3 = local_13;
    pcVar4 = local_17;
    pfVar5 = local_10;
    zz_0049184_(param_9,param_11,&uStack_14,&uStack_18,pcVar3,pcVar4,pfVar5);
    iVar2 = param_9 + param_11 * 0x40;
    if ((*(char *)(iVar2 + 0x1bfc) == local_13[0]) && (*(char *)(iVar2 + 0x1bfd) == local_17[0])) {
      FUN_80049dac((double)local_10[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   param_9,param_11);
    }
    else {
      FUN_80049cc4((double)local_10[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   param_9,param_11,(int)local_13[0],(int)local_17[0],pcVar3,pcVar4,pfVar5,param_16)
      ;
    }
  }
  return;
}



// ==== 8004a00c  FUN_8004a00c ====

void FUN_8004a00c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                 undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(param_10 + 0x1c) = *(float *)(param_10 + 0x1c) + *(float *)(param_9 + 0x1dc8);
  fVar1 = *(float *)(param_10 + 0x1c);
  fVar2 = *(float *)(param_10 + 0x18);
  if (fVar2 <= fVar1) {
    fVar3 = *(float *)(param_10 + 0xc);
    *(float *)(param_10 + 0xc) = (float)((double)fVar3 + (double)(fVar1 - fVar2));
    zz_004a830_((double)fVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                param_11,1,param_14,param_15,param_16);
    *(undefined1 *)(param_10 + 0x2f) = 0;
  }
  else {
    dVar4 = (double)FLOAT_804370f0;
    *(float *)(param_10 + 0x20) = (float)(dVar4 - (double)(fVar1 / fVar2));
    zz_004a830_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,param_11,0
                ,param_14,param_15,param_16);
    FUN_8004a8cc((double)*(float *)(param_10 + 0x20),param_9,param_11);
  }
  return;
}



// ==== 8004a0e0  FUN_8004a0e0 ====

void FUN_8004a0e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                 undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  double dVar2;
  
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(param_10 + 0x1c) = *(float *)(param_10 + 0x1c) + *(float *)(param_9 + 0x1dc8);
  if (*(float *)(param_10 + 0x18) <= *(float *)(param_10 + 0x1c)) {
    fVar1 = *(float *)(param_10 + 0xc);
    *(float *)(param_10 + 0xc) =
         (float)((double)fVar1 + (double)(*(float *)(param_10 + 0x1c) - *(float *)(param_10 + 0x18))
                );
    zz_004a830_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                param_11,1,param_14,param_15,param_16);
    *(undefined1 *)(param_10 + 0x2f) = 0;
  }
  else {
    dVar2 = (double)FLOAT_804370f0;
    *(float *)(param_10 + 0xc) = *(float *)(param_10 + 0xc) + *(float *)(param_9 + 0x1dc8);
    *(float *)(param_10 + 0x20) =
         (float)(dVar2 - (double)(float)((double)*(float *)(param_10 + 0x1c) /
                                        (double)*(float *)(param_10 + 0x18)));
    zz_004a830_((double)*(float *)(param_10 + 0x1c),dVar2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,0,param_11,2,param_14,param_15,param_16);
    FUN_8004a8cc((double)*(float *)(param_10 + 0x20),param_9,param_11);
  }
  return;
}



// ==== 8004a1cc  FUN_8004a1cc ====

void FUN_8004a1cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11)

{
  float fVar1;
  int iVar2;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  double dVar4;
  
  iVar2 = param_9 + param_11 * 0x40 + 0x1bd4;
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(iVar2 + 8) = *(float *)(iVar2 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(param_10 + 0x1c) = *(float *)(param_10 + 0x1c) + *(float *)(param_9 + 0x1dc8);
  if (*(float *)(param_10 + 0x18) <= *(float *)(param_10 + 0x1c)) {
    fVar1 = *(float *)(param_10 + 0xc);
    *(float *)(param_10 + 0xc) =
         (float)((double)fVar1 + (double)(*(float *)(param_10 + 0x1c) - *(float *)(param_10 + 0x18))
                );
    zz_004a830_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                param_11,1,iVar2,in_r9,in_r10);
    *(undefined1 *)(param_10 + 0x2f) = 0;
  }
  else {
    dVar4 = (double)FLOAT_804370f0;
    *(float *)(iVar2 + 0xc) = *(float *)(iVar2 + 0xc) + *(float *)(param_9 + 0x1dc8);
    *(float *)(param_10 + 0x20) =
         (float)(dVar4 - (double)(float)((double)*(float *)(param_10 + 0x1c) /
                                        (double)*(float *)(param_10 + 0x18)));
    uVar3 = zz_004a830_((double)*(float *)(param_10 + 0x1c),dVar4,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,0,0,param_11,0,iVar2,in_r9,in_r10);
    zz_004a830_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,1,param_11,2,
                iVar2,in_r9,in_r10);
    FUN_8004a8cc((double)*(float *)(param_10 + 0x20),param_9,param_11);
  }
  return;
}



// ==== 8004a2ec  FUN_8004a2ec ====

void FUN_8004a2ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11)

{
  float fVar1;
  int iVar2;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  double dVar4;
  
  iVar2 = param_9 + param_11 * 0x40 + 0x1bd4;
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(iVar2 + 8) = *(float *)(iVar2 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(param_10 + 0x1c) = *(float *)(param_10 + 0x1c) + *(float *)(param_9 + 0x1dc8);
  if (*(float *)(param_10 + 0x18) <= *(float *)(param_10 + 0x1c)) {
    fVar1 = *(float *)(param_10 + 0xc);
    *(float *)(param_10 + 0xc) =
         (float)((double)fVar1 + (double)(*(float *)(param_10 + 0x1c) - *(float *)(param_10 + 0x18))
                );
    zz_004a830_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,
                param_11,1,iVar2,in_r9,in_r10);
    *(undefined1 *)(param_10 + 0x2f) = 0;
  }
  else {
    dVar4 = (double)FLOAT_804370f0;
    *(float *)(param_10 + 0xc) = *(float *)(param_10 + 0xc) + *(float *)(param_9 + 0x1dc8);
    *(float *)(iVar2 + 0xc) = *(float *)(iVar2 + 0xc) + *(float *)(param_9 + 0x1dc8);
    *(float *)(param_10 + 0x20) =
         (float)(dVar4 - (double)(float)((double)*(float *)(param_10 + 0x1c) /
                                        (double)*(float *)(param_10 + 0x18)));
    uVar3 = zz_004a830_((double)*(float *)(param_10 + 0x1c),dVar4,param_3,param_4,param_5,param_6,
                        param_7,param_8,param_9,0,0,param_11,2,iVar2,in_r9,in_r10);
    zz_004a830_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,1,param_11,2,
                iVar2,in_r9,in_r10);
    FUN_8004a8cc((double)*(float *)(param_10 + 0x20),param_9,param_11);
  }
  return;
}



// ==== 8004a41c  zz_004a41c_ ====

void zz_004a41c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  iVar4 = param_9 + param_11 * 0x40;
  puVar2 = (undefined1 *)
           zz_004d1f4_(param_9,(int)*(char *)(param_9 + 0x1b3c),(int)*(char *)(param_9 + 0x1b3d));
  *(undefined1 *)(iVar4 + 0x1c05) = *(undefined1 *)(param_9 + 0x1b45);
  *(undefined1 *)(iVar4 + 0x1bfc) = *(undefined1 *)(param_9 + 0x1b3c);
  *(undefined1 *)(iVar4 + 0x1bfd) = *(undefined1 *)(param_9 + 0x1b3d);
  *(undefined1 *)(iVar4 + 0x1c04) = *(undefined1 *)(param_9 + 0x1b44);
  *(undefined4 *)(iVar4 + 0x1bdc) = *(undefined4 *)(param_9 + 0x1b1c);
  *(undefined4 *)(iVar4 + 0x1be0) = *(undefined4 *)(param_9 + 0x1b20);
  zz_004d244_(param_9,param_11,iVar4 + 0x1bd4,puVar2);
  zz_004a754_((double)*(float *)(iVar4 + 0x1be0),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,1,1,param_11,param_13,param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x1b43) != '\0') {
    param_3 = (double)*(float *)(iVar4 + 0x1aec);
    param_2 = (double)(float)(param_3 - (double)*(float *)(iVar4 + 0x1af0));
    dVar5 = (double)(*(float *)(param_9 + 0x1b2c) - *(float *)(param_9 + 0x1b30));
    if (param_2 < dVar5) {
      *(float *)(iVar4 + 0x1aec) =
           (float)(param_3 + (double)(FLOAT_804370f0 + (float)(dVar5 - param_2)));
    }
  }
  *(float *)(iVar4 + 0x1af0) = *(float *)(iVar4 + 0x1af0) + *(float *)(param_9 + 0x1dc8);
  *(undefined4 *)(iVar4 + 0x1adc) = *(undefined4 *)(param_9 + 0x1b1c);
  *(undefined4 *)(iVar4 + 0x1ae0) = *(undefined4 *)(param_9 + 0x1b20);
  if (*(float *)(iVar4 + 0x1aec) <= *(float *)(iVar4 + 0x1af0)) {
    *(undefined1 *)(iVar4 + 0x1b03) = 0;
    iVar3 = param_9 + param_11 * 0x20;
    *(undefined1 *)(param_9 + 0x1d9a) = 0;
    uVar1 = *(undefined4 *)(param_9 + 0x1cf8);
    *(undefined4 *)(iVar3 + 0x1cd4) = *(undefined4 *)(param_9 + 0x1cf4);
    *(undefined4 *)(iVar3 + 0x1cd8) = uVar1;
    uVar1 = *(undefined4 *)(param_9 + 0x1d00);
    *(undefined4 *)(iVar3 + 0x1cdc) = *(undefined4 *)(param_9 + 0x1cfc);
    *(undefined4 *)(iVar3 + 0x1ce0) = uVar1;
    uVar1 = *(undefined4 *)(param_9 + 0x1d08);
    *(undefined4 *)(iVar3 + 0x1ce4) = *(undefined4 *)(param_9 + 0x1d04);
    *(undefined4 *)(iVar3 + 0x1ce8) = uVar1;
    uVar1 = *(undefined4 *)(param_9 + 0x1d10);
    *(undefined4 *)(iVar3 + 0x1cec) = *(undefined4 *)(param_9 + 0x1d0c);
    *(undefined4 *)(iVar3 + 0x1cf0) = uVar1;
    *(undefined1 *)(iVar4 + 0x1b04) = *(undefined1 *)(param_9 + 0x1b44);
    zz_0048648_((double)*(float *)(param_9 + 0x1b20),param_2,param_3,param_4,param_5,param_6,param_7
                ,param_8,param_9,param_11,(int)*(char *)(param_9 + 0x1b3c),
                (int)*(char *)(param_9 + 0x1b3d),
                (int)(*(float *)(param_9 + 0x1b2c) - *(float *)(param_9 + 0x1b30)),
                (int)*(char *)(param_9 + 0x1b43),param_15,param_16);
    *(undefined4 *)(iVar4 + 0x1adc) = *(undefined4 *)(param_9 + 0x1b1c);
  }
  else {
    *(float *)(iVar4 + 0x1af4) = *(float *)(iVar4 + 0x1af0) / *(float *)(iVar4 + 0x1aec);
    FUN_8004a8cc((double)*(float *)(iVar4 + 0x1af4),param_9,param_11);
  }
  return;
}



// ==== 8004a60c  FUN_8004a60c ====

void FUN_8004a60c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,int param_11)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  undefined4 *in_r10;
  char local_28;
  char local_27 [3];
  char local_24;
  char local_23 [3];
  float local_20 [5];
  
  *(float *)(param_10 + 8) = *(float *)(param_10 + 8) + *(float *)(param_9 + 0x1dc8);
  *(float *)(param_10 + 0x1c) = *(float *)(param_10 + 0x1c) + *(float *)(param_9 + 0x1dc8);
  fVar1 = *(float *)(param_10 + 0x1c);
  fVar2 = *(float *)(param_10 + 0x18);
  if (fVar2 <= fVar1) {
    pfVar3 = local_20;
    *(float *)(param_10 + 0xc) = *(float *)(param_10 + 0xc) + (fVar1 - fVar2);
    zz_0049184_(param_9,param_11,&local_24,&local_28,local_23,local_27,pfVar3);
    zz_0049b98_((double)local_20[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                param_11,(int)local_24,(int)local_28,(int)local_23[0],(int)local_27[0],pfVar3,in_r10
               );
    *(undefined1 *)(param_10 + 0x2f) = 0;
  }
  else {
    *(float *)(param_10 + 0x20) = FLOAT_804370f0 - fVar1 / fVar2;
    zz_0049184_(param_9,param_11,&local_24,&local_28,local_23,local_27,local_20);
    zz_00496d8_((double)local_20[0],param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                0,param_11,(int)local_24,(int)local_28,(int)local_23[0],
                (undefined4 *)(int)local_27[0],in_r10);
    FUN_8004a8cc((double)*(float *)(param_10 + 0x20),param_9,param_11);
  }
  return;
}



// ==== 8004a754  zz_004a754_ ====

void zz_004a754_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int *piVar2;
  undefined8 uVar3;
  int local_18;
  int local_14;
  
  piVar2 = (int *)(param_9 + param_10 * 0x100 + param_12 * 0x40 + 0x1ad4);
  *(char *)((int)piVar2 + 0x35) = (char)param_11;
  if (*(char *)((int)piVar2 + 0x31) == '\0') {
    *piVar2 = *(int *)(param_9 + 0x1d78);
  }
  else {
    *piVar2 = *(int *)(param_9 + 0x1d7c);
  }
  *(undefined1 *)((int)piVar2 + 0x2e) = 0;
  uVar1 = zz_004d548_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,
                      param_10 * 0x100,param_11,param_12,param_13,param_14,param_15,param_16);
  *(char *)(piVar2 + 0xe) = (char)uVar1;
  if ((char)uVar1 != '\0') {
    *(undefined1 *)((int)piVar2 + 0x2e) = 1;
  }
  uVar3 = zz_004b8f4_(param_9,param_12,&local_18);
  for (; local_18 < local_14; local_18 = local_18 + 1) {
    uVar3 = zz_004aae0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,piVar2
                        ,*(char *)(*(int *)(param_9 + 0x4b0) + local_18 + 0x8c),1,param_13,param_14,
                        param_15,param_16);
  }
  return;
}



// ==== 8004a830  zz_004a830_ ====

void zz_004a830_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined1 param_11,int param_12,uint param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int *piVar2;
  undefined8 uVar3;
  int local_18;
  int local_14;
  
  piVar2 = (int *)(param_9 + param_10 * 0x100 + param_12 * 0x40 + 0x1ad4);
  *(undefined1 *)((int)piVar2 + 0x35) = param_11;
  uVar1 = param_13;
  uVar3 = zz_004b8f4_(param_9,param_12,&local_18);
  for (; local_18 < local_14; local_18 = local_18 + 1) {
    uVar3 = zz_004aae0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,piVar2
                        ,*(char *)(*(int *)(param_9 + 0x4b0) + local_18 + 0x8c),param_13,uVar1,
                        param_14,param_15,param_16);
  }
  return;
}



// ==== 8004a8cc  FUN_8004a8cc ====

/* WARNING: Removing unreachable block (ram,0x8004aac4) */
/* WARNING: Removing unreachable block (ram,0x8004aabc) */
/* WARNING: Removing unreachable block (ram,0x8004a8e4) */
/* WARNING: Removing unreachable block (ram,0x8004a8dc) */

void FUN_8004a8cc(double param_1,int param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  int local_78;
  int local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [3];
  float afStack_44 [4];
  
  dVar6 = (double)(float)((double)FLOAT_804370f0 - param_1);
  zz_004b8f4_(param_2,param_3,&local_78);
  iVar4 = local_78;
  do {
    if (local_74 <= iVar4) {
      return;
    }
    iVar3 = (int)*(char *)(*(int *)(param_2 + 0x4b0) + iVar4 + 0x8c);
    iVar2 = param_2 + iVar3 * 0xc;
    pfVar1 = (float *)(iVar2 + 0x12d4);
    gnt4_PSQUATScale_bl(dVar6,pfVar1,afStack_44);
    gnt4_PSQUATScale_bl(param_1,(float *)(iVar2 + 0x1454),afStack_50);
    gnt4_PSVECAdd_bl(afStack_44,afStack_50,pfVar1);
    iVar2 = param_2 + iVar3 * 0x10;
    local_60 = *(float *)(iVar2 + 0xed4);
    local_5c = *(float *)(iVar2 + 0xed8);
    local_58 = *(float *)(iVar2 + 0xedc);
    local_54 = *(float *)(iVar2 + 0xee0);
    local_70 = *(float *)(iVar2 + 0x10d4);
    local_6c = *(float *)(iVar2 + 0x10d8);
    local_68 = *(float *)(iVar2 + 0x10dc);
    local_64 = *(float *)(iVar2 + 0x10e0);
    if ((local_54 + local_64) * (local_54 + local_64) +
        (local_58 + local_68) * (local_58 + local_68) +
        (local_60 + local_70) * (local_60 + local_70) +
        (local_5c + local_6c) * (local_5c + local_6c) <
        (local_54 - local_64) * (local_54 - local_64) +
        (local_58 - local_68) * (local_58 - local_68) +
        (local_60 - local_70) * (local_60 - local_70) +
        (local_5c - local_6c) * (local_5c - local_6c)) {
      local_70 = -local_70;
      local_6c = -local_6c;
      local_68 = -local_68;
      local_64 = -local_64;
    }
    C_QUATSlerp(param_1,&local_60,&local_70,(float *)(iVar2 + 0xed4));
    iVar2 = 0;
    iVar5 = 2;
    do {
      if (*(char *)(*(int *)(param_2 + 0x4b0) + iVar2 + 0x42) == iVar3) {
        if (param_1 <= (double)FLOAT_80437104) {
          *(undefined1 *)(param_2 + iVar2 + 0x1d94) = *(undefined1 *)(param_2 + iVar2 + 0x1d74);
        }
        else {
          *(undefined1 *)(param_2 + iVar2 + 0x1d94) = *(undefined1 *)(param_2 + iVar2 + 0x1d76);
        }
        break;
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar4 = iVar4 + 1;
  } while( true );
}



// ==== 8004aae0  zz_004aae0_ ====

void zz_004aae0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int *param_10,char param_11
                ,uint param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*param_10 == 0) {
    *(undefined1 *)((int)param_10 + 0x2e) = 1;
  }
  else {
    cVar1 = param_11;
    if (*(char *)(param_10 + 0xc) != '\0') {
      cVar1 = *(char *)(*(int *)(param_9 + 0x4b0) + (int)param_11 + 0x6c);
    }
    if (param_11 == '\0') {
      *(undefined4 *)(param_9 + 0x1da0) = *(undefined4 *)(param_9 + 0x12d4);
      *(undefined4 *)(param_9 + 0x1da4) = *(undefined4 *)(param_9 + 0x12d8);
      *(undefined4 *)(param_9 + 0x1da8) = *(undefined4 *)(param_9 + 0x12dc);
      zz_004acdc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  (int)param_10,0,(int)cVar1,param_12,*(undefined4 *)(param_9 + 0x12d4),param_15,
                  param_16);
      fVar2 = FLOAT_804370f4;
      if ((((param_12 & 2) == 0) || (*(char *)((int)param_10 + 0x2f) != '\0')) ||
         ((float)param_10[3] <= FLOAT_804370f4)) {
        *(float *)(param_9 + 0x1da8) = FLOAT_804370f4;
        *(float *)(param_9 + 0x1da4) = fVar2;
        *(float *)(param_9 + 0x1da0) = fVar2;
        *(float *)(param_9 + 0x1dac) = fVar2;
        *(undefined2 *)(param_9 + 0x1db0) = 0;
      }
      else {
        gnt4_PSVECSubtract_bl
                  ((float *)(param_9 + 0x12d4),(float *)(param_9 + 0x1da0),
                   (float *)(param_9 + 0x1da0));
        if ((*(char *)(param_9 + 0x1db2) == '\0') && (-1 < *(char *)((int)param_10 + 0x32))) {
          fVar2 = (FLOAT_804370f0 + *(float *)(param_9 + 0x1d9c)) *
                  *(float *)(param_9 + *(char *)((int)param_10 + 0x32) * 4 + 0x1dd4);
        }
        else {
          fVar2 = FLOAT_804370f0 + *(float *)(param_9 + 0x1d9c);
        }
        gnt4_PSQUATScale_bl((double)fVar2,(float *)(param_9 + 0x1da0),(float *)(param_9 + 0x1da0));
        dVar4 = gnt4_PSVECMag_bl((float *)(param_9 + 0x1da0));
        *(float *)(param_9 + 0x1dac) = (float)(dVar4 / (double)*(float *)(param_9 + 0x5f4));
        iVar3 = FUN_800452a0((double)*(float *)(param_9 + 0x1da0),
                             (double)*(float *)(param_9 + 0x1da8));
        *(short *)(param_9 + 0x1db0) = (short)iVar3;
        if (*(char *)(param_9 + 0x1d9b) != '\0') {
          gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x1da0),
                              (float *)(param_9 + 0x1da0));
          zz_00453fc_('y',(float *)(param_9 + 0x1da0),(float *)(param_9 + 0x1da0),
                      *(short *)(param_9 + 0x5ae));
          fVar2 = FLOAT_804370f4;
          if (*(char *)(param_9 + 0x598) != '\0') {
            *(float *)(param_9 + 0x1da8) = FLOAT_804370f4;
            *(float *)(param_9 + 0x1da0) = fVar2;
          }
          gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x1da0),
                           (float *)(param_9 + 0x20));
        }
      }
    }
    else {
      zz_004acdc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  (int)param_10,(int)param_11,(int)cVar1,param_12,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8004acdc  zz_004acdc_ ====

void zz_004acdc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,uint param_11,
                int param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  float *pfVar1;
  uint uVar2;
  int *piVar3;
  double dVar4;
  
  if ((int)param_11 < (int)*(char *)(param_9 + 0x1d90)) {
    uVar2 = (uint)*(byte *)(param_10 + 0x33);
    piVar3 = *(int **)(*(int *)(param_9 + (char)*(byte *)(param_10 + 0x33) * 4 + 0x1db4) +
                      param_11 * 4);
    dVar4 = (double)zz_004adc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,param_10,piVar3,param_11,param_13,uVar2,param_15,param_16);
    zz_004b76c_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                (int)piVar3,
                (float *)(param_9 + *(char *)(param_10 + 0x35) * 0x180 + param_12 * 0xc + 0x12d4),
                (float *)(param_9 + *(char *)(param_10 + 0x35) * 0x200 + param_12 * 0x10 + 0xed4),
                uVar2,param_15,param_16);
    if ((-1 < *(char *)(param_10 + 0x32)) && (param_12 == 1)) {
      pfVar1 = (float *)(param_9 + *(char *)(param_10 + 0x35) * 0x180 + 0x12e0);
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + *(char *)(param_10 + 0x32) * 4 + 0x1dd4),
                          pfVar1,pfVar1);
    }
  }
  return;
}



// ==== 8004adc8  zz_004adc8_ ====

/* WARNING: Removing unreachable block (ram,0x8004b744) */
/* WARNING: Removing unreachable block (ram,0x8004add8) */
/* WARNING: Removing unreachable block (ram,0x8004b5a8) */
/* WARNING: Removing unreachable block (ram,0x8004b4b0) */
/* WARNING: Removing unreachable block (ram,0x8004b378) */
/* WARNING: Removing unreachable block (ram,0x8004b1c8) */
/* WARNING: Removing unreachable block (ram,0x8004b154) */
/* WARNING: Removing unreachable block (ram,0x8004b02c) */
/* WARNING: Removing unreachable block (ram,0x8004b0c0) */
/* WARNING: Removing unreachable block (ram,0x8004b23c) */
/* WARNING: Removing unreachable block (ram,0x8004b2b0) */
/* WARNING: Removing unreachable block (ram,0x8004aeb8) */
/* WARNING: Removing unreachable block (ram,0x8004b414) */
/* WARNING: Removing unreachable block (ram,0x8004b52c) */
/* WARNING: Removing unreachable block (ram,0x8004b624) */
/* WARNING: Removing unreachable block (ram,0x8004af44) */

void zz_004adc8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int *param_11,
                uint param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  bool bVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  uint uVar13;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined *puVar14;
  int *piVar15;
  undefined4 uVar16;
  undefined4 *puVar17;
  double dVar18;
  undefined8 uVar19;
  double dVar20;
  double local_28;
  
  if ((param_13 & 1) == 0) {
    if (((param_13 & 2) != 0) && (param_11[0x1f] != 0)) {
      piVar15 = param_11;
      uVar19 = zz_0243fc0_((double)*(float *)(param_9 + 0x1dc8),param_11[0x1f]);
      gnt4_HSD_JObjAnim(uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_11,
                        extraout_r4_00,piVar15,param_12,param_13,param_14,param_15,param_16);
      *(byte *)(param_10 + 0x2d) = (byte)((uint)*(undefined4 *)param_11[0x1f] >> 0x1a) & 1;
    }
  }
  else {
    iVar8 = zz_0006f98_(param_9);
    iVar7 = DAT_802b0bd4;
    puVar6 = DAT_802b0bd0;
    iVar5 = DAT_802b0bcc;
    iVar10 = DAT_802b0bc8;
    iVar11 = *(int *)(*(int *)(param_10 + 4) + 0xc);
    iVar8 = iVar8 + param_12 * 0x30;
    fVar1 = *(float *)(iVar8 + 0xc);
    dVar20 = (double)fVar1;
    fVar2 = *(float *)(iVar8 + 0x1c);
    dVar18 = (double)fVar2;
    fVar3 = *(float *)(iVar8 + 0x2c);
    if (param_12 < *(uint *)(iVar11 + 0xc)) {
      pcVar9 = (char *)zz_025b178_(iVar11,param_12);
      iVar10 = gnt4_HSD_ArchiveGetPublicAddress_bl(*(int *)(*(int *)(param_10 + 4) + 0xc),pcVar9);
      pcVar9 = (char *)0x0;
      uVar16 = 0;
      uVar19 = gnt4_HSD_JObjAddAnim
                         (dVar18,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_11,iVar10,(undefined4 *)0x0,0,param_13,param_14,param_15,
                          param_16);
      if (param_11[0x1f] == 0) {
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2a4,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        if ((param_11[5] & 0x20000U) != 0) {
          pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2a5,s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,
                                    uVar16,param_13,param_14,param_15,param_16);
        }
        param_11[7] = (int)FLOAT_804370f4;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                               (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_11,uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2b8,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        if ((param_11[5] & 0x20000U) != 0) {
          pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2b9,s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,
                                    uVar16,param_13,param_14,param_15,param_16);
        }
        param_11[8] = (int)FLOAT_804370f4;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                               (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_11,uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2cc,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        if ((param_11[5] & 0x20000U) != 0) {
          pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x2cd,s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,
                                    uVar16,param_13,param_14,param_15,param_16);
        }
        param_11[9] = (int)FLOAT_804370f4;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                               (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_11,uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x3b8,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        param_11[0xe] = (int)fVar1;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                               (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_11,uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
        dVar18 = (double)fVar2;
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x3c6,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        param_11[0xf] = (int)(float)dVar18;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                               (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_11,uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
        dVar18 = (double)fVar3;
        if (param_11 == (int *)0x0) {
          pcVar9 = &DAT_80437110;
          uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_80437108,0x3d4,&DAT_80437110,uVar16,param_13,param_14,
                                    param_15,param_16);
        }
        param_11[0x10] = (int)(float)dVar18;
        if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
          uVar12 = param_11[5];
          bVar4 = false;
          if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
            bVar4 = true;
          }
          if (!bVar4) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,param_11,uVar12
                       ,pcVar9,uVar16,param_13,param_14,param_15,param_16);
          }
        }
      }
      else {
        uVar12 = 0;
        for (puVar17 = *(undefined4 **)(param_11[0x1f] + 0x14); puVar17 != (undefined4 *)0x0;
            puVar17 = (undefined4 *)*puVar17) {
          uVar12 = uVar12 | 1 << (uint)*(byte *)((int)puVar17 + 0x13);
        }
        if ((uVar12 & 2) == 0) {
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2a4,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          if ((param_11[5] & 0x20000U) != 0) {
            pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2a5,
                                      s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,uVar16,param_13,
                                      param_14,param_15,param_16);
          }
          param_11[7] = (int)FLOAT_804370f4;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar13 = param_11[5];
            bVar4 = false;
            if (((uVar13 & 0x800000) == 0) && ((uVar13 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar13,pcVar9,uVar16,param_13,param_14,param_15,param_16)
              ;
            }
          }
        }
        if ((uVar12 & 4) == 0) {
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2b8,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          if ((param_11[5] & 0x20000U) != 0) {
            pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2b9,
                                      s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,uVar16,param_13,
                                      param_14,param_15,param_16);
          }
          param_11[8] = (int)FLOAT_804370f4;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar13 = param_11[5];
            bVar4 = false;
            if (((uVar13 & 0x800000) == 0) && ((uVar13 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar13,pcVar9,uVar16,param_13,param_14,param_15,param_16)
              ;
            }
          }
        }
        if ((uVar12 & 8) == 0) {
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2cc,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          if ((param_11[5] & 0x20000U) != 0) {
            pcVar9 = s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x2cd,
                                      s___jobj_>flags___JOBJ_USE_QUATERN_802b0bd8,uVar16,param_13,
                                      param_14,param_15,param_16);
          }
          param_11[9] = (int)FLOAT_804370f4;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar13 = param_11[5];
            bVar4 = false;
            if (((uVar13 & 0x800000) == 0) && ((uVar13 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar13,pcVar9,uVar16,param_13,param_14,param_15,param_16)
              ;
            }
          }
        }
        if ((uVar12 & 0x20) == 0) {
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x3b8,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          param_11[0xe] = (int)fVar1;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar13 = param_11[5];
            bVar4 = false;
            if (((uVar13 & 0x800000) == 0) && ((uVar13 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar13,pcVar9,uVar16,param_13,param_14,param_15,param_16)
              ;
            }
          }
        }
        if ((uVar12 & 0x40) == 0) {
          dVar18 = (double)fVar2;
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x3c6,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          param_11[0xf] = (int)(float)dVar18;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar13 = param_11[5];
            bVar4 = false;
            if (((uVar13 & 0x800000) == 0) && ((uVar13 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                 (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar13,pcVar9,uVar16,param_13,param_14,param_15,param_16)
              ;
            }
          }
        }
        if ((uVar12 & 0x80) == 0) {
          dVar18 = (double)fVar3;
          if (param_11 == (int *)0x0) {
            pcVar9 = &DAT_80437110;
            uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                      &DAT_80437108,0x3d4,&DAT_80437110,uVar16,param_13,param_14,
                                      param_15,param_16);
          }
          param_11[0x10] = (int)(float)dVar18;
          if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
            uVar12 = param_11[5];
            bVar4 = false;
            if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
              bVar4 = true;
            }
            if (!bVar4) {
              gnt4_HSD_JObjSetMtxDirtySub_bl
                        (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,param_11,
                         uVar12,pcVar9,uVar16,param_13,param_14,param_15,param_16);
            }
          }
        }
        if (*(char *)(param_10 + 0x2c) == '\x01') {
          zz_0243aec_((uint *)param_11[0x1f],0x20000000);
          local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_10 + 0x26)) ^ 0x80000000);
          uVar19 = gnt4_HSD_AObjSetRewindFrame
                             ((double)(float)(local_28 - DOUBLE_804370f8),param_11[0x1f]);
        }
        else {
          uVar19 = zz_0243b08_((uint *)param_11[0x1f],0x20000000);
        }
        iVar10 = param_11[0x1f];
        if (iVar10 == 0) {
          pcVar9 = &DAT_80437120;
          gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80437118,0xab,&DAT_80437120,uVar16,param_13,param_14,param_15,
                           param_16);
        }
        *(short *)(param_10 + 0x24) = (short)(int)*(float *)(iVar10 + 0xc);
        gnt4_HSD_JObjReqAnimByFlags((double)*(float *)(param_10 + 0xc),(int)param_11,1);
        uVar19 = zz_0243fc0_((double)*(float *)(param_9 + 0x1dc8),param_11[0x1f]);
        gnt4_HSD_JObjAnim(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,param_11,
                          extraout_r4,pcVar9,uVar16,param_13,param_14,param_15,param_16);
        *(undefined1 *)(param_10 + 0x2d) = 0;
      }
    }
    else {
      puVar17 = &DAT_802b0bc8;
      puVar14 = DAT_802b0bd0;
      iVar8 = DAT_802b0bcc;
      iVar11 = DAT_802b0bc8;
      uVar19 = zz_024d4f4_(dVar18,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int)param_11,1,DAT_802b0bd0,DAT_802b0bcc,DAT_802b0bc8,&DAT_802b0bc8,
                           param_15,param_16);
      if (param_11 == (int *)0x0) {
        puVar14 = &DAT_80437110;
        uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  &DAT_80437108,0x3a9,&DAT_80437110,iVar8,iVar11,puVar17,param_15,
                                  param_16);
      }
      param_11[0xe] = (int)fVar1;
      param_11[0xf] = (int)fVar2;
      param_11[0x10] = (int)fVar3;
      if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
        uVar12 = param_11[5];
        bVar4 = false;
        if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
          bVar4 = true;
        }
        if (!bVar4) {
          uVar19 = gnt4_HSD_JObjSetMtxDirtySub_bl
                             (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,param_11
                              ,uVar12,puVar14,iVar8,iVar11,puVar17,param_15,param_16);
        }
      }
      if (param_11 == (int *)0x0) {
        puVar14 = &DAT_80437110;
        uVar19 = gnt4___assert_bl(uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,
                                  &DAT_80437108,0x290,&DAT_80437110,iVar8,iVar11,puVar17,param_15,
                                  param_16);
      }
      param_11[7] = iVar10;
      param_11[8] = iVar5;
      param_11[9] = (int)puVar6;
      param_11[10] = iVar7;
      if (((param_11[5] & 0x2000000U) == 0) && (param_11 != (int *)0x0)) {
        uVar12 = param_11[5];
        bVar4 = false;
        if (((uVar12 & 0x800000) == 0) && ((uVar12 & 0x40) != 0)) {
          bVar4 = true;
        }
        if (!bVar4) {
          gnt4_HSD_JObjSetMtxDirtySub_bl
                    (uVar19,dVar20,param_3,param_4,param_5,param_6,param_7,param_8,param_11,uVar12,
                     puVar14,iVar8,iVar11,puVar17,param_15,param_16);
        }
      }
      fVar1 = FLOAT_804370f4;
      *(undefined2 *)(param_10 + 0x24) = 0;
      *(float *)(param_10 + 0xc) = fVar1;
    }
  }
  return;
}



// ==== 8004b76c  zz_004b76c_ ====

/* WARNING: Removing unreachable block (ram,0x8004b878) */

void zz_004b76c_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,int param_10,
                int param_11,float *param_12,float *param_13,undefined4 param_14,undefined4 param_15
                ,undefined4 param_16)

{
  float fVar1;
  float *pfVar2;
  float *pfVar3;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_1c;
  
  pfVar2 = param_12;
  pfVar3 = param_13;
  if (param_11 == 0) {
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80437108,0x3e4,&DAT_80437110,param_12,param_13,
                                       param_14,param_15,param_16);
  }
  if (param_12 == (float *)0x0) {
    param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_80437108,0x3e5,s_translate_802b0c00,pfVar2,
                                       pfVar3,param_14,param_15,param_16);
  }
  fVar1 = *(float *)(param_11 + 0x3c);
  *param_12 = *(float *)(param_11 + 0x38);
  param_12[1] = fVar1;
  param_12[2] = *(float *)(param_11 + 0x40);
  if (*(char *)(param_10 + 0x30) != '\0') {
    param_1 = (double)*param_12;
    *param_12 = (float)(param_1 * (double)FLOAT_80437128);
  }
  if (param_11 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80437108,
                     0x2dd,&DAT_80437110,pfVar2,pfVar3,param_14,param_15,param_16);
  }
  local_28 = *(float *)(param_11 + 0x1c);
  local_24 = *(float *)(param_11 + 0x20);
  local_20 = *(float *)(param_11 + 0x24);
  local_1c = *(undefined4 *)(param_11 + 0x28);
  if (*(char *)(param_10 + 0x30) != '\0') {
    local_24 = local_24 * FLOAT_80437128;
    local_20 = local_20 * FLOAT_80437128;
  }
  FUN_8025acfc(&local_28,param_13);
  if (((*(int *)(param_11 + 0x7c) != 0) &&
      (*(undefined4 *)(param_10 + 0xc) = *(undefined4 *)(*(int *)(param_11 + 0x7c) + 4),
      *(char *)(param_10 + 0x2f) == '\0')) &&
     ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_10 + 0x24) ^ 0x80000000) -
             DOUBLE_804370f8) <= *(float *)(param_10 + 0xc))) {
    *(undefined1 *)(param_10 + 0x2e) = 1;
  }
  return;
}



// ==== 8004b8f4  zz_004b8f4_ ====

void zz_004b8f4_(int param_1,int param_2,int *param_3)

{
  if (param_2 == 0) {
    *param_3 = 0;
  }
  else {
    *param_3 = (int)*(char *)(param_1 + param_2 + 0x1d90);
  }
  if (param_2 == 3) {
    param_3[1] = (int)*(char *)(param_1 + 0x1d90);
    return;
  }
  param_3[1] = (int)*(char *)(param_1 + param_2 + 0x1d91);
  return;
}



// ==== 8004b94c  FUN_8004b94c ====

void FUN_8004b94c(int param_1,uint param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  uint uVar8;
  int local_18;
  int local_14;
  
  uVar8 = param_2 ^ 1;
  puVar3 = (undefined4 *)(param_1 + param_2 * 0x100 + param_3 * 0x40 + 0x1ad4);
  uVar1 = puVar3[1];
  puVar5 = (undefined4 *)(param_1 + uVar8 * 0x100 + param_3 * 0x40 + 0x1ad4);
  *puVar5 = *puVar3;
  puVar5[1] = uVar1;
  uVar1 = puVar3[3];
  puVar5[2] = puVar3[2];
  puVar5[3] = uVar1;
  uVar1 = puVar3[5];
  puVar5[4] = puVar3[4];
  puVar5[5] = uVar1;
  uVar1 = puVar3[7];
  puVar5[6] = puVar3[6];
  puVar5[7] = uVar1;
  uVar1 = puVar3[9];
  puVar5[8] = puVar3[8];
  puVar5[9] = uVar1;
  uVar1 = puVar3[0xb];
  puVar5[10] = puVar3[10];
  puVar5[0xb] = uVar1;
  uVar1 = puVar3[0xd];
  puVar5[0xc] = puVar3[0xc];
  puVar5[0xd] = uVar1;
  uVar1 = puVar3[0xf];
  puVar5[0xe] = puVar3[0xe];
  puVar5[0xf] = uVar1;
  *(char *)((int)puVar5 + 0x33) = (char)uVar8;
  if (param_3 == 0) {
    iVar4 = param_1 + param_2 * 2;
    iVar2 = param_1 + uVar8 * 2;
    *(undefined1 *)(iVar2 + 0x1d74) = *(undefined1 *)(iVar4 + 0x1d74);
    *(undefined1 *)(iVar2 + 0x1d75) = *(undefined1 *)(iVar4 + 0x1d75);
  }
  if (param_4 == 0) {
    zz_004b8f4_(param_1,param_3,&local_18);
    for (; local_18 < local_14; local_18 = local_18 + 1) {
      iVar4 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + local_18 + 0x8c);
      iVar2 = iVar4 * 0x10 + 0xed4;
      puVar6 = (undefined4 *)(param_1 + param_2 * 0x200 + iVar2);
      puVar7 = (undefined4 *)(param_1 + uVar8 * 0x200 + iVar2);
      uVar1 = puVar6[1];
      *puVar7 = *puVar6;
      iVar2 = iVar4 * 0xc + 0x12d4;
      puVar7[1] = uVar1;
      puVar3 = (undefined4 *)(param_1 + param_2 * 0x180 + iVar2);
      puVar5 = (undefined4 *)(param_1 + uVar8 * 0x180 + iVar2);
      uVar1 = puVar6[3];
      puVar7[2] = puVar6[2];
      puVar7[3] = uVar1;
      uVar1 = puVar3[1];
      *puVar5 = *puVar3;
      puVar5[1] = uVar1;
      puVar5[2] = puVar3[2];
    }
  }
  return;
}



// ==== 8004bb14  FUN_8004bb14 ====

/* WARNING: Removing unreachable block (ram,0x8004bdec) */
/* WARNING: Removing unreachable block (ram,0x8004bb24) */

void FUN_8004bb14(int param_1)

{
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined2 *puVar7;
  float *pfVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  float *pfVar13;
  int iVar14;
  double dVar15;
  float afStack_68 [14];
  
  iVar4 = *(int *)(&DAT_803c4d7c + *(char *)(param_1 + 999) * 4);
  *(int *)(param_1 + 0x1d78) = iVar4;
  if (iVar4 == 0) {
    *(undefined4 *)(param_1 + 0x1d7c) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x1d7c) = DAT_80436254;
  }
  puVar9 = (undefined4 *)(param_1 + 0x12d4);
  pfVar13 = (float *)(param_1 + 0x15d4);
  puVar12 = (undefined4 *)(param_1 + 0x1454);
  pfVar8 = (float *)(param_1 + 0x1754);
  iVar6 = zz_0006f98_(param_1);
  dVar15 = (double)FLOAT_804370f0;
  iVar4 = param_1;
  for (iVar11 = 0; iVar11 < *(char *)(param_1 + 0x1d90); iVar11 = iVar11 + 1) {
    *puVar9 = *(undefined4 *)(iVar6 + 0xc);
    puVar9[1] = *(undefined4 *)(iVar6 + 0x1c);
    puVar9[2] = *(undefined4 *)(iVar6 + 0x2c);
    uVar5 = puVar9[1];
    *puVar12 = *puVar9;
    puVar12[1] = uVar5;
    puVar1 = puVar9 + 2;
    puVar9 = puVar9 + 3;
    puVar12[2] = *puVar1;
    puVar12 = puVar12 + 3;
    pfVar13[2] = (float)dVar15;
    pfVar13[1] = (float)dVar15;
    *pfVar13 = (float)dVar15;
    pfVar13 = pfVar13 + 3;
    pfVar8[2] = (float)dVar15;
    pfVar8[1] = (float)dVar15;
    *pfVar8 = (float)dVar15;
    pfVar8 = pfVar8 + 3;
    gnt4_PSMTXIdentity_bl(afStack_68);
    zz_020bcb0_((float *)(iVar4 + 0xed4),afStack_68);
    zz_020bcb0_((float *)(iVar4 + 0x10d4),afStack_68);
    iVar6 = iVar6 + 0x30;
    iVar4 = iVar4 + 0x10;
  }
  puVar7 = (undefined2 *)(param_1 + 0x18d4);
  iVar4 = 4;
  do {
    puVar7[2] = 0;
    puVar7[1] = 0;
    *puVar7 = 0;
    puVar7[5] = 0;
    puVar7[4] = 0;
    puVar7[3] = 0;
    puVar7[8] = 0;
    puVar7[7] = 0;
    puVar7[6] = 0;
    puVar7[0xb] = 0;
    puVar7[10] = 0;
    puVar7[9] = 0;
    puVar7[0xe] = 0;
    puVar7[0xd] = 0;
    puVar7[0xc] = 0;
    puVar7[0x11] = 0;
    puVar7[0x10] = 0;
    puVar7[0xf] = 0;
    puVar7[0x14] = 0;
    puVar7[0x13] = 0;
    puVar7[0x12] = 0;
    puVar7[0x17] = 0;
    puVar7[0x16] = 0;
    puVar7[0x15] = 0;
    fVar3 = FLOAT_804370f4;
    fVar2 = FLOAT_804370f0;
    puVar7 = puVar7 + 0x18;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar6 = 0;
  *(float *)(param_1 + 0x1dbc) = FLOAT_804370f4;
  *(float *)(param_1 + 0x1dc0) = fVar3;
  *(float *)(param_1 + 0x1dc4) = fVar3;
  *(float *)(param_1 + 0x1d54) = fVar3;
  *(float *)(param_1 + 0x1d58) = fVar3;
  *(float *)(param_1 + 0x1d5c) = fVar3;
  *(undefined4 *)(param_1 + 0x1d70) = 0xffffffff;
  *(undefined1 *)(param_1 + 0x579) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 2);
  *(undefined2 *)(param_1 + 0x1d64) = 0;
  *(undefined2 *)(param_1 + 0x1d66) = 0;
  *(undefined2 *)(param_1 + 0x1d68) = 0;
  *(float *)(param_1 + 0x1dc8) = fVar2;
  *(float *)(param_1 + 0x1dcc) = fVar2;
  *(float *)(param_1 + 0x1d9c) = fVar3;
  *(undefined1 *)(param_1 + 0x1d9b) = 0;
  *(undefined1 *)(param_1 + 0x1db2) = 0;
  *(float *)(param_1 + 0x1d60) = fVar3;
  *(float *)(param_1 + 0x6d8) = fVar2;
  *(float *)(param_1 + 0x6d4) = fVar3;
  *(float *)(param_1 + 0x6d0) = fVar3;
  *(undefined4 *)(param_1 + 0x6dc) = *(undefined4 *)(param_1 + 0x24);
  iVar4 = param_1;
  do {
    iVar10 = 0;
    iVar11 = param_1;
    iVar14 = iVar4;
    do {
      gnt4_memset((void *)(iVar14 + 0x1ad4),0,0x40);
      *(char *)(iVar14 + 0x1b07) = (char)iVar6;
      *(char *)(iVar14 + 0x1b08) = (char)iVar10;
      *(undefined1 *)(iVar14 + 0x1b0b) = 0xff;
      gnt4_memset((void *)(iVar11 + 0x1cd4),0,0x20);
      iVar10 = iVar10 + 1;
      iVar11 = iVar11 + 0x20;
      iVar14 = iVar14 + 0x40;
    } while (iVar10 < 4);
    iVar6 = iVar6 + 1;
    iVar4 = iVar4 + 0x100;
  } while (iVar6 < 2);
  *(undefined1 *)(param_1 + 0x1d91) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0xc);
  *(undefined1 *)(param_1 + 0x1d92) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0xd);
  *(undefined1 *)(param_1 + 0x1d93) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0xe);
  *(float *)(param_1 + 0x1dd4) =
       *(float *)(*(int *)(param_1 + 0x4b0) + 0x68) / *(float *)(*(int *)(param_1 + 0x4b0) + 0x58);
  *(float *)(param_1 + 0x1dd8) =
       *(float *)(*(int *)(param_1 + 0x4b0) + 0x68) / *(float *)(*(int *)(param_1 + 0x4b0) + 0x5c);
  *(float *)(param_1 + 0x1ddc) =
       *(float *)(*(int *)(param_1 + 0x4b0) + 0x68) / *(float *)(*(int *)(param_1 + 0x4b0) + 0x60);
  *(float *)(param_1 + 0x1de0) =
       *(float *)(*(int *)(param_1 + 0x4b0) + 0x68) / *(float *)(*(int *)(param_1 + 0x4b0) + 100);
  return;
}



// ==== 8004be08  zz_004be08_ ====

void zz_004be08_(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  iVar3 = 8;
  piVar1 = param_1;
  do {
    if (*piVar1 != 0) {
      *piVar1 = *piVar1 + (int)param_1;
      for (piVar2 = (int *)*piVar1; *piVar2 != -1; piVar2 = piVar2 + 1) {
        if (*piVar2 != 0) {
          *piVar2 = (int)param_1 + *piVar2 + 1;
        }
      }
    }
    if (piVar1[1] != 0) {
      piVar1[1] = piVar1[1] + (int)param_1;
      for (piVar2 = (int *)piVar1[1]; *piVar2 != -1; piVar2 = piVar2 + 1) {
        if (*piVar2 != 0) {
          *piVar2 = (int)param_1 + *piVar2 + 1;
        }
      }
    }
    piVar1 = piVar1 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 8004beb8  zz_004beb8_ ====

void zz_004beb8_(undefined8 param_1,int param_2,uint param_3,uint param_4,int param_5,
                undefined4 param_6,undefined4 param_7)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  
  uVar5 = param_3 & (int)*(char *)(param_2 + 0x579);
  if ((uVar5 & 2) != 0) {
    *(undefined1 *)(param_2 + 0x709) = 0;
  }
  if ((param_4 & 0x80) == 0) {
    iVar2 = *(int *)(param_2 + 0x1d80);
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)(param_2 + 0x1cd4);
      iVar2 = 0;
      do {
        zz_004c020_(puVar3);
        iVar2 = iVar2 + 1;
        *(undefined1 *)((int)puVar3 + 0x1a) = 1;
        puVar3 = puVar3 + 8;
      } while (iVar2 < 4);
      return;
    }
    if (param_4 == 0) {
      param_4 = (uint)*(char *)(param_2 + 0x582);
    }
    iVar2 = iVar2 + *(short *)(iVar2 + param_4 * 2);
  }
  else {
    iVar2 = *(int *)(param_2 + 0x1d84);
    if (iVar2 == 0) {
      puVar3 = (undefined4 *)(param_2 + 0x1cd4);
      iVar2 = 0;
      do {
        zz_004c020_(puVar3);
        iVar2 = iVar2 + 1;
        *(undefined1 *)((int)puVar3 + 0x1a) = 1;
        puVar3 = puVar3 + 8;
      } while (iVar2 < 4);
      return;
    }
    iVar2 = iVar2 + *(short *)(iVar2 + (param_4 & 0x7f) * 2);
  }
  puVar3 = (undefined4 *)(param_2 + 0x1cd4);
  sVar1 = *(short *)(iVar2 + param_5 * 2);
  iVar4 = 0;
  do {
    if ((uVar5 & 1 << iVar4) != 0) {
      *(char *)(puVar3 + 6) = (char)param_4;
      *(char *)((int)puVar3 + 0x19) = (char)param_5;
      zz_004c020_(puVar3);
    }
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 8;
  } while (iVar4 < 4);
  zz_004c050_(param_1,param_2,uVar5,(byte *)(iVar2 + sVar1),param_6,param_7);
  return;
}



// ==== 8004c020  zz_004c020_ ====

void zz_004c020_(undefined4 *param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804370f4;
  param_1[3] = FLOAT_804370f4;
  param_1[4] = fVar1;
  param_1[2] = fVar1;
  *(undefined1 *)((int)param_1 + 0x1d) = 0;
  *(undefined1 *)((int)param_1 + 0x1e) = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[5] = fVar1;
  *(undefined1 *)((int)param_1 + 0x1a) = 0;
  return;
}



// ==== 8004c050  zz_004c050_ ====

/* WARNING: Removing unreachable block (ram,0x8004c27c) */
/* WARNING: Removing unreachable block (ram,0x8004c060) */

void zz_004c050_(undefined8 param_1,int param_2,uint param_3,byte *param_4,undefined4 param_5,
                undefined4 param_6)

{
  byte bVar1;
  bool bVar2;
  double dVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  byte *local_48 [2];
  undefined4 local_40;
  uint uStack_3c;
  
  bVar2 = true;
  bVar1 = *param_4;
  local_48[0] = param_4;
  while (bVar1 != 0) {
    (*(code *)(&PTR_FUN_802d0da0)[bVar1])(param_1,param_2,param_3,local_48,param_5,param_6);
    if (bVar1 == 1) {
      bVar2 = false;
    }
    bVar1 = *local_48[0];
  }
  if (bVar2) {
    iVar5 = param_2 + 0x1cd4;
    iVar6 = 0;
    iVar7 = param_2;
    do {
      if ((param_3 & 1 << iVar6) != 0) {
        *(undefined4 *)(iVar5 + 0xc) = *(undefined4 *)(iVar5 + 8);
        zz_0049e58_(param_2,iVar6);
        if (*(char *)(iVar7 + 0x1b01) != '\0') {
          local_40 = 0x43300000;
          uStack_3c = (int)*(short *)(iVar7 + 0x1af8) ^ 0x80000000;
          *(float *)(iVar5 + 0x10) =
               *(float *)(iVar5 + 0x10) +
               (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_804370f8);
        }
        *(float *)(iVar5 + 8) = *(float *)(iVar5 + 0x10) + *(float *)(iVar7 + 0x1ae0);
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x20;
      iVar7 = iVar7 + 0x40;
    } while (iVar6 < 4);
  }
  dVar3 = DOUBLE_804370f8;
  pbVar4 = local_48[0] + 4;
  if ((param_3 & 1) != 0) {
    *(byte **)(param_2 + 0x1cd4) = local_48[0];
    *(byte **)(param_2 + 0x1cd8) = pbVar4;
    *(float *)(param_2 + 0x1ce8) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(local_48[0] + 2) ^ 0x80000000) - dVar3)
    ;
    *(undefined1 *)(param_2 + 0x1cee) = 0;
  }
  if ((param_3 & 2) != 0) {
    *(byte **)(param_2 + 0x1cf4) = local_48[0];
    *(byte **)(param_2 + 0x1cf8) = pbVar4;
    *(float *)(param_2 + 0x1d08) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(local_48[0] + 2) ^ 0x80000000) - dVar3)
    ;
    *(undefined1 *)(param_2 + 0x1d0e) = 0;
  }
  if ((param_3 & 4) != 0) {
    *(byte **)(param_2 + 0x1d14) = local_48[0];
    *(byte **)(param_2 + 0x1d18) = pbVar4;
    *(float *)(param_2 + 0x1d28) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(local_48[0] + 2) ^ 0x80000000) - dVar3)
    ;
    *(undefined1 *)(param_2 + 0x1d2e) = 0;
  }
  if ((param_3 & 8) != 0) {
    *(byte **)(param_2 + 0x1d34) = local_48[0];
    *(byte **)(param_2 + 0x1d38) = pbVar4;
    *(float *)(param_2 + 0x1d48) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(local_48[0] + 2) ^ 0x80000000) - dVar3)
    ;
    *(undefined1 *)(param_2 + 0x1d4e) = 0;
  }
  return;
}



// ==== 8004c298  FUN_8004c298 ====

/* WARNING: Removing unreachable block (ram,0x8004c408) */
/* WARNING: Removing unreachable block (ram,0x8004c3f0) */
/* WARNING: Removing unreachable block (ram,0x8004c2a8) */

void FUN_8004c298(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,uint param_10,
                 int *param_11,uint param_12,uint param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  iVar4 = *param_11;
  dVar5 = (double)FLOAT_804370f4;
  *param_11 = iVar4 + 8;
  if (param_1 < dVar5) {
    param_1 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar4 + 6) ^ 0x80000000) -
                             DOUBLE_804370f8);
  }
  if ((int)param_13 < 0) {
    param_13 = (uint)*(byte *)(iVar4 + 3);
  }
  if ((int)param_12 < 0) {
    param_12 = (uint)*(byte *)(iVar4 + 4);
  }
  iVar1 = param_9 + 0x1cd4;
  iVar2 = 0;
  iVar3 = param_9;
  do {
    if ((param_10 & 1 << iVar2) != 0) {
      *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(iVar1 + 8);
      if (*(char *)(iVar1 + 0x1d) != '\0') {
        param_2 = (double)*(float *)(iVar1 + 0x10);
        *(float *)(iVar1 + 0x10) =
             (float)(param_2 +
                    (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(iVar3 + 0x1af8) ^ 0x80000000) -
                                   DOUBLE_804370f8));
      }
      if (param_1 < (double)FLOAT_804370f4) {
        param_1 = (double)(*(float *)(iVar3 + 0x1ae0) + *(float *)(param_9 + 0x1dc8));
      }
      zz_0048648_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  (uint)*(byte *)(iVar4 + 1),(uint)*(byte *)(iVar4 + 2),param_12,param_13,param_15,
                  param_16);
      *(undefined1 *)(iVar1 + 0x1d) = 1;
      *(float *)(iVar1 + 8) = *(float *)(iVar1 + 0x10) + *(float *)(iVar3 + 0x1ae0);
    }
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + 0x20;
    iVar3 = iVar3 + 0x40;
  } while (iVar2 < 4);
  if ((param_10 & 2) != 0) {
    *(undefined1 *)(param_9 + 0x71d) = 0;
  }
  if (*(char *)(iVar4 + 5) != '\0') {
    *(float *)(param_9 + 0x1dcc) =
         FLOAT_8043712c *
         (float)((double)((longlong)(double)*(char *)(iVar4 + 5) * 0x3ff0000000000000) -
                (double)FLOAT_804370f0);
  }
  return;
}



// ==== 8004c5fc  FUN_8004c5fc ====

void FUN_8004c5fc(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  *param_3 = iVar1 + 4;
  if ((param_2 & 2) != 0) {
    if (*(char *)(iVar1 + 3) < '\0') {
      *(undefined1 *)(param_1 + 0x71d) = 0;
      *(float *)(param_1 + 0x6d8) =
           FLOAT_80437130 *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(iVar1 + 3) ^ 0x80000000) -
                  DOUBLE_804370f8);
    }
    else {
      *(char *)(param_1 + 0x71d) = *(char *)(iVar1 + 3);
    }
    zz_004d08c_(param_1);
  }
  return;
}



// ==== 8004c67c  FUN_8004c67c ====

void FUN_8004c67c(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  *param_3 = iVar1 + 4;
  if ((param_2 & 1) != 0) {
    zz_0099e70_(param_1,(char)*(undefined2 *)(iVar1 + 2));
  }
  return;
}



// ==== 8004c6b4  FUN_8004c6b4 ====

void FUN_8004c6b4(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  *param_3 = iVar1 + 4;
  if ((param_2 & 1) != 0) {
    if ('\0' < *(char *)(iVar1 + 1)) {
      zz_008ac80_(param_1,(int)*(char *)(iVar1 + 1));
      *(undefined1 *)(param_1 + 0x744) = *(undefined1 *)(iVar1 + 1);
    }
    if ((('\0' < *(char *)(iVar1 + 2)) && (*(char *)(param_1 + 0x43d) < '\x03')) &&
       (*(char *)(param_1 + 0x6f8) != *(char *)(iVar1 + 2))) {
      *(undefined1 *)(param_1 + 0x43d) = 0x81;
      *(undefined1 *)(param_1 + 0x6f8) = *(undefined1 *)(iVar1 + 2);
      *(undefined1 *)(param_1 + 0x6f9) = *(undefined1 *)(iVar1 + 3);
    }
  }
  return;
}



// ==== 8004c7fc  FUN_8004c7fc ====

/* WARNING: Removing unreachable block (ram,0x8004c960) */
/* WARNING: Removing unreachable block (ram,0x8004c80c) */

void FUN_8004c7fc(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,uint param_10,
                 int *param_11,uint param_12)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  
  iVar5 = *param_11;
  dVar7 = (double)FLOAT_804370f4;
  *param_11 = iVar5 + 8;
  puVar2 = (undefined1 *)(param_9 + 0x1de4);
  if (param_1 < dVar7) {
    param_1 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar5 + 6) ^ 0x80000000) -
                             DOUBLE_804370f8);
  }
  if ((int)param_12 < 0) {
    param_12 = (uint)*(byte *)(iVar5 + 5);
  }
  iVar3 = param_9 + 0x1cd4;
  iVar4 = 0;
  iVar6 = param_9;
  do {
    if ((param_10 & 1 << iVar4) != 0) {
      uVar1 = *(undefined1 *)(iVar5 + 1);
      puVar2[2] = uVar1;
      puVar2[1] = uVar1;
      *puVar2 = uVar1;
      puVar2[3] = *(undefined1 *)(iVar5 + 2);
      puVar2[4] = *(undefined1 *)(iVar5 + 3);
      puVar2[5] = *(undefined1 *)(iVar5 + 4);
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar3 + 8);
      if (*(char *)(iVar3 + 0x1d) != '\0') {
        param_2 = (double)*(float *)(iVar3 + 0x10);
        *(float *)(iVar3 + 0x10) =
             (float)(param_2 +
                    (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(iVar6 + 0x1af8) ^ 0x80000000) -
                                   DOUBLE_804370f8));
      }
      if (param_1 < (double)FLOAT_804370f4) {
        param_1 = (double)(*(float *)(iVar6 + 0x1ae0) + *(float *)(param_9 + 0x1dc8));
      }
      FUN_80048f9c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar4,
                   param_12);
      *(undefined1 *)(iVar3 + 0x1d) = 1;
      *(float *)(iVar3 + 8) = *(float *)(iVar3 + 0x10) + *(float *)(iVar6 + 0x1ae0);
    }
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + 0x40;
    iVar3 = iVar3 + 0x20;
    puVar2 = puVar2 + 6;
  } while (iVar4 < 4);
  if ((param_10 & 2) != 0) {
    *(undefined1 *)(param_9 + 0x71d) = 0;
  }
  return;
}



// ==== 8004c97c  FUN_8004c97c ====

/* WARNING: Removing unreachable block (ram,0x8004c9c0) */

void FUN_8004c97c(int param_1,uint param_2,int *param_3)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *param_3;
  *param_3 = iVar3 + 4;
  if ((param_2 & 1 << (uint)*(byte *)(iVar3 + 1)) != 0) {
    bVar1 = *(byte *)(iVar3 + 2);
    if (bVar1 == 1) {
      if (FLOAT_80437134 <= *(float *)(param_1 + 0xb4)) {
        if (*(float *)(param_1 + 0xb4) <= FLOAT_80437138) {
          uVar2 = (uint)*(byte *)(iVar3 + 3);
        }
        else {
          uVar2 = *(byte *)(iVar3 + 3) + 1;
        }
      }
      else {
        uVar2 = *(byte *)(iVar3 + 3) - 1;
      }
      zz_00f036c_(param_1,uVar2);
    }
    else if (bVar1 == 0) {
      zz_00f036c_(param_1,(uint)*(byte *)(iVar3 + 3));
    }
    else if ((bVar1 != 4) && (bVar1 < 4)) {
      zz_00f061c_((double)FLOAT_8043713c,param_1,(uint)*(byte *)(iVar3 + 3));
    }
  }
  return;
}



// ==== 8004ca3c  FUN_8004ca3c ====

void FUN_8004ca3c(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  *param_3 = iVar1 + 4;
  if (((param_2 & 1 << (uint)*(byte *)(iVar1 + 1)) != 0) && (*(char *)(iVar1 + 2) == '\0')) {
    zz_00b2190_(param_1,2);
    zz_00f07e8_(param_1);
  }
  return;
}



// ==== 8004caa4  FUN_8004caa4 ====

/* WARNING: Removing unreachable block (ram,0x8004cad0) */

void FUN_8004caa4(int param_1,uint param_2,int *param_3)

{
  byte bVar1;
  ushort uVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = *param_3;
  *param_3 = iVar5 + 4;
  dVar3 = DOUBLE_80437140;
  bVar1 = *(byte *)(iVar5 + 2);
  if (bVar1 == 2) {
    iVar4 = 0;
    iVar6 = 2;
    do {
      if ((param_2 & 1 << iVar4) != 0) {
        bVar1 = *(byte *)(iVar5 + 3);
        if (bVar1 == 2) {
          *(undefined1 *)(param_1 + 0x1b04) = 1;
        }
        else if (bVar1 < 2) {
          if (bVar1 != 0) {
            *(undefined1 *)(param_1 + 0x1b04) = 0;
          }
        }
        else if (bVar1 < 4) {
          *(byte *)(param_1 + 0x1b04) = *(byte *)(param_1 + 0x1b04) ^ 1;
        }
      }
      if ((param_2 & 1 << iVar4 + 1) != 0) {
        bVar1 = *(byte *)(iVar5 + 3);
        if (bVar1 == 2) {
          *(undefined1 *)(param_1 + 0x1b44) = 1;
        }
        else if (bVar1 < 2) {
          if (bVar1 != 0) {
            *(undefined1 *)(param_1 + 0x1b44) = 0;
          }
        }
        else if (bVar1 < 4) {
          *(byte *)(param_1 + 0x1b44) = *(byte *)(param_1 + 0x1b44) ^ 1;
        }
      }
      param_1 = param_1 + 0x80;
      iVar4 = iVar4 + 2;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      if ((param_2 & 1 << (uint)*(byte *)(iVar5 + 1)) != 0) {
        *(undefined1 *)(param_1 + 0x73f) = 0;
      }
    }
    else {
      if ((param_2 & 1) != 0) {
        *(float *)(param_1 + 0x1ce4) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar5 + 3)) - DOUBLE_80437140);
      }
      if ((param_2 & 2) != 0) {
        *(float *)(param_1 + 0x1d04) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar5 + 3)) - dVar3);
      }
      if ((param_2 & 4) != 0) {
        *(float *)(param_1 + 0x1d24) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar5 + 3)) - dVar3);
      }
      if ((param_2 & 8) != 0) {
        *(float *)(param_1 + 0x1d44) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar5 + 3)) - dVar3);
      }
    }
  }
  else if ((bVar1 < 4) && ((param_2 & 2) != 0)) {
    uVar2 = (ushort)*(byte *)(iVar5 + 3);
    *(ushort *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + uVar2 * 0x100;
    *(ushort *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + uVar2 * 0x100;
    *(ushort *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + uVar2 * -0x100;
    *(ushort *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x5ac) + uVar2 * -0x100;
  }
  return;
}



// ==== 8004cccc  FUN_8004cccc ====

void FUN_8004cccc(int param_1,uint param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  *param_3 = iVar1 + 4;
  if (((param_2 & 1 << (uint)*(byte *)(iVar1 + 1)) != 0) &&
     (*(code **)(param_1 + 0x4d8) != (code *)0x0)) {
    (**(code **)(param_1 + 0x4d8))(param_1,*(undefined1 *)(iVar1 + 2),*(undefined1 *)(iVar1 + 3));
  }
  return;
}



// ==== 8004cd24  zz_004cd24_ ====

/* WARNING: Removing unreachable block (ram,0x8004ce34) */
/* WARNING: Removing unreachable block (ram,0x8004ce68) */

undefined4 zz_004cd24_(int param_1,uint param_2)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  
  uVar9 = 0;
  piVar8 = (int *)(param_1 + 0x1cd4);
  iVar7 = param_1 + 0x1ad4;
  cVar1 = *(char *)(param_1 + 0x579);
  if (*(int *)(param_1 + 0x1cd4) == 0) {
    uVar9 = 1;
    *(undefined1 *)(param_1 + 0x1cee) = 1;
    *(undefined1 *)(param_1 + 0x1d0e) = 1;
    *(undefined1 *)(param_1 + 0x1d2e) = 1;
    *(undefined1 *)(param_1 + 0x1d4e) = 1;
  }
  else {
    iVar10 = 0;
    iVar11 = param_1;
    do {
      uVar5 = 1 << iVar10;
      if ((param_2 & (int)cVar1 & uVar5) != 0) {
        uVar6 = 0;
        *(undefined1 *)((int)piVar8 + 0x1e) = 0;
        fVar4 = FLOAT_804370f4;
        if (((int)*(char *)(param_1 + 0x1d9a) & uVar5) == 0) {
          if (*(char *)((int)piVar8 + 0x1a) == '\0') {
            bVar3 = true;
            bVar2 = *(byte *)(*piVar8 + 1);
            if ((bVar2 & 8) == 0) {
              if ((bVar2 & 2) == 0) {
                if ((bVar2 & 4) == 0) {
                  if (FLOAT_804370f4 <= (float)piVar8[5]) {
                    uVar6 = (uint)((float)piVar8[5] <= *(float *)(iVar7 + 8));
                  }
                  else if ((bVar2 & 1) == 0) {
                    uVar6 = (uint)(-(int)*(char *)(iVar7 + 0x2e) & ~(int)*(char *)(iVar7 + 0x2e)) >>
                            0x1f;
                  }
                  else if (('\0' < *(char *)(iVar7 + 0x2e)) || ('\0' < *(char *)(iVar7 + 0x2d))) {
                    uVar6 = 1;
                  }
                }
                else {
                  uVar6 = (uint)((float)piVar8[5] <=
                                FLOAT_80437148 *
                                (float)((double)*(float *)(iVar7 + 0xc) /
                                       (double)((longlong)(double)*(short *)(iVar7 + 0x24) *
                                               0x3ff0000000000000)));
                }
              }
              else {
                dVar13 = (double)(float)piVar8[5];
                dVar12 = (double)FLOAT_804370f4;
                if ((dVar13 < dVar12) &&
                   (dVar13 = (double)(float)((double)((longlong)(double)*(short *)(iVar7 + 0x24) *
                                                     0x3ff0000000000000) + dVar13), dVar13 < dVar12)
                   ) {
                  dVar13 = dVar12;
                }
                uVar6 = (uint)(dVar13 <= (double)*(float *)(iVar7 + 0xc));
              }
            }
            else {
              bVar3 = false;
              piVar8[5] = (int)((float)piVar8[5] - *(float *)(param_1 + 0x1dc8));
              if (fVar4 < (float)piVar8[5]) {
                uVar6 = 0;
              }
              else {
                piVar8[5] = (int)fVar4;
                uVar6 = 1;
              }
            }
            if (uVar6 == 0) {
              if (bVar3) {
                piVar8[3] = piVar8[2];
                zz_0049e58_(param_1,iVar10);
                if (*(char *)(iVar11 + 0x1b01) != '\0') {
                  piVar8[4] = (int)((float)piVar8[4] +
                                   (float)((double)CONCAT44(0x43300000,
                                                            (int)*(short *)(iVar11 + 0x1af8) ^
                                                            0x80000000) - DOUBLE_804370f8));
                }
                piVar8[2] = (int)((float)piVar8[4] + *(float *)(iVar11 + 0x1ae0));
              }
            }
            else if ((*(byte *)(*piVar8 + 1) & 1) == 0) {
              zz_004c050_((double)FLOAT_80437128,param_1,uVar5,(byte *)piVar8[1],0xffffffff,
                          0xffffffff);
            }
            else {
              uVar9 = 1;
              *(undefined1 *)((int)piVar8 + 0x1a) = 1;
            }
          }
          else {
            uVar9 = 1;
            if (*(char *)(iVar11 + 0x1b0a) == '\x01') {
              zz_0049e58_(param_1,iVar10);
            }
          }
        }
        else {
          zz_0049e58_(param_1,iVar10);
        }
      }
      iVar10 = iVar10 + 1;
      piVar8 = piVar8 + 8;
      iVar7 = iVar7 + 0x40;
      iVar11 = iVar11 + 0x40;
    } while (iVar10 < 4);
  }
  return uVar9;
}



// ==== 8004cff4  zz_004cff4_ ====

void zz_004cff4_(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = param_1 + 0x1cd4;
  uVar1 = param_2 & (int)*(char *)(param_1 + 0x579);
  do {
    if ((uVar1 & 1 << iVar3) != 0) {
      if (((int)*(char *)(param_1 + 0x1d9a) & 1 << uVar1) == 0) {
        zz_004c050_((double)FLOAT_80437128,param_1,1 << iVar3,*(byte **)(iVar2 + 4),0xffffffff,
                    0xffffffff);
      }
      else {
        zz_0049e58_(param_1,iVar3);
      }
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x20;
  } while (iVar3 < 4);
  return;
}



// ==== 8004d08c  zz_004d08c_ ====

void zz_004d08c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  
  fVar1 = FLOAT_80437104;
  if (((*(char *)(param_1 + 1000) == '\x05') || (*(char *)(param_1 + 0x661) != '\0')) ||
     ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) {
    *(float *)(param_1 + 0x6d0) = FLOAT_804370f4;
    return;
  }
  if (*(char *)(param_1 + 0x71d) != '\0') {
    *(float *)(param_1 + 0x6d0) =
         FLOAT_8043714c *
         (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x71d) - 1U ^ 0x80000000) -
                DOUBLE_804370f8) * *(float *)(param_1 + 0xb4);
    return;
  }
  pcVar4 = (char *)(*(int *)(param_1 + 0x4b0) + 0x22);
  *(undefined4 *)(param_1 + 0x6d0) = *(undefined4 *)(param_1 + 0x920);
  *(float *)(param_1 + 0x6d0) = -(*(float *)(param_1 + 0x66c) * fVar1 - *(float *)(param_1 + 0x6d0))
  ;
  fVar1 = (*(float *)(param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0xf) * 0x30 + 0x8f0) -
          *(float *)(param_1 + 0x24)) * fVar1 + *(float *)(param_1 + 0x24);
  if (fVar1 < *(float *)(param_1 + 0x6d0)) {
    *(float *)(param_1 + 0x6d0) = fVar1;
  }
  iVar3 = 0;
  for (; (fVar2 = FLOAT_80437134, fVar1 = FLOAT_804370f4, iVar3 < 4 && (*pcVar4 != -1));
      pcVar4 = pcVar4 + 8) {
    fVar1 = *(float *)(param_1 + *pcVar4 * 0x30 + 0x8f0) - *(float *)(param_1 + 0x670);
    if (fVar1 < *(float *)(param_1 + 0x6d0)) {
      *(float *)(param_1 + 0x6d0) = fVar1;
    }
    iVar3 = iVar3 + 1;
  }
  *(float *)(param_1 + 0x6d0) = *(float *)(param_1 + 0x6d0) - *(float *)(param_1 + 0x24);
  *(float *)(param_1 + 0x6d0) = *(float *)(param_1 + 0x6d0) * fVar2 * *(float *)(param_1 + 0x6d8);
  if (fVar1 <= *(float *)(param_1 + 0x6d0)) {
    return;
  }
  *(float *)(param_1 + 0x6d0) = fVar1;
  return;
}



// ==== 8004d1f4  zz_004d1f4_ ====

int zz_004d1f4_(int param_1,uint param_2,int param_3)

{
  int iVar1;
  
  if ((param_2 & 0x80) == 0) {
    if (param_2 == 0) {
      param_2 = (uint)*(char *)(param_1 + 0x582);
    }
    iVar1 = *(int *)(param_1 + 0x1d88) + (int)*(short *)(*(int *)(param_1 + 0x1d88) + param_2 * 2);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x1d8c) +
            (int)*(short *)(*(int *)(param_1 + 0x1d8c) + (param_2 & 0x7f) * 2);
  }
  return iVar1 + *(short *)(iVar1 + param_3 * 2);
}



// ==== 8004d244  zz_004d244_ ====

void zz_004d244_(int param_1,int param_2,int param_3,undefined1 *param_4)

{
  byte bVar1;
  
  *(undefined1 *)(param_3 + 0x32) = *param_4;
  if (param_2 == 2) {
    *(undefined1 *)(param_3 + 0x2a) = param_4[0x14];
    *(undefined1 *)(param_3 + 0x2b) = param_4[0x15];
    *(ushort *)(param_3 + 0x26) = (ushort)(byte)param_4[0x17];
    *(undefined1 *)(param_3 + 0x37) = param_4[0x18];
    bVar1 = param_4[0x16];
    if ((bVar1 & 3) == 3) {
      *(byte *)(param_3 + 0x30) = *(byte *)(param_3 + 0x30) ^ 1;
    }
    else if ((bVar1 & 1) == 0) {
      if ((bVar1 & 2) != 0) {
        *(undefined1 *)(param_3 + 0x30) = 1;
      }
    }
    else {
      *(undefined1 *)(param_3 + 0x30) = 0;
    }
    if ((param_4[0x16] & 4) != 0) {
      *(undefined1 *)(param_3 + 0x2c) = 1;
      return;
    }
    *(undefined1 *)(param_3 + 0x2c) = 0;
    return;
  }
  if (param_2 < 2) {
    if (param_2 != 0) {
      if (param_2 < 0) {
        return;
      }
      *(undefined1 *)(param_3 + 0x2a) = param_4[0xc];
      *(undefined1 *)(param_3 + 0x2b) = param_4[0xd];
      *(ushort *)(param_3 + 0x26) = (ushort)(byte)param_4[0xf];
      *(undefined1 *)(param_3 + 0x37) = param_4[0x10];
      bVar1 = param_4[0xe];
      if ((bVar1 & 3) == 3) {
        *(byte *)(param_3 + 0x30) = *(byte *)(param_3 + 0x30) ^ 1;
      }
      else if ((bVar1 & 1) == 0) {
        if ((bVar1 & 2) != 0) {
          *(undefined1 *)(param_3 + 0x30) = 1;
        }
      }
      else {
        *(undefined1 *)(param_3 + 0x30) = 0;
      }
      if ((param_4[0xe] & 4) == 0) {
        *(undefined1 *)(param_3 + 0x2c) = 0;
      }
      else {
        *(undefined1 *)(param_3 + 0x2c) = 1;
      }
      *(undefined1 *)(param_1 + 0x1d98) = param_4[0x11];
      *(undefined1 *)(param_1 + 0x1d99) = param_4[0x12];
      *(undefined1 *)(param_1 + 0x1d9b) = param_4[0x13];
      return;
    }
    *(undefined1 *)(param_3 + 0x2a) = param_4[4];
    *(undefined1 *)(param_3 + 0x2b) = param_4[5];
    *(ushort *)(param_3 + 0x26) = (ushort)(byte)param_4[7];
    *(undefined1 *)(param_3 + 0x37) = param_4[8];
    bVar1 = param_4[6];
    if ((bVar1 & 3) == 3) {
      *(byte *)(param_3 + 0x30) = *(byte *)(param_3 + 0x30) ^ 1;
    }
    else if ((bVar1 & 1) == 0) {
      if ((bVar1 & 2) != 0) {
        *(undefined1 *)(param_3 + 0x30) = 1;
      }
    }
    else {
      *(undefined1 *)(param_3 + 0x30) = 0;
    }
    if ((param_4[6] & 4) == 0) {
      *(undefined1 *)(param_3 + 0x2c) = 0;
    }
    else {
      *(undefined1 *)(param_3 + 0x2c) = 1;
    }
    if ((char)param_4[9] < '\0') {
      *(undefined1 *)(param_1 + *(char *)(param_3 + 0x33) * 2 + 0x1d74) =
           *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0xbe);
    }
    else {
      *(undefined1 *)(param_1 + *(char *)(param_3 + 0x33) * 2 + 0x1d74) = param_4[9];
    }
    if ((char)param_4[10] < '\0') {
      *(undefined1 *)(param_1 + *(char *)(param_3 + 0x33) * 2 + 0x1d75) =
           *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0xbf);
    }
    else {
      *(undefined1 *)(param_1 + *(char *)(param_3 + 0x33) * 2 + 0x1d75) = param_4[10];
    }
    if (*(char *)(param_3 + 0x33) != '\0') {
      return;
    }
    *(undefined1 *)(param_1 + 0x1d94) = *(undefined1 *)(param_1 + 0x1d74);
    *(undefined1 *)(param_1 + 0x1d95) = *(undefined1 *)(param_1 + 0x1d75);
    return;
  }
  if (3 < param_2) {
    return;
  }
  *(undefined1 *)(param_3 + 0x2a) = param_4[0x1c];
  *(undefined1 *)(param_3 + 0x2b) = param_4[0x1d];
  *(ushort *)(param_3 + 0x26) = (ushort)(byte)param_4[0x1f];
  *(undefined1 *)(param_3 + 0x37) = param_4[0x20];
  bVar1 = param_4[0x1e];
  if ((bVar1 & 3) == 3) {
    *(byte *)(param_3 + 0x30) = *(byte *)(param_3 + 0x30) ^ 1;
  }
  else if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) != 0) {
      *(undefined1 *)(param_3 + 0x30) = 1;
    }
  }
  else {
    *(undefined1 *)(param_3 + 0x30) = 0;
  }
  if ((param_4[0x1e] & 4) != 0) {
    *(undefined1 *)(param_3 + 0x2c) = 1;
    return;
  }
  *(undefined1 *)(param_3 + 0x2c) = 0;
  return;
}



// ==== 8004d548  zz_004d548_ ====

undefined4
zz_004d548_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
           undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  
  puVar1 = (undefined4 *)*param_9;
  if (puVar1 == (undefined4 *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
    if (puVar1[*(byte *)((int)param_9 + 0x2a) & 0x7f] == 0) {
      puVar1 = (undefined4 *)*puVar1;
      uVar2 = 1;
      param_9[1] = *puVar1;
    }
    else {
      puVar1 = (undefined4 *)
               (puVar1[*(byte *)((int)param_9 + 0x2a) & 0x7f] + *(char *)((int)param_9 + 0x2b) * 4);
      param_9[1] = *puVar1;
      if (param_9[1] == 0) {
        uVar2 = 1;
        puVar1 = *(undefined4 **)*param_9;
        param_9[1] = *puVar1;
      }
    }
    if ((param_9[1] & 1) != 0) {
      param_9[1] = param_9[1] & 0xfffffffe;
      piVar3 = zz_0197a0c_(2);
      gnt4_HSD_ArchiveParse_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(uint *)piVar3[3],
                 (uint *)param_9[1],*(uint *)param_9[1],param_12,param_13,param_14,param_15,param_16
                );
      *puVar1 = piVar3;
      param_9[1] = piVar3;
    }
  }
  return uVar2;
}



// ==== 8004d63c  zz_004d63c_ ====

void zz_004d63c_(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = *(int **)(&DAT_803c4d7c + param_1 * 4);
  if (piVar4 != (int *)0x0) {
    iVar3 = 0;
    do {
      piVar1 = (int *)*piVar4;
      if (piVar1 != (int *)0x0) {
        for (; *piVar1 != -1; piVar1 = piVar1 + 1) {
          piVar2 = (int *)*piVar1;
          if ((piVar2 != (int *)0x0) && (((uint)piVar2 & 1) == 0)) {
            zz_0197ad8_(piVar2);
          }
        }
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < 0x10);
  }
  return;
}



// ==== 8004d6dc  zz_004d6dc_ ====

void zz_004d6dc_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0) || (sVar1 == 3)) || (sVar1 == 10)) || (sVar1 == 0xc)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_8004d7fc;
    *(code **)(puVar2 + 0x10c) = FUN_8004dabc;
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



// ==== 8004d7fc  FUN_8004d7fc ====

void FUN_8004d7fc(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d0f88)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004d850  FUN_8004d850 ====

void FUN_8004d850(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  uint uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  
  uVar2 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x4b;
  fVar1 = FLOAT_80437150;
  *(float *)(param_9 + 0xb4) = FLOAT_80437150;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  uVar4 = (uint)*(short *)(&DAT_802d0de8 + *(char *)(param_9 + 0x11) * 2);
  if ((int)uVar4 < 0) {
    *(undefined1 *)(param_9 + 0x84) = 0x14;
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),uVar4 & 0x7fff,uVar2,in_r7,in_r8,in_r9,in_r10);
  }
  else {
    iVar5 = zz_0006f98_(iVar5);
    uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),uVar4,iVar5 + 0xc28,in_r7,
                        in_r8,in_r9,in_r10);
    iVar3 = iVar5 + 0xc28;
    uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),uVar4,iVar3,in_r7,in_r8,
                        in_r9,in_r10);
    zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4,uVar4,iVar3,in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80437154,*(int *)(param_9 + 0xe4));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_004d978_(param_9);
  return;
}



// ==== 8004d978  zz_004d978_ ====

void zz_004d978_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  *(byte *)(param_1 + 0x12) = *(byte *)(iVar3 + 0x6e8) & 0x7f;
  *(undefined *)(param_1 + 0x89) =
       (&DAT_804336b0)[*(char *)(param_1 + 0x12) * 2 + (*(byte *)(param_1 + 0x11) & 1)];
  puVar2 = (undefined4 *)
           (*(char *)(param_1 + 0x12) * 0x78 + -0x7fd2f204 + *(char *)(param_1 + 0x11) * 0xc);
  uVar1 = puVar2[1];
  *(undefined4 *)(param_1 + 100) = *puVar2;
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = puVar2[2];
  puVar2 = (undefined4 *)
           (*(char *)(param_1 + 0x12) * 0xc + -0x7fd2f09c + (*(byte *)(param_1 + 0x11) & 1) * 6);
  *(undefined4 *)(param_1 + 0x70) = *puVar2;
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(puVar2 + 1);
  if (*(char *)(param_1 + 0x11) == '\t') {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar3 + 0xae4),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(iVar3 + 0x72);
    uVar1 = *(undefined4 *)(iVar3 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined4 *)(param_1 + 0x58) = uVar1;
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
  }
  return;
}



// ==== 8004da9c  FUN_8004da9c ====

void FUN_8004da9c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004dabc  FUN_8004dabc ====

void FUN_8004dabc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_9 + 0x11);
  puVar2 = *(undefined **)(param_9 + 0x90);
  if (((bVar1 & 1) == 0) ||
     ((*(char *)(param_9 + 0x12) == '\x02' && (0 < *(short *)(puVar2 + 0x784))))) {
    if ((bVar1 != 4) && (bVar1 != 5)) {
      if ((puVar2[0xae] == '\0') && (puVar2[0x3ec] != '\x04')) {
        iVar3 = *(int *)(param_9 + 0xe0);
        uVar4 = 1;
      }
      else {
        iVar3 = *(int *)(param_9 + 0xe4);
        uVar4 = 0x44;
      }
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                  (float *)(param_9 + 0x114),puVar2,param_12,param_13,param_14,param_15,param_16);
      zz_00097b4_(iVar3,uVar4);
      return;
    }
    if (puVar2[0x7c8] != '\0') {
      if ((puVar2[0xae] == '\0') && (puVar2[0x7c8] != '\x02')) {
        iVar3 = *(int *)(param_9 + 0xe0);
        uVar4 = 1;
      }
      else {
        iVar3 = *(int *)(param_9 + 0xe4);
        uVar4 = 0x44;
      }
      dVar6 = (double)*(float *)(puVar2 + 0x7b4);
      dVar7 = (double)*(float *)(puVar2 + 0x7b8);
      uVar5 = zz_020b4ac_((double)*(float *)(puVar2 + 0x7b0),dVar6,dVar7,(float *)(param_9 + 0x114),
                          afStack_38);
      zz_00076d0_(uVar5,dVar6,dVar7,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_38,puVar2,
                  param_12,param_13,param_14,param_15,param_16);
      zz_00097b4_(iVar3,uVar4);
    }
  }
  return;
}



// ==== 8004dbd8  zz_004dbd8_ ====

void zz_004dbd8_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int *piVar2;
  int iVar3;
  
  if ((*(short *)(param_1 + 1000) == 0x100) || (*(short *)(param_1 + 1000) == 0x108)) {
    iVar3 = 0;
    do {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x83] = 0x18;
        *(code **)(puVar1 + 0xc) = FUN_8004dd28;
        *(code **)(puVar1 + 0x10c) = FUN_8004df94;
        puVar1[0x11] = (char)iVar3;
        puVar1[0x12] = param_2;
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
        piVar2 = zz_0006dc8_(0x90);
        *(int **)(puVar1 + 0xdc) = piVar2;
        if (piVar2 == (int *)0x0) {
          puVar1[0x18] = 2;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
  }
  return;
}



// ==== 8004dd28  FUN_8004dd28 ====

void FUN_8004dd28(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d0fe0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004dd7c  FUN_8004dd7c ====

void FUN_8004dd7c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80437158;
  *(undefined1 *)(param_9 + 0x84) = 0x49;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_804336bc)
                                 [*(char *)(param_9 + 0x12) * 2 + (int)*(char *)(param_9 + 0x11)],
                      iVar4 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = (int)(char)(&DAT_804336bc)[*(char *)(param_9 + 0x12) * 2 + (int)*(char *)(param_9 + 0x11)]
  ;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043715c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_004de98_(param_9);
  return;
}



// ==== 8004de98  zz_004de98_ ====

void zz_004de98_(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  
  cVar2 = *(char *)(*(int *)(param_1 + 0x90) + 0x6e8);
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x1b04) != '\0') {
    cVar2 = (&DAT_804336c0)[cVar2];
  }
  iVar4 = (int)(short)(ushort)(((int)cVar2 & 1 << (*(byte *)(param_1 + 0x11) & 1)) != 0);
  *(undefined *)(param_1 + 0x89) = (&DAT_804336b8)[iVar4 * 2 + (int)(char)*(byte *)(param_1 + 0x11)]
  ;
  puVar3 = (undefined4 *)(iVar4 * 0x18 + -0x7fd2f068 + *(char *)(param_1 + 0x11) * 0xc);
  uVar1 = puVar3[1];
  *(undefined4 *)(param_1 + 100) = *puVar3;
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = puVar3[2];
  puVar3 = (undefined4 *)(iVar4 * 0xc + -0x7fd2f038 + *(char *)(param_1 + 0x11) * 6);
  *(undefined4 *)(param_1 + 0x70) = *puVar3;
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(puVar3 + 1);
  return;
}



// ==== 8004df74  FUN_8004df74 ====

void FUN_8004df74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004df94  FUN_8004df94 ====

void FUN_8004df94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8004e00c  zz_004e00c_ ====

void zz_004e00c_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x200) || (sVar1 == 0x20a)) || (sVar1 == 0x20f)) || (sVar1 == 0x206)) &&
     (puVar2 = zz_0088aa0_(param_1,3,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_8004e12c;
    *(code **)(puVar2 + 0x10c) = FUN_8004e518;
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



// ==== 8004e12c  FUN_8004e12c ====

void FUN_8004e12c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d1080)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004e180  FUN_8004e180 ====

void FUN_8004e180(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  undefined8 uVar9;
  
  uVar7 = (uint)*(byte *)(param_9 + 0x11);
  iVar8 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar3 = (char)*(byte *)(param_9 + 0x11) * 0x24;
  *(code **)(param_9 + 0x100) = FUN_80047c38;
  uVar9 = zz_0089100_(param_9,(int)*(char *)(iVar8 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80437160;
  *(char *)(param_9 + 0x84) = (char)*(undefined2 *)(&DAT_802d1010 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined *)(param_9 + 0x89) = (&DAT_802d0ff2)[iVar3];
  uVar4 = *(undefined4 *)(&DAT_802d0ff8 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802d0ff4 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar4;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802d0ffc + iVar3);
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_802d100c + iVar3);
  iVar8 = zz_0006f98_(iVar8);
  iVar6 = iVar8 + 0xc28;
  puVar5 = (undefined *)(uint)*(ushort *)(&DAT_802d0ff0 + iVar3);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe0),(int)puVar5,iVar6,uVar7,in_r8
                      ,in_r9,in_r10);
  iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  if (iVar2 != 0) {
    uVar9 = gnt4_HSD_JObjSetFlagsAll
                      (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                       puVar5,iVar6,uVar7,in_r8,in_r9,in_r10);
  }
  iVar2 = iVar8 + 0xc28;
  puVar5 = (undefined *)(uint)*(ushort *)(&DAT_802d0ff0 + iVar3);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe4),(int)puVar5,iVar2,uVar7,in_r8
                      ,in_r9,in_r10);
  iVar8 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
  if (iVar8 == 0) {
    iVar8 = 0;
  }
  else {
    iVar8 = *(int *)(iVar8 + 0x10);
  }
  uVar4 = extraout_r4;
  if (iVar8 != 0) {
    uVar9 = gnt4_HSD_JObjSetFlagsAll
                      (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,0x10,
                       puVar5,iVar2,uVar7,in_r8,in_r9,in_r10);
    uVar4 = extraout_r4_00;
  }
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,uVar4,puVar5,iVar2,uVar7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437164,*(int *)(param_9 + 0xe4));
  iVar8 = zz_008ac80_(param_9,(int)(char)(&DAT_802d0ff3)[iVar3]);
  if (iVar8 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
    *(undefined2 *)(param_9 + 0x1c6) = 10000;
    *(undefined2 *)(param_9 + 0x1c8) = 10000;
    *(undefined2 *)(param_9 + 0x1c4) = 10000;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 2;
    zz_004e350_(param_9);
  }
  return;
}



// ==== 8004e350  zz_004e350_ ====

void zz_004e350_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x11) * 0x24;
  if (*(char *)(iVar3 + 0x144) == '\x01') {
    uVar1 = *(undefined4 *)(&DAT_802d1004 + iVar2);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802d1000 + iVar2);
    *(undefined4 *)(param_1 + 0x68) = uVar1;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802d1008 + iVar2);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802d100e + iVar2);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x46;
  }
  else if (*(char *)(iVar3 + 0x144) == '\x02') {
    uVar1 = *(undefined4 *)(&DAT_802d0ff8 + iVar2);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802d0ff4 + iVar2);
    *(undefined4 *)(param_1 + 0x68) = uVar1;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802d0ffc + iVar2);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802d100c + iVar2);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x46;
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_802d0ff8 + iVar2);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802d0ff4 + iVar2);
    *(undefined4 *)(param_1 + 0x68) = uVar1;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802d0ffc + iVar2);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802d100c + iVar2);
    if (((*(uint *)(iVar3 + 0x5e0) & 0x1000000) == 0) ||
       ((*(uint *)(iVar3 + 0x5e0) & 0x10000000) != 0)) {
      *(undefined2 *)(param_1 + 0x272) = *(undefined2 *)(iVar3 + 0x272);
    }
    else {
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
    }
  }
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar3 + 0xc0);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  if (*(char *)(param_1 + 0x11) == '\x03') {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar3 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),(float *)(param_1 + 100),
               (float *)(param_1 + 0x20));
    *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(iVar3 + 0x70);
    *(short *)(param_1 + 0x72) = *(short *)(iVar3 + 0x72) + -0x4000;
    *(short *)(param_1 + 0x74) = *(short *)(iVar3 + 0x74) + -0x4000;
    uVar1 = *(undefined4 *)(iVar3 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined4 *)(param_1 + 0x58) = uVar1;
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
  }
  return;
}



// ==== 8004e4cc  FUN_8004e4cc ====

void FUN_8004e4cc(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 8004e4f8  FUN_8004e4f8 ====

void FUN_8004e4f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004e518  FUN_8004e518 ====

void FUN_8004e518(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x144) != '\x02') {
    if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
      iVar1 = *(int *)(param_9 + 0xe0);
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,0x47);
  }
  return;
}



// ==== 8004e580  FUN_8004e580 ====

void FUN_8004e580(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x300) || (*(short *)(param_1 + 1000) == 0x30b)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,6), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_8004e690;
    *(code **)(puVar1 + 0x10c) = FUN_8004ea18;
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



// ==== 8004e690  FUN_8004e690 ====

void FUN_8004e690(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d10cc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004e6e4  FUN_8004e6e4 ====

void FUN_8004e6e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
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
  fVar1 = FLOAT_80437168;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_802d10b4 + *(char *)(param_9 + 0x11) * 0xc),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_802d10b4 + *(char *)(param_9 + 0x11) * 0xc);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_8043716c,*(int *)(param_9 + 0xe4));
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),
                      *(int *)(&DAT_802d10b8 + *(char *)(param_9 + 0x11) * 0xc),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_802d10b8 + *(char *)(param_9 + 0x11) * 0xc);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_8043716c,*(int *)(param_9 + 0xec));
  fVar1 = FLOAT_80437170;
  *(float *)(param_9 + 0x174) = FLOAT_80437170;
  *(float *)(param_9 + 0x178) = fVar1;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xf0),
                      *(int *)(&DAT_802d10bc + *(char *)(param_9 + 0x11) * 0xc),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_802d10bc + *(char *)(param_9 + 0x11) * 0xc);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xf4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xf4)
              ,extraout_r4_01,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043716c,*(int *)(param_9 + 0xf4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_004e8bc_(param_9);
  return;
}



// ==== 8004e8bc  zz_004e8bc_ ====

void zz_004e8bc_(int param_1)

{
  char cVar1;
  double dVar2;
  undefined4 uVar3;
  int iVar4;
  
  dVar2 = DOUBLE_80437178;
  iVar4 = *(int *)(param_1 + 0x90);
  cVar1 = *(char *)(iVar4 + 0x144);
  if ((cVar1 != '\x02') && (cVar1 != '\x03')) {
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x13) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x13) = 1;
    *(float *)(param_1 + 0x174) =
         (float)(dVar2 * (double)(float)((double)*(float *)(param_1 + 0x178) -
                                        (double)*(float *)(param_1 + 0x174)) +
                (double)*(float *)(param_1 + 0x174));
    if (*(char *)(iVar4 + 0x145) == '\x02') {
      *(undefined1 *)(iVar4 + 0x145) = 1;
      *(float *)(param_1 + 0x174) = FLOAT_80437170;
    }
    if (*(char *)(iVar4 + 0x145) == '\x03') {
      *(float *)(param_1 + 0x174) = FLOAT_80437170;
    }
    if (*(short *)(iVar4 + 0x784) < 1) {
      *(float *)(param_1 + 0x174) = FLOAT_80437170;
    }
    if (*(float *)(param_1 + 0x174) < FLOAT_80437168) {
      *(float *)(param_1 + 0x178) = FLOAT_80437180;
    }
    if (DOUBLE_80437188 <= (double)*(float *)(param_1 + 0x174)) {
      *(float *)(param_1 + 0x178) = FLOAT_80437168;
    }
  }
  *(undefined *)(param_1 + 0x89) = (&DAT_804336c8)[*(char *)(param_1 + 0x13)];
  iVar4 = *(char *)(param_1 + 0x13) * 0xc;
  uVar3 = *(undefined4 *)(&DAT_802d1094 + iVar4);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802d1090 + iVar4);
  *(undefined4 *)(param_1 + 0x68) = uVar3;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802d1098 + iVar4);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  return;
}



// ==== 8004e9f8  FUN_8004e9f8 ====

void FUN_8004e9f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004ea18  FUN_8004ea18 ====

void FUN_8004ea18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  float afStack_7c [3];
  float local_70;
  undefined4 local_60;
  undefined4 local_50;
  float afStack_4c [15];
  
  iVar4 = *(int *)(param_9 + 0x90);
  iVar1 = (int)(char)(*(char *)(param_9 + 0x13) << 1);
  if (*(char *)(iVar4 + 0xae) == '\0') {
    uVar3 = 0x47;
    iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  }
  else {
    uVar3 = 0x44;
    iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar3);
  if (*(char *)(param_9 + 0x13) == '\x01') {
    if (*(short *)(iVar4 + 0x784) != 0) {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_9 + 0x90) +
                                 *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),afStack_7c);
      gnt4_PSMTXMultVec_bl(afStack_7c,(float *)&DAT_802d10a8,&local_88);
      local_70 = local_88;
      local_60 = local_84;
      local_50 = local_80;
      gnt4_PSMTXRotRad_bl((double)FLOAT_80437190,afStack_4c,0x79);
      gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
      dVar5 = (double)*(float *)(param_9 + 0x174);
      dVar7 = dVar5;
      gnt4_PSMTXScale_bl(dVar5,dVar5,dVar5,afStack_4c);
      pfVar2 = afStack_7c;
      uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_4c,pfVar2);
      if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
        iVar1 = *(int *)(param_9 + 0xf0);
      }
      else {
        iVar1 = *(int *)(param_9 + 0xf4);
      }
      zz_00076d0_(uVar6,dVar5,dVar7,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_7c,
                  (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
      zz_00097b4_(iVar1,uVar3);
    }
  }
  return;
}



// ==== 8004eb98  zz_004eb98_ ====

void zz_004eb98_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x900) || (sVar1 == 0x90d)) || (sVar1 == 0x908)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,4), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_8004ecb0;
    *(code **)(puVar2 + 0x10c) = FUN_8004f124;
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



// ==== 8004ecb0  FUN_8004ecb0 ====

void FUN_8004ecb0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d1130)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004ed04  FUN_8004ed04 ====

void FUN_8004ed04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  uVar4 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  *(undefined1 *)(param_9 + 0x144) = 1;
  *(code **)(param_9 + 0x100) = FUN_8004ef14;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x90) + 0x3e4) + 0x10,1);
  iVar1 = zz_0006f98_(param_9);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_802d1118 + *(char *)(param_9 + 0x11) * 8),iVar1 + 0xc28,uVar4,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar1 + 0xc28;
  iVar2 = *(int *)(&DAT_802d1118 + *(char *)(param_9 + 0x11) * 8);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,uVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,uVar4,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_80437198,*(int *)(param_9 + 0xe4));
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe8),
                      *(int *)(&DAT_802d111c + *(char *)(param_9 + 0x11) * 8),iVar1 + 0xc28,uVar4,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar1 + 0xc28;
  iVar2 = *(int *)(&DAT_802d111c + *(char *)(param_9 + 0x11) * 8);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xec),iVar2,iVar3,uVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar2,iVar3,uVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437198,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_004ee58_(param_9);
  return;
}



// ==== 8004ee58  zz_004ee58_ ====

void zz_004ee58_(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  bVar1 = *(byte *)(iVar2 + 0x145);
  if (bVar1 == 99) {
    return;
  }
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) != 0) {
      *(undefined1 *)(param_1 + 0x144) = 2;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x144) = 1;
  }
  bVar1 = *(byte *)(iVar2 + 0x145);
  if ((bVar1 & 4) == 0) {
    if ((bVar1 & 8) == 0) {
      if (bVar1 == 0) {
        *(undefined1 *)(param_1 + 0x144) = 1;
        *(undefined1 *)(param_1 + 0x145) = 8;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x145) = 8;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x145) = 4;
  }
  *(undefined1 *)(iVar2 + 0x145) = 99;
  return;
}



// ==== 8004eef4  FUN_8004eef4 ====

void FUN_8004eef4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004ef14  FUN_8004ef14 ====

/* WARNING: Removing unreachable block (ram,0x8004f0e8) */
/* WARNING: Removing unreachable block (ram,0x8004f0c0) */
/* WARNING: Removing unreachable block (ram,0x8004f098) */
/* WARNING: Removing unreachable block (ram,0x8004eff0) */
/* WARNING: Removing unreachable block (ram,0x8004efc8) */
/* WARNING: Removing unreachable block (ram,0x8004efa0) */

void FUN_8004ef14(int param_1)

{
  float afStack_38 [13];
  
  if (*(char *)(param_1 + 0x144) == '\x01') {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + DAT_804336d0 * 0x30 + 0x8d4),
                      (float *)(param_1 + 0x114));
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)&DAT_802d10e0,(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    *(undefined2 *)(param_1 + 0x70) = DAT_802d1104;
    *(undefined2 *)(param_1 + 0x72) = DAT_802d1106;
    *(undefined2 *)(param_1 + 0x74) = DAT_802d1108;
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  else if (*(char *)(param_1 + 0x144) == '\x02') {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + cRam804336d1 * 0x30 + 0x8d4),
                      (float *)(param_1 + 0x114));
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)&DAT_802d10ec,(float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
    *(undefined2 *)(param_1 + 0x70) = DAT_802d110a;
    *(undefined2 *)(param_1 + 0x72) = DAT_802d110c;
    *(undefined2 *)(param_1 + 0x74) = DAT_802d110e;
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043719c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 8004f124  FUN_8004f124 ====

void FUN_8004f124(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar3;
  int iVar4;
  
  iVar2 = (int)*(char *)(param_9 + 0x145);
  uVar1 = (int)~(iVar2 - 4U | 4U - iVar2) >> 0x1f & 2;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    if (uVar1 == 0) {
      uVar3 = 0x47;
    }
    else {
      uVar3 = 0x44;
    }
  }
  else {
    uVar3 = 0x44;
    uVar1 = uVar1 + 1;
  }
  iVar4 = *(int *)(param_9 + uVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),(undefined *)0x2,iVar2 - 4U,iVar2,in_r8,in_r9,in_r10);
  zz_00097b4_(iVar4,uVar3);
  return;
}



// ==== 8004f1c4  zz_004f1c4_ ====

void zz_004f1c4_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 1000) != '\x0f') {
    if (*(char *)(param_1 + 1000) == '\x06') {
      iVar2 = *(int *)(&DAT_802d125c + (uint)*(byte *)(param_1 + 0x3e9) * 4);
    }
    else {
      iVar2 = *(int *)(&DAT_802d1240 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
    }
    if (-1 < iVar2) {
      iVar3 = 0;
      do {
        puVar1 = zz_0088aa0_(param_1,2,0,0,2);
        if (puVar1 != (undefined1 *)0x0) {
          *puVar1 = 1;
          puVar1[0x83] = 0x18;
          *(code **)(puVar1 + 0xc) = FUN_8004f330;
          *(code **)(puVar1 + 0x10c) = FUN_8004fc90;
          puVar1[0x11] = (char)iVar2 + (char)iVar3;
          puVar1[0x13] = (char)iVar3;
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
        iVar3 = iVar3 + 1;
      } while (iVar3 < 2);
    }
  }
  return;
}



// ==== 8004f330  FUN_8004f330 ====

void FUN_8004f330(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802d1308)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8004f384  FUN_8004f384 ====

void FUN_8004f384(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  undefined8 uVar11;
  
  iVar9 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar9;
  iVar10 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar5 = *(char *)(param_9 + 0x11) * 0x10;
  uVar11 = zz_0089100_(param_9,(int)*(char *)(iVar10 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804371a0;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_802d1142 + iVar5);
  uVar3 = *(undefined4 *)(&DAT_802d1148 + iVar5);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802d1144 + iVar5);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802d114c + iVar5);
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  *(undefined1 *)(param_9 + 0x1b) = 0;
  iVar2 = zz_0006f98_(iVar10);
  iVar8 = iVar2 + 0xc28;
  iVar6 = (int)*(short *)(&DAT_802d1140 + iVar5);
  zz_0007030_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x600)
              ,*(int *)(param_9 + 0xe0),iVar6,iVar8,iVar9,in_r8,in_r9,in_r10);
  iVar4 = *(int *)(param_9 + 0xe0);
  zz_0008614_((double)FLOAT_804371a4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(iVar2 + 0x600),iVar4,iVar6,iVar8,iVar9,in_r8,in_r9,in_r10);
  uVar11 = FUN_80008ef4((double)FLOAT_804371a8,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0xe0),iVar4,iVar6,iVar8,iVar9,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar2 + 0xc28;
  pfVar7 = (float *)(int)*(short *)(&DAT_802d1140 + iVar5);
  uVar11 = zz_0007030_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe4),(int)pfVar7,iVar4,iVar9,
                       in_r8,in_r9,in_r10);
  zz_0007c54_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),extraout_r4,pfVar7,iVar4,iVar9,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804371ac,*(int *)(param_9 + 0xe4));
  iVar5 = *(int *)(param_9 + 0xe4);
  zz_0008614_((double)FLOAT_804371a4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(iVar2 + 0x600),iVar5,pfVar7,iVar4,iVar9,in_r8,in_r9,in_r10);
  uVar11 = FUN_80008ef4((double)FLOAT_804371a8,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0xe4),iVar5,pfVar7,iVar4,iVar9,in_r8,in_r9,in_r10
                       );
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined4 *)(param_9 + 0x144) =
       *(undefined4 *)(iVar10 + *(char *)(param_9 + 0x89) * 0x30 + 0x8e0);
  *(undefined4 *)(param_9 + 0x148) =
       *(undefined4 *)(iVar10 + *(char *)(param_9 + 0x89) * 0x30 + 0x8f0);
  *(undefined4 *)(param_9 + 0x14c) =
       *(undefined4 *)(iVar10 + *(char *)(param_9 + 0x89) * 0x30 + 0x900);
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
  *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
  *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  zz_004f55c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              *(undefined4 *)(param_9 + 0x144),pfVar7,iVar4,iVar9,in_r8,in_r9,in_r10);
  return;
}



// ==== 8004f55c  zz_004f55c_ ====

/* WARNING: Removing unreachable block (ram,0x8004fc40) */
/* WARNING: Removing unreachable block (ram,0x8004f56c) */

void zz_004f55c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  short sVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  float *pfVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  float afStack_48 [3];
  float local_3c;
  float local_38;
  float local_34;
  undefined8 local_28;
  double local_20;
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined4 *)(param_9 + 0x144) =
       *(undefined4 *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x8e0);
  *(undefined4 *)(param_9 + 0x148) =
       *(undefined4 *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x8f0);
  *(undefined4 *)(param_9 + 0x14c) =
       *(undefined4 *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x900);
  dVar7 = DOUBLE_804371d0;
  sVar3 = *(short *)(iVar5 + 1000);
  if (sVar3 == 0x618) {
    sVar3 = 0x16c;
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 2;
    uVar2 = *(uint *)(iVar5 + 0x5e0);
    if ((uVar2 & 2) != 0) {
      sVar3 = 0x38e;
    }
    if ((uVar2 & 0x20) != 0) {
      sVar3 = 0x38e;
    }
    if ((uVar2 & 0x80) != 0) {
      sVar3 = 0x38e;
    }
    if ((uVar2 & 0x20000000) != 0) {
      sVar3 = 0;
    }
    local_28 = (double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x70) ^ 0x80000000);
    *(short *)(param_9 + 0x70) =
         (short)(int)((float)((double)CONCAT44(0x43300000,(int)sVar3 ^ 0x80000000) - DOUBLE_804371d0
                             ) * *(float *)(iVar5 + 0x1dc8) + (float)(local_28 - DOUBLE_804371d0));
    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  }
  else if ((((sVar3 == 0x604) || (sVar3 == 0x610)) || (sVar3 == 0x612)) ||
          ((sVar3 == 0x621 || (sVar3 == 0x626)))) {
    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  }
  else {
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 == '\x01') {
      if ((*(uint *)(iVar5 + 0x5e0) & 0x1000000) == 0) {
        *(undefined1 *)(param_9 + 0x19) = 0;
      }
      else {
        cVar1 = *(char *)(param_9 + 0x1a);
        if (cVar1 == '\x01') {
          local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c)) ^ 0x80000000);
          *(short *)(param_9 + 0x1c) =
               (short)(int)((float)(local_20 - DOUBLE_804371d0) - *(float *)(iVar5 + 0x768));
          if (*(short *)(param_9 + 0x1c) < 1) {
            *(undefined1 *)(param_9 + 0x1a) = 2;
            *(undefined2 *)(param_9 + 0x1c) = 0x30;
          }
        }
        else if (cVar1 < '\x01') {
          if ((-1 < cVar1) && ((*(uint *)(iVar5 + 0x5e0) & 0x4000000) != 0)) {
            *(undefined1 *)(param_9 + 0x1a) = 1;
            *(undefined2 *)(param_9 + 0x1c) = 0x3c;
          }
        }
        else if (cVar1 < '\x03') {
          local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c)) ^ 0x80000000);
          iVar5 = (int)((float)(local_20 - DOUBLE_804371d0) - *(float *)(iVar5 + 0x768));
          local_28 = (double)(longlong)iVar5;
          *(short *)(param_9 + 0x1c) = (short)iVar5;
          if (*(short *)(param_9 + 0x1c) < 1) {
            *(undefined1 *)(param_9 + 0x19) = 0;
          }
          uVar8 = FUN_80008ef4((double)FLOAT_804371cc,dVar7,param_3,param_4,param_5,param_6,param_7,
                               param_8,*(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,
                               param_14,param_15,param_16);
          zz_0007c30_(uVar8,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4_03,param_11,param_12,param_13,param_14,
                      param_15,param_16);
          uVar8 = FUN_80008ef4((double)FLOAT_804371cc,dVar7,param_3,param_4,param_5,param_6,param_7,
                               param_8,*(int *)(param_9 + 0xe4),extraout_r4_04,param_11,param_12,
                               param_13,param_14,param_15,param_16);
          zz_0007c30_(uVar8,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe4),extraout_r4_05,param_11,param_12,param_13,param_14,
                      param_15,param_16);
          if (*(char *)(param_9 + 0x13) != '\0') {
            iVar5 = *(int *)(param_9 + 0x90);
            if (FLOAT_804371c4 <= *(float *)(iVar5 + 0xb4)) {
              if (*(float *)(iVar5 + 0xb4) <= FLOAT_804371c8) {
                zz_00f0104_(iVar5,0xb,6);
              }
              else {
                zz_00f0104_(iVar5,0xd,6);
              }
            }
            else {
              zz_00f0104_(iVar5,0xc,6);
            }
          }
        }
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        uVar2 = *(uint *)(iVar5 + 0x5e0);
        if ((uVar2 & 0x2000000) == 0) {
          if (*(char *)(iVar5 + 0x6cb) == '\0') {
            if (((*(char *)(iVar5 + 0x1db) != '\0') && ((uVar2 & 0x10) == 0)) &&
               ((uVar2 & 0x20) == 0)) {
              *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
              *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
              *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
              return;
            }
            if ((*(char *)(iVar5 + 0x1dd) == '\0') || (*(char *)(iVar5 + 0x1db) != '\0')) {
              gnt4_PSVECSubtract_bl((float *)(param_9 + 0x144),(float *)(param_9 + 0x150),&local_3c)
              ;
            }
            else {
              dVar7 = gnt4_PSVECSquareMag_bl((float *)(iVar5 + 0x1cc));
              if (dVar7 <= (double)FLOAT_804371a4) {
                local_3c = FLOAT_804371a4;
                local_38 = FLOAT_804371a0;
                local_34 = FLOAT_804371a4;
              }
              else {
                gnt4_PSQUATScale_bl((double)FLOAT_804371b0,(float *)(iVar5 + 0x1cc),&local_3c);
              }
              gnt4_PSVECSubtract_bl
                        ((float *)(param_9 + 0x144),(float *)(param_9 + 0x150),afStack_48);
              gnt4_PSVECAdd_bl(&local_3c,afStack_48,&local_3c);
            }
            dVar7 = gnt4_PSVECSquareMag_bl(&local_3c);
            dVar9 = (double)FLOAT_804371a4;
            if (dVar7 <= dVar9) {
              local_3c = FLOAT_804371a4;
              local_38 = FLOAT_804371a0;
              local_34 = FLOAT_804371a4;
            }
            pfVar4 = &local_3c;
            zz_00451b8_((float *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),pfVar4,pfVar4);
            sVar3 = *(short *)(iVar5 + 1000);
            if ((sVar3 == 0x605) || (sVar3 == 0x619)) {
              dVar7 = (double)local_38;
            }
            else if ((((sVar3 == 0x611) || (sVar3 == 0x61f)) || (sVar3 == 0x622)) ||
                    (sVar3 == 0x625)) {
              dVar7 = -(double)local_38;
            }
            else {
              dVar7 = (double)local_34;
            }
            dVar6 = dVar7;
            if (dVar7 < (double)FLOAT_804371a4) {
              dVar6 = -dVar7;
            }
            if ((double)FLOAT_804371b4 <= dVar6) {
              dVar6 = (double)FLOAT_804371b8;
              if ((dVar7 < dVar6) && (dVar6 = dVar7, dVar7 <= (double)FLOAT_804371bc)) {
                dVar6 = (double)FLOAT_804371bc;
              }
              if (((*(uint *)(iVar5 + 0x5e0) & 0x20) != 0) ||
                 ((*(uint *)(iVar5 + 0x5e0) & 0x40) != 0)) {
                dVar6 = (double)(float)(dVar6 * (double)FLOAT_804371c0);
              }
              uVar8 = FUN_80008ef4(dVar6,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(param_9 + 0xe0),extraout_r4,pfVar4,param_12,param_13,
                                   param_14,param_15,param_16);
              zz_0007c30_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar4,param_12,param_13,param_14,
                          param_15,param_16);
              uVar8 = FUN_80008ef4(dVar6,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(param_9 + 0xe4),extraout_r4_01,pfVar4,param_12,param_13,
                                   param_14,param_15,param_16);
              zz_0007c30_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0xe4),extraout_r4_02,pfVar4,param_12,param_13,param_14,
                          param_15,param_16);
              if (*(char *)(param_9 + 0x13) != '\0') {
                iVar5 = *(int *)(param_9 + 0x90);
                if (FLOAT_804371c4 <= *(float *)(iVar5 + 0xb4)) {
                  if (*(float *)(iVar5 + 0xb4) <= FLOAT_804371c8) {
                    zz_00f0104_(iVar5,0xb,6);
                  }
                  else {
                    zz_00f0104_(iVar5,0xd,6);
                  }
                }
                else {
                  zz_00f0104_(iVar5,0xc,6);
                }
              }
            }
          }
          else {
            *(undefined1 *)(param_9 + 0x19) = 2;
            *(undefined1 *)(param_9 + 0x1a) = 0;
          }
        }
        else {
          *(undefined1 *)(param_9 + 0x19) = 1;
          *(undefined1 *)(param_9 + 0x1a) = 0;
        }
      }
    }
    else if (cVar1 < '\x03') {
      if (*(char *)(iVar5 + 0x6cb) == '\0') {
        *(undefined1 *)(param_9 + 0x19) = 0;
      }
      else {
        cVar1 = *(char *)(param_9 + 0x1a);
        if (cVar1 == '\x02') {
          *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
          if (*(short *)(param_9 + 0x1c) < 1) {
            *(undefined1 *)(param_9 + 0x1a) = 3;
          }
          uVar8 = FUN_80008ef4((double)FLOAT_804371cc,param_2,param_3,param_4,param_5,param_6,
                               param_7,param_8,*(int *)(param_9 + 0xe0),param_10,param_11,param_12,
                               param_13,param_14,param_15,param_16);
          zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4_06,param_11,param_12,param_13,param_14,
                      param_15,param_16);
          uVar8 = FUN_80008ef4((double)FLOAT_804371cc,param_2,param_3,param_4,param_5,param_6,
                               param_7,param_8,*(int *)(param_9 + 0xe4),extraout_r4_07,param_11,
                               param_12,param_13,param_14,param_15,param_16);
          zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe4),extraout_r4_08,param_11,param_12,param_13,param_14,
                      param_15,param_16);
          if (*(char *)(param_9 + 0x13) != '\0') {
            iVar5 = *(int *)(param_9 + 0x90);
            if (FLOAT_804371c4 <= *(float *)(iVar5 + 0xb4)) {
              if (*(float *)(iVar5 + 0xb4) <= FLOAT_804371c8) {
                zz_00f0104_(iVar5,0xb,6);
              }
              else {
                zz_00f0104_(iVar5,0xd,6);
              }
            }
            else {
              zz_00f0104_(iVar5,0xc,6);
            }
          }
        }
        else if (cVar1 < '\x02') {
          if (cVar1 == '\0') {
            if ((*(uint *)(iVar5 + 0x5e0) & 0x40) == 0) {
              *(undefined1 *)(param_9 + 0x1a) = 1;
              *(undefined2 *)(param_9 + 0x1c) = 0x1e;
            }
          }
          else if ((-1 < cVar1) &&
                  (*(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1,
                  *(short *)(param_9 + 0x1c) < 1)) {
            *(undefined1 *)(param_9 + 0x1a) = 2;
            *(undefined2 *)(param_9 + 0x1c) = 0x30;
          }
        }
      }
    }
    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  }
  return;
}



// ==== 8004fc70  FUN_8004fc70 ====

void FUN_8004fc70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8004fc90  FUN_8004fc90 ====

void FUN_8004fc90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 0x47;
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



// ==== 8004fcfc  zz_004fcfc_ ====

void zz_004fcfc_(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = zz_0006f98_(param_1);
  pcVar3 = *(char **)((&PTR_PTR_802d2564)[*(char *)(param_1 + 1000)] +
                     (uint)*(byte *)(param_1 + 0x3e9) * 4);
  if (pcVar3 != (char *)0x0) {
    for (; -1 < *pcVar3; pcVar3 = pcVar3 + 4) {
      if (((((*(uint *)(param_1 + 0x76c) & 1 << (int)pcVar3[1]) != 0) &&
           ((*(uint *)(param_1 + 0x810) & 1 << (int)pcVar3[1]) == 0)) &&
          (iVar1 = (int)pcVar3[2], iVar1 != -1)) && (iVar1 != 7)) {
        (*(code *)(&PTR_FUN_802d1318)[iVar1])(param_1,pcVar3,iVar2,param_2);
      }
    }
  }
  return;
}



// ==== 8004fdf0  FUN_8004fdf0 ====

void FUN_8004fdf0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,byte *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  char cVar2;
  undefined *puVar3;
  
  bVar1 = *(byte *)(param_9 + 0x1d94);
  cVar2 = bVar1 + *param_10;
  if ((char)bVar1 < *(char *)(param_11 + 0xc0f)) {
    puVar3 = (undefined *)(param_11 + param_12 * 0x80);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(puVar3 + cVar2 * 4 + 0x708),(float *)(param_9 + 0xa24),puVar3,param_12,
                (uint)*param_10,(uint)bVar1,param_15,param_16);
    zz_00097b4_(*(int *)(puVar3 + cVar2 * 4 + 0x708),0x47);
  }
  return;
}



// ==== 8004fe60  FUN_8004fe60 ====

void FUN_8004fe60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,byte *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  char cVar2;
  undefined *puVar3;
  
  bVar1 = *(byte *)(param_9 + 0x1d95);
  cVar2 = bVar1 + *param_10;
  if ((char)bVar1 < *(char *)(param_11 + 0xc13)) {
    puVar3 = (undefined *)(param_11 + param_12 * 0x80);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(puVar3 + cVar2 * 4 + 0x708),(float *)(param_9 + 0xae4),puVar3,param_12,
                (uint)*param_10,(uint)bVar1,param_15,param_16);
    zz_00097b4_(*(int *)(puVar3 + cVar2 * 4 + 0x708),0x47);
  }
  return;
}



// ==== 8004fed0  FUN_8004fed0 ====

void FUN_8004fed0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,char *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = param_11 + param_12 * 0x80 + 0x708;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(iVar1 + *param_10 * 4),(float *)(param_9 + param_10[1] * 0x30 + 0x8d4),
              param_9,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar1 + *param_10 * 4),0x47);
  return;
}



// ==== 8004ff50  FUN_8004ff50 ====

void FUN_8004ff50(int param_1,char *param_2,int param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  bool bVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  float local_84;
  float afStack_80 [12];
  float afStack_50 [3];
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_24;
  
  iVar9 = param_3 + param_4 * 0x80 + 0x708;
  iVar8 = *(int *)(iVar9 + *param_2 * 4);
  iVar7 = *(char *)(param_1 + param_2[1] * 4 + 0x1996) * 0x30;
  iVar5 = param_1 + param_2[1] * 0x30;
  iVar6 = param_1 + iVar7;
  local_98 = *(undefined4 *)(iVar6 + 0x8d4);
  local_94 = *(undefined4 *)(iVar6 + 0x8e4);
  local_90 = *(undefined4 *)(iVar6 + 0x8f4);
  local_8c = *(float *)(iVar5 + 0x8d8);
  local_88 = *(float *)(iVar5 + 0x8e8);
  local_84 = *(float *)(iVar5 + 0x8f8);
  pfVar4 = &local_8c;
  bVar1 = zz_0045ef4_(afStack_50,0,&local_98,&local_8c);
  if (bVar1) {
    iVar5 = param_1 + param_2[1] * 0x30;
    local_8c = *(float *)(iVar5 + 0x8dc);
    local_88 = *(float *)(iVar5 + 0x8ec);
    local_84 = *(float *)(iVar5 + 0x8fc);
    pfVar4 = &local_8c;
    zz_0045ef4_(afStack_50,1,&local_98,&local_8c);
  }
  iVar2 = param_1 + param_2[1] * 0x30;
  local_98 = *(undefined4 *)(iVar2 + 0x8e0);
  local_94 = *(undefined4 *)(iVar2 + 0x8f0);
  local_90 = *(undefined4 *)(iVar2 + 0x900);
  local_44 = local_98;
  local_34 = local_94;
  local_24 = local_90;
  zz_0046470_((float *)(param_1 + iVar7 + 0x8d4),&local_8c);
  dVar11 = (double)local_88;
  dVar12 = (double)local_84;
  gnt4_PSMTXScale_bl((double)local_8c,dVar11,dVar12,afStack_80);
  pfVar3 = afStack_50;
  uVar10 = gnt4_PSMTXConcat_bl(pfVar3,afStack_80,pfVar3);
  zz_00076d0_(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar8,afStack_50,
              (undefined *)pfVar3,pfVar4,iVar5,iVar6,param_7,param_8);
  zz_00097b4_(*(int *)(iVar9 + *param_2 * 4),0x47);
  return;
}



// ==== 800500d8  FUN_800500d8 ====

void FUN_800500d8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,char *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  
  local_3c = FLOAT_804371d8;
  local_40 = FLOAT_804371d8;
  local_44 = FLOAT_804371d8;
  local_48 = FLOAT_804371d8;
  local_2c = FLOAT_804371d8;
  local_30 = FLOAT_804371d8;
  local_34 = FLOAT_804371d8;
  local_38 = FLOAT_804371d8;
  local_1c = FLOAT_804371d8;
  local_20 = FLOAT_804371d8;
  local_24 = FLOAT_804371d8;
  local_28 = FLOAT_804371d8;
  gnt4_HSD_MtxScaledAdd_bl
            ((double)*(float *)(&DAT_804336d8 + param_10[3] * 8),
             (float *)(param_9 + *(char *)(param_9 + param_10[1] * 4 + 0x1996) * 0x30 + 0x8d4),
             &local_48,&local_48);
  puVar3 = &DAT_804336d8;
  puVar2 = &DAT_804336d8 + param_10[3] * 8;
  gnt4_HSD_MtxScaledAdd_bl
            ((double)*(float *)(param_10[3] * 8 + -0x7fbcc924),
             (float *)(param_9 + param_10[1] * 0x30 + 0x8d4),&local_48,&local_48);
  puVar1 = (undefined *)(param_9 + param_10[1] * 0x30);
  local_2c = *(float *)(puVar1 + 0x8f0);
  local_1c = *(float *)(puVar1 + 0x900);
  local_3c = *(float *)(puVar1 + 0x8e0);
  iVar4 = *(int *)(param_11 + param_12 * 0x80 + *param_10 * 4 + 0x708);
  zz_00076d0_((double)local_2c,(double)local_1c,param_3,param_4,param_5,param_6,param_7,param_8,
              iVar4,&local_48,puVar1,puVar2,puVar3,param_14,param_15,param_16);
  zz_00097b4_(iVar4,0x47);
  return;
}



// ==== 80050230  FUN_80050230 ====

void FUN_80050230(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,char *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  
  puVar4 = &DAT_804336d8;
  local_3c = FLOAT_804371d8;
  local_40 = FLOAT_804371d8;
  local_44 = FLOAT_804371d8;
  local_48 = FLOAT_804371d8;
  local_2c = FLOAT_804371d8;
  local_30 = FLOAT_804371d8;
  local_34 = FLOAT_804371d8;
  local_38 = FLOAT_804371d8;
  local_1c = FLOAT_804371d8;
  local_20 = FLOAT_804371d8;
  local_24 = FLOAT_804371d8;
  local_28 = FLOAT_804371d8;
  iVar3 = param_9 + param_10[1] * 4;
  cVar1 = *(char *)(iVar3 + 0x1994);
  gnt4_HSD_MtxScaledAdd_bl
            ((double)*(float *)(&DAT_804336d8 + param_10[3] * 8),
             (float *)(param_9 + param_10[1] * 0x30 + 0x8d4),&local_48,&local_48);
  gnt4_HSD_MtxScaledAdd_bl
            ((double)*(float *)(param_10[3] * 8 + -0x7fbcc924),
             (float *)(param_9 + cVar1 * 0x30 + 0x8d4),&local_48,&local_48);
  puVar2 = (undefined *)(param_9 + param_10[1] * 0x30);
  local_2c = *(float *)(puVar2 + 0x8f0);
  local_1c = *(float *)(puVar2 + 0x900);
  local_3c = *(float *)(puVar2 + 0x8e0);
  iVar5 = *(int *)(param_11 + param_12 * 0x80 + *param_10 * 4 + 0x708);
  zz_00076d0_((double)local_2c,(double)local_1c,param_3,param_4,param_5,param_6,param_7,param_8,
              iVar5,&local_48,puVar2,iVar3,puVar4,param_14,param_15,param_16);
  zz_00097b4_(iVar5,0x47);
  return;
}



// ==== 80050368  FUN_80050368 ====

void FUN_80050368(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,char *param_10,
                 int param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  float afStack_48 [3];
  undefined4 local_3c;
  float local_2c;
  float local_1c;
  
  iVar2 = param_11 + param_12 * 0x80;
  iVar3 = *(int *)(iVar2 + *param_10 * 4 + 0x708);
  gnt4_PSMTXCopy_bl((float *)(param_9 + *(char *)(param_9 + param_10[1] * 4 + 0x1996) * 0x30 + 0x8d4
                             ),afStack_48);
  puVar1 = (undefined *)(param_9 + param_10[1] * 0x30);
  local_2c = *(float *)(puVar1 + 0x8f0);
  local_1c = *(float *)(puVar1 + 0x900);
  local_3c = *(undefined4 *)(puVar1 + 0x8e0);
  zz_00076d0_((double)local_2c,(double)local_1c,param_3,param_4,param_5,param_6,param_7,param_8,
              iVar3,afStack_48,puVar1,iVar2,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar3,0x47);
  return;
}



// ==== 8005042c  zz_005042c_ ====

void zz_005042c_(void)

{
  DAT_803b2160 = 0x10;
  DAT_803b2168 = &DAT_803b211c;
  DAT_803b2170 = 0x100;
  DAT_803b2178 = &DAT_803b1d18;
  DAT_803b2180 = 0x100;
  DAT_803b2188 = &DAT_803b1914;
  DAT_803b2190 = 0x100;
  DAT_803b2198 = &DAT_803b1510;
  DAT_803b21a0 = 0x10;
  DAT_803b21a8 = &DAT_803b14cc;
  DAT_803b21b0 = 0x100;
  DAT_803b21b8 = &DAT_803b10c8;
  DAT_803b21c0 = 0x10;
  DAT_803b21c8 = &DAT_803b1084;
  DAT_803b21d0 = 0x100;
  DAT_803b21d8 = &DAT_803b0c80;
  DAT_80436184 = 0x80000;
  DAT_80436180 = 0;
  DAT_80436188 = zz_002a860_(0x80000);
  if (DAT_80436188 != 0) {
    DAT_80436180 = DAT_80436184;
  }
  DAT_80436174 = 0x10000;
  DAT_80436170 = 0;
  DAT_8043618c = DAT_80436188;
  DAT_80436178 = zz_002a860_(0x10000);
  if (DAT_80436178 != 0) {
    DAT_80436170 = DAT_80436174;
  }
  DAT_8043617c = DAT_80436178;
  zz_00505a8_();
  zz_0050604_();
  return;
}



// ==== 80050560  zz_0050560_ ====

void zz_0050560_(int param_1)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)(&DAT_803b2168)[param_1 * 4];
  for (uVar2 = 0; uVar2 < (uint)(&DAT_803b2160)[param_1 * 4]; uVar2 = uVar2 + 1) {
    *puVar1 = (uint)(puVar1 + 1) & 0xf1ffffff;
    puVar1 = puVar1 + 1;
  }
  *puVar1 = 0xe000000;
  return;
}



// ==== 800505a8  zz_00505a8_ ====

void zz_00505a8_(void)

{
  zz_0050560_(0);
  zz_0050560_(1);
  zz_0050560_(2);
  zz_0050560_(3);
  zz_0050560_(4);
  zz_0050560_(5);
  DAT_80436180 = DAT_80436184;
  DAT_80436188 = DAT_8043618c;
  return;
}



// ==== 80050604  zz_0050604_ ====

void zz_0050604_(void)

{
  zz_0050560_(6);
  zz_0050560_(7);
  DAT_80436170 = DAT_80436174;
  DAT_80436178 = DAT_8043617c;
  return;
}



// ==== 80050640  zz_0050640_ ====

int zz_0050640_(int param_1,int param_2)

{
  uint uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  if (param_2 < 6) {
    puVar2 = &DAT_80436180;
    piVar3 = &DAT_80436188;
  }
  else {
    puVar2 = &DAT_80436170;
    piVar3 = &DAT_80436178;
  }
  uVar1 = param_1 + 0x1fU & 0xffffffe0;
  if (uVar1 <= *puVar2) {
    *puVar2 = *puVar2 - uVar1;
    iVar4 = *piVar3;
    *piVar3 = iVar4 + uVar1;
  }
  return iVar4;
}



// ==== 80050694  zz_0050694_ ====

void zz_0050694_(int param_1,uint param_2,uint *param_3)

{
  uint uVar1;
  
  if ((&DAT_803b2160)[param_1 * 4] - 1 < param_2) {
    param_2 = (&DAT_803b2160)[param_1 * 4] - 1;
  }
  uVar1 = *(uint *)((&DAT_803b2168)[param_1 * 4] + param_2 * 4);
  *(uint *)((&DAT_803b2168)[param_1 * 4] + param_2 * 4) =
       uVar1 & 0xe000000 | (uint)param_3 & 0xf1ffffff;
  *param_3 = *param_3 & 0xe000000;
  *param_3 = *param_3 | uVar1 & 0xf1ffffff;
  return;
}



// ==== 800506f0  FUN_800506f0 ====

/* WARNING: Removing unreachable block (ram,0x800507dc) */
/* WARNING: Removing unreachable block (ram,0x80050700) */

void FUN_800506f0(double param_1,int param_2,undefined4 param_3,uint *param_4)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  
  iVar5 = (&DAT_803b2160)[param_2 * 4];
  uVar3 = gnt4___cvt_fp2unsigned_bl
                    ((double)((float)((double)CONCAT44(0x43300000,iVar5) - DOUBLE_804371e8) *
                             (float)((double)FLOAT_804371e0 - param_1)));
  uVar2 = iVar5 - 1;
  if (uVar2 < uVar3) {
    uVar3 = uVar2;
  }
  puVar4 = (uint *)((&DAT_803b2168)[param_2 * 4] + uVar3 * 4);
  do {
    puVar1 = (uint *)(*puVar4 & 0xf1ffffff);
    uVar3 = *puVar1 >> 0x19 & 7;
    if (((uVar3 == 0) || ((*puVar1 & 0xe000000) == 0xe000000)) ||
       ((double)(float)puVar1[2] < param_1)) break;
    puVar4 = puVar1;
  } while (uVar3 != 0);
  uVar3 = *puVar4;
  *puVar4 = uVar3 & 0xe000000 | (uint)param_4 & 0xf1ffffff;
  *param_4 = *param_4 & 0xe000000;
  *param_4 = *param_4 | uVar3 & 0xf1ffffff;
  param_4[2] = (uint)(float)param_1;
  return;
}



// ==== 80050800  zz_0050800_ ====

void zz_0050800_(int param_1,int param_2)

{
  uint *puVar1;
  uint3 local_18;
  undefined4 local_14;
  
  local_14 = DAT_8043d508;
  gnt4_GXSetAlphaCompare_bl(7,0,0,7,0);
  _local_18 = local_14;
  gnt4_GXSetFog_bl((double)FLOAT_804371f0,(double)FLOAT_804371e0,(double)FLOAT_804371f4,
                   (double)FLOAT_804371e0,0,&local_18);
  gnt4_GXSetFogRangeAdj_bl(0,0,(ushort *)0x0);
  gnt4_GXSetLineWidth_bl(6,0);
  gnt4_GXSetPointSize_bl(6,0);
  gnt4_GXEnableTexOffsets_bl(0,0,0);
  gnt4_GXEnableTexOffsets_bl(1,0,0);
  gnt4_GXEnableTexOffsets_bl(2,0,0);
  gnt4_GXEnableTexOffsets_bl(3,0,0);
  gnt4_GXEnableTexOffsets_bl(4,0,0);
  gnt4_GXEnableTexOffsets_bl(5,0,0);
  gnt4_GXEnableTexOffsets_bl(6,0,0);
  gnt4_GXEnableTexOffsets_bl(7,0,0);
  gnt4_GXSetColorUpdate_bl(1);
  gnt4_GXSetAlphaUpdate_bl(1);
  for (puVar1 = (uint *)((&DAT_803b2168)[param_1 * 4] + param_2 * 4);
      (*puVar1 & 0xe000000) != 0xe000000; puVar1 = (uint *)(*puVar1 & 0xf1ffffff)) {
    if ((*puVar1 & 0xe000000) == 0x2000000) {
      zz_0050988_((int)puVar1);
    }
  }
  return;
}



// ==== 80050988  zz_0050988_ ====

void zz_0050988_(int param_1)

{
  switch(*(uint *)(param_1 + 4) >> 0x12 & 0x3f) {
  case 0:
    zz_0050a50_(param_1);
    break;
  case 1:
    zz_0050bf4_(param_1);
    break;
  case 2:
    zz_0050d78_(param_1);
    break;
  case 3:
    zz_0050f80_(param_1);
    break;
  case 4:
    zz_00514cc_(param_1);
    break;
  case 5:
    zz_0051658_(param_1);
    break;
  case 6:
    zz_005116c_(param_1);
  }
  return;
}



// ==== 80050a00  zz_0050a00_ ====

int zz_0050a00_(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x10;
  gnt4_GXSetBlendMode_bl
            (*(uint *)(&DAT_802d2d44 + iVar1),*(uint *)(&DAT_802d2d48 + iVar1),
             *(uint *)(&DAT_802d2d4c + iVar1),*(uint *)(&DAT_802d2d50 + iVar1));
  return param_1;
}



// ==== 80050a50  zz_0050a50_ ====

void zz_0050a50_(int param_1)

{
  undefined4 uVar1;
  float afStack_38 [13];
  
  gnt4_GXSetCullMode_bl(2);
  zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  gnt4_PSMTXIdentity_bl(afStack_38);
  gnt4_GXLoadPosMtxImm_bl(afStack_38,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXSetZMode_bl(1,7,0);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXBegin_bl(0x80,0,4);
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x10);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x12);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(short *)(param_1 + 0x10) + *(short *)(param_1 + 0x18);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x12);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(short *)(param_1 + 0x10) + *(short *)(param_1 + 0x18);
  DAT_cc008000._0_2_ = *(short *)(param_1 + 0x12) + *(short *)(param_1 + 0x1a);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x10);
  DAT_cc008000._0_2_ = *(short *)(param_1 + 0x12) + *(short *)(param_1 + 0x1a);
  DAT_cc008000 = uVar1;
  return;
}



// ==== 80050bf4  zz_0050bf4_ ====

void zz_0050bf4_(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar3 = *(uint *)(param_1 + 0x3c);
  uVar2 = *(uint *)(param_1 + 0x40);
  gnt4_GXSetCullMode_bl(0);
  zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f80,0);
  gnt4_GXLoadPosMtxImm_bl((float *)(param_1 + 0xc),0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXSetZMode_bl(1,3,1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,2);
  gnt4_GXSetVtxDesc_bl(0xb,2);
  gnt4_GXSetArray(9,uVar3,0xc);
  gnt4_GXSetArray(0xb,uVar2,4);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXInvalidateVtxCache_bl();
  gnt4_GXBegin_bl(0xb0,0,*(undefined2 *)(param_1 + 0x44));
  for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(param_1 + 0x44); iVar1 = iVar1 + 1) {
    DAT_cc008000._0_1_ = (char)iVar1;
    DAT_cc008000._0_1_ = (char)iVar1;
  }
  return;
}



// ==== 80050d78  zz_0050d78_ ====

/* WARNING: Removing unreachable block (ram,0x80050f40) */

void zz_0050d78_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_1c = DAT_804371f8;
  gnt4_GXSetCullMode_bl(2);
  gnt4_GXSetZMode_bl(1,3,1);
  zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f80,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetChanCtrl_bl(0,1,0,0,1,2,2);
  uVar2 = 0;
  uVar3 = 0;
  gnt4_GXSetChanCtrl_bl(2,1,0,0,1,0,2);
  local_20 = local_1c;
  gnt4_GXSetChanAmbColor_bl(0,&local_20,uVar2,uVar3);
  local_24 = *(uint *)(param_1 + 0x3c);
  gnt4_GXSetChanMatColor_bl(0,&local_24,uVar2,uVar3);
  local_28 = *(uint *)(param_1 + 0x3c);
  gnt4_GXSetChanMatColor_bl(2,&local_28,uVar2,uVar3);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_PSMTXMultVec_bl((float *)&DAT_803c1100,(float *)&DAT_803c10f4,&local_18);
  gnt4_GXInitLightPos_bl((double)local_18,(double)local_14,(double)local_10,-0x7fc3ef4c);
  gnt4_GXLoadLightObjImm_bl(-0x7fc3ef4c,1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(10,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,10,0,4,0);
  gnt4_GXLoadPosMtxImm_bl((float *)(param_1 + 0xc),0);
  gnt4_GXLoadNrmMtxImm_bl((float *)(param_1 + 0xc),0);
  bVar1 = *(byte *)(param_1 + 0x4c);
  if (bVar1 == 1) {
    zz_022b7a0_();
  }
  else if (bVar1 == 0) {
    zz_022b9f0_('\x02');
  }
  else if (bVar1 < 3) {
    zz_022aebc_(0x10);
  }
  return;
}



// ==== 80050f80  zz_0050f80_ ====

/* WARNING: Removing unreachable block (ram,0x80051150) */
/* WARNING: Removing unreachable block (ram,0x80050f90) */

void zz_0050f80_(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  undefined4 *puVar5;
  double dVar6;
  
  puVar5 = *(undefined4 **)(param_1 + 0x3c);
  puVar4 = *(uint **)(param_1 + 0x40);
  gnt4_GXSetCullMode_bl((uint)*(byte *)(param_1 + 0x4a));
  iVar2 = zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  if (iVar2 == 0) {
    gnt4_GXSetZMode_bl(1,3,1);
  }
  else {
    gnt4_GXSetZMode_bl(1,3,0);
  }
  if (*(char *)(param_1 + 0x4b) == '\0') {
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f80,0);
  }
  else {
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  }
  gnt4_GXLoadPosMtxImm_bl((float *)(param_1 + 0xc),0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXBegin_bl(0x98,0,*(undefined2 *)(param_1 + 0x48));
  dVar6 = DOUBLE_80437200;
  for (iVar2 = 0; iVar2 < (int)(uint)*(ushort *)(param_1 + 0x48); iVar2 = iVar2 + 1) {
    DAT_cc008000 = *puVar5;
    DAT_cc008000 = puVar5[1];
    DAT_cc008000 = puVar5[2];
    uVar3 = gnt4___cvt_fp2unsigned_bl
                      ((double)((float)((double)CONCAT44(0x43300000,(byte)*puVar4 ^ 0x80000000) -
                                       dVar6) * *(float *)(param_1 + 0x44)));
    uVar1 = *puVar4;
    puVar5 = puVar5 + 3;
    puVar4 = puVar4 + 1;
    DAT_cc008000 = uVar3 & 0xff | uVar1 & 0xffffff00;
  }
  return;
}



// ==== 8005116c  zz_005116c_ ====

void zz_005116c_(int param_1)

{
  undefined4 *puVar1;
  undefined2 *puVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  undefined4 *puVar9;
  undefined2 *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  double dVar13;
  undefined4 local_68;
  undefined4 local_64;
  float afStack_60 [12];
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  puVar12 = *(undefined4 **)(param_1 + 0x40);
  puVar11 = *(uint **)(param_1 + 0x44);
  puVar10 = *(undefined2 **)(param_1 + 0x50);
  gnt4_GXSetCullMode_bl((uint)*(byte *)(param_1 + 0x4e));
  iVar6 = zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  if (iVar6 == 0) {
    gnt4_GXSetZMode_bl(1,3,1);
  }
  else {
    gnt4_GXSetZMode_bl(1,3,0);
  }
  if (*(char *)(param_1 + 0x4f) == '\0') {
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f80,0);
    gnt4_GXLoadPosMtxImm_bl((float *)(param_1 + 0x10),0);
  }
  else {
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_GXLoadPosMtxImm_bl((float *)(param_1 + 0x10),0);
  }
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxDesc_bl(0xd,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(1);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  if (*(int *)(param_1 + 0x54) == 0) {
    gnt4_GXSetTevOp_bl(0,0);
  }
  else {
    gnt4_GXSetTevColorOp_bl(0,0,0,0,1,0);
    puVar8 = *(uint **)(param_1 + 0x54);
    gnt4_GXSetTevColorIn_bl(0,*puVar8,puVar8[1],puVar8[2],puVar8[3]);
    gnt4_GXSetTevKColorSel_bl(0,0xc);
    gnt4_GXSetTevAlphaOp_bl(0,0,0,0,1,0);
    iVar6 = *(int *)(param_1 + 0x54);
    gnt4_GXSetTevAlphaIn_bl
              (0,*(uint *)(iVar6 + 0x10),*(uint *)(iVar6 + 0x14),*(uint *)(iVar6 + 0x18),
               *(uint *)(iVar6 + 0x1c));
    local_64 = *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x20);
    gnt4_GXSetTevKColor_bl(0,(byte *)&local_64);
    local_68 = *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x24);
    gnt4_GXSetTevColor_bl(1,(byte *)&local_68);
  }
  gnt4_GXSetTevOrder_bl(0,0,0,4);
  puVar9 = *(undefined4 **)(param_1 + 0xc);
  if ((uint *)puVar9[1] != (uint *)0x0) {
    gnt4_GXLoadTlut_bl((uint *)puVar9[1],0);
  }
  gnt4_GXLoadTexObj_bl((uint *)*puVar9,0);
  uStack_2c = (uint)*(ushort *)(puVar9 + 5);
  uStack_24 = (uint)*(ushort *)((int)puVar9 + 0x16);
  local_30 = 0x43300000;
  dVar13 = (double)FLOAT_804371e0;
  local_28 = 0x43300000;
  gnt4_PSMTXScale_bl((double)(float)(dVar13 / (double)(float)((double)CONCAT44(0x43300000,uStack_2c)
                                                             - DOUBLE_804371e8)),
                     (double)(float)(dVar13 / (double)(float)((double)CONCAT44(0x43300000,uStack_24)
                                                             - DOUBLE_804371e8)),dVar13,afStack_60);
  gnt4_GXLoadTexMtxImm_bl(afStack_60,0x1e,0);
  gnt4_GXSetTexCoordGen2_bl(0,0,4,0x1e,0,0x7d);
  gnt4_GXBegin_bl(0x98,0,*(undefined2 *)(param_1 + 0x4c));
  uVar7 = gnt4___cvt_fp2unsigned_bl((double)(FLOAT_80437208 * *(float *)(param_1 + 0x48)));
  iVar6 = 0;
  while (iVar6 < (int)(uint)*(ushort *)(param_1 + 0x4c)) {
    puVar9 = puVar12 + 2;
    iVar6 = iVar6 + 1;
    puVar1 = puVar12 + 1;
    uVar3 = *puVar12;
    puVar12 = puVar12 + 3;
    DAT_cc008000 = uVar3;
    DAT_cc008000 = *puVar1;
    DAT_cc008000 = *puVar9;
    uVar5 = *puVar11;
    puVar11 = puVar11 + 1;
    DAT_cc008000 = uVar5 & 0xffffff00 | uVar7 & 0xff;
    puVar2 = puVar10 + 1;
    uVar4 = *puVar10;
    puVar10 = puVar10 + 2;
    DAT_cc008000._0_2_ = uVar4;
    DAT_cc008000._0_2_ = *puVar2;
  }
  return;
}



// ==== 800514cc  zz_00514cc_ ====

void zz_00514cc_(int param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  float afStack_48 [15];
  
  uVar3 = *(uint *)(param_1 + 0x3c);
  uVar2 = *(uint *)(param_1 + 0x40);
  gnt4_GXSetCullMode_bl(0);
  zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  gnt4_PSMTXIdentity_bl(afStack_48);
  gnt4_GXLoadPosMtxImm_bl(afStack_48,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXSetZMode_bl(1,3,1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,2);
  gnt4_GXSetVtxDesc_bl(0xb,2);
  gnt4_GXSetArray(9,uVar3,8);
  gnt4_GXSetArray(0xb,uVar2,4);
  gnt4_GXSetVtxAttrFmt_bl(0,9,0,4,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(0);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
  gnt4_GXSetTevOp_bl(0,4);
  gnt4_GXInvalidateVtxCache_bl();
  gnt4_GXBegin_bl(0xb0,0,*(undefined2 *)(param_1 + 0x44));
  for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(param_1 + 0x44); iVar1 = iVar1 + 1) {
    DAT_cc008000._0_1_ = (char)iVar1;
    DAT_cc008000._0_1_ = (char)iVar1;
  }
  return;
}



// ==== 80051658  zz_0051658_ ====

void zz_0051658_(int param_1)

{
  undefined4 uVar1;
  uint *puVar2;
  int iVar3;
  undefined4 *puVar4;
  double dVar5;
  undefined4 local_58;
  undefined4 local_54;
  float afStack_50 [12];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  gnt4_GXSetCullMode_bl(2);
  zz_0050a00_(*(uint *)(param_1 + 4) >> 8 & 0xf);
  gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
  gnt4_PSMTXIdentity_bl(afStack_50);
  gnt4_GXLoadPosMtxImm_bl(afStack_50,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXSetZMode_bl(1,7,0);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXSetVtxDesc_bl(9,1);
  gnt4_GXSetVtxDesc_bl(0xb,1);
  gnt4_GXSetVtxDesc_bl(0xd,1);
  gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
  gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
  gnt4_GXSetNumChans_bl(1);
  gnt4_GXSetNumTexGens_bl(1);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
  if (*(int *)(param_1 + 0x2c) == 0) {
    gnt4_GXSetTevOp_bl(0,0);
  }
  else {
    gnt4_GXSetTevColorOp_bl(0,0,0,0,1,0);
    puVar2 = *(uint **)(param_1 + 0x2c);
    gnt4_GXSetTevColorIn_bl(0,*puVar2,puVar2[1],puVar2[2],puVar2[3]);
    gnt4_GXSetTevKColorSel_bl(0,0xc);
    gnt4_GXSetTevAlphaOp_bl(0,0,0,0,1,0);
    iVar3 = *(int *)(param_1 + 0x2c);
    gnt4_GXSetTevAlphaIn_bl
              (0,*(uint *)(iVar3 + 0x10),*(uint *)(iVar3 + 0x14),*(uint *)(iVar3 + 0x18),
               *(uint *)(iVar3 + 0x1c));
    local_54 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x20);
    gnt4_GXSetTevKColor_bl(0,(byte *)&local_54);
    local_58 = *(undefined4 *)(*(int *)(param_1 + 0x2c) + 0x24);
    gnt4_GXSetTevColor_bl(1,(byte *)&local_58);
  }
  gnt4_GXSetTevOrder_bl(0,0,0,4);
  puVar4 = *(undefined4 **)(param_1 + 0x28);
  if ((uint *)puVar4[1] != (uint *)0x0) {
    gnt4_GXLoadTlut_bl((uint *)puVar4[1],0);
  }
  gnt4_GXLoadTexObj_bl((uint *)*puVar4,0);
  uStack_1c = (uint)*(ushort *)(puVar4 + 5);
  uStack_14 = (uint)*(ushort *)((int)puVar4 + 0x16);
  local_20 = 0x43300000;
  dVar5 = (double)FLOAT_804371e0;
  local_18 = 0x43300000;
  gnt4_PSMTXScale_bl((double)(float)(dVar5 / (double)(float)((double)CONCAT44(0x43300000,uStack_1c)
                                                            - DOUBLE_804371e8)),
                     (double)(float)(dVar5 / (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                            - DOUBLE_804371e8)),dVar5,afStack_50);
  gnt4_GXLoadTexMtxImm_bl(afStack_50,0x1e,1);
  gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
  gnt4_GXBegin_bl(0x80,0,4);
  uVar1 = *(undefined4 *)(param_1 + 0xc);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x10);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x12);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x18);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1a);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1c);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x12);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x24);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1a);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1c);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1e);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x24);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x26);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x10);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x1e);
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x18);
  DAT_cc008000._0_2_ = *(undefined2 *)(param_1 + 0x26);
  return;
}



// ==== 80051998  FUN_80051998 ====

/* WARNING: Removing unreachable block (ram,0x80051b0c) */
/* WARNING: Removing unreachable block (ram,0x80051b04) */
/* WARNING: Removing unreachable block (ram,0x80051afc) */
/* WARNING: Removing unreachable block (ram,0x80051af4) */
/* WARNING: Removing unreachable block (ram,0x80051a60) */
/* WARNING: Removing unreachable block (ram,0x80051a48) */
/* WARNING: Removing unreachable block (ram,0x80051a14) */
/* WARNING: Removing unreachable block (ram,0x80051a04) */
/* WARNING: Removing unreachable block (ram,0x800519c0) */
/* WARNING: Removing unreachable block (ram,0x800519b8) */
/* WARNING: Removing unreachable block (ram,0x800519b0) */
/* WARNING: Removing unreachable block (ram,0x800519a8) */

undefined4 FUN_80051998(int param_1)

{
  uint *puVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  puVar1 = (uint *)zz_0050640_(0x1c,*(int *)(param_1 + 0x34));
  if (puVar1 != (uint *)0x0) {
    *puVar1 = 0x2000000;
    uVar4 = 1;
    puVar1[1] = 0;
    pfVar3 = *(float **)(param_1 + 0x10);
    *(short *)(puVar1 + 4) = (short)(*pfVar3 * 1.0);
    *(short *)((int)puVar1 + 0x12) = (short)(pfVar3[1] * 1.0);
    puVar1[5] = (int)pfVar3[2];
    pfVar2 = *(float **)(param_1 + 0x14);
    if (pfVar2 != (float *)0x0) {
      *(short *)(puVar1 + 4) = *(short *)(puVar1 + 4) + (short)(*pfVar2 * 1.0);
      *(short *)((int)puVar1 + 0x12) = *(short *)((int)puVar1 + 0x12) + (short)(pfVar2[1] * 1.0);
      puVar1[5] = puVar1[5] + (int)pfVar2[2];
      pfVar3 = pfVar2;
    }
    puVar1[6] = **(uint **)(param_1 + 0x24);
    puVar1[3] = **(uint **)(param_1 + 0x20);
    if (*(char *)(param_1 + 0x40) == '\0') {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar1);
    }
    else {
      puVar1[1] = puVar1[1] | 8;
      puVar1[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar1[1] & 0xfffff0ff;
      FUN_800506f0((double)pfVar3[2],*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),
                   puVar1);
    }
  }
  return uVar4;
}



// ==== 80051b2c  FUN_80051b2c ====

/* WARNING: Removing unreachable block (ram,0x80051cf4) */
/* WARNING: Removing unreachable block (ram,0x80051b3c) */

undefined4 FUN_80051b2c(int param_1)

{
  float *pfVar1;
  bool bVar2;
  float fVar3;
  undefined4 uVar4;
  uint *puVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  float *pfVar10;
  undefined4 uVar11;
  double dVar12;
  double in_f31;
  
  uVar11 = 0;
  if ((((2 < *(ushort *)(param_1 + 0x3a)) &&
       (puVar5 = (uint *)zz_0050640_(0x4c,*(int *)(param_1 + 0x34)), puVar5 != (uint *)0x0)) &&
      (pfVar6 = (float *)zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) * 0xc,
                                     *(int *)(param_1 + 0x34)), pfVar6 != (float *)0x0)) &&
     (puVar7 = (undefined4 *)
               zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
     puVar7 != (undefined4 *)0x0)) {
    *puVar5 = 0x2000000;
    uVar11 = 1;
    puVar5[1] = 0xc0000;
    *(undefined1 *)((int)puVar5 + 0x4b) = 0;
    puVar5[0xf] = (uint)pfVar6;
    puVar5[0x10] = (uint)puVar7;
    puVar5[0x11] = *(uint *)(param_1 + 0x44);
    *(undefined1 *)((int)puVar5 + 0x4a) = *(undefined1 *)(param_1 + 0x42);
    if (*(float **)(param_1 + 0xc) == (float *)0x0) {
      gnt4_PSMTXCopy_bl((float *)&DAT_803c1100,(float *)(puVar5 + 3));
    }
    else {
      gnt4_PSMTXConcat_bl((float *)&DAT_803c1100,*(float **)(param_1 + 0xc),(float *)(puVar5 + 3));
    }
    *(undefined2 *)(puVar5 + 0x12) = *(undefined2 *)(param_1 + 0x3a);
    bVar2 = *(char *)(param_1 + 0x40) == '\0';
    if (!bVar2) {
      in_f31 = (double)FLOAT_804371f0;
      puVar5[1] = puVar5[1] | 8;
      puVar5[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar5[1] & 0xfffff0ff;
    }
    pfVar10 = *(float **)(param_1 + 0x10);
    puVar9 = *(undefined4 **)(param_1 + 0x20);
    for (iVar8 = 0; iVar8 < (int)(uint)*(ushort *)(param_1 + 0x3a); iVar8 = iVar8 + 1) {
      if (!bVar2) {
        dVar12 = zz_0005744_(*(float **)(param_1 + 0xc),pfVar10,(float *)0x0);
        in_f31 = (double)(float)(in_f31 + dVar12);
      }
      fVar3 = pfVar10[1];
      *pfVar6 = *pfVar10;
      pfVar6[1] = fVar3;
      pfVar1 = pfVar10 + 2;
      pfVar10 = pfVar10 + 3;
      pfVar6[2] = *pfVar1;
      pfVar6 = pfVar6 + 3;
      uVar4 = *puVar9;
      puVar9 = puVar9 + 1;
      *puVar7 = uVar4;
      puVar7 = puVar7 + 1;
    }
    if (bVar2) {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
    else {
      FUN_800506f0((double)(float)(in_f31 / (double)(float)((double)CONCAT44(0x43300000,
                                                                             (uint)*(ushort *)
                                                                                    (param_1 + 0x3a)
                                                                            ) - DOUBLE_804371e8)),
                   *(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
  }
  return uVar11;
}



// ==== 80051d10  FUN_80051d10 ====

/* WARNING: Removing unreachable block (ram,0x80051ed8) */
/* WARNING: Removing unreachable block (ram,0x80051d20) */

undefined4 FUN_80051d10(int param_1)

{
  float *pfVar1;
  bool bVar2;
  float fVar3;
  undefined4 uVar4;
  uint *puVar5;
  float *pfVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  float *pfVar10;
  undefined4 uVar11;
  double dVar12;
  double in_f31;
  
  uVar11 = 0;
  if ((((2 < *(ushort *)(param_1 + 0x3a)) &&
       (puVar5 = (uint *)zz_0050640_(0x4c,*(int *)(param_1 + 0x34)), puVar5 != (uint *)0x0)) &&
      (pfVar6 = (float *)zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) * 0xc,
                                     *(int *)(param_1 + 0x34)), pfVar6 != (float *)0x0)) &&
     (puVar7 = (undefined4 *)
               zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
     puVar7 != (undefined4 *)0x0)) {
    *puVar5 = 0x2000000;
    uVar11 = 1;
    puVar5[1] = 0xc0000;
    *(undefined1 *)((int)puVar5 + 0x4b) = 1;
    puVar5[0xf] = (uint)pfVar6;
    puVar5[0x10] = (uint)puVar7;
    puVar5[0x11] = *(uint *)(param_1 + 0x44);
    *(undefined1 *)((int)puVar5 + 0x4a) = *(undefined1 *)(param_1 + 0x42);
    if (*(float **)(param_1 + 0xc) == (float *)0x0) {
      gnt4_PSMTXCopy_bl((float *)&DAT_803c1100,(float *)(puVar5 + 3));
    }
    else {
      gnt4_PSMTXConcat_bl((float *)&DAT_803c1100,*(float **)(param_1 + 0xc),(float *)(puVar5 + 3));
    }
    *(undefined2 *)(puVar5 + 0x12) = *(undefined2 *)(param_1 + 0x3a);
    bVar2 = *(char *)(param_1 + 0x40) == '\0';
    if (!bVar2) {
      in_f31 = (double)FLOAT_804371f0;
      puVar5[1] = puVar5[1] | 8;
      puVar5[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar5[1] & 0xfffff0ff;
    }
    pfVar10 = *(float **)(param_1 + 0x10);
    puVar9 = *(undefined4 **)(param_1 + 0x20);
    for (iVar8 = 0; iVar8 < (int)(uint)*(ushort *)(param_1 + 0x3a); iVar8 = iVar8 + 1) {
      if (!bVar2) {
        dVar12 = zz_0005744_(*(float **)(param_1 + 0xc),pfVar10,(float *)0x0);
        in_f31 = (double)(float)(in_f31 + dVar12);
      }
      fVar3 = pfVar10[1];
      *pfVar6 = *pfVar10;
      pfVar6[1] = fVar3;
      pfVar1 = pfVar10 + 2;
      pfVar10 = pfVar10 + 3;
      pfVar6[2] = *pfVar1;
      pfVar6 = pfVar6 + 3;
      uVar4 = *puVar9;
      puVar9 = puVar9 + 1;
      *puVar7 = uVar4;
      puVar7 = puVar7 + 1;
    }
    if (bVar2) {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
    else {
      FUN_800506f0((double)(float)(in_f31 / (double)(float)((double)CONCAT44(0x43300000,
                                                                             (uint)*(ushort *)
                                                                                    (param_1 + 0x3a)
                                                                            ) - DOUBLE_804371e8)),
                   *(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
  }
  return uVar11;
}



// ==== 80051ef4  FUN_80051ef4 ====

/* WARNING: Removing unreachable block (ram,0x800521f4) */
/* WARNING: Removing unreachable block (ram,0x800521ec) */
/* WARNING: Removing unreachable block (ram,0x800521e4) */
/* WARNING: Removing unreachable block (ram,0x800521dc) */
/* WARNING: Removing unreachable block (ram,0x800521d4) */
/* WARNING: Removing unreachable block (ram,0x800521cc) */
/* WARNING: Removing unreachable block (ram,0x80052030) */
/* WARNING: Removing unreachable block (ram,0x8005200c) */
/* WARNING: Removing unreachable block (ram,0x80051fc8) */
/* WARNING: Removing unreachable block (ram,0x80051fb8) */
/* WARNING: Removing unreachable block (ram,0x80051f78) */
/* WARNING: Removing unreachable block (ram,0x80051f68) */
/* WARNING: Removing unreachable block (ram,0x80051f2c) */
/* WARNING: Removing unreachable block (ram,0x80051f24) */
/* WARNING: Removing unreachable block (ram,0x80051f1c) */
/* WARNING: Removing unreachable block (ram,0x80051f14) */
/* WARNING: Removing unreachable block (ram,0x80051f0c) */
/* WARNING: Removing unreachable block (ram,0x80051f04) */

undefined4 FUN_80051ef4(int param_1)

{
  float fVar1;
  double dVar2;
  undefined4 uVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  float *pfVar7;
  undefined4 *puVar8;
  double local_90;
  double local_88;
  double local_80;
  double local_78;
  
  puVar4 = (uint *)zz_0050640_(0x30,*(int *)(param_1 + 0x34));
  if (puVar4 != (uint *)0x0) {
    *puVar4 = 0x2000000;
    puVar4[1] = 0x140000;
    pfVar7 = *(float **)(param_1 + 0x10);
    *(short *)(puVar4 + 4) = (short)(*pfVar7 * 1.0);
    dVar2 = DOUBLE_80437200;
    *(short *)((int)puVar4 + 0x12) = (short)(pfVar7[1] * 1.0);
    local_88 = (double)(CONCAT44(0x43300000,(int)pfVar7[2]) ^ 0x80000000);
    puVar4[5] = (uint)(float)(local_88 - dVar2);
    *(short *)(puVar4 + 7) = (short)(pfVar7[3] * 1.0);
    *(short *)((int)puVar4 + 0x1e) = (short)(pfVar7[4] * 1.0);
    local_78 = (double)(CONCAT44(0x43300000,(int)pfVar7[5]) ^ 0x80000000);
    puVar4[8] = (uint)(float)(local_78 - dVar2);
    pfVar7 = *(float **)(param_1 + 0x14);
    if (pfVar7 != (float *)0x0) {
      fVar1 = *pfVar7;
      *(short *)(puVar4 + 4) = *(short *)(puVar4 + 4) + (short)(fVar1 * 1.0);
      *(short *)(puVar4 + 7) = *(short *)(puVar4 + 7) + (short)(fVar1 * 1.0);
      fVar1 = pfVar7[1];
      *(short *)((int)puVar4 + 0x12) = *(short *)((int)puVar4 + 0x12) + (short)(fVar1 * 1.0);
      *(short *)((int)puVar4 + 0x1e) = *(short *)((int)puVar4 + 0x1e) + (short)(fVar1 * 1.0);
      local_80 = (double)(CONCAT44(0x43300000,(int)pfVar7[2]) ^ 0x80000000);
      puVar4[5] = (uint)((float)puVar4[5] + (float)(local_80 - dVar2));
      local_90 = (double)(CONCAT44(0x43300000,(int)pfVar7[2]) ^ 0x80000000);
      puVar4[8] = (uint)((float)puVar4[8] + (float)(local_90 - dVar2));
    }
    puVar4[3] = **(uint **)(param_1 + 0x20);
    puVar4[6] = **(uint **)(param_1 + 0x2c);
    puVar4[9] = *(uint *)(*(int *)(param_1 + 0x2c) + 4);
    puVar4[10] = *(uint *)(param_1 + 0x30);
    puVar4[0xb] = 0;
    if (*(char *)(param_1 + 0x43) != -1) {
      uVar5 = zz_0050640_(0x28,*(int *)(param_1 + 0x34));
      puVar4[0xb] = uVar5;
      if (uVar5 != 0) {
        puVar8 = (undefined4 *)puVar4[0xb];
        iVar6 = *(char *)(param_1 + 0x43) * 0x28;
        uVar3 = *(undefined4 *)(&DAT_802d25ac + iVar6);
        *puVar8 = *(undefined4 *)(&DAT_802d25a8 + iVar6);
        puVar8[1] = uVar3;
        uVar3 = *(undefined4 *)(&DAT_802d25b4 + iVar6);
        puVar8[2] = *(undefined4 *)(&DAT_802d25b0 + iVar6);
        puVar8[3] = uVar3;
        uVar3 = *(undefined4 *)(&DAT_802d25bc + iVar6);
        puVar8[4] = *(undefined4 *)(&DAT_802d25b8 + iVar6);
        puVar8[5] = uVar3;
        uVar3 = *(undefined4 *)(&DAT_802d25c4 + iVar6);
        puVar8[6] = *(undefined4 *)(&DAT_802d25c0 + iVar6);
        puVar8[7] = uVar3;
        uVar3 = *(undefined4 *)(&DAT_802d25cc + iVar6);
        puVar8[8] = *(undefined4 *)(&DAT_802d25c8 + iVar6);
        puVar8[9] = uVar3;
      }
    }
    if (*(char *)(param_1 + 0x40) == '\0') {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar4);
    }
    else {
      puVar4[1] = puVar4[1] | 8;
      puVar4[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar4[1] & 0xfffff0ff;
      FUN_800506f0((double)(float)puVar4[5],*(int *)(param_1 + 0x34),
                   (uint)*(ushort *)(param_1 + 0x38),puVar4);
    }
  }
  return 0;
}



// ==== 80052214  zz_0052214_ ====

/* WARNING: Removing unreachable block (ram,0x800524b8) */
/* WARNING: Removing unreachable block (ram,0x80052224) */

undefined4 zz_0052214_(int param_1)

{
  float *pfVar1;
  undefined2 *puVar2;
  bool bVar3;
  undefined4 uVar4;
  float fVar5;
  uint *puVar6;
  float *pfVar7;
  undefined4 *puVar8;
  undefined2 *puVar9;
  uint uVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 uVar13;
  undefined2 *puVar14;
  float *pfVar15;
  double dVar16;
  double in_f31;
  
  uVar13 = 0;
  if ((((2 < *(ushort *)(param_1 + 0x3a)) &&
       (puVar6 = (uint *)zz_0050640_(0x58,*(int *)(param_1 + 0x34)), puVar6 != (uint *)0x0)) &&
      (pfVar7 = (float *)zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) * 0xc,
                                     *(int *)(param_1 + 0x34)), pfVar7 != (float *)0x0)) &&
     ((puVar8 = (undefined4 *)
                zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
      puVar8 != (undefined4 *)0x0 &&
      (puVar9 = (undefined2 *)
                zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
      puVar9 != (undefined2 *)0x0)))) {
    *puVar6 = 0x2000000;
    uVar13 = 1;
    puVar6[1] = 0x180000;
    *(undefined1 *)((int)puVar6 + 0x4f) = 0;
    puVar6[0x10] = (uint)pfVar7;
    puVar6[0x11] = (uint)puVar8;
    puVar6[0x14] = (uint)puVar9;
    puVar6[0x12] = *(uint *)(param_1 + 0x44);
    *(undefined1 *)((int)puVar6 + 0x4e) = *(undefined1 *)(param_1 + 0x42);
    if (*(float **)(param_1 + 0xc) == (float *)0x0) {
      gnt4_PSMTXCopy_bl((float *)&DAT_803c1100,(float *)(puVar6 + 4));
    }
    else {
      gnt4_PSMTXConcat_bl((float *)&DAT_803c1100,*(float **)(param_1 + 0xc),(float *)(puVar6 + 4));
    }
    *(undefined2 *)(puVar6 + 0x13) = *(undefined2 *)(param_1 + 0x3a);
    puVar6[3] = *(uint *)(param_1 + 0x30);
    puVar6[0x15] = 0;
    if (*(char *)(param_1 + 0x43) != -1) {
      uVar10 = zz_0050640_(0x28,*(int *)(param_1 + 0x34));
      puVar6[0x15] = uVar10;
      if (uVar10 != 0) {
        puVar12 = (undefined4 *)puVar6[0x15];
        iVar11 = *(char *)(param_1 + 0x43) * 0x28;
        uVar4 = *(undefined4 *)(&DAT_802d25ac + iVar11);
        *puVar12 = *(undefined4 *)(&DAT_802d25a8 + iVar11);
        puVar12[1] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25b4 + iVar11);
        puVar12[2] = *(undefined4 *)(&DAT_802d25b0 + iVar11);
        puVar12[3] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25bc + iVar11);
        puVar12[4] = *(undefined4 *)(&DAT_802d25b8 + iVar11);
        puVar12[5] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25c4 + iVar11);
        puVar12[6] = *(undefined4 *)(&DAT_802d25c0 + iVar11);
        puVar12[7] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25cc + iVar11);
        puVar12[8] = *(undefined4 *)(&DAT_802d25c8 + iVar11);
        puVar12[9] = uVar4;
      }
    }
    bVar3 = *(char *)(param_1 + 0x40) == '\0';
    if (!bVar3) {
      in_f31 = (double)FLOAT_804371f0;
      puVar6[1] = puVar6[1] | 8;
      puVar6[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar6[1] & 0xfffff0ff;
    }
    pfVar15 = *(float **)(param_1 + 0x10);
    puVar12 = *(undefined4 **)(param_1 + 0x20);
    puVar14 = *(undefined2 **)(param_1 + 0x2c);
    for (iVar11 = 0; iVar11 < (int)(uint)*(ushort *)(param_1 + 0x3a); iVar11 = iVar11 + 1) {
      if (!bVar3) {
        dVar16 = zz_0005744_(*(float **)(param_1 + 0xc),pfVar15,(float *)0x0);
        in_f31 = (double)(float)(in_f31 + dVar16);
      }
      fVar5 = pfVar15[1];
      *pfVar7 = *pfVar15;
      pfVar7[1] = fVar5;
      pfVar1 = pfVar15 + 2;
      pfVar15 = pfVar15 + 3;
      pfVar7[2] = *pfVar1;
      pfVar7 = pfVar7 + 3;
      uVar4 = *puVar12;
      puVar12 = puVar12 + 1;
      *puVar8 = uVar4;
      puVar8 = puVar8 + 1;
      *puVar9 = *puVar14;
      puVar2 = puVar14 + 1;
      puVar14 = puVar14 + 2;
      puVar9[1] = *puVar2;
      puVar9 = puVar9 + 2;
    }
    if (bVar3) {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar6);
    }
    else {
      FUN_800506f0((double)(float)(in_f31 / (double)(float)((double)CONCAT44(0x43300000,
                                                                             (uint)*(ushort *)
                                                                                    (param_1 + 0x3a)
                                                                            ) - DOUBLE_804371e8)),
                   *(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar6);
    }
  }
  return uVar13;
}



// ==== 800524d4  zz_00524d4_ ====

/* WARNING: Removing unreachable block (ram,0x800527bc) */
/* WARNING: Removing unreachable block (ram,0x800524e4) */

undefined4 zz_00524d4_(int param_1)

{
  undefined4 *puVar1;
  undefined2 *puVar2;
  bool bVar3;
  undefined4 uVar4;
  uint *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined2 *puVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined2 *puVar13;
  undefined4 uVar14;
  double in_f31;
  
  uVar14 = 0;
  if ((((2 < *(ushort *)(param_1 + 0x3a)) &&
       (puVar5 = (uint *)zz_0050640_(0x58,*(int *)(param_1 + 0x34)), puVar5 != (uint *)0x0)) &&
      (puVar6 = (undefined4 *)
                zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) * 0xc,*(int *)(param_1 + 0x34)),
      puVar6 != (undefined4 *)0x0)) &&
     ((puVar7 = (undefined4 *)
                zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
      puVar7 != (undefined4 *)0x0 &&
      (puVar8 = (undefined2 *)
                zz_0050640_((uint)*(ushort *)(param_1 + 0x3a) << 2,*(int *)(param_1 + 0x34)),
      puVar8 != (undefined2 *)0x0)))) {
    *puVar5 = 0x2000000;
    uVar14 = 1;
    puVar5[1] = 0x180000;
    *(undefined1 *)((int)puVar5 + 0x4f) = 1;
    puVar5[0x10] = (uint)puVar6;
    puVar5[0x11] = (uint)puVar7;
    puVar5[0x14] = (uint)puVar8;
    puVar5[0x12] = *(uint *)(param_1 + 0x44);
    *(undefined1 *)((int)puVar5 + 0x4e) = *(undefined1 *)(param_1 + 0x42);
    if (*(float **)(param_1 + 0xc) == (float *)0x0) {
      gnt4_PSMTXIdentity_bl((float *)(puVar5 + 4));
    }
    else {
      gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0xc),(float *)(puVar5 + 4));
    }
    *(undefined2 *)(puVar5 + 0x13) = *(undefined2 *)(param_1 + 0x3a);
    puVar5[3] = *(uint *)(param_1 + 0x30);
    puVar5[0x15] = 0;
    if (*(char *)(param_1 + 0x43) != -1) {
      uVar9 = zz_0050640_(0x28,*(int *)(param_1 + 0x34));
      puVar5[0x15] = uVar9;
      if (uVar9 != 0) {
        puVar11 = (undefined4 *)puVar5[0x15];
        iVar10 = *(char *)(param_1 + 0x43) * 0x28;
        uVar4 = *(undefined4 *)(&DAT_802d25ac + iVar10);
        *puVar11 = *(undefined4 *)(&DAT_802d25a8 + iVar10);
        puVar11[1] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25b4 + iVar10);
        puVar11[2] = *(undefined4 *)(&DAT_802d25b0 + iVar10);
        puVar11[3] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25bc + iVar10);
        puVar11[4] = *(undefined4 *)(&DAT_802d25b8 + iVar10);
        puVar11[5] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25c4 + iVar10);
        puVar11[6] = *(undefined4 *)(&DAT_802d25c0 + iVar10);
        puVar11[7] = uVar4;
        uVar4 = *(undefined4 *)(&DAT_802d25cc + iVar10);
        puVar11[8] = *(undefined4 *)(&DAT_802d25c8 + iVar10);
        puVar11[9] = uVar4;
      }
    }
    bVar3 = *(char *)(param_1 + 0x40) == '\0';
    if (!bVar3) {
      in_f31 = (double)FLOAT_804371f0;
      puVar5[1] = puVar5[1] | 8;
      puVar5[1] = (*(byte *)(param_1 + 0x40) & 0xf) << 8 | puVar5[1] & 0xfffff0ff;
    }
    puVar11 = *(undefined4 **)(param_1 + 0x10);
    puVar12 = *(undefined4 **)(param_1 + 0x20);
    iVar10 = 0;
    puVar13 = *(undefined2 **)(param_1 + 0x2c);
    if (bVar3) {
      for (; uVar9 = (uint)*(ushort *)(param_1 + 0x3a), iVar10 < (int)uVar9; iVar10 = iVar10 + 1) {
        uVar4 = puVar11[1];
        *puVar6 = *puVar11;
        puVar6[1] = uVar4;
        puVar1 = puVar11 + 2;
        puVar11 = puVar11 + 3;
        puVar6[2] = *puVar1;
        puVar6 = puVar6 + 3;
        uVar4 = *puVar12;
        puVar12 = puVar12 + 1;
        *puVar7 = uVar4;
        puVar7 = puVar7 + 1;
        *puVar8 = *puVar13;
        puVar2 = puVar13 + 1;
        puVar13 = puVar13 + 2;
        puVar8[1] = *puVar2;
        puVar8 = puVar8 + 2;
      }
    }
    else {
      for (; uVar9 = (uint)*(ushort *)(param_1 + 0x3a), iVar10 < (int)uVar9; iVar10 = iVar10 + 1) {
        uVar4 = puVar11[1];
        in_f31 = (double)(float)(in_f31 + (double)(float)puVar11[2]);
        *puVar6 = *puVar11;
        puVar6[1] = uVar4;
        puVar1 = puVar11 + 2;
        puVar11 = puVar11 + 3;
        puVar6[2] = *puVar1;
        puVar6 = puVar6 + 3;
        uVar4 = *puVar12;
        puVar12 = puVar12 + 1;
        *puVar7 = uVar4;
        puVar7 = puVar7 + 1;
        *puVar8 = *puVar13;
        puVar2 = puVar13 + 1;
        puVar13 = puVar13 + 2;
        puVar8[1] = *puVar2;
        puVar8 = puVar8 + 2;
      }
    }
    if (bVar3) {
      zz_0050694_(*(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
    else {
      FUN_800506f0((double)(float)(in_f31 / (double)(float)((double)CONCAT44(0x43300000,uVar9) -
                                                           DOUBLE_804371e8)),
                   *(int *)(param_1 + 0x34),(uint)*(ushort *)(param_1 + 0x38),puVar5);
    }
  }
  return uVar14;
}



// ==== 800527d8  zz_00527d8_ ====

void zz_00527d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                int param_11,undefined *param_12,undefined4 param_13,undefined *param_14,
                uint param_15,int param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  uVar3 = zz_002a3e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_002a638_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  do {
    zz_010d450_();
    zz_008c088_();
    zz_0080278_();
    uVar3 = zz_0052838_();
    uVar3 = zz_00e9994_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,
                        param_14,param_15,param_16);
    uVar2 = extraout_r4;
    DAT_80436190 = zz_008dbe0_();
    zz_000a004_();
    iVar1 = zz_0018b10_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00efda8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,param_11,
                param_12,param_13,param_14,param_15,param_16);
    zz_002a4b0_();
    zz_008c3ac_();
    zz_00528b4_();
    zz_00802a8_();
    zz_008c2dc_();
    zz_008c344_();
    uVar3 = zz_0027c34_();
    zz_002a4d4_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
                param_15,param_16);
  } while( true );
}



// ==== 80052838  zz_0052838_ ====

void zz_0052838_(void)

{
  if (*(int *)(PTR_DAT_80433930 + 0x38) != 0) {
    if (*PTR_DAT_80433930 != '\x04') goto LAB_800528a0;
  }
  zz_008b650_();
  (*(code *)(&PTR_zz_003fbac__802d2e48)[(char)*PTR_DAT_80433930])();
  if (PTR_DAT_80433930[0x42] != '\0') {
    PTR_DAT_80433930[0x42] = PTR_DAT_80433930[0x42] + -1;
  }
LAB_800528a0:
  zz_0052904_();
  return;
}



// ==== 800528b4  zz_00528b4_ ====

void zz_00528b4_(void)

{
  zz_0005668_(0);
  zz_00058d0_(0,1);
  zz_008c154_();
  zz_0050800_(6,0);
  zz_0050800_(7,0);
  zz_0050604_();
  return;
}



// ==== 80052904  zz_0052904_ ====

void zz_0052904_(void)

{
  uint uVar1;
  
  if (DAT_80436190 == 0) {
    if ((*PTR_DAT_80433930 != '\x04') && ((PTR_DAT_80433930[0x2b] & 0x10) != 0)) {
      uVar1 = PlatAudio__IsSFXPlaying_unsigned();
      if (uVar1 == 0) {
        PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 1;
      }
      else {
        PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 4;
      }
      *PTR_DAT_80433930 = 4;
      PTR_DAT_80433930[1] = 0;
    }
  }
  return;
}



// ==== 80052990  zz_0052990_ ====

void zz_0052990_(void)

{
  DAT_80436198 = &DAT_803b21e0;
  gnt4_memset(&DAT_803b21e0,0,0x28);
  DAT_80436198[9] = PTR_DAT_80433930[2];
  zz_00f0920_(0x7f);
  return;
}



// ==== 800529dc  zz_00529dc_ ====

void zz_00529dc_(void)

{
  *(undefined1 *)(DAT_80436198 + 0xd) = 1;
  return;
}



// ==== 800529ec  zz_00529ec_ ====

void zz_00529ec_(void)

{
  *(undefined1 *)(DAT_80436198 + 0xd) = 0;
  return;
}



// ==== 800529fc  zz_00529fc_ ====

undefined1
zz_00529fc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8)

{
  char cVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  undefined1 *puVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (DAT_80436198[0xd] == '\0') {
    iVar4 = 0;
    do {
      if (((uint)(byte)DAT_80436198[9] & 1 << iVar4) != 0) {
        zz_0052d1c_(iVar4);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
    cVar1 = DAT_80436198[5];
    if (cVar1 == '\0') {
      iVar4 = 0;
      iVar6 = 4;
      do {
        if (((uint)(byte)DAT_80436198[6] & 1 << iVar4) != 0) {
          DAT_80436198[5] = (char)(1 << iVar4);
          DAT_80436198[10] = (char)iVar4;
          break;
        }
        iVar4 = iVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    else if (((uint)(byte)DAT_80436198[6] & 1 << (uint)(byte)DAT_80436198[10]) != 0) {
      DAT_80436198[5] = 0;
    }
    if (DAT_80436198[7] == '\0') {
      iVar4 = 0;
      iVar6 = 4;
      do {
        uVar3 = 1 << iVar4;
        if ((((byte)DAT_80436198[8] & uVar3) != 0) &&
           ((((byte)DAT_80436198[5] & uVar3) != 0 || ((byte)DAT_80436198[5] == 0)))) {
          DAT_80436198[5] = (char)uVar3;
          DAT_80436198[7] = (char)uVar3;
          DAT_80436198[10] = (char)iVar4;
          break;
        }
        iVar4 = iVar4 + 1;
        iVar6 = iVar6 + -1;
      } while (iVar6 != 0);
    }
    else if (((uint)(byte)DAT_80436198[8] & 1 << (uint)(byte)DAT_80436198[10]) == 0) {
      DAT_80436198[7] = 0;
    }
    if ((cVar1 == '\0') && (DAT_80436198[5] != '\0')) {
      zz_00f03c0_(0,0x70);
      iVar4 = 0;
      *DAT_80436198 = 0;
      DAT_80436198[4] = 0;
      DAT_80436198[0xb] = 0x1e;
      DAT_80436198[0xf] = DAT_80436198[5];
      do {
        zz_010d8f8_(iVar4,2);
        iVar4 = iVar4 + 1;
      } while (iVar4 < 4);
      zz_00f094c_(1);
      zz_00e9b60_((double)FLOAT_80437210,2,0x1e,1);
      zz_00e9b60_((double)FLOAT_80437214,0,0x1e,2);
      zz_00e9b60_((double)FLOAT_80437214,1,0x1e,2);
      iVar4 = 0;
      puVar5 = &DAT_802d2e60;
      iVar6 = 0;
      do {
        puVar2 = zz_008893c_(2,0x3c,0,(int)*(short *)(puVar5 + 2));
        *(undefined1 **)(DAT_80436198 + iVar6 + 0x10) = puVar2;
        if (puVar2 != (undefined1 *)0x0) {
          *puVar2 = 1;
          *(code **)(puVar2 + 0xc) = FUN_80053074;
          *(code **)(puVar2 + 0x10c) = FUN_800530b0;
          puVar2[0x11] = *puVar5;
          puVar2[0x12] = puVar5[1];
          puVar2[0x10] = DAT_80436198[5];
        }
        iVar4 = iVar4 + 1;
        iVar6 = iVar6 + 4;
        puVar5 = puVar5 + 4;
      } while (iVar4 < 6);
    }
    else if ((cVar1 != '\0') && (DAT_80436198[5] == '\0')) {
      zz_00e9b60_((double)FLOAT_80437218,2,0x1e,0);
      uVar7 = zz_00f094c_(0);
      iVar6 = 0;
      iVar4 = 0;
      do {
        if (*(undefined1 **)(DAT_80436198 + iVar4 + 0x10) != (undefined1 *)0x0) {
          uVar7 = zz_0088e50_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(undefined1 **)(DAT_80436198 + iVar4 + 0x10));
        }
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + 4;
      } while (iVar6 < 6);
    }
  }
  DAT_80436198[6] = 0;
  DAT_80436198[8] = 0;
  return DAT_80436198[5];
}



// ==== 80052d1c  zz_0052d1c_ ====

void zz_0052d1c_(int param_1)

{
  byte bVar1;
  
  bVar1 = (byte)(1 << param_1);
  if ((&DAT_803c7291)[param_1 * 0x20] == '\0') {
    *(byte *)(DAT_80436198 + 8) = *(byte *)(DAT_80436198 + 8) | bVar1;
    return;
  }
  *(byte *)(DAT_80436198 + 8) = *(byte *)(DAT_80436198 + 8) & ~bVar1;
  if ((*(byte *)(DAT_80436198 + 5) != 0) &&
     ((uint)*(byte *)(DAT_80436198 + 5) != (1 << param_1 & 0xffU))) {
    return;
  }
  if (((&DAT_803c7204)[param_1 * 8] & 0x1000) == 0) {
    return;
  }
  *(byte *)(DAT_80436198 + 6) = *(byte *)(DAT_80436198 + 6) | bVar1;
  return;
}



// ==== 80052da8  Wiper::CutHasOccured( ====

undefined1 Wiper__CutHasOccured_(void)

{
  return *(undefined1 *)(DAT_80436198 + 5);
}



// ==== 80052db4  zz_0052db4_ ====

undefined4 zz_0052db4_(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  if (DAT_80436198[7] == '\0') {
    if (DAT_80436198[5] != DAT_80436198[0xf]) {
      DAT_80436198[0xf] = DAT_80436198[5];
      *DAT_80436198 = '\x01';
      DAT_80436198[4] = '\0';
    }
    cVar1 = *DAT_80436198;
    if (cVar1 == '\x02') {
      cVar1 = DAT_80436198[0xe];
      DAT_80436198[0xe] = cVar1 + -1;
      if ((char)(cVar1 + -1) < '\x01') {
        if (DAT_80436198[4] == '\0') {
          DAT_80436198[6] = DAT_80436198[6] | (byte)(1 << (uint)(byte)DAT_80436198[10]);
          zz_00529ec_();
        }
        else {
          *DAT_80436198 = *DAT_80436198 + '\x01';
          DAT_80436198[0xe] = '\0';
          zz_0027aac_(0,0x3c,1);
          zz_00e9b60_((double)FLOAT_80437214,2,0x3c,2);
        }
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if (DAT_80436198[0xb] < '\x01') {
          *DAT_80436198 = '\x01';
        }
        else {
          DAT_80436198[0xb] = DAT_80436198[0xb] + -1;
        }
      }
      else if (-1 < cVar1) {
        cVar1 = DAT_80436198[4];
        uVar2 = zz_008bab0_(1 << (uint)(byte)DAT_80436198[10],3,1);
        iVar3 = zz_008ba58_(uVar2,(int)cVar1,1,1);
        DAT_80436198[4] = (char)iVar3;
        if (DAT_80436198[4] != cVar1) {
          zz_00f03c0_(0,0x77);
        }
        uVar2 = zz_008b888_(1 << (uint)(byte)DAT_80436198[10]);
        if (uVar2 != 0) {
          *DAT_80436198 = *DAT_80436198 + '\x01';
          zz_00f03c0_(0,0x7a);
          DAT_80436198[0xe] = '<';
          zz_00529dc_();
        }
      }
    }
    else if ((cVar1 < '\x04') && (iVar3 = zz_0027adc_(), iVar3 == 0)) {
      uVar4 = 0xffffffff;
    }
  }
  else {
    *DAT_80436198 = '\x01';
    DAT_80436198[4] = '\0';
  }
  zz_0089898_(0x3c);
  zz_008c104_(FUN_80052fe0);
  return uVar4;
}



// ==== 80052fe0  FUN_80052fe0 ====

void FUN_80052fe0(void)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  if (PTR_DAT_80433930[0x34] == '\x04') {
    iVar2 = 0;
    iVar3 = 0;
    do {
      pcVar1 = *(char **)(DAT_80436198 + iVar3 + 0x10);
      if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
        if ((*(code **)(pcVar1 + 0x10c) != (code *)0x0) && (pcVar1[0x82] != '\0')) {
          (**(code **)(pcVar1 + 0x10c))();
        }
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar2 < 6);
  }
  return;
}



// ==== 80053074  FUN_80053074 ====

void FUN_80053074(int param_1)

{
  (*(code *)(&PTR_FUN_802d2e78)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800530b0  FUN_800530b0 ====

void FUN_800530b0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(char *)(param_1 + 0x99); iVar1 = iVar1 + 1) {
    zz_0009958_(*(int *)(iVar2 + 0xe0),2);
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 80053118  FUN_80053118 ====

void FUN_80053118(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined4 extraout_r4;
  double dVar4;
  undefined8 uVar5;
  
  fVar3 = FLOAT_8043721c;
  fVar2 = FLOAT_80437214;
  cVar1 = *(char *)(param_9 + 0x18);
  if (cVar1 == '\x01') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar4 = (double)FLOAT_80437220;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar4);
    if ((float)(param_2 - dVar4) <= fVar2) {
      *(float *)(param_9 + 0xd4) = fVar2;
      *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_9 + 0x18) = cVar1 + '\x01';
    param_11 = (float *)0x68;
    *(float *)(param_9 + 0xd4) = fVar3;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                *(int *)(param_9 + 0xe0),0x68,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0x15;
  }
  uVar5 = zz_00086b8_((double)((FLOAT_8043721c - *(float *)(param_9 + 0xd4)) / FLOAT_8043721c),
                      param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                     );
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800531e4  FUN_800531e4 ====

void FUN_800531e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined4 extraout_r4;
  double dVar4;
  undefined8 uVar5;
  
  fVar3 = FLOAT_80437224;
  fVar2 = FLOAT_80437214;
  cVar1 = *(char *)(param_9 + 0x18);
  if (cVar1 == '\x01') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar4 = (double)FLOAT_80437220;
    *(float *)(param_9 + 0xd4) = (float)(param_2 + dVar4);
    if (fVar3 <= (float)(param_2 + dVar4)) {
      *(float *)(param_9 + 0xd4) = fVar3;
      *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_9 + 0x18) = cVar1 + '\x01';
    param_11 = (float *)0x6e;
    *(float *)(param_9 + 0xd4) = fVar2;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                *(int *)(param_9 + 0xe0),0x6e,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0x15;
  }
  uVar5 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_804361fc,*(int *)(param_9 + 0xe0),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800532a4  FUN_800532a4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_800532a4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  short sVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar6;
  uint uVar7;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar8;
  undefined8 uVar9;
  
  fVar3 = FLOAT_80437228;
  uVar7 = (uint)(*(char *)(DAT_80436198 + 7) != '\0');
  cVar1 = *(char *)(param_9 + 0x18);
  if (cVar1 == '\x02') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar8 = (double)FLOAT_80437228;
    param_1 = (double)(float)(param_2 + (double)FLOAT_80437220);
    *(float *)(param_9 + 0xd4) = (float)(param_2 + (double)FLOAT_80437220);
    if (dVar8 <= param_1) {
      *(float *)(param_9 + 0xd4) = fVar3;
      *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_9 + 0x18) = 1;
      fVar4 = FLOAT_80437220;
      fVar3 = FLOAT_80437214;
      dVar8 = (double)FLOAT_80437214;
      iVar2 = uVar7 * 2;
      *(undefined2 *)(param_9 + 0x1c) =
           *(undefined2 *)(&DAT_804337e0 + *(char *)(param_9 + 0x12) * 2);
      *(float *)(param_9 + 0xd4) = fVar3;
      *(float *)(param_9 + 0x58) = fVar4;
      *(float *)(param_9 + 0x60) = fVar4;
      uVar7 = *(char *)(param_9 + 0x12) * 4;
      param_1 = (double)zz_0006fb4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*(int *)(param_9 + 0xe0),
                                    (int)*(short *)(&DAT_802d2e88 + iVar2 + uVar7),uVar7,in_r7,in_r8
                                    ,in_r9,in_r10);
    }
    else if ((-1 < cVar1) &&
            (sVar5 = *(short *)(param_9 + 0x1c) + -1, *(short *)(param_9 + 0x1c) = sVar5, sVar5 < 1)
            ) {
      *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
      *(undefined1 *)(param_9 + 0x82) = 0x15;
    }
  }
  pfVar6 = (float *)(int)*(char *)(param_9 + 0x12);
  if (pfVar6 == (float *)0x0) {
    if (*(char *)(DAT_80436198 + 7) == '\0') {
      pfVar6 = (float *)(int)_DAT_802d2e88;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0xe0),(int)pfVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      pfVar6 = (float *)(int)u_ullmm_802d2e8a[0];
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0xe0),(int)pfVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
    }
    uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                         (uint)*(byte *)(DAT_80436198 + 10)) -
                                       DOUBLE_80437238),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_804361fc,*(int *)(param_9 + 0xe0),pfVar6,uVar7,in_r7,
                        in_r8,in_r9,in_r10);
    zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
  }
  else if ((-1 < (int)pfVar6) && ((int)pfVar6 < 3)) {
    if (*(char *)(DAT_80436198 + 7) == '\0') {
      if (pfVar6 == (float *)(*(char *)(DAT_80436198 + 4) + 1)) {
        if ((*(byte *)(DAT_80436198 + 0xe) & 4) == 0) {
          dVar8 = (double)FLOAT_80437214;
        }
        else {
          dVar8 = (double)FLOAT_80437220;
        }
      }
      else {
        dVar8 = (double)FLOAT_8043722c;
      }
      uVar9 = zz_00086b8_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                          ,*(int *)(param_9 + 0xe0),pfVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
      zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
      *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 1;
    }
    else {
      *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 0;
    }
  }
  *(float *)(param_9 + 0x5c) = (float)((double)*(float *)(param_9 + 0xd4) * (double)FLOAT_80437230);
  zz_0007ae4_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,*(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x58),(char *)pfVar6,uVar7,
              in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80053500  FUN_80053500 ====

void FUN_80053500(int param_1)

{
  (**(code **)(&DAT_804337e8 + *(char *)(param_1 + 0x18) * 4))();
  return;
}



// ==== 80053538  FUN_80053538 ====

void FUN_80053538(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  char *pcVar1;
  undefined8 uVar2;
  
  if (*DAT_80436198 != '\0') {
    *(undefined1 *)(param_9 + 0x18) = 1;
    uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                        ,*(int *)(param_9 + 0xe0),0x6a,param_12,param_13,param_14,param_15,param_16)
    ;
    pcVar1 = (char *)0x6b;
    uVar2 = zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                        *(int *)(param_9 + 0xe4),0x6b,param_12,param_13,param_14,param_15,param_16);
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0x15;
    zz_00535b0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                pcVar1,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800535b0  zz_00535b0_ ====

void zz_00535b0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  double dVar4;
  undefined4 auStack_38 [2];
  float local_30;
  undefined4 uStack_28;
  undefined4 local_24;
  undefined4 local_18;
  uint uStack_14;
  
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + -0x100;
  zz_0007a60_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),auStack_38,param_11,param_12,param_13,param_14,param_15,
              param_16);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar4 = (double)FLOAT_80437240;
  local_30 = (float)(dVar4 * (double)(float)((double)CONCAT44(0x43300000,uStack_14) -
                                            DOUBLE_80437248));
  uVar3 = zz_0007988_(DOUBLE_80437248,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe4),auStack_38,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  iVar1 = 0;
  iVar2 = param_9;
  do {
    uVar3 = zz_0007908_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar2 + 0xe0),&uStack_28,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    local_24 = *(undefined4 *)(&DAT_804337f0 + *(char *)(DAT_80436198 + 4) * 4);
    uVar3 = zz_0007834_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar2 + 0xe0),&uStack_28,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 2);
  if (*(char *)(DAT_80436198 + 7) == '\0') {
    *(undefined1 *)(param_9 + 0x82) = 0x15;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 800536b0  zz_00536b0_ ====

void zz_00536b0_(undefined1 *param_1)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_803c4e84;
  iVar3 = 0;
  iVar2 = 0;
  do {
    *puVar4 = param_1;
    param_1[0x3e4] = (char)iVar2;
    zz_00537a8_(param_1);
    if (*(short *)(PTR_DAT_80433934 + iVar3 + 0x10) != -1) {
      *param_1 = 1;
      *(undefined2 *)(param_1 + 0x3ea) = *(undefined2 *)(PTR_DAT_80433934 + iVar3 + 0x10);
      *(undefined2 *)(param_1 + 1000) = *(undefined2 *)(param_1 + 0x3ea);
      uVar1 = PTR_DAT_80433934[iVar2 + 0xa0];
      param_1[0x3ed] = uVar1;
      param_1[0x3ec] = uVar1;
      param_1[0x492] = PTR_DAT_80433934[iVar2 + 0x54];
      param_1[0x3f2] = 0;
      param_1[0x486] = 0;
      *(undefined1 **)(param_1 + 0x8c) = param_1;
      *(undefined1 **)(param_1 + 0x90) = param_1;
      *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(param_1 + 1000);
      param_1[0x96] = param_1[0x3e4];
      param_1[0x97] = param_1[999];
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 2;
    param_1 = param_1 + 0x1e00;
    puVar4 = puVar4 + 1;
  } while (iVar2 < 6);
  return;
}



// ==== 800537a8  zz_00537a8_ ====

void zz_00537a8_(void *param_1)

{
  char cVar1;
  
  cVar1 = *(char *)((int)param_1 + 0x3e4);
  gnt4_memset(param_1,0,0x1e00);
  *(undefined1 *)((int)param_1 + 0x83) = 0;
  *(char *)((int)param_1 + 0x3e4) = cVar1;
  *(char *)((int)param_1 + 0x3e5) = (char)(1 << (int)cVar1);
  *(undefined1 *)((int)param_1 + 999) = *(undefined1 *)((int)param_1 + 0x3e4);
  return;
}



// ==== 8005380c  zz_005380c_ ====

void zz_005380c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  char *pcVar4;
  undefined8 uVar5;
  int local_18 [4];
  
  local_18[0] = 0;
  iVar3 = zz_0006f98_(param_9);
  uVar5 = zz_0067e18_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      *(int *)(*(int *)(iVar3 + 0x708) + 0xc),iVar3 + 0x608,local_18,in_r7,in_r8,
                      in_r9,in_r10);
  local_18[0] = 0;
  zz_0067e18_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              *(int *)(*(int *)(iVar3 + 0x788) + 0xc),iVar3 + 0x688,local_18,in_r7,in_r8,in_r9,
              in_r10);
  *(char *)(param_9 + 0x1d90) = (char)local_18[0];
  *(int *)(param_9 + 0x1db4) = iVar3 + 0x608;
  *(int *)(param_9 + 0x1db8) = iVar3 + 0x688;
  pcVar4 = *(char **)((&PTR_PTR_802d2564)[*(char *)(param_9 + 1000)] +
                     (uint)*(byte *)(param_9 + 0x3e9) * 4);
  iVar3 = zz_0006f98_(param_9);
  while( true ) {
    if (*pcVar4 < '\0') break;
    cVar2 = *(char *)(iVar3 + pcVar4[1] + 0xc08);
    *(undefined4 *)(iVar3 + pcVar4[1] * 0x20 + cVar2 * 4 + 0x808) =
         *(undefined4 *)(iVar3 + *pcVar4 * 4 + 0x708);
    pcVar1 = pcVar4 + 1;
    pcVar4 = pcVar4 + 4;
    *(char *)(iVar3 + *pcVar1 + 0xc08) = cVar2 + '\x01';
  }
  return;
}



// ==== 80053928  zz_0053928_ ====

void zz_0053928_(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = &DAT_803c4e84;
  iVar4 = 3;
  do {
    iVar3 = *piVar2;
    if ((iVar3 != 0) && (*(char *)(iVar3 + 0x82) != '\0')) {
      iVar1 = (&DAT_803c6e4c)[*(char *)(iVar3 + 0x3e4)];
      *(undefined4 *)(iVar3 + 0x110) = 0;
      (&DAT_803c6e4c)[*(char *)(iVar3 + 0x3e4)] = iVar3;
      if (iVar1 == 0) {
        (&DAT_803c6e64)[*(char *)(iVar3 + 0x3e4)] = iVar3;
      }
      else {
        *(int *)(iVar1 + 0x110) = iVar3;
      }
    }
    iVar3 = piVar2[1];
    if ((iVar3 != 0) && (*(char *)(iVar3 + 0x82) != '\0')) {
      iVar1 = (&DAT_803c6e4c)[*(char *)(iVar3 + 0x3e4)];
      *(undefined4 *)(iVar3 + 0x110) = 0;
      (&DAT_803c6e4c)[*(char *)(iVar3 + 0x3e4)] = iVar3;
      if (iVar1 == 0) {
        (&DAT_803c6e64)[*(char *)(iVar3 + 0x3e4)] = iVar3;
      }
      else {
        *(int *)(iVar1 + 0x110) = iVar3;
      }
    }
    piVar2 = piVar2 + 2;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return;
}



// ==== 80053a2c  zz_0053a2c_ ====

void zz_0053a2c_(void)

{
  int iVar1;
  int *piVar2;
  
  FUN_8005ace8();
  piVar2 = &DAT_803c4e6c;
  for (iVar1 = 0; iVar1 < DAT_80436260; iVar1 = iVar1 + 1) {
    FUN_80054070(*piVar2);
    piVar2 = piVar2 + 1;
  }
  zz_005b140_();
  zz_005b2b8_();
  return;
}



// ==== 80053a94  zz_0053a94_ ====

void zz_0053a94_(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_803c4e6c;
  iVar2 = 0;
  while( true ) {
    if (DAT_80436260 <= iVar2) break;
    iVar1 = *piVar3;
    if ((*(byte *)(iVar1 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0) {
      if (*(code **)(iVar1 + 0x4e0) != (code *)0x0) {
        if ((*(char *)(iVar1 + 0x18) != '\0') && (*(char *)(iVar1 + 0x18) != '\x03')) {
          (**(code **)(iVar1 + 0x4e0))();
        }
      }
    }
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 80053b30  zz_0053b30_ ====

void zz_0053b30_(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  undefined4 *puVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  char *pcVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  uint uVar15;
  char local_18 [20];
  
  pcVar9 = local_18;
  DAT_803c6dec = 0;
  DAT_803c6df0 = 0;
  DAT_803c6df4 = 0;
  DAT_803c6df8 = 0;
  DAT_803c6dfc = 0;
  DAT_803c6e00 = 0;
  DAT_803c6e04 = 0;
  DAT_803c6e08 = 0;
  DAT_803c6e0c = 0;
  DAT_803c6e10 = 0;
  DAT_803c6e14 = 0;
  DAT_803c6e18 = 0;
  DAT_803c6e1c = 0;
  DAT_803c6e20 = 0;
  DAT_803c6e24 = 0;
  DAT_803c6e28 = 0;
  DAT_803c6e2c = 0;
  DAT_803c6e30 = 0;
  DAT_803c6e34 = 0;
  DAT_803c6e38 = 0;
  DAT_80436264 = 0;
  DAT_803c6e3c = 0;
  uRam80436265 = 0;
  DAT_803c6e40 = 0;
  uRam80436266 = 0;
  DAT_803c6e44 = 0;
  DAT_803c6e48 = 0;
  uRam80436267 = 0;
  iVar14 = 6;
  pcVar11 = DAT_803c4e84;
  do {
    fVar2 = FLOAT_80437250;
    if (*pcVar11 != '\0') {
      *pcVar9 = '\0';
      *(float *)(pcVar11 + 0x204) = FLOAT_80437250;
      if ((pcVar11[0x18] == '\x01') || (pcVar11[0x18] == '\x02')) {
        fVar2 = *(float *)(*(int *)(pcVar11 + 0x4ac) + 0x98);
        if (FLOAT_80437254 <= fVar2) {
          *(float *)(pcVar11 + 0x208) = fVar2;
        }
        else {
          *(float *)(pcVar11 + 0x208) = fVar2 * *(float *)(pcVar11 + 0xb4);
        }
      }
      else {
        *(float *)(pcVar11 + 0x208) = fVar2;
      }
      if (pcVar11[0x18] == '\x01') {
        iVar7 = (int)pcVar11[0x88];
        cVar1 = (&DAT_80436264)[iVar7];
        (&DAT_80436264)[iVar7] = cVar1 + '\x01';
        (&DAT_803c6dec)[iVar7 * 6 + (int)cVar1] = pcVar11;
      }
    }
    pcVar9 = pcVar9 + 1;
    pcVar11 = pcVar11 + 0x1e00;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  piVar6 = (int *)&DAT_803c4e84;
  iVar14 = 3;
  do {
    iVar10 = *piVar6;
    *(float *)(iVar10 + 0x204) = *(float *)(iVar10 + 0x204) + *(float *)(iVar10 + 0x208);
    iVar7 = iVar10;
    while ((*(char *)(iVar7 + 0x1db) != '\0' &&
           (iVar7 = *(int *)(iVar7 + 0x1e4), *(char *)(iVar7 + 0x83) == '\0'))) {
      fVar2 = *(float *)(iVar7 + 0x204);
      fVar3 = *(float *)(iVar10 + 0x208);
      local_18[*(char *)(iVar7 + 0x3e4)] = local_18[*(char *)(iVar7 + 0x3e4)] + '\x01';
      *(float *)(iVar7 + 0x204) = fVar2 + fVar3;
    }
    iVar10 = piVar6[1];
    *(float *)(iVar10 + 0x204) = *(float *)(iVar10 + 0x204) + *(float *)(iVar10 + 0x208);
    iVar7 = iVar10;
    while ((*(char *)(iVar7 + 0x1db) != '\0' &&
           (iVar7 = *(int *)(iVar7 + 0x1e4), *(char *)(iVar7 + 0x83) == '\0'))) {
      fVar2 = *(float *)(iVar7 + 0x204);
      fVar3 = *(float *)(iVar10 + 0x208);
      local_18[*(char *)(iVar7 + 0x3e4)] = local_18[*(char *)(iVar7 + 0x3e4)] + '\x01';
      *(float *)(iVar7 + 0x204) = fVar2 + fVar3;
    }
    piVar6 = piVar6 + 2;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  uVar4 = zz_00055fc_();
  uVar13 = (uVar4 >> 2) % 6;
  uVar4 = zz_00055fc_();
  fVar2 = FLOAT_80437258;
  iVar14 = -1;
  if ((uVar4 & 8) != 0) {
    iVar14 = 1;
  }
  iVar7 = 0;
  DAT_80436260 = '\0';
  do {
    pcVar11 = (&DAT_803c4e84)[uVar13];
    *(float *)(pcVar11 + 0x664) = fVar2;
    if ((int)(uVar13 + iVar14) < 0) {
      uVar13 = 5;
    }
    else {
      uVar13 = (int)(uVar13 + iVar14) % 6;
    }
    if ((*pcVar11 != '\0') && (pcVar11[0x4a0] != '\x01')) {
      piVar6 = &DAT_803c4e6c;
      iVar12 = (int)DAT_80436260;
      iVar10 = 0;
      iVar8 = iVar12 + 1;
      if (-1 < iVar12) {
LAB_80053e1c:
        if (iVar10 == iVar12) {
          iVar10 = (int)DAT_80436260;
          DAT_80436260 = DAT_80436260 + '\x01';
          (&DAT_803c4e6c)[iVar10] = pcVar11;
        }
        else {
          if (local_18[pcVar11[0x3e4]] <= local_18[*(char *)(*piVar6 + 0x3e4)]) goto LAB_80053f24;
          iVar8 = (int)DAT_80436260;
          puVar5 = &DAT_803c4e6c + iVar8;
          uVar4 = iVar8 - iVar10;
          if (iVar10 < iVar8) {
            uVar15 = uVar4 >> 3;
            if (uVar15 == 0) goto LAB_80053ef4;
            do {
              *puVar5 = puVar5[-1];
              puVar5[-1] = puVar5[-2];
              puVar5[-2] = puVar5[-3];
              puVar5[-3] = puVar5[-4];
              puVar5[-4] = puVar5[-5];
              puVar5[-5] = puVar5[-6];
              puVar5[-6] = puVar5[-7];
              puVar5[-7] = puVar5[-8];
              puVar5 = puVar5 + -8;
              uVar15 = uVar15 - 1;
            } while (uVar15 != 0);
            for (uVar4 = uVar4 & 7; uVar4 != 0; uVar4 = uVar4 - 1) {
LAB_80053ef4:
              *puVar5 = puVar5[-1];
              puVar5 = puVar5 + -1;
            }
          }
          DAT_80436260 = DAT_80436260 + '\x01';
          (&DAT_803c4e6c)[iVar10] = pcVar11;
        }
      }
    }
LAB_80053f30:
    iVar7 = iVar7 + 1;
  } while (iVar7 < 6);
  iVar14 = 0;
  pcVar11 = DAT_803c4e84;
  do {
    if ((*pcVar11 != '\0') && (pcVar11[0x4a0] == '\x01')) {
      piVar6 = &DAT_803c4e6c;
      iVar10 = 0;
      iVar7 = DAT_80436260 + 1;
      if (-1 < DAT_80436260) {
LAB_80053f80:
        if (*piVar6 != *(int *)(pcVar11 + 0x4a4)) goto LAB_80054040;
        iVar7 = (int)DAT_80436260;
        puVar5 = &DAT_803c4e6c + iVar7;
        uVar4 = iVar7 - iVar10;
        if (iVar10 < iVar7) {
          uVar13 = uVar4 >> 3;
          if (uVar13 == 0) goto LAB_80054010;
          do {
            *puVar5 = puVar5[-1];
            puVar5[-1] = puVar5[-2];
            puVar5[-2] = puVar5[-3];
            puVar5[-3] = puVar5[-4];
            puVar5[-4] = puVar5[-5];
            puVar5[-5] = puVar5[-6];
            puVar5[-6] = puVar5[-7];
            puVar5[-7] = puVar5[-8];
            puVar5 = puVar5 + -8;
            uVar13 = uVar13 - 1;
          } while (uVar13 != 0);
          for (uVar4 = uVar4 & 7; uVar4 != 0; uVar4 = uVar4 - 1) {
LAB_80054010:
            *puVar5 = puVar5[-1];
            puVar5 = puVar5 + -1;
          }
        }
        DAT_80436260 = DAT_80436260 + '\x01';
        (&DAT_803c4e6c)[iVar10] = pcVar11;
      }
    }
LAB_8005404c:
    iVar14 = iVar14 + 1;
    pcVar11 = pcVar11 + 0x1e00;
    if (5 < iVar14) {
      return;
    }
  } while( true );
LAB_80053f24:
  piVar6 = piVar6 + 1;
  iVar10 = iVar10 + 1;
  iVar8 = iVar8 + -1;
  if (iVar8 == 0) goto LAB_80053f30;
  goto LAB_80053e1c;
LAB_80054040:
  piVar6 = piVar6 + 1;
  iVar10 = iVar10 + 1;
  iVar7 = iVar7 + -1;
  if (iVar7 == 0) goto LAB_8005404c;
  goto LAB_80053f80;
}



// ==== 80054070  FUN_80054070 ====

/* WARNING: Removing unreachable block (ram,0x80054190) */
/* WARNING: Removing unreachable block (ram,0x80054080) */

void FUN_80054070(int param_1)

{
  float fVar1;
  char cVar2;
  double dVar3;
  
  zz_005685c_(param_1);
  if ((*(byte *)(param_1 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0) {
    (*(code *)(&PTR_FUN_802d3264)[*(char *)(param_1 + 0x18)])(param_1);
  }
  *(float *)(param_1 + 0x6dc) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0);
  cVar2 = zz_008b480_();
  if (((cVar2 == '\0') && (*(char *)(param_1 + 0x730) != '\0')) &&
     (*(char *)(param_1 + 0x18) == '\x01')) {
    dVar3 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x724),(float *)(param_1 + 0x20))
    ;
    fVar1 = (float)(dVar3 - (double)*(float *)(param_1 + 0x6d0));
    if (*(float *)(param_1 + 0x24) < fVar1) {
      *(float *)(param_1 + 0x24) = fVar1;
    }
  }
  FUN_8005a580(param_1);
  if ((*(char *)(param_1 + 0x18) == '\x01') || (*(char *)(param_1 + 0x18) == '\x02')) {
    zz_00465fc_(param_1);
  }
  fVar1 = FLOAT_80437250;
  *(undefined1 *)(param_1 + 0x1ca) = 0;
  *(undefined1 *)(param_1 + 0x732) = 0;
  *(undefined1 *)(param_1 + 0x730) = 0;
  *(undefined1 *)(param_1 + 0x731) = 0;
  *(float *)(param_1 + 0x724) = fVar1;
  *(float *)(param_1 + 0x728) = fVar1;
  *(float *)(param_1 + 0x72c) = fVar1;
  zz_0006284_(param_1);
  return;
}



// ==== 800541ac  FUN_800541ac ====

void FUN_800541ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  iVar4 = zz_00422d8_((int)param_9[0x3e4]);
  if (iVar4 != 0) {
    param_9[0x18] = '\x01';
    param_9[0x19] = '\0';
    param_9[0x1a] = '\0';
    param_9[0x1b] = '\0';
    param_9[0x493] = '\0';
    *(float *)(param_9 + 0x24) = *(float *)(param_9 + 0x24) + *(float *)(param_9 + 0x6d0);
    gnt4_memset(param_9 + 0x144,0,0x80);
    uVar5 = 0x394;
    gnt4_memset(param_9 + 0x540,0,0x394);
    fVar3 = FLOAT_80437250;
    *(float *)(param_9 + 0x50) = FLOAT_80437250;
    *(float *)(param_9 + 0x48) = fVar3;
    *(float *)(param_9 + 0x4c) = fVar3;
    *(float *)(param_9 + 0x44) = fVar3;
    param_9[0x80] = '\0';
    param_9[0x81] = '\0';
    param_9[0x7e] = '\0';
    param_9[0x7f] = '\0';
    param_9[0x7c] = '\0';
    param_9[0x7d] = '\0';
    param_9[0x501] = '\0';
    param_9[0x530] = '\0';
    param_9[0x531] = '\0';
    param_9[0x532] = '\0';
    param_9[0x533] = '\0';
    param_9[0x534] = '\0';
    param_9[0x535] = '\0';
    param_9[0x536] = '\0';
    param_9[0x537] = '\0';
    param_9[0x538] = '\0';
    param_9[0x539] = '\0';
    param_9[0x53a] = '\0';
    param_9[0x53b] = '\0';
    param_9[0x53c] = '\0';
    param_9[0x53d] = '\0';
    param_9[0x53e] = '\0';
    param_9[0x53f] = '\0';
    param_9[999] = param_9[0x3e4];
    *(undefined2 *)(param_9 + 1000) = *(undefined2 *)(PTR_DAT_80433934 + param_9[999] * 2 + 0x10);
    param_9[0x3ec] = PTR_DAT_80433934[param_9[999] + 0xa0];
    param_9[0x88] = PTR_DAT_80433934[param_9[0x3e4] + 0xcb];
    if (param_9[0x490] == '\0') {
      FUN_80068344((int)param_9);
      *(undefined2 *)(param_9 + 0x3ea) = *(undefined2 *)(param_9 + 1000);
      param_9[0x3ed] = param_9[0x3ec];
      param_9[0x3ef] = param_9[0x3ee];
    }
    else if (param_9[0x4a0] == '\0') {
      param_9[0x3ee] = param_9[0x48f];
    }
    else {
      param_9[0x3ee] =
           (char)((int)param_9[0x48f] + (int)*(char *)(*(int *)(param_9 + 0x4a4) + 0x48f) >> 1);
    }
    param_9[0x3f0] = param_9[0x3f0] + '\x01';
    uVar6 = zz_0056ce0_((int)param_9);
    if ((param_9[0x490] == '\0') && (-1 < *(short *)(*(int *)(param_9 + 0x4ac) + 0xa6))) {
      *(short *)(param_9 + 0x3ea) = *(short *)(*(int *)(param_9 + 0x4ac) + 0xa6);
    }
    *(char **)(param_9 + 0x8c) = param_9;
    *(char **)(param_9 + 0x90) = param_9;
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_9 + 1000);
    param_9[0x96] = param_9[0x3e4];
    param_9[0x97] = param_9[999];
    if (param_9[0x48a] == '\0') {
      uVar6 = zz_00419ec_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9
                          ,extraout_r4,uVar5,param_12,param_13,param_14,param_15,param_16);
      zz_005380c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9);
      zz_0041b20_((int)param_9);
    }
    if ((PTR_DAT_80433930[2] & param_9[0x3e5]) == 0) {
      param_9[0x3e6] = '\x01';
      param_9[0x488] = '\x01';
      if (PTR_DAT_80433930[0x32] == '\x02') {
        param_9[0x3f3] = '\0';
      }
      else {
        param_9[0x3f3] = '\x01';
      }
    }
    else {
      param_9[0x3e6] = '\0';
      param_9[0x488] = '\0';
      param_9[0x3f3] = '\0';
    }
    *(code **)(param_9 + 0x10c) = FUN_80056aa8;
    param_9[0x76c] = -1;
    param_9[0x76d] = -1;
    param_9[0x76e] = -1;
    param_9[0x76f] = -1;
    param_9[0x5a0] = '\0';
    param_9[0x5a1] = '\0';
    param_9[0x5a2] = '\0';
    param_9[0x5a3] = '\0';
    param_9[0x26f] = '\x01';
    param_9[0x82] = '\0';
    zz_0055f90_((int)param_9);
    zz_005614c_((int)param_9);
    zz_0055dcc_((int)param_9);
    zz_0068004_((int)param_9);
    FUN_80027a44((int)param_9);
    FUN_8004bb14((int)param_9);
    zz_003cc24_((int)param_9);
    zz_001c80c_(param_9);
    (**(code **)(param_9 + 0x4b8))(param_9);
    FUN_800807e4(param_9);
    FUN_800813a8(param_9);
    if (param_9[0x4a0] != '\x02') {
      if (param_9[0x48a] == '\x01') {
        *(int *)(param_9 + 0x3fc) = *(int *)(PTR_DAT_80433934 + 0x9c) + param_9[0x48b] * 0x1ea0;
      }
      zz_008ab30_((int)param_9);
    }
    if (param_9[0x490] == '\0') {
      param_9[0x491] = param_9[0x491] + '\x01';
      if (param_9[0x500] == '\0') {
        FUN_80056d28(param_9);
        param_9[0x3f1] = '\0';
      }
      param_9[0x741] = '\x01';
    }
    else {
      param_9[0x741] = '\x02';
    }
    param_9[0x742] = '\0';
    if (param_9[0x4a0] == '\0') {
      if (PTR_DAT_80433930[0x32] == '\0') {
        param_9[0x742] = PTR_DAT_80433934[param_9[0x3e4] + 0x164c];
        PTR_DAT_80433934[param_9[0x3e4] + 0x164c] = 0;
      }
      cVar1 = param_9[0x742];
      if (cVar1 == '\x02') {
        zz_006a750_((int)param_9,6);
        zz_006a6fc_((int)param_9,6);
        zz_004beb8_((double)FLOAT_8043725c,(int)param_9,0xf,0,0xd,0,0);
      }
      else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
        zz_006a750_((int)param_9,0);
        zz_006a6fc_((int)param_9,0);
        zz_004beb8_((double)FLOAT_8043725c,(int)param_9,0xf,0,0,0,0);
      }
      else {
        zz_006a750_((int)param_9,0);
        zz_006a6fc_((int)param_9,0);
        zz_004beb8_((double)FLOAT_8043725c,(int)param_9,0xf,0,8,0,0);
      }
    }
    else {
      zz_006a750_((int)param_9,0x1a);
      zz_006a6fc_((int)param_9,0x1a);
    }
    iVar4 = *(int *)(param_9 + 0x508);
    if ((iVar4 != 0) &&
       (((**(char **)(param_9 + 0x504) == '\0' || (*(char *)(iVar4 + 0x83) != '\0')) ||
        (*(char *)(iVar4 + 0x88) == param_9[0x88])))) {
      param_9[0x73c] = '\x02';
    }
    puVar2 = PTR_DAT_80433934;
    if (param_9[0x4a0] != '\0') {
      iVar4 = param_9[0x88] * 0x3c;
      PTR_DAT_80433934[iVar4 + 0x103] = 0;
      puVar2[iVar4 + 0x104] = 2;
      *(undefined2 *)(puVar2 + iVar4 + 0x10e) = 0x708;
      *(undefined2 *)(puVar2 + iVar4 + 0x10c) = 0x708;
    }
    if (param_9[0x490] == '\x04') {
      if ((param_9[0x489] == '\0') || (param_9[0x48a] != '\x04')) {
        param_9[0x490] = '\0';
        param_9[0x489] = '\0';
        param_9[0x48a] = '\0';
      }
      else {
        param_9[0x490] = '\x02';
        param_9[0x48a] = '\0';
      }
    }
    if (param_9[0x490] == '\x01') {
      param_9[0x490] = '\x02';
    }
    if (param_9[0x48a] == '\x01') {
      param_9[0x48a] = '\x02';
    }
    else if (param_9[0x489] == '\x01') {
      param_9[0x489] = '\x02';
    }
    param_9[0x500] = '\0';
  }
  return;
}



// ==== 8005475c  FUN_8005475c ====

void FUN_8005475c(int param_1)

{
  if (((*(char *)(param_1 + 0x19) == '\x01') || (*(char *)(param_1 + 0x19) == '\x02')) &&
     (PTR_DAT_80433934[0x1f] != '\0')) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x488) = 2;
  }
  (*(code *)(&PTR_FUN_802d3274)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800547dc  FUN_800547dc ====

void FUN_800547dc(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  uint uVar8;
  short sVar9;
  double dVar10;
  double dVar11;
  undefined2 local_18 [4];
  longlong local_10;
  
  cVar2 = *(char *)(param_1 + 0x1a);
  if (cVar2 == '\x02') {
    FUN_80055568(param_1);
    if (*(short *)(param_1 + 0x1c) < 1) {
      iVar1 = (int)(FLOAT_80437270 * (*(float *)(param_1 + 0xd4) / *(float *)(param_1 + 0xd8)));
      local_10 = (longlong)iVar1;
      dVar10 = zz_0045204_((short)iVar1);
      fVar4 = FLOAT_80437250;
      dVar11 = (double)FLOAT_80437258;
      *(float *)(param_1 + 0xb4) =
           *(float *)(param_1 + 0x6a8) * (float)(dVar11 - dVar10) + *(float *)(param_1 + 0x6ac);
      uVar3 = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0xc4) = uVar3;
      *(undefined4 *)(param_1 + 0xc0) = uVar3;
      *(undefined4 *)(param_1 + 0x60) = uVar3;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined4 *)(param_1 + 0x58) = uVar3;
      *(undefined4 *)(param_1 + 0xb8) = uVar3;
      *(float *)(param_1 + 0xd4) = (float)((double)*(float *)(param_1 + 0xd4) - dVar11);
      if (fVar4 < *(float *)(param_1 + 0xd4)) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0x6b0);
      uVar3 = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0xc4) = uVar3;
      *(undefined4 *)(param_1 + 0xc0) = uVar3;
      *(undefined4 *)(param_1 + 0x60) = uVar3;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined4 *)(param_1 + 0x58) = uVar3;
      *(undefined4 *)(param_1 + 0xb8) = uVar3;
      *(undefined1 *)(param_1 + 0x592) = 0;
      return;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    if (*(short *)(param_1 + 0x1c) != 0x1e) {
      return;
    }
    FUN_800061a8(param_1,0x15);
    return;
  }
  if ('\x01' < cVar2) {
    if ('\x03' < cVar2) {
      return;
    }
    if (((*(char *)(param_1 + 0x3f3) == '\0') && (PTR_DAT_80433934[0x45] == '\x04')) &&
       (*(char *)(param_1 + 0x741) != '\x02')) {
      *(float *)(param_1 + 0x720) = FLOAT_8043727c;
    }
    FUN_80055568(param_1);
    if (PTR_DAT_80433934[0x15dd] != '\0') {
      if (PTR_DAT_80433934[0x1829] != '\0') {
        return;
      }
      uVar8 = zz_0010514_((int)*(char *)(param_1 + 0x3e4));
      if ((uVar8 & 0x80) != 0) {
        return;
      }
    }
    sVar9 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar9;
    if (0 < sVar9) {
      return;
    }
    *(undefined1 *)(param_1 + 0x741) = 0;
    *(undefined1 *)(param_1 + 0x743) = 1;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
    return;
  }
  if (cVar2 != '\0') {
    if (cVar2 < '\0') {
      return;
    }
    goto LAB_80054940;
  }
  *(undefined1 *)(param_1 + 0x1a) = 1;
  cVar2 = *(char *)(param_1 + 0x742);
  if (cVar2 == '\x02') {
LAB_800548d4:
    FUN_800061a8(param_1,0);
    if (*(char *)(param_1 + 0x741) == '\x02') {
      *(float *)(param_1 + 0xd4) = FLOAT_80437258;
    }
    else {
      *(float *)(param_1 + 0xd4) = FLOAT_80437264;
    }
  }
  else {
    if ('\x01' < cVar2) {
      if ((cVar2 < '\x04') &&
         ((PTR_DAT_80433934[0x1c] == '\t' || (PTR_DAT_80433934[0x1c] == '\x10')))) {
        *(float *)(param_1 + 0xb4) = FLOAT_80437260;
        uVar3 = *(undefined4 *)(param_1 + 0xb4);
        *(undefined4 *)(param_1 + 0xc4) = uVar3;
        *(undefined4 *)(param_1 + 0xc0) = uVar3;
        *(undefined4 *)(param_1 + 0x60) = uVar3;
        *(undefined4 *)(param_1 + 0x5c) = uVar3;
        *(undefined4 *)(param_1 + 0x58) = uVar3;
        zz_0055dcc_(param_1);
        if (PTR_DAT_80433934[0x1c] == '\t') {
          FUN_800108c8(param_1);
        }
        else if (PTR_DAT_80433934[0x1c] == '\x10') {
          FUN_80010924(param_1);
        }
      }
      goto LAB_800548d4;
    }
    if (cVar2 < '\x01') goto LAB_800548d4;
    *(float *)(param_1 + 0xd4) = FLOAT_80437258;
  }
  fVar5 = FLOAT_80437268;
  fVar4 = FLOAT_80437264;
  *(float *)(param_1 + 0x58) = FLOAT_80437268 * *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x60) = fVar5 * *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x5c) = fVar4 * *(float *)(param_1 + 0xb4);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0xd4);
LAB_80054940:
  iVar1 = (int)-(FLOAT_80437270 * (*(float *)(param_1 + 0xd4) / *(float *)(param_1 + 0xd8)) -
                FLOAT_80437270);
  local_10 = (longlong)iVar1;
  dVar10 = zz_0045204_((short)iVar1);
  fVar7 = FLOAT_80437274;
  fVar6 = FLOAT_80437264;
  fVar5 = FLOAT_80437258;
  fVar4 = FLOAT_80437250;
  *(float *)(param_1 + 0x58) = (float)((double)FLOAT_8043726c * dVar10 + (double)FLOAT_80437268);
  *(float *)(param_1 + 0x5c) = -(fVar7 * *(float *)(param_1 + 0x58) - fVar6);
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - fVar5;
  if (*(float *)(param_1 + 0xd4) <= fVar4) {
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    fVar5 = FLOAT_80437278;
    if (*(char *)(param_1 + 0x742) == '\x03') {
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x5a;
      *(float *)(param_1 + 0xd4) = fVar5;
      *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0xd4);
      *(float *)(param_1 + 0x6a8) = *(float *)(param_1 + 0xb8) - *(float *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x6ac) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x6b0) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined1 *)(param_1 + 0x592) = 1;
    }
    else {
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x02';
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      *(float *)(param_1 + 0x44) = fVar4;
    }
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xffd3;
    if (PTR_DAT_80433930[0x32] == '\0') {
      local_18[0] = *(undefined2 *)(param_1 + 1000);
      zz_01cb750_(-0x7fc401e0,local_18,(int)*(char *)(param_1 + 0x3ec));
    }
    if (*(char *)(param_1 + 0x741) != '\x02') {
      if (*(char *)(param_1 + 0x491) == '\x01') {
        zz_00ea2c8_(param_1,0);
      }
      else {
        zz_00ea2c8_(param_1,0xb);
      }
    }
  }
  return;
}



// ==== 80054c78  FUN_80054c78 ====

void FUN_80054c78(int param_1)

{
  if (PTR_DAT_80433934[0x45] == '\x04') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x272) = 0;
  }
  FUN_80055568(param_1);
  return;
}



// ==== 80054cbc  FUN_80054cbc ====

void FUN_80054cbc(char *param_1)

{
  FUN_80056900(param_1);
  FUN_80055568((int)param_1);
  return;
}



// ==== 80054cf0  FUN_80054cf0 ====

void FUN_80054cf0(char *param_1)

{
  if (PTR_DAT_80433934[0x52] == '\x05') {
    param_1[0x8c4] = '\0';
    param_1[0x8c5] = '\0';
    param_1[0x8c6] = '\0';
    param_1[0x8c7] = '\0';
    param_1[0x6fc] = '\0';
    param_1[0x710] = '\0';
    param_1[0x711] = '\0';
    param_1[0x712] = '\0';
    param_1[0x713] = '\0';
  }
  FUN_80069960((int)param_1);
  FUN_80056900(param_1);
  FUN_80055568((int)param_1);
  return;
}



// ==== 80054d54  FUN_80054d54 ====

void FUN_80054d54(int param_1)

{
  float fVar1;
  char cVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  short sVar7;
  double dVar8;
  double local_18;
  
  cVar2 = *(char *)(param_1 + 0x19);
  if (cVar2 == '\x02') {
    cVar2 = *(char *)(param_1 + 0x1a);
    if (cVar2 == '\x01') {
      sVar7 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar7;
      if (sVar7 == 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        zz_008aff0_(param_1);
        *(undefined1 *)(param_1 + 0x662) = 1;
        *(undefined1 *)(param_1 + 0x71b) = 0;
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
    }
    else if (cVar2 < '\x01') {
      if (-1 < cVar2) {
        *(char *)(param_1 + 0x1a) = cVar2 + '\x01';
        if (*(char *)(param_1 + 0x490) == '\x04') {
          *(undefined2 *)(param_1 + 0x1c) = 6;
        }
        else {
          *(undefined2 *)(param_1 + 0x1c) = 2;
        }
        *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_1 + 0x668);
        *(undefined1 *)(param_1 + 0x7d5) = 0xff;
        (**(code **)(param_1 + 0x4cc))(param_1);
      }
    }
    else if (cVar2 < '\x03') {
      *(undefined1 *)(param_1 + 0x18) = 3;
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x1b) = 0;
    }
  }
  else if (cVar2 < '\x02') {
    if (cVar2 == '\0') {
      *(undefined1 *)(param_1 + 0x7d5) = 0xff;
      FUN_80055568(param_1);
    }
    else if (-1 < cVar2) {
      cVar2 = *(char *)(param_1 + 0x1a);
      if (cVar2 != '\x01') {
        if ('\0' < cVar2) {
          if ('\x02' < cVar2) {
            return;
          }
          *(undefined1 *)(param_1 + 0x18) = 3;
          *(undefined1 *)(param_1 + 0x19) = 0;
          *(undefined1 *)(param_1 + 0x1a) = 0;
          *(undefined1 *)(param_1 + 0x1b) = 0;
          return;
        }
        if (cVar2 < '\0') {
          return;
        }
        *(char *)(param_1 + 0x1a) = cVar2 + '\x01';
        fVar1 = FLOAT_80437264;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        *(undefined1 *)(param_1 + 0x5e6) = 0;
        *(undefined1 *)(param_1 + 0x656) = 1;
        *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_1 + 0x668);
        *(undefined2 *)(param_1 + 0x272) = 0xffff;
        *(undefined1 *)(param_1 + 0x7d5) = 0xff;
        *(float *)(param_1 + 0x558) = fVar1;
        FUN_800061a8(param_1,0xc);
        (**(code **)(param_1 + 0x4cc))(param_1);
      }
      fVar4 = FLOAT_80437270;
      fVar1 = FLOAT_80437264;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - FLOAT_80437258;
      dVar8 = zz_0045204_((short)(int)(fVar4 * (*(float *)(param_1 + 0x558) / fVar1)));
      fVar6 = FLOAT_80437284;
      fVar5 = FLOAT_80437280;
      fVar4 = FLOAT_80437250;
      fVar1 = (float)((double)FLOAT_8043726c * dVar8 + (double)FLOAT_80437268);
      *(float *)(param_1 + 0x60) = fVar1;
      *(float *)(param_1 + 0x58) = fVar1;
      *(float *)(param_1 + 0x5c) = -(fVar6 * *(float *)(param_1 + 0x58) - fVar5);
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0xb4);
      if (*(float *)(param_1 + 0x558) <= fVar4) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        zz_008aff0_(param_1);
        *(undefined1 *)(param_1 + 0x662) = 1;
        *(undefined1 *)(param_1 + 0x71b) = 0;
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
    }
  }
  else if (cVar2 < '\x04') {
    cVar2 = *(char *)(param_1 + 0x1a);
    if (cVar2 == '\x02') {
      sVar7 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar7;
      if (sVar7 == 0) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        zz_008aff0_(param_1);
        *(undefined1 *)(param_1 + 0x662) = 1;
        *(undefined1 *)(param_1 + 0x71b) = 0;
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
    }
    else if (cVar2 < '\x02') {
      if (cVar2 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        fVar1 = FLOAT_80437288;
        *(undefined2 *)(param_1 + 0x1c) = 4;
        *(float *)(param_1 + 0xb8) =
             fVar1 / (*(float *)(param_1 + 0x668) / *(float *)(param_1 + 0xb4));
        *(undefined4 *)(param_1 + 0x400) = *(undefined4 *)(param_1 + 0x668);
        *(undefined1 *)(param_1 + 0x7d5) = 0xff;
        (**(code **)(param_1 + 0x4cc))();
      }
      else if (-1 < cVar2) {
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c)) ^ 0x80000000);
        *(float *)(param_1 + 0xb4) =
             *(float *)(param_1 + 0xb4) +
             (*(float *)(param_1 + 0xb8) - *(float *)(param_1 + 0xb4)) /
             (float)(local_18 - DOUBLE_80437290);
        uVar3 = *(undefined4 *)(param_1 + 0xb4);
        *(undefined4 *)(param_1 + 0xc4) = uVar3;
        *(undefined4 *)(param_1 + 0xc0) = uVar3;
        *(undefined4 *)(param_1 + 0x60) = uVar3;
        *(undefined4 *)(param_1 + 0x5c) = uVar3;
        *(undefined4 *)(param_1 + 0x58) = uVar3;
        sVar7 = *(short *)(param_1 + 0x1c) + -1;
        *(short *)(param_1 + 0x1c) = sVar7;
        if (sVar7 == 0) {
          zz_0176ec0_(param_1,*(undefined1 *)(param_1 + 0x88),0);
          *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
          *(undefined2 *)(param_1 + 0x1c) = 2;
        }
      }
    }
    else if (cVar2 < '\x04') {
      *(undefined1 *)(param_1 + 0x18) = 3;
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x1b) = 0;
    }
  }
  return;
}



// ==== 8005514c  FUN_8005514c ====

void FUN_8005514c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined1 *param_9)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  undefined8 uVar4;
  char local_28 [4];
  undefined2 local_24 [2];
  undefined2 local_20 [2];
  undefined2 local_1c [2];
  undefined2 local_18 [2];
  undefined2 local_14 [6];
  
  if (((PTR_DAT_80433934[0x1f] == '\0') || (param_9[0x490] != '\0')) ||
     (((int)(char)PTR_DAT_80433934[0x1f] & 1 << (int)(char)param_9[0x88]) != 0)) {
    bVar3 = false;
    if (param_9[0x490] == '\0') {
      if ((param_9[0x3e6] == '\0') || (param_9[0x37f] == '\0')) {
        if ((char)PTR_DAT_80433934[(char)param_9[0x3e4] + 0x5a] <= (char)param_9[0x491]) {
          param_9[0x3f2] = 1;
          if ((PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0xf6] == '\0') ||
             (PTR_DAT_80433930[0x32] == '\0')) {
            bVar3 = true;
          }
          else {
            param_9[0x486] = 1;
          }
        }
      }
      else {
        bVar3 = true;
      }
    }
    cVar1 = param_9[0x19];
    if (cVar1 == '\x01') {
      sVar2 = *(short *)(param_9 + 0x1c);
      *(short *)(param_9 + 0x1c) = sVar2 + -1;
      if ((short)(sVar2 + -1) < 1) {
        if (bVar3) {
          if ((param_9[0x3e6] == '\0') || (param_9[0x37f] == '\0')) {
            param_9[0x19] = param_9[0x19] + '\x01';
            *param_9 = 0;
            param_9[0x747] = 0;
            *(undefined2 *)(param_9 + 0x736) = *(undefined2 *)(*(int *)(param_9 + 0x4ac) + 4);
            param_9[0x502] = 0;
            *(undefined4 *)(param_9 + 0x504) = 0;
            *(undefined4 *)(param_9 + 0x508) = 0;
            *(undefined4 *)(param_9 + 200) = 0;
            *(undefined4 *)(param_9 + 0xcc) = 0;
          }
          else {
            zz_0041b58_((int)(char)param_9[0x3e4]);
            if (param_9[0x1e9] == '\0') {
              PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x105] =
                   PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x105] + -1;
            }
            else {
              PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x106] =
                   PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x106] + -1;
            }
            if (param_9[0x1ea] != '\0') {
              PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x107] =
                   PTR_DAT_80433934[(char)param_9[0x88] * 0x3c + 0x107] + -1;
            }
            zz_00537a8_(param_9);
          }
          PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + -1;
          PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] & ~param_9[0x3e5];
        }
        else {
          param_9[0x18] = 0;
          param_9[0x19] = 0;
          param_9[0x1a] = 0;
          param_9[0x1b] = 0;
        }
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      param_9[0x19] = cVar1 + '\x01';
      uVar4 = (**(code **)(param_9 + 0x4d0))(param_9);
      param_9[0x82] = 0;
      if (param_9[0x490] == '\0') {
        *(undefined2 *)(param_9 + 0x1c) = 0x3c;
        if (!bVar3) {
          if (param_9[0x486] == '\0') {
            if (param_9[0x500] == '\0') {
              zz_0068424_((int)(char)param_9[0x3e4],local_14,local_28);
              uVar4 = zz_00683ec_((int)param_9);
            }
            else {
              zz_00684a4_((int)(char)param_9[0x3e4],local_14,local_28);
              uVar4 = zz_00682f8_((int)param_9);
            }
          }
          else {
            local_28[0] = '\0';
            local_14[0] = 0xf07;
          }
          *(undefined2 *)(PTR_DAT_80433934 + (char)param_9[0x3e4] * 2 + 0x10) = local_14[0];
          PTR_DAT_80433934[(char)param_9[0x3e4] + 0xa0] = local_28[0];
          local_18[0] = local_14[0];
          zz_0041bf0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                      (char *)local_18,local_28[0]);
        }
      }
      else {
        *(undefined2 *)(param_9 + 0x1c) = 1;
        *(undefined2 *)(PTR_DAT_80433934 + (char)param_9[0x3e4] * 2 + 0x10) =
             *(undefined2 *)(param_9 + 0x48c);
        PTR_DAT_80433934[(char)param_9[0x3e4] + 0xa0] = param_9[0x48e];
        if (param_9[0x48a] == '\0') {
          if (param_9[0x490] == '\x04') {
            param_9[0x4a0] = 0;
            *(undefined4 *)(param_9 + 0x4a4) = 0;
          }
          if (param_9[0x4a0] == '\0') {
            local_1c[0] = *(undefined2 *)(param_9 + 0x48c);
            zz_0041bf0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                        (char *)local_1c,param_9[0x48e]);
          }
          else if (param_9[0x4a0] == '\x01') {
            local_24[0] = *(undefined2 *)(*(int *)(param_9 + 0x4a4) + 0x48c);
            local_20[0] = *(undefined2 *)(param_9 + 0x48c);
            zz_0041f18_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)(char)param_9[0x3e4],(int)*(char *)(*(int *)(param_9 + 0x4a4) + 0x3e4),
                        (char *)local_20,local_24,param_9[0x48e]);
          }
        }
      }
    }
  }
  return;
}



// ==== 80055568  FUN_80055568 ====

void FUN_80055568(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  *(undefined1 *)(param_1 + 0x578) = 2;
  zz_0055dcc_(param_1);
  zz_005568c_(param_1);
  zz_0059068_(param_1);
  uVar4 = *(undefined4 *)(param_1 + 0x20);
  uVar3 = *(undefined4 *)(param_1 + 0x24);
  uVar2 = *(undefined4 *)(param_1 + 0x28);
  (**(code **)(param_1 + 0x4bc))(param_1);
  cVar1 = *(char *)(param_1 + 0x5da);
  *(undefined1 *)(param_1 + 0x578) = 1;
  (*(code *)(&PTR_LAB_802d37a8)[*(char *)(param_1 + 0x5db)])(param_1);
  *(undefined1 *)(param_1 + 0x578) = 0;
  (*(code *)(&PTR_LAB_802d36a8)[cVar1])(param_1);
  *(undefined1 *)(param_1 + 0x578) = 2;
  (**(code **)(param_1 + 0x4c0))(param_1);
  zz_0055ee4_(param_1);
  if (((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) && (*(char *)(param_1 + 0x598) != '\0')) {
    *(undefined4 *)(param_1 + 0x20) = uVar4;
    *(undefined4 *)(param_1 + 0x24) = uVar3;
    *(undefined4 *)(param_1 + 0x28) = uVar2;
  }
  zz_005b880_(param_1);
  return;
}



// ==== 8005568c  zz_005568c_ ====

void zz_005568c_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  
  fVar3 = FLOAT_80437250;
  if ((((*(uint *)(param_1 + 0x5e0) & 3) == 0) && (FLOAT_80437250 < *(float *)(param_1 + 0x694))) &&
     (*(float *)(param_1 + 0x694) = *(float *)(param_1 + 0x694) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x694) <= fVar3)) {
    *(float *)(param_1 + 0x694) = fVar3;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined1 *)(param_1 + 0x73f) = 0;
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x690)) &&
     (*(float *)(param_1 + 0x690) = *(float *)(param_1 + 0x690) - *(float *)(param_1 + 0x768),
     *(float *)(param_1 + 0x690) < fVar3)) {
    *(float *)(param_1 + 0x690) = fVar3;
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x698)) &&
     (*(float *)(param_1 + 0x698) = *(float *)(param_1 + 0x698) - *(float *)(param_1 + 0x768),
     *(float *)(param_1 + 0x698) < fVar3)) {
    *(float *)(param_1 + 0x698) = fVar3;
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x69c)) &&
     (*(float *)(param_1 + 0x69c) = *(float *)(param_1 + 0x69c) - *(float *)(param_1 + 0x768),
     *(float *)(param_1 + 0x69c) < fVar3)) {
    *(float *)(param_1 + 0x69c) = fVar3;
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x6a0)) &&
     (*(float *)(param_1 + 0x6a0) = *(float *)(param_1 + 0x6a0) - *(float *)(param_1 + 0x768),
     *(float *)(param_1 + 0x6a0) < fVar3)) {
    *(float *)(param_1 + 0x6a0) = fVar3;
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x6a4)) &&
     (*(float *)(param_1 + 0x6a4) = *(float *)(param_1 + 0x6a4) - *(float *)(param_1 + 0x768),
     *(float *)(param_1 + 0x6a4) < fVar3)) {
    *(float *)(param_1 + 0x6a4) = fVar3;
  }
  if (*(char *)(param_1 + 0x6fc) == '\0') {
    if (*(char *)(param_1 + 0x7de) != '\0') {
      *(char *)(param_1 + 0x7de) = *(char *)(param_1 + 0x7de) + -1;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x7de) = 1;
  }
  if (*(short *)(param_1 + 0x6b8) != 0) {
    if (*(char *)(param_1 + 0x4a1) == '\0') {
      if (*(char *)(param_1 + 0x71c) == '\0') {
        *(short *)(param_1 + 0x6b8) = *(short *)(param_1 + 0x6b8) + -1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x6b8) = 0;
    }
  }
  if (*(char *)(param_1 + 0x656) != '\0') {
    *(char *)(param_1 + 0x656) = *(char *)(param_1 + 0x656) + -1;
  }
  if (*(char *)(param_1 + 0x593) != '\0') {
    *(char *)(param_1 + 0x593) = *(char *)(param_1 + 0x593) + -1;
  }
  if (*(char *)(param_1 + 0x594) != '\0') {
    *(char *)(param_1 + 0x594) = *(char *)(param_1 + 0x594) + -1;
  }
  if (*(char *)(param_1 + 0x596) != '\0') {
    *(char *)(param_1 + 0x596) = *(char *)(param_1 + 0x596) + -1;
  }
  if (*(short *)(param_1 + 0x6ba) != 0) {
    if ((*(char *)(param_1 + 0x18) == '\x01') && (*(char *)(param_1 + 0x19) == '\x02')) {
      sVar5 = *(short *)(param_1 + 0x6ba) + -1;
      iVar7 = (int)sVar5;
      *(short *)(param_1 + 0x6ba) = sVar5;
      iVar4 = iVar7 / 0x1e + (iVar7 >> 0x1f);
      if ((iVar7 == (iVar4 - (iVar4 >> 0x1f)) * 0x1e) && (1 < *(short *)(param_1 + 0x1c6))) {
        *(short *)(param_1 + 0x1c6) = *(short *)(param_1 + 0x1c6) + -1;
      }
    }
    if (*(short *)(param_1 + 0x6ba) < 1) {
      *(uint *)(param_1 + 0x8c4) = *(uint *)(param_1 + 0x8c4) & 0xfffffffb;
    }
  }
  iVar4 = 0;
  iVar7 = 2;
  do {
    if (((int)*(char *)(param_1 + 0x708) & 1 << iVar4) != 0) {
      if (((int)*(char *)(param_1 + 0x709) & 1 << iVar4) != 0) {
        *(undefined1 *)(param_1 + iVar4 + 0xa8) = 2;
      }
      cVar1 = *(char *)(param_1 + iVar4 + 0xa8);
      if (cVar1 != '\0') {
        *(char *)(param_1 + iVar4 + 0xa8) = cVar1 + -1;
      }
    }
    uVar6 = 1 << iVar4 + 1;
    if (((int)*(char *)(param_1 + 0x708) & uVar6) != 0) {
      if (((int)*(char *)(param_1 + 0x709) & uVar6) != 0) {
        *(undefined1 *)(param_1 + iVar4 + 0xa9) = 2;
      }
      cVar1 = *(char *)(param_1 + iVar4 + 0xa9);
      if (cVar1 != '\0') {
        *(char *)(param_1 + iVar4 + 0xa9) = cVar1 + -1;
      }
    }
    uVar6 = 1 << iVar4 + 2;
    if (((int)*(char *)(param_1 + 0x708) & uVar6) != 0) {
      if (((int)*(char *)(param_1 + 0x709) & uVar6) != 0) {
        *(undefined1 *)(param_1 + iVar4 + 0xaa) = 2;
      }
      cVar1 = *(char *)(param_1 + iVar4 + 0xaa);
      if (cVar1 != '\0') {
        *(char *)(param_1 + iVar4 + 0xaa) = cVar1 + -1;
      }
    }
    iVar4 = iVar4 + 3;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if ((byte)(*(byte *)(param_1 + 0x709) & *(byte *)(param_1 + 0x708) & ~*(byte *)(param_1 + 0x707))
      != 0) {
    zz_00f0104_(param_1,0,5);
  }
  cVar1 = *(char *)(param_1 + 0x661);
  if (((cVar1 == '\x03') || (cVar1 == '\x06')) || (cVar1 == '\x02')) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
      if (*(short *)(param_1 + 0x73a) == 0) {
        *(short *)(param_1 + 0x736) =
             *(short *)(param_1 + 0x736) + *(short *)(*(int *)(param_1 + 0x4ac) + 8);
        sVar5 = *(short *)(*(int *)(param_1 + 0x4ac) + 4);
        if (sVar5 < *(short *)(param_1 + 0x736)) {
          *(short *)(param_1 + 0x736) = sVar5;
        }
      }
      else {
        *(short *)(param_1 + 0x73a) = *(short *)(param_1 + 0x73a) + -1;
      }
    }
  }
  else if (*(char *)(param_1 + 0x87) == '\0') {
    if (*(short *)(param_1 + 0x73a) == 0) {
      *(short *)(param_1 + 0x736) =
           *(short *)(param_1 + 0x736) + *(short *)(*(int *)(param_1 + 0x4ac) + 8);
      sVar5 = *(short *)(*(int *)(param_1 + 0x4ac) + 4);
      if (sVar5 < *(short *)(param_1 + 0x736)) {
        *(short *)(param_1 + 0x736) = sVar5;
      }
    }
    else {
      *(short *)(param_1 + 0x73a) = *(short *)(param_1 + 0x73a) + -1;
    }
    *(undefined1 *)(param_1 + 0x747) = 0;
  }
  fVar3 = FLOAT_80437250;
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
    if ((FLOAT_80437250 < *(float *)(param_1 + 0x684)) &&
       (*(float *)(param_1 + 0x684) = *(float *)(param_1 + 0x684) - *(float *)(param_1 + 0x1dcc),
       *(float *)(param_1 + 0x684) <= fVar3)) {
      *(float *)(param_1 + 0x684) = fVar3;
      *(undefined2 *)(param_1 + 0x6c2) = *(undefined2 *)(param_1 + 0x6be);
    }
    fVar3 = FLOAT_80437250;
    if ((FLOAT_80437250 < *(float *)(param_1 + 0x688)) &&
       (*(float *)(param_1 + 0x688) = *(float *)(param_1 + 0x688) - *(float *)(param_1 + 0x1dcc),
       *(float *)(param_1 + 0x688) <= fVar3)) {
      *(float *)(param_1 + 0x688) = fVar3;
      zz_003d3e8_(param_1);
    }
    fVar3 = FLOAT_80437250;
    if ((FLOAT_80437250 < *(float *)(param_1 + 0x7d8)) &&
       (*(float *)(param_1 + 0x7d8) = *(float *)(param_1 + 0x7d8) - *(float *)(param_1 + 0x1dcc),
       *(float *)(param_1 + 0x7d8) <= fVar3)) {
      *(float *)(param_1 + 0x7d8) = fVar3;
      zz_003d444_(param_1);
    }
    fVar3 = FLOAT_80437250;
    if ((FLOAT_80437250 < *(float *)(param_1 + 0x68c)) &&
       (*(float *)(param_1 + 0x68c) = *(float *)(param_1 + 0x68c) - *(float *)(param_1 + 0x1dcc),
       *(float *)(param_1 + 0x68c) <= fVar3)) {
      *(float *)(param_1 + 0x68c) = fVar3;
      *(undefined2 *)(param_1 + 0x6c8) = 0;
      *(undefined1 *)(param_1 + 0x6ca) = 0;
    }
  }
  fVar3 = FLOAT_80437250;
  if ((FLOAT_80437250 < *(float *)(param_1 + 0x720)) &&
     (*(float *)(param_1 + 0x720) = *(float *)(param_1 + 0x720) - *(float *)(param_1 + 0x1dcc),
     *(float *)(param_1 + 0x720) <= fVar3)) {
    *(float *)(param_1 + 0x720) = fVar3;
    *(undefined2 *)(param_1 + 0x272) = 0;
  }
  iVar10 = 0;
  iVar7 = 0;
  iVar4 = param_1;
  do {
    if ((*(int *)(iVar4 + 0x440) != 0) && ('\x01' < *(char *)(*(int *)(iVar4 + 0x440) + 0x18))) {
      iVar9 = param_1 + iVar7;
      uVar6 = 7 - iVar10;
      iVar11 = iVar10;
      if (iVar10 < 7) {
        uVar12 = uVar6 >> 3;
        uVar8 = uVar6;
        if (uVar12 == 0) goto LAB_80055cc0;
        do {
          *(undefined4 *)(iVar9 + 0x440) = *(undefined4 *)(iVar9 + 0x444);
          *(undefined4 *)(iVar9 + 0x444) = *(undefined4 *)(iVar9 + 0x448);
          *(undefined4 *)(iVar9 + 0x448) = *(undefined4 *)(iVar9 + 0x44c);
          *(undefined4 *)(iVar9 + 0x44c) = *(undefined4 *)(iVar9 + 0x450);
          *(undefined4 *)(iVar9 + 0x450) = *(undefined4 *)(iVar9 + 0x454);
          *(undefined4 *)(iVar9 + 0x454) = *(undefined4 *)(iVar9 + 0x458);
          *(undefined4 *)(iVar9 + 0x458) = *(undefined4 *)(iVar9 + 0x45c);
          *(undefined4 *)(iVar9 + 0x45c) = *(undefined4 *)(iVar9 + 0x460);
          iVar9 = iVar9 + 0x20;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
        for (uVar8 = uVar6 & 7; uVar8 != 0; uVar8 = uVar8 - 1) {
LAB_80055cc0:
          *(undefined4 *)(iVar9 + 0x440) = *(undefined4 *)(iVar9 + 0x444);
          iVar9 = iVar9 + 4;
        }
        iVar11 = iVar10 + uVar6;
      }
      *(undefined4 *)(param_1 + iVar11 * 4 + 0x440) = 0;
      *(char *)(param_1 + 0x485) = *(char *)(param_1 + 0x485) + -1;
    }
    iVar10 = iVar10 + 1;
    iVar7 = iVar7 + 4;
    iVar4 = iVar4 + 4;
  } while (iVar10 < 8);
  zz_006dcc0_(param_1);
  if (((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) && (*(char *)(param_1 + 0x7d4) != '\0')) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) == 0) {
      uVar2 = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 4);
      *(undefined2 *)(param_1 + 0x738) = uVar2;
      *(undefined2 *)(param_1 + 0x736) = uVar2;
      *(undefined1 *)(param_1 + 0x747) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x6fd) = 0x26;
      *(undefined1 *)(param_1 + 0x702) = 8;
      *(undefined2 *)(param_1 + 0x282) = 0xd800;
      *(short *)(param_1 + 0x284) = *(short *)(param_1 + 0x5ae) + 0x2000;
      uVar2 = *(undefined2 *)(param_1 + 0x6b6);
      zz_005c290_(param_1);
      *(undefined2 *)(param_1 + 0x6b6) = uVar2;
    }
  }
  if (*(char *)(param_1 + 0x5da) == '\x01') {
    if (FLOAT_80437250 <= *(float *)(param_1 + 0x8c8)) {
      *(float *)(param_1 + 0x8c8) = *(float *)(param_1 + 0x8c8) + *(float *)(param_1 + 0x1dcc);
    }
  }
  else {
    *(float *)(param_1 + 0x8c8) = FLOAT_80437250;
  }
  return;
}



// ==== 80055dcc  zz_0055dcc_ ====

void zz_0055dcc_(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(byte *)(param_1 + 0x87) = (byte)(*(uint *)(param_1 + 0x5e0) >> 6) & 1;
  iVar2 = *(int *)(param_1 + 0x4b0);
  fVar1 = *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x668) = *(float *)(iVar2 + 0x4c) * fVar1;
  *(float *)(param_1 + 0x66c) = *(float *)(iVar2 + 0x44) * fVar1;
  *(float *)(param_1 + 0x670) = *(float *)(iVar2 + 0x48) * fVar1;
  *(float *)(param_1 + 0x674) = *(float *)(iVar2 + 0x54) * fVar1;
  *(float *)(param_1 + 0x770) = *(float *)(iVar2 + 0x50) * fVar1;
  *(undefined4 *)(param_1 + 0x678) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x74);
  *(undefined4 *)(param_1 + 0x67c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x78);
  *(undefined4 *)(param_1 + 0x680) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x7c);
  *(undefined4 *)(param_1 + 0x814) = *(undefined4 *)(param_1 + 0x850);
  *(undefined4 *)(param_1 + 0x818) = *(undefined4 *)(param_1 + 0x854);
  *(undefined4 *)(param_1 + 0x81c) = *(undefined4 *)(param_1 + 0x858);
  *(undefined4 *)(param_1 + 0x820) = *(undefined4 *)(param_1 + 0x85c);
  *(undefined4 *)(param_1 + 0x824) = *(undefined4 *)(param_1 + 0x860);
  *(undefined4 *)(param_1 + 0x828) = *(undefined4 *)(param_1 + 0x864);
  *(undefined4 *)(param_1 + 0x82c) = *(undefined4 *)(param_1 + 0x868);
  *(undefined4 *)(param_1 + 0x830) = *(undefined4 *)(param_1 + 0x86c);
  *(undefined4 *)(param_1 + 0x834) = *(undefined4 *)(param_1 + 0x870);
  *(undefined4 *)(param_1 + 0x838) = *(undefined4 *)(param_1 + 0x874);
  *(undefined4 *)(param_1 + 0x83c) = *(undefined4 *)(param_1 + 0x878);
  *(undefined4 *)(param_1 + 0x840) = *(undefined4 *)(param_1 + 0x87c);
  *(undefined4 *)(param_1 + 0x844) = *(undefined4 *)(param_1 + 0x880);
  *(undefined4 *)(param_1 + 0x848) = *(undefined4 *)(param_1 + 0x884);
  *(undefined4 *)(param_1 + 0x84c) = *(undefined4 *)(param_1 + 0x888);
  zz_004d08c_(param_1);
  return;
}



// ==== 80055ee4  zz_0055ee4_ ====

void zz_0055ee4_(int param_1)

{
  char cVar1;
  
  *(byte *)(param_1 + 0x87) = (byte)(*(uint *)(param_1 + 0x5e0) >> 6) & 1;
  cVar1 = *(char *)(param_1 + 0x8cc);
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0x1eb) = 0;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if (FLOAT_80437298 <= *(float *)(param_1 + 0x7fc) * *(float *)(param_1 + 0xb4)) {
      *(undefined1 *)(param_1 + 0x1eb) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x1eb) = 1;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x1eb) = 1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x20000000) == 0) {
    *(undefined1 *)(param_1 + 0x276) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x276) = 1;
  }
  if (*(char *)(param_1 + 0x7c9) != '\0') {
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
    return;
  }
  return;
}



// ==== 80055f90  zz_0055f90_ ====

void zz_0055f90_(int param_1)

{
  undefined2 uVar1;
  short sVar2;
  int iVar3;
  undefined2 local_28 [18];
  
  iVar3 = ((int)*(char *)(param_1 + 0x3ee) +
          (uint)*(byte *)(param_1 + 0x3e9) * 0x14 +
          (int)(char)(&DAT_804339e8)[*(char *)(param_1 + 0x3ec)]) * 0x12;
  if (*(char *)(param_1 + 0x490) == '\0') {
    uVar1 = *(undefined2 *)((&PTR_DAT_802f2988)[*(char *)(param_1 + 1000)] + iVar3);
    *(undefined2 *)(param_1 + 0x1c4) = uVar1;
    *(undefined2 *)(param_1 + 0x1c8) = uVar1;
    *(undefined2 *)(param_1 + 0x1c6) = uVar1;
    local_28[0] = *(undefined2 *)(param_1 + 1000);
    iVar3 = zz_0066168_((char *)local_28,(int)*(char *)(param_1 + 0x3ec));
    *(short *)(param_1 + 0x4aa) = (short)iVar3;
    if (*(char *)(param_1 + 0x3e6) != '\0') {
      *(short *)(param_1 + 0x4aa) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x4aa) ^ 0x80000000) -
                               DOUBLE_80437290) * FLOAT_8043729c);
    }
    if (*(char *)(param_1 + 0x486) != '\0') {
      *(undefined2 *)(param_1 + 0x4aa) = 0;
    }
  }
  else if (*(char *)(param_1 + 0x4a0) == '\0') {
    if (*(char *)(param_1 + 0x48a) == '\x01') {
      *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(param_1 + 0x496);
      *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x494);
      *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x494);
      sVar2 = *(short *)(param_1 + 0x1c4);
      if (sVar2 < *(short *)(param_1 + 0x1c6)) {
        *(short *)(param_1 + 0x1c8) = sVar2;
        *(short *)(param_1 + 0x1c6) = sVar2;
      }
      *(undefined2 *)(param_1 + 0x4aa) = *(undefined2 *)(param_1 + 0x498);
    }
    else {
      *(undefined2 *)(param_1 + 0x1c4) =
           *(undefined2 *)((&PTR_DAT_802f2988)[*(char *)(param_1 + 1000)] + iVar3);
      *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x494);
      *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x494);
      sVar2 = *(short *)(param_1 + 0x1c4);
      if (sVar2 < *(short *)(param_1 + 0x1c6)) {
        *(short *)(param_1 + 0x1c8) = sVar2;
        *(short *)(param_1 + 0x1c6) = sVar2;
      }
      *(undefined2 *)(param_1 + 0x4aa) = *(undefined2 *)(param_1 + 0x498);
    }
  }
  else {
    *(short *)(param_1 + 0x1c4) =
         *(short *)(param_1 + 0x496) + *(short *)(*(int *)(param_1 + 0x4a4) + 0x496);
    sVar2 = *(short *)(param_1 + 0x494) + *(short *)(*(int *)(param_1 + 0x4a4) + 0x494);
    *(short *)(param_1 + 0x1c8) = sVar2;
    *(short *)(param_1 + 0x1c6) = sVar2;
    *(undefined2 *)(param_1 + 0x4aa) = *(undefined2 *)(param_1 + 0x498);
  }
  return;
}



// ==== 8005614c  zz_005614c_ ====

void zz_005614c_(int param_1)

{
  zz_0056180_(param_1);
  FUN_800562b8(param_1);
  return;
}



// ==== 80056180  zz_0056180_ ====

void zz_0056180_(int param_1)

{
  undefined4 uVar1;
  undefined2 uVar2;
  float fVar3;
  
  fVar3 = FLOAT_80437258;
  *(float *)(param_1 + 0x5f4) = FLOAT_80437258;
  *(float *)(param_1 + 0x768) = fVar3;
  uVar2 = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 4);
  *(undefined2 *)(param_1 + 0x738) = uVar2;
  *(undefined2 *)(param_1 + 0x736) = uVar2;
  *(undefined *)(param_1 + 0x438) = PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x20];
  *(undefined *)(param_1 + 0x439) = PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x32];
  *(undefined *)(param_1 + 0x43a) = PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x3e];
  *(undefined1 *)(param_1 + 0x74a) = 0x10;
  *(undefined1 *)(param_1 + 0x74d) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0xa1);
  *(undefined1 *)(param_1 + 0x74c) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0xa2);
  zz_006826c_(param_1);
  if (*(char *)(param_1 + 0x489) == '\0') {
    if ((*(char *)(param_1 + 0x48a) == '\0') && (*(char *)(param_1 + 0x500) == '\0')) {
      *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0xb8);
      goto LAB_8005628c;
    }
  }
  if (*(float *)(param_1 + 0x400) <= FLOAT_80437250) {
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0xb8);
  }
  else {
    *(float *)(param_1 + 0xb4) =
         *(float *)(param_1 + 0x400) / *(float *)(*(int *)(param_1 + 0x4b0) + 0x4c);
    if (*(float *)(param_1 + 0xb8) < *(float *)(param_1 + 0xb4)) {
      *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb8);
    }
  }
LAB_8005628c:
  uVar1 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc4) = uVar1;
  *(undefined4 *)(param_1 + 0xc0) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  return;
}



