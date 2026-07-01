// ==== 800562b8  FUN_800562b8 ====

/* WARNING: Removing unreachable block (ram,0x80056838) */
/* WARNING: Removing unreachable block (ram,0x800562c8) */

void FUN_800562b8(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  float fVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  double dVar11;
  
  *(undefined1 *)(param_1 + 0x660) = **(undefined1 **)(param_1 + 0x4b0);
  *(undefined1 *)(param_1 + 0x661) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 1);
  *(undefined1 *)(param_1 + 0x591) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 4);
  *(undefined2 *)(param_1 + 0x59c) = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 0xa8);
  *(undefined2 *)(param_1 + 0x59e) = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 0xaa);
  *(undefined4 *)(param_1 + 0x850) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x80);
  *(undefined4 *)(param_1 + 0x854) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x84);
  *(undefined4 *)(param_1 + 0x858) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x88);
  *(undefined4 *)(param_1 + 0x85c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x8c);
  *(undefined4 *)(param_1 + 0x860) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x90);
  *(undefined4 *)(param_1 + 0x864) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x94);
  *(undefined4 *)(param_1 + 0x868) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x134);
  *(undefined4 *)(param_1 + 0x86c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x138);
  *(undefined4 *)(param_1 + 0x870) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x13c);
  *(undefined4 *)(param_1 + 0x874) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x140);
  *(undefined4 *)(param_1 + 0x878) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x144);
  *(undefined4 *)(param_1 + 0x87c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x148);
  *(undefined4 *)(param_1 + 0x880) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x14c);
  *(undefined4 *)(param_1 + 0x884) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x150);
  *(undefined4 *)(param_1 + 0x888) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x154);
  fVar4 = FLOAT_80437258;
  *(undefined1 *)(param_1 + 0x589) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0xb6);
  iVar7 = 0;
  *(float *)(param_1 + 0x5f4) = fVar4;
  *(float *)(param_1 + 0x768) = fVar4;
  *(undefined1 *)(param_1 + 0x8cc) = *(undefined1 *)(*(int *)(param_1 + 0x4ac) + 0x182);
  *(undefined2 *)(param_1 + 0x6be) = **(undefined2 **)(param_1 + 0x4ac);
  *(undefined2 *)(param_1 + 0x6c2) = **(undefined2 **)(param_1 + 0x4ac);
  *(undefined2 *)(param_1 + 0x6c0) = 100;
  uVar2 = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 2);
  *(undefined2 *)(param_1 + 0x6c6) = uVar2;
  *(undefined2 *)(param_1 + 0x6c4) = uVar2;
  uVar2 = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 2);
  *(undefined2 *)(param_1 + 0x7dc) = uVar2;
  *(undefined2 *)(param_1 + 0x7d6) = uVar2;
  uVar6 = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x98);
  *(undefined4 *)(param_1 + 0x208) = uVar6;
  *(undefined4 *)(param_1 + 0x204) = uVar6;
  *(float *)(param_1 + 0x664) = fVar4;
  puVar9 = (&PTR_DAT_802f2988)[*(char *)(param_1 + 1000)] +
           ((int)*(char *)(param_1 + 0x3ee) +
           (uint)*(byte *)(param_1 + 0x3e9) * 0x14 +
           (int)(char)(&DAT_804339e8)[*(char *)(param_1 + 0x3ec)]) * 0x12;
  iVar10 = 2;
  do {
    uVar5 = countLeadingZeros(iVar7);
    iVar8 = param_1 + (~-(uVar5 >> 5 & 1) & 2) * 8;
    *(undefined2 *)(iVar8 + 0x774) = *(undefined2 *)(puVar9 + 2);
    *(undefined2 *)(iVar8 + 0x776) = *(undefined2 *)(puVar9 + 4);
    uVar6 = *(undefined4 *)(puVar9 + 6);
    *(undefined4 *)(iVar8 + 0x78c) = *(undefined4 *)(puVar9 + 2);
    *(undefined4 *)(iVar8 + 0x790) = uVar6;
    if (*(short *)(iVar8 + 0x774) == 0) {
      sVar3 = *(short *)(iVar8 + 0x790);
      if (sVar3 == 1) {
        *(float *)(iVar8 + 0x778) =
             *(float *)(iVar8 + 0x778) +
             (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x792) ^ 0x80000000) -
                    DOUBLE_80437290);
      }
      else if (sVar3 < 1) {
        if (-1 < sVar3) {
          *(float *)(iVar8 + 0x778) =
               (float)((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x792) ^ 0x80000000) -
                      DOUBLE_80437290);
        }
      }
      else if (sVar3 < 4) {
        *(float *)(iVar8 + 0x778) = FLOAT_80437250;
      }
    }
    else {
      *(float *)(iVar8 + 0x778) = FLOAT_80437250;
    }
    puVar9 = puVar9 + 8;
    iVar7 = iVar7 + 1;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x11) == '\0') {
    *(undefined1 *)(param_1 + 0x7cd) = 0;
  }
  else if (*(char *)(param_1 + 0x661) == '\x02') {
    *(undefined1 *)(param_1 + 0x7cd) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x7cd) = 1;
  }
  dVar11 = (double)FLOAT_80437250;
  iVar10 = 0;
  iVar7 = param_1;
  do {
    if (*(char *)(*(int *)(param_1 + 0x4b0) + iVar10 + 0xbb) != -1) {
      FUN_8013bd80(param_1,(char)iVar10);
    }
    *(float *)(iVar7 + 0x63c) = (float)dVar11;
    iVar10 = iVar10 + 1;
    *(float *)(iVar7 + 0x648) = (float)dVar11;
    iVar7 = iVar7 + 4;
  } while (iVar10 < 3);
  iVar7 = 0;
  *(undefined1 *)(param_1 + 0x655) = 0;
  iVar10 = param_1 + 0x78c;
  iVar8 = 3;
  do {
    if (*(short *)(iVar10 + 2) == 0) {
      if (*(char *)(*(int *)(param_1 + 0x4b0) + iVar7 + 0xb8) == -1) {
        *(undefined1 *)(param_1 + iVar7 + 0x8cd) = 0;
      }
      else {
        *(undefined1 *)(param_1 + iVar7 + 0x8cd) = 1;
      }
    }
    else if (*(short *)(iVar10 + 4) == 3) {
      *(undefined1 *)(param_1 + iVar7 + 0x8cd) = 1;
    }
    else {
      *(undefined1 *)(param_1 + iVar7 + 0x8cd) = 2;
    }
    if (*(char *)(*(int *)(param_1 + 0x4b0) + iVar7 + 0xbb) != -1) {
      *(char *)(param_1 + iVar7 + 0x8cd) = *(char *)(param_1 + iVar7 + 0x8cd) + '\x03';
    }
    iVar7 = iVar7 + 1;
    iVar10 = iVar10 + 8;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  cVar1 = *(char *)(param_1 + 0x8cd);
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x8d0) = *(undefined1 *)(param_1 + 0x8ce);
  }
  else if (cVar1 == '\x03') {
    *(char *)(param_1 + 0x8d0) = *(char *)(param_1 + 0x8ce) + '\x03';
    if ('\x05' < *(char *)(param_1 + 0x8d0)) {
      *(char *)(param_1 + 0x8d0) = *(char *)(param_1 + 0x8d0) + -3;
    }
  }
  else {
    *(char *)(param_1 + 0x8d0) = cVar1;
  }
  if (*(char *)(param_1 + 0x8cf) == '\0') {
    if (((*(char *)(param_1 + 0x661) == '\x02') || (*(char *)(param_1 + 0x661) == '\x05')) &&
       (*(char *)(*(int *)(param_1 + 0x4f0) + 0x41) != -1)) {
      *(undefined1 *)(param_1 + 0x8d1) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x8d1) = 0;
    }
  }
  else {
    *(char *)(param_1 + 0x8d1) = *(char *)(param_1 + 0x8cf);
  }
  *(undefined4 *)(param_1 + 0x88c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xb8);
  *(undefined4 *)(param_1 + 0x890) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xbc);
  *(undefined4 *)(param_1 + 0x894) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xc0);
  *(undefined4 *)(param_1 + 0x898) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xc4);
  *(undefined4 *)(param_1 + 0x89c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 200);
  *(undefined4 *)(param_1 + 0x8a0) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xcc);
  *(undefined4 *)(param_1 + 0x8a4) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xd0);
  *(undefined4 *)(param_1 + 0x8a8) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xd4);
  *(undefined4 *)(param_1 + 0x8ac) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xd8);
  *(undefined4 *)(param_1 + 0x8b0) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xdc);
  *(undefined4 *)(param_1 + 0x8b4) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xe0);
  *(undefined4 *)(param_1 + 0x8b8) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xe4);
  *(undefined4 *)(param_1 + 0x8bc) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xe8);
  *(undefined4 *)(param_1 + 0x8c0) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0xec);
  zz_0006238_(param_1);
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    FUN_8001c2c8(param_1);
  }
  return;
}



// ==== 8005685c  zz_005685c_ ====

void zz_005685c_(int param_1)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x5e8) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(param_1 + 0x5ec) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x5f0) = *(undefined4 *)(param_1 + 0x34);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x76) = *(undefined4 *)(param_1 + 0x70);
  *(undefined2 *)(param_1 + 0x7a) = *(undefined2 *)(param_1 + 0x74);
  *(undefined4 *)(param_1 + 0x1d6a) = *(undefined4 *)(param_1 + 0x1d64);
  *(undefined2 *)(param_1 + 0x1d6e) = *(undefined2 *)(param_1 + 0x1d68);
  *(undefined4 *)(param_1 + 0x6d4) = *(undefined4 *)(param_1 + 0x6d0);
  iVar1 = *(int *)(param_1 + 0xcc);
  if (iVar1 == 0) {
    return;
  }
  if ((*(char *)(iVar1 + 0x83) == '\0') &&
     ((*(byte *)(iVar1 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) == 0)) {
    return;
  }
  *(undefined4 *)(param_1 + 0x524) = *(undefined4 *)(param_1 + 0x518);
  *(undefined4 *)(param_1 + 0x528) = *(undefined4 *)(param_1 + 0x51c);
  *(undefined4 *)(param_1 + 0x52c) = *(undefined4 *)(param_1 + 0x520);
  return;
}



// ==== 80056900  FUN_80056900 ====

void FUN_80056900(char *param_1)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  undefined4 *unaff_r31;
  
  cVar5 = param_1[0x488];
  cVar2 = param_1[0x3e6];
  bVar1 = cVar5 == '\x03';
  if (bVar1) {
    param_1[0x488] = '\0';
    cVar5 = '\0';
  }
  if ((PTR_DAT_80433930[0x32] == '\0') && (PTR_DAT_80433934[0x1829] != '\0')) {
    cVar5 = '\x02';
  }
  if ('\x04' < (char)PTR_DAT_80433934[0x45]) {
    cVar5 = '\x02';
  }
  if (cVar2 == '\0') {
    iVar3 = (int)param_1[0x3e4] >> 0x1f;
    iVar3 = (iVar3 * 4 | (uint)(param_1[0x3e4] * 0x40000000 + iVar3) >> 0x1e) - iVar3;
    unaff_r31 = &DAT_803c727c + iVar3 * 8;
    param_1[0x5c9] = (&DAT_803c7291)[iVar3 * 0x20];
  }
  *(undefined4 *)(param_1 + 0x5b8) = *(undefined4 *)(param_1 + 0x5b4);
  if (cVar5 != '\x01') {
    if (cVar5 == '\0') {
      uVar4 = zz_008bbc0_((int)param_1[0x3e4],(&DAT_803c727c)[param_1[0x3e4] * 8]);
      *(uint *)(param_1 + 0x5b4) = uVar4;
      param_1[0x5ca] = *(char *)((int)unaff_r31 + 0x16);
      param_1[0x5cb] = *(char *)((int)unaff_r31 + 0x17);
      param_1[0x5cc] = *(char *)(unaff_r31 + 6);
      param_1[0x5cd] = *(char *)((int)unaff_r31 + 0x19);
      param_1[0x5ce] = *(char *)((int)unaff_r31 + 0x1a);
      param_1[0x5cf] = *(char *)((int)unaff_r31 + 0x1b);
    }
    else {
      param_1[0x5cf] = '\0';
      param_1[0x5ce] = '\0';
      param_1[0x5cd] = '\0';
      param_1[0x5cc] = '\0';
      param_1[0x5cb] = '\0';
      param_1[0x5ca] = '\0';
      param_1[0x5b4] = '\0';
      param_1[0x5b5] = '\0';
      param_1[0x5b6] = '\0';
      param_1[0x5b7] = '\0';
    }
  }
  if ((cVar2 != '\0') && (cVar5 != '\x02')) {
    zz_001c9d0_(param_1);
  }
  param_1[0x5c4] = '\0';
  param_1[0x5c5] = '\0';
  param_1[0x5c6] = '\0';
  param_1[0x5c7] = '\0';
  *(uint *)(param_1 + 0x5bc) = *(uint *)(param_1 + 0x5b4) & ~*(uint *)(param_1 + 0x5b8);
  *(uint *)(param_1 + 0x5c0) = *(uint *)(param_1 + 0x5b8) & ~*(uint *)(param_1 + 0x5b4);
  if (bVar1) {
    param_1[0x5c0] = '\0';
    param_1[0x5c1] = '\0';
    param_1[0x5c2] = '\0';
    param_1[0x5c3] = '\0';
    param_1[0x5bc] = '\0';
    param_1[0x5bd] = '\0';
    param_1[0x5be] = '\0';
    param_1[0x5bf] = '\0';
  }
  return;
}



// ==== 80056aa8  FUN_80056aa8 ====

/* WARNING: Removing unreachable block (ram,0x80056c3c) */

void FUN_80056aa8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  
  if (*(char *)(param_9 + 0x4a0) != '\x02') {
    iVar6 = 0;
    if (((-1 < (char)PTR_DAT_80433930[0x28]) &&
        (uVar2 = zz_0010514_((int)(char)(&DAT_803c7695)[(char)PTR_DAT_80433930[0x28] * 0x3e4]),
        uVar2 == 0)) &&
       (param_11 = (undefined *)(int)*(short *)(param_9 + 0x270),
       ((uint)param_11 & 1 << (int)(char)PTR_DAT_80433930[0x28]) != 0)) {
      iVar6 = 1;
    }
    if (*(char *)(param_9 + 0x59a) != '\0') {
      iVar6 = 1;
    }
    dVar10 = (double)*(float *)(param_9 + 0x720);
    if ((((double)FLOAT_80437250 < dVar10) && (iVar6 == 0)) &&
       ((*(int *)(PTR_DAT_80433934 + 0xb0) + (int)*(char *)(param_9 + 0x3e4) & 2U) != 0)) {
      iVar6 = 1;
    }
    *(char *)(param_9 + 0xae) = (char)iVar6;
    if ((*(byte *)(param_9 + 0x48a) & 6) == 0) {
      iVar3 = zz_0006f98_(param_9);
      iVar9 = iVar3 + iVar6 * 0x80;
      uVar2 = 1;
      iVar8 = param_9;
      for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x1d90); iVar7 = iVar7 + 1) {
        if ((*(uint *)(param_9 + 0x76c) & uVar2) == 0) {
          uVar11 = gnt4_HSD_JObjSetFlags
                             (dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar9 + 0x608),0x10,param_11,param_12,param_13,param_14,
                              param_15,param_16);
        }
        else {
          uVar11 = gnt4_HSD_JObjClearFlags
                             (dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(iVar9 + 0x608),0x10,param_11,param_12,param_13,param_14,
                              param_15,param_16);
        }
        iVar5 = *(int *)(iVar9 + 0x608);
        if (iVar5 == 0) {
          param_11 = &DAT_804372a8;
          uVar11 = gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    &DAT_804372a0,0x495,&DAT_804372a8,param_12,param_13,param_14,
                                    param_15,param_16);
        }
        if (iVar8 == -0x8d4) {
          param_11 = &DAT_804372b0;
          gnt4___assert_bl(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_804372a0,0x496,&DAT_804372b0,param_12,param_13,param_14,param_15,
                           param_16);
        }
        dVar10 = (double)gnt4_PSMTXCopy_bl((float *)(iVar8 + 0x8d4),(float *)(iVar5 + 0x44));
        *(uint *)(iVar5 + 0x14) = *(uint *)(iVar5 + 0x14) | 0x3800000;
        if (iVar5 != 0) {
          uVar4 = *(uint *)(iVar5 + 0x14);
          bVar1 = false;
          if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            dVar10 = (double)gnt4_HSD_JObjSetMtxDirtySub_bl
                                       (dVar10,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,iVar5,uVar4,param_11,param_12,param_13,param_14,
                                        param_15,param_16);
          }
        }
        uVar2 = uVar2 << 1;
        iVar9 = iVar9 + 4;
        iVar8 = iVar8 + 0x30;
      }
      zz_00097b4_(*(int *)(iVar3 + iVar6 * 0x80 + 0x708),0x47);
      if (*(code **)(param_9 + 0x4d4) != (code *)0x0) {
        (**(code **)(param_9 + 0x4d4))(param_9);
      }
      zz_004fcfc_(param_9,iVar6);
    }
  }
  return;
}



// ==== 80056ce0  zz_0056ce0_ ====

void zz_0056ce0_(int param_1)

{
  (**(code **)((&PTR_PTR_802d3224)[*(char *)(param_1 + 1000)] + (uint)*(byte *)(param_1 + 0x3e9) * 4
              ))();
  return;
}



// ==== 80056d28  FUN_80056d28 ====

void FUN_80056d28(char *param_1)

{
  char cVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  bool bVar9;
  double dVar10;
  float local_28;
  float local_24;
  undefined4 local_20;
  float fStack_1c;
  undefined4 local_18;
  
  if (PTR_DAT_80433930[0x32] == '\0') {
    if (param_1[0x43b] == '\0') {
      param_1[0x43b] = '\x01';
      fVar3 = FLOAT_80437250;
      if ((param_1[0x3e6] == '\0') || (param_1[0x37f] == '\0')) {
        *(undefined4 *)(param_1 + 0x20) =
             *(undefined4 *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1604);
        *(undefined4 *)(param_1 + 0x28) =
             *(undefined4 *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x160c);
        if (fVar3 == *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608)) {
          *(float *)(param_1 + 0x24) = FLOAT_804372b8;
          *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
          dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                                (float *)(param_1 + 0x20));
          *(float *)(param_1 + 0x24) = (float)dVar10;
          cVar1 = param_1[0x661];
          if (cVar1 == '\x03') {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c0;
          }
          else if (cVar1 == '\x04') {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
          }
          else if (cVar1 == '\x05') {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
          }
          else if (cVar1 == '\b') {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
          }
          else if ((cVar1 == '\t') || (cVar1 == '\v')) {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c0;
          }
          else if (cVar1 == '\n') {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c8;
          }
        }
        else {
          *(float *)(param_1 + 0x24) = *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608);
        }
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
      }
      else {
        fVar3 = *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1604);
        bVar9 = FLOAT_804372b4 != fVar3;
        if (bVar9) {
          *(float *)(param_1 + 0x20) = fVar3;
          *(undefined4 *)(param_1 + 0x28) =
               *(undefined4 *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x160c);
        }
        else {
          FUN_80057634(param_1);
        }
        if (FLOAT_80437250 == *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608)) {
          *(float *)(param_1 + 0x24) = FLOAT_804372b8;
          *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
          dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                                (float *)(param_1 + 0x20));
          *(float *)(param_1 + 0x24) = (float)dVar10;
        }
        else if (bVar9) {
          *(float *)(param_1 + 0x24) = *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608);
        }
        else {
          *(float *)(param_1 + 0x24) = FLOAT_804372b8;
          *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
          dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                                (float *)(param_1 + 0x20));
          *(float *)(param_1 + 0x24) = (float)dVar10;
          if (*(float *)(param_1 + 0x24) <=
              *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608)) {
            *(float *)(param_1 + 0x24) =
                 *(float *)(PTR_DAT_80433934 + param_1[0x3e4] * 0xc + 0x1608);
          }
          else {
            *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372bc;
          }
        }
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
      }
      iVar5 = (int)(char)PTR_DAT_80433934[param_1[0x3e4] + 0x15fe];
      if (iVar5 == 0x78) {
        iVar5 = FUN_800452a0(-(double)*(float *)(param_1 + 0x20),-(double)*(float *)(param_1 + 0x28)
                            );
        *(short *)(param_1 + 0x72) = (short)iVar5;
      }
      else if (iVar5 == 0x38) {
        iVar8 = 0;
        piVar7 = &DAT_803c4e84;
        iVar5 = 0;
        do {
          if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar8) != 0) {
            iVar6 = *piVar7;
            if (*(char *)(iVar6 + 0x43b) == '\0') {
              fVar3 = *(float *)(PTR_DAT_80433934 + iVar5 + 0x1604) - *(float *)(param_1 + 0x20);
              fVar4 = *(float *)(PTR_DAT_80433934 + iVar5 + 0x160c) - *(float *)(param_1 + 0x28);
            }
            else {
              fVar3 = *(float *)(iVar6 + 0x20) - *(float *)(param_1 + 0x20);
              fVar4 = *(float *)(iVar6 + 0x28) - *(float *)(param_1 + 0x28);
            }
            iVar6 = FUN_800452a0((double)fVar3,(double)fVar4);
            *(short *)(param_1 + 0x72) = (short)iVar6;
          }
          iVar8 = iVar8 + 1;
          iVar5 = iVar5 + 0xc;
          piVar7 = piVar7 + 1;
        } while (iVar8 < 6);
      }
      else if (iVar5 == 0x18) {
        bVar9 = false;
        piVar7 = &DAT_803c4e84;
        iVar8 = 0;
        iVar5 = 0;
        do {
          if ((PTR_DAT_80433934[iVar8 + 0xcb] == '\0') &&
             (((int)(char)PTR_DAT_80433930[2] & 1 << iVar8) == 0)) {
            iVar6 = *piVar7;
            if (*(char *)(iVar6 + 0x43b) == '\0') {
              fVar3 = *(float *)(PTR_DAT_80433934 + iVar5 + 0x1604) - *(float *)(param_1 + 0x20);
              fVar4 = *(float *)(PTR_DAT_80433934 + iVar5 + 0x160c) - *(float *)(param_1 + 0x28);
            }
            else {
              fVar3 = *(float *)(iVar6 + 0x20) - *(float *)(param_1 + 0x20);
              fVar4 = *(float *)(iVar6 + 0x28) - *(float *)(param_1 + 0x28);
            }
            iVar6 = FUN_800452a0((double)fVar3,(double)fVar4);
            *(short *)(param_1 + 0x72) = (short)iVar6;
            bVar9 = true;
          }
          iVar8 = iVar8 + 1;
          iVar5 = iVar5 + 0xc;
          piVar7 = piVar7 + 1;
        } while (iVar8 < 6);
        if (!bVar9) {
          iVar5 = FUN_800452a0(-(double)*(float *)(param_1 + 0x20),
                               -(double)*(float *)(param_1 + 0x28));
          *(short *)(param_1 + 0x72) = (short)iVar5;
        }
      }
      else {
        *(short *)(param_1 + 0x72) = (short)(iVar5 << 8);
      }
      PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] =
           PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] & 3;
      param_1[0x43c] = PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] & 1;
      PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] =
           PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] + '\x01';
    }
    else {
      cVar1 = param_1[0x661];
      if (((cVar1 == '\b') || (cVar1 == '\t')) || (cVar1 == '\v')) {
        zz_00579dc_((int)param_1);
      }
      else {
        FUN_80057634(param_1);
        *(float *)(param_1 + 0x24) = FLOAT_804372b8;
        *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
        dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                              (float *)(param_1 + 0x20));
        *(float *)(param_1 + 0x24) = (float)dVar10;
        cVar1 = param_1[0x661];
        if (cVar1 == '\x03') {
          *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c0;
        }
        else if (cVar1 == '\x04') {
          *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
        }
        else if (cVar1 == '\x05') {
          *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
        }
        else if (cVar1 == '\n') {
          *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c8;
        }
      }
      iVar5 = FUN_800452a0(-(double)*(float *)(param_1 + 0x20),-(double)*(float *)(param_1 + 0x28));
      *(short *)(param_1 + 0x72) = (short)iVar5;
    }
  }
  else {
    cVar1 = param_1[0x661];
    if (((cVar1 == '\b') || (cVar1 == '\t')) || (cVar1 == '\v')) {
      zz_00579dc_((int)param_1);
    }
    else if (param_1[0x43b] == '\0') {
      param_1[0x43b] = '\x01';
      fVar3 = FLOAT_804372b8;
      iVar5 = (int)param_1[0x88];
      PTR_DAT_80433934[iVar5 * 0x3c + 0xfe] = PTR_DAT_80433934[iVar5 * 0x3c + 0xfe] & 3;
      bVar2 = PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe];
      param_1[0x43c] = bVar2 & 1;
      PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] =
           PTR_DAT_80433934[param_1[0x88] * 0x3c + 0xfe] + '\x01';
      iVar5 = (iVar5 * 8 + (char)bVar2 * 2 + (char)PTR_DAT_80433934[0x1c] * 0x10) * 4;
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(&DAT_802ddf00 + iVar5);
      *(float *)(param_1 + 0x24) = fVar3;
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(&DAT_802ddf04 + iVar5);
      if (PTR_DAT_80433934[0x1c] == '\x11') {
        if (FLOAT_804372cc <= *(float *)(param_1 + 0x20)) {
          if (FLOAT_804372d0 < *(float *)(param_1 + 0x20)) {
            *(float *)(param_1 + 0x20) = FLOAT_804372d0;
          }
        }
        else {
          *(float *)(param_1 + 0x20) = FLOAT_804372cc;
        }
        if (FLOAT_804372d4 <= *(float *)(param_1 + 0x28)) {
          if (FLOAT_804372d0 < *(float *)(param_1 + 0x28)) {
            *(float *)(param_1 + 0x28) = FLOAT_804372d0;
          }
        }
        else {
          *(float *)(param_1 + 0x28) = FLOAT_804372d4;
        }
      }
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
      dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                            (float *)(param_1 + 0x20));
      *(float *)(param_1 + 0x24) = (float)dVar10;
    }
    else {
      FUN_80057634(param_1);
      *(float *)(param_1 + 0x24) = FLOAT_804372b8;
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
      dVar10 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),(int)param_1,
                            (float *)(param_1 + 0x20));
      *(float *)(param_1 + 0x24) = (float)dVar10;
    }
    cVar1 = param_1[0x661];
    if (cVar1 == '\x03') {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c0;
    }
    else if (cVar1 == '\x04') {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
    }
    else if (cVar1 == '\x05') {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c4;
    }
    else if (cVar1 == '\n') {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_804372c8;
    }
    iVar5 = FUN_800452a0(-(double)*(float *)(param_1 + 0x20),-(double)*(float *)(param_1 + 0x28));
    *(short *)(param_1 + 0x72) = (short)iVar5;
  }
  local_28 = *(float *)(param_1 + 0x20);
  local_20 = *(undefined4 *)(param_1 + 0x28);
  local_24 = *(float *)(param_1 + 0x24) + *(float *)(DAT_8043625c + 0x34);
  iVar5 = zz_003f044_(&local_28,(float *)(param_1 + 0x20),&fStack_1c);
  if (iVar5 != 0) {
    *(undefined4 *)(param_1 + 0x24) = local_18;
  }
  local_28 = *(float *)(param_1 + 0x20);
  local_20 = *(undefined4 *)(param_1 + 0x28);
  local_24 = *(float *)(param_1 + 0x24) + *(float *)(DAT_8043625c + 0x34);
  iVar5 = FUN_80037b98((int)param_1,&local_28,(float *)(param_1 + 0x20),&fStack_1c);
  if (iVar5 != 0) {
    *(undefined4 *)(param_1 + 0x24) = local_18;
  }
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x5e8) = *(undefined4 *)(param_1 + 0x2c);
  *(undefined4 *)(param_1 + 0x5ec) = *(undefined4 *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x5f0) = *(undefined4 *)(param_1 + 0x34);
  *(undefined4 *)(param_1 + 0x76) = *(undefined4 *)(param_1 + 0x70);
  *(undefined2 *)(param_1 + 0x7a) = *(undefined2 *)(param_1 + 0x74);
  *(undefined4 *)(param_1 + 0x354) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x358) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x35c) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 80057634  FUN_80057634 ====

/* WARNING: Removing unreachable block (ram,0x800579bc) */
/* WARNING: Removing unreachable block (ram,0x800579b4) */
/* WARNING: Removing unreachable block (ram,0x800579ac) */
/* WARNING: Removing unreachable block (ram,0x80057654) */
/* WARNING: Removing unreachable block (ram,0x8005764c) */
/* WARNING: Removing unreachable block (ram,0x80057644) */

void FUN_80057634(char *param_1)

{
  float fVar1;
  short sVar2;
  uint uVar3;
  short sVar4;
  char *pcVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  
  uVar3 = zz_00055fc_();
  dVar9 = (double)FLOAT_80437250;
  sVar2 = (short)uVar3 << 0xc;
  dVar8 = (double)FLOAT_804372d8;
  sVar4 = 30000;
  iVar6 = 3;
  pcVar5 = DAT_803c4e84;
  dVar10 = dVar9;
  do {
    if ((((pcVar5 != param_1) && (*pcVar5 != '\0')) && (pcVar5[0x88] == param_1[0x88])) &&
       (*(short *)(pcVar5 + 0x1c6) <= sVar4)) {
      dVar10 = (double)*(float *)(pcVar5 + 0x20);
      dVar9 = (double)*(float *)(pcVar5 + 0x28);
      dVar8 = (double)*(float *)(&DAT_802dea40 +
                                (uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0xb7) * 4);
      sVar4 = *(short *)(pcVar5 + 0x1c6);
    }
    if (((pcVar5 + 0x1e00 != param_1) && (pcVar5[0x1e00] != '\0')) &&
       ((pcVar5[0x1e88] == param_1[0x88] && (*(short *)(pcVar5 + 0x1fc6) <= sVar4)))) {
      dVar10 = (double)*(float *)(pcVar5 + 0x1e20);
      dVar9 = (double)*(float *)(pcVar5 + 0x1e28);
      dVar8 = (double)*(float *)(&DAT_802dea40 +
                                (uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0xb7) * 4);
      sVar4 = *(short *)(pcVar5 + 0x1fc6);
    }
    pcVar5 = pcVar5 + 0x3c00;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  dVar7 = zz_0045204_(sVar2);
  *(float *)(param_1 + 0x20) = (float)(dVar8 * dVar7 + dVar10);
  dVar10 = zz_0045238_(sVar2);
  *(float *)(param_1 + 0x28) = (float)(dVar8 * dVar10 + dVar9);
  if ((PTR_DAT_80433930[0x32] == '\0') && (PTR_DAT_80433934[0x1c] == '\x10')) {
    fVar1 = *(float *)(param_1 + 0x20);
    if ((fVar1 < FLOAT_804372dc) ||
       (((FLOAT_804372e0 < fVar1 || (*(float *)(param_1 + 0x28) < FLOAT_804372dc)) ||
        (FLOAT_804372e0 < *(float *)(param_1 + 0x28))))) {
      dVar10 = (double)(fVar1 * fVar1 + *(float *)(param_1 + 0x28) * *(float *)(param_1 + 0x28));
      if ((double)FLOAT_80437250 < dVar10) {
        dVar8 = 1.0 / SQRT(dVar10);
        dVar8 = DOUBLE_804372e8 * dVar8 * -(dVar10 * dVar8 * dVar8 - DOUBLE_804372f0);
        dVar8 = DOUBLE_804372e8 * dVar8 * -(dVar10 * dVar8 * dVar8 - DOUBLE_804372f0);
        dVar10 = (double)(float)(dVar10 * DOUBLE_804372e8 * dVar8 *
                                          -(dVar10 * dVar8 * dVar8 - DOUBLE_804372f0));
      }
      if (dVar10 <= (double)FLOAT_804372f8) {
        fVar1 = (float)((double)FLOAT_804372f8 / dVar10);
        *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) * fVar1;
        *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) * fVar1;
      }
    }
    else {
      uVar3 = zz_00055fc_();
      *(float *)(param_1 + 0x20) =
           FLOAT_804372c0 + (float)((double)CONCAT44(0x43300000,uVar3 & 0x3f) - DOUBLE_80437300);
      uVar3 = zz_00055fc_();
      *(float *)(param_1 + 0x28) =
           FLOAT_804372c0 + (float)((double)CONCAT44(0x43300000,uVar3 & 0x3f) - DOUBLE_80437300);
    }
  }
  if (*(float *)(DAT_8043625c + 0x3c) <= *(float *)(param_1 + 0x20)) {
    if (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x20)) {
      *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38) - FLOAT_804372fc;
    }
  }
  else {
    *(float *)(param_1 + 0x20) = FLOAT_804372fc + *(float *)(DAT_8043625c + 0x3c);
  }
  if (*(float *)(DAT_8043625c + 0x44) <= *(float *)(param_1 + 0x28)) {
    if (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x28)) {
      *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x40) - FLOAT_804372fc;
    }
  }
  else {
    *(float *)(param_1 + 0x28) = FLOAT_804372fc + *(float *)(DAT_8043625c + 0x44);
  }
  if (PTR_DAT_80433934[0x1c] == '\x11') {
    if (FLOAT_804372cc <= *(float *)(param_1 + 0x20)) {
      if (FLOAT_804372d0 < *(float *)(param_1 + 0x20)) {
        *(float *)(param_1 + 0x20) = FLOAT_804372d0;
      }
    }
    else {
      *(float *)(param_1 + 0x20) = FLOAT_804372cc;
    }
    if (FLOAT_804372d4 <= *(float *)(param_1 + 0x28)) {
      if (FLOAT_804372d0 < *(float *)(param_1 + 0x28)) {
        *(float *)(param_1 + 0x28) = FLOAT_804372d0;
      }
    }
    else {
      *(float *)(param_1 + 0x28) = FLOAT_804372d4;
    }
  }
  return;
}



// ==== 800579dc  zz_00579dc_ ====

void zz_00579dc_(int param_1)

{
  char cVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x43b) == '\0') {
    *(undefined1 *)(param_1 + 0x43b) = 1;
    iVar2 = (int)*(char *)(param_1 + 0x88);
    PTR_DAT_80433934[iVar2 * 0x3c + 0xfe] = PTR_DAT_80433934[iVar2 * 0x3c + 0xfe] & 3;
    *(byte *)(param_1 + 0x43c) = PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xfe] & 1;
    cVar1 = *(char *)(param_1 + 0x43c);
    PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xfe] =
         PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xfe] + '\x01';
    iVar2 = iVar2 * 2 + (int)cVar1 + (char)PTR_DAT_80433934[0x1c] * 4;
  }
  else {
    iVar2 = *(char *)(param_1 + 0x88) * 2 + (int)*(char *)(param_1 + 0x43c) +
            (char)PTR_DAT_80433934[0x1c] * 4;
  }
  iVar2 = iVar2 * 0xc;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(&DAT_802de380 + iVar2);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(&DAT_802de384 + iVar2);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(&DAT_802de388 + iVar2);
  return;
}



// ==== 80057ad0  zz_0057ad0_ ====

void zz_0057ad0_(void)

{
  zz_0057b0c_(DAT_803c4e84);
  zz_0057b0c_(DAT_803c4e88);
  return;
}



// ==== 80057b0c  zz_0057b0c_ ====

void zz_0057b0c_(int param_1)

{
  zz_005685c_(param_1);
  (*(code *)(&PTR_FUN_802d3284)[*(char *)(param_1 + 0x18)])(param_1);
  if (*(char *)(param_1 + 0x18) == '\x01') {
    zz_0046720_(param_1);
  }
  zz_0006284_(param_1);
  return;
}



// ==== 80057b78  FUN_80057b78 ====

void FUN_80057b78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  
  iVar1 = zz_00422d8_((int)*(char *)(param_9 + 0x3e4));
  if (iVar1 != 0) {
    uVar2 = 0;
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined1 *)(param_9 + 0x19) = 0;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x1b) = 0;
    *(undefined1 *)(param_9 + 0x493) = 1;
    *(undefined1 *)(param_9 + 999) = *(undefined1 *)(param_9 + 0x3e4);
    *(undefined2 *)(param_9 + 1000) =
         *(undefined2 *)(PTR_DAT_80433934 + *(char *)(param_9 + 999) * 2 + 0x10);
    *(undefined *)(param_9 + 0x3ec) = PTR_DAT_80433934[*(char *)(param_9 + 999) + 0xa0];
    *(undefined *)(param_9 + 0x88) = PTR_DAT_80433934[*(char *)(param_9 + 0x3e4) + 0xcb];
    *(undefined1 *)(param_9 + 0x3ee) = 0;
    uVar3 = zz_0056ce0_(param_9);
    *(int *)(param_9 + 0x8c) = param_9;
    *(int *)(param_9 + 0x90) = param_9;
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_9 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_9 + 0x3e4);
    *(undefined1 *)(param_9 + 0x97) = *(undefined1 *)(param_9 + 999);
    uVar3 = zz_00419ec_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        extraout_r4,uVar2,param_12,param_13,param_14,param_15,param_16);
    zz_005380c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    zz_0041b20_(param_9);
    *(undefined1 *)(param_9 + 0x3e6) = 0;
    *(undefined1 *)(param_9 + 0x488) = 2;
    *(code **)(param_9 + 0x10c) = FUN_80056aa8;
    *(undefined4 *)(param_9 + 0x76c) = 0xffffffff;
    *(undefined1 *)(param_9 + 0x26f) = 0;
    zz_0055f90_(param_9);
    zz_005614c_(param_9);
    zz_0055dcc_(param_9);
    zz_0068004_(param_9);
    FUN_8004bb14(param_9);
    zz_003cc24_(param_9);
    (**(code **)(param_9 + 0x4b8))(param_9);
    zz_008ab30_(param_9);
    *(undefined1 *)(param_9 + 0x741) = 0;
    *(undefined1 *)(param_9 + 0x743) = 1;
    *(undefined2 *)(param_9 + 0x272) = 0;
    zz_0057cf4_(param_9);
  }
  return;
}



// ==== 80057cf4  zz_0057cf4_ ====

void zz_0057cf4_(int param_1)

{
  zz_005685c_(param_1);
  *(undefined1 *)(param_1 + 0x578) = 2;
  zz_0055dcc_(param_1);
  zz_005568c_(param_1);
  (**(code **)(param_1 + 0x4bc))(param_1);
  (*(code *)(&PTR_LAB_802d3294)[*(char *)(param_1 + 0x19)])(param_1);
  (**(code **)(param_1 + 0x4c0))(param_1);
  zz_0055ee4_(param_1);
  zz_005b880_(param_1);
  return;
}



// ==== 80057d9c  FUN_80057d9c ====

void FUN_80057d9c(int param_1)

{
  char cVar1;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x1cef);
  if (cVar1 == '\x03') {
    local_18 = *(undefined4 *)(param_1 + 0x8e0);
    local_14 = *(undefined4 *)(param_1 + 0x8f0);
    local_10 = *(undefined4 *)(param_1 + 0x900);
    zz_00b2290_((double)(*(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x7fc)),param_1,2,
                &local_18);
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined1 *)(param_1 + 0x1a) = 0;
    }
    else if ('\0' < cVar1) {
      zz_001ab6c_(param_1,0x7e);
    }
  }
  else if (cVar1 < '\x05') {
    local_18 = *(undefined4 *)(param_1 + 0x8e0);
    local_14 = *(undefined4 *)(param_1 + 0x8f0);
    local_10 = *(undefined4 *)(param_1 + 0x900);
    *(undefined2 *)(param_1 + 0x5ae) = 0x8000;
    zz_00b2290_((double)(*(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x7fc)),param_1,0,
                &local_18);
  }
  *(undefined1 *)(param_1 + 0x1cef) = 0;
  return;
}



// ==== 80057ea0  FUN_80057ea0 ====

void FUN_80057ea0(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  
  fVar1 = FLOAT_804372e0;
  cVar2 = *(char *)(param_1 + 0x1a);
  if (cVar2 != '\x01') {
    if ('\0' < cVar2) {
      return;
    }
    if (cVar2 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar2 + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_800061a8(param_1,0xc);
    zz_00f036c_(param_1,0xf2);
  }
  fVar3 = FLOAT_804372e0;
  fVar1 = FLOAT_80437270;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - FLOAT_80437258;
  dVar6 = zz_0045204_((short)(int)(fVar1 * (*(float *)(param_1 + 0x558) / fVar3)));
  fVar5 = FLOAT_80437284;
  fVar4 = FLOAT_80437280;
  fVar3 = FLOAT_80437250;
  fVar1 = (float)((double)FLOAT_8043726c * dVar6 + (double)FLOAT_80437268);
  *(float *)(param_1 + 0x15dc) = fVar1;
  *(float *)(param_1 + 0x15d4) = fVar1;
  *(float *)(param_1 + 0x15d8) = -(fVar5 * *(float *)(param_1 + 0x15d4) - fVar4);
  if (*(float *)(param_1 + 0x558) <= fVar3) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80057fac  zz_0057fac_ ====

void zz_0057fac_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = param_2[1];
  *(undefined4 *)(param_1 + 0x20) = *param_2;
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  *(undefined4 *)(param_1 + 0x28) = param_2[2];
  return;
}



// ==== 80057fc8  zz_0057fc8_ ====

void zz_0057fc8_(int param_1,undefined2 param_2)

{
  *(undefined2 *)(param_1 + 0x72) = param_2;
  return;
}



// ==== 80057fd0  zz_0057fd0_ ====

void zz_0057fd0_(double param_1,int param_2,int param_3)

{
  if (param_3 == 0) {
    *(float *)(param_2 + 0xb4) = (float)param_1;
  }
  else {
    param_1 = (double)(float)(param_1 * (double)*(float *)(param_2 + 0xb4));
  }
  *(float *)(param_2 + 0x60) = (float)param_1;
  *(float *)(param_2 + 0x5c) = (float)param_1;
  *(float *)(param_2 + 0x58) = (float)param_1;
  return;
}



// ==== 80057ff8  zz_0057ff8_ ====

void zz_0057ff8_(int param_1,uint param_2,int param_3)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043725c;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  zz_004beb8_(dVar1,param_1,0xf,param_2,param_3,0xffffffff,0xffffffff);
  return;
}



// ==== 80058044  zz_0058044_ ====

void zz_0058044_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80437258;
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(float *)(param_1 + 0x15dc) = fVar1;
  *(float *)(param_1 + 0x15d8) = fVar1;
  *(float *)(param_1 + 0x15d4) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  *(float *)(param_1 + 0xb8) = fVar1;
  *(float *)(param_1 + 0xb4) = fVar1;
  FUN_800061a8(param_1,0xe);
  return;
}



// ==== 8005809c  zz_005809c_ ====

void zz_005809c_(undefined1 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_803c4e84;
  DAT_803c4e84 = 0;
  DAT_803c4e88 = 0;
  DAT_803c4e8c = 0;
  DAT_803c4e90 = 0;
  DAT_803c4e94 = 0;
  DAT_803c4e98 = 0;
  for (iVar1 = 0; iVar1 < param_2; iVar1 = iVar1 + 1) {
    *puVar2 = param_1;
    param_1[0x3e4] = (char)iVar1;
    zz_00537a8_(param_1);
    *param_1 = 1;
    puVar2 = puVar2 + 1;
    param_1[0x492] = 0;
    param_1[0x3f2] = 0;
    param_1[0x486] = 0;
    *(undefined1 **)(param_1 + 0x8c) = param_1;
    *(undefined1 **)(param_1 + 0x90) = param_1;
    *(undefined2 *)(param_1 + 0x94) = *(undefined2 *)(param_1 + 1000);
    param_1[0x96] = param_1[0x3e4];
    param_1[0x97] = param_1[999];
    param_1 = param_1 + 0x1e00;
  }
  return;
}



// ==== 8005814c  zz_005814c_ ====

void zz_005814c_(int param_1,undefined2 param_2,undefined1 param_3)

{
  *(undefined2 *)(param_1 + 0x3ea) = param_2;
  *(undefined2 *)(param_1 + 1000) = param_2;
  *(undefined1 *)(param_1 + 0x3ed) = param_3;
  *(undefined1 *)(param_1 + 0x3ec) = param_3;
  return;
}



// ==== 80058160  zz_0058160_ ====

void zz_0058160_(void)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = &DAT_803c4e84;
  iVar1 = 0;
  do {
    if (*piVar2 != 0) {
      zz_00581b8_(*piVar2);
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 6);
  return;
}



// ==== 800581b8  zz_00581b8_ ====

void zz_00581b8_(int param_1)

{
  zz_005685c_(param_1);
  (*(code *)(&PTR_FUN_802d32a0)[*(char *)(param_1 + 0x18)])(param_1);
  if (*(char *)(param_1 + 0x18) == '\x01') {
    zz_0046698_(param_1);
  }
  zz_0006284_(param_1);
  DAT_80436260 = 1;
  DAT_803c4e6c = param_1;
  return;
}



// ==== 80058244  FUN_80058244 ====

void FUN_80058244(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined8 uVar5;
  double dVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x19) = 2;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  *(undefined1 *)(param_9 + 0x1b) = 0;
  *(undefined1 *)(param_9 + 0x493) = 2;
  *(undefined1 *)(param_9 + 999) = *(undefined1 *)(param_9 + 0x3e4);
  uVar5 = zz_0056ce0_(param_9);
  *(int *)(param_9 + 0x8c) = param_9;
  *(int *)(param_9 + 0x90) = param_9;
  *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_9 + 1000);
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_9 + 0x3e4);
  *(undefined1 *)(param_9 + 0x97) = *(undefined1 *)(param_9 + 999);
  uVar5 = zz_0058f50_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  zz_005380c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  zz_0041b20_(param_9);
  *(undefined1 *)(param_9 + 0x3e6) = 0;
  *(undefined1 *)(param_9 + 0x488) = 2;
  *(code **)(param_9 + 0x10c) = FUN_80056aa8;
  *(undefined4 *)(param_9 + 0x76c) = 0xffffffff;
  *(undefined1 *)(param_9 + 0x26f) = 0;
  *(undefined1 *)(param_9 + 0x3ee) = 0;
  zz_0055f90_(param_9);
  zz_005614c_(param_9);
  zz_0055dcc_(param_9);
  zz_0068004_(param_9);
  FUN_8004bb14(param_9);
  zz_003cc24_(param_9);
  (**(code **)(param_9 + 0x4b8))(param_9);
  *(undefined1 *)(param_9 + 0x741) = 0;
  fVar4 = FLOAT_80437308;
  *(undefined1 *)(param_9 + 0x743) = 1;
  fVar2 = FLOAT_80437250;
  *(undefined2 *)(param_9 + 0x272) = 0;
  fVar3 = FLOAT_80437258;
  *(float *)(param_9 + 0x20) = fVar4;
  *(float *)(param_9 + 0x28) = fVar2;
  *(float *)(param_9 + 0x24) = fVar2;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0xb4) = fVar3 / *(float *)(param_9 + 0x7fc);
  zz_00583cc_(param_9);
  uVar1 = *(undefined4 *)(param_9 + 0xb4);
  dVar6 = (double)FLOAT_8043725c;
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  zz_004beb8_(dVar6,param_9,0xf,0,0,0,0);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0058e30_(param_9);
  return;
}



// ==== 800583cc  zz_00583cc_ ====

void zz_00583cc_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  
  switch(*(undefined1 *)(param_1 + 1000)) {
  case 0:
    *(float *)(param_1 + 0x24) = FLOAT_8043730c;
    break;
  case 1:
    *(float *)(param_1 + 0x24) = FLOAT_804372e0;
    break;
  case 2:
    *(float *)(param_1 + 0x24) = FLOAT_804372e0;
    break;
  case 3:
    *(float *)(param_1 + 0x24) = FLOAT_8043730c;
    break;
  case 4:
    *(float *)(param_1 + 0x24) = FLOAT_804372e0;
    break;
  case 5:
    *(float *)(param_1 + 0x24) = FLOAT_804372dc;
    break;
  case 6:
    *(float *)(param_1 + 0x24) = FLOAT_8043730c;
    break;
  case 7:
    *(float *)(param_1 + 0x24) = FLOAT_80437280;
    break;
  case 8:
    *(float *)(param_1 + 0x24) = FLOAT_804372e0;
    break;
  case 9:
    *(float *)(param_1 + 0x24) = FLOAT_804372e0;
    break;
  case 10:
    *(float *)(param_1 + 0x24) = FLOAT_80437310;
    break;
  case 0xb:
    *(float *)(param_1 + 0x24) = FLOAT_80437314;
    break;
  case 0xc:
    *(float *)(param_1 + 0x24) = FLOAT_80437318;
    break;
  case 0xd:
    *(float *)(param_1 + 0x24) = FLOAT_8043731c;
    break;
  case 0xe:
    *(float *)(param_1 + 0x24) = FLOAT_80437250;
    break;
  case 0xf:
    *(float *)(param_1 + 0x24) = FLOAT_80437320;
  }
  fVar25 = FLOAT_804373bc;
  fVar24 = FLOAT_804373b4;
  fVar23 = FLOAT_804373a4;
  fVar22 = FLOAT_80437394;
  fVar21 = FLOAT_80437390;
  fVar20 = FLOAT_8043738c;
  fVar19 = FLOAT_80437384;
  fVar18 = FLOAT_80437380;
  fVar17 = FLOAT_80437378;
  fVar16 = FLOAT_80437368;
  fVar15 = FLOAT_80437360;
  fVar14 = FLOAT_8043735c;
  fVar13 = FLOAT_80437350;
  fVar12 = FLOAT_8043734c;
  fVar11 = FLOAT_80437348;
  fVar10 = FLOAT_80437344;
  fVar9 = FLOAT_80437340;
  fVar8 = FLOAT_80437334;
  fVar7 = FLOAT_80437330;
  fVar6 = FLOAT_8043732c;
  fVar5 = FLOAT_80437328;
  fVar4 = FLOAT_8043726c;
  fVar3 = FLOAT_80437268;
  fVar2 = FLOAT_80437258;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x623) {
    return;
  }
  if (0x622 < sVar1) {
    if (sVar1 == 0xa04) {
LAB_80058cbc:
      *(float *)(param_1 + 0x24) = FLOAT_80437250;
      return;
    }
    if (0xa03 < sVar1) {
      if (sVar1 == 0xd02) {
        *(float *)(param_1 + 0xb4) = FLOAT_80437348;
        return;
      }
      if (0xd01 < sVar1) {
        if (sVar1 == 0xe04) {
          *(float *)(param_1 + 0x24) = FLOAT_804373b8;
          return;
        }
        if (sVar1 < 0xe04) {
          if (sVar1 != 0xe00) {
            if (0xdff < sVar1) {
              if (sVar1 == 0xe02) {
                *(float *)(param_1 + 0x24) = FLOAT_8043733c;
                *(float *)(param_1 + 0xb4) = fVar24;
                return;
              }
              if (0xe01 < sVar1) {
                *(float *)(param_1 + 0x24) = FLOAT_804373b0;
                return;
              }
              *(float *)(param_1 + 0xb4) = FLOAT_80437350;
              return;
            }
            if (sVar1 == 0xd06) {
              *(float *)(param_1 + 0x24) = FLOAT_80437398;
              *(float *)(param_1 + 0xb4) = fVar16;
              return;
            }
            if (0xd05 < sVar1) {
              if (sVar1 < 0xd08) {
                *(float *)(param_1 + 0x24) = FLOAT_804373ac;
                *(float *)(param_1 + 0xb4) = fVar7;
                return;
              }
              return;
            }
            if (sVar1 < 0xd04) {
              *(float *)(param_1 + 0xb4) = FLOAT_804373a8;
              return;
            }
LAB_80058d48:
            *(float *)(param_1 + 0xb4) = FLOAT_804373a4;
            return;
          }
        }
        else {
          if (sVar1 == 0xf04) {
            *(float *)(param_1 + 0x24) = FLOAT_80437318;
            *(float *)(param_1 + 0xb4) = fVar4;
            return;
          }
          if (0xf03 < sVar1) {
            if (sVar1 == 0xf06) {
              *(float *)(param_1 + 0x24) = FLOAT_80437318;
              *(float *)(param_1 + 0xb4) = fVar2;
              return;
            }
            if (sVar1 < 0xf06) {
              *(float *)(param_1 + 0x24) = FLOAT_80437318;
              *(float *)(param_1 + 0xb4) = fVar7;
              return;
            }
            return;
          }
          if (sVar1 == 0xf00) {
            *(float *)(param_1 + 0x24) = FLOAT_80437250;
            *(float *)(param_1 + 0xb4) = fVar25;
            return;
          }
          if (0xeff < sVar1) {
            return;
          }
          if (0xe05 < sVar1) {
            return;
          }
        }
        *(float *)(param_1 + 0x24) = FLOAT_80437310;
        *(float *)(param_1 + 0xb4) = fVar15;
        return;
      }
      if (sVar1 != 0xc00) {
        if (sVar1 < 0xc00) {
          if (sVar1 == 0xa0a) {
            *(float *)(param_1 + 0xb4) = FLOAT_80437394;
            return;
          }
          if (0xa09 < sVar1) {
            if (sVar1 == 0xb07) {
              *(float *)(param_1 + 0x24) = FLOAT_80437314;
              *(float *)(param_1 + 0xb4) = fVar4;
              return;
            }
            if (sVar1 < 0xb07) {
              if (sVar1 == 0xb03) {
                *(float *)(param_1 + 0x24) = FLOAT_8043737c;
                *(float *)(param_1 + 0xb4) = fVar4;
                return;
              }
              return;
            }
            return;
          }
          if (sVar1 == 0xa07) {
            *(float *)(param_1 + 0x24) = FLOAT_80437314;
            return;
          }
          if (sVar1 < 0xa07) {
            if (sVar1 < 0xa06) {
              return;
            }
LAB_80058c9c:
            *(float *)(param_1 + 0x24) = FLOAT_80437310;
            *(float *)(param_1 + 0xb4) = fVar22;
            return;
          }
          goto LAB_80058cbc;
        }
        if (sVar1 == 0xc05) {
          *(float *)(param_1 + 0x24) = FLOAT_80437398;
          return;
        }
        if (sVar1 < 0xc05) {
          if (sVar1 == 0xc03) {
            return;
          }
          if (0xc02 < sVar1) {
            *(float *)(param_1 + 0xb4) = FLOAT_804373a0;
            return;
          }
          if (0xc01 < sVar1) {
            *(float *)(param_1 + 0x24) = FLOAT_8043731c;
            *(float *)(param_1 + 0xb4) = fVar21;
            return;
          }
          *(float *)(param_1 + 0x24) = FLOAT_8043731c;
          *(float *)(param_1 + 0xb4) = fVar23;
          return;
        }
        if (0xcff < sVar1) goto LAB_80058d48;
        if (0xc06 < sVar1) {
          return;
        }
      }
      *(float *)(param_1 + 0xb4) = FLOAT_8043739c;
      return;
    }
    if (sVar1 == 0x804) {
LAB_80058c3c:
      *(float *)(param_1 + 0x24) = FLOAT_80437250;
      return;
    }
    if (0x803 < sVar1) {
      if (sVar1 == 0x907) {
        *(float *)(param_1 + 0x24) = FLOAT_80437250;
        *(float *)(param_1 + 0xb4) = fVar2;
        return;
      }
      if (sVar1 < 0x907) {
        if (sVar1 == 0x901) {
          *(float *)(param_1 + 0x24) = FLOAT_80437250;
          *(float *)(param_1 + 0xb4) = fVar5;
          return;
        }
        if (sVar1 < 0x901) {
          if (sVar1 != 0x80c) {
            if (sVar1 < 0x80c) {
              if (0x805 < sVar1) {
                return;
              }
            }
            else if (0x80e < sVar1) {
              return;
            }
            *(float *)(param_1 + 0x24) = FLOAT_80437374;
            return;
          }
          goto LAB_80058c3c;
        }
        if (sVar1 != 0x903) {
          return;
        }
      }
      else if (sVar1 != 0x90c) {
        if (0x90b < sVar1) {
          if (sVar1 != 0xa02) {
            if (sVar1 < 0xa02) {
              if (0xa00 < sVar1) {
                *(float *)(param_1 + 0x24) = FLOAT_8043733c;
                *(float *)(param_1 + 0xb4) = fVar6;
                return;
              }
              return;
            }
            goto LAB_80058c9c;
          }
          goto LAB_80058cbc;
        }
        if (sVar1 != 0x90a) {
          return;
        }
      }
      *(float *)(param_1 + 0x24) = FLOAT_80437250;
      return;
    }
    if (sVar1 == 0x704) {
LAB_80058bf0:
      *(float *)(param_1 + 0x24) = FLOAT_804372dc;
      *(float *)(param_1 + 0xb4) = fVar20;
      return;
    }
    if (sVar1 < 0x704) {
      if (sVar1 == 0x628) {
        *(float *)(param_1 + 0x24) = FLOAT_80437314;
        *(float *)(param_1 + 0xb4) = fVar17;
        return;
      }
      if (sVar1 < 0x628) {
        if (sVar1 != 0x626) {
          if (0x625 < sVar1) {
            return;
          }
          if (0x624 < sVar1) {
            *(float *)(param_1 + 0x24) = FLOAT_8043737c;
            *(float *)(param_1 + 0xb4) = fVar11;
            return;
          }
        }
        goto LAB_80058b24;
      }
      if (sVar1 != 0x702) {
        if (0x701 < sVar1) {
          *(float *)(param_1 + 0x24) = FLOAT_804372e0;
          return;
        }
        if (0x700 < sVar1) {
          *(float *)(param_1 + 0x24) = FLOAT_80437374;
          *(float *)(param_1 + 0xb4) = fVar21;
          return;
        }
        return;
      }
    }
    else {
      if (sVar1 == 0x70b) {
        *(float *)(param_1 + 0xb4) = FLOAT_80437328;
        return;
      }
      if (0x70a < sVar1) {
        if (sVar1 == 0x801) {
          *(float *)(param_1 + 0xb4) = FLOAT_8043726c;
          return;
        }
        if (sVar1 < 0x801) {
          if (sVar1 < 0x70e) {
            *(float *)(param_1 + 0x24) = FLOAT_8043733c;
            *(float *)(param_1 + 0xb4) = fVar6;
            return;
          }
          return;
        }
        return;
      }
      if (sVar1 == 0x707) goto LAB_80058bf0;
      if (sVar1 < 0x707) {
        return;
      }
      if (sVar1 < 0x70a) {
        return;
      }
    }
    *(float *)(param_1 + 0x24) = FLOAT_80437250;
    return;
  }
  if (sVar1 < 0x40e) {
    if (sVar1 == 0x20d) {
      *(float *)(param_1 + 0x24) = FLOAT_80437250;
      *(float *)(param_1 + 0xb4) = fVar6;
      return;
    }
    if (sVar1 < 0x20d) {
      if (sVar1 != 0x203) {
        if (sVar1 < 0x203) {
          if (sVar1 == 0x103) {
            *(float *)(param_1 + 0x24) = FLOAT_804372e0;
            *(float *)(param_1 + 0xb4) = fVar6;
            return;
          }
          if (sVar1 < 0x103) {
            if (sVar1 == 0xc) {
              *(float *)(param_1 + 0xb4) = FLOAT_80437328;
              return;
            }
            if (sVar1 < 0xc) {
              if (sVar1 == 5) {
                *(float *)(param_1 + 0xb4) = FLOAT_80437324;
                return;
              }
              return;
            }
            return;
          }
          if (sVar1 != 0x201) {
            if (0x200 < sVar1) {
              *(float *)(param_1 + 0x24) = FLOAT_804372dc;
              return;
            }
            return;
          }
LAB_80058978:
          *(float *)(param_1 + 0x24) = FLOAT_80437250;
          *(float *)(param_1 + 0xb4) = fVar7;
          return;
        }
        if (sVar1 != 0x208) {
          if (sVar1 < 0x208) {
            if (sVar1 == 0x206) goto LAB_80058940;
            if (0x205 < sVar1) {
              return;
            }
            if (sVar1 < 0x205) {
              *(float *)(param_1 + 0x24) = FLOAT_80437250;
              *(float *)(param_1 + 0xb4) = fVar6;
              return;
            }
          }
          else {
            if (sVar1 == 0x20b) {
              *(float *)(param_1 + 0x24) = FLOAT_804372dc;
              *(float *)(param_1 + 0xb4) = fVar8;
              return;
            }
            if (0x20a < sVar1) goto LAB_80058978;
            if (0x209 < sVar1) {
              return;
            }
          }
          *(float *)(param_1 + 0x24) = FLOAT_8043731c;
          return;
        }
      }
    }
    else {
      if (sVar1 == 0x402) {
LAB_80058a00:
        *(float *)(param_1 + 0xb4) = FLOAT_80437344;
        return;
      }
      if (0x401 < sVar1) {
        if (sVar1 != 0x407) {
          if (sVar1 < 0x407) {
            if (sVar1 != 0x405) {
              if (sVar1 < 0x405) {
                if (0x403 < sVar1) {
                  *(float *)(param_1 + 0x24) = FLOAT_80437250;
                  *(float *)(param_1 + 0xb4) = fVar10;
                  return;
                }
                *(float *)(param_1 + 0x24) = FLOAT_80437280;
                *(float *)(param_1 + 0xb4) = fVar11;
                return;
              }
LAB_800589e0:
              *(float *)(param_1 + 0x24) = FLOAT_8043733c;
              return;
            }
          }
          else {
            if (sVar1 == 0x40a) goto LAB_800589ec;
            if (0x409 < sVar1) goto LAB_800589e0;
            if (sVar1 < 0x409) goto LAB_80058a00;
          }
        }
        *(float *)(param_1 + 0x24) = FLOAT_80437250;
        *(float *)(param_1 + 0xb4) = fVar11;
        return;
      }
      if (sVar1 == 0x309) {
        return;
      }
      if (0x308 < sVar1) {
        if (sVar1 != 0x400) {
          if (0x3ff < sVar1) {
            return;
          }
          if (sVar1 < 0x30b) {
            *(float *)(param_1 + 0xb4) = FLOAT_80437258;
            return;
          }
          return;
        }
LAB_800589ec:
        *(float *)(param_1 + 0x24) = FLOAT_80437280;
        *(float *)(param_1 + 0xb4) = fVar9;
        return;
      }
      if (sVar1 == 0x20f) {
LAB_80058940:
        *(float *)(param_1 + 0x24) = FLOAT_80437280;
        return;
      }
      if (0x20e < sVar1) {
        if (0x307 < sVar1) {
          *(float *)(param_1 + 0x24) = FLOAT_80437338;
          return;
        }
        return;
      }
    }
    *(float *)(param_1 + 0x24) = FLOAT_80437250;
    *(float *)(param_1 + 0xb4) = fVar7;
    return;
  }
  if (sVar1 == 0x517) {
LAB_80058a84:
    *(float *)(param_1 + 0xb4) = FLOAT_80437354;
    return;
  }
  if (0x516 < sVar1) {
    if (sVar1 == 0x618) {
      *(float *)(param_1 + 0x24) = FLOAT_80437338;
      *(float *)(param_1 + 0xb4) = fVar19;
      return;
    }
    if (sVar1 < 0x618) {
      if (sVar1 < 0x611) {
        if (sVar1 == 0x606) {
          return;
        }
        if (sVar1 < 0x606) {
          if (sVar1 < 0x605) {
            return;
          }
        }
        else if (0x607 < sVar1) {
          return;
        }
      }
      else if (sVar1 != 0x614) {
        if (0x613 < sVar1) {
          return;
        }
        if (0x612 < sVar1) {
          return;
        }
      }
    }
    else {
      if (sVar1 == 0x61f) {
        *(float *)(param_1 + 0x24) = FLOAT_8043737c;
        *(float *)(param_1 + 0xb4) = fVar18;
        return;
      }
      if (sVar1 < 0x61f) {
        if (sVar1 == 0x61b) {
          *(float *)(param_1 + 0x24) = FLOAT_80437374;
          *(float *)(param_1 + 0xb4) = fVar11;
          return;
        }
        if (sVar1 < 0x61b) {
          if (0x619 < sVar1) {
            *(float *)(param_1 + 0x24) = FLOAT_80437388;
            *(float *)(param_1 + 0xb4) = fVar16;
            return;
          }
          *(float *)(param_1 + 0x24) = FLOAT_80437310;
          *(float *)(param_1 + 0xb4) = fVar17;
          return;
        }
        return;
      }
      if (sVar1 == 0x621) {
        return;
      }
      if (sVar1 < 0x621) {
        *(float *)(param_1 + 0x24) = FLOAT_8043733c;
        *(float *)(param_1 + 0xb4) = fVar16;
        return;
      }
    }
LAB_80058b24:
    *(float *)(param_1 + 0x24) = FLOAT_804372dc;
    return;
  }
  if (sVar1 == 0x50b) {
LAB_80058acc:
    *(float *)(param_1 + 0x24) = FLOAT_80437250;
    *(float *)(param_1 + 0xb4) = fVar11;
    return;
  }
  if (sVar1 < 0x50b) {
    if (sVar1 == 0x504) {
      *(float *)(param_1 + 0xb4) = FLOAT_80437360;
      return;
    }
    if (sVar1 < 0x504) {
      if (sVar1 == 0x501) goto LAB_80058acc;
      if (0x500 < sVar1) {
        if (0x502 < sVar1) {
          *(float *)(param_1 + 0xb4) = FLOAT_8043736c;
          return;
        }
        *(float *)(param_1 + 0x24) = FLOAT_80437364;
        *(float *)(param_1 + 0xb4) = fVar16;
        return;
      }
      if (sVar1 < 0x500) {
        return;
      }
    }
    else {
      if (sVar1 == 0x506) {
        *(float *)(param_1 + 0x24) = FLOAT_80437250;
        *(float *)(param_1 + 0xb4) = fVar15;
        return;
      }
      if (sVar1 < 0x506) {
        *(float *)(param_1 + 0x24) = FLOAT_80437318;
        *(float *)(param_1 + 0xb4) = fVar14;
        return;
      }
      if (sVar1 < 0x509) {
        return;
      }
    }
    *(float *)(param_1 + 0x24) = FLOAT_80437250;
    *(float *)(param_1 + 0xb4) = fVar12;
    return;
  }
  if (sVar1 == 0x510) {
    *(float *)(param_1 + 0xb4) = FLOAT_80437370;
    return;
  }
  if (sVar1 < 0x510) {
    if (sVar1 == 0x50e) {
      *(float *)(param_1 + 0x24) = FLOAT_80437308;
      *(float *)(param_1 + 0xb4) = fVar11;
      return;
    }
    if (0x50d < sVar1) {
LAB_80058b0c:
      *(float *)(param_1 + 0xb4) = FLOAT_80437360;
      return;
    }
    if (0x50c < sVar1) goto LAB_80058a84;
  }
  else {
    if (sVar1 == 0x512) goto LAB_80058b0c;
    if (sVar1 < 0x512) {
      *(float *)(param_1 + 0x24) = FLOAT_80437358;
      *(float *)(param_1 + 0xb4) = fVar3;
      return;
    }
    if (sVar1 < 0x515) {
      return;
    }
  }
  *(float *)(param_1 + 0x24) = FLOAT_804372dc;
  *(float *)(param_1 + 0xb4) = fVar13;
  return;
}



// ==== 80058e30  zz_0058e30_ ====

void zz_0058e30_(int param_1)

{
  zz_005685c_(param_1);
  *(undefined1 *)(param_1 + 0x578) = 2;
  zz_0055dcc_(param_1);
  zz_005568c_(param_1);
  (**(code **)(param_1 + 0x4bc))(param_1);
  (*(code *)(&PTR_FUN_802d32f0)[*(char *)(param_1 + 0x19)])(param_1);
  (**(code **)(param_1 + 0x4c0))(param_1);
  zz_0055ee4_(param_1);
  zz_005b880_(param_1);
  return;
}



// ==== 80058ec8  FUN_80058ec8 ====

void FUN_80058ec8(int param_1)

{
  zz_004cd24_(param_1,0xf);
  return;
}



// ==== 80058eec  FUN_80058eec ====

void FUN_80058eec(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(undefined1 *)(param_1 + 0x662) = 1;
  (**(code **)(param_1 + 0x4cc))();
  (**(code **)(param_1 + 0x4d0))(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80058f50  zz_0058f50_ ====

void zz_0058f50_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar1 = zz_0006f98_(param_9);
  if (*(int *)(&DAT_803bb4a0 + *(char *)(param_9 + 0x3e4) * 4) != 0) {
    iVar5 = *(int *)(iVar1 + 0x600);
    *(undefined4 *)(iVar1 + 0xc28) = 0xff;
    *(undefined4 *)(iVar1 + 0xc2c) = 0;
    iVar7 = iVar1;
    for (iVar6 = 0; iVar6 < *(short *)(*(int *)(iVar1 + 0x600) + 0x1a); iVar6 = iVar6 + 1) {
      piVar2 = zz_0197a0c_(0);
      *(int **)(iVar7 + 0x708) = piVar2;
      param_1 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                            *(int *)(iVar7 + 0x708),iVar6,iVar1 + 0xc28,in_r7,in_r8,in_r9,in_r10);
      iVar7 = iVar7 + 4;
    }
    iVar7 = iVar1;
    for (iVar6 = 0; iVar6 < *(short *)(*(int *)(iVar1 + 0x600) + 0x1a); iVar6 = iVar6 + 1) {
      piVar2 = zz_0197a0c_(0);
      *(int **)(iVar7 + 0x788) = piVar2;
      iVar4 = iVar1 + 0xc28;
      iVar3 = iVar6;
      uVar8 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                          *(int *)(iVar7 + 0x788),iVar6,iVar4,in_r7,in_r8,in_r9,in_r10);
      zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar7 + 0x788),extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
      param_1 = zz_0007cac_((double)FLOAT_80437368,*(int *)(iVar7 + 0x788));
      iVar7 = iVar7 + 4;
    }
  }
  return;
}



// ==== 80059068  zz_0059068_ ====

void zz_0059068_(int param_1)

{
  int iVar1;
  
  *(float *)(param_1 + 0x760) = *(float *)(param_1 + 0x760) / *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x764) = *(float *)(param_1 + 0x764) / *(float *)(param_1 + 0xb4);
  zz_005bab8_(param_1);
  zz_0067a70_(param_1);
  FUN_80059e58(param_1);
  zz_00685c0_(param_1);
  iVar1 = FUN_8005a190(param_1);
  if (iVar1 == 0) {
    (*(code *)(&PTR_FUN_802d3300)[*(char *)(param_1 + 0x5e4)])(param_1);
    (**(code **)(param_1 + 0x4c8))(param_1);
    FUN_80059f5c(param_1);
    FUN_8005a144(param_1);
  }
  FUN_8005a298(param_1);
  FUN_8005a378(param_1);
  zz_0068030_(param_1);
  return;
}



// ==== 8005913c  FUN_8005913c ====

void FUN_8005913c(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x661) == '\x03') {
    zz_006a750_(param_1,0x1b);
    zz_006a6fc_(param_1,0x1b);
  }
  else {
    iVar1 = FUN_80068df8(param_1);
    if ((((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
        (iVar1 = FUN_80069814(param_1), iVar1 == 0)) &&
       (((iVar1 = FUN_800696f4(param_1), iVar1 == 0 && (iVar1 = zz_0069038_(param_1), iVar1 == 0))
        && (iVar1 = FUN_80069354(param_1), iVar1 == 0)))) {
      FUN_80068f9c(param_1);
    }
  }
  return;
}



// ==== 800591f0  FUN_800591f0 ====

void FUN_800591f0(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if ((((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
      (iVar1 = FUN_80069814(param_1), iVar1 == 0)) &&
     (((iVar1 = FUN_800696f4(param_1), iVar1 == 0 && (iVar1 = zz_0069038_(param_1), iVar1 == 0)) &&
      (iVar1 = FUN_80069354(param_1), iVar1 == 0)))) {
    FUN_80069000(param_1);
  }
  return;
}



// ==== 80059280  FUN_80059280 ====

void FUN_80059280(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if ((((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
      (iVar1 = FUN_80069814(param_1), iVar1 == 0)) &&
     (((iVar1 = FUN_800696f4(param_1), iVar1 == 0 && (iVar1 = zz_0069038_(param_1), iVar1 == 0)) &&
      (iVar1 = FUN_80069354(param_1), iVar1 == 0)))) {
    FUN_80069000(param_1);
  }
  return;
}



// ==== 80059310  FUN_80059310 ====

void FUN_80059310(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if ((((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
      (iVar1 = FUN_80069814(param_1), iVar1 == 0)) &&
     (((iVar1 = FUN_800696f4(param_1), iVar1 == 0 && (iVar1 = zz_0069038_(param_1), iVar1 == 0)) &&
      ((iVar1 = FUN_80069354(param_1), iVar1 == 0 && (*(char *)(param_1 + 0x661) != '\x04')))))) {
    FUN_80068f9c(param_1);
  }
  return;
}



// ==== 800593ac  FUN_800593ac ====

void FUN_800593ac(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if (((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
     (iVar1 = FUN_80069814(param_1), iVar1 == 0)) {
    FUN_800696f4(param_1);
  }
  return;
}



// ==== 8005940c  FUN_8005940c ====

void FUN_8005940c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_80069140(param_1), iVar2 == 0)) &&
     (((iVar2 = FUN_800693fc(param_1), iVar2 == 0 && (iVar2 = FUN_800696f4(param_1), iVar2 == 0)) &&
      ((iVar2 = FUN_8006965c(param_1), iVar2 == 0 && (*(char *)(param_1 + 0x661) == '\x06')))))) {
    FUN_80068f9c(param_1);
  }
  return;
}



// ==== 800594a8  FUN_800594a8 ====

void FUN_800594a8(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
        (iVar2 = zz_0069210_(param_1), iVar2 == 0)) &&
       ((iVar2 = FUN_800693fc(param_1), iVar2 == 0 && (iVar2 = FUN_800696f4(param_1), iVar2 == 0))))
      && ((iVar2 = FUN_8006965c(param_1), iVar2 == 0 &&
          ((iVar2 = FUN_800695c4(param_1), iVar2 == 0 && (iVar2 = FUN_8006952c(param_1), iVar2 == 0)
           ))))) &&
     ((iVar2 = FUN_800691d8(param_1), iVar2 == 0 && (*(char *)(param_1 + 0x661) == '\x06')))) {
    FUN_80068f9c(param_1);
  }
  return;
}



// ==== 80059574  FUN_80059574 ====

void FUN_80059574(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if ((((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
      (iVar1 = FUN_80069814(param_1), iVar1 == 0)) && (iVar1 = zz_0069038_(param_1), iVar1 == 0)) {
    FUN_80069354(param_1);
  }
  return;
}



// ==== 800595e4  FUN_800595e4 ====

void FUN_800595e4(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if (((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
       (iVar2 = FUN_80069140(param_1), iVar2 == 0)) &&
      ((iVar2 = FUN_800696f4(param_1), iVar2 == 0 && (iVar2 = FUN_8006965c(param_1), iVar2 == 0))))
     && ((iVar2 = FUN_800693fc(param_1), iVar2 == 0 &&
         ((iVar2 = FUN_800691d8(param_1), iVar2 == 0 && (*(char *)(param_1 + 0x661) == '\x06'))))))
  {
    FUN_80068f9c(param_1);
  }
  return;
}



// ==== 80059690  FUN_80059690 ====

void FUN_80059690(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_80068df8(param_1);
  if (((iVar1 == 0) && (uVar2 = FUN_800699d8(param_1), uVar2 == 0)) &&
     (iVar1 = FUN_80069814(param_1), iVar1 == 0)) {
    iVar1 = FUN_800696f4(param_1);
    if ((iVar1 == 0) && (*(char *)(param_1 + 0x7cd) != '\0')) {
      zz_0069038_(param_1);
    }
  }
  return;
}



// ==== 8005970c  FUN_8005970c ====

void FUN_8005970c(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_800699d8(param_1);
  if (uVar1 == 0) {
    FUN_80069814(param_1);
  }
  return;
}



// ==== 8005974c  FUN_8005974c ====

void FUN_8005974c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_800692bc(param_1), iVar2 == 0)) && (iVar2 = FUN_800694e8(param_1), iVar2 == 0)) {
    FUN_800691d8(param_1);
  }
  return;
}



// ==== 800597bc  FUN_800597bc ====

void FUN_800597bc(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = zz_0069210_(param_1), iVar2 == 0)) && (iVar2 = FUN_800693fc(param_1), iVar2 == 0)) {
    FUN_800691d8(param_1);
  }
  return;
}



// ==== 8005982c  FUN_8005982c ====

void FUN_8005982c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_800696f4(param_1), iVar2 == 0)) &&
     (((iVar2 = FUN_8006958c(param_1), iVar2 == 0 && (iVar2 = FUN_8006965c(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_800695c4(param_1), iVar2 == 0)))) {
    FUN_800691d8(param_1);
  }
  return;
}



// ==== 800598bc  FUN_800598bc ====

void FUN_800598bc(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_800692bc(param_1), iVar2 == 0)) &&
     ((iVar2 = FUN_800696f4(param_1), iVar2 == 0 && (iVar2 = FUN_8006965c(param_1), iVar2 == 0)))) {
    FUN_80069624(param_1);
  }
  return;
}



// ==== 8005993c  FUN_8005993c ====

void FUN_8005993c(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_800692bc(param_1), iVar2 == 0)) &&
     (((iVar2 = FUN_800696f4(param_1), iVar2 == 0 && (iVar2 = FUN_8006958c(param_1), iVar2 == 0)) &&
      (iVar2 = FUN_8006965c(param_1), iVar2 == 0)))) {
    FUN_800695c4(param_1);
  }
  return;
}



// ==== 800599cc  FUN_800599cc ====

void FUN_800599cc(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if (((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
     (iVar2 = FUN_800692bc(param_1), iVar2 == 0)) {
    FUN_800696f4(param_1);
  }
  return;
}



// ==== 80059a30  FUN_80059a30 ====

void FUN_80059a30(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) {
    FUN_80069860(param_1);
  }
  return;
}



// ==== 80059a80  FUN_80059a80 ====

void FUN_80059a80(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) {
    FUN_800698c0(param_1);
  }
  return;
}



// ==== 80059ad0  FUN_80059ad0 ====

void FUN_80059ad0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if (((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
     (iVar2 = FUN_80069354(param_1), iVar2 == 0)) {
    FUN_80069918(param_1);
  }
  return;
}



// ==== 80059b30  FUN_80059b30 ====

void FUN_80059b30(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = zz_0069038_(param_1), iVar2 == 0)) && (iVar2 = FUN_80069354(param_1), iVar2 == 0)) {
    FUN_80068f9c(param_1);
  }
  return;
}



// ==== 80059ba0  FUN_80059ba0 ====

void FUN_80059ba0(int param_1)

{
  uint uVar1;
  
  uVar1 = FUN_800699d8(param_1);
  if (uVar1 == 0) {
    FUN_80069814(param_1);
  }
  return;
}



// ==== 80059be0  FUN_80059be0 ====

void FUN_80059be0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = zz_0069210_(param_1), iVar2 == 0)) && (iVar2 = FUN_80069788(param_1), iVar2 == 0)) {
    FUN_800691d8(param_1);
  }
  return;
}



// ==== 80059c50  FUN_80059c50 ====

void FUN_80059c50(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = FUN_800699d8(param_1);
  if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
      (iVar2 = zz_0069210_(param_1), iVar2 == 0)) &&
     ((iVar2 = FUN_800696f4(param_1), iVar2 == 0 && (iVar2 = FUN_8006965c(param_1), iVar2 == 0)))) {
    FUN_800691d8(param_1);
  }
  return;
}



// ==== 80059cd0  FUN_80059cd0 ====

void FUN_80059cd0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x588) = 1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    iVar2 = FUN_80068df8(param_1);
    if ((((iVar2 == 0) && (uVar1 = FUN_800699d8(param_1), uVar1 == 0)) &&
        (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
       (((iVar2 = FUN_800696f4(param_1), iVar2 == 0 && (iVar2 = FUN_800690a0(param_1), iVar2 == 0))
        && ((iVar2 = zz_0069038_(param_1), iVar2 == 0 && (iVar2 = FUN_80069354(param_1), iVar2 == 0)
            ))))) {
      FUN_80068f9c(param_1);
    }
  }
  else {
    uVar1 = FUN_800699d8(param_1);
    if ((((uVar1 == 0) && (iVar2 = FUN_80069814(param_1), iVar2 == 0)) &&
        ((iVar2 = zz_0069210_(param_1), iVar2 == 0 &&
         ((((iVar2 = FUN_800693fc(param_1), iVar2 == 0 &&
            (iVar2 = FUN_800696f4(param_1), iVar2 == 0)) &&
           (iVar2 = FUN_8006965c(param_1), iVar2 == 0)) &&
          ((iVar2 = FUN_800695c4(param_1), iVar2 == 0 && (iVar2 = FUN_8006952c(param_1), iVar2 == 0)
           ))))))) &&
       ((iVar2 = FUN_800691d8(param_1), iVar2 == 0 && (*(char *)(param_1 + 0x661) == '\x06')))) {
      FUN_80068f9c(param_1);
    }
  }
  return;
}



// ==== 80059e30  FUN_80059e30 ====

void FUN_80059e30(int param_1)

{
  FUN_80069814(param_1);
  return;
}



// ==== 80059e58  FUN_80059e58 ====

void FUN_80059e58(int param_1)

{
  if (*(char *)(param_1 + 0x4a1) == '\0') {
    if ((*(char *)(param_1 + 0x18) == '\x01') && (*(char *)(param_1 + 0x6cb) == '\0')) {
      if ((*(float *)(param_1 + 0x20) < *(float *)(DAT_8043625c + 0x3c)) ||
         (((*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x20) ||
           (*(float *)(param_1 + 0x28) < *(float *)(DAT_8043625c + 0x44))) ||
          (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x28))))) {
        *(short *)(param_1 + 0x6cc) = *(short *)(param_1 + 0x6cc) + 1;
        if ((0x1d < *(short *)(param_1 + 0x6cc)) || ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0))
        {
          *(undefined2 *)(param_1 + 0x6cc) = 0;
          if ((*(uint *)(param_1 + 0x5e0) & 0x5000000) == 0) {
            *(undefined1 *)(param_1 + 0x6cb) = 1;
          }
          else {
            *(undefined1 *)(param_1 + 0x6cb) = 2;
            *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
          }
          zz_006a750_(param_1,9);
          zz_006a6fc_(param_1,9);
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x6cc) = 0;
      }
    }
  }
  return;
}



// ==== 80059f5c  FUN_80059f5c ====

void FUN_80059f5c(int param_1)

{
  float fVar1;
  double dVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x81000003) == 0) {
    if ((int)*(char *)(param_1 + 0x5e4) != (int)*(char *)(param_1 + 0x5e5)) {
      zz_006a6fc_(param_1,(int)*(char *)(param_1 + 0x5e4));
    }
    dVar2 = DOUBLE_804373d0;
    if (*(char *)(param_1 + 0x661) != '\n') {
      iVar4 = 0;
      fVar1 = FLOAT_804373c4 * (FLOAT_804373c8 - *(float *)(param_1 + 0x1dc8)) + FLOAT_804373c0;
      iVar5 = 8;
      do {
        iVar3 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + iVar4 + 0xb0);
        if (iVar3 == -1) break;
        iVar4 = iVar4 + 1;
        iVar3 = param_1 + iVar3 * 6;
        local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x18d4)) ^ 0x80000000);
        *(short *)(iVar3 + 0x18d4) = (short)(int)((float)(local_38 - dVar2) * fVar1);
        local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x18d6)) ^ 0x80000000);
        *(short *)(iVar3 + 0x18d6) = (short)(int)((float)(local_28 - dVar2) * fVar1);
        local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar3 + 0x18d8)) ^ 0x80000000);
        *(short *)(iVar3 + 0x18d8) = (short)(int)((float)(local_18 - dVar2) * fVar1);
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      dVar2 = DOUBLE_804373d0;
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
      *(short *)(param_1 + 0x18da) = (short)(int)((float)(local_10 - DOUBLE_804373d0) * fVar1);
      local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18dc)) ^ 0x80000000);
      *(short *)(param_1 + 0x18dc) = (short)(int)((float)(local_20 - dVar2) * fVar1);
      local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18de)) ^ 0x80000000);
      *(short *)(param_1 + 0x18de) = (short)(int)((float)(local_30 - dVar2) * fVar1);
    }
  }
  else if ((*(byte *)(param_1 + 0x1d9) & 0xf0) != 0) {
    *(byte *)(param_1 + 0x57a) = *(byte *)(param_1 + 0x57a) | *(byte *)(param_1 + 0x57b);
  }
  return;
}



// ==== 8005a144  FUN_8005a144 ====

void FUN_8005a144(int param_1)

{
  short sVar1;
  
  if (0 < *(short *)(param_1 + 0x6bc)) {
    sVar1 = *(short *)(param_1 + 0x6bc) + -1;
    *(short *)(param_1 + 0x6bc) = sVar1;
    if ((sVar1 < 1) && (*(code **)(param_1 + 0x4dc) != (code *)0x0)) {
      (**(code **)(param_1 + 0x4dc))();
    }
  }
  return;
}



// ==== 8005a190  FUN_8005a190 ====

undefined4 FUN_8005a190(int param_1)

{
  uint uVar1;
  short sVar2;
  
  if (((*(char *)(param_1 + 0x4a1) == '\0') && (*(char *)(param_1 + 0x4a0) == '\0')) &&
     (*(char *)(param_1 + 0x6fc) == '\0')) {
    if (*(char *)(param_1 + 0x48a) == '\x02') {
      if (*(short *)(param_1 + 0x49c) < 1) {
        uVar1 = zz_006ab9c_(param_1);
        if (uVar1 != 0) {
          FUN_8006aab0(param_1);
          zz_0176ec0_(param_1,*(undefined1 *)(param_1 + 0x88),0);
          return 1;
        }
      }
      else {
        *(short *)(param_1 + 0x49c) = *(short *)(param_1 + 0x49c) + -1;
      }
    }
    else if (((*(char *)(param_1 + 0x490) == '\x02') && (0 < *(short *)(param_1 + 0x49a))) &&
            (sVar2 = *(short *)(param_1 + 0x49a) + -1, *(short *)(param_1 + 0x49a) = sVar2,
            sVar2 < 1)) {
      uVar1 = FUN_8006abb8(param_1);
      if (uVar1 != 0) {
        FUN_8006a980(param_1);
        *(undefined1 *)(param_1 + 0x489) = 4;
        *(undefined1 *)(param_1 + 0x19) = 3;
        return 1;
      }
      *(undefined2 *)(param_1 + 0x49a) = 1;
    }
    return 0;
  }
  return 0;
}



// ==== 8005a298  FUN_8005a298 ====

void FUN_8005a298(int param_1)

{
  uint uVar1;
  
  if ((*(byte *)(param_1 + 0x7d2) & 3) == 1) {
    if ((*(uint *)(param_1 + 0x5b4) & 0x10) == 0) {
      *(undefined1 *)(param_1 + 0x73c) = 4;
    }
  }
  else if (*(char *)(param_1 + 0x73f) == '\0') {
    if (*(char *)(param_1 + 0x73c) == '\0') {
      if (*(char *)(param_1 + 0x4a1) == '\0') {
        uVar1 = zz_0010514_((int)*(char *)(param_1 + 0x3e4));
        if (uVar1 == 0) {
          uVar1 = *(uint *)(param_1 + 0x5d4);
          if ((uVar1 & 4) == 0) {
            if ((uVar1 & 8) == 0) {
              if ((uVar1 & 0x10) != 0) {
                *(undefined1 *)(param_1 + 0x73c) = 5;
              }
            }
            else {
              *(undefined1 *)(param_1 + 0x73c) = 3;
            }
          }
          else {
            *(undefined1 *)(param_1 + 0x73c) = 2;
          }
        }
      }
      else if (*(int *)(param_1 + 0x508) == *(int *)(param_1 + 0x4a4)) {
        *(undefined1 *)(param_1 + 0x73c) = 2;
      }
    }
  }
  return;
}



// ==== 8005a378  FUN_8005a378 ====

void FUN_8005a378(int param_1)

{
  float fVar1;
  int iVar2;
  short sVar3;
  char cVar4;
  
  fVar1 = FLOAT_804373c8;
  if (*(char *)(param_1 + 0x4a1) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804373c8;
    *(float *)(param_1 + 0x5f4) = fVar1;
    *(float *)(param_1 + 0x768) = fVar1;
    return;
  }
  if (*(char *)(param_1 + 0x4a0) == '\x02') {
    iVar2 = *(int *)(param_1 + 0x4a4);
    *(undefined4 *)(param_1 + 0x768) = *(undefined4 *)(iVar2 + 0x768);
    *(undefined4 *)(param_1 + 0x5f4) = *(undefined4 *)(iVar2 + 0x5f4);
    *(undefined4 *)(param_1 + 0x1dc8) = *(undefined4 *)(iVar2 + 0x1dc8);
    return;
  }
  if (*(short *)(param_1 + 0x710) != 0) {
    sVar3 = *(short *)(param_1 + 0x710) + -1;
    *(short *)(param_1 + 0x710) = sVar3;
    if (sVar3 < 1) {
      *(undefined1 *)(param_1 + 0x70e) = 0;
    }
  }
  if (*(short *)(param_1 + 0x712) != 0) {
    sVar3 = *(short *)(param_1 + 0x712) + -1;
    *(short *)(param_1 + 0x712) = sVar3;
    if (sVar3 < 1) {
      *(undefined1 *)(param_1 + 0x70f) = 0;
    }
  }
  *(float *)(param_1 + 0x768) = FLOAT_804373c8;
  if (*(char *)(param_1 + 0x6fc) != '\0') {
    *(float *)(param_1 + 0x768) = FLOAT_804373d8;
  }
  if (*(char *)(param_1 + 0x70d) != '\0') {
    *(float *)(param_1 + 0x768) =
         *(float *)(param_1 + 0x768) * *(float *)(&DAT_802dd58c + *(char *)(param_1 + 0x70d) * 4);
  }
  if (*(char *)(param_1 + 0x70f) != '\0') {
    *(float *)(param_1 + 0x768) =
         *(float *)(param_1 + 0x768) * *(float *)(&DAT_802dd58c + *(char *)(param_1 + 0x70f) * 4);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
    if (*(char *)(param_1 + 0x6fc) == '\0') {
      if (*(char *)(param_1 + 0x4a0) == '\0') {
        if (*(char *)(param_1 + 0x70c) != '\0') {
          *(float *)(param_1 + 0x768) =
               *(float *)(param_1 + 0x768) *
               *(float *)(&DAT_802dd57c + *(char *)(param_1 + 0x70c) * 4);
        }
        if (*(char *)(param_1 + 0x70e) != '\0') {
          *(float *)(param_1 + 0x768) =
               *(float *)(param_1 + 0x768) *
               *(float *)(&DAT_802dd57c + *(char *)(param_1 + 0x70e) * 4);
        }
      }
    }
  }
  if (*(char *)(param_1 + 0x71c) != '\0') {
    cVar4 = *(char *)(param_1 + 0x71c) + -1;
    *(char *)(param_1 + 0x71c) = cVar4;
    fVar1 = FLOAT_804373dc;
    if (cVar4 != '\0') {
      *(float *)(param_1 + 0x5f4) = FLOAT_804373dc;
      *(float *)(param_1 + 0x1dc8) = fVar1;
      return;
    }
    *(undefined4 *)(param_1 + 0x5f4) = *(undefined4 *)(param_1 + 0x768);
    *(float *)(param_1 + 0x1dc8) =
         *(float *)(param_1 + 0x1dd0) * *(float *)(param_1 + 0x1dcc) * *(float *)(param_1 + 0x768);
    return;
  }
  *(undefined4 *)(param_1 + 0x5f4) = *(undefined4 *)(param_1 + 0x768);
  *(float *)(param_1 + 0x1dc8) =
       *(float *)(param_1 + 0x1dd0) * *(float *)(param_1 + 0x1dcc) * *(float *)(param_1 + 0x768);
  return;
}



// ==== 8005a580  FUN_8005a580 ====

uint FUN_8005a580(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  uint uVar4;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(char *)(param_1 + 0x4a1) == '\0') {
    uVar4 = 0;
    fVar3 = FLOAT_804373e0 + *(float *)(DAT_8043625c + 0x3c);
    if (fVar3 <= *(float *)(param_1 + 0x20)) {
      fVar3 = *(float *)(DAT_8043625c + 0x38) - FLOAT_804373e0;
      if (fVar3 < *(float *)(param_1 + 0x20)) {
        *(float *)(param_1 + 0x20) = fVar3;
        if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
          sVar2 = *(short *)(param_1 + 0x5ae);
          if (sVar2 < 1) {
            if ((sVar2 == 0) || (sVar2 == -0x7fff)) {
              *(undefined2 *)(param_1 + 0x5ae) = 0x4000;
            }
          }
          else {
            *(short *)(param_1 + 0x5ae) = -sVar2;
          }
          fVar3 = FLOAT_804373ec;
          if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
            *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
            *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38) - fVar3;
            local_18 = *(undefined4 *)(param_1 + 0x20);
            local_14 = *(undefined4 *)(param_1 + 0x920);
            local_10 = *(undefined4 *)(param_1 + 0x28);
            FUN_80092ecc(1,&local_18,(undefined4 *)&DAT_802b0ccc);
            FUN_80092ecc(2,(undefined4 *)&DAT_802d33cc,(undefined4 *)&DAT_802b0ccc);
            *(undefined1 *)(param_1 + 0x71c) = 6;
            cVar1 = *(char *)(param_1 + 1000);
            if ((((cVar1 == '\x04') || (cVar1 == '\x06')) || ((byte)(cVar1 - 0xcU) < 2)) ||
               (cVar1 == '\x0e')) {
              zz_00f036c_(param_1,0x13);
            }
            else {
              zz_00f036c_(param_1,0x10);
            }
          }
        }
        uVar4 = 2;
      }
    }
    else {
      *(float *)(param_1 + 0x20) = fVar3;
      if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
        sVar2 = *(short *)(param_1 + 0x5ae);
        if (sVar2 < 0) {
          *(short *)(param_1 + 0x5ae) = -sVar2;
        }
        else if ((sVar2 == 0) || (sVar2 == -0x7fff)) {
          *(undefined2 *)(param_1 + 0x5ae) = 0xc000;
        }
        fVar3 = FLOAT_804373ec;
        if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
          *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
          *(float *)(param_1 + 0x20) = fVar3 + *(float *)(DAT_8043625c + 0x3c);
          local_18 = *(undefined4 *)(param_1 + 0x20);
          local_14 = *(undefined4 *)(param_1 + 0x920);
          local_10 = *(undefined4 *)(param_1 + 0x28);
          FUN_80092ecc(1,&local_18,&DAT_802b0ca8);
          FUN_80092ecc(2,(undefined4 *)&DAT_802d33d8,&DAT_802b0ca8);
          *(undefined1 *)(param_1 + 0x71c) = 6;
          cVar1 = *(char *)(param_1 + 1000);
          if (((cVar1 == '\x04') || (cVar1 == '\x06')) ||
             (((byte)(cVar1 - 0xcU) < 2 || (cVar1 == '\x0e')))) {
            zz_00f036c_(param_1,0x13);
          }
          else {
            zz_00f036c_(param_1,0x10);
          }
        }
      }
      uVar4 = 2;
    }
    fVar3 = FLOAT_804373e0 + *(float *)(DAT_8043625c + 0x44);
    if (fVar3 <= *(float *)(param_1 + 0x28)) {
      fVar3 = *(float *)(DAT_8043625c + 0x40) - FLOAT_804373e0;
      if (fVar3 < *(float *)(param_1 + 0x28)) {
        *(float *)(param_1 + 0x28) = fVar3;
        if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
          sVar2 = *(short *)(param_1 + 0x5ae);
          if ((sVar2 < 0x4000) && (-0x4000 < sVar2)) {
            *(short *)(param_1 + 0x5ae) = -(sVar2 + -0x8000);
          }
          else if ((sVar2 == 0x4000) || (sVar2 == -0x4000)) {
            *(undefined2 *)(param_1 + 0x5ae) = 0x8000;
          }
          fVar3 = FLOAT_804373ec;
          if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
            *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
            *(float *)(param_1 + 0x28) = *(float *)(DAT_8043625c + 0x40) - fVar3;
            local_18 = *(undefined4 *)(param_1 + 0x20);
            local_14 = *(undefined4 *)(param_1 + 0x920);
            local_10 = *(undefined4 *)(param_1 + 0x28);
            FUN_80092ecc(1,&local_18,&DAT_802b0ce4);
            FUN_80092ecc(2,(undefined4 *)&DAT_802d33c0,&DAT_802b0ce4);
            *(undefined1 *)(param_1 + 0x71c) = 6;
            cVar1 = *(char *)(param_1 + 1000);
            if ((((cVar1 == '\x04') || (cVar1 == '\x06')) || ((byte)(cVar1 - 0xcU) < 2)) ||
               (cVar1 == '\x0e')) {
              zz_00f036c_(param_1,0x13);
            }
            else {
              zz_00f036c_(param_1,0x10);
            }
          }
        }
        uVar4 = 3;
      }
    }
    else {
      *(float *)(param_1 + 0x28) = fVar3;
      if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
        sVar2 = *(short *)(param_1 + 0x5ae);
        if ((sVar2 < 0x4001) && (-0x4001 < sVar2)) {
          if ((sVar2 == 0x4000) || (sVar2 == -0x4000)) {
            *(undefined2 *)(param_1 + 0x5ae) = 0;
          }
        }
        else {
          *(short *)(param_1 + 0x5ae) = -(sVar2 + -0x8000);
        }
        fVar3 = FLOAT_804373ec;
        if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
          *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
          *(float *)(param_1 + 0x28) = fVar3 + *(float *)(DAT_8043625c + 0x44);
          local_18 = *(undefined4 *)(param_1 + 0x20);
          local_14 = *(undefined4 *)(param_1 + 0x920);
          local_10 = *(undefined4 *)(param_1 + 0x28);
          FUN_80092ecc(1,&local_18,&DAT_802b0cc0);
          FUN_80092ecc(2,(undefined4 *)&DAT_802d33e4,&DAT_802b0cc0);
          *(undefined1 *)(param_1 + 0x71c) = 6;
          cVar1 = *(char *)(param_1 + 1000);
          if ((((cVar1 == '\x04') || (cVar1 == '\x06')) || ((byte)(cVar1 - 0xcU) < 2)) ||
             (cVar1 == '\x0e')) {
            zz_00f036c_(param_1,0x13);
          }
          else {
            zz_00f036c_(param_1,0x10);
          }
        }
      }
      uVar4 = 3;
    }
    if ((uVar4 & 1) != 0) {
      fVar3 = FLOAT_804373e0 + *(float *)(DAT_8043625c + 0x3c);
      if (fVar3 <= *(float *)(param_1 + 0x20)) {
        fVar3 = *(float *)(DAT_8043625c + 0x38) - FLOAT_804373e0;
        if ((fVar3 < *(float *)(param_1 + 0x20)) &&
           (*(float *)(param_1 + 0x20) = fVar3, (*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0)) {
          sVar2 = *(short *)(param_1 + 0x5ae);
          if (sVar2 < 0) {
            *(short *)(param_1 + 0x5ae) = -sVar2;
          }
          else if ((sVar2 == 0) || (sVar2 == -0x7fff)) {
            *(undefined2 *)(param_1 + 0x5ae) = 0x4000;
          }
          fVar3 = FLOAT_804373ec;
          if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
            *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
            *(float *)(param_1 + 0x20) = *(float *)(DAT_8043625c + 0x38) - fVar3;
            local_18 = *(undefined4 *)(param_1 + 0x20);
            local_14 = *(undefined4 *)(param_1 + 0x920);
            local_10 = *(undefined4 *)(param_1 + 0x28);
            FUN_80092ecc(1,&local_18,(undefined4 *)&DAT_802b0ccc);
            FUN_80092ecc(2,(undefined4 *)&DAT_802d33cc,(undefined4 *)&DAT_802b0ccc);
            *(undefined1 *)(param_1 + 0x71c) = 6;
            cVar1 = *(char *)(param_1 + 1000);
            if ((((cVar1 == '\x04') || (cVar1 == '\x06')) || ((byte)(cVar1 - 0xcU) < 2)) ||
               (cVar1 == '\x0e')) {
              zz_00f036c_(param_1,0x13);
            }
            else {
              zz_00f036c_(param_1,0x10);
            }
          }
        }
      }
      else {
        *(float *)(param_1 + 0x20) = fVar3;
        if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
          sVar2 = *(short *)(param_1 + 0x5ae);
          if (sVar2 < 1) {
            if ((sVar2 == 0) || (sVar2 == -0x7fff)) {
              *(undefined2 *)(param_1 + 0x5ae) = 0xc000;
            }
          }
          else {
            *(short *)(param_1 + 0x5ae) = -sVar2;
          }
          fVar3 = FLOAT_804373ec;
          if (*(float *)(param_1 + 0x6a0) <= FLOAT_804373e4) {
            *(float *)(param_1 + 0x6a0) = FLOAT_804373e8;
            *(float *)(param_1 + 0x20) = fVar3 + *(float *)(DAT_8043625c + 0x3c);
            local_18 = *(undefined4 *)(param_1 + 0x20);
            local_14 = *(undefined4 *)(param_1 + 0x920);
            local_10 = *(undefined4 *)(param_1 + 0x28);
            FUN_80092ecc(1,&local_18,&DAT_802b0ca8);
            FUN_80092ecc(2,(undefined4 *)&DAT_802d33d8,&DAT_802b0ca8);
            *(undefined1 *)(param_1 + 0x71c) = 6;
            cVar1 = *(char *)(param_1 + 1000);
            if (((cVar1 == '\x04') || (cVar1 == '\x06')) ||
               (((byte)(cVar1 - 0xcU) < 2 || (cVar1 == '\x0e')))) {
              zz_00f036c_(param_1,0x13);
            }
            else {
              zz_00f036c_(param_1,0x10);
            }
          }
        }
      }
    }
    if ((uVar4 & 2) != 0) {
      zz_00677b0_(param_1);
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 8005ace8  FUN_8005ace8 ====

/* WARNING: Removing unreachable block (ram,0x8005b118) */
/* WARNING: Removing unreachable block (ram,0x8005b110) */
/* WARNING: Removing unreachable block (ram,0x8005ad00) */
/* WARNING: Removing unreachable block (ram,0x8005acf8) */

void FUN_8005ace8(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined2 uVar5;
  undefined4 uVar4;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  iVar11 = 0;
  pcVar10 = DAT_803c4e84;
  do {
    if (PTR_DAT_80433934[pcVar10[0x88] * 0x3c + 0x104] == '\0') {
      if (pcVar10[0x4a0] == '\0') {
        if (((PTR_DAT_80433934[pcVar10[0x88] * 0x3c + 0x103] != '\0') && (*pcVar10 != '\0')) &&
           (pcVar10[0x18] == '\x01')) {
          cVar1 = pcVar10[0x4a1];
          if (cVar1 == '\x05') {
            if (*(char *)(*(int *)(pcVar10 + 0x4a4) + 0x4a1) == '\x05') {
              pcVar10[0x4a1] = '\x06';
              *(undefined1 *)(*(int *)(pcVar10 + 0x4a4) + 0x4a1) = 6;
            }
          }
          else if (cVar1 < '\x05') {
            if (((cVar1 == '\x02') && (pcVar7 = *(char **)(pcVar10 + 0x4a4), pcVar7 != (char *)0x0))
               && ((*pcVar7 != '\0' && ((pcVar7[0x18] == '\x01' && (pcVar7[0x4a1] == '\x02')))))) {
              pcVar10[0x4a1] = '\x03';
              pcVar7[0x4a1] = '\x03';
              pcVar10[0x6fa] = '\x01';
              pcVar7[0x6fa] = '\x01';
              fVar3 = FLOAT_804373f0;
              fVar2 = FLOAT_804373e4;
              pcVar9 = pcVar10;
              if (pcVar10[0x4a8] == '\x01') {
                pcVar9 = pcVar7;
                pcVar7 = pcVar10;
              }
              uVar5 = (undefined2)
                      (((int)*(short *)(pcVar7 + 0x72) + (int)*(short *)(pcVar9 + 0x72)) / 2);
              *(undefined2 *)(pcVar9 + 0x5a8) = uVar5;
              *(undefined2 *)(pcVar9 + 0x5ac) = uVar5;
              *(undefined2 *)(pcVar7 + 0x5a8) = uVar5;
              *(undefined2 *)(pcVar7 + 0x5ac) = uVar5;
              *(short *)(pcVar7 + 0x5aa) = *(short *)(pcVar7 + 0x5ac) - *(short *)(pcVar7 + 0x72);
              *(short *)(pcVar9 + 0x5aa) = *(short *)(pcVar9 + 0x5ac) - *(short *)(pcVar9 + 0x72);
              *(float *)(pcVar7 + 0x7a4) =
                   (*(float *)(pcVar7 + 0x20) + *(float *)(pcVar9 + 0x20)) * fVar3;
              *(float *)(pcVar7 + 0x7a8) = fVar2;
              *(float *)(pcVar7 + 0x7ac) =
                   (*(float *)(pcVar7 + 0x28) + *(float *)(pcVar9 + 0x28)) * fVar3;
              dVar12 = FUN_8003d964((double)*(float *)(DAT_8043625c + 0x34),(int)pcVar7,
                                    (float *)(pcVar7 + 0x7a4));
              *(float *)(pcVar7 + 0x7a8) = (float)dVar12;
              uVar4 = *(undefined4 *)(pcVar7 + 0x7a8);
              *(undefined4 *)(pcVar9 + 0x7a4) = *(undefined4 *)(pcVar7 + 0x7a4);
              *(undefined4 *)(pcVar9 + 0x7a8) = uVar4;
              *(undefined4 *)(pcVar9 + 0x7ac) = *(undefined4 *)(pcVar7 + 0x7ac);
              fVar2 = FLOAT_804373f8;
              if (pcVar7[1000] == '\x06') {
                *(float *)(pcVar7 + 0x7a8) =
                     FLOAT_804373f4 * *(float *)(*(int *)(pcVar9 + 0x4b0) + 0x4c) +
                     *(float *)(pcVar7 + 0x7a8);
                *(float *)(pcVar9 + 0x7a8) =
                     fVar2 * *(float *)(*(int *)(pcVar9 + 0x4b0) + 0x4c) +
                     *(float *)(pcVar9 + 0x7a8);
              }
              else {
                dVar14 = (double)FLOAT_804373fc;
                dVar12 = (double)FLOAT_80437400;
                if ((*(short *)(pcVar7 + 0x48c) == 0x513) || (*(short *)(pcVar9 + 0x48c) == 0x513))
                {
                  dVar14 = (double)(float)(dVar14 * (double)FLOAT_804373f0);
                  dVar12 = (double)(float)(dVar12 * (double)FLOAT_804373f0);
                }
                if (*(int *)(pcVar7 + 0x508) != 0) {
                  iVar8 = FUN_800452a0((double)(*(float *)(pcVar7 + 0x50c) -
                                               *(float *)(pcVar7 + 0x7a4)),
                                       (double)(*(float *)(pcVar7 + 0x514) -
                                               *(float *)(pcVar7 + 0x7ac)));
                  uVar5 = (undefined2)iVar8;
                  *(undefined2 *)(pcVar9 + 0x5a8) = uVar5;
                  *(undefined2 *)(pcVar9 + 0x5ac) = uVar5;
                  *(undefined2 *)(pcVar7 + 0x5a8) = uVar5;
                  *(undefined2 *)(pcVar7 + 0x5ac) = uVar5;
                  *(short *)(pcVar7 + 0x5aa) =
                       *(short *)(pcVar7 + 0x5ac) - *(short *)(pcVar7 + 0x72);
                  *(short *)(pcVar9 + 0x5aa) =
                       *(short *)(pcVar9 + 0x5ac) - *(short *)(pcVar9 + 0x72);
                }
                dVar13 = (double)FLOAT_80437408;
                *(float *)(pcVar9 + 0x7a8) =
                     FLOAT_80437404 * *(float *)(*(int *)(pcVar9 + 0x4b0) + 0x4c) +
                     *(float *)(pcVar9 + 0x7a8);
                *(float *)(pcVar7 + 0x7a8) =
                     *(float *)(pcVar7 + 0x7a8) +
                     (float)(dVar13 * (double)*(float *)(*(int *)(pcVar9 + 0x4b0) + 0x4c) + dVar12);
                dVar12 = zz_0045204_(*(short *)(pcVar7 + 0x5ac));
                *(float *)(pcVar7 + 0x7a4) =
                     (float)(dVar14 * dVar12 + (double)*(float *)(pcVar9 + 0x7a4));
                dVar12 = zz_0045238_(*(short *)(pcVar7 + 0x5ac));
                *(float *)(pcVar7 + 0x7ac) =
                     (float)(dVar14 * dVar12 + (double)*(float *)(pcVar9 + 0x7ac));
              }
              FUN_80068138((int)pcVar7);
              FUN_80068138((int)pcVar9);
            }
          }
          else if ((cVar1 == '\a') &&
                  (iVar8 = *(int *)(pcVar10 + 0x4a4), *(char *)(iVar8 + 0x4a1) == '\a')) {
            pcVar10[0x4a1] = '\0';
            pcVar10[0x4a0] = pcVar10[0x4a9];
            pcVar10[0x272] = -1;
            pcVar10[0x273] = -1;
            zz_006a868_((int)pcVar10,*(undefined2 *)(pcVar10 + 0x48c),pcVar10[0x48e]);
            *(undefined1 *)(iVar8 + 0x4a1) = 0;
            *(undefined1 *)(iVar8 + 0x4a0) = *(undefined1 *)(iVar8 + 0x4a9);
            *(undefined2 *)(iVar8 + 0x272) = 0xffff;
            zz_006a868_(iVar8,*(undefined2 *)(iVar8 + 0x48c),*(undefined1 *)(iVar8 + 0x48e));
          }
        }
      }
      else {
        iVar8 = *(int *)(pcVar10 + 0x4a4);
        if ((((pcVar10[0x18] == '\x01') && (PTR_DAT_80433934[0x1f] == '\0')) &&
            (((*(uint *)(pcVar10 + 0x5e0) & 3) == 0 || (pcVar10[0x584] != '\x05')))) &&
           ((uVar6 = FUN_8006abb8((int)pcVar10), uVar6 != 0 &&
            (uVar6 = FUN_8006abb8(iVar8), uVar6 != 0)))) {
          if (pcVar10[0x4a8] == '\x02') {
            zz_00f6654_((int)pcVar10);
            zz_00f036c_((int)pcVar10,0x9b);
          }
          FUN_8006a980((int)pcVar10);
          *(uint *)(pcVar10 + 0x8c4) = *(uint *)(pcVar10 + 0x8c4) & 0xfffffffe;
        }
      }
    }
    iVar11 = iVar11 + 1;
    pcVar10 = pcVar10 + 0x1e00;
  } while (iVar11 < 6);
  return;
}



// ==== 8005b140  zz_005b140_ ====

void zz_005b140_(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  
  iVar5 = 0;
  pcVar4 = DAT_803c4e84;
  do {
    if ((*pcVar4 != '\0') && (pcVar4[0x4a0] == '\x02')) {
      cVar1 = pcVar4[0x18];
      iVar3 = *(int *)(pcVar4 + 0x4a4);
      if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
        uVar2 = *(undefined4 *)(iVar3 + 0x24);
        *(undefined4 *)(pcVar4 + 0x20) = *(undefined4 *)(iVar3 + 0x20);
        *(undefined4 *)(pcVar4 + 0x24) = uVar2;
        *(undefined4 *)(pcVar4 + 0x28) = *(undefined4 *)(iVar3 + 0x28);
        *(undefined4 *)(pcVar4 + 0x70) = *(undefined4 *)(iVar3 + 0x70);
        *(undefined2 *)(pcVar4 + 0x74) = *(undefined2 *)(iVar3 + 0x74);
        *(undefined2 *)(pcVar4 + 0x736) = *(undefined2 *)(iVar3 + 0x736);
        *(undefined2 *)(pcVar4 + 0x738) = *(undefined2 *)(iVar3 + 0x738);
        pcVar4[0x58a] = *(char *)(iVar3 + 0x58a);
        pcVar4[0x87] = *(char *)(iVar3 + 0x87);
        *(uint *)(pcVar4 + 0x5e0) =
             *(uint *)(pcVar4 + 0x5e0) & 0xff000f | *(uint *)(iVar3 + 0x5e0) & 0xff00fff0;
        pcVar4[0x74a] = *(char *)(iVar3 + 0x74a);
        zz_006826c_((int)pcVar4);
        if ((*(uint *)(pcVar4 + 0x5e0) & 2) != 0) {
          if ((pcVar4[0x584] == '\x05') &&
             (((*(uint *)(iVar3 + 0x5e0) & 2) == 0 || (*(char *)(iVar3 + 0x584) != '\x05')))) {
            pcVar4[0x73f] = '\0';
            *(uint *)(pcVar4 + 0x5e0) = *(uint *)(pcVar4 + 0x5e0) & 0xfffffffc;
          }
        }
      }
      else if ((cVar1 == '\x03') && (pcVar4[1000] == '\x05')) {
        *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(pcVar4 + 0xb20);
        *(undefined4 *)(iVar3 + 0x24) = *(undefined4 *)(pcVar4 + 0xb30);
        *(undefined4 *)(iVar3 + 0x28) = *(undefined4 *)(pcVar4 + 0xb40);
      }
    }
    iVar5 = iVar5 + 1;
    pcVar4 = pcVar4 + 0x1e00;
  } while (iVar5 < 6);
  return;
}



// ==== 8005b2b8  zz_005b2b8_ ====

void zz_005b2b8_(void)

{
  byte bVar1;
  short *psVar2;
  char cVar4;
  char *pcVar3;
  char *pcVar5;
  char *pcVar6;
  short *psVar7;
  int iVar8;
  undefined *puVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  char *pcVar15;
  int iVar16;
  undefined4 local_48 [8];
  
  pcVar6 = (char *)0x0;
  iVar16 = 2;
  psVar7 = DAT_803c4e84;
  do {
    if ((PTR_DAT_80433934[*(char *)(psVar7 + 0x44) * 0x3c + 0x104] == '\0') &&
       (*(char *)(psVar7 + 0x37e) != '\0')) {
      *(undefined1 *)(psVar7 + 0x37e) = 0;
      *(uint *)(psVar7 + 0x462) = *(uint *)(psVar7 + 0x462) & 0xfffffffe;
      *(undefined1 *)(psVar7 + 0x3ef) = 0;
    }
    if ((PTR_DAT_80433934[*(char *)(psVar7 + 0xf44) * 0x3c + 0x104] == '\0') &&
       (*(char *)(psVar7 + 0x127e) != '\0')) {
      *(undefined1 *)(psVar7 + 0x127e) = 0;
      *(uint *)(psVar7 + 0x1362) = *(uint *)(psVar7 + 0x1362) & 0xfffffffe;
      *(undefined1 *)(psVar7 + 0x12ef) = 0;
    }
    pcVar5 = PTR_DAT_80433934;
    if ((PTR_DAT_80433934[*(char *)(psVar7 + 0x1e44) * 0x3c + 0x104] == '\0') &&
       (*(char *)(psVar7 + 0x217e) != '\0')) {
      *(undefined1 *)(psVar7 + 0x217e) = 0;
      *(uint *)(psVar7 + 0x2262) = *(uint *)(psVar7 + 0x2262) & 0xfffffffe;
      *(undefined1 *)(psVar7 + 0x21ef) = 0;
    }
    pcVar6 = pcVar6 + 2;
    psVar7 = psVar7 + 0x2d00;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  piVar14 = &DAT_803c6dec;
  iVar16 = 0;
  puVar9 = PTR_DAT_80433934 + 0xf4;
  pcVar15 = &DAT_80436264;
  iVar13 = 0;
  do {
    if ((('\0' < *pcVar15) && (puVar9[0x10] == '\0')) && (puVar9[0xf] != '\0')) {
      iVar8 = 0;
      iVar10 = 0;
      piVar11 = piVar14;
      for (iVar12 = 0; iVar12 < *pcVar15; iVar12 = iVar12 + 1) {
        pcVar3 = (char *)*piVar11;
        if ((((pcVar3[0x6fb] != '\0') && (*pcVar3 != '\0')) &&
            ((pcVar3[0x18] == '\x01' && ((pcVar3[0x4a0] == '\0' && (pcVar3[0x4a1] == '\0')))))) &&
           ((cVar4 = zz_008b480_(), cVar4 == '\0' || ((PTR_DAT_80433934[0xeb] & pcVar3[0x3e5]) != 0)
            ))) {
          iVar10 = iVar10 + 1;
          *(char **)((int)local_48 + iVar8) = pcVar3;
          iVar8 = iVar8 + 4;
        }
        piVar11 = piVar11 + 1;
      }
      if (PTR_DAT_80433934[iVar13 + 0xf5] == '\x01') {
        if (0 < iVar10) {
LAB_8005b4b8:
          pcVar3 = zz_005b678_(local_48,iVar10,pcVar5,pcVar6,psVar7);
          if (pcVar3 == (char *)0x0) {
            puVar9[0xf] = 0;
            pcVar5 = (char *)0x0;
            puVar9[0x10] = 1;
            *(undefined2 *)(puVar9 + 0x1a) = 600;
            *(undefined2 *)(puVar9 + 0x18) = 600;
            iVar8 = 0;
            piVar11 = piVar14;
            for (iVar10 = 0; iVar10 < *pcVar15; iVar10 = iVar10 + 1) {
              iVar8 = *piVar11;
              if (*(char *)(iVar8 + 0x18) == '\x01') {
                *(undefined1 *)(iVar8 + 0x6fc) = 1;
                pcVar5 = (char *)((uint)pcVar5 | (int)*(char *)(iVar8 + 0x3e5));
                *(undefined1 *)(iVar8 + 0x6fa) = 1;
                FUN_800061a8(iVar8,3);
              }
              piVar11 = piVar11 + 1;
            }
            zz_0067f54_((int)*(char *)(iVar8 + 0x88),2,(char)pcVar5);
          }
          else {
            iVar8 = *(int *)(pcVar3 + 0x4a4);
            zz_005c15c_((int)pcVar3);
            zz_005c15c_(iVar8);
            *(uint *)(pcVar3 + 0x8c4) = *(uint *)(pcVar3 + 0x8c4) & 0xfffffffd;
            *(uint *)(iVar8 + 0x8c4) = *(uint *)(iVar8 + 0x8c4) & 0xfffffffd;
            pcVar3[0x4a1] = '\x01';
            *(undefined1 *)(iVar8 + 0x4a1) = 1;
            bVar1 = pcVar3[0x3e5] | *(byte *)(iVar8 + 0x3e5);
            pcVar5 = (char *)(int)(char)bVar1;
            zz_0067f54_((int)pcVar3[0x88],1,bVar1);
            zz_006a750_((int)pcVar3,0x19);
            zz_006a750_(iVar8,0x19);
          }
        }
      }
      else if (1 < iVar10) goto LAB_8005b4b8;
    }
    psVar2 = DAT_803c4e84;
    iVar16 = iVar16 + 1;
    piVar14 = piVar14 + 6;
    iVar13 = iVar13 + 0x3c;
    puVar9 = puVar9 + 0x3c;
    pcVar15 = pcVar15 + 1;
    if (3 < iVar16) {
      if (*(char *)((int)DAT_803c4e84 + 0x6fb) != '\0') {
        *(char *)((int)DAT_803c4e84 + 0x6fb) = *(char *)((int)DAT_803c4e84 + 0x6fb) + -1;
      }
      if (*(char *)((int)psVar2 + 0x24fb) != '\0') {
        *(char *)((int)psVar2 + 0x24fb) = *(char *)((int)psVar2 + 0x24fb) + -1;
      }
      if (*(char *)((int)psVar2 + 0x42fb) != '\0') {
        *(char *)((int)psVar2 + 0x42fb) = *(char *)((int)psVar2 + 0x42fb) + -1;
      }
      if (*(char *)((int)psVar2 + 0x60fb) != '\0') {
        *(char *)((int)psVar2 + 0x60fb) = *(char *)((int)psVar2 + 0x60fb) + -1;
      }
      if (*(char *)((int)psVar2 + 0x7efb) != '\0') {
        *(char *)((int)psVar2 + 0x7efb) = *(char *)((int)psVar2 + 0x7efb) + -1;
      }
      if (*(char *)((int)psVar2 + 0x9cfb) != '\0') {
        *(char *)((int)psVar2 + 0x9cfb) = *(char *)((int)psVar2 + 0x9cfb) + -1;
      }
      return;
    }
  } while( true );
}



// ==== 8005b678  zz_005b678_ ====

char * zz_005b678_(undefined4 *param_1,int param_2,char *param_3,char *param_4,short *param_5)

{
  bool bVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  
  if (param_2 < 2) {
    param_3 = (char *)0x0;
  }
  else {
    bVar1 = false;
    iVar7 = 0;
    puVar4 = param_1;
    while ((iVar7 < param_2 + -1 && (!bVar1))) {
      param_3 = (char *)*puVar4;
      if ((*(int *)(&DAT_802d352c + param_3[1000] * 4) != 0) &&
         (((psVar5 = *(short **)
                      (*(int *)(&DAT_802d352c + param_3[1000] * 4) + (uint)(byte)param_3[0x3e9] * 4)
           , psVar5 != (short *)0x0 && (*param_3 != '\0')) && (param_3[0x18] == '\x01')))) {
        iVar6 = iVar7 + 1;
        puVar3 = param_1 + iVar6;
        while ((iVar6 < param_2 && (!bVar1))) {
          param_4 = (char *)*puVar3;
          for (param_5 = psVar5; *param_5 != -1; param_5 = param_5 + 2) {
            if (*(short *)(param_4 + 1000) == *param_5) {
              bVar1 = true;
              break;
            }
          }
          puVar3 = puVar3 + 1;
          iVar6 = iVar6 + 1;
        }
      }
      puVar4 = puVar4 + 1;
      iVar7 = iVar7 + 1;
    }
    if (bVar1) {
      *(char **)(param_3 + 0x4a4) = param_4;
      *(char **)(param_4 + 0x4a4) = param_3;
      pcVar2 = param_4;
      if ((param_3[0x3e6] != '\0') && (param_4[0x3e6] == '\0')) {
        pcVar2 = *(char **)(param_4 + 0x4a4);
        param_3 = param_4;
      }
      if (((param_3[0x3e6] == '\0') && (param_3[0x4a8] == '\x02')) && (pcVar2[0x3e6] != '\0')) {
        *(short *)(param_3 + 0x48c) = param_5[1];
        *(short *)(pcVar2 + 0x48c) = param_5[1] + 1;
        param_3[0x4a9] = '\x01';
        pcVar2[0x4a9] = '\x02';
      }
      else {
        *(short *)(param_3 + 0x48c) = (short)param_3[0x4a8] + param_5[1] + -1;
        *(short *)(pcVar2 + 0x48c) = (short)pcVar2[0x4a8] + param_5[1] + -1;
        param_3[0x4a9] = param_3[0x4a8];
        pcVar2[0x4a9] = pcVar2[0x4a8];
      }
      if (param_3[0x4a8] == '\x01') {
        param_3[0x48e] = param_3[0x3ec];
        pcVar2[0x48e] = param_3[0x3ec];
      }
      else {
        param_3[0x48e] = pcVar2[0x3ec];
        pcVar2[0x48e] = pcVar2[0x3ec];
      }
    }
    else {
      param_3 = (char *)0x0;
    }
  }
  return param_3;
}



// ==== 8005b880  zz_005b880_ ====

void zz_005b880_(int param_1)

{
  ushort *puVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  double dVar5;
  double dVar6;
  
  if (*(int *)(param_1 + 0x4e8) != 0) {
    iVar2 = 0;
    iVar3 = param_1 + 0x1ad4;
    do {
      if (*(char *)(iVar3 + 0x37) != -1) {
        puVar4 = (ushort *)(*(int *)(param_1 + 0x4e8) + *(char *)(iVar3 + 0x37) * 8);
        do {
          if (*(char *)(puVar4 + 1) == '\0') {
            zz_005b98c_((double)*(float *)(iVar3 + 8),(double)*(float *)(iVar3 + 0x10),param_1,
                        puVar4);
          }
          else {
            dVar5 = (double)*(float *)(iVar3 + 0xc);
            dVar6 = (double)*(float *)(iVar3 + 0x14);
            if (dVar5 < dVar6) {
              zz_005b98c_((double)(float)(dVar5 + (double)(float)((double)CONCAT44(0x43300000,
                                                                                   (int)*(short *)(
                                                  iVar3 + 0x24) ^ 0x80000000) - DOUBLE_804373d0)),
                          dVar6,param_1,puVar4);
            }
            else {
              zz_005b98c_(dVar5,dVar6,param_1,puVar4);
            }
          }
          puVar1 = puVar4 + 3;
          puVar4 = puVar4 + 4;
        } while (*(char *)puVar1 != -1);
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x40;
    } while (iVar2 < 4);
  }
  return;
}



// ==== 8005b98c  zz_005b98c_ ====

/* WARNING: Removing unreachable block (ram,0x8005ba3c) */

void zz_005b98c_(double param_1,double param_2,int param_3,ushort *param_4)

{
  byte bVar1;
  uint uVar2;
  
  uVar2 = (uint)*param_4;
  if ((((double)FLOAT_804373e4 !=
        (double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_80437418)) ||
      (param_1 <= (double)FLOAT_804373e4)) &&
     (((float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_80437418) <= FLOAT_804373e4 ||
      (((double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_80437418) <= param_1 &&
       (param_2 < (double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_80437418))))))) {
    bVar1 = *(byte *)((int)param_4 + 3);
    if (bVar1 == 1) {
      if (FLOAT_8043740c <= *(float *)(param_3 + 0xb4)) {
        if (*(float *)(param_3 + 0xb4) <= FLOAT_80437410) {
          uVar2 = (uint)param_4[2];
        }
        else {
          uVar2 = param_4[2] + 1;
        }
      }
      else {
        uVar2 = param_4[2] - 1;
      }
      zz_00f036c_(param_3,uVar2);
    }
    else if (bVar1 == 0) {
      zz_00f036c_(param_3,(uint)param_4[2]);
    }
    else if ((bVar1 != 4) && (bVar1 < 4)) {
      zz_00f061c_((double)FLOAT_80437404,param_3,(uint)param_4[2]);
    }
  }
  return;
}



// ==== 8005bab8  zz_005bab8_ ====

void zz_005bab8_(int param_1)

{
  float fVar1;
  short sVar2;
  
  if (0 < *(short *)(param_1 + 0x750)) {
    sVar2 = *(short *)(param_1 + 0x750) + -1;
    *(short *)(param_1 + 0x750) = sVar2;
    if (sVar2 < 1) {
      zz_006817c_(param_1,-(int)*(char *)(param_1 + 0x74e));
      *(undefined2 *)(param_1 + 0x750) = 0;
      *(undefined1 *)(param_1 + 0x74e) = 0;
    }
  }
  fVar1 = *(float *)(param_1 + 0xb4);
  if ((*(float *)(param_1 + 0xb8) != fVar1) && (*(char *)(param_1 + 0x7c9) == '\0')) {
    if (*(float *)(param_1 + 0xb8) <= fVar1) {
      *(float *)(param_1 + 0xb4) = fVar1 - FLOAT_80437420;
      if (*(float *)(param_1 + 0xb4) <= *(float *)(param_1 + 0xb8)) {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb8);
        zz_003d3e8_(param_1);
      }
    }
    else {
      *(float *)(param_1 + 0xb4) = fVar1 + FLOAT_80437420;
      if (*(float *)(param_1 + 0xb8) <= *(float *)(param_1 + 0xb4)) {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb8);
        zz_003d3e8_(param_1);
      }
    }
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0xb4);
  }
  return;
}



// ==== 8005bbc0  zz_005bbc0_ ====

void zz_005bbc0_(int param_1)

{
  char cVar1;
  
  zz_005f00c_(param_1);
  zz_005efc4_(param_1,*(char *)(param_1 + 0x1da));
  if (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) != 0) {
    *(undefined1 *)(param_1 + 0x6fe) = 7;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 0;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80000000;
  *(undefined4 *)(param_1 + 0x8c4) = 0;
  *(undefined2 *)(param_1 + 0x710) = 0;
  *(undefined2 *)(param_1 + 0x712) = 0;
  PTR_DAT_80433934[0xea] = PTR_DAT_80433934[0xea] & ~*(byte *)(param_1 + 0x3e5);
  cVar1 = zz_008b480_();
  if (cVar1 != '\0') {
    if ((uint)(byte)PTR_DAT_80433934[0xee] == (int)*(char *)(param_1 + 0x3e4)) {
      zz_008b640_();
    }
  }
  zz_006a750_(param_1,0x2f);
  zz_006a6fc_(param_1,0x2f);
  zz_005c028_(param_1);
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
  if ((*(byte *)(param_1 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0) {
    zz_005bccc_(param_1);
  }
  return;
}



// ==== 8005bccc  zz_005bccc_ ====

void zz_005bccc_(int param_1)

{
  if (*(char *)(param_1 + 0x543) == '\0') {
    *(undefined1 *)(param_1 + 0x543) = 1;
    if ((*(char *)(param_1 + 0x6fe) < 9) && (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) != 0)) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    }
    zz_005c15c_(param_1);
    (**(code **)(param_1 + 0x4cc))(param_1);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x443;
    *(undefined1 *)(param_1 + 0x5e6) = 0;
    *(undefined1 *)(param_1 + 0x656) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x80000000;
    if ((*(char *)(param_1 + 0x6fe) < 9) && (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) != 0)) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    }
    if (*(char *)(param_1 + 0x491) < (char)PTR_DAT_80433934[*(char *)(param_1 + 0x3e4) + 0x5a]) {
      zz_00ea2c8_(param_1,9);
    }
    else {
      zz_00ea2c8_(param_1,9);
    }
  }
  (*(code *)(&PTR_FUN_802d3570)[*(char *)(param_1 + 0x540)])(param_1);
  *(undefined1 *)(param_1 + 0x656) = 1;
  return;
}



// ==== 8005be08  FUN_8005be08 ====

void FUN_8005be08(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x591) != '\a') {
    if (*(char *)(param_1 + 0x663) == '\0') {
      zz_005c694_(param_1);
    }
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - FLOAT_80437428;
  if ((*(uint *)(param_1 + 0x5e0) & 0xc000000) != 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043742c;
  }
  if ((*(char *)(param_1 + 0x541) == '\0') && (*(float *)(param_1 + 0x558) < FLOAT_80437430)) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    iVar1 = zz_0006f98_(param_1);
    *(undefined4 *)(iVar1 + 0xc28) = 0xffffffff;
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_8043742c) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  return;
}



// ==== 8005bec8  FUN_8005bec8 ====

void FUN_8005bec8(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437434;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (*(short *)(param_1 + 1000) == 0xe04) {
    zz_00c1f70_(param_1,1);
  }
  else {
    zz_00c1f70_(param_1,0);
  }
  iVar2 = *(int *)(param_1 + 0x5a4);
  if ((iVar2 != 0) && (PTR_DAT_80433934[0x1f] == '\0')) {
    if ((*(char *)(iVar2 + 0x18) == '\x01') && ((*(uint *)(iVar2 + 0x5e0) & 0x1000000) == 0)) {
      zz_00ea2c8_(iVar2,8);
    }
  }
  zz_00680d4_(param_1,2);
  return;
}



// ==== 8005bf6c  FUN_8005bf6c ====

void FUN_8005bf6c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043742c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - FLOAT_80437428;
  if (*(float *)(param_1 + 0x558) < fVar1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x71b) = 0;
    *(undefined1 *)(param_1 + 0x490) = 0;
    *(undefined1 *)(param_1 + 0x489) = 0;
    *(undefined1 *)(param_1 + 0x48a) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x662) = 1;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 8005c028  zz_005c028_ ====

void zz_005c028_(int param_1)

{
  if (*(char *)(param_1 + 0x591) == '\a') {
    *(float *)(param_1 + 0x558) = FLOAT_80437428;
    return;
  }
  if (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) == 0) {
    *(float *)(param_1 + 0x558) = FLOAT_8043743c;
  }
  else {
    *(float *)(param_1 + 0x558) = FLOAT_80437438;
  }
  if (*(char *)(param_1 + 0x663) == '\0') {
    return;
  }
  *(float *)(param_1 + 0x558) = FLOAT_80437428;
  return;
}



// ==== 8005c080  zz_005c080_ ====

void zz_005c080_(int param_1)

{
  float fVar1;
  char cVar2;
  
  fVar1 = FLOAT_80437444;
  *(float *)(param_1 + 0x1dcc) = FLOAT_80437440;
  *(float *)(param_1 + 0x1d9c) = fVar1;
  *(undefined1 *)(param_1 + 0x1db2) = 0;
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0x43;
  *(undefined1 *)(param_1 + 0x709) = 0;
  if (*(char *)(param_1 + 0x4a1) != '\0') {
    *(undefined1 *)(param_1 + 0x4a1) = 0;
    *(undefined1 *)(*(int *)(param_1 + 0x4a4) + 0x4a1) = 0;
    cVar2 = zz_008b290_();
    if (cVar2 == '\x01') {
      if ((((uint)(byte)PTR_DAT_80433934[0xd8] & 1 << (int)*(char *)(param_1 + 0x88)) != 0) &&
         ((PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0x101] & *(byte *)(param_1 + 0x3e5))
          != 0)) {
        zz_008b1e8_();
      }
    }
    zz_0067f74_((int)*(char *)(param_1 + 0x88));
  }
  *(undefined1 *)(param_1 + 0x6fb) = 0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  (**(code **)(param_1 + 0x4c4))(param_1);
  return;
}



// ==== 8005c15c  zz_005c15c_ ====

void zz_005c15c_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  zz_005c080_(param_1);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0x5ff0040;
  *(undefined1 *)(param_1 + 0x1d9a) = 0;
  if (*(char *)(param_1 + 0x661) != '\n') {
    iVar2 = 0;
    iVar3 = 2;
    do {
      iVar1 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + iVar2 + 0xb0);
      if (iVar1 == -1) break;
      iVar1 = param_1 + iVar1 * 6;
      *(undefined2 *)(iVar1 + 0x18d8) = 0;
      *(undefined2 *)(iVar1 + 0x18d6) = 0;
      *(undefined2 *)(iVar1 + 0x18d4) = 0;
      iVar1 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + iVar2 + 0xb1);
      if (iVar1 == -1) break;
      iVar1 = param_1 + iVar1 * 6;
      *(undefined2 *)(iVar1 + 0x18d8) = 0;
      *(undefined2 *)(iVar1 + 0x18d6) = 0;
      *(undefined2 *)(iVar1 + 0x18d4) = 0;
      iVar1 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + iVar2 + 0xb2);
      if (iVar1 == -1) break;
      iVar1 = param_1 + iVar1 * 6;
      *(undefined2 *)(iVar1 + 0x18d8) = 0;
      *(undefined2 *)(iVar1 + 0x18d6) = 0;
      *(undefined2 *)(iVar1 + 0x18d4) = 0;
      iVar1 = (int)*(char *)(*(int *)(param_1 + 0x4b0) + iVar2 + 0xb3);
      if (iVar1 == -1) break;
      iVar2 = iVar2 + 4;
      iVar1 = param_1 + iVar1 * 6;
      *(undefined2 *)(iVar1 + 0x18d8) = 0;
      *(undefined2 *)(iVar1 + 0x18d6) = 0;
      *(undefined2 *)(iVar1 + 0x18d4) = 0;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    *(undefined2 *)(param_1 + 0x18de) = 0;
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined2 *)(param_1 + 0x1d68) = 0;
    *(undefined2 *)(param_1 + 0x1d66) = 0;
    *(undefined2 *)(param_1 + 0x1d64) = 0;
  }
  return;
}



// ==== 8005c290  zz_005c290_ ====

void zz_005c290_(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = *(uint *)(param_1 + 0x5e0);
  if (*(char *)(param_1 + 0x4a0) != '\x02') {
    if (*(byte *)(param_1 + 0x6fd) != 0) {
      if ((*(byte *)(param_1 + 0x6fd) & 0x80) != 0) {
        *(float *)(param_1 + 0x720) = FLOAT_80437448;
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
      }
      iVar1 = (*(code *)(&PTR_FUN_802d3580)[*(char *)(param_1 + 0x591)])(param_1);
      if (iVar1 == 0) {
        if ((*(char *)(param_1 + 0x6fe) < 9) && (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) != 0)) {
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
        }
        if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
          zz_00f036c_(param_1,0);
          zz_00f036c_(param_1,0x80);
          zz_00f036c_(param_1,0x100);
        }
        zz_006a750_(param_1,0x2e);
        zz_006a6fc_(param_1,0x2e);
        if ((uVar2 & 0x5000000) == 0x5000000) {
          if (*(char *)(param_1 + 0x702) < '\x03') {
            *(undefined1 *)(param_1 + 0x702) = 4;
          }
          *(undefined1 *)(param_1 + 0x6fe) = 9;
        }
        if ((*(byte *)(param_1 + 0x1da) & 8) != 0) {
          *(undefined1 *)(param_1 + 0x6fe) = 0x14;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x22000000;
        }
        if ((*(byte *)(param_1 + 0x1da) & 0x10) != 0) {
          *(undefined1 *)(param_1 + 0x6fe) = 0x12;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfdffffff;
        }
        if ((*(short *)(param_1 + 0x272) == 0) && ((*(byte *)(param_1 + 0x1da) & 2) != 0)) {
          if (*(char *)(*(int *)(param_1 + 0x4b0) + 3) == '\x01') {
            if ((uVar2 & 0x40) == 0) {
              *(undefined1 *)(param_1 + 0x6fe) = 0xd;
            }
            else {
              *(undefined1 *)(param_1 + 0x6fe) = 0xe;
            }
          }
        }
        if (*(char *)(param_1 + 0x599) != '\0') {
          *(undefined1 *)(param_1 + 0x6fe) = 0x15;
        }
        *(undefined2 *)(param_1 + 0x6b6) = 300;
        *(undefined2 *)(param_1 + 0x6b4) = 0x1e;
        zz_005efc4_(param_1,*(char *)(param_1 + 0x1da));
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x1000000;
        if ((*(byte *)(param_1 + 0x3e5) & PTR_DAT_80433934[0xd2]) == 0) {
          zz_005c694_(param_1);
        }
      }
    }
  }
  return;
}



// ==== 8005c4a4  FUN_8005c4a4 ====

undefined4 FUN_8005c4a4(int param_1)

{
  zz_005f00c_(param_1);
  return 0;
}



// ==== 8005c4c8  FUN_8005c4c8 ====

undefined4 FUN_8005c4c8(int param_1)

{
  zz_005f00c_(param_1);
  if (((int)*(char *)(param_1 + 0x6fe) - 1U & 4) != 0) {
    if (((*(byte *)(param_1 + 0x6fd) & 2) == 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
      *(undefined1 *)(param_1 + 0x6fe) = 0x11;
    }
  }
  return 0;
}



// ==== 8005c530  FUN_8005c530 ====

undefined4 FUN_8005c530(int param_1)

{
  uint uVar1;
  
  zz_005f00c_(param_1);
  uVar1 = (int)*(char *)(param_1 + 0x6fe) - 1;
  if ((uVar1 & 4) != 0) {
    if ((*(byte *)(param_1 + 0x6fd) & 2) == 0) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
        if ((uVar1 & 1) == 0) {
          *(undefined1 *)(param_1 + 0x6fe) = 0xf;
        }
        else {
          *(undefined1 *)(param_1 + 0x6fe) = 0x10;
        }
      }
    }
  }
  return 0;
}



// ==== 8005c5ac  FUN_8005c5ac ====

undefined4 FUN_8005c5ac(int param_1)

{
  zz_005f00c_(param_1);
  return 0;
}



// ==== 8005c5d0  FUN_8005c5d0 ====

undefined4 FUN_8005c5d0(int param_1)

{
  if (((*(byte *)(param_1 + 0x1da) & 0x10) == 0) && (*(char *)(param_1 + 0x599) == '\0')) {
    if ((*(byte *)(param_1 + 0x6fd) & 0x80) != 0) {
      *(float *)(param_1 + 0x720) = FLOAT_80437448;
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
    }
    zz_00ea2c8_(param_1,4);
    return 1;
  }
  return 0;
}



// ==== 8005c638  FUN_8005c638 ====

undefined4 FUN_8005c638(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(param_1 + 0x1da) & 0x10) == 0) {
    if ((*(byte *)(param_1 + 0x6fd) & 0x80) != 0) {
      *(float *)(param_1 + 0x720) = FLOAT_80437448;
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
    }
    zz_00ea2c8_(param_1,4);
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8005c694  zz_005c694_ ====

void zz_005c694_(int param_1)

{
  undefined2 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) {
    if (*(char *)(param_1 + 0x540) == '\0') {
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_005c15c_(param_1);
      if ((*(byte *)(param_1 + 0x1da) & 0x10) == 0) {
        zz_00ea2c8_(param_1,4);
      }
    }
  }
  (*(code *)(&PTR_FUN_802d35a4)[*(char *)(param_1 + 0x6fe)])(param_1);
  if (*(short *)(param_1 + 0x6b4) != 0) {
    *(short *)(param_1 + 0x6b4) = *(short *)(param_1 + 0x6b4) + -1;
  }
  if (((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0)) {
    if (0 < *(short *)(param_1 + 0x6b6)) {
      *(short *)(param_1 + 0x6b6) = *(short *)(param_1 + 0x6b6) + -1;
      fVar4 = FLOAT_80437448;
      fVar3 = FLOAT_80437444;
      if (0 < *(short *)(param_1 + 0x6b6)) {
        if (*(float *)(param_1 + 0x720) <= FLOAT_80437444) goto LAB_8005c7c4;
        if ((0x3c < *(short *)(param_1 + 0x6b6)) || (*(char *)(param_1 + 0x730) == '\0'))
        goto LAB_8005c7c4;
      }
      *(float *)(param_1 + 0x720) = FLOAT_80437444;
      fVar2 = FLOAT_80437440;
      *(undefined2 *)(param_1 + 0x272) = 0;
      *(float *)(param_1 + 0x720) = fVar4;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xff0000;
      *(float *)(param_1 + 0x1dcc) = fVar2;
      *(float *)(param_1 + 0x1d9c) = fVar3;
      uVar1 = *(undefined2 *)(*(int *)(param_1 + 0x4ac) + 4);
      *(undefined2 *)(param_1 + 0x738) = uVar1;
      *(undefined2 *)(param_1 + 0x736) = uVar1;
      *(undefined1 *)(param_1 + 0x747) = 0;
      *(undefined2 *)(param_1 + 0x272) = 0;
      zz_006a5a4_(param_1);
    }
  }
LAB_8005c7c4:
  if (FLOAT_80437444 < *(float *)(param_1 + 0x720)) {
    *(float *)(param_1 + 0x720) = FLOAT_80437448;
  }
  return;
}



// ==== 8005c7f0  FUN_8005c7f0 ====

void FUN_8005c7f0(int param_1)

{
  zz_006a474_(param_1);
  return;
}



// ==== 8005c810  FUN_8005c810 ====

void FUN_8005c810(int param_1)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  char cVar4;
  
  cVar4 = *(char *)(param_1 + 0x544);
  if (cVar4 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005c92c;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar4 < '\x01') && (-1 < cVar4)) {
    *(char *)(param_1 + 0x544) = cVar4 + '\x01';
    uVar1 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar3 = zz_0046510_(uVar1,2);
    cVar4 = (char)iVar3;
    if ((*(byte *)(param_1 + 0x6fd) & 0x40) != 0) {
      cVar4 = '\x04';
    }
    zz_005f188_(param_1,-0x80,cVar4);
    if (cVar4 == 4) {
      sVar2 = *(short *)(param_1 + 0x72);
    }
    else {
      sVar2 = (*(short *)(param_1 + 0x72) + uVar1) - (short)((int)cVar4 << 0xe);
    }
    if (*(char *)(param_1 + 0x1d0f) != '\x01') {
      *(short *)(param_1 + 0x72) = sVar2;
    }
    *(short *)(param_1 + 0x5ae) = sVar2;
    zz_005ec20_(param_1);
    goto LAB_8005c92c;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) {
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_006a474_(param_1);
    return;
  }
LAB_8005c92c:
  zz_005ecb0_(param_1);
  zz_005ee0c_(param_1);
  return;
}



// ==== 8005c95c  FUN_8005c95c ====

void FUN_8005c95c(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005ca54;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    uVar2 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar3 = zz_0046510_(uVar2,2);
    zz_005f188_(param_1,-0x80,(char)iVar3 + '\x05');
    sVar4 = *(short *)(param_1 + 0x72) + uVar2 + (char)iVar3 * -0x4000;
    if (*(char *)(param_1 + 0x1d0f) != '\x01') {
      *(short *)(param_1 + 0x72) = sVar4;
    }
    *(short *)(param_1 + 0x5ae) = sVar4;
    zz_005ec20_(param_1);
    goto LAB_8005ca54;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) {
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_006a474_(param_1);
    return;
  }
LAB_8005ca54:
  zz_005ecb0_(param_1);
  zz_005ee0c_(param_1);
  return;
}



// ==== 8005ca80  FUN_8005ca80 ====

void FUN_8005ca80(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  short sVar4;
  byte bVar5;
  float local_28 [7];
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005cbd4;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    uVar2 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar3 = zz_0046510_(uVar2,1);
    bVar5 = -((char)(byte)iVar3 >> 7) - (2 < (byte)iVar3) & 2;
    zz_004516c_((float *)(param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30 + 0x8d4),
                (float *)(param_1 + 0x2a0),local_28);
    if (local_28[0] < FLOAT_80437444) {
      bVar5 = bVar5 + 1;
    }
    zz_005f188_(param_1,-0x80,bVar5 + 9);
    sVar4 = (*(short *)(param_1 + 0x72) + uVar2) - (short)(((int)(char)bVar5 >> 1) << 0xf);
    if (*(char *)(param_1 + 0x1d0f) != '\x01') {
      *(short *)(param_1 + 0x72) = sVar4;
    }
    *(short *)(param_1 + 0x5ae) = sVar4;
    zz_005ec20_(param_1);
    goto LAB_8005cbd4;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) {
    *(undefined2 *)(param_1 + 0x272) = 0;
    zz_006a474_(param_1);
    return;
  }
LAB_8005cbd4:
  zz_005ecb0_(param_1);
  zz_005ee0c_(param_1);
  return;
}



// ==== 8005cc00  zz_005cc00_ ====

void zz_005cc00_(int param_1)

{
  float fVar1;
  ushort uVar2;
  char cVar4;
  short sVar3;
  int iVar5;
  char cVar6;
  
  cVar6 = *(char *)(param_1 + 0x544);
  if (cVar6 == '\x01') {
    zz_0066f1c_(param_1);
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_004cd24_(param_1,0xf);
    iVar5 = zz_00677b0_(param_1);
    fVar1 = FLOAT_80437444;
    if (iVar5 == 0) goto LAB_8005cdf0;
    if (*(short *)(param_1 + 0x6b4) != 0) {
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_8043744c;
      goto LAB_8005cdf0;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  else if ((cVar6 < '\x01') && (-1 < cVar6)) {
    *(char *)(param_1 + 0x544) = cVar6 + '\x01';
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    FUN_8005ed38(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
    uVar2 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar5 = zz_0046510_(uVar2,2);
    cVar6 = (char)iVar5;
    if ((*(char *)(param_1 + 0x6fe) == '\x05') && ((*(byte *)(param_1 + 0x6fd) & 0x40) != 0)) {
      cVar6 = '\x04';
    }
    cVar4 = cVar6 + '\x05';
    if (*(char *)(param_1 + 0x6fe) == '\x05') {
      cVar4 = cVar6;
    }
    zz_005f188_(param_1,-0x7f,cVar4);
    if (cVar6 == 4) {
      sVar3 = *(short *)(param_1 + 0x72);
    }
    else {
      sVar3 = (*(short *)(param_1 + 0x72) + uVar2) - (short)((int)cVar6 << 0xe);
    }
    if (*(char *)(param_1 + 0x1cf0) != '\x01') {
      *(short *)(param_1 + 0x72) = sVar3;
    }
    cVar4 = *(char *)(param_1 + 0x591);
    if (((cVar4 == '\x04') || ((byte)(cVar4 - 5U) < 2)) || (cVar4 == '\x02')) {
      *(undefined2 *)(param_1 + 0x5aa) = 0;
    }
    else {
      *(undefined2 *)(param_1 + 0x5aa) = *(undefined2 *)(cVar6 * 2 + -0x7fd2ca04);
    }
    *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
    zz_0066ec0_(param_1,(int)*(short *)(param_1 + 0x1b38));
    zz_0066f1c_(param_1);
    goto LAB_8005cdf0;
  }
  zz_005ec04_(param_1,10);
LAB_8005cdf0:
  zz_005f114_(param_1);
  return;
}



// ==== 8005ce14  FUN_8005ce14 ====

void FUN_8005ce14(int param_1)

{
  char cVar1;
  float fVar2;
  ushort uVar3;
  int iVar4;
  byte bVar5;
  float local_38 [4];
  undefined8 local_28;
  undefined4 local_20;
  uint uStack_1c;
  undefined8 local_18;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d10) != '\0') {
      if (*(char *)(param_1 + 0x1d10) == '\x01') {
        iVar4 = FUN_800452a0((double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
        uStack_1c = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
        local_28 = (double)CONCAT44(0x43300000,(int)(short)iVar4 ^ 0x80000000);
        local_20 = 0x43300000;
        iVar4 = (int)(FLOAT_80437450 *
                      (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80437458) +
                     FLOAT_80437454 * (float)(local_28 - DOUBLE_80437458));
        local_18 = (double)(longlong)iVar4;
        *(short *)(param_1 + 0x1c) = (short)iVar4;
        *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x1c) + -0x4000;
        *(undefined2 *)(param_1 + 0x18dc) = 0;
      }
      else {
        iVar4 = FUN_800452a0(-(double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44))
        ;
        uStack_1c = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
        local_18 = (double)CONCAT44(0x43300000,(int)(short)iVar4 ^ 0x80000000);
        local_20 = 0x43300000;
        iVar4 = (int)(FLOAT_80437450 *
                      (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80437458) +
                     FLOAT_80437454 * (float)(local_18 - DOUBLE_80437458));
        local_28 = (double)(longlong)iVar4;
        *(short *)(param_1 + 0x1c) = (short)iVar4;
        *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x1c) + 0x4000;
        *(undefined2 *)(param_1 + 0x18dc) = 0;
      }
    }
    iVar4 = zz_00677b0_(param_1);
    fVar2 = FLOAT_80437444;
    if (iVar4 == 0) {
      return;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x50) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    FUN_8005ed38(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
    uVar3 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar4 = zz_0046510_(uVar3,1);
    bVar5 = -((char)(byte)iVar4 >> 7) - (2 < (byte)iVar4) & 2;
    zz_004516c_((float *)(param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30 + 0x8d4),
                (float *)(param_1 + 0x2a0),local_38);
    if (local_38[0] < FLOAT_80437444) {
      bVar5 = bVar5 + 1;
    }
    *(ushort *)(param_1 + 0x72) =
         *(short *)(param_1 + 0x72) + (uVar3 - (short)(((int)(char)bVar5 >> 1) << 0xf));
    zz_005f188_(param_1,-0x7f,bVar5 + 9);
    return;
  }
  zz_005ec04_(param_1,10);
  return;
}



// ==== 8005d0a8  FUN_8005d0a8 ====

void FUN_8005d0a8(int param_1)

{
  float fVar1;
  ushort uVar2;
  int iVar3;
  char cVar4;
  
  cVar4 = *(char *)(param_1 + 0x544);
  if (cVar4 == '\x01') {
    zz_0066f1c_(param_1);
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_004cd24_(param_1,0xf);
    iVar3 = zz_00677b0_(param_1);
    fVar1 = FLOAT_80437444;
    if (iVar3 == 0) goto LAB_8005d204;
    if (*(short *)(param_1 + 0x6b4) != 0) {
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_8043744c;
      goto LAB_8005d204;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  else if ((cVar4 < '\x01') && (-1 < cVar4)) {
    *(char *)(param_1 + 0x544) = cVar4 + '\x01';
    *(undefined1 *)(param_1 + 0x87) = 1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    FUN_8005ed38(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
    uVar2 = (*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72);
    iVar3 = zz_0046510_(uVar2,2);
    cVar4 = (char)iVar3;
    *(ushort *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + (uVar2 - (short)((int)cVar4 << 0xe));
    *(undefined2 *)(param_1 + 0x5aa) = *(undefined2 *)(&DAT_80433818 + cVar4 * 2);
    *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
    zz_005f188_(param_1,-0x7f,cVar4 + '\r');
    zz_0066ec0_(param_1,(int)*(short *)(param_1 + 0x1b38));
    zz_0066f1c_(param_1);
    goto LAB_8005d204;
  }
  zz_005ec04_(param_1,10);
LAB_8005d204:
  zz_005f114_(param_1);
  return;
}



// ==== 8005d224  FUN_8005d224 ====

void FUN_8005d224(int param_1)

{
  if (*(char *)(param_1 + 0x3f3) == '\0') {
    *(float *)(param_1 + 0x720) = FLOAT_80437448;
  }
  zz_005cc00_(param_1);
  return;
}



// ==== 8005d258  FUN_8005d258 ====

void FUN_8005d258(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar2 = FLOAT_80437444;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    dVar4 = (double)FLOAT_80437464;
    *(float *)(param_1 + 0x50) = FLOAT_80437444;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_004beb8_(dVar4,param_1,0xf,0x82,(int)*(char *)(param_1 + 0x1d0f),0xffffffff,0xffffffff);
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    goto LAB_8005d44c;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      fVar3 = FLOAT_80437460;
      fVar2 = FLOAT_80437444;
      *(float *)(param_1 + 0x1d9c) = FLOAT_80437444;
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(undefined2 *)(param_1 + 0x18dc) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfdffffbf;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x4000000;
      *(undefined1 *)(param_1 + 0x87) = 0;
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(undefined4 *)(param_1 + 0x5ec) = *(undefined4 *)(param_1 + 0x30);
      dVar4 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
      *(float *)(param_1 + 0x24) = (float)dVar4;
      *(float *)(param_1 + 0x30) = (float)dVar4;
      cVar1 = *(char *)(param_1 + 0x591);
      if ((((cVar1 == '\x04') || (cVar1 == '\x05')) || (cVar1 == '\x06')) &&
         (*(char *)(param_1 + 0x1cef) == '\x01')) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x8000;
      }
      zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x82,*(char *)(param_1 + 0x1d0f) + 2,0xffffffff
                  ,0xffffffff);
      *(float *)(param_1 + 0x6d0) = FLOAT_80437444;
      zz_00b2190_(param_1,2);
      zz_00f0854_(param_1);
      goto LAB_8005d44c;
    }
    if (-1 < cVar1) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437468;
      zz_004cd24_(param_1,0xf);
      if (*(char *)(param_1 + 0x1d0e) != '\0') {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      }
      goto LAB_8005d44c;
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005d44c;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  zz_005ec04_(param_1,0xb);
LAB_8005d44c:
  if ((*(uint *)(param_1 + 0x5b4) & 0xf0700) != 0) {
    zz_005ec04_(param_1,0xb);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_005ee0c_(param_1);
  return;
}



// ==== 8005d494  FUN_8005d494 ====

void FUN_8005d494(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  *(float *)(param_1 + 0x720) = FLOAT_80437448;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x544) = 3;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    zz_00ea2c8_(param_1,7);
    if (*(char *)(param_1 + 0x1cf0) == '\x01') {
      zz_00670dc_(param_1,*(short *)(param_1 + 0x72) + *(char *)(param_1 + 0x57c) * 0x4000);
    }
    else if (*(char *)(param_1 + 0x1cf0) == '\x02') {
      zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    }
    if ((*(byte *)(param_1 + 0x57c) & 1) == 0) {
      zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x82,*(char *)(param_1 + 0x1d0f) + 4,0xffffffff
                  ,0xffffffff);
    }
    else {
      if (*(char *)(param_1 + 0x1cef) != *(char *)(param_1 + 0x1d0f)) {
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x8000;
      }
      zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x82,*(char *)(param_1 + 0x1cef) + 4,0xffffffff
                  ,0);
    }
    goto LAB_8005d9b8;
  }
  if ('\x01' < cVar1) {
    if (cVar1 < '\x04') {
      zz_004cd24_(param_1,0xf);
      if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005d9b8;
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
LAB_8005d990:
    *(undefined2 *)(param_1 + 0x272) = 0;
    if (*(char *)(param_1 + 0x3f3) != '\0') {
      *(float *)(param_1 + 0x720) = FLOAT_80437444;
    }
    zz_006a474_(param_1);
    return;
  }
  if (cVar1 == '\0') {
    if (*(char *)(param_1 + 0x591) == '\x06') {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x8000;
    }
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xf9ffffff;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x8000000;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    iVar3 = zz_0066ac0_(param_1,0);
    if (iVar3 == 0) {
      *(undefined1 *)(param_1 + 0x544) = 3;
      zz_00ea2c8_(param_1,7);
      dVar4 = (double)FLOAT_80437464;
      *(float *)(param_1 + 0x44) = FLOAT_80437444;
      zz_004beb8_(dVar4,param_1,0xf,0x82,*(char *)(param_1 + 0x1d0f) + 4,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined2 *)(param_1 + 0x550) = 0;
      *(undefined2 *)(param_1 + 0x552) = 0;
      iVar3 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),2);
      iVar3 = *(char *)(param_1 + 0x1d0f) * 4 + iVar3;
      zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x82,iVar3 + 8,0xffffffff,0xffffffff);
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_802d3608 + iVar3 * 4);
      *(byte *)(param_1 + 0x57c) = (byte)iVar3 & 3;
      fVar2 = FLOAT_8043746c;
      cVar1 = *(char *)(param_1 + 0x591);
      if (((cVar1 == '\x04') || (cVar1 == '\x05')) || (cVar1 == '\x06')) {
        if (cVar1 == '\x05') {
          *(short *)(param_1 + 0x5ac) =
               *(short *)(param_1 + 0x5b0) + *(short *)(param_1 + 0x734) + -0x8000;
          *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5ac) - *(short *)(param_1 + 0x72);
          *(float *)(param_1 + 0x44) = fVar2;
        }
        else {
          if (cVar1 == '\x04') {
            *(undefined2 *)(param_1 + 0x5aa) = *(undefined2 *)(&DAT_80433820 + iVar3 * 2);
          }
          else {
            *(undefined2 *)(param_1 + 0x5aa) = *(undefined2 *)(&DAT_80433828 + iVar3 * 2);
          }
          *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
        }
        *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
        zz_00ea2c8_(param_1,7);
      }
      else if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
        *(short *)(param_1 + 0x5ae) =
             *(short *)(param_1 + 0x5b0) + *(short *)(param_1 + 0x734) + -0x8000;
        *(undefined2 *)(param_1 + 0x5aa) = 0;
        *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * *(float *)(param_1 + 0x1dd4);
        zz_00ea2c8_(param_1,7);
      }
      else {
        *(undefined2 *)(param_1 + 0x5aa) = 0;
        *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
      }
      zz_0066ec0_(param_1,0x10);
      zz_0066f1c_(param_1);
    }
    goto LAB_8005d9b8;
  }
  if (cVar1 < '\0') goto LAB_8005d990;
  if ((*(uint *)(param_1 + 0x5b4) & 0x700) != 0) {
    *(undefined2 *)(param_1 + 0x552) = 1;
  }
  zz_0066f1c_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf0) == '\x01') {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x72) + *(char *)(param_1 + 0x57c) * 0x4000);
  }
  else if (*(char *)(param_1 + 0x1cf0) == '\x02') {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  cVar1 = *(char *)(param_1 + 0x591);
  if ((((cVar1 == '\x04') || (cVar1 == '\x05')) || (cVar1 == '\x06')) &&
     (*(char *)(param_1 + 0x1d10) != '\x01')) goto LAB_8005d9b8;
  if ((cVar1 == '\x01') || (cVar1 == '\x02')) {
    if ((*(short *)(param_1 + 0x552) != 0) || (iVar3 = zz_0066ac0_(param_1,0), iVar3 == 0)) {
      *(undefined1 *)(param_1 + 0x544) = 3;
      goto LAB_8005d9b8;
    }
    if (*(char *)(param_1 + 0x1d10) != '\x01') goto LAB_8005d9b8;
  }
  else if (*(char *)(param_1 + 0x1d10) == '\x01') {
    *(short *)(param_1 + 0x550) = *(short *)(param_1 + 0x550) + 1;
  }
  *(undefined1 *)(param_1 + 0x1d10) = 0;
  if (*(char *)(param_1 + 0x1d0f) == -1) {
    *(undefined1 *)(param_1 + 0x544) = 4;
  }
  else if (((4 < *(short *)(param_1 + 0x550)) || (*(short *)(param_1 + 0x552) != 0)) ||
          (iVar3 = zz_0066ac0_(param_1,0), iVar3 == 0)) {
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
LAB_8005d9b8:
  zz_005ee0c_(param_1);
  return;
}



// ==== 8005d9d8  FUN_8005d9d8 ====

void FUN_8005d9d8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  double dVar6;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    if (*(char *)(param_1 + 0x545) == '\0') {
      *(undefined1 *)(param_1 + 0x545) = 1;
    }
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437474;
    iVar4 = zz_00677b0_(param_1);
    fVar2 = FLOAT_80437444;
    if (iVar4 == 0) goto LAB_8005db28;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x50) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x87) = 1;
    fVar3 = FLOAT_80437444;
    fVar2 = FLOAT_80437440;
    uVar5 = *(uint *)(param_1 + 0x5e0);
    if ((uVar5 & 0x18000000) != 0) {
      *(uint *)(param_1 + 0x5e0) = uVar5 & 0xff0000;
      fVar3 = FLOAT_80437444;
      *(float *)(param_1 + 0x1dcc) = fVar2;
      *(float *)(param_1 + 0x1d9c) = fVar3;
      *(undefined2 *)(param_1 + 0x272) = 0;
      zz_006a5a4_(param_1);
      return;
    }
    *(uint *)(param_1 + 0x5e0) = uVar5 & 0xf3ffffff;
    fVar2 = FLOAT_80437470;
    dVar6 = (double)FLOAT_80437440;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    *(undefined2 *)(param_1 + 0x6b4) = 0x1e;
    FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
    zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x81,*(char *)(param_1 + 0x1cef) + 0x11,
                0xffffffff,0xffffffff);
    goto LAB_8005db28;
  }
  zz_005ec04_(param_1,10);
LAB_8005db28:
  zz_005f114_(param_1);
  return;
}



// ==== 8005db44  FUN_8005db44 ====

void FUN_8005db44(int param_1)

{
  char cVar1;
  double dVar2;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005dc00;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    dVar2 = (double)FLOAT_80437464;
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x10000000;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x284) + -0x8000;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    zz_004beb8_(dVar2,param_1,0xf,0x80,0xd,0xffffffff,0xffffffff);
    zz_005ec20_(param_1);
LAB_8005dc00:
    zz_005ecb0_(param_1);
    zz_005ee0c_(param_1);
    return;
  }
  *(undefined2 *)(param_1 + 0x272) = 0;
  zz_006a474_(param_1);
  return;
}



// ==== 8005dc24  FUN_8005dc24 ====

void FUN_8005dc24(int param_1)

{
  char cVar1;
  double dVar2;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005dce4;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    dVar2 = (double)FLOAT_80437464;
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x10000000;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x284) + -0x8000;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
    zz_004beb8_(dVar2,param_1,0xf,0x80,0xe,0xffffffff,0xffffffff);
    zz_005ec20_(param_1);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
LAB_8005dce4:
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    return;
  }
  zz_006a5a4_(param_1);
  return;
}



// ==== 8005dd10  FUN_8005dd10 ====

void FUN_8005dd10(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043747c;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_0066f1c_(param_1);
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_004cd24_(param_1,0xf);
    zz_00677b0_(param_1);
    fVar2 = FLOAT_80437444;
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x568) <= fVar2) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
    }
  }
  else {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        *(undefined1 *)(param_1 + 0x87) = 1;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
        FUN_8005ed38(param_1);
        *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
        iVar3 = zz_0046510_((*(short *)(param_1 + 0x284) + -0x8000) - *(short *)(param_1 + 0x72),2);
        iVar3 = (int)(char)iVar3;
        if (*(char *)(param_1 + 0x6fe) == '\x0f') {
          zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x81,iVar3 + 0x13,0xffffffff,0xffffffff);
        }
        else {
          zz_004beb8_((double)FLOAT_80437464,param_1,0xf,0x81,iVar3 + 0x17,0xffffffff,0xffffffff);
        }
        *(undefined2 *)(param_1 + 0x5aa) = *(undefined2 *)(&DAT_802d3628 + iVar3 * 2);
        *(short *)(param_1 + 0x5ac) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x5aa);
        zz_0066ec0_(param_1,(int)*(short *)(param_1 + 0x1b38));
        zz_0066f1c_(param_1);
        *(float *)(param_1 + 0x568) =
             FLOAT_80437478 +
             (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1b38) ^ 0x80000000) -
                    DOUBLE_80437458);
        return;
      }
    }
    else if (cVar1 < '\x03') {
      dVar4 = (double)FLOAT_80437440;
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043747c;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
      FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
      zz_004cd24_(param_1,0xf);
      zz_00677b0_(param_1);
      if (*(char *)(param_1 + 0x1d0e) == '\0') {
        return;
      }
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8005df2c  FUN_8005df2c ====

void FUN_8005df2c(int param_1)

{
  char cVar1;
  double dVar2;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1d0e) == '\0') goto LAB_8005dfd0;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    dVar2 = (double)FLOAT_80437464;
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
    zz_004beb8_(dVar2,param_1,0xf,0x80,0xd,0xffffffff,0xffffffff);
    zz_005ec20_(param_1);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
LAB_8005dfd0:
    FUN_80067310((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    return;
  }
  zz_006a5a4_(param_1);
  return;
}



// ==== 8005dffc  FUN_8005dffc ====

void FUN_8005dffc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double local_30;
  
  fVar3 = FLOAT_80437480;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
LAB_8005e0bc:
    fVar2 = FLOAT_8043748c;
    fVar3 = FLOAT_80437488;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    fVar4 = FLOAT_80437490;
    *(float *)(param_1 + 0x568) = fVar3;
    fVar3 = FLOAT_80437460;
    *(float *)(param_1 + 0x56c) = fVar2;
    dVar5 = DOUBLE_80437458;
    *(float *)(param_1 + 0x570) = fVar4;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined2 *)(param_1 + 0x550) = 0x2f;
    *(short *)(param_1 + 0x7e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x550) ^ 0x80000000) -
                             dVar5) * *(float *)(param_1 + 0x56c));
  }
  else {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        fVar2 = FLOAT_80437444;
        *(float *)(param_1 + 0x568) = fVar3;
        dVar5 = (double)FLOAT_80437464;
        *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
        *(float *)(param_1 + 0x50) = fVar2;
        *(float *)(param_1 + 0x48) = fVar2;
        *(float *)(param_1 + 0x4c) = fVar2;
        *(float *)(param_1 + 0x44) = fVar2;
        *(undefined2 *)(param_1 + 0x80) = 0;
        *(undefined2 *)(param_1 + 0x7e) = 0;
        *(undefined2 *)(param_1 + 0x7c) = 0;
        zz_004beb8_(dVar5,param_1,0xf,0x80,0xf,0xffffffff,0xffffffff);
        FUN_800061a8(param_1,2);
        zz_00f061c_((double)FLOAT_80437484,param_1,0xdd);
        zz_00107a0_(param_1,0x15);
        goto LAB_8005e0bc;
      }
    }
    else if (cVar1 < '\x03') {
      zz_004cd24_(param_1,0xf);
      fVar3 = FLOAT_80437444;
      if (FLOAT_80437444 < *(float *)(param_1 + 0x56c)) {
        *(float *)(param_1 + 0x56c) = *(float *)(param_1 + 0x56c) - *(float *)(param_1 + 0x1dc8);
        dVar5 = DOUBLE_80437458;
        if (*(float *)(param_1 + 0x56c) <= fVar3) {
          *(undefined2 *)(param_1 + 0x18dc) = 0;
          *(undefined2 *)(param_1 + 0x7e) = 0;
        }
        else {
          local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x7e)) ^ 0x80000000);
          *(short *)(param_1 + 0x18dc) =
               (short)(int)-((float)(local_30 - DOUBLE_80437458) * *(float *)(param_1 + 0x1dc8) -
                            (float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000)
                                   - DOUBLE_80437458));
          *(short *)(param_1 + 0x7e) =
               (short)(int)-((float)((double)CONCAT44(0x43300000,
                                                      (int)*(short *)(param_1 + 0x550) ^ 0x80000000)
                                    - dVar5) * *(float *)(param_1 + 0x1dc8) -
                            (float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                                   dVar5));
        }
      }
      fVar3 = FLOAT_80437444;
      if ((FLOAT_80437444 < *(float *)(param_1 + 0x570)) &&
         (*(float *)(param_1 + 0x570) = *(float *)(param_1 + 0x570) - FLOAT_80437440,
         *(float *)(param_1 + 0x570) <= fVar3)) {
        *(float *)(param_1 + 0x570) = fVar3;
        zz_00ea2c8_(param_1,0xe);
      }
      FUN_80067310((double)FLOAT_80437444,param_1,*(short *)(param_1 + 0x5ae));
      fVar3 = FLOAT_80437444;
      *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
      if (*(float *)(param_1 + 0x568) <= fVar3) {
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        *(float *)(param_1 + 0x48) = fVar3;
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
        *(uint *)(param_1 + 0x8c4) = *(uint *)(param_1 + 0x8c4) & 0xfffffffd;
      }
      goto LAB_8005e300;
    }
    zz_004cd24_(param_1,0xf);
    FUN_80067310((double)FLOAT_80437494,param_1,*(short *)(param_1 + 0x5ae));
    if (*(char *)(param_1 + 0x1d0e) != '\0') {
      *(undefined2 *)(param_1 + 0x272) = 0;
      if (*(char *)(param_1 + 0x591) != '\a') {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
  }
LAB_8005e300:
  zz_00677b0_(param_1);
  return;
}



// ==== 8005e31c  FUN_8005e31c ====

void FUN_8005e31c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  float fVar5;
  int iVar6;
  short sVar7;
  double dVar8;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x544) = 3;
    iVar6 = zz_0066ac0_(param_1,0);
    if (iVar6 == 0) {
      *(float *)(param_1 + 0x44) = FLOAT_80437444;
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(*(int *)(param_1 + 0x4ac) + 0x50) * FLOAT_80437460;
    }
    dVar4 = DOUBLE_80437458;
    *(float *)(param_1 + 0x4c) = FLOAT_80437444;
    dVar8 = (double)FLOAT_80437464;
    *(ushort *)(param_1 + 0x550) = *(byte *)(*(int *)(param_1 + 0x4ac) + 0x3f) + 1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x68);
    *(float *)(param_1 + 0x48) =
         -(*(float *)(param_1 + 0x50) *
           (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x550) ^ 0x80000000) -
                  dVar4) - *(float *)(*(int *)(param_1 + 0x4ac) + 0x4c));
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    zz_004beb8_(dVar8,param_1,0xf,0,0xf,0xffffffff,0xffffffff);
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) == '\0') {
      zz_00f036c_(param_1,0x1e);
    }
    else {
      *(undefined1 *)(param_1 + 0x709) = 1;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      fVar3 = FLOAT_80437444;
      *(undefined1 *)(param_1 + 0x87) = 1;
      fVar5 = FLOAT_80437498;
      *(undefined4 *)(param_1 + 0x754) = 0;
      fVar2 = FLOAT_80437440;
      *(float *)(param_1 + 0x69c) = fVar3;
      dVar4 = DOUBLE_804374a0;
      dVar8 = (double)FLOAT_80437464;
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar5;
      *(float *)(param_1 + 0x4c) = fVar3;
      *(float *)(param_1 + 0x48) = fVar3;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xff0000;
      *(float *)(param_1 + 0x1dcc) = fVar2;
      *(float *)(param_1 + 0x1d9c) = fVar3;
      *(undefined2 *)(param_1 + 0x272) = 0;
      *(undefined1 *)(param_1 + 0x71b) = 0;
      *(undefined2 *)(param_1 + 0x18de) = 0;
      *(undefined2 *)(param_1 + 0x18dc) = 0;
      *(undefined2 *)(param_1 + 0x18da) = 0;
      *(float *)(param_1 + 0x690) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x40)) -
                  dVar4);
      *(undefined1 *)(param_1 + 0x57d) = 0;
      zz_004beb8_(dVar8,param_1,0xf,0,0xe,0,0);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
        *(undefined1 *)(param_1 + 0x709) = 1;
      }
      zz_0092dcc_(param_1,0);
      FUN_800061a8(param_1,7);
    }
    else if ((-1 < cVar1) && (iVar6 = zz_004cd24_(param_1,0xf), iVar6 != 0)) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,0xf);
    sVar7 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar7;
    if (sVar7 < 1) {
      *(undefined1 *)(param_1 + 0x590) = 2;
      zz_006a750_(param_1,6);
    }
  }
  zz_0067458_((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8005e5a8  FUN_8005e5a8 ====

void FUN_8005e5a8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  uint uVar7;
  double dVar8;
  
  *(undefined2 *)(param_1 + 0x6b4) = 0x1e;
  *(undefined1 *)(param_1 + 0x7de) = 1;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    fVar3 = FLOAT_804374a8;
    fVar2 = FLOAT_80437478;
    if (-1 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    *(undefined2 *)(param_1 + 0x550) = 0xf0;
    *(undefined2 *)(param_1 + 0x552) = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      fVar2 = FLOAT_80437444;
      *(undefined2 *)(param_1 + 0x550) = 8;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x22000040;
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x284);
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      FUN_8005ed38(param_1);
      zz_01ee744_(param_1,0);
      return;
    }
    if ('\x02' < cVar1) {
      return;
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar6 = FUN_8005ef08(param_1);
    if (iVar6 != 0) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000040;
    }
  }
  else {
    FUN_80067524((double)FLOAT_80437440,param_1,*(short *)(param_1 + 0x5ae));
    iVar6 = zz_00677b0_(param_1);
    if (iVar6 != 0) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfdffffbf;
      *(undefined1 *)(param_1 + 0x87) = 0;
      zz_00b2190_(param_1,2);
      zz_00f0854_(param_1);
      fVar2 = FLOAT_80437444;
      *(float *)(param_1 + 0x48) = FLOAT_80437444;
      if (*(float *)(param_1 + 0x720) != fVar2) {
        *(undefined2 *)(param_1 + 0x550) = 0;
      }
    }
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_804374ac;
  iVar6 = zz_006de44_(param_1,0xf0f00);
  if ((iVar6 != 0) &&
     (*(short *)(param_1 + 0x550) = *(short *)(param_1 + 0x550) + -3,
     *(short *)(param_1 + 0x552) < 1)) {
    *(undefined2 *)(param_1 + 0x552) = 4;
    uVar7 = zz_00055fc_();
    sVar5 = (short)(uVar7 << 8);
    sVar4 = sVar5 - *(short *)(param_1 + 0x5ac);
    if ((sVar4 < 0x2000) && (-0x2000 < sVar4)) {
      sVar5 = *(short *)(param_1 + 0x5ac) + 0x7000;
    }
    *(short *)(param_1 + 0x5ac) = sVar5;
    dVar8 = zz_0045204_(*(short *)(param_1 + 0x5ac));
    *(float *)(param_1 + 0x1dbc) = (float)((double)FLOAT_804374b0 * dVar8);
    dVar8 = zz_0045238_(*(short *)(param_1 + 0x5ac));
    *(float *)(param_1 + 0x1dc4) = (float)((double)FLOAT_804374b0 * dVar8);
  }
  if (0 < *(short *)(param_1 + 0x552)) {
    *(short *)(param_1 + 0x552) = *(short *)(param_1 + 0x552) + -1;
  }
  sVar5 = *(short *)(param_1 + 0x550) + -1;
  *(short *)(param_1 + 0x550) = sVar5;
  fVar3 = FLOAT_80437448;
  fVar2 = FLOAT_80437444;
  if (sVar5 < 0) {
    *(uint *)(param_1 + 0x8c4) = *(uint *)(param_1 + 0x8c4) & 0xfffffff7;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xdfffffff;
    *(float *)(param_1 + 0x1dbc) = fVar2;
    *(float *)(param_1 + 0x1dc4) = fVar2;
    *(float *)(param_1 + 0x720) = fVar3;
    *(undefined2 *)(param_1 + 0x6b6) = 300;
    *(undefined2 *)(param_1 + 0x6b4) = 0x1e;
    zz_005ec04_(param_1,5);
  }
  return;
}



// ==== 8005e868  FUN_8005e868 ====

void FUN_8005e868(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  double dVar9;
  
  fVar4 = FLOAT_804374bc;
  fVar3 = FLOAT_80437490;
  fVar1 = FLOAT_80437444;
  cVar2 = *(char *)(param_1 + 0x544);
  iVar8 = *(int *)(PTR_DAT_80433934 + 0xbc);
  if (cVar2 == '\x02') {
    sVar7 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar7;
    if (-1 < sVar7) {
      return;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(undefined2 *)(param_1 + 0x550) = 2;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar8 + 0x8d4),(float *)(*(char *)(iVar8 + 400) * 0xc + -0x7fd2c9cc),
               (float *)(param_1 + 0x20));
    zz_01e3838_(iVar8,*(undefined1 *)(iVar8 + 400));
    iVar6 = *(char *)(iVar8 + 400) + 1;
    cVar2 = (char)(iVar6 >> 0x1f);
    *(byte *)(iVar8 + 400) =
         (cVar2 * '\x04' | (byte)((uint)(iVar6 * 0x40000000 + (iVar6 >> 0x1f)) >> 0x1e)) - cVar2;
  }
  else {
    if (cVar2 < '\x02') {
      if (cVar2 == '\0') {
        *(undefined1 *)(param_1 + 0x544) = 1;
        fVar3 = FLOAT_80437490;
        *(float *)(param_1 + 0x50) = fVar1;
        *(float *)(param_1 + 0x48) = fVar1;
        *(float *)(param_1 + 0x4c) = fVar1;
        *(float *)(param_1 + 0x44) = fVar1;
        *(undefined2 *)(param_1 + 0x80) = 0;
        *(undefined2 *)(param_1 + 0x7e) = 0;
        *(undefined2 *)(param_1 + 0x7c) = 0;
        *(undefined2 *)(param_1 + 0x272) = 0x43;
        *(float *)(param_1 + 0x568) = fVar3;
        *(undefined1 *)(param_1 + 0x656) = 1;
        FUN_800061a8(param_1,0xc);
        zz_00f036c_(param_1,0xf2);
        return;
      }
      if (cVar2 < '\0') {
        return;
      }
      *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - FLOAT_80437440;
      dVar9 = zz_0045204_((short)(int)(fVar4 * (*(float *)(param_1 + 0x568) / fVar3)));
      fVar5 = FLOAT_804374c0;
      fVar4 = FLOAT_804374b0;
      fVar3 = FLOAT_80437444;
      fVar1 = (float)((double)FLOAT_804374b8 * dVar9 + (double)FLOAT_804374b4);
      *(float *)(param_1 + 0x60) = fVar1;
      *(float *)(param_1 + 0x58) = fVar1;
      *(float *)(param_1 + 0x5c) = -(fVar5 * *(float *)(param_1 + 0x58) - fVar4);
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0xb4);
      if (fVar3 < *(float *)(param_1 + 0x568)) {
        return;
      }
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined2 *)(param_1 + 0x550) = 2;
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
      *(undefined1 *)(param_1 + 0x7c9) = 3;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x1000;
      *(undefined1 *)(param_1 + 0x82) = 0;
      return;
    }
    if (cVar2 == '\x04') {
      *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - FLOAT_80437440;
      dVar9 = zz_0045204_((short)(int)-(fVar4 * (*(float *)(param_1 + 0x568) / fVar3) - fVar4));
      fVar4 = FLOAT_804374c4;
      fVar3 = FLOAT_80437490;
      fVar1 = FLOAT_80437444;
      *(float *)(param_1 + 0x58) = (float)((double)FLOAT_804374b8 * dVar9 + (double)FLOAT_804374b4);
      *(float *)(param_1 + 0x5c) = -(fVar4 * *(float *)(param_1 + 0x58) - fVar3);
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0xb4);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
      if (fVar1 < *(float *)(param_1 + 0x568)) {
        return;
      }
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined2 *)(param_1 + 0x272) = 0;
      if (*(char *)(param_1 + 0x3f3) == '\0') {
        *(float *)(param_1 + 0x720) = FLOAT_804374c8;
      }
      if (*(char *)(param_1 + 0x591) != '\a') {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
    if ('\x03' < cVar2) {
      return;
    }
  }
  sVar7 = *(short *)(param_1 + 0x550) + -1;
  *(short *)(param_1 + 0x550) = sVar7;
  fVar3 = FLOAT_804374b4;
  fVar1 = FLOAT_80437490;
  if (sVar7 < 0) {
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(undefined2 *)(param_1 + 0x272) = 0x43;
    *(undefined1 *)(param_1 + 0x7c9) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffefff;
    *(float *)(param_1 + 0x568) = fVar1;
    *(float *)(param_1 + 0x58) = fVar3 * *(float *)(param_1 + 0xb4);
    *(float *)(param_1 + 0x60) = fVar3 * *(float *)(param_1 + 0xb4);
    *(float *)(param_1 + 0x5c) = fVar1 * *(float *)(param_1 + 0xb4);
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    FUN_800061a8(param_1,0);
  }
  return;
}



// ==== 8005ec04  zz_005ec04_ ====

void zz_005ec04_(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x6fe) = param_2;
  *(undefined1 *)(param_1 + 0x547) = 0;
  *(undefined1 *)(param_1 + 0x546) = 0;
  *(undefined1 *)(param_1 + 0x545) = 0;
  *(undefined1 *)(param_1 + 0x544) = 0;
  return;
}



// ==== 8005ec20  zz_005ec20_ ====

void zz_005ec20_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  
  cVar5 = *(char *)(param_1 + 0x702);
  if (cVar5 < '\0') {
    cVar5 = -cVar5;
  }
  fVar1 = *(float *)(param_1 + 0x298) / *(float *)(param_1 + 0xc4);
  if ('\x0f' < cVar5) {
    cVar5 = '\x0f';
  }
  *(undefined1 *)(param_1 + 0x1d9b) = 0;
  fVar2 = FLOAT_80437440;
  *(undefined1 *)(param_1 + 0x1db2) = 1;
  fVar4 = FLOAT_80437490;
  fVar3 = FLOAT_80437444;
  *(float *)(param_1 + 0x44) = fVar1 * *(float *)(&DAT_802dd8a0 + cVar5 * 4);
  *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) / fVar4;
  *(float *)(param_1 + 0x1d9c) = fVar1 - fVar2;
  *(float *)(param_1 + 0x50) = fVar3;
  *(float *)(param_1 + 0x48) = fVar3;
  return;
}



// ==== 8005ecb0  zz_005ecb0_ ====

void zz_005ecb0_(int param_1)

{
  if ((*(char *)(param_1 + 0x702) != '\0') && (*(char *)(param_1 + 0x1d9b) == '\0')) {
    if (*(char *)(param_1 + 0x1d10) == '\x01') {
      zz_00670dc_(param_1,*(short *)(param_1 + 0x284));
    }
    else {
      if (FLOAT_80437444 < *(float *)(param_1 + 0x1dac)) {
        zz_00670dc_(param_1,*(short *)(param_1 + 0x284));
      }
      if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x1dac)) {
        *(undefined1 *)(param_1 + 0x1d9b) = 1;
      }
    }
  }
  return;
}



// ==== 8005ed38  FUN_8005ed38 ====

/* WARNING: Removing unreachable block (ram,0x8005edec) */
/* WARNING: Removing unreachable block (ram,0x8005ed48) */

void FUN_8005ed38(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  double dVar6;
  double dVar7;
  
  cVar1 = *(char *)(param_1 + 0x702);
  cVar5 = -cVar1;
  if (-1 < cVar1) {
    cVar5 = cVar1;
  }
  if ((*(byte *)(param_1 + 0x6fd) & 0x80) != 0) {
    cVar5 = cVar5 + '\x02';
  }
  if ('\x0f' < cVar5) {
    cVar5 = '\x0f';
  }
  sVar2 = *(short *)(param_1 + 0x282);
  *(float *)(param_1 + 0x1d9c) = FLOAT_80437444;
  dVar7 = (double)*(float *)(&DAT_802d3664 + cVar5 * 4);
  dVar6 = zz_0045238_(-sVar2);
  *(float *)(param_1 + 0x44) = (float)(dVar7 * dVar6);
  dVar6 = zz_0045204_(-sVar2);
  fVar4 = FLOAT_804374cc;
  fVar3 = FLOAT_80437470;
  *(float *)(param_1 + 0x48) = (float)(dVar7 * dVar6);
  *(float *)(param_1 + 0x4c) = fVar4;
  *(float *)(param_1 + 0x50) = fVar3;
  return;
}



// ==== 8005ee0c  zz_005ee0c_ ====

void zz_005ee0c_(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  iVar2 = FUN_8005ef08(param_1);
  if (iVar2 != 0) {
    dVar4 = (double)(*(float *)(param_1 + 0x28) - *(float *)(param_1 + 0x34));
    dVar3 = (double)(*(float *)(param_1 + 0x20) - *(float *)(param_1 + 0x2c));
    dVar6 = (double)(float)(dVar3 * dVar3 + (double)(float)(dVar4 * dVar4));
    if ((double)FLOAT_80437444 < dVar6) {
      dVar5 = 1.0 / SQRT(dVar6);
      dVar5 = DOUBLE_804374d0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_804374d8);
      dVar5 = DOUBLE_804374d0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_804374d8);
      dVar6 = (double)(float)(dVar6 * DOUBLE_804374d0 * dVar5 *
                                      -(dVar6 * dVar5 * dVar5 - DOUBLE_804374d8));
    }
    fVar1 = (float)(dVar6 / (double)*(float *)(param_1 + 0x5f8));
    if (*(float *)(param_1 + 0x44) < fVar1) {
      *(float *)(param_1 + 0x44) = fVar1;
      iVar2 = FUN_800452a0(dVar3,dVar4);
      *(short *)(param_1 + 0x5ae) = (short)iVar2;
    }
    *(float *)(param_1 + 0x698) = FLOAT_804374e0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x2000000;
    (**(code **)(param_1 + 0x4c4))(param_1);
    zz_005ec04_(param_1,0xc);
  }
  return;
}



// ==== 8005ef08  FUN_8005ef08 ====

/* WARNING: Removing unreachable block (ram,0x8005efa8) */
/* WARNING: Removing unreachable block (ram,0x8005ef18) */

undefined4 FUN_8005ef08(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)*(float *)(param_1 + 0x24);
  dVar2 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
  *(float *)(param_1 + 0x24) = (float)dVar2;
  fVar1 = *(float *)(param_1 + 0x24) - *(float *)(param_1 + 0x30);
  if ((fVar1 <= *(float *)(param_1 + 0x674)) ||
     ((*(float *)(param_1 + 0x20) == *(float *)(param_1 + 0x2c) &&
      (*(float *)(param_1 + 0x28) == *(float *)(param_1 + 0x34))))) {
    if (fVar1 < -*(float *)(param_1 + 0x674)) {
      *(float *)(param_1 + 0x24) = (float)dVar3;
      return 1;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x2c);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x30);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x34);
  }
  return 0;
}



// ==== 8005efc4  zz_005efc4_ ====

void zz_005efc4_(int param_1,char param_2)

{
  int iVar1;
  
  if (((int)param_2 & 0x80U) == 0) {
    if (((int)param_2 & 0x72U) == 0) {
      iVar1 = 1;
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = 2;
  }
  zz_00680d4_(param_1,iVar1);
  return;
}



// ==== 8005f00c  zz_005f00c_ ====

void zz_005f00c_(int param_1)

{
  byte bVar1;
  char cVar2;
  byte bVar3;
  
  bVar3 = 0;
  *(undefined1 *)(param_1 + 0x700) = *(undefined1 *)(param_1 + 0x6fe);
  *(undefined1 *)(param_1 + 0x6fe) = 0;
  bVar1 = *(byte *)(param_1 + 0x6fd);
  if ((bVar1 & 0x40) == 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        if (*(float *)(param_1 + 0x2a4) < *(float *)(param_1 + 0x920)) {
          bVar3 = 1;
        }
      }
      else {
        bVar3 = 1;
      }
    }
    if (((bVar1 & 0x10) == 0) && ((bVar1 & 0x20) != 0)) {
      bVar3 = bVar3 | 2;
    }
  }
  else if (((*(float *)(param_1 + 0x68c) <= FLOAT_80437444) ||
           (*(char *)(param_1 + 0x700) != '\x01')) || ((*(byte *)(param_1 + 0x6ff) & 0x40) == 0)) {
    bVar3 = 0;
  }
  else {
    bVar3 = 6;
    *(byte *)(param_1 + 0x6fd) = *(byte *)(param_1 + 0x6fd) & 0xbf;
  }
  if (((bVar1 & 2) != 0) || ((*(uint *)(param_1 + 0x5e0) & 0x2000040) != 0)) {
    bVar3 = bVar3 | 4;
  }
  cVar2 = *(char *)(param_1 + 0x591);
  if (cVar2 != '\x03') {
    if (cVar2 < '\x03') {
      if (cVar2 < '\x01') goto LAB_8005f100;
    }
    else if ('\x06' < cVar2) goto LAB_8005f100;
    bVar3 = bVar3 & 0xfc;
  }
LAB_8005f100:
  *(byte *)(param_1 + 0x6fe) = bVar3 + 1;
  *(undefined1 *)(param_1 + 0x6ff) = *(undefined1 *)(param_1 + 0x6fd);
  return;
}



// ==== 8005f114  zz_005f114_ ====

void zz_005f114_(int param_1)

{
  char cVar1;
  
  if (((((*(uint *)(param_1 + 0x5e0) & 0x80000000) == 0) &&
       (cVar1 = *(char *)(param_1 + 0x591), cVar1 != '\x01')) && (cVar1 != '\x02')) &&
     (((cVar1 != '\a' && (cVar1 != '\b')) &&
      ((*(short *)(param_1 + 0x6b4) == 0 && ((*(uint *)(param_1 + 0x5bc) & 0x100) != 0)))))) {
    zz_005ec04_(param_1,0x13);
  }
  return;
}



// ==== 8005f188  zz_005f188_ ====

void zz_005f188_(int param_1,char param_2,char param_3)

{
  float fVar1;
  
  if ((*(char *)(param_1 + 0x1d0c) == param_2) && (*(char *)(param_1 + 0x1d0d) == param_3)) {
    fVar1 = FLOAT_804374b0;
    if (param_2 == -0x80) {
      fVar1 = FLOAT_804374e4;
    }
    if (*(float *)(param_1 + 0x1cfc) <= fVar1) {
      zz_004cd24_(param_1,0xf);
    }
    else {
      zz_004beb8_((double)FLOAT_80437464,param_1,0xf,(int)param_2,(int)param_3,0xffffffff,0xffffffff
                 );
    }
  }
  else {
    zz_004beb8_((double)FLOAT_80437464,param_1,0xf,(int)param_2,(int)param_3,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8005f23c  FUN_8005f23c ====

void FUN_8005f23c(int param_1)

{
  if (((*(char *)(param_1 + 0x1cec) != '\0') || (*(char *)(param_1 + 0x1ced) != '\0')) &&
     (*(char *)(param_1 + 0x1cee) != '\0')) {
    zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0,0xffffffff,0xffffffff);
    return;
  }
  zz_004cd24_(param_1,0xd);
  return;
}



// ==== 8005f2a4  FUN_8005f2a4 ====

void FUN_8005f2a4(int param_1)

{
  if (((*(uint *)(param_1 + 0x5e0) & 1) == 0) &&
     (((*(char *)(param_1 + 0x1d0c) != '\0' || (*(char *)(param_1 + 0x1d0d) != '\0')) &&
      (*(char *)(param_1 + 0x1d0e) != '\0')))) {
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0,0xffffffff,0xffffffff);
    return;
  }
  zz_004cd24_(param_1,2);
  return;
}



// ==== 8005f318  zz_005f318_ ====

void zz_005f318_(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    if (*(char *)(param_1 + 0x661) == '\x04') {
      *(byte *)(param_1 + 0x1b04) = *(byte *)(param_1 + 0x1b44) ^ 1;
    }
    iVar1 = (int)*(float *)(param_1 + 0x1b2c) + -1;
    if (iVar1 < 0) {
      iVar1 = 0;
    }
    zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,1,iVar1,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8005f3a0  FUN_8005f3a0 ====

void FUN_8005f3a0(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    zz_0066ac0_(param_1,0);
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    fVar1 = FLOAT_804374ec;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x10;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + iVar2 * 4 + 0x18);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    uVar3 = (uint)*(short *)(param_1 + 0x5aa);
    if (*(short *)(param_1 + 0x5aa) < 0) {
      uVar3 = -uVar3;
    }
    uVar4 = (uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + 0xc0);
    iVar2 = (int)(((float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_804374f8) /
                  FLOAT_804374f0) *
                  (float)((double)CONCAT44(0x43300000,
                                           *(ushort *)(*(int *)(param_1 + 0x4b0) + 200) - uVar4 ^
                                           0x80000000) - DOUBLE_804374f8) +
                 (float)((double)CONCAT44(0x43300000,uVar4) - DOUBLE_80437500));
    zz_0066ec0_(param_1,iVar2);
    if (*(char *)(param_1 + 0x661) == '\x04') {
      *(byte *)(param_1 + 0x1b44) = *(byte *)(param_1 + 0x1b44) ^ 1;
    }
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,1,iVar2,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_804374ec;
  }
  else {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_004cd24_(param_1,2);
    iVar2 = zz_0066f1c_(param_1);
    if (iVar2 != 0) {
      zz_006a750_(param_1,2);
    }
  }
  return;
}



// ==== 8005f554  zz_005f554_ ====

void zz_005f554_(int param_1)

{
  zz_004cd24_(param_1,0xd);
  return;
}



// ==== 8005f578  zz_005f578_ ====

void zz_005f578_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x10;
  }
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 0x10) != 0) {
    zz_00b22f4_(param_1);
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,0);
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,2);
  return;
}



// ==== 8005f624  zz_005f624_ ====

void zz_005f624_(int param_1)

{
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    *(undefined1 *)(param_1 + 0x1b04) = *(undefined1 *)(param_1 + 0x1b44);
    if (((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 1) == 0) &&
       (*(char *)(param_1 + 1000) != '\x05')) {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0x1f,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0x1f,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8005f6c0  FUN_8005f6c0 ====

void FUN_8005f6c0(int param_1)

{
  float fVar1;
  double dVar2;
  
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 0x10) != 0) {
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 2) == 0) {
      if (*(float *)(param_1 + 0x1b20) <
          (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1b38) / 2 ^ 0x80000000) -
                 DOUBLE_804374f8)) {
        *(byte *)(param_1 + 0x1b44) = *(byte *)(param_1 + 0x1b44) ^ 1;
      }
    }
    fVar1 = FLOAT_804374ec;
    if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 1) == 0) {
      if (*(char *)(param_1 + 0x661) == '\x04') {
        zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0x1f,0xffffffff,0xffffffff);
      }
      else {
        dVar2 = (double)FLOAT_804374e8;
        *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
        *(float *)(param_1 + 0x44) = fVar1;
        zz_004beb8_(dVar2,param_1,2,0,0x1f,0xffffffff,0xffffffff);
      }
    }
    else {
      dVar2 = (double)FLOAT_804374e8;
      *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
      zz_004beb8_(dVar2,param_1,2,0,0x1f,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,2);
    fVar1 = FLOAT_804374ec;
    if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 1) == 0) {
      if (*(char *)(param_1 + 0x661) == '\x04') {
        if (*(char *)(param_1 + 0x1d0f) != '\0') {
          *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
          *(float *)(param_1 + 0x44) = fVar1;
        }
        fVar1 = FLOAT_804374ec;
        if (*(char *)(param_1 + 0x1d0e) != '\0') {
          *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
          *(float *)(param_1 + 0x44) = fVar1;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
          zz_006a474_(param_1);
        }
      }
      else {
        if (*(char *)(param_1 + 0x1b43) == '\0') {
          *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
          *(float *)(param_1 + 0x44) = fVar1;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
          zz_006a474_(param_1);
        }
        *(float *)(param_1 + 0x44) =
             *(float *)(param_1 + 0x44) *
             (FLOAT_8043750c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437508);
      }
    }
    else {
      if (*(char *)(param_1 + 0x1d0e) != '\0') {
        *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
        *(float *)(param_1 + 0x44) = fVar1;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffef;
        zz_006a474_(param_1);
      }
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + 0x44) *
           (FLOAT_8043750c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437508);
    }
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8005f920  FUN_8005f920 ====

void FUN_8005f920(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,2,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8005f978  FUN_8005f978 ====

void FUN_8005f978(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    iVar3 = zz_004cd24_(param_1,2);
    if (iVar3 == 0) goto LAB_8005fa4c;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        *(undefined1 *)(param_1 + 0x87) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdf8f;
        if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 1) == 0) {
          *(float *)(param_1 + 0x44) = FLOAT_804374ec;
        }
        fVar2 = FLOAT_804374ec;
        dVar4 = (double)FLOAT_804374e8;
        *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
        *(float *)(param_1 + 0x50) = fVar2;
        *(float *)(param_1 + 0x48) = fVar2;
        zz_004beb8_(dVar4,param_1,2,0,2,0xffffffff,0xffffffff);
      }
      goto LAB_8005fa4c;
    }
    if ('\x02' < cVar1) goto LAB_8005fa4c;
  }
  zz_006a750_(param_1,5);
LAB_8005fa4c:
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437518 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8005fa90  FUN_8005fa90 ====

void FUN_8005fa90(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,*(char *)(param_1 + 0x5e7) + 4,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8005faf0  FUN_8005faf0 ====

void FUN_8005faf0(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    zz_004cd24_(param_1,2);
    iVar4 = zz_0066f1c_(param_1);
    if (iVar4 != 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x544) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0x588) = 1;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
      *(undefined1 *)(param_1 + 0x87) = 1;
      *(char *)(param_1 + 0x747) = *(char *)(param_1 + 0x747) + '\x01';
      iVar4 = zz_0066ac0_(param_1,0);
      if (iVar4 == 0) {
        *(float *)(param_1 + 0x44) = FLOAT_804374ec;
        *(undefined1 *)(param_1 + 0x5e7) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x50);
        iVar4 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),2);
        if (iVar4 == 0) {
          *(undefined1 *)(param_1 + 0x5e7) = 0;
        }
        else {
          *(undefined1 *)(param_1 + 0x5e7) = 0;
        }
      }
      *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
      fVar2 = FLOAT_8043751c;
      if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
        *(float *)(param_1 + 0x568) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3c))
                    - DOUBLE_80437500);
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
      }
      else {
        *(float *)(param_1 + 0x568) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3d))
                    - DOUBLE_80437500);
      }
      dVar3 = DOUBLE_80437500;
      *(float *)(param_1 + 0x690) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3e)) -
                  DOUBLE_80437500);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x68);
      *(float *)(param_1 + 0x48) =
           -(*(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x568) -
            *(float *)(*(int *)(param_1 + 0x4ac) + 0x48));
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
      fVar2 = FLOAT_80437520;
      if ((*(uint *)(param_1 + 0x5e0) & 0x2000) != 0) {
        *(float *)(param_1 + 0x568) =
             (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3d))
                    - dVar3);
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
        *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar2;
        zz_00b2190_(param_1,2);
      }
      iVar4 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
      zz_0066ec0_(param_1,(uint)*(ushort *)(*(int *)(param_1 + 0x4b0) + iVar4 * 2 + 0xc0));
      zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,*(char *)(param_1 + 0x5e7) + 4,0xffffffff,
                  0xffffffff);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) == '\0') {
        zz_00f036c_(param_1,0x1e);
      }
      else {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
      }
    }
  }
  else if (cVar1 < '\x03') {
    zz_004cd24_(param_1,2);
  }
  zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  if ((*(float *)(param_1 + 0x698) <= FLOAT_804374ec) &&
     (iVar4 = zz_0066ac0_(param_1,0), iVar4 != 0)) {
    FUN_800676d8((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x54),param_1,
                 *(short *)(param_1 + 0x5ac));
  }
  fVar2 = FLOAT_804374ec;
  *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x568) <= fVar2) {
    *(undefined1 *)(param_1 + 0x590) = 0;
    zz_006a750_(param_1,6);
  }
  return;
}



// ==== 8005fe04  FUN_8005fe04 ====

void FUN_8005fe04(int param_1)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    cVar1 = *(char *)(param_1 + 0x590);
    if (cVar1 == '\x02') {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,*(char *)(param_1 + 0x57d) + 0x15,0xffffffff,
                  0xffffffff);
    }
    else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0xd,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,*(char *)(param_1 + 0x5e7) + 6,0xffffffff,
                  0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 8005fecc  FUN_8005fecc ====

void FUN_8005fecc(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  double dVar6;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x87) = 1;
    fVar3 = FLOAT_804374ec;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
    *(code **)(param_1 + 0x754) = FUN_80065e64;
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    cVar1 = *(char *)(param_1 + 0x590);
    if (cVar1 == '\x02') {
      zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,*(char *)(param_1 + 0x57d) + 0x15,0xffffffff,
                  0xffffffff);
    }
    else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
      zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0xd,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,*(char *)(param_1 + 0x5e7) + 6,0xffffffff,
                  0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,2);
  }
  if (*(float *)(param_1 + 0x690) <= FLOAT_804374ec) {
    *(undefined1 *)(param_1 + 0x588) = 1;
  }
  if ((*(float *)(param_1 + 0x698) <= FLOAT_804374ec) &&
     (iVar4 = zz_0066ac0_(param_1,0), iVar4 != 0)) {
    FUN_800676d8((double)*(float *)(*(int *)(param_1 + 0x4ac) + 0x54),param_1,
                 *(short *)(param_1 + 0x5ac));
  }
  if (*(char *)(param_1 + 0x661) == '\x02') {
    zz_0066ac0_(param_1,0);
    zz_0066e40_(param_1,1);
  }
  dVar6 = (double)FLOAT_80437510;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437528 * (float)(dVar6 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_80437524);
  sVar2 = *(short *)(param_1 + 1000);
  if (((sVar2 == 0x207) || (sVar2 == 0x205)) || (sVar2 == 0x209)) {
    uVar5 = 2;
    if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
      uVar5 = 0xf;
    }
    if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
      if (*(char *)(param_1 + 0x1d10) != '\0') {
        zz_004beb8_((double)FLOAT_804374e8,param_1,uVar5,0,0xd,0xffffffff,0xffffffff);
      }
      FUN_80067310((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    }
    else if (FLOAT_8043752c <= *(float *)(param_1 + 0x48)) {
      dVar6 = (double)FLOAT_80437510;
      *(undefined1 *)(param_1 + 0x1d0f) = 0;
      FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
    }
    else {
      iVar4 = zz_0066ac0_(param_1,0);
      if (iVar4 == 0) {
        if (*(char *)(param_1 + 0x1d10) != '\x01') {
          zz_004beb8_((double)FLOAT_804374e8,param_1,uVar5,0,0x2a,0xffffffff,0xffffffff);
        }
      }
      else if (*(char *)(param_1 + 0x1d10) != '\x02') {
        zz_004beb8_((double)FLOAT_804374e8,param_1,uVar5,0,0x2b,0xffffffff,0xffffffff);
      }
      zz_0066e40_(param_1,1);
      FUN_80067310((double)FLOAT_804374ec,param_1,*(short *)(param_1 + 0x5ae));
    }
  }
  else {
    FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_00677b0_(param_1);
  return;
}



// ==== 800601d0  FUN_800601d0 ====

void FUN_800601d0(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,8,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80060228  FUN_80060228 ====

void FUN_80060228(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    fVar1 = FLOAT_804374ec;
    *(undefined1 *)(param_1 + 0x87) = 0;
    dVar3 = (double)FLOAT_804374e8;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfbf;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x200;
    *(float *)(param_1 + 0x69c) = fVar1;
    zz_004beb8_(dVar3,param_1,2,0,2,0xffffffff,0xffffffff);
    fVar1 = FLOAT_804374ec;
    if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 1) == 0) {
      *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
      *(float *)(param_1 + 0x44) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
    }
    fVar1 = FLOAT_804374ec;
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    dVar3 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
    *(float *)(param_1 + 0x24) = (float)dVar3;
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,8,0xffffffff,0xffffffff);
    zz_00b2190_(param_1,2);
    if (*(char *)(param_1 + 0x661) != '\x05') {
      zz_00f07e8_(param_1);
    }
  }
  else {
    iVar2 = zz_004cd24_(param_1,2);
    if (iVar2 != 0) {
      zz_006a474_(param_1);
    }
  }
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_80437518 * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437514);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 8006037c  FUN_8006037c ====

void FUN_8006037c(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x540);
  if (cVar1 == '\x02') {
    dVar3 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 3;
    zz_004beb8_(dVar3,param_1,0xd,0,*(char *)(param_1 + 0x57d) + 0xf,0xffffffff,0xffffffff);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      dVar3 = (double)FLOAT_804374e8;
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_004beb8_(dVar3,param_1,0xd,0,0xe,0xffffffff,0xffffffff);
    }
    else if ((-1 < cVar1) && (iVar2 = zz_004cd24_(param_1,0xd), iVar2 != 0)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80060454  FUN_80060454 ====

void FUN_80060454(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x544) = 3;
    iVar5 = zz_0066ac0_(param_1,0);
    if (iVar5 == 0) {
      *(float *)(param_1 + 0x44) = FLOAT_804374ec;
      *(undefined1 *)(param_1 + 0x57d) = 1;
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(*(int *)(param_1 + 0x4ac) + 0x50) * FLOAT_80437534;
      iVar5 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),0);
      *(undefined *)(param_1 + 0x57d) = (&DAT_80433830)[iVar5];
    }
    if (((int)*(char *)(param_1 + 0x747) != (uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f)) ||
       ((*(uint *)(param_1 + 0x5e0) & 1) != 0)) {
      *(undefined1 *)(param_1 + 0x57d) = 0;
    }
    dVar3 = DOUBLE_80437500;
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    dVar6 = (double)FLOAT_804374e8;
    *(float *)(param_1 + 0x568) =
         FLOAT_80437510 +
         (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x3f)) -
                dVar3);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x68);
    *(float *)(param_1 + 0x48) =
         -(*(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x568) -
          *(float *)(*(int *)(param_1 + 0x4ac) + 0x4c));
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    zz_004beb8_(dVar6,param_1,2,0,*(char *)(param_1 + 0x57d) + 0xf,0xffffffff,0xffffffff);
    if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) == '\0') {
      zz_00f036c_(param_1,0x1e);
    }
    else {
      *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x544) = 1;
      *(undefined1 *)(param_1 + 0x87) = 1;
      fVar4 = FLOAT_80437530;
      dVar3 = DOUBLE_80437500;
      fVar2 = FLOAT_804374ec;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfef;
      dVar6 = (double)FLOAT_804374e8;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
      *(code **)(param_1 + 0x754) = FUN_80065e64;
      *(float *)(param_1 + 0x69c) = fVar2;
      *(undefined1 *)(param_1 + 0x588) = 1;
      *(char *)(param_1 + 0x747) = *(char *)(param_1 + 0x747) + '\x01';
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar4;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(float *)(param_1 + 0x690) =
           (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x40)) -
                  dVar3);
      zz_004beb8_(dVar6,param_1,2,0,0xe,0xffffffff,0xffffffff);
      if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
        *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
      }
    }
    else if ((-1 < cVar1) && (iVar5 = zz_004cd24_(param_1,2), iVar5 != 0)) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    zz_004cd24_(param_1,2);
    fVar2 = FLOAT_804374ec;
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x568) <= fVar2) {
      *(undefined1 *)(param_1 + 0x590) = 2;
      zz_006a750_(param_1,6);
    }
  }
  zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80060730  FUN_80060730 ====

void FUN_80060730(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_005c080_(param_1);
  fVar1 = *(float *)(param_1 + 0x20);
  fVar2 = *(float *)(DAT_8043625c + 0x38) - FLOAT_80437538;
  if (fVar1 <= fVar2) {
    fVar2 = FLOAT_80437538 + *(float *)(DAT_8043625c + 0x3c);
    if (fVar2 <= fVar1) {
      *(float *)(param_1 + 0x38) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x38) = fVar2;
    }
  }
  else {
    *(float *)(param_1 + 0x38) = fVar2;
  }
  fVar1 = *(float *)(param_1 + 0x28);
  fVar2 = *(float *)(DAT_8043625c + 0x40) - FLOAT_80437538;
  if (fVar1 <= fVar2) {
    fVar2 = FLOAT_80437538 + *(float *)(DAT_8043625c + 0x44);
    if (fVar2 <= fVar1) {
      *(float *)(param_1 + 0x40) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x40) = fVar2;
    }
  }
  else {
    *(float *)(param_1 + 0x40) = fVar2;
  }
  dVar3 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,(float *)(param_1 + 0x38));
  *(float *)(param_1 + 0x3c) = (float)((double)FLOAT_8043753c + dVar3);
  if (*(char *)(param_1 + 1000) == '\x05') {
    zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,0xd,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0x81,0x11,0xffffffff,0xffffffff);
    fVar1 = FLOAT_80437510;
    *(float *)(param_1 + 0x1dcc) = FLOAT_80437510;
    *(float *)(param_1 + 0x1dc8) = fVar1;
  }
  zz_006a750_(param_1,10);
  return;
}



// ==== 80060864  FUN_80060864 ====

void FUN_80060864(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  double dVar7;
  float local_14 [2];
  float local_c;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043755c;
  cVar1 = *(char *)(param_1 + 0x544);
  switch(cVar1) {
  case '\0':
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    if (*(float *)(param_1 + 0x3c) <= *(float *)(param_1 + 0x24)) {
      *(undefined1 *)(param_1 + 0x544) = 2;
      return;
    }
  case '\x01':
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_80437540;
    if (*(float *)(param_1 + 0x3c) <= *(float *)(param_1 + 0x24)) {
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x3c);
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    }
    break;
  case '\x02':
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x20),local_14);
    iVar4 = FUN_800452a0((double)local_14[0],(double)local_c);
    *(short *)(param_1 + 0x5ae) = (short)iVar4;
    dVar7 = (double)(local_14[0] * local_14[0] + local_c * local_c);
    if ((double)FLOAT_804374ec < dVar7) {
      dVar6 = 1.0 / SQRT(dVar7);
      dVar6 = DOUBLE_80437548 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437550);
      dVar6 = DOUBLE_80437548 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437550);
      dVar7 = (double)(float)(dVar7 * DOUBLE_80437548 * dVar6 *
                                      -(dVar7 * dVar6 * dVar6 - DOUBLE_80437550));
    }
    *(float *)(param_1 + 0x44) = (float)(dVar7 / (double)FLOAT_80437558);
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / *(float *)(param_1 + 0xb4);
    *(undefined2 *)(param_1 + 0x550) = 0x1e;
    break;
  case '\x03':
    if ((*(byte *)(param_1 + 0x274) & 1) != 0) {
      *(undefined1 *)(param_1 + 0x544) = 1;
      *(float *)(param_1 + 0x3c) = fVar2 + *(float *)(param_1 + 0x24);
      return;
    }
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    sVar5 = *(short *)(param_1 + 0x550) + -1;
    *(short *)(param_1 + 0x550) = sVar5;
    fVar3 = FLOAT_80437560;
    fVar2 = FLOAT_804374ec;
    if (0 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x50) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    *(float *)(param_1 + 0x50) = fVar3;
  case '\x04':
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar4 = zz_00677b0_(param_1);
    if (iVar4 != 0) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      if (*(char *)(param_1 + 1000) == '\x05') {
        zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0,8,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0x82,2,0xffffffff,0xffffffff);
        fVar2 = FLOAT_80437510;
        *(float *)(param_1 + 0x1dcc) = FLOAT_80437510;
        *(float *)(param_1 + 0x1dc8) = fVar2;
      }
      *(float *)(param_1 + 0x6d0) = FLOAT_804374ec;
      zz_00b2190_(param_1,2);
    }
    break;
  case '\x05':
    if (*(char *)(param_1 + 0x1d0e) == '\0') {
      return;
    }
    *(char *)(param_1 + 0x544) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    if (*(char *)(param_1 + 1000) != '\x05') {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xf,0x82,4,0xffffffff,0xffffffff);
      fVar2 = FLOAT_80437510;
      *(float *)(param_1 + 0x1dcc) = FLOAT_80437510;
      *(float *)(param_1 + 0x1dc8) = fVar2;
    }
  case '\x06':
    if (*(char *)(param_1 + 0x1d0e) != '\0') {
      zz_006a750_(param_1,0xb);
    }
  }
  return;
}



// ==== 80060b60  FUN_80060b60 ====

void FUN_80060b60(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  *(undefined2 *)(param_1 + 0x272) = 0;
  if (*(char *)(param_1 + 0x6cb) == '\x01') {
    *(float *)(param_1 + 0x720) = FLOAT_80437558;
  }
  else {
    *(float *)(param_1 + 0x720) = FLOAT_80437564;
  }
  fVar1 = FLOAT_804374ec;
  *(undefined1 *)(param_1 + 0x6cb) = 0;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006a474_(param_1);
  return;
}



// ==== 80060be8  zz_0060be8_ ====

void zz_0060be8_(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,*(char *)(param_1 + 0x57c) + 0x1b,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80060c48  FUN_80060c48 ====

void FUN_80060c48(int param_1)

{
  zz_0060c94_(param_1);
  zz_006a750_(param_1,0xd);
  *(float *)(param_1 + 0x80c) = FLOAT_804374ec;
  zz_00b2190_(param_1,0);
  return;
}



// ==== 80060c94  zz_0060c94_ ====

void zz_0060c94_(int param_1)

{
  char cVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x7cc) = 1;
  *(undefined1 *)(param_1 + 0x5e6) = 0;
  *(undefined1 *)(param_1 + 0x656) = 1;
  zz_0066ac0_(param_1,1);
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 0x20) == 0) {
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),0);
    *(undefined *)(param_1 + 0x57c) = (&DAT_80433838)[iVar2];
  }
  else {
    iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x734),0);
    *(undefined *)(param_1 + 0x57c) = (&DAT_80433838)[iVar2];
    if ((*(char *)(param_1 + 0x57c) == '\0') &&
       (iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),0), (&DAT_80433838)[iVar2] == '\x02')) {
      *(undefined1 *)(param_1 + 0x57c) = 2;
    }
  }
  iVar2 = zz_0046510_(*(ushort *)(param_1 + 0x734),2);
  *(char *)(param_1 + 0x57d) = (char)iVar2;
  zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,*(char *)(param_1 + 0x57c) + 0x1b,0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x48) = FLOAT_804374ec;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  iVar2 = *(int *)(param_1 + 0x4ac);
  if (*(char *)(iVar2 + 0x41) == '\0') {
    zz_00f036c_(param_1,0x1e);
  }
  else {
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
  }
  cVar1 = *(char *)(param_1 + 0x57c);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar2 + 0xf0);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar2 + 0xf4);
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0xf8);
        *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar2 + 0xfc);
        goto LAB_80060e58;
      }
    }
    else if (cVar1 < '\x03') {
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar2 + 0x110);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar2 + 0x114);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x118);
      *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar2 + 0x11c);
      goto LAB_80060e58;
    }
  }
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(iVar2 + 0x100);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar2 + 0x104);
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x108);
  *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(iVar2 + 0x10c);
LAB_80060e58:
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5b0) + -0x8000;
  zz_0065eb0_(param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 80060e94  zz_0060e94_ ====

void zz_0060e94_(int param_1)

{
  if (*(char *)(param_1 + 0x57e) == '\0') {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80060ec4  FUN_80060ec4 ====

void FUN_80060ec4(int param_1)

{
  int iVar1;
  
  zz_0060f78_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar1 = zz_00677b0_(param_1);
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x7cc) = 0;
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_804374ec;
      *(undefined1 *)(param_1 + 0x7cc) = 1;
    }
  }
  if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0) {
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x545) != '\0') {
    zz_006a750_(param_1,0xe);
  }
  return;
}



// ==== 80060f78  zz_0060f78_ ====

void zz_0060f78_(int param_1)

{
  float fVar1;
  
  zz_0065eb0_(param_1);
  if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x38);
  }
  if ((*(byte *)(param_1 + 0x1d0f) & 1) == 0) {
    zz_004cd24_(param_1,2);
    *(undefined1 *)(param_1 + 0x57e) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x57e) = 1;
  }
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if ((*(float *)(param_1 + 0x568) <= fVar1) ||
       ((*(uint *)(param_1 + 0x5b4) & *(uint *)(&DAT_802d38c4 + *(char *)(param_1 + 0x57d) * 4)) ==
        0)) {
      *(undefined1 *)(param_1 + 0x545) = 1;
    }
  }
  return;
}



// ==== 80061048  zz_0061048_ ====

void zz_0061048_(int param_1)

{
  if (*(char *)(param_1 + 0x57e) == '\0') {
    zz_004cd24_(param_1,0xd);
  }
  else {
    zz_004cff4_(param_1,0xd);
  }
  return;
}



// ==== 80061084  FUN_80061084 ====

void FUN_80061084(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_0061160_(param_1);
  if ((FLOAT_804374ec < *(float *)(param_1 + 0x44)) &&
     ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 4) != 0)) {
    zz_00b22f4_(param_1);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    zz_0067458_((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      *(undefined1 *)(param_1 + 0x7cc) = 0;
      *(undefined1 *)(param_1 + 0x709) = 0;
    }
    else {
      *(float *)(param_1 + 0x48) = FLOAT_804374ec;
      if (*(char *)(param_1 + 0x545) == '\0') {
        *(undefined1 *)(param_1 + 0x7cc) = 1;
      }
    }
  }
  fVar1 = FLOAT_804374ec;
  if (*(char *)(param_1 + 0x1d0e) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(float *)(param_1 + 0x44) = fVar1;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80061160  zz_0061160_ ====

void zz_0061160_(int param_1)

{
  char cVar1;
  
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x545) = 0;
    *(undefined1 *)(param_1 + 0x709) = 0;
    if ((*(byte *)(param_1 + 0x1d0f) & 2) == 0) {
      zz_004cd24_(param_1,2);
      *(undefined1 *)(param_1 + 0x57e) = 0;
    }
    else {
      zz_004cff4_(param_1,2);
      *(undefined1 *)(param_1 + 0x57e) = 1;
    }
  }
  else {
    zz_004cd24_(param_1,2);
    *(undefined1 *)(param_1 + 0x57e) = 0;
  }
  if ((*(char *)(param_1 + 0x545) == '\0') && (*(char *)(param_1 + 0x1d0f) == '\x03')) {
    *(undefined1 *)(param_1 + 0x545) = 1;
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined1 *)(param_1 + 0x7cc) = 0;
  }
  if (*(char *)(param_1 + 0x661) == '\x02') {
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_8043756c * (FLOAT_80437510 - *(float *)(param_1 + 0x1dc8)) + FLOAT_80437568);
  }
  else if ((*(uint *)(*(int *)(param_1 + 0x4b0) + 8) & 8) == 0) {
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x1dac);
  }
  else {
    cVar1 = *(char *)(param_1 + 0x546);
    if (cVar1 == '\x01') {
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x1dac);
    }
    else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
            (*(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437570,
            *(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x1dac))) {
      *(char *)(param_1 + 0x546) = *(char *)(param_1 + 0x546) + '\x01';
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x1dac);
    }
  }
  if (FLOAT_804374ec < *(float *)(param_1 + 0x44)) {
    zz_0065eb0_(param_1);
  }
  return;
}



// ==== 800612e0  FUN_800612e0 ====

void FUN_800612e0(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,10,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80061338  FUN_80061338 ====

void FUN_80061338(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x69c) = FLOAT_80437558;
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined4 *)(param_1 + 0x754) = 0;
    if ((*(char *)(param_1 + 0x7cd) == '\0') && (*(char *)(param_1 + 0x747) == '\0')) {
      *(undefined1 *)(param_1 + 0x747) = 1;
    }
    *(undefined1 *)(param_1 + 0x87) = 1;
    zz_0066ac0_(param_1,2);
    fVar2 = FLOAT_80437534;
    fVar1 = FLOAT_804374ec;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffdfff;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    iVar3 = zz_0046510_(*(ushort *)(param_1 + 0x5aa),1);
    *(float *)(param_1 + 0x568) =
         (float)((double)CONCAT44(0x43300000,
                                  *(ushort *)(*(int *)(param_1 + 0x4b0) + iVar3 * 2 + 0xc0) >> 1 ^
                                  0x80000000) - DOUBLE_804374f8);
    zz_0066ec0_(param_1,(int)*(float *)(param_1 + 0x568));
    zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,10,0xffffffff,0xffffffff);
    zz_00f036c_(param_1,0x25);
  }
  else {
    zz_004cd24_(param_1,2);
    zz_0066f1c_(param_1);
    FUN_80067310((double)FLOAT_80437510,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_804374ec;
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x568) <= fVar1) {
      zz_00664a0_(param_1,2);
      zz_006a750_(param_1,0x10);
    }
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    *(float *)(param_1 + 0x48) = FLOAT_804374ec;
  }
  return;
}



// ==== 800614f0  FUN_800614f0 ====

void FUN_800614f0(int param_1)

{
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    if (*(char *)(param_1 + 1000) == '\x05') {
      zz_004cd24_(param_1,0xd);
    }
    else {
      zz_004beb8_((double)FLOAT_804374e8,param_1,0xd,0,0xb,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



// ==== 80061560  FUN_80061560 ====

void FUN_80061560(int param_1)

{
  char cVar1;
  undefined1 uVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_804374ec;
  cVar1 = *(char *)(param_1 + 0x544);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x568) = *(float *)(param_1 + 0x568) - *(float *)(param_1 + 0x5f4);
    if (*(float *)(param_1 + 0x568) <= fVar3) {
      *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
      if (*(short *)(param_1 + 0x550) != 0) {
        zz_006a750_(param_1,0x11);
      }
      *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
      *(undefined1 *)(param_1 + 0x588) = 1;
      *(code **)(param_1 + 0x754) = FUN_80065e64;
    }
  }
  else {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(char *)(param_1 + 0x544) = cVar1 + '\x01';
        *(undefined1 *)(param_1 + 0x5e6) = 0;
        *(undefined1 *)(param_1 + 0x656) = 1;
        zz_0092dcc_(param_1,0);
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x60);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
        *(undefined4 *)(param_1 + 0x568) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 100);
        uVar4 = countLeadingZeros((int)*(char *)(param_1 + 0x7cd));
        *(short *)(param_1 + 0x550) = (short)(uVar4 >> 5);
        *(undefined4 *)(param_1 + 0x754) = 0;
        if (*(char *)(param_1 + 1000) == '\x05') {
          zz_004cd24_(param_1,2);
        }
        else {
          zz_004beb8_((double)FLOAT_804374e8,param_1,2,0,0xb,0xffffffff,0xffffffff);
        }
      }
      goto LAB_800616e0;
    }
    if ('\x02' < cVar1) goto LAB_800616e0;
  }
  zz_004cd24_(param_1,2);
  fVar3 = FLOAT_804374ec;
  if (*(float *)(param_1 + 0x44) < FLOAT_804374ec) {
    *(float *)(param_1 + 0x4c) = FLOAT_804374ec;
    *(float *)(param_1 + 0x44) = fVar3;
  }
LAB_800616e0:
  if (*(char *)(*(int *)(param_1 + 0x4ac) + 0x41) != '\0') {
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
  }
  *(float *)(param_1 + 0x69c) = FLOAT_80437558;
  zz_00664a0_(param_1,3);
  if ((*(short *)(param_1 + 0x550) == 0) && (*(short *)(param_1 + 0x736) < 1)) {
    uVar2 = *(undefined1 *)(param_1 + 0x588);
    zz_006a750_(param_1,0x11);
    *(undefined1 *)(param_1 + 0x588) = uVar2;
  }
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  dVar5 = (double)FLOAT_80437510;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8006178c  FUN_8006178c ====

void FUN_8006178c(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    dVar1 = (double)FLOAT_804374e8;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar1,param_1,0xd,0,0xc,0xffffffff,0xffffffff);
  }
  else {
    zz_004cd24_(param_1,0xd);
  }
  return;
}



