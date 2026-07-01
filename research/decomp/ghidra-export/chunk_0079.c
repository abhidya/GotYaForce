// ==== 802a9710  zz_02a9710_ ====

undefined4 zz_02a9710_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined4 local_18;
  int local_14;
  int local_10;
  uint local_c;
  
  iVar1 = zz_02a3744_(*(int *)(param_1 + 0x40),&local_10,&local_c);
  if (iVar1 == 0) {
    if ((local_c < 0x800) || (local_10 == 0)) {
      uVar2 = 0xffffffff;
    }
    else {
      piVar3 = zz_02a91d8_(local_10,local_c);
      if (piVar3 == (int *)0x0) {
        uVar2 = 0xffffffff;
      }
      else {
        iVar1 = zz_02a8f78_(piVar3,&local_14);
        if ((iVar1 == 0) || (local_14 == 0)) {
          zz_02a91ac_(piVar3);
          uVar2 = 0xffffffff;
        }
        else {
          iVar1 = zz_02a8324_(piVar3,&local_18);
          uVar2 = local_18;
          if (iVar1 == 0) {
            uVar2 = 0xffffffff;
          }
          zz_02a91ac_(piVar3);
        }
      }
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// ==== 802a97e8  zz_02a97e8_ ====

undefined4
zz_02a97e8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E202231__mwPlyGetNumSkipDisp__ha_802b90e0,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_9 + 0x84);
  }
  return uVar2;
}



// ==== 802a9838  zz_02a9838_ ====

void zz_02a9838_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122615__mwPlyRelCurFrm__handle_802b9148,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    uVar4 = *(undefined4 *)(param_9 + 0x78);
    iVar3 = *(int *)(param_9 + 0x7c);
    iVar2 = *(int *)(param_9 + 0x80);
    iVar1 = zz_02af50c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar2 < iVar3) {
      zz_02a1008_(iVar1,uVar4);
      *(int *)(param_9 + 0x80) = *(int *)(param_9 + 0x80) + 1;
      *(undefined4 *)(param_9 + 0x7c) = *(undefined4 *)(param_9 + 0x80);
    }
  }
  return;
}



// ==== 802a98d0  zz_02a98d0_ ====

void zz_02a98d0_(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  short local_c;
  short local_a;
  
  zz_02a05b4_(param_1,param_2,param_3,&local_18);
  *param_4 = local_10;
  param_4[1] = local_18;
  param_4[2] = local_14;
  param_4[3] = (int)local_a;
  param_4[4] = (int)local_c;
  param_4[5] = (int)local_c;
  return;
}



// ==== 802a9930  zz_02a9930_ ====

void zz_02a9930_(int param_1)

{
  *(undefined4 *)(param_1 + 0xb4) = 0;
  *(undefined4 *)(param_1 + 0xb8) = 0;
  zz_02ab0c8_(param_1,0);
  return;
}



// ==== 802a9960  zz_02a9960_ ====

void zz_02a9960_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 *param_10,undefined4 *param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  uint uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined8 uVar18;
  uint local_58;
  undefined4 local_54;
  undefined4 local_50;
  
  iVar2 = param_10[7];
  iVar5 = *(int *)(param_9 + 0x40);
  uVar14 = param_10[8];
  if (iVar2 == 2) {
    uVar17 = 2;
  }
  else if (iVar2 < 2) {
    if (iVar2 < 1) {
LAB_802a99c4:
      uVar17 = 3;
    }
    else {
      uVar17 = 1;
    }
  }
  else {
    if (3 < iVar2) goto LAB_802a99c4;
    uVar17 = 3;
  }
  iVar2 = param_10[4];
  uVar13 = *param_10;
  uVar12 = param_10[1];
  uVar11 = param_10[2];
  uVar10 = param_10[3];
  puVar4 = param_11;
  if (iVar2 == 3) {
    uVar16 = 3;
    goto LAB_802a9a38;
  }
  if (iVar2 < 3) {
    if (iVar2 == 1) {
      uVar16 = 1;
      goto LAB_802a9a38;
    }
    if (0 < iVar2) {
      uVar16 = 2;
      goto LAB_802a9a38;
    }
  }
  else if (iVar2 < 5) {
    uVar16 = 4;
    goto LAB_802a9a38;
  }
  param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        s_mwl_convPtypeFromSFD___Invalid_P_802b91d0,param_10,param_11,param_12,
                        param_13,param_14,param_15,param_16);
  uVar16 = 1;
LAB_802a9a38:
  local_50 = param_10[9];
  iVar9 = param_10[0xd];
  puVar3 = &local_58;
  local_54 = param_10[10];
  iVar8 = param_10[6];
  uVar7 = param_10[0xc];
  uVar6 = param_10[0xb];
  iVar2 = zz_02a4124_(iVar5,puVar3);
  if (iVar2 != 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E201301__MWSFD__GetFps_failed__802b91f8,puVar3,puVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
  uVar1 = local_58;
  uVar15 = (uint)((ulonglong)((longlong)iVar8 * 1000) >> 0x20);
  iVar2 = (int)local_58 >> 0x1f;
  uVar18 = gnt4___div2i((uint)((ulonglong)((longlong)iVar9 * (longlong)(int)local_58) >> 0x20),
                        iVar9 * local_58,uVar15,iVar8 * 1000);
  *param_11 = uVar14;
  param_11[1] = uVar17;
  param_11[2] = uVar13;
  param_11[3] = uVar12;
  param_11[4] = uVar11;
  param_11[5] = uVar10;
  param_11[6] = uVar16;
  param_11[7] = local_58;
  param_11[8] = (int)uVar18;
  param_11[9] = iVar9;
  param_11[10] = iVar8;
  param_11[0xb] = uVar6;
  uVar18 = gnt4___div2i((int)((ulonglong)uVar1 * (ulonglong)uVar7 >> 0x20) + iVar2 * uVar7 +
                        uVar1 * ((int)uVar7 >> 0x1f),uVar1 * uVar7,uVar15,iVar8 * 1000);
  param_11[0xc] = (int)uVar18;
  param_11[0xd] = uVar7;
  param_11[0xe] = local_50;
  param_11[0xf] = local_54;
  iVar5 = *(int *)(param_9 + 0xd4);
  iVar9 = *(int *)param_10[0xe];
  iVar8 = ((int *)param_10[0xe])[1];
  iVar2 = zz_02ade24_();
  if (iVar2 == 1) {
    if (iVar5 == param_9 + 0xbc) {
      param_11[0x10] = 0;
      param_11[0x11] = 0;
    }
    else {
      if ((iVar9 != 0) && (4 < iVar8)) {
        iVar9 = iVar9 + 4;
        iVar8 = iVar8 + -4;
      }
      param_11[0x10] = iVar9;
      param_11[0x11] = iVar8;
    }
  }
  else {
    param_11[0x10] = 0;
    param_11[0x11] = 0;
  }
  return;
}



// ==== 802a9b94  zz_02a9b94_ ====

void zz_02a9b94_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 *param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  int iVar6;
  undefined4 *puVar7;
  uint *puVar8;
  int iVar9;
  undefined4 uVar10;
  int iVar11;
  undefined8 uVar12;
  int local_38;
  int local_34;
  uint local_30;
  void *local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  uint *local_1c;
  
  iVar6 = -0x7fd40000;
  puVar7 = param_10;
  iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar2 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122614__mwPlyGetCurFrm__handle_802b9218,puVar7,iVar6,param_12,param_13,param_14,
                param_15,param_16);
    *param_10 = 0;
  }
  else {
    iVar2 = zz_02af50c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        puVar7,iVar6,param_12,param_13,param_14,param_15,param_16);
    uVar12 = zz_02a107c_(iVar2,(int *)&local_1c);
    if (*(int *)(param_9 + 0x54) == 0) {
      iVar9 = *(int *)(param_9 + 0x1c);
      uVar5 = extraout_r4;
      for (iVar11 = 0; iVar11 < iVar9; iVar11 = iVar11 + 1) {
        iVar3 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
        if (iVar3 == 0) {
          uVar12 = zz_02aa530_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_E1122618__mwPlyIsNextFrmReady__h_802b9114,uVar5,iVar6,param_12,
                               param_13,param_14,param_15,param_16);
          iVar6 = 0;
        }
        else {
          iVar6 = zz_02af50c_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9
                              ,uVar5,iVar6,param_12,param_13,param_14,param_15,param_16);
          iVar6 = zz_02a0448_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6);
        }
        if (iVar6 != 1) break;
        zz_02a1008_(iVar2,local_1c);
        iVar6 = *(int *)(param_9 + 0x84);
        *(int *)(param_9 + 0x84) = iVar6 + 1;
        uVar12 = zz_02a107c_(iVar2,(int *)&local_1c);
        uVar5 = extraout_r4_00;
      }
    }
    if (local_1c == (uint *)0x0) {
      *param_10 = 0;
    }
    else {
      if (*(int *)(param_9 + 0xb4) != 1) {
        *(undefined4 *)(param_9 + 0xb8) = 0;
        *(undefined4 *)(param_9 + 0xb4) = 1;
        iVar2 = zz_02a3744_(*(int *)(param_9 + 0x40),&local_20,&local_24);
        if ((((iVar2 == 0) && (0x7ff < local_24)) && (local_20 != 0)) &&
           (piVar4 = zz_02a91d8_(local_20,local_24), piVar4 != (int *)0x0)) {
          iVar2 = zz_02a8f78_(piVar4,&local_38);
          if (((iVar2 != 0) && (local_38 != 0)) &&
             ((iVar2 = zz_02a8e88_(piVar4,-0x20,&local_34), iVar2 != 0 &&
              ((local_34 != 0 && (iVar2 = zz_02a768c_(piVar4,0xe0,&local_30), iVar2 != 0)))))) {
            if (local_30 == 3) {
              *(undefined4 *)(param_9 + 0xb8) = 1;
              zz_02ab0c8_(param_9,1);
            }
            else {
              zz_02ab0c8_(param_9,0);
            }
          }
          uVar12 = zz_02a91ac_(piVar4);
        }
      }
      *(int *)(param_9 + 0x7c) = *(int *)(param_9 + 0x7c) + 1;
      *(uint **)(param_9 + 0x78) = local_1c;
      *(uint *)(param_9 + 0x88) = local_1c[0xf];
      *(uint *)(param_9 + 0x8c) = local_1c[0x10];
      *(uint *)(param_9 + 0x90) = local_1c[0x11];
      *(uint *)(param_9 + 0x94) = local_1c[0x12];
      *(uint *)(param_9 + 0x98) = local_1c[0x13];
      *(uint *)(param_9 + 0x9c) = local_1c[0x14];
      *(uint *)(param_9 + 0xa0) = local_1c[0x15];
      *(undefined4 *)(param_9 + 0xa4) = 0;
      puVar7 = param_10;
      puVar8 = local_1c;
      uVar12 = zz_02a9960_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                           local_1c,param_10,local_1c,param_13,param_14,param_15,param_16);
      iVar6 = *(int *)local_1c[0xe];
      iVar9 = ((int *)local_1c[0xe])[1];
      uVar5 = extraout_r4_01;
      iVar2 = zz_02ade24_();
      if ((iVar2 == 1) && (*(int *)(param_9 + 0xd8) != 0)) {
        if ((iVar6 == 0) || (iVar9 < 5)) {
          local_2c = (void *)0x0;
          local_28 = 0;
        }
        else {
          puVar8 = &local_28;
          zz_027b098_((void *)(iVar6 + 4),iVar9 + -4,&local_2c,puVar8);
        }
        if ((local_2c == (void *)0x0) || ((int)local_28 < 1)) {
          *(undefined4 *)(param_9 + 0xe0) = 0;
          *(undefined4 *)(param_9 + 0xe4) = 0;
        }
        else {
          if ((int)*(size_t *)(param_9 + 0xdc) < (int)local_28) {
            local_28 = *(size_t *)(param_9 + 0xdc);
          }
          gnt4_memset(*(void **)(param_9 + 0xd8),0,*(size_t *)(param_9 + 0xdc));
          gnt4_memcpy(*(void **)(param_9 + 0xd8),local_2c,local_28);
          *(undefined4 *)(param_9 + 0xe0) = *(undefined4 *)(param_9 + 0xd8);
          *(uint *)(param_9 + 0xe4) = local_28;
        }
        puVar7 = *(undefined4 **)(param_9 + 0xe4);
        uVar12 = zz_02aac24_(param_9,*(undefined4 *)(param_9 + 0xe0),puVar7);
        uVar5 = extraout_r4_02;
      }
      if (*(int *)(param_9 + 0xfc) < (int)param_10[0xb]) {
        uVar12 = zz_02aadd4_(param_9);
        uVar5 = extraout_r4_03;
      }
      *(undefined4 *)(param_9 + 0xfc) = param_10[0xb];
      if ((int)(-*(uint *)(param_9 + 0xe0) | *(uint *)(param_9 + 0xe0)) < 0) {
        iVar2 = zz_02aac00_(param_9);
        if (iVar2 == 1) {
          uVar12 = zz_02ab0a4_(param_9,1);
          uVar5 = extraout_r4_04;
        }
        else {
          uVar12 = zz_02ab0a4_(param_9,0);
          uVar5 = extraout_r4_05;
        }
      }
      uVar10 = 0;
      uVar1 = local_1c[0xf];
      if (uVar1 == 3) {
        if (local_1c[0x11] == 0) {
          uVar10 = 2;
        }
      }
      else if ((((int)uVar1 < 3) && (uVar1 != 0)) && (-1 < (int)uVar1)) {
        uVar10 = 2;
      }
      else {
        zz_02aa530_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E301271__mwsffrm_DecideFrmType___802b919c,uVar5,puVar7,puVar8,param_13,
                    param_14,param_15,param_16);
      }
      iVar2 = zz_02ade24_();
      if ((iVar2 == 1) && (iVar2 = zz_02aabdc_(param_9), iVar2 == 1)) {
        uVar10 = 2;
      }
      param_10[0x12] = uVar10;
    }
  }
  return;
}



// ==== 802a9f94  zz_02a9f94_ ====

undefined4
zz_02a9f94_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2010801__mwPlyGetFrmSync__handl_802b9248,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_9 + 0x54);
  }
  return uVar2;
}



// ==== 802a9fe4  zz_02a9fe4_ ====

void zz_02a9fe4_(int param_1,undefined4 param_2)

{
  zz_02988d4_(*(int *)(param_1 + 0x40),param_2);
  return;
}



// ==== 802aa008  zz_02aa008_ ====

void zz_02aa008_(int param_1,undefined4 param_2,undefined4 param_3)

{
  zz_0298960_(*(int *)(param_1 + 0x40),param_2,param_3);
  return;
}



// ==== 802aa02c  zz_02aa02c_ ====

void zz_02aa02c_(int param_1)

{
  zz_02987d8_(*(int *)(param_1 + 0x40));
  return;
}



// ==== 802aa050  zz_02aa050_ ====

void zz_02aa050_(int param_1,undefined4 param_2)

{
  zz_0298854_(*(int *)(param_1 + 0x40),param_2);
  return;
}



// ==== 802aa074  zz_02aa074_ ====

void zz_02aa074_(void)

{
  return;
}



// ==== 802aa078  zz_02aa078_ ====

void zz_02aa078_(void)

{
  return;
}



// ==== 802aa07c  zz_02aa07c_ ====

void zz_02aa07c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_10;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122642__mwPlyLinkStm__handle_i_802b92a8,iVar2,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    if ((*(char *)(param_9 + 0x70) == '\x01') && (param_10 == 0)) {
      *(undefined1 *)(param_9 + 0x71) = 1;
    }
    if (((*(char *)(param_9 + 0x70) == '\0') && (param_10 == 1)) &&
       (iVar1 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar1 != 0)) {
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E99072101_mwPlyLinkStm__can_t_li_802b92d4,iVar2,param_11,param_12,param_13,
                  param_14,param_15,param_16);
    }
    *(char *)(param_9 + 0x70) = (char)param_10;
  }
  return;
}



// ==== 802aa124  cCharacter::UpdateBlinking(float) ====

void cCharacter__UpdateBlinking_float_
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
               undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (*(int *)(param_9 + 0x4c) != 0) {
    zz_0275c14_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x4c),param_10,param_11,param_12,param_13,param_14,param_15,
                param_16);
  }
  return;
}



// ==== 802aa150  zz_02aa150_ ====

uint zz_02aa150_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = zz_0275cb8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = countLeadingZeros(3 - iVar2);
  return uVar1 >> 5;
}



// ==== 802aa17c  zz_02aa17c_ ====

void zz_02aa17c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,uint param_11,undefined4 param_12,uint **param_13,
                undefined4 ***param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  undefined *extraout_r4_00;
  undefined *puVar4;
  undefined *extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  uint uVar5;
  uint *puVar6;
  undefined8 uVar7;
  uint local_28;
  uint *local_24;
  uint **local_20 [3];
  
  puVar6 = (uint *)0x802c0000;
  iVar2 = param_10;
  uVar5 = param_11;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122632__mwPlyStartAfsLp__handl_802b9358,iVar2,uVar5,puVar6,param_13,param_14,
                param_15,param_16);
  }
  else {
    uVar7 = zz_0275d68_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x4c),iVar2,uVar5,puVar6,param_13,param_14,param_15,
                        param_16);
    uVar3 = extraout_r4;
    iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar2 == 0) {
      uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122636__mwPlyEntryAfs__handle_i_802b9388,uVar3,uVar5,puVar6,param_13,
                          param_14,param_15,param_16);
      puVar4 = extraout_r4_00;
      param_11 = uVar5;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x4c);
      puVar6 = &local_28;
      param_13 = &local_24;
      param_14 = local_20;
      iVar2 = zz_0272048_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                          param_11,-0x7fbcf2b0,puVar6,(int *)param_13,(uint *)param_14,param_15,
                          param_16);
      if (iVar2 == 0) {
        puVar4 = &DAT_80430d50;
        zz_0275f34_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                    (int *)&DAT_80430d50,local_28,(uint)local_24,(uint)local_20[0],param_14,param_15
                    ,param_16);
        param_11 = local_28;
        puVar6 = local_24;
        param_13 = local_20[0];
      }
      else {
        uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E008311_mwPlyEntryAfs__can_t_ent_802b93b4,param_10,param_11,puVar6,
                            param_13,param_14,param_15,param_16);
        puVar4 = extraout_r4_01;
      }
    }
    iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar2 == 0) {
      uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122641__mwPlySetLpFlg__handle_i_802b93e8,puVar4,param_11,puVar6,
                          param_13,param_14,param_15,param_16);
      uVar3 = extraout_r4_02;
    }
    else {
      uVar7 = zz_0275b98_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x4c),1,param_11,puVar6,param_13,param_14,param_15,
                          param_16);
      uVar3 = extraout_r4_03;
    }
    iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar2 == 0) {
      zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E1122634__mwPlyStartSeamless__ha_802b9414,uVar3,param_11,puVar6,param_13,
                  param_14,param_15,param_16);
    }
    else {
      iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
      if (iVar2 == 0) {
        uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E1122642__mwPlyLinkStm__handle_i_802b92a8,uVar3,param_11,puVar6,
                            param_13,param_14,param_15,param_16);
      }
      else {
        if ((*(char *)(param_9 + 0x70) == '\0') &&
           (iVar2 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar2 != 0)) {
          uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E99072101_mwPlyLinkStm__can_t_li_802b92d4,uVar3,param_11,puVar6,
                              param_13,param_14,param_15,param_16);
        }
        *(undefined1 *)(param_9 + 0x70) = 1;
      }
      uVar7 = zz_02ae50c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *(int *)(param_9 + 300),param_11,puVar6,param_13,param_14,param_15,
                          param_16);
      uVar7 = zz_02ae184_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      uVar7 = zz_0275e24_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x4c),extraout_r4_04,param_11,puVar6,param_13,param_14,
                          param_15,param_16);
      if (*(int **)(param_9 + 0x128) != (int *)0x0) {
        uVar7 = (**(code **)(**(int **)(param_9 + 0x128) + 0x14))();
      }
      zz_02ad96c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  return;
}



// ==== 802aa338  zz_02aa338_ ====

void zz_02aa338_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 extraout_f1;
  longlong lVar6;
  
  uVar4 = 0x802c0000;
  piVar2 = param_10;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122630__mwPlyStartFnameLp__han_802b94ac,piVar2,uVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
  else if (param_10 == (int *)0x0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E10915A__mwPlyStartFnameLp__fnam_802b94dc,piVar2,uVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
  else {
    uVar5 = zz_0275d68_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x4c),piVar2,uVar4,param_12,param_13,param_14,param_15,
                        param_16);
    uVar3 = extraout_r4;
    iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar1 == 0) {
      uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122633__mwPlyEntryFname__handl_802b9508,uVar3,uVar4,param_12,param_13,
                          param_14,param_15,param_16);
      uVar3 = extraout_r4_00;
    }
    else if (param_10 == (int *)0x0) {
      uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E10915B__mwPlyEntryFname__fname_i_802b9538,uVar3,uVar4,param_12,param_13
                          ,param_14,param_15,param_16);
      uVar3 = extraout_r4_01;
    }
    else {
      lVar6 = zz_0276174_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x4c),param_10);
      uVar3 = (undefined4)lVar6;
      if (lVar6 < 0) {
        *(undefined4 *)(param_9 + 8) = 4;
        uVar5 = zz_02aa530_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E204021__mwPlyEntryFname__Can_t_e_802b9564,param_10,uVar4,param_12,
                            param_13,param_14,param_15,param_16);
        uVar3 = extraout_r4_02;
      }
      else {
        *(int *)(param_9 + 0x74) = *(int *)(param_9 + 0x74) + 1;
        uVar5 = extraout_f1;
      }
    }
    iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar1 == 0) {
      uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122641__mwPlySetLpFlg__handle_i_802b93e8,uVar3,uVar4,param_12,param_13
                          ,param_14,param_15,param_16);
      uVar3 = extraout_r4_03;
    }
    else {
      uVar5 = zz_0275b98_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x4c),1,uVar4,param_12,param_13,param_14,param_15,
                          param_16);
      uVar3 = extraout_r4_04;
    }
    iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
    if (iVar1 == 0) {
      zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E1122634__mwPlyStartSeamless__ha_802b9414,uVar3,uVar4,param_12,param_13,param_14
                  ,param_15,param_16);
    }
    else {
      iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
      if (iVar1 == 0) {
        uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E1122642__mwPlyLinkStm__handle_i_802b92a8,uVar3,uVar4,param_12,
                            param_13,param_14,param_15,param_16);
      }
      else {
        if ((*(char *)(param_9 + 0x70) == '\0') &&
           (iVar1 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar1 != 0)) {
          uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E99072101_mwPlyLinkStm__can_t_li_802b92d4,uVar3,uVar4,param_12,
                              param_13,param_14,param_15,param_16);
        }
        *(undefined1 *)(param_9 + 0x70) = 1;
      }
      uVar5 = zz_02ae50c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *(int *)(param_9 + 300),uVar4,param_12,param_13,param_14,param_15,param_16
                         );
      uVar5 = zz_02ae184_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      uVar5 = zz_0275e24_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(param_9 + 0x4c),extraout_r4_05,uVar4,param_12,param_13,param_14,
                          param_15,param_16);
      if (*(int **)(param_9 + 0x128) != (int *)0x0) {
        uVar5 = (**(code **)(**(int **)(param_9 + 0x128) + 0x14))();
      }
      zz_02ad96c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  return;
}



// ==== 802aa50c  zz_02aa50c_ ====

void zz_02aa50c_(void)

{
  zz_0277fd4_(6);
  return;
}



// ==== 802aa530  zz_02aa530_ ====

void zz_02aa530_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
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
  gnt4_memset(&DAT_80430e70,0,0x100);
  local_14 = &stack0x00000008;
  local_10 = &local_78;
  local_18[0] = '\x01';
  local_18[1] = '\0';
  local_18[2] = '\0';
  local_18[3] = '\0';
  zz_0236910_(-0x7fbcf190,param_9,local_18);
  zz_0278594_(-0x7fbcf190);
  return;
}



// ==== 802aa5ec  zz_02aa5ec_ ====

void zz_02aa5ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_0277a30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802aa60c  zz_02aa60c_ ====

void zz_02aa60c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  zz_02786c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 802aa62c  zz_02aa62c_ ====

undefined4 zz_02aa62c_(void)

{
  zz_02787e4_();
  return 1;
}



// ==== 802aa650  zz_02aa650_ ====

void zz_02aa650_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  zz_0278754_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 802aa670  zz_02aa670_ ====

undefined4 zz_02aa670_(void)

{
  zz_027884c_();
  return 1;
}



// ==== 802aa694  zz_02aa694_ ====

void zz_02aa694_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_80430f70 = zz_0278418_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5,
                             param_9,param_10,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802aa6c8  zz_02aa6c8_ ====

void zz_02aa6c8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  DAT_80430f74 = zz_0278418_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,
                             param_9,param_10,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802aa6fc  zz_02aa6fc_ ====

void zz_02aa6fc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_027811c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,param_9,param_10,
              param_11,param_13,param_14,param_15,param_16);
  DAT_80430f78 = param_9;
  return;
}



// ==== 802aa744  zz_02aa744_ ====

void zz_02aa744_(void)

{
  zz_0277bec_();
  DAT_80430f7c = 0;
  DAT_80430f78 = 0;
  DAT_80430f74 = 0;
  DAT_80430f70 = 0;
  return;
}



// ==== 802aa788  zz_02aa788_ ====

void zz_02aa788_(int param_1)

{
  zz_026d7dc_(param_1);
  return;
}



// ==== 802aa7a8  zz_02aa7a8_ ====

void zz_02aa7a8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined8 uVar1;
  
  uVar1 = zz_026d658_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  zz_026d9ac_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 802aa7dc  zz_02aa7dc_ ====

void zz_02aa7dc_(int param_1)

{
  zz_026d718_(param_1);
  return;
}



// ==== 802aa7fc  zz_02aa7fc_ ====

void zz_02aa7fc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                )

{
  undefined8 uVar1;
  
  uVar1 = zz_026d9ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  zz_026dafc_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13);
  zz_026d510_(param_9,param_13);
  return;
}



// ==== 802aa85c  zz_02aa85c_ ====

void zz_02aa85c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined1 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026db58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802aa87c  zz_02aa87c_ ====

void zz_02aa87c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9)

{
  zz_026ddec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0);
  return;
}



// ==== 802aa8a0  MWEnterCriticalSection ====

void MWEnterCriticalSection(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = zz_026ceb8_(param_1);
  *param_2 = uVar1;
  return;
}



// ==== 802aa8d0  zz_02aa8d0_ ====

void zz_02aa8d0_(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (param_1 != 0) {
    zz_026cecc_(param_1,param_2,param_3);
  }
  return;
}



// ==== 802aa8f8  zz_02aa8f8_ ====

uint zz_02aa8f8_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = zz_026d7dc_(param_1);
  uVar1 = countLeadingZeros(4 - iVar2);
  return uVar1 >> 5;
}



// ==== 802aa924  zz_02aa924_ ====

undefined4 zz_02aa924_(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  if (param_3 == 0) {
    zz_026d78c_(param_1,param_2);
  }
  else if (param_3 == 1) {
    iVar2 = zz_026d770_(param_1);
    zz_026d78c_(param_1,param_2 + iVar2);
  }
  else if (param_3 == 2) {
    iVar2 = zz_026ceb8_(param_1);
    uVar1 = iVar2 + 0x7ff;
    zz_026d78c_(param_1,((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0) +
                        param_2);
  }
  return 0;
}



// ==== 802aa9b4  zz_02aa9b4_ ====

undefined4 zz_02aa9b4_(void)

{
  return 0;
}



// ==== 802aa9bc  zz_02aa9bc_ ====

void zz_02aa9bc_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_02adc9c_();
  if (iVar1 == 1) {
    zz_02ae10c_(param_1);
  }
  return;
}



// ==== 802aa9f8  zz_02aa9f8_ ====

void zz_02aa9f8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,int param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = zz_02adc9c_();
  if ((iVar1 == 1) && (iVar1 = *(int *)(param_9 + 0x40), param_11 != -1)) {
    uVar5 = 1;
    zz_02a3a84_(iVar1,0x30,1);
    iVar3 = DAT_80430f80 + param_11 * 0xdc4;
    iVar2 = zz_02a36c8_(iVar1,iVar3);
    if (iVar2 != 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_W2002_mwPlyStartFnameSeek__SFD_E_802b9598,iVar3,uVar5,param_12,
                            param_13,param_14,param_15,param_16);
    }
    uVar5 = 0xfffffff8;
    local_24 = 0;
    puVar4 = &local_24;
    local_20 = 0xfffffff8;
    local_1c = 1;
    iVar2 = zz_02a3190_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,puVar4
                       );
    if (iVar2 != 0) {
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_W2002_mwPlyStartFnameSeek__SFD_S_802b95c4,puVar4,uVar5,param_12,param_13,
                  param_14,param_15,param_16);
    }
    zz_02a3a84_(iVar1,0x38,1);
    zz_02a3a84_(iVar1,0x39,1);
    MWEnterCriticalSection(*(int *)(param_9 + 0x44),&local_28);
    zz_02a308c_(iVar1,local_28);
  }
  return;
}



// ==== 802aab04  zz_02aab04_ ====

void zz_02aab04_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  int local_18 [3];
  
  iVar2 = zz_02adc9c_();
  if (iVar2 == 1) {
    if ((param_11 != -1) && (*(int *)(DAT_80430f80 + param_11 * 0xdc4) == 0)) {
      param_10 = 0;
    }
    uVar4 = MWEnterCriticalSection(*(int *)(param_9 + 0x44),local_18);
    uVar1 = local_18[0] + 0x7ff;
    iVar2 = ((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0) + -1;
    if (iVar2 < param_10) {
      param_10 = iVar2;
    }
    if (0 < param_10) {
      uVar3 = 0;
      iVar2 = zz_02aa924_(*(int *)(param_9 + 0x44),param_10,0);
      if (iVar2 != 0) {
        zz_02addf4_(0xfffffffc);
        zz_02aa530_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E2080605_MWSTM_SeekSct__error_802b95e8,param_10,uVar3,param_12,param_13,
                    param_14,param_15,param_16);
      }
    }
  }
  return;
}



// ==== 802aabdc  zz_02aabdc_ ====

void zz_02aabdc_(int param_1)

{
  zz_027bb80_(*(int *)(param_1 + 0xa8));
  return;
}



// ==== 802aac00  zz_02aac00_ ====

void zz_02aac00_(int param_1)

{
  zz_027bb54_(*(int *)(param_1 + 0xa8));
  return;
}



// ==== 802aac24  zz_02aac24_ ====

void zz_02aac24_(int param_1,undefined4 param_2,undefined4 param_3)

{
  zz_027bbac_(*(int *)(param_1 + 0xa8),param_2,param_3);
  return;
}



// ==== 802aac48  zz_02aac48_ ====

void zz_02aac48_(int param_1)

{
  uint uVar1;
  char *pcVar2;
  int *piVar3;
  undefined1 auStack_28 [8];
  void *local_20;
  size_t local_1c;
  int local_18;
  int local_14;
  
  piVar3 = *(int **)(param_1 + 0xe8);
  local_14 = (**(code **)(*piVar3 + 0x24))(piVar3,1);
  if (local_14 == 0) {
    *(undefined4 *)(param_1 + 0x104) = 0;
    *(undefined4 *)(param_1 + 0x108) = 0;
    *(undefined4 *)(param_1 + 0x100) = 1;
  }
  else {
    local_18 = *(int *)(param_1 + 0xec);
    pcVar2 = zz_02777b8_(&local_18,s_CRITAGS_802b97f8,s_CRITAGE_802b9800,(int *)&local_20);
    if (pcVar2 == (char *)0x0) {
      *(undefined4 *)(param_1 + 0x104) = 0;
      *(undefined4 *)(param_1 + 0x108) = 0;
      *(undefined4 *)(param_1 + 0x100) = 1;
    }
    else if (*(void **)(param_1 + 0xf4) == (void *)0x0) {
      *(void **)(param_1 + 0x104) = local_20;
      *(size_t *)(param_1 + 0x108) = local_1c;
      *(undefined4 *)(param_1 + 0x100) = 1;
      uVar1 = countLeadingZeros(2 - *(int *)(param_1 + 0xc));
      if ((uVar1 >> 5 != 1) && (*(int *)(param_1 + 0xe8) != 0)) {
        zz_02a5c0c_(*(int *)(param_1 + 0x40),2,0,0);
      }
    }
    else {
      gnt4_memcpy(*(void **)(param_1 + 0xf4),local_20,local_1c);
      *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xf4);
      *(size_t *)(param_1 + 0x108) = local_1c;
      *(undefined4 *)(param_1 + 0x100) = 1;
      (**(code **)(*piVar3 + 0x18))(piVar3,1,0x7fffffff,auStack_28);
      (**(code **)(*piVar3 + 0x20))(piVar3,0,auStack_28);
      (**(code **)(*piVar3 + 0x14))(piVar3);
    }
  }
  return;
}



// ==== 802aadd4  zz_02aadd4_ ====

void zz_02aadd4_(int param_1)

{
  char *pcVar1;
  int iVar2;
  int local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0xe8) != 0) {
    zz_02aac48_(param_1);
    local_18 = *(int *)(param_1 + 0x104);
    iVar2 = *(int *)(param_1 + 0xa8);
    if (local_18 == 0) {
      zz_027b268_(iVar2,0,0);
    }
    else {
      local_14 = *(undefined4 *)(param_1 + 0x108);
      pcVar1 = zz_02777b8_(&local_18,s_SFXINFS_802b97b0,s_SFXINFE_802b97b8,&local_10);
      if (pcVar1 == (char *)0x0) {
        zz_027b268_(iVar2,0,0);
      }
      else {
        zz_027b268_(iVar2,local_10,local_c);
      }
    }
  }
  return;
}



// ==== 802aae8c  zz_02aae8c_ ====

void zz_02aae8c_(int param_1)

{
  if (*(int **)(param_1 + 0xe8) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0xe8) + 0x14))();
  }
  return;
}



// ==== 802aaec4  zz_02aaec4_ ====

void zz_02aaec4_(int param_1)

{
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined4 *)(param_1 + 0x104) = 0;
  *(undefined4 *)(param_1 + 0x108) = 0;
  *(undefined4 *)(param_1 + 0xfc) = 0xffffffff;
  return;
}



// ==== 802aaee0  zz_02aaee0_ ====

int zz_02aaee0_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = countLeadingZeros(2 - *(int *)(param_1 + 0xc));
  if (uVar1 >> 5 == 1) {
    iVar2 = 0;
  }
  else if (*(int *)(param_1 + 0xe8) == 0) {
    iVar2 = 0;
  }
  else {
    uVar1 = zz_02a5c0c_(*(int *)(param_1 + 0x40),2,*(int *)(param_1 + 0xe8),0);
    iVar2 = (int)(-uVar1 | uVar1) >> 0x1f;
  }
  return iVar2;
}



// ==== 802aaf4c  zz_02aaf4c_ ====

void zz_02aaf4c_(int param_1)

{
  if (*(int **)(param_1 + 0xe8) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0xe8) + 0xc))();
  }
  return;
}



// ==== 802aaf84  zz_02aaf84_ ====

undefined4 *
zz_02aaf84_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
           undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined8 uVar5;
  
  if ((param_9[0xb] == 0) || (param_9[0xb] == 0x101)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    uVar4 = 0;
    uVar3 = param_9[0x3c];
    puVar2 = zz_02774e0_(param_9[0x3b],uVar3,0);
    if (puVar2 == (undefined4 *)0x0) {
      uVar5 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E201211_mwPlyCreate__can_t_creat_802b9808,uVar3,uVar4,param_12,param_13,
                          param_14,param_15,param_16);
      zz_02ab4b8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                  uVar4,param_12,param_13,param_14,param_15,param_16);
      puVar2 = (undefined4 *)0x0;
    }
  }
  else {
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}



// ==== 802ab010  zz_02ab010_ ====

undefined4 zz_02ab010_(int param_1)

{
  if ((*(int *)(param_1 + 0x20) != 0) && (*(int *)(param_1 + 0x20) != 0x101)) {
    return 0;
  }
  return 1;
}



// ==== 802ab034  zz_02ab034_ ====

void zz_02ab034_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = param_10;
  uVar3 = param_11;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2011916__mwPlyFxSetOutBufSize__h_802b9938,uVar2,uVar3,param_12,param_13,param_14,
                param_15,param_16);
  }
  else {
    zz_027b304_(*(int *)(param_9 + 0xa8),param_10,param_11);
  }
  return;
}



// ==== 802ab0a4  zz_02ab0a4_ ====

void zz_02ab0a4_(int param_1,undefined4 param_2)

{
  zz_027b230_(*(int *)(param_1 + 0xa8),param_2);
  return;
}



// ==== 802ab0c8  zz_02ab0c8_ ====

void zz_02ab0c8_(int param_1,undefined4 param_2)

{
  zz_027b230_(*(int *)(param_1 + 0xa8),param_2);
  return;
}



// ==== 802ab0ec  zz_02ab0ec_ ====

void zz_02ab0ec_(int param_1,undefined4 param_2)

{
  zz_027b310_(*(int *)(param_1 + 0xa8),param_2);
  return;
}



// ==== 802ab110  zz_02ab110_ ====

void zz_02ab110_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10,int param_11,undefined4 *param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int aiStack_a8 [37];
  
  piVar2 = param_10;
  iVar4 = param_11;
  puVar3 = param_12;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E201199__mwPlyFxCnvFrmYUV422__ha_802b9bf8,piVar2,iVar4,puVar3,param_13,param_14,
                param_15,param_16);
  }
  else if (*param_10 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2011910__mwPlyFxCnvFrmYUV422__g_802b9c2c,piVar2,iVar4,puVar3,param_13,param_14,
                param_15,param_16);
  }
  else {
    iVar4 = *(int *)(param_9 + 0xa8);
    zz_02ab1ac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                aiStack_a8,puVar3,param_13,param_14,param_15,param_16);
    zz_027b318_(iVar4,aiStack_a8,param_11,(int)param_12);
  }
  return;
}



// ==== 802ab1ac  zz_02ab1ac_ ====

void zz_02ab1ac_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10,undefined4 *param_11,undefined4 *param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = param_10[1];
  if (iVar1 == 2) {
    uVar2 = 2;
  }
  else if (iVar1 < 2) {
    if (iVar1 < 1) {
LAB_802ab210:
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E201184___MwsfdBufFmt_value_is_i_802b9d98,0x802c0000,param_11,param_12,param_13,
                  param_14,param_15,param_16);
      uVar2 = 3;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    if (3 < iVar1) goto LAB_802ab210;
    uVar2 = 3;
  }
  *param_11 = uVar2;
  iVar1 = param_10[2];
  iVar4 = param_10[3];
  param_11[0x11] = iVar1;
  param_11[0x12] = iVar4;
  if (param_10[1] == 3) {
    param_12 = &local_30;
    zz_02a98d0_(*param_10,iVar1,iVar4,param_12);
    param_11[1] = local_30;
    param_11[2] = local_24;
    param_11[3] = iVar4;
    param_11[5] = local_2c;
    param_11[6] = local_20;
    param_11[7] = iVar4;
    param_11[9] = local_28;
    param_11[10] = local_1c;
    param_11[0xb] = iVar4;
  }
  else {
    param_11[1] = *param_10;
    param_11[2] = iVar1;
    param_11[3] = iVar4;
  }
  puVar3 = &local_34;
  param_11[0x13] = param_10[0xc];
  uVar6 = zz_027b238_(*(int *)(param_9 + 0xa8),&local_38,puVar3);
  uVar5 = 3;
  param_11[0x14] = local_38;
  param_11[0x15] = local_34;
  param_11[0x16] = 0;
  param_11[0x17] = 0;
  iVar1 = *(int *)(param_9 + 0x88);
  uVar2 = extraout_r4;
  if (iVar1 == 2) {
    uVar5 = 2;
  }
  else if (iVar1 < 2) {
    if (iVar1 < 1) {
LAB_802ab314:
      uVar6 = zz_02aa530_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E301272___picture_structure_is_i_802b9d70,extraout_r4,puVar3,param_12,
                          param_13,param_14,param_15,param_16);
      uVar2 = extraout_r4_00;
    }
    else {
      uVar5 = 1;
    }
  }
  else if (3 < iVar1) goto LAB_802ab314;
  param_11[0x18] = uVar5;
  uVar5 = 1;
  iVar1 = *(int *)(param_9 + 0x8c);
  if (iVar1 == 2) {
    uVar5 = 2;
  }
  else {
    if (iVar1 < 2) {
      if (0 < iVar1) goto LAB_802ab370;
    }
    else if (iVar1 < 4) {
      uVar5 = 3;
      goto LAB_802ab370;
    }
    uVar6 = zz_02aa530_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        s_E301273___chroma_format_is_inval_802b9d4c,uVar2,puVar3,param_12,param_13,
                        param_14,param_15,param_16);
    uVar2 = extraout_r4_01;
  }
LAB_802ab370:
  param_11[0x19] = uVar5;
  uVar5 = 1;
  param_11[0x1a] = *(undefined4 *)(param_9 + 0x90);
  param_11[0x1b] = *(undefined4 *)(param_9 + 0x94);
  param_11[0x1c] = *(undefined4 *)(param_9 + 0x98);
  iVar1 = *(int *)(param_9 + 0x9c);
  if (iVar1 != 1) {
    if ((iVar1 < 1) && (-1 < iVar1)) {
      uVar5 = 0;
    }
    else {
      uVar6 = zz_02aa530_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E301274___chromapos_is_invalid__802b9d2c,uVar2,puVar3,param_12,param_13,
                          param_14,param_15,param_16);
      uVar2 = extraout_r4_02;
    }
  }
  param_11[0x1d] = uVar5;
  uVar5 = 1;
  iVar1 = *(int *)(param_9 + 0xa0);
  if (iVar1 != 1) {
    if ((iVar1 < 1) && (-1 < iVar1)) {
      uVar5 = 0;
    }
    else {
      zz_02aa530_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E301274___chromapos_is_invalid__802b9d2c,uVar2,puVar3,param_12,param_13,param_14
                  ,param_15,param_16);
    }
  }
  param_11[0x1e] = uVar5;
  return;
}



// ==== 802ab418  zz_02ab418_ ====

void zz_02ab418_(undefined4 *param_1)

{
  zz_027b554_(param_1);
  return;
}



// ==== 802ab438  zz_02ab438_ ====

void zz_02ab438_(int param_1,uint param_2)

{
  zz_027b5b4_(param_1,param_2);
  return;
}



// ==== 802ab458  zz_02ab458_ ====

undefined4 zz_02ab458_(void)

{
  return 0x301f;
}



// ==== 802ab460  FUN_802ab460 ====

void FUN_802ab460(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,char *param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802ab488  zz_02ab488_ ====

void zz_02ab488_(void)

{
  zz_027b83c_();
  zz_027b828_(FUN_802ab460,0);
  return;
}



// ==== 802ab4b8  zz_02ab4b8_ ====

void zz_02ab4b8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 uVar2;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 extraout_f1;
  undefined8 uVar6;
  
  if (param_9 != (undefined4 *)0x0) {
    zz_02ae48c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    param_9[1] = 0;
    uVar5 = zz_02aaf4c_((int)param_9);
    uVar2 = extraout_r4;
    if ((undefined4 *)param_9[0x2a] != (undefined4 *)0x0) {
      uVar5 = zz_02ab418_((undefined4 *)param_9[0x2a]);
      uVar2 = extraout_r4_00;
    }
    if ((undefined1 *)param_9[0x13] != (undefined1 *)0x0) {
      uVar5 = zz_02761ac_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (undefined1 *)param_9[0x13],uVar2,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      uVar2 = extraout_r4_01;
    }
    if ((undefined1 *)param_9[0x11] != (undefined1 *)0x0) {
      uVar5 = zz_02aa85c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (undefined1 *)param_9[0x11],uVar2,param_11,param_12,param_13,param_14,
                          param_15,param_16);
      uVar2 = extraout_r4_02;
    }
    if ((int *)param_9[0x4b] != (int *)0x0) {
      uVar5 = (**(code **)(*(int *)param_9[0x4b] + 0xc))();
      uVar2 = extraout_r4_03;
    }
    if ((int *)param_9[0x53] != (int *)0x0) {
      uVar5 = (**(code **)(*(int *)param_9[0x53] + 0xc))();
      uVar2 = extraout_r4_04;
    }
    if ((param_9[0x10] != 0) &&
       (uVar6 = zz_02a1794_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            param_9[0x10]), uVar2 = (undefined4)uVar6, uVar5 = extraout_f1,
       (int)((ulonglong)uVar6 >> 0x20) != 0)) {
      zz_02addf4_(0xfffffece);
      uVar5 = zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar2,param_11,param_12,param_13
                          ,param_14,param_15,param_16);
      uVar2 = extraout_r4_05;
    }
    iVar3 = 0;
    do {
      iVar4 = param_9[-iVar3 + 0x7a];
      if (iVar4 != 0) {
        if (param_9[0x56] == 0) {
          puVar1 = GetOneTimerLeadGroundContactAnims_void_();
          uVar5 = (**(code **)(puVar1 + 0x2c))(*(undefined4 *)(puVar1 + 0x30),iVar4);
          uVar2 = extraout_r4_06;
        }
        param_9[0x5a] = param_9[0x5a] + -1;
        param_9[-iVar3 + 0x7a] = 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x20);
    if (param_9[0x5a] != 0) {
      zz_02aa530_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E2053005__forgot_free__802b9ec4,uVar2,param_11,param_12,param_13,param_14,
                  param_15,param_16);
    }
    gnt4_memset(param_9,0,0x210);
    param_9[1] = 0;
    *param_9 = &DAT_803aefa8;
  }
  return;
}



// ==== 802ab630  zz_02ab630_ ====

undefined4
zz_02ab630_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           uint param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  uint extraout_r4;
  uint uVar4;
  uint extraout_r4_00;
  int iVar5;
  int iVar6;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  ulonglong uVar7;
  
  iVar1 = zz_02ab458_();
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (iVar1 < 0) {
      uVar7 = (ulonglong)param_10;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar2 = GetOneTimerLeadGroundContactAnims_void_();
        uVar7 = (**(code **)(puVar2 + 0x28))(*(undefined4 *)(puVar2 + 0x30),iVar1);
        param_1 = extraout_f1;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar1)) {
        uVar7 = (ulonglong)param_10;
      }
      else {
        uVar7 = CONCAT44(*(int *)(param_9 + 0x160),param_10);
        *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + iVar1;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar1;
      }
      iVar5 = (int)(uVar7 >> 0x20);
      if (iVar5 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar5;
        uVar7 = CONCAT44(iVar5,*(int *)(param_9 + 0x168));
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,param_10,param_11,param_12
                          ,param_13,param_14,param_15,param_16);
    uVar7 = (ulonglong)extraout_r4;
  }
  iVar5 = (int)(uVar7 >> 0x20);
  uVar4 = (uint)uVar7;
  if (iVar5 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2053003__not_enough_work__sfx_w_802b9edc,uVar4,param_11,param_12,param_13,
                param_14,param_15,param_16);
    iVar1 = 0;
    do {
      iVar5 = (0x1f - iVar1) * 4 + 0x16c;
      iVar6 = *(int *)(param_9 + iVar5);
      if (iVar6 != 0) {
        if (*(int *)(param_9 + 0x158) == 0) {
          puVar2 = GetOneTimerLeadGroundContactAnims_void_();
          (**(code **)(puVar2 + 0x2c))(*(undefined4 *)(puVar2 + 0x30),iVar6);
        }
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + -1;
        *(undefined4 *)(param_9 + iVar5) = 0;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x20);
    uVar3 = 0xffffffff;
  }
  else {
    *(int *)(param_9 + 0xac) = iVar5;
    *(int *)(param_9 + 0xb0) = iVar1;
    iVar1 = zz_02ab010_(param_9 + 0xc);
    if (iVar1 == 1) {
      if (*(int *)(param_9 + 0x168) < 0x20) {
        if (*(int *)(param_9 + 0x158) == 0) {
          puVar2 = GetOneTimerLeadGroundContactAnims_void_();
          uVar7 = (**(code **)(puVar2 + 0x28))(*(undefined4 *)(puVar2 + 0x30),0x20000);
          param_1 = extraout_f1_00;
        }
        else if (*(uint *)(param_9 + 0x15c) < *(int *)(param_9 + 0x164) + 0x20000U) {
          uVar7 = (ulonglong)uVar4;
        }
        else {
          iVar1 = *(int *)(param_9 + 0x160);
          *(int *)(param_9 + 0x160) = iVar1 + 0x20000;
          uVar7 = CONCAT44(iVar1,*(int *)(param_9 + 0x164));
          *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + 0x20000;
        }
        iVar1 = (int)(uVar7 >> 0x20);
        if (iVar1 != 0) {
          *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar1;
          uVar7 = CONCAT44(iVar1,*(int *)(param_9 + 0x168));
          *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
        }
      }
      else {
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,uVar4,param_11,
                              param_12,param_13,param_14,param_15,param_16);
        uVar7 = (ulonglong)extraout_r4_00;
      }
      iVar1 = (int)(uVar7 >> 0x20);
      if (iVar1 == 0) {
        zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E2053004__not_enough_work__ainfs_802b9f00,(int)uVar7,param_11,param_12,
                    param_13,param_14,param_15,param_16);
        iVar1 = 0;
        do {
          iVar5 = (0x1f - iVar1) * 4 + 0x16c;
          iVar6 = *(int *)(param_9 + iVar5);
          if (iVar6 != 0) {
            if (*(int *)(param_9 + 0x158) == 0) {
              puVar2 = GetOneTimerLeadGroundContactAnims_void_();
              (**(code **)(puVar2 + 0x2c))(*(undefined4 *)(puVar2 + 0x30),iVar6);
            }
            *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + -1;
            *(undefined4 *)(param_9 + iVar5) = 0;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < 0x20);
        return 0xffffffff;
      }
      *(int *)(param_9 + 0xec) = iVar1;
      *(undefined4 *)(param_9 + 0xf0) = 0x20000;
    }
    else {
      *(undefined4 *)(param_9 + 0xec) = 0;
      *(undefined4 *)(param_9 + 0xf0) = 0;
    }
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 802ab8ec  zz_02ab8ec_ ====

undefined4 *
zz_02ab8ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int *param_9,
           undefined4 param_10,undefined4 param_11,int param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  undefined4 *__s;
  undefined *puVar3;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  char *pcVar8;
  undefined4 *puVar9;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  int *piVar10;
  undefined4 uVar11;
  undefined4 extraout_r4_09;
  undefined4 extraout_r4_10;
  undefined4 extraout_r4_11;
  undefined4 extraout_r4_12;
  undefined4 extraout_r4_13;
  undefined4 extraout_r4_14;
  undefined4 extraout_r4_15;
  undefined4 extraout_r4_16;
  undefined4 extraout_r4_17;
  undefined4 extraout_r4_18;
  undefined4 extraout_r4_19;
  undefined4 extraout_r4_20;
  undefined4 extraout_r4_21;
  undefined4 extraout_r4_22;
  undefined4 extraout_r4_23;
  undefined4 extraout_r4_24;
  undefined4 extraout_r4_25;
  undefined4 extraout_r4_26;
  undefined4 extraout_r4_27;
  undefined4 extraout_r4_28;
  undefined4 extraout_r4_29;
  undefined4 extraout_r4_30;
  undefined4 extraout_r4_31;
  undefined4 extraout_r4_32;
  undefined4 extraout_r4_33;
  undefined4 extraout_r4_34;
  undefined4 extraout_r4_35;
  uint extraout_r4_36;
  undefined4 extraout_r4_37;
  undefined4 extraout_r4_38;
  undefined4 extraout_r4_39;
  undefined4 extraout_r4_40;
  undefined4 extraout_r4_41;
  undefined4 extraout_r4_42;
  undefined4 extraout_r4_43;
  undefined4 extraout_r4_44;
  undefined4 extraout_r4_45;
  undefined4 extraout_r4_46;
  undefined4 extraout_r4_47;
  undefined4 extraout_r4_48;
  undefined4 extraout_r4_49;
  undefined4 extraout_r4_50;
  undefined4 extraout_r4_51;
  undefined4 extraout_r4_52;
  undefined4 extraout_r4_53;
  undefined4 extraout_r4_54;
  undefined4 extraout_r4_55;
  undefined4 extraout_r4_56;
  undefined4 extraout_r4_57;
  undefined4 extraout_r4_58;
  undefined4 extraout_r4_59;
  undefined4 extraout_r4_60;
  undefined4 extraout_r4_61;
  undefined4 extraout_r4_62;
  undefined4 extraout_r4_63;
  undefined4 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined8 uVar16;
  undefined8 extraout_f1;
  longlong lVar17;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 extraout_f1_04;
  undefined8 extraout_f1_05;
  undefined8 extraout_f1_06;
  undefined8 extraout_f1_07;
  double dVar18;
  double dVar19;
  undefined8 uVar20;
  
  if (param_9 == (int *)0x0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122612_mwPlyCreateSofdec___cpr_802b9f4c,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    __s = (undefined4 *)0x0;
  }
  else {
    bVar1 = true;
    if ((param_9[9] != 0) && (param_9[9] != 3)) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E3012102__Buffer_format_is_inval_802b9f28,param_10,param_11,param_12,
                            param_13,param_14,param_15,param_16);
      bVar1 = false;
      param_10 = extraout_r4;
    }
    if (bVar1) {
      puVar3 = GetOneTimerLeadGroundContactAnims_void_();
      iVar4 = 0;
      __s = (undefined4 *)(puVar3 + 0x68);
      if (*(int *)(puVar3 + 0x6c) != 0) {
        __s = (undefined4 *)(puVar3 + 0x278);
        iVar4 = 1;
        if (*(int *)(puVar3 + 0x27c) != 0) {
          __s = (undefined4 *)(puVar3 + 0x488);
          iVar4 = 2;
          if (*(int *)(puVar3 + 0x48c) != 0) {
            __s = (undefined4 *)(puVar3 + 0x698);
            iVar4 = 3;
            if (*(int *)(puVar3 + 0x69c) != 0) {
              __s = (undefined4 *)(puVar3 + 0x8a8);
              iVar4 = 4;
              if (*(int *)(puVar3 + 0x8ac) != 0) {
                __s = (undefined4 *)(puVar3 + 0xab8);
                iVar4 = 5;
                if (*(int *)(puVar3 + 0xabc) != 0) {
                  __s = (undefined4 *)(puVar3 + 0xcc8);
                  iVar4 = 6;
                  if (*(int *)(puVar3 + 0xccc) != 0) {
                    __s = (undefined4 *)(puVar3 + 0xed8);
                    iVar4 = 7;
                    if (*(int *)(puVar3 + 0xedc) != 0) {
                      iVar4 = 8;
                    }
                  }
                }
              }
            }
          }
        }
      }
      if (iVar4 == 8) {
        zz_02addf4_(0xfffffff5);
        zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_W2000_mwPlyCreateSofdec_can_t_cr_802b9f78,param_10,param_11,param_12,param_13,
                    param_14,param_15,param_16);
        __s = (undefined4 *)0x0;
      }
      else {
        puVar5 = GetOneTimerLeadGroundContactAnims_void_();
        iVar4 = 0;
        if (param_9[6] == 0) {
          if (*(int *)(puVar5 + 0x28) == 0) {
            iVar4 = -1;
          }
          if (*(int *)(puVar5 + 0x2c) == 0) {
            iVar4 = -1;
          }
        }
        if (iVar4 == -1) {
          zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_E2053006_mwPlyCreateSofdec__Didn_802b9fa4,0xffffffff,param_11,param_12,
                      param_13,param_14,param_15,param_16);
          __s = (undefined4 *)0x0;
        }
        else {
          if (__s != (undefined4 *)0x0) {
            param_11 = 0x210;
            gnt4_memset(__s,0,0x210);
          }
          __s[0x56] = param_9[6];
          __s[0x57] = param_9[7];
          __s[0x58] = param_9[6];
          __s[0x59] = 0;
          __s[0x5a] = 0;
          __s[0x5b] = 0;
          __s[0x5c] = 0;
          __s[0x5d] = 0;
          __s[0x5e] = 0;
          __s[0x5f] = 0;
          __s[0x60] = 0;
          __s[0x61] = 0;
          __s[0x62] = 0;
          __s[99] = 0;
          __s[100] = 0;
          __s[0x65] = 0;
          __s[0x66] = 0;
          __s[0x67] = 0;
          __s[0x68] = 0;
          __s[0x69] = 0;
          __s[0x6a] = 0;
          __s[0x6b] = 0;
          __s[0x6c] = 0;
          __s[0x6d] = 0;
          __s[0x6e] = 0;
          __s[0x6f] = 0;
          __s[0x70] = 0;
          __s[0x71] = 0;
          __s[0x72] = 0;
          __s[0x73] = 0;
          __s[0x74] = 0;
          __s[0x75] = 0;
          __s[0x76] = 0;
          __s[0x77] = 0;
          __s[0x78] = 0;
          __s[0x79] = 0;
          __s[0x7a] = 0;
          piVar10 = param_9;
          uVar6 = zz_02aca1c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              (int)__s,param_9);
          __s[0x10] = uVar6;
          if (__s[0x10] == 0) {
            uVar16 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_E2012_mwPlyCreate_can_t_create_S_802b9fe0,piVar10,param_11,
                                 param_12,param_13,param_14,param_15,param_16);
            if (__s != (undefined4 *)0x0) {
              zz_02ae48c_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)__s,
                          extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
              __s[1] = 0;
              uVar16 = zz_02aaf4c_((int)__s);
              uVar11 = extraout_r4_01;
              if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                uVar11 = extraout_r4_02;
              }
              if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                uVar16 = zz_02761ac_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     (undefined1 *)__s[0x13],uVar11,param_11,param_12,param_13,
                                     param_14,param_15,param_16);
                uVar11 = extraout_r4_03;
              }
              if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                uVar16 = zz_02aa85c_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     (undefined1 *)__s[0x11],uVar11,param_11,param_12,param_13,
                                     param_14,param_15,param_16);
                uVar11 = extraout_r4_04;
              }
              if ((int *)__s[0x4b] != (int *)0x0) {
                uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                uVar11 = extraout_r4_05;
              }
              if ((int *)__s[0x53] != (int *)0x0) {
                uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                uVar11 = extraout_r4_06;
              }
              if (__s[0x10] != 0) {
                uVar20 = zz_02a1794_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     __s[0x10]);
                uVar11 = (undefined4)uVar20;
                uVar16 = extraout_f1;
                if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                  zz_02addf4_(0xfffffece);
                  uVar16 = zz_02aa530_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar11,
                                       param_11,param_12,param_13,param_14,param_15,param_16);
                  uVar11 = extraout_r4_07;
                }
              }
              iVar4 = 0;
              do {
                iVar13 = __s[-iVar4 + 0x7a];
                if (iVar13 != 0) {
                  if (__s[0x56] == 0) {
                    puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                    uVar16 = (**(code **)(puVar3 + 0x2c))(*(undefined4 *)(puVar3 + 0x30),iVar13);
                    uVar11 = extraout_r4_08;
                  }
                  __s[0x5a] = __s[0x5a] + -1;
                  __s[-iVar4 + 0x7a] = 0;
                }
                iVar4 = iVar4 + 1;
              } while (iVar4 < 0x20);
              if (__s[0x5a] != 0) {
                zz_02aa530_(uVar16,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E2053005__forgot_free__802b9ec4,uVar11,param_11,param_12,param_13,
                            param_14,param_15,param_16);
              }
              gnt4_memset(__s,0,0x210);
              __s[1] = 0;
              *__s = &DAT_803aefa8;
            }
            __s = (undefined4 *)0x0;
          }
          else {
            piVar10 = (int *)__s[0x35];
            if (piVar10 == (int *)0x0) {
              zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E02120501__Internal_Error__mwsfc_802ba004,0,param_11,param_12,param_13,
                          param_14,param_15,param_16);
            }
            else {
              iVar14 = __s[7];
              iVar4 = piVar10[2];
              iVar13 = *piVar10;
              if (piVar10[1] < (iVar14 + 3) * iVar4) {
                zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E02120502__mwsfcre_AttachPicUsrB_802ba03c,piVar10,param_11,param_12,
                            param_13,param_14,param_15,param_16);
              }
              else {
                iVar15 = zz_02ade24_();
                if (iVar15 == 1) {
                  zz_02a0374_(__s[0x10],iVar13,iVar14 + 3,iVar4);
                  param_12 = iVar4;
                }
              }
            }
            iVar4 = param_9[5];
            uVar2 = param_9[1];
            if (iVar4 < 1) {
              iVar4 = 1;
            }
            iVar13 = (int)uVar2 >> 3;
            if (*param_9 == 2) {
              uVar2 = iVar13 + (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0);
              iVar4 = iVar4 * (((int)uVar2 >> 0xb) + (uint)((int)uVar2 < 0 && (uVar2 & 0x7ff) != 0))
                              * 0x800;
            }
            else if (*param_9 == 3) {
              uVar2 = iVar13 + (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0);
              iVar4 = iVar4 * (((int)uVar2 >> 0xb) + (uint)((int)uVar2 < 0 && (uVar2 & 0x7ff) != 0))
                              * 0x800;
            }
            else {
              uVar2 = iVar13 + (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0);
              iVar4 = iVar4 * (((int)uVar2 >> 0xb) + (uint)((int)uVar2 < 0 && (uVar2 & 0x7ff) != 0))
                              * 0x800;
            }
            iVar14 = __s[0x10];
            iVar13 = *(int *)(puVar3 + 0xc);
            iVar15 = *(int *)(puVar3 + 8);
            zz_02a3a84_(iVar14,8,0);
            zz_02a3a84_(iVar14,1,1);
            zz_02a3a84_(iVar14,0,0);
            zz_02a3a84_(iVar14,0x17,4);
            dVar19 = DAT_802ba078 +
                     ((double)CONCAT44(0x43300000,iVar15 * iVar13 * 1000 ^ 0x80000000) -
                     DAT_802ba110);
            uVar2 = (uint)dVar19;
            lVar17 = (longlong)(int)uVar2;
            if (dVar19 < (double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DAT_802ba110) {
              uVar2 = uVar2 - 1;
            }
            dVar18 = DAT_802ba110;
            zz_02a3a84_(iVar14,0x2d,uVar2);
            zz_02a3a84_(iVar14,0x2c,uVar2);
            zz_02a3a84_(iVar14,0x2a,uVar2);
            zz_02a3a84_(iVar14,0xf,2);
            zz_02a3a84_(iVar14,0x33,0);
            zz_02a3a84_(iVar14,0xe,0);
            zz_02a3a84_(iVar14,0x1c,0);
            zz_02a0508_(iVar14,5,(undefined *)0x0);
            uVar11 = __s[0x4d];
            uVar12 = __s[0x4e];
            puVar7 = zz_02774e0_(__s[0x4c],uVar11,uVar12);
            __s[0x4b] = puVar7;
            if (__s[0x4b] == 0) {
              uVar16 = zz_02aa530_(lVar17,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                   s_E2013_mwPlyCreate_can_t_create_S_802ba080,uVar11,uVar12,
                                   param_12,param_13,param_14,param_15,param_16);
              if (__s != (undefined4 *)0x0) {
                zz_02ae48c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,(int)__s,
                            extraout_r4_09,uVar12,param_12,param_13,param_14,param_15,param_16);
                __s[1] = 0;
                uVar16 = zz_02aaf4c_((int)__s);
                uVar11 = extraout_r4_10;
                if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                  uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                  uVar11 = extraout_r4_11;
                }
                if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                  uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                       (undefined1 *)__s[0x13],uVar11,uVar12,param_12,param_13,
                                       param_14,param_15,param_16);
                  uVar11 = extraout_r4_12;
                }
                if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                  uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                       (undefined1 *)__s[0x11],uVar11,uVar12,param_12,param_13,
                                       param_14,param_15,param_16);
                  uVar11 = extraout_r4_13;
                }
                if ((int *)__s[0x4b] != (int *)0x0) {
                  uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                  uVar11 = extraout_r4_14;
                }
                if ((int *)__s[0x53] != (int *)0x0) {
                  uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                  uVar11 = extraout_r4_15;
                }
                if (__s[0x10] != 0) {
                  uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                       __s[0x10]);
                  uVar11 = (undefined4)uVar20;
                  uVar16 = extraout_f1_00;
                  if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                    zz_02addf4_(0xfffffece);
                    uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                         param_8,s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar11,
                                         uVar12,param_12,param_13,param_14,param_15,param_16);
                    uVar11 = extraout_r4_16;
                  }
                }
                iVar4 = 0;
                do {
                  iVar13 = __s[-iVar4 + 0x7a];
                  if (iVar13 != 0) {
                    if (__s[0x56] == 0) {
                      puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                      uVar16 = (**(code **)(puVar3 + 0x2c))(*(undefined4 *)(puVar3 + 0x30),iVar13);
                      uVar11 = extraout_r4_17;
                    }
                    __s[0x5a] = __s[0x5a] + -1;
                    __s[-iVar4 + 0x7a] = 0;
                  }
                  iVar4 = iVar4 + 1;
                } while (iVar4 < 0x20);
                if (__s[0x5a] != 0) {
                  zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                              s_E2053005__forgot_free__802b9ec4,uVar11,uVar12,param_12,param_13,
                              param_14,param_15,param_16);
                }
                gnt4_memset(__s,0,0x210);
                __s[1] = 0;
                *__s = &DAT_803aefa8;
              }
              __s = (undefined4 *)0x0;
            }
            else {
              uVar11 = 0;
              puVar7 = zz_0276c34_(0,0);
              __s[0x53] = puVar7;
              if (__s[0x53] == 0) {
                uVar16 = zz_02aa530_(lVar17,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                     s_E2020_mwPlyCreate_can_t_create_S_802ba0a4,uVar11,uVar12,
                                     param_12,param_13,param_14,param_15,param_16);
                if (__s != (undefined4 *)0x0) {
                  zz_02ae48c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,(int)__s,
                              extraout_r4_18,uVar12,param_12,param_13,param_14,param_15,param_16);
                  __s[1] = 0;
                  uVar16 = zz_02aaf4c_((int)__s);
                  uVar11 = extraout_r4_19;
                  if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                    uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                    uVar11 = extraout_r4_20;
                  }
                  if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                    uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                         param_8,(undefined1 *)__s[0x13],uVar11,uVar12,param_12,
                                         param_13,param_14,param_15,param_16);
                    uVar11 = extraout_r4_21;
                  }
                  if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                    uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                         param_8,(undefined1 *)__s[0x11],uVar11,uVar12,param_12,
                                         param_13,param_14,param_15,param_16);
                    uVar11 = extraout_r4_22;
                  }
                  if ((int *)__s[0x4b] != (int *)0x0) {
                    uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                    uVar11 = extraout_r4_23;
                  }
                  if ((int *)__s[0x53] != (int *)0x0) {
                    uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                    uVar11 = extraout_r4_24;
                  }
                  if (__s[0x10] != 0) {
                    uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                         param_8,__s[0x10]);
                    uVar11 = (undefined4)uVar20;
                    uVar16 = extraout_f1_01;
                    if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                      zz_02addf4_(0xfffffece);
                      uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                           param_8,s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar11,
                                           uVar12,param_12,param_13,param_14,param_15,param_16);
                      uVar11 = extraout_r4_25;
                    }
                  }
                  iVar4 = 0;
                  do {
                    iVar13 = __s[-iVar4 + 0x7a];
                    if (iVar13 != 0) {
                      if (__s[0x56] == 0) {
                        puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                        uVar16 = (**(code **)(puVar3 + 0x2c))(*(undefined4 *)(puVar3 + 0x30),iVar13)
                        ;
                        uVar11 = extraout_r4_26;
                      }
                      __s[0x5a] = __s[0x5a] + -1;
                      __s[-iVar4 + 0x7a] = 0;
                    }
                    iVar4 = iVar4 + 1;
                  } while (iVar4 < 0x20);
                  if (__s[0x5a] != 0) {
                    zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                s_E2053005__forgot_free__802b9ec4,uVar11,uVar12,param_12,param_13,
                                param_14,param_15,param_16);
                  }
                  gnt4_memset(__s,0,0x210);
                  __s[1] = 0;
                  *__s = &DAT_803aefa8;
                }
                __s = (undefined4 *)0x0;
              }
              else {
                uVar11 = 1;
                *__s = &DAT_803aefa8;
                puVar7 = __s + 0x12;
                __s[0x16] = iVar4;
                iVar4 = param_9[1];
                __s[3] = *param_9;
                __s[4] = iVar4;
                iVar4 = param_9[3];
                __s[5] = param_9[2];
                __s[6] = iVar4;
                iVar4 = param_9[5];
                __s[7] = param_9[4];
                __s[8] = iVar4;
                iVar4 = param_9[7];
                __s[9] = param_9[6];
                __s[10] = iVar4;
                iVar4 = param_9[9];
                __s[0xb] = param_9[8];
                __s[0xc] = iVar4;
                iVar14 = param_9[10];
                iVar13 = param_9[0xb];
                __s[0xd] = iVar14;
                __s[0xe] = iVar13;
                __s[0xf] = 1;
                __s[0x1a] = 0;
                __s[2] = 0;
                __s[0x14] = param_9[8];
                iVar4 = zz_02a37d4_(uVar6,3,puVar7);
                if (iVar4 != 0) {
                  __s[0x12] = 0;
                }
                __s[0x1b] = 1;
                *(undefined1 *)(__s + 0x1c) = 0;
                *(undefined1 *)((int)__s + 0x71) = 0;
                *(undefined1 *)((int)__s + 0x72) = 0;
                *(undefined1 *)((int)__s + 0x73) = 0;
                __s[0x17] = 0;
                zz_02af668_((int)__s,0);
                uVar16 = zz_02af660_((int)__s,0);
                __s[0x15] = 0;
                __s[0x21] = 0;
                uVar16 = zz_02aa87c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                     (int *)__s[0x4b]);
                __s[0x11] = (int)((ulonglong)uVar16 >> 0x20);
                if (__s[0x11] == 0) {
                  if (__s != (undefined4 *)0x0) {
                    zz_02ae48c_(extraout_f1_02,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8
                                ,(int)__s,(int)uVar16,puVar7,uVar11,iVar13,iVar14,param_15,param_16)
                    ;
                    __s[1] = 0;
                    uVar16 = zz_02aaf4c_((int)__s);
                    uVar12 = extraout_r4_27;
                    if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                      uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                      uVar12 = extraout_r4_28;
                    }
                    if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                      uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                           param_8,(undefined1 *)__s[0x13],uVar12,puVar7,uVar11,
                                           iVar13,iVar14,param_15,param_16);
                      uVar12 = extraout_r4_29;
                    }
                    if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                      uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                           param_8,(undefined1 *)__s[0x11],uVar12,puVar7,uVar11,
                                           iVar13,iVar14,param_15,param_16);
                      uVar12 = extraout_r4_30;
                    }
                    if ((int *)__s[0x4b] != (int *)0x0) {
                      uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                      uVar12 = extraout_r4_31;
                    }
                    if ((int *)__s[0x53] != (int *)0x0) {
                      uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                      uVar12 = extraout_r4_32;
                    }
                    if (__s[0x10] != 0) {
                      uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                           param_8,__s[0x10]);
                      uVar12 = (undefined4)uVar20;
                      uVar16 = extraout_f1_03;
                      if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                        zz_02addf4_(0xfffffece);
                        uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                             param_8,s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,
                                             uVar12,puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                        uVar12 = extraout_r4_33;
                      }
                    }
                    iVar4 = 0;
                    do {
                      iVar15 = __s[-iVar4 + 0x7a];
                      if (iVar15 != 0) {
                        if (__s[0x56] == 0) {
                          puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                          uVar16 = (**(code **)(puVar3 + 0x2c))
                                             (*(undefined4 *)(puVar3 + 0x30),iVar15);
                          uVar12 = extraout_r4_34;
                        }
                        __s[0x5a] = __s[0x5a] + -1;
                        __s[-iVar4 + 0x7a] = 0;
                      }
                      iVar4 = iVar4 + 1;
                    } while (iVar4 < 0x20);
                    if (__s[0x5a] != 0) {
                      zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                  s_E2053005__forgot_free__802b9ec4,uVar12,puVar7,uVar11,iVar13,
                                  iVar14,param_15,param_16);
                    }
                    gnt4_memset(__s,0,0x210);
                    __s[1] = 0;
                    *__s = &DAT_803aefa8;
                  }
                  __s = (undefined4 *)0x0;
                }
                else {
                  uVar16 = zz_02ae184_(extraout_f1_02,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                       param_8,(int)__s);
                  pcVar8 = zz_0276284_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                       (int *)__s[0x4b],extraout_r4_35,puVar7,uVar11,iVar13,iVar14,
                                       param_15,param_16);
                  __s[0x13] = pcVar8;
                  __s[0x1d] = 0;
                  uVar16 = zz_02761a4_(__s[0x13],__s[0x11]);
                  uVar6 = extraout_r4_36;
                  iVar4 = zz_02ab630_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                      (int)__s,extraout_r4_36,puVar7,uVar11,iVar13,iVar14,param_15,
                                      param_16);
                  if (iVar4 == -1) {
                    if (__s != (undefined4 *)0x0) {
                      zz_02ae48c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                  (int)__s,uVar6,puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                      __s[1] = 0;
                      uVar16 = zz_02aaf4c_((int)__s);
                      uVar12 = extraout_r4_37;
                      if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                        uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                        uVar12 = extraout_r4_38;
                      }
                      if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                        uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                             param_8,(undefined1 *)__s[0x13],uVar12,puVar7,uVar11,
                                             iVar13,iVar14,param_15,param_16);
                        uVar12 = extraout_r4_39;
                      }
                      if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                        uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                             param_8,(undefined1 *)__s[0x11],uVar12,puVar7,uVar11,
                                             iVar13,iVar14,param_15,param_16);
                        uVar12 = extraout_r4_40;
                      }
                      if ((int *)__s[0x4b] != (int *)0x0) {
                        uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                        uVar12 = extraout_r4_41;
                      }
                      if ((int *)__s[0x53] != (int *)0x0) {
                        uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                        uVar12 = extraout_r4_42;
                      }
                      if (__s[0x10] != 0) {
                        uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                             param_8,__s[0x10]);
                        uVar12 = (undefined4)uVar20;
                        uVar16 = extraout_f1_04;
                        if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                          zz_02addf4_(0xfffffece);
                          uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                               param_8,s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,
                                               uVar12,puVar7,uVar11,iVar13,iVar14,param_15,param_16)
                          ;
                          uVar12 = extraout_r4_43;
                        }
                      }
                      iVar4 = 0;
                      do {
                        iVar15 = __s[-iVar4 + 0x7a];
                        if (iVar15 != 0) {
                          if (__s[0x56] == 0) {
                            puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                            uVar16 = (**(code **)(puVar3 + 0x2c))
                                               (*(undefined4 *)(puVar3 + 0x30),iVar15);
                            uVar12 = extraout_r4_44;
                          }
                          __s[0x5a] = __s[0x5a] + -1;
                          __s[-iVar4 + 0x7a] = 0;
                        }
                        iVar4 = iVar4 + 1;
                      } while (iVar4 < 0x20);
                      if (__s[0x5a] != 0) {
                        zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                    s_E2053005__forgot_free__802b9ec4,uVar12,puVar7,uVar11,iVar13,
                                    iVar14,param_15,param_16);
                      }
                      gnt4_memset(__s,0,0x210);
                      __s[1] = 0;
                      *__s = &DAT_803aefa8;
                    }
                    __s = (undefined4 *)0x0;
                  }
                  else {
                    uVar16 = zz_02ab438_(__s[0x2b],__s[0x2c]);
                    iVar4 = (int)((ulonglong)uVar16 >> 0x20);
                    if (iVar4 == 0) {
                      uVar16 = zz_02aa530_(extraout_f1_05,dVar18,dVar19,param_4,param_5,param_6,
                                           param_7,param_8,s_E201185__can_t_create_SfxHn_802ba0c8,
                                           (int)uVar16,puVar7,uVar11,iVar13,iVar14,param_15,param_16
                                          );
                      if (__s != (undefined4 *)0x0) {
                        zz_02ae48c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                    (int)__s,extraout_r4_45,puVar7,uVar11,iVar13,iVar14,param_15,
                                    param_16);
                        __s[1] = 0;
                        uVar16 = zz_02aaf4c_((int)__s);
                        uVar12 = extraout_r4_46;
                        if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                          uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                          uVar12 = extraout_r4_47;
                        }
                        if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                          uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                               param_8,(undefined1 *)__s[0x13],uVar12,puVar7,uVar11,
                                               iVar13,iVar14,param_15,param_16);
                          uVar12 = extraout_r4_48;
                        }
                        if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                          uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                               param_8,(undefined1 *)__s[0x11],uVar12,puVar7,uVar11,
                                               iVar13,iVar14,param_15,param_16);
                          uVar12 = extraout_r4_49;
                        }
                        if ((int *)__s[0x4b] != (int *)0x0) {
                          uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                          uVar12 = extraout_r4_50;
                        }
                        if ((int *)__s[0x53] != (int *)0x0) {
                          uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                          uVar12 = extraout_r4_51;
                        }
                        if (__s[0x10] != 0) {
                          uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                               param_8,__s[0x10]);
                          uVar12 = (undefined4)uVar20;
                          uVar16 = extraout_f1_06;
                          if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                            zz_02addf4_(0xfffffece);
                            uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,
                                                 param_7,param_8,
                                                 s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar12,
                                                 puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                            uVar12 = extraout_r4_52;
                          }
                        }
                        iVar4 = 0;
                        do {
                          iVar15 = __s[-iVar4 + 0x7a];
                          if (iVar15 != 0) {
                            if (__s[0x56] == 0) {
                              puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                              uVar16 = (**(code **)(puVar3 + 0x2c))
                                                 (*(undefined4 *)(puVar3 + 0x30),iVar15);
                              uVar12 = extraout_r4_53;
                            }
                            __s[0x5a] = __s[0x5a] + -1;
                            __s[-iVar4 + 0x7a] = 0;
                          }
                          iVar4 = iVar4 + 1;
                        } while (iVar4 < 0x20);
                        if (__s[0x5a] != 0) {
                          zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                      s_E2053005__forgot_free__802b9ec4,uVar12,puVar7,uVar11,iVar13,
                                      iVar14,param_15,param_16);
                        }
                        gnt4_memset(__s,0,0x210);
                        __s[1] = 0;
                        *__s = &DAT_803aefa8;
                      }
                      __s = (undefined4 *)0x0;
                    }
                    else {
                      __s[0x2a] = iVar4;
                      uVar16 = zz_02ab0ec_((int)__s,__s[0xb]);
                      uVar12 = extraout_r4_54;
                      puVar9 = zz_02aaf84_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                           param_8,__s,extraout_r4_54,puVar7,uVar11,iVar13,iVar14,
                                           param_15,param_16);
                      __s[0x3a] = puVar9;
                      iVar4 = zz_02aaee0_((int)__s);
                      if (iVar4 == 0) {
                        zz_02aaec4_((int)__s);
                        __s[1] = 1;
                      }
                      else {
                        uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,
                                             param_8,s_E201212_mwPlyCreate__can_t_set_A_802ba0e4,
                                             uVar12,puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                        if (__s != (undefined4 *)0x0) {
                          zz_02ae48c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8,
                                      (int)__s,extraout_r4_55,puVar7,uVar11,iVar13,iVar14,param_15,
                                      param_16);
                          __s[1] = 0;
                          uVar16 = zz_02aaf4c_((int)__s);
                          uVar12 = extraout_r4_56;
                          if ((undefined4 *)__s[0x2a] != (undefined4 *)0x0) {
                            uVar16 = zz_02ab418_((undefined4 *)__s[0x2a]);
                            uVar12 = extraout_r4_57;
                          }
                          if ((undefined1 *)__s[0x13] != (undefined1 *)0x0) {
                            uVar16 = zz_02761ac_(uVar16,dVar18,dVar19,param_4,param_5,param_6,
                                                 param_7,param_8,(undefined1 *)__s[0x13],uVar12,
                                                 puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                            uVar12 = extraout_r4_58;
                          }
                          if ((undefined1 *)__s[0x11] != (undefined1 *)0x0) {
                            uVar16 = zz_02aa85c_(uVar16,dVar18,dVar19,param_4,param_5,param_6,
                                                 param_7,param_8,(undefined1 *)__s[0x11],uVar12,
                                                 puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                            uVar12 = extraout_r4_59;
                          }
                          if ((int *)__s[0x4b] != (int *)0x0) {
                            uVar16 = (**(code **)(*(int *)__s[0x4b] + 0xc))();
                            uVar12 = extraout_r4_60;
                          }
                          if ((int *)__s[0x53] != (int *)0x0) {
                            uVar16 = (**(code **)(*(int *)__s[0x53] + 0xc))();
                            uVar12 = extraout_r4_61;
                          }
                          if (__s[0x10] != 0) {
                            uVar20 = zz_02a1794_(uVar16,dVar18,dVar19,param_4,param_5,param_6,
                                                 param_7,param_8,__s[0x10]);
                            uVar12 = (undefined4)uVar20;
                            uVar16 = extraout_f1_07;
                            if ((int)((ulonglong)uVar20 >> 0x20) != 0) {
                              zz_02addf4_(0xfffffece);
                              uVar16 = zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,
                                                   param_7,param_8,
                                                   s_E20010703E_MWSFCRE_DestroySfd__802b9ea4,uVar12,
                                                   puVar7,uVar11,iVar13,iVar14,param_15,param_16);
                              uVar12 = extraout_r4_62;
                            }
                          }
                          iVar4 = 0;
                          do {
                            iVar15 = __s[-iVar4 + 0x7a];
                            if (iVar15 != 0) {
                              if (__s[0x56] == 0) {
                                puVar3 = GetOneTimerLeadGroundContactAnims_void_();
                                uVar16 = (**(code **)(puVar3 + 0x2c))
                                                   (*(undefined4 *)(puVar3 + 0x30),iVar15);
                                uVar12 = extraout_r4_63;
                              }
                              __s[0x5a] = __s[0x5a] + -1;
                              __s[-iVar4 + 0x7a] = 0;
                            }
                            iVar4 = iVar4 + 1;
                          } while (iVar4 < 0x20);
                          if (__s[0x5a] != 0) {
                            zz_02aa530_(uVar16,dVar18,dVar19,param_4,param_5,param_6,param_7,param_8
                                        ,s_E2053005__forgot_free__802b9ec4,uVar12,puVar7,uVar11,
                                        iVar13,iVar14,param_15,param_16);
                          }
                          gnt4_memset(__s,0,0x210);
                          __s[1] = 0;
                          *__s = &DAT_803aefa8;
                        }
                        __s = (undefined4 *)0x0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
      __s = (undefined4 *)0x0;
    }
  }
  return __s;
}



// ==== 802ac91c  zz_02ac91c_ ====

undefined4
zz_02ac91c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar5 = *(int *)(param_9 + 0x40);
  iVar1 = zz_02a143c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5);
  if (iVar1 == 0) {
    pcVar3 = FUN_802adcac;
    iVar1 = param_9;
    iVar5 = zz_029ab20_(iVar5,FUN_802adcac,param_9);
    if (iVar5 == 0) {
      piVar4 = *(int **)(param_9 + 0xd4);
      if (piVar4 == (int *)0x0) {
        zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E02120501__Internal_Error__mwsfc_802ba004,0,iVar1,param_12,param_13,param_14,
                    param_15,param_16);
      }
      else {
        iVar7 = *(int *)(param_9 + 0x1c);
        iVar6 = piVar4[2];
        iVar5 = *piVar4;
        if (piVar4[1] < (iVar7 + 3) * iVar6) {
          zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      s_E02120502__mwsfcre_AttachPicUsrB_802ba03c,piVar4,iVar1,param_12,param_13,
                      param_14,param_15,param_16);
        }
        else {
          iVar1 = zz_02ade24_();
          if (iVar1 == 1) {
            zz_02a0374_(*(int *)(param_9 + 0x40),iVar5,iVar7 + 3,iVar6);
          }
        }
      }
      uVar2 = 0;
    }
    else {
      zz_02addf4_(0xfffffed1);
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E0203262__MWSFCRE_ResetSfdHn__SF_802ba14c,pcVar3,iVar1,param_12,param_13,
                  param_14,param_15,param_16);
      uVar2 = 0xffffffff;
    }
  }
  else {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E0203261__MWSFCRE_ResetSfdHn__SF_802ba118,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}



// ==== 802aca1c  zz_02aca1c_ ====

/* WARNING: Removing unreachable block (ram,0x802ad158) */
/* WARNING: Removing unreachable block (ram,0x802ad210) */

uint zz_02aca1c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10)

{
  undefined **ppuVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  uint extraout_r4;
  int *piVar8;
  uint extraout_r4_00;
  uint extraout_r4_01;
  uint extraout_r4_02;
  uint extraout_r4_03;
  uint extraout_r4_04;
  uint extraout_r4_05;
  uint extraout_r4_06;
  undefined **ppuVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  code *pcVar12;
  uint uVar13;
  int *piVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  int iVar18;
  uint uVar19;
  undefined4 uVar20;
  int iVar21;
  uint in_r8;
  int in_r9;
  undefined4 uVar22;
  undefined4 in_r10;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 extraout_f1_04;
  undefined8 extraout_f1_05;
  undefined8 extraout_f1_06;
  undefined8 extraout_f1_07;
  undefined8 uVar33;
  ulonglong uVar34;
  ulonglong uVar35;
  int aiStack_d8 [2];
  int local_d0 [15];
  undefined4 uStack_94;
  int local_90 [10];
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined4 local_58;
  int local_54;
  undefined4 local_50;
  int local_4c;
  
  iVar21 = -0x7fc50000;
  iVar18 = -0x7fbd0000;
  uVar13 = 0x802c0000;
  iVar2 = param_10[5];
  iVar25 = *param_10;
  iVar24 = param_10[4];
  local_4c = param_10[2];
  iVar23 = param_10[3];
  uVar4 = param_10[1];
  if (iVar2 < 1) {
    iVar2 = 1;
  }
  iVar3 = (int)uVar4 >> 3;
  if (iVar25 == 2) {
    uVar4 = iVar3 + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0);
    DAT_80430f9c = 0;
    iVar3 = (((int)uVar4 >> 0xb) + (uint)((int)uVar4 < 0 && (uVar4 & 0x7ff) != 0)) * 0x800;
    DAT_80430f98 = 0;
    DAT_80430f88 = 0;
    DAT_80430f8c = 0;
    DAT_80430fa4 = iVar2 * iVar3;
  }
  else if (iVar25 == 3) {
    uVar4 = iVar3 + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0);
    uVar13 = ((int)uVar4 >> 0xb) + (uint)((int)uVar4 < 0 && (uVar4 & 0x7ff) != 0);
    DAT_80430f98 = 0;
    iVar18 = uVar13 * 0x800;
    iVar3 = iVar2 * iVar18;
    DAT_80430f88 = 0;
    DAT_80430f8c = 0;
    DAT_80430f9c = ((int)((uVar13 >> 0x14 & 1) + iVar18) >> 1) + 0x800;
    DAT_80430fa4 = iVar3;
  }
  else {
    uVar4 = iVar3 + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0);
    iVar18 = 0;
    in_r8 = ((int)uVar4 >> 0xb) + (uint)((int)uVar4 < 0 && (uVar4 & 0x7ff) != 0);
    in_r9 = in_r8 * 0x800;
    iVar3 = 0x5f0c;
    iVar21 = iVar2 * in_r9;
    DAT_80430f98 = 0x5dcc;
    uVar13 = (int)((in_r8 >> 0x14 & 1) + in_r9) >> 1;
    DAT_80430f9c = uVar13 + 0x800;
    DAT_80430f88 = 0x5f0c;
    DAT_80430f8c = 0xc1c0;
    DAT_80430fa4 = iVar21;
  }
  DAT_80430fa0 = 0;
  iVar2 = param_10[4];
  iVar28 = param_10[2];
  iVar26 = param_10[3];
  if ((3 < param_10[9]) || (param_10[9] < 0)) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E206011__MwsfdCrePrm__illigal_bu_802ba1bc,iVar3,uVar13,iVar18,iVar21,
                          in_r8,in_r9,in_r10);
  }
  uVar4 = iVar28 + 0xf;
  uVar13 = iVar26 + 0xf;
  uVar4 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
  iVar18 = uVar4 * 0x10;
  uVar19 = ((int)uVar13 >> 4) + (uint)((int)uVar13 < 0 && (uVar13 & 0xf) != 0);
  uVar13 = iVar18 + 0x1f;
  iVar21 = uVar19 * 0x10;
  iVar26 = (uVar4 >> 0x1b & 1) + iVar18;
  iVar28 = (int)((uVar19 >> 0x1b & 1) + iVar21) >> 1;
  iVar3 = (((int)uVar13 >> 5) + (uint)((int)uVar13 < 0 && (uVar13 & 0x1f) != 0)) * 0x20;
  iVar27 = DAT_80430fa0 + DAT_80430f9c + DAT_80430f98 + 0x20;
  uVar4 = (iVar26 >> 1) + 0x1f;
  iVar21 = iVar21 * iVar3 +
           iVar28 * (((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)) * 0x20 * 2 +
           0x20;
  DAT_80430f90 = iVar2 * iVar21;
  DAT_80430f94 = iVar21 * 2;
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (iVar27 < 0) {
      uVar34 = (ulonglong)DAT_80430fa0;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar7 = GetOneTimerLeadGroundContactAnims_void_();
        uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),iVar27);
        param_1 = extraout_f1;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar27)) {
        uVar34 = (ulonglong)DAT_80430fa0;
      }
      else {
        uVar34 = CONCAT44(*(int *)(param_9 + 0x160),DAT_80430fa0);
        *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + iVar27;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar27;
      }
      iVar2 = (int)(uVar34 >> 0x20);
      if (iVar2 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar2;
        uVar34 = CONCAT44(iVar2,*(int *)(param_9 + 0x168));
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,DAT_80430fa0,iVar26,iVar28
                          ,iVar3,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4;
  }
  iVar21 = (int)(uVar34 >> 0x20);
  iVar2 = DAT_80430fa4 + 0x40;
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (iVar2 < 0) {
      iVar26 = 0;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar7 = GetOneTimerLeadGroundContactAnims_void_();
        iVar26 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),iVar2);
        param_1 = extraout_f1_00;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar2)) {
        iVar26 = 0;
      }
      else {
        iVar26 = *(int *)(param_9 + 0x160);
        *(int *)(param_9 + 0x160) = iVar26 + iVar2;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar2;
      }
      if (iVar26 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar26;
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar26,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    iVar26 = 0;
  }
  piVar14 = aiStack_d8;
  piVar8 = param_10;
  iVar2 = zz_02ad720_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      (int)param_10,piVar14,iVar28,iVar3,iVar18,in_r9,in_r10);
  iVar29 = param_10[4];
  iVar32 = 0;
  iVar30 = param_10[2];
  iVar27 = param_10[3];
  if ((3 < param_10[9]) || (param_10[9] < 0)) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E206011__MwsfdCrePrm__illigal_bu_802ba1bc,piVar8,piVar14,iVar28,iVar3,
                          iVar18,in_r9,in_r10);
  }
  uVar13 = iVar30 + 0xf;
  uVar4 = iVar27 + 0xf;
  piVar8 = local_d0;
  uVar13 = ((int)uVar13 >> 4) + (uint)((int)uVar13 < 0 && (uVar13 & 0xf) != 0);
  iVar28 = uVar13 * 0x10;
  uVar19 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
  uVar4 = iVar28 + 0x1f;
  iVar27 = uVar19 * 0x10;
  uVar19 = (int)((uVar19 >> 0x1b & 1) + iVar27) >> 1;
  iVar30 = (((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)) * 0x20;
  uVar4 = ((int)((uVar13 >> 0x1b & 1) + iVar28) >> 1) + 0x1f;
  iVar31 = iVar27 * iVar30 +
           uVar19 * (((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)) * 0x20 * 2 +
           0x20;
  for (iVar27 = 0; iVar5 = DAT_80430f88, iVar27 < iVar29; iVar27 = iVar27 + 1) {
    if (*(int *)(param_9 + 0x168) < 0x20) {
      if (iVar31 < 0) {
        uVar34 = (ulonglong)uVar19;
      }
      else {
        if (*(int *)(param_9 + 0x158) == 0) {
          puVar7 = GetOneTimerLeadGroundContactAnims_void_();
          uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),iVar31);
          param_1 = extraout_f1_01;
        }
        else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar31)) {
          uVar34 = (ulonglong)uVar19;
        }
        else {
          uVar34 = CONCAT44(*(int *)(param_9 + 0x160),uVar19);
          *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + iVar31;
          *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar31;
        }
        iVar5 = (int)(uVar34 >> 0x20);
        if (iVar5 != 0) {
          *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar5;
          uVar34 = CONCAT44(iVar5,*(int *)(param_9 + 0x168));
          *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
        }
      }
    }
    else {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,uVar19,iVar30,iVar28,
                            iVar3,iVar18,in_r9,in_r10);
      uVar34 = (ulonglong)extraout_r4_00;
    }
    uVar19 = (uint)uVar34;
    *piVar8 = (int)(uVar34 >> 0x20);
    if (*piVar8 == 0) {
      iVar32 = -1;
    }
    piVar8 = piVar8 + 1;
  }
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (DAT_80430f88 < 0) {
      uVar34 = (ulonglong)uVar19;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar7 = GetOneTimerLeadGroundContactAnims_void_();
        uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),iVar5);
        param_1 = extraout_f1_02;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + DAT_80430f88)) {
        uVar34 = (ulonglong)uVar19;
      }
      else {
        uVar34 = CONCAT44(*(int *)(param_9 + 0x160),uVar19);
        *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + DAT_80430f88;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar5;
      }
      iVar27 = (int)(uVar34 >> 0x20);
      if (iVar27 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar27;
        uVar34 = CONCAT44(iVar27,*(int *)(param_9 + 0x168));
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,uVar19,iVar30,iVar28,iVar3
                          ,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4_01;
  }
  iVar27 = DAT_80430f8c;
  iVar29 = (int)(uVar34 >> 0x20);
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (DAT_80430f8c < 0) {
      uVar34 = uVar34 & 0xffffffff;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar7 = GetOneTimerLeadGroundContactAnims_void_();
        uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),iVar27);
        param_1 = extraout_f1_03;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + DAT_80430f8c)) {
        uVar34 = uVar34 & 0xffffffff;
      }
      else {
        uVar34 = CONCAT44(*(int *)(param_9 + 0x160),(int)uVar34);
        *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + DAT_80430f8c;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar27;
      }
      iVar27 = (int)(uVar34 >> 0x20);
      if (iVar27 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar27;
        uVar34 = CONCAT44(iVar27,*(int *)(param_9 + 0x168));
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar30,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4_02;
  }
  iVar27 = (int)(uVar34 >> 0x20);
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (*(int *)(param_9 + 0x158) == 0) {
      puVar7 = GetOneTimerLeadGroundContactAnims_void_();
      uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),0x800);
      param_1 = extraout_f1_04;
    }
    else if (*(uint *)(param_9 + 0x15c) < *(int *)(param_9 + 0x164) + 0x800U) {
      uVar34 = uVar34 & 0xffffffff;
    }
    else {
      iVar31 = *(int *)(param_9 + 0x160);
      *(int *)(param_9 + 0x160) = iVar31 + 0x800;
      uVar34 = CONCAT44(iVar31,*(int *)(param_9 + 0x164));
      *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + 0x800;
    }
    iVar31 = (int)(uVar34 >> 0x20);
    if (iVar31 != 0) {
      *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar31;
      uVar34 = CONCAT44(iVar31,*(int *)(param_9 + 0x168));
      *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar30,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4_03;
  }
  iVar31 = (int)(uVar34 >> 0x20);
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (*(int *)(param_9 + 0x158) == 0) {
      puVar7 = GetOneTimerLeadGroundContactAnims_void_();
      uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),0x4000);
      param_1 = extraout_f1_05;
    }
    else if (*(uint *)(param_9 + 0x15c) < *(int *)(param_9 + 0x164) + 0x4000U) {
      uVar34 = uVar34 & 0xffffffff;
    }
    else {
      iVar5 = *(int *)(param_9 + 0x160);
      *(int *)(param_9 + 0x160) = iVar5 + 0x4000;
      uVar34 = CONCAT44(iVar5,*(int *)(param_9 + 0x164));
      *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + 0x4000;
    }
    iVar5 = (int)(uVar34 >> 0x20);
    if (iVar5 != 0) {
      *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar5;
      uVar34 = CONCAT44(iVar5,*(int *)(param_9 + 0x168));
      *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar30,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4_04;
  }
  iVar5 = (int)(uVar34 >> 0x20);
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (*(int *)(param_9 + 0x158) == 0) {
      puVar7 = GetOneTimerLeadGroundContactAnims_void_();
      uVar34 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),0x700);
      param_1 = extraout_f1_06;
    }
    else if (*(uint *)(param_9 + 0x15c) < *(int *)(param_9 + 0x164) + 0x700U) {
      uVar34 = uVar34 & 0xffffffff;
    }
    else {
      iVar6 = *(int *)(param_9 + 0x160);
      *(int *)(param_9 + 0x160) = iVar6 + 0x700;
      uVar34 = CONCAT44(iVar6,*(int *)(param_9 + 0x164));
      *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + 0x700;
    }
    iVar6 = (int)(uVar34 >> 0x20);
    if (iVar6 != 0) {
      *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar6;
      uVar34 = CONCAT44(iVar6,*(int *)(param_9 + 0x168));
      *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar30,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    uVar34 = (ulonglong)extraout_r4_05;
  }
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (*(int *)(param_9 + 0x158) == 0) {
      puVar7 = GetOneTimerLeadGroundContactAnims_void_();
      uVar35 = (**(code **)(puVar7 + 0x28))(*(undefined4 *)(puVar7 + 0x30),0x100);
      param_1 = extraout_f1_07;
    }
    else if (*(uint *)(param_9 + 0x15c) < *(int *)(param_9 + 0x164) + 0x100U) {
      uVar35 = uVar34 & 0xffffffff;
    }
    else {
      iVar6 = *(int *)(param_9 + 0x160);
      *(int *)(param_9 + 0x160) = iVar6 + 0x100;
      uVar35 = CONCAT44(iVar6,*(int *)(param_9 + 0x164));
      *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + 0x100;
    }
    iVar6 = (int)(uVar35 >> 0x20);
    if (iVar6 != 0) {
      *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar6;
      uVar35 = CONCAT44(iVar6,*(int *)(param_9 + 0x168));
      *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar34,iVar30,iVar28,
                          iVar3,iVar18,in_r9,in_r10);
    uVar35 = (ulonglong)extraout_r4_06;
  }
  iVar6 = (int)(uVar35 >> 0x20);
  if ((((((iVar21 == 0) || (iVar26 == 0)) || (iVar2 != 0)) || ((iVar32 != 0 || (iVar29 == 0)))) ||
      ((iVar27 == 0 || ((iVar31 == 0 || (iVar5 == 0)))))) ||
     ((iVar6 == 0 || ((int)(uVar34 >> 0x20) == 0)))) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2053002__not_enough_work_802ba1e4,(int)uVar35,iVar30,iVar28,iVar3,iVar18,in_r9,
                in_r10);
    iVar18 = 0;
    do {
      iVar21 = (0x1f - iVar18) * 4 + 0x16c;
      iVar2 = *(int *)(param_9 + iVar21);
      if (iVar2 != 0) {
        if (*(int *)(param_9 + 0x158) == 0) {
          puVar7 = GetOneTimerLeadGroundContactAnims_void_();
          (**(code **)(puVar7 + 0x2c))(*(undefined4 *)(puVar7 + 0x30),iVar2);
        }
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + -1;
        *(undefined4 *)(param_9 + iVar21) = 0;
      }
      iVar18 = iVar18 + 1;
    } while (iVar18 < 0x20);
    return 0;
  }
  DAT_80430fa8 = iVar26 + 0x3fU & 0xffffffc0;
  puVar15 = (undefined4 *)0x0;
  DAT_803af0c0 = param_10[2];
  DAT_803af0c4 = param_10[3];
  uVar4 = DAT_803af0c0 / 2 + 0x1f;
  iVar18 = (((int)uVar4 >> 5) + (uint)((int)uVar4 < 0 && (uVar4 & 0x1f) != 0)) * 0x20;
  iVar2 = DAT_803af0c4 / 2;
  DAT_803af0c8 = 0;
  DAT_803af0d8 = 0;
  DAT_803af0b8 = iVar18;
  DAT_803af0bc = iVar2;
  DAT_803af0cc = DAT_803af0c0;
  DAT_803af0d0 = DAT_803af0c4;
  DAT_803af0d4 = iVar24;
  DAT_803af0e4 = iVar29;
  DAT_803af0f4 = iVar27;
  if (iVar25 == 2) {
    iVar3 = 8;
    puVar16 = (undefined4 *)0x803af02c;
    puVar15 = &uStack_94;
    do {
      puVar17 = puVar15;
      puVar10 = puVar16;
      uVar22 = puVar10[2];
      puVar17[1] = puVar10[1];
      puVar15 = puVar17 + 2;
      *puVar15 = uVar22;
      iVar3 = iVar3 + -1;
      puVar16 = puVar10 + 2;
    } while (iVar3 != 0);
    puVar17[3] = puVar10[3];
    *(uint *)(param_9 + 0x130) = DAT_80430fa8;
    *(int *)(param_9 + 0x134) = DAT_80430fa4 + -0x800;
    *(undefined4 *)(param_9 + 0x138) = 0x800;
  }
  else if (iVar25 < 2) {
    if (0 < iVar25) {
      iVar3 = 8;
      ppuVar1 = &PTR_FUN_803aefe8;
      puVar15 = &uStack_94;
      do {
        puVar16 = puVar15;
        ppuVar9 = ppuVar1;
        puVar7 = ppuVar9[2];
        puVar16[1] = ppuVar9[1];
        puVar15 = puVar16 + 2;
        *puVar15 = puVar7;
        iVar3 = iVar3 + -1;
        ppuVar1 = ppuVar9 + 2;
      } while (iVar3 != 0);
      puVar16[3] = ppuVar9[3];
      *(uint *)(param_9 + 0x130) = DAT_80430fa8;
      *(int *)(param_9 + 0x134) = DAT_80430fa4 + -0x800;
      *(undefined4 *)(param_9 + 0x138) = 0x800;
    }
  }
  else if (iVar25 < 4) {
    iVar3 = 8;
    puVar16 = (undefined4 *)0x803af070;
    puVar15 = &uStack_94;
    do {
      puVar17 = puVar15;
      puVar10 = puVar16;
      uVar22 = puVar10[2];
      puVar17[1] = puVar10[1];
      puVar15 = puVar17 + 2;
      *puVar15 = uVar22;
      iVar3 = iVar3 + -1;
      puVar16 = puVar10 + 2;
    } while (iVar3 != 0);
    puVar17[3] = puVar10[3];
    *(uint *)(param_9 + 0x130) = DAT_80430fa8;
    *(int *)(param_9 + 0x134) = DAT_80430fa4 + -0x800;
    *(undefined4 *)(param_9 + 0x138) = 0x800;
  }
  local_68 = DAT_803af0f8;
  if (DAT_80430fa0 != 0) {
    DAT_80430fa0 = ((int)DAT_80430fa0 / DAT_803af0f8) * DAT_803af0f8;
  }
  iVar3 = param_10[9];
  if (iVar3 == 2) {
    uVar22 = 2;
    goto LAB_802ad600;
  }
  if (iVar3 < 2) {
    if (iVar3 == 0) {
      uVar22 = 3;
      goto LAB_802ad600;
    }
    if (-1 < iVar3) {
      uVar22 = 1;
      goto LAB_802ad600;
    }
  }
  else if (iVar3 < 4) {
    uVar22 = 3;
    goto LAB_802ad600;
  }
  zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              s_E206011__MwsfdCrePrm__illigal_bu_802ba1bc,DAT_803af0f8,puVar15,&DAT_803af0b8,iVar2,
              iVar18,in_r9,in_r10);
  uVar22 = 3;
LAB_802ad600:
  uVar20 = 0x4000;
  local_90[4] = DAT_80430f98;
  piVar8 = local_d0;
  local_90[2] = DAT_80430fa0;
  local_90[3] = DAT_80430f9c;
  local_60 = local_4c;
  local_50 = 0x4000;
  iVar18 = DAT_80430f9c;
  uVar4 = DAT_80430fa0;
  local_90[1] = iVar21;
  local_64 = iVar24;
  local_5c = iVar23;
  local_58 = uVar22;
  local_54 = iVar5;
  uVar33 = zz_02a063c_(&DAT_803af0b8,aiStack_d8,piVar8);
  if (iVar25 == 1) {
    uVar33 = zz_02982c4_((undefined4 *)&DAT_803af0dc);
  }
  uVar11 = 0;
  uVar13 = zz_02a1dd8_(uVar33,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_90);
  if (uVar13 == 0) {
    zz_02addf4_(0xfffffecf);
    zz_02aa530_(uVar33,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E20010703C_mwPlyCreateSofdec__cr_802ba200,uVar11,piVar8,uVar20,iVar18,uVar4,uVar22
                ,in_r10);
    uVar13 = 0;
  }
  else {
    pcVar12 = FUN_802adcac;
    iVar2 = param_9;
    iVar21 = zz_029ab20_(uVar13,FUN_802adcac,param_9);
    if (iVar21 == 0) {
      *(int *)(param_9 + 0x110) = iVar6;
      *(undefined4 *)(param_9 + 0x114) = 0x100;
      *(int *)(param_9 + 0xd8) = iVar31;
      *(undefined4 *)(param_9 + 0xdc) = 0x40;
      *(undefined4 *)(param_9 + 0xe0) = 0;
      *(undefined4 *)(param_9 + 0xe4) = 0;
      *(int *)(param_9 + 0xbc) = iVar31 + 0x40;
      *(undefined4 *)(param_9 + 0xc0) = 0x7c0;
      *(undefined4 *)(param_9 + 0xc4) = 0x40;
      *(int *)(param_9 + 0xd4) = param_9 + 0xbc;
    }
    else {
      zz_02addf4_(0xfffffed1);
      zz_02aa530_(uVar33,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E20010703D_mwPlyCreateSofdec__se_802ba22c,pcVar12,iVar2,uVar20,iVar18,uVar4,
                  uVar22,in_r10);
      uVar13 = 0;
    }
  }
  return uVar13;
}



// ==== 802ad720  zz_02ad720_ ====

undefined4
zz_02ad720_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10,int *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
           undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  uint extraout_r4;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  undefined8 extraout_f1;
  ulonglong uVar11;
  
  uVar9 = 0;
  uVar5 = *(int *)(param_10 + 8) + 0xf;
  uVar1 = *(int *)(param_10 + 0xc) + 0xf;
  uVar5 = ((int)uVar5 >> 4) + (uint)((int)uVar5 < 0 && (uVar5 & 0xf) != 0);
  uVar6 = ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
  iVar3 = uVar5 * 0x10;
  uVar1 = iVar3 + 0x1f;
  iVar8 = uVar6 * 0x10;
  uVar6 = (int)((uVar6 >> 0x1b & 1) + iVar8) >> 1;
  iVar7 = (((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * 0x20;
  uVar1 = ((int)((uVar5 >> 0x1b & 1) + iVar3) >> 1) + 0x1f;
  iVar10 = iVar8 * iVar7 +
           uVar6 * (((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * 0x20 * 2 +
           0x20;
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (iVar10 < 0) {
      uVar11 = (ulonglong)uVar6;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar4 = GetOneTimerLeadGroundContactAnims_void_();
        uVar11 = (**(code **)(puVar4 + 0x28))(*(undefined4 *)(puVar4 + 0x30),iVar10);
        param_1 = extraout_f1;
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar10)) {
        uVar11 = (ulonglong)uVar6;
      }
      else {
        uVar11 = CONCAT44(*(int *)(param_9 + 0x160),uVar6);
        *(int *)(param_9 + 0x160) = *(int *)(param_9 + 0x160) + iVar10;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar10;
      }
      iVar2 = (int)(uVar11 >> 0x20);
      if (iVar2 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar2;
        uVar11 = CONCAT44(iVar2,*(int *)(param_9 + 0x168));
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,uVar6,iVar7,iVar3,iVar8,
                          param_14,param_15,param_16);
    uVar11 = (ulonglong)extraout_r4;
  }
  *param_11 = (int)(uVar11 >> 0x20);
  if (*(int *)(param_9 + 0x168) < 0x20) {
    if (iVar10 < 0) {
      iVar3 = 0;
    }
    else {
      if (*(int *)(param_9 + 0x158) == 0) {
        puVar4 = GetOneTimerLeadGroundContactAnims_void_();
        iVar3 = (**(code **)(puVar4 + 0x28))(*(undefined4 *)(puVar4 + 0x30),iVar10);
      }
      else if (*(uint *)(param_9 + 0x15c) < (uint)(*(int *)(param_9 + 0x164) + iVar10)) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(param_9 + 0x160);
        *(int *)(param_9 + 0x160) = iVar3 + iVar10;
        *(int *)(param_9 + 0x164) = *(int *)(param_9 + 0x164) + iVar10;
      }
      if (iVar3 != 0) {
        *(int *)(param_9 + *(int *)(param_9 + 0x168) * 4 + 0x16c) = iVar3;
        *(int *)(param_9 + 0x168) = *(int *)(param_9 + 0x168) + 1;
      }
    }
  }
  else {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_XE2053001_MWSFD_Malloc__cnt_over_802b9e2b + 1,(int)uVar11,iVar7,iVar3,iVar8,
                param_14,param_15,param_16);
    iVar3 = 0;
  }
  param_11[1] = iVar3;
  if ((*param_11 == 0) || (param_11[1] == 0)) {
    uVar9 = 0xffffffff;
  }
  return uVar9;
}



// ==== 802ad96c  zz_02ad96c_ ====

void zz_02ad96c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar4;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar2 = *(int *)(param_9 + 0x128);
  iVar3 = *(int *)(param_9 + 0x40);
  if (iVar2 != 0) {
    if (iVar2 == *(int *)(param_9 + 0x14c)) {
      local_18 = 1;
      local_10 = *(undefined4 *)(param_9 + 0x150);
      local_c = *(undefined4 *)(param_9 + 0x154);
      local_8 = 0;
    }
    else if (iVar2 == *(int *)(param_9 + 300)) {
      local_18 = 0;
      local_10 = *(undefined4 *)(param_9 + 0x130);
      local_c = *(undefined4 *)(param_9 + 0x134);
      local_8 = *(undefined4 *)(param_9 + 0x138);
    }
    else {
      local_18 = *(int *)(param_9 + 0x13c);
      local_10 = *(undefined4 *)(param_9 + 0x140);
      local_c = *(undefined4 *)(param_9 + 0x144);
      local_8 = *(undefined4 *)(param_9 + 0x148);
    }
    local_4 = 0;
    local_14 = iVar2;
    uVar4 = zz_02a0fa8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                        &local_18);
    uVar1 = (undefined4)uVar4;
    if ((int)((ulonglong)uVar4 >> 0x20) != 0) {
      uVar4 = extraout_f1;
      zz_02addf4_(0xfffffec8);
      zz_02aa530_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E20010703B_MWSFCRE_SetSupplySj__802ba254,uVar1,iVar2,iVar3,in_r7,in_r8,in_r9,
                  in_r10);
    }
  }
  return;
}



// ==== 802ada60  zz_02ada60_ ====

int zz_02ada60_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_9 == (int *)0x0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122613_mwPlyCalcWorkCprmSfd__c_802ba278,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    iVar1 = 0;
  }
  else {
    iVar1 = zz_02adadc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar2 = zz_02ab458_();
    iVar3 = zz_02ab010_((int)param_9);
    if (iVar3 == 1) {
      iVar2 = iVar2 + 0x20000;
    }
    iVar1 = iVar1 + iVar2;
  }
  return iVar1;
}



// ==== 802adadc  zz_02adadc_ ====

int zz_02adadc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar4 = param_9[5];
  uVar1 = param_9[1];
  if (iVar4 < 1) {
    iVar4 = 1;
  }
  iVar2 = (int)uVar1 >> 3;
  if (*param_9 == 2) {
    uVar1 = iVar2 + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
    iVar6 = 0;
    iVar11 = 0;
    iVar10 = 0;
    iVar9 = 0;
    iVar12 = iVar4 * (((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0)) * 0x800;
    iVar2 = 2;
  }
  else if (*param_9 == 3) {
    uVar1 = iVar2 + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
    iVar11 = 0;
    iVar10 = 0;
    uVar1 = ((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0);
    iVar9 = 0;
    iVar2 = uVar1 * 0x800;
    iVar12 = iVar4 * iVar2;
    iVar2 = (int)((uVar1 >> 0x14 & 1) + iVar2) >> 1;
    iVar6 = iVar2 + 0x800;
  }
  else {
    uVar1 = iVar2 + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
    iVar9 = 0xc1c0;
    uVar1 = ((int)uVar1 >> 0xb) + (uint)((int)uVar1 < 0 && (uVar1 & 0x7ff) != 0);
    iVar11 = 0x5dcc;
    iVar2 = uVar1 * 0x800;
    iVar10 = 0x5f0c;
    iVar12 = iVar4 * iVar2;
    iVar2 = (int)((uVar1 >> 0x14 & 1) + iVar2) >> 1;
    iVar6 = iVar2 + 0x800;
  }
  iVar13 = param_9[4];
  iVar7 = param_9[2];
  iVar8 = param_9[3];
  if ((3 < param_9[9]) || (param_9[9] < 0)) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E206011__MwsfdCrePrm__illigal_bu_802ba1bc,iVar2,iVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
  uVar1 = iVar7 + 0xf;
  uVar3 = iVar8 + 0xf;
  uVar1 = ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
  iVar4 = uVar1 * 0x10;
  uVar5 = ((int)uVar3 >> 4) + (uint)((int)uVar3 < 0 && (uVar3 & 0xf) != 0);
  uVar3 = iVar4 + 0x1f;
  iVar2 = uVar5 * 0x10;
  uVar1 = ((int)((uVar1 >> 0x1b & 1) + iVar4) >> 1) + 0x1f;
  iVar4 = iVar2 * (((int)uVar3 >> 5) + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * 0x20 +
          ((int)((uVar5 >> 0x1b & 1) + iVar2) >> 1) *
          (((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * 0x20 * 2 + 0x20;
  return iVar6 + iVar11 + iVar12 + iVar4 * 2 + iVar13 * iVar4 + iVar10 + iVar9 + 0x5060;
}



// ==== 802adc9c  zz_02adc9c_ ====

undefined4 zz_02adc9c_(void)

{
  return DAT_804310b8;
}



// ==== 802adcac  FUN_802adcac ====

void FUN_802adcac(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  
  uVar4 = 0x802c0000;
  if (param_9 == 0) {
    DAT_80430fbc = 0;
    DAT_80430fb8 = 0;
  }
  else {
    DAT_80430fb8 = zz_02af50c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               param_9,param_10,0x80430000,0x802c0000,param_13,param_14,param_15,
                               param_16);
    DAT_80430fbc = param_9;
  }
  iVar2 = DAT_80431040;
  if ((param_10 != 0) &&
     (bVar1 = DAT_80431040 < 0xf, *(int *)(&DAT_80431044 + DAT_80431040 * 4) = param_10, bVar1)) {
    DAT_80431040 = iVar2 + 1;
  }
  if (param_10 == -0xfff0e4) {
    pcVar3 = s_SFD_ERROR__08X___Picture_data_si_802ba38c;
    sprintf(&DAT_80430fc0,s_SFD_ERROR__08X___Picture_data_si_802ba38c);
  }
  else {
    if (param_10 < -0xfff0e4) {
      if ((param_10 < -0xfff0e7) && (-0xfff0ea < param_10)) {
        pcVar3 = s_SFD_ERROR__08X___width__height_o_802ba358;
        sprintf(&DAT_80430fc0,s_SFD_ERROR__08X___width__height_o_802ba358);
        goto LAB_802addc8;
      }
    }
    else if ((param_10 < -1) && (-4 < param_10)) {
      pcVar3 = s_DATA_ERROR__08X__802ba344;
      sprintf(&DAT_80430fc0,s_DATA_ERROR__08X__802ba344);
      goto LAB_802addc8;
    }
    pcVar3 = s_SFD_ERROR__08X__802ba3e8;
    sprintf(&DAT_80430fc0,s_SFD_ERROR__08X__802ba3e8);
  }
LAB_802addc8:
  zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80430fc0,pcVar3,
              param_10,uVar4,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802addf4  zz_02addf4_ ====

uint zz_02addf4_(uint param_1)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(param_1);
  DAT_804310e8 = param_1;
  return param_1 & ~-(uVar1 >> 5 & 1);
}



// ==== 802ade14  zz_02ade14_ ====

undefined4 zz_02ade14_(void)

{
  return DAT_804310c0;
}



// ==== 802ade24  zz_02ade24_ ====

undefined4 zz_02ade24_(void)

{
  return DAT_804310bc;
}



// ==== 802ade34  zz_02ade34_ ====

void zz_02ade34_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                float *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  code *pcVar3;
  code *extraout_r4_00;
  undefined *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  undefined *local_28;
  int local_24;
  longlong local_20;
  
  if (param_9 == (float *)0x0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122611_mwPlyInitSfdFx__iprm_is_802ba438,0x802c0000,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    DAT_8043216c = s_MWSFD_GC_Ver_2_62_Build_Feb_6_20_802ba2a8;
    uVar7 = zz_02aa744_();
    param_9[2] = (float)((int)param_9[2] + -2);
    if ((int)param_9[2] < 0) {
      param_9[2] = 0.0;
    }
    if (DAT_80430fb0 == 0) {
      zz_0264414_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_02776b8_();
      zz_0276da4_();
      uVar7 = zz_0277764_();
      uVar6 = extraout_r4;
      iVar1 = zz_02aa9b4_();
      if (iVar1 != 0) {
        DAT_804310e8 = 0xffffff9b;
        zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E2005_mwPlyInitSfdFx__can_t_init_802ba460,uVar6,param_11,param_12,param_13,
                    param_14,param_15,param_16);
      }
      gnt4_memset(&DAT_80431084,0,0x10e8);
      zz_02af670_(0);
      DAT_804310dc = 0;
      if (param_9 == (float *)0x0) {
        DAT_8043108c = 1.4013e-45;
        DAT_80431088 = DAT_802ba434;
        DAT_80431090 = 1.4013e-45;
        DAT_80431094 = 0.0;
      }
      else {
        DAT_80431088 = *param_9;
        DAT_8043108c = param_9[1];
        DAT_80431090 = param_9[2];
        DAT_80431094 = param_9[3];
      }
      uVar6 = 1;
      DAT_804310bc = 1;
      dVar8 = (double)DAT_802ba490;
      pcVar3 = (code *)0x2968;
      DAT_804310c0 = 1;
      DAT_80432174 = 0;
      local_28 = PTR_PTR_802ba338;
      local_24 = (int)(DAT_802ba488 + (double)(float)(dVar8 * (double)*param_9));
      local_20 = (longlong)local_24;
      puVar4 = PTR_PTR_802ba338;
      dVar9 = DAT_802ba488;
      uVar2 = zz_029ae04_(s_1_842_802ba3f8,0x2968);
      if (uVar2 == 1) {
        iVar1 = zz_029ace4_(&local_28);
        if (iVar1 == 0) {
          pcVar3 = FUN_802adcac;
          puVar4 = (undefined *)0x0;
          iVar1 = zz_029ab20_(0,FUN_802adcac,0);
          if (iVar1 == 0) {
            iVar1 = 0;
          }
          else {
            iVar1 = -0x12f;
            DAT_804310e8 = 0xfffffed1;
          }
        }
        else {
          iVar1 = -0x12d;
          DAT_804310e8 = 0xfffffed3;
        }
      }
      else {
        dVar8 = (double)zz_02aa530_(dVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                                    s_E011081_mwPlySfdInit__Not_compat_802ba400,pcVar3,puVar4,uVar6,
                                    param_13,param_14,param_15,param_16);
        iVar1 = -1;
        pcVar3 = extraout_r4_00;
      }
      if (iVar1 != 0) {
        zz_02aa530_(dVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_ERR20010421A___mwPlyInitSfdFx_802ba494,pcVar3,puVar4,uVar6,param_13,param_14,
                    param_15,param_16);
      }
      DAT_80430fb4 = 1;
      local_20 = (longlong)(int)*param_9;
      zz_02af4d8_(0,0x1b,(int)*param_9);
      zz_02af4d8_(0,7,1);
      zz_02764b4_();
      zz_0275b24_(-0x7fd51f28,0);
      uVar7 = zz_02ab488_();
      uVar5 = 0;
      uVar7 = zz_02aa6fc_(uVar7,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,2,-0x7fd503b4,
                          0,uVar6,param_13,param_14,param_15,param_16);
      uVar7 = zz_02aa694_(uVar7,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd504a8,0,
                          uVar5,uVar6,param_13,param_14,param_15,param_16);
      zz_02aa6c8_(uVar7,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fd50508,0,uVar5,
                  uVar6,param_13,param_14,param_15,param_16);
    }
    DAT_80430fb0 = DAT_80430fb0 + 1;
  }
  return;
}



// ==== 802ae0d8  FUN_802ae0d8 ====

void FUN_802ae0d8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,char *param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802ae100  GetOneTimerLeadGroundContactAnims(void) ====

undefined * GetOneTimerLeadGroundContactAnims_void_(void)

{
  return &DAT_80431084;
}



// ==== 802ae10c  zz_02ae10c_ ====

void zz_02ae10c_(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x40);
  piVar2 = *(int **)(param_1 + 0x128);
  if (((*(int *)(param_1 + 0x44) != 0) &&
      (iVar1 = zz_02aa788_(*(int *)(param_1 + 0x44)), iVar1 == 3)) &&
     (iVar1 = (**(code **)(*piVar2 + 0x24))(piVar2,1), iVar1 < 4)) {
    zz_02a1104_(iVar3);
  }
  return;
}



// ==== 802ae184  zz_02ae184_ ====

void zz_02ae184_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  zz_02af490_(DAT_802ba508,DAT_802ba500,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              (int)(DAT_802ba500 *
                   ((double)CONCAT44(0x43300000,*(uint *)(param_9 + 0x134) ^ 0x80000000) -
                   DAT_802ba508)),*(uint *)(param_9 + 0x134),0x802c0000,0x802c0000,in_r8,in_r9,
              in_r10);
  return;
}



// ==== 802ae1e0  zz_02ae1e0_ ====

void zz_02ae1e0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  uint *puVar7;
  undefined8 uVar8;
  int local_28;
  uint local_24;
  int local_20 [5];
  
  iVar3 = param_10;
  iVar4 = param_11;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera((int)param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122638__mwPlyStartAfs__handle_i_802ba510,iVar3,iVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
  else {
    uVar2 = zz_02aefe4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9
                        ,iVar3,iVar4,param_12,param_13,param_14,param_15,param_16);
    uVar8 = (**(code **)(*param_9 + 0x3c))(param_9,uVar2);
    iVar4 = param_9[0x44];
    piVar5 = local_20;
    piVar6 = &local_28;
    puVar7 = &local_24;
    iVar3 = zz_0272048_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                        param_11,iVar4,piVar5,piVar6,puVar7,param_15,param_16);
    if (iVar3 == 0) {
      param_9[0x47] = local_20[0];
      param_9[0x48] = local_28;
      param_9[0x49] = local_24;
      param_9[0x46] = 1;
    }
    else {
      zz_02aa530_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E211151__ADXF_GetFnameRangeEx___f_802ba4b8,param_11,iVar4,piVar5,piVar6,puVar7,
                  param_15,param_16);
    }
    param_9[0x46] = 1;
  }
  return;
}



// ==== 802ae2c0  FUN_802ae2c0 ====

void FUN_802ae2c0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  int local_18 [2];
  
  piVar3 = (int *)0x802c0000;
  iVar4 = param_10;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122604_mwSfdPause__handle_is_i_802ba53c,iVar4,piVar3,param_12,param_13,param_14,
                param_15,param_16);
  }
  else {
    iVar4 = *(int *)(param_9 + 0x40);
    if ((*(char *)(param_9 + 0x72) != '\0') || (param_10 != 0)) {
      iVar1 = zz_02ade14_();
      if ((iVar1 == 1) && (*(int *)(param_9 + 0xc) == 1)) {
        piVar3 = local_18;
        iVar1 = zz_02a3948_(iVar4,6,piVar3);
        if (iVar1 == 0) {
          if (local_18[0] == 1) {
            param_1 = zz_02af5bc_(param_9);
          }
        }
        else {
          param_1 = zz_02af5bc_(param_9);
        }
      }
      iVar4 = zz_02a0dcc_(iVar4,param_10);
      if (iVar4 != 0) {
        zz_02addf4_(0xfffffeca);
        puVar2 = &DAT_802ba58c;
        if (param_10 == 1) {
          puVar2 = &DAT_802ba588;
        }
        zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    s_E2007_mwSfdPause__can_t_pause____802ba564,puVar2,piVar3,param_12,param_13,
                    param_14,param_15,param_16);
      }
      *(char *)(param_9 + 0x72) = (char)param_10;
    }
  }
  return;
}



// ==== 802ae3cc  FUN_802ae3cc ====

void FUN_802ae3cc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined4 extraout_r4_00;
  undefined8 uVar3;
  
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122602_mwSfdStop__handle_is_in_802ba590,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    iVar1 = *(int *)(param_9 + 0x40);
    if (iVar1 != 0) {
      param_1 = zz_02af5bc_(param_9);
      *(undefined4 *)(param_9 + 8) = 0;
      uVar2 = extraout_r4;
      iVar1 = zz_02a143c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1);
      if (iVar1 != 0) {
        zz_02addf4_(0xfffffecc);
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E2003_mwSfdStop_can_t_stop_SFD_802ba5b8,uVar2,param_11,param_12,
                              param_13,param_14,param_15,param_16);
      }
      if (*(int *)(param_9 + 0x44) != 0) {
        param_1 = zz_02aa7a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 0x44));
      }
    }
    uVar3 = zz_02aa07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x74) = 0;
    zz_0275d68_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x4c),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                ,param_16);
  }
  return;
}



// ==== 802ae48c  zz_02ae48c_ ====

void zz_02ae48c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = *(int *)(param_9 + 0x40);
  if (iVar2 != 0) {
    uVar3 = zz_02af5bc_(param_9);
    *(undefined4 *)(param_9 + 8) = 0;
    uVar1 = extraout_r4;
    iVar2 = zz_02a143c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2);
    if (iVar2 != 0) {
      zz_02addf4_(0xfffffecc);
      uVar3 = zz_02aa530_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E2003_mwSfdStop_can_t_stop_SFD_802ba5b8,uVar1,param_11,param_12,param_13
                          ,param_14,param_15,param_16);
    }
    if (*(int *)(param_9 + 0x44) != 0) {
      zz_02aa7a8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x44));
    }
  }
  return;
}



// ==== 802ae50c  zz_02ae50c_ ====

void zz_02ae50c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int extraout_r4;
  int extraout_r4_00;
  int extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 uVar4;
  int extraout_r4_03;
  int extraout_r4_04;
  int extraout_r4_05;
  int extraout_r4_06;
  undefined *puVar5;
  int extraout_r4_07;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  int local_18 [2];
  
  piVar6 = (int *)0x802c0000;
  iVar3 = param_10;
  iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar2 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122609_mwSfdStartSj__handle_is_802ba5d8,iVar3,piVar6,param_12,param_13,param_14,
                param_15,param_16);
    return;
  }
  iVar2 = *(int *)(param_9 + 0x40);
  if (iVar2 != 0) {
    param_1 = zz_02af5bc_(param_9);
    *(undefined4 *)(param_9 + 8) = 0;
    iVar3 = extraout_r4;
    iVar2 = zz_02a143c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2);
    if (iVar2 != 0) {
      zz_02addf4_(0xfffffecc);
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E2003_mwSfdStop_can_t_stop_SFD_802ba5b8,iVar3,piVar6,param_12,param_13
                            ,param_14,param_15,param_16);
      iVar3 = extraout_r4_00;
    }
    if (*(int *)(param_9 + 0x44) != 0) {
      param_1 = zz_02aa7a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x44));
      iVar3 = extraout_r4_01;
    }
  }
  *(int *)(param_9 + 0x128) = param_10;
  *(undefined4 *)(param_9 + 0x13c) = 2;
  *(undefined4 *)(param_9 + 0x140) = 0;
  *(undefined4 *)(param_9 + 0x144) = 0;
  *(undefined4 *)(param_9 + 0x148) = 0;
  GetOneTimerLeadGroundContactAnims_void_();
  if (*(int *)(param_9 + 0x40) != 0) {
    iVar2 = zz_02ac91c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        iVar3,piVar6,param_12,param_13,param_14,param_15,param_16);
    if (iVar2 != 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E0203263__mw_sfd_start_ex__RESET_802ba604,iVar3,piVar6,param_12,
                            param_13,param_14,param_15,param_16);
      goto LAB_802ae784;
    }
    zz_02a9930_(param_9);
    uVar8 = zz_02aae8c_(param_9);
    uVar4 = extraout_r4_02;
    iVar3 = zz_02aaee0_(param_9);
    if (iVar3 != 0) {
      param_1 = zz_02aa530_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E201213_mw_sfd_start_ex__can_t_s_802ba630,uVar4,piVar6,param_12,
                            param_13,param_14,param_15,param_16);
      goto LAB_802ae784;
    }
    param_1 = zz_02aaec4_(param_9);
    iVar3 = extraout_r4_03;
  }
  *(undefined4 *)(param_9 + 0x7c) = 0;
  *(undefined4 *)(param_9 + 0x80) = 0;
  iVar2 = zz_02a0bf8_(*(int *)(param_9 + 0x40));
  if (iVar2 != 0) {
    zz_02addf4_(0xfffffec9);
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E20010703F_mwPlySfdStandby__802ba65c,iVar3,piVar6,param_12,param_13,
                          param_14,param_15,param_16);
    iVar3 = extraout_r4_04;
  }
  iVar2 = zz_02a1718_(*(int *)(param_9 + 0x40));
  if (iVar2 != 0) {
    zz_02addf4_(0xfffffecd);
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E20010703G_mwPlySfdStart__802ba67c,iVar3,piVar6,param_12,param_13,
                          param_14,param_15,param_16);
    iVar3 = extraout_r4_05;
  }
  cVar1 = *(char *)(param_9 + 0x72);
  iVar7 = (int)cVar1;
  iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar2 == 0) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122604_mwSfdPause__handle_is_i_802ba53c,iVar3,piVar6,param_12,param_13
                          ,param_14,param_15,param_16);
    iVar3 = extraout_r4_06;
  }
  else {
    iVar2 = *(int *)(param_9 + 0x40);
    if ((*(char *)(param_9 + 0x72) != '\0') || (iVar7 != 0)) {
      iVar3 = zz_02ade14_();
      if ((iVar3 == 1) && (*(int *)(param_9 + 0xc) == 1)) {
        piVar6 = local_18;
        iVar3 = zz_02a3948_(iVar2,6,piVar6);
        if (iVar3 == 0) {
          if (local_18[0] == 1) {
            param_1 = zz_02af5bc_(param_9);
          }
        }
        else {
          param_1 = zz_02af5bc_(param_9);
        }
      }
      iVar3 = iVar7;
      iVar2 = zz_02a0dcc_(iVar2,iVar7);
      if (iVar2 != 0) {
        zz_02addf4_(0xfffffeca);
        puVar5 = &DAT_802ba58c;
        if (iVar7 == 1) {
          puVar5 = &DAT_802ba588;
        }
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E2007_mwSfdPause__can_t_pause____802ba564,puVar5,piVar6,param_12,
                              param_13,param_14,param_15,param_16);
        iVar3 = extraout_r4_07;
      }
      *(char *)(param_9 + 0x72) = cVar1;
    }
  }
  if ((*(char *)(param_9 + 0x70) == '\x01') &&
     (iVar2 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar2 != 0)) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E99072103_mwPlyStartXX__can_t_li_802ba698,iVar3,piVar6,param_12,param_13
                          ,param_14,param_15,param_16);
  }
  *(undefined4 *)(param_9 + 0x84) = 0;
  *(undefined1 *)(param_9 + 0x71) = 0;
  *(undefined4 *)(param_9 + 8) = 1;
LAB_802ae784:
  zz_02ad96c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 802ae7ac  FUN_802ae7ac ====

void FUN_802ae7ac(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,int *param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_r4;
  int *piVar6;
  undefined4 extraout_r4_00;
  int *extraout_r4_01;
  int *extraout_r4_02;
  int *extraout_r4_03;
  int *extraout_r4_04;
  undefined *puVar7;
  int *extraout_r4_05;
  int *piVar8;
  undefined4 uVar9;
  int *piVar10;
  undefined8 uVar11;
  int local_28 [5];
  
  uVar9 = 0x802c0000;
  uVar5 = param_10;
  piVar8 = param_11;
  iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar2 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122610_mwSfdStartMem__handle_i_802ba6c4,uVar5,piVar8,uVar9,param_13,param_14,
                param_15,param_16);
    return;
  }
  iVar2 = *(int *)(param_9 + 0x40);
  if (iVar2 != 0) {
    uVar11 = zz_02af5bc_(param_9);
    *(undefined4 *)(param_9 + 8) = 0;
    uVar5 = extraout_r4;
    iVar2 = zz_02a143c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2);
    if (iVar2 != 0) {
      zz_02addf4_(0xfffffecc);
      uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_E2003_mwSfdStop_can_t_stop_SFD_802ba5b8,uVar5,piVar8,uVar9,param_13,
                           param_14,param_15,param_16);
    }
    if (*(int *)(param_9 + 0x44) != 0) {
      zz_02aa7a8_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0x44));
    }
  }
  uVar11 = (**(code **)(**(int **)(param_9 + 0x14c) + 0xc))();
  piVar6 = param_11;
  puVar3 = zz_0276c34_(param_10,param_11);
  *(undefined4 **)(param_9 + 0x14c) = puVar3;
  *(undefined4 *)(param_9 + 0x128) = *(undefined4 *)(param_9 + 0x14c);
  *(undefined4 *)(param_9 + 0x150) = param_10;
  *(int **)(param_9 + 0x154) = param_11;
  GetOneTimerLeadGroundContactAnims_void_();
  if (*(int *)(param_9 + 0x40) != 0) {
    iVar2 = zz_02ac91c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        piVar6,piVar8,uVar9,param_13,param_14,param_15,param_16);
    if (iVar2 != 0) {
      uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_E0203263__mw_sfd_start_ex__RESET_802ba604,piVar6,piVar8,uVar9,param_13,
                           param_14,param_15,param_16);
      goto LAB_802aea34;
    }
    zz_02a9930_(param_9);
    uVar11 = zz_02aae8c_(param_9);
    uVar5 = extraout_r4_00;
    iVar2 = zz_02aaee0_(param_9);
    if (iVar2 != 0) {
      uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_E201213_mw_sfd_start_ex__can_t_s_802ba630,uVar5,piVar8,uVar9,param_13,
                           param_14,param_15,param_16);
      goto LAB_802aea34;
    }
    uVar11 = zz_02aaec4_(param_9);
    piVar6 = extraout_r4_01;
  }
  *(undefined4 *)(param_9 + 0x7c) = 0;
  *(undefined4 *)(param_9 + 0x80) = 0;
  iVar2 = zz_02a0bf8_(*(int *)(param_9 + 0x40));
  if (iVar2 != 0) {
    zz_02addf4_(0xfffffec9);
    uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_E20010703F_mwPlySfdStandby__802ba65c,piVar6,piVar8,uVar9,param_13,
                         param_14,param_15,param_16);
    piVar6 = extraout_r4_02;
  }
  iVar2 = zz_02a1718_(*(int *)(param_9 + 0x40));
  if (iVar2 != 0) {
    zz_02addf4_(0xfffffecd);
    uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_E20010703G_mwPlySfdStart__802ba67c,piVar6,piVar8,uVar9,param_13,param_14,
                         param_15,param_16);
    piVar6 = extraout_r4_03;
  }
  cVar1 = *(char *)(param_9 + 0x72);
  piVar10 = (int *)(int)cVar1;
  iVar2 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar2 == 0) {
    uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_E1122604_mwSfdPause__handle_is_i_802ba53c,piVar6,piVar8,uVar9,param_13,
                         param_14,param_15,param_16);
    piVar6 = extraout_r4_04;
  }
  else {
    iVar2 = *(int *)(param_9 + 0x40);
    if ((*(char *)(param_9 + 0x72) != '\0') || (piVar10 != (int *)0x0)) {
      iVar4 = zz_02ade14_();
      if ((iVar4 == 1) && (*(int *)(param_9 + 0xc) == 1)) {
        piVar8 = local_28;
        iVar4 = zz_02a3948_(iVar2,6,piVar8);
        if (iVar4 == 0) {
          if (local_28[0] == 1) {
            uVar11 = zz_02af5bc_(param_9);
          }
        }
        else {
          uVar11 = zz_02af5bc_(param_9);
        }
      }
      piVar6 = piVar10;
      iVar2 = zz_02a0dcc_(iVar2,(int)piVar10);
      if (iVar2 != 0) {
        zz_02addf4_(0xfffffeca);
        puVar7 = &DAT_802ba58c;
        if (piVar10 == (int *)0x1) {
          puVar7 = &DAT_802ba588;
        }
        uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_E2007_mwSfdPause__can_t_pause____802ba564,puVar7,piVar8,uVar9,
                             param_13,param_14,param_15,param_16);
        piVar6 = extraout_r4_05;
      }
      *(char *)(param_9 + 0x72) = cVar1;
    }
  }
  if ((*(char *)(param_9 + 0x70) == '\x01') &&
     (iVar2 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar2 != 0)) {
    uVar11 = zz_02aa530_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         s_E99072103_mwPlyStartXX__can_t_li_802ba698,piVar6,piVar8,uVar9,param_13,
                         param_14,param_15,param_16);
  }
  *(undefined4 *)(param_9 + 0x84) = 0;
  *(undefined1 *)(param_9 + 0x71) = 0;
  *(undefined4 *)(param_9 + 8) = 1;
LAB_802aea34:
  zz_02ad96c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 802aea50  zz_02aea50_ ====

void zz_02aea50_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,char *param_10,int *param_11,int param_12,undefined4 param_13,
                undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  char *extraout_r4;
  char *pcVar4;
  char *extraout_r4_00;
  char *extraout_r4_01;
  char *extraout_r4_02;
  undefined4 extraout_r4_03;
  char *extraout_r4_04;
  char *extraout_r4_05;
  char *extraout_r4_06;
  char *extraout_r4_07;
  char *extraout_r4_08;
  undefined *puVar5;
  char *extraout_r4_09;
  char *extraout_r4_10;
  int *piVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  char *pcVar10;
  int iVar11;
  undefined8 uVar12;
  int local_28 [3];
  
  uVar9 = 0x802c0000;
  *(undefined4 *)(param_9 + 0x128) = *(undefined4 *)(param_9 + 300);
  iVar11 = *(int *)(param_9 + 0x40);
  pcVar4 = param_10;
  piVar6 = param_11;
  iVar7 = param_12;
  if (iVar11 != 0) {
    param_1 = zz_02af5bc_(param_9);
    *(undefined4 *)(param_9 + 8) = 0;
    pcVar4 = extraout_r4;
    iVar11 = zz_02a143c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar11);
    if (iVar11 != 0) {
      zz_02addf4_(0xfffffecc);
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E2003_mwSfdStop_can_t_stop_SFD_802ba5b8,pcVar4,piVar6,iVar7,uVar9,
                            param_14,param_15,param_16);
      pcVar4 = extraout_r4_00;
    }
    if (*(int *)(param_9 + 0x44) != 0) {
      param_1 = zz_02aa7a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int *)(param_9 + 0x44));
      pcVar4 = extraout_r4_01;
    }
  }
  GetOneTimerLeadGroundContactAnims_void_();
  if (*(int *)(param_9 + 0x40) != 0) {
    iVar11 = zz_02ac91c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         pcVar4,piVar6,iVar7,uVar9,param_14,param_15,param_16);
    if (iVar11 != 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E0203263__mw_sfd_start_ex__RESET_802ba604,pcVar4,piVar6,iVar7,uVar9,
                            param_14,param_15,param_16);
      pcVar4 = extraout_r4_02;
      goto LAB_802aec90;
    }
    zz_02a9930_(param_9);
    uVar12 = zz_02aae8c_(param_9);
    uVar8 = extraout_r4_03;
    iVar11 = zz_02aaee0_(param_9);
    if (iVar11 != 0) {
      param_1 = zz_02aa530_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E201213_mw_sfd_start_ex__can_t_s_802ba630,uVar8,piVar6,iVar7,uVar9,
                            param_14,param_15,param_16);
      pcVar4 = extraout_r4_04;
      goto LAB_802aec90;
    }
    param_1 = zz_02aaec4_(param_9);
    pcVar4 = extraout_r4_05;
  }
  *(undefined4 *)(param_9 + 0x7c) = 0;
  *(undefined4 *)(param_9 + 0x80) = 0;
  iVar11 = zz_02a0bf8_(*(int *)(param_9 + 0x40));
  if (iVar11 != 0) {
    zz_02addf4_(0xfffffec9);
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E20010703F_mwPlySfdStandby__802ba65c,pcVar4,piVar6,iVar7,uVar9,param_14,
                          param_15,param_16);
    pcVar4 = extraout_r4_06;
  }
  iVar11 = zz_02a1718_(*(int *)(param_9 + 0x40));
  if (iVar11 != 0) {
    zz_02addf4_(0xfffffecd);
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E20010703G_mwPlySfdStart__802ba67c,pcVar4,piVar6,iVar7,uVar9,param_14,
                          param_15,param_16);
    pcVar4 = extraout_r4_07;
  }
  cVar1 = *(char *)(param_9 + 0x72);
  pcVar10 = (char *)(int)cVar1;
  iVar11 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar11 == 0) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E1122604_mwSfdPause__handle_is_i_802ba53c,pcVar4,piVar6,iVar7,uVar9,
                          param_14,param_15,param_16);
    pcVar4 = extraout_r4_08;
  }
  else {
    iVar11 = *(int *)(param_9 + 0x40);
    if ((*(char *)(param_9 + 0x72) != '\0') || (pcVar10 != (char *)0x0)) {
      iVar2 = zz_02ade14_();
      if ((iVar2 == 1) && (*(int *)(param_9 + 0xc) == 1)) {
        piVar6 = local_28;
        iVar2 = zz_02a3948_(iVar11,6,piVar6);
        if (iVar2 == 0) {
          if (local_28[0] == 1) {
            param_1 = zz_02af5bc_(param_9);
          }
        }
        else {
          param_1 = zz_02af5bc_(param_9);
        }
      }
      pcVar4 = pcVar10;
      iVar11 = zz_02a0dcc_(iVar11,(int)pcVar10);
      if (iVar11 != 0) {
        zz_02addf4_(0xfffffeca);
        puVar5 = &DAT_802ba58c;
        if (pcVar10 == (char *)0x1) {
          puVar5 = &DAT_802ba588;
        }
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E2007_mwSfdPause__can_t_pause____802ba564,puVar5,piVar6,iVar7,uVar9,
                              param_14,param_15,param_16);
        pcVar4 = extraout_r4_09;
      }
      *(char *)(param_9 + 0x72) = cVar1;
    }
  }
  if ((*(char *)(param_9 + 0x70) == '\x01') &&
     (iVar11 = zz_029a06c_(*(int *)(param_9 + 0x40)), iVar11 != 0)) {
    param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          s_E99072103_mwPlyStartXX__can_t_li_802ba698,pcVar4,piVar6,iVar7,uVar9,
                          param_14,param_15,param_16);
    pcVar4 = extraout_r4_10;
  }
  *(undefined4 *)(param_9 + 0x84) = 0;
  *(undefined1 *)(param_9 + 0x71) = 0;
  *(undefined4 *)(param_9 + 8) = 1;
LAB_802aec90:
  sVar3 = strlen(param_10);
  if (*(int *)(param_9 + 0x114) < (int)sVar3) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E211121__filename_is_longer__802ba4e0,pcVar4,piVar6,iVar7,uVar9,param_14,param_15,
                param_16);
    param_1 = zz_0238cbc_(*(int *)(param_9 + 0x110),(int)param_10,*(int *)(param_9 + 0x114));
  }
  else {
    strcpy(*(char **)(param_9 + 0x110),param_10);
  }
  *(undefined4 *)(param_9 + 0x11c) = 0;
  uVar8 = 0xfffff;
  *(undefined4 *)(param_9 + 0x120) = 0;
  *(undefined4 *)(param_9 + 0x124) = 0xfffff;
  *(undefined4 *)(param_9 + 0x118) = 1;
  uVar12 = zz_02aab04_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       (int)param_11,param_12,0xfffff,uVar9,param_14,param_15,param_16);
  zz_02aa9f8_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_11,
              param_12,uVar8,uVar9,param_14,param_15,param_16);
  return;
}



// ==== 802aed24  FUN_802aed24 ====

void FUN_802aed24(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,char *param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = param_10;
  iVar1 = nlDLRingGetStart<11cBaseCamera>_cBaseCamera(param_9);
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122601__mwPlyStartFname__handl_802ba6f0,pcVar2,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else if (param_10 == (char *)0x0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E10915C__mwPlyStartFname__fname_i_802ba720,pcVar2,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    zz_02aea50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                (int *)0x0,-1,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 802aeda8  zz_02aeda8_ ====

void zz_02aeda8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *extraout_r4;
  undefined4 *extraout_r4_00;
  undefined4 *extraout_r4_01;
  undefined4 uStack_118;
  int local_114;
  int local_108;
  undefined4 auStack_d8 [4];
  int local_c8;
  undefined4 uStack_98;
  int local_94;
  int local_88;
  undefined4 auStack_58 [7];
  int local_3c;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E202191__mwPlyGetPlyInf__handle_i_802ba838,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 4);
    }
    if (iVar1 == 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E1122640__mwPlyGetSfdHn__handle_i_802ba798,param_10,param_11,param_12,
                            param_13,param_14,param_15,param_16);
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 0x40);
    }
    puVar3 = auStack_58;
    zz_02a3860_(iVar1,puVar3);
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 4);
    }
    if (iVar1 == 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E202232__mwPlyGetNumDropFrm__han_802ba864,puVar3,param_11,param_12,
                            param_13,param_14,param_15,param_16);
      iVar1 = 0;
      puVar3 = extraout_r4;
    }
    else {
      if (param_9 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(param_9 + 4);
      }
      if (iVar1 == 0) {
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E1122619__mwPlyGetNumSkipDec__ha_802ba894,puVar3,param_11,param_12,
                              param_13,param_14,param_15,param_16);
        iVar1 = 0;
        puVar3 = extraout_r4_00;
      }
      else {
        if (param_9 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(param_9 + 4);
        }
        if (iVar1 == 0) {
          param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                s_E1122640__mwPlyGetSfdHn__handle_i_802ba798,puVar3,param_11,
                                param_12,param_13,param_14,param_15,param_16);
          iVar1 = 0;
        }
        else {
          iVar1 = *(int *)(param_9 + 0x40);
        }
        puVar3 = &uStack_118;
        zz_02a3860_(iVar1,puVar3);
        iVar1 = local_114 - local_108;
      }
      iVar2 = zz_02a97e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          puVar3,param_11,param_12,param_13,param_14,param_15,param_16);
      iVar1 = iVar1 + iVar2;
    }
    *param_10 = iVar1;
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 4);
    }
    if (iVar1 == 0) {
      param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            s_E1122619__mwPlyGetNumSkipDec__ha_802ba894,puVar3,param_11,param_12,
                            param_13,param_14,param_15,param_16);
      local_94 = 0;
      puVar3 = extraout_r4_01;
    }
    else {
      if (param_9 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(param_9 + 4);
      }
      if (iVar1 == 0) {
        param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_E1122640__mwPlyGetSfdHn__handle_i_802ba798,puVar3,param_11,param_12,
                              param_13,param_14,param_15,param_16);
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(param_9 + 0x40);
      }
      puVar3 = &uStack_98;
      zz_02a3860_(iVar1,puVar3);
      local_94 = local_94 - local_88;
    }
    param_10[1] = local_94;
    iVar1 = zz_02a97e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        puVar3,param_11,param_12,param_13,param_14,param_15,param_16);
    param_10[2] = iVar1;
    if (param_9 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_9 + 4);
    }
    if (iVar1 == 0) {
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E1122623__mwPlyGetNumSkipEmptyB__802ba8c8,puVar3,param_11,param_12,param_13,
                  param_14,param_15,param_16);
      local_c8 = 0;
    }
    else {
      zz_02a3860_(*(int *)(param_9 + 0x40),auStack_d8);
    }
    param_10[3] = local_c8;
    param_10[4] = local_3c;
  }
  return;
}



// ==== 802aefe4  zz_02aefe4_ ====

undefined4
zz_02aefe4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122624__mwPlyGetInputSj__handl_802ba8fc,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_9 + 300);
  }
  return uVar2;
}



// ==== 802af038  FUN_802af038 ====

undefined4
FUN_802af038(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122608_mwSfdGetOutPan__handle_i_802ba960,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = zz_02a9fe4_(param_9,param_10);
  }
  return uVar2;
}



// ==== 802af08c  FUN_802af08c ====

void FUN_802af08c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122607_mwSfdSetOutPan__handle_i_802ba98c,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    zz_02aa008_(param_9,param_10,param_11);
  }
  return;
}



// ==== 802af0dc  FUN_802af0dc ====

undefined4
FUN_802af0dc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122606_mwSfdGetOutVol__handle_i_802ba9b8,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = zz_02aa02c_(param_9);
  }
  return uVar2;
}



// ==== 802af130  FUN_802af130 ====

void FUN_802af130(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122605_mwSfdSetOutVol__handle_i_802ba9e4,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    zz_02aa050_(param_9,param_10);
  }
  return;
}



// ==== 802af180  FUN_802af180 ====

void FUN_802af180(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int *param_10,uint *param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122603_mwSfdGetTime__handle_is_802baa10,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    *param_10 = 0;
    *param_11 = 1;
  }
  else {
    piVar2 = param_10;
    puVar3 = param_11;
    iVar1 = zz_02a4ac4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x40),param_10,param_11);
    if (iVar1 != 0) {
      zz_02addf4_(0xfffffecb);
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E2006_mwSfdGetTime__can_t_get_ti_802baa3c,piVar2,puVar3,param_12,param_13,
                  param_14,param_15,param_16);
      *param_10 = 0;
      *param_11 = 1;
    }
    if (*param_10 < 0) {
      *param_10 = 0;
      *param_11 = 1;
    }
  }
  return;
}



// ==== 802af250  zz_02af250_ ====

undefined4
zz_02af250_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 local_48 [18];
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122620__mwPlyGetNumTotalDec__h_802baa60,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    local_48[0] = 0;
  }
  else {
    zz_02a3860_(*(int *)(param_9 + 0x40),local_48);
  }
  return local_48[0];
}



// ==== 802af2b0  zz_02af2b0_ ====

int zz_02af2b0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int local_8 [2];
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122621__mwPlyGetNumDecPool__ha_802baa94,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    local_8[0] = 0;
  }
  else {
    piVar2 = local_8;
    iVar1 = zz_02a049c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x40),piVar2);
    if (iVar1 != 0) {
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E1121601_mwPlyGetNumDecPool_802baac8,piVar2,param_11,param_12,param_13,param_14,
                  param_15,param_16);
    }
  }
  return local_8[0];
}



// ==== 802af328  zz_02af328_ ====

undefined4
zz_02af328_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int local_8 [2];
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E2010802__mwPlyGetSyncMode__hand_802baae4,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0xffffffff;
  }
  else {
    piVar3 = local_8;
    uVar2 = 0xf;
    zz_02a3948_(*(int *)(param_9 + 0x40),0xf,piVar3);
    if (local_8[0] == 1) {
      uVar2 = 1;
    }
    else {
      if (local_8[0] < 1) {
        if (-1 < local_8[0]) {
          return 0;
        }
      }
      else if (local_8[0] < 3) {
        return 2;
      }
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E2010803__mwPlyGetSyncMode__mode_802bab14,uVar2,piVar3,param_12,param_13,
                  param_14,param_15,param_16);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}



// ==== 802af3dc  FUN_802af3dc ====

int FUN_802af3dc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02addf4_(0xfffffff4);
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_W2004_mwSfdGetStat__handle_is_in_802bab74,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 8);
    if (iVar1 == 2) {
      iVar2 = zz_02a3c68_(*(int *)(param_9 + 0x40));
      if ((iVar2 == 4) || (iVar2 == 6)) {
        iVar1 = 2;
      }
      else {
        iVar1 = 1;
        if (iVar2 < 0) {
          iVar1 = 4;
        }
      }
    }
  }
  return iVar1;
}



// ==== 802af478  nlDLRingGetStart<11cBaseCamera>(cBaseCamera ====

undefined4 nlDLRingGetStart<11cBaseCamera>_cBaseCamera(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 4);
}



// ==== 802af490  zz_02af490_ ====

void zz_02af490_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_02aa8d0_(*(int *)(param_9 + 0x44),param_10,param_11);
  cCharacter__UpdateBlinking_float_
            (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,param_11
             ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802af4d8  zz_02af4d8_ ====

void zz_02af4d8_(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x40);
  }
  zz_02a3a84_(iVar1,param_2,param_3);
  return;
}



// ==== 802af50c  zz_02af50c_ ====

undefined4
zz_02af50c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122640__mwPlyGetSfdHn__handle_i_802ba798,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_9 + 0x40);
  }
  return uVar2;
}



// ==== 802af560  zz_02af560_ ====

void zz_02af560_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (param_9 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_9 + 4);
  }
  if (iVar1 == 0) {
    zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                s_E1122617_mwPlySetAudioSw__handle_802bad40,param_10,param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  else {
    zz_02a3a84_(*(int *)(param_9 + 0x40),6,param_10);
  }
  return;
}



// ==== 802af5bc  zz_02af5bc_ ====

void zz_02af5bc_(int param_1)

{
  undefined *puVar1;
  int iVar2;
  
  zz_02aa078_();
  puVar1 = GetOneTimerLeadGroundContactAnims_void_();
  *(undefined4 *)(param_1 + 0x5c) = 1;
  *(undefined4 *)(puVar1 + 0x24) = 1;
  zz_02aa50c_();
  puVar1 = GetOneTimerLeadGroundContactAnims_void_();
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(puVar1 + 0x24) = 0;
  zz_02aa074_();
  if (*(int *)(param_1 + 0x60) == 1) {
    iVar2 = 0;
    do {
      puVar1 = GetOneTimerLeadGroundContactAnims_void_();
      *(undefined4 *)(param_1 + 0x5c) = 1;
      *(undefined4 *)(puVar1 + 0x24) = 1;
      zz_0271244_();
      puVar1 = GetOneTimerLeadGroundContactAnims_void_();
      *(undefined4 *)(param_1 + 0x5c) = 0;
      *(undefined4 *)(puVar1 + 0x24) = 0;
      if (*(int *)(param_1 + 0x60) == 0) {
        return;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 10);
  }
  return;
}



// ==== 802af660  zz_02af660_ ====

void zz_02af660_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 100) = param_2;
  return;
}



// ==== 802af668  zz_02af668_ ====

void zz_02af668_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x60) = param_2;
  return;
}



// ==== 802af670  zz_02af670_ ====

void zz_02af670_(undefined4 param_1)

{
  undefined *puVar1;
  
  puVar1 = GetOneTimerLeadGroundContactAnims_void_();
  *(undefined4 *)(puVar1 + 0x54) = param_1;
  return;
}



// ==== 802af6a0  zz_02af6a0_ ====

uint zz_02af6a0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar5;
  int iVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 extraout_f1_00;
  
  uVar5 = 1;
  iVar6 = *(int *)(param_9 + 0x40);
  *(undefined4 *)(param_9 + 0x60) = 1;
  if (*(int *)(param_9 + 4) == 1) {
    uVar4 = 0x80430000;
    DAT_80432178 = param_9;
    *(undefined4 *)(param_9 + 100) = 1;
    zz_02a2c58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6);
    *(undefined4 *)(param_9 + 100) = 0;
    if (*(int *)(param_9 + 8) == 0) {
      *(undefined4 *)(param_9 + 0x68) = 0;
    }
    else {
      *(undefined4 *)(param_9 + 0x68) = 1;
      iVar1 = *(int *)(param_9 + 8);
      if (iVar1 == 2) {
        iVar1 = *(int *)(param_9 + 0x40);
        if ((*(char *)(param_9 + 0x71) == '\x01') &&
           (iVar3 = zz_0275c78_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(int *)(param_9 + 0x4c),uVar4,uVar5,param_12,param_13,param_14,
                                param_15,param_16), iVar3 == 0)) {
          iVar3 = zz_02a1104_(iVar1);
          if (iVar3 != 0) {
            param_1 = zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  s_E99072102_mwlSfdExecDecSvrPlayin_802bad9c,uVar4,uVar5,param_12,
                                  param_13,param_14,param_15,param_16);
            uVar4 = extraout_r4_00;
          }
          *(undefined1 *)(param_9 + 0x71) = 0;
        }
        iVar1 = zz_02a3c68_(iVar1);
        if (iVar1 == 6) {
          *(undefined4 *)(param_9 + 8) = 3;
        }
      }
      else if (((iVar1 < 2) && (iVar1 != 0)) && (-1 < iVar1)) {
        iVar1 = *(int *)(param_9 + 0x40);
        if (*(int *)(param_9 + 0x118) == 1) {
          zz_02aa62c_();
          iVar3 = zz_02aa788_(*(int *)(param_9 + 0x44));
          if (iVar3 == 2) {
            iVar3 = -1;
            uVar7 = extraout_f1;
          }
          else {
            uVar7 = extraout_f1;
            if (*(int **)(param_9 + 0x128) != (int *)0x0) {
              uVar7 = (**(code **)(**(int **)(param_9 + 0x128) + 0x14))();
            }
            uVar5 = *(undefined4 *)(param_9 + 0x11c);
            param_12 = *(undefined4 *)(param_9 + 0x120);
            param_13 = *(int *)(param_9 + 0x124);
            zz_02aa7fc_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x44),*(undefined4 *)(param_9 + 0x110),uVar5,param_12,
                        param_13);
            iVar3 = zz_02aa7dc_(*(int *)(param_9 + 0x44));
            if (iVar3 == -1) {
              *(undefined4 *)(param_9 + 8) = 4;
              uVar7 = extraout_f1_00;
              zz_02addf4_(0xffffff9a);
              uVar7 = zz_02aa530_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  s_E211141_MWSTM_ReqStart__can_t_st_802bad70,
                                  *(undefined4 *)(param_9 + 0x110),uVar5,param_12,param_13,param_14,
                                  param_15,param_16);
              iVar3 = -1;
              *(undefined4 *)(param_9 + 0x118) = 0;
            }
            else {
              uVar7 = zz_02ad96c_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,
                                  param_8,param_9);
              iVar3 = 1;
            }
          }
          if (iVar3 == 1) {
            *(undefined4 *)(param_9 + 0x118) = 0;
          }
          param_1 = zz_02aa60c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
          uVar4 = extraout_r4;
        }
        iVar1 = zz_02a3c68_(iVar1);
        if ((iVar1 == 4) || (iVar1 == 6)) {
          *(undefined4 *)(param_9 + 8) = 2;
        }
      }
      if ((*(int *)(param_9 + 0x44) != 0) &&
         (uVar2 = zz_02aa8f8_(*(int *)(param_9 + 0x44)), uVar2 != 0)) {
        *(undefined4 *)(param_9 + 8) = 4;
      }
      if ((*(int *)(param_9 + 0x4c) != 0) &&
         (uVar2 = zz_02aa150_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 0x4c),uVar4,uVar5,param_12,param_13,param_14,
                              param_15,param_16), uVar2 == 1)) {
        *(undefined4 *)(param_9 + 8) = 4;
      }
      zz_02aa9bc_(param_9);
    }
    *(undefined4 *)(param_9 + 0x60) = 0;
    uVar2 = zz_02a2d78_(iVar6);
    uVar2 = (1 - uVar2 | uVar2 - 1) >> 0x1f;
  }
  else {
    uVar2 = 0;
    *(undefined4 *)(param_9 + 0x60) = 0;
  }
  return uVar2;
}



// ==== 802af91c  zz_02af91c_ ====

uint zz_02af91c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,int param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  
  uVar3 = 0x80430000;
  if (DAT_80430fb4 == 1) {
    if (param_9 == 0) {
      zz_02aa530_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  s_E1071901_mwPlyExecSvrHndl__NULL_h_802badcc,0x80430000,param_11,param_12,param_13
                  ,param_14,param_15,param_16);
      uVar1 = 0;
    }
    else if (*(int *)(param_9 + 4) == 1) {
      if (*(int *)(param_9 + 0x60) == 1) {
        uVar1 = 0;
      }
      else {
        puVar2 = GetOneTimerLeadGroundContactAnims_void_();
        if (*(int *)(puVar2 + 0x24) == 1) {
          uVar1 = 0;
        }
        else {
          uVar1 = zz_02af6a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_9,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
        }
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 802af9c4  zz_02af9c4_ ====

uint zz_02af9c4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                int param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 extraout_f1;
  undefined8 uVar5;
  
  if (DAT_80430fb4 == 1) {
    puVar2 = GetOneTimerLeadGroundContactAnims_void_();
    uVar5 = zz_02aa5ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int *)(puVar2 + 0x54),param_10,param_11,param_12,param_13,param_14,param_15
                        ,param_16);
    uVar3 = (undefined4)uVar5;
    if ((int)((ulonglong)uVar5 >> 0x20) == 0) {
      uVar1 = 0;
    }
    else {
      iVar4 = 0;
      uVar5 = extraout_f1;
      do {
        if (puVar2 + 0x68 != (undefined *)0x0) {
          zz_02af91c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)(puVar2 + 0x68),uVar3,param_11,param_12,param_13,param_14,param_15,
                      param_16);
        }
        iVar4 = iVar4 + 1;
        puVar2 = puVar2 + 0x210;
      } while (iVar4 < 8);
      puVar2 = GetOneTimerLeadGroundContactAnims_void_();
      *(undefined4 *)(puVar2 + 0x54) = 0;
      iVar4 = zz_02a2cb4_();
      uVar1 = (1U - iVar4 | iVar4 - 1U) >> 0x1f;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 802afa68  FUN_802afa68 ====

void FUN_802afa68(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined *puVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  
  puVar5 = &DAT_80432170;
  puVar3 = &DAT_80432174;
  iVar4 = DAT_80432170 + 1;
  DAT_80432170 = iVar4;
  iVar2 = DAT_80432174 + 1;
  if (DAT_80430fb4 == 1) {
    iVar2 = DAT_80432174;
    DAT_80432174 = DAT_80432174 + 1;
    puVar1 = GetOneTimerLeadGroundContactAnims_void_();
    iVar4 = zz_02aa5ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int *)(puVar1 + 0x58),iVar2,puVar3,iVar4,puVar5,in_r8,in_r9,in_r10);
    iVar2 = DAT_80432174;
    if (iVar4 != 0) {
      if (DAT_80430fb4 == 1) {
        zz_02a2dbc_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      }
      *(undefined4 *)(puVar1 + 0x58) = 0;
      iVar2 = DAT_80432174;
    }
  }
  DAT_80432174 = iVar2;
  return;
}



// ==== 802afaf8  FUN_802afaf8 ====

uint FUN_802afaf8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 int param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined *puVar2;
  uint uVar3;
  
  uVar3 = 0;
  uVar1 = zz_0270bb8_();
  if ((uVar1 == 1) &&
     (puVar2 = GetOneTimerLeadGroundContactAnims_void_(), *(int *)(puVar2 + 0x10) != 1)) {
    uVar3 = zz_02af9c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return uVar3;
}



// ==== 802afb58  FUN_802afb58 ====

uint FUN_802afb58(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 int param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  undefined4 extraout_r4;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined8 extraout_f1;
  undefined8 uVar11;
  
  uVar10 = 0;
  uVar2 = zz_0270bb8_();
  if (uVar2 == 1) {
    puVar3 = GetOneTimerLeadGroundContactAnims_void_();
    if (*(int *)(puVar3 + 0x10) == 1) {
      uVar10 = zz_02af9c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                           param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  else {
    zz_02aa670_();
    puVar9 = &DAT_80432170;
    puVar7 = &DAT_80432174;
    iVar5 = DAT_80432170 + 1;
    iVar6 = DAT_80432174;
    iVar8 = DAT_80432170;
    iVar1 = DAT_80432174 + 1;
    if (DAT_80430fb4 == 1) {
      DAT_80432170 = iVar5;
      DAT_80432174 = DAT_80432174 + 1;
      puVar3 = GetOneTimerLeadGroundContactAnims_void_();
      iVar4 = zz_02aa5ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)(puVar3 + 0x58),iVar5,iVar6,puVar7,iVar8,puVar9,param_15,param_16);
      param_1 = extraout_f1;
      iVar5 = DAT_80432170;
      iVar1 = DAT_80432174;
      if (iVar4 != 0) {
        if (DAT_80430fb4 == 1) {
          param_1 = zz_02a2dbc_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8)
          ;
        }
        *(undefined4 *)(puVar3 + 0x58) = 0;
        iVar5 = DAT_80432170;
        iVar1 = DAT_80432174;
      }
    }
    DAT_80432174 = iVar1;
    DAT_80432170 = iVar5;
    uVar11 = zz_02aa650_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    uVar10 = zz_02af9c4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         extraout_r4,iVar6,puVar7,iVar8,puVar9,param_15,param_16);
  }
  return uVar10;
}



// ==== 802afc4c  FUN_802afc4c ====

undefined4
FUN_802afc4c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  
  uVar1 = zz_0270bb8_();
  if (uVar1 == 1) {
    zz_02aa670_();
    puVar7 = &DAT_80432170;
    puVar6 = &DAT_80432174;
    iVar4 = DAT_80432170 + 1;
    iVar5 = DAT_80432174 + 1;
    if (DAT_80430fb4 == 1) {
      iVar5 = DAT_80432174;
      iVar3 = DAT_80432170;
      DAT_80432170 = iVar4;
      DAT_80432174 = DAT_80432174 + 1;
      puVar2 = GetOneTimerLeadGroundContactAnims_void_();
      iVar3 = zz_02aa5ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)(puVar2 + 0x58),iVar4,iVar5,puVar6,iVar3,puVar7,in_r9,in_r10);
      param_1 = extraout_f1;
      iVar4 = DAT_80432170;
      iVar5 = DAT_80432174;
      if (iVar3 != 0) {
        if (DAT_80430fb4 == 1) {
          param_1 = zz_02a2dbc_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8)
          ;
        }
        *(undefined4 *)(puVar2 + 0x58) = 0;
        iVar4 = DAT_80432170;
        iVar5 = DAT_80432174;
      }
    }
    DAT_80432174 = iVar5;
    DAT_80432170 = iVar4;
    zz_02aa650_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return 0;
}



// ==== 802afd0c  zz_02afd0c_ ====

void zz_02afd0c_(int *param_1,int param_2,int param_3,int param_4,uint param_5)

{
  undefined8 *puVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint *puVar16;
  undefined8 *puVar17;
  uint *puVar18;
  undefined8 *puVar19;
  undefined8 *puVar20;
  undefined8 *puVar21;
  undefined8 *puVar22;
  uint *puVar23;
  uint *puVar24;
  uint *puVar25;
  uint uVar26;
  int iVar27;
  undefined8 uVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  undefined8 uVar31;
  
  iVar8 = 0;
  puVar21 = (undefined8 *)(param_2 + -8);
  uVar10 = param_1[3];
  puVar22 = (undefined8 *)*param_1;
  uVar13 = uVar10 * 3;
  uVar6 = param_4 - uVar10;
  uVar3 = ((int)uVar10 >> 3) + (uint)((int)uVar10 < 0 && (uVar10 & 7) != 0);
  do {
    if ((int)(((int)param_5 >> 2) + (uint)((int)param_5 < 0 && (param_5 & 3) != 0)) <= iVar8) {
      iVar8 = param_1[3];
      uVar3 = param_5 - ((int)param_5 >> 0x1f);
      uVar10 = param_1[4];
      puVar7 = (uint *)param_1[1];
      uVar6 = iVar8 - (iVar8 >> 0x1f);
      puVar2 = (uint *)param_1[2];
      puVar5 = (uint *)(param_3 + -4);
      iVar4 = ((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0);
      uVar6 = uVar10 - iVar8 / 2;
      iVar15 = ((int)uVar6 >> 2) + (uint)((int)uVar6 < 0 && (uVar6 & 3) != 0);
      iVar11 = ((int)uVar10 >> 2) + (uint)((int)uVar10 < 0 && (uVar10 & 3) != 0);
      iVar8 = iVar11 * 3 + iVar15;
      for (iVar9 = 0; iVar9 < (int)(((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0));
          iVar9 = iVar9 + 1) {
        puVar12 = puVar2 + iVar11;
        puVar16 = puVar2 + iVar11 * 2;
        puVar18 = puVar2 + iVar11 * 3;
        puVar25 = puVar7 + iVar11;
        puVar24 = puVar7 + iVar11 * 2;
        puVar23 = puVar7 + iVar11 * 3;
        iVar27 = iVar4;
        if (0 < iVar4) {
          do {
            dataCacheBlockClearToZero(puVar5 + 1);
            uVar6 = *puVar2;
            puVar2 = puVar2 + 1;
            uVar10 = *puVar7;
            puVar7 = puVar7 + 1;
            puVar5[1] = uVar6 >> 0x10 & 0xff |
                        uVar10 >> 8 & 0xff00 | uVar10 & 0xff000000 | uVar6 >> 8 & 0xff0000;
            puVar5[2] = uVar6 & 0xff |
                        (uVar10 & 0xff) << 8 | (uVar10 & 0xff00) << 0x10 | (uVar6 & 0xff00) << 8;
            uVar6 = *puVar12;
            puVar12 = puVar12 + 1;
            uVar10 = *puVar25;
            puVar25 = puVar25 + 1;
            puVar5[3] = uVar6 >> 0x10 & 0xff |
                        uVar10 >> 8 & 0xff00 | uVar10 & 0xff000000 | uVar6 >> 8 & 0xff0000;
            puVar5[4] = uVar6 & 0xff |
                        (uVar10 & 0xff) << 8 | (uVar10 & 0xff00) << 0x10 | (uVar6 & 0xff00) << 8;
            uVar6 = *puVar16;
            puVar16 = puVar16 + 1;
            uVar10 = *puVar24;
            puVar24 = puVar24 + 1;
            puVar5[5] = uVar6 >> 0x10 & 0xff |
                        uVar10 >> 8 & 0xff00 | uVar10 & 0xff000000 | uVar6 >> 8 & 0xff0000;
            puVar5[6] = uVar6 & 0xff |
                        (uVar10 & 0xff) << 8 | (uVar10 & 0xff00) << 0x10 | (uVar6 & 0xff00) << 8;
            uVar6 = *puVar18;
            puVar18 = puVar18 + 1;
            uVar10 = *puVar23;
            puVar23 = puVar23 + 1;
            puVar5[7] = uVar6 >> 0x10 & 0xff |
                        uVar10 >> 8 & 0xff00 | uVar10 & 0xff000000 | uVar6 >> 8 & 0xff0000;
            puVar5 = puVar5 + 8;
            *puVar5 = uVar6 & 0xff |
                      (uVar10 & 0xff) << 8 | (uVar10 & 0xff00) << 0x10 | (uVar6 & 0xff00) << 8;
            iVar27 = iVar27 + -1;
          } while (iVar27 != 0);
        }
        puVar5 = puVar5 + iVar15 * 8;
        puVar7 = puVar7 + iVar8;
        puVar2 = puVar2 + iVar8;
      }
      return;
    }
    puVar20 = (undefined8 *)(uVar10 + (int)puVar22);
    puVar19 = (undefined8 *)(uVar10 * 2 + (int)puVar22);
    puVar17 = (undefined8 *)(uVar13 + (int)puVar22);
    if (0 < (int)uVar3) {
      uVar26 = uVar3 >> 2;
      uVar14 = uVar3;
      if (uVar26 != 0) {
        do {
          dataCacheBlockClearToZero(puVar21 + 1);
          uVar28 = *puVar20;
          uVar29 = *puVar19;
          uVar30 = *puVar17;
          dataCacheBlockTouch(puVar22 + 1);
          puVar21[1] = *puVar22;
          puVar21[2] = uVar28;
          puVar21[3] = uVar29;
          puVar21[4] = uVar30;
          dataCacheBlockClearToZero(puVar21 + 5);
          uVar28 = puVar20[1];
          uVar29 = puVar19[1];
          uVar30 = puVar17[1];
          dataCacheBlockTouch(puVar22 + 2);
          puVar21[5] = puVar22[1];
          puVar21[6] = uVar28;
          puVar21[7] = uVar29;
          puVar21[8] = uVar30;
          dataCacheBlockClearToZero(puVar21 + 9);
          uVar28 = puVar20[2];
          uVar29 = puVar19[2];
          uVar30 = puVar17[2];
          dataCacheBlockTouch(puVar22 + 3);
          puVar21[9] = puVar22[2];
          puVar21[10] = uVar28;
          puVar21[0xb] = uVar29;
          puVar21[0xc] = uVar30;
          dataCacheBlockClearToZero(puVar21 + 0xd);
          puVar1 = puVar22 + 3;
          uVar28 = puVar20[3];
          uVar29 = puVar19[3];
          uVar30 = puVar17[3];
          dataCacheBlockTouch(puVar22 + 4);
          puVar22 = puVar22 + 4;
          puVar21[0xd] = *puVar1;
          puVar17 = puVar17 + 4;
          puVar19 = puVar19 + 4;
          puVar20 = puVar20 + 4;
          puVar21[0xe] = uVar28;
          puVar21[0xf] = uVar29;
          puVar21 = puVar21 + 0x10;
          *puVar21 = uVar30;
          uVar26 = uVar26 - 1;
        } while (uVar26 != 0);
        uVar14 = uVar3 & 3;
        if (uVar14 == 0) goto LAB_802afe80;
      }
      do {
        dataCacheBlockClearToZero(puVar21 + 1);
        uVar28 = *puVar22;
        uVar29 = *puVar20;
        uVar30 = *puVar19;
        uVar31 = *puVar17;
        dataCacheBlockTouch(puVar22 + 1);
        puVar22 = puVar22 + 1;
        puVar21[1] = uVar28;
        puVar17 = puVar17 + 1;
        puVar19 = puVar19 + 1;
        puVar20 = puVar20 + 1;
        puVar21[2] = uVar29;
        puVar21[3] = uVar30;
        puVar21 = puVar21 + 4;
        *puVar21 = uVar31;
        uVar14 = uVar14 - 1;
      } while (uVar14 != 0);
    }
LAB_802afe80:
    puVar21 = puVar21 + (((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0)) * 4;
    puVar22 = puVar22 + ((int)uVar13 >> 3) + (uint)((int)uVar13 < 0 && (uVar13 & 7) != 0);
    iVar8 = iVar8 + 1;
  } while( true );
}



// ==== 802b0038  zz_02b0038_ ====

void zz_02b0038_(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  uint uVar7;
  uint uVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  float *pfVar14;
  int iVar15;
  
  dVar6 = DAT_802bae58;
  fVar5 = DAT_802bae44;
  fVar4 = DAT_802bae40;
  fVar3 = DAT_802bae3c;
  fVar2 = DAT_802bae34;
  fVar1 = DAT_802bae30;
  pfVar9 = (float *)&DAT_80432180;
  DAT_80433580 = PTR_s_CRI_CFT_GC_Ver_1_24_Build_Feb_6_2_803af100;
  pfVar11 = (float *)&DAT_80433180;
  pfVar12 = (float *)&DAT_80432d80;
  pfVar13 = (float *)&DAT_80432980;
  pfVar14 = (float *)&DAT_80432580;
  iVar10 = 0;
  iVar15 = 0x100;
  do {
    uVar8 = iVar10 - 0x10;
    uVar7 = iVar10 - 0x80U ^ 0x80000000;
    iVar10 = iVar10 + 1;
    *pfVar12 = fVar2 * (float)((double)CONCAT44(0x43300000,uVar7) - dVar6);
    pfVar12 = pfVar12 + 1;
    *pfVar13 = fVar1 * (float)((double)CONCAT44(0x43300000,uVar7) - dVar6);
    pfVar13 = pfVar13 + 1;
    *pfVar11 = fVar5 * (float)((double)CONCAT44(0x43300000,uVar8 ^ 0x80000000) - dVar6);
    pfVar11 = pfVar11 + 1;
    *pfVar9 = fVar4 * (float)((double)CONCAT44(0x43300000,uVar7) - dVar6);
    pfVar9 = pfVar9 + 1;
    *pfVar14 = fVar3 * (float)((double)CONCAT44(0x43300000,uVar7) - dVar6);
    pfVar14 = pfVar14 + 1;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  return;
}



