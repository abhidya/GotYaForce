// ==== 801e307c  zz_01e307c_ ====

void zz_01e307c_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2b;
    puVar1[0x11] = 0;
    puVar1[0x13] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801e3268;
    *(code **)(puVar1 + 0x10c) = FUN_801e3734;
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



// ==== 801e3170  zz_01e3170_ ====

void zz_01e3170_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2b;
    puVar1[0x11] = 1;
    puVar1[0x13] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801e3268;
    *(code **)(puVar1 + 0x10c) = FUN_801e3734;
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



// ==== 801e3268  FUN_801e3268 ====

void FUN_801e3268(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(iVar1 + 0x18) < '\x02') {
      if ((*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94)) &&
         (*(char *)(iVar1 + 0x6f4) != '\0')) goto LAB_801e32d0;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801e32d0:
  (*(code *)(&PTR_FUN_80391a68)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e3300  FUN_801e3300 ====

void FUN_801e3300(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  uVar5 = zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0xd0;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(undefined1 *)(param_9 + 0x89) = 1;
  *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(iVar4 + 0x908);
  *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(iVar4 + 0x918);
  *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(iVar4 + 0x928);
  *(undefined2 *)(param_9 + 0x1c) = 0;
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x7c) = (short)(uVar3 << 8);
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x7e) = (short)(uVar3 << 8);
  fVar1 = FLOAT_8043c1c8;
  *(undefined2 *)(param_9 + 0x80) = 0x1999;
  *(float *)(param_9 + 0x150) = fVar1;
  *(undefined1 *)(param_9 + 0x154) = 0;
  *(undefined1 *)(param_9 + 0x155) = 10;
  uVar2 = *(undefined4 *)(iVar4 + 0x24);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(iVar4 + 0x20);
  *(undefined4 *)(param_9 + 0x148) = uVar2;
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(iVar4 + 0x28);
  if (*(char *)(param_9 + 0x11) == '\0') {
    iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
    uVar5 = zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                        *(int *)(param_9 + 0xe0),(float *)0xc,(int)*(char *)(param_9 + 0x88),in_r7,
                        in_r8,in_r9,in_r10);
  }
  else {
    iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
    uVar5 = zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                        *(int *)(param_9 + 0xe0),(float *)0xe,(int)*(char *)(param_9 + 0x88),in_r7,
                        in_r8,in_r9,in_r10);
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  zz_01e3438_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e3438  zz_01e3438_ ====

void zz_01e3438_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  double dVar5;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar4 = *(int *)(param_9 + 0x90);
  *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + *(short *)(param_9 + 0x7c);
  *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7e);
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + *(short *)(param_9 + 0x80);
  *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(iVar4 + 0x908);
  *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(iVar4 + 0x918);
  *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(iVar4 + 0x928);
  if (*(char *)(param_9 + 0x11) == '\0') {
    gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x20),(float *)(iVar4 + 0x2c),&local_18);
    dVar5 = gnt4_PSVECSquareMag_bl(&local_18);
    if (dVar5 <= (double)FLOAT_8043c1cc) {
      *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar4 + 0x90c);
      *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(iVar4 + 0x91c);
      *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar4 + 0x92c);
    }
    else {
      *(float *)(param_9 + 0x38) = local_18;
      *(undefined4 *)(param_9 + 0x3c) = local_14;
      *(undefined4 *)(param_9 + 0x40) = local_10;
    }
    fVar3 = FLOAT_8043c1d4;
    fVar2 = FLOAT_8043c1c8;
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 == '\x01') {
      if (*(char *)(iVar4 + 0x6f4) == '\x01') {
        *(undefined1 *)(param_9 + 0x19) = 0;
        iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
        zz_000726c_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                    *(int *)(param_9 + 0xe0),(float *)0xc,(int)*(char *)(param_9 + 0x88),in_r7,in_r8
                    ,in_r9,in_r10);
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      if (*(char *)(iVar4 + 0x6f4) == '\x02') {
        *(undefined1 *)(param_9 + 0x19) = 1;
        iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
        zz_000726c_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                    *(int *)(param_9 + 0xe0),(float *)0xd,(int)*(char *)(param_9 + 0x88),in_r7,in_r8
                    ,in_r9,in_r10);
        zz_01e3170_(param_9);
      }
      else {
        if (*(char *)(param_9 + 0x154) == '\0') {
          *(float *)(param_9 + 0x150) = *(float *)(param_9 + 0x150) - FLOAT_8043c1d0;
          if (*(float *)(param_9 + 0x150) <= fVar3) {
            *(float *)(param_9 + 0x150) = fVar3;
            *(undefined1 *)(param_9 + 0x154) = 1;
          }
        }
        else {
          *(float *)(param_9 + 0x150) = *(float *)(param_9 + 0x150) + FLOAT_8043c1d0;
          if (fVar2 <= *(float *)(param_9 + 0x150)) {
            *(float *)(param_9 + 0x150) = fVar2;
            *(undefined1 *)(param_9 + 0x154) = 0;
          }
        }
        *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) * *(float *)(param_9 + 0x150);
        *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) * *(float *)(param_9 + 0x150);
        *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x60) * *(float *)(param_9 + 0x150);
      }
    }
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x20),(float *)(param_9 + 0x144),&local_18);
    dVar5 = gnt4_PSVECSquareMag_bl(&local_18);
    if (dVar5 <= (double)FLOAT_8043c1cc) {
      *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar4 + 0x90c);
      *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(iVar4 + 0x91c);
      *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar4 + 0x92c);
    }
    else {
      *(float *)(param_9 + 0x38) = local_18;
      *(undefined4 *)(param_9 + 0x3c) = local_14;
      *(undefined4 *)(param_9 + 0x40) = local_10;
    }
    dVar5 = gnt4_PSVECMag_bl(&local_18);
    *(float *)(param_9 + 0x60) = (float)(dVar5 / (double)FLOAT_8043c1d8);
    if (*(char *)(iVar4 + 0x6f4) != '\x02') {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x1b) = 0;
      *(undefined1 *)(param_9 + 0x1a) = 0;
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  return;
}



// ==== 801e3700  FUN_801e3700 ====

void FUN_801e3700(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801e3714  FUN_801e3714 ====

void FUN_801e3714(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e3734  FUN_801e3734 ====

/* WARNING: Removing unreachable block (ram,0x801e37c8) */
/* WARNING: Removing unreachable block (ram,0x801e379c) */
/* WARNING: Removing unreachable block (ram,0x801e3774) */

void FUN_801e3734(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float afStack_68 [12];
  float afStack_38 [13];
  
  if (*(char *)(param_9 + 0x11) == '\0') {
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 == '\x01') {
      gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c1dc *
                                         (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                                 0x3ff0000000000000)),afStack_38,0x7a);
      param_11 = afStack_38;
      param_1 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c1dc *
                                         (double)((longlong)(double)*(short *)(param_9 + 0x70) *
                                                 0x3ff0000000000000)),afStack_38,0x78);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,afStack_38);
      gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c1dc *
                                         (double)((longlong)(double)*(short *)(param_9 + 0x72) *
                                                 0x3ff0000000000000)),afStack_68,0x79);
      param_11 = afStack_38;
      param_1 = gnt4_PSMTXConcat_bl(param_11,afStack_68,param_11);
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),afStack_38,(undefined *)param_11,param_12,param_13,param_14
                ,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  else {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),(undefined *)param_11,param_12,
                param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  return;
}



// ==== 801e3838  zz_01e3838_ ====

void zz_01e3838_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2c;
    puVar1[0x11] = param_2;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801e3938;
    *(code **)(puVar1 + 0x10c) = FUN_801e3bc4;
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



// ==== 801e3938  FUN_801e3938 ====

void FUN_801e3938(int param_1)

{
  (*(code *)(&PTR_FUN_80391aa8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e3974  FUN_801e3974 ====

void FUN_801e3974(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x8c) + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x89) = 1;
  fVar1 = FLOAT_8043c1e0;
  iVar3 = *(char *)(param_9 + 0x11) * 0xc;
  uVar4 = *(undefined4 *)(&DAT_80391a78 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80391a7c + iVar3);
  *(undefined4 *)(param_9 + 100) = uVar4;
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  uVar2 = *(undefined4 *)(&DAT_80391a80 + iVar3);
  *(undefined4 *)(param_9 + 0x6c) = uVar2;
  *(undefined2 *)(param_9 + 0x7e) = 0xfa4;
  *(float *)(param_9 + 0x144) = fVar1;
  *(undefined1 *)(param_9 + 0x148) = 0;
  *(undefined1 *)(param_9 + 0x149) = 5;
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),0x60,0xfa4,uVar2,uVar4,&DAT_80391a78 + iVar3,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  return;
}



// ==== 801e3ba4  FUN_801e3ba4 ====

void FUN_801e3ba4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e3bc4  FUN_801e3bc4 ====

void FUN_801e3bc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801e3c04  zz_01e3c04_ ====

void zz_01e3c04_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_80391ab8; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(6,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801e3c84;
      *(code **)(iVar2 + 0x10c) = FUN_801e3ef8;
    }
  }
  return;
}



// ==== 801e3c84  FUN_801e3c84 ====

void FUN_801e3c84(int param_1)

{
  (*(code *)(&PTR_FUN_80391b58)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e3cc0  FUN_801e3cc0 ====

void FUN_801e3cc0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043c1f0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  if ('\x01' < *(char *)(param_9 + 0x11)) {
    *(undefined4 *)(param_9 + 0x174) = 1;
  }
  zz_01e3d5c_(param_9);
  return;
}



// ==== 801e3d5c  zz_01e3d5c_ ====

void zz_01e3d5c_(int param_1)

{
  (*(code *)(&PTR_LAB_80391b68)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e3db8  FUN_801e3db8 ====

void FUN_801e3db8(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    if (*(char *)(DAT_80436354 + *(char *)(param_1 + 0x11) + 0xa0c) != '\0') {
      return;
    }
    *(undefined1 *)(param_1 + 0x19) = 3;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if (*(char *)(DAT_80436354 + *(char *)(param_1 + 0x11) + 0xa0c) == '\0') {
          return;
        }
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 0;
        *(undefined1 *)(param_1 + 0x82) = 4;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + 1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (0x3b < sVar2) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
      goto LAB_801e3e44;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
LAB_801e3e44:
  *(float *)(param_1 + 0x178) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) -
              DOUBLE_8043c1f8) / FLOAT_8043c1f4;
  return;
}



// ==== 801e3ed8  FUN_801e3ed8 ====

void FUN_801e3ed8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e3ef8  FUN_801e3ef8 ====

void FUN_801e3ef8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e3f18  zz_01e3f18_ ====

void zz_01e3f18_(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x2e;
    puVar1[0x11] = param_2;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801e4038;
    *(code **)(puVar1 + 0x10c) = FUN_801e4318;
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
    *(undefined4 *)(puVar1 + 0x158) = param_3;
    *(undefined4 *)(puVar1 + 0x15c) = param_4;
  }
  return;
}



// ==== 801e4038  FUN_801e4038 ====

void FUN_801e4038(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') && ('\x01' < *(char *)(*(int *)(param_1 + 0x8c) + 0x18)))
  {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80391c58)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e40b4  FUN_801e40b4 ====

void FUN_801e40b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  
  cVar1 = *(char *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = cVar1 * 0x38;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80391bea + iVar3);
  *(code **)(param_9 + 0x100) = FUN_801e4368;
  *(undefined1 *)(param_9 + 0x84) = 0x31;
  if (*(short *)(&DAT_80391c10 + iVar3) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 2;
  }
  if (*(short *)(&DAT_80391c12 + iVar3) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 4;
  }
  if (*(short *)(&DAT_80391c14 + iVar3) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 8;
  }
  uVar4 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x90) + 0x3e4) + 0x10,1);
  uVar2 = *(undefined4 *)(&DAT_80391bf0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80391bec + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80391bf4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80391c10 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80391c14 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80391c08 + iVar3);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(&DAT_80391c04 + iVar3);
  *(undefined4 *)(param_9 + 0x5c) = uVar2;
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(&DAT_80391c0c + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80391bfc + iVar3);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(&DAT_80391bf8 + iVar3);
  *(undefined4 *)(param_9 + 0x3c) = uVar2;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(&DAT_80391c00 + iVar3);
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_80391c16 + iVar3);
  *(undefined2 *)(param_9 + 0x80) = 0xfa4;
  *(undefined2 *)(param_9 + 0x160) = *(undefined2 *)(&DAT_80391c1c + iVar3);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_80391be8 + iVar3),param_12,param_13,
              param_14,param_15,param_16);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(undefined2 *)(param_9 + 0x1c) = 0;
  zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_80391c18)[cVar1 * 0xe],
              (float *)(param_9 + 0x14c));
  zz_01e4238_(param_9);
  return;
}



// ==== 801e4238  zz_01e4238_ ====

void zz_01e4238_(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  short sVar3;
  
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  gnt4_PSVECAdd_bl((float *)(param_1 + 100),(float *)(param_1 + 0x38),(float *)(param_1 + 100));
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  uVar2 = zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),
                      (float *)(param_1 + 0x14c));
  if (uVar2 != 0) {
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x148) = 0;
  }
  sVar3 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar3;
  if (sVar3 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801e42e4  FUN_801e42e4 ====

void FUN_801e42e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801e42f8  FUN_801e42f8 ====

void FUN_801e42f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e4318  FUN_801e4318 ====

void FUN_801e4318(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  pfVar1 = (float *)(param_9 + 0x14c);
  uVar2 = zz_00456a0_((float *)(param_9 + 0x114),afStack_38,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),(int)*(short *)(param_9 + 0x160));
  return;
}



// ==== 801e4368  FUN_801e4368 ====

void FUN_801e4368(int param_1)

{
  float afStack_38 [13];
  
  gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x158),(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  gnt4_PSMTXScale_bl((double)(*(float *)(param_1 + 0x58) * **(float **)(param_1 + 0x15c)),
                     (double)(*(float *)(param_1 + 0x5c) * **(float **)(param_1 + 0x15c)),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 801e4504  FUN_801e4504 ====

void FUN_801e4504(int param_1)

{
  if (*(char *)(param_1 + 0x48a) == '\x01') {
    zz_01e92c0_(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0xf06) {
    zz_01ef724_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0xf07) {
    zz_01ef724_(param_1,1);
  }
  return;
}



// ==== 801e4560  FUN_801e4560 ====

void FUN_801e4560(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_80391ca8);
  return;
}



// ==== 801e4598  FUN_801e4598 ====

void FUN_801e4598(int param_1)

{
  (**(code **)(&DAT_80435b58 + *(char *)(param_1 + 0x580) * 4))();
  return;
}



// ==== 801e45d0  FUN_801e45d0 ====

void FUN_801e45d0(int param_1)

{
  (*(code *)(&PTR_LAB_80391cd8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801e463c  FUN_801e463c ====

void FUN_801e463c(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14c) = 1;
  }
  dVar2 = (double)FLOAT_8043c208;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,1,0,(short *)&DAT_80435b50);
  if ((iVar1 == 0) && (FLOAT_8043c204 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801e46c8  FUN_801e46c8 ====

void FUN_801e46c8(int param_1)

{
  float fVar1;
  int iVar2;
  
  FUN_8006cc90((double)FLOAT_8043c208,param_1,1,0,(short *)&DAT_80435b50);
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14c) = 1;
  }
  if (*(short *)(param_1 + 0x14e) == 0) {
    *(undefined2 *)(param_1 + 0x14e) = 0xc;
    *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 1;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      if (*(short *)(param_1 + 1000) != 0xf06) {
        zz_0082824_(param_1,0x7b);
        fVar1 = FLOAT_8043c20c;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
        return;
      }
      zz_0082824_(param_1,0x7a);
    }
    fVar1 = FLOAT_8043c20c;
    if (*(short *)(param_1 + 0x14c) == 0) {
      if (0 < *(short *)(param_1 + 0x150)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x14c) = 0;
      fVar1 = FLOAT_8043c20c;
      if (4 < *(short *)(param_1 + 0x150)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x14e) = *(short *)(param_1 + 0x14e) + -1;
  }
  return;
}



// ==== 801e47f8  FUN_801e47f8 ====

void FUN_801e47f8(int param_1)

{
  float fVar1;
  
  if (FLOAT_8043c204 < *(float *)(param_1 + 0x55c)) {
    FUN_8006cc90((double)FLOAT_8043c208,param_1,2,1,(short *)&DAT_80435b50);
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  fVar1 = FLOAT_8043c204;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  }
  return;
}



// ==== 801e488c  zz_01e488c_ ====

void zz_01e488c_(undefined1 param_1,int param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_80391f18)[param_2]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801e49cc;
    *(code **)(puVar1 + 0x10c) = FUN_801e4b58;
    puVar1[0x10] = 1;
    puVar1[0x11] = (char)param_2;
    puVar1[0x12] = param_3;
    puVar1[0x96] = param_1;
    puVar1[0x13] = (&DAT_80391f18)[(char)puVar1[0x11]];
  }
  return;
}



// ==== 801e493c  FUN_801e493c ====

void FUN_801e493c(int param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = zz_01e488c_(*(undefined1 *)(param_1 + 0x96),param_2,param_3);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x8c) = param_1;
  }
  return;
}



// ==== 801e497c  zz_01e497c_ ====

void zz_01e497c_(int param_1,int param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = zz_01e488c_(*(undefined1 *)(param_1 + 0x96),param_2,param_3);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x8c) = param_1;
    *(undefined4 *)(iVar1 + 0xcc) = param_4;
  }
  return;
}



// ==== 801e49cc  FUN_801e49cc ====

void FUN_801e49cc(int param_1)

{
  (*(code *)(&PTR_FUN_80391f28)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801e4a08  FUN_801e4a08 ====

void FUN_801e4a08(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = *(char *)(param_1 + 0x13) * 0x24;
  if (uVar1 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_1 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    (*(code *)(&PTR_FUN_80391f38)[*(char *)(param_1 + 0x11)])(param_1);
    *(undefined1 *)(param_1 + 0x82) = 5;
  }
  return;
}



// ==== 801e4ac0  FUN_801e4ac0 ====

void FUN_801e4ac0(int param_1)

{
  (*(code *)(&PTR_zz_01e4cbc__80391f78)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e4b10  FUN_801e4b10 ====

void FUN_801e4b10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e4b58  FUN_801e4b58 ====

void FUN_801e4b58(int param_1)

{
  (*(code *)(&PTR_FUN_80391fb8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801e4b94  FUN_801e4b94 ====

void FUN_801e4b94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 extraout_r4;
  float *pfVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  undefined8 uVar9;
  
  fVar1 = FLOAT_8043c210;
  psVar7 = &DAT_80391ff8;
  iVar8 = 0;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(float *)(param_9 + 0x28) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x20) = fVar1;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(int)*psVar7;
    puVar3 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    if (iVar5 == 2) {
      pfVar4 = (float *)((int)pfVar4 + (int)*(char *)(param_9 + 0x1b));
    }
    *(short *)(puVar3 + 8) = psVar7[1];
    *(undefined2 *)((int)puVar3 + 0x22) = 0;
    uVar2 = *(undefined4 *)(psVar7 + 4);
    *puVar3 = *(undefined4 *)(psVar7 + 2);
    puVar3[1] = uVar2;
    puVar3[2] = *(undefined4 *)(psVar7 + 6);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar6 + 0xe0),(int)pfVar4,param_12,param_13,param_14
                          ,param_15,param_16);
    if (iVar5 < 2) {
      uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(char *)(param_9 + 0x1b) ^
                                                           0x80000000) - DOUBLE_8043c218),param_2,
                          param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                          *(int *)(iVar6 + 0xe0),pfVar4,param_12,param_13,param_14,param_15,param_16
                         );
      param_1 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar6 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14,
                            param_15,param_16);
    }
    iVar8 = iVar8 + 0x24;
    psVar7 = psVar7 + 8;
    iVar6 = iVar6 + 4;
  }
  zz_01e4cbc_(param_9);
  return;
}



// ==== 801e4cbc  zz_01e4cbc_ ====

void zz_01e4cbc_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    iVar3 = *(int *)(param_1 + 0x54) + iVar1;
    if (2 < iVar2) {
      *(short *)(iVar3 + 0x22) = *(short *)(iVar3 + 0x22) + -0x200;
    }
    iVar1 = iVar1 + 0x24;
  }
  if (PTR_DAT_80435a30[0x149] == *(char *)(param_1 + 0x1b)) {
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  return;
}



// ==== 801e4d24  FUN_801e4d24 ====

void FUN_801e4d24(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar3;
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
  float afStack_48 [13];
  
  dVar8 = (double)*(float *)(param_1 + 0x24);
  dVar9 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
  iVar6 = 0;
  iVar5 = param_1;
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar3);
    pfVar1 = afStack_48;
    iVar2 = (int)*(short *)((int)pfVar3 + 0x22);
    uVar7 = zz_00457d4_('z',pfVar1,pfVar1,*(short *)((int)pfVar3 + 0x22));
    zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_48,
                (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)(pfVar3 + 8));
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 801e4dd0  FUN_801e4dd0 ====

void FUN_801e4dd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 *puVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  undefined8 uVar10;
  
  fVar2 = FLOAT_8043c210;
  psVar8 = &DAT_80392048;
  iVar9 = 0;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(float *)(param_9 + 0x28) = fVar2;
  *(float *)(param_9 + 0x24) = fVar2;
  *(float *)(param_9 + 0x20) = fVar2;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar9);
    *(short *)(puVar4 + 8) = psVar8[1];
    uVar3 = *(undefined4 *)(psVar8 + 4);
    *puVar4 = *(undefined4 *)(psVar8 + 2);
    puVar4[1] = uVar3;
    puVar4[2] = *(undefined4 *)(psVar8 + 6);
    sVar1 = *psVar8;
    *(short *)((int)puVar4 + 0x22) = sVar1;
    if (-1 < sVar1) {
      if ((*(char *)(param_9 + 0x1b) == '\x02') && (iVar6 == 2)) {
        *(short *)((int)puVar4 + 0x22) = *(short *)((int)puVar4 + 0x22) + 1;
      }
      pfVar5 = (float *)(int)*(short *)((int)puVar4 + 0x22);
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                  *(int *)(iVar7 + 0xe0),(int)pfVar5,param_12,param_13,param_14,param_15,param_16);
      uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                            (int)*(char *)(param_9 + 0x1b) ^
                                                            0x80000000) - DOUBLE_8043c218),param_2,
                           param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                           *(int *)(iVar7 + 0xe0),pfVar5,param_12,param_13,param_14,param_15,
                           param_16);
      param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar7 + 0xe0),extraout_r4,pfVar5,param_12,param_13,param_14,
                            param_15,param_16);
    }
    iVar9 = iVar9 + 0x24;
    psVar8 = psVar8 + 8;
    iVar7 = iVar7 + 4;
  }
  zz_01e4f04_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e4f04  zz_01e4f04_ ====

void zz_01e4f04_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  float *pfVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  
  iVar9 = 0;
  sVar1 = *(short *)(&DAT_80435b60 + (char)PTR_DAT_80435a30[0x14a] * 2);
  pfVar6 = (float *)(int)sVar1;
  iVar8 = param_9;
  for (iVar7 = 0; iVar2 = DAT_803bb32c, iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    if ((iVar7 == 3) &&
       (iVar5 = *(int *)(param_9 + 0x54) + iVar9, pfVar6 != (float *)(int)*(short *)(iVar5 + 0x22)))
    {
      iVar3 = *(int *)(iVar8 + 0xe0);
      *(short *)(iVar5 + 0x22) = sVar1;
      pfVar4 = pfVar6;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,iVar3,
                  (int)pfVar6,iVar5,in_r7,in_r8,in_r9,in_r10);
      uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                            (int)*(char *)(param_9 + 0x1b) ^
                                                            0x80000000) - DOUBLE_8043c218),param_2,
                           param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                           *(int *)(iVar8 + 0xe0),pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
      param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar8 + 0xe0),extraout_r4,pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10
                           );
    }
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 4;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e500c  FUN_801e500c ====

void FUN_801e500c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
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
  
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar5 = 0;
  iVar4 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
    pfVar1 = pfVar2;
    uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar2);
    zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar4 + 0xe0),(int)*(short *)(pfVar2 + 8));
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 801e50a4  FUN_801e50a4 ====

/* WARNING: Removing unreachable block (ram,0x801e5228) */
/* WARNING: Removing unreachable block (ram,0x801e50b4) */

void FUN_801e50a4(int param_1)

{
  float fVar1;
  float fVar2;
  float *extraout_r4;
  float *extraout_r4_00;
  float *pfVar3;
  float *extraout_r4_01;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  undefined8 uVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar14;
  
  fVar1 = FLOAT_8043c220;
  iVar5 = param_1 + 0x38;
  *(undefined *)(param_1 + 0x1b) = PTR_DAT_80435a30[0x149];
  fVar2 = FLOAT_8043c210;
  iVar4 = 0;
  dVar13 = (double)FLOAT_8043c210;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  dVar14 = DOUBLE_8043c218;
  *(float *)(param_1 + 0xd4) = fVar1;
  dVar12 = (double)FLOAT_8043c224;
  *(float *)(param_1 + 0x20) = fVar2;
  uVar6 = (uint)*(byte *)(param_1 + 0x12);
  *(float *)(param_1 + 0x24) =
       (float)(dVar12 * (double)(float)((double)CONCAT44(0x43300000,
                                                         (int)(char)*(byte *)(param_1 + 0x12) ^
                                                         0x80000000) - dVar14));
  *(float *)(param_1 + 0x28) = fVar2;
  uVar11 = zz_01e497c_(param_1,3,0,iVar5);
  pfVar3 = extraout_r4;
  if (*(char *)(param_1 + 0x1b) < '\x02') {
    zz_01e497c_(param_1,3,1,param_1 + 0x3c);
    iVar5 = param_1 + 0x40;
    iVar4 = 2;
    uVar11 = zz_01e497c_(param_1,3,2,iVar5);
    pfVar3 = extraout_r4_00;
  }
  dVar14 = (double)FLOAT_8043c220;
  puVar9 = &DAT_80392088;
  iVar10 = 0;
  iVar8 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar10);
    pfVar3[6] = (float)dVar14;
    *(undefined2 *)(pfVar3 + 8) = puVar9[1];
    *(undefined2 *)((int)pfVar3 + 0x22) = *puVar9;
    fVar2 = *(float *)(puVar9 + 4);
    *pfVar3 = *(float *)(puVar9 + 2);
    pfVar3[1] = fVar2;
    pfVar3[2] = *(float *)(puVar9 + 6);
    if (*(char *)(param_1 + 0x1b) == '\x02') {
      if (iVar7 == 3) {
        *pfVar3 = FLOAT_8043c228;
      }
      else if (iVar7 == 4) {
        *pfVar3 = FLOAT_8043c22c;
      }
    }
    iVar4 = (int)*(short *)((int)pfVar3 + 0x22);
    if (-1 < *(short *)((int)pfVar3 + 0x22)) {
      uVar11 = zz_0006fb4_(uVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb32c,
                           *(int *)(iVar8 + 0xe0),iVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
      pfVar3 = extraout_r4_01;
    }
    iVar10 = iVar10 + 0x24;
    puVar9 = puVar9 + 8;
    iVar8 = iVar8 + 4;
  }
  zz_01e5244_(uVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,pfVar3,iVar4,iVar5,uVar6,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 801e5244  zz_01e5244_ ====

void zz_01e5244_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  byte bVar2;
  undefined4 uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar9;
  undefined4 extraout_r4_01;
  float *pfVar10;
  int iVar11;
  int unaff_r24;
  int unaff_r25;
  int iVar12;
  int unaff_r27;
  int iVar13;
  int iVar14;
  double dVar15;
  undefined8 uVar16;
  double dVar17;
  undefined2 local_48 [2];
  undefined2 local_44 [2];
  undefined2 local_40 [2];
  undefined2 local_3c;
  undefined4 local_38;
  uint uStack_34;
  
  fVar1 = FLOAT_8043c234;
  dVar15 = DOUBLE_8043c218;
  bVar2 = *(byte *)(param_9 + 0x1b);
  pfVar10 = (float *)(uint)bVar2;
  iVar12 = (int)*(char *)(param_9 + 0x12) + (int)*(short *)(PTR_DAT_80435a30 + 0x15e);
  if (bVar2 == 0) {
    pfVar10 = *(float **)(PTR_DAT_80435a30 + 0x24);
    pfVar7 = pfVar10 + *(short *)(&DAT_803d4b60 + iVar12 * 2) * 8 + 0x21c;
    local_3c = *(undefined2 *)pfVar7;
    unaff_r25 = (int)*(char *)((int)pfVar7 + 2);
    unaff_r27 = (int)*(char *)((int)pfVar7 + 3);
    unaff_r24 = (int)*(char *)(pfVar7 + 3);
  }
  else if (bVar2 == 1) {
    pfVar10 = *(float **)(PTR_DAT_80435a30 + 0x28);
    pfVar7 = pfVar10 + *(short *)(&DAT_803d4b60 + iVar12 * 2) * 4;
    local_3c = *(undefined2 *)pfVar7;
    unaff_r25 = (int)*(char *)((int)pfVar7 + 2);
    unaff_r27 = (int)*(char *)((int)pfVar7 + 3);
    unaff_r24 = (int)*(char *)(pfVar7 + 3);
  }
  else if (bVar2 == 2) {
    pfVar10 = *(float **)(PTR_DAT_80435a30 + 0x28);
    unaff_r27 = 0;
    pfVar7 = pfVar10 + *(short *)(&DAT_803d4b60 + iVar12 * 2) * 3 + 8000;
    local_3c = *(undefined2 *)pfVar7;
    unaff_r25 = (int)*(char *)((int)pfVar7 + 3);
    unaff_r24 = (int)*(char *)(pfVar7 + 2);
  }
  if (iVar12 == *(short *)(PTR_DAT_80435a30 + 0x160)) {
    dVar15 = (double)FLOAT_8043c230;
    *(float *)(param_9 + 0xb4) = FLOAT_8043c230;
    *(float *)(param_9 + 0xd4) = fVar1;
  }
  else {
    local_38 = 0x43300000;
    *(float *)(param_9 + 0xb4) = FLOAT_8043c238;
    uStack_34 = (int)*(char *)(param_9 + 0x1b) ^ 0x80000000;
    *(float *)(param_9 + 0xd4) = (float)((double)CONCAT44(0x43300000,uStack_34) - dVar15);
  }
  uVar3 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = uVar3;
  *(undefined4 *)(param_9 + 0x5c) = uVar3;
  *(undefined4 *)(param_9 + 0x58) = uVar3;
  if (iVar12 < *(short *)(PTR_DAT_80435a30 + 0x162)) {
    *(int *)(param_9 + 0x38) = iVar12 + 1;
  }
  else {
    *(undefined4 *)(param_9 + 0x38) = 0xffffffff;
  }
  if ((iVar12 < *(short *)(PTR_DAT_80435a30 + 0x162)) && (PTR_DAT_80435a30[0x14a] == '\x01')) {
    local_40[0] = local_3c;
    iVar5 = zz_0066168_((char *)local_40,unaff_r25);
    *(int *)(param_9 + 0x3c) = iVar5;
    *(int *)(param_9 + 0x40) = unaff_r27 + 1;
  }
  else {
    *(undefined4 *)(param_9 + 0x40) = 0xffffffff;
    *(undefined4 *)(param_9 + 0x3c) = 0xffffffff;
  }
  iVar14 = 0;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  iVar5 = param_9;
  for (iVar13 = 0; dVar17 = DOUBLE_8043c218, iVar6 = DAT_803bb32c,
      iVar13 < *(char *)(param_9 + 0x13); iVar13 = iVar13 + 1) {
    iVar11 = *(int *)(param_9 + 0x54) + iVar14;
    if (iVar13 == 0) {
      local_38 = 0x43300000;
      uStack_34 = (int)*(char *)(param_9 + 0x1b) ^ 0x80000000;
      dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043c218);
      param_2 = DOUBLE_8043c218;
      if (dVar15 != (double)*(float *)(iVar11 + 0x18)) {
        iVar8 = *(int *)(iVar5 + 0xe0);
        local_38 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043c218);
        *(float *)(iVar11 + 0x18) = fVar1;
        uVar16 = zz_00086b8_((double)fVar1,dVar17,param_3,param_4,param_5,param_6,param_7,param_8,
                             iVar6,iVar8,pfVar10,param_12,param_13,param_14,param_15,param_16);
        dVar15 = (double)zz_0007c30_(uVar16,dVar17,param_3,param_4,param_5,param_6,param_7,param_8,
                                     *(int *)(iVar5 + 0xe0),extraout_r4,pfVar10,param_12,param_13,
                                     param_14,param_15,param_16);
        param_2 = dVar17;
      }
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 1;
    }
    else if (iVar12 < *(short *)(PTR_DAT_80435a30 + 0x162)) {
      if (iVar13 == 1) {
        dVar15 = (double)*(float *)(param_9 + 0xd4);
        if (dVar15 != (double)*(float *)(iVar11 + 0x18)) {
          iVar8 = *(int *)(iVar5 + 0xe0);
          *(float *)(iVar11 + 0x18) = *(float *)(param_9 + 0xd4);
          uVar16 = zz_00086b8_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                               iVar8,pfVar10,param_12,param_13,param_14,param_15,param_16);
          dVar15 = (double)zz_0007c30_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,*(int *)(iVar5 + 0xe0),extraout_r4_00,pfVar10,
                                       param_12,param_13,param_14,param_15,param_16);
        }
        *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 2;
      }
      else if (iVar13 == 2) {
        if (unaff_r24 != 0) {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 4;
        }
      }
      else if (iVar13 == 3) {
        sVar4 = *(short *)(&DAT_803920e8 + unaff_r25 * 2);
        if ((sVar4 != *(short *)(iVar11 + 0x22)) && (*(short *)(iVar11 + 0x22) = sVar4, -1 < sVar4))
        {
          pfVar10 = (float *)(int)*(short *)(iVar11 + 0x22);
          dVar15 = (double)zz_0006fb4_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,DAT_803bb32c,*(int *)(iVar5 + 0xe0),(int)pfVar10,
                                       param_12,param_13,param_14,param_15,param_16);
        }
        if (-1 < *(short *)(iVar11 + 0x22)) {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 8;
        }
      }
      else if (iVar13 == 4) {
        local_44[0] = local_3c;
        iVar8 = zz_00662c0_((char *)local_44,unaff_r25);
        iVar6 = DAT_803bb32c;
        pfVar10 = (float *)(int)*(short *)(&DAT_803920f4 + iVar8 * 2);
        if (pfVar10 != (float *)(int)*(short *)(iVar11 + 0x22)) {
          iVar9 = *(int *)(iVar5 + 0xe0);
          *(short *)(iVar11 + 0x22) = *(short *)(&DAT_803920f4 + iVar8 * 2);
          dVar15 = (double)zz_0006fb4_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,iVar6,iVar9,(int)pfVar10,param_12,param_13,param_14,
                                       param_15,param_16);
        }
        if (PTR_DAT_80435a30[0x14a] != '\0') {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 0x10;
        }
      }
      else if (iVar13 == 5) {
        local_48[0] = local_3c;
        iVar6 = zz_0066298_((char *)local_48);
        sVar4 = *(short *)(&DAT_80392100 + iVar6 * 2);
        pfVar10 = (float *)(int)sVar4;
        if (pfVar10 != (float *)(int)*(short *)(iVar11 + 0x22)) {
          *(float *)(iVar11 + 0x18) = FLOAT_8043c220;
          iVar6 = DAT_803bb32c;
          iVar8 = *(int *)(iVar5 + 0xe0);
          *(short *)(iVar11 + 0x22) = sVar4;
          zz_0006fb4_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,iVar8,
                      (int)pfVar10,param_12,param_13,param_14,param_15,param_16);
        }
        iVar6 = DAT_803bb32c;
        dVar15 = (double)*(float *)(param_9 + 0xd4);
        if (dVar15 != (double)*(float *)(iVar11 + 0x18)) {
          iVar8 = *(int *)(iVar5 + 0xe0);
          *(float *)(iVar11 + 0x18) = *(float *)(param_9 + 0xd4);
          uVar16 = zz_00086b8_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                               iVar8,pfVar10,param_12,param_13,param_14,param_15,param_16);
          dVar15 = (double)zz_0007c30_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,*(int *)(iVar5 + 0xe0),extraout_r4_01,pfVar10,
                                       param_12,param_13,param_14,param_15,param_16);
        }
        if (PTR_DAT_80435a30[0x14a] == '\0') {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 0x20;
        }
      }
    }
    iVar14 = iVar14 + 0x24;
    iVar5 = iVar5 + 4;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e5728  FUN_801e5728 ====

void FUN_801e5728(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  undefined2 *puVar10;
  int iVar11;
  int iVar12;
  undefined8 uVar13;
  double dVar14;
  double dVar15;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  undefined2 local_78 [2];
  undefined2 local_74;
  float local_70;
  float local_6c;
  float local_68;
  float afStack_64 [13];
  longlong local_30;
  
  dVar14 = (double)*(float *)(param_1 + 0x24);
  iVar12 = (int)*(char *)(param_1 + 0x12) + (int)*(short *)(PTR_DAT_80435a30 + 0x15e);
  dVar15 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar14,dVar15,(float *)(param_1 + 0x114));
  iVar7 = 0;
  iVar5 = 0;
  iVar11 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar7) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar7) != 0) {
      pfVar9 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      local_70 = *pfVar9;
      local_6c = pfVar9[1];
      local_68 = pfVar9[2];
      if ((iVar7 != 0) && (iVar12 == *(short *)(PTR_DAT_80435a30 + 0x160))) {
        local_68 = local_68 + FLOAT_8043c23c;
      }
      zz_00455fc_((float *)(param_1 + 0x114),afStack_64,&local_70);
      pfVar3 = (float *)(param_1 + 0x58);
      uVar13 = zz_00456a0_(afStack_64,afStack_64,pfVar3);
      zz_00076d0_(uVar13,dVar14,dVar15,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar11 + 0xe0),
                  afStack_64,(undefined *)pfVar3,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar11 + 0xe0),(int)*(short *)(pfVar9 + 8));
    }
    iVar5 = iVar5 + 0x24;
    iVar11 = iVar11 + 4;
    iVar7 = iVar7 + 1;
  }
  if (iVar12 < *(short *)(PTR_DAT_80435a30 + 0x162)) {
    cVar1 = *(char *)(param_1 + 0x1b);
    iVar11 = (int)*(float *)(param_1 + 0xd4);
    local_30 = (longlong)iVar11;
    if (cVar1 == '\0') {
      pcVar6 = (char *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                       *(short *)(&DAT_803d4b60 + iVar12 * 2) * 0x20 + 0x870);
      strcpy(&DAT_803d5eb8,*(char **)((&PTR_PTR_803510d8)[*pcVar6] + (uint)(byte)pcVar6[1] * 4));
      if ((*(uint *)(pcVar6 + 0x10) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) != 0) {
        iVar11 = 3;
      }
    }
    else if (cVar1 == '\x01') {
      pcVar6 = (char *)(*(int *)(PTR_DAT_80435a30 + 0x28) +
                       *(short *)(&DAT_803d4b60 + iVar12 * 2) * 0x10);
      strcpy(&DAT_803d5eb8,*(char **)((&PTR_PTR_803510d8)[*pcVar6] + (uint)(byte)pcVar6[1] * 4));
    }
    else if (cVar1 == '\x02') {
      puVar10 = (undefined2 *)
                (*(int *)(PTR_DAT_80435a30 + 0x28) +
                *(short *)(&DAT_803d4b60 + iVar12 * 2) * 0xc + 32000);
      strcpy(&DAT_803d5eb8,&DAT_802b3ba0);
      zz_0238c90_(-0x7fc2a148,(int)(&PTR_DAT_80390a28)[*(char *)((int)puVar10 + 3)]);
      local_78[0] = *puVar10;
      uVar8 = 100;
      local_74 = local_78[0];
      iVar5 = zz_00661d8_((char *)local_78);
      iVar7 = 0;
      do {
        iVar4 = (iVar5 + 1) / (int)uVar8;
        iVar2 = iVar4 / 10 + (iVar4 >> 0x1f);
        zz_0238c90_(-0x7fc2a148,(int)(&PTR_DAT_80390a40)[iVar4 + (iVar2 - (iVar2 >> 0x1f)) * -10]);
        iVar7 = iVar7 + 1;
        uVar8 = uVar8 / 10;
      } while (iVar7 < 3);
      zz_0238c90_(-0x7fc2a148,(int)(&PTR_DAT_80390a68)[*(char *)(puVar10 + 1)]);
    }
    local_70 = FLOAT_8043c240;
    local_6c = FLOAT_8043c244;
    local_68 = FLOAT_8043c248;
    if (iVar12 == *(short *)(PTR_DAT_80435a30 + 0x160)) {
      local_68 = FLOAT_8043c248 + FLOAT_8043c23c;
    }
    FUN_801c53dc((double)FLOAT_8043c238,(double)FLOAT_8043c24c,(double)FLOAT_8043c250,
                 (float *)(param_1 + 0x114),&local_70,(float *)(param_1 + 0x58),2,
                 (char)*(undefined2 *)(iVar11 * 2 + -0x7fc6ded8),(short *)&DAT_803d5eb8);
  }
  return;
}



// ==== 801e5aa8  FUN_801e5aa8 ====

/* WARNING: Removing unreachable block (ram,0x801e5be8) */
/* WARNING: Removing unreachable block (ram,0x801e5be0) */
/* WARNING: Removing unreachable block (ram,0x801e5bd8) */
/* WARNING: Removing unreachable block (ram,0x801e5ac8) */
/* WARNING: Removing unreachable block (ram,0x801e5ac0) */
/* WARNING: Removing unreachable block (ram,0x801e5ab8) */

void FUN_801e5aa8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float *pfVar2;
  int extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar6;
  short *psVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  iVar5 = *(int *)(param_9 + 0x8c);
  iVar4 = (int)*(char *)(param_9 + 0x12);
  *(float *)(param_9 + 0xd8) = FLOAT_8043c220;
  iVar9 = 0;
  iVar3 = iVar4 * 0x10;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  dVar12 = DOUBLE_8043c218;
  psVar7 = (short *)(&DAT_80392134 + iVar3);
  dVar11 = (double)FLOAT_8043c254;
  *(undefined *)(param_9 + 0x87) = (&DAT_80392137)[iVar3];
  dVar13 = (double)FLOAT_8043c258;
  dVar14 = (double)FLOAT_8043c210;
  *(undefined *)(param_9 + 0x13) = (&DAT_80392136)[iVar3];
  uVar1 = *(undefined4 *)(&DAT_8039213c + iVar3);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_80392138 + iVar3);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_80392140 + iVar3);
  dVar10 = (double)(float)((double)CONCAT44(0x43300000,(int)*(char *)(iVar5 + 0x12) ^ 0x80000000) -
                          dVar12);
  *(float *)(param_9 + 0x24) = -(float)(dVar11 * dVar10 - (double)*(float *)(param_9 + 0x24));
  iVar8 = param_9;
  for (uVar6 = 0; (int)uVar6 < (int)*(char *)(param_9 + 0x13); uVar6 = uVar6 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar9);
    *pfVar2 = (float)(dVar13 * (double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) -
                                              dVar12));
    pfVar2[2] = (float)dVar14;
    pfVar2[1] = (float)dVar14;
    iVar4 = (int)*psVar7;
    dVar10 = (double)zz_0006fb4_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb32c,*(int *)(iVar8 + 0xe0),iVar4,iVar5,in_r7,in_r8,in_r9,
                                 in_r10);
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 4;
    iVar3 = extraout_r4;
  }
  FUN_801e5c04(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar3,iVar4,
               iVar5,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 801e5c04  FUN_801e5c04 ====

void FUN_801e5c04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  double dVar2;
  size_t sVar3;
  undefined4 extraout_r4;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  undefined8 uVar12;
  char local_38 [8];
  char acStack_30 [8];
  undefined4 local_28;
  uint uStack_24;
  
  iVar6 = **(int **)(param_9 + 0xcc);
  iVar8 = *(int *)(param_9 + 0x8c);
  if (iVar6 != *(int *)(param_9 + 0xd8)) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(int *)(param_9 + 0xd8) = iVar6;
    if (-1 < iVar6) {
      if (((int)*(char *)(param_9 + 0x87) & 0xf0U) == 0) {
        if (((int)*(char *)(param_9 + 0x87) & 0xfU) == 0) {
          sprintf(acStack_30,&DAT_8043c268,(int)*(char *)(param_9 + 0x13));
        }
        else {
          sprintf(acStack_30,&DAT_8043c260,(int)*(char *)(param_9 + 0x13));
        }
      }
      else {
        sprintf(acStack_30,&DAT_8043c25c);
      }
      sprintf(local_38,acStack_30,iVar6);
      sVar3 = strlen(local_38);
      pcVar10 = local_38;
      iVar7 = 0;
      iVar11 = 0;
      iVar9 = 2;
      iVar6 = param_9;
      while( true ) {
        dVar2 = DOUBLE_8043c218;
        if (*(char *)(param_9 + 0x13) <= iVar7) break;
        iVar4 = (int)*pcVar10;
        if ((*(byte *)(param_9 + 0x87) & 0xf0) != 0) {
          uStack_24 = iVar9 - sVar3 ^ 0x80000000;
          local_28 = 0x43300000;
          param_3 = (double)FLOAT_8043c258;
          *(float *)(*(int *)(param_9 + 0x54) + iVar11) =
               (float)(param_3 *
                      (double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043c218)) *
               FLOAT_8043c270;
          param_2 = dVar2;
        }
        dVar2 = DOUBLE_8043c218;
        if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
          *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
          local_28 = 0x43300000;
          pfVar5 = (float *)(iVar4 + *(char *)(iVar8 + 0x1b) * 10);
          uStack_24 = (uint)(pfVar5 + -0xc) ^ 0x80000000;
          uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar2),
                               param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                               *(int *)(iVar6 + 0xe0),pfVar5,param_12,param_13,param_14,param_15,
                               param_16);
          zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0xe0),extraout_r4,pfVar5,param_12,param_13,param_14,param_15,
                      param_16);
        }
        iVar11 = iVar11 + 0x24;
        pcVar10 = pcVar10 + 1;
        iVar9 = iVar9 + 2;
        iVar6 = iVar6 + 4;
        iVar7 = iVar7 + 1;
      }
    }
  }
  uVar1 = *(undefined4 *)(iVar8 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  if ('\x01' < *(char *)(iVar8 + 0x18)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e5df8  FUN_801e5df8 ====

void FUN_801e5df8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [14];
  
  iVar3 = *(int *)(param_1 + 0x8c);
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar2 = *(char *)(param_1 + 0x13) + -1;
  iVar5 = iVar2 * 0x24;
  iVar4 = param_1 + iVar2 * 4;
  while( true ) {
    if (iVar2 < 0) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      local_58 = *pfVar1;
      local_54 = pfVar1[1];
      local_50 = pfVar1[2];
      if ((int)*(short *)(PTR_DAT_80435a30 + 0x160) ==
          (int)*(char *)(iVar3 + 0x12) + (int)*(short *)(PTR_DAT_80435a30 + 0x15e)) {
        local_50 = local_50 + FLOAT_8043c23c;
      }
      zz_00455fc_((float *)(param_1 + 0x114),afStack_4c,&local_58);
      pfVar1 = (float *)(param_1 + 0x58);
      uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar1);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    }
    iVar5 = iVar5 + -0x24;
    iVar4 = iVar4 + -4;
    iVar2 = iVar2 + -1;
  }
  return;
}



// ==== 801e5f04  FUN_801e5f04 ====

void FUN_801e5f04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  
  iVar6 = 0;
  psVar5 = &DAT_80392164;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    *(short *)(puVar2 + 8) = psVar5[1];
    uVar1 = *(undefined4 *)(psVar5 + 4);
    *puVar2 = *(undefined4 *)(psVar5 + 2);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(psVar5 + 6);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar4 + 0xe0),(int)*psVar5,param_12,param_13,
                          param_14,param_15,param_16);
    iVar6 = iVar6 + 0x24;
    psVar5 = psVar5 + 8;
    iVar4 = iVar4 + 4;
  }
  FUN_801e5fbc(param_9);
  return;
}



// ==== 801e5fbc  FUN_801e5fbc ====

void FUN_801e5fbc(int param_1)

{
  short sVar1;
  
  if ((*(short *)(PTR_DAT_80435a30 + 0x162) < 0xe) || (*(short *)(PTR_DAT_80435a30 + 0x158) != 0)) {
    *(undefined2 *)(param_1 + 0x1c) = 0x48;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x1c) + 1;
    *(short *)(param_1 + 0x1c) = sVar1;
    if (0x47 < sVar1) {
      *(undefined2 *)(param_1 + 0x1c) = 0;
    }
  }
  if (PTR_DAT_80435a30[0x149] == *(char *)(param_1 + 0x1b)) {
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  return;
}



// ==== 801e602c  FUN_801e602c ====

void FUN_801e602c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  float afStack_48 [13];
  
  if (*(short *)(param_9 + 0x1c) < 0x31) {
    gnt4_PSMTXIdentity_bl((float *)(param_9 + 0x114));
    iVar7 = 0;
    iVar6 = param_9;
    for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
      pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar4);
      pfVar2 = afStack_48;
      sVar1 = *(short *)(pfVar4 + 8);
      iVar3 = (int)sVar1;
      uVar8 = zz_00457d4_('z',pfVar2,pfVar2,sVar1);
      zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,
                  in_r10);
      zz_00097b4_(*(int *)(iVar6 + 0xe0),0x44);
      iVar7 = iVar7 + 0x24;
      iVar6 = iVar6 + 4;
    }
  }
  return;
}



// ==== 801e60d8  FUN_801e60d8 ====

void FUN_801e60d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined *puVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  puVar1 = PTR_DAT_80435a30;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
              *(int *)(param_9 + 0xe0),0x55,puVar1,in_r7,in_r8,in_r9,in_r10);
  FUN_801e612c(param_9);
  return;
}



// ==== 801e612c  FUN_801e612c ====

void FUN_801e612c(int param_1)

{
  short sVar1;
  short sVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  
  fVar4 = FLOAT_8043c274;
  dVar3 = DOUBLE_8043c218;
  sVar1 = *(short *)(PTR_DAT_80435a30 + 0x15e);
  sVar2 = *(short *)(PTR_DAT_80435a30 + 0x160);
  *(float *)(param_1 + 0x20) = FLOAT_8043c210;
  fVar5 = FLOAT_8043c278;
  *(float *)(param_1 + 0x24) =
       fVar4 - (float)((double)CONCAT44(0x43300000,((int)sVar2 - (int)sVar1) * 10 ^ 0x80000000) -
                      dVar3);
  *(float *)(param_1 + 0x28) = fVar5;
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_1 + 0x1b)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801e61a8  FUN_801e61a8 ====

void FUN_801e61a8(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  if (*(short *)(PTR_DAT_80435a30 + 0x162) != 0) {
    dVar2 = (double)*(float *)(param_1 + 0x24);
    dVar3 = (double)*(float *)(param_1 + 0x28);
    uVar1 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar2,dVar3,
                               (float *)(param_1 + 0x114));
    zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),1);
  }
  return;
}



// ==== 801e620c  FUN_801e620c ====

/* WARNING: Removing unreachable block (ram,0x801e631c) */
/* WARNING: Removing unreachable block (ram,0x801e621c) */

void FUN_801e620c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 *extraout_r4_01;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  
  puVar2 = (undefined4 *)PTR_DAT_80435a30;
  iVar6 = 0;
  puVar5 = &DAT_80392184;
  dVar8 = (double)FLOAT_8043c238;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    *(short *)(puVar2 + 8) = (short)*puVar5;
    uVar1 = puVar5[1];
    puVar2[4] = uVar1;
    puVar2[3] = uVar1;
    puVar2[5] = (float)dVar8;
    uVar1 = puVar5[3];
    *puVar2 = puVar5[2];
    puVar2[1] = uVar1;
    puVar2[2] = puVar5[4];
    param_11 = (float *)(int)*(short *)(puVar2 + 8);
    if ((-1 < *(short *)(puVar2 + 8)) &&
       (param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_803bb32c,*(int *)(iVar4 + 0xe0),(int)param_11,param_12,param_13,
                              param_14,param_15,param_16), puVar2 = extraout_r4, iVar3 < 2)) {
      uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(char *)(param_9 + 0x1b) ^
                                                           0x80000000) - DOUBLE_8043c218),param_2,
                          param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                          *(int *)(iVar4 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                          param_16);
      param_1 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(iVar4 + 0xe0),extraout_r4_00,param_11,param_12,param_13,
                            param_14,param_15,param_16);
      puVar2 = extraout_r4_01;
    }
    iVar6 = iVar6 + 0x24;
    puVar5 = puVar5 + 5;
    iVar4 = iVar4 + 4;
  }
  FUN_801e6338(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar2,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e6338  FUN_801e6338 ====

void FUN_801e6338(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  double dVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  char local_2a [10];
  undefined4 local_20;
  uint uStack_1c;
  
  if (*(int *)(PTR_DAT_80435a30 + 0x164) == -1) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    param_12 = 0;
    while( true ) {
      if (0x13 < param_12) break;
      if ((*(uint *)(PTR_DAT_80435a30 + 0x164) & 1 << param_12) != 0) {
        iVar5 = param_12 + 1;
        param_12 = 0x14;
      }
      param_12 = param_12 + 1;
    }
  }
  sVar1 = (&DAT_803921fc)[iVar5];
  iVar8 = 9999;
  if (*(short *)(PTR_DAT_80435a30 + 0x162) < 9999) {
    iVar8 = (int)*(short *)(PTR_DAT_80435a30 + 0x162);
  }
  sprintf(local_2a + 2,&DAT_8043c27c,iVar8);
  pcVar7 = local_2a + 2;
  iVar9 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar8 = param_9;
  for (iVar6 = 0; dVar2 = DOUBLE_8043c218, iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    iVar3 = *(int *)(param_9 + 0x54) + iVar9;
    if (iVar6 < 2) {
      if ((iVar6 == 0) && (sVar1 != *(short *)(iVar3 + 0x20))) {
        *(short *)(iVar3 + 0x20) = sVar1;
        pfVar4 = (float *)(int)*(short *)(iVar3 + 0x20);
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                    *(int *)(iVar8 + 0xe0),(int)pfVar4,param_12,iVar5,param_14,param_15,param_16);
        local_20 = 0x43300000;
        uStack_1c = (int)*(char *)(param_9 + 0x1b) ^ 0x80000000;
        uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_1c) -
                                            DOUBLE_8043c218),param_2,param_3,param_4,param_5,param_6
                             ,param_7,param_8,DAT_803bb32c,*(int *)(iVar8 + 0xe0),pfVar4,param_12,
                             iVar5,param_14,param_15,param_16);
        param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar8 + 0xe0),extraout_r4,pfVar4,param_12,iVar5,param_14,
                              param_15,param_16);
      }
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar6);
    }
    else {
      iVar3 = (int)pcVar7[-2];
      if ((0x2f < iVar3) && (iVar3 < 0x3a)) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar6);
        local_20 = 0x43300000;
        pfVar4 = (float *)(iVar3 + *(char *)(param_9 + 0x1b) * 10);
        uStack_1c = (uint)(pfVar4 + -0xc) ^ 0x80000000;
        uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_1c) - dVar2),param_2
                             ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                             *(int *)(iVar8 + 0xe0),pfVar4,param_12,iVar5,param_14,param_15,param_16
                            );
        param_1 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar8 + 0xe0),extraout_r4_00,pfVar4,param_12,iVar5,param_14,
                              param_15,param_16);
      }
    }
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 4;
    pcVar7 = pcVar7 + 1;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e6550  FUN_801e6550 ====

void FUN_801e6550(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  gnt4_PSMTXIdentity_bl((float *)(param_9 + 0x114));
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801e6600  FUN_801e6600 ====

void FUN_801e6600(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined *extraout_r4;
  int iVar6;
  undefined *extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined *extraout_r4_02;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  
  fVar3 = FLOAT_8043c284;
  fVar2 = FLOAT_8043c280;
  fVar1 = FLOAT_8043c210;
  dVar14 = (double)FLOAT_8043c210;
  dVar12 = (double)FLOAT_8043c280;
  iVar11 = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  puVar7 = PTR_DAT_80435a30;
  puVar10 = &DAT_80392228;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar3;
  iVar9 = param_9;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar11);
    *(undefined2 *)(puVar5 + 8) = 0;
    uVar4 = puVar10[2];
    *puVar5 = puVar10[1];
    puVar5[1] = uVar4;
    puVar5[2] = puVar10[3];
    puVar5[3] = *puVar5;
    puVar5[4] = puVar5[1];
    puVar5[5] = puVar5[2];
    param_11 = (float *)*puVar10;
    if (iVar8 == 3) {
      param_11 = (float *)((int)param_11 -
                          ((int)(2U - (int)*(char *)(param_9 + 0x1b) |
                                (int)*(char *)(param_9 + 0x1b) - 2U) >> 0x1f));
    }
    dVar12 = (double)zz_0006fb4_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb32c,*(int *)(iVar9 + 0xe0),(int)param_11,param_12,param_13
                                 ,param_14,param_15,param_16);
    if (iVar8 == 0) {
      iVar6 = *(int *)(iVar9 + 0xe0);
      dVar12 = (double)*(float *)(param_9 + 0xd4);
      zz_0008614_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar6,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      dVar12 = (double)zz_0007c30_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar9 + 0xe0),iVar6,param_11,param_12,param_13,param_14,
                                   param_15,param_16);
      puVar7 = extraout_r4_00;
    }
    else {
      puVar7 = extraout_r4;
      if (iVar8 == 1) {
        uVar13 = zz_00086b8_((double)FLOAT_8043c238,dVar14,param_3,param_4,param_5,param_6,param_7,
                             param_8,DAT_803bb32c,*(int *)(iVar9 + 0xe0),param_11,param_12,param_13,
                             param_14,param_15,param_16);
        dVar12 = (double)zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                                     *(int *)(iVar9 + 0xe0),extraout_r4_01,param_11,param_12,
                                     param_13,param_14,param_15,param_16);
        puVar7 = extraout_r4_02;
      }
    }
    iVar11 = iVar11 + 0x24;
    puVar10 = puVar10 + 4;
    iVar9 = iVar9 + 4;
  }
  FUN_801e6768(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar7,param_11
               ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e6768  FUN_801e6768 ====

void FUN_801e6768(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  
  fVar2 = FLOAT_8043c288;
  fVar1 = FLOAT_8043c210;
  pfVar4 = (float *)(uint)*(byte *)(param_9 + 0x19);
  if (*(byte *)(param_9 + 0x19) == 0) {
    if (((int)*(short *)(PTR_DAT_80435a30 + 0x158) & 1 << (int)*(char *)(param_9 + 0x12)) == 0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else {
      param_2 = (double)*(float *)(param_9 + 0xd8);
      if (((double)*(float *)(param_9 + 0xd4) < param_2) &&
         (fVar1 = (float)((double)*(float *)(param_9 + 0xd4) + (double)FLOAT_8043c238),
         *(float *)(param_9 + 0xd4) = fVar1, param_2 < (double)fVar1)) {
        *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(param_9 + 0xd8);
      }
    }
  }
  else {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar8 = (double)FLOAT_8043c238;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar8);
    if ((float)(param_2 - dVar8) <= fVar1) {
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    iVar3 = *(int *)(param_9 + 0x54) + iVar7;
    if (iVar5 == 0) {
      iVar3 = *(int *)(iVar6 + 0xe0);
      dVar8 = (double)*(float *)(param_9 + 0xd4);
      zz_0008614_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar3,
                  pfVar4,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),iVar3,pfVar4,param_12,param_13,param_14,param_15,param_16);
    }
    else if (iVar5 < 3) {
      if (iVar5 == 2) {
        *(short *)(iVar3 + 0x20) = *(short *)(iVar3 + 0x20) + -0x100;
      }
      param_2 = DOUBLE_8043c218;
      param_3 = (double)FLOAT_8043c254;
      *(float *)(iVar3 + 4) =
           -(float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,
                                                               (int)(char)PTR_DAT_80435a30[0x15b] ^
                                                               0x80000000) - DOUBLE_8043c218) -
                   (double)*(float *)(iVar3 + 0x10));
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e6918  FUN_801e6918 ====

void FUN_801e6918(int param_1)

{
  short sVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  dVar9 = (double)*(float *)(param_1 + 0x24);
  dVar10 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar9,dVar10,(float *)(param_1 + 0x114));
  iVar7 = 0;
  iVar6 = param_1;
  for (iVar5 = 0; iVar5 < *(char *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
    if ((iVar5 == 0) || (FLOAT_8043c288 < *(float *)(param_1 + 0xd4))) {
      pfVar4 = (float *)(*(int *)(param_1 + 0x54) + iVar7);
      zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar4);
      pfVar2 = afStack_48;
      sVar1 = *(short *)(pfVar4 + 8);
      iVar3 = (int)sVar1;
      uVar8 = zz_00457d4_('z',pfVar2,pfVar2,sVar1);
      zz_00076d0_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),afStack_48
                  ,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar6 + 0xe0),0x44);
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 801e69dc  FUN_801e69dc ====

void FUN_801e69dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 extraout_r4;
  int iVar5;
  undefined4 extraout_r4_00;
  undefined4 *puVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  
  fVar2 = FLOAT_8043c28c;
  fVar1 = FLOAT_8043c210;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  if (*(char *)(param_9 + 0x12) == '\x05') {
    *(float *)(param_9 + 0x28) = *(float *)(param_9 + 0x28) + FLOAT_8043c238;
  }
  fVar1 = FLOAT_8043c210;
  iVar7 = 0;
  dVar12 = (double)FLOAT_8043c210;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  fVar2 = FLOAT_8043c284;
  pfVar8 = (float *)0x0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar2;
  while( true ) {
    if ((char)PTR_DAT_80435a30[0x15d] <= iVar7) break;
    param_11 = pfVar8;
    dVar12 = (double)FUN_801e493c(param_9,9,(char)pfVar8);
    iVar7 = iVar7 + 8;
    pfVar8 = (float *)((int)pfVar8 + 1);
  }
  if ((int)(char)PTR_DAT_80435a30[0x15c] <= (int)(char)PTR_DAT_80435a30[0x15d]) {
    *(char *)(param_9 + 0x13) = *(char *)(param_9 + 0x13) + -2;
  }
  uVar3 = 0x80390000;
  iVar11 = 0;
  iVar10 = 0;
  iVar7 = param_9;
  for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar11);
    puVar6 = (undefined4 *)(&DAT_80392288 + iVar10 + *(char *)(param_9 + 0x12) * 0x50);
    if (iVar9 == 4) {
      *(undefined2 *)(puVar4 + 8) = 0x8000;
    }
    else {
      *(undefined2 *)(puVar4 + 8) = 0;
    }
    uVar3 = puVar6[2];
    *puVar4 = puVar6[1];
    puVar4[1] = uVar3;
    puVar4[2] = puVar6[3];
    puVar4[3] = *puVar4;
    puVar4[4] = puVar4[1];
    puVar4[5] = puVar4[2];
    param_11 = (float *)*puVar6;
    dVar12 = (double)zz_0006fb4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb32c,*(int *)(iVar7 + 0xe0),(int)param_11,param_12,param_13
                                 ,param_14,param_15,param_16);
    uVar3 = extraout_r4;
    if (iVar9 == 0) {
      iVar5 = *(int *)(iVar7 + 0xe0);
      dVar12 = (double)*(float *)(param_9 + 0xd4);
      zz_0008614_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar5,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      dVar12 = (double)zz_0007c30_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar7 + 0xe0),iVar5,param_11,param_12,param_13,param_14,
                                   param_15,param_16);
      uVar3 = extraout_r4_00;
    }
    iVar11 = iVar11 + 0x24;
    iVar10 = iVar10 + 0x10;
    iVar7 = iVar7 + 4;
  }
  FUN_801e6b9c(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,param_11
               ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e6b9c  FUN_801e6b9c ====

void FUN_801e6b9c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  
  fVar2 = FLOAT_8043c288;
  fVar1 = FLOAT_8043c210;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (((int)*(short *)(PTR_DAT_80435a30 + 0x158) & 1 << (int)*(char *)(param_9 + 0x12)) == 0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else {
      param_2 = (double)*(float *)(param_9 + 0xd8);
      if (((double)*(float *)(param_9 + 0xd4) < param_2) &&
         (fVar1 = (float)((double)*(float *)(param_9 + 0xd4) + (double)FLOAT_8043c238),
         *(float *)(param_9 + 0xd4) = fVar1, param_2 < (double)fVar1)) {
        *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(param_9 + 0xd8);
      }
    }
  }
  else {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar9 = (double)FLOAT_8043c238;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar9);
    if ((float)(param_2 - dVar9) <= fVar1) {
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (0x47 < sVar3) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  iVar8 = 0;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    pfVar5 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
    if (iVar6 == 0) {
      iVar4 = *(int *)(iVar7 + 0xe0);
      dVar9 = (double)*(float *)(param_9 + 0xd4);
      zz_0008614_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar4,
                  pfVar5,param_12,param_13,param_14,param_15,param_16);
      zz_0007c30_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar7 + 0xe0),iVar4,pfVar5,param_12,param_13,param_14,param_15,param_16);
    }
    else if (iVar6 < 3) {
      if (iVar6 == 2) {
        *(short *)(pfVar5 + 8) = *(short *)(pfVar5 + 8) + -0x100;
      }
      param_2 = DOUBLE_8043c218;
      param_3 = (double)FLOAT_8043c254;
      pfVar5[1] = -(float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,
                                                                      (int)(char)PTR_DAT_80435a30
                                                                                 [0x15b] -
                                                                      (int)(char)PTR_DAT_80435a30
                                                                                 [0x15a] ^
                                                                      0x80000000) - DOUBLE_8043c218)
                          - (double)pfVar5[4]);
    }
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e6d78  FUN_801e6d78 ====

void FUN_801e6d78(int param_1)

{
  short sVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  uint uVar5;
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
  float afStack_48 [12];
  
  uVar5 = 1;
  if ((FLOAT_8043c288 < *(float *)(param_1 + 0xd4)) &&
     (uVar5 = 7, *(short *)(param_1 + 0x1c) < 0x31)) {
    uVar5 = 0x1f;
  }
  dVar10 = (double)*(float *)(param_1 + 0x24);
  dVar11 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar10,dVar11,(float *)(param_1 + 0x114));
  iVar6 = 0;
  iVar8 = 0;
  iVar7 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar6) break;
    if ((uVar5 & 1 << iVar6) != 0) {
      pfVar4 = (float *)(*(int *)(param_1 + 0x54) + iVar8);
      zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar4);
      pfVar2 = afStack_48;
      sVar1 = *(short *)(pfVar4 + 8);
      iVar3 = (int)sVar1;
      uVar9 = zz_00457d4_('z',pfVar2,pfVar2,sVar1);
      zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0xe0),
                  afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar7 + 0xe0),0x44);
    }
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 801e6e5c  FUN_801e6e5c ====

void FUN_801e6e5c(int param_1)

{
  int iVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  float *pfVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar6 = (int)(char)PTR_DAT_80435a30[0x15d] + *(char *)(param_1 + 0x12) * -8;
  iVar4 = (int)*(char *)(*(int *)(param_1 + 0x8c) + 0x12);
  iVar1 = iVar4 * 0x10;
  if (*(char *)(param_1 + 0x13) < iVar6) {
    iVar6 = (int)*(char *)(param_1 + 0x13);
  }
  *(char *)(param_1 + 0x13) = (char)iVar6;
  fVar2 = FLOAT_8043c210;
  dVar9 = (double)FLOAT_8043c210;
  iVar6 = 0;
  pfVar7 = *(float **)(&DAT_803924b0 + iVar1);
  uVar5 = *(undefined4 *)(&DAT_803924b4 + iVar1);
  dVar8 = (double)FLOAT_8043c224;
  *(float **)(param_1 + 0x20) = pfVar7;
  dVar3 = DOUBLE_8043c218;
  *(undefined4 *)(param_1 + 0x24) = uVar5;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(&DAT_803924b8 + iVar1);
  *(undefined **)(param_1 + 0xcc) = (&PTR_DAT_803924bc)[iVar4 * 4];
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    pfVar7 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    iVar6 = iVar6 + 0x24;
    *(undefined2 *)(pfVar7 + 8) = 0xffff;
    *(short *)((int)pfVar7 + 0x22) = (short)iVar4 + *(char *)(param_1 + 0x12) * 8;
    *pfVar7 = fVar2;
    pfVar7[1] = (float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,
                                                                 (int)*(short *)((int)pfVar7 + 0x22)
                                                                 ^ 0x80000000) - dVar3));
    pfVar7[2] = fVar2;
  }
  FUN_801e6f6c(dVar3,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,0x43300000,pfVar7,iVar6,
               &DAT_803924b0 + iVar1,iVar4,in_r9,in_r10);
  return;
}



// ==== 801e6f6c  FUN_801e6f6c ====

void FUN_801e6f6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = 0;
  iVar6 = *(int *)(param_9 + 0x8c);
  iVar7 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_9 + 0x54) + iVar8;
    iVar3 = (int)(char)PTR_DAT_80435a30[0x15a] + (int)*(short *)(iVar4 + 0x22);
    if ((iVar3 < 0) || ((char)PTR_DAT_80435a30[0x15c] <= iVar3)) {
      *(undefined2 *)(iVar4 + 0x20) = 0xffff;
    }
    else {
      sVar1 = *(short *)(*(int *)(param_9 + 0xcc) + iVar3 * 2);
      if (*(short *)(iVar4 + 0x20) != sVar1) {
        *(short *)(iVar4 + 0x20) = sVar1;
        pfVar2 = (float *)(int)*(short *)(iVar4 + 0x20);
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                    *(int *)(iVar7 + 0xe0),(int)pfVar2,param_12,param_13,param_14,param_15,param_16)
        ;
        if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << iVar3) == 0) {
          *(float *)(iVar4 + 0x18) = FLOAT_8043c210;
        }
        else {
          *(float *)(iVar4 + 0x18) = FLOAT_8043c290;
        }
        uVar9 = zz_00086b8_((double)*(float *)(iVar4 + 0x18),param_2,param_3,param_4,param_5,param_6
                            ,param_7,param_8,DAT_803bb32c,*(int *)(iVar7 + 0xe0),pfVar2,param_12,
                            param_13,param_14,param_15,param_16);
        param_1 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar7 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,
                              param_15,param_16);
      }
    }
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  if ('\x01' < *(char *)(iVar6 + 0x18)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e7098  FUN_801e7098 ====

void FUN_801e7098(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [14];
  
  if (FLOAT_8043c288 < *(float *)(*(int *)(param_9 + 0x8c) + 0xd4)) {
    zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
                (float *)(param_9 + 0x20));
    iVar4 = 0;
    iVar3 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      if (-1 < *(short *)(pfVar1 + 8)) {
        uVar5 = zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
        zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14
                    ,param_15,param_16);
        zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      }
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 801e7160  FUN_801e7160 ====

void FUN_801e7160(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float *extraout_r4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  
  fVar3 = FLOAT_8043c294;
  fVar2 = FLOAT_8043c28c;
  fVar1 = FLOAT_8043c210;
  pfVar4 = (float *)PTR_DAT_80435a30;
  dVar9 = (double)FLOAT_8043c294;
  iVar7 = 0;
  dVar8 = (double)FLOAT_8043c28c;
  *(undefined *)(param_9 + 0x1b) = PTR_DAT_80435a30[0x149];
  *(float *)(param_9 + 0x20) = fVar1;
  fVar1 = FLOAT_8043c238;
  *(float *)(param_9 + 0x24) = fVar3;
  *(float *)(param_9 + 0x28) = fVar2;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = param_9;
  for (iVar5 = 0; fVar3 = FLOAT_8043c29c, fVar2 = FLOAT_8043c238, fVar1 = FLOAT_8043c210,
      iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    if (iVar5 == 0) {
      dVar8 = (double)FLOAT_8043c210;
      pfVar4[2] = FLOAT_8043c210;
      param_11 = 0xa3;
      pfVar4[1] = fVar1;
      *pfVar4 = fVar1;
      pfVar4[5] = fVar2;
      pfVar4[4] = fVar2;
      pfVar4[3] = fVar2;
      dVar8 = (double)zz_0006fb4_(dVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_803bb32c,*(int *)(iVar6 + 0xe0),0xa3,param_12,param_13,
                                  param_14,param_15,param_16);
      pfVar4 = extraout_r4;
    }
    else {
      *pfVar4 = FLOAT_8043c298;
      fVar1 = FLOAT_8043c2a0;
      pfVar4[1] = fVar3;
      fVar2 = FLOAT_8043c2a4;
      pfVar4[2] = fVar1;
      dVar8 = (double)*pfVar4;
      pfVar4[6] = *pfVar4;
      *(undefined2 *)(pfVar4 + 8) = 0x88;
      *(undefined2 *)((int)pfVar4 + 0x22) = 0;
      pfVar4[5] = fVar2;
      pfVar4[4] = fVar2;
      pfVar4[3] = fVar2;
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  FUN_801e7294(dVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,param_9,pfVar4,param_11,
               param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e7294  FUN_801e7294 ====

void FUN_801e7294(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  size_t sVar2;
  size_t sVar3;
  int *piVar4;
  int iVar5;
  
  *(undefined2 *)(param_9 + 0x1c) = 0;
  if ((-1 < *(short *)(PTR_DAT_80435a30 + 0x168)) &&
     (piVar4 = (int *)(*(int *)(PTR_DAT_80435a30 + 0x28) +
                      *(short *)(PTR_DAT_80435a30 + 0x168) * 0xc + 32000), -1 < *piVar4)) {
    iVar5 = *(int *)(param_9 + 0x54);
    cVar1 = (char)*piVar4;
    if (((int)*(short *)(iVar5 + 0x46) != (int)cVar1) &&
       (*(short *)(iVar5 + 0x46) = (short)cVar1, cVar1 != '\0')) {
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                  *(int *)(param_9 + 0xe4),
                  (int)*(short *)(iVar5 + 0x44) + (int)*(short *)(iVar5 + 0x46),param_12,param_13,
                  param_14,param_15,param_16);
    }
    sVar2 = strlen(*(char **)((&PTR_PTR_803510d8)[*(char *)piVar4] +
                             (uint)*(byte *)((int)piVar4 + 1) * 4));
    sVar3 = strlen(&DAT_802b3bbc);
    *(float *)(iVar5 + 0x24) =
         FLOAT_8043c2a8 *
         (float)((double)CONCAT44(0x43300000,(sVar2 >> 1) + (sVar3 >> 1) ^ 0x80000000) -
                DOUBLE_8043c218) * FLOAT_8043c270 + *(float *)(iVar5 + 0x3c);
    *(undefined2 *)(param_9 + 0x1c) = 1;
  }
  if (PTR_DAT_80435a30[0x149] != *(char *)(param_9 + 0x1b)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801e73e4  FUN_801e73e4 ====

void FUN_801e73e4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [14];
  
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar1 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if ((iVar3 == 0) || ((*(short *)(param_1 + 0x1c) != 0 && (*(short *)((int)pfVar2 + 0x22) != 0)))
       ) {
      zz_00455fc_((float *)(param_1 + 0x114),afStack_4c,pfVar2);
      pfVar2 = pfVar2 + 3;
      uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar1 + 0xe0),afStack_4c,
                  (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar1 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar1 = iVar1 + 4;
  }
  if (*(short *)(param_1 + 0x1c) != 0) {
    if (*(short *)(PTR_DAT_80435a30 + 0x160) < *(short *)(PTR_DAT_80435a30 + 0x162)) {
      psVar5 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x28) +
                        *(short *)(PTR_DAT_80435a30 + 0x168) * 0xc + 32000);
      iVar1 = zz_01cee00_((int)*psVar5);
      sprintf(&DAT_803d5eb8,&DAT_802b3bd0,(&PTR_DAT_80390a40)[iVar1]);
      local_58 = FLOAT_8043c298;
      local_54 = FLOAT_8043c258;
      local_50 = FLOAT_8043c2a0;
      FUN_801c53dc((double)FLOAT_8043c238,(double)FLOAT_8043c24c,(double)FLOAT_8043c2a8,
                   (float *)(param_1 + 0x114),&local_58,(float *)(param_1 + 0x58),3,0x2a,
                   (short *)&DAT_803d5eb8);
      if (*(char *)((int)psVar5 + 3) == '\0') {
        sprintf(&DAT_803d5eb8,&DAT_802b3c04,
                *(undefined4 *)((&PTR_PTR_803510d8)[*(char *)psVar5] + (uint)(byte)*psVar5 * 4));
      }
      else {
        sprintf(&DAT_803d5eb8,&DAT_802b3c1c,
                *(undefined4 *)((&PTR_PTR_803510d8)[*(char *)psVar5] + (uint)(byte)*psVar5 * 4));
      }
      local_58 = FLOAT_8043c298;
      local_54 = FLOAT_8043c29c;
      local_50 = FLOAT_8043c2a0;
      FUN_801c53dc((double)FLOAT_8043c238,(double)FLOAT_8043c24c,(double)FLOAT_8043c2a8,
                   (float *)(param_1 + 0x114),&local_58,(float *)(param_1 + 0x58),3,0x2a,
                   (short *)&DAT_803d5eb8);
    }
  }
  return;
}



// ==== 801e7620  FUN_801e7620 ====

void FUN_801e7620(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 extraout_r4;
  float *pfVar4;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  
  fVar3 = FLOAT_8043c28c;
  fVar2 = FLOAT_8043c284;
  fVar1 = FLOAT_8043c210;
  dVar7 = (double)FLOAT_8043c210;
  pfVar4 = (float *)0xc;
  dVar5 = (double)FLOAT_8043c28c;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar2;
  fVar2 = FLOAT_8043c238;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar3;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x60) = fVar2;
  uVar6 = zz_0006fb4_(dVar5,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                      *(int *)(param_9 + 0xe0),0xc,param_12,param_13,param_14,param_15,param_16);
  FUN_801e76a0(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
               pfVar4,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e76a0  FUN_801e76a0 ====

void FUN_801e76a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043c288;
  fVar1 = FLOAT_8043c210;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (PTR_DAT_80435a30[0x14b] == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else {
      param_2 = (double)*(float *)(param_9 + 0xd8);
      if (((double)*(float *)(param_9 + 0xd4) < param_2) &&
         (fVar1 = (float)((double)*(float *)(param_9 + 0xd4) + (double)FLOAT_8043c238),
         *(float *)(param_9 + 0xd4) = fVar1, param_2 < (double)fVar1)) {
        *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(param_9 + 0xd8);
      }
    }
  }
  else {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar4 = (double)FLOAT_8043c238;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar4);
    if ((float)(param_2 - dVar4) <= fVar1) {
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  iVar3 = *(int *)(param_9 + 0xe0);
  dVar4 = (double)*(float *)(param_9 + 0xd4);
  zz_0008614_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar3,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801e7774  FUN_801e7774 ====

void FUN_801e7774(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_18;
  float local_14;
  float local_10;
  
  dVar2 = (double)*(float *)(param_1 + 0x24);
  dVar3 = (double)*(float *)(param_1 + 0x28);
  uVar1 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar2,dVar3,
                             (float *)(param_1 + 0x114));
  zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  if (FLOAT_8043c288 < *(float *)(param_1 + 0xd4)) {
    sprintf(&DAT_803d5eb8,&DAT_802b3c38);
    local_18 = FLOAT_8043c2ac;
    local_14 = FLOAT_8043c2b0;
    local_10 = FLOAT_8043c2a0;
    FUN_801c53dc((double)FLOAT_8043c238,(double)FLOAT_8043c24c,(double)FLOAT_8043c2a8,
                 (float *)(param_1 + 0x114),&local_18,(float *)(param_1 + 0x58),3,0x27,
                 (short *)&DAT_803d5eb8);
    sprintf(&DAT_803d5eb8,&DAT_802b3c5c);
    local_18 = FLOAT_8043c2ac;
    local_14 = FLOAT_8043c2b4;
    local_10 = FLOAT_8043c2a0;
    FUN_801c53dc((double)FLOAT_8043c238,(double)FLOAT_8043c24c,(double)FLOAT_8043c2a8,
                 (float *)(param_1 + 0x114),&local_18,(float *)(param_1 + 0x58),3,0x27,
                 (short *)&DAT_803d5eb8);
  }
  return;
}



// ==== 801e79c4  FUN_801e79c4 ====

void FUN_801e79c4(int param_1)

{
  *(undefined1 *)(param_1 + 0x4a8) = 1;
  if (*(short *)(param_1 + 1000) == 0x505) {
    zz_00c74ec_(param_1,0x13);
  }
  else if (*(short *)(param_1 + 1000) == 0x511) {
    zz_00c74ec_(param_1,0x17);
  }
  return;
}



// ==== 801e7a10  FUN_801e7a10 ====

void FUN_801e7a10(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043c2c0;
  fVar1 = FLOAT_8043c2b8;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) -
                           DOUBLE_8043c2c0) * FLOAT_8043c2b8);
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) - dVar2
                           ) * fVar1);
  return;
}



// ==== 801e7ac0  FUN_801e7ac0 ====

void FUN_801e7ac0(int param_1)

{
  (*(code *)(&PTR_FUN_80392550)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801e7afc  FUN_801e7afc ====

void FUN_801e7afc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043c2c8;
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    *(float *)(param_1 + 0x558) = fVar1;
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      if (*(short *)(param_1 + 1000) == 0x505) {
        zz_00c3be0_(param_1,0x67);
        zz_00c3be0_(param_1,0x68);
      }
      else if (*(short *)(param_1 + 1000) == 0x511) {
        zz_00c3be0_(param_1,0x79);
        zz_00c3be0_(param_1,0x7a);
      }
    }
  }
  fVar2 = FLOAT_8043c2cc;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,0xc);
  }
  return;
}



// ==== 801e7be0  FUN_801e7be0 ====

void FUN_801e7be0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  fVar3 = FLOAT_8043c2cc;
  cVar1 = *(char *)(param_1 + 0x540);
  if (cVar1 == '\x02') {
    fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar2;
    if (fVar2 <= fVar3) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) + 0x2aa;
      fVar3 = FLOAT_8043c2d0;
      if (0x2000 < *(short *)(param_1 + 0x18e0)) {
        *(undefined2 *)(param_1 + 0x18e0) = 0x2000;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar3;
        *(undefined1 *)(param_1 + 0x6f7) = 2;
        iVar5 = zz_006dbe0_(param_1,2,1,1);
        if (iVar5 != 0) {
          if (*(short *)(param_1 + 1000) == 0x505) {
            zz_00e19a8_(param_1,0x10,param_1 + 0x6f7);
          }
          else if (*(short *)(param_1 + 1000) == 0x511) {
            zz_00e19a8_(param_1,0x13,param_1 + 0x6f7);
          }
        }
      }
    }
    else if (-1 < cVar1) {
      *(undefined1 *)(param_1 + 0x6f7) = 2;
      fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      *(float *)(param_1 + 0x558) = fVar2;
      fVar4 = FLOAT_8043c2d4;
      if (fVar2 <= fVar3) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar4;
        *(undefined1 *)(param_1 + 0x6f7) = 0;
      }
    }
  }
  else if ((cVar1 < '\x04') &&
          (*(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) + -0x199,
          *(short *)(param_1 + 0x18e0) < 0)) {
    *(undefined2 *)(param_1 + 0x18e0) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,0xc);
  }
  return;
}



// ==== 801e7e80  FUN_801e7e80 ====

void FUN_801e7e80(int param_1)

{
  if (*(char *)(param_1 + 0x48a) == '\x01') {
    FUN_801e87c4(param_1);
  }
  else {
    FUN_801eb384(param_1);
  }
  return;
}



// ==== 801e7eb8  FUN_801e7eb8 ====

void FUN_801e7eb8(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_80392978);
  return;
}



// ==== 801e7ef0  FUN_801e7ef0 ====

void FUN_801e7ef0(int param_1)

{
  (**(code **)(&DAT_80435b78 + *(char *)(param_1 + 0x580) * 4))();
  return;
}



// ==== 801e7f28  FUN_801e7f28 ====

void FUN_801e7f28(int param_1)

{
  (*(code *)(&PTR_LAB_803929a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801e7f74  FUN_801e7f74 ====

void FUN_801e7f74(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043c2d8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    FUN_801fad10(param_1,0);
    zz_00f036c_(param_1,0xeb);
  }
  return;
}



// ==== 801e801c  zz_01e801c_ ====

void zz_01e801c_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x1f,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x12;
    *(code **)(puVar1 + 0xc) = zz_01e8108_;
    *(code **)(puVar1 + 0x10c) = FUN_801e840c;
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
    zz_01e8108_((int)puVar1);
  }
  return;
}



// ==== 801e8108  zz_01e8108_ ====

void zz_01e8108_(int param_1)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar1 = zz_00660e8_(param_1,iVar3);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
    zz_008aff0_(param_1);
  }
  bVar2 = zz_008b480_();
  if ((bVar2 == 0) || ((bVar2 & *(byte *)(iVar3 + 0x3e5)) != 0)) {
    (*(code *)(&PTR_FUN_80392bf4)[*(char *)(param_1 + 0x18)])(param_1);
  }
  return;
}



// ==== 801e81ac  FUN_801e81ac ====

void FUN_801e81ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar4 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar4;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x57;
  *(char *)(param_9 + 0x89) = (char)DAT_80392bd2;
  uVar1 = DAT_80392bd8;
  *(undefined4 *)(param_9 + 100) = DAT_80392bd4;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = DAT_80392bdc;
  *(undefined4 *)(param_9 + 0x70) = DAT_80392be0;
  *(undefined2 *)(param_9 + 0x74) = DAT_80392be4;
  uVar1 = DAT_80392bec;
  *(undefined4 *)(param_9 + 0x58) = DAT_80392be8;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x60) = DAT_80392bf0;
  zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)(int)DAT_80392bd0,(int)*(char *)(param_9 + 0x88),
              iVar4,in_r8,in_r9,in_r10);
  fVar2 = FLOAT_8043c2e0;
  *(undefined4 *)(param_9 + 0x154) = 0;
  fVar3 = FLOAT_8043c2e4;
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(iVar5 + 0x7fc);
  *(float *)(param_9 + 0x14c) = *(float *)(param_9 + 0x150) / fVar2;
  *(float *)(param_9 + 0x144) = fVar3;
  zz_0007cac_((double)*(float *)(param_9 + 0x144),*(int *)(param_9 + 0xe0));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 801e82c4  FUN_801e82c4 ====

void FUN_801e82c4(int param_1)

{
  char cVar1;
  float fVar2;
  
  *(int *)(param_1 + 0x154) = *(int *)(param_1 + 0x154) + 1;
  fVar2 = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x14c);
  *(float *)(param_1 + 0x60) = fVar2;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  fVar2 = *(float *)(param_1 + 0x150);
  if (fVar2 < *(float *)(param_1 + 0x58)) {
    *(float *)(param_1 + 0x60) = fVar2;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x58) = fVar2;
  }
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(param_1 + 0x154) < 3) {
      return;
    }
    *(float *)(param_1 + 0x148) =
         FLOAT_8043c2e4 /
         (float)((double)CONCAT44(0x43300000,10U - *(int *)(param_1 + 0x154) ^ 0x80000000) -
                DOUBLE_8043c2f0);
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  fVar2 = FLOAT_8043c2e8;
  *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - *(float *)(param_1 + 0x148);
  if (*(float *)(param_1 + 0x144) < fVar2) {
    *(float *)(param_1 + 0x144) = fVar2;
  }
  zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe0));
  if (9 < *(int *)(param_1 + 0x154)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801e83d4  FUN_801e83d4 ====

void FUN_801e83d4(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801e83ec  FUN_801e83ec ====

void FUN_801e83ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e840c  FUN_801e840c ====

void FUN_801e840c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801e844c  zz_01e844c_ ====

void zz_01e844c_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xb01) &&
     (puVar1 = zz_0088aa0_(param_1,2,0x18,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x12;
    *(code **)(puVar1 + 0xc) = FUN_801e8540;
    *(code **)(puVar1 + 0x10c) = FUN_801e8784;
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



// ==== 801e8540  FUN_801e8540 ====

void FUN_801e8540(int param_1)

{
  int iVar1;
  
  iVar1 = zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  if ((iVar1 == 1) || (*(float *)(param_1 + 0x24) < FLOAT_8043c2f8)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80392c20)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801e85bc  FUN_801e85bc ====

void FUN_801e85bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  uint uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x14;
  *(float *)(param_9 + 0x58) = DAT_80392c14 * *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x5c) = DAT_80392c18 * *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x60) = DAT_80392c1c * *(float *)(param_9 + 0xb4);
  gnt4_PSMTXMultVec_bl((float *)(iVar5 + 0xa24),(float *)&DAT_80392c08,(float *)(param_9 + 0x20));
  zz_00055fc_();
  zz_00055fc_();
  uVar3 = zz_00055fc_();
  uVar4 = zz_00055fc_();
  fVar2 = FLOAT_8043c300;
  fVar1 = FLOAT_8043c2fc;
  dVar6 = (double)FLOAT_8043c2fc;
  *(short *)(param_9 + 0x72) = (short)(uVar3 << 8) + (short)uVar4;
  *(float *)(param_9 + 0x48) = fVar1;
  *(float *)(param_9 + 0x50) = fVar2;
  iVar5 = zz_0006f78_(param_9);
  zz_000726c_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
              *(int *)(param_9 + 0xe0),(float *)0xb,(int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9
              ,in_r10);
  *(undefined2 *)(param_9 + 0x1c) = 10;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 801e86dc  FUN_801e86dc ====

void FUN_801e86dc(int param_1)

{
  float fVar1;
  double dVar2;
  short sVar3;
  
  dVar2 = DOUBLE_8043c308;
  fVar1 = FLOAT_8043c300;
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (fVar1 <= (float)((double)CONCAT44(0x43300000,(int)sVar3 ^ 0x80000000) - dVar2)) {
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x50);
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801e8754  FUN_801e8754 ====

void FUN_801e8754(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  return;
}



// ==== 801e8764  FUN_801e8764 ====

void FUN_801e8764(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e8784  FUN_801e8784 ====

void FUN_801e8784(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801e87c4  FUN_801e87c4 ====

void FUN_801e87c4(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,6);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801e8900;
    *(code **)(puVar1 + 0x10c) = FUN_801e8f88;
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
    gnt4_memset(puVar1 + 0x144,0,0x18);
    iVar3 = 0;
    piVar4 = (int *)(puVar1 + 0x144);
    do {
      iVar2 = zz_0006d4c_();
      *piVar4 = iVar2;
      if (iVar2 == 0) {
        puVar1[0x18] = 2;
        return;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < 6);
  }
  return;
}



// ==== 801e8900  FUN_801e8900 ====

void FUN_801e8900(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80392c6c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801e8954  FUN_801e8954 ====

void FUN_801e8954(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar7 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043c310;
  dVar8 = (double)FLOAT_8043c310;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar2 = FLOAT_8043c314;
  uVar6 = 0;
  uVar5 = 0xa00;
  *(float *)(param_9 + 100) = fVar1;
  *(float *)(param_9 + 0x68) = fVar2;
  fVar2 = FLOAT_8043c318;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(undefined2 *)(param_9 + 0x15c) = 0;
  *(undefined2 *)(param_9 + 0x15e) = 0xa00;
  *(undefined2 *)(param_9 + 0x160) = 0;
  *(undefined2 *)(param_9 + 0x162) = 0;
  *(undefined2 *)(param_9 + 0x164) = 0x20;
  *(undefined2 *)(param_9 + 0x166) = 0x30;
  *(undefined2 *)(param_9 + 0x168) = 0;
  *(undefined2 *)(param_9 + 0x16a) = 0;
  *(undefined2 *)(param_9 + 0x16c) = 0x100;
  *(undefined2 *)(param_9 + 0x16e) = 0x100;
  *(float *)(param_9 + 0xb4) = fVar2;
  *(float *)(param_9 + 0xb8) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x60) = fVar2;
  *(undefined1 *)(param_9 + 0x89) = 1;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),0x56,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar4 = iVar7 + 0xc28;
  uVar3 = 0x56;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe4),0x56,iVar4,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar3,iVar4,uVar5,uVar6,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0xe4));
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe8),0x57,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar4 = iVar7 + 0xc28;
  uVar3 = 0x57;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xec),0x57,iVar4,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar3,iVar4,uVar5,uVar6,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0xec));
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xf0),0x58,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar4 = iVar7 + 0xc28;
  uVar3 = 0x58;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xf4),0x58,iVar4,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xf4)
              ,extraout_r4_01,uVar3,iVar4,uVar5,uVar6,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0xf4));
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x144),0x59,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar4 = iVar7 + 0xc28;
  uVar3 = 0x59;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x148),0x59,iVar4,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x148),extraout_r4_02,uVar3,iVar4,uVar5,uVar6,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0x148));
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x14c),0x5a,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar4 = iVar7 + 0xc28;
  uVar3 = 0x5a;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x150),0x5a,iVar4,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x150),extraout_r4_03,uVar3,iVar4,uVar5,uVar6,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0x150));
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x154),0x5b,iVar7 + 0xc28,uVar5,uVar6,in_r9,in_r10);
  iVar7 = iVar7 + 0xc28;
  uVar3 = 0x5b;
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x158),0x5b,iVar7,uVar5,uVar6,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x158),extraout_r4_04,uVar3,iVar7,uVar5,uVar6,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c31c,*(int *)(param_9 + 0x158));
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_01e8c10_(param_9);
  return;
}



// ==== 801e8c10  zz_01e8c10_ ====

void zz_01e8c10_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  undefined8 local_28;
  undefined8 local_18;
  
  fVar3 = FLOAT_8043c314;
  fVar2 = FLOAT_8043c310;
  iVar5 = *(int *)(param_1 + 0x90);
  *(float *)(param_1 + 100) = FLOAT_8043c310;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar2;
  if ((*(uint *)(iVar5 + 0x5e0) & 0x20000000) == 0) {
    if ((*(uint *)(iVar5 + 0x5e0) & 0x10) != 0) {
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15e)) ^ 0x80000000);
      *(short *)(param_1 + 0x15c) =
           (short)(int)((float)(local_28 - DOUBLE_8043c330) * *(float *)(iVar5 + 0x5f4) +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x15c) ^ 0x80000000) -
                              DOUBLE_8043c330));
      zz_00f0104_(iVar5,0x19,5);
      sVar1 = *(short *)(param_1 + 0x15e);
      if (sVar1 < 1) {
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15c)) ^ 0x80000000);
        if ((float)(local_18 - DOUBLE_8043c330) < FLOAT_8043c324) {
          *(short *)(param_1 + 0x15e) = -sVar1;
          *(undefined2 *)(param_1 + 0x15c) = 0xf556;
        }
      }
      else {
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15c)) ^ 0x80000000);
        if (FLOAT_8043c320 < (float)(local_18 - DOUBLE_8043c330)) {
          *(short *)(param_1 + 0x15e) = -sVar1;
          *(undefined2 *)(param_1 + 0x15c) = 0xaaa;
        }
      }
    }
    if ((*(uint *)(iVar5 + 0x5e0) & 0x40) != 0) {
      *(undefined2 *)(param_1 + 0x15c) = 0;
    }
    dVar4 = DOUBLE_8043c330;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x164)) ^ 0x80000000);
    *(short *)(param_1 + 0x160) =
         (short)(int)((float)(local_18 - DOUBLE_8043c330) * *(float *)(iVar5 + 0x5f4) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x160) ^ 0x80000000) -
                            DOUBLE_8043c330));
    sVar1 = *(short *)(param_1 + 0x164);
    if (sVar1 < 1) {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x160)) ^ 0x80000000);
      if ((float)(local_18 - dVar4) < FLOAT_8043c32c) {
        *(short *)(param_1 + 0x164) = -sVar1;
        *(undefined2 *)(param_1 + 0x160) = 0xfc72;
      }
    }
    else {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x160)) ^ 0x80000000);
      if (FLOAT_8043c328 < (float)(local_18 - dVar4)) {
        *(short *)(param_1 + 0x164) = -sVar1;
        *(undefined2 *)(param_1 + 0x160) = 0x38e;
      }
    }
    dVar4 = DOUBLE_8043c330;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x166)) ^ 0x80000000);
    *(short *)(param_1 + 0x162) =
         (short)(int)((float)(local_18 - DOUBLE_8043c330) * *(float *)(iVar5 + 0x5f4) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x162) ^ 0x80000000) -
                            DOUBLE_8043c330));
    sVar1 = *(short *)(param_1 + 0x166);
    if (sVar1 < 1) {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x162)) ^ 0x80000000);
      if ((float)(local_18 - dVar4) < FLOAT_8043c32c) {
        *(short *)(param_1 + 0x166) = -sVar1;
        *(undefined2 *)(param_1 + 0x162) = 0xfc72;
      }
    }
    else {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x162)) ^ 0x80000000);
      if (FLOAT_8043c328 < (float)(local_18 - dVar4)) {
        *(short *)(param_1 + 0x166) = -sVar1;
        *(undefined2 *)(param_1 + 0x162) = 0x38e;
      }
    }
    *(short *)(param_1 + 0x168) = -*(short *)(param_1 + 0x160);
    *(short *)(param_1 + 0x16a) = -*(short *)(param_1 + 0x162);
  }
  return;
}



// ==== 801e8f20  FUN_801e8f20 ====

void FUN_801e8f20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  } while (iVar1 < 6);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e8f88  FUN_801e8f88 ====

/* WARNING: Removing unreachable block (ram,0x801e91c0) */
/* WARNING: Removing unreachable block (ram,0x801e91a8) */
/* WARNING: Removing unreachable block (ram,0x801e9134) */
/* WARNING: Removing unreachable block (ram,0x801e911c) */
/* WARNING: Removing unreachable block (ram,0x801e907c) */
/* WARNING: Removing unreachable block (ram,0x801e8fcc) */

void FUN_801e8f88(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  double dVar7;
  float local_178;
  undefined4 local_174;
  undefined4 local_170;
  float afStack_16c [12];
  float afStack_13c [12];
  float afStack_10c [3];
  float local_100;
  undefined4 local_f0;
  undefined4 local_e0;
  float afStack_dc [3];
  float local_d0;
  undefined4 local_c0;
  undefined4 local_b0;
  float afStack_ac [3];
  float local_a0;
  undefined4 local_90;
  undefined4 local_80;
  float afStack_7c [3];
  float local_70;
  undefined4 local_60;
  undefined4 local_50;
  float afStack_4c [3];
  float local_40;
  undefined4 local_30;
  undefined4 local_20;
  
  bVar1 = *(char *)(*(int *)(param_9 + 0x90) + 0xae) != '\0';
  if (bVar1) {
    uVar5 = 0x44;
  }
  else {
    uVar5 = 1;
  }
  uVar4 = (uint)bVar1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x48b) == '\0') {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x15c) *
                                               0x3ff0000000000000)),afStack_13c,0x79);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_ac);
    gnt4_PSMTXMultVec_bl(afStack_ac,(float *)&DAT_80392c48,&local_178);
    local_a0 = local_178;
    local_90 = local_174;
    local_80 = local_170;
    gnt4_PSMTXConcat_bl(afStack_ac,afStack_13c,afStack_ac);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_10c);
    gnt4_PSMTXMultVec_bl(afStack_10c,(float *)&DAT_80392c60,&local_178);
    local_100 = local_178;
    local_f0 = local_174;
    local_e0 = local_170;
    gnt4_PSMTXConcat_bl(afStack_10c,afStack_13c,afStack_10c);
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       -(double)((longlong)(double)*(short *)(param_9 + 0x15c) *
                                                0x3ff0000000000000)),afStack_13c,0x79);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_dc);
    gnt4_PSMTXMultVec_bl(afStack_dc,(float *)&DAT_80392c54,&local_178);
    local_d0 = local_178;
    local_c0 = local_174;
    local_b0 = local_170;
    gnt4_PSMTXConcat_bl(afStack_dc,afStack_13c,afStack_dc);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_4c);
    gnt4_PSMTXMultVec_bl(afStack_4c,(float *)&DAT_80392c30,&local_178);
    local_40 = local_178;
    local_30 = local_174;
    local_20 = local_170;
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x160) *
                                               0x3ff0000000000000)),afStack_13c,0x78);
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x162) *
                                               0x3ff0000000000000)),afStack_16c,0x79);
    gnt4_PSMTXConcat_bl(afStack_4c,afStack_16c,afStack_4c);
    gnt4_PSMTXConcat_bl(afStack_4c,afStack_13c,afStack_4c);
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_7c);
    gnt4_PSMTXMultVec_bl(afStack_7c,(float *)&DAT_80392c3c,&local_178);
    dVar7 = (double)local_178;
    local_70 = local_178;
    local_60 = local_174;
    local_50 = local_170;
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x168) *
                                               0x3ff0000000000000)),afStack_13c,0x78);
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c338 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x16a) *
                                               0x3ff0000000000000)),afStack_16c,0x79);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_16c,afStack_7c);
    pfVar2 = afStack_7c;
    uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_13c,pfVar2);
    iVar3 = param_9 + uVar4 * 4;
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xe0),
                (float *)(param_9 + 0x114),(undefined *)pfVar2,param_12,param_13,param_14,param_15,
                param_16);
    uVar6 = zz_00097b4_(*(int *)(iVar3 + 0xe0),uVar5);
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xe8),
                afStack_4c,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_00097b4_(*(int *)(iVar3 + 0xe8),uVar5);
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xf0),
                afStack_7c,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_00097b4_(*(int *)(iVar3 + 0xf0),uVar5);
    iVar3 = param_9 + uVar4 * 4;
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x144),
                afStack_ac,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_00097b4_(*(int *)(iVar3 + 0x144),uVar5);
    iVar3 = param_9 + (uVar4 + 2) * 4;
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x144),
                afStack_dc,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_00097b4_(*(int *)(iVar3 + 0x144),uVar5);
    iVar3 = param_9 + (uVar4 + 4) * 4;
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x144),
                afStack_10c,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(iVar3 + 0x144),uVar5);
  }
  return;
}



// ==== 801e92c0  zz_01e92c0_ ====

void zz_01e92c0_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,8);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    piVar4 = (int *)(puVar1 + 0x144);
    *(code **)(puVar1 + 0xc) = FUN_801e9400;
    iVar3 = 0;
    *(code **)(puVar1 + 0x10c) = FUN_801e9c38;
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
    *(undefined4 *)(puVar1 + 0x148) = 0;
    *(undefined4 *)(puVar1 + 0x144) = 0;
    do {
      iVar2 = zz_0006d4c_();
      *piVar4 = iVar2;
      if (iVar2 == 0) {
        puVar1[0x18] = 2;
        return;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < 2);
  }
  return;
}



// ==== 801e9400  FUN_801e9400 ====

void FUN_801e9400(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80392cdc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801e9454  FUN_801e9454 ====

void FUN_801e9454(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 *puVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double local_28;
  double local_20;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(undefined1 *)(param_9 + 0x89) = 1;
  fVar1 = FLOAT_8043c340;
  uVar3 = DAT_80392cb4;
  *(undefined4 *)(param_9 + 100) = DAT_80392cb0;
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = DAT_80392cb8;
  *(undefined4 *)(param_9 + 0x70) = DAT_80392cd4;
  *(undefined2 *)(param_9 + 0x74) = DAT_80392cd8;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x144),0x99,iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  uVar3 = 0x99;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0x148),0x99,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x148),extraout_r4,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043c344,*(int *)(param_9 + 0x148));
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),0x9a,iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  uVar3 = 0x9a;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe4),0x9a,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4_00,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043c344,*(int *)(param_9 + 0xe4));
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe8),0x9a,iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  uVar3 = 0x9a;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xec),0x9a,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_01,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043c344,*(int *)(param_9 + 0xec));
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xf0),0x9a,iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  uVar3 = 0x9a;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xf4),0x9a,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xf4)
              ,extraout_r4_02,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043c344,*(int *)(param_9 + 0xf4));
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xf8),0x9a,iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar6 = iVar6 + 0xc28;
  uVar3 = 0x9a;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xfc),0x9a,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xfc)
              ,extraout_r4_03,uVar3,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c344,*(int *)(param_9 + 0xfc));
  iVar4 = param_9 + 0x144;
  iVar5 = 0;
  puVar2 = (undefined4 *)&DAT_80392cbc;
  iVar7 = 4;
  iVar6 = iVar4;
  do {
    *(undefined4 *)(iVar6 + 8) = *puVar2;
    *(undefined2 *)(iVar6 + 0xc) = *(undefined2 *)(puVar2 + 1);
    *(undefined2 *)(iVar4 + 0x20) = 0;
    *(undefined2 *)(iVar4 + 0x28) = 0xd00;
    *(undefined2 *)(iVar4 + 0x30) = *(undefined2 *)puVar2;
    if (iVar5 == 0) {
      *(undefined2 *)(iVar6 + 10) = 0x1000;
      *(undefined1 *)(param_9 + 0x17c) = 0;
    }
    else if (iVar5 == 1) {
      *(undefined2 *)(iVar6 + 10) = 0x9000;
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x28)) ^ 0x80000000);
      *(short *)(iVar4 + 0x20) =
           (short)(int)(FLOAT_8043c348 *
                       (FLOAT_8043c34c / (FLOAT_8043c350 / (float)(local_28 - DOUBLE_8043c358))));
      *(undefined2 *)(iVar4 + 0x30) = 0;
      *(undefined1 *)(param_9 + 0x17d) = 1;
    }
    else if (iVar5 == 2) {
      *(undefined2 *)(iVar6 + 10) = 0x7000;
      local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar4 + 0x28)) ^ 0x80000000);
      *(short *)(iVar4 + 0x20) =
           -(short)(int)(FLOAT_8043c348 *
                        (FLOAT_8043c34c / (FLOAT_8043c350 / (float)(local_20 - DOUBLE_8043c358))));
      *(undefined2 *)(iVar4 + 0x30) = 0;
      *(short *)(iVar4 + 0x28) = -*(short *)(iVar4 + 0x28);
      *(undefined1 *)(param_9 + 0x17e) = 1;
    }
    else if (iVar5 == 3) {
      *(undefined2 *)(iVar6 + 10) = 0xf000;
      *(short *)(iVar4 + 0x28) = -*(short *)(iVar4 + 0x28);
      *(undefined1 *)(param_9 + 0x17f) = 0;
    }
    puVar2 = (undefined4 *)((int)puVar2 + 6);
    iVar6 = iVar6 + 6;
    iVar4 = iVar4 + 2;
    iVar5 = iVar5 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_01e97ec_(param_9);
  return;
}



// ==== 801e97ec  zz_01e97ec_ ====

void zz_01e97ec_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double local_48;
  double local_38;
  undefined8 local_30;
  double local_28;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(uint *)(iVar2 + 0x5e0) & 0x50) != 0) {
    iVar3 = param_1 + 0x144;
    psVar4 = &DAT_80392cbc;
    iVar1 = 0;
    iVar5 = iVar3;
    do {
      dVar7 = DOUBLE_8043c358;
      if ((iVar1 == 0) || (iVar1 == 2)) {
        iVar6 = param_1 + iVar1;
        local_48 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x28)) ^ 0x80000000);
        *(short *)(iVar5 + 10) =
             (short)(int)((float)(local_48 - DOUBLE_8043c358) * *(float *)(iVar2 + 0x5f4) +
                         (float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(iVar5 + 10) ^ 0x80000000) -
                                DOUBLE_8043c358));
        if (*(char *)(iVar6 + 0x17c) == '\x01') {
          local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x20)) ^ 0x80000000);
          *(short *)(iVar3 + 0x30) =
               (short)(int)((float)(local_38 - dVar7) * *(float *)(iVar2 + 0x5f4) +
                           (float)((double)CONCAT44(0x43300000,
                                                    (int)*(short *)(iVar3 + 0x30) ^ 0x80000000) -
                                  dVar7));
          dVar7 = zz_0045204_(*(short *)(iVar3 + 0x30));
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar4) ^ 0x80000000);
          *(short *)(iVar5 + 8) =
               (short)(int)((double)FLOAT_8043c360 * dVar7 +
                           (double)(float)(local_30 - DOUBLE_8043c358));
          if (*psVar4 < *(short *)(iVar5 + 8)) {
            *(short *)(iVar5 + 8) = *psVar4;
          }
        }
        if (*(short *)(iVar5 + 10) < 0x7001) {
          if (*(short *)(iVar5 + 10) < 0x1000) {
            *(undefined2 *)(iVar5 + 10) = 0x1000;
            *(short *)(iVar3 + 0x28) = -*(short *)(iVar3 + 0x28);
            *(short *)(iVar5 + 8) = *psVar4;
            *(undefined1 *)(iVar6 + 0x17c) = 0;
          }
        }
        else {
          *(undefined2 *)(iVar5 + 10) = 0x7000;
          local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x28)) ^ 0x80000000);
          *(short *)(iVar3 + 0x20) =
               -(short)(int)(FLOAT_8043c348 *
                            (FLOAT_8043c34c / (FLOAT_8043c350 / (float)(local_28 - DOUBLE_8043c358))
                            ));
          *(undefined2 *)(iVar3 + 0x30) = 0;
          *(short *)(iVar3 + 0x28) = -*(short *)(iVar3 + 0x28);
          *(undefined1 *)(iVar6 + 0x17c) = 1;
        }
      }
      else if ((iVar1 == 1) || (iVar1 == 3)) {
        iVar6 = param_1 + iVar1;
        local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x28)) ^ 0x80000000);
        local_30 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar5 + 10) ^ 0x80000000);
        *(short *)(iVar5 + 10) =
             (short)(int)((float)(local_28 - DOUBLE_8043c358) * *(float *)(iVar2 + 0x5f4) +
                         (float)(local_30 - DOUBLE_8043c358));
        if (*(char *)(iVar6 + 0x17c) == '\x01') {
          local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x20)) ^ 0x80000000);
          local_30 = (double)CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x30) ^ 0x80000000);
          *(short *)(iVar3 + 0x30) =
               (short)(int)((float)(local_28 - dVar7) * *(float *)(iVar2 + 0x5f4) +
                           (float)(local_30 - dVar7));
          dVar7 = zz_0045204_(*(short *)(iVar3 + 0x30));
          *(short *)(iVar5 + 8) =
               (short)(int)((double)FLOAT_8043c360 * dVar7 +
                           (double)(float)((double)CONCAT44(0x43300000,(int)*psVar4 ^ 0x80000000) -
                                          DOUBLE_8043c358));
          if (*psVar4 < *(short *)(iVar5 + 8)) {
            *(short *)(iVar5 + 8) = *psVar4;
          }
        }
        if (*(short *)(iVar5 + 10) < -0x7000) {
          *(undefined2 *)(iVar5 + 10) = 0x9000;
          local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x28)) ^ 0x80000000);
          *(short *)(iVar3 + 0x20) =
               (short)(int)(FLOAT_8043c348 *
                           (FLOAT_8043c34c / (FLOAT_8043c350 / (float)(local_28 - DOUBLE_8043c358)))
                           );
          *(undefined2 *)(iVar3 + 0x30) = 0;
          *(short *)(iVar3 + 0x28) = -*(short *)(iVar3 + 0x28);
          *(undefined1 *)(iVar6 + 0x17c) = 1;
        }
        else if (-0x1000 < *(short *)(iVar5 + 10)) {
          *(undefined2 *)(iVar5 + 10) = 0xf000;
          *(short *)(iVar3 + 0x28) = -*(short *)(iVar3 + 0x28);
          *(short *)(iVar5 + 8) = *psVar4;
          *(undefined1 *)(iVar6 + 0x17c) = 0;
        }
      }
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + 6;
      psVar4 = psVar4 + 3;
      iVar3 = iVar3 + 2;
    } while (iVar1 < 4);
  }
  return;
}



// ==== 801e9bd0  FUN_801e9bd0 ====

void FUN_801e9bd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  } while (iVar1 < 2);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801e9c38  FUN_801e9c38 ====

/* WARNING: Removing unreachable block (ram,0x801e9d70) */
/* WARNING: Removing unreachable block (ram,0x801e9ce8) */
/* WARNING: Removing unreachable block (ram,0x801e9d0c) */
/* WARNING: Removing unreachable block (ram,0x801e9c48) */

void FUN_801e9c38(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  float *pfVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  float *pfVar10;
  undefined8 uVar11;
  double dVar12;
  float afStack_128 [12];
  float afStack_f8 [49];
  
  bVar1 = *(char *)(*(int *)(param_9 + 0x90) + 0xae) != '\0';
  if (bVar1) {
    uVar4 = 0x44;
  }
  else {
    uVar4 = 1;
  }
  uVar3 = (uint)bVar1;
  iVar6 = param_9 + uVar3 * 4;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(iVar6 + 0x144),(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14
              ,param_15,param_16);
  zz_00097b4_(*(int *)(iVar6 + 0x144),uVar4);
  dVar12 = (double)FLOAT_8043c364;
  pfVar9 = (float *)&DAT_80392c80;
  pfVar10 = afStack_f8;
  iVar8 = param_9 + 0x144;
  iVar6 = 0;
  iVar7 = 0;
  do {
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),pfVar10);
    gnt4_PSMTXMultVec_bl(pfVar10,pfVar9,(float *)(param_9 + 0x20));
    pfVar10[3] = *(float *)(param_9 + 0x20);
    pfVar10[7] = *(float *)(param_9 + 0x24);
    pfVar10[0xb] = *(float *)(param_9 + 0x28);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar12 * (double)((longlong)(double)*(short *)(iVar8 + 10) *
                                                         0x3ff0000000000000)),afStack_128,0x79);
    gnt4_PSMTXConcat_bl(pfVar10,afStack_128,pfVar10);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar12 * (double)((longlong)(double)*(short *)(iVar8 + 8) *
                                                         0x3ff0000000000000)),afStack_128,0x78);
    pfVar2 = pfVar10;
    uVar11 = gnt4_PSMTXConcat_bl(pfVar10,afStack_128,pfVar10);
    iVar5 = (uVar3 + iVar7) * 4 + 0xe0;
    zz_00076d0_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + iVar5),pfVar10,(undefined *)pfVar2,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + iVar5),uVar4);
    iVar6 = iVar6 + 1;
    pfVar9 = pfVar9 + 3;
    iVar8 = iVar8 + 6;
    iVar7 = iVar7 + 2;
    pfVar10 = pfVar10 + 0xc;
  } while (iVar6 < 4);
  return;
}



// ==== 801e9d8c  zz_01e9d8c_ ====

void zz_01e9d8c_(void)

{
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_80393380,(float *)&DAT_80393398,
                      (float *)&DAT_8039338c);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  PTR_DAT_80433930[0xc] = 0xff;
  return;
}



// ==== 801e9de8  zz_01e9de8_ ====

void zz_01e9de8_(int param_1)

{
  if (param_1 == 2) {
    FUN_801e9eec();
    zz_01e9e74_((int *)&DAT_803932b8);
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      zz_01e9d8c_();
      zz_01a7208_();
      zz_01e9e74_((int *)&DAT_80392cf0);
    }
    else if (-1 < param_1) {
      zz_01e9e74_((int *)&DAT_80392d40);
    }
  }
  else if (param_1 < 4) {
    zz_01e9e74_((int *)&DAT_80393330);
  }
  return;
}



// ==== 801e9e74  zz_01e9e74_ ====

void zz_01e9e74_(int *param_1)

{
  int iVar1;
  
  for (; -1 < *param_1; param_1 = param_1 + 5) {
    iVar1 = zz_01a7538_(7,param_1);
    if (iVar1 != 0) {
      *(code **)(iVar1 + 0xc) = FUN_801ea024;
      *(code **)(iVar1 + 0x10c) = FUN_801eb364;
    }
  }
  return;
}



// ==== 801e9eec  FUN_801e9eec ====

/* WARNING: Removing unreachable block (ram,0x801ea008) */
/* WARNING: Removing unreachable block (ram,0x801ea000) */
/* WARNING: Removing unreachable block (ram,0x801e9ff8) */
/* WARNING: Removing unreachable block (ram,0x801e9f0c) */
/* WARNING: Removing unreachable block (ram,0x801e9f04) */
/* WARNING: Removing unreachable block (ram,0x801e9efc) */

void FUN_801e9eec(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  dVar5 = (double)FLOAT_8043c368;
  uVar2 = 0;
  dVar6 = DOUBLE_8043c370;
  do {
    dVar4 = (double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000)
                                                   - dVar6));
    for (piVar3 = &DAT_80393150; -1 < *piVar3; piVar3 = piVar3 + 5) {
      iVar1 = zz_01a7538_(7,piVar3);
      if (iVar1 != 0) {
        *(code **)(iVar1 + 0xc) = FUN_801ea024;
        *(code **)(iVar1 + 0x10c) = FUN_801eb364;
        *(char *)(iVar1 + 0x12) = (char)uVar2;
        *(float *)(iVar1 + 0x68) = (float)((double)*(float *)(iVar1 + 0x68) + dVar4);
        *(undefined4 *)(iVar1 + 0x14c) = *(undefined4 *)(iVar1 + 0x68);
      }
    }
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < 6);
  for (piVar3 = &DAT_803932f4; -1 < *piVar3; piVar3 = piVar3 + 5) {
    iVar1 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup(7,piVar3,0x12);
    if (iVar1 != 0) {
      *(code **)(iVar1 + 0xc) = FUN_801ea024;
      *(code **)(iVar1 + 0x10c) = FUN_801eb364;
    }
  }
  return;
}



// ==== 801ea024  FUN_801ea024 ====

void FUN_801ea024(int param_1)

{
  (*(code *)(&PTR_FUN_803933a4)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ea060  FUN_801ea060 ====

void FUN_801ea060(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043c378;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
  zz_01ea0e0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ea0e0  zz_01ea0e0_ ====

void zz_01ea0e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = (int)*(char *)(param_9 + 0x11);
  if (iVar3 < 10) {
    (*(code *)(&PTR_FUN_803933b4)[iVar3])();
  }
  else if (iVar3 < 0x50) {
    iVar2 = iVar3 / 10 + (iVar3 >> 0x1f);
    iVar1 = -(iVar2 >> 0x1f);
    if (iVar3 == (iVar2 + iVar1) * 10) {
      zz_01ea9d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar1,
                  iVar3,param_12,param_13,param_14,param_15,param_16);
    }
    else {
      zz_01eac34_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  else if (iVar3 == 0x50) {
    zz_01eade4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                0x50,param_12,param_13,param_14,param_15,param_16);
  }
  else if (iVar3 == 0x51) {
    zz_01eafb8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                0x51,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    zz_01eb0b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 801ea184  FUN_801ea184 ====

void FUN_801ea184(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801ea1d4  FUN_801ea1d4 ====

int FUN_801ea1d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return param_9;
    }
    if (cVar1 < '\0') {
      return param_9;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(char *)(param_9 + 0x13) = (char)*(undefined4 *)(param_9 + 0x144);
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  uVar5 = zz_01a7668_(param_9,0x3c);
  uVar4 = *(uint *)(param_9 + 0x170);
  iVar2 = uVar4 - 0x1e;
  iVar3 = ((int)uVar4 >> 0x1f) + (uint)(0x1d < uVar4);
  if (*(int *)(param_9 + 0x180) != iVar3) {
    *(int *)(param_9 + 0x180) = iVar3;
    *(int *)(param_9 + 0x144) = *(char *)(param_9 + 0x13) + iVar3;
    iVar2 = zz_01a7688_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                        iVar3,uVar4,param_13,param_14,param_15,param_16);
  }
  return iVar2;
}



// ==== 801ea28c  FUN_801ea28c ====

void FUN_801ea28c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  
  if (*(char *)(DAT_80436354 + 1) == '\x04') {
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      *(char *)(param_9 + 0x19) = cVar1 + '\x01';
      fVar2 = FLOAT_8043c37c;
      if (*(char *)(param_9 + 0x11) == '\x02') {
        zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                    param_11,param_12,param_13,param_14,param_15,param_16);
      }
      else {
        *(undefined4 *)(param_9 + 0x174) = 1;
        *(float *)(param_9 + 0x178) = fVar2;
        zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,
                    param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    zz_01ea338_(param_9);
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ea338  zz_01ea338_ ====

void zz_01ea338_(int param_1)

{
  char cVar1;
  ushort uVar2;
  short sVar4;
  int iVar3;
  undefined2 uVar5;
  double dVar6;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x03') {
    *(undefined1 *)(param_1 + 0x82) = 1;
    uVar2 = *(ushort *)(DAT_80436354 + 0x24) & 0x7f;
    if (uVar2 == 2) {
      return;
    }
    if (uVar2 == 3) goto LAB_801ea4cc;
    uVar5 = 10;
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    if (*(char *)(param_1 + 0x11) < 'P') {
      uVar5 = 1;
    }
    *(undefined2 *)(param_1 + 0x1c) = uVar5;
LAB_801ea490:
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (0 < sVar4) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    zz_0181fbc_(param_1);
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 != '\x01') {
        if ('\0' < cVar1) goto LAB_801ea3d8;
        if (cVar1 < '\0') {
          return;
        }
        if (*(short *)(DAT_80436354 + 0x24) != 2) {
          return;
        }
        *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 1;
      }
      sVar4 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar4;
      if (0 < sVar4) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      zz_0181fbc_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 1;
LAB_801ea3d8:
      iVar3 = zz_0181fd0_(param_1,0x20);
      if (((iVar3 != 0) &&
          (*(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01',
          *(char *)(param_1 + 0x11) == 'Q')) && (*(char *)(param_1 + 0x12) == '\0')) {
        *(ushort *)(DAT_80436354 + 0x24) = *(ushort *)(DAT_80436354 + 0x24) | 0x80;
      }
      dVar6 = zz_01820b0_((double)FLOAT_8043c380,param_1);
      *(float *)(param_1 + 100) =
           (float)((double)(FLOAT_8043c380 + *(float *)(param_1 + 0x148)) - dVar6);
      return;
    }
    if (cVar1 != '\x05') {
      if ('\x04' < cVar1) {
        return;
      }
      goto LAB_801ea490;
    }
  }
  iVar3 = zz_0181fd0_(param_1,0x20);
  if (iVar3 == 0) {
    dVar6 = zz_01820b0_((double)FLOAT_8043c380,param_1);
    *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar6);
    return;
  }
LAB_801ea4cc:
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  if ((*(char *)(param_1 + 0x11) == 'Q') && (*(char *)(param_1 + 0x12) == '\0')) {
    *(ushort *)(DAT_80436354 + 0x24) = *(ushort *)(DAT_80436354 + 0x24) | 0x80;
  }
  return;
}



// ==== 801ea530  FUN_801ea530 ====

void FUN_801ea530(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  if (*(char *)(DAT_80436354 + 1) != '\x04') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801ea5e0;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    if (*(char *)(param_9 + 0x11) == '\x05') {
      *(undefined2 *)(param_9 + 0x74) = 0x8000;
    }
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  if (*(short *)(DAT_80436354 + 0x24) != 0x82) {
    return;
  }
  *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  *(undefined1 *)(param_9 + 0x82) = 1;
LAB_801ea5e0:
  if ((((*(char *)(param_9 + 0x11) == '\x04') && (*(short *)(DAT_80436354 + 0x26) != 0)) ||
      ((*(char *)(param_9 + 0x11) == '\x05' && (*(short *)(DAT_80436354 + 0x26) < 8)))) &&
     (*(int *)(DAT_80436354 + 0x10) < 0x32)) {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  if (*(short *)(DAT_80436354 + 0x24) != 0x82) {
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ea674  FUN_801ea674 ====

void FUN_801ea674(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  if (*(short *)(DAT_80436354 + 0x24) == 0) {
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ea6f8  FUN_801ea6f8 ====

void FUN_801ea6f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x03') {
    if (*(short *)(DAT_80436354 + 0x24) != 3) {
      return;
    }
    *(undefined1 *)(param_9 + 0x19) = 4;
LAB_801ea808:
    sVar2 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (0x22 < sVar2) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined2 *)(DAT_80436354 + 0x24) = 4;
    }
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                               DOUBLE_8043c370),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,param_11,param_12,param_13,param_14,param_15,param_16);
    return;
  }
  if ('\x02' < cVar1) {
    if (cVar1 == '\x05') {
      return;
    }
    if ('\x04' < cVar1) {
      return;
    }
    goto LAB_801ea808;
  }
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) goto LAB_801ea79c;
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  if (*(short *)(DAT_80436354 + 0x24) == 0) {
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    return;
  }
  if (*(short *)(DAT_80436354 + 0x24) != 2) {
    return;
  }
  *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 0x82) = 1;
LAB_801ea79c:
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x18 < sVar2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                             DOUBLE_8043c370),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ea878  FUN_801ea878 ====

void FUN_801ea878(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  short sVar3;
  
  bVar1 = *(byte *)(param_9 + 0x19);
  switch(bVar1) {
  case 0:
    break;
  case 1:
    goto switchD_801ea8b0_caseD_1;
  case 2:
    goto switchD_801ea8b0_caseD_2;
  case 3:
    goto switchD_801ea8b0_caseD_3;
  case 4:
    if (*(short *)(DAT_80436354 + 0x24) != 3) {
      return;
    }
    *(byte *)(param_9 + 0x19) = bVar1 + 1;
  case 5:
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    }
    goto LAB_801ea954;
  default:
    goto switchD_801ea8b0_caseD_6;
  }
  *(byte *)(param_9 + 0x19) = bVar1 + 1;
  zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,(uint)bVar1,
              param_12,param_13,param_14,param_15,param_16);
switchD_801ea8b0_caseD_1:
  if (*(short *)(DAT_80436354 + 0x24) == 0) {
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  }
  else if (*(short *)(DAT_80436354 + 0x24) == 2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0x3c;
switchD_801ea8b0_caseD_2:
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined2 *)(param_9 + 0x1c) = 0;
      *(undefined1 *)(param_9 + 0x82) = 1;
switchD_801ea8b0_caseD_3:
      sVar3 = *(short *)(param_9 + 0x1c) + 1;
      *(short *)(param_9 + 0x1c) = sVar3;
      if (7 < sVar3) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      }
LAB_801ea954:
      fVar2 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                     DOUBLE_8043c370) * FLOAT_8043c384;
      *(float *)(param_9 + 0x5c) = fVar2;
      *(float *)(param_9 + 0x58) = fVar2;
    }
  }
switchD_801ea8b0_caseD_6:
  return;
}



// ==== 801ea9d8  zz_01ea9d8_ ====

void zz_01ea9d8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  if (*(char *)(DAT_80436354 + 1) == '\x03') {
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      *(char *)(param_9 + 0x19) = cVar1 + '\x01';
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11
                  ,param_12,param_13,param_14,param_15,param_16);
    }
    zz_01eaa5c_(param_9);
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801eaa5c  zz_01eaa5c_ ====

void zz_01eaa5c_(int param_1)

{
  char cVar1;
  int iVar2;
  short sVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  iVar2 = (int)*(char *)(param_1 + 0x11) / 10 + ((int)*(char *)(param_1 + 0x11) >> 0x1f);
  sVar3 = (short)iVar2 - (short)(iVar2 >> 0x1f);
  if (cVar1 == '\x03') {
    if ((*(ushort *)(DAT_80436354 + 0x24) & 0x7f) == 1) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 4;
    *(short *)(param_1 + 0x1c) = sVar3 * 4;
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 != '\x01') {
        if ('\0' < cVar1) goto LAB_801eab1c;
        if (cVar1 < '\0') {
          return;
        }
        if (*(short *)(DAT_80436354 + 0x24) != 1) {
          return;
        }
        *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
        *(short *)(param_1 + 0x1c) = sVar3 * 4;
      }
      sVar3 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar3;
      if (0 < sVar3) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      zz_0181fbc_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 1;
LAB_801eab1c:
      iVar2 = zz_0181fd0_(param_1,0x20);
      if ((iVar2 != 0) &&
         (*(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01',
         *(char *)(param_1 + 0x11) == 'G')) {
        *(ushort *)(DAT_80436354 + 0x24) = *(ushort *)(DAT_80436354 + 0x24) | 0x80;
      }
      dVar4 = zz_01820b0_((double)FLOAT_8043c388,param_1);
      *(float *)(param_1 + 0x68) =
           (float)((double)(*(float *)(param_1 + 0x14c) - FLOAT_8043c388) + dVar4);
      return;
    }
    if (cVar1 == '\x05') goto LAB_801eabc8;
    if ('\x04' < cVar1) {
      return;
    }
  }
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (0 < sVar3) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  zz_0181fbc_(param_1);
LAB_801eabc8:
  iVar2 = zz_0181fd0_(param_1,0x20);
  if (iVar2 == 0) {
    dVar4 = zz_01820b0_((double)FLOAT_8043c388,param_1);
    *(float *)(param_1 + 0x68) = (float)((double)*(float *)(param_1 + 0x14c) + dVar4);
  }
  else {
    *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
    if (*(char *)(param_1 + 0x11) == 'G') {
      *(ushort *)(DAT_80436354 + 0x24) = *(ushort *)(DAT_80436354 + 0x24) | 0x80;
    }
  }
  return;
}



// ==== 801eac34  zz_01eac34_ ====

void zz_01eac34_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 in_r8;
  uint uVar8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  
  iVar6 = (int)*(char *)(param_9 + 0x11);
  iVar5 = iVar6 / 10 + (iVar6 >> 0x1f);
  iVar2 = -(iVar5 >> 0x1f);
  iVar3 = iVar6 + (iVar5 - (iVar5 >> 0x1f)) * -10;
  iVar9 = iVar3 + -1;
  if (*(char *)(DAT_80436354 + 1) != '\x03') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801eacf4;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar5,
                iVar2,iVar6,in_r8,in_r9,in_r10);
  }
  param_1 = zz_01eaa5c_(param_9);
LAB_801eacf4:
  if (*(char *)(param_9 + 0x82) != '\0') {
    uVar4 = 0;
    iVar6 = 4;
    uVar7 = *(uint *)(DAT_80436354 + 0x1434);
    uVar8 = *(uint *)(DAT_80436354 + 0x1438);
    switch(iVar5 + iVar2) {
    case 1:
      uVar4 = uVar7 + uVar8;
      break;
    case 2:
      uVar4 = uVar7;
      break;
    case 3:
      uVar4 = uVar8;
      break;
    case 4:
      if (uVar7 + uVar8 != 0) {
        uVar4 = (int)(uVar7 * 100) / (int)(uVar7 + uVar8);
      }
      iVar6 = 3;
      break;
    case 5:
      uVar4 = *(uint *)(DAT_80436354 + 0x1504);
      break;
    case 6:
      uVar4 = *(uint *)(DAT_80436354 + 0x1508);
      break;
    case 7:
      if (iVar9 < 3) {
        iVar6 = 3;
        uVar4 = *(uint *)(DAT_80436354 + 0x1440) / 0x3c;
      }
      else {
        iVar6 = 2;
        iVar9 = iVar3 + -4;
        uVar4 = *(uint *)(DAT_80436354 + 0x1440) % 0x3c;
      }
    }
    zz_01eb23c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar4,iVar9,
                iVar6,uVar7,uVar8,in_r9,in_r10);
  }
  return;
}



// ==== 801eade4  zz_01eade4_ ====

void zz_01eade4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  
  if (*(char *)(DAT_80436354 + 1) != '\x04') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        zz_01ea338_(param_9);
      }
      goto LAB_801eae88;
    }
    if (cVar1 < '\0') goto LAB_801eae88;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 10;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
LAB_801eae88:
  FUN_801eaea4(param_9);
  return;
}



// ==== 801eaea4  FUN_801eaea4 ====

/* WARNING: Removing unreachable block (ram,0x801eaf9c) */
/* WARNING: Removing unreachable block (ram,0x801eaeb4) */

void FUN_801eaea4(int param_1)

{
  char cVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_8043c38c;
  if (*(short *)(DAT_80436354 + 0xc) == 0) {
    cVar1 = *(char *)(param_1 + 0x12);
    if (cVar1 == '\x05') {
      dVar3 = zz_01820c4_((double)*(float *)(DAT_80436354 + 0x30),dVar3);
      *(float *)(param_1 + 0x68) =
           (float)((double)((*(float *)(param_1 + 0x14c) + FLOAT_8043c390) - FLOAT_8043c38c) + dVar3
                  );
    }
    else {
      if (('\x04' < cVar1) || (cVar1 != '\0')) {
        dVar3 = (double)FLOAT_8043c390;
      }
      dVar3 = zz_01820c4_((double)*(float *)(DAT_80436354 + 0x30),dVar3);
      *(float *)(param_1 + 0x68) = (float)((double)*(float *)(param_1 + 0x14c) + dVar3);
    }
  }
  else {
    cVar1 = *(char *)(param_1 + 0x12);
    if (cVar1 == '\x05') {
      dVar3 = zz_01820c4_((double)*(float *)(DAT_80436354 + 0x30),dVar3);
      *(float *)(param_1 + 0x68) =
           (float)((double)(*(float *)(param_1 + 0x14c) + FLOAT_8043c390) - dVar3);
    }
    else {
      if (('\x04' < cVar1) || (cVar1 != '\0')) {
        dVar3 = (double)FLOAT_8043c390;
      }
      dVar2 = zz_01820c4_((double)*(float *)(DAT_80436354 + 0x30),dVar3);
      *(float *)(param_1 + 0x68) =
           (float)((double)(float)((double)*(float *)(param_1 + 0x14c) + dVar3) - dVar2);
    }
  }
  return;
}



// ==== 801eafb8  zz_01eafb8_ ====

void zz_01eafb8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  if (*(char *)(DAT_80436354 + 1) != '\x04') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        param_1 = zz_01ea338_(param_9);
      }
      goto LAB_801eb05c;
    }
    if (cVar1 < '\0') goto LAB_801eb05c;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 10;
    *(char *)(param_9 + 0x13) = (char)*(undefined4 *)(param_9 + 0x144);
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
LAB_801eb05c:
  iVar3 = (int)*(short *)(DAT_80436354 + 0x26) + (int)*(char *)(param_9 + 0x12);
  if (*(int *)(param_9 + 0x180) != iVar3) {
    *(int *)(param_9 + 0x180) = iVar3;
    *(int *)(param_9 + 0x144) = *(char *)(param_9 + 0x13) + iVar3;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar3,
                param_12,param_13,param_14,param_15,param_16);
  }
  FUN_801eaea4(param_9);
  return;
}



// ==== 801eb0b8  zz_01eb0b8_ ====

void zz_01eb0b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  fVar2 = FLOAT_8043c394;
  iVar6 = *(char *)(param_9 + 0x11) + -0x52;
  iVar5 = iVar6 / 3;
  if (*(char *)(DAT_80436354 + 1) != '\x04') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    return;
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        param_1 = zz_01ea338_(param_9);
      }
      goto LAB_801eb19c;
    }
    if (cVar1 < '\0') goto LAB_801eb19c;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(float *)(param_9 + 0x5c) = fVar2;
    *(float *)(param_9 + 0x58) = fVar2;
    *(undefined2 *)(param_9 + 0x1c) = 10;
    param_1 = zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                          iVar6,0x55555556,in_r7,in_r8,in_r9,in_r10);
  }
  sVar4 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar4;
  if (sVar4 < 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
LAB_801eb19c:
  if (*(char *)(param_9 + 0x82) != '\0') {
    iVar3 = (int)*(short *)(DAT_80436354 + 0x26) + *(char *)(param_9 + 0x12) + 1;
    if (iVar5 == 1) {
      iVar5 = *(int *)(DAT_80436354 + iVar3 * 4 + 0x1484);
    }
    else if ((iVar5 < 1) || (2 < iVar5)) {
      iVar5 = *(int *)(DAT_80436354 + iVar3 * 4 + 0x1444);
    }
    else {
      iVar5 = *(int *)(DAT_80436354 + iVar3 * 4 + 0x14c4);
    }
    zz_01eb23c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar5,
                iVar6 % 3,3,in_r7,in_r8,in_r9,in_r10);
    FUN_801eaea4(param_9);
  }
  return;
}



// ==== 801eb23c  zz_01eb23c_ ====

void zz_01eb23c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                int param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  float *pfVar1;
  double dVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  uint uVar6;
  
  dVar2 = DOUBLE_8043c370;
  if (*(short *)(&DAT_80393410 + param_12 * 2) + -1 < param_10) {
    param_10 = *(short *)(&DAT_80393410 + param_12 * 2) + -1;
  }
  iVar3 = param_12 + -1;
  iVar5 = 1;
  psVar4 = &DAT_80393412;
  if (1 < param_12) {
    do {
      if (param_10 < *psVar4) break;
      psVar4 = psVar4 + 1;
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  if (param_11 < iVar5) {
    iVar5 = param_10 / (int)*(short *)(&DAT_80393410 + param_11 * 2);
    iVar3 = iVar5 / 10 + (iVar5 >> 0x1f);
    pfVar1 = (float *)-(iVar3 >> 0x1f);
    uVar6 = iVar5 + (iVar3 + (int)pfVar1) * -10;
    if (*(uint *)(param_9 + 0x180) != uVar6) {
      *(uint *)(param_9 + 0x180) = uVar6;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - dVar2),param_2,
                  param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar1,iVar5,
                  param_11 * 2,uVar6,param_15,param_16);
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801eb344  FUN_801eb344 ====

void FUN_801eb344(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801eb364  FUN_801eb364 ====

void FUN_801eb364(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801eb384  FUN_801eb384 ====

void FUN_801eb384(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801eb4c0;
    *(code **)(puVar1 + 0x10c) = FUN_801ebae8;
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
    gnt4_memset(puVar1 + 0x144,0,0x18);
    iVar3 = 0;
    piVar4 = (int *)(puVar1 + 0x144);
    do {
      iVar2 = zz_0006d4c_();
      *piVar4 = iVar2;
      if (iVar2 == 0) {
        puVar1[0x18] = 2;
        return;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < 6);
  }
  return;
}



// ==== 801eb4c0  FUN_801eb4c0 ====

void FUN_801eb4c0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8039345c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801eb514  FUN_801eb514 ====

void FUN_801eb514(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar7 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar1 = FLOAT_8043c398;
  uVar6 = 0;
  dVar10 = (double)FLOAT_8043c398;
  *(undefined1 *)(param_9 + 0x89) = 1;
  fVar2 = FLOAT_8043c39c;
  dVar8 = (double)FLOAT_8043c39c;
  *(float *)(param_9 + 100) = fVar1;
  fVar3 = FLOAT_8043c3a0;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(undefined2 *)(param_9 + 0x15c) = 0;
  *(undefined2 *)(param_9 + 0x15e) = 0xa00;
  *(undefined2 *)(param_9 + 0x160) = 0;
  *(undefined2 *)(param_9 + 0x162) = 0;
  *(undefined2 *)(param_9 + 0x164) = 0x20;
  *(undefined2 *)(param_9 + 0x166) = 0x30;
  *(undefined2 *)(param_9 + 0x168) = 0;
  *(undefined2 *)(param_9 + 0x16a) = 0;
  *(undefined2 *)(param_9 + 0x16c) = 0x100;
  *(undefined2 *)(param_9 + 0x16e) = 0x100;
  *(float *)(param_9 + 0xb4) = fVar3;
  *(float *)(param_9 + 0xb8) = fVar3;
  *(float *)(param_9 + 0x58) = fVar3;
  *(float *)(param_9 + 0x5c) = fVar3;
  *(float *)(param_9 + 0x60) = fVar3;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),1,iVar7 + 0xc28,uVar6,in_r8,
                      in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  uVar4 = 1;
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),1,iVar5,uVar6,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4,uVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c3a4,*(int *)(param_9 + 0xe4));
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe8),2,iVar7 + 0xc28,uVar6,in_r8,
                      in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  uVar4 = 2;
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xec),2,iVar5,uVar6,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec),
              extraout_r4_00,uVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c3a4,*(int *)(param_9 + 0xec));
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x144),3,iVar7 + 0xc28,uVar6,in_r8,
                      in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  uVar4 = 3;
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x148),3,iVar5,uVar6,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x148)
              ,extraout_r4_01,uVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c3a4,*(int *)(param_9 + 0x148));
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x14c),4,iVar7 + 0xc28,uVar6,in_r8,
                      in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  uVar4 = 4;
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x150),4,iVar5,uVar6,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x150)
              ,extraout_r4_02,uVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  uVar9 = zz_0007cac_((double)FLOAT_8043c3a4,*(int *)(param_9 + 0x150));
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x154),5,iVar7 + 0xc28,uVar6,in_r8,
                      in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  uVar4 = 5;
  uVar9 = zz_0007030_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0x158),5,iVar5,uVar6,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x158)
              ,extraout_r4_03,uVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c3a4,*(int *)(param_9 + 0x158));
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_01eb784_(param_9);
  return;
}



// ==== 801eb784  zz_01eb784_ ====

void zz_01eb784_(int param_1)

{
  short sVar1;
  double dVar2;
  int iVar3;
  undefined8 local_28;
  undefined8 local_18;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if ((*(uint *)(iVar3 + 0x5e0) & 0x20000000) == 0) {
    if ((*(uint *)(iVar3 + 0x5e0) & 0x10) != 0) {
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15e)) ^ 0x80000000);
      *(short *)(param_1 + 0x15c) =
           (short)(int)((float)(local_28 - DOUBLE_8043c3b8) * *(float *)(iVar3 + 0x5f4) +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x15c) ^ 0x80000000) -
                              DOUBLE_8043c3b8));
      zz_00f0104_(iVar3,0x19,5);
      sVar1 = *(short *)(param_1 + 0x15e);
      if (sVar1 < 1) {
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15c)) ^ 0x80000000);
        if ((float)(local_18 - DOUBLE_8043c3b8) < FLOAT_8043c3ac) {
          *(short *)(param_1 + 0x15e) = -sVar1;
          *(undefined2 *)(param_1 + 0x15c) = 0xf556;
        }
      }
      else {
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x15c)) ^ 0x80000000);
        if (FLOAT_8043c3a8 < (float)(local_18 - DOUBLE_8043c3b8)) {
          *(short *)(param_1 + 0x15e) = -sVar1;
          *(undefined2 *)(param_1 + 0x15c) = 0xaaa;
        }
      }
    }
    if ((*(uint *)(iVar3 + 0x5e0) & 0x40) != 0) {
      *(undefined2 *)(param_1 + 0x15c) = 0;
    }
    dVar2 = DOUBLE_8043c3b8;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x164)) ^ 0x80000000);
    *(short *)(param_1 + 0x160) =
         (short)(int)((float)(local_18 - DOUBLE_8043c3b8) * *(float *)(iVar3 + 0x5f4) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x160) ^ 0x80000000) -
                            DOUBLE_8043c3b8));
    sVar1 = *(short *)(param_1 + 0x164);
    if (sVar1 < 1) {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x160)) ^ 0x80000000);
      if ((float)(local_18 - dVar2) < FLOAT_8043c3b4) {
        *(short *)(param_1 + 0x164) = -sVar1;
        *(undefined2 *)(param_1 + 0x160) = 0xfc72;
      }
    }
    else {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x160)) ^ 0x80000000);
      if (FLOAT_8043c3b0 < (float)(local_18 - dVar2)) {
        *(short *)(param_1 + 0x164) = -sVar1;
        *(undefined2 *)(param_1 + 0x160) = 0x38e;
      }
    }
    dVar2 = DOUBLE_8043c3b8;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x166)) ^ 0x80000000);
    *(short *)(param_1 + 0x162) =
         (short)(int)((float)(local_18 - DOUBLE_8043c3b8) * *(float *)(iVar3 + 0x5f4) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x162) ^ 0x80000000) -
                            DOUBLE_8043c3b8));
    sVar1 = *(short *)(param_1 + 0x166);
    if (sVar1 < 1) {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x162)) ^ 0x80000000);
      if ((float)(local_18 - dVar2) < FLOAT_8043c3b4) {
        *(short *)(param_1 + 0x166) = -sVar1;
        *(undefined2 *)(param_1 + 0x162) = 0xfc72;
      }
    }
    else {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x162)) ^ 0x80000000);
      if (FLOAT_8043c3b0 < (float)(local_18 - dVar2)) {
        *(short *)(param_1 + 0x166) = -sVar1;
        *(undefined2 *)(param_1 + 0x162) = 0x38e;
      }
    }
    *(short *)(param_1 + 0x168) = -*(short *)(param_1 + 0x160);
    *(short *)(param_1 + 0x16a) = -*(short *)(param_1 + 0x162);
  }
  return;
}



// ==== 801eba80  FUN_801eba80 ====

void FUN_801eba80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  } while (iVar1 < 6);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ebae8  FUN_801ebae8 ====

/* WARNING: Removing unreachable block (ram,0x801ebd28) */
/* WARNING: Removing unreachable block (ram,0x801ebd10) */
/* WARNING: Removing unreachable block (ram,0x801ebc9c) */
/* WARNING: Removing unreachable block (ram,0x801ebc84) */
/* WARNING: Removing unreachable block (ram,0x801ebbe4) */
/* WARNING: Removing unreachable block (ram,0x801ebb34) */

void FUN_801ebae8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  double dVar6;
  float local_178;
  undefined4 local_174;
  undefined4 local_170;
  float afStack_16c [12];
  float afStack_13c [12];
  float afStack_10c [3];
  float local_100;
  undefined4 local_f0;
  undefined4 local_e0;
  float afStack_dc [3];
  float local_d0;
  undefined4 local_c0;
  undefined4 local_b0;
  float afStack_ac [3];
  float local_a0;
  undefined4 local_90;
  undefined4 local_80;
  float afStack_7c [3];
  float local_70;
  undefined4 local_60;
  undefined4 local_50;
  float afStack_4c [3];
  float local_40;
  undefined4 local_30;
  undefined4 local_20;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar3 = 0;
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar4 = 0x44;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    iVar3 = 1;
    uVar4 = 0x44;
  }
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x15c) *
                                             0x3ff0000000000000)),afStack_13c,0x79);
  gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_ac);
  gnt4_PSMTXMultVec_bl(afStack_ac,(float *)&DAT_80393438,&local_178);
  local_a0 = local_178;
  local_90 = local_174;
  local_80 = local_170;
  gnt4_PSMTXConcat_bl(afStack_ac,afStack_13c,afStack_ac);
  gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_10c);
  gnt4_PSMTXMultVec_bl(afStack_10c,(float *)&DAT_80393450,&local_178);
  local_100 = local_178;
  local_f0 = local_174;
  local_e0 = local_170;
  gnt4_PSMTXConcat_bl(afStack_10c,afStack_13c,afStack_10c);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     -(double)((longlong)(double)*(short *)(param_9 + 0x15c) *
                                              0x3ff0000000000000)),afStack_13c,0x79);
  gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_dc);
  gnt4_PSMTXMultVec_bl(afStack_dc,(float *)&DAT_80393444,&local_178);
  local_d0 = local_178;
  local_c0 = local_174;
  local_b0 = local_170;
  gnt4_PSMTXConcat_bl(afStack_dc,afStack_13c,afStack_dc);
  gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_4c);
  gnt4_PSMTXMultVec_bl(afStack_4c,(float *)&DAT_80393420,&local_178);
  local_40 = local_178;
  local_30 = local_174;
  local_20 = local_170;
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x160) *
                                             0x3ff0000000000000)),afStack_13c,0x78);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x162) *
                                             0x3ff0000000000000)),afStack_16c,0x79);
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_16c,afStack_4c);
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_13c,afStack_4c);
  gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_7c);
  gnt4_PSMTXMultVec_bl(afStack_7c,(float *)&DAT_8039342c,&local_178);
  dVar6 = (double)local_178;
  local_70 = local_178;
  local_60 = local_174;
  local_50 = local_170;
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x168) *
                                             0x3ff0000000000000)),afStack_13c,0x78);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c3c0 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x16a) *
                                             0x3ff0000000000000)),afStack_16c,0x79);
  gnt4_PSMTXConcat_bl(afStack_7c,afStack_16c,afStack_7c);
  pfVar1 = afStack_7c;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar1,afStack_13c,pfVar1);
  iVar2 = param_9 + iVar3 * 4;
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xe0),
              afStack_4c,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00097b4_(*(int *)(iVar2 + 0xe0),uVar4);
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xe8),
              afStack_7c,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00097b4_(*(int *)(iVar2 + 0xe8),uVar4);
  iVar2 = param_9 + iVar3 * 4;
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x144),
              afStack_ac,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00097b4_(*(int *)(iVar2 + 0x144),uVar4);
  iVar2 = param_9 + (iVar3 + 2) * 4;
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x144),
              afStack_dc,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00097b4_(*(int *)(iVar2 + 0x144),uVar4);
  iVar3 = param_9 + (iVar3 + 4) * 4;
  zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x144),
              afStack_10c,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar3 + 0x144),uVar4);
  return;
}



// ==== 801ebe10  zz_01ebe10_ ====

undefined4 zz_01ebe10_(int param_1,char param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x801) && (param_2 < '\x04')) {
    puVar2 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      puVar2[0x13] = param_2;
      puVar2[0x83] = 0x18;
      *(code **)(puVar2 + 0xc) = FUN_801ebf2c;
      *(code **)(puVar2 + 0x10c) = FUN_801ec13c;
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
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 801ebf2c  FUN_801ebf2c ====

void FUN_801ebf2c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a1038)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801ebf80  FUN_801ebf80 ====

void FUN_801ebf80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_800480f4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x45;
  *(undefined1 *)(param_9 + 0x89) = 3;
  fVar1 = FLOAT_8043c3c8;
  iVar3 = *(char *)(param_9 + 0x13) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_803a0ff4 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a0ff0 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a0ff8 + iVar3);
  *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_803a1020 + *(char *)(param_9 + 0x13) * 6);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_803a1022 + *(char *)(param_9 + 0x13) * 6);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803a1024 + *(char *)(param_9 + 0x13) * 6);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),7,iVar3 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar3 + 0xc28;
  uVar2 = 7;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),7,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c3cc,*(int *)(param_9 + 0xe4));
  zz_01ec0d4_(param_9);
  return;
}



// ==== 801ec0d4  zz_01ec0d4_ ====

void zz_01ec0d4_(int param_1)

{
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x146) == '\0') {
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



