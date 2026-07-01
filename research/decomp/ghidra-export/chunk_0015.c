// ==== 80097e54  zz_0097e54_ ====

int zz_0097e54_(byte *param_1,short *param_2,int *param_3)

{
  int iVar1;
  byte *pbVar2;
  short sVar3;
  int iVar4;
  byte local_18;
  byte local_17;
  int local_14;
  
  iVar4 = 0;
  if (param_3 == (int *)0x0) {
    param_3 = &local_14;
  }
  *param_3 = 1;
  do {
    if (*param_1 == 0) {
      *param_2 = 0x1001;
      return iVar4 + 1;
    }
    iVar1 = zz_0098044_(*param_1);
    if ((iVar1 == 0) || (*param_1 == 0x7e)) {
      local_18 = *param_1;
      local_17 = param_1[1];
      param_1 = param_1 + 2;
      iVar1 = gnt4_strncmp((char *)&local_18,&DAT_80437da8,2);
      if (iVar1 == 0) {
        *param_2 = -2;
      }
      else {
        sVar3 = 0;
        *param_2 = 0;
        pbVar2 = DAT_804362f8;
        while( true ) {
          if (*pbVar2 == 0) break;
          if (local_18 == *pbVar2) {
            if (local_17 == pbVar2[1]) {
              *param_2 = sVar3;
              break;
            }
          }
          pbVar2 = pbVar2 + 2;
          sVar3 = sVar3 + 1;
        }
      }
    }
    else {
      if (*param_1 == 10) {
        *param_2 = 0x1000;
        *param_3 = *param_3 + 1;
      }
      else {
        *param_2 = -2;
      }
      param_1 = param_1 + 1;
    }
    param_2 = param_2 + 1;
    iVar4 = iVar4 + 1;
  } while( true );
}



// ==== 80097fbc  zz_0097fbc_ ====

int zz_0097fbc_(short param_1)

{
  int iVar1;
  short *psVar2;
  short *psVar3;
  short sVar4;
  short sVar5;
  byte local_8;
  
  local_8 = (byte)((ushort)param_1 >> 8);
  iVar1 = zz_0098044_(local_8);
  if (iVar1 == 0) {
    sVar4 = 0;
    psVar2 = DAT_804362f8;
    for (psVar3 = DAT_804362f8;
        (sVar5 = -2, *(char *)psVar2 != '\0' && (sVar5 = sVar4, param_1 != *psVar3));
        psVar3 = psVar3 + 1) {
      psVar2 = psVar2 + 1;
      sVar4 = sVar4 + 1;
    }
  }
  else {
    sVar5 = -2;
  }
  return (int)sVar5;
}



// ==== 80098044  zz_0098044_ ====

undefined4 zz_0098044_(byte param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((param_1 < 0x80) || (0x9f < param_1)) {
    if (0xdf < param_1) {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80098084  zz_0098084_ ====

void zz_0098084_(int param_1,int param_2,byte *param_3)

{
  bool bVar1;
  int iVar2;
  void *__src;
  short *psVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  void *pvVar7;
  int iVar8;
  void *pvVar9;
  short local_58 [28];
  
  psVar3 = local_58;
  bVar1 = false;
  iVar6 = **(int **)(*(int *)(*(int *)(*(int *)(**(int **)(**(int **)(param_1 + 0x10) + param_2 * 4)
                                               + 0x10) + 8) + 8) + 0x4c);
  zz_0097d04_(param_3,psVar3);
  iVar5 = 0;
  pvVar9 = (void *)(iVar6 + param_2 * 0xd80);
  pvVar4 = pvVar9;
  do {
    if ((0xb < iVar5) || (bVar1)) {
      pvVar9 = (void *)((int)pvVar9 + iVar5 * 0x60);
      for (; iVar5 < 0xc; iVar5 = iVar5 + 1) {
        iVar6 = 0;
        pvVar4 = pvVar9;
        do {
          gnt4_memset(pvVar4,0,0x60);
          iVar6 = iVar6 + 1;
          pvVar4 = (void *)((int)pvVar4 + 0x480);
        } while (iVar6 < 3);
        pvVar9 = (void *)((int)pvVar9 + 0x60);
      }
      return;
    }
    iVar6 = (int)*psVar3;
    psVar3 = psVar3 + 1;
    if (iVar6 == -1) {
      bVar1 = true;
LAB_80098110:
      iVar6 = 0;
      pvVar7 = pvVar4;
      do {
        gnt4_memset(pvVar7,0,0x60);
        iVar6 = iVar6 + 1;
        pvVar7 = (void *)((int)pvVar7 + 0x480);
      } while (iVar6 < 3);
    }
    else {
      if ((iVar6 < -1) && (-3 < iVar6)) goto LAB_80098110;
      iVar8 = 0;
      iVar2 = iVar6 / 10 + (iVar6 >> 0x1f);
      __src = (void *)(DAT_804362fc + iVar6 * 0x60 + iVar2 * 0x780 + (iVar2 >> 0x1f) * -0x780 + 0x80
                      );
      pvVar7 = pvVar4;
      do {
        gnt4_memcpy(pvVar7,__src,0x60);
        iVar8 = iVar8 + 1;
        __src = (void *)((int)__src + 0x3c0);
        pvVar7 = (void *)((int)pvVar7 + 0x480);
      } while (iVar8 < 3);
    }
    pvVar4 = (void *)((int)pvVar4 + 0x60);
    iVar5 = iVar5 + 1;
  } while( true );
}



// ==== 80098214  zz_0098214_ ====

undefined4 * zz_0098214_(void)

{
  return &DAT_803ccd44;
}



// ==== 80098220  zz_0098220_ ====

void zz_0098220_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 1) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80098314;
    *(code **)(puVar1 + 0x10c) = FUN_80098774;
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



// ==== 80098314  FUN_80098314 ====

void FUN_80098314(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802dc890)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80098368  FUN_80098368 ====

void FUN_80098368(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar4;
  undefined4 in_r7;
  uint uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_800480f4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x47;
  fVar1 = FLOAT_80437db0;
  *(float *)(param_9 + 0xb4) = FLOAT_80437db0;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined2 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x12) = 5;
  *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_802dc854 + *(char *)(param_9 + 0x12) * 2);
  iVar3 = *(char *)(param_9 + 0x12) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_802dc804 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802dc800 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802dc808 + iVar3);
  iVar3 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),7,iVar3 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar3 + 0xc28;
  uVar2 = 7;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),7,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar7 = zz_0007cac_((double)FLOAT_80437db4,*(int *)(param_9 + 0xe4));
  iVar3 = zz_0006f98_(iVar6);
  uVar7 = zz_0007338_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe8),(float *)0x9,iVar3 + 0xc28,
                      (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
  iVar4 = iVar3 + 0xc28;
  uVar2 = 9;
  uVar5 = (uint)*(char *)(param_9 + 0x88);
  uVar7 = zz_0007338_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xec),(float *)0x9,iVar4,uVar5,
                      in_r8,in_r9,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar4,uVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437db4,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0098500_(param_9);
  return;
}



// ==== 80098500  zz_0098500_ ====

void zz_0098500_(int param_1)

{
  double dVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x89) = DAT_80433990;
  *(byte *)(param_1 + 0x12) = *(byte *)(iVar6 + 0x6e9) & 0x7f;
  iVar4 = *(char *)(param_1 + 0x12) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_802dc804 + iVar4);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802dc800 + iVar4);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802dc808 + iVar4);
  if ((*(uint *)(iVar6 + 0x5e0) & 0x20000000) == 0) {
    sVar3 = *(short *)(&DAT_802dc854 + *(char *)(param_1 + 0x12) * 2) - *(short *)(param_1 + 0x70);
    if (0x222 < sVar3) {
      sVar3 = 0x222;
    }
    if (sVar3 < -0x222) {
      sVar3 = -0x222;
    }
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar3;
    dVar1 = DOUBLE_80437db8;
    if ((&DAT_80433994)[*(char *)(param_1 + 0x12)] == '\0') {
      *(undefined2 *)(param_1 + 0x72) = 0;
    }
    else {
      sVar3 = *(short *)(&DAT_802dc864 + *(char *)(param_1 + 0x12) * 2) - *(short *)(param_1 + 0x7e)
      ;
      if (0x410 < sVar3) {
        sVar3 = 0x410;
      }
      if (sVar3 < -0x410) {
        sVar3 = -0x410;
      }
      *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + sVar3;
      *(short *)(param_1 + 0x72) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                               dVar1) * *(float *)(iVar6 + 0x1dc8) +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x72) ^ 0x80000000) -
                              dVar1));
    }
    if ('\0' < (char)(&DAT_8043399c)[*(char *)(param_1 + 0x12)]) {
      zz_00f0104_(iVar6,3,2);
    }
  }
  if ('\0' < *(char *)(iVar6 + 0xaf)) {
    cVar5 = 'y';
    if (*(char *)(iVar6 + 0xaf) == '\x01') {
      cVar5 = '5';
    }
    iVar4 = 0;
    *(undefined1 *)(iVar6 + 0xaf) = 0;
    *(undefined1 *)(param_1 + 0xaf) = 0;
    *(undefined2 *)(param_1 + 0x144) = *(undefined2 *)(iVar6 + 0x14a);
    do {
      zz_001ac80_(param_1,cVar5 + (char)iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < 4);
  }
  if (*(char *)(param_1 + 0xaf) != -1) {
    if ((*(short *)(param_1 + 0x144) != *(short *)(iVar6 + 0x14a)) ||
       (*(char *)(iVar6 + 0xaf) < '\0')) {
      *(undefined1 *)(param_1 + 0xaf) = 0xff;
    }
  }
  return;
}



// ==== 80098754  FUN_80098754 ====

void FUN_80098754(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80098774  FUN_80098774 ====

void FUN_80098774(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  
  iVar3 = *(int *)(param_9 + 0x90);
  cVar1 = *(char *)(param_9 + 0x12);
  puVar2 = &DAT_802dc874;
  if ((*(char *)(iVar3 + 0xae) != '\0') || (*(char *)(iVar3 + 0x3ec) == '\x04')) {
    puVar2 = &DAT_802dc876;
  }
  iVar4 = *(int *)(param_9 + (char)puVar2[cVar1 * 4] * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),(undefined *)(int)cVar1,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_00097b4_(iVar4,(int)(char)(puVar2 + cVar1 * 4)[1]);
  return;
}



// ==== 8009880c  zz_009880c_ ====

void zz_009880c_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 1000) == 0x101) {
    iVar2 = 0;
    do {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x83] = 0x18;
        *(code **)(puVar1 + 0xc) = FUN_80098920;
        *(code **)(puVar1 + 0x10c) = FUN_80098c3c;
        puVar1[0x11] = (char)iVar2;
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
  }
  return;
}



// ==== 80098920  FUN_80098920 ====

void FUN_80098920(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802dc8fc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80098974  FUN_80098974 ====

void FUN_80098974(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(code **)(param_9 + 0x100) = FUN_80098cb4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80437dc0;
  *(float *)(param_9 + 0xb4) = FLOAT_80437dc0;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_804339ac)[*(char *)(param_9 + 0x11)],iVar5 + 0xc28,uVar4,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  iVar2 = (int)(char)(&DAT_804339ac)[*(char *)(param_9 + 0x11)];
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,uVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,uVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437dc4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0098a78_(param_9);
  return;
}



// ==== 80098a78  zz_0098a78_ ====

void zz_0098a78_(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  undefined4 uVar5;
  char cVar6;
  undefined4 *puVar7;
  ushort uVar8;
  
  iVar4 = *(int *)(param_1 + 0x90);
  cVar6 = *(char *)(iVar4 + 0x6e8);
  if (*(char *)(iVar4 + 0x1b04) != '\0') {
    cVar6 = (&DAT_804339b0)[cVar6];
  }
  uVar8 = (ushort)(((int)cVar6 & 1 << (*(byte *)(param_1 + 0x11) & 1)) != 0);
  iVar2 = (int)(short)uVar8;
  *(undefined *)(param_1 + 0x89) = (&DAT_804339a8)[iVar2 * 2 + (int)(char)*(byte *)(param_1 + 0x11)]
  ;
  puVar7 = (undefined4 *)(&DAT_802dc8a0 + *(char *)(param_1 + 0x11) * 0xc + iVar2 * 0x18);
  uVar5 = puVar7[1];
  *(undefined4 *)(param_1 + 100) = *puVar7;
  *(undefined4 *)(param_1 + 0x68) = uVar5;
  *(undefined4 *)(param_1 + 0x6c) = puVar7[2];
  if ((*(char *)(iVar4 + 0x6e9) != '\0') && (uVar8 != 0)) {
    iVar2 = iVar2 * 0xc + -0x7fd23730;
    *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(iVar2 + *(char *)(param_1 + 0x11) * 6);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar2 + *(char *)(param_1 + 0x11) * 6 + 4);
    iVar4 = *(char *)(iVar4 + 0x6e9) * 4;
    sVar3 = *(short *)(&DAT_802dc8e8 + iVar4);
    if (*(char *)(param_1 + 0x11) != '\0') {
      sVar3 = -sVar3;
    }
    sVar3 = sVar3 - *(short *)(param_1 + 0x72);
    sVar1 = *(short *)(&DAT_802dc8ea + iVar4);
    if ((int)sVar1 < (int)sVar3) {
      sVar3 = sVar1;
    }
    iVar4 = -(int)sVar1;
    if (sVar3 < iVar4) {
      sVar3 = (short)iVar4;
    }
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar3;
    return;
  }
  puVar7 = (undefined4 *)(iVar2 * 0xc + -0x7fd23730 + *(char *)(param_1 + 0x11) * 6);
  *(undefined4 *)(param_1 + 0x70) = *puVar7;
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(puVar7 + 1);
  return;
}



// ==== 80098c1c  FUN_80098c1c ====

void FUN_80098c1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80098c3c  FUN_80098c3c ====

void FUN_80098c3c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80098cb4  FUN_80098cb4 ====

/* WARNING: Removing unreachable block (ram,0x80098d80) */
/* WARNING: Removing unreachable block (ram,0x80098d58) */
/* WARNING: Removing unreachable block (ram,0x80098d30) */

void FUN_80098cb4(int param_1)

{
  float afStack_38 [13];
  
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)FLOAT_80437dc8,afStack_38,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437dcc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437dcc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437dcc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                             0x3ff0000000000000)),afStack_38,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 80098dbc  zz_0098dbc_ ====

void zz_0098dbc_(int param_1,undefined1 param_2,undefined1 param_3)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((((sVar1 == 0x500) || (sVar1 == 0x509)) || (sVar1 == 0x50a)) ||
        ((sVar1 == 0x50c || (sVar1 == 0x515)))) ||
       ((sVar1 == 0x516 || ((sVar1 == 0x503 || (sVar1 == 0x507)))))) ||
      ((sVar1 == 0x50f || (sVar1 == 0x513)))) &&
     (puVar2 = zz_0088aa0_(param_1,2,8,0,1), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x10] = 0x2e;
    puVar2[0x13] = param_3;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_80099180;
    *(code **)(puVar2 + 0x10c) = FUN_80099944;
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



// ==== 80098f1c  zz_0098f1c_ ====

void zz_0098f1c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,8,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2e;
    puVar1[0x13] = *(undefined1 *)(param_1 + 0x13);
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80099180;
    *(code **)(puVar1 + 0x10c) = FUN_80099944;
    *(int *)(puVar1 + 0x54) = param_1;
    *(undefined4 *)(puVar1 + 0x8c) = *(undefined4 *)(param_1 + 0x90);
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(*(int *)(param_1 + 0x90) + 0x94);
    puVar1[0x96] = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x96);
    puVar1[0x97] = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x97);
    puVar1[0x88] = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(*(int *)(param_1 + 0x90) + 0xd0);
  }
  return;
}



// ==== 80099064  zz_0099064_ ====

void zz_0099064_(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,1,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2e;
    puVar1[0x13] = *(undefined1 *)(param_2 + 0x13);
    puVar1[0x11] = *(undefined1 *)(param_2 + 0x11);
    *(int *)(puVar1 + 0x54) = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80099b28;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
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
    *(undefined4 *)(puVar1 + 0x70) = *(undefined4 *)(param_2 + 0x70);
    *(undefined2 *)(puVar1 + 0x74) = *(undefined2 *)(param_2 + 0x74);
    puVar1[0x89] = *(undefined1 *)(param_2 + 0x89);
  }
  return;
}



// ==== 80099180  FUN_80099180 ====

void FUN_80099180(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94)) {
      if ((*(char *)(iVar1 + 0x18) == '\x01') && ('\0' < *(char *)(iVar1 + 0x6f7)))
      goto LAB_800991d8;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_800991d8:
  (*(code *)(&PTR_FUN_802f3db8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80099208  FUN_80099208 ====

void FUN_80099208(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar9;
  
  fVar3 = FLOAT_80437dd4;
  fVar2 = FLOAT_80437dd0;
  dVar9 = (double)FLOAT_80437dd4;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar7 = *(char *)(*(char *)(param_9 + 0x13) * 5 + -0x7fd0c2e0 + (int)*(char *)(param_9 + 0x11)) *
          0x20;
  uVar5 = *(undefined4 *)(&DAT_802f3aa4 + iVar7);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f3aa0 + iVar7);
  *(undefined4 *)(param_9 + 0x68) = uVar5;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f3aa8 + iVar7);
  uVar5 = *(undefined4 *)(&DAT_802f3ab0 + iVar7);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(&DAT_802f3aac + iVar7);
  *(undefined4 *)(param_9 + 0x5c) = uVar5;
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(&DAT_802f3ab4 + iVar7);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_802f3ab8 + iVar7);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_802f3abc + iVar7);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_802f3abe + iVar7);
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x158) = fVar2;
  *(float *)(param_9 + 0x15c) = fVar3;
  *(float *)(param_9 + 0x160) = fVar2;
  fVar2 = FLOAT_80437dd8;
  if ('\x05' < *(char *)(param_9 + 0x13)) {
    *(float *)(param_9 + 0x158) = FLOAT_80437dd8;
    *(float *)(param_9 + 0x15c) = fVar3;
    *(float *)(param_9 + 0x160) = fVar2;
  }
  fVar3 = FLOAT_80437de0;
  fVar2 = FLOAT_80437ddc;
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_9 + 0x84) = 0x57;
    *(float *)(param_9 + 0xd4) = fVar3;
    uVar6 = zz_00055fc_();
    fVar2 = FLOAT_80437dd0;
    param_2 = (double)FLOAT_80437dd0;
    dVar9 = (double)FLOAT_80437de0;
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + (short)(uVar6 << 0xc);
    *(float *)(param_9 + 0x38) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x58)) / dVar9);
    *(float *)(param_9 + 0x3c) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x5c)) / dVar9);
    *(float *)(param_9 + 0x40) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x60)) / dVar9);
    *(float *)(param_9 + 0x14c) = fVar2;
    *(float *)(param_9 + 0x150) = fVar2;
    *(float *)(param_9 + 0x154) = fVar2;
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      param_2 = (double)FLOAT_80437ddc;
      *(undefined1 *)(param_9 + 0x84) = 0x57;
      fVar3 = FLOAT_80437de0;
      dVar9 = (double)FLOAT_80437de0;
      *(float *)(param_9 + 0xd4) = fVar2;
      fVar4 = FLOAT_80437de4;
      *(float *)(param_9 + 0x144) = fVar3;
      *(float *)(param_9 + 0x148) = fVar4;
      *(undefined2 *)(param_9 + 0x7e) = 0x1999;
      *(float *)(param_9 + 0x14c) = fVar2;
      *(float *)(param_9 + 0x150) = fVar2;
      *(float *)(param_9 + 0x154) = fVar2;
    }
    else if (-1 < cVar1) {
      *(undefined1 *)(param_9 + 0x84) = 0x57;
      fVar3 = FLOAT_80437dec;
      fVar2 = FLOAT_80437de8;
      if (*(short *)(param_9 + 0x94) == 0x509) {
        *(float *)(param_9 + 0xd8) = FLOAT_80437de8;
        *(float *)(param_9 + 0xd4) = fVar2;
      }
      else {
        *(float *)(param_9 + 0xd8) = FLOAT_80437dec;
        *(float *)(param_9 + 0xd4) = fVar3;
      }
      uVar6 = zz_00055fc_();
      fVar2 = FLOAT_80437dd0;
      param_3 = (double)FLOAT_80437dd0;
      param_2 = (double)FLOAT_80437df0;
      *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + (short)(uVar6 << 0xc);
      *(float *)(param_9 + 0x38) =
           (float)(param_3 - (double)*(float *)(param_9 + 0x58)) /
           (float)((double)*(float *)(param_9 + 0xd8) * param_2);
      *(float *)(param_9 + 0x3c) =
           (float)(param_3 - (double)*(float *)(param_9 + 0x5c)) /
           (float)((double)*(float *)(param_9 + 0xd8) * param_2);
      dVar9 = (double)(float)(param_3 - (double)*(float *)(param_9 + 0x60));
      *(float *)(param_9 + 0x40) =
           (float)(dVar9 / (double)(float)((double)*(float *)(param_9 + 0xd8) * param_2));
      *(float *)(param_9 + 0x14c) = fVar2;
      *(float *)(param_9 + 0x150) = fVar2;
      *(float *)(param_9 + 0x154) = fVar2;
    }
  }
  else if (cVar1 < '\x05') {
    *(undefined1 *)(param_9 + 0x84) = 0x53;
    if (*(char *)(param_9 + 0x11) == '\x03') {
      *(float *)(param_9 + 0xd4) = FLOAT_80437df4;
    }
    else {
      *(float *)(param_9 + 0xd4) = FLOAT_80437df8;
    }
    param_2 = (double)FLOAT_80437dd0;
    dVar9 = (double)FLOAT_80437df4;
    *(float *)(param_9 + 0x38) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x58)) / dVar9);
    *(float *)(param_9 + 0x3c) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x5c)) / dVar9);
    *(float *)(param_9 + 0x40) =
         (float)((double)(float)(param_2 - (double)*(float *)(param_9 + 0x60)) / dVar9);
  }
  iVar7 = zz_0006f78_(*(int *)(param_9 + 0x90));
  iVar8 = *(char *)(param_9 + 0x13) * 10;
  zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,
              *(int *)(param_9 + 0xe0),
              (int)*(short *)(iVar8 + -0x7fd0c2b8 + *(char *)(param_9 + 0x11) * 2),iVar8,in_r7,in_r8
              ,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 80099510  FUN_80099510 ====

void FUN_80099510(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float afStack_18 [4];
  
  iVar5 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  fVar2 = FLOAT_80437ddc;
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(iVar5 + 0x1dc8);
    if (fVar2 <= *(float *)(param_1 + 0xd4)) {
      gnt4_PSQUATScale_bl((double)*(float *)(iVar5 + 0x1dc8),(float *)(param_1 + 0x38),afStack_18);
      gnt4_PSVECAdd_bl(afStack_18,(float *)(param_1 + 0x58),(float *)(param_1 + 0x58));
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      zz_0099064_(iVar5,param_1);
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) + *(float *)(iVar5 + 0x1dc8);
      fVar4 = FLOAT_80437e00;
      fVar3 = FLOAT_80437dfc;
      fVar2 = FLOAT_80437dd0;
      if ((*(ushort *)(param_1 + 0x1c) & 1) == 0) {
        *(float *)(param_1 + 0x58) = FLOAT_80437dd0;
        *(float *)(param_1 + 0x5c) = fVar4;
        *(float *)(param_1 + 0x60) = fVar2;
      }
      else {
        *(float *)(param_1 + 0x58) = FLOAT_80437dfc;
        *(float *)(param_1 + 0x5c) = fVar2;
        *(float *)(param_1 + 0x60) = fVar3;
      }
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x7e);
      cVar1 = *(char *)(param_1 + 0x19);
      if (cVar1 == '\x01') {
        zz_00f0104_(param_1,9,2);
        if (((*(float *)(iVar5 + 0x558) <= FLOAT_80437ddc) ||
            (FLOAT_80437e08 <= *(float *)(param_1 + 0xd4))) || ((*(uint *)(iVar5 + 0x5e0) & 3) == 0)
           ) {
          *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        }
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          if (FLOAT_80437dd0 <= *(float *)(param_1 + 0x14c)) {
            *(char *)(param_1 + 0x19) = cVar1 + '\x01';
          }
          else {
            fVar2 = FLOAT_80437e04 * *(float *)(iVar5 + 0x1dc8);
            *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + fVar2;
            *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + fVar2;
            *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + fVar2;
          }
        }
      }
      else if (cVar1 < '\x03') {
        if (*(float *)(param_1 + 0x14c) <= FLOAT_80437ddc) {
          *(undefined1 *)(param_1 + 0x18) = 2;
        }
        else {
          fVar2 = FLOAT_80437e0c * *(float *)(iVar5 + 0x1dc8);
          *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + fVar2;
          *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + fVar2;
        }
      }
      fVar2 = FLOAT_80437ddc;
      if (*(char *)(param_1 + 0x19) < '\x02') {
        *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - *(float *)(iVar5 + 0x1dc8);
        if (*(float *)(param_1 + 0x144) < fVar2) {
          *(float *)(param_1 + 0x144) = FLOAT_80437de0;
          zz_0098f1c_(param_1,1);
        }
        fVar2 = FLOAT_80437ddc;
        *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) - *(float *)(iVar5 + 0x1dc8);
        if (*(float *)(param_1 + 0x148) < fVar2) {
          *(float *)(param_1 + 0x148) = FLOAT_80437de4;
          zz_0098f1c_(param_1,2);
        }
      }
    }
    else if (-1 < cVar1) {
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(iVar5 + 0x1dc8);
      if (fVar2 <= *(float *)(param_1 + 0xd4)) {
        gnt4_PSQUATScale_bl((double)*(float *)(iVar5 + 0x1dc8),(float *)(param_1 + 0x38),afStack_18)
        ;
        gnt4_PSVECAdd_bl(afStack_18,(float *)(param_1 + 0x58),(float *)(param_1 + 0x58));
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
      }
      fVar3 = FLOAT_80437e10;
      fVar2 = FLOAT_80437df0;
      if ((*(char *)(param_1 + 0x19) == '\0') &&
         (*(float *)(param_1 + 0xd4) <= *(float *)(param_1 + 0xd8) * FLOAT_80437df0)) {
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(float *)(param_1 + 0x38) =
             -*(float *)(param_1 + 0x58) / (*(float *)(param_1 + 0xd8) * fVar2);
        *(float *)(param_1 + 0x3c) =
             (fVar3 - *(float *)(param_1 + 0x5c)) / (*(float *)(param_1 + 0xd8) * fVar2);
        *(float *)(param_1 + 0x40) =
             -*(float *)(param_1 + 0x60) / (*(float *)(param_1 + 0xd8) * fVar2);
      }
    }
  }
  else if (cVar1 < '\x05') {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(iVar5 + 0x1dc8);
    fVar4 = FLOAT_80437e14;
    fVar3 = FLOAT_80437dd0;
    if (fVar2 <= *(float *)(param_1 + 0xd4)) {
      if ((*(ushort *)(param_1 + 0x1c) & 1) == 0) {
        *(float *)(param_1 + 0x14c) = FLOAT_80437e14;
        *(float *)(param_1 + 0x150) = fVar4;
        *(float *)(param_1 + 0x154) = fVar4;
      }
      else {
        *(float *)(param_1 + 0x14c) = FLOAT_80437dd0;
        *(float *)(param_1 + 0x150) = fVar3;
        *(float *)(param_1 + 0x154) = fVar3;
      }
      if (*(float *)(param_1 + 0x58) < FLOAT_80437dd0) {
        gnt4_PSQUATScale_bl((double)*(float *)(iVar5 + 0x1dc8),(float *)(param_1 + 0x38),afStack_18)
        ;
        gnt4_PSVECAdd_bl(afStack_18,(float *)(param_1 + 0x58),(float *)(param_1 + 0x58));
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  return;
}



// ==== 80099910  FUN_80099910 ====

void FUN_80099910(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80099924  FUN_80099924 ====

void FUN_80099924(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80099944  FUN_80099944 ====

void FUN_80099944(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_0099988_(param_9);
  zz_00076d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x45);
  return;
}



// ==== 80099988  zz_0099988_ ====

/* WARNING: Removing unreachable block (ram,0x80099a8c) */
/* WARNING: Removing unreachable block (ram,0x80099a5c) */
/* WARNING: Removing unreachable block (ram,0x80099a2c) */

void zz_0099988_(int param_1)

{
  byte bVar1;
  float afStack_38 [12];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 0x20) == 0) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + 0x114),(float *)(param_1 + 0x114));
    }
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4)
                      ,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 1) != 0) {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  }
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e18 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e18 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_38,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e18 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 0x10) != 0) {
    gnt4_PSMTXScale_bl((double)(*(float *)(param_1 + 0x158) *
                               *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x14c)),
                       (double)(*(float *)(param_1 + 0x15c) *
                               *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0x150)),
                       (double)(*(float *)(param_1 + 0x160) *
                               *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0x154)),afStack_38)
    ;
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 80099b28  FUN_80099b28 ====

void FUN_80099b28(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     ((*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94) ||
      (*(char *)(*(int *)(param_1 + 0x90) + 0x18) != '\x01')))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_802f3dc8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80099bb4  FUN_80099bb4 ====

void FUN_80099bb4(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(char *)(*(char *)(param_1 + 0x13) * 5 + -0x7fd0c2e0 + (int)*(char *)(param_1 + 0x11)) *
          0x20;
  uVar1 = *(undefined4 *)(&DAT_802f3aa4 + iVar2);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802f3aa0 + iVar2);
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802f3aa8 + iVar2);
  iVar2 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),(float *)(param_1 + 100),
             (float *)(param_1 + 0x20));
  iVar2 = zz_008ac80_(param_1,0);
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    zz_0099cb0_(param_1);
  }
  return;
}



// ==== 80099cb0  zz_0099cb0_ ====

void zz_0099cb0_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  float local_58;
  undefined4 local_54;
  float local_50;
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  iVar3 = *(int *)(param_1 + 0x54);
  iVar4 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar3 + 0x18) == '\x02') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    uVar2 = *(undefined4 *)(iVar3 + 0x5c);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(iVar3 + 0x58);
    *(undefined4 *)(param_1 + 0x5c) = uVar2;
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar3 + 0x60);
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      local_58 = FLOAT_80437ddc;
      local_50 = FLOAT_80437ddc;
      local_54 = *(undefined4 *)(&DAT_802f3d98 + *(char *)(param_1 + 0x13) * 4);
      gnt4_PSQUATScale_bl((double)*(float *)(iVar3 + 0x150),&local_58,&local_58);
      local_18 = 0x43300000;
      uStack_14 = (int)*(short *)(param_1 + 0x70) ^ 0x80000000;
      gnt4_PSMTXRotRad_bl((double)(FLOAT_80437e18 *
                                  (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80437e20))
                          ,afStack_4c,0x78);
      gnt4_PSMTXConcat_bl((float *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),afStack_4c,
                          afStack_4c);
      gnt4_PSMTXMultVec_bl(afStack_4c,&local_58,(float *)(param_1 + 0x20));
      *(undefined1 *)(param_1 + 0x19) = 2;
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                   (float *)(param_1 + 100),(float *)(param_1 + 0x20));
        *(undefined1 *)(param_1 + 0x19) = 1;
      }
    }
    else if (cVar1 < '\x03') {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 80099e28  FUN_80099e28 ====

void FUN_80099e28(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}



// ==== 80099e50  FUN_80099e50 ====

void FUN_80099e50(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80099e70  zz_0099e70_ ====

void zz_0099e70_(int param_1,undefined1 param_2)

{
  FUN_80099e94(param_1,param_2,0);
  return;
}



// ==== 80099e94  FUN_80099e94 ====

/* WARNING: Removing unreachable block (ram,0x8009a0b4) */
/* WARNING: Removing unreachable block (ram,0x80099ea4) */

void FUN_80099e94(int param_1,undefined1 param_2,short param_3)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float fStack_68;
  float local_64;
  float afStack_5c [2];
  undefined4 local_54;
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_28;
  uint uStack_24;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 10;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8009a0dc;
    *(code **)(puVar1 + 0x10c) = FUN_8009a634;
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
    if ((puVar1[0xd0] & 4) == 0) {
      *(undefined4 *)(puVar1 + 200) = 0;
    }
    iVar2 = (uint)(byte)puVar1[0x11] * 0x3c;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + *(short *)(&DAT_802f3dda + iVar2) * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fd0c220),(float *)(puVar1 + 0x20));
    uStack_24 = (int)param_3 ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80437e28 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80437e30)),
                        afStack_5c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + *(short *)(&DAT_802f3dda + iVar2) * 0x30 + 0x8d4),
                        afStack_5c,afStack_5c);
    *(undefined4 *)(puVar1 + 0x38) = local_54;
    *(undefined4 *)(puVar1 + 0x3c) = local_44;
    *(undefined4 *)(puVar1 + 0x40) = local_34;
    if ((*(ushort *)(&DAT_802f3e02 + iVar2) & 4) != 0) {
      gnt4_PSVECAdd_bl((float *)(puVar1 + 0x20),(float *)(param_1 + 0x7b0),(float *)(puVar1 + 0x20))
      ;
    }
    zz_006ec1c_((float *)(puVar1 + 0x38),&fStack_68);
    dVar5 = (double)local_64;
    local_64 = FLOAT_80437e2c;
    dVar4 = gnt4_PSVECMag_bl(&fStack_68);
    iVar3 = FUN_800452a0(dVar5,dVar4);
    *(short *)(puVar1 + 0x70) = -(short)iVar3;
    *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(puVar1 + 0x74) = *(undefined2 *)(&DAT_802f3e00 + iVar2);
    *(undefined2 *)(puVar1 + 0x158) = 0;
    *(undefined2 *)(puVar1 + 0x156) = 0;
    gnt4_PSQUATScale_bl((double)*(float *)(puVar1 + 0xb4),(float *)(iVar2 + -0x7fd0c20c),
                        (float *)(puVar1 + 0x58));
  }
  return;
}



// ==== 8009a0dc  FUN_8009a0dc ====

void FUN_8009a0dc(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_802f4d14)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8009a12c  FUN_8009a12c ====

void FUN_8009a12c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  *(undefined1 *)(param_9 + 0x19) = 0;
  if ((*(ushort *)(&DAT_802f3e02 + iVar4) & 8) == 0) {
    *(code **)(param_9 + 0x100) = FUN_80047f60;
    zz_0089100_(param_9,0,1);
    *(undefined1 *)(param_9 + 0x84) = 0x1e;
  }
  else {
    *(code **)(param_9 + 0x100) = zz_0048288_;
    zz_0089100_(param_9,0,1);
    *(undefined1 *)(param_9 + 0x84) = 0x10;
    uVar1 = DAT_802b0cb4;
    *(undefined1 *)(param_9 + 0x98) = 5;
    uVar2 = DAT_802b0cb8;
    *(undefined4 *)(param_9 + 0x9c) = uVar1;
    uVar1 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0xa0) = uVar2;
    *(undefined4 *)(param_9 + 0xa4) = uVar1;
    zz_0048288_(param_9);
    *(undefined2 *)(param_9 + 0x158) = *(undefined2 *)(param_9 + 0x74);
  }
  iVar3 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802f3ddc + iVar4));
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar5 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802f3dec + iVar4),(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802f3dec + iVar4);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_802f3df0 + iVar4);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802f3dde + iVar4);
    *(undefined1 *)(param_9 + 0x82) = 1;
    uVar5 = zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                        *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_802f3dd8)[iVar4],
                        (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    FUN_8009a2ac(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    if (-1 < *(short *)(&DAT_802f3e10 + iVar4)) {
      zz_00f036c_(param_9,(int)*(short *)(&DAT_802f3e10 + iVar4));
    }
  }
  return;
}



// ==== 8009a2ac  FUN_8009a2ac ====

void FUN_8009a2ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x18) == '\x01') {
    iVar3 = zz_0083244_((float *)(param_9 + 0x20));
    if (iVar3 == 0) {
      cVar1 = *(char *)(param_9 + 0x19);
      if (cVar1 == '\x01') {
        if ((*(ushort *)(&DAT_802f3e02 + iVar4) & 0x20) != 0) {
          *(short *)(param_9 + 0x156) = *(short *)(param_9 + 0x156) + 0x3000;
        }
        gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                         (float *)(param_9 + 0x20));
        gnt4_PSVECAdd_bl((float *)(param_9 + 0x58),(float *)(param_9 + 0x144),
                         (float *)(param_9 + 0x58));
        fVar2 = FLOAT_80437e2c;
        *(float *)(param_9 + 0x150) = *(float *)(param_9 + 0x150) - FLOAT_80437e4c;
        if (*(float *)(param_9 + 0x150) <= fVar2) {
          *(float *)(param_9 + 0x150) = fVar2;
        }
        zz_0007cac_((double)*(float *)(param_9 + 0x150),*(int *)(param_9 + 0xe0));
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
        if (*(short *)(param_9 + 0x1c) < 1) {
          *(undefined1 *)(param_9 + 0x18) = 2;
          *(undefined1 *)(param_9 + 0x19) = 0;
          *(undefined1 *)(param_9 + 0x82) = 0;
        }
      }
      else if ((cVar1 < '\x01') && (-1 < cVar1)) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
        if (*(short *)(param_9 + 0x1c) < 1) {
          *(undefined1 *)(param_9 + 0x19) = 1;
          uVar5 = zz_008aff0_(param_9);
          *(undefined2 *)(param_9 + 0x1c) = 10;
          *(float *)(param_9 + 0x150) = FLOAT_80437e38;
          zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_802f3dd9)[iVar4],
                      (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
        }
        if ((*(ushort *)(&DAT_802f3e02 + iVar4) & 2) != 0) {
          *(short *)(param_9 + 0x158) = *(short *)(param_9 + 0x158) + 0x11c8;
        }
        if ((*(ushort *)(&DAT_802f3e02 + iVar4) & 0x20) != 0) {
          *(short *)(param_9 + 0x156) = *(short *)(param_9 + 0x156) + 0x3000;
        }
        fVar2 = FLOAT_80437e2c;
        if (FLOAT_80437e2c < *(float *)(param_9 + 0x44)) {
          *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c);
          if (fVar2 < *(float *)(param_9 + 0x44)) {
            if ((*(ushort *)(&DAT_802f3e02 + iVar4) & 8) == 0) {
              gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
              gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                                  (float *)(param_9 + 0x38));
              gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x20));
            }
            else {
              *(short *)(param_9 + 0x158) =
                   (short)(int)(((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(param_9 + 0x158) ^ 0x80000000) -
                                DOUBLE_80437e30) * DOUBLE_80437e40);
              FUN_80083874((double)*(float *)(&DAT_802f3e0c + iVar4),param_9);
              FUN_80083ad4((double)*(float *)(&DAT_802f3e08 + iVar4),param_9,
                           (char)*(undefined4 *)(&DAT_802f3e04 + iVar4));
            }
          }
          else {
            *(float *)(param_9 + 0x44) = fVar2;
          }
        }
        zz_00833ec_(param_9);
        zz_0083524_(param_9);
        gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar4 + -0x7fd0c20c),
                            (float *)(param_9 + 0x58));
        gnt4_PSQUATScale_bl((double)FLOAT_80437e48,(float *)(param_9 + 0x58),
                            (float *)(param_9 + 0x144));
        iVar4 = zz_0083714_(param_9);
        if (iVar4 == 0) {
          iVar4 = zz_0084170_(param_9);
          if (iVar4 != 0) {
            *(undefined1 *)(param_9 + 0x18) = 2;
            *(undefined1 *)(param_9 + 0x82) = 0;
          }
        }
        else {
          *(undefined1 *)(param_9 + 0x18) = 2;
          zz_008aff0_(param_9);
          *(undefined1 *)(param_9 + 0x82) = 0;
        }
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 2;
      zz_008aff0_(param_9);
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 8009a5d8  FUN_8009a5d8 ====

void FUN_8009a5d8(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8009a614  FUN_8009a614 ====

void FUN_8009a614(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8009a634  FUN_8009a634 ====

/* WARNING: Removing unreachable block (ram,0x8009a670) */
/* WARNING: Removing unreachable block (ram,0x8009a648) */

void FUN_8009a634(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_68 [12];
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e28 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x158) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,afStack_68);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e28 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x156) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl(afStack_68,pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x24);
  return;
}



// ==== 8009a6c4  FUN_8009a6c4 ====

void FUN_8009a6c4(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (((*(short *)(param_1 + 1000) == 2) || (*(short *)(param_1 + 1000) == 0xb)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,1,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = 0;
    puVar1[0x13] = param_2;
    iVar3 = 0;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_8009a8dc;
    *(code **)(puVar1 + 0x10c) = FUN_8009abcc;
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
    *(int *)(puVar1 + 0x144) = param_1 + 0xae4;
    do {
      puVar2 = zz_0088aa0_(param_1,2,0,1,2);
      if (puVar2 != (undefined1 *)0x0) {
        *puVar2 = 1;
        puVar2[0x11] = (char)iVar3 + '\x01';
        puVar2[0x13] = param_2;
        puVar2[0x83] = 0x18;
        *(code **)(puVar2 + 0xc) = FUN_8009a8dc;
        *(code **)(puVar2 + 0x10c) = FUN_8009abcc;
        *(undefined1 **)(puVar2 + 0x8c) = puVar1;
        *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(puVar1 + 0x90);
        *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(puVar1 + 0x94);
        puVar2[0x96] = puVar1[0x96];
        puVar2[0x97] = puVar1[0x97];
        puVar2[0x88] = puVar1[0x88];
        *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(puVar1 + 200);
        *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(puVar1 + 0xcc);
        *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(puVar1 + 0xb8);
        *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(puVar1 + 0xb4);
        *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(puVar1 + 0xb4);
        *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(puVar1 + 0xb4);
        *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(puVar1 + 0xb4);
        *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(puVar1 + 0xc0);
        *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(puVar1 + 0xc4);
        puVar2[0xd0] = puVar1[0xd0];
        *(undefined1 **)(puVar2 + 0x144) = puVar1 + 0x114;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 2);
  }
  return;
}



// ==== 8009a8dc  FUN_8009a8dc ====

void FUN_8009a8dc(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802f4d84)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8009a930  FUN_8009a930 ====

void FUN_8009a930(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 extraout_r4;
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x148) = 0;
  *(undefined1 *)(param_9 + 0x89) = 0xb;
  *(code **)(param_9 + 0x100) = FUN_8009ac48;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  iVar4 = zz_0006f98_(iVar4);
  iVar2 = *(char *)(param_9 + 0x13) * 0xc;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(iVar2 + -0x7fd0b2d8 + *(char *)(param_9 + 0x11) * 4),iVar4 + 0xc28,
                      iVar2,in_r8,in_r9,in_r10);
  iVar3 = *(char *)(param_9 + 0x13) * 0xc;
  iVar1 = iVar4 + 0xc28;
  iVar2 = *(int *)(iVar3 + -0x7fd0b2d8 + *(char *)(param_9 + 0x11) * 4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar1,iVar3,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar1,iVar3,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437e50,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_8009aa50(param_9);
  return;
}



// ==== 8009aa50  FUN_8009aa50 ====

void FUN_8009aa50(int param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar7 = *(int *)(param_1 + 0x90);
  cVar1 = *(char *)(param_1 + 0x11);
  iVar5 = *(char *)(iVar7 + 0x6e9) * 8;
  sVar3 = *(short *)(&DAT_802f4d6a + iVar5);
  if (cVar1 == '\0') {
    sVar4 = *(short *)(param_1 + 0x74);
  }
  else {
    sVar4 = *(short *)(param_1 + 0x72);
  }
  sVar4 = *(short *)(iVar5 + -0x7fd0b29c + cVar1 * 2) - sVar4;
  if ((int)sVar3 < (int)sVar4) {
    sVar4 = sVar3;
  }
  iVar5 = -(int)sVar3;
  if (sVar4 < iVar5) {
    sVar4 = (short)iVar5;
  }
  if (cVar1 == '\0') {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + sVar4;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar4;
  }
  bVar2 = *(byte *)(iVar7 + 0xaf);
  if ('\0' < (char)bVar2) {
    uVar6 = 1 << (int)*(char *)(param_1 + 0x11);
    if (((int)(char)bVar2 & uVar6) != 0) {
      *(byte *)(iVar7 + 0xaf) = bVar2 & ~(byte)uVar6;
      *(undefined1 *)(param_1 + 0xaf) = 0;
      *(undefined2 *)(param_1 + 0x148) = *(undefined2 *)(iVar7 + 0x15e);
      zz_001ac80_(param_1,(char)*(undefined2 *)(&DAT_80433a18 + *(char *)(param_1 + 0x13) * 2));
    }
  }
  if ((*(char *)(iVar7 + 0xaf) < '\0') || (*(short *)(param_1 + 0x148) != *(short *)(iVar7 + 0x15e))
     ) {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  return;
}



// ==== 8009abac  FUN_8009abac ====

void FUN_8009abac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8009abcc  FUN_8009abcc ====

void FUN_8009abcc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = 0;
    uVar2 = 1;
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = param_9 + iVar1 * 4;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0xe0)
              ,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar1 + 0xe0),uVar2);
  return;
}



// ==== 8009ac48  FUN_8009ac48 ====

/* WARNING: Removing unreachable block (ram,0x8009ace4) */
/* WARNING: Removing unreachable block (ram,0x8009acb0) */

void FUN_8009ac48(int param_1)

{
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  float afStack_3c [14];
  
  gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x144),(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(*(char *)(param_1 + 0x11) * 0xc + -0x7fd0b2c0),
             &local_48);
  *(float *)(param_1 + 0x120) = local_48;
  *(undefined4 *)(param_1 + 0x130) = local_44;
  *(undefined4 *)(param_1 + 0x140) = local_40;
  if (*(short *)(param_1 + 0x74) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e54 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_3c,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  if (*(short *)(param_1 + 0x72) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e54 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_3c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 8009ad20  FUN_8009ad20 ====

bool FUN_8009ad20(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x26;
    *(code **)(puVar1 + 0xc) = FUN_8009ae38;
    *(code **)(puVar1 + 0x10c) = FUN_8009b33c;
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



// ==== 8009ae38  FUN_8009ae38 ====

void FUN_8009ae38(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802f4dec)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8009aed0  FUN_8009aed0 ====

void FUN_8009aed0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  puVar7 = &DAT_802f4dd0;
  puVar5 = &DAT_802f4d98;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  iVar6 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar2 = iVar6 * 0x1c;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar1 = iVar2;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fd0b260),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_802f4d9c + iVar2) * 0x30 + 0x8fc);
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802f4de0 + iVar3),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802f4de0 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802f4dd2 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_802f4dd4 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_802f4dd6 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(&DAT_802f4de4 + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar8 = zz_0006f98_(iVar8);
  uVar9 = zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_802f4d98 + iVar2),iVar1,iVar4,puVar5,iVar6,puVar7);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar8 + 0x600),
              *(int *)(param_9 + 0xe4),(int)*(short *)(&DAT_802f4d9a + iVar2),iVar1,iVar4,puVar5,
              iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(undefined1 *)(param_9 + 0x146) = 0;
  *(undefined1 *)(param_9 + 0x147) = 0;
  *(undefined2 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802f4dd0 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x49);
  }
  return;
}



// ==== 8009b0f4  FUN_8009b0f4 ====

void FUN_8009b0f4(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x1d9);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  iVar3 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar3 == 0) {
    if (*(short *)(param_1 + 0x1c6) < 1) {
      FUN_8009b3dc(param_1);
      FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    }
    else {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      if (*(short *)(param_1 + 0x1c) < 1) {
        FUN_8009b3dc(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        if (*(char *)(param_1 + 0x19) == '\0') {
          if (*(char *)(param_1 + 0x147) == '\0') {
            if (cVar1 != '\0') {
              *(undefined1 *)(param_1 + 0x146) = 4;
              *(undefined1 *)(param_1 + 0x19) = 1;
            }
          }
          else {
            *(char *)(param_1 + 0x147) = *(char *)(param_1 + 0x147) + -1;
          }
        }
        else if (*(char *)(param_1 + 0x146) == '\0') {
          *(undefined1 *)(param_1 + 0x19) = 0;
          *(undefined1 *)(param_1 + 0x147) = 1;
        }
        else {
          *(char *)(param_1 + 0x146) = *(char *)(param_1 + 0x146) + -1;
        }
        if (*(char *)(param_1 + 0x146) == '\0') {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x148)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_802f4de8 + iVar2);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x148);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_802f4ddc + iVar2),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_802f4dd8 + iVar2),param_1,
                       (char)*(undefined2 *)(&DAT_802f4dd4 + iVar2));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          if (*(char *)(param_1 + 0x13) == '\0') {
            *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + 0x1c00;
          }
          else {
            *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + -0x1c00;
          }
        }
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x148));
        iVar2 = zz_0083714_(param_1);
        if (iVar2 != 0) {
          FUN_8009b3dc(param_1);
        }
      }
    }
  }
  else {
    FUN_8009b3dc(param_1);
  }
  return;
}



// ==== 8009b310  FUN_8009b310 ====

void FUN_8009b310(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8009b31c  FUN_8009b31c ====

void FUN_8009b31c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8009b33c  FUN_8009b33c ====

/* WARNING: Removing unreachable block (ram,0x8009b384) */

void FUN_8009b33c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  uint uVar2;
  undefined8 uVar3;
  float afStack_38 [12];
  
  uVar2 = 1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar2);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437e58 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x144) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  pfVar1 = afStack_38;
  uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe4),uVar2);
  return;
}



// ==== 8009b3dc  FUN_8009b3dc ====

void FUN_8009b3dc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 8009b508  FUN_8009b508 ====

void FUN_8009b508(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  FUN_800c10f0(param_1);
  iVar1 = 0;
  do {
    FUN_801395c0(param_1,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  zz_00c74ec_(param_1,0xb);
  *(undefined1 *)(param_1 + 0x149) = 0;
  return;
}



// ==== 8009b57c  FUN_8009b57c ====

void FUN_8009b57c(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  if (*(short *)(param_1 + 0x78e) <= *(short *)(param_1 + 0x774)) {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined1 *)(param_1 + 0x146) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(float *)(param_1 + 0x1dc0) = FLOAT_80437e60;
  }
  if (((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0) && (*(char *)(param_1 + 0x5da) != '/')) {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xffef;
  }
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    iVar4 = FUN_80112534(param_1);
    fVar3 = FLOAT_80437e64;
    if (iVar4 != 0) {
      iVar5 = 0x10;
      if ((*(byte *)(param_1 + 0x149) & 1) != 0) {
        iVar5 = 0x13;
      }
      *(char *)(param_1 + 0x149) = *(char *)(param_1 + 0x149) + '\x01';
      iVar5 = param_1 + iVar5 * 0x30;
      *(byte *)(param_1 + 0x149) = *(byte *)(param_1 + 0x149) & 1;
      uVar1 = *(undefined4 *)(iVar5 + 0x8f0);
      uVar2 = *(undefined4 *)(iVar5 + 0x900);
      *(undefined4 *)(iVar4 + 0x20) = *(undefined4 *)(iVar5 + 0x8e0);
      *(undefined4 *)(iVar4 + 0x24) = uVar1;
      *(undefined4 *)(iVar4 + 0x28) = uVar2;
      *(float *)(iVar4 + 0xb4) = *(float *)(iVar4 + 0xb4) * fVar3;
      *(undefined1 *)(iVar4 + 0x19) = 1;
    }
  }
  return;
}



// ==== 8009b6a8  FUN_8009b6a8 ====

void FUN_8009b6a8(int param_1,char param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = zz_011243c_(param_1,0);
  fVar3 = FLOAT_80437e64;
  if (iVar5 != 0) {
    iVar4 = 0x10;
    if (param_2 != '\0') {
      iVar4 = 0x13;
    }
    iVar4 = param_1 + iVar4 * 0x30;
    uVar1 = *(undefined4 *)(iVar4 + 0x8f0);
    uVar2 = *(undefined4 *)(iVar4 + 0x900);
    *(undefined4 *)(iVar5 + 0x20) = *(undefined4 *)(iVar4 + 0x8e0);
    *(undefined4 *)(iVar5 + 0x24) = uVar1;
    *(undefined4 *)(iVar5 + 0x28) = uVar2;
    *(float *)(iVar5 + 0xb4) = *(float *)(iVar5 + 0xb4) * fVar3;
    *(undefined1 *)(iVar5 + 0x19) = 1;
  }
  return;
}



// ==== 8009b74c  FUN_8009b74c ====

void FUN_8009b74c(int param_1)

{
  (*(code *)(&PTR_FUN_802f57e8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8009b788  FUN_8009b788 ====

void FUN_8009b788(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00f1e30_(param_1,&DAT_802f57f4);
  return;
}



// ==== 8009b7bc  FUN_8009b7bc ====

void FUN_8009b7bc(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    FUN_8009ad20(param_1,*(undefined1 *)(param_1 + 0x146));
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x146) + 0x144) = 1;
    *(char *)(param_1 + 0x146) = *(char *)(param_1 + 0x146) + '\x01';
  }
  return;
}



// ==== 8009b82c  FUN_8009b82c ====

undefined4 FUN_8009b82c(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 8009b894  FUN_8009b894 ====

void FUN_8009b894(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437e70;
  fVar1 = FLOAT_80437e68;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80437e70) * FLOAT_80437e68);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_802f5808)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8009b960  FUN_8009b960 ====

void FUN_8009b960(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 8009b984  FUN_8009b984 ====

void FUN_8009b984(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 8009b9a8  FUN_8009b9a8 ====

void FUN_8009b9a8(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 8009b9cc  FUN_8009b9cc ====

void FUN_8009b9cc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f581c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8009ba1c  FUN_8009ba1c ====

void FUN_8009ba1c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80437e78;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80437e7c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80437e80;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8009bb1c  FUN_8009bb1c ====

void FUN_8009bb1c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80437e7c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80437e60;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80437e84;
    fVar1 = FLOAT_80437e78;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 8009bbe8  FUN_8009bbe8 ====

void FUN_8009bbe8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  fVar2 = FLOAT_80437e60;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         (FLOAT_80437e94 * *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c)
         ) / FLOAT_80437e78;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_1c = *(float *)(iVar4 + 0x8e0);
    local_18 = *(float *)(iVar4 + 0x8f0);
    local_14 = *(undefined4 *)(iVar4 + 0x900);
    local_28 = *(float *)(param_1 + 0x518);
    local_20 = *(undefined4 *)(param_1 + 0x520);
    local_24 = FLOAT_80437e88 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
    fVar2 = FLOAT_80437e60;
    *(float *)(param_1 + 0x48) = local_18 / FLOAT_80437e8c;
    local_18 = fVar2;
    dVar5 = gnt4_PSVECMag_bl(&local_1c);
    fVar1 = FLOAT_80437e90;
    fVar2 = FLOAT_80437e60;
    *(float *)(param_1 + 0x44) = (float)(dVar5 / (double)FLOAT_80437e8c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) == 0) {
    uVar3 = FUN_800668cc((double)FLOAT_80437e98,param_1);
    fVar2 = FLOAT_80437e60;
    if (((int)uVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  return;
}



// ==== 8009bdc4  FUN_8009bdc4 ====

void FUN_8009bdc4(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x544) == '\0') && (*(char *)(param_1 + 0x1cf2) != '\0')) {
      dVar3 = (double)FLOAT_80437e80;
      *(undefined1 *)(param_1 + 0x544) = 1;
      zz_004beb8_(dVar3,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
    }
    FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80437e60;
    if (*(float *)(param_1 + 0x44) < FLOAT_80437e60) {
      *(float *)(param_1 + 0x44) = FLOAT_80437e60;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      if (*(char *)(param_1 + 0x1cee) != '\0') {
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_80437e98 + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 8009bed8  FUN_8009bed8 ====

void FUN_8009bed8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437e70;
  fVar1 = FLOAT_80437e68;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80437e70) * FLOAT_80437e68);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_802f582c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8009bf78  FUN_8009bf78 ====

void FUN_8009bf78(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802f5840)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8009bfc8  FUN_8009bfc8 ====

void FUN_8009bfc8(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80437e80;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80437e60;
  return;
}



// ==== 8009c08c  FUN_8009c08c ====

void FUN_8009c08c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_80437e9c;
  fVar2 = FLOAT_80437e60;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_80437ea0;
    *(float *)(param_1 + 0x558) = fVar3;
    dVar5 = (double)FLOAT_80437e80;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x48) = fVar4;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8009c128  FUN_8009c128 ====

void FUN_8009c128(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x10;
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_80437e60;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar3 < fVar2) {
    iVar4 = zz_00677b0_(param_1);
    if ((iVar4 != 0) && (*(char *)(param_1 + 0x1b01) != '\0')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0xc;
      zz_0066530_(param_1,0x2c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar5 = (double)FLOAT_80437e80;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  else {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xffef;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8009c22c  FUN_8009c22c ====

void FUN_8009c22c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x10;
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80437ea4;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    zz_006d144_(param_1,0xc0);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ac);
    fVar3 = FLOAT_80437e60;
    fVar2 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar2 < *(float *)(param_1 + 0x760))) {
      fVar2 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar2 / FLOAT_80437ea4;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_011243c_(param_1,1);
    dVar4 = (double)FLOAT_80437e80;
    *(float *)(param_1 + 0x1dc0) = FLOAT_80437ea8;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  FUN_80112534(param_1);
  return;
}



// ==== 8009c354  FUN_8009c354 ====

void FUN_8009c354(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  float local_58;
  float local_54;
  undefined4 local_50;
  float afStack_4c [3];
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  float afStack_28 [8];
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  FUN_8005a580(param_1);
  local_40 = *(float *)(param_1 + 0x20);
  local_38 = *(undefined4 *)(param_1 + 0x28);
  local_3c = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
  local_34 = *(float *)(param_1 + 0x2c);
  local_30 = *(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x66c);
  local_2c = *(undefined4 *)(param_1 + 0x34);
  iVar3 = zz_003f044_(&local_40,&local_34,afStack_28);
  if (iVar3 != 0) {
    gnt4_PSVECSubtract_bl(&local_40,&local_34,afStack_4c);
    dVar5 = gnt4_PSVECSquareMag_bl(afStack_4c);
    if (dVar5 <= (double)FLOAT_80437e60) {
      dVar5 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,(float *)(param_1 + 0x20)
                          );
      local_3c = (float)dVar5;
      *(float *)(param_1 + 0x24) = (float)dVar5;
    }
    else {
      gnt4_PSVECNormalize_bl(afStack_4c,afStack_4c);
      gnt4_PSQUATScale_bl((double)FLOAT_80437eac,afStack_4c,afStack_4c);
      gnt4_PSVECAdd_bl(&local_40,afStack_4c,&local_34);
      dVar5 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,(float *)(param_1 + 0x20)
                          );
      local_3c = (float)dVar5;
      dVar5 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,&local_34);
      local_30 = (float)dVar5;
      if (local_3c < (float)dVar5) {
        *(float *)(param_1 + 0x24) = (float)dVar5;
      }
      else {
        *(float *)(param_1 + 0x24) = local_3c;
      }
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) - *(float *)(param_1 + 0x6d0);
    }
  }
  fVar2 = FLOAT_80437e60;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar2 < fVar1) && (uVar4 = FUN_80066838((double)FLOAT_80437e84,param_1), (int)uVar4 < 1))
  goto LAB_8009c5f4;
  fVar1 = FLOAT_80437e60;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x543) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0x1e;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfff3;
  if (*(int *)(param_1 + 0xcc) == 0) {
LAB_8009c5c0:
    fVar1 = FLOAT_80437eb8;
    *(float *)(param_1 + 0x44) = FLOAT_80437eb8;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  else {
    local_58 = *(float *)(param_1 + 0x910);
    local_54 = *(float *)(param_1 + 0x920);
    local_50 = *(undefined4 *)(param_1 + 0x930);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_58,&local_58);
    gnt4_PSVECNormalize_bl(&local_58,&local_58);
    if (local_54 <= FLOAT_80437eb0) goto LAB_8009c5c0;
    gnt4_PSQUATScale_bl((double)FLOAT_80437eb4,&local_58,&local_58);
    fVar1 = FLOAT_80437e60;
    *(float *)(param_1 + 0x48) = local_54;
    local_54 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_58);
    *(float *)(param_1 + 0x44) = (float)dVar5;
  }
  fVar1 = FLOAT_80437e60;
  *(float *)(param_1 + 0x4c) = FLOAT_80437e60;
  *(float *)(param_1 + 0x50) = fVar1;
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x48);
  iVar3 = FUN_800452a0((double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
  *(short *)(param_1 + 0x18da) = -(short)iVar3;
LAB_8009c5f4:
  FUN_801125a4(param_1);
  return;
}



// ==== 8009c614  FUN_8009c614 ====

/* WARNING: Removing unreachable block (ram,0x8009c78c) */
/* WARNING: Removing unreachable block (ram,0x8009c624) */

void FUN_8009c614(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar4 = DOUBLE_80437e70;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar4);
  }
  zz_004cd24_(param_1,0xf);
  dVar4 = (double)FLOAT_80437e98;
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
  dVar5 = (double)*(float *)(param_1 + 0x24);
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x1dc0) =
       *(float *)(param_1 + 0x1dc0) +
       (float)((double)*(float *)(param_1 + 0x24) - dVar5) / *(float *)(param_1 + 0x5f8);
  *(float *)(param_1 + 0x24) = (float)dVar5;
  fVar2 = FLOAT_80437ebc;
  fVar1 = FLOAT_80437e60;
  if ((*(char *)(param_1 + 0x1b01) != '\0') && (FLOAT_80437e60 <= *(float *)(param_1 + 0x1dc0))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x1dc0);
    *(float *)(param_1 + 0x1dc0) = fVar1;
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfff3;
    zz_0066530_(param_1,0x2d);
  }
  if (*(float *)(param_1 + 0x24) <= *(float *)(param_1 + 0x920)) {
    if (*(char *)(param_1 + 0x543) == '\0') {
      *(undefined1 *)(param_1 + 0x543) = 1;
      zz_011243c_(param_1,0);
      zz_011243c_(param_1,1);
      zz_011243c_(param_1,3);
    }
  }
  else {
    FUN_801125a4(param_1);
  }
  return;
}



// ==== 8009c7a8  FUN_8009c7a8 ====

void FUN_8009c7a8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  
  if (*(char *)(param_1 + 0x542) == '\0') {
    uVar4 = zz_006de44_(param_1,0xf0f00);
    dVar6 = DOUBLE_80437e70;
    if (uVar4 != 0) {
      if ((int)*(short *)(param_1 + 0x54e) < (int)uVar4) {
        uVar4 = (int)*(short *)(param_1 + 0x54e);
      }
      *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar4;
      *(float *)(param_1 + 0x560) =
           *(float *)(param_1 + 0x560) +
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar6);
    }
    fVar3 = FLOAT_80437ec0;
    fVar2 = FLOAT_80437ebc;
    if (*(float *)(param_1 + 0x560) <= FLOAT_80437e60) {
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(float *)(param_1 + 0x50) = -*(float *)(param_1 + 0x48) / fVar3;
    }
    else {
      *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar2;
    }
  }
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar5 = FUN_800452a0((double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
  fVar3 = FLOAT_80437e60;
  *(short *)(param_1 + 0x18da) = -(short)iVar5;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) && (*(char *)(param_1 + 0x1b01) != '\0')) {
    dVar6 = (double)FLOAT_80437e80;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8009c918  FUN_8009c918 ====

void FUN_8009c918(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80437e70) * FLOAT_80437ec4);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80437e7c,param_1);
  FUN_80067310((double)FLOAT_80437e98,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8009c9cc  zz_009c9cc_ ====

void zz_009c9cc_(undefined1 *param_1)

{
  int iVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = (int)(char)param_1[2];
  if (iVar1 < 9) {
    iVar4 = 0;
  }
  else {
    iVar4 = iVar1 + -8;
    iVar1 = 8;
  }
  puVar2 = zz_008893c_(2,(int)(char)param_1[4],0,iVar4);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x83] = 0x14;
    puVar5 = (undefined4 *)(puVar2 + 0x144);
    iVar4 = 0;
    puVar2[0x11] = *param_1;
    puVar2[0x12] = param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_8009cbc0;
    *(code **)(puVar2 + 0x10c) = FUN_800a0b34;
    puVar2[0x173] = param_1[3];
    puVar2[0x176] = PTR_DAT_80433930[0x29];
    puVar2[0x171] = param_1[5];
    do {
      if (iVar1 == 0) {
        *puVar5 = 0;
      }
      else {
        uVar3 = zz_0006d4c_();
        *puVar5 = uVar3;
        iVar1 = iVar1 + -1;
      }
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < 8);
  }
  return;
}



// ==== 8009cac0  zz_009cac0_ ====

void zz_009cac0_(void)

{
  char *pcVar1;
  
  pcVar1 = &DAT_802f644c;
  while( true ) {
    if (*pcVar1 < '\0') break;
    zz_009c9cc_(pcVar1);
    pcVar1 = pcVar1 + 6;
  }
  return;
}



// ==== 8009cb0c  zz_009cb0c_ ====

void zz_009cb0c_(void)

{
  char *pcVar1;
  
  pcVar1 = &DAT_802f65bc;
  while( true ) {
    if (*pcVar1 < '\0') break;
    zz_009c9cc_(pcVar1);
    pcVar1 = pcVar1 + 6;
  }
  return;
}



// ==== 8009cb58  zz_009cb58_ ====

undefined4 zz_009cb58_(int param_1)

{
  char cVar1;
  
  cVar1 = (&PTR_s_CKPT02_CP000_B_802f5c70)[param_1][0xd];
  if (cVar1 == 'C') {
    return 2;
  }
  if (cVar1 < 'C') {
    if (cVar1 == 'A') {
      return 0;
    }
    if ('@' < cVar1) {
      return 1;
    }
  }
  else if (cVar1 < 'E') {
    return 3;
  }
  return 0;
}



// ==== 8009cbc0  FUN_8009cbc0 ====

void FUN_8009cbc0(int param_1)

{
  (*(code *)(&PTR_FUN_802f6c20)[*(char *)(param_1 + 0x18)])();
  if (((*(char *)(param_1 + 0x18) < '\x02') && (PTR_DAT_80433934[0x45] == '\x05')) &&
     ('\x01' < (char)PTR_DAT_80433934[0x52])) {
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 8009cc48  FUN_8009cc48 ====

void FUN_8009cc48(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined *param_12,undefined4 *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *extraout_r4;
  undefined4 *extraout_r4_00;
  undefined4 *extraout_r4_01;
  undefined4 *extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 *extraout_r4_04;
  undefined4 *extraout_r4_05;
  undefined4 *extraout_r4_06;
  undefined4 *extraout_r4_07;
  undefined4 *puVar7;
  undefined4 *extraout_r4_08;
  undefined4 *extraout_r4_09;
  int iVar8;
  short *psVar9;
  int iVar10;
  int *piVar11;
  double dVar12;
  undefined8 uVar13;
  
  puVar7 = (undefined4 *)PTR_DAT_80433934;
  if (((char)PTR_DAT_80433934[0x45] < '\x03') && (*(char *)(param_9 + 0x11) != '\n')) {
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x96) = 0xff;
  *(undefined2 *)(param_9 + 0x94) = 0xffff;
  if (*(char *)(param_9 + 0x11) == '\x12') {
    if ((-1 < (char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0]) &&
       (*(char *)(&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0]] != '\0')
       ) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
  }
  else if (*(char *)(param_9 + 0x171) == '\0') {
    if ((char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0] < '\0') {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    pcVar5 = (char *)(&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0]];
    *(char *)(param_9 + 0x88) = pcVar5[0x88];
    if ((pcVar5 == (char *)0x0) || (*pcVar5 == '\0')) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    *(char **)(param_9 + 0x90) = pcVar5;
    *(char *)(param_9 + 0x96) = pcVar5[0x3e4];
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(pcVar5 + 1000);
    *(char *)(param_9 + 0x174) = pcVar5[0x491];
  }
  iVar8 = -1;
  *(undefined1 *)(param_9 + 0x82) = 0x11;
  *(undefined1 *)(param_9 + 0x172) = 0xff;
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    fVar1 = FLOAT_80437ec8;
    param_2 = (double)FLOAT_80437ec8;
    *(undefined1 *)(param_9 + 0x84) = 0x13;
    fVar2 = FLOAT_80437ecc;
    iVar6 = 0;
    dVar12 = (double)FLOAT_80437ecc;
    *(float *)(param_9 + 0x60) = fVar1;
    fVar3 = FLOAT_80437ed0;
    piVar11 = (int *)(param_9 + 0x144);
    *(float *)(param_9 + 0x5c) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    *(undefined2 *)(param_9 + 0x70) = 0;
    *(undefined2 *)(param_9 + 0x7c) = 0x444;
    *(float *)(param_9 + 100) = fVar2;
    *(float *)(param_9 + 0x68) = fVar2;
    *(float *)(param_9 + 0x6c) = fVar3;
    do {
      dVar12 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_804361fc,*piVar11,(int)*(char *)(param_9 + 0x12),param_12,
                                   param_13,iVar8,param_15,param_16);
      iVar6 = iVar6 + 1;
      piVar11 = piVar11 + 1;
    } while (iVar6 < 2);
    iVar6 = 2;
    piVar11 = (int *)(param_9 + 0x14c);
    do {
      dVar12 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_804361fc,*piVar11,*(char *)(param_9 + 0x12) * 2 + 2,param_12,
                                   param_13,iVar8,param_15,param_16);
      iVar6 = iVar6 + 1;
      piVar11 = piVar11 + 1;
    } while (iVar6 < 8);
    param_1 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0xe0),
                                  *(char *)(param_9 + 0x12) * 2 + 3,param_12,param_13,iVar8,param_15
                                  ,param_16);
    iVar10 = 1;
    iVar6 = param_9;
    do {
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(iVar6 + 0xe4),(int)*(char *)(param_9 + 0x12),param_12,param_13,iVar8,
                  param_15,param_16);
      zz_0007cd0_(*(int *)(iVar6 + 0xe4),0xff,0xe0,0);
      param_11 = (float *)0xe0;
      param_12 = (undefined *)0x0;
      param_1 = (double)zz_0007cf4_(*(int *)(iVar6 + 0xe4),0xff,0xe0,0);
      fVar1 = FLOAT_80437ec8;
      iVar10 = iVar10 + 1;
      iVar6 = iVar6 + 4;
    } while (iVar10 < 3);
    *(undefined1 *)(param_9 + 400) = *(undefined1 *)(param_9 + 0x12);
    *(float *)(param_9 + 0x17c) = fVar1;
    iVar6 = *(int *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x12) * 0x3c + 0x118);
    *(int *)(param_9 + 0x18c) = iVar6 + -1;
    *(int *)(param_9 + 0x184) = iVar6 + -1;
    puVar7 = extraout_r4;
    break;
  case 2:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    fVar1 = FLOAT_80437ecc;
    dVar12 = (double)FLOAT_80437ecc;
    *(undefined1 *)(param_9 + 0x84) = 9;
    fVar2 = FLOAT_80437ed4;
    *(float *)(param_9 + 100) = fVar1;
    *(float *)(param_9 + 0x68) = fVar1;
    *(float *)(param_9 + 0x6c) = fVar2;
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(undefined4 *)(*(int *)(param_9 + 0x14c) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x148) + 0x14) = 0xffffffff;
    *(undefined4 *)(*(int *)(param_9 + 0x144) + 0x14) = 0xffffffff;
    *(undefined1 *)(param_9 + 0x192) = 0xff;
    *(undefined1 *)(param_9 + 0x191) = 0xff;
    *(undefined1 *)(param_9 + 400) = 0xff;
    uVar13 = zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                         ,*(int *)(param_9 + 0x15c),0xf,param_12,param_13,iVar8,param_15,param_16);
    zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                *(int *)(param_9 + 0x160),0xe,param_12,param_13,iVar8,param_15,param_16);
    iVar6 = *(int *)(param_9 + 0x160);
    param_11 = (float *)0x0;
    param_12 = (undefined *)0x0;
    zz_0007cd0_(iVar6,0,0,0);
    param_1 = (double)zz_0007cac_((double)FLOAT_80437ed8,iVar6);
    *(undefined4 *)(param_9 + 0x188) = 0;
    iVar6 = *(int *)(PTR_DAT_80433934 + 0x4c) - *(int *)(param_9 + 0x188);
    if (iVar6 < 0x51) {
      *(undefined4 *)(param_9 + 0x18c) = 1;
    }
    else {
      iVar6 = iVar6 / 0x50 + (iVar6 >> 0x1f);
      *(int *)(param_9 + 0x18c) = (iVar6 - (iVar6 >> 0x1f)) + 1;
    }
    puVar7 = (undefined4 *)0x0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    if (PTR_DAT_80433934[0x50] != '\0') {
      *(undefined2 *)(param_9 + 0x74) = 0;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0x15c),0x71,param_12,param_13,iVar8,param_15,param_16);
      return;
    }
    break;
  case 5:
    param_11 = (float *)0x1;
    *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
    param_13 = (undefined4 *)(*(char *)(param_9 + 0x96) * 4);
    param_12 = (undefined *)(int)*(short *)(param_13[-0x1ff0ec5f] + 1000);
    *(short *)(param_9 + 0x94) = *(short *)(param_13[-0x1ff0ec5f] + 1000);
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    param_1 = (double)zz_0089100_(param_9,0x20,1);
    fVar1 = FLOAT_80437ecc;
    *(float *)(param_9 + 0x6c) = FLOAT_80437ecc;
    *(float *)(param_9 + 0x68) = fVar1;
    *(float *)(param_9 + 100) = fVar1;
    *(undefined1 *)(param_9 + 0x84) = 1;
    puVar7 = extraout_r4_00;
    break;
  case 6:
    *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
    *(undefined2 *)(param_9 + 0x94) =
         *(undefined2 *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 1000);
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    fVar2 = FLOAT_80437edc;
    fVar1 = FLOAT_80437ec8;
    dVar12 = (double)FLOAT_80437ec8;
    param_11 = (float *)0x19;
    iVar6 = *(char *)(param_9 + 0x12) * 0xc;
    param_13 = (undefined4 *)(&DAT_802f5ef0 + iVar6);
    param_12 = (undefined *)*param_13;
    uVar4 = *(undefined4 *)(&DAT_802f5ef4 + iVar6);
    *(undefined **)(param_9 + 100) = param_12;
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f5ef8 + iVar6);
    *(float *)(param_9 + 0x60) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    *(float *)(param_9 + 0x5c) = fVar2;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 0xffff;
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    param_1 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0xe0),0x19,param_12,param_13,iVar8
                                  ,param_15,param_16);
    *(undefined1 *)(param_9 + 0x1a5) = 1;
    *(undefined1 *)(param_9 + 0x1a6) = 0;
    puVar7 = extraout_r4_01;
    break;
  case 7:
    *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    fVar2 = FLOAT_80437edc;
    fVar1 = FLOAT_80437ec8;
    param_13 = (undefined4 *)&DAT_802f65d0;
    param_2 = (double)FLOAT_80437ec8;
    puVar7 = (undefined4 *)0x0;
    param_1 = (double)FLOAT_80437edc;
    *(float *)(param_9 + 0x60) = FLOAT_80437ec8;
    fVar3 = FLOAT_80437ee0;
    *(float *)(param_9 + 0x58) = fVar1;
    *(float *)(param_9 + 0x5c) = fVar2;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(undefined4 *)(param_9 + 100) =
         *(undefined4 *)
          (&DAT_802f65d0 + *(char *)(param_9 + 0x12) * 8 + *(char *)(param_9 + 0x173) * 0x10);
    param_12 = &DAT_802f65d0 + *(char *)(param_9 + 0x173) * 0x10;
    param_11 = (float *)(param_12 + *(char *)(param_9 + 0x12) * 8);
    *(float *)(param_9 + 0x68) = param_11[1];
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 400) = 1;
    *(undefined1 *)(param_9 + 0x191) = 0xff;
    *(undefined2 *)(param_9 + 0x17a) = 0xffff;
    break;
  case 8:
    *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
    param_13 = (undefined4 *)(*(char *)(param_9 + 0x96) * 4);
    param_12 = (undefined *)(int)*(short *)(param_13[-0x1ff0ec5f] + 1000);
    *(short *)(param_9 + 0x94) = *(short *)(param_13[-0x1ff0ec5f] + 1000);
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    iVar6 = 0;
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    fVar3 = FLOAT_80437ee4;
    fVar2 = FLOAT_80437ecc;
    param_2 = (double)FLOAT_80437ecc;
    param_1 = (double)FLOAT_80437ee4;
    iVar10 = 0;
    *(float *)(param_9 + 0x68) = FLOAT_80437ecc;
    fVar1 = FLOAT_80437ec8;
    piVar11 = (int *)(param_9 + 0x144);
    *(float *)(param_9 + 100) = fVar2;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(float *)(param_9 + 0x60) = fVar1;
    *(float *)(param_9 + 0x5c) = fVar1;
    *(float *)(param_9 + 0x58) = fVar1;
    *(undefined2 *)(param_9 + 0x70) = 0;
    *(undefined2 *)(param_9 + 0x7c) = 0x1000;
    *(float *)(param_9 + 0x17c) = fVar1;
    do {
      param_11 = (float *)(int)*(short *)(&DAT_802f5f94 + iVar10 + *(char *)(param_9 + 0x12) * 8);
      param_1 = (double)zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    DAT_804361fc,*piVar11,(int)param_11,param_12,param_13,iVar8,
                                    param_15,param_16);
      iVar6 = iVar6 + 1;
      piVar11 = piVar11 + 1;
      iVar10 = iVar10 + 2;
      puVar7 = extraout_r4_02;
    } while (iVar6 < 4);
    break;
  case 9:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    iVar6 = *(char *)(param_9 + 0x12) * 0x18;
    uVar13 = zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    param_1 = (double)zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0x144),
                                  *(int *)(&DAT_802f6b90 + iVar6),param_12,param_13,iVar8,param_15,
                                  param_16);
    param_11 = *(float **)(&DAT_802f6b9c + iVar6);
    uVar4 = *(undefined4 *)(&DAT_802f6ba0 + iVar6);
    *(float **)(param_9 + 100) = param_11;
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f6ba4 + iVar6);
    *(short *)(param_9 + 0x1c) = (short)*(undefined4 *)(&DAT_802f6b94 + iVar6);
    puVar7 = *(undefined4 **)(&DAT_802f6b98 + iVar6);
    *(short *)(param_9 + 0x1e) = (short)puVar7;
    *(undefined **)(param_9 + 0x54) = &DAT_802f6bf0;
    *(undefined1 *)(param_9 + 0x82) = 0;
    break;
  case 10:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    uVar13 = zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 1;
    iVar6 = *(char *)(param_9 + 0x173) * 0xc;
    uVar4 = *(undefined4 *)(&DAT_802f6348 + iVar6);
    *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f6344 + iVar6);
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f634c + iVar6);
    uVar13 = zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                         ,*(int *)(param_9 + 0x144),0x39,param_12,param_13,iVar8,param_15,param_16);
    param_11 = (float *)0x3a;
    zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                *(int *)(param_9 + 0x148),0x3a,param_12,param_13,iVar8,param_15,param_16);
    uVar13 = zz_00086b8_((double)FLOAT_80437ecc,param_2,param_3,param_4,param_5,param_6,param_7,
                         param_8,DAT_804361fc,*(int *)(param_9 + 0x148),param_11,param_12,param_13,
                         iVar8,param_15,param_16);
    param_1 = (double)zz_0007c30_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  *(int *)(param_9 + 0x148),extraout_r4_03,param_11,param_12,
                                  param_13,iVar8,param_15,param_16);
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    puVar7 = extraout_r4_04;
    break;
  case 0xb:
    *(code **)(param_9 + 0x100) = FUN_80012274;
    zz_0089100_(param_9,0x21,1);
    fVar1 = FLOAT_80437ee8;
    *(undefined1 *)(param_9 + 0x84) = 1;
    fVar2 = FLOAT_80437eec;
    *(float *)(param_9 + 100) = fVar1;
    fVar3 = FLOAT_80437ef0;
    dVar12 = (double)FLOAT_80437ef0;
    *(float *)(param_9 + 0x68) = fVar2;
    fVar1 = FLOAT_80437ecc;
    *(float *)(param_9 + 0x6c) = fVar3;
    *(float *)(param_9 + 0x16c) = fVar1;
    *(float *)(param_9 + 0x168) = fVar1;
    *(float *)(param_9 + 0x164) = fVar1;
    if ((*(byte *)(param_9 + 0x173) & 2) != 0) {
      *(float *)(param_9 + 0x168) = FLOAT_80437ef4;
    }
    if ((*(byte *)(param_9 + 0x173) & 1) != 0) {
      *(float *)(param_9 + 0x164) = FLOAT_80437ef8;
    }
    piVar11 = (int *)(param_9 + 0x144);
    psVar9 = &DAT_802f6334;
    iVar6 = 0;
    do {
      dVar12 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_804361fc,*piVar11,(int)*psVar9,param_12,param_13,iVar8,
                                   param_15,param_16);
      iVar6 = iVar6 + 1;
      piVar11 = piVar11 + 1;
      psVar9 = psVar9 + 1;
    } while (iVar6 < 8);
    param_11 = (float *)0x56;
    param_1 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0xe0),0x56,param_12,param_13,iVar8
                                  ,param_15,param_16);
    puVar7 = extraout_r4_05;
    break;
  case 0xc:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    fVar1 = FLOAT_80437ecc;
    dVar12 = (double)FLOAT_80437ecc;
    *(undefined1 *)(param_9 + 0x84) = 1;
    fVar2 = FLOAT_80437efc;
    param_11 = (float *)0x18;
    *(float *)(param_9 + 100) = fVar1;
    *(float *)(param_9 + 0x68) = fVar1;
    *(float *)(param_9 + 0x6c) = fVar2;
    param_1 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0x144),0x18,param_12,param_13,
                                  iVar8,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 0x11;
    puVar7 = extraout_r4_06;
    break;
  case 0xe:
    param_1 = (double)zz_009f3e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_9);
    puVar7 = extraout_r4_07;
    break;
  case 0xf:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    param_11 = (float *)0x1;
    param_1 = (double)zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 1;
    iVar6 = *(char *)(param_9 + 0x173) * 0xc;
    puVar7 = (undefined4 *)(&DAT_802f63bc + iVar6);
    uVar4 = *(undefined4 *)(&DAT_802f63c0 + iVar6);
    *(undefined4 *)(param_9 + 100) = *puVar7;
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f63c4 + iVar6);
    break;
  case 0x10:
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    uVar13 = zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x84) = 1;
    puVar7 = (undefined4 *)
             (*(char *)(param_9 + 0x173) * 0x18 + -0x7fd09c14 + *(char *)(param_9 + 0x12) * 0xc);
    uVar4 = puVar7[1];
    *(undefined4 *)(param_9 + 100) = *puVar7;
    *(undefined4 *)(param_9 + 0x68) = uVar4;
    *(undefined4 *)(param_9 + 0x6c) = puVar7[2];
    uVar13 = zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc
                         ,*(int *)(param_9 + 0x144),0x3c,param_12,param_13,iVar8,param_15,param_16);
    param_11 = (float *)(*(char *)(param_9 + 0x12) + 0x66);
    param_1 = (double)zz_0006fb4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_804361fc,*(int *)(param_9 + 0x148),(int)param_11,param_12,
                                  param_13,iVar8,param_15,param_16);
    puVar7 = extraout_r4_08;
    break;
  case 0x12:
    param_11 = (float *)0x50;
    uVar13 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_804361fc,*(int *)(param_9 + 0x144),0x50,param_12,param_13,0xffffffff,
                         param_15,param_16);
    uVar13 = zz_0007908_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0x144),(undefined4 *)(param_9 + 0x20),param_11,param_12,
                         param_13,iVar8,param_15,param_16);
    if ((*(byte *)(param_9 + 0x173) & 1) == 0) {
      *(float *)(param_9 + 0x20) = -*(float *)(param_9 + 0x20);
    }
    if ((*(byte *)(param_9 + 0x173) & 2) != 0) {
      *(float *)(param_9 + 0x24) = -*(float *)(param_9 + 0x24);
    }
    param_1 = (double)zz_0007834_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  *(int *)(param_9 + 0x144),(undefined4 *)(param_9 + 0x20),
                                  (char *)param_11,param_12,param_13,iVar8,param_15,param_16);
    puVar7 = extraout_r4_09;
  }
  zz_009f0c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(int)puVar7,
              param_11,param_12,param_13,iVar8,param_15,param_16);
  return;
}



// ==== 8009d6bc  FUN_8009d6bc ====

/* WARNING: Removing unreachable block (ram,0x8009da68) */
/* WARNING: Removing unreachable block (ram,0x8009da60) */
/* WARNING: Removing unreachable block (ram,0x8009d6d4) */
/* WARNING: Removing unreachable block (ram,0x8009d6cc) */

void FUN_8009d6bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,int param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined1 uVar1;
  float fVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  char *pcVar6;
  float *pfVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  int *piVar14;
  int iVar15;
  double dVar16;
  double dVar17;
  undefined8 uVar18;
  double dVar19;
  double dVar20;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  iVar5 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  if (*(char *)(iVar5 + 0x18) == '\x01') {
    if (*(char *)(param_9 + 0x172) != '\0') {
      *(short *)(param_9 + 0x94) = (short)*(char *)(iVar5 + 0x11);
      *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(iVar5 + 0x3e4);
      param_14 = *(int *)(iVar5 + 0x4ac);
      *(undefined1 *)(param_9 + 0x172) = 0;
      cVar4 = *(char *)(iVar5 + 0x7cd);
      *(char *)(param_9 + 0x17a) = cVar4;
      dVar17 = DOUBLE_80437f10;
      uVar8 = DAT_802b1534;
      uVar10 = DAT_802b1530;
      if (cVar4 == '\0') {
        local_68 = DAT_802b1530;
        piVar14 = (int *)(param_9 + 0x144);
        local_64 = DAT_802b1534;
        dVar20 = (double)FLOAT_80437f00;
        local_60 = DAT_802b1538;
        dVar16 = (double)FLOAT_80437f04;
        uVar1 = *(undefined1 *)(param_14 + 0x9f);
        local_58 = 0x43300000;
        *(undefined1 *)(param_9 + 0x17c) = uVar1;
        *(undefined1 *)(param_9 + 0x17b) = uVar1;
        uStack_54 = (int)*(char *)(param_9 + 0x17b) - 1U ^ 0x80000000;
        param_2 = (double)(float)(dVar20 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                          dVar17));
        dVar19 = -(double)(float)(param_2 * dVar16 -
                                 (double)*(float *)(&DAT_802f5ec0 + *(char *)(param_9 + 0x173) * 0xc
                                                   ));
        iVar5 = param_9;
        for (uVar13 = 0; (int)uVar13 < (int)*(char *)(param_9 + 0x17b); uVar13 = uVar13 + 1) {
          if ((int)uVar13 < 8) {
            iVar9 = *piVar14;
          }
          else {
            iVar9 = *(int *)(iVar5 + 0xc0);
          }
          pcVar6 = (char *)0x17;
          uVar18 = zz_0006fb4_(dVar16,param_2,dVar17,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar9,0x17,uVar8,uVar10,param_14,param_15,param_16);
          uVar3 = uVar13 & 1;
          *(float *)(&DAT_802f5e90 + ((*(byte *)(param_9 + 0x173) & 2) + uVar3) * 0xc) =
               (float)dVar19;
          uVar18 = zz_0007834_(uVar18,param_2,dVar17,param_4,param_5,param_6,param_7,param_8,iVar9,
                               (undefined4 *)
                               (&DAT_802f5e90 + ((*(byte *)(param_9 + 0x173) & 2) + uVar3) * 0xc),
                               pcVar6,uVar8,uVar10,param_14,param_15,param_16);
          zz_0007ae4_(uVar18,param_2,dVar17,param_4,param_5,param_6,param_7,param_8,iVar9,&local_68,
                      pcVar6,uVar8,uVar10,param_14,param_15,param_16);
          fVar2 = FLOAT_80437f0c;
          if (uVar3 != 0) {
            fVar2 = FLOAT_80437f08;
          }
          dVar16 = (double)zz_0007e74_((double)fVar2,param_2,dVar17,param_4,param_5,param_6,param_7,
                                       param_8,iVar9,extraout_r4,pcVar6,uVar8,uVar10,param_14,
                                       param_15,param_16);
          dVar19 = (double)(float)(dVar19 + dVar20);
          iVar5 = iVar5 + 4;
          piVar14 = piVar14 + 1;
        }
        *(undefined1 *)(param_9 + 0x17c) = 0xff;
        param_13 = uVar10;
        param_3 = dVar17;
      }
      else {
        pcVar6 = (char *)0x16;
        uVar18 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_804361fc,*(int *)(param_9 + 0x144),0x16,param_12,param_13,param_14,
                             param_15,param_16);
        zz_0007834_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x144),
                    (undefined4 *)(&DAT_802f5ec0 + *(char *)(param_9 + 0x173) * 0xc),pcVar6,param_12
                    ,param_13,param_14,param_15,param_16);
      }
    }
    iVar5 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
    iVar9 = *(int *)(iVar5 + 0x4ac);
    *(undefined1 *)(param_9 + 0x170) = 0;
    dVar17 = DOUBLE_80437f10;
    if (((*(byte *)(iVar5 + 0x7d5) & 1) == 0) &&
       (pfVar7 = (float *)0x1,
       ((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) != 0)) {
      if (*(char *)(iVar5 + 0x7cd) == '\0') {
        if (*(char *)(iVar5 + 0x747) == '\0') {
          *(undefined1 *)(param_9 + 0x17c) = 0xff;
        }
        else {
          *(undefined1 *)(param_9 + 0x170) = 1;
          cVar4 = *(char *)(param_9 + 0x17b) - *(char *)(iVar5 + 0x747);
          iVar5 = (int)cVar4;
          if (iVar5 != *(char *)(param_9 + 0x17c)) {
            *(undefined1 *)(param_9 + 0x17d) = 0x1e;
            *(char *)(param_9 + 0x17c) = cVar4;
          }
          if (*(char *)(param_9 + 0x17d) != '\0') {
            *(char *)(param_9 + 0x17d) = *(char *)(param_9 + 0x17d) + -1;
          }
          piVar14 = (int *)(param_9 + 0x144);
          iVar12 = param_9;
          for (iVar11 = 0; iVar11 < *(char *)(param_9 + 0x17b); iVar11 = iVar11 + 1) {
            if (iVar11 < 8) {
              iVar15 = *piVar14;
            }
            else {
              iVar15 = *(int *)(iVar12 + 0xc0);
            }
            if (iVar5 < iVar11) {
              dVar17 = (double)FLOAT_80437ec8;
            }
            else if (iVar5 == iVar11) {
              dVar17 = (double)FLOAT_80437ec8;
            }
            else {
              dVar17 = (double)FLOAT_80437ecc;
            }
            uVar18 = zz_00086b8_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_804361fc,iVar15,pfVar7,iVar9,param_13,param_14,param_15,
                                 param_16);
            zz_0007c30_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar15,
                        extraout_r4_00,pfVar7,iVar9,param_13,param_14,param_15,param_16);
            iVar12 = iVar12 + 4;
            piVar14 = piVar14 + 1;
          }
        }
      }
      else {
        uStack_54 = (int)*(short *)(iVar5 + 0x736) ^ 0x80000000;
        local_58 = 0x43300000;
        uStack_4c = (int)*(short *)(iVar9 + 4) ^ 0x80000000;
        dVar20 = (double)FLOAT_80437ec8;
        dVar19 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80437f10);
        local_50 = 0x43300000;
        dVar16 = (double)(float)(dVar20 - (double)(float)(dVar19 / (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_4c) - DOUBLE_80437f10)));
        if ((double)FLOAT_80437ecc != dVar16) {
          iVar5 = *(int *)(param_9 + 0x144);
          *(undefined1 *)(param_9 + 0x170) = 1;
          uVar18 = zz_00086b8_(dVar16,dVar19,dVar17,dVar20,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,1,iVar9,param_13,param_14,param_15,param_16);
          zz_0007c30_(uVar18,dVar19,dVar17,dVar20,param_5,param_6,param_7,param_8,iVar5,
                      extraout_r4_01,pfVar7,iVar9,param_13,param_14,param_15,param_16);
        }
      }
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  return;
}



// ==== 8009da84  zz_009da84_ ====

undefined4 zz_009da84_(int param_1,int param_2)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  bool bVar6;
  
  uVar5 = 0;
  if (*(char *)(param_2 + 0x11) == '\a') {
    *(undefined1 *)(param_2 + 400) = 0;
  }
  else {
    *(undefined1 *)(param_2 + 0x1a5) = 0;
  }
  fVar4 = FLOAT_80437ec8;
  cVar1 = *(char *)(param_2 + 0x19);
  if (cVar1 == '\x02') {
    uVar5 = 1;
    bVar6 = false;
    if (*(char *)(param_2 + 0x11) == '\x06') {
      cVar1 = *(char *)(param_2 + 0x1a3);
    }
    else {
      cVar1 = *(char *)(param_2 + 0x18b);
    }
    if (*(char *)(param_1 + 0x18) < '\x02') {
      if (*(char *)(param_1 + 0x3f0) != cVar1) {
        bVar6 = true;
        *(undefined2 *)(param_2 + 0x178) = 0;
        if (*(char *)(param_2 + 0x11) == '\x06') {
          *(undefined1 *)(param_2 + 0x1a4) = 1;
          *(undefined1 *)(param_2 + 0x1a3) = *(undefined1 *)(param_1 + 0x3f0);
          uVar2 = *(undefined2 *)(param_1 + 0x1c6);
          *(undefined2 *)(param_2 + 0x194) = uVar2;
          *(undefined2 *)(param_2 + 0x1a0) = uVar2;
          *(undefined2 *)(param_2 + 0x19c) = uVar2;
        }
        else {
          *(undefined1 *)(param_2 + 0x18c) = 1;
          *(undefined1 *)(param_2 + 0x18b) = *(undefined1 *)(param_1 + 0x3f0);
        }
      }
    }
    else {
      bVar6 = true;
      if (*(char *)(param_1 + 0x4a0) == '\0') {
        *(undefined2 *)(param_2 + 0x178) = 0x1e;
      }
      else {
        *(undefined2 *)(param_2 + 0x178) = 0;
      }
      if (*(char *)(param_2 + 0x11) == '\x06') {
        *(undefined1 *)(param_2 + 0x1a4) = 0;
      }
      else {
        *(undefined1 *)(param_2 + 0x18c) = 0;
      }
    }
    if (bVar6) {
      *(char *)(param_2 + 0x19) = *(char *)(param_2 + 0x19) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if (*(char *)(param_2 + 0x11) == '\a') {
        *(undefined1 *)(param_2 + 400) = 1;
      }
      else {
        *(undefined1 *)(param_2 + 0x1a5) = 1;
      }
      fVar3 = FLOAT_80437f18;
      fVar4 = FLOAT_80437edc;
      if (*(char *)(param_1 + 0x18) == '\x01') {
        uVar5 = 1;
        *(char *)(param_2 + 0x19) = *(char *)(param_2 + 0x19) + '\x01';
        *(float *)(param_2 + 0x5c) = fVar4;
        *(float *)(param_2 + 0x3c) = fVar3;
        if (*(char *)(param_2 + 0x11) == '\x06') {
          *(undefined1 *)(param_2 + 0x1a4) = 0;
          *(undefined1 *)(param_2 + 0x1a3) = *(undefined1 *)(param_1 + 0x3f0);
        }
        else {
          *(undefined1 *)(param_2 + 0x18c) = 0;
          *(undefined1 *)(param_2 + 0x18b) = *(undefined1 *)(param_1 + 0x3f0);
        }
      }
    }
    else if (-1 < cVar1) {
      uVar5 = 1;
      fVar3 = *(float *)(param_2 + 0x5c) + *(float *)(param_2 + 0x3c);
      bVar6 = FLOAT_80437ec8 < fVar3;
      *(float *)(param_2 + 0x5c) = fVar3;
      if (bVar6) {
        *(char *)(param_2 + 0x19) = *(char *)(param_2 + 0x19) + '\x01';
        *(float *)(param_2 + 0x5c) = fVar4;
      }
    }
  }
  else if (cVar1 < '\x04') {
    uVar5 = 1;
    if (*(short *)(param_2 + 0x178) == 0) {
      fVar4 = *(float *)(param_2 + 0x5c) - *(float *)(param_2 + 0x3c);
      bVar6 = fVar4 < FLOAT_80437ecc;
      *(float *)(param_2 + 0x5c) = fVar4;
      fVar4 = FLOAT_80437edc;
      if (bVar6) {
        *(undefined1 *)(param_2 + 0x19) = 0;
        *(float *)(param_2 + 0x5c) = fVar4;
        if (*(char *)(param_2 + 0x11) == '\a') {
          *(undefined1 *)(param_2 + 400) = 1;
        }
        else {
          *(undefined1 *)(param_2 + 0x1a5) = 1;
        }
      }
    }
    else {
      *(short *)(param_2 + 0x178) = *(short *)(param_2 + 0x178) + -1;
    }
  }
  return uVar5;
}



// ==== 8009dce4  FUN_8009dce4 ====

/* WARNING: Removing unreachable block (ram,0x8009e114) */
/* WARNING: Removing unreachable block (ram,0x8009dcf4) */

void FUN_8009dce4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  short sVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int *piVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  undefined8 local_58;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x1a6) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x1a6) != '\0') && (*(char *)(param_9 + 0x1a5) != '\0')) {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x1a6) = 0;
    *(undefined1 *)(param_9 + 0x172) = 1;
  }
  iVar10 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  uVar4 = zz_009da84_(iVar10,param_9);
  *(char *)(param_9 + 0x170) = (char)uVar4;
  if ((*(char *)(param_9 + 0x1a4) == '\0') && (*(char *)(param_9 + 0x1a6) < '\x01')) {
    if ((*(short *)(param_9 + 0x194) != *(short *)(iVar10 + 0x1c6)) ||
       (*(char *)(param_9 + 0x172) != '\0')) {
      *(short *)(param_9 + 0x194) = *(short *)(iVar10 + 0x1c6);
      param_2 = DOUBLE_80437f10;
      local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar10 + 0x1c6)) ^ 0x80000000);
      param_1 = (double)(float)(local_58 - DOUBLE_80437f10);
      *(float *)(param_9 + 0x198) =
           (float)(param_1 /
                  (double)(float)((double)CONCAT44(0x43300000,
                                                   (int)*(short *)(iVar10 + 0x1c4) ^ 0x80000000) -
                                 DOUBLE_80437f10));
    }
    sVar3 = *(short *)(param_9 + 0x194);
    if ((*(short *)(param_9 + 0x19c) != sVar3) || (*(char *)(param_9 + 0x172) != '\0')) {
      if (*(char *)(param_9 + 0x172) != '\0') {
        *(short *)(param_9 + 0x1a0) = sVar3;
        *(short *)(param_9 + 0x19c) = sVar3;
      }
      if (*(short *)(param_9 + 0x194) != *(short *)(param_9 + 0x1a0)) {
        *(short *)(param_9 + 0x1a0) = *(short *)(param_9 + 0x194);
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (sVar3 < 0) {
          sVar3 = -sVar3;
        }
        iVar10 = (int)sVar3;
        if (iVar10 < 0x1f) {
          *(undefined2 *)(param_9 + 0x19e) = 1;
        }
        else {
          iVar10 = iVar10 / 0x1e + (iVar10 >> 0x1f);
          *(short *)(param_9 + 0x19e) = ((short)iVar10 - (short)(iVar10 >> 0x1f)) + 1;
        }
      }
      if (*(short *)(param_9 + 0x194) < *(short *)(param_9 + 0x19c)) {
        sVar3 = *(short *)(param_9 + 0x19c) - *(short *)(param_9 + 0x194);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) - sVar3;
      }
      if (*(short *)(param_9 + 0x19c) < *(short *)(param_9 + 0x194)) {
        sVar3 = *(short *)(param_9 + 0x194) - *(short *)(param_9 + 0x19c);
        if (*(short *)(param_9 + 0x19e) < sVar3) {
          sVar3 = *(short *)(param_9 + 0x19e);
        }
        *(short *)(param_9 + 0x19c) = *(short *)(param_9 + 0x19c) + sVar3;
      }
      iVar10 = (int)*(short *)(param_9 + 0x19c);
      if (9999 < iVar10) {
        iVar10 = 9999;
        *(undefined2 *)(param_9 + 0x19c) = 9999;
      }
      piVar13 = &DAT_802f5f50;
      piVar14 = (int *)(param_9 + 0x144);
      iVar12 = 0;
      iVar11 = 0;
      uVar7 = 1000;
      do {
        uVar6 = iVar10 / (int)uVar7;
        if (((uVar6 != 0) || (uVar7 == 1)) || (iVar11 != 0)) {
          if (iVar11 == 0) {
            *(short *)(param_9 + 0x196) = 4 - (short)iVar12;
          }
          iVar9 = *piVar14;
          iVar8 = piVar14[4];
          uVar15 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar9,*piVar13,param_12,param_13,param_14,param_15,
                               param_16);
          pfVar5 = (float *)piVar13[4];
          zz_0006fb4_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                      iVar8,(int)pfVar5,param_12,param_13,param_14,param_15,param_16);
          zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) -
                                     DOUBLE_80437f10),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_804361fc,iVar9,pfVar5,param_12,param_13,param_14,param_15,
                      param_16);
          local_58 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
          uVar15 = zz_00086b8_((double)(float)(local_58 - DOUBLE_80437f10),param_2,param_3,param_4,
                               param_5,param_6,param_7,param_8,DAT_804361fc,iVar8,pfVar5,param_12,
                               param_13,param_14,param_15,param_16);
          uVar15 = zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,
                               extraout_r4,pfVar5,param_12,param_13,param_14,param_15,param_16);
          param_1 = (double)zz_0007c30_(uVar15,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,iVar8,extraout_r4_00,pfVar5,param_12,param_13,
                                        param_14,param_15,param_16);
          piVar14 = piVar14 + 1;
          piVar13 = piVar13 + 1;
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 - (iVar10 / (int)uVar7) * uVar7;
        }
        iVar12 = iVar12 + 1;
        uVar7 = uVar7 / 10;
      } while (iVar12 < 4);
    }
    fVar1 = FLOAT_80437f1c;
    bVar2 = false;
    *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
    if (*(float *)(param_9 + 0x198) <= fVar1) {
      bVar2 = true;
      if ((*(ushort *)(param_9 + 0x1c) & 8) == 0) {
        *(undefined1 *)(param_9 + 0x1a2) = 1;
      }
      else {
        *(undefined1 *)(param_9 + 0x1a2) = 0;
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x1a2) = 0;
    }
    fVar1 = FLOAT_80437ecc;
    if (bVar2) {
      fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x1a2) ^ 0x80000001) -
                     DOUBLE_80437f10);
    }
    dVar16 = (double)fVar1;
    iVar10 = *(int *)(param_9 + 0xe0);
    dVar17 = (double)(float)((double)FLOAT_80437f30 * dVar16 + (double)FLOAT_80437ed8);
    zz_0007cd0_(iVar10,(int)(DOUBLE_80437f20 * dVar16) & 0xff,
                (int)(DOUBLE_80437f20 * DOUBLE_80437f28 * dVar16) & 0xff,0);
    zz_0007cac_(dVar17,iVar10);
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 8009e130  zz_009e130_ ====

void zz_009e130_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar2;
  short *psVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (*(short *)(param_11 + 2) == 0) {
    *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  }
  else {
    iVar1 = (int)*param_12;
    if (*(short *)(param_9 + 0x17a) != iVar1) {
      local_58 = DAT_802b153c;
      local_54 = DAT_802b1540;
      local_50 = DAT_802b1544;
      if (999 < iVar1) {
        iVar1 = 999;
      }
      *(short *)(param_9 + 0x17a) = (short)iVar1;
      iVar8 = 0;
      iVar7 = 0;
      uVar9 = 100;
      psVar3 = param_12;
      do {
        uVar4 = iVar1 / (int)uVar9;
        if (((uVar4 != 0) || (uVar9 == 1)) || (iVar7 != 0)) {
          if (iVar7 == 0) {
            *(short *)(param_9 + 0x17c) = 3 - (short)iVar8;
          }
          pfVar2 = (float *)0x13;
          iVar6 = param_9 + (2 - iVar8) * 4;
          iVar5 = *(int *)(iVar6 + 0xe0);
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x13,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_44 = uVar4 ^ 0x80000000;
          local_48 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_44) -
                                              DOUBLE_80437f10),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                               extraout_r4,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar5 = *(int *)(iVar6 + 0xec);
          pfVar2 = (float *)0x15;
          uVar10 = zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,iVar5,0x15,psVar3,param_13,param_14,param_15,param_16);
          zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,&local_58
                      ,(char *)pfVar2,psVar3,param_13,param_14,param_15,param_16);
          uStack_3c = uVar4 ^ 0x80000000;
          local_40 = 0x43300000;
          uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) -
                                              DOUBLE_80437f10),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar2,psVar3,param_13,
                               param_14,param_15,param_16);
          param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5
                                ,extraout_r4_00,pfVar2,psVar3,param_13,param_14,param_15,param_16);
          iVar7 = iVar7 + 1;
          iVar1 = iVar1 - (iVar1 / (int)uVar9) * uVar9;
        }
        iVar8 = iVar8 + 1;
        uVar9 = uVar9 / 10;
      } while (iVar8 < 3);
      if (*(char *)(param_9 + 0x172) == '\0') {
        if (*(short *)(param_11 + 4) == 1) {
          if (*param_12 < param_12[1]) {
            *(undefined2 *)(param_9 + 0x17e) = 10;
          }
        }
        else if (*param_12 < *(short *)(param_11 + 2)) {
          *(undefined2 *)(param_9 + 0x17e) = 10;
        }
      }
      else {
        *(undefined2 *)(param_9 + 0x17e) = 0;
        *(undefined2 *)(param_9 + 0x182) = 0;
      }
      pfVar2 = (float *)0x43300000;
      uStack_3c = (int)*(short *)(param_9 + 0x17a) ^ 0x80000000;
      iVar1 = *(int *)(param_9 + 0x154);
      uStack_44 = (int)*(short *)(param_11 + 2) ^ 0x80000000;
      local_40 = 0x43300000;
      dVar12 = (double)FLOAT_80437ec8;
      local_48 = 0x43300000;
      dVar11 = DOUBLE_80437f10;
      uVar10 = zz_00086b8_((double)(float)(dVar12 - (double)((float)((double)CONCAT44(0x43300000,
                                                                                      uStack_3c) -
                                                                    DOUBLE_80437f10) /
                                                            (float)((double)CONCAT44(0x43300000,
                                                                                     uStack_44) -
                                                                   DOUBLE_80437f10))),
                           DOUBLE_80437f10,dVar12,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar1,0x43300000,psVar3,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,dVar12,param_4,param_5,param_6,param_7,param_8,iVar1,extraout_r4_01,
                  pfVar2,psVar3,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8009e388  zz_009e388_ ====

void zz_009e388_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  float local_28;
  float local_24;
  float local_20;
  
  iVar5 = *(int *)(param_9 + 0x15c);
  iVar2 = *(char *)(param_9 + 399) * 4;
  iVar4 = param_10 + iVar2;
  pfVar3 = (float *)(*(int *)(param_10 + 0x4ac) + iVar2);
  uVar6 = zz_00086b8_((double)(*(float *)(iVar4 + 0x648) / pfVar3[0x61]),param_2,param_3,param_4,
                      param_5,param_6,param_7,param_8,DAT_804361fc,iVar5,pfVar3,iVar4,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4,pfVar3
              ,iVar4,param_13,param_14,param_15,param_16);
  iVar5 = *(int *)(param_9 + 0x160);
  iVar2 = *(char *)(param_9 + 399) * 4;
  if (*(float *)(param_10 + iVar2 + 0x648) == *(float *)(*(int *)(param_10 + 0x4ac) + iVar2 + 0x184)
     ) {
    *(undefined1 *)(iVar5 + 0x10) = 1;
    if (*(char *)(param_9 + 0x18e) == '\0') {
      *(undefined2 *)(param_9 + 0x186) = 0;
      *(undefined2 *)(param_9 + 0x188) = 0;
    }
    else {
      *(short *)(param_9 + 0x186) = *(short *)(param_9 + 0x186) + 0x444;
      *(short *)(param_9 + 0x188) = *(short *)(param_9 + 0x188) + 1;
    }
    *(undefined1 *)(param_9 + 0x18e) = 1;
    fVar1 = FLOAT_80437f34;
    if ((*(ushort *)(param_9 + 0x188) & 4) != 0) {
      fVar1 = FLOAT_80437ec8;
    }
    uVar6 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_804361fc,iVar5,pfVar3,iVar4,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,extraout_r4_00,
                pfVar3,iVar4,param_13,param_14,param_15,param_16);
    local_20 = FLOAT_80437ec8;
    dVar7 = zz_0045238_(*(short *)(param_9 + 0x186));
    local_28 = (float)((double)FLOAT_80437f3c * dVar7 + (double)FLOAT_80437f38);
    local_24 = local_28;
    zz_0007ae4_(dVar7,(double)FLOAT_80437f3c,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                &local_28,(char *)pfVar3,iVar4,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined1 *)(iVar5 + 0x10) = 0;
    *(undefined1 *)(param_9 + 0x18e) = 0;
  }
  return;
}



// ==== 8009e4dc  FUN_8009e4dc ====

/* WARNING: Removing unreachable block (ram,0x8009e8c8) */
/* WARNING: Removing unreachable block (ram,0x8009e4ec) */

int FUN_8009e4dc(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short sVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  float *pfVar4;
  char *pcVar5;
  short *psVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  undefined4 auStack_58 [2];
  float local_50;
  undefined8 local_48;
  undefined4 local_40;
  uint uStack_3c;
  double local_38;
  
  sVar2 = *(short *)(param_11 + 1);
  iVar9 = 0;
  if (sVar2 == 1) {
    dVar11 = (double)*(float *)(param_12 + 2);
    if ((double)FLOAT_80437ecc < dVar11) {
      iVar8 = *(int *)(param_9 + 0x154);
      pfVar4 = (float *)((int)*(short *)((int)param_11 + 2) * (int)*(short *)((int)param_11 + 6));
      local_48 = (double)(CONCAT44(0x43300000,pfVar4) ^ 0x80000000);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80437f10));
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_01
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar8 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_02
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      if (*param_12 == 0) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
        if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
          *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
        }
        iVar9 = 1;
      }
    }
  }
  else if (sVar2 < 1) {
    if (((-1 < sVar2) && (*param_12 == 0)) && (*(short *)(param_9 + 0x17e) == 0)) {
      iVar9 = *(int *)(param_9 + 0x154);
      local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)param_11 + 6)) ^ 0x80000000);
      dVar11 = (double)*(float *)(param_12 + 2);
      dVar12 = (double)(float)(dVar11 / (double)(float)(local_48 - DOUBLE_80437f10));
      pfVar4 = param_11;
      psVar6 = param_12;
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4,
                  pfVar4,psVar6,param_13,param_14,param_15,param_16);
      iVar9 = *(int *)(param_9 + 0x158);
      uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,iVar9,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar9,extraout_r4_00
                  ,pfVar4,psVar6,param_13,param_14,param_15,param_16);
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  else if (sVar2 < 4) {
    pfVar4 = (float *)0x43300000;
    iVar8 = *(int *)(param_9 + 0x154);
    uStack_3c = (int)*(short *)((int)param_11 + 2) ^ 0x80000000;
    local_48 = (double)CONCAT44(0x43300000,(int)*param_12 ^ 0x80000000);
    param_3 = (double)FLOAT_80437ec8;
    local_40 = 0x43300000;
    dVar12 = (double)(float)(param_3 -
                            (double)((float)(local_48 - DOUBLE_80437f10) /
                                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80437f10
                                           )));
    psVar6 = param_12;
    dVar11 = DOUBLE_80437f10;
    uVar10 = zz_00086b8_(dVar12,DOUBLE_80437f10,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_804361fc,iVar8,0x43300000,param_12,param_13,param_14,param_15,param_16)
    ;
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_03,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    iVar8 = *(int *)(param_9 + 0x158);
    uVar10 = zz_00086b8_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                         iVar8,pfVar4,psVar6,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,extraout_r4_04,
                pfVar4,psVar6,param_13,param_14,param_15,param_16);
    if (*param_12 == 0) {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
        *(byte *)(param_9 + 0x180) = *(byte *)(param_9 + 0x180) ^ 1;
      }
      iVar9 = 1;
    }
  }
  fVar3 = FLOAT_80437ecc;
  if (iVar9 != 0) {
    local_40 = 0x43300000;
    uStack_3c = (int)*(char *)(param_9 + 0x180) ^ 0x80000001;
    fVar3 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80437f10);
  }
  dVar12 = (double)fVar3;
  uVar7 = 0;
  iVar8 = *(int *)(param_9 + 0x144);
  local_48 = (double)(longlong)(int)(DOUBLE_80437f20 * dVar12);
  uVar1 = (uint)(DOUBLE_80437f20 * DOUBLE_80437f28 * dVar12);
  local_38 = (double)(longlong)(int)uVar1;
  pcVar5 = (char *)(uVar1 & 0xff);
  dVar11 = DOUBLE_80437f20;
  zz_0007cd0_(iVar8,(int)(DOUBLE_80437f20 * dVar12) & 0xff,pcVar5,0);
  dVar12 = (double)zz_0007cac_((double)(float)((double)FLOAT_80437f44 * dVar12 +
                                              (double)FLOAT_80437f40),iVar8);
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  if (*(char *)(param_9 + 0x180) == '\0') {
    *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 1;
  }
  else {
    *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 1;
  }
  if (*(short *)(param_9 + 0x17e) == 0) {
    dVar12 = (double)*(float *)(param_12 + 2);
    if (dVar12 <= (double)FLOAT_80437ecc) {
      if (*(short *)(param_9 + 0x182) != 0) {
        *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
      }
    }
    else if ((*(short *)(param_11 + 1) != 2) && (*(short *)(param_11 + 1) != 3)) {
      *(undefined2 *)(param_9 + 0x184) = 0xf000;
      *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
    }
  }
  else {
    *(short *)(param_9 + 0x17e) = *(short *)(param_9 + 0x17e) + -1;
    *(undefined2 *)(param_9 + 0x184) = 0x1000;
    *(short *)(param_9 + 0x182) = *(short *)(param_9 + 0x182) + *(short *)(param_9 + 0x184);
  }
  zz_0007a60_(dVar12,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16)
  ;
  local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x182)) ^ 0x80000000);
  local_50 = (float)((double)FLOAT_80437f48 * (double)(float)(local_38 - DOUBLE_80437f10));
  zz_0007988_(DOUBLE_80437f10,(double)FLOAT_80437f48,param_3,param_4,param_5,param_6,param_7,param_8
              ,*(int *)(param_9 + 0x14c),auStack_58,pcVar5,uVar7,param_13,param_14,param_15,param_16
             );
  return iVar9;
}



// ==== 8009e8e4  zz_009e8e4_ ====

void zz_009e8e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_009e130_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_009e388_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_8009e4dc(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8009e964  zz_009e964_ ====

void zz_009e964_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,short *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_009e130_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,(int)param_11,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x180) = 0;
  FUN_8009e4dc(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8009e9d0  zz_009e9d0_ ====

void zz_009e9d0_(void)

{
  return;
}



// ==== 8009e9d4  zz_009e9d4_ ====

void zz_009e9d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  char *pcVar5;
  float *pfVar6;
  int iVar7;
  short *psVar8;
  int in_r7;
  int in_r8;
  int in_r9;
  undefined4 in_r10;
  int *piVar9;
  undefined8 uVar10;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x191) = 1;
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  if ((*(char *)(param_9 + 0x191) == '\0') || (*(char *)(param_9 + 400) == '\0')) goto LAB_8009ec4c;
  in_r8 = *(int *)(param_9 + 0x90);
  in_r9 = 0;
  iVar7 = (int)*(short *)(in_r8 + 1000);
  iVar2 = 3;
  *(short *)(param_9 + 0x94) = *(short *)(in_r8 + 1000);
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(in_r8 + 0x3e4);
  *(undefined2 *)(param_9 + 0x17a) = 0xffff;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 399) = 0xff;
  *(undefined1 *)(param_9 + 0x18a) = 0;
  in_r7 = in_r8;
  do {
    if (*(short *)(in_r7 + 0x78e) != 0) {
      cVar1 = *(char *)(param_9 + 0x18a);
      if (*(char *)(param_9 + 0x12) == cVar1) {
        *(char *)(param_9 + 0x13) = cVar1;
        *(char *)(param_9 + 399) = (char)in_r9;
        break;
      }
      *(char *)(param_9 + 0x18a) = cVar1 + '\x01';
    }
    in_r7 = in_r7 + 8;
    in_r9 = in_r9 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  piVar9 = (int *)(param_9 + 0x144);
  *(char *)(param_9 + 399) = *(char *)(param_9 + 0x12) << 1;
  *(undefined1 *)(param_9 + 0x18d) = *(undefined1 *)(in_r8 + *(char *)(param_9 + 0x12) + 0x8d0);
  *(undefined1 *)(*(int *)(param_9 + 0x144) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x148) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x14c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x150) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x154) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x158) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x15c) + 0x10) = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x160) + 0x10) = 0;
  cVar1 = *(char *)(param_9 + 0x18d);
  if (cVar1 == '\x03') {
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802f6770;
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      piVar3 = &DAT_802f6a30;
      *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    }
    else if (cVar1 < '\x01') {
LAB_8009ebbc:
      piVar3 = (int *)0x0;
    }
    else {
      *(undefined2 *)(param_9 + 0x17c) = 0;
      piVar3 = &DAT_802f68d0;
    }
  }
  else if (cVar1 == '\x05') {
    *(undefined2 *)(param_9 + 0x17c) = 0;
    piVar3 = &DAT_802f6610;
  }
  else {
    if ('\x04' < cVar1) goto LAB_8009ebbc;
    *(undefined2 *)(param_9 + 0x17c) = 0xffff;
    piVar3 = &DAT_802f6770;
  }
  if (piVar3 != (int *)0x0) {
    iVar2 = 0;
    do {
      pcVar5 = (char *)*piVar3;
      if (-1 < (int)pcVar5) {
        if (iVar2 == 2) {
          pcVar5 = pcVar5 + *(char *)(param_9 + 0x12);
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,*piVar9,(int)pcVar5,iVar7,in_r7,in_r8,in_r9,in_r10);
        }
        else {
          uVar10 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_804361fc,*piVar9,(int)pcVar5,iVar7,in_r7,in_r8,in_r9,in_r10);
        }
        uVar10 = zz_0007834_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar9,
                             piVar3 + 1,pcVar5,iVar7,in_r7,in_r8,in_r9,in_r10);
        uVar10 = zz_0007ae4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar9,
                             piVar3 + 4,pcVar5,iVar7,in_r7,in_r8,in_r9,in_r10);
        param_1 = zz_0007988_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar9
                              ,piVar3 + 7,pcVar5,iVar7,in_r7,in_r8,in_r9,in_r10);
      }
      iVar2 = iVar2 + 1;
      piVar9 = piVar9 + 1;
      piVar3 = piVar3 + 0xb;
    } while (iVar2 < 8);
  }
  *(undefined1 *)(param_9 + 0x191) = 0;
LAB_8009ec4c:
  iVar2 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  uVar4 = zz_009da84_(iVar2,param_9);
  *(char *)(param_9 + 0x170) = (char)uVar4;
  cVar1 = *(char *)(param_9 + 0x18d);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else if (((*(char *)(param_9 + 0x191) < '\x01') && (*(char *)(param_9 + 0x18c) == '\0')) &&
          ((*(byte *)(iVar2 + 0x7d5) & 4) == 0)) {
    iVar7 = iVar2 + *(char *)(param_9 + 399) * 8;
    pfVar6 = (float *)(iVar7 + 0x78c);
    psVar8 = (short *)(iVar7 + 0x774);
    if (cVar1 == '\x05') {
      zz_009e8e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  pfVar6,psVar8,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x03') {
      zz_009e388_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  pfVar6,psVar8,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x02') {
      zz_009e964_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  pfVar6,psVar8,in_r7,in_r8,in_r9,in_r10);
    }
    else if (cVar1 == '\x01') {
      zz_009e9d0_();
    }
    else if (cVar1 == '\x04') {
      zz_009e388_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
                  pfVar6,psVar8,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      *(undefined1 *)(param_9 + 0x170) = 0;
    }
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 8009ed74  zz_009ed74_ ====

void zz_009ed74_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0015cc8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8009ed94  zz_009ed94_ ====

void zz_009ed94_(int param_1)

{
  zz_0016384_(param_1);
  return;
}



// ==== 8009edb4  zz_009edb4_ ====

void zz_009edb4_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_00165ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8009edd4  zz_009edd4_ ====

void zz_009edd4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0016f58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8009edf4  zz_009edf4_ ====

void zz_009edf4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  FUN_800173a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8009ee14  FUN_8009ee14 ====

/* WARNING: Removing unreachable block (ram,0x8009f0a4) */
/* WARNING: Removing unreachable block (ram,0x8009ee24) */

void FUN_8009ee14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  undefined4 extraout_r4;
  short sVar4;
  float *pfVar5;
  int iVar6;
  uint in_r7;
  int iVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  short sVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  double dVar15;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined2 *)(param_9 + 0x17a) = 0;
    *(undefined1 *)(param_9 + 0x182) = 0;
    *(undefined1 *)(param_9 + 0x186) = 0;
    *(undefined2 *)(param_9 + 0x17c) = 0;
    *(undefined1 *)(param_9 + 0x183) = 0;
    *(undefined1 *)(param_9 + 0x187) = 0;
    *(undefined2 *)(param_9 + 0x17e) = 0;
    *(undefined1 *)(param_9 + 0x184) = 0;
    *(undefined1 *)(param_9 + 0x188) = 0;
    *(undefined2 *)(param_9 + 0x180) = 0;
    *(undefined1 *)(param_9 + 0x185) = 0;
    *(undefined1 *)(param_9 + 0x189) = 0;
    *(undefined1 *)(param_9 + 0x18a) = 0;
  }
  iVar2 = *(int *)(param_9 + 0x90);
  if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else {
    iVar11 = param_9 + 0x144;
    iVar7 = 0;
    iVar13 = 2;
    iVar6 = iVar11;
    do {
      pfVar5 = (float *)(param_9 + iVar7);
      if (*(char *)((int)pfVar5 + 0x186) != '\0') {
        *(char *)((int)pfVar5 + 0x186) = *(char *)((int)pfVar5 + 0x186) + -1;
      }
      sVar4 = *(short *)(iVar2 + 0x4f4);
      if (sVar4 != *(short *)(iVar6 + 0x36)) {
        *(short *)(iVar6 + 0x36) = sVar4;
        if (sVar4 == 0) {
          *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) & ~(byte)(1 << iVar7);
        }
        else {
          in_r7 = 1 << iVar7;
          if (((*(byte *)(param_9 + 0x18a) & in_r7) == 0) ||
             (*(char *)((int)pfVar5 + 0x186) == '\0')) {
            *(undefined1 *)((int)pfVar5 + 0x186) = 8;
          }
          *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) | (byte)in_r7;
        }
      }
      iVar6 = iVar6 + 2;
      iVar2 = iVar2 + 2;
      iVar7 = iVar7 + 1;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    iVar2 = 0;
    *(undefined1 *)(param_9 + 0x170) = 0;
    if (*(char *)(param_9 + 0x18a) != '\0') {
      iVar13 = 0;
      *(undefined1 *)(param_9 + 0x170) = 1;
      do {
        if (((uint)*(byte *)(param_9 + 0x18a) & 1 << iVar13) != 0) {
          sVar4 = *(short *)(iVar11 + 0x36);
          if (1000 < sVar4) {
            sVar4 = 999;
            *(undefined2 *)(iVar11 + 0x36) = 999;
          }
          iVar12 = param_9 + iVar13;
          iVar10 = 0;
          *(undefined1 *)(iVar12 + 0x182) = 0;
          iVar8 = iVar2 << 2;
          sVar9 = 100;
          dVar15 = DOUBLE_80437f10;
          do {
            uVar3 = (int)sVar4 / (int)sVar9;
            if (((uVar3 != 0) && (*(char *)(iVar12 + 0x182) == '\0')) ||
               ((*(char *)(iVar12 + 0x182) == '\0' && (sVar9 == 1)))) {
              *(char *)(iVar12 + 0x182) = '\x03' - (char)iVar10;
            }
            if (9 < (int)uVar3) {
              uVar3 = 9;
            }
            uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) -
                                                dVar15),param_2,param_3,param_4,param_5,param_6,
                                 param_7,param_8,DAT_804361fc,*(int *)(param_9 + iVar8 + 0x148),
                                 pfVar5,iVar6,in_r7,iVar7,in_r9,in_r10);
            zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + iVar8 + 0x148),extraout_r4,pfVar5,iVar6,in_r7,iVar7,in_r9
                        ,in_r10);
            pfVar5 = (float *)(int)sVar4;
            iVar10 = iVar10 + 1;
            iVar8 = iVar8 + 4;
            sVar1 = (sVar4 / sVar9) * sVar9;
            sVar9 = (short)((uint)(int)sVar9 / 10);
            sVar4 = sVar4 - sVar1;
          } while (iVar10 < 3);
        }
        iVar13 = iVar13 + 1;
        iVar2 = iVar2 + 4;
        iVar11 = iVar11 + 2;
      } while (iVar13 < 2);
    }
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 8009f0c0  zz_009f0c0_ ====

void zz_009f0c0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,int param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  int iVar3;
  ushort uVar4;
  undefined4 extraout_r4;
  int *piVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (*(char *)(param_9 + 0x171) == '\0') {
    if ((char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0] < '\0') {
      *(undefined1 *)(param_9 + 0x170) = 0;
      return;
    }
    param_10 = (&DAT_803c4e84)[(char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0]];
    if (((*(short *)(param_9 + 0x94) != *(short *)(param_10 + 1000)) ||
        (*(char *)(param_9 + 0x96) != *(char *)(param_10 + 0x3e4))) ||
       (*(char *)(param_9 + 0x174) != *(char *)(param_10 + 0x491))) {
      *(undefined1 *)(param_9 + 0x172) = 0xff;
      *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_10 + 0x3e4);
      *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_10 + 1000);
      *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)(param_10 + 0x491);
    }
  }
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    zz_0012638_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    cVar1 = *(char *)(param_9 + 0x1a);
    if (cVar1 == '\x01') {
      uVar4 = *(short *)(param_9 + 0x1e) + 1;
      *(ushort *)(param_9 + 0x1e) = uVar4;
      dVar2 = DOUBLE_80437f10;
      if ((uVar4 & 0x1f) == 0) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) ^ 1;
        uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(param_9 + 0x1c) ^
                                                             0x80000000) - dVar2),param_2,param_3,
                            param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                            *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                            param_16);
        zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      piVar5 = &DAT_803c4e84;
      iVar6 = 0;
      iVar3 = (int)(char)PTR_DAT_80433934[0x15da];
      if (0 < iVar3) {
        do {
          if (((((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << iVar6) != 0) &&
              ((int)*(char *)(param_9 + 0x12) == (int)*(char *)(*piVar5 + 0x88))) &&
             (*(int *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x12) * 0x3c + 0x118) <=
              (int)*(short *)(*piVar5 + 0x4aa))) {
            *(undefined1 *)(param_9 + 0x1a) = 1;
            *(undefined2 *)(param_9 + 0x1e) = 0;
            *(undefined2 *)(param_9 + 0x1c) = 0;
            return;
          }
          piVar5 = piVar5 + 1;
          iVar6 = iVar6 + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    break;
  case 2:
    if (PTR_DAT_80433934[0x50] == '\0') {
      FUN_80012e74(param_9,-0x7fd0a1b8,param_11,param_12,param_13,param_14,param_15,param_16);
    }
    break;
  case 5:
    FUN_8009d6bc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 6:
    FUN_8009dce4(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 7:
    zz_009e9d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 8:
    zz_009ed74_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 9:
    zz_009ed94_(param_9);
    break;
  case 10:
    zz_009edb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0xb:
    FUN_8009ee14(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0xe:
    zz_009f4c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0xf:
    zz_009edd4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0x10:
    zz_009edf4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8009f378  FUN_8009f378 ====

void FUN_8009f378(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  puVar2 = (undefined4 *)(param_9 + 0x144);
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      param_1 = zz_0006d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar2,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
      param_10 = extraout_r4;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8009f3e0  zz_009f3e0_ ====

void zz_009f3e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  uVar3 = 1;
  uVar4 = (uint)(byte)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
  *(undefined *)(param_9 + 0x96) = PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0];
  *(undefined1 *)(param_9 + 0x84) = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0x20,1);
  iVar2 = *(char *)(param_9 + 0x173) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_802f6390 + iVar2);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f638c + iVar2);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f6394 + iVar2);
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3e6) == '\0') {
    iVar2 = *(char *)(param_9 + 0x96) + 0x3d;
  }
  else {
    iVar2 = 0x41;
    *(undefined1 *)(param_9 + 0x19) = 6;
  }
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0x144),iVar2,uVar3,uVar4,in_r8,in_r9,in_r10);
  if (PTR_DAT_80433930[0x29] == '\x02') {
    *(undefined4 *)(*(int *)(param_9 + 0x148) + 0x14) = 0xffffffff;
  }
  return;
}



// ==== 8009f4c4  zz_009f4c4_ ====

void zz_009f4c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  short sVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  
  if (PTR_DAT_80433930[0x29] == '\x02') {
    if ((*(char *)(param_9 + 0x19) < '\x03') &&
       (*(char *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 0x486) != '\0')) {
      *(undefined1 *)(param_9 + 0x19) = 3;
    }
    fVar3 = FLOAT_80437ecc;
    bVar1 = *(byte *)(param_9 + 0x19);
    pfVar6 = (float *)(uint)bVar1;
    switch(bVar1) {
    case 0:
      iVar7 = *(int *)(param_9 + 0x90);
      if ((*(char *)(iVar7 + 0x18) < '\x02') &&
         (*(int *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x88) * 0x3c + 0x118) <=
          (int)*(short *)(iVar7 + 0x4aa))) {
        *(byte *)(param_9 + 0x19) = bVar1 + 1;
        fVar2 = FLOAT_80437ecc;
        fVar3 = FLOAT_80437ec8;
        dVar9 = (double)FLOAT_80437ec8;
        pfVar6 = (float *)0x64;
        *(float *)(param_9 + 0x58) = FLOAT_80437ecc;
        dVar4 = DOUBLE_80437f10;
        *(float *)(param_9 + 0x5c) = fVar2;
        *(float *)(param_9 + 0x60) = fVar3;
        *(undefined2 *)(param_9 + 0x1c) = 0;
        *(undefined2 *)(param_9 + 0x1e) = 4;
        *(undefined1 *)(param_9 + 0x1b) = 0;
        *(float *)(param_9 + 0x44) =
             (float)(dVar9 / (double)(float)((double)CONCAT44(0x43300000,
                                                              (int)*(short *)(param_9 + 0x1e) ^
                                                              0x80000000) - dVar4));
        zz_0006fb4_(dVar4,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                    *(int *)(param_9 + 0x148),100,iVar7,param_13,param_14,param_15,param_16);
        uVar8 = zz_00086b8_((double)FLOAT_80437ecc,dVar9,param_3,param_4,param_5,param_6,param_7,
                            param_8,DAT_804361fc,*(int *)(param_9 + 0x148),pfVar6,iVar7,param_13,
                            param_14,param_15,param_16);
        zz_0007c30_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x148),extraout_r4,pfVar6,iVar7,param_13,param_14,param_15,
                    param_16);
      }
      break;
    case 1:
      *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) + *(float *)(param_9 + 0x44);
      *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) + *(float *)(param_9 + 0x44);
      sVar5 = *(short *)(param_9 + 0x1e) + -1;
      *(short *)(param_9 + 0x1e) = sVar5;
      fVar3 = FLOAT_80437ec8;
      if (sVar5 < 1) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0x5c) = fVar3;
        *(float *)(param_9 + 0x58) = fVar3;
      }
      break;
    case 2:
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
      dVar4 = DOUBLE_80437f10;
      if ((*(ushort *)(param_9 + 0x1c) & 0x1f) == 0) {
        *(byte *)(param_9 + 0x1b) = *(byte *)(param_9 + 0x1b) ^ 1;
        uVar8 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(char *)(param_9 + 0x1b) ^
                                                             0x80000000) - dVar4),param_2,param_3,
                            param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                            *(int *)(param_9 + 0x148),pfVar6,param_12,param_13,param_14,param_15,
                            param_16);
        zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x148),extraout_r4_00,pfVar6,param_12,param_13,param_14,
                    param_15,param_16);
      }
      break;
    case 3:
      *(byte *)(param_9 + 0x19) = bVar1 + 1;
      *(undefined2 *)(param_9 + 0x1c) = 0xb4;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0x148),0x2b,param_12,param_13,param_14,param_15,param_16);
      break;
    case 4:
      sVar5 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar5;
      fVar3 = FLOAT_80437f4c;
      if (sVar5 < 1) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0xd8) = fVar3;
        *(float *)(param_9 + 0xd4) = fVar3;
      }
      break;
    case 5:
      fVar2 = *(float *)(param_9 + 0xd4) - FLOAT_80437ec8;
      *(float *)(param_9 + 0xd4) = fVar2;
      if (fVar2 <= fVar3) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(float *)(param_9 + 0xd4) = fVar3;
      }
      zz_0007cac_((double)(FLOAT_80437f54 *
                           (*(float *)(param_9 + 0xd4) / *(float *)(param_9 + 0xd8)) +
                          FLOAT_80437f50),*(int *)(param_9 + 0x148));
    }
  }
  return;
}



// ==== 8009f770  zz_009f770_ ====

/* WARNING: Removing unreachable block (ram,0x8009f8e4) */
/* WARNING: Removing unreachable block (ram,0x8009f780) */

void zz_009f770_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float afStack_48 [12];
  
  iVar4 = *(int *)(param_9 + 0x144);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar1);
  iVar1 = *(int *)(param_9 + 0x148);
  if (*(int *)(iVar1 + 0x14) != -1) {
    if (*(char *)(param_9 + 0x19) < '\x03') {
      if (*(int *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x88) * 0x3c + 0x118) <=
          (int)*(short *)(*(int *)(param_9 + 0x90) + 0x4aa)) {
        dVar8 = (double)*(float *)(&DAT_802f6ce4 + *(char *)(param_9 + 0x173) * 0xc);
        if (*(char *)(*(int *)(param_9 + 0x90) + 0x3e6) != '\0') {
          dVar8 = (double)(float)(dVar8 + (double)FLOAT_80437f58);
        }
        zz_020b520_((double)*(float *)(param_9 + 0x58),(double)*(float *)(param_9 + 0x5c),
                    (double)*(float *)(param_9 + 0x60),(float *)(param_9 + 0x114),afStack_48);
        iVar4 = *(char *)(param_9 + 0x173) * 0xc;
        puVar2 = &DAT_802f6ce4 + iVar4;
        dVar6 = (double)*(float *)(&DAT_802f6ce8 + iVar4);
        dVar7 = (double)*(float *)(&DAT_802f6cec + iVar4);
        uVar5 = zz_020b4ac_(dVar8,dVar6,dVar7,afStack_48,afStack_48);
        zz_00076d0_(uVar5,dVar6,dVar7,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_48,
                    puVar2,param_12,param_13,param_14,param_15,param_16);
        iVar4 = zz_009cb58_(*(int *)(iVar1 + 0x14));
        zz_0009958_(iVar1,iVar4);
      }
    }
    else {
      puVar3 = &DAT_802f6d14;
      iVar4 = *(char *)(param_9 + 0x173) * 0xc;
      puVar2 = &DAT_802f6d14 + iVar4;
      dVar8 = (double)*(float *)(&DAT_802f6d18 + iVar4);
      dVar6 = (double)*(float *)(&DAT_802f6d1c + iVar4);
      uVar5 = zz_020b4ac_((double)*(float *)(&DAT_802f6d14 + iVar4),dVar8,dVar6,
                          (float *)(param_9 + 0x114),afStack_48);
      zz_00076d0_(uVar5,dVar8,dVar6,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_48,puVar2,
                  puVar3,param_13,param_14,param_15,param_16);
      iVar4 = zz_009cb58_(*(int *)(iVar1 + 0x14));
      zz_0009958_(iVar1,iVar4);
    }
  }
  return;
}



// ==== 8009f904  zz_009f904_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_009f904_(int param_1,undefined4 param_2,float *param_3,undefined *param_4,undefined4 param_5
                ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  cVar1 = *(char *)(param_1 + 400);
  iVar8 = (int)*(char *)(param_1 + 0x12);
  if ((double)FLOAT_80437f5c < (double)*(float *)(param_1 + 0x17c)) {
    iVar6 = *(int *)(param_1 + 0x144);
    zz_020b520_((double)*(float *)(param_1 + 0x17c),(double)FLOAT_80437ec8,(double)FLOAT_80437ec8,
                (float *)(param_1 + 0x114),afStack_4c);
    iVar2 = iVar8 * 8;
    dVar11 = (double)FLOAT_80437ecc;
    param_4 = &DAT_802f6d44;
    puVar4 = &DAT_802f6d44 + iVar2;
    dVar10 = (double)*(float *)(&DAT_802f6d48 + iVar2);
    uVar9 = zz_020b4ac_((double)*(float *)(&DAT_802f6d44 + iVar2),dVar10,dVar11,afStack_4c,
                        afStack_4c);
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar6,afStack_4c,puVar4,param_4,
                param_5,param_6,param_7,param_8);
    iVar2 = zz_009cb58_(*(int *)(iVar6 + 0x14));
    zz_0009958_(iVar6,iVar2);
    iVar6 = *(int *)(param_1 + 0x148);
    gnt4_PSMTXRotRad_bl((double)FLOAT_80437f60,afStack_7c,0x78);
    param_3 = afStack_7c;
    uVar9 = gnt4_PSMTXConcat_bl(afStack_4c,param_3,param_3);
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar6,afStack_7c,
                (undefined *)param_3,param_4,param_5,param_6,param_7,param_8);
    iVar2 = zz_009cb58_(*(int *)(iVar6 + 0x14));
    zz_0009958_(iVar6,iVar2);
  }
  if (*(int *)(param_1 + 0x184) != *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118)) {
    iVar2 = *(int *)(param_1 + 0xe4);
    local_80 = FLOAT_80437ecc;
    local_84 = FLOAT_80437ecc;
    zz_020b520_((double)(*(float *)(param_1 + 0x180) - *(float *)(param_1 + 0x17c)),
                (double)FLOAT_80437ec8,(double)FLOAT_80437ec8,(float *)(param_1 + 0x114),afStack_4c)
    ;
    if (iVar8 == 0) {
      dVar10 = (double)_DAT_802f6d48;
      dVar11 = (double)FLOAT_80437ecc;
      uVar9 = zz_020b4ac_(-(double)(FLOAT_80437f64 * *(float *)(param_1 + 0x17c) - _DAT_802f6d44),
                          dVar10,dVar11,afStack_4c,afStack_4c);
    }
    else {
      dVar10 = (double)*(float *)(&DAT_802f6d48 + iVar8 * 8);
      dVar11 = (double)FLOAT_80437ecc;
      uVar9 = zz_020b4ac_((double)(FLOAT_80437f64 * *(float *)(param_1 + 0x17c) +
                                  *(float *)(&DAT_802f6d44 + iVar8 * 8)),dVar10,dVar11,afStack_4c,
                          afStack_4c);
    }
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_4c,
                (undefined *)param_3,param_4,param_5,param_6,param_7,param_8);
    iVar6 = zz_009cb58_(*(int *)(iVar2 + 0x14));
    zz_0009958_(iVar2,iVar6);
    iVar6 = *(int *)(param_1 + 0xe8);
    gnt4_PSMTXRotRad_bl((double)FLOAT_80437f60,afStack_7c,0x78);
    pfVar5 = afStack_7c;
    uVar9 = gnt4_PSMTXConcat_bl(afStack_4c,pfVar5,pfVar5);
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar6,afStack_7c,
                (undefined *)pfVar5,param_4,param_5,param_6,param_7,param_8);
    iVar2 = zz_009cb58_(*(int *)(iVar6 + 0x14));
    zz_0009958_(iVar6,iVar2);
  }
  iVar2 = *(int *)(param_1 + 0xe0);
  if (iVar8 == 0) {
    local_88 = -(FLOAT_80437f64 * *(float *)(param_1 + 0x180) - _DAT_802f6d44);
  }
  else {
    local_88 = FLOAT_80437f64 * *(float *)(param_1 + 0x180) + *(float *)(&DAT_802f6d44 + iVar8 * 8);
  }
  local_84 = FLOAT_80437ecc;
  pfVar5 = &local_88;
  local_80 = FLOAT_80437f68;
  gnt4_PSVECAdd_bl(pfVar5,(float *)(param_1 + 0x20),pfVar5);
  dVar10 = (double)local_84;
  dVar11 = (double)local_80;
  uVar9 = gnt4_PSMTXTrans_bl((double)local_88,dVar10,dVar11,afStack_4c);
  zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_4c,(undefined *)pfVar5
              ,param_4,param_5,param_6,param_7,param_8);
  iVar6 = zz_009cb58_(*(int *)(iVar2 + 0x14));
  zz_0009958_(iVar2,iVar6);
  iVar2 = iVar8 * 0xc;
  dVar11 = (double)FLOAT_80437ecc;
  dVar10 = (double)*(float *)(&DAT_802f6d58 + iVar2);
  uVar9 = zz_020b4ac_((double)*(float *)(&DAT_802f6d54 + iVar2),dVar11,dVar10,afStack_4c,afStack_4c)
  ;
  if (iVar8 == 1) {
    param_4 = (undefined *)0x43300000;
    dVar11 = (double)FLOAT_80437ecc;
    uStack_14 = (int)*(char *)(param_1 + 0x1b) ^ 0x80000000;
    pfVar5 = (float *)0x802f6d60;
    local_18 = 0x43300000;
    dVar10 = dVar11;
    in_f4 = DOUBLE_80437f10;
    uVar9 = zz_020b4ac_(-(double)((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80437f10)
                                 * fRam802f6d68),dVar11,dVar11,afStack_4c,afStack_4c);
  }
  iVar6 = param_1 + 0x158;
  iVar8 = 5;
  do {
    iVar7 = *(int *)(iVar6 + 8);
    zz_00076d0_(uVar9,dVar11,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,iVar7,afStack_4c,
                (undefined *)pfVar5,param_4,param_5,param_6,param_7,param_8);
    iVar3 = zz_009cb58_(*(int *)(iVar7 + 0x14));
    zz_0009958_(iVar7,iVar3);
    dVar11 = (double)FLOAT_80437ecc;
    dVar10 = dVar11;
    uVar9 = zz_020b4ac_((double)*(float *)(&DAT_802f6d5c + iVar2),dVar11,dVar11,afStack_4c,
                        afStack_4c);
    iVar8 = iVar8 + -1;
    iVar6 = iVar6 + -4;
  } while (-1 < iVar8);
  return;
}



// ==== 8009fcac  zz_009fcac_ ====

void zz_009fcac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [15];
  
  iVar3 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  iVar3 = *(int *)(param_9 + 0x160);
  pfVar2 = &local_88;
  local_88 = FLOAT_80437ecc;
  local_84 = FLOAT_80437ecc;
  local_80 = FLOAT_80437f6c;
  uVar6 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_0007834_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_88,
              (char *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  if (PTR_DAT_80433934[0x50] == '\0') {
    iVar1 = 0;
    piVar5 = (int *)(param_9 + 0x144);
    do {
      if (-1 < *(int *)(*piVar5 + 0x14)) {
        iVar4 = *(int *)(param_9 + (iVar1 + *(char *)(param_9 + 0x193) * 3) * 4 + 0x144);
        gnt4_PSMTXTrans_bl((double)*(float *)piVar5[0xe],(double)((float *)piVar5[0xe])[1],
                           (double)FLOAT_80437ed0,afStack_4c);
        dVar7 = (double)FLOAT_80437f70;
        dVar8 = (double)FLOAT_80437ec8;
        gnt4_PSMTXScale_bl(dVar7,dVar7,dVar8,afStack_7c);
        pfVar2 = afStack_4c;
        uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_7c,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_4c,
                    (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
        iVar3 = zz_009cb58_(*(int *)(iVar4 + 0x14));
        zz_0009958_(iVar4,iVar3);
      }
      iVar1 = iVar1 + 1;
      piVar5 = piVar5 + 1;
    } while (iVar1 < 3);
  }
  return;
}



// ==== 8009fe08  zz_009fe08_ ====

void zz_009fe08_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,int param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_8009d6bc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96));
  if ((uVar1 == 0) && (*(char *)(param_9 + 0x170) != '\0')) {
    if (*(char *)(param_9 + 0x17a) == '\0') {
      piVar5 = (int *)(param_9 + 0x144);
      iVar6 = param_9;
      for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x17b); iVar3 = iVar3 + 1) {
        if (iVar3 < 8) {
          iVar4 = *piVar5;
        }
        else {
          iVar4 = *(int *)(iVar6 + 0xc0);
        }
        iVar2 = zz_009cb58_(*(int *)(iVar4 + 0x14));
        zz_0009958_(iVar4,iVar2);
        iVar6 = iVar6 + 4;
        piVar5 = piVar5 + 1;
      }
    }
    else {
      iVar3 = *(int *)(param_9 + 0x144);
      iVar6 = zz_009cb58_(*(int *)(iVar3 + 0x14));
      zz_0009958_(iVar3,iVar6);
    }
  }
  return;
}



// ==== 8009fedc  zz_009fedc_ ====

void zz_009fedc_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  float afStack_78 [12];
  float afStack_48 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = (double)FUN_8009dce4(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   param_9,param_10,param_11,param_12,param_13,param_14,param_15,
                                   param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar5 = *(int *)(param_9 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_009cb58_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar3);
    cVar1 = *(char *)(param_9 + 0x1a2);
    gnt4_PSMTXScale_bl((double)FLOAT_80437f44,(double)FLOAT_80437f44,(double)FLOAT_80437ec8,
                       afStack_48);
    iVar5 = (int)*(short *)(param_9 + 0x196);
    for (iVar3 = iVar5; 0 < iVar3; iVar3 = iVar3 + -1) {
      iVar2 = iVar5 - iVar3;
      iVar6 = *(int *)(param_9 + ((((-(int)cVar1 | (int)cVar1) >> 0x1f & 4U) + iVar5) - iVar3) * 4 +
                      0x144);
      dVar8 = (double)(float)(&DAT_802f5f24)[iVar2 * 3];
      dVar9 = (double)(float)(&DAT_802f5f28)[iVar2 * 3];
      gnt4_PSMTXTrans_bl((double)(float)(&DAT_802f5f20)[iVar2 * 3],dVar8,dVar9,afStack_78);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_78,afStack_78);
      pfVar4 = afStack_78;
      uVar7 = gnt4_PSMTXConcat_bl(pfVar4,afStack_48,pfVar4);
      zz_00076d0_(uVar7,dVar8,dVar9,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_78,
                  (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_009cb58_(*(int *)(iVar6 + 0x14));
      zz_0009958_(iVar6,iVar2);
    }
  }
  return;
}



// ==== 800a0008  zz_00a0008_ ====

void zz_00a0008_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  undefined8 uVar7;
  undefined4 auStack_a8 [2];
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float afStack_80 [12];
  float afStack_50 [15];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined1 *)(param_9 + 0x191) = 1;
    param_1 = zz_009e9d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar4 = 0;
    piVar6 = (int *)(param_9 + 0x144);
    do {
      iVar3 = *piVar6;
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0xc) != 0)) {
        uVar7 = zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            &local_98,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar7 = zz_0007a60_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            auStack_a8,param_11,param_12,param_13,param_14,param_15,param_16);
        zz_0007908_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_8c,
                    param_11,param_12,param_13,param_14,param_15,param_16);
        gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
        gnt4_PSMTXRotRad_bl((double)local_a0,afStack_80,0x7a);
        gnt4_PSMTXConcat_bl(afStack_50,afStack_80,afStack_50);
        param_2 = (double)local_88;
        param_3 = (double)local_84;
        zz_020b4ac_((double)local_8c,param_2,param_3,afStack_50,afStack_50);
        param_11 = afStack_50;
        uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_50,
                    (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
        iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
        param_1 = zz_0009958_(iVar3,iVar1);
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 8);
    pfVar5 = (float *)&DAT_802f5f70;
    iVar3 = 0;
    iVar4 = param_9;
    while( true ) {
      if (*(short *)(param_9 + 0x17c) <= iVar3) break;
      if (*(char *)(param_9 + 0x180) == '\0') {
        iVar1 = *(int *)(iVar4 + 0xe0);
      }
      else {
        iVar1 = *(int *)(iVar4 + 0xec);
      }
      zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_98,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
      param_2 = (double)pfVar5[1];
      param_3 = (double)pfVar5[2];
      zz_020b4ac_((double)*pfVar5,param_2,param_3,afStack_50,afStack_50);
      param_11 = afStack_50;
      uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
      zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_50,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_009cb58_(*(int *)(iVar1 + 0x14));
      param_1 = zz_0009958_(iVar1,iVar2);
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + 3;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 800a01d0  FUN_800a01d0 ====

/* WARNING: Removing unreachable block (ram,0x800a0594) */
/* WARNING: Removing unreachable block (ram,0x800a058c) */
/* WARNING: Removing unreachable block (ram,0x800a01e8) */
/* WARNING: Removing unreachable block (ram,0x800a01e0) */

void FUN_800a01d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  float local_d8;
  float local_d4;
  float local_d0;
  float afStack_cc [12];
  float afStack_9c [13];
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_009ed74_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if ((-1 < *(char *)(param_9 + 400)) &&
     (uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96)), uVar1 == 0)) {
    if (*(char *)(param_9 + 400) == '\0') {
      iVar10 = 0;
      uVar4 = 0x802f0000;
      dVar14 = (double)FLOAT_80437f48;
      iVar9 = 0;
      iVar7 = 0;
      iVar11 = param_9 + 0x144;
      iVar5 = 0;
      dVar13 = DOUBLE_80437f10;
      do {
        pfVar3 = &local_d8;
        iVar6 = *(int *)(iVar11 + 8);
        uVar12 = gnt4_PSMTXMultVec_bl
                           ((float *)(param_9 + 0x114),
                            (float *)(*(char *)(param_9 + 0x173) * 0x60 + -0x7fd09ecc +
                                      *(char *)(param_9 + 0x12) * 0x18 + iVar10),pfVar3);
        zz_0007834_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    (char *)pfVar3,uVar4,param_13,param_14,param_15,param_16);
        local_68 = 0x43300000;
        uStack_64 = (int)*(short *)(&DAT_802f62f4 + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        zz_0007e74_((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_64)
                                                            - dVar13)),param_2,param_3,param_4,
                    param_5,param_6,param_7,param_8,iVar6,
                    &DAT_802f62f4 + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,param_13,
                    param_14,param_15,param_16);
        local_60 = 0x43300000;
        uStack_5c = (int)*(short *)(&DAT_802f62e4 + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        uVar12 = FUN_80007db0((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_5c) -
                                                                      dVar13)),param_2,param_3,
                              param_4,param_5,param_6,param_7,param_8,iVar6,
                              &DAT_802f62e4 + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,
                              param_13,param_14,param_15,param_16);
        local_d8 = *(float *)(param_9 + 0x17c);
        local_d0 = *(float *)(&DAT_802f62b4 + *(char *)(param_9 + 0x12) * 8 + iVar7);
        local_d4 = local_d8;
        zz_0007ae4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    &DAT_802f62b4 + *(char *)(param_9 + 0x12) * 8,uVar4,param_13,param_14,param_15,
                    param_16);
        iVar2 = zz_009cb58_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar2);
        iVar5 = iVar5 + 1;
        iVar10 = iVar10 + 0xc;
        iVar9 = iVar9 + 2;
        iVar7 = iVar7 + 4;
        iVar11 = iVar11 + 4;
      } while (iVar5 < 2);
    }
    else {
      iVar10 = 0;
      piVar8 = (int *)(param_9 + 0x144);
      iVar5 = 0;
      iVar7 = 0;
      iVar9 = 0;
      do {
        if ((iVar10 != 0) || (FLOAT_80437f74 <= *(float *)(param_9 + 0x180))) {
          iVar11 = *piVar8;
          pfVar3 = (float *)(*(char *)(param_9 + 0x173) * 0x60 + -0x7fd0a04c +
                             *(char *)(param_9 + 0x12) * 0x18 + iVar5);
          gnt4_PSMTXTrans_bl((double)*pfVar3,(double)pfVar3[1],(double)pfVar3[2],afStack_9c);
          gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_9c,afStack_9c);
          local_60 = 0x43300000;
          uStack_5c = (int)*(short *)(&DAT_802f62f4 + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80437f48 *
                                      (float)((double)CONCAT44(0x43300000,uStack_5c) -
                                             DOUBLE_80437f10)),afStack_cc,0x7a);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          local_68 = 0x43300000;
          uStack_64 = (int)*(short *)(&DAT_802f62d4 + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80437f48 *
                                      (float)((double)CONCAT44(0x43300000,uStack_64) -
                                             DOUBLE_80437f10)),afStack_cc,0x79);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          if (iVar10 == 0) {
            iVar2 = *(char *)(param_9 + 0x12) * 0xc;
            local_d0 = FLOAT_80437ec8;
            local_d8 = *(float *)(&DAT_802f6304 + iVar2);
            local_d4 = *(float *)(&DAT_802f6308 + iVar2);
          }
          else {
            local_d8 = *(float *)(param_9 + 0x184);
            local_d4 = *(float *)(param_9 + 0x188);
            local_d0 = *(float *)(param_9 + 0x18c);
          }
          dVar13 = (double)local_d4;
          local_d0 = local_d0 * *(float *)(&DAT_802f62b4 + iVar9 + *(char *)(param_9 + 0x12) * 8);
          dVar14 = (double)local_d0;
          gnt4_PSMTXScale_bl((double)local_d8,dVar13,dVar14,afStack_cc);
          pfVar3 = afStack_9c;
          uVar12 = gnt4_PSMTXConcat_bl(pfVar3,afStack_cc,pfVar3);
          zz_00076d0_(uVar12,dVar13,dVar14,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_9c
                      ,(undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
          iVar2 = zz_009cb58_(*(int *)(iVar11 + 0x14));
          zz_0009958_(iVar11,iVar2);
        }
        iVar10 = iVar10 + 1;
        iVar5 = iVar5 + 0xc;
        iVar7 = iVar7 + 2;
        iVar9 = iVar9 + 4;
        piVar8 = piVar8 + 1;
      } while (iVar10 < 2);
    }
  }
  return;
}



// ==== 800a05b0  FUN_800a05b0 ====

void FUN_800a05b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x144);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar2 + 0x14));
  zz_0009958_(iVar2,iVar1);
  return;
}



// ==== 800a05f8  FUN_800a05f8 ====

void FUN_800a05f8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_009edb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar5 = (double)FLOAT_80437f48;
  iVar3 = *(int *)(param_9 + 0x144);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_80437f10)),afStack_48,0x7a);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  dVar5 = (double)FLOAT_80437ecc;
  iVar3 = *(int *)(param_9 + 0x148);
  dVar6 = (double)FLOAT_80437f04;
  gnt4_PSMTXTrans_bl(dVar5,dVar5,dVar6,afStack_48);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}



// ==== 800a06e8  FUN_800a06e8 ====

/* WARNING: Removing unreachable block (ram,0x800a093c) */
/* WARNING: Removing unreachable block (ram,0x800a0934) */
/* WARNING: Removing unreachable block (ram,0x800a0700) */
/* WARNING: Removing unreachable block (ram,0x800a06f8) */

void FUN_800a06e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  char **ppcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 *puVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  char *local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  uint uStack_54;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_8009ee14(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    puVar11 = &DAT_802f6374;
    piVar12 = (int *)(param_9 + 0x144);
    puVar9 = &DAT_802f6d6c;
    uVar7 = 0;
    iVar10 = 1;
    do {
      if (((uint)*(byte *)(param_9 + 0x18a) & 1 << uVar7) != 0) {
        uStack_54 = uVar7 ^ 0x80000000;
        iVar6 = *piVar12;
        local_58 = 0x43300000;
        pcVar4 = *(char **)(param_9 + 0x20);
        dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80437f10);
        local_64 = (float)((double)FLOAT_80437f78 * dVar14 + (double)*(float *)(param_9 + 0x24));
        local_60 = *(float *)(param_9 + 0x28);
        local_68 = pcVar4;
        zz_0007834_(dVar14,(double)FLOAT_80437f78,param_3,param_4,param_5,param_6,param_7,param_8,
                    iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
        iVar3 = zz_009cb58_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar3);
        if ((uVar7 == 1) && (*(char *)(param_9 + 0x183) != '\0')) {
          iVar6 = *(int *)(param_9 + 0xe0);
          uStack_54 = (int)*(char *)(param_9 + 0x183) - 1U ^ 0x80000000;
          local_58 = 0x43300000;
          dVar14 = (double)(float)local_68;
          local_68 = (char *)(float)(dVar14 + DOUBLE_80437f80 +
                                              (double)(float)((double)FLOAT_80437f88 *
                                                             (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_54) - DOUBLE_80437f10)));
          zz_0007834_(dVar14,(double)FLOAT_80437f88,DOUBLE_80437f80,param_4,param_5,param_6,param_7,
                      param_8,iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
          iVar3 = zz_009cb58_(*(int *)(iVar6 + 0x14));
          zz_0009958_(iVar6,iVar3);
        }
        uStack_54 = uVar7 ^ 0x80000000;
        local_58 = 0x43300000;
        param_3 = (double)FLOAT_80437f90;
        dVar17 = (double)FLOAT_80437f94;
        dVar16 = (double)(float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                          DOUBLE_80437f10) + (double)FLOAT_80437f8c)
        ;
        puVar13 = puVar11;
        dVar14 = DOUBLE_80437f10;
        for (uVar8 = 0; (int)uVar8 < (int)*(char *)(param_9 + uVar7 + 0x182); uVar8 = uVar8 + 1) {
          local_68 = (char *)*puVar13;
          iVar3 = *(int *)(param_9 + ((2 - uVar8) + iVar10) * 4 + 0x144);
          local_64 = (float)dVar16;
          local_60 = (float)dVar17;
          bVar1 = *(byte *)(param_9 + uVar7 + 0x186);
          if (bVar1 != 0) {
            fVar2 = *(float *)(puVar9 + (bVar1 & 3) * 4);
            if ((uVar8 & 1) != 0) {
              fVar2 = fVar2 * FLOAT_80437f98;
            }
            local_64 = local_64 + fVar2;
          }
          ppcVar5 = &local_68;
          uVar15 = gnt4_PSMTXMultVec_bl
                             ((float *)(param_9 + 0x114),(float *)ppcVar5,(float *)ppcVar5);
          zz_0007834_(uVar15,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_68,
                      (char *)ppcVar5,param_12,param_13,param_14,param_15,param_16);
          iVar6 = zz_009cb58_(*(int *)(iVar3 + 0x14));
          zz_0009958_(iVar3,iVar6);
          puVar13 = puVar13 + 1;
        }
      }
      uVar7 = uVar7 + 1;
      puVar11 = puVar11 + 3;
      iVar10 = iVar10 + 4;
      puVar9 = puVar9 + 0x10;
      piVar12 = piVar12 + 4;
    } while ((int)uVar7 < 2);
  }
  return;
}



// ==== 800a0958  FUN_800a0958 ====

void FUN_800a0958(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  float afStack_78 [12];
  float afStack_48 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_009edd4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    piVar6 = (int *)(param_9 + 0x144);
    pfVar4 = (float *)&DAT_802f6e1c;
    iVar2 = 0;
    iVar5 = 0;
    do {
      iVar3 = *piVar6;
      if (*(char *)(iVar3 + 0x10) != '\0') {
        pfVar1 = (float *)(&DAT_802f6d8c + iVar5 + *(char *)(param_9 + 0x173) * 0x24);
        gnt4_PSMTXTrans_bl((double)*pfVar1,(double)pfVar1[1],(double)pfVar1[2],afStack_48);
        gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_48,afStack_48);
        dVar8 = (double)pfVar4[1];
        dVar9 = (double)pfVar4[2];
        gnt4_PSMTXScale_bl((double)*pfVar4,dVar8,dVar9,afStack_78);
        pfVar1 = afStack_48;
        uVar7 = gnt4_PSMTXConcat_bl(afStack_78,pfVar1,pfVar1);
        zz_00076d0_(uVar7,dVar8,dVar9,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
                    (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar3,3);
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0xc;
      pfVar4 = pfVar4 + 3;
      piVar6 = piVar6 + 1;
    } while (iVar2 < 3);
  }
  return;
}



// ==== 800a0a54  zz_00a0a54_ ====

void zz_00a0a54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_38 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = zz_009edf4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar3 = *(int *)(param_9 + 0x144);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                (float *)(param_9 + 0x114),(undefined *)param_11,param_12,param_13,param_14,param_15
                ,param_16);
    iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
    dVar5 = (double)FLOAT_80437ecc;
    dVar6 = dVar5;
    gnt4_PSMTXTrans_bl((double)FLOAT_80437f9c,dVar5,dVar5,afStack_38);
    pfVar2 = afStack_38;
    uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
    iVar3 = *(int *)(param_9 + 0x148);
    zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_38,
                (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    iVar1 = zz_009cb58_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
  }
  return;
}



// ==== 800a0b0c  zz_00a0b0c_ ====

void zz_00a0b0c_(int param_1)

{
  zz_0009958_(*(int *)(param_1 + 0x144),1);
  return;
}



// ==== 800a0b34  FUN_800a0b34 ====

void FUN_800a0b34(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined *param_12,undefined4 param_13,int param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  if (((*(char *)(param_9 + 0x171) != '\0') ||
      ((((-1 < (char)PTR_DAT_80433934[*(char *)(param_9 + 0x173) + 0xc0] &&
         (cVar1 = zz_008b290_(), cVar1 == '\0')) && (PTR_DAT_80433934[0x1833] == '\0')) &&
       (PTR_DAT_80433934[0x1832] == '\0')))) && (PTR_DAT_80433930[0x33] == '\0')) {
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      zz_009f904_(param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 2:
      zz_009fcac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 5:
      zz_009fe08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 6:
      zz_009fedc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 7:
      zz_00a0008_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 8:
      FUN_800a01d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 9:
      FUN_800a05b0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 10:
      FUN_800a05f8(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xb:
      FUN_800a06e8(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xc:
      FUN_800a05b0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xe:
      zz_009f770_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xf:
      FUN_800a0958(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x10:
      zz_00a0a54_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x12:
      zz_00a0b0c_(param_9);
    }
  }
  return;
}



// ==== 800a0c88  zz_00a0c88_ ====

bool zz_00a0c88_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x83] = 0x10;
    puVar1[0x10] = 0x39;
    *(code **)(puVar1 + 0xc) = FUN_800a0da0;
    *(code **)(puVar1 + 0x10c) = FUN_800a21bc;
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



// ==== 800a0da0  FUN_800a0da0 ====

void FUN_800a0da0(int param_1)

{
  (*(code *)(&PTR_FUN_802f6f0c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800a0ddc  FUN_800a0ddc ====

void FUN_800a0ddc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar3 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar3;
  iVar4 = *(int *)(param_9 + 0x90);
  iVar1 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_802f6e98 + iVar1);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802f6e94 + iVar1);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802f6e9c + iVar1);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_802f6ea0 + iVar1);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_802f6ea4 + iVar1);
  *(undefined *)(param_9 + 0x89) = (&DAT_802f6e92)[iVar1];
  *(code **)(param_9 + 0x100) = FUN_800480f4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x4d;
  iVar4 = zz_0006f98_(iVar4);
  iVar5 = param_9 + 0x17c;
  *(undefined4 *)(param_9 + 0x17c) = *(undefined4 *)(iVar4 + 0xc28);
  *(undefined1 *)(param_9 + 0x180) = 0;
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_802f6e90 + iVar1),iVar5,iVar3,in_r8,in_r9,in_r10);
  iVar1 = (int)*(short *)(&DAT_802f6e90 + iVar1);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar1,iVar5,iVar3,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar1,iVar5,iVar3,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437fa0,*(int *)(param_9 + 0xe4));
  zz_00a0f00_(param_9);
  return;
}



// ==== 800a0f00  zz_00a0f00_ ====

void zz_00a0f00_(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(char *)(iVar2 + 0x18) < '\x02') && (*(short *)(iVar2 + 1000) == *(short *)(param_1 + 0x94))
     ) {
    if (*(char *)(iVar2 + *(char *)(param_1 + 0x13) + 0x146) == '\0') {
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
    else {
      *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
    }
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      zz_00a1138_(param_1);
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        zz_00a0fe4_(param_1);
      }
    }
    else if (cVar1 < '\x03') {
      zz_00a1c70_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800a0fe4  zz_00a0fe4_ ====

void zz_00a0fe4_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x90);
  uVar2 = *(undefined4 *)(iVar4 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  *(undefined4 *)(param_1 + 0xb4) = uVar2;
  cVar1 = *(char *)(iVar4 + *(char *)(param_1 + 0x13) + 0x146);
  *(undefined1 *)(param_1 + 0xb1) = 0;
  if (*(char *)(param_1 + 0x180) == '\x01') {
    *(undefined1 *)(param_1 + 0x180) = 0;
    iVar3 = zz_0006f98_(iVar4);
    *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(iVar3 + 0xc28);
  }
  if ((cVar1 != '\0') && (cVar1 != '\x02')) {
    if (cVar1 < '\x02') {
      if ('\0' < cVar1) {
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined1 *)(param_1 + 0x1b) = 0;
        *(int *)(param_1 + 0x8c) = iVar4;
        *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(iVar4 + 0x90);
        *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(iVar4 + 0x94);
        *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(iVar4 + 0x96);
        *(undefined1 *)(param_1 + 0x97) = *(undefined1 *)(iVar4 + 0x97);
        *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(iVar4 + 0x88);
        *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar4 + 200);
        *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar4 + 0xcc);
        *(undefined4 *)(param_1 + 0xb8) = *(undefined4 *)(iVar4 + 0xb8);
        *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
        *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(iVar4 + 0xb4);
        *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(iVar4 + 0xb4);
        *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(iVar4 + 0xb4);
        *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar4 + 0xc0);
        *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(iVar4 + 0xc4);
        *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar4 + 0xd0);
      }
    }
    else if (cVar1 < '\x04') {
      zz_00a2654_(param_1);
    }
  }
  return;
}



// ==== 800a1138  zz_00a1138_ ====

void zz_00a1138_(int param_1)

{
  if ((*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x146) == '\x03') ||
     ((*(int *)(param_1 + 0xcc) != 0 && ('\x01' < *(char *)(*(int *)(param_1 + 0xcc) + 0x18))))) {
    zz_00a2654_(param_1);
  }
  else {
    (*(code *)(&PTR_FUN_80433a20)[*(char *)(param_1 + 0x1a)])();
  }
  return;
}



// ==== 800a11b0  FUN_800a11b0 ====

/* WARNING: Removing unreachable block (ram,0x800a1920) */
/* WARNING: Removing unreachable block (ram,0x800a11c0) */

void FUN_800a11b0(int param_1)

{
  uint uVar1;
  char cVar2;
  undefined4 uVar3;
  float fVar4;
  undefined4 uVar5;
  float fVar6;
  short sVar7;
  float fVar8;
  float fVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  float local_4c;
  float local_48;
  float local_44;
  double local_40;
  double local_38;
  
  cVar2 = *(char *)(param_1 + 0x1b);
  iVar12 = *(int *)(param_1 + 0x90);
  iVar10 = *(char *)(param_1 + 0x13) * 0x18;
  iVar11 = *(int *)(param_1 + 0xcc);
  if (cVar2 == '\x03') {
    sVar7 = *(short *)(param_1 + 0x16e) + -1;
    *(short *)(param_1 + 0x16e) = sVar7;
    fVar8 = FLOAT_80437fd4;
    if (sVar7 < 1) {
      *(undefined2 *)(param_1 + 0x16e) = 0xffff;
      local_4c = (*(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x20)) * fVar8;
      local_48 = (*(float *)(param_1 + 0x158) - *(float *)(param_1 + 0x24)) * fVar8;
      local_44 = (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x28)) * fVar8;
      dVar14 = gnt4_PSVECMag_bl(&local_4c);
      *(float *)(param_1 + 0x44) = (float)dVar14;
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
    }
    if (FLOAT_80437fc8 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = FLOAT_80437fc8;
    }
    dVar14 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x154),(float *)(param_1 + 0x20));
    if ((dVar14 <= (double)FLOAT_80437fc8) ||
       (sVar7 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar7, sVar7 < 1)) {
      zz_00a2654_(param_1);
    }
    else {
      zz_006c440_((double)FLOAT_80437fd0,param_1,(float *)(param_1 + 0x154));
    }
    zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
    dVar14 = (double)*(float *)(param_1 + 0x44);
    zz_00833ec_(param_1);
    zz_0083610_(param_1,(float *)(param_1 + 0x178));
    zz_0083714_(param_1);
    *(float *)(param_1 + 0x44) = (float)dVar14;
    iVar10 = FUN_800a25f8(param_1,3);
    if (iVar10 == 0) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1b) = 5;
    fVar8 = FLOAT_80437fa8;
    *(undefined2 *)(param_1 + 0x1c) = 0xf;
    *(float *)(param_1 + 0x44) = fVar8;
    return;
  }
  if ('\x02' < cVar2) {
    if (cVar2 == '\x05') {
      sVar7 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar7;
      if (-1 < sVar7) {
        return;
      }
      zz_00a2654_(param_1);
      return;
    }
    if ('\x04' < cVar2) {
      return;
    }
    if (*(char *)(iVar11 + 0x83) == '\0') {
      dVar14 = zz_0045204_(*(short *)(param_1 + 0x16c));
      dVar15 = (double)(float)((double)(FLOAT_80437fd8 + *(float *)(iVar11 + 0x770)) * dVar14);
      dVar14 = zz_0045238_(*(short *)(param_1 + 0x16c));
      fVar4 = FLOAT_80437fdc;
      fVar9 = FLOAT_80437fd8;
      fVar8 = *(float *)(iVar11 + 0x770);
      fVar6 = *(float *)(iVar11 + 0x900);
      *(float *)(param_1 + 0x154) = (float)((double)*(float *)(iVar11 + 0x8e0) + dVar15);
      *(float *)(param_1 + 0x158) = fVar4 + *(float *)(iVar11 + 0x24) + *(float *)(iVar11 + 0x668);
      *(float *)(param_1 + 0x15c) = fVar6 + (float)((double)(fVar9 + fVar8) * dVar14);
    }
    else {
      iVar10 = *(int *)(param_1 + 200);
      fVar9 = *(float *)(iVar10 + 100);
      fVar8 = *(float *)(iVar10 + 0x68);
      fVar6 = *(float *)(iVar10 + 0x6c);
      dVar14 = zz_0045204_(*(short *)(param_1 + 0x16c));
      dVar16 = (double)(float)((double)FLOAT_80437fe0 * dVar14);
      dVar14 = zz_0045238_(*(short *)(param_1 + 0x16c));
      dVar15 = (double)FLOAT_80437fe0;
      fVar8 = FLOAT_80437fdc + fVar8;
      *(float *)(param_1 + 0x154) = (float)((double)fVar9 + dVar16);
      *(float *)(param_1 + 0x158) = fVar8;
      *(float *)(param_1 + 0x15c) = fVar6 + (float)(dVar15 * dVar14);
    }
    sVar7 = *(short *)(param_1 + 0x16e) + -1;
    *(short *)(param_1 + 0x16e) = sVar7;
    fVar8 = FLOAT_80437fd4;
    if (sVar7 < 1) {
      *(undefined2 *)(param_1 + 0x16e) = 0xffff;
      local_4c = (*(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x20)) * fVar8;
      local_48 = (*(float *)(param_1 + 0x158) - *(float *)(param_1 + 0x24)) * fVar8;
      local_44 = (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x28)) * fVar8;
      dVar14 = gnt4_PSVECMag_bl(&local_4c);
      *(float *)(param_1 + 0x44) = (float)dVar14;
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
    }
    if (*(float *)(param_1 + 0x178) < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x178);
    }
    dVar14 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x154),(float *)(param_1 + 0x20));
    if ((dVar14 <= (double)FLOAT_80437fc8) ||
       (sVar7 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar7, sVar7 < 1)) {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined1 *)(param_1 + 0x1b) = 0;
    }
    else {
      zz_006c440_((double)FLOAT_80437fd0,param_1,(float *)(param_1 + 0x154));
    }
    zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0);
    dVar14 = (double)*(float *)(param_1 + 0x44);
    zz_00833ec_(param_1);
    zz_0083610_(param_1,(float *)(param_1 + 0x178));
    zz_0083714_(param_1);
    *(float *)(param_1 + 0x44) = (float)dVar14;
    iVar10 = FUN_800a25f8(param_1,3);
    if (iVar10 == 0) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1b) = 5;
    fVar8 = FLOAT_80437fa8;
    *(undefined2 *)(param_1 + 0x1c) = 0xf;
    *(float *)(param_1 + 0x44) = fVar8;
    return;
  }
  if (cVar2 != '\x01') {
    if ('\0' < cVar2) goto LAB_800a1464;
    if (cVar2 < '\0') {
      return;
    }
    zz_0089444_(param_1);
    *(code **)(param_1 + 0x100) = FUN_800a2234;
    zz_0089100_(param_1,1,1);
    fVar8 = FLOAT_80437fa4;
    uVar5 = *(undefined4 *)(&DAT_802f6e98 + iVar10);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802f6e94 + iVar10);
    local_4c = FLOAT_80437fa8;
    *(undefined4 *)(param_1 + 0x68) = uVar5;
    local_44 = FLOAT_80437fb0;
    local_48 = FLOAT_80437fac;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802f6e9c + iVar10);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_802f6ea0 + iVar10);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802f6ea4 + iVar10);
    *(undefined *)(param_1 + 0x89) = (&DAT_802f6e92)[iVar10];
    *(undefined2 *)(param_1 + 0x188) = *(undefined2 *)(&DAT_802f6ea4 + iVar10);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
    *(float *)(param_1 + 0xd4) = fVar8;
    gnt4_PSMTXMultVec_bl((float *)(iVar12 + 0x904),&local_4c,(float *)(param_1 + 0x148));
    *(undefined1 *)(param_1 + 0x17c) = 0xff;
    *(undefined1 *)(param_1 + 0x17d) = 0xff;
    *(undefined1 *)(param_1 + 0x17e) = 0xff;
    *(undefined1 *)(param_1 + 0x180) = 1;
    *(undefined1 *)(param_1 + 0x1b) = 1;
    zz_00f036c_(param_1,0xfa);
  }
  fVar8 = *(float *)(param_1 + 0xd4) - *(float *)(iVar12 + 0x768);
  bVar13 = fVar8 <= FLOAT_80437fa8;
  *(float *)(param_1 + 0xd4) = fVar8;
  fVar8 = FLOAT_80437fb8;
  if (bVar13) {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x148);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x14c);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x150);
    *(undefined1 *)(param_1 + 0x17c) = 0;
    *(undefined1 *)(param_1 + 0x17d) = 0;
    *(undefined1 *)(param_1 + 0x17e) = 0;
    *(undefined1 *)(param_1 + 0x180) = 0;
  }
  else {
    fVar6 = *(float *)(param_1 + 0xd4) / FLOAT_80437fa4;
    fVar9 = FLOAT_80437fb4 - fVar6;
    *(float *)(param_1 + 0x20) =
         *(float *)(param_1 + 0x20) * fVar6 + fVar9 * *(float *)(param_1 + 0x148);
    *(float *)(param_1 + 0x24) =
         *(float *)(param_1 + 0x24) * fVar6 + fVar9 * *(float *)(param_1 + 0x14c);
    *(float *)(param_1 + 0x28) =
         *(float *)(param_1 + 0x28) * fVar6 + fVar9 * *(float *)(param_1 + 0x150);
    uVar1 = (uint)(fVar8 * *(float *)(iVar12 + 0x768));
    if ((uint)*(byte *)(param_1 + 0x17c) < (uVar1 & 0xff)) {
      *(undefined1 *)(param_1 + 0x17e) = 0;
      *(undefined1 *)(param_1 + 0x17d) = 0;
      *(undefined1 *)(param_1 + 0x17c) = 0;
    }
    else {
      cVar2 = (char)uVar1;
      *(byte *)(param_1 + 0x17c) = *(byte *)(param_1 + 0x17c) - cVar2;
      *(char *)(param_1 + 0x17d) = *(char *)(param_1 + 0x17d) - cVar2;
      *(char *)(param_1 + 0x17e) = *(char *)(param_1 + 0x17e) - cVar2;
    }
  }
  local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x188)) ^ 0x80000000);
  iVar10 = (int)(FLOAT_80437fbc * *(float *)(iVar12 + 0x1dc8) + (float)(local_40 - DOUBLE_80437fe8))
  ;
  local_38 = (double)(longlong)iVar10;
  *(short *)(param_1 + 0x188) = (short)iVar10;
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(param_1 + 0x188);
  if (*(char *)(iVar12 + *(char *)(param_1 + 0x13) + 0x146) != '\x02') {
    return;
  }
  *(undefined2 *)(param_1 + 0x16c) = *(undefined2 *)(iVar12 + *(char *)(param_1 + 0x13) * 2 + 0x14a)
  ;
  *(undefined1 *)(param_1 + 0x1b) = 2;
LAB_800a1464:
  uVar5 = DAT_802b0cb4;
  *(code **)(param_1 + 0x100) = FUN_800a22d0;
  uVar3 = DAT_802b0cb8;
  *(undefined4 *)(param_1 + 0x9c) = uVar5;
  uVar5 = DAT_802b0cbc;
  *(undefined4 *)(param_1 + 0xa0) = uVar3;
  *(undefined4 *)(param_1 + 0xa4) = uVar5;
  *(undefined1 *)(param_1 + 0x98) = 5;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  fVar8 = FLOAT_80437fa8;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  dVar14 = DOUBLE_80437fe8;
  fVar6 = FLOAT_80437fc0;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  fVar9 = FLOAT_80437fc4;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  *(float *)(param_1 + 0x154) = fVar8;
  local_38 = (double)(CONCAT44(0x43300000,*(char *)(param_1 + 0x13) * 0x1e) ^ 0x80000000);
  *(float *)(param_1 + 0x158) = (fVar6 + *(float *)(iVar12 + 0x668)) - (float)(local_38 - dVar14);
  *(float *)(param_1 + 0x15c) = fVar9;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar12 + 0x8d4),(float *)(param_1 + 0x154),(float *)(param_1 + 0x154));
  fVar8 = FLOAT_80437fc8;
  *(undefined2 *)(param_1 + 0x16e) = 7;
  fVar6 = FLOAT_80437fcc;
  *(float *)(param_1 + 0x178) = fVar8;
  fVar8 = FLOAT_80437fd0;
  *(float *)(param_1 + 0x44) = fVar6;
  *(float *)(param_1 + 0x4c) = fVar8;
  zz_008ac80_(param_1,(int)DAT_802f6ef0);
  if ((*(int *)(param_1 + 0xcc) == 0) || ((*(byte *)(param_1 + 0xd0) & 4) == 0)) {
    *(undefined1 *)(param_1 + 0x1b) = 3;
  }
  else {
    *(undefined1 *)(param_1 + 0x1b) = 4;
  }
  zz_00f036c_(param_1,0xfb);
  *(undefined2 *)(param_1 + 0x1c) = 300;
  return;
}



// ==== 800a193c  FUN_800a193c ====

/* WARNING: Removing unreachable block (ram,0x800a1c50) */
/* WARNING: Removing unreachable block (ram,0x800a1c48) */
/* WARNING: Removing unreachable block (ram,0x800a1c40) */
/* WARNING: Removing unreachable block (ram,0x800a195c) */
/* WARNING: Removing unreachable block (ram,0x800a1954) */
/* WARNING: Removing unreachable block (ram,0x800a194c) */

void FUN_800a193c(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  float *pfVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [3];
  longlong local_40;
  
  if ('\x01' < *(char *)(*(int *)(param_1 + 0xcc) + 0x18)) {
    zz_00a2654_(param_1);
    return;
  }
  cVar1 = *(char *)(param_1 + 0x1b);
  if (cVar1 == '\x02') {
    pfVar5 = (float *)(param_1 + 0x148);
    *(undefined1 *)(param_1 + 0x84) = 0x18;
    dVar7 = (double)FLOAT_80437fd4;
    iVar4 = *(int *)(param_1 + 200);
    local_58 = *(float *)(iVar4 + 100);
    local_54 = *(float *)(iVar4 + 0x68);
    local_50 = *(float *)(iVar4 + 0x6c);
    dVar9 = (double)(local_58 - *(float *)(param_1 + 0x20));
    dVar8 = (double)(local_54 - *(float *)(param_1 + 0x24));
    dVar6 = (double)(local_50 - *(float *)(param_1 + 0x28));
    *(float *)(param_1 + 0x148) = (float)(dVar9 * dVar7);
    *(float *)(param_1 + 0x14c) = (float)(dVar8 * dVar7);
    *(float *)(param_1 + 0x150) = (float)(dVar6 * dVar7);
    dVar7 = gnt4_PSVECMag_bl(pfVar5);
    *(float *)(param_1 + 0x44) = (float)dVar7;
    *pfVar5 = (float)dVar9;
    *(float *)(param_1 + 0x14c) = (float)dVar8;
    *(float *)(param_1 + 0x150) = (float)dVar6;
    gnt4_PSVECNormalize_bl(pfVar5,pfVar5);
    if (*(float *)(param_1 + 0x178) < *(float *)(param_1 + 0x44)) {
      iVar4 = (int)(FLOAT_80437fcc +
                   (FLOAT_80437ff0 * *(float *)(param_1 + 0x44)) / *(float *)(param_1 + 0x178));
      local_40 = (longlong)iVar4;
      *(short *)(param_1 + 0x1c) = (short)iVar4;
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x178);
    }
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1b) = 1;
        zz_0089444_(param_1);
        *(code **)(param_1 + 0x100) = FUN_800a23c4;
        zz_0089100_(param_1,1,1);
        *(undefined1 *)(param_1 + 0x84) = 0x14;
        *(undefined2 *)(param_1 + 0x74) = 0;
        *(undefined2 *)(param_1 + 0x72) = 0;
        *(undefined2 *)(param_1 + 0x70) = 0;
        *(undefined2 *)(param_1 + 0x1c) = 0x14;
      }
      else if (cVar1 < '\0') goto LAB_800a1c1c;
      iVar4 = *(int *)(param_1 + 200);
      local_58 = *(float *)(iVar4 + 100);
      local_54 = *(float *)(iVar4 + 0x68);
      local_50 = *(float *)(iVar4 + 0x6c);
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1800;
      zz_006d228_(param_1,*(int *)(param_1 + 0xcc),0x81);
      sVar3 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar3;
      if (sVar3 < 0) {
        *(undefined1 *)(param_1 + 0x1b) = 2;
        dVar7 = (double)FLOAT_80437fdc;
        *(undefined2 *)(param_1 + 0x1c) = 0x10;
        FUN_8006c1c8(dVar7,param_1,&local_58);
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        *(undefined2 *)(param_1 + 0x72) = 0;
      }
      goto LAB_800a1c1c;
    }
    if (cVar1 == '\x04') {
      sVar3 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar3;
      if (sVar3 < 0) {
        zz_00a2654_(param_1);
      }
      goto LAB_800a1c1c;
    }
    if ('\x03' < cVar1) goto LAB_800a1c1c;
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x148),afStack_4c);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_4c,(float *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x13) < '\x02') {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1a00;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1500;
  }
  iVar4 = FUN_800a25f8(param_1,3);
  if (iVar4 == 0) {
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (sVar3 < 0) {
      zz_00a2654_(param_1);
      *(undefined2 *)(param_1 + 0x74) = 0;
      *(undefined2 *)(param_1 + 0x72) = 0;
      *(undefined2 *)(param_1 + 0x70) = 0;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x1b) = 4;
    fVar2 = FLOAT_80437fa8;
    *(undefined2 *)(param_1 + 0x1c) = 0xf;
    *(float *)(param_1 + 0x44) = fVar2;
  }
LAB_800a1c1c:
  dVar7 = (double)*(float *)(param_1 + 0x44);
  zz_00833ec_(param_1);
  zz_0083610_(param_1,(float *)(param_1 + 0x178));
  zz_0083714_(param_1);
  *(float *)(param_1 + 0x44) = (float)dVar7;
  return;
}



// ==== 800a1c70  zz_00a1c70_ ====

void zz_00a1c70_(int param_1)

{
  (*(code *)(&PTR_FUN_80433a28)[*(char *)(param_1 + 0x1a)])();
  return;
}



// ==== 800a1ca8  FUN_800a1ca8 ====

void FUN_800a1ca8(int param_1)

{
  float fVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x180) == '\x01') {
    *(undefined1 *)(param_1 + 0x180) = 0;
    iVar2 = zz_0006f98_(*(int *)(param_1 + 0x90));
    *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(iVar2 + 0xc28);
  }
  fVar1 = FLOAT_80437ff4;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
  *(float *)(param_1 + 0x44) = fVar1;
  zz_0089444_(param_1);
  *(code **)(param_1 + 0x100) = FUN_800a2554;
  zz_0089100_(param_1,1,1);
  *(undefined2 *)(param_1 + 0x174) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 1;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  zz_00a1d54_(param_1);
  return;
}



// ==== 800a1d54  zz_00a1d54_ ====

/* WARNING: Removing unreachable block (ram,0x800a216c) */
/* WARNING: Removing unreachable block (ram,0x800a2164) */
/* WARNING: Removing unreachable block (ram,0x800a1d6c) */
/* WARNING: Removing unreachable block (ram,0x800a1d64) */

void zz_00a1d54_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  float afStack_b0 [3];
  float afStack_a4 [2];
  float local_9c;
  float local_8c;
  float local_7c;
  float afStack_74 [13];
  undefined4 local_40;
  uint uStack_3c;
  
  fVar4 = FLOAT_80437ff8;
  cVar1 = *(char *)(param_1 + 0x1b);
  iVar7 = *(int *)(param_1 + 0x90);
  iVar6 = *(char *)(param_1 + 0x13) * 0x18;
  if (cVar1 == '\x01') {
    zz_0089444_(param_1);
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    fVar4 = FLOAT_80438004;
    *(undefined1 *)(param_1 + 0x84) = 0x1e;
    uVar5 = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar5;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined4 *)(param_1 + 0x58) = uVar5;
    *(float *)(param_1 + 0xd4) = fVar4;
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      fVar2 = *(float *)(iVar7 + 0x8f0);
      uVar5 = *(undefined4 *)(iVar7 + 0x900);
      *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(iVar7 + 0x8e0);
      fVar3 = FLOAT_80437fd4;
      *(float *)(param_1 + 0x158) =
           fVar4 * *(float *)(iVar7 + 0xb4) + fVar2 + *(float *)(iVar7 + 0x668);
      *(undefined4 *)(param_1 + 0x15c) = uVar5;
      *(float *)(param_1 + 0x38) =
           (*(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x20)) * fVar3;
      *(float *)(param_1 + 0x3c) =
           (*(float *)(param_1 + 0x158) - *(float *)(param_1 + 0x24)) * fVar3;
      *(float *)(param_1 + 0x40) =
           (*(float *)(param_1 + 0x15c) - *(float *)(param_1 + 0x28)) * fVar3;
      dVar8 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
      *(float *)(param_1 + 0x44) = (float)dVar8;
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      if (*(float *)(param_1 + 0x44) <= FLOAT_80437ff4) {
        if (*(float *)(param_1 + 0x44) < FLOAT_80437ff4) {
          *(float *)(param_1 + 0x44) = FLOAT_80437ff4;
        }
      }
      else {
        *(float *)(param_1 + 0x44) = FLOAT_80437ff4;
      }
      *(float *)(param_1 + 0x20) =
           *(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x20);
      *(float *)(param_1 + 0x24) =
           *(float *)(param_1 + 0x3c) * *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x24);
      *(float *)(param_1 + 0x28) =
           *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x28);
      *(short *)(param_1 + 0x174) = *(short *)(param_1 + 0x174) + 0x600;
      dVar8 = zz_0045204_(*(short *)(param_1 + 0x174));
      *(float *)(param_1 + 0x184) =
           *(float *)(param_1 + 0xb4) * (float)((double)FLOAT_80437ffc * dVar8);
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0xe00;
      dVar8 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x154),(float *)(param_1 + 0x20));
      if ((double)FLOAT_80438000 < dVar8) {
        return;
      }
      *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
      return;
    }
    if ('\x02' < cVar1) {
      return;
    }
  }
  fVar4 = FLOAT_80438004;
  if (*(float *)(param_1 + 0xd4) <= FLOAT_80437fa8) {
    *(undefined1 *)(iVar7 + *(char *)(param_1 + 0x13) + 0x146) = 0;
    *(char *)(iVar7 + 0x156) = *(char *)(iVar7 + 0x156) + '\x01';
    zz_006de10_(iVar7,2);
    zz_0089444_(param_1);
    *(code **)(param_1 + 0x100) = FUN_800480f4;
    zz_0089100_(param_1,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
    *(undefined1 *)(param_1 + 0x84) = 0x4d;
    *(undefined *)(param_1 + 0x89) = (&DAT_802f6e92)[iVar6];
    uVar5 = *(undefined4 *)(&DAT_802f6e98 + iVar6);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802f6e94 + iVar6);
    *(undefined4 *)(param_1 + 0x68) = uVar5;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802f6e9c + iVar6);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_802f6ea0 + iVar6);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_802f6ea4 + iVar6);
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
    dVar10 = (double)(*(float *)(param_1 + 0xd4) / fVar4);
    gnt4_PSMTXCopy_bl((float *)(iVar7 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),afStack_74);
    gnt4_PSMTXMultVec_bl(afStack_74,(float *)(&DAT_802f6e94 + iVar6),afStack_b0);
    zz_0046588_(dVar10,(float *)(param_1 + 0x20),afStack_b0,(float *)(param_1 + 0x20));
    local_40 = 0x43300000;
    uStack_3c = (int)*(short *)(&DAT_802f6ea2 + iVar6) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80438008 *
                                (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80437fe8)),
                        afStack_a4,0x79);
    gnt4_PSMTXConcat_bl(afStack_74,afStack_a4,afStack_a4);
    local_c8 = local_9c;
    local_c4 = local_8c;
    local_c0 = local_7c;
    local_bc = *(float *)(param_1 + 0x11c);
    local_b8 = *(undefined4 *)(param_1 + 300);
    local_b4 = *(undefined4 *)(param_1 + 0x13c);
    zz_0046588_(dVar10,&local_bc,&local_c8,&local_c8);
    dVar9 = (double)local_c4;
    local_c4 = FLOAT_80437fa8;
    dVar8 = gnt4_PSVECMag_bl(&local_c8);
    iVar6 = FUN_800452a0(-dVar9,dVar8);
    *(short *)(param_1 + 0x70) = (short)iVar6;
    iVar6 = FUN_800452a0((double)local_c8,(double)local_c0);
    *(short *)(param_1 + 0x72) = (short)iVar6;
    dVar8 = (double)FLOAT_80437fb4;
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(float *)(param_1 + 0xb4) =
         (float)((double)*(float *)(param_1 + 0xb4) * dVar10 +
                (double)((float)(dVar8 - dVar10) * *(float *)(iVar7 + 0xb4)));
    uVar5 = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar5;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined4 *)(param_1 + 0x58) = uVar5;
    *(float *)(param_1 + 0xd4) = (float)((double)*(float *)(param_1 + 0xd4) - dVar8);
  }
  return;
}



// ==== 800a219c  FUN_800a219c ====

void FUN_800a219c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800a21bc  FUN_800a21bc ====

void FUN_800a21bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = *(int *)(param_9 + 0xe0);
    uVar2 = 1;
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 800a2234  FUN_800a2234 ====

/* WARNING: Removing unreachable block (ram,0x800a2248) */

void FUN_800a2234(int param_1)

{
  double dVar1;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438008 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  *(undefined2 *)(param_1 + 0x74) = 0;
  zz_00456f8_((float *)(param_1 + 0x114));
  dVar1 = (double)*(float *)(param_1 + 0xb4);
  gnt4_PSMTXScale_bl(dVar1,dVar1,dVar1,afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800a22d0  FUN_800a22d0 ====

void FUN_800a22d0(int param_1)

{
  bool bVar1;
  double dVar2;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [14];
  
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                      param_1 + 0x9c);
  if (bVar1) {
    local_40 = *(float *)(param_1 + 0x9c);
    local_48 = *(float *)(param_1 + 0xa0);
    if ((local_40 == local_48) && (local_44 = *(float *)(param_1 + 0xa4), local_40 == local_44)) {
      local_48 = FLOAT_80437fd0 + local_48;
    }
    else {
      local_44 = *(float *)(param_1 + 0xa4);
      local_40 = *(float *)(param_1 + 0x9c);
    }
    bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                        &local_48);
    if (bVar1) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
  }
  dVar2 = (double)*(float *)(param_1 + 0xb4);
  gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_3c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800a23c4  FUN_800a23c4 ====

/* WARNING: Removing unreachable block (ram,0x800a24f0) */
/* WARNING: Removing unreachable block (ram,0x800a24c0) */
/* WARNING: Removing unreachable block (ram,0x800a2490) */

void FUN_800a23c4(int param_1)

{
  byte bVar1;
  bool bVar2;
  double dVar3;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [13];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                      param_1 + 0x9c);
  if (bVar2) {
    local_40 = *(float *)(param_1 + 0x9c);
    local_48 = *(float *)(param_1 + 0xa0);
    if ((local_40 == local_48) && (local_44 = *(float *)(param_1 + 0xa4), local_40 == local_44)) {
      local_48 = FLOAT_80437fd0 + local_48;
    }
    else {
      local_44 = *(float *)(param_1 + 0xa4);
      local_40 = *(float *)(param_1 + 0x9c);
    }
    bVar2 = zz_0045ef4_((float *)(param_1 + 0x114),(int)*(char *)(param_1 + 0x98),param_1 + 0x38,
                        &local_48);
    if (bVar2) {
      gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    }
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438008 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_3c,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438008 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_3c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438008 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_3c,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  }
  dVar3 = (double)*(float *)(param_1 + 0xb4);
  gnt4_PSMTXScale_bl(dVar3,dVar3,dVar3,afStack_3c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  return;
}



// ==== 800a2554  FUN_800a2554 ====

/* WARNING: Removing unreachable block (ram,0x800a2570) */

void FUN_800a2554(int param_1)

{
  double dVar1;
  float afStack_38 [13];
  
  gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438008 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  dVar1 = (double)*(float *)(param_1 + 0xb4);
  gnt4_PSMTXScale_bl(dVar1,dVar1,dVar1,afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  *(float *)(param_1 + 0x130) = *(float *)(param_1 + 0x130) + *(float *)(param_1 + 0x184);
  return;
}



// ==== 800a25f8  FUN_800a25f8 ====

undefined4 FUN_800a25f8(int param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((param_2 & 1) != 0) && (*(char *)(param_1 + 0x1d9) != '\0')) {
    return 1;
  }
  if (((param_2 & 2) == 0) || (iVar1 = zz_0084170_(param_1), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 800a2654  zz_00a2654_ ====

void zz_00a2654_(int param_1)

{
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 800a2684  zz_00a2684_ ====

void zz_00a2684_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 2) || (*(short *)(param_1 + 1000) == 0xb)) &&
     (puVar1 = zz_0088aa0_(param_1,3,8,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x10] = 0x11;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800a27b8;
    *(code **)(puVar1 + 0x10c) = FUN_800a2ba4;
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
    *(undefined4 *)(puVar1 + 0x20) = *(undefined4 *)(param_1 + 0xaf0);
    *(undefined4 *)(puVar1 + 0x24) = *(undefined4 *)(param_1 + 0xb00);
    *(undefined4 *)(puVar1 + 0x28) = *(undefined4 *)(param_1 + 0xb10);
    zz_0083d60_((int)puVar1,param_1,0);
  }
  return;
}



// ==== 800a27b8  FUN_800a27b8 ====

void FUN_800a27b8(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_802f6f20)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800a2850  FUN_800a2850 ====

void FUN_800a2850(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  uVar4 = DAT_802b0cb8;
  *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
  uVar1 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar4;
  *(undefined4 *)(param_9 + 0xa4) = uVar1;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar5 = *(int *)(param_9 + 0x90);
  iVar3 = zz_008ac80_(param_9,0);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar6 = gnt4_PSQUATScale_bl((double)FLOAT_80438010,(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined2 *)(param_9 + 0x74) = 0;
    fVar2 = FLOAT_80438010;
    *(undefined2 *)(param_9 + 0x80) = 0xf000;
    *(float *)(param_9 + 0x44) = fVar2;
    *(undefined1 *)(param_9 + 0x1cb) = 2;
    iVar3 = zz_0006f98_(iVar5);
    zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                (float *)(int)*(short *)(&DAT_80433a30 + *(char *)(param_9 + 0x11) * 2),
                (int)*(char *)(param_9 + 0x88),uVar4,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00f036c_(param_9,199);
  }
  return;
}



// ==== 800a2980  FUN_800a2980 ====

void FUN_800a2980(int param_1)

{
  short sVar2;
  int iVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if ((sVar2 < 1) || (iVar1 = zz_0083244_((float *)(param_1 + 0x20)), iVar1 != 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  if (*(byte *)(param_1 + 0x1d9) != 0) {
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
      iVar1 = *(int *)(param_1 + 0x290);
      if (*(char *)(iVar1 + 0x83) != '\0') {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
        *(undefined1 *)(param_1 + 0x82) = 0;
        return;
      }
      if (FLOAT_80438014 <= *(float *)(iVar1 + 0x204)) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
        *(undefined1 *)(param_1 + 0x82) = 0;
        return;
      }
      local_18 = *(undefined4 *)(iVar1 + 0x910);
      local_14 = *(undefined4 *)(iVar1 + 0x920);
      local_10 = *(undefined4 *)(iVar1 + 0x930);
      zz_00a2d7c_(*(int *)(param_1 + 0x90),iVar1,&local_18);
      *(undefined1 *)(iVar1 + 0x719) = 1;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  FUN_80083874((double)FLOAT_80438018,param_1);
  FUN_80083ad4((double)FLOAT_8043801c,param_1,2);
  zz_00833ec_(param_1);
  zz_0083524_(param_1);
  iVar1 = zz_0083714_(param_1);
  if (iVar1 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  iVar1 = zz_0084170_(param_1);
  if (iVar1 == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800a2b50  FUN_800a2b50 ====

void FUN_800a2b50(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800a2b84  FUN_800a2b84 ====

void FUN_800a2b84(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800a2ba4  FUN_800a2ba4 ====

void FUN_800a2ba4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  float afStack_38 [13];
  
  pfVar1 = afStack_38;
  iVar2 = (int)*(short *)(param_9 + 0x74);
  uVar3 = zz_00457d4_('z',(float *)(param_9 + 0x114),pfVar1,*(short *)(param_9 + 0x74));
  zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 800a2bf8  zz_00a2bf8_ ====

void zz_00a2bf8_(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4,int param_5,
                undefined1 param_6)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,8,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 4;
    puVar1[0x11] = (char)param_5;
    puVar1[0x12] = param_6;
    *(code **)(puVar1 + 0xc) = FUN_800a2ef8;
    *(code **)(puVar1 + 0x10c) = FUN_800a3288;
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
    *(undefined4 *)(puVar1 + 0x15c) = param_2;
    *(undefined4 *)(puVar1 + 0x20) = *param_3;
    *(undefined4 *)(puVar1 + 0x24) = param_3[1];
    *(undefined4 *)(puVar1 + 0x28) = param_3[2];
    *(undefined4 **)(puVar1 + 0x16c) = param_3;
    *(undefined4 **)(puVar1 + 0x170) = param_4;
    *(undefined4 *)(puVar1 + 0x144) = *param_3;
    *(undefined4 *)(puVar1 + 0x148) = param_3[1];
    *(undefined4 *)(puVar1 + 0x14c) = param_3[2];
    *(undefined4 *)(puVar1 + 0x150) = *param_4;
    *(undefined4 *)(puVar1 + 0x154) = param_4[1];
    *(undefined4 *)(puVar1 + 0x158) = param_4[2];
    if (param_5 == 5) {
      *(undefined1 *)(param_1 + 0xb0) = 0;
    }
    *(short *)(puVar1 + 0x17c) =
         (short)*(char *)(param_1 + 0x1afd) + *(char *)(param_1 + 0x1afc) * 0x1000;
  }
  return;
}



// ==== 800a2d7c  zz_00a2d7c_ ====

void zz_00a2d7c_(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,8,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 4;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_800a2ef8;
    *(code **)(puVar1 + 0x10c) = FUN_800a3288;
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
    *(undefined4 *)(puVar1 + 0x15c) = param_2;
    *(undefined4 *)(puVar1 + 0x20) = *param_3;
    *(undefined4 *)(puVar1 + 0x24) = param_3[1];
    *(undefined4 *)(puVar1 + 0x28) = param_3[2];
    *(undefined4 **)(puVar1 + 0x16c) = param_3;
    *(undefined4 **)(puVar1 + 0x170) = param_3;
    *(undefined4 *)(puVar1 + 0x144) = *param_3;
    *(undefined4 *)(puVar1 + 0x148) = param_3[1];
    *(undefined4 *)(puVar1 + 0x14c) = param_3[2];
    *(undefined4 *)(puVar1 + 0x150) = *param_3;
    *(undefined4 *)(puVar1 + 0x154) = param_3[1];
    *(undefined4 *)(puVar1 + 0x158) = param_3[2];
    *(short *)(puVar1 + 0x17c) =
         (short)*(char *)(param_1 + 0x1afd) + *(char *)(param_1 + 0x1afc) * 0x1000;
  }
  return;
}



