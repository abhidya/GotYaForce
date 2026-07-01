// ==== 800df37c  FUN_800df37c ====

/* WARNING: Removing unreachable block (ram,0x800df4ac) */
/* WARNING: Removing unreachable block (ram,0x800df38c) */

void FUN_800df37c(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float afStack_28 [4];
  
  iVar4 = *(int *)(param_1 + 0x8c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  uVar2 = zz_00055fc_();
  *(short *)(param_1 + 0x70) = (short)(uVar2 << 8);
  uVar2 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar2 << 8);
  iVar3 = ((int)*(short *)(param_1 + 0x1c) & 1U) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_80316150 + iVar3);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_8031614c + iVar3);
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_80316154 + iVar3);
  gnt4_PSQUATScale_bl((double)*(float *)(iVar4 + 0xb4),(float *)(param_1 + 0x58),
                      (float *)(param_1 + 0x58));
  gnt4_PSVECSubtract_bl(*(float **)(param_1 + 0x148),*(float **)(param_1 + 0x144),afStack_28);
  dVar5 = gnt4_PSVECMag_bl(afStack_28);
  if ((double)FLOAT_80438d38 != dVar5) {
    uVar2 = zz_00055fc_();
    *(float *)(param_1 + 0x4c) =
         *(float *)(iVar4 + 0xb4) * *(float *)(&DAT_80316164 + (uVar2 & 0xf) * 4) +
         *(float *)(param_1 + 0x4c);
    gnt4_PSVECNormalize_bl(afStack_28,afStack_28);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x4c),afStack_28,afStack_28);
    gnt4_PSVECAdd_bl(*(float **)(param_1 + 0x144),afStack_28,(float *)(param_1 + 0x20));
  }
  if ((dVar5 <= (double)*(float *)(param_1 + 0x4c)) || ('\x01' < *(char *)(iVar4 + 0x18))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800df4cc  FUN_800df4cc ====

void FUN_800df4cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800df50c  FUN_800df50c ====

void FUN_800df50c(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
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
  
  fVar1 = FLOAT_80438d38;
  puVar4 = *(undefined4 **)(param_1 + 0x144);
  uVar2 = puVar4[1];
  *(undefined4 *)(param_1 + 0x20) = *puVar4;
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  *(undefined4 *)(param_1 + 0x28) = puVar4[2];
  *(float *)(param_1 + 0x4c) = fVar1;
  uVar3 = zz_00055fc_();
  *(short *)(param_1 + 0x74) = (short)(uVar3 << 8);
  *(undefined2 *)(param_1 + 0x80) = 0x888;
  uVar3 = zz_00055fc_();
  *(float *)(param_1 + 0x58) =
       FLOAT_80438d3c +
       (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438d48) / FLOAT_80438d40;
  uVar3 = zz_00055fc_();
  *(float *)(param_1 + 0x5c) =
       FLOAT_80438d3c +
       (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438d48) / FLOAT_80438d40;
  uVar3 = zz_00055fc_();
  dVar7 = DOUBLE_80438d48;
  dVar6 = (double)(float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438d48);
  *(float *)(param_1 + 0x60) = FLOAT_80438d3c + (float)(dVar6 / (double)FLOAT_80438d40);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),
                      (float *)(param_1 + 0x58));
  gnt4_PSVECSubtract_bl
            (*(float **)(param_1 + 0x148),*(float **)(param_1 + 0x144),(float *)(param_1 + 0x38));
  *(code **)(param_1 + 0x100) = FUN_800df774;
  uVar5 = zz_0089100_(param_1,1,1);
  zz_000726c_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb374,*(int *)(param_1 + 0xe0),
              (float *)0x1e,(int)*(char *)(param_1 + 0x88),in_r7,in_r8,in_r9,in_r10);
  *(undefined1 *)(param_1 + 0x82) = 1;
  return;
}



// ==== 800df66c  FUN_800df66c ====

/* WARNING: Removing unreachable block (ram,0x800df754) */
/* WARNING: Removing unreachable block (ram,0x800df67c) */

void FUN_800df66c(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  float afStack_28 [4];
  
  iVar2 = *(int *)(param_1 + 0x8c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
  gnt4_PSVECSubtract_bl
            (*(float **)(param_1 + 0x148),*(float **)(param_1 + 0x144),(float *)(param_1 + 0x38));
  dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438d38 != dVar3) {
    uVar1 = zz_00055fc_();
    *(float *)(param_1 + 0x4c) =
         *(float *)(param_1 + 0xb4) * *(float *)(&DAT_80316164 + (uVar1 & 0xf) * 4) +
         *(float *)(param_1 + 0x4c);
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),afStack_28);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x4c),afStack_28,afStack_28);
    gnt4_PSVECAdd_bl(*(float **)(param_1 + 0x144),afStack_28,(float *)(param_1 + 0x20));
  }
  if ((dVar3 <= (double)*(float *)(param_1 + 0x4c)) || ('\x01' < *(char *)(iVar2 + 0x18))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800df774  FUN_800df774 ====

void FUN_800df774(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,param_1 + 0x38,&DAT_802b0ca8);
  }
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 800df810  FUN_800df810 ====

void FUN_800df810(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800df850  FUN_800df850 ====

void FUN_800df850(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  uint uVar2;
  int *piVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  uVar2 = *(char *)(param_9 + 0x13) * 0x18;
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
    iVar6 = *(int *)(param_9 + 0x8c);
    *(code **)(param_9 + 0x100) = FUN_800dfa8c;
    zz_0089100_(param_9,1,1);
    uVar9 = zz_01e801c_(iVar6);
    iVar8 = 0;
    iVar7 = 0;
    for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
      puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
      puVar4 = (undefined4 *)((&PTR_DAT_80315f08)[*(char *)(param_9 + 0x12) * 2] + iVar7);
      uVar2 = zz_00055fc_();
      *(short *)(puVar5 + 5) = (short)(uVar2 << 8);
      uVar2 = zz_00055fc_();
      iVar8 = iVar8 + 0x18;
      *(short *)((int)puVar5 + 0x16) = (short)(uVar2 << 8);
      iVar7 = iVar7 + 0x14;
      *puVar5 = *puVar4;
      puVar5[4] = puVar4[1];
      uVar1 = puVar4[3];
      puVar5[1] = puVar4[2];
      puVar5[2] = uVar1;
      puVar5[3] = puVar4[4];
    }
    zz_000744c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x8b,(int)*(char *)(param_9 + 0x13),
                (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800df9b8  FUN_800df9b8 ====

void FUN_800df9b8(int param_1)

{
  byte bVar2;
  uint uVar1;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 0x8c);
  if ((*(uint *)(iVar4 + 0x8c4) & 1) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_01e801c_(iVar4);
  }
  bVar2 = zz_008b480_();
  if ((bVar2 == 0) || ((bVar2 & *(byte *)(iVar4 + 0x3e5)) != 0)) {
    iVar5 = 0;
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
      iVar3 = *(int *)(param_1 + 0x54) + iVar5;
      uVar1 = zz_00055fc_();
      *(short *)(iVar3 + 0x14) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      iVar5 = iVar5 + 0x18;
      *(short *)(iVar3 + 0x16) = (short)(uVar1 << 8);
    }
  }
  return;
}



// ==== 800dfa8c  FUN_800dfa8c ====

/* WARNING: Removing unreachable block (ram,0x800dfb94) */

void FUN_800dfa8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  float afStack_68 [3];
  float afStack_5c [16];
  
  iVar7 = 0;
  iVar8 = *(int *)(param_9 + 0x8c);
  iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  iVar9 = 0;
  while (iVar7 < *(char *)(param_9 + 0x13)) {
    piVar6 = (int *)(*(int *)(param_9 + 0x54) + iVar9);
    gnt4_PSQUATScale_bl((double)(*(float *)(iVar8 + 0x7fc) * (float)piVar6[4]),
                        (float *)(&DAT_8031614c + (*(short *)(param_9 + 0x1c) + iVar7 & 1U) * 0xc),
                        afStack_68);
    zz_00455fc_((float *)(iVar8 + *piVar6 * 0x30 + 0x8d4),afStack_5c,(float *)(piVar6 + 1));
    zz_00457d4_('y',afStack_5c,afStack_5c,*(short *)((int)piVar6 + 0x16));
    iVar5 = (int)*(short *)(piVar6 + 5);
    zz_00457d4_('x',afStack_5c,afStack_5c,*(short *)(piVar6 + 5));
    pfVar4 = afStack_68;
    uVar10 = zz_00456a0_(afStack_5c,afStack_5c,pfVar4);
    if (iVar2 == 0) {
      pfVar4 = (float *)&DAT_80438d58;
      gnt4___assert_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80438d50,
                       0x495,&DAT_80438d58,iVar5,in_r7,in_r8,in_r9,in_r10);
    }
    uVar10 = gnt4_PSMTXCopy_bl(afStack_5c,(float *)(iVar2 + 0x44));
    *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
    if (iVar2 != 0) {
      uVar3 = *(uint *)(iVar2 + 0x14);
      bVar1 = false;
      if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        gnt4_HSD_JObjSetMtxDirtySub_bl
                  (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                   (undefined *)pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
      }
    }
    iVar9 = iVar9 + 0x18;
    iVar7 = iVar7 + 1;
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
  }
  return;
}



// ==== 800dfc10  FUN_800dfc10 ====

void FUN_800dfc10(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  return;
}



// ==== 800dfd34  FUN_800dfd34 ====

void FUN_800dfd34(int param_1)

{
  zz_00de5a4_(param_1,0,param_1 + 0x144);
  zz_00de5a4_(param_1,1,(undefined1 *)(param_1 + 0x145));
  zz_00de8f4_(param_1);
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  zz_00c74ec_(param_1,0xd);
  return;
}



// ==== 800dfda4  FUN_800dfda4 ====

void FUN_800dfda4(int param_1)

{
  if (0 < *(short *)(param_1 + 0x784)) {
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined1 *)(param_1 + 0x147) = 0;
    *(undefined1 *)(param_1 + 0x148) = 0;
    *(undefined1 *)(param_1 + 0x149) = 0;
  }
  if ((*(char *)(param_1 + 0x144) == '\0') && (*(char *)(param_1 + 0x145) == '\0')) {
    if (*(short *)(param_1 + 0x774) < 1) {
      zz_006de10_(param_1,0);
    }
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
  }
  else {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
  }
  return;
}



// ==== 800dfe4c  FUN_800dfe4c ====

void FUN_800dfe4c(int param_1)

{
  (*(code *)(&PTR_FUN_80316ac0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800dfe88  FUN_800dfe88 ====

void FUN_800dfe88(int param_1)

{
  (*(code *)(&PTR_FUN_80316acc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800dfec4  FUN_800dfec4 ====

void FUN_800dfec4(int param_1)

{
  zz_00f1e30_(param_1,&DAT_80316ae0);
  return;
}



// ==== 800dfeec  FUN_800dfeec ====

uint FUN_800dfeec(int param_1)

{
  char *pcVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  
  uVar2 = zz_006dbe0_(param_1,0,1,1);
  if (uVar2 != 0) {
    iVar4 = 0;
    iVar5 = 0;
    do {
      pcVar1 = (char *)(param_1 + iVar5 + 0x144);
      if (*pcVar1 == '\0') {
        *pcVar1 = '\x01';
        bVar3 = zz_00e0e90_(param_1,(char)iVar5,0,pcVar1);
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



// ==== 800dffd0  FUN_800dffd0 ====

void FUN_800dffd0(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80438d68;
  fVar1 = FLOAT_80438d60;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80438d68) * FLOAT_80438d60);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) - dVar2
                           ) * fVar1);
  (*(code *)(&PTR_FUN_80316af4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800e0070  FUN_800e0070 ====

void FUN_800e0070(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 800e0094  FUN_800e0094 ====

void FUN_800e0094(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 800e00b8  FUN_800e00b8 ====

void FUN_800e00b8(int param_1)

{
  zz_00f3028_(param_1);
  return;
}



// ==== 800e00dc  FUN_800e00dc ====

void FUN_800e00dc(int param_1)

{
  zz_00f3cb4_(param_1);
  return;
}



// ==== 800e0100  FUN_800e0100 ====

void FUN_800e0100(int param_1)

{
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                           DOUBLE_80438d68) * FLOAT_80438d60);
  (*(code *)(&PTR_FUN_80316b08)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800e0174  FUN_800e0174 ====

void FUN_800e0174(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80316b1c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800e01c4  FUN_800e01c4 ====

void FUN_800e01c4(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80438d70;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if (*(short *)(param_1 + 0x784) < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006e970_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438d74;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,(int)*(char *)(param_1 + 0x543),4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800e0274  FUN_800e0274 ====

void FUN_800e0274(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80438d78;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006e970_(param_1), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800e02e0  FUN_800e02e0 ====

void FUN_800e02e0(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,1);
  zz_006e970_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar2 = zz_006dbe0_(param_1,2,1,0);
    if (iVar2 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      if (*(char *)(param_1 + 0x5db) != '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      cVar1 = *(char *)(param_1 + 0x6ea) + '\x01';
      dVar3 = (double)FLOAT_80438d74;
      *(char *)(param_1 + 0x6ea) = cVar1;
      zz_004beb8_(dVar3,param_1,(int)*(char *)(param_1 + 0x543),4,(int)cVar1,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x543) = 1;
      if (*(char *)(param_1 + 0x5db) == '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 0xf;
      }
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar3 = (double)FLOAT_80438d74;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar3,param_1,(int)*(char *)(param_1 + 0x543),4,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 800e03ec  FUN_800e03ec ====

uint FUN_800e03ec(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  double dVar5;
  
  zz_004cd24_(param_1,1);
  uVar2 = zz_006e970_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    uVar2 = 0;
    if (iVar3 != 0) {
      zz_00f036c_(param_1,0xeb);
      iVar3 = 0;
      do {
        *(undefined1 *)(param_1 + iVar3 + 0x146) = 1;
        bVar4 = zz_00e058c_(param_1,0,(char)iVar3);
        uVar2 = (uint)bVar4;
        iVar3 = iVar3 + 1;
      } while (iVar3 < 4);
    }
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(char *)(param_1 + 0x5db) != '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_80438d74;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    uVar2 = zz_004beb8_(dVar5,param_1,(int)*(char *)(param_1 + 0x543),4,(int)cVar1,0xffffffff,
                        0xffffffff);
  }
  return uVar2;
}



// ==== 800e04f8  FUN_800e04f8 ====

void FUN_800e04f8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = DOUBLE_80438d68;
  uVar1 = (uint)*(short *)(param_9 + 0x18e2);
  dVar2 = (double)(float)((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) - DOUBLE_80438d68);
  *(short *)(param_9 + 0x18e2) = (short)(int)(dVar2 * (double)FLOAT_80438d7c);
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar2,dVar3,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,uVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800e058c  zz_00e058c_ ====

bool zz_00e058c_(int param_1,int param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,1,1);
  if (puVar1 == (undefined1 *)0x0) {
    zz_00e0e68_(param_1,(int)(char)(&DAT_80317065)[param_2 * 0x14]);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = param_3;
    puVar1[0x11] = (char)param_2;
    puVar1[0x10] = 0x29;
    *(code **)(puVar1 + 0xc) = FUN_800e06c4;
    *(code **)(puVar1 + 0x10c) = FUN_800e0e0c;
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



// ==== 800e06c4  FUN_800e06c4 ====

void FUN_800e06c4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_803170b4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e075c  FUN_800e075c ====

/* WARNING: Removing unreachable block (ram,0x800e08b4) */
/* WARNING: Removing unreachable block (ram,0x800e0888) */
/* WARNING: Removing unreachable block (ram,0x800e085c) */

void FUN_800e075c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  float *pfVar6;
  uint uVar7;
  uint uVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  undefined8 uVar10;
  float afStack_78 [12];
  float afStack_48 [4];
  undefined4 auStack_38 [4];
  undefined4 auStack_28 [6];
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  uVar8 = (uint)*(byte *)(param_9 + 0x11);
  iVar9 = *(int *)(param_9 + 0x90);
  iVar4 = *(char *)(param_9 + 0x13) * 0x1c;
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x14;
  uVar2 = *(undefined4 *)(&DAT_80316f00 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80316efc + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80316f04 + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80316f08 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80316f0c + iVar4);
  *(undefined *)(param_9 + 0x89) = (&DAT_80316ef9)[iVar4];
  FUN_80047aa4(param_9);
  *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x118);
  *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x128);
  *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x138);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  uVar7 = (uint)(byte)(&DAT_80316efa)[iVar4];
  *(undefined *)(param_9 + 0x98) = (&DAT_80316efa)[iVar4];
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXCopy_bl((float *)(iVar9 + (char)(&DAT_8031706a)[iVar5] * 0x30 + 0x8d4),afStack_48);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438d80 *
                                     (double)((longlong)(double)*(short *)(&DAT_80316f12 + iVar4) *
                                             0x3ff0000000000000)),afStack_78,0x7a);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_78,afStack_48);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438d80 *
                                     (double)((longlong)(double)*(short *)(&DAT_80316f10 + iVar4) *
                                             0x3ff0000000000000)),afStack_78,0x79);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_78,afStack_48);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80438d80 *
                                     (double)((longlong)(double)*(short *)(&DAT_80316f0e + iVar4) *
                                             0x3ff0000000000000)),afStack_78,0x78);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_78,afStack_48);
  *(float *)(param_9 + 0x38) = afStack_48[(byte)(&DAT_8031706b)[iVar5] & 0x7f];
  *(undefined4 *)(param_9 + 0x3c) = auStack_38[(byte)(&DAT_8031706b)[iVar5] & 0x7f];
  *(undefined4 *)(param_9 + 0x40) = auStack_28[(byte)(&DAT_8031706b)[iVar5] & 0x7f];
  if (((&DAT_8031706b)[iVar5] & 0x80) != 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438d84,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  uVar10 = zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031706c + iVar5);
  *(undefined2 *)(param_9 + 0x152) = *(undefined2 *)(&DAT_80317066 + iVar5);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80317068 + iVar5);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  uVar3 = zz_00055fc_();
  *(ushort *)(param_9 + 0x152) = *(short *)(param_9 + 0x152) + ((ushort)uVar3 & 0x3f);
  *(undefined *)(param_9 + 0x158) = (&DAT_80317065)[iVar5];
  *(undefined2 *)(param_9 + 0x1c) = 0xff;
  iVar9 = zz_0006f98_(iVar9);
  pfVar6 = (float *)(int)(char)(&DAT_80316ef8)[iVar4];
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar9 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)pfVar6,uVar7,uVar8,in_r8,in_r9,in_r10);
  cVar1 = (&DAT_80316efb)[iVar4];
  *(char *)(param_9 + 0x12) = cVar1;
  if ('\0' < cVar1) {
    uVar10 = zz_00086b8_((double)FLOAT_80438d88,param_2,param_3,param_4,param_5,param_6,param_7,
                         param_8,*(int *)(iVar9 + 0x600),*(int *)(param_9 + 0xe0),pfVar6,uVar7,uVar8
                         ,in_r8,in_r9,in_r10);
    zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar6,uVar7,uVar8,in_r8,in_r9,in_r10);
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar4 = zz_008ac80_(param_9,(int)(char)(&DAT_80317064)[iVar5]);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 800e0a30  FUN_800e0a30 ====

void FUN_800e0a30(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  iVar5 = *(int *)(param_9 + 0x90);
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x14;
  if (*(char *)(param_9 + 0x12) != '\0') {
    zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(uint)*(byte *)(param_9 + 0x11),param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  if ((*(char *)(param_9 + 0x11) == '\x03') && (*(char *)(iVar5 + 0x6f7) != '\0')) {
    *(undefined1 *)(iVar5 + 0x6f7) = 0;
    zz_00e0d7c_(param_9);
    zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),(char)*(undefined4 *)(&DAT_80317074 + iVar3))
    ;
  }
  else if (*(char *)(param_9 + 0x1d9) == '\0') {
    iVar5 = zz_0083244_((float *)(param_9 + 0x20));
    if (iVar5 == 0) {
      if (*(short *)(param_9 + 0x1c6) < 1) {
        zz_00e0d7c_(param_9);
        zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),
                    (char)*(undefined4 *)(&DAT_80317074 + iVar3));
      }
      else {
        *(short *)(param_9 + 0x152) = *(short *)(param_9 + 0x152) + -1;
        if (*(short *)(param_9 + 0x152) < 1) {
          zz_00e0d7c_(param_9);
          zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),
                      (char)*(undefined4 *)(&DAT_80317074 + iVar3));
        }
        else {
          local_1c = *(float *)(param_9 + 0x118);
          local_18 = *(undefined4 *)(param_9 + 0x128);
          local_14 = *(undefined4 *)(param_9 + 0x138);
          local_28 = DAT_802b0cb4;
          local_24 = DAT_802b0cb8;
          local_20 = DAT_802b0cbc;
          gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_28);
          dVar6 = gnt4_PSVECMag_bl(&local_28);
          if (dVar6 != (double)FLOAT_80438d88) {
            gnt4_PSQUATScale_bl((double)FLOAT_80438d8c,&local_28,&local_28);
            gnt4_PSVECAdd_bl(&local_28,&local_1c,(float *)(param_9 + 0x9c));
          }
          fVar2 = FLOAT_80438d88;
          cVar1 = *(char *)(param_9 + 0x19);
          if (cVar1 == '\x01') {
            *(short *)(param_9 + 0x150) = *(short *)(param_9 + 0x150) + 0x180;
            dVar6 = zz_0045204_(*(short *)(param_9 + 0x150));
            dVar7 = (double)FLOAT_80438d90;
            *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x144);
            *(float *)(param_9 + 0x24) =
                 (float)(dVar7 * dVar6 + (double)*(float *)(param_9 + 0x148));
            *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x14c);
            if (*(float *)(param_9 + 0x154) < *(float *)(param_9 + 0x148)) {
              *(float *)(param_9 + 0x148) = *(float *)(param_9 + 0x148) - FLOAT_80438d98;
            }
          }
          else if ((cVar1 < '\x01') && (-1 < cVar1)) {
            dVar6 = (double)FLOAT_80438d88;
            *(float *)(param_9 + 0x44) =
                 *(float *)(param_9 + 0x44) + *(float *)(&DAT_80317070 + iVar3);
            if (dVar6 < (double)*(float *)(param_9 + 0x44)) {
              gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                                  &local_28);
              gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
            }
            else {
              *(float *)(param_9 + 0x44) = fVar2;
              *(undefined1 *)(param_9 + 0x19) = 1;
              *(undefined2 *)(param_9 + 0x1c) = 0;
              *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
              *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
              *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
              uVar4 = zz_00055fc_();
              *(ushort *)(param_9 + 0x150) = (ushort)uVar4 & 0xf;
              *(short *)(param_9 + 0x150) = *(short *)(param_9 + 0x150) << 0xc;
              dVar6 = zz_0045204_(*(short *)(param_9 + 0x150));
              dVar7 = (double)FLOAT_80438d90;
              *(float *)(param_9 + 0x148) =
                   -(float)(dVar7 * dVar6 - (double)*(float *)(param_9 + 0x148));
              dVar6 = FUN_8003d964(dVar7,param_9,(float *)(param_9 + 0x20));
              *(float *)(param_9 + 0x154) = (float)dVar6;
              *(float *)(param_9 + 0x154) = *(float *)(param_9 + 0x154) + FLOAT_80438d94;
            }
          }
          zz_00833ec_(param_9);
          zz_0083524_(param_9);
          iVar5 = zz_0083714_(param_9);
          if (iVar5 == 0) {
            iVar5 = zz_0084170_(param_9);
            if (iVar5 != 0) {
              zz_00e0d7c_(param_9);
              zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),
                          (char)*(undefined4 *)(&DAT_80317074 + iVar3));
            }
          }
          else {
            zz_00e0d7c_(param_9);
          }
        }
      }
    }
    else {
      zz_00e0d7c_(param_9);
    }
  }
  else {
    zz_00e0d7c_(param_9);
    zz_0085e00_(param_9,(undefined4 *)(param_9 + 0x20),(char)*(undefined4 *)(&DAT_80317074 + iVar3))
    ;
  }
  return;
}



// ==== 800e0d7c  zz_00e0d7c_ ====

void zz_00e0d7c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800e0db8  FUN_800e0db8 ====

void FUN_800e0db8(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_00e0e68_(*(int *)(param_1 + 0x90),(int)*(char *)(param_1 + 0x158));
  return;
}



// ==== 800e0dec  FUN_800e0dec ====

void FUN_800e0dec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e0e0c  FUN_800e0e0c ====

void FUN_800e0e0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800e0e68  zz_00e0e68_ ====

void zz_00e0e68_(int param_1,int param_2)

{
  if (-1 < param_2) {
    zz_006de10_(param_1,param_2);
  }
  return;
}



// ==== 800e0e90  zz_00e0e90_ ====

bool zz_00e0e90_(int param_1,undefined1 param_2,undefined1 param_3,undefined1 *param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    zz_00e199c_(param_1,param_4);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = param_3;
    puVar1[0x10] = 0x28;
    *(code **)(puVar1 + 0xc) = FUN_800e0fc4;
    *(code **)(puVar1 + 0x10c) = FUN_800e1940;
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
    *(undefined1 **)(puVar1 + 0x170) = param_4;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800e0fc4  FUN_800e0fc4 ====

void FUN_800e0fc4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80317234)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e105c  FUN_800e105c ====

void FUN_800e105c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  double dVar9;
  double dVar10;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  uVar2 = DAT_802b0cb8;
  iVar5 = *(char *)(param_9 + 0x13) * 0x24;
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 == '\x03') {
    *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
    uVar3 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0xa0) = uVar2;
    *(undefined4 *)(param_9 + 0xa4) = uVar3;
    *(undefined1 *)(param_9 + 0x98) = 2;
  }
  else if ((cVar1 < '\x03') && ('\x01' < cVar1)) {
    *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
    uVar3 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0xa0) = uVar2;
    *(undefined4 *)(param_9 + 0xa4) = uVar3;
    *(undefined1 *)(param_9 + 0x98) = 5;
  }
  else {
    *(undefined4 *)(param_9 + 0x9c) =
         *(undefined4 *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8d8);
    *(undefined4 *)(param_9 + 0xa0) =
         *(undefined4 *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8e8);
    *(undefined4 *)(param_9 + 0xa4) =
         *(undefined4 *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8f8);
    *(undefined1 *)(param_9 + 0x98) = 5;
  }
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fce8f34),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8e4);
  iVar7 = iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar7 + 0x8f4);
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  if (*(char *)(param_9 + 0x13) < '\x02') {
    gnt4_PSQUATScale_bl(-(double)*(float *)(&DAT_803171d4 + iVar6),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  else {
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_803171d4 + iVar6),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  zz_0083d60_(param_9,iVar8,(int)(char)(&DAT_803170cb)[iVar5]);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_803171d4 + iVar6),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  dVar9 = (double)FLOAT_80438da0;
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_803171d4 + iVar6);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803171c8 + iVar6);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_803171ca + iVar6);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  dVar10 = (double)*(float *)(iVar8 + 0x204);
  *(float *)(param_9 + 0x204) = (float)(dVar10 * dVar9);
  *(undefined4 *)(param_9 + 0x16c) = *(undefined4 *)(&DAT_803171d8 + iVar6);
  iVar4 = zz_0006f98_(iVar8);
  zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_803170c8 + iVar5),iVar7,in_r7,in_r8,
              in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar6 = zz_008ac80_(param_9,(int)*(short *)(&DAT_803171c4 + iVar6));
  if (iVar6 == 0) {
    zz_00e199c_(iVar8,*(undefined1 **)(param_9 + 0x170));
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar8 + (char)(&DAT_803170ca)[iVar5] * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fce8f28),(float *)(param_9 + 0x144));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x150))
    ;
    zz_00a2bf8_(iVar8,param_9,(undefined4 *)(param_9 + 0x144),(float *)(param_9 + 0x150),1,0);
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  return;
}



// ==== 800e1388  FUN_800e1388 ====

void FUN_800e1388(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_00e1604_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_00e13d0_(param_1);
  }
  return;
}



// ==== 800e13d0  zz_00e13d0_ ====

void zz_00e13d0_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float afStack_28 [5];
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x24;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00e17e0_(param_1);
        *(undefined2 *)(param_1 + 0x1c) = 4;
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x16c)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_803171dc + iVar3);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x16c);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_803171d0 + iVar3),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_803171cc + iVar3),param_1,
                     (char)*(undefined2 *)(&DAT_803171c8 + iVar3));
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x16c));
        iVar3 = zz_0083714_(param_1);
        if (iVar3 == 0) {
          iVar3 = zz_0084170_(param_1);
          if (iVar3 == 0) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(iVar4 + (char)(&DAT_803170ca)[iVar2] * 0x30 + 0x8d4),
                       (float *)(iVar2 + -0x7fce8f28),(float *)(param_1 + 0x144));
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),afStack_28);
            dVar5 = gnt4_PSVECMag_bl(afStack_28);
            if ((double)FLOAT_80438da4 <= dVar5) {
              gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_80438da4 / dVar5),afStack_28,
                                  afStack_28);
              gnt4_PSVECAdd_bl((float *)(param_1 + 0x144),afStack_28,(float *)(param_1 + 0x20));
              *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x20);
              *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
              *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
              zz_00e17e0_(param_1);
            }
          }
          else {
            zz_00e17e0_(param_1);
            *(undefined2 *)(param_1 + 0x1c) = 4;
          }
        }
        else {
          zz_00e17e0_(param_1);
        }
      }
    }
    else {
      zz_00e17e0_(param_1);
    }
  }
  else {
    zz_00e17e0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 4;
  }
  return;
}



// ==== 800e1604  zz_00e1604_ ====

void zz_00e1604_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float afStack_28 [7];
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + (char)(&DAT_803170ca)[iVar1] * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fce8f34),afStack_28);
  dVar6 = gnt4_PSVECSquareDistance_bl(afStack_28,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80438da8 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80438db0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438db8);
    dVar7 = DOUBLE_80438db0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438db8);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80438db0 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80438db8));
  }
  if ((double)*(float *)(param_1 + 0x44) < dVar6) {
    if (*(short *)(param_1 + 0x1c) < 1) {
      uVar4 = *(undefined4 *)(param_1 + 0x38);
      uVar3 = *(undefined4 *)(param_1 + 0x3c);
      uVar2 = *(undefined4 *)(param_1 + 0x40);
      dVar6 = (double)FLOAT_80438dc0;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x15c);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x160);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x164);
      zz_006c440_(dVar6,param_1,afStack_28);
      *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x38);
      *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x40);
      *(undefined4 *)(param_1 + 0x38) = uVar4;
      *(undefined4 *)(param_1 + 0x3c) = uVar3;
      *(undefined4 *)(param_1 + 0x40) = uVar2;
    }
    else {
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    }
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + (char)(&DAT_803170ca)[iVar1] * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fce8f28),(float *)(param_1 + 0x144));
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    zz_00e199c_(iVar5,*(undefined1 **)(param_1 + 0x170));
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_00f036c_(param_1,0xdc);
  }
  return;
}



// ==== 800e17e0  zz_00e17e0_ ====

void zz_00e17e0_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  double dVar6;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [4];
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar4 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_803170ca)[iVar4] * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fce8f34),afStack_1c);
  gnt4_PSVECSubtract_bl(afStack_1c,(float *)(param_1 + 0x20),&local_28);
  dVar6 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar2 = DAT_802b0cac;
  if (dVar6 <= (double)FLOAT_80438da8) {
    *(undefined4 *)(param_1 + 0x15c) = DAT_802b0ca8;
    uVar3 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x160) = uVar2;
    *(undefined4 *)(param_1 + 0x164) = uVar3;
  }
  else {
    *(float *)(param_1 + 0x15c) = local_28;
    *(undefined4 *)(param_1 + 0x160) = local_24;
    *(undefined4 *)(param_1 + 0x164) = local_20;
  }
  pfVar5 = (float *)(param_1 + 0x15c);
  gnt4_PSVECNormalize_bl(pfVar5,pfVar5);
  if (*(float *)(&DAT_803171d8 + (uint)bVar1 * 0x1c) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_803171d8 + (uint)bVar1 * 0x1c);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar5,pfVar5);
  *(undefined1 *)(param_1 + 0x19) = 1;
  zz_008aff0_(param_1);
  return;
}



// ==== 800e1914  FUN_800e1914 ====

void FUN_800e1914(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800e1920  FUN_800e1920 ====

void FUN_800e1920(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e1940  FUN_800e1940 ====

void FUN_800e1940(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800e199c  zz_00e199c_ ====

void zz_00e199c_(undefined4 param_1,undefined1 *param_2)

{
  *param_2 = 0;
  return;
}



// ==== 800e19a8  zz_00e19a8_ ====

void zz_00e19a8_(int param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,6);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x20;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800e1ab4;
    *(code **)(puVar1 + 0x10c) = FUN_800e21f4;
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
    *(undefined4 *)(puVar1 + 0x154) = param_3;
  }
  return;
}



// ==== 800e1ab4  FUN_800e1ab4 ====

void FUN_800e1ab4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(undefined1 *)(param_1 + 0x158) = 0;
  (*(code *)(&PTR_FUN_80317698)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e1b64  FUN_800e1b64 ====

void FUN_800e1b64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  fVar1 = FLOAT_80438dc8;
  iVar5 = *(int *)(param_9 + 0x90);
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(float *)(param_9 + 0xd8) = fVar1;
  *(float *)(param_9 + 0x148) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xc0) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined *)(param_9 + 0x89) = (&DAT_8031724a)[iVar4];
  uVar2 = *(undefined4 *)(&DAT_80317258 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80317254 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031725c + iVar4);
  *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_80317260 + iVar4);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_80317262 + iVar4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_80317250 + iVar4);
  *(undefined2 *)(param_9 + 0x14c) = *(undefined2 *)(&DAT_80317248 + iVar4);
  *(ushort *)(param_9 + 0x14e) = *(ushort *)(&DAT_8031724c + iVar4) & 0x8000;
  *(ushort *)(param_9 + 0x150) = *(ushort *)(&DAT_8031724c + iVar4) & 0x7fff;
  *(undefined2 *)(param_9 + 0x152) = *(undefined2 *)(&DAT_8031724e + iVar4);
  *(undefined *)(param_9 + 0x159) = (&DAT_8031724b)[iVar4];
  if (*(short *)(param_9 + 0x152) < 0) {
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(400);
    *(int **)(param_9 + 0xdc) = piVar3;
  }
  zz_00e245c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  *(code **)(param_9 + 0x100) = FUN_800e2298;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  iVar4 = DAT_803bb374;
  if (*(short *)(param_9 + 0x14e) == 0) {
    iVar4 = zz_0006f78_(iVar5);
  }
  zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              *(int *)(param_9 + 0xf4),(float *)(int)*(short *)(param_9 + 0x150),
              (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  return;
}



// ==== 800e1cd8  FUN_800e1cd8 ====

void FUN_800e1cd8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  short sVar6;
  bool bVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined8 uVar11;
  double dVar12;
  double dVar13;
  float local_98;
  undefined4 local_94;
  undefined4 local_90;
  float local_8c;
  float local_88;
  float local_84;
  float afStack_80 [12];
  float fStack_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_3c;
  float local_38;
  undefined4 local_34;
  float local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  uint uStack_1c;
  
  iVar10 = *(int *)(param_9 + 0x90);
  iVar9 = *(int *)(param_9 + 0x8c);
  if (*(char *)(param_9 + 0x159) == '\0') {
    uVar11 = zz_00f0104_(iVar10,0xe,2);
  }
  else {
    uVar11 = zz_00f0104_(iVar10,0x23,2);
  }
  sVar6 = *(short *)(param_9 + 0x1c) + 1;
  iVar8 = (int)sVar6;
  *(short *)(param_9 + 0x1c) = sVar6;
  iVar5 = iVar8 / 5 + (iVar8 >> 0x1f);
  if (iVar8 == (iVar5 - (iVar5 >> 0x1f)) * 5) {
    zz_00e245c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (**(char **)(param_9 + 0x154) < '\x01') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(param_9 + 0x148);
    zz_008aff0_(param_9);
  }
  else {
    local_20 = 0x43300000;
    uStack_1c = (int)*(short *)(param_9 + 0x1c) ^ 0x80000000;
    fVar3 = ((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80438de8) / FLOAT_80438dcc) *
            *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x148) = fVar3;
    if (*(float *)(param_9 + 0x144) <= fVar3) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x144);
    }
    uVar2 = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x60) = uVar2;
    *(undefined4 *)(param_9 + 0x5c) = uVar2;
    *(undefined4 *)(param_9 + 0x58) = uVar2;
    fVar3 = *(float *)(iVar10 + 0xb4) * *(float *)(param_9 + 0x148);
    *(float *)(param_9 + 0xb4) = fVar3;
    *(float *)(param_9 + 0xc0) = fVar3;
    if (*(char *)(param_9 + 0x89) < '\0') {
      zz_00455fc_((float *)(iVar9 + 0x114),&fStack_50,(float *)(param_9 + 100));
    }
    else {
      zz_00455fc_((float *)(iVar10 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),&fStack_50,
                  (float *)(param_9 + 100));
    }
    if (*(short *)(param_9 + 0x70) != 0) {
      uStack_1c = (int)*(short *)(param_9 + 0x70) ^ 0x80000000;
      local_20 = 0x43300000;
      gnt4_PSMTXRotRad_bl((double)(FLOAT_80438dd0 *
                                  (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80438de8))
                          ,afStack_80,0x78);
      gnt4_PSMTXConcat_bl(&fStack_50,afStack_80,&fStack_50);
    }
    if (*(short *)(param_9 + 0x72) != 0) {
      uStack_1c = (int)*(short *)(param_9 + 0x72) ^ 0x80000000;
      local_20 = 0x43300000;
      gnt4_PSMTXRotRad_bl((double)(FLOAT_80438dd0 *
                                  (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80438de8))
                          ,afStack_80,0x79);
      gnt4_PSMTXConcat_bl(&fStack_50,afStack_80,&fStack_50);
    }
    if (*(int *)(param_9 + 200) != 0) {
      bVar1 = *(byte *)(param_9 + 0x11);
      local_98 = local_44;
      local_94 = local_34;
      local_90 = local_24;
      gnt4_PSVECSubtract_bl((float *)(*(int *)(param_9 + 200) + 100),&local_98,&local_98);
      local_8c = local_48;
      local_88 = local_38;
      local_84 = local_28;
      zz_006ec1c_(&local_98,&local_98);
      zz_006ec1c_(&local_8c,&local_8c);
      dVar12 = gnt4_PSQUATDotProduct_bl(&local_98,&local_8c);
      dVar13 = (double)FLOAT_80438dd4;
      if ((dVar12 <= dVar13) && (dVar13 = dVar12, dVar12 < (double)FLOAT_80438dd8)) {
        dVar13 = (double)FLOAT_80438dd8;
      }
      if ((double)*(float *)(&DAT_80317264 + (uint)bVar1 * 0x20) < dVar13) {
        local_8c = local_4c;
        local_88 = local_3c;
        local_84 = local_2c;
        bVar7 = zz_0045ef4_(afStack_80,5,&local_98,&local_8c);
        if (!bVar7) {
          gnt4_PSMTXCopy_bl(afStack_80,&fStack_50);
          if (*(char *)(param_9 + 0x89) < '\0') {
            gnt4_PSMTXMultVec_bl((float *)(iVar9 + 0x114),(float *)(param_9 + 100),&local_98);
          }
          else {
            gnt4_PSMTXMultVec_bl
                      ((float *)(iVar10 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
                       (float *)(param_9 + 100),&local_98);
          }
          local_44 = local_98;
          local_34 = local_94;
          local_24 = local_90;
        }
      }
    }
    gnt4_PSMTXCopy_bl(&fStack_50,(float *)(param_9 + 0x114));
    dVar13 = (double)*(float *)(param_9 + 0x148);
    gnt4_PSMTXScale_bl(dVar13,dVar13,dVar13,afStack_80);
    gnt4_PSMTXConcat_bl(&fStack_50,afStack_80,&fStack_50);
    local_88 = FLOAT_80438dc8;
    local_8c = FLOAT_80438dc8;
    local_84 = FLOAT_80438ddc;
    gnt4_PSMTXMultVec_bl(&fStack_50,&local_8c,(float *)(param_9 + 0x38));
    local_84 = local_84 + FLOAT_80438de0;
    gnt4_PSMTXMultVec_bl(&fStack_50,&local_8c,(float *)(param_9 + 0x9c));
    fVar4 = FLOAT_80438dc8;
    fVar3 = *(float *)(param_9 + 0xd8) - *(float *)(iVar10 + 0x1dc8);
    *(float *)(param_9 + 0xd8) = fVar3;
    if (fVar3 <= fVar4) {
      *(float *)(param_9 + 0xd8) = FLOAT_80438dd4;
      zz_0139a6c_(param_9,param_9 + 0x38,param_9 + 0x9c,(char)*(undefined2 *)(param_9 + 0x14c));
    }
    *(undefined1 *)(param_9 + 0x158) = 1;
  }
  zz_00e255c_(param_9);
  return;
}



// ==== 800e211c  FUN_800e211c ====

void FUN_800e211c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  dVar3 = DOUBLE_80438de8;
  fVar1 = FLOAT_80438ddc;
  fVar2 = FLOAT_80438dc8;
  *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
  fVar1 = -(((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                    dVar3) / fVar1) * *(float *)(param_1 + 0x144) - *(float *)(param_1 + 0xc0));
  *(float *)(param_1 + 0x148) = fVar1;
  if (fVar1 <= fVar2) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x148);
  zz_00e255c_(param_1);
  return;
}



// ==== 800e21ac  FUN_800e21ac ====

void FUN_800e21ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e21f4  FUN_800e21f4 ====

void FUN_800e21f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar1 = 0;
    iVar3 = 0;
    iVar2 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar1) != 0) {
        zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar2 + 0xe0),
                    (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar3),param_11,param_12,
                    param_13,param_14,param_15,param_16);
        param_1 = zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 4;
      iVar3 = iVar3 + 0x50;
    } while (iVar1 < 5);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xf4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xf4),0x44);
  return;
}



// ==== 800e2298  FUN_800e2298 ====

void FUN_800e2298(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [13];
  undefined4 local_28;
  uint uStack_24;
  
  if (*(char *)(param_1 + 0x89) < '\0') {
    zz_00455fc_((float *)(*(int *)(param_1 + 0x8c) + 0x114),(float *)(param_1 + 0x114),
                (float *)(param_1 + 100));
  }
  else {
    zz_00455fc_((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                (float *)(param_1 + 0x114),(float *)(param_1 + 100));
  }
  if (*(short *)(param_1 + 0x70) != 0) {
    uStack_24 = (int)*(short *)(param_1 + 0x70) ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80438dd0 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80438de8)),
                        afStack_5c,0x78);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_5c,(float *)(param_1 + 0x114));
  }
  if (*(short *)(param_1 + 0x72) != 0) {
    uStack_24 = (int)*(short *)(param_1 + 0x72) ^ 0x80000000;
    local_28 = 0x43300000;
    gnt4_PSMTXRotRad_bl((double)(FLOAT_80438dd0 *
                                (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80438de8)),
                        afStack_5c,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_5c,(float *)(param_1 + 0x114));
  }
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar2 = 0;
    iVar3 = 0;
    do {
      if (((int)*(char *)(param_1 + 0x13) & 1 << iVar2) != 0) {
        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        zz_00457d4_('z',(float *)(param_1 + 0x114),pfVar1,*(short *)(pfVar1 + 0x12));
        zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0xe);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x50;
    } while (iVar2 < 5);
  }
  dVar4 = (double)*(float *)(param_1 + 0x148);
  gnt4_PSMTXScale_bl(dVar4,dVar4,dVar4,afStack_5c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_5c,(float *)(param_1 + 0x114));
  local_68 = *(float *)(&DAT_80433bc0 + ((int)*(short *)(param_1 + 0x1c) & 1U) * 4);
  local_60 = FLOAT_80438dd4;
  local_64 = local_68;
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),&local_68);
  return;
}



// ==== 800e245c  zz_00e245c_ ====

void zz_00e245c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    for (iVar4 = 0; iVar4 < 5; iVar4 = iVar4 + 1) {
      if (((int)(char)*(byte *)(param_9 + 0x13) & 1 << iVar4) == 0) {
        iVar3 = *(int *)(param_9 + 0x90);
        iVar2 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) | (byte)(1 << iVar4);
        iVar2 = iVar2 + iVar4 * 0x50;
        *(undefined2 *)(iVar2 + 0x44) = 0;
        *(undefined2 *)(iVar2 + 0x46) = 0x14;
        uVar1 = zz_00055fc_();
        *(short *)(iVar2 + 0x48) = (short)(uVar1 << 8);
        uVar5 = zz_0018f88_((int *)(iVar2 + 0x30),
                            (int)(&PTR_DAT_80317648)[*(char *)(param_9 + 0x11)],
                            (float *)(iVar2 + 0x38));
        iVar2 = DAT_803bb374;
        if (*(short *)(param_9 + 0x14e) == 0) {
          iVar2 = zz_0006f78_(iVar3);
        }
        zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                    *(int *)(param_9 + iVar4 * 4 + 0xe0),(float *)(int)*(short *)(param_9 + 0x152),
                    (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
        iVar4 = 5;
      }
    }
  }
  return;
}



// ==== 800e255c  zz_00e255c_ ====

void zz_00e255c_(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar3 = 0;
    iVar4 = 0;
    do {
      if (((int)*(char *)(param_1 + 0x13) & 1 << iVar3) != 0) {
        iVar2 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar4;
        sVar1 = *(short *)(iVar2 + 0x44) + 1;
        *(short *)(iVar2 + 0x44) = sVar1;
        if (*(short *)(iVar2 + 0x46) <= sVar1) {
          *(byte *)(param_1 + 0x13) = *(byte *)(param_1 + 0x13) & ~(byte)(1 << iVar3);
        }
        zz_0018fd8_((int *)(iVar2 + 0x30),(int)*(short *)(iVar2 + 0x44),(float *)(iVar2 + 0x38));
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x50;
    } while (iVar3 < 5);
  }
  return;
}



// ==== 800e2614  zz_00e2614_ ====

bool zz_00e2614_(int param_1)

{
  bool bVar2;
  undefined1 *puVar1;
  int iVar3;
  
  if (*(short *)(param_1 + 1000) == 4) {
    iVar3 = 0;
    do {
      puVar1 = zz_0088aa0_(param_1,2,0,0,2);
      bVar2 = puVar1 != (undefined1 *)0x0;
      if (bVar2) {
        *puVar1 = 1;
        puVar1[0x13] = (char)iVar3;
        puVar1[0x11] = 0;
        *(code **)(puVar1 + 0xc) = FUN_800e2740;
        *(code **)(puVar1 + 0x10c) = FUN_800e2910;
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
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 800e2740  FUN_800e2740 ====

void FUN_800e2740(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803176d8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e2794  FUN_800e2794 ====

void FUN_800e2794(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x84) = 0x43;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80438df0;
  *(float *)(param_9 + 0xb4) = FLOAT_80438df0;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_803176b0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803176ac + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803176b4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803176b8 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803176bc + iVar3);
  *(undefined *)(param_9 + 0x89) = (&DAT_803176a9)[iVar3];
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_803176a8)[iVar3],iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)(char)(&DAT_803176a8)[iVar3];
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438df4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00e28c4_(param_9);
  return;
}



// ==== 800e28c4  zz_00e28c4_ ====

void zz_00e28c4_(int param_1)

{
  if ((*(uint *)(*(int *)(param_1 + 0x90) + 0x5e0) & 0x20000000) != 0) {
    return;
  }
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x500;
  return;
}



// ==== 800e28f0  FUN_800e28f0 ====

void FUN_800e28f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e2910  FUN_800e2910 ====

void FUN_800e2910(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800e2990  zz_00e2990_ ====

void zz_00e2990_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x203) || (*(short *)(param_1 + 1000) == 0x20c)) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800e2aa0;
    *(code **)(puVar1 + 0x10c) = FUN_800e2d1c;
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



// ==== 800e2aa0  FUN_800e2aa0 ====

void FUN_800e2aa0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80317718)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e2af4  FUN_800e2af4 ====

void FUN_800e2af4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  uVar6 = (uint)*(byte *)(param_9 + 0x11);
  iVar7 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar3 = (char)*(byte *)(param_9 + 0x11) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80438df8;
  *(undefined1 *)(param_9 + 0x84) = 0x59;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_803176ea + iVar3);
  uVar2 = *(undefined4 *)(&DAT_803176f8 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803176f4 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803176fc + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803176ee + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803176f2 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar7 = zz_0006f98_(iVar7);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_803176e8 + iVar3),iVar7 + 0xc28,uVar6,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar7 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_803176e8 + iVar3);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,uVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438dfc,*(int *)(param_9 + 0xe4));
  iVar7 = zz_008ac80_(param_9,(int)*(short *)(&DAT_803176ec + iVar3));
  if (iVar7 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
    *(undefined2 *)(param_9 + 0x1c6) = 10000;
    *(undefined2 *)(param_9 + 0x1c8) = 10000;
    *(undefined2 *)(param_9 + 0x1c4) = 10000;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 2;
    zz_00e2c64_(param_9);
  }
  return;
}



// ==== 800e2c64  zz_00e2c64_ ====

void zz_00e2c64_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0) ||
     ((*(uint *)(iVar1 + 0x5e0) & 0x10000000) != 0)) {
    *(undefined2 *)(param_1 + 0x272) = *(undefined2 *)(iVar1 + 0x272);
  }
  else {
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
  }
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar1 + 0xc0);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  if ((*(byte *)(iVar1 + 0x6e9) & 8) == 0) {
    *(float *)(param_1 + 0x58) = FLOAT_80438df8;
  }
  else {
    *(float *)(param_1 + 0x58) = FLOAT_80438e00;
  }
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  return;
}



// ==== 800e2cd0  FUN_800e2cd0 ====

void FUN_800e2cd0(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 800e2cfc  FUN_800e2cfc ====

void FUN_800e2cfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e2d1c  FUN_800e2d1c ====

void FUN_800e2d1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((double)FLOAT_80438e00 < (double)*(float *)(param_9 + 0x58)) {
    if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
      iVar1 = *(int *)(param_9 + 0xe0);
      if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
        uVar2 = 0x44;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_((double)*(float *)(param_9 + 0x58),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,iVar1,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 800e2db0  zz_00e2db0_ ====

void zz_00e2db0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x203) || (*(short *)(param_1 + 1000) == 0x20c)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,8), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800e2ec0;
    *(code **)(puVar1 + 0x10c) = FUN_800e3274;
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



// ==== 800e2ec0  FUN_800e2ec0 ====

void FUN_800e2ec0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80317758)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e2f14  FUN_800e2f14 ====

void FUN_800e2f14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  
  uVar7 = (uint)*(byte *)(param_9 + 0x11);
  iVar8 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = (char)*(byte *)(param_9 + 0x11) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar8 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80438e08;
  dVar9 = (double)FLOAT_80438e08;
  *(undefined1 *)(param_9 + 0x84) = 0x59;
  fVar2 = FLOAT_80438e0c;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031772a + iVar4);
  uVar3 = *(undefined4 *)(&DAT_80317738 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80317734 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031773c + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031772c + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80317730 + iVar4);
  *(float *)(param_9 + 0xd4) = fVar2;
  iVar8 = zz_0006f98_(iVar8);
  uVar10 = zz_0007030_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe0),
                       (int)(char)(&DAT_80317728)[iVar4],iVar8 + 0xc28,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe8),
                       (int)(char)(&DAT_80317729)[iVar4],iVar8 + 0xc28,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xf0),
                       (int)(char)(&DAT_80317729)[iVar4],iVar8 + 0xc28,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xf8),
                       (int)(char)(&DAT_80317729)[iVar4],iVar8 + 0xc28,uVar7,in_r8,in_r9,in_r10);
  iVar6 = iVar8 + 0xc28;
  iVar5 = (int)(char)(&DAT_80317728)[iVar4];
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar6,uVar7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),extraout_r4,iVar5,iVar6,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_80438e10,*(int *)(param_9 + 0xe4));
  iVar6 = iVar8 + 0xc28;
  iVar5 = (int)(char)(&DAT_80317729)[iVar4];
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xec),iVar5,iVar6,uVar7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xec),extraout_r4_00,iVar5,iVar6,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_80438e0c,*(int *)(param_9 + 0xec));
  iVar6 = iVar8 + 0xc28;
  iVar5 = (int)(char)(&DAT_80317729)[iVar4];
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xf4),iVar5,iVar6,uVar7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xf4),extraout_r4_01,iVar5,iVar6,uVar7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_80438e0c,*(int *)(param_9 + 0xf4));
  iVar5 = iVar8 + 0xc28;
  iVar4 = (int)(char)(&DAT_80317729)[iVar4];
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xfc),iVar4,iVar5,uVar7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xfc),extraout_r4_02,iVar4,iVar5,uVar7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438e0c,*(int *)(param_9 + 0xfc));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_800e311c(param_9);
  return;
}



// ==== 800e311c  FUN_800e311c ====

/* WARNING: Removing unreachable block (ram,0x800e3228) */
/* WARNING: Removing unreachable block (ram,0x800e312c) */

void FUN_800e311c(int param_1)

{
  int iVar1;
  double dVar2;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (((*(uint *)(iVar1 + 0x5e0) & 0x20000000) == 0) && ((*(byte *)(iVar1 + 0x6e9) & 1) != 0)) {
    *(short *)(param_1 + 0x74) =
         (short)(int)(FLOAT_80438e14 * *(float *)(iVar1 + 0x1dc8) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x74) ^ 0x80000000) -
                            DOUBLE_80438e20));
  }
  if ((*(byte *)(iVar1 + 0x6e9) & 8) == 0) {
    *(float *)(param_1 + 0x58) = FLOAT_80438e08;
  }
  else {
    *(float *)(param_1 + 0x58) = FLOAT_80438e18;
  }
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  if ((*(byte *)(iVar1 + 0x6e9) & 6) != 0) {
    if ((*(byte *)(iVar1 + 0x6e9) & 0x20) == 0) {
      dVar2 = (double)(*(float *)(param_1 + 0xd4) - FLOAT_80438e1c);
      if (dVar2 < (double)FLOAT_80438e18) {
        dVar2 = (double)FLOAT_80438e18;
      }
      *(float *)(param_1 + 0xd4) = (float)dVar2;
    }
    else {
      dVar2 = (double)FLOAT_80438e0c;
      *(float *)(param_1 + 0xd4) = FLOAT_80438e0c;
    }
    zz_0007cac_(dVar2,*(int *)(param_1 + 0xec));
    zz_0007cac_(dVar2,*(int *)(param_1 + 0xf4));
    zz_0007cac_(dVar2,*(int *)(param_1 + 0xfc));
  }
  return;
}



// ==== 800e3254  FUN_800e3254 ====

void FUN_800e3254(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e3274  FUN_800e3274 ====

/* WARNING: Removing unreachable block (ram,0x800e33ec) */
/* WARNING: Removing unreachable block (ram,0x800e33e4) */
/* WARNING: Removing unreachable block (ram,0x800e33dc) */
/* WARNING: Removing unreachable block (ram,0x800e33d4) */
/* WARNING: Removing unreachable block (ram,0x800e329c) */
/* WARNING: Removing unreachable block (ram,0x800e3294) */
/* WARNING: Removing unreachable block (ram,0x800e328c) */
/* WARNING: Removing unreachable block (ram,0x800e3284) */

void FUN_800e3274(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float afStack_88 [3];
  undefined4 local_7c;
  undefined4 local_6c;
  undefined4 local_5c;
  
  iVar6 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar6 + 0x144) == '\0') {
    if ((*(char *)(iVar6 + 0xae) == '\0') && (*(char *)(iVar6 + 0x3ec) != '\x04')) {
      iVar1 = 0;
      uVar3 = 1;
    }
    else {
      iVar1 = 1;
      uVar3 = 0x44;
    }
    iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar3);
    if ((*(byte *)(iVar6 + 0x6e9) & 6) != 0) {
      dVar8 = (double)FLOAT_80438e28;
      iVar5 = 0;
      dVar9 = (double)FLOAT_80438e2c;
      iVar1 = 0;
      dVar11 = (double)FLOAT_80438e34;
      dVar10 = dVar8;
      do {
        gnt4_PSMTXRotRad_bl((double)(float)(dVar9 * dVar8),afStack_88,0x79);
        uVar7 = gnt4_PSMTXConcat_bl(afStack_88,
                                    (float *)(iVar6 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
                                    afStack_88);
        iVar2 = *(char *)(param_9 + 0x89) * 0x30;
        local_7c = *(undefined4 *)(iVar6 + iVar2 + 0x8e0);
        local_6c = *(undefined4 *)((undefined *)(iVar2 + 0x8f0) + iVar6);
        local_5c = *(undefined4 *)(iVar6 + iVar2 + 0x900);
        iVar4 = *(int *)(param_9 + iVar5 + 0xec);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_88,
                    (undefined *)(iVar2 + 0x8f0),iVar2,param_13,param_14,param_15,param_16);
        zz_00097b4_(iVar4,0x44);
        dVar8 = (double)(float)(dVar8 + dVar10);
        if (dVar11 <= dVar8) {
          dVar8 = (double)(float)(dVar8 - (double)FLOAT_80438e30);
        }
        iVar1 = iVar1 + 1;
        iVar5 = iVar5 + 8;
      } while (iVar1 < 3);
    }
  }
  return;
}



// ==== 800e3408  zz_00e3408_ ====

void zz_00e3408_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0xa04) || (sVar1 == 0xa08)) || (sVar1 == 0xa09)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_800e3520;
    *(code **)(puVar2 + 0x10c) = FUN_800e36d4;
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



// ==== 800e3520  FUN_800e3520 ====

void FUN_800e3520(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803177b0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e3574  FUN_800e3574 ====

void FUN_800e3574(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  fVar1 = FLOAT_80438e38;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031776a + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80317770 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031776c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80317774 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80317778 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031777c + iVar3);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80317768 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80317768 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438e3c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00e36a0_();
  return;
}



// ==== 800e36a0  zz_00e36a0_ ====

void zz_00e36a0_(void)

{
  return;
}



// ==== 800e36b4  FUN_800e36b4 ====

void FUN_800e36b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e36d4  FUN_800e36d4 ====

void FUN_800e36d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x15c) != '\x02') {
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
  return;
}



// ==== 800e3758  zz_00e3758_ ====

void zz_00e3758_(int param_1,int param_2,uint param_3,undefined4 *param_4,float *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  fVar4 = FLOAT_80438e40;
  if (0 < (int)param_3) {
    uVar6 = param_3 >> 1;
    if (uVar6 != 0) {
      do {
        iVar5 = *(char *)(param_2 + 0x2c) * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[1] = uVar2;
        param_4[2] = uVar3;
        param_5[2] = fVar4;
        param_5[1] = fVar4;
        *param_5 = fVar4;
        pcVar1 = (char *)(param_2 + 0x5c);
        param_2 = param_2 + 0x60;
        iVar5 = *pcVar1 * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        param_4[3] = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[4] = uVar2;
        param_4[5] = uVar3;
        param_4 = param_4 + 6;
        param_5[5] = fVar4;
        param_5[4] = fVar4;
        param_5[3] = fVar4;
        param_5 = param_5 + 6;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      param_3 = param_3 & 1;
      if (param_3 == 0) {
        return;
      }
    }
    do {
      pcVar1 = (char *)(param_2 + 0x2c);
      param_2 = param_2 + 0x30;
      iVar5 = *pcVar1 * 0x30;
      uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
      uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
      *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
      param_4[1] = uVar2;
      param_4[2] = uVar3;
      param_4 = param_4 + 3;
      param_5[2] = fVar4;
      param_5[1] = fVar4;
      *param_5 = fVar4;
      param_5 = param_5 + 3;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  return;
}



// ==== 800e38a4  zz_00e38a4_ ====

/* WARNING: Removing unreachable block (ram,0x800e3c84) */
/* WARNING: Removing unreachable block (ram,0x800e3c7c) */
/* WARNING: Removing unreachable block (ram,0x800e38bc) */
/* WARNING: Removing unreachable block (ram,0x800e38b4) */

void zz_00e38a4_(int param_1,float *param_2,uint param_3,float *param_4,float *param_5)

{
  uint uVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_88 [3];
  float afStack_7c [3];
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  
  uVar1 = zz_00e5230_(param_1);
  if (uVar1 == 0) {
    dVar8 = (double)*(float *)(param_1 + 0xb4);
    if ((double)FLOAT_80438e44 <= dVar8) {
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),
                 (float *)(param_1 + *(char *)(param_2 + 0xb) * 0xc + 0x12d4),local_88);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_7c);
      gnt4_PSQUATScale_bl((double)FLOAT_80438e48,afStack_7c,afStack_7c);
      dVar7 = (double)FLOAT_80438e4c;
      pfVar3 = local_88;
      for (iVar5 = 0; pfVar2 = param_4, iVar5 < (int)param_3; iVar5 = iVar5 + 1) {
        local_70 = *pfVar2;
        local_6c = pfVar2[1];
        pfVar4 = (float *)(param_1 + *(char *)(param_2 + 0xb) * 0x30 + 0x8d4);
        local_68 = pfVar2[2];
        gnt4_PSMTXMultVecSR_bl((float *)(param_1 + 0x8d4),param_2 + 3,&local_4c);
        gnt4_PSVECAdd_bl(&local_4c,pfVar2,pfVar2);
        gnt4_PSVECAdd_bl(afStack_7c,pfVar2,pfVar2);
        dVar6 = gnt4_PSVECMag_bl(param_5);
        if (dVar7 < dVar6) {
          gnt4_PSQUATScale_bl((double)(float)(dVar7 / dVar6),param_5,param_5);
        }
        gnt4_PSQUATScale_bl((double)FLOAT_80438e50,param_5,param_5);
        gnt4_PSVECAdd_bl(param_5,pfVar2,pfVar2);
        gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_4c);
        zz_006ec1c_(&local_4c,&local_4c);
        gnt4_PSQUATScale_bl((double)(float)((double)param_2[10] * dVar8),&local_4c,&local_4c);
        gnt4_PSVECAdd_bl(pfVar3,&local_4c,pfVar2);
        gnt4_PSMTXMultVec_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2,
                   &local_58);
        gnt4_PSVECSubtract_bl(pfVar2,&local_58,&local_4c);
        dVar6 = gnt4_PSVECMag_bl(&local_4c);
        if ((double)(float)((double)param_2[9] * dVar8) < dVar6) {
          gnt4_PSQUATScale_bl((double)(float)(dVar8 * (double)(float)((double)param_2[9] / dVar6)),
                              &local_4c,&local_4c);
          gnt4_PSVECAdd_bl(&local_58,&local_4c,pfVar2);
        }
        gnt4_PSMTXMultVecSR_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2 + 6,
                   &local_64);
        if (*(char *)((int)param_2 + 0x2e) == '\x01') {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_4c);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_4c,&local_4c);
          }
          gnt4_PSVECCrossProduct_bl(&local_64,&local_4c,&local_58);
          gnt4_PSVECCrossProduct_bl(&local_4c,&local_58,&local_64);
        }
        else {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_58);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_58,&local_58);
          }
          gnt4_PSVECCrossProduct_bl(&local_58,&local_64,&local_4c);
          gnt4_PSVECCrossProduct_bl(&local_4c,&local_58,&local_64);
        }
        zz_006eb4c_(&local_64,&local_64);
        zz_006ebb4_(&local_4c,&local_4c);
        zz_006ec1c_(&local_58,&local_58);
        gnt4_PSQUATScale_bl(dVar8,&local_64,&local_64);
        gnt4_PSQUATScale_bl(dVar8,&local_4c,&local_4c);
        gnt4_PSQUATScale_bl(dVar8,&local_58,&local_58);
        *pfVar4 = local_64;
        pfVar4[4] = local_60;
        pfVar4[8] = local_5c;
        pfVar4[1] = local_4c;
        pfVar4[5] = local_48;
        pfVar4[9] = local_44;
        pfVar4[2] = local_58;
        pfVar4[6] = local_54;
        pfVar4[10] = local_50;
        pfVar4[3] = *pfVar3;
        pfVar4[7] = pfVar3[1];
        pfVar4[0xb] = pfVar3[2];
        gnt4_PSVECSubtract_bl(pfVar2,&local_70,param_5);
        param_5 = param_5 + 3;
        *(uint *)(param_1 + 0x1d70) =
             *(uint *)(param_1 + 0x1d70) & ~(1 << (int)*(char *)(param_2 + 0xb));
        param_2 = param_2 + 0xc;
        param_4 = pfVar2 + 3;
        pfVar3 = pfVar2;
      }
    }
  }
  else {
    zz_00e3758_(param_1,(int)param_2,param_3,param_4,param_5);
  }
  return;
}



// ==== 800e3ca0  zz_00e3ca0_ ====

void zz_00e3ca0_(int param_1,int param_2,uint param_3,undefined4 *param_4,float *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  fVar4 = FLOAT_80438e40;
  if (0 < (int)param_3) {
    uVar6 = param_3 >> 1;
    if (uVar6 != 0) {
      do {
        iVar5 = *(char *)(param_2 + 0x2c) * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[1] = uVar2;
        param_4[2] = uVar3;
        param_5[2] = fVar4;
        param_5[1] = fVar4;
        *param_5 = fVar4;
        pcVar1 = (char *)(param_2 + 0x5c);
        param_2 = param_2 + 0x60;
        iVar5 = *pcVar1 * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        param_4[3] = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[4] = uVar2;
        param_4[5] = uVar3;
        param_4 = param_4 + 6;
        param_5[5] = fVar4;
        param_5[4] = fVar4;
        param_5[3] = fVar4;
        param_5 = param_5 + 6;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      param_3 = param_3 & 1;
      if (param_3 == 0) {
        return;
      }
    }
    do {
      pcVar1 = (char *)(param_2 + 0x2c);
      param_2 = param_2 + 0x30;
      iVar5 = *pcVar1 * 0x30;
      uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
      uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
      *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
      param_4[1] = uVar2;
      param_4[2] = uVar3;
      param_4 = param_4 + 3;
      param_5[2] = fVar4;
      param_5[1] = fVar4;
      *param_5 = fVar4;
      param_5 = param_5 + 3;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  return;
}



// ==== 800e3dec  FUN_800e3dec ====

/* WARNING: Removing unreachable block (ram,0x800e4278) */
/* WARNING: Removing unreachable block (ram,0x800e4270) */
/* WARNING: Removing unreachable block (ram,0x800e3e04) */
/* WARNING: Removing unreachable block (ram,0x800e3dfc) */

void FUN_800e3dec(int param_1,float *param_2,uint param_3,float *param_4,float *param_5,int *param_6
                 )

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float afStack_b8 [3];
  float afStack_ac [3];
  float local_a0 [3];
  float afStack_94 [3];
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  
  uVar1 = zz_00e5230_(param_1);
  if (uVar1 == 0) {
    dVar9 = (double)*(float *)(param_1 + 0xb4);
    if ((double)FLOAT_80438e44 <= dVar9) {
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),
                 (float *)(param_1 + *(char *)(param_2 + 0xb) * 0xc + 0x12d4),local_a0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_94);
      gnt4_PSQUATScale_bl((double)FLOAT_80438e48,afStack_94,afStack_94);
      dVar10 = (double)FLOAT_80438e4c;
      pfVar4 = local_a0;
      for (iVar6 = 0; pfVar2 = param_4, iVar6 < (int)param_3; iVar6 = iVar6 + 1) {
        local_88 = *pfVar2;
        local_84 = pfVar2[1];
        pfVar5 = (float *)(param_1 + *(char *)(param_2 + 0xb) * 0x30 + 0x8d4);
        local_80 = pfVar2[2];
        gnt4_PSMTXMultVecSR_bl((float *)(param_1 + 0x8d4),param_2 + 3,&local_64);
        gnt4_PSVECAdd_bl(&local_64,pfVar2,pfVar2);
        gnt4_PSVECAdd_bl(afStack_94,pfVar2,pfVar2);
        dVar8 = gnt4_PSVECMag_bl(param_5);
        if (dVar10 < dVar8) {
          gnt4_PSQUATScale_bl((double)(float)(dVar10 / dVar8),param_5,param_5);
        }
        gnt4_PSQUATScale_bl((double)FLOAT_80438e50,param_5,param_5);
        gnt4_PSVECAdd_bl(param_5,pfVar2,pfVar2);
        gnt4_PSVECSubtract_bl(pfVar2,pfVar4,&local_64);
        zz_006ec1c_(&local_64,&local_64);
        gnt4_PSQUATScale_bl((double)(float)((double)param_2[10] * dVar9),&local_64,&local_64);
        gnt4_PSVECAdd_bl(pfVar4,&local_64,pfVar2);
        gnt4_PSMTXMultVec_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2,
                   &local_70);
        gnt4_PSVECSubtract_bl(pfVar2,&local_70,&local_64);
        dVar8 = gnt4_PSVECMag_bl(&local_64);
        if ((double)(float)((double)param_2[9] * dVar9) < dVar8) {
          gnt4_PSQUATScale_bl((double)(float)(dVar9 * (double)(float)((double)param_2[9] / dVar8)),
                              &local_64,&local_64);
          gnt4_PSVECAdd_bl(&local_70,&local_64,pfVar2);
        }
        if (param_6 != (int *)0x0) {
          iVar7 = 0;
          for (iVar3 = 0; iVar3 < *param_6; iVar3 = iVar3 + 1) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(param_1 + *(char *)(param_6[1] + iVar3) * 0x30 + 0x8d4),
                       (float *)(param_6[2] + iVar7),afStack_ac);
            gnt4_PSVECSubtract_bl(pfVar2,afStack_ac,afStack_b8);
            dVar8 = gnt4_PSVECMag_bl(afStack_b8);
            if (dVar8 < (double)(float)(dVar9 * (double)*(float *)(param_6[2] + iVar7 + 0xc))) {
              gnt4_PSQUATScale_bl((double)(float)(dVar9 * (double)(float)((double)*(float *)(param_6
                                                  [2] + 0xc) / dVar8)),afStack_b8,afStack_b8);
              gnt4_PSVECAdd_bl(afStack_ac,afStack_b8,pfVar2);
            }
            iVar7 = iVar7 + 0x10;
          }
        }
        gnt4_PSMTXMultVecSR_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2 + 6,
                   &local_7c);
        if (*(char *)((int)param_2 + 0x2e) == '\x01') {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar4,&local_64);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_64,&local_64);
          }
          gnt4_PSVECCrossProduct_bl(&local_7c,&local_64,&local_70);
          gnt4_PSVECCrossProduct_bl(&local_64,&local_70,&local_7c);
        }
        else {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar4,&local_70);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_70,&local_70);
          }
          gnt4_PSVECCrossProduct_bl(&local_70,&local_7c,&local_64);
          gnt4_PSVECCrossProduct_bl(&local_64,&local_70,&local_7c);
        }
        zz_006eb4c_(&local_7c,&local_7c);
        zz_006ebb4_(&local_64,&local_64);
        zz_006ec1c_(&local_70,&local_70);
        gnt4_PSQUATScale_bl(dVar9,&local_7c,&local_7c);
        gnt4_PSQUATScale_bl(dVar9,&local_64,&local_64);
        gnt4_PSQUATScale_bl(dVar9,&local_70,&local_70);
        *pfVar5 = local_7c;
        pfVar5[4] = local_78;
        pfVar5[8] = local_74;
        pfVar5[1] = local_64;
        pfVar5[5] = local_60;
        pfVar5[9] = local_5c;
        pfVar5[2] = local_70;
        pfVar5[6] = local_6c;
        pfVar5[10] = local_68;
        pfVar5[3] = *pfVar4;
        pfVar5[7] = pfVar4[1];
        pfVar5[0xb] = pfVar4[2];
        gnt4_PSVECSubtract_bl(pfVar2,&local_88,param_5);
        param_5 = param_5 + 3;
        *(uint *)(param_1 + 0x1d70) =
             *(uint *)(param_1 + 0x1d70) & ~(1 << (int)*(char *)(param_2 + 0xb));
        param_2 = param_2 + 0xc;
        param_4 = pfVar2 + 3;
        pfVar4 = pfVar2;
      }
    }
  }
  else {
    zz_00e3ca0_(param_1,(int)param_2,param_3,param_4,param_5);
  }
  return;
}



// ==== 800e4294  FUN_800e4294 ====

void FUN_800e4294(int param_1,int param_2,uint param_3,undefined4 *param_4,float *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  fVar4 = FLOAT_80438e40;
  if (0 < (int)param_3) {
    uVar6 = param_3 >> 1;
    if (uVar6 != 0) {
      do {
        iVar5 = *(char *)(param_2 + 0x2c) * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[1] = uVar2;
        param_4[2] = uVar3;
        param_5[2] = fVar4;
        param_5[1] = fVar4;
        *param_5 = fVar4;
        pcVar1 = (char *)(param_2 + 0x5c);
        param_2 = param_2 + 0x60;
        iVar5 = *pcVar1 * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        param_4[3] = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[4] = uVar2;
        param_4[5] = uVar3;
        param_4 = param_4 + 6;
        param_5[5] = fVar4;
        param_5[4] = fVar4;
        param_5[3] = fVar4;
        param_5 = param_5 + 6;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      param_3 = param_3 & 1;
      if (param_3 == 0) {
        return;
      }
    }
    do {
      pcVar1 = (char *)(param_2 + 0x2c);
      param_2 = param_2 + 0x30;
      iVar5 = *pcVar1 * 0x30;
      uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
      uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
      *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
      param_4[1] = uVar2;
      param_4[2] = uVar3;
      param_4 = param_4 + 3;
      param_5[2] = fVar4;
      param_5[1] = fVar4;
      *param_5 = fVar4;
      param_5 = param_5 + 3;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  return;
}



// ==== 800e43e0  FUN_800e43e0 ====

/* WARNING: Removing unreachable block (ram,0x800e48b0) */
/* WARNING: Removing unreachable block (ram,0x800e48a8) */
/* WARNING: Removing unreachable block (ram,0x800e48a0) */
/* WARNING: Removing unreachable block (ram,0x800e4400) */
/* WARNING: Removing unreachable block (ram,0x800e43f8) */
/* WARNING: Removing unreachable block (ram,0x800e43f0) */

void FUN_800e43e0(int param_1,float *param_2,uint param_3,float *param_4,float *param_5,int *param_6
                 )

{
  uint uVar1;
  float *pfVar2;
  float *pfVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  float afStack_c8 [3];
  float local_bc;
  float local_b8;
  float local_b4;
  float local_b0 [3];
  float fStack_a4;
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  
  uVar1 = zz_00e5230_(param_1);
  if (uVar1 == 0) {
    dVar12 = (double)*(float *)(param_1 + 0xb4);
    if ((double)FLOAT_80438e44 <= dVar12) {
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),
                 (float *)(param_1 + *(char *)(param_2 + 0xb) * 0xc + 0x12d4),local_b0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&fStack_a4);
      dVar9 = (double)FLOAT_80438e58;
      if (((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) && (FLOAT_80438e40 < local_a0)) {
        dVar9 = (double)FLOAT_80438e5c;
      }
      gnt4_PSQUATScale_bl(dVar9,&fStack_a4,&fStack_a4);
      dVar9 = (double)FLOAT_80438e4c;
      pfVar5 = local_b0;
      for (iVar7 = 0; pfVar3 = param_4, iVar7 < (int)param_3; iVar7 = iVar7 + 1) {
        local_98 = *pfVar3;
        local_94 = pfVar3[1];
        pfVar6 = (float *)(param_1 + *(char *)(param_2 + 0xb) * 0x30 + 0x8d4);
        local_90 = pfVar3[2];
        gnt4_PSMTXMultVecSR_bl((float *)(param_1 + 0x8d4),param_2 + 3,&local_74);
        gnt4_PSVECAdd_bl(&local_74,pfVar3,pfVar3);
        gnt4_PSVECAdd_bl(&fStack_a4,pfVar3,pfVar3);
        dVar10 = gnt4_PSVECMag_bl(param_5);
        if (dVar9 < dVar10) {
          gnt4_PSQUATScale_bl((double)(float)(dVar9 / dVar10),param_5,param_5);
        }
        gnt4_PSQUATScale_bl((double)FLOAT_80438e50,param_5,param_5);
        gnt4_PSVECAdd_bl(param_5,pfVar3,pfVar3);
        gnt4_PSVECSubtract_bl(pfVar3,pfVar5,&local_74);
        zz_006ec1c_(&local_74,&local_74);
        gnt4_PSQUATScale_bl((double)(float)((double)param_2[10] * dVar12),&local_74,&local_74);
        gnt4_PSVECAdd_bl(pfVar5,&local_74,pfVar3);
        gnt4_PSMTXMultVec_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2,
                   &local_80);
        gnt4_PSVECSubtract_bl(pfVar3,&local_80,&local_74);
        dVar10 = gnt4_PSVECMag_bl(&local_74);
        if ((double)(float)((double)param_2[9] * dVar12) < dVar10) {
          gnt4_PSQUATScale_bl((double)(float)(dVar12 * (double)(float)((double)param_2[9] / dVar10))
                              ,&local_74,&local_74);
          gnt4_PSVECAdd_bl(&local_80,&local_74,pfVar3);
        }
        if (param_6 != (int *)0x0) {
          dVar10 = (double)FLOAT_80438e40;
          iVar8 = 0;
          for (iVar4 = 0; iVar4 < *param_6; iVar4 = iVar4 + 1) {
            pfVar2 = (float *)(param_1 + *(char *)(param_6[1] + iVar4) * 0x30 + 0x8d4);
            local_bc = pfVar2[3];
            local_b8 = pfVar2[7];
            local_b4 = pfVar2[0xb];
            gnt4_PSMTXMultVecSR_bl(pfVar2,(float *)(param_6[2] + iVar8),afStack_c8);
            zz_006ec1c_(afStack_c8,afStack_c8);
            gnt4_PSVECSubtract_bl(pfVar3,&local_bc,&local_8c);
            dVar11 = gnt4_PSQUATDotProduct_bl(&local_8c,afStack_c8);
            if (dVar11 < dVar10) {
              gnt4_PSQUATScale_bl(-dVar11,afStack_c8,afStack_c8);
              gnt4_PSVECAdd_bl(afStack_c8,pfVar3,pfVar3);
            }
            iVar8 = iVar8 + 0xc;
          }
        }
        gnt4_PSMTXMultVecSR_bl
                  ((float *)(param_1 + *(char *)((int)param_2 + 0x2d) * 0x30 + 0x8d4),param_2 + 6,
                   &local_8c);
        if (*(char *)((int)param_2 + 0x2e) == '\x01') {
          gnt4_PSVECSubtract_bl(pfVar3,pfVar5,&local_74);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_74,&local_74);
          }
          gnt4_PSVECCrossProduct_bl(&local_8c,&local_74,&local_80);
          gnt4_PSVECCrossProduct_bl(&local_74,&local_80,&local_8c);
        }
        else {
          gnt4_PSVECSubtract_bl(pfVar3,pfVar5,&local_80);
          if (*(char *)((int)param_2 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_80,&local_80);
          }
          gnt4_PSVECCrossProduct_bl(&local_80,&local_8c,&local_74);
          gnt4_PSVECCrossProduct_bl(&local_74,&local_80,&local_8c);
        }
        zz_006eb4c_(&local_8c,&local_8c);
        zz_006ebb4_(&local_74,&local_74);
        zz_006ec1c_(&local_80,&local_80);
        gnt4_PSQUATScale_bl(dVar12,&local_8c,&local_8c);
        gnt4_PSQUATScale_bl(dVar12,&local_74,&local_74);
        gnt4_PSQUATScale_bl(dVar12,&local_80,&local_80);
        *pfVar6 = local_8c;
        pfVar6[4] = local_88;
        pfVar6[8] = local_84;
        pfVar6[1] = local_74;
        pfVar6[5] = local_70;
        pfVar6[9] = local_6c;
        pfVar6[2] = local_80;
        pfVar6[6] = local_7c;
        pfVar6[10] = local_78;
        pfVar6[3] = *pfVar5;
        pfVar6[7] = pfVar5[1];
        pfVar6[0xb] = pfVar5[2];
        gnt4_PSVECSubtract_bl(pfVar3,&local_98,param_5);
        param_5 = param_5 + 3;
        *(uint *)(param_1 + 0x1d70) =
             *(uint *)(param_1 + 0x1d70) & ~(1 << (int)*(char *)(param_2 + 0xb));
        param_2 = param_2 + 0xc;
        param_4 = pfVar3 + 3;
        pfVar5 = pfVar3;
      }
    }
  }
  else {
    FUN_800e4294(param_1,(int)param_2,param_3,param_4,param_5);
  }
  return;
}



// ==== 800e48cc  zz_00e48cc_ ====

void zz_00e48cc_(int param_1,int param_2,uint param_3,undefined4 *param_4,float *param_5)

{
  char *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  fVar4 = FLOAT_80438e40;
  if (0 < (int)param_3) {
    uVar6 = param_3 >> 1;
    if (uVar6 != 0) {
      do {
        iVar5 = *(char *)(param_2 + 0x2c) * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[1] = uVar2;
        param_4[2] = uVar3;
        param_5[2] = fVar4;
        param_5[1] = fVar4;
        *param_5 = fVar4;
        pcVar1 = (char *)(param_2 + 0x5c);
        param_2 = param_2 + 0x60;
        iVar5 = *pcVar1 * 0x30;
        uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
        uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
        param_4[3] = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
        param_4[4] = uVar2;
        param_4[5] = uVar3;
        param_4 = param_4 + 6;
        param_5[5] = fVar4;
        param_5[4] = fVar4;
        param_5[3] = fVar4;
        param_5 = param_5 + 6;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      param_3 = param_3 & 1;
      if (param_3 == 0) {
        return;
      }
    }
    do {
      pcVar1 = (char *)(param_2 + 0x2c);
      param_2 = param_2 + 0x30;
      iVar5 = *pcVar1 * 0x30;
      uVar2 = *(undefined4 *)(param_1 + iVar5 + 0x8f0);
      uVar3 = *(undefined4 *)(param_1 + iVar5 + 0x900);
      *param_4 = *(undefined4 *)(param_1 + iVar5 + 0x8e0);
      param_4[1] = uVar2;
      param_4[2] = uVar3;
      param_4 = param_4 + 3;
      param_5[2] = fVar4;
      param_5[1] = fVar4;
      *param_5 = fVar4;
      param_5 = param_5 + 3;
      param_3 = param_3 - 1;
    } while (param_3 != 0);
  }
  return;
}



// ==== 800e4a18  FUN_800e4a18 ====

/* WARNING: Removing unreachable block (ram,0x800e4ea8) */
/* WARNING: Removing unreachable block (ram,0x800e4ea0) */
/* WARNING: Removing unreachable block (ram,0x800e4e98) */
/* WARNING: Removing unreachable block (ram,0x800e4a38) */
/* WARNING: Removing unreachable block (ram,0x800e4a30) */
/* WARNING: Removing unreachable block (ram,0x800e4a28) */

void FUN_800e4a18(double param_1,int param_2,float *param_3,uint param_4,float *param_5,
                 float *param_6,float *param_7)

{
  uint uVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float local_a8 [3];
  float afStack_9c [3];
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  
  uVar1 = zz_00e5230_(param_2);
  if (uVar1 == 0) {
    dVar8 = (double)*(float *)(param_2 + 0xb4);
    if ((double)FLOAT_80438e44 <= dVar8) {
      gnt4_PSMTXMultVec_bl
                ((float *)(param_2 + *(char *)((int)param_3 + 0x2d) * 0x30 + 0x8d4),
                 (float *)(param_2 + *(char *)(param_3 + 0xb) * 0xc + 0x12d4),local_a8);
      gnt4_PSVECSubtract_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x5e8),afStack_9c);
      gnt4_PSQUATScale_bl((double)FLOAT_80438e60,afStack_9c,afStack_9c);
      dVar9 = (double)(float)(param_1 * dVar8);
      dVar10 = (double)FLOAT_80438e4c;
      pfVar3 = local_a8;
      for (iVar5 = 0; pfVar2 = param_5, iVar5 < (int)param_4; iVar5 = iVar5 + 1) {
        local_90 = *pfVar2;
        local_8c = pfVar2[1];
        pfVar4 = (float *)(param_2 + *(char *)(param_3 + 0xb) * 0x30 + 0x8d4);
        local_88 = pfVar2[2];
        gnt4_PSMTXMultVecSR_bl((float *)(param_2 + 0x8d4),param_3 + 3,&local_6c);
        gnt4_PSVECAdd_bl(&local_6c,pfVar2,pfVar2);
        gnt4_PSVECAdd_bl(afStack_9c,pfVar2,pfVar2);
        dVar7 = gnt4_PSVECMag_bl(param_6);
        if (dVar10 < dVar7) {
          gnt4_PSQUATScale_bl((double)(float)(dVar10 / dVar7),param_6,param_6);
        }
        gnt4_PSQUATScale_bl((double)FLOAT_80438e50,param_6,param_6);
        gnt4_PSVECAdd_bl(param_6,pfVar2,pfVar2);
        gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_6c);
        zz_006ec1c_(&local_6c,&local_6c);
        gnt4_PSQUATScale_bl((double)(float)((double)param_3[10] * dVar8),&local_6c,&local_6c);
        gnt4_PSVECAdd_bl(pfVar3,&local_6c,pfVar2);
        dVar7 = FUN_8003d964((double)*(float *)(param_2 + 0x668),param_2,pfVar2);
        if ((double)*(float *)(param_2 + 0x24) < dVar7) {
          dVar7 = (double)*(float *)(param_2 + 0x24);
        }
        if (0 < iVar5) {
          dVar6 = (double)(FLOAT_80438e64 + param_7[-1]);
          if (dVar6 < dVar7) {
            dVar7 = dVar6;
          }
          dVar6 = (double)(param_7[-1] - FLOAT_80438e64);
          if (dVar7 < dVar6) {
            dVar7 = dVar6;
          }
        }
        *param_7 = (float)dVar7;
        if ((float)(dVar7 + dVar9) <= pfVar2[1]) {
          gnt4_PSMTXMultVec_bl
                    ((float *)(param_2 + *(char *)((int)param_3 + 0x2d) * 0x30 + 0x8d4),param_3,
                     &local_78);
          gnt4_PSVECSubtract_bl(pfVar2,&local_78,&local_6c);
          dVar7 = gnt4_PSVECMag_bl(&local_6c);
          if ((double)(float)((double)param_3[9] * dVar8) < dVar7) {
            gnt4_PSQUATScale_bl((double)(float)(dVar8 * (double)(float)((double)param_3[9] / dVar7))
                                ,&local_6c,&local_6c);
            gnt4_PSVECAdd_bl(&local_78,&local_6c,pfVar2);
          }
        }
        else {
          pfVar2[1] = (float)(dVar7 + dVar9) - FLOAT_80438e68;
          local_90 = *pfVar2;
          local_8c = pfVar2[1];
          local_88 = pfVar2[2];
        }
        gnt4_PSMTXMultVecSR_bl
                  ((float *)(param_2 + *(char *)((int)param_3 + 0x2d) * 0x30 + 0x8d4),param_3 + 6,
                   &local_84);
        if (*(char *)((int)param_3 + 0x2e) == '\x01') {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_6c);
          if (*(char *)((int)param_3 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_6c,&local_6c);
          }
          gnt4_PSVECCrossProduct_bl(&local_84,&local_6c,&local_78);
          gnt4_PSVECCrossProduct_bl(&local_6c,&local_78,&local_84);
        }
        else {
          gnt4_PSVECSubtract_bl(pfVar2,pfVar3,&local_78);
          if (*(char *)((int)param_3 + 0x2f) < '\0') {
            gnt4_PSQUATScale_bl((double)FLOAT_80438e54,&local_78,&local_78);
          }
          gnt4_PSVECCrossProduct_bl(&local_78,&local_84,&local_6c);
          gnt4_PSVECCrossProduct_bl(&local_6c,&local_78,&local_84);
        }
        zz_006eb4c_(&local_84,&local_84);
        zz_006ebb4_(&local_6c,&local_6c);
        zz_006ec1c_(&local_78,&local_78);
        gnt4_PSQUATScale_bl(dVar8,&local_84,&local_84);
        gnt4_PSQUATScale_bl(dVar8,&local_6c,&local_6c);
        gnt4_PSQUATScale_bl(dVar8,&local_78,&local_78);
        *pfVar4 = local_84;
        pfVar4[4] = local_80;
        pfVar4[8] = local_7c;
        pfVar4[1] = local_6c;
        pfVar4[5] = local_68;
        pfVar4[9] = local_64;
        pfVar4[2] = local_78;
        pfVar4[6] = local_74;
        pfVar4[10] = local_70;
        pfVar4[3] = *pfVar3;
        pfVar4[7] = pfVar3[1];
        pfVar4[0xb] = pfVar3[2];
        gnt4_PSVECSubtract_bl(pfVar2,&local_90,param_6);
        pfVar3 = param_3 + 0xb;
        param_3 = param_3 + 0xc;
        param_6 = param_6 + 3;
        *(uint *)(param_2 + 0x1d70) = *(uint *)(param_2 + 0x1d70) & ~(1 << (int)*(char *)pfVar3);
        param_7 = param_7 + 1;
        param_5 = pfVar2 + 3;
        pfVar3 = pfVar2;
      }
    }
  }
  else {
    zz_00e48cc_(param_2,(int)param_3,param_4,param_5,param_6);
  }
  return;
}



// ==== 800e4ec4  zz_00e4ec4_ ====

void zz_00e4ec4_(int param_1,int param_2,int param_3,float *param_4,float *param_5)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < param_3; iVar2 = iVar2 + 1) {
    gnt4_PSVECAdd_bl(param_4,param_5,param_4);
    if ((*(uint *)(param_1 + 0x1d70) & 1 << (int)*(char *)(param_2 + 0x2c)) == 0) {
      iVar1 = *(char *)(param_2 + 0x2c) * 0x30 + 0x8e0;
      *(float *)(param_1 + iVar1) = *(float *)(param_1 + iVar1) + *param_5;
      iVar1 = *(char *)(param_2 + 0x2c) * 0x30 + 0x8f0;
      *(float *)(param_1 + iVar1) = *(float *)(param_1 + iVar1) + param_5[1];
      iVar1 = *(char *)(param_2 + 0x2c) * 0x30 + 0x900;
      *(float *)(param_1 + iVar1) = *(float *)(param_1 + iVar1) + param_5[2];
    }
    param_2 = param_2 + 0x30;
    param_4 = param_4 + 3;
  }
  return;
}



// ==== 800e4f9c  FUN_800e4f9c ====

/* WARNING: Removing unreachable block (ram,0x800e5168) */
/* WARNING: Removing unreachable block (ram,0x800e4fac) */

void FUN_800e4f9c(int param_1,int param_2,int param_3,float *param_4,float *param_5)

{
  float *pfVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  double dVar5;
  float local_58;
  float local_54;
  float local_50;
  float local_4c [3];
  float local_40;
  float local_3c;
  float local_38;
  
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + *(char *)(param_2 + 0x2d) * 0x30 + 0x8d4),
             (float *)(param_1 + *(char *)(param_2 + 0x2c) * 0xc + 0x12d4),local_4c);
  dVar5 = (double)*(float *)(param_1 + 0xb4);
  pfVar4 = local_4c;
  for (iVar2 = 0; pfVar3 = param_4, iVar2 < param_3; iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(param_1 + *(char *)(param_2 + 0x2c) * 0x30 + 0x8d4);
    zz_0046470_(pfVar1,&local_58);
    local_40 = *pfVar1;
    local_3c = pfVar1[4];
    local_38 = pfVar1[8];
    gnt4_PSQUATScale_bl((double)(float)(dVar5 / (double)local_58),&local_40,&local_40);
    *pfVar1 = local_40;
    pfVar1[4] = local_3c;
    pfVar1[8] = local_38;
    local_40 = pfVar1[1];
    local_3c = pfVar1[5];
    local_38 = pfVar1[9];
    gnt4_PSQUATScale_bl((double)(float)(dVar5 / (double)local_54),&local_40,&local_40);
    pfVar1[1] = local_40;
    pfVar1[5] = local_3c;
    pfVar1[9] = local_38;
    local_40 = pfVar1[2];
    local_3c = pfVar1[6];
    local_38 = pfVar1[10];
    gnt4_PSQUATScale_bl((double)(float)(dVar5 / (double)local_50),&local_40,&local_40);
    pfVar1[2] = local_40;
    pfVar1[6] = local_3c;
    pfVar1[10] = local_38;
    pfVar1[3] = *pfVar4;
    pfVar1[7] = pfVar4[1];
    pfVar1[0xb] = pfVar4[2];
    gnt4_PSQUATScale_bl((double)(float)((double)*(float *)(param_2 + 0x28) * dVar5),param_5,
                        &local_40);
    gnt4_PSVECAdd_bl(pfVar4,&local_40,pfVar3);
    param_5 = param_5 + 3;
    *(uint *)(param_1 + 0x1d70) =
         *(uint *)(param_1 + 0x1d70) & ~(1 << (int)*(char *)(param_2 + 0x2c));
    param_2 = param_2 + 0x30;
    param_4 = pfVar3 + 3;
    pfVar4 = pfVar3;
  }
  return;
}



// ==== 800e5184  zz_00e5184_ ====

void zz_00e5184_(int param_1,int param_2,int param_3,float *param_4,float *param_5)

{
  float *pfVar1;
  int iVar2;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [3];
  
  iVar2 = param_1 + *(char *)(param_2 + 0x2d) * 0x30;
  local_28 = *(float *)(iVar2 + 0x8e0);
  local_24 = *(undefined4 *)(iVar2 + 0x8f0);
  local_20 = *(undefined4 *)(iVar2 + 0x900);
  pfVar1 = &local_28;
  for (iVar2 = 0; iVar2 < param_3; iVar2 = iVar2 + 1) {
    gnt4_PSVECSubtract_bl(param_4,pfVar1,afStack_1c);
    zz_006ec1c_(afStack_1c,param_5);
    param_5 = param_5 + 3;
    pfVar1 = param_4;
    param_4 = param_4 + 3;
  }
  return;
}



// ==== 800e5230  zz_00e5230_ ====

uint zz_00e5230_(int param_1)

{
  uint uVar1;
  
  if ('\x01' < *(char *)(param_1 + 0x18)) {
    return 0;
  }
  if (*(char *)(param_1 + 0x18) < '\x01') {
    return 1;
  }
  if ('\0' < *(char *)(param_1 + 0x19)) {
    return 0;
  }
  uVar1 = countLeadingZeros((uint)(FLOAT_80438e44 < *(float *)(param_1 + 0xb4)));
  return uVar1 >> 5;
}



// ==== 800e53a8  FUN_800e53a8 ====

void FUN_800e53a8(int param_1)

{
  *(undefined1 *)(param_1 + 0x144) = 0;
  if (*(short *)(param_1 + 1000) == 0x203) {
    zz_00e2990_(param_1,0);
    zz_00e2db0_(param_1,0);
    zz_01ee294_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0x20c) {
    zz_00e2990_(param_1,1);
    zz_00e2db0_(param_1,1);
  }
  return;
}



// ==== 800e54ac  FUN_800e54ac ====

void FUN_800e54ac(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18dc) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                             DOUBLE_80438e78) * FLOAT_80438e70);
  }
  return;
}



// ==== 800e550c  FUN_800e550c ====

void FUN_800e550c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80318870)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800e5550  FUN_800e5550 ====

void FUN_800e5550(int param_1,int param_2)

{
  float afStack_18 [5];
  
  if (param_2 == 1) {
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),(float *)&DAT_80318884,afStack_18);
    zz_00b2290_((double)FLOAT_80438e80,param_1,2,afStack_18);
  }
  return;
}



// ==== 800e55b0  FUN_800e55b0 ====

void FUN_800e55b0(int param_1)

{
  (*(code *)(&PTR_FUN_80318890)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800e55ec  FUN_800e55ec ====

void FUN_800e55ec(int param_1)

{
  (*(code *)(&PTR_FUN_803188a0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800e5628  FUN_800e5628 ====

void FUN_800e5628(int param_1)

{
  (*(code *)(&PTR_FUN_803188b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800e5664  FUN_800e5664 ====

void FUN_800e5664(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  fVar2 = FLOAT_80438e84;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x50) = FLOAT_80438e84;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
  }
  else if (*(char *)(param_1 + 0x581) == '\x01') {
    *(float *)(param_1 + 0x50) = FLOAT_80438e84;
    *(float *)(param_1 + 0x48) = fVar2;
  }
  zz_006d144_(param_1,0x81);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438e88;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  if (*(char *)(param_1 + 0x144) == '\0') {
    zz_00f036c_(param_1,0xd9);
  }
  *(float *)(param_1 + 0x80c) = FLOAT_80438e84;
  return;
}



// ==== 800e5740  FUN_800e5740 ====

void FUN_800e5740(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0x81);
  }
  zz_004cd24_(param_1,0xf);
  zz_0067458_((double)FLOAT_80438e80,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    if (*(char *)(param_1 + 0x144) == '\0') {
      iVar3 = zz_006dbe0_(param_1,0,1,1);
      if (iVar3 != 0) {
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        if (*(short *)(param_1 + 1000) == 0x203) {
          zz_00e65a0_(param_1,0);
        }
        else if (*(short *)(param_1 + 1000) == 0x20c) {
          zz_00e65a0_(param_1,1);
        }
        *(undefined1 *)(param_1 + 0x144) = 1;
        zz_00f036c_(param_1,0xda);
      }
    }
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (FLOAT_80438e8c < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
    }
  }
  else if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  else {
    dVar4 = (double)FLOAT_80438e88;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800e58b4  FUN_800e58b4 ====

void FUN_800e58b4(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438e80 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800e5920  FUN_800e5920 ====

void FUN_800e5920(int param_1)

{
  (*(code *)(&PTR_FUN_803188c0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800e595c  FUN_800e595c ====

void FUN_800e595c(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}



// ==== 800e5980  FUN_800e5980 ====

void FUN_800e5980(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}



// ==== 800e59a4  FUN_800e59a4 ====

void FUN_800e59a4(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}



// ==== 800e59c8  FUN_800e59c8 ====

void FUN_800e59c8(int param_1)

{
  zz_0158a94_(param_1);
  return;
}



// ==== 800e59ec  FUN_800e59ec ====

void FUN_800e59ec(int param_1)

{
  zz_00e5a0c_(param_1);
  return;
}



// ==== 800e5a0c  zz_00e5a0c_ ====

void zz_00e5a0c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803188d4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800e5a5c  FUN_800e5a5c ====

void FUN_800e5a5c(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x6f6) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80438e90;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x6f6));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80438e88;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80438e84;
  return;
}



// ==== 800e5b80  FUN_800e5b80 ====

void FUN_800e5b80(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80438e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x6f6));
  fVar2 = FLOAT_80438e84;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800e5c40  FUN_800e5c40 ====

void FUN_800e5c40(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  *(short *)(param_1 + 0x18dc) =
       (short)(int)-(DOUBLE_80438e98 * (double)*(float *)(param_1 + 0x1dc8) -
                    ((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                    DOUBLE_80438e78));
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x6f6));
  gnt4_PSQUATScale_bl((double)FLOAT_80438e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x28;
  *(undefined2 *)(param_1 + 0x54a) = 0x38;
  *(undefined2 *)(param_1 + 0x54c) = 7;
  if (*(short *)(param_1 + 1000) == 0x20c) {
    *(undefined2 *)(param_1 + 0x548) = 0x18;
    *(undefined2 *)(param_1 + 0x54a) = 0x28;
  }
  fVar2 = FLOAT_80438ea0;
  fVar1 = FLOAT_80438e84;
  *(float *)(param_1 + 0x38) = FLOAT_80438e84;
  fVar3 = FLOAT_80438ea4;
  *(float *)(param_1 + 0x3c) = fVar2;
  *(float *)(param_1 + 0x40) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x50) = fVar1;
  zz_0066530_(param_1,0x2d);
  zz_00b2190_(param_1,0);
  return;
}



// ==== 800e5d64  FUN_800e5d64 ====

void FUN_800e5d64(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  double dVar5;
  double dVar6;
  
  iVar3 = zz_006de44_(param_1,0xf0f00);
  if (iVar3 != 0) {
    sVar4 = *(short *)(param_1 + 0x54c);
    *(short *)(param_1 + 0x54c) = sVar4 + -1;
    if (*(short *)(param_1 + 0x54c) < 1) {
      *(undefined2 *)(param_1 + 0x54c) = 1;
    }
    if (*(short *)(param_1 + 0x54a) < sVar4) {
      sVar4 = *(short *)(param_1 + 0x54a);
    }
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) - sVar4;
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + sVar4;
  }
  *(short *)(param_1 + 0x18dc) =
       (short)(int)-(DOUBLE_80438e98 * (double)*(float *)(param_1 + 0x1dc8) -
                    ((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                    DOUBLE_80438e78));
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x6f6));
  *(float *)(param_1 + 0x38) =
       *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x3c) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x3c);
  }
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x6f6));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x6f6));
  dVar6 = (double)FLOAT_80438e80;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf2) != '\0') {
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -8;
    if (*(short *)(param_1 + 0x548) < 0) {
      dVar5 = (double)FLOAT_80438e88;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x18dc) = 0;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
      fVar2 = FLOAT_80438e84;
      *(float *)(param_1 + 0x50) = FLOAT_80438e84;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
    }
    zz_00f036c_(param_1,10);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 800e5f54  FUN_800e5f54 ====

void FUN_800e5f54(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80438e84;
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar2 = FLOAT_80438ea8;
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80438e80,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    zz_00b22f4_(param_1);
  }
  else {
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_80438eac + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800e6028  FUN_800e6028 ====

void FUN_800e6028(int param_1)

{
  zz_00e6048_(param_1);
  return;
}



// ==== 800e6048  zz_00e6048_ ====

void zz_00e6048_(int param_1)

{
  *(undefined1 *)(param_1 + 0x7de) = 4;
  *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  (*(code *)(&PTR_FUN_803188e8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800e6098  FUN_800e6098 ====

void FUN_800e6098(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  
  iVar5 = zz_006dbe0_(param_1,2,1,1);
  fVar4 = FLOAT_80438eb4;
  fVar3 = FLOAT_80438ea0;
  if (iVar5 == 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar5 = zz_00677b0_(param_1);
    if (iVar5 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80438eb0 + *(float *)(param_1 + 0x1dc8);
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80438e84;
    *(float *)(param_1 + 0x558) = fVar4;
    fVar4 = FLOAT_80438ea4;
    *(float *)(param_1 + 0x55c) = fVar3;
    *(float *)(param_1 + 0x560) = fVar2;
    *(undefined2 *)(param_1 + 0x54e) = 0x14;
    *(float *)(param_1 + 0x38) = fVar4 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x6ea) = 2;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      *(undefined1 *)(param_1 + 0x6ea) = 4;
    }
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar6 = (double)FLOAT_80438e88;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_80438e84;
  }
  return;
}



// ==== 800e61cc  FUN_800e61cc ====

void FUN_800e61cc(int param_1)

{
  FUN_800061a8(param_1,9);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800e622c  FUN_800e622c ====

void FUN_800e622c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  
  zz_00f0104_(param_1,0x20,2);
  if ((PTR_DAT_80433934[0x1f] != '\0') ||
     ((*(char *)(param_1 + 0x1d9) != '\0' &&
      (sVar5 = *(short *)(param_1 + 0x54e) + -1, *(short *)(param_1 + 0x54e) = sVar5, sVar5 < 1))))
  goto LAB_800e6430;
  *(undefined1 *)(param_1 + 0x747) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0x9f);
  cVar1 = *(char *)(param_1 + 0x541);
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0x747) = 0;
    dVar6 = DOUBLE_80438eb8;
    if ((*(uint *)(param_1 + 0x5bc) & 0x100) != 0) {
      *(char *)(param_1 + 0x541) = *(char *)(param_1 + 0x541) + '\x01';
      fVar2 = FLOAT_80438ea4;
      *(float *)(param_1 + 0x568) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3d)) -
                  dVar6);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x68);
      *(float *)(param_1 + 0x48) =
           fVar2 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x48) -
           *(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x568);
      goto LAB_800e6320;
    }
  }
  else if (('\0' < cVar1) && (cVar1 < '\x03')) {
LAB_800e6320:
    fVar3 = FLOAT_80438e84;
    fVar2 = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x568) = fVar2;
    if (fVar2 <= fVar3) {
      *(undefined1 *)(param_1 + 0x541) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  dVar6 = (double)FLOAT_80438e80;
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x38);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) &&
     (*(float *)(param_1 + 0x48) = FLOAT_80438e84, *(char *)(param_1 + 0x541) == '\0')) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    zz_00b2190_(param_1,2);
    zz_00f07e8_(param_1);
  }
  if (iVar4 != 0) {
    zz_0066ac0_(param_1,0);
    zz_0066e40_(param_1,2);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  if (FLOAT_80438e84 < *(float *)(param_1 + 0x55c)) {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  fVar2 = FLOAT_80438e84;
  if (((FLOAT_80438e84 < *(float *)(param_1 + 0x55c)) || ((*(uint *)(param_1 + 0x5bc) & 0x400) == 0)
      ) && (fVar3 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
           *(float *)(param_1 + 0x558) = fVar3, fVar2 < fVar3)) {
    if (*(float *)(param_1 + 0x44) <= FLOAT_80438e8c) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_800e6430:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 5;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar6 = (double)FLOAT_80438e88;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar6,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800e64b8  FUN_800e64b8 ====

void FUN_800e64b8(int param_1)

{
  float fVar1;
  int iVar2;
  
  FUN_800061a8(param_1,9);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80438e84;
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_006ed8c_((double)FLOAT_80438e94,param_1);
  FUN_80067310((double)FLOAT_80438e80,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (FLOAT_80438e8c < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80438eb0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800e65a0  zz_00e65a0_ ====

undefined4 zz_00e65a0_(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  if ((*(short *)(param_1 + 1000) == 0x203) || (*(short *)(param_1 + 1000) == 0x20c)) {
    puVar2 = zz_0088aa0_(param_1,3,8,1,1);
    if (puVar2 == (undefined1 *)0x0) {
      *(undefined1 *)(param_1 + 0x144) = 0;
      zz_006de10_(param_1,0);
      uVar1 = 0;
    }
    else {
      *puVar2 = 1;
      puVar2[0x11] = param_2;
      puVar2[0x13] = param_2;
      puVar2[0x10] = 0x1c;
      *(code **)(puVar2 + 0xc) = FUN_800e66dc;
      *(code **)(puVar2 + 0x10c) = FUN_800e6f74;
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



// ==== 800e66dc  FUN_800e66dc ====

void FUN_800e66dc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80318968)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e6774  FUN_800e6774 ====

void FUN_800e6774(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  undefined8 uVar10;
  
  puVar8 = &DAT_80318930;
  puVar6 = &DAT_803188f8;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar7 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar3 = iVar7 * 0x1c;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar2 = iVar3;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fce7704),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8f4);
  if (*(char *)(param_9 + 0x13) < '\x02') {
    gnt4_PSQUATScale_bl(-(double)*(float *)(&DAT_80318940 + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  else {
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80318940 + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
  }
  zz_0083d60_(param_9,iVar9,0);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80318940 + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80318940 + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80318934 + iVar4);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80318936 + iVar4);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x178) = *(undefined4 *)(&DAT_80318944 + iVar4);
  iVar1 = zz_0006f98_(iVar9);
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)(char)(&DAT_803188f8)[iVar3],iVar2,iVar5,puVar6,iVar7,
              puVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80318930 + iVar4));
  if (iVar2 == 0) {
    *(undefined1 *)(iVar9 + 0x144) = 0;
    zz_006de10_(iVar9,0);
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar9 + *(short *)(&DAT_803188fa + iVar3) * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fce76f8),(float *)(param_9 + 0x144));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x150))
    ;
    zz_00a2bf8_(iVar9,param_9,(undefined4 *)(param_9 + 0x144),(float *)(param_9 + 0x150),1,0);
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  return;
}



// ==== 800e6a00  FUN_800e6a00 ====

void FUN_800e6a00(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_00e6cb0_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_00e6a48_(param_1);
  }
  return;
}



// ==== 800e6a48  zz_00e6a48_ ====

void zz_00e6a48_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float afStack_38 [4];
  undefined4 local_28;
  uint uStack_24;
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00e6e48_(param_1);
        *(undefined2 *)(param_1 + 0x1c) = 4;
      }
      else {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1800;
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x178)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_80318948 + iVar3);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x178);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_8031893c + iVar3),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_80318938 + iVar3),param_1,
                     (char)*(undefined2 *)(&DAT_80318934 + iVar3));
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x178));
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_0084170_(param_1);
          if (iVar1 == 0) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(iVar4 + *(short *)(&DAT_803188fa + iVar2) * 0x30 + 0x8d4),
                       (float *)(iVar2 + -0x7fce76f8),(float *)(param_1 + 0x144));
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),(float *)(param_1 + 0x144),afStack_38);
            dVar5 = gnt4_PSVECMag_bl(afStack_38);
            uStack_24 = (int)*(short *)(&DAT_80318932 + iVar3) ^ 0x80000000;
            if ((double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80438ec0) <= dVar5)
            {
              local_28 = 0x43300000;
              gnt4_PSQUATScale_bl((double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_24) -
                                                                 DOUBLE_80438ec0) / dVar5),
                                  afStack_38,afStack_38);
              gnt4_PSVECAdd_bl((float *)(param_1 + 0x144),afStack_38,(float *)(param_1 + 0x20));
              *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x20);
              *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
              *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
              zz_00e6e48_(param_1);
            }
          }
          else {
            zz_00e6e48_(param_1);
            *(undefined2 *)(param_1 + 0x1c) = 4;
          }
        }
        else {
          zz_00e6e48_(param_1);
        }
      }
    }
    else {
      zz_00e6e48_(param_1);
    }
  }
  else {
    zz_00e6e48_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 4;
  }
  return;
}



// ==== 800e6cb0  zz_00e6cb0_ ====

void zz_00e6cb0_(int param_1)

{
  int iVar1;
  int iVar2;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_1 + 0x1a) == '\0') {
    *(undefined1 *)(param_1 + 0x1a) = 1;
    *(undefined2 *)(param_1 + 0x1e) = 0x1e;
  }
  iVar2 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x800;
  iVar1 = *(char *)(param_1 + 0x13) * 0x1c;
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
  }
  else {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  if (*(short *)(param_1 + 0x1e) < 1) {
    *(undefined1 *)(iVar2 + 0x144) = 0;
    zz_006de10_(iVar2,0);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + *(short *)(&DAT_803188fa + iVar1) * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fce7704),&local_28);
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_1 + 0x1e) ^ 0x80000000;
    zz_0046588_((double)((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80438ec0) /
                        FLOAT_80438ec8),(float *)(param_1 + 0x16c),&local_28,
                (float *)(param_1 + 0x20));
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + *(short *)(&DAT_803188fa + iVar1) * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fce76f8),&local_28);
    *(float *)(param_1 + 0x144) = local_28;
    *(undefined4 *)(param_1 + 0x148) = local_24;
    *(undefined4 *)(param_1 + 0x14c) = local_20;
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_28,&local_28);
    zz_006ec1c_(&local_28,(float *)(param_1 + 0x38));
  }
  return;
}



// ==== 800e6e48  zz_00e6e48_ ====

void zz_00e6e48_(int param_1)

{
  byte bVar1;
  int iVar2;
  float *pfVar3;
  float afStack_28 [3];
  float afStack_1c [4];
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar2 = *(char *)(param_1 + 0x13) * 0x1c;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_803188fa + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fce7704),afStack_1c);
  gnt4_PSVECSubtract_bl(afStack_1c,(float *)(param_1 + 0x20),afStack_28);
  pfVar3 = (float *)(param_1 + 0x15c);
  zz_006eb4c_(afStack_28,pfVar3);
  if (*(float *)(&DAT_80318944 + (uint)bVar1 * 0x1c) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_80318944 + (uint)bVar1 * 0x1c);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar3,pfVar3);
  *(undefined1 *)(param_1 + 0x19) = 1;
  zz_008aff0_(param_1);
  *(undefined2 *)(param_1 + 0x1e) = 0x1e;
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800e6f48  FUN_800e6f48 ====

void FUN_800e6f48(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800e6f54  FUN_800e6f54 ====

void FUN_800e6f54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e6f74  FUN_800e6f74 ====

void FUN_800e6f74(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  uint uVar2;
  undefined8 uVar3;
  double dVar4;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  uVar2 = 1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
    uVar2 = 0x44;
  }
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar4 = (double)FLOAT_80438ecc;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar4 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_80438ec0)),afStack_48,0x7a);
  pfVar1 = afStack_48;
  uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar2);
  return;
}



// ==== 800e7018  zz_00e7018_ ====

void zz_00e7018_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,0x1f,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0x11;
    puVar2[0x11] = 0;
    puVar2[0x13] = 0x80;
    *(code **)(puVar2 + 0xc) = FUN_800e7134;
    *(code **)(puVar2 + 0x10c) = FUN_800e7418;
    uVar1 = param_2[1];
    *(undefined4 *)(puVar2 + 0x20) = *param_2;
    *(undefined4 *)(puVar2 + 0x24) = uVar1;
    *(undefined4 *)(puVar2 + 0x28) = param_2[2];
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



// ==== 800e7134  FUN_800e7134 ====

void FUN_800e7134(int param_1)

{
  (*(code *)(&PTR_FUN_80318978)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800e7170  FUN_800e7170 ====

void FUN_800e7170(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int *piVar1;
  int iVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  piVar1 = zz_0006dc8_((uint)*(byte *)(param_9 + 0x13) << 6);
  *(int **)(param_9 + 0xdc) = piVar1;
  if (piVar1 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(code **)(param_9 + 0x100) = FUN_800e7544;
    uVar6 = zz_0089100_(param_9,0x21,1);
    zz_000744c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)0x2b,(uint)*(byte *)(param_9 + 0x13),
                (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
    iVar4 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    for (; iVar4 < (int)(uint)*(byte *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
      iVar3 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5;
      zz_00e7610_(iVar3,0);
      zz_00091e4_((double)*(float *)(iVar3 + 0x28),iVar2);
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
      iVar5 = iVar5 + 0x40;
    }
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800e7280  FUN_800e7280 ====

/* WARNING: Removing unreachable block (ram,0x800e73a0) */
/* WARNING: Removing unreachable block (ram,0x800e7290) */

void FUN_800e7280(int param_1)

{
  float fVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  
  iVar2 = *(int *)(*(int *)(param_1 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  dVar7 = (double)FLOAT_80438ed0;
  iVar6 = 0;
  for (iVar5 = 0; iVar5 < (int)(uint)*(byte *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar6;
    if (((double)*(float *)(iVar4 + 0x28) < dVar7) &&
       (fVar1 = (float)((double)*(float *)(iVar4 + 0x28) + DOUBLE_80438ed8),
       *(float *)(iVar4 + 0x28) = fVar1, dVar7 <= (double)fVar1)) {
      *(float *)(iVar4 + 0x28) = (float)dVar7;
    }
    fVar1 = *(float *)(iVar4 + 0x34) - *(float *)(iVar4 + 0x2c);
    *(float *)(iVar4 + 0x34) = fVar1;
    if ((double)fVar1 < dVar7) {
      zz_00e7610_(iVar4,1);
    }
    *(float *)(iVar4 + 0x1c) =
         (*(float *)(iVar4 + 0x38) * *(float *)(iVar4 + 0x34)) / *(float *)(iVar4 + 0x30);
    zz_00091e4_((double)*(float *)(iVar4 + 0x28),iVar2);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
    iVar6 = iVar6 + 0x40;
  }
  cVar3 = zz_008b290_();
  if ((cVar3 == '\0') || ('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800e73d0  FUN_800e73d0 ====

void FUN_800e73d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e7418  FUN_800e7418 ====

/* WARNING: Removing unreachable block (ram,0x800e74c0) */

void FUN_800e7418(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  float afStack_48 [13];
  
  iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  iVar7 = 0;
  for (iVar6 = 0; iVar6 < (int)(uint)*(byte *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    uVar4 = 1;
    pfVar5 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar7);
    zz_00484e8_(afStack_48,pfVar5,pfVar5 + 3,1);
    pfVar5 = pfVar5 + 6;
    uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar5);
    if (iVar2 == 0) {
      pfVar5 = (float *)&DAT_80438ee8;
      gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80438ee0,
                       0x495,&DAT_80438ee8,uVar4,in_r7,in_r8,in_r9,in_r10);
    }
    uVar8 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
    *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
    if (iVar2 != 0) {
      uVar3 = *(uint *)(iVar2 + 0x14);
      bVar1 = false;
      if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
        bVar1 = true;
      }
      if (!bVar1) {
        gnt4_HSD_JObjSetMtxDirtySub_bl
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                   (undefined *)pfVar5,uVar4,in_r7,in_r8,in_r9,in_r10);
      }
    }
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
    iVar7 = iVar7 + 0x40;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 800e7544  FUN_800e7544 ====

void FUN_800e7544(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float afStack_48 [13];
  
  iVar3 = 0;
  for (iVar2 = 0; iVar2 < (int)(uint)*(byte *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
    gnt4_PSMTXIdentity_bl(afStack_48);
    zz_00457d4_('y',afStack_48,afStack_48,*(short *)((int)pfVar1 + 0x26));
    zz_00457d4_('x',afStack_48,afStack_48,*(short *)(pfVar1 + 9));
    gnt4_PSMTXMultVec_bl(afStack_48,(float *)&DAT_802b0cc0,pfVar1);
    gnt4_PSQUATScale_bl((double)pfVar1[0xd],pfVar1,pfVar1);
    gnt4_PSVECAdd_bl(pfVar1,(float *)(param_1 + 0x20),pfVar1);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar1,pfVar1 + 3);
    iVar3 = iVar3 + 0x40;
  }
  return;
}



// ==== 800e7610  zz_00e7610_ ====

void zz_00e7610_(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  uVar3 = zz_00055fc_();
  *(float *)(param_1 + 0x3c) =
       FLOAT_80438ef4 * (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438f10) +
       FLOAT_80438ef0;
  uVar3 = zz_00055fc_();
  *(float *)(param_1 + 0x38) =
       FLOAT_80438efc * (float)((double)CONCAT44(0x43300000,uVar3 & 7) - DOUBLE_80438f10) +
       FLOAT_80438ef8;
  if (param_2 == 0) {
    uVar3 = zz_00055fc_();
    *(float *)(param_1 + 0x30) =
         FLOAT_80438f00 * (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438f10) +
         FLOAT_80438efc;
  }
  else {
    uVar3 = zz_00055fc_();
    *(float *)(param_1 + 0x30) =
         FLOAT_80438ef4 * (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80438f10) +
         FLOAT_80438f04;
  }
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x30);
  uVar3 = zz_00055fc_();
  *(short *)(param_1 + 0x24) = (short)(uVar3 << 8);
  uVar3 = zz_00055fc_();
  fVar1 = FLOAT_80438f08;
  *(short *)(param_1 + 0x26) = (short)(uVar3 << 8);
  fVar2 = FLOAT_80438f0c;
  *(float *)(param_1 + 0x28) = fVar1;
  fVar1 = FLOAT_80438ed0;
  *(float *)(param_1 + 0x2c) = fVar2;
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x38);
  *(float *)(param_1 + 0x20) = fVar1;
  return;
}



// ==== 800e7758  zz_00e7758_ ====

void zz_00e7758_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x205) || (*(short *)(param_1 + 1000) == 0x209)) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x13] = param_3;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800e7878;
    *(code **)(puVar1 + 0x10c) = FUN_800e7bd4;
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



// ==== 800e7878  FUN_800e7878 ====

void FUN_800e7878(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803189d0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800e78cc  FUN_800e78cc ====

void FUN_800e78cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x59;
  fVar1 = FLOAT_80438f18;
  iVar3 = *(char *)(param_9 + 0x13) * 0x1c;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80318998 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_803189ac + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803189a8 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803189b0 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031899c + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803189a0 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(*(char *)(param_9 + 0x11) * 8 + -0x7fce7678 +
                              *(char *)(param_9 + 0x13) * 4),iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar6 + 0xc28;
  iVar4 = *(int *)(*(char *)(param_9 + 0x11) * 8 + -0x7fce7678 + *(char *)(param_9 + 0x13) * 4);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438f1c,*(int *)(param_9 + 0xe4));
  iVar6 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031899a + iVar3));
  if (iVar6 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
    *(undefined2 *)(param_9 + 0x1c6) = 10000;
    *(undefined2 *)(param_9 + 0x1c8) = 10000;
    *(undefined2 *)(param_9 + 0x1c4) = 10000;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 2;
    zz_00e7a84_(param_9);
  }
  return;
}



// ==== 800e7a84  zz_00e7a84_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_00e7a84_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0) ||
     ((*(uint *)(iVar1 + 0x5e0) & 0x10000000) != 0)) {
    *(undefined2 *)(param_1 + 0x272) = *(undefined2 *)(iVar1 + 0x272);
  }
  else {
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
  }
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(iVar1 + 0xc0);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  if (*(char *)(param_1 + 0x13) != '\0') {
    if (*(char *)(iVar1 + 0x582) != '\x01') {
      *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x800;
      if (*(short *)(&DAT_803189a6 + *(char *)(param_1 + 0x13) * 0x1c) <= *(short *)(param_1 + 0x74)
         ) {
        return;
      }
      *(short *)(param_1 + 0x74) = *(short *)(&DAT_803189a6 + *(char *)(param_1 + 0x13) * 0x1c);
      return;
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x800;
    if (*(short *)(param_1 + 0x74) < 1) {
      return;
    }
    *(undefined2 *)(param_1 + 0x74) = 0;
    return;
  }
  if (*(char *)(iVar1 + 0x582) != '\0') {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x800;
    if (*(short *)(param_1 + 0x74) <= _DAT_803189a6) {
      return;
    }
    *(short *)(param_1 + 0x74) = _DAT_803189a6;
    return;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x800;
  if (-1 < *(short *)(param_1 + 0x74)) {
    return;
  }
  *(undefined2 *)(param_1 + 0x74) = 0;
  return;
}



// ==== 800e7b88  FUN_800e7b88 ====

void FUN_800e7b88(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 800e7bb4  FUN_800e7bb4 ====

void FUN_800e7bb4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800e7bd4  FUN_800e7bd4 ====

void FUN_800e7bd4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x59a) == '\0') {
    uVar2 = zz_0007cac_((double)FLOAT_80438f1c,*(int *)(param_9 + 0xe4));
  }
  else {
    uVar2 = zz_0007cac_((double)(*(float *)(iVar1 + 0x150) * *(float *)(iVar1 + 0x154)),
                        *(int *)(param_9 + 0xe4));
  }
  if (*(char *)(iVar1 + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x47);
  return;
}



// ==== 800e7c68  FUN_800e7c68 ====

void FUN_800e7c68(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 2) || (*(short *)(param_1 + 1000) == 0xb)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_3;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800e7d88;
    *(code **)(puVar1 + 0x10c) = FUN_800e812c;
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



// ==== 800e7d88  FUN_800e7d88 ====

void FUN_800e7d88(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80318a60)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



