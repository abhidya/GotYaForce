// ==== 802756fc  FUN_802756fc ====

uint FUN_802756fc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  undefined8 uVar5;
  int aiStack_148 [13];
  uint local_114;
  char local_10c [260];
  
  if (param_9 == 0) {
    if (DAT_8040b1d0 != (code *)0x0) {
      (*DAT_8040b1d0)(DAT_8040b1cc,s_E0092901_fname_is_null__gcCiGetF_802b77ec,0);
    }
    uVar1 = 0;
  }
  else {
    strcpy(local_10c,&DAT_8040c178);
    uVar5 = zz_0238c90_((int)local_10c,param_9);
    sVar2 = strlen(local_10c);
    pcVar4 = local_10c;
    for (; sVar2 != 0; sVar2 = sVar2 - 1) {
      if (*pcVar4 == '\\') {
        *pcVar4 = '/';
      }
      pcVar4 = pcVar4 + 1;
    }
    iVar3 = gnt4_DVDOpen_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_10c,
                            (int)aiStack_148,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar3 == 0) {
      if (DAT_8040b1d0 != (code *)0x0) {
        (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040201_can_t_open_a_file__gcCi_802b7818,0);
      }
      uVar1 = 0;
    }
    else {
      uVar1 = local_114;
      if ((local_114 & 0x80000000) != 0) {
        uVar1 = 0x7fffffff;
      }
      iVar3 = gnt4_DVDClose_bl(aiStack_148);
      if (iVar3 == 0) {
        if (DAT_8040b1d0 != (code *)0x0) {
          (*DAT_8040b1d0)(DAT_8040b1cc,s_E0040202_can_t_close_a_file__gcC_802b7848,0);
        }
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}



// ==== 80275874  FUN_80275874 ====

void FUN_80275874(void)

{
  int iVar1;
  int iVar2;
  size_t __n;
  void *__s;
  int iVar3;
  char *pcVar4;
  
  pcVar4 = &DAT_8040b1d4;
  iVar3 = 0;
  do {
    if ((*pcVar4 == '\x01') && (pcVar4[2] == '\x02')) {
      iVar1 = gnt4_DVDGetCommandBlockStatus_bl((int)(pcVar4 + 0x28));
      *(int *)(pcVar4 + 0xc) = iVar1;
      DAT_8040b1c0 = *(int *)(pcVar4 + 0xc);
      if (DAT_8040b1c0 == 0) {
        iVar2 = *(int *)(pcVar4 + 0x24);
        iVar1 = *(int *)(pcVar4 + 0x10);
        gnt4_DCInvalidateRange_bl(*(uint *)(pcVar4 + 8),iVar2 * iVar1);
        *(int *)(pcVar4 + 0x20) = iVar2 * iVar1;
        *(int *)(pcVar4 + 0x1c) = *(int *)(pcVar4 + 0x1c) + *(int *)(pcVar4 + 0x24);
        if (*(int *)(pcVar4 + 0x14) < *(int *)(pcVar4 + 0x1c) * *(int *)(pcVar4 + 0x10)) {
          __n = *(int *)(pcVar4 + 0x1c) * *(int *)(pcVar4 + 0x10) - *(int *)(pcVar4 + 0x14);
          __s = (void *)((*(int *)(pcVar4 + 8) + *(int *)(pcVar4 + 0x20)) - __n);
          gnt4_memset(__s,0,__n);
          gnt4_DCStoreRange_bl((uint)__s,__n);
        }
        pcVar4[2] = '\x01';
        DAT_8040b1c4 = 1;
      }
      else if (DAT_8040b1c0 < 0) {
        if (-2 < DAT_8040b1c0) {
          pcVar4[2] = '\x03';
          DAT_8040b1c4 = 3;
        }
      }
      else if (DAT_8040b1c0 == 10) {
        iVar1 = zz_020d728_((int)(pcVar4 + 0x28));
        gnt4_DCInvalidateRange_bl(*(uint *)(pcVar4 + 8),iVar1);
        DAT_8040b1c4 = 0;
        *(int *)(pcVar4 + 0x20) = *(int *)(pcVar4 + 0x10) * (iVar1 / *(int *)(pcVar4 + 0x10));
        *(int *)(pcVar4 + 0x1c) = *(int *)(pcVar4 + 0x1c) + iVar1 / *(int *)(pcVar4 + 0x10);
        pcVar4[2] = '\0';
      }
    }
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 100;
  } while (iVar3 < 0x28);
  return;
}



// ==== 802759ec  FUN_802759ec ====

undefined ** FUN_802759ec(void)

{
  gnt4_memset(&DAT_8040c178,0,0x100);
  DAT_8040b1d0 = 0;
  DAT_8040b1cc = 0;
  gnt4_memset(&DAT_8040b1c0,0,0xc);
  return &PTR_FUN_803adef8;
}



// ==== 80275a58  zz_0275a58_ ====

void zz_0275a58_(void)

{
  undefined4 in_r6;
  
  DAT_803adf60 = in_r6;
  return;
}



// ==== 80275a64  zz_0275a64_ ====

void zz_0275a64_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                char *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte in_cr1;
  char *local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  char local_18 [4];
  undefined1 *local_14;
  char **local_10;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_58 = param_1;
    local_50 = param_2;
    local_48 = param_3;
    local_40 = param_4;
    local_38 = param_5;
    local_30 = param_6;
    local_28 = param_7;
    local_20 = param_8;
  }
  local_14 = &stack0x00000008;
  local_10 = &local_78;
  local_18[0] = '\x01';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  local_78 = param_9;
  local_74 = param_10;
  local_70 = param_11;
  local_6c = param_12;
  local_68 = param_13;
  local_64 = param_14;
  local_60 = param_15;
  local_5c = param_16;
  zz_0236910_(-0x7fbf3d80,param_9,local_18);
  if (DAT_8040c278 != (code *)0x0) {
    (*DAT_8040c278)(DAT_8040c27c,&DAT_8040c280);
  }
  return;
}



// ==== 80275b24  zz_0275b24_ ====

void zz_0275b24_(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    DAT_8040c278 = 0;
    DAT_8040c27c = 0;
    return;
  }
  DAT_8040c278 = param_1;
  DAT_8040c27c = param_2;
  return;
}



// ==== 80275b58  zz_0275b58_ ====

void zz_0275b58_(void)

{
  zz_0276774_();
  return;
}



// ==== 80275b78  zz_0275b78_ ====

void zz_0275b78_(void)

{
  zz_02767c0_();
  return;
}



// ==== 80275b98  zz_0275b98_ ====

void zz_0275b98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    *(char *)(param_9 + 3) = (char)param_10;
  }
  return;
}



// ==== 80275bd4  zz_0275bd4_ ====

void zz_0275bd4_(void)

{
  if (DAT_8040c380 != (code *)0x0) {
    (*DAT_8040c380)(DAT_8040c384,DAT_8040c388);
  }
  return;
}



// ==== 80275c14  zz_0275c14_ ====

void zz_0275c14_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else if ((param_10 < 0) || (*(int *)(param_9 + 0x18) < param_10)) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0010__Illigal_parameter_min__d_802b789c,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    *(int *)(param_9 + 0x14) = param_10;
  }
  return;
}



// ==== 80275c78  zz_0275c78_ ====

undefined4
zz_0275c78_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = *(undefined4 *)(param_9 + 0x24);
  }
  return uVar1;
}



// ==== 80275cb8  zz_0275cb8_ ====

int zz_0275cb8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    iVar1 = -1;
  }
  else {
    iVar1 = (int)*(char *)(param_9 + 1);
  }
  return iVar1;
}



// ==== 80275cfc  zz_0275cfc_ ====

void zz_0275cfc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar4 = zz_0275b78_();
  iVar2 = 0;
  pcVar3 = &DAT_8040c394;
  uVar1 = extraout_r4;
  do {
    if (*pcVar3 == '\x01') {
      uVar4 = zz_027652c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)pcVar3,
                          uVar1,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar1 = extraout_r4_00;
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x238;
  } while (iVar2 < 0x10);
  zz_0275b58_();
  return;
}



// ==== 80275d68  zz_0275d68_ ====

void zz_0275d68_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else if (*(char *)(param_9 + 1) != '\0') {
    *(undefined1 *)(param_9 + 1) = 0;
    if ((*(int *)(param_9 + 0x28) != 0) && (*(char *)(param_9 + 2) == '\x01')) {
      param_1 = zz_026d564_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x28),param_10,param_11,param_12,param_13,param_14,
                            param_15,param_16);
      *(undefined1 *)(param_9 + 2) = 0;
      param_10 = extraout_r4;
    }
    *(undefined4 *)(param_9 + 0x2c) = 0;
    if (param_9 == 0) {
      zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                  param_14,param_15,param_16);
    }
    else if (*(char *)(param_9 + 1) == '\0') {
      *(undefined4 *)(param_9 + 0x1c) = 0;
      *(undefined4 *)(param_9 + 0x20) = 0;
      *(undefined4 *)(param_9 + 0x24) = 0;
    }
    *(undefined4 *)(param_9 + 0x34) = 0;
  }
  return;
}



// ==== 80275e24  zz_0275e24_ ====

void zz_0275e24_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  undefined8 uVar2;
  
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    uVar2 = zz_0275b78_();
    if (*(char *)(param_9 + 1) != '\0') {
      if (param_9 == 0) {
        zz_0275a64_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E0003__Illigal_parameter_lsc_NUL_802b7878,extraout_r4,param_11,param_12,
                    param_13,param_14,param_15,param_16);
      }
      else if (*(char *)(param_9 + 1) != '\0') {
        *(undefined1 *)(param_9 + 1) = 0;
        uVar1 = extraout_r4;
        if ((*(int *)(param_9 + 0x28) != 0) && (*(char *)(param_9 + 2) == '\x01')) {
          uVar2 = zz_026d564_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 0x28),extraout_r4,param_11,param_12,param_13,
                              param_14,param_15,param_16);
          *(undefined1 *)(param_9 + 2) = 0;
          uVar1 = extraout_r4_00;
        }
        *(undefined4 *)(param_9 + 0x2c) = 0;
        if (param_9 == 0) {
          zz_0275a64_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_E0003__Illigal_parameter_lsc_NUL_802b7878,uVar1,param_11,param_12,param_13,
                      param_14,param_15,param_16);
        }
        else if (*(char *)(param_9 + 1) == '\0') {
          *(undefined4 *)(param_9 + 0x1c) = 0;
          *(undefined4 *)(param_9 + 0x20) = 0;
          *(undefined4 *)(param_9 + 0x24) = 0;
        }
        *(undefined4 *)(param_9 + 0x34) = 0;
      }
    }
    if (*(int *)(param_9 + 0x24) < 1) {
      *(undefined1 *)(param_9 + 1) = 1;
    }
    else {
      *(undefined1 *)(param_9 + 1) = 2;
    }
    zz_0275b58_();
  }
  return;
}



// ==== 80275f34  zz_0275f34_ ====

uint zz_0275f34_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10,uint param_11,uint param_12,uint param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  size_t sVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint *puVar9;
  uint uVar10;
  
  if (param_9 == 0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar3 = 0xffffffff;
  }
  else if (*(int *)(param_9 + 0x24) < 0x10) {
    if (param_10 == (int *)0x0) {
      zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E0011__Illigal_parameter_fname___802b78c0,0,param_11,param_12,param_13,param_14,
                  param_15,param_16);
      uVar3 = 0xffffffff;
    }
    else {
      iVar7 = *(int *)(param_9 + 0x1c) + 0xf;
      iVar8 = iVar7 >> 0x1f;
      puVar9 = (uint *)(param_9 + *(int *)(param_9 + 0x1c) * 0x20 + 0x38);
      iVar8 = *(int *)(param_9 + ((iVar8 * 0x10 | (uint)(iVar7 * 0x10000000 + iVar8) >> 0x1c) -
                                 iVar8) * 0x20 + 0x38);
      uVar3 = iVar8 + 1U & ~((int)~(iVar8 + 0x80000001U | 0x7fffffffU - iVar8) >> 0x1f);
      *puVar9 = uVar3;
      puVar9[1] = (uint)param_10;
      sVar4 = strlen((char *)param_10);
      uVar2 = sVar4 >> 2;
      puVar9[2] = 0;
      uVar6 = 0;
      if (uVar2 != 0) {
        if ((8 < uVar2) && (uVar10 = uVar2 - 1 >> 3, piVar5 = param_10, uVar2 != 8)) {
          do {
            uVar6 = uVar6 + 8;
            puVar9[2] = puVar9[2] + *piVar5;
            puVar9[2] = puVar9[2] + piVar5[1];
            puVar9[2] = puVar9[2] + piVar5[2];
            puVar9[2] = puVar9[2] + piVar5[3];
            puVar9[2] = puVar9[2] + piVar5[4];
            puVar9[2] = puVar9[2] + piVar5[5];
            puVar9[2] = puVar9[2] + piVar5[6];
            piVar1 = piVar5 + 7;
            piVar5 = piVar5 + 8;
            puVar9[2] = puVar9[2] + *piVar1;
            uVar10 = uVar10 - 1;
          } while (uVar10 != 0);
        }
        iVar8 = uVar2 - uVar6;
        piVar5 = param_10 + uVar6;
        if (uVar6 < uVar2) {
          do {
            iVar7 = *piVar5;
            piVar5 = piVar5 + 1;
            puVar9[2] = puVar9[2] + iVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      puVar9[4] = param_12;
      puVar9[5] = param_13;
      puVar9[3] = param_11;
      puVar9[6] = 0;
      puVar9[7] = 0;
      *(int *)(param_9 + 0x24) = *(int *)(param_9 + 0x24) + 1;
      iVar7 = *(int *)(param_9 + 0x1c) + 1;
      iVar8 = iVar7 >> 0x1f;
      *(uint *)(param_9 + 0x1c) =
           (iVar8 * 0x10 | (uint)(iVar7 * 0x10000000 + iVar8) >> 0x1c) - iVar8;
      if (*(char *)(param_9 + 1) == '\x01') {
        *(undefined1 *)(param_9 + 1) = 2;
      }
    }
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}



// ==== 80276174  zz_0276174_ ====

void zz_0276174_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10)

{
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  zz_0275f34_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,0,0,
              0xfffff,in_r8,in_r9,in_r10);
  return;
}



// ==== 802761a4  zz_02761a4_ ====

void zz_02761a4_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  return;
}



// ==== 802761ac  zz_02761ac_ ====

/* WARNING: Removing unreachable block (ram,0x802761c8) */

void zz_02761ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined1 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (param_9 != (undefined1 *)0x0) {
    if (param_9[1] != '\0') {
      param_9[1] = 0;
      if ((*(int *)(param_9 + 0x28) != 0) && (param_9[2] == '\x01')) {
        param_1 = zz_026d564_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 0x28),param_10,param_11,param_12,param_13,param_14,
                              param_15,param_16);
        param_9[2] = 0;
        param_10 = extraout_r4;
      }
      *(undefined4 *)(param_9 + 0x2c) = 0;
      if (param_9 == (undefined1 *)0x0) {
        zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E0003__Illigal_parameter_lsc_NUL_802b7878,param_10,param_11,param_12,param_13,
                    param_14,param_15,param_16);
      }
      else if (param_9[1] == '\0') {
        *(undefined4 *)(param_9 + 0x1c) = 0;
        *(undefined4 *)(param_9 + 0x20) = 0;
        *(undefined4 *)(param_9 + 0x24) = 0;
      }
      *(undefined4 *)(param_9 + 0x34) = 0;
    }
    *param_9 = 0;
    gnt4_memset(param_9,0,0x238);
  }
  return;
}



// ==== 80276284  zz_0276284_ ====

char * zz_0276284_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                  undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined8 uVar6;
  
  if (param_9 == (int *)0x0) {
    zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0001__Illigal_parameter_sj__LSC_802b78e4,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    pcVar2 = (char *)0x0;
  }
  else {
    uVar6 = zz_0275b78_();
    pcVar2 = (char *)0x0;
    pcVar4 = &DAT_8040c394;
    iVar3 = 0;
    iVar5 = 0x10;
    do {
      if (*pcVar4 == '\0') {
        pcVar4 = (char *)(iVar3 * 0x238);
        pcVar2 = pcVar4 + -0x7fbf3c6c;
        break;
      }
      pcVar4 = pcVar4 + 0x238;
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (pcVar2 == (char *)0x0) {
      zz_0275a64_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E0002__Not_enough_instance__LSC__802b7910,pcVar4,param_11,param_12,param_13,
                  param_14,param_15,param_16);
    }
    else {
      *(int **)(pcVar2 + 8) = param_9;
      pcVar2[1] = '\0';
      iVar3 = (**(code **)(*param_9 + 0x24))(param_9,1);
      iVar5 = (**(code **)(*param_9 + 0x24))(param_9,0);
      *(int *)(pcVar2 + 0x18) = iVar5 + iVar3;
      uVar1 = *(uint *)(pcVar2 + 0x18) << 3;
      iVar3 = (int)uVar1 / 10 + ((int)(uVar1 | *(uint *)(pcVar2 + 0x18) >> 0x1d) >> 0x1f);
      *(int *)(pcVar2 + 0x14) = iVar3 - (iVar3 >> 0x1f);
      pcVar2[0x50] = '\0';
      pcVar2[0x51] = '\0';
      pcVar2[0x52] = '\0';
      pcVar2[0x53] = '\0';
      pcVar2[0x70] = '\0';
      pcVar2[0x71] = '\0';
      pcVar2[0x72] = '\0';
      pcVar2[0x73] = '\0';
      pcVar2[0x90] = '\0';
      pcVar2[0x91] = '\0';
      pcVar2[0x92] = '\0';
      pcVar2[0x93] = '\0';
      pcVar2[0xb0] = '\0';
      pcVar2[0xb1] = '\0';
      pcVar2[0xb2] = '\0';
      pcVar2[0xb3] = '\0';
      pcVar2[0xd0] = '\0';
      pcVar2[0xd1] = '\0';
      pcVar2[0xd2] = '\0';
      pcVar2[0xd3] = '\0';
      pcVar2[0xf0] = '\0';
      pcVar2[0xf1] = '\0';
      pcVar2[0xf2] = '\0';
      pcVar2[0xf3] = '\0';
      pcVar2[0x110] = '\0';
      pcVar2[0x111] = '\0';
      pcVar2[0x112] = '\0';
      pcVar2[0x113] = '\0';
      pcVar2[0x130] = '\0';
      pcVar2[0x131] = '\0';
      pcVar2[0x132] = '\0';
      pcVar2[0x133] = '\0';
      pcVar2[0x150] = '\0';
      pcVar2[0x151] = '\0';
      pcVar2[0x152] = '\0';
      pcVar2[0x153] = '\0';
      pcVar2[0x170] = '\0';
      pcVar2[0x171] = '\0';
      pcVar2[0x172] = '\0';
      pcVar2[0x173] = '\0';
      pcVar2[400] = '\0';
      pcVar2[0x191] = '\0';
      pcVar2[0x192] = '\0';
      pcVar2[0x193] = '\0';
      pcVar2[0x1b0] = '\0';
      pcVar2[0x1b1] = '\0';
      pcVar2[0x1b2] = '\0';
      pcVar2[0x1b3] = '\0';
      pcVar2[0x1d0] = '\0';
      pcVar2[0x1d1] = '\0';
      pcVar2[0x1d2] = '\0';
      pcVar2[0x1d3] = '\0';
      pcVar2[0x1f0] = '\0';
      pcVar2[0x1f1] = '\0';
      pcVar2[0x1f2] = '\0';
      pcVar2[499] = '\0';
      pcVar2[0x210] = '\0';
      pcVar2[0x211] = '\0';
      pcVar2[0x212] = '\0';
      pcVar2[0x213] = '\0';
      pcVar2[0x230] = '\0';
      pcVar2[0x231] = '\0';
      pcVar2[0x232] = '\0';
      pcVar2[0x233] = '\0';
      *pcVar2 = '\x01';
    }
    zz_0275b58_();
  }
  return pcVar2;
}



// ==== 80276410  zz_0276410_ ====

void zz_0276410_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  undefined4 *extraout_r4;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  
  uVar4 = zz_0275b78_();
  puVar1 = &DAT_8040c390;
  DAT_8040c390 = DAT_8040c390 + -1;
  if (DAT_8040c390 == 0) {
    iVar2 = 0;
    pcVar3 = &DAT_8040c394;
    do {
      if (*pcVar3 == '\x01') {
        uVar4 = zz_02761ac_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar3,
                            puVar1,param_11,param_12,param_13,param_14,param_15,param_16);
        puVar1 = extraout_r4;
      }
      iVar2 = iVar2 + 1;
      pcVar3 = pcVar3 + 0x238;
    } while (iVar2 < 0x10);
    gnt4_memset(&DAT_8040c394,0,0x2380);
    zz_0275b24_(0,0);
  }
  zz_0275b58_();
  return;
}



// ==== 802764b4  zz_02764b4_ ====

void zz_02764b4_(void)

{
  zz_0275b78_();
  if (DAT_8040c390 == 0) {
    gnt4_memset(&DAT_8040c394,0,0x2380);
    zz_0275b24_(0,0);
  }
  DAT_8040c390 = DAT_8040c390 + 1;
  zz_0275b58_();
  return;
}



// ==== 8027652c  zz_027652c_ ====

void zz_027652c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined8 uVar8;
  
  if (((*(char *)(param_9 + 4) != '\x01') && (*(char *)(param_9 + 1) == '\x02')) &&
     (0 < *(int *)(param_9 + 0x24))) {
    iVar2 = *(int *)(param_9 + 0x20) * 0x20;
    if (*(int *)(param_9 + iVar2 + 0x50) == 1) {
      if (*(int *)(param_9 + 0x28) == 0) {
        param_1 = zz_0275a64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E0007__lsc_>fp_NULL_802b7978,iVar2,param_11,param_12,param_13,
                              param_14,param_15,param_16);
      }
      else {
        iVar3 = param_9 + iVar2 + 0x38;
        iVar2 = zz_026d7dc_(*(int *)(param_9 + 0x28));
        if (iVar2 == 4) {
          *(undefined1 *)(param_9 + 1) = 3;
        }
        else if (iVar2 == 2) {
          uVar1 = zz_026d770_(*(int *)(param_9 + 0x28));
          *(undefined4 *)(iVar3 + 0x1c) = uVar1;
        }
        else if (iVar2 == 3) {
          *(undefined4 *)(iVar3 + 0x1c) = *(undefined4 *)(param_9 + 0x2c);
          *(undefined4 *)(iVar3 + 0x18) = 2;
        }
      }
    }
    iVar2 = *(int *)(param_9 + 0x20) * 0x20;
    if (*(int *)(param_9 + iVar2 + 0x50) == 2) {
      piVar4 = (int *)0x0;
      uVar5 = 0;
      uVar6 = 0;
      uVar7 = 0;
      if (*(int *)(param_9 + 0x28) != 0) {
        if (*(char *)(param_9 + 3) == '\x01') {
          iVar2 = param_9 + iVar2 + 0x38;
          piVar4 = *(int **)(iVar2 + 4);
          uVar5 = *(uint *)(iVar2 + 0xc);
          uVar6 = *(uint *)(iVar2 + 0x10);
          uVar7 = *(uint *)(iVar2 + 0x14);
        }
        *(int *)(param_9 + 0x24) = *(int *)(param_9 + 0x24) + -1;
        iVar3 = *(int *)(param_9 + 0x20) + 1;
        iVar2 = iVar3 >> 0x1f;
        *(uint *)(param_9 + 0x20) =
             (iVar2 * 0x10 | (uint)(iVar3 * 0x10000000 + iVar2) >> 0x1c) - iVar2;
        if (*(int *)(param_9 + 0x24) < 1) {
          param_1 = zz_0275bd4_();
          *(undefined1 *)(param_9 + 1) = 1;
        }
        if (*(char *)(param_9 + 3) == '\x01') {
          zz_0275f34_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,piVar4
                      ,uVar5,uVar6,uVar7,param_14,param_15,param_16);
        }
      }
    }
    iVar2 = *(int *)(param_9 + 0x20) * 0x20;
    if (*(int *)(param_9 + iVar2 + 0x50) == 0) {
      iVar2 = param_9 + iVar2 + 0x38;
      if (0 < *(int *)(param_9 + 0x24)) {
        uVar8 = zz_026d658_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x28));
        uVar8 = zz_026d9ac_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x28));
        zz_026dafc_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0x28),*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar2 + 0xc)
                    ,*(undefined4 *)(iVar2 + 0x10),*(int *)(iVar2 + 0x14));
        zz_026d510_(*(int *)(param_9 + 0x28),*(int *)(iVar2 + 0x14));
        *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(iVar2 + 0x14);
        *(undefined4 *)(iVar2 + 0x1c) = 0;
        *(undefined1 *)(param_9 + 2) = 0;
        if (*(char *)(param_9 + 2) == '\0') {
          zz_026cecc_(*(int *)(param_9 + 0x28),*(undefined4 *)(param_9 + 0x14),
                      *(undefined4 *)(param_9 + 0x18));
          zz_026d78c_(*(int *)(param_9 + 0x28),0);
          zz_026d718_(*(int *)(param_9 + 0x28));
          *(undefined1 *)(param_9 + 2) = 1;
        }
        *(undefined4 *)(iVar2 + 0x18) = 1;
      }
    }
  }
  return;
}



// ==== 80276774  zz_0276774_ ====

void zz_0276774_(void)

{
  DAT_8040e718 = DAT_8040e718 + -1;
  if (DAT_8040e718 == 0) {
    gnt4_OSRestoreInterrupts_bl();
  }
  return;
}



// ==== 802767c0  zz_02767c0_ ====

void zz_02767c0_(void)

{
  ulonglong uVar1;
  
  if (DAT_8040e718 == 0) {
    uVar1 = gnt4_OSDisableInterrupts_bl();
    DAT_8040e71c = (undefined4)(uVar1 >> 0x20);
  }
  DAT_8040e718 = DAT_8040e718 + 1;
  return;
}



// ==== 8027680c  FUN_8027680c ====

uint FUN_8027680c(int param_1,int param_2,int param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  
  zz_02767c0_();
  if (param_2 == 0) {
    iVar2 = 0;
  }
  else if (param_2 == 1) {
    iVar2 = param_3;
    if (*(int *)(param_1 + 0xc) < param_3) {
      iVar2 = *(int *)(param_1 + 0xc);
    }
  }
  else {
    iVar2 = 0;
    if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
      (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
    }
  }
  *param_4 = iVar2;
  zz_0276774_();
  uVar1 = countLeadingZeros(param_3 - iVar2);
  return uVar1 >> 5;
}



// ==== 802768c4  FUN_802768c4 ====

void FUN_802768c4(int param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  
  if ((0 < param_3[1]) && (*param_3 != 0)) {
    zz_02767c0_();
    if (param_2 == 0) {
      if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
        (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
      }
    }
    else if (param_2 == 1) {
      uVar2 = *(int *)(param_1 + 0x10) - param_3[1];
      uVar2 = uVar2 & (int)(-uVar2 & ~uVar2) >> 0x1f;
      *(uint *)(param_1 + 0x10) = uVar2;
      iVar1 = *(int *)(param_1 + 0xc) + param_3[1];
      if (*(int *)(param_1 + 0x18) < iVar1) {
        iVar1 = *(int *)(param_1 + 0x18);
      }
      *(int *)(param_1 + 0xc) = iVar1;
      if ((uVar2 != *param_3 - *(int *)(param_1 + 0x14)) &&
         (*(code **)(param_1 + 0x1c) != (code *)0x0)) {
        (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
      }
    }
    else {
      param_3[1] = 0;
      *param_3 = 0;
      if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
        (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
      }
    }
    zz_0276774_();
  }
  return;
}



// ==== 802769f4  FUN_802769f4 ====

void FUN_802769f4(int param_1,uint param_2,int *param_3)

{
  if ((0 < param_3[1]) && (*param_3 != 0)) {
    zz_02767c0_();
    if (1 < param_2) {
      param_3[1] = 0;
      *param_3 = 0;
      if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
        (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
      }
    }
    zz_0276774_();
  }
  return;
}



// ==== 80276a88  FUN_80276a88 ====

void FUN_80276a88(int param_1,int param_2,int param_3,int *param_4)

{
  zz_02767c0_();
  if (param_2 == 0) {
    param_4[1] = 0;
    *param_4 = 0;
  }
  else if (param_2 == 1) {
    if (*(int *)(param_1 + 0xc) < param_3) {
      param_3 = *(int *)(param_1 + 0xc);
    }
    param_4[1] = param_3;
    *param_4 = *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x10);
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_4[1];
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - param_4[1];
  }
  else {
    param_4[1] = 0;
    *param_4 = 0;
    if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
      (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
    }
  }
  zz_0276774_();
  return;
}



// ==== 80276b70  FUN_80276b70 ====

undefined4 FUN_80276b70(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 1) {
    uVar1 = *(undefined4 *)(param_1 + 0xc);
  }
  else if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    if (*(code **)(param_1 + 0x1c) != (code *)0x0) {
      (**(code **)(param_1 + 0x1c))(*(undefined4 *)(param_1 + 0x20),0xfffffffd);
    }
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80276bf4  FUN_80276bf4 ====

void FUN_80276bf4(void *param_1)

{
  if (param_1 != (void *)0x0) {
    gnt4_memset(param_1,0,0x24);
    *(undefined4 *)((int)param_1 + 4) = 0;
  }
  return;
}



// ==== 80276c34  zz_0276c34_ ====

undefined4 * zz_0276c34_(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  puVar1 = &DAT_8040e724;
  iVar2 = 0;
  iVar5 = 4;
  do {
    iVar3 = iVar2;
    if (((((*(int *)(puVar1 + 4) == 0) || (iVar3 = iVar2 + 1, *(int *)(puVar1 + 0x28) == 0)) ||
         (iVar3 = iVar2 + 2, *(int *)(puVar1 + 0x4c) == 0)) ||
        ((iVar3 = iVar2 + 3, *(int *)(puVar1 + 0x70) == 0 ||
         (iVar3 = iVar2 + 4, *(int *)(puVar1 + 0x94) == 0)))) ||
       ((iVar3 = iVar2 + 5, *(int *)(puVar1 + 0xb8) == 0 ||
        ((iVar3 = iVar2 + 6, *(int *)(puVar1 + 0xdc) == 0 ||
         (iVar3 = iVar2 + 7, *(int *)(puVar1 + 0x100) == 0)))))) break;
    puVar1 = puVar1 + 0x120;
    iVar2 = iVar2 + 8;
    iVar5 = iVar5 + -1;
    iVar3 = iVar2;
  } while (iVar5 != 0);
  if (iVar3 == 0x20) {
    return (undefined4 *)0x0;
  }
  iVar2 = iVar3 * 0x24;
  puVar4 = (undefined4 *)(&DAT_8040e724 + iVar2);
  (&DAT_8040e728)[iVar3 * 9] = 1;
  *puVar4 = &DAT_803adf68;
  *(undefined4 *)(iVar2 + -0x7fbf18c8) = param_1;
  *(undefined4 *)(iVar2 + -0x7fbf18c4) = param_2;
  *(undefined **)(iVar2 + -0x7fbf18d4) = &DAT_802b7990;
  *(undefined **)(iVar2 + -0x7fbf18c0) = &DAT_80276df8;
  *(undefined4 **)(iVar2 + -0x7fbf18bc) = puVar4;
  *(undefined4 *)(iVar2 + -0x7fbf18d0) = *(undefined4 *)(iVar2 + -0x7fbf18c4);
  *(undefined4 *)(iVar2 + -0x7fbf18cc) = 0;
  return puVar4;
}



// ==== 80276d5c  zz_0276d5c_ ====

void zz_0276d5c_(void)

{
  DAT_8040e720 = DAT_8040e720 + -1;
  if (DAT_8040e720 == 0) {
    gnt4_memset(&DAT_8040e724,0,0x480);
  }
  return;
}



// ==== 80276da4  zz_0276da4_ ====

void zz_0276da4_(void)

{
  if (DAT_8040e720 == 0) {
    gnt4_memset(&DAT_8040e724,0,0x480);
  }
  DAT_8040e720 = DAT_8040e720 + 1;
  return;
}



// ==== 80276dfc  zz_0276dfc_ ====

undefined4 zz_0276dfc_(int param_1,int param_2,int param_3)

{
  return *(undefined4 *)(param_1 + param_2 * 8 + param_3 * 4 + 0x28);
}



// ==== 80276e14  zz_0276e14_ ====

undefined4 zz_0276e14_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x24);
}



// ==== 80276e1c  zz_0276e1c_ ====

undefined4 zz_0276e1c_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}



// ==== 80276e24  zz_0276e24_ ====

undefined4 zz_0276e24_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x1c);
}



// ==== 80276e2c  FUN_80276e2c ====

uint FUN_80276e2c(int param_1,int param_2,int param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  zz_02767c0_();
  iVar3 = param_3;
  if (param_2 == 0) {
    iVar2 = *(int *)(param_1 + 0x24) + (*(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x14));
    if (*(int *)(param_1 + 0x10) < iVar2) {
      iVar2 = *(int *)(param_1 + 0x10);
    }
    if (iVar2 < param_3) {
      iVar3 = iVar2;
    }
  }
  else if (param_2 == 1) {
    iVar2 = *(int *)(param_1 + 0x24) + (*(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x18));
    if (*(int *)(param_1 + 0xc) < iVar2) {
      iVar2 = *(int *)(param_1 + 0xc);
    }
    if (iVar2 < param_3) {
      iVar3 = iVar2;
    }
  }
  else {
    iVar3 = 0;
    if (*(code **)(param_1 + 0x38) != (code *)0x0) {
      (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
    }
  }
  *param_4 = iVar3;
  zz_0276774_();
  uVar1 = countLeadingZeros(param_3 - iVar3);
  return uVar1 >> 5;
}



// ==== 80276f38  FUN_80276f38 ====

void FUN_80276f38(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((0 < param_3[1]) && (*param_3 != 0)) {
    zz_02767c0_();
    if (param_2 == 0) {
      iVar3 = *(int *)(param_1 + 0x20);
      iVar2 = (*(int *)(param_1 + 0x14) + iVar3) - param_3[1];
      iVar1 = *param_3 - *(int *)(param_1 + 0x1c);
      iVar2 = iVar2 - (iVar2 / iVar3) * iVar3;
      if (iVar2 == iVar1 - (iVar1 / iVar3) * iVar3) {
        *(int *)(param_1 + 0x14) = iVar2;
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3[1];
      }
      else if (*(code **)(param_1 + 0x38) != (code *)0x0) {
        (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
      }
      *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) - param_3[1];
    }
    else if (param_2 == 1) {
      iVar3 = *(int *)(param_1 + 0x20);
      iVar2 = (*(int *)(param_1 + 0x18) + iVar3) - param_3[1];
      iVar1 = *param_3 - *(int *)(param_1 + 0x1c);
      iVar2 = iVar2 - (iVar2 / iVar3) * iVar3;
      if (iVar2 == iVar1 - (iVar1 / iVar3) * iVar3) {
        *(int *)(param_1 + 0x18) = iVar2;
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_3[1];
      }
      else if (*(code **)(param_1 + 0x38) != (code *)0x0) {
        (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
      }
      *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - param_3[1];
    }
    else {
      param_3[1] = 0;
      *param_3 = 0;
      if (*(code **)(param_1 + 0x38) != (code *)0x0) {
        (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
      }
    }
    zz_0276774_();
  }
  return;
}



// ==== 802770e4  FUN_802770e4 ====

void FUN_802770e4(int param_1,int param_2,int *param_3)

{
  void *__dest;
  size_t sVar1;
  size_t __n;
  int iVar2;
  
  if ((0 < param_3[1]) && (*param_3 != 0)) {
    zz_02767c0_();
    if (param_2 == 1) {
      *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + param_3[1];
      iVar2 = *param_3 - *(int *)(param_1 + 0x1c);
      if (iVar2 < *(int *)(param_1 + 0x24)) {
        sVar1 = *(int *)(param_1 + 0x24) - iVar2;
        if (param_3[1] < (int)sVar1) {
          sVar1 = param_3[1];
        }
        gnt4_memcpy((void *)(*(int *)(param_1 + 0x20) + iVar2 + *(int *)(param_1 + 0x1c)),
                    (void *)*param_3,sVar1);
      }
      __dest = *(void **)(param_1 + 0x1c);
      sVar1 = param_3[1];
      iVar2 = sVar1 + (*param_3 - (int)__dest);
      if (*(int *)(param_1 + 0x20) < iVar2) {
        __n = iVar2 - *(int *)(param_1 + 0x20);
        if ((int)sVar1 < (int)__n) {
          __n = sVar1;
        }
        gnt4_memcpy(__dest,(void *)((int)__dest + (iVar2 - __n)),__n);
      }
      *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + param_3[1];
    }
    else if (param_2 == 0) {
      *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3[1];
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + param_3[1];
    }
    else {
      param_3[1] = 0;
      *param_3 = 0;
      if (*(code **)(param_1 + 0x38) != (code *)0x0) {
        (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
      }
    }
    zz_0276774_();
  }
  return;
}



// ==== 80277240  FUN_80277240 ====

void FUN_80277240(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  
  zz_02767c0_();
  if (param_2 == 0) {
    iVar1 = *(int *)(param_1 + 0x24) + (*(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x14));
    if (*(int *)(param_1 + 0x10) < iVar1) {
      iVar1 = *(int *)(param_1 + 0x10);
    }
    param_4[1] = iVar1;
    if (param_4[1] < param_3) {
      param_3 = param_4[1];
    }
    param_4[1] = param_3;
    *param_4 = *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x14);
    iVar1 = *(int *)(param_1 + 0x14) + param_4[1];
    *(int *)(param_1 + 0x14) = iVar1 - (iVar1 / *(int *)(param_1 + 0x20)) * *(int *)(param_1 + 0x20)
    ;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) - param_4[1];
    *(int *)(param_1 + 0x28) = *(int *)(param_1 + 0x28) + param_4[1];
  }
  else if (param_2 == 1) {
    iVar1 = *(int *)(param_1 + 0x24) + (*(int *)(param_1 + 0x20) - *(int *)(param_1 + 0x18));
    if (*(int *)(param_1 + 0xc) < iVar1) {
      iVar1 = *(int *)(param_1 + 0xc);
    }
    param_4[1] = iVar1;
    if (param_4[1] < param_3) {
      param_3 = param_4[1];
    }
    param_4[1] = param_3;
    *param_4 = *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 0x18);
    iVar1 = *(int *)(param_1 + 0x18) + param_4[1];
    *(int *)(param_1 + 0x18) = iVar1 - (iVar1 / *(int *)(param_1 + 0x20)) * *(int *)(param_1 + 0x20)
    ;
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - param_4[1];
    *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) + param_4[1];
  }
  else {
    param_4[1] = 0;
    *param_4 = 0;
    if (*(code **)(param_1 + 0x38) != (code *)0x0) {
      (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
    }
  }
  zz_0276774_();
  return;
}



// ==== 802773f4  FUN_802773f4 ====

undefined4 FUN_802773f4(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 1) {
    uVar1 = *(undefined4 *)(param_1 + 0xc);
  }
  else if (param_2 == 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x10);
  }
  else {
    if (*(code **)(param_1 + 0x38) != (code *)0x0) {
      (**(code **)(param_1 + 0x38))(*(undefined4 *)(param_1 + 0x3c),0xfffffffd);
    }
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80277490  FUN_80277490 ====

void FUN_80277490(void *param_1)

{
  zz_02767c0_();
  if (param_1 != (void *)0x0) {
    gnt4_memset(param_1,0,0x40);
    *(undefined4 *)((int)param_1 + 4) = 0;
  }
  zz_0276774_();
  return;
}



// ==== 802774e0  zz_02774e0_ ====

undefined4 * zz_02774e0_(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  
  zz_02767c0_();
  puVar1 = &DAT_8040ebac;
  iVar2 = 0;
  iVar5 = 0x20;
  do {
    iVar3 = iVar2;
    if (((((*(int *)(puVar1 + 4) == 0) || (iVar3 = iVar2 + 1, *(int *)(puVar1 + 0x44) == 0)) ||
         (iVar3 = iVar2 + 2, *(int *)(puVar1 + 0x84) == 0)) ||
        ((iVar3 = iVar2 + 3, *(int *)(puVar1 + 0xc4) == 0 ||
         (iVar3 = iVar2 + 4, *(int *)(puVar1 + 0x104) == 0)))) ||
       ((iVar3 = iVar2 + 5, *(int *)(puVar1 + 0x144) == 0 ||
        ((iVar3 = iVar2 + 6, *(int *)(puVar1 + 0x184) == 0 ||
         (iVar3 = iVar2 + 7, *(int *)(puVar1 + 0x1c4) == 0)))))) break;
    puVar1 = puVar1 + 0x200;
    iVar2 = iVar2 + 8;
    iVar5 = iVar5 + -1;
    iVar3 = iVar2;
  } while (iVar5 != 0);
  if (iVar3 == 0x100) {
    puVar4 = (undefined4 *)0x0;
  }
  else {
    iVar2 = iVar3 * 0x40;
    puVar4 = (undefined4 *)(&DAT_8040ebac + iVar2);
    (&DAT_8040ebb0)[iVar3 * 0x10] = 1;
    *puVar4 = &DAT_803adf98;
    *(undefined4 *)(iVar2 + -0x7fbf1438) = param_1;
    *(undefined4 *)(iVar2 + -0x7fbf1434) = param_2;
    *(undefined4 *)(iVar2 + -0x7fbf1430) = param_3;
    *(undefined **)(iVar2 + -0x7fbf144c) = &DAT_802b79d0;
    *(undefined **)(iVar2 + -0x7fbf141c) = &DAT_80277718;
    *(undefined4 **)(iVar2 + -0x7fbf1418) = puVar4;
    *(undefined4 *)(iVar2 + -0x7fbf1448) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf1444) = *(undefined4 *)(iVar2 + -0x7fbf1434);
    *(undefined4 *)(iVar2 + -0x7fbf1440) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf143c) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf142c) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf1428) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf1424) = 0;
    *(undefined4 *)(iVar2 + -0x7fbf1420) = 0;
  }
  zz_0276774_();
  return puVar4;
}



// ==== 80277670  zz_0277670_ ====

void zz_0277670_(void)

{
  DAT_8040eba8 = DAT_8040eba8 + -1;
  if (DAT_8040eba8 == 0) {
    gnt4_memset(&DAT_8040ebac,0,0x4000);
  }
  return;
}



// ==== 802776b8  zz_02776b8_ ====

void zz_02776b8_(void)

{
  if (DAT_8040eba8 == 0) {
    gnt4_memset(&DAT_8040ebac,0,0x4000);
  }
  DAT_8040eba8 = DAT_8040eba8 + 1;
  return;
}



// ==== 8027771c  zz_027771c_ ====

void zz_027771c_(void)

{
  DAT_80412bb0 = DAT_80412bb0 + -1;
  if (DAT_80412bb0 == 0) {
    gnt4_memset(&DAT_80412bb4,0,0xc00);
  }
  return;
}



// ==== 80277764  zz_0277764_ ====

void zz_0277764_(void)

{
  if (DAT_80412bb0 == 0) {
    gnt4_memset(&DAT_80412bb4,0,0xc00);
  }
  DAT_80412bb0 = DAT_80412bb0 + 1;
  return;
}



// ==== 802777b8  zz_02777b8_ ====

char * zz_02777b8_(int *param_1,char *param_2,char *param_3,int *param_4)

{
  int iVar1;
  char *__s1;
  char *pcVar2;
  
  *param_4 = 0;
  param_4[1] = 0;
  __s1 = (char *)*param_1;
  pcVar2 = __s1 + param_1[1];
  do {
    if (pcVar2 <= __s1) {
LAB_802779a4:
      if (pcVar2 <= __s1) {
        __s1 = (char *)0x0;
      }
      return __s1;
    }
    iVar1 = gnt4_strncmp(__s1,param_2,7);
    if (iVar1 == 0) {
      *param_4 = (int)(__s1 + 0x10);
      param_4[1] = (((((*(int *)(&DAT_803adfc8 + __s1[8] * 4) * 0x10 +
                       *(int *)(&DAT_803adfc8 + __s1[9] * 4)) * 0x10 +
                      *(int *)(&DAT_803adfc8 + __s1[10] * 4)) * 0x10 +
                     *(int *)(&DAT_803adfc8 + __s1[0xb] * 4)) * 0x10 +
                    *(int *)(&DAT_803adfc8 + __s1[0xc] * 4)) * 0x10 +
                   *(int *)(&DAT_803adfc8 + __s1[0xd] * 4)) * 0x10 +
                   *(int *)(&DAT_803adfc8 + __s1[0xe] * 4);
      goto LAB_802779a4;
    }
    if ((param_3 != (char *)0x0) && (iVar1 = gnt4_strncmp(__s1,param_3,7), iVar1 == 0)) {
      return (char *)0x0;
    }
    __s1 = __s1 + (((((*(int *)(&DAT_803adfc8 + __s1[8] * 4) * 0x10 +
                      *(int *)(&DAT_803adfc8 + __s1[9] * 4)) * 0x10 +
                     *(int *)(&DAT_803adfc8 + __s1[10] * 4)) * 0x10 +
                    *(int *)(&DAT_803adfc8 + __s1[0xb] * 4)) * 0x10 +
                   *(int *)(&DAT_803adfc8 + __s1[0xc] * 4)) * 0x10 +
                  *(int *)(&DAT_803adfc8 + __s1[0xd] * 4)) * 0x10 +
                  *(int *)(&DAT_803adfc8 + __s1[0xe] * 4) + 0x10;
  } while( true );
}



// ==== 802779cc  zz_02779cc_ ====

void zz_02779cc_(int *param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  
  iVar1 = param_1[1];
  *param_3 = *param_1;
  param_3[1] = iVar1;
  param_4[1] = param_3[1];
  if (param_2 < param_3[1]) {
    param_3[1] = param_2;
  }
  param_4[1] = param_4[1] - param_3[1];
  if (param_4[1] == 0) {
    *param_4 = 0;
    return;
  }
  *param_4 = *param_3 + param_3[1];
  return;
}



// ==== 80277a30  zz_0277a30_ ====

uint zz_0277a30_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if (DAT_804137e4 == (code *)0x0) {
    if (DAT_80413878 != (code *)0x0) {
      param_1 = (*DAT_80413878)(DAT_8041387c);
      if (DAT_804137bc == 0) {
        DAT_804137c0 = 1;
      }
      DAT_804137bc = DAT_804137bc + 1;
    }
    iVar2 = *param_9;
    *param_9 = 1;
    uVar1 = (1U - iVar2 | iVar2 - 1U) >> 0x1f;
    if (DAT_80413870 != (code *)0x0) {
      DAT_804137bc = DAT_804137bc + -1;
      if (DAT_804137bc == 0) {
        if (DAT_804137c0 != 1) {
          zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,param_12,param_13,
                      param_14,param_15,param_16);
        }
        DAT_804137c0 = 0;
      }
      (*DAT_80413870)(DAT_80413874);
    }
  }
  else {
    uVar1 = (*DAT_804137e4)();
  }
  return uVar1;
}



// ==== 80277b44  zz_0277b44_ ====

void zz_0277b44_(void)

{
  DAT_804137b8 = DAT_804137b8 + -1;
  if (DAT_804137b8 == 0) {
    gnt4_memset(&DAT_80413a40,0,0x20);
    gnt4_memset(&DAT_80413878,0,8);
    gnt4_memset(&DAT_80413870,0,8);
    DAT_80413a60 = 0;
    DAT_80413a64 = 0;
    DAT_80413a68 = 0;
    DAT_80413a6c = 0;
    DAT_80413a70 = 0;
    DAT_80413a74 = 0;
    DAT_804137e4 = 0;
    gnt4_memset(&DAT_80413868,0,8);
  }
  return;
}



// ==== 80277bec  zz_0277bec_ ====

void zz_0277bec_(void)

{
  if (DAT_804137b8 == 0) {
    gnt4_memset(&DAT_80413a40,0,0x20);
    gnt4_memset(&DAT_80413878,0,8);
    gnt4_memset(&DAT_80413870,0,8);
    DAT_80413a60 = 0;
    DAT_80413a64 = 0;
    DAT_80413a68 = 0;
    DAT_80413a6c = 0;
    DAT_80413a70 = 0;
    DAT_80413a74 = 0;
    DAT_804137e4 = 0;
  }
  DAT_804137b8 = DAT_804137b8 + 1;
  return;
}



// ==== 80277c84  zz_0277c84_ ====

uint zz_0277c84_(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  iVar3 = 0;
  puVar2 = &DAT_804139e0;
  do {
    if ((code *)*puVar2 != (code *)0x0) {
      DAT_80413a58 = 1;
      uVar1 = (*(code *)*puVar2)(puVar2[1]);
      uVar4 = uVar4 | uVar1;
      DAT_80413a58 = 0;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 2;
  } while (iVar3 < 6);
  DAT_80413a78 = DAT_80413a78 + 1;
  return uVar4;
}



// ==== 80277d14  zz_0277d14_ ====

uint zz_0277d14_(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  iVar3 = 0;
  puVar2 = &DAT_804139b0;
  do {
    if ((code *)*puVar2 != (code *)0x0) {
      DAT_80413a54 = 1;
      uVar1 = (*(code *)*puVar2)(puVar2[1]);
      uVar4 = uVar4 | uVar1;
      DAT_80413a54 = 0;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 2;
  } while (iVar3 < 6);
  DAT_80413a74 = DAT_80413a74 + 1;
  return uVar4;
}



// ==== 80277da4  zz_0277da4_ ====

uint zz_0277da4_(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  iVar3 = 0;
  puVar2 = &DAT_80413980;
  do {
    if ((code *)*puVar2 != (code *)0x0) {
      DAT_80413a50 = 1;
      uVar1 = (*(code *)*puVar2)(puVar2[1]);
      uVar4 = uVar4 | uVar1;
      DAT_80413a50 = 0;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 2;
  } while (iVar3 < 6);
  DAT_80413a70 = DAT_80413a70 + 1;
  return uVar4;
}



// ==== 80277e34  zz_0277e34_ ====

uint zz_0277e34_(void)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  
  uVar4 = 0;
  iVar3 = 0;
  puVar2 = &DAT_80413920;
  do {
    if ((code *)*puVar2 != (code *)0x0) {
      DAT_80413a48 = 1;
      uVar1 = (*(code *)*puVar2)(puVar2[1]);
      uVar4 = uVar4 | uVar1;
      DAT_80413a48 = 0;
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 2;
  } while (iVar3 < 6);
  DAT_80413a68 = DAT_80413a68 + 1;
  return uVar4;
}



// ==== 80277ec4  zz_0277ec4_ ====

void zz_0277ec4_(undefined4 param_1,undefined4 param_2)

{
  DAT_80413870 = param_1;
  DAT_80413874 = param_2;
  return;
}



// ==== 80277ed4  zz_0277ed4_ ====

void zz_0277ed4_(undefined4 param_1,undefined4 param_2)

{
  DAT_80413878 = param_1;
  DAT_8041387c = param_2;
  return;
}



// ==== 80277ee4  zz_0277ee4_ ====

void zz_0277ee4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (DAT_80413878 != (code *)0x0) {
    param_1 = (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  DAT_80413868 = param_9;
  DAT_8041386c = param_10;
  if (DAT_80413870 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,param_12,param_13,
                    param_14,param_15,param_16);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 80277fd4  zz_0277fd4_ ====

void zz_0277fd4_(int param_1)

{
  if (*(code **)(&DAT_80413880 + param_1 * 8) != (code *)0x0) {
    (**(code **)(&DAT_80413880 + param_1 * 8))(*(undefined4 *)(&DAT_80413884 + param_1 * 8));
  }
  return;
}



// ==== 80278018  zz_0278018_ ====

void zz_0278018_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  code *pcVar1;
  undefined4 uVar2;
  
  uVar2 = 0x80410000;
  if (DAT_80413878 != (code *)0x0) {
    param_1 = (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  pcVar1 = DAT_80413870;
  *(undefined4 *)(&DAT_80413880 + param_9 * 8) = param_10;
  *(undefined4 *)(&DAT_80413884 + param_9 * 8) = param_11;
  if (pcVar1 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,uVar2,param_13,
                    param_14,param_15,param_16);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 8027811c  zz_027811c_ ====

void zz_027811c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar3 = 0x802b0000;
  uVar2 = param_12;
  if ((param_10 < 0) || (5 < param_10)) {
    param_1 = zz_0238cbc_(-0x7fbec818,-0x7fd48550,0x7f);
    if (DAT_80413868 != (code *)0x0) {
      param_1 = (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
    }
  }
  if ((param_9 < 0) || (7 < param_10)) {
    param_1 = zz_0238cbc_(-0x7fbec818,-0x7fd4852c,0x7f);
    if (DAT_80413868 != (code *)0x0) {
      param_1 = (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
    }
  }
  if (DAT_80413878 != (code *)0x0) {
    param_1 = (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  iVar4 = param_9 * 0x30 + param_10 * 8;
  if (*(int *)(&DAT_804138c0 + iVar4) != 0) {
    param_1 = zz_0238cbc_(-0x7fbec818,-0x7fd48504,0x7f);
    if (DAT_80413868 != (code *)0x0) {
      param_1 = (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
    }
  }
  pcVar1 = DAT_80413870;
  *(int *)(&DAT_804138c0 + iVar4) = param_11;
  *(undefined4 *)(&DAT_804138c4 + iVar4) = param_12;
  if (pcVar1 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,uVar2,uVar3,param_14,
                    param_15,param_16);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 802782d0  zz_02782d0_ ====

void zz_02782d0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  int iVar1;
  code *pcVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if ((param_10 < 0) || (5 < param_10)) {
    param_1 = zz_0238cbc_(-0x7fbec818,-0x7fd484cc,0x7f);
    if (DAT_80413868 != (code *)0x0) {
      param_1 = (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
    }
  }
  if (DAT_80413878 != (code *)0x0) {
    param_1 = (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  pcVar2 = DAT_80413870;
  iVar1 = param_10 * 8;
  *(undefined4 *)(&DAT_804138c0 + param_9 * 0x30 + iVar1) = 0;
  *(undefined4 *)(&DAT_804138c4 + param_9 * 0x30 + iVar1) = 0;
  if (pcVar2 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,0,iVar1,in_r8,in_r9,
                    in_r10);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 80278418  zz_0278418_ ====

int zz_0278418_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  uVar2 = 0x80410000;
  if (DAT_80413878 != (code *)0x0) {
    param_1 = (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  iVar3 = 0;
  piVar1 = (int *)(&DAT_804138c0 + param_9 * 0x30);
  iVar4 = 6;
  do {
    if (*piVar1 == 0) {
      *piVar1 = param_10;
      piVar1[1] = param_11;
      break;
    }
    piVar1 = piVar1 + 2;
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((iVar3 == 6) &&
     (param_1 = zz_0238cbc_(-0x7fbec818,-0x7fd484ac,0x7f), DAT_80413868 != (code *)0x0)) {
    param_1 = (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
  }
  if (DAT_80413870 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,uVar2,param_13,
                    param_14,param_15,param_16);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  if (iVar3 == 6) {
    iVar3 = -1;
  }
  return iVar3;
}



// ==== 80278594  zz_0278594_ ====

void zz_0278594_(int param_1)

{
  zz_0238cbc_(-0x7fbec818,param_1,0x7f);
  if (DAT_80413868 != (code *)0x0) {
    (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
  }
  return;
}



// ==== 802785ec  zz_02785ec_ ====

void zz_02785ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                char *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte in_cr1;
  char *local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  char local_18 [4];
  undefined1 *local_14;
  char **local_10;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_58 = param_1;
    local_50 = param_2;
    local_48 = param_3;
    local_40 = param_4;
    local_38 = param_5;
    local_30 = param_6;
    local_28 = param_7;
    local_20 = param_8;
  }
  local_78 = param_9;
  local_74 = param_10;
  local_70 = param_11;
  local_6c = param_12;
  local_68 = param_13;
  local_64 = param_14;
  local_60 = param_15;
  local_5c = param_16;
  gnt4_memset(&DAT_804137e8,0,0x80);
  local_14 = &stack0x00000008;
  local_10 = &local_78;
  local_18[0] = '\x01';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  zz_0236910_(-0x7fbec818,param_9,local_18);
  if (DAT_80413868 != (code *)0x0) {
    (*DAT_80413868)(DAT_8041386c,&DAT_804137e8);
  }
  return;
}



// ==== 802786c4  zz_02786c4_ ====

void zz_02786c4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_80413870 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 5) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,5,in_r6,in_r7,in_r8,
                    in_r9,in_r10);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 80278754  zz_0278754_ ====

void zz_0278754_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_80413870 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 3) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,3,in_r6,in_r7,in_r8,
                    in_r9,in_r10);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 802787e4  zz_02787e4_ ====

void zz_02787e4_(void)

{
  if (DAT_80413878 != (code *)0x0) {
    (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 5;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  return;
}



// ==== 8027884c  zz_027884c_ ====

void zz_027884c_(void)

{
  if (DAT_80413878 != (code *)0x0) {
    (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 3;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  return;
}



// ==== 802788b4  zz_02788b4_ ====

void zz_02788b4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  if (DAT_80413870 != (code *)0x0) {
    DAT_804137bc = DAT_804137bc + -1;
    if (DAT_804137bc == 0) {
      if (DAT_804137c0 != 1) {
        zz_02785ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_2103102_SVM_svm_unlock_lock_type_802b7a14,DAT_804137c0,1,in_r6,in_r7,in_r8,
                    in_r9,in_r10);
      }
      DAT_804137c0 = 0;
    }
    (*DAT_80413870)(DAT_80413874);
  }
  return;
}



// ==== 80278944  zz_0278944_ ====

void zz_0278944_(void)

{
  if (DAT_80413878 != (code *)0x0) {
    (*DAT_80413878)(DAT_8041387c);
    if (DAT_804137bc == 0) {
      DAT_804137c0 = 1;
    }
    DAT_804137bc = DAT_804137bc + 1;
  }
  return;
}



// ==== 802789ac  FUN_802789ac ====

undefined4 FUN_802789ac(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E0092912_handl_is_null__802b7cc4,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x14);
  }
  return uVar1;
}



// ==== 80278a0c  FUN_80278a0c ====

void FUN_80278a0c(int param_1,int param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E0040302_handl_is_null__802b7cdc,0);
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 4);
    *(int *)(param_1 + 4) = param_2;
    *(int *)(param_1 + 0xc) =
         (*(int *)(param_1 + 4) + *(int *)(param_1 + 8) + -1) / *(int *)(param_1 + 4);
    *(int *)(param_1 + 0x10) = (*(int *)(param_1 + 0x10) * iVar1) / *(int *)(param_1 + 4);
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x18) * param_2;
  }
  return;
}



// ==== 80278aa4  FUN_80278aa4 ====

undefined4 FUN_80278aa4(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E0040301_handl_is_null__802b7cf4,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}



// ==== 80278b04  FUN_80278b04 ====

int FUN_80278b04(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E0092912_handl_is_null__802b7cc4,0);
    }
    iVar1 = 0;
  }
  else {
    iVar1 = (int)*(char *)(param_1 + 1);
  }
  return iVar1;
}



// ==== 80278b68  FUN_80278b68 ====

void FUN_80278b68(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  undefined8 uVar1;
  
  if (param_9 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E0092912_handl_is_null__802b7cc4,0);
    }
  }
  else {
    uVar1 = zz_0278944_();
    *(undefined1 *)(param_9 + 1) = 0;
    zz_02788b4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 80278bd8  FUN_80278bd8 ====

undefined4
FUN_80278bd8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            int param_10,void *param_11)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  size_t sVar4;
  uint uVar5;
  size_t __n;
  undefined8 uVar6;
  char *local_28;
  uint local_24;
  
  if (param_9 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100307_handl_is_null__802b7d0c,0);
    }
    uVar3 = 0;
  }
  else if (param_10 < 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100308_nsct_<_0_(mfCiReqRd)_802b7d28,param_9);
    }
    uVar3 = 0;
  }
  else if (param_11 == (void *)0x0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100309_buf_is_null__mfCiReqRd_802b7d48,param_9);
    }
    uVar3 = 0;
  }
  else if (param_10 == 0) {
    uVar3 = 0;
    *(undefined1 *)(param_9 + 1) = 1;
  }
  else {
    uVar6 = zz_0278944_();
    *(undefined4 *)(param_9 + 0x14) = 0;
    iVar1 = *(int *)(param_9 + 0xc) - *(int *)(param_9 + 0x10);
    if (param_10 < iVar1) {
      iVar1 = param_10;
    }
    *(int *)(param_9 + 0x18) = iVar1;
    iVar1 = *(int *)(param_9 + 0x18) * *(int *)(param_9 + 4);
    if (iVar1 == 0) {
      *(undefined1 *)(param_9 + 1) = 1;
      zz_02788b4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar3 = 0;
    }
    else {
      *(int *)(param_9 + 0x30) = *(int *)(param_9 + 0x10) * *(int *)(param_9 + 4);
      *(int *)(param_9 + 0x34) = iVar1;
      *(undefined1 *)(param_9 + 1) = 2;
      sVar4 = strlen((char *)(param_9 + 0x1c));
      if (sVar4 != 0x11) {
        sprintf(&DAT_80413a88,s_E01100308_length_of___s__is_not_1_802b7c48,param_9 + 0x1c);
        if (DAT_80413a80 != (code *)0x0) {
          uVar6 = (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
        }
      }
      if (*(char *)(param_9 + 0x24) != '.') {
        sprintf(&DAT_80413a88,s_E01100309_illegal_file_name_form_802b7c88,param_9 + 0x1c);
        if (DAT_80413a80 != (code *)0x0) {
          uVar6 = (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
        }
      }
      local_28 = (char *)(param_9 + 0x1c);
      uVar5 = zz_0238e94_((int)local_28,(int *)&local_28,0x10);
      if (*local_28 != '\0') {
        local_28 = local_28 + 1;
      }
      if (&stack0x00000000 != (undefined1 *)0x24) {
        local_24 = zz_0238e94_((int)local_28,(int *)&local_28,0x10);
      }
      __n = *(size_t *)(param_9 + 0x34);
      sVar2 = local_24 - *(int *)(param_9 + 0x30);
      sVar4 = __n;
      if ((int)sVar2 < (int)__n) {
        sVar4 = sVar2;
      }
      gnt4_memcpy(param_11,(void *)(uVar5 + *(int *)(param_9 + 0x30)),__n);
      gnt4_memset((void *)((int)param_11 + sVar4),0,*(int *)(param_9 + 0x34) - sVar4);
      *(int *)(param_9 + 0x14) = *(int *)(param_9 + 0x18) * *(int *)(param_9 + 4);
      *(int *)(param_9 + 0x10) = *(int *)(param_9 + 0x10) + *(int *)(param_9 + 0x18);
      *(undefined1 *)(param_9 + 1) = 1;
      zz_02788b4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar3 = *(undefined4 *)(param_9 + 0x18);
    }
  }
  return uVar3;
}



// ==== 80278e60  FUN_80278e60 ====

undefined4 FUN_80278e60(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100306_handl_is_null__802b7d6c,0);
    }
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x10);
  }
  return uVar1;
}



// ==== 80278ec0  FUN_80278ec0 ====

undefined4
FUN_80278ec0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            int param_10,int param_11)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (param_9 == 0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100305_handl_is_null__802b7d88,0);
    }
    uVar2 = 0;
  }
  else {
    uVar3 = zz_0278944_();
    if (param_11 == 0) {
      *(int *)(param_9 + 0x10) = param_10;
    }
    else if (param_11 == 2) {
      *(int *)(param_9 + 0x10) = *(int *)(param_9 + 0xc) + param_10;
    }
    else if (param_11 == 1) {
      *(int *)(param_9 + 0x10) = *(int *)(param_9 + 0x10) + param_10;
    }
    iVar1 = *(int *)(param_9 + 0xc);
    if (*(int *)(param_9 + 0x10) < *(int *)(param_9 + 0xc)) {
      iVar1 = *(int *)(param_9 + 0x10);
    }
    *(int *)(param_9 + 0x10) = iVar1;
    iVar1 = *(int *)(param_9 + 0x10);
    if (iVar1 < 1) {
      iVar1 = 0;
    }
    *(int *)(param_9 + 0x10) = iVar1;
    zz_02788b4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar2 = *(undefined4 *)(param_9 + 0x10);
  }
  return uVar2;
}



// ==== 80278fb4  FUN_80278fb4 ====

/* WARNING: Removing unreachable block (ram,0x80278fd0) */
/* WARNING: Removing unreachable block (ram,0x80278fe0) */

void FUN_80278fb4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 char *param_9)

{
  undefined8 uVar1;
  
  if (param_9 != (char *)0x0) {
    uVar1 = zz_0278944_();
    param_9[1] = '\0';
    zz_02788b4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (*param_9 == '\x01') {
      *param_9 = '\0';
      gnt4_memset(param_9,0,0x38);
    }
  }
  return;
}



// ==== 8027904c  FUN_8027904c ====

undefined1 * FUN_8027904c(char *param_1,undefined4 param_2,int param_3)

{
  undefined1 *puVar1;
  size_t sVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  char *local_18;
  uint local_14;
  
  if (param_1 == (char *)0x0) {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100301_fname_is_null__mfCiOpe_802b7da4,0);
    }
    puVar1 = (undefined1 *)0x0;
  }
  else if (param_3 == 0) {
    puVar1 = (undefined1 *)0x0;
    iVar3 = 0;
    pcVar4 = &DAT_80413bb4;
    iVar5 = 0x28;
    do {
      if (*pcVar4 == '\0') {
        puVar1 = &DAT_80413bb4 + iVar3 * 0x38;
        break;
      }
      pcVar4 = pcVar4 + 0x38;
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    if (puVar1 == (undefined1 *)0x0) {
      if (DAT_80413a80 != (code *)0x0) {
        (*DAT_80413a80)(DAT_80413a84,s_E01100303_not_enough_handle_reso_802b7dec,0);
      }
      puVar1 = (undefined1 *)0x0;
    }
    else {
      strcpy(puVar1 + 0x1c,param_1);
      *(undefined4 *)(puVar1 + 4) = 0x800;
      sVar2 = strlen(puVar1 + 0x1c);
      if (sVar2 != 0x11) {
        sprintf(&DAT_80413a88,s_E01100308_length_of___s__is_not_1_802b7c48,puVar1 + 0x1c);
        if (DAT_80413a80 != (code *)0x0) {
          (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
        }
      }
      if (puVar1[0x24] != '.') {
        sprintf(&DAT_80413a88,s_E01100309_illegal_file_name_form_802b7c88,puVar1 + 0x1c);
        if (DAT_80413a80 != (code *)0x0) {
          (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
        }
      }
      local_18 = puVar1 + 0x1c;
      zz_0238e94_((int)local_18,(int *)&local_18,0x10);
      if (*local_18 != '\0') {
        local_18 = local_18 + 1;
      }
      if (&stack0x00000000 != (undefined1 *)0x14) {
        local_14 = zz_0238e94_((int)local_18,(int *)&local_18,0x10);
      }
      *(uint *)(puVar1 + 8) = local_14;
      *(int *)(puVar1 + 0xc) =
           (*(int *)(puVar1 + 4) + *(int *)(puVar1 + 8) + -1) / *(int *)(puVar1 + 4);
      *(undefined4 *)(puVar1 + 0x10) = 0;
      *(undefined4 *)(puVar1 + 0x18) = 0;
      *(undefined4 *)(puVar1 + 0x14) = 0;
      puVar1[1] = 0;
      *puVar1 = 1;
    }
  }
  else {
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,s_E01100302_rw_is_illigal__mfCiOpe_802b7dc8,0);
    }
    puVar1 = (undefined1 *)0x0;
  }
  return puVar1;
}



// ==== 8027927c  FUN_8027927c ====

uint FUN_8027927c(char *param_1)

{
  size_t sVar1;
  char *local_18;
  uint local_14;
  
  sVar1 = strlen(param_1);
  if (sVar1 != 0x11) {
    sprintf(&DAT_80413a88,s_E01100308_length_of___s__is_not_1_802b7c48,param_1);
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
    }
  }
  if (param_1[8] != '.') {
    sprintf(&DAT_80413a88,s_E01100309_illegal_file_name_form_802b7c88,param_1);
    if (DAT_80413a80 != (code *)0x0) {
      (*DAT_80413a80)(DAT_80413a84,&DAT_80413a88,0);
    }
  }
  local_18 = param_1;
  zz_0238e94_((int)param_1,(int *)&local_18,0x10);
  if (*local_18 != '\0') {
    local_18 = local_18 + 1;
  }
  if (&stack0x00000000 != (undefined1 *)0x14) {
    local_14 = zz_0238e94_((int)local_18,(int *)&local_18,0x10);
  }
  return local_14;
}



// ==== 802793bc  zz_02793bc_ ====

void zz_02793bc_(int param_1)

{
  zz_0238cbc_(-0x7fbebb80,param_1,0xff);
  if (DAT_80414478 != (code *)0x0) {
    (*DAT_80414478)(DAT_8041447c,&DAT_80414480);
  }
  return;
}



// ==== 80279414  zz_0279414_ ====

void zz_0279414_(undefined4 param_1,undefined4 param_2)

{
  DAT_80414478 = param_1;
  DAT_8041447c = param_2;
  return;
}



// ==== 80279428  zz_0279428_ ====

void zz_0279428_(void)

{
  zz_0276774_();
  return;
}



// ==== 80279448  zz_0279448_ ====

void zz_0279448_(void)

{
  zz_02767c0_();
  return;
}



// ==== 80279468  zz_0279468_ ====

void zz_0279468_(int param_1,undefined2 param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(undefined2 *)(param_1 + 0xa0) = param_2;
  return;
}



// ==== 80279478  zz_0279478_ ====

undefined4 zz_0279478_(void)

{
  return 0;
}



// ==== 80279480  zz_0279480_ ====

undefined4 zz_0279480_(void)

{
  return 0;
}



// ==== 80279488  zz_0279488_ ====

void zz_0279488_(int param_1,undefined4 param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(undefined4 *)(param_1 + 0x80) = param_2;
  return;
}



// ==== 80279498  zz_0279498_ ====

void zz_0279498_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if ((param_1 != 0) && (param_2 < *(char *)(param_1 + 2))) {
    iVar1 = 0xf;
    if (param_3 < 0xf) {
      iVar1 = param_3;
    }
    iVar2 = -0xf;
    if (-0xf < iVar1) {
      iVar2 = iVar1;
    }
    iVar1 = param_1 + param_2 * 4;
    if (iVar2 != *(int *)(iVar1 + 0x88)) {
      *(int *)(iVar1 + 0x88) = iVar2;
      zz_0279448_();
      iVar1 = *(int *)(param_1 + param_2 * 4 + 8);
      if (iVar1 != 0) {
        zz_021b3e0_(iVar1,(&DAT_803ae230)[iVar2]);
      }
      zz_0279428_();
    }
  }
  return;
}



// ==== 8027954c  zz_027954c_ ====

void zz_027954c_(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  if (param_1 != 0) {
    uVar1 = param_2 & (int)param_2 >> 0x1f;
    uVar3 = 0xfffffc19;
    if (-999 < (int)uVar1) {
      uVar3 = uVar1;
    }
    if (uVar3 != *(uint *)(param_1 + 0x84)) {
      *(uint *)(param_1 + 0x84) = uVar3;
      iVar4 = param_1;
      for (iVar2 = 0; iVar2 < *(char *)(param_1 + 2); iVar2 = iVar2 + 1) {
        zz_0279448_();
        if (*(int *)(iVar4 + 8) != 0) {
          zz_021b3b8_(*(int *)(iVar4 + 8),uVar3);
        }
        zz_0279428_();
        iVar4 = iVar4 + 4;
      }
    }
  }
  return;
}



// ==== 802795f8  zz_02795f8_ ====

void zz_02795f8_(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  short local_38;
  short local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  
  if (param_1 != 0) {
    *(uint *)(param_1 + 0x24) = param_2;
    iVar1 = param_2 * 0x464 + 0x464;
    iVar1 = iVar1 / 0x465 + (iVar1 >> 0x1f);
    uVar5 = iVar1 - (iVar1 >> 0x1f);
    iVar3 = (int)param_2 / 32000 + ((int)param_2 >> 0x1f);
    iVar2 = (int)(param_2 << 8) / 0x7d + ((int)(param_2 << 8 | param_2 >> 0x18) >> 0x1f);
    iVar1 = param_1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 2); iVar4 = iVar4 + 1) {
      zz_0279448_();
      if (*(int *)(iVar1 + 8) != 0) {
        local_38 = (short)iVar3 - (short)(iVar3 >> 0x1f);
        local_36 = (short)iVar2 - (short)(iVar2 >> 0x1f);
        if (*(short *)(param_1 + 0xa0) == 1) {
          if (((param_2 == 32000) && (*(short *)(param_1 + 0xa2) == 0)) && (param_1 != 0)) {
            *(undefined4 *)(param_1 + 0xa4) = 0;
            *(undefined2 *)(param_1 + 0xa2) = 1;
          }
          local_38 = (short)(uVar5 / 32000);
          local_36 = (short)((uVar5 * 0x100) / 0x7d);
        }
        local_34 = 0;
        local_32 = 0;
        local_30 = 0;
        local_2e = 0;
        local_2c = 0;
        zz_021962c_(*(int *)(iVar1 + 8),*(int *)(param_1 + 0xa4));
        zz_0219bf8_(*(int *)(iVar1 + 8),&local_38);
      }
      zz_0279428_();
      iVar1 = iVar1 + 4;
    }
  }
  return;
}



// ==== 8027974c  zz_027974c_ ====

void zz_027974c_(int param_1,undefined1 param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 3) = param_2;
  return;
}



// ==== 8027975c  zz_027975c_ ====

void zz_027975c_(void)

{
  uint uVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80415654;
  uVar1 = 0;
  do {
    if (*pcVar2 == '\x01') {
      zz_02797b8_((int)pcVar2);
    }
    uVar1 = uVar1 + 1;
    pcVar2 = pcVar2 + 0xe8;
  } while (uVar1 < 0x10);
  return;
}



// ==== 802797b8  zz_02797b8_ ====

/* WARNING: Removing unreachable block (ram,0x802797d4) */

void zz_02797b8_(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_48;
  uint local_44;
  int aiStack_40 [2];
  int local_38;
  uint local_34;
  int aiStack_30 [2];
  int local_28;
  uint local_24;
  int aiStack_20 [2];
  
  if (param_1 != 0) {
    if ((*(byte *)(param_1 + 1) >> 1 & 1) == 1) {
      zz_0279c98_(param_1);
    }
    if (param_1 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = *(byte *)(param_1 + 1) & 1;
    }
    if (uVar2 == 1) {
      iVar3 = param_1;
      iVar4 = param_1;
      iVar5 = param_1;
      for (iVar6 = 0; iVar6 < *(char *)(param_1 + 3); iVar6 = iVar6 + 1) {
        if ((*(int *)(iVar5 + 8) != 0) && (*(int *)(iVar5 + 0x60) == 0)) {
          (**(code **)(**(int **)(iVar5 + 0x38) + 0x18))(*(int **)(iVar5 + 0x38),0,0x2000,&local_28)
          ;
          (**(code **)(**(int **)(iVar5 + 0x30) + 0x18))
                    (*(int **)(iVar5 + 0x30),1,local_24,&local_38);
          uVar2 = local_24;
          if ((int)local_34 < (int)local_24) {
            uVar2 = local_34;
          }
          uVar2 = ((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0);
          iVar1 = uVar2 * 0x20;
          zz_02779cc_(&local_28,iVar1,&local_28,aiStack_20);
          (**(code **)(**(int **)(iVar5 + 0x38) + 0x1c))(*(int **)(iVar5 + 0x38),0,aiStack_20);
          zz_02779cc_(&local_38,iVar1,&local_38,aiStack_30);
          (**(code **)(**(int **)(iVar5 + 0x30) + 0x1c))(*(int **)(iVar5 + 0x30),1,aiStack_30);
          if (iVar1 == 0) {
            return;
          }
          if (local_34 != local_24) {
            do {
                    /* WARNING: Do nothing block with infinite loop */
            } while( true );
          }
          *(int *)(iVar4 + 0x40) = local_38;
          *(uint *)(iVar4 + 0x44) = local_34;
          *(int *)(iVar4 + 0x50) = local_28;
          *(uint *)(iVar4 + 0x54) = local_24;
          *(uint *)(param_1 + 0x68) = (uVar2 & 0x7ffffff) << 4;
          gnt4_DCFlushRange_bl(*(uint *)(iVar4 + 0x40),*(int *)(iVar4 + 0x44));
          *(undefined4 *)(iVar5 + 0x60) = 1;
          gnt4_ARQPostRequest_bl
                    ((undefined4 *)(iVar3 + 0xa8),*(undefined4 *)(iVar5 + 0x28),0,1,local_38,
                     local_28,iVar1,-0x7fd86444);
        }
        iVar5 = iVar5 + 4;
        iVar4 = iVar4 + 8;
        iVar3 = iVar3 + 0x20;
      }
    }
    else {
      if (param_1 == 0) {
        uVar2 = 0xffffffff;
      }
      else {
        uVar2 = *(byte *)(param_1 + 1) >> 1 & 1;
      }
      if ((uVar2 == 1) && (*(int *)(param_1 + 0x7c) < *(int *)(param_1 + 0x20))) {
        iVar3 = param_1;
        iVar4 = param_1;
        iVar5 = param_1;
        for (iVar6 = 0; iVar6 < *(char *)(param_1 + 3); iVar6 = iVar6 + 1) {
          if (*(int *)(iVar3 + 0x70) == 0) {
            (**(code **)(**(int **)(iVar3 + 0x38) + 0x18))
                      (*(int **)(iVar3 + 0x38),0,0x2000,&local_48);
            uVar2 = ((int)local_44 >> 5) + (uint)((int)local_44 < 0 && (local_44 & 0x1f) != 0);
            iVar1 = uVar2 * 0x20;
            zz_02779cc_(&local_48,iVar1,&local_48,aiStack_40);
            (**(code **)(**(int **)(iVar3 + 0x38) + 0x1c))(*(int **)(iVar3 + 0x38),0,aiStack_40);
            if (iVar1 == 0) {
              return;
            }
            *(int *)(iVar4 + 0x50) = local_48;
            *(uint *)(iVar4 + 0x54) = local_44;
            *(uint *)(param_1 + 0x78) = (uVar2 & 0x7ffffff) << 4;
            gnt4_DCFlushRange_bl(DAT_80414584,0x1000);
            *(undefined4 *)(iVar3 + 0x70) = 1;
            gnt4_ARQPostRequest_bl
                      ((undefined4 *)(iVar5 + 0xa8),*(undefined4 *)(iVar3 + 0x28),0,1,DAT_80414584,
                       local_48,iVar1,-0x7fd86510);
          }
          iVar3 = iVar3 + 4;
          iVar4 = iVar4 + 8;
          iVar5 = iVar5 + 0x20;
        }
      }
    }
  }
  return;
}



// ==== 80279af0  FUN_80279af0 ====

void FUN_80279af0(int param_1)

{
  int *piVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  
  uVar2 = *(uint *)(param_1 + 4) & 1;
  iVar4 = ((int)(*(uint *)(param_1 + 4) & 0x7fffffff) >> 1) * 0xe8;
  piVar1 = (int *)(&DAT_80415654 + uVar2 * 4 + iVar4 + 0x70);
  if (*piVar1 == 1) {
    piVar3 = *(int **)(&DAT_80415654 + uVar2 * 4 + iVar4 + 0x38);
    (**(code **)(*piVar3 + 0x20))(piVar3,1,&DAT_80415654 + uVar2 * 8 + 0x50 + iVar4);
    *piVar1 = 0;
    if (uVar2 == (int)(char)(&DAT_80415657)[iVar4] - 1U) {
      *(int *)(&DAT_804156d0 + iVar4) =
           *(int *)(&DAT_804156d0 + iVar4) + *(int *)(&DAT_804156cc + iVar4);
    }
  }
  return;
}



// ==== 80279bbc  FUN_80279bbc ====

void FUN_80279bbc(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  uVar3 = *(uint *)(param_1 + 4) & 1;
  iVar6 = ((int)(*(uint *)(param_1 + 4) & 0x7fffffff) >> 1) * 0xe8;
  iVar2 = uVar3 * 4;
  piVar1 = (int *)(&DAT_80415654 + iVar2 + iVar6 + 0x60);
  if (*piVar1 == 1) {
    piVar5 = *(int **)(&DAT_80415654 + iVar2 + iVar6 + 0x30);
    iVar4 = uVar3 * 8 + iVar6;
    (**(code **)(*piVar5 + 0x20))(piVar5,0,&DAT_80415654 + iVar4 + 0x40);
    piVar5 = *(int **)(&DAT_80415654 + iVar2 + iVar6 + 0x38);
    (**(code **)(*piVar5 + 0x20))(piVar5,1,&DAT_80415654 + iVar4 + 0x50);
    *piVar1 = 0;
    if (uVar3 == (int)(char)(&DAT_80415657)[iVar6] - 1U) {
      *(int *)(&DAT_804156c0 + iVar6) =
           *(int *)(&DAT_804156c0 + iVar6) + *(int *)(&DAT_804156bc + iVar6);
    }
  }
  return;
}



// ==== 80279c98  zz_0279c98_ ====

void zz_0279c98_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint unaff_r31;
  undefined1 auStack_28 [20];
  
  iVar4 = *(int *)(param_1 + 4);
  iVar2 = param_1 + *(char *)(param_1 + 3) * 4;
  iVar3 = *(int *)(iVar2 + 4);
  if (iVar3 != 0) {
    iVar1 = DAT_80414590 + 1;
    iVar5 = DAT_80414590 * 4;
    iVar2 = *(int *)(iVar3 + 0x1b2) - *(int *)(iVar2 + 0x14);
    DAT_80414590 = iVar1;
    *(int *)(&DAT_80414594 + iVar5) = iVar2;
    if (iVar1 == 0x20) {
      DAT_80414590 = 0;
    }
    if ((iVar2 < 0) || (*(int *)(param_1 + 0x20) < iVar2)) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    if (iVar4 == -1) {
      if (iVar2 == 0) {
        unaff_r31 = 0;
      }
      else {
        iVar4 = 0;
        *(undefined4 *)(param_1 + 4) = 0;
      }
    }
    if (iVar4 != -1) {
      if (iVar4 < iVar2) {
        unaff_r31 = iVar2 - iVar4;
      }
      else {
        unaff_r31 = 0x1000 - (iVar4 - iVar2);
      }
    }
    iVar3 = ((int)unaff_r31 >> 0xb) + (uint)((int)unaff_r31 < 0 && (unaff_r31 & 0x7ff) != 0);
    iVar2 = iVar3 * 0x800;
    if (0 < iVar2) {
      iVar4 = param_1;
      for (iVar5 = 0; iVar5 < *(char *)(param_1 + 3); iVar5 = iVar5 + 1) {
        (**(code **)(**(int **)(iVar4 + 0x38) + 0x18))
                  (*(int **)(iVar4 + 0x38),1,iVar3 * 0x1000,auStack_28);
        (**(code **)(**(int **)(iVar4 + 0x38) + 0x20))(*(int **)(iVar4 + 0x38),0,auStack_28);
        iVar4 = iVar4 + 4;
      }
      *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + iVar2;
      if (0xfff < *(int *)(param_1 + 4)) {
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + -0x1000;
      }
    }
  }
  return;
}



// ==== 80279e10  zz_0279e10_ ====

uint zz_0279e10_(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    piVar2 = *(int **)(param_1 + *(char *)(param_1 + 3) * 4 + 0x34);
    uVar1 = (**(code **)(*piVar2 + 0x24))(piVar2,0);
    uVar1 = uVar1 >> 1;
  }
  return uVar1;
}



// ==== 80279e68  zz_0279e68_ ====

int zz_0279e68_(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  
  if (param_1 == 0) {
    iVar1 = -1;
  }
  else {
    piVar2 = *(int **)(param_1 + *(char *)(param_1 + 3) * 4 + 0x34);
    uVar3 = (**(code **)(*piVar2 + 0x24))(piVar2,0);
    iVar1 = 0x1000 - (uVar3 >> 1);
  }
  return iVar1;
}



// ==== 80279ec4  zz_0279ec4_ ====

/* WARNING: Removing unreachable block (ram,0x80279eec) */

void zz_0279ec4_(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  int local_20;
  undefined2 local_1c;
  undefined2 local_1a;
  
  if ((param_1 != 0) && (param_2 != (*(byte *)(param_1 + 1) >> 1 & 1))) {
    zz_0279448_();
    if (param_2 == 1) {
      *(undefined4 *)(param_1 + 4) = 0xffffffff;
      iVar3 = param_1;
      for (iVar2 = 0; iVar2 < *(char *)(param_1 + 3); iVar2 = iVar2 + 1) {
        if (*(int *)(iVar3 + 8) != 0) {
          iVar1 = *(int *)(iVar3 + 0x18);
          local_28 = 1;
          local_20 = iVar1 + *(int *)(param_1 + 0x20) + -1;
          local_26 = 10;
          local_24 = (undefined2)((uint)iVar1 >> 0x10);
          local_22 = (undefined2)iVar1;
          local_1c = local_24;
          local_1a = local_22;
          zz_0219a44_(*(int *)(iVar3 + 8),(undefined4 *)&local_28);
          zz_02196f0_(*(int *)(iVar3 + 8),1);
        }
        iVar3 = iVar3 + 4;
      }
      *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 2;
    }
    else if (param_2 == 0) {
      iVar3 = param_1;
      for (iVar2 = 0; iVar2 < *(char *)(param_1 + 3); iVar2 = iVar2 + 1) {
        if (*(int *)(iVar3 + 8) != 0) {
          zz_02196f0_(*(int *)(iVar3 + 8),0);
        }
        iVar3 = iVar3 + 4;
      }
      iVar3 = param_1;
      for (iVar2 = 0; iVar2 < *(char *)(param_1 + 2); iVar2 = iVar2 + 1) {
        (**(code **)(**(int **)(iVar3 + 0x38) + 0x14))();
        iVar3 = iVar3 + 4;
      }
      *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 1;
    }
    else {
      zz_02793bc_(-0x7fd481a0);
    }
    zz_0279428_();
  }
  return;
}



// ==== 8027a064  zz_027a064_ ====

/* WARNING: Removing unreachable block (ram,0x8027a088) */

void zz_027a064_(int param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((param_1 != 0) && (param_2 != (*(byte *)(param_1 + 1) & 1))) {
    if (param_2 == 1) {
      zz_0279448_();
      iVar2 = param_1;
      iVar3 = param_1;
      iVar4 = param_1;
      for (iVar1 = 0; iVar1 < *(char *)(param_1 + 3); iVar1 = iVar1 + 1) {
        (**(code **)(**(int **)(iVar4 + 0x38) + 0x14))();
        gnt4_memset((void *)(iVar3 + 0x40),0,8);
        gnt4_memset((void *)(iVar3 + 0x50),0,8);
        gnt4_memset((void *)(iVar2 + 0xa8),0,0x20);
        iVar2 = iVar2 + 0x20;
        *(undefined4 *)(iVar4 + 0x60) = 0;
        iVar4 = iVar4 + 4;
        iVar3 = iVar3 + 8;
      }
      *(undefined4 *)(param_1 + 0x68) = 0;
      *(undefined4 *)(param_1 + 0x6c) = 0;
      *(undefined4 *)(param_1 + 0x78) = 0;
      *(undefined4 *)(param_1 + 0x7c) = 0;
      *(undefined4 *)(param_1 + 4) = 0xffffffff;
      *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) | 1;
      zz_0279428_();
    }
    else if (param_2 == 0) {
      iVar2 = param_1;
      for (iVar3 = 0; iVar3 < *(char *)(param_1 + 3); iVar3 = iVar3 + 1) {
        iVar4 = 0;
        do {
          if (*(int *)(iVar2 + 0x60) == 0) break;
          iVar1 = 0x30d4;
          do {
            iVar1 = iVar1 + -1;
          } while (iVar1 != 0);
          iVar4 = iVar4 + 1;
        } while (iVar4 < 200);
        if (iVar4 == 200) {
          zz_02793bc_(-0x7fd4817c);
          return;
        }
        iVar4 = 0;
        do {
          if (*(int *)(iVar2 + 0x70) == 0) break;
          iVar1 = 0x30d4;
          do {
            iVar1 = iVar1 + -1;
          } while (iVar1 != 0);
          iVar4 = iVar4 + 1;
        } while (iVar4 < 200);
        if (iVar4 == 200) {
          zz_02793bc_(-0x7fd48144);
          return;
        }
        iVar2 = iVar2 + 4;
      }
      *(byte *)(param_1 + 1) = *(byte *)(param_1 + 1) & 2;
    }
    else {
      zz_02793bc_(-0x7fd4810c);
    }
  }
  return;
}



// ==== 8027a264  zz_027a264_ ====

void zz_027a264_(void *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1 != (void *)0x0) {
    zz_0279ec4_((int)param_1,0);
    zz_027a064_((int)param_1,0);
    pvVar2 = param_1;
    for (iVar1 = 0; iVar1 < *(char *)((int)param_1 + 2); iVar1 = iVar1 + 1) {
      if (*(int **)((int)pvVar2 + 0x38) != (int *)0x0) {
        (**(code **)(**(int **)((int)pvVar2 + 0x38) + 0xc))();
      }
      if (*(undefined4 **)((int)pvVar2 + 0x10) != (undefined4 *)0x0) {
        zz_027ac98_(*(undefined4 **)((int)pvVar2 + 0x10));
      }
      zz_0279448_();
      if (*(int *)((int)pvVar2 + 8) != 0) {
        zz_021b398_(*(int *)((int)pvVar2 + 8));
        zz_0217028_(*(int **)((int)pvVar2 + 8));
      }
      zz_0279428_();
      pvVar2 = (void *)((int)pvVar2 + 4);
    }
    gnt4_memset(param_1,0,0xe8);
  }
  return;
}



// ==== 8027a334  zz_027a334_ ====

undefined1 * zz_027a334_(int *param_1,int param_2)

{
  undefined1 *__s;
  undefined4 *puVar1;
  undefined4 uVar2;
  int *piVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined1 *puVar9;
  int iVar10;
  undefined2 local_28;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  undefined2 local_20;
  undefined2 local_1e;
  undefined2 local_1c;
  
  if (param_2 < 1) {
    zz_02793bc_(-0x7fd480e8);
    __s = (undefined1 *)0x0;
  }
  else {
    piVar3 = param_1;
    iVar6 = param_2;
    if (param_1 == (int *)0x0) {
      zz_02793bc_(-0x7fd480c0);
      __s = (undefined1 *)0x0;
    }
    else {
      for (; iVar6 != 0; iVar6 = iVar6 + -1) {
        if (*piVar3 == 0) {
          zz_02793bc_(-0x7fd48098);
          return (undefined1 *)0x0;
        }
        piVar3 = piVar3 + 1;
      }
      pcVar4 = &DAT_80415654;
      iVar6 = 0;
      iVar10 = 2;
      do {
        iVar7 = iVar6;
        if (((((*pcVar4 == '\0') || (iVar7 = iVar6 + 1, pcVar4[0xe8] == '\0')) ||
             (iVar7 = iVar6 + 2, pcVar4[0x1d0] == '\0')) ||
            ((iVar7 = iVar6 + 3, pcVar4[0x2b8] == '\0' || (iVar7 = iVar6 + 4, pcVar4[0x3a0] == '\0')
             ))) || ((iVar7 = iVar6 + 5, pcVar4[0x488] == '\0' ||
                     ((iVar7 = iVar6 + 6, pcVar4[0x570] == '\0' ||
                      (iVar7 = iVar6 + 7, pcVar4[0x658] == '\0')))))) break;
        pcVar4 = pcVar4 + 0x740;
        iVar6 = iVar6 + 8;
        iVar10 = iVar10 + -1;
        iVar7 = iVar6;
      } while (iVar10 != 0);
      if (iVar7 == 0x10) {
        zz_02793bc_(-0x7fd48070);
        __s = (undefined1 *)0x0;
      }
      else {
        iVar6 = iVar7 * 0xe8;
        __s = &DAT_80415654 + iVar6;
        (&DAT_80415657)[iVar6] = (char)param_2;
        (&DAT_80415656)[iVar6] = (char)param_2;
        puVar9 = __s;
        for (uVar5 = 0; uVar5 < (uint)(int)(char)(&DAT_80415656)[iVar6]; uVar5 = uVar5 + 1) {
          iVar10 = *param_1;
          param_1 = param_1 + 1;
          *(int *)(puVar9 + 0x30) = iVar10;
          puVar9 = puVar9 + 4;
        }
        *(undefined4 *)(iVar6 + -0x7fbea928) = 0;
        *(undefined4 *)(iVar6 + -0x7fbea91c) = 0x7f;
        uVar5 = iVar7 << 1;
        *(undefined4 *)(iVar6 + -0x7fbea918) = 0xfffffc19;
        *(undefined4 *)(iVar6 + -0x7fbea914) = 0xfffffc19;
        *(undefined4 *)(iVar6 + -0x7fbea910) = 0;
        puVar9 = __s;
        for (uVar8 = 0; uVar8 < (uint)(int)(char)(&DAT_80415656)[iVar6]; uVar8 = uVar8 + 1) {
          *(uint *)(puVar9 + 0x28) = uVar5 | 0x80000000;
          puVar1 = zz_027acac_();
          *(undefined4 **)(puVar9 + 0x10) = puVar1;
          if (puVar1 == (undefined4 *)0x0) {
            zz_02793bc_(-0x7fd4804c);
            if (__s != (undefined1 *)0x0) {
              zz_0279ec4_((int)__s,0);
              zz_027a064_((int)__s,0);
              puVar9 = __s;
              for (iVar10 = 0; iVar10 < (char)(&DAT_80415656)[iVar6]; iVar10 = iVar10 + 1) {
                if (*(int **)(puVar9 + 0x38) != (int *)0x0) {
                  (**(code **)(**(int **)(puVar9 + 0x38) + 0xc))();
                }
                if (*(undefined4 **)(puVar9 + 0x10) != (undefined4 *)0x0) {
                  zz_027ac98_(*(undefined4 **)(puVar9 + 0x10));
                }
                zz_0279448_();
                if (*(int *)(puVar9 + 8) != 0) {
                  zz_021b398_(*(int *)(puVar9 + 8));
                  zz_0217028_(*(int **)(puVar9 + 8));
                }
                zz_0279428_();
                puVar9 = puVar9 + 4;
              }
              gnt4_memset(__s,0,0xe8);
            }
            return (undefined1 *)0x0;
          }
          uVar2 = zz_027ac80_(*(int *)(puVar9 + 0x10));
          *(undefined4 *)(puVar9 + 0x18) = uVar2;
          uVar2 = zz_027ac68_(*(int *)(puVar9 + 0x10));
          *(undefined4 *)(iVar6 + -0x7fbea98c) = uVar2;
          puVar1 = zz_02774e0_(*(int *)(puVar9 + 0x18) << 1,*(int *)(iVar6 + -0x7fbea98c) << 1,0);
          *(undefined4 **)(puVar9 + 0x38) = puVar1;
          if (*(int *)(puVar9 + 0x38) == 0) {
            zz_02793bc_(-0x7fd4802c);
            if (__s != (undefined1 *)0x0) {
              zz_0279ec4_((int)__s,0);
              zz_027a064_((int)__s,0);
              puVar9 = __s;
              for (iVar10 = 0; iVar10 < (char)(&DAT_80415656)[iVar6]; iVar10 = iVar10 + 1) {
                if (*(int **)(puVar9 + 0x38) != (int *)0x0) {
                  (**(code **)(**(int **)(puVar9 + 0x38) + 0xc))();
                }
                if (*(undefined4 **)(puVar9 + 0x10) != (undefined4 *)0x0) {
                  zz_027ac98_(*(undefined4 **)(puVar9 + 0x10));
                }
                zz_0279448_();
                if (*(int *)(puVar9 + 8) != 0) {
                  zz_021b398_(*(int *)(puVar9 + 8));
                  zz_0217028_(*(int **)(puVar9 + 8));
                }
                zz_0279428_();
                puVar9 = puVar9 + 4;
              }
              gnt4_memset(__s,0,0xe8);
            }
            return (undefined1 *)0x0;
          }
          piVar3 = zz_02170a8_(0x1f,-0x7fd855e0,0);
          *(int **)(puVar9 + 8) = piVar3;
          if (piVar3 == (int *)0x0) {
            zz_02793bc_(-0x7fd48010);
            if (__s != (undefined1 *)0x0) {
              zz_0279ec4_((int)__s,0);
              zz_027a064_((int)__s,0);
              puVar9 = __s;
              for (iVar10 = 0; iVar10 < (char)(&DAT_80415656)[iVar6]; iVar10 = iVar10 + 1) {
                if (*(int **)(puVar9 + 0x38) != (int *)0x0) {
                  (**(code **)(**(int **)(puVar9 + 0x38) + 0xc))();
                }
                if (*(undefined4 **)(puVar9 + 0x10) != (undefined4 *)0x0) {
                  zz_027ac98_(*(undefined4 **)(puVar9 + 0x10));
                }
                zz_0279448_();
                if (*(int *)(puVar9 + 8) != 0) {
                  zz_021b398_(*(int *)(puVar9 + 8));
                  zz_0217028_(*(int **)(puVar9 + 8));
                }
                zz_0279428_();
                puVar9 = puVar9 + 4;
              }
              gnt4_memset(__s,0,0xe8);
            }
            return (undefined1 *)0x0;
          }
          zz_0279448_();
          if (*(int *)(puVar9 + 8) != 0) {
            zz_021a51c_(*(int *)(puVar9 + 8),3,*(int *)(iVar6 + -0x7fbea928),
                        *(undefined4 *)(iVar6 + -0x7fbea918),*(undefined4 *)(iVar6 + -0x7fbea914),
                        0x40,*(undefined4 *)(iVar6 + -0x7fbea91c),
                        *(undefined4 *)(iVar6 + -0x7fbea910));
          }
          zz_0279428_();
          uVar5 = uVar5 + 1;
          puVar9 = puVar9 + 4;
        }
        if (__s != (undefined1 *)0x0) {
          *(short *)(iVar6 + -0x7fbea90c) = (short)DAT_80414588;
          *(undefined4 *)(iVar6 + -0x7fbea908) = DAT_803ae1f0;
          *(undefined2 *)(iVar6 + -0x7fbea90a) = 1;
        }
        iVar10 = 0;
        *(undefined2 *)(iVar6 + -0x7fbea90a) = 0;
        if (__s != (undefined1 *)0x0) {
          *(undefined4 *)(iVar6 + -0x7fbea988) = 48000;
          puVar9 = __s;
          for (; iVar10 < (char)(&DAT_80415656)[iVar6]; iVar10 = iVar10 + 1) {
            zz_0279448_();
            if (*(int *)(puVar9 + 8) != 0) {
              if (*(short *)(iVar6 + -0x7fbea90c) == 1) {
                local_26 = 0x7fa9;
              }
              else {
                local_26 = 0x8000;
              }
              local_28 = 1;
              local_24 = 0;
              local_22 = 0;
              local_20 = 0;
              local_1e = 0;
              local_1c = 0;
              zz_021962c_(*(int *)(puVar9 + 8),*(int *)(iVar6 + -0x7fbea908));
              zz_0219bf8_(*(int *)(puVar9 + 8),&local_28);
            }
            zz_0279428_();
            puVar9 = puVar9 + 4;
          }
        }
        if (__s != (undefined1 *)0x0) {
          *(undefined4 *)(iVar6 + -0x7fbea92c) = 0x10;
        }
        if ((&DAT_80415656)[iVar6] == '\x02') {
          if ((__s != (undefined1 *)0x0) && (*(int *)(iVar6 + -0x7fbea924) != -0xf)) {
            *(undefined4 *)(iVar6 + -0x7fbea924) = 0xfffffff1;
            zz_0279448_();
            if ((&DAT_8041565c)[iVar7 * 0x3a] != 0) {
              zz_021b3e0_((&DAT_8041565c)[iVar7 * 0x3a],DAT_803ae1f4);
            }
            zz_0279428_();
          }
          if (((__s != (undefined1 *)0x0) && ('\x01' < (char)(&DAT_80415656)[iVar6])) &&
             (*(int *)(iVar6 + -0x7fbea920) != 0xf)) {
            *(undefined4 *)(iVar6 + -0x7fbea920) = 0xf;
            zz_0279448_();
            if ((&DAT_80415660)[iVar7 * 0x3a] != 0) {
              zz_021b3e0_((&DAT_80415660)[iVar7 * 0x3a],DAT_803ae26c);
            }
            zz_0279428_();
          }
        }
        else if (((__s != (undefined1 *)0x0) && ('\0' < (char)(&DAT_80415656)[iVar6])) &&
                (*(int *)(iVar6 + -0x7fbea924) != 0)) {
          *(undefined4 *)(iVar6 + -0x7fbea924) = 0;
          zz_0279448_();
          if ((&DAT_8041565c)[iVar7 * 0x3a] != 0) {
            zz_021b3e0_((&DAT_8041565c)[iVar7 * 0x3a],DAT_803ae230);
          }
          zz_0279428_();
        }
        *(undefined1 *)(iVar6 + -0x7fbea9ab) = 0;
        *__s = 1;
      }
    }
  }
  return __s;
}



// ==== 8027aa20  FUN_8027aa20 ====

void FUN_8027aa20(int param_1)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  puVar2 = &DAT_80415654;
  do {
    iVar4 = 0;
    iVar5 = 2;
    puVar1 = puVar2;
    do {
      if (param_1 == *(int *)(puVar1 + 8)) {
        zz_021b398_((&DAT_8041565c)[iVar4 + iVar3 * 0x3a]);
        (&DAT_8041565c)[iVar4 + iVar3 * 0x3a] = 0;
        return;
      }
      puVar1 = puVar1 + 4;
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 0xe8;
  } while (iVar3 < 0x10);
  return;
}



// ==== 8027aab4  zz_027aab4_ ====

void zz_027aab4_(void)

{
  int iVar1;
  char *__s;
  char *pcVar2;
  int iVar3;
  
  DAT_80414580 = DAT_80414580 + -1;
  if (DAT_80414580 == 0) {
    iVar1 = 0;
    __s = &DAT_80415654;
    do {
      if ((*__s == '\x01') && (__s != (char *)0x0)) {
        zz_0279ec4_((int)__s,0);
        zz_027a064_((int)__s,0);
        pcVar2 = __s;
        for (iVar3 = 0; iVar3 < __s[2]; iVar3 = iVar3 + 1) {
          if (*(int **)(pcVar2 + 0x38) != (int *)0x0) {
            (**(code **)(**(int **)(pcVar2 + 0x38) + 0xc))();
          }
          if (*(undefined4 **)(pcVar2 + 0x10) != (undefined4 *)0x0) {
            zz_027ac98_(*(undefined4 **)(pcVar2 + 0x10));
          }
          zz_0279448_();
          if (*(int *)(pcVar2 + 8) != 0) {
            zz_021b398_(*(int *)(pcVar2 + 8));
            zz_0217028_(*(int **)(pcVar2 + 8));
          }
          zz_0279428_();
          pcVar2 = pcVar2 + 4;
        }
        gnt4_memset(__s,0,0xe8);
      }
      iVar1 = iVar1 + 1;
      __s = __s + 0xe8;
    } while (iVar1 < 0x10);
    gnt4_memset(&DAT_80415654,0,0xe80);
    zz_027adb4_();
  }
  return;
}



// ==== 8027abd4  zz_027abd4_ ====

void zz_027abd4_(void)

{
  if (DAT_80414580 == 0) {
    zz_027af20_();
    gnt4_memset(&DAT_80415654,0,0xe80);
    DAT_80414584 = &DAT_80414620;
  }
  DAT_80414580 = DAT_80414580 + 1;
  return;
}



// ==== 8027ac48  zz_027ac48_ ====

void zz_027ac48_(undefined4 param_1,undefined4 param_2)

{
  zz_0279414_(param_1,param_2);
  return;
}



// ==== 8027ac68  zz_027ac68_ ====

undefined4 zz_027ac68_(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 8);
}



// ==== 8027ac80  zz_027ac80_ ====

undefined4 zz_027ac80_(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 4);
}



// ==== 8027ac98  zz_027ac98_ ====

void zz_027ac98_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 8027acac  zz_027acac_ ====

undefined4 * zz_027acac_(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  piVar1 = &DAT_804164ec;
  iVar5 = 4;
  do {
    iVar4 = iVar3;
    if (((((*piVar1 == 0) || (iVar4 = iVar3 + 1, piVar1[3] == 0)) ||
         (iVar4 = iVar3 + 2, piVar1[6] == 0)) ||
        ((iVar4 = iVar3 + 3, piVar1[9] == 0 || (iVar4 = iVar3 + 4, piVar1[0xc] == 0)))) ||
       ((iVar4 = iVar3 + 5, piVar1[0xf] == 0 ||
        ((iVar4 = iVar3 + 6, piVar1[0x12] == 0 || (iVar4 = iVar3 + 7, piVar1[0x15] == 0)))))) break;
    piVar1 = piVar1 + 0x18;
    iVar3 = iVar3 + 8;
    iVar5 = iVar5 + -1;
    iVar4 = iVar3;
  } while (iVar5 != 0);
  if (iVar4 == 0x20) {
    zz_02793bc_(-0x7fd47fe8);
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2 = &DAT_804164ec + iVar4 * 3;
    *puVar2 = 1;
  }
  return puVar2;
}



// ==== 8027adb4  zz_027adb4_ ====

void zz_027adb4_(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int local_18 [5];
  
  DAT_804164d8 = DAT_804164d8 + -1;
  if (DAT_804164d8 == 0) {
    piVar2 = &DAT_804164ec;
    iVar3 = 4;
    do {
      if ((*piVar2 == 1) && (piVar2 != (int *)0x0)) {
        *piVar2 = 0;
      }
      piVar1 = piVar2 + 3;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 6;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 9;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 0xc;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 0xf;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 0x12;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar1 = piVar2 + 0x15;
      if ((*piVar1 == 1) && (piVar1 != (int *)0x0)) {
        *piVar1 = 0;
      }
      piVar2 = piVar2 + 0x18;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    gnt4_memset(&DAT_804164ec,0,0x180);
    if (DAT_804164dc == 0) {
      ARFree(local_18);
      if (local_18[0] != DAT_804164e4) {
        zz_02793bc_(-0x7fd47fc4);
      }
      DAT_804164e0 = 0;
      DAT_804164e4 = 0;
      DAT_804164e8 = 0;
    }
  }
  return;
}



// ==== 8027af20  zz_027af20_ ====

void zz_027af20_(void)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  
  if (DAT_804164d8 == 0) {
    if (DAT_804164dc == 0) {
      DAT_804164e0 = 0x20;
      DAT_804164e4 = 0x40000;
      DAT_804164e8 = ARAlloc(0x40000);
    }
    gnt4_memset(&DAT_804164ec,0,0x180);
    iVar1 = DAT_804164e8;
    uVar2 = DAT_804164e0;
    puVar6 = &DAT_804164ec;
    iVar3 = 0;
    if (DAT_804164e0 != 0) {
      uVar7 = DAT_804164e0 >> 3;
      if (uVar7 != 0) {
        do {
          puVar6[1] = (uint)(iVar1 + iVar3) >> 1;
          puVar6[2] = 0x1000;
          puVar6[4] = (uint)(iVar1 + iVar3 + 0x2000) >> 1;
          puVar6[5] = 0x1000;
          puVar6[7] = (uint)(iVar1 + iVar3 + 0x4000) >> 1;
          puVar6[8] = 0x1000;
          puVar6[10] = (uint)(iVar1 + iVar3 + 0x6000) >> 1;
          iVar4 = iVar3 + 0xc000;
          puVar6[0xb] = 0x1000;
          puVar6[0xd] = (uint)(iVar1 + iVar3 + 0x8000) >> 1;
          iVar5 = iVar3 + 0xe000;
          puVar6[0xe] = 0x1000;
          puVar6[0x10] = (uint)(iVar1 + iVar3 + 0xa000) >> 1;
          iVar3 = iVar3 + 0x10000;
          puVar6[0x11] = 0x1000;
          puVar6[0x13] = (uint)(iVar1 + iVar4) >> 1;
          puVar6[0x14] = 0x1000;
          puVar6[0x16] = (uint)(iVar1 + iVar5) >> 1;
          puVar6[0x17] = 0x1000;
          puVar6 = puVar6 + 0x18;
          uVar7 = uVar7 - 1;
        } while (uVar7 != 0);
        uVar2 = uVar2 & 7;
        if (uVar2 == 0) goto LAB_8027b078;
      }
      do {
        uVar7 = iVar1 + iVar3;
        iVar3 = iVar3 + 0x2000;
        puVar6[1] = uVar7 >> 1;
        puVar6[2] = 0x1000;
        puVar6 = puVar6 + 3;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
  }
LAB_8027b078:
  DAT_804164d8 = DAT_804164d8 + 1;
  return;
}



// ==== 8027b098  zz_027b098_ ====

void zz_027b098_(void *param_1,int param_2,undefined4 *param_3,uint *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  *param_3 = 0;
  *param_4 = 0;
  if ((param_1 != (void *)0x0) && (0 < param_2)) {
    for (iVar3 = 0; iVar3 < param_2; iVar3 = iVar3 + 1) {
      iVar1 = gnt4_memcmp(param_1,&DAT_802b80a4,1);
      if ((iVar1 == 0) && (iVar1 = gnt4_memcmp(param_1,s_<SUDPS_>_802b80a8,8), iVar1 == 0)) {
        *param_3 = param_1;
        uVar2 = countLeadingZeros(*param_3);
        *param_4 = ~-(uVar2 >> 5 & 1) & 0x14;
      }
      param_1 = (void *)((int)param_1 + 1);
    }
  }
  return;
}



// ==== 8027b160  zz_027b160_ ====

uint zz_027b160_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((param_1 == 0) || (param_2 < 0)) {
    uVar1 = 0;
  }
  else {
    iVar2 = gnt4_strncmp((char *)(param_1 + 0x13),&DAT_802b80a0,1);
    uVar1 = countLeadingZeros(iVar2);
    uVar1 = uVar1 >> 5;
  }
  return uVar1;
}



// ==== 8027b1b0  zz_027b1b0_ ====

uint zz_027b1b0_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if ((param_1 == 0) || (param_2 < 0)) {
    uVar1 = 0;
  }
  else {
    iVar2 = gnt4_strncmp((char *)(param_1 + 0x12),&DAT_802b809c,1);
    uVar1 = countLeadingZeros(iVar2);
    uVar1 = uVar1 >> 5;
  }
  return uVar1;
}



// ==== 8027b200  zz_027b200_ ====

void zz_027b200_(void)

{
  if (0 < DAT_80416670) {
    return;
  }
  DAT_80416670 = DAT_80416670 + 1;
  DAT_80416674 = s_CRI_SUD_GC_Ver_0_02_Build_Feb_6_2_802b8068;
  return;
}



// ==== 8027b230  zz_027b230_ ====

void zz_027b230_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x30) = param_2;
  return;
}



// ==== 8027b238  zz_027b238_ ====

void zz_027b238_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (*(int *)(param_1 + 0x10) != 1) {
    *param_2 = 0;
    *param_3 = 0;
    return;
  }
  *param_2 = *(undefined4 *)(param_1 + 0x14);
  *param_3 = *(undefined4 *)(param_1 + 0x18);
  return;
}



// ==== 8027b268  zz_027b268_ ====

void zz_027b268_(int param_1,int param_2,undefined4 param_3)

{
  char *pcVar1;
  int iVar2;
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  
  iVar2 = *(int *)(param_1 + 0x20);
  *(int *)(param_1 + 0x14) = param_2;
  *(undefined4 *)(param_1 + 0x18) = param_3;
  local_10 = param_2;
  local_c = param_3;
  pcVar1 = zz_02777b8_(&local_10,&DAT_802b80b8,s_SFXINFE_802b80c0,&local_18);
  if (pcVar1 == (char *)0x0) {
    zz_027b9a0_(iVar2,0,0);
  }
  else {
    zz_027b9a0_(iVar2,local_18,local_14);
  }
  *(undefined4 *)(param_1 + 0x10) = 1;
  return;
}



// ==== 8027b304  zz_027b304_ ====

void zz_027b304_(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  *(undefined4 *)(param_1 + 0xc) = param_3;
  return;
}



// ==== 8027b310  zz_027b310_ ====

void zz_027b310_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}



// ==== 8027b318  zz_027b318_ ====

void zz_027b318_(int param_1,int *param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  
  iVar4 = *param_2;
  if (*(int *)(param_1 + 4) == 0) {
    uVar3 = zz_027b500_();
    *(undefined4 *)(param_1 + 4) = uVar3;
  }
  if (iVar4 != 3) {
    zz_027b508_(param_1,param_2,s_E201193__SFX_CnvFrmY84C44___frmf_802b82c0);
    return;
  }
  iVar4 = *(int *)(param_1 + 4);
  if (iVar4 == 0x41) {
LAB_8027b4c8:
    zz_027b508_(param_1,param_2,s_E201192__CnvToY84C44___compo_is_n_802b8290);
    return;
  }
  if (iVar4 < 0x41) {
    if (((iVar4 == 0x21) || (0x20 < iVar4)) || (iVar4 != 0x11)) goto LAB_8027b4c8;
  }
  else if (iVar4 != 0x101) goto LAB_8027b4c8;
  local_48 = param_2[1];
  local_44 = param_2[5];
  local_40 = param_2[9];
  local_3c = param_2[2];
  local_38 = param_2[6];
  local_34 = param_2[10];
  iVar4 = *(int *)(param_1 + 8);
  if (iVar4 == 0) {
    iVar4 = local_3c;
  }
  uVar5 = *(uint *)(param_1 + 0xc);
  if (uVar5 == 0) {
    uVar5 = param_2[3];
  }
  iVar2 = *(int *)(param_1 + 4);
  if (iVar2 == 0x41) goto LAB_8027b474;
  if (iVar2 < 0x41) {
    if (iVar2 != 0x21) {
      if (iVar2 < 0x21) {
        if (iVar2 != 0x11) {
LAB_8027b484:
          zz_027b508_(0,0,s_E201312__sfxcnv_IsCnvUpHalf___co_802b80c8);
          bVar1 = false;
          goto LAB_8027b498;
        }
      }
      else if (iVar2 != 0x31) goto LAB_8027b484;
LAB_8027b474:
      bVar1 = false;
      goto LAB_8027b498;
    }
  }
  else if (iVar2 != 0x101) {
    if (iVar2 < 0x101) {
      if (iVar2 != 0xf1) goto LAB_8027b484;
    }
    else if (iVar2 != 0x1001) goto LAB_8027b484;
    goto LAB_8027b474;
  }
  bVar1 = true;
LAB_8027b498:
  if (bVar1) {
    uVar5 = (int)uVar5 / 2;
  }
  zz_02afd0c_(&local_48,param_3,param_4,iVar4,uVar5);
  return;
}



// ==== 8027b500  zz_027b500_ ====

undefined4 zz_027b500_(void)

{
  return 0x11;
}



// ==== 8027b508  zz_027b508_ ====

void zz_027b508_(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  DAT_8041668c = DAT_8041668c + 1;
  if (DAT_80416684 != (code *)0x0) {
    (*DAT_80416684)(DAT_80416688,param_3);
  }
  return;
}



// ==== 8027b554  zz_027b554_ ====

void zz_027b554_(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)param_1[0xb];
    *param_1 = 0;
    zz_027ba78_((undefined4 *)param_1[8]);
    zz_027b8c0_(puVar1);
    DAT_8041667c = DAT_8041667c + -1;
  }
  return;
}



// ==== 8027b5b4  zz_027b5b4_ ====

int * zz_027b5b4_(int param_1,uint param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int *__s;
  
  __s = &DAT_80416694;
  iVar1 = DAT_80416680;
  if (0 < DAT_80416680) {
    do {
      if (*__s == 0) goto LAB_8027b618;
      __s = __s + 0x24;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  __s = (int *)0x0;
LAB_8027b618:
  if (__s != (int *)0x0) {
    if (((int)param_2 >> 0x1f) + (uint)(0x301e < param_2) == 1) {
      gnt4_memset(__s,0,0x90);
      __s[1] = 0;
      __s[2] = 0;
      __s[3] = 0;
      __s[9] = 1;
      __s[10] = 0;
      __s[0xd] = 0;
      __s[0xe] = param_1 + 0x1fU & 0xffffffe0;
      __s[0xf] = __s[0xe] + 0x400;
      __s[0x10] = __s[0xf] + 0x400;
      __s[0x11] = __s[0x10] + 0x400;
      __s[0x14] = param_1;
      __s[0x15] = param_2;
      __s[0x18] = -1;
      *__s = 1;
      iVar1 = zz_027ba9c_();
      if (iVar1 == 0) {
        DAT_8041668c = DAT_8041668c + 1;
        if (DAT_80416684 != (code *)0x0) {
          (*DAT_80416684)(DAT_80416688,s_E201281__SfxZHn__can_t_create__802b8510);
        }
        if (__s != (int *)0x0) {
          puVar2 = (undefined4 *)__s[0xb];
          *__s = 0;
          zz_027ba78_((undefined4 *)__s[8]);
          zz_027b8c0_(puVar2);
          DAT_8041667c = DAT_8041667c + -1;
        }
        __s = (int *)0x0;
      }
      else {
        __s[8] = iVar1;
        iVar1 = zz_027b8e4_();
        if (iVar1 == 0) {
          DAT_8041668c = DAT_8041668c + 1;
          if (DAT_80416684 != (code *)0x0) {
            (*DAT_80416684)(DAT_80416688,s_E202011__SfxAHn__can_t_create__802b8530);
          }
          if (__s != (int *)0x0) {
            puVar2 = (undefined4 *)__s[0xb];
            *__s = 0;
            zz_027ba78_((undefined4 *)__s[8]);
            zz_027b8c0_(puVar2);
            DAT_8041667c = DAT_8041667c + -1;
          }
          __s = (int *)0x0;
        }
        else {
          __s[0xb] = iVar1;
          DAT_8041667c = DAT_8041667c + 1;
        }
      }
    }
    else {
      DAT_8041668c = DAT_8041668c + 1;
      if (DAT_80416684 != (code *)0x0) {
        (*DAT_80416684)(DAT_80416688,s_E201194__sfx_InitHn__work_size_i_802b84e4);
      }
      __s = (int *)0x0;
    }
  }
  return __s;
}



// ==== 8027b828  zz_027b828_ ====

void zz_027b828_(undefined4 param_1,undefined4 param_2)

{
  DAT_80416684 = param_1;
  DAT_80416688 = param_2;
  return;
}



// ==== 8027b83c  zz_027b83c_ ====

void zz_027b83c_(void)

{
  if (DAT_80416678 < 1) {
    DAT_80416b24 = s_CRI_SFX_GC_Ver_1_22_Build_Feb_6_2_802b84b0;
    gnt4_memset(&DAT_8041667c,0,0x4a8);
    DAT_80416680 = 8;
    DAT_80416690 = 1;
    zz_02b0038_();
    zz_027bbb8_();
    zz_027bb0c_();
    zz_027b960_();
    DAT_80416678 = DAT_80416678 + 1;
  }
  return;
}



// ==== 8027b8c0  zz_027b8c0_ ====

void zz_027b8c0_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 0;
  DAT_80416b28 = DAT_80416b28 + -1;
  return;
}



// ==== 8027b8e4  zz_027b8e4_ ====

void zz_027b8e4_(void)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = &DAT_80416b30;
  iVar2 = DAT_80416b2c;
  if (0 < DAT_80416b2c) {
    do {
      if (*piVar1 == 0) goto LAB_8027b91c;
      piVar1 = piVar1 + 5;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  piVar1 = (int *)0x0;
LAB_8027b91c:
  if (piVar1 != (int *)0x0) {
    piVar1[2] = 0;
    piVar1[3] = 0x1f;
    piVar1[4] = 100;
    piVar1[1] = 1;
    DAT_80416b28 = DAT_80416b28 + 1;
    *piVar1 = 1;
    return;
  }
  return;
}



// ==== 8027b960  zz_027b960_ ====

void zz_027b960_(void)

{
  gnt4_memset(&DAT_80416b28,0,0xa8);
  DAT_80416b2c = 8;
  return;
}



// ==== 8027b9a0  zz_027b9a0_ ====

void zz_027b9a0_(int param_1,undefined4 param_2,undefined4 param_3)

{
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  
  *(undefined4 *)(param_1 + 8) = 1;
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  local_18 = *(int *)(param_1 + 0xc);
  if (local_18 == 0) {
    *(undefined4 *)(param_1 + 0x18) = 1;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)(param_1 + 0x20) = 0;
    *(undefined4 *)(param_1 + 0x28) = 1;
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  else {
    local_14 = *(undefined4 *)(param_1 + 0x10);
    zz_02777b8_(&local_18,s_ZMHDR_802b85e8,s_SFXINFE_802b85b0,&local_10);
    *(undefined4 *)(param_1 + 0x18) = 1;
    *(int *)(param_1 + 0x1c) = local_10;
    *(undefined4 *)(param_1 + 0x20) = local_c;
    zz_02777b8_(&local_18,s_ZMVFRM_802b85f0,s_SFXINFE_802b85b0,&local_10);
    *(undefined4 *)(param_1 + 0x28) = 1;
    *(int *)(param_1 + 0x2c) = local_10;
    *(undefined4 *)(param_1 + 0x30) = local_c;
  }
  return;
}



// ==== 8027ba78  zz_027ba78_ ====

void zz_027ba78_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 0;
  DAT_80416bd0 = DAT_80416bd0 + -1;
  return;
}



// ==== 8027ba9c  zz_027ba9c_ ====

void zz_027ba9c_(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = DAT_802b8550;
  piVar2 = &DAT_80416bdc;
  iVar3 = DAT_80416bd8;
  if (0 < DAT_80416bd8) {
    do {
      if (*piVar2 == 0) goto LAB_8027bad4;
      piVar2 = piVar2 + 0x11;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  piVar2 = (int *)0x0;
LAB_8027bad4:
  if (piVar2 != (int *)0x0) {
    piVar2[0xf] = DAT_802b8550;
    piVar2[0x10] = iVar1;
    DAT_80416bd0 = DAT_80416bd0 + 1;
    *piVar2 = 1;
    return;
  }
  return;
}



// ==== 8027bb0c  zz_027bb0c_ ====

void zz_027bb0c_(void)

{
  gnt4_memset(&DAT_80416bd0,0,0x22c);
  DAT_80416bd8 = 8;
  DAT_80416bd4 = 0;
  return;
}



// ==== 8027bb54  zz_027bb54_ ====

void zz_027bb54_(int param_1)

{
  zz_027b160_(*(int *)(param_1 + 0x58),*(int *)(param_1 + 0x5c));
  return;
}



// ==== 8027bb80  zz_027bb80_ ====

void zz_027bb80_(int param_1)

{
  zz_027b1b0_(*(int *)(param_1 + 0x58),*(int *)(param_1 + 0x5c));
  return;
}



// ==== 8027bbac  zz_027bbac_ ====

void zz_027bbac_(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x58) = param_2;
  *(undefined4 *)(param_1 + 0x5c) = param_3;
  return;
}



// ==== 8027bbb8  zz_027bbb8_ ====

void zz_027bbb8_(void)

{
  zz_027b200_();
  return;
}



// ==== 8027bbd8  zz_027bbd8_ ====

void zz_027bbd8_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double *pdVar4;
  double *pdVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double local_248 [65];
  
  iVar3 = 0;
  iVar6 = 0;
  iVar1 = 0;
  do {
    iVar2 = iVar6 << 3;
    iVar7 = 0;
    iVar8 = 4;
    do {
      pdVar4 = (double *)(param_3 + iVar7);
      dVar24 = *(double *)(param_1 + iVar1);
      dVar21 = *(double *)(param_1 + (iVar6 + 1) * 8);
      dVar19 = *(double *)(param_1 + (iVar6 + 2) * 8);
      dVar17 = *(double *)(param_1 + (iVar6 + 3) * 8);
      dVar15 = *(double *)(param_1 + (iVar6 + 4) * 8);
      dVar13 = *(double *)(param_1 + (iVar6 + 5) * 8);
      pdVar5 = (double *)(param_3 + iVar7 + 8);
      dVar11 = *(double *)(param_1 + (iVar6 + 6) * 8);
      dVar9 = *(double *)(param_1 + (iVar6 + 7) * 8);
      iVar7 = iVar7 + 0x10;
      dVar23 = *pdVar5;
      dVar22 = pdVar5[8];
      dVar20 = pdVar5[0x10];
      dVar18 = pdVar5[0x18];
      dVar16 = pdVar5[0x20];
      dVar14 = pdVar5[0x28];
      dVar12 = pdVar5[0x30];
      dVar10 = pdVar5[0x38];
      *(double *)((int)local_248 + iVar2) =
           pdVar4[0x38] * dVar9 +
           pdVar4[0x30] * dVar11 +
           pdVar4[0x28] * dVar13 +
           pdVar4[0x20] * dVar15 +
           pdVar4[0x18] * dVar17 +
           pdVar4[0x10] * dVar19 + pdVar4[8] * dVar21 + *pdVar4 * dVar24 + DAT_802b85f8;
      *(double *)((int)local_248 + iVar2 + 8) =
           dVar10 * dVar9 +
           dVar12 * dVar11 +
           dVar14 * dVar13 +
           dVar16 * dVar15 +
           dVar18 * dVar17 + dVar20 * dVar19 + dVar22 * dVar21 + dVar23 * dVar24 + DAT_802b85f8;
      iVar2 = iVar2 + 0x10;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    iVar3 = iVar3 + 1;
    iVar1 = iVar1 + 0x40;
    iVar6 = iVar6 + 8;
  } while (iVar3 < 8);
  iVar3 = 0;
  iVar1 = 0;
  do {
    iVar2 = 0;
    iVar6 = iVar3 << 3;
    iVar7 = 4;
    do {
      pdVar4 = (double *)(param_3 + iVar2);
      dVar16 = *(double *)((int)local_248 + iVar1);
      dVar15 = local_248[iVar3 + 8];
      dVar14 = local_248[iVar3 + 0x10];
      dVar13 = local_248[iVar3 + 0x18];
      dVar12 = local_248[iVar3 + 0x20];
      dVar11 = local_248[iVar3 + 0x28];
      pdVar5 = (double *)(param_3 + iVar2 + 8);
      dVar10 = local_248[iVar3 + 0x30];
      dVar9 = local_248[iVar3 + 0x38];
      iVar2 = iVar2 + 0x10;
      *(double *)(param_2 + iVar6) =
           pdVar4[0x38] * dVar9 +
           pdVar4[0x30] * dVar10 +
           pdVar4[0x28] * dVar11 +
           pdVar4[0x20] * dVar12 +
           pdVar4[0x18] * dVar13 +
           pdVar4[0x10] * dVar14 + pdVar4[8] * dVar15 + *pdVar4 * dVar16 + DAT_802b85f8;
      *(double *)(param_2 + iVar6 + 0x40) =
           pdVar5[0x38] * dVar9 +
           pdVar5[0x30] * dVar10 +
           pdVar5[0x28] * dVar11 +
           pdVar5[0x20] * dVar12 +
           pdVar5[0x18] * dVar13 +
           pdVar5[0x10] * dVar14 + pdVar5[8] * dVar15 + *pdVar5 * dVar16 + DAT_802b85f8;
      iVar6 = iVar6 + 0x80;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    iVar3 = iVar3 + 1;
    iVar1 = iVar1 + 8;
  } while (iVar3 < 8);
  return;
}



// ==== 8027be8c  FUN_8027be8c ====

void FUN_8027be8c(int param_1,int param_2)

{
  zz_027bbd8_(param_1,param_2,-0x7fbe9200);
  return;
}



// ==== 8027beb4  FUN_8027beb4 ====

void FUN_8027beb4(void)

{
  uint uVar1;
  uint uVar2;
  double *pdVar3;
  double *pdVar4;
  double *pdVar5;
  double *pdVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  FUN_80232a10();
  pdVar6 = (double *)&DAT_80416e00;
  DAT_80417200 = zz_027bfb4_();
  pdVar3 = (double *)&DAT_80417000;
  uVar2 = 0;
  dVar10 = DAT_802b8618;
  dVar11 = DAT_802b8600;
  dVar12 = DAT_802b8608;
  do {
    dVar9 = DAT_802b8600;
    if (uVar2 == 0) {
      dVar9 = DAT_802b8610;
    }
    uVar1 = 0;
    dVar8 = dVar10 * ((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar12);
    pdVar4 = pdVar3;
    pdVar5 = pdVar6;
    do {
      dVar7 = gnt4_cos_bl(dVar8 * (dVar11 + ((double)CONCAT44(0x43300000,uVar1 ^ 0x80000000) -
                                            dVar12)));
      uVar1 = uVar1 + 1;
      *pdVar5 = dVar9 * dVar7;
      pdVar5 = pdVar5 + 1;
      *pdVar4 = dVar9 * dVar7;
      pdVar4 = pdVar4 + 8;
    } while ((int)uVar1 < 8);
    uVar2 = uVar2 + 1;
    pdVar3 = pdVar3 + 1;
    pdVar6 = pdVar6 + 8;
  } while ((int)uVar2 < 8);
  FUN_80232a5c();
  return;
}



// ==== 8027bfb4  zz_027bfb4_ ====

void zz_027bfb4_(void)

{
  DAT_80417208 = s_CRI_DCT_GC_Ver_1_803_Build_Feb_6_802b8620;
  return;
}



