// ==== 8022e11c  TRKDoWriteRegisters ====

/* WARNING: Removing unreachable block (ram,0x8022e1b8) */
/* WARNING: Type propagation algorithm not settling */

undefined4 TRKDoWriteRegisters(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined1 uVar5;
  int aiStack_d8 [2];
  undefined1 local_d0;
  undefined1 local_cc;
  undefined4 local_94;
  undefined1 local_90;
  undefined1 local_8c;
  undefined4 local_54;
  undefined1 local_50;
  undefined1 local_4c;
  
  bVar1 = *(byte *)(param_1 + 0x18);
  uVar4 = (uint)*(ushort *)(param_1 + 0x1c);
  uVar3 = (uint)*(ushort *)(param_1 + 0x20);
  TRKSetBufferPosition(param_1,0);
  if (uVar3 < uVar4) {
    gnt4_memset(&local_94,0,0x40);
    local_90 = 0x80;
    local_94 = 0x40;
    local_8c = 0x14;
    zz_0231858_();
    return 0;
  }
  TRKSetBufferPosition(param_1,0x40);
  if (bVar1 == 2) {
    uVar3 = TRKTargetAccessExtended1(uVar4,uVar3,param_1,aiStack_d8,0);
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      uVar3 = TRKTargetAccessDefault(uVar4,uVar3,param_1,aiStack_d8,0);
    }
    else {
      uVar3 = zz_02305e4_(uVar4,uVar3,param_1,aiStack_d8,0);
    }
  }
  else if (bVar1 < 4) {
    uVar3 = TRKTargetAccessExtended2(uVar4,uVar3,param_1,aiStack_d8,0);
  }
  else {
    uVar3 = 0x703;
  }
  TRKResetBuffer(param_1,0);
  if (uVar3 == 0) {
    gnt4_memset(&local_54,0,0x40);
    local_54 = 0x40;
    local_50 = 0x80;
    local_4c = 0;
    uVar3 = TRKAppendBuffer(param_1,(undefined1 *)&local_54,0x40);
  }
  if (uVar3 == 0) {
    zz_02327c8_();
    uVar2 = TRKMessageSend();
    zz_02327c8_();
    return uVar2;
  }
  if (uVar3 == 0x703) {
    uVar5 = 0x12;
    goto LAB_8022e318;
  }
  if ((int)uVar3 < 0x703) {
    if (uVar3 == 0x701) {
      uVar5 = 0x14;
      goto LAB_8022e318;
    }
    if (0x700 < (int)uVar3) {
      uVar5 = 0x15;
      goto LAB_8022e318;
    }
    if (uVar3 == 0x302) {
      uVar5 = 2;
      goto LAB_8022e318;
    }
  }
  else {
    if (uVar3 == 0x706) {
      uVar5 = 0x20;
      goto LAB_8022e318;
    }
    if ((int)uVar3 < 0x706) {
      if ((int)uVar3 < 0x705) {
        uVar5 = 0x21;
      }
      else {
        uVar5 = 0x22;
      }
      goto LAB_8022e318;
    }
  }
  uVar5 = 3;
LAB_8022e318:
  gnt4_memset(aiStack_d8 + 1,0,0x40);
  local_d0 = 0x80;
  aiStack_d8[1] = 0x40;
  local_cc = uVar5;
  zz_0231858_();
  return 0;
}



// ==== 8022e3ac  TRKDoReadRegisters ====

/* WARNING: Type propagation algorithm not settling */

undefined4 TRKDoReadRegisters(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  int aiStack_d8 [2];
  undefined1 local_d0;
  undefined1 local_cc;
  undefined4 local_94;
  undefined1 local_90;
  undefined1 local_8c;
  undefined4 local_54;
  undefined1 local_50;
  
  if (*(ushort *)(param_1 + 0x20) < *(ushort *)(param_1 + 0x1c)) {
    gnt4_memset(&local_94,0,0x40);
    local_90 = 0x80;
    local_94 = 0x40;
    local_8c = 0x14;
    zz_0231858_();
    return 0;
  }
  local_50 = 0x80;
  local_54 = 0x468;
  TRKResetBuffer(param_1,0);
  zz_02327c8_();
  TRKAppendBuffer_ui8(param_1,(undefined1 *)&local_54,0x40);
  zz_02327c8_();
  uVar1 = TRKTargetAccessDefault(0,0x24,param_1,aiStack_d8,1);
  zz_02327c8_();
  zz_02327c8_();
  if (uVar1 == 0) {
    uVar1 = zz_02305e4_(0,0x21,param_1,aiStack_d8,1);
  }
  zz_02327c8_();
  zz_02327c8_();
  if (uVar1 == 0) {
    uVar1 = TRKTargetAccessExtended1(0,0x60,param_1,aiStack_d8,1);
  }
  zz_02327c8_();
  zz_02327c8_();
  if (uVar1 == 0) {
    uVar1 = TRKTargetAccessExtended2(0,0x1f,param_1,aiStack_d8,1);
  }
  zz_02327c8_();
  zz_02327c8_();
  if (uVar1 == 0) {
    zz_02327c8_();
    uVar2 = TRKMessageSend();
    zz_02327c8_();
    return uVar2;
  }
  if (uVar1 == 0x704) {
    uVar3 = 0x21;
    goto LAB_8022e604;
  }
  if ((int)uVar1 < 0x704) {
    if (uVar1 == 0x702) {
      uVar3 = 0x15;
      goto LAB_8022e604;
    }
    if (0x701 < (int)uVar1) {
      uVar3 = 0x12;
      goto LAB_8022e604;
    }
    if (0x700 < (int)uVar1) {
      uVar3 = 0x14;
      goto LAB_8022e604;
    }
  }
  else {
    if (uVar1 == 0x706) {
      uVar3 = 0x20;
      goto LAB_8022e604;
    }
    if ((int)uVar1 < 0x706) {
      uVar3 = 0x22;
      goto LAB_8022e604;
    }
  }
  uVar3 = 3;
LAB_8022e604:
  gnt4_memset(aiStack_d8 + 1,0,0x40);
  local_d0 = 0x80;
  aiStack_d8[1] = 0x40;
  local_cc = uVar3;
  zz_0231858_();
  return 0;
}



// ==== 8022e68c  zz_022e68c_ ====

/* WARNING: Type propagation algorithm not settling */

undefined4 zz_022e68c_(int param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 uVar6;
  uint local_8e8 [2];
  undefined1 local_8e0;
  undefined1 local_8dc;
  undefined4 local_8a4;
  undefined1 local_8a0;
  undefined1 local_89c;
  undefined4 local_864;
  undefined1 local_860;
  undefined1 local_85c;
  undefined1 auStack_824 [2064];
  
  uVar5 = *(uint *)(param_1 + 0x20);
  uVar2 = *(ushort *)(param_1 + 0x1c);
  bVar1 = *(byte *)(param_1 + 0x18);
  zz_02327c8_();
  if ((bVar1 & 2) == 0) {
    local_8e8[0] = (uint)uVar2;
    TRKSetBufferPosition(param_1,0x40);
    TRKReadBuffer(param_1,(int)auStack_824,local_8e8[0]);
    iVar4 = TRKTargetAccessMemory((int)auStack_824,uVar5,(int *)local_8e8,bVar1 >> 3 & 1 ^ 1,0);
    TRKResetBuffer(param_1,0);
    if (iVar4 == 0) {
      gnt4_memset(&local_864,0,0x40);
      local_864 = 0x40;
      local_860 = 0x80;
      local_85c = 0;
      iVar4 = TRKAppendBuffer(param_1,(undefined1 *)&local_864,0x40);
    }
    if (iVar4 == 0) {
      zz_02327c8_();
      uVar3 = TRKMessageSend();
      zz_02327c8_();
    }
    else {
      switch(iVar4) {
      case 0x700:
        uVar6 = 0x13;
        break;
      default:
        uVar6 = 3;
        break;
      case 0x702:
        uVar6 = 0x15;
        break;
      case 0x704:
        uVar6 = 0x21;
        break;
      case 0x705:
        uVar6 = 0x22;
        break;
      case 0x706:
        uVar6 = 0x20;
      }
      gnt4_memset(local_8e8 + 1,0,0x40);
      local_8e0 = 0x80;
      local_8e8[1] = 0x40;
      local_8dc = uVar6;
      zz_0231858_();
      uVar3 = 0;
    }
  }
  else {
    gnt4_memset(&local_8a4,0,0x40);
    local_8a0 = 0x80;
    local_8a4 = 0x40;
    local_89c = 0x12;
    zz_0231858_();
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 8022e880  zz_022e880_ ====

/* WARNING: Type propagation algorithm not settling */

undefined4 zz_022e880_(int param_1)

{
  byte bVar1;
  ushort uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined1 uVar6;
  uint local_8e8 [2];
  undefined1 local_8e0;
  undefined1 local_8dc;
  undefined4 local_8a4;
  undefined1 local_8a0;
  undefined1 local_89c;
  int local_864;
  undefined1 local_860;
  undefined1 local_85c;
  undefined1 auStack_824 [2064];
  
  uVar5 = *(uint *)(param_1 + 0x20);
  uVar2 = *(ushort *)(param_1 + 0x1c);
  bVar1 = *(byte *)(param_1 + 0x18);
  zz_02327c8_();
  if ((bVar1 & 2) == 0) {
    local_8e8[0] = (uint)uVar2;
    iVar4 = TRKTargetAccessMemory((int)auStack_824,uVar5,(int *)local_8e8,bVar1 >> 3 & 1 ^ 1,1);
    TRKResetBuffer(param_1,0);
    if (iVar4 == 0) {
      gnt4_memset(&local_864,0,0x40);
      local_85c = 0;
      local_864 = local_8e8[0] + 0x40;
      local_860 = 0x80;
      TRKAppendBuffer(param_1,(undefined1 *)&local_864,0x40);
      iVar4 = TRKAppendBuffer(param_1,auStack_824,local_8e8[0]);
    }
    if (iVar4 == 0) {
      zz_02327c8_();
      uVar3 = TRKMessageSend();
      zz_02327c8_();
    }
    else {
      switch(iVar4) {
      case 0x700:
        uVar6 = 0x13;
        break;
      default:
        uVar6 = 3;
        break;
      case 0x702:
        uVar6 = 0x15;
        break;
      case 0x704:
        uVar6 = 0x21;
        break;
      case 0x705:
        uVar6 = 0x22;
        break;
      case 0x706:
        uVar6 = 0x20;
      }
      gnt4_memset(local_8e8 + 1,0,0x40);
      local_8e0 = 0x80;
      local_8e8[1] = 0x40;
      local_8dc = uVar6;
      zz_0231858_();
      uVar3 = 0;
    }
  }
  else {
    gnt4_memset(&local_8a4,0,0x40);
    local_8a0 = 0x80;
    local_8a4 = 0x40;
    local_89c = 0x12;
    zz_0231858_();
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 8022ea6c  zz_022ea6c_ ====

undefined4 zz_022ea6c_(void)

{
  return 0;
}



// ==== 8022ea74  zz_022ea74_ ====

undefined4 zz_022ea74_(void)

{
  return 0;
}



// ==== 8022ea7c  TRKDoOverride ====

undefined4 TRKDoOverride(void)

{
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  gnt4_memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  zz_0231858_();
  __TRK_copy_vectors();
  return 0;
}



// ==== 8022ead4  zz_022ead4_ ====

undefined4
zz_022ead4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  gnt4_memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  zz_0231858_();
  __TRK_reset(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return 0;
}



// ==== 8022eb2c  TRKDoDisconnect ====

undefined4 TRKDoDisconnect(void)

{
  undefined4 auStack_58 [3];
  undefined4 local_4c;
  undefined1 local_48;
  undefined1 local_44;
  
  DAT_803f75d0 = 0;
  gnt4_memset(&local_4c,0,0x40);
  local_48 = 0x80;
  local_4c = 0x40;
  local_44 = 0;
  zz_0231858_();
  TRKConstructEvent(auStack_58,1);
  TRKPostEvent((int)auStack_58);
  return 0;
}



// ==== 8022eba4  TRKDoConnect ====

undefined4 TRKDoConnect(void)

{
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_40;
  
  DAT_803f75d0 = 1;
  gnt4_memset(&local_48,0,0x40);
  local_44 = 0x80;
  local_48 = 0x40;
  local_40 = 0;
  zz_0231858_();
  return 0;
}



// ==== 8022ec08  zz_022ec08_ ====

void zz_022ec08_(undefined4 param_1)

{
  DAT_803f75d0 = param_1;
  return;
}



// ==== 8022ec14  zz_022ec14_ ====

undefined4 zz_022ec14_(void)

{
  return DAT_803f75d0;
}



// ==== 8022ec24  OutputData ====

void OutputData(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    zz_02327c8_();
    iVar1 = iVar2 >> 0x1f;
    if ((iVar1 * 0x10 | (uint)(iVar2 * 0x10000000 + iVar1) >> 0x1c) - iVar1 == 0xf) {
      zz_02327c8_();
    }
  }
  zz_02327c8_();
  return;
}



// ==== 8022eccc  HandlePositionFileSupportRequest ====

/* WARNING: Type propagation algorithm not settling */

int HandlePositionFileSupportRequest
              (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
              undefined4 param_9,undefined4 *param_10,undefined1 param_11,undefined4 *param_12,
              undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int local_68;
  int local_64;
  int local_60 [2];
  undefined1 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined1 local_4c;
  
  uVar3 = 0x40;
  puVar4 = param_12;
  gnt4_memset(local_60 + 1,0,0x40);
  local_58 = 0xd4;
  local_60[1] = 0x40;
  local_50 = *param_10;
  local_54 = param_9;
  local_4c = param_11;
  iVar1 = TRKGetFreeBuffer(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_64
                           ,&local_68,uVar3,puVar4,param_13,param_14,param_15,param_16);
  if (iVar1 == 0) {
    iVar1 = TRKAppendBuffer_ui8(local_68,(undefined1 *)(local_60 + 1),0x40);
  }
  if (iVar1 == 0) {
    *param_12 = 0;
    *param_10 = 0xffffffff;
    iVar1 = TRKRequestSend(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_68,
                           local_60,3,3,0,param_14,param_15,param_16);
    if ((iVar1 == 0) && (puVar2 = TRKGetBuffer(local_60[0]), puVar2 != (undefined *)0x0)) {
      *param_12 = *(undefined4 *)(puVar2 + 0x20);
      *param_10 = *(undefined4 *)(puVar2 + 0x28);
    }
    TRKReleaseBuffer(local_60[0]);
  }
  TRKReleaseBuffer(local_64);
  return iVar1;
}



// ==== 8022eddc  HandleCloseFileSupportRequest ====

int HandleCloseFileSupportRequest
              (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
              undefined4 param_9,undefined4 *param_10,undefined4 param_11,undefined4 param_12,
              undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined1 local_58;
  undefined4 local_54;
  
  uVar3 = 0x40;
  gnt4_memset(&local_5c,0,0x40);
  local_58 = 0xd3;
  local_5c = 0x40;
  local_54 = param_9;
  iVar1 = TRKGetFreeBuffer(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_64
                           ,&local_68,uVar3,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 == 0) {
    iVar1 = TRKAppendBuffer_ui8(local_68,(undefined1 *)&local_5c,0x40);
  }
  if (iVar1 == 0) {
    *param_10 = 0;
    iVar1 = TRKRequestSend(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_68,
                           &local_60,3,3,0,param_14,param_15,param_16);
    if (iVar1 == 0) {
      puVar2 = TRKGetBuffer(local_60);
      *param_10 = *(undefined4 *)(puVar2 + 0x20);
    }
    TRKReleaseBuffer(local_60);
  }
  TRKReleaseBuffer(local_64);
  return iVar1;
}



// ==== 8022eec4  HandleOpenFileSupportRequest ====

int HandleOpenFileSupportRequest
              (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
              char *param_9,undefined1 param_10,undefined4 *param_11,undefined4 *param_12,
              undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  size_t sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined *unaff_r30;
  int local_68;
  int local_64;
  int local_60;
  int local_5c;
  undefined1 local_58;
  undefined1 local_54;
  short local_50;
  
  uVar3 = 0x40;
  puVar4 = param_12;
  gnt4_memset(&local_5c,0,0x40);
  *param_11 = 0;
  local_58 = 0xd2;
  sVar1 = strlen(param_9);
  local_5c = sVar1 + 0x41;
  local_54 = param_10;
  sVar1 = strlen(param_9);
  local_50 = (short)sVar1 + 1;
  TRKGetFreeBuffer(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_64,
                   &local_68,uVar3,puVar4,param_13,param_14,param_15,param_16);
  iVar2 = TRKAppendBuffer_ui8(local_68,(undefined1 *)&local_5c,0x40);
  if (iVar2 == 0) {
    sVar1 = strlen(param_9);
    iVar2 = TRKAppendBuffer_ui8(local_68,param_9,sVar1 + 1);
  }
  if (iVar2 == 0) {
    *param_12 = 0;
    iVar2 = TRKRequestSend(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_68,
                           &local_60,7,3,0,param_14,param_15,param_16);
    if (iVar2 == 0) {
      unaff_r30 = TRKGetBuffer(local_60);
    }
    *param_12 = *(undefined4 *)(unaff_r30 + 0x20);
    *param_11 = *(undefined4 *)(unaff_r30 + 0x18);
    TRKReleaseBuffer(local_60);
  }
  TRKReleaseBuffer(local_64);
  return iVar2;
}



// ==== 8022efe0  TRKRequestSend ====

int TRKRequestSend(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                  undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                  undefined4 param_9,int *param_10,uint param_11,uint param_12,int param_13,
                  undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint extraout_r4;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint unaff_r26;
  int iVar6;
  uint unaff_r28;
  undefined *unaff_r29;
  int iVar7;
  undefined8 uVar8;
  undefined8 extraout_f1;
  ulonglong uVar9;
  
  iVar6 = param_12 + 1;
  iVar7 = 0;
  bVar1 = true;
  *param_10 = -1;
  iVar4 = param_13;
LAB_8022f17c:
  if (((iVar6 == 0) || (*param_10 != -1)) || (iVar7 != 0)) {
    if (*param_10 == -1) {
      iVar7 = 0x800;
    }
    return iVar7;
  }
  uVar8 = zz_02327c8_();
  uVar5 = extraout_r4;
  iVar7 = TRKMessageSend();
  if (iVar7 == 0) {
    uVar9 = (ulonglong)uVar5;
    if (param_13 != 0) {
      unaff_r28 = 0;
      uVar9 = (ulonglong)uVar5;
    }
LAB_8022f048:
    uVar3 = (undefined4)uVar9;
    iVar2 = TRKTestForPacket(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (int)(uVar9 >> 0x20),uVar3,param_11,param_12,iVar4,param_14,param_15,
                             param_16);
    *param_10 = iVar2;
    iVar2 = *param_10;
    if (iVar2 == -1) goto code_r0x8022f05c;
    goto LAB_8022f078;
  }
  goto LAB_8022f178;
code_r0x8022f05c:
  uVar9 = CONCAT44(0xffffffff,uVar3);
  if (param_13 == 0) goto LAB_8022f048;
  uVar9 = 0xffffffff04c50000;
  unaff_r28 = unaff_r28 + 1;
  if (unaff_r28 < 0x4c4b3ec) goto LAB_8022f048;
LAB_8022f078:
  if (iVar2 != -1) {
    bVar1 = false;
    unaff_r29 = TRKGetBuffer(iVar2);
    TRKSetBufferPosition((int)unaff_r29,0);
    OutputData(unaff_r29 + 0x10,*(int *)(unaff_r29 + 8));
    unaff_r26 = (uint)(byte)unaff_r29[0x14];
    param_11 = unaff_r26;
    param_12 = unaff_r26;
    zz_02327c8_();
    if (0x7f < unaff_r26) goto LAB_8022f0d8;
    uVar9 = TRKProcessInput(*param_10);
    *param_10 = -1;
    uVar8 = extraout_f1;
    goto LAB_8022f048;
  }
LAB_8022f0d8:
  if (*param_10 != -1) {
    if (*(uint *)(unaff_r29 + 8) < 0x40) {
      bVar1 = true;
    }
    if (!bVar1) {
      uVar5 = (uint)(byte)unaff_r29[0x18];
      zz_02327c8_();
      param_11 = unaff_r26;
      if ((unaff_r26 != 0x80) || (uVar5 != 0)) {
        zz_02327c8_();
        bVar1 = true;
        param_12 = uVar5;
      }
    }
    if (bVar1) {
      TRKReleaseBuffer(*param_10);
      *param_10 = -1;
    }
  }
LAB_8022f178:
  iVar6 = iVar6 + -1;
  goto LAB_8022f17c;
}



// ==== 8022f1c0  zz_022f1c0_ ====

int zz_022f1c0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,int param_10,uint *param_11,uint *param_12,uint param_13,int param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  undefined *unaff_r22;
  uint uVar10;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  undefined1 local_78;
  int local_74;
  undefined2 local_70;
  
  if ((param_10 == 0) || (*param_11 == 0)) {
    iVar3 = 2;
  }
  else {
    bVar1 = false;
    *param_12 = 0;
    uVar10 = 0;
    iVar3 = 0;
    puVar6 = param_12;
    uVar2 = param_13;
    iVar7 = param_14;
    while ((((!bVar1 && (uVar10 < *param_11)) && (iVar3 == 0)) && (*param_12 == 0))) {
      uVar5 = 0x40;
      gnt4_memset(&local_7c,0,0x40);
      uVar4 = 0x800;
      if (*param_11 - uVar10 < 0x801) {
        uVar4 = *param_11 - uVar10;
      }
      local_78 = 0xd0;
      if (param_14 != 0) {
        local_78 = 0xd1;
      }
      local_7c = 0x40;
      if (param_14 == 0) {
        local_7c = uVar4 + 0x40;
      }
      local_70 = (undefined2)uVar4;
      local_74 = param_9;
      TRKGetFreeBuffer(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_84,
                       &local_88,uVar5,puVar6,uVar2,iVar7,param_15,param_16);
      iVar3 = TRKAppendBuffer_ui8(local_88,(undefined1 *)&local_7c,0x40);
      if ((param_14 == 0) && (iVar3 == 0)) {
        iVar3 = TRKAppendBuffer_ui8(local_88,(undefined1 *)(param_10 + uVar10),uVar4);
      }
      if (iVar3 == 0) {
        if (param_13 == 0) {
          iVar3 = TRKMessageSend();
        }
        else {
          uVar5 = 0;
          if ((param_14 != 0) && (param_9 == 0)) {
            uVar5 = 1;
          }
          uVar2 = countLeadingZeros(uVar5);
          puVar6 = (uint *)0x3;
          uVar2 = uVar2 >> 5;
          iVar3 = TRKRequestSend(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 local_88,&local_80,5,3,uVar2,iVar7,param_15,param_16);
          if (iVar3 == 0) {
            unaff_r22 = TRKGetBuffer(local_80);
          }
          uVar8 = (uint)*(ushort *)(unaff_r22 + 0x24);
          uVar9 = *(uint *)(unaff_r22 + 0x20) & 0xff;
          if (((param_14 != 0) && (iVar3 == 0)) && (uVar8 <= uVar4)) {
            TRKSetBufferPosition((int)unaff_r22,0x40);
            iVar3 = TRKReadBuffer_ui8((int)unaff_r22,param_10 + uVar10,uVar8);
            if (iVar3 == 0x302) {
              iVar3 = 0;
            }
          }
          if (uVar8 != uVar4) {
            if (((param_14 == 0) || (uVar4 <= uVar8)) && (uVar9 == 0)) {
              uVar9 = 1;
            }
            bVar1 = true;
            uVar4 = uVar8;
          }
          *param_12 = uVar9;
          TRKReleaseBuffer(local_80);
        }
      }
      param_1 = TRKReleaseBuffer(local_84);
      uVar10 = uVar10 + uVar4;
    }
    *param_11 = uVar10;
  }
  return iVar3;
}



// ==== 8022f400  zz_022f400_ ====

undefined4 zz_022f400_(void)

{
  return 0;
}



// ==== 8022f408  zz_022f408_ ====

undefined4 zz_022f408_(void)

{
  return 0;
}



// ==== 8022f410  zz_022f410_ ====

undefined4 zz_022f410_(void)

{
  return 0;
}



// ==== 8022f418  TRKDoNotifyStopped ====

int TRKDoNotifyStopped(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                      undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                      int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                      undefined4 param_13,undefined4 param_14,undefined4 param_15,
                      undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  int local_18;
  int local_14;
  int local_10 [2];
  
  iVar1 = TRKGetFreeBuffer(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_14
                           ,&local_18,param_11,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 == 0) {
    if (param_9 == 0x90) {
      uVar2 = TRKTargetAddStopInfo(local_18);
    }
    else {
      uVar2 = TRKTargetAddExceptionInfo(local_18);
    }
    iVar1 = TRKRequestSend(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_18,
                           local_10,2,3,1,param_14,param_15,param_16);
    if (iVar1 == 0) {
      TRKReleaseBuffer(local_10[0]);
    }
    TRKReleaseBuffer(local_14);
  }
  return iVar1;
}



// ==== 8022f4b0  TRK_flush_cache ====

void TRK_flush_cache(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 & 0xfffffff1;
  iVar1 = param_2 + (param_1 - uVar2);
  do {
    dataCacheBlockStore(uVar2);
    dataCacheBlockFlush(uVar2);
    sync(0);
    instructionCacheBlockInvalidate(uVar2);
    uVar2 = uVar2 + 8;
    iVar1 = iVar1 + -8;
  } while (-1 < iVar1);
  instructionSynchronize();
  return;
}



// ==== 8022f4e8  TRK_fill_mem ====

void TRK_fill_mem(int param_1,byte param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  byte *pbVar3;
  uint uVar4;
  
  uVar4 = (uint)param_2;
  pbVar3 = (byte *)(param_1 + -1);
  if (0x1f < param_3) {
    uVar1 = ~(uint)pbVar3 & 3;
    if (uVar1 != 0) {
      param_3 = param_3 - uVar1;
      do {
        uVar1 = uVar1 - 1;
        pbVar3 = pbVar3 + 1;
        *pbVar3 = param_2;
      } while (uVar1 != 0);
    }
    if (param_2 != 0) {
      uVar4 = uVar4 | uVar4 << 8 | (uint)param_2 << 0x18 | uVar4 << 0x10;
    }
    puVar2 = (uint *)(pbVar3 + -3);
    for (uVar1 = param_3 >> 5; uVar1 != 0; uVar1 = uVar1 - 1) {
      puVar2[1] = uVar4;
      puVar2[2] = uVar4;
      puVar2[3] = uVar4;
      puVar2[4] = uVar4;
      puVar2[5] = uVar4;
      puVar2[6] = uVar4;
      puVar2[7] = uVar4;
      puVar2 = puVar2 + 8;
      *puVar2 = uVar4;
    }
    for (uVar1 = param_3 >> 2 & 7; uVar1 != 0; uVar1 = uVar1 - 1) {
      puVar2 = puVar2 + 1;
      *puVar2 = uVar4;
    }
    pbVar3 = (byte *)((int)puVar2 + 3);
    param_3 = param_3 & 3;
  }
  if (param_3 != 0) {
    do {
      param_3 = param_3 - 1;
      pbVar3 = pbVar3 + 1;
      *pbVar3 = (byte)uVar4;
    } while (param_3 != 0);
    return;
  }
  return;
}



// ==== 8022f5a0  zz_022f5a0_ ====

void zz_022f5a0_(void)

{
  return;
}



// ==== 8022f5a8  zz_022f5a8_ ====

void zz_022f5a8_(void)

{
  return;
}



// ==== 8022f5b0  TRK_ppc_memcpy ====

void TRK_ppc_memcpy(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 != param_3; iVar1 = iVar1 + 1) {
    sync(0);
    sync(0);
    *(undefined1 *)(iVar1 + param_1) = *(undefined1 *)(iVar1 + param_2);
  }
  sync(0);
  return;
}



// ==== 8022f81c  TRKPostInterruptEvent ====

/* WARNING: This function may have set the stack pointer */

undefined4
TRKPostInterruptEvent
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
  undefined4 uVar1;
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
  uint in_MSR;
  uint uVar2;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined4 in_DSISR;
  undefined4 in_DAR;
  undefined4 in_SRR1;
  
  DAT_803f75e4 = &DAT_8043ea20;
  DAT_803f75e8 = &DAT_803f75dc;
  DAT_803f7610 = &FLOAT_8043b5a0;
  uVar2 = in_MSR & 0x9000;
  DAT_803f75dc = in_r0;
  DAT_803f75e0 = (undefined1 *)register0x00000004;
  DAT_803f75ec = param_2;
  DAT_803f75f0 = param_3;
  DAT_803f75f4 = param_4;
  DAT_803f75f8 = param_5;
  DAT_803f75fc = param_6;
  DAT_803f7600 = param_7;
  DAT_803f7604 = param_8;
  DAT_803f7608 = in_r11;
  DAT_803f760c = in_r12;
  DAT_803f7614 = unaff_r14;
  DAT_803f7618 = unaff_r15;
  DAT_803f761c = unaff_r16;
  DAT_803f7620 = unaff_r17;
  DAT_803f7624 = unaff_r18;
  DAT_803f7628 = unaff_r19;
  DAT_803f762c = unaff_r20;
  DAT_803f7630 = unaff_r21;
  DAT_803f7634 = unaff_r22;
  DAT_803f7638 = unaff_r23;
  DAT_803f763c = unaff_r24;
  DAT_803f7640 = unaff_r25;
  DAT_803f7644 = unaff_r26;
  DAT_803f7648 = unaff_r27;
  DAT_803f764c = unaff_r28;
  DAT_803f7650 = unaff_r29;
  DAT_803f7654 = unaff_r30;
  DAT_803f7658 = unaff_r31;
  DAT_803f765c = in_LR;
  DAT_803f7660 = in_CTR;
  DAT_803f7664 = in_XER;
  DAT_803f7668 = in_MSR;
  DAT_803f766c = in_DAR;
  DAT_803f7670 = in_DSISR;
  if (*DAT_803f767c != '\0') {
    DAT_803f7678 = 1;
    sync(0);
    sync(0);
    uVar1 = FUN_8022ff90();
    return uVar1;
  }
  DAT_803ab288._0_1_ = 0;
  TRKRestoreExtended1Block();
  returnFromInterrupt(uVar2,in_SRR1);
  return DAT_803f768c;
}



// ==== 8022f934  zz_022f934_ ====

void zz_022f934_(undefined4 param_1)

{
  DAT_803f767c = param_1;
  return;
}



// ==== 8022f944  TRKTargetStop ====

undefined4 TRKTargetStop(void)

{
  DAT_803f7674 = 1;
  return 0;
}



// ==== 8022f95c  TRKTargetSetInputPendingPtr ====

void TRKTargetSetInputPendingPtr(undefined4 param_1)

{
  DAT_803f7674 = param_1;
  return;
}



// ==== 8022f96c  zz_022f96c_ ====

undefined4 zz_022f96c_(void)

{
  return DAT_803f7674;
}



// ==== 8022f97c  TRKTargetSupportRequest ====

int TRKTargetSupportRequest
              (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
              undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
              undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
              undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint *puVar2;
  uint uVar3;
  int iVar4;
  uint local_38;
  uint local_34;
  undefined4 auStack_30 [7];
  
  puVar2 = DAT_803f7694;
  uVar1 = DAT_803f768c;
  if ((((DAT_803f768c == 0xd1) || (DAT_803f768c == 0xd0)) || (DAT_803f768c == 0xd2)) ||
     ((DAT_803f768c == 0xd3 || (DAT_803f768c == 0xd4)))) {
    if (DAT_803f768c == 0xd2) {
      iVar4 = HandleOpenFileSupportRequest
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_803f7690,(char)DAT_803f7694,DAT_803f7698,&local_34,param_13,param_14,
                         param_15,param_16);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_803f768c = local_34;
    }
    else if (DAT_803f768c == 0xd3) {
      iVar4 = HandleCloseFileSupportRequest
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_803f7690,&local_34,param_11,param_12,param_13,param_14,param_15,
                         param_16);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_803f768c = local_34;
    }
    else if (DAT_803f768c == 0xd4) {
      local_38 = *DAT_803f7694;
      iVar4 = HandlePositionFileSupportRequest
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_803f7690,&local_38,(char)DAT_803f7698,&local_34,local_38,param_14,
                         param_15,param_16);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_803f768c = local_34;
      *DAT_803f7694 = local_38;
    }
    else {
      uVar3 = countLeadingZeros(0xd1 - DAT_803f768c);
      iVar4 = zz_022f1c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int)DAT_803f7690,(int)DAT_803f7698,DAT_803f7694,&local_34,1,uVar3 >> 5,
                          param_15,param_16);
      if ((local_34 == 0) && (iVar4 != 0)) {
        local_34 = 1;
      }
      DAT_803f768c = local_34;
      if (uVar1 == 0xd1) {
        TRK_flush_cache((uint)DAT_803f7698,*puVar2);
      }
    }
    DAT_803f7700 = DAT_803f7700 + 4;
  }
  else {
    TRKConstructEvent(auStack_30,4);
    TRKPostEvent((int)auStack_30);
    iVar4 = 0;
  }
  return iVar4;
}



// ==== 8022fb7c  zz_022fb7c_ ====

undefined4 zz_022fb7c_(void)

{
  return DAT_803f7700;
}



// ==== 8022fb8c  TRKTargetStepOutOfRange ====

undefined4 TRKTargetStepOutOfRange(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_3 == 0) {
    DAT_803ab290 = 1;
    DAT_803ab28c = 1;
    DAT_803ab298 = param_1;
    DAT_803ab29c = param_2;
    zz_02327c8_();
    DAT_803f7878 = DAT_803f7878 | 0x400;
    if ((DAT_803ab290 == 0) || (DAT_803ab290 == 0x10)) {
      DAT_803ab294 = DAT_803ab294 + -1;
    }
    uVar1 = 0;
    DAT_803f7674 = 0;
  }
  else {
    uVar1 = 0x703;
  }
  return uVar1;
}



// ==== 8022fc44  TRKTargetSingleStep ====

undefined4 TRKTargetSingleStep(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    DAT_803ab290 = 0;
    DAT_803ab28c = 1;
    DAT_803ab294 = param_1;
    zz_02327c8_();
    DAT_803f7878 = DAT_803f7878 | 0x400;
    if ((DAT_803ab290 == 0) || (DAT_803ab290 == 0x10)) {
      DAT_803ab294 = DAT_803ab294 + -1;
    }
    uVar1 = 0;
    DAT_803f7674 = 0;
  }
  else {
    uVar1 = 0x703;
  }
  return uVar1;
}



// ==== 8022fcf0  TRKTargetAddExceptionInfo ====

void TRKTargetAddExceptionInfo(int param_1)

{
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_50;
  uint local_4c;
  undefined4 local_48;
  uint local_44;
  
  gnt4_memset(&local_54,0,0x40);
  local_54 = 0x40;
  local_50 = 0x91;
  local_4c = DAT_803ab27c;
  TRKTargetReadInstruction((int)&local_58,DAT_803ab27c);
  local_44 = (uint)DAT_803ab284._0_2_;
  local_48 = local_58;
  TRKAppendBuffer_ui8(param_1,(undefined1 *)&local_54,0x40);
  return;
}



// ==== 8022fd74  TRKTargetAddStopInfo ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void TRKTargetAddStopInfo(int param_1)

{
  undefined4 local_58;
  undefined4 local_54;
  undefined1 local_50;
  uint local_4c;
  undefined4 local_48;
  uint local_44;
  
  gnt4_memset(&local_54,0,0x40);
  local_54 = 0x40;
  local_50 = 0x90;
  local_4c = DAT_803f7700;
  TRKTargetReadInstruction((int)&local_58,DAT_803f7700);
  local_48 = local_58;
  local_44 = _DAT_803f7978 & 0xffff;
  TRKAppendBuffer_ui8(param_1,(undefined1 *)&local_54,0x40);
  return;
}



// ==== 8022fe00  TRKTargetInterrupt ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int TRKTargetInterrupt(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                      undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                      int *param_9,undefined4 param_10,undefined4 *param_11,undefined4 param_12,
                      undefined4 param_13,undefined4 param_14,undefined4 param_15,
                      undefined4 param_16)

{
  int iVar1;
  
  iVar1 = 0;
  if ((*param_9 < 5) && (2 < *param_9)) {
    if (DAT_803ab28c != 0) {
      param_11 = (undefined4 *)0x1;
      DAT_803f7878 = DAT_803f7878 & 0xfffffbff;
      if ((_DAT_803f7978 & 0xffff) == 0xd00) {
        if (DAT_803ab290 == 1) {
          if ((DAT_803ab298 <= DAT_803f7700) && (DAT_803f7700 <= DAT_803ab29c)) {
            param_11 = (undefined4 *)0x0;
          }
        }
        else if (((DAT_803ab290 < 1) && (-1 < DAT_803ab290)) && (DAT_803ab294 != 0)) {
          param_11 = (undefined4 *)0x0;
        }
      }
      if (param_11 == (undefined4 *)0x0) {
        param_11 = &DAT_803ab28c;
        DAT_803ab28c = 1;
        param_1 = zz_02327c8_();
        DAT_803f7878 = DAT_803f7878 | 0x400;
        if ((DAT_803ab290 == 0) || (DAT_803ab290 == 0x10)) {
          DAT_803ab294 = DAT_803ab294 + -1;
        }
        DAT_803f7674 = 0;
      }
      else {
        DAT_803ab28c = 0;
      }
    }
    if (DAT_803ab28c == 0) {
      DAT_803f7674 = 1;
      iVar1 = TRKDoNotifyStopped(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 0x90,&DAT_803f75dc,param_11,param_12,param_13,param_14,param_15,
                                 param_16);
    }
  }
  return iVar1;
}



// ==== 8022ff90  FUN_8022ff90 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_8022ff90(void)

{
  uint uVar1;
  undefined4 uVar2;
  int local_18;
  undefined4 auStack_14 [5];
  
  if (_DAT_803f7678 == 0) {
    uVar1 = _DAT_803f7978 & 0xffff;
    if ((uVar1 == 0xd00) || ((uVar1 < 0xd00 && (uVar1 == 0x700)))) {
      TRKTargetReadInstruction((int)&local_18,DAT_803f7700);
      if (local_18 == 0xfe00000) {
        uVar2 = 5;
      }
      else {
        uVar2 = 3;
      }
    }
    else {
      uVar2 = 4;
    }
    TRKConstructEvent(auStack_14,uVar2);
    TRKPostEvent((int)auStack_14);
  }
  else {
    _DAT_803f7678 = 0;
  }
  return;
}



// ==== 8023003c  TRKTargetAccessExtended2 ====

/* WARNING: Removing unreachable block (ram,0x802303c0) */

int TRKTargetAccessExtended2(uint param_1,uint param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  undefined4 extraout_r4;
  uint uVar2;
  uint local_128;
  undefined4 local_124;
  undefined4 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined4 local_114;
  undefined4 local_110;
  uint local_10c;
  undefined4 local_108;
  undefined4 local_104;
  undefined4 local_100;
  undefined4 local_fc;
  undefined4 local_f8;
  undefined4 local_f4;
  undefined4 local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  uint local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  
  if (param_2 < 0x20) {
    local_11c = DAT_803ab27c;
    local_118 = DAT_803ab280;
    local_114 = DAT_803ab284;
    local_110 = DAT_803ab288;
    DAT_803ab288._1_3_ = (uint3)DAT_803ab288._2_2_;
    local_64 = DAT_802b49b0;
    local_60 = DAT_802b49b4;
    local_5c = DAT_802b49b8;
    local_58 = DAT_802b49bc;
    local_54 = DAT_802b49c0;
    local_50 = DAT_802b49c4;
    local_4c = DAT_802b49c8;
    local_6c = 0x7c98e2a6;
    local_68 = 0x90830000;
    local_48 = 0x4e800020;
    TRK_flush_cache((uint)&local_6c,0x28);
    (*(code *)&local_6c)(&local_128,&DAT_803f7b44);
    local_128 = local_128 | 0xa0000000;
    local_8c = DAT_802b49b0;
    local_88 = DAT_802b49b4;
    local_84 = DAT_802b49b8;
    local_80 = DAT_802b49bc;
    local_7c = DAT_802b49c0;
    local_78 = DAT_802b49c4;
    local_74 = DAT_802b49c8;
    local_94 = 0x80830000;
    local_90 = 0x7c98e3a6;
    local_70 = 0x4e800020;
    TRK_flush_cache((uint)&local_94,0x28);
    (*(code *)&local_94)(&local_128,&DAT_803f7b44);
    local_128 = 0;
    local_b4 = DAT_802b49b0;
    local_b0 = DAT_802b49b4;
    local_ac = DAT_802b49b8;
    local_a8 = DAT_802b49bc;
    local_a4 = DAT_802b49c0;
    local_a0 = DAT_802b49c4;
    local_9c = DAT_802b49c8;
    local_bc = 0x80830000;
    local_b8 = 0x7c90e3a6;
    local_98 = 0x4e800020;
    TRK_flush_cache((uint)&local_bc,0x28);
    (*(code *)&local_bc)(&local_128,&DAT_803f7b44);
    uVar2 = param_1 << 0x15;
    *param_4 = 0;
    iVar1 = 0;
    while ((param_1 <= param_2 && (iVar1 == 0))) {
      if (param_5 == 0) {
        TRKReadBuffer1_ui64(param_3,(undefined1 *)&local_124);
        local_10c = uVar2 | 0xe0030000;
        local_108 = DAT_802b49d4;
        local_104 = DAT_802b49d8;
        local_100 = DAT_802b49dc;
        local_fc = DAT_802b49e0;
        local_f8 = DAT_802b49e4;
        local_f4 = DAT_802b49e8;
        local_f0 = DAT_802b49ec;
        local_ec = DAT_802b49f0;
        local_e8 = 0x4e800020;
        TRK_flush_cache((uint)&local_10c,0x28);
        (*(code *)&local_10c)(&local_124,&DAT_803f7b44);
        iVar1 = 0;
      }
      else {
        local_e0 = DAT_802b49d4;
        local_dc = DAT_802b49d8;
        local_d8 = DAT_802b49dc;
        local_d4 = DAT_802b49e0;
        local_d0 = DAT_802b49e4;
        local_cc = DAT_802b49e8;
        local_c8 = DAT_802b49ec;
        local_c4 = DAT_802b49f0;
        local_e4 = uVar2 | 0xf0030000;
        local_c0 = 0x4e800020;
        TRK_flush_cache((uint)&local_e4,0x28);
        (*(code *)&local_e4)(&local_124,&DAT_803f7b44);
        iVar1 = TRKAppendBuffer1_ui64(param_3,extraout_r4,local_124,local_120);
      }
      uVar2 = uVar2 + 0x200000;
      param_1 = param_1 + 1;
      *param_4 = *param_4 + 8;
    }
    if (DAT_803ab288._1_1_ != '\0') {
      iVar1 = 0x702;
      *param_4 = 0;
    }
    DAT_803ab27c = local_11c;
    DAT_803ab280 = local_118;
    DAT_803ab284 = local_114;
    DAT_803ab288 = local_110;
  }
  else {
    iVar1 = 0x701;
  }
  return iVar1;
}



// ==== 80230474  TRKTargetAccessExtended1 ====

uint TRKTargetAccessExtended1(uint param_1,uint param_2,int param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  uVar4 = DAT_803ab288;
  uVar3 = DAT_803ab284;
  uVar2 = DAT_803ab280;
  uVar1 = DAT_803ab27c;
  if (param_2 < 0x61) {
    DAT_803ab288._1_3_ = (uint3)DAT_803ab288._2_2_;
    *param_4 = 0;
    if (param_1 <= param_2) {
      iVar6 = param_2 - param_1;
      iVar5 = iVar6 + 1;
      *param_4 = *param_4 + iVar5 * 4;
      puVar7 = &DAT_803f7828 + param_1;
      if (param_5 == 0) {
        if ((puVar7 < (undefined4 *)((int)&DAT_803f786c + 1U)) &&
           ((undefined4 *)0x803f7867 < puVar7 + iVar6)) {
          DAT_803ab270 = 1;
        }
        if ((puVar7 < (undefined4 *)((int)&DAT_803f78f8 + 1U)) &&
           ((undefined4 *)0x803f78f7 < puVar7 + iVar6)) {
          DAT_803ab271 = 1;
        }
        param_1 = TRKReadBuffer_ui32(param_3,(undefined1 *)puVar7,iVar5);
      }
      else {
        param_1 = TRKAppendBuffer_ui32(param_3,puVar7,iVar5);
      }
    }
    if (DAT_803ab288._1_1_ != '\0') {
      param_1 = 0x702;
      *param_4 = 0;
    }
  }
  else {
    param_1 = 0x701;
  }
  DAT_803ab27c = uVar1;
  DAT_803ab280 = uVar2;
  DAT_803ab284 = uVar3;
  DAT_803ab288 = uVar4;
  return param_1;
}



// ==== 802305e4  zz_02305e4_ ====

/* WARNING: Removing unreachable block (ram,0x802309b8) */
/* WARNING: Removing unreachable block (ram,0x802308dc) */
/* WARNING: Removing unreachable block (ram,0x80230a20) */

int zz_02305e4_(uint param_1,uint param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  uint local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  if (param_2 < 0x22) {
    local_e0 = DAT_803ab27c;
    local_dc = DAT_803ab280;
    local_d8 = DAT_803ab284;
    local_d4 = DAT_803ab288;
    DAT_803ab288._1_3_ = (uint3)DAT_803ab288._2_2_;
    zz_022f5a0_();
    zz_022f5a8_();
    *param_4 = 0;
    uVar3 = param_1 << 0x15;
    iVar1 = 0;
    while ((uVar2 = local_e8, param_1 <= param_2 && (iVar1 == 0))) {
      if (param_5 == 0) {
        TRKReadBuffer1_ui64(param_3,(undefined1 *)&local_e8);
        iVar1 = 0;
        local_80 = DAT_802b49f8;
        local_7c = DAT_802b49fc;
        local_78 = DAT_802b4a00;
        local_74 = DAT_802b4a04;
        local_70 = DAT_802b4a08;
        local_6c = DAT_802b4a0c;
        local_68 = DAT_802b4a10;
        local_64 = DAT_802b4a14;
        local_60 = DAT_802b4a18;
        local_5c = DAT_802b4a1c;
        if (param_1 < 0x20) {
          local_80 = uVar3 | 0xc8030000;
          local_5c = 0x4e800020;
          TRK_flush_cache((uint)&local_80,0x28);
          (*(code *)&local_80)(&local_e8,&DAT_803f7b44);
          iVar1 = 0;
        }
        else if (param_1 == 0x20) {
          local_e8 = 0;
        }
        else if (param_1 == 0x21) {
          local_e8 = local_e4;
          local_c8 = DAT_802b49b0;
          local_c4 = DAT_802b49b4;
          local_c0 = DAT_802b49b8;
          local_bc = DAT_802b49bc;
          local_b8 = DAT_802b49c0;
          local_b4 = DAT_802b49c4;
          local_b0 = DAT_802b49c8;
          local_cc = 0x7c9efba6;
          local_d0 = 0x80830000;
          local_ac = 0x4e800020;
          TRK_flush_cache((uint)&local_d0,0x28);
          (*(code *)&local_d0)(&local_e8,&DAT_803f7b44);
          iVar1 = 0;
        }
      }
      else {
        local_58 = DAT_802b49f8;
        local_54 = DAT_802b49fc;
        local_50 = DAT_802b4a00;
        local_4c = DAT_802b4a04;
        local_48 = DAT_802b4a08;
        local_44 = DAT_802b4a0c;
        local_40 = DAT_802b4a10;
        local_3c = DAT_802b4a14;
        local_38 = DAT_802b4a18;
        local_34 = DAT_802b4a1c;
        if (param_1 < 0x20) {
          local_58 = uVar3 | 0xc8030000;
          if (param_5 != 0) {
            local_58 = uVar3 | 0xd8030000;
          }
          local_34 = 0x4e800020;
          TRK_flush_cache((uint)&local_58,0x28);
          (*(code *)&local_58)(&local_e8,&DAT_803f7b44);
          uVar2 = extraout_r4;
        }
        else if (param_1 == 0x20) {
          local_e8 = 0;
        }
        else {
          uVar2 = DAT_802b4a14;
          if (param_1 == 0x21) {
            if (param_5 == 0) {
              local_e8 = local_e4;
            }
            local_a0 = DAT_802b49b0;
            local_9c = DAT_802b49b4;
            local_98 = DAT_802b49b8;
            local_94 = DAT_802b49bc;
            local_90 = DAT_802b49c0;
            local_8c = DAT_802b49c4;
            local_88 = DAT_802b49c8;
            if (param_5 == 0) {
              local_a8 = 0x80830000;
              local_a4 = 0x7c9efba6;
            }
            else {
              local_a4 = 0x90830000;
              local_a8 = 0x7c9efaa6;
            }
            local_84 = 0x4e800020;
            TRK_flush_cache((uint)&local_a8,0x28);
            (*(code *)&local_a8)(&local_e8,&DAT_803f7b44);
            uVar2 = extraout_r4_00;
            if (param_5 != 0) {
              uVar2 = 0;
              local_e4 = local_e8;
              local_e8 = 0;
            }
          }
        }
        iVar1 = TRKAppendBuffer1_ui64(param_3,uVar2,local_e8,local_e4);
      }
      uVar3 = uVar3 + 0x200000;
      param_1 = param_1 + 1;
      *param_4 = *param_4 + 8;
    }
    if (DAT_803ab288._1_1_ != '\0') {
      iVar1 = 0x702;
      *param_4 = 0;
    }
    DAT_803ab27c = local_e0;
    DAT_803ab280 = local_dc;
    DAT_803ab284 = local_d8;
    DAT_803ab288 = local_d4;
  }
  else {
    iVar1 = 0x701;
  }
  return iVar1;
}



// ==== 80230ab0  TRKTargetAccessDefault ====

undefined4 TRKTargetAccessDefault(int param_1,uint param_2,int param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  
  uVar4 = DAT_803ab288;
  uVar3 = DAT_803ab284;
  uVar2 = DAT_803ab280;
  uVar1 = DAT_803ab27c;
  if (param_2 < 0x25) {
    iVar6 = (param_2 - param_1) + 1;
    DAT_803ab288._1_3_ = (uint3)DAT_803ab288._2_2_;
    *param_4 = iVar6 * 4;
    if (param_5 == 0) {
      uVar5 = TRKReadBuffer_ui32(param_3,(undefined1 *)(&DAT_803f7680 + param_1),iVar6);
    }
    else {
      uVar5 = TRKAppendBuffer_ui32(param_3,&DAT_803f7680 + param_1,iVar6);
    }
    if (DAT_803ab288._1_1_ != '\0') {
      uVar5 = 0x702;
      *param_4 = 0;
    }
  }
  else {
    uVar5 = 0x701;
  }
  DAT_803ab27c = uVar1;
  DAT_803ab280 = uVar2;
  DAT_803ab284 = uVar3;
  DAT_803ab288 = uVar4;
  return uVar5;
}



// ==== 80230ba4  TRKTargetReadInstruction ====

int TRKTargetReadInstruction(int param_1,uint param_2)

{
  int iVar1;
  int local_8 [2];
  
  local_8[0] = 4;
  iVar1 = TRKTargetAccessMemory(param_1,param_2,local_8,0,1);
  if ((iVar1 == 0) && (local_8[0] != 4)) {
    iVar1 = 0x700;
  }
  return iVar1;
}



// ==== 80230bf0  TRKTargetAccessMemory ====

int TRKTargetAccessMemory(int param_1,uint param_2,int *param_3,undefined4 param_4,int param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  uVar4 = DAT_803ab288;
  uVar3 = DAT_803ab284;
  uVar2 = DAT_803ab280;
  uVar1 = DAT_803ab27c;
  DAT_803ab288._1_3_ = (uint3)DAT_803ab288._2_2_;
  uVar6 = TRKTargetTranslate(param_2);
  uVar5 = countLeadingZeros(param_5);
  iVar7 = TRKValidMemory32(uVar6,*param_3,uVar5 >> 5);
  if (iVar7 == 0) {
    zz_022f5a0_();
    if (param_5 == 0) {
      TRK_ppc_memcpy(uVar6,param_1,*param_3);
      TRK_flush_cache(uVar6,*param_3);
      if (param_2 != uVar6) {
        TRK_flush_cache(param_2,*param_3);
      }
    }
    else {
      TRK_ppc_memcpy(param_1,uVar6,*param_3);
    }
  }
  else {
    *param_3 = 0;
  }
  if (DAT_803ab288._1_1_ != '\0') {
    iVar7 = 0x702;
    *param_3 = 0;
  }
  DAT_803ab27c = uVar1;
  DAT_803ab280 = uVar2;
  DAT_803ab284 = uVar3;
  DAT_803ab288 = uVar4;
  return iVar7;
}



// ==== 80230d3c  TRKValidMemory32 ====

int TRKValidMemory32(uint param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  uVar2 = (param_2 + param_1) - 1;
  iVar1 = 0x700;
  if (uVar2 < param_1) {
    iVar1 = 0x700;
  }
  else if ((param_1 <= DAT_802b499c) && (DAT_802b4998 <= uVar2)) {
    if (((param_3 == 0) && (DAT_802b49a0 == 0)) || ((param_3 == 1 && (DAT_802b49a4 == 0)))) {
      iVar1 = 0x700;
    }
    else {
      iVar1 = 0;
      if (param_1 < DAT_802b4998) {
        iVar1 = 0x700;
        uVar3 = DAT_802b4998 - 1;
        if (((param_1 <= uVar3) && (param_1 <= DAT_802b499c)) && (DAT_802b4998 <= uVar3)) {
          if (((param_3 == 0) && (DAT_802b49a0 == 0)) || ((param_3 == 1 && (DAT_802b49a4 == 0)))) {
            iVar1 = 0x700;
          }
          else {
            iVar1 = 0;
            if (param_1 < DAT_802b4998) {
              iVar1 = TRKValidMemory32(param_1,DAT_802b4998 - param_1,param_3);
            }
            if ((iVar1 == 0) && (DAT_802b499c < uVar3)) {
              iVar1 = TRKValidMemory32(DAT_802b499c,uVar3 - DAT_802b499c,param_3);
            }
          }
        }
      }
      if ((iVar1 == 0) && (DAT_802b499c < uVar2)) {
        iVar1 = 0x700;
        uVar2 = (param_2 + param_1) - 2;
        if ((DAT_802b499c <= uVar2) && (DAT_802b4998 <= uVar2)) {
          if (((param_3 == 0) && (DAT_802b49a0 == 0)) || ((param_3 == 1 && (DAT_802b49a4 == 0)))) {
            iVar1 = 0x700;
          }
          else {
            iVar1 = 0;
            if (DAT_802b499c < DAT_802b4998) {
              iVar1 = TRKValidMemory32(DAT_802b499c,DAT_802b4998 - DAT_802b499c,param_3);
            }
            if ((iVar1 == 0) && (DAT_802b499c < uVar2)) {
              iVar1 = TRKValidMemory32(DAT_802b499c,uVar2 - DAT_802b499c,param_3);
            }
          }
        }
      }
    }
  }
  return iVar1;
}



// ==== 80230fe0  zz_0230fe0_ ====

void zz_0230fe0_(void)

{
  undefined4 in_r0;
  
  trapWord(0x1f,in_r0,0);
  return;
}



// ==== 80230ff0  zz_0230ff0_ ====

void zz_0230ff0_(void)

{
  undefined4 in_r0;
  
  trapWord(0x1f,in_r0,0);
  return;
}



// ==== 80231000  TRKSaveExtended1Block ====

void TRKSaveExtended1Block(void)

{
  undefined4 in_sr0;
  undefined4 in_sr1;
  undefined4 in_sr2;
  undefined4 in_sr3;
  undefined4 in_sr4;
  undefined4 in_sr5;
  undefined4 in_sr6;
  undefined4 in_sr7;
  undefined4 in_sr8;
  undefined4 in_sr9;
  undefined4 in_sr10;
  undefined4 in_sr11;
  undefined4 in_sr12;
  undefined4 in_sr13;
  undefined4 in_sr14;
  undefined4 in_sr15;
  undefined4 in_DSISR;
  undefined4 in_DAR;
  undefined4 in_SDR1;
  undefined4 in_SRR1;
  undefined4 in_TBLr;
  undefined4 in_TBUr;
  undefined4 in_SPRG0;
  undefined4 in_SPRG1;
  undefined4 in_SPRG2;
  undefined4 in_SPRG3;
  undefined4 in_EAR;
  undefined4 in_PVR;
  undefined4 in_IBAT0U;
  undefined4 in_IBAT0L;
  undefined4 in_IBAT1U;
  undefined4 in_IBAT1L;
  undefined4 in_IBAT2U;
  undefined4 in_IBAT2L;
  undefined4 in_IBAT3U;
  undefined4 in_IBAT3L;
  undefined4 in_DBAT0U;
  undefined4 in_DBAT0L;
  undefined4 in_DBAT1U;
  undefined4 in_DBAT1L;
  undefined4 in_DBAT2U;
  undefined4 in_DBAT2L;
  undefined4 in_DBAT3U;
  undefined4 in_DBAT3L;
  undefined4 in_HID2;
  undefined4 in_WPAR;
  undefined4 in_DMAU;
  undefined4 in_DMAL;
  undefined4 in_MMCR0;
  undefined4 in_PMC1;
  undefined4 in_PMC2;
  undefined4 in_SIA;
  undefined4 in_MMCR1;
  undefined4 in_PMC3;
  undefined4 in_PMC4;
  undefined4 in_HID0;
  undefined4 in_HID1;
  undefined4 in_IABR;
  undefined4 in_DABR;
  undefined4 in_L2CR;
  undefined4 in_ICTC;
  undefined4 in_THRM1;
  undefined4 in_THRM2;
  undefined4 in_THRM3;
  
  DAT_803f7828 = in_sr0;
  DAT_803f782c = in_sr1;
  DAT_803f7830 = in_sr2;
  DAT_803f7834 = in_sr3;
  DAT_803f7838 = in_sr4;
  DAT_803f783c = in_sr5;
  DAT_803f7840 = in_sr6;
  DAT_803f7844 = in_sr7;
  DAT_803f7848 = in_sr8;
  DAT_803f784c = in_sr9;
  DAT_803f7850 = in_sr10;
  DAT_803f7854 = in_sr11;
  DAT_803f7858 = in_sr12;
  DAT_803f785c = in_sr13;
  DAT_803f7860 = in_sr14;
  DAT_803f7864 = in_sr15;
  DAT_803f7868 = in_TBLr;
  DAT_803f786c = in_TBUr;
  DAT_803f7870 = in_HID0;
  DAT_803f7874 = in_HID1;
  DAT_803f7878 = in_SRR1;
  DAT_803f787c = in_PVR;
  DAT_803f7880 = in_IBAT0U;
  DAT_803f7884 = in_IBAT0L;
  DAT_803f7888 = in_IBAT1U;
  DAT_803f788c = in_IBAT1L;
  DAT_803f7890 = in_IBAT2U;
  DAT_803f7894 = in_IBAT2L;
  DAT_803f7898 = in_IBAT3U;
  DAT_803f789c = in_IBAT3L;
  DAT_803f78a0 = in_DBAT0U;
  DAT_803f78a4 = in_DBAT0L;
  DAT_803f78a8 = in_DBAT1U;
  DAT_803f78ac = in_DBAT1L;
  DAT_803f78b0 = in_DBAT2U;
  DAT_803f78b4 = in_DBAT2L;
  DAT_803f78b8 = in_DBAT3U;
  DAT_803f78bc = in_DBAT3L;
  DAT_803f78dc = in_SDR1;
  DAT_803f78e0 = in_DAR;
  DAT_803f78e4 = in_DSISR;
  DAT_803f78e8 = in_SPRG0;
  DAT_803f78ec = in_SPRG1;
  DAT_803f78f0 = in_SPRG2;
  DAT_803f78f4 = in_SPRG3;
  DAT_803f78f8 = 0;
  DAT_803f78fc = in_IABR;
  DAT_803f7900 = in_EAR;
  DAT_803f797c = 0;
  DAT_803f7980 = 0;
  DAT_803f7984 = 0x40004;
  DAT_803f7988 = 0x50005;
  DAT_803f798c = 0x60006;
  DAT_803f7990 = 0x70007;
  DAT_803f7994 = 0;
  DAT_803f7998 = 0;
  DAT_803f799c = in_HID2;
  DAT_803f79a0 = in_WPAR;
  DAT_803f79a4 = in_DMAU;
  DAT_803f79a8 = in_DMAL;
  DAT_803f7904 = in_DABR;
  DAT_803f7908 = in_PMC1;
  DAT_803f790c = in_PMC2;
  DAT_803f7910 = in_PMC3;
  DAT_803f7914 = in_PMC4;
  DAT_803f7918 = in_SIA;
  DAT_803f791c = in_MMCR0;
  DAT_803f7920 = in_MMCR1;
  DAT_803f7924 = in_THRM1;
  DAT_803f7928 = in_THRM2;
  DAT_803f792c = in_THRM3;
  DAT_803f7930 = in_ICTC;
  DAT_803f7934 = in_L2CR;
  return;
}



// ==== 802311b8  TRKRestoreExtended1Block ====

void TRKRestoreExtended1Block(void)

{
  DAT_803ab270 = 0;
  DAT_803ab271 = 0;
  return;
}



// ==== 80231370  FUN_80231370 ====

/* WARNING: This function may have set the stack pointer */

undefined8
FUN_80231370(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 *param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 in_r0;
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
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
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_LR;
  undefined8 uVar9;
  
  DAT_803f7688 = &DAT_8043ea20;
  DAT_803f76b4 = &FLOAT_8043b5a0;
  DAT_803f7708 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
                 (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 |
                 (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
                 (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  DAT_803f7680 = in_r0;
  DAT_803f7684 = (undefined1 *)register0x00000004;
  DAT_803f768c = param_9;
  DAT_803f7690 = param_10;
  DAT_803f7694 = param_11;
  DAT_803f7698 = param_12;
  DAT_803f769c = param_13;
  DAT_803f76a0 = param_14;
  DAT_803f76a4 = param_15;
  DAT_803f76a8 = param_16;
  DAT_803f76ac = in_r11;
  DAT_803f76b0 = in_r12;
  DAT_803f76b8 = unaff_r14;
  DAT_803f76bc = unaff_r15;
  DAT_803f76c0 = unaff_r16;
  DAT_803f76c4 = unaff_r17;
  DAT_803f76c8 = unaff_r18;
  DAT_803f76cc = unaff_r19;
  DAT_803f76d0 = unaff_r20;
  DAT_803f76d4 = unaff_r21;
  DAT_803f76d8 = unaff_r22;
  DAT_803f76dc = unaff_r23;
  DAT_803f76e0 = unaff_r24;
  DAT_803f76e4 = unaff_r25;
  DAT_803f76e8 = unaff_r26;
  DAT_803f76ec = unaff_r27;
  DAT_803f76f0 = unaff_r28;
  DAT_803f76f4 = unaff_r29;
  DAT_803f76f8 = unaff_r30;
  DAT_803f76fc = unaff_r31;
  DAT_803f7700 = in_LR;
  DAT_803f7704 = in_LR;
  uVar9 = TRKSaveExtended1Block();
  uVar2 = DAT_803f7690;
  puVar3 = DAT_803f7694;
  uVar4 = DAT_803f7698;
  uVar5 = DAT_803f769c;
  uVar6 = DAT_803f76a0;
  uVar7 = DAT_803f76a4;
  uVar8 = DAT_803f76a8;
  iVar1 = InitMetroTRKCommTable
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803f7694
                     ,DAT_803f7690,DAT_803f7694,DAT_803f7698,DAT_803f769c,DAT_803f76a0,DAT_803f76a4,
                     DAT_803f76a8);
  if (iVar1 == 1) {
    return uRam0000000d;
  }
  uVar9 = FUN_8023168c(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,
                       puVar3,uVar4,uVar5,uVar6,uVar7,uVar8);
  return uVar9;
}



// ==== 80231408  InitMetroTRK_BBA ====

/* WARNING: This function may have set the stack pointer */

undefined8
InitMetroTRK_BBA(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 *param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 in_r0;
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
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
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_LR;
  undefined8 uVar9;
  
  DAT_803f7688 = &DAT_8043ea20;
  DAT_803f76b4 = &FLOAT_8043b5a0;
  DAT_803f7708 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 |
                 (uint)(in_cr2 & 0xf) << 0x14 | (uint)(in_cr3 & 0xf) << 0x10 |
                 (uint)(unaff_cr4 & 0xf) << 0xc | (uint)(in_cr5 & 0xf) << 8 |
                 (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  DAT_803f7680 = in_r0;
  DAT_803f7684 = (undefined1 *)register0x00000004;
  DAT_803f768c = param_9;
  DAT_803f7690 = param_10;
  DAT_803f7694 = param_11;
  DAT_803f7698 = param_12;
  DAT_803f769c = param_13;
  DAT_803f76a0 = param_14;
  DAT_803f76a4 = param_15;
  DAT_803f76a8 = param_16;
  DAT_803f76ac = in_r11;
  DAT_803f76b0 = in_r12;
  DAT_803f76b8 = unaff_r14;
  DAT_803f76bc = unaff_r15;
  DAT_803f76c0 = unaff_r16;
  DAT_803f76c4 = unaff_r17;
  DAT_803f76c8 = unaff_r18;
  DAT_803f76cc = unaff_r19;
  DAT_803f76d0 = unaff_r20;
  DAT_803f76d4 = unaff_r21;
  DAT_803f76d8 = unaff_r22;
  DAT_803f76dc = unaff_r23;
  DAT_803f76e0 = unaff_r24;
  DAT_803f76e4 = unaff_r25;
  DAT_803f76e8 = unaff_r26;
  DAT_803f76ec = unaff_r27;
  DAT_803f76f0 = unaff_r28;
  DAT_803f76f4 = unaff_r29;
  DAT_803f76f8 = unaff_r30;
  DAT_803f76fc = unaff_r31;
  DAT_803f7700 = in_LR;
  DAT_803f7704 = in_LR;
  uVar9 = TRKSaveExtended1Block();
  uVar2 = DAT_803f7690;
  puVar3 = DAT_803f7694;
  uVar4 = DAT_803f7698;
  uVar5 = DAT_803f769c;
  uVar6 = DAT_803f76a0;
  uVar7 = DAT_803f76a4;
  uVar8 = DAT_803f76a8;
  iVar1 = InitMetroTRKCommTable
                    (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,DAT_803f7690,
                     DAT_803f7694,DAT_803f7698,DAT_803f769c,DAT_803f76a0,DAT_803f76a4,DAT_803f76a8);
  if (iVar1 == 1) {
    return uRam0000000d;
  }
  uVar9 = FUN_8023168c(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,
                       puVar3,uVar4,uVar5,uVar6,uVar7,uVar8);
  return uVar9;
}



// ==== 8023149c  TRKInitializeTarget ====

undefined4 TRKInitializeTarget(void)

{
  DAT_803f7674 = 1;
  DAT_803f7668 = zz_022f5a0_();
  DAT_803f7b58 = 0xe0000000;
  return 0;
}



// ==== 802314e8  __TRK_copy_vectors ====

void __TRK_copy_vectors(void)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  if (((DAT_803f7b58 < 0x45) && (0x44 < DAT_803f7b58 + 0x4000)) && ((DAT_803f78b8 & 3) != 0)) {
    puVar1 = (uint *)&DAT_00000044;
  }
  else {
    puVar1 = &DAT_80000044;
  }
  uVar4 = *puVar1;
  puVar1 = &DAT_803ab2a0;
  iVar5 = 0;
  do {
    if (((uVar4 & 1 << iVar5) != 0) && (iVar5 != 4)) {
      uVar2 = *puVar1;
      uVar3 = uVar2;
      if (((uVar2 < DAT_803f7b58) || ((DAT_803f7b58 + 0x4000 <= uVar2 || ((DAT_803f78b8 & 3) == 0)))
          ) && ((uVar2 < 0x7e000000 || (0x80000000 < uVar2)))) {
        uVar3 = uVar2 & 0x3fffffff | 0x80000000;
      }
      TRK_memcpy(uVar3,uVar2 + 0x800034ac,0x100);
      TRK_flush_cache(uVar3,0x100);
    }
    iVar5 = iVar5 + 1;
    puVar1 = puVar1 + 1;
  } while (iVar5 < 0xf);
  return;
}



// ==== 80231614  TRKTargetTranslate ====

uint TRKTargetTranslate(uint param_1)

{
  if (DAT_803f7b58 <= param_1) {
    if ((param_1 < DAT_803f7b58 + 0x4000) && ((DAT_803f78b8 & 3) != 0)) {
      return param_1;
    }
  }
  if ((0x7dffffff < param_1) && (param_1 < 0x80000001)) {
    return param_1;
  }
  return param_1 & 0x3fffffff | 0x80000000;
}



// ==== 8023166c  zz_023166c_ ====

void zz_023166c_(void)

{
  EnableEXI2Interrupts();
  return;
}



// ==== 8023168c  FUN_8023168c ====

void FUN_8023168c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 *param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  undefined8 extraout_f1;
  
  uVar1 = zz_02327c8_();
  DAT_803f7b60 = TRKInitializeNub();
  if (DAT_803f7b60 == 0) {
    uVar1 = TRKNubWelcome(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0x803f0000
                          ,param_11,param_12,param_13,param_14,param_15,param_16);
    TRKNubMainLoop(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
                   param_15,param_16);
  }
  DAT_803f7b60 = zz_022ce50_();
  return;
}



// ==== 802316e4  TRKLoadContext ====

undefined4
TRKLoadContext(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  ushort uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 extraout_r4;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  uint uVar13;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  undefined4 uVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  uint uVar33;
  uint in_MSR;
  undefined4 uVar34;
  
  uVar2 = *param_1;
  puVar3 = (undefined1 *)param_1[1];
  uVar4 = param_1[2];
  uVar1 = *(ushort *)((int)param_1 + 0x1a2);
  uVar12 = (uint)uVar1;
  uVar13 = uVar1 & 2;
  if ((uVar1 & 2) == 0) {
    uVar14 = param_1[0xd];
    uVar15 = param_1[0xe];
    uVar16 = param_1[0xf];
    uVar17 = param_1[0x10];
    uVar18 = param_1[0x11];
    uVar19 = param_1[0x12];
    uVar20 = param_1[0x13];
    uVar21 = param_1[0x14];
    uVar22 = param_1[0x15];
    uVar23 = param_1[0x16];
    uVar24 = param_1[0x17];
    uVar25 = param_1[0x18];
    uVar26 = param_1[0x19];
    uVar27 = param_1[0x1a];
    uVar28 = param_1[0x1b];
    uVar29 = param_1[0x1c];
    uVar30 = param_1[0x1d];
    uVar31 = param_1[0x1e];
  }
  else {
    *(ushort *)((int)param_1 + 0x1a2) = uVar1 & 0xfffd;
    uVar12 = param_1[5];
    uVar13 = param_1[6];
    param_5 = param_1[7];
    param_6 = param_1[8];
    param_7 = param_1[9];
    param_8 = param_1[10];
    in_r11 = param_1[0xb];
    in_r12 = param_1[0xc];
    uVar14 = param_1[0xd];
    uVar15 = param_1[0xe];
    uVar16 = param_1[0xf];
    uVar17 = param_1[0x10];
    uVar18 = param_1[0x11];
    uVar19 = param_1[0x12];
    uVar20 = param_1[0x13];
    uVar21 = param_1[0x14];
    uVar22 = param_1[0x15];
    uVar23 = param_1[0x16];
    uVar24 = param_1[0x17];
    uVar25 = param_1[0x18];
    uVar26 = param_1[0x19];
    uVar27 = param_1[0x1a];
    uVar28 = param_1[0x1b];
    uVar29 = param_1[0x1c];
    uVar30 = param_1[0x1d];
    uVar31 = param_1[0x1e];
  }
  uVar6 = param_1[0x20];
  uVar7 = param_1[0x22];
  uVar8 = param_1[0x23];
  uVar33 = in_MSR & 0x9000;
  uVar9 = param_1[3];
  uVar10 = param_1[4];
  uVar5 = param_1[0x66];
  uVar11 = param_1[0x67];
  uVar32 = param_1[0x1f];
  uVar6 = uVar6 & 0xf0000000 | (uint)((byte)(uVar6 >> 0x18) & 0xf) << 0x18 |
          (uint)((byte)(uVar6 >> 0x14) & 0xf) << 0x14 | (uint)((byte)(uVar6 >> 0x10) & 0xf) << 0x10
          | (uint)((byte)(uVar6 >> 0xc) & 0xf) << 0xc | (uint)((byte)(uVar6 >> 8) & 0xf) << 8 |
          (uint)((byte)(uVar6 >> 4) & 0xf) << 4 | (uint)((byte)uVar6 & 0xf);
  sync(0);
  sync(0);
  DAT_803f75d8 = (undefined2)param_2;
  uVar34 = param_1[0x21];
  if (param_2 == 0x500) {
    DAT_803f7aac = param_1[0x21];
    zz_023176c_();
    if ((*DAT_803f767c == '\0') || (DAT_803ab288._0_1_ == '\x01')) {
      returnFromInterrupt(uVar33,uVar11);
      return DAT_803f7abc;
    }
    DAT_803f7678 = 1;
    uVar10 = extraout_r4;
    uVar34 = DAT_803f7aac;
  }
  if (DAT_803ab288._0_1_ != '\0') {
    DAT_803ab284._0_2_ = DAT_803f75d8;
    DAT_803ab27c = uVar5;
    DAT_803ab288._1_1_ = 1;
    returnFromInterrupt(uVar33,uVar11);
    return uVar9;
  }
  DAT_803f7978 = DAT_803f75d8;
  DAT_803f797a = DAT_803f75d8;
  DAT_803f7680 = uVar2;
  DAT_803f7684 = puVar3;
  DAT_803f7688 = uVar4;
  DAT_803f768c = uVar9;
  DAT_803f7690 = uVar10;
  DAT_803f7694 = uVar12;
  DAT_803f7698 = uVar13;
  DAT_803f769c = param_5;
  DAT_803f76a0 = param_6;
  DAT_803f76a4 = param_7;
  DAT_803f76a8 = param_8;
  DAT_803f76ac = in_r11;
  DAT_803f76b0 = in_r12;
  DAT_803f76b4 = uVar14;
  DAT_803f76b8 = uVar15;
  DAT_803f76bc = uVar16;
  DAT_803f76c0 = uVar17;
  DAT_803f76c4 = uVar18;
  DAT_803f76c8 = uVar19;
  DAT_803f76cc = uVar20;
  DAT_803f76d0 = uVar21;
  DAT_803f76d4 = uVar22;
  DAT_803f76d8 = uVar23;
  DAT_803f76dc = uVar24;
  DAT_803f76e0 = uVar25;
  DAT_803f76e4 = uVar26;
  DAT_803f76e8 = uVar27;
  DAT_803f76ec = uVar28;
  DAT_803f76f0 = uVar29;
  DAT_803f76f4 = uVar30;
  DAT_803f76f8 = uVar31;
  DAT_803f76fc = uVar32;
  DAT_803f7700 = uVar5;
  DAT_803f7704 = uVar34;
  DAT_803f7708 = uVar6;
  DAT_803f770c = uVar7;
  DAT_803f7710 = uVar8;
  TRKSaveExtended1Block();
  DAT_803ab288._0_1_ = 1;
  sync(0);
  sync(0);
  uVar2 = FUN_8022ff90();
  return uVar2;
}



// ==== 8023176c  zz_023176c_ ====

void zz_023176c_(void)

{
  return;
}



// ==== 80231770  InitializeProgramEndTrap ====

void InitializeProgramEndTrap(void)

{
  TRK_memcpy(-0x7fe015e0,-0x7fd4b5c0,4);
  gnt4_ICInvalidateRange_bl(0x801fea20,4);
  gnt4_DCFlushRange_bl(0x801fea20,4);
  return;
}



// ==== 802317c8  TRK_board_display ====

void TRK_board_display(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                      undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                      undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12
                      ,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                      undefined4 param_16)

{
  gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_802b4a44,
                   param_9,0x802b0000,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 802317f8  zz_02317f8_ ====

void zz_02317f8_(void)

{
  (*DAT_803ab300)();
  return;
}



// ==== 80231828  zz_0231828_ ====

void zz_0231828_(void)

{
  (*DAT_803ab304)();
  return;
}



// ==== 80231858  zz_0231858_ ====

int zz_0231858_(void)

{
  uint uVar1;
  
  uVar1 = (*DAT_803ab2f4)();
  return (int)(-uVar1 | uVar1) >> 0x1f;
}



// ==== 80231894  TRKWriteUARTN ====

int TRKWriteUARTN(void)

{
  uint uVar1;
  
  uVar1 = (*DAT_803ab2f0)();
  return (int)(-uVar1 | uVar1) >> 0x1f;
}



// ==== 802318d0  zz_02318d0_ ====

void zz_02318d0_(void)

{
  (*DAT_803ab2ec)();
  return;
}



// ==== 80231900  EnableEXI2Interrupts ====

void EnableEXI2Interrupts(void)

{
  if ((DAT_803f7b68 == '\0') && (DAT_803ab2e4 != (code *)0x0)) {
    (*DAT_803ab2e4)();
  }
  return;
}



// ==== 80231948  TRKInitializeIntDrivenUART ====

undefined4 TRKInitializeIntDrivenUART(void)

{
  undefined4 in_r6;
  
  (*DAT_803ab2e0)(in_r6,FUN_80231c04);
  (*DAT_803ab2f8)();
  return 0;
}



// ==== 80231998  InitMetroTRKCommTable ====

undefined4
InitMetroTRKCommTable
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
          undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
          undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar1;
  undefined8 uVar2;
  
  uVar1 = 1;
  uVar2 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Devkit_set_to____ld_802b4a48,param_9,param_11,param_12,param_13,
                           param_14,param_15,param_16);
  DAT_803f7b68 = 0;
  if (param_9 == 2) {
    gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_MetroTRK___Set_to_BBA_802b4a60,extraout_r4,param_11,param_12,param_13,
                     param_14,param_15,param_16);
    DAT_803f7b68 = 1;
    uVar1 = 0;
    DAT_803ab2e0 = (code *)&LAB_80231ec8;
    DAT_803ab2f8 = &LAB_80231eb8;
    DAT_803ab2fc = &LAB_80231eb0;
    DAT_803ab2f0 = (code *)&LAB_80231ea8;
    DAT_803ab2f4 = (code *)&LAB_80231ea0;
    DAT_803ab2e8 = &LAB_80231ec0;
    DAT_803ab2ec = (code *)&LAB_80231e98;
    DAT_803ab300 = (code *)&LAB_80231e90;
    DAT_803ab304 = (code *)&LAB_80231e88;
    DAT_803ab2e4 = (code *)0x0;
  }
  else if (param_9 == 1) {
    gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_MetroTRK___Set_to_GDEV_hardware_802b4a78,extraout_r4,param_11,param_12,
                     param_13,param_14,param_15,param_16);
    uVar1 = zz_023cce0_();
    DAT_803ab2e0 = FUN_80232740;
    DAT_803ab2f8 = &LAB_80232714;
    DAT_803ab2fc = &LAB_8023270c;
    DAT_803ab2f0 = FUN_80232618;
    DAT_803ab2f4 = FUN_80232558;
    DAT_803ab2e8 = &LAB_80232738;
    DAT_803ab2ec = FUN_802324a0;
    DAT_803ab300 = FUN_80232534;
    DAT_803ab304 = FUN_80232510;
    DAT_803ab2e4 = FUN_8023247c;
  }
  else if (param_9 == 0) {
    gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_MetroTRK___Set_to_AMC_DDH_hardwa_802b4a9c,extraout_r4,param_11,param_12,
                     param_13,param_14,param_15,param_16);
    uVar1 = zz_023ccd8_();
    DAT_803ab2e0 = FUN_8023218c;
    DAT_803ab2f8 = &LAB_80232160;
    DAT_803ab2fc = &LAB_80232158;
    DAT_803ab2f0 = FUN_8023206c;
    DAT_803ab2f4 = FUN_80231fac;
    DAT_803ab2e8 = &LAB_80232184;
    DAT_803ab2ec = FUN_80231ef4;
    DAT_803ab300 = FUN_80231f88;
    DAT_803ab304 = FUN_80231f64;
    DAT_803ab2e4 = FUN_80231ed0;
  }
  else {
    uVar2 = gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_MetroTRK___Set_to_UNKNOWN_hardwa_802b4ac0,param_9,param_11,param_12,
                             param_13,param_14,param_15,param_16);
    uVar2 = gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_MetroTRK___Invalid_hardware_ID_p_802b4aec,extraout_r4_00,param_11,
                             param_12,param_13,param_14,param_15,param_16);
    gnt4_OSReport_bl(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_MetroTRK___Defaulting_to_GDEV_Ha_802b4b1c,extraout_r4_01,param_11,param_12,
                     param_13,param_14,param_15,param_16);
  }
  return uVar1;
}



// ==== 80231c04  FUN_80231c04 ====

void FUN_80231c04(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  gnt4_OSEnableScheduler_bl();
  TRKLoadContext(param_2,0x500,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80231c3c  TRKTargetContinue ====

undefined4
TRKTargetContinue(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  
  TRKTargetSetInputPendingPtr(0);
  uVar1 = zz_02317f8_();
  TRKPostInterruptEvent
            ((int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_3,param_4,param_5,param_6,param_7,
             param_8);
  zz_0231828_();
  return 0;
}



// ==== 80231c70  SaveLoad::DidGameIDChange(void) ====

undefined1 SaveLoad__DidGameIDChange_void_(void)

{
  return DAT_803f7b70;
}



// ==== 80231c80  SetUseSerialIO ====

void SetUseSerialIO(undefined1 param_1)

{
  DAT_803f7b70 = param_1;
  return;
}



// ==== 80231c8c  FUN_80231c8c ====

/* WARNING: Removing unreachable block (ram,0x80231cd8) */

undefined4 FUN_80231c8c(void)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = zz_022ec14_();
  if (iVar1 == 0) {
    return 1;
  }
  bVar2 = zz_0230ff0_();
  if (bVar2 != 1) {
    if (bVar2 == 0) {
      return 0;
    }
    if (bVar2 < 3) {
      return 2;
    }
  }
  return 1;
}



// ==== 80231d10  zz_0231d10_ ====

/* WARNING: Removing unreachable block (ram,0x80231d90) */

undefined4 zz_0231d10_(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char cVar3;
  int iVar2;
  byte bVar4;
  
  cVar3 = SaveLoad__DidGameIDChange_void_();
  if ((cVar3 != '\0') && (iVar2 = zz_022ec14_(), iVar2 != 0)) {
    uVar1 = *param_3;
    bVar4 = zz_0230fe0_();
    *param_3 = uVar1;
    if (bVar4 != 1) {
      if (bVar4 == 0) {
        return 0;
      }
      if (bVar4 < 3) {
        return 2;
      }
    }
  }
  return 1;
}



// ==== 80231dcc  FUN_80231dcc ====

/* WARNING: Removing unreachable block (ram,0x80231e4c) */

undefined4 FUN_80231dcc(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  char cVar3;
  int iVar2;
  byte bVar4;
  
  cVar3 = SaveLoad__DidGameIDChange_void_();
  if ((cVar3 != '\0') && (iVar2 = zz_022ec14_(), iVar2 != 0)) {
    uVar1 = *param_3;
    bVar4 = zz_0230fe0_();
    *param_3 = uVar1;
    if (bVar4 != 1) {
      if (bVar4 == 0) {
        return 0;
      }
      if (bVar4 < 3) {
        return 2;
      }
    }
  }
  return 1;
}



// ==== 80231ed0  FUN_80231ed0 ====

undefined4 FUN_80231ed0(void)

{
  zz_023ccb4_();
  return 0;
}



// ==== 80231ef4  FUN_80231ef4 ====

uint FUN_80231ef4(void)

{
  uint uVar1;
  int iVar2;
  undefined1 auStack_808 [2052];
  
  uVar1 = zz_023ccb8_();
  if ((int)uVar1 < 1) {
    uVar1 = 0;
  }
  else {
    iVar2 = zz_023ccc0_();
    if (iVar2 == 0) {
      CircleBufferWriteBytes(-0x7fc07c88,auStack_808,uVar1);
    }
    else {
      uVar1 = 0xffffd8e7;
    }
  }
  return uVar1;
}



// ==== 80231f64  FUN_80231f64 ====

undefined4 FUN_80231f64(void)

{
  zz_023ccd0_();
  return 0;
}



// ==== 80231f88  FUN_80231f88 ====

undefined4 FUN_80231f88(void)

{
  zz_023ccd4_();
  return 0;
}



// ==== 80231fac  FUN_80231fac ====

undefined4 FUN_80231fac(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_80436848 == 0) {
    zz_02327c8_();
    uVar1 = 0xffffd8ef;
  }
  else {
    zz_02327c8_();
    for (; 0 < param_2; param_2 = param_2 - iVar2) {
      zz_02327c8_();
      iVar2 = zz_023ccc8_();
      if (iVar2 == 0) break;
    }
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8023206c  FUN_8023206c ====

int FUN_8023206c(void *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 auStack_818 [2052];
  
  iVar2 = 0;
  if (DAT_80436848 == 0) {
    iVar2 = -0x2711;
  }
  else {
    zz_02327c8_();
    while (uVar1 = zz_0232474_(-0x7fc07c88), uVar1 < param_2) {
      iVar2 = 0;
      uVar1 = zz_023ccb8_();
      if ((uVar1 != 0) && (iVar2 = zz_023ccc0_(), iVar2 == 0)) {
        CircleBufferWriteBytes(-0x7fc07c88,auStack_818,uVar1);
      }
    }
    if (iVar2 == 0) {
      CircleBufferReadBytes((int *)&DAT_803f8378,param_1,param_2);
    }
    else {
      zz_02327c8_();
    }
  }
  return iVar2;
}



// ==== 8023218c  FUN_8023218c ====

undefined4 FUN_8023218c(void)

{
  zz_02327c8_();
  zz_023ccb0_();
  zz_02327c8_();
  CircleBufferInitialize((undefined4 *)&DAT_803f8378,&DAT_803f7b78,0x800);
  return 0;
}



// ==== 80232214  CircleBufferReadBytes ====

undefined4 CircleBufferReadBytes(int *param_1,void *param_2,uint param_3)

{
  undefined4 uVar1;
  void *__src;
  uint __n;
  
  if ((uint)param_1[4] < param_3) {
    uVar1 = 0xffffffff;
  }
  else {
    zz_023283c_(param_1 + 6);
    __src = (void *)*param_1;
    __n = param_1[3] - ((int)__src - param_1[2]);
    if (param_3 < __n) {
      gnt4_memcpy(param_2,__src,param_3);
      *param_1 = *param_1 + param_3;
    }
    else {
      gnt4_memcpy(param_2,__src,__n);
      gnt4_memcpy((void *)((int)param_2 + __n),(void *)param_1[2],param_3 - __n);
      *param_1 = (param_1[2] + param_3) - __n;
    }
    if (param_1[3] == *param_1 - param_1[2]) {
      *param_1 = param_1[2];
    }
    param_1[5] = param_1[5] + param_3;
    param_1[4] = param_1[4] - param_3;
    zz_0232818_();
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8023231c  CircleBufferWriteBytes ====

undefined4 CircleBufferWriteBytes(int param_1,void *param_2,uint param_3)

{
  undefined4 uVar1;
  void *__dest;
  uint __n;
  
  if (*(uint *)(param_1 + 0x14) < param_3) {
    uVar1 = 0xffffffff;
  }
  else {
    zz_023283c_((undefined4 *)(param_1 + 0x18));
    __dest = *(void **)(param_1 + 4);
    __n = *(int *)(param_1 + 0xc) - ((int)__dest - *(int *)(param_1 + 8));
    if (__n < param_3) {
      gnt4_memcpy(__dest,param_2,__n);
      gnt4_memcpy(*(void **)(param_1 + 8),(void *)((int)param_2 + __n),param_3 - __n);
      *(uint *)(param_1 + 4) = (*(int *)(param_1 + 8) + param_3) - __n;
    }
    else {
      gnt4_memcpy(__dest,param_2,param_3);
      *(uint *)(param_1 + 4) = *(int *)(param_1 + 4) + param_3;
    }
    if (*(int *)(param_1 + 0xc) == *(int *)(param_1 + 4) - *(int *)(param_1 + 8)) {
      *(int *)(param_1 + 4) = *(int *)(param_1 + 8);
    }
    *(uint *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) - param_3;
    *(uint *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_3;
    zz_0232818_();
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80232424  CircleBufferInitialize ====

void CircleBufferInitialize(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  param_1[2] = param_2;
  param_1[3] = param_3;
  *param_1 = param_1[2];
  param_1[1] = param_1[2];
  param_1[4] = 0;
  param_1[5] = param_1[3];
  zz_023286c_();
  return;
}



// ==== 80232474  zz_0232474_ ====

undefined4 zz_0232474_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}



// ==== 8023247c  FUN_8023247c ====

undefined4 FUN_8023247c(void)

{
  DBInitInterrupts();
  return 0;
}



// ==== 802324a0  FUN_802324a0 ====

uint FUN_802324a0(void)

{
  uint uVar1;
  int iVar2;
  undefined4 auStack_508 [321];
  
  uVar1 = DBQueryData();
  if ((int)uVar1 < 1) {
    uVar1 = 0;
  }
  else {
    iVar2 = DBRead(auStack_508,uVar1);
    if (iVar2 == 0) {
      CircleBufferWriteBytes(-0x7fc07768,auStack_508,uVar1);
    }
    else {
      uVar1 = 0xffffd8e7;
    }
  }
  return uVar1;
}



// ==== 80232510  FUN_80232510 ====

undefined4 FUN_80232510(void)

{
  zz_023ccec_();
  return 0;
}



// ==== 80232534  FUN_80232534 ====

undefined4 FUN_80232534(void)

{
  zz_023cce8_();
  return 0;
}



// ==== 80232558  FUN_80232558 ====

undefined4 FUN_80232558(undefined4 *param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_80436850 == 0) {
    zz_02327c8_();
    uVar1 = 0xffffd8ef;
  }
  else {
    zz_02327c8_();
    for (; 0 < (int)param_2; param_2 = param_2 - iVar2) {
      zz_02327c8_();
      iVar2 = DBWrite(param_1,param_2);
      if (iVar2 == 0) break;
      param_1 = (undefined4 *)((int)param_1 + iVar2);
    }
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80232618  FUN_80232618 ====

int FUN_80232618(void *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 auStack_518 [320];
  
  iVar2 = 0;
  if (DAT_80436850 == 0) {
    iVar2 = -0x2711;
  }
  else {
    zz_02327c8_();
    while (uVar1 = zz_0232474_(-0x7fc07768), uVar1 < param_2) {
      iVar2 = 0;
      uVar1 = DBQueryData();
      if ((uVar1 != 0) && (iVar2 = DBRead(auStack_518,param_2), iVar2 == 0)) {
        CircleBufferWriteBytes(-0x7fc07768,auStack_518,uVar1);
      }
    }
    if (iVar2 == 0) {
      CircleBufferReadBytes((int *)&DAT_803f8898,param_1,param_2);
    }
    else {
      zz_02327c8_();
    }
  }
  return iVar2;
}



// ==== 80232740  FUN_80232740 ====

undefined4 FUN_80232740(undefined4 *param_1,undefined4 param_2)

{
  zz_02327c8_();
  DBInitComm(param_1,param_2);
  zz_02327c8_();
  CircleBufferInitialize((undefined4 *)&DAT_803f8898,&DAT_803f8398,0x500);
  return 0;
}



// ==== 802327c8  zz_02327c8_ ====

void zz_02327c8_(void)

{
  return;
}



// ==== 80232818  zz_0232818_ ====

void zz_0232818_(void)

{
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8023283c  zz_023283c_ ====

void zz_023283c_(undefined4 *param_1)

{
  ulonglong uVar1;
  
  uVar1 = gnt4_OSDisableInterrupts_bl();
  *param_1 = (int)(uVar1 >> 0x20);
  return;
}



// ==== 8023286c  zz_023286c_ ====

void zz_023286c_(void)

{
  return;
}



// ==== 80232870  __va_arg ====

int * __va_arg(char *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  char *pcVar3;
  int *piVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  
  cVar6 = *param_1;
  iVar1 = 8;
  iVar7 = 4;
  cVar8 = '\x01';
  uVar2 = 0;
  iVar9 = 0;
  iVar10 = 4;
  pcVar3 = param_1;
  if (param_2 == 3) {
    cVar6 = param_1[1];
    pcVar3 = param_1 + 1;
    iVar7 = 8;
    iVar9 = 0x20;
    iVar10 = 8;
  }
  uVar5 = (uint)cVar6;
  if (param_2 == 2) {
    iVar7 = 8;
    iVar1 = 7;
    uVar2 = (uint)((uVar5 & 1) != 0);
    cVar8 = '\x02';
  }
  if ((int)uVar5 < iVar1) {
    iVar1 = *(int *)(param_1 + 8);
    *pcVar3 = (char)(uVar5 + uVar2) + cVar8;
    piVar4 = (int *)(iVar1 + iVar9 + (uVar5 + uVar2) * iVar10);
  }
  else {
    *pcVar3 = '\b';
    piVar4 = (int *)(~(iVar7 - 1U) & (iVar7 + *(int *)(param_1 + 4)) - 1U);
    *(int *)(param_1 + 4) = (int)piVar4 + iVar7;
  }
  if (param_2 == 0) {
    piVar4 = (int *)*piVar4;
  }
  return piVar4;
}



// ==== 80232938  __destroy_global_chain ====

void __destroy_global_chain(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  while (DAT_80436858 != (int *)0x0) {
    puVar1 = DAT_80436858 + 1;
    puVar2 = DAT_80436858 + 2;
    DAT_80436858 = (int *)*DAT_80436858;
    (*(code *)*puVar1)(*puVar2,0xffffffff);
  }
  return;
}



// ==== 80232980  gnt4-__cvt_fp2unsigned-bl ====

int gnt4___cvt_fp2unsigned_bl(double param_1)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = 0;
  if ((DAT_802b4d08 <= param_1) && (iVar1 = -1, param_1 < DAT_802b4d10)) {
    bVar2 = DAT_802b4d18 <= param_1;
    if (bVar2) {
      param_1 = param_1 - DAT_802b4d18;
    }
    iVar1 = (int)param_1;
    if (bVar2) {
      iVar1 = iVar1 + -0x80000000;
    }
  }
  return iVar1;
}



// ==== 80232a08  zz_0232a10_ ====

void zz_0232a10_(void)

{
  int in_r11;
  undefined8 in_f25;
  undefined8 in_f26;
  undefined8 in_f27;
  undefined8 in_f28;
  undefined8 in_f29;
  undefined8 in_f30;
  undefined8 in_f31;
  
  *(undefined8 *)(in_r11 + -0x38) = in_f25;
  *(undefined8 *)(in_r11 + -0x30) = in_f26;
  *(undefined8 *)(in_r11 + -0x28) = in_f27;
  *(undefined8 *)(in_r11 + -0x20) = in_f28;
  *(undefined8 *)(in_r11 + -0x18) = in_f29;
  *(undefined8 *)(in_r11 + -0x10) = in_f30;
  *(undefined8 *)(in_r11 + -8) = in_f31;
  return;
}



// ==== 80232a10  FUN_80232a10 ====

void FUN_80232a10(void)

{
  int in_r11;
  undefined8 in_f27;
  undefined8 in_f28;
  undefined8 in_f29;
  undefined8 in_f30;
  undefined8 in_f31;
  
  *(undefined8 *)(in_r11 + -0x28) = in_f27;
  *(undefined8 *)(in_r11 + -0x20) = in_f28;
  *(undefined8 *)(in_r11 + -0x18) = in_f29;
  *(undefined8 *)(in_r11 + -0x10) = in_f30;
  *(undefined8 *)(in_r11 + -8) = in_f31;
  return;
}



// ==== 80232a54  zz_0232a54_ ====

void zz_0232a54_(void)

{
  return;
}



// ==== 80232a5c  FUN_80232a5c ====

void FUN_80232a5c(void)

{
  return;
}



// ==== 80232a74  gnt4-__save_gpr ====

void gnt4___save_gpr(void)

{
  int in_r11;
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
  
  *(undefined4 *)(in_r11 + -0x48) = unaff_r14;
  *(undefined4 *)(in_r11 + -0x44) = unaff_r15;
  *(undefined4 *)(in_r11 + -0x40) = unaff_r16;
  *(undefined4 *)(in_r11 + -0x3c) = unaff_r17;
  *(undefined4 *)(in_r11 + -0x38) = unaff_r18;
  *(undefined4 *)(in_r11 + -0x34) = unaff_r19;
  *(undefined4 *)(in_r11 + -0x30) = unaff_r20;
  *(undefined4 *)(in_r11 + -0x2c) = unaff_r21;
  *(undefined4 *)(in_r11 + -0x28) = unaff_r22;
  *(undefined4 *)(in_r11 + -0x24) = unaff_r23;
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232a88  gnt4-_savegpr_19-bl ====

void gnt4__savegpr_19_bl(void)

{
  int in_r11;
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
  
  *(undefined4 *)(in_r11 + -0x34) = unaff_r19;
  *(undefined4 *)(in_r11 + -0x30) = unaff_r20;
  *(undefined4 *)(in_r11 + -0x2c) = unaff_r21;
  *(undefined4 *)(in_r11 + -0x28) = unaff_r22;
  *(undefined4 *)(in_r11 + -0x24) = unaff_r23;
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232a8c  gnt4-_savegpr_20-bl ====

void gnt4__savegpr_20_bl(void)

{
  int in_r11;
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
  
  *(undefined4 *)(in_r11 + -0x30) = unaff_r20;
  *(undefined4 *)(in_r11 + -0x2c) = unaff_r21;
  *(undefined4 *)(in_r11 + -0x28) = unaff_r22;
  *(undefined4 *)(in_r11 + -0x24) = unaff_r23;
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232a94  gnt4-_savegpr_22-bl ====

void gnt4__savegpr_22_bl(void)

{
  int in_r11;
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
  
  *(undefined4 *)(in_r11 + -0x28) = unaff_r22;
  *(undefined4 *)(in_r11 + -0x24) = unaff_r23;
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232a98  gnt4-_savegpr_23-bl ====

void gnt4__savegpr_23_bl(void)

{
  int in_r11;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  
  *(undefined4 *)(in_r11 + -0x24) = unaff_r23;
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232a9c  gnt4-_savegpr_24-bl ====

void gnt4__savegpr_24_bl(void)

{
  int in_r11;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  
  *(undefined4 *)(in_r11 + -0x20) = unaff_r24;
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232aa0  gnt4-_savegpr_25-bl ====

void gnt4__savegpr_25_bl(void)

{
  int in_r11;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  
  *(undefined4 *)(in_r11 + -0x1c) = unaff_r25;
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232aa4  gnt4-_savegpr_26-bl ====

void gnt4__savegpr_26_bl(void)

{
  int in_r11;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  
  *(undefined4 *)(in_r11 + -0x18) = unaff_r26;
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232aa8  gnt4-_savegpr_27-bl ====

void gnt4__savegpr_27_bl(void)

{
  int in_r11;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  
  *(undefined4 *)(in_r11 + -0x14) = unaff_r27;
  *(undefined4 *)(in_r11 + -0x10) = unaff_r28;
  *(undefined4 *)(in_r11 + -0xc) = unaff_r29;
  *(undefined4 *)(in_r11 + -8) = unaff_r30;
  *(undefined4 *)(in_r11 + -4) = unaff_r31;
  return;
}



// ==== 80232ac0  gnt4-__restore_gpr ====

void gnt4___restore_gpr(void)

{
  return;
}



// ==== 80232ad4  gnt4-_restgpr_19-bl ====

void gnt4__restgpr_19_bl(void)

{
  return;
}



// ==== 80232ad8  gnt4-_restgpr_20-bl ====

void gnt4__restgpr_20_bl(void)

{
  return;
}



// ==== 80232ae0  gnt4-_restgpr_22-bl ====

void gnt4__restgpr_22_bl(void)

{
  return;
}



// ==== 80232ae4  gnt4-_restgpr_23-bl ====

void gnt4__restgpr_23_bl(void)

{
  return;
}



// ==== 80232ae8  gnt4-_restgpr_24-bl ====

void gnt4__restgpr_24_bl(void)

{
  return;
}



// ==== 80232aec  gnt4-_restgpr_25-bl ====

void gnt4__restgpr_25_bl(void)

{
  return;
}



// ==== 80232af0  gnt4-_restgpr_26-bl ====

void gnt4__restgpr_26_bl(void)

{
  return;
}



// ==== 80232af4  gnt4-_restgpr_27-bl ====

void gnt4__restgpr_27_bl(void)

{
  return;
}



// ==== 80232b0c  zz_0232b0c_ ====

undefined8 zz_0232b0c_(uint param_1,uint param_2,int param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  bool bVar12;
  bool bVar13;
  
  iVar3 = countLeadingZeros(param_1);
  iVar9 = countLeadingZeros(param_2);
  if (param_1 == 0) {
    iVar3 = iVar9 + 0x20;
  }
  iVar9 = countLeadingZeros(param_3);
  iVar11 = countLeadingZeros(param_4);
  if (param_3 == 0) {
    iVar9 = iVar11 + 0x20;
  }
  if (iVar3 <= iVar9) {
    iVar11 = 0x40 - (iVar9 + 1);
    iVar9 = iVar3 + iVar11;
    iVar11 = (0x40 - iVar3) - iVar11;
    if (iVar11 < 0x20) {
      uVar7 = param_2 >> iVar11 | param_1 << 0x20 - iVar11;
      uVar6 = param_1 >> iVar11;
    }
    else {
      uVar7 = param_1 >> iVar11 + -0x20;
      uVar6 = 0;
    }
    if (iVar9 < 0x20) {
      uVar4 = param_1 << iVar9 | param_2 >> 0x20 - iVar9;
      uVar5 = param_2 << iVar9;
    }
    else {
      uVar4 = param_2 << iVar9 + -0x20;
      uVar5 = 0;
    }
    bVar12 = false;
    do {
      bVar13 = CARRY4(uVar5,(uint)bVar12);
      uVar1 = uVar5 + bVar12;
      bVar12 = CARRY4(uVar5,uVar1);
      uVar5 = uVar5 + uVar1;
      uVar1 = (uint)(bVar13 || bVar12);
      bVar13 = CARRY4(uVar4,uVar1);
      uVar1 = uVar4 + uVar1;
      bVar12 = CARRY4(uVar4,uVar1);
      uVar4 = uVar4 + uVar1;
      uVar1 = (uint)(bVar13 || bVar12);
      uVar2 = uVar7 + uVar1;
      uVar8 = uVar7 + uVar2;
      uVar1 = uVar6 * 2 + (uint)(CARRY4(uVar7,uVar1) || CARRY4(uVar7,uVar2));
      uVar2 = (uint)(uVar8 < param_4) + param_3;
      uVar10 = uVar1 - uVar2;
      uVar6 = uVar1;
      uVar7 = uVar8;
      if (-1 < (int)uVar10) {
        uVar6 = uVar10;
        uVar7 = uVar8 - param_4;
      }
      bVar12 = -1 < (int)uVar10 || uVar2 <= uVar1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    uVar6 = uVar5 + bVar12;
    return CONCAT44(uVar4 * 2 + (uint)(CARRY4(uVar5,(uint)bVar12) || CARRY4(uVar5,uVar6)),
                    uVar5 + uVar6);
  }
  return 0;
}



// ==== 80232bf8  gnt4-__div2i ====

undefined8 gnt4___div2i(uint param_1,uint param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  bool bVar14;
  bool bVar15;
  
  uVar3 = param_1 & 0x80000000;
  if (uVar3 != 0) {
    bVar14 = param_2 != 0;
    param_2 = -param_2;
    param_1 = -(bVar14 + param_1);
  }
  uVar4 = param_3 & 0x80000000;
  if (uVar4 != 0) {
    bVar14 = param_4 != 0;
    param_4 = -param_4;
    param_3 = -(bVar14 + param_3);
  }
  iVar5 = countLeadingZeros(param_1);
  iVar11 = countLeadingZeros(param_2);
  if (param_1 == 0) {
    iVar5 = iVar11 + 0x20;
  }
  iVar11 = countLeadingZeros(param_3);
  iVar13 = countLeadingZeros(param_4);
  if (param_3 == 0) {
    iVar11 = iVar13 + 0x20;
  }
  if (iVar11 < iVar5) {
    iVar11 = 0;
    iVar5 = 0;
  }
  else {
    iVar13 = 0x40 - (iVar11 + 1);
    iVar11 = iVar5 + iVar13;
    iVar13 = (0x40 - iVar5) - iVar13;
    if (iVar13 < 0x20) {
      uVar9 = param_2 >> iVar13 | param_1 << 0x20 - iVar13;
      uVar8 = param_1 >> iVar13;
    }
    else {
      uVar9 = param_1 >> iVar13 + -0x20;
      uVar8 = 0;
    }
    if (iVar11 < 0x20) {
      uVar6 = param_1 << iVar11 | param_2 >> 0x20 - iVar11;
      uVar7 = param_2 << iVar11;
    }
    else {
      uVar6 = param_2 << iVar11 + -0x20;
      uVar7 = 0;
    }
    bVar14 = false;
    do {
      bVar15 = CARRY4(uVar7,(uint)bVar14);
      uVar1 = uVar7 + bVar14;
      bVar14 = CARRY4(uVar7,uVar1);
      uVar7 = uVar7 + uVar1;
      uVar1 = (uint)(bVar15 || bVar14);
      bVar15 = CARRY4(uVar6,uVar1);
      uVar1 = uVar6 + uVar1;
      bVar14 = CARRY4(uVar6,uVar1);
      uVar6 = uVar6 + uVar1;
      uVar1 = (uint)(bVar15 || bVar14);
      uVar2 = uVar9 + uVar1;
      uVar10 = uVar9 + uVar2;
      uVar1 = uVar8 * 2 + (uint)(CARRY4(uVar9,uVar1) || CARRY4(uVar9,uVar2));
      uVar2 = (uVar10 < param_4) + param_3;
      uVar12 = uVar1 - uVar2;
      uVar8 = uVar1;
      uVar9 = uVar10;
      if (-1 < (int)uVar12) {
        uVar8 = uVar12;
        uVar9 = uVar10 - param_4;
      }
      bVar14 = -1 < (int)uVar12 || uVar2 <= uVar1;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    uVar8 = uVar7 + bVar14;
    iVar11 = uVar7 + uVar8;
    iVar5 = uVar6 * 2 + (uint)(CARRY4(uVar7,(uint)bVar14) || CARRY4(uVar7,uVar8));
    if (uVar3 != uVar4) {
      bVar14 = iVar11 != 0;
      iVar11 = -iVar11;
      iVar5 = -((uint)bVar14 + iVar5);
    }
  }
  return CONCAT44(iVar5,iVar11);
}



// ==== 80232d30  __mod2u ====

undefined8 __mod2u(uint param_1,uint param_2,int param_3,uint param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  bool bVar12;
  bool bVar13;
  
  iVar3 = countLeadingZeros(param_1);
  iVar9 = countLeadingZeros(param_2);
  if (param_1 == 0) {
    iVar3 = iVar9 + 0x20;
  }
  iVar9 = countLeadingZeros(param_3);
  iVar11 = countLeadingZeros(param_4);
  if (param_3 == 0) {
    iVar9 = iVar11 + 0x20;
  }
  if (iVar9 < iVar3) {
    return CONCAT44(param_1,param_2);
  }
  iVar11 = 0x40 - (iVar9 + 1);
  iVar9 = iVar3 + iVar11;
  iVar11 = (0x40 - iVar3) - iVar11;
  if (iVar11 < 0x20) {
    uVar7 = param_2 >> iVar11 | param_1 << 0x20 - iVar11;
    uVar6 = param_1 >> iVar11;
  }
  else {
    uVar7 = param_1 >> iVar11 + -0x20;
    uVar6 = 0;
  }
  if (iVar9 < 0x20) {
    uVar4 = param_1 << iVar9 | param_2 >> 0x20 - iVar9;
    uVar5 = param_2 << iVar9;
  }
  else {
    uVar4 = param_2 << iVar9 + -0x20;
    uVar5 = 0;
  }
  bVar12 = false;
  do {
    bVar13 = CARRY4(uVar5,(uint)bVar12);
    uVar1 = uVar5 + bVar12;
    bVar12 = CARRY4(uVar5,uVar1);
    uVar5 = uVar5 + uVar1;
    uVar1 = (uint)(bVar13 || bVar12);
    bVar13 = CARRY4(uVar4,uVar1);
    uVar1 = uVar4 + uVar1;
    bVar12 = CARRY4(uVar4,uVar1);
    uVar4 = uVar4 + uVar1;
    uVar1 = (uint)(bVar13 || bVar12);
    uVar2 = uVar7 + uVar1;
    uVar8 = uVar7 + uVar2;
    uVar1 = uVar6 * 2 + (uint)(CARRY4(uVar7,uVar1) || CARRY4(uVar7,uVar2));
    uVar2 = (uint)(uVar8 < param_4) + param_3;
    uVar10 = uVar1 - uVar2;
    uVar6 = uVar1;
    uVar7 = uVar8;
    if (-1 < (int)uVar10) {
      uVar6 = uVar10;
      uVar7 = uVar8 - param_4;
    }
    bVar12 = -1 < (int)uVar10 || uVar2 <= uVar1;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  return CONCAT44(uVar6,uVar7);
}



// ==== 80232e14  gnt4-__mod2i ====

undefined8 gnt4___mod2i(uint param_1,uint param_2,int param_3,uint param_4)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  bool bVar12;
  
  bVar1 = (int)param_1 < 0;
  if (bVar1) {
    bVar11 = param_2 != 0;
    param_2 = -param_2;
    param_1 = -(bVar11 + param_1);
  }
  if (param_3 < 0) {
    bVar11 = param_4 != 0;
    param_4 = -param_4;
    param_3 = -((uint)bVar11 + param_3);
  }
  iVar2 = countLeadingZeros(param_1);
  iVar8 = countLeadingZeros(param_2);
  if (param_1 == 0) {
    iVar2 = iVar8 + 0x20;
  }
  iVar8 = countLeadingZeros(param_3);
  iVar10 = countLeadingZeros(param_4);
  if (param_3 == 0) {
    iVar8 = iVar10 + 0x20;
  }
  if (iVar2 <= iVar8) {
    iVar10 = 0x40 - (iVar8 + 1);
    iVar8 = iVar2 + iVar10;
    iVar10 = (0x40 - iVar2) - iVar10;
    if (iVar10 < 0x20) {
      uVar6 = param_2 >> iVar10 | param_1 << 0x20 - iVar10;
      uVar5 = param_1 >> iVar10;
    }
    else {
      uVar6 = param_1 >> iVar10 + -0x20;
      uVar5 = 0;
    }
    if (iVar8 < 0x20) {
      uVar3 = param_1 << iVar8 | param_2 >> 0x20 - iVar8;
      uVar4 = param_2 << iVar8;
    }
    else {
      uVar3 = param_2 << iVar8 + -0x20;
      uVar4 = 0;
    }
    bVar11 = false;
    param_1 = uVar5;
    param_2 = uVar6;
    do {
      bVar12 = CARRY4(uVar4,(uint)bVar11);
      uVar5 = uVar4 + bVar11;
      bVar11 = CARRY4(uVar4,uVar5);
      uVar4 = uVar4 + uVar5;
      uVar5 = (uint)(bVar12 || bVar11);
      bVar12 = CARRY4(uVar3,uVar5);
      uVar5 = uVar3 + uVar5;
      bVar11 = CARRY4(uVar3,uVar5);
      uVar3 = uVar3 + uVar5;
      uVar5 = (uint)(bVar12 || bVar11);
      uVar6 = param_2 + uVar5;
      uVar7 = param_2 + uVar6;
      uVar5 = param_1 * 2 + (uint)(CARRY4(param_2,uVar5) || CARRY4(param_2,uVar6));
      uVar6 = (uint)(uVar7 < param_4) + param_3;
      uVar9 = uVar5 - uVar6;
      param_1 = uVar5;
      param_2 = uVar7;
      if (-1 < (int)uVar9) {
        param_1 = uVar9;
        param_2 = uVar7 - param_4;
      }
      bVar11 = -1 < (int)uVar9 || uVar6 <= uVar5;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  if (bVar1) {
    return CONCAT44(-((param_2 != 0) + param_1),-param_2);
  }
  return CONCAT44(param_1,param_2);
}



// ==== 80232f20  gnt4-__shl2i ====

undefined8 gnt4___shl2i(int param_1,uint param_2,int param_3)

{
  return CONCAT44(param_1 << param_3 | param_2 >> 0x20 - param_3 | param_2 << param_3 + -0x20,
                  param_2 << param_3);
}



// ==== 80232f44  gnt4-__shr2u ====

undefined8 gnt4___shr2u(uint param_1,uint param_2,int param_3)

{
  return CONCAT44(param_1 >> param_3,
                  param_2 >> param_3 | param_1 << 0x20 - param_3 | param_1 >> param_3 + -0x20);
}



// ==== 80232f68  gnt4-__shr2i ====

undefined8 gnt4___shr2i(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = param_2 >> param_3 | param_1 << 0x20 - param_3;
  if (0 < (int)(param_3 - 0x20)) {
    uVar1 = uVar1 | param_1 >> (param_3 - 0x20 & 0x3f);
  }
  return CONCAT44(param_1 >> (param_3 & 0x3f),uVar1);
}



// ==== 80232f90  zz_0232f90_ ====

undefined8 zz_0232f90_(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  
  uVar1 = param_1 & 0x80000000;
  if (uVar1 != 0) {
    bVar5 = param_2 != 0;
    param_2 = -param_2;
    param_1 = -(bVar5 + param_1);
  }
  if (param_1 != 0 || param_2 != 0) {
    uVar2 = countLeadingZeros(param_1);
    uVar4 = countLeadingZeros(param_2);
    iVar3 = uVar2 + ((int)(uVar2 << 0x1a | uVar2 >> 6) >> 0x1f & uVar4);
    uVar2 = param_1 << iVar3 | param_2 >> 0x20 - iVar3 | param_2 << iVar3 + -0x20;
    uVar4 = param_2 << iVar3;
    iVar3 = 0x43e - iVar3;
    if ((0x3ff < (uVar4 & 0x7ff)) && ((0x400 < (uVar4 & 0x7ff) || ((uVar4 & 0x800) != 0)))) {
      bVar5 = 0xfffff7ff < uVar4;
      uVar4 = uVar4 + 0x800;
      bVar6 = CARRY4(uVar2,(uint)bVar5);
      uVar2 = uVar2 + bVar5;
      iVar3 = iVar3 + (uint)bVar6;
    }
    param_2 = uVar2 << 0x15 | uVar4 >> 0xb;
    param_1 = uVar1 | iVar3 << 0x14 | uVar2 >> 0xb & 0xfffff;
  }
  return CONCAT44(param_1,param_2);
}



// ==== 80233040  __cvt_dbl_usll ====

undefined8 __cvt_dbl_usll(ulonglong param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_8;
  undefined4 uStack_4;
  
  local_8 = (uint)(param_1 >> 0x20);
  uStack_4 = (uint)param_1;
  uVar3 = local_8 >> 0x14 & 0x7ff;
  if (uVar3 < 0x3ff) {
    uVar2 = 0;
    uStack_4 = 0;
  }
  else {
    uVar2 = local_8 & 0xfffff | 0x100000;
    iVar4 = uVar3 - 0x433;
    if (iVar4 < 0) {
      iVar4 = -iVar4;
      uStack_4 = uStack_4 >> iVar4 | uVar2 << uVar3 - 0x413 | uVar2 >> iVar4 + -0x20;
      uVar2 = uVar2 >> iVar4;
    }
    else {
      if (10 < iVar4) {
        if ((param_1 & 0x8000000000000000) == 0) {
          uVar2 = 0x7fffffff;
          uStack_4 = 0xffffffff;
        }
        else {
          uVar2 = 0x80000000;
          uStack_4 = 0;
        }
        goto LAB_80233104;
      }
      uVar2 = uVar2 << iVar4 | uStack_4 >> 0x20 - iVar4 | uStack_4 << uVar3 - 0x453;
      uStack_4 = uStack_4 << iVar4;
    }
    if ((param_1 & 0x8000000000000000) != 0) {
      bVar1 = uStack_4 != 0;
      uStack_4 = -uStack_4;
      uVar2 = -(bVar1 + uVar2);
    }
  }
LAB_80233104:
  return CONCAT44(uVar2,uStack_4);
}



// ==== 8023310c  __sys_free ====

void __sys_free(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined8 uVar3;
  
  if (DAT_80435c60 == -1) {
    uVar3 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             s_GCN_Mem_Alloc_c___InitDefaultHea_802b4d20,param_10,param_11,param_12,
                             param_13,param_14,param_15,param_16);
    gnt4_OSReport_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_Metrowerks_CW_runtime_library_in_802b4d58,extraout_r4,param_11,param_12,
                     param_13,param_14,param_15,param_16);
    iVar1 = gnt4_OSGetArenaLo_bl();
    uVar2 = gnt4_OSGetArenaHi_bl();
    iVar1 = gnt4_OSInitAlloc_bl(iVar1,uVar2,1);
    gnt4_OSSetArenaLo_bl(iVar1);
    iVar1 = gnt4_OSCreateHeap_bl(iVar1 + 0x1fU & 0xffffffe0,uVar2 & 0xffffffe0);
    gnt4_OSSetCurrentHeap_bl(iVar1);
    gnt4_OSSetArenaLo_bl(uVar2 & 0xffffffe0);
  }
  gnt4_OSFreeToHeap_bl(DAT_80435c60,param_9);
  return;
}



// ==== 802331c4  FUN_802331c4 ====

void FUN_802331c4(void)

{
  undefined **ppuVar1;
  
  if (DAT_80436860 == 0) {
    zz_02358d0_();
    zz_02358cc_();
    __destroy_global_chain();
    for (ppuVar1 = &PTR___destroy_global_chain_802b0180; (code *)*ppuVar1 != (code *)0x0;
        ppuVar1 = ppuVar1 + 1) {
      (*(code *)*ppuVar1)();
    }
    if (DAT_80436868 != (code *)0x0) {
      (*DAT_80436868)();
      DAT_80436868 = (code *)0x0;
    }
  }
  zz_02358d0_();
  while (0 < DAT_80436864) {
    DAT_80436864 = DAT_80436864 + -1;
    (**(code **)(&DAT_803f88b8 + DAT_80436864 * 4))();
  }
  zz_02358cc_();
  zz_02358d4_();
  if (DAT_8043686c != (code *)0x0) {
    (*DAT_8043686c)();
    DAT_8043686c = (code *)0x0;
  }
  gnt4__ExitProcess_bl();
  return;
}



// ==== 802332b4  free ====

void free(void *__ptr)

{
  undefined8 uVar1;
  undefined8 in_f2;
  undefined8 in_f3;
  undefined8 in_f4;
  undefined8 in_f5;
  undefined8 in_f6;
  undefined8 in_f7;
  undefined8 in_f8;
  
  uVar1 = zz_02358d0_();
  if (DAT_80436870 == '\0') {
    gnt4_memset(&DAT_803f89b8,0,0x34);
    DAT_80436870 = '\x01';
  }
  __pool_free(uVar1,in_f2,in_f3,in_f4,in_f5,in_f6,in_f7,in_f8,(undefined4 *)&DAT_803f89b8,__ptr);
  zz_02358cc_();
  return;
}



// ==== 80233324  __pool_free ====

void __pool_free(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 *param_9,int *param_10)

{
  uint uVar1;
  
  if (param_10 != (int *)0x0) {
    if ((param_10[-1] & 1U) == 0) {
      uVar1 = *(uint *)(param_10[-1] + 8);
    }
    else {
      uVar1 = (param_10[-2] & 0xfffffff8U) - 8;
    }
    if (uVar1 < 0x45) {
      deallocate_from_fixed_pools
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 uVar1);
    }
    else {
      deallocate_from_var_pools
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
    }
  }
  return;
}



// ==== 8023337c  deallocate_from_fixed_pools ====

void deallocate_from_fixed_pools
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 *param_9,int *param_10,uint param_11)

{
  int *piVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = 0;
  for (puVar3 = &DAT_802b4d98; *puVar3 < param_11; puVar3 = puVar3 + 1) {
    iVar4 = iVar4 + 1;
  }
  piVar1 = (int *)param_10[-1];
  piVar2 = param_9 + iVar4 * 2 + 1;
  if (piVar1[3] == 0) {
    if ((int *)piVar2[1] != piVar1) {
      if ((int *)*piVar2 == piVar1) {
        piVar2[1] = *(int *)piVar2[1];
        *piVar2 = *(int *)*piVar2;
      }
      else {
        *(int *)(*piVar1 + 4) = piVar1[1];
        *(int *)piVar1[1] = *piVar1;
        piVar1[1] = piVar2[1];
        *piVar1 = *(int *)piVar1[1];
        *(int **)(*piVar1 + 4) = piVar1;
        *(int **)piVar1[1] = piVar1;
        piVar2[1] = (int)piVar1;
      }
    }
  }
  *param_10 = piVar1[3];
  piVar1[3] = (int)(param_10 + -1);
  iVar4 = piVar1[4];
  piVar1[4] = iVar4 + -1;
  if (iVar4 + -1 == 0) {
    if ((int *)piVar2[1] == piVar1) {
      piVar2[1] = piVar1[1];
    }
    if ((int *)*piVar2 == piVar1) {
      *piVar2 = *piVar1;
    }
    *(int *)(*piVar1 + 4) = piVar1[1];
    *(int *)piVar1[1] = *piVar1;
    if ((int *)piVar2[1] == piVar1) {
      piVar2[1] = 0;
    }
    if ((int *)*piVar2 == piVar1) {
      *piVar2 = 0;
    }
    deallocate_from_var_pools
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,piVar1);
  }
  return;
}



// ==== 802334d4  deallocate_from_var_pools ====

void deallocate_from_var_pools
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               undefined4 *param_9,int *param_10)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint *puVar6;
  uint uVar7;
  uint *puVar8;
  uint *in_r9;
  uint in_r10;
  
  puVar8 = (uint *)(param_10 + -2);
  uVar7 = param_10[-2] & 0xfffffff8;
  *puVar8 = param_10[-2] & 0xfffffffd;
  puVar6 = (uint *)((int)puVar8 + uVar7);
  piVar1 = (int *)(param_10[-1] & 0xfffffffe);
  *puVar6 = *puVar6 & 0xfffffffb;
  puVar6[-1] = uVar7;
  iVar2 = (piVar1[3] & 0xfffffff8U) - 4;
  if (*(int *)((int)piVar1 + iVar2) == 0) {
    *(uint **)((int)piVar1 + iVar2) = puVar8;
    *param_10 = (int)puVar8;
    param_10[1] = (int)puVar8;
  }
  else {
    *param_10 = *(int *)(*(int *)((int)piVar1 + iVar2) + 8);
    *(uint **)(*param_10 + 0xc) = puVar8;
    param_10[1] = *(int *)((int)piVar1 + iVar2);
    *(uint **)(*(int *)((int)piVar1 + iVar2) + 8) = puVar8;
    *(uint **)((int)piVar1 + iVar2) = puVar8;
    puVar6 = *(uint **)((int)piVar1 + iVar2);
    if (((*puVar6 & 4) == 0) && (uVar7 = puVar6[-1], (uVar7 & 2) == 0)) {
      puVar8 = (uint *)((int)puVar6 - uVar7);
      *puVar8 = *puVar8 & 7;
      *puVar8 = *puVar8 | uVar7 + (*puVar6 & 0xfffffff8) & 0xfffffff8;
      if ((*puVar8 & 2) == 0) {
        iVar4 = uVar7 + (*puVar6 & 0xfffffff8);
        *(int *)((int)puVar8 + iVar4 + -4) = iVar4;
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar6) {
        *(uint *)((int)piVar1 + iVar2) = (*(uint **)((int)piVar1 + iVar2))[3];
      }
      *(uint *)(puVar6[3] + 8) = puVar6[2];
      *(uint *)(*(int *)(puVar6[3] + 8) + 0xc) = puVar6[3];
      puVar6 = puVar8;
    }
    *(uint **)((int)piVar1 + iVar2) = puVar6;
    in_r9 = *(uint **)((int)piVar1 + iVar2);
    in_r10 = *in_r9 & 0xfffffff8;
    puVar8 = (uint *)((int)in_r9 + in_r10);
    uVar7 = *puVar8;
    if ((uVar7 & 2) == 0) {
      *in_r9 = *in_r9 & 7;
      uVar7 = in_r10 + (uVar7 & 0xfffffff8);
      *in_r9 = *in_r9 | uVar7;
      if ((*in_r9 & 2) == 0) {
        *(uint *)((int)in_r9 + (uVar7 - 4)) = uVar7;
      }
      if ((*in_r9 & 2) == 0) {
        *(uint *)((int)in_r9 + uVar7) = *(uint *)((int)in_r9 + uVar7) & 0xfffffffb;
      }
      else {
        *(uint *)((int)in_r9 + uVar7) = *(uint *)((int)in_r9 + uVar7) | 4;
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar8) {
        *(uint *)((int)piVar1 + iVar2) = (*(uint **)((int)piVar1 + iVar2))[3];
      }
      if (*(uint **)((int)piVar1 + iVar2) == puVar8) {
        *(undefined4 *)((int)piVar1 + iVar2) = 0;
      }
      *(uint *)(puVar8[3] + 8) = puVar8[2];
      *(uint *)(puVar8[2] + 0xc) = puVar8[3];
    }
  }
  uVar5 = piVar1[2];
  uVar7 = **(uint **)((int)piVar1 + iVar2) & 0xfffffff8;
  if (uVar5 < uVar7) {
    piVar1[2] = uVar7;
  }
  iVar2 = 0;
  if (((piVar1[4] & 2U) == 0) &&
     (uVar5 = piVar1[4] & 0xfffffff8, uVar5 == (piVar1[3] & 0xfffffff8U) - 0x18)) {
    iVar2 = 1;
  }
  if (iVar2 != 0) {
    piVar3 = (int *)piVar1[1];
    if (piVar3 == piVar1) {
      piVar3 = (int *)0x0;
    }
    if ((int *)*param_9 == piVar1) {
      *param_9 = piVar3;
    }
    if (piVar3 != (int *)0x0) {
      *piVar3 = *piVar1;
      *(int **)(*piVar3 + 4) = piVar3;
    }
    piVar1[1] = 0;
    *piVar1 = 0;
    __sys_free(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)piVar1,piVar1,
               piVar3,uVar5,iVar2,puVar8,in_r9,in_r10);
  }
  return;
}



// ==== 80233768  __flush_all ====

undefined4 __flush_all(void)

{
  FILE *__stream;
  int iVar1;
  undefined4 uVar2;
  
  __stream = (FILE *)&DAT_803ab308;
  uVar2 = 0;
  while( true ) {
    if (__stream == (FILE *)0x0) break;
    if (((*(ushort *)&__stream->_IO_read_ptr >> 6 & 7) != 0) &&
       (iVar1 = fflush(__stream), iVar1 != 0)) {
      uVar2 = 0xffffffff;
    }
    __stream = *(FILE **)&__stream->field_0x4c;
  }
  return uVar2;
}



// ==== 802337d8  FUN_802337d8 ====

void FUN_802337d8(void)

{
  FILE *pFVar1;
  FILE *__stream;
  
  zz_02358d0_();
  pFVar1 = (FILE *)&DAT_803ab308;
  while( true ) {
    __stream = pFVar1;
    if (__stream == (FILE *)0x0) break;
    if ((*(ushort *)&__stream->_IO_read_ptr >> 6 & 7) != 0) {
      fclose(__stream);
    }
    pFVar1 = *(FILE **)&__stream->field_0x4c;
    if (*(char *)&__stream->_IO_read_base == '\0') {
      *(ushort *)&__stream->_IO_read_ptr = *(ushort *)&__stream->_IO_read_ptr & 0xfe3f | 0xc0;
      if ((pFVar1 != (FILE *)0x0) && (*(char *)&pFVar1->_IO_read_base != '\0')) {
        *(undefined4 *)&__stream->field_0x4c = 0;
      }
    }
    else {
      free(__stream);
    }
  }
  zz_02358cc_();
  return;
}



// ==== 80233880  __num2dec ====

void __num2dec(double param_1,int param_2,char *param_3)

{
  byte bVar1;
  int iVar2;
  char *pcVar3;
  byte *pbVar4;
  int iVar5;
  short sVar6;
  
  sVar6 = *(short *)(param_2 + 2);
  __num2dec_internal(param_1,param_3);
  if ((byte)param_3[5] < 10) {
    if (0x24 < sVar6) {
      sVar6 = 0x24;
    }
    iVar5 = (int)sVar6;
    if ((0 < iVar5) && (iVar5 < (int)(uint)(byte)param_3[4])) {
      if ((byte)param_3[iVar5 + 5] < 6) {
        if ((byte)param_3[iVar5 + 5] < 5) {
          iVar2 = -1;
        }
        else {
          pcVar3 = param_3 + iVar5 + 6;
          iVar2 = (int)(param_3 + (byte)param_3[4] + 5) - (int)pcVar3;
          if (pcVar3 < param_3 + (byte)param_3[4] + 5) {
            do {
              if (*pcVar3 != '\0') {
                iVar2 = 1;
                goto LAB_8023394c;
              }
              pcVar3 = pcVar3 + 1;
              iVar2 = iVar2 + -1;
            } while (iVar2 != 0);
          }
          if ((param_3[iVar5 + 4] & 1U) == 0) {
            iVar2 = -1;
          }
          else {
            iVar2 = 1;
          }
        }
      }
      else {
        iVar2 = 1;
      }
LAB_8023394c:
      param_3[4] = (char)sVar6;
      if (-1 < iVar2) {
        for (pbVar4 = (byte *)(param_3 + 5 + iVar5 + -1); 8 < *pbVar4; pbVar4 = pbVar4 + -1) {
          if (pbVar4 == (byte *)(param_3 + 5)) {
            *pbVar4 = 1;
            *(short *)(param_3 + 2) = *(short *)(param_3 + 2) + 1;
            goto LAB_802339c8;
          }
          *pbVar4 = 0;
        }
        *pbVar4 = *pbVar4 + 1;
      }
    }
LAB_802339c8:
    while ((int)(uint)(byte)param_3[4] < iVar5) {
      bVar1 = param_3[4];
      param_3[4] = bVar1 + 1;
      param_3[bVar1 + 5] = '\0';
    }
    *(ushort *)(param_3 + 2) = *(short *)(param_3 + 2) - ((byte)param_3[4] - 1);
    for (iVar5 = 0; iVar5 < (int)(uint)(byte)param_3[4]; iVar5 = iVar5 + 1) {
      param_3[iVar5 + 5] = param_3[iVar5 + 5] + '0';
    }
  }
  return;
}



// ==== 80233a24  __num2dec_internal ====

void __num2dec_internal(double param_1,char *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  int iVar3;
  char cVar4;
  undefined1 *puVar5;
  uint uVar6;
  undefined1 *puVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  longlong lVar11;
  undefined8 uVar12;
  double local_a8;
  int local_a0 [2];
  undefined8 local_98;
  undefined8 local_88;
  double local_80;
  undefined4 auStack_78 [11];
  undefined1 local_4c [2];
  short local_4a;
  byte local_48;
  undefined1 local_47 [39];
  
  local_a8._0_4_ = (uint)((ulonglong)param_1 >> 0x20);
  cVar4 = -(char)((longlong)param_1 >> 0x3f);
  if (DOUBLE_8043cc38 == param_1) {
    *param_2 = cVar4;
    param_2[2] = '\0';
    param_2[3] = '\0';
    param_2[4] = '\x01';
    param_2[5] = '\0';
  }
  else {
    local_88._4_4_ = SUB84(param_1,0);
    if ((local_a8._0_4_ & 0x7ff00000) == 0x7ff00000) {
      if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
    }
    else if (((local_a8._0_4_ & 0x7ff00000) < 0x7ff00000) &&
            (((ulonglong)param_1 & 0x7ff0000000000000) == 0)) {
      if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
        uVar2 = 3;
      }
      else {
        uVar2 = 5;
      }
    }
    else {
      uVar2 = 4;
    }
    if (uVar2 < 3) {
      *param_2 = cVar4;
      param_2[2] = '\0';
      param_2[3] = '\0';
      param_2[4] = '\x01';
      if ((local_a8._0_4_ & 0x7ff00000) == 0x7ff00000) {
        if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
          iVar3 = 2;
        }
        else {
          iVar3 = 1;
        }
      }
      else if (((local_a8._0_4_ & 0x7ff00000) < 0x7ff00000) &&
              (((ulonglong)param_1 & 0x7ff0000000000000) == 0)) {
        if ((((ulonglong)param_1 & 0xfffff00000000) == 0) && (local_88._4_4_ == 0)) {
          iVar3 = 3;
        }
        else {
          iVar3 = 5;
        }
      }
      else {
        iVar3 = 4;
      }
      cVar4 = 'I';
      if (iVar3 == 1) {
        cVar4 = 'N';
      }
      param_2[5] = cVar4;
    }
    else {
      local_a8 = param_1;
      if (cVar4 != '\0') {
        local_a8 = -param_1;
      }
      local_88 = param_1;
      dVar10 = frexp(local_a8,local_a0);
      local_98._4_4_ = SUB84(dVar10,0);
      if (local_98._4_4_ == 0) {
        local_98._0_4_ = (uint)((ulonglong)dVar10 >> 0x20);
        uVar6 = 0x10;
        iVar9 = 0;
        iVar3 = 0x10;
        local_98._0_4_ = local_98._0_4_ | 0x100000;
        uVar2 = 0xffff;
        iVar8 = 0x20;
        while (iVar8 != 0) {
          if ((local_98._0_4_ & uVar2) == 0) {
            iVar9 = iVar9 + iVar3;
            local_98._0_4_ = local_98._0_4_ >> iVar3;
            iVar8 = iVar8 - iVar3;
          }
          else if (uVar2 == 1) break;
          if (1 < uVar6) {
            uVar6 = (int)uVar6 >> 1;
          }
          if (1 < uVar2) {
            uVar2 = uVar2 >> uVar6;
            iVar3 = iVar3 - uVar6;
          }
        }
        iVar9 = iVar9 + 0x20;
      }
      else {
        uVar6 = 0x10;
        iVar9 = 0;
        iVar8 = 0x20;
        iVar3 = 0x10;
        uVar2 = 0xffff;
        while (iVar8 != 0) {
          if ((local_98._4_4_ & uVar2) == 0) {
            iVar9 = iVar9 + iVar3;
            local_98._4_4_ = local_98._4_4_ >> iVar3;
            iVar8 = iVar8 - iVar3;
          }
          else if (uVar2 == 1) break;
          if (1 < uVar6) {
            uVar6 = (int)uVar6 >> 1;
          }
          if (1 < uVar2) {
            uVar2 = uVar2 >> uVar6;
            iVar3 = iVar3 - uVar6;
          }
        }
      }
      local_98 = dVar10;
      __two_exp(auStack_78,local_a0[0] - (0x35 - iVar9));
      dVar10 = ldexp(dVar10,0x35 - iVar9);
      modf(dVar10,&local_80);
      lVar11 = __cvt_dbl_usll((ulonglong)local_80);
      local_4c[0] = 0;
      if (lVar11 == 0) {
        local_4a = 0;
        local_48 = 1;
        local_47[0] = 0;
      }
      else {
        local_48 = 0;
        while( true ) {
          uVar2 = (uint)((ulonglong)lVar11 >> 0x20);
          if (lVar11 == 0) break;
          uVar12 = __mod2u(uVar2,(uint)lVar11,0,10);
          uVar6 = (uint)local_48;
          local_48 = local_48 + 1;
          local_47[uVar6] = (char)uVar12;
          lVar11 = zz_0232b0c_(uVar2,(uint)lVar11,0,10);
        }
        puVar5 = local_47 + local_48;
        for (puVar7 = local_47; puVar5 = puVar5 + -1, puVar7 < puVar5; puVar7 = puVar7 + 1) {
          uVar1 = *puVar7;
          *puVar7 = *puVar5;
          *puVar5 = uVar1;
        }
        local_4a = local_48 - 1;
      }
      __timesdec(param_2,(int)local_4c,(int)auStack_78);
      *param_2 = cVar4;
    }
  }
  return;
}



// ==== 80233dd8  __two_exp ====

void __two_exp(undefined4 *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  char *pcVar6;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined2 local_40;
  undefined4 local_3c;
  byte local_38 [48];
  
  switch(param_2) {
  case 0:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e74; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 1:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e76; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 2:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e78; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 3:
    iVar3 = 0;
    *(undefined2 *)((int)param_1 + 2) = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e7a; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 4:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e7c; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 5:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e7f; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 6:
    *(undefined2 *)((int)param_1 + 2) = 1;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e82; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 7:
    *(undefined2 *)((int)param_1 + 2) = 2;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e85; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 8:
    *(undefined2 *)((int)param_1 + 2) = 2;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e89; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffc0:
    *(undefined2 *)((int)param_1 + 2) = 0xffec;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4dd5; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  default:
    __two_exp(&local_3c,(int)param_2 / 2);
    __timesdec((undefined1 *)param_1,(int)&local_3c,(int)&local_3c);
    if ((param_2 & 1) != 0) {
      local_68 = *param_1;
      local_64 = param_1[1];
      local_60 = param_1[2];
      local_5c = param_1[3];
      local_58 = param_1[4];
      local_54 = param_1[5];
      local_50 = param_1[6];
      local_4c = param_1[7];
      local_48 = param_1[8];
      local_44 = param_1[9];
      local_40 = *(undefined2 *)(param_1 + 10);
      if ((int)param_2 < 1) {
        local_3c._2_2_ = 0xffff;
        uVar5 = 0;
        for (pcVar6 = &DAT_802b4e72; ((int)uVar5 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1)
        {
          local_38[uVar5 + 1] = *pcVar6 - 0x30;
          uVar5 = uVar5 + 1;
        }
        local_38[0] = (byte)uVar5;
        cVar1 = *pcVar6;
        if ((cVar1 != '\0') && ('\x04' < cVar1)) {
          if (cVar1 < '\x06') {
            do {
              pcVar6 = pcVar6 + 1;
              if (*pcVar6 == '\0') {
                if ((local_38[uVar5] & 1) == 0) goto LAB_80235534;
                break;
              }
            } while (*pcVar6 == '0');
          }
          for (pbVar4 = local_38 + 1 + ((uVar5 & 0xff) - 1); 8 < *pbVar4; pbVar4 = pbVar4 + -1) {
            if (pbVar4 == local_38 + 1) {
              *pbVar4 = 1;
              local_3c._2_2_ = 0;
              goto LAB_80235534;
            }
            *pbVar4 = 0;
          }
          *pbVar4 = *pbVar4 + 1;
        }
      }
      else {
        local_3c._2_2_ = 0;
        uVar5 = 0;
        for (pcVar6 = &DAT_802b4e76; ((int)uVar5 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1)
        {
          local_38[uVar5 + 1] = *pcVar6 - 0x30;
          uVar5 = uVar5 + 1;
        }
        local_38[0] = (byte)uVar5;
        cVar1 = *pcVar6;
        if ((cVar1 != '\0') && ('\x04' < cVar1)) {
          if (cVar1 < '\x06') {
            do {
              pcVar6 = pcVar6 + 1;
              if (*pcVar6 == '\0') {
                if ((local_38[uVar5] & 1) == 0) goto LAB_80235534;
                break;
              }
            } while (*pcVar6 == '0');
          }
          for (pbVar4 = local_38 + 1 + ((uVar5 & 0xff) - 1); 8 < *pbVar4; pbVar4 = pbVar4 + -1) {
            if (pbVar4 == local_38 + 1) {
              *pbVar4 = 1;
              local_3c._2_2_ = 1;
              goto LAB_80235534;
            }
            *pbVar4 = 0;
          }
          *pbVar4 = *pbVar4 + 1;
        }
      }
LAB_80235534:
      local_3c._0_1_ = 0;
      __timesdec((undefined1 *)param_1,(int)&local_68,(int)&local_3c);
    }
    break;
  case 0xffffffcb:
    *(undefined2 *)((int)param_1 + 2) = 0xfff0;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e03; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffe0:
    *(undefined2 *)((int)param_1 + 2) = 0xfff6;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e2a; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff0:
    *(undefined2 *)((int)param_1 + 2) = 0xfffb;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e42; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff8:
    *(undefined2 *)((int)param_1 + 2) = 0xfffd;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e4f; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffff9:
    *(undefined2 *)((int)param_1 + 2) = 0xfffd;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e56; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffa:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e5c; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffb:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e62; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffc:
    *(undefined2 *)((int)param_1 + 2) = 0xfffe;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e67; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffd:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e6b; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xfffffffe:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e6f; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
    break;
  case 0xffffffff:
    *(undefined2 *)((int)param_1 + 2) = 0xffff;
    iVar3 = 0;
    *(undefined1 *)param_1 = 0;
    for (pcVar6 = &DAT_802b4e72; (iVar3 < 0x24 && (*pcVar6 != '\0')); pcVar6 = pcVar6 + 1) {
      iVar2 = iVar3 + 5;
      iVar3 = iVar3 + 1;
      *(char *)((int)param_1 + iVar2) = *pcVar6 + -0x30;
    }
    *(char *)(param_1 + 1) = (char)iVar3;
    cVar1 = *pcVar6;
    if ((cVar1 != '\0') && ('\x04' < cVar1)) {
      if (cVar1 < '\x06') {
        do {
          pcVar6 = pcVar6 + 1;
          if (*pcVar6 == '\0') {
            if ((*(byte *)((int)param_1 + iVar3 + 4) & 1) == 0) {
              return;
            }
            break;
          }
        } while (*pcVar6 == '0');
      }
      for (pbVar4 = (byte *)((int)param_1 + 5) + (*(byte *)(param_1 + 1) - 1); 8 < *pbVar4;
          pbVar4 = pbVar4 + -1) {
        if (pbVar4 == (byte *)((int)param_1 + 5)) {
          *pbVar4 = 1;
          *(short *)((int)param_1 + 2) = *(short *)((int)param_1 + 2) + 1;
          return;
        }
        *pbVar4 = 0;
      }
      *pbVar4 = *pbVar4 + 1;
    }
  }
  return;
}



// ==== 8023555c  __timesdec ====

void __timesdec(undefined1 *param_1,int param_2,int param_3)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  byte *pbVar13;
  byte *pbVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  char cVar19;
  int iVar20;
  byte *pbVar21;
  byte *pbVar22;
  byte *pbVar23;
  int iVar24;
  uint uVar25;
  uint uVar26;
  byte *pbVar27;
  int iVar28;
  uint uVar29;
  byte abStack_68 [84];
  
  bVar15 = *(byte *)(param_3 + 4);
  bVar16 = *(byte *)(param_2 + 4);
  uVar29 = 0;
  iVar28 = (uint)bVar16 + (bVar15 - 1);
  pbVar23 = abStack_68 + iVar28 + 1;
  *param_1 = 0;
  pbVar22 = pbVar23;
  for (; 0 < iVar28; iVar28 = iVar28 + -1) {
    iVar24 = bVar15 - 1;
    iVar20 = (iVar28 - iVar24) + -1;
    if (iVar20 < 0) {
      iVar20 = 0;
      iVar24 = iVar28 + -1;
    }
    uVar26 = (uint)bVar16 - iVar20;
    pbVar27 = (byte *)(param_2 + iVar20 + 5);
    pbVar21 = (byte *)(param_3 + iVar24 + 5);
    uVar25 = iVar24 + 1U;
    if ((int)uVar26 < (int)(iVar24 + 1U)) {
      uVar25 = uVar26;
    }
    if (0 < (int)uVar25) {
      uVar26 = uVar25 >> 3;
      if (uVar26 != 0) {
        do {
          bVar17 = *pbVar27;
          bVar18 = *pbVar21;
          pbVar1 = pbVar27 + 1;
          pbVar2 = pbVar21 + -1;
          pbVar3 = pbVar27 + 2;
          pbVar4 = pbVar21 + -2;
          pbVar5 = pbVar27 + 3;
          pbVar6 = pbVar21 + -3;
          pbVar7 = pbVar27 + 4;
          pbVar8 = pbVar21 + -4;
          pbVar9 = pbVar27 + 5;
          pbVar10 = pbVar21 + -5;
          pbVar11 = pbVar27 + 6;
          pbVar12 = pbVar21 + -6;
          pbVar13 = pbVar27 + 7;
          pbVar14 = pbVar21 + -7;
          pbVar27 = pbVar27 + 8;
          pbVar21 = pbVar21 + -8;
          uVar29 = uVar29 + (uint)bVar17 * (uint)bVar18 + (uint)*pbVar1 * (uint)*pbVar2 +
                   (uint)*pbVar3 * (uint)*pbVar4 + (uint)*pbVar5 * (uint)*pbVar6 +
                   (uint)*pbVar7 * (uint)*pbVar8 + (uint)*pbVar9 * (uint)*pbVar10 +
                   (uint)*pbVar11 * (uint)*pbVar12 + (uint)*pbVar13 * (uint)*pbVar14;
          uVar26 = uVar26 - 1;
        } while (uVar26 != 0);
        uVar25 = uVar25 & 7;
        if (uVar25 == 0) goto LAB_802356a4;
      }
      do {
        bVar17 = *pbVar27;
        pbVar27 = pbVar27 + 1;
        bVar18 = *pbVar21;
        pbVar21 = pbVar21 + -1;
        uVar29 = uVar29 + (uint)bVar17 * (uint)bVar18;
        uVar25 = uVar25 - 1;
      } while (uVar25 != 0);
    }
LAB_802356a4:
    uVar25 = uVar29 / 10;
    cVar19 = (char)uVar29;
    uVar29 = uVar29 / 10;
    pbVar22 = pbVar22 + -1;
    *pbVar22 = cVar19 + (char)uVar25 * -10;
  }
  *(short *)(param_1 + 2) = *(short *)(param_2 + 2) + *(short *)(param_3 + 2);
  if (uVar29 != 0) {
    pbVar22 = pbVar22 + -1;
    *pbVar22 = (byte)uVar29;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
  }
  iVar28 = 0;
  for (; (iVar28 < 0x24 && (pbVar22 < pbVar23)); pbVar22 = pbVar22 + 1) {
    iVar20 = iVar28 + 5;
    iVar28 = iVar28 + 1;
    param_1[iVar20] = *pbVar22;
  }
  param_1[4] = (char)iVar28;
  if ((pbVar22 < pbVar23) && (4 < *pbVar22)) {
    if (*pbVar22 == 5) {
      pbVar21 = pbVar22 + 1;
      iVar28 = (int)pbVar23 - (int)pbVar21;
      if (pbVar21 < pbVar23) {
        do {
          if (*pbVar21 != 0) goto LAB_80235770;
          pbVar21 = pbVar21 + 1;
          iVar28 = iVar28 + -1;
        } while (iVar28 != 0);
      }
      if ((pbVar22[-1] & 1) == 0) {
        return;
      }
    }
LAB_80235770:
    for (pbVar22 = param_1 + 5 + ((byte)param_1[4] - 1); 8 < *pbVar22; pbVar22 = pbVar22 + -1) {
      if (pbVar22 == param_1 + 5) {
        *pbVar22 = 1;
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
        return;
      }
      *pbVar22 = 0;
    }
    *pbVar22 = *pbVar22 + 1;
  }
  return;
}



// ==== 802357d4  __flush_buffer ====

int __flush_buffer(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  if (param_1[9] - param_1[7] != 0) {
    param_1[10] = param_1[9] - param_1[7];
    iVar1 = (*(code *)param_1[0x10])(*param_1,param_1[7],param_1 + 10,param_1[0x12]);
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_1[10];
    }
    if (iVar1 != 0) {
      return iVar1;
    }
    param_1[6] = param_1[6] + param_1[10];
  }
  param_1[9] = param_1[7];
  param_1[10] = param_1[8];
  param_1[10] = param_1[10] - (param_1[6] & param_1[0xb]);
  param_1[0xd] = param_1[6];
  return 0;
}



// ==== 80235898  zz_0235898_ ====

void zz_0235898_(int param_1)

{
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x20);
  *(uint *)(param_1 + 0x28) =
       *(int *)(param_1 + 0x28) - (*(uint *)(param_1 + 0x18) & *(uint *)(param_1 + 0x2c));
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x18);
  return;
}



// ==== 802358cc  zz_02358cc_ ====

void zz_02358cc_(void)

{
  return;
}



// ==== 802358d0  zz_02358d0_ ====

void zz_02358d0_(void)

{
  return;
}



// ==== 802358d4  zz_02358d4_ ====

void zz_02358d4_(void)

{
  return;
}



