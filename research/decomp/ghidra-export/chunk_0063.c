// ==== 802013f4  gnt4-OSReport-bl ====

void gnt4_OSReport_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                     undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                     char *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                     undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16
                     )

{
  byte in_cr1;
  char *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined8 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined4 local_c;
  undefined1 *local_8;
  char **local_4;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_50 = param_1;
    local_48 = param_2;
    local_40 = param_3;
    local_38 = param_4;
    local_30 = param_5;
    local_28 = param_6;
    local_20 = param_7;
    local_18 = param_8;
  }
  local_c = 0x1000000;
  local_8 = &stack0x00000008;
  local_4 = &local_70;
  local_70 = param_9;
  local_6c = param_10;
  local_68 = param_11;
  local_64 = param_12;
  local_60 = param_13;
  local_5c = param_14;
  local_58 = param_15;
  local_54 = param_16;
  gnt4_vprintf(param_9,&local_c);
  return;
}



// ==== 80201474  gnt4-OSPanic ====

void gnt4_OSPanic(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,char *param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  uint uVar4;
  byte in_cr1;
  undefined8 uVar5;
  undefined4 local_88;
  undefined4 local_84;
  char *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  undefined4 local_1c;
  undefined1 *local_18;
  undefined4 *local_14;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  uVar3 = 0x803a0000;
  local_88 = param_9;
  local_84 = param_10;
  local_80 = param_11;
  local_7c = param_12;
  local_78 = param_13;
  local_74 = param_14;
  local_70 = param_15;
  local_6c = param_16;
  gnt4_OSDisableInterrupts_bl();
  local_1c = 0x3000000;
  local_18 = &stack0x00000008;
  local_14 = &local_88;
  gnt4_vprintf(param_11,&local_1c);
  uVar5 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_in___s__on_line__d__803a3cd8,param_9,param_10,uVar3,param_13,param_14,
                           param_15,param_16);
  uVar5 = gnt4_OSReport_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Address__Back_Chain_LR_Save_803a3cf0,extraout_r4,param_10,uVar3,
                           param_13,param_14,param_15,param_16);
  uVar4 = 0;
  puVar2 = (undefined4 *)gnt4_OSGetStackPointer_bl();
  while (((puVar2 != (undefined4 *)0x0 && (puVar2 != (undefined4 *)0xffffffff)) &&
         (bVar1 = uVar4 < 0x10, uVar4 = uVar4 + 1, bVar1))) {
    uVar5 = gnt4_OSReport_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_0x_08x__0x_08x_0x_08x_803a3d18,puVar2,*puVar2,puVar2[1],param_13,
                             param_14,param_15,param_16);
    puVar2 = (undefined4 *)*puVar2;
  }
  gnt4_PPCHalt();
  return;
}



// ==== 802015a0  gnt4-OSSetErrorHandler-bl ====

int gnt4_OSSetErrorHandler_bl(ushort param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  gnt4_OSDisableInterrupts_bl();
  iVar3 = *(int *)(&DAT_803d6910 + (uint)param_1 * 4);
  *(int *)(&DAT_803d6910 + (uint)param_1 * 4) = param_2;
  if (param_1 == 0x10) {
    gnt4_PPCMfmsr();
    gnt4_PPCMtmsr();
    gnt4_PPCMffpscr();
    iVar2 = DAT_800000dc;
    if (param_2 == 0) {
      for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x2fc)) {
        *(uint *)(iVar2 + 0x19c) = *(uint *)(iVar2 + 0x19c) & 0xfffff6ff;
        *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0xffffff07;
        *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0x6005f8ff;
      }
    }
    else {
      for (; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x2fc)) {
        *(uint *)(iVar2 + 0x19c) = *(uint *)(iVar2 + 0x19c) | 0x900;
        if ((*(ushort *)(iVar2 + 0x1a2) & 1) == 0) {
          *(ushort *)(iVar2 + 0x1a2) = *(ushort *)(iVar2 + 0x1a2) | 1;
          iVar4 = 4;
          iVar1 = iVar2;
          do {
            *(undefined4 *)(iVar1 + 0x94) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x90) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1cc) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1c8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x9c) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x98) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1d4) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1d0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xa4) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xa0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1dc) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1d8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xac) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xa8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1e4) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1e0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xb4) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xb0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1ec) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1e8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xbc) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xb8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 500) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1f0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xc4) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xc0) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1fc) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x1f8) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0xcc) = 0xffffffff;
            *(undefined4 *)(iVar1 + 200) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x204) = 0xffffffff;
            *(undefined4 *)(iVar1 + 0x200) = 0xffffffff;
            iVar1 = iVar1 + 0x40;
            iVar4 = iVar4 + -1;
          } while (iVar4 != 0);
          *(undefined4 *)(iVar2 + 0x194) = 4;
        }
        *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) | DAT_80435c70 & 0xf8;
        *(uint *)(iVar2 + 0x194) = *(uint *)(iVar2 + 0x194) & 0x6005f8ff;
      }
    }
    gnt4_PPCMtfpscr();
    gnt4_PPCMtmsr();
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar3;
}



// ==== 802017b8  gnt4-__OSUnhandledException-bl ====

void gnt4___OSUnhandledException_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,byte param_9,undefined4 *param_10,
               uint param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined2 *puVar7;
  undefined8 extraout_f1;
  undefined8 uVar8;
  double dVar9;
  undefined8 uVar10;
  
  puVar7 = &DAT_803d0000;
  uVar6 = 0x803a0000;
  uVar5 = param_12;
  uVar10 = gnt4_OSGetTime_bl();
  uVar4 = param_10[0x67];
  if ((uVar4 & 2) == 0) {
    uVar8 = gnt4_OSReport_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Non_recoverable_Exception__d_803a3d34,(uint)param_9,uVar4,uVar5,uVar6
                             ,puVar7,param_15,param_16);
    uVar3 = extraout_r4;
  }
  else {
    uVar8 = extraout_f1;
    if (((param_9 == 6) && ((uVar4 & 0x100000) != 0)) && (DAT_803d6950 != (code *)0x0)) {
      param_9 = 0x10;
      gnt4_PPCMfmsr();
      dVar9 = (double)gnt4_PPCMtmsr();
      if (DAT_800000d8 != (undefined4 *)0x0) {
        gnt4_OSSaveFPUContext_bl
                  (dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_800000d8,
                   extraout_r4_00);
      }
      gnt4_PPCMffpscr();
      gnt4_PPCMtfpscr();
      uVar8 = gnt4_PPCMtmsr();
      if (DAT_800000d8 == param_10) {
        gnt4_OSDisableScheduler_bl();
        uVar4 = param_11;
        uVar5 = param_12;
        (*DAT_803d6950)(0x10,param_10);
        param_10[0x67] = param_10[0x67] & 0xffffdfff;
        DAT_800000d8 = (undefined4 *)0x0;
        param_10[0x65] = param_10[0x65] & 0x6005f8ff;
        gnt4_OSEnableScheduler_bl();
        uVar8 = gnt4___OSReschedule_bl();
      }
      else {
        param_10[0x67] = param_10[0x67] & 0xffffdfff;
        DAT_800000d8 = (undefined4 *)0x0;
      }
      gnt4_OSLoadContext_bl((int)param_10);
    }
    if (*(int *)(&DAT_803d6910 + (uint)param_9 * 4) != 0) {
      gnt4_OSDisableScheduler_bl();
      uVar4 = param_11;
      uVar5 = param_12;
      (**(code **)(&DAT_803d6910 + (uint)param_9 * 4))(param_9,param_10);
      gnt4_OSEnableScheduler_bl();
      uVar8 = gnt4___OSReschedule_bl();
      gnt4_OSLoadContext_bl((int)param_10);
    }
    if (param_9 == 8) {
      gnt4_OSLoadContext_bl((int)param_10);
    }
    uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Unhandled_Exception__d_803a3d54,(uint)param_9,uVar4,uVar5,uVar6,
                             puVar7,param_15,param_16);
    uVar3 = extraout_r4_01;
  }
  uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435c74,uVar3,uVar4,uVar5,uVar6,puVar7,param_15,param_16);
  uVar8 = gnt4_OSDumpContext_bl
                    (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                     extraout_r4_02,uVar4,uVar5,uVar6,puVar7,param_15,param_16);
  uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_DSISR___0x_08x_DAR___0x_08x_803a3d6c,param_11,param_12,uVar5,uVar6,
                           puVar7,param_15,param_16);
  uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_TB___0x_016llx_803a3da0,extraout_r4_03,(int)((ulonglong)uVar10 >> 0x20)
                           ,(int)uVar10,uVar6,puVar7,param_15,param_16);
  uVar5 = (undefined4)((ulonglong)uVar10 >> 0x20);
  uVar3 = (undefined4)uVar10;
  switch(param_9) {
  case 2:
    uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Instruction_at_0x_x__read_from_S_803a3db0,param_10[0x66],param_12,
                             uVar3,uVar6,puVar7,param_15,param_16);
    break;
  case 3:
    uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Attempted_to_fetch_instruction_f_803a3e10,param_10[0x66],uVar5,uVar3,
                             uVar6,puVar7,param_15,param_16);
    break;
  case 5:
    uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Instruction_at_0x_x__read_from_S_803a3e5c,param_10[0x66],param_12,
                             uVar3,uVar6,puVar7,param_15,param_16);
    break;
  case 6:
    uVar8 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_Program_exception___Possible_ill_803a3ec0,param_10[0x66],param_12,
                             uVar3,uVar6,puVar7,param_15,param_16);
    break;
  case 0xf:
    uVar10 = gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              &DAT_80435c74,extraout_r4_04,uVar5,uVar3,uVar6,puVar7,param_15,
                              param_16);
    uVar1 = DAT_cc005030;
    uVar2 = DAT_cc005032;
    uVar10 = gnt4_OSReport_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_AI_DMA_Address___0x_04x_04x_803a3f20,(uint)uVar1,(uint)uVar2,uVar3,
                              uVar6,puVar7,param_15,param_16);
    uVar1 = DAT_cc005020._0_2_;
    uVar2 = DAT_cc005020._2_2_;
    uVar4 = (uint)uVar2;
    uVar10 = gnt4_OSReport_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_ARAM_DMA_Address___0x_04x_04x_803a3f40,(uint)uVar1,uVar4,uVar3,uVar6
                              ,puVar7,param_15,param_16);
    uVar5 = DAT_cc006014;
    uVar8 = gnt4_OSReport_bl(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_DI_DMA_Address___0x_08x_803a3f60,uVar5,uVar4,uVar3,uVar6,puVar7,
                             param_15,param_16);
  }
  gnt4_OSReport_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   s_Last_interrupt___d___SRR0___0x_0_803a3f7c,(int)DAT_80436438,DAT_80436434,uVar3,
                   DAT_80436440,DAT_80436444,param_15,param_16);
  gnt4_PPCHalt();
  return;
}



// ==== 80201aa0  zz_0201aa0_ ====

void zz_0201aa0_(int param_1,uint param_2,uint param_3,byte *param_4,uint param_5,int param_6,
                int param_7,byte *param_8)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint local_164 [8];
  undefined4 local_144 [8];
  undefined4 local_124 [56];
  uint local_44;
  
  uVar1 = param_2 & 0xffff;
LAB_80201ae8:
  do {
    if ((int)((param_3 & 0xffff) - 0x18) < param_6) {
      return;
    }
    iVar9 = param_1 + (param_5 + param_6 * uVar1) * 2;
    uVar11 = param_5;
    while( true ) {
      if (*param_8 == 0) {
        return;
      }
      if (*param_8 == 10) {
        param_6 = param_6 + param_7;
        param_8 = param_8 + 1;
        goto LAB_80201ae8;
      }
      if ((int)(uVar1 - 0x30) < (int)uVar11) break;
      iVar12 = 3;
      iVar4 = 0;
      iVar6 = 0;
      do {
        uVar10 = 0;
        local_164[iVar6] = 0;
        local_144[iVar6] = 0;
        local_124[iVar6] = 0;
        iVar3 = (iVar4 + 1U & 7) + (iVar4 + 1U >> 3) * 0x18;
        local_164[iVar3] = 0;
        local_144[iVar3] = 0;
        local_124[iVar3] = 0;
        iVar3 = (iVar4 + 2U & 7) + (iVar4 + 2U >> 3) * 0x18;
        local_164[iVar3] = 0;
        local_144[iVar3] = 0;
        local_124[iVar3] = 0;
        iVar3 = (iVar4 + 3U & 7) + (iVar4 + 3U >> 3) * 0x18;
        local_164[iVar3] = 0;
        local_144[iVar3] = 0;
        local_124[iVar3] = 0;
        iVar8 = (iVar4 + 4U & 7) + (iVar4 + 4U >> 3) * 0x18;
        local_164[iVar8] = 0;
        local_144[iVar8] = 0;
        iVar3 = (iVar4 + 5U & 7) + (iVar4 + 5U >> 3) * 0x18;
        local_124[iVar8] = 0;
        local_164[iVar3] = 0;
        local_144[iVar3] = 0;
        local_124[iVar3] = 0;
        iVar8 = (iVar4 + 6U & 7) + (iVar4 + 6U >> 3) * 0x18;
        local_164[iVar8] = 0;
        local_144[iVar8] = 0;
        iVar3 = (iVar4 + 7U & 7) + (iVar4 + 7U >> 3) * 0x18;
        local_124[iVar8] = 0;
        local_164[iVar3] = 0;
        iVar6 = iVar6 + 0x18;
        iVar4 = iVar4 + 8;
        local_144[iVar3] = 0;
        local_124[iVar3] = 0;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
      param_8 = zz_0202e78_(param_8,(int)local_164,0,6,&local_44);
      iVar4 = 0;
      do {
        iVar3 = 0xc;
        iVar12 = (uVar10 & 7) + (uVar10 >> 3) * 0x18;
        iVar6 = iVar4 << 1;
        uVar7 = 0;
        uVar5 = uVar11;
        do {
          uVar2 = local_164[iVar12 + (uVar7 & 0xfffffff8)] >> (7 - (uVar7 & 7)) * 4 & 0xf;
          if (uVar2 != 0) {
            *(char *)(iVar9 + iVar6) = (char)(((uint)*param_4 * uVar2 * 0xef) / 0xef1) + '\x10';
            if ((uVar5 & 1) == 0) {
              *(byte *)(iVar9 + iVar6 + -1) = param_4[2];
              *(byte *)(iVar9 + iVar6 + 1) = param_4[1];
            }
            else {
              *(byte *)(iVar9 + iVar6 + -1) = param_4[1];
              *(byte *)(iVar9 + iVar6 + 1) = param_4[2];
            }
          }
          uVar2 = local_164[iVar12 + (uVar7 + 1 & 0xfffffff8)] >> (7 - (uVar7 + 1 & 7)) * 4 & 0xf;
          iVar8 = iVar6 + 2;
          if (uVar2 != 0) {
            *(char *)(iVar9 + iVar8) = (char)(((uint)*param_4 * uVar2 * 0xef) / 0xef1) + '\x10';
            if ((uVar5 + 1 & 1) == 0) {
              *(byte *)(iVar9 + iVar8 + -1) = param_4[2];
              *(byte *)(iVar9 + iVar8 + 1) = param_4[1];
            }
            else {
              *(byte *)(iVar9 + iVar8 + -1) = param_4[1];
              *(byte *)(iVar9 + iVar8 + 1) = param_4[2];
            }
          }
          iVar6 = iVar6 + 4;
          uVar5 = uVar5 + 2;
          uVar7 = uVar7 + 2;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
        uVar10 = uVar10 + 1;
        iVar4 = iVar4 + uVar1;
      } while (uVar10 < 0x18);
      iVar9 = iVar9 + local_44 * 2;
      uVar11 = uVar11 + local_44;
    }
    param_6 = param_6 + param_7;
  } while( true );
}



// ==== 80201e7c  zz_0201e7c_ ====

void zz_0201e7c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined2 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int iVar2;
  uint local_3c;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  undefined2 local_30;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined4 local_28;
  
  local_36 = 0x1e0;
  local_34 = (undefined2)param_10;
  local_32 = 0x28;
  local_2e = 0x280;
  local_38 = param_9;
  local_2c = local_34;
  iVar2 = gnt4_VIGetTvFormat();
  if (iVar2 != 2) {
    if (1 < iVar2) {
      if (iVar2 == 5) {
        local_3c = 0x14;
        local_30 = 0;
        local_28 = 1;
      }
      goto LAB_80201f4c;
    }
    if (iVar2 != 0) {
      if (-1 < iVar2) {
        local_3c = 4;
        local_30 = 0x2f;
        local_28 = 1;
      }
      goto LAB_80201f4c;
    }
  }
  uVar1 = DAT_cc00206c;
  if ((uVar1 & 1) == 0) {
    local_3c = 0;
    local_30 = 0;
    local_28 = 1;
  }
  else {
    local_3c = 2;
    local_30 = 0;
    local_28 = 0;
  }
LAB_80201f4c:
  gnt4_VIConfigure_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_3c,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0211dc0_(0,0,0x280,0x1e0);
  return;
}



// ==== 80201f78  zz_0201f78_ ====

void zz_0201f78_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9,undefined4 *param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 uVar8;
  
  puVar6 = &DAT_803d0000;
  uVar5 = param_11;
  gnt4_OSDisableInterrupts_bl();
  gnt4_OSDisableScheduler_bl();
  gnt4_OSClearContext_bl(-0x7fc29698);
  gnt4_OSSetCurrentContext_bl(0x803d6968);
  gnt4___OSStopAudioSystem_bl();
  zz_0214994_(0);
  uVar7 = AISetStreamVolLeft(0);
  gnt4_VIInit_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                 (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,uVar5,puVar6,param_13,param_14,param_15,
                 param_16);
  gnt4_VISetBlack(1);
  gnt4_VIFlush_bl();
  gnt4_OSEnableInterrupts_bl();
  iVar2 = zz_021236c_();
  do {
    iVar3 = zz_021236c_();
  } while (iVar3 - iVar2 < 1);
  uVar7 = gnt4_OSGetTime_bl();
  uVar1 = DAT_800000f8 / 4000;
  do {
    bVar4 = zz_020476c_(0);
    if (bVar4) break;
    uVar8 = gnt4_OSGetTime_bl();
  } while (((int)((ulonglong)uVar8 >> 0x20) -
            ((uint)((uint)uVar8 < (uint)uVar7) + (int)((ulonglong)uVar7 >> 0x20)) ^ 0x80000000) <
           ((uint)uVar8 - (uint)uVar7 < uVar1 * 1000) + 0x80000000);
  gnt4_OSDisableInterrupts_bl();
  zz_020476c_(1);
  gnt4___OSSetExceptionHandler_bl(8,gnt4_OSDefaultExceptionHandler_bl);
  zz_0227004_();
  gnt4_OSSetArenaLo_bl(0x81200000);
  gnt4_OSSetArenaHi_bl(DAT_80000038);
  DAT_803d6958 = *param_9;
  DAT_803d695c = *param_10;
  DAT_803d6960 = param_11;
  iVar2 = gnt4_OSGetArenaHi_bl();
  zz_0200e44_(zz_02020cc_,iVar2);
  return;
}



// ==== 802020cc  zz_02020cc_ ====

void zz_02020cc_(void)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  size_t sVar4;
  uint uVar5;
  int iVar6;
  ushort uVar10;
  char *pcVar7;
  undefined1 *puVar8;
  undefined1 *puVar9;
  uint uVar11;
  undefined4 uVar12;
  uint uVar13;
  byte *pbVar14;
  undefined4 in_r7;
  undefined4 uVar15;
  undefined4 in_r8;
  undefined4 uVar16;
  undefined4 in_r9;
  undefined4 in_r10;
  byte *pbVar17;
  int iVar18;
  double dVar19;
  undefined8 uVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  double dVar26;
  double dVar27;
  double dVar28;
  int local_70;
  int local_6c;
  int local_64;
  uint local_60;
  int local_5c;
  undefined8 local_58;
  undefined4 local_50;
  uint uStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  gnt4_OSEnableInterrupts_bl();
  sVar4 = strlen((char *)DAT_803d6960);
  uVar5 = gnt4_OSAllocFromArenaLo_bl(sVar4 + 1,0x20);
  DAT_803d6960 = (byte *)gnt4_memmove_bl(uVar5,(uint)DAT_803d6960,sVar4 + 1);
  zz_0207c68_(0,0);
  zz_0207c68_(2,0);
  while (iVar6 = gnt4_EXILock_bl(0,1,0), iVar6 == 0) {
    do {
      uVar5 = DAT_cc00680c;
    } while ((uVar5 & 1) == 1);
    gnt4_EXIDeselect(0);
    gnt4_EXIUnlock_bl(0);
  }
  gnt4_EXIUnlock_bl(0);
  do {
    uVar5 = DAT_cc00680c;
  } while ((uVar5 & 1) == 1);
  uVar10 = zz_0202a60_();
  if (uVar10 == 1) {
    uVar5 = gnt4_OSAllocFromArenaLo_bl(0x90ee4,0x20);
  }
  else {
    uVar5 = gnt4_OSAllocFromArenaLo_bl(0x10120,0x20);
  }
  pcVar7 = (char *)gnt4_OSGetArenaLo_bl();
  zz_0202b44_(uVar5,pcVar7);
  puVar8 = (undefined1 *)gnt4_OSAllocFromArenaLo_bl(0x96000,0x20);
  local_60 = DAT_803d695c;
  uStack_44 = DAT_803d695c >> 0x18;
  uStack_4c = DAT_803d695c >> 0x10 & 0xff;
  uStack_2c = DAT_803d695c >> 8 & 0xff;
  local_20 = 0x43300000;
  local_28 = 0x43300000;
  local_18 = 0x43300000;
  local_38 = 0x43300000;
  local_40 = 0x43300000;
  local_48 = 0x43300000;
  local_50 = 0x43300000;
  local_58 = (double)CONCAT44(0x43300000,uStack_2c);
  local_30 = 0x43300000;
  dVar19 = (double)FLOAT_8043ca24;
  dVar25 = (double)(FLOAT_8043ca38 *
                   (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043ca58));
  dVar23 = (double)(FLOAT_8043ca44 *
                   (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043ca58));
  dVar26 = (double)FLOAT_8043ca34;
  dVar24 = (double)(FLOAT_8043ca38 *
                    (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043ca58) +
                   (FLOAT_8043ca3c *
                    (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043ca58) -
                   FLOAT_8043ca40 *
                   (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043ca58)));
  dVar28 = (double)(FLOAT_8043ca20 +
                   (float)(dVar19 + (double)(FLOAT_8043ca28 *
                                             (float)((double)CONCAT44(0x43300000,uStack_2c) -
                                                    DOUBLE_8043ca58) +
                                            FLOAT_8043ca2c *
                                            (float)((double)CONCAT44(0x43300000,uStack_44) -
                                                   DOUBLE_8043ca58) +
                                            FLOAT_8043ca30 *
                                            (float)((double)CONCAT44(0x43300000,uStack_4c) -
                                                   DOUBLE_8043ca58))));
  dVar27 = (double)FLOAT_8043ca4c;
  dVar22 = (double)(FLOAT_8043ca20 + (float)(dVar26 + dVar24));
  dVar21 = (double)(FLOAT_8043ca20 +
                   (float)(dVar26 + (double)((float)(dVar25 - dVar23) -
                                            FLOAT_8043ca48 * (float)(local_58 - DOUBLE_8043ca58))));
  if ((dVar28 <= dVar27) && (dVar27 = dVar28, dVar28 < dVar19)) {
    dVar27 = dVar19;
  }
  dVar19 = (double)FLOAT_8043ca50;
  uVar1 = (undefined1)(int)dVar27;
  if ((dVar22 <= dVar19) && (dVar19 = dVar22, dVar22 < (double)FLOAT_8043ca24)) {
    dVar19 = (double)FLOAT_8043ca24;
  }
  dVar28 = (double)FLOAT_8043ca50;
  uVar2 = (undefined1)(int)dVar19;
  if ((dVar21 <= dVar28) && (dVar28 = dVar21, dVar21 < (double)FLOAT_8043ca24)) {
    dVar28 = (double)FLOAT_8043ca24;
  }
  uVar13 = (uint)dVar28;
  local_58 = (double)(longlong)(int)uVar13;
  iVar6 = 0;
  uVar3 = (undefined1)uVar13;
  local_70 = (uint)CONCAT21(CONCAT11(uVar1,uVar2),uVar3) << 8;
  local_5c = local_70;
  uVar11 = (int)dVar19 & 0xff;
  uVar13 = uVar13 & 0xff;
  puVar9 = puVar8;
  do {
    iVar18 = 0x28;
    do {
      *puVar9 = uVar1;
      puVar9[1] = uVar2;
      puVar9[2] = uVar1;
      puVar9[3] = uVar3;
      puVar9[4] = uVar1;
      puVar9[5] = uVar2;
      puVar9[6] = uVar1;
      puVar9[7] = uVar3;
      puVar9[8] = uVar1;
      puVar9[9] = uVar2;
      puVar9[10] = uVar1;
      puVar9[0xb] = uVar3;
      puVar9[0xc] = uVar1;
      puVar9[0xd] = uVar2;
      puVar9[0xe] = uVar1;
      puVar9[0xf] = uVar3;
      puVar9[0x10] = uVar1;
      puVar9[0x11] = uVar2;
      puVar9[0x12] = uVar1;
      puVar9[0x13] = uVar3;
      puVar9[0x14] = uVar1;
      puVar9[0x15] = uVar2;
      puVar9[0x16] = uVar1;
      puVar9[0x17] = uVar3;
      puVar9[0x18] = uVar1;
      puVar9[0x19] = uVar2;
      puVar9[0x1a] = uVar1;
      puVar9[0x1b] = uVar3;
      puVar9[0x1c] = uVar1;
      puVar9[0x1d] = uVar2;
      puVar9[0x1e] = uVar1;
      puVar9[0x1f] = uVar3;
      puVar9 = puVar9 + 0x20;
      iVar18 = iVar18 + -1;
    } while (iVar18 != 0);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x1e0);
  uStack_3c = uStack_4c;
  uStack_34 = uStack_44;
  uStack_24 = uStack_4c;
  uStack_1c = uStack_44;
  uStack_14 = uStack_2c;
  uVar20 = gnt4_VISetNextFrameBuffer(puVar8);
  zz_0201e7c_(uVar20,dVar21,dVar22,dVar23,dVar24,dVar25,dVar26,dVar27,0x280,0x1e0,uVar11,uVar13,
              in_r7,in_r8,in_r9,in_r10);
  gnt4_VIFlush_bl();
  iVar6 = zz_021236c_();
  do {
    iVar18 = zz_021236c_();
  } while (iVar18 - iVar6 < 2);
  uStack_4c = DAT_803d6958 >> 0x18;
  uStack_44 = DAT_803d6958 >> 0x10 & 0xff;
  uStack_3c = DAT_803d6958 >> 8 & 0xff;
  local_50 = 0x43300000;
  local_48 = 0x43300000;
  local_58 = (double)CONCAT44(0x43300000,uStack_3c);
  local_38 = 0x43300000;
  local_30 = 0x43300000;
  local_28 = 0x43300000;
  local_20 = 0x43300000;
  local_18 = 0x43300000;
  local_40 = 0x43300000;
  dVar19 = (double)FLOAT_8043ca24;
  dVar25 = (double)(FLOAT_8043ca38 *
                   (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043ca58));
  dVar23 = (double)(FLOAT_8043ca44 *
                   (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043ca58));
  dVar26 = (double)FLOAT_8043ca34;
  dVar24 = (double)(FLOAT_8043ca38 *
                    (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043ca58) +
                   (FLOAT_8043ca3c *
                    (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043ca58) -
                   FLOAT_8043ca40 *
                   (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043ca58)));
  dVar28 = (double)(FLOAT_8043ca20 +
                   (float)(dVar19 + (double)(FLOAT_8043ca28 * (float)(local_58 - DOUBLE_8043ca58) +
                                            FLOAT_8043ca2c *
                                            (float)((double)CONCAT44(0x43300000,uStack_4c) -
                                                   DOUBLE_8043ca58) +
                                            FLOAT_8043ca30 *
                                            (float)((double)CONCAT44(0x43300000,uStack_44) -
                                                   DOUBLE_8043ca58))));
  dVar27 = (double)FLOAT_8043ca4c;
  dVar22 = (double)(FLOAT_8043ca20 + (float)(dVar26 + dVar24));
  dVar21 = (double)(FLOAT_8043ca20 +
                   (float)(dVar26 + (double)((float)(dVar25 - dVar23) -
                                            FLOAT_8043ca48 *
                                            (float)((double)CONCAT44(0x43300000,uStack_3c) -
                                                   DOUBLE_8043ca58))));
  if ((dVar28 <= dVar27) && (dVar27 = dVar28, dVar28 < dVar19)) {
    dVar27 = dVar19;
  }
  dVar19 = (double)FLOAT_8043ca50;
  if ((dVar22 <= dVar19) && (dVar19 = dVar22, dVar22 < (double)FLOAT_8043ca24)) {
    dVar19 = (double)FLOAT_8043ca24;
  }
  dVar28 = (double)FLOAT_8043ca50;
  if ((dVar21 <= dVar28) && (dVar28 = dVar21, dVar21 < (double)FLOAT_8043ca24)) {
    dVar28 = (double)FLOAT_8043ca24;
  }
  local_58 = (double)(longlong)(int)dVar28;
  pbVar14 = (byte *)&local_64;
  uVar12 = 0x1e0;
  uVar16 = 100;
  uVar15 = 0x30;
  local_6c = (uint)CONCAT21(CONCAT11((char)(int)dVar27,(char)(int)dVar19),(char)(int)dVar28) << 8;
  local_64 = local_6c;
  uVar5 = (uint)*(ushort *)(uVar5 + 0xe);
  pbVar17 = DAT_803d6960;
  uStack_34 = uStack_4c;
  uStack_2c = uStack_44;
  uStack_24 = uStack_4c;
  uStack_1c = uStack_44;
  uStack_14 = uStack_3c;
  zz_0201aa0_((int)puVar8,0x280,0x1e0,pbVar14,0x30,100,uVar5,DAT_803d6960);
  gnt4_DCFlushRange_bl((uint)puVar8,0x96000);
  gnt4_VISetBlack(0);
  uVar20 = gnt4_VIFlush_bl();
  iVar6 = zz_021236c_();
  do {
    iVar18 = zz_021236c_();
  } while (iVar18 - iVar6 < 1);
  gnt4_OSDisableInterrupts_bl();
  gnt4_OSReport_bl(uVar20,dVar21,dVar22,dVar23,dVar24,dVar25,dVar26,dVar27,&DAT_80435c78,
                   DAT_803d6960,uVar12,pbVar14,uVar15,uVar16,uVar5,pbVar17);
  gnt4_PPCHalt();
  return;
}



// ==== 80202750  zz_0202750_ ====

uint zz_0202750_(uint param_1)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar6;
  int iVar5;
  
  uVar6 = zz_0202a60_();
  if (uVar6 == 1) {
    uVar3 = param_1 & 0xffff;
    if ((0x1f < uVar3) && (uVar3 < 0xe0)) {
      return (uint)*(ushort *)((int)&PTR_def_802019C0_803a3fb8 + uVar3 * 2);
    }
    uVar3 = param_1 & 0xffff;
    if ((0x889e < uVar3) && (uVar3 < 0x9873)) {
      uVar4 = param_1 & 0xff;
      bVar2 = false;
      bVar1 = false;
      if ((0x3f < uVar4) && (uVar4 < 0xfd)) {
        bVar1 = true;
      }
      if ((bVar1) && (uVar4 != 0x7f)) {
        bVar2 = true;
      }
      if (!bVar2) {
        return 0;
      }
      iVar5 = uVar4 - 0x40;
      if (0x3f < iVar5) {
        iVar5 = uVar4 - 0x41;
      }
      return (((int)uVar3 >> 8) + -0x88) * 0xbc + iVar5 + 0x2be;
    }
    uVar3 = param_1 & 0xffff;
    if ((0x813f < uVar3) && (uVar3 < 0x879e)) {
      uVar4 = param_1 & 0xff;
      bVar2 = false;
      bVar1 = false;
      if ((0x3f < uVar4) && (uVar4 < 0xfd)) {
        bVar1 = true;
      }
      if ((bVar1) && (uVar4 != 0x7f)) {
        bVar2 = true;
      }
      if (!bVar2) {
        return 0;
      }
      iVar5 = uVar4 - 0x40;
      if (0x3f < iVar5) {
        iVar5 = uVar4 - 0x41;
      }
      return (uint)*(ushort *)(&DAT_803a4178 + ((((int)uVar3 >> 8) + -0x81) * 0xbc + iVar5) * 2);
    }
  }
  else {
    uVar3 = param_1 & 0xffff;
    if ((0x20 < uVar3) && (uVar3 < 0x100)) {
      return uVar3 - 0x20;
    }
  }
  return 0;
}



// ==== 802028ec  zz_02028ec_ ====

void zz_02028ec_(int param_1,int param_2)

{
  byte *pbVar1;
  uint uVar2;
  uint *puVar3;
  ushort *puVar4;
  undefined1 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint unaff_r29;
  int iVar12;
  int iVar13;
  uint uVar14;
  
  puVar3 = (uint *)(param_1 + 0x10);
  iVar9 = 0;
  iVar12 = 0;
  iVar13 = *(int *)(param_1 + 4);
  iVar10 = *(int *)(param_1 + 8);
  iVar11 = *(int *)(param_1 + 0xc);
  do {
    if (iVar12 == 0) {
      unaff_r29 = *puVar3;
      iVar12 = 0x20;
      puVar3 = puVar3 + 1;
    }
    if ((unaff_r29 & 0x80000000) == 0) {
      puVar4 = (ushort *)(param_1 + iVar10);
      iVar10 = iVar10 + 2;
      iVar8 = iVar9 - ((*(byte *)puVar4 & 0xf) << 8 | (uint)(byte)*puVar4);
      if ((int)(uint)*puVar4 >> 0xc == 0) {
        pbVar1 = (byte *)(param_1 + iVar11);
        iVar11 = iVar11 + 1;
        uVar2 = *pbVar1 + 0x12;
      }
      else {
        uVar2 = ((int)(uint)*puVar4 >> 0xc) + 2;
      }
      puVar5 = (undefined1 *)(param_2 + iVar9);
      if (uVar2 != 0) {
        uVar14 = uVar2 >> 3;
        if (uVar14 != 0) {
          do {
            iVar9 = iVar9 + 8;
            *puVar5 = *(undefined1 *)(param_2 + iVar8 + -1);
            puVar5[1] = *(undefined1 *)(param_2 + iVar8);
            puVar5[2] = *(undefined1 *)(param_2 + iVar8 + 1);
            puVar5[3] = *(undefined1 *)(param_2 + iVar8 + 2);
            puVar5[4] = *(undefined1 *)(param_2 + iVar8 + 3);
            iVar6 = iVar8 + 5;
            puVar5[5] = *(undefined1 *)(param_2 + iVar8 + 4);
            iVar7 = iVar8 + 6;
            iVar8 = iVar8 + 8;
            puVar5[6] = *(undefined1 *)(param_2 + iVar6);
            puVar5[7] = *(undefined1 *)(param_2 + iVar7);
            puVar5 = puVar5 + 8;
            uVar14 = uVar14 - 1;
          } while (uVar14 != 0);
          uVar2 = uVar2 & 7;
          if (uVar2 == 0) goto LAB_80202a3c;
        }
        do {
          iVar6 = iVar8 + -1;
          iVar9 = iVar9 + 1;
          iVar8 = iVar8 + 1;
          *puVar5 = *(undefined1 *)(param_2 + iVar6);
          puVar5 = puVar5 + 1;
          uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
      }
    }
    else {
      *(undefined1 *)(param_2 + iVar9) = *(undefined1 *)(param_1 + iVar11);
      iVar11 = iVar11 + 1;
      iVar9 = iVar9 + 1;
    }
LAB_80202a3c:
    unaff_r29 = unaff_r29 << 1;
    iVar12 = iVar12 + -1;
    if (iVar13 <= iVar9) {
      return;
    }
  } while( true );
}



// ==== 80202a60  zz_0202a60_ ====

ushort zz_0202a60_(void)

{
  ushort uVar1;
  
  if (DAT_80435c80 < 2) {
    return DAT_80435c80;
  }
  if (DAT_800000cc == 0) {
    uVar1 = DAT_cc00206e;
    DAT_80435c80 = (ushort)((uVar1 & 2) != 0);
  }
  else {
    DAT_80435c80 = 0;
  }
  return DAT_80435c80;
}



// ==== 80202ab8  zz_0202ab8_ ====

void zz_0202ab8_(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  while (0 < param_2) {
    iVar2 = param_2;
    if (0x100 < param_2) {
      iVar2 = 0x100;
    }
    param_2 = param_2 - iVar2;
    do {
      uVar1 = gnt4___OSReadROM_bl(param_1,iVar2,param_3);
    } while (uVar1 == 0);
    param_3 = param_3 + iVar2;
    param_1 = param_1 + iVar2;
  }
  return;
}



// ==== 80202b44  zz_0202b44_ ====

int zz_0202b44_(int param_1,char *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar7;
  uint uVar5;
  uint uVar6;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined2 local_24;
  undefined2 uStack_22;
  undefined2 local_20;
  undefined2 uStack_1e;
  
  DAT_80436424 = 0;
  uVar7 = zz_0202a60_();
  if (uVar7 == 1) {
    zz_0202ab8_((uint)param_2,0x4d000,0x1aff00);
  }
  else {
    zz_0202ab8_((uint)param_2,0x3000,0x1fcf00);
  }
  if (((*param_2 == 'Y') && (param_2[1] == 'a')) && (param_2[2] == 'y')) {
    iVar12 = *(int *)(param_2 + 4);
  }
  else {
    iVar12 = 0;
  }
  if (iVar12 != 0) {
    zz_02028ec_((int)param_2,param_1);
    uVar2 = DAT_8043ca64;
    uVar1 = DAT_8043ca60;
    DAT_80436428 = param_1 + (uint)*(ushort *)(param_1 + 0x22);
    DAT_8043642c = (uint)*(ushort *)(param_1 + 0x1a) * (uint)*(ushort *)(param_1 + 0x1c);
    if (1 < DAT_80435c80) {
      if (DAT_800000cc == 0) {
        uVar7 = DAT_cc00206e;
        DAT_80435c80 = (ushort)((uVar7 & 2) != 0);
      }
      else {
        DAT_80435c80 = 0;
      }
    }
    DAT_80436420 = param_1;
    if (DAT_80435c80 == 1) {
      uVar5 = zz_0202750_(0x54);
      local_24 = (undefined2)((uint)uVar1 >> 0x10);
      iVar11 = uVar5 - ((int)uVar5 / DAT_8043642c) * DAT_8043642c;
      iVar10 = iVar11 / (int)(uint)*(ushort *)(DAT_80436420 + 0x1a);
      iVar9 = iVar10 * (uint)*(ushort *)(DAT_80436420 + 0x12);
      uVar6 = (iVar11 - iVar10 * (uint)*(ushort *)(DAT_80436420 + 0x1a)) *
              (uint)*(ushort *)(DAT_80436420 + 0x10);
      uVar3 = iVar9 + 4;
      uVar4 = uVar6 + (((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0)) * -8;
      iVar8 = DAT_80436420 + *(int *)(DAT_80436420 + 0x24) +
              ((uint)(((int)uVar5 / DAT_8043642c) * *(int *)(DAT_80436420 + 0x14)) >> 1);
      iVar10 = (((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0)) * 0x10;
      iVar11 = ((int)uVar4 >> 2) + (uint)((int)uVar4 < 0 && (uVar4 & 3) != 0);
      *(undefined2 *)
       (iVar8 + (((int)(uint)*(ushort *)(DAT_80436420 + 0x1e) >> 3) * 0x20 >> 1) *
                (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) + iVar10 +
        (uVar3 + (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) * -8) * 2 + iVar11
       ) = local_24;
      uVar5 = iVar9 + 5;
      uVar4 = iVar9 + 6;
      uVar3 = iVar9 + 7;
      uStack_22 = (undefined2)uVar1;
      *(undefined2 *)
       (iVar8 + (((int)(uint)*(ushort *)(DAT_80436420 + 0x1e) >> 3) * 0x20 >> 1) *
                (((int)uVar5 >> 3) + (uint)((int)uVar5 < 0 && (uVar5 & 7) != 0)) + iVar10 +
        (uVar5 + (((int)uVar5 >> 3) + (uint)((int)uVar5 < 0 && (uVar5 & 7) != 0)) * -8) * 2 + iVar11
       ) = uStack_22;
      local_20 = (undefined2)((uint)uVar2 >> 0x10);
      *(undefined2 *)
       (iVar8 + (((int)(uint)*(ushort *)(DAT_80436420 + 0x1e) >> 3) * 0x20 >> 1) *
                (((int)uVar4 >> 3) + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0)) + iVar10 +
        (uVar4 + (((int)uVar4 >> 3) + (uint)((int)uVar4 < 0 && (uVar4 & 7) != 0)) * -8) * 2 + iVar11
       ) = local_20;
      uStack_1e = (undefined2)uVar2;
      *(undefined2 *)
       (iVar8 + (((int)(uint)*(ushort *)(DAT_80436420 + 0x1e) >> 3) * 0x20 >> 1) *
                (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) + iVar10 +
        (uVar3 + (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) * -8) * 2 + iVar11
       ) = uStack_1e;
    }
  }
  return iVar12;
}



// ==== 80202e78  zz_0202e78_ ====

byte * zz_0202e78_(byte *param_1,int param_2,int param_3,uint param_4,uint *param_5)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  bool bVar4;
  bool bVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  byte bVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  byte *pbVar22;
  
  bVar17 = *param_1;
  uVar6 = (uint)bVar17;
  if (uVar6 != 0) {
    pbVar22 = param_1 + 1;
    if (1 < DAT_80435c80) {
      if (DAT_800000cc == 0) {
        uVar1 = DAT_cc00206e;
        DAT_80435c80 = (ushort)((uVar1 & 2) != 0);
      }
      else {
        DAT_80435c80 = 0;
      }
    }
    if (DAT_80435c80 == 1) {
      bVar5 = true;
      bVar4 = false;
      if ((0x80 < bVar17) && (bVar17 < 0xa0)) {
        bVar4 = true;
      }
      if (!bVar4) {
        bVar4 = false;
        if ((0xdf < bVar17) && (bVar17 < 0xfd)) {
          bVar4 = true;
        }
        if (!bVar4) {
          bVar5 = false;
        }
      }
      if ((bVar5) && (*pbVar22 != 0)) {
        uVar6 = (uint)CONCAT11(bVar17,*pbVar22);
        pbVar22 = param_1 + 2;
      }
    }
    param_1 = pbVar22;
    iVar20 = DAT_80436420 + 0x2c;
    uVar7 = zz_0202750_(uVar6);
    uVar6 = param_4 << 2 | param_4 >> 0x1e;
    iVar14 = (int)uVar7 / DAT_8043642c;
    iVar8 = *(int *)(DAT_80436420 + 0x14);
    uVar1 = *(ushort *)(DAT_80436420 + 0x1a);
    uVar2 = *(ushort *)(DAT_80436420 + 0x12);
    uVar3 = *(ushort *)(DAT_80436420 + 0x10);
    iVar16 = uVar7 - iVar14 * DAT_8043642c;
    iVar13 = iVar16 / (int)(uint)uVar1;
    iVar19 = DAT_80436420 + *(int *)(DAT_80436420 + 0x24);
    for (uVar21 = 0; (int)uVar21 < (int)(uint)*(ushort *)(DAT_80436420 + 0x12); uVar21 = uVar21 + 1)
    {
      uVar9 = iVar13 * (uint)uVar2 + uVar21;
      for (iVar15 = 0; iVar15 < (int)(uint)*(ushort *)(DAT_80436420 + 0x10); iVar15 = iVar15 + 1) {
        uVar18 = (iVar16 - iVar13 * (uint)uVar1) * (uint)uVar3 + iVar15;
        uVar10 = param_3 + iVar15;
        uVar11 = uVar18 + (((int)uVar18 >> 3) + (uint)((int)uVar18 < 0 && (uVar18 & 7) != 0)) * -8;
        uVar12 = uVar10 + (((int)uVar10 >> 3) + (uint)((int)uVar10 < 0 && (uVar10 & 7) != 0)) * -8;
        pbVar22 = (byte *)(param_2 + (((int)uVar21 >> 3) +
                                     (uint)((int)uVar21 < 0 && (uVar21 & 7) != 0)) *
                                     (((int)uVar6 >> 3) +
                                     (uint)((int)uVar6 < 0 && (param_4 << 2 & 4) != 0)) * 0x20 +
                           (((int)uVar10 >> 3) + (uint)((int)uVar10 < 0 && (uVar10 & 7) != 0)) *
                           0x20 + (uVar21 + (((int)uVar21 >> 3) +
                                            (uint)((int)uVar21 < 0 && (uVar21 & 7) != 0)) * -8) * 4
                          + ((int)uVar12 >> 1) + (uint)((int)uVar12 < 0 && (uVar12 & 1) != 0));
        if (uVar10 == (((int)uVar10 >> 1) + (uint)((int)uVar10 < 0 && (uVar10 & 1) != 0)) * 2) {
          bVar17 = 0xf0;
        }
        else {
          bVar17 = 0xf;
        }
        *pbVar22 = *pbVar22 |
                   *(byte *)(iVar20 + ((int)(uint)*(byte *)(iVar19 + ((uint)(iVar14 * iVar8) >> 1) +
                                                            (((int)(uint)*(ushort *)
                                                                          (DAT_80436420 + 0x1e) >> 3
                                                             ) * 0x20 >> 1) *
                                                            (((int)uVar9 >> 3) +
                                                            (uint)((int)uVar9 < 0 &&
                                                                  (uVar9 & 7) != 0)) +
                                                            (((int)uVar18 >> 3) +
                                                            (uint)((int)uVar18 < 0 &&
                                                                  (uVar18 & 7) != 0)) * 0x10 +
                                                            (uVar9 + (((int)uVar9 >> 3) +
                                                                     (uint)((int)uVar9 < 0 &&
                                                                           (uVar9 & 7) != 0)) * -8)
                                                            * 2 + ((int)uVar11 >> 2) +
                                                                  (uint)((int)uVar11 < 0 &&
                                                                        (uVar11 & 3) != 0)) >>
                                       ((uVar18 + (((int)uVar18 >> 2) +
                                                  (uint)((int)uVar18 < 0 && (uVar18 & 3) != 0)) * -4
                                        ) * -2 + 6 & 0x3f) & 3U)) & bVar17;
      }
    }
    if (param_5 != (uint *)0x0) {
      *param_5 = (uint)*(byte *)(DAT_80436428 + uVar7);
    }
  }
  return param_1;
}



// ==== 8020317c  zz_020317c_ ====

void zz_020317c_(int param_1,uint param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  
  iVar4 = DAT_80436420 + 0x2c;
  if (*(short *)(DAT_80436420 + 0x18) == 0) {
    uVar2 = *(uint *)(DAT_80436420 + 0x28);
    uVar2 = ((int)uVar2 >> 1) + (uint)((int)uVar2 < 0 && (uVar2 & 1) != 0);
    iVar3 = uVar2 - 1;
    pbVar6 = (byte *)(param_2 + iVar3 * 2);
    if (-1 < iVar3) {
      uVar8 = uVar2 >> 2;
      if (uVar8 != 0) {
        do {
          bVar1 = *(byte *)(param_1 + iVar3);
          *pbVar6 = *(byte *)(iVar4 + (uint)(bVar1 >> 6)) & 0xf0 |
                    *(byte *)(iVar4 + (bVar1 >> 4 & 3)) & 0xf;
          bVar1 = *(byte *)(param_1 + iVar3);
          pbVar7 = (byte *)(param_1 + iVar3 + -1);
          pbVar6[1] = *(byte *)(iVar4 + (bVar1 >> 2 & 3)) & 0xf0 |
                      *(byte *)(iVar4 + (bVar1 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar6[-2] = *(byte *)(iVar4 + (uint)(bVar1 >> 6)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 >> 4 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar7 = (byte *)(param_1 + iVar3 + -2);
          pbVar6[-1] = *(byte *)(iVar4 + (bVar1 >> 2 & 3)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar6[-4] = *(byte *)(iVar4 + (uint)(bVar1 >> 6)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 >> 4 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar7 = (byte *)(param_1 + iVar3 + -3);
          iVar3 = iVar3 + -4;
          pbVar6[-3] = *(byte *)(iVar4 + (bVar1 >> 2 & 3)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar6[-6] = *(byte *)(iVar4 + (uint)(bVar1 >> 6)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 >> 4 & 3)) & 0xf;
          bVar1 = *pbVar7;
          pbVar6[-5] = *(byte *)(iVar4 + (bVar1 >> 2 & 3)) & 0xf0 |
                       *(byte *)(iVar4 + (bVar1 & 3)) & 0xf;
          pbVar6 = pbVar6 + -8;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar2 = uVar2 & 3;
        if (uVar2 == 0) goto LAB_8020350c;
      }
      do {
        pbVar7 = (byte *)(param_1 + iVar3);
        bVar1 = *pbVar7;
        iVar3 = iVar3 + -1;
        *pbVar6 = *(byte *)(iVar4 + (uint)(bVar1 >> 6)) & 0xf0 |
                  *(byte *)(iVar4 + (bVar1 >> 4 & 3)) & 0xf;
        bVar1 = *pbVar7;
        pbVar6[1] = *(byte *)(iVar4 + (bVar1 >> 2 & 3)) & 0xf0 |
                    *(byte *)(iVar4 + (bVar1 & 3)) & 0xf;
        pbVar6 = pbVar6 + -2;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
  }
  else if (*(short *)(DAT_80436420 + 0x18) == 2) {
    uVar2 = *(uint *)(DAT_80436420 + 0x28);
    uVar2 = ((int)uVar2 >> 2) + (uint)((int)uVar2 < 0 && (uVar2 & 3) != 0);
    iVar3 = uVar2 - 1;
    puVar5 = (undefined1 *)(param_2 + iVar3 * 4);
    if (-1 < iVar3) {
      uVar8 = uVar2 >> 2;
      if (uVar8 != 0) {
        do {
          pbVar6 = (byte *)(param_1 + iVar3);
          *puVar5 = *(undefined1 *)(iVar4 + (uint)(*pbVar6 >> 6));
          puVar5[1] = *(undefined1 *)(iVar4 + (*pbVar6 >> 4 & 3));
          puVar5[2] = *(undefined1 *)(iVar4 + (*pbVar6 >> 2 & 3));
          pbVar7 = (byte *)(param_1 + iVar3 + -1);
          puVar5[3] = *(undefined1 *)(iVar4 + (*pbVar6 & 3));
          puVar5[-4] = *(undefined1 *)(iVar4 + (uint)(*pbVar7 >> 6));
          puVar5[-3] = *(undefined1 *)(iVar4 + (*pbVar7 >> 4 & 3));
          puVar5[-2] = *(undefined1 *)(iVar4 + (*pbVar7 >> 2 & 3));
          pbVar6 = (byte *)(param_1 + iVar3 + -2);
          puVar5[-1] = *(undefined1 *)(iVar4 + (*pbVar7 & 3));
          puVar5[-8] = *(undefined1 *)(iVar4 + (uint)(*pbVar6 >> 6));
          puVar5[-7] = *(undefined1 *)(iVar4 + (*pbVar6 >> 4 & 3));
          puVar5[-6] = *(undefined1 *)(iVar4 + (*pbVar6 >> 2 & 3));
          pbVar7 = (byte *)(param_1 + iVar3 + -3);
          iVar3 = iVar3 + -4;
          puVar5[-5] = *(undefined1 *)(iVar4 + (*pbVar6 & 3));
          puVar5[-0xc] = *(undefined1 *)(iVar4 + (uint)(*pbVar7 >> 6));
          puVar5[-0xb] = *(undefined1 *)(iVar4 + (*pbVar7 >> 4 & 3));
          puVar5[-10] = *(undefined1 *)(iVar4 + (*pbVar7 >> 2 & 3));
          puVar5[-9] = *(undefined1 *)(iVar4 + (*pbVar7 & 3));
          puVar5 = puVar5 + -0x10;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar2 = uVar2 & 3;
        if (uVar2 == 0) goto LAB_8020350c;
      }
      do {
        pbVar6 = (byte *)(param_1 + iVar3);
        iVar3 = iVar3 + -1;
        *puVar5 = *(undefined1 *)(iVar4 + (uint)(*pbVar6 >> 6));
        puVar5[1] = *(undefined1 *)(iVar4 + (*pbVar6 >> 4 & 3));
        puVar5[2] = *(undefined1 *)(iVar4 + (*pbVar6 >> 2 & 3));
        puVar5[3] = *(undefined1 *)(iVar4 + (*pbVar6 & 3));
        puVar5 = puVar5 + -4;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
  }
LAB_8020350c:
  gnt4_DCStoreRange_bl(param_2,*(int *)(DAT_80436420 + 0x28));
  return;
}



// ==== 8020352c  zz_020352c_ ====

bool zz_020352c_(int param_1)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  
  if (1 < DAT_80435c80) {
    if (DAT_800000cc == 0) {
      uVar1 = DAT_cc00206e;
      DAT_80435c80 = (ushort)((uVar1 & 2) != 0);
    }
    else {
      DAT_80435c80 = 0;
    }
  }
  if (DAT_80435c80 == 1) {
    uVar3 = param_1 + 0xd3f00;
  }
  else {
    uVar3 = param_1 + 0x1d120;
  }
  iVar2 = zz_0202b44_(param_1,(char *)(uVar3 & 0xffffffe0));
  if (iVar2 != 0) {
    DAT_80436424 = DAT_80436420 + *(int *)(DAT_80436420 + 0x24) + 0x1fU & 0xffffffe0;
    zz_020317c_(DAT_80436420 + *(int *)(DAT_80436420 + 0x24),DAT_80436424);
  }
  return iVar2 != 0;
}



// ==== 8020360c  FUN_8020360c ====

byte * FUN_8020360c(byte *param_1,int *param_2,int *param_3,int *param_4,uint *param_5)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  
  bVar1 = *param_1;
  uVar5 = (uint)bVar1;
  if (uVar5 == 0) {
    *param_2 = 0;
  }
  else {
    pbVar8 = param_1 + 1;
    if (1 < DAT_80435c80) {
      if (DAT_800000cc == 0) {
        uVar4 = DAT_cc00206e;
        DAT_80435c80 = (ushort)((uVar4 & 2) != 0);
      }
      else {
        DAT_80435c80 = 0;
      }
    }
    if (DAT_80435c80 == 1) {
      bVar3 = true;
      bVar2 = false;
      if ((0x80 < bVar1) && (bVar1 < 0xa0)) {
        bVar2 = true;
      }
      if (!bVar2) {
        bVar2 = false;
        if ((0xdf < bVar1) && (bVar1 < 0xfd)) {
          bVar2 = true;
        }
        if (!bVar2) {
          bVar3 = false;
        }
      }
      if ((bVar3) && (*pbVar8 != 0)) {
        uVar5 = (uint)CONCAT11(bVar1,*pbVar8);
        pbVar8 = param_1 + 2;
      }
    }
    param_1 = pbVar8;
    uVar5 = zz_0202750_(uVar5);
    iVar6 = (int)uVar5 / DAT_8043642c;
    *param_2 = DAT_80436424 + *(int *)(DAT_80436420 + 0x14) * iVar6;
    iVar6 = uVar5 - iVar6 * DAT_8043642c;
    iVar7 = iVar6 / (int)(uint)*(ushort *)(DAT_80436420 + 0x1a);
    *param_3 = (iVar6 - iVar7 * (uint)*(ushort *)(DAT_80436420 + 0x1a)) *
               (uint)*(ushort *)(DAT_80436420 + 0x10);
    *param_4 = iVar7 * (uint)*(ushort *)(DAT_80436420 + 0x12);
    if (param_5 != (uint *)0x0) {
      *param_5 = (uint)*(byte *)(DAT_80436428 + uVar5);
    }
  }
  return param_1;
}



// ==== 802037b4  gnt4-OSDisableInterrupts-bl ====

ulonglong gnt4_OSDisableInterrupts_bl(void)

{
  uint in_MSR;
  
  return CONCAT44(in_MSR >> 0xf,in_MSR) & 0x1ffff7fff;
}



// ==== 802037c8  gnt4-OSEnableInterrupts-bl ====

ulonglong gnt4_OSEnableInterrupts_bl(void)

{
  uint in_MSR;
  
  return CONCAT44(in_MSR >> 0xf,in_MSR) & 0x1ffffffff | 0x8000;
}



// ==== 802037dc  gnt4-OSRestoreInterrupts-bl ====

uint gnt4_OSRestoreInterrupts_bl(void)

{
  uint in_MSR;
  
  return in_MSR >> 0xf & 1;
}



// ==== 80203800  gnt4-__OSSetInterruptHandler-bl ====

undefined4 gnt4___OSSetInterruptHandler_bl(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(DAT_80436430 + param_1 * 4);
  uVar1 = *puVar2;
  *puVar2 = param_2;
  return uVar1;
}



// ==== 8020381c  gnt4-__OSGetInterruptHandler-bl ====

undefined4 gnt4___OSGetInterruptHandler_bl(short param_1)

{
  return *(undefined4 *)(DAT_80436430 + param_1 * 4);
}



// ==== 80203830  gnt4-__OSInterruptInit-bl ====

void gnt4___OSInterruptInit_bl(void)

{
  DAT_80436430 = &DAT_80003040;
  gnt4_memset(&DAT_80003040,0,0x80);
  DAT_800000c4 = 0;
  DAT_800000c8 = 0;
  DAT_cc003004 = 0xf0;
  gnt4___OSMaskInterrupts_bl(0xffffffe0);
  gnt4___OSSetExceptionHandler_bl(4,gnt4_ExternalInterruptHandler_bl);
  return;
}



// ==== 802038a4  gnt4-SetInterruptMask-bl ====

uint gnt4_SetInterruptMask_bl(uint param_1,uint param_2)

{
  int iVar1;
  ushort uVar3;
  uint uVar2;
  
  iVar1 = countLeadingZeros(param_1);
  if (iVar1 < 0xc) {
    if (iVar1 == 8) {
      uVar2 = DAT_cc006c00;
      uVar2 = uVar2 & 0xffffffd3;
      if ((param_2 & 0x800000) == 0) {
        uVar2 = uVar2 | 4;
      }
      DAT_cc006c00 = uVar2;
      param_1 = param_1 & 0xff7fffff;
    }
    else if (iVar1 < 8) {
      if (iVar1 < 5) {
        if (-1 < iVar1) {
          uVar3 = (ushort)((param_2 & 0x80000000) == 0);
          if ((param_2 & 0x40000000) == 0) {
            uVar3 = uVar3 | 2;
          }
          if ((param_2 & 0x20000000) == 0) {
            uVar3 = uVar3 | 4;
          }
          if ((param_2 & 0x10000000) == 0) {
            uVar3 = uVar3 | 8;
          }
          if ((param_2 & 0x8000000) == 0) {
            uVar3 = uVar3 | 0x10;
          }
          DAT_cc00401c = uVar3;
          param_1 = param_1 & 0x7ffffff;
        }
      }
      else {
        uVar3 = DAT_cc00500a;
        uVar3 = uVar3 & 0xfe07;
        if ((param_2 & 0x4000000) == 0) {
          uVar3 = uVar3 | 0x10;
        }
        if ((param_2 & 0x2000000) == 0) {
          uVar3 = uVar3 | 0x40;
        }
        if ((param_2 & 0x1000000) == 0) {
          uVar3 = uVar3 | 0x100;
        }
        DAT_cc00500a = uVar3;
        param_1 = param_1 & 0xf8ffffff;
      }
    }
    else {
      uVar2 = DAT_cc006800;
      uVar2 = uVar2 & 0xffffd3f0;
      if ((param_2 & 0x400000) == 0) {
        uVar2 = uVar2 | 1;
      }
      if ((param_2 & 0x200000) == 0) {
        uVar2 = uVar2 | 4;
      }
      if ((param_2 & 0x100000) == 0) {
        uVar2 = uVar2 | 0x400;
      }
      DAT_cc006800 = uVar2;
      param_1 = param_1 & 0xff8fffff;
    }
  }
  else if (iVar1 < 0x11) {
    if (iVar1 < 0xf) {
      uVar2 = DAT_cc006814;
      uVar2 = uVar2 & 0xfffff3f0;
      if ((param_2 & 0x80000) == 0) {
        uVar2 = uVar2 | 1;
      }
      if ((param_2 & 0x40000) == 0) {
        uVar2 = uVar2 | 4;
      }
      if ((param_2 & 0x20000) == 0) {
        uVar2 = uVar2 | 0x400;
      }
      DAT_cc006814 = uVar2;
      param_1 = param_1 & 0xfff1ffff;
    }
    else {
      uVar2 = DAT_cc006828;
      uVar2 = uVar2 & 0xfffffff0;
      if ((param_2 & 0x10000) == 0) {
        uVar2 = uVar2 | 1;
      }
      if ((param_2 & 0x8000) == 0) {
        uVar2 = uVar2 | 4;
      }
      DAT_cc006828 = uVar2;
      param_1 = param_1 & 0xfffe7fff;
    }
  }
  else if (iVar1 < 0x1b) {
    uVar2 = 0xf0;
    if ((param_2 & 0x4000) == 0) {
      uVar2 = 0x8f0;
    }
    if ((param_2 & 0x800) == 0) {
      uVar2 = uVar2 | 8;
    }
    if ((param_2 & 0x400) == 0) {
      uVar2 = uVar2 | 4;
    }
    if ((param_2 & 0x200) == 0) {
      uVar2 = uVar2 | 2;
    }
    if ((param_2 & 0x100) == 0) {
      uVar2 = uVar2 | 1;
    }
    if ((param_2 & 0x80) == 0) {
      uVar2 = uVar2 | 0x100;
    }
    if ((param_2 & 0x40) == 0) {
      uVar2 = uVar2 | 0x1000;
    }
    if ((param_2 & 0x2000) == 0) {
      uVar2 = uVar2 | 0x200;
    }
    if ((param_2 & 0x1000) == 0) {
      uVar2 = uVar2 | 0x400;
    }
    if ((param_2 & 0x20) == 0) {
      uVar2 = uVar2 | 0x2000;
    }
    DAT_cc003004 = uVar2;
    param_1 = param_1 & 0xffff801f;
  }
  return param_1;
}



// ==== 80203b7c  gnt4-__OSMaskInterrupts-bl ====

uint gnt4___OSMaskInterrupts_bl(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_800000c4;
  uVar2 = DAT_800000c4 | DAT_800000c8;
  DAT_800000c4 = param_1 | DAT_800000c4;
  uVar3 = DAT_800000c4 | DAT_800000c8;
  for (uVar2 = param_1 & ~uVar2; uVar2 != 0; uVar2 = gnt4_SetInterruptMask_bl(uVar2,uVar3)) {
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80203c04  gnt4-__OSUnmaskInterrupts-bl ====

uint gnt4___OSUnmaskInterrupts_bl(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_800000c4;
  uVar2 = DAT_800000c4 | DAT_800000c8;
  DAT_800000c4 = DAT_800000c4 & ~param_1;
  uVar3 = DAT_800000c4 | DAT_800000c8;
  for (uVar2 = param_1 & uVar2; uVar2 != 0; uVar2 = gnt4_SetInterruptMask_bl(uVar2,uVar3)) {
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80203c8c  gnt4-__OSDispatchInterrupt-bl ====

undefined8 gnt4___OSDispatchInterrupt_bl(undefined4 param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  code *pcVar8;
  undefined8 uVar9;
  
  uVar5 = DAT_cc003000;
  if (((uVar5 & 0xfffeffff) == 0) || (uVar3 = DAT_cc003004, (uVar5 & 0xfffeffff & uVar3) == 0)) {
    gnt4_OSLoadContext_bl(param_2);
  }
  uVar9 = CONCAT44(DAT_80436440,DAT_80436444);
  uVar3 = 0;
  if ((uVar5 & 0x80) != 0) {
    uVar1 = DAT_cc00401e;
    if ((uVar1 & 1) != 0) {
      uVar3 = 0x80000000;
    }
    if ((uVar1 & 2) != 0) {
      uVar3 = uVar3 | 0x40000000;
    }
    if ((uVar1 & 4) != 0) {
      uVar3 = uVar3 | 0x20000000;
    }
    if ((uVar1 & 8) != 0) {
      uVar3 = uVar3 | 0x10000000;
    }
    if ((uVar1 & 0x10) != 0) {
      uVar3 = uVar3 | 0x8000000;
    }
  }
  if ((uVar5 & 0x40) != 0) {
    uVar1 = DAT_cc00500a;
    if ((uVar1 & 8) != 0) {
      uVar3 = uVar3 | 0x4000000;
    }
    if ((uVar1 & 0x20) != 0) {
      uVar3 = uVar3 | 0x2000000;
    }
    if ((uVar1 & 0x80) != 0) {
      uVar3 = uVar3 | 0x1000000;
    }
  }
  if (((uVar5 & 0x20) != 0) && (uVar2 = DAT_cc006c00, (uVar2 & 8) != 0)) {
    uVar3 = uVar3 | 0x800000;
  }
  if ((uVar5 & 0x10) != 0) {
    uVar2 = DAT_cc006800;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x400000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x200000;
    }
    if ((uVar2 & 0x800) != 0) {
      uVar3 = uVar3 | 0x100000;
    }
    uVar2 = DAT_cc006814;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x80000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x40000;
    }
    if ((uVar2 & 0x800) != 0) {
      uVar3 = uVar3 | 0x20000;
    }
    uVar2 = DAT_cc006828;
    if ((uVar2 & 2) != 0) {
      uVar3 = uVar3 | 0x10000;
    }
    if ((uVar2 & 8) != 0) {
      uVar3 = uVar3 | 0x8000;
    }
  }
  if ((uVar5 & 0x2000) != 0) {
    uVar3 = uVar3 | 0x20;
  }
  if ((uVar5 & 0x1000) != 0) {
    uVar3 = uVar3 | 0x40;
  }
  if ((uVar5 & 0x400) != 0) {
    uVar3 = uVar3 | 0x1000;
  }
  if ((uVar5 & 0x200) != 0) {
    uVar3 = uVar3 | 0x2000;
  }
  if ((uVar5 & 0x100) != 0) {
    uVar3 = uVar3 | 0x80;
  }
  if ((uVar5 & 8) != 0) {
    uVar3 = uVar3 | 0x800;
  }
  if ((uVar5 & 4) != 0) {
    uVar3 = uVar3 | 0x400;
  }
  if ((uVar5 & 2) != 0) {
    uVar3 = uVar3 | 0x200;
  }
  if ((uVar5 & 0x800) != 0) {
    uVar3 = uVar3 | 0x4000;
  }
  if ((uVar5 & 1) != 0) {
    uVar3 = uVar3 | 0x100;
  }
  uVar3 = uVar3 & ~(DAT_800000c4 | DAT_800000c8);
  if (uVar3 != 0) {
    for (puVar4 = &DAT_803a4b08; uVar5 = uVar3 & *puVar4, uVar5 == 0; puVar4 = puVar4 + 1) {
    }
    uVar6 = countLeadingZeros(uVar5);
    iVar7 = (int)(short)uVar6;
    pcVar8 = *(code **)(DAT_80436430 + iVar7 * 4);
    if (pcVar8 != (code *)0x0) {
      if (4 < iVar7) {
        DAT_80436438 = (short)uVar6;
        uVar9 = gnt4_OSGetTime_bl();
        DAT_80436434 = *(undefined4 *)(param_2 + 0x198);
      }
      DAT_80436440 = (undefined4)((ulonglong)uVar9 >> 0x20);
      DAT_80436444 = (undefined4)uVar9;
      gnt4_OSDisableScheduler_bl();
      (*pcVar8)(iVar7,param_2);
      gnt4_OSEnableScheduler_bl();
      gnt4___OSReschedule_bl();
      gnt4_OSLoadContext_bl(param_2);
    }
  }
  uVar9 = gnt4_OSLoadContext_bl(param_2);
  return uVar9;
}



// ==== 80203fd0  gnt4-ExternalInterruptHandler-bl ====

undefined8
gnt4_ExternalInterruptHandler_bl
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
  uVar1 = gnt4___OSDispatchInterrupt_bl(param_1,(int)param_2);
  return uVar1;
}



// ==== 80204020  gnt4-__OSModuleInit-bl ====

void gnt4___OSModuleInit_bl(void)

{
  DAT_800030cc = 0;
  DAT_800030c8 = 0;
  DAT_800030d0 = 0;
  return;
}



// ==== 80204038  gnt4-OSGetPhysicalMemSize-bl ====

undefined4 gnt4_OSGetPhysicalMemSize_bl(void)

{
  return DAT_80000028;
}



// ==== 80204044  gnt4-OnReset__-bl ====

undefined4 gnt4_OnReset___bl(int param_1)

{
  if (param_1 != 0) {
    DAT_cc004010 = 0xff;
    gnt4___OSMaskInterrupts_bl(0xf0000000);
  }
  return 1;
}



// ==== 80204080  gnt4-MEMIntrruptHandler-bl ====

void gnt4_MEMIntrruptHandler_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 *param_10)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 in_r9;
  undefined4 in_r10;
  
  uVar3 = DAT_cc004024;
  uVar2 = DAT_cc004022;
  uVar1 = DAT_cc00401e;
  DAT_cc004020 = 0;
  if (DAT_803d694c == (code *)0x0) {
    gnt4___OSUnhandledException_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xf,param_10,
               (uint)uVar1,(uVar3 & 0x3ff) << 0x10 | (uint)uVar2,(uint)uVar3,&DAT_cc004000,in_r9,
               in_r10);
  }
  else {
    (*DAT_803d694c)(0xf);
  }
  return;
}



// ==== 802040ec  gnt4-Config24MB-bl ====

void gnt4_Config24MB_bl(void)

{
  uint in_MSR;
  
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  returnFromInterrupt(in_MSR,in_MSR | 0x30);
  return;
}



// ==== 8020416c  gnt4-Config48MB-bl ====

void gnt4_Config48MB_bl(void)

{
  uint in_MSR;
  
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  instructionSynchronize();
  returnFromInterrupt(in_MSR,in_MSR | 0x30);
  return;
}



// ==== 802041ec  gnt4-RealMode-bl ====

uint gnt4_RealMode_bl(void)

{
  uint in_MSR;
  
  returnFromInterrupt(in_MSR,in_MSR & 0xffffffcf);
  return in_MSR & 0xffffffcf;
}



// ==== 80204204  gnt4-__OSInitMemoryProtection-bl ====

void gnt4___OSInitMemoryProtection_bl(void)

{
  uint uVar1;
  
  uVar1 = DAT_800000f0;
  gnt4_OSDisableInterrupts_bl();
  DAT_cc004020 = 0;
  DAT_cc004010 = 0xff;
  gnt4___OSMaskInterrupts_bl(0xf0000000);
  gnt4___OSSetInterruptHandler_bl(0,gnt4_MEMIntrruptHandler_bl);
  gnt4___OSSetInterruptHandler_bl(1,gnt4_MEMIntrruptHandler_bl);
  gnt4___OSSetInterruptHandler_bl(2,gnt4_MEMIntrruptHandler_bl);
  gnt4___OSSetInterruptHandler_bl(3,gnt4_MEMIntrruptHandler_bl);
  gnt4___OSSetInterruptHandler_bl(4,gnt4_MEMIntrruptHandler_bl);
  gnt4_OSRegisterResetFunction_bl(-0x7fc5b4c8);
  if ((DAT_800000f0 < DAT_80000028) && (DAT_800000f0 == 0x1800000)) {
    gnt4_DCInvalidateRange_bl(0x81800000,0x1800000);
    DAT_cc004028 = 2;
  }
  if (uVar1 < 0x1800001) {
    gnt4_RealMode_bl();
  }
  else if (uVar1 < 0x3000001) {
    gnt4_RealMode_bl();
  }
  gnt4___OSUnmaskInterrupts_bl(0x8000000);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8020431c  gnt4-__OSUnlockAllMutex-bl ====

void gnt4___OSUnlockAllMutex_bl(int param_1)

{
  int *piVar1;
  int iVar2;
  
  while (piVar1 = *(int **)(param_1 + 0x2f4), piVar1 != (int *)0x0) {
    iVar2 = piVar1[4];
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x2f8) = 0;
    }
    else {
      *(undefined4 *)(iVar2 + 0x14) = 0;
    }
    *(int *)(param_1 + 0x2f4) = iVar2;
    piVar1[3] = 0;
    piVar1[2] = 0;
    gnt4_OSWakeupThread_bl(piVar1);
  }
  return;
}



// ==== 8020438c  zz_020438c_ ====

void zz_020438c_(void)

{
  sync(0);
  instructionSynchronize();
  return;
}



// ==== 802043a8  zz_02043a8_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_02043a8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 auStack_370 [12];
  undefined4 auStack_340 [12];
  undefined4 auStack_310 [12];
  undefined1 auStack_2e0 [712];
  
  gnt4_OSDisableInterrupts_bl();
  uVar5 = 1;
  _DAT_817ffffc = 0;
  _DAT_817ffff8 = 0;
  DAT_800030e2 = 1;
  _DAT_812fdff0 = DAT_80436448;
  _DAT_812fdfec = DAT_8043644c;
  uVar4 = DAT_80436448;
  gnt4_OSClearContext_bl((int)auStack_2e0);
  uVar6 = gnt4_OSSetCurrentContext_bl((uint)auStack_2e0);
  gnt4_DVDInit_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (int)((ulonglong)uVar6 >> 0x20),(int)uVar6,uVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
  gnt4_DVDSetAutoInvalidation(1);
  gnt4_DVDResume_bl();
  DAT_80436450 = 0;
  gnt4___DVDPrepareResetAsync_bl(&LAB_8020439c);
  gnt4___OSMaskInterrupts_bl(0xffffffe0);
  gnt4___OSUnmaskInterrupts_bl(0x400);
  gnt4_OSEnableInterrupts_bl();
  uVar6 = gnt4_OSGetTime_bl();
  uVar1 = DAT_800000f8 >> 2;
  while (DAT_80436450 != 1) {
    iVar3 = gnt4_DVDCheckDisk_bl();
    if ((iVar3 == 0) ||
       (uVar7 = gnt4_OSGetTime_bl(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar7 - (uint)uVar6) +
       ((int)((ulonglong)uVar7 >> 0x20) -
        ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000))) {
      gnt4___OSDoHotReset_bl(_DAT_817ffffc);
    }
  }
  if ((DAT_804363cc == 0) && (iVar3 = gnt4_DVDGetCurrentDiskID_bl(), *(char *)(iVar3 + 8) != '\0'))
  {
    zz_0214994_(0);
    AISetStreamVolLeft(0);
    gnt4_cbForGetStreamErrorStatusSync_bl(auStack_310,0);
    uVar6 = gnt4_OSGetTime_bl();
    uVar1 = DAT_800000f8 >> 2;
    while (iVar3 = gnt4_DVDGetCommandBlockStatus_bl((int)auStack_310), iVar3 != 0) {
      iVar3 = gnt4_DVDCheckDisk_bl();
      if ((iVar3 == 0) ||
         (uVar7 = gnt4_OSGetTime_bl(),
         0x80000000 <
         (uint)(uVar1 < (uint)uVar7 - (uint)uVar6) +
         ((int)((ulonglong)uVar7 >> 0x20) -
          ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000))) {
        gnt4___OSDoHotReset_bl(_DAT_817ffffc);
      }
    }
    AISetStreamPlayState(0);
  }
  gnt4_DVDReadAbsAsyncPrio_bl(auStack_340,&DAT_803d6c40,0x20,0x2440,0,0);
  uVar6 = gnt4_OSGetTime_bl();
  uVar1 = DAT_800000f8 >> 2;
  while (iVar3 = gnt4_DVDGetCommandBlockStatus_bl((int)auStack_340), iVar3 != 0) {
    iVar3 = gnt4_DVDCheckDisk_bl();
    if ((iVar3 == 0) ||
       (uVar7 = gnt4_OSGetTime_bl(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar7 - (uint)uVar6) +
       ((int)((ulonglong)uVar7 >> 0x20) -
        ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000))) {
      gnt4___OSDoHotReset_bl(_DAT_817ffffc);
    }
  }
  uVar2 = DAT_803d6c58 + 0x1fU & 0xffffffe0;
  gnt4_DVDReadAbsAsyncPrio_bl(auStack_370,0x81300000,uVar2,DAT_803d6c54 + 0x2460,0,0);
  uVar6 = gnt4_OSGetTime_bl();
  uVar1 = DAT_800000f8 >> 2;
  while (iVar3 = gnt4_DVDGetCommandBlockStatus_bl((int)auStack_370), iVar3 != 0) {
    iVar3 = gnt4_DVDCheckDisk_bl();
    if ((iVar3 == 0) ||
       (uVar7 = gnt4_OSGetTime_bl(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar7 - (uint)uVar6) +
       ((int)((ulonglong)uVar7 >> 0x20) -
        ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000))) {
      gnt4___OSDoHotReset_bl(_DAT_817ffffc);
    }
  }
  gnt4_ICInvalidateRange_bl(0x81300000,uVar2);
  gnt4_OSDisableInterrupts_bl();
  gnt4_ICFlashInvalidate_bl();
  zz_020438c_();
  return;
}



// ==== 802046e8  gnt4-OSRegisterResetFunction-bl ====

void gnt4_OSRegisterResetFunction_bl(int param_1)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = DAT_80436458; (iVar2 != 0 && (*(uint *)(iVar2 + 4) <= *(uint *)(param_1 + 4)));
      iVar2 = *(int *)(iVar2 + 8)) {
  }
  if (iVar2 != 0) {
    *(int *)(param_1 + 8) = iVar2;
    iVar1 = *(int *)(iVar2 + 0xc);
    *(int *)(iVar2 + 0xc) = param_1;
    *(int *)(param_1 + 0xc) = iVar1;
    if (iVar1 != 0) {
      *(int *)(iVar1 + 8) = param_1;
      return;
    }
    DAT_80436458 = param_1;
    return;
  }
  iVar2 = param_1;
  if (iRam8043645c != 0) {
    *(int *)(iRam8043645c + 8) = param_1;
    iVar2 = DAT_80436458;
  }
  DAT_80436458 = iVar2;
  *(int *)(param_1 + 0xc) = iRam8043645c;
  *(undefined4 *)(param_1 + 8) = 0;
  iRam8043645c = param_1;
  return;
}



// ==== 8020476c  zz_020476c_ ====

bool zz_020476c_(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  puVar4 = DAT_80436458;
  for (uVar3 = 0; (puVar4 != (undefined4 *)0x0 && (uVar3 == 0)); uVar3 = uVar3 >> 5) {
    uVar2 = (*(code *)*puVar4)(param_1);
    uVar3 = countLeadingZeros(uVar2);
    puVar4 = (undefined4 *)puVar4[2];
  }
  uVar2 = gnt4___OSSyncSram_bl();
  uVar1 = countLeadingZeros(uVar2);
  return uVar3 == 0 && uVar1 >> 5 == 0;
}



// ==== 80204800  gnt4-Reset-bl ====

/* WARNING: Removing unreachable block (ram,0x80204838) */
/* WARNING: Removing unreachable block (ram,0x80204864) */

void gnt4_Reset_bl(undefined4 param_1)

{
  instructionSynchronize();
  sync(0);
  do {
  } while( true );
}



// ==== 80204870  gnt4-__OSDoHotReset-bl ====

void gnt4___OSDoHotReset_bl(int param_1)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_cc002002 = 0;
  gnt4_ICFlashInvalidate_bl();
  gnt4_Reset_bl(param_1 << 3);
  return;
}



// ==== 802048b8  zz_02048b8_ ====

bool zz_02048b8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,int param_11)

{
  ushort uVar1;
  uint uVar2;
  bool bVar7;
  undefined4 uVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar8;
  undefined4 *puVar9;
  uint unaff_r31;
  undefined8 uVar10;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  ulonglong uVar11;
  
  gnt4_OSDisableScheduler_bl();
  uVar10 = gnt4___OSStopAudioSystem_bl();
  if ((param_9 == 2) || ((param_9 == 0 && (DAT_80436460 != 0)))) {
    bVar7 = gnt4___PADDisableRecalibration_bl(1);
    unaff_r31 = (uint)bVar7;
  }
  do {
    puVar9 = DAT_80436458;
    for (uVar8 = 0; (puVar9 != (undefined4 *)0x0 && (uVar8 == 0)); uVar8 = uVar8 >> 5) {
      uVar3 = (*(code *)*puVar9)(0);
      uVar8 = countLeadingZeros(uVar3);
      puVar9 = (undefined4 *)puVar9[2];
      uVar10 = extraout_f1;
    }
    uVar3 = gnt4___OSSyncSram_bl();
    uVar2 = countLeadingZeros(uVar3);
  } while (uVar8 != 0 || uVar2 >> 5 != 0);
  if ((param_9 == 1) && (param_11 != 0)) {
    puVar4 = gnt4___OSLockSram_bl();
    *(byte *)((int)puVar4 + 0x13) = *(byte *)((int)puVar4 + 0x13) | 0x40;
    uVar10 = gnt4___OSUnlockSram_bl(1);
    do {
      iVar5 = gnt4___OSSyncSram_bl();
    } while (iVar5 == 0);
  }
  uVar11 = gnt4_OSDisableInterrupts_bl();
  uVar3 = (undefined4)uVar11;
  puVar9 = DAT_80436458;
  for (uVar8 = 0; (puVar9 != (undefined4 *)0x0 && (uVar8 == 0)); uVar8 = uVar8 >> 5) {
    uVar10 = (*(code *)*puVar9)(1,uVar3);
    uVar3 = (undefined4)uVar10;
    uVar8 = countLeadingZeros((int)((ulonglong)uVar10 >> 0x20));
    puVar9 = (undefined4 *)puVar9[2];
    uVar10 = extraout_f1_00;
  }
  gnt4___OSSyncSram_bl();
  gnt4_LCDisable_bl();
  if (param_9 == 1) {
    gnt4_OSDisableInterrupts_bl();
    DAT_cc002002 = 0;
    gnt4_ICFlashInvalidate_bl();
    gnt4_Reset_bl(param_10 << 3);
    iVar5 = DAT_800000dc;
  }
  else {
    iVar5 = DAT_800000dc;
    if (param_9 == 0) {
      DAT_800030ec = DAT_80436460;
      if (DAT_80436460 != 0) {
        gnt4___PADDisableRecalibration_bl(unaff_r31);
        iVar5 = DAT_800000dc;
      }
      while (iVar6 = iVar5, iVar6 != 0) {
        uVar1 = *(ushort *)(iVar6 + 0x2c8);
        iVar5 = *(int *)(iVar6 + 0x2fc);
        if ((uVar1 == 4) || ((uVar1 < 4 && (uVar1 == 1)))) {
          uVar10 = gnt4_OSCancelThread_bl(iVar6);
        }
      }
      gnt4_OSEnableScheduler_bl();
      zz_02043a8_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      iVar5 = DAT_800000dc;
    }
  }
  while (iVar6 = iVar5, iVar6 != 0) {
    uVar1 = *(ushort *)(iVar6 + 0x2c8);
    iVar5 = *(int *)(iVar6 + 0x2fc);
    if ((uVar1 == 4) || ((uVar1 < 4 && (uVar1 == 1)))) {
      gnt4_OSCancelThread_bl(iVar6);
    }
  }
  gnt4_memset(&DAT_80000040,0,0x8c);
  gnt4_memset(&DAT_800000d4,0,0x14);
  gnt4_memset(&DAT_800000f4,0,4);
  gnt4_memset(&DAT_80003000,0,0xc0);
  gnt4_memset(&DAT_800030c8,0,0xc);
  gnt4_memset(&DAT_800030e2,0,1);
  bVar7 = gnt4___PADDisableRecalibration_bl(unaff_r31);
  return bVar7;
}



// ==== 80204b70  zz_0204b70_ ====

uint zz_0204b70_(void)

{
  uint uVar1;
  
  if (DAT_800030e2 == '\0') {
    uVar1 = DAT_cc003024;
    uVar1 = uVar1 >> 3;
  }
  else {
    uVar1 = 0x80000000;
  }
  return uVar1;
}



// ==== 80204ba0  gnt4-__OSResetSWInterruptHandler-bl ====

void gnt4___OSResetSWInterruptHandler_bl(void)

{
  uint uVar1;
  uint uVar2;
  code *pcVar3;
  longlong lVar4;
  longlong lVar5;
  
  lVar4 = gnt4___OSGetSystemTime_bl();
  uVar1 = DAT_800000f8 / 500000;
  do {
    DAT_80436480 = (int)((ulonglong)lVar4 >> 0x20);
    DAT_80436484 = (uint)lVar4;
    lVar5 = gnt4___OSGetSystemTime_bl();
    lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
    if (((uint)lVar5 - DAT_80436484 < uVar1 * 100 >> 3) + 0x80000000 <=
        ((int)((ulonglong)lVar5 >> 0x20) - ((uint)((uint)lVar5 < DAT_80436484) + DAT_80436480) ^
        0x80000000)) break;
    uVar2 = DAT_cc003000;
  } while ((uVar2 & 0x10000) == 0);
  uVar1 = DAT_cc003000;
  if ((uVar1 & 0x10000) == 0) {
    DAT_8043646c = 1;
    DAT_80436470 = 1;
    gnt4___OSMaskInterrupts_bl(0x200);
    pcVar3 = DAT_80436468;
    if (DAT_80436468 != (code *)0x0) {
      DAT_80436468 = (code *)0x0;
      (*pcVar3)();
    }
  }
  DAT_cc003000 = 2;
  return;
}



// ==== 80204c94  gnt4-OSGetResetButtonState-bl ====

uint gnt4_OSGetResetButtonState_bl(void)

{
  uint uVar1;
  byte bVar2;
  longlong lVar3;
  longlong lVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  longlong lVar11;
  undefined8 uVar12;
  ulonglong uVar13;
  
  gnt4_OSDisableInterrupts_bl();
  lVar11 = gnt4___OSGetSystemTime_bl();
  lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
  uVar5 = (uint)((ulonglong)lVar11 >> 0x20);
  uVar6 = (uint)lVar11;
  uVar10 = DAT_cc003000;
  if ((uVar10 & 0x10000) == 0) {
    if (DAT_8043646c == 0) {
      DAT_8043646c = 1;
      uVar10 = (uint)(DAT_8043647c != 0 || DAT_80436478 != 0);
      lVar3 = CONCAT44(DAT_80436478,DAT_8043647c);
      lVar4 = lVar11;
    }
    else {
      bVar2 = 1;
      if ((DAT_8043647c == 0 && DAT_80436478 == 0) &&
         ((uint)((DAT_800000f8 / 500000) * 100 >> 3 < uVar6 - DAT_80436484) +
          (uVar5 - ((uint)(uVar6 < DAT_80436484) + DAT_80436480) ^ 0x80000000) < 0x80000001)) {
        bVar2 = 0;
      }
      uVar10 = (uint)bVar2;
      lVar3 = CONCAT44(DAT_80436478,DAT_8043647c);
      lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
    }
  }
  else if (DAT_8043646c == 0) {
    if ((DAT_8043647c == 0 && DAT_80436478 == 0) ||
       ((uVar6 - DAT_8043647c < (DAT_800000f8 / 4000) * 0x28) + 0x80000000 <=
        (uVar5 - ((uint)(uVar6 < DAT_8043647c) + DAT_80436478) ^ 0x80000000))) {
      uVar10 = 0;
      lVar3 = 0;
      lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
    }
    else {
      uVar10 = 1;
      lVar3 = CONCAT44(DAT_80436478,DAT_8043647c);
      lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
    }
  }
  else {
    DAT_8043646c = 0;
    uVar10 = DAT_80436470;
    lVar3 = lVar11;
    if (DAT_80436470 == 0) {
      lVar3 = 0;
      lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
    }
  }
  DAT_80436480 = (int)((ulonglong)lVar4 >> 0x20);
  DAT_80436484 = (uint)lVar4;
  DAT_80436478 = (int)((ulonglong)lVar3 >> 0x20);
  DAT_8043647c = (uint)lVar3;
  DAT_80436470 = uVar10;
  if ((DAT_800030e3 & 0x3f) != 0) {
    uVar9 = (DAT_800030e3 & 0x3f) * 0x3c;
    uVar1 = DAT_800000f8 >> 2;
    uVar7 = uVar9 * uVar1;
    uVar8 = DAT_804363fc + uVar7;
    uVar7 = DAT_804363f8 +
            (int)((ulonglong)uVar9 * (ulonglong)uVar1 >> 0x20) + (uint)CARRY4(DAT_804363fc,uVar7);
    if ((uVar7 ^ 0x80000000) < (uint)(uVar8 < uVar6) + (uVar5 ^ 0x80000000)) {
      uVar12 = gnt4___div2i(uVar5 - ((uVar6 < uVar8) + uVar7),uVar6 - uVar8,0,uVar1);
      uVar13 = gnt4___div2i((uint)((ulonglong)uVar12 >> 0x20),(uint)uVar12,0,2);
      lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
      lVar3 = CONCAT44(DAT_80436478,DAT_8043647c);
      if ((uVar13 & 1) == 0) {
        uVar10 = 1;
        lVar3 = CONCAT44(DAT_80436478,DAT_8043647c);
        lVar4 = CONCAT44(DAT_80436480,DAT_80436484);
      }
      else {
        uVar10 = 0;
      }
    }
  }
  DAT_80436480 = (int)((ulonglong)lVar4 >> 0x20);
  DAT_80436484 = (uint)lVar4;
  DAT_80436478 = (int)((ulonglong)lVar3 >> 0x20);
  DAT_8043647c = (uint)lVar3;
  gnt4_OSRestoreInterrupts_bl();
  return uVar10;
}



// ==== 80204f2c  gnt4-WriteSramCallback-bl ====

void gnt4_WriteSramCallback_bl(void)

{
  DAT_803d6cac = gnt4_WriteSram_bl((byte *)((int)&DAT_803d6c60 + DAT_803d6ca0),DAT_803d6ca0,
                                   0x40 - DAT_803d6ca0);
  if (DAT_803d6cac != 0) {
    DAT_803d6ca0 = 0x40;
  }
  return;
}



// ==== 80204f8c  gnt4-WriteSram-bl ====

uint gnt4_WriteSram_bl(byte *param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint local_14 [2];
  
  iVar4 = gnt4_EXILock_bl(0,1,-0x7fdfb0d4);
  if (iVar4 == 0) {
    uVar5 = 0;
  }
  else {
    iVar4 = gnt4_EXISelect_bl(0,1,3);
    if (iVar4 == 0) {
      gnt4_EXIUnlock_bl(0);
      uVar5 = 0;
    }
    else {
      local_14[0] = param_2 * 0x40 + 0x100U | 0xa0000000;
      uVar6 = gnt4_EXIImm_bl(0,(byte *)local_14,4,1,0);
      uVar5 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXISync(0);
      uVar1 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXIImmEx(0,param_1,param_3,1);
      uVar2 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXIDeselect(0);
      uVar3 = countLeadingZeros(uVar6);
      gnt4_EXIUnlock_bl(0);
      uVar5 = countLeadingZeros((uVar5 | uVar1 | uVar2 | uVar3) >> 5);
      uVar5 = uVar5 >> 5;
    }
  }
  return uVar5;
}



// ==== 802050a4  gnt4-__OSInitSram-bl ====

void gnt4___OSInitSram_bl(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  ushort uVar7;
  uint uVar8;
  byte local_10 [8];
  
  uVar8 = 0;
  DAT_803d6ca4 = 0;
  DAT_803d6ca8 = 0;
  gnt4_DCInvalidateRange_bl(0x803d6c60,0x40);
  iVar5 = gnt4_EXILock_bl(0,1,0);
  if (iVar5 != 0) {
    iVar5 = gnt4_EXISelect_bl(0,1,3);
    if (iVar5 == 0) {
      gnt4_EXIUnlock_bl(0);
    }
    else {
      local_10[0] = 0x20;
      local_10[1] = 0;
      local_10[2] = 1;
      local_10[3] = 0;
      uVar6 = gnt4_EXIImm_bl(0,local_10,4,1,0);
      uVar8 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXISync(0);
      uVar1 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXIDma_bl(0,0x803d6c60,0x40,0,0);
      uVar2 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXISync(0);
      uVar3 = countLeadingZeros(uVar6);
      uVar6 = gnt4_EXIDeselect(0);
      uVar4 = countLeadingZeros(uVar6);
      gnt4_EXIUnlock_bl(0);
      uVar8 = countLeadingZeros((uVar8 | uVar1 | uVar2 | uVar3 | uVar4) >> 5);
      uVar8 = uVar8 >> 5;
    }
  }
  DAT_803d6ca0 = 0x40;
  DAT_803d6cac = uVar8;
  uVar7 = gnt4_OSGetGbsMode_bl();
  gnt4_OSSetGbsMode_bl(uVar7);
  return;
}



// ==== 802051e0  gnt4-__OSLockSram-bl ====

undefined2 * gnt4___OSLockSram_bl(void)

{
  undefined2 *puVar1;
  ulonglong uVar2;
  
  puVar1 = &DAT_803d6c60;
  uVar2 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar2 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = (undefined2 *)0x0;
  }
  return puVar1;
}



// ==== 8020523c  gnt4-__OSLockSramEx-bl ====

undefined2 * gnt4___OSLockSramEx_bl(void)

{
  undefined2 *puVar1;
  ulonglong uVar2;
  
  uVar2 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    puVar1 = &DAT_803d6c74;
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar2 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = (undefined2 *)0x0;
  }
  return puVar1;
}



// ==== 80205298  gnt4-UnlockSram-bl ====

/* WARNING: Removing unreachable block (ram,0x8020530c) */
/* WARNING: Removing unreachable block (ram,0x80205434) */

uint gnt4_UnlockSram_bl(int param_1,uint param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  ushort *puVar7;
  int iVar8;
  byte *pbVar9;
  int iVar10;
  uint local_20 [3];
  
  if (param_1 != 0) {
    if (param_2 == 0) {
      if (2 < ((byte)DAT_803d6c72 & 3)) {
        DAT_803d6c72._1_1_ = (byte)DAT_803d6c72 & 0xfc;
      }
      DAT_803d6c62 = 0;
      DAT_803d6c60 = 0;
      puVar7 = &DAT_803d6c6c;
      iVar10 = 4;
      do {
        DAT_803d6c60 = DAT_803d6c60 + *puVar7;
        uVar1 = *puVar7;
        puVar7 = puVar7 + 1;
        DAT_803d6c62 = DAT_803d6c62 + ~uVar1;
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
    }
    if (param_2 < DAT_803d6ca0) {
      DAT_803d6ca0 = param_2;
    }
    uVar2 = DAT_803d6ca0;
    if ((DAT_803d6ca0 < 0x15) &&
       (((DAT_803d6c9c & 0x7c00) == 0x5000 || ((DAT_803d6c9c & 0xc0) == 0xc0)))) {
      DAT_803d6c9c = 0;
    }
    iVar8 = 0x40 - DAT_803d6ca0;
    pbVar9 = (byte *)((int)&DAT_803d6c60 + DAT_803d6ca0);
    iVar10 = gnt4_EXILock_bl(0,1,-0x7fdfb0d4);
    if (iVar10 == 0) {
      DAT_803d6cac = 0;
    }
    else {
      iVar10 = gnt4_EXISelect_bl(0,1,3);
      if (iVar10 == 0) {
        gnt4_EXIUnlock_bl(0);
        DAT_803d6cac = 0;
      }
      else {
        local_20[0] = uVar2 * 0x40 + 0x100 | 0xa0000000;
        uVar6 = gnt4_EXIImm_bl(0,(byte *)local_20,4,1,0);
        uVar2 = countLeadingZeros(uVar6);
        uVar6 = gnt4_EXISync(0);
        uVar3 = countLeadingZeros(uVar6);
        uVar6 = gnt4_EXIImmEx(0,pbVar9,iVar8,1);
        uVar4 = countLeadingZeros(uVar6);
        uVar6 = gnt4_EXIDeselect(0);
        uVar5 = countLeadingZeros(uVar6);
        gnt4_EXIUnlock_bl(0);
        uVar2 = countLeadingZeros((uVar2 | uVar3 | uVar4 | uVar5) >> 5);
        DAT_803d6cac = uVar2 >> 5;
      }
    }
    if (DAT_803d6cac != 0) {
      DAT_803d6ca0 = 0x40;
    }
  }
  DAT_803d6ca8 = 0;
  gnt4_OSRestoreInterrupts_bl();
  return DAT_803d6cac;
}



// ==== 802055d4  gnt4-__OSUnlockSram-bl ====

void gnt4___OSUnlockSram_bl(int param_1)

{
  gnt4_UnlockSram_bl(param_1,0);
  return;
}



// ==== 802055f8  gnt4-__OSUnlockSramEx-bl ====

void gnt4___OSUnlockSramEx_bl(int param_1)

{
  gnt4_UnlockSram_bl(param_1,0x14);
  return;
}



// ==== 8020561c  gnt4-__OSSyncSram-bl ====

undefined4 gnt4___OSSyncSram_bl(void)

{
  return DAT_803d6cac;
}



// ==== 8020562c  gnt4-__OSReadROM-bl ====

uint gnt4___OSReadROM_bl(uint param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  int local_14 [2];
  
  gnt4_DCInvalidateRange_bl(param_1,param_2);
  iVar5 = gnt4_EXILock_bl(0,1,0);
  if (iVar5 == 0) {
    uVar6 = 0;
  }
  else {
    iVar5 = gnt4_EXISelect_bl(0,1,3);
    if (iVar5 == 0) {
      gnt4_EXIUnlock_bl(0);
      uVar6 = 0;
    }
    else {
      local_14[0] = param_3 << 6;
      uVar7 = gnt4_EXIImm_bl(0,(byte *)local_14,4,1,0);
      uVar6 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXISync(0);
      uVar1 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXIDma_bl(0,param_1,param_2,0,0);
      uVar2 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXISync(0);
      uVar3 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXIDeselect(0);
      uVar4 = countLeadingZeros(uVar7);
      gnt4_EXIUnlock_bl(0);
      uVar6 = countLeadingZeros((uVar6 | uVar1 | uVar2 | uVar3 | uVar4) >> 5);
      uVar6 = uVar6 >> 5;
    }
  }
  return uVar6;
}



// ==== 80205750  gnt4-OSGetSoundMode-bl ====

bool gnt4_OSGetSoundMode_bl(void)

{
  byte bVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  puVar2 = &DAT_803d6c60;
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  bVar1 = *(byte *)((int)puVar2 + 0x13);
  gnt4_UnlockSram_bl(0,0);
  return (bVar1 & 4) != 0;
}



// ==== 802057d0  gnt4-OSSetSoundMode-bl ====

void gnt4_OSSetSoundMode_bl(byte param_1)

{
  byte bVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  puVar2 = &DAT_803d6c60;
  bVar1 = (param_1 & 1) << 2;
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  if (bVar1 == (*(byte *)((int)puVar2 + 0x13) & 4)) {
    gnt4_UnlockSram_bl(0,0);
  }
  else {
    *(byte *)((int)puVar2 + 0x13) = *(byte *)((int)puVar2 + 0x13) & 0xfb;
    *(byte *)((int)puVar2 + 0x13) = *(byte *)((int)puVar2 + 0x13) | bVar1;
    gnt4_UnlockSram_bl(1,0);
  }
  return;
}



// ==== 80205874  gnt4-OSGetProgressiveMode-bl ====

byte gnt4_OSGetProgressiveMode_bl(void)

{
  byte bVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  puVar2 = &DAT_803d6c60;
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  bVar1 = *(byte *)((int)puVar2 + 0x13);
  gnt4_UnlockSram_bl(0,0);
  return bVar1 >> 7;
}



// ==== 802058e4  gnt4-OSSetProgressiveMode-bl ====

void gnt4_OSSetProgressiveMode_bl(char param_1)

{
  undefined2 *puVar1;
  ulonglong uVar2;
  
  puVar1 = &DAT_803d6c60;
  uVar2 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar2 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = (undefined2 *)0x0;
  }
  if ((byte)(param_1 << 7) == (*(byte *)((int)puVar1 + 0x13) & 0x80)) {
    gnt4_UnlockSram_bl(0,0);
  }
  else {
    *(byte *)((int)puVar1 + 0x13) = *(byte *)((int)puVar1 + 0x13) & 0x7f;
    *(byte *)((int)puVar1 + 0x13) = *(byte *)((int)puVar1 + 0x13) | param_1 << 7;
    gnt4_UnlockSram_bl(1,0);
  }
  return;
}



// ==== 80205988  OSGetLanguage ====

undefined1 OSGetLanguage(void)

{
  undefined1 uVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  puVar2 = &DAT_803d6c60;
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  uVar1 = *(undefined1 *)(puVar2 + 9);
  gnt4_UnlockSram_bl(0,0);
  return uVar1;
}



// ==== 802059f4  gnt4-OSGetWirelessID-bl ====

undefined2 gnt4_OSGetWirelessID_bl(int param_1)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    puVar2 = &DAT_803d6c74;
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  uVar1 = puVar2[param_1 + 0xe];
  gnt4_UnlockSram_bl(0,0x14);
  return uVar1;
}



// ==== 80205a78  gnt4-OSSetWirelessID-bl ====

void gnt4_OSSetWirelessID_bl(int param_1,short param_2)

{
  undefined2 *puVar1;
  ulonglong uVar2;
  
  uVar2 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    puVar1 = &DAT_803d6c74;
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar2 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = (undefined2 *)0x0;
  }
  if (puVar1[param_1 + 0xe] == param_2) {
    gnt4_UnlockSram_bl(0,0x14);
  }
  else {
    puVar1[param_1 + 0xe] = param_2;
    gnt4_UnlockSram_bl(1,0x14);
  }
  return;
}



// ==== 80205b24  gnt4-OSGetGbsMode-bl ====

undefined2 gnt4_OSGetGbsMode_bl(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  ulonglong uVar3;
  
  uVar3 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    puVar2 = &DAT_803d6c74;
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar3 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar2 = (undefined2 *)0x0;
  }
  uVar1 = puVar2[0x14];
  gnt4_UnlockSram_bl(0,0x14);
  return uVar1;
}



// ==== 80205b94  gnt4-OSSetGbsMode-bl ====

void gnt4_OSSetGbsMode_bl(ushort param_1)

{
  undefined2 *puVar1;
  ulonglong uVar2;
  
  if (((param_1 & 0x7c00) == 0x5000) || ((param_1 & 0xc0) == 0xc0)) {
    param_1 = 0;
  }
  uVar2 = gnt4_OSDisableInterrupts_bl();
  if (DAT_803d6ca8 == 0) {
    puVar1 = &DAT_803d6c74;
    DAT_803d6ca8 = 1;
    DAT_803d6ca4 = (int)(uVar2 >> 0x20);
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = (undefined2 *)0x0;
  }
  if (param_1 == puVar1[0x14]) {
    gnt4_UnlockSram_bl(0,0);
  }
  else {
    puVar1[0x14] = param_1;
    gnt4_UnlockSram_bl(1,0x14);
  }
  return;
}



// ==== 80205c4c  zz_0205c4c_ ====

void zz_0205c4c_(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  param_1[3] = 0;
  param_1[2] = 0;
  param_1[1] = 0;
  param_1[5] = 0xffffffff;
  param_1[4] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  return;
}



// ==== 80205c78  zz_0205c78_ ====

void zz_0205c78_(int param_1)

{
  undefined8 uVar1;
  
  *(undefined4 *)(param_1 + 0x28) = 1;
  uVar1 = gnt4_OSGetTime_bl();
  *(undefined8 *)(param_1 + 0x20) = uVar1;
  return;
}



// ==== 80205cb4  zz_0205cb4_ ====

undefined8 zz_0205cb4_(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  undefined8 uVar5;
  
  iVar3 = *(int *)(param_1 + 8);
  uVar2 = *(uint *)(param_1 + 0xc);
  if (*(int *)(param_1 + 0x28) != 0) {
    uVar5 = gnt4_OSGetTime_bl();
    uVar1 = (uint)uVar5 - *(uint *)(param_1 + 0x24);
    bVar4 = CARRY4(uVar2,uVar1);
    uVar2 = uVar2 + uVar1;
    iVar3 = iVar3 + ((int)((ulonglong)uVar5 >> 0x20) -
                    ((uint)((uint)uVar5 < *(uint *)(param_1 + 0x24)) + *(int *)(param_1 + 0x20))) +
                    (uint)bVar4;
  }
  return CONCAT44(iVar3,uVar2);
}



// ==== 80205d24  gnt4-SystemCallVector-bl ====

void gnt4_SystemCallVector_bl(void)

{
  undefined4 in_MSR;
  undefined4 in_SRR1;
  
  instructionSynchronize();
  sync(0);
  returnFromInterrupt(in_MSR,in_SRR1);
  return;
}



// ==== 80205d40  zz_0205d40_ ====

void zz_0205d40_(void)

{
  gnt4_memcpy(&DAT_80000c00,gnt4_SystemCallVector_bl,0x1c);
  gnt4_DCFlushRangeNoSync_bl(0x80000c00,0x100);
  sync(0);
  gnt4_ICInvalidateRange_bl(0x80000c00,0x100);
  return;
}



// ==== 80205d44  gnt4-__OSInitSystemCall-bl ====

void gnt4___OSInitSystemCall_bl(void)

{
  gnt4_memcpy(&DAT_80000c00,gnt4_SystemCallVector_bl,0x1c);
  gnt4_DCFlushRangeNoSync_bl(0x80000c00,0x100);
  sync(0);
  gnt4_ICInvalidateRange_bl(0x80000c00,0x100);
  return;
}



// ==== 80205da8  gnt4-DefaultSwitchThreadCallback-bl ====

void gnt4_DefaultSwitchThreadCallback_bl(void)

{
  return;
}



// ==== 80205dac  gnt4-__OSThreadInit-bl ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void gnt4___OSThreadInit_bl(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  DAT_803d7398 = 2;
  DAT_803d739a = 1;
  DAT_803d73a4 = 0x10;
  DAT_803d73a0 = 0x10;
  DAT_803d739c = 0;
  DAT_803d73a8 = 0xffffffff;
  DAT_803d73c0 = 0;
  gnt4_OSInitThreadQueue_bl((undefined4 *)&DAT_803d73b8);
  DAT_803d73c8 = 0;
  DAT_803d73c4 = 0;
  DAT_800000d8 = &DAT_803d70d0;
  gnt4_OSClearContext_bl(-0x7fc28f30);
  gnt4_OSSetCurrentContext_bl(0x803d70d0);
  DAT_803d73d4 = 0x8044d528;
  DAT_803d73d8 = &DAT_8043d528;
  _DAT_8043d528 = 0xdeadbabe;
  (*DAT_80435c88)(DAT_800000e4,&DAT_803d70d0);
  DAT_800000e4 = &DAT_803d70d0;
  gnt4_OSClearStack_bl(0);
  DAT_80436488 = 0;
  iVar2 = 0;
  DAT_8043648c = 0;
  puVar1 = (undefined4 *)&DAT_803d6cb8;
  do {
    gnt4_OSInitThreadQueue_bl(puVar1);
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 2;
  } while (iVar2 < 0x20);
  gnt4_OSInitThreadQueue_bl(&DAT_800000dc);
  if (DAT_800000e0 == (undefined *)0x0) {
    DAT_800000dc = &DAT_803d70d0;
  }
  else {
    *(undefined **)((int)DAT_800000e0 + 0x2fc) = &DAT_803d70d0;
  }
  DAT_803d73d0 = (int)DAT_800000e0;
  DAT_803d73cc = 0;
  DAT_800000e0 = &DAT_803d70d0;
  gnt4_OSClearContext_bl(-0x7fc28c18);
  DAT_80436490 = 0;
  return;
}



// ==== 80205f04  gnt4-OSInitThreadQueue-bl ====

void gnt4_OSInitThreadQueue_bl(undefined4 *param_1)

{
  param_1[1] = 0;
  *param_1 = 0;
  return;
}



// ==== 80205f14  gnt4-OSGetCurrentThread-bl ====

undefined4 gnt4_OSGetCurrentThread_bl(void)

{
  return DAT_800000e4;
}



// ==== 80205f20  gnt4-OSDisableScheduler-bl ====

int gnt4_OSDisableScheduler_bl(void)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_80436490;
  DAT_80436490 = DAT_80436490 + 1;
  gnt4_OSRestoreInterrupts_bl();
  return iVar1;
}



// ==== 80205f60  gnt4-OSEnableScheduler-bl ====

int gnt4_OSEnableScheduler_bl(void)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_80436490;
  DAT_80436490 = DAT_80436490 + -1;
  gnt4_OSRestoreInterrupts_bl();
  return iVar1;
}



// ==== 80205fa0  gnt4-UnsetRun-bl ====

void gnt4_UnsetRun_bl(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x2e0);
  piVar2 = *(int **)(param_1 + 0x2dc);
  iVar3 = *(int *)(param_1 + 0x2e4);
  if (iVar1 == 0) {
    piVar2[1] = iVar3;
  }
  else {
    *(int *)(iVar1 + 0x2e4) = iVar3;
  }
  if (iVar3 == 0) {
    *piVar2 = iVar1;
  }
  else {
    *(int *)(iVar3 + 0x2e0) = iVar1;
  }
  if (*piVar2 == 0) {
    DAT_80436488 = DAT_80436488 & ~(1 << 0x1f - *(int *)(param_1 + 0x2d0));
  }
  *(undefined4 *)(param_1 + 0x2dc) = 0;
  return;
}



// ==== 80206008  gnt4-__OSGetEffectivePriority-bl ====

int gnt4___OSGetEffectivePriority_bl(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = *(int *)(param_1 + 0x2d4);
  for (piVar3 = *(int **)(param_1 + 0x2f4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[4]) {
    if ((*piVar3 != 0) && (iVar1 = *(int *)(*piVar3 + 0x2d0), iVar1 < iVar2)) {
      iVar2 = iVar1;
    }
  }
  return iVar2;
}



// ==== 80206044  gnt4-SetEffectivePriority-bl ====

undefined4 gnt4_SetEffectivePriority_bl(int param_1,undefined4 param_2)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  uVar1 = *(ushort *)(param_1 + 0x2c8);
  if (uVar1 != 3) {
    if (uVar1 < 3) {
      if (uVar1 == 1) {
        gnt4_UnsetRun_bl(param_1);
        *(undefined4 *)(param_1 + 0x2d0) = param_2;
        *(undefined **)(param_1 + 0x2dc) = &DAT_803d6cb8 + *(int *)(param_1 + 0x2d0) * 8;
        iVar2 = (*(int **)(param_1 + 0x2dc))[1];
        if (iVar2 == 0) {
          **(int **)(param_1 + 0x2dc) = param_1;
        }
        else {
          *(int *)(iVar2 + 0x2e0) = param_1;
        }
        *(int *)(param_1 + 0x2e4) = iVar2;
        *(undefined4 *)(param_1 + 0x2e0) = 0;
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
        DAT_80436488 = DAT_80436488 | 1 << 0x1f - *(int *)(param_1 + 0x2d0);
        DAT_8043648c = 1;
      }
      else if (uVar1 != 0) {
        DAT_8043648c = 1;
        *(undefined4 *)(param_1 + 0x2d0) = param_2;
      }
    }
    else if (uVar1 < 5) {
      iVar2 = *(int *)(param_1 + 0x2e0);
      iVar4 = *(int *)(param_1 + 0x2e4);
      if (iVar2 == 0) {
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar4;
      }
      else {
        *(int *)(iVar2 + 0x2e4) = iVar4;
      }
      if (iVar4 == 0) {
        **(int **)(param_1 + 0x2dc) = iVar2;
      }
      else {
        *(int *)(iVar4 + 0x2e0) = iVar2;
      }
      *(undefined4 *)(param_1 + 0x2d0) = param_2;
      piVar3 = *(int **)(param_1 + 0x2dc);
      for (iVar2 = *piVar3; (iVar2 != 0 && (*(int *)(iVar2 + 0x2d0) <= *(int *)(param_1 + 0x2d0)));
          iVar2 = *(int *)(iVar2 + 0x2e0)) {
      }
      if (iVar2 == 0) {
        iVar2 = piVar3[1];
        if (iVar2 == 0) {
          *piVar3 = param_1;
        }
        else {
          *(int *)(iVar2 + 0x2e0) = param_1;
        }
        *(int *)(param_1 + 0x2e4) = iVar2;
        *(undefined4 *)(param_1 + 0x2e0) = 0;
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
      }
      else {
        *(int *)(param_1 + 0x2e0) = iVar2;
        iVar4 = *(int *)(iVar2 + 0x2e4);
        *(int *)(iVar2 + 0x2e4) = param_1;
        *(int *)(param_1 + 0x2e4) = iVar4;
        if (iVar4 == 0) {
          **(int **)(param_1 + 0x2dc) = param_1;
        }
        else {
          *(int *)(iVar4 + 0x2e0) = param_1;
        }
      }
      if (*(int *)(param_1 + 0x2f0) != 0) {
        return *(undefined4 *)(*(int *)(param_1 + 0x2f0) + 8);
      }
    }
  }
  return 0;
}



// ==== 80206204  gnt4-SelectThread-bl ====

uint gnt4_SelectThread_bl(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint *puVar4;
  
  if (DAT_80436490 < 1) {
    uVar2 = gnt4_OSGetCurrentContext_bl();
    uVar1 = DAT_800000e4;
    if (uVar2 == DAT_800000e4) {
      if (DAT_800000e4 != 0) {
        if (*(short *)(DAT_800000e4 + 0x2c8) == 2) {
          if ((param_1 == 0) &&
             (iVar3 = countLeadingZeros(DAT_80436488), *(int *)(DAT_800000e4 + 0x2d0) <= iVar3)) {
            return 0;
          }
          *(undefined2 *)(DAT_800000e4 + 0x2c8) = 1;
          *(undefined **)(uVar1 + 0x2dc) = &DAT_803d6cb8 + *(int *)(uVar1 + 0x2d0) * 8;
          uVar2 = (*(uint **)(uVar1 + 0x2dc))[1];
          if (uVar2 == 0) {
            **(uint **)(uVar1 + 0x2dc) = uVar1;
          }
          else {
            *(uint *)(uVar2 + 0x2e0) = uVar1;
          }
          *(uint *)(uVar1 + 0x2e4) = uVar2;
          *(undefined4 *)(uVar1 + 0x2e0) = 0;
          *(uint *)(*(int *)(uVar1 + 0x2dc) + 4) = uVar1;
          DAT_80436488 = DAT_80436488 | 1 << 0x1f - *(int *)(uVar1 + 0x2d0);
          DAT_8043648c = 1;
        }
        if (((*(ushort *)(uVar1 + 0x1a2) & 2) == 0) &&
           (iVar3 = gnt4_OSSaveContext_bl(uVar1), iVar3 != 0)) {
          return 0;
        }
      }
      if (DAT_80436488 == 0) {
        (*DAT_80435c88)(DAT_800000e4,0);
        DAT_800000e4 = 0;
        gnt4_OSSetCurrentContext_bl(0x803d73e8);
        do {
          gnt4_OSEnableInterrupts_bl();
          do {
          } while (DAT_80436488 == 0);
          gnt4_OSDisableInterrupts_bl();
        } while (DAT_80436488 == 0);
        gnt4_OSClearContext_bl(-0x7fc28c18);
      }
      DAT_8043648c = 0;
      iVar3 = countLeadingZeros(DAT_80436488);
      puVar4 = (uint *)(&DAT_803d6cb8 + iVar3 * 8);
      uVar1 = *puVar4;
      uVar2 = *(uint *)(uVar1 + 0x2e0);
      if (uVar2 == 0) {
        *(undefined4 *)(&DAT_803d6cbc + iVar3 * 8) = 0;
      }
      else {
        *(undefined4 *)(uVar2 + 0x2e4) = 0;
      }
      *puVar4 = uVar2;
      if (*puVar4 == 0) {
        DAT_80436488 = DAT_80436488 & ~(1 << 0x1f - iVar3);
      }
      *(undefined4 *)(uVar1 + 0x2dc) = 0;
      *(undefined2 *)(uVar1 + 0x2c8) = 2;
      (*DAT_80435c88)(DAT_800000e4,uVar1);
      DAT_800000e4 = uVar1;
      gnt4_OSSetCurrentContext_bl(uVar1);
      gnt4_OSLoadContext_bl(uVar1);
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



// ==== 8020642c  gnt4-__OSReschedule-bl ====

void gnt4___OSReschedule_bl(void)

{
  if (DAT_8043648c != 0) {
    gnt4_SelectThread_bl(0);
  }
  return;
}



// ==== 8020645c  gnt4-OSCreateThread-bl ====

undefined4
gnt4_OSCreateThread_bl
          (int param_1,undefined4 param_2,undefined4 param_3,uint param_4,int param_5,int param_6,
          ushort param_7)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  if ((param_6 < 0) || (0x1f < param_6)) {
    uVar2 = 0;
  }
  else {
    *(undefined2 *)(param_1 + 0x2c8) = 1;
    uVar1 = param_4 & 0xfffffff8;
    *(ushort *)(param_1 + 0x2ca) = param_7 & 1;
    *(int *)(param_1 + 0x2d4) = param_6;
    *(int *)(param_1 + 0x2d0) = param_6;
    *(undefined4 *)(param_1 + 0x2cc) = 1;
    *(undefined4 *)(param_1 + 0x2d8) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x2f0) = 0;
    *(undefined4 *)(param_1 + 0x2ec) = 0;
    *(undefined4 *)(param_1 + 0x2e8) = 0;
    *(undefined4 *)(param_1 + 0x2f8) = 0;
    *(undefined4 *)(param_1 + 0x2f4) = 0;
    *(undefined4 *)(uVar1 - 8) = 0;
    *(undefined4 *)(uVar1 - 4) = 0;
    gnt4_OSInitContext_bl(param_1,param_2,uVar1 - 8);
    *(code **)(param_1 + 0x84) = gnt4_OSExitThread_bl;
    *(undefined4 *)(param_1 + 0xc) = param_3;
    *(uint *)(param_1 + 0x304) = param_4;
    *(uint *)(param_1 + 0x308) = param_4 - param_5;
    **(undefined4 **)(param_1 + 0x308) = 0xdeadbabe;
    *(undefined4 *)(param_1 + 0x30c) = 0;
    *(undefined4 *)(param_1 + 0x310) = 0;
    *(undefined4 *)(param_1 + 0x314) = 0;
    gnt4_OSDisableInterrupts_bl();
    if (DAT_803d6950 != 0) {
      iVar4 = 4;
      *(uint *)(param_1 + 0x19c) = *(uint *)(param_1 + 0x19c) | 0x900;
      *(ushort *)(param_1 + 0x1a2) = *(ushort *)(param_1 + 0x1a2) | 1;
      *(uint *)(param_1 + 0x194) = DAT_80435c70 & 0xf8 | 4;
      iVar3 = param_1;
      do {
        *(undefined4 *)(iVar3 + 0x94) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x90) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1cc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1c8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x9c) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x98) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1dc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1d8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xac) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xa8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1ec) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1e8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xbc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xb8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 500) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1f0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xc4) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xc0) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1fc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x1f8) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0xcc) = 0xffffffff;
        *(undefined4 *)(iVar3 + 200) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x204) = 0xffffffff;
        *(undefined4 *)(iVar3 + 0x200) = 0xffffffff;
        iVar3 = iVar3 + 0x40;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar3 = param_1;
    if (DAT_800000e0 != 0) {
      *(int *)(DAT_800000e0 + 0x2fc) = param_1;
      iVar3 = DAT_800000dc;
    }
    DAT_800000dc = iVar3;
    *(int *)(param_1 + 0x300) = DAT_800000e0;
    *(undefined4 *)(param_1 + 0x2fc) = 0;
    DAT_800000e0 = param_1;
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80206644  gnt4-OSExitThread-bl ====

void gnt4_OSExitThread_bl(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_800000e4;
  gnt4_OSClearContext_bl(DAT_800000e4);
  if ((*(ushort *)(iVar1 + 0x2ca) & 1) == 0) {
    *(undefined2 *)(iVar1 + 0x2c8) = 8;
    *(undefined4 *)(iVar1 + 0x2d8) = param_1;
  }
  else {
    iVar3 = *(int *)(iVar1 + 0x2fc);
    iVar4 = *(int *)(iVar1 + 0x300);
    iVar2 = iVar4;
    if (iVar3 != 0) {
      *(int *)(iVar3 + 0x300) = iVar4;
      iVar2 = DAT_800000e0;
    }
    DAT_800000e0 = iVar2;
    if (iVar4 != 0) {
      *(int *)(iVar4 + 0x2fc) = iVar3;
      iVar3 = DAT_800000dc;
    }
    DAT_800000dc = iVar3;
    *(undefined2 *)(iVar1 + 0x2c8) = 0;
  }
  gnt4___OSUnlockAllMutex_bl(iVar1);
  gnt4_OSWakeupThread_bl((int *)(iVar1 + 0x2e8));
  DAT_8043648c = 1;
  gnt4_SelectThread_bl(0);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80206728  gnt4-OSCancelThread-bl ====

void gnt4_OSCancelThread_bl(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = *(ushort *)(param_1 + 0x2c8);
  if (uVar1 == 3) {
LAB_80206830:
    gnt4_OSRestoreInterrupts_bl();
  }
  else {
    if (uVar1 < 3) {
      if (uVar1 == 1) {
        if (*(int *)(param_1 + 0x2cc) < 1) {
          gnt4_UnsetRun_bl(param_1);
        }
      }
      else {
        if (uVar1 == 0) goto LAB_80206830;
        DAT_8043648c = 1;
      }
    }
    else {
      if (4 < uVar1) goto LAB_80206830;
      iVar2 = *(int *)(param_1 + 0x2e0);
      iVar3 = *(int *)(param_1 + 0x2e4);
      if (iVar2 == 0) {
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar3;
      }
      else {
        *(int *)(iVar2 + 0x2e4) = iVar3;
      }
      if (iVar3 == 0) {
        **(int **)(param_1 + 0x2dc) = iVar2;
      }
      else {
        *(int *)(iVar3 + 0x2e0) = iVar2;
      }
      *(undefined4 *)(param_1 + 0x2dc) = 0;
      if ((*(int *)(param_1 + 0x2cc) < 1) && (*(int *)(param_1 + 0x2f0) != 0)) {
        iVar2 = *(int *)(*(int *)(param_1 + 0x2f0) + 8);
        do {
          if ((0 < *(int *)(iVar2 + 0x2cc)) ||
             (iVar3 = gnt4___OSGetEffectivePriority_bl(iVar2), *(int *)(iVar2 + 0x2d0) == iVar3))
          break;
          iVar2 = gnt4_SetEffectivePriority_bl(iVar2,iVar3);
        } while (iVar2 != 0);
      }
    }
    gnt4_OSClearContext_bl(param_1);
    if ((*(ushort *)(param_1 + 0x2ca) & 1) == 0) {
      *(undefined2 *)(param_1 + 0x2c8) = 8;
    }
    else {
      iVar2 = *(int *)(param_1 + 0x2fc);
      iVar4 = *(int *)(param_1 + 0x300);
      iVar3 = iVar4;
      if (iVar2 != 0) {
        *(int *)(iVar2 + 0x300) = iVar4;
        iVar3 = DAT_800000e0;
      }
      DAT_800000e0 = iVar3;
      if (iVar4 != 0) {
        *(int *)(iVar4 + 0x2fc) = iVar2;
        iVar2 = DAT_800000dc;
      }
      DAT_800000dc = iVar2;
      *(undefined2 *)(param_1 + 0x2c8) = 0;
    }
    gnt4___OSUnlockAllMutex_bl(param_1);
    gnt4_OSWakeupThread_bl((int *)(param_1 + 0x2e8));
    if (DAT_8043648c != 0) {
      gnt4_SelectThread_bl(0);
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  return;
}



// ==== 802068e4  gnt4-OSResumeThread-bl ====

int gnt4_OSResumeThread_bl(int param_1)

{
  ushort uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  gnt4_OSDisableInterrupts_bl();
  iVar4 = *(int *)(param_1 + 0x2cc);
  *(int *)(param_1 + 0x2cc) = iVar4 + -1;
  if (*(int *)(param_1 + 0x2cc) < 0) {
    *(undefined4 *)(param_1 + 0x2cc) = 0;
  }
  else if (*(int *)(param_1 + 0x2cc) == 0) {
    uVar1 = *(ushort *)(param_1 + 0x2c8);
    if (uVar1 == 4) {
      iVar2 = *(int *)(param_1 + 0x2e0);
      iVar5 = *(int *)(param_1 + 0x2e4);
      if (iVar2 == 0) {
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar5;
      }
      else {
        *(int *)(iVar2 + 0x2e4) = iVar5;
      }
      if (iVar5 == 0) {
        **(int **)(param_1 + 0x2dc) = iVar2;
      }
      else {
        *(int *)(iVar5 + 0x2e0) = iVar2;
      }
      iVar2 = *(int *)(param_1 + 0x2d4);
      for (piVar3 = *(int **)(param_1 + 0x2f4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[4]) {
        if ((*piVar3 != 0) && (iVar5 = *(int *)(*piVar3 + 0x2d0), iVar5 < iVar2)) {
          iVar2 = iVar5;
        }
      }
      *(int *)(param_1 + 0x2d0) = iVar2;
      piVar3 = *(int **)(param_1 + 0x2dc);
      for (iVar2 = *piVar3; (iVar2 != 0 && (*(int *)(iVar2 + 0x2d0) <= *(int *)(param_1 + 0x2d0)));
          iVar2 = *(int *)(iVar2 + 0x2e0)) {
      }
      if (iVar2 == 0) {
        iVar2 = piVar3[1];
        if (iVar2 == 0) {
          *piVar3 = param_1;
        }
        else {
          *(int *)(iVar2 + 0x2e0) = param_1;
        }
        *(int *)(param_1 + 0x2e4) = iVar2;
        *(undefined4 *)(param_1 + 0x2e0) = 0;
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
      }
      else {
        *(int *)(param_1 + 0x2e0) = iVar2;
        iVar5 = *(int *)(iVar2 + 0x2e4);
        *(int *)(iVar2 + 0x2e4) = param_1;
        *(int *)(param_1 + 0x2e4) = iVar5;
        if (iVar5 == 0) {
          **(int **)(param_1 + 0x2dc) = param_1;
        }
        else {
          *(int *)(iVar5 + 0x2e0) = param_1;
        }
      }
      if (*(int *)(param_1 + 0x2f0) != 0) {
        iVar2 = *(int *)(*(int *)(param_1 + 0x2f0) + 8);
        do {
          if ((0 < *(int *)(iVar2 + 0x2cc)) ||
             (iVar5 = gnt4___OSGetEffectivePriority_bl(iVar2), *(int *)(iVar2 + 0x2d0) == iVar5))
          break;
          iVar2 = gnt4_SetEffectivePriority_bl(iVar2,iVar5);
        } while (iVar2 != 0);
      }
    }
    else if ((uVar1 < 4) && (uVar1 == 1)) {
      iVar2 = *(int *)(param_1 + 0x2d4);
      for (piVar3 = *(int **)(param_1 + 0x2f4); piVar3 != (int *)0x0; piVar3 = (int *)piVar3[4]) {
        if ((*piVar3 != 0) && (iVar5 = *(int *)(*piVar3 + 0x2d0), iVar5 < iVar2)) {
          iVar2 = iVar5;
        }
      }
      *(int *)(param_1 + 0x2d0) = iVar2;
      *(undefined **)(param_1 + 0x2dc) = &DAT_803d6cb8 + *(int *)(param_1 + 0x2d0) * 8;
      iVar2 = (*(int **)(param_1 + 0x2dc))[1];
      if (iVar2 == 0) {
        **(int **)(param_1 + 0x2dc) = param_1;
      }
      else {
        *(int *)(iVar2 + 0x2e0) = param_1;
      }
      *(int *)(param_1 + 0x2e4) = iVar2;
      *(undefined4 *)(param_1 + 0x2e0) = 0;
      *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
      DAT_80436488 = DAT_80436488 | 1 << 0x1f - *(int *)(param_1 + 0x2d0);
      DAT_8043648c = 1;
    }
    if (DAT_8043648c != 0) {
      gnt4_SelectThread_bl(0);
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar4;
}



// ==== 80206b6c  gnt4-OSSuspendThread-bl ====

int gnt4_OSSuspendThread_bl(int param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  gnt4_OSDisableInterrupts_bl();
  iVar2 = *(int *)(param_1 + 0x2cc);
  *(int *)(param_1 + 0x2cc) = iVar2 + 1;
  if (iVar2 == 0) {
    uVar1 = *(ushort *)(param_1 + 0x2c8);
    if (uVar1 != 3) {
      if (uVar1 < 3) {
        if (uVar1 == 1) {
          gnt4_UnsetRun_bl(param_1);
        }
        else if (uVar1 != 0) {
          DAT_8043648c = 1;
          *(undefined2 *)(param_1 + 0x2c8) = 1;
        }
      }
      else if (uVar1 < 5) {
        iVar3 = *(int *)(param_1 + 0x2e0);
        iVar4 = *(int *)(param_1 + 0x2e4);
        if (iVar3 == 0) {
          *(int *)(*(int *)(param_1 + 0x2dc) + 4) = iVar4;
        }
        else {
          *(int *)(iVar3 + 0x2e4) = iVar4;
        }
        if (iVar4 == 0) {
          **(int **)(param_1 + 0x2dc) = iVar3;
        }
        else {
          *(int *)(iVar4 + 0x2e0) = iVar3;
        }
        *(undefined4 *)(param_1 + 0x2d0) = 0x20;
        iVar3 = (*(int **)(param_1 + 0x2dc))[1];
        if (iVar3 == 0) {
          **(int **)(param_1 + 0x2dc) = param_1;
        }
        else {
          *(int *)(iVar3 + 0x2e0) = param_1;
        }
        *(int *)(param_1 + 0x2e4) = iVar3;
        *(undefined4 *)(param_1 + 0x2e0) = 0;
        *(int *)(*(int *)(param_1 + 0x2dc) + 4) = param_1;
        if (*(int *)(param_1 + 0x2f0) != 0) {
          iVar3 = *(int *)(*(int *)(param_1 + 0x2f0) + 8);
          do {
            if ((0 < *(int *)(iVar3 + 0x2cc)) ||
               (iVar4 = gnt4___OSGetEffectivePriority_bl(iVar3), *(int *)(iVar3 + 0x2d0) == iVar4))
            break;
            iVar3 = gnt4_SetEffectivePriority_bl(iVar3,iVar4);
          } while (iVar3 != 0);
        }
      }
    }
    if (DAT_8043648c != 0) {
      gnt4_SelectThread_bl(0);
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar2;
}



// ==== 80206cdc  gnt4-OSSleepThread-bl ====

void gnt4_OSSleepThread_bl(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_800000e4;
  *(undefined2 *)(DAT_800000e4 + 0x2c8) = 4;
  *(int **)(iVar1 + 0x2dc) = param_1;
  for (iVar3 = *param_1; (iVar3 != 0 && (*(int *)(iVar3 + 0x2d0) <= *(int *)(iVar1 + 0x2d0)));
      iVar3 = *(int *)(iVar3 + 0x2e0)) {
  }
  if (iVar3 == 0) {
    iVar3 = param_1[1];
    if (iVar3 == 0) {
      *param_1 = iVar1;
    }
    else {
      *(int *)(iVar3 + 0x2e0) = iVar1;
    }
    *(int *)(iVar1 + 0x2e4) = iVar3;
    *(undefined4 *)(iVar1 + 0x2e0) = 0;
    param_1[1] = iVar1;
  }
  else {
    *(int *)(iVar1 + 0x2e0) = iVar3;
    iVar2 = *(int *)(iVar3 + 0x2e4);
    *(int *)(iVar3 + 0x2e4) = iVar1;
    *(int *)(iVar1 + 0x2e4) = iVar2;
    if (iVar2 == 0) {
      *param_1 = iVar1;
    }
    else {
      *(int *)(iVar2 + 0x2e0) = iVar1;
    }
  }
  DAT_8043648c = 1;
  gnt4_SelectThread_bl(0);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80206dc8  gnt4-OSWakeupThread-bl ====

void gnt4_OSWakeupThread_bl(int *param_1)

{
  int iVar1;
  int iVar2;
  
  gnt4_OSDisableInterrupts_bl();
  while (iVar2 = *param_1, iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x2e0);
    if (iVar1 == 0) {
      param_1[1] = 0;
    }
    else {
      *(undefined4 *)(iVar1 + 0x2e4) = 0;
    }
    *param_1 = iVar1;
    *(undefined2 *)(iVar2 + 0x2c8) = 1;
    if (*(int *)(iVar2 + 0x2cc) < 1) {
      *(undefined **)(iVar2 + 0x2dc) = &DAT_803d6cb8 + *(int *)(iVar2 + 0x2d0) * 8;
      iVar1 = (*(int **)(iVar2 + 0x2dc))[1];
      if (iVar1 == 0) {
        **(int **)(iVar2 + 0x2dc) = iVar2;
      }
      else {
        *(int *)(iVar1 + 0x2e0) = iVar2;
      }
      *(int *)(iVar2 + 0x2e4) = iVar1;
      *(undefined4 *)(iVar2 + 0x2e0) = 0;
      *(int *)(*(int *)(iVar2 + 0x2dc) + 4) = iVar2;
      DAT_80436488 = DAT_80436488 | 1 << 0x1f - *(int *)(iVar2 + 0x2d0);
      DAT_8043648c = 1;
    }
  }
  if (DAT_8043648c != 0) {
    gnt4_SelectThread_bl(0);
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80206ecc  zz_0206ecc_ ====

undefined4 zz_0206ecc_(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((param_2 < 0) || (0x1f < param_2)) {
    uVar1 = 0;
  }
  else {
    gnt4_OSDisableInterrupts_bl();
    if (*(int *)(param_1 + 0x2d4) != param_2) {
      *(int *)(param_1 + 0x2d4) = param_2;
      while (*(int *)(param_1 + 0x2cc) < 1) {
        iVar2 = gnt4___OSGetEffectivePriority_bl(param_1);
        if ((*(int *)(param_1 + 0x2d0) == iVar2) ||
           (param_1 = gnt4_SetEffectivePriority_bl(param_1,iVar2), param_1 == 0)) break;
      }
      if (DAT_8043648c != 0) {
        gnt4_SelectThread_bl(0);
      }
    }
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80206f8c  zz_0206f8c_ ====

undefined4 zz_0206f8c_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2d4);
}



// ==== 80206f94  gnt4-OSClearStack-bl ====

void gnt4_OSClearStack_bl(uint param_1)

{
  uint *puVar1;
  undefined1 *puVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = param_1 & 0xff | (param_1 & 0xff) << 8 | param_1 << 0x18 | (param_1 & 0xff) << 0x10;
  puVar1 = (uint *)gnt4_OSGetStackPointer_bl();
  puVar4 = (uint *)(*(int *)(DAT_800000e4 + 0x308) + 4);
  puVar2 = (undefined1 *)((int)puVar1 + (3 - (int)puVar4));
  uVar3 = (uint)puVar2 >> 2;
  if (puVar4 < puVar1) {
    uVar6 = (uint)puVar2 >> 5;
    if (uVar6 != 0) {
      do {
        *puVar4 = uVar5;
        puVar4[1] = uVar5;
        puVar4[2] = uVar5;
        puVar4[3] = uVar5;
        puVar4[4] = uVar5;
        puVar4[5] = uVar5;
        puVar4[6] = uVar5;
        puVar4[7] = uVar5;
        puVar4 = puVar4 + 8;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) {
        return;
      }
    }
    do {
      *puVar4 = uVar5;
      puVar4 = puVar4 + 1;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
  return;
}



// ==== 80207040  gnt4-OSGetTime-bl ====

void gnt4_OSGetTime_bl(void)

{
  return;
}



// ==== 80207058  gnt4-OSGetTick-bl ====

void gnt4_OSGetTick_bl(void)

{
  return;
}



// ==== 80207060  gnt4-__OSGetSystemTime-bl ====

longlong gnt4___OSGetSystemTime_bl(void)

{
  longlong lVar1;
  longlong lVar2;
  
  gnt4_OSDisableInterrupts_bl();
  lVar2 = gnt4_OSGetTime_bl();
  lVar1 = CONCAT44(DAT_800030d8,DAT_800030dc);
  gnt4_OSRestoreInterrupts_bl();
  return lVar2 + lVar1;
}



// ==== 802070c4  gnt4-GetDates-bl ====

void gnt4_GetDates_bl(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = param_1 + 6;
  iVar5 = iVar7 / 7 + (iVar7 >> 0x1f);
  iVar3 = param_1 / 0x16d + (param_1 >> 0x1f);
  uVar6 = iVar3 - (iVar3 >> 0x1f);
  iVar3 = uVar6 * 0x16d;
  *(int *)(param_2 + 0x18) = iVar7 + (iVar5 - (iVar5 >> 0x1f)) * -7;
  while( true ) {
    if ((int)uVar6 < 1) {
      iVar5 = 0;
    }
    else {
      iVar5 = uVar6 - 1;
      iVar7 = iVar5 / 400 + (iVar5 >> 0x1f);
      iVar5 = iVar5 / 100 + (iVar5 >> 0x1f);
      uVar4 = uVar6 + 3;
      iVar5 = (iVar7 - (iVar7 >> 0x1f)) +
              ((((int)uVar4 >> 2) + (uint)((int)uVar4 < 0 && (uVar4 & 3) != 0)) -
              (iVar5 - (iVar5 >> 0x1f)));
    }
    if (iVar3 + iVar5 <= param_1) break;
    iVar3 = iVar3 + -0x16d;
    uVar6 = uVar6 - 1;
  }
  *(uint *)(param_2 + 0x14) = uVar6;
  iVar3 = param_1 - (iVar3 + iVar5);
  *(int *)(param_2 + 0x1c) = iVar3;
  bVar2 = true;
  bVar1 = false;
  if ((uVar6 == (((int)uVar6 >> 2) + (uint)((int)uVar6 < 0 && (uVar6 & 3) != 0)) * 4) &&
     (iVar5 = (int)uVar6 / 100 + ((int)uVar6 >> 0x1f), uVar6 + (iVar5 - (iVar5 >> 0x1f)) * -100 != 0
     )) {
    bVar1 = true;
  }
  if ((!bVar1) &&
     (iVar5 = (int)uVar6 / 400 + ((int)uVar6 >> 0x1f), uVar6 + (iVar5 - (iVar5 >> 0x1f)) * -400 != 0
     )) {
    bVar2 = false;
  }
  if (bVar2) {
    iVar5 = -0x7fc5b488;
  }
  else {
    iVar5 = -0x7fc5b4b8;
  }
  iVar8 = 0xc;
  iVar7 = 0x30;
  do {
    iVar7 = iVar7 + -4;
    iVar8 = iVar8 + -1;
  } while (iVar3 < *(int *)(iVar5 + iVar7));
  *(int *)(param_2 + 0x10) = iVar8;
  *(int *)(param_2 + 0xc) = (iVar3 - *(int *)(iVar5 + iVar7)) + 1;
  return;
}



// ==== 80207260  gnt4-OSTicksToCalendarTime-bl ====

void gnt4_OSTicksToCalendarTime_bl(uint param_1,uint param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  lVar7 = gnt4___mod2i(param_1,param_2,0,DAT_800000f8 >> 2);
  if (((uint)((ulonglong)lVar7 >> 0x20) ^ 0x80000000) < 0x80000000) {
    lVar7 = lVar7 + (ulonglong)(DAT_800000f8 >> 2);
  }
  uVar6 = (uint)((ulonglong)lVar7 >> 0x20);
  uVar3 = (uint)lVar7;
  uVar8 = gnt4___div2i((uint)((ulonglong)(lVar7 * 8) >> 0x20),(uint)(lVar7 * 8),0,
                       DAT_800000f8 / 500000);
  uVar8 = gnt4___mod2i((uint)((ulonglong)uVar8 >> 0x20),(uint)uVar8,0,1000);
  param_3[9] = (int)uVar8;
  uVar8 = gnt4___div2i(uVar6,uVar3,0,DAT_800000f8 / 4000);
  uVar8 = gnt4___mod2i((uint)((ulonglong)uVar8 >> 0x20),(uint)uVar8,0,1000);
  param_3[8] = (int)uVar8;
  uVar6 = param_1 - ((param_2 < uVar3) + uVar6);
  uVar8 = gnt4___div2i(uVar6,param_2 - uVar3,0,DAT_800000f8 >> 2);
  uVar8 = gnt4___div2i((uint)((ulonglong)uVar8 >> 0x20),(uint)uVar8,0,0x15180);
  iVar4 = (int)uVar8 + 0xb2575;
  uVar9 = gnt4___div2i(uVar6,param_2 - uVar3,0,DAT_800000f8 >> 2);
  uVar9 = gnt4___mod2i((uint)((ulonglong)uVar9 >> 0x20),(uint)uVar9,0,0x15180);
  iVar5 = (int)uVar9;
  if (iVar5 < 0) {
    iVar4 = (int)uVar8 + 0xb2574;
    iVar5 = iVar5 + 0x15180;
  }
  gnt4_GetDates_bl(iVar4,(int)param_3);
  iVar4 = iVar5 / 0x3c + (iVar5 >> 0x1f);
  iVar2 = iVar4 - (iVar4 >> 0x1f);
  iVar1 = iVar2 / 0x3c + (iVar2 >> 0x1f);
  param_3[2] = iVar1 - (iVar1 >> 0x1f);
  param_3[1] = iVar2 + (iVar1 - (iVar1 >> 0x1f)) * -0x3c;
  *param_3 = iVar5 + (iVar4 - (iVar4 >> 0x1f)) * -0x3c;
  return;
}



// ==== 80207464  gnt4-__init_user-bl ====

void gnt4___init_user_bl(void)

{
  gnt4___init_cpp_bl();
  return;
}



// ==== 80207484  gnt4-__init_cpp-bl ====

void gnt4___init_cpp_bl(void)

{
  undefined4 *puVar1;
  
  for (puVar1 = &DAT_802b0160; (code *)*puVar1 != (code *)0x0; puVar1 = puVar1 + 1) {
    (*(code *)*puVar1)();
  }
  return;
}



// ==== 802074d8  gnt4-_ExitProcess-bl ====

void gnt4__ExitProcess_bl(void)

{
  gnt4_PPCHalt();
  return;
}



// ==== 802074f8  gnt4-SetExiInterruptMask ====

void gnt4_SetExiInterruptMask(int param_1,int *param_2)

{
  int iVar1;
  
  if (param_1 == 1) {
    if ((*param_2 == 0) || ((param_2[3] & 0x10U) != 0)) {
      gnt4___OSMaskInterrupts_bl(0x80000);
    }
    else {
      gnt4___OSUnmaskInterrupts_bl(0x80000);
    }
  }
  else if (param_1 < 1) {
    if (-1 < param_1) {
      if (((*param_2 == 0) && (DAT_803d7730 == 0)) || ((param_2[3] & 0x10U) != 0)) {
        gnt4___OSMaskInterrupts_bl(0x410000);
      }
      else {
        gnt4___OSUnmaskInterrupts_bl(0x410000);
      }
    }
  }
  else if (param_1 < 3) {
    iVar1 = gnt4___OSGetInterruptHandler_bl(0x19);
    if ((iVar1 == 0) || ((param_2[3] & 0x10U) != 0)) {
      gnt4___OSMaskInterrupts_bl(0x40);
    }
    else {
      gnt4___OSUnmaskInterrupts_bl(0x40);
    }
  }
  return;
}



// ==== 802075ec  gnt4-EXIImm-bl ====

undefined4 gnt4_EXIImm_bl(int param_1,byte *param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  
  iVar1 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if (((*(uint *)(&DAT_803d76bc + iVar1) & 3) == 0) && ((*(uint *)(&DAT_803d76bc + iVar1) & 4) != 0)
     ) {
    *(undefined4 *)(&DAT_803d76b4 + iVar1) = param_5;
    if (*(int *)(&DAT_803d76b4 + iVar1) != 0) {
      gnt4_EXIClearInterrupts(param_1,0,1,0);
      gnt4___OSUnmaskInterrupts_bl(0x200000 >> param_1 * 3);
    }
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 2;
    if (param_4 != 0) {
      uVar2 = 0;
      iVar6 = 0;
      if (0 < param_3) {
        if ((8 < param_3) && (uVar7 = param_3 - 1U >> 3, pbVar4 = param_2, 0 < param_3 + -8)) {
          do {
            uVar2 = uVar2 | (uint)*pbVar4 << (3 - iVar6) * 8 |
                    (uint)pbVar4[1] << (3 - (iVar6 + 1)) * 8 |
                    (uint)pbVar4[2] << (3 - (iVar6 + 2)) * 8 | (uint)pbVar4[3] << iVar6 * -8 |
                    (uint)pbVar4[4] << (3 - (iVar6 + 4)) * 8 |
                    (uint)pbVar4[5] << (3 - (iVar6 + 5)) * 8 |
                    (uint)pbVar4[6] << (3 - (iVar6 + 6)) * 8 |
                    (uint)pbVar4[7] << (3 - (iVar6 + 7)) * 8;
            pbVar4 = pbVar4 + 8;
            iVar6 = iVar6 + 8;
            uVar7 = uVar7 - 1;
          } while (uVar7 != 0);
        }
        pbVar4 = param_2 + iVar6;
        iVar5 = param_3 - iVar6;
        if (iVar6 < param_3) {
          do {
            uVar2 = uVar2 | (uint)*pbVar4 << (3 - iVar6) * 8;
            pbVar4 = pbVar4 + 1;
            iVar6 = iVar6 + 1;
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
      }
      *(uint *)(&DAT_cc006810 + param_1 * 0x14) = uVar2;
    }
    *(byte **)(&DAT_803d76c4 + iVar1) = param_2;
    iVar6 = param_3;
    if (param_4 == 1) {
      iVar6 = 0;
    }
    *(int *)(&DAT_803d76c0 + iVar1) = iVar6;
    (&DAT_cc00680c)[param_1 * 5] = param_4 << 2 | 1U | (param_3 + -1) * 0x10;
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 80207848  gnt4-EXIImmEx ====

undefined4 gnt4_EXIImmEx(int param_1,byte *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  while( true ) {
    if (param_3 == 0) {
      return 1;
    }
    iVar2 = param_3;
    if (3 < param_3) {
      iVar2 = 4;
    }
    iVar1 = gnt4_EXIImm_bl(param_1,param_2,iVar2,param_4,0);
    if (iVar1 == 0) break;
    iVar1 = gnt4_EXISync(param_1);
    if (iVar1 == 0) {
      return 0;
    }
    param_2 = param_2 + iVar2;
    param_3 = param_3 - iVar2;
  }
  return 0;
}



// ==== 802078e8  gnt4-EXIDma-bl ====

undefined4
gnt4_EXIDma_bl(int param_1,uint param_2,undefined4 param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if (((*(uint *)(&DAT_803d76bc + iVar1) & 3) == 0) && ((*(uint *)(&DAT_803d76bc + iVar1) & 4) != 0)
     ) {
    *(undefined4 *)(&DAT_803d76b4 + iVar1) = param_5;
    if (*(int *)(&DAT_803d76b4 + iVar1) != 0) {
      gnt4_EXIClearInterrupts(param_1,0,1,0);
      gnt4___OSUnmaskInterrupts_bl(0x200000 >> param_1 * 3);
    }
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 1;
    *(uint *)(&DAT_cc006804 + param_1 * 0x14) = param_2 & 0x3ffffe0;
    *(undefined4 *)(&DAT_cc006808 + param_1 * 0x14) = param_3;
    (&DAT_cc00680c)[param_1 * 5] = param_4 << 2 | 3;
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 802079d4  gnt4-EXISync ====

undefined4 gnt4_EXISync(int param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  
  iVar2 = param_1 * 0x40;
  uVar8 = 0;
  do {
    if ((*(uint *)(&DAT_803d76bc + iVar2) & 4) == 0) {
      return 0;
    }
  } while (((&DAT_cc00680c)[param_1 * 5] & 1) != 0);
  gnt4_OSDisableInterrupts_bl();
  if ((*(uint *)(&DAT_803d76bc + iVar2) & 4) != 0) {
    if ((*(uint *)(&DAT_803d76bc + iVar2) & 3) != 0) {
      if ((*(uint *)(&DAT_803d76bc + iVar2) & 2) != 0) {
        iVar4 = *(int *)(&DAT_803d76c0 + iVar2);
        if (iVar4 != 0) {
          puVar6 = *(undefined1 **)(&DAT_803d76c4 + iVar2);
          uVar3 = *(uint *)(&DAT_cc006810 + param_1 * 0x14);
          iVar5 = 0;
          if (0 < iVar4) {
            if ((8 < iVar4) && (uVar9 = iVar4 - 1U >> 3, 0 < iVar4 + -8)) {
              do {
                *puVar6 = (char)(uVar3 >> (3 - iVar5) * 8);
                puVar6[1] = (char)(uVar3 >> (3 - (iVar5 + 1)) * 8);
                puVar6[2] = (char)(uVar3 >> (3 - (iVar5 + 2)) * 8);
                puVar6[3] = (char)(uVar3 >> iVar5 * -8);
                puVar6[4] = (char)(uVar3 >> (3 - (iVar5 + 4)) * 8);
                puVar6[5] = (char)(uVar3 >> (3 - (iVar5 + 5)) * 8);
                puVar6[6] = (char)(uVar3 >> (3 - (iVar5 + 6)) * 8);
                puVar6[7] = (char)(uVar3 >> (3 - (iVar5 + 7)) * 8);
                puVar6 = puVar6 + 8;
                iVar5 = iVar5 + 8;
                uVar9 = uVar9 - 1;
              } while (uVar9 != 0);
            }
            iVar7 = iVar4 - iVar5;
            if (iVar5 < iVar4) {
              do {
                *puVar6 = (char)(uVar3 >> (3 - iVar5) * 8);
                puVar6 = puVar6 + 1;
                iVar5 = iVar5 + 1;
                iVar7 = iVar7 + -1;
              } while (iVar7 != 0);
            }
          }
        }
      }
      *(uint *)(&DAT_803d76bc + iVar2) = *(uint *)(&DAT_803d76bc + iVar2) & 0xfffffffc;
    }
    uVar3 = gnt4___OSGetDIConfig_bl();
    if (((((uVar3 != 0xff) ||
          (uVar3 = gnt4_OSGetConsoleType_bl(), (uVar3 & 0xf0000000) == 0x20000000)) ||
         (*(int *)(&DAT_803d76c0 + iVar2) != 4)) ||
        ((((&DAT_cc006800)[param_1 * 5] & 0x70) != 0 ||
         (((piVar1 = (int *)(&DAT_cc006810 + param_1 * 0x14), *piVar1 != 0x1010000 &&
           (*piVar1 != 0x5070000)) && (*piVar1 != 0x4220001)))))) || (DAT_800030e6 == -0x7e00)) {
      uVar8 = 1;
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar8;
}



// ==== 80207c20  gnt4-EXIClearInterrupts ====

uint gnt4_EXIClearInterrupts(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (&DAT_cc006800)[param_1 * 5];
  uVar2 = uVar1 & 0x7f5;
  if (param_2 != 0) {
    uVar2 = uVar2 | 2;
  }
  if (param_3 != 0) {
    uVar2 = uVar2 | 8;
  }
  if (param_4 != 0) {
    uVar2 = uVar2 | 0x800;
  }
  (&DAT_cc006800)[param_1 * 5] = uVar2;
  return uVar1;
}



// ==== 80207c68  zz_0207c68_ ====

int zz_0207c68_(int param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = (int *)(&DAT_803d76b0 + param_1 * 0x40);
  gnt4_OSDisableInterrupts_bl();
  iVar1 = *piVar2;
  *piVar2 = param_2;
  if (param_1 == 2) {
    gnt4_SetExiInterruptMask(0,(int *)&DAT_803d76b0);
  }
  else {
    gnt4_SetExiInterruptMask(param_1,piVar2);
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar1;
}



// ==== 80207ce4  gnt4-__EXIProbe ====

undefined4 gnt4___EXIProbe(int param_1)

{
  undefined4 uVar1;
  uint *puVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  
  if (param_1 == 2) {
    uVar1 = 1;
  }
  else {
    uVar1 = 1;
    gnt4_OSDisableInterrupts_bl();
    puVar2 = &DAT_cc006800 + param_1 * 5;
    uVar5 = *puVar2;
    if ((*(uint *)(&DAT_803d76bc + param_1 * 0x40) & 8) == 0) {
      if ((uVar5 & 0x800) != 0) {
        *puVar2 = *puVar2 & 0x7f5 | 0x800;
        (&DAT_803d76d0)[param_1 * 0x10] = 0;
        (&DAT_800030c0)[param_1] = 0;
      }
      if ((uVar5 & 0x1000) == 0) {
        (&DAT_803d76d0)[param_1 * 0x10] = 0;
        (&DAT_800030c0)[param_1] = 0;
        uVar1 = 0;
      }
      else {
        uVar5 = DAT_800000f8 / 4000;
        uVar6 = gnt4_OSGetTime_bl();
        uVar6 = gnt4___div2i((uint)((ulonglong)uVar6 >> 0x20),(uint)uVar6,0,uVar5);
        uVar6 = gnt4___div2i((uint)((ulonglong)uVar6 >> 0x20),(uint)uVar6,0,100);
        iVar4 = (int)uVar6 + 1;
        piVar3 = &DAT_800030c0 + param_1;
        if (*piVar3 == 0) {
          *piVar3 = iVar4;
        }
        if (iVar4 - *piVar3 < 3) {
          uVar1 = 0;
        }
      }
    }
    else if (((uVar5 & 0x1000) == 0) || ((uVar5 & 0x800) != 0)) {
      (&DAT_803d76d0)[param_1 * 0x10] = 0;
      (&DAT_800030c0)[param_1] = 0;
      uVar1 = 0;
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar1;
}



// ==== 80207e58  zz_0207e58_ ====

int zz_0207e58_(int param_1)

{
  int iVar1;
  byte abStack_c [4];
  
  iVar1 = gnt4___EXIProbe(param_1);
  if ((iVar1 != 0) && ((&DAT_803d76d0)[param_1 * 0x10] == 0)) {
    iVar1 = zz_0208b24_(param_1,0,abStack_c);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  return iVar1;
}



// ==== 80207ed8  zz_0207ed8_ ====

undefined4 zz_0207ed8_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  byte abStack_c [4];
  
  iVar1 = gnt4___EXIProbe(param_1);
  if ((iVar1 != 0) && ((&DAT_803d76d0)[param_1 * 0x10] == 0)) {
    iVar1 = zz_0208b24_(param_1,0,abStack_c);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = 1;
    }
  }
  if (iVar1 == 0) {
    if ((&DAT_800030c0)[param_1] == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80207f8c  zz_0207f8c_ ====

undefined4 zz_0207f8c_(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte abStack_24 [16];
  
  iVar1 = param_1 * 0x40;
  iVar2 = gnt4___EXIProbe(param_1);
  if ((iVar2 != 0) && ((&DAT_803d76d0)[param_1 * 0x10] == 0)) {
    zz_0208b24_(param_1,0,abStack_24);
  }
  gnt4_OSDisableInterrupts_bl();
  if ((&DAT_803d76d0)[param_1 * 0x10] == 0) {
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 0;
  }
  else {
    gnt4_OSDisableInterrupts_bl();
    if (((*(uint *)(&DAT_803d76bc + iVar1) & 8) == 0) &&
       (iVar2 = gnt4___EXIProbe(param_1), iVar2 != 0)) {
      gnt4_EXIClearInterrupts(param_1,1,0,0);
      *(undefined4 *)(&DAT_803d76b8 + iVar1) = param_2;
      gnt4___OSUnmaskInterrupts_bl(0x100000 >> param_1 * 3);
      *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 8;
      gnt4_OSRestoreInterrupts_bl();
      uVar3 = 1;
    }
    else {
      gnt4_OSRestoreInterrupts_bl();
      uVar3 = 0;
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar3;
}



// ==== 80208098  zz_0208098_ ====

undefined4 zz_0208098_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if ((*(uint *)(&DAT_803d76bc + iVar1) & 8) == 0) {
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 1;
  }
  else if (((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) == 0) ||
          (*(int *)(&DAT_803d76c8 + iVar1) != 0)) {
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xfffffff7;
    gnt4___OSMaskInterrupts_bl(0x500000 >> param_1 * 3);
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80208154  gnt4-EXISelect-bl ====

undefined4 gnt4_EXISelect_bl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if (((*(uint *)(&DAT_803d76bc + iVar1) & 4) == 0) &&
     ((param_1 == 2 ||
      ((((param_2 != 0 || ((*(uint *)(&DAT_803d76bc + iVar1) & 8) != 0)) ||
        (iVar2 = gnt4___EXIProbe(param_1), iVar2 != 0)) &&
       (((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) != 0 &&
        (*(int *)(&DAT_803d76c8 + iVar1) == param_2)))))))) {
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 4;
    (&DAT_cc006800)[param_1 * 5] =
         (&DAT_cc006800)[param_1 * 5] & 0x405 | (1 << param_2) << 7 | param_3 << 4;
    if ((*(uint *)(&DAT_803d76bc + iVar1) & 8) != 0) {
      if (param_1 == 1) {
        gnt4___OSMaskInterrupts_bl(0x20000);
      }
      else if ((param_1 < 1) && (-1 < param_1)) {
        gnt4___OSMaskInterrupts_bl(0x100000);
      }
    }
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 80208280  gnt4-EXIDeselect ====

undefined4 gnt4_EXIDeselect(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if ((*(uint *)(&DAT_803d76bc + iVar2) & 4) == 0) {
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 0;
  }
  else {
    *(uint *)(&DAT_803d76bc + iVar2) = *(uint *)(&DAT_803d76bc + iVar2) & 0xfffffffb;
    uVar3 = (&DAT_cc006800)[param_1 * 5];
    (&DAT_cc006800)[param_1 * 5] = uVar3 & 0x405;
    if ((*(uint *)(&DAT_803d76bc + iVar2) & 8) != 0) {
      if (param_1 == 1) {
        gnt4___OSUnmaskInterrupts_bl(0x20000);
      }
      else if ((param_1 < 1) && (-1 < param_1)) {
        gnt4___OSUnmaskInterrupts_bl(0x100000);
      }
    }
    gnt4_OSRestoreInterrupts_bl();
    if ((param_1 == 2) || ((uVar3 & 0x80) == 0)) {
      uVar1 = 1;
    }
    else {
      iVar2 = gnt4___EXIProbe(param_1);
      if (iVar2 == 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
  }
  return uVar1;
}



// ==== 80208390  FUN_80208390 ====

void FUN_80208390(short param_1,uint param_2)

{
  int iVar1;
  code *pcVar2;
  undefined1 auStack_2e0 [724];
  
  iVar1 = (param_1 + -9) / 3;
  (&DAT_cc006800)[iVar1 * 5] = (&DAT_cc006800)[iVar1 * 5] & 0x7f5 | 2;
  pcVar2 = *(code **)(&DAT_803d76b0 + iVar1 * 0x40);
  if (pcVar2 != (code *)0x0) {
    gnt4_OSClearContext_bl((int)auStack_2e0);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2e0);
    (*pcVar2)(iVar1,param_2);
    gnt4_OSClearContext_bl((int)auStack_2e0);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  return;
}



// ==== 80208458  FUN_80208458 ====

void FUN_80208458(short param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined1 *puVar7;
  int iVar8;
  uint uVar9;
  undefined1 auStack_2d8 [712];
  
  iVar2 = (param_1 + -10) / 3;
  iVar1 = iVar2 * 0x40;
  gnt4___OSMaskInterrupts_bl(0x80000000 >> (int)param_1);
  (&DAT_cc006800)[iVar2 * 5] = (&DAT_cc006800)[iVar2 * 5] & 0x7f5 | 8;
  pcVar3 = *(code **)(&DAT_803d76b4 + iVar1);
  if (pcVar3 != (code *)0x0) {
    iVar6 = 0;
    *(undefined4 *)(&DAT_803d76b4 + iVar1) = 0;
    if ((*(uint *)(&DAT_803d76bc + iVar1) & 3) != 0) {
      if ((*(uint *)(&DAT_803d76bc + iVar1) & 2) != 0) {
        iVar5 = *(int *)(&DAT_803d76c0 + iVar1);
        if (iVar5 != 0) {
          puVar7 = *(undefined1 **)(&DAT_803d76c4 + iVar1);
          uVar4 = *(uint *)(&DAT_cc006810 + iVar2 * 0x14);
          if (0 < iVar5) {
            if ((8 < iVar5) && (uVar9 = iVar5 - 1U >> 3, 0 < iVar5 + -8)) {
              do {
                *puVar7 = (char)(uVar4 >> (3 - iVar6) * 8);
                puVar7[1] = (char)(uVar4 >> (3 - (iVar6 + 1)) * 8);
                puVar7[2] = (char)(uVar4 >> (3 - (iVar6 + 2)) * 8);
                puVar7[3] = (char)(uVar4 >> iVar6 * -8);
                puVar7[4] = (char)(uVar4 >> (3 - (iVar6 + 4)) * 8);
                puVar7[5] = (char)(uVar4 >> (3 - (iVar6 + 5)) * 8);
                puVar7[6] = (char)(uVar4 >> (3 - (iVar6 + 6)) * 8);
                puVar7[7] = (char)(uVar4 >> (3 - (iVar6 + 7)) * 8);
                puVar7 = puVar7 + 8;
                iVar6 = iVar6 + 8;
                uVar9 = uVar9 - 1;
              } while (uVar9 != 0);
            }
            iVar8 = iVar5 - iVar6;
            if (iVar6 < iVar5) {
              do {
                *puVar7 = (char)(uVar4 >> (3 - iVar6) * 8);
                puVar7 = puVar7 + 1;
                iVar6 = iVar6 + 1;
                iVar8 = iVar8 + -1;
              } while (iVar8 != 0);
            }
          }
        }
      }
      *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xfffffffc;
    }
    gnt4_OSClearContext_bl((int)auStack_2d8);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2d8);
    (*pcVar3)(iVar2,param_2);
    gnt4_OSClearContext_bl((int)auStack_2d8);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  return;
}



// ==== 80208670  FUN_80208670 ====

void FUN_80208670(short param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  undefined1 auStack_2d8 [712];
  
  iVar2 = (param_1 + -0xb) / 3;
  gnt4___OSMaskInterrupts_bl(0x500000 >> iVar2 * 3);
  iVar1 = iVar2 * 0x40;
  pcVar3 = *(code **)(&DAT_803d76b8 + iVar1);
  *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xfffffff7;
  if (pcVar3 != (code *)0x0) {
    gnt4_OSClearContext_bl((int)auStack_2d8);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2d8);
    *(undefined4 *)(&DAT_803d76b8 + iVar1) = 0;
    (*pcVar3)(iVar2,param_2);
    gnt4_OSClearContext_bl((int)auStack_2d8);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  return;
}



// ==== 80208740  zz_0208740_ ====

void zz_0208740_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  byte *pbVar4;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int local_18 [2];
  
  do {
    do {
      uVar1 = DAT_cc00680c;
    } while ((uVar1 & 1) == 1);
    uVar1 = DAT_cc006820;
  } while (((uVar1 & 1) == 1) || (uVar1 = DAT_cc006834, (uVar1 & 1) == 1));
  gnt4___OSMaskInterrupts_bl(0x7f8000);
  DAT_cc006800 = 0;
  DAT_cc006814 = 0;
  DAT_cc006828 = 0;
  DAT_cc006800 = 0x2000;
  gnt4___OSSetInterruptHandler_bl(9,FUN_80208390);
  gnt4___OSSetInterruptHandler_bl(10,FUN_80208458);
  gnt4___OSSetInterruptHandler_bl(0xb,FUN_80208670);
  gnt4___OSSetInterruptHandler_bl(0xc,FUN_80208390);
  gnt4___OSSetInterruptHandler_bl(0xd,FUN_80208458);
  gnt4___OSSetInterruptHandler_bl(0xe,FUN_80208670);
  gnt4___OSSetInterruptHandler_bl(0xf,FUN_80208390);
  gnt4___OSSetInterruptHandler_bl(0x10,FUN_80208458);
  pbVar4 = (byte *)&DAT_804364a0;
  zz_0208b24_(0,2,(byte *)&DAT_804364a0);
  if (DAT_804363f0 == 0) {
    pbVar4 = (byte *)local_18;
    iVar2 = zz_0208b24_(0,0,pbVar4);
    if ((iVar2 == 0) || (local_18[0] != 0x7010000)) {
      uVar3 = 0;
      pbVar4 = (byte *)local_18;
      iVar2 = zz_0208b24_(1,0,pbVar4);
      if ((iVar2 != 0) && (local_18[0] == 0x7010000)) {
        param_1 = zz_0209060_(0,2);
        uVar3 = extraout_r4_00;
      }
    }
    else {
      param_1 = zz_0209060_(1,0);
      uVar3 = extraout_r4;
    }
  }
  else {
    uVar3 = 0x80000000;
    DAT_800030c4 = 0;
    DAT_800030c0 = 0;
    DAT_803d7710 = 0;
    DAT_803d76d0 = 0;
    gnt4___EXIProbe(0);
    gnt4___EXIProbe(1);
  }
  gnt4_OSRegisterVersion_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435c90,uVar3,
             pbVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80208914  gnt4-EXILock-bl ====

undefined4 gnt4_EXILock_bl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar1 = param_1 * 0x40;
  piVar5 = (int *)(&DAT_803d76b0 + iVar1);
  gnt4_OSDisableInterrupts_bl();
  if ((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) == 0) {
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 0x10;
    *(int *)(&DAT_803d76c8 + iVar1) = param_2;
    gnt4_SetExiInterruptMask(param_1,piVar5);
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 1;
  }
  else {
    if (param_3 != 0) {
      iVar4 = *(int *)(&DAT_803d76d4 + iVar1);
      piVar2 = piVar5;
      iVar6 = iVar4;
      if (0 < iVar4) {
        do {
          if (piVar2[10] == param_2) {
            gnt4_OSRestoreInterrupts_bl();
            return 0;
          }
          piVar2 = piVar2 + 2;
          iVar6 = iVar6 + -1;
        } while (iVar6 != 0);
      }
      piVar5[iVar4 * 2 + 0xb] = param_3;
      piVar5[*(int *)(&DAT_803d76d4 + iVar1) * 2 + 10] = param_2;
      *(int *)(&DAT_803d76d4 + iVar1) = *(int *)(&DAT_803d76d4 + iVar1) + 1;
    }
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 80208a08  gnt4-EXIUnlock-bl ====

undefined4 gnt4_EXIUnlock_bl(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  iVar1 = param_1 * 0x40;
  gnt4_OSDisableInterrupts_bl();
  if ((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) == 0) {
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 0;
  }
  else {
    *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xffffffef;
    gnt4_SetExiInterruptMask(param_1,(int *)(&DAT_803d76b0 + iVar1));
    if (0 < *(int *)(&DAT_803d76d4 + iVar1)) {
      pcVar4 = *(code **)(&DAT_803d76dc + iVar1);
      iVar2 = *(int *)(&DAT_803d76d4 + iVar1) + -1;
      *(int *)(&DAT_803d76d4 + iVar1) = iVar2;
      if (0 < iVar2) {
        gnt4_memmove_bl((uint)(&DAT_803d76d8 + iVar1),(uint)(&DAT_803d76e0 + iVar1),
                        *(int *)(&DAT_803d76d4 + iVar1) << 3);
      }
      (*pcVar4)(param_1,0);
    }
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = 1;
  }
  return uVar3;
}



// ==== 80208ae4  zz_0208ae4_ ====

undefined4 zz_0208ae4_(int param_1)

{
  return *(undefined4 *)(&DAT_803d76bc + param_1 * 0x40);
}



// ==== 80208afc  FUN_80208afc ====

void FUN_80208afc(int param_1)

{
  byte abStack_8 [8];
  
  zz_0208b24_(param_1,0,abStack_8);
  return;
}



// ==== 80208b24  zz_0208b24_ ====

undefined4 zz_0208b24_(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  bool bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  code *pcVar11;
  int unaff_r29;
  byte local_2c [8];
  
  iVar1 = param_1 * 0x40;
  if (((param_1 == 0) && (param_2 == 2)) && (DAT_804364a0 != 0)) {
    *(int *)param_3 = DAT_804364a0;
    return 1;
  }
  if ((param_1 < 2) && (param_2 == 0)) {
    iVar9 = gnt4___EXIProbe(param_1);
    if (iVar9 == 0) {
      return 0;
    }
    if ((&DAT_803d76d0)[param_1 * 0x10] == (&DAT_800030c0)[param_1]) {
      *(undefined4 *)param_3 = *(undefined4 *)(&DAT_803d76cc + iVar1);
      return (&DAT_803d76d0)[param_1 * 0x10];
    }
    gnt4_OSDisableInterrupts_bl();
    if (((*(uint *)(&DAT_803d76bc + iVar1) & 8) == 0) &&
       (iVar9 = gnt4___EXIProbe(param_1), iVar9 != 0)) {
      gnt4_EXIClearInterrupts(param_1,1,0,0);
      *(undefined4 *)(&DAT_803d76b8 + iVar1) = 0;
      gnt4___OSUnmaskInterrupts_bl(0x100000 >> param_1 * 3);
      *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) | 8;
      gnt4_OSRestoreInterrupts_bl();
      bVar2 = true;
    }
    else {
      gnt4_OSRestoreInterrupts_bl();
      bVar2 = false;
    }
    if (!bVar2) {
      return 0;
    }
    unaff_r29 = (&DAT_800030c0)[param_1];
  }
  gnt4_OSDisableInterrupts_bl();
  bVar2 = false;
  if ((param_1 < 2) && (param_2 == 0)) {
    bVar2 = true;
  }
  if (bVar2) {
    pcVar11 = FUN_80208afc;
  }
  else {
    pcVar11 = (code *)0x0;
  }
  uVar10 = gnt4_EXILock_bl(param_1,param_2,(int)pcVar11);
  uVar3 = countLeadingZeros(uVar10);
  uVar3 = uVar3 >> 5;
  if (uVar3 == 0) {
    uVar10 = gnt4_EXISelect_bl(param_1,param_2,0);
    uVar4 = countLeadingZeros(uVar10);
    uVar3 = uVar4 >> 5;
    if (uVar3 == 0) {
      local_2c[0] = 0;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_2c[3] = 0;
      uVar10 = gnt4_EXIImm_bl(param_1,local_2c,2,1,0);
      uVar3 = countLeadingZeros(uVar10);
      uVar10 = gnt4_EXISync(param_1);
      uVar5 = countLeadingZeros(uVar10);
      uVar10 = gnt4_EXIImm_bl(param_1,param_3,4,0,0);
      uVar6 = countLeadingZeros(uVar10);
      uVar10 = gnt4_EXISync(param_1);
      uVar7 = countLeadingZeros(uVar10);
      uVar10 = gnt4_EXIDeselect(param_1);
      uVar8 = countLeadingZeros(uVar10);
      uVar3 = (uVar4 | uVar3 | uVar5 | uVar6 | uVar7 | uVar8) >> 5;
    }
    gnt4_OSDisableInterrupts_bl();
    if ((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) == 0) {
      gnt4_OSRestoreInterrupts_bl();
    }
    else {
      *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xffffffef;
      gnt4_SetExiInterruptMask(param_1,(int *)(&DAT_803d76b0 + iVar1));
      if (0 < *(int *)(&DAT_803d76d4 + iVar1)) {
        pcVar11 = *(code **)(&DAT_803d76dc + iVar1);
        iVar9 = *(int *)(&DAT_803d76d4 + iVar1) + -1;
        *(int *)(&DAT_803d76d4 + iVar1) = iVar9;
        if (0 < iVar9) {
          gnt4_memmove_bl((uint)(&DAT_803d76d8 + iVar1),(uint)(&DAT_803d76e0 + iVar1),
                          *(int *)(&DAT_803d76d4 + iVar1) << 3);
        }
        (*pcVar11)(param_1,0);
      }
      gnt4_OSRestoreInterrupts_bl();
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  if ((param_1 < 2) && (param_2 == 0)) {
    gnt4_OSDisableInterrupts_bl();
    if ((*(uint *)(&DAT_803d76bc + iVar1) & 8) == 0) {
      gnt4_OSRestoreInterrupts_bl();
    }
    else if (((*(uint *)(&DAT_803d76bc + iVar1) & 0x10) == 0) ||
            (*(int *)(&DAT_803d76c8 + iVar1) != 0)) {
      *(uint *)(&DAT_803d76bc + iVar1) = *(uint *)(&DAT_803d76bc + iVar1) & 0xfffffff7;
      gnt4___OSMaskInterrupts_bl(0x500000 >> param_1 * 3);
      gnt4_OSRestoreInterrupts_bl();
    }
    else {
      gnt4_OSRestoreInterrupts_bl();
    }
    gnt4_OSDisableInterrupts_bl();
    iVar9 = (&DAT_800030c0)[param_1];
    if (uVar3 == 0 && iVar9 == unaff_r29) {
      *(undefined4 *)(&DAT_803d76cc + iVar1) = *(undefined4 *)param_3;
      (&DAT_803d76d0)[param_1 * 0x10] = unaff_r29;
    }
    gnt4_OSRestoreInterrupts_bl();
    if (uVar3 == 0 && iVar9 == unaff_r29) {
      uVar10 = (&DAT_803d76d0)[param_1 * 0x10];
    }
    else {
      uVar10 = 0;
    }
  }
  else if (uVar3 == 0) {
    uVar10 = 1;
  }
  else {
    uVar10 = 0;
  }
  return uVar10;
}



// ==== 80208ed4  zz_0208ed4_ ====

undefined4 zz_0208ed4_(int param_1,int param_2,byte *param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  byte local_14 [4];
  
  if (((param_1 != 2) && (param_2 == 0)) && (iVar6 = zz_0207f8c_(param_1,0), iVar6 == 0)) {
    return 0;
  }
  uVar7 = gnt4_EXILock_bl(param_1,param_2,0);
  uVar1 = countLeadingZeros(uVar7);
  uVar1 = uVar1 >> 5;
  if (uVar1 == 0) {
    uVar7 = gnt4_EXISelect_bl(param_1,param_2,0);
    uVar1 = countLeadingZeros(uVar7);
    uVar1 = uVar1 >> 5;
    if (uVar1 == 0) {
      local_14[0] = 0x20;
      local_14[1] = 1;
      local_14[2] = 0x13;
      local_14[3] = 0;
      uVar7 = gnt4_EXIImm_bl(param_1,local_14,4,1,0);
      uVar1 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXISync(param_1);
      uVar2 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXIImm_bl(param_1,param_3,4,0,0);
      uVar3 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXISync(param_1);
      uVar4 = countLeadingZeros(uVar7);
      uVar7 = gnt4_EXIDeselect(param_1);
      uVar5 = countLeadingZeros(uVar7);
      uVar1 = (uVar1 | uVar2 | uVar3 | uVar4 | uVar5) >> 5;
    }
    gnt4_EXIUnlock_bl(param_1);
  }
  if ((param_1 != 2) && (param_2 == 0)) {
    zz_0208098_(param_1);
  }
  if (uVar1 == 0) {
    if (*(int *)param_3 == -1) {
      uVar7 = 0;
    }
    else {
      uVar7 = 1;
    }
  }
  else {
    uVar7 = 0;
  }
  return uVar7;
}



// ==== 80209060  zz_0209060_ ====

void zz_0209060_(int param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *local_10 [2];
  
  iVar2 = zz_0208b24_(param_1,param_2,(byte *)local_10);
  if (iVar2 == 0) {
    return;
  }
  if (local_10[0] == (undefined4 *)0x1020000) {
    return;
  }
  if ((int)local_10[0] < 0x1020000) {
    if (local_10[0] == (undefined4 *)0x4) {
      return;
    }
    if ((int)local_10[0] < 4) {
      if (local_10[0] == (undefined4 *)&DAT_80000010) {
        return;
      }
      if ((int)local_10[0] < -0x7ffffff0) {
        if (local_10[0] == (undefined4 *)&DAT_80000008) {
          return;
        }
        if (-0x7ffffff9 < (int)local_10[0]) goto LAB_802091d4;
        puVar1 = (undefined4 *)&DAT_80000004;
      }
      else {
        if (local_10[0] == (undefined4 *)0xffffffff) {
          return;
        }
        if (-2 < (int)local_10[0]) goto LAB_802091d4;
        puVar1 = &DAT_80000020;
      }
      if (local_10[0] == puVar1) {
        return;
      }
    }
    else {
      if (local_10[0] == (undefined4 *)0x20) {
        return;
      }
      if ((int)local_10[0] < 0x20) {
        if (local_10[0] == (undefined4 *)0x10) {
          return;
        }
        if (((int)local_10[0] < 0x10) && (local_10[0] == (undefined4 *)0x8)) {
          return;
        }
      }
      else if (local_10[0] == (undefined4 *)0x1010000) {
        return;
      }
    }
  }
  else {
    if (local_10[0] == (undefined4 *)0x4040404) {
      return;
    }
    if ((int)local_10[0] < 0x4040404) {
      if (local_10[0] == (undefined4 *)0x4020100) {
        return;
      }
      if ((int)local_10[0] < 0x4020100) {
        if (local_10[0] == (undefined4 *)0x3010000) {
          return;
        }
        if (((int)local_10[0] < 0x3010000) && (local_10[0] == (undefined4 *)0x2020000)) {
          return;
        }
      }
      else {
        if (local_10[0] == (undefined4 *)0x4020300) {
          return;
        }
        if (((int)local_10[0] < 0x4020300) && (local_10[0] == (undefined4 *)0x4020200)) {
          return;
        }
      }
    }
    else {
      if (local_10[0] == (undefined4 *)0x4130000) {
        return;
      }
      if ((int)local_10[0] < 0x4130000) {
        if (local_10[0] == (undefined4 *)0x4120000) {
          return;
        }
        if (((int)local_10[0] < 0x4120000) && (local_10[0] == (undefined4 *)0x4060000)) {
          return;
        }
      }
      else if (local_10[0] == (undefined4 *)0x4220000) {
        return;
      }
    }
  }
LAB_802091d4:
  iVar2 = zz_0208ed4_(param_1,param_2,(byte *)local_10);
  if (iVar2 != 0) {
    DAT_804364b4 = 0xa5ff005a;
    DAT_804364b0 = 0xa5ff005a;
    DAT_804364a8 = param_1;
    DAT_804364ac = param_2;
  }
  return;
}



// ==== 8020921c  zz_020921c_ ====

undefined4 zz_020921c_(void)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (DAT_804364b4 == -0x5a00ffa6) {
    uVar1 = 0;
  }
  else {
    uVar2 = gnt4_OSGetConsoleType_bl();
    if ((uVar2 & 0x10000000) == 0) {
      DAT_804364b0 = 0;
      uVar1 = 2;
    }
    else {
      DAT_804364b0 = 0xa5ff005a;
      DAT_804364a8 = 0;
      uVar1 = 0;
      DAT_804364ac = 1;
    }
  }
  return uVar1;
}



// ==== 8020928c  zz_020928c_ ====

undefined4 zz_020928c_(byte *param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint local_28;
  byte local_24 [8];
  
  if (DAT_804364b0 == -0x5a00ffa6) {
    gnt4_OSDisableInterrupts_bl();
    iVar3 = gnt4_EXILock_bl(DAT_804364a8,DAT_804364ac,0);
    pbVar4 = param_1;
    if (iVar3 == 0) {
      gnt4_OSRestoreInterrupts_bl();
      uVar2 = 0;
    }
    else {
      for (; (uint)((int)pbVar4 - (int)param_1) < param_2; pbVar4 = pbVar4 + 1) {
        if (*pbVar4 == 10) {
          *pbVar4 = 0xd;
        }
      }
      local_24[0] = 0xa0;
      local_24[1] = 1;
      local_24[2] = 0;
      local_24[3] = 0;
      uVar2 = 0;
      while (param_2 != 0) {
        iVar3 = gnt4_EXISelect_bl(DAT_804364a8,DAT_804364ac,3);
        if (iVar3 == 0) {
          uVar1 = 0xffffffff;
        }
        else {
          local_28 = 0x20010000;
          gnt4_EXIImm_bl(DAT_804364a8,(byte *)&local_28,4,1,0);
          gnt4_EXISync(DAT_804364a8);
          gnt4_EXIImm_bl(DAT_804364a8,(byte *)&local_28,1,0,0);
          gnt4_EXISync(DAT_804364a8);
          gnt4_EXIDeselect(DAT_804364a8);
          uVar1 = 0x10 - (local_28 >> 0x18);
        }
        if ((int)uVar1 < 0) {
          uVar2 = 3;
          break;
        }
        if ((0xb < (int)uVar1) || (param_2 <= uVar1)) {
          iVar3 = gnt4_EXISelect_bl(DAT_804364a8,DAT_804364ac,3);
          if (iVar3 == 0) {
            uVar2 = 3;
            break;
          }
          gnt4_EXIImm_bl(DAT_804364a8,local_24,4,1,0);
          gnt4_EXISync(DAT_804364a8);
          for (; ((uVar1 != 0 && (param_2 != 0)) && ((3 < (int)uVar1 || (param_2 <= uVar1))));
              param_2 = param_2 - uVar5) {
            uVar5 = param_2;
            if (3 < param_2) {
              uVar5 = 4;
            }
            gnt4_EXIImm_bl(DAT_804364a8,param_1,uVar5,1,0);
            param_1 = param_1 + uVar5;
            uVar1 = uVar1 - uVar5;
            gnt4_EXISync(DAT_804364a8);
          }
          gnt4_EXIDeselect(DAT_804364a8);
        }
      }
      gnt4_EXIUnlock_bl(DAT_804364a8);
      gnt4_OSRestoreInterrupts_bl();
    }
  }
  else {
    uVar2 = 2;
  }
  return uVar2;
}



// ==== 802094a8  zz_02094a8_ ====

undefined4 zz_02094a8_(void)

{
  if (DAT_803a4cfc != -1) {
    return 1;
  }
  return 0;
}



// ==== 802094c8  gnt4-SIIsChanBusy ====

undefined4 gnt4_SIIsChanBusy(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if (((&DAT_803d7770)[param_1 * 8] == -1) && (DAT_803a4cfc != param_1)) {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80209504  zz_0209504_ ====

uint zz_0209504_(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  undefined *puVar7;
  uint uVar8;
  uint uVar9;
  longlong lVar10;
  
  puVar7 = &DAT_cc006400;
  uVar5 = DAT_cc006434;
  uVar6 = DAT_cc006438;
  DAT_cc006434 = uVar5 & 0xfffffffe | 0x80000000;
  if (DAT_803a4cfc != -1) {
    lVar10 = gnt4___OSGetSystemTime_bl();
    uVar3 = 0;
    *(longlong *)(&DAT_803d78b0 + DAT_803a4cfc * 8) = lVar10;
    uVar5 = DAT_803a4d04 >> 2;
    puVar4 = DAT_803a4d08;
    if (uVar5 != 0) {
      if ((8 < uVar5) && (uVar8 = uVar5 - 1 >> 3, uVar5 != 8)) {
        do {
          uVar3 = uVar3 + 8;
          *puVar4 = *(undefined4 *)(puVar7 + 0x80);
          puVar4[1] = *(undefined4 *)(puVar7 + 0x84);
          puVar4[2] = *(undefined4 *)(puVar7 + 0x88);
          puVar4[3] = *(undefined4 *)(puVar7 + 0x8c);
          puVar4[4] = *(undefined4 *)(puVar7 + 0x90);
          puVar4[5] = *(undefined4 *)(puVar7 + 0x94);
          puVar4[6] = *(undefined4 *)(puVar7 + 0x98);
          puVar1 = (undefined4 *)(puVar7 + 0x9c);
          puVar7 = puVar7 + 0x20;
          puVar4[7] = *puVar1;
          puVar4 = puVar4 + 8;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
      }
      puVar7 = &DAT_cc006400 + uVar3 * 4;
      iVar2 = uVar5 - uVar3;
      if (uVar3 < uVar5) {
        do {
          puVar1 = (undefined4 *)(puVar7 + 0x80);
          puVar7 = puVar7 + 4;
          uVar3 = uVar3 + 1;
          *puVar4 = *puVar1;
          puVar4 = puVar4 + 1;
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
    }
    uVar5 = DAT_803a4d04 & 3;
    if (uVar5 != 0) {
      uVar8 = (&DAT_cc006480)[uVar3];
      uVar3 = 0;
      if (uVar5 != 0) {
        if ((8 < uVar5) && (uVar9 = uVar5 - 1 >> 3, uVar5 != 8)) {
          do {
            *(char *)puVar4 = (char)(uVar8 >> (3 - uVar3) * 8);
            *(char *)((int)puVar4 + 1) = (char)(uVar8 >> (3 - (uVar3 + 1)) * 8);
            *(char *)((int)puVar4 + 2) = (char)(uVar8 >> (3 - (uVar3 + 2)) * 8);
            *(char *)((int)puVar4 + 3) = (char)(uVar8 >> uVar3 * -8);
            *(char *)(puVar4 + 1) = (char)(uVar8 >> (3 - (uVar3 + 4)) * 8);
            *(char *)((int)puVar4 + 5) = (char)(uVar8 >> (3 - (uVar3 + 5)) * 8);
            *(char *)((int)puVar4 + 6) = (char)(uVar8 >> (3 - (uVar3 + 6)) * 8);
            *(char *)((int)puVar4 + 7) = (char)(uVar8 >> (3 - (uVar3 + 7)) * 8);
            puVar4 = puVar4 + 2;
            uVar3 = uVar3 + 8;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
        }
        iVar2 = uVar5 - uVar3;
        if (uVar3 < uVar5) {
          do {
            *(char *)puVar4 = (char)(uVar8 >> (3 - uVar3) * 8);
            puVar4 = (undefined4 *)((int)puVar4 + 1);
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + -1;
          } while (iVar2 != 0);
        }
      }
    }
    uVar5 = DAT_cc006434;
    if ((uVar5 & 0x20000000) == 0) {
      lVar10 = gnt4___OSGetSystemTime_bl();
      uVar6 = 0;
      *(longlong *)(&DAT_803d7890 + DAT_803a4cfc * 8) = lVar10;
    }
    else {
      uVar5 = uVar6 >> (3 - DAT_803a4cfc) * 8;
      uVar6 = uVar5 & 0xf;
      if (((uVar5 & 8) != 0) && ((*(uint *)(&DAT_803a4d10 + DAT_803a4cfc * 4) & 0x80) == 0)) {
        *(uint *)(&DAT_803a4d10 + DAT_803a4cfc * 4) = 8;
      }
      if (uVar6 == 0) {
        uVar6 = 4;
      }
    }
    DAT_803a4cfc = -1;
  }
  return uVar6;
}



// ==== 80209800  FUN_80209800 ====

void FUN_80209800(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  code *pcVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  undefined4 *puVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  longlong lVar10;
  
  uVar4 = DAT_803a4cfc;
  uVar1 = DAT_cc006434;
  if ((uVar1 & 0xc0000000) == 0xc0000000) {
    uVar3 = zz_0209504_();
    pcVar2 = DAT_803a4d0c;
    iVar9 = 0;
    DAT_803a4d0c = (code *)0x0;
    uVar8 = uVar4;
    do {
      uVar8 = uVar8 + 1;
      uVar8 = uVar8 + (((int)uVar8 >> 2) + (uint)((int)uVar8 < 0 && (uVar8 & 3) != 0)) * -4;
      puVar7 = &DAT_803d7770 + uVar8 * 8;
      if ((*puVar7 != 0xffffffff) &&
         (lVar10 = gnt4___OSGetSystemTime_bl(),
         (uint)((uint)lVar10 < (uint)(&DAT_803d778c)[uVar8 * 8]) +
         ((&DAT_803d7788)[uVar8 * 8] ^ 0x80000000) <=
         ((uint)((ulonglong)lVar10 >> 0x20) ^ 0x80000000))) {
        iVar9 = gnt4___SITransfer(*puVar7,(undefined4 *)(&DAT_803d7774)[uVar8 * 8],
                                  (&DAT_803d7778)[uVar8 * 8],(&DAT_803d777c)[uVar8 * 8],
                                  (&DAT_803d7780)[uVar8 * 8],(&DAT_803d7784)[uVar8 * 8]);
        if (iVar9 != 0) {
          gnt4_OSCancelAlarm_bl((int *)(&DAT_803d77f0 + uVar8 * 0x28));
          *puVar7 = 0xffffffff;
        }
        break;
      }
      iVar9 = iVar9 + 1;
    } while (iVar9 < 4);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(uVar4,uVar3,param_2);
    }
    uVar8 = DAT_cc006438;
    DAT_cc006438 = uVar8 & 0xf000000 >> ((uVar4 & 7) << 3);
    if (*(int *)(&DAT_803a4d10 + uVar4 * 4) == 0x80) {
      bVar5 = true;
      if (((&DAT_803d7770)[uVar4 * 8] == -1) && (DAT_803a4cfc != uVar4)) {
        bVar5 = false;
      }
      if (!bVar5) {
        gnt4_SITransfer_bl(uVar4,(undefined4 *)&DAT_804364b8,1,&DAT_803a4d10 + uVar4 * 4,3,
                           -0x7fdf5a00,0,(DAT_800000f8 / 500000) * 0x41 >> 3);
      }
    }
  }
  if ((uVar1 & 0x18000000) == 0x18000000) {
    uVar4 = zz_02124b4_();
    puVar7 = (uint *)&DAT_803d7950;
    uVar4 = uVar4 + 1;
    uVar1 = DAT_803a4d00 >> 0x10;
    iVar9 = 0;
    do {
      bVar5 = zz_020a270_(iVar9);
      if (bVar5) {
        *puVar7 = uVar4;
      }
      iVar9 = iVar9 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar9 < 4);
    uVar1 = (uVar1 & 0x3ff) >> 1;
    if ((((((DAT_803a4d00 & 0x80) == 0) || ((DAT_803d7950 != 0 && (uVar4 <= uVar1 + DAT_803d7950))))
         && (((DAT_803a4d00 & 0x40) == 0 || ((DAT_803d7954 != 0 && (uVar4 <= uVar1 + DAT_803d7954)))
             ))) &&
        (((DAT_803a4d00 & 0x20) == 0 || ((DAT_803d7958 != 0 && (uVar4 <= uVar1 + DAT_803d7958))))))
       && (((DAT_803a4d00 & 0x10) == 0 || ((DAT_803d795c != 0 && (uVar4 <= uVar1 + DAT_803d795c)))))
       ) {
      iVar9 = 0;
      DAT_803d7950 = 0;
      puVar6 = &DAT_803d7910;
      DAT_803d7954 = 0;
      DAT_803d7958 = 0;
      DAT_803d795c = 0;
      do {
        if ((code *)*puVar6 != (code *)0x0) {
          (*(code *)*puVar6)(param_1,param_2);
        }
        iVar9 = iVar9 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar9 < 4);
    }
  }
  return;
}



// ==== 80209b44  gnt4-SIEnablePollingInterrupt ====

bool gnt4_SIEnablePollingInterrupt(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_cc006434;
  if (param_1 == 0) {
    uVar2 = uVar1 & 0xf7ffffff;
  }
  else {
    DAT_803d7950 = 0;
    uVar2 = uVar1 | 0x8000000;
    DAT_803d7954 = 0;
    DAT_803d7958 = 0;
    DAT_803d795c = 0;
  }
  DAT_cc006434 = uVar2 & 0x7ffffffe;
  gnt4_OSRestoreInterrupts_bl();
  return (uVar1 & 0x8000000) != 0;
}



// ==== 80209bdc  gnt4-SIRegisterPollingHandler-bl ====

undefined4 gnt4_SIRegisterPollingHandler_bl(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  gnt4_OSDisableInterrupts_bl();
  piVar2 = &DAT_803d7910;
  iVar3 = 4;
  piVar1 = piVar2;
  do {
    if (*piVar1 == param_1) {
      gnt4_OSRestoreInterrupts_bl();
      return 1;
    }
    piVar1 = piVar1 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar4 = 4;
  iVar3 = 0;
  do {
    if (*piVar2 == 0) {
      (&DAT_803d7910)[iVar3] = param_1;
      gnt4_SIEnablePollingInterrupt(1);
      gnt4_OSRestoreInterrupts_bl();
      return 1;
    }
    piVar2 = piVar2 + 1;
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  gnt4_OSRestoreInterrupts_bl();
  return 0;
}



// ==== 80209ca8  gnt4-SIUnregisterPollingHandler ====

undefined4 gnt4_SIUnregisterPollingHandler(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  gnt4_OSDisableInterrupts_bl();
  piVar2 = &DAT_803d7910;
  iVar3 = 4;
  iVar1 = 0;
  do {
    if (*piVar2 == param_1) {
      (&DAT_803d7910)[iVar1] = 0;
      iVar1 = 0;
      if ((((DAT_803d7910 == 0) && (iVar1 = 1, DAT_803d7914 == 0)) && (iVar1 = 2, DAT_803d7918 == 0)
          ) && (iVar1 = 3, DAT_803d791c == 0)) {
        iVar1 = 4;
      }
      if (iVar1 == 4) {
        gnt4_SIEnablePollingInterrupt(0);
      }
      gnt4_OSRestoreInterrupts_bl();
      return 1;
    }
    piVar2 = piVar2 + 1;
    iVar1 = iVar1 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  gnt4_OSRestoreInterrupts_bl();
  return 0;
}



// ==== 80209d9c  zz_0209d9c_ ====

void zz_0209d9c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = gnt4_OSRegisterVersion_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435c98,
                     &DAT_803d0000,param_11,param_12,param_13,param_14,param_15,param_16);
  DAT_803d77d0 = 0xffffffff;
  DAT_803d77b0 = 0xffffffff;
  DAT_803d7790 = 0xffffffff;
  DAT_803d7770 = 0xffffffff;
  DAT_803a4d00 = 0;
  zz_020ad08_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,&DAT_803a4cfc,
              0xffffffff,param_12,param_13,param_14,param_15,param_16);
  do {
    uVar1 = DAT_cc006434;
  } while ((uVar1 & 1) != 0);
  DAT_cc006434 = 0x80000000;
  gnt4___OSSetInterruptHandler_bl(0x14,FUN_80209800);
  gnt4___OSUnmaskInterrupts_bl(0x800);
  gnt4_SIGetType(0);
  gnt4_SIGetType(1);
  gnt4_SIGetType(2);
  gnt4_SIGetType(3);
  return;
}



// ==== 80209e50  gnt4-__SITransfer ====

undefined4
gnt4___SITransfer(uint param_1,undefined4 *param_2,int param_3,undefined4 param_4,int param_5,
                 int param_6)

{
  undefined4 *puVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  undefined4 local_24;
  
  gnt4_OSDisableInterrupts_bl();
  if (DAT_803a4cfc == 0xffffffff) {
    uVar2 = DAT_cc006438;
    DAT_cc006438 = uVar2 & 0xf000000 >> ((param_1 & 7) << 3);
    uVar2 = param_3 + 3U >> 2;
    uVar6 = 0;
    DAT_803a4cfc = param_1;
    DAT_803a4d04 = param_5;
    DAT_803a4d08 = param_4;
    DAT_803a4d0c = param_6;
    if (uVar2 != 0) {
      if (8 < uVar2) {
        uVar9 = uVar2 - 1 >> 3;
        puVar7 = &DAT_cc006400;
        puVar8 = param_2;
        if (uVar2 != 8) {
          do {
            uVar6 = uVar6 + 8;
            *(undefined4 *)(puVar7 + 0x80) = *puVar8;
            *(undefined4 *)(puVar7 + 0x84) = puVar8[1];
            *(undefined4 *)(puVar7 + 0x88) = puVar8[2];
            *(undefined4 *)(puVar7 + 0x8c) = puVar8[3];
            *(undefined4 *)(puVar7 + 0x90) = puVar8[4];
            *(undefined4 *)(puVar7 + 0x94) = puVar8[5];
            *(undefined4 *)(puVar7 + 0x98) = puVar8[6];
            puVar1 = puVar8 + 7;
            puVar8 = puVar8 + 8;
            *(undefined4 *)(puVar7 + 0x9c) = *puVar1;
            puVar7 = puVar7 + 0x20;
            uVar9 = uVar9 - 1;
          } while (uVar9 != 0);
        }
      }
      puVar8 = param_2 + uVar6;
      puVar7 = &DAT_cc006400 + uVar6 * 4;
      iVar4 = uVar2 - uVar6;
      if (uVar6 < uVar2) {
        do {
          uVar5 = *puVar8;
          puVar8 = puVar8 + 1;
          *(undefined4 *)(puVar7 + 0x80) = uVar5;
          puVar7 = puVar7 + 4;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    uVar2 = DAT_cc006434;
    uVar2 = uVar2 & 0x7fffffff;
    if (param_3 == 0x80) {
      param_3 = 0;
    }
    local_24._1_1_ = (byte)(uVar2 >> 0x10);
    if (param_5 == 0x80) {
      param_5 = 0;
    }
    local_24._2_1_ = (byte)(uVar2 >> 8);
    bVar3 = local_24._2_1_ & 0x80;
    local_24._3_1_ = (byte)uVar2;
    local_24 = CONCAT22(CONCAT11((param_6 != 0) << 6 | (byte)(uVar2 >> 0x18) & 0xbf | 0x80,
                                 (byte)param_3 & 0x7f | local_24._1_1_ & 0x80),
                        CONCAT11((byte)param_5 & 0x7f | bVar3,(byte)local_24));
    local_24 = CONCAT31(local_24._0_3_,(byte)(param_1 << 1) & 6 | (byte)local_24 & 0xf9) &
               0xfffffffe | 1;
    DAT_cc006434 = local_24;
    gnt4_OSRestoreInterrupts_bl();
    uVar5 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar5 = 0;
  }
  return uVar5;
}



// ==== 8020a05c  gnt4-SIGetStatus ====

uint gnt4_SIGetStatus(int param_1)

{
  uint uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_cc006438;
  uVar1 = uVar1 >> (3 - param_1) * 8;
  if (((uVar1 & 8) != 0) && ((*(uint *)(&DAT_803a4d10 + param_1 * 4) & 0x80) == 0)) {
    *(uint *)(&DAT_803a4d10 + param_1 * 4) = 8;
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 8020a0d8  gnt4-SISetCommand ====

void gnt4_SISetCommand(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_cc006400 + param_1 * 0xc) = param_2;
  return;
}



// ==== 8020a0ec  gnt4-SITransferCommands ====

void gnt4_SITransferCommands(void)

{
  DAT_cc006438 = 0x80000000;
  return;
}



// ==== 8020a0fc  zz_020a0fc_ ====

uint zz_020a0fc_(int param_1,int param_2)

{
  uint uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_803a4d00 & 0xfc0000ff | param_1 << 0x10 | param_2 << 8;
  DAT_cc006430 = uVar1;
  DAT_803a4d00 = uVar1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 8020a168  gnt4-SIEnablePolling ====

uint gnt4_SIEnablePolling(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_803a4d00;
  if (param_1 != 0) {
    gnt4_OSDisableInterrupts_bl();
    uVar1 = DAT_803a4d00 & ~(param_1 >> 0x1c) | param_1 >> 0x18 & (param_1 >> 0x1c | 0x3fffff0);
    DAT_cc006438 = 0x80000000;
    DAT_cc006430 = uVar1;
    DAT_803a4d00 = uVar1;
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar1;
}



// ==== 8020a204  gnt4-SIDisablePolling ====

uint gnt4_SIDisablePolling(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_803a4d00;
  if (param_1 != 0) {
    gnt4_OSDisableInterrupts_bl();
    uVar1 = DAT_803a4d00 & ~(param_1 >> 0x18 & 0xf0);
    DAT_cc006430 = uVar1;
    DAT_803a4d00 = uVar1;
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar1;
}



// ==== 8020a270  zz_020a270_ ====

bool zz_020a270_(int param_1)

{
  bool bVar1;
  uint uVar2;
  
  gnt4_OSDisableInterrupts_bl();
  uVar2 = DAT_cc006438;
  uVar2 = uVar2 >> (3 - param_1) * 8;
  if (((uVar2 & 8) != 0) && ((*(uint *)(&DAT_803a4d10 + param_1 * 4) & 0x80) == 0)) {
    *(uint *)(&DAT_803a4d10 + param_1 * 4) = 8;
  }
  gnt4_OSRestoreInterrupts_bl();
  bVar1 = (uVar2 & 0x20) != 0;
  if (bVar1) {
    *(undefined4 *)(&DAT_803d7930 + param_1 * 8) = *(undefined4 *)(&DAT_cc006404 + param_1 * 0xc);
    *(undefined4 *)(&DAT_803d7934 + param_1 * 8) = *(undefined4 *)(&DAT_cc006408 + param_1 * 0xc);
    *(undefined4 *)(&DAT_803d7920 + param_1 * 4) = 1;
  }
  return bVar1;
}



// ==== 8020a344  gnt4-SIGetResponse ====

int gnt4_SIGetResponse(int param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = gnt4_SIGetStatus(param_1);
  if ((uVar1 & 0x20) != 0) {
    *(undefined4 *)(&DAT_803d7930 + param_1 * 8) = *(undefined4 *)(&DAT_cc006404 + param_1 * 0xc);
    *(undefined4 *)(&DAT_803d7934 + param_1 * 8) = *(undefined4 *)(&DAT_cc006408 + param_1 * 0xc);
    *(undefined4 *)(&DAT_803d7920 + param_1 * 4) = 1;
  }
  iVar2 = *(int *)(&DAT_803d7920 + param_1 * 4);
  *(undefined4 *)(&DAT_803d7920 + param_1 * 4) = 0;
  if (iVar2 != 0) {
    *param_2 = *(undefined4 *)(&DAT_803d7930 + param_1 * 8);
    param_2[1] = *(undefined4 *)(&DAT_803d7934 + param_1 * 8);
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar2;
}



// ==== 8020a408  FUN_8020a408 ====

void FUN_8020a408(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = (param_1 + 0x7fc28810) / 0x28 + (param_1 + 0x7fc28810 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  uVar2 = (&DAT_803d7770)[iVar1 * 8];
  if ((uVar2 != 0xffffffff) &&
     (iVar3 = gnt4___SITransfer(uVar2,(undefined4 *)(&DAT_803d7774)[iVar1 * 8],
                                (&DAT_803d7778)[iVar1 * 8],(&DAT_803d777c)[iVar1 * 8],
                                (&DAT_803d7780)[iVar1 * 8],(&DAT_803d7784)[iVar1 * 8]), iVar3 != 0))
  {
    (&DAT_803d7770)[iVar1 * 8] = 0xffffffff;
  }
  return;
}



// ==== 8020a494  gnt4-SITransfer-bl ====

undefined4
gnt4_SITransfer_bl(uint param_1,undefined4 *param_2,int param_3,undefined4 param_4,int param_5,
                  int param_6,int param_7,uint param_8)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  longlong lVar7;
  
  gnt4_OSDisableInterrupts_bl();
  if (((&DAT_803d7770)[param_1 * 8] == 0xffffffff) && (DAT_803a4cfc != param_1)) {
    lVar7 = gnt4___OSGetSystemTime_bl();
    uVar2 = (uint)((ulonglong)lVar7 >> 0x20);
    uVar4 = (uint)lVar7;
    if (param_8 != 0 || param_7 != 0) {
      lVar7 = CONCAT44(param_7 + *(int *)(&DAT_803d78b0 + param_1 * 8) +
                                 (uint)CARRY4(param_8,*(uint *)(&DAT_803d78b4 + param_1 * 8)),
                       param_8 + *(uint *)(&DAT_803d78b4 + param_1 * 8));
    }
    uVar6 = (uint)((ulonglong)lVar7 >> 0x20);
    uVar5 = (uint)lVar7;
    if ((uVar2 ^ 0x80000000) < (uint)(uVar4 < uVar5) + (uVar6 ^ 0x80000000)) {
      gnt4_OSSetAlarm_bl((undefined4 *)(&DAT_803d77f0 + param_1 * 0x28),0x80210000,
                         uVar6 - ((uVar5 < uVar4) + uVar2),uVar5 - uVar4,FUN_8020a408);
    }
    else {
      iVar3 = gnt4___SITransfer(param_1,param_2,param_3,param_4,param_5,param_6);
      if (iVar3 != 0) {
        gnt4_OSRestoreInterrupts_bl();
        return 1;
      }
    }
    (&DAT_803d7770)[param_1 * 8] = param_1;
    (&DAT_803d7774)[param_1 * 8] = param_2;
    (&DAT_803d7778)[param_1 * 8] = param_3;
    (&DAT_803d777c)[param_1 * 8] = param_4;
    (&DAT_803d7780)[param_1 * 8] = param_5;
    (&DAT_803d7784)[param_1 * 8] = param_6;
    *(longlong *)(&DAT_803d7788 + param_1 * 8) = lVar7;
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 1;
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8020a600  gnt4-GetTypeCallback-bl ====

void gnt4_GetTypeCallback_bl(uint param_1,uint param_2)

{
  uint uVar1;
  ushort uVar2;
  code *pcVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  undefined4 *puVar8;
  longlong lVar9;
  
  iVar6 = param_1 * 4;
  puVar7 = (uint *)(&DAT_803a4d10 + iVar6);
  *puVar7 = *puVar7 & 0xffffff7f;
  *puVar7 = *puVar7 | param_2;
  lVar9 = gnt4___OSGetSystemTime_bl();
  *(longlong *)(&DAT_803d7890 + param_1 * 8) = lVar9;
  uVar5 = *puVar7;
  uVar1 = DAT_804364c0 & ~(0x80000000U >> param_1);
  uVar4 = DAT_804364c0 & 0x80000000U >> param_1;
  DAT_804364c0 = uVar1;
  if (((((param_2 & 0xf) == 0) && ((uVar5 & 0x18000000) == 0x8000000)) &&
      ((uVar5 & 0x80000000) != 0)) && ((uVar5 & 0x4000000) == 0)) {
    uVar2 = gnt4_OSGetWirelessID_bl(param_1);
    uVar1 = (uint)uVar2 << 8;
    if ((uVar4 == 0) || ((uVar1 & 0x100000) == 0)) {
      if ((uVar5 & 0x100000) == 0) {
        if ((uVar5 & 0x40000000) != 0) {
          gnt4_OSSetWirelessID_bl(param_1,(ushort)((uVar5 & 0xcfff00) >> 8) | 0x1000);
          *(uint *)(&DAT_803d7960 + iVar6) = uVar5 & 0xcfff00 | 0x4e100000;
          *puVar7 = 0x80;
          gnt4_SITransfer_bl(param_1,(undefined4 *)(&DAT_803d7960 + iVar6),3,puVar7,3,-0x7fdf5a00,0,
                             0);
          return;
        }
        gnt4_OSSetWirelessID_bl(param_1,0);
      }
      else if ((uVar1 & 0xcfff00) != (uVar5 & 0xcfff00)) {
        if ((uVar1 & 0x100000) == 0) {
          uVar1 = uVar5 & 0xcfff00 | 0x100000;
          gnt4_OSSetWirelessID_bl(param_1,(short)(uVar1 >> 8));
        }
        *(uint *)(&DAT_803d7960 + iVar6) = uVar1 | 0x4e000000;
        *puVar7 = 0x80;
        gnt4_SITransfer_bl(param_1,(undefined4 *)(&DAT_803d7960 + iVar6),3,puVar7,3,-0x7fdf5a00,0,0)
        ;
        return;
      }
      uVar1 = *puVar7;
      iVar6 = 0;
      puVar8 = (undefined4 *)(&DAT_803d78d0 + param_1 * 0x10);
      do {
        pcVar3 = (code *)*puVar8;
        if (pcVar3 != (code *)0x0) {
          *puVar8 = 0;
          (*pcVar3)(param_1,uVar1);
        }
        iVar6 = iVar6 + 1;
        puVar8 = puVar8 + 1;
      } while (iVar6 < 4);
    }
    else {
      *(uint *)(&DAT_803d7960 + iVar6) = uVar1 & 0xcfff00 | 0x4e100000;
      *puVar7 = 0x80;
      gnt4_SITransfer_bl(param_1,(undefined4 *)(&DAT_803d7960 + iVar6),3,puVar7,3,-0x7fdf5a00,0,0);
    }
  }
  else {
    gnt4_OSSetWirelessID_bl(param_1,0);
    uVar1 = *puVar7;
    iVar6 = 0;
    puVar8 = (undefined4 *)(&DAT_803d78d0 + param_1 * 0x10);
    do {
      pcVar3 = (code *)*puVar8;
      if (pcVar3 != (code *)0x0) {
        *puVar8 = 0;
        (*pcVar3)(param_1,uVar1);
      }
      iVar6 = iVar6 + 1;
      puVar8 = puVar8 + 1;
    } while (iVar6 < 4);
  }
  return;
}



// ==== 8020a898  gnt4-SIGetType ====

int gnt4_SIGetType(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  longlong *plVar5;
  longlong lVar6;
  
  gnt4_OSDisableInterrupts_bl();
  piVar4 = (int *)(&DAT_803a4d10 + param_1 * 4);
  iVar3 = *piVar4;
  lVar6 = gnt4___OSGetSystemTime_bl();
  plVar5 = (longlong *)(&DAT_803d7890 + param_1 * 8);
  uVar2 = (uint)lVar6 - *(uint *)(&DAT_803d7894 + param_1 * 8);
  uVar1 = (int)((ulonglong)lVar6 >> 0x20) -
          ((uint)((uint)lVar6 < *(uint *)(&DAT_803d7894 + param_1 * 8)) + *(int *)plVar5);
  if ((DAT_803a4d00 & 0x80 >> (param_1 & 0x3f)) == 0) {
    if (((uint)((DAT_800000f8 / 4000) * 0x32 < uVar2) + (uVar1 ^ 0x80000000) < 0x80000001) &&
       (iVar3 != 8)) {
      gnt4_OSRestoreInterrupts_bl();
      return iVar3;
    }
    if ((uint)((DAT_800000f8 / 4000) * 0x4b < uVar2) + (uVar1 ^ 0x80000000) < 0x80000001) {
      *piVar4 = 0x80;
    }
    else {
      *piVar4 = 0x80;
      iVar3 = 0x80;
    }
  }
  else {
    if (iVar3 != 8) {
      lVar6 = gnt4___OSGetSystemTime_bl();
      *plVar5 = lVar6;
      gnt4_OSRestoreInterrupts_bl();
      return iVar3;
    }
    *piVar4 = 0x80;
    iVar3 = 0x80;
  }
  lVar6 = gnt4___OSGetSystemTime_bl();
  *plVar5 = lVar6;
  gnt4_SITransfer_bl(param_1,(undefined4 *)&DAT_804364bc,1,piVar4,3,-0x7fdf5a00,0,
                     (DAT_800000f8 / 500000) * 0x41 >> 3);
  gnt4_OSRestoreInterrupts_bl();
  return iVar3;
}



// ==== 8020aa5c  gnt4-SIGetTypeAsync ====

int gnt4_SIGetTypeAsync(uint param_1,undefined *param_2)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  gnt4_OSDisableInterrupts_bl();
  iVar3 = gnt4_SIGetType(param_1);
  if ((*(uint *)(&DAT_803a4d10 + param_1 * 4) & 0x80) == 0) {
    (*(code *)param_2)(param_1,iVar3);
  }
  else {
    iVar1 = param_1 * 0x10;
    puVar2 = *(undefined **)(&DAT_803d78d0 + iVar1);
    if (puVar2 != param_2) {
      if (puVar2 == (undefined *)0x0) {
        *(undefined **)(&DAT_803d78d0 + iVar1) = param_2;
      }
      else if (*(undefined **)(&DAT_803d78d4 + iVar1) != param_2) {
        if (*(undefined **)(&DAT_803d78d4 + iVar1) == (undefined *)0x0) {
          *(undefined **)(&DAT_803d78d4 + iVar1) = param_2;
        }
        else if (*(undefined **)(&DAT_803d78d8 + iVar1) != param_2) {
          if (*(undefined **)(&DAT_803d78d8 + iVar1) == (undefined *)0x0) {
            *(undefined **)(&DAT_803d78d8 + iVar1) = param_2;
          }
          else if ((*(undefined **)(&DAT_803d78dc + iVar1) != param_2) &&
                  (*(undefined **)(&DAT_803d78dc + iVar1) == (undefined *)0x0)) {
            *(undefined **)(&DAT_803d78dc + iVar1) = param_2;
          }
        }
      }
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar3;
}



