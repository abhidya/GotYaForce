// ==== 801d4524  FUN_801d4524 ====

void FUN_801d4524(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 801d4548  FUN_801d4548 ====

void FUN_801d4548(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 801d456c  FUN_801d456c ====

void FUN_801d456c(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 801d46bc  FUN_801d46bc ====

void FUN_801d46bc(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x40b) {
    zz_00de5a4_(param_1,2,param_1 + 0x144);
    zz_00de5a4_(param_1,3,(undefined1 *)(param_1 + 0x145));
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined1 *)(param_1 + 0x144) = 0;
  }
  zz_00c74ec_(param_1,0x10);
  return;
}



// ==== 801d4730  FUN_801d4730 ====

void FUN_801d4730(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x40b) {
    if ((*(char *)(param_1 + 0x144) == '\0') && (*(char *)(param_1 + 0x145) == '\0')) {
      if (*(short *)(param_1 + 0x784) < 1) {
        zz_006de10_(param_1,2);
      }
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
      *(undefined1 *)(param_1 + 0x748) = 2;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
      *(undefined1 *)(param_1 + 0x748) = 0;
    }
  }
  else if (sVar1 == 0x40c) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
    *(undefined1 *)(param_1 + 0x748) = 1;
  }
  else if (sVar1 == 0x40d) {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
    *(undefined1 *)(param_1 + 0x748) = 1;
  }
  return;
}



// ==== 801d4810  FUN_801d4810 ====

void FUN_801d4810(int param_1)

{
  (*(code *)(&PTR_FUN_8038bdf0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d484c  FUN_801d484c ====

void FUN_801d484c(int param_1)

{
  short sVar1;
  
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x40b) {
    zz_01d48a4_(param_1);
  }
  else if (sVar1 == 0x40c) {
    zz_01d49b0_(param_1);
  }
  else if (sVar1 == 0x40d) {
    zz_01d4ac0_(param_1);
  }
  return;
}



// ==== 801d48a4  zz_01d48a4_ ====

void zz_01d48a4_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_8038bdfc);
  return;
}



// ==== 801d48cc  FUN_801d48cc ====

uint FUN_801d48cc(int param_1)

{
  char *pcVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = zz_006dbe0_(param_1,2,1,1);
  if (uVar2 != 0) {
    iVar4 = 0;
    iVar5 = 0;
    do {
      pcVar1 = (char *)(param_1 + iVar5 + 0x144);
      if (*pcVar1 == '\0') {
        *pcVar1 = '\x01';
        bVar3 = zz_00e0e90_(param_1,(char)iVar5 + '\x02',1,pcVar1);
        uVar2 = (uint)bVar3;
        iVar4 = iVar4 + 1;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 2);
    if (iVar4 != 0) {
      uVar2 = zz_00f036c_(param_1,0xdb);
    }
  }
  return uVar2;
}



// ==== 801d49b0  zz_01d49b0_ ====

void zz_01d49b0_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_8038be10);
  return;
}



// ==== 801d49d8  FUN_801d49d8 ====

void FUN_801d49d8(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = FLOAT_8043be58;
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x73);
    zz_0082824_(param_1,0x74);
  }
  return;
}



// ==== 801d4a44  FUN_801d4a44 ====

undefined4 FUN_801d4a44(int param_1)

{
  int iVar1;
  
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043be5c) {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
      return 0x8444;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  return 0;
}



// ==== 801d4ac0  zz_01d4ac0_ ====

void zz_01d4ac0_(int param_1)

{
  zz_00f1e30_(param_1,&DAT_8038be24);
  return;
}



// ==== 801d4ae8  FUN_801d4ae8 ====

void FUN_801d4ae8(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,0x5f);
    zz_00c3be0_(param_1,0x60);
  }
  return;
}



// ==== 801d4b40  FUN_801d4b40 ====

undefined4 FUN_801d4b40(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}



// ==== 801d4ba8  FUN_801d4ba8 ====

void FUN_801d4ba8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043be68;
  fVar1 = FLOAT_8043be60;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_8043be68) * FLOAT_8043be60);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_8038be38)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d4c48  FUN_801d4c48 ====

void FUN_801d4c48(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 801d4c6c  FUN_801d4c6c ====

void FUN_801d4c6c(int param_1)

{
  zz_00f2c3c_(param_1);
  return;
}



// ==== 801d4c90  FUN_801d4c90 ====

void FUN_801d4c90(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 801d4cb4  FUN_801d4cb4 ====

void FUN_801d4cb4(int param_1)

{
  zz_00f3cb4_(param_1);
  return;
}



// ==== 801d4cd8  FUN_801d4cd8 ====

void FUN_801d4cd8(int param_1)

{
  zz_00f3738_(param_1);
  return;
}



// ==== 801d4d00  zz_01d4d00_ ====

void zz_01d4d00_(int param_1,byte param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x5e;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801d4f58;
    *(code **)(puVar1 + 0x10c) = FUN_801d5418;
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
    gnt4_PSQUATScale_bl((double)*(float *)(puVar1 + 0xb4),
                        (float *)((uint)param_2 * 0x3c + -0x7fc732c8),(float *)(puVar1 + 0x58));
  }
  return;
}



// ==== 801d4e24  zz_01d4e24_ ====

void zz_01d4e24_(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0;
    *(code **)(puVar2 + 0xc) = FUN_801d5480;
    *(code **)(puVar2 + 0x10c) = FUN_801d5694;
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(puVar2 + 0x20) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(puVar2 + 0x24) = uVar1;
    *(undefined4 *)(puVar2 + 0x28) = *(undefined4 *)(param_1 + 0x28);
    uVar1 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(puVar2 + 0x38) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(puVar2 + 0x3c) = uVar1;
    *(undefined4 *)(puVar2 + 0x40) = *(undefined4 *)(param_1 + 0x40);
    uVar1 = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(puVar2 + 0x9c) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(puVar2 + 0xa0) = uVar1;
    *(undefined4 *)(puVar2 + 0xa4) = *(undefined4 *)(param_1 + 0xa4);
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



// ==== 801d4f58  FUN_801d4f58 ====

void FUN_801d4f58(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8038ce08)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801d4fa8  FUN_801d4fa8 ====

void FUN_801d4fa8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  puVar2 = &DAT_8038cd18;
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fc732e4),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)
        (iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + (char)(&DAT_8038cd48)[iVar3] * 4 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)
        (iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + (char)(&DAT_8038cd48)[iVar3] * 4 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)
        (iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + (char)(&DAT_8038cd48)[iVar3] * 4 + 0x8f4);
  if ((&DAT_8038cd49)[iVar3] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043be70,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  if ((*(int *)(iVar5 + 200) != 0) &&
     (iVar1 = FUN_8006c334((double)*(float *)(&DAT_8038cd44 + iVar3),param_9,
                           (float *)(iVar5 + 0x518)), iVar1 != 0)) {
    zz_0083d60_(param_9,iVar5,(int)(char)(&DAT_8038cd19)[iVar3]);
  }
  zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8038cd28 + iVar3),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8038cd28 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_8038cd2c + iVar3);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar5 + (char)(&DAT_8038cd19)[iVar3] * 0x30 + 0x8f8);
  uVar6 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 300;
  *(undefined2 *)(param_9 + 0x1e) = 10;
  *(undefined2 *)(param_9 + 0x80) = 0x1000;
  iVar5 = zz_008ac80_(param_9,(int)(char)(&DAT_8038cd1a)[iVar3]);
  if (iVar5 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(uint)(byte)(&DAT_8038cd18)[iVar3],puVar2,iVar4,in_r8,in_r9
                ,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,0x104);
  }
  return;
}



// ==== 801d5200  FUN_801d5200 ====

void FUN_801d5200(int param_1)

{
  int iVar1;
  short sVar2;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  if (sVar2 < 1) {
    *(undefined2 *)(param_1 + 0x1e) = 10;
    zz_01d4e24_(param_1);
  }
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x7c);
        iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x3c;
        FUN_80083874((double)*(float *)(&DAT_8038cd34 + iVar1),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_8038cd30 + iVar1),param_1,
                     (char)*(undefined4 *)(&DAT_8038cd2c + iVar1));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar1 + -0x7fc732c8),
                            (float *)(param_1 + 0x58));
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,
                              auStack_28);
          if (iVar1 != 0) {
            *(float *)(param_1 + 0x20) = local_1c;
            *(undefined4 *)(param_1 + 0x24) = local_18;
            *(undefined4 *)(param_1 + 0x28) = local_14;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
            zz_0019550_(param_1,&local_1c,0);
            *(undefined1 *)(param_1 + 0x18) = 2;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 801d53bc  FUN_801d53bc ====

void FUN_801d53bc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801d53f8  FUN_801d53f8 ====

void FUN_801d53f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d5418  FUN_801d5418 ====

/* WARNING: Removing unreachable block (ram,0x801d542c) */

void FUN_801d5418(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043be74 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 801d5480  FUN_801d5480 ====

void FUN_801d5480(int param_1)

{
  (*(code *)(&PTR_FUN_8038ce18)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801d54bc  FUN_801d54bc ====

void FUN_801d54bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  uVar5 = 0x8f;
  *(undefined1 *)(param_9 + 0x18) = 1;
  uVar6 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),0x8f,param_12,param_13,param_14,param_15,param_16);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,uVar5,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 1;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar1 = FLOAT_8043be78;
  *(undefined1 *)(param_9 + 0x98) = 5;
  fVar2 = FLOAT_8043be7c;
  *(float *)(param_9 + 0xd4) = fVar1;
  fVar3 = FLOAT_8043be80;
  *(float *)(param_9 + 0xd8) = fVar1;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x44) = fVar3 / *(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0x48) = fVar2;
  uVar4 = zz_00055fc_();
  *(short *)(param_9 + 0x74) = (short)(uVar4 << 0xb);
  zz_01d5584_(param_9);
  return;
}



// ==== 801d5584  zz_01d5584_ ====

void zz_01d5584_(int param_1)

{
  char cVar1;
  float fVar2;
  bool bVar3;
  
  fVar2 = *(float *)(param_1 + 0xd4) - FLOAT_8043be7c;
  bVar3 = fVar2 < FLOAT_8043be84;
  *(float *)(param_1 + 0xd4) = fVar2;
  if (bVar3) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x44);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x44);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x44);
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ((('\0' < cVar1) || (cVar1 < '\0')) ||
       (*(float *)(param_1 + 0xd8) < *(float *)(param_1 + 0xd4))) goto LAB_801d564c;
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x48) / *(float *)(param_1 + 0xd8);
  }
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) - *(float *)(param_1 + 0x50);
LAB_801d564c:
  zz_0007cac_((double)*(float *)(param_1 + 0x48),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 801d5674  FUN_801d5674 ====

void FUN_801d5674(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d5694  FUN_801d5694 ====

void FUN_801d5694(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  double dVar3;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  dVar3 = (double)FLOAT_8043be74;
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar3 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_8043be88)),afStack_48,0x7a);
  pfVar1 = afStack_48;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 801d57f8  FUN_801d57f8 ====

void FUN_801d57f8(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043be90;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(float *)(*(int *)(param_1 + 0x4ac) + 0x98) = fVar1;
  zz_00c74ec_(param_1,0x3d);
  zz_00c74ec_(param_1,0x3e);
  zz_00c74ec_(param_1,0x3f);
  zz_00c74ec_(param_1,0x40);
  *(undefined4 *)(param_1 + 0x144) = 0x1010101;
  zz_013833c_(param_1,0x10,param_1 + 0x144);
  zz_013833c_(param_1,0x11,param_1 + 0x145);
  zz_013833c_(param_1,0x12,param_1 + 0x146);
  zz_013833c_(param_1,0x13,param_1 + 0x147);
  *(undefined2 *)(param_1 + 0x18e6) = 0x2000;
  *(undefined2 *)(param_1 + 0x18e0) = 0x2000;
  return;
}



// ==== 801d5928  FUN_801d5928 ====

void FUN_801d5928(int param_1)

{
  (*(code *)(&PTR_FUN_8038d218)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d5964  FUN_801d5964 ====

void FUN_801d5964(int param_1)

{
  (*(code *)(&PTR_LAB_8038d224)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d59b0  FUN_801d59b0 ====

void FUN_801d59b0(int param_1)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  iVar3 = 4;
  do {
    pbVar1 = (byte *)(param_1 + iVar2 + 0x144);
    if ((*pbVar1 & 1) != 0) {
      zz_013212c_(param_1,iVar2 + 0x16,pbVar1);
      *(undefined2 *)(param_1 + 0x548) = 0x1e;
      return;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 801d5a28  FUN_801d5a28 ====

void FUN_801d5a28(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801d5a64  FUN_801d5a64 ====

void FUN_801d5a64(int param_1)

{
  (*(code *)(&PTR_LAB_8038d230)[*(char *)(param_1 + 0x540)])();
  if (*(short *)(param_1 + 0x548) != 0) {
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  return;
}



// ==== 801d5adc  FUN_801d5adc ====

void FUN_801d5adc(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043be98;
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_8043be94;
    zz_01f23b0_(param_1,0);
    zz_01f23b0_(param_1,1);
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  return;
}



// ==== 801d5b5c  FUN_801d5b5c ====

void FUN_801d5b5c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043be9c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801d5c84  FUN_801d5c84 ====

void FUN_801d5c84(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043bea0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(float *)(*(int *)(param_1 + 0x4ac) + 0x98) = fVar1;
  zz_00c74ec_(param_1,0x41);
  *(undefined1 *)(param_1 + 0x14e) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  *(undefined2 *)(param_1 + 0x144) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x14d) = 0;
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x14a) = 0;
  return;
}



// ==== 801d5e90  FUN_801d5e90 ====

void FUN_801d5e90(int param_1)

{
  (*(code *)(&PTR_FUN_8038dbc8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d5ecc  FUN_801d5ecc ====

void FUN_801d5ecc(int param_1)

{
  (*(code *)(&PTR_FUN_8038dbd4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d5f08  FUN_801d5f08 ====

void FUN_801d5f08(int param_1)

{
  float fVar1;
  uint uVar2;
  float local_18;
  float local_14;
  float local_10;
  
  fVar1 = FLOAT_8043bea4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_0066408_(param_1,(int)*(char *)(*(int *)(param_1 + 0x4b0) + 0x10),(float *)(param_1 + 0x518),
              &local_18);
  uVar2 = (uint)(local_10 < FLOAT_8043bea8);
  if (local_18 < FLOAT_8043beac) {
    uVar2 = uVar2 | 2;
  }
  if (local_14 < FLOAT_8043beb0) {
    uVar2 = uVar2 | 4;
  }
  *(undefined1 *)(param_1 + 0x14f) = *(undefined1 *)(uVar2 * 2 + -0x7fc7241c);
  *(undefined1 *)(param_1 + 0x150) = *(undefined1 *)(uVar2 * 2 + -0x7fc7241b);
  return;
}



// ==== 801d5fbc  FUN_801d5fbc ====

void FUN_801d5fbc(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043beb4;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,(int)*(char *)(param_1 + 0x150),1,(short *)&DAT_80435ad8);
  if ((iVar1 == 0) && (FLOAT_8043beac < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801d6034  FUN_801d6034 ====

void FUN_801d6034(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  fVar1 = FLOAT_8043beac;
  if (iVar2 == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043bec0;
    *(float *)(param_1 + 0x55c) = fVar1;
  }
  else {
    FUN_8006cc90((double)FLOAT_8043beb4,param_1,(int)*(char *)(param_1 + 0x150),1,
                 (short *)&DAT_80435ad8);
    FUN_801f3784((double)FLOAT_8043beac,param_1,*(char *)(param_1 + 0x14f));
    fVar1 = FLOAT_8043bebc;
    *(float *)(param_1 + 0x558) = FLOAT_8043beb8;
    *(float *)(param_1 + 0x55c) = fVar1;
  }
  return;
}



// ==== 801d60d0  FUN_801d60d0 ====

void FUN_801d60d0(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (FLOAT_8043beac < *(float *)(param_1 + 0x55c)) {
    dVar2 = (double)FLOAT_8043beb4;
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
    FUN_8006cc90(dVar2,param_1,(int)*(char *)(param_1 + 0x150),1,(short *)&DAT_80435ad8);
  }
  fVar1 = FLOAT_8043beac;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801d615c  FUN_801d615c ====

void FUN_801d615c(int param_1)

{
  (*(code *)(&PTR_LAB_8038dbf4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d61a8  FUN_801d61a8 ====

void FUN_801d61a8(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043bec0;
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_8043bea4;
    zz_01f49c8_(param_1,*(undefined1 *)(param_1 + 0x14e));
    *(byte *)(param_1 + 0x14e) = *(byte *)(param_1 + 0x14e) ^ 1;
  }
  return;
}



// ==== 801d6224  FUN_801d6224 ====

void FUN_801d6224(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043beac;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801d634c  FUN_801d634c ====

void FUN_801d634c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043bec8;
  *(int *)(PTR_DAT_80433934 + 0xbc) = param_1;
  PTR_DAT_80433934[0x1834] = 1;
  *(undefined4 *)(param_1 + 0x5a0) = 0xffffffff;
  *(undefined2 *)(param_1 + 0x192a) = 0x2000;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(float *)(*(int *)(param_1 + 0x4ac) + 0x98) = fVar1;
  fVar2 = FLOAT_8043bed0;
  fVar1 = FLOAT_8043becc;
  if (*(char *)(param_1 + 0x493) == '\0') {
    iVar3 = 0;
    *(float *)(param_1 + 0x28) = FLOAT_8043becc;
    *(float *)(param_1 + 0x20) = fVar1;
    *(float *)(param_1 + 0x24) = fVar2;
    *(undefined2 *)(param_1 + 0x72) = 0x2000;
    *(undefined4 *)(param_1 + 0x76c) = 0xffffe01f;
    do {
      zz_01fb398_(param_1,(char)iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 8);
  }
  zz_01fd114_(param_1);
  *(undefined2 *)(param_1 + 0x17c) = 0;
  *(undefined2 *)(param_1 + 0x17e) = 0;
  *(undefined1 *)(param_1 + 0x18c) = 0;
  *(undefined1 *)(param_1 + 400) = 0;
  *(undefined2 *)(param_1 + 0x182) = 0;
  *(undefined1 *)(param_1 + 0x18d) = 0;
  *(undefined1 *)(param_1 + 0x18e) = 0xff;
  *(undefined1 *)(param_1 + 0x194) = 1;
  *(undefined1 *)(param_1 + 0x197) = 0;
  *(undefined2 *)(param_1 + 0x184) = 0x78;
  *(undefined1 *)(param_1 + 0x191) = 0;
  *(undefined1 *)(param_1 + 0x192) = 0;
  *(undefined1 *)(param_1 + 0x193) = 0;
  *(undefined1 *)(param_1 + 0x199) = 0xff;
  *(undefined1 *)(param_1 + 0x19a) = 0;
  *(undefined1 *)(param_1 + 0x19b) = 0;
  *(undefined2 *)(param_1 + 0x18a) = *(undefined2 *)(param_1 + 0x1c6);
  *(undefined1 *)(param_1 + 0x19d) = 0;
  *(undefined1 *)(param_1 + 0x19e) = 0;
  *(undefined1 *)(param_1 + 399) = 0xf;
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined4 *)(param_1 + 0x14c) = 0;
  *(undefined4 *)(param_1 + 0x150) = 0;
  *(undefined4 *)(param_1 + 0x154) = 0;
  *(undefined4 *)(param_1 + 0x158) = 0;
  *(undefined4 *)(param_1 + 0x15c) = 0;
  *(undefined4 *)(param_1 + 0x160) = 0;
  return;
}



// ==== 801d6494  FUN_801d6494 ====

void FUN_801d6494(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(undefined2 *)(param_1 + 0x6c2) = *(undefined2 *)(param_1 + 0x6be);
  fVar2 = FLOAT_8043bed0;
  fVar1 = FLOAT_8043becc;
  if (*(char *)(param_1 + 0x493) == '\0') {
    *(float *)(param_1 + 0x28) = FLOAT_8043becc;
    *(float *)(param_1 + 0x20) = fVar1;
    *(float *)(param_1 + 0x24) = fVar2;
    *(undefined2 *)(param_1 + 0x72) = 0x2000;
  }
  if (*(short *)(param_1 + 0x1c6) < *(short *)(param_1 + 0x18a)) {
    zz_01d72fc_(param_1);
  }
  *(undefined2 *)(param_1 + 0x18a) = *(undefined2 *)(param_1 + 0x1c6);
  if (-1 < *(char *)(param_1 + 0x199)) {
    iVar3 = zz_00ea0f0_((int)*(char *)(param_1 + 0x199));
    if (iVar3 == 0) {
      *(undefined1 *)(param_1 + 0x199) = 0xff;
    }
  }
  if ('\0' < *(char *)(param_1 + 0x18c)) {
    *(char *)(param_1 + 0x18c) = *(char *)(param_1 + 0x18c) + -1;
  }
  zz_01d684c_(param_1,param_1 + 0x144);
  zz_01d6e18_(param_1,param_1 + 0x144);
  return;
}



// ==== 801d6574  FUN_801d6574 ====

void FUN_801d6574(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = param_1 + 0x144;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  fVar2 = FLOAT_8043bed0;
  fVar1 = FLOAT_8043becc;
  if (*(char *)(param_1 + 0x493) == '\0') {
    *(float *)(param_1 + 0x28) = FLOAT_8043becc;
    *(float *)(param_1 + 0x20) = fVar1;
    *(float *)(param_1 + 0x24) = fVar2;
    *(undefined2 *)(param_1 + 0x72) = 0x2000;
  }
  else {
    *(short *)(param_1 + 0x18f4) = *(short *)(param_1 + 0x18f4) + 0x100;
    *(short *)(param_1 + 0x18fa) = *(short *)(param_1 + 0x18fa) + 0x100;
    *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) + 0x100;
    *(short *)(param_1 + 0x1906) = *(short *)(param_1 + 0x1906) + 0x100;
    *(short *)(param_1 + 0x190c) = *(short *)(param_1 + 0x190c) + 0x100;
    *(short *)(param_1 + 0x1912) = *(short *)(param_1 + 0x1912) + 0x100;
    *(short *)(param_1 + 0x1918) = *(short *)(param_1 + 0x1918) + 0x100;
    *(short *)(param_1 + 0x191e) = *(short *)(param_1 + 0x191e) + 0x100;
  }
  zz_01d69b0_(param_1,iVar3);
  zz_01d6ad8_(param_1,iVar3);
  zz_01d6bbc_(param_1,iVar3);
  zz_01d6708_(param_1,iVar3);
  return;
}



// ==== 801d6690  FUN_801d6690 ====

void FUN_801d6690(int param_1)

{
  (*(code *)(&PTR_LAB_8038dee8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d66d0  FUN_801d66d0 ====

void FUN_801d66d0(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a53c_(param_1,0);
  return;
}



// ==== 801d6708  zz_01d6708_ ====

void zz_01d6708_(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  float local_28;
  float local_24;
  float local_20;
  
  if (PTR_DAT_80433934[0x1f] != '\0') {
    return;
  }
  if ((*(byte *)(param_2 + 0x4a) & 0xf) != 0) {
    return;
  }
  sVar2 = *(short *)(param_2 + 0x3a);
  if (sVar2 != 1) {
    if (0 < sVar2) {
      if (2 < sVar2) {
        return;
      }
      goto LAB_801d67bc;
    }
    if (sVar2 < 0) {
      return;
    }
    *(short *)(param_2 + 0x3a) = sVar2 + 1;
    *(undefined2 *)(param_2 + 0x38) = 300;
  }
  sVar2 = *(short *)(param_2 + 0x38) + -1;
  *(short *)(param_2 + 0x38) = sVar2;
  if (0 < sVar2) {
    return;
  }
  *(short *)(param_2 + 0x3a) = *(short *)(param_2 + 0x3a) + 1;
  *(undefined2 *)(param_2 + 0x38) = 0x78;
  zz_01deb68_(param_1,2,param_2 + 0x20,param_2 + 0x2c,param_2 + 0x48);
LAB_801d67bc:
  *(undefined1 *)(param_2 + 0x48) = 2;
  local_28 = FLOAT_8043becc;
  local_24 = FLOAT_8043bed4;
  local_20 = FLOAT_8043becc;
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x964),&local_28,(float *)(param_1 + 0x164));
  fVar1 = FLOAT_8043bed8;
  *(float *)(param_1 + 0x170) = *(float *)(param_1 + 0x164);
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x168);
  *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x16c);
  *(float *)(param_1 + 0x174) = *(float *)(param_1 + 0x174) - fVar1;
  sVar2 = *(short *)(param_2 + 0x38) + -1;
  *(short *)(param_2 + 0x38) = sVar2;
  if (sVar2 < 1) {
    *(undefined2 *)(param_2 + 0x3a) = 0;
  }
  return;
}



// ==== 801d684c  zz_01d684c_ ====

void zz_01d684c_(int param_1,int param_2)

{
  float fVar1;
  byte bVar2;
  
  bVar2 = 0;
  fVar1 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c6) ^ 0x80000000) -
                 DOUBLE_8043bee0) /
          (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c4) ^ 0x80000000) -
                 DOUBLE_8043bee0);
  if (fVar1 < DAT_8038def4) {
    bVar2 = 1;
    if (fVar1 < DAT_8038def8) {
      bVar2 = 2;
      if (fVar1 < DAT_8038defc) {
        bVar2 = 3;
        if (fVar1 < DAT_8038df00) {
          bVar2 = 4;
          if (fVar1 < DAT_8038df04) {
            bVar2 = 5;
            if (fVar1 < DAT_8038df08) {
              bVar2 = 6;
              if (fVar1 < DAT_8038df0c) {
                bVar2 = 7;
                if (fVar1 < DAT_8038df10) {
                  bVar2 = 8;
                }
              }
            }
          }
        }
      }
    }
  }
  if (7 < bVar2) {
    bVar2 = 7;
  }
  if (*(char *)(param_2 + 0x54) < (char)bVar2) {
    *(byte *)(param_2 + 0x54) = bVar2;
  }
  if ((*(char *)(param_2 + 0x5a) == '\0') && ('\x02' < *(char *)(param_2 + 0x54))) {
    *(undefined1 *)(param_2 + 0x5a) = 1;
    zz_00e9ce4_((double)FLOAT_8043becc,2,0x20,1,DAT_8031a0f0);
  }
  return;
}



// ==== 801d69b0  zz_01d69b0_ ====

void zz_01d69b0_(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_2 + 0x49);
  if (cVar1 == '\x01') {
    sVar2 = *(short *)(param_2 + 0x3e) + -1;
    *(short *)(param_2 + 0x3e) = sVar2;
    if (sVar2 < 1) {
      *(undefined1 *)(param_2 + 0x49) = 0;
      *(undefined2 *)(param_2 + 0x3e) = 0;
      *(undefined1 *)(param_2 + 0x50) = 1;
      *(undefined1 *)(param_2 + 0x4b) = 0xff;
      *(undefined4 *)(param_1 + 0x5a0) = 0xffffffff;
      zz_01fd114_(param_1);
      iVar3 = 4;
      do {
        if (((uint)*(byte *)(param_2 + 0x4a) & 1 << iVar3) == 0) {
          zz_01fb398_(param_1,(char)iVar3);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < 8);
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (((*(byte *)(param_2 + 0x4a) & 0xf0) == 0 || (*(char *)(param_2 + 0x50) == '\0')))) {
    *(char *)(param_2 + 0x49) = *(char *)(param_2 + 0x49) + '\x01';
    *(undefined4 *)(param_1 + 0x5a0) = 0xffffdfff;
    *(undefined1 *)(param_2 + 0x50) = 0;
    *(undefined2 *)(param_2 + 0x3e) = 0x4b0;
    *(undefined1 *)(param_2 + 0x52) = 0;
    *(undefined2 *)(param_2 + 0x3c) = 0;
    *(undefined2 *)(param_2 + 0x44) = 0x1e;
    zz_01d72b8_(param_1);
  }
  return;
}



// ==== 801d6ad8  zz_01d6ad8_ ====

void zz_01d6ad8_(int param_1,int param_2)

{
  char cVar1;
  short sVar3;
  int iVar2;
  
  if ((((PTR_DAT_80433934[0x1f] == '\0') && (*(char *)(param_1 + 0x18) == '\x01')) &&
      ('\x01' < *(char *)(param_1 + 0x19))) &&
     (sVar3 = *(short *)(param_2 + 0x40) + -1, *(short *)(param_2 + 0x40) = sVar3, sVar3 < 1)) {
    *(undefined *)(param_2 + 0x4d) = (&DAT_80435ae0)[*(char *)(param_2 + 0x54)];
    if (*(char *)(param_2 + 0x4e) < *(char *)(param_2 + 0x4d)) {
      *(char *)(param_2 + 0x4e) = *(char *)(param_2 + 0x4e) + '\x01';
      zz_01f9fac_(param_1,*(undefined1 *)(param_2 + 0x4f));
      iVar2 = *(char *)(param_2 + 0x4f) + 1;
      cVar1 = (char)(iVar2 >> 0x1f);
      *(byte *)(param_2 + 0x4f) =
           (cVar1 * '\b' | (byte)((uint)(iVar2 * 0x20000000 + (iVar2 >> 0x1f)) >> 0x1d)) - cVar1;
      *(undefined2 *)(param_2 + 0x40) = 0x78;
    }
    else {
      *(undefined2 *)(param_2 + 0x40) = 1;
    }
  }
  return;
}



// ==== 801d6bbc  zz_01d6bbc_ ====

void zz_01d6bbc_(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  short sVar4;
  int iVar3;
  
  *(short *)(param_1 + 0x1924) =
       *(short *)(param_1 + 0x1924) - (*(char *)(param_2 + 0x54) * 0x100 + 0x80);
  if ((PTR_DAT_80433934[0x1f] == '\0') && (*(short *)(param_2 + 0x3e) != 0)) {
    zz_01d71d4_(param_1,param_2);
    sVar4 = *(short *)(param_2 + 0x3c) + -1;
    *(short *)(param_2 + 0x3c) = sVar4;
    if (sVar4 < 1) {
      uVar2 = countLeadingZeros((int)*(char *)(param_1 + 0x88));
      cVar1 = (&DAT_80436264)[uVar2 >> 5];
      if (cVar1 < '\x01') {
        *(undefined2 *)(param_2 + 0x3c) = 1;
      }
      else {
        *(char *)(param_2 + 0x51) =
             *(char *)(param_2 + 0x51) - (*(char *)(param_2 + 0x51) / cVar1) * cVar1;
        cVar1 = *(char *)(param_2 + 0x51);
        *(char *)(param_2 + 0x51) = cVar1 + '\x01';
        iVar3 = zz_006bc74_(param_1,(char *)(&DAT_803c6dec)[(uVar2 >> 5) * 6 + (int)cVar1]);
        if (iVar3 == 0) {
          *(undefined2 *)(param_2 + 0x3c) = 1;
        }
        else {
          zz_006bda8_(param_1);
          switch(*(undefined1 *)(param_2 + 0x54)) {
          case 1:
            *(undefined2 *)(param_2 + 0x3c) = 8;
            zz_0082824_(param_1,0x80);
            break;
          case 2:
            *(undefined2 *)(param_2 + 0x3c) = 4;
            zz_0082824_(param_1,0x80);
            break;
          case 3:
            *(undefined2 *)(param_2 + 0x3c) = 0x10;
            zz_01d7d2c_(param_1,0,(undefined4 *)&DAT_8038df14);
            break;
          case 4:
            *(undefined2 *)(param_2 + 0x3c) = 10;
            zz_01d7d2c_(param_1,0,(undefined4 *)&DAT_8038df14);
            break;
          case 5:
            *(undefined2 *)(param_2 + 0x3c) = 6;
            zz_01d7d2c_(param_1,0,(undefined4 *)&DAT_8038df14);
            break;
          case 6:
            *(undefined2 *)(param_2 + 0x3c) = 0x28;
            zz_01fc1b0_(param_1,0x16);
            zz_01fc1b0_(param_1,0x17);
            zz_01fc1b0_(param_1,0x18);
            zz_01fc1b0_(param_1,0x19);
            break;
          case 7:
            iVar3 = *(char *)(param_2 + 0x52) + 1;
            cVar1 = (char)(iVar3 >> 0x1f);
            *(byte *)(param_2 + 0x52) =
                 (cVar1 * ' ' | (byte)((uint)(iVar3 * 0x8000000 + (iVar3 >> 0x1f)) >> 0x1b)) - cVar1
            ;
            if (*(char *)(param_2 + 0x52) == '\0') {
              *(undefined2 *)(param_2 + 0x3c) = 0x78;
            }
            else {
              *(undefined2 *)(param_2 + 0x3c) = 4;
            }
            zz_01fc1b0_(param_1,0x16);
          }
        }
      }
    }
  }
  return;
}



// ==== 801d6e18  zz_01d6e18_ ====

void zz_01d6e18_(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  short sVar3;
  
  if (*(char *)(param_1 + 0x493) != '\0') {
    return;
  }
  if (PTR_DAT_80433934[0x15dd] == '\0') {
    return;
  }
  cVar1 = *(char *)(param_2 + 0x56);
  switch(cVar1) {
  case '\0':
    *(char *)(param_2 + 0x56) = cVar1 + '\x01';
    *(undefined1 *)(param_2 + 0x57) = 1;
    *(undefined2 *)(param_2 + 0x42) = 0x1a4;
  case '\x01':
    sVar3 = *(short *)(param_2 + 0x42) + -1;
    *(short *)(param_2 + 0x42) = sVar3;
    if (sVar3 < 1) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
switchD_801d6e6c_caseD_2:
      uVar2 = zz_01d7170_(param_1,param_2,0x16);
      if (uVar2 != 0) {
        *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
      }
    }
    break;
  case '\x02':
    goto switchD_801d6e6c_caseD_2;
  case '\x03':
    uVar2 = zz_01d7170_(param_1,param_2,0x21);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\x04':
    uVar2 = zz_01d7170_(param_1,param_2,0x19);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\x05':
    uVar2 = zz_01d7170_(param_1,param_2,0x1a);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\x06':
    uVar2 = zz_01d7170_(param_1,param_2,0x22);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\a':
    uVar2 = zz_01d7170_(param_1,param_2,0x23);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\b':
    *(char *)(param_2 + 0x56) = cVar1 + '\x01';
    *(undefined1 *)(param_2 + 0x57) = 0;
  case '\t':
    if (*(char *)(param_2 + 0x57) != '\0') {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
switchD_801d6e6c_caseD_a:
      uVar2 = zz_01d7170_(param_1,param_2,0x17);
      if (uVar2 != 0) {
        *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
      }
    }
    break;
  case '\n':
    goto switchD_801d6e6c_caseD_a;
  case '\v':
    uVar2 = zz_01d7170_(param_1,param_2,0x27);
    if (uVar2 != 0) {
      *(char *)(param_2 + 0x56) = *(char *)(param_2 + 0x56) + '\x01';
    }
    break;
  case '\f':
    *(undefined1 *)(param_2 + 0x56) = 8;
  }
  return;
}



// ==== 801d6ff4  zz_01d6ff4_ ====

void zz_01d6ff4_(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(PTR_DAT_80433934 + 0xbc);
  if (iVar4 == 0) {
    PTR_DAT_80433934[0x1834] = 0;
  }
  else {
    if ((-1 < *(char *)(iVar4 + 0x199)) &&
       (iVar2 = zz_00ea0f0_((int)*(char *)(iVar4 + 0x199)), iVar2 == 0)) {
      *(undefined1 *)(iVar4 + 0x199) = 0xff;
    }
    PTR_DAT_80433934[0x1834] = 1;
    cVar1 = *(char *)(iVar4 + 0x19d);
    if (cVar1 == '\x02') {
      uVar3 = zz_01d7170_(iVar4,iVar4 + 0x144,0x14);
      if (uVar3 != 0) {
        *(char *)(iVar4 + 0x19d) = *(char *)(iVar4 + 0x19d) + '\x01';
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(iVar4 + 0x19d) = 1;
      }
      else if (cVar1 < '\0') {
        return;
      }
      uVar3 = zz_00ea170_(0x12,0,-1,0x13);
      if (-1 < (int)uVar3) {
        *(char *)(iVar4 + 0x19d) = *(char *)(iVar4 + 0x19d) + '\x01';
      }
    }
    else if (cVar1 == '\x04') {
      PTR_DAT_80433934[0x1834] = 0;
    }
    else if ((cVar1 < '\x04') && (uVar3 = zz_01d7170_(iVar4,iVar4 + 0x144,0x15), uVar3 != 0)) {
      *(char *)(iVar4 + 0x19d) = *(char *)(iVar4 + 0x19d) + '\x01';
    }
  }
  return;
}



// ==== 801d7134  zz_01d7134_ ====

uint zz_01d7134_(int param_1,int param_2)

{
  uint uVar1;
  
  if (*(char *)(param_1 + 0x19b) == '\0') {
    uVar1 = zz_01d7170_(param_1,param_1 + 0x144,param_2);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 801d7170  zz_01d7170_ ====

uint zz_01d7170_(undefined4 param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (*(char *)(param_2 + 0x55) < '\0') {
    uVar1 = zz_00ea170_(0x12,0,-1,param_3);
    *(char *)(param_2 + 0x55) = (char)uVar1;
    uVar1 = (uint)(int)*(char *)(param_2 + 0x55) >> 0x1f ^ 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 801d71d4  zz_01d71d4_ ====

void zz_01d71d4_(int param_1,int param_2)

{
  char cVar1;
  short sVar3;
  uint uVar2;
  int iVar4;
  
  if (*(char *)(param_2 + 0x54) < '\a') {
    sVar3 = *(short *)(param_2 + 0x44) + -1;
    *(short *)(param_2 + 0x44) = sVar3;
    if (sVar3 < 1) {
      do {
        uVar2 = zz_00055fc_();
        cVar1 = *(char *)(*(char *)(param_2 + 0x54) * 8 + -0x7fc7208c + (uVar2 & 7));
        iVar4 = (int)cVar1;
        if (iVar4 < 0) break;
      } while (iVar4 == *(char *)(param_2 + 0x58));
      if (-1 < iVar4) {
        zz_01d7134_(param_1,iVar4);
      }
      *(char *)(param_2 + 0x58) = cVar1;
      if (iVar4 < 1) {
        *(undefined2 *)(param_2 + 0x44) = 0x1e;
      }
      else {
        *(undefined2 *)(param_2 + 0x44) = 0xf0;
      }
    }
  }
  else {
    *(undefined1 *)(param_2 + 0x57) = 1;
  }
  return;
}



// ==== 801d72b8  zz_01d72b8_ ====

void zz_01d72b8_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435ae8)[uVar1 & 1]);
  return;
}



// ==== 801d72fc  zz_01d72fc_ ====

void zz_01d72fc_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435aec)[uVar1 & 7]);
  return;
}



// ==== 801d7340  zz_01d7340_ ====

void zz_01d7340_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435af4)[uVar1 & 3]);
  return;
}



// ==== 801d7384  zz_01d7384_ ====

void zz_01d7384_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  zz_01d7134_(param_1,(int)(char)(&DAT_80435af8)[uVar1 & 7]);
  return;
}



// ==== 801d7564  FUN_801d7564 ====

void FUN_801d7564(int param_1)

{
  (*(code *)(&PTR_FUN_8038dff8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d75a0  FUN_801d75a0 ====

void FUN_801d75a0(int param_1)

{
  (*(code *)(&PTR_FUN_8038e004)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d75dc  FUN_801d75dc ====

/* WARNING: Removing unreachable block (ram,0x801d7720) */
/* WARNING: Removing unreachable block (ram,0x801d75ec) */

void FUN_801d75dc(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 == 0) {
    zz_006a53c_(param_1,10);
  }
  else {
    zz_00665cc_(param_1);
    fVar1 = FLOAT_8043bef0;
    *(float *)(param_1 + 0x558) = FLOAT_8043beec;
    *(float *)(param_1 + 0x55c) = fVar1;
    *(undefined1 *)(param_1 + 0x6f7) = 0x78;
    *(undefined1 *)(param_1 + 0x6ea) = 2;
    if (*(int *)(param_1 + 0xcc) != 0) {
      dVar7 = (double)FLOAT_8043bef4;
      iVar2 = 0;
      pcVar4 = &DAT_80435b00;
      iVar5 = 0;
      do {
        iVar3 = *pcVar4 * 0x30;
        local_38 = *(float *)(param_1 + iVar3 + 0x8e0);
        local_34 = *(undefined4 *)(param_1 + iVar3 + 0x8f0);
        local_30 = *(undefined4 *)(param_1 + iVar3 + 0x900);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x524),&local_38,&local_38);
        dVar6 = gnt4_PSVECMag_bl(&local_38);
        if (dVar6 < dVar7) {
          iVar2 = (int)*pcVar4;
          dVar7 = dVar6;
        }
        iVar5 = iVar5 + 1;
        pcVar4 = pcVar4 + 1;
      } while (iVar5 < 4);
      if (*(float *)(param_1 + 0x528) <= *(float *)(param_1 + iVar2 * 0x30 + 0x8f0)) {
        *(char *)(param_1 + 0x6ea) = (char)iVar2;
      }
    }
    zz_01deb68_(param_1,9,param_1 + 0x144,param_1 + 0x150,param_1 + 0x6f7);
    zz_01d773c_(param_1);
  }
  return;
}



// ==== 801d773c  zz_01d773c_ ====

void zz_01d773c_(int param_1)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  float local_18;
  float local_14;
  float local_10;
  
  pfVar3 = (float *)(param_1 + 0x144);
  zz_00665cc_(param_1);
  local_18 = FLOAT_8043bef0;
  local_14 = FLOAT_8043bef8;
  local_10 = FLOAT_8043bef0;
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + *(char *)(param_1 + 0x6ea) * 0x30 + 0x8d4),&local_18,pfVar3);
  local_18 = *(float *)(param_1 + 0x524);
  local_14 = *(float *)(param_1 + 0x528);
  local_10 = *(float *)(param_1 + 0x52c);
  if (*(char *)(param_1 + 0x6ea) != '\x02') {
    if (*(float *)(param_1 + 0x148) < local_14) {
      local_14 = *(float *)(param_1 + 0x148);
    }
  }
  gnt4_PSVECSubtract_bl(&local_18,pfVar3,&local_18);
  zz_006ebb4_(&local_18,&local_18);
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) + FLOAT_8043befc;
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x55c),&local_18,&local_18);
  gnt4_PSVECAdd_bl(pfVar3,&local_18,(float *)(param_1 + 0x150));
  fVar2 = FLOAT_8043bef0;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801d7864  FUN_801d7864 ====

void FUN_801d7864(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a53c_(param_1,0);
  return;
}



// ==== 801d789c  FUN_801d789c ====

void FUN_801d789c(int param_1)

{
  (*(code *)(&PTR_LAB_8038e010)[*(char *)(param_1 + 0x540)])();
  if (*(short *)(param_1 + 0x548) != 0) {
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  return;
}



// ==== 801d7914  FUN_801d7914 ====

void FUN_801d7914(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043bf00;
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_8043beec;
    zz_01f23b0_(param_1,2);
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  return;
}



// ==== 801d7988  FUN_801d7988 ====

void FUN_801d7988(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043bef0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801d79d0  zz_01d79d0_ ====

void zz_01d79d0_(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8038e020; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup(5,piVar1,3);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801d7a64;
      *(code **)(iVar2 + 0x10c) = FUN_801d7cc4;
      *(undefined4 *)(iVar2 + 0x54) = param_1;
    }
  }
  return;
}



// ==== 801d7a64  FUN_801d7a64 ====

void FUN_801d7a64(int param_1)

{
  (*(code *)(&PTR_FUN_8038e048)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801d7aa0  FUN_801d7aa0 ====

void FUN_801d7aa0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043bf08;
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
  zz_01d7b2c_(param_9);
  return;
}



// ==== 801d7b2c  zz_01d7b2c_ ====

void zz_01d7b2c_(int param_1)

{
  (*(code *)(&PTR_FUN_80435b08)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801d7b64  FUN_801d7b64 ====

void FUN_801d7b64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  iVar4 = *(int *)(param_9 + 0x54);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(iVar4 + 0x15c) == 0) {
      return;
    }
    dVar5 = (double)FLOAT_8043bf14;
    *(char *)(param_9 + 0x1a) = cVar1 + '\x01';
    param_3 = (double)FLOAT_8043bf10;
    param_2 = (double)*(float *)(iVar4 + 0x154);
    *(float *)(param_9 + 100) =
         -(float)(param_3 * (double)(float)(param_2 - dVar5) - (double)FLOAT_8043bf0c);
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(iVar4 + 0x15c);
    if (*(char *)(iVar4 + 0x11) == '\0') {
      *(undefined1 *)(param_9 + 0x82) = 7;
    }
    else {
      *(undefined1 *)(param_9 + 0x82) = 0x15;
    }
  }
  iVar4 = *(int *)(iVar4 + 0x15c);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else if (*(int *)(param_9 + 0x180) != iVar4) {
    *(int *)(param_9 + 0x180) = iVar4;
    fVar2 = FLOAT_8043bf08;
    if (*(int *)(param_9 + 0x180) != -1) {
      uVar3 = zz_00055fc_();
      fVar2 = (float)((double)CONCAT44(0x43300000,uVar3 % 3) - DOUBLE_8043bf18);
    }
    zz_01a76fc_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801d7ca4  FUN_801d7ca4 ====

void FUN_801d7ca4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d7cc4  FUN_801d7cc4 ====

void FUN_801d7cc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(param_9 + 0x54);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  if (*(char *)(iVar1 + 0x11) == '\0') {
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x45);
  }
  else {
    zz_0009958_(*(int *)(param_9 + 0xe0),2);
  }
  return;
}



// ==== 801d7d2c  zz_01d7d2c_ ====

void zz_01d7d2c_(int param_1,uint param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  int iVar3;
  
  iVar3 = (param_2 & 0xff) * 0x30;
  puVar2 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0x5f;
    *(uint *)(puVar2 + 0x14) = param_2;
    puVar2[0x12] = 0;
    *(code **)(puVar2 + 0xc) = FUN_801d7e9c;
    *(code **)(puVar2 + 0x10c) = FUN_801d85f8;
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
    uVar1 = param_3[1];
    *(undefined4 *)(puVar2 + 0x148) = *param_3;
    *(undefined4 *)(puVar2 + 0x14c) = uVar1;
    *(undefined4 *)(puVar2 + 0x150) = param_3[2];
    *(float *)(puVar2 + 0x58) = *(float *)(puVar2 + 0xb4) * *(float *)(&DAT_8038e06c + iVar3);
    *(float *)(puVar2 + 0x5c) = *(float *)(puVar2 + 0xb4) * *(float *)(&DAT_8038e070 + iVar3);
    *(float *)(puVar2 + 0x60) = *(float *)(puVar2 + 0xb4) * *(float *)(&DAT_8038e074 + iVar3);
  }
  return;
}



// ==== 801d7e9c  FUN_801d7e9c ====

void FUN_801d7e9c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8038e088)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801d7eec  FUN_801d7eec ====

void FUN_801d7eec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  float local_28;
  float local_24;
  float local_20;
  
  pcVar6 = *(char **)(param_9 + 200);
  iVar7 = *(int *)(param_9 + 0x90);
  iVar4 = (*(uint *)(param_9 + 0x14) & 0xff) * 0x30;
  *(undefined1 *)(param_9 + 0x18) = 1;
  if (((pcVar6 != (char *)0x0) && (*pcVar6 != '\0')) &&
     (*(char *)(*(int *)(pcVar6 + 0x20) + 0x18) < '\x02')) {
    *(int *)(param_9 + 0xcc) = *(int *)(pcVar6 + 0x20);
  }
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + 0x8d4),
             (float *)(param_9 + 0x148),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + (char)(&DAT_8038e07c)[iVar4] * 4 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + (char)(&DAT_8038e07c)[iVar4] * 4 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + (char)(&DAT_8038e07c)[iVar4] * 4 + 0x8f4);
  *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x24);
  if ((&DAT_8038e07d)[iVar4] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043bf20,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  iVar5 = *(int *)(param_9 + 200);
  if (iVar5 == 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043bf24,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x154))
    ;
  }
  else {
    uVar3 = *(undefined4 *)(iVar5 + 0x68);
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(iVar5 + 100);
    *(undefined4 *)(param_9 + 0x158) = uVar3;
    *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(iVar5 + 0x6c);
  }
  iVar5 = FUN_8006c334((double)*(float *)(&DAT_8038e078 + iVar4),param_9,(float *)(param_9 + 0x154))
  ;
  if (iVar5 == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
    if ((&DAT_8038e083)[iVar4] != '\0') {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    cVar1 = (&DAT_8038e07f)[iVar4];
    if (cVar1 == '\x02') {
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
      local_24 = FLOAT_8043bf28;
      dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
      if ((double)FLOAT_8043bf28 < dVar8) {
        *(float *)(param_9 + 0x38) = local_28;
        *(float *)(param_9 + 0x3c) = local_24;
        *(float *)(param_9 + 0x40) = local_20;
      }
    }
    else if (cVar1 < '\x02') {
      if ((cVar1 != '\0') && (-1 < cVar1)) {
        gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
        local_28 = FLOAT_8043bf28;
        dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
        if ((double)FLOAT_8043bf28 < dVar8) {
          *(float *)(param_9 + 0x38) = local_28;
          *(float *)(param_9 + 0x3c) = local_24;
          *(float *)(param_9 + 0x40) = local_20;
        }
      }
    }
    else if (cVar1 < '\x04') {
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
      local_20 = FLOAT_8043bf28;
      dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
      if ((double)FLOAT_8043bf28 < dVar8) {
        *(float *)(param_9 + 0x38) = local_28;
        *(float *)(param_9 + 0x3c) = local_24;
        *(float *)(param_9 + 0x40) = local_20;
      }
    }
  }
  else {
    FUN_801d8660(param_9,iVar7);
  }
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8038e05c + iVar4),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8038e05c + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_8038e060 + iVar4);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar7 + (char)(&DAT_8038e05a)[iVar4] * 0x30 + 0x8f8);
  if (-1 < (char)(&DAT_8038e07e)[iVar4]) {
    uVar9 = zz_0048288_(param_9);
    zz_00aedc0_(iVar7,(float *)(param_9 + 0x114),(int)(char)(&DAT_8038e07e)[iVar4],
                *(undefined1 *)(param_9 + 0x88));
  }
  *(undefined2 *)(param_9 + 0x1c) = 300;
  *(undefined2 *)(param_9 + 0x80) = 0x1400;
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8038e084 + iVar4);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  iVar5 = zz_008ac80_(param_9,(int)(char)(&DAT_8038e05b)[iVar4]);
  if (iVar5 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    uVar2 = *(ushort *)(&DAT_8038e058 + iVar4);
    if ((uVar2 & 0x4000) == 0) {
      zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),(float *)(uint)uVar2,(int)*(char *)(param_9 + 0x88),in_r7
                  ,in_r8,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x144) = 0;
      *(undefined1 *)(param_9 + 0x82) = 1;
    }
    else {
      iVar5 = zz_0006f78_(iVar7);
      zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                  *(int *)(param_9 + 0xe0),(float *)(uVar2 & 0xffffbfff),
                  (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x144) = 1;
      *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    }
    zz_00f061c_((double)FLOAT_8043bf2c,iVar7,(int)*(short *)(&DAT_8038e080 + iVar4));
  }
  return;
}



// ==== 801d8368  FUN_801d8368 ====

void FUN_801d8368(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (*(short *)(param_1 + 0x1c6) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    zz_00b19b4_(param_1,2,0x10);
  }
  else if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        fVar1 = *(float *)(param_1 + 0x160) - *(float *)(param_1 + 0x24);
        if (fVar1 < FLOAT_8043bf28) {
          fVar1 = -fVar1;
        }
        if (fVar1 <= FLOAT_8043bf30) {
          *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
          *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
          *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
          *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
          iVar2 = (*(uint *)(param_1 + 0x14) & 0xff) * 0x30;
          FUN_80083874((double)*(float *)(&DAT_8038e068 + iVar2),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_8038e064 + iVar2),param_1,
                       (char)*(undefined4 *)(&DAT_8038e060 + iVar2));
          zz_00833ec_(param_1);
          zz_0083524_(param_1);
          *(float *)(param_1 + 0x58) =
               *(float *)(param_1 + 0xb4) * *(float *)(&DAT_8038e06c + iVar2);
          *(float *)(param_1 + 0x5c) =
               *(float *)(param_1 + 0xb4) * *(float *)(&DAT_8038e070 + iVar2);
          *(float *)(param_1 + 0x60) =
               *(float *)(param_1 + 0xb4) * *(float *)(&DAT_8038e074 + iVar2);
          iVar2 = zz_0083714_(param_1);
          if (iVar2 == 0) {
            iVar2 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,
                                auStack_28);
            if (iVar2 != 0) {
              *(float *)(param_1 + 0x20) = local_1c;
              *(undefined4 *)(param_1 + 0x24) = local_18;
              *(undefined4 *)(param_1 + 0x28) = local_14;
              FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
              zz_0019550_(param_1,&local_1c,0);
              *(undefined1 *)(param_1 + 0x18) = 2;
            }
          }
          else {
            *(undefined1 *)(param_1 + 0x18) = 2;
            zz_008aff0_(param_1);
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
          zz_00b19b4_(param_1,2,0x10);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 801d859c  FUN_801d859c ====

void FUN_801d859c(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801d85d8  FUN_801d85d8 ====

void FUN_801d85d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d85f8  FUN_801d85f8 ====

/* WARNING: Removing unreachable block (ram,0x801d860c) */

void FUN_801d85f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043bf34 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 801d8660  FUN_801d8660 ====

/* WARNING: Removing unreachable block (ram,0x801d8710) */
/* WARNING: Removing unreachable block (ram,0x801d8670) */

undefined4 FUN_801d8660(int param_1,int param_2)

{
  undefined4 uVar1;
  double dVar2;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_1 + 200) == 0) {
    uVar1 = 1;
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x154),(float *)(param_1 + 0x20),&local_28);
    dVar2 = gnt4_PSVECSquareMag_bl(&local_28);
    if (dVar2 <= (double)FLOAT_8043bf28) {
      uVar1 = 1;
    }
    else {
      *(float *)(param_1 + 0x38) = local_28;
      *(undefined4 *)(param_1 + 0x3c) = local_24;
      *(undefined4 *)(param_1 + 0x40) = local_20;
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      if ((double)(*(float *)(param_2 + 0x814) * *(float *)(param_2 + 0x814)) < dVar2) {
        *(undefined4 *)(param_1 + 200) = 0;
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 801d8874  FUN_801d8874 ====

void FUN_801d8874(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80435b10)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801d88bc  FUN_801d88bc ====

void FUN_801d88bc(int param_1)

{
  (*(code *)(&PTR_FUN_8038e0d8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d88f8  FUN_801d88f8 ====

void FUN_801d88f8(int param_1)

{
  (*(code *)(&PTR_FUN_8038e0e4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d8934  FUN_801d8934 ====

void FUN_801d8934(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d8968  FUN_801d8968 ====

void FUN_801d8968(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801d89b8  FUN_801d89b8 ====

void FUN_801d89b8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d89ec  FUN_801d89ec ====

void FUN_801d89ec(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038e140)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d8a48  FUN_801d8a48 ====

void FUN_801d8a48(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043bf3c;
  fVar1 = FLOAT_8043bf38;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  *(undefined1 *)(param_1 + 0x6eb) = 0;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043bf40,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043bf44,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  return;
}



// ==== 801d8ba8  FUN_801d8ba8 ====

void FUN_801d8ba8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043bf40,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043bf38;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043bf48;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 801d8c70  FUN_801d8c70 ====

void FUN_801d8c70(int param_1)

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
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043bf4c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043bf50;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043bf4c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043bf38;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043bf54,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801d8d4c  FUN_801d8d4c ====

void FUN_801d8d4c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  fVar1 = FLOAT_8043bf38;
  if ((*(char *)(param_1 + 0x1d9) != '\0') &&
     (*(undefined1 *)(param_1 + 0x745) = 1, *(float *)(param_1 + 0x48) < fVar1)) {
    *(float *)(param_1 + 0x48) = fVar1;
  }
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if ((*(char *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    dVar3 = (double)FLOAT_8043bf44;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(char *)(param_1 + 0x6eb) = *(char *)(param_1 + 0x6eb) + '\x01';
    *(byte *)(param_1 + 0x6eb) = *(byte *)(param_1 + 0x6eb) & 1;
    zz_004beb8_(dVar3,param_1,0xf,3,
                (int)*(char *)(param_1 + 0x6ea) + (int)*(char *)(param_1 + 0x6eb),0xffffffff,
                0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043bf40,param_1);
  FUN_80067310((double)FLOAT_8043bf50,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043bf50 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801d8f14  FUN_801d8f14 ====

void FUN_801d8f14(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038e150)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d8f70  FUN_801d8f70 ====

void FUN_801d8f70(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043bf3c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0xb;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043bf44;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,6,1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043bf38;
  return;
}



// ==== 801d9048  FUN_801d9048 ====

void FUN_801d9048(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043bf38;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_8043bf58;
    fVar2 = FLOAT_8043bf4c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_8043bf38;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 801d90e8  FUN_801d90e8 ====

void FUN_801d90e8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043bf4c;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar3 = FLOAT_8043bf38;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar3;
  }
  zz_006ed8c_((double)FLOAT_8043bf40,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043bf38;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    if (*(char *)(param_1 + 0x1cf2) != '\0') {
      dVar4 = (double)FLOAT_8043bf44;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  if (FLOAT_8043bf50 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801d91e0  FUN_801d91e0 ====

void FUN_801d91e0(int param_1)

{
  zz_006ed8c_((double)FLOAT_8043bf5c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ((*(float *)(param_1 + 0x44) < FLOAT_8043bf50) &&
     (zz_004cd24_(param_1,0xf), *(char *)(param_1 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    return;
  }
  if (FLOAT_8043bf50 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801d927c  FUN_801d927c ====

void FUN_801d927c(int param_1)

{
  (*(code *)(&PTR_FUN_8038e160)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d92b8  FUN_801d92b8 ====

void FUN_801d92b8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d92ec  FUN_801d92ec ====

void FUN_801d92ec(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801d9418  FUN_801d9418 ====

void FUN_801d9418(int param_1)

{
  double dVar1;
  
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x191a) = 0;
    dVar1 = DOUBLE_8043bf68;
    *(undefined2 *)(param_1 + 0x1902) = 0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar1) * FLOAT_8043bf60);
    *(undefined2 *)(param_1 + 0x18dc) = 0;
  }
  return;
}



// ==== 801d94a4  FUN_801d94a4 ====

void FUN_801d94a4(int param_1)

{
  (*(code *)(&PTR_FUN_8038f010)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d94e0  FUN_801d94e0 ====

void FUN_801d94e0(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_8038f024)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d9528  FUN_801d9528 ====

void FUN_801d9528(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d955c  FUN_801d955c ====

void FUN_801d955c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d9590  FUN_801d9590 ====

void FUN_801d9590(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801d95c4  FUN_801d95c4 ====

void FUN_801d95c4(int param_1)

{
  if ((*(char *)(param_1 + 0x540) == '\0') && ((*(uint *)(param_1 + 0x5e0) & 0x2000) != 0)) {
    *(undefined1 *)(param_1 + 0x581) = 5;
    FUN_801d96b0(param_1);
  }
  else {
    zz_01c956c_(param_1);
  }
  return;
}



// ==== 801d9654  FUN_801d9654 ====

void FUN_801d9654(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801d96b0  FUN_801d96b0 ====

void FUN_801d96b0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038f0b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801d970c  FUN_801d970c ====

void FUN_801d970c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar3 = FLOAT_8043bf80;
  fVar2 = FLOAT_8043bf74;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0xc;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043bf84,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_8043bf88;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801d9870  FUN_801d9870 ====

void FUN_801d9870(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043bf84,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043bf74;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043bf8c * dVar4);
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043bf8c * -dVar4);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 801d995c  FUN_801d995c ====

void FUN_801d995c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043bf8c * dVar5);
    dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
    fVar2 = FLOAT_8043bf74;
    dVar6 = (double)FLOAT_8043bf88;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043bf8c * -dVar5);
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043bf84,param_1);
  uVar3 = FUN_800668cc((double)FLOAT_8043bf90,param_1);
  if (0 < (int)uVar3) {
    zz_006ed8c_((double)FLOAT_8043bf70,param_1);
  }
  FUN_80067310((double)FLOAT_8043bf94,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043bf94 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801d9b4c  FUN_801d9b4c ====

void FUN_801d9b4c(int param_1)

{
  FUN_801d9b6c(param_1);
  return;
}



// ==== 801d9b6c  FUN_801d9b6c ====

void FUN_801d9b6c(int param_1)

{
  zz_01c9c9c_(param_1);
  return;
}



// ==== 801d9bb8  FUN_801d9bb8 ====

void FUN_801d9bb8(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  (*(code *)(&PTR_FUN_8038f0e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d9c00  FUN_801d9c00 ====

void FUN_801d9c00(int param_1)

{
  FUN_801ca34c(param_1);
  return;
}



// ==== 801d9c28  FUN_801d9c28 ====

void FUN_801d9c28(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x75);
  }
  *(undefined1 *)(param_1 + 0x1cef) = 0;
  return;
}



// ==== 801d9c7c  FUN_801d9c7c ====

void FUN_801d9c7c(int param_1)

{
  FUN_801ca34c(param_1);
  return;
}



// ==== 801d9ca4  FUN_801d9ca4 ====

void FUN_801d9ca4(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 != 0) {
    if (*(char *)(param_1 + 0x6e9) == '\0') {
      *(undefined2 *)(param_1 + 0x191a) = 0x4000;
      *(undefined2 *)(param_1 + 0x1902) = 0;
      zz_0082824_(param_1,0x77);
    }
    else {
      *(undefined2 *)(param_1 + 0x191a) = 0;
      *(undefined2 *)(param_1 + 0x1902) = 0xc000;
      zz_0082824_(param_1,0x76);
    }
  }
  *(undefined1 *)(param_1 + 0x1cef) = 0;
  return;
}



// ==== 801d9d34  FUN_801d9d34 ====

undefined4 FUN_801d9d34(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  
  if ((*(char *)(param_1 + 0x746) == '\0') || (iVar2 = zz_006dbe0_(param_1,2,1,0), iVar2 == 0)) {
    uVar3 = 0;
  }
  else {
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      zz_006bf80_(param_1);
      fVar1 = FLOAT_8043bf9c;
      *(undefined1 *)(param_1 + 0x746) = 0;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(undefined1 *)(param_1 + 0x6ea) = 3;
      if (*(char *)(param_1 + 0x6e9) == '\0') {
        *(undefined1 *)(param_1 + 0x6ea) = 2;
      }
      zz_004beb8_((double)FLOAT_8043bf88,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                  0xffffffff);
    }
    else {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_8043bf98 + *(float *)(param_1 + 0x1dc8);
    }
    uVar3 = 0x81cd;
  }
  return uVar3;
}



// ==== 801d9e4c  FUN_801d9e4c ====

void FUN_801d9e4c(int param_1)

{
  *(short *)(param_1 + 0x18dc) = *(short *)(param_1 + 0x18dc) >> 1;
  FUN_801d9e78(param_1);
  return;
}



// ==== 801d9e78  FUN_801d9e78 ====

void FUN_801d9e78(int param_1)

{
  FUN_801ca34c(param_1);
  return;
}



// ==== 801d9ea0  FUN_801d9ea0 ====

void FUN_801d9ea0(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    zz_00107a0_(param_1,0xe);
  }
  return;
}



// ==== 801d9ed8  FUN_801d9ed8 ====

void FUN_801d9ed8(int param_1)

{
  zz_00e19a8_(param_1,0xe,param_1 + 0x6f7);
  return;
}



// ==== 801d9f00  FUN_801d9f00 ====

/* WARNING: Removing unreachable block (ram,0x801da028) */
/* WARNING: Removing unreachable block (ram,0x801da020) */
/* WARNING: Removing unreachable block (ram,0x801da018) */
/* WARNING: Removing unreachable block (ram,0x801d9f20) */
/* WARNING: Removing unreachable block (ram,0x801d9f18) */
/* WARNING: Removing unreachable block (ram,0x801d9f10) */

void FUN_801d9f00(void)

{
  int *piVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  
  for (piVar1 = &DAT_803903b8; -1 < *piVar1; piVar1 = piVar1 + 5) {
    FUN_801da044(0,piVar1);
    FUN_801da044(1,piVar1);
  }
  dVar6 = (double)FLOAT_8043bfa0;
  uVar4 = 0;
  dVar7 = DOUBLE_8043bfa8;
  do {
    dVar5 = (double)(float)(dVar6 * (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000)
                                                   - dVar7));
    for (piVar1 = &DAT_803905fc; -1 < *piVar1; piVar1 = piVar1 + 5) {
      iVar3 = 0;
      do {
        puVar2 = FUN_801da044((char)iVar3,piVar1);
        puVar2[0x13] = (char)uVar4;
        iVar3 = iVar3 + 1;
        *(float *)(puVar2 + 0x68) = (float)((double)*(float *)(puVar2 + 0x68) + dVar5);
      } while (iVar3 < 2);
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 9);
  for (piVar1 = &DAT_80390714; -1 < *piVar1; piVar1 = piVar1 + 5) {
    FUN_801da044(2,piVar1);
  }
  FUN_801dc2a4(0);
  FUN_801dc2a4(1);
  return;
}



// ==== 801da044  FUN_801da044 ====

undefined1 * FUN_801da044(undefined1 param_1,undefined4 *param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  
  puVar3 = zz_008893c_(2,0x39,1,1);
  if (puVar3 != (undefined1 *)0x0) {
    *puVar3 = 1;
    puVar3[0x10] = param_1;
    puVar3[0x11] = (char)*(undefined2 *)(param_2 + 1);
    puVar3[0x12] = (char)*(undefined2 *)((int)param_2 + 6);
    *(code **)(puVar3 + 0xc) = FUN_801da190;
    *(code **)(puVar3 + 0x10c) = FUN_801dc284;
    *(undefined4 *)(puVar3 + 0x144) = *param_2;
    uVar2 = param_2[2];
    *(undefined4 *)(puVar3 + 100) = uVar2;
    *(undefined4 *)(puVar3 + 0x148) = uVar2;
    uVar2 = param_2[3];
    *(undefined4 *)(puVar3 + 0x68) = uVar2;
    *(undefined4 *)(puVar3 + 0x14c) = uVar2;
    uVar2 = param_2[4];
    *(undefined4 *)(puVar3 + 0x6c) = uVar2;
    *(undefined4 *)(puVar3 + 0x150) = uVar2;
    *(undefined4 *)(puVar3 + 0x154) = DAT_803bb384;
    cVar1 = puVar3[0x11];
    if (cVar1 == '\r') {
      if (puVar3[0x12] != '\0') {
        return puVar3;
      }
    }
    else if (cVar1 < '\r') {
      if ('\b' < cVar1) {
        return puVar3;
      }
      if (cVar1 < '\a') {
        return puVar3;
      }
    }
    else if (cVar1 != '\x1b') {
      return puVar3;
    }
    puVar4 = zz_0088c40_(3,(int)puVar3,1,0);
    if (puVar4 != (undefined1 *)0x0) {
      *puVar4 = 1;
      *(code **)(puVar4 + 0xc) = FUN_801dc3ec;
      *(code **)(puVar4 + 0x10c) = FUN_801dc444;
      *(undefined1 **)(puVar4 + 0x8c) = puVar3;
    }
  }
  return puVar3;
}



// ==== 801da190  FUN_801da190 ====

void FUN_801da190(int param_1)

{
  (*(code *)(&PTR_FUN_80390958)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801da1cc  FUN_801da1cc ====

void FUN_801da1cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043bfb0;
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
  FUN_801da25c(param_9);
  return;
}



// ==== 801da25c  FUN_801da25c ====

void FUN_801da25c(int param_1)

{
  (*(code *)(&PTR_LAB_80390968)[*(char *)(param_1 + 0x11)])();
  if (*(char *)(DAT_804362d8 + 0x10c7) == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801da2d4  FUN_801da2d4 ====

void FUN_801da2d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  if (*(int *)(param_9 + 0x180) !=
      (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca)) {
    *(int *)(param_9 + 0x180) = (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca);
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                 (uint)*(float **)(param_9 + 0x180) ^ 0x80000000) -
                               DOUBLE_8043bfa8),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,*(float **)(param_9 + 0x180),param_12,param_13,param_14,param_15,
                param_16);
  }
  return;
}



// ==== 801da3ac  FUN_801da3ac ====

void FUN_801da3ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)(char)*(byte *)(param_9 + 0x10) ^ 0x80000000)
                               - DOUBLE_8043bfa8),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,(float *)(uint)*(byte *)(param_9 + 0x10),param_12,param_13,
                param_14,param_15,param_16);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  return;
}



// ==== 801da424  FUN_801da424 ====

void FUN_801da424(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  
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
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    iVar2 = (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10cc);
    if (*(int *)(param_9 + 0x180) != iVar2) {
      *(int *)(param_9 + 0x180) = iVar2;
      *(int *)(param_9 + 0x144) = (int)(char)(&DAT_80435b18)[*(int *)(param_9 + 0x180)];
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  &DAT_80435b18,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 0x17c) = 0xffffffff;
    }
    if (*(int *)(param_9 + 0x17c) !=
        (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca)) {
      *(int *)(param_9 + 0x17c) =
           (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca);
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                   (uint)*(float **)(param_9 + 0x17c) ^ 0x80000000)
                                 - DOUBLE_8043bfa8),param_2,param_3,param_4,param_5,param_6,param_7,
                  param_8,param_9,0,*(float **)(param_9 + 0x17c),param_12,param_13,param_14,param_15
                  ,param_16);
    }
  }
  return;
}



// ==== 801da568  FUN_801da568 ====

void FUN_801da568(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
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
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    iVar3 = (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca);
    if (*(int *)(param_9 + 0x180) != iVar3) {
      *(int *)(param_9 + 0x180) = iVar3;
      *(int *)(param_9 + 0x144) = (int)(char)(&DAT_80435b1c)[*(int *)(param_9 + 0x180)];
      zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  &DAT_80435b1c,param_12,param_13,param_14,param_15,param_16);
      fVar2 = FLOAT_8043bfb8;
      if (*(int *)(param_9 + 0x180) < 3) {
        fVar2 = FLOAT_8043bfb4;
      }
      *(float *)(param_9 + 100) = fVar2;
    }
  }
  return;
}



// ==== 801da668  FUN_801da668 ====

void FUN_801da668(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    if ((*(char *)(param_9 + 0x12) == '\x02') &&
       (*(int *)(param_9 + 0x180) !=
        (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca))) {
      *(int *)(param_9 + 0x180) =
           (int)*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10ca);
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                   (uint)*(float **)(param_9 + 0x180) ^ 0x80000000)
                                 - DOUBLE_8043bfa8),param_2,param_3,param_4,param_5,param_6,param_7,
                  param_8,param_9,0,*(float **)(param_9 + 0x180),param_12,param_13,param_14,param_15
                  ,param_16);
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) != '\0')) {
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  return;
}



// ==== 801da778  FUN_801da778 ====

void FUN_801da778(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10d4) != '\0') {
        return;
      }
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x82) = 0;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10d4) == '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    dVar5 = DOUBLE_8043bfa8;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    uVar4 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(char *)(param_9 + 0x10) ^ 0x80000000
                                                        ) - dVar5),param_2,param_3,param_4,param_5,
                        param_6,param_7,param_8,*(int *)(param_9 + 0x154),*(int *)(param_9 + 0xe0),
                        param_11,param_12,param_13,param_14,param_15,param_16);
    uVar4 = zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                ,param_16);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  iVar3 = *(int *)(param_9 + 0xe0);
  dVar5 = (double)(float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1c) ^ 0x80000000)
                         - DOUBLE_8043bfa8);
  zz_0008614_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0x154),iVar3,param_11,param_12,param_13,param_14,param_15,param_16)
  ;
  zz_0007c30_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x23 < sVar2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
  if (*(short *)(param_9 + 0x1c) == 5) {
    *(undefined1 *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10d4) = 2;
  }
  return;
}



// ==== 801da8f8  FUN_801da8f8 ====

void FUN_801da8f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10c9) != '\0')) {
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(char *)((int)(&DAT_804362d8)
                                                                     [*(char *)(param_9 + 0x10)] +
                                                               0x10c6) ^ 0x80000000) -
                               DOUBLE_8043bfa8),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,param_9,0,(float *)(&DAT_804362d8)[*(char *)(param_9 + 0x10)],&DAT_804362d8,
                in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  return;
}



// ==== 801daab4  FUN_801daab4 ====

void FUN_801daab4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,uint param_14,int param_15)

{
  char cVar1;
  double dVar2;
  int iVar3;
  float *pfVar4;
  uint uVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if ((*(char *)(param_9 + 0x10) == '\0') && (*(char *)(param_9 + 0x12) != '\0')) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    if (*(char *)((&DAT_804362d8)[*(char *)(param_9 + 0x10)] + 0x10d4) < '\x02') {
      return;
    }
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
  }
  pfVar4 = (float *)(&DAT_804362d8)[*(char *)(param_9 + 0x10)];
  if (*(char *)(pfVar4 + 0x435) < '\x02') {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + -1;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    if (*(char *)(param_9 + 0x10) == '\0') {
      uVar5 = (uint)*(char *)((int)pfVar4 + 0x10c6);
    }
    else {
      param_15 = 0;
      param_14 = 0;
      iVar3 = 4;
      *(undefined1 *)(param_9 + 0x82) = 0;
      pfVar4 = (float *)&DAT_803c71fc;
      uVar5 = 0xffffffff;
      do {
        param_12 = (uint)*(char *)(param_9 + 0x10);
        if ((param_14 != (int)*(char *)((&DAT_804362d8)[param_12 ^ 1] + 0x10c6)) &&
           (*(char *)((int)pfVar4 + 0x15) != '\0')) {
          if (param_15 == *(char *)(param_9 + 0x12)) {
            *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x10) + '\x01';
            uVar5 = param_14;
            break;
          }
          param_15 = param_15 + 1;
        }
        pfVar4 = pfVar4 + 8;
        param_14 = param_14 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      if ((int)uVar5 < 0) {
        return;
      }
    }
    dVar2 = DOUBLE_8043bfa8;
    if (*(uint *)(param_9 + 0x180) != uVar5) {
      *(uint *)(param_9 + 0x180) = uVar5;
      zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - dVar2),param_2,
                  param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4,param_12,
                  &DAT_804362d8,param_14,param_15,uVar5);
    }
  }
  return;
}



