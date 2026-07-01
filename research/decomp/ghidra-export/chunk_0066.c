// ==== 8021d01c  zz_021d01c_ ====

void zz_021d01c_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_804367d0;
  if (DAT_804367d0 == 0) {
    DAT_804367cc = param_1;
    DAT_804367d0 = param_1;
    DAT_804367d4 = param_1;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    return;
  }
  do {
    iVar1 = DAT_804367d0;
    if (iVar2 == 0) {
LAB_8021d094:
      DAT_804367d0 = iVar1;
      if (iVar2 == 0) {
        *(int *)(DAT_804367cc + 0x38) = param_1;
        *(undefined4 *)(param_1 + 0x38) = 0;
        *(int *)(param_1 + 0x3c) = DAT_804367cc;
        DAT_804367cc = param_1;
        return;
      }
      return;
    }
    if (*(uint *)(param_1 + 4) < *(uint *)(iVar2 + 4)) {
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x3c);
      *(int *)(iVar2 + 0x3c) = param_1;
      *(int *)(param_1 + 0x38) = iVar2;
      iVar1 = param_1;
      if (*(int *)(param_1 + 0x3c) != 0) {
        *(int *)(*(int *)(param_1 + 0x3c) + 0x38) = param_1;
        iVar1 = DAT_804367d0;
      }
      goto LAB_8021d094;
    }
    iVar2 = *(int *)(iVar2 + 0x38);
  } while( true );
}



// ==== 8021d0bc  zz_021d0bc_ ====

void zz_021d0bc_(undefined4 *param_1)

{
  param_1[2] = 0;
  *param_1 = 3;
  if (DAT_804367d0 != param_1) {
    if (DAT_804367cc == param_1) {
      DAT_804367cc = (undefined4 *)param_1[0xf];
      *(undefined4 *)(param_1[0xf] + 0x38) = 0;
      DAT_804367d4 = DAT_804367d0;
      return;
    }
    DAT_804367d4 = (undefined4 *)param_1[0xe];
    *(undefined4 *)(param_1[0xf] + 0x38) = param_1[0xe];
    *(undefined4 *)(param_1[0xe] + 0x3c) = param_1[0xf];
    return;
  }
  DAT_804367d0 = (undefined4 *)param_1[0xe];
  if (DAT_804367d0 != (undefined4 *)0x0) {
    *(undefined4 *)(param_1[0xe] + 0x3c) = 0;
    return;
  }
  DAT_804367d4 = (undefined4 *)0x0;
  DAT_804367cc = (undefined4 *)0x0;
  DAT_804367d0 = (undefined4 *)0x0;
  return;
}



// ==== 8021d154  FUN_8021d154 ====

void FUN_8021d154(int param_1)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] != 0) {
    (&DAT_803f50e0)[param_1 * 0x44] = 0;
    zz_0207c68_(param_1,0);
    gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + iVar2));
    pcVar1 = *(code **)(&DAT_803f51ac + iVar2);
    if (pcVar1 != (code *)0x0) {
      *(undefined4 *)(&DAT_803f51ac + iVar2) = 0;
      (*pcVar1)(param_1,0xfffffffd);
    }
    if ((&DAT_803f50e4)[param_1 * 0x44] != -1) {
      (&DAT_803f50e4)[param_1 * 0x44] = 0xfffffffd;
    }
    pcVar1 = *(code **)(&DAT_803f51a4 + iVar2);
    if ((pcVar1 != (code *)0x0) && (6 < *(int *)(&DAT_803f5104 + iVar2))) {
      *(undefined4 *)(&DAT_803f51a4 + iVar2) = 0;
      (*pcVar1)(param_1,0xfffffffd);
    }
  }
  return;
}



// ==== 8021d22c  FUN_8021d22c ====

void FUN_8021d22c(int param_1)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte local_18 [12];
  
  iVar4 = param_1 * 0x110;
  gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + iVar4));
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    return;
  }
  iVar2 = gnt4_EXILock_bl(param_1,0,0);
  if (iVar2 == 0) {
    iVar2 = -0x80;
  }
  else {
    iVar2 = zz_021d530_(param_1,local_18);
    if ((-1 < iVar2) && (iVar2 = zz_021d620_(param_1), -1 < iVar2)) {
      if ((local_18[0] & 0x18) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = -5;
      }
      if ((iVar2 == -5) &&
         (iVar3 = *(int *)(&DAT_803f5188 + iVar4), *(int *)(&DAT_803f5188 + iVar4) = iVar3 + -1,
         0 < iVar3 + -1)) {
        iVar2 = zz_021d770_(param_1);
        if (-1 < iVar2) {
          return;
        }
        goto LAB_8021d300;
      }
    }
    gnt4_EXIUnlock_bl(param_1);
  }
LAB_8021d300:
  pcVar1 = *(code **)(&DAT_803f51ac + iVar4);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51ac + iVar4) = 0;
    (*pcVar1)(param_1,iVar2);
  }
  return;
}



// ==== 8021d344  FUN_8021d344 ====

void FUN_8021d344(int param_1)

{
  bool bVar1;
  uint uVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar4 = gnt4_EXIDeselect(param_1);
  uVar2 = countLeadingZeros(uVar4);
  gnt4_EXIUnlock_bl(param_1);
  pcVar3 = *(code **)(&DAT_803f51a8 + param_1 * 0x110);
  if (pcVar3 != (code *)0x0) {
    bVar1 = false;
    *(undefined4 *)(&DAT_803f51a8 + param_1 * 0x110) = 0;
    if ((uVar2 >> 5 == 0) && (iVar5 = zz_0207e58_(param_1), iVar5 != 0)) {
      bVar1 = true;
    }
    if (bVar1) {
      uVar4 = 0;
    }
    else {
      uVar4 = 0xfffffffd;
    }
    (*pcVar3)(param_1,uVar4);
  }
  return;
}



// ==== 8021d3ec  FUN_8021d3ec ====

void FUN_8021d3ec(int param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  pcVar1 = *(code **)(&DAT_803f51bc + param_1 * 0x110);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51bc + param_1 * 0x110) = 0;
    iVar2 = zz_0207e58_(param_1);
    if (iVar2 == 0) {
      uVar3 = 0xfffffffd;
    }
    else {
      uVar3 = 1;
    }
    (*pcVar1)(param_1,uVar3);
  }
  return;
}



// ==== 8021d470  zz_021d470_ ====

undefined4 zz_021d470_(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 local_10 [2];
  
  iVar4 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar4 == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    if (param_2 == 0) {
      local_10[0] = 0x81000000;
    }
    else {
      local_10[0] = 0x81010000;
    }
    uVar5 = gnt4_EXIImm_bl(param_1,(byte *)local_10,2,1,0);
    uVar1 = countLeadingZeros(uVar5);
    uVar5 = gnt4_EXISync(param_1);
    uVar2 = countLeadingZeros(uVar5);
    uVar5 = gnt4_EXIDeselect(param_1);
    uVar3 = countLeadingZeros(uVar5);
    if ((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0xfffffffd;
    }
  }
  return uVar5;
}



// ==== 8021d530  zz_021d530_ ====

undefined4 zz_021d530_(int param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  byte local_18 [12];
  
  iVar6 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar6 == 0) {
    uVar7 = 0xfffffffd;
  }
  else {
    local_18[0] = 0x83;
    local_18[1] = 0;
    local_18[2] = 0;
    local_18[3] = 0;
    uVar7 = gnt4_EXIImm_bl(param_1,local_18,2,1,0);
    uVar1 = countLeadingZeros(uVar7);
    uVar7 = gnt4_EXISync(param_1);
    uVar2 = countLeadingZeros(uVar7);
    uVar7 = gnt4_EXIImm_bl(param_1,param_2,1,0,0);
    uVar3 = countLeadingZeros(uVar7);
    uVar7 = gnt4_EXISync(param_1);
    uVar4 = countLeadingZeros(uVar7);
    uVar7 = gnt4_EXIDeselect(param_1);
    uVar5 = countLeadingZeros(uVar7);
    if ((((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) && uVar4 >> 5 == 0) &&
        uVar5 >> 5 == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = 0xfffffffd;
    }
  }
  return uVar7;
}



// ==== 8021d620  zz_021d620_ ====

undefined4 zz_021d620_(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  byte local_c [4];
  
  iVar4 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar4 == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    local_c[0] = 0x89;
    local_c[1] = 0;
    local_c[2] = 0;
    local_c[3] = 0;
    uVar5 = gnt4_EXIImm_bl(param_1,local_c,1,1,0);
    uVar1 = countLeadingZeros(uVar5);
    uVar5 = gnt4_EXISync(param_1);
    uVar2 = countLeadingZeros(uVar5);
    uVar5 = gnt4_EXIDeselect(param_1);
    uVar3 = countLeadingZeros(uVar5);
    if ((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0xfffffffd;
    }
  }
  return uVar5;
}



// ==== 8021d6cc  FUN_8021d6cc ====

void FUN_8021d6cc(undefined *param_1)

{
  code *pcVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  piVar2 = &DAT_803f50e0;
  if (param_1 != &DAT_803f51c0) {
    iVar3 = 1;
    piVar2 = &DAT_803f51f0;
    if (param_1 != (undefined *)0x803f52d0) {
      iVar3 = 2;
      piVar2 = &DAT_803f51f0;
    }
  }
  if (*piVar2 != 0) {
    zz_0207c68_(iVar3,0);
    pcVar1 = (code *)piVar2[0x33];
    if (pcVar1 != (code *)0x0) {
      piVar2[0x33] = 0;
      (*pcVar1)(iVar3,0xfffffffb);
    }
  }
  return;
}



// ==== 8021d770  zz_021d770_ ====

undefined4 zz_021d770_(int param_1)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = param_1 * 0x110;
  iVar2 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar2 == 0) {
    gnt4_EXIUnlock_bl(param_1);
    return 0xfffffffd;
  }
  gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + iVar4));
  bVar1 = (&DAT_803f5174)[iVar4];
  if (bVar1 != 0xf3) {
    if (bVar1 < 0xf3) {
      if (bVar1 != 0xf1) {
        if (0xf0 < bVar1) {
          gnt4_OSSetAlarm_bl((undefined4 *)(&DAT_803f51c0 + iVar4),0x10624dd3,0,
                             (DAT_800000f8 / 4000) * 100,FUN_8021d6cc);
        }
        goto LAB_8021d890;
      }
    }
    else if (0xf4 < bVar1) goto LAB_8021d890;
    uVar5 = *(uint *)(&DAT_803f50ec + iVar4);
    uVar6 = (DAT_800000f8 >> 2) * 2;
    uVar5 = ((int)uVar5 >> 0xd) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1fff) != 0);
    iVar2 = ((int)uVar5 >> 0x1f) * uVar6 + (int)((ulonglong)uVar5 * (ulonglong)uVar6 >> 0x20);
    gnt4_OSSetAlarm_bl((undefined4 *)(&DAT_803f51c0 + iVar4),iVar2,iVar2,uVar5 * uVar6,FUN_8021d6cc)
    ;
  }
LAB_8021d890:
  iVar2 = gnt4_EXIImmEx(param_1,&DAT_803f5174 + iVar4,*(int *)(&DAT_803f5180 + iVar4),1);
  if (iVar2 == 0) {
    gnt4_EXIDeselect(param_1);
    gnt4_EXIUnlock_bl(param_1);
    uVar3 = 0xfffffffd;
  }
  else if (((&DAT_803f5174)[iVar4] == 'R') &&
          (iVar2 = gnt4_EXIImmEx(param_1,(byte *)((&DAT_803f5160)[param_1 * 0x44] + 0x200),
                                 *(int *)(&DAT_803f50f4 + iVar4),1), iVar2 == 0)) {
    gnt4_EXIDeselect(param_1);
    gnt4_EXIUnlock_bl(param_1);
    uVar3 = 0xfffffffd;
  }
  else if (*(int *)(&DAT_803f5184 + iVar4) == -1) {
    gnt4_EXIDeselect(param_1);
    gnt4_EXIUnlock_bl(param_1);
    uVar3 = 0;
  }
  else {
    if ((&DAT_803f5174)[iVar4] == 'R') {
      uVar3 = 0x200;
    }
    else {
      uVar3 = 0x80;
    }
    iVar2 = gnt4_EXIDma_bl(param_1,*(uint *)(&DAT_803f5194 + iVar4),uVar3,
                           *(int *)(&DAT_803f5184 + iVar4),FUN_8021d344);
    if (iVar2 == 0) {
      gnt4_EXIDeselect(param_1);
      gnt4_EXIUnlock_bl(param_1);
      uVar3 = 0xfffffffd;
    }
    else {
      uVar3 = 0;
    }
  }
  return uVar3;
}



// ==== 8021d99c  FUN_8021d99c ====

void FUN_8021d99c(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    *(code **)(&DAT_803f51bc + iVar3) = FUN_8021d99c;
    iVar2 = gnt4_EXILock_bl(param_1,0,-0x7fde2c14);
    if (iVar2 == 0) {
      param_2 = 0;
    }
    else {
      *(undefined4 *)(&DAT_803f51bc + iVar3) = 0;
      param_2 = zz_021d770_(param_1);
    }
  }
  if (param_2 < 0) {
    bVar1 = (&DAT_803f5174)[iVar3];
    if (bVar1 != 0xf3) {
      if (bVar1 < 0xf3) {
        if (bVar1 == 0x52) {
          pcVar4 = *(code **)(&DAT_803f51a8 + iVar3);
          if (pcVar4 == (code *)0x0) {
            return;
          }
          *(undefined4 *)(&DAT_803f51a8 + iVar3) = 0;
          (*pcVar4)(param_1);
          return;
        }
        if (bVar1 < 0x52) {
          return;
        }
        if (bVar1 < 0xf1) {
          return;
        }
      }
      else if (0xf4 < bVar1) {
        return;
      }
      pcVar4 = *(code **)(&DAT_803f51ac + iVar3);
      if (pcVar4 != (code *)0x0) {
        *(undefined4 *)(&DAT_803f51ac + iVar3) = 0;
        (*pcVar4)(param_1);
      }
    }
  }
  return;
}



// ==== 8021daac  zz_021daac_ ====

undefined4 zz_021daac_(int param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  
  gnt4_OSDisableInterrupts_bl();
  iVar4 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    uVar6 = 0xfffffffd;
    goto LAB_8021dc40;
  }
  if (param_2 != 0) {
    *(int *)(&DAT_803f51a8 + iVar4) = param_2;
  }
  if (param_3 != 0) {
    *(int *)(&DAT_803f51ac + iVar4) = param_3;
  }
  *(code **)(&DAT_803f51bc + iVar4) = FUN_8021d99c;
  iVar2 = gnt4_EXILock_bl(param_1,0,-0x7fde2c14);
  if (iVar2 == 0) {
    uVar6 = 0xffffffff;
    goto LAB_8021dc40;
  }
  *(undefined4 *)(&DAT_803f51bc + iVar4) = 0;
  iVar2 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar2 == 0) {
    gnt4_EXIUnlock_bl(param_1);
    uVar6 = 0xfffffffd;
    goto LAB_8021dc40;
  }
  gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + iVar4));
  bVar1 = (&DAT_803f5174)[iVar4];
  if (bVar1 != 0xf3) {
    if (bVar1 < 0xf3) {
      if (bVar1 == 0xf1) {
LAB_8021dbd8:
        uVar3 = *(uint *)(&DAT_803f50ec + iVar4);
        uVar5 = (DAT_800000f8 >> 2) * 2;
        uVar3 = ((int)uVar3 >> 0xd) + (uint)((int)uVar3 < 0 && (uVar3 & 0x1fff) != 0);
        iVar2 = ((int)uVar3 >> 0x1f) * uVar5 + (int)((ulonglong)uVar3 * (ulonglong)uVar5 >> 0x20);
        gnt4_OSSetAlarm_bl((undefined4 *)(&DAT_803f51c0 + iVar4),iVar2,iVar2,uVar3 * uVar5,
                           FUN_8021d6cc);
      }
      else if (0xf0 < bVar1) {
        gnt4_OSSetAlarm_bl((undefined4 *)(&DAT_803f51c0 + iVar4),0x10624dd3,0,
                           (DAT_800000f8 / 4000) * 100,FUN_8021d6cc);
      }
    }
    else if (bVar1 < 0xf5) goto LAB_8021dbd8;
  }
  uVar6 = 0;
LAB_8021dc40:
  gnt4_OSRestoreInterrupts_bl();
  return uVar6;
}



// ==== 8021dc60  zz_021dc60_ ====

int zz_021dc60_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  (&DAT_803f5174)[iVar2] = 0x52;
  (&DAT_803f5175)[iVar2] = (byte)(*(uint *)(&DAT_803f5190 + iVar2) >> 0x11) & 0x7f;
  (&DAT_803f5176)[iVar2] = (char)(*(uint *)(&DAT_803f5190 + iVar2) >> 9);
  (&DAT_803f5177)[iVar2] = (byte)(*(uint *)(&DAT_803f5190 + iVar2) >> 7) & 3;
  (&DAT_803f5178)[iVar2] = (byte)*(undefined4 *)(&DAT_803f5190 + iVar2) & 0x7f;
  *(undefined4 *)(&DAT_803f5180 + iVar2) = 5;
  *(undefined4 *)(&DAT_803f5184 + iVar2) = 0;
  *(undefined4 *)(&DAT_803f5188 + iVar2) = 0;
  iVar1 = zz_021daac_(param_1,param_2,0);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  else if (-1 < iVar1) {
    iVar1 = gnt4_EXIImmEx(param_1,&DAT_803f5174 + iVar2,*(int *)(&DAT_803f5180 + iVar2),1);
    if (((iVar1 == 0) ||
        (iVar1 = gnt4_EXIImmEx(param_1,(byte *)((&DAT_803f5160)[param_1 * 0x44] + 0x200),
                               *(int *)(&DAT_803f50f4 + iVar2),1), iVar1 == 0)) ||
       (iVar1 = gnt4_EXIDma_bl(param_1,*(uint *)(&DAT_803f5194 + iVar2),0x200,
                               *(int *)(&DAT_803f5184 + iVar2),FUN_8021d344), iVar1 == 0)) {
      *(undefined4 *)(&DAT_803f51a8 + iVar2) = 0;
      gnt4_EXIDeselect(param_1);
      gnt4_EXIUnlock_bl(param_1);
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}



// ==== 8021dd94  zz_021dd94_ ====

int zz_021dd94_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  (&DAT_803f5174)[iVar2] = 0xf2;
  (&DAT_803f5175)[iVar2] = (byte)(*(uint *)(&DAT_803f5190 + iVar2) >> 0x11) & 0x7f;
  (&DAT_803f5176)[iVar2] = (char)(*(uint *)(&DAT_803f5190 + iVar2) >> 9);
  (&DAT_803f5177)[iVar2] = (byte)(*(uint *)(&DAT_803f5190 + iVar2) >> 7) & 3;
  (&DAT_803f5178)[iVar2] = (byte)*(undefined4 *)(&DAT_803f5190 + iVar2) & 0x7f;
  *(undefined4 *)(&DAT_803f5180 + iVar2) = 5;
  *(undefined4 *)(&DAT_803f5184 + iVar2) = 1;
  *(undefined4 *)(&DAT_803f5188 + iVar2) = 3;
  iVar1 = zz_021daac_(param_1,0,param_2);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  else if (-1 < iVar1) {
    iVar1 = gnt4_EXIImmEx(param_1,&DAT_803f5174 + iVar2,*(int *)(&DAT_803f5180 + iVar2),1);
    if ((iVar1 == 0) ||
       (iVar1 = gnt4_EXIDma_bl(param_1,*(uint *)(&DAT_803f5194 + iVar2),0x80,
                               *(int *)(&DAT_803f5184 + iVar2),FUN_8021d344), iVar1 == 0)) {
      *(undefined4 *)(&DAT_803f51ac + iVar2) = 0;
      gnt4_EXIDeselect(param_1);
      gnt4_EXIUnlock_bl(param_1);
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
  }
  return iVar1;
}



// ==== 8021deb0  zz_021deb0_ ====

int zz_021deb0_(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  (&DAT_803f5174)[iVar2] = 0xf1;
  (&DAT_803f5175)[iVar2] = (byte)(param_2 >> 0x11) & 0x7f;
  (&DAT_803f5176)[iVar2] = (char)(param_2 >> 9);
  *(undefined4 *)(&DAT_803f5180 + iVar2) = 3;
  *(undefined4 *)(&DAT_803f5184 + iVar2) = 0xffffffff;
  *(undefined4 *)(&DAT_803f5188 + iVar2) = 3;
  iVar1 = zz_021daac_(param_1,0,param_3);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  else if (-1 < iVar1) {
    iVar1 = gnt4_EXIImmEx(param_1,&DAT_803f5174 + iVar2,*(int *)(&DAT_803f5180 + iVar2),1);
    if (iVar1 == 0) {
      *(undefined4 *)(&DAT_803f51ac + iVar2) = 0;
      iVar1 = -3;
    }
    else {
      iVar1 = 0;
    }
    gnt4_EXIDeselect(param_1);
    gnt4_EXIUnlock_bl(param_1);
  }
  return iVar1;
}



// ==== 8021df90  zz_021df90_ ====

void zz_021df90_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  puVar2 = &DAT_803f50e0;
  if ((DAT_803f51ec == 0) || (DAT_803f52fc == 0)) {
    DAT_804367d8 = zz_0202a60_();
    uVar3 = gnt4_OSRegisterVersion_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d50,
                       param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_021c678_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    gnt4_OSInitAlarm();
    iVar1 = 0;
    do {
      puVar2[1] = 0xfffffffd;
      gnt4_OSInitThreadQueue_bl(puVar2 + 0x23);
      gnt4_OSCreateAlarm_bl(puVar2 + 0x38);
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x44;
    } while (iVar1 < 2);
    zz_021e044_(&DAT_80000000);
    gnt4_OSRegisterResetFunction_bl(-0x7fc55cb8);
  }
  return;
}



// ==== 8021e03c  zz_021e03c_ ====

undefined2 zz_021e03c_(void)

{
  return DAT_804367d8;
}



// ==== 8021e044  zz_021e044_ ====

void zz_021e044_(undefined *param_1)

{
  DAT_803f51ec = param_1;
  if (param_1 == (undefined *)0x0) {
    DAT_803f51ec = &DAT_803f5300;
  }
  if (param_1 == (undefined *)0x0) {
    param_1 = &DAT_803f5300;
  }
  DAT_803f52fc = param_1;
  return;
}



// ==== 8021e07c  zz_021e07c_ ====

undefined4 zz_021e07c_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (((param_1 < 0) || (1 < param_1)) || ((&DAT_803f51ec)[param_1 * 0x44] == 0)) {
    uVar1 = 0xffffff80;
  }
  else {
    gnt4_OSDisableInterrupts_bl();
    if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
      uVar1 = 0xfffffffd;
    }
    else if ((&DAT_803f50e4)[param_1 * 0x44] == -1) {
      uVar1 = 0xffffffff;
    }
    else {
      (&DAT_803f50e4)[param_1 * 0x44] = 0xffffffff;
      uVar1 = 0;
      *(undefined4 *)(&DAT_803f51b0 + param_1 * 0x110) = 0;
      *param_2 = &DAT_803f50e0 + param_1 * 0x44;
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar1;
}



// ==== 8021e134  zz_021e134_ ====

int zz_021e134_(int *param_1,int param_2)

{
  gnt4_OSDisableInterrupts_bl();
  if (*param_1 == 0) {
    if (param_1[1] == -1) {
      param_1[1] = param_2;
    }
  }
  else {
    param_1[1] = param_2;
  }
  gnt4_OSRestoreInterrupts_bl();
  return param_2;
}



// ==== 8021e198  zz_021e198_ ====

undefined4 zz_021e198_(int param_1)

{
  if ((-1 < param_1) && (param_1 < 2)) {
    return (&DAT_803f50e4)[param_1 * 0x44];
  }
  return 0xffffff80;
}



// ==== 8021e1c8  zz_021e1c8_ ====

int zz_021e1c8_(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int *local_18 [3];
  
  iVar1 = zz_021e07c_(param_1,local_18);
  if (-1 < iVar1) {
    iVar1 = zz_021f8e8_((int)local_18[0]);
    iVar2 = zz_021fcec_((int)local_18[0]);
    if ((iVar1 == 0) || (iVar2 == 0)) {
      gnt4_OSDisableInterrupts_bl();
      if (*local_18[0] == 0) {
        if (local_18[0][1] == -1) {
          local_18[0][1] = -6;
        }
      }
      else {
        local_18[0][1] = -6;
      }
      gnt4_OSRestoreInterrupts_bl();
      iVar1 = -6;
    }
    else {
      if (param_2 != (int *)0x0) {
        *param_2 = local_18[0][3] * (uint)*(ushort *)(iVar1 + 6);
      }
      if (param_3 != (int *)0x0) {
        *param_3 = 0;
        for (uVar3 = 0; uVar3 < 0x7f; uVar3 = uVar3 + 1) {
          if (*(char *)(iVar2 + 8) == -1) {
            *param_3 = *param_3 + 1;
          }
          iVar2 = iVar2 + 0x40;
        }
      }
      gnt4_OSDisableInterrupts_bl();
      if (*local_18[0] == 0) {
        if (local_18[0][1] == -1) {
          local_18[0][1] = 0;
        }
      }
      else {
        local_18[0][1] = 0;
      }
      gnt4_OSRestoreInterrupts_bl();
      iVar1 = 0;
    }
  }
  return iVar1;
}



// ==== 8021e318  zz_021e318_ ====

int zz_021e318_(int param_1,undefined2 *param_2)

{
  int iVar1;
  int *local_c [2];
  
  iVar1 = zz_021e07c_(param_1,local_c);
  if (-1 < iVar1) {
    *param_2 = *(undefined2 *)(local_c[0][0x20] + 0x24);
    gnt4_OSDisableInterrupts_bl();
    if (*local_c[0] == 0) {
      if (local_c[0][1] == -1) {
        local_c[0][1] = 0;
      }
    }
    else {
      local_c[0][1] = 0;
    }
    gnt4_OSRestoreInterrupts_bl();
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 8021e3a0  FUN_8021e3a0 ====

undefined4 FUN_8021e3a0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) &&
     ((iVar1 = zz_0221858_(0), iVar1 == -1 || (iVar1 = zz_0221858_(1), iVar1 == -1)))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 8021e3f0  zz_021e3f0_ ====

uint zz_021e3f0_(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = 8;
  uVar1 = param_1 >> 0x1f;
  iVar5 = 0;
  iVar6 = 1;
  uVar2 = 0;
  uVar3 = 0;
  do {
    if (uVar3 < 0x10) {
      uVar2 = uVar2 | (param_1 & 1 << uVar3) << (0x1f - uVar3) - iVar5;
      iVar5 = iVar5 + 1;
    }
    else if (uVar3 == 0x1f) {
      uVar2 = uVar2 | uVar1;
    }
    else {
      uVar2 = uVar2 | (param_1 & 1 << uVar3) >> iVar6;
      iVar6 = iVar6 + 2;
    }
    uVar4 = uVar3 + 1;
    if (uVar4 < 0x10) {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) << (0x1f - uVar4) - iVar5;
      iVar5 = iVar5 + 1;
    }
    else if (uVar4 == 0x1f) {
      uVar2 = uVar2 | uVar1;
    }
    else {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) >> iVar6;
      iVar6 = iVar6 + 2;
    }
    uVar4 = uVar3 + 2;
    if (uVar4 < 0x10) {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) << (0x1f - uVar4) - iVar5;
      iVar5 = iVar5 + 1;
    }
    else if (uVar4 == 0x1f) {
      uVar2 = uVar2 | uVar1;
    }
    else {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) >> iVar6;
      iVar6 = iVar6 + 2;
    }
    uVar4 = uVar3 + 3;
    if (uVar4 < 0x10) {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) << (0x1f - uVar4) - iVar5;
      iVar5 = iVar5 + 1;
    }
    else if (uVar4 == 0x1f) {
      uVar2 = uVar2 | uVar1;
    }
    else {
      uVar2 = uVar2 | (param_1 & 1 << uVar4) >> iVar6;
      iVar6 = iVar6 + 2;
    }
    uVar3 = uVar3 + 4;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  return uVar2;
}



// ==== 8021e55c  zz_021e55c_ ====

undefined4 zz_021e55c_(int param_1,uint param_2,byte *param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  byte local_24;
  byte local_23;
  undefined1 local_22;
  byte local_21;
  byte local_20;
  
  iVar5 = gnt4_EXISelect_bl(param_1,0,4);
  if (iVar5 == 0) {
    uVar6 = 0xfffffffd;
  }
  else {
    gnt4_memset(&local_24,0,5);
    local_24 = 0x52;
    local_23 = (byte)(param_2 >> 0x18);
    if (param_5 == 0) {
      local_23 = local_23 >> 5 & 3;
      local_22 = (undefined1)(param_2 >> 0x15);
      local_21 = (byte)(param_2 >> 0x13) & 3;
      local_20 = (byte)(param_2 >> 0xc) & 0x7f;
    }
    else {
      local_22 = (undefined1)(param_2 >> 0x10);
    }
    uVar6 = gnt4_EXIImmEx(param_1,&local_24,5,1);
    uVar1 = countLeadingZeros(uVar6);
    uVar6 = gnt4_EXIImmEx(param_1,(byte *)((&DAT_803f5160)[param_1 * 0x44] + 0x200),
                          *(int *)(&DAT_803f50f4 + param_1 * 0x110),1);
    uVar2 = countLeadingZeros(uVar6);
    uVar6 = gnt4_EXIImmEx(param_1,param_3,param_4,0);
    uVar3 = countLeadingZeros(uVar6);
    uVar6 = gnt4_EXIDeselect(param_1);
    uVar4 = countLeadingZeros(uVar6);
    if (((uVar1 >> 5 == 0 && uVar2 >> 5 == 0) && uVar3 >> 5 == 0) && uVar4 >> 5 == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = 0xfffffffd;
    }
  }
  return uVar6;
}



// ==== 8021e6a0  zz_021e6a0_ ====

uint zz_021e6a0_(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 1;
  iVar1 = gnt4_OSGetTick_bl();
  for (uVar3 = 0;
      (DAT_80435d58 = iVar1 * 0x41c64e6d + 0x3039, uVar2 = (DAT_80435d58 >> 0x10 & 0x1f) + 1,
      uVar2 < 4 && (uVar3 < 10)); uVar3 = uVar3 + 1) {
    iVar1 = gnt4_OSGetTick_bl();
    iVar1 = iVar1 << uVar4;
    uVar4 = uVar4 + 1;
    if (0x10 < uVar4) {
      uVar4 = 1;
    }
  }
  if (uVar2 < 4) {
    uVar2 = 4;
  }
  return uVar2;
}



// ==== 8021e764  zz_021e764_ ====

undefined4 zz_021e764_(int param_1,uint *param_2)

{
  uint *puVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  
  iVar8 = param_1 * 0x110;
  puVar2 = (uint *)(&DAT_803f5160)[param_1 * 0x44];
  puVar1 = (uint *)((int)puVar2 + 0x2fU & 0xffffffe0);
  iVar3 = gnt4_OSGetTick_bl();
  DAT_80435d58 = iVar3 * 0x41c64e6d + 0x3039;
  uVar10 = DAT_80435d58 >> 0x10 & 0x7000 | 0x7fec8000;
  uVar4 = zz_021e6a0_();
  iVar3 = zz_021e55c_(param_1,uVar10,(byte *)&local_7c,uVar4,0);
  if (iVar3 < 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    uVar7 = uVar4 * 8 + 1;
    uVar6 = 0;
    if (uVar7 != 0) {
      if ((8 < uVar7) && (uVar11 = uVar4 & 0x1fffffff, uVar4 * 8 != 7)) {
        do {
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          uVar6 = uVar6 + 8;
          uVar11 = uVar11 - 1;
        } while (uVar11 != 0);
      }
      iVar3 = uVar7 - uVar6;
      if (uVar6 < uVar7) {
        do {
          uVar10 = uVar10 >> 1 |
                   (~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) & 1) << 0x1e;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    *(uint *)(&DAT_803f510c + iVar8) =
         uVar10 | ~(uVar10 >> 0x17 ^ uVar10 >> 0xf ^ uVar10 ^ uVar10 >> 7) << 0x1f;
    uVar10 = zz_021e3f0_(*(uint *)(&DAT_803f510c + iVar8));
    *(uint *)(&DAT_803f510c + iVar8) = uVar10;
    uVar10 = zz_021e6a0_();
    iVar3 = zz_021e55c_(param_1,0,(byte *)&local_7c,uVar10 + 0x14,1);
    if (iVar3 < 0) {
      uVar5 = 0xfffffffd;
    }
    else {
      uVar4 = *(uint *)(&DAT_803f510c + iVar8);
      iVar3 = 4;
      uVar6 = local_7c ^ uVar4;
      do {
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar4 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1f;
      iVar3 = 4;
      uVar4 = *(uint *)(&DAT_803f510c + iVar8);
      uVar7 = local_78 ^ uVar4;
      do {
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar4 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1f;
      iVar3 = 4;
      uVar4 = *(uint *)(&DAT_803f510c + iVar8);
      uVar11 = local_74 ^ uVar4;
      do {
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar4 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1f;
      iVar3 = 4;
      uVar4 = *(uint *)(&DAT_803f510c + iVar8);
      local_70 = local_70 ^ uVar4;
      do {
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar4 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1f;
      uVar10 = uVar10 * 8;
      uVar9 = *(uint *)(&DAT_803f510c + iVar8);
      uVar4 = 0;
      local_6c = local_6c ^ uVar9;
      if (uVar10 != 0) {
        if ((8 < uVar10) && (uVar12 = uVar10 - 1 >> 3, uVar10 != 8)) {
          do {
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            uVar4 = uVar4 + 8;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
        }
        iVar3 = uVar10 - uVar4;
        if (uVar4 < uVar10) {
          do {
            uVar9 = uVar9 << 1 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1e & 2;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
        }
      }
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar9 | ~(uVar9 << 0x17 ^ uVar9 << 0xf ^ uVar9 ^ uVar9 << 7) >> 0x1f;
      iVar3 = 4;
      uVar10 = 0;
      uVar4 = *(uint *)(&DAT_803f510c + iVar8);
      do {
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
        uVar10 = uVar10 + 8;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      iVar3 = 0x21 - uVar10;
      if (uVar10 < 0x21) {
        do {
          uVar4 = uVar4 << 1 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1e & 2;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      *(uint *)(&DAT_803f510c + iVar8) =
           uVar4 | ~(uVar4 << 0x17 ^ uVar4 << 0xf ^ uVar4 ^ uVar4 << 7) >> 0x1f;
      *puVar1 = local_70;
      puVar1[1] = local_6c;
      *puVar2 = (uint)puVar1;
      puVar2[1] = 8;
      puVar2[3] = (uint)(puVar1 + 8);
      puVar2[2] = 0;
      gnt4_DCFlushRange_bl((uint)puVar1,8);
      gnt4_DCInvalidateRange_bl((uint)(puVar1 + 8),4);
      gnt4_DCFlushRange_bl((uint)puVar2,0x10);
      *(undefined4 *)(&DAT_803f5114 + iVar8) = 0xff;
      *(undefined4 *)(&DAT_803f511c + iVar8) = 0x3aa360;
      *(undefined4 *)(&DAT_803f5120 + iVar8) = 0x160;
      *(undefined4 *)(&DAT_803f5124 + iVar8) = 0;
      *(undefined2 *)(&DAT_803f5134 + iVar8) = 0x10;
      *(code **)(&DAT_803f5138 + iVar8) = FUN_8021f2bc;
      *(undefined4 *)(&DAT_803f513c + iVar8) = 0;
      *(code **)(&DAT_803f5140 + iVar8) = FUN_8021f32c;
      *(undefined4 *)(&DAT_803f5144 + iVar8) = 0;
      zz_021c744_((undefined4 *)(iVar8 + -0x7fc0aef0));
      *param_2 = uVar6;
      uVar5 = 0;
      param_2[1] = uVar7;
      param_2[2] = uVar11;
    }
  }
  return uVar5;
}



// ==== 8021f2bc  FUN_8021f2bc ====

void FUN_8021f2bc(int param_1)

{
  ushort uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  puVar2 = &DAT_803f50e0;
  if (param_1 != -0x7fc0aef0) {
    puVar2 = &DAT_803f51f0;
  }
  uVar3 = puVar2[0x20];
  zz_021c664_(0xff000000);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(uVar3);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  return;
}



// ==== 8021f32c  FUN_8021f32c ====

void FUN_8021f32c(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  uint uVar8;
  int iVar9;
  byte local_58 [4];
  byte abStack_54 [68];
  
  iVar9 = 0;
  puVar7 = &DAT_803f50e0;
  if (param_1 != -0x7fc0aef0) {
    iVar9 = 1;
    puVar7 = &DAT_803f51f0;
    if (param_1 != -0x7fc0ade0) {
      iVar9 = 2;
      puVar7 = &DAT_803f51f0;
    }
  }
  uVar8 = *(uint *)((puVar7[0x20] + 0x2f & 0xffffffe0) + 0x20);
  uVar2 = zz_021e6a0_();
  iVar3 = zz_021e55c_(iVar9,(uVar8 ^ puVar7[0xb]) & 0xffff0000,abStack_54,uVar2,1);
  if (iVar3 < 0) {
    gnt4_EXIUnlock_bl(iVar9);
    zz_02214e4_(iVar9,-3);
  }
  else {
    uVar4 = 0;
    uVar1 = puVar7[0xb];
    uVar2 = uVar2 + puVar7[5] + 4;
    iVar3 = uVar2 * 8;
    uVar6 = iVar3 + 1;
    if (uVar6 != 0) {
      if ((8 < uVar6) && (uVar2 = uVar2 & 0x1fffffff, iVar3 != 7)) {
        do {
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          uVar4 = uVar4 + 8;
          uVar2 = uVar2 - 1;
        } while (uVar2 != 0);
      }
      iVar3 = uVar6 - uVar4;
      if (uVar4 < uVar6) {
        do {
          uVar1 = uVar1 << 1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1e & 2;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
    }
    puVar7[0xb] = uVar1 | ~(uVar1 << 0x17 ^ uVar1 << 0xf ^ uVar1 ^ uVar1 << 7) >> 0x1f;
    uVar2 = zz_021e6a0_();
    iVar3 = zz_021e55c_(iVar9,(uVar8 << 0x10 ^ puVar7[0xb]) & 0xffff0000,abStack_54,uVar2,1);
    if (iVar3 < 0) {
      gnt4_EXIUnlock_bl(iVar9);
      zz_02214e4_(iVar9,-3);
    }
    else {
      iVar3 = zz_021d530_(iVar9,local_58);
      iVar5 = zz_0207e58_(iVar9);
      if (iVar5 == 0) {
        gnt4_EXIUnlock_bl(iVar9);
        zz_02214e4_(iVar9,-3);
      }
      else {
        if ((iVar3 == 0) && ((local_58[0] & 0x40) == 0)) {
          gnt4_EXIUnlock_bl(iVar9);
          iVar3 = -5;
        }
        zz_02214e4_(iVar9,iVar3);
      }
    }
  }
  return;
}



// ==== 8021f650  FUN_8021f650 ====

void FUN_8021f650(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    *(int *)(&DAT_803f5198 + iVar3) = *(int *)(&DAT_803f5198 + iVar3) + 0x200;
    *(int *)(&DAT_803f5190 + iVar3) = *(int *)(&DAT_803f5190 + iVar3) + 0x200;
    *(int *)(&DAT_803f5194 + iVar3) = *(int *)(&DAT_803f5194 + iVar3) + 0x200;
    iVar2 = *(int *)(&DAT_803f518c + iVar3);
    *(int *)(&DAT_803f518c + iVar3) = iVar2 + -1;
    if ((0 < iVar2 + -1) && (param_2 = zz_021dc60_(param_1,-0x7fde09b0), -1 < param_2)) {
      return;
    }
  }
  if (*(int *)(&DAT_803f51b0 + iVar3) == 0) {
    zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  }
  pcVar1 = *(code **)(&DAT_803f51b4 + iVar3);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51b4 + iVar3) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}



// ==== 8021f72c  zz_021f72c_ ====

int zz_021f72c_(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
  iVar1 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    iVar1 = -3;
  }
  else {
    *(undefined4 *)(&DAT_803f51b4 + iVar1) = param_5;
    *(uint *)(&DAT_803f518c + iVar1) = param_3 >> 9;
    *(undefined4 *)(&DAT_803f5190 + iVar1) = param_2;
    *(undefined4 *)(&DAT_803f5194 + iVar1) = param_4;
    iVar1 = zz_021dc60_(param_1,-0x7fde09b0);
  }
  return iVar1;
}



// ==== 8021f790  FUN_8021f790 ====

void FUN_8021f790(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1 * 0x110;
  if (-1 < param_2) {
    *(int *)(&DAT_803f5198 + iVar3) = *(int *)(&DAT_803f5198 + iVar3) + 0x80;
    *(int *)(&DAT_803f5190 + iVar3) = *(int *)(&DAT_803f5190 + iVar3) + 0x80;
    *(int *)(&DAT_803f5194 + iVar3) = *(int *)(&DAT_803f5194 + iVar3) + 0x80;
    iVar2 = *(int *)(&DAT_803f518c + iVar3);
    *(int *)(&DAT_803f518c + iVar3) = iVar2 + -1;
    if ((0 < iVar2 + -1) && (param_2 = zz_021dd94_(param_1,-0x7fde0870), -1 < param_2)) {
      return;
    }
  }
  if (*(int *)(&DAT_803f51b0 + iVar3) == 0) {
    zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  }
  pcVar1 = *(code **)(&DAT_803f51b4 + iVar3);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51b4 + iVar3) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}



// ==== 8021f86c  zz_021f86c_ ====

int zz_021f86c_(int param_1,undefined4 param_2,uint param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  
  iVar1 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    iVar1 = -3;
  }
  else {
    *(undefined4 *)(&DAT_803f51b4 + iVar1) = param_5;
    *(uint *)(&DAT_803f518c + iVar1) = param_3 >> 7;
    *(undefined4 *)(&DAT_803f5190 + iVar1) = param_2;
    *(undefined4 *)(&DAT_803f5194 + iVar1) = param_4;
    iVar1 = zz_021dd94_(param_1,-0x7fde0870);
  }
  return iVar1;
}



// ==== 8021f8d0  zz_021f8d0_ ====

undefined4 zz_021f8d0_(int param_1)

{
  return *(undefined4 *)(&DAT_803f5198 + param_1 * 0x110);
}



// ==== 8021f8e8  zz_021f8e8_ ====

undefined4 zz_021f8e8_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x88);
}



// ==== 8021f8f0  FUN_8021f8f0 ====

void FUN_8021f8f0(int param_1,int param_2)

{
  code *pcVar1;
  void *__dest;
  int iVar2;
  void *__src;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    __dest = (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x6000);
    __src = (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x8000);
    if (*(void **)(&DAT_803f5168 + iVar2) == __dest) {
      *(void **)(&DAT_803f5168 + iVar2) = __src;
      gnt4_memcpy(__src,__dest,0x2000);
    }
    else {
      *(void **)(&DAT_803f5168 + iVar2) = __dest;
      gnt4_memcpy(__dest,__src,0x2000);
    }
  }
  if (*(int *)(&DAT_803f51b0 + iVar2) == 0) {
    zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  }
  pcVar1 = *(code **)(&DAT_803f51b8 + iVar2);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51b8 + iVar2) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}



// ==== 8021f9c4  FUN_8021f9c4 ====

void FUN_8021f9c4(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if ((param_2 < 0) ||
     (param_2 = zz_021f86c_(param_1,*(int *)(&DAT_803f50ec + iVar2) *
                                    ((uint)(*(int *)(&DAT_803f5168 + iVar2) -
                                           (&DAT_803f5160)[param_1 * 0x44]) >> 0xd),0x2000,
                            *(int *)(&DAT_803f5168 + iVar2),FUN_8021f8f0), param_2 < 0)) {
    if (*(int *)(&DAT_803f51b0 + iVar2) == 0) {
      zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
    }
    pcVar1 = *(code **)(&DAT_803f51b8 + iVar2);
    if (pcVar1 != (code *)0x0) {
      *(undefined4 *)(&DAT_803f51b8 + iVar2) = 0;
      (*pcVar1)(param_1,param_2);
    }
  }
  return;
}



// ==== 8021fa8c  zz_021fa8c_ ====

undefined4 zz_021fa8c_(int param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  short *psVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  ushort unaff_r31;
  
  iVar2 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    uVar1 = 0xfffffffd;
  }
  else {
    psVar3 = *(short **)(&DAT_803f5168 + iVar2);
    if ((ushort)psVar3[3] < param_2) {
      uVar1 = 0xfffffff7;
    }
    else {
      psVar3[3] = psVar3[3] - (short)param_2;
      uVar4 = psVar3[4];
      uVar7 = 0;
      uVar6 = 0xffff;
      while (param_2 != 0) {
        uVar7 = uVar7 + 1;
        if ((int)(*(ushort *)(&DAT_803f50f0 + iVar2) - 5) < (int)(uVar7 & 0xffff)) {
          return 0xfffffffa;
        }
        uVar4 = uVar4 + 1;
        if ((uVar4 < 5) || ((uint)*(ushort *)(&DAT_803f50f0 + iVar2) <= (uint)uVar4)) {
          uVar4 = 5;
        }
        if (psVar3[uVar4] == 0) {
          uVar5 = uVar4;
          if (uVar6 != 0xffff) {
            psVar3[unaff_r31] = uVar4;
            uVar5 = uVar6;
          }
          psVar3[uVar4] = -1;
          param_2 = param_2 - 1;
          unaff_r31 = uVar4;
          uVar6 = uVar5;
        }
      }
      psVar3[4] = uVar4;
      *(ushort *)(&DAT_803f519e + iVar2) = uVar6;
      uVar1 = zz_021fc40_(param_1,psVar3,param_3);
    }
  }
  return uVar1;
}



// ==== 8021fba4  __CARDFreeBlock ====

undefined4 __CARDFreeBlock(int param_1,ushort param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  short *psVar3;
  
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    uVar2 = 0xfffffffd;
  }
  else {
    psVar3 = *(short **)(&DAT_803f5168 + param_1 * 0x110);
    while (param_2 != 0xffff) {
      uVar1 = (uint)param_2;
      if ((uVar1 < 5) || (*(ushort *)(&DAT_803f50f0 + param_1 * 0x110) <= uVar1)) {
        return 0xfffffffa;
      }
      param_2 = psVar3[uVar1];
      psVar3[uVar1] = 0;
      psVar3[3] = psVar3[3] + 1;
    }
    uVar2 = zz_021fc40_(param_1,psVar3,param_3);
  }
  return uVar2;
}



// ==== 8021fc40  zz_021fc40_ ====

void zz_021fc40_(int param_1,short *param_2,undefined4 param_3)

{
  param_2[2] = param_2[2] + 1;
  zz_021ff50_((ushort *)(param_2 + 2),0x1ffc,param_2,param_2 + 1);
  gnt4_DCStoreRange_bl((uint)param_2,0x2000);
  *(undefined4 *)(&DAT_803f51b8 + param_1 * 0x110) = param_3;
  zz_021deb0_(param_1,*(int *)(&DAT_803f50ec + param_1 * 0x110) *
                      ((uint)((int)param_2 - (&DAT_803f5160)[param_1 * 0x44]) >> 0xd),-0x7fde063c);
  return;
}



// ==== 8021fcec  zz_021fcec_ ====

undefined4 zz_021fcec_(int param_1)

{
  return *(undefined4 *)(param_1 + 0x84);
}



// ==== 8021fcf4  FUN_8021fcf4 ====

void FUN_8021fcf4(int param_1,int param_2)

{
  void *__src;
  code *pcVar1;
  void *__dest;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    __dest = (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x2000);
    __src = (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x4000);
    if (*(void **)(&DAT_803f5164 + iVar2) == __dest) {
      *(void **)(&DAT_803f5164 + iVar2) = __src;
      gnt4_memcpy(__src,__dest,0x2000);
    }
    else {
      *(void **)(&DAT_803f5164 + iVar2) = __dest;
      gnt4_memcpy(__dest,__src,0x2000);
    }
  }
  if (*(int *)(&DAT_803f51b0 + iVar2) == 0) {
    zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  }
  pcVar1 = *(code **)(&DAT_803f51b8 + iVar2);
  if (pcVar1 != (code *)0x0) {
    *(undefined4 *)(&DAT_803f51b8 + iVar2) = 0;
    (*pcVar1)(param_1,param_2);
  }
  return;
}



// ==== 8021fdc4  FUN_8021fdc4 ====

void FUN_8021fdc4(int param_1,int param_2)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = param_1 * 0x110;
  if ((param_2 < 0) ||
     (param_2 = zz_021f86c_(param_1,*(int *)(&DAT_803f50ec + iVar2) *
                                    ((uint)(*(int *)(&DAT_803f5164 + iVar2) -
                                           (&DAT_803f5160)[param_1 * 0x44]) >> 0xd),0x2000,
                            *(int *)(&DAT_803f5164 + iVar2),FUN_8021fcf4), param_2 < 0)) {
    if (*(int *)(&DAT_803f51b0 + iVar2) == 0) {
      zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
    }
    pcVar1 = *(code **)(&DAT_803f51b8 + iVar2);
    if (pcVar1 != (code *)0x0) {
      *(undefined4 *)(&DAT_803f51b8 + iVar2) = 0;
      (*pcVar1)(param_1,param_2);
    }
  }
  return;
}



// ==== 8021fe8c  zz_021fe8c_ ====

int zz_021fe8c_(int param_1,undefined4 param_2)

{
  int iVar1;
  ushort *puVar2;
  
  iVar1 = param_1 * 0x110;
  if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
    iVar1 = -3;
  }
  else {
    puVar2 = *(ushort **)(&DAT_803f5164 + iVar1);
    puVar2[0xffd] = puVar2[0xffd] + 1;
    zz_021ff50_(puVar2,0x1ffc,(short *)(puVar2 + 0xffe),(short *)(puVar2 + 0xfff));
    gnt4_DCStoreRange_bl((uint)puVar2,0x2000);
    *(undefined4 *)(&DAT_803f51b8 + iVar1) = param_2;
    iVar1 = zz_021deb0_(param_1,*(int *)(&DAT_803f50ec + iVar1) *
                                ((uint)((int)puVar2 - (&DAT_803f5160)[param_1 * 0x44]) >> 0xd),
                        -0x7fde023c);
  }
  return iVar1;
}



// ==== 8021ff50  zz_021ff50_ ====

void zz_021ff50_(ushort *param_1,uint param_2,short *param_3,short *param_4)

{
  ushort *puVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  
  *param_4 = 0;
  uVar3 = ((int)param_2 >> 1) + (uint)((int)param_2 < 0 && (param_2 & 1) != 0);
  *param_3 = 0;
  if (0 < (int)uVar3) {
    uVar4 = uVar3 >> 3;
    if (uVar4 != 0) {
      do {
        *param_3 = *param_3 + *param_1;
        *param_4 = *param_4 + ~*param_1;
        *param_3 = *param_3 + param_1[1];
        *param_4 = *param_4 + ~param_1[1];
        *param_3 = *param_3 + param_1[2];
        *param_4 = *param_4 + ~param_1[2];
        *param_3 = *param_3 + param_1[3];
        *param_4 = *param_4 + ~param_1[3];
        *param_3 = *param_3 + param_1[4];
        *param_4 = *param_4 + ~param_1[4];
        *param_3 = *param_3 + param_1[5];
        *param_4 = *param_4 + ~param_1[5];
        *param_3 = *param_3 + param_1[6];
        *param_4 = *param_4 + ~param_1[6];
        *param_3 = *param_3 + param_1[7];
        puVar1 = param_1 + 7;
        param_1 = param_1 + 8;
        *param_4 = *param_4 + ~*puVar1;
        uVar4 = uVar4 - 1;
      } while (uVar4 != 0);
      uVar3 = uVar3 & 7;
      if (uVar3 == 0) goto LAB_802200d4;
    }
    do {
      *param_3 = *param_3 + *param_1;
      uVar2 = *param_1;
      param_1 = param_1 + 1;
      *param_4 = *param_4 + ~uVar2;
      uVar3 = uVar3 - 1;
    } while (uVar3 != 0);
  }
LAB_802200d4:
  if (*param_3 == -1) {
    *param_3 = 0;
  }
  if (*param_4 == -1) {
    *param_4 = 0;
    return;
  }
  return;
}



// ==== 80220100  zz_0220100_ ====

undefined4 zz_0220100_(int param_1)

{
  ushort uVar1;
  ushort *puVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  ushort uVar5;
  ushort uVar6;
  ushort *puVar7;
  uint uVar8;
  byte *pbVar9;
  int iVar10;
  int iVar11;
  longlong lVar12;
  undefined8 uVar13;
  
  puVar2 = *(ushort **)(param_1 + 0x80);
  if ((puVar2[0x10] == 0) && (puVar2[0x11] == *(ushort *)(param_1 + 8))) {
    uVar6 = 0;
    uVar5 = 0;
    iVar11 = 0x1f;
    puVar7 = puVar2;
    do {
      uVar5 = uVar5 + *puVar7 + puVar7[1] + puVar7[2] + puVar7[3] + puVar7[4] + puVar7[5] +
              puVar7[6] + puVar7[7];
      uVar6 = uVar6 + ~*puVar7 + ~puVar7[1] + ~puVar7[2] + ~puVar7[3] + ~puVar7[4] + ~puVar7[5] +
              ~puVar7[6] + ~puVar7[7];
      puVar7 = puVar7 + 8;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    iVar11 = 6;
    do {
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
      uVar5 = uVar5 + uVar1;
      uVar6 = uVar6 + ~uVar1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if (uVar5 == 0xffff) {
      uVar5 = 0;
    }
    if (uVar6 == 0xffff) {
      uVar6 = 0;
    }
    if ((puVar2[0xfe] == uVar5) && (puVar2[0xff] == uVar6)) {
      iVar10 = *(int *)(puVar2 + 6);
      uVar8 = *(uint *)(puVar2 + 8);
      puVar4 = gnt4___OSLockSramEx_bl();
      iVar11 = (param_1 + 0x7fc0af20) / 0x110 + (param_1 + 0x7fc0af20 >> 0x1f);
      pbVar9 = (byte *)(puVar4 + (iVar11 - (iVar11 >> 0x1f)) * 6);
      iVar11 = 0;
      puVar7 = puVar2;
      do {
        lVar12 = gnt4___shr2i(iVar10 * 0x41c64e6d + (int)((ulonglong)uVar8 * 0x41c64e6d >> 0x20) +
                              (uint)(0xffffcfc6 < uVar8 * 0x41c64e6d),uVar8 * 0x41c64e6d + 0x3039,
                              0x10);
        if ((uint)*(byte *)puVar7 != ((int)lVar12 + (uint)*pbVar9 & 0xff)) {
          gnt4___OSUnlockSramEx_bl(0);
          return 0xfffffffa;
        }
        lVar12 = lVar12 * 0x41c64e6d + 0x3039;
        uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
        iVar11 = iVar11 + 1;
        uVar8 = (uint)uVar13 & 0x7fff;
        iVar10 = 0;
        pbVar9 = pbVar9 + 1;
        puVar7 = (ushort *)((int)puVar7 + 1);
      } while (iVar11 < 0xc);
      gnt4___OSUnlockSramEx_bl(0);
      uVar5 = zz_021e03c_();
      if (puVar2[0x12] == uVar5) {
        uVar3 = 0;
      }
      else {
        uVar3 = 0xfffffff3;
      }
    }
    else {
      uVar3 = 0xfffffffa;
    }
  }
  else {
    uVar3 = 0xfffffffa;
  }
  return uVar3;
}



// ==== 80220384  zz_0220384_ ====

int zz_0220384_(int param_1,uint *param_2)

{
  ushort uVar1;
  uint uVar2;
  ushort *puVar3;
  int *piVar4;
  int *piVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int local_24 [6];
  
  piVar4 = local_24 + 2;
  piVar5 = local_24;
  iVar9 = 0;
  uVar8 = 0;
  uVar2 = 0;
  do {
    *piVar4 = *(int *)(param_1 + 0x80) + (uVar2 + 1) * 0x2000;
    sVar7 = 0;
    *piVar5 = *piVar4 + 0x1fc0;
    sVar6 = 0;
    puVar3 = (ushort *)*piVar4;
    iVar10 = 0x1ff;
    do {
      sVar6 = sVar6 + *puVar3 + puVar3[1] + puVar3[2] + puVar3[3] + puVar3[4] + puVar3[5] +
              puVar3[6] + puVar3[7];
      sVar7 = sVar7 + ~*puVar3 + ~puVar3[1] + ~puVar3[2] + ~puVar3[3] + ~puVar3[4] + ~puVar3[5] +
              ~puVar3[6] + ~puVar3[7];
      puVar3 = puVar3 + 8;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    iVar10 = 6;
    do {
      uVar1 = *puVar3;
      puVar3 = puVar3 + 1;
      sVar6 = sVar6 + uVar1;
      sVar7 = sVar7 + ~uVar1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    if (sVar6 == -1) {
      sVar6 = 0;
    }
    if (sVar7 == -1) {
      sVar7 = 0;
    }
    if ((sVar6 != *(short *)(*piVar5 + 0x3c)) || (sVar7 != *(short *)(*piVar5 + 0x3e))) {
      *(undefined4 *)(param_1 + 0x84) = 0;
      iVar9 = iVar9 + 1;
      uVar8 = uVar2;
    }
    uVar2 = uVar2 + 1;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  } while ((int)uVar2 < 2);
  if (iVar9 == 0) {
    if (*(int *)(param_1 + 0x84) == 0) {
      uVar8 = (uint)(-1 < (int)*(short *)(local_24[0] + 0x3a) - (int)*(short *)(local_24[1] + 0x3a))
      ;
      *(int *)(param_1 + 0x84) = local_24[uVar8 + 2];
      gnt4_memcpy((void *)local_24[uVar8 + 2],(void *)local_24[(uVar8 ^ 1) + 2],0x2000);
    }
    else {
      uVar8 = (uint)(*(int *)(param_1 + 0x84) != local_24[2]);
    }
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = uVar8;
  }
  return iVar9;
}



// ==== 802205c4  zz_02205c4_ ====

int zz_02205c4_(int param_1,uint *param_2)

{
  int *piVar1;
  uint uVar2;
  ushort *puVar3;
  short *psVar4;
  short *psVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int local_18 [3];
  
  uVar2 = 0;
  iVar10 = 0;
  uVar9 = 0;
  piVar1 = local_18;
  do {
    psVar5 = (short *)(*(int *)(param_1 + 0x80) + (uVar2 + 3) * 0x2000);
    *piVar1 = (int)psVar5;
    puVar3 = (ushort *)(psVar5 + 2);
    sVar8 = 0;
    sVar7 = 0;
    iVar11 = 0x1ff;
    do {
      sVar7 = sVar7 + *puVar3 + puVar3[1] + puVar3[2] + puVar3[3] + puVar3[4] + puVar3[5] +
              puVar3[6] + puVar3[7];
      sVar8 = sVar8 + ~*puVar3 + ~puVar3[1] + ~puVar3[2] + ~puVar3[3] + ~puVar3[4] + ~puVar3[5] +
              ~puVar3[6] + ~puVar3[7];
      puVar3 = puVar3 + 8;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    iVar11 = 6;
    do {
      uVar6 = *puVar3;
      puVar3 = puVar3 + 1;
      sVar7 = sVar7 + uVar6;
      sVar8 = sVar8 + ~uVar6;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    if (sVar7 == -1) {
      sVar7 = 0;
    }
    if (sVar8 == -1) {
      sVar8 = 0;
    }
    if ((*psVar5 == sVar7) && (psVar5[1] == sVar8)) {
      psVar4 = psVar5 + 5;
      sVar7 = 0;
      for (uVar6 = 5; uVar6 < *(ushort *)(param_1 + 0x10); uVar6 = uVar6 + 1) {
        if (*psVar4 == 0) {
          sVar7 = sVar7 + 1;
        }
        psVar4 = psVar4 + 1;
      }
      if (sVar7 != psVar5[3]) {
        *(undefined4 *)(param_1 + 0x88) = 0;
        iVar10 = iVar10 + 1;
        uVar9 = uVar2;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x88) = 0;
      iVar10 = iVar10 + 1;
      uVar9 = uVar2;
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while ((int)uVar2 < 2);
  if (iVar10 == 0) {
    if (*(int *)(param_1 + 0x88) == 0) {
      uVar9 = (uint)(-1 < (int)*(short *)(local_18[0] + 4) - (int)*(short *)(local_18[1] + 4));
      *(int *)(param_1 + 0x88) = local_18[uVar9];
      gnt4_memcpy((void *)local_18[uVar9],(void *)local_18[uVar9 ^ 1],0x2000);
    }
    else {
      uVar9 = (uint)(*(int *)(param_1 + 0x88) != local_18[0]);
    }
  }
  if (param_2 != (uint *)0x0) {
    *param_2 = uVar9;
  }
  return iVar10;
}



// ==== 80220848  zz_0220848_ ====

int zz_0220848_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_0220100_(param_1);
  if (-1 < iVar1) {
    iVar1 = zz_0220384_(param_1,(uint *)0x0);
    iVar2 = zz_02205c4_(param_1,(uint *)0x0);
    iVar1 = iVar1 + iVar2;
    if (iVar1 == 1) {
      iVar1 = -6;
    }
    else if ((iVar1 < 1) && (-1 < iVar1)) {
      iVar1 = 0;
    }
    else {
      iVar1 = -6;
    }
  }
  return iVar1;
}



// ==== 802208d4  zz_02208d4_ ====

int zz_02208d4_(int param_1,undefined4 *param_2,undefined *param_3)

{
  ushort *puVar1;
  uint uVar2;
  bool bVar3;
  byte bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  ushort uVar8;
  int iVar9;
  ushort *puVar10;
  short *psVar11;
  char *pcVar12;
  short *psVar13;
  ushort uVar14;
  short sVar15;
  void *__s;
  uint local_40;
  uint local_3c;
  int local_38 [4];
  int *local_28 [3];
  
  bVar4 = 0;
  bVar5 = false;
  bVar3 = false;
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = 0;
  }
  iVar6 = zz_021e07c_(param_1,local_28);
  if (-1 < iVar6) {
    iVar6 = zz_0220100_((int)local_28[0]);
    if (iVar6 < 0) {
      iVar6 = zz_021e134_(local_28[0],iVar6);
    }
    else {
      iVar6 = zz_0220384_((int)local_28[0],&local_40);
      iVar7 = zz_02205c4_((int)local_28[0],&local_3c);
      if (iVar6 + iVar7 < 2) {
        iVar9 = local_28[0][0x20];
        local_38[2] = iVar9 + 0x2000;
        local_38[0] = iVar9 + 0x6000;
        local_38[3] = iVar9 + 0x4000;
        local_38[1] = iVar9 + 0x8000;
        if (iVar6 + iVar7 == 1) {
          if (local_28[0][0x21] == 0) {
            local_28[0][0x21] = local_38[local_40 + 2];
            gnt4_memcpy((void *)local_38[local_40 + 2],(void *)local_38[(local_40 ^ 1) + 2],0x2000);
            bVar5 = true;
          }
          else {
            local_28[0][0x22] = local_38[local_3c];
            gnt4_memcpy((void *)local_38[local_3c],(void *)local_38[local_3c ^ 1],0x2000);
            bVar4 = 1;
          }
        }
        __s = (void *)local_38[local_3c ^ 1];
        gnt4_memset(__s,0,0x2000);
        iVar7 = 0x7f;
        iVar6 = 0;
        do {
          pcVar12 = (char *)(local_28[0][0x21] + iVar6);
          if (*pcVar12 != -1) {
            uVar8 = *(ushort *)(pcVar12 + 0x36);
            for (uVar14 = 0; (uVar8 != 0xffff && (uVar14 < *(ushort *)(pcVar12 + 0x38)));
                uVar14 = uVar14 + 1) {
              uVar2 = (uint)uVar8;
              if ((uVar2 < 5) || (*(ushort *)(local_28[0] + 4) <= uVar2)) {
LAB_80220ab8:
                iVar6 = zz_021e134_(local_28[0],-6);
                return iVar6;
              }
              iVar9 = uVar2 * 2;
              uVar8 = *(short *)((int)__s + iVar9) + 1;
              *(ushort *)((int)__s + iVar9) = uVar8;
              if (1 < uVar8) goto LAB_80220ab8;
              uVar8 = *(ushort *)(local_28[0][0x22] + iVar9);
            }
            if ((uVar14 != *(ushort *)(pcVar12 + 0x38)) || (uVar8 != 0xffff)) {
              iVar6 = zz_021e134_(local_28[0],-6);
              return iVar6;
            }
          }
          iVar6 = iVar6 + 0x40;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        psVar11 = (short *)((int)__s + 10);
        sVar15 = 0;
        iVar6 = 10;
        for (uVar8 = 5; uVar8 < *(ushort *)(local_28[0] + 4); uVar8 = uVar8 + 1) {
          uVar14 = *(ushort *)(local_28[0][0x22] + iVar6);
          if (*psVar11 == 0) {
            if (uVar14 != 0) {
              *(ushort *)(local_28[0][0x22] + iVar6) = 0;
              bVar3 = true;
            }
            sVar15 = sVar15 + 1;
          }
          else if (((uVar14 < 5) || (*(ushort *)(local_28[0] + 4) <= uVar14)) && (uVar14 != 0xffff))
          {
            iVar6 = zz_021e134_(local_28[0],-6);
            return iVar6;
          }
          iVar6 = iVar6 + 2;
          psVar11 = psVar11 + 1;
        }
        if (sVar15 != *(short *)(local_28[0][0x22] + 6)) {
          *(short *)(local_28[0][0x22] + 6) = sVar15;
          bVar3 = true;
        }
        if (bVar3) {
          psVar11 = (short *)local_28[0][0x22];
          psVar11[1] = 0;
          psVar13 = psVar11 + 1;
          puVar10 = (ushort *)(psVar11 + 2);
          *psVar11 = 0;
          iVar6 = 0x1ff;
          do {
            *psVar11 = *psVar11 + *puVar10;
            *psVar13 = *psVar13 + ~*puVar10;
            *psVar11 = *psVar11 + puVar10[1];
            *psVar13 = *psVar13 + ~puVar10[1];
            *psVar11 = *psVar11 + puVar10[2];
            *psVar13 = *psVar13 + ~puVar10[2];
            *psVar11 = *psVar11 + puVar10[3];
            *psVar13 = *psVar13 + ~puVar10[3];
            *psVar11 = *psVar11 + puVar10[4];
            *psVar13 = *psVar13 + ~puVar10[4];
            *psVar11 = *psVar11 + puVar10[5];
            *psVar13 = *psVar13 + ~puVar10[5];
            *psVar11 = *psVar11 + puVar10[6];
            *psVar13 = *psVar13 + ~puVar10[6];
            *psVar11 = *psVar11 + puVar10[7];
            puVar1 = puVar10 + 7;
            puVar10 = puVar10 + 8;
            *psVar13 = *psVar13 + ~*puVar1;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          iVar6 = 6;
          do {
            *psVar11 = *psVar11 + *puVar10;
            uVar8 = *puVar10;
            puVar10 = puVar10 + 1;
            *psVar13 = *psVar13 + ~uVar8;
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          if (*psVar11 == -1) {
            *psVar11 = 0;
          }
          if (*psVar13 == -1) {
            *psVar13 = 0;
          }
        }
        gnt4_memcpy((void *)local_38[local_3c ^ 1],(void *)local_38[local_3c],0x2000);
        if (bVar5) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = 0x2000;
          }
          iVar6 = zz_021fe8c_(param_1,param_3);
        }
        else if ((bool)(bVar4 | bVar3)) {
          if (param_2 != (undefined4 *)0x0) {
            *param_2 = 0x2000;
          }
          iVar6 = zz_021fc40_(param_1,(short *)local_28[0][0x22],param_3);
        }
        else {
          zz_021e134_(local_28[0],0);
          if (param_3 != (undefined *)0x0) {
            gnt4_OSDisableInterrupts_bl();
            (*(code *)param_3)(param_1,0);
            gnt4_OSRestoreInterrupts_bl();
          }
          iVar6 = 0;
        }
      }
      else {
        iVar6 = zz_021e134_(local_28[0],-6);
      }
    }
  }
  return iVar6;
}



// ==== 80220e64  CARDCheckAsync ====

void CARDCheckAsync(int param_1,undefined *param_2)

{
  undefined4 auStack_8 [2];
  
  zz_02208d4_(param_1,auStack_8,param_2);
  return;
}



// ==== 80220e8c  zz_0220e8c_ ====

undefined4 zz_0220e8c_(undefined1 *param_1)

{
  uint uVar1;
  
  if ((((uint)param_1 & 0xffff0000) != 0) && ((param_1 != &DAT_80000004 || (DAT_80435d60 == -1)))) {
    return 0;
  }
  if (((uint)param_1 & 3) != 0) {
    return 0;
  }
  uVar1 = (uint)param_1 & 0xfc;
  if (uVar1 != 0x20) {
    if (uVar1 < 0x20) {
      if (uVar1 != 8) {
        if (uVar1 < 8) {
          if (uVar1 != 4) {
            return 0;
          }
        }
        else if (uVar1 != 0x10) {
          return 0;
        }
      }
    }
    else if (uVar1 != 0x80) {
      if (0x7f < uVar1) {
        return 0;
      }
      if (uVar1 != 0x40) {
        return 0;
      }
    }
  }
  if (*(uint *)(&DAT_803aa4c0 + ((uint)param_1 >> 9 & 0x1c)) == 0) {
    return 0;
  }
  if ((((uint)param_1 & 0xfc) << 0x11) / *(uint *)(&DAT_803aa4c0 + ((uint)param_1 >> 9 & 0x1c)) < 8)
  {
    return 0;
  }
  return 1;
}



// ==== 80220f58  zz_0220f58_ ====

undefined4 zz_0220f58_(int param_1,uint *param_2,undefined4 *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *local_1c [2];
  
  if ((-1 < param_1) && (param_1 < 2)) {
    if ((DAT_800030e3 & 0x80) != 0) {
      return 0xfffffffd;
    }
    iVar3 = param_1 * 0x110;
    gnt4_OSDisableInterrupts_bl();
    iVar1 = zz_0207ed8_(param_1);
    if (iVar1 == -1) {
      uVar4 = 0xfffffffd;
    }
    else if (iVar1 == 0) {
      uVar4 = 0xffffffff;
    }
    else if ((&DAT_803f50e0)[param_1 * 0x44] == 0) {
      uVar2 = zz_0208ae4_(param_1);
      if ((uVar2 & 8) == 0) {
        iVar1 = zz_0208b24_(param_1,0,(byte *)local_1c);
        if (iVar1 == 0) {
          uVar4 = 0xffffffff;
        }
        else {
          iVar1 = zz_0220e8c_(local_1c[0]);
          if (iVar1 == 0) {
            uVar4 = 0xfffffffe;
          }
          else {
            if (param_2 != (uint *)0x0) {
              *param_2 = (uint)local_1c[0] & 0xfc;
            }
            if (param_3 != (undefined4 *)0x0) {
              *param_3 = *(undefined4 *)(&DAT_803aa4c0 + ((uint)local_1c[0] >> 9 & 0x1c));
            }
            uVar4 = 0;
          }
        }
      }
      else {
        uVar4 = 0xfffffffe;
      }
    }
    else if (*(int *)(&DAT_803f5104 + iVar3) < 1) {
      uVar4 = 0xffffffff;
    }
    else {
      if (param_2 != (uint *)0x0) {
        *param_2 = (uint)*(ushort *)(&DAT_803f50e8 + iVar3);
      }
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = *(undefined4 *)(&DAT_803f50ec + iVar3);
      }
      uVar4 = 0;
    }
    gnt4_OSRestoreInterrupts_bl();
    return uVar4;
  }
  return 0xffffff80;
}



// ==== 802210d4  zz_02210d4_ ====

int zz_02210d4_(int param_1)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  short sVar8;
  byte bVar9;
  int iVar10;
  undefined2 *puVar11;
  int iVar12;
  undefined2 *puVar13;
  int iVar14;
  char *pcVar15;
  char *pcVar16;
  byte local_1c [4];
  undefined1 *local_18 [2];
  
  iVar12 = param_1 * 0x110;
  if (*(int *)(&DAT_803f5104 + iVar12) == 0) {
    iVar10 = zz_0208b24_(param_1,0,(byte *)local_18);
    if (iVar10 == 0) {
      iVar10 = -3;
    }
    else {
      iVar10 = zz_0220e8c_(local_18[0]);
      if (iVar10 == 0) {
        iVar10 = -2;
      }
      else {
        iVar10 = 0;
      }
    }
    if (-1 < iVar10) {
      *(undefined1 **)(&DAT_803f51e8 + iVar12) = local_18[0];
      *(ushort *)(&DAT_803f50e8 + iVar12) = (ushort)local_18[0] & 0xfc;
      *(undefined4 *)(&DAT_803f50ec + iVar12) =
           *(undefined4 *)(&DAT_803aa4c0 + ((uint)local_18[0] >> 9 & 0x1c));
      *(short *)(&DAT_803f50f0 + iVar12) =
           (short)(((int)((uint)*(ushort *)(&DAT_803f50e8 + iVar12) << 0x14) >> 3) /
                  *(int *)(&DAT_803f50ec + iVar12));
      *(undefined4 *)(&DAT_803f50f4 + iVar12) =
           *(undefined4 *)(&DAT_803aa4e0 + ((uint)local_18[0] >> 6 & 0x1c));
      iVar10 = zz_021d620_(param_1);
      if ((-1 < iVar10) && (iVar10 = zz_021d530_(param_1,local_1c), -1 < iVar10)) {
        iVar10 = zz_0207e58_(param_1);
        if (iVar10 == 0) {
          iVar10 = -3;
        }
        else if ((local_1c[0] & 0x40) == 0) {
          iVar10 = zz_021e764_(param_1,(uint *)(&DAT_803f50f8 + iVar12));
          if (-1 < iVar10) {
            puVar11 = gnt4___OSLockSramEx_bl();
            puVar13 = puVar11 + param_1 * 6;
            *(undefined *)puVar13 = (&DAT_803f50f8)[iVar12];
            cVar1 = (&DAT_803f50f8)[iVar12];
            *(undefined *)((int)puVar13 + 1) = (&DAT_803f50f9)[iVar12];
            iVar14 = 8;
            cVar2 = (&DAT_803f50f9)[iVar12];
            *(undefined *)(puVar13 + 1) = (&DAT_803f50fa)[iVar12];
            cVar3 = (&DAT_803f50fa)[iVar12];
            *(undefined *)((int)puVar13 + 3) = (&DAT_803f50fb)[iVar12];
            cVar4 = (&DAT_803f50fb)[iVar12];
            *(undefined *)(puVar13 + 2) = (&DAT_803f50fc)[iVar12];
            cVar5 = (&DAT_803f50fc)[iVar12];
            *(undefined *)((int)puVar13 + 5) = (&DAT_803f50fd)[iVar12];
            cVar6 = (&DAT_803f50fd)[iVar12];
            *(undefined *)(puVar13 + 3) = (&DAT_803f50fe)[iVar12];
            cVar7 = (&DAT_803f50fe)[iVar12];
            *(undefined *)((int)puVar13 + 7) = (&DAT_803f50ff)[iVar12];
            bVar9 = cVar1 + cVar2 + cVar3 + cVar4 + cVar5 + cVar6 + cVar7 + (&DAT_803f50ff)[iVar12];
            pcVar15 = (char *)(puVar13 + 4);
            iVar12 = 4;
            do {
              pcVar16 = (char *)((int)(&DAT_803f50e0 + param_1 * 0x44) + iVar14 + 0x18);
              iVar14 = iVar14 + 1;
              *pcVar15 = *pcVar16;
              pcVar15 = pcVar15 + 1;
              bVar9 = bVar9 + *pcVar16;
              iVar12 = iVar12 + -1;
            } while (iVar12 != 0);
            *(byte *)((int)puVar11 + param_1 + 0x26) = ~bVar9;
            gnt4___OSUnlockSramEx_bl(1);
            return iVar10;
          }
        }
        else {
          *(undefined4 *)(&DAT_803f5104 + iVar12) = 1;
          puVar11 = gnt4___OSLockSramEx_bl();
          pcVar15 = (char *)(puVar11 + param_1 * 6);
          bVar9 = *pcVar15 + pcVar15[1] + pcVar15[2] + pcVar15[3] + pcVar15[4] + pcVar15[5] +
                  pcVar15[6] + pcVar15[7];
          pcVar15 = pcVar15 + 8;
          iVar10 = 4;
          do {
            cVar1 = *pcVar15;
            pcVar15 = pcVar15 + 1;
            bVar9 = bVar9 + cVar1;
            iVar10 = iVar10 + -1;
          } while (iVar10 != 0);
          gnt4___OSUnlockSramEx_bl(0);
          if (*(byte *)((int)puVar11 + param_1 + 0x26) == (byte)~bVar9) goto LAB_802213bc;
          iVar10 = -5;
        }
      }
    }
LAB_80221498:
    gnt4_EXIUnlock_bl(param_1);
    zz_02217bc_(param_1,iVar10);
  }
  else {
LAB_802213bc:
    if (*(int *)(&DAT_803f5104 + iVar12) == 1) {
      if (*(undefined1 **)(&DAT_803f51e8 + iVar12) == &DAT_80000004) {
        puVar11 = gnt4___OSLockSramEx_bl();
        sVar8 = puVar11[param_1 * 6];
        gnt4___OSUnlockSramEx_bl(0);
        if ((DAT_80435d60 == -1) || (sVar8 != DAT_80435d60)) {
          iVar10 = -2;
          goto LAB_80221498;
        }
      }
      *(undefined4 *)(&DAT_803f5104 + iVar12) = 2;
      iVar10 = zz_021d470_(param_1,1);
      if (iVar10 < 0) goto LAB_80221498;
      zz_0207c68_(param_1,-0x7fde2dd4);
      gnt4_EXIUnlock_bl(param_1);
      gnt4_DCInvalidateRange_bl((&DAT_803f5160)[param_1 * 0x44],0xa000);
    }
    iVar10 = zz_021f72c_(param_1,*(int *)(&DAT_803f50ec + iVar12) *
                                 (*(int *)(&DAT_803f5104 + iVar12) + -2),0x2000,
                         (&DAT_803f5160)[param_1 * 0x44] +
                         (*(int *)(&DAT_803f5104 + iVar12) + -2) * 0x2000,zz_02214e4_);
    if (iVar10 < 0) {
      zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,iVar10);
    }
  }
  return iVar10;
}



// ==== 802214e4  zz_02214e4_ ====

void zz_02214e4_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  iVar2 = param_1 * 0x110;
  if (param_2 != -3) {
    if (-4 < param_2) {
      if (param_2 == 1) {
        *(code **)(&DAT_803f51bc + iVar2) = zz_02214e4_;
        iVar1 = gnt4_EXILock_bl(param_1,0,-0x7fde2c14);
        if (iVar1 == 0) {
          return;
        }
        *(undefined4 *)(&DAT_803f51bc + iVar2) = 0;
        param_2 = zz_02210d4_(param_1);
      }
      else {
        if ((0 < param_2) || (param_2 < 0)) goto LAB_802215d0;
        iVar1 = *(int *)(&DAT_803f5104 + iVar2);
        *(int *)(&DAT_803f5104 + iVar2) = iVar1 + 1;
        if (6 < iVar1 + 1) {
          param_2 = zz_0220848_((int)(&DAT_803f50e0 + param_1 * 0x44));
          goto LAB_802215d0;
        }
        param_2 = zz_02210d4_(param_1);
      }
      if (-1 < param_2) {
        return;
      }
      goto LAB_802215d0;
    }
    if (param_2 != -5) goto LAB_802215d0;
  }
  zz_02217bc_(param_1,param_2);
LAB_802215d0:
  pcVar3 = *(code **)(&DAT_803f51b0 + iVar2);
  *(undefined4 *)(&DAT_803f51b0 + iVar2) = 0;
  zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  (*pcVar3)(param_1,param_2);
  return;
}



// ==== 8022161c  zz_022161c_ ====

int zz_022161c_(int param_1,undefined4 param_2,undefined4 param_3,undefined *param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  
  if ((param_1 < 0) || (1 < param_1)) {
    iVar1 = -0x80;
  }
  else if ((DAT_800030e3 & 0x80) == 0) {
    iVar1 = param_1 * 0x110;
    piVar4 = &DAT_803f50e0 + param_1 * 0x44;
    gnt4_OSDisableInterrupts_bl();
    if ((&DAT_803f50e4)[param_1 * 0x44] == -1) {
      gnt4_OSRestoreInterrupts_bl();
      iVar1 = -1;
    }
    else if ((*piVar4 == 0) && (uVar2 = zz_0208ae4_(param_1), (uVar2 & 8) != 0)) {
      gnt4_OSRestoreInterrupts_bl();
      iVar1 = -2;
    }
    else {
      (&DAT_803f50e4)[param_1 * 0x44] = 0xffffffff;
      (&DAT_803f5160)[param_1 * 0x44] = param_2;
      *(undefined4 *)(&DAT_803f51a4 + iVar1) = param_3;
      if (param_4 == (undefined *)0x0) {
        param_4 = &DAT_8021d150;
      }
      *(undefined **)(&DAT_803f51b0 + iVar1) = param_4;
      *(undefined4 *)(&DAT_803f51ac + iVar1) = 0;
      if ((*piVar4 == 0) && (iVar3 = zz_0207f8c_(param_1,FUN_8021d154), iVar3 == 0)) {
        (&DAT_803f50e4)[param_1 * 0x44] = 0xfffffffd;
        gnt4_OSRestoreInterrupts_bl();
        iVar1 = -3;
      }
      else {
        *(undefined4 *)(&DAT_803f5104 + iVar1) = 0;
        *piVar4 = 1;
        zz_0207c68_(param_1,0);
        gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + iVar1));
        *(undefined4 *)(&DAT_803f5164 + iVar1) = 0;
        *(undefined4 *)(&DAT_803f5168 + iVar1) = 0;
        gnt4_OSRestoreInterrupts_bl();
        *(code **)(&DAT_803f51bc + iVar1) = zz_02214e4_;
        iVar3 = gnt4_EXILock_bl(param_1,0,-0x7fde2c14);
        if (iVar3 == 0) {
          iVar1 = 0;
        }
        else {
          *(undefined4 *)(&DAT_803f51bc + iVar1) = 0;
          iVar1 = zz_02210d4_(param_1);
        }
      }
    }
  }
  else {
    iVar1 = -3;
  }
  return iVar1;
}



// ==== 802217bc  zz_02217bc_ ====

void zz_02217bc_(int param_1,undefined4 param_2)

{
  gnt4_OSDisableInterrupts_bl();
  if ((&DAT_803f50e0)[param_1 * 0x44] != 0) {
    zz_0207c68_(param_1,0);
    zz_0208098_(param_1);
    gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + param_1 * 0x110));
    (&DAT_803f50e0)[param_1 * 0x44] = 0;
    (&DAT_803f50e4)[param_1 * 0x44] = param_2;
    *(undefined4 *)(&DAT_803f5104 + param_1 * 0x110) = 0;
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80221858  zz_0221858_ ====

int zz_0221858_(int param_1)

{
  int iVar1;
  undefined4 auStack_14 [2];
  
  iVar1 = zz_021e07c_(param_1,auStack_14);
  if (-1 < iVar1) {
    gnt4_OSDisableInterrupts_bl();
    if ((&DAT_803f50e0)[param_1 * 0x44] != 0) {
      zz_0207c68_(param_1,0);
      zz_0208098_(param_1);
      gnt4_OSCancelAlarm_bl((int *)(&DAT_803f51c0 + param_1 * 0x110));
      (&DAT_803f50e0)[param_1 * 0x44] = 0;
      (&DAT_803f50e4)[param_1 * 0x44] = 0xfffffffd;
      *(undefined4 *)(&DAT_803f5104 + param_1 * 0x110) = 0;
    }
    gnt4_OSRestoreInterrupts_bl();
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 80221904  FUN_80221904 ====

void FUN_80221904(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  iVar2 = param_1 * 0x110;
  if (-1 < param_2) {
    *(int *)(&DAT_803f5108 + iVar2) = *(int *)(&DAT_803f5108 + iVar2) + 1;
    iVar1 = *(int *)(&DAT_803f5108 + iVar2);
    if (iVar1 < 5) {
      param_2 = zz_021deb0_(param_1,*(int *)(&DAT_803f50ec + iVar2) * iVar1,-0x7fdde6fc);
    }
    else {
      if (9 < iVar1) {
        *(int *)(&DAT_803f5164 + iVar2) = (&DAT_803f5160)[param_1 * 0x44] + 0x2000;
        gnt4_memcpy(*(void **)(&DAT_803f5164 + iVar2),
                    (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x4000),0x2000);
        *(int *)(&DAT_803f5168 + iVar2) = (&DAT_803f5160)[param_1 * 0x44] + 0x6000;
        gnt4_memcpy(*(void **)(&DAT_803f5168 + iVar2),
                    (void *)((&DAT_803f5160)[param_1 * 0x44] + 0x8000),0x2000);
        goto LAB_802219fc;
      }
      param_2 = zz_021f86c_(param_1,*(int *)(&DAT_803f50ec + iVar2) * (iVar1 + -5),0x2000,
                            (&DAT_803f5160)[param_1 * 0x44] + (iVar1 + -5) * 0x2000,FUN_80221904);
    }
    if (-1 < param_2) {
      return;
    }
  }
LAB_802219fc:
  pcVar3 = *(code **)(&DAT_803f51b0 + iVar2);
  *(undefined4 *)(&DAT_803f51b0 + iVar2) = 0;
  zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  (*pcVar3)(param_1,param_2);
  return;
}



// ==== 80221a48  __CARDFormatRegionAsync ====

int __CARDFormatRegionAsync(int param_1,ushort param_2,undefined *param_3)

{
  ulonglong uVar1;
  uint uVar2;
  int iVar3;
  undefined2 *puVar4;
  uint uVar5;
  ushort uVar6;
  short *__s;
  char *pcVar7;
  ushort *puVar8;
  short sVar9;
  char *pcVar10;
  ulonglong uVar11;
  longlong lVar12;
  undefined8 uVar13;
  int *local_40 [2];
  
  iVar3 = zz_021e07c_(param_1,local_40);
  if (-1 < iVar3) {
    puVar8 = (ushort *)local_40[0][0x20];
    gnt4_memset(puVar8,0xff,0x2000);
    uVar6 = DAT_cc00206e;
    puVar8[0x12] = param_2;
    puVar4 = gnt4___OSLockSram_bl();
    *(undefined4 *)(puVar8 + 10) = *(undefined4 *)(puVar4 + 6);
    *(uint *)(puVar8 + 0xc) = (uint)*(byte *)(puVar4 + 9);
    gnt4___OSUnlockSram_bl(0);
    uVar11 = gnt4_OSGetTime_bl();
    puVar4 = gnt4___OSLockSramEx_bl();
    pcVar10 = (char *)(puVar4 + param_1 * 6);
    sVar9 = 0;
    pcVar7 = pcVar10;
    uVar1 = uVar11;
    while( true ) {
      if (3 < sVar9) break;
      uVar2 = (int)uVar1 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)(uVar1 >> 0x20) * 0x41c64e6d +
                            (int)((uVar1 & 0xffffffff) * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)sVar9) = (char)lVar12 + *pcVar7;
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 1)) = (char)lVar12 + pcVar10[(short)(sVar9 + 1)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 2)) = (char)lVar12 + pcVar10[(short)(sVar9 + 2)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 3)) = (char)lVar12 + pcVar10[(short)(sVar9 + 3)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 4)) = (char)lVar12 + pcVar10[(short)(sVar9 + 4)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 5)) = (char)lVar12 + pcVar10[(short)(sVar9 + 5)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 6)) = (char)lVar12 + pcVar10[(short)(sVar9 + 6)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar5 = (uint)uVar13 & 0x7fff;
      uVar2 = uVar5 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)((ulonglong)uVar5 * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)(short)(sVar9 + 7)) = (char)lVar12 + pcVar10[(short)(sVar9 + 7)];
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar1 = (ulonglong)((uint)uVar13 & 0x7fff);
      pcVar7 = pcVar7 + 8;
      sVar9 = sVar9 + 8;
    }
    pcVar10 = pcVar10 + sVar9;
    while( true ) {
      if (0xb < sVar9) break;
      uVar2 = (int)uVar1 * 0x41c64e6d;
      lVar12 = gnt4___shr2i((int)(uVar1 >> 0x20) * 0x41c64e6d +
                            (int)((uVar1 & 0xffffffff) * 0x41c64e6d >> 0x20) +
                            (uint)(0xffffcfc6 < uVar2),uVar2 + 0x3039,0x10);
      *(char *)((int)puVar8 + (int)sVar9) = (char)lVar12 + *pcVar10;
      lVar12 = lVar12 * 0x41c64e6d + 0x3039;
      uVar13 = gnt4___shr2i((int)((ulonglong)lVar12 >> 0x20),(uint)lVar12,0x10);
      uVar1 = (ulonglong)((uint)uVar13 & 0x7fff);
      pcVar10 = pcVar10 + 1;
      sVar9 = sVar9 + 1;
    }
    gnt4___OSUnlockSramEx_bl(0);
    *(uint *)(puVar8 + 0xe) = (uint)uVar6;
    *(ulonglong *)(puVar8 + 6) = uVar11;
    puVar8[0x10] = 0;
    puVar8[0x11] = *(ushort *)(local_40[0] + 2);
    zz_021ff50_(puVar8,0x1fc,(short *)(puVar8 + 0xfe),(short *)(puVar8 + 0xff));
    for (uVar6 = 0; (short)uVar6 < 2; uVar6 = uVar6 + 1) {
      puVar8 = (ushort *)(local_40[0][0x20] + ((short)uVar6 + 1) * 0x2000);
      gnt4_memset(puVar8,0xff,0x2000);
      puVar8[0xffd] = uVar6;
      zz_021ff50_(puVar8,0x1ffc,(short *)(puVar8 + 0xffe),(short *)(puVar8 + 0xfff));
    }
    for (sVar9 = 0; sVar9 < 2; sVar9 = sVar9 + 1) {
      __s = (short *)(local_40[0][0x20] + (sVar9 + 3) * 0x2000);
      gnt4_memset(__s,0,0x2000);
      __s[2] = sVar9;
      __s[3] = *(short *)(local_40[0] + 4) + -5;
      __s[4] = 4;
      zz_021ff50_((ushort *)(__s + 2),0x1ffc,__s,__s + 1);
    }
    if (param_3 == (undefined *)0x0) {
      param_3 = &DAT_8021d150;
    }
    local_40[0][0x34] = (int)param_3;
    gnt4_DCStoreRange_bl(local_40[0][0x20],0xa000);
    local_40[0][10] = 0;
    iVar3 = zz_021deb0_(param_1,local_40[0][3] * local_40[0][10],-0x7fdde6fc);
    if (iVar3 < 0) {
      zz_021e134_(local_40[0],iVar3);
    }
  }
  return iVar3;
}



// ==== 802220a0  CARDFormatAsync ====

void CARDFormatAsync(int param_1,undefined *param_2)

{
  ushort uVar1;
  
  uVar1 = zz_021e03c_();
  __CARDFormatRegionAsync(param_1,uVar1,param_2);
  return;
}



// ==== 802220e8  zz_02220e8_ ====

undefined4 zz_02220e8_(int param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  
  pcVar3 = (char *)(param_1 + 8);
  iVar4 = 0x20;
  do {
    iVar4 = iVar4 + -1;
    if (iVar4 < 0) {
      if (*param_2 == '\0') {
        return 1;
      }
      return 0;
    }
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
    cVar2 = *param_2;
    param_2 = param_2 + 1;
    if (cVar1 != cVar2) {
      return 0;
    }
  } while (cVar2 != '\0');
  return 1;
}



// ==== 80222150  zz_0222150_ ====

undefined4 zz_0222150_(int param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined *__s2;
  
  __s2 = *(undefined **)(param_1 + 0x10c);
  if (*param_2 == -1) {
    uVar1 = 0xfffffffc;
  }
  else if ((__s2 == &DAT_803f5300) ||
          ((iVar2 = gnt4_memcmp(param_2,__s2,4), iVar2 == 0 &&
           (iVar2 = gnt4_memcmp(param_2 + 4,__s2 + 4,2), iVar2 == 0)))) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0xfffffff6;
  }
  return uVar1;
}



// ==== 802221e4  zz_02221e4_ ====

int zz_02221e4_(int param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  undefined *__s2;
  int iVar3;
  
  __s2 = *(undefined **)(param_1 + 0x10c);
  if (*param_2 == -1) {
    iVar3 = -4;
  }
  else if ((__s2 == &DAT_803f5300) ||
          ((iVar3 = gnt4_memcmp(param_2,__s2,4), iVar3 == 0 &&
           (iVar3 = gnt4_memcmp(param_2 + 4,__s2 + 4,2), iVar3 == 0)))) {
    iVar3 = 0;
  }
  else {
    iVar3 = -10;
  }
  if (iVar3 == -10) {
    bVar1 = param_2[0x34] & DAT_80435d62;
    if ((((bVar1 & 0x20) == 0) || (iVar2 = gnt4_memcmp(param_2,&DAT_803f5300,4), iVar2 != 0)) ||
       (iVar2 = gnt4_memcmp(param_2 + 4,&DAT_803f5304,2), iVar2 != 0)) {
      if ((((bVar1 & 0x40) != 0) && (iVar2 = gnt4_memcmp(param_2,&DAT_803f5300,4), iVar2 == 0)) &&
         (iVar2 = gnt4_memcmp(param_2 + 4,__s2 + 4,2), iVar2 == 0)) {
        iVar3 = 0;
      }
    }
    else {
      iVar3 = 0;
    }
  }
  return iVar3;
}



// ==== 80222318  zz_0222318_ ====

int zz_0222318_(int param_1,char *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x10c);
  iVar2 = zz_0222150_(param_1,param_2);
  if (iVar2 == -10) {
    bVar1 = param_2[0x34] & DAT_80435d62;
    if ((((bVar1 & 0x20) == 0) || (iVar3 = gnt4_memcmp(param_2,&DAT_803f5300,4), iVar3 != 0)) ||
       (iVar3 = gnt4_memcmp(param_2 + 4,&DAT_803f5304,2), iVar3 != 0)) {
      if ((((bVar1 & 0x40) != 0) && (iVar3 = gnt4_memcmp(param_2,&DAT_803f5300,4), iVar3 == 0)) &&
         (iVar4 = gnt4_memcmp(param_2 + 4,(void *)(iVar4 + 4),2), iVar4 == 0)) {
        iVar2 = 0;
      }
    }
    else {
      iVar2 = 0;
    }
  }
  if ((iVar2 == -10) && ((param_2[0x34] & 4U) != 0)) {
    iVar2 = 0;
  }
  return iVar2;
}



// ==== 8022240c  __CARDGetFileNo ====

undefined4 __CARDGetFileNo(int *param_1,char *param_2,int *param_3)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  char *__s1;
  char *pcVar6;
  char *pcVar7;
  undefined *__s2;
  int iVar8;
  
  if (*param_1 == 0) {
    uVar5 = 0xfffffffd;
  }
  else {
    __s1 = (char *)zz_021fcec_((int)param_1);
    iVar8 = 0;
    do {
      __s2 = (undefined *)param_1[0x43];
      if (*__s1 == -1) {
        iVar4 = -4;
      }
      else if ((__s2 == &DAT_803f5300) ||
              ((iVar4 = gnt4_memcmp(__s1,__s2,4), iVar4 == 0 &&
               (iVar4 = gnt4_memcmp(__s1 + 4,__s2 + 4,2), iVar4 == 0)))) {
        iVar4 = 0;
      }
      else {
        iVar4 = -10;
      }
      if (-1 < iVar4) {
        pcVar6 = __s1 + 8;
        iVar4 = 0x20;
        pcVar7 = param_2;
        do {
          iVar4 = iVar4 + -1;
          if (iVar4 < 0) {
            if (*pcVar7 == '\0') {
              bVar3 = true;
            }
            else {
              bVar3 = false;
            }
            goto LAB_80222520;
          }
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          cVar2 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          if (cVar1 != cVar2) {
            bVar3 = false;
            goto LAB_80222520;
          }
        } while (cVar2 != '\0');
        bVar3 = true;
LAB_80222520:
        if (bVar3) {
          *param_3 = iVar8;
          return 0;
        }
      }
      iVar8 = iVar8 + 1;
      __s1 = __s1 + 0x40;
    } while (iVar8 < 0x7f);
    uVar5 = 0xfffffffc;
  }
  return uVar5;
}



// ==== 8022255c  zz_022255c_ ====

int zz_022255c_(int param_1,int param_2,int *param_3)

{
  int iVar1;
  char *pcVar2;
  int *local_14;
  
  if ((param_2 < 0) || (0x7e < param_2)) {
    iVar1 = -0x80;
  }
  else {
    *param_3 = -1;
    iVar1 = zz_021e07c_(param_1,&local_14);
    if (-1 < iVar1) {
      iVar1 = zz_021fcec_((int)local_14);
      pcVar2 = (char *)(iVar1 + param_2 * 0x40);
      iVar1 = zz_02221e4_((int)local_14,pcVar2);
      if ((iVar1 == -10) && ((pcVar2[0x34] & 4U) != 0)) {
        iVar1 = 0;
      }
      if (-1 < iVar1) {
        if ((*(ushort *)(pcVar2 + 0x36) < 5) ||
           (*(ushort *)(local_14 + 4) <= *(ushort *)(pcVar2 + 0x36))) {
          iVar1 = -6;
        }
        else {
          *param_3 = param_1;
          param_3[1] = param_2;
          param_3[2] = 0;
          *(undefined2 *)(param_3 + 4) = *(undefined2 *)(pcVar2 + 0x36);
        }
      }
      iVar1 = zz_021e134_(local_14,iVar1);
    }
  }
  return iVar1;
}



// ==== 80222660  zz_0222660_ ====

void zz_0222660_(int param_1,char *param_2,int *param_3)

{
  ushort uVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int unaff_r31;
  int *local_24 [2];
  
  *param_3 = -1;
  iVar3 = zz_021e07c_(param_1,local_24);
  piVar2 = local_24[0];
  if (-1 < iVar3) {
    if (*local_24[0] == 0) {
      iVar5 = -3;
    }
    else {
      pcVar4 = (char *)zz_021fcec_((int)local_24[0]);
      iVar3 = 0;
      do {
        iVar5 = zz_0222150_((int)piVar2,pcVar4);
        if ((-1 < iVar5) && (iVar5 = zz_02220e8_((int)pcVar4,param_2), iVar5 != 0)) {
          iVar5 = 0;
          unaff_r31 = iVar3;
          goto LAB_80222708;
        }
        iVar3 = iVar3 + 1;
        pcVar4 = pcVar4 + 0x40;
      } while (iVar3 < 0x7f);
      iVar5 = -4;
    }
LAB_80222708:
    if (-1 < iVar5) {
      iVar3 = zz_021fcec_((int)local_24[0]);
      iVar3 = iVar3 + unaff_r31 * 0x40;
      uVar1 = *(ushort *)(iVar3 + 0x36);
      if ((uVar1 < 5) || (*(ushort *)(local_24[0] + 4) <= uVar1)) {
        iVar5 = -6;
      }
      else {
        *param_3 = param_1;
        param_3[1] = unaff_r31;
        param_3[2] = 0;
        *(undefined2 *)(param_3 + 4) = *(undefined2 *)(iVar3 + 0x36);
      }
    }
    zz_021e134_(local_24[0],iVar5);
  }
  return;
}



// ==== 8022277c  zz_022277c_ ====

void zz_022277c_(int *param_1)

{
  int iVar1;
  int *local_c [2];
  
  iVar1 = zz_021e07c_(*param_1,local_c);
  if (-1 < iVar1) {
    *param_1 = -1;
    zz_021e134_(local_c[0],0);
  }
  return;
}



// ==== 802227d0  zz_02227d0_ ====

undefined4 zz_02227d0_(void)

{
  return 0;
}



// ==== 802227d8  FUN_802227d8 ====

void FUN_802227d8(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  code *pcVar4;
  void *__dest;
  undefined8 uVar5;
  
  iVar3 = param_1 * 0x110;
  pcVar4 = *(code **)(&DAT_803f51b0 + iVar3);
  *(undefined4 *)(&DAT_803f51b0 + iVar3) = 0;
  if (-1 < param_2) {
    iVar2 = zz_021fcec_((int)(&DAT_803f50e0 + param_1 * 0x44));
    __dest = (void *)(iVar2 + (uint)*(ushort *)(&DAT_803f519c + iVar3) * 0x40);
    gnt4_memcpy(__dest,(void *)(&DAT_803f51ec)[param_1 * 0x44],4);
    gnt4_memcpy((void *)((int)__dest + 4),(void *)((&DAT_803f51ec)[param_1 * 0x44] + 4),2);
    *(undefined1 *)((int)__dest + 0x34) = 4;
    *(undefined1 *)((int)__dest + 0x35) = 0;
    *(undefined2 *)((int)__dest + 0x36) = *(undefined2 *)(&DAT_803f519e + iVar3);
    *(undefined1 *)((int)__dest + 7) = 0;
    *(undefined4 *)((int)__dest + 0x2c) = 0xffffffff;
    *(undefined2 *)((int)__dest + 0x30) = 0;
    *(undefined2 *)((int)__dest + 0x32) = 0;
    *(undefined4 *)((int)__dest + 0x3c) = 0xffffffff;
    *(ushort *)((int)__dest + 0x32) = *(ushort *)((int)__dest + 0x32) & 0xfffc | 1;
    *(undefined4 *)(*(int *)(&DAT_803f51a0 + iVar3) + 8) = 0;
    *(undefined2 *)(*(int *)(&DAT_803f51a0 + iVar3) + 0x10) = *(undefined2 *)((int)__dest + 0x36);
    uVar1 = DAT_800000f8 >> 2;
    uVar5 = gnt4_OSGetTime_bl();
    uVar5 = gnt4___div2i((uint)((ulonglong)uVar5 >> 0x20),(uint)uVar5,0,uVar1);
    *(int *)((int)__dest + 0x28) = (int)uVar5;
    param_2 = zz_021fe8c_(param_1,pcVar4);
    if (-1 < param_2) {
      return;
    }
  }
  zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  if (pcVar4 != (code *)0x0) {
    (*pcVar4)(param_1,param_2);
  }
  return;
}



// ==== 80222908  zz_0222908_ ====

int zz_0222908_(int param_1,char *param_2,uint param_3,int *param_4,undefined *param_5)

{
  size_t sVar1;
  int iVar2;
  char *pcVar3;
  ushort uVar4;
  char *__s1;
  ushort uVar5;
  int *local_2c [2];
  
  sVar1 = strlen(param_2);
  if (sVar1 < 0x21) {
    iVar2 = zz_021e07c_(param_1,local_2c);
    if (-1 < iVar2) {
      if ((param_3 == 0) || (param_3 != (param_3 / (uint)local_2c[0][3]) * local_2c[0][3])) {
        iVar2 = -0x80;
      }
      else {
        uVar5 = 0xffff;
        pcVar3 = (char *)zz_021fcec_((int)local_2c[0]);
        __s1 = pcVar3;
        for (uVar4 = 0; uVar4 < 0x7f; uVar4 = uVar4 + 1) {
          if (*__s1 == -1) {
            if (uVar5 == 0xffff) {
              uVar5 = uVar4;
            }
          }
          else {
            iVar2 = gnt4_memcmp(__s1,(void *)local_2c[0][0x43],4);
            if (((iVar2 == 0) &&
                (iVar2 = gnt4_memcmp(__s1 + 4,(void *)(local_2c[0][0x43] + 4),2), iVar2 == 0)) &&
               (iVar2 = zz_02220e8_((int)__s1,param_2), iVar2 != 0)) {
              iVar2 = zz_021e134_(local_2c[0],-7);
              return iVar2;
            }
          }
          __s1 = __s1 + 0x40;
        }
        if (uVar5 == 0xffff) {
          iVar2 = zz_021e134_(local_2c[0],-8);
        }
        else {
          iVar2 = zz_021f8e8_((int)local_2c[0]);
          if (local_2c[0][3] * (uint)*(ushort *)(iVar2 + 6) < param_3) {
            iVar2 = zz_021e134_(local_2c[0],-9);
          }
          else {
            if (param_5 == (undefined *)0x0) {
              param_5 = &DAT_8021d150;
            }
            local_2c[0][0x34] = (int)param_5;
            *(ushort *)(local_2c[0] + 0x2f) = uVar5;
            *(short *)(pcVar3 + (uint)uVar5 * 0x40 + 0x38) = (short)(param_3 / (uint)local_2c[0][3])
            ;
            zz_0238cbc_((int)(pcVar3 + (uint)uVar5 * 0x40 + 8),(int)param_2,0x20);
            local_2c[0][0x30] = (int)param_4;
            *param_4 = param_1;
            param_4[1] = (uint)uVar5;
            iVar2 = zz_021fa8c_(param_1,param_3 / (uint)local_2c[0][3],FUN_802227d8);
            if (iVar2 < 0) {
              iVar2 = zz_021e134_(local_2c[0],iVar2);
            }
          }
        }
      }
    }
  }
  else {
    iVar2 = -0xc;
  }
  return iVar2;
}



// ==== 80222b28  zz_0222b28_ ====

int zz_0222b28_(int *param_1,int param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  int iVar2;
  int *local_18 [2];
  
  iVar1 = zz_021e07c_(*param_1,local_18);
  if (-1 < iVar1) {
    if (((*(ushort *)(param_1 + 4) < 5) ||
        ((uint)*(ushort *)(local_18[0] + 4) <= (uint)*(ushort *)(param_1 + 4))) ||
       ((int)((uint)*(ushort *)(local_18[0] + 4) * local_18[0][3]) <= param_1[2])) {
      iVar1 = zz_021e134_(local_18[0],-0x80);
    }
    else {
      iVar1 = zz_021fcec_((int)local_18[0]);
      iVar1 = iVar1 + param_1[1] * 0x40;
      iVar2 = (uint)*(ushort *)(iVar1 + 0x38) * local_18[0][3];
      if (((int)param_3 < iVar2) && ((int)(param_3 + param_2) <= iVar2)) {
        local_18[0][0x30] = (int)param_1;
        param_1[3] = param_2;
        if ((int)param_3 < param_1[2]) {
          param_1[2] = 0;
          *(undefined2 *)(param_1 + 4) = *(undefined2 *)(iVar1 + 0x36);
          if ((*(ushort *)(param_1 + 4) < 5) ||
             (*(ushort *)(local_18[0] + 4) <= *(ushort *)(param_1 + 4))) {
            iVar1 = zz_021e134_(local_18[0],-6);
            return iVar1;
          }
        }
        iVar1 = zz_021f8e8_((int)local_18[0]);
        do {
          if ((param_3 & ~(local_18[0][3] - 1U)) <= (uint)param_1[2]) {
            param_1[2] = param_3;
            *param_4 = local_18[0];
            return 0;
          }
          param_1[2] = param_1[2] + local_18[0][3];
          *(undefined2 *)(param_1 + 4) = *(undefined2 *)(iVar1 + (uint)*(ushort *)(param_1 + 4) * 2)
          ;
        } while ((4 < *(ushort *)(param_1 + 4)) &&
                (*(ushort *)(param_1 + 4) < *(ushort *)(local_18[0] + 4)));
        iVar1 = zz_021e134_(local_18[0],-6);
      }
      else {
        iVar1 = zz_021e134_(local_18[0],-0xb);
      }
    }
  }
  return iVar1;
}



// ==== 80222ce0  FUN_80222ce0 ====

void FUN_80222ce0(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  code *pcVar7;
  int iVar8;
  
  iVar4 = param_1 * 0x110;
  if (-1 < param_2) {
    iVar8 = *(int *)(&DAT_803f51a0 + iVar4);
    if (*(int *)(iVar8 + 0xc) < 0) {
      param_2 = -0xe;
    }
    else {
      iVar6 = (~(*(int *)(&DAT_803f50ec + iVar4) - 1U) &
              *(int *)(iVar8 + 8) + *(int *)(&DAT_803f50ec + iVar4)) - *(int *)(iVar8 + 8);
      *(int *)(iVar8 + 0xc) = *(int *)(iVar8 + 0xc) - iVar6;
      if (0 < *(int *)(iVar8 + 0xc)) {
        iVar2 = zz_021f8e8_((int)(&DAT_803f50e0 + param_1 * 0x44));
        *(int *)(iVar8 + 8) = *(int *)(iVar8 + 8) + iVar6;
        *(undefined2 *)(iVar8 + 0x10) = *(undefined2 *)(iVar2 + (uint)*(ushort *)(iVar8 + 0x10) * 2)
        ;
        uVar3 = (uint)*(ushort *)(iVar8 + 0x10);
        if ((uVar3 < 5) || (*(ushort *)(&DAT_803f50f0 + iVar4) <= uVar3)) {
          param_2 = -6;
        }
        else {
          uVar1 = *(uint *)(&DAT_803f50ec + iVar4);
          uVar5 = uVar1;
          if ((int)*(uint *)(iVar8 + 0xc) < (int)uVar1) {
            uVar5 = *(uint *)(iVar8 + 0xc);
          }
          param_2 = zz_021f72c_(param_1,uVar1 * uVar3,uVar5,*(undefined4 *)(&DAT_803f5194 + iVar4),
                                FUN_80222ce0);
          if (-1 < param_2) {
            return;
          }
        }
      }
    }
  }
  pcVar7 = *(code **)(&DAT_803f51b0 + iVar4);
  *(undefined4 *)(&DAT_803f51b0 + iVar4) = 0;
  zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
  (*pcVar7)(param_1,param_2);
  return;
}



// ==== 80222e10  zz_0222e10_ ====

int zz_0222e10_(int *param_1,uint param_2,uint param_3,uint param_4,undefined *param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int *local_14;
  
  if (((param_4 & 0x1ff) == 0) && ((param_3 & 0x1ff) == 0)) {
    iVar1 = zz_0222b28_(param_1,param_3,param_4,&local_14);
    if (-1 < iVar1) {
      iVar1 = zz_021fcec_((int)local_14);
      iVar1 = zz_0222318_((int)local_14,(char *)(iVar1 + param_1[1] * 0x40));
      if (iVar1 < 0) {
        iVar1 = zz_021e134_(local_14,iVar1);
      }
      else {
        gnt4_DCInvalidateRange_bl(param_2,param_3);
        if (param_5 == (undefined *)0x0) {
          param_5 = &DAT_8021d150;
        }
        local_14[0x34] = (int)param_5;
        iVar1 = local_14[3];
        uVar3 = param_1[2] & iVar1 - 1U;
        uVar2 = iVar1 - uVar3;
        if ((int)param_3 < (int)uVar2) {
          uVar2 = param_3;
        }
        iVar1 = zz_021f72c_(*param_1,uVar3 + iVar1 * (uint)*(ushort *)(param_1 + 4),uVar2,param_2,
                            FUN_80222ce0);
        if (iVar1 < 0) {
          zz_021e134_(local_14,iVar1);
        }
      }
    }
  }
  else {
    iVar1 = -0x80;
  }
  return iVar1;
}



// ==== 80222f54  FUN_80222f54 ====

void FUN_80222f54(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  code *pcVar6;
  int *piVar7;
  undefined8 uVar8;
  
  iVar4 = param_1 * 0x110;
  piVar7 = &DAT_803f50e0 + param_1 * 0x44;
  if (-1 < param_2) {
    iVar5 = *(int *)(&DAT_803f51a0 + iVar4);
    if (*(int *)(iVar5 + 0xc) < 0) {
      param_2 = -0xe;
    }
    else {
      *(int *)(iVar5 + 0xc) = *(int *)(iVar5 + 0xc) - *(int *)(&DAT_803f50ec + iVar4);
      if (*(int *)(iVar5 + 0xc) < 1) {
        iVar1 = zz_021fcec_((int)piVar7);
        iVar5 = *(int *)(iVar5 + 4);
        uVar3 = DAT_800000f8 >> 2;
        uVar8 = gnt4_OSGetTime_bl();
        uVar8 = gnt4___div2i((uint)((ulonglong)uVar8 >> 0x20),(uint)uVar8,0,uVar3);
        *(int *)(iVar1 + iVar5 * 0x40 + 0x28) = (int)uVar8;
        uVar2 = *(undefined4 *)(&DAT_803f51b0 + iVar4);
        *(undefined4 *)(&DAT_803f51b0 + iVar4) = 0;
        param_2 = zz_021fe8c_(param_1,uVar2);
      }
      else {
        iVar1 = zz_021f8e8_((int)piVar7);
        *(int *)(iVar5 + 8) = *(int *)(iVar5 + 8) + *(int *)(&DAT_803f50ec + iVar4);
        *(undefined2 *)(iVar5 + 0x10) = *(undefined2 *)(iVar1 + (uint)*(ushort *)(iVar5 + 0x10) * 2)
        ;
        uVar3 = (uint)*(ushort *)(iVar5 + 0x10);
        if ((uVar3 < 5) || (*(ushort *)(&DAT_803f50f0 + iVar4) <= uVar3)) {
          param_2 = -6;
          goto LAB_80223078;
        }
        param_2 = zz_021deb0_(param_1,*(int *)(&DAT_803f50ec + iVar4) * uVar3,-0x7fddcf3c);
      }
      if (-1 < param_2) {
        return;
      }
    }
  }
LAB_80223078:
  pcVar6 = *(code **)(&DAT_803f51b0 + iVar4);
  *(undefined4 *)(&DAT_803f51b0 + iVar4) = 0;
  zz_021e134_(piVar7,param_2);
  (*pcVar6)(param_1,param_2);
  return;
}



// ==== 802230c4  FUN_802230c4 ====

void FUN_802230c4(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1 * 0x110;
  if ((param_2 < 0) ||
     (param_2 = zz_021f86c_(param_1,*(uint *)(&DAT_803f50ec + iVar1) *
                                    (uint)*(ushort *)(*(int *)(&DAT_803f51a0 + iVar1) + 0x10),
                            *(uint *)(&DAT_803f50ec + iVar1),*(undefined4 *)(&DAT_803f5194 + iVar1),
                            FUN_80222f54), param_2 < 0)) {
    pcVar2 = *(code **)(&DAT_803f51b0 + iVar1);
    *(undefined4 *)(&DAT_803f51b0 + iVar1) = 0;
    zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2);
    (*pcVar2)(param_1,param_2);
  }
  return;
}



// ==== 80223174  zz_0223174_ ====

int zz_0223174_(int *param_1,uint param_2,uint param_3,uint param_4,undefined *param_5)

{
  int iVar1;
  int *local_1c [2];
  
  iVar1 = zz_0222b28_(param_1,param_3,param_4,local_1c);
  if (-1 < iVar1) {
    if (((param_4 & local_1c[0][3] - 1U) == 0) && ((param_3 & local_1c[0][3] - 1U) == 0)) {
      iVar1 = zz_021fcec_((int)local_1c[0]);
      iVar1 = zz_02221e4_((int)local_1c[0],(char *)(iVar1 + param_1[1] * 0x40));
      if (iVar1 < 0) {
        iVar1 = zz_021e134_(local_1c[0],iVar1);
      }
      else {
        gnt4_DCStoreRange_bl(param_2,param_3);
        if (param_5 == (undefined *)0x0) {
          param_5 = &DAT_8021d150;
        }
        local_1c[0][0x34] = (int)param_5;
        local_1c[0][0x2d] = param_2;
        iVar1 = zz_021deb0_(*param_1,local_1c[0][3] * (uint)*(ushort *)(param_1 + 4),-0x7fddcf3c);
        if (iVar1 < 0) {
          zz_021e134_(local_1c[0],iVar1);
        }
      }
    }
    else {
      iVar1 = zz_021e134_(local_1c[0],-0x80);
    }
  }
  return iVar1;
}



// ==== 80223288  FUN_80223288 ====

void FUN_80223288(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  
  iVar1 = param_1 * 0x110;
  pcVar2 = *(code **)(&DAT_803f51b0 + iVar1);
  *(undefined4 *)(&DAT_803f51b0 + iVar1) = 0;
  if (((param_2 < 0) ||
      (param_2 = __CARDFreeBlock(param_1,*(ushort *)(&DAT_803f519e + iVar1),pcVar2), param_2 < 0))
     && (zz_021e134_(&DAT_803f50e0 + param_1 * 0x44,param_2), pcVar2 != (code *)0x0)) {
    (*pcVar2)(param_1,param_2);
  }
  return;
}



// ==== 8022332c  CARDDeleteAsync ====

int CARDDeleteAsync(int param_1,char *param_2,undefined *param_3)

{
  int iVar1;
  void *__s;
  int local_1c;
  int *local_18 [3];
  
  iVar1 = zz_021e07c_(param_1,local_18);
  if (-1 < iVar1) {
    iVar1 = __CARDGetFileNo(local_18[0],param_2,&local_1c);
    if (iVar1 < 0) {
      iVar1 = zz_021e134_(local_18[0],iVar1);
    }
    else {
      iVar1 = zz_02227d0_();
      if (iVar1 == 0) {
        iVar1 = zz_021fcec_((int)local_18[0]);
        __s = (void *)(iVar1 + local_1c * 0x40);
        *(undefined2 *)((int)local_18[0] + 0xbe) = *(undefined2 *)((int)__s + 0x36);
        gnt4_memset(__s,0xff,0x40);
        if (param_3 == (undefined *)0x0) {
          param_3 = &DAT_8021d150;
        }
        local_18[0][0x34] = (int)param_3;
        iVar1 = zz_021fe8c_(param_1,FUN_80223288);
        if (iVar1 < 0) {
          zz_021e134_(local_18[0],iVar1);
        }
      }
      else {
        iVar1 = zz_021e134_(local_18[0],-1);
      }
    }
  }
  return iVar1;
}



// ==== 8022343c  zz_022343c_ ====

void zz_022343c_(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = *(int *)(param_1 + 0x2c);
  if (iVar6 == -1) {
    *(undefined1 *)(param_2 + 0x2e) = 0;
    iVar6 = 0;
    *(undefined2 *)(param_2 + 0x34) = 0;
    *(undefined2 *)(param_2 + 0x36) = 0;
  }
  bVar1 = false;
  bVar3 = *(byte *)(param_1 + 7) & 3;
  if (bVar3 == 2) {
    *(int *)(param_2 + 0x3c) = iVar6;
    iVar6 = iVar6 + 0x1800;
    *(undefined4 *)(param_2 + 0x40) = 0xffffffff;
  }
  else if ((bVar3 < 2) && ((*(byte *)(param_1 + 7) & 3) != 0)) {
    *(int *)(param_2 + 0x3c) = iVar6;
    iVar5 = iVar6 + 0xc00;
    iVar6 = iVar6 + 0xe00;
    *(int *)(param_2 + 0x40) = iVar5;
  }
  else {
    *(undefined4 *)(param_2 + 0x3c) = 0xffffffff;
    *(undefined4 *)(param_2 + 0x40) = 0xffffffff;
  }
  iVar7 = 2;
  uVar4 = 0;
  iVar5 = param_2;
  do {
    uVar2 = (int)(uint)*(ushort *)(param_1 + 0x30) >> (uVar4 & 0x3f) & 3;
    if (uVar2 == 2) {
      *(int *)(iVar5 + 0x44) = iVar6;
      iVar6 = iVar6 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      *(int *)(iVar5 + 0x44) = iVar6;
      bVar1 = true;
      iVar6 = iVar6 + 0x400;
    }
    else {
      *(undefined4 *)(iVar5 + 0x44) = 0xffffffff;
    }
    uVar2 = (int)(uint)*(ushort *)(param_1 + 0x30) >> (uVar4 + 2 & 0x3f) & 3;
    if (uVar2 == 2) {
      *(int *)(iVar5 + 0x48) = iVar6;
      iVar6 = iVar6 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      *(int *)(iVar5 + 0x48) = iVar6;
      bVar1 = true;
      iVar6 = iVar6 + 0x400;
    }
    else {
      *(undefined4 *)(iVar5 + 0x48) = 0xffffffff;
    }
    uVar2 = (int)(uint)*(ushort *)(param_1 + 0x30) >> (uVar4 + 4 & 0x3f) & 3;
    if (uVar2 == 2) {
      *(int *)(iVar5 + 0x4c) = iVar6;
      iVar6 = iVar6 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      *(int *)(iVar5 + 0x4c) = iVar6;
      bVar1 = true;
      iVar6 = iVar6 + 0x400;
    }
    else {
      *(undefined4 *)(iVar5 + 0x4c) = 0xffffffff;
    }
    uVar2 = (int)(uint)*(ushort *)(param_1 + 0x30) >> (uVar4 + 6 & 0x3f) & 3;
    if (uVar2 == 2) {
      *(int *)(iVar5 + 0x50) = iVar6;
      iVar6 = iVar6 + 0x800;
    }
    else if ((uVar2 < 2) && (uVar2 != 0)) {
      *(int *)(iVar5 + 0x50) = iVar6;
      bVar1 = true;
      iVar6 = iVar6 + 0x400;
    }
    else {
      *(undefined4 *)(iVar5 + 0x50) = 0xffffffff;
    }
    uVar4 = uVar4 + 8;
    iVar5 = iVar5 + 0x10;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  if (bVar1) {
    *(int *)(param_2 + 100) = iVar6;
    iVar6 = iVar6 + 0x200;
  }
  else {
    *(undefined4 *)(param_2 + 100) = 0xffffffff;
  }
  *(int *)(param_2 + 0x68) = iVar6;
  return;
}



// ==== 80223634  zz_0223634_ ====

int zz_0223634_(int param_1,int param_2,void *param_3)

{
  int iVar1;
  char *__src;
  int *local_14 [2];
  
  if ((param_2 < 0) || (0x7e < param_2)) {
    iVar1 = -0x80;
  }
  else {
    iVar1 = zz_021e07c_(param_1,local_14);
    if (-1 < iVar1) {
      iVar1 = zz_021fcec_((int)local_14[0]);
      __src = (char *)(iVar1 + param_2 * 0x40);
      iVar1 = zz_0222318_((int)local_14[0],__src);
      if (-1 < iVar1) {
        gnt4_memcpy((void *)((int)param_3 + 0x28),__src,4);
        gnt4_memcpy((void *)((int)param_3 + 0x2c),__src + 4,2);
        *(uint *)((int)param_3 + 0x20) = (uint)*(ushort *)(__src + 0x38) * local_14[0][3];
        gnt4_memcpy(param_3,__src + 8,0x20);
        *(undefined4 *)((int)param_3 + 0x24) = *(undefined4 *)(__src + 0x28);
        *(char *)((int)param_3 + 0x2e) = __src[7];
        *(undefined4 *)((int)param_3 + 0x30) = *(undefined4 *)(__src + 0x2c);
        *(undefined2 *)((int)param_3 + 0x34) = *(undefined2 *)(__src + 0x30);
        *(undefined2 *)((int)param_3 + 0x36) = *(undefined2 *)(__src + 0x32);
        *(undefined4 *)((int)param_3 + 0x38) = *(undefined4 *)(__src + 0x3c);
        zz_022343c_((int)__src,(int)param_3);
      }
      iVar1 = zz_021e134_(local_14[0],iVar1);
    }
  }
  return iVar1;
}



// ==== 80223748  CARDSetStatusAsync ====

int CARDSetStatusAsync(int param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  undefined8 uVar4;
  int *local_18 [2];
  
  if ((((param_2 < 0) || (0x7e < param_2)) ||
      ((*(uint *)(param_3 + 0x30) != 0xffffffff && (0x1ff < *(uint *)(param_3 + 0x30))))) ||
     ((*(uint *)(param_3 + 0x38) != 0xffffffff && (0x1fc0 < (*(uint *)(param_3 + 0x38) & 0x1fff)))))
  {
    iVar2 = -0x80;
  }
  else {
    iVar2 = zz_021e07c_(param_1,local_18);
    if (-1 < iVar2) {
      iVar2 = zz_021fcec_((int)local_18[0]);
      pcVar3 = (char *)(iVar2 + param_2 * 0x40);
      iVar2 = zz_02221e4_((int)local_18[0],pcVar3);
      if (iVar2 < 0) {
        iVar2 = zz_021e134_(local_18[0],iVar2);
      }
      else {
        pcVar3[7] = *(char *)(param_3 + 0x2e);
        *(undefined4 *)(pcVar3 + 0x2c) = *(undefined4 *)(param_3 + 0x30);
        *(undefined2 *)(pcVar3 + 0x30) = *(undefined2 *)(param_3 + 0x34);
        *(undefined2 *)(pcVar3 + 0x32) = *(undefined2 *)(param_3 + 0x36);
        *(undefined4 *)(pcVar3 + 0x3c) = *(undefined4 *)(param_3 + 0x38);
        zz_022343c_((int)pcVar3,param_3);
        if (*(int *)(pcVar3 + 0x2c) == -1) {
          *(ushort *)(pcVar3 + 0x32) = *(ushort *)(pcVar3 + 0x32) & 0xfffc | 1;
        }
        uVar1 = DAT_800000f8 >> 2;
        uVar4 = gnt4_OSGetTime_bl();
        uVar4 = gnt4___div2i((uint)((ulonglong)uVar4 >> 0x20),(uint)uVar4,0,uVar1);
        *(int *)(pcVar3 + 0x28) = (int)uVar4;
        iVar2 = zz_021fe8c_(param_1,param_4);
        if (iVar2 < 0) {
          zz_021e134_(local_18[0],iVar2);
        }
      }
    }
  }
  return iVar2;
}



// ==== 802238bc  zz_02238bc_ ====

int zz_02238bc_(int param_1,int param_2,void *param_3)

{
  int iVar1;
  char *__src;
  int *local_14 [2];
  
  if ((param_2 < 0) || (0x7e < param_2)) {
    iVar1 = -0x80;
  }
  else {
    iVar1 = zz_021e07c_(param_1,local_14);
    if (-1 < iVar1) {
      iVar1 = zz_021fcec_((int)local_14[0]);
      __src = (char *)(iVar1 + param_2 * 0x40);
      iVar1 = zz_0222318_((int)local_14[0],__src);
      if (-1 < iVar1) {
        gnt4_memcpy(param_3,__src,0x40);
      }
      iVar1 = zz_021e134_(local_14[0],iVar1);
    }
  }
  return iVar1;
}



// ==== 80223960  zz_0223960_ ====

int zz_0223960_(int param_1,int param_2,void *param_3,undefined4 param_4)

{
  int iVar1;
  char *__s1;
  int iVar2;
  char *pcVar3;
  char *__s1_00;
  int *local_28 [3];
  
  if ((((param_2 < 0) || (0x7e < param_2)) || (*(char *)((int)param_3 + 8) == -1)) ||
     (*(char *)((int)param_3 + 8) == '\0')) {
    iVar1 = -0x80;
  }
  else {
    iVar1 = zz_021e07c_(param_1,local_28);
    if (-1 < iVar1) {
      __s1 = (char *)zz_021fcec_((int)local_28[0]);
      __s1_00 = __s1 + param_2 * 0x40;
      iVar1 = zz_02221e4_((int)local_28[0],__s1_00);
      if (iVar1 < 0) {
        iVar1 = zz_021e134_(local_28[0],iVar1);
      }
      else {
        pcVar3 = (char *)((int)param_3 + 8);
        iVar1 = ((int)param_3 + 0x28) - (int)pcVar3;
        if (pcVar3 < (char *)((int)param_3 + 0x28)) {
LAB_80223a10:
          if (*pcVar3 != '\0') goto LAB_80223a3c;
          while (pcVar3 = pcVar3 + 1, pcVar3 < (char *)((int)param_3 + 0x28)) {
            *pcVar3 = '\0';
          }
        }
LAB_80223a44:
        if ((*(byte *)((int)param_3 + 0x34) & 0x20) != 0) {
          gnt4_memset(param_3,0,4);
          gnt4_memset((void *)((int)param_3 + 4),0,2);
        }
        if ((*(byte *)((int)param_3 + 0x34) & 0x40) != 0) {
          gnt4_memset(param_3,0,4);
        }
        iVar1 = gnt4_memcmp(__s1_00 + 8,(void *)((int)param_3 + 8),0x20);
        if (((iVar1 != 0) || (iVar1 = gnt4_memcmp(__s1_00,param_3,4), iVar1 != 0)) ||
           (iVar1 = gnt4_memcmp(__s1_00 + 4,(void *)((int)param_3 + 4),2), iVar1 != 0)) {
          iVar1 = 0;
          do {
            if (((iVar1 != param_2) && (*__s1 != -1)) &&
               ((iVar2 = gnt4_memcmp(__s1,param_3,4), iVar2 == 0 &&
                ((iVar2 = gnt4_memcmp(__s1 + 4,(void *)((int)param_3 + 4),2), iVar2 == 0 &&
                 (iVar2 = gnt4_memcmp(__s1 + 8,(void *)((int)param_3 + 8),0x20), iVar2 == 0)))))) {
              iVar1 = zz_021e134_(local_28[0],-7);
              return iVar1;
            }
            iVar1 = iVar1 + 1;
            __s1 = __s1 + 0x40;
          } while (iVar1 < 0x7f);
          gnt4_memcpy(__s1_00 + 8,(void *)((int)param_3 + 8),0x20);
          gnt4_memcpy(__s1_00,param_3,4);
          gnt4_memcpy(__s1_00 + 4,(void *)((int)param_3 + 4),2);
        }
        *(undefined4 *)(__s1_00 + 0x28) = *(undefined4 *)((int)param_3 + 0x28);
        __s1_00[7] = *(char *)((int)param_3 + 7);
        *(undefined4 *)(__s1_00 + 0x2c) = *(undefined4 *)((int)param_3 + 0x2c);
        *(undefined2 *)(__s1_00 + 0x30) = *(undefined2 *)((int)param_3 + 0x30);
        *(undefined2 *)(__s1_00 + 0x32) = *(undefined2 *)((int)param_3 + 0x32);
        *(undefined4 *)(__s1_00 + 0x3c) = *(undefined4 *)((int)param_3 + 0x3c);
        __s1_00[0x34] = *(char *)((int)param_3 + 0x34);
        __s1_00[0x35] = *(char *)((int)param_3 + 0x35);
        iVar1 = zz_021fe8c_(param_1,param_4);
        if (iVar1 < 0) {
          zz_021e134_(local_28[0],iVar1);
        }
      }
    }
  }
  return iVar1;
LAB_80223a3c:
  pcVar3 = pcVar3 + 1;
  iVar1 = iVar1 + -1;
  if (iVar1 == 0) goto LAB_80223a44;
  goto LAB_80223a10;
}



// ==== 80223bfc  zz_0223bfc_ ====

int zz_0223bfc_(int param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int *local_10 [3];
  
  if ((param_1 < 0) || (1 < param_1)) {
    iVar5 = -0x80;
  }
  else {
    iVar5 = zz_021e07c_(param_1,local_10);
    if (-1 < iVar5) {
      puVar6 = (uint *)local_10[0][0x20];
      uVar1 = *puVar6;
      uVar2 = puVar6[2];
      uVar3 = puVar6[4];
      uVar4 = puVar6[6];
      param_2[1] = puVar6[1] ^ puVar6[3] ^ puVar6[5] ^ puVar6[7];
      *param_2 = uVar1 ^ uVar2 ^ uVar3 ^ uVar4;
      iVar5 = zz_021e134_(local_10[0],0);
    }
  }
  return iVar5;
}



// ==== 80223cc0  zz_0223cc0_ ====

void zz_0223cc0_(int param_1,int param_2,undefined1 *param_3)

{
  int iVar1;
  undefined1 auStack_4c [52];
  undefined1 local_18;
  
  iVar1 = zz_02238bc_(param_1,param_2,auStack_4c);
  if (iVar1 == 0) {
    *param_3 = local_18;
  }
  return;
}



// ==== 80223d00  zz_0223d00_ ====

int zz_0223d00_(int param_1,int param_2,byte param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 auStack_58 [52];
  byte local_24;
  
  if ((param_3 & ~DAT_80435d62) == 0) {
    iVar1 = zz_02238bc_(param_1,param_2,auStack_58);
    if (-1 < iVar1) {
      if ((((local_24 & 0x20) == 0) || ((param_3 & 0x20) != 0)) &&
         (((local_24 & 0x40) == 0 || ((param_3 & 0x40) != 0)))) {
        if (((((param_3 & 0x20) == 0) || ((param_3 & 0x40) == 0)) &&
            (((param_3 & 0x20) == 0 || ((local_24 & 0x40) == 0)))) &&
           (((param_3 & 0x40) == 0 || ((local_24 & 0x20) == 0)))) {
          local_24 = param_3;
          iVar1 = zz_0223960_(param_1,param_2,auStack_58,param_4);
        }
        else {
          iVar1 = -10;
        }
      }
      else {
        iVar1 = -10;
      }
    }
  }
  else {
    iVar1 = -10;
  }
  return iVar1;
}



// ==== 80223de4  gnt4-__GXDefaultTexRegionCallback-bl ====

int gnt4___GXDefaultTexRegionCallback_bl(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = gnt4_GXGetTexObjFmt_bl(param_1);
  uVar2 = gnt4_GXGetTexObjMipMap_bl(param_1);
  iVar3 = param_2 + (((int)param_2 >> 3) + (uint)((int)param_2 < 0 && (param_2 & 7) != 0)) * -8;
  if (iVar1 != 7) {
    if (iVar1 < 7) {
      if (5 < iVar1) {
        if ((uVar2 & 0xff) != 0) {
          return DAT_8043cb00 + iVar3 * 0x10 + 0x308;
        }
        return DAT_8043cb00 + iVar3 * 0x10 + 0x288;
      }
    }
    else if (iVar1 < 0xb) {
      return DAT_8043cb00 + iVar3 * 0x10 + 0x208;
    }
  }
  if ((uVar2 & 0xff) == 0) {
    iVar1 = iVar3 * 0x10 + 0x208;
  }
  else {
    iVar1 = iVar3 * 0x10 + 0x288;
  }
  return DAT_8043cb00 + iVar1;
}



// ==== 80223ee0  gnt4-__GXDefaultTlutRegionCallback-bl ====

int gnt4___GXDefaultTlutRegionCallback_bl(uint param_1)

{
  int iVar1;
  
  if (param_1 < 0x14) {
    iVar1 = DAT_8043cb00 + param_1 * 0x10 + 0x388;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}



// ==== 80223f04  gnt4-__GXShutdown-bl ====

undefined4 gnt4___GXShutdown_bl(int param_1)

{
  bool bVar1;
  int iVar2;
  short sVar4;
  uint uVar3;
  short *psVar5;
  int *piVar6;
  undefined8 uVar7;
  
  if (param_1 == 0) {
    if (DAT_80436800 == 0) {
      psVar5 = (short *)(DAT_804367ec + 0x4e);
      sVar4 = *psVar5;
      do {
        DAT_804367f0 = *(int *)psVar5;
        bVar1 = *psVar5 != sVar4;
        sVar4 = *psVar5;
      } while (bVar1);
      uVar7 = gnt4_OSGetTime_bl();
      DAT_804367f8 = (int)((ulonglong)uVar7 >> 0x20);
      DAT_804367fc = (int)uVar7;
      DAT_80436800 = 1;
      return 0;
    }
    uVar7 = gnt4_OSGetTime_bl();
    iVar2 = (int)((ulonglong)uVar7 >> 0x20);
    uVar3 = (uint)uVar7;
    piVar6 = (int *)(DAT_804367ec + 0x4e);
    sVar4 = *(short *)piVar6;
    do {
      bVar1 = *(short *)piVar6 != sVar4;
      sVar4 = *(short *)piVar6;
    } while (bVar1);
    if ((iVar2 - ((uint)(uVar3 < DAT_804367fc) + DAT_804367f8) ^ 0x80000000) <
        (uVar3 - DAT_804367fc < 10) + 0x80000000) {
      return 0;
    }
    if (*piVar6 != DAT_804367f0) {
      DAT_804367f0 = *piVar6;
      DAT_804367f8 = iVar2;
      DAT_804367fc = uVar3;
      return 0;
    }
  }
  else {
    gnt4_GXSetBreakPtCallback_bl(0);
    gnt4_GXSetDrawSyncCallback_bl(0);
    gnt4_GXSetDrawDoneCallback_bl(0);
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    DAT_cc008000 = 0;
    gnt4_PPCSync();
    *(undefined2 *)(DAT_804367e4 + 2) = 0;
    *(undefined2 *)(DAT_804367e4 + 4) = 3;
    *(undefined1 *)(DAT_8043cb00 + 0x5aa) = 1;
    gnt4___GXAbort_bl();
  }
  return 1;
}



// ==== 80224094  zz_0224094_ ====

undefined *
zz_0224094_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           uint param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint *puVar12;
  int iVar13;
  byte bVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  
  gnt4_OSRegisterVersion_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d68,0x803f0000
             ,param_11,param_12,param_13,param_14,param_15,param_16);
  iVar18 = DAT_8043cb00;
  *(undefined1 *)(DAT_8043cb00 + 0x5a8) = 0;
  *(undefined1 *)(iVar18 + 0x5a9) = 1;
  *(undefined1 *)(iVar18 + 0x5aa) = 1;
  *(undefined4 *)(iVar18 + 0x594) = 0;
  *(undefined4 *)(iVar18 + 0x598) = 0;
  gnt4_GXSetMisc_bl(1,0);
  DAT_804367e4 = &DAT_cc000000;
  DAT_804367e0 = &DAT_cc003000;
  DAT_804367e8 = &DAT_cc001000;
  DAT_804367ec = &DAT_cc004000;
  gnt4___GXFifoInit_bl();
  gnt4_GXInitFifoBase_bl((int *)&DAT_803f5320,param_9,param_10);
  gnt4_GXSetCPUFifo_bl((uint *)&DAT_803f5320);
  gnt4_GXSetGPFifo_bl((undefined4 *)&DAT_803f5320);
  if (DAT_80436804 == 0) {
    gnt4_OSRegisterResetFunction_bl(-0x7fc558d4);
    DAT_80436804 = 1;
  }
  gnt4___GXPEInit_bl();
  gnt4_PPCMfhid2();
  zz_01feab8_();
  gnt4_PPCMthid2();
  iVar18 = DAT_8043cb00;
  iVar13 = 0;
  uVar3 = 0;
  *(undefined4 *)(DAT_8043cb00 + 0x204) = 0;
  *(uint *)(iVar18 + 0x204) = *(uint *)(iVar18 + 0x204) & 0xffffff;
  iVar15 = 0xc0;
  *(undefined4 *)(iVar18 + 0x124) = 0xff;
  iVar10 = 0xc1;
  *(uint *)(iVar18 + 0x124) = *(uint *)(iVar18 + 0x124) & 0xffffff | 0xf000000;
  *(undefined4 *)(iVar18 + 0x7c) = 0;
  *(uint *)(iVar18 + 0x7c) = *(uint *)(iVar18 + 0x7c) & 0xffffff | 0x22000000;
  iVar18 = 8;
  do {
    iVar4 = DAT_8043cb00;
    uVar17 = uVar3 >> 1;
    iVar8 = iVar13 + 0x130;
    *(undefined4 *)(DAT_8043cb00 + iVar8) = 0;
    iVar7 = iVar13 + 0x170;
    *(undefined4 *)(iVar4 + iVar7) = 0;
    iVar6 = uVar17 * 4 + 0x100;
    *(undefined4 *)(iVar4 + iVar6) = 0;
    iVar5 = uVar17 * 4 + 0x1b0;
    *(undefined4 *)(iVar4 + iVar13 + 0x554) = 0xff;
    *(uint *)(iVar4 + iVar8) = iVar15 << 0x18 | *(uint *)(iVar4 + iVar8) & 0xffffff;
    uVar1 = uVar3 + 1 >> 1;
    iVar9 = iVar13 + 0x134;
    *(uint *)(iVar4 + iVar7) = iVar10 << 0x18 | *(uint *)(iVar4 + iVar7) & 0xffffff;
    iVar8 = iVar13 + 0x174;
    iVar7 = iVar13 + 0x558;
    *(uint *)(iVar4 + iVar5) = (uVar17 + 0xf6) * 0x1000000 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    iVar16 = iVar15 + 2;
    iVar11 = iVar10 + 2;
    iVar5 = uVar1 * 4 + 0x1b0;
    *(uint *)(iVar4 + iVar6) = (uVar17 + 0x28) * 0x1000000 | *(uint *)(iVar4 + iVar6) & 0xffffff;
    iVar6 = uVar1 * 4 + 0x100;
    *(undefined4 *)(iVar4 + iVar9) = 0;
    iVar13 = iVar13 + 8;
    *(undefined4 *)(iVar4 + iVar8) = 0;
    uVar3 = uVar3 + 2;
    *(undefined4 *)(iVar4 + iVar6) = 0;
    *(undefined4 *)(iVar4 + iVar7) = 0xff;
    iVar15 = iVar15 + 4;
    *(uint *)(iVar4 + iVar9) = iVar16 * 0x1000000 | *(uint *)(iVar4 + iVar9) & 0xffffff;
    iVar10 = iVar10 + 4;
    *(uint *)(iVar4 + iVar8) = iVar11 * 0x1000000 | *(uint *)(iVar4 + iVar8) & 0xffffff;
    *(uint *)(iVar4 + iVar5) = (uVar1 + 0xf6) * 0x1000000 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    *(uint *)(iVar4 + iVar6) = (uVar1 + 0x28) * 0x1000000 | *(uint *)(iVar4 + iVar6) & 0xffffff;
    iVar18 = iVar18 + -1;
  } while (iVar18 != 0);
  *(undefined4 *)(iVar4 + 0x120) = 0;
  iVar18 = 0;
  *(uint *)(iVar4 + 0x120) = *(uint *)(iVar4 + 0x120) & 0xffffff | 0x27000000;
  iVar10 = 0x30;
  iVar13 = 0x31;
  iVar15 = 2;
  do {
    iVar4 = DAT_8043cb00;
    iVar7 = iVar18 + 0xb8;
    iVar5 = iVar18 + 0xd8;
    *(undefined4 *)(DAT_8043cb00 + iVar7) = 0;
    *(undefined4 *)(iVar4 + iVar5) = 0;
    *(uint *)(iVar4 + iVar7) = iVar10 << 0x18 | *(uint *)(iVar4 + iVar7) & 0xffffff;
    iVar7 = iVar18 + 0xbc;
    *(uint *)(iVar4 + iVar5) = iVar13 << 0x18 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    iVar5 = iVar18 + 0xdc;
    *(undefined4 *)(iVar4 + iVar7) = 0;
    *(undefined4 *)(iVar4 + iVar5) = 0;
    *(uint *)(iVar4 + iVar7) = (iVar10 + 2) * 0x1000000 | *(uint *)(iVar4 + iVar7) & 0xffffff;
    iVar7 = iVar18 + 0xc0;
    *(uint *)(iVar4 + iVar5) = (iVar13 + 2) * 0x1000000 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    iVar5 = iVar18 + 0xe0;
    *(undefined4 *)(iVar4 + iVar7) = 0;
    *(undefined4 *)(iVar4 + iVar5) = 0;
    iVar6 = iVar10 + 6;
    *(uint *)(iVar4 + iVar7) = (iVar10 + 4) * 0x1000000 | *(uint *)(iVar4 + iVar7) & 0xffffff;
    iVar7 = iVar18 + 0xc4;
    iVar8 = iVar13 + 6;
    *(uint *)(iVar4 + iVar5) = (iVar13 + 4) * 0x1000000 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    iVar5 = iVar18 + 0xe4;
    iVar18 = iVar18 + 0x10;
    *(undefined4 *)(iVar4 + iVar7) = 0;
    *(undefined4 *)(iVar4 + iVar5) = 0;
    iVar10 = iVar10 + 8;
    *(uint *)(iVar4 + iVar7) = iVar6 * 0x1000000 | *(uint *)(iVar4 + iVar7) & 0xffffff;
    iVar13 = iVar13 + 8;
    *(uint *)(iVar4 + iVar5) = iVar8 * 0x1000000 | *(uint *)(iVar4 + iVar5) & 0xffffff;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  *(uint *)(iVar4 + 0xf8) = *(uint *)(iVar4 + 0xf8) & 0xffffff | 0x20000000;
  *(uint *)(iVar4 + 0xfc) = *(uint *)(iVar4 + 0xfc) & 0xffffff | 0x21000000;
  *(uint *)(iVar4 + 0x1d0) = *(uint *)(iVar4 + 0x1d0) & 0xffffff | 0x41000000;
  bVar14 = 0;
  *(uint *)(iVar4 + 0x1d4) = *(uint *)(iVar4 + 0x1d4) & 0xffffff | 0x42000000;
  *(uint *)(iVar4 + 0x1d8) = *(uint *)(iVar4 + 0x1d8) & 0xffffff | 0x40000000;
  *(uint *)(iVar4 + 0x1dc) = *(uint *)(iVar4 + 0x1dc) & 0xffffff | 0x43000000;
  *(uint *)(iVar4 + 0x1fc) = *(uint *)(iVar4 + 0x1fc) & 0xfffffe7f;
  *(float *)(iVar4 + 0x510) = FLOAT_8043cb04;
  *(float *)(iVar4 + 0x50c) = FLOAT_8043cb08;
  *(undefined4 *)(iVar4 + 0x5ac) = 0;
  *(undefined1 *)(iVar4 + 0x5ab) = 0;
  uVar3 = DAT_800000f8 / 500;
  gnt4___GXFlushTextureState_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar3 >> 0xb | 0x69000400;
  gnt4___GXFlushTextureState_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar3 / 0x1080 | 0x46000200;
  iVar18 = 0;
  iVar10 = 2;
  do {
    iVar13 = DAT_8043cb00;
    iVar15 = iVar18 + 0x3c;
    *(uint *)(DAT_8043cb00 + iVar18 + 0x1c) =
         *(uint *)(DAT_8043cb00 + iVar18 + 0x1c) & 0xbfffffff | 0x40000000;
    *(uint *)(iVar13 + iVar15) = *(uint *)(iVar13 + iVar15) & 0x7fffffff | 0x80000000;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = bVar14 | 0x80;
    iVar4 = iVar18 + 0x40;
    DAT_cc008000 = *(undefined4 *)(iVar13 + iVar15);
    *(uint *)(iVar13 + iVar18 + 0x20) = *(uint *)(iVar13 + iVar18 + 0x20) & 0xbfffffff | 0x40000000;
    *(uint *)(iVar13 + iVar4) = *(uint *)(iVar13 + iVar4) & 0x7fffffff | 0x80000000;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = bVar14 + 1 | 0x80;
    bVar2 = bVar14 + 3;
    iVar15 = iVar18 + 0x44;
    DAT_cc008000 = *(undefined4 *)(iVar13 + iVar4);
    *(uint *)(iVar13 + iVar18 + 0x24) = *(uint *)(iVar13 + iVar18 + 0x24) & 0xbfffffff | 0x40000000;
    iVar5 = iVar18 + 0x28;
    *(uint *)(iVar13 + iVar15) = *(uint *)(iVar13 + iVar15) & 0x7fffffff | 0x80000000;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = bVar14 + 2 | 0x80;
    bVar14 = bVar14 + 4;
    iVar4 = iVar18 + 0x48;
    iVar18 = iVar18 + 0x10;
    DAT_cc008000 = *(undefined4 *)(iVar13 + iVar15);
    *(uint *)(iVar13 + iVar5) = *(uint *)(iVar13 + iVar5) & 0xbfffffff | 0x40000000;
    *(uint *)(iVar13 + iVar4) = *(uint *)(iVar13 + iVar4) & 0x7fffffff | 0x80000000;
    DAT_cc008000._0_1_ = 8;
    DAT_cc008000._0_1_ = bVar2 | 0x80;
    DAT_cc008000 = *(undefined4 *)(iVar13 + iVar4);
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1000;
  DAT_cc008000 = 0x3f;
  uVar17 = 0;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1012;
  DAT_cc008000 = 1;
  uVar3 = 0x5800000f;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x5800000f;
  puVar12 = &DAT_803aa66c;
  iVar18 = 0;
  do {
    gnt4_GXInitTexCacheRegion_bl
              ((uint *)(DAT_8043cb00 + iVar18 + 0x208),0,*puVar12,0,puVar12[8],0,uVar3);
    gnt4_GXInitTexCacheRegion_bl
              ((uint *)(DAT_8043cb00 + iVar18 + 0x288),0,puVar12[0x10],0,puVar12[0x18],0,uVar3);
    gnt4_GXInitTexCacheRegion_bl
              ((uint *)(DAT_8043cb00 + iVar18 + 0x308),1,puVar12[0x20],0,puVar12[0x28],0,uVar3);
    puVar12 = puVar12 + 1;
    iVar18 = iVar18 + 0x10;
    uVar17 = uVar17 + 1;
  } while (uVar17 < 8);
  uVar3 = 0;
  iVar10 = 0xc0000;
  iVar18 = 0;
  do {
    gnt4_GXInitTlutRegion_bl((uint *)(DAT_8043cb00 + iVar18 + 0x388),iVar10,0x10);
    iVar10 = iVar10 + 0x2000;
    iVar18 = iVar18 + 0x10;
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x10);
  uVar3 = 0;
  iVar18 = 0xe0000;
  do {
    gnt4_GXInitTlutRegion_bl((uint *)(DAT_8043cb00 + (uVar3 + 0x10) * 0x10 + 0x388),iVar18,0x40);
    iVar18 = iVar18 + 0x8000;
    uVar3 = uVar3 + 1;
  } while (uVar3 < 4);
  *(undefined2 *)(DAT_804367e4 + 6) = 0;
  iVar18 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x5a4) = *(uint *)(DAT_8043cb00 + 0x5a4) & 0xffffff0f;
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = 0x20;
  DAT_cc008000 = *(undefined4 *)(iVar18 + 0x5a4);
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x1006;
  DAT_cc008000 = 0;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x23000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x24000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x67000000;
  gnt4___GXSetTmemConfig_bl(2);
  gnt4___GXInitGX_bl();
  return &DAT_803f5320;
}



// ==== 80224824  gnt4-__GXInitGX-bl ====

void gnt4___GXInitGX_bl(void)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint uVar5;
  double dVar6;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  undefined4 local_84;
  uint local_80;
  uint local_7c;
  undefined4 local_78;
  float local_74;
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
  uint auStack_44 [9];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  local_78 = DAT_8043cb0c;
  local_7c = DAT_8043cb10;
  local_80 = DAT_8043cb14;
  iVar2 = gnt4_VIGetTvFormat();
  if (iVar2 == 2) {
    puVar1 = (undefined *)0x803aaa30;
    goto LAB_802248d4;
  }
  if (iVar2 < 2) {
    if (iVar2 == 0) {
      puVar1 = &DAT_803aa9b8;
      goto LAB_802248d4;
    }
    if (-1 < iVar2) {
      puVar1 = (undefined *)0x803aaa6c;
      goto LAB_802248d4;
    }
  }
  else if (iVar2 == 5) {
    puVar1 = (undefined *)0x803aaaa8;
    goto LAB_802248d4;
  }
  puVar1 = &DAT_803aa9b8;
LAB_802248d4:
  local_84 = local_78;
  gnt4_GXSetCopyClear_bl((undefined1 *)&local_84,0xffffff);
  gnt4_GXSetTexCoordGen2_bl(0,1,4,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(1,1,5,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(2,1,6,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(3,1,7,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(4,1,8,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(5,1,9,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(6,1,10,0x3c,0,0x7d);
  gnt4_GXSetTexCoordGen2_bl(7,1,0xb,0x3c,0,0x7d);
  gnt4_GXSetNumTexGens_bl(1);
  gnt4_GXClearVtxDesc_bl();
  gnt4_GXInvalidateVtxCache_bl();
  uVar5 = 9;
  do {
    gnt4_GXSetArray(uVar5,DAT_8043cb00,0);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x19);
  uVar5 = 0;
  do {
    gnt4_GXSetVtxAttrFmtv_bl(uVar5,(int *)&DAT_803aa580);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 8);
  gnt4_GXSetLineWidth_bl(6,0);
  gnt4_GXSetPointSize_bl(6,0);
  gnt4_GXEnableTexOffsets_bl(0,0,0);
  gnt4_GXEnableTexOffsets_bl(1,0,0);
  gnt4_GXEnableTexOffsets_bl(2,0,0);
  gnt4_GXEnableTexOffsets_bl(3,0,0);
  gnt4_GXEnableTexOffsets_bl(4,0,0);
  gnt4_GXEnableTexOffsets_bl(5,0,0);
  gnt4_GXEnableTexOffsets_bl(6,0,0);
  gnt4_GXEnableTexOffsets_bl(7,0,0);
  local_74 = FLOAT_8043cb18;
  local_70 = FLOAT_8043cb08;
  local_6c = FLOAT_8043cb08;
  local_68 = FLOAT_8043cb08;
  local_64 = FLOAT_8043cb08;
  local_60 = FLOAT_8043cb18;
  local_5c = FLOAT_8043cb08;
  local_58 = FLOAT_8043cb08;
  local_54 = FLOAT_8043cb08;
  local_50 = FLOAT_8043cb08;
  local_4c = FLOAT_8043cb18;
  local_48 = FLOAT_8043cb08;
  gnt4_GXLoadPosMtxImm_bl(&local_74,0);
  gnt4_GXLoadNrmMtxImm_bl(&local_74,0);
  gnt4_GXSetCurrentMtx_bl(0);
  gnt4_GXLoadTexMtxImm_bl(&local_74,0x3c,0);
  gnt4_GXLoadTexMtxImm_bl(&local_74,0x7d,0);
  uStack_14 = (uint)*(ushort *)(puVar1 + 4);
  uStack_1c = (uint)*(ushort *)(puVar1 + 8);
  dVar6 = (double)FLOAT_8043cb08;
  local_18 = 0x43300000;
  local_20 = 0x43300000;
  gnt4_GXSetViewport_bl
            (dVar6,dVar6,(double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043cb20),
             (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043cb20),dVar6,
             (double)FLOAT_8043cb18);
  gnt4_GXSetProjectionv_bl((float *)&DAT_803aa650);
  gnt4_GXSetCoPlanar_bl(0);
  gnt4_GXSetCullMode_bl(2);
  gnt4_GXSetClipMode_bl(0);
  gnt4_GXSetScissor_bl(0,0,(uint)*(ushort *)(puVar1 + 4),(uint)*(ushort *)(puVar1 + 6));
  gnt4_GXSetScissorBoxOffset_bl(0,0);
  gnt4_GXSetNumChans_bl(0);
  uVar3 = 0;
  uVar4 = 1;
  gnt4_GXSetChanCtrl_bl(4,0,0,1,0,0,2);
  local_88 = local_7c;
  gnt4_GXSetChanAmbColor_bl(4,&local_88,uVar3,uVar4);
  local_8c = local_80;
  gnt4_GXSetChanMatColor_bl(4,&local_8c,uVar3,uVar4);
  uVar3 = 0;
  uVar4 = 1;
  gnt4_GXSetChanCtrl_bl(5,0,0,1,0,0,2);
  local_90 = local_7c;
  gnt4_GXSetChanAmbColor_bl(5,&local_90,uVar3,uVar4);
  local_94 = local_80;
  gnt4_GXSetChanMatColor_bl(5,&local_94,uVar3,uVar4);
  gnt4_GXInvalidateTexAll_bl();
  gnt4_GXSetTexRegionCallback_bl(gnt4___GXDefaultTexRegionCallback_bl);
  gnt4_GXSetTlutRegionCallback_bl(gnt4___GXDefaultTlutRegionCallback_bl);
  gnt4_GXInitTexObj_bl(auStack_44,0x803aa560,4,4,3,0,0,'\0');
  gnt4_GXLoadTexObj_bl(auStack_44,0);
  gnt4_GXLoadTexObj_bl(auStack_44,1);
  gnt4_GXLoadTexObj_bl(auStack_44,2);
  gnt4_GXLoadTexObj_bl(auStack_44,3);
  gnt4_GXLoadTexObj_bl(auStack_44,4);
  gnt4_GXLoadTexObj_bl(auStack_44,5);
  gnt4_GXLoadTexObj_bl(auStack_44,6);
  gnt4_GXLoadTexObj_bl(auStack_44,7);
  gnt4_GXSetTevOrder_bl(0,0,0,4);
  gnt4_GXSetTevOrder_bl(1,1,1,4);
  gnt4_GXSetTevOrder_bl(2,2,2,4);
  gnt4_GXSetTevOrder_bl(3,3,3,4);
  gnt4_GXSetTevOrder_bl(4,4,4,4);
  gnt4_GXSetTevOrder_bl(5,5,5,4);
  gnt4_GXSetTevOrder_bl(6,6,6,4);
  gnt4_GXSetTevOrder_bl(7,7,7,4);
  gnt4_GXSetTevOrder_bl(8,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(9,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(10,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(0xb,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(0xc,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(0xd,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(0xe,0xff,0xff,0xff);
  gnt4_GXSetTevOrder_bl(0xf,0xff,0xff,0xff);
  gnt4_GXSetNumTevStages_bl(1);
  gnt4_GXSetTevOp_bl(0,3);
  gnt4_GXSetAlphaCompare_bl(7,0,0,7,0);
  gnt4_GXSetZTexture_bl(0,0x11,0);
  uVar5 = 0;
  do {
    gnt4_GXSetTevKColorSel_bl(uVar5,6);
    gnt4_GXSetTevKAlphaSel_bl(uVar5,0);
    gnt4_GXSetTevSwapMode_bl(uVar5,0,0);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x10);
  gnt4_GXSetTevSwapModeTable_bl(0,0,1,2,3);
  gnt4_GXSetTevSwapModeTable_bl(1,0,0,0,3);
  gnt4_GXSetTevSwapModeTable_bl(2,1,1,1,3);
  gnt4_GXSetTevSwapModeTable_bl(3,2,2,2,3);
  uVar5 = 0;
  do {
    gnt4_GXSetTevDirect_bl(uVar5);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x10);
  gnt4_GXSetNumIndStages_bl(0);
  gnt4_GXSetIndTexCoordScale_bl(0,0,0);
  gnt4_GXSetIndTexCoordScale_bl(1,0,0);
  gnt4_GXSetIndTexCoordScale_bl(2,0,0);
  gnt4_GXSetIndTexCoordScale_bl(3,0,0);
  local_98 = local_7c;
  gnt4_GXSetFog_bl((double)FLOAT_8043cb08,(double)FLOAT_8043cb18,(double)FLOAT_8043cb1c,
                   (double)FLOAT_8043cb18,0,(uint3 *)&local_98);
  gnt4_GXSetFogRangeAdj_bl(0,0,(ushort *)0x0);
  gnt4_GXSetBlendMode_bl(0,4,5,0);
  gnt4_GXSetColorUpdate_bl(1);
  gnt4_GXSetAlphaUpdate_bl(1);
  gnt4_GXSetZMode_bl(1,3,1);
  gnt4_GXSetZCompLoc_bl(1);
  gnt4_GXSetDither_bl(1);
  gnt4_GXSetDstAlpha_bl(0,0);
  gnt4_GXSetPixelFmt_bl(0,0);
  gnt4_GXSetFieldMask_bl(1,1);
  gnt4_GXSetFieldMode_bl
            ((uint)(byte)puVar1[0x18],
             (uint)((uint)*(ushort *)(puVar1 + 0x10) == (uint)*(ushort *)(puVar1 + 8) << 1));
  gnt4_GXSetDispCopySrc_bl(0,0,(uint)*(ushort *)(puVar1 + 4),(uint)*(ushort *)(puVar1 + 6));
  gnt4_GXSetDispCopyDst_bl((uint)*(ushort *)(puVar1 + 4));
  uStack_1c = (uint)*(ushort *)(puVar1 + 8);
  uStack_14 = (uint)*(ushort *)(puVar1 + 6);
  local_20 = 0x43300000;
  local_18 = 0x43300000;
  gnt4_GXSetDispCopyYScale_bl
            ((double)((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043cb20) /
                     (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043cb20)));
  gnt4_GXSetCopyClamp_bl(3);
  gnt4_GXSetCopyFilter_bl(puVar1[0x19],puVar1 + 0x1a,'\x01',puVar1 + 0x32);
  gnt4_GXSetDispCopyGamma_bl(0);
  gnt4_GXSetDispCopyFrame2Field_bl(0);
  gnt4_GXClearBoundingBox_bl();
  gnt4_GXPokeColorUpdate_bl(1);
  gnt4_GXPokeAlphaUpdate_bl(1);
  gnt4_GXPokeDither_bl(0);
  gnt4_GXPokeBlendMode_bl(0,0,1,0xf);
  gnt4_GXPokeAlphaMode_bl(7,0);
  gnt4_GXPokeAlphaRead_bl(1);
  gnt4_GXPokeDstAlpha_bl(0,0);
  gnt4_GXPokeZMode_bl(1,7,1);
  gnt4_GXSetGPMetric_bl(0x23,0x16);
  gnt4_GXClearGPMetric_bl();
  return;
}



// ==== 8022515c  gnt4-GXCPInterruptHandler-bl ====

void gnt4_GXCPInterruptHandler_bl(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined1 auStack_2d0 [716];
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0xc) = (uint)*DAT_804367e4;
  if (((*(uint *)(iVar1 + 8) >> 3 & 1) != 0) && ((*(uint *)(iVar1 + 0xc) >> 1 & 1) != 0)) {
    gnt4_OSResumeThread_bl(DAT_80436810);
    DAT_80436818 = 0;
    gnt4___GXWriteFifoIntReset_bl(1,1);
    gnt4___GXWriteFifoIntEnable_bl(1,0);
  }
  if (((*(uint *)(DAT_8043cb00 + 8) >> 2 & 1) != 0) && ((*(uint *)(DAT_8043cb00 + 0xc) & 1) != 0)) {
    DAT_80436820 = DAT_80436820 + 1;
    gnt4___GXWriteFifoIntEnable_bl(0,1);
    gnt4___GXWriteFifoIntReset_bl(1,0);
    DAT_80436818 = 1;
    gnt4_OSSuspendThread_bl(DAT_80436810);
  }
  iVar1 = DAT_8043cb00;
  if (((*(uint *)(DAT_8043cb00 + 8) >> 5 & 1) != 0) &&
     ((*(uint *)(DAT_8043cb00 + 0xc) >> 4 & 1) != 0)) {
    *(uint *)(DAT_8043cb00 + 8) = *(uint *)(DAT_8043cb00 + 8) & 0xffffffdf;
    DAT_804367e4[1] = (ushort)*(undefined4 *)(iVar1 + 8);
    if (DAT_8043681c != (code *)0x0) {
      gnt4_OSClearContext_bl((int)auStack_2d0);
      gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
      (*DAT_8043681c)();
      gnt4_OSClearContext_bl((int)auStack_2d0);
      gnt4_OSSetCurrentContext_bl(param_2);
    }
  }
  return;
}



// ==== 80225290  gnt4-GXInitFifoBase-bl ====

void gnt4_GXInitFifoBase_bl(int *param_1,int param_2,uint param_3)

{
  *param_1 = param_2;
  param_1[1] = param_2 + (param_3 - 4);
  param_1[2] = param_3;
  param_1[7] = 0;
  gnt4_GXInitFifoLimits_bl((int)param_1,param_3 - 0x4000,param_3 >> 1 & 0x7fffffe0);
  gnt4_GXInitFifoPtrs_bl((int)param_1,param_2,param_2);
  return;
}



// ==== 802252fc  gnt4-GXInitFifoPtrs-bl ====

void gnt4_GXInitFifoPtrs_bl(int param_1,int param_2,int param_3)

{
  gnt4_OSDisableInterrupts_bl();
  *(int *)(param_1 + 0x14) = param_2;
  *(int *)(param_1 + 0x18) = param_3;
  *(int *)(param_1 + 0x1c) = param_3 - param_2;
  if (*(int *)(param_1 + 0x1c) < 0) {
    *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + *(int *)(param_1 + 8);
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8022536c  gnt4-GXInitFifoLimits-bl ====

void gnt4_GXInitFifoLimits_bl(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  return;
}



// ==== 80225378  gnt4-GXSetCPUFifo-bl ====

void gnt4_GXSetCPUFifo_bl(uint *param_1)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_80436808 = param_1;
  if (param_1 == DAT_8043680c) {
    *(uint *)(DAT_804367e0 + 0xc) = *param_1 & 0x3fffffff;
    *(uint *)(DAT_804367e0 + 0x10) = param_1[1] & 0x3fffffff;
    *(uint *)(DAT_804367e0 + 0x14) = param_1[6] & 0x3ffffe0;
    DAT_80436814 = '\x01';
    gnt4___GXWriteFifoIntReset_bl(1,1);
    gnt4___GXWriteFifoIntEnable_bl(1,0);
    gnt4___GXFifoLink_bl('\x01');
  }
  else {
    if (DAT_80436814 != '\0') {
      gnt4___GXFifoLink_bl('\0');
      DAT_80436814 = '\0';
    }
    gnt4___GXWriteFifoIntEnable_bl(0,0);
    *(uint *)(DAT_804367e0 + 0xc) = *param_1 & 0x3fffffff;
    *(uint *)(DAT_804367e0 + 0x10) = param_1[1] & 0x3fffffff;
    *(uint *)(DAT_804367e0 + 0x14) = param_1[6] & 0x3ffffe0;
  }
  gnt4_PPCSync();
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802254a0  gnt4-GXSetGPFifo-bl ====

void gnt4_GXSetGPFifo_bl(undefined4 *param_1)

{
  gnt4_OSDisableInterrupts_bl();
  gnt4___GXFifoReadDisable_bl();
  gnt4___GXWriteFifoIntEnable_bl(0,0);
  DAT_8043680c = param_1;
  *(short *)(DAT_804367e4 + 0x20) = (short)*param_1;
  *(short *)(DAT_804367e4 + 0x24) = (short)param_1[1];
  *(short *)(DAT_804367e4 + 0x30) = (short)param_1[7];
  *(short *)(DAT_804367e4 + 0x34) = (short)param_1[6];
  *(short *)(DAT_804367e4 + 0x38) = (short)param_1[5];
  *(short *)(DAT_804367e4 + 0x28) = (short)param_1[3];
  *(short *)(DAT_804367e4 + 0x2c) = (short)param_1[4];
  *(ushort *)(DAT_804367e4 + 0x22) = (ushort)((uint)*param_1 >> 0x10) & 0x3fff;
  *(ushort *)(DAT_804367e4 + 0x26) = (ushort)((uint)param_1[1] >> 0x10) & 0x3fff;
  *(short *)(DAT_804367e4 + 0x32) = (short)((uint)param_1[7] >> 0x10);
  *(ushort *)(DAT_804367e4 + 0x36) = (ushort)((uint)param_1[6] >> 0x10) & 0x3fff;
  *(ushort *)(DAT_804367e4 + 0x3a) = (ushort)((uint)param_1[5] >> 0x10) & 0x3fff;
  *(short *)(DAT_804367e4 + 0x2a) = (short)((uint)param_1[3] >> 0x10);
  *(short *)(DAT_804367e4 + 0x2e) = (short)((uint)param_1[4] >> 0x10);
  gnt4_PPCSync();
  if (DAT_80436808 == DAT_8043680c) {
    DAT_80436814 = 1;
    gnt4___GXWriteFifoIntEnable_bl(1,0);
    gnt4___GXFifoLink_bl('\x01');
  }
  else {
    DAT_80436814 = 0;
    gnt4___GXWriteFifoIntEnable_bl(0,0);
    gnt4___GXFifoLink_bl('\0');
  }
  gnt4___GXWriteFifoIntReset_bl(1,1);
  gnt4___GXFifoReadEnable_bl();
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80225618  gnt4-GXSetBreakPtCallback-bl ====

undefined4 gnt4_GXSetBreakPtCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8043681c;
  gnt4_OSDisableInterrupts_bl();
  DAT_8043681c = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 8022565c  gnt4-__GXFifoInit-bl ====

void gnt4___GXFifoInit_bl(void)

{
  gnt4___OSSetInterruptHandler_bl(0x11,gnt4_GXCPInterruptHandler_bl);
  gnt4___OSUnmaskInterrupts_bl(0x4000);
  DAT_80436810 = gnt4_OSGetCurrentThread_bl();
  DAT_80436818 = 0;
  DAT_80436808 = 0;
  DAT_8043680c = 0;
  return;
}



// ==== 802256a8  gnt4-__GXFifoReadEnable-bl ====

void gnt4___GXFifoReadEnable_bl(void)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 8) = *(uint *)(DAT_8043cb00 + 8) & 0xfffffffe | 1;
  *(short *)(DAT_804367e4 + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}



// ==== 802256cc  gnt4-__GXFifoReadDisable-bl ====

void gnt4___GXFifoReadDisable_bl(void)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 8) = *(uint *)(DAT_8043cb00 + 8) & 0xfffffffe;
  *(short *)(DAT_804367e4 + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}



// ==== 802256f0  gnt4-__GXFifoLink-bl ====

void gnt4___GXFifoLink_bl(char param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 8) =
       (uint)(param_1 != '\0') << 4 | *(uint *)(DAT_8043cb00 + 8) & 0xffffffef;
  *(short *)(DAT_804367e4 + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}



// ==== 80225724  gnt4-__GXWriteFifoIntEnable-bl ====

void gnt4___GXWriteFifoIntEnable_bl(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 8) = (param_1 & 1) << 2 | *(uint *)(DAT_8043cb00 + 8) & 0xfffffffb;
  *(uint *)(iVar1 + 8) = (param_2 & 1) << 3 | *(uint *)(iVar1 + 8) & 0xfffffff7;
  *(short *)(DAT_804367e4 + 2) = (short)*(undefined4 *)(iVar1 + 8);
  return;
}



// ==== 80225754  gnt4-__GXWriteFifoIntReset-bl ====

void gnt4___GXWriteFifoIntReset_bl(uint param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x10) = param_1 & 1 | *(uint *)(DAT_8043cb00 + 0x10) & 0xfffffffe;
  *(uint *)(iVar1 + 0x10) = (param_2 & 1) << 1 | *(uint *)(iVar1 + 0x10) & 0xfffffffd;
  *(short *)(DAT_804367e4 + 4) = (short)*(undefined4 *)(iVar1 + 0x10);
  return;
}



// ==== 80225784  zz_0225784_ ====

/* WARNING: Removing unreachable block (ram,0x802257f8) */

void zz_0225784_(void)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  int iVar7;
  uint auStack_9c [2];
  uint local_94 [5];
  uint local_80;
  uint local_7c;
  undefined4 local_78;
  
  puVar2 = (uint *)gnt4_GXGetGPFifo_bl();
  if (puVar2 != (uint *)0x0) {
    puVar3 = (uint *)zz_0225884_();
    uVar6 = *puVar2;
    iVar7 = 0x10;
    puVar4 = puVar2 + -2;
    puVar5 = auStack_9c;
    do {
      uVar1 = puVar4[3];
      puVar5[2] = puVar4[2];
      puVar5[3] = uVar1;
      iVar7 = iVar7 + -1;
      puVar4 = puVar4 + 2;
      puVar5 = puVar5 + 2;
    } while (iVar7 != 0);
    gnt4_OSDisableInterrupts_bl();
    local_78 = 0;
    local_80 = uVar6;
    local_7c = uVar6;
    gnt4_OSRestoreInterrupts_bl();
    gnt4_GXSetGPFifo_bl(local_94);
    if (puVar3 == puVar2) {
      gnt4_GXSetCPUFifo_bl(local_94);
    }
    gnt4_OSDisableInterrupts_bl();
    puVar2[5] = uVar6;
    puVar2[6] = uVar6;
    puVar2[7] = 0;
    if ((int)puVar2[7] < 0) {
      puVar2[7] = puVar2[7] + puVar2[2];
    }
    gnt4_OSRestoreInterrupts_bl();
    gnt4_GXSetGPFifo_bl(puVar2);
    if (puVar3 == puVar2) {
      gnt4_GXSetCPUFifo_bl(puVar3);
    }
  }
  return;
}



// ==== 80225884  zz_0225884_ ====

undefined4 zz_0225884_(void)

{
  return DAT_80436808;
}



// ==== 8022588c  gnt4-GXGetGPFifo-bl ====

undefined4 gnt4_GXGetGPFifo_bl(void)

{
  return DAT_8043680c;
}



// ==== 80225894  gnt4-GXSetVtxDesc-bl ====

void gnt4_GXSetVtxDesc_bl(undefined4 param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  switch(param_1) {
  case 0:
    *(uint *)(DAT_8043cb00 + 0x14) = param_2 & 1 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffe;
    break;
  case 1:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 1 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffd;
    break;
  case 2:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 2 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffb;
    break;
  case 3:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 3 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffff7;
    break;
  case 4:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 4 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffef;
    break;
  case 5:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 5 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffdf;
    break;
  case 6:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 6 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffbf;
    break;
  case 7:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 7 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffff7f;
    break;
  case 8:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 1) << 8 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffeff;
    break;
  case 9:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 3) << 9 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffff9ff;
    break;
  case 10:
    if (param_2 == 0) {
      *(undefined1 *)(DAT_8043cb00 + 0x4d4) = 0;
    }
    else {
      *(undefined1 *)(DAT_8043cb00 + 0x4d4) = 1;
      *(undefined1 *)(iVar1 + 0x4d5) = 0;
      *(uint *)(iVar1 + 0x4d0) = param_2;
    }
    break;
  case 0xb:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 3) << 0xd | *(uint *)(DAT_8043cb00 + 0x14) & 0xffff9fff;
    break;
  case 0xc:
    *(uint *)(DAT_8043cb00 + 0x14) =
         (param_2 & 3) << 0xf | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffe7fff;
    break;
  case 0xd:
    *(uint *)(DAT_8043cb00 + 0x18) = param_2 & 3 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffffc;
    break;
  case 0xe:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 2 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffff3;
    break;
  case 0xf:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 4 | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffffcf;
    break;
  case 0x10:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 6 | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffff3f;
    break;
  case 0x11:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 8 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffcff;
    break;
  case 0x12:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 10 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffff3ff;
    break;
  case 0x13:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 0xc | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffcfff;
    break;
  case 0x14:
    *(uint *)(DAT_8043cb00 + 0x18) =
         (param_2 & 3) << 0xe | *(uint *)(DAT_8043cb00 + 0x18) & 0xffff3fff;
    break;
  case 0x19:
    if (param_2 == 0) {
      *(undefined1 *)(DAT_8043cb00 + 0x4d5) = 0;
    }
    else {
      *(undefined1 *)(DAT_8043cb00 + 0x4d5) = 1;
      *(undefined1 *)(iVar1 + 0x4d4) = 0;
      *(uint *)(iVar1 + 0x4d0) = param_2;
    }
  }
  if ((*(char *)(DAT_8043cb00 + 0x4d4) == '\0') && (*(char *)(DAT_8043cb00 + 0x4d5) == '\0')) {
    *(uint *)(DAT_8043cb00 + 0x14) = *(uint *)(DAT_8043cb00 + 0x14) & 0xffffe7ff;
  }
  else {
    *(uint *)(DAT_8043cb00 + 0x14) =
         (*(uint *)(DAT_8043cb00 + 0x4d0) & 3) << 0xb | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffe7ff;
  }
  *(uint *)(DAT_8043cb00 + 0x5ac) = *(uint *)(DAT_8043cb00 + 0x5ac) | 8;
  return;
}



// ==== 80225b00  zz_0225b00_ ====

void zz_0225b00_(int *param_1)

{
  int iVar1;
  uint uVar2;
  
  for (; iVar1 = DAT_8043cb00, *param_1 != 0xff; param_1 = param_1 + 2) {
    uVar2 = param_1[1];
    switch(*param_1) {
    case 0:
      *(uint *)(DAT_8043cb00 + 0x14) = uVar2 & 1 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffe;
      break;
    case 1:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 1 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffd;
      break;
    case 2:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 2 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffffb;
      break;
    case 3:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 3 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffff7;
      break;
    case 4:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 4 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffef;
      break;
    case 5:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 5 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffdf;
      break;
    case 6:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 6 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffffbf;
      break;
    case 7:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 7 | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffff7f;
      break;
    case 8:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 1) << 8 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffffeff;
      break;
    case 9:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 3) << 9 | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffff9ff;
      break;
    case 10:
      if (uVar2 == 0) {
        *(undefined1 *)(DAT_8043cb00 + 0x4d4) = 0;
      }
      else {
        *(undefined1 *)(DAT_8043cb00 + 0x4d4) = 1;
        *(undefined1 *)(iVar1 + 0x4d5) = 0;
        *(uint *)(iVar1 + 0x4d0) = uVar2;
      }
      break;
    case 0xb:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 3) << 0xd | *(uint *)(DAT_8043cb00 + 0x14) & 0xffff9fff;
      break;
    case 0xc:
      *(uint *)(DAT_8043cb00 + 0x14) =
           (uVar2 & 3) << 0xf | *(uint *)(DAT_8043cb00 + 0x14) & 0xfffe7fff;
      break;
    case 0xd:
      *(uint *)(DAT_8043cb00 + 0x18) = uVar2 & 3 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffffc;
      break;
    case 0xe:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 2 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffff3;
      break;
    case 0xf:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 4 | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffffcf;
      break;
    case 0x10:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 6 | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffff3f;
      break;
    case 0x11:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 8 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffffcff;
      break;
    case 0x12:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 10 | *(uint *)(DAT_8043cb00 + 0x18) & 0xfffff3ff;
      break;
    case 0x13:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 0xc | *(uint *)(DAT_8043cb00 + 0x18) & 0xffffcfff;
      break;
    case 0x14:
      *(uint *)(DAT_8043cb00 + 0x18) =
           (uVar2 & 3) << 0xe | *(uint *)(DAT_8043cb00 + 0x18) & 0xffff3fff;
      break;
    case 0x19:
      if (uVar2 == 0) {
        *(undefined1 *)(DAT_8043cb00 + 0x4d5) = 0;
      }
      else {
        *(undefined1 *)(DAT_8043cb00 + 0x4d5) = 1;
        *(undefined1 *)(iVar1 + 0x4d4) = 0;
        *(uint *)(iVar1 + 0x4d0) = uVar2;
      }
    }
  }
  if ((*(char *)(DAT_8043cb00 + 0x4d4) == '\0') && (*(char *)(DAT_8043cb00 + 0x4d5) == '\0')) {
    *(uint *)(DAT_8043cb00 + 0x14) = *(uint *)(DAT_8043cb00 + 0x14) & 0xffffe7ff;
  }
  else {
    *(uint *)(DAT_8043cb00 + 0x14) =
         (*(uint *)(DAT_8043cb00 + 0x4d0) & 3) << 0xb | *(uint *)(DAT_8043cb00 + 0x14) & 0xffffe7ff;
  }
  *(uint *)(DAT_8043cb00 + 0x5ac) = *(uint *)(DAT_8043cb00 + 0x5ac) | 8;
  return;
}



// ==== 80225d88  gnt4-__GXSetVCD-bl ====

void gnt4___GXSetVCD_bl(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = 0x50;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x14);
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = 0x60;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x18);
  if (*(char *)(DAT_8043cb00 + 0x4d5) == '\0') {
    if (*(char *)(DAT_8043cb00 + 0x4d4) == '\0') {
      iVar3 = 0;
    }
    else {
      iVar3 = 1;
    }
  }
  else {
    iVar3 = 2;
  }
  iVar2 = countLeadingZeros(*(uint *)(DAT_8043cb00 + 0x14) >> 0xd & 0xf);
  DAT_cc008000._0_1_ = 0x10;
  iVar1 = countLeadingZeros(*(uint *)(DAT_8043cb00 + 0x18) & 0xffff);
  DAT_cc008000 = 0x1008;
  DAT_cc008000 = (0x21 - iVar1) * 8 & 0xfffffff0U | 0x21U - iVar2 >> 1 | iVar3 << 2;
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



// ==== 80225e44  gnt4-__GXCalculateVLim-bl ====

void gnt4___GXCalculateVLim_bl(void)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  
  if (*(short *)(DAT_8043cb00 + 4) == 0) {
    return;
  }
  uVar3 = *(uint *)(DAT_8043cb00 + 0x14);
  uVar1 = *(uint *)(DAT_8043cb00 + 0x18);
  if ((*(uint *)(DAT_8043cb00 + 0x1c) >> 9 & 1) == 1) {
    sVar2 = 3;
  }
  else {
    sVar2 = 1;
  }
  *(ushort *)(DAT_8043cb00 + 6) =
       ((ushort)uVar3 & 1) + ((ushort)(uVar3 >> 1) & 1) + ((ushort)(uVar3 >> 2) & 1) +
       ((ushort)(uVar3 >> 3) & 1) + ((ushort)(uVar3 >> 4) & 1) + ((ushort)(uVar3 >> 5) & 1) +
       ((ushort)(uVar3 >> 6) & 1) + ((ushort)(uVar3 >> 7) & 1) + ((ushort)(uVar3 >> 8) & 1) +
       (ushort)(byte)(&DAT_80435d78)[uVar3 >> 9 & 3] +
       (ushort)(byte)(&DAT_80435d78)[uVar3 >> 0xb & 3] * sVar2 +
       (ushort)(byte)(&DAT_80435d70)[uVar3 >> 0xd & 3] +
       (ushort)(byte)(&DAT_80435d70)[uVar3 >> 0xf & 3] + (ushort)(byte)(&DAT_80435d74)[uVar1 & 3] +
       (ushort)(byte)(&DAT_80435d74)[uVar1 >> 2 & 3] + (ushort)(byte)(&DAT_80435d74)[uVar1 >> 4 & 3]
       + (ushort)(byte)(&DAT_80435d74)[uVar1 >> 6 & 3] +
       (ushort)(byte)(&DAT_80435d74)[uVar1 >> 8 & 3] +
       (ushort)(byte)(&DAT_80435d74)[uVar1 >> 10 & 3] +
       (ushort)(byte)(&DAT_80435d74)[uVar1 >> 0xc & 3] +
       (ushort)(byte)(&DAT_80435d74)[uVar1 >> 0xe & 3];
  return;
}



// ==== 80225f68  zz_0225f68_ ====

void zz_0225f68_(undefined4 param_1,uint *param_2)

{
  uint uVar1;
  
  switch(param_1) {
  case 0:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) & 1;
    break;
  case 1:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 1 & 1;
    break;
  case 2:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 2 & 1;
    break;
  case 3:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 3 & 1;
    break;
  case 4:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 4 & 1;
    break;
  case 5:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 5 & 1;
    break;
  case 6:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 6 & 1;
    break;
  case 7:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 7 & 1;
    break;
  case 8:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 8 & 1;
    break;
  case 9:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 9 & 3;
    break;
  case 10:
    if (*(char *)(DAT_8043cb00 + 0x4d4) == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 0xb & 3;
    }
    break;
  case 0xb:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 0xd & 3;
    break;
  case 0xc:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 0xf & 3;
    break;
  case 0xd:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) & 3;
    break;
  case 0xe:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 2 & 3;
    break;
  case 0xf:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 4 & 3;
    break;
  case 0x10:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 6 & 3;
    break;
  case 0x11:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 8 & 3;
    break;
  case 0x12:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 10 & 3;
    break;
  case 0x13:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 0xc & 3;
    break;
  case 0x14:
    uVar1 = *(uint *)(DAT_8043cb00 + 0x18) >> 0xe & 3;
    break;
  default:
    uVar1 = 0;
    break;
  case 0x19:
    if (*(char *)(DAT_8043cb00 + 0x4d5) == '\0') {
      uVar1 = 0;
    }
    else {
      uVar1 = *(uint *)(DAT_8043cb00 + 0x14) >> 0xb & 3;
    }
  }
  *param_2 = uVar1;
  return;
}



// ==== 8022611c  zz_022611c_ ====

void zz_022611c_(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  do {
    iVar2 = iVar3;
    *(int *)(param_1 + iVar4) = iVar2;
    zz_0225f68_(iVar2,(uint *)((int *)(param_1 + iVar4) + 1));
    iVar3 = iVar2 + 1;
    iVar4 = iVar4 + 8;
  } while (iVar3 < 0x15);
  puVar1 = (undefined4 *)(param_1 + iVar3 * 8);
  *puVar1 = 0x19;
  zz_0225f68_(0x19,puVar1 + 1);
  *(undefined4 *)(param_1 + (iVar2 + 2) * 8) = 0xff;
  return;
}



// ==== 802261ac  gnt4-GXClearVtxDesc-bl ====

void gnt4_GXClearVtxDesc_bl(void)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(undefined4 *)(DAT_8043cb00 + 0x14) = 0;
  *(uint *)(iVar1 + 0x14) = *(uint *)(iVar1 + 0x14) & 0xfffff9ff | 0x200;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  *(undefined1 *)(iVar1 + 0x4d4) = 0;
  *(undefined1 *)(iVar1 + 0x4d5) = 0;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 8;
  return;
}



// ==== 802261e4  gnt4-GXSetVtxAttrFmt-bl ====

void gnt4_GXSetVtxAttrFmt_bl(uint param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5)

{
  uint *puVar1;
  int iVar2;
  uint *puVar3;
  uint *puVar4;
  
  iVar2 = DAT_8043cb00 + param_1 * 4;
  puVar1 = (uint *)(iVar2 + 0x1c);
  puVar3 = (uint *)(iVar2 + 0x3c);
  puVar4 = (uint *)(iVar2 + 0x5c);
  switch(param_2) {
  case 9:
    *puVar1 = param_3 & 1 | *puVar1 & 0xfffffffe;
    *puVar1 = (param_4 & 7) << 1 | *puVar1 & 0xfffffff1;
    *puVar1 = (param_5 & 0x1f) << 4 | *puVar1 & 0xfffffe0f;
    break;
  case 10:
  case 0x19:
    *puVar1 = (param_4 & 7) << 10 | *puVar1 & 0xffffe3ff;
    if (param_3 == 2) {
      *puVar1 = *puVar1 & 0xfffffdff | 0x200;
      *puVar1 = *puVar1 & 0x7fffffff | 0x80000000;
    }
    else {
      *puVar1 = (param_3 & 1) << 9 | *puVar1 & 0xfffffdff;
      *puVar1 = *puVar1 & 0x7fffffff;
    }
    break;
  case 0xb:
    *puVar1 = (param_3 & 1) << 0xd | *puVar1 & 0xffffdfff;
    *puVar1 = (param_4 & 7) << 0xe | *puVar1 & 0xfffe3fff;
    break;
  case 0xc:
    *puVar1 = (param_3 & 1) << 0x11 | *puVar1 & 0xfffdffff;
    *puVar1 = (param_4 & 7) << 0x12 | *puVar1 & 0xffe3ffff;
    break;
  case 0xd:
    *puVar1 = (param_3 & 1) << 0x15 | *puVar1 & 0xffdfffff;
    *puVar1 = (param_4 & 7) << 0x16 | *puVar1 & 0xfe3fffff;
    *puVar1 = (param_5 & 0x1f) << 0x19 | *puVar1 & 0xc1ffffff;
    break;
  case 0xe:
    *puVar3 = param_3 & 1 | *puVar3 & 0xfffffffe;
    *puVar3 = (param_4 & 7) << 1 | *puVar3 & 0xfffffff1;
    *puVar3 = (param_5 & 0x1f) << 4 | *puVar3 & 0xfffffe0f;
    break;
  case 0xf:
    *puVar3 = (param_3 & 1) << 9 | *puVar3 & 0xfffffdff;
    *puVar3 = (param_4 & 7) << 10 | *puVar3 & 0xffffe3ff;
    *puVar3 = (param_5 & 0x1f) << 0xd | *puVar3 & 0xfffc1fff;
    break;
  case 0x10:
    *puVar3 = (param_3 & 1) << 0x12 | *puVar3 & 0xfffbffff;
    *puVar3 = (param_4 & 7) << 0x13 | *puVar3 & 0xffc7ffff;
    *puVar3 = (param_5 & 0x1f) << 0x16 | *puVar3 & 0xf83fffff;
    break;
  case 0x11:
    *puVar3 = (param_3 & 1) << 0x1b | *puVar3 & 0xf7ffffff;
    *puVar3 = (param_4 & 7) << 0x1c | *puVar3 & 0x8fffffff;
    *puVar4 = param_5 & 0x1f | *puVar4 & 0xffffffe0;
    break;
  case 0x12:
    *puVar4 = (param_3 & 1) << 5 | *puVar4 & 0xffffffdf;
    *puVar4 = (param_4 & 7) << 6 | *puVar4 & 0xfffffe3f;
    *puVar4 = (param_5 & 0x1f) << 9 | *puVar4 & 0xffffc1ff;
    break;
  case 0x13:
    *puVar4 = (param_3 & 1) << 0xe | *puVar4 & 0xffffbfff;
    *puVar4 = (param_4 & 7) << 0xf | *puVar4 & 0xfffc7fff;
    *puVar4 = (param_5 & 0x1f) << 0x12 | *puVar4 & 0xff83ffff;
    break;
  case 0x14:
    *puVar4 = (param_3 & 1) << 0x17 | *puVar4 & 0xff7fffff;
    *puVar4 = (param_4 & 7) << 0x18 | *puVar4 & 0xf8ffffff;
    *puVar4 = param_5 << 0x1b | *puVar4 & 0x7ffffff;
  }
  iVar2 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x5ac) = *(uint *)(DAT_8043cb00 + 0x5ac) | 0x10;
  *(byte *)(iVar2 + 0x5ab) = *(byte *)(iVar2 + 0x5ab) | (byte)(1 << (param_1 & 0xff));
  return;
}



// ==== 80226440  gnt4-GXSetVtxAttrFmtv-bl ====

void gnt4_GXSetVtxAttrFmtv_bl(uint param_1,int *param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  uint uVar8;
  
  iVar3 = DAT_8043cb00 + param_1 * 4;
  puVar5 = (uint *)(iVar3 + 0x1c);
  puVar6 = (uint *)(iVar3 + 0x3c);
  puVar7 = (uint *)(iVar3 + 0x5c);
  for (; iVar3 = DAT_8043cb00, *param_2 != 0xff; param_2 = param_2 + 4) {
    bVar1 = *(byte *)(param_2 + 3);
    uVar4 = (uint)bVar1;
    uVar2 = param_2[2];
    uVar8 = param_2[1];
    switch(*param_2) {
    case 9:
      *puVar5 = uVar8 & 1 | *puVar5 & 0xfffffffe;
      *puVar5 = (uVar2 & 7) << 1 | *puVar5 & 0xfffffff1;
      *puVar5 = (uVar4 & 0x1f) << 4 | *puVar5 & 0xfffffe0f;
      break;
    case 10:
    case 0x19:
      *puVar5 = (uVar2 & 7) << 10 | *puVar5 & 0xffffe3ff;
      if (uVar8 == 2) {
        *puVar5 = *puVar5 & 0xfffffdff | 0x200;
        *puVar5 = *puVar5 & 0x7fffffff | 0x80000000;
      }
      else {
        *puVar5 = (uVar8 & 1) << 9 | *puVar5 & 0xfffffdff;
        *puVar5 = *puVar5 & 0x7fffffff;
      }
      break;
    case 0xb:
      *puVar5 = (uVar8 & 1) << 0xd | *puVar5 & 0xffffdfff;
      *puVar5 = (uVar2 & 7) << 0xe | *puVar5 & 0xfffe3fff;
      break;
    case 0xc:
      *puVar5 = (uVar8 & 1) << 0x11 | *puVar5 & 0xfffdffff;
      *puVar5 = (uVar2 & 7) << 0x12 | *puVar5 & 0xffe3ffff;
      break;
    case 0xd:
      *puVar5 = (uVar8 & 1) << 0x15 | *puVar5 & 0xffdfffff;
      *puVar5 = (uVar2 & 7) << 0x16 | *puVar5 & 0xfe3fffff;
      *puVar5 = (uVar4 & 0x1f) << 0x19 | *puVar5 & 0xc1ffffff;
      break;
    case 0xe:
      *puVar6 = uVar8 & 1 | *puVar6 & 0xfffffffe;
      *puVar6 = (uVar2 & 7) << 1 | *puVar6 & 0xfffffff1;
      *puVar6 = (uVar4 & 0x1f) << 4 | *puVar6 & 0xfffffe0f;
      break;
    case 0xf:
      *puVar6 = (uVar8 & 1) << 9 | *puVar6 & 0xfffffdff;
      *puVar6 = (uVar2 & 7) << 10 | *puVar6 & 0xffffe3ff;
      *puVar6 = (uVar4 & 0x1f) << 0xd | *puVar6 & 0xfffc1fff;
      break;
    case 0x10:
      *puVar6 = (uVar8 & 1) << 0x12 | *puVar6 & 0xfffbffff;
      *puVar6 = (uVar2 & 7) << 0x13 | *puVar6 & 0xffc7ffff;
      *puVar6 = (uVar4 & 0x1f) << 0x16 | *puVar6 & 0xf83fffff;
      break;
    case 0x11:
      *puVar6 = (uVar8 & 1) << 0x1b | *puVar6 & 0xf7ffffff;
      *puVar6 = (uVar2 & 7) << 0x1c | *puVar6 & 0x8fffffff;
      *puVar7 = bVar1 & 0x1f | *puVar7 & 0xffffffe0;
      break;
    case 0x12:
      *puVar7 = (uVar8 & 1) << 5 | *puVar7 & 0xffffffdf;
      *puVar7 = (uVar2 & 7) << 6 | *puVar7 & 0xfffffe3f;
      *puVar7 = (uVar4 & 0x1f) << 9 | *puVar7 & 0xffffc1ff;
      break;
    case 0x13:
      *puVar7 = (uVar8 & 1) << 0xe | *puVar7 & 0xffffbfff;
      *puVar7 = (uVar2 & 7) << 0xf | *puVar7 & 0xfffc7fff;
      *puVar7 = (uVar4 & 0x1f) << 0x12 | *puVar7 & 0xff83ffff;
      break;
    case 0x14:
      *puVar7 = (uVar8 & 1) << 0x17 | *puVar7 & 0xff7fffff;
      *puVar7 = (uVar2 & 7) << 0x18 | *puVar7 & 0xf8ffffff;
      *puVar7 = uVar4 << 0x1b | *puVar7 & 0x7ffffff;
    }
  }
  *(uint *)(DAT_8043cb00 + 0x5ac) = *(uint *)(DAT_8043cb00 + 0x5ac) | 0x10;
  *(byte *)(iVar3 + 0x5ab) = *(byte *)(iVar3 + 0x5ab) | (byte)(1 << (param_1 & 0xff));
  return;
}



// ==== 802266c0  gnt4-__GXSetVAT ====

void gnt4___GXSetVAT(void)

{
  int iVar1;
  byte bVar2;
  
  bVar2 = 0;
  iVar1 = 0;
  while( true ) {
    if (7 < bVar2) break;
    if (((uint)*(byte *)(DAT_8043cb00 + 0x5ab) & 1 << (uint)bVar2) != 0) {
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x70;
      DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + iVar1 + 0x1c);
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x80;
      DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + iVar1 + 0x3c);
      DAT_cc008000._0_1_ = 8;
      DAT_cc008000._0_1_ = bVar2 | 0x90;
      DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + iVar1 + 0x5c);
    }
    iVar1 = iVar1 + 4;
    bVar2 = bVar2 + 1;
  }
  *(undefined1 *)(DAT_8043cb00 + 0x5ab) = 0;
  return;
}



// ==== 8022675c  zz_022675c_ ====

void zz_022675c_(int param_1,undefined4 param_2,uint *param_3,uint *param_4,byte *param_5)

{
  uint uVar1;
  byte bVar2;
  uint *puVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar6;
  
  iVar4 = DAT_8043cb00 + param_1 * 4;
  puVar3 = (uint *)(iVar4 + 0x1c);
  puVar5 = (uint *)(iVar4 + 0x3c);
  puVar6 = (uint *)(iVar4 + 0x5c);
  switch(param_2) {
  case 9:
    *param_3 = *puVar3 & 1;
    *param_4 = *puVar3 >> 1 & 7;
    *param_5 = (byte)(*puVar3 >> 4) & 0x1f;
    return;
  case 10:
  case 0x19:
    break;
  case 0xb:
    *param_3 = *puVar3 >> 0xd & 1;
    *param_4 = *puVar3 >> 0xe & 7;
    *param_5 = 0;
    return;
  case 0xc:
    *param_3 = *puVar3 >> 0x11 & 1;
    *param_4 = *puVar3 >> 0x12 & 7;
    *param_5 = 0;
    return;
  case 0xd:
    *param_3 = *puVar3 >> 0x15 & 1;
    *param_4 = *puVar3 >> 0x16 & 7;
    *param_5 = (byte)(*puVar3 >> 0x19) & 0x1f;
    return;
  case 0xe:
    *param_3 = *puVar5 & 1;
    *param_4 = *puVar5 >> 1 & 7;
    *param_5 = (byte)(*puVar5 >> 4) & 0x1f;
    return;
  case 0xf:
    *param_3 = *puVar5 >> 9 & 1;
    *param_4 = *puVar5 >> 10 & 7;
    *param_5 = (byte)(*puVar5 >> 0xd) & 0x1f;
    return;
  case 0x10:
    *param_3 = *puVar5 >> 0x12 & 1;
    *param_4 = *puVar5 >> 0x13 & 7;
    *param_5 = (byte)(*puVar5 >> 0x16) & 0x1f;
    return;
  case 0x11:
    *param_3 = *puVar5 >> 0x1b & 1;
    *param_4 = *puVar5 >> 0x1c & 7;
    *param_5 = (byte)*puVar6 & 0x1f;
    return;
  case 0x12:
    *param_3 = *puVar6 >> 5 & 1;
    *param_4 = *puVar6 >> 6 & 7;
    *param_5 = (byte)(*puVar6 >> 9) & 0x1f;
    return;
  case 0x13:
    *param_3 = *puVar6 >> 0xe & 1;
    *param_4 = *puVar6 >> 0xf & 7;
    *param_5 = (byte)(*puVar6 >> 0x12) & 0x1f;
    return;
  case 0x14:
    *param_3 = *puVar6 >> 0x17 & 1;
    *param_4 = *puVar6 >> 0x18 & 7;
    *param_5 = (byte)(*puVar6 >> 0x1b);
    return;
  default:
    *param_3 = 1;
    *param_4 = 0;
    *param_5 = 0;
    return;
  }
  *param_3 = *puVar3 >> 9 & 1;
  if ((*param_3 == 1) && ((int)*puVar3 < 0)) {
    *param_3 = 2;
  }
  *param_4 = *puVar3 >> 10 & 7;
  uVar1 = *param_4;
  if (uVar1 != 2) {
    if ((int)uVar1 < 2) {
      if (0 < (int)uVar1) {
        bVar2 = 6;
        goto LAB_80226834;
      }
    }
    else if ((int)uVar1 < 4) {
      bVar2 = 0xe;
      goto LAB_80226834;
    }
  }
  bVar2 = 0;
LAB_80226834:
  *param_5 = bVar2;
  return;
}



// ==== 802269dc  zz_02269dc_ ====

void zz_02269dc_(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = 9;
  do {
    *param_2 = iVar1;
    zz_022675c_(param_1,iVar1,(uint *)(param_2 + 1),(uint *)(param_2 + 2),(byte *)(param_2 + 3));
    iVar1 = iVar1 + 1;
    param_2 = param_2 + 4;
  } while (iVar1 < 0x15);
  *param_2 = 0xff;
  return;
}



// ==== 80226a50  gnt4-GXSetArray ====

void gnt4_GXSetArray(int param_1,uint param_2,uint param_3)

{
  byte bVar1;
  int iVar2;
  
  if (param_1 == 0x19) {
    param_1 = 10;
  }
  bVar1 = (char)param_1 - 9;
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = bVar1 | 0xa0;
  iVar2 = param_1 + -0x15;
  DAT_cc008000 = param_2 & 0x3fffffff;
  if ((-1 < iVar2) && (iVar2 < 4)) {
    *(uint *)(DAT_8043cb00 + iVar2 * 4 + 0x88) = param_2 & 0x3fffffff;
  }
  DAT_cc008000._0_1_ = 8;
  DAT_cc008000._0_1_ = bVar1 | 0xb0;
  iVar2 = param_1 + -0x15;
  DAT_cc008000 = param_3 & 0xff;
  if (iVar2 < 0) {
    return;
  }
  if (3 < iVar2) {
    return;
  }
  *(uint *)(DAT_8043cb00 + iVar2 * 4 + 0x98) = param_3 & 0xff;
  return;
}



// ==== 80226adc  gnt4-GXInvalidateVtxCache-bl ====

void gnt4_GXInvalidateVtxCache_bl(void)

{
  DAT_cc008000._0_1_ = 0x48;
  return;
}



// ==== 80226aec  gnt4-GXSetTexCoordGen2-bl ====

void gnt4_GXSetTexCoordGen2_bl
               (int param_1,int param_2,int param_3,uint param_4,uint param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = 0;
  iVar3 = 0;
  iVar2 = 5;
  switch(param_3) {
  case 0:
    iVar2 = 0;
    iVar3 = 1;
    break;
  case 1:
    iVar2 = 1;
    iVar3 = 1;
    break;
  case 2:
    iVar2 = 3;
    iVar3 = 1;
    break;
  case 3:
    iVar2 = 4;
    iVar3 = 1;
    break;
  case 4:
    iVar2 = 5;
    break;
  case 5:
    iVar2 = 6;
    break;
  case 6:
    iVar2 = 7;
    break;
  case 7:
    iVar2 = 8;
    break;
  case 8:
    iVar2 = 9;
    break;
  case 9:
    iVar2 = 10;
    break;
  case 10:
    iVar2 = 0xb;
    break;
  case 0xb:
    iVar2 = 0xc;
    break;
  case 0x13:
    iVar2 = 2;
    break;
  case 0x14:
    iVar2 = 2;
  }
  if (param_2 == 1) {
    uVar1 = iVar2 << 7 | iVar3 << 2;
  }
  else if (param_2 < 1) {
    if (-1 < param_2) {
      uVar1 = iVar2 << 7 | iVar3 << 2 | 2U;
    }
  }
  else if (param_2 == 10) {
    if (param_3 == 0x13) {
      uVar1 = 0x20;
    }
    else {
      uVar1 = 0x30;
    }
    uVar1 = uVar1 | iVar3 << 2 | 0x100;
  }
  else if (param_2 < 10) {
    uVar1 = (param_2 + -2) * 0x8000 & 0x38000U |
            (param_3 + -0xc) * 0x1000 & 0x7000U | iVar2 << 7 | iVar3 << 2 | 0x10U;
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_1 + 0x1040;
  DAT_cc008000 = uVar1;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_1 + 0x1050;
  DAT_cc008000 = (param_5 & 1) << 8 | param_6 - 0x40U & 0x3f;
  switch(param_1) {
  case 0:
    *(uint *)(DAT_8043cb00 + 0x80) =
         (param_4 & 0x3f) << 6 | *(uint *)(DAT_8043cb00 + 0x80) & 0xfffff03f;
    break;
  case 1:
    *(uint *)(DAT_8043cb00 + 0x80) =
         (param_4 & 0x3f) << 0xc | *(uint *)(DAT_8043cb00 + 0x80) & 0xfffc0fff;
    break;
  case 2:
    *(uint *)(DAT_8043cb00 + 0x80) =
         (param_4 & 0x3f) << 0x12 | *(uint *)(DAT_8043cb00 + 0x80) & 0xff03ffff;
    break;
  case 3:
    *(uint *)(DAT_8043cb00 + 0x80) =
         (param_4 & 0x3f) << 0x18 | *(uint *)(DAT_8043cb00 + 0x80) & 0xc0ffffff;
    break;
  case 4:
    *(uint *)(DAT_8043cb00 + 0x84) = param_4 & 0x3f | *(uint *)(DAT_8043cb00 + 0x84) & 0xffffffc0;
    break;
  case 5:
    *(uint *)(DAT_8043cb00 + 0x84) =
         (param_4 & 0x3f) << 6 | *(uint *)(DAT_8043cb00 + 0x84) & 0xfffff03f;
    break;
  case 6:
    *(uint *)(DAT_8043cb00 + 0x84) =
         (param_4 & 0x3f) << 0xc | *(uint *)(DAT_8043cb00 + 0x84) & 0xfffc0fff;
    break;
  default:
    *(uint *)(DAT_8043cb00 + 0x84) =
         (param_4 & 0x3f) << 0x12 | *(uint *)(DAT_8043cb00 + 0x84) & 0xff03ffff;
  }
  gnt4___GXSetMatrixIndex_bl(param_1 + 1);
  return;
}



// ==== 80226d6c  gnt4-GXSetNumTexGens-bl ====

void gnt4_GXSetNumTexGens_bl(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_8043cb00;
  *(uint *)(DAT_8043cb00 + 0x204) = param_1 & 0xf | *(uint *)(DAT_8043cb00 + 0x204) & 0xfffffff0;
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x103f;
  DAT_cc008000 = param_1 & 0xff;
  *(uint *)(iVar1 + 0x5ac) = *(uint *)(iVar1 + 0x5ac) | 4;
  return;
}



// ==== 80226da8  gnt4-GXSetMisc-bl ====

void gnt4_GXSetMisc_bl(int param_1,int param_2)

{
  undefined2 *puVar1;
  uint uVar2;
  
  puVar1 = DAT_8043cb00;
  if (param_1 == 2) {
    *(char *)((int)DAT_8043cb00 + 0x5a9) = '\x01' - (param_2 == 0);
    return;
  }
  if (1 < param_1) {
    if (3 < param_1) {
      return;
    }
    *(char *)(DAT_8043cb00 + 0x2d5) = '\x01' - (param_2 == 0);
    return;
  }
  if (param_1 == 0) {
    return;
  }
  if (param_1 < 0) {
    return;
  }
  DAT_8043cb00[2] = (short)param_2;
  uVar2 = countLeadingZeros((uint)(ushort)puVar1[2]);
  *puVar1 = (short)(uVar2 >> 5);
  puVar1[1] = 1;
  if (puVar1[2] == 0) {
    return;
  }
  *(uint *)(puVar1 + 0x2d6) = *(uint *)(puVar1 + 0x2d6) | 8;
  return;
}



// ==== 80226e3c  gnt4-GXFlush ====

void gnt4_GXFlush(void)

{
  if (*(int *)(DAT_8043cb00 + 0x5ac) != 0) {
    gnt4___GXSetDirtyState_bl();
  }
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  gnt4_PPCSync();
  return;
}



// ==== 80226e98  gnt4-__GXAbort-bl ====

void gnt4___GXAbort_bl(void)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if ((*(char *)(DAT_8043cb00 + 0x5aa) != '\0') && (iVar4 = gnt4_GXGetGPFifo_bl(), iVar4 != 0)) {
    sVar5 = *(short *)(DAT_804367ec + 0x4e);
    do {
      sVar2 = *(short *)(DAT_804367ec + 0x4e);
      iVar4 = *(int *)(DAT_804367ec + 0x4e);
      bVar1 = sVar2 != sVar5;
      sVar5 = sVar2;
    } while (bVar1);
    do {
      uVar6 = gnt4_OSGetTime_bl();
      do {
        uVar7 = gnt4_OSGetTime_bl();
      } while ((uint)(8 < (uint)uVar7 - (uint)uVar6) +
               ((int)((ulonglong)uVar7 >> 0x20) -
                ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000)
               < 0x80000001);
      sVar5 = *(short *)(DAT_804367ec + 0x4e);
      do {
        sVar2 = *(short *)(DAT_804367ec + 0x4e);
        iVar3 = *(int *)(DAT_804367ec + 0x4e);
        bVar1 = sVar2 != sVar5;
        sVar5 = sVar2;
      } while (bVar1);
      bVar1 = iVar3 != iVar4;
      iVar4 = iVar3;
    } while (bVar1);
  }
  DAT_cc003018 = 1;
  uVar6 = gnt4_OSGetTime_bl();
  do {
    uVar7 = gnt4_OSGetTime_bl();
  } while ((uint)(0x32 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  DAT_cc003018 = 0;
  uVar6 = gnt4_OSGetTime_bl();
  do {
    uVar7 = gnt4_OSGetTime_bl();
  } while ((uint)(5 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  return;
}



// ==== 80227004  zz_0227004_ ====

void zz_0227004_(void)

{
  bool bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  
  if ((*(char *)(DAT_8043cb00 + 0x5aa) != '\0') && (iVar4 = gnt4_GXGetGPFifo_bl(), iVar4 != 0)) {
    sVar5 = *(short *)(DAT_804367ec + 0x4e);
    do {
      sVar2 = *(short *)(DAT_804367ec + 0x4e);
      iVar4 = *(int *)(DAT_804367ec + 0x4e);
      bVar1 = sVar2 != sVar5;
      sVar5 = sVar2;
    } while (bVar1);
    do {
      uVar6 = gnt4_OSGetTime_bl();
      do {
        uVar7 = gnt4_OSGetTime_bl();
      } while ((uint)(8 < (uint)uVar7 - (uint)uVar6) +
               ((int)((ulonglong)uVar7 >> 0x20) -
                ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000)
               < 0x80000001);
      sVar5 = *(short *)(DAT_804367ec + 0x4e);
      do {
        sVar2 = *(short *)(DAT_804367ec + 0x4e);
        iVar3 = *(int *)(DAT_804367ec + 0x4e);
        bVar1 = sVar2 != sVar5;
        sVar5 = sVar2;
      } while (bVar1);
      bVar1 = iVar3 != iVar4;
      iVar4 = iVar3;
    } while (bVar1);
  }
  DAT_cc003018 = 1;
  uVar6 = gnt4_OSGetTime_bl();
  do {
    uVar7 = gnt4_OSGetTime_bl();
  } while ((uint)(0x32 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  DAT_cc003018 = 0;
  uVar6 = gnt4_OSGetTime_bl();
  do {
    uVar7 = gnt4_OSGetTime_bl();
  } while ((uint)(5 < (uint)uVar7 - (uint)uVar6) +
           ((int)((ulonglong)uVar7 >> 0x20) -
            ((uint)((uint)uVar7 < (uint)uVar6) + (int)((ulonglong)uVar6 >> 0x20)) ^ 0x80000000) <
           0x80000001);
  zz_0225784_();
  return;
}



// ==== 80227174  gnt4-GXWaitDrawDone-bl ====

void gnt4_GXWaitDrawDone_bl(void)

{
  gnt4_OSDisableInterrupts_bl();
  while (DAT_80436830 == '\0') {
    gnt4_OSSleepThread_bl((int *)&DAT_80436834);
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802271c0  gnt4-GXDrawDone-bl ====

void gnt4_GXDrawDone_bl(void)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = 0x45000002;
  gnt4_GXFlush();
  DAT_80436830 = '\0';
  gnt4_OSRestoreInterrupts_bl();
  gnt4_OSDisableInterrupts_bl();
  while (DAT_80436830 == '\0') {
    gnt4_OSSleepThread_bl((int *)&DAT_80436834);
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80227240  gnt4-GXPixModeSync-bl ====

void gnt4_GXPixModeSync_bl(void)

{
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_8043cb00 + 0x1dc);
  *(undefined2 *)(DAT_8043cb00 + 2) = 0;
  return;
}



// ==== 80227264  gnt4-GXPokeAlphaMode-bl ====

void gnt4_GXPokeAlphaMode_bl(short param_1,ushort param_2)

{
  *(ushort *)(DAT_804367e8 + 6) = param_1 << 8 | param_2 & 0xff;
  return;
}



// ==== 80227278  gnt4-GXPokeAlphaRead-bl ====

void gnt4_GXPokeAlphaRead_bl(ushort param_1)

{
  *(ushort *)(DAT_804367e8 + 8) = param_1 & 3 | 4;
  return;
}



// ==== 80227298  gnt4-GXPokeAlphaUpdate-bl ====

void gnt4_GXPokeAlphaUpdate_bl(ushort param_1)

{
  *(ushort *)(DAT_804367e8 + 2) = (param_1 & 1) << 4 | *(ushort *)(DAT_804367e8 + 2) & 0xffef;
  return;
}



// ==== 802272b0  gnt4-GXPokeBlendMode-bl ====

void gnt4_GXPokeBlendMode_bl(int param_1,ushort param_2,ushort param_3,short param_4)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar3 = 1;
  if ((param_1 != 1) && (param_1 != 3)) {
    uVar3 = 0;
  }
  uVar2 = countLeadingZeros(3 - param_1);
  uVar1 = countLeadingZeros(2 - param_1);
  *(ushort *)(DAT_804367e8 + 2) =
       (param_3 & 7) << 5 |
       (param_2 & 7) << 8 |
       param_4 << 0xc |
       (ushort)(uVar1 >> 4) & 2 |
       (ushort)((uVar2 >> 5) << 0xb) & 0x800 | uVar3 | *(ushort *)(DAT_804367e8 + 2) & 0x1c;
  return;
}



// ==== 80227314  gnt4-GXPokeColorUpdate-bl ====

void gnt4_GXPokeColorUpdate_bl(ushort param_1)

{
  *(ushort *)(DAT_804367e8 + 2) = (param_1 & 1) << 3 | *(ushort *)(DAT_804367e8 + 2) & 0xfff7;
  return;
}



// ==== 8022732c  gnt4-GXPokeDstAlpha-bl ====

void gnt4_GXPokeDstAlpha_bl(ushort param_1,ushort param_2)

{
  *(ushort *)(DAT_804367e8 + 4) = (param_1 & 1) << 8 | param_2 & 0xff;
  return;
}



// ==== 80227350  gnt4-GXPokeDither-bl ====

void gnt4_GXPokeDither_bl(ushort param_1)

{
  *(ushort *)(DAT_804367e8 + 2) = (param_1 & 1) << 2 | *(ushort *)(DAT_804367e8 + 2) & 0xfffb;
  return;
}



// ==== 80227368  gnt4-GXPokeZMode-bl ====

void gnt4_GXPokeZMode_bl(ushort param_1,ushort param_2,ushort param_3)

{
  *DAT_804367e8 = (param_3 & 1) << 4 | (param_2 & 7) << 1 | param_1 & 1;
  return;
}



// ==== 80227388  gnt4-GXSetDrawSyncCallback-bl ====

undefined4 gnt4_GXSetDrawSyncCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80436828;
  gnt4_OSDisableInterrupts_bl();
  DAT_80436828 = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 802273cc  gnt4-GXTokenInterruptHandler-bl ====

void gnt4_GXTokenInterruptHandler_bl(undefined4 param_1,uint param_2)

{
  undefined2 uVar1;
  undefined1 auStack_2d0 [712];
  
  uVar1 = *(undefined2 *)(DAT_804367e8 + 0xe);
  if (DAT_80436828 != (code *)0x0) {
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
    (*DAT_80436828)(uVar1);
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  *(ushort *)(DAT_804367e8 + 10) = *(ushort *)(DAT_804367e8 + 10) & 0xfffb | 4;
  return;
}



// ==== 80227454  gnt4-GXSetDrawDoneCallback-bl ====

undefined4 gnt4_GXSetDrawDoneCallback_bl(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8043682c;
  gnt4_OSDisableInterrupts_bl();
  DAT_8043682c = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80227498  gnt4-GXFinishInterruptHandler-bl ====

void gnt4_GXFinishInterruptHandler_bl(undefined4 param_1,uint param_2)

{
  undefined1 auStack_2d0 [716];
  
  *(ushort *)(DAT_804367e8 + 10) = *(ushort *)(DAT_804367e8 + 10) & 0xfff7 | 8;
  DAT_80436830 = 1;
  if (DAT_8043682c != (code *)0x0) {
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
    (*DAT_8043682c)();
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  gnt4_OSWakeupThread_bl((int *)&DAT_80436834);
  return;
}



// ==== 80227518  gnt4-__GXPEInit-bl ====

void gnt4___GXPEInit_bl(void)

{
  gnt4___OSSetInterruptHandler_bl(0x12,gnt4_GXTokenInterruptHandler_bl);
  gnt4___OSSetInterruptHandler_bl(0x13,gnt4_GXFinishInterruptHandler_bl);
  gnt4_OSInitThreadQueue_bl((undefined4 *)&DAT_80436834);
  gnt4___OSUnmaskInterrupts_bl(0x2000);
  gnt4___OSUnmaskInterrupts_bl(0x1000);
  *(ushort *)(DAT_804367e8 + 10) = *(ushort *)(DAT_804367e8 + 10) & 0xfff0 | 0xf;
  return;
}



// ==== 8022758c  gnt4-__GXSetDirtyState-bl ====

void gnt4___GXSetDirtyState_bl(void)

{
  uint uVar1;
  
  uVar1 = *(uint *)(DAT_8043cb00 + 0x5ac);
  if ((uVar1 & 1) != 0) {
    gnt4___GXSetSUTexRegs_bl();
  }
  if ((uVar1 & 2) != 0) {
    gnt4___GXUpdateBPMask_bl();
  }
  if ((uVar1 & 4) != 0) {
    gnt4___GXSetGenMode_bl();
  }
  if ((uVar1 & 8) != 0) {
    gnt4___GXSetVCD_bl();
  }
  if ((uVar1 & 0x10) != 0) {
    gnt4___GXSetVAT();
  }
  if ((uVar1 & 0x18) != 0) {
    gnt4___GXCalculateVLim_bl();
  }
  *(undefined4 *)(DAT_8043cb00 + 0x5ac) = 0;
  return;
}



// ==== 8022760c  gnt4-GXBegin-bl ====

void gnt4_GXBegin_bl(byte param_1,byte param_2,undefined2 param_3)

{
  uint uVar1;
  
  uVar1 = DAT_8043cb00[0x16b];
  if (uVar1 != 0) {
    if ((uVar1 & 1) != 0) {
      gnt4___GXSetSUTexRegs_bl();
    }
    if ((uVar1 & 2) != 0) {
      gnt4___GXUpdateBPMask_bl();
    }
    if ((uVar1 & 4) != 0) {
      gnt4___GXSetGenMode_bl();
    }
    if ((uVar1 & 8) != 0) {
      gnt4___GXSetVCD_bl();
    }
    if ((uVar1 & 0x10) != 0) {
      gnt4___GXSetVAT();
    }
    if ((uVar1 & 0x18) != 0) {
      gnt4___GXCalculateVLim_bl();
    }
    DAT_8043cb00[0x16b] = 0;
  }
  if (*DAT_8043cb00 == 0) {
    gnt4___GXSendFlushPrim_bl();
  }
  DAT_cc008000._0_1_ = param_2 | param_1;
  DAT_cc008000._0_2_ = param_3;
  return;
}



// ==== 802276dc  gnt4-__GXSendFlushPrim-bl ====

void gnt4___GXSendFlushPrim_bl(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = (uint)*(ushort *)(DAT_8043cb00 + 4) * (uint)*(ushort *)(DAT_8043cb00 + 6);
  DAT_cc008000._0_1_ = 0x98;
  DAT_cc008000._0_2_ = *(ushort *)(DAT_8043cb00 + 4);
  uVar1 = iVar3 + 3;
  uVar2 = uVar1 >> 2;
  if (iVar3 != 0) {
    uVar1 = uVar1 >> 5;
    if (uVar1 != 0) {
      do {
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        DAT_cc008000 = 0;
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
      uVar2 = uVar2 & 7;
      if (uVar2 == 0) goto LAB_80227754;
    }
    do {
      DAT_cc008000 = 0;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
LAB_80227754:
  *(undefined2 *)(DAT_8043cb00 + 2) = 1;
  return;
}



