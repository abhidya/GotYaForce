// ==== 801fae24  FUN_801fae24 ====

void FUN_801fae24(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_803a2adc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801fae74  FUN_801fae74 ====

void FUN_801fae74(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  int iVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 in_r10;
  int iVar11;
  undefined8 uVar12;
  double dVar13;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  uint uStack_14;
  
  local_28 = DAT_802b4478;
  puVar9 = &DAT_803a2ac8;
  local_24 = DAT_802b447c;
  local_20 = DAT_802b4480;
  iVar11 = *(int *)(param_9 + 0x90);
  iVar10 = (int)*(char *)(param_9 + 0x11);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar7 = iVar10 * 0x14;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(code **)(param_9 + 0x100) = FUN_800480f4;
  iVar8 = iVar7;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  gnt4_PSMTXMultVec_bl((float *)(iVar11 + 0x904),&local_28,(float *)(param_9 + 0x20));
  dVar13 = (double)FLOAT_8043c8b0;
  *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x20);
  fVar2 = FLOAT_8043c8b4;
  *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x164) = *(undefined4 *)(param_9 + 0x28);
  *(float *)(param_9 + 0x154) = (float)(dVar13 * (double)*(float *)(param_9 + 0xb4));
  *(float *)(param_9 + 0x158) = *(float *)(param_9 + 0x154) / fVar2;
  uVar1 = *(undefined4 *)(param_9 + 0x158);
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  *(undefined2 *)(param_9 + 0x168) = 0;
  iVar5 = zz_008ac80_(param_9,(int)(char)(&DAT_803a2aca)[iVar7]);
  if (iVar5 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 300;
    fVar2 = FLOAT_8043c8b8;
    *(undefined2 *)(param_9 + 0x1e) = 0x1e;
    fVar3 = FLOAT_8043c8bc;
    *(float *)(param_9 + 0x144) = fVar2;
    dVar4 = DOUBLE_8043c8c0;
    iVar5 = param_9 + 0x14c;
    *(float *)(param_9 + 0x148) = fVar3;
    local_18 = 0x43300000;
    uStack_14 = (int)*(char *)(param_9 + 0x88) << 1 ^ 0x80000000;
    *(float *)(param_9 + 0x150) = (float)((double)CONCAT44(0x43300000,uStack_14) - dVar4);
    *(undefined1 *)(param_9 + 0x14c) = 0;
    *(undefined1 *)(param_9 + 0x14d) = 0;
    *(undefined1 *)(param_9 + 0x14e) = 0;
    *(undefined1 *)(param_9 + 0x14f) = 0;
    pfVar6 = (float *)(uint)*(ushort *)(&DAT_803a2ac8 + iVar7);
    zz_0007030_(dVar4,dVar13,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(int)pfVar6,iVar5,iVar8,puVar9,iVar10,in_r10);
    uVar12 = zz_00086b8_((double)(*(float *)(param_9 + 0x144) + *(float *)(param_9 + 0x150)),dVar13,
                         param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                         *(int *)(param_9 + 0xe0),pfVar6,iVar5,iVar8,puVar9,iVar10,in_r10);
    uVar12 = zz_0007c30_(uVar12,dVar13,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xe0),extraout_r4,pfVar6,iVar5,iVar8,puVar9,iVar10,
                         in_r10);
    zz_0007d40_(uVar12,dVar13,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar6,iVar5,iVar8,puVar9,iVar10,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(iVar11,(int)*(short *)(&DAT_803a2ada + iVar7));
  }
  return;
}



// ==== 801fb060  FUN_801fb060 ====

/* WARNING: Removing unreachable block (ram,0x801fb2a8) */
/* WARNING: Removing unreachable block (ram,0x801fb070) */

void FUN_801fb060(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar4;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar5;
  double dVar6;
  double in_f31;
  
  fVar2 = *(float *)(param_9 + 0x60) + *(float *)(param_9 + 0x158);
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  if (*(float *)(param_9 + 0x154) < *(float *)(param_9 + 0x58)) {
    *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x154);
    *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0x154);
    *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0x154);
  }
  sVar4 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar4;
  fVar2 = FLOAT_8043c8b8;
  if (sVar4 < 1) {
    *(undefined2 *)(param_9 + 0x1e) = 0x1e;
    if (*(float *)(param_9 + 0x148) <= fVar2) {
      *(float *)(param_9 + 0x144) = fVar2;
    }
    else {
      *(float *)(param_9 + 0x144) = FLOAT_8043c8c8;
    }
    *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) * FLOAT_8043c8cc;
  }
  else {
    *(float *)(param_9 + 0x144) = *(float *)(param_9 + 0x144) + *(float *)(param_9 + 0x148);
  }
  uVar5 = zz_00086b8_((double)(*(float *)(param_9 + 0x144) + *(float *)(param_9 + 0x150)),param_2,
                      param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                     );
  uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007d40_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x16a) == '\x01') {
    *(short *)(param_9 + 0x168) = *(short *)(param_9 + 0x168) + 0x200;
    dVar6 = zz_0045204_(*(short *)(param_9 + 0x168));
    *(float *)(param_9 + 0x24) =
         (float)((double)FLOAT_8043c8d0 * dVar6 + (double)*(float *)(param_9 + 0x160));
    in_f31 = (double)(*(float *)(param_9 + 0x24) - *(float *)(param_9 + 0x160));
  }
  iVar3 = zz_0083714_(param_9);
  if (iVar3 != 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    return;
  }
  if (*(char *)(param_9 + 0x16a) == '\x01') {
    dVar6 = (double)(*(float *)(param_9 + 0x24) - *(float *)(param_9 + 0x160));
    if (in_f31 != dVar6) {
      *(float *)(param_9 + 0x160) = *(float *)(param_9 + 0x160) - (float)(in_f31 - dVar6);
    }
  }
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    *(undefined2 *)(param_9 + 0x1c) = 0x19;
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      if ((*(byte *)(param_9 + 0x1d9) & 0x10) != 0) {
        *(undefined1 *)(param_9 + 0x19) = 1;
        return;
      }
      sVar4 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar4;
      if (0 < sVar4) {
        return;
      }
      *(undefined1 *)(param_9 + 0x19) = 1;
      return;
    }
    if ('\x02' < cVar1) {
      return;
    }
  }
  sVar4 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar4;
  if (sVar4 < 1) {
    zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),0x1a);
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
  }
  else {
    *(char *)(param_9 + 0x14c) = *(char *)(param_9 + 0x14c) + '(';
    *(char *)(param_9 + 0x14d) = *(char *)(param_9 + 0x14d) + '(';
    *(char *)(param_9 + 0x14e) = *(char *)(param_9 + 0x14e) + '(';
  }
  return;
}



// ==== 801fb2c4  FUN_801fb2c4 ====

void FUN_801fb2c4(int param_1)

{
  zz_006de10_(*(int *)(param_1 + 0x90),0);
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801fb310  FUN_801fb310 ====

void FUN_801fb310(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fb330  FUN_801fb330 ====

/* WARNING: Removing unreachable block (ram,0x801fb344) */

void FUN_801fb330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c8d4 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x45);
  return;
}



// ==== 801fb398  zz_01fb398_ ====

void zz_01fb398_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x65;
    *(code **)(puVar1 + 0xc) = FUN_801fb494;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    *(undefined2 *)(puVar1 + 0x1c6) = 1;
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



// ==== 801fb494  FUN_801fb494 ====

void FUN_801fb494(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(iVar2 + 0x18) || (*(short *)(iVar2 + 1000) != *(short *)(param_1 + 0x94)))
     )) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_803a2bb0)[*(char *)(param_1 + 0x18)])(param_1);
  uVar1 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  *(undefined4 *)(iVar2 + *(char *)(param_1 + 0x89) * 0xc + 0x15d4) =
       *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(iVar2 + *(char *)(param_1 + 0x89) * 0xc + 0x15d8) =
       *(undefined4 *)(param_1 + 0x5c);
  *(undefined4 *)(iVar2 + *(char *)(param_1 + 0x89) * 0xc + 0x15dc) =
       *(undefined4 *)(param_1 + 0x60);
  iVar2 = iVar2 + *(char *)(param_1 + 0x89) * 6;
  *(undefined4 *)(iVar2 + 0x18d4) = *(undefined4 *)(param_1 + 0x70);
  *(undefined2 *)(iVar2 + 0x18d8) = *(undefined2 *)(param_1 + 0x74);
  return;
}



// ==== 801fb59c  FUN_801fb59c ====

void FUN_801fb59c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar7 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x84) = 0x5f;
  iVar6 = *(char *)(param_1 + 0x11) * 0x18;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  fVar1 = FLOAT_8043c8d8;
  *(char *)(param_1 + 0x89) = (char)*(undefined2 *)(&DAT_803a2af2 + iVar6);
  fVar3 = FLOAT_8043c8e0;
  fVar2 = FLOAT_8043c8dc;
  uVar4 = *(undefined4 *)(&DAT_803a2b00 + iVar6);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803a2afc + iVar6);
  *(undefined4 *)(param_1 + 0x68) = uVar4;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803a2b04 + iVar6);
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(&DAT_803a2af8 + iVar6);
  *(undefined2 *)(param_1 + 0x15c) = *(undefined2 *)(&DAT_803a2af8 + iVar6);
  iVar5 = iVar7 + *(char *)(param_1 + 0x89) * 6;
  *(undefined4 *)(iVar5 + 0x18d4) = *(undefined4 *)(param_1 + 0x70);
  *(undefined2 *)(iVar5 + 0x18d8) = *(undefined2 *)(param_1 + 0x74);
  *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(&DAT_803a2af6 + iVar6);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
  *(float *)(param_1 + 0x204) = fVar1;
  *(undefined2 *)(param_1 + 0x15e) = *(undefined2 *)(&DAT_803a2afa + iVar6);
  *(uint *)(iVar7 + 0x76c) = *(uint *)(iVar7 + 0x76c) | 1 << (int)*(char *)(param_1 + 0x89);
  *(byte *)(iVar7 + 0x18e) = *(byte *)(iVar7 + 0x18e) | (byte)(1 << (int)*(char *)(param_1 + 0x11));
  *(int *)(iVar7 + *(char *)(param_1 + 0x11) * 4 + 0x144) = param_1;
  *(float *)(param_1 + 0xb4) = fVar2;
  *(float *)(param_1 + 0xb8) = fVar3;
  *(undefined2 *)(param_1 + 0x1c) = 0x78;
  iVar5 = zz_008ac80_(param_1,(int)*(short *)(&DAT_803a2af4 + iVar6));
  if (iVar5 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 801fb714  FUN_801fb714 ====

void FUN_801fb714(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((*(char *)(param_1 + 0x19) < '\x02') && (*(short *)(param_1 + 0x1c6) < 1)) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  (*(code *)(&PTR_FUN_803a2bc0)[*(char *)(param_1 + 0x19)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  if (*(float *)(param_1 + 0xb4) < *(float *)(param_1 + 0xb8)) {
    *(float *)(param_1 + 0xb4) =
         FLOAT_8043c8e4 * *(float *)(param_1 + 0xb4) + FLOAT_8043c8e8 * *(float *)(param_1 + 0xb8);
  }
  if (((uint)*(byte *)(iVar1 + 399) & 1 << (int)*(char *)(param_1 + 0x11)) == 0) {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x600;
  }
  else {
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 63999;
  }
  return;
}



// ==== 801fb7f8  FUN_801fb7f8 ====

void FUN_801fb7f8(int param_1,int param_2)

{
  char cVar1;
  double dVar2;
  short sVar3;
  bool bVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
LAB_801fb85c:
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (0 < sVar3) goto LAB_801fb8cc;
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (((cVar1 < '\0') || (*(char *)(param_2 + 0x18) != '\x01')) ||
         (*(char *)(param_2 + 0x19) < '\x02')) goto LAB_801fb8cc;
      *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
      goto LAB_801fb85c;
    }
    if ('\x02' < cVar1) goto LAB_801fb8cc;
  }
  if (((((uint)*(byte *)(param_2 + 399) & 1 << (int)*(char *)(param_1 + 0x11)) != 0) &&
      (PTR_DAT_80433934[0x1f] == '\0')) && (bVar4 = zz_01fbcd0_(param_1), bVar4)) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
LAB_801fb8cc:
  dVar2 = DOUBLE_8043c8f0;
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x100;
  *(short *)(param_1 + 0x70) =
       (short)(int)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70) ^ 0x80000000
                                            ) - dVar2) * FLOAT_8043c8ec);
  return;
}



// ==== 801fb924  FUN_801fb924 ====

void FUN_801fb924(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  int iVar5;
  double dVar6;
  float local_28;
  float local_24;
  float local_20;
  
  iVar5 = *(int *)(param_1 + 0xcc);
  if ('\x01' < *(char *)(iVar5 + 0x18)) {
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 0x78;
    *(undefined1 *)(param_1 + 0x160) = 0xff;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x1a) = 3;
    fVar2 = FLOAT_8043c8fc;
    *(undefined2 *)(param_1 + 0x1c) = 0x78;
    fVar3 = FLOAT_8043c900;
    *(float *)(param_1 + 0x40) = fVar2;
    *(float *)(param_1 + 0x44) = fVar3;
    *(undefined1 *)(param_1 + 0x160) = 1;
    zz_01deb68_(param_2,3,(float *)(param_1 + 0x144),param_1 + 0x150,param_1 + 0x160);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 0x78;
      }
      else if (cVar1 < '\0') {
        return;
      }
      if (*(char *)(iVar5 + 0x83) == '\0') {
        zz_006d228_(param_1,iVar5,0);
      }
      dVar6 = (double)FLOAT_8043c8f8;
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      iVar5 = zz_01fbf30_(dVar6,param_1,-0x7fbca3b8);
      if ((iVar5 == 0) && (0 < *(short *)(param_1 + 0x1c))) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      return;
    }
    if (cVar1 == '\x04') {
      sVar4 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar4;
      if (0 < sVar4) {
        return;
      }
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined2 *)(param_1 + 0x1c) = 4;
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  if (*(char *)(iVar5 + 0x83) == '\0') {
    zz_006d228_(param_1,iVar5,0x81);
  }
  zz_01fbf30_((double)FLOAT_8043c904,param_1,-0x7fbca3b8);
  local_28 = FLOAT_8043c8fc;
  local_24 = FLOAT_8043c8fc;
  local_20 = FLOAT_8043c908;
  gnt4_PSMTXMultVec_bl
            ((float *)(param_2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),&local_28,
             (float *)(param_1 + 0x144));
  fVar2 = FLOAT_8043c90c;
  *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x44);
  if (fVar2 < *(float *)(param_1 + 0x40)) {
    *(float *)(param_1 + 0x40) = fVar2;
  }
  local_20 = local_20 + *(float *)(param_1 + 0x40);
  gnt4_PSMTXMultVec_bl
            ((float *)(param_2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),&local_28,
             (float *)(param_1 + 0x150));
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if ((*(short *)(param_1 + 0x1c) < 1) ||
     (iVar5 = zz_01fbdd4_(param_1,*(int *)(param_1 + 0xcc)), iVar5 != 0)) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x78;
    *(undefined1 *)(param_1 + 0x160) = 0xff;
  }
  return;
}



// ==== 801fbba8  FUN_801fbba8 ====

void FUN_801fbba8(int param_1,int param_2)

{
  short sVar1;
  
  if (*(char *)(param_1 + 0x1a) == '\0') {
    *(undefined1 *)(param_1 + 0x1a) = 1;
    *(undefined2 *)(param_1 + 0x1c) = 0x1e;
    FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    *(uint *)(param_2 + 0x76c) = *(uint *)(param_2 + 0x76c) & ~(1 << (int)*(char *)(param_1 + 0x89))
    ;
    *(byte *)(param_2 + 0x18e) =
         *(byte *)(param_2 + 0x18e) & ~(byte)(1 << (int)*(char *)(param_1 + 0x11));
    *(undefined1 *)(param_1 + 0x160) = 0xff;
    zz_01d7340_(param_2);
  }
  else {
    sVar1 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar1;
    if (sVar1 < 1) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined4 *)(param_2 + *(char *)(param_1 + 0x11) * 4 + 0x144) = 0;
    }
  }
  return;
}



// ==== 801fbc88  FUN_801fbc88 ====

void FUN_801fbc88(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}



// ==== 801fbcb0  FUN_801fbcb0 ====

void FUN_801fbcb0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fbcd0  zz_01fbcd0_ ====

bool zz_01fbcd0_(int param_1)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int local_38 [8];
  
  puVar5 = &DAT_803c4e84;
  uVar7 = 0;
  iVar6 = 0;
  iVar4 = 0;
  do {
    pcVar3 = (char *)*puVar5;
    if ((((*pcVar3 != '\0') && (*(char *)(param_1 + 0x88) != pcVar3[0x88])) &&
        (pcVar3[0x88] != '\x04')) &&
       (((pcVar3[0x18] == '\x01' && (iVar1 = zz_01fbdd4_(param_1,(int)pcVar3), iVar1 == 0)) &&
        (((*(uint *)(pcVar3 + 0x5e0) & 0x1000000) == 0 &&
         (*(float *)(pcVar3 + 0x720) <= FLOAT_8043c8fc)))))) {
      uVar7 = uVar7 + 1;
      *(char **)((int)local_38 + iVar6) = pcVar3;
      iVar6 = iVar6 + 4;
    }
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 1;
  } while (iVar4 < 6);
  if (uVar7 != 0) {
    uVar2 = zz_00055fc_();
    iVar4 = local_38[uVar2 - (uVar2 / uVar7) * uVar7];
    *(int *)(param_1 + 0xcc) = iVar4;
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar4 + 0x530);
  }
  return uVar7 != 0;
}



// ==== 801fbdd4  zz_01fbdd4_ ====

undefined4 zz_01fbdd4_(int param_1,int param_2)

{
  undefined4 uVar1;
  float local_18 [2];
  float local_10;
  
  if (param_2 == 0) {
    uVar1 = 1;
  }
  else {
    if (*(char *)(param_1 + 0x11) < '\x04') {
      if (FLOAT_8043c910 + *(float *)(param_1 + 0x24) < *(float *)(param_2 + 0x24)) {
        return 1;
      }
    }
    else if (*(float *)(param_2 + 0x24) < *(float *)(param_1 + 0x24) - FLOAT_8043c910) {
      return 1;
    }
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0x20),(float *)(param_1 + 0x20),local_18);
    if (FLOAT_8043c914 < local_18[0] * local_18[0] + local_10 * local_10) {
      zz_00453fc_('y',local_18,local_18,
                  -(*(short *)(*(int *)(param_1 + 0x90) + 0x72) + *(short *)(param_1 + 0x15c)));
      if (('\x03' < *(char *)(param_1 + 0x11)) || (FLOAT_8043c918 <= local_10)) {
        if ((FLOAT_8043c910 <= local_18[0]) || (local_18[0] <= FLOAT_8043c91c)) {
          if ((FLOAT_8043c920 < local_10) || (local_10 < FLOAT_8043c924)) {
            uVar1 = 1;
          }
          else {
            uVar1 = 0;
          }
        }
        else {
          uVar1 = 1;
        }
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}



// ==== 801fbf30  zz_01fbf30_ ====

/* WARNING: Removing unreachable block (ram,0x801fc18c) */
/* WARNING: Removing unreachable block (ram,0x801fbf40) */

undefined4 zz_01fbf30_(double param_1,int param_2,int param_3)

{
  short sVar1;
  undefined4 uVar2;
  uint uVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  double local_38;
  undefined8 local_30;
  
  if (*(int *)(param_2 + 0xcc) == 0) {
    uVar2 = 1;
  }
  else {
    iVar5 = *(int *)(param_2 + 200);
    iVar6 = *(int *)(param_2 + 0x90);
    local_74 = *(float *)(iVar5 + 100);
    local_70 = *(float *)(iVar5 + 0x68);
    local_6c = *(float *)(iVar5 + 0x6c);
    local_68 = *(float *)(iVar6 + 0x994);
    local_58 = *(undefined4 *)(iVar6 + 0x9a4);
    local_48 = *(undefined4 *)(iVar6 + 0x9b4);
    local_64 = *(undefined4 *)(iVar6 + 0x998);
    local_54 = *(undefined4 *)(iVar6 + 0x9a8);
    local_44 = *(undefined4 *)(iVar6 + 0x9b8);
    local_60 = *(undefined4 *)(iVar6 + 0x99c);
    local_50 = *(undefined4 *)(iVar6 + 0x9ac);
    local_40 = *(undefined4 *)(iVar6 + 0x9bc);
    iVar6 = iVar6 + *(char *)(param_2 + 0x89) * 0x30;
    local_5c = *(undefined4 *)(iVar6 + 0x8e0);
    local_4c = *(undefined4 *)(iVar6 + 0x8f0);
    local_3c = *(undefined4 *)(iVar6 + 0x900);
    zz_004516c_(&local_68,&local_74,&local_74);
    dVar8 = (double)(local_74 * local_74 + local_6c * local_6c);
    if ((double)FLOAT_8043c8fc < dVar8) {
      dVar7 = 1.0 / SQRT(dVar8);
      dVar7 = DOUBLE_8043c928 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c930);
      dVar7 = DOUBLE_8043c928 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c930);
      dVar8 = (double)(float)(dVar8 * DOUBLE_8043c928 * dVar7 *
                                      -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c930));
    }
    iVar6 = FUN_800452a0((double)local_70,dVar8);
    sVar1 = -(short)iVar6;
    iVar6 = FUN_800452a0((double)local_74,(double)local_6c);
    dVar8 = DOUBLE_8043c8f0;
    if (sVar1 < 1) {
      if (sVar1 <= *(short *)(param_3 + 4)) {
        sVar1 = *(short *)(param_3 + 4);
      }
    }
    else if (*(short *)(param_3 + 6) <= sVar1) {
      sVar1 = *(short *)(param_3 + 6);
    }
    local_38 = (double)(CONCAT44(0x43300000,(int)sVar1 - (int)*(short *)(param_2 + 0x70)) ^
                       0x80000000);
    uVar3 = (int)(short)iVar6 - (int)*(short *)(param_2 + 0x72);
    if ((int)uVar3 < 0x8001) {
      if ((int)uVar3 < -0x8000) {
        uVar3 = uVar3 + 0x10000;
      }
    }
    else {
      uVar3 = uVar3 - 0x10000;
    }
    sVar4 = (short)(int)(param_1 * (double)(float)(local_38 - DOUBLE_8043c8f0));
    local_30 = (double)CONCAT44(0x43300000,uVar3 ^ 0x80000000);
    *(short *)(param_2 + 0x70) = *(short *)(param_2 + 0x70) + sVar4;
    sVar1 = (short)(int)((double)(float)(local_30 - dVar8) * param_1);
    *(short *)(param_2 + 0x72) = *(short *)(param_2 + 0x72) + sVar1;
    if ((sVar4 == 0) && (sVar1 == 0)) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}



// ==== 801fc1b0  zz_01fc1b0_ ====

void zz_01fc1b0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x10;
    *(code **)(puVar1 + 0xc) = FUN_801fc2a8;
    *(code **)(puVar1 + 0x10c) = FUN_801fcbb8;
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



// ==== 801fc2a8  FUN_801fc2a8 ====

void FUN_801fc2a8(int param_1)

{
  zz_0084000_(param_1);
  if ((*(int *)(param_1 + 0xcc) != 0) && ('\x01' < *(char *)(*(int *)(param_1 + 0xcc) + 0x18))) {
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined4 *)(param_1 + 200) = 0;
  }
  (*(code *)(&PTR_FUN_803a2f78)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801fc320  FUN_801fc320 ====

void FUN_801fc320(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  
  uVar5 = 0x803a0000;
  iVar8 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(char *)(param_9 + 0x11) * 0x24;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(code **)(param_9 + 0x100) = zz_01fcbf8_;
  iVar7 = iVar6;
  zz_0089100_(param_9,1,1);
  *(undefined *)(param_9 + 0x89) = (&DAT_803a2bd0)[iVar6];
  *(undefined1 *)(param_9 + 0x84) = 0x4f;
  uVar3 = *(undefined4 *)(&DAT_803a2bd8 + iVar6);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a2bd4 + iVar6);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a2bdc + iVar6);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803a2be0 + iVar6);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803a2be4 + iVar6);
  FUN_80047aa4(param_9);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x11c);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 300);
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x13c);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
  uVar3 = *(undefined4 *)(&DAT_803a2bec + iVar6);
  *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(&DAT_803a2be8 + iVar6);
  *(undefined4 *)(param_9 + 0x160) = uVar3;
  *(undefined4 *)(param_9 + 0x164) = *(undefined4 *)(&DAT_803a2bf0 + iVar6);
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x15c) * *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x160) * *(float *)(param_9 + 0xb4);
  *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x164) * *(float *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(param_9 + 0x58);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  uVar9 = zz_01fcbf8_(param_9);
  zz_00aedc0_(iVar8,(float *)(param_9 + 0x114),1,*(undefined1 *)(param_9 + 0x88));
  *(undefined1 *)(param_9 + 0x180) = 0;
  iVar6 = zz_008ac80_(param_9,(int)*(short *)(&DAT_803a2bd2 + iVar6));
  if (iVar6 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 300;
    zz_0006f98_(iVar8);
    zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x0,(int)*(char *)(param_9 + 0x88),uVar5,iVar7,
                in_r9,in_r10);
    bVar4 = zz_0045ef4_((float *)(param_9 + 0x114),5,param_9 + 0x38,&DAT_802b0cb4);
    if (bVar4) {
      zz_0045ef4_((float *)(param_9 + 0x114),4,param_9 + 0x38,&DAT_802b0ca8);
    }
    fVar1 = FLOAT_8043c93c;
    *(float *)(param_9 + 0x4c) = FLOAT_8043c938;
    fVar2 = FLOAT_8043c940;
    *(float *)(param_9 + 0x44) = fVar1;
    fVar1 = FLOAT_8043c944;
    *(float *)(param_9 + 0x178) = fVar2;
    dVar10 = (double)FLOAT_8043c948;
    *(float *)(param_9 + 0x174) = fVar2;
    fVar1 = (fVar2 - *(float *)(param_9 + 0x15c)) / fVar1;
    *(float *)(param_9 + 0x16c) = fVar1;
    *(float *)(param_9 + 0x168) = fVar1;
    *(undefined2 *)(param_9 + 0x1e) = 0xf;
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f061c_(dVar10,iVar8,0xb9);
  }
  return;
}



// ==== 801fc584  FUN_801fc584 ====

void FUN_801fc584(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  double dVar9;
  double dVar10;
  float afStack_2c [3];
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  float afStack_14 [3];
  
  uVar7 = (uint)*(char *)(param_1 + 0x1d9);
  if (uVar7 != 0) goto LAB_801fcb24;
  if (*(float *)(param_1 + 0x15c) < *(float *)(param_1 + 0x174)) {
    *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x15c) + *(float *)(param_1 + 0x168);
    *(float *)(param_1 + 0x160) = *(float *)(param_1 + 0x160) + *(float *)(param_1 + 0x16c);
    if (*(float *)(param_1 + 0x174) < *(float *)(param_1 + 0x15c)) {
      *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x174);
      *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x178);
    }
  }
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    sVar5 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar5;
    if (sVar5 < 1) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      sVar5 = *(short *)(param_1 + 0x1e) + -1;
      *(short *)(param_1 + 0x1e) = sVar5;
      fVar2 = FLOAT_8043c974;
      fVar3 = FLOAT_8043c94c;
      if (sVar5 < 1) {
        *(float *)(param_1 + 0x170) =
             (*(float *)(param_1 + 0x164) - FLOAT_8043c970) / FLOAT_8043c974;
        *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x44) / fVar2;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        goto LAB_801fc73c;
      }
      fVar2 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
      bVar8 = FLOAT_8043c94c < fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      if (bVar8) {
        *(float *)(param_1 + 0x44) = fVar3;
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),afStack_14);
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_14,(float *)(param_1 + 0x20));
      dVar9 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
      fVar3 = FLOAT_8043c96c;
      if ((double)FLOAT_8043c950 < dVar9) {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar9 = (double)(float)(dVar9 * DOUBLE_8043c958 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960));
      }
      *(float *)(param_1 + 0x164) = (float)(dVar9 / (double)FLOAT_8043c968);
      if (fVar3 < *(float *)(param_1 + 0x164)) {
        *(float *)(param_1 + 0x164) = fVar3;
      }
    }
    else if (-1 < cVar1) {
LAB_801fc73c:
      fVar2 = FLOAT_8043c950;
      fVar3 = *(float *)(param_1 + 0x44) - *(float *)(param_1 + 0x4c);
      bVar8 = fVar3 < FLOAT_8043c950;
      *(float *)(param_1 + 0x44) = fVar3;
      if (bVar8) {
        *(float *)(param_1 + 0x44) = fVar2;
      }
      if (FLOAT_8043c950 < *(float *)(param_1 + 0x44)) {
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),afStack_14)
        ;
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_14,(float *)(param_1 + 0x20));
      }
      fVar2 = FLOAT_8043c970;
      fVar3 = *(float *)(param_1 + 0x164) - *(float *)(param_1 + 0x170);
      bVar8 = fVar3 < FLOAT_8043c970;
      *(float *)(param_1 + 0x164) = fVar3;
      if (bVar8) {
        *(float *)(param_1 + 0x164) = fVar2;
        *(undefined2 *)(param_1 + 0x1e) = 5;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
  }
  else {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) goto LAB_801fca84;
      zz_0089444_(param_1);
      *(code **)(param_1 + 0x100) = zz_0048288_;
      zz_0089100_(param_1,0,1);
      *(undefined1 *)(param_1 + 0x98) = 5;
      fVar3 = FLOAT_8043c950;
      *(undefined1 *)(param_1 + 0x84) = 0x10;
      fVar2 = FLOAT_8043c978;
      *(float *)(param_1 + 0x9c) = fVar3;
      *(float *)(param_1 + 0xa0) = fVar2;
      *(float *)(param_1 + 0xa4) = fVar3;
      iVar6 = *(int *)(param_1 + 200);
      if (iVar6 == 0) {
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
        *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
        *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
      }
      else {
        local_20 = *(float *)(iVar6 + 100);
        local_1c = *(undefined4 *)(iVar6 + 0x68);
        local_18 = *(undefined4 *)(iVar6 + 0x6c);
        gnt4_PSVECSubtract_bl(&local_20,(float *)(param_1 + 0x20),afStack_2c);
        gnt4_PSVECNormalize_bl(afStack_2c,(float *)(param_1 + 0x38));
      }
      fVar3 = FLOAT_8043c97c;
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
      fVar2 = FLOAT_8043c980;
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
      *(float *)(param_1 + 0x4c) = fVar3;
      *(float *)(param_1 + 0x44) = fVar2 - *(float *)(param_1 + 0x4c);
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    fVar3 = FLOAT_8043c984;
    if (*(int *)(param_1 + 200) == 0) {
      if ((*(float *)(param_1 + 0x44) < FLOAT_8043c984) &&
         (fVar2 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c),
         bVar8 = FLOAT_8043c984 < fVar2, *(float *)(param_1 + 0x44) = fVar2, bVar8)) {
        *(float *)(param_1 + 0x44) = fVar3;
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20)
                      );
      dVar9 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
      fVar3 = FLOAT_8043c96c;
      if ((double)FLOAT_8043c950 < dVar9) {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar9 = (double)(float)(dVar9 * DOUBLE_8043c958 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960));
      }
      *(float *)(param_1 + 0x164) = (float)(dVar9 / (double)FLOAT_8043c968);
      if (fVar3 < *(float *)(param_1 + 0x164)) {
        *(float *)(param_1 + 0x164) = fVar3;
      }
    }
    else {
      if ((*(float *)(param_1 + 0x44) < FLOAT_8043c984) &&
         (fVar2 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c),
         bVar8 = FLOAT_8043c984 < fVar2, *(float *)(param_1 + 0x44) = fVar2, bVar8)) {
        *(float *)(param_1 + 0x44) = fVar3;
      }
      FUN_80083874((double)FLOAT_8043c988,param_1);
      FUN_80083ad4((double)FLOAT_8043c98c,param_1,4);
      dVar9 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
      fVar3 = FLOAT_8043c96c;
      if ((double)FLOAT_8043c950 < dVar9) {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar10 = DOUBLE_8043c958 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960);
        dVar9 = (double)(float)(dVar9 * DOUBLE_8043c958 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_8043c960));
      }
      *(float *)(param_1 + 0x164) = (float)(dVar9 / (double)FLOAT_8043c968);
      if (fVar3 < *(float *)(param_1 + 0x164)) {
        *(float *)(param_1 + 0x164) = fVar3;
      }
    }
  }
LAB_801fca84:
  zz_00833ec_(param_1);
  zz_0083610_(param_1,(float *)(param_1 + 0x48));
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x15c) * *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x160) * *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x164) * *(float *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0x58);
  uVar7 = zz_0084170_(param_1);
  uVar4 = zz_0083714_(param_1);
  uVar7 = uVar7 | uVar4;
  if (*(char *)(param_1 + 0x180) == '\x01') {
    uVar4 = zz_0083244_((float *)(param_1 + 0x20));
    uVar7 = uVar7 | uVar4;
  }
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  uVar4 = countLeadingZeros((int)sVar5);
  uVar7 = uVar7 | (1 << (uVar4 & 0x1f) | 1U >> 0x20 - (uVar4 & 0x1f)) & 1;
LAB_801fcb24:
  if (uVar7 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801fcb5c  FUN_801fcb5c ====

void FUN_801fcb5c(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801fcb98  FUN_801fcb98 ====

void FUN_801fcb98(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fcbb8  FUN_801fcbb8 ====

void FUN_801fcbb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801fcbf8  zz_01fcbf8_ ====

void zz_01fcbf8_(int param_1)

{
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00456f8_((float *)(param_1 + 0x114));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 801fcc50  zz_01fcc50_ ====

bool zz_01fcc50_(int param_1,undefined1 param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  bool bVar3;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0xa0a) || (sVar1 == 0xc)) || (sVar1 == 0xb07)) || (sVar1 == 0x70b)) {
    puVar2 = zz_0088aa0_(param_1,2,0,0,2);
    bVar3 = puVar2 != (undefined1 *)0x0;
    if (bVar3) {
      *puVar2 = 1;
      puVar2[0x13] = 0;
      puVar2[0x11] = param_2;
      *(code **)(puVar2 + 0xc) = FUN_801fcda8;
      *(code **)(puVar2 + 0x10c) = FUN_801fd09c;
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
      *(undefined4 *)(puVar2 + 0x144) = param_3;
      *(undefined4 *)(puVar2 + 0x148) = param_4;
    }
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}



// ==== 801fcda8  FUN_801fcda8 ====

void FUN_801fcda8(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a2f98)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801fcdfc  FUN_801fcdfc ====

void FUN_801fcdfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_9 + 0x90);
  iVar4 = (int)*(char *)(param_9 + 0x11);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar2 = iVar4 * 4;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043c990;
  *(undefined1 *)(param_9 + 0x84) = 0x54;
  *(undefined *)(param_9 + 0x89) = (&DAT_803a2f89)[iVar2];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_803a2f88)[iVar2],iVar5 + 0xc28,iVar4,in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  iVar2 = (int)(char)(&DAT_803a2f88)[iVar2];
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,iVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,iVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c994,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  zz_01fcefc_(param_9);
  return;
}



// ==== 801fcefc  zz_01fcefc_ ====

byte * zz_01fcefc_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  float fVar4;
  byte *pbVar5;
  bool bVar6;
  byte *pbVar7;
  float *pfVar8;
  int iVar9;
  
  pfVar8 = (float *)(param_1 + 0x14c);
  iVar9 = *(int *)(param_1 + 0x90);
  iVar3 = *(char *)(param_1 + 0x11) * 4;
  zz_0046588_((double)FLOAT_8043c998,*(float **)(param_1 + 0x144),pfVar8,pfVar8);
  pbVar5 = (byte *)gnt4_PSVECAdd_bl(pfVar8,(float *)(iVar9 + 0x1dbc),(float *)(param_1 + 0x20));
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(iVar9 + 0x1dfc);
  uVar2 = *(undefined4 *)(iVar9 + 0xb4);
  *(undefined4 *)(param_1 + 0xb8) = uVar2;
  *(undefined4 *)(param_1 + 0xb4) = uVar2;
  pbVar7 = *(byte **)(param_1 + 0x148);
  if (pbVar7 != (byte *)0x0) {
    bVar1 = *pbVar7;
    pbVar5 = (byte *)(uint)bVar1;
    if ((bVar1 & 0x80) != 0) {
      *pbVar7 = bVar1 & 0x7f;
      pbVar5 = *(byte **)(param_1 + 0x148);
      if ((*pbVar5 & 1) != 0) {
        *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar9 + 0xcc);
        *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar9 + 200);
        *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar9 + 0xd0);
        uVar2 = *(undefined4 *)(iVar9 + 0xb4);
        *(undefined4 *)(param_1 + 0x60) = uVar2;
        *(undefined4 *)(param_1 + 0x5c) = uVar2;
        *(undefined4 *)(param_1 + 0x58) = uVar2;
        *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar9 + 0xc0);
        *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(iVar9 + 0xc4);
        bVar1 = (&DAT_803a2f8a)[iVar3];
        pbVar5 = (byte *)(uint)bVar1;
        if (bVar1 == 0) {
          pbVar5 = (byte *)zz_008296c_(param_1,(uint)(byte)(&DAT_803a2f8b)[iVar3]);
        }
        else if (bVar1 == 1) {
          pbVar5 = (byte *)zz_00c3be0_(param_1,(&DAT_803a2f8b)[iVar3]);
        }
        else if (bVar1 == 2) {
          pbVar5 = (byte *)zz_006ee14_(param_1,(&DAT_803a2f8b)[iVar3]);
        }
        else if (bVar1 == 3) {
          bVar6 = zz_00fbc64_(param_1,8);
          pbVar5 = (byte *)(uint)bVar6;
        }
        fVar4 = FLOAT_8043c990;
        *(float *)(param_1 + 0x60) = FLOAT_8043c990;
        *(float *)(param_1 + 0x5c) = fVar4;
        *(float *)(param_1 + 0x58) = fVar4;
      }
    }
  }
  return pbVar5;
}



// ==== 801fd07c  FUN_801fd07c ====

void FUN_801fd07c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fd09c  FUN_801fd09c ====

void FUN_801fd09c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801fd114  zz_01fd114_ ====

void zz_01fd114_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xe04) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,8), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801fd208;
    *(code **)(puVar1 + 0x10c) = FUN_801fd758;
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



// ==== 801fd208  FUN_801fd208 ====

void FUN_801fd208(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     ((iVar1 = zz_00660e8_(param_1,iVar2), iVar1 == 1 || (*(short *)(iVar2 + 0x182) != 0)))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  (*(code *)(&PTR_FUN_803a2fc0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801fd29c  FUN_801fd29c ====

void FUN_801fd29c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int *piVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar8 = *(int *)(param_9 + 0x90);
  piVar5 = zz_0006dc8_(0xe0);
  *(int **)(param_9 + 0xdc) = piVar5;
  if (piVar5 == (int *)0x0) {
    *(undefined4 *)(param_9 + 0x54) = 0;
  }
  else {
    *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
  }
  zz_008ac80_(param_9,9);
  *(code **)(param_9 + 0x100) = FUN_801fd9c4;
  uVar9 = zz_0089100_(param_9,1,1);
  *(char *)(param_9 + 0x89) = (char)DAT_803a2faa;
  uVar1 = DAT_803a2fb0;
  *(undefined4 *)(param_9 + 100) = DAT_803a2fac;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = DAT_803a2fb4;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  iVar6 = zz_0006f98_(iVar8);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),2,param_9 + 0x150,in_r7,in_r8
                      ,in_r9,in_r10);
  iVar7 = 1;
  iVar8 = param_9;
  do {
    zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar6 + 0x600),*(int *)(iVar8 + 0xe4),3,iVar6 + 0xc28,in_r7,in_r8,in_r9,
                in_r10);
    uVar9 = zz_0007cac_((double)FLOAT_8043c9a0,*(int *)(iVar8 + 0xe4));
    fVar3 = FLOAT_8043c9a8;
    fVar2 = FLOAT_8043c9a4;
    iVar7 = iVar7 + 1;
    iVar8 = iVar8 + 4;
  } while (iVar7 < 8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  fVar4 = FLOAT_8043c9ac;
  *(float *)(param_9 + 0xd8) = fVar2;
  fVar2 = FLOAT_8043c9b0;
  *(float *)(param_9 + 0x148) = fVar3;
  *(float *)(param_9 + 0x14c) = fVar4;
  *(undefined2 *)(param_9 + 0x1c4) = 0xfa;
  *(undefined2 *)(param_9 + 0x1c8) = 0xfa;
  *(undefined2 *)(param_9 + 0x1c6) = 0xfa;
  *(float *)(param_9 + 0x154) = fVar3;
  *(undefined4 *)(param_9 + 0x144) = 0;
  *(float *)(param_9 + 0xd4) = fVar2;
  *(undefined2 *)(param_9 + 0x1c) = 600;
  zz_01fd438_(param_9);
  zz_01fd8e4_(param_9);
  return;
}



// ==== 801fd438  zz_01fd438_ ====

void zz_01fd438_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x90);
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  else {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x200;
    if ((*(byte *)(param_1 + 0x1da) & 2) != 0) {
      *(float *)(param_1 + 0x154) = FLOAT_8043c9b4;
      zz_01d7384_(iVar5);
    }
    iVar4 = zz_0006f98_(iVar5);
    if (*(float *)(param_1 + 0x154) <= FLOAT_8043c9a8) {
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar4 + 0xc28);
    }
    else {
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - FLOAT_8043c9b8;
      *(undefined1 *)(param_1 + 0x150) = 0xc0;
      *(undefined1 *)(param_1 + 0x151) = 0xc0;
      *(undefined1 *)(param_1 + 0x152) = 0xc0;
    }
    zz_01fd8e4_(param_1);
    fVar2 = FLOAT_8043c9a8;
    if (*(char *)(param_1 + 0x19) == '\0') {
      fVar1 = *(float *)(param_1 + 0xd8) - *(float *)(iVar5 + 0x768);
      *(float *)(param_1 + 0xd8) = fVar1;
      fVar3 = FLOAT_8043c9c0;
      if (fVar1 < fVar2) {
        *(float *)(param_1 + 0xd8) = FLOAT_8043c9bc;
        fVar2 = FLOAT_8043c9b8;
        *(float *)(param_1 + 0x14c) = fVar3;
        *(float *)(param_1 + 0x148) = fVar2;
        zz_0007cac_((double)*(float *)(param_1 + 0x148),*(int *)(param_1 + 0xe0));
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
      else {
        zz_0007cac_((double)*(float *)(param_1 + 0x148),*(int *)(param_1 + 0xe0));
        fVar2 = FLOAT_8043c9b8;
        *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) + *(float *)(param_1 + 0x14c);
        if (fVar2 < *(float *)(param_1 + 0x148)) {
          *(float *)(param_1 + 0x148) = fVar2;
        }
        zz_0007cac_((double)*(float *)(param_1 + 0x148),*(int *)(param_1 + 0xe0));
      }
    }
    fVar1 = FLOAT_8043c9a8;
    fVar2 = *(float *)(param_1 + 0xd4) - *(float *)(iVar5 + 0x768);
    *(float *)(param_1 + 0xd4) = fVar2;
    if (fVar2 <= fVar1) {
      *(float *)(param_1 + 0xd4) = FLOAT_8043c9b0;
      zz_01fd860_(param_1);
    }
  }
  return;
}



// ==== 801fd5cc  FUN_801fd5cc ====

/* WARNING: Removing unreachable block (ram,0x801fd6ec) */
/* WARNING: Removing unreachable block (ram,0x801fd5dc) */

void FUN_801fd5cc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  double dVar7;
  double dVar8;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    zz_008aff0_(param_1);
    iVar5 = 0;
    dVar7 = (double)FLOAT_8043c9c8;
    *(float *)(param_1 + 0xd8) = FLOAT_8043c9c4;
    *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x148) / *(float *)(param_1 + 0xd8);
    dVar8 = (double)*(float *)(param_1 + 0xb4);
    *(float *)(param_1 + 0xb4) = (float)(dVar8 * dVar7);
    do {
      zz_00b19b4_(param_1,3,0x10);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 2);
    *(float *)(param_1 + 0xb4) = (float)dVar8;
    *(undefined1 *)(iVar4 + 0x194) = 0;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  fVar3 = FLOAT_8043c9a8;
  fVar2 = *(float *)(param_1 + 0xd8) - FLOAT_8043c9b8;
  bVar6 = fVar2 <= FLOAT_8043c9a8;
  *(float *)(param_1 + 0xd8) = fVar2;
  if (bVar6) {
    zz_00f036c_(param_1,0xe1);
    zz_0089444_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  }
  else {
    *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) - *(float *)(param_1 + 0x14c);
    if (*(float *)(param_1 + 0x148) < fVar3) {
      *(float *)(param_1 + 0x148) = fVar3;
    }
    zz_0007cac_((double)*(float *)(param_1 + 0x148),*(int *)(param_1 + 0xe0));
  }
  return;
}



// ==== 801fd710  FUN_801fd710 ====

void FUN_801fd710(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fd758  FUN_801fd758 ====

void FUN_801fd758(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  undefined4 local_88;
  float local_84;
  float afStack_80 [12];
  float afStack_50 [3];
  float local_44;
  undefined4 local_34;
  undefined4 local_24;
  
  iVar3 = *(int *)(param_9 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar3,0x24);
  iVar2 = 0;
  iVar5 = 0;
  iVar3 = param_9;
  do {
    if ((*(uint *)(param_9 + 0x144) & 1 << iVar2) != 0) {
      iVar4 = *(int *)(param_9 + 0x54) + iVar5;
      gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),afStack_50);
      local_8c = FLOAT_8043c9a8;
      local_88 = *(undefined4 *)(iVar4 + 4);
      local_84 = FLOAT_8043c9a8;
      gnt4_PSMTXMultVec_bl(afStack_50,&local_8c,&local_98);
      local_44 = local_98;
      local_34 = local_94;
      local_24 = local_90;
      dVar7 = (double)*(float *)(iVar4 + 0x10);
      dVar8 = (double)*(float *)(iVar4 + 0x14);
      gnt4_PSMTXScale_bl((double)*(float *)(iVar4 + 0xc),dVar7,dVar8,afStack_80);
      pfVar1 = afStack_50;
      uVar6 = gnt4_PSMTXConcat_bl(pfVar1,afStack_80,pfVar1);
      iVar4 = *(int *)(iVar3 + 0xe4);
      zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_50,
                  (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
      zz_00097b4_(iVar4,0x24);
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
    iVar5 = iVar5 + 0x20;
  } while (iVar2 < 7);
  return;
}



// ==== 801fd860  zz_01fd860_ ====

void zz_01fd860_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0xdc) == 0) {
    return;
  }
  iVar6 = 0;
  iVar7 = 7;
  do {
    if ((*(uint *)(param_1 + 0x144) & 1 << iVar6) == 0) {
      *(uint *)(param_1 + 0x144) = *(uint *)(param_1 + 0x144) | 1 << iVar6;
      fVar3 = FLOAT_8043c9d0;
      fVar1 = FLOAT_8043c9a8;
      pfVar5 = (float *)(*(int *)(param_1 + 0x54) + iVar6 * 0x20);
      pfVar5[1] = FLOAT_8043c9cc;
      fVar2 = FLOAT_8043c9b8;
      pfVar5[2] = fVar3;
      fVar3 = FLOAT_8043c9d4;
      pfVar5[3] = fVar1;
      fVar4 = FLOAT_8043c9d8;
      pfVar5[4] = fVar2;
      pfVar5[5] = fVar1;
      pfVar5[6] = fVar3;
      *pfVar5 = fVar4;
      return;
    }
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return;
}



// ==== 801fd8e4  zz_01fd8e4_ ====

void zz_01fd8e4_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  if (*(int *)(param_1 + 0xdc) == 0) {
    return;
  }
  iVar8 = *(int *)(param_1 + 0x90);
  iVar7 = 0;
  iVar6 = 0;
  iVar9 = 7;
  do {
    fVar2 = FLOAT_8043c9a8;
    if ((*(uint *)(param_1 + 0x144) & 1 << iVar7) != 0) {
      pfVar5 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      pfVar5[1] = pfVar5[1] + pfVar5[2];
      pfVar5[3] = pfVar5[3] + pfVar5[6];
      pfVar5[5] = pfVar5[5] + pfVar5[6];
      fVar1 = *pfVar5 - *(float *)(iVar8 + 0x768);
      *pfVar5 = fVar1;
      fVar4 = FLOAT_8043c9dc;
      fVar3 = FLOAT_8043c9b8;
      if (fVar1 <= fVar2) {
        if (pfVar5[6] <= fVar2) {
          *(uint *)(param_1 + 0x144) = *(uint *)(param_1 + 0x144) & ~(1 << iVar7);
        }
        else {
          pfVar5[3] = FLOAT_8043c9b8;
          fVar1 = FLOAT_8043c9d8;
          pfVar5[5] = fVar3;
          pfVar5[6] = pfVar5[6] * fVar4;
          *pfVar5 = fVar1;
          pfVar5[1] = fVar2;
        }
      }
    }
    iVar6 = iVar6 + 0x20;
    iVar7 = iVar7 + 1;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  return;
}



// ==== 801fd9c4  FUN_801fd9c4 ====

/* WARNING: Removing unreachable block (ram,0x801fda20) */

void FUN_801fd9c4(int param_1)

{
  float afStack_38 [13];
  
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c9e0 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 801fda5c  FUN_801fda5c ====

void FUN_801fda5c(void)

{
  DAT_804363b8 = &DAT_803d6680;
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    PTR_DAT_80433930[0x40] = 0;
    zz_002a5f4_(0,0,0,0);
    gnt4_memset(DAT_804363b8,0,0x238);
  }
  (*(code *)(&PTR_FUN_803a2fd0)[*DAT_804363b8])();
  return;
}



// ==== 801fdaec  FUN_801fdaec ====

void FUN_801fdaec(void)

{
  int iVar1;
  int iVar2;
  undefined **ppuVar3;
  
  *DAT_804363b8 = 1;
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  iVar1 = 0;
  ppuVar3 = &PTR_DAT_802cfda0;
  iVar2 = 0;
  do {
    strcpy((char *)((int)DAT_804363b8 + iVar2 + 0x1d0),*ppuVar3);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 0x1a;
    ppuVar3 = ppuVar3 + 1;
  } while (iVar1 < 4);
  DAT_804363b8[8] = 0;
  PTR_DAT_80433934[0x15d7] = 0;
  *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = 2000;
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = 2000;
  return;
}



// ==== 801fdb9c  FUN_801fdb9c ====

void FUN_801fdb9c(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (DAT_804363b8[1] == 0) {
    gnt4_memset(PTR_DAT_80433944,0,0x4a0);
    iVar3 = 0;
    DAT_804363b8[1] = DAT_804363b8[1] + 1;
    PTR_DAT_80433944[0x94] = *(undefined1 *)(DAT_804363b8 + 9);
    PTR_DAT_80433944[0x95] = *(undefined1 *)((int)DAT_804363b8 + 0x13);
    PTR_DAT_80433944[0x93] = (char)DAT_804363b8[8];
    PTR_DAT_80433944[0x91] = *(undefined1 *)(DAT_804363b8 + 10);
    PTR_DAT_80433944[0x6b] = *(undefined1 *)((int)DAT_804363b8 + 0x15);
    for (iVar2 = 0; iVar2 < (char)PTR_DAT_80433944[0x6b]; iVar2 = iVar2 + 1) {
      strcpy(PTR_DAT_80433944 + iVar3 + 0x300,(char *)((int)DAT_804363b8 + iVar3 + 0x30));
      iVar3 = iVar3 + 0x1a;
    }
    iVar4 = 0;
    iVar2 = 0;
    iVar3 = 0;
    do {
      puVar1 = PTR_DAT_80433944;
      PTR_DAT_80433944[iVar4 + 0x28] = *(undefined1 *)((int)DAT_804363b8 + iVar4 + 0x20);
      puVar1[iVar2 + 0x166] = *(undefined1 *)((int)DAT_804363b8 + iVar4 + 0x24);
      puVar1[iVar2 + 0x161] = *(undefined1 *)((int)DAT_804363b8 + iVar4 + 0x28);
      strcpy(puVar1 + iVar2 + 0x120,(char *)((int)DAT_804363b8 + iVar3 + 0x1d0));
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x1a;
      iVar2 = iVar2 + 0x80;
    } while (iVar4 < 4);
    PTR_DAT_80433944[0x82] = PTR_DAT_80433934[0x15d7];
    *(undefined4 *)(PTR_DAT_80433944 + 0x70) = *(undefined4 *)(PTR_DAT_80433934 + 0x120);
    *(undefined4 *)(PTR_DAT_80433944 + 0x74) = *(undefined4 *)(PTR_DAT_80433934 + 0x15c);
  }
  else {
    iVar2 = FUN_8016e608();
    if (iVar2 < 0) {
      *DAT_804363b8 = 3;
      DAT_804363b8[1] = 1;
    }
    else if (0 < iVar2) {
      *DAT_804363b8 = 2;
      iVar2 = 0;
      DAT_804363b8[1] = 0;
      *(undefined *)(DAT_804363b8 + 9) = PTR_DAT_80433930[2];
      *(undefined *)(DAT_804363b8 + 10) = PTR_DAT_80433944[0x91];
      *(undefined *)((int)DAT_804363b8 + 0x15) = PTR_DAT_80433944[0x6b];
      for (iVar3 = 0; iVar3 < *(char *)((int)DAT_804363b8 + 0x15); iVar3 = iVar3 + 1) {
        strcpy((char *)((int)DAT_804363b8 + iVar2 + 0x30),PTR_DAT_80433944 + iVar2 + 0x300);
        iVar2 = iVar2 + 0x1a;
      }
      iVar4 = 0;
      *(undefined1 *)((int)DAT_804363b8 + 0x13) = 0;
      iVar2 = 0;
      for (iVar3 = 0; puVar1 = PTR_DAT_80433944, iVar3 < 4; iVar3 = iVar3 + 1) {
        *(undefined *)((int)DAT_804363b8 + iVar3 + 0x20) = PTR_DAT_80433944[iVar3 + 0x28];
        if ((PTR_DAT_80433944[*(char *)((int)DAT_804363b8 + iVar3 + 0x20) + 0x20] & 0xc0) == 0xc0) {
          *(byte *)((int)DAT_804363b8 + 0x13) =
               *(byte *)((int)DAT_804363b8 + 0x13) | (byte)(1 << iVar3);
        }
        if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
          *(undefined *)((int)DAT_804363b8 + iVar3 + 0x24) = puVar1[iVar2 + 0x166];
          *(undefined *)((int)DAT_804363b8 + iVar3 + 0x28) = puVar1[iVar2 + 0x161];
          strcpy((char *)((int)DAT_804363b8 + iVar4 + 0x1d0),puVar1 + iVar2 + 0x120);
        }
        iVar2 = iVar2 + 0x80;
        iVar4 = iVar4 + 0x1a;
      }
    }
  }
  return;
}



// ==== 801fdeb4  FUN_801fdeb4 ====

void FUN_801fdeb4(void)

{
  (*(code *)(&PTR_FUN_803a2fe0)[*(short *)(DAT_804363b8 + 2)])();
  return;
}



// ==== 801fdef0  FUN_801fdef0 ====

void FUN_801fdef0(void)

{
  int iVar1;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    *(short *)(DAT_804363b8 + 2) = *(short *)(DAT_804363b8 + 2) + 1;
    PTR_DAT_80433934[7] = 0;
    PTR_DAT_80433934[6] = 0;
    PTR_DAT_80433934[5] = 0;
    PTR_DAT_80433934[4] = 0;
    PTR_DAT_80433934[3] = 0;
    PTR_DAT_80433934[2] = 0;
    PTR_DAT_80433934[1] = 0;
    *PTR_DAT_80433934 = 0;
    *(undefined2 *)(PTR_DAT_80433934 + 0x46) = *(undefined2 *)(DAT_804363b8 + 0x10);
  }
  return;
}



// ==== 801fdf7c  FUN_801fdf7c ====

void FUN_801fdf7c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  uVar3 = zz_0028264_();
  if (*PTR_DAT_80433930 != '\x03') {
    *(short *)(DAT_804363b8 + 2) = *(short *)(DAT_804363b8 + 2) + 1;
    iVar2 = DAT_804363b8;
    *(short *)(DAT_804363b8 + 0x10) = *(short *)(DAT_804363b8 + 0x10) + 1;
    *PTR_DAT_80433930 = 3;
    puVar1 = PTR_DAT_80433930;
    PTR_DAT_80433930[1] = 1;
    zz_004369c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,puVar1,3,iVar2,in_r7
                ,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 801fe050  FUN_801fe050 ====

void FUN_801fe050(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  if ((PTR_DAT_80433930[0x32] == '\0') && (PTR_DAT_80433934[0x1833] == '\0')) {
    iVar2 = 0;
    do {
      puVar1 = zz_008893c_(2,0x39,0,0);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x11] = (char)param_1;
        puVar1[0x12] = 0;
        puVar1[0x13] = (char)iVar2;
        *(code **)(puVar1 + 0xc) = FUN_801fe144;
        *(code **)(puVar1 + 0x10c) = FUN_801fe3ac;
        puVar1[0x88] = 4;
        *(int *)(puVar1 + 0x144) = param_1 * 0x18 + -0x7fc5d010;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
    if (puVar1 != (undefined1 *)0x0) {
      PTR_DAT_80433934[0x1833] = 1;
    }
  }
  return;
}



// ==== 801fe134  FUN_801fe134 ====

void FUN_801fe134(void)

{
  PTR_DAT_80433934[0x1833] = 0;
  return;
}



// ==== 801fe144  FUN_801fe144 ====

void FUN_801fe144(int param_1)

{
  (*(code *)(&PTR_FUN_803a3008)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801fe180  FUN_801fe180 ====

void FUN_801fe180(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x84) = 0x11;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  fVar1 = FLOAT_8043c9e8;
  *(undefined2 *)(param_1 + 0x1c) = 0x708;
  *(float *)(param_1 + 0xd4) = fVar1;
  fVar1 = FLOAT_8043c9f0;
  if (*(char *)(param_1 + 0x13) == '\0') {
    *(float *)(param_1 + 0x48) = FLOAT_8043c9ec;
    fVar2 = FLOAT_8043c9f4;
    *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x48) - fVar1;
    *(float *)(param_1 + 0x5c) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_8043c9f8;
    fVar2 = FLOAT_8043c9fc;
    *(float *)(param_1 + 0x68) = fVar1 + *(float *)(param_1 + 0x48);
    *(float *)(param_1 + 0x5c) = fVar2;
  }
  fVar2 = FLOAT_8043ca00;
  fVar1 = FLOAT_8043c9f4;
  *(float *)(param_1 + 0x6c) = FLOAT_8043ca00;
  *(float *)(param_1 + 100) = fVar2;
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  *(float *)(param_1 + 0x3c) =
       (*(float *)(param_1 + 0x48) - *(float *)(param_1 + 0x68)) / *(float *)(param_1 + 0xd4);
  FUN_801fe268(param_1);
  return;
}



// ==== 801fe268  FUN_801fe268 ====

void FUN_801fe268(int param_1)

{
  char cVar1;
  float fVar2;
  
  if ((*(char *)(param_1 + 0x19) < '\x03') &&
     ((PTR_DAT_80433934[0x1833] == '\0' || ('\x04' < (char)PTR_DAT_80433934[0x45])))) {
    *(undefined1 *)(param_1 + 0x19) = 3;
  }
  fVar2 = FLOAT_8043c9e8;
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x03') {
    *(undefined1 *)(param_1 + 0x19) = 4;
    *(float *)(param_1 + 0x3c) = -*(float *)(param_1 + 0x3c);
    *(float *)(param_1 + 0xd4) = fVar2;
    return;
  }
  if (cVar1 < '\x03') {
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      *(char *)(param_1 + 0x19) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0x82) = 0x11;
    }
  }
  else {
    if (cVar1 == '\x05') {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    if ('\x04' < cVar1) {
      return;
    }
  }
  fVar2 = FLOAT_8043ca00;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_8043c9f4;
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x3c);
  if (*(float *)(param_1 + 0xd4) <= fVar2) {
    if (*(char *)(param_1 + 0x19) == '\x01') {
      *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x48);
    }
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    return;
  }
  return;
}



// ==== 801fe38c  FUN_801fe38c ====

void FUN_801fe38c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fe3ac  FUN_801fe3ac ====

void FUN_801fe3ac(int param_1)

{
  DAT_803c1140 = &DAT_803a3018;
  DAT_803c113c = param_1 + 0x114;
  DAT_803c1150 = *(undefined4 *)(param_1 + 0x144);
  DAT_803c1174 = FLOAT_8043c9f4;
  DAT_803c1164 = 5;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  DAT_803c116a = 6;
  DAT_803c1172 = 0;
  FUN_80051d10(-0x7fc3eed0);
  return;
}



// ==== 801fe424  FUN_801fe424 ====

void FUN_801fe424(int param_1,undefined1 param_2,undefined4 *param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x35;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801fe538;
    *(code **)(puVar1 + 0x10c) = FUN_801fe8fc;
    *(undefined4 *)(puVar1 + 0x70) = *param_3;
    *(undefined2 *)(puVar1 + 0x74) = *(undefined2 *)(param_3 + 1);
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



// ==== 801fe538  FUN_801fe538 ====

void FUN_801fe538(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(iVar1 + 0x18) < '\x02') {
      if ((*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94)) &&
         ((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0)) goto LAB_801fe5a0;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801fe5a0:
  (*(code *)(&PTR_FUN_803a32b0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801fe5d0  FUN_801fe5d0 ====

void FUN_801fe5d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  undefined8 uVar3;
  
  bVar1 = *(byte *)(param_9 + 0x11);
  iVar2 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(undefined **)(param_9 + 0x54) = (&PTR_DAT_803a30fc)[(uint)bVar1 * 7];
  *(code **)(param_9 + 0x100) = FUN_801fe758;
  uVar3 = zz_0089100_(param_9,0x41,1);
  FUN_801fe93c(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  *(undefined1 *)(param_9 + 0x82) = 1;
  if (*(short *)(&DAT_803a30f2 + (uint)bVar1 * 0x1c) == 0) {
    zz_00f036c_(iVar2,0xb0);
  }
  else {
    zz_00f061c_((double)FLOAT_8043ca08,iVar2,0xb0);
  }
  return;
}



// ==== 801fe694  FUN_801fe694 ====

void FUN_801fe694(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  char cVar2;
  double dVar3;
  
  fVar1 = *(float *)(param_9 + 0xd4) + *(float *)(*(int *)(param_9 + 0x8c) + 0x1dc8);
  dVar3 = (double)fVar1;
  *(float *)(param_9 + 0xd4) = fVar1;
  if ((double)*(float *)(param_9 + 0xd8) <= dVar3) {
    cVar2 = *(char *)(param_9 + 0x13) + '\x01';
    *(char *)(param_9 + 0x13) = cVar2;
    if (cVar2 < '\x01') {
      FUN_801fe93c(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  zz_0019178_((double)*(float *)(param_9 + 0xd4),(int *)(param_9 + 0x144),(float *)(param_9 + 0x58))
  ;
  return;
}



// ==== 801fe724  FUN_801fe724 ====

void FUN_801fe724(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801fe738  FUN_801fe738 ====

void FUN_801fe738(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fe758  FUN_801fe758 ====

void FUN_801fe758(int param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float afStack_30 [4];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  local_20 = 0x43300000;
  iVar4 = *(int *)(param_1 + 0x8c);
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  psVar3 = (short *)(&DAT_803a30f0 + iVar1);
  iVar2 = iVar4 + *psVar3 * 0x30 + (char)(&DAT_803a30f4)[iVar1] * 4;
  uStack_1c = (int)(char)(&DAT_803a30f5)[iVar1] ^ 0x80000000;
  local_3c = *(float *)(iVar2 + 0x8d4);
  local_38 = *(undefined4 *)(iVar2 + 0x8e4);
  local_34 = *(undefined4 *)(iVar2 + 0x8f4);
  gnt4_PSQUATScale_bl((double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043ca10),
                      &local_3c,&local_3c);
  local_18 = 0x43300000;
  iVar2 = iVar4 + *psVar3 * 0x30 + (char)(&DAT_803a30f6)[iVar1] * 4;
  uStack_14 = (int)(char)(&DAT_803a30f7)[iVar1] ^ 0x80000000;
  local_48 = *(float *)(iVar2 + 0x8d4);
  local_44 = *(undefined4 *)(iVar2 + 0x8e4);
  local_40 = *(undefined4 *)(iVar2 + 0x8f4);
  gnt4_PSQUATScale_bl((double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043ca10),
                      &local_48,&local_48);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar4 + *psVar3 * 0x30 + 0x8d4),(float *)(iVar1 + -0x7fc5cf00),
             (float *)(param_1 + 0x20));
  gnt4_PSQUATScale_bl((double)(*(float *)(iVar4 + 0xb4) * *(float *)(&DAT_803a30f8 + iVar1)),
                      (float *)(param_1 + 0x58),afStack_30);
  zz_0045ef4_((float *)(param_1 + 0x114),5,&local_3c,&local_48);
  FUN_80045838((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70),
               *(short *)(param_1 + 0x72),*(short *)(param_1 + 0x74));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),afStack_30);
  return;
}



// ==== 801fe8fc  FUN_801fe8fc ====

void FUN_801fe8fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801fe93c  FUN_801fe93c ====

void FUN_801fe93c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  double dVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar2;
  undefined8 uVar3;
  
  dVar1 = DOUBLE_8043ca10;
  *(float *)(param_9 + 0xd4) = FLOAT_8043ca18;
  psVar2 = (short *)(*(int *)(param_9 + 0x54) + *(char *)(param_9 + 0x13) * 8);
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)psVar2[1] ^ 0x80000000) - dVar1);
  uVar3 = zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar2 + 2),(float *)(param_9 + 0x58));
  zz_000726c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)(int)*psVar2,(int)*(char *)(param_9 + 0x88),in_r7,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 801fe9dc  gnt4-PPCMfmsr ====

void gnt4_PPCMfmsr(void)

{
  return;
}



// ==== 801fe9e4  gnt4-PPCMtmsr ====

void gnt4_PPCMtmsr(void)

{
  return;
}



// ==== 801fe9ec  gnt4-PPCMfhid0 ====

void gnt4_PPCMfhid0(void)

{
  return;
}



// ==== 801fe9f4  zz_01fe9f4_ ====

void zz_01fe9f4_(void)

{
  return;
}



// ==== 801fe9fc  gnt4-PPCMfl2cr ====

void gnt4_PPCMfl2cr(void)

{
  return;
}



// ==== 801fea04  gnt4-PPCMtl2cr ====

void gnt4_PPCMtl2cr(void)

{
  return;
}



// ==== 801fea0c  gnt4-PPCMtdec ====

void gnt4_PPCMtdec(void)

{
  return;
}



// ==== 801fea14  gnt4-PPCSync ====

void gnt4_PPCSync(void)

{
  syscall();
  return;
}



// ==== 801fea1c  gnt4-PPCHalt ====

void gnt4_PPCHalt(void)

{
  sync(0);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== 801fea30  zz_01fea30_ ====

void zz_01fea30_(void)

{
  return;
}



// ==== 801fea38  zz_01fea38_ ====

void zz_01fea38_(void)

{
  return;
}



// ==== 801fea40  zz_01fea40_ ====

void zz_01fea40_(void)

{
  return;
}



// ==== 801fea48  zz_01fea48_ ====

void zz_01fea48_(void)

{
  return;
}



// ==== 801fea50  zz_01fea50_ ====

void zz_01fea50_(void)

{
  return;
}



// ==== 801fea58  zz_01fea58_ ====

void zz_01fea58_(void)

{
  return;
}



// ==== 801fea60  gnt4-PPCMffpscr ====

uint gnt4_PPCMffpscr(void)

{
  byte in_fp_fx;
  byte in_fp_fex;
  byte in_fp_vx;
  byte in_fp_ox;
  byte in_fp_ux;
  byte in_fp_zx;
  byte in_fp_xx;
  byte in_fp_vxsnan;
  byte in_fp_vxisi;
  byte in_fp_vxidi;
  byte in_fp_vxzdz;
  byte in_fp_vximz;
  byte in_fp_vxvc;
  byte in_fp_fr;
  byte in_fp_fi;
  byte in_fp_c;
  byte in_fp_cc0;
  byte in_fp_cc1;
  byte in_fp_cc2;
  byte in_fp_cc3;
  byte in_fp_reserve1;
  byte in_fp_vxsoft;
  byte in_fp_vxsqrt;
  byte in_fp_vxcvi;
  byte in_fp_ve;
  byte in_fp_oe;
  byte in_fp_ue;
  byte in_fp_ze;
  byte in_fp_xe;
  byte in_fp_ni;
  byte in_fp_rn0;
  byte in_fp_rn1;
  
  return in_fp_rn1 & 1 | (uint)in_fp_fx << 0x1f | (in_fp_fex & 1) << 0x1e | (in_fp_vx & 1) << 0x1d |
         (in_fp_ox & 1) << 0x1c | (in_fp_ux & 1) << 0x1b | (in_fp_zx & 1) << 0x1a |
         (in_fp_xx & 1) << 0x19 | (in_fp_vxsnan & 1) << 0x18 | (in_fp_vxisi & 1) << 0x17 |
         (in_fp_vxidi & 1) << 0x16 | (in_fp_vxzdz & 1) << 0x15 | (in_fp_vximz & 1) << 0x14 |
         (in_fp_vxvc & 1) << 0x13 | (in_fp_fr & 1) << 0x12 | (in_fp_fi & 1) << 0x11 |
         (in_fp_c & 1) << 0x10 | (in_fp_cc0 & 1) << 0xf | (in_fp_cc1 & 1) << 0xe |
         (in_fp_cc2 & 1) << 0xd | (in_fp_cc3 & 1) << 0xc | (in_fp_reserve1 & 1) << 0xb |
         (in_fp_vxsoft & 1) << 10 | (in_fp_vxsqrt & 1) << 9 | (in_fp_vxcvi & 1) << 8 |
         (in_fp_ve & 1) << 7 | (in_fp_oe & 1) << 6 | (in_fp_ue & 1) << 5 | (in_fp_ze & 1) << 4 |
         (in_fp_xe & 1) << 3 | (in_fp_ni & 1) << 2 | (in_fp_rn0 & 1) << 1;
}



// ==== 801fea80  gnt4-PPCMtfpscr ====

void gnt4_PPCMtfpscr(void)

{
  return;
}



// ==== 801feaa8  gnt4-PPCMfhid2 ====

void gnt4_PPCMfhid2(void)

{
  return;
}



// ==== 801feab0  gnt4-PPCMthid2 ====

void gnt4_PPCMthid2(void)

{
  return;
}



// ==== 801feab8  zz_01feab8_ ====

void zz_01feab8_(void)

{
  return;
}



// ==== 801feac0  zz_01feac0_ ====

void zz_01feac0_(void)

{
  gnt4_PPCMfhid0();
  zz_01fe9f4_();
  return;
}



// ==== 801feae8  zz_01feae8_ ====

void zz_01feae8_(void)

{
  return;
}



// ==== 801feaf0  gnt4-__OSFPRInit-bl ====

/* WARNING: Removing unreachable block (ram,0x801feb10) */

double gnt4___OSFPRInit_bl(void)

{
  return DOUBLE_804363d0;
}



// ==== 801fec18  gnt4-OSGetConsoleType-bl ====

int gnt4_OSGetConsoleType_bl(void)

{
  int iVar1;
  
  if ((DAT_804363c0 == 0) || (iVar1 = *(int *)(DAT_804363c0 + 0x2c), iVar1 == 0)) {
    iVar1 = 0x10000002;
  }
  return iVar1;
}



// ==== 801fec40  zz_01fec40_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_01fec40_(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  void *pvVar4;
  void *pvVar5;
  size_t __n;
  
  uVar1 = zz_0204b70_();
  if (uVar1 == 0x80000000) {
    DAT_804363ec = _DAT_812fdff0;
    DAT_804363e8 = _DAT_812fdfec;
    if (_DAT_812fdff0 == 0) {
      iVar2 = gnt4_OSGetArenaHi_bl();
      iVar3 = gnt4_OSGetArenaLo_bl();
      pvVar4 = (void *)gnt4_OSGetArenaLo_bl();
      gnt4_memset(pvVar4,0,iVar2 - iVar3);
    }
    else {
      uVar1 = gnt4_OSGetArenaLo_bl();
      if (uVar1 < DAT_804363ec) {
        uVar1 = gnt4_OSGetArenaHi_bl();
        if (DAT_804363ec < uVar1) {
          iVar2 = gnt4_OSGetArenaLo_bl();
          __n = DAT_804363ec - iVar2;
          pvVar4 = (void *)gnt4_OSGetArenaLo_bl();
          gnt4_memset(pvVar4,0,__n);
          pvVar5 = (void *)gnt4_OSGetArenaHi_bl();
          pvVar4 = DAT_804363e8;
          if (DAT_804363e8 < pvVar5) {
            iVar2 = gnt4_OSGetArenaHi_bl();
            gnt4_memset(pvVar4,0,iVar2 - (int)pvVar4);
          }
        }
        else {
          iVar2 = gnt4_OSGetArenaHi_bl();
          iVar3 = gnt4_OSGetArenaLo_bl();
          pvVar4 = (void *)gnt4_OSGetArenaLo_bl();
          gnt4_memset(pvVar4,0,iVar2 - iVar3);
        }
      }
    }
  }
  else {
    DAT_804363ec = 0;
    DAT_804363e8 = (void *)0x0;
    iVar2 = gnt4_OSGetArenaHi_bl();
    iVar3 = gnt4_OSGetArenaLo_bl();
    pvVar4 = (void *)gnt4_OSGetArenaLo_bl();
    gnt4_memset(pvVar4,0,iVar2 - iVar3);
  }
  return;
}



// ==== 801fed68  gnt4-InquiryCallback-bl ====

void gnt4_InquiryCallback_bl(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0xc) == 0) {
    DAT_800030e6 = DAT_803d68c2 | 0x8000;
  }
  else {
    DAT_800030e6 = 1;
  }
  return;
}



// ==== 801feda4  zz_01feda4_ ====

void zz_01feda4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,uint param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  char *pcVar5;
  undefined4 extraout_r4_02;
  char *pcVar6;
  undefined8 uVar7;
  undefined8 extraout_f1;
  longlong lVar8;
  ulonglong uVar9;
  
  if (DAT_804363e0 != 0) {
    return;
  }
  DAT_804363e0 = 1;
  lVar8 = gnt4___OSGetSystemTime_bl();
  DAT_804363f8 = (undefined4)((ulonglong)lVar8 >> 0x20);
  DAT_804363fc = (undefined4)lVar8;
  gnt4_OSDisableInterrupts_bl();
  zz_01fea30_();
  zz_01fea38_();
  zz_01fea40_();
  zz_01fea48_();
  zz_01fea50_();
  zz_01fea58_();
  zz_01feac0_();
  zz_01feae8_();
  DAT_804363c4 = (uint *)0x0;
  DAT_804363c0 = -0x80000000;
  if (DAT_800000f4 == 0) {
    if (DAT_80000034 != 0) {
      DAT_804363c8 = (uint)DAT_800030e8;
      DAT_804363c4 = &DAT_804363c8;
      DAT_80436624 = (uint)DAT_800030e9;
    }
  }
  else {
    DAT_804363c4 = (uint *)(DAT_800000f4 + 0xc);
    DAT_80436624 = *(uint *)(DAT_800000f4 + 0x24);
    DAT_800030e8 = (byte)*DAT_804363c4;
    DAT_800030e9 = (byte)DAT_80436624;
  }
  DAT_80436534 = 1;
  iVar2 = DAT_80000030;
  if (DAT_80000030 == 0) {
    iVar2 = -0x7fbb0ac0;
  }
  gnt4_OSSetArenaLo_bl(iVar2);
  if (((*(int *)(DAT_804363c0 + 0x30) == 0) && (DAT_804363c4 != (uint *)0x0)) && (*DAT_804363c4 < 2)
     ) {
    gnt4_OSSetArenaLo_bl(0x8044d540);
  }
  iVar2 = *(int *)(DAT_804363c0 + 0x34);
  if (iVar2 == 0) {
    iVar2 = -0x7e900000;
  }
  gnt4_OSSetArenaHi_bl(iVar2);
  gnt4_OSExceptionInit_bl();
  gnt4___OSInitSystemCall_bl();
  gnt4_OSInitAlarm();
  gnt4___OSModuleInit_bl();
  gnt4___OSInterruptInit_bl();
  gnt4___OSSetInterruptHandler_bl(0x16,gnt4___OSResetSWInterruptHandler_bl);
  gnt4___OSContextInit_bl();
  uVar7 = gnt4___OSCacheInit_bl();
  uVar7 = zz_0208740_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0209d9c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,param_11,param_12,param_13,param_14,
              param_15,param_16);
  gnt4___OSInitSram_bl();
  gnt4___OSThreadInit_bl();
  gnt4___OSInitAudioSystem_bl();
  gnt4_PPCMfhid2();
  uVar7 = gnt4_PPCMthid2();
  uVar3 = extraout_r4;
  if (DAT_804363f0 == 0) {
    uVar7 = gnt4___OSInitMemoryProtection_bl();
    uVar3 = extraout_r4_00;
  }
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Dolphin_OS_803a3304,uVar3,param_11,param_12,param_13,param_14,param_15,
                           param_16);
  pcVar6 = s_12_33_06_803a3338;
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Kernel_built____s__s_803a3314,s_Apr_17_2003_803a332c,
                           s_12_33_06_803a3338,param_12,param_13,param_14,param_15,param_16);
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Console_Type___803a3344,extraout_r4_01,pcVar6,param_12,param_13,
                           param_14,param_15,param_16);
  if ((DAT_804363c0 == 0) || (pcVar5 = *(char **)(DAT_804363c0 + 0x2c), pcVar5 == (char *)0x0)) {
    pcVar5 = (char *)0x10000002;
  }
  uVar1 = (uint)pcVar5 & 0xf0000000;
  if (uVar1 == 0x10000000) {
LAB_801ff00c:
    pcVar6 = (char *)((uint)pcVar5 & 0xfffffff);
    if (pcVar6 == (char *)0x10000002) {
      uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_EPPC_Arthur_803a3380,pcVar5,0x10000002,param_12,param_13,param_14,
                               param_15,param_16);
    }
    else {
      if (pcVar6 < (char *)0x10000002) {
        if (pcVar6 == (char *)0x10000000) {
          uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   s_Mac_Emulator_803a3360,pcVar5,0x10000000,param_12,param_13,
                                   param_14,param_15,param_16);
          goto LAB_801ff0ac;
        }
        if ((char *)0xfffffff < pcVar6) {
          uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   s_PC_Emulator_803a3370,pcVar5,pcVar6,param_12,param_13,param_14,
                                   param_15,param_16);
          goto LAB_801ff0ac;
        }
      }
      else if (pcVar6 < (char *)0x10000004) {
        uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_EPPC_Minnow_803a3390,pcVar5,pcVar6,param_12,param_13,param_14,
                                 param_15,param_16);
        goto LAB_801ff0ac;
      }
      param_12 = (uint)pcVar5 & 0xfffffff;
      uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_Development_HW_d___08x__803a33a0,param_12 - 3,pcVar5,param_12,
                               param_13,param_14,param_15,param_16);
      pcVar6 = pcVar5;
    }
  }
  else {
    if ((int)uVar1 < 0x10000000) {
      if (uVar1 == 0) {
        uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_Retail__d_803a3354,pcVar5,pcVar6,param_12,param_13,param_14,
                                 param_15,param_16);
        goto LAB_801ff0ac;
      }
    }
    else if (uVar1 == 0x20000000) goto LAB_801ff00c;
    uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435c54,pcVar5,pcVar6,param_12,param_13,param_14,param_15,
                             param_16);
  }
LAB_801ff0ac:
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Memory__d_MB_803a33bc,*(uint *)(DAT_804363c0 + 0x28) >> 0x14,pcVar6,
                           param_12,param_13,param_14,param_15,param_16);
  uVar3 = gnt4_OSGetArenaHi_bl();
  uVar4 = gnt4_OSGetArenaLo_bl();
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Arena___0x_x___0x_x_803a33cc,uVar4,uVar3,param_12,param_13,param_14,
                           param_15,param_16);
  gnt4_OSRegisterVersion_bl
            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435c50,
             extraout_r4_02,uVar3,param_12,param_13,param_14,param_15,param_16);
  if ((DAT_804363c4 != (uint *)0x0) && (1 < *DAT_804363c4)) {
    zz_023166c_();
  }
  uVar7 = zz_01fec40_();
  uVar9 = gnt4_OSEnableInterrupts_bl();
  if (DAT_804363f0 == 0) {
    gnt4_DVDInit_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (int)(uVar9 >> 0x20),(int)uVar9,uVar3,param_12,param_13,param_14,param_15,
                    param_16);
    if (DAT_804363cc == 0) {
      gnt4_DCInvalidateRange_bl(0x803d68c0,0x20);
      gnt4_DVDInquiryAsync_bl((undefined4 *)&DAT_803d68e0,&DAT_803d68c0,gnt4_InquiryCallback_bl);
    }
    else {
      DAT_800030e6 = 0x9000;
    }
  }
  return;
}



// ==== 801ff17c  gnt4-OSExceptionInit-bl ====

/* WARNING: Removing unreachable block (ram,0x801ff2ec) */
/* WARNING: Removing unreachable block (ram,0x801ff2f0) */
/* WARNING: Removing unreachable block (ram,0x801ff334) */

void gnt4_OSExceptionInit_bl(void)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  void *__dest;
  uint uVar4;
  int *piVar5;
  int iVar6;
  
  uVar1 = uRam801ff4bc;
  if (DAT_80000060 == 0) {
    gnt4_DBPrintf();
    gnt4_memcpy(&DAT_80000060,gnt4___OSDBIntegrator,0x24);
    gnt4_DCFlushRangeNoSync_bl(0x80000060,0x24);
    sync(0);
    gnt4_ICInvalidateRange_bl(0x80000060,0x24);
  }
  piVar5 = &DAT_803a33e4;
  for (uVar4 = 0; (uVar4 & 0xff) < 0xf; uVar4 = uVar4 + 1) {
    if (((DAT_804363c4 == (uint *)0x0) || (*DAT_804363c4 < 2)) ||
       (uVar2 = gnt4___DBIsExceptionMarked(uVar4), uVar2 == 0)) {
      uRam801ff4bc = uVar1 | uVar4 & 0xff;
      uVar2 = gnt4___DBIsExceptionMarked(uVar4);
      if (uVar2 == 0) {
        puVar3 = (undefined4 *)0x801ff4ac;
        iVar6 = 1;
        do {
          *puVar3 = 0x60000000;
          puVar3 = puVar3 + 1;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      else {
        gnt4_DBPrintf();
        gnt4_memcpy((void *)0x801ff4ac,gnt4___OSDBJump_bl,4);
      }
      __dest = (void *)(*piVar5 + -0x80000000);
      gnt4_memcpy(__dest,(void *)0x801ff454,0x98);
      gnt4_DCFlushRangeNoSync_bl((uint)__dest,0x98);
      sync(0);
      gnt4_ICInvalidateRange_bl((uint)__dest,0x98);
    }
    else {
      gnt4_DBPrintf();
    }
    piVar5 = piVar5 + 1;
  }
  DAT_804363e4 = &DAT_80003000;
  for (uVar4 = 0; (uVar4 & 0xff) < 0xf; uVar4 = uVar4 + 1) {
    gnt4___OSSetExceptionHandler_bl(uVar4,gnt4_OSDefaultExceptionHandler_bl);
  }
  uRam801ff4bc = uVar1;
  gnt4_DBPrintf();
  return;
}



// ==== 801ff3fc  gnt4-__OSDBIntegrator ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 gnt4___OSDBIntegrator(void)

{
  undefined4 in_LR;
  
  _DAT_0000004c = in_LR;
  return 0x30;
}



// ==== 801ff420  gnt4-__OSDBJump-bl ====

undefined4 gnt4___OSDBJump_bl(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = func_0x00000060();
  puVar2 = (undefined4 *)(DAT_804363e4 + ((uint)((ulonglong)uVar3 >> 0x20) & 0xff) * 4);
  uVar1 = *puVar2;
  *puVar2 = (int)uVar3;
  return uVar1;
}



// ==== 801ff424  gnt4-__OSSetExceptionHandler-bl ====

undefined4 gnt4___OSSetExceptionHandler_bl(uint param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(DAT_804363e4 + (param_1 & 0xff) * 4);
  uVar1 = *puVar2;
  *puVar2 = param_2;
  return uVar1;
}



// ==== 801ff440  gnt4-__OSGetExceptionHandler-bl ====

undefined4 gnt4___OSGetExceptionHandler_bl(uint param_1)

{
  return *(undefined4 *)(DAT_804363e4 + (param_1 & 0xff) * 4);
}



// ==== 801ff454  gnt4-OSExceptionVector-bl ====

void gnt4_OSExceptionVector_bl(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint in_MSR;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined4 in_SRR0;
  uint in_SRR1;
  
  iVar1 = iRam000000c0;
  *(undefined4 *)(iRam000000c0 + 0xc) = param_1;
  *(undefined4 *)(iVar1 + 0x10) = param_2;
  *(undefined4 *)(iVar1 + 0x14) = param_3;
  *(ushort *)(iVar1 + 0x1a2) = *(ushort *)(iVar1 + 0x1a2) | 2;
  *(uint *)(iVar1 + 0x80) =
       (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
       (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
       (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  *(undefined4 *)(iVar1 + 0x84) = in_LR;
  *(undefined4 *)(iVar1 + 0x88) = in_CTR;
  *(undefined4 *)(iVar1 + 0x8c) = in_XER;
  *(undefined4 *)(iVar1 + 0x198) = in_SRR0;
  *(uint *)(iVar1 + 0x19c) = in_SRR1;
  if ((in_SRR1 & 2) == 0) {
    returnFromInterrupt(in_MSR,in_MSR | 0x30);
    return;
  }
  returnFromInterrupt(in_MSR,in_MSR | 0x30);
  return;
}



// ==== 801ff4f0  gnt4-OSDefaultExceptionHandler-bl ====

void gnt4_OSDefaultExceptionHandler_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,byte param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 in_r0;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  uint in_DSISR;
  undefined4 in_DAR;
  
  *param_10 = in_r0;
  param_10[1] = register0x00000004;
  param_10[2] = &DAT_8043ea20;
  param_10[6] = param_12;
  param_10[7] = param_13;
  param_10[8] = param_14;
  param_10[9] = param_15;
  param_10[10] = param_16;
  param_10[0xb] = in_r11;
  param_10[0xc] = in_r12;
  param_10[0xd] = &FLOAT_8043b5a0;
  param_10[0xe] = unaff_r14;
  param_10[0xf] = unaff_r15;
  param_10[0x10] = unaff_r16;
  param_10[0x11] = unaff_r17;
  param_10[0x12] = unaff_r18;
  param_10[0x13] = unaff_r19;
  param_10[0x14] = unaff_r20;
  param_10[0x15] = unaff_r21;
  param_10[0x16] = unaff_r22;
  param_10[0x17] = unaff_r23;
  param_10[0x18] = unaff_r24;
  param_10[0x19] = unaff_r25;
  param_10[0x1a] = unaff_r26;
  param_10[0x1b] = unaff_r27;
  param_10[0x1c] = unaff_r28;
  param_10[0x1d] = unaff_r29;
  param_10[0x1e] = unaff_r30;
  param_10[0x1f] = unaff_r31;
  param_10[0x6a] = 0;
  param_10[0x6b] = 0x40004;
  param_10[0x6c] = 0x50005;
  param_10[0x6d] = 0x60006;
  param_10[0x6e] = 0x70007;
  param_10[0x6f] = 0;
  param_10[0x70] = 0;
  gnt4___OSUnhandledException_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             in_DSISR,in_DAR,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ff548  gnt4-__OSPSInit-bl ====

undefined4 gnt4___OSPSInit_bl(void)

{
  gnt4_PPCMfhid2();
  gnt4_PPCMthid2();
  gnt4_ICFlashInvalidate_bl();
  sync(0);
  return 0;
}



// ==== 801ff59c  gnt4-__OSGetDIConfig-bl ====

uint gnt4___OSGetDIConfig_bl(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006024;
  return uVar1 & 0xff;
}



// ==== 801ff5b0  gnt4-OSRegisterVersion-bl ====

void gnt4_OSRegisterVersion_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435c5c,
                   param_9,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ff5dc  gnt4-OSInitAlarm ====

void gnt4_OSInitAlarm(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)gnt4___OSGetExceptionHandler_bl(8);
  if (pcVar1 != gnt4_DecrementerExceptionHandler_bl) {
    uRam80436404 = 0;
    DAT_80436400 = 0;
    gnt4___OSSetExceptionHandler_bl(8,gnt4_DecrementerExceptionHandler_bl);
  }
  return;
}



// ==== 801ff628  gnt4-OSCreateAlarm-bl ====

void gnt4_OSCreateAlarm_bl(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  return;
}



// ==== 801ff638  gnt4-InsertAlarm-bl ====

void gnt4_InsertAlarm_bl(undefined4 *param_1,undefined4 param_2,uint param_3,uint param_4,
                        undefined4 param_5)

{
  ulonglong uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  bool bVar8;
  longlong lVar9;
  
  if (0x80000000 < (uint)(param_1[7] != 0) + (param_1[6] ^ 0x80000000)) {
    lVar9 = gnt4___OSGetSystemTime_bl();
    uVar3 = (uint)((ulonglong)lVar9 >> 0x20);
    uVar4 = (uint)lVar9;
    param_3 = param_1[8];
    param_4 = param_1[9];
    if ((param_3 ^ 0x80000000) < (uint)(param_4 < uVar4) + (uVar3 ^ 0x80000000)) {
      uVar7 = param_1[6];
      uVar6 = param_1[7];
      lVar9 = gnt4___div2i(uVar3 - ((uVar4 < param_4) + param_3),uVar4 - param_4,uVar7,uVar6);
      uVar1 = lVar9 + 1;
      uVar3 = uVar6 * (int)uVar1;
      bVar8 = CARRY4(param_4,uVar3);
      param_4 = param_4 + uVar3;
      param_3 = param_3 + uVar7 * (int)uVar1 +
                          (int)((ulonglong)uVar6 * (uVar1 & 0xffffffff) >> 0x20) +
                          uVar6 * (int)(uVar1 >> 0x20) + (uint)bVar8;
    }
  }
  *param_1 = param_5;
  param_1[3] = param_4;
  param_1[2] = param_3;
  puVar5 = DAT_80436400;
  while( true ) {
    if (puVar5 == (undefined4 *)0x0) {
      param_1[5] = 0;
      iVar2 = (int)puRam80436404;
      bVar8 = puRam80436404 == (undefined4 *)0x0;
      puVar5 = param_1;
      param_1[4] = puRam80436404;
      puRam80436404 = puVar5;
      if (bVar8) {
        DAT_80436400 = param_1;
        puRam80436404 = param_1;
        lVar9 = gnt4___OSGetSystemTime_bl();
        uVar3 = param_1[2] -
                ((uint)((uint)param_1[3] < (uint)lVar9) + (int)((ulonglong)lVar9 >> 0x20)) ^
                0x80000000;
        if (uVar3 < 0x80000000) {
          gnt4_PPCMtdec();
        }
        else if (uVar3 < (param_1[3] - (uint)lVar9 < 0x80000000) + 0x80000000) {
          gnt4_PPCMtdec();
        }
        else {
          gnt4_PPCMtdec();
        }
      }
      else {
        *(undefined4 **)(iVar2 + 0x14) = param_1;
      }
      return;
    }
    if ((param_3 ^ 0x80000000) < (uint)(param_4 < (uint)puVar5[3]) + (puVar5[2] ^ 0x80000000))
    break;
    puVar5 = (undefined4 *)puVar5[5];
  }
  param_1[4] = puVar5[4];
  puVar5[4] = param_1;
  param_1[5] = puVar5;
  if (param_1[4] != 0) {
    *(undefined4 **)(param_1[4] + 0x14) = param_1;
    return;
  }
  DAT_80436400 = param_1;
  lVar9 = gnt4___OSGetSystemTime_bl();
  uVar3 = param_1[2] - ((uint)((uint)param_1[3] < (uint)lVar9) + (int)((ulonglong)lVar9 >> 0x20)) ^
          0x80000000;
  if (uVar3 < 0x80000000) {
    gnt4_PPCMtdec();
    return;
  }
  if (uVar3 < (param_1[3] - (uint)lVar9 < 0x80000000) + 0x80000000) {
    gnt4_PPCMtdec();
    return;
  }
  gnt4_PPCMtdec();
  return;
}



// ==== 801ff888  gnt4-OSSetAlarm-bl ====

void gnt4_OSSetAlarm_bl(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                       ,undefined4 param_5)

{
  longlong lVar1;
  longlong lVar2;
  
  gnt4_OSDisableInterrupts_bl();
  param_1[7] = 0;
  param_1[6] = 0;
  lVar2 = gnt4___OSGetSystemTime_bl();
  lVar1 = lVar2 + CONCAT44(param_3,param_4);
  gnt4_InsertAlarm_bl(param_1,(int)lVar2,(uint)((ulonglong)lVar1 >> 0x20),(uint)lVar1,param_5);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 801ff8f0  gnt4-OSCancelAlarm-bl ====

void gnt4_OSCancelAlarm_bl(int *param_1)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  
  gnt4_OSDisableInterrupts_bl();
  if (*param_1 == 0) {
    gnt4_OSRestoreInterrupts_bl();
  }
  else {
    iVar2 = param_1[5];
    if (iVar2 == 0) {
      iRam80436404 = param_1[4];
    }
    else {
      *(int *)(iVar2 + 0x10) = param_1[4];
    }
    if (param_1[4] == 0) {
      DAT_80436400 = iVar2;
      if (iVar2 != 0) {
        lVar3 = gnt4___OSGetSystemTime_bl();
        uVar1 = *(int *)(iVar2 + 8) -
                ((uint)(*(uint *)(iVar2 + 0xc) < (uint)lVar3) + (int)((ulonglong)lVar3 >> 0x20)) ^
                0x80000000;
        if (uVar1 < 0x80000000) {
          gnt4_PPCMtdec();
        }
        else if (uVar1 < (*(uint *)(iVar2 + 0xc) - (uint)lVar3 < 0x80000000) + 0x80000000) {
          gnt4_PPCMtdec();
        }
        else {
          gnt4_PPCMtdec();
        }
      }
    }
    else {
      *(int *)(param_1[4] + 0x14) = iVar2;
    }
    *param_1 = 0;
    gnt4_OSRestoreInterrupts_bl();
  }
  return;
}



// ==== 801ffa0c  gnt4-DecrementerExceptionCallback-bl ====

undefined8 gnt4_DecrementerExceptionCallback_bl(undefined4 param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  code *pcVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined1 auStack_2d8 [712];
  
  lVar6 = gnt4___OSGetSystemTime_bl();
  puVar1 = DAT_80436400;
  if (DAT_80436400 == (undefined4 *)0x0) {
    gnt4_OSLoadContext_bl(param_2);
  }
  if (((uint)((ulonglong)lVar6 >> 0x20) ^ 0x80000000) <
      (uint)((uint)lVar6 < (uint)puVar1[3]) + (puVar1[2] ^ 0x80000000)) {
    lVar6 = gnt4___OSGetSystemTime_bl();
    uVar3 = puVar1[2] - ((uint)((uint)puVar1[3] < (uint)lVar6) + (int)((ulonglong)lVar6 >> 0x20)) ^
            0x80000000;
    if (uVar3 < 0x80000000) {
      gnt4_PPCMtdec();
    }
    else if (uVar3 < (puVar1[3] - (uint)lVar6 < 0x80000000) + 0x80000000) {
      gnt4_PPCMtdec();
    }
    else {
      gnt4_PPCMtdec();
    }
    gnt4_OSLoadContext_bl(param_2);
  }
  DAT_80436400 = (undefined4 *)puVar1[5];
  if (DAT_80436400 == (undefined4 *)0x0) {
    uRam80436404 = 0;
  }
  else {
    *(undefined4 *)((int)DAT_80436400 + 0x10) = 0;
  }
  pcVar5 = (code *)*puVar1;
  *puVar1 = 0;
  if (0x80000000 < (uint)(puVar1[7] != 0) + (puVar1[6] ^ 0x80000000)) {
    gnt4_InsertAlarm_bl(puVar1,0x80000000,0,0,pcVar5);
  }
  iVar2 = (int)DAT_80436400;
  if (DAT_80436400 != (undefined4 *)0x0) {
    lVar6 = gnt4___OSGetSystemTime_bl();
    uVar3 = *(uint *)(iVar2 + 0xc);
    uVar4 = *(int *)(iVar2 + 8) - ((uint)(uVar3 < (uint)lVar6) + (int)((ulonglong)lVar6 >> 0x20)) ^
            0x80000000;
    if (uVar4 < 0x80000000) {
      gnt4_PPCMtdec();
    }
    else if (uVar4 < (uVar3 - (uint)lVar6 < 0x80000000) + 0x80000000) {
      gnt4_PPCMtdec();
    }
    else {
      gnt4_PPCMtdec();
    }
  }
  gnt4_OSDisableScheduler_bl();
  gnt4_OSClearContext_bl((int)auStack_2d8);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d8);
  (*pcVar5)(puVar1,param_2);
  gnt4_OSClearContext_bl((int)auStack_2d8);
  gnt4_OSSetCurrentContext_bl(param_2);
  gnt4_OSEnableScheduler_bl();
  gnt4___OSReschedule_bl();
  uVar7 = gnt4_OSLoadContext_bl(param_2);
  return uVar7;
}



// ==== 801ffc3c  gnt4-DecrementerExceptionHandler-bl ====

undefined8
gnt4_DecrementerExceptionHandler_bl
          (undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  undefined8 uVar1;
  
  *param_2 = in_r0;
  param_2[1] = register0x00000004;
  param_2[2] = &DAT_8043ea20;
  param_2[6] = param_4;
  param_2[7] = param_5;
  param_2[8] = param_6;
  param_2[9] = param_7;
  param_2[10] = param_8;
  param_2[0xb] = in_r11;
  param_2[0xc] = in_r12;
  param_2[0xd] = &FLOAT_8043b5a0;
  param_2[0xe] = unaff_r14;
  param_2[0xf] = unaff_r15;
  param_2[0x10] = unaff_r16;
  param_2[0x11] = unaff_r17;
  param_2[0x12] = unaff_r18;
  param_2[0x13] = unaff_r19;
  param_2[0x14] = unaff_r20;
  param_2[0x15] = unaff_r21;
  param_2[0x16] = unaff_r22;
  param_2[0x17] = unaff_r23;
  param_2[0x18] = unaff_r24;
  param_2[0x19] = unaff_r25;
  param_2[0x1a] = unaff_r26;
  param_2[0x1b] = unaff_r27;
  param_2[0x1c] = unaff_r28;
  param_2[0x1d] = unaff_r29;
  param_2[0x1e] = unaff_r30;
  param_2[0x1f] = unaff_r31;
  param_2[0x6a] = 0;
  param_2[0x6b] = 0x40004;
  param_2[0x6c] = 0x50005;
  param_2[0x6d] = 0x60006;
  param_2[0x6e] = 0x70007;
  param_2[0x6f] = 0;
  param_2[0x70] = 0;
  uVar1 = gnt4_DecrementerExceptionCallback_bl(param_1,(uint)param_2);
  return uVar1;
}



// ==== 801ffc8c  gnt4-DLInsert-bl ====

uint * gnt4_DLInsert_bl(uint *param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  
  puVar1 = (uint *)0x0;
  for (puVar2 = param_1; (puVar2 != (uint *)0x0 && (puVar2 < param_2)); puVar2 = (uint *)puVar2[1])
  {
    puVar1 = puVar2;
  }
  param_2[1] = (uint)puVar2;
  *param_2 = (uint)puVar1;
  if (puVar2 != (uint *)0x0) {
    *puVar2 = (uint)param_2;
    if ((uint *)((int)param_2 + param_2[2]) == puVar2) {
      param_2[2] = param_2[2] + puVar2[2];
      puVar2 = (uint *)puVar2[1];
      param_2[1] = (uint)puVar2;
      if (puVar2 != (uint *)0x0) {
        *puVar2 = (uint)param_2;
      }
    }
  }
  if (puVar1 == (uint *)0x0) {
    return param_2;
  }
  puVar1[1] = (uint)param_2;
  if ((uint *)((int)puVar1 + puVar1[2]) != param_2) {
    return param_1;
  }
  puVar1[2] = puVar1[2] + param_2[2];
  puVar1[1] = (uint)puVar2;
  if (puVar2 == (uint *)0x0) {
    return param_1;
  }
  *puVar2 = (uint)puVar1;
  return param_1;
}



// ==== 801ffd38  gnt4-OSAllocFromHeap-bl ====

int * gnt4_OSAllocFromHeap_bl(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  iVar5 = DAT_80436408 + param_1 * 0xc;
  uVar1 = param_2 + 0x3fU & 0xffffffe0;
  for (piVar6 = *(int **)(iVar5 + 4); (piVar6 != (int *)0x0 && (piVar6[2] < (int)uVar1));
      piVar6 = (int *)piVar6[1]) {
  }
  if (piVar6 == (int *)0x0) {
    return (int *)0x0;
  }
  iVar2 = piVar6[2];
  if (iVar2 - uVar1 < 0x40) {
    iVar2 = *(int *)(iVar5 + 4);
    if ((int *)piVar6[1] != (int *)0x0) {
      *(int *)piVar6[1] = *piVar6;
    }
    if (*piVar6 == 0) {
      iVar2 = piVar6[1];
    }
    else {
      *(int *)(*piVar6 + 4) = piVar6[1];
    }
    *(int *)(iVar5 + 4) = iVar2;
  }
  else {
    piVar6[2] = uVar1;
    piVar4 = (int *)((int)piVar6 + uVar1);
    piVar4[2] = iVar2 - uVar1;
    *piVar4 = *piVar6;
    piVar4[1] = piVar6[1];
    if ((undefined4 *)piVar4[1] != (undefined4 *)0x0) {
      *(undefined4 *)piVar4[1] = piVar4;
    }
    if (*piVar4 == 0) {
      *(int **)(iVar5 + 4) = piVar4;
    }
    else {
      *(int **)(*piVar4 + 4) = piVar4;
    }
  }
  puVar3 = *(undefined4 **)(iVar5 + 8);
  piVar6[1] = (int)puVar3;
  *piVar6 = 0;
  if (puVar3 != (undefined4 *)0x0) {
    *puVar3 = piVar6;
  }
  *(int **)(iVar5 + 8) = piVar6;
  return piVar6 + 8;
}



// ==== 801ffe34  gnt4-OSFreeToHeap-bl ====

void gnt4_OSFreeToHeap_bl(int param_1,int param_2)

{
  undefined4 uVar1;
  uint *puVar2;
  int iVar3;
  
  puVar2 = (uint *)(param_2 + -0x20);
  iVar3 = DAT_80436408 + param_1 * 0xc;
  uVar1 = *(undefined4 *)(iVar3 + 8);
  if (*(uint **)(param_2 + -0x1c) != (uint *)0x0) {
    **(uint **)(param_2 + -0x1c) = *puVar2;
  }
  if (*puVar2 == 0) {
    uVar1 = *(undefined4 *)(param_2 + -0x1c);
  }
  else {
    *(undefined4 *)(*puVar2 + 4) = *(undefined4 *)(param_2 + -0x1c);
  }
  *(undefined4 *)(iVar3 + 8) = uVar1;
  puVar2 = gnt4_DLInsert_bl(*(uint **)(iVar3 + 4),puVar2);
  *(uint **)(iVar3 + 4) = puVar2;
  return;
}



// ==== 801ffeb0  gnt4-OSSetCurrentHeap-bl ====

undefined4 gnt4_OSSetCurrentHeap_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80435c60;
  DAT_80435c60 = param_1;
  return uVar1;
}



// ==== 801ffec0  gnt4-OSInitAlloc-bl ====

void gnt4_OSInitAlloc_bl(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  iVar1 = 0;
  DAT_80436408 = param_1;
  DAT_8043640c = param_3;
  for (iVar2 = 0; iVar2 < DAT_8043640c; iVar2 = iVar2 + 1) {
    puVar3 = (undefined4 *)(DAT_80436408 + iVar1);
    *puVar3 = 0xffffffff;
    iVar1 = iVar1 + 0xc;
    puVar3[2] = 0;
    puVar3[1] = 0;
  }
  DAT_80436414 = param_2 & 0xffffffe0;
  DAT_80435c60 = 0xffffffff;
  DAT_80436410 = DAT_80436408 + param_3 * 0xc + 0x1fU & 0xffffffe0;
  return;
}



// ==== 801fff30  gnt4-OSCreateHeap-bl ====

int gnt4_OSCreateHeap_bl(int param_1,uint param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  puVar1 = (undefined4 *)(param_1 + 0x1fU & 0xffffffe0);
  iVar2 = 0;
  piVar3 = DAT_80436408;
  iVar4 = DAT_8043640c;
  if (0 < DAT_8043640c) {
    do {
      if (*piVar3 < 0) {
        *piVar3 = (param_2 & 0xffffffe0) - (int)puVar1;
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = *piVar3;
        piVar3[1] = (int)puVar1;
        piVar3[2] = 0;
        return iVar2;
      }
      piVar3 = piVar3 + 3;
      iVar2 = iVar2 + 1;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  return -1;
}



// ==== 801fff9c  gnt4-OSDestroyHeap-bl ====

void gnt4_OSDestroyHeap_bl(int param_1)

{
  *(undefined4 *)(DAT_80436408 + param_1 * 0xc) = 0xffffffff;
  return;
}



// ==== 801fffb0  gnt4-OSCheckHeap-bl ====

int gnt4_OSCheckHeap_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                       undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                       int param_9,undefined4 param_10,int param_11,undefined4 param_12,
                       undefined4 param_13,undefined4 param_14,undefined4 param_15,
                       undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  
  iVar1 = 0;
  iVar2 = 0;
  if (DAT_80436408 == 0) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,0x37d,param_11,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,0,param_14,param_15,param_16);
    return -1;
  }
  if ((param_9 < 0) || (param_11 = DAT_8043640c, DAT_8043640c <= param_9)) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_OSCheckHeap__Failed_0_<__heap_&&_803a34dc,0x37e,param_11,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,DAT_80436408,param_14,param_15,
                     param_16);
    return -1;
  }
  piVar3 = (int *)(DAT_80436408 + param_9 * 0xc);
  if (*piVar3 < 0) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_OSCheckHeap__Failed_0_<__hd_>siz_803a3514,0x381,piVar3,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,DAT_80436408,param_14,param_15,
                     param_16);
    return -1;
  }
  piVar4 = (int *)piVar3[2];
  if ((piVar4 != (int *)0x0) && (*piVar4 != 0)) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_OSCheckHeap__Failed_hd_>allocate_803a353c,899,piVar3,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,param_14,param_15,param_16);
    return -1;
  }
  while (piVar4 != (int *)0x0) {
    if ((piVar4 < DAT_80436410) || (DAT_80436414 <= piVar4)) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_InRange_cell_803a358c,0x386,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar4,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if (((uint)piVar4 & 0x1f) != 0) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_OFFSET_cell__803a35cc,0x387,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar4,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    piVar6 = (int *)piVar4[1];
    if ((piVar6 != (int *)0x0) && ((int *)*piVar6 != piVar4)) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_cell_>next___803a3604,0x388,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar6,piVar4,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    uVar5 = piVar4[2];
    if (uVar5 < 0x40) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_MINOBJSIZE_<_803a3650,0x389,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar6,uVar5,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if ((uVar5 & 0x1f) != 0) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_OFFSET_cell__803a3684,0x38a,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar6,uVar5,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    iVar1 = iVar1 + uVar5;
    if ((iVar1 < 1) || (piVar4 = piVar6, *piVar3 < iVar1)) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_0_<_total_&&_803a36c4,0x38d,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar6,uVar5,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
  }
  piVar7 = (int *)piVar3[1];
  piVar4 = (int *)0x0;
  piVar6 = piVar4;
  if ((piVar7 != (int *)0x0) && (*piVar7 != 0)) {
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_OSCheckHeap__Failed_hd_>free____N_803a3700,0x395,piVar3,
                     s_OSCheckHeap__Failed_HeapArray_in_803a34b8,0,0,DAT_80436410,DAT_80436414);
    return -1;
  }
  do {
    if (piVar7 == (int *)0x0) {
      if (iVar1 == *piVar3) {
        return iVar2;
      }
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_total____hd__803a37a8,0x3a8,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if ((piVar7 < DAT_80436410) || (DAT_80436414 <= piVar7)) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_InRange_cell_803a358c,0x398,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if (((uint)piVar7 & 0x1f) != 0) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_OFFSET_cell__803a35cc,0x399,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    piVar4 = (int *)piVar7[1];
    if ((piVar4 != (int *)0x0) && ((int *)*piVar4 != piVar7)) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_cell_>next___803a3604,0x39a,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    piVar6 = (int *)piVar7[2];
    if (piVar6 < (int *)0x40) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_MINOBJSIZE_<_803a3650,0x39b,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if (((uint)piVar6 & 0x1f) != 0) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_OFFSET_cell__803a3684,0x39c,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    if ((piVar4 != (int *)0x0) && (piVar4 <= (int *)((int)piVar7 + (int)piVar6))) {
      gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_OSCheckHeap__Failed_cell_>next___803a3748,0x39d,piVar3,
                       s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                       DAT_80436414);
      return -1;
    }
    iVar1 = iVar1 + (int)piVar6;
    iVar2 = (int)piVar6 + iVar2 + -0x20;
  } while ((0 < iVar1) && (piVar7 = piVar4, iVar1 <= *piVar3));
  gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   s_OSCheckHeap__Failed_0_<_total_&&_803a36c4,0x3a1,piVar3,
                   s_OSCheckHeap__Failed_HeapArray_in_803a34b8,piVar4,piVar6,DAT_80436410,
                   DAT_80436414);
  return -1;
}



// ==== 80200310  gnt4-OSGetArenaHi-bl ====

undefined4 gnt4_OSGetArenaHi_bl(void)

{
  return DAT_80436418;
}



// ==== 80200318  gnt4-OSGetArenaLo-bl ====

undefined4 gnt4_OSGetArenaLo_bl(void)

{
  return DAT_80435c68;
}



// ==== 80200320  gnt4-OSSetArenaHi-bl ====

void gnt4_OSSetArenaHi_bl(undefined4 param_1)

{
  DAT_80436418 = param_1;
  return;
}



// ==== 80200328  gnt4-OSSetArenaLo-bl ====

void gnt4_OSSetArenaLo_bl(undefined4 param_1)

{
  DAT_80435c68 = param_1;
  return;
}



// ==== 80200330  gnt4-OSAllocFromArenaLo-bl ====

uint gnt4_OSAllocFromArenaLo_bl(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = param_2 - 1;
  uVar2 = ~uVar1 & DAT_80435c68 + uVar1;
  DAT_80435c68 = ~uVar1 & uVar2 + param_1 + uVar1;
  return uVar2;
}



// ==== 8020035c  gnt4-__OSInitAudioSystem-bl ====

void gnt4___OSInitAudioSystem_bl(void)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = gnt4_OSGetArenaHi_bl();
  gnt4_memcpy((void *)(iVar3 + -0x80),(void *)0x81000000,0x80);
  gnt4_memcpy((void *)0x81000000,&DAT_803a3850,0x80);
  gnt4_DCFlushRange_bl(0x81000000,0x80);
  DAT_cc005012 = 0x43;
  DAT_cc00500a = 0x8ac;
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 | 1;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 1) != 0);
  DAT_cc005000 = 0;
  do {
    uVar1 = DAT_cc005004;
  } while ((uVar1 & 0x8000) != 0);
  DAT_cc005020 = 0x1000000;
  DAT_cc005024 = 0;
  DAT_cc005028 = 0x20;
  uVar1 = DAT_cc00500a;
  while ((uVar1 & 0x20) == 0) {
    uVar1 = DAT_cc00500a;
  }
  DAT_cc00500a = uVar1;
  iVar3 = gnt4_OSGetTick_bl();
  do {
    iVar4 = gnt4_OSGetTick_bl();
  } while (iVar4 - iVar3 < 0x892);
  DAT_cc005020 = 0x1000000;
  DAT_cc005024 = 0;
  DAT_cc005028 = 0x20;
  uVar1 = DAT_cc00500a;
  while ((uVar1 & 0x20) == 0) {
    uVar1 = DAT_cc00500a;
  }
  DAT_cc00500a = uVar1;
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xf7ff;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 0x400) != 0);
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xfffb;
  uVar1 = DAT_cc005004;
  while ((uVar1 & 0x8000) == 0) {
    uVar1 = DAT_cc005004;
  }
  uVar1 = DAT_cc00500a;
  uVar2 = DAT_cc005006;
  DAT_cc00500a = uVar1 | 4;
  DAT_cc00500a = 0x8ac;
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 | 1;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 1) != 0);
  iVar3 = gnt4_OSGetArenaHi_bl();
  gnt4_memcpy((void *)0x81000000,(void *)(iVar3 + -0x80),0x80);
  return;
}



// ==== 80200518  gnt4-__OSStopAudioSystem-bl ====

void gnt4___OSStopAudioSystem_bl(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  
  DAT_cc00500a = 0x804;
  uVar1 = DAT_cc005036;
  DAT_cc005036 = uVar1 & 0x7fff;
  uVar1 = DAT_cc00500a;
  while ((uVar1 & 0x400) != 0) {
    uVar1 = DAT_cc00500a;
  }
  uVar1 = DAT_cc00500a;
  while ((uVar1 & 0x200) != 0) {
    uVar1 = DAT_cc00500a;
  }
  DAT_cc00500a = 0x8ac;
  DAT_cc005000 = 0;
  do {
    uVar1 = DAT_cc005004;
  } while ((uVar1 & 0x8000) != 0);
  iVar2 = gnt4_OSGetTick_bl();
  do {
    iVar3 = gnt4_OSGetTick_bl();
  } while (iVar3 - iVar2 < 0x2c);
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 | 1;
  uVar1 = DAT_cc00500a;
  while ((uVar1 & 1) != 0) {
    uVar1 = DAT_cc00500a;
  }
  return;
}



// ==== 802005f0  gnt4-DCEnable-bl ====

uint gnt4_DCEnable_bl(void)

{
  uint in_HID0;
  
  sync(0);
  return in_HID0 | 0x4000;
}



// ==== 80200604  gnt4-DCInvalidateRange-bl ====

uint gnt4_DCInvalidateRange_bl(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    dataCacheBlockInvalidate(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  return param_1;
}



// ==== 80200630  gnt4-DCFlushRange-bl ====

uint gnt4_DCFlushRange_bl(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    dataCacheBlockFlush(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  syscall();
  return param_1;
}



// ==== 80200660  gnt4-DCStoreRange-bl ====

uint gnt4_DCStoreRange_bl(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    dataCacheBlockStore(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  syscall();
  return param_1;
}



// ==== 80200690  gnt4-DCFlushRangeNoSync-bl ====

uint gnt4_DCFlushRangeNoSync_bl(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    dataCacheBlockFlush(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  return param_1;
}



// ==== 802006bc  gnt4-ICInvalidateRange-bl ====

uint gnt4_ICInvalidateRange_bl(uint param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == 0) {
    return param_1;
  }
  uVar1 = param_2 + (param_1 & 0x1f) + 0x1f >> 5;
  do {
    instructionCacheBlockInvalidate(param_1);
    param_1 = param_1 + 0x20;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  sync(0);
  instructionSynchronize();
  return param_1;
}



// ==== 802006f0  gnt4-ICFlashInvalidate-bl ====

uint gnt4_ICFlashInvalidate_bl(void)

{
  uint in_HID0;
  
  return in_HID0 | 0x800;
}



// ==== 80200700  gnt4-ICEnable-bl ====

uint gnt4_ICEnable_bl(void)

{
  uint in_HID0;
  
  instructionSynchronize();
  return in_HID0 | 0x8000;
}



// ==== 80200714  gnt4-LCDisable-bl ====

ulonglong gnt4_LCDisable_bl(void)

{
  int iVar1;
  int iVar2;
  undefined4 in_HID2;
  
  iVar1 = -0x20000000;
  iVar2 = 0x200;
  do {
    dataCacheBlockInvalidate(iVar1);
    iVar1 = iVar1 + 0x20;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return CONCAT44(iVar1,in_HID2) & 0xffffffffefffffff;
}



// ==== 8020073c  gnt4-L2GlobalInvalidate-bl ====

void gnt4_L2GlobalInvalidate_bl(void)

{
  uint uVar1;
  
  sync(0);
  gnt4_PPCMfl2cr();
  gnt4_PPCMtl2cr();
  sync(0);
  gnt4_PPCMfl2cr();
  gnt4_PPCMtl2cr();
  do {
    uVar1 = gnt4_PPCMfl2cr();
  } while ((uVar1 & 1) != 0);
  gnt4_PPCMfl2cr();
  gnt4_PPCMtl2cr();
  while (uVar1 = gnt4_PPCMfl2cr(), (uVar1 & 1) != 0) {
    gnt4_DBPrintf();
  }
  return;
}



// ==== 802007d4  gnt4-DMAErrorHandler-bl ====

void gnt4_DMAErrorHandler_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 param_9,undefined4 *param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  undefined4 uVar1;
  undefined4 uVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  ulonglong uVar4;
  
  uVar4 = gnt4_PPCMfhid2();
  uVar3 = gnt4_OSReport_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Machine_check_received_803a38fc,(int)uVar4,param_11,param_12,param_13,
                           param_14,param_15,param_16);
  uVar2 = param_10[0x67];
  uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_HID2___0x_x_SRR1___0x_x_803a3914,(int)(uVar4 >> 0x20),uVar2,param_12,
                           param_13,param_14,param_15,param_16);
  if (((uVar4 & 0xf0000000000000) == 0) || (uVar1 = extraout_r4, (param_10[0x67] & 0x200000) == 0))
  {
    uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Machine_check_was_not_DMA_locked_803a3930,extraout_r4,uVar2,param_12,
                             param_13,param_14,param_15,param_16);
    gnt4_OSDumpContext_bl
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,extraout_r4_00
               ,uVar2,param_12,param_13,param_14,param_15,param_16);
    uVar3 = gnt4_PPCHalt();
    uVar1 = extraout_r4_01;
  }
  uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_DMAErrorHandler____An_error_occu_803a3960,uVar1,uVar2,param_12,param_13
                           ,param_14,param_15,param_16);
  uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_The_following_errors_have_been_d_803a399c,extraout_r4_02,uVar2,param_12
                           ,param_13,param_14,param_15,param_16);
  uVar1 = extraout_r4_03;
  if ((uVar4 & 0x80000000000000) != 0) {
    uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s___Requested_a_locked_cache_tag_t_803a39d4,extraout_r4_03,uVar2,
                             param_12,param_13,param_14,param_15,param_16);
    uVar1 = extraout_r4_04;
  }
  if ((uVar4 & 0x40000000000000) != 0) {
    uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s___DMA_attempted_to_access_normal_803a3a14,uVar1,uVar2,param_12,
                             param_13,param_14,param_15,param_16);
    uVar1 = extraout_r4_05;
  }
  if ((uVar4 & 0x20000000000000) != 0) {
    uVar3 = gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s___DMA_missed_in_data_cache_803a3a40,uVar1,uVar2,param_12,param_13,
                             param_14,param_15,param_16);
    uVar1 = extraout_r4_06;
  }
  if ((uVar4 & 0x10000000000000) != 0) {
    gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s___DMA_queue_overflowed_803a3a60,uVar1,uVar2,param_12,param_13,param_14,
                     param_15,param_16);
  }
  gnt4_PPCMthid2();
  return;
}



// ==== 80200934  gnt4-__OSCacheInit-bl ====

void gnt4___OSCacheInit_bl(void)

{
  uint uVar1;
  
  uVar1 = gnt4_PPCMfhid0();
  if ((uVar1 & 0x8000) == 0) {
    gnt4_ICEnable_bl();
    gnt4_DBPrintf();
  }
  uVar1 = gnt4_PPCMfhid0();
  if ((uVar1 & 0x4000) == 0) {
    gnt4_DCEnable_bl();
    gnt4_DBPrintf();
  }
  uVar1 = gnt4_PPCMfl2cr();
  if ((uVar1 & 0x80000000) == 0) {
    gnt4_PPCMfmsr();
    sync(0);
    gnt4_PPCMtmsr();
    sync(0);
    sync(0);
    gnt4_PPCMfl2cr();
    gnt4_PPCMtl2cr();
    sync(0);
    gnt4_L2GlobalInvalidate_bl();
    gnt4_PPCMtmsr();
    gnt4_PPCMfl2cr();
    gnt4_PPCMtl2cr();
    gnt4_DBPrintf();
  }
  gnt4_OSSetErrorHandler_bl(1,-0x7fdff82c);
  gnt4_DBPrintf();
  return;
}



// ==== 80200a28  gnt4-__OSLoadFPUContext-bl ====

/* WARNING: Removing unreachable block (ram,0x80200ac4) */
/* WARNING: Removing unreachable block (ram,0x80200ac0) */
/* WARNING: Removing unreachable block (ram,0x80200abc) */
/* WARNING: Removing unreachable block (ram,0x80200ab8) */
/* WARNING: Removing unreachable block (ram,0x80200ab4) */
/* WARNING: Removing unreachable block (ram,0x80200ab0) */
/* WARNING: Removing unreachable block (ram,0x80200aac) */
/* WARNING: Removing unreachable block (ram,0x80200aa8) */
/* WARNING: Removing unreachable block (ram,0x80200aa4) */
/* WARNING: Removing unreachable block (ram,0x80200aa0) */
/* WARNING: Removing unreachable block (ram,0x80200a9c) */
/* WARNING: Removing unreachable block (ram,0x80200a98) */
/* WARNING: Removing unreachable block (ram,0x80200a94) */
/* WARNING: Removing unreachable block (ram,0x80200a90) */
/* WARNING: Removing unreachable block (ram,0x80200a8c) */
/* WARNING: Removing unreachable block (ram,0x80200a88) */
/* WARNING: Removing unreachable block (ram,0x80200a84) */
/* WARNING: Removing unreachable block (ram,0x80200a80) */
/* WARNING: Removing unreachable block (ram,0x80200a7c) */
/* WARNING: Removing unreachable block (ram,0x80200a78) */
/* WARNING: Removing unreachable block (ram,0x80200a74) */
/* WARNING: Removing unreachable block (ram,0x80200a70) */
/* WARNING: Removing unreachable block (ram,0x80200a6c) */
/* WARNING: Removing unreachable block (ram,0x80200a68) */
/* WARNING: Removing unreachable block (ram,0x80200a64) */
/* WARNING: Removing unreachable block (ram,0x80200a60) */
/* WARNING: Removing unreachable block (ram,0x80200a5c) */
/* WARNING: Removing unreachable block (ram,0x80200a58) */
/* WARNING: Removing unreachable block (ram,0x80200a54) */
/* WARNING: Removing unreachable block (ram,0x80200a50) */
/* WARNING: Removing unreachable block (ram,0x80200a4c) */
/* WARNING: Removing unreachable block (ram,0x80200a48) */

undefined8 gnt4___OSLoadFPUContext_bl(undefined8 param_1,undefined4 param_2,int param_3)

{
  if ((*(ushort *)(param_3 + 0x1a2) & 1) != 0) {
    param_1 = *(undefined8 *)(param_3 + 0x98);
  }
  return param_1;
}



// ==== 80200b4c  gnt4-__OSSaveFPUContext-bl ====

/* WARNING: Removing unreachable block (ram,0x80200c6c) */
/* WARNING: Removing unreachable block (ram,0x80200c68) */
/* WARNING: Removing unreachable block (ram,0x80200c64) */
/* WARNING: Removing unreachable block (ram,0x80200c60) */
/* WARNING: Removing unreachable block (ram,0x80200c5c) */
/* WARNING: Removing unreachable block (ram,0x80200c58) */
/* WARNING: Removing unreachable block (ram,0x80200c54) */
/* WARNING: Removing unreachable block (ram,0x80200c50) */
/* WARNING: Removing unreachable block (ram,0x80200c4c) */
/* WARNING: Removing unreachable block (ram,0x80200c48) */
/* WARNING: Removing unreachable block (ram,0x80200c44) */
/* WARNING: Removing unreachable block (ram,0x80200c40) */
/* WARNING: Removing unreachable block (ram,0x80200c3c) */
/* WARNING: Removing unreachable block (ram,0x80200c38) */
/* WARNING: Removing unreachable block (ram,0x80200c34) */
/* WARNING: Removing unreachable block (ram,0x80200c30) */
/* WARNING: Removing unreachable block (ram,0x80200c2c) */
/* WARNING: Removing unreachable block (ram,0x80200c28) */
/* WARNING: Removing unreachable block (ram,0x80200c24) */
/* WARNING: Removing unreachable block (ram,0x80200c20) */
/* WARNING: Removing unreachable block (ram,0x80200c1c) */
/* WARNING: Removing unreachable block (ram,0x80200c18) */
/* WARNING: Removing unreachable block (ram,0x80200c14) */
/* WARNING: Removing unreachable block (ram,0x80200c10) */
/* WARNING: Removing unreachable block (ram,0x80200c0c) */
/* WARNING: Removing unreachable block (ram,0x80200c08) */
/* WARNING: Removing unreachable block (ram,0x80200c04) */
/* WARNING: Removing unreachable block (ram,0x80200c00) */
/* WARNING: Removing unreachable block (ram,0x80200bfc) */
/* WARNING: Removing unreachable block (ram,0x80200bf8) */
/* WARNING: Removing unreachable block (ram,0x80200bf4) */
/* WARNING: Removing unreachable block (ram,0x80200bf0) */

void gnt4___OSSaveFPUContext_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int param_11)

{
  byte in_fp_fx;
  byte in_fp_fex;
  byte in_fp_vx;
  byte in_fp_ox;
  byte in_fp_ux;
  byte in_fp_zx;
  byte in_fp_xx;
  byte in_fp_vxsnan;
  byte in_fp_vxisi;
  byte in_fp_vxidi;
  byte in_fp_vxzdz;
  byte in_fp_vximz;
  byte in_fp_vxvc;
  byte in_fp_fr;
  byte in_fp_fi;
  byte in_fp_c;
  byte in_fp_cc0;
  byte in_fp_cc1;
  byte in_fp_cc2;
  byte in_fp_cc3;
  byte in_fp_reserve1;
  byte in_fp_vxsoft;
  byte in_fp_vxsqrt;
  byte in_fp_vxcvi;
  byte in_fp_ve;
  byte in_fp_oe;
  byte in_fp_ue;
  byte in_fp_ze;
  byte in_fp_xe;
  byte in_fp_ni;
  byte in_fp_rn0;
  byte in_fp_rn1;
  uint in_HID2;
  undefined8 in_f0;
  double in_f9;
  double in_f10;
  double in_f11;
  double in_f12;
  double in_f13;
  double in_f14;
  double in_f15;
  double in_f16;
  double in_f17;
  double in_f18;
  double in_f19;
  double in_f20;
  double in_f21;
  double in_f22;
  double in_f23;
  double in_f24;
  double in_f25;
  double in_f26;
  double in_f27;
  double in_f28;
  double in_f29;
  double in_f30;
  double in_f31;
  double in_ps0_1;
  double in_ps1_1;
  double in_ps2_1;
  double in_ps3_1;
  double in_ps4_1;
  double in_ps5_1;
  double in_ps6_1;
  double in_ps7_1;
  double in_ps8_1;
  double in_ps9_1;
  double in_ps10_1;
  double in_ps11_1;
  double in_ps12_1;
  double in_ps13_1;
  double in_ps14_1;
  double in_ps15_1;
  double in_ps16_1;
  double in_ps17_1;
  double in_ps18_1;
  double in_ps19_1;
  double in_ps20_1;
  double in_ps21_1;
  double in_ps22_1;
  double in_ps23_1;
  double in_ps24_1;
  double in_ps25_1;
  double in_ps26_1;
  double in_ps27_1;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  
  *(ushort *)(param_11 + 0x1a2) = *(ushort *)(param_11 + 0x1a2) | 1;
  *(undefined8 *)(param_11 + 0x90) = in_f0;
  *(double *)(param_11 + 0x98) = param_1;
  *(double *)(param_11 + 0xa0) = param_2;
  *(double *)(param_11 + 0xa8) = param_3;
  *(double *)(param_11 + 0xb0) = param_4;
  *(double *)(param_11 + 0xb8) = param_5;
  *(double *)(param_11 + 0xc0) = param_6;
  *(double *)(param_11 + 200) = param_7;
  *(double *)(param_11 + 0xd0) = param_8;
  *(double *)(param_11 + 0xd8) = in_f9;
  *(double *)(param_11 + 0xe0) = in_f10;
  *(double *)(param_11 + 0xe8) = in_f11;
  *(double *)(param_11 + 0xf0) = in_f12;
  *(double *)(param_11 + 0xf8) = in_f13;
  *(double *)(param_11 + 0x100) = in_f14;
  *(double *)(param_11 + 0x108) = in_f15;
  *(double *)(param_11 + 0x110) = in_f16;
  *(double *)(param_11 + 0x118) = in_f17;
  *(double *)(param_11 + 0x120) = in_f18;
  *(double *)(param_11 + 0x128) = in_f19;
  *(double *)(param_11 + 0x130) = in_f20;
  *(double *)(param_11 + 0x138) = in_f21;
  *(double *)(param_11 + 0x140) = in_f22;
  *(double *)(param_11 + 0x148) = in_f23;
  *(double *)(param_11 + 0x150) = in_f24;
  *(double *)(param_11 + 0x158) = in_f25;
  *(double *)(param_11 + 0x160) = in_f26;
  *(double *)(param_11 + 0x168) = in_f27;
  *(double *)(param_11 + 0x170) = in_f28;
  *(double *)(param_11 + 0x178) = in_f29;
  *(double *)(param_11 + 0x180) = in_f30;
  *(double *)(param_11 + 0x188) = in_f31;
  *(ulonglong *)(param_11 + 400) =
       (ulonglong)
       (in_fp_rn1 & 1 | (uint)in_fp_fx << 0x1f | (in_fp_fex & 1) << 0x1e | (in_fp_vx & 1) << 0x1d |
        (in_fp_ox & 1) << 0x1c | (in_fp_ux & 1) << 0x1b | (in_fp_zx & 1) << 0x1a |
        (in_fp_xx & 1) << 0x19 | (in_fp_vxsnan & 1) << 0x18 | (in_fp_vxisi & 1) << 0x17 |
        (in_fp_vxidi & 1) << 0x16 | (in_fp_vxzdz & 1) << 0x15 | (in_fp_vximz & 1) << 0x14 |
        (in_fp_vxvc & 1) << 0x13 | (in_fp_fr & 1) << 0x12 | (in_fp_fi & 1) << 0x11 |
        (in_fp_c & 1) << 0x10 | (in_fp_cc0 & 1) << 0xf | (in_fp_cc1 & 1) << 0xe |
        (in_fp_cc2 & 1) << 0xd | (in_fp_cc3 & 1) << 0xc | (in_fp_reserve1 & 1) << 0xb |
        (in_fp_vxsoft & 1) << 10 | (in_fp_vxsqrt & 1) << 9 | (in_fp_vxcvi & 1) << 8 |
        (in_fp_ve & 1) << 7 | (in_fp_oe & 1) << 6 | (in_fp_ue & 1) << 5 | (in_fp_ze & 1) << 4 |
        (in_fp_xe & 1) << 3 | (in_fp_ni & 1) << 2 | (in_fp_rn0 & 1) << 1);
  if ((in_HID2 >> 0x1d & 1) != 0) {
    *(float *)(param_11 + 0x1c8) = (float)*(double *)(param_11 + 0x90);
    *(float *)(param_11 + 0x1cc) = (float)in_ps0_1;
    *(float *)(param_11 + 0x1d0) = (float)param_1;
    *(float *)(param_11 + 0x1d4) = (float)in_ps1_1;
    *(float *)(param_11 + 0x1d8) = (float)param_2;
    *(float *)(param_11 + 0x1dc) = (float)in_ps2_1;
    *(float *)(param_11 + 0x1e0) = (float)param_3;
    *(float *)(param_11 + 0x1e4) = (float)in_ps3_1;
    *(float *)(param_11 + 0x1e8) = (float)param_4;
    *(float *)(param_11 + 0x1ec) = (float)in_ps4_1;
    *(float *)(param_11 + 0x1f0) = (float)param_5;
    *(float *)(param_11 + 500) = (float)in_ps5_1;
    *(float *)(param_11 + 0x1f8) = (float)param_6;
    *(float *)(param_11 + 0x1fc) = (float)in_ps6_1;
    *(float *)(param_11 + 0x200) = (float)param_7;
    *(float *)(param_11 + 0x204) = (float)in_ps7_1;
    *(float *)(param_11 + 0x208) = (float)param_8;
    *(float *)(param_11 + 0x20c) = (float)in_ps8_1;
    *(float *)(param_11 + 0x210) = (float)in_f9;
    *(float *)(param_11 + 0x214) = (float)in_ps9_1;
    *(float *)(param_11 + 0x218) = (float)in_f10;
    *(float *)(param_11 + 0x21c) = (float)in_ps10_1;
    *(float *)(param_11 + 0x220) = (float)in_f11;
    *(float *)(param_11 + 0x224) = (float)in_ps11_1;
    *(float *)(param_11 + 0x228) = (float)in_f12;
    *(float *)(param_11 + 0x22c) = (float)in_ps12_1;
    *(float *)(param_11 + 0x230) = (float)in_f13;
    *(float *)(param_11 + 0x234) = (float)in_ps13_1;
    *(float *)(param_11 + 0x238) = (float)in_f14;
    *(float *)(param_11 + 0x23c) = (float)in_ps14_1;
    *(float *)(param_11 + 0x240) = (float)in_f15;
    *(float *)(param_11 + 0x244) = (float)in_ps15_1;
    *(float *)(param_11 + 0x248) = (float)in_f16;
    *(float *)(param_11 + 0x24c) = (float)in_ps16_1;
    *(float *)(param_11 + 0x250) = (float)in_f17;
    *(float *)(param_11 + 0x254) = (float)in_ps17_1;
    *(float *)(param_11 + 600) = (float)in_f18;
    *(float *)(param_11 + 0x25c) = (float)in_ps18_1;
    *(float *)(param_11 + 0x260) = (float)in_f19;
    *(float *)(param_11 + 0x264) = (float)in_ps19_1;
    *(float *)(param_11 + 0x268) = (float)in_f20;
    *(float *)(param_11 + 0x26c) = (float)in_ps20_1;
    *(float *)(param_11 + 0x270) = (float)in_f21;
    *(float *)(param_11 + 0x274) = (float)in_ps21_1;
    *(float *)(param_11 + 0x278) = (float)in_f22;
    *(float *)(param_11 + 0x27c) = (float)in_ps22_1;
    *(float *)(param_11 + 0x280) = (float)in_f23;
    *(float *)(param_11 + 0x284) = (float)in_ps23_1;
    *(float *)(param_11 + 0x288) = (float)in_f24;
    *(float *)(param_11 + 0x28c) = (float)in_ps24_1;
    *(float *)(param_11 + 0x290) = (float)in_f25;
    *(float *)(param_11 + 0x294) = (float)in_ps25_1;
    *(float *)(param_11 + 0x298) = (float)in_f26;
    *(float *)(param_11 + 0x29c) = (float)in_ps26_1;
    *(float *)(param_11 + 0x2a0) = (float)in_f27;
    *(float *)(param_11 + 0x2a4) = (float)in_ps27_1;
    *(float *)(param_11 + 0x2a8) = (float)in_f28;
    *(float *)(param_11 + 0x2ac) = (float)in_ps28_1;
    *(float *)(param_11 + 0x2b0) = (float)in_f29;
    *(float *)(param_11 + 0x2b4) = (float)in_ps29_1;
    *(float *)(param_11 + 0x2b8) = (float)in_f30;
    *(float *)(param_11 + 700) = (float)in_ps30_1;
    *(float *)(param_11 + 0x2c0) = (float)in_f31;
    *(float *)(param_11 + 0x2c4) = (float)in_ps31_1;
  }
  return;
}



// ==== 80200c74  gnt4-OSSaveFPUContext-bl ====

void gnt4_OSSaveFPUContext_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10)

{
  gnt4___OSSaveFPUContext_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             param_9);
  return;
}



// ==== 80200c7c  gnt4-OSSetCurrentContext-bl ====

void gnt4_OSSetCurrentContext_bl(uint param_1)

{
  DAT_800000c0 = param_1 & 0x3fffffff;
  DAT_800000d4 = param_1;
  if (DAT_800000d8 == param_1) {
    *(uint *)(param_1 + 0x19c) = *(uint *)(param_1 + 0x19c) | 0x2000;
    return;
  }
  *(uint *)(param_1 + 0x19c) = *(uint *)(param_1 + 0x19c) & 0xffffdfff;
  instructionSynchronize();
  return;
}



// ==== 80200cd8  gnt4-OSGetCurrentContext-bl ====

undefined4 gnt4_OSGetCurrentContext_bl(void)

{
  return DAT_800000d4;
}



// ==== 80200ce4  gnt4-OSSaveContext-bl ====

undefined4 gnt4_OSSaveContext_bl(int param_1)

{
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  undefined4 in_MSR;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  
  *(float **)(param_1 + 0x34) = &FLOAT_8043b5a0;
  *(undefined4 *)(param_1 + 0x38) = unaff_r14;
  *(undefined4 *)(param_1 + 0x3c) = unaff_r15;
  *(undefined4 *)(param_1 + 0x40) = unaff_r16;
  *(undefined4 *)(param_1 + 0x44) = unaff_r17;
  *(undefined4 *)(param_1 + 0x48) = unaff_r18;
  *(undefined4 *)(param_1 + 0x4c) = unaff_r19;
  *(undefined4 *)(param_1 + 0x50) = unaff_r20;
  *(undefined4 *)(param_1 + 0x54) = unaff_r21;
  *(undefined4 *)(param_1 + 0x58) = unaff_r22;
  *(undefined4 *)(param_1 + 0x5c) = unaff_r23;
  *(undefined4 *)(param_1 + 0x60) = unaff_r24;
  *(undefined4 *)(param_1 + 100) = unaff_r25;
  *(undefined4 *)(param_1 + 0x68) = unaff_r26;
  *(undefined4 *)(param_1 + 0x6c) = unaff_r27;
  *(undefined4 *)(param_1 + 0x70) = unaff_r28;
  *(undefined4 *)(param_1 + 0x74) = unaff_r29;
  *(undefined4 *)(param_1 + 0x78) = unaff_r30;
  *(undefined4 *)(param_1 + 0x7c) = unaff_r31;
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  *(undefined4 *)(param_1 + 0x1ac) = 0x40004;
  *(undefined4 *)(param_1 + 0x1b0) = 0x50005;
  *(undefined4 *)(param_1 + 0x1b4) = 0x60006;
  *(undefined4 *)(param_1 + 0x1b8) = 0x70007;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(uint *)(param_1 + 0x80) =
       (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14 |
       (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
       (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  *(undefined4 *)(param_1 + 0x84) = in_LR;
  *(undefined4 *)(param_1 + 0x198) = in_LR;
  *(undefined4 *)(param_1 + 0x19c) = in_MSR;
  *(undefined4 *)(param_1 + 0x88) = in_CTR;
  *(undefined4 *)(param_1 + 0x8c) = in_XER;
  *(BADSPACEBASE **)(param_1 + 4) = register0x00000004;
  *(undefined1 **)(param_1 + 8) = &DAT_8043ea20;
  *(undefined4 *)(param_1 + 0xc) = 1;
  return 0;
}



// ==== 80200d64  gnt4-OSLoadContext-bl ====

undefined8 gnt4_OSLoadContext_bl(int param_1)

{
  uint in_MSR;
  
  if ((gnt4_OSDisableInterrupts_bl < *(code **)(param_1 + 0x198)) &&
     (*(code **)(param_1 + 0x198) < (code *)0x802037c0)) {
    *(code **)(param_1 + 0x198) = gnt4_OSDisableInterrupts_bl;
  }
  if ((*(ushort *)(param_1 + 0x1a2) & 2) != 0) {
    *(ushort *)(param_1 + 0x1a2) = *(ushort *)(param_1 + 0x1a2) & 0xfffd;
  }
  returnFromInterrupt(in_MSR & 0x9000,*(undefined4 *)(param_1 + 0x19c));
  return *(undefined8 *)(param_1 + 0xc);
}



// ==== 80200e3c  gnt4-OSGetStackPointer-bl ====

undefined1 * gnt4_OSGetStackPointer_bl(void)

{
  return &stack0x00000000;
}



// ==== 80200e44  zz_0200e44_ ====

void zz_0200e44_(undefined *param_1,int param_2)

{
  *(BADSPACEBASE **)(param_2 + -8) = register0x00000004;
  (*(code *)param_1)();
  return;
}



// ==== 80200e74  gnt4-OSClearContext-bl ====

void gnt4_OSClearContext_bl(int param_1)

{
  *(undefined2 *)(param_1 + 0x1a0) = 0;
  *(undefined2 *)(param_1 + 0x1a2) = 0;
  if (param_1 == DAT_800000d8) {
    DAT_800000d8 = 0;
  }
  return;
}



// ==== 80200e98  gnt4-OSInitContext-bl ====

void gnt4_OSInitContext_bl(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x198) = param_2;
  *(undefined4 *)(param_1 + 4) = param_3;
  *(undefined4 *)(param_1 + 0x19c) = 0x9032;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined1 **)(param_1 + 8) = &DAT_8043ea20;
  *(float **)(param_1 + 0x34) = &FLOAT_8043b5a0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x78) = 0;
  *(undefined4 *)(param_1 + 0x7c) = 0;
  *(undefined4 *)(param_1 + 0x1a4) = 0;
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  *(undefined4 *)(param_1 + 0x1ac) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  gnt4_OSClearContext_bl(param_1);
  return;
}



// ==== 80200f54  gnt4-OSDumpContext-bl ====

void gnt4_OSDumpContext_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined8 uVar12;
  double dVar13;
  undefined1 auStack_2e8 [416];
  undefined2 local_148;
  undefined2 local_146;
  
  uVar12 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s___________________________Contex_803a3b00,param_9,param_11,param_12,
                            param_13,param_14,param_15,param_16);
  uVar9 = 0;
  puVar11 = param_9;
  do {
    uVar7 = puVar11[0x10];
    uVar2 = *puVar11;
    iVar6 = uVar9 + 0x10;
    uVar8 = uVar7;
    uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_r__2d___0x_08x___14d__r__2d___0x_803a3b44,uVar9,uVar2,uVar2,iVar6,
                              uVar7,uVar7,param_16);
    puVar11 = puVar11 + 1;
    uVar9 = uVar9 + 1;
  } while (uVar9 < 0x10);
  uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_LR___0x_08x_CR___0x_08x_803a3b74,param_9[0x21],param_9[0x20],uVar2,
                            iVar6,uVar7,uVar8,param_16);
  uVar3 = param_9[0x67];
  uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_SRR0___0x_08x_SRR1___0x_08x_803a3ba4,param_9[0x66],uVar3,uVar2,iVar6,
                            uVar7,uVar8,param_16);
  uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_GQRs___________803a3bd4,extraout_r4,uVar3,uVar2,iVar6,uVar7,uVar8,
                            param_16);
  uVar9 = 0;
  puVar11 = param_9;
  do {
    uVar2 = puVar11[0x69];
    iVar6 = puVar11[0x6d];
    iVar4 = uVar9 + 4;
    uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_gqr_d___0x_08x_gqr_d___0x_08x_803a3be8,uVar9,uVar2,iVar4,iVar6,uVar7
                              ,uVar8,param_16);
    puVar11 = puVar11 + 1;
    uVar9 = uVar9 + 1;
  } while (uVar9 < 4);
  uVar3 = extraout_r4_00;
  if ((*(ushort *)((int)param_9 + 0x1a2) & 1) != 0) {
    gnt4_OSDisableInterrupts_bl();
    uVar9 = DAT_800000d4;
    uVar3 = 0x80000000;
    uVar2 = 0;
    local_148 = 0;
    local_146 = 0;
    if (auStack_2e8 == DAT_800000d8) {
      DAT_800000d8 = (undefined1 *)0x0;
    }
    uVar12 = gnt4_OSSetCurrentContext_bl((uint)auStack_2e8);
    gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_FPRs___________803a3c0c,extraout_r4_01,uVar2,uVar3,iVar6,uVar7,uVar8,param_16
                    );
    uVar10 = 0;
    puVar11 = param_9;
    do {
      iVar6 = gnt4___cvt_fp2unsigned_bl(*(double *)(puVar11 + 0x26));
      dVar13 = *(double *)(puVar11 + 0x24);
      iVar4 = gnt4___cvt_fp2unsigned_bl(dVar13);
      iVar5 = uVar10 + 1;
      uVar12 = gnt4_OSReport_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                s_fr_d____d_fr_d____d_803a3c20,uVar10,iVar4,iVar5,iVar6,uVar7,uVar8,
                                param_16);
      puVar11 = puVar11 + 4;
      uVar10 = uVar10 + 2;
    } while (uVar10 < 0x20);
    gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_PSFs___________803a3c3c,extraout_r4_02,iVar4,iVar5,iVar6,uVar7,uVar8,param_16
                    );
    uVar10 = 0;
    puVar11 = param_9;
    do {
      iVar6 = gnt4___cvt_fp2unsigned_bl(*(double *)(puVar11 + 0x74));
      dVar13 = *(double *)(puVar11 + 0x72);
      iVar5 = gnt4___cvt_fp2unsigned_bl(dVar13);
      iVar4 = uVar10 + 1;
      gnt4_OSReport_bl(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       s_ps_d___0x_x_ps_d___0x_x_803a3c50,uVar10,iVar5,iVar4,iVar6,uVar7,uVar8,
                       param_16);
      puVar11 = puVar11 + 4;
      uVar10 = uVar10 + 2;
    } while (uVar10 < 0x20);
    uVar2 = 0;
    local_148 = 0;
    local_146 = 0;
    if (auStack_2e8 == DAT_800000d8) {
      DAT_800000d8 = (undefined1 *)0x0;
    }
    uVar12 = gnt4_OSSetCurrentContext_bl(uVar9);
    uVar3 = extraout_r4_03;
    gnt4_OSRestoreInterrupts_bl();
  }
  uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_Address__Back_Chain_LR_Save_803a3c70,uVar3,uVar2,iVar4,iVar6,uVar7,
                            uVar8,param_16);
  puVar11 = (undefined4 *)param_9[1];
  uVar9 = 0;
  while (((puVar11 != (undefined4 *)0x0 && (puVar11 != (undefined4 *)0xffffffff)) &&
         (bVar1 = uVar9 < 0x10, uVar9 = uVar9 + 1, bVar1))) {
    uVar12 = gnt4_OSReport_bl(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_0x_08x__0x_08x_0x_08x_803a3c98,puVar11,*puVar11,puVar11[1],iVar6,
                              uVar7,uVar8,param_16);
    puVar11 = (undefined4 *)*puVar11;
  }
  return;
}



// ==== 802011fc  gnt4-SwitchFPUContext-bl ====

undefined8
gnt4_SwitchFPUContext_bl
          (double param_1,double param_2,double param_3,double param_4,double param_5,double param_6
          ,double param_7,double param_8,undefined4 param_9,int param_10)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint in_MSR;
  uint uVar6;
  double extraout_f1;
  undefined8 uVar7;
  
  iVar2 = DAT_800000d8;
  uVar6 = in_MSR & 0x9000;
  instructionSynchronize();
  uVar5 = *(uint *)(param_10 + 0x19c) | 0x2000;
  uVar4 = 0x80000000;
  iVar3 = param_10;
  if (DAT_800000d8 != param_10) {
    bVar1 = DAT_800000d8 != 0;
    DAT_800000d8 = param_10;
    if (bVar1) {
      uVar7 = gnt4___OSSaveFPUContext_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x80000000,
                         param_10,iVar2);
      uVar4 = (undefined4)((ulonglong)uVar7 >> 0x20);
      param_10 = (int)uVar7;
      param_1 = extraout_f1;
    }
    gnt4___OSLoadFPUContext_bl(param_1,uVar4,param_10);
    iVar3 = DAT_800000d8;
  }
  DAT_800000d8 = iVar3;
  *(ushort *)(param_10 + 0x1a2) = *(ushort *)(param_10 + 0x1a2) & 0xfffd;
  returnFromInterrupt(uVar6,uVar5);
  return *(undefined8 *)(param_10 + 0xc);
}



// ==== 80201280  gnt4-__OSContextInit-bl ====

void gnt4___OSContextInit_bl(void)

{
  gnt4___OSSetExceptionHandler_bl(7,gnt4_SwitchFPUContext_bl);
  DAT_800000d8 = 0;
  gnt4_DBPrintf();
  return;
}



// ==== 802012c8  gnt4-OSFillFPUContext-bl ====

/* WARNING: Removing unreachable block (ram,0x802013ec) */
/* WARNING: Removing unreachable block (ram,0x802013e8) */
/* WARNING: Removing unreachable block (ram,0x802013e4) */
/* WARNING: Removing unreachable block (ram,0x802013e0) */
/* WARNING: Removing unreachable block (ram,0x802013dc) */
/* WARNING: Removing unreachable block (ram,0x802013d8) */
/* WARNING: Removing unreachable block (ram,0x802013d4) */
/* WARNING: Removing unreachable block (ram,0x802013d0) */
/* WARNING: Removing unreachable block (ram,0x802013cc) */
/* WARNING: Removing unreachable block (ram,0x802013c8) */
/* WARNING: Removing unreachable block (ram,0x802013c4) */
/* WARNING: Removing unreachable block (ram,0x802013c0) */
/* WARNING: Removing unreachable block (ram,0x802013bc) */
/* WARNING: Removing unreachable block (ram,0x802013b8) */
/* WARNING: Removing unreachable block (ram,0x802013b4) */
/* WARNING: Removing unreachable block (ram,0x802013b0) */
/* WARNING: Removing unreachable block (ram,0x802013ac) */
/* WARNING: Removing unreachable block (ram,0x802013a8) */
/* WARNING: Removing unreachable block (ram,0x802013a4) */
/* WARNING: Removing unreachable block (ram,0x802013a0) */
/* WARNING: Removing unreachable block (ram,0x8020139c) */
/* WARNING: Removing unreachable block (ram,0x80201398) */
/* WARNING: Removing unreachable block (ram,0x80201394) */
/* WARNING: Removing unreachable block (ram,0x80201390) */
/* WARNING: Removing unreachable block (ram,0x8020138c) */
/* WARNING: Removing unreachable block (ram,0x80201388) */
/* WARNING: Removing unreachable block (ram,0x80201384) */
/* WARNING: Removing unreachable block (ram,0x80201380) */
/* WARNING: Removing unreachable block (ram,0x8020137c) */
/* WARNING: Removing unreachable block (ram,0x80201378) */
/* WARNING: Removing unreachable block (ram,0x80201374) */
/* WARNING: Removing unreachable block (ram,0x80201370) */

void gnt4_OSFillFPUContext_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9)

{
  byte in_fp_fx;
  byte in_fp_fex;
  byte in_fp_vx;
  byte in_fp_ox;
  byte in_fp_ux;
  byte in_fp_zx;
  byte in_fp_xx;
  byte in_fp_vxsnan;
  byte in_fp_vxisi;
  byte in_fp_vxidi;
  byte in_fp_vxzdz;
  byte in_fp_vximz;
  byte in_fp_vxvc;
  byte in_fp_fr;
  byte in_fp_fi;
  byte in_fp_c;
  byte in_fp_cc0;
  byte in_fp_cc1;
  byte in_fp_cc2;
  byte in_fp_cc3;
  byte in_fp_reserve1;
  byte in_fp_vxsoft;
  byte in_fp_vxsqrt;
  byte in_fp_vxcvi;
  byte in_fp_ve;
  byte in_fp_oe;
  byte in_fp_ue;
  byte in_fp_ze;
  byte in_fp_xe;
  byte in_fp_ni;
  byte in_fp_rn0;
  byte in_fp_rn1;
  uint in_HID2;
  undefined8 in_f0;
  double in_f9;
  double in_f10;
  double in_f11;
  double in_f12;
  double in_f13;
  double in_f14;
  double in_f15;
  double in_f16;
  double in_f17;
  double in_f18;
  double in_f19;
  double in_f20;
  double in_f21;
  double in_f22;
  double in_f23;
  double in_f24;
  double in_f25;
  double in_f26;
  double in_f27;
  double in_f28;
  double in_f29;
  double in_f30;
  double in_f31;
  double in_ps0_1;
  double in_ps1_1;
  double in_ps2_1;
  double in_ps3_1;
  double in_ps4_1;
  double in_ps5_1;
  double in_ps6_1;
  double in_ps7_1;
  double in_ps8_1;
  double in_ps9_1;
  double in_ps10_1;
  double in_ps11_1;
  double in_ps12_1;
  double in_ps13_1;
  double in_ps14_1;
  double in_ps15_1;
  double in_ps16_1;
  double in_ps17_1;
  double in_ps18_1;
  double in_ps19_1;
  double in_ps20_1;
  double in_ps21_1;
  double in_ps22_1;
  double in_ps23_1;
  double in_ps24_1;
  double in_ps25_1;
  double in_ps26_1;
  double in_ps27_1;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  
  instructionSynchronize();
  *(undefined8 *)(param_9 + 0x90) = in_f0;
  *(double *)(param_9 + 0x98) = param_1;
  *(double *)(param_9 + 0xa0) = param_2;
  *(double *)(param_9 + 0xa8) = param_3;
  *(double *)(param_9 + 0xb0) = param_4;
  *(double *)(param_9 + 0xb8) = param_5;
  *(double *)(param_9 + 0xc0) = param_6;
  *(double *)(param_9 + 200) = param_7;
  *(double *)(param_9 + 0xd0) = param_8;
  *(double *)(param_9 + 0xd8) = in_f9;
  *(double *)(param_9 + 0xe0) = in_f10;
  *(double *)(param_9 + 0xe8) = in_f11;
  *(double *)(param_9 + 0xf0) = in_f12;
  *(double *)(param_9 + 0xf8) = in_f13;
  *(double *)(param_9 + 0x100) = in_f14;
  *(double *)(param_9 + 0x108) = in_f15;
  *(double *)(param_9 + 0x110) = in_f16;
  *(double *)(param_9 + 0x118) = in_f17;
  *(double *)(param_9 + 0x120) = in_f18;
  *(double *)(param_9 + 0x128) = in_f19;
  *(double *)(param_9 + 0x130) = in_f20;
  *(double *)(param_9 + 0x138) = in_f21;
  *(double *)(param_9 + 0x140) = in_f22;
  *(double *)(param_9 + 0x148) = in_f23;
  *(double *)(param_9 + 0x150) = in_f24;
  *(double *)(param_9 + 0x158) = in_f25;
  *(double *)(param_9 + 0x160) = in_f26;
  *(double *)(param_9 + 0x168) = in_f27;
  *(double *)(param_9 + 0x170) = in_f28;
  *(double *)(param_9 + 0x178) = in_f29;
  *(double *)(param_9 + 0x180) = in_f30;
  *(double *)(param_9 + 0x188) = in_f31;
  *(ulonglong *)(param_9 + 400) =
       (ulonglong)
       (in_fp_rn1 & 1 | (uint)in_fp_fx << 0x1f | (in_fp_fex & 1) << 0x1e | (in_fp_vx & 1) << 0x1d |
        (in_fp_ox & 1) << 0x1c | (in_fp_ux & 1) << 0x1b | (in_fp_zx & 1) << 0x1a |
        (in_fp_xx & 1) << 0x19 | (in_fp_vxsnan & 1) << 0x18 | (in_fp_vxisi & 1) << 0x17 |
        (in_fp_vxidi & 1) << 0x16 | (in_fp_vxzdz & 1) << 0x15 | (in_fp_vximz & 1) << 0x14 |
        (in_fp_vxvc & 1) << 0x13 | (in_fp_fr & 1) << 0x12 | (in_fp_fi & 1) << 0x11 |
        (in_fp_c & 1) << 0x10 | (in_fp_cc0 & 1) << 0xf | (in_fp_cc1 & 1) << 0xe |
        (in_fp_cc2 & 1) << 0xd | (in_fp_cc3 & 1) << 0xc | (in_fp_reserve1 & 1) << 0xb |
        (in_fp_vxsoft & 1) << 10 | (in_fp_vxsqrt & 1) << 9 | (in_fp_vxcvi & 1) << 8 |
        (in_fp_ve & 1) << 7 | (in_fp_oe & 1) << 6 | (in_fp_ue & 1) << 5 | (in_fp_ze & 1) << 4 |
        (in_fp_xe & 1) << 3 | (in_fp_ni & 1) << 2 | (in_fp_rn0 & 1) << 1);
  if ((in_HID2 >> 0x1d & 1) != 0) {
    *(float *)(param_9 + 0x1c8) = (float)*(double *)(param_9 + 0x90);
    *(float *)(param_9 + 0x1cc) = (float)in_ps0_1;
    *(float *)(param_9 + 0x1d0) = (float)param_1;
    *(float *)(param_9 + 0x1d4) = (float)in_ps1_1;
    *(float *)(param_9 + 0x1d8) = (float)param_2;
    *(float *)(param_9 + 0x1dc) = (float)in_ps2_1;
    *(float *)(param_9 + 0x1e0) = (float)param_3;
    *(float *)(param_9 + 0x1e4) = (float)in_ps3_1;
    *(float *)(param_9 + 0x1e8) = (float)param_4;
    *(float *)(param_9 + 0x1ec) = (float)in_ps4_1;
    *(float *)(param_9 + 0x1f0) = (float)param_5;
    *(float *)(param_9 + 500) = (float)in_ps5_1;
    *(float *)(param_9 + 0x1f8) = (float)param_6;
    *(float *)(param_9 + 0x1fc) = (float)in_ps6_1;
    *(float *)(param_9 + 0x200) = (float)param_7;
    *(float *)(param_9 + 0x204) = (float)in_ps7_1;
    *(float *)(param_9 + 0x208) = (float)param_8;
    *(float *)(param_9 + 0x20c) = (float)in_ps8_1;
    *(float *)(param_9 + 0x210) = (float)in_f9;
    *(float *)(param_9 + 0x214) = (float)in_ps9_1;
    *(float *)(param_9 + 0x218) = (float)in_f10;
    *(float *)(param_9 + 0x21c) = (float)in_ps10_1;
    *(float *)(param_9 + 0x220) = (float)in_f11;
    *(float *)(param_9 + 0x224) = (float)in_ps11_1;
    *(float *)(param_9 + 0x228) = (float)in_f12;
    *(float *)(param_9 + 0x22c) = (float)in_ps12_1;
    *(float *)(param_9 + 0x230) = (float)in_f13;
    *(float *)(param_9 + 0x234) = (float)in_ps13_1;
    *(float *)(param_9 + 0x238) = (float)in_f14;
    *(float *)(param_9 + 0x23c) = (float)in_ps14_1;
    *(float *)(param_9 + 0x240) = (float)in_f15;
    *(float *)(param_9 + 0x244) = (float)in_ps15_1;
    *(float *)(param_9 + 0x248) = (float)in_f16;
    *(float *)(param_9 + 0x24c) = (float)in_ps16_1;
    *(float *)(param_9 + 0x250) = (float)in_f17;
    *(float *)(param_9 + 0x254) = (float)in_ps17_1;
    *(float *)(param_9 + 600) = (float)in_f18;
    *(float *)(param_9 + 0x25c) = (float)in_ps18_1;
    *(float *)(param_9 + 0x260) = (float)in_f19;
    *(float *)(param_9 + 0x264) = (float)in_ps19_1;
    *(float *)(param_9 + 0x268) = (float)in_f20;
    *(float *)(param_9 + 0x26c) = (float)in_ps20_1;
    *(float *)(param_9 + 0x270) = (float)in_f21;
    *(float *)(param_9 + 0x274) = (float)in_ps21_1;
    *(float *)(param_9 + 0x278) = (float)in_f22;
    *(float *)(param_9 + 0x27c) = (float)in_ps22_1;
    *(float *)(param_9 + 0x280) = (float)in_f23;
    *(float *)(param_9 + 0x284) = (float)in_ps23_1;
    *(float *)(param_9 + 0x288) = (float)in_f24;
    *(float *)(param_9 + 0x28c) = (float)in_ps24_1;
    *(float *)(param_9 + 0x290) = (float)in_f25;
    *(float *)(param_9 + 0x294) = (float)in_ps25_1;
    *(float *)(param_9 + 0x298) = (float)in_f26;
    *(float *)(param_9 + 0x29c) = (float)in_ps26_1;
    *(float *)(param_9 + 0x2a0) = (float)in_f27;
    *(float *)(param_9 + 0x2a4) = (float)in_ps27_1;
    *(float *)(param_9 + 0x2a8) = (float)in_f28;
    *(float *)(param_9 + 0x2ac) = (float)in_ps28_1;
    *(float *)(param_9 + 0x2b0) = (float)in_f29;
    *(float *)(param_9 + 0x2b4) = (float)in_ps29_1;
    *(float *)(param_9 + 0x2b8) = (float)in_f30;
    *(float *)(param_9 + 700) = (float)in_ps30_1;
    *(float *)(param_9 + 0x2c0) = (float)in_f31;
    *(float *)(param_9 + 0x2c4) = (float)in_ps31_1;
  }
  return;
}



