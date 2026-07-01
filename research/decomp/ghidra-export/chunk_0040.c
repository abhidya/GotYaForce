// ==== 80154510  FUN_80154510 ====

void FUN_80154510(int param_1)

{
  char cVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + -1;
  if (*(short *)(param_1 + 0x148) < 1) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    *(undefined2 *)(param_1 + 0x14a) = 1;
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 8;
  }
  iVar2 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    zz_015498c_(param_1);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      zz_01545f0_(param_1);
    }
    else if (-1 < cVar1) {
      zz_0154754_(param_1);
    }
  }
  else if (cVar1 < '\x04') {
    zz_0154be8_(param_1);
  }
  return;
}



// ==== 801545f0  zz_01545f0_ ====

void zz_01545f0_(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x28;
  if (*(byte *)(param_1 + 0x1d9) != 0) {
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x290);
    if (*(char *)(*(int *)(param_1 + 0x54) + 0x83) != '\0') {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    *(undefined1 *)(param_1 + 0x19) = 1;
  }
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  FUN_80083874((double)FLOAT_8043a590,param_1);
  FUN_80083ad4((double)*(float *)(&DAT_80341f54 + iVar1),param_1,
               (char)*(undefined2 *)(&DAT_80341f52 + iVar1));
  zz_00833ec_(param_1);
  zz_0083524_(param_1);
  iVar1 = zz_0083714_(param_1);
  if (iVar1 == 0) {
    iVar1 = zz_0084170_(param_1);
    if (iVar1 != 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80154754  zz_0154754_ ====

/* WARNING: Removing unreachable block (ram,0x80154970) */
/* WARNING: Removing unreachable block (ram,0x80154764) */

void zz_0154754_(int param_1)

{
  float fVar1;
  float fVar2;
  char *pcVar3;
  double dVar4;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  float afStack_30 [7];
  
  fVar2 = FLOAT_8043a58c;
  pcVar3 = *(char **)(param_1 + 0x54);
  if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
     (((int)pcVar3[0x3e5] & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
    if ((pcVar3 == (char *)0x0) || ((*pcVar3 == '\0' || ('\x01' < pcVar3[0x18])))) {
      *(undefined1 *)(param_1 + 0x19) = 3;
      *(undefined2 *)(param_1 + 0x1c) = 8;
      *(undefined2 *)(param_1 + 0x14a) = 1;
      zz_008aff0_(param_1);
    }
    else {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
      fVar1 = *(float *)(param_1 + 0x144) +
              *(float *)(&DAT_80341f60 + (uint)*(byte *)(param_1 + 0x11) * 0x28);
      *(float *)(param_1 + 0x144) = fVar1;
      if (fVar2 <= fVar1) {
        *(float *)(param_1 + 0x144) = fVar2;
        *(undefined2 *)(param_1 + 0x272) = 0;
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
        *(undefined1 *)(param_1 + 0x19) = 2;
        if (*(char *)(param_1 + 0x88) == pcVar3[0x88]) {
          *(undefined2 *)(param_1 + 0x72) = 0x8000;
        }
        else {
          *(undefined2 *)(param_1 + 0x72) = 0;
        }
        *(undefined2 *)(param_1 + 0x74) = 0;
        *(undefined2 *)(param_1 + 0x80) = 0x1c8;
      }
      local_3c = *(float *)(pcVar3 + 0x20);
      local_34 = *(undefined4 *)(pcVar3 + 0x28);
      dVar4 = (double)(FLOAT_8043a594 * *(float *)(pcVar3 + 0x668));
      local_38 = *(float *)(pcVar3 + 0x668) * FLOAT_8043a590 + *(float *)(pcVar3 + 0x24);
      if ((double)FLOAT_8043a598 <= dVar4) {
        dVar4 = (double)FLOAT_8043a598;
      }
      gnt4_PSVECSubtract_bl((float *)(pcVar3 + 0x50c),&local_3c,afStack_30);
      gnt4_PSVECNormalize_bl(afStack_30,afStack_30);
      gnt4_PSQUATScale_bl(dVar4,afStack_30,afStack_30);
      gnt4_PSVECAdd_bl(&local_3c,afStack_30,&local_48);
      fVar2 = FLOAT_8043a59c;
      *(float *)(param_1 + 0x20) =
           (local_48 - *(float *)(param_1 + 0x20)) * FLOAT_8043a59c + *(float *)(param_1 + 0x20);
      *(float *)(param_1 + 0x24) =
           (local_44 - *(float *)(param_1 + 0x24)) * fVar2 + *(float *)(param_1 + 0x24);
      *(float *)(param_1 + 0x28) =
           (local_40 - *(float *)(param_1 + 0x28)) * fVar2 + *(float *)(param_1 + 0x28);
      gnt4_PSVECSubtract_bl(&local_3c,(float *)(param_1 + 0x20),(float *)(param_1 + 0x38));
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x19) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 8;
    *(undefined2 *)(param_1 + 0x14a) = 1;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 8015498c  zz_015498c_ ====

/* WARNING: Removing unreachable block (ram,0x80154bcc) */
/* WARNING: Removing unreachable block (ram,0x8015499c) */

void zz_015498c_(int param_1)

{
  char *pcVar1;
  double dVar2;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  float afStack_24 [4];
  
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  if (*(char *)(param_1 + 0x1da) == '\0') {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
  }
  else {
    *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
    zz_00db250_(param_1,(undefined4 *)(param_1 + 0x20),2);
    zz_00f036c_(param_1,0x26);
  }
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 8;
    *(undefined2 *)(param_1 + 0x14a) = 0;
    zz_008aff0_(param_1);
  }
  else {
    pcVar1 = *(char **)(param_1 + 0x54);
    if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
       (((int)pcVar1[0x3e5] & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
      if ((pcVar1 == (char *)0x0) || ((*pcVar1 == '\0' || ('\x01' < pcVar1[0x18])))) {
        *(undefined1 *)(param_1 + 0x19) = 3;
        *(undefined2 *)(param_1 + 0x1c) = 8;
        *(undefined2 *)(param_1 + 0x14a) = 1;
        zz_008aff0_(param_1);
      }
      else {
        local_30 = *(float *)(pcVar1 + 0x20);
        local_28 = *(undefined4 *)(pcVar1 + 0x28);
        dVar2 = (double)(FLOAT_8043a594 * *(float *)(pcVar1 + 0x668));
        local_2c = *(float *)(pcVar1 + 0x668) * FLOAT_8043a590 + *(float *)(pcVar1 + 0x24);
        if ((double)FLOAT_8043a598 <= dVar2) {
          dVar2 = (double)FLOAT_8043a598;
        }
        gnt4_PSVECSubtract_bl((float *)(pcVar1 + 0x50c),&local_30,afStack_24);
        gnt4_PSVECNormalize_bl(afStack_24,afStack_24);
        gnt4_PSQUATScale_bl(dVar2,afStack_24,afStack_24);
        gnt4_PSVECAdd_bl(&local_30,afStack_24,&local_3c);
        local_48 = (local_3c - *(float *)(param_1 + 0x20)) * FLOAT_8043a5a0 +
                   *(float *)(param_1 + 0x20);
        local_44 = (local_38 - *(float *)(param_1 + 0x24)) * FLOAT_8043a5a0 +
                   *(float *)(param_1 + 0x24);
        local_40 = (local_34 - *(float *)(param_1 + 0x28)) * FLOAT_8043a5a0 +
                   *(float *)(param_1 + 0x28);
        gnt4_PSVECSubtract_bl(&local_48,&local_30,afStack_24);
        gnt4_PSVECNormalize_bl(afStack_24,afStack_24);
        gnt4_PSQUATScale_bl(dVar2,afStack_24,afStack_24);
        gnt4_PSVECAdd_bl(&local_30,afStack_24,(float *)(param_1 + 0x20));
        gnt4_PSVECSubtract_bl(&local_30,(float *)(param_1 + 0x20),(float *)(param_1 + 0x38));
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x19) = 3;
      *(undefined2 *)(param_1 + 0x1c) = 8;
      *(undefined2 *)(param_1 + 0x14a) = 1;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 80154be8  zz_0154be8_ ====

void zz_0154be8_(int param_1)

{
  float fVar1;
  short sVar2;
  uint uVar3;
  
  fVar1 = FLOAT_8043a5a8;
  sVar2 = *(short *)(param_1 + 0x14a);
  if (sVar2 == 1) {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) * FLOAT_8043a5a4;
    if (*(float *)(param_1 + 0x144) <= fVar1) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  else if ((sVar2 < 1) && (-1 < sVar2)) {
    uVar3 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x18) + 0x20;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    *(char *)(*(int *)(param_1 + 0xe0) + 0x18) = (char)uVar3;
    uVar3 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x19) + 0x20;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    *(char *)(*(int *)(param_1 + 0xe0) + 0x19) = (char)uVar3;
    uVar3 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1a) + 0x20;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    *(char *)(*(int *)(param_1 + 0xe0) + 0x1a) = (char)uVar3;
    uVar3 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1b) + 0x20;
    if (0xff < uVar3) {
      uVar3 = 0xff;
    }
    *(char *)(*(int *)(param_1 + 0xe0) + 0x1b) = (char)uVar3;
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (sVar2 < 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_00b19b4_(param_1,1,0x10);
      zz_00f036c_(param_1,0xe1);
    }
  }
  return;
}



// ==== 80154d18  FUN_80154d18 ====

void FUN_80154d18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80154d38  FUN_80154d38 ====

void FUN_80154d38(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,param_1 + 0x38,&DAT_802b0ca8);
  }
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  return;
}



// ==== 80154de8  FUN_80154de8 ====

void FUN_80154de8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80154e28  zz_0154e28_ ====

bool zz_0154e28_(int param_1)

{
  bool bVar2;
  undefined1 *puVar1;
  
  if (*(short *)(param_1 + 1000) == 0xa02) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,2);
    bVar2 = puVar1 != (undefined1 *)0x0;
    if (bVar2) {
      *puVar1 = 1;
      puVar1[0x13] = 0;
      puVar1[0x11] = 0;
      puVar1[0x10] = 0x3f;
      *(code **)(puVar1 + 0xc) = FUN_80154f40;
      *(code **)(puVar1 + 0x10c) = FUN_80155bd0;
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
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 80154f40  FUN_80154f40 ====

void FUN_80154f40(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_80341fc4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80154f90  FUN_80154f90 ====

void FUN_80154f90(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  
  fVar1 = FLOAT_8043a5b0;
  puVar3 = &DAT_80341fa0;
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x24;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + (char)(&DAT_80341fa2)[iVar4] * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fcbe05c),(float *)(param_9 + 0x20));
  dVar7 = (double)FLOAT_8043a5b0;
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar6 + (char)(&DAT_80341fa2)[iVar4] * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar6 + (char)(&DAT_80341fa2)[iVar4] * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar6 + (char)(&DAT_80341fa2)[iVar4] * 0x30 + 0x8fc);
  dVar7 = FUN_8003d964(dVar7,param_9,(float *)(param_9 + 0x20));
  *(float *)(param_9 + 0x144) = (float)((double)*(float *)(param_9 + 0x24) - dVar7);
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_80341fa3)[iVar4]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(float *)(param_9 + 0x3c) = FLOAT_8043a5b0;
    dVar7 = gnt4_PSVECSquareMag_bl((float *)(param_9 + 0x38));
    fVar1 = FLOAT_8043a5b0;
    dVar9 = (double)FLOAT_8043a5b0;
    if (dVar7 < dVar9) {
      *(float *)(param_9 + 0x38) = FLOAT_8043a5b4;
      *(float *)(param_9 + 0x3c) = fVar1;
      *(float *)(param_9 + 0x40) = fVar1;
    }
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar8 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80341fb0 + iVar4),(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined2 *)(param_9 + 0x1c) = 600;
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80341fb0 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_80341fb4 + iVar4);
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    iVar2 = zz_0006f78_(iVar6);
    zz_000726c_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                *(int *)(param_9 + 0xe0),(float *)0xa,(int)*(char *)(param_9 + 0x88),puVar3,iVar5,
                in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,0xad);
  }
  return;
}



// ==== 80155178  FUN_80155178 ====

/* WARNING: Removing unreachable block (ram,0x80155b50) */
/* WARNING: Removing unreachable block (ram,0x80155188) */

void FUN_80155178(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float **param_11,float *param_12,float *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double in_f31;
  float *local_64;
  float local_60;
  undefined4 local_5c;
  float *local_58;
  float local_54;
  undefined4 local_50;
  float *local_4c;
  float *local_48;
  undefined4 local_44;
  float afStack_40 [3];
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
  if (*(short *)(param_9 + 0x1c) < 1) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
  }
  else {
    iVar5 = zz_0083244_((float *)(param_9 + 0x20));
    if (iVar5 == 0) {
      bVar1 = *(byte *)(param_9 + 0x1d9);
      if ((((bVar1 & 0x10) == 0) && ((bVar1 & 0x20) == 0)) && ((bVar1 & 0x40) == 0)) {
        iVar7 = (uint)*(byte *)(param_9 + 0x11) * 0x24;
        FUN_80083874((double)*(float *)(&DAT_80341fbc + iVar7),param_9);
        zz_00833ec_(param_9);
        zz_0083524_(param_9);
        iVar5 = zz_0083714_(param_9);
        if (iVar5 == 0) {
          if ((*(int *)(param_9 + 200) == 0) && (iVar5 = zz_0084170_(param_9), iVar5 != 0)) {
            *(undefined1 *)(param_9 + 0x18) = 2;
            zz_008aff0_(param_9);
          }
          else {
            cVar2 = *(char *)(param_9 + 0x19);
            if (cVar2 == '\x02') {
              gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x20));
              gnt4_PSQUATScale_bl((double)FLOAT_8043a5e0,(float *)(param_9 + 0x9c),&local_34);
              gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_34,(float *)&local_58);
              param_12 = &local_34;
              iVar5 = zz_003ecb8_((float *)(param_9 + 0x20),(float *)&local_58,(float *)&local_4c,
                                  param_12);
              if (iVar5 == 3) {
                *(float *)(param_9 + 0x9c) = local_34;
                *(undefined4 *)(param_9 + 0xa0) = local_30;
                *(undefined4 *)(param_9 + 0xa4) = local_2c;
                gnt4_PSVECNormalize_bl((float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
                gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,(float *)(param_9 + 0x9c),&local_34);
                param_11 = (float **)(param_9 + 0x20);
                gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)param_11);
              }
              else {
                local_64 = *(float **)(param_9 + 0x2c);
                param_11 = &local_4c;
                param_12 = &local_34;
                local_60 = *(float *)(param_9 + 0x30) + FLOAT_8043a5e4;
                local_5c = *(undefined4 *)(param_9 + 0x34);
                param_13 = *(float **)(param_9 + 0x20);
                local_54 = *(float *)(param_9 + 0x24) + FLOAT_8043a5e4;
                local_50 = *(undefined4 *)(param_9 + 0x28);
                local_58 = param_13;
                iVar5 = zz_003ecb8_((float *)&local_64,(float *)&local_58,(float *)param_11,param_12
                                   );
                if (iVar5 == 2) {
                  *(undefined1 *)(param_9 + 0x19) = 1;
                  *(float *)(param_9 + 0x9c) = local_34;
                  *(undefined4 *)(param_9 + 0xa0) = local_30;
                  *(undefined4 *)(param_9 + 0xa4) = local_2c;
                  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
                  gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,(float *)(param_9 + 0x9c),&local_34);
                  gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)&local_64);
                  gnt4_PSVECSubtract_bl((float *)&local_64,(float *)&local_58,&local_34);
                  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_34,(float *)(param_9 + 0x20));
                  fVar3 = FLOAT_8043a5b0;
                  *(float *)(param_9 + 0x38) = FLOAT_8043a5b0;
                  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x44);
                  *(float *)(param_9 + 0x40) = fVar3;
                  param_12 = *(float **)(param_9 + 0x2c);
                  local_44 = *(undefined4 *)(param_9 + 0x34);
                  local_48 = DAT_8043625c[0xd];
                  param_11 = DAT_8043625c;
                  local_4c = param_12;
                  dVar8 = FUN_8003d964((double)(float)local_48,param_9,(float *)&local_4c);
                  *(float *)(param_9 + 0x148) = (float)dVar8;
                  *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) + FLOAT_8043a5b8;
                }
              }
            }
            else if (cVar2 < '\x02') {
              if (cVar2 == '\0') {
                gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),afStack_40);
                gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,afStack_40,afStack_40);
                gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),afStack_40,(float *)&local_58);
                param_12 = &local_34;
                iVar5 = zz_003ecb8_((float *)(param_9 + 0x20),(float *)&local_58,(float *)&local_4c,
                                    param_12);
                if (iVar5 == 2) {
                  *(undefined1 *)(param_9 + 0x19) = 1;
                  *(undefined1 *)(param_9 + 0x1a) = 0;
                  *(float *)(param_9 + 0x9c) = local_34;
                  *(undefined4 *)(param_9 + 0xa0) = local_30;
                  *(undefined4 *)(param_9 + 0xa4) = local_2c;
                  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
                  gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,(float *)(param_9 + 0x9c),&local_34);
                  gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)(param_9 + 0x20));
                  fVar3 = FLOAT_8043a5b0;
                  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x38);
                  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x3c);
                  *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x40);
                  *(float *)(param_9 + 0x38) = fVar3;
                  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x44);
                  *(float *)(param_9 + 0x40) = fVar3;
                  local_48 = DAT_8043625c[0xd];
                  param_11 = DAT_8043625c;
                  dVar8 = FUN_8003d964((double)(float)local_48,param_9,(float *)&local_4c);
                  *(float *)(param_9 + 0x148) = (float)dVar8;
                  *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) + FLOAT_8043a5b8;
                }
                else {
                  iVar5 = FUN_800374b8((float *)(param_9 + 0x20),(float *)&local_58,
                                       (float *)&local_4c);
                  if (iVar5 == 0) {
                    FUN_80083c90((double)*(float *)(&DAT_80341fb8 + iVar7),param_9,
                                 (char)*(undefined4 *)(&DAT_80341fb4 + iVar7));
                    if (*(char *)(param_9 + 0x1a) == '\0') {
                      param_11 = (float **)(param_9 + 0x9c);
                      dVar8 = FUN_8003e3f4((double)FLOAT_8043a5b8,param_9,(float *)(param_9 + 0x20),
                                           (float *)param_11);
                      in_f31 = (double)(float)(dVar8 + (double)FLOAT_8043a5c4);
                    }
                    else {
                      param_12 = *(float **)(param_9 + 0x20);
                      param_11 = &local_4c;
                      local_54 = *(float *)(param_9 + 0x24) - FLOAT_8043a5c8;
                      local_50 = *(undefined4 *)(param_9 + 0x28);
                      local_58 = param_12;
                      iVar5 = FUN_800374b8((float *)(param_9 + 0x20),(float *)&local_58,
                                           (float *)param_11);
                      if (iVar5 == 0) {
                        *(undefined1 *)(param_9 + 0x1a) = 0;
                      }
                      else {
                        in_f31 = (double)(FLOAT_8043a5c4 + (float)local_48);
                      }
                    }
                    dVar8 = (double)*(float *)(param_9 + 0x24);
                    if (dVar8 < in_f31) {
                      if ((dVar8 <= in_f31) &&
                         (*(float *)(param_9 + 0x24) = (float)(dVar8 + (double)FLOAT_8043a5cc),
                         in_f31 <= (double)*(float *)(param_9 + 0x24))) {
                        *(float *)(param_9 + 0x24) = (float)in_f31;
                      }
                    }
                    else {
                      *(float *)(param_9 + 0x24) = (float)(dVar8 - (double)FLOAT_8043a5cc);
                      if ((double)*(float *)(param_9 + 0x24) <= in_f31) {
                        *(float *)(param_9 + 0x24) = (float)in_f31;
                      }
                    }
                    iVar5 = *(int *)(param_9 + 200);
                    if (iVar5 != 0) {
                      param_13 = *(float **)(iVar5 + 100);
                      param_11 = &local_4c;
                      param_12 = &local_34;
                      local_50 = *(undefined4 *)(iVar5 + 0x6c);
                      local_54 = *(float *)(param_9 + 0x24);
                      local_58 = param_13;
                      iVar6 = zz_003ecb8_((float *)(param_9 + 0x20),(float *)&local_58,
                                          (float *)param_11,param_12);
                      if ((iVar6 != 2) && (iVar6 != 3)) {
                        param_11 = &local_4c;
                        iVar6 = FUN_800374b8((float *)(param_9 + 0x20),(float *)&local_58,
                                             (float *)param_11);
                        if (iVar6 == 0) {
                          param_3 = (double)(*(float *)(iVar5 + 0x6c) - *(float *)(param_9 + 0x28));
                          param_2 = (double)(*(float *)(iVar5 + 100) - *(float *)(param_9 + 0x20));
                          param_4 = (double)(float)(param_2 * param_2 +
                                                   (double)(float)(param_3 * param_3));
                          dVar8 = param_4;
                          if ((double)FLOAT_8043a5b0 < param_4) {
                            dVar8 = 1.0 / SQRT(param_4);
                            dVar8 = DOUBLE_8043a5d0 * dVar8 *
                                    -(param_4 * dVar8 * dVar8 - DOUBLE_8043a5d8);
                            dVar8 = DOUBLE_8043a5d0 * dVar8 *
                                    -(param_4 * dVar8 * dVar8 - DOUBLE_8043a5d8);
                            dVar8 = (double)(float)(param_4 *
                                                   DOUBLE_8043a5d0 * dVar8 *
                                                   -(param_4 * dVar8 * dVar8 - DOUBLE_8043a5d8));
                            param_2 = DOUBLE_8043a5d8;
                            param_3 = DOUBLE_8043a5d0;
                          }
                          if (dVar8 <= (double)*(float *)(&DAT_80341fc0 + iVar7)) {
                            *(undefined1 *)(param_9 + 0x19) = 4;
                            *(undefined2 *)(param_9 + 0x1e) = 4;
                            *(undefined1 *)(param_9 + 0x1cb) = 1;
                          }
                        }
                      }
                    }
                  }
                  else {
                    *(undefined1 *)(param_9 + 0x19) = 1;
                    *(undefined1 *)(param_9 + 0x1a) = 1;
                    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),afStack_40);
                    gnt4_PSQUATScale_bl((double)FLOAT_8043a5bc,afStack_40,&local_34);
                    dVar8 = (double)FLOAT_8043a5b8;
                    *(float *)(param_9 + 0x9c) = local_34;
                    *(undefined4 *)(param_9 + 0xa0) = local_30;
                    *(undefined4 *)(param_9 + 0xa4) = local_2c;
                    gnt4_PSQUATScale_bl(dVar8,&local_34,&local_34);
                    gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)(param_9 + 0x20));
                    fVar3 = FLOAT_8043a5b0;
                    param_2 = (double)FLOAT_8043a5b0;
                    param_11 = &local_4c;
                    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x38);
                    local_60 = FLOAT_8043a5c0;
                    *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x3c);
                    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x40);
                    *(float *)(param_9 + 0x38) = fVar3;
                    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x44);
                    *(float *)(param_9 + 0x40) = fVar3;
                    local_64 = local_58;
                    local_60 = local_54 + local_60;
                    local_5c = local_50;
                    param_12 = local_58;
                    iVar5 = FUN_800374b8((float *)&local_64,(float *)&local_58,(float *)param_11);
                    fVar3 = FLOAT_8043a5b8;
                    if (iVar5 != 0) {
                      *(float **)(param_9 + 0x148) = local_48;
                      *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) + fVar3;
                    }
                  }
                }
              }
              else if (-1 < cVar2) {
                gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                                 (float *)(param_9 + 0x20));
                gnt4_PSQUATScale_bl((double)FLOAT_8043a5e0,(float *)(param_9 + 0x9c),&local_34);
                gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_34,(float *)&local_58);
                iVar5 = zz_003ecb8_((float *)(param_9 + 0x20),(float *)&local_58,(float *)&local_4c,
                                    &local_34);
                if (iVar5 == 2) {
                  *(float *)(param_9 + 0x9c) = local_34;
                  *(undefined4 *)(param_9 + 0xa0) = local_30;
                  *(undefined4 *)(param_9 + 0xa4) = local_2c;
                  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
                  gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,(float *)(param_9 + 0x9c),&local_34);
                  gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)(param_9 + 0x20));
                }
                gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),afStack_40);
                gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,afStack_40,afStack_40);
                gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),afStack_40,(float *)&local_58);
                param_11 = &local_4c;
                param_12 = &local_34;
                iVar5 = zz_003ecb8_((float *)(param_9 + 0x20),(float *)&local_58,(float *)param_11,
                                    param_12);
                if (iVar5 == 3) {
                  *(undefined1 *)(param_9 + 0x19) = 2;
                  *(float *)(param_9 + 0x9c) = local_34;
                  *(undefined4 *)(param_9 + 0xa0) = local_30;
                  *(undefined4 *)(param_9 + 0xa4) = local_2c;
                  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
                  gnt4_PSQUATScale_bl((double)FLOAT_8043a5b8,(float *)(param_9 + 0x9c),&local_34);
                  param_11 = (float **)(param_9 + 0x20);
                  gnt4_PSVECAdd_bl((float *)&local_4c,&local_34,(float *)param_11);
                  fVar3 = FLOAT_8043a5bc;
                  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x14c);
                  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x150);
                  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x154);
                  *(float *)(param_9 + 0x38) = *(float *)(param_9 + 0x38) * fVar3;
                  *(float *)(param_9 + 0x40) = *(float *)(param_9 + 0x40) * fVar3;
                }
                else if (*(float *)(param_9 + 0x148) <= *(float *)(param_9 + 0x24)) {
                  *(undefined1 *)(param_9 + 0x19) = 3;
                  fVar3 = FLOAT_8043a5b0;
                  *(undefined2 *)(param_9 + 0x1e) = 4;
                  fVar4 = FLOAT_8043a5b4;
                  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x14c);
                  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x150);
                  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x154);
                  *(float *)(param_9 + 0x9c) = fVar3;
                  *(float *)(param_9 + 0xa0) = fVar4;
                  *(float *)(param_9 + 0xa4) = fVar3;
                }
              }
            }
            else if (cVar2 == '\x04') {
              if (*(short *)(param_9 + 0x1e) < 1) {
                FUN_80083ad4((double)*(float *)(&DAT_80341fb8 + iVar7),param_9,
                             (char)*(undefined4 *)(&DAT_80341fb4 + iVar7));
              }
              else {
                dVar8 = (double)FLOAT_8043a5e8;
                *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + -1;
                FUN_80083ad4(dVar8,param_9,1);
              }
              if (*(int *)(param_9 + 200) == 0) {
                iVar5 = zz_0084170_(param_9);
                if (iVar5 != 0) {
                  *(undefined1 *)(param_9 + 0x18) = 2;
                  zz_008aff0_(param_9);
                  return;
                }
              }
              else {
                iVar5 = zz_0084170_(param_9);
                if (iVar5 == 3) {
                  *(undefined1 *)(param_9 + 0x18) = 2;
                  zz_008aff0_(param_9);
                  return;
                }
              }
            }
            else if (cVar2 < '\x04') {
              param_11 = (float **)(param_9 + 0x20);
              gnt4_PSVECAdd_bl((float *)param_11,(float *)(param_9 + 0x38),(float *)param_11);
              *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + -1;
              if (*(short *)(param_9 + 0x1e) < 1) {
                *(undefined1 *)(param_9 + 0x19) = 0;
              }
            }
            fVar3 = FLOAT_8043a5b4;
            *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x1800;
            *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + fVar3;
            iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
            iVar7 = *(int *)(param_9 + 0xe0);
            dVar8 = (double)*(float *)(param_9 + 0xd4);
            zz_0008614_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,iVar7,
                        param_11,param_12,param_13,param_14,param_15,param_16);
            zz_0007c30_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),iVar7,(float *)param_11,param_12,param_13,param_14,
                        param_15,param_16);
          }
        }
        else {
          *(undefined1 *)(param_9 + 0x18) = 2;
          zz_008aff0_(param_9);
        }
      }
      else {
        *(undefined1 *)(param_9 + 0x18) = 2;
        zz_008aff0_(param_9);
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 2;
      zz_008aff0_(param_9);
    }
  }
  return;
}



// ==== 80155b74  FUN_80155b74 ====

void FUN_80155b74(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80155bb0  FUN_80155bb0 ====

void FUN_80155bb0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80155bd0  FUN_80155bd0 ====

void FUN_80155bd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80155c10  FUN_80155c10 ====

void FUN_80155c10(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1e;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80155d08;
    *(code **)(puVar1 + 0x10c) = FUN_801560fc;
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



// ==== 80155d08  FUN_80155d08 ====

void FUN_80155d08(int param_1)

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
  (*(code *)(&PTR_FUN_80342068)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80155d94  FUN_80155d94 ====

void FUN_80155d94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = DAT_80342052;
  zz_0018f88_((int *)(param_9 + 0x144),(int)PTR_DAT_80342054,(float *)(param_9 + 0x58));
  zz_0019338_((int *)(param_9 + 0x14c),DAT_80342058,(float *)(param_9 + 0x44));
  gnt4_PSQUATScale_bl((double)*(float *)(iVar1 + 0xb4),(float *)(param_9 + 0x58),
                      (float *)(param_9 + 0x58));
  *(code **)(param_9 + 0x100) = FUN_801560cc;
  uVar2 = zz_0089100_(param_9,1,1);
  iVar1 = zz_0006f78_(*(int *)(param_9 + 0x90));
  zz_000726c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              *(int *)(param_9 + 0xe0),(float *)(int)DAT_80342050,(int)*(char *)(param_9 + 0x88),
              in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(param_9 + 0xe0));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 80155e88  FUN_80155e88 ====

void FUN_80155e88(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  
  if (*(char *)(*(int *)(param_1 + 0x8c) + 0x6f2) != '\x01') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    cVar1 = *(char *)(*(int *)(param_1 + 0x8c) + 0x6f2);
    *(byte *)(param_1 + 0x19) = (byte)((byte)((uint)-(int)cVar1 >> 0x18) | cVar1 >> 7) >> 7;
  }
  sVar2 = *(short *)(param_1 + 0x1c);
  sVar3 = *(short *)(param_1 + 0x1e);
  if (sVar3 < sVar2) {
    *(short *)(param_1 + 0x1c) = sVar3;
  }
  else if (sVar2 < sVar3) {
    *(short *)(param_1 + 0x1c) = sVar2 + 1;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x44));
  zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 80155f3c  FUN_80155f3c ====

void FUN_80155f3c(int param_1)

{
  (*(code *)(&PTR_LAB_804346d0)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80155f88  FUN_80155f88 ====

void FUN_80155f88(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  undefined8 uVar4;
  
  iVar3 = *(int *)(param_9 + 0x8c);
  if (*(char *)(param_9 + 0x13) == '\0') {
    *(undefined1 *)(param_9 + 0x13) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = uRam8034205e;
    zz_0018f88_((int *)(param_9 + 0x144),iRam80342060,(float *)(param_9 + 0x58));
    uVar4 = zz_0019338_((int *)(param_9 + 0x14c),iRam80342064,(float *)(param_9 + 0x44));
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                *(int *)(param_9 + 0xe0),(float *)(int)sRam8034205c,(int)*(char *)(param_9 + 0x88),
                in_r7,in_r8,in_r9,in_r10);
  }
  else {
    sVar1 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar1;
    if (*(short *)(param_9 + 0x1e) <= sVar1) {
      *(undefined1 *)(param_9 + 0x19) = 0;
    }
    zz_0018fd8_((int *)(param_9 + 0x144),(int)*(short *)(param_9 + 0x1c),(float *)(param_9 + 0x58));
    zz_0019370_((int *)(param_9 + 0x14c),(int)*(short *)(param_9 + 0x1c),(float *)(param_9 + 0x44));
  }
  zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(param_9 + 0xe0));
  if (*(char *)(iVar3 + 0x6f2) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
  }
  return;
}



// ==== 801560ac  FUN_801560ac ====

void FUN_801560ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801560cc  FUN_801560cc ====

void FUN_801560cc(int param_1)

{
  zz_00456a0_((float *)(*(int *)(param_1 + 0x8c) + 0x934),(float *)(param_1 + 0x114),
              (float *)(param_1 + 0x58));
  return;
}



// ==== 801560fc  FUN_801560fc ====

void FUN_801560fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80156268  FUN_80156268 ====

void FUN_80156268(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar3;
  
  iVar2 = zz_0006f98_(param_9);
  uVar3 = zz_00086b8_((double)FLOAT_8043a5f0,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar2 + 0x600),*(int *)(iVar2 + 0x708),param_11,param_12,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x708),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar3 = zz_00086b8_((double)FLOAT_8043a5f0,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar2 + 0x600),*(int *)(iVar2 + 0x788),param_11,param_12,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x788),
              extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  sVar1 = *(short *)(param_9 + 1000);
  if (sVar1 == 0x806) {
    zz_0163670_(param_9,0);
    *(undefined1 *)(param_9 + 0x144) = 0;
  }
  else if (sVar1 == 0x809) {
    zz_0163670_(param_9,1);
    *(undefined1 *)(param_9 + 0x144) = 0;
    zz_008ac80_(param_9,1);
  }
  else if (sVar1 == 0x80f) {
    zz_0163670_(param_9,2);
    *(undefined1 *)(param_9 + 0x144) = 0;
  }
  return;
}



// ==== 8015633c  FUN_8015633c ====

void FUN_8015633c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x809) {
    if (*(char *)(param_1 + 0x18) == '\x01') {
      if ((*(char *)(param_1 + 0x1d9) != '\0') || (*(char *)(param_1 + 0x1db) != '\0')) {
        *(undefined2 *)(param_1 + 0x1c6) = 1;
        *(undefined1 *)(param_1 + 0x663) = 1;
        *(undefined2 *)(param_1 + 0x272) = 0xff;
        zz_00bdd9c_(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
    }
  }
  return;
}



// ==== 801563bc  FUN_801563bc ====

void FUN_801563bc(int param_1)

{
  (*(code *)(&PTR_LAB_80342670)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80156428  FUN_80156428 ====

void FUN_80156428(int param_1)

{
  (*(code *)(&PTR_FUN_804346d8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80156460  FUN_80156460 ====

void FUN_80156460(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8034267c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801564b0  FUN_801564b0 ====

void FUN_801564b0(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(undefined2 *)(param_1 + 0x54c) = 0x1e;
  *(undefined2 *)(param_1 + 0x54e) = 0x1e;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar1 = FLOAT_8043a5f0;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a5f0;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043a5f4,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 == 1) && (*(char *)(param_1 + 0x581) == '\x01')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    return;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_004beb8_((double)FLOAT_8043a5f8,param_1,0xf,4,0,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_8043a5f8,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  *(float *)(param_1 + 0x80c) = FLOAT_8043a5f0;
  return;
}



// ==== 801565cc  FUN_801565cc ====

uint FUN_801565cc(int param_1)

{
  short sVar1;
  uint uVar2;
  bool bVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043a5f4,param_1,*(short *)(param_1 + 0x54a));
  uVar2 = zz_00677b0_(param_1);
  if (uVar2 == 0) {
    uVar2 = zz_00b22f4_(param_1);
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    uVar2 = *(byte *)(param_1 + 0x540) + 1;
    *(char *)(param_1 + 0x540) = (char)uVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x809) {
      if (*(char *)(param_1 + 0x144) == '\0') {
        *(undefined1 *)(param_1 + 0x144) = 1;
        bVar3 = zz_00c4704_(param_1,1,(undefined1 *)(param_1 + 0x144));
        uVar2 = (uint)bVar3;
      }
    }
    else if (sVar1 < 0x809) {
      if ((sVar1 == 0x806) && (*(char *)(param_1 + 0x144) == '\0')) {
        bVar3 = zz_01639c0_(param_1,0);
        uVar2 = (uint)bVar3;
      }
    }
    else if ((sVar1 == 0x80f) && (*(char *)(param_1 + 0x144) == '\0')) {
      bVar3 = zz_01639c0_(param_1,1);
      uVar2 = (uint)bVar3;
    }
  }
  return uVar2;
}



// ==== 801566f0  FUN_801566f0 ====

void FUN_801566f0(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043a5f4,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 == 1) && (*(char *)(param_1 + 0x581) == '\x01')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a5fc + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    fVar1 = FLOAT_8043a5f0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a5f0;
      *(float *)(param_1 + 0x44) = fVar1;
      zz_006a474_(param_1);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801568ec  FUN_801568ec ====

void FUN_801568ec(int param_1)

{
  *(undefined1 *)(param_1 + 0x582) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  zz_00e7758_(param_1,0,0);
  zz_00e7758_(param_1,0,1);
  *(float *)(param_1 + 0x144) = FLOAT_8043a600;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x14a) = 0;
  *(undefined1 *)(param_1 + 0x14b) = 0;
  if (*(char *)(param_1 + 0x3ec) == '\x04') {
    *(float *)(param_1 + 0x154) = FLOAT_8043a604;
  }
  else {
    *(float *)(param_1 + 0x154) = FLOAT_8043a608;
  }
  *(float *)(param_1 + 0x150) = FLOAT_8043a60c;
  return;
}



// ==== 8015697c  FUN_8015697c ====

void FUN_8015697c(int param_1)

{
  uint uVar1;
  
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 5;
  *(undefined1 *)(param_1 + 0x748) = 2;
  uVar1 = zz_006ab9c_(param_1);
  if (uVar1 == 0) {
    if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
      *(byte *)(param_1 + 0x14b) = *(byte *)(param_1 + 0x582) ^ 1 | 0x80;
    }
  }
  else if ((*(uint *)(param_1 + 0x5bc) & 0x400) == 0) {
    if ((*(byte *)(param_1 + 0x14b) & 0x80) != 0) {
      *(byte *)(param_1 + 0x14b) = *(byte *)(param_1 + 0x14b) & 0x7f;
      *(undefined1 *)(param_1 + 0x582) = *(undefined1 *)(param_1 + 0x14b);
    }
  }
  else {
    zz_006a3d0_(param_1,'\x02',0,0);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
    if (*(char *)(param_1 + 0x582) == '\x01') {
      *(undefined1 *)(param_1 + 0x1b44) = 1;
      *(undefined1 *)(param_1 + 0x1b04) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x1b44) = 0;
      *(undefined1 *)(param_1 + 0x1b04) = 0;
    }
  }
  return;
}



// ==== 80156a58  zz_0156a58_ ====

/* WARNING: Removing unreachable block (ram,0x80156df4) */
/* WARNING: Removing unreachable block (ram,0x80156a68) */

void zz_0156a58_(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double in_f31;
  
  fVar1 = FLOAT_8043a60c;
  bVar3 = false;
  if (((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) || ((*(uint *)(param_1 + 0x5e0) & 2) != 0)) {
    if (*(char *)(param_1 + 0x59a) == '\x01') {
      *(undefined1 *)(param_1 + 0x59a) = 0;
      bVar3 = true;
      in_f31 = (double)FLOAT_8043a604;
      *(float *)(param_1 + 0x150) = fVar1;
    }
  }
  else if (*(char *)(param_1 + 0x5db) == '\x0e') {
    if (FLOAT_8043a600 < *(float *)(param_1 + 0x150)) {
      fVar1 = *(float *)(param_1 + 0x150) - FLOAT_8043a610;
      if (fVar1 < FLOAT_8043a600) {
        fVar1 = FLOAT_8043a600;
      }
      *(float *)(param_1 + 0x150) = fVar1;
      bVar3 = true;
      in_f31 = (double)(*(float *)(param_1 + 0x150) * *(float *)(param_1 + 0x154));
    }
    *(undefined1 *)(param_1 + 0x59a) = 1;
  }
  else if (*(char *)(param_1 + 0x5db) == '\x0f') {
    if (FLOAT_8043a60c <= *(float *)(param_1 + 0x150)) {
      *(undefined1 *)(param_1 + 0x59a) = 0;
    }
    else {
      bVar3 = true;
      *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + FLOAT_8043a610;
      if (fVar1 <= *(float *)(param_1 + 0x150)) {
        in_f31 = (double)FLOAT_8043a604;
        *(undefined1 *)(param_1 + 0x59a) = 0;
        *(float *)(param_1 + 0x150) = fVar1;
      }
      else {
        *(undefined1 *)(param_1 + 0x59a) = 1;
        in_f31 = (double)(*(float *)(param_1 + 0x150) * *(float *)(param_1 + 0x154));
      }
    }
  }
  if (bVar3) {
    iVar5 = zz_0006f98_(param_1);
    iVar7 = iVar5;
    for (iVar6 = 0; iVar6 < *(short *)(*(int *)(iVar5 + 0x600) + 0x1a); iVar6 = iVar6 + 1) {
      zz_0007cac_(in_f31,*(int *)(iVar7 + 0x788));
      iVar7 = iVar7 + 4;
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a628) * FLOAT_8043a614);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00b241c_(param_1);
  }
  *(float *)(param_1 + 0x1dc0) = FLOAT_8043a618;
  fVar2 = FLOAT_8043a60c;
  fVar1 = FLOAT_8043a600;
  if (((*(char *)(param_1 + 0x18) == '\x01') && (*(char *)(param_1 + 0x19) == '\x02')) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0)) {
    if ((*(char *)(param_1 + 0x5db) == '\x01') || ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0)) {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043a61c;
      if (fVar2 < *(float *)(param_1 + 0x144)) {
        *(float *)(param_1 + 0x144) = fVar2;
      }
      *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + 0x180;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043a61c;
      if (*(float *)(param_1 + 0x144) < fVar1) {
        *(float *)(param_1 + 0x144) = fVar1;
      }
    }
    dVar8 = zz_0045204_(*(short *)(param_1 + 0x148));
    *(float *)(param_1 + 0x1dc0) =
         *(float *)(param_1 + 0x144) * (float)((double)FLOAT_8043a620 * dVar8) + FLOAT_8043a618;
  }
  fVar1 = FLOAT_8043a624;
  if (*(char *)(param_1 + 0x14a) < '\x01') {
    if (*(char *)(param_1 + 0x582) == '\0') {
      fVar1 = *(float *)(param_1 + 0x16c4) + FLOAT_8043a624;
      if (FLOAT_8043a60c < fVar1) {
        fVar1 = FLOAT_8043a60c;
      }
      *(float *)(param_1 + 0x16cc) = fVar1;
      fVar2 = FLOAT_8043a624;
      *(float *)(param_1 + 0x16c8) = fVar1;
      fVar4 = FLOAT_8043a600;
      *(float *)(param_1 + 0x16c4) = fVar1;
      fVar2 = *(float *)(param_1 + 0x16d0) - fVar2;
      if (fVar2 < fVar4) {
        fVar2 = fVar4;
      }
      *(float *)(param_1 + 0x16d8) = fVar2;
      *(float *)(param_1 + 0x16d4) = fVar2;
      *(float *)(param_1 + 0x16d0) = fVar2;
    }
    else {
      fVar1 = *(float *)(param_1 + 0x16c4) - FLOAT_8043a624;
      if (fVar1 < FLOAT_8043a600) {
        fVar1 = FLOAT_8043a600;
      }
      *(float *)(param_1 + 0x16cc) = fVar1;
      fVar2 = FLOAT_8043a624;
      *(float *)(param_1 + 0x16c8) = fVar1;
      fVar4 = FLOAT_8043a60c;
      *(float *)(param_1 + 0x16c4) = fVar1;
      fVar2 = *(float *)(param_1 + 0x16d0) + fVar2;
      if (fVar4 < fVar2) {
        fVar2 = fVar4;
      }
      *(float *)(param_1 + 0x16d8) = fVar2;
      *(float *)(param_1 + 0x16d4) = fVar2;
      *(float *)(param_1 + 0x16d0) = fVar2;
    }
  }
  else {
    *(char *)(param_1 + 0x14a) = *(char *)(param_1 + 0x14a) + -1;
    fVar1 = *(float *)(param_1 + 0x16c4) - fVar1;
    if (fVar1 < FLOAT_8043a600) {
      fVar1 = FLOAT_8043a600;
    }
    *(float *)(param_1 + 0x16cc) = fVar1;
    fVar2 = FLOAT_8043a624;
    *(float *)(param_1 + 0x16c8) = fVar1;
    fVar4 = FLOAT_8043a600;
    *(float *)(param_1 + 0x16c4) = fVar1;
    fVar2 = *(float *)(param_1 + 0x16d0) - fVar2;
    if (fVar2 < fVar4) {
      fVar2 = fVar4;
    }
    *(float *)(param_1 + 0x16d8) = fVar2;
    *(float *)(param_1 + 0x16d4) = fVar2;
    *(float *)(param_1 + 0x16d0) = fVar2;
  }
  return;
}



// ==== 80156e44  FUN_80156e44 ====

void FUN_80156e44(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80342998)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80156e84  FUN_80156e84 ====

void FUN_80156e84(int param_1,int param_2)

{
  zz_006bda8_(param_1);
  zz_0099e70_(param_1,(&DAT_803429b8)[param_2]);
  return;
}



// ==== 80156ed4  FUN_80156ed4 ====

void FUN_80156ed4(int param_1)

{
  zz_0137540_(param_1,*(char *)(param_1 + 0x582) == '\x01');
  return;
}



// ==== 80156f08  FUN_80156f08 ====

void FUN_80156f08(int param_1,uint param_2)

{
  if ((*(char *)(param_1 + 0x582) == '\x01') && (param_2 != 3)) {
    param_2 = param_2 ^ 3;
  }
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if ((param_2 & 1) != 0) {
    zz_001ab6c_(param_1,0xe);
  }
  if ((param_2 & 2) != 0) {
    zz_001ab6c_(param_1,0xd);
  }
  return;
}



// ==== 80156fb0  FUN_80156fb0 ====

bool FUN_80156fb0(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0183730_(param_1,0,0xff);
  return bVar1;
}



// ==== 80156fd8  FUN_80156fd8 ====

void FUN_80156fd8(int param_1)

{
  FUN_800061a8(param_1,0x11);
  return;
}



// ==== 80156ffc  FUN_80156ffc ====

void FUN_80156ffc(int param_1)

{
  if (*(char *)(param_1 + 0x582) == '\x01') {
    (*(code *)(&PTR_FUN_803429c4)[*(char *)(param_1 + 0x580)])();
  }
  else {
    (*(code *)(&PTR_FUN_803429d4)[*(char *)(param_1 + 0x580)])();
  }
  return;
}



// ==== 80157068  FUN_80157068 ====

void FUN_80157068(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803429e4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801570b0  FUN_801570b0 ====

void FUN_801570b0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803429f8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801570f8  FUN_801570f8 ====

void FUN_801570f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_015809c_(param_1,0);
  return;
}



// ==== 80157128  FUN_80157128 ====

void FUN_80157128(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158688_(param_1,4);
  return;
}



// ==== 80157158  FUN_80157158 ====

void FUN_80157158(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0158a94_(param_1);
  return;
}



// ==== 80157188  FUN_80157188 ====

void FUN_80157188(int param_1)

{
  (*(code *)(&PTR_FUN_804346e0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801571c0  FUN_801571c0 ====

void FUN_801571c0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 8;
  zz_006d144_(param_1,0xc1);
  fVar3 = FLOAT_8043a630;
  fVar2 = FLOAT_8043a600;
  *(float *)(param_1 + 0x50) = FLOAT_8043a600;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(float *)(param_1 + 0x48) = fVar3;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a638;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80157294  FUN_80157294 ====

void FUN_80157294(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01572c0_(param_1);
  return;
}



// ==== 801572c0  zz_01572c0_ ====

void zz_01572c0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x14b) = 0;
  (*(code *)(&PTR_FUN_804346e8)[*(char *)(param_1 + 0x540)])();
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x14a) = 2;
  }
  return;
}



// ==== 80157320  FUN_80157320 ====

void FUN_80157320(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a600;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a638,param_1,0xf,4,0,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a600;
  return;
}



// ==== 801573d8  FUN_801573d8 ====

void FUN_801573d8(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d0dc_(param_1,0xc1,0);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_8043a60c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 == 0)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043a60c + *(float *)(param_1 + 0x1dc8);
  }
  else if (*(char *)(param_1 + 0x1cee) == '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      zz_00b22f4_(param_1);
    }
  }
  else {
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
    *(float *)(param_1 + 0x694) = FLOAT_8043a60c + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80157540  FUN_80157540 ====

void FUN_80157540(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_804346f0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80157584  FUN_80157584 ====

void FUN_80157584(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a600;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a638,param_1,0xf,3,3,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a600;
  return;
}



// ==== 8015763c  FUN_8015763c ====

void FUN_8015763c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80342a0c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015768c  FUN_8015768c ====

void FUN_8015768c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a63c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 6;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043a600;
  *(float *)(param_1 + 0x50) = FLOAT_8043a600;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a638;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a600;
  return;
}



// ==== 801577c0  FUN_801577c0 ====

void FUN_801577c0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a600;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80157868  FUN_80157868 ====

void FUN_80157868(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_006d144_(param_1,0xc0);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a63c;
  fVar1 = FLOAT_8043a600;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043a640;
    *(float *)(param_1 + 0x558) = fVar2;
    fVar2 = FLOAT_8043a630;
    *(float *)(param_1 + 0x38) = fVar1;
    *(float *)(param_1 + 0x3c) = fVar3;
    *(float *)(param_1 + 0x40) = fVar2;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80157910  FUN_80157910 ====

void FUN_80157910(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1d0_(param_1,0xc0,1,0x4000);
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x3c);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a60c;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043a600;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    dVar4 = (double)FLOAT_8043a638;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80157a38  FUN_80157a38 ====

void FUN_80157a38(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a628) * FLOAT_8043a614);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a60c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    zz_00b22f4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80157af8  zz_0157af8_ ====

void zz_0157af8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80342a20)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80157b48  FUN_80157b48 ====

void FUN_80157b48(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_8043a600;
  *(float *)(param_1 + 0x50) = FLOAT_8043a600;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 9;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043a638,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80157c34  FUN_80157c34 ====

void FUN_80157c34(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    iVar2 = 0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    do {
      zz_00c3be0_(param_1,(char)iVar2 + '%');
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    fVar1 = FLOAT_8043a600;
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a644 * dVar3);
    *(float *)(param_1 + 0x4c) = fVar1;
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a644 * dVar3);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80157d20  FUN_80157d20 ====

void FUN_80157d20(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a634,param_1);
  FUN_80067310((double)FLOAT_8043a60c,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  iVar2 = zz_00677b0_(param_1);
  fVar1 = FLOAT_8043a600;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a648 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80157df8  zz_0157df8_ ====

void zz_0157df8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80342a2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80157e48  FUN_80157e48 ====

void FUN_80157e48(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_8043a600;
  *(float *)(param_1 + 0x50) = FLOAT_8043a600;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 10;
  zz_006d144_(param_1,0xc1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043a638,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80157f24  FUN_80157f24 ====

void FUN_80157f24(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01f4260_(param_1,0);
  }
  return;
}



// ==== 80157fac  FUN_80157fac ====

void FUN_80157fac(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a634,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a648 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80158050  FUN_80158050 ====

void FUN_80158050(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0157df8_(param_1);
  return;
}



// ==== 8015807c  FUN_8015807c ====

void FUN_8015807c(int param_1)

{
  zz_0157af8_(param_1);
  return;
}



// ==== 8015809c  zz_015809c_ ====

void zz_015809c_(int param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_0159100_(param_1);
  (*(code *)(&PTR_FUN_80343c00)[*(char *)(param_1 + 0x540)])(param_1,param_2);
  return;
}



// ==== 80158114  FUN_80158114 ====

void FUN_80158114(int param_1,undefined1 param_2)

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
  fVar2 = FLOAT_8043a650;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a654;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801581f4  FUN_801581f4 ====

void FUN_801581f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    }
    *(float *)(param_1 + 0x558) = FLOAT_8043a65c;
    fVar2 = FLOAT_8043a658;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043a65c;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    if (FLOAT_8043a660 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 80158318  FUN_80158318 ====

void FUN_80158318(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a660,param_1), uVar3 != 0)) {
    fVar1 = FLOAT_8043a664;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 801583b4  FUN_801583b4 ====

/* WARNING: Removing unreachable block (ram,0x80158428) */
/* WARNING: Removing unreachable block (ram,0x801583c4) */

void FUN_801583b4(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x1dc8) = (float)(dVar4 * DOUBLE_8043a668);
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  bVar3 = fVar1 < FLOAT_8043a658;
  *(float *)(param_1 + 0x558) = fVar1;
  if (bVar3) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
  }
  return;
}



// ==== 80158444  FUN_80158444 ====

/* WARNING: Removing unreachable block (ram,0x8015866c) */
/* WARNING: Removing unreachable block (ram,0x80158454) */

void FUN_80158444(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar2 = FLOAT_8043a670;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && ('\0' < *(char *)(param_1 + 0x746))) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) *
           FLOAT_8043a678;
    }
    else {
      *(float *)(param_1 + 0x44) = FLOAT_8043a674 * *(float *)(param_1 + 0x764) * FLOAT_8043a678;
    }
    if (FLOAT_8043a660 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar3 = (double)FLOAT_8043a654;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    if ('\0' < *(char *)(param_1 + 0x1d10)) {
      zz_006d144_(param_1,0xc0);
    }
    if ((*(float *)(param_1 + 0x558) <= FLOAT_8043a658) || (*(int *)(param_1 + 0xcc) == 0)) {
      if ((*(short *)(param_1 + 1000) == 0x205) || (*(short *)(param_1 + 1000) == 0x209)) {
        zz_006ed8c_((double)FLOAT_8043a67c,param_1);
        zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
      }
      zz_004cd24_(param_1,0xf);
    }
    else {
      dVar3 = (double)FLOAT_8043a67c;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      zz_006ed8c_(dVar3,param_1);
      if (*(float *)(param_1 + 0x764) < FLOAT_8043a660) {
        zz_006ed8c_((double)FLOAT_8043a67c,param_1);
      }
      zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
      dVar3 = (double)*(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_8043a680);
      zz_004cd24_(param_1,0xf);
      *(float *)(param_1 + 0x1dc8) = (float)dVar3;
    }
    if (((*(char *)(param_1 + 0x1cef) < '\0') &&
        (((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0 || ((*(uint *)(param_1 + 0x5d4) & 1) != 0))))
       || (*(char *)(param_1 + 0x1cee) != '\0')) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 80158688  zz_0158688_ ====

void zz_0158688_(int param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_0159100_(param_1);
  (*(code *)(&PTR_FUN_80343c14)[*(char *)(param_1 + 0x540)])(param_1,param_2);
  return;
}



// ==== 80158700  FUN_80158700 ====

void FUN_80158700(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a650;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a654;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801587cc  FUN_801587cc ====

void FUN_801587cc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a65c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_8043a658;
    dVar4 = (double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (dVar4 < (double)*(float *)(param_1 + 0x760))) {
      dVar4 = (double)*(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = (float)((DOUBLE_8043a688 * dVar4) / DOUBLE_8043a690);
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 801588bc  FUN_801588bc ====

void FUN_801588bc(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a660,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043a658;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 80158958  FUN_80158958 ====

/* WARNING: Removing unreachable block (ram,0x801589e4) */
/* WARNING: Removing unreachable block (ram,0x80158968) */

void FUN_80158958(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar3 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_8043a680);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80158a00  FUN_80158a00 ====

void FUN_80158a00(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    zz_006ed8c_((double)FLOAT_8043a67c,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80158a94  zz_0158a94_ ====

void zz_0158a94_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80343c28)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80158ae4  FUN_80158ae4 ====

void FUN_80158ae4(int param_1,undefined1 param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else if (((*(short *)(param_1 + 1000) == 0x208) || (*(short *)(param_1 + 1000) == 0x20e)) &&
          (iVar5 = FUN_800667a0(param_1),
          (float)((double)CONCAT44(0x43300000,(int)(short)iVar5 ^ 0x80000000) - DOUBLE_8043a6a0) <
          FLOAT_8043a698)) {
    *(undefined1 *)(param_1 + 0x581) = 5;
    return;
  }
  fVar3 = FLOAT_8043a658;
  fVar2 = FLOAT_8043a650;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = param_2;
  *(float *)(param_1 + 0x50) = fVar3;
  *(float *)(param_1 + 0x48) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar3;
  *(float *)(param_1 + 0x44) = fVar3;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a69c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar6 = (double)FLOAT_8043a654;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80158c70  FUN_80158c70 ====

void FUN_80158c70(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a69c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a65c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80158d38  FUN_80158d38 ====

void FUN_80158d38(int param_1)

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
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a6a8 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043a6ac;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a6a8 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043a660,param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_8043a680;
    fVar1 = FLOAT_8043a670;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar4);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar4);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar4);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar4);
  }
  return;
}



// ==== 80158e60  FUN_80158e60 ====

/* WARNING: Removing unreachable block (ram,0x80158f3c) */
/* WARNING: Removing unreachable block (ram,0x80158e70) */

void FUN_80158e60(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar3 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_8043a680);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  }
  zz_0067458_((double)FLOAT_8043a6ac,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a658;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  dVar3 = DOUBLE_8043a688;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar3);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar3);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar3);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar3);
  }
  return;
}



// ==== 80158f58  FUN_80158f58 ====

void FUN_80158f58(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a658;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && ('\0' < *(char *)(param_1 + 0x746))) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
    zz_006d144_(param_1,0xc0);
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a6a8 * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
    dVar5 = (double)FLOAT_8043a654;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a6a8 * -dVar4);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar2 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar2;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043a69c,param_1);
  FUN_80067310((double)FLOAT_8043a6ac,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if ((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a6ac + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80159100  zz_0159100_ ====

void zz_0159100_(int param_1)

{
  double dVar1;
  float afStack_18 [5];
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(float *)(param_1 + 0x80c) = FLOAT_8043a658;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  dVar1 = gnt4_PSVECMag_bl(afStack_18);
  if ((double)FLOAT_8043a6b0 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80159168  zz_0159168_ ====

void zz_0159168_(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_2,2,0x18,0,7);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1f;
    puVar1[0x11] = 0;
    puVar1[0x13] = 7;
    *(code **)(puVar1 + 0xc) = FUN_80159274;
    *(code **)(puVar1 + 0x10c) = FUN_80159794;
    *(int *)(puVar1 + 0x8c) = param_2;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_2 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_2 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_2 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_2 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_2 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_2 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_2 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_2 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_2 + 0xd0);
    *(undefined4 *)(puVar1 + 0x54) = param_1;
  }
  return;
}



// ==== 80159274  FUN_80159274 ====

void FUN_80159274(int param_1)

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
  (*(code *)(&PTR_FUN_80343c88)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80159300  FUN_80159300 ====

void FUN_80159300(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  
  iVar7 = *(int *)(param_9 + 0x54);
  uVar4 = *(char *)(param_9 + 0x13) * 0x28;
  if (uVar4 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar5 = zz_0006dc8_(uVar4);
    *(int **)(param_9 + 0xdc) = piVar5;
    if (piVar5 == (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = 0;
    }
    else {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    fVar1 = FLOAT_8043a6b8;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    fVar2 = FLOAT_8043a6bc;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    fVar3 = FLOAT_8043a6c0;
    uVar6 = 1;
    *(float *)(param_9 + 0xd4) = fVar1;
    fVar1 = FLOAT_8043a6c4;
    dVar9 = (double)FLOAT_8043a6c4;
    *(float *)(param_9 + 0xd8) = fVar2;
    fVar2 = FLOAT_8043a6c8;
    *(float *)(param_9 + 0x44) = fVar3;
    fVar3 = FLOAT_8043a6cc;
    *(float *)(param_9 + 0x4c) = fVar1;
    *(float *)(param_9 + 0x38) = fVar2;
    *(float *)(param_9 + 0x3c) = fVar3;
    *(float *)(param_9 + 0x40) = fVar2;
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar7 + 0x910);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(iVar7 + 0x920);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar7 + 0x930);
    *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(iVar7 + 0xb4);
    *(code **)(param_9 + 0x100) = FUN_801596bc;
    uVar8 = zz_0089100_(param_9,1,1);
    zz_0159818_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar6,param_12
                ,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 80159434  FUN_80159434 ====

void FUN_80159434(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  bool bVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  fVar2 = FLOAT_8043a6c8;
  iVar4 = *(int *)(param_9 + 0x8c);
  local_14 = *(float *)(iVar4 + 0x910);
  local_10 = *(undefined4 *)(iVar4 + 0x920);
  local_c = *(undefined4 *)(iVar4 + 0x930);
  fVar1 = *(float *)(param_9 + 0xd8) - FLOAT_8043a6cc;
  *(float *)(param_9 + 0xd8) = fVar1;
  if (fVar2 < fVar1) {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    param_11 = (float *)(param_9 + 0x20);
    gnt4_PSVECAdd_bl(param_11,(float *)(param_9 + 0x38),param_11);
  }
  else if (*(float *)(param_9 + 0xd4) <= FLOAT_8043a6d0) {
    dVar6 = (double)FLOAT_8043a6bc;
    *(float *)(param_9 + 0xd8) = FLOAT_8043a6d4;
    zz_006c440_(dVar6,param_9,&local_14);
  }
  else {
    dVar6 = (double)FLOAT_8043a6d4;
    *(float *)(param_9 + 0xd8) = FLOAT_8043a6bc;
    zz_006c440_(dVar6,param_9,&local_14);
  }
  fVar1 = FLOAT_8043a6d8;
  if ((*(float *)(param_9 + 0x44) < FLOAT_8043a6d8) &&
     (fVar2 = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c),
     bVar5 = FLOAT_8043a6d8 < fVar2, *(float *)(param_9 + 0x44) = fVar2, bVar5)) {
    *(float *)(param_9 + 0x44) = fVar1;
  }
  dVar6 = (double)*(float *)(param_9 + 0xb4);
  if ((double)*(float *)(iVar4 + 0xb4) != dVar6) {
    *(float *)(param_9 + 0xb4) =
         (float)((double)FLOAT_8043a6dc * (double)(float)((double)*(float *)(iVar4 + 0xb4) - dVar6)
                + dVar6);
  }
  dVar7 = gnt4_PSVECSquareDistance_bl((float *)(param_9 + 0x20),&local_14);
  if ((double)FLOAT_8043a6c8 < dVar7) {
    dVar6 = 1.0 / SQRT(dVar7);
    dVar6 = DOUBLE_8043a6e0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043a6e8);
    dVar8 = DOUBLE_8043a6e0 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_8043a6e8);
    dVar6 = DOUBLE_8043a6e0 * dVar8;
    dVar7 = (double)(float)(dVar7 * dVar6 * -(dVar7 * dVar8 * dVar8 - DOUBLE_8043a6e8));
    param_3 = DOUBLE_8043a6e8;
    param_4 = DOUBLE_8043a6e0;
  }
  if ((double)FLOAT_8043a6d8 < dVar7) {
    dVar6 = (double)*(float *)(param_9 + 0xd4);
    dVar8 = (double)FLOAT_8043a6c8;
    dVar7 = (double)(float)(dVar6 - (double)FLOAT_8043a6cc);
    *(float *)(param_9 + 0xd4) = (float)(dVar6 - (double)FLOAT_8043a6cc);
    if (dVar7 <= dVar8) {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(char *)(iVar4 + 0x15a) = *(char *)(iVar4 + 0x15a) + '\x01';
  }
  zz_0159990_(param_9);
  sVar3 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar3;
  if (sVar3 < 1) {
    zz_0159818_(dVar7,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80159630  FUN_80159630 ====

void FUN_80159630(int param_1)

{
  int iVar1;
  
  iVar1 = zz_0159990_(param_1);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80159674  FUN_80159674 ====

void FUN_80159674(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801596bc  FUN_801596bc ====

void FUN_801596bc(int param_1)

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



// ==== 80159794  FUN_80159794 ====

void FUN_80159794(int param_1)

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



// ==== 80159818  zz_0159818_ ====

void zz_0159818_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined2 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & 1 << iVar5) == 0) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar5);
      piVar4 = (int *)(*(int *)(param_9 + 0x54) + iVar5 * 0x28);
      *(undefined2 *)(piVar4 + 9) = param_10;
      *(undefined1 *)((int)piVar4 + 0x26) = 0;
      iVar1 = *(int *)(param_9 + 0x24);
      piVar4[2] = *(int *)(param_9 + 0x20);
      piVar4[3] = iVar1;
      piVar4[4] = *(int *)(param_9 + 0x28);
      if (*(short *)(piVar4 + 9) == 0) {
        *(undefined2 *)((int)piVar4 + 0x22) = 0;
        *(undefined2 *)(piVar4 + 8) = 0;
        iVar1 = (*(byte *)((int)piVar4 + 0x26) & 1) * 0xc;
        iVar2 = *(int *)(&DAT_80343c74 + iVar1);
        piVar4[5] = *(int *)(&DAT_80343c70 + iVar1);
        piVar4[6] = iVar2;
        piVar4[7] = *(int *)(&DAT_80343c78 + iVar1);
        param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_803bb374,*(int *)(param_9 + iVar5 * 4 + 0xe0),0x83,
                              &DAT_80343c70 + iVar1,param_13,param_14,param_15,param_16);
      }
      else {
        *(undefined2 *)(param_9 + 0x1e) = 3;
        *(undefined1 *)((int)piVar4 + 0x27) = 0xf;
        uVar3 = zz_00055fc_();
        *(short *)(piVar4 + 8) = (short)(uVar3 << 8);
        uVar3 = zz_00055fc_();
        *(short *)((int)piVar4 + 0x22) = (short)(uVar3 << 8);
        uVar6 = zz_0018f88_(piVar4,-0x7fcbc3c0,(float *)(piVar4 + 5));
        uVar3 = zz_00055fc_();
        param_1 = zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_803bb374,*(int *)(param_9 + iVar5 * 4 + 0xe0),
                              (uVar3 & 0xff) % 3 + 0x84,uVar3 & 0xff,param_13,param_14,param_15,
                              param_16);
      }
      iVar5 = (int)*(char *)(param_9 + 0x13);
    }
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 80159990  zz_0159990_ ====

int zz_0159990_(int param_1)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar5) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar5) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar6);
      *(char *)((int)piVar2 + 0x26) = *(char *)((int)piVar2 + 0x26) + '\x01';
      uVar1 = (ushort)(1 << iVar5);
      if (*(short *)(piVar2 + 9) == 0) {
        if ('\x01' < *(char *)(param_1 + 0x18)) {
          *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~uVar1;
        }
        iVar4 = *(int *)(param_1 + 0x24);
        piVar2[2] = *(int *)(param_1 + 0x20);
        piVar2[3] = iVar4;
        piVar2[4] = *(int *)(param_1 + 0x28);
        iVar3 = (*(byte *)((int)piVar2 + 0x26) & 1) * 0xc;
        iVar4 = *(int *)(&DAT_80343c74 + iVar3);
        piVar2[5] = *(int *)(&DAT_80343c70 + iVar3);
        piVar2[6] = iVar4;
        piVar2[7] = *(int *)(&DAT_80343c78 + iVar3);
      }
      else {
        if (*(char *)((int)piVar2 + 0x27) <= *(char *)((int)piVar2 + 0x26)) {
          *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~uVar1;
        }
        piVar2[3] = (int)((float)piVar2[3] + FLOAT_8043a6f0);
        zz_0018fd8_(piVar2,(int)*(char *)((int)piVar2 + 0x26),(float *)(piVar2 + 5));
      }
    }
    iVar6 = iVar6 + 0x28;
    iVar5 = iVar5 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 80159ad0  zz_0159ad0_ ====

undefined4 zz_0159ad0_(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x701) || (*(short *)(param_1 + 1000) == 0x70c)) {
    puVar2 = zz_0088aa0_(param_1,3,8,0,2);
    if (puVar2 == (undefined1 *)0x0) {
      uVar1 = 0;
      *(undefined1 *)(param_1 + (param_3 & 0xff) + 0x158) = 0;
    }
    else {
      *puVar2 = 1;
      puVar2[0x13] = (char)param_3;
      puVar2[0x11] = (char)(param_3 >> 8);
      puVar2[0x10] = 0x52;
      *(code **)(puVar2 + 0xc) = FUN_80159c54;
      *(code **)(puVar2 + 0x10c) = FUN_8015a410;
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
      uVar1 = *(undefined4 *)(param_2 + 0x24);
      *(undefined4 *)(puVar2 + 0x20) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)(puVar2 + 0x24) = uVar1;
      *(undefined4 *)(puVar2 + 0x28) = *(undefined4 *)(param_2 + 0x28);
      *(undefined4 *)(puVar2 + 0x70) = *(undefined4 *)(param_2 + 0x70);
      *(undefined2 *)(puVar2 + 0x74) = *(undefined2 *)(param_2 + 0x74);
      *(undefined1 **)(param_2 + 0x54) = puVar2;
      *(int *)(puVar2 + 0x54) = param_2;
      zz_0083d60_((int)puVar2,param_1,0);
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80159c54  FUN_80159c54 ====

void FUN_80159c54(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80343d18)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80159cec  FUN_80159cec ====

void FUN_80159cec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar6;
  char *pcVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = *(int *)(param_9 + 0x90);
  iVar4 = *(char *)(param_9 + 0x11) * 0x38;
  iVar5 = (int)*(char *)(param_9 + 0x13);
  pcVar7 = (char *)(*(char *)(param_9 + 0x11) * 8 + -0x7fcbc368 + iVar5 * 4);
  psVar6 = (short *)(iVar4 + -0x7fcbc358 + iVar5 * 0x1c);
  iVar2 = zz_008ac80_(param_9,(int)*psVar6);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    *(undefined1 *)(param_9 + 0x84) = 0x16;
    iVar3 = (int)*(short *)(pcVar7 + 2);
    *(char *)(param_9 + 0x89) = (char)*(short *)(pcVar7 + 2);
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0,1);
    FUN_80047aa4(param_9);
    zz_006ec1c_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(psVar6 + 8),(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(psVar6 + 8);
    *(short *)(param_9 + 0x1c) = psVar6[1];
    *(char *)(param_9 + 0x1cb) = (char)psVar6[2];
    *(short *)(param_9 + 0x1c4) = psVar6[3];
    *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
    *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
    *(char *)(param_9 + 0x12) = pcVar7[1];
    iVar2 = zz_0006f98_(iVar8);
    uVar9 = zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe0),(int)*pcVar7,iVar3,iVar4,
                        iVar5,in_r9,in_r10);
    if (-1 < *(char *)(param_9 + 0x12)) {
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe4),(int)pcVar7[1],iVar3,iVar4,iVar5,
                  in_r9,in_r10);
    }
    fVar1 = FLOAT_8043a6f8;
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0xb4);
    *(float *)(param_9 + 0x150) = fVar1;
    *(undefined2 *)(param_9 + 0x15c) = 0;
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(psVar6 + 10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    if ((*(char *)(param_9 + 0x11) < '\x01') && ((*(byte *)(param_9 + 0x13) & 1) == 0)) {
      zz_00f036c_(*(int *)(param_9 + 0x90),0xab);
    }
  }
  return;
}



// ==== 80159ec4  FUN_80159ec4 ====

void FUN_80159ec4(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x19) == '\0') {
    zz_0159f1c_(param_1);
  }
  else {
    zz_015a16c_(param_1);
  }
  fVar1 = *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x150);
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  return;
}



// ==== 80159f1c  zz_0159f1c_ ====

/* WARNING: Removing unreachable block (ram,0x8015a148) */
/* WARNING: Removing unreachable block (ram,0x80159f2c) */

void zz_0159f1c_(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  float local_30;
  
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    if (*(char *)(param_1 + 0x19) != '\0') goto LAB_8015a068;
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    iVar4 = *(char *)(param_1 + 0x11) * 0x38 + -0x7fcbc358 + *(char *)(param_1 + 0x13) * 0x1c;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(iVar4 + 0x18);
    if (*(float *)(param_1 + 0x158) < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x158);
    }
    FUN_80083874((double)*(float *)(iVar4 + 0xc),param_1);
    FUN_80083ad4((double)*(float *)(iVar4 + 8),param_1,(char)*(undefined2 *)(iVar4 + 4));
    zz_00833ec_(param_1);
    zz_0083610_(param_1,(float *)(param_1 + 0x158));
    iVar4 = zz_0083714_(param_1);
    if (((iVar4 == 0) && (iVar4 = zz_0083244_((float *)(param_1 + 0x20)), iVar4 == 0)) &&
       (iVar4 = zz_0084170_(param_1), iVar4 == 0)) {
      if (*(short *)(param_1 + 0x1c) < 1) {
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined1 *)(param_1 + 0x1a) = 0;
        zz_008aff0_(param_1);
      }
      goto LAB_8015a068;
    }
  }
  fVar1 = FLOAT_8043a6fc;
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined1 *)(param_1 + 0x1a) = 1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x1e) = 0xf;
  zz_008aff0_(param_1);
LAB_8015a068:
  if (*(int *)(param_1 + 200) != 0) {
    gnt4_PSVECSubtract_bl
              ((float *)(*(int *)(param_1 + 200) + 100),(float *)(param_1 + 0x20),&local_38);
    dVar6 = (double)local_34;
    local_34 = FLOAT_8043a6fc;
    dVar5 = gnt4_PSVECMag_bl(&local_38);
    iVar4 = FUN_800452a0(-dVar6,dVar5);
    iVar3 = FUN_800452a0((double)local_38,(double)local_30);
    sVar2 = (short)iVar4 - *(short *)(param_1 + 0x70);
    if (0x400 < sVar2) {
      sVar2 = 0x400;
    }
    if (sVar2 < -0x400) {
      sVar2 = -0x400;
    }
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar2;
    sVar2 = (short)iVar3 - *(short *)(param_1 + 0x72);
    if (0x400 < sVar2) {
      sVar2 = 0x400;
    }
    if (sVar2 < -0x400) {
      sVar2 = -0x400;
    }
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar2;
  }
  fVar1 = FLOAT_8043a704;
  *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + FLOAT_8043a700;
  if (fVar1 < *(float *)(param_1 + 0x150)) {
    *(float *)(param_1 + 0x150) = fVar1;
  }
  *(undefined2 *)(param_1 + 0x15c) = 0x2000;
  return;
}



// ==== 8015a16c  zz_015a16c_ ====

void zz_015a16c_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  iVar3 = *(int *)(param_1 + 0x90);
  *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) - FLOAT_8043a700;
  iVar4 = *(char *)(param_1 + 0x11) * 0x38 + -0x7fcbc358 + *(char *)(param_1 + 0x13) * 0x1c;
  if (*(float *)(param_1 + 0x150) < FLOAT_8043a6f8) {
    *(float *)(param_1 + 0x150) = FLOAT_8043a6f8;
  }
  *(float *)(param_1 + 0xb4) =
       FLOAT_8043a700 * (*(float *)(iVar3 + 0xb4) - *(float *)(param_1 + 0xb4)) +
       *(float *)(param_1 + 0xb4);
  *(short *)(param_1 + 0x15c) = *(short *)(param_1 + 0x15c) + 0x400;
  *(ushort *)(param_1 + 0x15c) = *(ushort *)(param_1 + 0x15c) & 0x1fff;
  fVar2 = FLOAT_8043a6fc;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
    if (*(short *)(param_1 + 0x1e) < 1) {
      *(undefined1 *)(param_1 + 0x1a) = 2;
      dVar5 = (double)FLOAT_8043a70c;
      *(undefined2 *)(param_1 + 0x1e) = 0x1e;
      gnt4_PSQUATScale_bl(dVar5,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(iVar4 + 0x10),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar4 + 0x10);
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - FLOAT_8043a708;
      if (fVar2 < *(float *)(param_1 + 0x44)) {
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
      else {
        *(float *)(param_1 + 0x44) = fVar2;
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0xf;
      }
    }
  }
  else if (cVar1 < '\x04') {
    *(short *)(param_1 + 0x15c) = *(short *)(param_1 + 0x15c) + 0x400;
    *(ushort *)(param_1 + 0x15c) = *(ushort *)(param_1 + 0x15c) & 0x1fff;
    *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
    if (*(short *)(param_1 + 0x1e) < 1) {
      *(undefined1 *)(iVar3 + *(char *)(param_1 + 0x13) + 0x158) = 0;
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
    else {
      zz_0046588_((double)((float)((double)CONCAT44(0x43300000,
                                                    (int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                                  DOUBLE_8043a718) / FLOAT_8043a710),(float *)(param_1 + 0x144),
                  (float *)(iVar3 + *(char *)(param_1 + 0x13) * 0xc + 0x174),
                  (float *)(param_1 + 0x20));
    }
  }
  return;
}



// ==== 8015a3d0  FUN_8015a3d0 ====

void FUN_8015a3d0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x54);
  if (*(int *)(iVar1 + 0x54) == param_1) {
    *(int *)(iVar1 + 0x54) = iVar1;
  }
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8015a3f0  FUN_8015a3f0 ====

void FUN_8015a3f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8015a410  FUN_8015a410 ====

void FUN_8015a410(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  undefined8 uVar3;
  float afStack_38 [13];
  
  uVar3 = gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_38);
  zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x45);
  if (-1 < *(char *)(param_9 + 0x12)) {
    iVar2 = (int)*(short *)(param_9 + 0x15c);
    pfVar1 = afStack_38;
    uVar3 = zz_00457d4_('x',(float *)(param_9 + 0x114),pfVar1,*(short *)(param_9 + 0x15c));
    zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),afStack_38,(undefined *)pfVar1,iVar2,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x45);
  }
  return;
}



// ==== 8015a5b4  FUN_8015a5b4 ====

void FUN_8015a5b4(int param_1)

{
  short sVar1;
  
  zz_00c74ec_(param_1,0x21);
  zz_004f1c4_(param_1);
  *(undefined1 *)(param_1 + 0x145) = 0;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x610) {
    zz_0185850_(param_1,0,0);
    zz_0185850_(param_1,1,0);
    zz_0185850_(param_1,2,0);
  }
  else if (sVar1 == 0x61e) {
    zz_0185850_(param_1,0,1);
    zz_0185850_(param_1,1,1);
    zz_0185850_(param_1,2,1);
  }
  else if (sVar1 == 0x621) {
    zz_0185850_(param_1,0,2);
    zz_0185850_(param_1,1,2);
    zz_0185850_(param_1,2,2);
  }
  else if (sVar1 == 0x623) {
    zz_0185850_(param_1,0,3);
    zz_0185850_(param_1,1,3);
    zz_0185850_(param_1,2,3);
  }
  return;
}



// ==== 8015a718  FUN_8015a718 ====

void FUN_8015a718(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803447d8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8015a760  FUN_8015a760 ====

void FUN_8015a760(int param_1)

{
  zz_0137540_(param_1,5);
  return;
}



// ==== 8015a784  FUN_8015a784 ====

void FUN_8015a784(int param_1)

{
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float afStack_44 [3];
  float local_38;
  undefined4 local_28;
  undefined4 local_18;
  
  local_5c = *(undefined4 *)(param_1 + 0x96c);
  local_58 = *(undefined4 *)(param_1 + 0x97c);
  local_54 = *(undefined4 *)(param_1 + 0x98c);
  local_50 = *(undefined4 *)(param_1 + 0x968);
  local_4c = *(undefined4 *)(param_1 + 0x978);
  local_48 = *(undefined4 *)(param_1 + 0x988);
  gnt4_PSMTXIdentity_bl(afStack_44);
  zz_0045ef4_(afStack_44,5,&local_5c,&local_50);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x964),(float *)&DAT_803447e8,&local_68);
  local_38 = local_68;
  local_28 = local_64;
  local_18 = local_60;
  zz_00aedc0_(param_1,afStack_44,4,*(undefined1 *)(param_1 + 0x88));
  zz_00f036c_(param_1,0xb9);
  return;
}



// ==== 8015a848  FUN_8015a848 ====

void FUN_8015a848(int param_1)

{
  (*(code *)(&PTR_FUN_803447f4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8015a884  FUN_8015a884 ====

void FUN_8015a884(int param_1)

{
  (*(code *)(&PTR_FUN_80344804)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015a8c0  FUN_8015a8c0 ====

void FUN_8015a8c0(int param_1)

{
  (*(code *)(&PTR_FUN_804346f8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015a8f8  FUN_8015a8f8 ====

void FUN_8015a8f8(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar2 = FLOAT_8043a720;
  *(float *)(param_1 + 0x50) = FLOAT_8043a720;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043a724;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a72c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8015aa24  FUN_8015aa24 ====

void FUN_8015aa24(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  int unaff_r30;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    fVar2 = FLOAT_8043a734;
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(float *)(param_1 + 0x694) = fVar2 + *(float *)(param_1 + 0x1dc8);
      goto LAB_8015abd8;
    }
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x610) {
      zz_00c3be0_(param_1,0x35);
    }
    else if (sVar1 == 0x61e) {
      zz_00c3be0_(param_1,0x55);
    }
    else if (sVar1 == 0x621) {
      zz_00c3be0_(param_1,0x56);
    }
    else if (sVar1 == 0x623) {
      zz_00c3be0_(param_1,0x57);
    }
  }
  if ((*(char *)(param_1 + 0x1d10) != '\0') &&
     (zz_006d144_(param_1,0xc1), (*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_8043a738,param_1,*(short *)(param_1 + 0x5ae));
  unaff_r30 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    return;
  }
LAB_8015abd8:
  fVar2 = FLOAT_8043a720;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  if ((unaff_r30 == 0) || ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006a5a4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8015ac38  FUN_8015ac38 ====

void FUN_8015ac38(int param_1)

{
  (*(code *)(&PTR_FUN_80344818)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015ac74  FUN_8015ac74 ====

void FUN_8015ac74(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8015aca8  FUN_8015aca8 ====

void FUN_8015aca8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8015acdc  FUN_8015acdc ====

void FUN_8015acdc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0178394_(param_1);
  return;
}



// ==== 8015ad10  FUN_8015ad10 ====

void FUN_8015ad10(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x610) {
    zz_015ad5c_(param_1);
  }
  else if (sVar1 == 0x621) {
    zz_015ad84_(param_1);
  }
  else if (sVar1 == 0x623) {
    zz_015adac_(param_1);
  }
  return;
}



// ==== 8015ad5c  zz_015ad5c_ ====

void zz_015ad5c_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015ad84  zz_015ad84_ ====

void zz_015ad84_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015adac  zz_015adac_ ====

void zz_015adac_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015add4  FUN_8015add4 ====

void FUN_8015add4(int param_1)

{
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 8;
  (*(code *)(&PTR_FUN_8034489c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015ae1c  FUN_8015ae1c ====

void FUN_8015ae1c(int param_1)

{
  (*(code *)(&PTR_FUN_803448b0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015ae58  FUN_8015ae58 ====

void FUN_8015ae58(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043a74c;
  *(float *)(param_1 + 0x558) = FLOAT_8043a748;
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a720;
  *(float *)(param_1 + 0x50) = FLOAT_8043a720;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a72c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8015af70  FUN_8015af70 ====

void FUN_8015af70(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  if (*(float *)(param_1 + 0x760) < FLOAT_8043a750) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a754,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar2 = FLOAT_8043a720;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6eb) = 4;
    *(undefined1 *)(param_1 + 0x6ec) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
    *(undefined2 *)(param_1 + 0x54e) = 0x14;
  }
  return;
}



// ==== 8015b0b4  FUN_8015b0b4 ====

void FUN_8015b0b4(int param_1)

{
  uint uVar1;
  char cVar3;
  short sVar2;
  double dVar4;
  
  zz_00f0104_(param_1,0x17,2);
  if (FLOAT_8043a720 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (*(short *)(param_1 + 1000) == 0x61e) {
      uVar1 = *(uint *)(param_1 + 0x5b4) & 0x400;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0x5b4) & 0x200;
    }
    if ((uVar1 != 0) && (*(short *)(param_1 + 0x54c) < 2)) {
      *(undefined2 *)(param_1 + 0x54c) = 2;
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  zz_004cd24_(param_1,0xf);
  if (('\0' < *(char *)(param_1 + 0x1d10)) &&
     (zz_006d144_(param_1,0xc0), (*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc0,1);
  }
  if (*(float *)(param_1 + 0x760) < FLOAT_8043a750) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a754,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    cVar3 = *(char *)(param_1 + 0x6eb) + -1;
    *(char *)(param_1 + 0x6eb) = cVar3;
    if (cVar3 < '\x01') {
      *(undefined1 *)(param_1 + 0x6eb) = 4;
      *(byte *)(param_1 + 0x6ec) = *(byte *)(param_1 + 0x6ec) ^ 1;
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x610) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x36);
      }
      else if (sVar2 == 0x621) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x53);
      }
      else if (sVar2 == 0x623) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x55);
      }
    }
    sVar2 = *(short *)(param_1 + 0x54c) + -1;
    *(short *)(param_1 + 0x54c) = sVar2;
    if (sVar2 < 1) {
      dVar4 = (double)FLOAT_8043a72c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      cVar3 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar3 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar3,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8015b2ec  FUN_8015b2ec ====

void FUN_8015b2ec(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043a738,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
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
    *(float *)(param_1 + 0x694) = FLOAT_8043a724 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8015b55c  FUN_8015b55c ====

void FUN_8015b55c(int param_1)

{
  int iVar1;
  
  zz_00c74ec_(param_1,0x22);
  zz_00c74ec_(param_1,0x23);
  zz_004f1c4_(param_1);
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    zz_00b2190_(param_1,2);
  }
  return;
}



// ==== 8015b5c0  FUN_8015b5c0 ====

void FUN_8015b5c0(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d520_(param_1,(float *)&DAT_80345bb8);
  dVar2 = DOUBLE_8043a760;
  fVar1 = FLOAT_8043a758;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x1922) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1922) ^ 0x80000000) -
                             DOUBLE_8043a760) * FLOAT_8043a758);
    *(short *)(param_1 + 0x1926) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1926) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1968) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1968) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1974) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1974) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 8015b6e8  FUN_8015b6e8 ====

void FUN_8015b6e8(char *param_1)

{
  if (*(short *)(param_1 + 1000) == 0x611) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
      zz_00f036c_((int)param_1,0xb2);
      zz_006a8c0_(param_1,0x610);
      zz_005f00c_((int)param_1);
      zz_017a608_((int)param_1);
    }
  }
  else if ((*(short *)(param_1 + 1000) == 0x622) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0))
  {
    zz_00f036c_((int)param_1,0xb2);
    zz_006a8c0_(param_1,0x621);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}



// ==== 8015b7a0  FUN_8015b7a0 ====

void FUN_8015b7a0(int param_1)

{
  (*(code *)(&PTR_FUN_80345be8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8015b7dc  FUN_8015b7dc ====

void FUN_8015b7dc(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_015b814_(param_1);
  return;
}



// ==== 8015b814  zz_015b814_ ====

void zz_015b814_(int param_1)

{
  zz_0177634_(param_1);
  return;
}



// ==== 8015b83c  FUN_8015b83c ====

void FUN_8015b83c(int param_1)

{
  short sVar1;
  int iVar2;
  
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x611) {
      zz_0082824_(param_1,0x30);
      zz_0082824_(param_1,0x31);
    }
    else if (sVar1 == 0x61f) {
      zz_0082824_(param_1,0x57);
      zz_0082824_(param_1,0x58);
    }
    else if (sVar1 == 0x622) {
      zz_0082824_(param_1,0x59);
      zz_0082824_(param_1,0x5a);
    }
    else if (sVar1 == 0x625) {
      zz_0082824_(param_1,0x5b);
      zz_0082824_(param_1,0x5c);
    }
    *(undefined1 *)(param_1 + 0x6ea) = 4;
  }
  return;
}



// ==== 8015b914  FUN_8015b914 ====

undefined4 FUN_8015b914(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_006dbe0_(param_1,0,1,0);
  if ((iVar1 == 0) || (*(char *)(param_1 + 0x6ef) < '\x01')) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x8444;
  }
  return uVar2;
}



// ==== 8015b970  FUN_8015b970 ====

undefined4 FUN_8015b970(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  float local_18;
  undefined4 local_14;
  float local_10;
  
  uVar2 = zz_006eae0_(param_1,(short *)(param_1 + 0x1922),(short *)(param_1 + 0x1926),3);
  if (uVar2 == 0) {
    uVar5 = 0;
  }
  else {
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_18 = *(float *)(param_1 + 0xb48);
      local_14 = *(undefined4 *)(param_1 + 0xb58);
      local_10 = *(float *)(param_1 + 0xb68);
      iVar3 = FUN_800452a0(-(double)local_18,-(double)local_10);
      local_18 = *(float *)(param_1 + 0xd60);
      local_14 = *(undefined4 *)(param_1 + 0xd70);
      local_10 = *(float *)(param_1 + 0xd80);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_18,&local_18);
      iVar4 = FUN_800452a0((double)local_18,(double)local_10);
      sVar1 = (short)iVar4 - (short)iVar3;
      if (0 < sVar1) {
        sVar1 = 0;
      }
      if (sVar1 < -0x2000) {
        sVar1 = -0x2000;
      }
      *(short *)(param_1 + 0x1968) = sVar1;
      local_18 = *(float *)(param_1 + 0xdc0);
      local_14 = *(undefined4 *)(param_1 + 0xdd0);
      local_10 = *(float *)(param_1 + 0xde0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_18,&local_18);
      iVar4 = FUN_800452a0((double)local_18,(double)local_10);
      sVar1 = (short)iVar4 - (short)iVar3;
      if (sVar1 < 0) {
        sVar1 = 0;
      }
      if (0x2000 < sVar1) {
        sVar1 = 0x2000;
      }
      *(short *)(param_1 + 0x1974) = sVar1;
    }
    uVar5 = 0x8444;
  }
  return uVar5;
}



// ==== 8015bab0  FUN_8015bab0 ====

void FUN_8015bab0(char *param_1)

{
  param_1[0x580] = '\x03';
  param_1[0x581] = '\0';
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    param_1[0x581] = '\x03';
  }
  zz_00f036c_((int)param_1,0xb2);
  if (*(short *)(param_1 + 1000) == 0x611) {
    zz_006a8c0_(param_1,0x610);
  }
  else if (*(short *)(param_1 + 1000) == 0x622) {
    zz_006a8c0_(param_1,0x621);
  }
  zz_017a608_((int)param_1);
  return;
}



// ==== 8015bb44  FUN_8015bb44 ====

void FUN_8015bb44(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x611) {
    zz_015bb90_(param_1);
  }
  else if (sVar1 == 0x622) {
    zz_015bbd0_(param_1);
  }
  else if (sVar1 == 0x625) {
    zz_015bc10_(param_1);
  }
  return;
}



// ==== 8015bb90  zz_015bb90_ ====

void zz_015bb90_(int param_1)

{
  *(short *)(param_1 + 0x1922) = *(short *)(param_1 + 0x1922) >> 1;
  *(short *)(param_1 + 0x1926) = *(short *)(param_1 + 0x1926) >> 1;
  zz_017a374_(param_1);
  return;
}



// ==== 8015bbd0  zz_015bbd0_ ====

void zz_015bbd0_(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_017a374_(param_1);
  return;
}



// ==== 8015bc10  zz_015bc10_ ====

void zz_015bc10_(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_017a374_(param_1);
  return;
}



// ==== 8015bc50  FUN_8015bc50 ====

void FUN_8015bc50(int param_1)

{
  *(short *)(param_1 + 0x1922) = *(short *)(param_1 + 0x1922) >> 1;
  *(short *)(param_1 + 0x1926) = *(short *)(param_1 + 0x1926) >> 1;
  zz_015bc88_(param_1);
  return;
}



// ==== 8015bc88  zz_015bc88_ ====

void zz_015bc88_(int param_1)

{
  zz_0177a3c_(param_1);
  return;
}



// ==== 8015bcb0  FUN_8015bcb0 ====

void FUN_8015bcb0(int param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x611) {
    zz_0084600_(param_1,9);
    zz_0084600_(param_1,10);
  }
  else if (sVar1 == 0x61f) {
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 != 0) {
      zz_0084600_(param_1,0x11);
      zz_0084600_(param_1,0x12);
    }
  }
  else if (sVar1 == 0x622) {
    zz_0084600_(param_1,0x13);
    zz_0084600_(param_1,0x14);
  }
  else if (sVar1 == 0x625) {
    zz_0084600_(param_1,0x15);
    zz_0084600_(param_1,0x16);
  }
  return;
}



// ==== 8015beb0  FUN_8015beb0 ====

void FUN_8015beb0(int param_1)

{
  short sVar1;
  
  zz_00c74ec_(param_1,0x24);
  zz_004f1c4_(param_1);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x612) {
    zz_0186528_(param_1,0);
  }
  else if (sVar1 == 0x620) {
    zz_0186528_(param_1,1);
  }
  else if (sVar1 == 0x624) {
    zz_0186528_(param_1,2);
  }
  else if (sVar1 == 0x626) {
    zz_0186528_(param_1,3);
  }
  *(undefined1 *)(param_1 + 0x144) = 0;
  return;
}



