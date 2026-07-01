// ==== 8026d6c8  zz_026d6c8_ ====

undefined4 zz_026d6c8_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 3) = 0;
  if (*(int *)(param_1 + 0x10) == 0) {
    *(undefined1 *)(param_1 + 1) = 3;
  }
  else {
    *(undefined1 *)(param_1 + 1) = 2;
  }
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined1 *)(param_1 + 0x43) = 1;
  *(undefined4 *)(param_1 + 0x58) = param_2;
  return 1;
}



// ==== 8026d718  zz_026d718_ ====

undefined4 zz_026d718_(int param_1)

{
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 3) = 0;
  if (*(int *)(param_1 + 0x10) == 0) {
    *(undefined1 *)(param_1 + 1) = 3;
  }
  else {
    *(undefined1 *)(param_1 + 1) = 2;
  }
  *(undefined1 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined1 *)(param_1 + 0x43) = 1;
  *(undefined4 *)(param_1 + 0x58) = 0xfffff;
  return 1;
}



// ==== 8026d770  zz_026d770_ ====

undefined4 zz_026d770_(int param_1)

{
  if (*(int *)(param_1 + 8) != 0) {
    return *(undefined4 *)(param_1 + 0x54);
  }
  return 0;
}



// ==== 8026d78c  zz_026d78c_ ====

undefined4 zz_026d78c_(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  *(undefined4 *)(param_1 + 0x54) = param_2;
  uVar3 = *(uint *)(param_1 + 0x10);
  if ((int)uVar3 < *(int *)(param_1 + 0x54) << 0xb) {
    iVar1 = (int)uVar3 >> 0x1f;
    uVar2 = (iVar1 * 0x800 | uVar3 * 0x200000 + iVar1 >> 0x15) - iVar1;
    *(uint *)(param_1 + 0x54) =
         (((int)uVar3 >> 0xb) + (uint)((int)uVar3 < 0 && (uVar3 & 0x7ff) != 0)) -
         ((int)(-uVar2 & ~uVar2) >> 0x1f);
  }
  return *(undefined4 *)(param_1 + 0x54);
}



// ==== 8026d7dc  zz_026d7dc_ ====

int zz_026d7dc_(int param_1)

{
  return (int)*(char *)(param_1 + 1);
}



// ==== 8026d7e8  zz_026d7e8_ ====

void zz_026d7e8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  char *pcVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar5 = zz_0278944_();
  if ((*(char *)(param_9 + 1) == '\x02') && (*(char *)(param_9 + 2) == '\x01')) {
    *(undefined1 *)(param_9 + 0x44) = 1;
    if (*(char *)(param_9 + 0x43) == '\x01') {
      *(undefined1 *)(param_9 + 0x43) = 0;
    }
  }
  else {
    *(undefined1 *)(param_9 + 1) = 1;
  }
  uVar5 = zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar2 = extraout_r4;
  do {
    uVar1 = zz_0277a30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803ff2ec,
                        uVar2,param_11,param_12,param_13,param_14,param_15,param_16);
    if (uVar1 != 0) {
      iVar4 = 0;
      pcVar3 = &DAT_803ff2f8;
      do {
        if (*pcVar3 == '\x01') {
          uVar5 = zz_026cf58_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)pcVar3,uVar2,param_11,param_12,param_13,param_14,param_15,
                              param_16);
          uVar2 = extraout_r4_00;
        }
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 0x5c;
      } while (iVar4 < 0x28);
      DAT_803ff2ec = 0;
    }
  } while ((*(char *)(param_9 + 1) != '\x01') || (*(int *)(param_9 + 0x20) != 0));
  uVar5 = zz_0278944_();
  if ((*(char *)(param_9 + 1) == '\x02') && (*(char *)(param_9 + 2) == '\x01')) {
    *(undefined1 *)(param_9 + 0x44) = 1;
    if (*(char *)(param_9 + 0x43) == '\x01') {
      *(undefined1 *)(param_9 + 0x43) = 0;
    }
  }
  else {
    *(undefined1 *)(param_9 + 1) = 1;
  }
  zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar5 = zz_0278944_();
  if (*(char *)(param_9 + 0x45) == '\x01') {
    *(undefined1 *)(param_9 + 0x42) = 1;
  }
  *(undefined1 *)(param_9 + 0x41) = 0;
  uVar5 = zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar2 = extraout_r4_01;
  while (*(char *)(param_9 + 0x45) != '\0') {
    uVar1 = zz_0277a30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803ff2ec,
                        uVar2,param_11,param_12,param_13,param_14,param_15,param_16);
    if (uVar1 != 0) {
      iVar4 = 0;
      pcVar3 = &DAT_803ff2f8;
      do {
        if (*pcVar3 == '\x01') {
          uVar5 = zz_026cf58_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)pcVar3,uVar2,param_11,param_12,param_13,param_14,param_15,
                              param_16);
          uVar2 = extraout_r4_02;
        }
        iVar4 = iVar4 + 1;
        pcVar3 = pcVar3 + 0x5c;
      } while (iVar4 < 0x28);
      DAT_803ff2ec = 0;
    }
  }
  return;
}



// ==== 8026d9ac  zz_026d9ac_ ====

void zz_026d9ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined8 uVar1;
  
  uVar1 = zz_0278944_();
  if ((*(char *)(param_9 + 1) == '\x02') && (*(char *)(param_9 + 2) == '\x01')) {
    *(undefined1 *)(param_9 + 0x44) = 1;
    if (*(char *)(param_9 + 0x43) == '\x01') {
      *(undefined1 *)(param_9 + 0x43) = 0;
    }
  }
  else {
    *(undefined1 *)(param_9 + 1) = 1;
  }
  zz_02788b4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = zz_0278944_();
  if (*(char *)(param_9 + 0x45) == '\x01') {
    *(undefined1 *)(param_9 + 0x42) = 1;
  }
  *(undefined1 *)(param_9 + 0x41) = 0;
  zz_02788b4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 8026da40  zz_026da40_ ====

void zz_026da40_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined8 uVar8;
  
  uVar3 = param_11;
  uVar4 = param_12;
  iVar5 = param_13;
  uVar8 = zz_0278944_();
  *(undefined4 *)(param_9 + 0xc) = param_12;
  *(int *)(param_9 + 0x10) = param_13 << 0xb;
  *(undefined4 *)(param_9 + 0x4c) = param_10;
  *(undefined4 *)(param_9 + 0x50) = param_11;
  *(undefined1 *)(param_9 + 0x41) = 1;
  uVar8 = zz_02788b4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar2 = extraout_r4;
  do {
    uVar1 = zz_0277a30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803ff2ec,
                        uVar2,uVar3,uVar4,iVar5,param_14,param_15,param_16);
    if (uVar1 != 0) {
      iVar7 = 0;
      pcVar6 = &DAT_803ff2f8;
      do {
        if (*pcVar6 == '\x01') {
          uVar8 = zz_026cf58_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)pcVar6,uVar2,uVar3,uVar4,iVar5,param_14,param_15,param_16);
          uVar2 = extraout_r4_00;
        }
        iVar7 = iVar7 + 1;
        pcVar6 = pcVar6 + 0x5c;
      } while (iVar7 < 0x28);
      DAT_803ff2ec = 0;
    }
  } while (*(char *)(param_9 + 0x45) != '\x01');
  return;
}



// ==== 8026dafc  zz_026dafc_ ====

void zz_026dafc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                )

{
  undefined8 uVar1;
  
  uVar1 = zz_0278944_();
  *(undefined4 *)(param_9 + 0xc) = param_12;
  *(int *)(param_9 + 0x10) = param_13 << 0xb;
  *(undefined4 *)(param_9 + 0x4c) = param_10;
  *(undefined4 *)(param_9 + 0x50) = param_11;
  *(undefined1 *)(param_9 + 0x41) = 1;
  zz_02788b4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 8026db58  zz_026db58_ ====

void zz_026db58_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined1 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  char *pcVar3;
  int iVar4;
  undefined8 uVar5;
  
  if (param_9 != (undefined1 *)0x0) {
    uVar5 = zz_0278944_();
    if ((param_9[1] == '\x02') && (param_9[2] == '\x01')) {
      param_9[0x44] = 1;
      if (param_9[0x43] == '\x01') {
        param_9[0x43] = 0;
      }
    }
    else {
      param_9[1] = 1;
    }
    uVar5 = zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar2 = extraout_r4;
    do {
      uVar1 = zz_0277a30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803ff2ec,uVar2,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      if (uVar1 != 0) {
        iVar4 = 0;
        pcVar3 = &DAT_803ff2f8;
        do {
          if (*pcVar3 == '\x01') {
            uVar5 = zz_026cf58_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (int)pcVar3,uVar2,param_11,param_12,param_13,param_14,param_15,
                                param_16);
            uVar2 = extraout_r4_00;
          }
          iVar4 = iVar4 + 1;
          pcVar3 = pcVar3 + 0x5c;
        } while (iVar4 < 0x28);
        DAT_803ff2ec = 0;
      }
    } while ((param_9[1] != '\x01') || (*(int *)(param_9 + 0x20) != 0));
    uVar5 = zz_0278944_();
    if ((param_9[1] == '\x02') && (param_9[2] == '\x01')) {
      param_9[0x44] = 1;
      if (param_9[0x43] == '\x01') {
        param_9[0x43] = 0;
      }
    }
    else {
      param_9[1] = 1;
    }
    uVar5 = zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar2 = extraout_r4_01;
    do {
      uVar1 = zz_0277a30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803ff2ec,uVar2,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      if (uVar1 != 0) {
        iVar4 = 0;
        pcVar3 = &DAT_803ff2f8;
        do {
          if (*pcVar3 == '\x01') {
            uVar5 = zz_026cf58_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (int)pcVar3,uVar2,param_11,param_12,param_13,param_14,param_15,
                                param_16);
            uVar2 = extraout_r4_02;
          }
          iVar4 = iVar4 + 1;
          pcVar3 = pcVar3 + 0x5c;
        } while (iVar4 < 0x28);
        DAT_803ff2ec = 0;
      }
    } while ((param_9[1] != '\x01') || (*(int *)(param_9 + 0x20) != 0));
    uVar5 = zz_0278944_();
    if ((param_9[1] == '\x02') && (param_9[2] == '\x01')) {
      param_9[0x44] = 1;
      if (param_9[0x43] == '\x01') {
        param_9[0x43] = 0;
      }
    }
    else {
      param_9[1] = 1;
    }
    zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar5 = zz_0278944_();
    if (param_9[0x45] == '\x01') {
      param_9[0x42] = 1;
    }
    param_9[0x41] = 0;
    uVar5 = zz_02788b4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar2 = extraout_r4_03;
    while (param_9[0x45] != '\0') {
      uVar1 = zz_0277a30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803ff2ec,uVar2,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
      if (uVar1 != 0) {
        iVar4 = 0;
        pcVar3 = &DAT_803ff2f8;
        do {
          if (*pcVar3 == '\x01') {
            uVar5 = zz_026cf58_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                (int)pcVar3,uVar2,param_11,param_12,param_13,param_14,param_15,
                                param_16);
            uVar2 = extraout_r4_04;
          }
          iVar4 = iVar4 + 1;
          pcVar3 = pcVar3 + 0x5c;
        } while (iVar4 < 0x28);
        DAT_803ff2ec = 0;
      }
    }
    *param_9 = 0;
    gnt4_memset(param_9,0,0x5c);
  }
  return;
}



// ==== 8026ddec  zz_026ddec_ ====

char * zz_026ddec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  int *param_9,int param_10)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  if (param_10 < 0x100) {
    pcVar4 = (char *)0x0;
    iVar3 = 0;
    iVar2 = DAT_803ff2e8 * 0x5c;
    iVar5 = DAT_803adec0;
    if (0 < DAT_803adec0) {
      do {
        pcVar4 = &DAT_803ff2f8 + iVar2;
        if (*pcVar4 == '\0') break;
        iVar2 = iVar2 + 0x5c;
        iVar3 = iVar3 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (iVar3 == DAT_803adec0) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4[1] = '\x01';
      pcVar4[2] = '\0';
      *(int **)(pcVar4 + 4) = param_9;
      pcVar4[8] = '\0';
      pcVar4[9] = '\0';
      pcVar4[10] = '\0';
      pcVar4[0xb] = '\0';
      pcVar4[0xc] = '\0';
      pcVar4[0xd] = '\0';
      pcVar4[0xe] = '\0';
      pcVar4[0xf] = '\0';
      pcVar4[0x10] = '\0';
      pcVar4[0x11] = '\0';
      pcVar4[0x12] = '\0';
      pcVar4[0x13] = '\0';
      pcVar4[0x28] = '\0';
      pcVar4[0x29] = '\0';
      pcVar4[0x2a] = '\x02';
      pcVar4[0x2b] = '\0';
      pcVar4[0x54] = '\0';
      pcVar4[0x55] = '\0';
      pcVar4[0x56] = '\0';
      pcVar4[0x57] = '\0';
      pcVar4[0x58] = '\0';
      pcVar4[0x59] = '\x0f';
      pcVar4[0x5a] = -1;
      pcVar4[0x5b] = -1;
      uVar1 = *(uint *)(pcVar4 + 0x10);
      *(uint *)(pcVar4 + 0x2c) =
           ((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0);
      iVar5 = *(int *)(pcVar4 + 0x10) >> 0x1f;
      if (0 < (int)((iVar5 * 0x800 | (uint)(*(int *)(pcVar4 + 0x10) * 0x200000 + iVar5) >> 0x15) -
                   iVar5)) {
        *(int *)(pcVar4 + 0x2c) = *(int *)(pcVar4 + 0x2c) + 1;
      }
      if (*(int *)(pcVar4 + 4) != 0) {
        zz_026960c_();
        iVar5 = (**(code **)(*param_9 + 0x24))(param_9,1);
        iVar2 = (**(code **)(*param_9 + 0x24))(param_9,0);
        *(int *)(pcVar4 + 0x3c) = iVar2 + iVar5;
        zz_02695d4_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        *(undefined4 *)(pcVar4 + 0x14) = *(undefined4 *)(pcVar4 + 0x3c);
        *(undefined4 *)(pcVar4 + 0x18) = *(undefined4 *)(pcVar4 + 0x3c);
      }
      pcVar4[0x40] = '\0';
      *pcVar4 = '\x01';
    }
  }
  else {
    pcVar4 = (char *)0x0;
    iVar3 = 0;
    iVar2 = DAT_803adec4 * 0x5c;
    iVar5 = DAT_803adec8;
    if (0 < DAT_803adec8) {
      do {
        pcVar4 = &DAT_803ff2f8 + iVar2;
        if (*pcVar4 == '\0') break;
        iVar2 = iVar2 + 0x5c;
        iVar3 = iVar3 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if (iVar3 == DAT_803adec8) {
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4[1] = '\x01';
      pcVar4[2] = '\0';
      *(int **)(pcVar4 + 4) = param_9;
      pcVar4[8] = '\0';
      pcVar4[9] = '\0';
      pcVar4[10] = '\0';
      pcVar4[0xb] = '\0';
      pcVar4[0xc] = '\0';
      pcVar4[0xd] = '\0';
      pcVar4[0xe] = '\0';
      pcVar4[0xf] = '\0';
      pcVar4[0x10] = '\0';
      pcVar4[0x11] = '\0';
      pcVar4[0x12] = '\0';
      pcVar4[0x13] = '\0';
      pcVar4[0x28] = '\0';
      pcVar4[0x29] = '\0';
      pcVar4[0x2a] = '\x02';
      pcVar4[0x2b] = '\0';
      pcVar4[0x54] = '\0';
      pcVar4[0x55] = '\0';
      pcVar4[0x56] = '\0';
      pcVar4[0x57] = '\0';
      pcVar4[0x58] = '\0';
      pcVar4[0x59] = '\x0f';
      pcVar4[0x5a] = -1;
      pcVar4[0x5b] = -1;
      uVar1 = *(uint *)(pcVar4 + 0x10);
      *(uint *)(pcVar4 + 0x2c) =
           ((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0);
      iVar5 = *(int *)(pcVar4 + 0x10) >> 0x1f;
      if (0 < (int)((iVar5 * 0x800 | (uint)(*(int *)(pcVar4 + 0x10) * 0x200000 + iVar5) >> 0x15) -
                   iVar5)) {
        *(int *)(pcVar4 + 0x2c) = *(int *)(pcVar4 + 0x2c) + 1;
      }
      if (*(int *)(pcVar4 + 4) != 0) {
        zz_026960c_();
        iVar5 = (**(code **)(*param_9 + 0x24))(param_9,1);
        iVar2 = (**(code **)(*param_9 + 0x24))(param_9,0);
        *(int *)(pcVar4 + 0x3c) = iVar2 + iVar5;
        zz_02695d4_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        *(undefined4 *)(pcVar4 + 0x14) = *(undefined4 *)(pcVar4 + 0x3c);
        *(undefined4 *)(pcVar4 + 0x18) = *(undefined4 *)(pcVar4 + 0x3c);
      }
      pcVar4[0x40] = '\0';
      *pcVar4 = '\x01';
    }
  }
  return pcVar4;
}



// ==== 8026e0a8  zz_026e0a8_ ====

void zz_026e0a8_(void)

{
  return;
}



// ==== 8026e0ac  zz_026e0ac_ ====

undefined4 zz_026e0ac_(void)

{
  gnt4_memset(&DAT_803ff2f8,0,0xe60);
  return 1;
}



// ==== 8026e0e0  zz_026e0e0_ ====

void zz_026e0e0_(undefined4 param_1)

{
  SetTRKConnected(param_1);
  return;
}



// ==== 8026e100  zz_026e100_ ====

int zz_026e100_(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  int iVar2;
  size_t __n;
  size_t __n_00;
  int iVar3;
  int aiStack_28 [2];
  void *local_20;
  int local_1c;
  
  piVar1 = *(int **)(param_1 + 0x14);
  if (piVar1 == (int *)0x0) {
    iVar2 = 0;
  }
  else {
    iVar3 = param_2 * 0x12;
    iVar2 = (((int)param_3 >> 5) + (uint)((int)param_3 < 0 && (param_3 & 0x1f) != 0)) * iVar3;
    (**(code **)(*piVar1 + 0x18))(piVar1,0,iVar2,&local_20);
    __n = iVar3 * (local_1c / iVar3);
    gnt4_memset(local_20,0,__n);
    zz_02779cc_((int *)&local_20,__n,(int *)&local_20,aiStack_28);
    (**(code **)(*piVar1 + 0x20))(piVar1,1,&local_20);
    (**(code **)(*piVar1 + 0x1c))(piVar1,0,aiStack_28);
    (**(code **)(*piVar1 + 0x18))(piVar1,0,iVar2 - __n,&local_20);
    __n_00 = iVar3 * (local_1c / iVar3);
    gnt4_memset(local_20,0,__n_00);
    zz_02779cc_((int *)&local_20,__n_00,(int *)&local_20,aiStack_28);
    (**(code **)(*piVar1 + 0x20))(piVar1,1,&local_20);
    (**(code **)(*piVar1 + 0x1c))(piVar1,0,aiStack_28);
    iVar2 = (int)(__n + __n_00) / iVar3 << 5;
  }
  return iVar2;
}



// ==== 8026e280  zz_026e280_ ====

undefined4 zz_026e280_(short *param_1,int param_2,int *param_3)

{
  if (param_2 < 2) {
    return 0;
  }
  if (*param_1 != -0x7fff) {
    return 0;
  }
  *param_3 = param_2;
  return 1;
}



// ==== 8026e2b0  zz_026e2b0_ ====

undefined4 zz_026e2b0_(short *param_1,int param_2,int *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 uStack_20;
  char cStack_1f;
  char cStack_1e;
  undefined1 uStack_1d;
  short local_1c [2];
  int iStack_18;
  uint uStack_14;
  uint auStack_10 [3];
  
  if (param_2 < 2) {
    uVar1 = 0;
  }
  else if (*param_1 == -0x8000) {
    iVar2 = zz_02699b8_(param_1,param_2,local_1c,&uStack_1d,&cStack_1e,&cStack_1f,&uStack_20,
                        auStack_10,&uStack_14,&iStack_18);
    if (iVar2 < 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
      *param_3 = (int)local_1c[0];
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8026e344  zz_026e344_ ====

void zz_026e344_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x88) = param_2;
  return;
}



// ==== 8026e34c  zz_026e34c_ ====

undefined4
zz_026e34c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,void **param_11,int param_12,int param_13,undefined4 param_14,
           undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  char *pcVar4;
  undefined8 uVar5;
  uint local_38;
  uint local_34 [3];
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (*(char *)(param_9 + 0x72) == '\0') {
    uVar1 = 0;
  }
  else {
    uVar1 = zz_02713b4_();
    uVar5 = zz_0271204_();
    if (DAT_8040015c == 0) {
      zz_02711e4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar5 = zz_026960c_();
      DAT_8040015c = 1;
      uVar5 = zz_0264840_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      DAT_8040015c = 2;
      pcVar4 = &DAT_803faa6c;
      iVar2 = 0;
      uVar3 = extraout_r4;
      do {
        if (*pcVar4 == '\x01') {
          uVar5 = zz_026fab8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)pcVar4,uVar3,param_11,param_12,param_13,param_14,param_15,
                              param_16);
          uVar3 = extraout_r4_00;
        }
        iVar2 = iVar2 + 1;
        pcVar4 = pcVar4 + 0xc0;
      } while (iVar2 < 0x10);
      DAT_8040015c = 3;
      uVar5 = zz_0271474_();
      DAT_8040015c = 0;
      uVar5 = zz_02695d4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      uVar5 = zz_02711e4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    uVar3 = DAT_80400158;
    DAT_80400158 = 0;
    zz_026e970_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,local_34,
                &local_38,param_12,param_13,param_14,param_15,param_16);
    uStack_24 = local_34[0] ^ 0x80000000;
    local_28 = 0x43300000;
    uStack_1c = local_38 ^ 0x80000000;
    local_34[2] = DAT_8040018c ^ 0x80000000;
    local_20 = 0x43300000;
    local_34[1] = 0x43300000;
    DAT_80400158 = uVar3;
    iVar2 = gnt4___cvt_fp2unsigned_bl
                      ((double)((float)((double)CONCAT44(0x43300000,local_34[2]) - DAT_802b5cd0) *
                               ((float)((double)CONCAT44(0x43300000,uStack_24) - DAT_802b5cd0) /
                               (float)((double)CONCAT44(0x43300000,uStack_1c) - DAT_802b5cd0))));
    *(int *)(param_9 + 0x9c) = iVar2;
    *(undefined4 *)(param_9 + 0xa0) = DAT_803faa68;
  }
  return uVar1;
}



// ==== 8026e4b0  zz_026e4b0_ ====

void zz_026e4b0_(void)

{
  return;
}



// ==== 8026e4b4  zz_026e4b4_ ====

void zz_026e4b4_(void)

{
  return;
}



// ==== 8026e4b8  zz_026e4b8_ ====

void zz_026e4b8_(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  uint local_38;
  uint local_34 [3];
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a2f8,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    cVar1 = *(char *)(param_9 + 1);
    if (param_10 != *(char *)(param_9 + 0x72)) {
      dVar4 = (double)zz_026960c_();
      *(char *)(param_9 + 0x72) = (char)param_10;
      if ((cVar1 == '\x03') || (cVar1 == '\x04')) {
        if (param_10 == 1) {
          uVar5 = zz_02714d4_(*(int *)(param_9 + 0xc),0);
        }
        else {
          uVar5 = zz_02714d4_(*(int *)(param_9 + 0xc),1);
          *(undefined4 *)(param_9 + 0xa0) = DAT_803faa68;
        }
        uVar2 = DAT_80400158;
        DAT_80400158 = 0;
        zz_026e970_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,local_34,
                    &local_38,&DAT_80400158,param_13,param_14,param_15,param_16);
        uStack_24 = local_34[0] ^ 0x80000000;
        local_28 = 0x43300000;
        uStack_1c = local_38 ^ 0x80000000;
        local_20 = 0x43300000;
        local_34[2] = DAT_8040018c ^ 0x80000000;
        local_34[1] = 0x43300000;
        dVar4 = (double)((float)((double)CONCAT44(0x43300000,local_34[2]) - DAT_802b5cd0) *
                        ((float)((double)CONCAT44(0x43300000,uStack_24) - DAT_802b5cd0) /
                        (float)((double)CONCAT44(0x43300000,uStack_1c) - DAT_802b5cd0)));
        param_2 = DAT_802b5cd0;
        DAT_80400158 = uVar2;
        iVar3 = gnt4___cvt_fp2unsigned_bl(dVar4);
        *(int *)(param_9 + 0x9c) = iVar3;
      }
      zz_02695d4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
  }
  return;
}



// ==== 8026e608  zz_026e608_ ====

int zz_026e608_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a1b4,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = -1;
  }
  else {
    iVar1 = (int)*(short *)(param_9 + 0x60);
  }
  return iVar1;
}



// ==== 8026e644  zz_026e644_ ====

void zz_026e644_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,void **param_11,int param_12,int param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar4 = zz_0271204_();
  if (DAT_8040015c == 0) {
    zz_02711e4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar4 = zz_026960c_();
    DAT_8040015c = 1;
    uVar4 = zz_0264840_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar1 = 0x80400000;
    DAT_8040015c = 2;
    pcVar3 = &DAT_803faa6c;
    iVar2 = 0;
    do {
      if (*pcVar3 == '\x01') {
        uVar4 = zz_026fab8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int)pcVar3,uVar1,param_11,param_12,param_13,param_14,param_15,param_16)
        ;
        uVar1 = extraout_r4;
      }
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 0xc0;
    } while (iVar2 < 0x10);
    DAT_8040015c = 3;
    uVar4 = zz_0271474_();
    DAT_8040015c = 0;
    zz_02695d4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  else {
    zz_02711e4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8026e700  zz_026e700_ ====

void zz_026e700_(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0x6d) = param_2;
  return;
}



// ==== 8026e708  zz_026e708_ ====

void zz_026e708_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49fb0,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    *(undefined4 *)(param_9 + 0x38) = param_10;
  }
  return;
}



// ==== 8026e740  zz_026e740_ ====

int zz_026e740_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49f84,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = 0;
  }
  else {
    iVar1 = (int)*(short *)(param_9 + 0x40);
  }
  return iVar1;
}



// ==== 8026e77c  zz_026e77c_ ====

void zz_026e77c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49f58,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    *(short *)(param_9 + 0x40) = (short)param_10;
    zz_0271414_(*(int *)(param_9 + 0xc),param_10);
  }
  return;
}



// ==== 8026e7bc  zz_026e7bc_ ====

int zz_026e7bc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49f2c,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = 0;
  }
  else {
    iVar1 = (int)*(short *)(param_9 + param_10 * 2 + 0x42);
  }
  return iVar1;
}



// ==== 8026e800  zz_026e800_ ====

void zz_026e800_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49f00,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    iVar1 = param_9 + param_10 * 2;
    *(short *)(iVar1 + 0x42) = (short)param_11;
    if (param_10 < *(char *)(param_9 + 3)) {
      zz_02713f4_(*(int *)(param_9 + 0xc),param_10,param_11);
    }
    else {
      zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49ed4,
                  param_10,param_11,iVar1,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 8026e868  zz_026e868_ ====

undefined4
zz_026e868_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a0c8,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0xffffffff;
  }
  else if (*(char *)(param_9 + 1) < '\x02') {
    uVar1 = 0;
  }
  else {
    uVar1 = zz_02647a0_(*(int *)(param_9 + 4));
  }
  return uVar1;
}



// ==== 8026e8c0  zz_026e8c0_ ====

undefined4
zz_026e8c0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a09c,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0xffffffff;
  }
  else if (*(char *)(param_9 + 1) < '\x02') {
    uVar1 = 0;
  }
  else {
    uVar1 = zz_02647c4_(*(int *)(param_9 + 4));
  }
  return uVar1;
}



// ==== 8026e918  zz_026e918_ ====

undefined4
zz_026e918_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49e50,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0xffffffff;
  }
  else if (*(char *)(param_9 + 1) < '\x02') {
    uVar1 = 0;
  }
  else {
    uVar1 = zz_0264734_(*(int *)(param_9 + 4));
  }
  return uVar1;
}



// ==== 8026e970  zz_026e970_ ====

void zz_026e970_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint *param_10,uint *param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint *puVar7;
  undefined4 uVar8;
  int iVar9;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  double dVar10;
  double dVar11;
  double dVar12;
  undefined8 uVar13;
  uint local_48;
  uint local_44;
  undefined8 local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  uVar8 = 0x802b0000;
  if (((param_9 == 0) || (param_10 == (uint *)0x0)) || (param_11 == (uint *)0x0)) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49e20,param_10
                ,param_11,0x802b0000,param_13,param_14,param_15,param_16);
  }
  else if (DAT_80400158 == 0) {
    cVar1 = *(char *)(param_9 + 1);
    if ((cVar1 == '\x03') || (cVar1 == '\x04')) {
      puVar7 = param_11;
      uVar13 = zz_02647c4_(*(int *)(param_9 + 4));
      uVar6 = (undefined4)uVar13;
      *param_11 = (uint)((ulonglong)uVar13 >> 0x20);
      uVar13 = extraout_f1;
      iVar2 = zz_0264838_(*(int *)(param_9 + 4));
      if (param_9 == 0) {
        zz_026a274_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a070,uVar6
                    ,puVar7,uVar8,param_13,param_14,param_15,param_16);
        iVar9 = -1;
      }
      else {
        piVar3 = *(int **)(param_9 + 0x18);
        if (piVar3 == (int *)0x0) {
          iVar9 = 0;
        }
        else {
          iVar9 = (**(code **)(*piVar3 + 0x24))(piVar3,1);
          iVar9 = iVar9 / 2;
        }
      }
      iVar4 = zz_02714b4_(*(int *)(param_9 + 0xc));
      *param_10 = *(int *)(param_9 + 0xa4) + (iVar2 - (iVar4 + iVar9));
    }
    else if (cVar1 == '\x05') {
      uVar5 = zz_0264734_(*(int *)(param_9 + 4));
      *param_10 = uVar5;
      uVar5 = zz_02647c4_(*(int *)(param_9 + 4));
      *param_11 = uVar5;
      iVar2 = zz_026477c_(*(int *)(param_9 + 4));
      *param_10 = *param_10 * (0x10 / iVar2);
      *param_10 = *param_10 + *(int *)(param_9 + 0xa4);
    }
    else {
      *param_10 = 0;
      *param_11 = 1;
    }
    *param_10 = *param_10 + *(int *)(param_9 + 0x88);
  }
  else {
    DAT_80400188 = DAT_802b5ed4;
    cVar1 = *(char *)(param_9 + 1);
    if ((cVar1 == '\x03') || (cVar1 == '\x04')) {
      if (*(char *)(param_9 + 0x72) == '\0') {
        puVar7 = *(uint **)(param_9 + 0x9c);
        *param_10 = (uint)(puVar7 + (DAT_803faa68 - *(int *)(param_9 + 0xa0)) * 0x19);
      }
      else {
        *param_10 = *(uint *)(param_9 + 0x9c);
        puVar7 = param_11;
      }
      cVar1 = *(char *)(param_9 + 1);
      if ((cVar1 == '\x03') || (cVar1 == '\x04')) {
        uVar13 = zz_02647c4_(*(int *)(param_9 + 4));
        local_48 = (uint)((ulonglong)uVar13 >> 0x20);
        uVar6 = (undefined4)uVar13;
        uVar13 = extraout_f1_00;
        iVar2 = zz_0264838_(*(int *)(param_9 + 4));
        if (param_9 == 0) {
          zz_026a274_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a070,
                      uVar6,puVar7,uVar8,param_13,param_14,param_15,param_16);
          iVar9 = -1;
        }
        else {
          piVar3 = *(int **)(param_9 + 0x18);
          if (piVar3 == (int *)0x0) {
            iVar9 = 0;
          }
          else {
            iVar9 = (**(code **)(*piVar3 + 0x24))(piVar3,1);
            iVar9 = iVar9 / 2;
          }
        }
        iVar4 = zz_02714b4_(*(int *)(param_9 + 0xc));
        local_44 = *(int *)(param_9 + 0xa4) + (iVar2 - (iVar4 + iVar9));
      }
      else if (cVar1 == '\x05') {
        local_44 = zz_0264734_(*(int *)(param_9 + 4));
        local_48 = zz_02647c4_(*(int *)(param_9 + 4));
        iVar2 = zz_026477c_(*(int *)(param_9 + 4));
        local_44 = local_44 * (0x10 / iVar2) + *(int *)(param_9 + 0xa4);
      }
      else {
        local_44 = 0;
        local_48 = 1;
      }
      iVar2 = DAT_80400158;
      local_44 = local_44 + *(int *)(param_9 + 0x88);
      uStack_34 = local_48 ^ 0x80000000;
      uStack_24 = DAT_8040018c ^ 0x80000000;
      uStack_2c = *param_10 ^ 0x80000000;
      local_40 = (double)CONCAT44(0x43300000,local_44 ^ 0x80000000);
      local_38 = 0x43300000;
      local_30 = 0x43300000;
      dVar12 = (double)((float)(local_40 - DAT_802b5cd0) /
                       (float)((double)CONCAT44(0x43300000,uStack_34) - DAT_802b5cd0));
      local_28 = 0x43300000;
      dVar11 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DAT_802b5cd0);
      DAT_80400188 = (float)((double)DAT_802b6208 *
                            (double)(float)(dVar12 - (double)(float)(dVar11 / (double)(float)((
                                                  double)CONCAT44(0x43300000,uStack_24) -
                                                  DAT_802b5cd0))));
      dVar10 = (double)DAT_80400188;
      if (((double)DAT_802b620c < dVar10) || (dVar10 < (double)DAT_802b6210)) {
        if (DAT_803aded0 == 1) {
          DAT_80400158 = 0;
          zz_026e970_(dVar10,dVar11,dVar12,DAT_802b5cd0,(double)DAT_802b6208,param_6,param_7,param_8
                      ,param_9,&local_44,&local_48,local_44 ^ 0x80000000,param_13,param_14,param_15,
                      param_16);
          DAT_80400160 = DAT_80400160 + 1;
        }
        uStack_2c = local_44 ^ 0x80000000;
        uStack_34 = local_48 ^ 0x80000000;
        uStack_24 = DAT_8040018c ^ 0x80000000;
        local_30 = 0x43300000;
        local_38 = 0x43300000;
        local_28 = 0x43300000;
        DAT_80400158 = iVar2;
        iVar2 = gnt4___cvt_fp2unsigned_bl
                          ((double)((float)((double)CONCAT44(0x43300000,uStack_24) - DAT_802b5cd0) *
                                   ((float)((double)CONCAT44(0x43300000,uStack_2c) - DAT_802b5cd0) /
                                   (float)((double)CONCAT44(0x43300000,uStack_34) - DAT_802b5cd0))))
        ;
        *(int *)(param_9 + 0x9c) = iVar2;
        *(int *)(param_9 + 0xa0) = DAT_803faa68;
      }
    }
    else if (cVar1 == '\x05') {
      local_44 = zz_0264734_(*(int *)(param_9 + 4));
      local_48 = zz_02647c4_(*(int *)(param_9 + 4));
      iVar2 = zz_026477c_(*(int *)(param_9 + 4));
      *param_10 = (int)((float)((double)CONCAT44(0x43300000,DAT_8040018c ^ 0x80000000) -
                               DAT_802b5cd0) *
                       ((float)((double)CONCAT44(0x43300000,local_44 * (0x10 / iVar2) ^ 0x80000000)
                               - DAT_802b5cd0) /
                       (float)((double)CONCAT44(0x43300000,local_48 ^ 0x80000000) - DAT_802b5cd0)));
      *param_10 = *(int *)(param_9 + 0x9c) + *param_10 + 1;
    }
    else {
      *param_10 = 0;
    }
    *param_10 = *param_10 + *(int *)(param_9 + 0x88);
    *param_11 = DAT_8040018c;
  }
  return;
}



// ==== 8026ee64  zz_026ee64_ ====

int zz_026ee64_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4a0f0,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = -1;
  }
  else {
    iVar1 = (int)*(char *)(param_9 + 1);
  }
  return iVar1;
}



// ==== 8026eea4  zz_026eea4_ ====

void zz_026eea4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49dec,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    if (DAT_8040017c != (code *)0x0) {
      zz_0264f8c_(*(int *)(param_9 + 4));
      param_1 = (*DAT_8040017c)(param_9);
    }
    if (*(int *)(param_9 + 8) != 0) {
      zz_026d9ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 8));
    }
    uVar1 = zz_026960c_();
    if (*(char *)(param_9 + 2) == '\x04') {
      zz_0275d68_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x94),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                  param_16);
      if (*(int **)(param_9 + 0x14) != (int *)0x0) {
        (**(code **)(**(int **)(param_9 + 0x14) + 0x14))();
      }
    }
    zz_026960c_();
    zz_02714f4_(*(int *)(param_9 + 0xc),0);
    zz_02714d4_(*(int *)(param_9 + 0xc),0);
    uVar1 = zz_0264f8c_(*(int *)(param_9 + 4));
    if ((*(char *)(param_9 + 2) == '\x02') && (*(int **)(param_9 + 0x14) != (int *)0x0)) {
      uVar1 = (**(code **)(**(int **)(param_9 + 0x14) + 0xc))();
    }
    if (*(int *)(param_9 + 0x74) != 0) {
      uVar1 = zz_02693cc_(*(int *)(param_9 + 0x74));
    }
    *(undefined4 *)(param_9 + 0x14) = 0;
    *(undefined1 *)(param_9 + 1) = 0;
    *(undefined1 *)(param_9 + 0xa8) = 0;
    uVar1 = zz_02695d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    zz_02695d4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8026efc4  zz_026efc4_ ====

void zz_026efc4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  if ((param_9 == 0) || (param_10 == 0)) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49dc4,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    if (param_9 == 0) {
      zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49dec,
                  param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    }
    else {
      if (DAT_8040017c != (code *)0x0) {
        zz_0264f8c_(*(int *)(param_9 + 4));
        param_1 = (*DAT_8040017c)(param_9);
      }
      if (*(int *)(param_9 + 8) != 0) {
        zz_026d9ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 8));
      }
      uVar3 = zz_026960c_();
      if (*(char *)(param_9 + 2) == '\x04') {
        zz_0275d68_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x94),extraout_r4,param_11,param_12,param_13,param_14,
                    param_15,param_16);
        if (*(int **)(param_9 + 0x14) != (int *)0x0) {
          (**(code **)(**(int **)(param_9 + 0x14) + 0x14))();
        }
      }
      zz_026960c_();
      zz_02714f4_(*(int *)(param_9 + 0xc),0);
      zz_02714d4_(*(int *)(param_9 + 0xc),0);
      uVar3 = zz_0264f8c_(*(int *)(param_9 + 4));
      if ((*(char *)(param_9 + 2) == '\x02') && (*(int **)(param_9 + 0x14) != (int *)0x0)) {
        uVar3 = (**(code **)(**(int **)(param_9 + 0x14) + 0xc))();
      }
      if (*(int *)(param_9 + 0x74) != 0) {
        uVar3 = zz_02693cc_(*(int *)(param_9 + 0x74));
      }
      *(undefined4 *)(param_9 + 0x14) = 0;
      *(undefined1 *)(param_9 + 1) = 0;
      *(undefined1 *)(param_9 + 0xa8) = 0;
      uVar3 = zz_02695d4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_02695d4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    zz_026960c_();
    iVar1 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 3); iVar2 = iVar2 + 1) {
      (**(code **)(**(int **)(iVar1 + 0x18) + 0x14))();
      iVar1 = iVar1 + 4;
    }
    zz_0265074_(*(int *)(param_9 + 4),param_10);
    *(int *)(param_9 + 0x14) = param_10;
    uVar3 = zz_0264fc4_(*(int *)(param_9 + 4));
    *(undefined1 *)(param_9 + 1) = 1;
    *(undefined4 *)(param_9 + 0x4c) = 0;
    *(undefined1 *)(param_9 + 0x71) = 0;
    *(undefined4 *)(param_9 + 0x8c) = 0x7fffffff;
    *(undefined4 *)(param_9 + 0x90) = 0xffffffff;
    *(undefined4 *)(param_9 + 0x9c) = 0;
    *(undefined4 *)(param_9 + 0xa4) = 0;
    *(undefined4 *)(param_9 + 0xa0) = DAT_803faa68;
    if (*(int *)(param_9 + 0x74) != 0) {
      uVar3 = zz_02693d8_(*(int *)(param_9 + 0x74));
    }
    *(undefined1 *)(param_9 + 2) = 3;
    *(undefined1 *)(param_9 + 0x98) = 1;
    zz_02695d4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8026f1d4  zz_026f1d4_ ====

void zz_026f1d4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                )

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined8 uVar4;
  
  zz_026cecc_(*(int *)(param_9 + 8),(int)*(short *)(param_9 + 0x3e) << 0xb,
              (int)*(short *)(param_9 + 0x3c) << 0xb);
  zz_026d510_(*(int *)(param_9 + 8),0x19);
  uVar4 = zz_026d558_(*(int *)(param_9 + 8),0,0);
  zz_026d78c_(*(int *)(param_9 + 8),0);
  uVar4 = zz_026d658_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 8));
  uVar4 = zz_026d9ac_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 8));
  zz_026dafc_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 8),
              param_10,param_11,param_12,param_13);
  zz_026d718_(*(int *)(param_9 + 8));
  uVar2 = *(undefined4 *)(param_9 + 0x10);
  iVar1 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 3); iVar3 = iVar3 + 1) {
    (**(code **)(**(int **)(iVar1 + 0x18) + 0x14))();
    iVar1 = iVar1 + 4;
  }
  zz_0265074_(*(int *)(param_9 + 4),uVar2);
  *(undefined4 *)(param_9 + 0x14) = uVar2;
  zz_0264fc4_(*(int *)(param_9 + 4));
  *(undefined1 *)(param_9 + 1) = 1;
  *(undefined4 *)(param_9 + 0x4c) = 0;
  *(undefined1 *)(param_9 + 0x71) = 0;
  *(undefined4 *)(param_9 + 0x8c) = 0x7fffffff;
  *(undefined4 *)(param_9 + 0x90) = 0xffffffff;
  *(undefined4 *)(param_9 + 0x9c) = 0;
  *(undefined4 *)(param_9 + 0xa4) = 0;
  *(undefined4 *)(param_9 + 0xa0) = DAT_803faa68;
  if (*(int *)(param_9 + 0x74) != 0) {
    zz_02693d8_(*(int *)(param_9 + 0x74));
  }
  return;
}



// ==== 8026f31c  zz_026f31c_ ====

void zz_026f31c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                char *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar1 = 0x80400000;
  if (param_9 == (char *)0x0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49d9c,
                0x80400000,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    if (DAT_80400184 != (code *)0x0) {
      param_1 = (*DAT_80400184)();
      uVar1 = extraout_r4;
    }
    if (DAT_80400180 != (code *)0x0) {
      param_1 = (*DAT_80400180)(param_9);
      uVar1 = extraout_r4_00;
    }
    if (*param_9 == '\x01') {
      if (param_9 == (char *)0x0) {
        param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              -0x7fd49dec,uVar1,param_11,param_12,param_13,param_14,param_15,
                              param_16);
        uVar1 = extraout_r4_01;
      }
      else {
        if (DAT_8040017c != (code *)0x0) {
          zz_0264f8c_(*(int *)(param_9 + 4));
          param_1 = (*DAT_8040017c)(param_9);
        }
        if (*(int *)(param_9 + 8) != 0) {
          zz_026d9ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 8));
        }
        uVar4 = zz_026960c_();
        if (param_9[2] == '\x04') {
          zz_0275d68_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x94),extraout_r4_02,param_11,param_12,param_13,param_14,
                      param_15,param_16);
          if (*(int **)(param_9 + 0x14) != (int *)0x0) {
            (**(code **)(**(int **)(param_9 + 0x14) + 0x14))();
          }
        }
        zz_026960c_();
        zz_02714f4_(*(int *)(param_9 + 0xc),0);
        zz_02714d4_(*(int *)(param_9 + 0xc),0);
        uVar4 = zz_0264f8c_(*(int *)(param_9 + 4));
        if ((param_9[2] == '\x02') && (*(int **)(param_9 + 0x14) != (int *)0x0)) {
          uVar4 = (**(code **)(**(int **)(param_9 + 0x14) + 0xc))();
        }
        if (*(int *)(param_9 + 0x74) != 0) {
          uVar4 = zz_02693cc_(*(int *)(param_9 + 0x74));
        }
        param_9[0x14] = '\0';
        param_9[0x15] = '\0';
        param_9[0x16] = '\0';
        param_9[0x17] = '\0';
        param_9[1] = '\0';
        param_9[0xa8] = '\0';
        uVar4 = zz_02695d4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        param_1 = zz_02695d4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        uVar1 = extraout_r4_03;
      }
    }
    if (*(void **)(param_9 + 0xc) != (void *)0x0) {
      param_1 = zz_0271514_(*(void **)(param_9 + 0xc));
      uVar1 = extraout_r4_04;
    }
    if (*(void **)(param_9 + 4) != (void *)0x0) {
      param_1 = zz_02650cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(void **)(param_9 + 4));
      uVar1 = extraout_r4_05;
    }
    if (*(undefined1 **)(param_9 + 8) != (undefined1 *)0x0) {
      param_1 = zz_026db58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(undefined1 **)(param_9 + 8),uVar1,param_11,param_12,param_13,param_14,
                            param_15,param_16);
      uVar1 = extraout_r4_06;
    }
    if (*(undefined1 **)(param_9 + 0x94) != (undefined1 *)0x0) {
      zz_02761ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(undefined1 **)(param_9 + 0x94),uVar1,param_11,param_12,param_13,param_14,
                  param_15,param_16);
    }
    uVar4 = zz_026960c_();
    if (*(int **)(param_9 + 0x10) != (int *)0x0) {
      uVar4 = (**(code **)(**(int **)(param_9 + 0x10) + 0xc))();
    }
    pcVar3 = param_9;
    for (iVar2 = 0; iVar2 < param_9[3]; iVar2 = iVar2 + 1) {
      if (*(int **)(pcVar3 + 0x18) != (int *)0x0) {
        uVar4 = (**(code **)(**(int **)(pcVar3 + 0x18) + 0xc))();
      }
      if (*(int **)(pcVar3 + 0x78) != (int *)0x0) {
        uVar4 = (**(code **)(**(int **)(pcVar3 + 0x78) + 0xc))();
      }
      if (*(int **)(pcVar3 + 0x80) != (int *)0x0) {
        uVar4 = (**(code **)(**(int **)(pcVar3 + 0x80) + 0xc))();
      }
      pcVar3 = pcVar3 + 4;
    }
    if (*(void **)(param_9 + 0x74) != (void *)0x0) {
      uVar4 = zz_0269590_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(void **)(param_9 + 0x74));
    }
    gnt4_memset(param_9,0,0xc0);
    *param_9 = '\0';
    zz_02695d4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8026f5a0  zz_026f5a0_ ====

char * zz_026f5a0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                  undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  float fVar2;
  char *pcVar3;
  undefined4 *puVar4;
  char *pcVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  undefined8 extraout_f1;
  undefined8 uVar18;
  
  uVar14 = param_10 + 0x3fU & 0xffffffc0;
  if (((param_9 < 0) || (param_10 == 0)) || (param_11 < 0)) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49d74,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    pcVar3 = (char *)0x0;
  }
  else {
    pcVar3 = &DAT_803faa6c;
    iVar7 = 0;
    iVar17 = 2;
    do {
      iVar9 = iVar7;
      if (((((*pcVar3 == '\0') || (iVar9 = iVar7 + 1, pcVar3[0xc0] == '\0')) ||
           ((iVar9 = iVar7 + 2, pcVar3[0x180] == '\0' ||
            ((iVar9 = iVar7 + 3, pcVar3[0x240] == '\0' || (iVar9 = iVar7 + 4, pcVar3[0x300] == '\0')
             ))))) || (iVar9 = iVar7 + 5, pcVar3[0x3c0] == '\0')) ||
         ((iVar9 = iVar7 + 6, pcVar3[0x480] == '\0' || (iVar9 = iVar7 + 7, pcVar3[0x540] == '\0'))))
      break;
      pcVar3 = pcVar3 + 0x600;
      iVar7 = iVar7 + 8;
      iVar17 = iVar17 + -1;
      iVar9 = iVar7;
    } while (iVar17 != 0);
    if (iVar9 == 0x10) {
      pcVar3 = (char *)0x0;
    }
    else {
      iVar9 = iVar9 * 0xc0;
      pcVar3 = &DAT_803faa6c + iVar9;
      gnt4_memset(pcVar3,0,0xc0);
      *(char *)(iVar9 + -0x7fc05591) = (char)param_9;
      uVar15 = ((param_11 - (uVar14 - param_10)) + param_9 * -0x60c0) - 0x124;
      *(uint *)(iVar9 + -0x7fc05574) = uVar14 + param_9 * 0x60c0;
      *(uint *)(iVar9 + -0x7fc05570) =
           (((int)uVar15 >> 0xb) + (uint)((int)uVar15 < 0 && (uVar15 & 0x7ff) != 0)) * 0x800;
      *(undefined4 *)(iVar9 + -0x7fc0556c) = 0x24;
      iVar17 = *(int *)(iVar9 + -0x7fc05574);
      iVar7 = *(int *)(iVar9 + -0x7fc05570);
      *(int *)(iVar9 + -0x7fc054e8) = iVar7 + *(int *)(iVar9 + -0x7fc0556c) + iVar17;
      *(uint *)(iVar9 + -0x7fc05568) = uVar14;
      *(undefined4 *)(iVar9 + -0x7fc05564) = 0x2000;
      *(undefined4 *)(iVar9 + -0x7fc05560) = 0x2060;
      *(undefined4 *)(iVar9 + -0x7fc05580) = 0;
      uVar8 = *(undefined4 *)(iVar9 + -0x7fc05570);
      uVar10 = *(undefined4 *)(iVar9 + -0x7fc0556c);
      puVar4 = zz_02774e0_(*(undefined4 *)(iVar9 + -0x7fc05574),uVar8,uVar10);
      *(undefined4 **)(iVar9 + -0x7fc05584) = puVar4;
      if (*(int **)(iVar9 + -0x7fc05584) == (int *)0x0) {
        zz_026f31c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,uVar8,
                    uVar10,iVar7,iVar17,param_14,param_15,param_16);
        pcVar3 = (char *)0x0;
      }
      else {
        uVar8 = 0;
        pcVar5 = zz_026ddec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int **)(iVar9 + -0x7fc05584),0);
        *(char **)(iVar9 + -0x7fc0558c) = pcVar5;
        if (pcVar5 == (char *)0x0) {
          zz_026f31c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,uVar8,
                      uVar10,iVar7,iVar17,param_14,param_15,param_16);
          pcVar3 = (char *)0x0;
        }
        else {
          pcVar5 = pcVar3;
          for (iVar16 = 0; iVar16 < param_9; iVar16 = iVar16 + 1) {
            iVar7 = *(int *)(iVar9 + -0x7fc05568);
            iVar13 = *(int *)(iVar9 + -0x7fc05564) << 1;
            iVar11 = (*(int *)(iVar9 + -0x7fc05560) - *(int *)(iVar9 + -0x7fc05564)) * 2;
            puVar4 = zz_02774e0_(iVar7 + *(int *)(iVar9 + -0x7fc05560) * iVar16 * 2,iVar13,iVar11);
            *(undefined4 **)(pcVar5 + 0x18) = puVar4;
            if (*(int *)(pcVar5 + 0x18) == 0) {
              zz_026f31c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,
                          iVar13,iVar11,iVar7,iVar17,param_14,param_15,param_16);
              return (char *)0x0;
            }
            pcVar5 = pcVar5 + 4;
          }
          piVar12 = (int *)(iVar9 + -0x7fc0557c);
          iVar16 = param_9;
          puVar6 = zz_0265120_(*(undefined4 *)(iVar9 + -0x7fc05584),param_9,piVar12);
          *(undefined1 **)(iVar9 + -0x7fc05590) = puVar6;
          if (puVar6 == (undefined1 *)0x0) {
            zz_026f31c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,
                        iVar16,piVar12,iVar7,iVar17,param_14,param_15,param_16);
            pcVar3 = (char *)0x0;
          }
          else {
            iVar13 = uVar14 + param_9 * 0x40c0;
            uVar18 = zz_0271558_((int *)(iVar9 + -0x7fc0557c),param_9);
            iVar16 = (int)((ulonglong)uVar18 >> 0x20);
            uVar8 = (undefined4)uVar18;
            *(int *)(iVar9 + -0x7fc05588) = iVar16;
            if (iVar16 == 0) {
              zz_026f31c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3
                          ,uVar8,iVar13,iVar7,iVar17,param_14,param_15,param_16);
              pcVar3 = (char *)0x0;
            }
            else {
              uVar18 = extraout_f1;
              pcVar5 = zz_0276284_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,
                                   param_8,*(int **)(iVar9 + -0x7fc05584),uVar8,iVar13,iVar7,iVar17,
                                   param_14,param_15,param_16);
              *(char **)(iVar9 + -0x7fc05500) = pcVar5;
              if (pcVar5 == (char *)0x0) {
                zz_026f31c_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,
                            uVar8,iVar13,iVar7,iVar17,param_14,param_15,param_16);
                pcVar3 = (char *)0x0;
              }
              else {
                zz_02761a4_(*(int *)(iVar9 + -0x7fc05500),*(undefined4 *)(iVar9 + -0x7fc0558c));
                *(undefined4 *)(iVar9 + -0x7fc0555c) = 0x3c;
                fVar2 = DAT_802b62b4;
                dVar1 = DAT_802b5cd0;
                uVar14 = *(uint *)(iVar9 + -0x7fc05570);
                iVar7 = 0;
                *(ushort *)(iVar9 + -0x7fc05558) =
                     (short)((int)uVar14 >> 0xb) +
                     (ushort)((int)uVar14 < 0 && (uVar14 & 0x7ff) != 0);
                *(short *)(iVar9 + -0x7fc05556) =
                     (short)(int)(fVar2 * (float)((double)CONCAT44(0x43300000,
                                                                   (int)*(short *)(iVar9 + 
                                                  -0x7fc05558) ^ 0x80000000) - dVar1));
                *(undefined2 *)(iVar9 + -0x7fc05554) = 0;
                if (0 < param_9) {
                  if ((8 < param_9) &&
                     (uVar14 = param_9 - 1U >> 3, pcVar5 = pcVar3, 0 < param_9 + -8)) {
                    do {
                      pcVar5[0x42] = -1;
                      pcVar5[0x43] = -0x80;
                      iVar7 = iVar7 + 8;
                      pcVar5[0x44] = -1;
                      pcVar5[0x45] = -0x80;
                      pcVar5[0x46] = -1;
                      pcVar5[0x47] = -0x80;
                      pcVar5[0x48] = -1;
                      pcVar5[0x49] = -0x80;
                      pcVar5[0x4a] = -1;
                      pcVar5[0x4b] = -0x80;
                      pcVar5[0x4c] = -1;
                      pcVar5[0x4d] = -0x80;
                      pcVar5[0x4e] = -1;
                      pcVar5[0x4f] = -0x80;
                      pcVar5[0x50] = -1;
                      pcVar5[0x51] = -0x80;
                      pcVar5 = pcVar5 + 0x10;
                      uVar14 = uVar14 - 1;
                    } while (uVar14 != 0);
                  }
                  iVar17 = param_9 - iVar7;
                  pcVar5 = pcVar3 + iVar7 * 2;
                  if (iVar7 < param_9) {
                    do {
                      pcVar5[0x42] = -1;
                      pcVar5[0x43] = -0x80;
                      pcVar5 = pcVar5 + 2;
                      iVar17 = iVar17 + -1;
                    } while (iVar17 != 0);
                  }
                }
                *(undefined1 *)(iVar9 + -0x7fc05528) = 1;
                *(undefined4 *)(iVar9 + -0x7fc05540) = 0;
                *(undefined4 *)(iVar9 + -0x7fc0553c) = 0;
                *(undefined4 *)(iVar9 + -0x7fc05538) = 0;
                *(undefined2 *)(iVar9 + -0x7fc05534) = 0;
                *(undefined4 *)(iVar9 + -0x7fc05530) = 0;
                *(undefined2 *)(iVar9 + -0x7fc0552c) = 0;
                *(undefined2 *)(iVar9 + -0x7fc0552a) = 0;
                *(undefined1 *)(iVar9 + -0x7fc05527) = 1;
                *(undefined1 *)(iVar9 + -0x7fc05522) = 0;
                *(undefined4 *)(iVar9 + -0x7fc0550c) = 0;
                *(undefined1 *)(iVar9 + -0x7fc054fc) = 0;
                *pcVar3 = '\x01';
              }
            }
          }
        }
      }
    }
  }
  return pcVar3;
}



// ==== 8026f9b8  zz_026f9b8_ ====

void zz_026f9b8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  int *piVar4;
  uint *puVar5;
  undefined8 uVar6;
  undefined4 local_38;
  uint local_34;
  int local_30;
  char acStack_2c [32];
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49d48,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    uVar6 = zz_026eea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    piVar4 = &local_30;
    puVar5 = &local_34;
    iVar1 = zz_0272048_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        param_11,-0x7fbffe60,&local_38,piVar4,puVar5,param_15,param_16);
    if (iVar1 == 0) {
      if (*(int *)(param_9 + 8) == 0) {
        pcVar2 = acStack_2c;
        uVar3 = 0x10;
        uVar6 = zz_0269d18_(param_10,param_11,pcVar2,0x10);
        zz_026a1f4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49d1c,
                    (int)acStack_2c,pcVar2,uVar3,piVar4,puVar5,param_15,param_16);
        *(undefined2 *)(param_9 + 0x60) = 0xffff;
        *(undefined1 *)(param_9 + 1) = 6;
      }
      else {
        *(undefined **)(param_9 + 0xb0) = &DAT_804001a0;
        *(undefined4 *)(param_9 + 0xb4) = local_38;
        *(int *)(param_9 + 0xb8) = local_30;
        *(uint *)(param_9 + 0xbc) = local_34;
        *(undefined1 *)(param_9 + 1) = 1;
        *(undefined1 *)(param_9 + 0xa8) = 1;
        *(undefined1 *)(param_9 + 2) = 1;
        *(undefined1 *)(param_9 + 0x98) = 0;
      }
    }
  }
  return;
}



// ==== 8026fab8  zz_026fab8_ ====

void zz_026fab8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,void **param_11,int param_12,int param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  void *local_28;
  size_t local_24;
  
  uVar3 = 0x80400000;
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49cf8,
                0x80400000,param_11,param_12,param_13,param_14,param_15,param_16);
    return;
  }
  cVar1 = *(char *)(param_9 + 1);
  if (cVar1 == '\x03') {
    iVar2 = zz_02650c0_(*(int *)(param_9 + 4));
    if (iVar2 == 3) {
      uVar8 = zz_02647a0_(*(int *)(param_9 + 4));
      iVar4 = (int)((ulonglong)uVar8 >> 0x20);
      iVar2 = param_9;
      param_1 = extraout_f1;
      for (iVar6 = 0; DAT_804002a8 = (undefined4)((ulonglong)uVar8 >> 0x20), iVar6 < iVar4;
          iVar6 = iVar6 + 1) {
        param_11 = (void **)**(undefined4 **)(iVar2 + 0x18);
        lVar9 = (*param_11[9])(*(undefined4 **)(iVar2 + 0x18),1);
        DAT_804002a4 = (undefined4)((ulonglong)lVar9 >> 0x20);
        uVar8 = CONCAT44(DAT_804002a8,(int)lVar9);
        param_1 = extraout_f1_00;
        if (0x3fffffffff < lVar9) break;
        iVar2 = iVar2 + 4;
      }
      DAT_804002a8 = (undefined4)((ulonglong)uVar8 >> 0x20);
      uVar3 = (undefined4)uVar8;
      if (iVar6 == iVar4) {
        param_1 = zz_02714f4_(*(int *)(param_9 + 0xc),0);
        *(undefined1 *)(param_9 + 1) = 4;
        uVar3 = extraout_r4;
      }
    }
    goto LAB_8026fcf8;
  }
  if (cVar1 == '\x01') {
    param_1 = zz_026fdc0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    uVar3 = extraout_r4_00;
    goto LAB_8026fcf8;
  }
  if (cVar1 != '\x02') {
    if (cVar1 == '\x04') {
      DAT_804002a0 = zz_02714b4_(*(int *)(param_9 + 0xc));
      lVar9 = zz_02714b4_(*(int *)(param_9 + 0xc));
      uVar3 = (undefined4)lVar9;
      param_1 = extraout_f1_03;
      if (lVar9 < 0x100000000) {
        param_1 = zz_02714d4_(*(int *)(param_9 + 0xc),0);
        *(undefined1 *)(param_9 + 1) = 5;
        uVar3 = extraout_r4_03;
      }
    }
    goto LAB_8026fcf8;
  }
  iVar6 = *(int *)(param_9 + 0xc);
  iVar4 = *(int *)(param_9 + 4);
  iVar2 = zz_02714b4_(iVar6);
  uVar8 = zz_0271494_(iVar6);
  uVar3 = (undefined4)uVar8;
  param_1 = extraout_f1_01;
  if (iVar2 < *(int *)(param_9 + 0x48) << 1) {
    uVar10 = zz_0264758_(iVar4);
    uVar3 = (undefined4)uVar10;
    param_1 = extraout_f1_02;
    if (((int)((ulonglong)uVar8 >> 0x20) <= (int)((ulonglong)uVar10 >> 0x20)) ||
       (iVar2 = zz_02650c0_(*(int *)(param_9 + 4)), iVar2 == 3)) goto LAB_8026fbe0;
  }
  else {
LAB_8026fbe0:
    if (*(char *)(param_9 + 0x70) == '\0') {
      if (*(char *)(param_9 + 0x72) == '\0') {
        param_1 = zz_02714d4_(iVar6,1);
        *(undefined4 *)(param_9 + 0x9c) = 0;
        *(undefined4 *)(param_9 + 0xa0) = DAT_803faa68;
        uVar3 = extraout_r4_01;
      }
      *(undefined1 *)(param_9 + 1) = 3;
    }
    *(undefined1 *)(param_9 + 0x71) = 1;
  }
  iVar2 = zz_02650c0_(*(int *)(param_9 + 4));
  if (iVar2 == 3) {
    iVar6 = zz_026e868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar4 = *(int *)(param_9 + 0x48);
    iVar2 = param_9;
    for (iVar5 = 0; iVar5 < iVar6; iVar5 = iVar5 + 1) {
      piVar7 = *(int **)(iVar2 + 0x18);
      param_13 = *piVar7;
      (**(code **)(param_13 + 0x18))(piVar7,0,iVar4 * iVar6 * 2,&local_28);
      gnt4_memset(local_28,0,local_24);
      param_12 = *piVar7;
      param_11 = &local_28;
      param_1 = (**(code **)(param_12 + 0x20))(piVar7,1);
      iVar2 = iVar2 + 4;
      uVar3 = extraout_r4_02;
    }
  }
LAB_8026fcf8:
  if ((*(int *)(param_9 + 8) != 0) &&
     (iVar2 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          uVar3,param_11,param_12,param_13,param_14,param_15,param_16), iVar2 != 0))
  {
    cVar1 = *(char *)(param_9 + 2);
    if (cVar1 == '\x02') {
      param_1 = zz_0265004_(*(int *)(param_9 + 4));
      uVar3 = extraout_r4_05;
    }
    else if (((cVar1 < '\x02') && (-1 < cVar1)) &&
            (iVar2 = zz_026d7dc_(*(int *)(param_9 + 8)), iVar2 == 3)) {
      param_1 = zz_0265004_(*(int *)(param_9 + 4));
      uVar3 = extraout_r4_04;
    }
  }
  if ((*(int *)(param_9 + 8) != 0) && (iVar2 = zz_026d7dc_(*(int *)(param_9 + 8)), iVar2 == 4)) {
    *(undefined2 *)(param_9 + 0x60) = 0xffff;
    *(undefined1 *)(param_9 + 1) = 6;
  }
  if ((*(int *)(param_9 + 0x94) != 0) &&
     (iVar2 = zz_0275cb8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x94),uVar3,param_11,param_12,param_13,param_14,
                          param_15,param_16), iVar2 == 3)) {
    *(undefined2 *)(param_9 + 0x60) = 0xffff;
    *(undefined1 *)(param_9 + 1) = 6;
  }
  return;
}



// ==== 8026fdc0  zz_026fdc0_ ====

/* WARNING: Removing unreachable block (ram,0x802700e8) */

void zz_026fdc0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  undefined4 extraout_r4;
  char *pcVar5;
  undefined4 uVar6;
  int in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  char acStack_40 [44];
  
  iVar7 = *(int *)(param_9 + 4);
  if (((*(char *)(param_9 + 2) == '\0') || (*(char *)(param_9 + 2) == '\x01')) &&
     (*(char *)(param_9 + 0xa8) == '\x01')) {
    iVar1 = zz_026d7dc_(*(int *)(param_9 + 8));
    if (iVar1 == 2) {
      return;
    }
    if (*(int **)(param_9 + 0x10) != (int *)0x0) {
      param_1 = (**(code **)(**(int **)(param_9 + 0x10) + 0x14))();
    }
    in_r7 = *(int *)(param_9 + 0xbc);
    zz_026f1d4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                *(undefined4 *)(param_9 + 0xb0),*(undefined4 *)(param_9 + 0xb4),
                *(undefined4 *)(param_9 + 0xb8),in_r7);
    *(undefined1 *)(param_9 + 0xa8) = 0;
  }
  iVar1 = zz_02650c0_(iVar7);
  if (iVar1 == 2) {
    iVar1 = zz_02647a0_(iVar7);
    if (*(char *)(param_9 + 3) < iVar1) {
      pcVar5 = acStack_40;
      uVar6 = 0x10;
      uVar8 = zz_0269d18_(iVar1,(int)*(char *)(param_9 + 3),pcVar5,0x10);
      uVar8 = zz_026a1f4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49ccc,
                          (int)acStack_40,pcVar5,uVar6,in_r7,in_r8,in_r9,in_r10);
      zz_026eea4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                  pcVar5,uVar6,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      iVar1 = zz_02647c4_(iVar7);
      iVar2 = zz_0264710_(iVar7);
      if (iVar2 < 1) {
        *(int *)(param_9 + 0x48) = ((iVar1 / *(int *)(param_9 + 0x38)) * 3) / 2;
      }
      else {
        *(int *)(param_9 + 0x48) = (iVar1 / *(int *)(param_9 + 0x38)) * 3;
      }
      iVar1 = zz_0264758_(iVar7);
      iVar1 = iVar1 * 2;
      *(int *)(param_9 + 0x48) = iVar1 * ((*(int *)(param_9 + 0x48) + iVar1) / iVar1);
      zz_0265028_(iVar7,*(int *)(param_9 + 0x48));
      if (iVar2 < 1) {
        if (*(int *)(param_9 + 8) != 0) {
          zz_026d510_(*(int *)(param_9 + 8),0x7fffffff);
        }
        uVar6 = zz_0264734_(iVar7);
        zz_026481c_(iVar7,uVar6);
        zz_026480c_(iVar7,0);
        zz_0264814_(iVar7,0);
        zz_0264824_(iVar7,FUN_802701f4,param_9);
      }
      else {
        if (*(char *)(param_9 + 2) == '\x02') {
          *(undefined4 *)(param_9 + 0x50) = 0;
        }
        else {
          iVar2 = zz_0264680_(iVar7);
          iVar1 = iVar2 >> 0x1f;
          uVar3 = iVar2 + 0x7ff;
          *(uint *)(param_9 + 0x50) =
               0x800 - ((iVar1 * 0x800 | (uint)(iVar2 * 0x200000 + iVar1) >> 0x15) - iVar1);
          iVar2 = ((int)uVar3 >> 0xb) + (uint)((int)uVar3 < 0 && (uVar3 & 0x7ff) != 0);
          iVar1 = *(int *)(param_9 + 0x50) >> 0x1f;
          *(uint *)(param_9 + 0x50) =
               (iVar1 * 0x800 | (uint)(*(int *)(param_9 + 0x50) * 0x200000 + iVar1) >> 0x15) - iVar1
          ;
          *(int *)(param_9 + 0x8c) = iVar2;
          zz_026d510_(*(int *)(param_9 + 8),iVar2);
          zz_026d558_(*(int *)(param_9 + 8),FUN_802704d4,param_9);
        }
        zz_02646a4_(iVar7);
        uVar6 = zz_02646ec_(iVar7);
        *(undefined4 *)(param_9 + 0x90) = uVar6;
        zz_026481c_(iVar7,*(undefined4 *)(param_9 + 0x90));
        zz_026480c_(iVar7,0);
        zz_0264814_(iVar7,0);
        zz_0264824_(iVar7,FUN_802706cc,param_9);
      }
      uVar3 = zz_02647c4_(iVar7);
      uVar4 = zz_02647a0_(iVar7);
      zz_0264734_(iVar7);
      uVar6 = zz_026477c_(iVar7);
      zz_02713d4_(*(int *)(param_9 + 0xc),uVar6);
      zz_0271434_(*(int *)(param_9 + 0xc),uVar3);
      zz_0271454_(*(int *)(param_9 + 0xc),uVar4);
      zz_02713b0_();
      zz_0271414_(*(int *)(param_9 + 0xc),(int)*(short *)(param_9 + 0x40));
      zz_026e4b0_();
      iVar1 = zz_02647a0_(*(int *)(param_9 + 4));
      if (iVar1 == 1) {
        if (*(short *)(param_9 + 0x42) == -0x80) {
          zz_02713f4_(*(int *)(param_9 + 0xc),0,0);
        }
        else {
          zz_02713f4_(*(int *)(param_9 + 0xc),0,(int)*(short *)(param_9 + 0x42));
        }
      }
      else {
        if (*(short *)(param_9 + 0x42) == -0x80) {
          zz_02713f4_(*(int *)(param_9 + 0xc),0,-0xf);
        }
        else {
          zz_02713f4_(*(int *)(param_9 + 0xc),0,(int)*(short *)(param_9 + 0x42));
        }
        if (*(short *)(param_9 + 0x44) == -0x80) {
          zz_02713f4_(*(int *)(param_9 + 0xc),1,0xf);
        }
        else {
          zz_02713f4_(*(int *)(param_9 + 0xc),1,(int)*(short *)(param_9 + 0x44));
        }
      }
      if (*(int *)(param_9 + 0x74) != 0) {
        zz_02693c4_(*(int *)(param_9 + 0x74),uVar3);
      }
      iVar1 = zz_02647e8_(iVar7);
      if (iVar1 == 2) {
        zz_0264678_(iVar7);
        zz_027138c_();
      }
      zz_02714f4_(*(int *)(param_9 + 0xc),1);
      *(undefined1 *)(param_9 + 1) = 2;
    }
  }
  return;
}



// ==== 802701f4  FUN_802701f4 ====

void FUN_802701f4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  short local_48;
  short local_46;
  int aiStack_44 [2];
  short *local_3c;
  uint local_38;
  int aiStack_34 [2];
  short *local_2c;
  int local_28;
  
  iVar7 = *(int *)(param_9 + 4);
  piVar6 = *(int **)(param_9 + 0x14);
  if (*(char *)(param_9 + 0x98) != '\0') {
    local_48 = 0;
    (**(code **)(*piVar6 + 0x18))(piVar6,1,0x7fffffff,&local_2c);
    (**(code **)(*piVar6 + 0x18))(piVar6,1,0x7fffffff,&local_3c);
    iVar1 = zz_02696fc_(local_2c,local_28,&local_46);
    if (iVar1 == 0) {
      iVar5 = (int)local_46;
      iVar1 = zz_0269aa8_((short *)((int)local_2c + iVar5),local_28 - iVar5,&local_46);
      if (iVar1 == 0) {
        iVar2 = -1;
      }
      else {
        iVar2 = zz_0269aa8_(local_3c,local_38,&local_48);
      }
      iVar4 = (int)local_48;
      if ((iVar1 == 0) || (iVar2 == 0)) {
        if (iVar1 == 0) {
          (**(code **)(*piVar6 + 0x1c))(piVar6,1,&local_3c);
          zz_02779cc_((int *)&local_2c,iVar5 + local_46,(int *)&local_2c,aiStack_34);
          (**(code **)(*piVar6 + 0x20))(piVar6,0,&local_2c);
          (**(code **)(*piVar6 + 0x1c))(piVar6,1,aiStack_34);
        }
        else {
          (**(code **)(*piVar6 + 0x20))(piVar6,0,&local_2c);
          zz_02779cc_((int *)&local_3c,iVar4,(int *)&local_3c,aiStack_44);
          (**(code **)(*piVar6 + 0x20))(piVar6,0,&local_3c);
          (**(code **)(*piVar6 + 0x1c))(piVar6,1,aiStack_44);
        }
        iVar1 = zz_0264838_(iVar7);
        *(int *)(param_9 + 0xa4) = *(int *)(param_9 + 0xa4) + iVar1;
        zz_0264f8c_(iVar7);
        uVar8 = zz_0264fc4_(iVar7);
        zz_026489c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7);
        iVar1 = zz_02650c0_(iVar7);
        if (iVar1 == 2) {
          zz_0265028_(iVar7,*(int *)(param_9 + 0x48));
          uVar3 = zz_0264734_(iVar7);
          zz_026481c_(iVar7,uVar3);
          zz_026480c_(iVar7,0);
          zz_0264814_(iVar7,0);
        }
        else {
          *(undefined1 *)(param_9 + 0x98) = 0;
        }
      }
      else {
        (**(code **)(*piVar6 + 0x1c))(piVar6,1,&local_3c);
        (**(code **)(*piVar6 + 0x1c))(piVar6,1,&local_2c);
        *(undefined1 *)(param_9 + 0x98) = 0;
      }
    }
    else {
      *(undefined1 *)(param_9 + 0x98) = 0;
      (**(code **)(*piVar6 + 0x1c))(piVar6,1,&local_3c);
      (**(code **)(*piVar6 + 0x1c))(piVar6,1,&local_2c);
    }
  }
  return;
}



// ==== 802704d4  FUN_802704d4 ====

void FUN_802704d4(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = zz_02646c8_(*(int *)(param_1 + 4));
  if (*(char *)(param_1 + 0x6c) == '\0') {
    zz_026481c_(*(int *)(param_1 + 4),0xffffffff);
    zz_026d510_(*(int *)(param_1 + 8),0x7fffffff);
  }
  else {
    zz_026d78c_(iVar2,((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0));
  }
  return;
}



// ==== 8027054c  FUN_8027054c ====

void FUN_8027054c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  undefined1 auStack_28 [4];
  int local_24;
  
  iVar7 = *(int *)(param_9 + 4);
  piVar6 = *(int **)(param_9 + 0x14);
  iVar1 = zz_02646ec_(iVar7);
  uVar2 = zz_02646c8_(iVar7);
  iVar3 = zz_02646a4_(iVar7);
  if ((*(int *)(param_9 + 8) == 0) && (*(char *)(param_9 + 0x6c) == '\0')) {
    zz_026481c_(*(int *)(param_9 + 4),0xffffffff);
  }
  else {
    puVar5 = auStack_28;
    uVar4 = *(undefined4 *)(param_9 + 0x50);
    uVar8 = (**(code **)(*piVar6 + 0x18))(piVar6,1);
    if (local_24 < *(int *)(param_9 + 0x50)) {
      zz_026a274_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49c8c,
                  extraout_r4,uVar4,puVar5,in_r7,in_r8,in_r9,in_r10);
    }
    (**(code **)(*piVar6 + 0x20))(piVar6,0,auStack_28);
    zz_0264814_(iVar7,0);
    *(int *)(param_9 + 0x90) = iVar3 - iVar1;
    zz_026481c_(iVar7,iVar3 - iVar1);
    zz_026480c_(iVar7,uVar2);
    zz_0264830_(iVar7,iVar1);
    if (*(char *)(param_9 + 2) == '\x02') {
      (**(code **)(*piVar6 + 0x14))(piVar6);
      (**(code **)(*piVar6 + 0x18))(piVar6,1,uVar2,auStack_28);
      (**(code **)(*piVar6 + 0x20))(piVar6,0,auStack_28);
    }
    zz_0264630_(iVar7);
    *(int *)(param_9 + 0x4c) = *(int *)(param_9 + 0x4c) + 1;
  }
  return;
}



// ==== 802706cc  FUN_802706cc ====

void FUN_802706cc(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 4);
  iVar1 = zz_02646ec_(iVar4);
  uVar2 = zz_02646c8_(iVar4);
  iVar3 = zz_02646a4_(iVar4);
  zz_0264654_(iVar4);
  zz_0264814_(iVar4,0);
  *(int *)(param_1 + 0x90) = iVar3 - iVar1;
  zz_026481c_(iVar4,iVar3 - iVar1);
  zz_026480c_(iVar4,uVar2);
  zz_0264830_(iVar4,iVar1);
  zz_0264824_(iVar4,FUN_8027054c,param_1);
  return;
}



// ==== 80270774  zz_0270774_ ====

void zz_0270774_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (*(int *)(param_1 + 0xc) == 1) {
    *(undefined4 *)(param_1 + 0xc) = 2;
  }
  if (*(int *)(param_1 + 0xc) == 2) {
    if (*(int *)(param_1 + 0x14) == 1) {
      iVar1 = zz_0271b8c_(*(ushort **)(param_1 + 0x18),*(int *)(param_1 + 0x1c),
                          *(undefined2 **)(param_1 + 0x20),(short *)(param_1 + 0x28),
                          *(short *)(param_1 + 0x30),*(short *)(param_1 + 0x32),
                          (ushort *)(param_1 + 0x34),*(short *)(param_1 + 0x36),
                          *(short *)(param_1 + 0x38));
      *(int *)(param_1 + 0x10) = iVar1;
    }
    else {
      uVar2 = zz_02715d8_(*(ushort **)(param_1 + 0x18),*(int *)(param_1 + 0x1c),
                          *(undefined2 **)(param_1 + 0x20),(short *)(param_1 + 0x28),
                          *(undefined2 **)(param_1 + 0x24),(short *)(param_1 + 0x2c),
                          *(short *)(param_1 + 0x30),*(short *)(param_1 + 0x32),
                          (ushort *)(param_1 + 0x34),*(short *)(param_1 + 0x36),
                          *(short *)(param_1 + 0x38));
      *(undefined4 *)(param_1 + 0x10) = uVar2;
      iVar1 = (int)*(uint *)(param_1 + 0x10) >> 0x1f;
      if ((*(uint *)(param_1 + 0x10) & 1 ^ -iVar1) + iVar1 == 1) {
        DAT_804002b0 = 1;
      }
    }
    *(undefined4 *)(param_1 + 0xc) = 3;
  }
  return;
}



// ==== 8027086c  zz_027086c_ ====

undefined4 zz_027086c_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}



// ==== 80270874  zz_0270874_ ====

void zz_0270874_(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 3) {
    return;
  }
  *(undefined4 *)(param_1 + 0xc) = 0;
  return;
}



// ==== 8027088c  zz_027088c_ ====

void zz_027088c_(int param_1)

{
  *(undefined4 *)(param_1 + 0xc) = 0;
  gnt4_memset((void *)(param_1 + 0x28),0,8);
  return;
}



// ==== 802708c0  zz_02708c0_ ====

void zz_02708c0_(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 1;
  return;
}



// ==== 802708e0  zz_02708e0_ ====

undefined4
zz_02708e0_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  if (*(int *)(param_1 + 0xc) == 0) {
    *(undefined4 *)(param_1 + 0x14) = 2;
    *(undefined4 *)(param_1 + 0x18) = param_2;
    *(undefined4 *)(param_1 + 0x1c) = param_3;
    *(undefined4 *)(param_1 + 0x20) = param_4;
    *(undefined4 *)(param_1 + 0x24) = param_5;
    return 1;
  }
  return 0;
}



// ==== 80270914  zz_0270914_ ====

undefined4 zz_0270914_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (*(int *)(param_1 + 0xc) == 0) {
    *(undefined4 *)(param_1 + 0x14) = 1;
    *(undefined4 *)(param_1 + 0x18) = param_2;
    *(undefined4 *)(param_1 + 0x1c) = param_3;
    *(undefined4 *)(param_1 + 0x20) = param_4;
    *(undefined4 *)(param_1 + 0x24) = 0;
    return 1;
  }
  return 0;
}



// ==== 8027094c  zz_027094c_ ====

undefined4 zz_027094c_(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}



// ==== 80270954  zz_0270954_ ====

void zz_0270954_(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    *param_1 = 0;
    gnt4_memset(param_1,0,0x3c);
  }
  return;
}



// ==== 8027098c  zz_027098c_ ====

void zz_027098c_(int param_1,undefined2 *param_2,undefined2 *param_3,undefined2 *param_4)

{
  *param_2 = *(undefined2 *)(param_1 + 0x34);
  *param_3 = *(undefined2 *)(param_1 + 0x36);
  *param_4 = *(undefined2 *)(param_1 + 0x38);
  return;
}



// ==== 802709a8  zz_02709a8_ ====

void zz_02709a8_(int param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4)

{
  *(undefined2 *)(param_1 + 0x34) = param_2;
  *(undefined2 *)(param_1 + 0x36) = param_3;
  *(undefined2 *)(param_1 + 0x38) = param_4;
  return;
}



// ==== 802709b8  zz_02709b8_ ====

void zz_02709b8_(int param_1,undefined2 *param_2,undefined2 *param_3)

{
  *param_2 = *(undefined2 *)(param_1 + 0x28);
  *param_3 = *(undefined2 *)(param_1 + 0x2a);
  param_2[1] = *(undefined2 *)(param_1 + 0x2c);
  param_3[1] = *(undefined2 *)(param_1 + 0x2e);
  return;
}



// ==== 802709dc  zz_02709dc_ ====

void zz_02709dc_(int param_1,undefined2 *param_2,undefined2 *param_3)

{
  *(undefined2 *)(param_1 + 0x28) = *param_2;
  *(undefined2 *)(param_1 + 0x2a) = *param_3;
  *(undefined2 *)(param_1 + 0x2c) = param_2[1];
  *(undefined2 *)(param_1 + 0x2e) = param_3[1];
  return;
}



// ==== 80270a00  zz_0270a00_ ====

void zz_0270a00_(int param_1,uint param_2,uint param_3)

{
  zz_0269b24_(param_3,param_2,(undefined2 *)(param_1 + 0x30),(undefined2 *)(param_1 + 0x32));
  return;
}



// ==== 80270a30  zz_0270a30_ ====

undefined4 * zz_0270a30_(void)

{
  int *piVar1;
  undefined4 *__s;
  int iVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = &DAT_804002b4;
  iVar2 = 0;
  iVar4 = 2;
  do {
    iVar3 = iVar2;
    if (((((*piVar1 == 0) || (iVar3 = iVar2 + 1, piVar1[0xf] == 0)) ||
         (iVar3 = iVar2 + 2, piVar1[0x1e] == 0)) ||
        ((iVar3 = iVar2 + 3, piVar1[0x2d] == 0 || (iVar3 = iVar2 + 4, piVar1[0x3c] == 0)))) ||
       ((iVar3 = iVar2 + 5, piVar1[0x4b] == 0 ||
        ((iVar3 = iVar2 + 6, piVar1[0x5a] == 0 || (iVar3 = iVar2 + 7, piVar1[0x69] == 0)))))) break;
    piVar1 = piVar1 + 0x78;
    iVar2 = iVar2 + 8;
    iVar4 = iVar4 + -1;
    iVar3 = iVar2;
  } while (iVar4 != 0);
  if (iVar3 == 0x10) {
    __s = (undefined4 *)0x0;
  }
  else {
    iVar2 = iVar3 * 0x3c;
    __s = &DAT_804002b4 + iVar3 * 0xf;
    gnt4_memset(__s,0,0x3c);
    *__s = 1;
    *(int *)(iVar2 + -0x7fbffd48) = iVar3;
    *(undefined4 *)(iVar2 + -0x7fbffd44) = 0;
    *(undefined4 *)(iVar2 + -0x7fbffd40) = 0;
    zz_0269b24_(500,0xac44,(undefined2 *)(iVar2 + -0x7fbffd1c),(undefined2 *)(iVar2 + -0x7fbffd1a));
    gnt4_memset((void *)(iVar2 + -0x7fbffd24),0,8);
  }
  return __s;
}



// ==== 80270b88  zz_0270b88_ ====

void zz_0270b88_(void)

{
  gnt4_memset(&DAT_804002b4,0,0x3c0);
  return;
}



// ==== 80270bb8  zz_0270bb8_ ====

uint zz_0270bb8_(void)

{
  return (-DAT_8040067c | DAT_8040067c) >> 0x1f;
}



// ==== 80270bd4  zz_0270bd4_ ====

void zz_0270bd4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  if (DAT_8040067c == 0) {
    zz_0277bec_();
    zz_0277ed4_(FUN_80271130,0);
    uVar5 = zz_0277ec4_(FUN_802710cc,0);
    if (param_9 == (undefined4 *)0x0) {
      DAT_803adee8 = 0x10;
      DAT_803aded8 = 1;
      DAT_803adedc = 8;
      DAT_803adee0 = 0xc;
      DAT_803adee4 = 0xe;
      DAT_803adeec = 0x18;
    }
    else {
      DAT_803aded8 = *param_9;
      DAT_803adedc = param_9[1];
      DAT_803adee0 = param_9[2];
      DAT_803adee4 = param_9[3];
      DAT_803adee8 = param_9[4];
      DAT_803adeec = param_9[5];
    }
    gnt4_OSCreateThread_bl(-0x7fbff018,&LAB_80270fe0,0,0x80408328,0x1000,DAT_803adedc,1);
    gnt4_OSCreateThread_bl(-0x7fbff648,FUN_80270f30,0,0x80407328,0x2000,DAT_803adee0,1);
    gnt4_OSCreateThread_bl(-0x7fbff330,FUN_80270ed8,0,0x80405328,0x2000,DAT_803adee4,1);
    uVar2 = 0x2000;
    uVar4 = 1;
    puVar1 = &DAT_80403328;
    iVar3 = DAT_803adeec;
    gnt4_OSCreateThread_bl(-0x7fbff960,FUN_80270e0c,0,0x80403328,0x2000,DAT_803adeec,1);
    DAT_8040069c = gnt4_OSGetCurrentThread_bl();
    DAT_8040130c = 1;
    DAT_8040131c = 1;
    DAT_80401314 = 1;
    DAT_80401324 = 1;
    DAT_80401308 = 0;
    DAT_80401318 = 0;
    DAT_80401310 = 0;
    DAT_80401320 = 0;
    DAT_80401304 = 0;
    gnt4_OSResumeThread_bl(-0x7fbff648);
    gnt4_OSResumeThread_bl(-0x7fbff330);
    gnt4_OSResumeThread_bl(-0x7fbff960);
    zz_0278018_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,FUN_80271010,0,
                puVar1,uVar2,iVar3,uVar4,in_r10);
  }
  DAT_8040067c = DAT_8040067c + 1;
  return;
}



// ==== 80270dec  zz_0270dec_ ====

void zz_0270dec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_0277ee4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80270e0c  FUN_80270e0c ====

void FUN_80270e0c(void)

{
  uint uVar1;
  
  while (DAT_8040131c == 1) {
    DAT_80400694 = DAT_80400694 + 1;
    uVar1 = zz_0277c84_();
    if ((uVar1 == 0) || (DAT_80400684 == 1)) {
      if (DAT_80400684 == 1) {
        DAT_80400684 = 0;
        zz_0206ecc_(-0x7fbff960,DAT_803adeec);
      }
      if (DAT_803adef0 != (code *)0x0) {
        (*DAT_803adef0)(DAT_803adef4);
      }
      gnt4_OSSuspendThread_bl(-0x7fbff960);
    }
  }
  DAT_80401318 = 1;
  return;
}



// ==== 80270ed8  FUN_80270ed8 ====

void FUN_80270ed8(void)

{
  while (DAT_8040130c == 1) {
    gnt4_VIWaitForRetrace();
    DAT_80400690 = DAT_80400690 + 1;
    zz_0277da4_();
  }
  DAT_80401308 = 1;
  return;
}



// ==== 80270f30  FUN_80270f30 ====

void FUN_80270f30(void)

{
  while (DAT_80401314 == 1) {
    gnt4_VIWaitForRetrace();
    DAT_8040068c = DAT_8040068c + 1;
    DAT_803faa68 = DAT_803faa68 + 1;
    zz_0277e34_();
    if (DAT_80401318 == 0) {
      gnt4_OSResumeThread_bl(-0x7fbff960);
      if (DAT_803adef0 != (code *)0x0) {
        (*DAT_803adef0)(DAT_803adef4);
      }
    }
  }
  DAT_80401310 = 1;
  return;
}



// ==== 80271010  FUN_80271010 ====

void FUN_80271010(void)

{
  int iVar1;
  
  if (DAT_80401318 != 1) {
    DAT_80400684 = 1;
    zz_0206ecc_(-0x7fbff960,DAT_803aded8);
    iVar1 = 0;
    while ((iVar1 < 200000000 && (gnt4_OSResumeThread_bl(-0x7fbff960), DAT_80400684 != 0))) {
      iVar1 = iVar1 + 1;
    }
    if (iVar1 == 200000000) {
      zz_0278594_(-0x7fd49c30);
    }
    zz_0206ecc_(-0x7fbff960,DAT_803adeec);
  }
  return;
}



// ==== 802710cc  FUN_802710cc ====

void FUN_802710cc(void)

{
  int iVar1;
  
  DAT_80400680 = DAT_80400680 + -1;
  if (DAT_80400680 == 0) {
    iVar1 = gnt4_OSGetCurrentThread_bl();
    gnt4_OSSuspendThread_bl(-0x7fbff018);
    zz_0206ecc_(iVar1,DAT_80401300);
  }
  return;
}



// ==== 80271130  FUN_80271130 ====

void FUN_80271130(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if (DAT_80400680 == 0) {
    gnt4_OSDisableInterrupts_bl();
    gnt4_OSDisableScheduler_bl();
    DAT_80401304 = 1;
    iVar1 = gnt4_OSGetCurrentThread_bl();
    uVar2 = zz_0206f8c_(iVar1);
    zz_0206ecc_(iVar1,DAT_803aded8);
    DAT_80401304 = 0;
    DAT_80401300 = uVar2;
    gnt4_OSEnableScheduler_bl();
    gnt4_OSRestoreInterrupts_bl();
    gnt4_OSResumeThread_bl(-0x7fbff018);
  }
  DAT_80400680 = DAT_80400680 + 1;
  return;
}



// ==== 802711e4  zz_02711e4_ ====

void zz_02711e4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  zz_02788b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80271204  zz_0271204_ ====

void zz_0271204_(void)

{
  zz_0278944_();
  return;
}



// ==== 80271224  zz_0271224_ ====

void zz_0271224_(void)

{
  zz_0277d14_();
  return;
}



// ==== 80271244  zz_0271244_ ====

void zz_0271244_(void)

{
  gnt4_VIWaitForRetrace();
  return;
}



// ==== 80271264  zz_0271264_ ====

void zz_0271264_(int param_1)

{
  zz_0273b7c_(-0x7fd8ecdc,0);
  zz_027476c_(&DAT_802b6440,&LAB_802793a8);
  zz_0273b7c_(-0x7fd8ecdc,0);
  zz_027476c_(&DAT_802b6444,FUN_802759ec);
  zz_0274638_(&DAT_802b6444);
  if (param_1 == 0) {
    zz_0275a58_();
  }
  else {
    zz_0275a58_();
  }
  return;
}



// ==== 80271324  FUN_80271324 ====

void FUN_80271324(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,int param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80271348  zz_0271348_ ====

void zz_0271348_(int param_1,undefined2 param_2)

{
  zz_027136c_(*(int *)(param_1 + 0xc),param_2);
  return;
}



// ==== 8027136c  zz_027136c_ ====

void zz_027136c_(int param_1,undefined2 param_2)

{
  zz_0279468_(param_1,param_2);
  return;
}



// ==== 8027138c  zz_027138c_ ====

undefined4 zz_027138c_(void)

{
  zz_0279480_();
  return 0;
}



// ==== 802713b0  zz_02713b0_ ====

void zz_02713b0_(void)

{
  return;
}



// ==== 802713b4  zz_02713b4_ ====

void zz_02713b4_(void)

{
  zz_0279478_();
  return;
}



// ==== 802713d4  zz_02713d4_ ====

void zz_02713d4_(int param_1,undefined4 param_2)

{
  zz_0279488_(param_1,param_2);
  return;
}



// ==== 802713f4  zz_02713f4_ ====

void zz_02713f4_(int param_1,int param_2,int param_3)

{
  zz_0279498_(param_1,param_2,param_3);
  return;
}



// ==== 80271414  zz_0271414_ ====

void zz_0271414_(int param_1,uint param_2)

{
  zz_027954c_(param_1,param_2);
  return;
}



// ==== 80271434  zz_0271434_ ====

void zz_0271434_(int param_1,uint param_2)

{
  zz_02795f8_(param_1,param_2);
  return;
}



// ==== 80271454  zz_0271454_ ====

void zz_0271454_(int param_1,undefined1 param_2)

{
  zz_027974c_(param_1,param_2);
  return;
}



// ==== 80271474  zz_0271474_ ====

void zz_0271474_(void)

{
  zz_027975c_();
  return;
}



// ==== 80271494  zz_0271494_ ====

void zz_0271494_(int param_1)

{
  zz_0279e10_(param_1);
  return;
}



// ==== 802714b4  zz_02714b4_ ====

void zz_02714b4_(int param_1)

{
  zz_0279e68_(param_1);
  return;
}



// ==== 802714d4  zz_02714d4_ ====

void zz_02714d4_(int param_1,uint param_2)

{
  zz_0279ec4_(param_1,param_2);
  return;
}



// ==== 802714f4  zz_02714f4_ ====

void zz_02714f4_(int param_1,uint param_2)

{
  zz_027a064_(param_1,param_2);
  return;
}



// ==== 80271514  zz_0271514_ ====

void zz_0271514_(void *param_1)

{
  zz_0279ec4_((int)param_1,0);
  zz_027a064_((int)param_1,0);
  zz_027a264_(param_1);
  return;
}



// ==== 80271558  zz_0271558_ ====

void zz_0271558_(int *param_1,int param_2)

{
  zz_027a334_(param_1,param_2);
  return;
}



// ==== 80271578  zz_0271578_ ====

void zz_0271578_(undefined4 param_1,undefined4 param_2)

{
  zz_027ac48_(param_1,param_2);
  return;
}



// ==== 80271598  zz_0271598_ ====

void zz_0271598_(void)

{
  zz_027aab4_();
  return;
}



// ==== 802715b8  zz_02715b8_ ====

void zz_02715b8_(void)

{
  zz_027abd4_();
  return;
}



// ==== 802715d8  zz_02715d8_ ====

void zz_02715d8_(ushort *param_1,int param_2,undefined2 *param_3,short *param_4,undefined2 *param_5,
                short *param_6,short param_7,short param_8,ushort *param_9,short param_10,
                short param_11)

{
  if (DAT_803fccd8 == 0) {
    zz_027163c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11);
  }
  else {
    zz_027189c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11);
  }
  return;
}



// ==== 8027163c  zz_027163c_ ====

int zz_027163c_(ushort *param_1,int param_2,undefined2 *param_3,short *param_4,undefined2 *param_5,
               short *param_6,short param_7,short param_8,ushort *param_9,short param_10,
               short param_11)

{
  char cVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  
  iVar8 = (int)param_8;
  iVar7 = (int)param_7;
  iVar12 = 0;
  iVar13 = (int)*param_4;
  iVar16 = (int)param_4[1];
  iVar14 = (int)*param_6;
  iVar15 = (int)param_6[1];
  while( true ) {
    if (param_2 / 2 <= iVar12) {
      *param_4 = (short)iVar13;
      param_4[1] = (short)iVar16;
      *param_6 = (short)iVar14;
      param_6[1] = (short)iVar15;
      return param_2;
    }
    uVar3 = *param_1;
    if (((int)(short)uVar3 & 0x8000U) != 0) break;
    uVar4 = *param_9;
    *param_9 = param_11 + uVar4 * param_10;
    iVar10 = (int)(short)(((uVar3 ^ uVar4) & 0x1fff) + 1);
    *param_9 = *param_9 & 0x7fff;
    uVar3 = param_1[9];
    if (((int)(short)uVar3 & 0x8000U) != 0) {
      return iVar12 << 1;
    }
    uVar4 = *param_9;
    *param_9 = param_11 + uVar4 * param_10;
    iVar9 = (int)(short)(((uVar3 ^ uVar4) & 0x1fff) + 1);
    *param_9 = *param_9 & 0x7fff;
    iVar17 = 0x10;
    puVar5 = param_1 + 1;
    do {
      puVar6 = puVar5;
      cVar1 = *(char *)puVar6;
      cVar2 = *(char *)(puVar6 + 9);
      iVar16 = ((int)cVar1 >> 4) * iVar10 + (iVar7 * iVar13 + iVar8 * iVar16 >> 0xc);
      if ((0x7fff < iVar16) || (iVar16 < -0x8000)) {
        if (iVar16 < -0x8000) {
          iVar16 = -0x8000;
        }
        else if (0x7fff < iVar16) {
          iVar16 = 0x7fff;
        }
      }
      iVar15 = ((int)cVar2 >> 4) * iVar9 + (iVar7 * iVar14 + iVar8 * iVar15 >> 0xc);
      if ((0x7fff < iVar15) || (iVar15 < -0x8000)) {
        if (iVar15 < -0x8000) {
          iVar15 = -0x8000;
        }
        else if (0x7fff < iVar15) {
          iVar15 = 0x7fff;
        }
      }
      *param_3 = (short)iVar16;
      iVar11 = *(int *)(&DAT_802b6448 + ((int)cVar1 & 0xfU) * 4);
      *param_5 = (short)iVar15;
      iVar13 = iVar11 * iVar10 + (iVar7 * iVar16 + iVar8 * iVar13 >> 0xc);
      if ((0x7fff < iVar13) || (iVar13 < -0x8000)) {
        if (iVar13 < -0x8000) {
          iVar13 = -0x8000;
        }
        else if (0x7fff < iVar13) {
          iVar13 = 0x7fff;
        }
      }
      iVar14 = *(int *)(&DAT_802b6448 + ((int)cVar2 & 0xfU) * 4) * iVar9 +
               (iVar7 * iVar15 + iVar8 * iVar14 >> 0xc);
      if ((0x7fff < iVar14) || (iVar14 < -0x8000)) {
        if (iVar14 < -0x8000) {
          iVar14 = -0x8000;
        }
        else if (0x7fff < iVar14) {
          iVar14 = 0x7fff;
        }
      }
      param_3[1] = (short)iVar13;
      param_3 = param_3 + 2;
      param_5[1] = (short)iVar14;
      param_5 = param_5 + 2;
      iVar17 = iVar17 + -1;
      puVar5 = (ushort *)((int)puVar6 + 1);
    } while (iVar17 != 0);
    param_1 = (ushort *)((int)puVar6 + 0x13);
    iVar12 = iVar12 + 1;
  }
  return iVar12 << 1;
}



// ==== 8027189c  zz_027189c_ ====

int zz_027189c_(ushort *param_1,int param_2,undefined2 *param_3,short *param_4,undefined2 *param_5,
               short *param_6,short param_7,short param_8,ushort *param_9,short param_10,
               short param_11)

{
  char cVar1;
  char cVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  
  iVar8 = (int)param_8;
  iVar7 = (int)param_7;
  iVar14 = 0;
  iVar15 = (int)*param_4;
  iVar9 = (int)param_4[1];
  iVar16 = (int)*param_6;
  iVar17 = (int)param_6[1];
  while( true ) {
    if (param_2 / 2 <= iVar14) {
      *param_4 = (short)iVar15;
      param_4[1] = (short)iVar9;
      *param_6 = (short)iVar16;
      param_6[1] = (short)iVar17;
      return param_2;
    }
    uVar3 = *param_1;
    if (((int)(short)uVar3 & 0x8000U) != 0) break;
    uVar4 = *param_9;
    *param_9 = param_11 + uVar4 * param_10;
    iVar13 = (int)(short)(((uVar3 ^ uVar4) & 0x1fff) + 1);
    *param_9 = *param_9 & 0x7fff;
    uVar3 = param_1[9];
    if (((int)(short)uVar3 & 0x8000U) != 0) {
      return iVar14 << 1;
    }
    uVar4 = *param_9;
    *param_9 = param_11 + uVar4 * param_10;
    iVar12 = (int)(short)(((uVar3 ^ uVar4) & 0x1fff) + 1);
    *param_9 = *param_9 & 0x7fff;
    iVar18 = 0x10;
    puVar5 = param_1 + 1;
    do {
      puVar6 = puVar5;
      cVar1 = *(char *)puVar6;
      cVar2 = *(char *)(puVar6 + 9);
      iVar9 = ((int)cVar1 >> 4) * iVar13 + (iVar7 * iVar15 + iVar8 * iVar9 >> 0xc);
      if ((0x7fff < iVar9) || (iVar9 < -0x8000)) {
        if (iVar9 < -0x8000) {
          iVar9 = -0x8000;
        }
        else if (0x7fff < iVar9) {
          iVar9 = 0x7fff;
        }
      }
      iVar17 = ((int)cVar2 >> 4) * iVar12 + (iVar7 * iVar16 + iVar8 * iVar17 >> 0xc);
      if ((0x7fff < iVar17) || (iVar17 < -0x8000)) {
        if (iVar17 < -0x8000) {
          iVar17 = -0x8000;
        }
        else if (0x7fff < iVar17) {
          iVar17 = 0x7fff;
        }
      }
      iVar10 = (iVar9 + iVar17) * 7;
      iVar10 = iVar10 / 10 + (iVar10 >> 0x1f);
      iVar10 = iVar10 - (iVar10 >> 0x1f);
      if ((0x7fff < iVar10) || (iVar10 < -0x8000)) {
        if (iVar10 < -0x8000) {
          iVar10 = -0x8000;
        }
        else if (0x7fff < iVar10) {
          iVar10 = 0x7fff;
        }
      }
      *param_5 = (short)iVar10;
      iVar11 = *(int *)(&DAT_802b6448 + ((int)cVar1 & 0xfU) * 4);
      *param_3 = (short)iVar10;
      iVar15 = iVar11 * iVar13 + (iVar7 * iVar9 + iVar8 * iVar15 >> 0xc);
      if ((0x7fff < iVar15) || (iVar15 < -0x8000)) {
        if (iVar15 < -0x8000) {
          iVar15 = -0x8000;
        }
        else if (0x7fff < iVar15) {
          iVar15 = 0x7fff;
        }
      }
      iVar16 = *(int *)(&DAT_802b6448 + ((int)cVar2 & 0xfU) * 4) * iVar12 +
               (iVar7 * iVar17 + iVar8 * iVar16 >> 0xc);
      if ((0x7fff < iVar16) || (iVar16 < -0x8000)) {
        if (iVar16 < -0x8000) {
          iVar16 = -0x8000;
        }
        else if (0x7fff < iVar16) {
          iVar16 = 0x7fff;
        }
      }
      iVar10 = (iVar15 + iVar16) * 7;
      iVar10 = iVar10 / 10 + (iVar10 >> 0x1f);
      iVar10 = iVar10 - (iVar10 >> 0x1f);
      if ((0x7fff < iVar10) || (iVar10 < -0x8000)) {
        if (iVar10 < -0x8000) {
          iVar10 = -0x8000;
        }
        else if (0x7fff < iVar10) {
          iVar10 = 0x7fff;
        }
      }
      param_5[1] = (short)iVar10;
      param_5 = param_5 + 2;
      param_3[1] = (short)iVar10;
      param_3 = param_3 + 2;
      iVar18 = iVar18 + -1;
      puVar5 = (ushort *)((int)puVar6 + 1);
    } while (iVar18 != 0);
    param_1 = (ushort *)((int)puVar6 + 0x13);
    iVar14 = iVar14 + 1;
  }
  return iVar14 << 1;
}



// ==== 80271b8c  zz_0271b8c_ ====

int zz_0271b8c_(ushort *param_1,int param_2,undefined2 *param_3,short *param_4,short param_5,
               short param_6,ushort *param_7,short param_8,short param_9)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar4 = 0;
  iVar6 = (int)*param_4;
  iVar5 = (int)param_4[1];
  while( true ) {
    if (param_2 <= iVar4) {
      *param_4 = (short)iVar6;
      param_4[1] = (short)iVar5;
      return param_2;
    }
    uVar2 = *param_1;
    if (((int)(short)uVar2 & 0x8000U) != 0) break;
    uVar3 = *param_7;
    *param_7 = param_9 + uVar3 * param_8;
    iVar7 = (int)(short)(((uVar2 ^ uVar3) & 0x1fff) + 1);
    *param_7 = *param_7 & 0x7fff;
    iVar8 = 0x10;
    param_1 = param_1 + 1;
    do {
      cVar1 = *(char *)param_1;
      param_1 = (ushort *)((int)param_1 + 1);
      iVar5 = ((int)cVar1 >> 4) * iVar7 + (param_5 * iVar6 + param_6 * iVar5 >> 0xc);
      if ((0x7fff < iVar5) || (iVar5 < -0x8000)) {
        if (iVar5 < -0x8000) {
          iVar5 = -0x8000;
        }
        else if (0x7fff < iVar5) {
          iVar5 = 0x7fff;
        }
      }
      *param_3 = (short)iVar5;
      iVar6 = *(int *)(&DAT_802b6448 + ((int)cVar1 & 0xfU) * 4) * iVar7 +
              (param_5 * iVar5 + param_6 * iVar6 >> 0xc);
      if ((0x7fff < iVar6) || (iVar6 < -0x8000)) {
        if (iVar6 < -0x8000) {
          iVar6 = -0x8000;
        }
        else if (0x7fff < iVar6) {
          iVar6 = 0x7fff;
        }
      }
      param_3[1] = (short)iVar6;
      param_3 = param_3 + 2;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    iVar4 = iVar4 + 1;
  }
  return iVar4;
}



// ==== 80271ce0  zz_0271ce0_ ====

undefined4 zz_0271ce0_(char *param_1)

{
  if (*param_1 != -1) {
    return 0;
  }
  if ((param_1[1] != -4) && (param_1[1] != -3)) {
    return 0;
  }
  return 1;
}



// ==== 80271d18  zz_0271d18_ ====

undefined4 zz_0271d18_(int param_1,int param_2,int param_3)

{
  byte bVar1;
  uint uVar2;
  
  if (*(int *)(param_1 + 0xbc) == 0) {
    return 0;
  }
  if (param_3 < 4) {
    return 0;
  }
  bVar1 = *(byte *)(param_2 + 2);
  uVar2 = (uint)(*(byte *)(param_2 + 3) >> 6);
  *(undefined2 *)(param_1 + 2) = 1;
  *(undefined4 *)(param_1 + 0x14) = *(undefined4 *)(&DAT_802b6488 + (bVar1 & 0xc));
  *(char *)(param_1 + 0xe) =
       ((char)~((byte)(uVar2 - 3 >> 0x18) | (byte)(3 - uVar2 >> 0x18)) >> 7) + '\x02';
  *(undefined1 *)(param_1 + 0xd) = 0x10;
  *(undefined4 *)(param_1 + 0x18) = 0x7fffffff;
  *(undefined1 *)(param_1 + 0xf) = 0x7f;
  *(undefined4 *)(param_1 + 0x10) = 0x480;
  *(undefined2 *)(param_1 + 0x98) = 0xb;
  *(int *)(param_1 + 0x50) = (int)*(char *)(param_1 + 0xe);
  *(int *)(param_1 + 0x54) = (int)*(char *)(param_1 + 0xf);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0x10);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x44);
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  *(undefined2 *)(param_1 + 0x24) = 0;
  *(undefined2 *)(param_1 + 0x26) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  return 1;
}



// ==== 80271e14  zz_0271e14_ ====

void zz_0271e14_(int param_1)

{
  if (*(int *)(param_1 + 0xbc) != 0) {
    (*DAT_80408330)();
  }
  return;
}



// ==== 80271e4c  zz_0271e4c_ ====

void zz_0271e4c_(int param_1)

{
  if (*(int *)(param_1 + 0xbc) != 0) {
    (*DAT_8040832c)();
  }
  return;
}



// ==== 80271e84  zz_0271e84_ ====

void zz_0271e84_(int param_1,int param_2)

{
  int iVar1;
  
  *(int *)(param_1 + 0xc0) = param_2;
  iVar1 = param_2 / 0x480 + (param_2 >> 0x1f);
  *(int *)(param_1 + 0xc4) = iVar1 - (iVar1 >> 0x1f);
  return;
}



// ==== 80271ea8  zz_0271ea8_ ====

void zz_0271ea8_(int param_1)

{
  if (*(int *)(param_1 + 0xbc) != 0) {
    (*DAT_80408328)();
  }
  return;
}



// ==== 80271ee0  zz_0271ee0_ ====

void zz_0271ee0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  DAT_80408338 = DAT_80408338 + -1;
  if (DAT_80408338 == 0) {
    zz_0272ce4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    DAT_8040833c = 0xffffffff;
    DAT_80408340 = 0;
    DAT_80408344 = 0;
    DAT_8040846c = 0;
    DAT_80408348 = 0;
    gnt4_memset(&DAT_8040834c,0,0x20);
    gnt4_memset(&DAT_8040836c,0xff,0x100);
    gnt4_memset(&DAT_80408470,0,0x400);
    gnt4_memset(&DAT_80408870,0,0x440);
  }
  return;
}



// ==== 80271f7c  zz_0271f7c_ ====

void zz_0271f7c_(void)

{
  if (DAT_80408338 == 0) {
    gnt4_memset(&DAT_80408870,0,0x440);
    gnt4_memset(&DAT_80408470,0,0x400);
    gnt4_memset(&DAT_8040836c,0xff,0x100);
    gnt4_memset(&DAT_8040834c,0,0x20);
    DAT_80408348 = 0;
    DAT_8040846c = 0;
    DAT_80408344 = 0;
    DAT_80408340 = 0;
    DAT_8040833c = 0xffffffff;
  }
  DAT_80408338 = DAT_80408338 + 1;
  return;
}



// ==== 80272028  zz_0272028_ ====

void zz_0272028_(uint param_1,int param_2)

{
  gnt4_DCInvalidateRange_bl(param_1,param_2);
  return;
}



// ==== 80272048  zz_0272048_ ====

int zz_0272048_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11,undefined4 *param_12,int *param_13,
               uint *param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  ushort *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort *puVar11;
  ushort *puVar12;
  ushort *puVar13;
  ushort *puVar14;
  ushort uVar15;
  int iVar16;
  int *piVar17;
  ushort *puVar18;
  int *piVar19;
  int iVar20;
  ushort *puVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  uint uVar25;
  
  if ((param_9 < 0) || (0xff < param_9)) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49b04,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar24 = -3;
  }
  else if (*(int *)(&DAT_80408470 + param_9 * 4) == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49b04,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar24 = -3;
  }
  else if ((param_10 < 0) || (*(int *)(*(int *)(&DAT_80408470 + param_9 * 4) + 8) <= param_10)) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49ae0,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar24 = -3;
  }
  else {
    iVar24 = 0;
  }
  if (iVar24 < 0) {
    *param_12 = 0;
    *param_13 = -1;
    *param_14 = 0xffffffff;
  }
  else {
    iVar23 = *(int *)(&DAT_80408470 + param_9 * 4);
    if (*(char *)(iVar23 + 0xf) == '\x01') {
      uVar22 = *(uint *)(iVar23 + 0x118);
      piVar19 = (int *)(iVar23 + 0x11c);
      iVar20 = 0;
      if (0 < param_10) {
        if ((8 < param_10) && (uVar25 = param_10 - 1U >> 3, piVar17 = piVar19, 0 < param_10 + -8)) {
          do {
            iVar16 = *piVar17;
            iVar20 = iVar20 + 8;
            piVar1 = piVar17 + 1;
            piVar2 = piVar17 + 2;
            piVar3 = piVar17 + 3;
            piVar4 = piVar17 + 4;
            piVar5 = piVar17 + 5;
            piVar6 = piVar17 + 6;
            piVar7 = piVar17 + 7;
            piVar17 = piVar17 + 8;
            uVar22 = uVar22 + iVar16 + *piVar1 + *piVar2 + *piVar3 + *piVar4 + *piVar5 + *piVar6 +
                     *piVar7;
            uVar25 = uVar25 - 1;
          } while (uVar25 != 0);
        }
        iVar16 = param_10 - iVar20;
        piVar17 = piVar19 + iVar20;
        if (iVar20 < param_10) {
          do {
            iVar20 = *piVar17;
            piVar17 = piVar17 + 1;
            uVar22 = uVar22 + iVar20;
            iVar16 = iVar16 + -1;
          } while (iVar16 != 0);
        }
      }
      *param_14 = piVar19[param_10];
    }
    else {
      uVar22 = (uint)*(ushort *)(iVar23 + 0x118);
      puVar21 = (ushort *)(iVar23 + 0x11a);
      iVar20 = 0;
      if (0 < param_10) {
        if ((8 < param_10) && (uVar25 = param_10 - 1U >> 3, puVar18 = puVar21, 0 < param_10 + -8)) {
          do {
            uVar15 = *puVar18;
            iVar20 = iVar20 + 8;
            puVar8 = puVar18 + 1;
            puVar9 = puVar18 + 2;
            puVar10 = puVar18 + 3;
            puVar11 = puVar18 + 4;
            puVar12 = puVar18 + 5;
            puVar13 = puVar18 + 6;
            puVar14 = puVar18 + 7;
            puVar18 = puVar18 + 8;
            uVar22 = uVar22 + uVar15 + (uint)*puVar8 + (uint)*puVar9 + (uint)*puVar10 +
                     (uint)*puVar11 + (uint)*puVar12 + (uint)*puVar13 + (uint)*puVar14;
            uVar25 = uVar25 - 1;
          } while (uVar25 != 0);
        }
        iVar16 = param_10 - iVar20;
        puVar18 = puVar21 + iVar20;
        if (iVar20 < param_10) {
          do {
            uVar15 = *puVar18;
            puVar18 = puVar18 + 1;
            uVar22 = uVar22 + uVar15;
            iVar16 = iVar16 + -1;
          } while (iVar16 != 0);
        }
      }
      *param_14 = (uint)puVar21[param_10];
    }
    zz_0238cbc_(param_11,iVar23 + 0x10,0x100);
    *param_12 = *(undefined4 *)(iVar23 + 0x110);
    *param_13 = *(int *)(iVar23 + 0x114) + uVar22;
  }
  return iVar24;
}



// ==== 802722d8  zz_02722d8_ ====

int zz_02722d8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49abc,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = -3;
  }
  else {
    iVar1 = (int)*(char *)(param_9 + 1);
  }
  return iVar1;
}



// ==== 80272318  zz_0272318_ ====

int zz_0272318_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49a38,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = -3;
  }
  else {
    if (0xffffe < *(int *)(param_9 + 0xc)) {
      zz_026cd94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 4),*(int *)(param_9 + 0xc),param_11,param_12,param_13,param_14,
                  param_15,param_16);
      iVar1 = zz_026d7dc_(*(int *)(param_9 + 4));
      if (iVar1 == 4) {
        return -5;
      }
    }
    uVar2 = zz_026ceb8_(*(int *)(param_9 + 4));
    *(uint *)(param_9 + 0xc) = ((int)uVar2 >> 0xb) + (uint)((int)uVar2 < 0 && (uVar2 & 0x7ff) != 0);
    iVar1 = *(int *)(param_9 + 0xc);
    if (0xffffe < iVar1) {
      iVar1 = -5;
    }
  }
  return iVar1;
}



// ==== 802723b8  zz_02723b8_ ====

undefined4
zz_02723b8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           uint param_10,int param_11)

{
  int iVar1;
  ushort uVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint extraout_r4;
  uint extraout_r4_00;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined8 uVar13;
  
  puVar7 = &DAT_80408348;
  iVar12 = (int)DAT_80408348 >> 0x1f;
  puVar11 = (undefined4 *)&DAT_8040836c;
  puVar9 = (undefined *)(DAT_80408358 + 1);
  iVar12 = (iVar12 * 0x10 | (uint)((int)DAT_80408348 * 0x10000000 + iVar12) >> 0x1c) - iVar12;
  iVar10 = 0;
  iVar6 = iVar12 * 0x10;
  DAT_80408348 = (undefined *)(iVar12 + 1);
  (&DAT_8040836c)[iVar6] = 6;
  (&DAT_8040836d)[iVar6] = 0;
  DAT_80408358 = (ushort)puVar9;
  *(ushort *)(&DAT_8040836e + iVar6) = DAT_80408358;
  *(int *)(&DAT_80408370 + iVar6) = param_9;
  *(uint *)(&DAT_80408374 + iVar6) = param_10;
  *(int *)(&DAT_80408378 + iVar6) = param_11;
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd499e8,param_10
                ,param_11,&DAT_80408348,puVar9,0,&DAT_8040836c,iVar12);
    uVar4 = 0xfffffffd;
  }
  else {
    uVar5 = param_10;
    iVar6 = param_11;
    puVar8 = puVar7;
    if (*(char *)(param_9 + 1) == '\x02') {
      iVar6 = (int)DAT_80408348 >> 0x1f;
      uVar5 = 5;
      puVar9 = (undefined *)
               ((iVar6 * 0x10 | (uint)((int)DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6);
      iVar1 = (int)puVar9 * 0x10;
      iVar6 = DAT_80408356 + 1;
      puVar11 = (undefined4 *)(&DAT_8040836c + iVar1);
      *(undefined1 *)puVar11 = 5;
      DAT_80408348 = puVar9 + 1;
      (&DAT_8040836d)[iVar1] = 0;
      DAT_80408356 = (ushort)iVar6;
      *(ushort *)(&DAT_8040836e + iVar1) = DAT_80408356;
      *(int *)(&DAT_80408370 + iVar1) = param_9;
      *(undefined4 *)(&DAT_80408374 + iVar1) = 0xffffffff;
      *(undefined4 *)(&DAT_80408378 + iVar1) = 0xffffffff;
      if (param_9 == 0) {
        param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              -0x7fd499c4,5,iVar6,&DAT_80408348,puVar9,0,puVar11,iVar12);
        uVar5 = extraout_r4;
        puVar8 = puVar7;
      }
      else {
        puVar8 = &DAT_80408348;
        if (*(char *)(param_9 + 1) != '\x01') {
          if (*(char *)(param_9 + 1) == '\x03') {
            *(undefined1 *)(param_9 + 1) = 1;
          }
          else if (*(int *)(param_9 + 4) == 0) {
            param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  -0x7fd499a0,5,iVar6,&DAT_80408348,puVar9,0,puVar11,iVar12);
            uVar5 = extraout_r4_00;
            puVar8 = puVar7;
          }
          else {
            zz_026d564_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 4),5,iVar6,&DAT_80408348,puVar9,0,puVar11,iVar12);
            uVar13 = zz_026960c_();
            iVar6 = zz_026d770_(*(int *)(param_9 + 4));
            *(int *)(param_9 + 0x20) = iVar6 - *(int *)(param_9 + 0x14);
            if ((*(int *)(param_9 + 8) != 0) && (*(char *)(param_9 + 2) == '\0')) {
              if (DAT_8040846c == 1) {
                zz_0272028_(*(uint *)(param_9 + 0x24),*(int *)(param_9 + 0x28));
              }
              uVar13 = (**(code **)(**(int **)(param_9 + 8) + 0xc))();
              *(undefined4 *)(param_9 + 8) = 0;
            }
            *(undefined1 *)(param_9 + 1) = 1;
            param_1 = zz_02695d4_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
            uVar2 = DAT_80408356;
            puVar11 = &DAT_80408348;
            puVar8 = (undefined4 *)0x5;
            iVar6 = 1;
            uVar5 = (uint)DAT_80408356;
            iVar10 = (int)DAT_80408348 >> 0x1f;
            iVar10 = (iVar10 * 0x10 | (uint)((int)DAT_80408348 * 0x10000000 + iVar10) >> 0x1c) -
                     iVar10;
            iVar1 = iVar10 * 0x10;
            puVar9 = &DAT_8040836c + iVar1;
            DAT_80408348 = (undefined *)(iVar10 + 1);
            *puVar9 = 5;
            (&DAT_8040836d)[iVar1] = 1;
            *(ushort *)(&DAT_8040836e + iVar1) = uVar2;
            *(int *)(&DAT_80408370 + iVar1) = param_9;
            *(undefined4 *)(&DAT_80408374 + iVar1) = 0xffffffff;
            *(undefined4 *)(&DAT_80408378 + iVar1) = 0xffffffff;
          }
        }
      }
    }
    if (param_11 == 0) {
      *(uint *)(param_9 + 0x14) = param_10;
    }
    else if (param_11 == 1) {
      *(uint *)(param_9 + 0x14) = *(int *)(param_9 + 0x14) + param_10;
    }
    else {
      if (param_11 != 2) {
        zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49974,
                    uVar5,iVar6,puVar8,puVar9,iVar10,puVar11,iVar12);
        return 0xfffffffd;
      }
      *(uint *)(param_9 + 0x14) = *(int *)(param_9 + 0xc) + param_10;
    }
    if (*(int *)(param_9 + 0x14) < 0) {
      *(undefined4 *)(param_9 + 0x14) = 0;
    }
    else if (*(int *)(param_9 + 0xc) < *(int *)(param_9 + 0x14)) {
      *(int *)(param_9 + 0x14) = *(int *)(param_9 + 0xc);
    }
    uVar3 = DAT_80408358;
    iVar12 = (int)DAT_80408348 >> 0x1f;
    iVar12 = (iVar12 * 0x10 | (uint)((int)DAT_80408348 * 0x10000000 + iVar12) >> 0x1c) - iVar12;
    iVar6 = iVar12 * 0x10;
    DAT_80408348 = (undefined *)(iVar12 + 1);
    (&DAT_8040836c)[iVar6] = 6;
    (&DAT_8040836d)[iVar6] = 1;
    *(undefined2 *)(&DAT_8040836e + iVar6) = uVar3;
    *(int *)(&DAT_80408370 + iVar6) = param_9;
    *(uint *)(&DAT_80408374 + iVar6) = param_10;
    *(int *)(&DAT_80408378 + iVar6) = param_11;
    uVar4 = *(undefined4 *)(param_9 + 0x14);
  }
  return uVar4;
}



// ==== 802726d8  zz_02726d8_ ====

void zz_02726d8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar4 = zz_026960c_();
  iVar2 = 0;
  pcVar3 = &DAT_80408870;
  do {
    if (*pcVar3 == '\x01') {
      if (pcVar3[1] == '\x02') {
        iVar1 = zz_026d7dc_(*(int *)(pcVar3 + 4));
        pcVar3[1] = (char)iVar1;
        iVar1 = zz_026d770_(*(int *)(pcVar3 + 4));
        *(int *)(pcVar3 + 0x20) = iVar1 - *(int *)(pcVar3 + 0x14);
        if ((pcVar3[1] == '\x03') || (pcVar3[1] == '\x04')) {
          *(int *)(pcVar3 + 0x14) = *(int *)(pcVar3 + 0x14) + *(int *)(pcVar3 + 0x20);
          if ((*(int *)(pcVar3 + 8) != 0) && (pcVar3[2] == '\0')) {
            if (DAT_8040846c == 1) {
              zz_0272028_(*(uint *)(pcVar3 + 0x24),*(int *)(pcVar3 + 0x28));
            }
            uVar4 = (**(code **)(**(int **)(pcVar3 + 8) + 0xc))();
            pcVar3[8] = '\0';
            pcVar3[9] = '\0';
            pcVar3[10] = '\0';
            pcVar3[0xb] = '\0';
          }
        }
      }
      if ((pcVar3[3] == '\x01') && (iVar1 = zz_026d7dc_(*(int *)(pcVar3 + 4)), iVar1 == 1)) {
        iVar1 = zz_026d770_(*(int *)(pcVar3 + 4));
        *(int *)(pcVar3 + 0x20) = iVar1 - *(int *)(pcVar3 + 0x14);
        if ((*(int *)(pcVar3 + 8) != 0) && (pcVar3[2] == '\0')) {
          if (DAT_8040846c == 1) {
            zz_0272028_(*(uint *)(pcVar3 + 0x24),*(int *)(pcVar3 + 0x28));
          }
          uVar4 = (**(code **)(**(int **)(pcVar3 + 8) + 0xc))();
          pcVar3[8] = '\0';
          pcVar3[9] = '\0';
          pcVar3[10] = '\0';
          pcVar3[0xb] = '\0';
        }
        pcVar3[1] = '\x01';
        pcVar3[3] = '\0';
      }
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x44;
  } while (iVar2 < 0x10);
  zz_02695d4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80272868  zz_0272868_ ====

undefined4
zz_0272868_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  
  iVar6 = DAT_80408348 >> 0x1f;
  iVar4 = DAT_8040835a + 1;
  iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
  iVar1 = iVar6 * 0x10;
  puVar5 = &DAT_8040836c + iVar1;
  DAT_8040835a = (short)iVar4;
  *puVar5 = 7;
  DAT_80408348 = iVar6 + 1;
  (&DAT_8040836d)[iVar1] = 0;
  *(short *)(&DAT_8040836e + iVar1) = (short)iVar4;
  *(int *)(&DAT_80408370 + iVar1) = param_9;
  *(undefined4 *)(&DAT_80408374 + iVar1) = 0xffffffff;
  *(undefined4 *)(&DAT_80408378 + iVar1) = 0xffffffff;
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4994c,0,iVar4,
                puVar5,iVar6,&DAT_80408348,in_r9,in_r10);
    uVar3 = 0xfffffffd;
  }
  else if (*(char *)(param_9 + 1) == '\x01') {
    uVar3 = *(undefined4 *)(param_9 + 0x14);
  }
  else if (*(char *)(param_9 + 1) == '\x03') {
    *(undefined1 *)(param_9 + 1) = 1;
    uVar3 = *(undefined4 *)(param_9 + 0x14);
  }
  else if (*(int *)(param_9 + 4) == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49924,0,iVar4,
                puVar5,iVar6,&DAT_80408348,in_r9,in_r10);
    uVar3 = 0xffffffff;
  }
  else {
    zz_026d658_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 4));
    *(undefined1 *)(param_9 + 3) = 1;
    uVar2 = DAT_8040835a;
    iVar6 = DAT_80408348 >> 0x1f;
    iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
    iVar1 = iVar6 * 0x10;
    DAT_80408348 = iVar6 + 1;
    (&DAT_8040836c)[iVar1] = 7;
    (&DAT_8040836d)[iVar1] = 1;
    *(undefined2 *)(&DAT_8040836e + iVar1) = uVar2;
    *(int *)(&DAT_80408370 + iVar1) = param_9;
    *(undefined4 *)(&DAT_80408374 + iVar1) = 0xffffffff;
    *(undefined4 *)(&DAT_80408378 + iVar1) = 0xffffffff;
    uVar3 = *(undefined4 *)(param_9 + 0x14);
  }
  return uVar3;
}



// ==== 802729e4  zz_02729e4_ ====

int zz_02729e4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,uint param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if ((param_11 & 0x1f) == 0) {
    iVar1 = zz_0272a20_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11);
  }
  else {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd498f8,param_10
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = -3;
  }
  return iVar1;
}



// ==== 80272a20  zz_0272a20_ ====

int zz_0272a20_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11)

{
  undefined2 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  
  puVar9 = &DAT_80408348;
  uVar10 = 0x802b0000;
  iVar8 = DAT_80408348 >> 0x1f;
  iVar6 = DAT_80408354 + 1;
  iVar8 = (iVar8 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar8) >> 0x1c) - iVar8;
  iVar2 = iVar8 * 0x10;
  puVar7 = &DAT_8040836c + iVar2;
  DAT_80408354 = (short)iVar6;
  *puVar7 = 4;
  (&DAT_8040836d)[iVar2] = 0;
  DAT_80408348 = iVar8 + 1;
  *(short *)(&DAT_8040836e + iVar2) = (short)iVar6;
  *(int *)(&DAT_80408370 + iVar2) = param_9;
  *(int *)(&DAT_80408374 + iVar2) = param_10;
  *(int *)(&DAT_80408378 + iVar2) = param_11;
  if (param_9 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd498c4,param_10
                ,param_11,iVar6,puVar7,iVar8,&DAT_80408348,0x802b0000);
    iVar2 = -3;
  }
  else if (param_10 < 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4989c,param_10
                ,param_11,iVar6,puVar7,iVar8,&DAT_80408348,0x802b0000);
    iVar2 = -3;
  }
  else if (param_11 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49870,param_10
                ,0,iVar6,puVar7,iVar8,&DAT_80408348,0x802b0000);
    iVar2 = -3;
  }
  else if (*(char *)(param_9 + 1) == '\x02') {
    iVar2 = 0;
  }
  else if (*(int *)(param_9 + 8) == 0) {
    uVar5 = 0;
    piVar3 = zz_02774e0_(param_11,param_10 << 0xb,0);
    if (piVar3 == (int *)0x0) {
      iVar2 = -2;
    }
    else {
      *(int *)(param_9 + 0x24) = param_11;
      *(int *)(param_9 + 0x28) = param_10 << 0xb;
      uVar11 = zz_026960c_();
      uVar4 = extraout_r4;
      if (DAT_8040846c == 1) {
        uVar11 = zz_0272028_(*(uint *)(param_9 + 0x24),*(int *)(param_9 + 0x28));
        uVar4 = extraout_r4_00;
      }
      iVar2 = zz_026d7dc_(*(int *)(param_9 + 4));
      if (iVar2 != 1) {
        zz_026d564_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 4),uVar4,uVar5,iVar6,puVar7,iVar8,puVar9,uVar10);
      }
      uVar11 = zz_026960c_();
      *(int *)(param_9 + 0x18) = *(int *)(param_9 + 0x30) + *(int *)(param_9 + 0x14);
      iVar2 = *(int *)(param_9 + 0xc) - *(int *)(param_9 + 0x14);
      if (param_10 < iVar2) {
        iVar2 = param_10;
      }
      *(int *)(param_9 + 0x1c) = iVar2;
      iVar2 = 0;
      *(undefined4 *)(param_9 + 0x20) = 0;
      if (*(int *)(param_9 + 0x1c) == 0) {
        *(undefined1 *)(param_9 + 1) = 3;
      }
      else {
        uVar11 = zz_026d510_(*(int *)(param_9 + 4),-1);
        zz_026ce20_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 4),piVar3);
        zz_026cec0_(*(int *)(param_9 + 4),*(undefined4 *)(param_9 + 0x2c));
        *(undefined1 *)(param_9 + 1) = 2;
        *(undefined1 *)(param_9 + 3) = 0;
        uVar11 = zz_026ceb0_(*(int *)(param_9 + 4),0);
        zz_026d78c_(*(int *)(param_9 + 4),*(undefined4 *)(param_9 + 0x14));
        zz_026d6c8_(*(int *)(param_9 + 4),*(undefined4 *)(param_9 + 0x1c));
        iVar2 = *(int *)(param_9 + 0x1c);
      }
      uVar11 = zz_02695d4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      if (iVar2 < 1) {
        uVar11 = (**(code **)(*piVar3 + 0xc))(piVar3);
      }
      else {
        *(int **)(param_9 + 8) = piVar3;
      }
      *(undefined1 *)(param_9 + 2) = 0;
      zz_02695d4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar1 = DAT_80408354;
      iVar6 = DAT_80408348 >> 0x1f;
      iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
      iVar8 = iVar6 * 0x10;
      DAT_80408348 = iVar6 + 1;
      (&DAT_8040836c)[iVar8] = 4;
      (&DAT_8040836d)[iVar8] = 1;
      *(undefined2 *)(&DAT_8040836e + iVar8) = uVar1;
      *(int *)(&DAT_80408370 + iVar8) = param_9;
      *(int *)(&DAT_80408374 + iVar8) = param_10;
      *(int *)(&DAT_80408378 + iVar8) = param_11;
    }
  }
  else {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49848,param_10
                ,param_11,iVar6,puVar7,iVar8,&DAT_80408348,0x802b0000);
    iVar2 = -1;
  }
  return iVar2;
}



// ==== 80272ce4  zz_0272ce4_ ====

void zz_0272ce4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80408870;
  iVar1 = 0;
  do {
    if (*pcVar2 == '\x01') {
      param_1 = zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar2);
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x44;
  } while (iVar1 < 0x10);
  return;
}



// ==== 80272d40  zz_0272d40_ ====

void zz_0272d40_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                void *param_9)

{
  undefined2 uVar1;
  ushort uVar2;
  int iVar3;
  undefined4 *extraout_r4;
  undefined4 *extraout_r4_00;
  undefined4 *puVar4;
  undefined4 extraout_r4_01;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined *puVar10;
  undefined8 uVar11;
  
  puVar9 = (undefined4 *)&DAT_8040836c;
  iVar8 = 0;
  iVar6 = DAT_80408348 >> 0x1f;
  iVar5 = DAT_80408352 + 1;
  puVar7 = (undefined *)0xffffffff;
  iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
  iVar3 = iVar6 * 0x10;
  puVar10 = &DAT_8040836c + iVar3;
  DAT_80408348 = iVar6 + 1;
  DAT_80408352 = (short)iVar5;
  *puVar10 = 3;
  (&DAT_8040836d)[iVar3] = 0;
  *(short *)(&DAT_8040836e + iVar3) = (short)iVar5;
  *(void **)(&DAT_80408370 + iVar3) = param_9;
  *(undefined4 *)(&DAT_80408374 + iVar3) = 0xffffffff;
  *(undefined4 *)(&DAT_80408378 + iVar3) = 0xffffffff;
  if (param_9 != (void *)0x0) {
    puVar4 = &DAT_80408348;
    if (*(char *)((int)param_9 + 1) == '\x02') {
      iVar6 = DAT_80408348 >> 0x1f;
      iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
      iVar5 = DAT_80408356 + 1;
      iVar3 = iVar6 * 0x10;
      puVar9 = (undefined4 *)(&DAT_8040836c + iVar3);
      *(undefined1 *)puVar9 = 5;
      DAT_80408348 = iVar6 + 1;
      (&DAT_8040836d)[iVar3] = 0;
      DAT_80408356 = (ushort)iVar5;
      *(ushort *)(&DAT_8040836e + iVar3) = DAT_80408356;
      *(void **)(&DAT_80408370 + iVar3) = param_9;
      *(undefined4 *)(&DAT_80408374 + iVar3) = 0xffffffff;
      *(undefined4 *)(&DAT_80408378 + iVar3) = 0xffffffff;
      if (param_9 == (void *)0x0) {
        param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              -0x7fd499c4,&DAT_80408348,iVar5,iVar6,0xffffffff,0,puVar9,puVar10);
        puVar4 = extraout_r4;
      }
      else {
        puVar4 = &DAT_80408348;
        if (*(char *)((int)param_9 + 1) != '\x01') {
          if (*(char *)((int)param_9 + 1) == '\x03') {
            *(undefined1 *)((int)param_9 + 1) = 1;
          }
          else if (*(int *)((int)param_9 + 4) == 0) {
            param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  -0x7fd499a0,&DAT_80408348,iVar5,iVar6,0xffffffff,0,puVar9,puVar10)
            ;
            puVar4 = extraout_r4_00;
          }
          else {
            zz_026d564_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)((int)param_9 + 4),&DAT_80408348,iVar5,iVar6,0xffffffff,0,puVar9,
                        puVar10);
            uVar11 = zz_026960c_();
            iVar3 = zz_026d770_(*(int *)((int)param_9 + 4));
            *(int *)((int)param_9 + 0x20) = iVar3 - *(int *)((int)param_9 + 0x14);
            if ((*(int *)((int)param_9 + 8) != 0) && (*(char *)((int)param_9 + 2) == '\0')) {
              if (DAT_8040846c == 1) {
                zz_0272028_(*(uint *)((int)param_9 + 0x24),*(int *)((int)param_9 + 0x28));
              }
              uVar11 = (**(code **)(**(int **)((int)param_9 + 8) + 0xc))();
              *(undefined4 *)((int)param_9 + 8) = 0;
            }
            *(undefined1 *)((int)param_9 + 1) = 1;
            param_1 = zz_02695d4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
            uVar2 = DAT_80408356;
            puVar9 = &DAT_80408348;
            iVar6 = 5;
            iVar5 = 1;
            puVar4 = (undefined4 *)(uint)DAT_80408356;
            iVar8 = DAT_80408348 >> 0x1f;
            iVar8 = (iVar8 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar8) >> 0x1c) - iVar8;
            iVar3 = iVar8 * 0x10;
            puVar7 = &DAT_8040836c + iVar3;
            DAT_80408348 = iVar8 + 1;
            *puVar7 = 5;
            (&DAT_8040836d)[iVar3] = 1;
            *(ushort *)(&DAT_8040836e + iVar3) = uVar2;
            *(void **)(&DAT_80408370 + iVar3) = param_9;
            *(undefined4 *)(&DAT_80408374 + iVar3) = 0xffffffff;
            *(undefined4 *)(&DAT_80408378 + iVar3) = 0xffffffff;
          }
        }
      }
    }
    if (*(int *)((int)param_9 + 4) != 0) {
      uVar11 = zz_026d7e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)((int)param_9 + 4),puVar4,iVar5,iVar6,puVar7,iVar8,puVar9,puVar10
                          );
      zz_026db58_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(undefined1 **)((int)param_9 + 4),extraout_r4_01,iVar5,iVar6,puVar7,iVar8,puVar9,
                  puVar10);
    }
    gnt4_memset(param_9,0,0x44);
    uVar1 = DAT_80408352;
    iVar6 = DAT_80408348 >> 0x1f;
    iVar6 = (iVar6 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar6) >> 0x1c) - iVar6;
    iVar3 = iVar6 * 0x10;
    DAT_80408348 = iVar6 + 1;
    (&DAT_8040836c)[iVar3] = 3;
    (&DAT_8040836d)[iVar3] = 1;
    *(undefined2 *)(&DAT_8040836e + iVar3) = uVar1;
    *(void **)(&DAT_80408370 + iVar3) = param_9;
    *(undefined4 *)(&DAT_80408374 + iVar3) = 0xffffffff;
    *(undefined4 *)(&DAT_80408378 + iVar3) = 0xffffffff;
  }
  return;
}



// ==== 80273000  zz_0273000_ ====

undefined1 *
zz_0273000_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10)

{
  undefined2 uVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined1 *puVar11;
  int iVar12;
  uint local_128;
  int local_124;
  undefined4 local_120;
  undefined1 auStack_11c [268];
  
  puVar9 = &DAT_80408348;
  pcVar10 = &DAT_80408870;
  puVar11 = (undefined1 *)0x0;
  iVar7 = DAT_80408348 >> 0x1f;
  iVar7 = (iVar7 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar7) >> 0x1c) - iVar7;
  iVar4 = DAT_80408350 + 1;
  iVar12 = iVar7 * 0x10;
  DAT_80408348 = iVar7 + 1;
  puVar5 = &DAT_8040836c + iVar12;
  *puVar5 = 2;
  iVar6 = 0;
  (&DAT_8040836d)[iVar12] = 0;
  DAT_80408350 = (ushort)iVar4;
  *(ushort *)(&DAT_8040836e + iVar12) = DAT_80408350;
  *(int *)(&DAT_80408370 + iVar12) = param_9;
  *(int *)(&DAT_80408374 + iVar12) = param_10;
  *(undefined4 *)(&DAT_80408378 + iVar12) = 0xffffffff;
  iVar12 = 0x10;
  do {
    if (*pcVar10 == '\0') {
      puVar11 = &DAT_80408870 + iVar6 * 0x44;
      break;
    }
    pcVar10 = pcVar10 + 0x44;
    iVar6 = iVar6 + 1;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  if (puVar11 == (undefined1 *)0x0) {
    puVar11 = (undefined1 *)0x0;
  }
  else {
    uVar3 = 0x100;
    pcVar2 = zz_026ddec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)0x0,
                         0x100);
    *(char **)(puVar11 + 4) = pcVar2;
    if (pcVar2 == (char *)0x0) {
      param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            -0x7fd497a4,uVar3,iVar4,puVar5,iVar6,iVar7,puVar9,pcVar10);
      puVar11 = (undefined1 *)0x0;
    }
    else {
      puVar11[1] = 1;
      *(undefined4 *)(puVar11 + 0x18) = 0;
      *(undefined4 *)(puVar11 + 0x1c) = 0;
      *(undefined4 *)(puVar11 + 0x20) = 0;
      *(undefined4 *)(puVar11 + 0x2c) = 0x200;
      puVar11[2] = 0;
      *(undefined4 *)(puVar11 + 8) = 0;
      puVar11[3] = 0;
      *puVar11 = 1;
    }
  }
  if (puVar11 != (undefined1 *)0x0) {
    puVar8 = &local_128;
    iVar12 = zz_0272048_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10,(int)auStack_11c,&local_120,&local_124,puVar8,puVar9,pcVar10);
    if (iVar12 < 0) {
      iVar12 = -3;
    }
    else {
      *(int *)(puVar11 + 0x30) = local_124;
      iVar12 = *(int *)(&DAT_80408470 + param_9 * 4);
      *(undefined4 *)(puVar11 + 0x34) = local_120;
      *(int *)(puVar11 + 0x38) = iVar12 + 0x10;
      *(uint *)(puVar11 + 0x40) = local_128;
      *(int *)(puVar11 + 0x3c) = local_124;
      *(undefined4 *)(puVar11 + 0x14) = 0;
      param_1 = zz_026da40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(puVar11 + 4),*(undefined4 *)(puVar11 + 0x38),
                            *(undefined4 *)(puVar11 + 0x34),*(undefined4 *)(puVar11 + 0x3c),
                            *(int *)(puVar11 + 0x40),puVar8,puVar9,pcVar10);
      iVar12 = 0;
      *(uint *)(puVar11 + 0xc) = local_128;
      *(uint *)(puVar11 + 0x10) = local_128 << 0xb;
    }
    if (iVar12 < 0) {
      zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar11);
      puVar11 = (undefined1 *)0x0;
    }
  }
  uVar1 = DAT_80408350;
  iVar7 = DAT_80408348 >> 0x1f;
  iVar7 = (iVar7 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar7) >> 0x1c) - iVar7;
  iVar12 = iVar7 * 0x10;
  (&DAT_8040836c)[iVar12] = 2;
  (&DAT_8040836d)[iVar12] = 1;
  *(undefined2 *)(&DAT_8040836e + iVar12) = uVar1;
  *(int *)(&DAT_80408370 + iVar12) = param_9;
  *(int *)(&DAT_80408374 + iVar12) = param_10;
  *(undefined4 *)(&DAT_80408378 + iVar12) = 0xffffffff;
  DAT_80408348 = iVar7 + 1;
  return puVar11;
}



// ==== 8027327c  zz_027327c_ ====

undefined1 *
zz_027327c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10)

{
  undefined2 uVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  int extraout_r4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  char *pcVar10;
  undefined1 *puVar11;
  int iVar12;
  undefined8 uVar13;
  
  puVar9 = &DAT_80408348;
  pcVar10 = &DAT_80408870;
  puVar11 = (undefined1 *)0x0;
  iVar3 = -1;
  iVar8 = DAT_80408348 >> 0x1f;
  iVar8 = (iVar8 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar8) >> 0x1c) - iVar8;
  iVar5 = DAT_8040834e + 1;
  iVar12 = iVar8 * 0x10;
  DAT_80408348 = iVar8 + 1;
  puVar6 = &DAT_8040836c + iVar12;
  *puVar6 = 1;
  iVar7 = 0;
  (&DAT_8040836d)[iVar12] = 0;
  DAT_8040834e = (ushort)iVar5;
  *(ushort *)(&DAT_8040836e + iVar12) = DAT_8040834e;
  *(int *)(&DAT_80408370 + iVar12) = param_9;
  *(undefined4 *)(&DAT_80408374 + iVar12) = param_10;
  *(undefined4 *)(&DAT_80408378 + iVar12) = 0xffffffff;
  iVar12 = 0x10;
  do {
    if (*pcVar10 == '\0') {
      iVar3 = iVar7 * 0x44;
      puVar11 = &DAT_80408870 + iVar3;
      break;
    }
    pcVar10 = pcVar10 + 0x44;
    iVar7 = iVar7 + 1;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  if (puVar11 == (undefined1 *)0x0) {
    puVar11 = (undefined1 *)0x0;
  }
  else {
    uVar4 = 0x100;
    pcVar2 = zz_026ddec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)0x0,
                         0x100);
    *(char **)(puVar11 + 4) = pcVar2;
    if (pcVar2 == (char *)0x0) {
      param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            -0x7fd497a4,uVar4,iVar5,puVar6,iVar7,iVar8,puVar9,pcVar10);
      puVar11 = (undefined1 *)0x0;
      iVar3 = extraout_r4;
    }
    else {
      iVar3 = 1;
      puVar11[1] = 1;
      *(undefined4 *)(puVar11 + 0x18) = 0;
      *(undefined4 *)(puVar11 + 0x1c) = 0;
      *(undefined4 *)(puVar11 + 0x20) = 0;
      *(undefined4 *)(puVar11 + 0x2c) = 0x200;
      puVar11[2] = 0;
      *(undefined4 *)(puVar11 + 8) = 0;
      puVar11[3] = 0;
      *puVar11 = 1;
    }
  }
  if (puVar11 != (undefined1 *)0x0) {
    if (param_9 == 0) {
      uVar13 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           -0x7fd4976c,iVar3,iVar5,puVar6,iVar7,iVar8,puVar9,pcVar10);
      iVar12 = -1;
    }
    else {
      *(undefined4 *)(puVar11 + 0x34) = param_10;
      *(int *)(puVar11 + 0x38) = param_9;
      *(undefined4 *)(puVar11 + 0x40) = 0xfffff;
      *(undefined4 *)(puVar11 + 0x3c) = 0;
      *(undefined4 *)(puVar11 + 0xc) = 0xfffff;
      *(undefined4 *)(puVar11 + 0x10) = 0x7ffff800;
      *(undefined4 *)(puVar11 + 0x14) = 0;
      uVar13 = zz_026da40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(puVar11 + 4),*(undefined4 *)(puVar11 + 0x38),
                           *(undefined4 *)(puVar11 + 0x34),*(undefined4 *)(puVar11 + 0x30),
                           *(int *)(puVar11 + 0xc),iVar8,puVar9,pcVar10);
      iVar12 = 0;
    }
    if (iVar12 < 0) {
      zz_0272d40_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar11);
      puVar11 = (undefined1 *)0x0;
    }
  }
  uVar1 = DAT_8040834e;
  iVar8 = DAT_80408348 >> 0x1f;
  iVar8 = (iVar8 * 0x10 | (uint)(DAT_80408348 * 0x10000000 + iVar8) >> 0x1c) - iVar8;
  iVar12 = iVar8 * 0x10;
  (&DAT_8040836c)[iVar12] = 1;
  (&DAT_8040836d)[iVar12] = 1;
  *(undefined2 *)(&DAT_8040836e + iVar12) = uVar1;
  *(int *)(&DAT_80408370 + iVar12) = param_9;
  *(undefined4 *)(&DAT_80408374 + iVar12) = param_10;
  *(undefined4 *)(&DAT_80408378 + iVar12) = 0xffffffff;
  DAT_80408348 = iVar8 + 1;
  return puVar11;
}



// ==== 802734c8  zz_02734c8_ ====

int zz_02734c8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,uint param_12,
               undefined4 *param_13,uint param_14,int param_15,uint param_16)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined1 *puVar13;
  int *piVar14;
  short *psVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  uint uVar19;
  undefined8 uVar20;
  
  iVar18 = 0;
  psVar15 = (short *)0x0;
  iVar17 = 0;
  piVar14 = (int *)0x0;
  if (param_9 == DAT_8040833c) {
    if (DAT_80408340 == 0) {
      param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            -0x7fd49abc,0x80410000,0x802b0000,param_12,param_13,param_14,param_15,
                            param_16);
      iVar7 = -3;
    }
    else {
      iVar7 = (int)*(char *)(DAT_80408340 + 1);
    }
    if (iVar7 == 3) {
      iVar16 = *(int *)(&DAT_80408470 + param_9 * 4);
      if (*(char *)(iVar16 + 0xf) == '\x01') {
        piVar14 = (int *)(iVar16 + 0x118);
        iVar17 = iVar16 + 0x11c;
      }
      else {
        psVar15 = (short *)(iVar16 + 0x118);
        iVar18 = iVar16 + 0x11a;
      }
      if (*(int *)(iVar16 + 8) == 0) {
        puVar10 = &DAT_802b68fc;
        uVar12 = 3;
        iVar8 = gnt4_memcmp(DAT_80408cb0,&DAT_802b68fc,3);
        if (iVar8 != 0) {
          uVar20 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               -0x7fd49700,puVar10,uVar12,param_12,param_13,param_14,param_15,
                               param_16);
          zz_0273888_(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
          return 4;
        }
        uVar5 = CONCAT11(*(undefined1 *)((int)DAT_80408cb0 + 5),
                         *(undefined1 *)((int)DAT_80408cb0 + 4));
        param_12 = CONCAT13(*(undefined1 *)((int)DAT_80408cb0 + 7),
                            CONCAT12(*(byte *)((int)DAT_80408cb0 + 6),uVar5));
        if (0x10000 < (int)param_12) {
          uVar20 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               -0x7fd496cc,(uint)*(byte *)((int)DAT_80408cb0 + 6),DAT_80408cb0,
                               param_12,param_13,param_14,param_15,param_16);
          zz_0273888_(uVar20,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
          return 4;
        }
        *(ushort *)(iVar16 + 0xc) = uVar5;
        *(uint *)(iVar16 + 8) = (uint)uVar5;
        if (*(char *)(iVar16 + 0xf) == '\x01') {
          *(int *)(iVar16 + 4) = (*(int *)(iVar16 + 8) + 1) * 4 + 0x11c;
        }
        else {
          *(uint *)(iVar16 + 4) = (*(int *)(iVar16 + 8) + 1) * 2 + 0x11aU & 0xfffffffc;
        }
        if (*(char *)(iVar16 + 0xf) == '\x01') {
          *piVar14 = (CONCAT13(*(char *)((int)DAT_80408cb0 + 0xb),
                               CONCAT12(*(undefined1 *)((int)DAT_80408cb0 + 10),
                                        CONCAT11(*(byte *)((int)DAT_80408cb0 + 9),
                                                 *(char *)((int)DAT_80408cb0 + 8)))) >> 0xb) +
                     (uint)(*(char *)((int)DAT_80408cb0 + 0xb) < '\0' &&
                           ((*(byte *)((int)DAT_80408cb0 + 9) & 7) != 0 ||
                           *(char *)((int)DAT_80408cb0 + 8) != '\0'));
        }
        else {
          *psVar15 = (short)(CONCAT13(*(char *)((int)DAT_80408cb0 + 0xb),
                                      CONCAT12(*(undefined1 *)((int)DAT_80408cb0 + 10),
                                               CONCAT11(*(byte *)((int)DAT_80408cb0 + 9),
                                                        *(char *)((int)DAT_80408cb0 + 8)))) >> 0xb)
                     + (ushort)(*(char *)((int)DAT_80408cb0 + 0xb) < '\0' &&
                               ((*(byte *)((int)DAT_80408cb0 + 9) & 7) != 0 ||
                               *(char *)((int)DAT_80408cb0 + 8) != '\0'));
        }
        iVar8 = 3;
      }
      else {
        iVar8 = 1;
      }
      iVar9 = iVar8 << 2;
      iVar6 = (DAT_80408cb4 << 0xb) >> 2;
      uVar19 = (uint)((iVar6 + 1) - iVar8) >> 1;
      if (iVar8 < iVar6) {
        do {
          if (*(char *)(iVar16 + 0xf) == '\x01') {
            puVar13 = (undefined1 *)((int)DAT_80408cb0 + iVar9);
            bVar1 = puVar13[1];
            iVar4 = DAT_80408344 * 4;
            bVar2 = puVar13[2];
            bVar3 = puVar13[3];
            param_15 = CONCAT13(bVar3,CONCAT12(bVar2,CONCAT11(bVar1,*puVar13)));
            uVar11 = param_15 + 0x7ff;
            DAT_80408344 = DAT_80408344 + 1;
            *(uint *)(iVar17 + iVar4) =
                 ((int)uVar11 >> 0xb) + (uint)((int)uVar11 < 0 && (uVar11 & 0x7ff) != 0);
          }
          else {
            puVar13 = (undefined1 *)((int)DAT_80408cb0 + iVar9);
            bVar1 = puVar13[1];
            iVar4 = DAT_80408344 * 2;
            bVar2 = puVar13[2];
            bVar3 = puVar13[3];
            param_15 = CONCAT13(bVar3,CONCAT12(bVar2,CONCAT11(bVar1,*puVar13)));
            uVar11 = param_15 + 0x7ff;
            DAT_80408344 = DAT_80408344 + 1;
            *(ushort *)(iVar18 + iVar4) =
                 (short)((int)uVar11 >> 0xb) + (ushort)((int)uVar11 < 0 && (uVar11 & 0x7ff) != 0);
          }
          param_16 = (uint)bVar3;
          param_12 = (uint)bVar2;
          param_14 = (uint)bVar1;
          param_13 = &DAT_80408344;
          if (*(int *)(iVar16 + 8) <= DAT_80408344) {
            iVar7 = 3;
            param_1 = zz_0273888_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
            break;
          }
          iVar9 = iVar9 + 8;
          iVar8 = iVar8 + 2;
          uVar19 = uVar19 - 1;
        } while (uVar19 != 0);
      }
      if (iVar6 <= iVar8) {
        if (((uint)DAT_80408cb0 & 0x1f) == 0) {
          iVar17 = zz_0272a20_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_80408340,DAT_80408cb4,(int)DAT_80408cb0);
        }
        else {
          param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                -0x7fd498f8,DAT_80408cb4,DAT_80408cb0,param_12,param_13,param_14,
                                param_15,param_16);
          iVar17 = -3;
        }
        if (iVar17 < 0) {
          iVar7 = 4;
          zz_0273888_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        }
        else {
          iVar7 = (int)*(char *)(DAT_80408340 + 1);
        }
      }
    }
  }
  else {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49738,
                0x80410000,0x802b0000,param_12,param_13,param_14,param_15,param_16);
    iVar7 = -3;
  }
  return iVar7;
}



// ==== 80273868  zz_0273868_ ====

void zz_0273868_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,uint param_12,
                undefined4 *param_13,uint param_14,int param_15,uint param_16)

{
  zz_02734c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80273888  zz_0273888_ ====

void zz_0273888_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80408340);
  DAT_80408340 = (void *)0x0;
  DAT_8040833c = 0xffffffff;
  DAT_80408344 = 0;
  DAT_80408cb4 = 0;
  return;
}



// ==== 802738dc  zz_02738dc_ ====

int zz_02738dc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11,int param_12,uint param_13,uint *param_14,
               uint param_15,uint param_16,undefined1 param_17)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint local_38;
  uint uStack_34;
  uint local_30 [3];
  
  uVar5 = 0x802b0000;
  local_38 = param_13;
  if (param_15 == 0) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd49698,param_10
                ,param_11,param_12,0x802b0000,param_14,0,param_16);
    iVar1 = -3;
  }
  else if ((int)param_16 < 1) {
    zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd4966c,param_10
                ,param_11,param_12,0x802b0000,param_14,param_15,param_16);
    iVar1 = -3;
  }
  else {
    iVar2 = param_11;
    iVar4 = param_12;
    puVar6 = param_14;
    uVar7 = param_15;
    uVar8 = param_16;
    if ((param_9 < 0) || (0xff < param_9)) {
      param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            -0x7fd49644,param_10,param_11,param_12,0x802b0000,param_14,param_15,
                            param_16);
      iVar1 = -3;
    }
    else if (param_14 == (uint *)0x0) {
      param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            -0x7fd4960c,param_10,param_11,param_12,0x802b0000,0,param_15,param_16);
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
    if (-1 < iVar1) {
      if (DAT_8040833c < 0) {
        DAT_80408344 = 0;
        uVar3 = 0x11c;
        DAT_8040833c = param_9;
        gnt4_memset(param_14,0,0x11c);
        *(uint **)(&DAT_80408470 + param_9 * 4) = param_14;
        *param_14 = 0;
        if (param_12 == 0) {
          DAT_80408340 = zz_0273000_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,param_10,param_11);
          if (DAT_80408340 == (undefined1 *)0x0) {
            zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd495b0,
                        0x80410000,uVar3,iVar4,uVar5,puVar6,uVar7,uVar8);
            return -1;
          }
          puVar6 = &uStack_34;
          iVar2 = zz_0272048_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_10,param_11,(int)(param_14 + 4),&local_38,(int *)local_30,puVar6
                              ,uVar7,uVar8);
          if (iVar2 < 0) {
            return iVar2;
          }
          param_14[0x45] = local_30[0];
        }
        else {
          DAT_80408340 = zz_027327c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,param_12,local_38);
          if (DAT_80408340 == (undefined1 *)0x0) {
            zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd495b0,
                        0x80410000,uVar3,iVar4,uVar5,puVar6,uVar7,uVar8);
            return -1;
          }
          param_1 = zz_0238cbc_((int)(param_14 + 4),param_12,0x100);
        }
        param_14[0x44] = local_38;
        *(undefined1 *)((int)param_14 + 0xe) = 0;
        DAT_80408cb4 = ((int)param_16 >> 0xb) + (uint)((int)param_16 < 0 && (param_16 & 0x7ff) != 0)
        ;
        *(undefined1 *)((int)param_14 + 0xf) = param_17;
        DAT_80408cb0 = param_15;
        if ((param_15 & 0x1f) == 0) {
          iVar1 = zz_0272a20_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)DAT_80408340,DAT_80408cb4,param_15);
        }
        else {
          param_1 = zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                -0x7fd498f8,DAT_80408cb4,0x80410000,0x80410000,0,puVar6,uVar7,uVar8)
          ;
          iVar1 = -3;
        }
        if (iVar1 < 0) {
          zz_0272d40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80408340);
        }
        else {
          iVar1 = 0;
          param_14[2] = 0;
        }
      }
      else {
        zz_026a274_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd495e0,
                    &DAT_8040833c,iVar2,iVar4,uVar5,puVar6,uVar7,uVar8);
        iVar1 = -1;
      }
    }
  }
  return iVar1;
}



// ==== 80273b2c  zz_0273b2c_ ====

void zz_0273b2c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,uint param_11,uint *param_12)

{
  zz_02738dc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,0,param_10,
              param_11,param_12,0x80408cc0,0x800,0);
  return;
}



// ==== 80273b7c  zz_0273b7c_ ====

void zz_0273b7c_(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    DAT_8040ad38 = 0;
    DAT_8040ad3c = 0;
    return;
  }
  DAT_8040ad38 = param_1;
  DAT_8040ad3c = param_2;
  return;
}



// ==== 80273bb0  zz_0273bb0_ ====

undefined4 zz_0273bb0_(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 3;
  if (param_1 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsGetStat__1_handle_error_802b7338,0);
    }
    uVar1 = 3;
  }
  else if (*(code **)(*param_1 + 0x2c) == (code *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsGetStat__2_vtbl_error_802b7354,0);
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x2c))(param_1[1]);
  }
  return uVar1;
}



// ==== 80273c70  zz_0273c70_ ====

void zz_0273c70_(void)

{
  code *pcVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_8040ae7c;
  iVar2 = 0;
  do {
    if (((undefined4 *)*piVar3 != (undefined4 *)0x0) &&
       (pcVar1 = *(code **)*piVar3, pcVar1 != (code *)0x0)) {
      (*pcVar1)();
    }
    iVar2 = iVar2 + 1;
    piVar3 = piVar3 + 4;
  } while (iVar2 < 0x20);
  return;
}



// ==== 80273cd8  zz_0273cd8_ ====

undefined4 zz_0273cd8_(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsReqRd__1_handle_error_802b73dc,0);
    }
    uVar1 = 0;
  }
  else if (*(code **)(*param_1 + 0x20) == (code *)0x0) {
    uVar1 = 0;
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsReqRd__2_vtbl_error_802b73f8,0);
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x20))(param_1[1]);
  }
  return uVar1;
}



// ==== 80273d98  zz_0273d98_ ====

undefined4 zz_0273d98_(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsSeek__1_handle_error_802b7410,0);
    }
    uVar1 = 0;
  }
  else if (*(code **)(*param_1 + 0x18) == (code *)0x0) {
    uVar1 = 0;
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsSeek__2_vtbl_error_802b742c,0);
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x18))(param_1[1]);
  }
  return uVar1;
}



// ==== 80273e58  zz_0273e58_ ====

undefined4 zz_0273e58_(int *param_1)

{
  undefined4 uVar1;
  
  if (param_1 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsTell__1_handle_error_802b7444,0);
    }
    uVar1 = 0;
  }
  else if (*(code **)(*param_1 + 0x1c) == (code *)0x0) {
    uVar1 = 0;
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsTell__2_vtbl_error_802b7460,0);
    }
  }
  else {
    uVar1 = (**(code **)(*param_1 + 0x1c))(param_1[1]);
  }
  return uVar1;
}



// ==== 80273f18  zz_0273f18_ ====

void zz_0273f18_(int *param_1)

{
  if (param_1 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsClose__1_handle_error_802b7478,0);
    }
  }
  else if (*(code **)(*param_1 + 0x14) == (code *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsClose__2_vtbl_error_802b7494,0);
    }
  }
  else {
    (**(code **)(*param_1 + 0x14))(param_1[1]);
    param_1[1] = 0;
    *param_1 = 0;
  }
  return;
}



// ==== 80273fd4  zz_0273fd4_ ====

int * zz_0273fd4_(char *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  code *pcVar2;
  char *pcVar3;
  size_t sVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  int iVar8;
  code *pcVar9;
  undefined4 *puVar10;
  uint uVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  char local_288 [300];
  char local_15c [300];
  
  if (param_1 == (char *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsOpen__1_illegal_file_name_802b74ac,0);
    }
    return (int *)0x0;
  }
  pcVar7 = local_15c;
  iVar8 = 0;
  iVar13 = 99;
  pcVar3 = param_1;
  while ((cVar1 = *pcVar3, iVar14 = iVar8, cVar1 != ':' && (cVar1 != '\0'))) {
    *pcVar7 = cVar1;
    cVar1 = pcVar3[1];
    iVar14 = iVar8 + 1;
    if ((cVar1 == ':') || (cVar1 == '\0')) break;
    pcVar7[1] = cVar1;
    cVar1 = pcVar3[2];
    iVar14 = iVar8 + 2;
    if ((cVar1 == ':') || (cVar1 == '\0')) break;
    pcVar7[2] = cVar1;
    pcVar7 = pcVar7 + 3;
    iVar8 = iVar8 + 3;
    pcVar3 = pcVar3 + 3;
    iVar13 = iVar13 + -1;
    iVar14 = iVar8;
    if (iVar13 == 0) break;
  }
  if (param_1[iVar14] == '\0') {
    local_15c[iVar14] = '\0';
    sVar4 = strlen(local_15c);
    gnt4_memcpy(local_288,local_15c,sVar4 + 1);
    local_15c[0] = '\0';
  }
  else {
    local_15c[iVar14] = '\0';
    iVar14 = iVar14 + 1;
    if (iVar14 == 2) {
      iVar14 = 0;
      local_15c[0] = '\0';
    }
    iVar13 = 0x129 - iVar14;
    pcVar3 = param_1 + iVar14;
    iVar8 = iVar14;
    if (iVar14 < 0x129) {
      do {
        cVar1 = *pcVar3;
        if (cVar1 == '\0') break;
        pcVar3 = pcVar3 + 1;
        local_288[iVar8 - iVar14] = cVar1;
        iVar8 = iVar8 + 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
    }
    local_288[iVar8 - iVar14] = '\0';
    sVar4 = strlen(local_15c);
    pcVar3 = local_15c;
    for (iVar8 = sVar4 + 1; iVar8 != 0; iVar8 = iVar8 + -1) {
      cVar1 = *pcVar3;
      if (('`' < cVar1) && (cVar1 < '{')) {
        *pcVar3 = cVar1 + -0x20;
      }
      pcVar3 = pcVar3 + 1;
    }
  }
  if (local_288[0] == '\0') {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsOpen__1_illegal_file_name_802b74ac,0);
    }
    return (int *)0x0;
  }
  iVar13 = -0x7fbf4f84;
  iVar8 = 0;
  iVar14 = 4;
  do {
    iVar5 = iVar8;
    if (((((((*(int *)(iVar13 + 4) == 0) || (iVar5 = iVar8 + 1, *(int *)(iVar13 + 0xc) == 0)) ||
           (iVar5 = iVar8 + 2, *(int *)(iVar13 + 0x14) == 0)) ||
          ((iVar5 = iVar8 + 3, *(int *)(iVar13 + 0x1c) == 0 ||
           (iVar5 = iVar8 + 4, *(int *)(iVar13 + 0x24) == 0)))) ||
         ((iVar5 = iVar8 + 5, *(int *)(iVar13 + 0x2c) == 0 ||
          ((iVar5 = iVar8 + 6, *(int *)(iVar13 + 0x34) == 0 ||
           (iVar5 = iVar8 + 7, *(int *)(iVar13 + 0x3c) == 0)))))) ||
        (iVar5 = iVar8 + 8, *(int *)(iVar13 + 0x44) == 0)) ||
       (iVar5 = iVar8 + 9, *(int *)(iVar13 + 0x4c) == 0)) break;
    iVar13 = iVar13 + 0x50;
    iVar8 = iVar8 + 10;
    iVar14 = iVar14 + -1;
    iVar5 = iVar8;
  } while (iVar14 != 0);
  piVar6 = (int *)(iVar5 * 8 + -0x7fbf4f84);
  if (iVar5 == 0x28) {
    piVar6 = (int *)0x0;
  }
  if (piVar6 == (int *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsOpen__3_failed_handle_alloce_802b74cc,0);
    }
    return (int *)0x0;
  }
  if (local_15c[0] == '\0') {
    sVar4 = strlen(&DAT_8040ae70);
    if (DAT_8040ae70 == '\0') {
      local_15c[0] = '\0';
    }
    else {
      gnt4_memcpy(local_15c,&DAT_8040ae70,sVar4 + 1);
    }
    if (local_15c[0] == '\0') {
      iVar8 = 0;
      goto LAB_80274504;
    }
  }
  pcVar3 = local_15c;
  if (local_15c == (char *)0x0) {
    pcVar3 = &DAT_8040ae70;
  }
  sVar4 = strlen(pcVar3);
  puVar12 = &DAT_8040ae7c;
  uVar11 = 0;
  puVar10 = puVar12;
  do {
    iVar8 = gnt4_strncmp(pcVar3,(char *)(puVar10 + 1),sVar4);
    if (iVar8 == 0) {
      iVar8 = (&DAT_8040ae7c)[uVar11 * 4];
      goto LAB_802743a8;
    }
    uVar11 = uVar11 + 1;
    puVar10 = puVar10 + 4;
  } while (uVar11 < 0x20);
  iVar8 = 0;
LAB_802743a8:
  if (iVar8 == 0) {
    iVar8 = 0;
  }
  else if (*(code **)(iVar8 + 0x60) == (code *)0x0) {
    iVar8 = 0;
  }
  else {
    iVar8 = (**(code **)(iVar8 + 0x60))(0,100,0,0);
  }
  if (iVar8 == 1) {
    strcpy(&DAT_8040ad44,local_288);
    sprintf(local_288,s__s__s_802b6ab4,pcVar3,&DAT_8040ad44);
  }
  sVar4 = strlen(local_15c);
  uVar11 = 0;
  puVar10 = puVar12;
  do {
    iVar8 = gnt4_strncmp(local_15c,(char *)(puVar10 + 1),sVar4);
    if (iVar8 == 0) {
      iVar8 = (&DAT_8040ae7c)[uVar11 * 4];
      goto LAB_80274460;
    }
    uVar11 = uVar11 + 1;
    puVar10 = puVar10 + 4;
  } while (uVar11 < 0x20);
  iVar8 = 0;
LAB_80274460:
  if (iVar8 == 0) {
    sVar4 = strlen(&DAT_8040ae70);
    if (DAT_8040ae70 == '\0') {
      local_15c[0] = '\0';
    }
    else {
      gnt4_memcpy(local_15c,&DAT_8040ae70,sVar4 + 1);
    }
    sVar4 = strlen(local_15c);
    uVar11 = 0;
    do {
      iVar8 = gnt4_strncmp(local_15c,(char *)(puVar12 + 1),sVar4);
      if (iVar8 == 0) {
        iVar8 = (&DAT_8040ae7c)[uVar11 * 4];
        goto LAB_802744e8;
      }
      uVar11 = uVar11 + 1;
      puVar12 = puVar12 + 4;
    } while (uVar11 < 0x20);
    iVar8 = 0;
LAB_802744e8:
    if (iVar8 == 0) {
      iVar8 = 0;
    }
    else {
      strcpy(local_288,param_1);
    }
  }
LAB_80274504:
  *piVar6 = iVar8;
  pcVar2 = DAT_8040ad38;
  if (&stack0x00000000 == (undefined1 *)0x15c) {
    piVar6[1] = 0;
    *piVar6 = 0;
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(DAT_8040ad3c,s_cvFsOpen__2_illegal_device_name_802b74f0,0);
    }
    piVar6 = (int *)0x0;
  }
  else if (*piVar6 == 0) {
    piVar6[1] = 0;
    *piVar6 = 0;
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(DAT_8040ad3c,s_cvFsOpen__4_device_not_found_802b7510,0);
    }
    piVar6 = (int *)0x0;
  }
  else {
    pcVar9 = *(code **)(*piVar6 + 0x10);
    if (pcVar9 == (code *)0x0) {
      piVar6[1] = 0;
      *piVar6 = 0;
      if (pcVar2 != (code *)0x0) {
        (*pcVar2)(DAT_8040ad3c,s_cvFsOpen__5_vtbl_error_802b7530,0);
      }
      piVar6 = (int *)0x0;
    }
    else {
      iVar8 = (*pcVar9)(local_288,param_2,param_3);
      piVar6[1] = iVar8;
      pcVar2 = DAT_8040ad38;
      if (piVar6[1] == 0) {
        piVar6[1] = 0;
        *piVar6 = 0;
        if (pcVar2 != (code *)0x0) {
          (*pcVar2)(DAT_8040ad3c,s_cvFsOpen__6_open_failed_802b7548,0);
        }
        piVar6 = (int *)0x0;
      }
    }
  }
  return piVar6;
}



// ==== 80274638  zz_0274638_ ====

void zz_0274638_(char *param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  size_t __n;
  size_t sVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if (param_1 == (char *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsSetDefDev__1_illegal_device_n_802b7560,0);
    }
  }
  else {
    __n = strlen(param_1);
    if (__n == 0) {
      DAT_8040ae70 = 0;
    }
    else {
      sVar4 = strlen(param_1);
      pcVar5 = param_1;
      for (iVar3 = sVar4 + 1; iVar3 != 0; iVar3 = iVar3 + -1) {
        cVar1 = *pcVar5;
        if (('`' < cVar1) && (cVar1 < '{')) {
          *pcVar5 = cVar1 + -0x20;
        }
        pcVar5 = pcVar5 + 1;
      }
      puVar7 = &DAT_8040ae7c;
      iVar3 = 0;
      do {
        iVar6 = gnt4_strncmp(param_1,(char *)(puVar7 + 1),__n);
        if (iVar6 == 0) {
          bVar2 = true;
          goto LAB_80274718;
        }
        iVar3 = iVar3 + 1;
        puVar7 = puVar7 + 4;
      } while (iVar3 < 0x20);
      bVar2 = false;
LAB_80274718:
      if (bVar2) {
        gnt4_memcpy(&DAT_8040ae70,param_1,__n + 1);
      }
      else if (DAT_8040ad38 != (code *)0x0) {
        (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsSetDefDev__2_unknown_device_n_802b7588,0);
      }
    }
  }
  return;
}



// ==== 8027476c  zz_027476c_ ====

void zz_027476c_(char *param_1,undefined *param_2)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  
  if (param_1 == (char *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsAddDev__1_illegal_device_nam_802b75d4,0);
    }
  }
  else if (param_2 == (undefined *)0x0) {
    if (DAT_8040ad38 != (code *)0x0) {
      (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsAddDev__2_illegal_I_F_func_n_802b75f8,0);
    }
  }
  else {
    sVar3 = strlen(param_1);
    pcVar4 = param_1;
    for (iVar2 = sVar3 + 1; iVar2 != 0; iVar2 = iVar2 + -1) {
      cVar1 = *pcVar4;
      if (('`' < cVar1) && (cVar1 < '{')) {
        *pcVar4 = cVar1 + -0x20;
      }
      pcVar4 = pcVar4 + 1;
    }
    iVar2 = (*(code *)param_2)();
    sVar3 = strlen(param_1);
    puVar7 = &DAT_8040ae7c;
    uVar8 = 0;
    do {
      iVar5 = gnt4_strncmp(param_1,(char *)(puVar7 + 1),sVar3);
      if (iVar5 == 0) {
        iVar5 = (&DAT_8040ae7c)[uVar8 * 4];
        goto LAB_8027488c;
      }
      uVar8 = uVar8 + 1;
      puVar7 = puVar7 + 4;
    } while (uVar8 < 0x20);
    iVar5 = 0;
LAB_8027488c:
    if (iVar5 == 0) {
      puVar7 = &DAT_8040ae7c;
      iVar5 = 0;
      iVar9 = 4;
      do {
        iVar6 = iVar5;
        if (((((*(char *)(puVar7 + 1) == '\0') || (iVar6 = iVar5 + 1, *(char *)(puVar7 + 5) == '\0')
              ) || (iVar6 = iVar5 + 2, *(char *)(puVar7 + 9) == '\0')) ||
            ((iVar6 = iVar5 + 3, *(char *)(puVar7 + 0xd) == '\0' ||
             (iVar6 = iVar5 + 4, *(char *)(puVar7 + 0x11) == '\0')))) ||
           ((iVar6 = iVar5 + 5, *(char *)(puVar7 + 0x15) == '\0' ||
            ((iVar6 = iVar5 + 6, *(char *)(puVar7 + 0x19) == '\0' ||
             (iVar6 = iVar5 + 7, *(char *)(puVar7 + 0x1d) == '\0')))))) break;
        puVar7 = puVar7 + 0x20;
        iVar5 = iVar5 + 8;
        iVar9 = iVar9 + -1;
        iVar6 = iVar5;
      } while (iVar9 != 0);
      if (iVar6 == 0x20) {
        iVar2 = 0;
      }
      else {
        (&DAT_8040ae7c)[iVar6 * 4] = iVar2;
        sVar3 = strlen(param_1);
        gnt4_memcpy(&DAT_8040ae80 + iVar6 * 0x10,param_1,sVar3 + 1);
      }
    }
    if (iVar2 == 0) {
      if (DAT_8040ad38 != (code *)0x0) {
        (*DAT_8040ad38)(DAT_8040ad3c,s_cvFsAddDev__3_failed_added_a_dev_802b761c,0);
      }
    }
    else if (*(code **)(iVar2 + 4) != (code *)0x0) {
      (**(code **)(iVar2 + 4))(zz_02749e8_,0);
    }
  }
  return;
}



// ==== 802749e8  zz_02749e8_ ====

void zz_02749e8_(void)

{
  if (DAT_8040ad38 != (code *)0x0) {
    (*DAT_8040ad38)(DAT_8040ad3c);
  }
  return;
}



// ==== 80274a28  zz_0274a28_ ====

void zz_0274a28_(void)

{
  return;
}



// ==== 80274a2c  zz_0274a2c_ ====

undefined4 zz_0274a2c_(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x20);
  }
  return uVar1;
}



// ==== 80274a8c  zz_0274a8c_ ====

void zz_0274a8c_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040302_handl_is_null__802b7684,0);
    }
  }
  else {
    iVar2 = *(int *)(param_1 + 0x10);
    uVar1 = iVar2 >> 0x1f;
    if ((uVar1 * 0x20 | iVar2 * 0x8000000 + uVar1 >> 0x1b) == uVar1) {
      *(int *)(param_1 + 0x10) = param_2;
      *(int *)(param_1 + 0x18) =
           (*(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x14) + -1) / *(int *)(param_1 + 0x10);
      *(int *)(param_1 + 0x1c) = (*(int *)(param_1 + 0x1c) * iVar2) / *(int *)(param_1 + 0x10);
      *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x24) * param_2;
    }
    else if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040303_invalidate_size__802b769c,0);
    }
  }
  return;
}



// ==== 80274b70  zz_0274b70_ ====

undefined4 zz_0274b70_(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040301_handl_is_null__802b76b8,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x10);
  }
  return uVar1;
}



// ==== 80274bd0  zz_0274bd0_ ====

int zz_0274bd0_(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
    iVar1 = 0;
  }
  else {
    iVar1 = (int)*(char *)(param_1 + 2);
  }
  return iVar1;
}



// ==== 80274c34  zz_0274c34_ ====

void zz_0274c34_(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
  }
  else if ((*(char *)(param_1 + 2) != '\x01') && (*(char *)(param_1 + 2) != '\0')) {
    gnt4_DVDGetCommandBlockStatus_bl(param_1 + 0x28);
    gnt4_DVDGetDriveStatus_bl();
    DAT_8040b1c8 = 1;
    iVar2 = gnt4_DVDCancel_bl((int *)(param_1 + 0x28));
    DAT_8040b1c8 = 0;
    if (iVar2 < 0) {
      if (DAT_8040b1d0 != (code *)0x0) {
        (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092917_DVDCancel_failed__802b76d0,param_1);
      }
    }
    else {
      uVar3 = gnt4_OSGetTick_bl();
      uVar3 = uVar3 / (DAT_800000f8 / 4000);
      do {
        bVar1 = false;
        if ((*(int *)(param_1 + 0xc) == 0) || (*(int *)(param_1 + 0xc) == 10)) {
          bVar1 = true;
        }
        if (bVar1) goto LAB_80274da4;
        iVar2 = gnt4_DVDGetCommandBlockStatus_bl(param_1 + 0x28);
        *(int *)(param_1 + 0xc) = iVar2;
        DAT_8040b1c0 = *(undefined4 *)(param_1 + 0xc);
        uVar4 = gnt4_OSGetTick_bl();
        uVar4 = uVar4 / (DAT_800000f8 / 4000);
        iVar2 = -1 - uVar3;
        if (uVar3 <= uVar4) {
          iVar2 = -uVar3;
        }
      } while (iVar2 + uVar4 < 0x7d1);
      if (DAT_8040b1d0 != (code *)0x0) {
        (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092918_DVDCancel_time_out__802b76ec,param_1);
      }
LAB_80274da4:
      *(undefined1 *)(param_1 + 2) = 0;
      DAT_8040b1c4 = 0;
      gnt4_DVDGetCommandBlockStatus_bl(param_1 + 0x28);
      gnt4_DVDGetDriveStatus_bl();
    }
  }
  return;
}



// ==== 80274dd4  zz_0274dd4_ ====

int zz_0274dd4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,uint param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  size_t __n;
  void *__s;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  
  if (param_9 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
    param_10 = 0;
  }
  else if (param_10 < 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092913_nsct_<_0_(gcCiReqRd)_802b770c,param_9);
    }
    param_10 = 0;
  }
  else if (param_11 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092914_buf_is_null__gcCiReqRd__802b772c,param_9);
    }
    param_10 = 0;
  }
  else {
    bVar1 = false;
    if ((*(char *)(param_9 + 2) == '\x01') || (*(char *)(param_9 + 2) == '\0')) {
      bVar1 = true;
    }
    if (bVar1) {
      bVar1 = false;
      if ((*(int *)(param_9 + 0xc) == 0) || (*(int *)(param_9 + 0xc) == 10)) {
        bVar1 = true;
      }
      if (bVar1) {
        pcVar7 = &DAT_8040b1d4;
        iVar8 = 8;
        pcVar4 = pcVar7;
        do {
          if ((*pcVar4 == '\x01') && (pcVar4[2] == '\x02')) {
            bVar1 = true;
            goto LAB_80274fa8;
          }
          if ((pcVar4[100] == '\x01') && (pcVar4[0x66] == '\x02')) {
            bVar1 = true;
            goto LAB_80274fa8;
          }
          if ((pcVar4[200] == '\x01') && (pcVar4[0xca] == '\x02')) {
            bVar1 = true;
            goto LAB_80274fa8;
          }
          if ((pcVar4[300] == '\x01') && (pcVar4[0x12e] == '\x02')) {
            bVar1 = true;
            goto LAB_80274fa8;
          }
          if ((pcVar4[400] == '\x01') && (pcVar4[0x192] == '\x02')) {
            bVar1 = true;
            goto LAB_80274fa8;
          }
          pcVar4 = pcVar4 + 500;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
        bVar1 = false;
LAB_80274fa8:
        if (bVar1) {
          param_10 = 0;
        }
        else if (param_10 == 0) {
          *(undefined1 *)(param_9 + 2) = 1;
          param_10 = 0;
          DAT_8040b1c4 = 1;
        }
        else {
          iVar8 = 0;
          *(undefined4 *)(param_9 + 0x20) = 0;
          *(uint *)(param_9 + 8) = param_11;
          *(int *)(param_9 + 0x24) = param_10;
          do {
            if ((*pcVar7 == '\x01') && (pcVar7[2] == '\x02')) {
              iVar3 = gnt4_DVDGetCommandBlockStatus_bl((int)(pcVar7 + 0x28));
              *(int *)(pcVar7 + 0xc) = iVar3;
              DAT_8040b1c0 = *(int *)(pcVar7 + 0xc);
              if (DAT_8040b1c0 == 0) {
                iVar5 = *(int *)(pcVar7 + 0x24);
                iVar3 = *(int *)(pcVar7 + 0x10);
                gnt4_DCInvalidateRange_bl(*(uint *)(pcVar7 + 8),iVar5 * iVar3);
                *(int *)(pcVar7 + 0x20) = iVar5 * iVar3;
                *(int *)(pcVar7 + 0x1c) = *(int *)(pcVar7 + 0x1c) + *(int *)(pcVar7 + 0x24);
                if (*(int *)(pcVar7 + 0x14) < *(int *)(pcVar7 + 0x1c) * *(int *)(pcVar7 + 0x10)) {
                  __n = *(int *)(pcVar7 + 0x1c) * *(int *)(pcVar7 + 0x10) - *(int *)(pcVar7 + 0x14);
                  __s = (void *)((*(int *)(pcVar7 + 8) + *(int *)(pcVar7 + 0x20)) - __n);
                  gnt4_memset(__s,0,__n);
                  gnt4_DCStoreRange_bl((uint)__s,__n);
                }
                pcVar7[2] = '\x01';
                DAT_8040b1c4 = 1;
              }
              else if (DAT_8040b1c0 < 0) {
                if (-2 < DAT_8040b1c0) {
                  pcVar7[2] = '\x03';
                  DAT_8040b1c4 = 3;
                }
              }
              else if (DAT_8040b1c0 == 10) {
                iVar3 = zz_020d728_((int)(pcVar7 + 0x28));
                gnt4_DCInvalidateRange_bl(*(uint *)(pcVar7 + 8),iVar3);
                DAT_8040b1c4 = 0;
                *(int *)(pcVar7 + 0x20) =
                     *(int *)(pcVar7 + 0x10) * (iVar3 / *(int *)(pcVar7 + 0x10));
                *(int *)(pcVar7 + 0x1c) = *(int *)(pcVar7 + 0x1c) + iVar3 / *(int *)(pcVar7 + 0x10);
                pcVar7[2] = '\0';
              }
            }
            iVar8 = iVar8 + 1;
            pcVar7 = pcVar7 + 100;
          } while (iVar8 < 0x28);
          uVar6 = *(int *)(param_9 + 0x1c) * *(int *)(param_9 + 0x10);
          iVar8 = *(int *)(param_9 + 0x24) * *(int *)(param_9 + 0x10);
          if ((*(int *)(param_9 + 0x14) < (int)(uVar6 + iVar8)) &&
             (iVar8 = *(int *)(param_9 + 0x14) - uVar6, iVar8 < 0)) {
            *(undefined1 *)(param_9 + 2) = 1;
            DAT_8040b1c4 = 1;
          }
          else {
            uVar2 = iVar8 + 0x1fU & 0xffffffe0;
            gnt4_DCInvalidateRange_bl(param_11,uVar2);
            if (DAT_803adf60 == 0) {
              iVar8 = gnt4_DVDReadAsyncPrio_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 (undefined4 *)(param_9 + 0x28),param_11,uVar2,uVar6,zz_0274a28_,2,
                                 param_15,param_16);
            }
            else {
              iVar8 = gnt4_DVDReadPrio_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,(undefined4 *)(param_9 + 0x28),param_11,uVar2,
                                          uVar6,2,param_14,param_15,param_16);
            }
            if (iVar8 == 0) {
              param_10 = 0;
            }
            else {
              *(undefined1 *)(param_9 + 2) = 2;
              DAT_8040b1c4 = 2;
              param_10 = *(int *)(param_9 + 0x24);
            }
          }
        }
      }
      else {
        param_10 = 0;
      }
    }
    else {
      param_10 = 0;
    }
  }
  return param_10;
}



// ==== 802751fc  zz_02751fc_ ====

undefined4 zz_02751fc_(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
  }
  return uVar1;
}



// ==== 8027525c  zz_027525c_ ====

undefined4 zz_027525c_(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092912_handl_is_null__802b766c,0);
    }
    uVar2 = 0;
  }
  else {
    if (param_3 == 0) {
      *(int *)(param_1 + 0x1c) = param_2;
    }
    else if (param_3 == 2) {
      *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x18) + param_2;
    }
    else if (param_3 == 1) {
      *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + param_2;
    }
    iVar1 = *(int *)(param_1 + 0x18);
    if (*(int *)(param_1 + 0x1c) < *(int *)(param_1 + 0x18)) {
      iVar1 = *(int *)(param_1 + 0x1c);
    }
    *(int *)(param_1 + 0x1c) = iVar1;
    iVar1 = *(int *)(param_1 + 0x1c);
    if (iVar1 < 1) {
      iVar1 = 0;
    }
    *(int *)(param_1 + 0x1c) = iVar1;
    uVar2 = *(undefined4 *)(param_1 + 0x1c);
  }
  return uVar2;
}



// ==== 80275328  zz_0275328_ ====

/* WARNING: Removing unreachable block (ram,0x80275358) */
/* WARNING: Removing unreachable block (ram,0x80275364) */

void zz_0275328_(undefined1 *param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  if (param_1 != (undefined1 *)0x0) {
    if ((param_1[2] != '\x01') && (param_1[2] != '\0')) {
      gnt4_DVDGetCommandBlockStatus_bl((int)(param_1 + 0x28));
      gnt4_DVDGetDriveStatus_bl();
      DAT_8040b1c8 = 1;
      iVar2 = gnt4_DVDCancel_bl((int *)(param_1 + 0x28));
      DAT_8040b1c8 = 0;
      if (iVar2 < 0) {
        if (DAT_8040b1d0 != (code *)0x0) {
          (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092917_DVDCancel_failed__802b76d0,param_1);
        }
      }
      else {
        uVar3 = gnt4_OSGetTick_bl();
        uVar3 = uVar3 / (DAT_800000f8 / 4000);
        do {
          bVar1 = false;
          if ((*(int *)(param_1 + 0xc) == 0) || (*(int *)(param_1 + 0xc) == 10)) {
            bVar1 = true;
          }
          if (bVar1) goto LAB_8027549c;
          iVar2 = gnt4_DVDGetCommandBlockStatus_bl((int)(param_1 + 0x28));
          *(int *)(param_1 + 0xc) = iVar2;
          DAT_8040b1c0 = *(undefined4 *)(param_1 + 0xc);
          uVar4 = gnt4_OSGetTick_bl();
          uVar4 = uVar4 / (DAT_800000f8 / 4000);
          iVar2 = -1 - uVar3;
          if (uVar3 <= uVar4) {
            iVar2 = -uVar3;
          }
        } while (iVar2 + uVar4 < 0x7d1);
        if (DAT_8040b1d0 != (code *)0x0) {
          (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092918_DVDCancel_time_out__802b76ec,param_1);
        }
LAB_8027549c:
        param_1[2] = 0;
        DAT_8040b1c4 = 0;
        gnt4_DVDGetCommandBlockStatus_bl((int)(param_1 + 0x28));
        gnt4_DVDGetDriveStatus_bl();
      }
    }
    gnt4_DVDClose_bl((int *)(param_1 + 0x28));
    *param_1 = 0;
    gnt4_memset(param_1,0,100);
  }
  return;
}



// ==== 802754ec  FUN_802754ec ====

undefined1 *
FUN_802754ec(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,int param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined1 *__s;
  int iVar1;
  size_t sVar2;
  uint uVar3;
  char *pcVar4;
  int iVar5;
  undefined8 uVar6;
  char local_118 [264];
  
  if (param_9 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092908_fname_is_null__gcCiOpen_802b7750,0);
    }
    __s = (undefined1 *)0x0;
  }
  else if (param_11 == 0) {
    __s = (undefined1 *)0x0;
    iVar1 = 0;
    pcVar4 = &DAT_8040b1d4;
    iVar5 = 0x28;
    do {
      if (*pcVar4 == '\0') {
        __s = &DAT_8040b1d4 + iVar1 * 100;
        break;
      }
      pcVar4 = pcVar4 + 100;
      iVar1 = iVar1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (__s == (undefined1 *)0x0) {
      if (DAT_8040b1d0 != (code *)0x0) {
        (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092910_not_enough_handle_resou_802b7798,0);
      }
      __s = (undefined1 *)0x0;
    }
    else {
      strcpy(local_118,&DAT_8040c178);
      uVar6 = zz_0238c90_((int)local_118,param_9);
      sVar2 = strlen(local_118);
      pcVar4 = local_118;
      for (; sVar2 != 0; sVar2 = sVar2 - 1) {
        if (*pcVar4 == '\\') {
          *pcVar4 = '/';
        }
        pcVar4 = pcVar4 + 1;
      }
      iVar1 = gnt4_DVDOpen_bl(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              local_118,(int)(__s + 0x28),param_11,param_12,param_13,param_14,
                              param_15,param_16);
      if (iVar1 == 0) {
        if (DAT_8040b1d0 != (code *)0x0) {
          (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092911_DVDOpen_fail__gcCiOpen__802b77c8,0);
        }
        gnt4_memset(__s,0,100);
        __s = (undefined1 *)0x0;
      }
      else {
        *(undefined4 *)(__s + 0x10) = 0x800;
        uVar3 = *(uint *)(__s + 0x5c);
        if ((uVar3 & 0x80000000) != 0) {
          uVar3 = 0x7fffffff;
        }
        *(uint *)(__s + 0x14) = uVar3;
        *(int *)(__s + 0x18) =
             (*(int *)(__s + 0x10) + *(int *)(__s + 0x14) + -1) / *(int *)(__s + 0x10);
        *(undefined4 *)(__s + 0x1c) = 0;
        *(undefined4 *)(__s + 8) = 0;
        *(undefined4 *)(__s + 0x24) = 0;
        *(undefined4 *)(__s + 0x20) = 0;
        __s[2] = 0;
        *__s = 1;
      }
    }
  }
  else {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092909_rw_is_illigal__gcCiOpen_802b7774,0);
    }
    __s = (undefined1 *)0x0;
  }
  return __s;
}



