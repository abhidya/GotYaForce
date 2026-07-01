// ==== 80195d8c  FUN_80195d8c ====

void FUN_80195d8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  double dVar4;
  undefined8 uVar5;
  
  fVar2 = FLOAT_8043b2e8;
  fVar1 = FLOAT_8043b188;
  dVar4 = (double)FLOAT_8043b188;
  pfVar3 = (float *)0x67;
  *(float *)(param_9 + 0xd4) = FLOAT_8043b188;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x67,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar3,param_12,param_13
                      ,param_14,param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar3,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80195e04  FUN_80195e04 ====

void FUN_80195e04(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  bool bVar3;
  undefined8 uVar4;
  double dVar5;
  
  fVar2 = FLOAT_8043b190;
  fVar1 = FLOAT_8043b188;
  dVar5 = (double)*(float *)(param_9 + 0xd4);
  if (PTR_DAT_80433944[0x6f] == '\0') {
    bVar3 = (float)(dVar5 - (double)FLOAT_8043b2d4) < FLOAT_8043b188;
    *(float *)(param_9 + 0xd4) = (float)(dVar5 - (double)FLOAT_8043b2d4);
    if (bVar3) {
      *(float *)(param_9 + 0xd4) = fVar1;
    }
  }
  else {
    bVar3 = FLOAT_8043b190 < (float)(dVar5 + (double)FLOAT_8043b2d4);
    *(float *)(param_9 + 0xd4) = (float)(dVar5 + (double)FLOAT_8043b2d4);
    if (bVar3) {
      *(float *)(param_9 + 0xd4) = fVar2;
    }
  }
  if ((double)*(float *)(param_9 + 0xd4) != dVar5) {
    uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar5,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
                ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80195ea4  FUN_80195ea4 ====

void FUN_80195ea4(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
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
  
  if (FLOAT_8043b188 < *(float *)(param_1 + 0xd4)) {
    dVar2 = (double)*(float *)(param_1 + 0x24);
    dVar3 = (double)*(float *)(param_1 + 0x28);
    uVar1 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar2,dVar3,
                               (float *)(param_1 + 0x114));
    zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 80195f2c  FUN_80195f2c ====

void FUN_80195f2c(void)

{
  DAT_80436378 = &DAT_803d4960;
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    PTR_DAT_80433930[0x40] = 0;
    zz_002a5f4_(0,0,0,0);
    gnt4_memset(DAT_80436378,0,0x16);
  }
  (*(code *)(&PTR_FUN_8036f560)[*DAT_80436378])();
  return;
}



// ==== 80195fbc  FUN_80195fbc ====

void FUN_80195fbc(void)

{
  *DAT_80436378 = 1;
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  gnt4_memset(PTR_DAT_80433944,0,0x4a0);
  PTR_DAT_80433934[0x1c] = 0xff;
  *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = 999999;
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = 999999;
  zz_0196f3c_();
  zz_0006b74_();
  return;
}



// ==== 80196030  FUN_80196030 ====

void FUN_80196030(void)

{
  uint uVar1;
  
  if (DAT_80436378[2] == 0) {
    DAT_80436378[2] = 1;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    *(undefined2 *)PTR_DAT_80433944 = 0;
    if (PTR_DAT_80433944[0x17] != '\0') {
      PTR_DAT_80433944[(char)PTR_DAT_80433944[0x14] * 0x80 + 0x161] =
           *(undefined1 *)((int)DAT_80436378 + 0x15);
    }
  }
  else {
    uVar1 = zz_018f56c_();
    if ((int)uVar1 < 0) {
      *DAT_80436378 = 7;
      DAT_80436378[2] = 1;
    }
    else if ((uVar1 & 0x8000) == 0) {
      if (0 < (int)uVar1) {
        *DAT_80436378 = 3;
        DAT_80436378[2] = 0;
        *(undefined *)(DAT_80436378 + 10) = PTR_DAT_80433944[0x16];
        *(undefined *)((int)DAT_80436378 + 0x13) = PTR_DAT_80433944[0x15];
        *(undefined *)(DAT_80436378 + 9) = (&DAT_804356d0)[*(char *)((int)DAT_80436378 + 0x13)];
        *(undefined4 *)(PTR_DAT_80433934 + 0x120) =
             *(undefined4 *)(&DAT_8036f554 + *(char *)((int)DAT_80436378 + 0x13) * 4);
      }
    }
    else {
      *DAT_80436378 = 2;
      DAT_80436378[2] = 0;
      *(char *)((int)DAT_80436378 + 0x15) = (char)uVar1;
    }
  }
  return;
}



// ==== 80196188  FUN_80196188 ====

void FUN_80196188(void)

{
  int iVar1;
  
  if (DAT_80436378[2] == 0) {
    DAT_80436378[2] = 1;
    gnt4_memset(PTR_DAT_80435a30,0,0x200);
    PTR_DAT_80435a30[0x46] = PTR_DAT_80433944[0x14];
    PTR_DAT_80435a30[0x47] = (char)(1 << (int)(char)PTR_DAT_80433944[0x14]);
    PTR_DAT_80435a30[0x149] = 3;
    PTR_DAT_80435a30[0x40] = *(undefined1 *)((int)DAT_80436378 + 0x15);
    *(undefined4 *)(PTR_DAT_80435a30 + 0x24) =
         *(undefined4 *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x140);
    *(undefined4 *)(PTR_DAT_80435a30 + 0x28) =
         *(undefined4 *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x144);
    *(undefined4 *)(PTR_DAT_80435a30 + 0x2c) =
         *(undefined4 *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x148);
    gnt4_memcpy(&DAT_803bfe20,*(void **)(PTR_DAT_80435a30 + 0x2c),600);
  }
  else {
    iVar1 = zz_01ba750_();
    if (iVar1 != 0) {
      *DAT_80436378 = 1;
      DAT_80436378[2] = 0;
      *(undefined *)((int)DAT_80436378 + 0x15) = PTR_DAT_80435a30[0x40];
    }
  }
  return;
}



// ==== 801962c4  FUN_801962c4 ====

void FUN_801962c4(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 local_68 [2];
  undefined2 local_64;
  int local_60 [4];
  int local_50;
  int local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  int local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  iVar4 = 0;
  local_50 = 0;
  local_4c = 0;
  local_38 = 0;
  local_48 = 0;
  *DAT_80436378 = 4;
  local_34 = 0;
  PTR_DAT_80433934[0x15d9] = 0;
  local_44 = 0;
  PTR_DAT_80433934[0x15da] = 0;
  iVar10 = 3;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar4) == 0) {
      PTR_DAT_80433934[iVar4 + 0xcb] = 0xff;
    }
    else {
      PTR_DAT_80433934[iVar4 + 0xcb] = 0;
      local_50 = local_50 + 1;
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar4);
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
    }
    uVar3 = 1 << iVar4 + 1;
    if (((int)(char)PTR_DAT_80433930[2] & uVar3) == 0) {
      PTR_DAT_80433934[iVar4 + 0xcc] = 0xff;
    }
    else {
      PTR_DAT_80433934[iVar4 + 0xcc] = 0;
      local_50 = local_50 + 1;
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)uVar3;
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
    }
    iVar4 = iVar4 + 2;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  cVar1 = *(char *)((int)DAT_80436378 + 0x13);
  iVar4 = (int)(short)DAT_80436378[8];
  iVar9 = 0;
  iVar8 = 0;
  iVar10 = 0;
  local_40 = 2;
  local_3c = 2;
  local_60[2] = (int)(char)(&PTR_DAT_8036f40c)[cVar1][iVar4];
  local_60[0] = *(int *)((&PTR_DAT_8036f4b8)[cVar1] + iVar4 * 4);
  local_60[3] = (int)(char)(&PTR_DAT_8036f434)[cVar1][iVar4];
  local_60[1] = *(undefined4 *)((&PTR_DAT_8036f53c)[cVar1] + iVar4 * 4);
  iVar4 = 0;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar4) == 0) {
      PTR_DAT_80433934[iVar4 + 0x5a] = 0;
      iVar5 = -1;
      PTR_DAT_80433934[iVar9 + 0x1654] = 0;
      if (local_50 < local_40) {
        iVar5 = 0;
        PTR_DAT_80433934[iVar4 + 0xcb] = 0;
        local_50 = local_50 + 1;
      }
      else if (local_4c < local_3c) {
        iVar5 = local_4c + 1;
        local_4c = iVar5;
        PTR_DAT_80433934[iVar4 + 0xcb] = 1;
      }
      if (-1 < iVar5) {
        iVar5 = 0;
        PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar4);
        iVar6 = 0;
        PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
        PTR_DAT_80433934[iVar4 + 0x5a] = 0;
        while( true ) {
          if (local_60[(char)PTR_DAT_80433934[iVar4 + 0xcb] + 2] <= iVar6) break;
          uVar3 = zz_00055fc_();
          iVar2 = (short)DAT_80436378[8] * 4 + (uVar3 & 3);
          if (PTR_DAT_80433934[iVar4 + 0xcb] == '\0') {
            iVar2 = zz_0196eb8_((int)(char)(&PTR_DAT_8036f360)[*(char *)((int)DAT_80436378 + 0x13)]
                                           [iVar2]);
            local_68[0] = (undefined2)iVar2;
          }
          else {
            iVar2 = zz_0196eb8_((int)(char)(&PTR_DAT_8036f3e4)[*(char *)((int)DAT_80436378 + 0x13)]
                                           [iVar2]);
            local_68[0] = (undefined2)iVar2;
          }
          local_64 = local_68[0];
          uVar3 = zz_0066168_((char *)local_68,0);
          iVar5 = iVar5 + (int)(uVar3 << 1) / 3 + ((int)(uVar3 << 1 | uVar3 >> 0x1f) >> 0x1f) +
                          ((uVar3 & 0x7fffffff) >> 0x1e);
          if (local_60[(char)PTR_DAT_80433934[iVar4 + 0xcb]] < iVar5) break;
          iVar6 = iVar6 + 1;
          *(undefined2 *)
           (PTR_DAT_80433934 + iVar8 + (char)PTR_DAT_80433934[iVar4 + 0x5a] * 0x1c + 0x1e8) =
               local_64;
          PTR_DAT_80433934[iVar8 + (char)PTR_DAT_80433934[iVar4 + 0x5a] * 0x1c + 0x1ea] = 0;
          PTR_DAT_80433934[iVar8 + (char)PTR_DAT_80433934[iVar4 + 0x5a] * 0x1c + 0x1eb] = 0;
          PTR_DAT_80433934[iVar4 + 0x5a] = PTR_DAT_80433934[iVar4 + 0x5a] + '\x01';
        }
      }
    }
    iVar2 = iVar10 + 0x10;
    PTR_DAT_80433934[iVar4 + 0x20] = 0xe;
    iVar6 = iVar8 + 0x1e8;
    PTR_DAT_80433934[iVar4 + 0x3e] = 3;
    iVar5 = iVar8 + 0x1ea;
    iVar9 = iVar9 + 0x29;
    iVar8 = iVar8 + 0x348;
    iVar10 = iVar10 + 2;
    iVar7 = iVar4 + 1;
    PTR_DAT_80433934[iVar4 + 0x32] =
         (&DAT_804356ec)
         [(int)(char)PTR_DAT_80433934[iVar4 + 0xcb] + *(char *)((int)DAT_80436378 + 0x13) * 2];
    PTR_DAT_80433934[iVar4 + 0x54] = 0;
    *(undefined2 *)(PTR_DAT_80433934 + iVar2) = *(undefined2 *)(PTR_DAT_80433934 + iVar6);
    PTR_DAT_80433934[iVar4 + 0xa0] = PTR_DAT_80433934[iVar5];
    iVar4 = iVar7;
    if (5 < iVar7) {
      iVar4 = 0;
      PTR_DAT_80433934[0x53] = 2;
      *(undefined2 *)(PTR_DAT_80433934 + 0x46) = DAT_80436378[8];
      for (iVar10 = 0; iVar10 < (char)PTR_DAT_80433934[0x53]; iVar10 = iVar10 + 1) {
        iVar8 = iVar4 + 0x110;
        PTR_DAT_80433934[iVar4 + 0xf4] = (char)iVar10;
        iVar4 = iVar4 + 0x3c;
        *(undefined2 *)(PTR_DAT_80433934 + iVar8) = 0;
      }
      *(undefined4 *)(PTR_DAT_80433934 + 0x48) = 18000;
      *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = 18000;
      PTR_DAT_80433934[0x50] = 1;
      PTR_DAT_80433930[0x33] = 1;
      if (PTR_DAT_80433930[3] == '\x01') {
        PTR_DAT_80433930[0x29] = 0;
      }
      else if (PTR_DAT_80433930[3] == '\x02') {
        PTR_DAT_80433930[0x29] = 1;
        PTR_DAT_80433930[0x3d] = 1;
      }
      zz_0029fd4_();
      zz_000685c_(0);
      zz_00064d4_();
      *PTR_DAT_80433950 = (&DAT_804356e4)[*(char *)((int)DAT_80436378 + 0x13) * 2];
      PTR_DAT_80433950[1] = *(undefined1 *)(*(char *)((int)DAT_80436378 + 0x13) * 2 + -0x7fbca91b);
      zz_0027c1c_();
      return;
    }
  } while( true );
}



// ==== 8019688c  FUN_8019688c ====

void FUN_8019688c(void)

{
  (*(code *)(&PTR_FUN_8036f580)[*(short *)(DAT_80436378 + 4)])();
  zz_0196f64_();
  return;
}



// ==== 801968cc  FUN_801968cc ====

void FUN_801968cc(void)

{
  int iVar1;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    *(short *)(DAT_80436378 + 4) = *(short *)(DAT_80436378 + 4) + 1;
    PTR_DAT_80433934[7] = 0;
    PTR_DAT_80433934[6] = 0;
    PTR_DAT_80433934[5] = 0;
    PTR_DAT_80433934[4] = 0;
    PTR_DAT_80433934[3] = 0;
    PTR_DAT_80433934[2] = 0;
    PTR_DAT_80433934[1] = 0;
    *PTR_DAT_80433934 = 0;
  }
  return;
}



// ==== 80196948  FUN_80196948 ====

void FUN_80196948(void)

{
  zz_0028264_();
  if (*PTR_DAT_80433930 == '\x01') {
    *(short *)(DAT_80436378 + 4) = *(short *)(DAT_80436378 + 4) + 1;
    *PTR_DAT_80433930 = 3;
    PTR_DAT_80433930[1] = 1;
  }
  return;
}



// ==== 801969a0  FUN_801969a0 ====

void FUN_801969a0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  puVar2 = DAT_80436378;
  iVar4 = -1;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    if (-1 < iVar4) break;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
      iVar4 = iVar3;
    }
  }
  if ((((int)(char)PTR_DAT_80433934[0x1f] & 1 << (int)(char)PTR_DAT_80433934[iVar4 + 0xcb]) == 0) ||
     (2 < (char)PTR_DAT_80433934[0x1f])) {
    *DAT_80436378 = 6;
  }
  else {
    sVar1 = DAT_80436378[8];
    DAT_80436378[8] = sVar1 + 1;
    if ((int)(short)(sVar1 + 1) < (int)*(char *)(puVar2 + 9)) {
      *DAT_80436378 = 3;
      uVar5 = zz_0196dac_();
      uVar5 = zz_0042454_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar5 = zz_0042690_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_00437b0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
    }
    else {
      *DAT_80436378 = 5;
    }
  }
  DAT_80436378[2] = 0;
  return;
}



// ==== 80196a9c  FUN_80196a9c ====

void FUN_80196a9c(void)

{
  int iVar1;
  
  if (DAT_80436378[2] == 0) {
    DAT_80436378[2] = 1;
    *(undefined2 *)(PTR_DAT_80433930 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433930 + 6) = 1;
    zz_01f5ae0_(*(undefined1 *)((int)DAT_80436378 + 0x13));
  }
  iVar1 = zz_01f5b68_();
  if (iVar1 != 0) {
    *DAT_80436378 = 7;
    DAT_80436378[2] = 0;
  }
  return;
}



// ==== 80196b1c  FUN_80196b1c ====

void FUN_80196b1c(void)

{
  DAT_803c1140 = &DAT_8036f58c;
  DAT_803c1144 = 0;
  DAT_803c1150 = &DAT_804356f4;
  DAT_803c115c = &DAT_804356fc;
  DAT_803c113c = 0;
  DAT_803c1174 = FLOAT_8043b2f0;
  if (*(short *)(PTR_DAT_80433930 + 6) == 0) {
    DAT_803c1160 = &DAT_803c04b0;
  }
  else {
    DAT_803c1160 = &DAT_803c04c8;
  }
  DAT_803c1164 = 0;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 0;
  DAT_803c1173 = 0xff;
  FUN_80051ef4(-0x7fc3eed0);
  return;
}



// ==== 80196bc4  zz_0196bc4_ ====

undefined4
zz_0196bc4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
           undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  puVar2 = PTR_DAT_80433930;
  uVar5 = 0;
  sVar1 = *(short *)(PTR_DAT_80433930 + 4);
  if (sVar1 == 2) {
    zz_008c0dc_(FUN_80196b1c);
    sVar1 = *(short *)(PTR_DAT_80433930 + 10);
    *(short *)(PTR_DAT_80433930 + 10) = sVar1 + -1;
    if (((short)(sVar1 + -1) < 0) || (uVar4 = zz_008bab0_(0xf,1,0), (uVar4 & 0x1f70) != 0)) {
      *(short *)(PTR_DAT_80433930 + 4) = *(short *)(PTR_DAT_80433930 + 4) + 1;
      zz_0027aac_(0,0x3c,1);
    }
  }
  else if (sVar1 < 2) {
    if (sVar1 == 0) {
      *(undefined2 *)(PTR_DAT_80433930 + 4) = 1;
      zz_00441bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,puVar2,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
    else if (sVar1 < 0) {
      return 0;
    }
    iVar3 = zz_000a3c4_();
    if (iVar3 == 0) {
      *(short *)(PTR_DAT_80433930 + 4) = *(short *)(PTR_DAT_80433930 + 4) + 1;
      *(undefined2 *)(PTR_DAT_80433930 + 10) = 300;
      zz_0027aac_(0,0x3c,0);
    }
  }
  else if (sVar1 < 4) {
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      zz_0027c1c_();
      uVar5 = 1;
    }
    else {
      zz_008c0dc_(FUN_80196b1c);
    }
  }
  return uVar5;
}



// ==== 80196cec  FUN_80196cec ====

void FUN_80196cec(void)

{
  int iVar1;
  
  if (DAT_80436378[2] == 0) {
    DAT_80436378[2] = 1;
    *(undefined2 *)(PTR_DAT_80433930 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433930 + 6) = 1;
    zz_01f5ae0_(3);
  }
  iVar1 = zz_01f5b68_();
  if (iVar1 != 0) {
    *DAT_80436378 = 7;
    DAT_80436378[2] = 0;
  }
  return;
}



// ==== 80196dac  zz_0196dac_ ====

void zz_0196dac_(void)

{
  uint uVar1;
  uint uVar2;
  
  do {
    uVar1 = zz_00055fc_();
    uVar1 = (uVar1 & 0xff) % 0xb;
    if (10 < uVar1) {
      uVar1 = 0;
    }
  } while (PTR_DAT_80433934[0x1c] == (&DAT_8036f548)[uVar1]);
  PTR_DAT_80433934[0x1c] = (&DAT_8036f548)[uVar1];
  uVar1 = zz_00055fc_();
  PTR_DAT_80433934[0x1d] = (char)uVar1 + (char)(uVar1 / 3) * -3;
  uVar1 = LooseBallAnims__GetDesperationInfo_unsigned((int)(char)PTR_DAT_80433934[0x1c]);
  uVar2 = zz_00055fc_();
  PTR_DAT_80433934[0x1e] = (char)uVar2 - (char)(uVar2 / uVar1) * (char)uVar1;
  return;
}



// ==== 80196e80  zz_0196e80_ ====

undefined4 zz_0196e80_(void)

{
  if (PTR_DAT_80433930[0x32] != '\x01') {
    return 0;
  }
  if ((int)*(short *)(DAT_80436378 + 0x10) < *(char *)(DAT_80436378 + 0x12) + -1) {
    return 0;
  }
  return 1;
}



// ==== 80196eb8  zz_0196eb8_ ====

int zz_0196eb8_(int param_1)

{
  short *psVar1;
  short *psVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  psVar1 = (short *)(&PTR_DAT_80380804)[param_1];
  for (psVar2 = psVar1; *psVar2 != -1; psVar2 = psVar2 + 1) {
    uVar5 = uVar5 + 1;
  }
  if (uVar5 == 0) {
    iVar3 = 8;
  }
  else {
    uVar4 = zz_00055fc_();
    iVar3 = (int)psVar1[uVar4 - (uVar4 / uVar5) * uVar5];
  }
  return iVar3;
}



// ==== 80196f3c  zz_0196f3c_ ====

void zz_0196f3c_(void)

{
  *(undefined2 *)(PTR_DAT_80433934 + 0x182a) = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0x182c) = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0x182e) = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0x1830) = 0;
  return;
}



// ==== 80196f64  zz_0196f64_ ====

void zz_0196f64_(void)

{
  zz_0196f84_();
  return;
}



// ==== 80196f84  zz_0196f84_ ====

void zz_0196f84_(void)

{
  short sVar1;
  
  if (*(short *)(PTR_DAT_80433934 + 0x182a) < 0) {
    return;
  }
  sVar1 = *(short *)(PTR_DAT_80433934 + 0x182a) + 1;
  *(short *)(PTR_DAT_80433934 + 0x182a) = sVar1;
  if (sVar1 < 0x3c) {
    return;
  }
  *(undefined2 *)(PTR_DAT_80433934 + 0x182a) = 0;
  sVar1 = *(short *)(PTR_DAT_80433934 + 0x182c);
  *(short *)(PTR_DAT_80433934 + 0x182c) = sVar1 + 1;
  if ((short)(sVar1 + 1) < 0x3c) {
    return;
  }
  *(undefined2 *)(PTR_DAT_80433934 + 0x182c) = 0;
  sVar1 = *(short *)(PTR_DAT_80433934 + 0x182e);
  *(short *)(PTR_DAT_80433934 + 0x182e) = sVar1 + 1;
  if ((short)(sVar1 + 1) < 0x3c) {
    return;
  }
  *(undefined2 *)(PTR_DAT_80433934 + 0x182e) = 0;
  sVar1 = *(short *)(PTR_DAT_80433934 + 0x1830);
  *(short *)(PTR_DAT_80433934 + 0x1830) = sVar1 + 1;
  if ((short)(sVar1 + 1) < 100) {
    return;
  }
  *(undefined2 *)(PTR_DAT_80433934 + 0x1830) = 99;
  *(undefined2 *)(PTR_DAT_80433934 + 0x182e) = 0x3b;
  *(undefined2 *)(PTR_DAT_80433934 + 0x182c) = 0x3b;
  *(undefined2 *)(PTR_DAT_80433934 + 0x182a) = 0xffff;
  return;
}



// ==== 80197048  zz_0197048_ ====

void zz_0197048_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x904) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_8019713c;
    *(code **)(puVar1 + 0x10c) = FUN_801977d4;
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



// ==== 8019713c  FUN_8019713c ====

void FUN_8019713c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8036f5a8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80197190  FUN_80197190 ====

void FUN_80197190(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
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
  *(undefined1 *)(param_9 + 0x89) = 0;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043b2f8;
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 100) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),0x19,iVar5 + 0xc28,uVar4,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  uVar2 = 0x19;
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),0x19,iVar3,uVar4,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,uVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043b2fc,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined1 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  zz_0197278_(param_9);
  return;
}



// ==== 80197278  zz_0197278_ ====

void zz_0197278_(int param_1)

{
  uint uVar1;
  undefined *local_18 [6];
  
  local_18[2] = PTR_FUN_802b3648;
  local_18[1] = PTR_FUN_802b3644;
  local_18[0] = PTR_LAB_802b3640;
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0xb4);
  uVar1 = (int)*(char *)(*(int *)(param_1 + 0x90) + 0x144) & 0xf7;
  if (uVar1 == 6) {
    *(undefined1 *)(param_1 + 0x144) = 6;
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  else if (uVar1 < 6) {
    if (uVar1 == 0) {
      *(undefined1 *)(param_1 + 0x144) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
    }
    else if (4 < uVar1) {
      *(undefined1 *)(param_1 + 0x144) = 5;
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined1 *)(param_1 + 0x1a) = 0;
    }
  }
  (*(code *)local_18[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80197364  FUN_80197364 ====

void FUN_80197364(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    fVar2 = FLOAT_8043b2f8;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    dVar4 = DOUBLE_8043b308;
    *(undefined1 *)(param_1 + 0x154) = 0;
    fVar3 = FLOAT_8043b300;
    *(float *)(param_1 + 0x68) = fVar2;
    *(undefined2 *)(param_1 + 0x72) = 0;
    *(float *)(param_1 + 0x60) = fVar2;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x58) = fVar2;
    *(undefined4 *)(param_1 + 0x158) = 0xf;
    *(float *)(param_1 + 0x148) =
         fVar3 / (float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x158) ^ 0x80000000) -
                        dVar4);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    return;
  }
  cVar1 = *(char *)(param_1 + 0x154);
  if (cVar1 == '\x02') {
LAB_8019746c:
    *(undefined4 *)(param_1 + 0x150) = 0xfffffe00;
    *(undefined4 *)(param_1 + 0x15c) = 0xc;
    *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
LAB_80197488:
    iVar5 = *(int *)(param_1 + 0x15c);
    *(int *)(param_1 + 0x15c) = iVar5 + -1;
    if (0 < iVar5) goto LAB_801974b8;
    *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined4 *)(param_1 + 0x14c) = 0;
        *(undefined4 *)(param_1 + 0x150) = 0x200;
        *(undefined4 *)(param_1 + 0x15c) = 0xf;
        *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
      }
      else if (cVar1 < '\0') goto LAB_801974a8;
      iVar5 = *(int *)(param_1 + 0x15c);
      *(int *)(param_1 + 0x15c) = iVar5 + -1;
      if (0 < iVar5) goto LAB_801974b8;
      *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
      goto LAB_8019746c;
    }
    if (cVar1 < '\x04') goto LAB_80197488;
  }
LAB_801974a8:
  *(undefined4 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
LAB_801974b8:
  *(int *)(param_1 + 0x14c) = *(int *)(param_1 + 0x14c) + *(int *)(param_1 + 0x150);
  if (*(int *)(param_1 + 0x14c) < 0) {
    *(undefined4 *)(param_1 + 0x14c) = 0;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + (short)*(undefined4 *)(param_1 + 0x14c);
  cVar1 = *(char *)(param_1 + 0x1b);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    iVar5 = *(int *)(param_1 + 0x158);
    *(int *)(param_1 + 0x158) = iVar5 + -1;
    if (0 < iVar5) {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x148);
      return;
    }
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  }
  fVar2 = FLOAT_8043b300;
  *(float *)(param_1 + 0x60) = FLOAT_8043b300;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  return;
}



// ==== 80197584  FUN_80197584 ====

void FUN_80197584(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    fVar2 = FLOAT_8043b2f8;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    dVar4 = DOUBLE_8043b308;
    *(undefined1 *)(param_1 + 0x154) = 0;
    fVar3 = FLOAT_8043b300;
    *(float *)(param_1 + 0x68) = fVar2;
    *(undefined2 *)(param_1 + 0x72) = 0;
    *(float *)(param_1 + 0x60) = fVar2;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x58) = fVar2;
    *(undefined4 *)(param_1 + 0x158) = 0xf;
    *(float *)(param_1 + 0x148) =
         fVar3 / (float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x158) ^ 0x80000000) -
                        dVar4);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    return;
  }
  cVar1 = *(char *)(param_1 + 0x154);
  if (cVar1 == '\x02') {
LAB_8019768c:
    *(undefined4 *)(param_1 + 0x150) = 0xfffffe00;
    *(undefined4 *)(param_1 + 0x15c) = 0xc;
    *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
LAB_801976a8:
    iVar5 = *(int *)(param_1 + 0x15c);
    *(int *)(param_1 + 0x15c) = iVar5 + -1;
    if (0 < iVar5) goto LAB_801976d8;
    *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined4 *)(param_1 + 0x14c) = 0;
        *(undefined4 *)(param_1 + 0x150) = 0x200;
        *(undefined4 *)(param_1 + 0x15c) = 0xf;
        *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
      }
      else if (cVar1 < '\0') goto LAB_801976c8;
      iVar5 = *(int *)(param_1 + 0x15c);
      *(int *)(param_1 + 0x15c) = iVar5 + -1;
      if (0 < iVar5) goto LAB_801976d8;
      *(char *)(param_1 + 0x154) = *(char *)(param_1 + 0x154) + '\x01';
      goto LAB_8019768c;
    }
    if (cVar1 < '\x04') goto LAB_801976a8;
  }
LAB_801976c8:
  *(undefined4 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
LAB_801976d8:
  *(int *)(param_1 + 0x14c) = *(int *)(param_1 + 0x14c) + *(int *)(param_1 + 0x150);
  if (*(int *)(param_1 + 0x14c) < 0) {
    *(undefined4 *)(param_1 + 0x14c) = 0;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + (short)*(undefined4 *)(param_1 + 0x14c);
  cVar1 = *(char *)(param_1 + 0x1b);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    iVar5 = *(int *)(param_1 + 0x158);
    *(int *)(param_1 + 0x158) = iVar5 + -1;
    if (0 < iVar5) {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x148);
      return;
    }
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  }
  fVar2 = FLOAT_8043b300;
  *(float *)(param_1 + 0x60) = FLOAT_8043b300;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
  return;
}



// ==== 801977b4  FUN_801977b4 ====

void FUN_801977b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801977d4  FUN_801977d4 ====

void FUN_801977d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 80197854  zz_0197854_ ====

void zz_0197854_(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)(&PTR_DAT_8036fa18)[param_1];
  DAT_80435708 = param_1;
  DAT_80436380 = piVar1;
  for (; *piVar1 != -1; piVar1 = piVar1 + 7) {
    if (*piVar1 != 0) {
      zz_0197950_(iVar2);
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801978d0  zz_01978d0_ ====

void zz_01978d0_(void)

{
  int iVar1;
  int *piVar2;
  
  if (DAT_80436380 != (int *)0x0) {
    iVar1 = 0;
    for (piVar2 = DAT_80436380; *piVar2 != -1; piVar2 = piVar2 + 7) {
      if (*piVar2 != 0) {
        zz_0197b94_(iVar1);
      }
      iVar1 = iVar1 + 1;
    }
    DAT_80436380 = (int *)0x0;
    DAT_80435708 = 0xffffffff;
  }
  return;
}



// ==== 80197950  zz_0197950_ ====

void zz_0197950_(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  undefined4 *__s;
  
  piVar4 = (int *)(DAT_80436380 + param_1 * 0x1c);
  if (*piVar4 == 0) {
    zz_0197bd8_(param_1,0);
  }
  else {
    uVar2 = piVar4[1];
    sVar1 = *(short *)(piVar4 + 4);
    zz_0197bd8_(param_1,(short)(uVar2 / (uint)(int)sVar1));
    piVar4[2] = 0;
    __s = (undefined4 *)(*piVar4 + DAT_80436238);
    piVar4[3] = (int)__s;
    puVar5 = (undefined4 *)0x0;
    for (iVar3 = 0; iVar3 < (int)(uVar2 / (uint)(int)sVar1); iVar3 = iVar3 + 1) {
      gnt4_memset(__s,0,(int)*(short *)(piVar4 + 4));
      *(char *)(__s + 2) = (char)param_1;
      if (puVar5 != (undefined4 *)0x0) {
        *puVar5 = __s;
      }
      puVar5 = __s;
      __s = (undefined4 *)((int)__s + (int)*(short *)(piVar4 + 4));
    }
  }
  return;
}



// ==== 80197a0c  zz_0197a0c_ ====

int * zz_0197a0c_(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)0x0;
  iVar3 = DAT_80436380 + param_1 * 0x1c;
  iVar1 = zz_0197bec_(param_1);
  if (0 < iVar1) {
    zz_0197bd8_(param_1,(short)iVar1 + -1);
    piVar2 = *(int **)(iVar3 + 0xc);
    *(int *)(iVar3 + 0xc) = *piVar2;
    *piVar2 = 0;
    *(undefined1 *)((int)piVar2 + 9) = 1;
    *(undefined1 *)((int)piVar2 + 10) = 0;
    iVar1 = *(int *)(iVar3 + 8);
    piVar2[1] = iVar1;
    if (iVar1 != 0) {
      **(undefined4 **)(iVar3 + 8) = piVar2;
    }
    *(int **)(iVar3 + 8) = piVar2;
    if ((*(code **)(iVar3 + 0x14) != (code *)0x0) &&
       (iVar1 = (**(code **)(iVar3 + 0x14))(piVar2), iVar1 != 0)) {
      zz_0197ad8_(piVar2);
      piVar2 = (int *)0x0;
    }
  }
  return piVar2;
}



// ==== 80197ad8  zz_0197ad8_ ====

void zz_0197ad8_(int *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (param_1 != (int *)0x0) {
    iVar3 = (int)*(char *)(param_1 + 2);
    iVar4 = DAT_80436380 + iVar3 * 0x1c;
    if (*(code **)(iVar4 + 0x18) != (code *)0x0) {
      (**(code **)(iVar4 + 0x18))();
    }
    iVar2 = *param_1;
    piVar1 = (int *)param_1[1];
    if (iVar2 == 0) {
      *(int **)(iVar4 + 8) = piVar1;
    }
    else {
      *(int **)(iVar2 + 4) = piVar1;
    }
    if (piVar1 != (int *)0x0) {
      *piVar1 = iVar2;
    }
    *param_1 = *(int *)(iVar4 + 0xc);
    *(int **)(iVar4 + 0xc) = param_1;
    *(undefined1 *)((int)param_1 + 9) = 0;
    iVar4 = zz_0197bec_(iVar3);
    zz_0197bd8_(iVar3,(short)iVar4 + 1);
  }
  return;
}



// ==== 80197b94  zz_0197b94_ ====

void zz_0197b94_(int param_1)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = DAT_80436380 + param_1 * 0x1c;
  while (piVar1 = *(int **)(iVar2 + 8), piVar1 != (int *)0x0) {
    zz_0197ad8_(piVar1);
  }
  return;
}



// ==== 80197bd8  zz_0197bd8_ ====

void zz_0197bd8_(int param_1,undefined2 param_2)

{
  *(undefined2 *)(DAT_80436380 + param_1 * 0x1c + 0x12) = param_2;
  return;
}



// ==== 80197bec  zz_0197bec_ ====

int zz_0197bec_(int param_1)

{
  return (int)*(short *)(DAT_80436380 + param_1 * 0x1c + 0x12);
}



// ==== 80197c00  zz_0197c00_ ====

void zz_0197c00_(void)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0x24;
  do {
    puVar1 = zz_008893c_(2,0x28,0,1);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0;
      puVar1[0x88] = 4;
      if (iVar2 < 0x1b) {
        puVar1[0x11] = 0x45;
      }
      else {
        puVar1[0x11] = 0x15;
      }
      puVar1[0x13] = (char)iVar2;
      if ((iVar2 == 0xf) || (iVar2 == 0x10)) {
        *(code **)(puVar1 + 0xc) = FUN_80197ed0;
        *(code **)(puVar1 + 0x10c) = FUN_80198094;
      }
      else {
        *(code **)(puVar1 + 0xc) = FUN_80197d98;
        *(code **)(puVar1 + 0x10c) = FUN_80197ea4;
      }
    }
    iVar2 = iVar2 + -1;
  } while (4 < iVar2);
  iVar2 = 2;
  do {
    puVar1 = zz_008893c_(2,0x28,0,1);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0;
      puVar1[0x88] = 4;
      puVar1[0x11] = 0x44;
      puVar1[0x13] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_80198100;
      *(code **)(puVar1 + 0x10c) = FUN_80197ea4;
    }
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  iVar2 = 4;
  do {
    puVar1 = zz_008893c_(2,0x10,0,1);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0;
      puVar1[0x88] = 4;
      puVar1[0x11] = 0x44;
      puVar1[0x13] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_80198270;
      *(code **)(puVar1 + 0x10c) = FUN_8019844c;
    }
    iVar2 = iVar2 + -1;
  } while (2 < iVar2);
  return;
}



// ==== 80197d98  FUN_80197d98 ====

void FUN_80197d98(int param_1)

{
  (*(code *)(&PTR_FUN_8036fa38)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80197dd4  FUN_80197dd4 ====

void FUN_80197dd4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  
  bVar1 = DAT_803bb3f4 != 0;
  *(int *)(param_9 + 0x54) = DAT_803bb3f4;
  if (bVar1) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(int)*(char *)(param_9 + 0x13),
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_0197e40_(param_9);
  }
  return;
}



// ==== 80197e40  zz_0197e40_ ====

void zz_0197e40_(int param_1)

{
  if (*PTR_DAT_80433930 == '\x01') {
    return;
  }
  if (*PTR_DAT_80433930 == '\x02') {
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80197e84  FUN_80197e84 ====

void FUN_80197e84(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80197ea4  FUN_80197ea4 ====

void FUN_80197ea4(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),(int)*(char *)(param_1 + 0x11));
  return;
}



// ==== 80197ed0  FUN_80197ed0 ====

void FUN_80197ed0(int param_1)

{
  (*(code *)(&PTR_FUN_8036fa48)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80197f0c  FUN_80197f0c ====

void FUN_80197f0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  float afStack_38 [13];
  
  bVar1 = DAT_803bb3f4 != 0;
  *(int *)(param_9 + 0x54) = DAT_803bb3f4;
  if (bVar1) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(int)*(char *)(param_9 + 0x13),
                param_12,param_13,param_14,param_15,param_16);
    gnt4_PSMTXTrans_bl((double)FLOAT_8043b310,(double)FLOAT_8043b314,(double)FLOAT_8043b318,
                       (float *)(param_9 + 0x114));
    gnt4_PSMTXRotRad_bl((double)FLOAT_8043b31c,afStack_38,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,(float *)(param_9 + 0x114));
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 80197fa4  FUN_80197fa4 ====

void FUN_80197fa4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar3 = FLOAT_8043b328;
  fVar2 = FLOAT_8043b320;
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    if (*PTR_DAT_80433930 != '\x01') {
      *(undefined1 *)(param_1 + 0x19) = 2;
      fVar3 = FLOAT_8043b324;
      *(float *)(param_1 + 0xd4) = fVar2;
      *(float *)(param_1 + 0xd8) = fVar3;
      zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(param_1 + 0xe0));
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) && (iVar4 = zz_01c7dd4_(), iVar4 == 0xc)) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined1 *)(param_1 + 0x82) = 1;
    }
  }
  else if (cVar1 < '\x03') {
    fVar2 = *(float *)(param_1 + 0xd4) + *(float *)(param_1 + 0xd8);
    *(float *)(param_1 + 0xd4) = fVar2;
    if (fVar3 < fVar2) {
      zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(param_1 + 0xe0));
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return;
}



// ==== 80198094  FUN_80198094 ====

void FUN_80198094(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  if (*(char *)(param_9 + 0x13) == '\x0f') {
    gnt4_PSMTXInverse_bl((float *)&DAT_803c1100,afStack_38);
    pfVar1 = afStack_38;
    uVar2 = gnt4_PSMTXConcat_bl(pfVar1,(float *)(param_9 + 0x114),pfVar1);
    zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,
                param_15,param_16);
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80198100  FUN_80198100 ====

void FUN_80198100(int param_1)

{
  (*(code *)(&PTR_FUN_8036fa58)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8019813c  FUN_8019813c ====

void FUN_8019813c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  undefined8 uVar3;
  
  bVar1 = DAT_803bb3f4 != 0;
  *(int *)(param_9 + 0x54) = DAT_803bb3f4;
  if (bVar1) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    pfVar2 = (float *)(int)*(char *)(param_9 + 0x13);
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(int)pfVar2,param_12,param_13,
                param_14,param_15,param_16);
    uVar3 = zz_00087d4_((double)FLOAT_8043b328,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),pfVar2,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,param_15,
                param_16);
  }
  return;
}



// ==== 801981b0  FUN_801981b0 ====

void FUN_801981b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if ((sVar3 < 1) || (*PTR_DAT_80433930 != '\x01')) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
    else {
      zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (iVar2 = zz_01c7dd4_(), 10 < iVar2)) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0x78;
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f03c0_(0,0x179);
  }
  return;
}



// ==== 80198270  FUN_80198270 ====

void FUN_80198270(int param_1)

{
  (*(code *)(&PTR_FUN_8036fa68)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801982ac  FUN_801982ac ====

void FUN_801982ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  undefined8 uVar3;
  
  bVar1 = DAT_803bb3f4 != 0;
  *(int *)(param_9 + 0x54) = DAT_803bb3f4;
  if (bVar1) {
    *(undefined1 *)(param_9 + 0x18) = 1;
    pfVar2 = (float *)(int)*(char *)(param_9 + 0x13);
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(int)pfVar2,param_12,param_13,
                param_14,param_15,param_16);
    uVar3 = zz_00087d4_((double)FLOAT_8043b328,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),pfVar2,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,param_15,
                param_16);
    *(code **)(param_9 + 0x100) = FUN_801983f0;
    zz_0089100_(param_9,1,1);
  }
  return;
}



// ==== 8019833c  FUN_8019833c ====

void FUN_8019833c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if ((sVar3 < 1) || (*PTR_DAT_80433930 != '\x01')) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
    else {
      zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (iVar2 = zz_01c7dd4_(), 2 < iVar2)) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0x28;
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801983f0  FUN_801983f0 ====

void FUN_801983f0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)((int)&DAT_803c4e84 +
                  ((3U - (int)*(char *)(param_1 + 0x13) | (int)*(char *)(param_1 + 0x13) - 3U) >>
                   0x1d & 4));
  if (*(char *)(iVar1 + 0x82) == '\0') {
    gnt4_PSMTXCopy_bl((float *)(iVar1 + 0x904),(float *)(param_1 + 0x114));
  }
  return;
}



// ==== 8019844c  FUN_8019844c ====

void FUN_8019844c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),(int)*(char *)(param_9 + 0x11));
  return;
}



// ==== 801985b0  FUN_801985b0 ====

uint FUN_801985b0(uint param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = param_1;
  if (*(short *)(param_1 + 1000) == 0x10a) {
    zz_00de5a4_(param_1,4,param_1 + 0x144);
    bVar2 = zz_00de5a4_(param_1,5,param_1 + 0x145);
    uVar1 = (uint)bVar2;
  }
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  return uVar1;
}



// ==== 8019860c  FUN_8019860c ====

void FUN_8019860c(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    *(undefined2 *)(param_1 + 0x18da) = 0;
  }
  if (*(short *)(param_1 + 1000) == 0x10a) {
    if ((*(char *)(param_1 + 0x144) == '\0') && (*(char *)(param_1 + 0x145) == '\0')) {
      if (*(short *)(param_1 + 0x774) < 1) {
        zz_006de10_(param_1,0);
      }
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
    }
  }
  return;
}



// ==== 801986d8  FUN_801986d8 ====

void FUN_801986d8(undefined4 param_1,char param_2,char param_3)

{
  (**(code **)(&DAT_80435710 + param_2 * 4))(param_1,(int)param_3);
  return;
}



// ==== 80198714  FUN_80198714 ====

void FUN_80198714(int param_1)

{
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float afStack_44 [3];
  float local_38;
  undefined4 local_28;
  undefined4 local_18;
  
  if (*(short *)(param_1 + 1000) == 0x105) {
    local_50 = *(float *)(param_1 + 0xa24);
    local_4c = *(undefined4 *)(param_1 + 0xa34);
    local_48 = *(undefined4 *)(param_1 + 0xa44);
    gnt4_PSQUATScale_bl((double)FLOAT_8043b330,&local_50,&local_50);
    local_5c = *(undefined4 *)(param_1 + 0xa2c);
    local_58 = *(undefined4 *)(param_1 + 0xa3c);
    local_54 = *(undefined4 *)(param_1 + 0xa4c);
    gnt4_PSMTXIdentity_bl(afStack_44);
    zz_0045ef4_(afStack_44,5,&local_50,&local_5c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xa24),(float *)&DAT_8036fab8,&local_68);
    local_38 = local_68;
    local_28 = local_64;
    local_18 = local_60;
    zz_00aedc0_(param_1,afStack_44,0,*(undefined1 *)(param_1 + 0x88));
    local_50 = *(float *)(param_1 + 0xae4);
    local_4c = *(undefined4 *)(param_1 + 0xaf4);
    local_48 = *(undefined4 *)(param_1 + 0xb04);
    local_5c = *(undefined4 *)(param_1 + 0xaec);
    local_58 = *(undefined4 *)(param_1 + 0xafc);
    local_54 = *(undefined4 *)(param_1 + 0xb0c);
    gnt4_PSMTXIdentity_bl(afStack_44);
    zz_0045ef4_(afStack_44,5,&local_50,&local_5c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xae4),(float *)&DAT_8036fac4,&local_68);
    local_38 = local_68;
    local_28 = local_64;
    local_18 = local_60;
    zz_00aedc0_(param_1,afStack_44,0,*(undefined1 *)(param_1 + 0x88));
    zz_00f036c_(param_1,6);
  }
  else if (*(short *)(param_1 + 1000) == 0x10a) {
    zz_00f036c_(param_1,9);
  }
  return;
}



// ==== 8019889c  FUN_8019889c ====

void FUN_8019889c(int param_1)

{
  (*(code *)(&PTR_FUN_8036fad0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801988d8  FUN_801988d8 ====

void FUN_801988d8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043b338;
  fVar1 = FLOAT_8043b334;
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_8043b338) * FLOAT_8043b334);
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) - dVar2
                           ) * fVar1);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8036fadc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80198984  FUN_80198984 ====

void FUN_80198984(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_zz_01989dc__8036faf4)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 801989dc  zz_01989dc_ ====

void zz_01989dc_(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  
  fVar2 = FLOAT_8043b344;
  fVar1 = FLOAT_8043b340;
  uVar3 = 0;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar3 = 0xe;
  }
  (*(code *)(&PTR_FUN_8036fb00)[*(char *)(param_1 + 0x581)])(param_1,uVar3);
  return;
}



// ==== 80198a50  FUN_80198a50 ====

void FUN_80198a50(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043b330,param_1,1,2,param_2,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\x02') || (*(char *)(param_1 + 0x1d0d) != param_2)) {
    zz_004beb8_((double)FLOAT_8043b330,param_1,2,2,param_2,4,2);
  }
  return;
}



// ==== 80198adc  FUN_80198adc ====

void FUN_80198adc(int param_1,int param_2)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    iVar1 = 3;
    if (*(char *)(param_1 + 0x5db) == '\x02') {
      iVar1 = 0;
    }
    zz_004beb8_((double)FLOAT_8043b330,param_1,1,2,iVar1 + param_2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80198b50  FUN_80198b50 ====

void FUN_80198b50(int param_1,int param_2)

{
  if ((*(char *)(param_1 + 0x543) < '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 4;
    zz_006a3d0_(param_1,'\0',4,2);
  }
  else {
    zz_004beb8_((double)FLOAT_8043b330,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
    if (((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) && ((*(uint *)(param_1 + 0x5e0) & 2) == 0)) {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 80198be8  FUN_80198be8 ====

void FUN_80198be8(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043b330,param_1,1,2,param_2 + 9,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043b330,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80198c68  FUN_80198c68 ====

void FUN_80198c68(int param_1,int param_2)

{
  zz_004beb8_((double)FLOAT_8043b330,param_1,1,2,param_2 + 6,0xffffffff,0xffffffff);
  return;
}



// ==== 80198ca0  FUN_80198ca0 ====

void FUN_80198ca0(int param_1)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x543) < '\0') {
    uVar1 = *(uint *)(param_1 + 0x5e0);
    if ((uVar1 & 0x40) == 0) {
      if ((uVar1 & 0x10) != 0) {
        *(undefined1 *)(param_1 + 0x581) = 0;
        zz_006a3d0_(param_1,'\0',0,2);
        return;
      }
    }
    else if ((uVar1 & 0x80) == 0) {
      zz_006d0dc_(param_1,0xc1,0);
    }
  }
  zz_004cd24_(param_1,1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019932c_(param_1);
  }
  return;
}



// ==== 80198d48  FUN_80198d48 ====

void FUN_80198d48(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043b348) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_0199208_(param_9);
        return;
      }
      goto LAB_80198dd0;
    }
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_80198dd0;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (*(char *)(param_9 + 0x1cee) == '\0') {
    return;
  }
LAB_80198dd0:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 80198e08  FUN_80198e08 ====

void FUN_80198e08(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8036fb18)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80198e50  FUN_80198e50 ====

void FUN_80198e50(int param_1)

{
  zz_01989dc_(param_1);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
  return;
}



// ==== 80198e98  FUN_80198e98 ====

/* WARNING: Removing unreachable block (ram,0x80198f44) */
/* WARNING: Removing unreachable block (ram,0x80198ea8) */

void FUN_80198e98(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043b348;
  if ((iVar3 != 0) ||
     (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) {
    zz_004cd24_(param_1,0xf);
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_019932c_(param_1);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
      zz_006a474_(param_1);
    }
  }
  else {
    dVar4 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = fVar2;
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  }
  return;
}



// ==== 80198f60  FUN_80198f60 ====

void FUN_80198f60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043b348) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) == 0) {
      if (((*(char *)(param_9 + 0x5db) == '\x01') && ((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0))
         && (*(char *)(param_9 + 0x1cee) == '\0')) {
        return;
      }
    }
    else {
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_0199208_(param_9);
        return;
      }
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(char *)(param_9 + 0x5db) == '\x01') {
      zz_006d0dc_(param_9,0xc1,0);
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,0,param_12,
              param_13,param_14,param_15,param_16);
  return;
}



// ==== 80199048  FUN_80199048 ====

void FUN_80199048(int param_1)

{
  int iVar1;
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffdf;
  iVar1 = zz_006c674_(param_1);
  if (iVar1 == 2) {
    *(undefined1 *)(param_1 + 0x581) = 0;
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 3;
    zz_006a3d0_(param_1,'\0',3,0);
  }
  return;
}



// ==== 801990c4  FUN_801990c4 ====

void FUN_801990c4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8036fb24)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019910c  FUN_8019910c ====

void FUN_8019910c(int param_1)

{
  double dVar1;
  
  zz_01989dc_(param_1);
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_8043b34c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b348;
  return;
}



// ==== 80199174  FUN_80199174 ====

void FUN_80199174(int param_1)

{
  zz_006d0dc_(param_1,0x81,0);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_019932c_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  FUN_80067310((double)FLOAT_8043b34c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_00b22f4_(param_1);
  return;
}



// ==== 80199208  zz_0199208_ ====

void zz_0199208_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  
  uVar3 = *(uint *)(param_1 + 0x5e0);
  if ((uVar3 & 0x100) == 0) {
    if ((uVar3 & 0x80) == 0) {
      if ((uVar3 & 0x20) == 0) {
        if ((uVar3 & 0x40) == 0) {
          if ((uVar3 & 0x10) == 0) {
            if (*(char *)(param_1 + 0x5e4) == '\x04') {
              uVar5 = 3;
            }
            else {
              uVar5 = 0;
            }
          }
          else {
            uVar5 = 1;
          }
        }
        else {
          uVar5 = 3;
        }
      }
      else if ((uVar3 & 0x40) == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = 3;
      }
    }
    else {
      uVar5 = 4;
    }
  }
  else {
    uVar5 = 5;
  }
  uVar4 = zz_006c674_(param_1);
  zz_006a3d0_(param_1,'\0',uVar5,(char)uVar4);
  *(undefined1 *)(param_1 + 0x540) = 1;
  fVar1 = FLOAT_8043b340;
  uVar4 = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  fVar2 = FLOAT_8043b344;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar4 = 0xf;
  }
  (*(code *)(&PTR_FUN_8036fb30)[*(char *)(param_1 + 0x581)])(param_1,uVar4);
  return;
}



// ==== 8019932c  zz_019932c_ ====

/* WARNING: Removing unreachable block (ram,0x80199470) */
/* WARNING: Removing unreachable block (ram,0x8019933c) */

void zz_019932c_(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  *(undefined2 *)(param_1 + 0x1900) = 0;
  zz_0046698_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    local_2c = *(float *)(param_1 + 0xa24);
    dVar4 = (double)*(float *)(param_1 + 0xa34);
    local_24 = *(undefined4 *)(param_1 + 0xa44);
    local_28 = FLOAT_8043b348;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    iVar1 = FUN_800452a0(dVar4,dVar5);
    local_2c = *(float *)(param_1 + 0xa30);
    local_28 = *(float *)(param_1 + 0xa40);
    local_24 = *(undefined4 *)(param_1 + 0xa50);
    local_38 = *(float *)(param_1 + 0x518);
    local_34 = *(float *)(param_1 + 0x51c);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_38);
    dVar5 = (double)local_34;
    local_34 = FLOAT_8043b348;
    dVar4 = gnt4_PSVECMag_bl(&local_38);
    iVar2 = FUN_800452a0(dVar5,dVar4);
    *(short *)(param_1 + 0x1900) = (short)iVar1 + (short)iVar2;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                (float *)(param_1 + 0x1628));
  }
  uVar3 = 0x38;
  if (*(char *)(param_1 + 0x1b04) != '\0') {
    uVar3 = 0x39;
  }
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,uVar3);
  }
  return;
}



// ==== 80199490  FUN_80199490 ====

void FUN_80199490(int param_1)

{
  zz_01994b0_(param_1);
  return;
}



// ==== 801994b0  zz_01994b0_ ====

void zz_01994b0_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  (*(code *)(&PTR_FUN_8036fb48)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80199504  FUN_80199504 ====

void FUN_80199504(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  fVar1 = FLOAT_8043b348;
  *(float *)(param_1 + 0x50) = FLOAT_8043b348;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b350,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043b330,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b348;
  return;
}



// ==== 80199608  FUN_80199608 ====

/* WARNING: Removing unreachable block (ram,0x8019986c) */
/* WARNING: Removing unreachable block (ram,0x80199618) */

void FUN_80199608(int param_1)

{
  char *pcVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_38;
  float local_34;
  undefined4 local_30;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043b350,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  fVar3 = FLOAT_8043b358;
  fVar2 = FLOAT_8043b354;
  if ('\0' < *(char *)(param_1 + 0x1cf0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar4 = FLOAT_8043b35c;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar4;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if (*(short *)(param_1 + 1000) == 0x105) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        iVar5 = zz_00853ec_(param_1,0xb);
        local_38 = *(float *)(param_1 + 0xa24);
        dVar7 = (double)*(float *)(param_1 + 0xa34);
        local_30 = *(undefined4 *)(param_1 + 0xa44);
        local_34 = FLOAT_8043b348;
        dVar8 = gnt4_PSVECMag_bl(&local_38);
        iVar6 = FUN_800452a0(dVar7,dVar8);
        *(short *)(param_1 + 0x1900) = (short)iVar6 - (short)iVar5;
        iVar5 = zz_00853ec_(param_1,0xc);
        local_38 = *(float *)(param_1 + 0xae4);
        dVar8 = (double)*(float *)(param_1 + 0xaf4);
        local_30 = *(undefined4 *)(param_1 + 0xb04);
        local_34 = FLOAT_8043b348;
        dVar7 = gnt4_PSVECMag_bl(&local_38);
        iVar6 = FUN_800452a0(dVar8,dVar7);
        *(short *)(param_1 + 0x1918) = (short)iVar5 + (short)iVar6;
      }
      iVar5 = zz_006dbe0_(param_1,2,1,1);
      if (iVar5 != 0) {
        zz_0084600_(param_1,0xb);
        zz_0084600_(param_1,0xc);
      }
    }
    else if ((*(short *)(param_1 + 1000) == 0x10a) &&
            (iVar5 = zz_006dbe0_(param_1,0,1,1), iVar5 != 0)) {
      iVar5 = 0;
      iVar6 = 0;
      do {
        pcVar1 = (char *)(param_1 + iVar6 + 0x144);
        if (*pcVar1 == '\0') {
          *pcVar1 = '\x01';
          zz_00e0e90_(param_1,(char)iVar6 + '\x04',2,pcVar1);
          iVar5 = iVar5 + 1;
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < 2);
      if (iVar5 != 0) {
        zz_00f036c_(param_1,0xdb);
      }
    }
  }
  dVar7 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043b360 < dVar7) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80199894  FUN_80199894 ====

void FUN_80199894(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b338) * FLOAT_8043b364);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043b34c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
LAB_80199924:
    if (*(char *)(param_1 + 0x1cee) == '\0') goto LAB_80199998;
  }
  else if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_006ed8c_((double)FLOAT_8043b368,param_1);
    goto LAB_80199924;
  }
  *(undefined2 *)(param_1 + 0x1900) = 0;
  *(undefined2 *)(param_1 + 0x1918) = 0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(undefined1 *)(param_1 + 0x6e8) = 0;
  if (iVar1 == 0) {
    zz_006a5a4_(param_1);
  }
  else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a750_(param_1,7);
  }
  *(float *)(param_1 + 0x694) = FLOAT_8043b34c + *(float *)(param_1 + 0x1dc8);
LAB_80199998:
  if (FLOAT_8043b360 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801999c8  zz_01999c8_ ====

void zz_01999c8_(undefined1 param_1)

{
  int iVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  
  PTR_DAT_80433934[0x1653] = 0;
  zz_0199b60_(4,param_1);
  zz_0199b60_(0,0);
  zz_0199b60_(1,0);
  zz_0199b60_(2,0);
  zz_0199b60_(2,1);
  zz_0199b60_(2,2);
  zz_0199b60_(2,3);
  zz_0199b60_(2,4);
  zz_0199b60_(2,5);
  zz_0199b60_(2,6);
  zz_0199b60_(2,7);
  zz_0199b60_(2,8);
  zz_0199b60_(2,9);
  zz_0199b60_(2,10);
  zz_0199b60_(2,0xb);
  zz_0199b60_(2,0xc);
  zz_0199b60_(2,0xd);
  zz_0199b60_(2,0xe);
  zz_0199b60_(2,0xf);
  zz_0199b60_(2,0x10);
  zz_0199b60_(2,0x11);
  iVar2 = 0;
  cVar3 = '\0';
  do {
    iVar1 = 0;
    cVar4 = cVar3;
    do {
      zz_0199b60_(5,cVar4);
      iVar1 = iVar1 + 1;
      cVar4 = cVar4 + '\x01';
    } while (iVar1 < 6);
    iVar2 = iVar2 + 1;
    cVar3 = cVar3 + '\x06';
  } while (iVar2 < 6);
  zz_0199b60_(6,0);
  zz_00f03c0_(0,0x174);
  return;
}



// ==== 80199b60  zz_0199b60_ ====

void zz_0199b60_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_((int)(char)(&DAT_80370f31)[param_1 * 0x10],0x39,1,
                       (int)(char)(&DAT_80370f30)[param_1 * 0x10]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0;
    *(code **)(puVar1 + 0xc) = FUN_80199c0c;
    *(undefined **)(puVar1 + 0x10c) = (&PTR_FUN_80370f34)[param_1 * 4];
    puVar1[0x11] = (char)param_1;
    puVar1[0x12] = param_2;
    PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + '\x01';
  }
  return;
}



// ==== 80199c0c  FUN_80199c0c ====

void FUN_80199c0c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') && ('\x01' < (char)PTR_DAT_80433934[0x45])) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_80370fa8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80199c74  FUN_80199c74 ====

void FUN_80199c74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = *(char *)(param_9 + 0x11) * 0x10;
  pcVar2 = &DAT_80370f28 + iVar1;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < (char)(&DAT_80370f30)[iVar1]; iVar3 = iVar3 + 1) {
    if (-1 < *pcVar2) {
      param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            DAT_803bb384,*(int *)(iVar4 + 0xe0),(int)*pcVar2,param_12,param_13,
                            param_14,param_15,param_16);
    }
    iVar4 = iVar4 + 4;
    pcVar2 = pcVar2 + 1;
  }
  (*(code *)(&PTR_FUN_80370fb8)[*(char *)(param_9 + 0x11)])(param_9);
  return;
}



// ==== 80199d30  FUN_80199d30 ====

void FUN_80199d30(int param_1)

{
  (*(code *)(&PTR_FUN_80370fd8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80199d6c  FUN_80199d6c ====

void FUN_80199d6c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80199d80  FUN_80199d80 ====

void FUN_80199d80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80199da0  zz_0199da0_ ====

uint zz_0199da0_(void)

{
  return (5U - (int)(char)PTR_DAT_80433930[0x3e] | (int)(char)PTR_DAT_80433930[0x3e] - 5U) >> 0x1f;
}



// ==== 80199dc0  FUN_80199dc0 ====

void FUN_80199dc0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043b378;
  fVar2 = FLOAT_8043b374;
  fVar1 = FLOAT_8043b370;
  *(float *)(param_1 + 0x148) = FLOAT_8043b370;
  fVar4 = FLOAT_8043b37c;
  *(float *)(param_1 + 0x144) = fVar1;
  *(float *)(param_1 + 0x14c) = fVar2;
  *(float *)(param_1 + 0x164) = fVar3;
  *(float *)(param_1 + 0x160) = fVar3;
  *(float *)(param_1 + 0x15c) = fVar3;
  *(float *)(param_1 + 0x154) = fVar1;
  *(float *)(param_1 + 0x150) = fVar1;
  *(float *)(param_1 + 0x158) = fVar4;
  *(float *)(param_1 + 0x16c) = fVar1;
  *(float *)(param_1 + 0x168) = fVar1;
  *(float *)(param_1 + 0x170) = fVar3;
  *(float *)(param_1 + 0x174) = fVar1;
  zz_0007cac_((double)*(float *)(param_1 + 0x174),*(int *)(param_1 + 0xe0));
  *(undefined2 *)(param_1 + 0x1e) = 10;
  dVar5 = DOUBLE_8043b388;
  fVar1 = FLOAT_8043b384;
  *(float *)(param_1 + 0x3c) =
       FLOAT_8043b378 /
       ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
               DOUBLE_8043b388) * FLOAT_8043b380);
  *(float *)(param_1 + 0x40) =
       (fVar1 - *(float *)(param_1 + 0x14c)) /
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) - dVar5);
  *(undefined1 *)(param_1 + 0x82) = 0x11;
  return;
}



// ==== 80199ea8  FUN_80199ea8 ====

void FUN_80199ea8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  short sVar5;
  bool bVar6;
  
  fVar3 = FLOAT_8043b384;
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    sVar5 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar5;
    dVar4 = DOUBLE_8043b388;
    if (sVar5 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      fVar3 = FLOAT_8043b378;
      *(undefined2 *)(param_1 + 0x1e) = 10;
      *(float *)(param_1 + 0x38) =
           fVar3 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                          - dVar4);
      zz_00f03c0_(0,0x175);
    }
    fVar3 = FLOAT_8043b378;
    if ((*(ushort *)(param_1 + 0x1e) & 2) != 0) {
      fVar3 = FLOAT_8043b390;
    }
    *(float *)(param_1 + 0x15c) = fVar3;
    *(float *)(param_1 + 0x160) = fVar3;
    *(float *)(param_1 + 0x164) = fVar3;
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      fVar2 = *(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x40);
      bVar6 = fVar2 < FLOAT_8043b384;
      *(float *)(param_1 + 0x14c) = fVar2;
      if (bVar6) {
        *(float *)(param_1 + 0x14c) = fVar3;
      }
      fVar2 = FLOAT_8043b378;
      fVar3 = *(float *)(param_1 + 0x174) + *(float *)(param_1 + 0x3c);
      *(float *)(param_1 + 0x174) = fVar3;
      if (fVar2 <= fVar3) {
        *(float *)(param_1 + 0x174) = fVar2;
      }
      sVar5 = *(short *)(param_1 + 0x1e) + -1;
      *(short *)(param_1 + 0x1e) = sVar5;
      fVar2 = FLOAT_8043b384;
      fVar3 = FLOAT_8043b378;
      if (sVar5 < 1) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(float *)(param_1 + 0x14c) = fVar2;
        *(float *)(param_1 + 0x174) = fVar3;
        *(undefined2 *)(param_1 + 0x1e) = 10;
      }
    }
  }
  else if (cVar1 < '\x03') {
    *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) + *(float *)(param_1 + 0x38);
    *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + *(float *)(param_1 + 0x38);
    sVar5 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar5;
    fVar3 = FLOAT_8043b378;
    if (sVar5 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(float *)(param_1 + 0x168) = fVar3;
      *(float *)(param_1 + 0x16c) = fVar3;
      *(float *)(param_1 + 0x170) = fVar3;
      PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
    }
  }
  return;
}



// ==== 8019a064  FUN_8019a064 ====

void FUN_8019a064(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar3 = zz_0007834_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        (undefined4 *)(param_9 + 0x144),param_11,param_12,param_13,param_14,param_15
                        ,param_16);
    zz_0007ae4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (undefined4 *)(param_9 + 0x15c),param_11,param_12,param_13,param_14,param_15,
                param_16);
    zz_0007cac_((double)*(float *)(param_9 + 0x174),iVar2);
    uVar3 = zz_0009958_(iVar2,0);
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar3 = zz_0007834_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        (undefined4 *)(param_9 + 0x150),param_11,param_12,param_13,param_14,param_15
                        ,param_16);
    zz_0007ae4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (undefined4 *)(param_9 + 0x168),param_11,param_12,param_13,param_14,param_15,
                param_16);
    zz_0009958_(iVar2,1);
  }
  return;
}



// ==== 8019a108  FUN_8019a108 ====

void FUN_8019a108(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  float fVar3;
  double dVar4;
  float fVar5;
  undefined4 extraout_r4;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  if ((PTR_DAT_80433930[0x32] == '\0') || (PTR_DAT_80433930[0x40] != '\0')) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  }
  else {
    *(undefined1 *)(param_9 + 0x13) = 0;
    iVar2 = DAT_803bb384;
    iVar7 = *(short *)(PTR_DAT_80433934 + 0x46) + 1;
    if (99 < iVar7) {
      iVar7 = 99;
    }
    bVar1 = false;
    iVar8 = param_9;
    for (uVar6 = 10; fVar3 = FLOAT_8043b398, uVar6 != 0; uVar6 = uVar6 / 10) {
      if (((!bVar1) && (iVar7 / (int)uVar6 != 0)) || (uVar6 == 1)) {
        bVar1 = true;
      }
      if (bVar1) {
        uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                             iVar7 / (int)uVar6 ^ 0x80000000) -
                                           DOUBLE_8043b388),param_2,param_3,param_4,param_5,param_6,
                            param_7,param_8,iVar2,*(int *)(iVar8 + 0xe4),param_11,param_12,param_13,
                            param_14,param_15,param_16);
        zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar8 + 0xe4),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                    param_16);
        *(char *)(param_9 + 0x13) = *(char *)(param_9 + 0x13) + '\x01';
      }
      else {
        *(undefined1 *)(*(int *)(iVar8 + 0xe4) + 0x10) = 0;
      }
      iVar8 = iVar8 + 4;
      iVar7 = iVar7 - (iVar7 / (int)uVar6) * uVar6;
    }
    *(float *)(param_9 + 100) = FLOAT_8043b394;
    fVar5 = FLOAT_8043b39c;
    *(float *)(param_9 + 0x68) = fVar3;
    fVar3 = FLOAT_8043b384;
    *(float *)(param_9 + 0x6c) = fVar5;
    dVar4 = DOUBLE_8043b388;
    *(undefined2 *)(param_9 + 0x1e) = 0xf;
    *(float *)(param_9 + 0x40) =
         (fVar3 - *(float *)(param_9 + 0x6c)) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1e) ^ 0x80000000) - dVar4);
    *(undefined1 *)(param_9 + 0x84) = 1;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x82) = 0x11;
  }
  return;
}



// ==== 8019a330  FUN_8019a330 ====

void FUN_8019a330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  undefined8 uVar7;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  float local_24;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    iVar4 = *(int *)(param_9 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0009958_(iVar4,1);
    iVar3 = 0;
    local_28 = FLOAT_8043b3a0;
    pfVar6 = (float *)&DAT_80435718;
    local_24 = FLOAT_8043b3a4;
    iVar4 = param_9;
    do {
      iVar5 = *(int *)(iVar4 + 0xe4);
      if (*(char *)(iVar5 + 0x10) != '\0') {
        local_2c = *pfVar6;
        pfVar2 = afStack_38;
        uVar7 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),&local_2c,pfVar2);
        zz_0007834_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_38,
                    (char *)pfVar2,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar5,1);
      }
      iVar3 = iVar3 + 1;
      pfVar6 = pfVar6 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 < 2);
  }
  return;
}



// ==== 8019a3f0  FUN_8019a3f0 ====

void FUN_8019a3f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  int iVar7;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 *puVar8;
  float *pfVar9;
  int iVar10;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar11;
  undefined8 uVar12;
  
  cVar1 = *(char *)(param_9 + 0x12);
  iVar10 = (int)cVar1;
  *(char *)(param_9 + 0x96) =
       cVar1 + ((char)((ulonglong)((longlong)iVar10 * 0x2aaaaaab) >> 0x20) -
               ((char)((char)(iVar10 / 0x6000000) + (cVar1 >> 7)) >> 7)) * -6;
  cVar1 = *(char *)(param_9 + 0x12);
  *(char *)(param_9 + 0x12) =
       (char)((ulonglong)((longlong)(int)cVar1 * 0x2aaaaaab) >> 0x20) -
       ((char)((char)((int)cVar1 / 0x6000000) + (cVar1 >> 7)) >> 7);
  *(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb];
  uVar6 = 1 << (int)*(char *)(param_9 + 0x96);
  if ((((byte)PTR_DAT_80433934[0x15d9] & uVar6) == 0) ||
     ((((PTR_DAT_80433930[0x32] == '\0' && (*(char *)(param_9 + 0x12) == '\0')) &&
       (((int)(char)PTR_DAT_80433930[2] & uVar6) != 0)) && (iVar7 = zz_0181c70_(), iVar7 == 0)))) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  }
  else {
    iVar7 = zz_019bf18_(param_9);
    *(char *)(param_9 + 0x13) = (char)iVar7;
    fVar2 = FLOAT_8043b370;
    iVar7 = DAT_803bb384;
    *(float *)(param_9 + 0x44) = FLOAT_8043b370;
    *(float *)(param_9 + 0x40) = fVar2;
    *(float *)(param_9 + 0x3c) = fVar2;
    cVar1 = *(char *)(param_9 + 0x12);
    if (cVar1 == '\x01') {
      if (PTR_DAT_80433930[0x32] == '\0') {
        uVar6 = (uint)(char)PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0x20];
        if (((int)uVar6 < 1) || (0xd < (int)uVar6)) {
          *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 0;
        }
        else {
          pfVar9 = (float *)0x1a;
          zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,
                      *(int *)(param_9 + 0xe0),0x1a,iVar10,in_r7,in_r8,in_r9,in_r10);
          uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) -
                                              DOUBLE_8043b388),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,iVar7,*(int *)(param_9 + 0xe0),pfVar9,iVar10,
                               in_r7,in_r8,in_r9,in_r10);
          zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4_01,pfVar9,iVar10,in_r7,in_r8,in_r9,in_r10
                     );
          fVar4 = FLOAT_8043b3b0;
          *(float *)(param_9 + 0x44) = FLOAT_8043b3ac;
          fVar2 = FLOAT_8043b378;
          *(float *)(param_9 + 0x3c) = fVar4;
          *(float *)(param_9 + 0x40) = fVar2;
        }
      }
      else {
        iVar11 = 0xf;
        if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) != 0) {
          iVar11 = *(char *)(param_9 + 0x96) + 4;
        }
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,
                    *(int *)(param_9 + 0xe0),iVar11,iVar10,in_r7,in_r8,in_r9,in_r10);
      }
      *(float *)(param_9 + 0x38) = FLOAT_8043b3b4;
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(undefined2 *)(param_9 + 0x70) = 0;
        pfVar9 = (float *)0xe;
        iVar11 = *(int *)(param_9 + 0xe0);
        zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar11,0xe
                    ,iVar10,in_r7,in_r8,in_r9,in_r10);
        uVar6 = zz_0005630_();
        uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar6 & 7 ^ 0x80000000) -
                                            DOUBLE_8043b388),param_2,param_3,param_4,param_5,param_6
                             ,param_7,param_8,iVar7,iVar11,pfVar9,iVar10,in_r7,in_r8,in_r9,in_r10);
        zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,
                    extraout_r4,pfVar9,iVar10,in_r7,in_r8,in_r9,in_r10);
        uVar5 = 0xff;
        uVar12 = zz_0007cd0_(iVar11,0xff,0xff,0xff);
        iVar10 = *(int *)(param_9 + 0xe4);
        pfVar9 = (float *)0xe;
        zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar10,0xe,
                    uVar5,in_r7,in_r8,in_r9,in_r10);
        uVar6 = zz_0005630_();
        uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar6 & 7 ^ 0x80000000) -
                                            DOUBLE_8043b388),param_2,param_3,param_4,param_5,param_6
                             ,param_7,param_8,iVar7,iVar10,pfVar9,uVar5,in_r7,in_r8,in_r9,in_r10);
        zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                    extraout_r4_00,pfVar9,uVar5,in_r7,in_r8,in_r9,in_r10);
        zz_0007cd0_(iVar10,0,0,0);
        *(float *)(param_9 + 0x38) = FLOAT_8043b3a8;
      }
    }
    else if (cVar1 < '\x03') {
      iVar10 = (int)((int)*(char *)(param_9 + 0x88) - 1U | 1U - (int)*(char *)(param_9 + 0x88)) >>
               0x1f;
      iVar11 = iVar10 + 0x17;
      if ((PTR_DAT_80433930[0x32] == '\0') &&
         (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0)) {
        iVar11 = iVar10 + 0x19;
      }
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,
                  *(int *)(param_9 + 0xe0),iVar11,PTR_DAT_80433930,in_r7,in_r8,in_r9,in_r10);
      *(float *)(param_9 + 0x38) = FLOAT_8043b3a8;
    }
    if (*(char *)(param_9 + 0x88) == '\x01') {
      *(float *)(param_9 + 0x38) = -*(float *)(param_9 + 0x38);
      *(float *)(param_9 + 0x44) = -*(float *)(param_9 + 0x44);
    }
    dVar3 = DOUBLE_8043b388;
    *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0x40);
    *(undefined2 *)(param_9 + 0x1c) = 0xf;
    *(float *)(param_9 + 0x4c) =
         *(float *)(param_9 + 0x38) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) - dVar3);
    if (PTR_DAT_80433930[0x32] == '\0') {
      iVar10 = ((int)*(char *)(param_9 + 0x13) + *(char *)(param_9 + 0x88) * 3) * 0xc;
      uVar5 = *(undefined4 *)(&DAT_803710d4 + iVar10);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803710d0 + iVar10);
      *(undefined4 *)(param_9 + 0x68) = uVar5;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803710d8 + iVar10);
      cVar1 = *(char *)(param_9 + 0x12);
      if (cVar1 == '\x01') {
        *(float *)(param_9 + 0x6c) = FLOAT_8043b3b8;
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(float *)(param_9 + 0x6c) = FLOAT_8043b37c;
        }
      }
      else if (cVar1 < '\x03') {
        *(float *)(param_9 + 0x6c) = FLOAT_8043b3bc;
      }
    }
    else {
      puVar8 = (undefined4 *)
               (*(char *)(param_9 + 0x12) * 0x48 + -0x7fc8f008 +
               ((int)*(char *)(param_9 + 0x13) + *(char *)(param_9 + 0x88) * 3) * 0xc);
      uVar5 = puVar8[1];
      *(undefined4 *)(param_9 + 100) = *puVar8;
      *(undefined4 *)(param_9 + 0x68) = uVar5;
      *(undefined4 *)(param_9 + 0x6c) = puVar8[2];
    }
    *(undefined1 *)(param_9 + 0x84) = 1;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    *(undefined1 *)(param_9 + 0x82) = 0x11;
  }
  return;
}



// ==== 8019a8f0  FUN_8019a8f0 ====

/* WARNING: Removing unreachable block (ram,0x8019ac00) */
/* WARNING: Removing unreachable block (ram,0x8019a900) */

void FUN_8019a8f0(int param_1,undefined4 param_2,float *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  short sVar4;
  ushort uVar5;
  uint uVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double local_30;
  double local_28;
  
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) - *(float *)(param_1 + 0x4c);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x44);
      PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
      if (*(char *)(param_1 + 0x12) == '\0') {
        uVar5 = zz_0005630_();
        *(ushort *)(param_1 + 0x1c) = (uVar5 & 7) << 3;
        *(undefined2 *)(param_1 + 0x1e) = 0x78;
        *(short *)(param_1 + 0x7c) = (short)(0x10000 / (int)*(short *)(param_1 + 0x1e));
      }
    }
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x40);
  }
  else if (*(char *)(param_1 + 0x12) == '\0') {
    if (*(short *)(param_1 + 0x1c) < 1) {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(param_1 + 0x7c);
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        uVar2 = zz_0005630_();
        *(float *)(param_1 + 0x58) =
             FLOAT_8043b3c8 *
             (float)((double)CONCAT44(0x43300000,(uVar2 & 0x1f) + 1 ^ 0x80000000) - DOUBLE_8043b388)
             * FLOAT_8043b3c0 + FLOAT_8043b3c4;
        uVar2 = zz_0005630_();
        local_30 = (double)(CONCAT44(0x43300000,(uVar2 & 0x1f) + 1) ^ 0x80000000);
        dVar8 = (double)(float)(local_30 - DOUBLE_8043b388);
        dVar7 = (double)(float)(dVar8 * (double)FLOAT_8043b3c0);
        *(float *)(param_1 + 0x5c) =
             (float)((double)FLOAT_8043b3d0 * dVar7 + (double)FLOAT_8043b3cc);
        *(undefined2 *)(param_1 + 0x1e) = 0x78;
        *(undefined2 *)(param_1 + 0x70) = 0;
        uVar3 = zz_0005630_();
        local_28 = (double)(CONCAT44(0x43300000,uVar3) & 0xffffffff00000007 ^ 0x80000000);
        uVar6 = zz_00086b8_((double)(float)(local_28 - DOUBLE_8043b388),dVar7,dVar8,in_f4,in_f5,
                            in_f6,in_f7,in_f8,DAT_803bb384,*(int *)(param_1 + 0xe4),param_3,param_4,
                            param_5,param_6,param_7,param_8);
        zz_0007c30_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),
                    extraout_r4,param_3,param_4,param_5,param_6,param_7,param_8);
      }
      else if (*(short *)(param_1 + 0x1e) == 0x3c) {
        uVar2 = zz_0005630_();
        local_28 = (double)(CONCAT44(0x43300000,(uVar2 & 0x1f) + 1) ^ 0x80000000);
        *(float *)(param_1 + 0x38) =
             FLOAT_8043b3c8 * (float)(local_28 - DOUBLE_8043b388) * FLOAT_8043b3c0 + FLOAT_8043b3c4;
        uVar2 = zz_0005630_();
        local_30 = (double)(CONCAT44(0x43300000,(uVar2 & 0x1f) + 1) ^ 0x80000000);
        dVar8 = (double)(float)(local_30 - DOUBLE_8043b388);
        dVar7 = (double)(float)(dVar8 * (double)FLOAT_8043b3c0);
        *(float *)(param_1 + 0x3c) =
             (float)((double)FLOAT_8043b3d0 * dVar7 + (double)FLOAT_8043b3cc);
        *(undefined2 *)(param_1 + 0x70) = 0x8000;
        uVar2 = zz_0005630_();
        uVar6 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar2 & 7 ^ 0x80000000) -
                                           DOUBLE_8043b388),dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,
                            in_f8,DAT_803bb384,*(int *)(param_1 + 0xe0),param_3,param_4,param_5,
                            param_6,param_7,param_8);
        zz_0007c30_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                    extraout_r4_00,param_3,param_4,param_5,param_6,param_7,param_8);
      }
      dVar7 = zz_0045238_(*(short *)(param_1 + 0x70));
      dVar7 = (double)(float)((double)FLOAT_8043b380 * dVar7 + (double)FLOAT_8043b380);
      iVar1 = (int)((double)FLOAT_8043b3d4 * dVar7);
      zz_0007cd0_(*(int *)(param_1 + 0xe0),iVar1,iVar1,iVar1);
      iVar1 = (int)(FLOAT_8043b3d4 * (float)((double)FLOAT_8043b378 - dVar7));
      zz_0007cd0_(*(int *)(param_1 + 0xe4),iVar1,iVar1,iVar1);
    }
    else {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    }
  }
  return;
}



// ==== 8019ac1c  FUN_8019ac1c ====

void FUN_8019ac1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  size_t sVar2;
  float *pfVar3;
  int iVar4;
  undefined8 uVar5;
  float local_38;
  float local_34;
  undefined4 local_28;
  uint uStack_24;
  longlong local_20;
  longlong local_18;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    if (*(char *)(param_9 + 0x12) == '\0') {
      if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) != 0) {
        iVar4 = *(int *)(param_9 + 0xe0);
        pfVar3 = &local_38;
        uVar5 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)(param_9 + 0x38),pfVar3);
        zz_0007834_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_38,
                    (char *)pfVar3,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar4,1);
        iVar4 = *(int *)(param_9 + 0xe4);
        pfVar3 = &local_38;
        uVar5 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)(param_9 + 0x58),pfVar3);
        zz_0007834_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_38,
                    (char *)pfVar3,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar4,1);
        if (*(char *)(param_9 + 0x19) == '\0') {
          zz_0005744_((float *)0x0,&local_38,&local_38);
        }
        else {
          zz_0005744_((float *)0x0,(float *)(param_9 + 0x20),&local_38);
        }
        sVar2 = strlen(PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 0x29 + 0x1654);
        uStack_24 = sVar2 >> 1 ^ 0x80000000;
        local_28 = 0x43300000;
        local_34 = local_34 - FLOAT_8043b3dc;
        local_38 = -(FLOAT_8043b3d8 *
                     (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043b388) *
                     FLOAT_8043b380 - local_38);
        zz_0096d14_((double)FLOAT_8043b3e0);
        local_20 = (longlong)(int)local_38;
        local_18 = (longlong)(int)local_34;
        zz_0097144_((short)(int)local_38,(short)(int)local_34,*(char *)(param_9 + 0x88) + 2,
                    PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 0x29 + 0x1654);
      }
    }
    else {
      iVar4 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar4 + 0x10) != '\0') {
        pfVar3 = &local_38;
        uVar5 = gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)(param_9 + 0x38),pfVar3);
        zz_0007834_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_38,
                    (char *)pfVar3,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar4,1);
      }
    }
  }
  return;
}



// ==== 8019ae00  FUN_8019ae00 ====

void FUN_8019ae00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  char cVar2;
  undefined *puVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar9;
  
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_9 + 0x12);
  *(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb];
  PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    if (*(char *)(param_9 + 0x88) == '\0') {
      uVar5 = 0;
      uVar6 = 0xff;
      uVar8 = 0x79;
    }
    else {
      uVar5 = 0xf0;
      uVar6 = 0x31;
      uVar8 = 0x2b;
    }
    uVar9 = zz_0007cd0_(*(int *)(param_9 + 0xe0),uVar5,uVar6,uVar8);
    iVar7 = 0xc;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) != 0) {
      iVar7 = *(char *)(param_9 + 0x96) + 8;
    }
    zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(param_9 + 0xe4),iVar7,uVar8,in_r7,in_r8,in_r9,in_r10);
    fVar4 = FLOAT_8043b370;
    puVar3 = PTR_DAT_80433934;
    if (PTR_DAT_80433930[0x32] == '\0') {
      cVar2 = *(char *)(param_9 + 0x96);
      uVar5 = *(undefined4 *)(PTR_DAT_80433934 + cVar2 * 0xc + 0x1608);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(PTR_DAT_80433934 + cVar2 * 0xc + 0x1604);
      *(undefined4 *)(param_9 + 0x68) = uVar5;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(puVar3 + cVar2 * 0xc + 0x160c);
    }
    else {
      iVar7 = (int)*(char *)(param_9 + 0x88);
      bVar1 = PTR_DAT_80433934[iVar7 * 0x3c + 0xff];
      PTR_DAT_80433934[iVar7 * 0x3c + 0xff] = bVar1 + 1;
      iVar7 = (iVar7 * 8 + (bVar1 & 3) * 2 + (char)PTR_DAT_80433934[0x1c] * 0x10) * 4;
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802ddf00 + iVar7);
      *(float *)(param_9 + 0x68) = fVar4;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802ddf04 + iVar7);
    }
    *(undefined1 *)(param_9 + 0x82) = 0x21;
  }
  return;
}



// ==== 8019afa8  FUN_8019afa8 ====

void FUN_8019afa8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  double dVar3;
  undefined8 uVar4;
  float fStack_18;
  float local_14;
  float local_10;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    pfVar2 = &fStack_18;
    zz_0005744_((float *)0x0,(float *)(param_9 + 100),pfVar2);
    dVar3 = (double)local_14;
    local_10 = FLOAT_8043b378;
    local_14 = (float)-dVar3;
    zz_0007834_(-dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),&fStack_18,(char *)pfVar2,param_12,param_13,param_14,
                param_15,param_16);
    uVar4 = zz_0009958_(*(int *)(param_9 + 0xe0),1);
    zz_0007834_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),&fStack_18,(char *)pfVar2,param_12,param_13,param_14,
                param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe4),1);
  }
  return;
}



// ==== 8019b030  FUN_8019b030 ====

void FUN_8019b030(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  
  fVar2 = FLOAT_8043b3e4;
  fVar1 = FLOAT_8043b370;
  dVar4 = (double)FLOAT_8043b370;
  *(undefined1 *)(param_9 + 0x82) = 0x12;
  iVar3 = *(char *)(param_9 + 0x12) * 0x3c;
  *(short *)(param_9 + 0x1c) = (short)iVar3;
  *(float *)(param_9 + 0x44) = fVar1;
  *(float *)(param_9 + 0x4c) = fVar2;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x80) = 0x80;
  *(undefined2 *)(param_9 + 0x7e) = 0xa0;
  zz_019b094_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x80,
              (float *)0x0,iVar3,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 8019b094  zz_019b094_ ====

void zz_019b094_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  uint uVar3;
  bool bVar4;
  undefined8 uVar5;
  
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -1;
  uVar5 = zz_00086b8_((double)*(float *)(param_9 + 0x44),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe4),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00086b8_((double)*(float *)(param_9 + 0x44),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe8),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8)
              ,extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  fVar2 = FLOAT_8043b3e8;
  fVar1 = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c);
  bVar4 = FLOAT_8043b3e8 < fVar1;
  *(float *)(param_9 + 0x44) = fVar1;
  if (bVar4) {
    *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x44) - fVar2;
  }
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + *(short *)(param_9 + 0x80);
  *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7e);
  if (*(char *)(param_9 + 0x19) == '\0') {
    uVar3 = 0;
    if ((PTR_DAT_80433930[2] & 1) != 0) {
      uVar3 = DAT_803c7204;
    }
    if ((PTR_DAT_80433930[2] & 2) != 0) {
      uVar3 = uVar3 | DAT_803c7224;
    }
    if ((PTR_DAT_80433930[2] & 4) != 0) {
      uVar3 = uVar3 | DAT_803c7244;
    }
    if ((PTR_DAT_80433930[2] & 8) != 0) {
      uVar3 = uVar3 | DAT_803c7264;
    }
    if ((*(short *)(param_9 + 0x1c) < 1) || ((uVar3 & 0x1f70) != 0)) {
      PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    }
  }
  return;
}



// ==== 8019b228  FUN_8019b228 ====

void FUN_8019b228(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  double dVar3;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  local_24 = FLOAT_8043b370;
  local_28 = FLOAT_8043b370;
  local_2c = FLOAT_8043b370;
  local_30 = FLOAT_8043b370;
  local_34 = FLOAT_8043b370;
  local_38 = FLOAT_8043b370;
  iVar1 = *(int *)(param_9 + 0xe0);
  local_20 = FLOAT_8043b3ec;
  zz_0007834_((double)FLOAT_8043b370,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              &local_28,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar2 = zz_0009958_(iVar1,1);
  iVar1 = *(int *)(param_9 + 0xe4);
  local_20 = FLOAT_8043b3f0;
  zz_0007834_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_28,param_11
              ,param_12,param_13,param_14,param_15,param_16);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar3 = (double)FLOAT_8043b3f4;
  local_30 = (float)(dVar3 * (double)(float)((double)CONCAT44(0x43300000,uStack_14) -
                                            DOUBLE_8043b388));
  zz_0007988_(DOUBLE_8043b388,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_38,
              param_11,param_12,param_13,param_14,param_15,param_16);
  uVar2 = zz_0009958_(iVar1,1);
  iVar1 = *(int *)(param_9 + 0xe8);
  local_20 = FLOAT_8043b3f0;
  zz_0007834_(uVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_28,param_11,
              param_12,param_13,param_14,param_15,param_16);
  local_10 = 0x43300000;
  uStack_c = 0x10000U - (int)*(short *)(param_9 + 0x72) ^ 0x80000000;
  local_30 = (float)((double)FLOAT_8043b3f4 *
                    (double)(float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_8043b388));
  zz_0007988_(DOUBLE_8043b388,(double)FLOAT_8043b3f4,param_3,param_4,param_5,param_6,param_7,param_8
              ,iVar1,&local_38,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0009958_(iVar1,1);
  return;
}



// ==== 8019b358  FUN_8019b358 ====

void FUN_8019b358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  undefined *puVar9;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  cVar1 = *(char *)(param_9 + 0x12);
  *(char *)(param_9 + 0x96) =
       (char)((ulonglong)((longlong)(int)cVar1 * 0x2aaaaaab) >> 0x20) -
       ((char)((char)((int)cVar1 / 0x6000000) + (cVar1 >> 7)) >> 7);
  puVar9 = PTR_DAT_80433934;
  if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) != 0) {
    *(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x96) + 0xcb];
    cVar1 = *(char *)(param_9 + 0x12);
    *(char *)(param_9 + 0x12) =
         cVar1 + ((char)((ulonglong)((longlong)(int)cVar1 * 0x2aaaaaab) >> 0x20) -
                 ((char)((char)((int)cVar1 / 0x6000000) + (cVar1 >> 7)) >> 7)) * -6;
    iVar6 = zz_019bf18_(param_9);
    *(char *)(param_9 + 0x13) = (char)iVar6;
    *(undefined1 *)(param_9 + 0x1b) = 0;
    iVar10 = (int)*(char *)(param_9 + 0x96);
    iVar12 = 0;
    iVar13 = *(char *)(param_9 + 0x12) * 0x8c;
    iVar6 = param_9;
    for (iVar11 = *(char *)(param_9 + 0x12) * 5;
        (iVar12 < 5 && (iVar11 < (char)PTR_DAT_80433934[iVar10 + 0x5a])); iVar11 = iVar11 + 1) {
      pcVar8 = PTR_DAT_80433934 + iVar10 * 0x348 + iVar13 + 0x1e8;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb334,
                  *(int *)(iVar6 + 0xe0),
                  *(int *)((&PTR_DAT_80350d0c)[*pcVar8] + (uint)(byte)pcVar8[1] * 4),pcVar8,puVar9,
                  in_r8,in_r9,in_r10);
      param_1 = zz_0007d68_(*(int *)(iVar6 + 0xe0),-1);
      iVar6 = iVar6 + 4;
      iVar12 = iVar12 + 1;
      iVar13 = iVar13 + 0x1c;
      *(char *)(param_9 + 0x1b) = *(char *)(param_9 + 0x1b) + '\x01';
    }
    if ((PTR_DAT_80433930[0x32] == '\0') && (((int)(char)PTR_DAT_80433930[2] & 1 << iVar10) == 0)) {
      if (*(char *)(param_9 + 0x12) == '\0') {
        *(undefined1 *)(param_9 + 0x1b) = 1;
      }
      else {
        *(undefined1 *)(param_9 + 0x1b) = 0;
      }
      *(float *)(param_9 + 0x44) = FLOAT_8043b370;
    }
    else {
      if ((char)PTR_DAT_80433934[iVar10 + 0x5a] < 6) {
        uVar7 = (int)(char)PTR_DAT_80433934[iVar10 + 0x5a] - 1;
        if ((int)uVar7 < 0) {
          uVar7 = 0;
        }
        *(float *)(param_9 + 0x44) =
             FLOAT_8043b3f8 *
             (float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) - DOUBLE_8043b388) *
             FLOAT_8043b380;
      }
      else {
        *(float *)(param_9 + 0x44) = FLOAT_8043b3fc;
      }
      *(float *)(param_9 + 0x44) =
           FLOAT_8043b400 *
           (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12) ^ 0x80000000) -
                  DOUBLE_8043b388) + *(float *)(param_9 + 0x44);
    }
    *(undefined2 *)(param_9 + 0x1c) = 0xf;
    dVar3 = DOUBLE_8043b388;
    *(float *)(param_9 + 0x38) = FLOAT_8043b3a8;
    *(float *)(param_9 + 0x4c) =
         *(float *)(param_9 + 0x38) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000) - dVar3);
    *(undefined1 *)(param_9 + 0x84) = 0x11;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0x20,1);
    if (PTR_DAT_80433930[0x32] == '\0') {
      iVar6 = ((int)*(char *)(param_9 + 0x13) + *(char *)(param_9 + 0x88) * 3) * 0xc;
      uVar5 = *(undefined4 *)(&DAT_8037117c + iVar6);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80371178 + iVar6);
      *(undefined4 *)(param_9 + 0x68) = uVar5;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80371180 + iVar6);
    }
    else {
      iVar6 = ((int)*(char *)(param_9 + 0x13) + *(char *)(param_9 + 0x88) * 3) * 0xc;
      uVar5 = *(undefined4 *)(&DAT_80371134 + iVar6);
      *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80371130 + iVar6);
      *(undefined4 *)(param_9 + 0x68) = uVar5;
      *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80371138 + iVar6);
    }
    fVar4 = FLOAT_8043b404;
    fVar2 = FLOAT_8043b378;
    *(float *)(param_9 + 0x5c) = FLOAT_8043b404;
    *(float *)(param_9 + 0x58) = fVar4;
    *(float *)(param_9 + 0x60) = fVar2;
    *(undefined1 *)(param_9 + 0x82) = 0x11;
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  return;
}



// ==== 8019b718  FUN_8019b718 ====

/* WARNING: Removing unreachable block (ram,0x8019b87c) */
/* WARNING: Removing unreachable block (ram,0x8019b874) */
/* WARNING: Removing unreachable block (ram,0x8019b86c) */
/* WARNING: Removing unreachable block (ram,0x8019b864) */
/* WARNING: Removing unreachable block (ram,0x8019b85c) */
/* WARNING: Removing unreachable block (ram,0x8019b748) */
/* WARNING: Removing unreachable block (ram,0x8019b740) */
/* WARNING: Removing unreachable block (ram,0x8019b738) */
/* WARNING: Removing unreachable block (ram,0x8019b730) */
/* WARNING: Removing unreachable block (ram,0x8019b728) */

void FUN_8019b718(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  double dVar4;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float afStack_a8 [3];
  float local_9c;
  float local_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    dVar5 = (double)FLOAT_8043b408;
    dVar8 = (double)(*(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x38));
    if ((*(byte *)(param_1 + 0x88) & 1) != 0) {
      dVar8 = -dVar8;
      dVar5 = -dVar5;
    }
    local_78 = 0x43300000;
    uStack_74 = (int)*(char *)(param_1 + 0x12) ^ 0x80000000;
    local_70 = 0x43300000;
    dVar6 = (double)(FLOAT_8043b3cc *
                    (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8043b388));
    iVar3 = param_1;
    dVar4 = (double)(FLOAT_8043b40c *
                    (float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8043b388));
    dVar9 = DOUBLE_8043b388;
    uStack_6c = uStack_74;
    for (uVar1 = 0; (int)uVar1 < (int)*(char *)(param_1 + 0x1b); uVar1 = uVar1 + 1) {
      dVar7 = dVar4;
      gnt4_PSMTXTrans_bl(dVar8,dVar4,dVar6,afStack_a8);
      pfVar2 = afStack_a8;
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
      uStack_6c = uVar1 ^ 0x80000000;
      local_70 = 0x43300000;
      local_9c = (float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uStack_6c) - dVar9) +
                        (double)local_9c);
      zz_00076d0_((double)local_9c,dVar4,(double)local_7c,in_f4,in_f5,in_f6,in_f7,in_f8,
                  *(int *)(iVar3 + 0xe0),afStack_a8,(undefined *)pfVar2,param_4,param_5,param_6,
                  param_7,param_8);
      zz_0009958_(*(int *)(iVar3 + 0xe0),1);
      iVar3 = iVar3 + 4;
      dVar4 = dVar7;
    }
  }
  return;
}



// ==== 8019b8a4  FUN_8019b8a4 ====

void FUN_8019b8a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar4;
  uint uVar3;
  int iVar5;
  double dVar6;
  
  PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  *(undefined1 *)(param_9 + 0x18) = 1;
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(undefined1 *)(param_9 + 0x84) = 0x19;
    fVar2 = FLOAT_8043b410;
    *(undefined2 *)(param_9 + 0x74) = 0;
    fVar1 = FLOAT_8043b378;
    iVar5 = 0x15;
    *(undefined2 *)(param_9 + 0x80) = 0x444;
    *(float *)(param_9 + 0x58) = fVar2;
    *(float *)(param_9 + 0x5c) = fVar2;
    *(float *)(param_9 + 0x60) = fVar1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 8;
    *(undefined1 *)(param_9 + 0x82) = 0x12;
  }
  else {
    iVar5 = 0x14;
    *(undefined1 *)(param_9 + 0x84) = 0x1b;
    sVar4 = zz_0005630_();
    *(short *)(param_9 + 0x70) = sVar4 << 0xb;
    uVar3 = zz_0005630_();
    fVar2 = FLOAT_8043b378;
    fVar1 = FLOAT_8043b370;
    *(short *)(param_9 + 0x74) =
         (short)(*(int *)(PTR_DAT_80433934 + 0xa8) + (uVar3 & 0xffff)) * 0x800;
    *(float *)(param_9 + 0x58) = fVar2;
    *(float *)(param_9 + 0x5c) = fVar2;
    *(float *)(param_9 + 0x60) = fVar2;
    *(float *)(param_9 + 0xd4) = fVar1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    FUN_8019bb34(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0x12;
  }
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar2 = FLOAT_8043b414;
  fVar1 = FLOAT_8043b370;
  dVar6 = (double)FLOAT_8043b370;
  *(float *)(param_9 + 100) = FLOAT_8043b370;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar2;
  zz_0006fb4_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),iVar5,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8019b9ec  FUN_8019b9ec ====

void FUN_8019b9ec(int param_1)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  short sVar4;
  
  fVar1 = FLOAT_8043b3c8;
  if (*(char *)(param_1 + 0x12) == '\0') {
    uVar3 = *(short *)(param_1 + 0x1c) + 1;
    *(ushort *)(param_1 + 0x1c) = uVar3;
    fVar2 = FLOAT_8043b410;
    fVar1 = FLOAT_8043b378;
    if ((uVar3 & 2) == 0) {
      *(float *)(param_1 + 0x5c) = FLOAT_8043b378;
      *(float *)(param_1 + 0x58) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x5c) = FLOAT_8043b410;
      *(float *)(param_1 + 0x58) = fVar2;
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
    sVar4 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar4;
    if (sVar4 < 1) {
      *(short *)(param_1 + 0x1e) = (short)DAT_80435720;
      zz_0199b60_(6,1);
    }
    zz_0199b60_(7,0);
    zz_0199b60_(7,0);
    zz_0199b60_(7,0);
    zz_0199b60_(7,0);
  }
  else {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) + FLOAT_80435724;
    if (*(float *)(param_1 + 0xd4) <= fVar1) {
      FUN_8019bb34(param_1);
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return;
}



// ==== 8019bae8  FUN_8019bae8 ====

void FUN_8019bae8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0009958_(*(int *)(param_9 + 0xe0),1);
  }
  return;
}



// ==== 8019bb34  FUN_8019bb34 ====

void FUN_8019bb34(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  float *pfVar4;
  uint uVar5;
  float *pfVar6;
  
  pfVar4 = (float *)&DAT_803711d8;
LAB_8019bbcc:
  do {
    pfVar6 = (float *)0x0;
    if (*(float *)(param_1 + 0xd4) < *pfVar4) {
LAB_8019bbe0:
      if (pfVar6 == (float *)0x0) {
        pfVar6 = pfVar4 + -5;
      }
      fVar1 = *pfVar4 - *pfVar6;
      fVar2 = *(float *)(param_1 + 0xd4) - *pfVar6;
      *(float *)(param_1 + 0x58) = fVar2 * ((pfVar4[1] - pfVar6[1]) / fVar1) + pfVar6[1];
      *(float *)(param_1 + 0x5c) = fVar2 * ((pfVar4[2] - pfVar6[2]) / fVar1) + pfVar6[2];
      *(float *)(param_1 + 0x60) = fVar2 * ((pfVar4[3] - pfVar6[3]) / fVar1) + pfVar6[3];
      return;
    }
    if (((uint)pfVar4[4] & 0xf0000000) != 0) {
      uVar3 = (uint)pfVar4[4] & 0xff;
      pfVar6 = pfVar4;
      if (uVar3 == 0) {
        *(float *)(param_1 + 0xd4) = *pfVar4;
        goto LAB_8019bbe0;
      }
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
      uVar5 = (uint)pfVar4[4] >> 8 & 0xff;
      if ((uVar5 != 0) && ((int)uVar5 <= (int)*(short *)(param_1 + 0x1c))) {
        *(float *)(param_1 + 0xd4) = *pfVar4;
        goto LAB_8019bbe0;
      }
      fVar1 = *pfVar4;
      pfVar4 = pfVar4 + uVar3 * -5;
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - fVar1;
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) + *pfVar4;
      goto LAB_8019bbcc;
    }
    pfVar4 = pfVar4 + 5;
  } while( true );
}



// ==== 8019bc4c  FUN_8019bc4c ====

/* WARNING: Removing unreachable block (ram,0x8019bda0) */
/* WARNING: Removing unreachable block (ram,0x8019bd98) */
/* WARNING: Removing unreachable block (ram,0x8019bc64) */
/* WARNING: Removing unreachable block (ram,0x8019bc5c) */

void FUN_8019bc4c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar5;
  uint uVar4;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  fVar2 = FLOAT_8043b418;
  fVar1 = FLOAT_8043b370;
  PTR_DAT_80433934[0x1653] = PTR_DAT_80433934[0x1653] + -1;
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar2;
  sVar5 = zz_0005630_();
  uVar4 = zz_0005630_();
  dVar8 = (double)(FLOAT_8043b3c8 *
                   (float)((double)CONCAT44(0x43300000,uVar4 & 8 ^ 0x80000000) - DOUBLE_8043b388) +
                  FLOAT_8043b41c);
  uVar4 = zz_0005630_();
  dVar7 = (double)(float)((double)CONCAT44(0x43300000,
                                           (int)*(short *)(&DAT_80371250 + (uVar4 & 7) * 2) ^
                                           0x80000000) - DOUBLE_8043b388);
  dVar6 = zz_0045238_(sVar5 << 9);
  dVar9 = (double)(float)(dVar8 / dVar7);
  *(float *)(param_1 + 0x38) = (float)(dVar9 * dVar6);
  dVar8 = zz_0045204_(sVar5 << 9);
  fVar3 = FLOAT_8043b420;
  fVar2 = FLOAT_8043b3e4;
  dVar6 = (double)FLOAT_8043b424;
  *(float *)(param_1 + 0x3c) = (float)(dVar9 * dVar8);
  fVar1 = FLOAT_8043b378;
  *(float *)(param_1 + 0x40) = -(float)((double)*(float *)(param_1 + 0x6c) / dVar7);
  *(float *)(param_1 + 0x44) = (float)((double)(fVar3 * *(float *)(param_1 + 0x38)) / dVar7);
  *(float *)(param_1 + 0x48) = (float)((double)(fVar3 * *(float *)(param_1 + 0x3c)) / dVar7);
  *(undefined2 *)(param_1 + 0x70) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(float *)(param_1 + 0x58) = fVar2;
  *(float *)(param_1 + 0x5c) = (float)(dVar6 / dVar7);
  *(float *)(param_1 + 0x60) = fVar1;
  *(undefined1 *)(param_1 + 0x82) = 0x12;
  return;
}



// ==== 8019be30  FUN_8019be30 ====

void FUN_8019be30(int param_1)

{
  uint uVar1;
  bool bVar3;
  float *pfVar2;
  float *pfVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_88 [3];
  float local_7c;
  float local_78;
  float local_74;
  float afStack_70 [12];
  float afStack_40 [15];
  
  uVar1 = zz_0199da0_();
  if (uVar1 == 0) {
    local_74 = FLOAT_8043b370;
    local_78 = FLOAT_8043b370;
    local_7c = FLOAT_8043b370;
    gnt4_PSVECSubtract_bl(&local_7c,(float *)(param_1 + 100),afStack_88);
    pfVar4 = afStack_88;
    bVar3 = zz_0045ef4_((float *)(param_1 + 0x114),3,param_1 + 0x38,pfVar4);
    if (!bVar3) {
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 100);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x68);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x6c);
      dVar6 = (double)*(float *)(param_1 + 0x5c);
      dVar7 = (double)*(float *)(param_1 + 0x60);
      gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),dVar6,dVar7,afStack_40);
      pfVar2 = (float *)(param_1 + 0x114);
      uVar5 = gnt4_PSMTXConcat_bl(pfVar2,afStack_40,pfVar2);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                  (float *)(param_1 + 0x114),(undefined *)pfVar2,pfVar4,in_r7,in_r8,in_r9,in_r10);
      zz_0009958_(*(int *)(param_1 + 0xe0),1);
      dVar6 = (double)FLOAT_8043b41c;
      gnt4_PSMTXScale_bl(dVar6,dVar6,dVar6,afStack_70);
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_70,afStack_70);
    }
  }
  return;
}



// ==== 8019bf18  zz_019bf18_ ====

int zz_019bf18_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  
  cVar1 = *(char *)(param_1 + 0x96);
  iVar3 = (char)PTR_DAT_80433934[cVar1 + 0xcb] * 0x3c;
  if (PTR_DAT_80433930[0x32] != '\0') {
    iVar4 = 0;
    iVar2 = (int)(char)PTR_DAT_80433934[iVar3 + 0xf5];
    if (iVar2 < 1) {
      return 0;
    }
    do {
      if ((int)(char)PTR_DAT_80433934[iVar4 + 4 + iVar3 + 0xf4] == (int)cVar1) {
        return (int)(char)iVar4;
      }
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    return 0;
  }
  cVar5 = '\0';
  while( true ) {
    if (('\x05' < cVar5) || (((int)(char)PTR_DAT_80433930[2] & 1 << (int)cVar5) != 0)) break;
    cVar5 = cVar5 + '\x01';
  }
  if (cVar5 == cVar1) {
    return 0;
  }
  iVar4 = 0;
  iVar6 = 0;
  iVar2 = (int)(char)PTR_DAT_80433934[iVar3 + 0xf5];
  if (0 < iVar2) {
    do {
      if (PTR_DAT_80433934[iVar6 + 4 + iVar3 + 0xf4] != cVar5) {
        if (PTR_DAT_80433934[iVar6 + 4 + iVar3 + 0xf4] == cVar1) break;
        iVar4 = iVar4 + 1;
      }
      iVar6 = iVar6 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if (PTR_DAT_80433934[iVar3 + 0xf6] == '\0') {
    return iVar4;
  }
  return iVar4 + 1;
}



// ==== 8019c128  FUN_8019c128 ====

void FUN_8019c128(int param_1)

{
  *(undefined1 *)(param_1 + 0x582) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  zz_004e00c_(param_1,2);
  return;
}



// ==== 8019c1d0  FUN_8019c1d0 ====

void FUN_8019c1d0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803712a0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8019c210  FUN_8019c210 ====

void FUN_8019c210(int param_1,int param_2)

{
  if ('\b' < *(char *)(param_1 + 0x3ee)) {
    zz_0099e70_(param_1,(&DAT_80435728)[param_2]);
  }
  return;
}



// ==== 8019c24c  FUN_8019c24c ====

void FUN_8019c24c(int param_1)

{
  zz_0137540_(param_1,4);
  return;
}



// ==== 8019c270  FUN_8019c270 ====

void FUN_8019c270(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x39);
  return;
}



// ==== 8019c2a8  FUN_8019c2a8 ====

void FUN_8019c2a8(int param_1)

{
  (*(code *)(&PTR_FUN_803712b4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019c2e4  FUN_8019c2e4 ====

void FUN_8019c2e4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_803712c4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019c338  FUN_8019c338 ====

void FUN_8019c338(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 8019c35c  FUN_8019c35c ====

void FUN_8019c35c(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 8019c47c  FUN_8019c47c ====

void FUN_8019c47c(int param_1)

{
  zz_00c74ec_(param_1,7);
  return;
}



// ==== 8019c4a0  FUN_8019c4a0 ====

void FUN_8019c4a0(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}



// ==== 8019c4d4  FUN_8019c4d4 ====

void FUN_8019c4d4(int param_1)

{
  (*(code *)(&PTR_FUN_80372108)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019c60c  FUN_8019c60c ====

uint FUN_8019c60c(uint param_1)

{
  float fVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = param_1;
  if (*(short *)(param_1 + 1000) == 0x70b) {
    zz_00c627c_(param_1,3,param_1 + 0x168);
    bVar3 = zz_01fcc50_(param_1,3,param_1 + 0x150,param_1 + 0x169);
    uVar2 = (uint)bVar3;
    if ('\b' < *(char *)(param_1 + 0x3ee)) {
      bVar3 = zz_01fcc50_(param_1,3,param_1 + 0x15c,param_1 + 0x16a);
      uVar2 = (uint)bVar3;
    }
  }
  fVar1 = FLOAT_8043b428;
  *(undefined1 *)(param_1 + 0x168) = 1;
  *(undefined1 *)(param_1 + 0x169) = 1;
  *(undefined1 *)(param_1 + 0x16a) = 1;
  *(undefined1 *)(param_1 + 0x16b) = 1;
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x154) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x20);
  *(float *)(param_1 + 0x160) = fVar1 + *(float *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x28);
  return uVar2;
}



// ==== 8019c6d4  FUN_8019c6d4 ====

void FUN_8019c6d4(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x705) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
    *(undefined1 *)(param_1 + 0x748) = 2;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043b430) * FLOAT_8043b42c);
  }
  return;
}



// ==== 8019c744  FUN_8019c744 ====

/* WARNING: Removing unreachable block (ram,0x8019c810) */
/* WARNING: Removing unreachable block (ram,0x8019c754) */

void FUN_8019c744(int param_1)

{
  float *pfVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float afStack_2c [3];
  
  if (*(short *)(param_1 + 1000) == 0x70b) {
    local_38 = *(float *)(param_1 + 0xb20);
    dVar6 = (double)FLOAT_8043b438;
    iVar4 = 0;
    local_34 = *(undefined4 *)(param_1 + 0xb30);
    local_30 = *(undefined4 *)(param_1 + 0xb40);
    pfVar1 = (float *)(param_1 + 0x150);
    pfVar3 = &local_38;
    do {
      pfVar2 = pfVar1;
      gnt4_PSVECSubtract_bl(pfVar2,pfVar3,afStack_2c);
      dVar5 = gnt4_PSVECMag_bl(afStack_2c);
      if ((double)(float)(dVar6 * (double)*(float *)(param_1 + 0xb4)) < dVar5) {
        zz_006ebb4_(afStack_2c,afStack_2c);
        gnt4_PSQUATScale_bl((double)(FLOAT_8043b438 * *(float *)(param_1 + 0xb4)),afStack_2c,
                            afStack_2c);
        gnt4_PSVECAdd_bl(afStack_2c,pfVar3,pfVar2);
      }
      iVar4 = iVar4 + 1;
      pfVar1 = pfVar2 + 3;
      pfVar3 = pfVar2;
    } while (iVar4 < 2);
  }
  return;
}



// ==== 8019c848  FUN_8019c848 ====

void FUN_8019c848(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803737a0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8019c888  FUN_8019c888 ====

void FUN_8019c888(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x705) {
    zz_001ab6c_(param_1,0x3b);
  }
  else if (*(short *)(param_1 + 1000) == 0x70b) {
    zz_001ab6c_(param_1,0x77);
  }
  return;
}



// ==== 8019c8d4  FUN_8019c8d4 ====

void FUN_8019c8d4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x705) {
    zz_001ab6c_(param_1,0x3a);
  }
  else if (*(short *)(param_1 + 1000) == 0x70b) {
    zz_001ab6c_(param_1,0x76);
  }
  return;
}



// ==== 8019c920  FUN_8019c920 ====

void FUN_8019c920(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x705) {
    zz_001ab6c_(param_1,0x3b);
    zz_001ab6c_(param_1,0x3a);
  }
  else if (*(short *)(param_1 + 1000) == 0x70b) {
    zz_001ab6c_(param_1,0x77);
    zz_001ab6c_(param_1,0x76);
  }
  return;
}



// ==== 8019c99c  FUN_8019c99c ====

uint FUN_8019c99c(uint param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = param_1;
  if ((*(short *)(param_1 + 1000) == 0x70b) &&
     (iVar1 = zz_006dbe0_(param_1,0,1,1), uVar2 = 0, iVar1 != 0)) {
    bVar3 = zz_00fbc64_(param_1,7);
    uVar2 = (uint)bVar3;
    *(byte *)(param_1 + 0x168) = *(byte *)(param_1 + 0x168) | 0x80;
    *(byte *)(param_1 + 0x169) = *(byte *)(param_1 + 0x169) | 0x80;
    *(byte *)(param_1 + 0x16a) = *(byte *)(param_1 + 0x16a) | 0x80;
    *(byte *)(param_1 + 0x16b) = *(byte *)(param_1 + 0x16b) | 0x80;
  }
  return uVar2;
}



// ==== 8019ca28  FUN_8019ca28 ====

void FUN_8019ca28(int param_1)

{
  (*(code *)(&PTR_FUN_803737bc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8019ca64  FUN_8019ca64 ====

void FUN_8019ca64(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043b430) * FLOAT_8043b42c);
  (*(code *)(&PTR_FUN_803737c8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019cad8  FUN_8019cad8 ====

void FUN_8019cad8(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 8019cb00  FUN_8019cb00 ====

void FUN_8019cb00(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 8019cb28  FUN_8019cb28 ====

void FUN_8019cb28(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 8019cb50  FUN_8019cb50 ====

void FUN_8019cb50(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8037381c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8019cba0  FUN_8019cba0 ====

void FUN_8019cba0(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043b43c;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043b440,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8019cc5c  FUN_8019cc5c ====

void FUN_8019cc5c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b444;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043b448;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_8043b44c;
    fVar2 = FLOAT_8043b444;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043b448;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 8019cd50  FUN_8019cd50 ====

void FUN_8019cd50(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043b450,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b444;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043b44c,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_8043b440;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,7,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019ce04  FUN_8019ce04 ====

void FUN_8019ce04(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043b454,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b45c;
  fVar1 = FLOAT_8043b458;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  return;
}



// ==== 8019ce80  FUN_8019ce80 ====

void FUN_8019ce80(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043b450,param_1);
  FUN_80067310((double)FLOAT_8043b460,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    dVar2 = (double)FLOAT_8043b440;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8019cf08  FUN_8019cf08 ====

void FUN_8019cf08(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043b450,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8019cf78  FUN_8019cf78 ====

void FUN_8019cf78(int param_1)

{
  (*(code *)(&PTR_FUN_80373834)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8019cfb4  FUN_8019cfb4 ====

void FUN_8019cfb4(int param_1)

{
  zz_0149708_(param_1);
  return;
}



