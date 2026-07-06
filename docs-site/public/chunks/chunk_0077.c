// ==== 8029772c  FUN_8029772c ====

int FUN_8029772c(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  char *pcVar2;
  undefined4 *puVar3;
  int *piVar4;
  code *pcVar5;
  code *pcVar6;
  code *pcVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  
  iVar1 = cTeam__GetPlayer_int_(param_9,6);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    puVar9 = (undefined4 *)(param_9 + 0x279c);
    *(undefined4 **)(param_9 + 0x1b74) = puVar9;
    iVar1 = zz_0297538_(param_9,puVar9);
    if (iVar1 == 0) {
      iVar1 = zz_02a1168_();
      pcVar2 = DAT_8041d42c;
      if (iVar1 != 1) {
        pcVar2 = zz_026f5a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 0x27b0),*(int *)(param_9 + 0x27bc),
                             *(int *)(param_9 + 0x27b8),param_12,param_13,param_14,param_15,param_16
                            );
      }
      if (pcVar2 == (char *)0x0) {
        pcVar2 = (char *)0x0;
      }
      else {
        zz_026e700_((int)pcVar2,0);
        param_1 = zz_0271348_((int)pcVar2,1);
      }
      if (pcVar2 == (char *)0x0) {
        iVar1 = zz_029abec_(param_9,-0xfff3fc);
      }
      else {
        puVar3 = zz_02774e0_(*(undefined4 *)(param_9 + 0x27ac),*(undefined4 *)(param_9 + 0x27a4),
                             *(undefined4 *)(param_9 + 0x27a8));
        if (puVar3 == (undefined4 *)0x0) {
          iVar1 = zz_029abec_(param_9,-0xfff3fb);
        }
        else {
          *puVar9 = pcVar2;
          *(undefined4 **)(param_9 + 0x27a0) = puVar3;
          iVar1 = param_9 + 0x2848;
          *(int *)(param_9 + 0x1c84) = iVar1;
          pcVar7 = FUN_80298434;
          pcVar6 = FUN_8029840c;
          uVar8 = *(undefined4 *)(pcVar2 + 0xc);
          pcVar5 = FUN_802983e4;
          *(undefined4 *)(param_9 + 0x2848) = uVar8;
          *(code **)(param_9 + 0x284c) = FUN_80298434;
          *(code **)(param_9 + 0x2850) = FUN_8029840c;
          *(code **)(param_9 + 0x2854) = FUN_802983e4;
          *(code **)(param_9 + 0x2858) = FUN_802983bc;
          *(code **)(param_9 + 0x285c) = FUN_80298318;
          uVar10 = zz_026efc4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               (int)pcVar2,(int)puVar3,FUN_802983bc,FUN_802983e4,FUN_8029840c,
                               FUN_80298434,uVar8,iVar1);
          piVar4 = *(int **)(param_9 + 0x1b74);
          piVar4[0xb] = 1;
          zz_026e4b8_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar4,1,
                      piVar4,pcVar5,pcVar6,pcVar7,uVar8,iVar1);
          zz_02a6b28_((undefined4 *)(param_9 + 0xf60),1);
          zz_02a4618_(param_9,FUN_8029743c,2);
          zz_02a39d8_(param_9,0xf,2);
          iVar1 = 0;
        }
      }
    }
  }
  return iVar1;
}



// ==== 802978e4  FUN_802978e4 ====

void FUN_802978e4(int param_1,void *param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int unaff_r26;
  int iVar3;
  
  *param_4 = 0;
  iVar3 = *(int *)(param_1 + 0x1b74);
  iVar1 = zz_029a0fc_(param_1);
  if (iVar1 < 0x6c) {
    for (iVar1 = 0; iVar1 < param_3 + -0x12; iVar1 = iVar1 + 0x12) {
      iVar2 = gnt4_memcmp(param_2,&DAT_802b8a68,0x12);
      if (iVar2 != 0) {
        *(code **)(iVar3 + 0x3c) = FUN_802979f8;
        break;
      }
      param_2 = (void *)((int)param_2 + 0x12);
    }
    *param_4 = iVar1;
    if (*(int *)(param_1 + 0x2898) == 0) {
      iVar2 = 0;
    }
    else if (*(int *)(*(int *)(param_1 + 0x1b74) + 0x40) < 1) {
      iVar2 = *(int *)(param_1 + 0x2898) + 0xcfc;
    }
    else {
      iVar2 = 0;
    }
    if (iVar2 == 0) {
      iVar2 = -1;
    }
    else {
      unaff_r26 = *(int *)(iVar2 + 0xc);
      iVar2 = 0;
    }
    if (iVar2 == 0) {
      *(int *)(iVar3 + 0x38) = *(int *)(iVar3 + 0x38) + (iVar1 / (unaff_r26 * 0x12)) * 0x20;
    }
  }
  else {
    *(code **)(iVar3 + 0x3c) = FUN_802979f8;
  }
  return;
}



// ==== 802979f8  FUN_802979f8 ====

void FUN_802979f8(int param_1,short *param_2,int param_3,int *param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  int iStack_38;
  int local_34 [2];
  
  *param_4 = 0;
  iVar4 = *(int *)(param_1 + 0x1b74);
  if (0x11f < param_3) {
    iVar2 = zz_026e2b0_(param_2,param_3,local_34);
    if (iVar2 == 0) {
      iVar2 = zz_029a0fc_(param_1);
      if (iVar2 < 0x6c) {
        bVar1 = false;
        psVar8 = (short *)0x0;
        psVar7 = (short *)0x0;
        for (psVar5 = param_2; psVar5 < param_2 + 0x12; psVar5 = psVar5 + 1) {
          uVar3 = (uint)((int)param_2 + param_3 + (0x11 - (int)psVar5)) / 0x12;
          bVar1 = false;
          psVar6 = psVar5;
          if (psVar5 < (short *)((int)param_2 + param_3)) {
            do {
              if (*(char *)psVar6 < '\0') {
                bVar1 = true;
                iVar2 = zz_026e280_(psVar6,0x12,&iStack_38);
                if ((iVar2 != 0) && (psVar8 < psVar6)) {
                  psVar7 = psVar5;
                  psVar8 = psVar6;
                }
                break;
              }
              psVar6 = psVar6 + 9;
              uVar3 = uVar3 - 1;
            } while (uVar3 != 0);
          }
          if (!bVar1) break;
        }
        if ((bVar1) && (psVar5 = psVar7, psVar7 == (short *)0x0)) {
          zz_029abec_(param_1,-0xfff3f6);
          psVar5 = param_2;
        }
        local_34[0] = (int)psVar5 - (int)param_2;
      }
      else {
        local_34[0] = 0;
      }
    }
    *(code **)(iVar4 + 0x3c) = FUN_80297b50;
    *param_4 = local_34[0];
  }
  return;
}



// ==== 80297b50  FUN_80297b50 ====

void FUN_80297b50(int param_1,short *param_2,int param_3,int *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_r28;
  uint unaff_r29;
  short *psVar7;
  int iVar8;
  int iStack_48;
  int local_44;
  int aiStack_40 [5];
  
  iVar4 = 0;
  iVar5 = param_1 + 0xcc0;
  *param_4 = 0;
  iVar8 = *(int *)(param_1 + 0x1b74);
  if ((*(int *)(param_1 + 0x2898) != 0) && (*(int *)(iVar8 + 0x40) < 1)) {
    iVar4 = *(int *)(param_1 + 0x2898) + 0xcfc;
  }
  if (iVar4 == 0) {
    iVar1 = -1;
  }
  else {
    unaff_r28 = *(int *)(iVar4 + 0xc);
    iVar1 = 0;
    unaff_r29 = *(uint *)(iVar4 + 0x10);
  }
  if (iVar1 == 0) {
    iVar4 = zz_02a4c68_(iVar5,unaff_r29);
    if (-1 < iVar4) {
      iVar1 = cTeam__GetPlayer_int_(param_1,5);
      if (iVar1 == 0) {
        zz_02a4be0_(iVar5,iVar4,unaff_r29);
        *(code **)(iVar8 + 0x3c) = FUN_80297db4;
      }
      else {
        iVar1 = zz_02a4bec_(iVar5,unaff_r29,&local_44);
        if (-1 < iVar1) {
          zz_02a4be0_(iVar5,iVar1,unaff_r29);
          iVar5 = 0;
          uVar2 = (iVar1 - iVar4) - *(int *)(iVar8 + 0x38);
          if ((int)uVar2 < 0) {
            if (local_44 != 0) {
              uVar2 = -uVar2;
              uVar2 = (((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * 0x20;
              if (0 < (int)uVar2) {
                iVar4 = zz_026e100_(**(int **)(param_1 + 0x1b74),unaff_r28,uVar2);
                uVar2 = uVar2 - iVar4;
                *(int *)(iVar8 + 0x38) = *(int *)(iVar8 + 0x38) - iVar4;
              }
              if ((int)uVar2 < 1) {
                *(code **)(iVar8 + 0x3c) = FUN_80297db4;
              }
            }
          }
          else {
            iVar4 = 0;
            iVar1 = (((int)uVar2 >> 5) + (uint)((int)uVar2 < 0 && (uVar2 & 0x1f) != 0)) * unaff_r28
                    * 0x12;
            if (0 < iVar1) {
              iVar4 = unaff_r28 * (param_3 / (unaff_r28 * 0x12)) * 0x12;
              iVar6 = iVar1;
              if (iVar4 < iVar1) {
                iVar6 = iVar4;
              }
              iVar4 = 0;
              psVar7 = param_2;
              for (iVar5 = 0; iVar5 < iVar6; iVar5 = iVar5 + 0x12) {
                iVar3 = zz_026e280_(psVar7,0x12,&iStack_48);
                if (iVar3 != 0) {
                  iVar4 = 1;
                  break;
                }
                psVar7 = psVar7 + 9;
              }
              iVar1 = iVar1 - iVar6;
              *(int *)(iVar8 + 0x38) = *(int *)(iVar8 + 0x38) + (iVar5 / (unaff_r28 * 0x12)) * 0x20;
            }
            if ((iVar1 < 1) && (local_44 != 0)) {
              *(code **)(iVar8 + 0x3c) = FUN_80297db4;
              iVar4 = zz_026e280_(param_2,param_3,aiStack_40);
            }
            if (iVar4 != 0) {
              zz_02a39d8_(param_1,6,0);
            }
          }
          *param_4 = iVar5;
        }
      }
    }
  }
  else {
    *(code **)(iVar8 + 0x3c) = FUN_80297db4;
  }
  return;
}



// ==== 80297db4  FUN_80297db4 ====

void FUN_80297db4(int param_1,void *param_2,size_t param_3,size_t *param_4)

{
  int *piVar1;
  int iVar2;
  size_t sVar3;
  int aiStack_28 [2];
  void *local_20;
  size_t local_1c;
  
  iVar2 = *(int *)(param_1 + 0x1b74);
  piVar1 = *(int **)(iVar2 + 4);
  (**(code **)(*piVar1 + 0x18))(piVar1,0,*(undefined4 *)(iVar2 + 8),&local_20);
  if ((int)param_3 < (int)local_1c) {
    local_1c = param_3;
  }
  sVar3 = 0x19000;
  if ((int)local_1c < 0x19000) {
    sVar3 = local_1c;
  }
  zz_027c990_(local_20,param_2,sVar3);
  if (sVar3 == 0) {
    (**(code **)(*piVar1 + 0x1c))(piVar1,0,&local_20);
  }
  else {
    zz_02779cc_((int *)&local_20,sVar3,(int *)&local_20,aiStack_28);
    (**(code **)(*piVar1 + 0x20))(piVar1,1,&local_20);
    (**(code **)(*piVar1 + 0x1c))(piVar1,0,aiStack_28);
  }
  *(size_t *)(iVar2 + 0x48) = *(int *)(iVar2 + 0x48) + sVar3;
  *param_4 = sVar3;
  return;
}



// ==== 80297ec4  zz_0297ec4_ ====

int zz_0297ec4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,int *param_12,undefined4 param_13
               ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int extraout_r4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int unaff_r31;
  int local_48;
  undefined4 local_44;
  int local_40;
  
  iVar3 = cTeam__GetPlayer_int_(param_9,6);
  if (iVar3 == 0) {
    return unaff_r31;
  }
  iVar3 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1b80));
  if (iVar3 == 1) {
    return unaff_r31;
  }
  iVar8 = *(int *)(param_9 + 0x1b74);
  iVar10 = 0;
  iVar4 = zz_0299180_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      *(int *)(param_9 + 0x1b7c),&local_44);
  iVar3 = local_40;
  if (iVar4 == 0) {
    param_12 = &local_48;
    param_1 = (**(code **)(iVar8 + 0x3c))(param_9,local_44);
    zz_0298df8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                *(int *)(param_9 + 0x1b7c),local_48);
    iVar3 = local_48;
    iVar10 = local_40;
  }
  iVar9 = *(int *)(param_9 + 0x1b80);
  iVar7 = *(int *)(param_9 + 0x1b7c);
  iVar4 = iVar9;
  iVar8 = zz_0298b40_(param_9,iVar9);
  if ((iVar8 != 1) && (iVar8 = zz_0298b40_(param_9,iVar7), iVar4 = iVar7, iVar8 == 1)) {
    iVar4 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        **(int **)(param_9 + 0x1b74),iVar7,iVar3,param_12,param_13,param_14,param_15
                        ,param_16);
    uVar2 = countLeadingZeros(3 - iVar4);
    iVar4 = iVar7;
    if (uVar2 >> 5 != 0) {
      iVar3 = 1;
      param_1 = zz_0298b50_(param_9,iVar9,1);
      iVar4 = extraout_r4;
    }
  }
  piVar5 = *(int **)(param_9 + 0x1b74);
  iVar7 = *piVar5;
  iVar8 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar4,
                      iVar3,param_12,param_13,param_14,param_15,param_16);
  iVar4 = zz_026e608_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,iVar4,
                      iVar3,param_12,param_13,param_14,param_15,param_16);
  if (iVar4 != 0) {
    DAT_8041cff4 = iVar4;
  }
  iVar7 = cTeam__GetPlayer_int_(param_9,0x1a);
  if (iVar7 == 0) {
    iVar4 = 0;
  }
  if (iVar4 == -1) {
    zz_029abec_(param_9,-0xfff3f8);
  }
  else {
    if (iVar4 < -1) {
      if (-3 < iVar4) {
        zz_029abec_(param_9,-0xfff3f7);
        goto LAB_80298078;
      }
    }
    else if (iVar4 < 1) goto LAB_80298078;
    zz_029abec_(param_9,-0xfff3f9);
  }
LAB_80298078:
  if ((iVar8 == 4) || (iVar8 == 5)) {
    param_1 = zz_02a6b20_(param_9 + 0xf60,0);
  }
  if ((iVar8 == 5) || (iVar4 != 0)) {
    iVar3 = 1;
    param_1 = zz_0298b30_(param_9,*(int *)(param_9 + 0x1b80),1);
  }
  iVar4 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1b7c));
  if (((iVar4 == 1) && (iVar10 == 0)) && (piVar5[0x12] == 0)) {
    iVar3 = 1;
    param_1 = zz_0298b30_(param_9,*(int *)(param_9 + 0x1b80),1);
  }
  piVar5 = *(int **)(param_9 + 0x1b74);
  if (*(int *)(param_9 + 0x2898) == 0) {
    piVar6 = (int *)0x0;
  }
  else if (piVar5[0x10] < 1) {
    piVar6 = (int *)(*(int *)(param_9 + 0x2898) + 0xcfc);
  }
  else {
    piVar6 = (int *)0x0;
  }
  if ((piVar6 != (int *)0x0) && (*piVar6 == 0)) {
    iVar4 = *piVar5;
    iVar10 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                         piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
    if ((iVar10 == 0) || (iVar10 == 1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      iVar10 = zz_026e8c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
      piVar6[4] = iVar10;
      iVar10 = zz_026e918_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
      piVar6[5] = iVar10;
      iVar10 = zz_026e868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                           piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
      piVar6[3] = iVar10;
      uVar2 = piVar6[4] * piVar6[3] * 9;
      piVar6[1] = ((int)uVar2 >> 4) + (uint)((int)uVar2 < 0 && (uVar2 & 0xf) != 0);
      piVar6[2] = 1;
      *piVar6 = 1;
    }
  }
  piVar5 = *(int **)(param_9 + 0x1b74);
  iVar4 = *piVar5;
  iVar10 = cTeam__GetPlayer_int_(param_9,0x1b);
  if (piVar5[0x11] != iVar10) {
    piVar5[0x11] = iVar10;
    param_1 = zz_026e708_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                          iVar10,iVar3,param_12,param_13,param_14,param_15,param_16);
  }
  piVar5 = *(int **)(param_9 + 0x1b74);
  iVar10 = *piVar5;
  if (*(int *)(param_9 + 0xe70) == *(int *)(param_9 + 0xe74)) {
    iVar4 = zz_026e918_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                        piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_026e8c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                        piVar5,iVar3,param_12,param_13,param_14,param_15,param_16);
    if ((0 < iVar4) && (0 < iVar3)) {
      zz_0299e64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar4,
                  iVar3);
    }
  }
  return unaff_r31;
}



// ==== 80298240  FUN_80298240 ====

void FUN_80298240(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,int *param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_0297ec4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80298260  FUN_80298260 ====

undefined4
FUN_80298260(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  uVar1 = zz_026a59c_();
  zz_0264384_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  return 0;
}



// ==== 80298288  FUN_80298288 ====

undefined4
FUN_80298288(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  zz_0264414_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_026a5b4_();
  zz_02a94c4_(-0x7fbe3008,0,7);
  return 0;
}



// ==== 802982c4  zz_02982c4_ ====

void zz_02982c4_(undefined4 *param_1)

{
  DAT_8041cff8 = *param_1;
  DAT_8041cffc = param_1[1];
  DAT_8041d000 = param_1[2] + 0x1f & 0xffffffe0;
  DAT_8041d004 = param_1[3];
  DAT_8041d008 = param_1[4];
  DAT_8041d00c = param_1[5];
  DAT_8041d010 = param_1[6] + 0x1f & 0xffffffe0;
  return;
}



// ==== 80298318  FUN_80298318 ====

void FUN_80298318(undefined4 param_1,uint param_2)

{
  gnt4_log_bl((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DAT_802b8a88);
  zz_026e4b4_();
  return;
}



// ==== 802983bc  FUN_802983bc ====

void FUN_802983bc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026e740_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              **(int **)(param_9 + 0x1b74),param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 802983e4  FUN_802983e4 ====

void FUN_802983e4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,uint param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026e77c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              **(int **)(param_9 + 0x1b74),param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 8029840c  FUN_8029840c ====

void FUN_8029840c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026e7bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              **(int **)(param_9 + 0x1b74),param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 80298434  FUN_80298434 ====

void FUN_80298434(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int param_10,int param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026e800_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              **(int **)(param_9 + 0x1b74),param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 80298464  FUN_80298464 ====

void FUN_80298464(int param_1)

{
  zz_029abec_(param_1,-0xfff5ff);
  return;
}



// ==== 8029848c  FUN_8029848c ====

void FUN_8029848c(int param_1)

{
  zz_029abec_(param_1,-0xfff5ff);
  return;
}



// ==== 802984b4  FUN_802984b4 ====

void FUN_802984b4(int param_1)

{
  zz_029abec_(param_1,-0xfff5ff);
  return;
}



// ==== 802984dc  FUN_802984dc ====

void FUN_802984dc(int param_1)

{
  zz_029abec_(param_1,-0xfff5ff);
  return;
}



// ==== 80298504  FUN_80298504 ====

int FUN_80298504(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar2 = zz_02a5408_(param_1,3,8,param_2,0);
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}



// ==== 8029857c  FUN_8029857c ====

int FUN_8029857c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar2 = zz_02a5408_(param_1,3,7,0,0);
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}



// ==== 802985e8  FUN_802985e8 ====

int FUN_802985e8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar2 = zz_02a5408_(param_1,3,6,0,0);
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}



// ==== 80298654  FUN_80298654 ====

int FUN_80298654(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar2 = zz_02a5408_(param_1,3,5,0,0);
    iVar1 = 0;
    if (iVar2 != 0) {
      iVar1 = iVar2;
    }
  }
  return iVar1;
}



// ==== 802986c8  FUN_802986c8 ====

undefined4 FUN_802986c8(int param_1)

{
  int iVar1;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 != 0) {
    *(int *)(param_1 + 0x1c84) = param_1 + 0x2848;
  }
  return 0;
}



// ==== 80298714  FUN_80298714 ====

undefined4 FUN_80298714(int param_1)

{
  int iVar1;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,6);
  if (iVar1 != 0) {
    iVar1 = zz_02a53e8_(param_1,7);
    if ((iVar1 != 1) && (iVar1 = zz_0298b40_(param_1,*(int *)(param_1 + 0x1c8c)), iVar1 == 1)) {
      zz_02a53f8_(param_1,7,1);
    }
    iVar1 = zz_02a53c8_(param_1,7);
    if ((iVar1 != 1) && (iVar1 = zz_0298b20_(param_1,*(int *)(param_1 + 0x1c8c)), iVar1 == 1)) {
      zz_02a53d8_(param_1,7,1);
    }
  }
  return 0;
}



// ==== 802987d8  zz_02987d8_ ====

undefined4 zz_02987d8_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = cTeam__GetPlayer_int_(param_1,6);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(param_1 + 0x1c84) + 0x10))(param_1);
    }
  }
  else {
    zz_029abec_(0,-0xfffe5c);
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80298854  zz_0298854_ ====

void zz_0298854_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = cTeam__GetPlayer_int_(param_1,6);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(param_1 + 0x1c84) + 0xc))(param_1,param_2);
    }
  }
  else {
    zz_029abec_(0,-0xfffe5d);
  }
  return;
}



// ==== 802988d4  zz_02988d4_ ====

undefined4 zz_02988d4_(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = cTeam__GetPlayer_int_(param_1,6);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = (**(code **)(*(int *)(param_1 + 0x1c84) + 8))(param_1,param_2);
    }
  }
  else {
    zz_029abec_(0,-0xfffe5e);
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80298960  zz_0298960_ ====

void zz_0298960_(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = cTeam__GetPlayer_int_(param_1,6);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(param_1 + 0x1c84) + 4))(param_1,param_2,param_3);
    }
  }
  else {
    zz_029abec_(0,-0xfffe5f);
  }
  return;
}



// ==== 802989f0  zz_02989f0_ ====

int zz_02989f0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 auStack_24 [4];
  int local_20;
  undefined4 local_1c;
  int local_18;
  
  iVar1 = param_9 + param_10 * 0x74;
  iVar2 = 0;
  piVar3 = *(int **)(iVar1 + 0x1154);
  iVar4 = 0;
  if ((*(int *)(iVar1 + 0x1144) != 0) && (piVar3 != (int *)0x0)) {
    zz_029aac8_();
    iVar2 = (**(code **)(*piVar3 + 0x24))(piVar3,1);
    (**(code **)(*piVar3 + 0x18))(piVar3,1,0x7fffffff,auStack_24);
    if (local_20 < iVar2) {
      (**(code **)(*piVar3 + 0x18))(piVar3,1,0x7fffffff,&local_1c);
      (**(code **)(*piVar3 + 0x1c))(piVar3,1,&local_1c);
    }
    else {
      local_1c = 0;
      local_18 = 0;
    }
    uVar5 = (**(code **)(*piVar3 + 0x1c))(piVar3,1,auStack_24);
    iVar2 = local_18;
    zz_029aa9c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    iVar4 = local_20;
  }
  return iVar4 + iVar2;
}



// ==== 80298b20  zz_0298b20_ ====

undefined4 zz_0298b20_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x74 + 0x114c);
}



// ==== 80298b30  zz_0298b30_ ====

void zz_0298b30_(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + param_2 * 0x74 + 0x114c) = param_3;
  return;
}



// ==== 80298b40  zz_0298b40_ ====

undefined4 zz_0298b40_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x74 + 0x1148);
}



// ==== 80298b50  zz_0298b50_ ====

void zz_0298b50_(int param_1,int param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + param_2 * 0x74 + 0x1148) = param_3;
  return;
}



// ==== 80298b60  zz_0298b60_ ====

undefined4 zz_0298b60_(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = 0;
  iVar2 = param_1 + param_2 * 0x74;
  if (*(int *)(iVar2 + 0x1144) == 0) {
    uVar1 = zz_02a5408_(param_1,*(int *)(iVar2 + 0x118c),0xc,param_3,0);
  }
  *(undefined4 *)(param_1 + 0x44) = 1;
  return uVar1;
}



// ==== 80298bc4  zz_0298bc4_ ====

undefined4 zz_0298bc4_(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_1 + param_2 * 0x74;
  if (*(int *)(iVar2 + 0x1144) == 0) {
    uVar1 = zz_02a5408_(param_1,*(int *)(iVar2 + 0x118c),0xb,param_3,0);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80298c10  zz_0298c10_ ====

void zz_0298c10_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + param_2 * 0x74;
  iVar1 = *(int *)(iVar2 + 0x1174);
  if (iVar1 < 0) {
    return;
  }
  *(int *)(iVar2 + 0x1174) = iVar1 + param_3;
  return;
}



// ==== 80298c30  zz_0298c30_ ====

int zz_0298c30_(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  
  *param_3 = 0;
  iVar2 = param_1 + param_2 * 0x74;
  if (*(int *)(iVar2 + 0x1144) == 0) {
    iVar1 = zz_029abec_(param_1,-0xfffbff);
  }
  else {
    iVar1 = 0;
    *param_3 = *(undefined4 *)(iVar2 + 0x1154);
  }
  return iVar1;
}



// ==== 80298c84  zz_0298c84_ ====

int zz_0298c84_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  undefined8 extraout_f1;
  
  iVar3 = param_9 + param_10 * 0x74;
  uVar4 = zz_029aac8_();
  iVar2 = *(int *)(iVar3 + 0x1170);
  iVar1 = *(int *)(iVar3 + 0x1174);
  if ((iVar2 == 0) && (iVar1 != 0)) {
    iVar2 = (**(code **)(**(int **)(iVar3 + 0x1154) + 0x24))(*(int **)(iVar3 + 0x1154),1);
    iVar2 = iVar1 + iVar2;
    uVar4 = extraout_f1;
  }
  if (iVar2 < 0) {
    iVar2 = 0x7fffffff;
  }
  zz_029aa9c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return iVar2;
}



// ==== 80298d18  zz_0298d18_ ====

undefined4 zz_0298d18_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x74 + 0x1174);
}



// ==== 80298d28  zz_0298d28_ ====

undefined4 zz_0298d28_(int param_1,int param_2)

{
  return *(undefined4 *)(param_1 + param_2 * 0x74 + 0x115c);
}



// ==== 80298d38  zz_0298d38_ ====

void zz_0298d38_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = param_9 + param_10 * 0x74;
  uVar2 = zz_029aac8_();
  *(undefined4 *)(iVar1 + 0x1168) = param_11;
  *(undefined4 *)(iVar1 + 0x116c) = param_12;
  zz_029aa9c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80298d94  zz_0298d94_ ====

void zz_0298d94_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 *param_11,undefined4 *param_12)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = param_9 + param_10 * 0x74;
  uVar2 = zz_029aac8_();
  *param_11 = *(undefined4 *)(iVar1 + 0x1168);
  *param_12 = *(undefined4 *)(iVar1 + 0x116c);
  zz_029aa9c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80298df8  zz_0298df8_ ====

int zz_0298df8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined8 uVar6;
  uint local_44;
  int local_40;
  uint local_3c;
  int local_38;
  undefined1 auStack_34 [4];
  int local_30;
  undefined1 auStack_2c [4];
  int local_28;
  
  iVar5 = 0;
  iVar1 = param_9 + param_10 * 0x74;
  piVar4 = *(int **)(iVar1 + 0x1154);
  if (param_11 != 0) {
    if ((*(int *)(iVar1 + 0x1144) == 0) || (piVar4 == (int *)0x0)) {
      iVar5 = 0;
    }
    else {
      zz_029aac8_();
      (**(code **)(*piVar4 + 0x18))(piVar4,1,param_11,auStack_2c);
      uVar6 = (**(code **)(*piVar4 + 0x20))(piVar4,0,auStack_2c);
      if (local_28 < param_11) {
        (**(code **)(*piVar4 + 0x18))(piVar4,1,param_11 - local_28,auStack_34);
        uVar6 = (**(code **)(*piVar4 + 0x20))(piVar4,0,auStack_34);
        if (local_30 < param_11 - local_28) {
          iVar5 = zz_029abec_(param_9,-0xfffbf5);
        }
      }
      if (param_10 == 1) {
        piVar4 = *(int **)(iVar1 + 0x1154);
        iVar2 = (**(code **)(*piVar4 + 0x24))(piVar4,1);
        (**(code **)(*piVar4 + 0x18))(piVar4,1,0x7fffffff,&local_44);
        if (local_40 < iVar2) {
          (**(code **)(*piVar4 + 0x18))(piVar4,1,0x7fffffff,&local_3c);
          (**(code **)(*piVar4 + 0x1c))(piVar4,1,&local_3c);
        }
        else {
          local_3c = 0;
          local_38 = 0;
        }
        uVar6 = (**(code **)(*piVar4 + 0x1c))(piVar4,1,&local_44);
        uVar3 = *(uint *)(iVar1 + 0x1168);
        if (((uVar3 < local_44) || (local_44 + local_40 <= uVar3)) &&
           ((uVar3 < local_3c || (local_3c + local_38 <= uVar3)))) {
          *(undefined4 *)(iVar1 + 0x1168) = 0;
          *(undefined4 *)(iVar1 + 0x116c) = 0;
        }
      }
      if (-1 < *(int *)(iVar1 + 0x1174)) {
        *(int *)(iVar1 + 0x1174) = *(int *)(iVar1 + 0x1174) + param_11;
      }
      *(undefined4 *)(param_9 + 0x44) = 1;
      zz_029aa9c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
  }
  return iVar5;
}



// ==== 80299044  zz_0299044_ ====

int zz_0299044_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,int param_11)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined8 uVar4;
  undefined1 auStack_34 [4];
  int local_30;
  undefined1 auStack_2c [4];
  int local_28;
  
  iVar1 = param_9 + param_10 * 0x74;
  iVar2 = 0;
  piVar3 = *(int **)(iVar1 + 0x1154);
  if (param_11 != 0) {
    if ((*(int *)(iVar1 + 0x1144) == 0) || (piVar3 == (int *)0x0)) {
      iVar2 = 0;
    }
    else {
      zz_029aac8_();
      (**(code **)(*piVar3 + 0x18))(piVar3,0,param_11,auStack_2c);
      uVar4 = (**(code **)(*piVar3 + 0x20))(piVar3,1,auStack_2c);
      if (local_28 < param_11) {
        (**(code **)(*piVar3 + 0x18))(piVar3,0,param_11 - local_28,auStack_34);
        uVar4 = (**(code **)(*piVar3 + 0x20))(piVar3,1,auStack_34);
        if (local_30 < param_11 - local_28) {
          iVar2 = zz_029abec_(param_9,-0xfffbf5);
        }
      }
      if (-1 < *(int *)(iVar1 + 0x1170)) {
        *(int *)(iVar1 + 0x1170) = *(int *)(iVar1 + 0x1170) + param_11;
      }
      *(undefined4 *)(param_9 + 0x44) = 1;
      zz_029aa9c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
  }
  return iVar2;
}



// ==== 80299180  zz_0299180_ ====

undefined4
zz_0299180_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10,undefined4 *param_11)

{
  int iVar1;
  int *piVar2;
  undefined8 uVar3;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = param_9 + param_10 * 0x74;
  *param_11 = 0;
  param_11[1] = 0;
  param_11[2] = 0;
  param_11[3] = 0;
  param_11[4] = 0;
  param_11[5] = 0;
  param_11[6] = 0;
  piVar2 = *(int **)(iVar1 + 0x1154);
  if ((*(int *)(iVar1 + 0x1144) != 0) && (piVar2 != (int *)0x0)) {
    zz_029aac8_();
    iVar1 = (**(code **)(*piVar2 + 0x24))(piVar2,1);
    (**(code **)(*piVar2 + 0x18))(piVar2,1,0x7fffffff,&local_24);
    if (local_20 < iVar1) {
      (**(code **)(*piVar2 + 0x18))(piVar2,1,0x7fffffff,&local_1c);
      (**(code **)(*piVar2 + 0x1c))(piVar2,1,&local_1c);
    }
    else {
      local_1c = 0;
      local_18 = 0;
    }
    uVar3 = (**(code **)(*piVar2 + 0x1c))(piVar2,1,&local_24);
    *param_11 = local_24;
    param_11[1] = local_20;
    param_11[2] = local_1c;
    param_11[3] = local_18;
    zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return 0;
}



// ==== 802992ec  zz_02992ec_ ====

undefined4
zz_02992ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10,undefined4 *param_11)

{
  int iVar1;
  int *piVar2;
  undefined8 uVar3;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  iVar1 = param_9 + param_10 * 0x74;
  *param_11 = 0;
  param_11[1] = 0;
  param_11[2] = 0;
  param_11[3] = 0;
  param_11[4] = 0;
  param_11[5] = 0;
  param_11[6] = 0;
  piVar2 = *(int **)(iVar1 + 0x1154);
  if ((*(int *)(iVar1 + 0x1144) != 0) && (piVar2 != (int *)0x0)) {
    zz_029aac8_();
    iVar1 = (**(code **)(*piVar2 + 0x24))(piVar2,0);
    (**(code **)(*piVar2 + 0x18))(piVar2,0,0x7fffffff,&local_24);
    if (local_20 < iVar1) {
      (**(code **)(*piVar2 + 0x18))(piVar2,0,0x7fffffff,&local_1c);
      (**(code **)(*piVar2 + 0x1c))(piVar2,0,&local_1c);
    }
    else {
      local_1c = 0;
      local_18 = 0;
    }
    uVar3 = (**(code **)(*piVar2 + 0x1c))(piVar2,0,&local_24);
    *param_11 = local_24;
    param_11[1] = local_20;
    param_11[2] = local_1c;
    param_11[3] = local_18;
    zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return 0;
}



// ==== 80299458  zz_0299458_ ====

void zz_0299458_(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = param_1 + param_2 * 0x74 + param_3 * 0x10;
  uVar1 = *(undefined4 *)(iVar2 + 0x1154);
  *param_4 = *(undefined4 *)(iVar2 + 0x1150);
  param_4[1] = uVar1;
  uVar1 = *(undefined4 *)(iVar2 + 0x115c);
  param_4[2] = *(undefined4 *)(iVar2 + 0x1158);
  param_4[3] = uVar1;
  return;
}



// ==== 8029948c  zz_029948c_ ====

void zz_029948c_(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = param_4[1];
  iVar2 = param_1 + param_2 * 0x74 + param_3 * 0x10;
  *(undefined4 *)(iVar2 + 0x1150) = *param_4;
  *(undefined4 *)(iVar2 + 0x1154) = uVar1;
  uVar1 = param_4[3];
  *(undefined4 *)(iVar2 + 0x1158) = param_4[2];
  *(undefined4 *)(iVar2 + 0x115c) = uVar1;
  return;
}



// ==== 802994c0  zz_02994c0_ ====

int zz_02994c0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int *param_10)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  if (param_10[1] == 0) {
    iVar1 = -1;
    goto LAB_80299544;
  }
  if (*param_10 == 0) {
    if (param_10[2] == 0) {
      iVar1 = -1;
      goto LAB_80299544;
    }
    if (param_10[3] < 1) {
      iVar1 = -1;
      goto LAB_80299544;
    }
    if (0 < param_10[5]) {
      iVar1 = -1;
      goto LAB_80299544;
    }
  }
  iVar1 = 0;
LAB_80299544:
  if (iVar1 == 0) {
    uVar2 = zz_02a53ac_(param_9,1);
    if (uVar2 == 0) {
      uVar2 = zz_02a53ac_(param_9,2);
      if (uVar2 == 0) {
        uVar2 = zz_02a53ac_(param_9,3);
        if (uVar2 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = 2;
        }
      }
      else {
        iVar1 = 1;
      }
    }
    else {
      iVar1 = 0;
    }
    iVar1 = param_9 + iVar1 * 0x74;
    if (*(int *)(iVar1 + 0x1140) == 4) {
      uVar2 = param_10[1];
      zz_029aac8_();
      *(uint *)(iVar1 + 0x1144) = (-uVar2 | uVar2) >> 0x1f;
      iVar3 = param_10[1];
      *(int *)(iVar1 + 0x1150) = *param_10;
      *(int *)(iVar1 + 0x1154) = iVar3;
      iVar3 = param_10[3];
      *(int *)(iVar1 + 0x1158) = param_10[2];
      *(int *)(iVar1 + 0x115c) = iVar3;
      iVar3 = param_10[5];
      *(int *)(iVar1 + 0x1160) = param_10[4];
      *(int *)(iVar1 + 0x1164) = iVar3;
      *(undefined4 *)(iVar1 + 0x1168) = 0;
      *(undefined4 *)(iVar1 + 0x116c) = 0;
      *(undefined4 *)(iVar1 + 0x1170) = 0;
      *(undefined4 *)(iVar1 + 0x1174) = 0;
      uVar4 = zz_02a3070_((undefined4 *)(iVar1 + 0x1178));
      zz_029aa9c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      iVar1 = 0;
    }
    else {
      iVar1 = zz_029abec_(param_9,-0xfffbf7);
    }
  }
  else {
    iVar1 = zz_029abec_(param_9,-0xfffbf8);
  }
  return iVar1;
}



// ==== 80299678  zz_0299678_ ====

void zz_0299678_(int param_1)

{
  if ((*(int *)(param_1 + 0x1140) == 5) && (*(int **)(param_1 + 0x1154) != (int *)0x0)) {
    (**(code **)(**(int **)(param_1 + 0x1154) + 0xc))();
    *(undefined4 *)(param_1 + 0x1154) = 0;
  }
  if ((*(int *)(param_1 + 0x11b4) == 5) && (*(int **)(param_1 + 0x11c8) != (int *)0x0)) {
    (**(code **)(**(int **)(param_1 + 0x11c8) + 0xc))();
    *(undefined4 *)(param_1 + 0x11c8) = 0;
  }
  if ((*(int *)(param_1 + 0x1228) == 5) && (*(int **)(param_1 + 0x123c) != (int *)0x0)) {
    (**(code **)(**(int **)(param_1 + 0x123c) + 0xc))();
    *(undefined4 *)(param_1 + 0x123c) = 0;
  }
  return;
}



// ==== 80299744  zz_0299744_ ====

int zz_0299744_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 *param_10,int param_11)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  undefined8 uVar14;
  undefined4 *local_88;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 *local_70;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 *local_58;
  int local_4c;
  undefined4 local_48;
  
  iVar4 = *(int *)(param_11 + 8);
  iVar6 = *(int *)(param_11 + 4);
  iVar7 = iVar6 + iVar4;
  iVar8 = iVar7 + *(int *)(param_11 + 0xc);
  iVar9 = iVar8 + *(int *)(param_11 + 0x10);
  iVar10 = iVar9 + *(int *)(param_11 + 0x14);
  iVar2 = *(int *)(param_11 + 0x1c);
  iVar11 = iVar10 + *(int *)(param_11 + 0x18);
  iVar3 = iVar4 - (iVar4 / *(int *)(param_11 + 0x28)) * *(int *)(param_11 + 0x28);
  if (iVar4 == 0) {
    uVar12 = 0;
    uVar13 = 4;
LAB_80299890:
    *param_10 = uVar13;
    iVar4 = 0;
    param_10[1] = uVar12;
    param_10[2] = 0;
    param_10[3] = 0;
    param_10[0x13] = 9;
    param_10[0x14] = 9;
  }
  else {
    iVar4 = iVar4 - iVar3;
    puVar1 = (undefined4 *)0x0;
    uVar12 = 1;
    uVar13 = 5;
    if (0 < iVar4) {
      local_48 = 0;
      puVar1 = zz_02774e0_(iVar6,iVar4,iVar3);
      local_58 = puVar1;
      local_4c = iVar3;
    }
    if (puVar1 != (undefined4 *)0x0) {
      zz_029aac8_();
      param_10[1] = 1;
      param_10[4] = 0;
      param_10[5] = local_58;
      param_10[6] = iVar6;
      param_10[7] = iVar4;
      param_10[8] = local_4c;
      param_10[9] = local_48;
      param_10[10] = 0;
      param_10[0xb] = 0;
      param_10[0xc] = 0;
      param_10[0xd] = 0;
      uVar14 = zz_02a3070_(param_10 + 0xe);
      zz_029aa9c_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      goto LAB_80299890;
    }
    iVar4 = -1;
  }
  if (*(int *)(param_11 + 0xc) == 0) {
    uVar12 = 0;
    uVar13 = 4;
LAB_80299980:
    param_10[0x1d] = uVar13;
    iVar3 = 0;
    param_10[0x1e] = uVar12;
    param_10[0x1f] = 0;
    param_10[0x20] = 0;
    param_10[0x30] = 9;
    param_10[0x31] = 9;
  }
  else {
    iVar3 = *(int *)(param_11 + 0xc) + -0x800;
    puVar1 = (undefined4 *)0x0;
    uVar12 = 1;
    uVar13 = 5;
    if (0 < iVar3) {
      local_60 = 0;
      local_64 = 0x800;
      puVar1 = zz_02774e0_(iVar7,iVar3,0x800);
      local_70 = puVar1;
    }
    if (puVar1 != (undefined4 *)0x0) {
      zz_029aac8_();
      param_10[0x1e] = 1;
      param_10[0x21] = 0;
      param_10[0x22] = local_70;
      param_10[0x23] = iVar7;
      param_10[0x24] = iVar3;
      param_10[0x25] = local_64;
      param_10[0x26] = local_60;
      param_10[0x27] = 0;
      param_10[0x28] = 0;
      param_10[0x29] = 0;
      param_10[0x2a] = 0;
      uVar14 = zz_02a3070_(param_10 + 0x2b);
      zz_029aa9c_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      goto LAB_80299980;
    }
    iVar3 = -1;
  }
  iVar6 = *(int *)(param_11 + 0x10);
  if (iVar6 == 0) {
    uVar12 = 0;
    uVar13 = 4;
  }
  else {
    puVar1 = (undefined4 *)0x0;
    uVar12 = 1;
    uVar13 = 5;
    if (0 < iVar6) {
      local_7c = 0;
      local_78 = 0;
      puVar1 = zz_02774e0_(iVar8,iVar6,0);
      local_88 = puVar1;
    }
    if (puVar1 == (undefined4 *)0x0) {
      iVar6 = -1;
      goto LAB_80299a88;
    }
    zz_029aac8_();
    param_10[0x3b] = 1;
    param_10[0x3e] = 0;
    param_10[0x3f] = local_88;
    param_10[0x40] = iVar8;
    param_10[0x41] = iVar6;
    param_10[0x42] = local_7c;
    param_10[0x43] = local_78;
    param_10[0x44] = 0;
    param_10[0x45] = 0;
    param_10[0x46] = 0;
    param_10[0x47] = 0;
    uVar14 = zz_02a3070_(param_10 + 0x48);
    zz_029aa9c_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  param_10[0x3a] = uVar13;
  iVar6 = 0;
  param_10[0x3b] = uVar12;
  param_10[0x3c] = 0;
  param_10[0x3d] = 0;
  param_10[0x4d] = 9;
  param_10[0x4e] = 9;
LAB_80299a88:
  if (((iVar4 == 0) && (iVar3 == 0)) && (iVar6 == 0)) {
    uVar5 = *(uint *)(param_11 + 0x14);
    param_10[0x57] = 1;
    param_10[0x58] = (-uVar5 | uVar5) >> 0x1f;
    param_10[0x59] = 0;
    param_10[0x5a] = 0;
    param_10[0x6a] = 9;
    param_10[0x6b] = 9;
    param_10[0x5b] = iVar9;
    param_10[0x5c] = *(undefined4 *)(param_11 + 0x14);
    param_10[0x5d] = 0;
    param_10[0x5e] = 0;
    param_10[0x5f] = param_9 + 0x14e0;
    *(undefined4 *)param_10[0x5f] = 0;
    *(undefined4 *)(param_10[0x5f] + 0x5c) = 0;
    *(undefined4 *)(param_10[0x5f] + 0xb8) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x114) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x170) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x1cc) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x228) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x284) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x2e0) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x33c) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x398) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x3f4) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x450) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x4ac) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x508) = 0;
    *(undefined4 *)(param_10[0x5f] + 0x564) = 0;
    uVar5 = *(uint *)(param_11 + 0x18);
    param_10[0x74] = 2;
    param_10[0x75] = (-uVar5 | uVar5) >> 0x1f;
    param_10[0x76] = 0;
    param_10[0x77] = 0;
    param_10[0x87] = 9;
    param_10[0x88] = 9;
    param_10[0x78] = iVar10;
    param_10[0x79] = *(undefined4 *)(param_11 + 0x18);
    param_10[0x7a] = 0;
    param_10[0x7b] = 0;
    param_10[0x7c] = 0;
    param_10[0x7d] = 0;
    param_10[0x7e] = 0;
    param_10[0x7f] = 0;
    param_10[0x80] = 0;
    param_10[0x81] = 0;
    param_10[0x82] = 0;
    param_10[0x83] = 0;
    uVar5 = *(uint *)(param_11 + 0x1c);
    param_10[0x91] = 1;
    param_10[0x92] = (-uVar5 | uVar5) >> 0x1f;
    param_10[0x93] = 0;
    param_10[0x94] = 0;
    param_10[0xa4] = 9;
    param_10[0xa5] = 9;
    param_10[0x95] = iVar11;
    param_10[0x96] = *(undefined4 *)(param_11 + 0x1c);
    param_10[0x97] = 0;
    param_10[0x98] = 0;
    param_10[0x99] = param_9 + 0x14e0;
    *(undefined4 *)param_10[0x99] = 0;
    *(undefined4 *)(param_10[0x99] + 0x5c) = 0;
    *(undefined4 *)(param_10[0x99] + 0xb8) = 0;
    *(undefined4 *)(param_10[0x99] + 0x114) = 0;
    *(undefined4 *)(param_10[0x99] + 0x170) = 0;
    *(undefined4 *)(param_10[0x99] + 0x1cc) = 0;
    *(undefined4 *)(param_10[0x99] + 0x228) = 0;
    *(undefined4 *)(param_10[0x99] + 0x284) = 0;
    *(undefined4 *)(param_10[0x99] + 0x2e0) = 0;
    *(undefined4 *)(param_10[0x99] + 0x33c) = 0;
    *(undefined4 *)(param_10[0x99] + 0x398) = 0;
    *(undefined4 *)(param_10[0x99] + 0x3f4) = 0;
    *(undefined4 *)(param_10[0x99] + 0x450) = 0;
    *(undefined4 *)(param_10[0x99] + 0x4ac) = 0;
    *(undefined4 *)(param_10[0x99] + 0x508) = 0;
    *(undefined4 *)(param_10[0x99] + 0x564) = 0;
    uVar5 = *(uint *)(param_11 + 0x20);
    param_10[0xae] = 2;
    param_10[0xaf] = (-uVar5 | uVar5) >> 0x1f;
    iVar4 = 0;
    param_10[0xb0] = 0;
    param_10[0xb1] = 0;
    param_10[0xc1] = 9;
    param_10[0xc2] = 9;
    param_10[0xb2] = iVar11 + iVar2;
    param_10[0xb3] = *(undefined4 *)(param_11 + 0x20);
    param_10[0xb4] = 0;
    param_10[0xb5] = 0;
    param_10[0xb6] = 0;
    param_10[0xb7] = 0;
    param_10[0xb8] = 0;
    param_10[0xb9] = 0;
    param_10[0xba] = 0;
    param_10[0xbb] = 0;
    param_10[0xbc] = 0;
    param_10[0xbd] = 0;
    param_10[0xcb] = 3;
    param_10[0xcc] = 1;
    param_10[0xcd] = 0;
    param_10[0xce] = 0;
    param_10[0xde] = 9;
    param_10[0xdf] = 9;
    param_10[0xcf] = 0;
    param_10[0xd0] = 0;
    param_10[0xd1] = 0;
    param_10[0xd2] = 0;
    param_10[0xd3] = 0;
    param_10[0xd4] = 0;
    param_10[0xd5] = 0;
    param_10[0xd6] = 0;
    param_10[0xd7] = 0;
    param_10[0xd8] = 0;
    param_10[0xd9] = 0;
    param_10[0xda] = 0;
  }
  else {
    iVar4 = zz_029abec_(param_9,-0xfffbf6);
  }
  return iVar4;
}



// ==== 80299da4  zz_0299da4_ ====

void zz_0299da4_(void)

{
  return;
}



// ==== 80299da8  zz_0299da8_ ====

bool zz_0299da8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 *param_10,undefined4 *param_11)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = zz_029aac8_();
  bVar1 = 0 < *(int *)(param_9 + 0xe70) - *(int *)(param_9 + 0xe74);
  if (bVar1) {
    *param_11 = *(undefined4 *)(param_9 + 0xe68);
    iVar2 = *(int *)(param_9 + 0xe74) >> 0x1f;
    *param_10 = *(undefined4 *)
                 (param_9 + ((iVar2 * 0x20 |
                             (uint)(*(int *)(param_9 + 0xe74) * 0x8000000 + iVar2) >> 0x1b) - iVar2)
                            * 4 + 0xe78);
    *(int *)(param_9 + 0xe74) = *(int *)(param_9 + 0xe74) + 1;
  }
  else {
    *param_10 = 0xffffffff;
  }
  zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return bVar1;
}



// ==== 80299e64  zz_0299e64_ ====

bool zz_0299e64_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11)

{
  bool bVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = zz_029aac8_();
  bVar1 = *(int *)(param_9 + 0xe70) - *(int *)(param_9 + 0xe74) < 0x20;
  if (bVar1) {
    *(undefined4 *)(param_9 + 0xe68) = param_11;
    iVar2 = *(int *)(param_9 + 0xe70) >> 0x1f;
    *(undefined4 *)
     (param_9 + ((iVar2 * 0x20 | (uint)(*(int *)(param_9 + 0xe70) * 0x8000000 + iVar2) >> 0x1b) -
                iVar2) * 4 + 0xe78) = param_10;
    *(int *)(param_9 + 0xe70) = *(int *)(param_9 + 0xe70) + 1;
  }
  zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return bVar1;
}



// ==== 80299f0c  zz_0299f0c_ ====

void zz_0299f0c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = zz_029aac8_();
  *(int *)(param_9 + 0xde0) = *(int *)(param_9 + 0xde0) + param_10;
  iVar2 = *(int *)(param_9 + 0xde4) + 1;
  iVar1 = iVar2 >> 0x1f;
  *(undefined4 *)
   (param_9 + ((iVar1 * 0x20 | (uint)(iVar2 * 0x8000000 + iVar1) >> 0x1b) - iVar1) * 4 + 0xde8) =
       *(undefined4 *)(param_9 + 0xde0);
  *(int *)(param_9 + 0xde4) = iVar2;
  zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80299f8c  zz_0299f8c_ ====

undefined4 zz_0299f8c_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,0x31);
  if ((iVar1 == 0) && (iVar1 = cTeam__GetPlayer_int_(param_1,0x39), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80299fe4  zz_0299fe4_ ====

undefined4 zz_0299fe4_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,0x31);
  if ((iVar1 == 0) && (iVar1 = cTeam__GetPlayer_int_(param_1,0x38), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 8029a03c  zz_029a03c_ ====

uint zz_029a03c_(int param_1)

{
  uint uVar1;
  
  uVar1 = cTeam__GetPlayer_int_(param_1,0x31);
  return (-uVar1 | uVar1) >> 0x1f;
}



// ==== 8029a06c  zz_029a06c_ ====

int zz_029a06c_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    zz_02a39d8_(param_1,0x31,1);
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffe9f);
  }
  return iVar1;
}



// ==== 8029a0c8  zz_029a0c8_ ====

undefined4 zz_029a0c8_(int param_1)

{
  if (*(int *)(param_1 + 0x78) == 0) {
    return 0xffffffff;
  }
  if (*(int *)(param_1 + 0xe8) != 0) {
    return *(undefined4 *)(param_1 + 0xec);
  }
  return 0xffffffff;
}



// ==== 8029a0fc  zz_029a0fc_ ====

int zz_029a0fc_(int param_1)

{
  if (*(int *)(param_1 + 0x78) != 0) {
    return *(int *)(param_1 + 0x80) + *(int *)(param_1 + 0x7c) * 100;
  }
  return 0;
}



// ==== 8029a124  zz_029a124_ ====

void zz_029a124_(int *param_1,undefined4 *param_2)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  undefined4 local_7c;
  uint local_78;
  uint local_74;
  undefined4 local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  uint local_48;
  undefined4 local_44;
  int local_40;
  uint local_3c;
  undefined4 local_38;
  uint local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14 [2];
  
  iVar3 = zz_02a8f78_(param_1,local_14);
  if (iVar3 == 0) {
    local_14[0] = 0;
  }
  if (local_14[0] != 0) {
    iVar3 = zz_02a8998_(param_1,&local_1c,&local_20);
    if (iVar3 == 0) {
      local_1c = 0;
      local_20 = 0;
    }
    param_2[1] = local_1c;
    param_2[2] = local_20;
    iVar3 = param_2[1];
    iVar5 = param_2[2];
    iVar4 = zz_02a84bc_(param_1,&local_18);
    if (iVar4 == 0) {
      local_18 = 0;
    }
    if (iVar5 + iVar3 * 100 < 0x6e) {
      local_18 = -local_18;
    }
    param_2[3] = local_18;
    iVar3 = zz_02a8910_(param_1,&local_38);
    if (iVar3 == 0) {
      local_38 = 0xffffffff;
    }
    param_2[4] = local_38;
    iVar3 = zz_02a8888_(param_1,&local_3c);
    if (iVar3 == 0) {
      local_3c = 0xffffffff;
    }
    param_2[5] = local_3c;
    iVar3 = zz_02a8800_(param_1,&local_40);
    if (iVar3 == 0) {
      local_40 = -1;
    }
    param_2[6] = local_40;
    if (param_2[6] == -1) {
      param_2[6] = 2;
    }
    iVar3 = zz_02a8778_(param_1,&local_44);
    if (iVar3 == 0) {
      local_44 = 0xffffffff;
    }
    param_2[7] = local_44;
    iVar3 = zz_02a86f0_(param_1,&local_48);
    if (iVar3 == 0) {
      local_48 = 0xffffffff;
    }
    param_2[8] = local_48;
    iVar3 = zz_02a8668_(param_1,&local_4c);
    if (iVar3 == 0) {
      local_4c = 0xffffffff;
    }
    param_2[9] = local_4c;
    iVar3 = zz_02a85e0_(param_1,&local_50);
    if (iVar3 == 0) {
      local_50 = 0xffffffff;
    }
    param_2[10] = local_50;
    iVar3 = zz_02a8558_(param_1,&local_54);
    if (iVar3 == 0) {
      local_54 = 0xffffffff;
    }
    param_2[0xb] = local_54;
    iVar3 = zz_02a8434_(param_1,&local_58);
    if (iVar3 == 0) {
      local_58 = 0xffffffff;
    }
    param_2[0xc] = local_58;
    iVar3 = zz_02a83ac_(param_1,&local_5c);
    if (iVar3 == 0) {
      local_5c = 0xffffffff;
    }
    param_2[0xd] = local_5c;
    iVar3 = zz_02a8324_(param_1,&local_60);
    if (iVar3 == 0) {
      local_60 = 0xffffffff;
    }
    param_2[0xe] = local_60;
    iVar3 = zz_02a8e88_(param_1,-0x43,&local_24);
    if ((iVar3 == 0) || (local_24 == 0)) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xbd;
    }
    param_2[0xf] = uVar2;
    iVar3 = zz_02a8e88_(param_1,-0x41,&local_28);
    if ((iVar3 == 0) || (local_28 == 0)) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0xbf;
    }
    param_2[0x10] = uVar2;
    iVar3 = 0xc0;
    do {
      iVar4 = zz_02a8e88_(param_1,(char)iVar3,&local_2c);
      if ((iVar4 != 0) && (local_2c != 0)) goto LAB_8029a428;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xe0);
    iVar3 = 0;
LAB_8029a428:
    param_2[0x11] = iVar3;
    iVar3 = 0xe0;
    do {
      iVar4 = zz_02a8e88_(param_1,(char)iVar3,&local_30);
      if ((iVar4 != 0) && (local_30 != 0)) goto LAB_8029a468;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0xf0);
    iVar3 = 0;
LAB_8029a468:
    param_2[0x12] = iVar3;
    if (param_2[0x11] != 0) {
      bVar1 = (byte)param_2[0x11];
      iVar3 = zz_02a81dc_(param_1,bVar1,&local_64);
      if (iVar3 == 0) {
        local_64 = 0xffffffff;
      }
      param_2[0x13] = local_64;
      iVar3 = zz_02a8080_(param_1,bVar1,&local_68);
      if (iVar3 == 0) {
        local_68 = 0xffffffff;
      }
      param_2[0x14] = local_68;
      iVar3 = zz_02a7f38_(param_1,bVar1,&local_6c);
      if (iVar3 == 0) {
        local_6c = 0xffffffff;
      }
      param_2[0x15] = local_6c;
      iVar3 = zz_02a7df0_(param_1,bVar1,&local_70);
      if (iVar3 == 0) {
        local_70 = 0xffffffff;
      }
      param_2[0x16] = local_70;
    }
    bVar1 = (byte)param_2[0x12];
    iVar3 = zz_02a7ca8_(param_1,bVar1,&local_74);
    if (iVar3 == 0) {
      local_74 = 0xffffffff;
    }
    param_2[0x17] = local_74;
    iVar3 = zz_02a7b50_(param_1,bVar1,&local_78);
    if (iVar3 == 0) {
      local_78 = 0xffffffff;
    }
    param_2[0x18] = local_78;
    iVar3 = zz_02a79c4_(param_1,bVar1,param_2 + 0x19,param_2 + 0x1a);
    if (iVar3 == 0) {
      param_2[0x19] = 0xffffffff;
      param_2[0x1a] = 0xffffffff;
    }
    iVar3 = zz_02a780c_(param_1,bVar1,&local_7c);
    if (iVar3 == 0) {
      local_7c = 0xffffffff;
    }
    param_2[0x1b] = local_7c;
    iVar3 = zz_02a8e80_(param_1,bVar1,&local_34);
    if (iVar3 == 0) {
      local_34 = 0;
    }
    param_2[0x1c] = (-local_34 | local_34) >> 0x1f;
    if (local_34 != 0) {
      iVar3 = zz_02a768c_(param_1,bVar1,&local_80);
      if (iVar3 == 0) {
        local_80 = 0xffffffff;
      }
      param_2[0x1d] = local_80;
      iVar3 = zz_02a750c_(param_1,bVar1,&local_84);
      if (iVar3 == 0) {
        local_84 = 0xffffffff;
      }
      param_2[0x1e] = local_84;
      iVar3 = zz_02a7388_(param_1,bVar1,&local_88);
      if (iVar3 == 0) {
        local_88 = 0xffffffff;
      }
      param_2[0x1f] = local_88;
      iVar3 = zz_02a7204_(param_1,bVar1,&local_8c);
      if (iVar3 == 0) {
        local_8c = 0xffffffff;
      }
      param_2[0x20] = local_8c;
      iVar3 = zz_02a7084_(param_1,bVar1,&local_90);
      if (iVar3 == 0) {
        local_90 = 0xffffffff;
      }
      param_2[0x21] = local_90;
      iVar3 = zz_02a6ef0_(param_1,bVar1,&local_94);
      if (iVar3 == 0) {
        local_94 = 0xffffffff;
      }
      param_2[0x22] = local_94;
      iVar3 = zz_02a6d5c_(param_1,bVar1,&local_98);
      if (iVar3 == 0) {
        local_98 = 0xffffffff;
      }
      param_2[0x23] = local_98;
    }
    *param_2 = 1;
  }
  return;
}



// ==== 8029a738  zz_029a738_ ====

void zz_029a738_(undefined4 *param_1)

{
  int *piVar1;
  
  piVar1 = zz_02a91d8_((int)(param_1 + 0x25),param_1[0x24]);
  if (piVar1 != (int *)0x0) {
    zz_029a124_(piVar1,param_1);
    zz_02a91ac_(piVar1);
  }
  return;
}



// ==== 8029a78c  zz_029a78c_ ====

void zz_029a78c_(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x2898) == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = zz_029af30_(param_1);
    if (iVar4 < 1) {
      iVar4 = *(int *)(param_1 + 0x2898) + 0xc;
    }
    else {
      iVar4 = 0;
    }
  }
  if (iVar4 != 0) {
    iVar7 = 0x112;
    puVar1 = (undefined4 *)(iVar4 + -4);
    puVar2 = (undefined4 *)(param_1 + 0x74);
    do {
      puVar6 = puVar2;
      puVar5 = puVar1;
      uVar3 = puVar5[2];
      puVar6[1] = puVar5[1];
      puVar6[2] = uVar3;
      iVar7 = iVar7 + -1;
      puVar1 = puVar5 + 2;
      puVar2 = puVar6 + 2;
    } while (iVar7 != 0);
    puVar6[3] = puVar5[3];
    zz_029a738_((undefined4 *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x930) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x934) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x938) = *(undefined4 *)(param_1 + 0xa4);
  }
  return;
}



// ==== 8029a838  zz_029a838_ ====

undefined4 zz_029a838_(int param_1,void *param_2,size_t param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  size_t sVar7;
  int iVar8;
  
  if (*(int *)(param_1 + 0x78) == 0) {
    sVar7 = 0x800;
    if ((int)param_3 < 0x800) {
      sVar7 = param_3;
    }
    zz_027c990_((void *)(param_1 + 0x10c),param_2,sVar7);
    *(size_t *)(param_1 + 0x108) = sVar7;
    zz_029a738_((undefined4 *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x930) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x934) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x938) = *(undefined4 *)(param_1 + 0xa4);
    if (*(int *)(param_1 + 0x2898) == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = zz_029af30_(param_1);
      if (iVar4 < 1) {
        iVar4 = *(int *)(param_1 + 0x2898) + 0xc;
      }
      else {
        iVar4 = 0;
      }
    }
    if (iVar4 != 0) {
      iVar8 = 0x112;
      puVar1 = (undefined4 *)(param_1 + 0x74);
      puVar2 = (undefined4 *)(iVar4 + -4);
      do {
        puVar6 = puVar2;
        puVar5 = puVar1;
        uVar3 = puVar5[2];
        puVar6[1] = puVar5[1];
        puVar6[2] = uVar3;
        iVar8 = iVar8 + -1;
        puVar1 = puVar5 + 2;
        puVar2 = puVar6 + 2;
      } while (iVar8 != 0);
      puVar6[3] = puVar5[3];
    }
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 8029a928  zz_029a928_ ====

undefined4 zz_029a928_(int param_1,int param_2,int param_3,int param_4,undefined4 *param_5)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_28 [5];
  
  *param_5 = 0;
  if (param_2 == 2) {
    iVar4 = param_3 + -6;
    iVar5 = param_4 + 6;
    if (*(int *)(param_3 + -6) != 0x1bf) {
      iVar5 = param_4 + 8;
      iVar4 = param_3 + -8;
      if (CONCAT31(CONCAT21(*(undefined2 *)(param_3 + -8),*(undefined1 *)(param_3 + -6)),
                   *(undefined1 *)(param_3 + -5)) != 0x1bf) {
        return 0;
      }
    }
    piVar2 = zz_02a91d8_(iVar4 + -0xc,iVar5 + 0xc);
    if (piVar2 == (int *)0x0) {
      iVar3 = 0;
    }
    else {
      iVar3 = zz_02a8f78_(piVar2,local_28);
      if (iVar3 == 0) {
        local_28[0] = 0;
      }
      zz_02a91ac_(piVar2);
      iVar3 = local_28[0];
    }
    if (iVar3 == 0) {
      uVar1 = 0;
    }
    else {
      uVar1 = zz_029a838_(param_1,(void *)(iVar4 + -0xc),iVar5 + 0xc);
      *param_5 = uVar1;
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8029aa40  zz_029aa40_ ====

void zz_029aa40_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[3] = 0;
  param_1[0x24] = 0;
  return;
}



// ==== 8029aa54  zz_029aa54_ ====

void zz_029aa54_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[0x24] = 0;
  return;
}



// ==== 8029aa70  InstallCallStackDumper(void) ====

void InstallCallStackDumper_void_(void)

{
  zz_02a9244_(0x20,(undefined4 *)&DAT_8041d018);
  return;
}



// ==== 8029aa9c  zz_029aa9c_ ====

void zz_029aa9c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  
  uVar1 = zz_02a2da0_();
  if (uVar1 == 0) {
    zz_02711e4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8029aac8  zz_029aac8_ ====

void zz_029aac8_(void)

{
  uint uVar1;
  
  uVar1 = zz_02a2da0_();
  if (uVar1 == 0) {
    zz_0271204_();
  }
  return;
}



// ==== 8029aaf4  zz_029aaf4_ ====

int zz_029aaf4_(int param_1)

{
  uint uVar1;
  
  DAT_8041d224 = param_1;
  if (param_1 == 0) {
    return -1;
  }
  uVar1 = countLeadingZeros(*(undefined4 *)(param_1 + 0x48));
  return -(uVar1 >> 5 & 1);
}



// ==== 8029ab20  zz_029ab20_ ====

/* WARNING: Removing unreachable block (ram,0x8029ab54) */

undefined4 zz_029ab20_(int param_1,undefined *param_2,undefined4 param_3)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  
  pcVar1 = (code *)param_2;
  uVar2 = param_3;
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0x48) == 0) {
      iVar3 = -1;
    }
    else {
      iVar3 = 0;
    }
    DAT_8041d224 = param_1;
    if (iVar3 != 0) {
      if (DAT_8041d3d0 == 0) {
        DAT_8041d3d0 = -0xfffeff;
      }
      if (DAT_8041d3c8 != (code *)0x0) {
        (*DAT_8041d3c8)(DAT_8041d3cc,0xff000101);
      }
      return 0xff000101;
    }
    *(undefined **)(param_1 + 0x98c) = param_2;
    *(undefined4 *)(param_1 + 0x990) = param_3;
    pcVar1 = DAT_8041d3c8;
    uVar2 = DAT_8041d3cc;
  }
  DAT_8041d3cc = uVar2;
  DAT_8041d3c8 = pcVar1;
  return 0;
}



// ==== 8029abec  zz_029abec_ ====

int zz_029abec_(int param_1,int param_2)

{
  if (param_2 == 0) {
    param_2 = 0;
  }
  else if (param_1 == 0) {
    if (DAT_8041d3d0 == 0) {
      DAT_8041d3d0 = param_2;
    }
    if ((param_2 != 0) && (DAT_8041d3c8 != (code *)0x0)) {
      (*DAT_8041d3c8)(DAT_8041d3cc,param_2);
    }
  }
  else {
    if (*(int *)(param_1 + 0x994) == 0) {
      *(int *)(param_1 + 0x994) = param_2;
    }
    if ((param_2 != 0) && (*(code **)(param_1 + 0x98c) != (code *)0x0)) {
      (**(code **)(param_1 + 0x98c))(*(undefined4 *)(param_1 + 0x990),param_2);
    }
    if (0 < *(int *)(param_1 + 0x48)) {
      *(int *)(param_1 + 0x48) = -*(int *)(param_1 + 0x48);
    }
  }
  return param_2;
}



// ==== 8029acc8  zz_029acc8_ ====

void zz_029acc8_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return;
}



// ==== 8029ace4  zz_029ace4_ ====

int zz_029ace4_(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  
  DAT_8041d220 = 0x2968;
  DAT_8041d228 = s_CRI_SFD_GC_Ver_1_842_Build_Feb_6_802b8ac8;
  zz_02776b8_();
  zz_02a94c4_(-0x7fbe2dd4,0,0x89);
  zz_027c990_(&DAT_8041d22c,&DAT_802b8c40,400);
  DAT_8041d3c0 = param_1[1];
  DAT_8041d3bc = *param_1;
  DAT_8041d3c4 = 0;
  DAT_8041d3c8 = 0;
  DAT_8041d3cc = 0;
  DAT_8041d3d0 = 0;
  DAT_8041d3d4 = 0;
  DAT_8041d3d8 = 0;
  zz_02a5398_(&DAT_8041d3dc,DAT_8041d3c0);
  zz_0299da4_();
  DAT_8041d428 = 0;
  DAT_8041d42c = 0;
  DAT_8041d430 = 0;
  DAT_8041d434 = 0;
  DAT_8041d438 = 0;
  DAT_8041d43c = 0;
  DAT_8041d440 = 0;
  DAT_8041d444 = 0;
  DAT_8041d448 = 0;
  DAT_8041d44c = 0;
  iVar1 = zz_02a5928_((int *)&DAT_8041d3ec,(int *)*param_1);
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar2 = iVar1;
  }
  if (iVar2 == 0) {
    zz_02a2e04_();
    InstallCallStackDumper_void_();
    iVar2 = 0;
  }
  return iVar2;
}



// ==== 8029ae04  zz_029ae04_ ====

uint zz_029ae04_(undefined4 param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(0x2968 - param_2);
  return uVar1 >> 5;
}



// ==== 8029ae1c  FUN_8029ae1c ====

void FUN_8029ae1c(int param_1)

{
  zz_029abec_(param_1,-0xfffaff);
  return;
}



// ==== 8029ae44  FUN_8029ae44 ====

void FUN_8029ae44(int param_1)

{
  zz_029abec_(param_1,-0xfffaff);
  return;
}



// ==== 8029ae6c  FUN_8029ae6c ====

void FUN_8029ae6c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,int param_10)

{
  zz_0299044_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              *(int *)(param_9 + 0x1ab4),param_10);
  return;
}



// ==== 8029ae9c  FUN_8029ae9c ====

void FUN_8029ae9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 *param_10)

{
  zz_02992ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              *(int *)(param_9 + 0x1ab4),param_10);
  return;
}



// ==== 8029aef4  FUN_8029aef4 ====

undefined4 FUN_8029aef4(int param_1)

{
  zz_0298b50_(param_1,*(int *)(param_1 + 0x1ab4),1);
  return 0;
}



// ==== 8029af30  zz_029af30_ ====

undefined4 zz_029af30_(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x1aec) + 0x14);
}



// ==== 8029af3c  FUN_8029af3c ====

int FUN_8029af3c(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  int *piVar5;
  uint uStack_28;
  int aiStack_24 [3];
  
  if (*(int *)(param_1 + 0x2898) == 0) {
    piVar5 = (int *)0x0;
  }
  else if (*(int *)(*(int *)(param_1 + 0x1aec) + 0x14) < 1) {
    piVar5 = (int *)(*(int *)(param_1 + 0x2898) + 0x8a0);
  }
  else {
    piVar5 = (int *)0x0;
  }
  if (piVar5 == (int *)0x0) {
    iVar1 = 0;
  }
  else if (*piVar5 == 0) {
    iVar1 = 0;
  }
  else {
    puVar3 = *(undefined4 **)(param_1 + 0x1aec);
    zz_029a78c_(param_1);
    piVar4 = (int *)*puVar3;
    iVar1 = zz_027d6ec_(piVar4,piVar5 + 9,piVar5[0x61],aiStack_24,&uStack_28);
    iVar2 = zz_027d6ec_(piVar4,piVar5 + 0x35,piVar5[0x62],aiStack_24,&uStack_28);
    if ((iVar1 == 0) && (iVar2 == 0)) {
      iVar1 = 0;
    }
    else {
      iVar1 = zz_029abec_(param_1,-0xfff2f3);
    }
    if (iVar1 == 0) {
      iVar1 = 0;
      puVar3[8] = piVar5[7];
      puVar3[9] = piVar5[8];
      *(int *)(param_1 + 0xdd4) = piVar5[5];
      puVar3[3] = piVar5[6];
    }
  }
  return iVar1;
}



// ==== 8029b058  FUN_8029b058 ====

void FUN_8029b058(int param_1)

{
  zz_029abec_(param_1,-0xfff2f5);
  return;
}



// ==== 8029b080  FUN_8029b080 ====

void FUN_8029b080(int param_1)

{
  zz_029abec_(param_1,-0xfff2f5);
  return;
}



// ==== 8029b0a8  FUN_8029b0a8 ====

void FUN_8029b0a8(int param_1)

{
  zz_029abec_(param_1,-0xfff2f5);
  return;
}



// ==== 8029b0d0  FUN_8029b0d0 ====

void FUN_8029b0d0(int param_1)

{
  zz_029abec_(param_1,-0xfff2f5);
  return;
}



// ==== 8029b118  FUN_8029b118 ====

int FUN_8029b118(int param_1)

{
  int iVar1;
  
  iVar1 = zz_027dc30_((int *)**(undefined4 **)(param_1 + 0x1aec));
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(param_1,-0xfff2f6);
  }
  return iVar1;
}



// ==== 8029b16c  FUN_8029b16c ====

void FUN_8029b16c(int param_1,int param_2)

{
  zz_029abec_(param_1,param_2);
  return;
}



// ==== 8029b18c  FUN_8029b18c ====

int FUN_8029b18c(int param_1)

{
  int *piVar1;
  int iVar2;
  
  *(undefined4 **)(param_1 + 0x1aec) = (undefined4 *)(param_1 + 0x1d04);
  *(undefined4 *)(param_1 + 0x1d04) = 0;
  *(undefined4 *)(param_1 + 0x1d08) = 0;
  *(undefined4 *)(param_1 + 0x1d0c) = 0;
  *(undefined4 *)(param_1 + 0x1d10) = 0x7fffffff;
  *(undefined4 *)(param_1 + 0x1d14) = 0x7fffffff;
  *(undefined4 *)(param_1 + 0x1d18) = 0;
  *(undefined4 *)(param_1 + 0x1d1c) = 0x7fffffff;
  *(undefined4 *)(param_1 + 0x1d20) = 0x7fffffff;
  *(undefined4 *)(param_1 + 0x1d24) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1d28) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1d2c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1d30) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1d34) = 0;
  piVar1 = zz_027dcc8_();
  if (piVar1 == (int *)0x0) {
    iVar2 = zz_029abec_(param_1,-0xfff2f8);
  }
  else {
    iVar2 = zz_027de48_(piVar1,-0x7fd64e94,param_1);
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x1d04) = piVar1;
      iVar2 = 0;
    }
    else {
      zz_027dc30_(piVar1);
      iVar2 = zz_029abec_(param_1,-0xfff2f7);
    }
  }
  return iVar2;
}



// ==== 8029b26c  zz_029b26c_ ====

void zz_029b26c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int aiStack_68 [2];
  int local_60;
  int aiStack_5c [4];
  int local_4c;
  int aiStack_3c [2];
  int local_34;
  int local_30;
  
  iVar10 = 0;
  puVar7 = *(undefined4 **)(param_9 + 0x1aec);
  piVar9 = (int *)*puVar7;
  iVar5 = 0;
  iVar8 = 0;
  do {
    zz_027db0c_(piVar9,aiStack_3c,iVar10);
    iVar1 = local_34;
    if (local_34 < iVar5) {
      iVar1 = iVar5;
    }
    iVar6 = local_30;
    if (local_30 < iVar8) {
      iVar6 = iVar8;
    }
    iVar10 = iVar10 + 1;
    iVar5 = iVar1;
    iVar8 = iVar6;
  } while (iVar10 < 3);
  puVar7[2] = iVar1;
  puVar7[1] = iVar6;
  uVar2 = zz_0298b40_(param_9,*(int *)(param_9 + 0x1afc));
  uVar3 = zz_0298b40_(param_9,*(int *)(param_9 + 0x1af8));
  uVar4 = zz_0298b40_(param_9,*(int *)(param_9 + 0x1b00));
  if (((uVar4 | uVar2 | uVar3) != 1) &&
     (iVar5 = zz_0298b40_(param_9,*(int *)(param_9 + 0x1af4)), iVar5 == 1)) {
    iVar5 = *(int *)(param_9 + 8);
    iVar8 = *(int *)(param_9 + 0x9f8);
    if (iVar5 < 1) {
      iVar5 = *(int *)(param_9 + *(int *)(param_9 + 0x1af4) * 0x74 + 0x115c);
    }
    if (iVar5 < 1) {
      iVar5 = iVar8;
    }
    if (iVar5 < iVar8) {
      iVar8 = iVar5;
    }
    iVar5 = zz_0298c84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0);
    if (iVar8 <= iVar5) {
      zz_0298b50_(param_9,*(int *)(param_9 + 0x1afc),1);
      zz_0298b50_(param_9,*(int *)(param_9 + 0x1af8),1);
      zz_0298b50_(param_9,*(int *)(param_9 + 0x1b00),1);
    }
  }
  puVar7 = *(undefined4 **)(param_9 + 0x1aec);
  piVar9 = (int *)*puVar7;
  zz_027dbb8_(piVar9,aiStack_68);
  if ((local_60 != -1) && (0 < local_60)) {
    *(int *)(param_9 + 0x924) = local_60;
  }
  zz_027db0c_(piVar9,aiStack_5c,1);
  if (local_4c != -1) {
    *(int *)(param_9 + 0x928) = local_4c;
  }
  if (*(int *)(param_9 + 0x930) == -1) {
    *(undefined4 *)(param_9 + 0x930) = puVar7[2];
  }
  if (*(int *)(param_9 + 0x934) == -1) {
    *(undefined4 *)(param_9 + 0x934) = puVar7[1];
  }
  iVar8 = *(int *)(param_9 + 0x1aec);
  iVar5 = cTeam__GetPlayer_int_(param_9,6);
  if (((iVar5 == 1) && (*(int *)(iVar8 + 8) == 0)) && (iVar5 = zz_02a53e8_(param_9,6), iVar5 != 0))
  {
    zz_02a39d8_(param_9,6,0);
  }
  iVar5 = cTeam__GetPlayer_int_(param_9,5);
  if (((iVar5 == 1) && (*(int *)(iVar8 + 4) == 0)) && (iVar5 = zz_02a53e8_(param_9,7), iVar5 != 0))
  {
    zz_02a39d8_(param_9,5,0);
  }
  if (*(int *)(param_9 + 0x2898) == 0) {
    piVar9 = (int *)0x0;
  }
  else if (*(int *)(*(int *)(param_9 + 0x1aec) + 0x14) < 1) {
    piVar9 = (int *)(*(int *)(param_9 + 0x2898) + 0x8a0);
  }
  else {
    piVar9 = (int *)0x0;
  }
  if (piVar9 != (int *)0x0) {
    iVar5 = *(int *)(param_9 + 0x1aec);
    if ((*(int *)(iVar5 + 0x10) != 0x7fffffff) &&
       (*(int *)(param_9 + 0xdd8) = *(int *)(iVar5 + 0x10) - piVar9[6], *piVar9 == 0)) {
      piVar9[1] = *(int *)(param_9 + 0x924) * 0x32;
      piVar9[2] = *(int *)(param_9 + 0x928);
      piVar9[3] = *(int *)(iVar5 + 4);
      piVar9[4] = *(int *)(iVar5 + 8);
      piVar9[5] = *(int *)(param_9 + 0xdd4);
      piVar9[6] = *(int *)(iVar5 + 0xc);
      piVar9[7] = *(int *)(iVar5 + 0x20);
      piVar9[8] = *(int *)(iVar5 + 0x24);
    }
  }
  return;
}



// ==== 8029b568  zz_029b568_ ====

undefined4 zz_029b568_(int param_1,int *param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *(int *)(param_1 + 0x1aec);
  iVar6 = *(int *)(param_1 + 0x1af4);
  iVar8 = *(int *)(param_1 + 0x28);
  if (param_3 < 4) {
    iVar2 = 0;
  }
  else {
    iVar2 = zz_027d944_(param_2);
    if (iVar2 == 0x80000) {
      if (*(int *)(param_1 + 0x1b04) < 0) {
        iVar3 = zz_0298d18_(param_1,iVar6);
        *(int *)(param_1 + 0x1b04) = iVar3 + 4;
      }
      *(undefined4 *)(iVar7 + 0x30) = 1;
    }
    else if (iVar2 != 0) {
      *(undefined4 *)(iVar7 + 0x30) = 0;
    }
  }
  if (iVar2 == 0x80000) {
    uVar4 = zz_029a03c_(param_1);
    if ((uVar4 == 0) && (iVar7 = zz_0299fe4_(param_1), iVar7 == 0)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1afc),1);
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1af8),1);
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1b00),1);
    uVar5 = 0;
  }
  else if ((param_4 < 4) && (iVar6 = zz_0298b20_(param_1,iVar6), iVar6 == 1)) {
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1afc),1);
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1af8),1);
    zz_0298b30_(param_1,*(int *)(param_1 + 0x1b00),1);
    uVar5 = 0;
  }
  else if (param_3 < iVar8) {
    if (iVar2 == 0x10000) {
      uVar5 = 0;
    }
    else {
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 1;
  }
  return uVar5;
}



// ==== 8029b714  FUN_8029b714 ====

int FUN_8029b714(int param_1,int param_2,void *param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  size_t sVar4;
  int local_78;
  void *local_74;
  size_t local_70;
  void *local_6c;
  size_t local_68;
  void *local_64;
  size_t local_60;
  void *local_5c;
  size_t local_58;
  int *local_54;
  code *local_50;
  code *local_4c;
  undefined4 local_48;
  int *local_44;
  code *local_40;
  code *local_3c;
  undefined4 local_38;
  
  iVar2 = zz_029a928_(param_1,param_2,(int)param_3,param_4,&local_78);
  if (iVar2 == 0) {
    if (*(int *)(param_1 + 0x1b00) == 8) {
      iVar2 = 1;
    }
    else {
      zz_0299458_(param_1,*(int *)(param_1 + 0x1b00),param_2,&local_54);
      if (local_54 == (int *)0x0) {
        iVar2 = 1;
      }
      else {
        iVar2 = (**(code **)(*local_54 + 0x24))(local_54,0);
        if (iVar2 < param_4) {
          iVar2 = 0;
        }
        else {
          (**(code **)(*local_54 + 0x18))(local_54,0,param_4,&local_6c);
          zz_027c990_(local_6c,param_3,local_68);
          (**(code **)(*local_54 + 0x20))(local_54,1,&local_6c);
          if (local_68 == 0) {
            iVar2 = 0;
          }
          else {
            sVar4 = param_4 - local_68;
            if (0 < (int)sVar4) {
              (**(code **)(*local_54 + 0x18))(local_54,0,sVar4,&local_74);
              zz_027c990_(local_74,(void *)((int)param_3 + local_68),local_70);
              (**(code **)(*local_54 + 0x20))(local_54,1,&local_74);
              if (local_70 != sVar4) {
                DAT_8041d450 = DAT_8041d450 + 1;
              }
            }
            iVar2 = 1;
          }
        }
        if (iVar2 == 1) {
          if (local_50 != (code *)0x0) {
            (*local_50)(param_1,param_2);
          }
          if (local_4c != (code *)0x0) {
            (*local_4c)(local_48,param_2);
          }
        }
      }
    }
  }
  else {
    if (((local_78 != 0) && (*(int *)(param_1 + 0x1b00) != 8)) &&
       (zz_0299458_(param_1,*(int *)(param_1 + 0x1b00),0,&local_44), local_44 != (int *)0x0)) {
      iVar3 = param_4 + 0x12;
      iVar2 = (**(code **)(*local_44 + 0x24))(local_44,0);
      if (iVar2 < iVar3) {
        bVar1 = false;
      }
      else {
        (**(code **)(*local_44 + 0x18))(local_44,0,iVar3,&local_5c);
        zz_027c990_(local_5c,(void *)((int)param_3 + -0x12),local_58);
        (**(code **)(*local_44 + 0x20))(local_44,1,&local_5c);
        if (local_58 == 0) {
          bVar1 = false;
        }
        else {
          sVar4 = iVar3 - local_58;
          if (0 < (int)sVar4) {
            (**(code **)(*local_44 + 0x18))(local_44,0,sVar4,&local_64);
            zz_027c990_(local_64,(void *)((int)param_3 + -0x12 + local_58),local_60);
            (**(code **)(*local_44 + 0x20))(local_44,1,&local_64);
            if (local_60 != sVar4) {
              DAT_8041d450 = DAT_8041d450 + 1;
            }
          }
          bVar1 = true;
        }
      }
      if (bVar1) {
        if (local_40 != (code *)0x0) {
          (*local_40)(param_1,0);
        }
        if (local_3c != (code *)0x0) {
          (*local_3c)(local_38,0);
        }
      }
    }
    iVar2 = 1;
  }
  return iVar2;
}



// ==== 8029ba78  FUN_8029ba78 ====

int FUN_8029ba78(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint param_10,char *param_11,size_t param_12,int param_13)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  int iVar9;
  undefined8 uVar10;
  int local_78;
  void *local_74;
  size_t local_70;
  int aiStack_6c [2];
  int local_64;
  int local_60;
  void *local_4c;
  size_t local_48;
  void *local_44;
  int local_40;
  
  iVar3 = cTeam__GetPlayer_int_(param_9,5);
  if (iVar3 == 0) {
    iVar3 = 1;
  }
  else {
    iVar3 = *(int *)(param_9 + 0x1aec);
    if (*(int *)(iVar3 + 0x28) == -1) {
      iVar4 = cTeam__GetPlayer_int_(param_9,0x3b);
      uVar2 = param_10;
      if (((iVar4 != 1) && (0 < iVar4)) && (iVar4 < 3)) {
        puVar7 = *(undefined4 **)(param_9 + 0x1aec);
        piVar8 = (int *)*puVar7;
        iVar9 = 0;
        iVar4 = 0;
        iVar6 = 0;
        do {
          zz_027db0c_(piVar8,aiStack_6c,iVar9);
          iVar1 = local_64;
          if (local_64 < iVar6) {
            iVar1 = iVar6;
          }
          iVar5 = local_60;
          if (local_60 < iVar4) {
            iVar5 = iVar4;
          }
          iVar9 = iVar9 + 1;
          iVar4 = iVar5;
          iVar6 = iVar1;
        } while (iVar9 < 3);
        puVar7[2] = iVar1;
        puVar7[1] = iVar5;
        if (1 < (int)puVar7[1]) {
          uVar2 = 2;
        }
      }
      *(uint *)(iVar3 + 0x28) = uVar2;
    }
    if (*(int *)(iVar3 + 0x20) == -1) {
      *(uint *)(iVar3 + 0x20) = param_10;
    }
    iVar4 = cTeam__GetPlayer_int_(param_9,0x1d);
    if (iVar4 != -1) {
      iVar6 = cTeam__GetPlayer_int_(param_9,0x37);
      if (iVar6 == 0) {
        uVar2 = countLeadingZeros(*(int *)(iVar3 + 0x20) - param_10);
        uVar2 = uVar2 >> 5;
      }
      else {
        uVar2 = *(uint *)(iVar3 + 0x18) ^ param_10;
        uVar2 = ((int)uVar2 >> 1) - (uVar2 & *(uint *)(iVar3 + 0x18)) >> 0x1f;
      }
      if ((uVar2 != 0) && (*(int *)(iVar3 + 0x28) != iVar4)) {
        if ((int)param_12 < 4) {
          uVar2 = 0;
        }
        else if (*param_11 == '\0') {
          if (param_11[1] == '\0') {
            if (param_11[2] == '\x01') {
              if (param_11[3] == 0xb3) {
                uVar2 = 1;
              }
              else {
                uVar2 = countLeadingZeros(0xb8 - (uint)(byte)param_11[3]);
                uVar2 = uVar2 >> 5;
              }
            }
            else {
              uVar2 = 0;
            }
          }
          else {
            uVar2 = 0;
          }
        }
        else {
          uVar2 = 0;
        }
        if (uVar2 != 0) {
          *(int *)(iVar3 + 0x28) = iVar4;
        }
      }
    }
    *(uint *)(iVar3 + 0x18) = param_10;
    if (*(uint *)(iVar3 + 0x28) == param_10) {
      iVar4 = *(int *)(param_9 + 0x1af8);
      iVar3 = zz_02992ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          iVar4,&local_4c);
      if (iVar3 == 0) {
        if ((int)(local_48 + local_40) < (int)param_12) {
          iVar3 = 0;
        }
        else {
          if ((int)local_48 < (int)param_12) {
            zz_027c990_(local_4c,param_11,local_48);
            uVar10 = zz_027c990_(local_44,param_11 + local_48,param_12 - local_48);
          }
          else {
            uVar10 = zz_027c990_(local_4c,param_11,param_12);
          }
          iVar3 = zz_0299044_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9
                              ,iVar4,param_12);
          if (iVar3 == 0) {
            if (-1 < param_13) {
              local_74 = local_4c;
              local_78 = param_13;
              local_70 = param_12;
              iVar3 = zz_02a2fa4_(param_9,iVar4,&local_78);
              if (iVar3 != 0) {
                return iVar3;
              }
            }
            iVar3 = 1;
          }
        }
      }
    }
    else {
      iVar3 = 1;
    }
  }
  return iVar3;
}



// ==== 8029bd74  FUN_8029bd74 ====

int FUN_8029bd74(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint param_10,void *param_11,size_t param_12,int param_13)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  int local_58;
  void *local_54;
  size_t local_50;
  void *local_4c;
  size_t local_48;
  void *local_44;
  int local_40;
  
  iVar2 = cTeam__GetPlayer_int_(param_9,6);
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0x1aec);
    if (*(int *)(iVar2 + 0x2c) == -1) {
      *(uint *)(iVar2 + 0x2c) = param_10;
    }
    if (*(int *)(iVar2 + 0x24) == -1) {
      *(uint *)(iVar2 + 0x24) = param_10;
    }
    iVar3 = cTeam__GetPlayer_int_(param_9,0x1e);
    if (iVar3 != -1) {
      iVar4 = cTeam__GetPlayer_int_(param_9,0x37);
      if (iVar4 == 0) {
        uVar1 = countLeadingZeros(*(int *)(iVar2 + 0x24) - param_10);
        uVar1 = uVar1 >> 5;
      }
      else {
        uVar1 = *(uint *)(iVar2 + 0x1c) ^ param_10;
        uVar1 = ((int)uVar1 >> 1) - (uVar1 & *(uint *)(iVar2 + 0x1c)) >> 0x1f;
      }
      if (uVar1 != 0) {
        *(int *)(iVar2 + 0x2c) = iVar3;
      }
    }
    *(uint *)(iVar2 + 0x1c) = param_10;
    if (*(uint *)(iVar2 + 0x2c) == param_10) {
      if (-1 < param_13) {
        iVar3 = *(int *)(iVar2 + 0xc);
        if (param_13 < *(int *)(iVar2 + 0xc)) {
          iVar3 = param_13;
        }
        *(int *)(iVar2 + 0xc) = iVar3;
        iVar3 = *(int *)(iVar2 + 0x10);
        if (param_13 < *(int *)(iVar2 + 0x10)) {
          iVar3 = param_13;
        }
        *(int *)(iVar2 + 0x10) = iVar3;
        param_13 = param_13 - *(int *)(iVar2 + 0xc);
      }
      iVar3 = *(int *)(param_9 + 0x1afc);
      iVar2 = zz_02992ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          iVar3,&local_4c);
      if (iVar2 == 0) {
        if ((int)(local_48 + local_40) < (int)param_12) {
          iVar2 = 0;
        }
        else {
          if ((int)local_48 < (int)param_12) {
            zz_027c990_(local_4c,param_11,local_48);
            uVar5 = zz_027c990_(local_44,(void *)((int)param_11 + local_48),param_12 - local_48);
          }
          else {
            uVar5 = zz_027c990_(local_4c,param_11,param_12);
          }
          iVar2 = zz_0299044_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                              iVar3,param_12);
          if (iVar2 == 0) {
            if (-1 < param_13) {
              local_54 = local_4c;
              local_58 = param_13;
              local_50 = param_12;
              iVar2 = zz_02a2fa4_(param_9,iVar3,&local_58);
              if (iVar2 != 0) {
                return iVar2;
              }
            }
            iVar2 = 1;
          }
        }
      }
    }
    else {
      iVar2 = 1;
    }
  }
  return iVar2;
}



// ==== 8029bf74  zz_029bf74_ ====

int zz_029bf74_(int param_1,void *param_2,int param_3,int *param_4,int *param_5)

{
  int iVar1;
  undefined4 *puVar2;
  size_t sVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  code *pcVar7;
  void *local_58;
  size_t local_54;
  void *local_50;
  size_t local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_34;
  int local_2c;
  
  iVar5 = 0;
  *param_4 = 0;
  *param_5 = 0;
  puVar2 = *(undefined4 **)(param_1 + 0x1aec);
  iVar1 = zz_027d9dc_((int *)*puVar2,&local_48);
  if (iVar1 != 0) {
    iVar5 = zz_029abec_(param_1,-0xfff2fa);
  }
  if (local_2c < 0) {
    iVar5 = zz_029abec_(param_1,-0xfff2f2);
  }
  else if (local_2c == 0) {
    *param_4 = 0;
    *param_5 = 1;
    iVar5 = 0;
  }
  else if (param_3 < local_2c) {
    iVar5 = 0;
  }
  else {
    piVar4 = (int *)puVar2[local_48 + -0xaf];
    if (piVar4 == (int *)0x0) {
      iVar1 = (*(code *)(&PTR_FUN_802b8b90)[local_44])(param_1,local_40,param_2,local_2c,local_34);
      *param_5 = iVar1;
    }
    else {
      uVar6 = puVar2[0x52];
      pcVar7 = (code *)puVar2[0x51];
      iVar1 = (**(code **)(*piVar4 + 0x24))(piVar4,0);
      if (iVar1 < local_2c) {
        iVar1 = 0;
      }
      else {
        (**(code **)(*piVar4 + 0x18))(piVar4,0,local_2c,&local_50);
        zz_027c990_(local_50,param_2,local_4c);
        (**(code **)(*piVar4 + 0x20))(piVar4,1,&local_50);
        if (local_4c == 0) {
          iVar1 = 0;
        }
        else {
          sVar3 = local_2c - local_4c;
          if (0 < (int)sVar3) {
            (**(code **)(*piVar4 + 0x18))(piVar4,0,sVar3,&local_58);
            zz_027c990_(local_58,(void *)((int)param_2 + local_4c),local_54);
            (**(code **)(*piVar4 + 0x20))(piVar4,1,&local_58);
            if (local_54 != sVar3) {
              DAT_8041d450 = DAT_8041d450 + 1;
            }
          }
          iVar1 = 1;
        }
      }
      if ((iVar1 == 1) && (pcVar7 != (code *)0x0)) {
        (*pcVar7)(uVar6,local_48);
      }
      *param_5 = iVar1;
    }
    iVar1 = *param_5;
    if (iVar1 == 1) {
      *param_4 = local_2c;
    }
    else if ((0 < iVar1) || (iVar1 < 0)) {
      iVar5 = iVar1;
    }
  }
  return iVar5;
}



// ==== 8029c1e4  zz_029c1e4_ ====

int zz_029c1e4_(int param_1,int *param_2,size_t param_3,int *param_4,int param_5)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  size_t sVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int local_48;
  int local_44;
  int local_40;
  uint local_3c;
  int aiStack_38 [2];
  int local_30;
  int local_2c;
  
  iVar10 = 0;
  *param_4 = 0;
  piVar8 = (int *)**(undefined4 **)(param_1 + 0x1aec);
  iVar3 = zz_029b568_(param_1,param_2,param_3,param_5);
  if (iVar3 == 0) {
    return 0;
  }
  iVar3 = zz_027d6ec_(piVar8,param_2,param_3,&local_40,&local_3c);
  if (iVar3 != 0) {
    iVar10 = zz_029abec_(param_1,-0xfff2fd);
  }
  if ((local_3c & 0x20000) != 0) {
    if (*(int *)(param_1 + 0x2898) == 0) {
      piVar5 = (int *)0x0;
    }
    else if (*(int *)(*(int *)(param_1 + 0x1aec) + 0x14) < 1) {
      piVar5 = (int *)(*(int *)(param_1 + 0x2898) + 0x8a0);
    }
    else {
      piVar5 = (int *)0x0;
    }
    if ((piVar5 != (int *)0x0) && (*piVar5 == 0)) {
      piVar9 = piVar5 + 9;
      zz_027da74_(piVar8,aiStack_38);
      sVar6 = 0xb0;
      if ((int)param_3 < 0xb0) {
        sVar6 = param_3;
      }
      if (local_2c < 1) {
        if (local_30 < 1) goto LAB_8029c308;
        piVar5[0x62] = sVar6;
        piVar9 = piVar5 + 0x35;
      }
      else {
        piVar5[0x61] = sVar6;
      }
      zz_027c990_(piVar9,param_2,sVar6);
    }
  }
LAB_8029c308:
  if ((local_3c == 0x80000) && (uVar4 = zz_029a03c_(param_1), uVar4 != 0)) {
    *(int *)(*(int *)(param_1 + 0x1aec) + 0x14) = *(int *)(*(int *)(param_1 + 0x1aec) + 0x14) + 1;
    *param_4 = 4;
    return iVar10;
  }
  if ((local_3c == 0x80000) && (iVar3 = zz_0299fe4_(param_1), iVar3 != 0)) {
    *param_4 = 4;
    return iVar10;
  }
  if (local_3c != 0) {
    if ((local_3c & 0x40000) == 0) {
      iVar3 = zz_029abec_(param_1,-0xfff2fb);
      return iVar3;
    }
    iVar3 = zz_029bf74_(param_1,(void *)((int)param_2 + local_40),param_3 - local_40,&local_44,
                        &local_48);
    if (local_48 != 1) {
      return iVar3;
    }
    *param_4 = local_40 + local_44;
    return iVar3;
  }
  iVar3 = *(int *)(param_1 + 0x28);
  if (iVar3 + 3 <= (int)param_3) {
    piVar8 = param_2;
    iVar7 = iVar3;
    if (0 < iVar3) {
      do {
        cVar1 = *(char *)piVar8;
        piVar8 = (int *)((int)piVar8 + 1);
        if (cVar1 != '\0') {
          bVar2 = false;
          goto LAB_8029c3bc;
        }
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    bVar2 = true;
LAB_8029c3bc:
    if (bVar2) goto LAB_8029c47c;
  }
  iVar3 = 0;
  for (; 3 < (int)param_3; param_3 = param_3 - 1) {
    uVar4 = zz_027d944_(param_2);
    if ((uVar4 & 0xd0000) != 0) goto LAB_8029c47c;
    iVar3 = iVar3 + 1;
    param_2 = (int *)((int)param_2 + 1);
  }
  if ((0 < (int)param_3) && ((int)param_3 < 4)) {
    iVar7 = param_1 + *(int *)(param_1 + 0x1af4) * 0x74;
    if ((*(int *)(iVar7 + 0x1150) == 0) &&
       ((*(int *)(iVar7 + 0x1160) != 0 || (*(int *)(iVar7 + 0x1164) != 0)))) {
      bVar2 = false;
    }
    else if ((int)param_2 + param_3 == *(int *)(iVar7 + 0x1158) + *(int *)(iVar7 + 0x115c)) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      iVar3 = iVar3 + param_3;
    }
  }
LAB_8029c47c:
  *param_4 = iVar3;
  return iVar10;
}



// ==== 8029c500  zz_029c500_ ====

int zz_029c500_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  size_t unaff_r28;
  int *unaff_r29;
  int iVar6;
  int unaff_r31;
  int local_48;
  int *local_44;
  size_t local_40;
  int local_38;
  
  uVar1 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1afc));
  uVar2 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1af8));
  uVar3 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1b00));
  if ((uVar3 & uVar1 & uVar2) == 1) {
    iVar4 = 0;
  }
  else {
    iVar4 = 0;
    for (iVar6 = 0; iVar6 < 0x7fffffff; iVar6 = iVar6 + local_48) {
      iVar4 = zz_0299180_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *(int *)(param_9 + 0x1af4),&local_44);
      if (iVar4 == 0) {
        iVar4 = 0;
        unaff_r31 = local_40 + local_38;
        unaff_r28 = local_40;
        unaff_r29 = local_44;
      }
      if (((iVar4 != 0) ||
          (iVar4 = zz_029c1e4_(param_9,unaff_r29,unaff_r28,&local_48,unaff_r31), iVar4 != 0)) ||
         (local_48 == 0)) break;
      iVar5 = zz_0298df8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          *(int *)(param_9 + 0x1af4),local_48);
      iVar4 = 0;
      if (iVar5 != 0) {
        iVar4 = iVar5;
      }
      if (iVar4 != 0) break;
    }
    if (*(int *)(param_9 + 0x48) == 2) {
      zz_029b26c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
  }
  return iVar4;
}



// ==== 8029c630  FUN_8029c630 ====

void FUN_8029c630(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  zz_029c500_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8029c650  FUN_8029c650 ====

undefined4 FUN_8029c650(void)

{
  zz_027df88_();
  return 0;
}



// ==== 8029c674  FUN_8029c674 ====

/* WARNING: Removing unreachable block (ram,0x8029c68c) */
/* WARNING: Removing unreachable block (ram,0x8029c6ac) */

int FUN_8029c674(void)

{
  int iVar1;
  
  iVar1 = zz_027e06c_(0x20,(undefined4 *)&DAT_8041d454);
  if (iVar1 == 0) {
    iVar1 = 0;
    DAT_8041d450 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfff2ff);
  }
  return iVar1;
}



// ==== 8029c700  FUN_8029c700 ====

int FUN_8029c700(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int iStack_28;
  int *local_24;
  int local_20;
  
  bVar1 = false;
  piVar5 = *(int **)(param_1 + 0x1b30);
  if (*(int *)(param_1 + 0x2898) == 0) {
    piVar4 = (int *)0x0;
  }
  else if (piVar5[0x22] < 1) {
    piVar4 = (int *)(*(int *)(param_1 + 0x2898) + 0xac4);
  }
  else {
    piVar4 = (int *)0x0;
  }
  if (piVar4 == (int *)0x0) {
    iVar2 = 0;
  }
  else if (*piVar4 == 0) {
    iVar2 = 0;
  }
  else {
    iVar3 = *piVar5;
    local_24 = piVar4 + 0xd;
    iVar2 = piVar4[4];
    *(int *)(param_1 + 0xcdc) = piVar4[3];
    *(int *)(param_1 + 0xce0) = iVar2;
    iVar2 = piVar4[6];
    *(int *)(param_1 + 0xce4) = piVar4[5];
    *(int *)(param_1 + 0xce8) = iVar2;
    iVar2 = piVar4[8];
    *(int *)(param_1 + 0xcec) = piVar4[7];
    *(int *)(param_1 + 0xcf0) = iVar2;
    iVar2 = piVar4[10];
    *(int *)(param_1 + 0xcf4) = piVar4[9];
    *(int *)(param_1 + 0xcf8) = iVar2;
    iVar2 = piVar4[0xc];
    *(int *)(param_1 + 0xcfc) = piVar4[0xb];
    *(int *)(param_1 + 0xd00) = iVar2;
    local_20 = piVar4[0x8d];
    iVar2 = zz_0283224_(iVar3,&local_24,&iStack_28);
    if (iVar2 == 0) {
      bVar1 = true;
      iVar2 = 0;
    }
    else {
      iVar2 = zz_029abec_(param_1,-0xfff0e5);
    }
  }
  if (iVar2 == 0) {
    piVar5[0x1d] = 2;
    if ((bVar1) && (iVar2 = cTeam__GetPlayer_int_(param_1,0x30), iVar2 != 0)) {
      piVar5[0x1e] = 200;
    }
    else {
      piVar5[0x1e] = 0xc0;
    }
    iVar2 = 0;
  }
  return iVar2;
}



// ==== 8029c86c  FUN_8029c86c ====

int FUN_8029c86c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = zz_029aac8_();
  iVar2 = *(int *)(param_9 + 0x1b30);
  piVar1 = *(int **)(param_9 + *(int *)(param_9 + 0x1b3c) * 0x74 + 0x1160);
  if (*piVar1 == 1) {
    if (piVar1 + 1 == param_10) {
      *piVar1 = 0;
      uVar3 = zz_02a0a40_(*(int **)(iVar2 + 0x70));
      iVar2 = 0;
    }
    else {
      iVar2 = zz_029abec_(param_9,-0xfff0f1);
    }
  }
  else {
    iVar2 = zz_029abec_(param_9,-0xfff0f2);
  }
  zz_029aa9c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return iVar2;
}



// ==== 8029c924  zz_029c924_ ====

void zz_029c924_(int param_1,int param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = *(int *)(param_1 + 0x1b30);
  puVar2 = *(undefined4 **)(param_1 + *(int *)(param_1 + 0x1b3c) * 0x74 + 0x1160);
  *param_3 = (int)(puVar2 + 1);
  *puVar2 = 1;
  *(int *)(iVar1 + 0x70) = param_2;
  *(undefined4 *)*param_3 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(*param_3 + 4) = *(undefined4 *)(param_2 + 0x2c);
  *(undefined4 *)(*param_3 + 8) = *(undefined4 *)(param_2 + 0x30);
  *(undefined4 *)(*param_3 + 0xc) = *(undefined4 *)(param_2 + 0x34);
  *(undefined4 *)(*param_3 + 0x10) = *(undefined4 *)(param_2 + 0x40);
  *(undefined4 *)(*param_3 + 0x14) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(*param_3 + 0x18) = *(undefined4 *)(param_2 + 0xc);
  *(undefined4 *)(*param_3 + 0x1c) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(*param_3 + 0x20) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(*param_3 + 0x24) = *(undefined4 *)(param_2 + 0x10);
  *(undefined4 *)(*param_3 + 0x28) = *(undefined4 *)(param_2 + 0x14);
  *(undefined4 *)(*param_3 + 0x2c) = *(undefined4 *)(param_2 + 0x18);
  *(undefined4 *)(*param_3 + 0x30) = *(undefined4 *)(param_2 + 0x1c);
  *(undefined4 *)(*param_3 + 0x34) = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(*param_3 + 0x38) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(*param_3 + 0x3c) = *(undefined4 *)(param_2 + 0x5c);
  *(undefined4 *)(*param_3 + 0x40) = *(undefined4 *)(param_2 + 0x60);
  *(undefined4 *)(*param_3 + 0x44) = *(undefined4 *)(param_2 + 100);
  *(undefined4 *)(*param_3 + 0x48) = *(undefined4 *)(param_2 + 0x68);
  *(undefined4 *)(*param_3 + 0x4c) = *(undefined4 *)(param_2 + 0x6c);
  *(undefined4 *)(*param_3 + 0x50) = *(undefined4 *)(param_2 + 0x70);
  *(undefined4 *)(*param_3 + 0x54) = *(undefined4 *)(param_2 + 0x74);
  return;
}



// ==== 8029ca58  FUN_8029ca58 ====

undefined4
FUN_8029ca58(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            int *param_10)

{
  int iVar1;
  int *piVar2;
  undefined4 auStack_18 [4];
  
  iVar1 = zz_02a0b30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if (iVar1 == -1) {
    *param_10 = 0;
  }
  else {
    piVar2 = zz_02a091c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         auStack_18);
    if (piVar2 == (int *)0x0) {
      *param_10 = 0;
    }
    else {
      zz_029c924_(param_9,(int)piVar2,param_10);
      *(undefined4 *)(param_9 + 0xef8) = *(undefined4 *)(*param_10 + 0x14);
      *(undefined4 *)(param_9 + 0xefc) = *(undefined4 *)(*param_10 + 0x18);
    }
  }
  return 0;
}



// ==== 8029caf4  FUN_8029caf4 ====

void FUN_8029caf4(int param_1)

{
  zz_029abec_(param_1,-0xfff0f3);
  return;
}



// ==== 8029cb1c  FUN_8029cb1c ====

void FUN_8029cb1c(int param_1)

{
  zz_029abec_(param_1,-0xfff0f3);
  return;
}



// ==== 8029cb6c  FUN_8029cb6c ====

int FUN_8029cb6c(int param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 0x1b30);
  iVar1 = *piVar2;
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    DAT_8041ecb4 = piVar2[1];
    DAT_8041ecb8 = piVar2[2];
    DAT_8041ecbc = piVar2[3];
    DAT_8041ecc0 = piVar2[4];
    DAT_8041ecc4 = piVar2[5];
    DAT_8041ecc8 = piVar2[6];
    DAT_8041eccc = piVar2[7];
    DAT_8041ecd0 = piVar2[8];
    DAT_8041ecd4 = piVar2[9];
    gnt4_memcpy(&DAT_8041ecac,piVar2 + 10,8);
    gnt4_memcpy(&DAT_8041ec6c,piVar2 + 0xc,0x40);
    iVar1 = zz_0283bd4_(iVar1);
    if (iVar1 == 0) {
      iVar1 = 0;
      *piVar2 = 0;
    }
    else {
      iVar1 = zz_029abec_(param_1,-0xfff0f4);
    }
  }
  return iVar1;
}



// ==== 8029cc64  FUN_8029cc64 ====

void FUN_8029cc64(int param_1,int param_2)

{
  if (param_2 != -1) {
    if (param_2 < -1) {
      if (-4 < param_2) {
        return;
      }
    }
    else if (param_2 < 1) {
      return;
    }
  }
  zz_029abec_(param_1,param_2);
  return;
}



// ==== 8029cca8  zz_029cca8_ ====

int zz_029cca8_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  uVar1 = DAT_8041ecb8;
  piVar5 = (int *)0x8041ec68;
  if ((DAT_8041ecd0 < 1) || (0x10 < DAT_8041ecd0)) {
    iVar2 = -1;
    goto LAB_8029cd5c;
  }
  if ((DAT_8041ecc4 == 0) || (DAT_8041ecd4 == 0)) {
    if (DAT_8041ecac == 0) {
      iVar2 = -1;
      goto LAB_8029cd5c;
    }
    if (DAT_8041ecb0 == 0) {
      iVar2 = -1;
      goto LAB_8029cd5c;
    }
    iVar2 = DAT_8041ecd0;
    if (0 < DAT_8041ecd0) {
      do {
        piVar5 = piVar5 + 1;
        if (*piVar5 == 0) {
          iVar2 = -1;
          goto LAB_8029cd5c;
        }
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  iVar2 = 0;
LAB_8029cd5c:
  if (iVar2 == 0) {
    param_2[1] = DAT_8041ecb4;
    param_2[2] = uVar1;
    uVar1 = DAT_8041ecc0;
    param_2[3] = DAT_8041ecbc;
    param_2[4] = uVar1;
    uVar1 = DAT_8041ecc8;
    param_2[5] = DAT_8041ecc4;
    param_2[6] = uVar1;
    iVar2 = DAT_8041ecd0;
    param_2[7] = DAT_8041eccc;
    param_2[8] = iVar2;
    param_2[9] = DAT_8041ecd4;
    gnt4_memcpy(param_2 + 10,&DAT_8041ecac,8);
    gnt4_memcpy(param_2 + 0xc,&DAT_8041ec6c,0x40);
    *param_2 = 0;
    iVar2 = 0;
    param_2[0x1c] = 0;
    puVar4 = param_2 + 0x4e;
    param_2[0x1d] = 5;
    param_2[0x1e] = 0xc0;
    param_2[0x40] = 0;
    param_2[0x41] = 1;
    param_2[0x1f] = 0;
    param_2[0x20] = 0;
    param_2[0x4a] = 0;
    param_2[0x4b] = 0;
    param_2[0x4c] = 0;
    puVar3 = param_2;
    do {
      *puVar4 = 0;
      puVar4[1] = puVar3[0xc];
      puVar4[2] = 0;
      puVar4[3] = 1;
      puVar4[4] = 0;
      puVar4[5] = 0;
      puVar4[6] = 0;
      puVar4[7] = 0;
      puVar4[8] = 0;
      zz_02a94c4_((int)(puVar4 + 10),0xffffffff,0x14);
      iVar2 = iVar2 + 1;
      puVar4 = puVar4 + 0x1e;
      puVar3 = puVar3 + 1;
    } while (iVar2 < 0x10);
    param_2[0x21] = 0;
    param_2[0x22] = 0;
    zz_02a94c4_((int)(param_2 + 0x23),0xffffffff,0x14);
    param_2[0x37] = 0xffffffff;
    param_2[0x38] = 0;
    param_2[0x39] = 0x7fffffff;
    param_2[0x3a] = 0;
    iVar2 = 0;
    param_2[0x3b] = 0;
    param_2[0x3c] = 0;
    param_2[0x3d] = 0xffffffff;
    param_2[0x3e] = 0;
    param_2[0x3f] = 0xffffffff;
    param_2[0x22e] = 0;
    param_2[0x22f] = 0;
    param_2[0x230] = 0;
    param_2[0x231] = 0;
    param_2[0x232] = 0;
    param_2[0x233] = 0;
    param_2[0x234] = 0;
    param_2[0x235] = 0;
    param_2[0x236] = 0;
    param_2[0x237] = 0;
    param_2[0x238] = 0;
    param_2[0x239] = 0;
    param_2[0x23a] = 0;
    param_2[0x23b] = 0;
    param_2[0x23c] = 0;
    param_2[0x23d] = 0;
    param_2[0x23e] = 0;
    param_2[0x23f] = 0;
    param_2[0x240] = 0;
    param_2[0x241] = 0;
    param_2[0x242] = 0;
    param_2[0x243] = 0;
    param_2[0x244] = 0;
    param_2[0x245] = 0;
    param_2[0x246] = 0;
    param_2[0x247] = 0;
    param_2[0x248] = 0;
    param_2[0x249] = 0;
    param_2[0x24a] = 0;
    param_2[0x24b] = 0;
    param_2[0x24c] = 0;
    param_2[0x24d] = 0;
    param_2[0x24e] = 0;
    param_2[0x24f] = 0;
    param_2[0x250] = 0;
    param_2[0x251] = 0;
    param_2[0x252] = 0;
    param_2[0x57] = param_2 + 0x233;
    param_2[0x75] = param_2 + 0x235;
    param_2[0x93] = param_2 + 0x237;
    param_2[0xb1] = param_2 + 0x239;
    param_2[0xcf] = param_2 + 0x23b;
    param_2[0xed] = param_2 + 0x23d;
    param_2[0x10b] = param_2 + 0x23f;
    param_2[0x129] = param_2 + 0x241;
    param_2[0x147] = param_2 + 0x243;
    param_2[0x165] = param_2 + 0x245;
    param_2[0x183] = param_2 + 0x247;
    param_2[0x1a1] = param_2 + 0x249;
    param_2[0x1bf] = param_2 + 0x24b;
    param_2[0x1dd] = param_2 + 0x24d;
    param_2[0x1fb] = param_2 + 0x24f;
    param_2[0x219] = param_2 + 0x251;
  }
  else {
    iVar2 = zz_029abec_(param_1,-0xfff0eb);
  }
  return iVar2;
}



// ==== 8029cfec  FUN_8029cfec ====

int FUN_8029cfec(int param_1)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int *piVar4;
  
  iVar1 = cTeam__GetPlayer_int_(param_1,5);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    piVar4 = (int *)(param_1 + 0x1e50);
    *(int **)(param_1 + 0x1b30) = piVar4;
    iVar1 = zz_029cca8_(param_1,piVar4);
    if (iVar1 == 0) {
      iVar1 = zz_0283f10_();
      if (iVar1 == 0) {
        iVar1 = zz_029abec_(param_1,-0xfff0f6);
      }
      else {
        iVar2 = zz_0281750_(iVar1,FUN_8029cc64,param_1);
        if (iVar2 == 0) {
          puVar3 = (undefined *)cTeam__GetPlayer_int_(param_1,0);
          zz_0283af0_(iVar1,1,puVar3);
          puVar3 = (undefined *)cTeam__GetPlayer_int_(param_1,1);
          zz_0283af0_(iVar1,2,puVar3);
          zz_0283af0_(iVar1,3,(undefined *)0x0);
          zz_0283af0_(iVar1,4,(undefined *)0x0);
          zz_0283af0_(iVar1,5,(undefined *)0x0);
          zz_0283af0_(iVar1,6,*(undefined **)(param_1 + 0x38));
          zz_0283af0_(iVar1,7,(undefined *)0x7fffffff);
          zz_0283af0_(iVar1,8,(undefined *)0x0);
          zz_0283af0_(iVar1,9,(undefined *)0x0);
          *piVar4 = iVar1;
          iVar1 = 0;
        }
        else {
          zz_0283bd4_(iVar1);
          iVar1 = zz_029abec_(param_1,-0xfff0f5);
        }
      }
    }
  }
  return iVar1;
}



// ==== 8029d164  zz_029d164_ ====

undefined4
zz_029d164_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int *param_10,int *param_11,int *param_12)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined2 uVar8;
  int *piVar7;
  int *piVar9;
  undefined2 uVar10;
  int iVar11;
  int iVar12;
  
  iVar11 = *(int *)(param_9 + 0x1b30);
  if (*(int *)(iVar11 + 0x130) == 0) {
    piVar7 = zz_02a0aa8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *param_12 = (int)piVar7;
    if (*param_12 == 0) {
      *(undefined4 *)(param_9 + 0x970) = 1;
      return 0xffffffff;
    }
  }
  else {
    *param_12 = *(int *)(iVar11 + 0x130);
  }
  piVar7 = param_10 + -1;
  piVar9 = (int *)(*param_12 + 0x24);
  iVar12 = 10;
  do {
    piVar1 = piVar7 + 1;
    piVar7 = piVar7 + 2;
    iVar3 = *piVar7;
    piVar9[1] = *piVar1;
    piVar9 = piVar9 + 2;
    *piVar9 = iVar3;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  if (*(int *)(param_9 + 0x38) == 3) {
    if (((param_10[6] == 1) || (param_10[6] == 2)) && (*(int *)(iVar11 + 0x130) == 0)) {
      zz_02a0a14_(*(int **)(iVar11 + 0x128));
      *(undefined4 *)(iVar11 + 0x128) = *(undefined4 *)(iVar11 + 300);
      *(int *)(iVar11 + 300) = *param_12;
    }
    uVar4 = *param_10 + 0xf;
    uVar5 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
    uVar4 = param_10[1] + 0xf;
    iVar12 = uVar5 * 0x10;
    uVar6 = iVar12 + 0x1f;
    uVar5 = ((int)((uVar5 >> 0x1b & 1) + iVar12) >> 1) + 0x1f;
    iVar12 = (((int)uVar6 >> 5) + (uint)((int)uVar6 < 0 && (uVar6 & 0x1f) != 0)) * 0x20;
    uVar8 = (undefined2)iVar12;
    *(undefined2 *)((int)param_11 + 0xe) = uVar8;
    iVar3 = (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * 0x20;
    uVar10 = (undefined2)iVar3;
    *(undefined2 *)(param_11 + 3) = uVar10;
    uVar4 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
    iVar2 = uVar4 * 0x10;
    iVar12 = iVar2 * iVar12;
    param_11[2] = *(int *)(*(int *)(iVar11 + 0x128) + 4);
    iVar3 = ((int)((uVar4 >> 0x1b & 1) + iVar2) >> 1) * iVar3;
    *param_11 = param_11[2] + iVar12;
    param_11[1] = *param_11 + iVar3;
    *(undefined2 *)((int)param_11 + 0x1e) = uVar8;
    *(undefined2 *)(param_11 + 7) = uVar10;
    param_11[6] = *(int *)(*(int *)(iVar11 + 300) + 4);
    param_11[4] = param_11[6] + iVar12;
    param_11[5] = param_11[4] + iVar3;
  }
  else {
    if ((param_10[6] == 1) || (param_10[6] == 2)) {
      *(uint *)(iVar11 + 0x100) = *(uint *)(iVar11 + 0x100) ^ 1;
      *(uint *)(iVar11 + 0x104) = *(uint *)(iVar11 + 0x104) ^ 1;
    }
    piVar7 = (int *)(iVar11 + 0x108 + *(int *)(iVar11 + 0x100) * 0x10);
    iVar12 = piVar7[1];
    *param_11 = *piVar7;
    param_11[1] = iVar12;
    iVar12 = piVar7[3];
    param_11[2] = piVar7[2];
    param_11[3] = iVar12;
    piVar7 = (int *)(iVar11 + 0x108 + *(int *)(iVar11 + 0x104) * 0x10);
    iVar11 = piVar7[1];
    param_11[4] = *piVar7;
    param_11[5] = iVar11;
    iVar11 = piVar7[3];
    param_11[6] = piVar7[2];
    param_11[7] = iVar11;
  }
  param_11[8] = *(int *)(*param_12 + 4);
  param_11[9] = *param_12 + 0x28;
  param_11[10] = 0;
  param_11[0xb] = 0;
  *(undefined4 *)(param_9 + 0x970) = 0;
  return 0;
}



// ==== 8029d3b8  zz_029d3b8_ ====

int zz_029d3b8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int *param_10)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  int local_88;
  undefined4 local_84;
  undefined4 *local_80;
  int local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int aiStack_60 [10];
  int local_38;
  int local_34;
  
  piVar7 = *(int **)(param_9 + 0x1b30);
  iVar6 = *piVar7;
  iVar2 = zz_029d164_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      piVar7 + 0x23,aiStack_60,(int *)&local_80);
  if (iVar2 != 0) {
    return 0;
  }
  if (0 < piVar7[0x232]) {
    gnt4_memcpy(*(void **)local_80[9],(void *)piVar7[0x231],piVar7[0x232]);
    *(int *)(local_80[9] + 4) = piVar7[0x232];
  }
  if (*(int *)(param_9 + 0xda4) == 0) {
    local_7c = *(int *)(param_9 + 0xd58);
    bVar1 = false;
    local_78 = *(undefined4 *)(param_9 + 0xd5c);
    local_74 = *(undefined4 *)(param_9 + 0xd60);
    local_70 = *(undefined4 *)(param_9 + 0xd64);
    local_6c = *(undefined4 *)(param_9 + 0xd68);
    local_68 = *(undefined4 *)(param_9 + 0xd6c);
    local_64 = *(undefined4 *)(param_9 + 0xd70);
    iVar2 = *(int *)(*(int *)(param_9 + 0x1b30) + 0x74);
    if ((iVar2 != 4) && (iVar2 < 4)) {
      if (iVar2 == 2) {
        bVar1 = true;
      }
      else if (1 < iVar2) {
        bVar1 = true;
      }
    }
    if ((!bVar1) && (*(int *)(param_9 + 0x9b0) != 0)) {
      local_64 = 0;
    }
    zz_02a4570_(&local_7c,&local_88,&local_84);
    *(int *)(param_9 + 0xda8) = local_7c;
    *(undefined4 *)(param_9 + 0xdac) = local_78;
    *(undefined4 *)(param_9 + 0xdb0) = local_74;
    *(undefined4 *)(param_9 + 0xdb4) = local_70;
    *(undefined4 *)(param_9 + 0xdb8) = local_6c;
    *(undefined4 *)(param_9 + 0xdbc) = local_68;
    *(undefined4 *)(param_9 + 0xdc0) = local_64;
    *(int *)(param_9 + 0xdc4) = local_88 - *(int *)(param_9 + 0xcfc);
    *(undefined4 *)(param_9 + 0xdc8) = local_84;
    *(undefined4 *)(param_9 + 0xda4) = 1;
  }
  uVar8 = zz_02a9654_();
  iVar2 = zz_0276dfc_((int)param_10,0,1);
  iVar3 = zz_02818c0_(iVar6,param_10,aiStack_60);
  iVar4 = zz_0276dfc_((int)param_10,0,1);
  iVar4 = iVar4 - iVar2;
  uVar9 = zz_02a9654_();
  uVar5 = (uint)uVar9;
  zz_02a5f18_((int *)(param_9 + piVar7[0x29] * 0x20 + 0x28a8),uVar5,
              (int)((ulonglong)uVar9 >> 0x20) -
              ((uint)(uVar5 < (uint)uVar8) + (int)((ulonglong)uVar8 >> 0x20)),uVar5 - (uint)uVar8);
  *(int *)(param_9 + 0x998) = *(int *)(param_9 + 0x998) + local_38;
  *(int *)(param_9 + 0x99c) = *(int *)(param_9 + 0x99c) + local_34;
  if (iVar3 != -1) {
    if (iVar3 < -1) {
      if (iVar3 == -3) {
        if (iVar4 < 1) {
          iVar2 = zz_029abec_(param_9,-3);
        }
        else {
          iVar2 = 0;
        }
        goto LAB_8029d648;
      }
      if (-4 < iVar3) {
        if (iVar4 < 1) {
          iVar2 = zz_029abec_(param_9,-2);
        }
        else {
          iVar2 = 0;
        }
        goto LAB_8029d648;
      }
    }
    else if (iVar3 < 1) {
      iVar2 = 0;
      goto LAB_8029d648;
    }
  }
  iVar2 = zz_029abec_(param_9,-0xfff0fa);
LAB_8029d648:
  zz_0298c10_(param_9,*(int *)(param_9 + 0x1b38),iVar4);
  if (iVar2 == 0) {
    if (iVar4 < 1) {
      if (piVar7[0x4c] == 0) {
        zz_02a0a94_(local_80);
      }
    }
    else {
      GameInfoManager__SetUserSelectedCupSidekick_eSidekickID_(param_9,0);
      local_80[3] = *(undefined4 *)(param_9 + 0xd78);
      local_80[2] = *(int *)(param_9 + 0xde0) +
                    (*(int *)(param_9 + 0xd74) - *(int *)(param_9 + 0xdc4));
      local_80[7] = *(undefined4 *)(param_9 + 0xd74);
      local_80[8] = *(int *)(param_9 + 0xd74) + *(int *)(param_9 + 0xde0);
      if (*(int *)(param_9 + 0xf00) < (int)local_80[2]) {
        *(undefined4 *)(param_9 + 0xf00) = local_80[2];
        *(undefined4 *)(param_9 + 0xf04) = local_80[3];
      }
      local_80[6] = piVar7[0x22];
      local_80[4] = local_38;
      local_80[5] = local_34;
      if ((piVar7[0x30] == 3) || (piVar7[0x4c] != 0)) {
        piVar7[0x4c] = 0;
      }
      else {
        piVar7[0x4c] = (int)local_80;
      }
      if (piVar7[0x4c] == 0) {
        if ((*(int *)(param_9 + 0x38) == 3) && ((piVar7[0x29] == 1 || (piVar7[0x29] == 2)))) {
          zz_02a0a6c_(local_80);
        }
        else {
          zz_02a0a80_(local_80);
        }
        zz_0283ca4_(iVar6,(undefined4 *)(param_9 + 0x954),(undefined4 *)(param_9 + 0x958));
        zz_02a1b50_(param_9,1,piVar7[0x29]);
        piVar7[0x21] = 0;
      }
    }
    iVar2 = 0;
  }
  else {
    zz_02a0a94_(local_80);
  }
  return iVar2;
}



// ==== 8029d7c4  zz_029d7c4_ ====

int zz_029d7c4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,uint *param_10)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int local_38;
  int local_34;
  uint local_30;
  uint local_2c [4];
  
  iVar6 = *(int *)(param_9 + 0x1b30);
  iVar1 = cTeam__GetPlayer_int_(param_9,0x2f);
  if (iVar1 == 1) {
    return 1;
  }
  iVar1 = cTeam__GetPlayer_int_(param_9,0x27);
  if (iVar1 == 1) {
    return 0;
  }
  if (*(int *)(iVar6 + 0x130) != 0) {
    return 0;
  }
  iVar1 = *(int *)(iVar6 + 0xa4);
  if ((int)*(uint *)(param_9 + 0x28a0) < 0) {
    bVar2 = false;
  }
  else if (*(int *)(param_9 + 0xda4) == 0) {
    bVar2 = zz_02a9378_(*(uint *)(param_9 + 0x28a0),*(uint *)(param_9 + 0x28a4),
                        *(uint *)(param_9 + 0xd74),*(uint *)(param_9 + 0xd78));
    if (bVar2) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    iVar1 = 1;
    goto LAB_8029daf0;
  }
  if (iVar1 == 2) {
    iVar3 = *(int *)(param_9 + 0x9ac);
LAB_8029d8d4:
    if (iVar3 == 0) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
  }
  else {
    if (iVar1 < 2) {
      if (0 < iVar1) {
        iVar3 = *(int *)(param_9 + 0x9a8);
        goto LAB_8029d8d4;
      }
    }
    else if (iVar1 < 4) {
      iVar3 = *(int *)(param_9 + 0x9b0);
      goto LAB_8029d8d4;
    }
    bVar2 = true;
  }
  if (bVar2) {
    iVar1 = 1;
    goto LAB_8029daf0;
  }
  if (iVar1 == 3) {
    iVar3 = cTeam__GetPlayer_int_(param_9,7);
    if (iVar3 == 0) {
      iVar3 = zz_0281554_(*param_10,param_10[1],
                          *(int *)(param_9 + 0x914) * *(int *)(param_9 + 0x918));
      if (iVar3 != 0) {
        *(int *)(param_9 + 0x95c) = *(int *)(param_9 + 0x95c) + 1;
      }
    }
    else {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = 0;
  }
  if (iVar3 != 0) {
    iVar1 = 1;
    goto LAB_8029daf0;
  }
  iVar7 = *(int *)(param_9 + 0x1b30);
  bVar2 = false;
  iVar3 = *(int *)(iVar7 + 0x74);
  if ((iVar3 != 4) && (iVar3 < 4)) {
    if (iVar3 == 2) {
      if ((iVar1 == 2) || (iVar1 == 3)) {
        bVar2 = true;
      }
    }
    else if ((1 < iVar3) && (iVar1 == 3)) {
      bVar2 = true;
    }
  }
  if (bVar2) {
    iVar1 = 1;
    goto LAB_8029daf0;
  }
  if (*(int *)(param_9 + 0xda4) == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(param_9 + 0xde0) + (*(int *)(param_9 + 0xd74) - *(int *)(param_9 + 0xdc4));
  }
  uVar4 = *(uint *)(param_9 + 0xd78);
  if (*(code **)(param_9 + 0xcd8) == (code *)0x0) {
    if (iVar1 == 1) {
      param_1 = zz_02a4fa8_(param_9 + 0xcc0,iVar3);
LAB_8029da3c:
      iVar3 = zz_02a4f70_(param_9 + 0xcc0,iVar3);
    }
    else if (iVar1 == 2) goto LAB_8029da3c;
    iVar1 = zz_02a3cb0_(param_9);
    if ((iVar1 < 0x3e9) && (*(int *)(param_9 + 0xa38) <= *(int *)(iVar7 + 0x84))) {
      iVar1 = 0;
    }
    else {
      zz_02a4910_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  (int *)&local_30,local_2c);
      if ((int)local_30 < 0) {
        iVar1 = 0;
      }
      else {
        bVar2 = zz_02a9378_(local_30,local_2c[0],
                            iVar3 - (int)(uVar4 * *(int *)(param_9 + 0xa48)) /
                                    *(int *)(param_9 + 0xa4c),uVar4);
        if (bVar2) {
          iVar1 = 0;
        }
        else {
          iVar1 = 1;
          *(int *)(iVar7 + 0x84) = *(int *)(iVar7 + 0x84) + 1;
        }
      }
    }
  }
  else {
    iVar1 = (**(code **)(param_9 + 0xcd8))(param_9,iVar1,iVar3,uVar4);
  }
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
LAB_8029daf0:
  piVar5 = *(int **)(param_9 + 0x1b30);
  iVar3 = piVar5[0x1d];
  if (piVar5[0x38] != 0) {
    zz_0281a20_(*piVar5,&local_38,&local_34);
    if ((local_38 == 0) && (local_34 == 1)) {
      iVar3 = 2;
    }
    if (local_38 == 1) {
      iVar3 = 5;
    }
  }
  if (iVar1 == 1) {
    if ((*(int *)(iVar6 + 0xa4) == 1) || (*(int *)(iVar6 + 0xa4) == 2)) {
      iVar3 = 2;
    }
  }
  else if (iVar3 == 2) {
    iVar3 = 3;
  }
  else if (iVar3 == 3) {
    iVar3 = 5;
  }
  piVar5[0x1d] = iVar3;
  return iVar1;
}



// ==== 8029db98  zz_029db98_ ====

int zz_029db98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int *param_10)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  undefined4 *puVar24;
  int iVar25;
  int iVar26;
  undefined8 uVar27;
  
  iVar25 = *(int *)(param_9 + 0x1b30);
  uVar1 = *param_10 + 0xf;
  uVar9 = ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
  iVar15 = *(int *)(iVar25 + 0x20);
  uVar1 = param_10[1] + 0xf;
  iVar2 = uVar9 * 0x10;
  uVar12 = ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
  uVar5 = iVar2 + 0x1f;
  uVar7 = *(int *)(iVar25 + 0xc) + 0xf;
  iVar13 = uVar12 * 0x10;
  uVar1 = *(int *)(iVar25 + 0x10) + 0xf;
  iVar18 = (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * 0x20;
  puVar24 = (undefined4 *)(iVar25 + 0x138);
  uVar9 = ((int)((uVar9 >> 0x1b & 1) + iVar2) >> 1) + 0x1f;
  uVar5 = ((int)uVar7 >> 4) + (uint)((int)uVar7 < 0 && (uVar7 & 0xf) != 0);
  iVar2 = (((int)uVar9 >> 5) + (uint)((int)uVar9 < 0 && (uVar9 & 0x1f) != 0)) * 0x20;
  iVar17 = uVar5 * 0x10;
  uVar7 = ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
  uVar1 = iVar17 + 0x1f;
  iVar6 = uVar7 * 0x10;
  uVar5 = ((int)((uVar5 >> 0x1b & 1) + iVar17) >> 1) + 0x1f;
  iVar14 = ((int)((uVar12 >> 0x1b & 1) + iVar13) >> 1) * iVar2;
  iVar13 = iVar13 * iVar18;
  iVar8 = iVar13 + iVar14 * 2 + 0x20;
  iVar17 = iVar6 * (((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * 0x20 +
           ((int)((uVar7 >> 0x1b & 1) + iVar6) >> 1) *
           (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * 0x20 * 2 + 0x20;
  if (iVar17 * 2 < iVar8 * 2) {
    iVar2 = zz_029abec_(param_9,-0xfff0e9);
  }
  else {
    iVar6 = *(int *)(iVar25 + 0x24);
    if (iVar6 != 0) {
      iVar17 = iVar15 * iVar17;
      iVar16 = 1;
      iVar26 = 2;
      iVar4 = iVar8;
      do {
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + -1;
          break;
        }
        if (iVar17 < iVar4 + iVar8) break;
        iVar4 = iVar4 + iVar8 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 1;
          break;
        }
        iVar4 = iVar4 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 2;
          break;
        }
        iVar4 = iVar4 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 3;
          break;
        }
        iVar4 = iVar4 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 4;
          break;
        }
        iVar4 = iVar4 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 5;
          break;
        }
        iVar4 = iVar4 + iVar8;
        if (iVar17 < iVar4) {
          iVar16 = iVar16 + 6;
          break;
        }
        iVar4 = iVar4 + iVar8;
        iVar16 = iVar16 + 8;
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
      if (iVar16 < iVar15) {
        iVar2 = zz_029abec_(param_9,-0xfff0e9);
        return iVar2;
      }
      iVar17 = 0;
      *(int *)(iVar25 + 0x28) = *(int *)(iVar25 + 0x14);
      *(int *)(iVar25 + 0x2c) = *(int *)(iVar25 + 0x14) + iVar8;
      iVar15 = iVar16;
      if (0 < iVar16) {
        if (8 < iVar16) {
          uVar1 = iVar16 - 1U >> 3;
          iVar26 = 0;
          iVar4 = iVar25;
          if (0 < iVar16 + -8) {
            do {
              iVar19 = iVar17 + 3;
              *(int *)(iVar4 + 0x30) = iVar6 + iVar26;
              iVar20 = iVar17 + 4;
              iVar23 = iVar17 + 5;
              *(int *)(iVar4 + 0x34) = iVar6 + (iVar17 + 1) * iVar8;
              iVar22 = iVar17 + 6;
              iVar21 = iVar17 + 7;
              iVar26 = iVar26 + iVar8 * 8;
              *(int *)(iVar4 + 0x38) = iVar6 + (iVar17 + 2) * iVar8;
              iVar17 = iVar17 + 8;
              *(int *)(iVar4 + 0x3c) = iVar6 + iVar19 * iVar8;
              *(int *)(iVar4 + 0x40) = iVar6 + iVar20 * iVar8;
              *(int *)(iVar4 + 0x44) = iVar6 + iVar23 * iVar8;
              *(int *)(iVar4 + 0x48) = iVar6 + iVar22 * iVar8;
              *(int *)(iVar4 + 0x4c) = iVar6 + iVar21 * iVar8;
              iVar4 = iVar4 + 0x20;
              uVar1 = uVar1 - 1;
            } while (uVar1 != 0);
          }
        }
        iVar19 = iVar17 * iVar8;
        iVar4 = iVar16 - iVar17;
        iVar26 = iVar25 + iVar17 * 4;
        if (iVar17 < iVar16) {
          do {
            iVar17 = iVar6 + iVar19;
            iVar19 = iVar19 + iVar8;
            *(int *)(iVar26 + 0x30) = iVar17;
            iVar26 = iVar26 + 4;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
        }
      }
    }
    uVar10 = (undefined2)iVar18;
    *(undefined2 *)(iVar25 + 0x116) = uVar10;
    uVar11 = (undefined2)iVar2;
    *(undefined2 *)(iVar25 + 0x114) = uVar11;
    *(undefined4 *)(iVar25 + 0x110) = *(undefined4 *)(iVar25 + 0x28);
    *(int *)(iVar25 + 0x108) = *(int *)(iVar25 + 0x110) + iVar13;
    *(int *)(iVar25 + 0x10c) = *(int *)(iVar25 + 0x108) + iVar14;
    *(undefined2 *)(iVar25 + 0x126) = uVar10;
    *(undefined2 *)(iVar25 + 0x124) = uVar11;
    *(undefined4 *)(iVar25 + 0x120) = *(undefined4 *)(iVar25 + 0x2c);
    *(int *)(iVar25 + 0x118) = *(int *)(iVar25 + 0x120) + iVar13;
    *(int *)(iVar25 + 0x11c) = *(int *)(iVar25 + 0x118) + iVar14;
    if (*(int *)(param_9 + 0x38) == 3) {
      iVar2 = 0xe;
      if (iVar15 < 0xe) {
        iVar2 = iVar15;
      }
      iVar18 = 0;
      *(int *)(iVar25 + 0x134) = iVar2 + 2;
      iVar13 = iVar25;
      do {
        *puVar24 = 0;
        puVar24[1] = *(undefined4 *)(iVar13 + 0x28);
        puVar24[2] = 0;
        puVar24[3] = 1;
        puVar24[4] = 0;
        puVar24[5] = 0;
        puVar24[6] = 0;
        puVar24[7] = 0;
        puVar24[8] = 0;
        uVar27 = zz_02a94c4_((int)(puVar24 + 10),0xffffffff,0x14);
        iVar18 = iVar18 + 1;
        puVar24 = puVar24 + 0x1e;
        iVar13 = iVar13 + 4;
      } while (iVar18 < 2);
      puVar24 = (undefined4 *)(iVar25 + 0x228);
      iVar13 = iVar25;
      for (iVar18 = 0; iVar18 < iVar2; iVar18 = iVar18 + 1) {
        *puVar24 = 0;
        puVar24[1] = *(undefined4 *)(iVar13 + 0x30);
        puVar24[2] = 0;
        puVar24[3] = 1;
        puVar24[4] = 0;
        puVar24[5] = 0;
        puVar24[6] = 0;
        puVar24[7] = 0;
        puVar24[8] = 0;
        uVar27 = zz_02a94c4_((int)(puVar24 + 10),0xffffffff,0x14);
        iVar13 = iVar13 + 4;
        puVar24 = puVar24 + 0x1e;
      }
      piVar3 = zz_02a0aa8_(uVar27,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      *(int **)(iVar25 + 0x128) = piVar3;
      piVar3 = zz_02a0aa8_(uVar27,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      *(int **)(iVar25 + 300) = piVar3;
    }
    else {
      iVar2 = 0x10;
      if (iVar15 < 0x10) {
        iVar2 = iVar15;
      }
      *(int *)(iVar25 + 0x134) = iVar2;
      for (iVar13 = 0; iVar13 < iVar2; iVar13 = iVar13 + 1) {
        *puVar24 = 0;
        puVar24[1] = *(undefined4 *)(iVar25 + 0x30);
        puVar24[2] = 0;
        puVar24[3] = 1;
        puVar24[4] = 0;
        puVar24[5] = 0;
        puVar24[6] = 0;
        puVar24[7] = 0;
        puVar24[8] = 0;
        zz_02a94c4_((int)(puVar24 + 10),0xffffffff,0x14);
        iVar25 = iVar25 + 4;
        puVar24 = puVar24 + 0x1e;
      }
    }
    iVar2 = 0;
  }
  return iVar2;
}



// ==== 8029e08c  zz_029e08c_ ====

void zz_029e08c_(uint param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  uVar8 = *(uint *)(&DAT_802b8dd8 + param_2 * 4);
  iVar9 = *(int *)(&DAT_802b8bd8 + param_2 * 4);
  iVar2 = zz_02a9598_(param_1,uVar8,22500000);
  uVar3 = iVar2 - param_4;
  uVar3 = uVar3 & (int)(-uVar3 & ~uVar3) >> 0x1f;
  if ((param_3 == 0) || ((uVar8 != 0x7512 && (uVar8 != 0xea24)))) {
    iVar4 = (int)uVar3 / iVar9;
    iVar2 = iVar4 / 0x3c + (iVar4 >> 0x1f);
    iVar7 = iVar2 - (iVar2 >> 0x1f);
    iVar5 = iVar7 / 0x3c + (iVar7 >> 0x1f);
    iVar1 = iVar5 - (iVar5 >> 0x1f);
    iVar9 = uVar3 - iVar4 * iVar9;
    iVar4 = iVar4 + (iVar2 - (iVar2 >> 0x1f)) * -0x3c;
    iVar7 = iVar7 + (iVar5 - (iVar5 >> 0x1f)) * -0x3c;
  }
  else {
    piVar6 = &DAT_802b8c1c;
    if (uVar8 == 0x7512) {
      piVar6 = &DAT_802b8bfc;
    }
    iVar1 = (int)uVar3 / *piVar6;
    iVar9 = uVar3 - iVar1 * *piVar6;
    iVar2 = iVar9 / piVar6[1];
    iVar9 = iVar9 - iVar2 * piVar6[1];
    if (iVar9 < piVar6[2]) {
      iVar7 = 0;
      iVar4 = iVar9 / piVar6[5];
      iVar9 = iVar9 - iVar4 * piVar6[5];
    }
    else {
      iVar9 = iVar9 - piVar6[2];
      iVar5 = iVar9 / piVar6[3];
      iVar7 = iVar5 + 1;
      iVar9 = iVar9 - iVar5 * piVar6[3];
      if (iVar9 < piVar6[4]) {
        iVar4 = 0;
        iVar9 = iVar9 + piVar6[7];
      }
      else {
        iVar9 = iVar9 - piVar6[4];
        iVar5 = iVar9 / piVar6[5];
        iVar4 = iVar5 + 1;
        iVar9 = iVar9 - iVar5 * piVar6[5];
      }
    }
    iVar7 = iVar7 + piVar6[6] * iVar2;
  }
  *(int *)(param_5 + 8) = iVar1;
  *(int *)(param_5 + 0xc) = iVar7;
  *(int *)(param_5 + 0x10) = iVar4;
  *(int *)(param_5 + 0x14) = iVar9;
  return;
}



// ==== 8029e244  zz_029e244_ ====

void zz_029e244_(int param_1,int param_2,uint param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined1 auStack_28 [8];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if ((param_4 == 0) || ((int)param_3 < 0)) {
    if (*(int *)(param_1 + 0xd04) == 0) {
      if (*(int *)(param_1 + 0x2898) == 0) {
        *(undefined4 *)(param_2 + 0x1c) = 0;
        *(undefined4 *)(param_2 + 0x20) = 0;
        *(undefined4 *)(param_2 + 0x24) = 0;
        *(undefined4 *)(param_2 + 0x28) = 0;
        *(undefined4 *)(param_2 + 0x2c) = 0;
      }
    }
    else if (param_4 == 0) {
      *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0xd10);
      *(undefined4 *)(param_2 + 0x24) = *(undefined4 *)(param_1 + 0xd14);
      *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0xd18);
      *(undefined4 *)(param_2 + 0x2c) = *(undefined4 *)(param_1 + 0xd1c);
    }
    else {
      iVar3 = *(int *)(param_1 + 0xd1c) + *(int *)(param_1 + 0xd20) + 1;
      iVar6 = iVar3 / *(int *)(&DAT_802b8bd8 + *(int *)(param_2 + 0x10) * 4);
      iVar1 = *(int *)(param_1 + 0xd18) + iVar6;
      iVar4 = iVar1 / 0x3c + (iVar1 >> 0x1f);
      iVar2 = *(int *)(param_1 + 0xd14) + (iVar4 - (iVar4 >> 0x1f));
      iVar5 = iVar2 / 0x3c + (iVar2 >> 0x1f);
      iVar3 = iVar3 - iVar6 * *(int *)(&DAT_802b8bd8 + *(int *)(param_2 + 0x10) * 4);
      iVar1 = iVar1 + (iVar4 - (iVar4 >> 0x1f)) * -0x3c;
      iVar2 = iVar2 + (iVar5 - (iVar5 >> 0x1f)) * -0x3c;
      if (*(int *)(param_2 + 0x1c) != 0) {
        if (((iVar1 == 0) &&
            (iVar4 = iVar2 / 10 + (iVar2 >> 0x1f), iVar2 != (iVar4 - (iVar4 >> 0x1f)) * 10)) &&
           ((iVar3 == 0 || (iVar3 == 1)))) {
          iVar3 = 2;
        }
      }
      *(int *)(param_2 + 0x20) = *(int *)(param_1 + 0xd10) + (iVar5 - (iVar5 >> 0x1f));
      *(int *)(param_2 + 0x24) = iVar2;
      *(int *)(param_2 + 0x28) = iVar1;
      *(int *)(param_2 + 0x2c) = iVar3;
    }
  }
  else {
    zz_029e08c_(param_3,*(int *)(param_2 + 0x10),*(int *)(param_2 + 0x1c),*(int *)(param_2 + 0x14),
                (int)auStack_28);
    *(undefined4 *)(param_2 + 0x20) = local_20;
    *(undefined4 *)(param_2 + 0x24) = local_1c;
    *(undefined4 *)(param_2 + 0x28) = local_18;
    *(undefined4 *)(param_2 + 0x2c) = local_14;
  }
  return;
}



// ==== 8029e438  zz_029e438_ ====

int zz_029e438_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 *param_10,int *param_11,int param_12)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  uint uVar10;
  int *piVar11;
  int iVar12;
  undefined8 uVar13;
  int local_c8;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  undefined4 uStack_b4;
  int local_b0;
  int local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  int local_9c;
  undefined4 local_98;
  undefined4 local_94;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  
  piVar6 = *(int **)(param_9 + 0x1b30);
  iVar12 = *piVar6;
  piVar11 = piVar6 + 0x23;
  zz_0283a90_(iVar12,piVar6[0x231],piVar6[0x230]);
  iVar2 = zz_0276dfc_((int)param_11,0,1);
  iVar3 = zz_02832d4_(iVar12,param_11);
  iVar4 = zz_0276dfc_((int)param_11,0,1);
  iVar4 = iVar4 - iVar2;
  if (iVar3 == -1) {
LAB_8029e520:
    iVar2 = zz_029abec_(param_9,-0xfff0fc);
  }
  else if (iVar3 < -1) {
    if (iVar3 == -3) {
      if (iVar4 < 1) {
        iVar2 = zz_029abec_(param_9,-3);
      }
      else {
        iVar2 = 0;
      }
    }
    else {
      if (iVar3 < -3) goto LAB_8029e520;
      if (iVar4 < 1) {
        iVar2 = zz_029abec_(param_9,-2);
      }
      else {
        iVar2 = 0;
      }
    }
  }
  else {
    if (0 < iVar3) goto LAB_8029e520;
    iVar2 = 0;
  }
  zz_0298c10_(param_9,*(int *)(param_9 + 0x1b38),iVar4);
  if (iVar2 != 0) {
    return iVar2;
  }
  zz_0283a6c_(iVar12,(undefined4 *)0x0,piVar6 + 0x232);
  iVar2 = zz_0281bbc_(iVar12,(int)piVar11);
  if (iVar2 != 0) {
    iVar2 = zz_029abec_(param_9,-0xfff0fb);
    return iVar2;
  }
  if (piVar6[0x37] == piVar6[0x2f]) {
    piVar6[0x38] = 0;
  }
  else {
    piVar6[0x37] = piVar6[0x2f];
    piVar6[0x38] = 1;
  }
  iVar3 = piVar6[0x38];
  uVar7 = 0xffffffff;
  iVar4 = *(int *)(param_9 + 0x1b30);
  iVar2 = *(int *)(param_9 + 0x1b38);
  pcVar5 = zz_0281140_((char *)*param_10,param_10[1],4);
  if ((pcVar5 != (char *)0x0) && (zz_02a2e54_(param_9,iVar2,(uint)pcVar5,&local_9c), -1 < local_9c))
  {
    uVar8 = piVar6[0x28];
    uVar10 = *(uint *)(&DAT_802b8dd8 + piVar6[0x27] * 4);
    if (*(int *)(param_9 + 0xdd4) < 0) {
      iVar2 = zz_02a953c_(uVar8,22500000,uVar10);
      uVar7 = local_9c - iVar2;
      *(uint *)(param_9 + 0xdd4) = uVar7 & (int)(-uVar7 & ~uVar7) >> 0x1f;
    }
    uVar7 = local_9c - *(int *)(param_9 + 0xdd4);
    uVar7 = uVar7 & (int)(-uVar7 & ~uVar7) >> 0x1f;
    iVar2 = gnt4_memcmp((void *)(iVar4 + 0xf4),&local_9c,4);
    if (iVar2 == 0) {
      if (iVar3 != 0) {
        *(int *)(iVar4 + 0xec) = *(int *)(iVar4 + 0xf0) + *(int *)(iVar4 + 0xec) + 1;
        *(undefined4 *)(iVar4 + 0xf0) = 0;
        *(undefined4 *)(iVar4 + 0xe8) = 0;
      }
      iVar3 = uVar8 - *(int *)(iVar4 + 0xe8);
      iVar2 = iVar3;
      if (iVar3 < *(int *)(iVar4 + 0xf0)) {
        iVar2 = *(int *)(iVar4 + 0xf0);
      }
      *(int *)(iVar4 + 0xf0) = iVar2;
      iVar2 = zz_02a953c_(*(int *)(iVar4 + 0xec) + iVar3,22500000,uVar10);
      uVar7 = uVar7 + iVar2;
      uVar7 = uVar7 & (int)(-uVar7 & ~uVar7) >> 0x1f;
    }
    else {
      *(int *)(iVar4 + 0xf4) = local_9c;
      *(undefined4 *)(iVar4 + 0xf8) = local_98;
      *(undefined4 *)(iVar4 + 0xfc) = local_94;
      *(undefined4 *)(iVar4 + 0xec) = 0;
      *(uint *)(iVar4 + 0xe8) = uVar8;
      if (piVar6[0x29] == 3) {
        *(undefined4 *)(iVar4 + 0xf0) = 1;
      }
      else {
        *(undefined4 *)(iVar4 + 0xf0) = 0;
      }
    }
  }
  if (param_12 == 0) {
    return 0;
  }
  iVar3 = piVar6[0x38];
  iVar2 = cTeam__GetPlayer_int_(param_9,0x34);
  if (iVar2 != 0) goto LAB_8029e83c;
  if ((int)uVar7 < 0) {
    if (iVar3 == 0) goto LAB_8029e83c;
    if (*(int *)(param_9 + 0xd04) == 0) {
      bVar1 = false;
    }
    else {
      local_90 = piVar6[0x27];
      local_8c = piVar6[0x2a];
      local_88 = piVar6[0x2b];
      local_84 = piVar6[0x2c];
      local_80 = piVar6[0x2d];
      local_7c = piVar6[0x2e];
      local_78 = piVar6[0x28];
      zz_02a4570_(&local_90,&local_c8,&local_c0);
      zz_02a4570_((int *)(param_9 + 0xd08),&local_c4,&local_c0);
      iVar4 = cTeam__GetPlayer_int_(param_9,0x35);
      if (local_c4 < local_c8) {
        if (local_c8 < local_c4 + local_c0 * iVar4) {
          bVar1 = false;
        }
        else {
          bVar1 = true;
        }
      }
      else {
        bVar1 = true;
      }
    }
    if (!bVar1) goto LAB_8029e83c;
  }
  zz_02a39d8_(param_9,0x34,1);
  iVar2 = 1;
LAB_8029e83c:
  if (iVar2 == 1) {
    zz_029e244_(param_9,(int)piVar11,uVar7,iVar3);
  }
  if (*(int *)(param_9 + 0xcdc) == 0) {
    local_58 = piVar6[0x27];
    local_54 = piVar6[0x2a];
    local_50 = piVar6[0x2b];
    local_4c = piVar6[0x2c];
    local_48 = piVar6[0x2d];
    local_44 = piVar6[0x2e];
    local_40 = 0;
    zz_02a4570_(&local_58,&local_a4,&local_a0);
    *(int *)(param_9 + 0xce0) = local_58;
    *(int *)(param_9 + 0xce4) = local_54;
    *(int *)(param_9 + 0xce8) = local_50;
    *(int *)(param_9 + 0xcec) = local_4c;
    *(int *)(param_9 + 0xcf0) = local_48;
    *(int *)(param_9 + 0xcf4) = local_44;
    *(undefined4 *)(param_9 + 0xcf8) = local_40;
    *(undefined4 *)(param_9 + 0xcfc) = local_a4;
    *(undefined4 *)(param_9 + 0xd00) = local_a0;
    *(undefined4 *)(param_9 + 0xcdc) = 1;
  }
  local_74 = piVar6[0x27];
  local_70 = piVar6[0x2a];
  local_6c = piVar6[0x2b];
  local_68 = piVar6[0x2c];
  local_64 = piVar6[0x2d];
  local_60 = piVar6[0x2e];
  local_5c = piVar6[0x28];
  uVar13 = zz_02a4570_(&local_74,&local_ac,&local_a8);
  *(int *)(param_9 + 0xd58) = local_74;
  *(int *)(param_9 + 0xd5c) = local_70;
  *(int *)(param_9 + 0xd60) = local_6c;
  *(int *)(param_9 + 0xd64) = local_68;
  *(int *)(param_9 + 0xd68) = local_64;
  *(int *)(param_9 + 0xd6c) = local_60;
  *(int *)(param_9 + 0xd70) = local_5c;
  *(int *)(param_9 + 0xd74) = local_ac - *(int *)(param_9 + 0xcfc);
  *(undefined4 *)(param_9 + 0xd78) = local_a8;
  *(undefined4 *)(param_9 + 0xd54) = 1;
  if (*(int *)(param_9 + 0xd24) <= *(int *)(param_9 + 0xd74)) {
    *(undefined4 *)(param_9 + 0xd04) = *(undefined4 *)(param_9 + 0xd54);
    *(undefined4 *)(param_9 + 0xd08) = *(undefined4 *)(param_9 + 0xd58);
    *(undefined4 *)(param_9 + 0xd0c) = *(undefined4 *)(param_9 + 0xd5c);
    *(undefined4 *)(param_9 + 0xd10) = *(undefined4 *)(param_9 + 0xd60);
    *(undefined4 *)(param_9 + 0xd14) = *(undefined4 *)(param_9 + 0xd64);
    *(undefined4 *)(param_9 + 0xd18) = *(undefined4 *)(param_9 + 0xd68);
    *(undefined4 *)(param_9 + 0xd1c) = *(undefined4 *)(param_9 + 0xd6c);
    *(undefined4 *)(param_9 + 0xd20) = *(undefined4 *)(param_9 + 0xd70);
    *(undefined4 *)(param_9 + 0xd24) = *(undefined4 *)(param_9 + 0xd74);
    *(undefined4 *)(param_9 + 0xd28) = *(undefined4 *)(param_9 + 0xd78);
  }
  iVar2 = *(int *)(param_9 + 0x1b30);
  if (*(int *)(param_9 + 0x91c) == 0) {
    iVar3 = zz_0281b5c_(iVar12,&local_bc);
    if (iVar3 == 0) {
      zz_0281a94_(iVar12,&local_b8,&uStack_b4,&local_b0);
      iVar3 = cTeam__GetPlayer_int_(param_9,0x3c);
      if (iVar3 == 0) {
        *(undefined4 *)(iVar2 + 0xe4) = 0;
      }
      else {
        iVar3 = zz_0298d28_(param_9,1);
        if (local_b0 == -1) {
          local_b0 = local_b8;
        }
        if (local_b0 < iVar3) {
          iVar3 = local_b0;
        }
        *(int *)(iVar2 + 0xe4) = iVar3;
      }
      iVar2 = local_bc;
      if (*(int *)(param_9 + 0x2898) == 0) {
        piVar9 = (int *)0x0;
      }
      else if (*(int *)(*(int *)(param_9 + 0x1b30) + 0x88) < 1) {
        piVar9 = (int *)(*(int *)(param_9 + 0x2898) + 0xac4);
      }
      else {
        piVar9 = (int *)0x0;
      }
      if ((piVar9 != (int *)0x0) && (*piVar9 == 0)) {
        iVar3 = 0x200;
        if ((int)param_10[1] < 0x200) {
          iVar3 = param_10[1];
        }
        piVar9[0x8d] = iVar3;
        uVar13 = zz_027c990_(piVar9 + 0xd,(void *)*param_10,piVar9[0x8d]);
        if (iVar2 == 0x3ffff) {
          piVar9[1] = 0;
          piVar9[2] = 0;
        }
        else {
          piVar9[1] = iVar2 * 0x32;
          piVar9[2] = 1;
        }
        iVar2 = *(int *)(param_9 + 0xce0);
        piVar9[3] = *(int *)(param_9 + 0xcdc);
        piVar9[4] = iVar2;
        iVar2 = *(int *)(param_9 + 0xce8);
        piVar9[5] = *(int *)(param_9 + 0xce4);
        piVar9[6] = iVar2;
        iVar2 = *(int *)(param_9 + 0xcf0);
        piVar9[7] = *(int *)(param_9 + 0xcec);
        piVar9[8] = iVar2;
        iVar2 = *(int *)(param_9 + 0xcf8);
        piVar9[9] = *(int *)(param_9 + 0xcf4);
        piVar9[10] = iVar2;
        iVar2 = *(int *)(param_9 + 0xd00);
        piVar9[0xb] = *(int *)(param_9 + 0xcfc);
        piVar9[0xc] = iVar2;
        *piVar9 = 1;
      }
      *(int *)(param_9 + 0x90c) = *piVar11;
      *(int *)(param_9 + 0x910) = piVar6[0x24];
      *(int *)(param_9 + 0x914) = piVar6[0x25];
      *(int *)(param_9 + 0x918) = piVar6[0x26];
      *(int *)(param_9 + 0x920) = piVar6[0x27];
      *(int *)(param_9 + 0x91c) = local_bc;
      *(int *)(param_9 + 0x92c) = local_b8;
      iVar2 = zz_029db98_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          (int *)(param_9 + 0x90c));
    }
    else {
      iVar2 = zz_029abec_(param_9,-0xfff0ea);
    }
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}



// ==== 8029ec04  zz_029ec04_ ====

int zz_029ec04_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int *param_9,int param_10,uint param_11,undefined4 *param_12)

{
  int iVar1;
  uint uVar2;
  bool bVar4;
  int iVar3;
  size_t __n;
  size_t __n_00;
  int iVar5;
  int *piVar6;
  int local_a8;
  uint local_a4;
  int local_a0;
  undefined4 uStack_9c;
  int *local_98;
  int aiStack_94 [2];
  int *local_8c;
  int local_88;
  int *local_84;
  int local_80;
  uint local_7c;
  undefined4 local_78;
  int local_74;
  int local_70;
  int local_6c;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  int *local_58;
  size_t local_54;
  int *local_50;
  size_t local_4c;
  uint local_3c;
  undefined4 local_38;
  
  *param_12 = 0;
  iVar5 = param_9[0x6cc];
  param_9[0x25b] = 0;
  if (*(int *)(iVar5 + 0x78) != 0xcc) {
    param_11 = param_11 & 0xcc;
  }
  iVar1 = zz_0298c30_((int)param_9,param_9[0x6ce],&local_98);
  if (iVar1 != 0) {
    return 0;
  }
  if ((param_11 & 200) != 0) {
    param_1 = GameInfoManager__SetUserSelectedCupSidekick_eSidekickID_((int)param_9,1);
  }
  if (param_11 == 0x80) {
    if (param_9[0x6d2] < 0) {
      iVar1 = zz_0298d18_((int)param_9,param_9[0x6ce]);
      param_9[0x6d2] = iVar1 + 4;
    }
    if (param_9[0x353] < 0) {
      param_9[0x34b] = param_9[0x341];
      param_9[0x34c] = param_9[0x342];
      param_9[0x34d] = param_9[0x343];
      param_9[0x34e] = param_9[0x344];
      param_9[0x34f] = param_9[0x345];
      param_9[0x350] = param_9[0x346];
      param_9[0x351] = param_9[0x347];
      param_9[0x352] = param_9[0x348];
      param_9[0x353] = param_9[0x349];
      param_9[0x354] = param_9[0x34a];
    }
  }
  if ((param_11 != 0x80) || (uVar2 = zz_029a03c_((int)param_9), uVar2 == 0)) {
    if ((param_11 == 0x80) && (iVar1 = zz_0299f8c_((int)param_9), iVar1 != 0)) {
      while (((**(code **)(*local_98 + 0x18))(local_98,1,4,&local_84), local_80 == 4 &&
             (iVar5 = zz_028132c_(local_84), iVar5 == 0x80))) {
        (**(code **)(*local_98 + 0x20))(local_98,0,&local_84);
        zz_0298c10_((int)param_9,param_9[0x6ce],4);
      }
      (**(code **)(*local_98 + 0x1c))(local_98,1,&local_84);
      *param_12 = 1;
      return 0;
    }
    if (param_11 == 0x80) {
      bVar4 = true;
    }
    else if ((param_10 < 5) && (iVar1 = zz_0298b20_((int)param_9,param_9[0x6ce]), iVar1 == 1)) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      zz_02a0bd8_((int)param_9);
      return 0;
    }
    if (param_10 < 5) {
      param_9[0x25b] = 1;
      return 0;
    }
    if ((param_11 & 0x4c) != 0) {
      iVar1 = zz_0299180_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_9,param_9[0x6ce],&local_3c);
      if (iVar1 == 0) {
        local_7c = local_3c;
        local_78 = local_38;
      }
      else {
        local_7c = 0;
        local_78 = 0;
      }
      uVar2 = param_11 & *(uint *)(iVar5 + 0x78);
      iVar1 = zz_029e438_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_9,&local_7c,local_98,(-uVar2 | uVar2) >> 0x1f);
      if (iVar1 != 0) {
        return iVar1;
      }
      if ((param_11 & *(uint *)(iVar5 + 0x78)) != 0) {
        *(undefined4 *)(iVar5 + 0x78) = 0xcc;
      }
      *param_12 = 1;
      return 0;
    }
    if ((param_11 & 2) == 0) {
      if (param_11 == 0x80) {
        return 0;
      }
      iVar5 = zz_0299180_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_9,param_9[0x6ce],&local_58);
      if ((iVar5 == 0) && (local_54 != 0)) {
        piVar6 = (int *)zz_0281140_((char *)local_58,local_54,0xcc);
        if (piVar6 == (int *)0x0) {
          if (local_4c == 0) {
            piVar6 = (int *)0x0;
          }
          else {
            __n_00 = local_54;
            if (2 < (int)local_54) {
              __n_00 = 3;
            }
            __n = local_4c;
            if (2 < (int)local_4c) {
              __n = 3;
            }
            gnt4_memcpy(aiStack_94,(void *)((int)local_58 + (local_54 - __n_00)),__n_00);
            gnt4_memcpy((void *)((int)aiStack_94 + __n_00),local_50,__n);
            piVar6 = aiStack_94;
            for (iVar5 = 0; iVar5 < (int)(__n_00 + (__n - 3)); iVar5 = iVar5 + 1) {
              uVar2 = zz_028132c_(piVar6);
              if ((uVar2 & 0xcc) != 0) {
                piVar6 = (int *)((int)local_58 + iVar5 + (local_54 - __n_00));
                goto LAB_8029f3b8;
              }
              piVar6 = (int *)((int)piVar6 + 1);
            }
            piVar6 = (int *)zz_0281140_((char *)local_50,local_4c,0xcc);
            if (piVar6 == (int *)0x0) {
              piVar6 = (int *)0x0;
            }
            else {
              zz_028132c_(piVar6);
            }
          }
        }
        else {
          zz_028132c_(piVar6);
        }
LAB_8029f3b8:
        if (piVar6 == (int *)0x0) {
          uVar2 = (local_54 + local_4c) - 3;
          uVar2 = uVar2 & (int)(-uVar2 & ~uVar2) >> 0x1f;
        }
        else if ((piVar6 < local_58) || ((int *)((int)local_58 + local_54) <= piVar6)) {
          if ((piVar6 < local_50) || ((int *)((int)local_50 + local_4c) <= piVar6)) {
            uVar2 = 0;
          }
          else {
            uVar2 = (int)piVar6 + (local_54 - (int)local_50);
          }
        }
        else {
          uVar2 = (int)piVar6 - (int)local_58;
        }
        zz_0298df8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                    param_9[0x6ce],uVar2);
      }
      *param_12 = 1;
      return 0;
    }
    if (param_9[0x378] < 0) {
      return 0;
    }
    iVar5 = zz_029d7c4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9
                        ,&local_7c);
    if (iVar5 == 0) {
      iVar5 = zz_029d3b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_9,local_98);
      return iVar5;
    }
    piVar6 = (int *)param_9[0x6cc];
    iVar5 = *piVar6;
    if (param_9[0x35d] < param_9[0x371]) {
      param_9[0x35f] = param_9[0x355];
      param_9[0x360] = param_9[0x356];
      param_9[0x361] = param_9[0x357];
      param_9[0x362] = param_9[0x358];
      param_9[0x363] = param_9[0x359];
      param_9[0x364] = param_9[0x35a];
      param_9[0x365] = param_9[0x35b];
      param_9[0x366] = param_9[0x35c];
      param_9[0x367] = param_9[0x35d];
      param_9[0x368] = param_9[0x35e];
    }
    iVar1 = zz_0276dfc_((int)local_98,0,1);
    iVar5 = zz_0281818_(iVar5,local_98);
    iVar3 = zz_0276dfc_((int)local_98,0,1);
    iVar3 = iVar3 - iVar1;
    if (iVar5 != -1) {
      if (iVar5 < -1) {
        if (iVar5 == -3) {
          if (iVar3 < 1) {
            iVar5 = zz_029abec_((int)param_9,-3);
          }
          else {
            iVar5 = 0;
          }
          goto LAB_8029f238;
        }
        if (-4 < iVar5) {
          if (iVar3 < 1) {
            iVar5 = zz_029abec_((int)param_9,-2);
          }
          else {
            iVar5 = 0;
          }
          goto LAB_8029f238;
        }
      }
      else if (iVar5 < 1) {
        iVar5 = 0;
        goto LAB_8029f238;
      }
    }
    iVar5 = zz_029abec_((int)param_9,-0xfff0f9);
LAB_8029f238:
    zz_0298c10_((int)param_9,param_9[0x6ce],iVar3);
    if (iVar5 == 0) {
      zz_02a1adc_((int)param_9,1,piVar6[0x29]);
      iVar5 = 0;
    }
    if (iVar5 != 0) {
      return iVar5;
    }
    *param_12 = 1;
    return 0;
  }
  iVar1 = param_9[0x6cc];
  iVar5 = cTeam__GetPlayer_int_((int)param_9,6);
  if (iVar5 == 0) {
    if (param_9[0x341] == 0) {
      local_a0 = 0;
    }
    else {
      local_74 = param_9[0x342];
      local_70 = param_9[0x343];
      local_6c = param_9[0x344];
      local_68 = param_9[0x345];
      local_64 = param_9[0x346];
      local_60 = param_9[0x347];
      local_5c = param_9[0x348] + 1;
      param_1 = zz_02a4570_(&local_74,&local_a0,&uStack_9c);
      local_a0 = local_a0 - param_9[0x33f];
    }
  }
  else {
    if (*(undefined ***)(*param_9 + 0xc) == &PTR_FUN_802b8a30) {
      bVar4 = zz_0299da8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)param_9,&local_a8,&local_a4);
      if (bVar4) goto LAB_8029ee00;
      local_a0 = -1;
    }
    else {
      local_a8 = 0;
      local_a4 = 0xac44;
LAB_8029ee00:
      param_9[0x39b] = param_9[0x39b] + local_a8;
      local_a0 = zz_02a953c_(param_9[0x39b],param_9[0x340],local_a4);
      local_a0 = local_a0 - param_9[0x378];
      if (local_a0 < 0) {
        local_a0 = 0;
      }
    }
    if (local_a0 < 0) {
      iVar5 = -1;
      goto LAB_8029ee84;
    }
  }
  if (0 < local_a0) {
    zz_0299f0c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                local_a0);
    *(int *)(iVar1 + 0x88) = *(int *)(iVar1 + 0x88) + 1;
  }
  zz_02a5044_(param_9 + 0x337,0x7fffffff);
  zz_02a5044_(param_9 + 0x341,0xffffffff);
  iVar5 = 0;
  *(undefined4 *)(iVar1 + 0x78) = 0xc0;
LAB_8029ee84:
  if (iVar5 == -1) {
    iVar5 = -1;
  }
  else {
    while (((**(code **)(*local_98 + 0x18))(local_98,1,4,&local_8c), local_88 == 4 &&
           (iVar5 = zz_028132c_(local_8c), iVar5 == 0x80))) {
      (**(code **)(*local_98 + 0x20))(local_98,0,&local_8c);
      zz_0298c10_((int)param_9,param_9[0x6ce],4);
    }
    (**(code **)(*local_98 + 0x1c))(local_98,1,&local_8c);
    iVar5 = 0;
  }
  if (iVar5 == 0) {
    *param_12 = 1;
  }
  return 0;
}



// ==== 8029f464  zz_029f464_ ====

undefined4 zz_029f464_(uint *param_1,uint param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  size_t sVar4;
  size_t sVar5;
  int iStack_38;
  int aiStack_34 [2];
  int aiStack_2c [5];
  
  if (param_3 == (int *)0x0) {
    return 1;
  }
  piVar1 = (int *)*param_1;
  if (param_3 == piVar1) {
    return 1;
  }
  if ((param_3 < piVar1) || ((int *)((int)piVar1 + param_1[1]) <= param_3)) {
    if ((param_3 < (int *)param_1[2]) ||
       (piVar1 = (int *)((int)param_1[2] + param_1[3]), piVar1 <= param_3)) {
      return 1;
    }
    if (0 < (int)param_3 + (4 - (int)piVar1)) {
      return 1;
    }
    gnt4_memcpy(&iStack_38,param_3,4);
  }
  else {
    sVar4 = (int)param_3 + (4 - (int)((int)piVar1 + param_1[1]));
    if ((int)sVar4 < 1) {
      gnt4_memcpy(&iStack_38,param_3,4);
    }
    else {
      if ((int)param_1[3] < (int)sVar4) {
        return 1;
      }
      gnt4_memcpy(&iStack_38,param_3,4 - sVar4);
      gnt4_memcpy((void *)((int)aiStack_34 - sVar4),(void *)param_1[2],sVar4);
    }
  }
  iVar2 = zz_028132c_(&iStack_38);
  if (iVar2 != 0x40) {
    if (iVar2 < 0x40) {
      if (iVar2 == 8) {
        if ((param_2 & 0x40) != 0) {
          piVar1 = (int *)zz_0281140_((char *)*param_1,param_1[1],8);
          if (piVar1 == (int *)0x0) {
            if (param_1[3] == 0) {
              piVar1 = (int *)0x0;
            }
            else {
              sVar4 = param_1[1];
              if (2 < (int)sVar4) {
                sVar4 = 3;
              }
              if ((int)param_1[3] < 3) {
                sVar5 = param_1[3];
              }
              else {
                sVar5 = 3;
              }
              gnt4_memcpy(aiStack_2c,(void *)((*param_1 + param_1[1]) - sVar4),sVar4);
              gnt4_memcpy((void *)((int)aiStack_2c + sVar4),(void *)param_1[2],sVar5);
              piVar1 = aiStack_2c;
              for (iVar2 = 0; iVar2 < (int)(sVar4 + (sVar5 - 3)); iVar2 = iVar2 + 1) {
                uVar3 = zz_028132c_(piVar1);
                if ((uVar3 & 8) != 0) {
                  piVar1 = (int *)(((*param_1 + param_1[1]) - sVar4) + iVar2);
                  goto LAB_8029f698;
                }
                piVar1 = (int *)((int)piVar1 + 1);
              }
              piVar1 = (int *)zz_0281140_((char *)param_1[2],param_1[3],8);
              if (piVar1 == (int *)0x0) {
                piVar1 = (int *)0x0;
              }
              else {
                zz_028132c_(piVar1);
              }
            }
          }
          else {
            zz_028132c_(piVar1);
          }
LAB_8029f698:
          if ((piVar1 == (int *)0x0) || (piVar1 == param_3)) {
            return 1;
          }
        }
      }
      else {
        if (7 < iVar2) {
          return 1;
        }
        if (iVar2 != 4) {
          return 1;
        }
        if ((param_2 & 0x48) != 0) {
          piVar1 = (int *)zz_0281140_((char *)*param_1,param_1[1],4);
          if (piVar1 == (int *)0x0) {
            if (param_1[3] == 0) {
              piVar1 = (int *)0x0;
            }
            else {
              sVar4 = param_1[1];
              if (2 < (int)sVar4) {
                sVar4 = 3;
              }
              if ((int)param_1[3] < 3) {
                sVar5 = param_1[3];
              }
              else {
                sVar5 = 3;
              }
              gnt4_memcpy(aiStack_34,(void *)((*param_1 + param_1[1]) - sVar4),sVar4);
              gnt4_memcpy((void *)((int)aiStack_34 + sVar4),(void *)param_1[2],sVar5);
              piVar1 = aiStack_34;
              for (iVar2 = 0; iVar2 < (int)(sVar4 + (sVar5 - 3)); iVar2 = iVar2 + 1) {
                uVar3 = zz_028132c_(piVar1);
                if ((uVar3 & 4) != 0) {
                  piVar1 = (int *)(((*param_1 + param_1[1]) - sVar4) + iVar2);
                  goto LAB_8029f7b4;
                }
                piVar1 = (int *)((int)piVar1 + 1);
              }
              piVar1 = (int *)zz_0281140_((char *)param_1[2],param_1[3],4);
              if (piVar1 == (int *)0x0) {
                piVar1 = (int *)0x0;
              }
              else {
                zz_028132c_(piVar1);
              }
            }
          }
          else {
            zz_028132c_(piVar1);
          }
LAB_8029f7b4:
          if ((piVar1 == (int *)0x0) || (piVar1 == param_3)) {
            return 1;
          }
        }
      }
    }
    else if (iVar2 != 0x80) {
      return 1;
    }
  }
  return 0;
}



// ==== 8029f7ec  zz_029f7ec_ ====

int zz_029f7ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,uint *param_10,uint *param_11)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  size_t sVar5;
  size_t sVar6;
  int iVar7;
  undefined8 uVar8;
  int local_78;
  int *local_74;
  int aiStack_70 [2];
  int aiStack_68 [2];
  int aiStack_60 [2];
  int aiStack_58 [2];
  int *local_50;
  size_t local_4c;
  int *local_48;
  size_t local_44;
  
  iVar7 = *(int *)(param_9 + 0x1b38);
  *param_10 = 0;
  *param_11 = 0;
  iVar1 = zz_0299180_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar7,
                      &local_50);
  if (iVar1 != 0) {
    return iVar1;
  }
  if (local_4c == 0) {
    return 0;
  }
  piVar2 = (int *)zz_0281140_((char *)local_50,local_4c,0xce);
  if (piVar2 == (int *)0x0) {
    if (local_44 == 0) {
      piVar2 = (int *)0x0;
      uVar3 = 0;
    }
    else {
      sVar5 = local_4c;
      if (2 < (int)local_4c) {
        sVar5 = 3;
      }
      sVar6 = local_44;
      if (2 < (int)local_44) {
        sVar6 = 3;
      }
      gnt4_memcpy(aiStack_58,(void *)((int)local_50 + (local_4c - sVar5)),sVar5);
      gnt4_memcpy((void *)((int)aiStack_58 + sVar5),local_48,sVar6);
      piVar2 = aiStack_58;
      for (iVar1 = 0; iVar1 < (int)(sVar5 + (sVar6 - 3)); iVar1 = iVar1 + 1) {
        uVar3 = zz_028132c_(piVar2);
        if ((uVar3 & 0xce) != 0) {
          piVar2 = (int *)((int)local_50 + iVar1 + (local_4c - sVar5));
          goto LAB_8029f94c;
        }
        piVar2 = (int *)((int)piVar2 + 1);
      }
      piVar2 = (int *)zz_0281140_((char *)local_48,local_44,0xce);
      if (piVar2 == (int *)0x0) {
        piVar2 = (int *)0x0;
        uVar3 = 0;
      }
      else {
        uVar3 = zz_028132c_(piVar2);
      }
    }
  }
  else {
    uVar3 = zz_028132c_(piVar2);
  }
LAB_8029f94c:
  if (piVar2 != local_50) {
    if (piVar2 == (int *)0x0) {
      uVar3 = local_4c + (local_44 - 3);
      *param_10 = uVar3 & ~((int)uVar3 >> 0x1f);
    }
    else {
      if ((piVar2 < local_50) || ((int *)((int)local_50 + local_4c) <= piVar2)) {
        if ((piVar2 < local_48) || ((int *)((int)local_48 + local_44) <= piVar2)) {
          uVar3 = 0;
        }
        else {
          uVar3 = (int)piVar2 + (local_4c - (int)local_48);
        }
      }
      else {
        uVar3 = (int)piVar2 - (int)local_50;
      }
      *param_10 = uVar3;
    }
    return 0;
  }
  *param_11 = uVar3;
  *param_10 = 4;
  if ((uVar3 & 0x80) != 0) {
    return 0;
  }
  uVar8 = zz_0298d94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar7,
                      &local_74,&local_78);
  iVar1 = zz_029f464_((uint *)&local_50,uVar3,local_74);
  if (iVar1 == 0) goto LAB_8029fb70;
  local_74 = (int *)0x0;
  if (local_44 == 0) {
    iVar1 = (int)local_50 + local_4c;
  }
  else {
    iVar1 = (int)local_48 + local_44;
  }
  if (local_78 == iVar1) goto LAB_8029fb70;
  local_78 = iVar1;
  if (local_44 == 0) {
LAB_8029fb30:
    piVar2 = zz_028122c_((int *)((int)local_50 + local_4c),local_4c,0xcc);
    if (piVar2 == (int *)0x0) {
      piVar2 = (int *)0x0;
    }
    else {
      zz_028132c_(piVar2);
    }
  }
  else {
    piVar2 = zz_028122c_((int *)((int)local_48 + local_44),local_44,0xcc);
    if (piVar2 == (int *)0x0) {
      sVar5 = local_4c;
      if (2 < (int)local_4c) {
        sVar5 = 3;
      }
      sVar6 = local_44;
      if (2 < (int)local_44) {
        sVar6 = 3;
      }
      gnt4_memcpy(aiStack_60,(void *)((int)local_50 + (local_4c - sVar5)),sVar5);
      gnt4_memcpy((void *)((int)aiStack_60 + sVar5),local_48,sVar6);
      piVar2 = aiStack_60;
      for (iVar1 = 0; iVar1 < (int)(sVar5 + (sVar6 - 3)); iVar1 = iVar1 + 1) {
        uVar4 = zz_028132c_(piVar2);
        if ((uVar4 & 0xcc) != 0) {
          piVar2 = (int *)((int)local_50 + iVar1 + (local_4c - sVar5));
          goto LAB_8029fb58;
        }
        piVar2 = (int *)((int)piVar2 + 1);
      }
      goto LAB_8029fb30;
    }
    zz_028132c_(piVar2);
  }
LAB_8029fb58:
  local_74 = piVar2;
  uVar8 = zz_0298d38_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar7,
                      piVar2,local_78);
LAB_8029fb70:
  if (local_74 == (int *)0x0) {
    iVar7 = *(int *)(param_9 + 0x1b38);
    iVar1 = zz_0298d28_(param_9,iVar7);
    iVar7 = zz_02989f0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar7)
    ;
    if (iVar1 - iVar7 < *(int *)(param_9 + 0x28)) {
      iVar1 = zz_029abec_(param_9,-0xfff0e4);
    }
    else {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = zz_028132c_(local_74);
    if ((iVar1 != 0x40) && (iVar1 < 0x40)) {
      if (iVar1 == 8) {
        if ((uVar3 & 0x40) != 0) {
          piVar2 = (int *)zz_0281140_((char *)local_50,local_4c,8);
          if (piVar2 == (int *)0x0) {
            if (local_44 == 0) {
              piVar2 = (int *)0x0;
            }
            else {
              sVar5 = local_4c;
              if (2 < (int)local_4c) {
                sVar5 = 3;
              }
              sVar6 = local_44;
              if (2 < (int)local_44) {
                sVar6 = 3;
              }
              gnt4_memcpy(aiStack_68,(void *)((int)local_50 + (local_4c - sVar5)),sVar5);
              gnt4_memcpy((void *)((int)aiStack_68 + sVar5),local_48,sVar6);
              piVar2 = aiStack_68;
              for (iVar1 = 0; iVar1 < (int)(sVar5 + (sVar6 - 3)); iVar1 = iVar1 + 1) {
                uVar3 = zz_028132c_(piVar2);
                if ((uVar3 & 8) != 0) {
                  piVar2 = (int *)((int)local_50 + iVar1 + (local_4c - sVar5));
                  goto LAB_8029fd00;
                }
                piVar2 = (int *)((int)piVar2 + 1);
              }
              piVar2 = (int *)zz_0281140_((char *)local_48,local_44,8);
              if (piVar2 == (int *)0x0) {
                piVar2 = (int *)0x0;
              }
              else {
                zz_028132c_(piVar2);
              }
            }
          }
          else {
            zz_028132c_(piVar2);
          }
LAB_8029fd00:
          if ((piVar2 == (int *)0x0) || (piVar2 == local_74)) {
            iVar7 = *(int *)(param_9 + 0x1b38);
            iVar1 = zz_0298d28_(param_9,iVar7);
            iVar7 = zz_02989f0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,iVar7);
            if (iVar1 - iVar7 < *(int *)(param_9 + 0x28)) {
              iVar1 = zz_029abec_(param_9,-0xfff0e4);
              return iVar1;
            }
            return 0;
          }
        }
      }
      else if (((iVar1 < 8) && (iVar1 == 4)) && ((uVar3 & 0x48) != 0)) {
        piVar2 = (int *)zz_0281140_((char *)local_50,local_4c,4);
        if (piVar2 == (int *)0x0) {
          if (local_44 == 0) {
            piVar2 = (int *)0x0;
          }
          else {
            sVar5 = local_4c;
            if (2 < (int)local_4c) {
              sVar5 = 3;
            }
            sVar6 = local_44;
            if (2 < (int)local_44) {
              sVar6 = 3;
            }
            gnt4_memcpy(aiStack_70,(void *)((int)local_50 + (local_4c - sVar5)),sVar5);
            gnt4_memcpy((void *)((int)aiStack_70 + sVar5),local_48,sVar6);
            piVar2 = aiStack_70;
            for (iVar1 = 0; iVar1 < (int)(sVar5 + (sVar6 - 3)); iVar1 = iVar1 + 1) {
              uVar3 = zz_028132c_(piVar2);
              if ((uVar3 & 4) != 0) {
                piVar2 = (int *)((int)local_50 + iVar1 + (local_4c - sVar5));
                goto LAB_8029fe64;
              }
              piVar2 = (int *)((int)piVar2 + 1);
            }
            piVar2 = (int *)zz_0281140_((char *)local_48,local_44,4);
            if (piVar2 == (int *)0x0) {
              piVar2 = (int *)0x0;
            }
            else {
              zz_028132c_(piVar2);
            }
          }
        }
        else {
          zz_028132c_(piVar2);
        }
LAB_8029fe64:
        if ((piVar2 == (int *)0x0) || (piVar2 == local_74)) {
          iVar7 = *(int *)(param_9 + 0x1b38);
          iVar1 = zz_0298d28_(param_9,iVar7);
          iVar7 = zz_02989f0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                              iVar7);
          if (iVar1 - iVar7 < *(int *)(param_9 + 0x28)) {
            iVar1 = zz_029abec_(param_9,-0xfff0e4);
            return iVar1;
          }
          return 0;
        }
      }
    }
    if ((local_74 < local_50) || ((int *)((int)local_50 + local_4c) <= local_74)) {
      if ((local_74 < local_48) || ((int *)((int)local_48 + local_44) <= local_74)) {
        uVar3 = 0;
      }
      else {
        uVar3 = (int)local_74 + (local_4c - (int)local_48);
      }
    }
    else {
      uVar3 = (int)local_74 - (int)local_50;
    }
    *param_10 = uVar3;
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8029ff38  zz_029ff38_ ====

int zz_029ff38_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int unaff_r29;
  int iVar6;
  undefined8 extraout_f1;
  int local_28;
  uint local_24;
  int local_20;
  uint local_1c [2];
  
  iVar2 = cTeam__GetPlayer_int_(param_9,5);
  if (iVar2 == 0) {
    return unaff_r29;
  }
  iVar2 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1b3c));
  if (iVar2 == 1) {
    return unaff_r29;
  }
  iVar2 = cTeam__GetPlayer_int_(param_9,0x1c);
  if ((iVar2 != 0) && (iVar2 = zz_029a0c8_(param_9), iVar2 != -1)) {
    if (param_9 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = zz_029aaf4_(param_9);
      if (iVar2 != 0) {
        zz_029abec_(0,-0xfffe7f);
        goto LAB_802a0004;
      }
      iVar2 = **(int **)(param_9 + 0x1b30);
    }
    iVar2 = zz_0283af0_(iVar2,5,(undefined *)0x0);
    if (iVar2 != 0) {
      zz_029abec_(param_9,-0xfff0ee);
    }
  }
LAB_802a0004:
  do {
    iVar2 = zz_029f7ec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        &local_24,local_1c);
    if ((iVar2 != 0) ||
       (iVar2 = zz_029ec04_(param_9,local_24,local_1c[0],&local_20), param_1 = extraout_f1,
       iVar2 != 0)) break;
  } while (local_20 != 0);
  iVar5 = *(int *)(param_9 + 0x1b3c);
  iVar6 = *(int *)(param_9 + 0x1b38);
  iVar2 = zz_0298b40_(param_9,iVar5);
  if ((iVar2 == 1) || (iVar2 = zz_0298b40_(param_9,iVar6), iVar2 != 1)) goto LAB_802a01cc;
  iVar2 = DrawableCharacter__GetAnimController_(param_9);
  if (iVar2 == 0) {
    iVar6 = *(int *)(param_9 + 0x2c);
    iVar2 = *(int *)(param_9 + 0x9fc);
    if (*(int *)(param_9 + 0x9fc) == -1) {
      iVar2 = iVar6;
    }
    if (iVar6 < iVar2) {
      iVar2 = iVar6;
    }
    iVar6 = zz_02a0b30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    if (iVar2 <= iVar6) {
      piVar4 = *(int **)(param_9 + 0x1b30);
      iVar6 = *piVar4;
      iVar2 = zz_0298b20_(param_9,*(int *)(param_9 + 0x1b38));
      if (iVar2 == 1) {
        bVar1 = true;
      }
      else if ((*(int *)(param_9 + 0x78) == 0) || (*(int *)(param_9 + 0xf4) != 0)) {
        zz_0281b5c_(iVar6,&local_28);
        if (local_28 == 0x3ffff) {
          bVar1 = true;
        }
        else {
          iVar2 = zz_0298c84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_9,1);
          if (iVar2 < piVar4[0x39]) {
            uVar3 = zz_02a53ac_(param_9,1);
            uVar3 = countLeadingZeros(uVar3);
            iVar2 = zz_0298d28_(param_9,uVar3 >> 5);
            iVar6 = zz_0298c84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,uVar3 >> 5);
            if (iVar6 < iVar2) {
              bVar1 = false;
            }
            else {
              bVar1 = true;
            }
          }
          else {
            bVar1 = true;
          }
        }
      }
      else {
        bVar1 = true;
      }
      if (bVar1) {
        bVar1 = true;
        goto LAB_802a019c;
      }
    }
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
LAB_802a019c:
  if ((bVar1) && (param_1 = zz_0298b50_(param_9,iVar5,1), *(int *)(param_9 + 0xdc4) != 0x7fffffff))
  {
    *(undefined4 *)(param_9 + 0xda4) = 1;
  }
LAB_802a01cc:
  iVar2 = zz_02a0b30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if (((iVar2 == -1) ||
      (((iVar5 = DrawableCharacter__GetAnimController_(param_9), iVar5 != 0 && (iVar2 == 1)) &&
       (*(int *)(param_9 + 0x960) != 0)))) &&
     (zz_0298b30_(param_9,*(int *)(param_9 + 0x1b3c),1), *(int *)(param_9 + 0x94c) == 0)) {
    zz_02a39d8_(param_9,5,0);
  }
  return unaff_r29;
}



// ==== 802a0248  FUN_802a0248 ====

void FUN_802a0248(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  zz_029ff38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 802a0268  FUN_802a0268 ====

ulonglong FUN_802a0268(void)

{
  ulonglong uVar1;
  
  uVar1 = zz_0283ff8_();
  return uVar1 & 0xffffffff;
}



// ==== 802a028c  FUN_802a028c ====

/* WARNING: Removing unreachable block (ram,0x802a02c4) */
/* WARNING: Removing unreachable block (ram,0x802a02e4) */

int FUN_802a028c(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_0284048_(8,0x8041ecd8);
  if (iVar1 == 0) {
    gnt4_memset(&DAT_8041ecb4,0,0x24);
    gnt4_memset(&DAT_8041ecac,0,8);
    gnt4_memset(&DAT_8041ec6c,0,0x40);
    iVar1 = 0;
    uRam8041ec68 = 0;
  }
  else {
    iVar2 = -0xfff0ff;
    if (iVar1 == -0xfc00fb) {
      iVar2 = -0xfff0ed;
    }
    iVar1 = zz_029abec_(0,iVar2);
  }
  return iVar1;
}



// ==== 802a0374  zz_02a0374_ ====

int zz_02a0374_(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar2 = *(int *)(param_1 + 0x1b30);
    iVar3 = iVar2 + 0x8b8;
    *(int *)(iVar2 + 0x8b8) = param_2;
    iVar1 = 0x10;
    if (param_3 < 0x10) {
      iVar1 = param_3;
    }
    *(int *)(iVar2 + 0x8bc) = iVar1;
    *(int *)(iVar2 + 0x8c0) = param_4;
    *(int *)(iVar2 + 0x8c4) = param_2;
    *(undefined4 *)(iVar2 + 0x8c8) = 0;
    for (iVar1 = 0; iVar1 < *(int *)(iVar2 + 0x8bc); iVar1 = iVar1 + 1) {
      *(int *)(iVar3 + 0x14) = param_2 + param_4 * (iVar1 + 1);
      *(undefined4 *)(iVar3 + 0x18) = 0;
      iVar3 = iVar3 + 8;
    }
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffe7b);
  }
  return iVar1;
}



// ==== 802a0448  zz_02a0448_ ====

undefined4
zz_02a0448_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_029aaf4_(param_9);
  if (iVar1 == 0) {
    uVar2 = zz_02a079c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  else {
    zz_029abec_(0,-0xfffe7d);
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 802a049c  zz_02a049c_ ====

int zz_02a049c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int *param_10)

{
  int iVar1;
  
  *param_10 = 0;
  iVar1 = zz_029aaf4_(param_9);
  if (iVar1 == 0) {
    iVar1 = zz_02a0b30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *param_10 = iVar1;
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffe7e);
  }
  return iVar1;
}



// ==== 802a0508  zz_02a0508_ ====

int zz_02a0508_(int param_1,int param_2,undefined *param_3)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029aaf4_(param_1);
    if (iVar1 != 0) {
      iVar1 = zz_029abec_(0,-0xfffe7f);
      return iVar1;
    }
    iVar1 = **(int **)(param_1 + 0x1b30);
  }
  if (param_2 == 5) {
    param_3 = (undefined *)0x0;
  }
  iVar1 = zz_0283af0_(iVar1,param_2,param_3);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = zz_029abec_(param_1,-0xfff0ee);
  }
  return iVar1;
}



// ==== 802a05b4  zz_02a05b4_ ====

void zz_02a05b4_(int param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = param_2 + 0xf;
  uVar4 = param_3 + 0xf;
  uVar5 = ((int)uVar5 >> 4) + (uint)((int)uVar5 < 0 && (uVar5 & 0xf) != 0);
  iVar1 = uVar5 * 0x10;
  uVar6 = iVar1 + 0x1f;
  uVar5 = ((int)((uVar5 >> 0x1b & 1) + iVar1) >> 1) + 0x1f;
  iVar1 = (((int)uVar6 >> 5) + (uint)((int)uVar6 < 0 && (uVar6 & 0x1f) != 0)) * 0x20;
  *(short *)((int)param_4 + 0xe) = (short)iVar1;
  iVar2 = (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * 0x20;
  uVar4 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
  *(short *)(param_4 + 3) = (short)iVar2;
  iVar3 = uVar4 * 0x10;
  param_4[2] = param_1;
  *param_4 = param_4[2] + iVar3 * iVar1;
  param_4[1] = *param_4 + ((int)((uVar4 >> 0x1b & 1) + iVar3) >> 1) * iVar2;
  return;
}



// ==== 802a063c  zz_02a063c_ ====

void zz_02a063c_(undefined4 *param_1,int *param_2,int *param_3)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (uint *)0x8041ec68;
  DAT_8041ecb4 = *param_1;
  iVar2 = 0;
  DAT_8041ecb8 = param_1[1];
  DAT_8041ecbc = param_1[2];
  DAT_8041ecc0 = param_1[3];
  DAT_8041ecc8 = param_1[5];
  DAT_8041eccc = param_1[6];
  DAT_8041ecd0 = param_1[7];
  DAT_8041ecc4 = 0;
  DAT_8041ecd4 = 0;
  DAT_8041ecac = *param_2 + 0x1fU & 0xffffffe0;
  DAT_8041ecb0 = param_2[1] + 0x1fU & 0xffffffe0;
  iVar3 = 4;
  do {
    if (iVar2 < (int)param_1[7]) {
      puVar1[1] = *param_3 + 0x1fU & 0xffffffe0;
    }
    else {
      puVar1[1] = 0;
    }
    if (iVar2 + 1 < (int)param_1[7]) {
      puVar1[2] = param_3[1] + 0x1fU & 0xffffffe0;
    }
    else {
      puVar1[2] = 0;
    }
    if (iVar2 + 2 < (int)param_1[7]) {
      puVar1[3] = param_3[2] + 0x1fU & 0xffffffe0;
    }
    else {
      puVar1[3] = 0;
    }
    puVar1 = puVar1 + 4;
    if (iVar2 + 3 < (int)param_1[7]) {
      *puVar1 = param_3[3] + 0x1fU & 0xffffffe0;
    }
    else {
      *puVar1 = 0;
    }
    param_3 = param_3 + 4;
    iVar2 = iVar2 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 802a079c  zz_02a079c_ ====

undefined4
zz_02a079c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  
  uVar11 = zz_029aac8_();
  iVar7 = *(int *)(param_9 + 0x1b30);
  piVar8 = (int *)0x0;
  iVar3 = 0;
  iVar2 = *(int *)(iVar7 + 0x134);
  piVar4 = (int *)(iVar7 + 0x138);
  piVar5 = (int *)0x0;
  piVar9 = piVar8;
  if (0 < iVar2) {
    do {
      if ((*piVar4 == 2) || (piVar6 = piVar5, piVar8 = piVar9, *piVar4 == 4)) {
        iVar3 = iVar3 + 1;
        if (piVar5 == (int *)0x0) {
          bVar1 = true;
        }
        else if (piVar4[2] < piVar5[2]) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
        piVar6 = piVar4;
        piVar8 = piVar5;
        if (!bVar1) {
          if (piVar9 == (int *)0x0) {
            bVar1 = true;
          }
          else if (piVar4[2] < piVar9[2]) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
          piVar6 = piVar5;
          piVar8 = piVar9;
          if (bVar1) {
            piVar8 = piVar4;
          }
        }
      }
      piVar4 = piVar4 + 0x1e;
      iVar2 = iVar2 + -1;
      piVar5 = piVar6;
      piVar9 = piVar8;
    } while (iVar2 != 0);
  }
  if (*(int *)(param_9 + 0x48) == 4) {
    if (iVar3 < 2) {
      uVar10 = 0;
    }
    else if ((iVar3 == 2) && (*(int *)(iVar7 + 0x7c) == 0)) {
      uVar10 = 0;
    }
    else {
      iVar2 = cTeam__GetPlayer_int_(param_9,0xf);
      if (iVar2 == 0) {
        uVar10 = 1;
      }
      else {
        iVar2 = zz_02a40ac_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                            piVar8[2],piVar8[3]);
        if (iVar2 == 0) {
          uVar10 = 0;
        }
        else {
          uVar10 = 1;
        }
      }
    }
  }
  else {
    uVar10 = 0;
  }
  zz_029aa9c_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return uVar10;
}



// ==== 802a091c  zz_02a091c_ ====

int * zz_02a091c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9,undefined4 *param_10)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  
  uVar7 = zz_029aac8_();
  iVar5 = *(int *)(param_9 + 0x1b30);
  piVar6 = (int *)0x0;
  iVar3 = 0;
  iVar2 = *(int *)(iVar5 + 0x134);
  piVar4 = (int *)(iVar5 + 0x138);
  *param_10 = 0;
  if (0 < iVar2) {
    do {
      if ((*piVar4 == 2) || (*piVar4 == 4)) {
        iVar3 = iVar3 + 1;
        if (piVar6 == (int *)0x0) {
          bVar1 = true;
        }
        else if (piVar4[2] < piVar6[2]) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
        if (bVar1) {
          piVar6 = piVar4;
        }
      }
      piVar4 = piVar4 + 0x1e;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  if (iVar3 == 1) {
    if (*(int *)(iVar5 + 0x7c) == 0) {
      if (*(int *)(iVar5 + 0x80) == 0) {
        piVar6 = (int *)0x0;
      }
    }
    else {
      *param_10 = 1;
    }
  }
  zz_029aa9c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return piVar6;
}



// ==== 802a0a14  zz_02a0a14_ ====

void zz_02a0a14_(int *param_1)

{
  if (param_1 == (int *)0x0) {
    return;
  }
  if (*param_1 == 4) {
    *param_1 = 2;
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 802a0a40  zz_02a0a40_ ====

void zz_02a0a40_(int *param_1)

{
  if (param_1 == (int *)0x0) {
    return;
  }
  if (*param_1 == 4) {
    *param_1 = 3;
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 802a0a6c  zz_02a0a6c_ ====

void zz_02a0a6c_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 4;
  return;
}



// ==== 802a0a80  zz_02a0a80_ ====

void zz_02a0a80_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 2;
  return;
}



// ==== 802a0a94  zz_02a0a94_ ====

void zz_02a0a94_(undefined4 *param_1)

{
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 802a0aa8  zz_02a0aa8_ ====

int * zz_02a0aa8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar5 = zz_029aac8_();
  iVar1 = 0;
  iVar2 = *(int *)(*(int *)(param_9 + 0x1b30) + 0x134);
  piVar3 = (int *)(*(int *)(param_9 + 0x1b30) + 0x138);
  iVar4 = iVar2;
  if (0 < iVar2) {
    do {
      if (*piVar3 == 0) {
        *piVar3 = 1;
        break;
      }
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 0x1e;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (iVar1 == iVar2) {
    piVar3 = (int *)0x0;
  }
  zz_029aa9c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return piVar3;
}



// ==== 802a0b30  zz_02a0b30_ ====

int zz_02a0b30_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar5 = zz_029aac8_();
  iVar2 = *(int *)(param_9 + 0x1b30);
  iVar4 = 0;
  iVar1 = *(int *)(iVar2 + 0x134);
  piVar3 = (int *)(iVar2 + 0x138);
  if (0 < iVar1) {
    do {
      if ((*piVar3 == 2) || (*piVar3 == 4)) {
        iVar4 = iVar4 + 1;
      }
      piVar3 = piVar3 + 0x1e;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  if ((*(int *)(iVar2 + 0x7c) == 1) && (iVar4 == 0)) {
    iVar4 = -1;
  }
  zz_029aa9c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return iVar4;
}



// ==== 802a0bc0  GameInfoManager::SetUserSelectedCupSidekick(eSidekickID) ====

void GameInfoManager__SetUserSelectedCupSidekick_eSidekickID_(int param_1,undefined4 param_2)

{
  *(undefined4 *)(*(int *)(param_1 + 0x1b30) + 0x80) = param_2;
  return;
}



// ==== 802a0bcc  DrawableCharacter::GetAnimController( ====

undefined4 DrawableCharacter__GetAnimController_(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x1b30) + 0x7c);
}



// ==== 802a0bd8  zz_02a0bd8_ ====

void zz_02a0bd8_(int param_1)

{
  *(undefined4 *)(*(int *)(param_1 + 0x1b30) + 0x7c) = 1;
  return;
}



// ==== 802a0be8  MWInitializeMutex ====

undefined4 MWInitializeMutex(int param_1)

{
  *(undefined4 *)(param_1 + 0x4c) = 3;
  return 0;
}



// ==== 802a0bf8  zz_02a0bf8_ ====

int zz_02a0bf8_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
    *(undefined4 *)(param_1 + 0x4c) = 3;
  }
  else {
    iVar1 = zz_029abec_(0,-0xfffebd);
  }
  return iVar1;
}



// ==== 802a0c4c  zz_02a0c4c_ ====

int zz_02a0c4c_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (param_2 == 1) {
    iVar1 = *(int *)(param_1 + 0x54);
    *(int *)(param_1 + 0x54) = iVar1 + 1;
    if (iVar1 == 0) {
      if ((*(int *)(param_1 + 0x4c) == 3) || (*(int *)(param_1 + 0x4c) == 4)) {
        zz_02a41ec_(param_1,1);
        iVar1 = zz_02a5408_(param_1,7,8,1,0);
        iVar2 = 0;
        if (iVar1 != 0) {
          iVar2 = iVar1;
        }
      }
      else {
        iVar2 = 0;
      }
    }
  }
  else if (param_2 < 1) {
    if ((-1 < param_2) &&
       (iVar1 = *(int *)(param_1 + 0x54) + -1, *(int *)(param_1 + 0x54) = iVar1, iVar1 == 0)) {
      if ((*(int *)(param_1 + 0x4c) == 3) || (*(int *)(param_1 + 0x4c) == 4)) {
        zz_02a41ec_(param_1,0);
        iVar1 = zz_02a5408_(param_1,7,8,0,0);
        iVar2 = 0;
        if (iVar1 != 0) {
          iVar2 = iVar1;
        }
      }
      else {
        iVar2 = 0;
      }
    }
  }
  else if ((param_2 < 3) && (*(int *)(param_1 + 0x48) == 4)) {
    if ((*(int *)(param_1 + 0x4c) == 3) || (*(int *)(param_1 + 0x4c) == 4)) {
      zz_02a41ec_(param_1,2);
      iVar1 = zz_02a5408_(param_1,7,8,2,0);
      iVar2 = 0;
      if (iVar1 != 0) {
        iVar2 = iVar1;
      }
    }
    else {
      iVar2 = 0;
    }
  }
  return iVar2;
}



// ==== 802a0dcc  zz_02a0dcc_ ====

/* WARNING: Removing unreachable block (ram,0x802a0e5c) */

int zz_02a0dcc_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = zz_029aaf4_(param_1);
  if (iVar3 == 0) {
    if (param_2 == 0) {
      if (*(int *)(param_1 + 0x50) == 0) {
        return 0;
      }
      uVar1 = 0;
    }
    else if (*(int *)(param_1 + 0x50) == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 2;
    }
    *(int *)(param_1 + 0x50) = param_2;
    iVar3 = 0;
    if (uVar1 == 1) {
      iVar2 = *(int *)(param_1 + 0x54);
      *(int *)(param_1 + 0x54) = iVar2 + 1;
      if ((iVar2 == 0) && ((*(int *)(param_1 + 0x4c) == 3 || (*(int *)(param_1 + 0x4c) == 4)))) {
        zz_02a41ec_(param_1,1);
        iVar2 = zz_02a5408_(param_1,7,8,1,0);
        iVar3 = 0;
        if (iVar2 != 0) {
          iVar3 = iVar2;
        }
      }
    }
    else if (uVar1 == 0) {
      iVar2 = *(int *)(param_1 + 0x54) + -1;
      *(int *)(param_1 + 0x54) = iVar2;
      if ((iVar2 == 0) && ((*(int *)(param_1 + 0x4c) == 3 || (*(int *)(param_1 + 0x4c) == 4)))) {
        zz_02a41ec_(param_1,0);
        iVar2 = zz_02a5408_(param_1,7,8,0,0);
        iVar3 = 0;
        if (iVar2 != 0) {
          iVar3 = iVar2;
        }
      }
    }
    else if (((uVar1 < 3) && (*(int *)(param_1 + 0x48) == 4)) &&
            ((*(int *)(param_1 + 0x4c) == 3 || (*(int *)(param_1 + 0x4c) == 4)))) {
      zz_02a41ec_(param_1,2);
      iVar2 = zz_02a5408_(param_1,7,8,2,0);
      iVar3 = 0;
      if (iVar2 != 0) {
        iVar3 = iVar2;
      }
    }
    *(undefined4 *)(param_1 + 0x44) = 1;
  }
  else {
    iVar3 = zz_029abec_(0,-0xfffebe);
  }
  return iVar3;
}



// ==== 802a0fa8  zz_02a0fa8_ ====

void zz_02a0fa8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int *param_10)

{
  int iVar1;
  
  iVar1 = zz_029aaf4_(param_9);
  if (iVar1 == 0) {
    zz_02994c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  }
  else {
    zz_029abec_(0,-0xfffec7);
  }
  return;
}



