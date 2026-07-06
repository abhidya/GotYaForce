// ==== 8015bf54  FUN_8015bf54 ====

void FUN_8015bf54(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043a770;
  fVar1 = FLOAT_8043a768;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x1964) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1964) ^ 0x80000000) -
                             DOUBLE_8043a770) * FLOAT_8043a768);
    *(short *)(param_1 + 0x1970) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1970) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 8015bfd0  FUN_8015bfd0 ====

void FUN_8015bfd0(char *param_1)

{
  if (*(short *)(param_1 + 1000) == 0x612) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
      zz_00f036c_((int)param_1,0xb2);
      zz_006a8c0_(param_1,0x610);
      zz_005f00c_((int)param_1);
      zz_017a608_((int)param_1);
    }
  }
  else if ((*(short *)(param_1 + 1000) == 0x624) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0))
  {
    zz_00f036c_((int)param_1,0xb2);
    zz_006a8c0_(param_1,0x623);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}



// ==== 8015c084  FUN_8015c084 ====

void FUN_8015c084(int param_1)

{
  (*(code *)(&PTR_FUN_80346250)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8015c0c0  FUN_8015c0c0 ====

void FUN_8015c0c0(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  double dVar6;
  float local_28;
  undefined4 local_24;
  float local_20;
  double local_18;
  double local_10;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    fVar1 = FLOAT_8043a778;
    *(undefined1 *)(param_1 + 0x6ea) = 5;
    dVar6 = (double)FLOAT_8043a77c;
    *(float *)(param_1 + 0x558) = fVar1;
    zz_004beb8_(dVar6,param_1,0xf,0,0,0xffffffff,0xffffffff);
  }
  zz_004cd24_(param_1,0xf);
  if (FLOAT_8043a778 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    return;
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a780;
  local_28 = *(float *)(param_1 + 0x8dc);
  local_24 = *(undefined4 *)(param_1 + 0x8ec);
  local_20 = *(float *)(param_1 + 0x8fc);
  iVar3 = FUN_800452a0((double)local_28,(double)local_20);
  local_28 = *(float *)(param_1 + 0xd60);
  local_24 = *(undefined4 *)(param_1 + 0xd70);
  local_20 = *(float *)(param_1 + 0xd80);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
  iVar4 = FUN_800452a0((double)local_28,(double)local_20);
  sVar2 = (short)iVar4 - (short)iVar3;
  if ((sVar2 < 0x2000) && (-0x2000 < sVar2)) {
    if (0x800 < sVar2) {
      sVar2 = 0x800;
    }
    if (sVar2 < -0x800) {
      sVar2 = -0x800;
    }
    *(short *)(param_1 + 0x1964) = -sVar2;
  }
  else {
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1964)) ^ 0x80000000);
    iVar4 = (int)((float)(local_18 - DOUBLE_8043a770) * FLOAT_8043a768);
    local_10 = (double)(longlong)iVar4;
    *(short *)(param_1 + 0x1964) = (short)iVar4;
  }
  local_28 = *(float *)(param_1 + 0xdc0);
  local_24 = *(undefined4 *)(param_1 + 0xdd0);
  local_20 = *(float *)(param_1 + 0xde0);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
  iVar4 = FUN_800452a0((double)local_28,(double)local_20);
  sVar2 = (short)iVar4 - (short)iVar3;
  if ((sVar2 < 0x2000) && (-0x2000 < sVar2)) {
    if (0x800 < sVar2) {
      sVar2 = 0x800;
    }
    if (sVar2 < -0x800) {
      sVar2 = -0x800;
    }
    *(short *)(param_1 + 0x1970) = sVar2;
  }
  else {
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1970)) ^ 0x80000000);
    iVar3 = (int)((float)(local_10 - DOUBLE_8043a770) * FLOAT_8043a768);
    local_18 = (double)(longlong)iVar3;
    *(short *)(param_1 + 0x1970) = (short)iVar3;
  }
  cVar5 = *(char *)(param_1 + 0x6ea) + -1;
  *(char *)(param_1 + 0x6ea) = cVar5;
  if ((-1 < cVar5) && (iVar3 = zz_006dbe0_(param_1,0,1,0), iVar3 != 0)) {
    zz_006bda8_(param_1);
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x612) {
        zz_0082824_(param_1,0x2e);
        zz_0082824_(param_1,0x2f);
      }
      else if (sVar2 == 0x620) {
        zz_0082824_(param_1,0x5d);
        zz_0082824_(param_1,0x5e);
      }
      else if (sVar2 == 0x624) {
        zz_0082824_(param_1,0x5f);
        zz_0082824_(param_1,0x60);
      }
      else if (sVar2 == 0x626) {
        zz_0082824_(param_1,0x61);
        zz_0082824_(param_1,0x62);
      }
    }
    zz_004beb8_((double)FLOAT_8043a77c,param_1,0xf,2,1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,8);
    zz_004beb8_((double)FLOAT_8043a77c,param_1,0xf,0,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8015c430  FUN_8015c430 ====

void FUN_8015c430(char *param_1)

{
  param_1[0x580] = '\x03';
  param_1[0x581] = '\0';
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    param_1[0x581] = '\x03';
  }
  zz_00f036c_((int)param_1,0xb2);
  if (*(short *)(param_1 + 1000) == 0x612) {
    zz_006a8c0_(param_1,0x610);
  }
  else if (*(short *)(param_1 + 1000) == 0x624) {
    zz_006a8c0_(param_1,0x623);
  }
  zz_017a608_((int)param_1);
  return;
}



// ==== 8015c4c4  FUN_8015c4c4 ====

void FUN_8015c4c4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x612) {
    zz_015c510_(param_1);
  }
  else if (sVar1 == 0x624) {
    zz_015c538_(param_1);
  }
  else if (sVar1 == 0x626) {
    zz_015c560_(param_1);
  }
  return;
}



// ==== 8015c510  zz_015c510_ ====

void zz_015c510_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015c538  zz_015c538_ ====

void zz_015c538_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015c560  zz_015c560_ ====

void zz_015c560_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8015c588  FUN_8015c588 ====

void FUN_8015c588(int param_1)

{
  zz_015c5a8_(param_1);
  return;
}



// ==== 8015c5a8  zz_015c5a8_ ====

void zz_015c5a8_(int param_1)

{
  (*(code *)(&PTR_FUN_80346284)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015c5e4  FUN_8015c5e4 ====

void FUN_8015c5e4(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(short *)(param_1 + 1000) == 0x620) && (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 == 0)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,8);
    *(float *)(param_1 + 0x694) = FLOAT_8043a784 + *(float *)(param_1 + 0x1dc8);
  }
  else {
    fVar1 = FLOAT_8043a778;
    dVar3 = (double)FLOAT_8043a77c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6ea) = 5;
    *(float *)(param_1 + 0x558) = fVar1;
    zz_004beb8_(dVar3,param_1,0xf,2,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8015c6a0  FUN_8015c6a0 ====

void FUN_8015c6a0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1b03) == '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8015c6e8  FUN_8015c6e8 ====

uint FUN_8015c6e8(uint param_1)

{
  short sVar1;
  uint uVar2;
  bool bVar3;
  char cVar4;
  double dVar5;
  
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043a778) {
    *(float *)(param_1 + 0x558) = FLOAT_8043a788;
    cVar4 = *(char *)(param_1 + 0x6ea) + -1;
    *(char *)(param_1 + 0x6ea) = cVar4;
    if (cVar4 < '\0') {
      dVar5 = (double)FLOAT_8043a77c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      uVar2 = zz_004beb8_(dVar5,param_1,0xf,0,0,10,1);
    }
    else {
      uVar2 = zz_006bda8_(param_1);
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x612) {
        bVar3 = zz_00fcd38_(param_1,1,0);
        uVar2 = (uint)bVar3;
      }
      else if (sVar1 == 0x620) {
        bVar3 = zz_00fcd38_(param_1,3,0);
        uVar2 = (uint)bVar3;
      }
      else if (sVar1 == 0x624) {
        bVar3 = zz_00fcd38_(param_1,4,0);
        uVar2 = (uint)bVar3;
      }
      else if (sVar1 == 0x626) {
        bVar3 = zz_00fcd38_(param_1,5,0);
        uVar2 = (uint)bVar3;
      }
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    uVar2 = param_1;
  }
  return uVar2;
}



// ==== 8015c7f4  FUN_8015c7f4 ====

void FUN_8015c7f4(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1b03) == '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,8);
  }
  return;
}



// ==== 8015c850  zz_015c850_ ====

bool zz_015c850_(int param_1,char param_2)

{
  undefined1 *puVar1;
  int iVar2;
  char cVar3;
  
  cVar3 = param_2 << 1;
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = cVar3;
      puVar1[0x11] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_8015c974;
      *(code **)(puVar1 + 0x10c) = FUN_8015cbc0;
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
    cVar3 = cVar3 + '\x01';
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 8015c974  FUN_8015c974 ====

void FUN_8015c974(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803468c8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8015c9c8  FUN_8015c9c8 ====

void FUN_8015c9c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043a790;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80346870 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8034686c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80346874 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80346878 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8034687c + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8034686a + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80346868 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80346868 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a794,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_015caf4_(param_9);
  return;
}



// ==== 8015caf4  zz_015caf4_ ====

void zz_015caf4_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a798;
  fVar1 = FLOAT_8043a790;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x148) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_8043a798;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if ((int)*(short *)(*(int *)(param_1 + 0x90) + 0x774) <= (int)*(char *)(param_1 + 0x11)) {
    *(float *)(param_1 + 0x58) = FLOAT_8043a798;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_8043a790) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_8043a798;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_8043a790;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 8015cba0  FUN_8015cba0 ====

void FUN_8015cba0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8015cbc0  FUN_8015cbc0 ====

void FUN_8015cbc0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x148) == '\0') {
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



// ==== 8015cc58  zz_015cc58_ ====

bool zz_015cc58_(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = (char)param_2;
    puVar1[0x11] = (char)(param_2 >> 1);
    puVar1[0x10] = 0x35;
    *(code **)(puVar1 + 0xc) = FUN_8015cd70;
    *(code **)(puVar1 + 0x10c) = FUN_8015d22c;
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



// ==== 8015cd70  FUN_8015cd70 ====

void FUN_8015cd70(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80346970)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8015ce08  FUN_8015ce08 ====

void FUN_8015ce08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  puVar7 = &DAT_80346938;
  puVar5 = &DAT_803468d8;
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
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8fc);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fcb9724),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_803468da + iVar2) * 0x30 + 0x8f8);
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80346948 + iVar3),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a7a0,&local_28,&local_28);
  uVar9 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80346948 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8034693a + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8034693c + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8034693e + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar8 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar8 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_803468d8 + iVar2),iVar1,iVar4,puVar5,
              iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80346938 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 8015d01c  FUN_8015d01c ====

void FUN_8015d01c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_00832c4_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_015d1d0_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_015d1d0_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_8034694c + iVar1)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_80346950 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(&DAT_8034694c + iVar1);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_80346944 + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_80346940 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_8034693c + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083524_(param_1);
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_015d1d0_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0xe);
            }
          }
          else {
            zz_015d1d0_(param_1);
          }
        }
      }
    }
    else {
      zz_015d1d0_(param_1);
    }
  }
  else {
    zz_015d1d0_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),0xe);
  }
  return;
}



// ==== 8015d1d0  zz_015d1d0_ ====

void zz_015d1d0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 8015d200  FUN_8015d200 ====

void FUN_8015d200(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8015d20c  FUN_8015d20c ====

void FUN_8015d20c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8015d22c  FUN_8015d22c ====

void FUN_8015d22c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8015d3a0  FUN_8015d3a0 ====

void FUN_8015d3a0(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a7b0) * FLOAT_8043a7a8);
  }
  if ('\0' < *(char *)(param_1 + 0x6f5)) {
    zz_01e844c_(param_1);
  }
  return;
}



// ==== 8015d438  FUN_8015d438 ====

void FUN_8015d438(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803469c0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8015d478  FUN_8015d478 ====

void FUN_8015d478(int param_1)

{
  zz_0140450_(param_1,0);
  return;
}



// ==== 8015d49c  FUN_8015d49c ====

void FUN_8015d49c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x41);
  return;
}



// ==== 8015d4e8  FUN_8015d4e8 ====

void FUN_8015d4e8(int param_1)

{
  (*(code *)(&PTR_FUN_803469d4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8015d524  FUN_8015d524 ====

void FUN_8015d524(int param_1)

{
  (*(code *)(&PTR_FUN_803469e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015d560  FUN_8015d560 ====

void FUN_8015d560(int param_1)

{
  zz_014a200_(param_1,&DAT_80434700);
  return;
}



// ==== 8015d584  FUN_8015d584 ====

void FUN_8015d584(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80434708);
  return;
}



// ==== 8015d5a8  FUN_8015d5a8 ====

void FUN_8015d5a8(int param_1)

{
  zz_0082824_(param_1,0x3d);
  return;
}



// ==== 8015d5cc  FUN_8015d5cc ====

void FUN_8015d5cc(int param_1)

{
  (*(code *)(&PTR_FUN_803469f4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015d608  FUN_8015d608 ====

void FUN_8015d608(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 8015d62c  FUN_8015d62c ====

void FUN_8015d62c(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 8015d650  FUN_8015d650 ====

void FUN_8015d650(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 8015d770  zz_015d770_ ====

void zz_015d770_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(300);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    FUN_800e4294(param_1,-0x7fcb7608,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fcb75a8,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fcb7548,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fcb74e8,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}



// ==== 8015d844  zz_015d844_ ====

void zz_015d844_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e43e0(param_1,(float *)&DAT_803489f8,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348a58,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348ab8,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80348b18,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcb7608,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fcb75a8,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fcb7548,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcb74e8,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}



// ==== 8015d99c  zz_015d99c_ ====

void zz_015d99c_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 8015d9d4  zz_015d9d4_ ====

void zz_015d9d4_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb7608,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb75a8,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb7548,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcb74e8,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fcb7608,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fcb75a8,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fcb7548,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcb74e8,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 8015db1c  FUN_8015db1c ====

void FUN_8015db1c(int param_1)

{
  short sVar1;
  
  zz_015d770_(param_1);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x909) {
    zz_0162f78_(param_1,2);
  }
  else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
    zz_0162f78_(param_1,0);
  }
  return;
}



// ==== 8015dba4  FUN_8015dba4 ====

void FUN_8015dba4(int param_1)

{
  zz_015d844_(param_1);
  return;
}



// ==== 8015dbd0  FUN_8015dbd0 ====

void FUN_8015dbd0(int param_1)

{
  zz_015d99c_(param_1);
  return;
}



// ==== 8015dbf0  FUN_8015dbf0 ====

void FUN_8015dbf0(int param_1)

{
  zz_015d9d4_(param_1);
  return;
}



// ==== 8015dc10  FUN_8015dc10 ====

void FUN_8015dc10(int param_1)

{
  (*(code *)(&PTR_FUN_80348b78)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8015dc4c  FUN_8015dc4c ====

void FUN_8015dc4c(int param_1)

{
  (*(code *)(&PTR_FUN_80348b84)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015dc88  FUN_8015dc88 ====

void FUN_8015dc88(int param_1)

{
  *(short *)(param_1 + 0x1dfc) =
       (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000) -
                    DOUBLE_8043a7c0) * DOUBLE_8043a7b8);
  (*(code *)(&PTR_FUN_80348b98)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015dcfc  FUN_8015dcfc ====

void FUN_8015dcfc(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a7cc;
  fVar1 = FLOAT_8043a7c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006d0dc_(param_1,0xc1,0);
  return;
}



// ==== 8015dd44  FUN_8015dd44 ====

void FUN_8015dd44(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_8043a7cc < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar2 = (double)FLOAT_8043a7d0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 8015ddd0  FUN_8015ddd0 ====

void FUN_8015ddd0(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_0082824_(param_1,0x67);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_0082824_(param_1,0x66);
      }
    }
  }
  return;
}



// ==== 8015de78  FUN_8015de78 ====

void FUN_8015de78(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8015decc  FUN_8015decc ====

void FUN_8015decc(int param_1)

{
  (*(code *)(&PTR_FUN_80348ba8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015df08  FUN_8015df08 ====

void FUN_8015df08(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a7d4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_8043a7d0,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 8015df6c  FUN_8015df6c ====

void FUN_8015df6c(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar3 = FLOAT_8043a7cc;
  if (iVar4 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_0082824_(param_1,0x67);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_0082824_(param_1,0x66);
      }
    }
  }
  return;
}



// ==== 8015e07c  FUN_8015e07c ====

void FUN_8015e07c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar2 = DOUBLE_8043a7c0;
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    dVar3 = (double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1dfc) ^ 0x80000000) -
            DOUBLE_8043a7c0;
    iVar1 = (int)(dVar3 * DOUBLE_8043a7b8);
    *(short *)(param_9 + 0x1dfc) = (short)iVar1;
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,iVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8015e110  FUN_8015e110 ====

void FUN_8015e110(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_80348bb4)[*(char *)(param_1 + 0x540)])(param_1);
  zz_015e3bc_(param_1);
  return;
}



// ==== 8015e170  FUN_8015e170 ====

void FUN_8015e170(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043a7cc;
  fVar1 = FLOAT_8043a7c8;
  dVar3 = (double)FLOAT_8043a7d0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar2;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  zz_004beb8_(dVar3,param_1,0xf,2,4,0xffffffff,0xffffffff);
  if (*(char *)(param_1 + 0x543) < '\0') {
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_006d0dc_(param_1,0xc1,0);
  }
  else {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8015e208  FUN_8015e208 ====

void FUN_8015e208(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  if (*(char *)(param_1 + 0x542) == '\0') {
    iVar1 = zz_006d0dc_(param_1,0xc1,0);
    if ((iVar1 != 1) && (FLOAT_8043a7cc < *(float *)(param_1 + 0x558))) {
      return;
    }
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8015e2c0  FUN_8015e2c0 ====

void FUN_8015e2c0(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_0082824_(param_1,0x67);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_0082824_(param_1,0x66);
      }
    }
  }
  return;
}



// ==== 8015e368  FUN_8015e368 ====

void FUN_8015e368(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8015e3bc  zz_015e3bc_ ====

void zz_015e3bc_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a7d8;
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7d8;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x540)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8015e444  FUN_8015e444 ====

void FUN_8015e444(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348bc4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015e494  FUN_8015e494 ====

void FUN_8015e494(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043a7e0;
  fVar1 = FLOAT_8043a7cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x80c) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8015e53c  FUN_8015e53c ====

void FUN_8015e53c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_8043a7d0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,7,0xffffffff,0xffffffff);
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_8043a7e4;
    fVar1 = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  return;
}



// ==== 8015e60c  FUN_8015e60c ====

void FUN_8015e60c(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_0082824_(param_1,0x67);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_0082824_(param_1,0x66);
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 1) {
    zz_00b22f4_(param_1);
    fVar2 = FLOAT_8043a7e4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  }
  return;
}



// ==== 8015e718  FUN_8015e718 ====

void FUN_8015e718(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
    fVar1 = FLOAT_8043a7e4;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      return;
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8015e804  FUN_8015e804 ====

void FUN_8015e804(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_80348bd4)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 8015e85c  FUN_8015e85c ====

void FUN_8015e85c(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043a7d4;
  dVar2 = (double)FLOAT_8043a7d0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 8015e8a8  FUN_8015e8a8 ====

void FUN_8015e8a8(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,1);
  fVar3 = FLOAT_8043a7cc;
  if (*(char *)(param_1 + 0x543) < '\0') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if (((('\0' < *(char *)(param_1 + 0x543)) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_0082824_(param_1,0x67);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_0082824_(param_1,0x66);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8015e9c0  FUN_8015e9c0 ====

void FUN_8015e9c0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_9,1);
  if (iVar1 == 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8015ea18  FUN_8015ea18 ====

void FUN_8015ea18(int param_1)

{
  (*(code *)(&PTR_FUN_80348be0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8015ea54  FUN_8015ea54 ====

void FUN_8015ea54(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348bf8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015eaa4  FUN_8015eaa4 ====

void FUN_8015eaa4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043a7e0;
  fVar1 = FLOAT_8043a7cc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a7cc;
  return;
}



// ==== 8015eb60  FUN_8015eb60 ====

void FUN_8015eb60(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    fVar1 = FLOAT_8043a7c8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_8043a7e8 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_8043a7e8 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_8043a7ec;
    *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a7d0,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8015ec78  FUN_8015ec78 ====

void FUN_8015ec78(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x04') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_8015ecb0;
  }
  zz_004cd24_(param_1,0xf);
LAB_8015ecb0:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7f0;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar4 = FUN_80066838((double)FLOAT_8043a7ec,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_8043a7f8;
    fVar1 = FLOAT_8043a7f4;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 8015ed78  FUN_8015ed78 ====

void FUN_8015ed78(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  if (iVar2 == 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  else {
    if (*(char *)(param_1 + 0x542) == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x04') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x04') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x04' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_8043a7fc;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_8043a7c8;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_8043a800;
          }
          dVar3 = (double)FLOAT_8043a7d0;
          *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
          zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
        }
        else {
          *(undefined1 *)(param_1 + 0x542) = 99;
        }
      }
    }
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 8015ef20  FUN_8015ef20 ====

void FUN_8015ef20(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x1cef) == '\x02') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043a7d0;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar2 = FLOAT_8043a7cc;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if ((*(float *)(param_1 + 0x558) <= fVar2) ||
         (uVar4 = FUN_80066838((double)FLOAT_8043a7ec,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_8043a804;
        fVar2 = FLOAT_8043a7f8;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_8043a7cc,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a808;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  else if ((cVar1 < '\x04') && (iVar5 = zz_004cd24_(param_1,0xf), iVar5 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    return;
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  if (iVar5 != 0) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8015f0dc  FUN_8015f0dc ====

void FUN_8015f0dc(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8015f114  FUN_8015f114 ====

void FUN_8015f114(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348c10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015f164  FUN_8015f164 ====

void FUN_8015f164(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar1 = FLOAT_8043a80c;
  *(float *)(param_1 + 0x558) = FLOAT_8043a7e0;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a7cc;
  return;
}



// ==== 8015f244  FUN_8015f244 ====

void FUN_8015f244(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a810;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a810;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043a7cc;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043a7c8;
    *(float *)(param_1 + 0x558) = FLOAT_8043a7c8;
    fVar3 = FLOAT_8043a7ec;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043a7d0,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 8015f388  FUN_8015f388 ====

void FUN_8015f388(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar3 = FUN_80066838((double)FLOAT_8043a7ec,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_8043a7d0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8015f46c  FUN_8015f46c ====

void FUN_8015f46c(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043a7dc < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043a814,param_1);
  if (0 < (int)uVar6) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x541) == '\0') {
    uVar2 = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
    zz_006660c_(param_1);
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_800669d0(param_1,0x40);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
    *(undefined2 *)(param_1 + 0x72) = uVar2;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043a7cc;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar5 = zz_004cd24_(param_1,0xf);
        if (iVar5 != 1) {
          return;
        }
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8015f60c;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043a818;
      fVar3 = FLOAT_8043a7f8;
      if (*(char *)(param_1 + 0x1cef) != '\x02') {
        return;
      }
      if (*(char *)(param_1 + 0x1cf0) != '\x01') {
        return;
      }
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0;
      *(undefined2 *)(param_1 + 0x54a) = 0x1500;
      *(float *)(param_1 + 0x558) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar3 < *(float *)(param_1 + 0x558)) {
      zz_0067754_(param_1,(short *)(param_1 + 0x72),*(short *)(param_1 + 0x54a));
      return;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  zz_0066ed8_(param_1,*(ushort *)(param_1 + 0x5ae),*(undefined2 *)(param_1 + 0x54a));
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_8015f60c:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 8015f66c  FUN_8015f66c ====

void FUN_8015f66c(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8015f6a4  FUN_8015f6a4 ====

void FUN_8015f6a4(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348c24)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015f6f4  FUN_8015f6f4 ====

void FUN_8015f6f4(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043a7d0;
  *(float *)(param_1 + 0x558) = FLOAT_8043a7e0;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 8015f7b0  FUN_8015f7b0 ====

void FUN_8015f7b0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_8043a7cc < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8015f830;
  }
  fVar2 = FLOAT_8043a814;
  fVar1 = FLOAT_8043a7c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8015f830:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8015f870  FUN_8015f870 ====

/* WARNING: Removing unreachable block (ram,0x8015faa0) */
/* WARNING: Removing unreachable block (ram,0x8015f880) */

void FUN_8015f870(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a7cc;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a7e8 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a7c8
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a7c8 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a81c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a820;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043a81c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043a7e0,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_8043a7b8 * (double)*(float *)(param_1 + 0x44)) goto LAB_8015fa94;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8015fa94:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8015fabc  FUN_8015fabc ====

void FUN_8015fabc(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a7cc;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a7cc) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a7cc;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a7c8 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8015fb60  FUN_8015fb60 ====

void FUN_8015fb60(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348c34)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8015fbb0  FUN_8015fbb0 ====

void FUN_8015fbb0(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x870),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043a7d0;
  *(float *)(param_1 + 0x558) = FLOAT_8043a7e0;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8015fc6c  FUN_8015fc6c ====

void FUN_8015fc6c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_8043a7cc < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8015fcec;
  }
  fVar2 = FLOAT_8043a814;
  fVar1 = FLOAT_8043a7c8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8015fcec:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8015fd2c  FUN_8015fd2c ====

/* WARNING: Removing unreachable block (ram,0x8015ff5c) */
/* WARNING: Removing unreachable block (ram,0x8015fd3c) */

void FUN_8015fd2c(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043a7cc;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043a824 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043a7c8
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043a7c8 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043a81c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043a820;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043a81c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_8043a7e0,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_8043a7b8 * (double)*(float *)(param_1 + 0x44)) goto LAB_8015ff50;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8015ff50:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8015ff78  FUN_8015ff78 ====

void FUN_8015ff78(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043a7cc;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043a7cc) {
      *(float *)(param_1 + 0x44) = FLOAT_8043a7cc;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043a7c8 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8016001c  FUN_8016001c ====

void FUN_8016001c(int param_1)

{
  (*(code *)(&PTR_FUN_80348c44)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80160058  FUN_80160058 ====

void FUN_80160058(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348c54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801600a8  FUN_801600a8 ====

void FUN_801600a8(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  fVar2 = FLOAT_8043a7f0;
  fVar1 = FLOAT_8043a7cc;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a7cc;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  else if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7f0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  fVar2 = FLOAT_8043a82c;
  *(float *)(param_1 + 0x48) = FLOAT_8043a828;
  fVar1 = FLOAT_8043a7e0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a7d0,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}



// ==== 801601ac  FUN_801601ac ====

void FUN_801601ac(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  fVar1 = FLOAT_8043a7f0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7f0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 8016027c  FUN_8016027c ====

void FUN_8016027c(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_014452c_(param_1,2);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_014452c_(param_1,0);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043a7f0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7f0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 8016037c  FUN_8016037c ====

void FUN_8016037c(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_8043a7f0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a7f0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x694) = FLOAT_8043a7d4 + *(float *)(param_1 + 0x1dc8);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80160430  FUN_80160430 ====

void FUN_80160430(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80348c64)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80160480  FUN_80160480 ====

void FUN_80160480(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a7e0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  if (0 < *(short *)(param_1 + 0x784)) {
    if (*(char *)(param_1 + 0x581) == '\x01') {
      if (*(float *)(param_1 + 0x48) <= FLOAT_8043a7cc) {
        *(float *)(param_1 + 0x48) = FLOAT_8043a830;
      }
      else {
        *(float *)(param_1 + 0x48) = FLOAT_8043a808;
      }
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_8043a834;
    }
    *(float *)(param_1 + 0x50) = FLOAT_8043a82c;
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a7d0,param_1,0xf,4,1,0xffffffff,0xffffffff);
  return;
}



// ==== 80160590  FUN_80160590 ====

void FUN_80160590(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043a7cc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_006e1ac_(param_1,0xc1,1);
  return;
}



// ==== 80160640  FUN_80160640 ====

void FUN_80160640(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x909) {
        zz_014452c_(param_1,2);
      }
      else if ((sVar1 < 0x909) && (sVar1 == 0x902)) {
        zz_014452c_(param_1,0);
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  FUN_80067310((double)FLOAT_8043a7dc,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}



// ==== 80160734  FUN_80160734 ====

void FUN_80160734(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a7f0;
  dVar3 = (double)FLOAT_8043a7dc;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a7c0) * FLOAT_8043a838);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x54a));
  if (*(char *)(param_1 + 0x1cef) == -1) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
  }
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80160938  FUN_80160938 ====

void FUN_80160938(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a848) * FLOAT_8043a840);
  }
  return;
}



// ==== 801609bc  FUN_801609bc ====

void FUN_801609bc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80348cb8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801609fc  FUN_801609fc ====

void FUN_801609fc(int param_1)

{
  zz_014b634_(param_1,0);
  return;
}



// ==== 80160a20  FUN_80160a20 ====

void FUN_80160a20(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x42);
  return;
}



// ==== 80160a58  FUN_80160a58 ====

void FUN_80160a58(int param_1)

{
  (*(code *)(&PTR_FUN_80348cc8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80160a94  FUN_80160a94 ====

void FUN_80160a94(int param_1)

{
  (*(code *)(&PTR_FUN_80348cd4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80160ad0  FUN_80160ad0 ====

void FUN_80160ad0(int param_1)

{
  zz_014a200_(param_1,&DAT_80434710);
  return;
}



// ==== 80160af4  FUN_80160af4 ====

void FUN_80160af4(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80434718);
  return;
}



// ==== 80160b18  FUN_80160b18 ====

void FUN_80160b18(int param_1)

{
  zz_0082824_(param_1,0x3e);
  return;
}



// ==== 80160b3c  FUN_80160b3c ====

void FUN_80160b3c(int param_1)

{
  (*(code *)(&PTR_FUN_80348ce8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80160b78  FUN_80160b78 ====

void FUN_80160b78(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 80160b9c  FUN_80160b9c ====

void FUN_80160b9c(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 80160bc0  FUN_80160bc0 ====

void FUN_80160bc0(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 80160ce0  FUN_80160ce0 ====

void FUN_80160ce0(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  zz_01040c4_(param_1);
  zz_01049d4_(param_1);
  return;
}



// ==== 80160d2c  FUN_80160d2c ====

void FUN_80160d2c(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a858) * FLOAT_8043a850);
  }
  return;
}



// ==== 80160db0  FUN_80160db0 ====

void FUN_80160db0(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80349098)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80160df0  FUN_80160df0 ====

void FUN_80160df0(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f2) = 2;
  zz_0141390_(param_1);
  *(undefined1 *)(param_1 + 0x6f3) = 2;
  zz_0165184_(param_1,0);
  return;
}



// ==== 80160e38  FUN_80160e38 ====

void FUN_80160e38(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x43);
  return;
}



// ==== 80160e70  FUN_80160e70 ====

void FUN_80160e70(int param_1)

{
  (*(code *)(&PTR_FUN_803490a8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80160eac  FUN_80160eac ====

void FUN_80160eac(int param_1)

{
  (*(code *)(&PTR_FUN_803490b4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80160ee8  FUN_80160ee8 ====

void FUN_80160ee8(int param_1)

{
  zz_014a200_(param_1,&DAT_80434720);
  return;
}



// ==== 80160f0c  FUN_80160f0c ====

void FUN_80160f0c(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80434728);
  return;
}



// ==== 80160f30  FUN_80160f30 ====

void FUN_80160f30(int param_1)

{
  zz_0082824_(param_1,0x3f);
  return;
}



// ==== 80160f54  FUN_80160f54 ====

void FUN_80160f54(int param_1)

{
  (*(code *)(&PTR_FUN_803490c8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80160f90  FUN_80160f90 ====

void FUN_80160f90(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 80160fb4  FUN_80160fb4 ====

void FUN_80160fb4(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



// ==== 80160fd8  FUN_80160fd8 ====

void FUN_80160fd8(int param_1)

{
  zz_014b22c_(param_1);
  return;
}



// ==== 80161114  FUN_80161114 ====

void FUN_80161114(int param_1)

{
  zz_014b504_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a868) * FLOAT_8043a860);
  }
  return;
}



// ==== 80161198  FUN_80161198 ====

void FUN_80161198(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80349460)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801611d8  FUN_801611d8 ====

void FUN_801611d8(int param_1)

{
  zz_00f036c_(param_1,0xed);
  zz_01657f0_(param_1);
  return;
}



// ==== 80161210  FUN_80161210 ====

void FUN_80161210(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x18);
  return;
}



// ==== 80161248  FUN_80161248 ====

void FUN_80161248(int param_1)

{
  (*(code *)(&PTR_FUN_80349470)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80161284  FUN_80161284 ====

void FUN_80161284(int param_1)

{
  (*(code *)(&PTR_FUN_8034947c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801612c0  FUN_801612c0 ====

void FUN_801612c0(int param_1)

{
  zz_014a200_(param_1,&DAT_80434730);
  return;
}



// ==== 801612e4  FUN_801612e4 ====

void FUN_801612e4(int param_1)

{
  zz_0149ec8_(param_1,&DAT_80434738);
  return;
}



// ==== 80161308  FUN_80161308 ====

void FUN_80161308(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    zz_016ddb0_(param_1,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}



// ==== 80161354  FUN_80161354 ====

void FUN_80161354(int param_1)

{
  (*(code *)(&PTR_FUN_80349490)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80161390  FUN_80161390 ====

void FUN_80161390(int param_1)

{
  zz_014a8c0_(param_1);
  return;
}



// ==== 801613b4  FUN_801613b4 ====

void FUN_801613b4(int param_1)

{
  zz_014ad94_(param_1);
  return;
}



