// ==== 80137358  FUN_80137358 ====

/* WARNING: Removing unreachable block (ram,0x80137424) */
/* WARNING: Removing unreachable block (ram,0x80137368) */

void FUN_80137358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  double dVar2;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_80439ff4,(float *)(param_9 + 0x58),(float *)(param_9 + 0x58));
  *(undefined2 *)(param_9 + 0x1e) = 0;
  dVar3 = zz_0045204_(*(short *)(param_9 + 0x1e));
  dVar5 = (double)FLOAT_80439ffc;
  dVar2 = (double)(float)(dVar3 * (double)FLOAT_80439ff8 + (double)FLOAT_80439ff8);
  if ((dVar2 <= dVar5) && (dVar5 = dVar2, dVar2 < (double)FLOAT_8043a000)) {
    dVar5 = (double)FLOAT_8043a000;
  }
  pfVar1 = (float *)0x46;
  zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),0x46,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_00086b8_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 80137444  FUN_80137444 ====

void FUN_80137444(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  double dVar1;
  double dVar2;
  undefined8 uVar3;
  
  *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 0x400;
  dVar2 = zz_0045204_(*(short *)(param_9 + 0x1e));
  dVar1 = (double)FLOAT_80439ffc;
  dVar2 = (double)(float)(dVar2 * (double)FLOAT_80439ff8 + (double)FLOAT_80439ff8);
  if ((dVar2 <= dVar1) && (dVar1 = dVar2, dVar2 < (double)FLOAT_8043a000)) {
    dVar1 = (double)FLOAT_8043a000;
  }
  uVar3 = zz_00086b8_(dVar1,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                      *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                     );
  zz_0007c30_(uVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801374cc  FUN_801374cc ====

void FUN_801374cc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801374e0  FUN_801374e0 ====

void FUN_801374e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80137500  FUN_80137500 ====

void FUN_80137500(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80137540  zz_0137540_ ====

void zz_0137540_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x19;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80137638;
    *(code **)(puVar1 + 0x10c) = FUN_801377d8;
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



// ==== 80137638  FUN_80137638 ====

void FUN_80137638(int param_1)

{
  (*(code *)(&PTR_FUN_80339330)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80137674  FUN_80137674 ====

void FUN_80137674(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  cVar1 = *(char *)(param_9 + 0x11);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = cVar1 * 0x1c;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_8033928a + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80339290 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8033928c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80339294 + iVar3);
  uVar4 = zz_00055fc_();
  *(short *)(param_9 + 0x74) = (short)(uVar4 << 0xb);
  *(code **)(param_9 + 0x100) = FUN_80137818;
  zz_0089100_(param_9,1,1);
  uVar5 = zz_0018f88_((int *)(param_9 + 0x144),(int)(&PTR_DAT_80339298)[cVar1 * 7],
                      (float *)(param_9 + 0x58));
  zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)(int)(char)(&DAT_80339288)[iVar3],
              (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 80137750  FUN_80137750 ====

void FUN_80137750(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 801377b8  FUN_801377b8 ====

void FUN_801377b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801377d8  FUN_801377d8 ====

void FUN_801377d8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80137818  FUN_80137818 ====

void FUN_80137818(int param_1)

{
  int iVar1;
  int iVar2;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar1 = *(char *)(param_1 + 0x11) * 0x1c;
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x8c) + (char)(&DAT_80339289)[iVar1] * 0x30 + 0x8d4
                             ),(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 100),(float *)(param_1 + 0x20));
  iVar2 = param_1 + (char)(&DAT_8033929c)[iVar1] * 4;
  local_28 = *(float *)(iVar2 + 0x114);
  local_24 = *(undefined4 *)(iVar2 + 0x124);
  local_20 = *(undefined4 *)(iVar2 + 0x134);
  if ((&DAT_8033929d)[iVar1] != '\0') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a008,&local_28,&local_28);
  }
  iVar2 = param_1 + (char)(&DAT_8033929e)[iVar1] * 4;
  local_1c = *(float *)(iVar2 + 0x114);
  local_18 = *(undefined4 *)(iVar2 + 0x124);
  local_14 = *(undefined4 *)(iVar2 + 0x134);
  if ((&DAT_8033929f)[iVar1] != '\0') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a008,&local_1c,&local_1c);
  }
  zz_0045ef4_((float *)(param_1 + 0x114),*(int *)(&DAT_803392a0 + iVar1),&local_28,&local_1c);
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),&local_28);
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),&local_28);
  return;
}



// ==== 80137984  zz_0137984_ ====

void zz_0137984_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1a;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = FUN_80137a8c;
    *(code **)(puVar1 + 0x10c) = FUN_80137d0c;
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



// ==== 80137a8c  FUN_80137a8c ====

void FUN_80137a8c(int param_1)

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
  (*(code *)(&PTR_FUN_80339370)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80137b18  FUN_80137b18 ====

void FUN_80137b18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,uint param_13,int param_14,int param_15,
                 undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined8 uVar10;
  
  uVar2 = *(char *)(param_9 + 0x13) * 0x180;
  if (uVar2 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar2);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    pcVar5 = (char *)0x1;
    *(code **)(param_9 + 0x100) = FUN_80137e68;
    uVar10 = zz_0089100_(param_9,1,1);
    pcVar9 = &DAT_80434638;
    iVar8 = param_9;
    for (iVar7 = 0; cVar1 = *(char *)(param_9 + 0x13), iVar7 < cVar1; iVar7 = iVar7 + 1) {
      iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
      param_12 = (uint)cVar1;
      pcVar5 = (char *)(int)*pcVar9;
      uVar10 = zz_0007198_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           *(int *)(iVar8 + 0xe0),pcVar5,param_12,param_13,param_14,param_15,
                           param_16);
      iVar6 = 0;
      iVar4 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x10);
      }
      do {
        uVar10 = gnt4_HSD_JObjSetFlagsAll
                           (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                            0x10,pcVar5,param_12,param_13,param_14,param_15,param_16);
        if (iVar4 == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar4 + 8);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < 4);
      pcVar9 = pcVar9 + 1;
      iVar8 = iVar8 + 4;
    }
    zz_0137f88_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pcVar5,
                param_12,param_13,param_14,param_15);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  }
  return;
}



// ==== 80137c74  FUN_80137c74 ====

void FUN_80137c74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,uint param_13,int param_14,int param_15,
                 undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_01381bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 80137cb0  FUN_80137cb0 ====

void FUN_80137cb0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80137cc4  FUN_80137cc4 ====

void FUN_80137cc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80137d0c  FUN_80137d0c ====

/* WARNING: Removing unreachable block (ram,0x80137dc8) */

void FUN_80137d0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar9 = 0;
  iVar10 = param_9;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    iVar7 = 0;
    iVar2 = *(int *)(*(int *)(iVar10 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar6 = iVar9 * 0x60;
    iVar5 = iVar9;
    do {
      if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar5) != 0) {
        pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
        if (iVar2 == 0) {
          param_11 = &DAT_8043a018;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_8043a010,0x495,&DAT_8043a018,param_12,param_13,param_14,
                                     param_15,param_16);
        }
        if (pfVar4 == (float *)0x0) {
          param_11 = &DAT_8043a020;
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_8043a010,0x496,&DAT_8043a020,param_12,param_13,param_14,param_15,
                           param_16);
        }
        param_1 = gnt4_PSMTXCopy_bl(pfVar4,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 0x60;
      iVar5 = iVar5 + 1;
    } while (iVar7 < 4);
    param_1 = zz_00097b4_(*(int *)(iVar10 + 0xe0),0x44);
    iVar10 = iVar10 + 4;
    iVar9 = iVar9 + 4;
  }
  return;
}



// ==== 80137e68  FUN_80137e68 ====

void FUN_80137e68(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = 0;
  iVar4 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    iVar6 = iVar4 * 0x60;
    iVar2 = 0;
    iVar5 = iVar4;
    do {
      if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar5) != 0) {
        pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
        if (iVar3 == 0) {
          zz_00457d4_('x',(float *)(*(int *)(param_1 + 0x8c) + 0x904),pfVar1,
                      *(short *)(pfVar1 + 0xf));
          zz_00455fc_(pfVar1,pfVar1,pfVar1 + 0xc);
          *(float *)(param_1 + 0x20) = pfVar1[3];
          *(float *)(param_1 + 0x24) = pfVar1[7];
          *(float *)(param_1 + 0x28) = pfVar1[0xb];
        }
        else {
          gnt4_PSMTXTrans_bl((double)pfVar1[0xc],(double)pfVar1[0xd],(double)pfVar1[0xe],pfVar1);
          zz_00457d4_('y',pfVar1,pfVar1,*(short *)((int)pfVar1 + 0x3e));
          zz_00457d4_('x',pfVar1,pfVar1,*(short *)(pfVar1 + 0xf));
          zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0x10);
        }
      }
      iVar2 = iVar2 + 1;
      iVar6 = iVar6 + 0x60;
      iVar5 = iVar5 + 1;
    } while (iVar2 < 4);
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 80137f88  zz_0137f88_ ====

void zz_0137f88_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,uint param_12,uint param_13,int param_14,int param_15)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  int unaff_r30;
  double dVar11;
  
  if (param_10 == 0) {
    unaff_r30 = 0;
    iVar9 = 0;
    if ((*(ushort *)(param_9 + 0x1c) & 1) != 0) {
      unaff_r30 = -1;
    }
  }
  else {
    uVar6 = zz_00055fc_();
    bVar1 = *(byte *)(param_9 + 0x13);
    param_13 = (uint)bVar1;
    param_12 = (int)(char)bVar1 - 1;
    iVar9 = uVar6 - (uVar6 / param_12) * param_12;
    for (param_14 = 0; param_14 < (int)param_12; param_14 = param_14 + 1) {
      iVar9 = iVar9 + 1;
      if ((int)param_12 < iVar9) {
        iVar9 = 1;
      }
      iVar7 = iVar9 << 2;
      unaff_r30 = -1;
      for (param_15 = 0; param_15 < 4; param_15 = param_15 + 1) {
        if (-1 < unaff_r30) break;
        if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar7) == 0) {
          unaff_r30 = param_15;
        }
        iVar7 = iVar7 + 1;
      }
      if (-1 < unaff_r30) {
        param_14 = (int)(char)bVar1;
      }
    }
  }
  if (-1 < unaff_r30) {
    iVar7 = iVar9 * 4;
    pfVar8 = (float *)(unaff_r30 + iVar7);
    *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << (int)pfVar8);
    iVar10 = *(int *)(param_9 + 0x54) + (int)pfVar8 * 0x60;
    if (iVar9 == 0) {
      *(undefined2 *)(iVar10 + 0x58) = 0;
      fVar2 = FLOAT_8043a024;
      dVar11 = (double)FLOAT_8043a024;
      *(undefined2 *)(iVar10 + 0x5a) = 3;
      fVar3 = FLOAT_8043a028;
      *(float *)(iVar10 + 0x38) = fVar2;
      *(float *)(iVar10 + 0x30) = fVar2;
      *(float *)(iVar10 + 0x34) = fVar3;
      if (*(char *)(param_9 + 0x11) == '\x01') {
        *(undefined2 *)(iVar10 + 0x3c) = 0x4000;
      }
      else {
        *(undefined2 *)(iVar10 + 0x3c) = 0;
      }
    }
    else {
      iVar5 = *(int *)(param_9 + 0x8c);
      *(undefined2 *)(iVar10 + 0x58) = 0;
      *(short *)(iVar10 + 0x5a) = (short)DAT_80434630;
      *(undefined4 *)(iVar10 + 0x4c) = *(undefined4 *)(iVar5 + 0xb4);
      uVar4 = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(iVar10 + 0x30) = *(undefined4 *)(param_9 + 0x20);
      *(undefined4 *)(iVar10 + 0x34) = uVar4;
      *(undefined4 *)(iVar10 + 0x38) = *(undefined4 *)(param_9 + 0x28);
      uVar6 = zz_00055fc_();
      *(short *)(iVar10 + 0x3c) = (short)(uVar6 << 8);
      uVar6 = zz_00055fc_();
      *(short *)(iVar10 + 0x3e) = (short)(uVar6 << 8);
      pfVar8 = (float *)(iVar10 + 0x40);
      zz_0018f88_((int *)(iVar10 + 0x50),iRam80434634,pfVar8);
      dVar11 = (double)gnt4_PSQUATScale_bl((double)*(float *)(iVar10 + 0x4c),
                                           (float *)(iVar10 + 0x40),(float *)(iVar10 + 0x40));
    }
    iVar7 = *(int *)(*(int *)(param_9 + iVar7 + 0xe0) + 0xc);
    if (iVar7 == 0) {
      iVar7 = 0;
    }
    else {
      iVar7 = *(int *)(iVar7 + 0x10);
    }
    if (0 < unaff_r30) {
      do {
        if (iVar7 == 0) {
          iVar7 = 0;
        }
        else {
          iVar7 = *(int *)(iVar7 + 8);
        }
        unaff_r30 = unaff_r30 + -1;
      } while (unaff_r30 != 0);
    }
    gnt4_HSD_JObjClearFlagsAll
              (dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,0x10,
               (undefined *)pfVar8,param_12,param_13,param_14,param_15,iVar9);
  }
  return;
}



// ==== 801381bc  zz_01381bc_ ====

int zz_01381bc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,uint param_12,uint param_13,int param_14,int param_15,
               undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar8 = 0;
  iVar9 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(iVar9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar4 = iVar8 * 0x60;
    iVar10 = iVar8;
    do {
      puVar3 = (undefined *)(1 << iVar10);
      if (((int)(short)*(ushort *)(param_9 + 0x1c) & (uint)puVar3) != 0) {
        iVar5 = *(int *)(param_9 + 0x54) + iVar4;
        if (iVar7 == 0) {
          if (*(char *)(*(int *)(param_9 + 0x8c) + 0x6f2) < '\x01') {
            *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) & ~(ushort)puVar3;
            param_1 = gnt4_HSD_JObjSetFlagsAll
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2,0x10,puVar3,param_12,param_13,param_14,param_15,param_16);
          }
          else {
            sVar1 = *(short *)(iVar5 + 0x58) + 1;
            *(short *)(iVar5 + 0x58) = sVar1;
            if (*(short *)(iVar5 + 0x5a) <= sVar1) {
              *(undefined2 *)(iVar5 + 0x58) = 0;
              param_1 = zz_0137f88_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_9,1,puVar3,param_12,param_13,param_14,param_15);
            }
          }
        }
        else {
          sVar1 = *(short *)(iVar5 + 0x58) + 1;
          *(short *)(iVar5 + 0x58) = sVar1;
          if (sVar1 < *(short *)(iVar5 + 0x5a)) {
            zz_0018fd8_((int *)(iVar5 + 0x50),(int)*(short *)(iVar5 + 0x58),(float *)(iVar5 + 0x40))
            ;
            param_1 = gnt4_PSQUATScale_bl((double)*(float *)(iVar5 + 0x4c),(float *)(iVar5 + 0x40),
                                          (float *)(iVar5 + 0x40));
          }
          else {
            *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) & ~(ushort)puVar3;
            param_1 = gnt4_HSD_JObjSetFlagsAll
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2,0x10,puVar3,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
      iVar6 = iVar6 + 1;
      iVar4 = iVar4 + 0x60;
      iVar10 = iVar10 + 1;
    } while (iVar6 < 4);
    iVar9 = iVar9 + 4;
    iVar8 = iVar8 + 4;
  }
  return (int)*(short *)(param_9 + 0x1c);
}



// ==== 8013833c  zz_013833c_ ====

void zz_013833c_(int param_1,undefined1 param_2,undefined4 param_3)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x609) || (sVar1 == 0x61d)) || (sVar1 == 0x60d)) ||
      ((sVar1 == 0x60b || (sVar1 == 0xe01)))) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80138474;
    *(code **)(puVar2 + 0x10c) = FUN_801386c4;
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
  }
  return;
}



// ==== 80138474  FUN_80138474 ====

void FUN_80138474(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80339560)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801384c8  FUN_801384c8 ====

void FUN_801384c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar5 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar5;
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043a030;
  *(undefined1 *)(param_9 + 0x84) = 0x4f;
  *(undefined *)(param_9 + 0x13) = (&DAT_80339396)[iVar3];
  *(undefined *)(param_9 + 0x12) = (&DAT_80339397)[iVar3];
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80339382 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80339388 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80339384 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033938c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80339390 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80339394 + iVar3);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80339380 + iVar3),iVar6 + 0xc28,iVar5,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80339380 + iVar3);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,iVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a034,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0138604_(param_9);
  return;
}



// ==== 80138604  zz_0138604_ ====

void zz_0138604_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  bVar1 = **(byte **)(param_1 + 0x144);
  if ((bVar1 & 0x80) != 0) {
    **(byte **)(param_1 + 0x144) = bVar1 & 0x7f;
    if (((**(byte **)(param_1 + 0x144) & 1) != 0) && (-1 < *(char *)(param_1 + 0x12))) {
      *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar3 + 0xcc);
      *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar3 + 200);
      *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar3 + 0xd0);
      uVar2 = *(undefined4 *)(iVar3 + 0xb4);
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined4 *)(param_1 + 0x58) = uVar2;
      *(undefined4 *)(param_1 + 0xb8) = uVar2;
      *(undefined4 *)(param_1 + 0xb4) = uVar2;
      zz_00c3be0_(param_1,*(undefined1 *)(param_1 + 0x12));
    }
  }
  return;
}



// ==== 801386a4  FUN_801386a4 ====

void FUN_801386a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801386c4  FUN_801386c4 ====

void FUN_801386c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((**(byte **)(param_9 + 0x144) & 1) != 0) {
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
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 8013874c  zz_013874c_ ====

void zz_013874c_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x805) || (sVar1 == 0x80d)) || (sVar1 == 0x80e)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80138864;
    *(code **)(puVar2 + 0x10c) = FUN_80138ca0;
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



// ==== 80138864  FUN_80138864 ====

void FUN_80138864(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803395ac)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801388b8  FUN_801388b8 ====

void FUN_801388b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXMultVec_bl((float *)(iVar5 + 0xc94),(float *)&DAT_8033957c,(float *)(param_9 + 0x144));
  *(code **)(param_9 + 0x100) = FUN_80138a3c;
  *(undefined1 *)(param_9 + 0x84) = 0;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x89) = 0x14;
  uVar1 = DAT_80339574;
  puVar4 = &DAT_80339570;
  *(undefined4 *)(param_9 + 100) = DAT_80339570;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = DAT_80339578;
  uVar1 = DAT_8033958c;
  *(undefined4 *)(param_9 + 0x38) = DAT_80339588;
  *(undefined4 *)(param_9 + 0x3c) = uVar1;
  *(undefined4 *)(param_9 + 0x40) = DAT_80339590;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_803395a0 + *(char *)(param_9 + 0x11) * 4),iVar5 + 0xc28,puVar4,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  iVar2 = *(int *)(&DAT_803395a0 + *(char *)(param_9 + 0x11) * 4);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,puVar4,in_r8,
                      in_r9,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,puVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a038,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0138a08_();
  return;
}



// ==== 80138a08  zz_0138a08_ ====

void zz_0138a08_(void)

{
  return;
}



// ==== 80138a1c  FUN_80138a1c ====

void FUN_80138a1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80138a3c  FUN_80138a3c ====

/* WARNING: Removing unreachable block (ram,0x80138c7c) */
/* WARNING: Removing unreachable block (ram,0x80138a4c) */

void FUN_80138a3c(int param_1)

{
  float *pfVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float afStack_68 [3];
  float local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  
  iVar2 = *(int *)(param_1 + 0x90);
  pfVar1 = (float *)(param_1 + 0x144);
  dVar4 = (double)*(float *)(iVar2 + 0xb4);
  gnt4_PSMTXMultVecSR_bl((float *)(iVar2 + 0x8d4),(float *)&DAT_80339588,&local_38);
  gnt4_PSVECAdd_bl(pfVar1,&local_38,pfVar1);
  gnt4_PSMTXMultVec_bl((float *)(iVar2 + 0xc94),(float *)&DAT_80339594,afStack_68);
  gnt4_PSVECSubtract_bl(pfVar1,afStack_68,&local_38);
  dVar3 = gnt4_PSVECMag_bl(&local_38);
  if ((double)(float)((double)FLOAT_8043a03c * dVar4) < dVar3) {
    gnt4_PSQUATScale_bl((double)(float)((double)(float)((double)FLOAT_8043a03c / dVar3) * dVar4),
                        &local_38,&local_38);
    gnt4_PSVECAdd_bl(afStack_68,&local_38,pfVar1);
  }
  gnt4_PSMTXMultVec_bl((float *)(iVar2 + 0xc94),(float *)&DAT_80339570,&local_38);
  gnt4_PSVECSubtract_bl(pfVar1,&local_38,&local_50);
  zz_006ebb4_(&local_50,&local_50);
  gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_8043a040 * dVar4),&local_50,&local_50);
  local_44 = *(float *)(iVar2 + 0xc94);
  local_40 = *(undefined4 *)(iVar2 + 0xca4);
  local_3c = *(undefined4 *)(iVar2 + 0xcb4);
  zz_006ec1c_(&local_44,&local_44);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_44,&local_50);
  gnt4_PSQUATScale_bl(dVar3,&local_44,&local_44);
  gnt4_PSVECSubtract_bl(&local_50,&local_44,&local_50);
  gnt4_PSVECAdd_bl(&local_38,&local_50,pfVar1);
  local_44 = *(float *)(iVar2 + 0xc94);
  local_40 = *(undefined4 *)(iVar2 + 0xca4);
  local_3c = *(undefined4 *)(iVar2 + 0xcb4);
  gnt4_PSVECCrossProduct_bl(&local_44,&local_50,&local_5c);
  gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_44);
  zz_006eb4c_(&local_44,&local_44);
  zz_006ebb4_(&local_50,&local_50);
  zz_006ec1c_(&local_5c,&local_5c);
  gnt4_PSQUATScale_bl(dVar4,&local_44,&local_44);
  gnt4_PSQUATScale_bl(dVar4,&local_50,&local_50);
  gnt4_PSQUATScale_bl(dVar4,&local_5c,&local_5c);
  *(float *)(param_1 + 0x114) = local_44;
  *(undefined4 *)(param_1 + 0x124) = local_40;
  *(undefined4 *)(param_1 + 0x134) = local_3c;
  *(float *)(param_1 + 0x118) = local_50;
  *(undefined4 *)(param_1 + 0x128) = local_4c;
  *(undefined4 *)(param_1 + 0x138) = local_48;
  *(float *)(param_1 + 0x11c) = local_5c;
  *(undefined4 *)(param_1 + 300) = local_58;
  *(undefined4 *)(param_1 + 0x13c) = local_54;
  *(float *)(param_1 + 0x120) = local_38;
  *(undefined4 *)(param_1 + 0x130) = local_34;
  *(undefined4 *)(param_1 + 0x140) = local_30;
  return;
}



// ==== 80138ca0  FUN_80138ca0 ====

void FUN_80138ca0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80138d18  zz_0138d18_ ====

void zz_0138d18_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x102) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80138e1c;
    *(code **)(puVar1 + 0x10c) = FUN_80139014;
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



// ==== 80138e1c  FUN_80138e1c ====

void FUN_80138e1c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803395cc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80138e70  FUN_80138e70 ====

void FUN_80138e70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043a048;
  *(undefined1 *)(param_9 + 0x84) = 0x4f;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = (int)(char)(&DAT_80434640)[*(char *)(param_9 + 0x11)];
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),iVar3,iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar2 = iVar4 + 0xc28;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar2,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar2,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a04c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0138f68_(param_9);
  return;
}



// ==== 80138f68  zz_0138f68_ ====

void zz_0138f68_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  *(byte *)(param_1 + 0x12) = *(byte *)(*(int *)(param_1 + 0x90) + 0x6e8) & 0x7f;
  *(undefined *)(param_1 + 0x89) = (&DAT_80434644)[*(char *)(param_1 + 0x11)];
  iVar2 = *(char *)(param_1 + 0x11) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_803395c4 + iVar2);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803395c0 + iVar2);
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803395c8 + iVar2);
  iVar2 = *(char *)(param_1 + 0x11) * 6;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_80434648 + iVar2);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar2 + -0x7fbcb9b4);
  return;
}



// ==== 80138ff4  FUN_80138ff4 ====

void FUN_80138ff4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80139014  FUN_80139014 ====

void FUN_80139014(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(param_9 + 0x12) == '\x01') {
    if (0 < *(short *)(iVar1 + 0x784)) {
      if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
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
    }
  }
  return;
}



// ==== 801390a4  zz_01390a4_ ====

void zz_01390a4_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x304) || (*(short *)(param_1 + 1000) == 0x308)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x13] = param_3;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801391c4;
    *(code **)(puVar1 + 0x10c) = FUN_80139514;
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



// ==== 801391c4  FUN_801391c4 ====

void FUN_801391c4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80339628)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80139218  FUN_80139218 ====

void FUN_80139218(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  float fVar2;
  undefined4 extraout_r4;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar2 = FLOAT_8043a050;
  *(undefined *)(param_9 + 0x84) = (&DAT_8043465c)[*(char *)(param_9 + 0x11)];
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0xb8) = fVar2;
  *(float *)(param_9 + 0xb4) = fVar2;
  cVar1 = (&DAT_80434650)[*(char *)(param_9 + 0x13) * 4 + (int)*(char *)(param_9 + 0x11)];
  *(float *)(param_9 + 0x144) = fVar2;
  iVar4 = (int)cVar1;
  if (*(char *)(param_9 + 0x11) == '\x01') {
    *(float *)(param_9 + 0x144) = FLOAT_8043a054;
  }
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),iVar4,iVar5 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a058,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0139344_(param_9);
  return;
}



// ==== 80139344  zz_0139344_ ====

void zz_0139344_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar2 = *(int *)(param_1 + 0x90);
  *(undefined *)(param_1 + 0x89) = (&DAT_80434658)[*(char *)(param_1 + 0x11)];
  iVar3 = *(char *)(param_1 + 0x11) * 0xc;
  uVar4 = *(undefined4 *)(&DAT_803395e4 + iVar3);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803395e0 + iVar3);
  *(undefined4 *)(param_1 + 0x68) = uVar4;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803395e8 + iVar3);
  iVar3 = *(char *)(param_1 + 0x11) * 6;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_80339610 + iVar3);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_80339614 + iVar3);
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 == '\x01') {
    if (*(char *)(iVar2 + 0x144) == '\x03') {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043a05c;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043a05c;
    }
    if ((*(char *)(iVar2 + 0x144) == '\x01') && (*(char *)(iVar2 + 0x145) == '\x03')) {
      *(float *)(param_1 + 0x144) = FLOAT_8043a054;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if (*(char *)(iVar2 + 0x144) == '\x02') {
        *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043a05c;
      }
      else {
        *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043a05c;
      }
      if ((*(char *)(iVar2 + 0x144) == '\x01') && (*(char *)(iVar2 + 0x145) == '\x03')) {
        *(float *)(param_1 + 0x144) = FLOAT_8043a054;
      }
    }
  }
  else if (((cVar1 < '\x04') && (*(char *)(iVar2 + 0x144) == '\x05')) &&
          (*(char *)(iVar2 + 0x145) != '\0')) {
    *(undefined2 *)(param_1 + 0x70) = 0;
  }
  if (FLOAT_8043a050 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = FLOAT_8043a050;
  }
  if (*(float *)(param_1 + 0x144) < FLOAT_8043a054) {
    *(float *)(param_1 + 0x144) = FLOAT_8043a054;
  }
  uVar4 = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x60) = uVar4;
  *(undefined4 *)(param_1 + 0x5c) = uVar4;
  *(undefined4 *)(param_1 + 0x58) = uVar4;
  return;
}



// ==== 801394f4  FUN_801394f4 ====

void FUN_801394f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80139514  FUN_80139514 ====

void FUN_80139514(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if ((('\x01' < *(char *)(param_9 + 0x11)) || (*(char *)(param_9 + 0x11) < '\0')) ||
     (param_1 = (double)*(float *)(param_9 + 0x144), (double)FLOAT_8043a054 < param_1)) {
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
  }
  return;
}



// ==== 801395c0  FUN_801395c0 ====

void FUN_801395c0(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801396b0;
    *(code **)(puVar1 + 0x10c) = FUN_801399f4;
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



// ==== 801396b0  FUN_801396b0 ====

void FUN_801396b0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8033964c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80139704  FUN_80139704 ====

void FUN_80139704(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  iVar4 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar4;
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar2 = *(char *)(param_9 + 0x11) * 4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043a060;
  *(undefined *)(param_9 + 0x89) = (&DAT_80339638)[iVar2];
  *(undefined *)(param_9 + 0x84) = (&DAT_8033963a)[iVar2];
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined2 *)(param_9 + 0x144) = 0;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_80339639)[iVar2],iVar5 + 0xc28,iVar4,in_r8,in_r9,in_r10);
  iVar3 = iVar5 + 0xc28;
  iVar2 = (int)(char)(&DAT_80339639)[iVar2];
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,iVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,iVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a064,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0139824_(param_9);
  return;
}



// ==== 80139824  zz_0139824_ ====

void zz_0139824_(int param_1)

{
  int iVar1;
  float fVar2;
  double dVar3;
  short sVar4;
  int iVar5;
  
  dVar3 = DOUBLE_8043a078;
  fVar2 = FLOAT_8043a06c;
  iVar5 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x11) * 4;
  if ((*(uint *)(iVar5 + 0x5e0) & 0x20000000) == 0) {
    if (*(char *)(iVar5 + 0x6e9) < '\x01') {
      *(short *)(param_1 + 0x144) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x144) ^ 0x80000000) -
                               DOUBLE_8043a078) * FLOAT_8043a070);
    }
    else {
      *(short *)(param_1 + 0x144) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x144) ^ 0x80000000) -
                               DOUBLE_8043a078) + FLOAT_8043a068);
      if (fVar2 < (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x144) ^ 0x80000000)
                         - dVar3)) {
        *(undefined2 *)(param_1 + 0x144) = 0x2000;
      }
      zz_00f0104_(iVar5,6,2);
    }
    if ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x144) ^ 0x80000000) -
               DOUBLE_8043a078) < FLOAT_8043a074) {
      *(undefined2 *)(param_1 + 0x144) = 0x16c;
    }
    sVar4 = *(short *)(param_1 + 0x144);
    if (((int)(char)(&DAT_8033963b)[iVar1] & 0x80U) != 0) {
      sVar4 = -sVar4;
    }
    if (((int)(char)(&DAT_8033963b)[iVar1] & 1U) != 0) {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + sVar4;
    }
    if (((&DAT_8033963b)[iVar1] & 2) != 0) {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar4;
    }
    if (((&DAT_8033963b)[iVar1] & 4) != 0) {
      *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + sVar4;
    }
  }
  return;
}



// ==== 801399d4  FUN_801399d4 ====

void FUN_801399d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801399f4  FUN_801399f4 ====

void FUN_801399f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80139a6c  zz_0139a6c_ ====

void zz_0139a6c_(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088c40_(3,param_1,1,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0xb;
    puVar1[0x11] = param_4;
    *(code **)(puVar1 + 0xc) = FUN_80139b80;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    *(undefined4 *)(puVar1 + 0x144) = param_2;
    *(undefined4 *)(puVar1 + 0x148) = param_3;
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



// ==== 80139b80  FUN_80139b80 ====

void FUN_80139b80(int param_1)

{
  (*(code *)(&PTR_FUN_80339660)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80139bbc  FUN_80139bbc ====

void FUN_80139bbc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = -((int)*(char *)(param_1 + 0x11) >> 0x1f);
  if (iVar1 == 0) {
    iVar1 = zz_008ac80_(param_1,(int)*(char *)(param_1 + 0x11));
  }
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    puVar3 = *(undefined4 **)(param_1 + 0x144);
    uVar2 = puVar3[1];
    *(undefined4 *)(param_1 + 0x20) = *puVar3;
    *(undefined4 *)(param_1 + 0x24) = uVar2;
    *(undefined4 *)(param_1 + 0x28) = puVar3[2];
    *(code **)(param_1 + 0x100) = FUN_80139cc0;
    zz_0089100_(param_1,1,1);
  }
  return;
}



// ==== 80139c78  FUN_80139c78 ====

void FUN_80139c78(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}



// ==== 80139ca0  FUN_80139ca0 ====

void FUN_80139ca0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80139cc0  FUN_80139cc0 ====

void FUN_80139cc0(int param_1)

{
  double dVar1;
  
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  dVar1 = (double)*(float *)(param_1 + 0xc0);
  zz_0045654_(dVar1,dVar1,dVar1,(float *)(param_1 + 0x114),(float *)(param_1 + 0x114));
  return;
}



// ==== 80139d14  FUN_80139d14 ====

void FUN_80139d14(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0xa02) || (*(short *)(param_1 + 1000) == 0xa07)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80139e24;
    *(code **)(puVar1 + 0x10c) = FUN_80139fd8;
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



// ==== 80139e24  FUN_80139e24 ====

void FUN_80139e24(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803396a0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80139e78  FUN_80139e78 ====

void FUN_80139e78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_8043a080;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80339672 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80339678 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80339674 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033967c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80339680 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80339684 + iVar3);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80339670 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80339670 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a084,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0139fa4_();
  return;
}



// ==== 80139fa4  zz_0139fa4_ ====

void zz_0139fa4_(void)

{
  return;
}



// ==== 80139fb8  FUN_80139fb8 ====

void FUN_80139fb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80139fd8  FUN_80139fd8 ====

void FUN_80139fd8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8013a050  zz_013a050_ ====

bool zz_013a050_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    zz_006de10_(param_1,0);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x31;
    *(code **)(puVar1 + 0xc) = FUN_8013a16c;
    *(undefined **)(puVar1 + 0x10c) = &DAT_8013a950;
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



// ==== 8013a16c  FUN_8013a16c ====

void FUN_8013a16c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_80339708)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8013a1fc  FUN_8013a1fc ====

void FUN_8013a1fc(int param_1)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  char *pcVar4;
  int iVar5;
  
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  iVar5 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x11) * 0x2c;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  pcVar4 = &DAT_803396b0 + iVar2;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x10;
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8d8);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8e8);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + *pcVar4 * 0x30 + 0x8d4),(float *)(iVar2 + -0x7fcc694c),
             (float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8d8);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8e8);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(iVar5 + *pcVar4 * 0x30 + 0x8f8);
  if ((*(int *)(iVar5 + 200) != 0) &&
     (iVar1 = FUN_8006c334((double)FLOAT_8043a088,param_1,(float *)(iVar5 + 0x518)), iVar1 != 0)) {
    zz_0083d60_(param_1,iVar5,0);
  }
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_803396c8 + iVar2),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_803396c8 + iVar2);
  *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_803396ce + iVar2);
  iVar1 = zz_008ac80_(param_1,(int)(char)(&DAT_803396b1)[iVar2]);
  if (iVar1 == 0) {
    zz_006de10_(iVar5,0);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    pfVar3 = (float *)(param_1 + 0x150);
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),pfVar3);
    zz_00a2bf8_(iVar5,param_1,(undefined4 *)(param_1 + 0x144),pfVar3,
                (int)*(short *)(&DAT_803396d8 + iVar2),1);
    zz_0117ed4_(param_1,param_1 + 0x144,(int)*(short *)(&DAT_803396da + iVar2));
    zz_0117ed4_(param_1,pfVar3,(int)*(short *)(&DAT_803396da + iVar2));
    zz_00f036c_(*(int *)(param_1 + 0x90),0xd2);
  }
  return;
}



// ==== 8013a440  FUN_8013a440 ====

void FUN_8013a440(int param_1)

{
  char cVar1;
  
  zz_00f0104_(*(int *)(param_1 + 0x90),7,2);
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_013a76c_(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_013a4c4_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_013a818_(param_1);
  }
  return;
}



// ==== 8013a4c4  zz_013a4c4_ ====

void zz_013a4c4_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x11) * 0x2c;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar3 + (char)(&DAT_803396b0)[iVar1] * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fcc694c),(float *)(param_1 + 0x144));
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_803396d0 + iVar1)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_803396d4 + iVar1);
      }
      else {
        *(float *)(param_1 + 0x44) = *(float *)(&DAT_803396d0 + iVar1);
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_803396c4 + iVar1),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_803396c0 + iVar1),param_1,
                   (char)*(undefined2 *)(&DAT_803396ce + iVar1));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0083714_(param_1);
      if (iVar2 == 0) {
        iVar2 = zz_0084170_(param_1);
        if (iVar2 == 0) {
          gnt4_PSMTXMultVec_bl
                    ((float *)(iVar3 + (char)(&DAT_803396b0)[iVar1] * 0x30 + 0x8d4),
                     (float *)(iVar1 + -0x7fcc694c),(float *)(param_1 + 0x144));
          *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x20);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
          dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144))
          ;
          if ((double)FLOAT_8043a08c < dVar4) {
            dVar5 = 1.0 / SQRT(dVar4);
            dVar5 = DOUBLE_8043a090 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a098);
            dVar5 = DOUBLE_8043a090 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a098);
            dVar4 = (double)(float)(dVar4 * DOUBLE_8043a090 * dVar5 *
                                            -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a098));
          }
          if ((double)FLOAT_8043a0a0 <= dVar4) {
            zz_013a720_(param_1);
          }
        }
        else {
          zz_013a720_(param_1);
        }
      }
      else {
        zz_006de10_(iVar3,0);
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      zz_013a720_(param_1);
    }
  }
  else {
    zz_013a720_(param_1);
  }
  return;
}



// ==== 8013a720  zz_013a720_ ====

void zz_013a720_(int param_1)

{
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 10;
  *(undefined4 *)(param_1 + 0x160) = 300;
  zz_008aff0_(param_1);
  *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + 0x290);
  return;
}



// ==== 8013a76c  zz_013a76c_ ====

void zz_013a76c_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  iVar1 = zz_008ac80_(param_1,(int)(char)(&DAT_803396b2)[*(char *)(param_1 + 0x11) * 0x2c]);
  if (iVar1 == 0) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    if (*(short *)(param_1 + 0x1c) < 1) {
      zz_006de10_(iVar2,0);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x164) = 0;
  }
  return;
}



// ==== 8013a818  zz_013a818_ ====

void zz_013a818_(int param_1)

{
  char cVar1;
  
  if (*(int *)(param_1 + 0x160) < 1) {
    zz_006de10_(*(int *)(param_1 + 0x90),0);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    *(int *)(param_1 + 0x160) = *(int *)(param_1 + 0x160) + -1;
    if (*(char *)(param_1 + 0x1d9) != '\0') {
      *(char *)(param_1 + 0x164) = *(char *)(param_1 + 0x164) + '\x01';
    }
    if (*(char *)(param_1 + 0x164) < '\x10') {
      cVar1 = *(char *)(param_1 + 0x1a);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x150);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x154);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x158);
      }
      else if ((cVar1 < '\x01') && (-1 < cVar1)) {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
      }
    }
    else {
      zz_006de10_(*(int *)(param_1 + 0x90),0);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 8013a91c  FUN_8013a91c ====

void FUN_8013a91c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8013a930  FUN_8013a930 ====

void FUN_8013a930(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013a954  zz_013a954_ ====

undefined4 zz_013a954_(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if (*(short *)(param_1 + 1000) == 0x103) {
    puVar2 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar2 == (undefined1 *)0x0) {
      if (*(char *)(param_1 + 0x159) == '\x01') {
        *(undefined1 *)(param_1 + 0x159) = 4;
      }
      uVar1 = 0;
    }
    else {
      *puVar2 = 1;
      puVar2[0x13] = param_2;
      puVar2[0x11] = 0;
      puVar2[0x10] = 0x16;
      *(code **)(puVar2 + 0xc) = FUN_8013aad0;
      *(code **)(puVar2 + 0x10c) = FUN_8013b110;
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
      zz_00f036c_(param_1,6);
      if (*(char *)(param_1 + 0x159) == '\x01') {
        puVar2[0x144] = 1;
        *(undefined1 *)(param_1 + 0x159) = 2;
        *(undefined1 **)(param_1 + 0x148) = puVar2;
        *(undefined2 *)(param_1 + 0x784) = 0;
      }
      else {
        puVar2[0x144] = 0;
      }
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8013aad0  FUN_8013aad0 ====

void FUN_8013aad0(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80339778)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8013ab68  FUN_8013ab68 ====

void FUN_8013ab68(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  puVar8 = &DAT_80339748;
  puVar6 = &DAT_80339718;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar7 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x18;
  *(undefined1 *)(param_9 + 0x98) = 0;
  iVar3 = iVar7 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar2 = iVar3;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fcc68e4),(float *)(param_9 + 0x20));
  if (*(char *)(param_9 + 0x13) == '\0') {
    dVar10 = (double)FLOAT_8043a0a8;
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8d4);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8e4);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8f4);
    gnt4_PSQUATScale_bl(dVar10,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  else {
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8dc);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8ec);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8fc);
  }
  if ((*(int *)(iVar9 + 200) == 0) ||
     (iVar1 = FUN_8006c334((double)*(float *)(&DAT_8033975c + iVar4),param_9,
                           (float *)(iVar9 + 0x518)), iVar1 == 0)) {
    *(undefined4 *)(param_9 + 200) = 0;
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
    local_24 = FLOAT_8043a0ac;
    dVar10 = gnt4_PSVECMag_bl(&local_28);
    if ((double)FLOAT_8043a0ac < dVar10) {
      *(float *)(param_9 + 0x38) = local_28;
      *(float *)(param_9 + 0x3c) = local_24;
      *(undefined4 *)(param_9 + 0x40) = local_20;
    }
  }
  else {
    zz_0083d60_(param_9,iVar9,(int)*(short *)(&DAT_8033971a + iVar3));
  }
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar11 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80339758 + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8033971a + iVar3) * 0x30 + 0x8f8);
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80339758 + iVar4);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8033974a + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033974c + iVar4);
  iVar9 = zz_0006f98_(iVar9);
  zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar9 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_80339718 + iVar3),iVar2,iVar5,puVar6,
              iVar7,puVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80339748 + iVar4));
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 8013ae00  FUN_8013ae00 ====

void FUN_8013ae00(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_013b010_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_013ae48_(param_1);
  }
  return;
}



// ==== 8013ae48  zz_013ae48_ ====

void zz_013ae48_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x18;
  if (*(short *)(param_1 + 0x1c) < 1) {
    zz_013b08c_(param_1);
  }
  else if (*(byte *)(param_1 + 0x1d9) == 0) {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0xe00;
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      FUN_80083874((double)*(float *)(&DAT_80339754 + iVar1),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_80339750 + iVar1),param_1,
                   (char)*(undefined2 *)(&DAT_8033974c + iVar1));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar1 = zz_0083714_(param_1);
      if (iVar1 == 0) {
        iVar1 = zz_0084170_(param_1);
        if (iVar1 != 0) {
          zz_013b08c_(param_1);
        }
      }
      else {
        zz_013b08c_(param_1);
      }
    }
    else {
      zz_013b08c_(param_1);
    }
  }
  else if (*(char *)(param_1 + 0x144) == '\0') {
    zz_013b08c_(param_1);
  }
  else if ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0) {
    zz_013b08c_(param_1);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x290);
    if (*(char *)(iVar1 + 0x83) == '\0') {
      if (*(float *)(iVar1 + 0x204) < FLOAT_8043a0b0) {
        *(int *)(iVar2 + 0x144) = iVar1;
        *(undefined1 *)(iVar2 + 0x159) = 3;
        iVar1 = *(int *)(iVar2 + 0x144);
        *(undefined1 *)(param_1 + 0x19) = 1;
        zz_008aff0_(param_1);
        *(undefined1 *)(iVar2 + 0x158) = *(undefined1 *)(iVar1 + 0x71a);
        zz_0066408_(iVar1,(int)*(char *)(iVar2 + 0x158),(float *)(param_1 + 0x20),
                    (float *)(iVar2 + 0x14c));
        *(undefined1 *)(iVar1 + 0x719) = 1;
      }
      else {
        zz_013b08c_(param_1);
      }
    }
    else {
      zz_013b08c_(param_1);
    }
  }
  return;
}



// ==== 8013b010  zz_013b010_ ====

void zz_013b010_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar1 + 0x159) != '\x03') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(iVar1 + 0x144) + *(char *)(iVar1 + 0x158) * 0x30 + 0x8d4),
             (float *)(iVar1 + 0x14c),(float *)(param_1 + 0x20));
  zz_00f0104_(param_1,4,3);
  return;
}



// ==== 8013b08c  zz_013b08c_ ====

void zz_013b08c_(int param_1)

{
  if (*(char *)(param_1 + 0x144) != '\0') {
    *(undefined1 *)(*(int *)(param_1 + 0x90) + 0x159) = 4;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8013b0e4  FUN_8013b0e4 ====

void FUN_8013b0e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8013b0f0  FUN_8013b0f0 ====

void FUN_8013b0f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013b110  FUN_8013b110 ====

/* WARNING: Removing unreachable block (ram,0x8013b12c) */

void FUN_8013b110(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  float afStack_38 [12];
  
  iVar3 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043a0b4 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x70) *
                                             0x3ff0000000000000)),afStack_38,0x78);
  pfVar2 = afStack_38;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar3 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 8013b194  zz_013b194_ ====

undefined4 zz_013b194_(int param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if (*(short *)(param_1 + 1000) == 0x103) {
    puVar2 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar2 == (undefined1 *)0x0) {
      uVar1 = 0;
      *(undefined1 *)(param_1 + 0x159) = 0;
      *(undefined1 *)(param_1 + 0x15a) = 0;
      *(undefined2 *)(param_1 + 0x784) = *(undefined2 *)(param_1 + 0x79e);
      *(undefined2 *)(param_1 + 0x786) = *(undefined2 *)(param_1 + 0x79e);
    }
    else {
      *puVar2 = 1;
      puVar2[0x13] = 0;
      puVar2[0x11] = 0;
      puVar2[0x10] = 0x17;
      *(code **)(puVar2 + 0xc) = FUN_8013b2c4;
      *(code **)(puVar2 + 0x10c) = FUN_8013bd24;
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
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8013b2c4  FUN_8013b2c4 ====

void FUN_8013b2c4(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  iVar1 = zz_00840b8_(param_1);
  if (iVar1 != 0) {
    *(undefined1 *)(iVar2 + 0x159) = 0;
    *(undefined1 *)(iVar2 + 0x15a) = 0;
  }
  (*(code *)(&PTR_FUN_803397a0)[*(char *)(param_1 + 0x18)])(param_1);
  *(undefined1 *)(param_1 + 0x22d) = *(undefined1 *)(iVar2 + 0x15a);
  return;
}



// ==== 8013b33c  FUN_8013b33c ====

void FUN_8013b33c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  uVar2 = 0x80340000;
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  uVar6 = gnt4_PSMTXMultVec_bl
                    ((float *)(iVar5 + *(short *)(&DAT_8033978a + iVar3) * 0x30 + 0x8d4),
                     (float *)(iVar3 + -0x7fcc6874),(float *)(param_9 + 0x20));
  zz_008458c_((float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar5 + 0x70);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar5 + 0x74);
  *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + -0x8000;
  iVar1 = zz_0006f98_(iVar5);
  zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_80339788 + iVar3),uVar2,iVar4,in_r8,
              in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(undefined1 *)(param_9 + 0x86) = 0;
  *(undefined1 *)(param_9 + 0x224) = 0;
  *(undefined1 *)(param_9 + 0x225) = 0;
  *(undefined1 *)(param_9 + 0x226) = 0;
  *(undefined1 *)(param_9 + 0x227) = 0;
  *(undefined1 *)(param_9 + 0x228) = 0;
  *(undefined1 *)(param_9 + 0x229) = 0;
  *(undefined1 *)(param_9 + 0x22a) = 0;
  *(undefined1 *)(param_9 + 0x22b) = 0;
  *(undefined4 *)(param_9 + 0x1c4) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x1c8) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x1cc) = *(undefined4 *)(param_9 + 0x28);
  *(undefined4 *)(param_9 + 0x1d0) = *(undefined4 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x1d4) = *(undefined4 *)(param_9 + 0x1c8);
  *(undefined4 *)(param_9 + 0x1d8) = *(undefined4 *)(param_9 + 0x1cc);
  *(undefined1 *)(param_9 + 0x224) = 1;
  *(undefined1 *)(param_9 + 0x225) = 1;
  *(undefined1 *)(param_9 + 0x22c) = 1;
  zz_00a2bf8_(iVar5,param_9,(undefined4 *)(param_9 + 0x1c4),(undefined4 *)(param_9 + 0x1d0),3,0);
  *(undefined4 *)(param_9 + 0x230) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x234) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x238) = *(undefined4 *)(param_9 + 0x28);
  zz_0117ed4_(param_9,param_9 + 0x230,0);
  return;
}



// ==== 8013b4cc  FUN_8013b4cc ====

void FUN_8013b4cc(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar4 = *(int *)(param_1 + 0x90);
  if (cVar1 == '\x01') {
    zz_013b768_(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_013b590_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_013b828_(param_1);
  }
  iVar3 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
  uVar2 = *(undefined4 *)(iVar3 + 0x1c8);
  *(undefined4 *)(param_1 + 0x230) = *(undefined4 *)(iVar3 + 0x1c4);
  *(undefined4 *)(param_1 + 0x234) = uVar2;
  *(undefined4 *)(param_1 + 0x238) = *(undefined4 *)(iVar3 + 0x1cc);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar4 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  return;
}



// ==== 8013b590  zz_013b590_ ====

void zz_013b590_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_1 + 0x90);
  iVar3 = *(char *)(param_1 + 0x13) * 0x18;
  if (*(char *)(iVar6 + 0x159) == '\x04') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(iVar6 + 0x159) = 0;
    *(undefined1 *)(iVar6 + 0x15a) = 0;
    *(undefined2 *)(iVar6 + 0x784) = *(undefined2 *)(iVar6 + 0x79e);
    *(undefined2 *)(iVar6 + 0x786) = *(undefined2 *)(iVar6 + 0x79e);
  }
  else {
    if (*(char *)(iVar6 + 0x159) == '\x02') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      iVar5 = *(int *)(iVar6 + 0x148);
      if (iVar5 == 0) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        *(undefined1 *)(iVar6 + 0x159) = 0;
        *(undefined1 *)(iVar6 + 0x15a) = 0;
        *(undefined2 *)(iVar6 + 0x784) = *(undefined2 *)(iVar6 + 0x79e);
        *(undefined2 *)(iVar6 + 0x786) = *(undefined2 *)(iVar6 + 0x79e);
        return;
      }
      uVar2 = *(undefined4 *)(iVar5 + 0x24);
      iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
      *(undefined4 *)(iVar4 + 0x1c4) = *(undefined4 *)(iVar5 + 0x20);
      *(undefined4 *)(iVar4 + 0x1c8) = uVar2;
      *(undefined4 *)(iVar4 + 0x1cc) = *(undefined4 *)(iVar5 + 0x28);
    }
    else {
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar6 + *(short *)(&DAT_8033978a + iVar3) * 0x30 + 0x8d4),
                 (float *)(iVar3 + -0x7fcc6874),
                 (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    }
    if (*(char *)(param_1 + 0x22d) != *(char *)(iVar6 + 0x15a)) {
      cVar1 = *(char *)(param_1 + 0x22c);
      zz_00a2bf8_(iVar6,param_1,(undefined4 *)(param_1 + cVar1 * 0xc + 0x1c4),
                  (undefined4 *)(param_1 + (cVar1 + 1) * 0xc + 0x1c4),3,cVar1);
      *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + '\x01';
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 1;
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar6 + *(short *)(&DAT_8033978a + iVar3) * 0x30 + 0x8d4),
                 (float *)(iVar3 + -0x7fcc6874),
                 (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
      zz_008458c_((float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    }
  }
  return;
}



// ==== 8013b768  zz_013b768_ ====

void zz_013b768_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar3 + 0x159) == '\x04') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(iVar3 + 0x159) = 0;
    *(undefined1 *)(iVar3 + 0x15a) = 0;
    *(undefined2 *)(iVar3 + 0x784) = *(undefined2 *)(iVar3 + 0x79e);
    *(undefined2 *)(iVar3 + 0x786) = *(undefined2 *)(iVar3 + 0x79e);
    return;
  }
  iVar4 = *(int *)(iVar3 + 0x148);
  if (iVar4 != 0) {
    uVar1 = *(undefined4 *)(iVar4 + 0x24);
    iVar2 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
    *(undefined4 *)(iVar2 + 0x1c4) = *(undefined4 *)(iVar4 + 0x20);
    *(undefined4 *)(iVar2 + 0x1c8) = uVar1;
    *(undefined4 *)(iVar2 + 0x1cc) = *(undefined4 *)(iVar4 + 0x28);
    if (*(char *)(iVar3 + 0x159) != '\x03') {
      return;
    }
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x22e) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 300;
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(iVar3 + 0x159) = 0;
  *(undefined1 *)(iVar3 + 0x15a) = 0;
  *(undefined2 *)(iVar3 + 0x784) = *(undefined2 *)(iVar3 + 0x79e);
  *(undefined2 *)(iVar3 + 0x786) = *(undefined2 *)(iVar3 + 0x79e);
  return;
}



// ==== 8013b828  zz_013b828_ ====

/* WARNING: Removing unreachable block (ram,0x8013bcd0) */
/* WARNING: Removing unreachable block (ram,0x8013b838) */

void zz_013b828_(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float fStack_34;
  float local_30;
  
  iVar7 = *(int *)(param_1 + 0x90);
  iVar6 = *(int *)(iVar7 + 0x144);
  dVar8 = gnt4_PSVECSquareDistance_bl((float *)(iVar6 + 0x2c),(float *)(iVar6 + 0x5e8));
  if ((double)FLOAT_8043a0b8 < dVar8) {
    dVar9 = 1.0 / SQRT(dVar8);
    dVar9 = DOUBLE_8043a0c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_8043a0c8);
    dVar9 = DOUBLE_8043a0c0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_8043a0c8);
    dVar8 = (double)(float)(dVar8 * DOUBLE_8043a0c0 * dVar9 *
                                    -(dVar8 * dVar9 * dVar9 - DOUBLE_8043a0c8));
  }
  if ((double)(FLOAT_8043a0d0 * *(float *)(iVar6 + 0xb4)) < dVar8) {
    *(undefined1 *)(param_1 + 0x22e) = 0;
  }
  else {
    *(char *)(param_1 + 0x22e) = *(char *)(param_1 + 0x22e) + '\x01';
  }
  if (0 < *(short *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  if ((((*(char *)(iVar7 + 0x159) == '\x04') || (*(char *)(iVar6 + 0x6cb) != '\0')) ||
      (iVar4 = zz_0084434_(iVar6,0), iVar4 != 0)) ||
     ((((byte)PTR_DAT_80433934[0xd4] != 0 &&
       (((int)*(char *)(iVar6 + 0x3e5) & ~(uint)(byte)PTR_DAT_80433934[0xd4]) != 0)) ||
      ((',' < *(char *)(param_1 + 0x22e) || (*(short *)(param_1 + 0x1c) < 1)))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(iVar7 + 0x159) = 0;
    *(undefined1 *)(iVar7 + 0x15a) = 0;
    *(undefined2 *)(iVar7 + 0x784) = *(undefined2 *)(iVar7 + 0x79e);
    *(undefined2 *)(iVar7 + 0x786) = *(undefined2 *)(iVar7 + 0x79e);
  }
  else {
    *(undefined1 *)(iVar6 + 0x719) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar6 + *(char *)(iVar7 + 0x158) * 0x30 + 0x8d4),(float *)(iVar7 + 0x14c),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + (*(char *)(param_1 + 0x22c) + -1) * 0xc + 0x1c4),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4),&fStack_34);
    dVar8 = gnt4_PSVECMag_bl(&fStack_34);
    if (dVar8 <= (double)(FLOAT_8043a0d4 * *(float *)(param_1 + 0xb4))) {
      if (*(char *)(param_1 + 0x22c) == 1) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        *(undefined1 *)(iVar7 + 0x159) = 0;
        *(undefined1 *)(iVar7 + 0x15a) = 0;
        *(undefined2 *)(iVar7 + 0x784) = *(undefined2 *)(iVar7 + 0x79e);
        *(undefined2 *)(iVar7 + 0x786) = *(undefined2 *)(iVar7 + 0x79e);
        zz_00f036c_(iVar6,0xc3);
        return;
      }
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x22c) + 0x224) = 0;
      *(char *)(param_1 + 0x22c) = *(char *)(param_1 + 0x22c) + -1;
      *(char *)(iVar7 + 0x15a) = *(char *)(iVar7 + 0x15a) + -1;
      zz_00f0214_(iVar6,4,3);
      *(undefined2 *)(param_1 + 0x1c) = 300;
    }
    gnt4_PSVECNormalize_bl(&fStack_34,&fStack_34);
    fVar1 = FLOAT_8043a0b8;
    if (*(char *)(iVar6 + 0x87) == '\0') {
      fVar1 = FLOAT_8043a0d4 * *(float *)(param_1 + 0xb4);
      iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
      fVar2 = *(float *)(iVar4 + 0x1bc) - *(float *)(iVar4 + 0x1c8);
      if (((fVar1 <= fVar2) || (fVar2 <= -fVar1)) && (FLOAT_8043a0d8 <= local_30)) {
        *(float *)(iVar6 + 0x48) = FLOAT_8043a0b8;
        *(byte *)(iVar6 + 0x732) = *(byte *)(iVar6 + 0x732) | 0x40;
      }
    }
    else if ((FLOAT_8043a0b8 < local_30) &&
            (*(byte *)(iVar6 + 0x732) = *(byte *)(iVar6 + 0x732) | 0x40,
            *(float *)(iVar6 + 0x48) <= fVar1)) {
      *(float *)(iVar6 + 0x48) = fVar1;
    }
    dVar9 = (double)(FLOAT_8043a0d4 * *(float *)(param_1 + 0xb4));
    if ((double)(float)((double)FLOAT_8043a0dc * dVar9) < dVar8) {
      dVar8 = (double)(FLOAT_8043a0e0 * *(float *)(param_1 + 0xb4));
      if (*(char *)(iVar6 + 0x70c) != '\0') {
        dVar8 = (double)(float)(dVar8 * (double)*(float *)(iVar6 + 0x768));
      }
      gnt4_PSQUATScale_bl(dVar8,&fStack_34,&fStack_34);
    }
    else {
      gnt4_PSQUATScale_bl(dVar9,&fStack_34,&fStack_34);
    }
    zz_0084498_(iVar6,&fStack_34);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar6 + *(char *)(iVar7 + 0x158) * 0x30 + 0x8d4),(float *)(iVar7 + 0x14c),
               (float *)(param_1 + *(char *)(param_1 + 0x22c) * 0xc + 0x1c4));
    puVar5 = (undefined4 *)(param_1 + 0x1c4);
    iVar6 = 0;
    iVar7 = 2;
    do {
      if (*(char *)(param_1 + 0x22c) < iVar6) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        *puVar5 = *(undefined4 *)(iVar4 + 0x1c4);
        puVar5[1] = uVar3;
        puVar5[2] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar6 + 1) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar5[3] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar5[4] = uVar3;
        puVar5[5] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar6 + 2) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar5[6] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar5[7] = uVar3;
        puVar5[8] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      if ((int)*(char *)(param_1 + 0x22c) < iVar6 + 3) {
        iVar4 = param_1 + *(char *)(param_1 + 0x22c) * 0xc;
        uVar3 = *(undefined4 *)(iVar4 + 0x1c8);
        puVar5[9] = *(undefined4 *)(iVar4 + 0x1c4);
        puVar5[10] = uVar3;
        puVar5[0xb] = *(undefined4 *)(iVar4 + 0x1cc);
      }
      puVar5 = puVar5 + 0xc;
      iVar6 = iVar6 + 4;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  return;
}



// ==== 8013bd04  FUN_8013bd04 ====

void FUN_8013bd04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013bd24  FUN_8013bd24 ====

void FUN_8013bd24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8013bd80  FUN_8013bd80 ====

void FUN_8013bd80(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,5);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1b;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 5;
    *(code **)(puVar1 + 0xc) = FUN_8013be88;
    *(code **)(puVar1 + 0x10c) = FUN_8013c264;
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



// ==== 8013be88  FUN_8013be88 ====

void FUN_8013be88(int param_1)

{
  (*(code *)(&PTR_FUN_803397e0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8013bec4  FUN_8013bec4 ====

void FUN_8013bec4(int param_1)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  
  uVar2 = *(char *)(param_1 + 0x13) * 0x24;
  if (uVar2 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar2);
    *(int **)(param_1 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    cVar1 = *(char *)(*(int *)(param_1 + 0x8c) + 1000);
    if (cVar1 == '\x05') {
      *(undefined1 *)(param_1 + 0x89) = 2;
    }
    else if (((byte)(cVar1 - 0xcU) < 3) || (cVar1 == '\x0f')) {
      *(undefined1 *)(param_1 + 0x89) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x89) = 3;
    }
    *(code **)(param_1 + 0x100) = FUN_8013c144;
    zz_0089100_(param_1,1,1);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 8013bfcc  FUN_8013bfcc ====

void FUN_8013bfcc(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  double dVar5;
  
  fVar2 = FLOAT_8043a0e8;
  iVar4 = *(int *)(param_9 + 0x8c);
  cVar1 = *(char *)(iVar4 + 0x655);
  if (((int)cVar1 & 1 << (int)*(char *)(param_9 + 0x11)) == 0) {
    *(float *)(param_9 + 0xd8) = FLOAT_8043a0e8;
    *(float *)(param_9 + 0xd4) = fVar2;
  }
  else {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar5 = (double)FLOAT_8043a0ec;
    param_1 = (double)FLOAT_8043a0f0;
    *(float *)(param_9 + 0xd4) = (float)(param_2 + dVar5);
    if (param_1 <= (double)(float)(param_2 + dVar5)) {
      *(float *)(param_9 + 0xd4) = (float)((double)*(float *)(param_9 + 0xd4) - param_1);
    }
    *(float *)(param_9 + 0xd8) = FLOAT_8043a0f4;
  }
  zz_013c410_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(int)cVar1,
              param_11,param_12,param_13,param_14,param_15,param_16);
  if (((int)*(char *)(iVar4 + 0x654) & 1 << (int)*(char *)(param_9 + 0x11)) == 0) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  else {
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(undefined2 *)(param_9 + 0x1c) = 5;
      zz_013c2f4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11
                  ,param_12,param_13,param_14,param_15,param_16);
    }
  }
  if (('\x01' < *(char *)(iVar4 + 0x18)) || (*(short *)(iVar4 + 0x94) != *(short *)(param_9 + 0x94))
     ) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8013c0fc  FUN_8013c0fc ====

void FUN_8013c0fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013c144  FUN_8013c144 ====

void FUN_8013c144(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
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
  
  iVar1 = *(int *)(param_1 + 0x8c);
  if (*(short *)(param_1 + 0x1e) != 0) {
    *(undefined4 *)(param_1 + 0x20) =
         *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8e0);
    *(undefined4 *)(param_1 + 0x24) =
         *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8f0);
    *(undefined4 *)(param_1 + 0x28) =
         *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x900);
    dVar8 = (double)*(float *)(param_1 + 0x24);
    dVar9 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
    iVar5 = 0;
    iVar6 = 0;
    iVar1 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar5) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar5) != 0) {
        iVar4 = *(int *)(param_1 + 0x54) + iVar6;
        zz_00457d4_('y',(float *)(param_1 + 0x114),afStack_48,*(short *)(iVar4 + 0x16));
        iVar3 = (int)*(short *)(iVar4 + 0x14);
        zz_00457d4_('x',afStack_48,afStack_48,*(short *)(iVar4 + 0x14));
        pfVar2 = (float *)(iVar4 + 8);
        uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
        zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar1 + 0xe0),
                    afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      }
      iVar6 = iVar6 + 0x24;
      iVar1 = iVar1 + 4;
      iVar5 = iVar5 + 1;
    }
  }
  return;
}



// ==== 8013c264  FUN_8013c264 ====

void FUN_8013c264(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 0x1e) != 0) {
    iVar1 = 0;
    iVar2 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar1) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
        zz_00097b4_(*(int *)(iVar2 + 0xe0),1);
      }
      iVar2 = iVar2 + 4;
      iVar1 = iVar1 + 1;
    }
  }
  return;
}



// ==== 8013c2f4  zz_013c2f4_ ====

void zz_013c2f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar4 = 0;
  iVar5 = *(int *)(param_9 + 0x8c);
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar4) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1e) & 1 << iVar4) == 0) {
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)(1 << iVar4);
      piVar3 = (int *)(*(int *)(param_9 + 0x54) + iVar4 * 0x24);
      piVar3[7] = (int)(*(float *)(iVar5 + 0xb4) * *(float *)(iVar5 + 0x7fc));
      *(undefined2 *)(piVar3 + 6) = 0;
      *(undefined2 *)((int)piVar3 + 0x1a) = uRam80434662;
      uVar1 = zz_00055fc_();
      *(short *)(piVar3 + 5) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      *(short *)((int)piVar3 + 0x16) = (short)(uVar1 << 8);
      zz_0018f88_(piVar3,iRam80434664,(float *)(piVar3 + 2));
      uVar6 = gnt4_PSQUATScale_bl((double)(float)piVar3[7],(float *)(piVar3 + 2),
                                  (float *)(piVar3 + 2));
      iVar4 = iVar4 * 4 + 0xe0;
      pfVar2 = (float *)(int)DAT_80434660;
      zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar4),(int)pfVar2,param_12,param_13,param_14,param_15,param_16
                 );
      uVar6 = zz_00086b8_((double)(*(float *)(param_9 + 0xd4) + *(float *)(param_9 + 0xd8)),param_2,
                          param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                          *(int *)(param_9 + iVar4),pfVar2,param_12,param_13,param_14,param_15,
                          param_16);
      uVar6 = zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + iVar4),extraout_r4,pfVar2,param_12,param_13,param_14,
                          param_15,param_16);
      zz_0007d40_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + iVar4),extraout_r4_00,pfVar2,param_12,param_13,param_14,
                  param_15,param_16);
      iVar4 = (int)*(char *)(param_9 + 0x13);
    }
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 8013c410  zz_013c410_ ====

int zz_013c410_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (*(short *)(param_9 + 0x1e) != 0) {
    iVar4 = 0;
    iVar6 = 0;
    iVar5 = param_9;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar4) break;
      if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar4) != 0) {
        piVar3 = (int *)(*(int *)(param_9 + 0x54) + iVar6);
        sVar1 = *(short *)(piVar3 + 6);
        *(short *)(piVar3 + 6) = sVar1 + 1;
        if ((short)(sVar1 + 1) < *(short *)((int)piVar3 + 0x1a)) {
          pfVar2 = (float *)(piVar3 + 2);
          zz_0018fd8_(piVar3,(int)*(short *)(piVar3 + 6),pfVar2);
          gnt4_PSQUATScale_bl((double)(float)piVar3[7],(float *)(piVar3 + 2),(float *)(piVar3 + 2));
          uVar7 = zz_00086b8_((double)(*(float *)(param_9 + 0xd4) + *(float *)(param_9 + 0xd8)),
                              param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                              *(int *)(iVar5 + 0xe0),pfVar2,param_12,param_13,param_14,param_15,
                              param_16);
          uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar5 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,
                              param_15,param_16);
          zz_0007d40_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0xe0),extraout_r4_00,pfVar2,param_12,param_13,param_14,
                      param_15,param_16);
        }
        else {
          *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) & ~(ushort)(1 << iVar4);
        }
      }
      iVar6 = iVar6 + 0x24;
      iVar5 = iVar5 + 4;
      iVar4 = iVar4 + 1;
    }
  }
  return (int)*(short *)(param_9 + 0x1e);
}



// ==== 8013c50c  zz_013c50c_ ====

void zz_013c50c_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0xdc) == 0) {
    piVar2 = zz_0006dc8_(0xc0);
    *(int **)(param_1 + 0xdc) = piVar2;
    puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
    if (puVar3 != (undefined4 *)0x0) {
      uVar1 = *(undefined4 *)(param_1 + 0x24);
      *puVar3 = *(undefined4 *)(param_1 + 0x20);
      puVar3[1] = uVar1;
      puVar3[2] = *(undefined4 *)(param_1 + 0x28);
      zz_00e3ca0_(param_1,-0x7fcc6810,5,puVar3 + 3,(float *)(puVar3 + 0x12));
    }
  }
  return;
}



// ==== 8013c590  zz_013c590_ ====

void zz_013c590_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
    if (puVar2 != (undefined4 *)0x0) {
      uVar1 = *(undefined4 *)(param_1 + 0x24);
      *puVar2 = *(undefined4 *)(param_1 + 0x20);
      puVar2[1] = uVar1;
      puVar2[2] = *(undefined4 *)(param_1 + 0x28);
      if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
        FUN_800e3dec(param_1,(float *)&DAT_803397f0,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12)
                     ,(int *)&DAT_803398f0);
      }
      else {
        FUN_800e4f9c(param_1,-0x7fcc6810,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      }
    }
  }
  return;
}



// ==== 8013c62c  zz_013c62c_ ====

void zz_013c62c_(int param_1)

{
  if (*(int **)(param_1 + 0xdc) != (int *)0x0) {
    zz_0197ad8_(*(int **)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}



// ==== 8013c66c  zz_013c66c_ ====

void zz_013c66c_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  if ((*(int *)(param_1 + 0xdc) != 0) &&
     (pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc), pfVar2 != (float *)0x0)) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc6810,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcc6810,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 8013c844  FUN_8013c844 ====

void FUN_8013c844(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(undefined4 *)(param_9 + 0x144) = 0;
  if (*(short *)(param_9 + 1000) == 0x802) {
    zz_013c50c_(param_9);
    iVar1 = zz_0006f98_(param_9);
    iVar4 = iVar1;
    for (cVar3 = '\0'; cVar3 < '\x02'; cVar3 = cVar3 + '\x01') {
      iVar2 = *(int *)(iVar4 + 0x708);
      uVar5 = zz_00086b8_((double)FLOAT_8043a0f8,param_2,param_3,param_4,param_5,param_6,param_7,
                          param_8,*(int *)(iVar1 + 0x600),iVar2,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                          extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
      zz_0007d40_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,extraout_r4_00
                  ,param_11,param_12,param_13,param_14,param_15,param_16);
      iVar4 = iVar4 + 0x80;
    }
  }
  else if (*(short *)(param_9 + 1000) == 0x803) {
    zz_013c50c_(param_9);
    for (cVar3 = '\0'; cVar3 < '\x0e'; cVar3 = cVar3 + '\x01') {
      zz_0120b58_(param_9,cVar3);
    }
    iVar1 = zz_0006f98_(param_9);
    iVar4 = iVar1;
    for (cVar3 = '\0'; cVar3 < '\x02'; cVar3 = cVar3 + '\x01') {
      iVar2 = *(int *)(iVar4 + 0x708);
      uVar5 = zz_00086b8_((double)FLOAT_8043a0fc,param_2,param_3,param_4,param_5,param_6,param_7,
                          param_8,*(int *)(iVar1 + 0x600),iVar2,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                          extraout_r4_01,param_11,param_12,param_13,param_14,param_15,param_16);
      zz_0007d40_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,extraout_r4_02
                  ,param_11,param_12,param_13,param_14,param_15,param_16);
      iVar4 = iVar4 + 0x80;
    }
    *(undefined4 *)(param_9 + 0x144) = 0x708;
  }
  return;
}



// ==== 8013c9d8  FUN_8013c9d8 ====

void FUN_8013c9d8(int param_1)

{
  zz_013c590_(param_1);
  return;
}



// ==== 8013ca04  FUN_8013ca04 ====

void FUN_8013ca04(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 1000) == 0x802) {
    if ((((0 < *(short *)(param_1 + 0x784)) && ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0)) &&
        (uVar1 = zz_006ab9c_(param_1), uVar1 != 0)) &&
       (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 != 0)) {
      zz_006a3d0_(param_1,'\x04',0,0);
    }
  }
  else if (*(short *)(param_1 + 1000) == 0x803) {
    if ((0 < *(int *)(param_1 + 0x144)) &&
       (*(int *)(param_1 + 0x144) = *(int *)(param_1 + 0x144) + -1, *(int *)(param_1 + 0x144) == 0))
    {
      *(undefined4 *)(param_1 + 0x144) = 0xffffffff;
    }
    if ((*(int *)(param_1 + 0x144) < 0) && (uVar1 = zz_006ab9c_(param_1), uVar1 != 0)) {
      *(undefined4 *)(param_1 + 0x144) = 0;
      zz_006a3d0_(param_1,'\x05',0,0);
    }
  }
  return;
}



// ==== 8013cafc  FUN_8013cafc ====

void FUN_8013cafc(int param_1)

{
  zz_013c62c_(param_1);
  return;
}



// ==== 8013cb1c  FUN_8013cb1c ====

void FUN_8013cb1c(int param_1)

{
  zz_013c66c_(param_1);
  return;
}



// ==== 8013cb40  FUN_8013cb40 ====

void FUN_8013cb40(int param_1)

{
  (*(code *)(&PTR_FUN_8033993c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8013cb7c  FUN_8013cb7c ====

void FUN_8013cb7c(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_8043a108) * FLOAT_8043a100);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  (*(code *)(&PTR_FUN_803399e4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8013cc08  FUN_8013cc08 ====

void FUN_8013cc08(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803399f8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013cc50  FUN_8013cc50 ====

void FUN_8013cc50(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_013d5a4_(param_1);
  fVar1 = FLOAT_8043a0f8;
  *(float *)(param_1 + 0x50) = FLOAT_8043a0f8;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a0f8;
  return;
}



// ==== 8013cd30  FUN_8013cd30 ====

/* WARNING: Removing unreachable block (ram,0x8013ce14) */
/* WARNING: Removing unreachable block (ram,0x8013cd40) */

void FUN_8013cd30(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043a0f8;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043a0f8;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_8013d600(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043a118 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8013ce30  FUN_8013ce30 ====

void FUN_8013ce30(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_8043a0f8) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043a0f8) {
    if ((*(char *)(param_1 + 0x1cef) < '\0') && ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0)) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if (iVar1 == 0) goto LAB_8013cf60;
      if (('\0' < *(char *)(param_1 + 0x6ef)) && (-1 < *(int *)(param_1 + 0x144))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_8043a110;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
        return;
      }
    }
    else {
      *(float *)(param_1 + 0x55c) = FLOAT_8043a0f8;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_8043a118) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_8013cf60:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8013cfd8  FUN_8013cfd8 ====

void FUN_8013cfd8(int param_1)

{
  (*(code *)(&PTR_FUN_80339a04)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013d014  FUN_8013d014 ====

void FUN_8013d014(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 6;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 2;
  }
  if (((uVar1 & 0x20) != 0) &&
     (iVar2 = *(char *)(param_1 + 0x1d10) + 8, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_8043a110,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_013d5a4_(param_1);
  return;
}



// ==== 8013d0bc  FUN_8013d0bc ====

void FUN_8013d0bc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_8043a0f8;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_8013d600(param_1);
    }
  }
  return;
}



// ==== 8013d190  FUN_8013d190 ====

void FUN_8013d190(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_8043a0f8) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_8043a0f8) {
    if ((*(char *)(param_9 + 0x1cef) < '\0') && ((*(uint *)(param_9 + 0x5b4) & 0x200) != 0)) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 == 0) goto LAB_8013d364;
      if (('\0' < *(char *)(param_9 + 0x6ef)) && (-1 < *(int *)(param_9 + 0x144))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 5;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 7;
          }
          zz_004beb8_((double)FLOAT_8043a110,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_8043a110;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,3,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          *(undefined1 *)(param_9 + 0x581) = 2;
          iVar1 = *(char *)(param_9 + 0x1d10) + 9;
          if (*(char *)(param_9 + 0x5db) == '\x0f') {
            iVar1 = 1;
          }
          zz_004beb8_((double)FLOAT_8043a110,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
    }
    else {
      *(float *)(param_9 + 0x55c) = FLOAT_8043a0f8;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_8013d364:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8013d398  FUN_8013d398 ====

void FUN_8013d398(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80339a10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013d3e0  FUN_8013d3e0 ====

void FUN_8013d3e0(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_8043a0fc;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043a110,param_1,1,2,*(char *)(param_1 + 0x6ee) + 4,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043a110,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  zz_013d5a4_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a0f8;
  return;
}



// ==== 8013d4b4  FUN_8013d4b4 ====

/* WARNING: Removing unreachable block (ram,0x8013d588) */
/* WARNING: Removing unreachable block (ram,0x8013d4c4) */

void FUN_8013d4b4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043a0f8;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_8043a0f8;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_8013d600(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8013d5a4  zz_013d5a4_ ====

void zz_013d5a4_(int param_1)

{
  *(float *)(param_1 + 0x560) = FLOAT_8043a11c;
  *(undefined4 *)(param_1 + 0x558) =
       *(undefined4 *)(&DAT_80339964 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined4 *)(param_1 + 0x55c) =
       *(undefined4 *)(&DAT_803399a4 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(char *)(param_1 + 0x6ef) = s_ddddddddddddddd_80339954[*(byte *)(param_1 + 0x3e9)];
  return;
}



// ==== 8013d600  FUN_8013d600 ====

/* WARNING: Removing unreachable block (ram,0x8013d79c) */
/* WARNING: Removing unreachable block (ram,0x8013d610) */

void FUN_8013d600(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  *(float *)(param_1 + 0x560) = FLOAT_8043a11c;
  *(undefined4 *)(param_1 + 0x558) =
       *(undefined4 *)(&DAT_80339964 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined4 *)(param_1 + 0x55c) =
       *(undefined4 *)(&DAT_803399a4 + (uint)*(byte *)(param_1 + 0x3e9) * 4);
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar4 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_8043a0f8;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar2 = FUN_800452a0(dVar4,dVar5);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar5 = (double)local_24;
      local_24 = FLOAT_8043a0f8;
      dVar4 = gnt4_PSVECMag_bl(&local_28);
      iVar3 = FUN_800452a0(dVar5,dVar4);
      *(short *)(param_1 + 0x1900) = (short)iVar2 + (short)iVar3;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                  (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                  (float *)(param_1 + 0x1628));
    }
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x803) {
        zz_00c3be0_(param_1,0x22);
      }
      else if ((sVar1 < 0x803) && (0x801 < sVar1)) {
        zz_0082824_(param_1,0x2d);
      }
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
  }
  return;
}



// ==== 8013d7bc  FUN_8013d7bc ====

void FUN_8013d7bc(int param_1)

{
  (*(code *)(&PTR_FUN_80339a1c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8013d7f8  FUN_8013d7f8 ====

void FUN_8013d7f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80339a30)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013d860  FUN_8013d860 ====

void FUN_8013d860(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043a11c;
  fVar2 = FLOAT_8043a0f8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8013d940  FUN_8013d940 ====

void FUN_8013d940(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_8043a120;
    fVar2 = FLOAT_8043a11c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_8043a0f8;
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 8013d9e0  FUN_8013d9e0 ====

void FUN_8013d9e0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043a0f8;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)FLOAT_8043a124,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043a110;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8013da94  FUN_8013da94 ====

void FUN_8013da94(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a124,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 8013db28  FUN_8013db28 ====

void FUN_8013db28(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar4 = FLOAT_8043a120;
  fVar3 = FLOAT_8043a11c;
  if ((*(char *)(param_1 + 0x1cef) < '\0') && (*(char *)(param_1 + 0x745) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_8043a0f8;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x44) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_8043a110;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    FUN_8013dc0c(param_1);
  }
  return;
}



// ==== 8013dbec  FUN_8013dbec ====

void FUN_8013dbec(int param_1)

{
  FUN_8013dc0c(param_1);
  return;
}



// ==== 8013dc0c  FUN_8013dc0c ====

void FUN_8013dc0c(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  fVar2 = FLOAT_8043a120;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar1 = FLOAT_8043a0f8;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
  }
  if (*(float *)(param_1 + 0x764) < FLOAT_8043a124) {
    zz_006ed8c_((double)FLOAT_8043a128,param_1);
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    zz_006ed8c_((double)FLOAT_8043a128,param_1);
  }
  zz_006ed8c_((double)FLOAT_8043a114,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8013dcec  FUN_8013dcec ====

void FUN_8013dcec(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80339a60)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013dd3c  FUN_8013dd3c ====

void FUN_8013dd3c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a12c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  fVar2 = FLOAT_8043a0f8;
  *(float *)(param_1 + 0x50) = FLOAT_8043a0f8;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8013de88  FUN_8013de88 ====

void FUN_8013de88(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043a11c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8013df58  FUN_8013df58 ====

void FUN_8013df58(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a11c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a0fc;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a11c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_8043a130,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043a134;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x558) = FLOAT_8043a0f8;
    }
  }
  return;
}



// ==== 8013e064  FUN_8013e064 ====

void FUN_8013e064(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043a11c;
  fVar1 = FLOAT_8043a0f8;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x44) = FLOAT_8043a0f8;
    fVar2 = FLOAT_8043a110;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x71c) == '\0') && (*(char *)(param_1 + 0x542) != '\0')) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a108) * FLOAT_8043a138);
  }
  zz_006ed8c_((double)FLOAT_8043a13c,param_1);
  dVar5 = (double)FLOAT_8043a0fc;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a140 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043a140 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8013e1d8  FUN_8013e1d8 ====

void FUN_8013e1d8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80339a70)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013e240  FUN_8013e240 ====

void FUN_8013e240(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 5;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(undefined1 *)(param_1 + 0x6ea) = 6;
  }
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a11c;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043a110,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a0f8;
  return;
}



// ==== 8013e33c  FUN_8013e33c ====

void FUN_8013e33c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043a120;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_8043a144;
    fVar2 = FLOAT_8043a0f8;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043a120;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 8013e43c  FUN_8013e43c ====

void FUN_8013e43c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a124,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8013e4d8  FUN_8013e4d8 ====

void FUN_8013e4d8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_8043a138,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  if (FLOAT_8043a118 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8013e578  FUN_8013e578 ====

void FUN_8013e578(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80339a80)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013e5c8  FUN_8013e5c8 ====

void FUN_8013e5c8(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a12c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 8;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8013e6e4  FUN_8013e6e4 ====

void FUN_8013e6e4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043a114,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_8043a11c;
    fVar1 = FLOAT_8043a0f8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8013e7d8  FUN_8013e7d8 ====

void FUN_8013e7d8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1d0_(param_1,0xc0,1,0x2000);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a11c * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_8043a0fc;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a11c * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a130,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043a134;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x558) = FLOAT_8043a0f8;
    }
  }
  return;
}



