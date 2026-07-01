// ==== 8021254c  gnt4-VIGetTvFormat ====

undefined4 gnt4_VIGetTvFormat(void)

{
  undefined4 unaff_r31;
  
  gnt4_OSDisableInterrupts_bl();
  switch(DAT_804365ec) {
  case 0:
  case 3:
  case 6:
    unaff_r31 = 0;
    break;
  case 1:
  case 4:
    unaff_r31 = 1;
    break;
  case 2:
  case 5:
    unaff_r31 = DAT_804365ec;
  }
  gnt4_OSRestoreInterrupts_bl();
  return unaff_r31;
}



// ==== 802125b4  VIGetDTVStatus ====

ushort VIGetDTVStatus(void)

{
  ushort uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_cc00206e;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1 & 1;
}



// ==== 802125f0  zz_02125f0_ ====

void zz_02125f0_(int param_1,int param_2,short *param_3,ushort *param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (param_2 + -1) * 2 + (param_1 - 1U) / (uint)*(ushort *)(DAT_804365e8 + 0x1a);
  if (DAT_803d7c7c == 0) {
    uVar2 = (uint)*(ushort *)(DAT_804365e8 + 0x18);
    if (uVar1 < uVar2) {
      if (uVar1 < (uint)*(ushort *)(DAT_804365e8 + 4) + (uint)*DAT_804365e8 * 3) {
        *param_4 = 0xffff;
      }
      else if (uVar1 < uVar2 - *(ushort *)(DAT_804365e8 + 8)) {
        *param_4 = ((short)uVar1 + (ushort)*DAT_804365e8 * -3) - *(ushort *)(DAT_804365e8 + 4) &
                   0xfffe;
      }
      else {
        *param_4 = 0xffff;
      }
    }
    else {
      uVar1 = uVar1 - uVar2;
      if (uVar1 < (uint)*(ushort *)(DAT_804365e8 + 6) + (uint)*DAT_804365e8 * 3) {
        *param_4 = 0xffff;
      }
      else if (uVar1 < uVar2 - *(ushort *)(DAT_804365e8 + 10)) {
        *param_4 = (((short)uVar1 + (ushort)*DAT_804365e8 * -3) - *(ushort *)(DAT_804365e8 + 6) &
                   0xfffe) + 1;
      }
      else {
        *param_4 = 0xffff;
      }
    }
  }
  else if (DAT_803d7c7c == 1) {
    uVar2 = (uint)*(ushort *)(DAT_804365e8 + 0x18);
    if (uVar2 <= uVar1) {
      uVar1 = uVar1 - uVar2;
    }
    if (uVar1 < (uint)*(ushort *)(DAT_804365e8 + 4) + (uint)*DAT_804365e8 * 3) {
      *param_4 = 0xffff;
    }
    else if (uVar1 < uVar2 - *(ushort *)(DAT_804365e8 + 8)) {
      *param_4 = ((short)uVar1 + (ushort)*DAT_804365e8 * -3) - *(ushort *)(DAT_804365e8 + 4) &
                 0xfffe;
    }
    else {
      *param_4 = 0xffff;
    }
  }
  else if (DAT_803d7c7c == 2) {
    uVar2 = (uint)*(ushort *)(DAT_804365e8 + 0x18);
    if (uVar1 < uVar2) {
      if (uVar1 < (uint)*(ushort *)(DAT_804365e8 + 4) + (uint)*DAT_804365e8 * 3) {
        *param_4 = 0xffff;
      }
      else if (uVar1 < uVar2 - *(ushort *)(DAT_804365e8 + 8)) {
        *param_4 = ((short)uVar1 + (ushort)*DAT_804365e8 * -3) - *(ushort *)(DAT_804365e8 + 4);
      }
      else {
        *param_4 = 0xffff;
      }
    }
    else {
      uVar1 = uVar1 - uVar2;
      if (uVar1 < (uint)*(ushort *)(DAT_804365e8 + 6) + (uint)*DAT_804365e8 * 3) {
        *param_4 = 0xffff;
      }
      else if (uVar1 < uVar2 - *(ushort *)(DAT_804365e8 + 10)) {
        *param_4 = ((short)uVar1 + (ushort)*DAT_804365e8 * -3) - *(ushort *)(DAT_804365e8 + 6) &
                   0xfffe;
      }
      else {
        *param_4 = 0xffff;
      }
    }
  }
  *param_3 = (short)param_1 + -1;
  return;
}



// ==== 8021280c  zz_021280c_ ====

void zz_021280c_(short *param_1,ushort *param_2)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = DAT_cc00202c;
  uVar4 = uVar2 & 0x7ff;
  do {
    uVar2 = DAT_cc00202c;
    uVar3 = DAT_cc00202e;
    uVar5 = uVar2 & 0x7ff;
    bVar1 = uVar4 != uVar5;
    uVar4 = uVar5;
  } while (bVar1);
  zz_02125f0_(uVar3 & 0x7ff,uVar5,param_1,param_2);
  return;
}



// ==== 8021286c  ClampCircle ====

void ClampCircle(char *param_1,char *param_2,char param_3,char param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  undefined8 local_28;
  
  iVar3 = (int)param_4;
  iVar1 = (int)*param_1;
  iVar4 = (int)*param_2;
  if ((-iVar3 < iVar1) && (iVar1 < iVar3)) {
    iVar1 = 0;
  }
  else if (iVar1 < 1) {
    iVar1 = iVar1 + iVar3;
  }
  else {
    iVar1 = iVar1 - iVar3;
  }
  if ((-iVar3 < iVar4) && (iVar4 < iVar3)) {
    iVar4 = 0;
  }
  else if (iVar4 < 1) {
    iVar4 = iVar4 + iVar3;
  }
  else {
    iVar4 = iVar4 - iVar3;
  }
  iVar3 = (int)param_3;
  uVar2 = iVar1 * iVar1 + iVar4 * iVar4;
  if (iVar3 * iVar3 < (int)uVar2) {
    uVar2 = uVar2 ^ 0x80000000;
    if ((float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043cae8) <= FLOAT_8043cad0) {
      local_28 = (double)CONCAT44(0x43300000,uVar2);
      local_28 = local_28 - DOUBLE_8043cae8;
    }
    else {
      dVar5 = 1.0 / SQRT((double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043cae8));
      dVar5 = DOUBLE_8043cad8 * dVar5 *
              (DOUBLE_8043cae0 -
              (double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043cae8) * dVar5 * dVar5)
      ;
      local_28 = (double)CONCAT44(0x43300000,uVar2);
      dVar5 = DOUBLE_8043cad8 * dVar5 *
              (DOUBLE_8043cae0 -
              (double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043cae8) * dVar5 * dVar5)
      ;
      local_28 = (double)(float)(local_28 - DOUBLE_8043cae8) *
                 DOUBLE_8043cad8 * dVar5 *
                 (DOUBLE_8043cae0 -
                 (double)(float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043cae8) *
                 dVar5 * dVar5);
    }
    iVar1 = (iVar1 * iVar3) / (int)local_28;
    iVar4 = (iVar4 * iVar3) / (int)local_28;
  }
  *param_1 = (char)iVar1;
  *param_2 = (char)iVar4;
  return;
}



// ==== 80212a14  PADClampCircle ====

void PADClampCircle(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(char *)(param_1 + 10) == '\0') {
      ClampCircle((char *)(param_1 + 2),(char *)(param_1 + 3),DAT_802b44b8,DAT_802b44b2);
      ClampCircle((char *)(param_1 + 4),(char *)(param_1 + 5),DAT_802b44b9,DAT_802b44b5);
      if (DAT_802b44b0 < *(byte *)(param_1 + 6)) {
        if (DAT_802b44b1 < *(byte *)(param_1 + 6)) {
          *(byte *)(param_1 + 6) = DAT_802b44b1;
        }
        *(byte *)(param_1 + 6) = *(char *)(param_1 + 6) - DAT_802b44b0;
      }
      else {
        *(undefined1 *)(param_1 + 6) = 0;
      }
      if (DAT_802b44b0 < *(byte *)(param_1 + 7)) {
        if (DAT_802b44b1 < *(byte *)(param_1 + 7)) {
          *(byte *)(param_1 + 7) = DAT_802b44b1;
        }
        *(byte *)(param_1 + 7) = *(char *)(param_1 + 7) - DAT_802b44b0;
      }
      else {
        *(undefined1 *)(param_1 + 7) = 0;
      }
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 0xc;
  } while (iVar1 < 4);
  return;
}



// ==== 80212b20  gnt4-UpdateOrigin-bl ====

void gnt4_UpdateOrigin_bl(uint param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = param_1 * 0xc;
  uVar1 = DAT_80435d04 & 0x700;
  if (uVar1 == 0x400) goto LAB_80212c48;
  if (uVar1 < 0x400) {
    if (uVar1 == 0x200) {
      (&DAT_803d7cc4)[iVar2] = (&DAT_803d7cc4)[iVar2] & 0xf0;
      (&DAT_803d7cc5)[iVar2] = (&DAT_803d7cc5)[iVar2] & 0xf0;
      (&DAT_803d7cc6)[iVar2] = (&DAT_803d7cc6)[iVar2] & 0xf0;
      (&DAT_803d7cc7)[iVar2] = (&DAT_803d7cc7)[iVar2] & 0xf0;
      goto LAB_80212c48;
    }
    if (0x1ff < uVar1) goto LAB_80212c48;
    if (uVar1 == 0x100) {
      (&DAT_803d7cc4)[iVar2] = (&DAT_803d7cc4)[iVar2] & 0xf0;
      (&DAT_803d7cc5)[iVar2] = (&DAT_803d7cc5)[iVar2] & 0xf0;
      (&DAT_803d7cc8)[iVar2] = (&DAT_803d7cc8)[iVar2] & 0xf0;
      (&DAT_803d7cc9)[iVar2] = (&DAT_803d7cc9)[iVar2] & 0xf0;
      goto LAB_80212c48;
    }
    if ((0xff < uVar1) || (uVar1 != 0)) goto LAB_80212c48;
  }
  else if (uVar1 != 0x600) {
    if (uVar1 < 0x600) {
      if (uVar1 != 0x500) goto LAB_80212c48;
    }
    else if (uVar1 != 0x700) goto LAB_80212c48;
  }
  (&DAT_803d7cc6)[iVar2] = (&DAT_803d7cc6)[iVar2] & 0xf0;
  (&DAT_803d7cc7)[iVar2] = (&DAT_803d7cc7)[iVar2] & 0xf0;
  (&DAT_803d7cc8)[iVar2] = (&DAT_803d7cc8)[iVar2] & 0xf0;
  (&DAT_803d7cc9)[iVar2] = (&DAT_803d7cc9)[iVar2] & 0xf0;
LAB_80212c48:
  (&DAT_803d7cc2)[iVar2] = (&DAT_803d7cc2)[iVar2] + -0x80;
  (&DAT_803d7cc3)[iVar2] = (&DAT_803d7cc3)[iVar2] + -0x80;
  (&DAT_803d7cc4)[iVar2] = (&DAT_803d7cc4)[iVar2] + -0x80;
  (&DAT_803d7cc5)[iVar2] = (&DAT_803d7cc5)[iVar2] + -0x80;
  if ((((DAT_80435d00 & 0x80000000U >> param_1) != 0) && ('@' < (char)(&DAT_803d7cc2)[iVar2])) &&
     (uVar1 = gnt4_SIGetType(param_1), (uVar1 & 0xffff0000) == 0x9000000)) {
    (&DAT_803d7cc2)[iVar2] = 0;
  }
  return;
}



// ==== 80212cc4  gnt4-PADOriginCallback-bl ====

void gnt4_PADOriginCallback_bl(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 auStack_14 [4];
  
  if ((param_2 & 0xf) == 0) {
    gnt4_UpdateOrigin_bl(DAT_80435cfc);
    uVar1 = DAT_80435cfc;
    DAT_80436604 = DAT_80436604 | 0x80000000U >> DAT_80435cfc;
    gnt4_SIGetResponse(DAT_80435cfc,auStack_14);
    gnt4_SISetCommand(uVar1,DAT_80435d04 | 0x400000);
    gnt4_SIEnablePolling(DAT_80436604);
  }
  DAT_80435cfc = countLeadingZeros(DAT_80436608);
  if (DAT_80435cfc != 0x20) {
    DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
    gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
    gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
  }
  return;
}



// ==== 80212d88  gnt4-PADOriginUpdateCallback-bl ====

void gnt4_PADOriginUpdateCallback_bl(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0x80000000 >> param_1;
  if ((DAT_80436604 & uVar1) != 0) {
    if ((param_2 & 0xf) == 0) {
      gnt4_UpdateOrigin_bl(param_1);
    }
    if ((param_2 & 8) != 0) {
      gnt4_OSDisableInterrupts_bl();
      gnt4_SIDisablePolling(uVar1);
      uVar1 = ~uVar1;
      DAT_80436604 = DAT_80436604 & uVar1;
      DAT_80436610 = DAT_80436610 & uVar1;
      DAT_80436614 = DAT_80436614 & uVar1;
      DAT_80436618 = DAT_80436618 & uVar1;
      gnt4_OSSetWirelessID_bl(param_1,0);
      gnt4_OSRestoreInterrupts_bl();
    }
  }
  return;
}



// ==== 80212e48  gnt4-PADProbeCallback-bl ====

void gnt4_PADProbeCallback_bl(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 auStack_14 [3];
  
  iVar1 = DAT_80435cfc;
  if ((param_2 & 0xf) == 0) {
    DAT_80436604 = DAT_80436604 | 0x80000000U >> DAT_80435cfc;
    gnt4_SIGetResponse(DAT_80435cfc,auStack_14);
    gnt4_SISetCommand(iVar1,DAT_80435d04 | 0x400000);
    gnt4_SIEnablePolling(DAT_80436604);
    DAT_80436610 = DAT_80436610 | 0x80000000U >> DAT_80435cfc;
  }
  DAT_80435cfc = countLeadingZeros(DAT_80436608);
  if (DAT_80435cfc != 0x20) {
    DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
    gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
    gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
  }
  return;
}



// ==== 80212f20  gnt4-PADTypeAndStatusCallback-bl ====

void gnt4_PADTypeAndStatusCallback_bl(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined4 auStack_24 [5];
  
  uVar1 = DAT_80435cfc;
  uVar5 = 0x80000000 >> DAT_80435cfc;
  uVar2 = DAT_8043660c & ~uVar5;
  uVar4 = DAT_8043660c & uVar5;
  iVar3 = 1;
  DAT_8043660c = uVar2;
  if ((param_2 & 0xf) != 0) {
    DAT_80435cfc = countLeadingZeros(DAT_80436608);
    if (DAT_80435cfc == 0x20) {
      return;
    }
    DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
    gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
    gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
    return;
  }
  *(uint *)(&DAT_803d7cb0 + DAT_80435cfc * 4) = param_2 & 0xffffff00;
  if (((param_2 & 0x18000000) != 0x8000000) || ((param_2 & 0x1000000) == 0)) {
    DAT_80435cfc = countLeadingZeros(DAT_80436608);
    if (DAT_80435cfc == 0x20) {
      return;
    }
    DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
    gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
    gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
    return;
  }
  if (1 < DAT_80435d08) {
    if (((param_2 & 0x80000000) == 0) || ((param_2 & 0x4000000) != 0)) {
      if (uVar4 == 0) {
        iVar3 = gnt4_SITransfer_bl(uVar1,(undefined4 *)&DAT_80435d10,1,&DAT_803d7cc0 + uVar1 * 0xc,
                                   10,-0x7fded33c,0,0);
      }
      else {
        iVar3 = gnt4_SITransfer_bl(uVar1,(undefined4 *)&DAT_80435d14,3,&DAT_803d7cc0 + uVar1 * 0xc,
                                   10,-0x7fded33c,0,0);
      }
    }
    else if ((((param_2 & 0x100000) != 0) && ((param_2 & 0x80000) == 0)) &&
            ((param_2 & 0x40000) == 0)) {
      if ((param_2 & 0x40000000) == 0) {
        iVar3 = gnt4_SITransfer_bl(uVar1,&DAT_803d7cf0 + uVar1,3,&DAT_803d7cc0 + uVar1 * 0xc,8,
                                   -0x7fded1b8,0,0);
      }
      else {
        iVar3 = gnt4_SITransfer_bl(uVar1,(undefined4 *)&DAT_80435d10,1,&DAT_803d7cc0 + uVar1 * 0xc,
                                   10,-0x7fded33c,0,0);
      }
    }
    if (iVar3 == 0) {
      DAT_80435cfc = countLeadingZeros(DAT_80436608);
      DAT_80436618 = DAT_80436618 | uVar5;
      if (DAT_80435cfc != 0x20) {
        DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
        gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
        gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
      }
    }
    return;
  }
  DAT_80436604 = DAT_80436604 | uVar5;
  gnt4_SIGetResponse(uVar1,auStack_24);
  gnt4_SISetCommand(uVar1,DAT_80435d04 | 0x400000);
  gnt4_SIEnablePolling(DAT_80436604);
  DAT_80435cfc = countLeadingZeros(DAT_80436608);
  if (DAT_80435cfc == 0x20) {
    return;
  }
  DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
  gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
  gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
  return;
}



// ==== 8021324c  gnt4-PADReceiveCheckCallback-bl ====

void gnt4_PADReceiveCheckCallback_bl(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = 0x80000000 >> param_1;
  if ((DAT_80436604 & uVar1) != 0) {
    DAT_80436610 = DAT_80436610 & ~uVar1;
    DAT_80436614 = DAT_80436614 & ~uVar1;
    if (((((param_2 & 0xf) == 0) && ((param_2 & 0x80000000) != 0)) && ((param_2 & 0x100000) != 0))
       && ((((param_2 & 0x40000000) != 0 && ((param_2 & 0x4000000) == 0)) &&
           (((param_2 & 0x80000) == 0 && ((param_2 & 0x40000) == 0)))))) {
      gnt4_SITransfer_bl(param_1,(undefined4 *)&DAT_80435d10,1,&DAT_803d7cc0 + param_1 * 0xc,10,
                         -0x7fded278,0,0);
      return;
    }
    gnt4_OSDisableInterrupts_bl();
    gnt4_SIDisablePolling(uVar1);
    uVar1 = ~uVar1;
    DAT_80436604 = DAT_80436604 & uVar1;
    DAT_80436610 = DAT_80436610 & uVar1;
    DAT_80436614 = DAT_80436614 & uVar1;
    DAT_80436618 = DAT_80436618 & uVar1;
    gnt4_OSSetWirelessID_bl(param_1,0);
    gnt4_OSRestoreInterrupts_bl();
  }
  return;
}



// ==== 80213380  gnt4-PADReset-bl ====

undefined4 gnt4_PADReset_bl(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  gnt4_OSDisableInterrupts_bl();
  uVar2 = (param_1 | DAT_80436618) & ~(DAT_80436610 | DAT_80436614);
  DAT_80436608 = DAT_80436608 | uVar2;
  DAT_80436618 = 0;
  uVar1 = DAT_80436608 & DAT_80436604;
  if (DAT_80435d08 == 4) {
    DAT_8043660c = DAT_8043660c | uVar2;
  }
  DAT_80436604 = DAT_80436604 & ~uVar2;
  gnt4_SIDisablePolling(uVar1);
  if (DAT_80435cfc == 0x20) {
    DAT_80435cfc = countLeadingZeros(DAT_80436608);
    if (DAT_80435cfc != 0x20) {
      DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
      gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
      gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 80213480  gnt4-PADRecalibrate-bl ====

undefined4 gnt4_PADRecalibrate_bl(uint param_1)

{
  uint uVar1;
  uint uVar2;
  
  gnt4_OSDisableInterrupts_bl();
  uVar2 = (param_1 | DAT_80436618) & ~(DAT_80436610 | DAT_80436614);
  DAT_80436608 = DAT_80436608 | uVar2;
  DAT_80436618 = 0;
  uVar1 = DAT_80436608 & DAT_80436604;
  if ((DAT_800030e3 & 0x40) == 0) {
    DAT_8043660c = DAT_8043660c | uVar2;
  }
  DAT_80436604 = DAT_80436604 & ~uVar2;
  gnt4_SIDisablePolling(uVar1);
  if (DAT_80435cfc == 0x20) {
    DAT_80435cfc = countLeadingZeros(DAT_80436608);
    if (DAT_80435cfc != 0x20) {
      DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
      gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
      gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 80213584  zz_0213584_ ====

undefined4
zz_0213584_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,int param_11,uint param_12,undefined4 param_13,
           undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined8 uVar6;
  undefined8 extraout_f1;
  undefined8 uVar7;
  undefined8 uVar8;
  
  if (DAT_80436600 == 0) {
    uVar6 = gnt4_OSRegisterVersion_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435cf8,
                       param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar3 = extraout_r4;
    if (DAT_80436624 != 0) {
      uVar6 = zz_0213bec_(DAT_80436624);
      uVar3 = extraout_r4_00;
    }
    DAT_80436600 = 1;
    if (DAT_804364c0 != 0) {
      uVar6 = gnt4_OSGetTime_bl();
      iVar1 = (int)((ulonglong)uVar6 >> 0x20);
      uVar2 = (uint)uVar6;
      uVar6 = extraout_f1;
      uVar7 = gnt4___shr2i(iVar1,uVar2,0x10);
      param_12 = (uint)uVar7 & 0xffff;
      iVar5 = (uVar2 & 0xffff) + param_12;
      uVar7 = gnt4___shr2i(iVar1,uVar2,0x20);
      uVar8 = gnt4___shr2i(iVar1,uVar2,0x30);
      param_11 = ((uint)uVar8 & 0xffff) + ((uint)uVar7 & 0xffff) + iVar5;
      uVar3 = 0x3fff;
      DAT_8043660c = 0xf0000000;
      DAT_800030e0 = (ushort)param_11 & 0x3fff;
    }
    DAT_803d7cf0 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d000000;
    DAT_803d7cf4 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d400000;
    DAT_803d7cf8 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d800000;
    DAT_803d7cfc = (DAT_800030e0 & 0x3fff) << 8 | 0x4dc00000;
    zz_020adec_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x80000000,uVar3,
                param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_OSRegisterResetFunction_bl(-0x7fc5a598);
    gnt4_OSDisableInterrupts_bl();
    uVar4 = (DAT_80436618 | 0xf0000000) & ~(DAT_80436610 | DAT_80436614);
    DAT_80436608 = DAT_80436608 | uVar4;
    DAT_80436618 = 0;
    uVar2 = DAT_80436608 & DAT_80436604;
    if (DAT_80435d08 == 4) {
      DAT_8043660c = DAT_8043660c | uVar4;
    }
    DAT_80436604 = DAT_80436604 & ~uVar4;
    gnt4_SIDisablePolling(uVar2);
    if ((DAT_80435cfc == 0x20) &&
       (DAT_80435cfc = countLeadingZeros(DAT_80436608), DAT_80435cfc != 0x20)) {
      DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
      gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
      gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  return 1;
}



// ==== 8021379c  zz_021379c_ ====

uint zz_021379c_(ushort *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined *puVar6;
  uint local_3c [3];
  
  gnt4_OSDisableInterrupts_bl();
  uVar4 = 0;
  puVar6 = &DAT_803d7cc0;
  uVar3 = 0;
  do {
    uVar5 = 0x80000000 >> uVar4;
    if ((DAT_80436618 & uVar5) == 0) {
      if ((DAT_80436608 & uVar5) == 0) {
        if (DAT_80435cfc != uVar4) {
          if ((DAT_80436604 & uVar5) == 0) {
            *(undefined1 *)(param_1 + 5) = 0xff;
            gnt4_memset(param_1,0,10);
          }
          else {
            iVar1 = gnt4_SIIsChanBusy(uVar4);
            if (iVar1 == 0) {
              uVar2 = gnt4_SIGetStatus(uVar4);
              if ((uVar2 & 8) == 0) {
                uVar2 = gnt4_SIGetType(uVar4);
                if ((uVar2 & 0x20000000) == 0) {
                  uVar3 = uVar3 | uVar5;
                }
                iVar1 = gnt4_SIGetResponse(uVar4,local_3c);
                if (iVar1 == 0) {
                  *(undefined1 *)(param_1 + 5) = 0xfd;
                  gnt4_memset(param_1,0,10);
                }
                else if ((local_3c[0] & 0x80000000) == 0) {
                  (*DAT_80435d0c)(uVar4,param_1,local_3c);
                  if ((*param_1 & 0x2000) == 0) {
                    *(undefined1 *)(param_1 + 5) = 0;
                    *param_1 = *param_1 & 0xff7f;
                  }
                  else {
                    *(undefined1 *)(param_1 + 5) = 0xfd;
                    gnt4_memset(param_1,0,10);
                    gnt4_SITransfer_bl(uVar4,(undefined4 *)&DAT_80435d10,1,puVar6,10,-0x7fded278,0,0
                                      );
                  }
                }
                else {
                  *(undefined1 *)(param_1 + 5) = 0xfd;
                  gnt4_memset(param_1,0,10);
                }
              }
              else {
                gnt4_SIGetResponse(uVar4,local_3c);
                if ((DAT_80436610 & uVar5) == 0) {
                  gnt4_OSDisableInterrupts_bl();
                  gnt4_SIDisablePolling(uVar5);
                  uVar5 = ~uVar5;
                  DAT_80436604 = DAT_80436604 & uVar5;
                  DAT_80436610 = DAT_80436610 & uVar5;
                  DAT_80436614 = DAT_80436614 & uVar5;
                  DAT_80436618 = DAT_80436618 & uVar5;
                  gnt4_OSSetWirelessID_bl(uVar4,0);
                  gnt4_OSRestoreInterrupts_bl();
                  *(undefined1 *)(param_1 + 5) = 0xff;
                  gnt4_memset(param_1,0,10);
                }
                else {
                  *(undefined1 *)(param_1 + 5) = 0;
                  gnt4_memset(param_1,0,10);
                  if ((DAT_80436614 & uVar5) == 0) {
                    DAT_80436614 = DAT_80436614 | uVar5;
                    gnt4_SIGetTypeAsync(uVar4,gnt4_PADReceiveCheckCallback_bl);
                  }
                }
              }
            }
            else {
              *(undefined1 *)(param_1 + 5) = 0xfd;
              gnt4_memset(param_1,0,10);
            }
          }
          goto LAB_80213b14;
        }
      }
      *(undefined1 *)(param_1 + 5) = 0xfe;
      gnt4_memset(param_1,0,10);
    }
    else {
      gnt4_OSDisableInterrupts_bl();
      uVar2 = DAT_80436618 & ~(DAT_80436610 | DAT_80436614);
      DAT_80436608 = DAT_80436608 | uVar2;
      DAT_80436618 = 0;
      uVar5 = DAT_80436608 & DAT_80436604;
      if (DAT_80435d08 == 4) {
        DAT_8043660c = DAT_8043660c | uVar2;
      }
      DAT_80436604 = DAT_80436604 & ~uVar2;
      gnt4_SIDisablePolling(uVar5);
      if (DAT_80435cfc == 0x20) {
        DAT_80435cfc = countLeadingZeros(DAT_80436608);
        if (DAT_80435cfc != 0x20) {
          DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
          gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
          gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
        }
      }
      gnt4_OSRestoreInterrupts_bl();
      *(undefined1 *)(param_1 + 5) = 0xfe;
      gnt4_memset(param_1,0,10);
    }
LAB_80213b14:
    uVar4 = uVar4 + 1;
    puVar6 = puVar6 + 0xc;
    param_1 = param_1 + 6;
    if (3 < (int)uVar4) {
      gnt4_OSRestoreInterrupts_bl();
      return uVar3;
    }
  } while( true );
}



// ==== 80213b48  gnt4-PADControlMotor-bl ====

void gnt4_PADControlMotor_bl(uint param_1,uint param_2)

{
  uint uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  if (((DAT_80436604 & 0x80000000U >> param_1) != 0) &&
     (uVar1 = gnt4_SIGetType(param_1), (uVar1 & 0x20000000) == 0)) {
    if ((DAT_80435d08 < 2) && (param_2 == 2)) {
      param_2 = 0;
    }
    gnt4_SISetCommand(param_1,DAT_80435d04 | 0x400000 | param_2 & 3);
    gnt4_SITransferCommands();
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80213bec  zz_0213bec_ ====

void zz_0213bec_(int param_1)

{
  DAT_80436624 = 0;
  if (param_1 == 1) {
    DAT_80435d0c = gnt4_SPEC1_MakeStatus_bl;
  }
  else if (param_1 < 1) {
    if (-1 < param_1) {
      DAT_80435d0c = gnt4_SPEC0_MakeStatus_bl;
    }
  }
  else if (param_1 < 6) {
    DAT_80435d0c = gnt4_SPEC2_MakeStatus_bl;
  }
  DAT_80435d08 = param_1;
  return;
}



// ==== 80213c4c  gnt4-SPEC0_MakeStatus-bl ====

void gnt4_SPEC0_MakeStatus_bl(undefined4 param_1,ushort *param_2,uint *param_3)

{
  ushort uVar1;
  
  uVar1 = 0;
  *param_2 = 0;
  if ((*param_3 >> 0x10 & 8) != 0) {
    uVar1 = 0x100;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x20) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x200;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x100) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x400;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x800;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x1000;
  }
  *param_2 = *param_2 | uVar1;
  *(char *)(param_2 + 1) = (char)(param_3[1] >> 0x10);
  *(char *)((int)param_2 + 3) = (char)(param_3[1] >> 0x18);
  *(char *)(param_2 + 2) = (char)param_3[1];
  *(char *)((int)param_2 + 5) = (char)(param_3[1] >> 8);
  *(char *)(param_2 + 3) = (char)(*param_3 >> 8);
  *(char *)((int)param_2 + 7) = (char)*param_3;
  *(undefined1 *)(param_2 + 4) = 0;
  *(undefined1 *)((int)param_2 + 9) = 0;
  if (0xa9 < *(byte *)(param_2 + 3)) {
    *param_2 = *param_2 | 0x40;
  }
  if (0xa9 < *(byte *)((int)param_2 + 7)) {
    *param_2 = *param_2 | 0x20;
  }
  *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + -0x80;
  *(char *)((int)param_2 + 3) = *(char *)((int)param_2 + 3) + -0x80;
  *(char *)(param_2 + 2) = *(char *)(param_2 + 2) + -0x80;
  *(char *)((int)param_2 + 5) = *(char *)((int)param_2 + 5) + -0x80;
  return;
}



// ==== 80213dc0  gnt4-SPEC1_MakeStatus-bl ====

void gnt4_SPEC1_MakeStatus_bl(undefined4 param_1,ushort *param_2,uint *param_3)

{
  ushort uVar1;
  
  uVar1 = 0;
  *param_2 = 0;
  if ((*param_3 >> 0x10 & 0x80) != 0) {
    uVar1 = 0x100;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x100) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x200;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x20) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x400;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x10) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x800;
  }
  *param_2 = *param_2 | uVar1;
  if ((*param_3 >> 0x10 & 0x200) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x1000;
  }
  *param_2 = *param_2 | uVar1;
  *(char *)(param_2 + 1) = (char)(param_3[1] >> 0x10);
  *(char *)((int)param_2 + 3) = (char)(param_3[1] >> 0x18);
  *(char *)(param_2 + 2) = (char)param_3[1];
  *(char *)((int)param_2 + 5) = (char)(param_3[1] >> 8);
  *(char *)(param_2 + 3) = (char)(*param_3 >> 8);
  *(char *)((int)param_2 + 7) = (char)*param_3;
  *(undefined1 *)(param_2 + 4) = 0;
  *(undefined1 *)((int)param_2 + 9) = 0;
  if (0xa9 < *(byte *)(param_2 + 3)) {
    *param_2 = *param_2 | 0x40;
  }
  if (0xa9 < *(byte *)((int)param_2 + 7)) {
    *param_2 = *param_2 | 0x20;
  }
  *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + -0x80;
  *(char *)((int)param_2 + 3) = *(char *)((int)param_2 + 3) + -0x80;
  *(char *)(param_2 + 2) = *(char *)(param_2 + 2) + -0x80;
  *(char *)((int)param_2 + 5) = *(char *)((int)param_2 + 5) + -0x80;
  return;
}



// ==== 80213f34  gnt4-SPEC2_MakeStatus-bl ====

void gnt4_SPEC2_MakeStatus_bl(int param_1,ushort *param_2,undefined4 *param_3)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  char cVar6;
  
  *param_2 = (ushort)((uint)*param_3 >> 0x10) & 0x3fff;
  *(char *)(param_2 + 1) = (char)((uint)*param_3 >> 8);
  *(char *)((int)param_2 + 3) = (char)*param_3;
  uVar3 = DAT_80435d04 & 0x700;
  if (uVar3 == 0x400) {
    *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
    *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
    *(undefined1 *)(param_2 + 3) = 0;
    *(undefined1 *)((int)param_2 + 7) = 0;
    *(char *)(param_2 + 4) = (char)((uint)param_3[1] >> 8);
    *(char *)((int)param_2 + 9) = (char)param_3[1];
    goto LAB_80214140;
  }
  if (uVar3 < 0x400) {
    if (uVar3 == 0x200) {
      *(byte *)(param_2 + 2) = (byte)((uint)param_3[1] >> 0x18) & 0xf0;
      *(byte *)((int)param_2 + 5) = (byte)((uint)param_3[1] >> 0x14) & 0xf0;
      *(byte *)(param_2 + 3) = (byte)((uint)param_3[1] >> 0x10) & 0xf0;
      *(byte *)((int)param_2 + 7) = (byte)((uint)param_3[1] >> 0xc) & 0xf0;
      *(char *)(param_2 + 4) = (char)((uint)param_3[1] >> 8);
      *(char *)((int)param_2 + 9) = (char)param_3[1];
      goto LAB_80214140;
    }
    if (0x1ff < uVar3) {
      if (uVar3 == 0x300) {
        *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
        *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
        *(char *)(param_2 + 3) = (char)((uint)param_3[1] >> 8);
        *(char *)((int)param_2 + 7) = (char)param_3[1];
        *(undefined1 *)(param_2 + 4) = 0;
        *(undefined1 *)((int)param_2 + 9) = 0;
      }
      goto LAB_80214140;
    }
    if (uVar3 == 0x100) {
      *(byte *)(param_2 + 2) = (byte)((uint)param_3[1] >> 0x18) & 0xf0;
      *(byte *)((int)param_2 + 5) = (byte)((uint)param_3[1] >> 0x14) & 0xf0;
      *(char *)(param_2 + 3) = (char)((uint)param_3[1] >> 0x10);
      *(char *)((int)param_2 + 7) = (char)((uint)param_3[1] >> 8);
      *(byte *)(param_2 + 4) = (byte)param_3[1] & 0xf0;
      *(char *)((int)param_2 + 9) = (char)(param_3[1] << 4);
      goto LAB_80214140;
    }
    if ((0xff < uVar3) || (uVar3 != 0)) goto LAB_80214140;
  }
  else if (uVar3 != 0x600) {
    if (uVar3 < 0x600) {
      if (uVar3 != 0x500) goto LAB_80214140;
    }
    else if (uVar3 != 0x700) goto LAB_80214140;
  }
  *(char *)(param_2 + 2) = (char)((uint)param_3[1] >> 0x18);
  *(char *)((int)param_2 + 5) = (char)((uint)param_3[1] >> 0x10);
  *(byte *)(param_2 + 3) = (byte)((uint)param_3[1] >> 8) & 0xf0;
  *(byte *)((int)param_2 + 7) = (byte)((uint)param_3[1] >> 4) & 0xf0;
  *(byte *)(param_2 + 4) = (byte)param_3[1] & 0xf0;
  *(char *)((int)param_2 + 9) = (char)(param_3[1] << 4);
LAB_80214140:
  iVar4 = param_1 * 0xc;
  *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + -0x80;
  *(char *)((int)param_2 + 3) = *(char *)((int)param_2 + 3) + -0x80;
  *(char *)(param_2 + 2) = *(char *)(param_2 + 2) + -0x80;
  *(char *)((int)param_2 + 5) = *(char *)((int)param_2 + 5) + -0x80;
  cVar1 = (&DAT_803d7cc2)[iVar4];
  cVar6 = *(char *)(param_2 + 1);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar6)) {
      cVar6 = cVar1 + '\x7f';
    }
  }
  else if (cVar6 < (char)(cVar1 + -0x80)) {
    cVar6 = cVar1 + -0x80;
  }
  *(char *)(param_2 + 1) = cVar6 - cVar1;
  cVar1 = (&DAT_803d7cc3)[iVar4];
  cVar6 = *(char *)((int)param_2 + 3);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar6)) {
      cVar6 = cVar1 + '\x7f';
    }
  }
  else if (cVar6 < (char)(cVar1 + -0x80)) {
    cVar6 = cVar1 + -0x80;
  }
  *(char *)((int)param_2 + 3) = cVar6 - cVar1;
  cVar1 = (&DAT_803d7cc4)[iVar4];
  cVar6 = *(char *)(param_2 + 2);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar6)) {
      cVar6 = cVar1 + '\x7f';
    }
  }
  else if (cVar6 < (char)(cVar1 + -0x80)) {
    cVar6 = cVar1 + -0x80;
  }
  *(char *)(param_2 + 2) = cVar6 - cVar1;
  cVar1 = (&DAT_803d7cc5)[iVar4];
  cVar6 = *(char *)((int)param_2 + 5);
  if (cVar1 < '\x01') {
    if ((cVar1 < '\0') && ((char)(cVar1 + '\x7f') < cVar6)) {
      cVar6 = cVar1 + '\x7f';
    }
  }
  else if (cVar6 < (char)(cVar1 + -0x80)) {
    cVar6 = cVar1 + -0x80;
  }
  *(char *)((int)param_2 + 5) = cVar6 - cVar1;
  bVar2 = (&DAT_803d7cc6)[iVar4];
  bVar5 = *(byte *)(param_2 + 3);
  if (*(byte *)(param_2 + 3) < bVar2) {
    bVar5 = bVar2;
  }
  *(byte *)(param_2 + 3) = bVar5 - bVar2;
  bVar2 = (&DAT_803d7cc7)[iVar4];
  bVar5 = *(byte *)((int)param_2 + 7);
  if (*(byte *)((int)param_2 + 7) < bVar2) {
    bVar5 = bVar2;
  }
  *(byte *)((int)param_2 + 7) = bVar5 - bVar2;
  return;
}



// ==== 8021432c  zz_021432c_ ====

int zz_021432c_(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  if (DAT_8043661c != 0) {
    gnt4_PADSetSamplingCallback_bl(0);
  }
  if (param_1 == 0) {
    iVar4 = 0;
    bVar1 = false;
    if ((DAT_80436608 == 0) && (DAT_80435cfc == 0x20)) {
      bVar1 = true;
    }
    if ((bVar1) && (iVar2 = zz_02094a8_(), iVar2 == 0)) {
      iVar4 = 1;
    }
    if ((DAT_80436620 == 0) && (iVar4 != 0)) {
      gnt4_OSDisableInterrupts_bl();
      uVar5 = (DAT_80436618 | 0xf0000000) & ~(DAT_80436610 | DAT_80436614);
      DAT_80436608 = DAT_80436608 | uVar5;
      DAT_80436618 = 0;
      uVar3 = DAT_80436608 & DAT_80436604;
      if ((DAT_800030e3 & 0x40) == 0) {
        DAT_8043660c = DAT_8043660c | uVar5;
      }
      DAT_80436604 = DAT_80436604 & ~uVar5;
      gnt4_SIDisablePolling(uVar3);
      if ((DAT_80435cfc == 0x20) &&
         (DAT_80435cfc = countLeadingZeros(DAT_80436608), DAT_80435cfc != 0x20)) {
        DAT_80436608 = DAT_80436608 & ~(0x80000000U >> DAT_80435cfc);
        gnt4_memset(&DAT_803d7cc0 + DAT_80435cfc * 0xc,0,0xc);
        gnt4_SIGetTypeAsync(DAT_80435cfc,gnt4_PADTypeAndStatusCallback_bl);
      }
      gnt4_OSRestoreInterrupts_bl();
      DAT_80436620 = 1;
      iVar4 = 0;
    }
  }
  else {
    DAT_80436620 = 0;
    iVar4 = 1;
  }
  return iVar4;
}



// ==== 802144c0  gnt4-SamplingHandler-bl ====

void gnt4_SamplingHandler_bl(undefined4 param_1,uint param_2)

{
  undefined1 auStack_2d0 [716];
  
  if (DAT_8043661c != (code *)0x0) {
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
    (*DAT_8043661c)();
    gnt4_OSClearContext_bl((int)auStack_2d0);
    gnt4_OSSetCurrentContext_bl(param_2);
  }
  return;
}



// ==== 80214520  gnt4-PADSetSamplingCallback-bl ====

undefined4 gnt4_PADSetSamplingCallback_bl(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8043661c;
  DAT_8043661c = param_1;
  if (param_1 == 0) {
    gnt4_SIUnregisterPollingHandler(-0x7fdebb40);
  }
  else {
    gnt4_SIRegisterPollingHandler_bl(-0x7fdebb40);
  }
  return uVar1;
}



// ==== 80214574  gnt4-__PADDisableRecalibration-bl ====

bool gnt4___PADDisableRecalibration_bl(int param_1)

{
  byte bVar1;
  
  gnt4_OSDisableInterrupts_bl();
  bVar1 = DAT_800030e3 & 0x40;
  DAT_800030e3 = DAT_800030e3 & 0xbf;
  if (param_1 != 0) {
    DAT_800030e3 = DAT_800030e3 | 0x40;
  }
  gnt4_OSRestoreInterrupts_bl();
  return bVar1 != 0;
}



// ==== 802145f0  zz_02145f0_ ====

undefined4 zz_02145f0_(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_8043662c;
  gnt4_OSDisableInterrupts_bl();
  DAT_8043662c = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80214634  AIInitDMA ====

void AIInitDMA(undefined4 param_1,uint param_2)

{
  ushort uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_cc005030;
  DAT_cc005030 = uVar1 & 0xfc00 | (ushort)((uint)param_1 >> 0x10);
  uVar1 = DAT_cc005032;
  DAT_cc005032 = uVar1 & 0x1f | (ushort)param_1;
  uVar1 = DAT_cc005036;
  DAT_cc005036 = uVar1 & 0x8000 | (ushort)(param_2 >> 5);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802146bc  AIStartDMA ====

void AIStartDMA(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005036;
  DAT_cc005036 = uVar1 | 0x8000;
  return;
}



// ==== 802146d4  AISetStreamPlayState ====

void AISetStreamPlayState(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = zz_02147ac_();
  if (param_1 != uVar1) {
    uVar1 = zz_0214984_();
    if ((uVar1 == 0) && (param_1 == 1)) {
      uVar2 = zz_02149dc_();
      uVar3 = AIGetStreamPlayState();
      AISetStreamVolLeft(0);
      zz_0214994_(0);
      gnt4_OSDisableInterrupts_bl();
      __AI_SRC_INIT();
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xfffffffe | 1;
      gnt4_OSRestoreInterrupts_bl();
      zz_0214994_(uVar2);
      AISetStreamVolLeft(uVar3);
    }
    else {
      uVar1 = DAT_cc006c00;
      DAT_cc006c00 = uVar1 & 0xfffffffe | param_1;
    }
  }
  return;
}



// ==== 802147ac  zz_02147ac_ ====

uint zz_02147ac_(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 & 1;
}



// ==== 802147bc  AISetDSPSampleRate ====

void AISetDSPSampleRate(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = AIGetDSPSampleRate();
  if ((param_1 != uVar2) && (uVar2 = DAT_cc006c00, DAT_cc006c00 = uVar2 & 0xffffffbf, param_1 == 0))
  {
    uVar3 = AIGetStreamPlayState();
    uVar4 = zz_02149dc_();
    uVar2 = DAT_cc006c00;
    uVar5 = zz_0214984_();
    zz_0214994_(0);
    AISetStreamVolLeft(0);
    gnt4_OSDisableInterrupts_bl();
    __AI_SRC_INIT();
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 & 0xfffffffd | uVar5 << 1;
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 & 0xfffffffe | uVar2 & 1;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 | 0x40;
    gnt4_OSRestoreInterrupts_bl();
    zz_0214994_(uVar3);
    AISetStreamVolLeft(uVar4);
  }
  return;
}



// ==== 8021489c  AIGetDSPSampleRate ====

uint AIGetDSPSampleRate(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 >> 6 & 1 ^ 1;
}



// ==== 802148b0  __AI_set_stream_sample_rate ====

void __AI_set_stream_sample_rate(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar3 = zz_0214984_();
  if (param_1 != uVar3) {
    uVar3 = DAT_cc006c00;
    uVar4 = AIGetStreamPlayState();
    uVar5 = zz_02149dc_();
    AISetStreamVolLeft(0);
    zz_0214994_(0);
    uVar1 = DAT_cc006c00;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xffffffbf;
    gnt4_OSDisableInterrupts_bl();
    __AI_SRC_INIT();
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 | uVar1 & 0x40;
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
    uVar1 = DAT_cc006c00;
    DAT_cc006c00 = uVar1 & 0xfffffffd | param_1 << 1;
    gnt4_OSRestoreInterrupts_bl();
    AISetStreamPlayState(uVar3 & 1);
    zz_0214994_(uVar4);
    AISetStreamVolLeft(uVar5);
  }
  return;
}



// ==== 80214984  zz_0214984_ ====

uint zz_0214984_(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c00;
  return uVar1 >> 1 & 1;
}



// ==== 80214994  zz_0214994_ ====

void zz_0214994_(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  DAT_cc006c04 = param_1 & 0xff | uVar1 & 0xffffff00;
  return;
}



// ==== 802149b0  AIGetStreamPlayState ====

uint AIGetStreamPlayState(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  return uVar1 & 0xff;
}



// ==== 802149c0  AISetStreamVolLeft ====

void AISetStreamVolLeft(uint param_1)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  DAT_cc006c04 = (param_1 & 0xff) << 8 | uVar1 & 0xffff00ff;
  return;
}



// ==== 802149dc  zz_02149dc_ ====

uint zz_02149dc_(void)

{
  uint uVar1;
  
  uVar1 = DAT_cc006c04;
  return uVar1 >> 8 & 0xff;
}



// ==== 802149ec  AIInit ====

void AIInit(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
           undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint uVar2;
  
  if (DAT_80436638 != 1) {
    gnt4_OSRegisterVersion_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d18,param_10
               ,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar1 = DAT_800000f8 / 500000;
    DAT_80436644 = (uVar1 * 0x7b24) / 8000;
    DAT_8043664c = (uVar1 * 0xa428) / 8000;
    DAT_80436654 = (uVar1 * 42000) / 8000;
    DAT_8043665c = (uVar1 * 63000) / 8000;
    DAT_80436664 = (uVar1 * 3000) / 8000;
    uVar1 = DAT_cc006c00;
    DAT_80436640 = 0;
    DAT_80436648 = 0;
    DAT_80436650 = 0;
    DAT_80436658 = 0;
    DAT_80436660 = 0;
    uVar2 = DAT_cc006c04;
    DAT_cc006c00 = uVar1 & 0xffffffdf | 0x20;
    DAT_cc006c04 = uVar2 & 0xffff00ff;
    uVar1 = DAT_cc006c04;
    DAT_cc006c04 = uVar1 & 0xffffff00;
    DAT_cc006c0c = 0;
    __AI_set_stream_sample_rate(1);
    AISetDSPSampleRate(0);
    DAT_80436628 = 0;
    DAT_8043662c = 0;
    DAT_80436630 = param_9;
    gnt4___OSSetInterruptHandler_bl(5,FUN_80214bd4);
    gnt4___OSUnmaskInterrupts_bl(0x4000000);
    gnt4___OSSetInterruptHandler_bl(8,FUN_80214b58);
    gnt4___OSUnmaskInterrupts_bl(0x800000);
    DAT_80436638 = 1;
  }
  return;
}



// ==== 80214b58  FUN_80214b58 ====

void FUN_80214b58(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 auStack_2d0 [712];
  
  uVar1 = DAT_cc006c00;
  DAT_cc006c00 = uVar1 | 8;
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
  if (DAT_80436628 != (code *)0x0) {
    uVar2 = DAT_cc006c08;
    (*DAT_80436628)(uVar2);
  }
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl(param_2);
  return;
}



// ==== 80214bd4  FUN_80214bd4 ====

void FUN_80214bd4(undefined4 param_1,uint param_2)

{
  ushort uVar1;
  undefined1 auStack_2d0 [716];
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff5f | 8;
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
  if ((DAT_8043662c != (code *)0x0) && (DAT_8043663c == 0)) {
    DAT_8043663c = 1;
    if (DAT_80436630 == 0) {
      (*DAT_8043662c)();
    }
    else {
      __AICallbackStackSwitch(DAT_8043662c);
    }
    DAT_8043663c = 0;
  }
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl(param_2);
  return;
}



// ==== 80214c80  __AICallbackStackSwitch ====

void __AICallbackStackSwitch(undefined *param_1)

{
  DAT_80436634 = &stack0xffffffe8;
  (*(code *)param_1)();
  return;
}



// ==== 80214cd8  __AI_SRC_INIT ====

void __AI_SRC_INIT(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  
  lVar9 = 0;
  bVar1 = false;
  uVar7 = 0;
  uVar8 = 0;
  while (!bVar1) {
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xffffffdf | 0x20;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffd;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffe | 1;
    iVar3 = DAT_cc006c08;
    do {
      iVar4 = DAT_cc006c08;
    } while (iVar3 == iVar4);
    uVar10 = gnt4_OSGetTime_bl();
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffd | 2;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffe | 1;
    iVar3 = DAT_cc006c08;
    do {
      iVar4 = DAT_cc006c08;
    } while (iVar3 == iVar4);
    lVar9 = gnt4_OSGetTime_bl();
    uVar6 = (uint)lVar9 - (uint)uVar10;
    uVar2 = DAT_cc006c00;
    uVar5 = (int)((ulonglong)lVar9 >> 0x20) -
            ((uint)((uint)lVar9 < (uint)uVar10) + (int)((ulonglong)uVar10 >> 0x20)) ^ 0x80000000;
    DAT_cc006c00 = uVar2 & 0xfffffffd;
    uVar2 = DAT_cc006c00;
    DAT_cc006c00 = uVar2 & 0xfffffffe;
    if (uVar5 < (uint)(uVar6 < DAT_80436644 - DAT_80436664) +
                (DAT_80436640 - ((uint)(DAT_80436644 < DAT_80436664) + DAT_80436660) ^ 0x80000000))
    {
      bVar1 = true;
      uVar7 = DAT_80436654;
      uVar8 = DAT_80436650;
    }
    else if ((uVar5 < (uint)(uVar6 < DAT_80436644 + DAT_80436664) +
                      (DAT_80436640 + DAT_80436660 + (uint)CARRY4(DAT_80436644,DAT_80436664) ^
                      0x80000000)) ||
            ((uint)(uVar6 < DAT_8043664c - DAT_80436664) +
             (DAT_80436648 - ((uint)(DAT_8043664c < DAT_80436664) + DAT_80436660) ^ 0x80000000) <=
             uVar5)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
      uVar7 = DAT_8043665c;
      uVar8 = DAT_80436658;
    }
  }
  lVar9 = lVar9 + CONCAT44(uVar8,uVar7);
  do {
    uVar10 = gnt4_OSGetTime_bl();
  } while (((uint)((ulonglong)uVar10 >> 0x20) ^ 0x80000000) <
           (uint)((uint)uVar10 < (uint)lVar9) + ((uint)((ulonglong)lVar9 >> 0x20) ^ 0x80000000));
  return;
}



// ==== 80214ebc  gnt4-ARRegisterDMACallback ====

undefined4 gnt4_ARRegisterDMACallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80436668;
  gnt4_OSDisableInterrupts_bl();
  DAT_80436668 = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80214f00  gnt4-ARStartDMA ====

void gnt4_ARStartDMA(short param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  uVar1 = DAT_cc005020._0_2_;
  DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)param_2 >> 0x10);
  uVar1 = DAT_cc005020._2_2_;
  DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)param_2;
  uVar1 = DAT_cc005024._0_2_;
  DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)param_3 >> 0x10);
  uVar1 = DAT_cc005024._2_2_;
  DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)param_3;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = param_1 << 0xf | uVar1 & 0x7fff;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)param_4 >> 0x10);
  uVar1 = DAT_cc005028._2_2_;
  DAT_cc005028._2_2_ = uVar1 & 0x1f | (ushort)param_4;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80214ff0  ARAlloc ====

int ARAlloc(int param_1)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_80436678;
  DAT_80436678 = DAT_80436678 + param_1;
  *DAT_80436680 = param_1;
  DAT_80436680 = DAT_80436680 + 1;
  DAT_8043667c = DAT_8043667c + -1;
  gnt4_OSRestoreInterrupts_bl();
  return iVar1;
}



// ==== 80215058  ARFree ====

int ARFree(int *param_1)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_80436680 = (int *)((int)DAT_80436680 + -4);
  if (param_1 != (int *)0x0) {
    *param_1 = *DAT_80436680;
  }
  DAT_8043667c = DAT_8043667c + 1;
  DAT_80436678 = DAT_80436678 - *DAT_80436680;
  gnt4_OSRestoreInterrupts_bl();
  return DAT_80436678;
}



// ==== 802150cc  ARInit ====

undefined4
ARInit(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
      undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,undefined4 param_9
      ,undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
      undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  
  if (DAT_80436684 == 1) {
    uVar3 = 0x4000;
  }
  else {
    gnt4_OSRegisterVersion_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d20,param_10
               ,param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_OSDisableInterrupts_bl();
    DAT_80436668 = 0;
    gnt4___OSSetInterruptHandler_bl(6,FUN_80215190);
    gnt4___OSUnmaskInterrupts_bl(0x2000000);
    DAT_80436678 = 0x4000;
    uVar1 = DAT_cc00501a;
    uVar2 = DAT_cc00501a;
    DAT_cc00501a = uVar2 & 0xff | uVar1 & 0xff00;
    DAT_8043667c = param_10;
    DAT_80436680 = param_9;
    __ARChecksize();
    DAT_80436684 = 1;
    gnt4_OSRestoreInterrupts_bl();
    uVar3 = DAT_80436678;
  }
  return uVar3;
}



// ==== 80215190  FUN_80215190 ====

void FUN_80215190(undefined4 param_1,uint param_2)

{
  ushort uVar1;
  undefined1 auStack_2d0 [716];
  
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
  if (DAT_80436668 != (code *)0x0) {
    (*DAT_80436668)();
  }
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl(param_2);
  return;
}



// ==== 80215208  __ARChecksize ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __ARChecksize(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  undefined1 auStack_2a0 [64];
  undefined1 auStack_260 [64];
  undefined1 auStack_220 [64];
  undefined1 auStack_1e0 [19];
  undefined1 auStack_1cd [45];
  undefined1 auStack_1a0 [19];
  undefined1 auStack_18d [45];
  int aiStack_160 [4];
  undefined1 auStack_14d [45];
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  int aiStack_e0 [4];
  undefined4 uStack_d0;
  undefined1 uStack_cd;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 *local_ac;
  undefined1 *local_a8;
  undefined1 *local_a4;
  uint local_a0;
  uint local_9c;
  undefined4 local_98;
  uint local_94;
  undefined4 local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  ushort *local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  undefined4 local_5c;
  uint local_58;
  undefined4 local_54;
  ushort local_50;
  
  do {
    uVar1 = DAT_cc005016;
  } while ((uVar1 & 1) == 0);
  DAT_80436670 = 0x1000000;
  uVar1 = DAT_cc005012;
  local_a4 = auStack_220;
  DAT_cc005012 = uVar1 & 0xffc0 | 0x23;
  aiStack_e0[0] = -0x21524111;
  uStack_120 = 0xbad0bad0;
  aiStack_e0[1] = 0xdeadbeef;
  local_ac = auStack_2a0;
  local_a8 = auStack_260;
  uStack_11c = 0xbad0bad0;
  aiStack_e0[2] = 0xdeadbeef;
  uVar3 = 0x1000000;
  uStack_118 = 0xbad0bad0;
  aiStack_e0[3] = 0xdeadbeef;
  uStack_114 = 0xbad0bad0;
  uStack_d0 = 0xdeadbeef;
  uStack_110 = 0xbad0bad0;
  uStack_cc = 0xdeadbeef;
  uStack_10c = 0xbad0bad0;
  uStack_c8 = 0xdeadbeef;
  uStack_108 = 0xbad0bad0;
  uStack_c4 = 0xdeadbeef;
  local_78 = &DAT_cc005012;
  local_50 = 3;
  uStack_104 = 0xbad0bad0;
  gnt4_DCFlushRange_bl((uint)aiStack_e0,0x20);
  gnt4_DCFlushRange_bl((uint)&uStack_120,0x20);
  DAT_80436674 = 0;
  gnt4_DCInvalidateRange_bl((uint)auStack_1a0,0x20);
  local_84 = (uint)auStack_18d >> 0x10;
  uVar1 = DAT_cc005020._0_2_;
  DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)auStack_18d >> 0x10);
  local_74 = (uint)auStack_1a0 & 0xffff;
  uVar1 = DAT_cc005020._2_2_;
  DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)auStack_1a0;
  uVar1 = DAT_cc005024._0_2_;
  DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
  uVar1 = DAT_cc005024._2_2_;
  DAT_cc005024._2_2_ = uVar1 & 0x1f;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 | 0x8000;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0xfc00;
  uVar1 = DAT_cc005028._2_2_;
  DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 0x200) != 0);
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  gnt4_PPCSync();
  local_7c = (uint)&uStack_cd >> 0x10;
  uVar1 = DAT_cc005020._0_2_;
  DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)&uStack_cd >> 0x10);
  local_70 = (uint)aiStack_e0 & 0xffff;
  uVar1 = DAT_cc005020._2_2_;
  DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)aiStack_e0;
  uVar1 = DAT_cc005024._0_2_;
  DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
  uVar1 = DAT_cc005024._2_2_;
  DAT_cc005024._2_2_ = uVar1 & 0x1f;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0x7fff;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0xfc00;
  uVar1 = DAT_cc005028._2_2_;
  DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 0x200) != 0);
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  gnt4_memset(aiStack_160,0,0x20);
  gnt4_DCFlushRange_bl((uint)aiStack_160,0x20);
  local_80 = (uint)auStack_14d >> 0x10;
  uVar1 = DAT_cc005020._0_2_;
  DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)auStack_14d >> 0x10);
  local_6c = (uint)aiStack_160 & 0xffff;
  uVar1 = DAT_cc005020._2_2_;
  DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)aiStack_160;
  uVar1 = DAT_cc005024._0_2_;
  DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
  uVar1 = DAT_cc005024._2_2_;
  DAT_cc005024._2_2_ = uVar1 & 0x1f;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 | 0x8000;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0xfc00;
  uVar1 = DAT_cc005028._2_2_;
  DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
  do {
    uVar1 = DAT_cc00500a;
  } while ((uVar1 & 0x200) != 0);
  uVar1 = DAT_cc00500a;
  DAT_cc00500a = uVar1 & 0xff77 | 0x20;
  gnt4_PPCSync();
  if (aiStack_160[0] == aiStack_e0[0]) {
    gnt4_DCInvalidateRange_bl((uint)auStack_1e0,0x20);
    local_8c = (uint)auStack_1cd >> 0x10;
    uVar1 = DAT_cc005020._0_2_;
    DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)auStack_1cd >> 0x10);
    local_68 = (uint)auStack_1e0 & 0xffff;
    uVar1 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)auStack_1e0;
    uVar1 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x120;
    uVar1 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar1 & 0x1f;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 | 0x8000;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 & 0xfc00;
    uVar1 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
    do {
      uVar1 = DAT_cc00500a;
    } while ((uVar1 & 0x200) != 0);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff77 | 0x20;
    gnt4_PPCSync();
    gnt4_DCInvalidateRange_bl((uint)local_a4,0x20);
    uVar1 = DAT_cc005020._0_2_;
    local_94 = (uint)local_a4 >> 0x10;
    DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)local_a4 >> 0x10);
    local_64 = (uint)local_a4 & 0xffff;
    uVar1 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_a4;
    uVar1 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x200;
    uVar1 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar1 & 0x1f;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 | 0x8000;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 & 0xfc00;
    uVar1 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
    do {
      uVar1 = DAT_cc00500a;
    } while ((uVar1 & 0x200) != 0);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff77 | 0x20;
    gnt4_PPCSync();
    gnt4_DCInvalidateRange_bl((uint)local_a8,0x20);
    uVar1 = DAT_cc005020._0_2_;
    local_9c = (uint)local_a8 >> 0x10;
    DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)local_a8 >> 0x10);
    local_90 = 0x100;
    local_5c = 0x200;
    local_60 = (uint)local_a8 & 0xffff;
    uVar1 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_a8;
    uVar1 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
    uVar1 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar1 & 0x1f | 0x200;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 | 0x8000;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 & 0xfc00;
    uVar1 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
    do {
      uVar1 = DAT_cc00500a;
    } while ((uVar1 & 0x200) != 0);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff77 | 0x20;
    gnt4_PPCSync();
    gnt4_DCInvalidateRange_bl((uint)local_ac,0x20);
    uVar1 = DAT_cc005020._0_2_;
    local_a0 = (uint)local_ac >> 0x10;
    DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)local_ac >> 0x10);
    local_98 = 0x140;
    local_54 = 0;
    local_58 = (uint)local_ac & 0xffff;
    uVar1 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_ac;
    uVar1 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x140;
    uVar1 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar1 & 0x1f;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 | 0x8000;
    uVar1 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar1 & 0xfc00;
    uVar1 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
    do {
      uVar1 = DAT_cc00500a;
    } while ((uVar1 & 0x200) != 0);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff77 | 0x20;
    gnt4_PPCSync();
    local_88 = (int)&uStack_110 + 3U >> 0x10;
    uVar2 = DAT_cc005020._0_2_;
    uVar1 = (ushort)&uStack_120;
    DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)((int)&uStack_110 + 3U >> 0x10);
    uVar2 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar2 & 0x1f | uVar1;
    uVar2 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x120;
    uVar2 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar2 & 0x1f;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 & 0x7fff;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 & 0xfc00;
    uVar2 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
    do {
      uVar2 = DAT_cc00500a;
    } while ((uVar2 & 0x200) != 0);
    uVar2 = DAT_cc00500a;
    DAT_cc00500a = uVar2 & 0xff77 | 0x20;
    uVar2 = DAT_cc005020._0_2_;
    DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_7c;
    uVar2 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_70;
    uVar2 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x100;
    uVar2 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar2 & 0x1f;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 & 0x7fff;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 & 0xfc00;
    uVar2 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
    do {
      uVar2 = DAT_cc00500a;
    } while ((uVar2 & 0x200) != 0);
    uVar2 = DAT_cc00500a;
    DAT_cc00500a = uVar2 & 0xff77 | 0x20;
    gnt4_memset(aiStack_160,0,0x20);
    gnt4_DCFlushRange_bl((uint)aiStack_160,0x20);
    uVar2 = DAT_cc005020._0_2_;
    DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_80;
    uVar2 = DAT_cc005020._2_2_;
    DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_6c;
    uVar2 = DAT_cc005024._0_2_;
    DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x120;
    uVar2 = DAT_cc005024._2_2_;
    DAT_cc005024._2_2_ = uVar2 & 0x1f;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 | 0x8000;
    uVar2 = DAT_cc005028._0_2_;
    DAT_cc005028._0_2_ = uVar2 & 0xfc00;
    uVar2 = DAT_cc005028._2_2_;
    DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
    do {
      uVar2 = DAT_cc00500a;
    } while ((uVar2 & 0x200) != 0);
    uVar2 = DAT_cc00500a;
    DAT_cc00500a = uVar2 & 0xff77 | 0x20;
    gnt4_PPCSync();
    if (aiStack_160[0] == aiStack_e0[0]) {
      uVar1 = DAT_cc005020._0_2_;
      DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_84;
      uVar1 = DAT_cc005020._2_2_;
      DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_74;
      uVar1 = DAT_cc005024._0_2_;
      DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
      uVar1 = DAT_cc005024._2_2_;
      DAT_cc005024._2_2_ = uVar1 & 0x1f;
      uVar1 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar1 & 0x7fff;
      uVar1 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar1 & 0xfc00;
      uVar1 = DAT_cc005028._2_2_;
      DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
      do {
        uVar1 = DAT_cc00500a;
      } while ((uVar1 & 0x200) != 0);
      uVar1 = DAT_cc00500a;
      DAT_cc00500a = uVar1 & 0xff77 | 0x20;
      uVar3 = 0x1200000;
      DAT_80436674 = 0x200000;
    }
    else {
      uVar2 = DAT_cc005020._0_2_;
      DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_88;
      uVar2 = DAT_cc005020._2_2_;
      DAT_cc005020._2_2_ = uVar2 & 0x1f | uVar1;
      uVar2 = DAT_cc005024._0_2_;
      DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x200;
      uVar2 = DAT_cc005024._2_2_;
      DAT_cc005024._2_2_ = uVar2 & 0x1f;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 & 0x7fff;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 & 0xfc00;
      uVar2 = DAT_cc005028._2_2_;
      DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
      do {
        uVar2 = DAT_cc00500a;
      } while ((uVar2 & 0x200) != 0);
      uVar2 = DAT_cc00500a;
      DAT_cc00500a = uVar2 & 0xff77 | 0x20;
      uVar2 = DAT_cc005020._0_2_;
      DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_7c;
      uVar2 = DAT_cc005020._2_2_;
      DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_70;
      uVar2 = DAT_cc005024._0_2_;
      DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x100;
      uVar2 = DAT_cc005024._2_2_;
      DAT_cc005024._2_2_ = uVar2 & 0x1f;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 & 0x7fff;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 & 0xfc00;
      uVar2 = DAT_cc005028._2_2_;
      DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
      do {
        uVar2 = DAT_cc00500a;
      } while ((uVar2 & 0x200) != 0);
      uVar2 = DAT_cc00500a;
      DAT_cc00500a = uVar2 & 0xff77 | 0x20;
      gnt4_memset(aiStack_160,0,0x20);
      gnt4_DCFlushRange_bl((uint)aiStack_160,0x20);
      uVar2 = DAT_cc005020._0_2_;
      DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_80;
      uVar2 = DAT_cc005020._2_2_;
      DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_6c;
      uVar2 = DAT_cc005024._0_2_;
      DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x200;
      uVar2 = DAT_cc005024._2_2_;
      DAT_cc005024._2_2_ = uVar2 & 0x1f;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 | 0x8000;
      uVar2 = DAT_cc005028._0_2_;
      DAT_cc005028._0_2_ = uVar2 & 0xfc00;
      uVar2 = DAT_cc005028._2_2_;
      DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
      do {
        uVar2 = DAT_cc00500a;
      } while ((uVar2 & 0x200) != 0);
      uVar2 = DAT_cc00500a;
      DAT_cc00500a = uVar2 & 0xff77 | 0x20;
      gnt4_PPCSync();
      if (aiStack_160[0] == aiStack_e0[0]) {
        uVar1 = DAT_cc005020._0_2_;
        DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_84;
        uVar1 = DAT_cc005020._2_2_;
        DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_74;
        uVar1 = DAT_cc005024._0_2_;
        DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
        uVar1 = DAT_cc005024._2_2_;
        DAT_cc005024._2_2_ = uVar1 & 0x1f;
        uVar1 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar1 & 0x7fff;
        uVar1 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar1 & 0xfc00;
        uVar1 = DAT_cc005028._2_2_;
        DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
        do {
          uVar1 = DAT_cc00500a;
        } while ((uVar1 & 0x200) != 0);
        uVar1 = DAT_cc00500a;
        DAT_cc00500a = uVar1 & 0xff77 | 0x20;
        uVar1 = DAT_cc005020._0_2_;
        DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_8c;
        uVar1 = DAT_cc005020._2_2_;
        DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_68;
        uVar1 = DAT_cc005024._0_2_;
        DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x120;
        uVar1 = DAT_cc005024._2_2_;
        DAT_cc005024._2_2_ = uVar1 & 0x1f;
        uVar1 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar1 & 0x7fff;
        uVar1 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar1 & 0xfc00;
        uVar1 = DAT_cc005028._2_2_;
        DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
        do {
          uVar1 = DAT_cc00500a;
        } while ((uVar1 & 0x200) != 0);
        uVar1 = DAT_cc00500a;
        DAT_cc00500a = uVar1 & 0xff77 | 0x20;
        uVar3 = 0x1400000;
        DAT_80436674 = 0x400000;
        local_50 = local_50 | 8;
      }
      else {
        uVar2 = DAT_cc005020._0_2_;
        DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_88;
        uVar2 = DAT_cc005020._2_2_;
        DAT_cc005020._2_2_ = uVar2 & 0x1f | uVar1;
        uVar2 = DAT_cc005024._0_2_;
        DAT_cc005024._0_2_ = uVar2 & 0xfc00 | (ushort)local_90;
        uVar2 = DAT_cc005024._2_2_;
        DAT_cc005024._2_2_ = uVar2 & 0x1f | (ushort)local_5c;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 & 0x7fff;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 & 0xfc00;
        uVar2 = DAT_cc005028._2_2_;
        DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
        do {
          uVar2 = DAT_cc00500a;
        } while ((uVar2 & 0x200) != 0);
        uVar2 = DAT_cc00500a;
        DAT_cc00500a = uVar2 & 0xff77 | 0x20;
        uVar2 = DAT_cc005020._0_2_;
        DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_7c;
        uVar2 = DAT_cc005020._2_2_;
        DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_70;
        uVar2 = DAT_cc005024._0_2_;
        DAT_cc005024._0_2_ = uVar2 & 0xfc00 | 0x100;
        uVar2 = DAT_cc005024._2_2_;
        DAT_cc005024._2_2_ = uVar2 & 0x1f;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 & 0x7fff;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 & 0xfc00;
        uVar2 = DAT_cc005028._2_2_;
        DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
        do {
          uVar2 = DAT_cc00500a;
        } while ((uVar2 & 0x200) != 0);
        uVar2 = DAT_cc00500a;
        DAT_cc00500a = uVar2 & 0xff77 | 0x20;
        gnt4_memset(aiStack_160,0,0x20);
        gnt4_DCFlushRange_bl((uint)aiStack_160,0x20);
        uVar2 = DAT_cc005020._0_2_;
        DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_80;
        uVar2 = DAT_cc005020._2_2_;
        DAT_cc005020._2_2_ = uVar2 & 0x1f | (ushort)local_6c;
        uVar2 = DAT_cc005024._0_2_;
        DAT_cc005024._0_2_ = uVar2 & 0xfc00 | (ushort)local_90;
        uVar2 = DAT_cc005024._2_2_;
        DAT_cc005024._2_2_ = uVar2 & 0x1f | (ushort)local_5c;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 | 0x8000;
        uVar2 = DAT_cc005028._0_2_;
        DAT_cc005028._0_2_ = uVar2 & 0xfc00;
        uVar2 = DAT_cc005028._2_2_;
        DAT_cc005028._2_2_ = uVar2 & 0x1f | 0x20;
        do {
          uVar2 = DAT_cc00500a;
        } while ((uVar2 & 0x200) != 0);
        uVar2 = DAT_cc00500a;
        DAT_cc00500a = uVar2 & 0xff77 | 0x20;
        gnt4_PPCSync();
        if (aiStack_160[0] == aiStack_e0[0]) {
          uVar1 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_84;
          uVar1 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_74;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0x7fff;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          uVar1 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_8c;
          uVar1 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_68;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x120;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0x7fff;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          uVar1 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_94;
          uVar1 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_64;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x200;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0x7fff;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          uVar3 = 0x1800000;
          DAT_80436674 = 0x800000;
          local_50 = local_50 | 0x10;
        }
        else {
          uVar2 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar2 & 0xfc00 | (ushort)local_88;
          uVar2 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar2 & 0x1f | uVar1;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)local_98;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)local_54;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0x7fff;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          uVar1 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_7c;
          uVar1 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_70;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0x7fff;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          gnt4_memset(aiStack_160,0,0x20);
          gnt4_DCFlushRange_bl((uint)aiStack_160,0x20);
          uVar1 = DAT_cc005020._0_2_;
          DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_80;
          uVar1 = DAT_cc005020._2_2_;
          DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_6c;
          uVar1 = DAT_cc005024._0_2_;
          DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)local_98;
          uVar1 = DAT_cc005024._2_2_;
          DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)local_54;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 | 0x8000;
          uVar1 = DAT_cc005028._0_2_;
          DAT_cc005028._0_2_ = uVar1 & 0xfc00;
          uVar1 = DAT_cc005028._2_2_;
          DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
          do {
            uVar1 = DAT_cc00500a;
          } while ((uVar1 & 0x200) != 0);
          uVar1 = DAT_cc00500a;
          DAT_cc00500a = uVar1 & 0xff77 | 0x20;
          gnt4_PPCSync();
          if (aiStack_160[0] == aiStack_e0[0]) {
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_84;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_74;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_8c;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_68;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x120;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_94;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_64;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x200;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_9c;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_60;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)local_90;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)local_5c;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar3 = 0x2000000;
            DAT_80436674 = 0x1000000;
            local_50 = local_50 | 0x18;
          }
          else {
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_84;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_74;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x100;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_8c;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_68;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x120;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_94;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_64;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | 0x200;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_9c;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_60;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)local_90;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)local_5c;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar1 = DAT_cc005020._0_2_;
            DAT_cc005020._0_2_ = uVar1 & 0xfc00 | (ushort)local_a0;
            uVar1 = DAT_cc005020._2_2_;
            DAT_cc005020._2_2_ = uVar1 & 0x1f | (ushort)local_58;
            uVar1 = DAT_cc005024._0_2_;
            DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)local_98;
            uVar1 = DAT_cc005024._2_2_;
            DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)local_54;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0x7fff;
            uVar1 = DAT_cc005028._0_2_;
            DAT_cc005028._0_2_ = uVar1 & 0xfc00;
            uVar1 = DAT_cc005028._2_2_;
            DAT_cc005028._2_2_ = uVar1 & 0x1f | 0x20;
            do {
              uVar1 = DAT_cc00500a;
            } while ((uVar1 & 0x200) != 0);
            uVar1 = DAT_cc00500a;
            DAT_cc00500a = uVar1 & 0xff77 | 0x20;
            uVar3 = 0x3000000;
            DAT_80436674 = 0x2000000;
            local_50 = local_50 | 0x20;
          }
        }
      }
    }
    *local_78 = *local_78 & 0xffc0 | local_50;
  }
  _DAT_c00000d0 = uVar3;
  DAT_8043666c = uVar3;
  return;
}



// ==== 802169fc  gnt4-__ARQServiceQueueLo-bl ====

void gnt4___ARQServiceQueueLo_bl(void)

{
  uint uVar1;
  
  if ((DAT_8043669c == (int *)0x0) && (DAT_80436690 != (int *)0x0)) {
    DAT_8043669c = DAT_80436690;
    DAT_80436690 = (int *)*DAT_80436690;
  }
  if (DAT_8043669c != (int *)0x0) {
    uVar1 = DAT_8043669c[6];
    if (DAT_804366a8 < uVar1) {
      if (DAT_8043669c[2] == 0) {
        gnt4_ARStartDMA(0,DAT_8043669c[4],DAT_8043669c[5],DAT_804366a8);
      }
      else {
        gnt4_ARStartDMA((short)DAT_8043669c[2],DAT_8043669c[5],DAT_8043669c[4],DAT_804366a8);
      }
    }
    else {
      if (DAT_8043669c[2] == 0) {
        gnt4_ARStartDMA(0,DAT_8043669c[4],DAT_8043669c[5],uVar1);
      }
      else {
        gnt4_ARStartDMA((short)DAT_8043669c[2],DAT_8043669c[5],DAT_8043669c[4],uVar1);
      }
      DAT_804366a4 = DAT_8043669c[7];
    }
    DAT_8043669c[6] = DAT_8043669c[6] - DAT_804366a8;
    DAT_8043669c[4] = DAT_8043669c[4] + DAT_804366a8;
    DAT_8043669c[5] = DAT_8043669c[5] + DAT_804366a8;
  }
  return;
}



// ==== 80216afc  gnt4-__ARQCallbackHack-bl ====

void gnt4___ARQCallbackHack_bl(void)

{
  return;
}



// ==== 80216b00  gnt4-__ARQInterruptServiceRoutine-bl ====

void gnt4___ARQInterruptServiceRoutine_bl(void)

{
  if (DAT_804366a0 == (code *)0x0) {
    if (DAT_804366a4 != (code *)0x0) {
      (*DAT_804366a4)(DAT_8043669c);
      DAT_8043669c = 0;
      DAT_804366a4 = (code *)0x0;
    }
  }
  else {
    (*DAT_804366a0)(DAT_80436698);
    DAT_80436698 = (int *)0x0;
    DAT_804366a0 = (code *)0x0;
  }
  if (DAT_80436688 != (int *)0x0) {
    if (DAT_80436688[2] == 0) {
      gnt4_ARStartDMA(0,DAT_80436688[4],DAT_80436688[5],DAT_80436688[6]);
    }
    else {
      gnt4_ARStartDMA((short)DAT_80436688[2],DAT_80436688[5],DAT_80436688[4],DAT_80436688[6]);
    }
    DAT_804366a0 = (code *)DAT_80436688[7];
    DAT_80436698 = DAT_80436688;
    DAT_80436688 = (int *)*DAT_80436688;
  }
  if (DAT_80436698 == (int *)0x0) {
    gnt4___ARQServiceQueueLo_bl();
  }
  return;
}



// ==== 80216bcc  gnt4-ARQInit-bl ====

void gnt4_ARQInit_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                    undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                    undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (DAT_804366ac != 1) {
    gnt4_OSRegisterVersion_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d28,param_10
               ,param_11,param_12,param_13,param_14,param_15,param_16);
    DAT_80436690 = 0;
    DAT_80436688 = 0;
    DAT_804366a8 = 0x1000;
    gnt4_ARRegisterDMACallback(gnt4___ARQInterruptServiceRoutine_bl);
    DAT_80436698 = 0;
    DAT_8043669c = 0;
    DAT_804366a0 = 0;
    DAT_804366a4 = 0;
    DAT_804366ac = 1;
  }
  return;
}



// ==== 80216c3c  gnt4-ARQPostRequest-bl ====

void gnt4_ARQPostRequest_bl
               (undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,int param_8)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  *param_1 = 0;
  param_1[1] = param_2;
  param_1[2] = param_3;
  param_1[4] = param_5;
  param_1[5] = param_6;
  param_1[6] = param_7;
  if (param_8 == 0) {
    param_1[7] = gnt4___ARQCallbackHack_bl;
  }
  else {
    param_1[7] = param_8;
  }
  gnt4_OSDisableInterrupts_bl();
  puVar3 = DAT_80436690;
  puVar4 = DAT_80436694;
  if (param_4 == 1) {
    piVar1 = param_1;
    puVar2 = param_1;
    if (DAT_80436688 != (int *)0x0) {
      *DAT_8043668c = param_1;
      piVar1 = DAT_80436688;
      puVar2 = param_1;
      puVar3 = DAT_80436690;
      puVar4 = DAT_80436694;
    }
  }
  else {
    piVar1 = DAT_80436688;
    puVar2 = DAT_8043668c;
    if (((param_4 < 1) && (-1 < param_4)) &&
       (puVar3 = param_1, puVar4 = param_1, DAT_80436690 != (undefined4 *)0x0)) {
      *DAT_80436694 = param_1;
      piVar1 = DAT_80436688;
      puVar2 = DAT_8043668c;
      puVar3 = DAT_80436690;
      puVar4 = param_1;
    }
  }
  DAT_80436694 = puVar4;
  DAT_80436690 = puVar3;
  DAT_8043668c = puVar2;
  DAT_80436688 = piVar1;
  if ((DAT_80436698 == (int *)0x0) && (DAT_8043669c == 0)) {
    if (DAT_80436688 != (int *)0x0) {
      if (DAT_80436688[2] == 0) {
        gnt4_ARStartDMA(0,DAT_80436688[4],DAT_80436688[5],DAT_80436688[6]);
      }
      else {
        gnt4_ARStartDMA((short)DAT_80436688[2],DAT_80436688[5],DAT_80436688[4],DAT_80436688[6]);
      }
      DAT_804366a0 = DAT_80436688[7];
      DAT_80436698 = DAT_80436688;
      DAT_80436688 = (int *)*DAT_80436688;
    }
    if (DAT_80436698 == (int *)0x0) {
      gnt4___ARQServiceQueueLo_bl();
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80216d98  zz_0216d98_ ====

void zz_0216d98_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_0216dbc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,param_10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80216dbc  zz_0216dbc_ ====

void zz_0216dbc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  gnt4_OSRegisterVersion_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d30,param_10,
             param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0216e94_();
  zz_021942c_();
  zz_0218954_();
  zz_021721c_();
  uVar1 = zz_0217da0_();
  zz_02181a8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80216e08  zz_0216e08_ ====

undefined4 zz_0216e08_(int param_1)

{
  return (&DAT_803d7d00)[param_1];
}



// ==== 80216e20  zz_0216e20_ ====

void zz_0216e20_(void)

{
  int *piVar1;
  
  piVar1 = (int *)zz_0216f78_();
  while (piVar1 != (int *)0x0) {
    if (piVar1[3] != 0) {
      if ((code *)piVar1[4] != (code *)0x0) {
        (*(code *)piVar1[4])(piVar1);
      }
      zz_0216f94_(piVar1);
      zz_0216f48_(piVar1);
    }
    piVar1 = (int *)zz_0216f78_();
  }
  return;
}



// ==== 80216e94  zz_0216e94_ ====

void zz_0216e94_(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  DAT_804366b0 = 0;
  iVar3 = 2;
  puVar2 = &DAT_803d7d80;
  puVar1 = &DAT_803d7d00;
  do {
    *puVar2 = 0;
    *puVar1 = 0;
    puVar2[1] = 0;
    puVar1[1] = 0;
    puVar2[2] = 0;
    puVar1[2] = 0;
    puVar2[3] = 0;
    puVar1[3] = 0;
    puVar2[4] = 0;
    puVar1[4] = 0;
    puVar2[5] = 0;
    puVar1[5] = 0;
    puVar2[6] = 0;
    puVar1[6] = 0;
    puVar2[7] = 0;
    puVar1[7] = 0;
    puVar2[8] = 0;
    puVar1[8] = 0;
    puVar2[9] = 0;
    puVar1[9] = 0;
    puVar2[10] = 0;
    puVar1[10] = 0;
    puVar2[0xb] = 0;
    puVar1[0xb] = 0;
    puVar2[0xc] = 0;
    puVar1[0xc] = 0;
    puVar2[0xd] = 0;
    puVar1[0xd] = 0;
    puVar2[0xe] = 0;
    puVar1[0xe] = 0;
    puVar2[0xf] = 0;
    puVar2 = puVar2 + 0x10;
    puVar1[0xf] = 0;
    puVar1 = puVar1 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 80216f48  zz_0216f48_ ====

void zz_0216f48_(undefined4 *param_1)

{
  *param_1 = DAT_803d7d00;
  DAT_803d7d00 = param_1;
  param_1[3] = 0;
  return;
}



// ==== 80216f68  zz_0216f68_ ====

void zz_0216f68_(int param_1)

{
  *(int *)(param_1 + 8) = DAT_804366b0;
  DAT_804366b0 = param_1;
  return;
}



// ==== 80216f78  zz_0216f78_ ====

void zz_0216f78_(void)

{
  if (DAT_804366b0 == 0) {
    return;
  }
  DAT_804366b0 = *(undefined4 *)(DAT_804366b0 + 8);
  return;
}



// ==== 80216f94  zz_0216f94_ ====

void zz_0216f94_(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar3 = &DAT_803d7d00 + param_1[3];
  piVar2 = &DAT_803d7d80 + param_1[3];
  if ((int *)*piVar3 == (int *)*piVar2) {
    *piVar2 = 0;
    *piVar3 = 0;
    return;
  }
  if (param_1 == (int *)*piVar3) {
    *piVar3 = *param_1;
    *(undefined4 *)(*piVar3 + 4) = 0;
    return;
  }
  if (param_1 == (int *)*piVar2) {
    *piVar2 = param_1[1];
    *(undefined4 *)*piVar2 = 0;
    return;
  }
  piVar2 = (int *)param_1[1];
  iVar1 = *param_1;
  *piVar2 = iVar1;
  *(int **)(iVar1 + 4) = piVar2;
  return;
}



// ==== 80217028  zz_0217028_ ====

void zz_0217028_(int *param_1)

{
  gnt4_OSDisableInterrupts_bl();
  zz_0216f94_(param_1);
  if (*(short *)((int)param_1 + 0x146) == 1) {
    param_1[8] = 1;
  }
  zz_02193ec_((int)param_1);
  *param_1 = (int)DAT_803d7d00;
  DAT_803d7d00 = param_1;
  param_1[3] = 0;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802170a8  zz_02170a8_ ====

int * zz_02170a8_(uint param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  undefined4 *puVar6;
  
  puVar6 = &DAT_803d7d00;
  gnt4_OSDisableInterrupts_bl();
  piVar3 = DAT_803d7d00;
  if (DAT_803d7d00 == (int *)0x0) {
    iVar1 = param_1 - 1;
    piVar4 = &DAT_803d7d84;
    if (1 < param_1) {
      do {
        puVar6 = puVar6 + 1;
        piVar2 = (int *)*puVar6;
        piVar3 = (int *)0x0;
        if (piVar2 != (int *)0x0) {
          piVar5 = (int *)*piVar4;
          if (piVar2 == piVar5) {
            *piVar4 = 0;
            *puVar6 = 0;
            piVar3 = piVar2;
          }
          else if (piVar5 != (int *)0x0) {
            *piVar4 = piVar5[1];
            *(undefined4 *)*piVar4 = 0;
            piVar3 = piVar5;
          }
        }
        if (piVar3 != (int *)0x0) {
          if (*(short *)((int)piVar3 + 0x146) == 1) {
            piVar3[8] = 1;
          }
          if ((code *)piVar3[4] != (code *)0x0) {
            (*(code *)piVar3[4])(piVar3);
          }
          break;
        }
        piVar4 = piVar4 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  else {
    DAT_803d7d00 = (int *)*DAT_803d7d00;
  }
  if (piVar3 != (int *)0x0) {
    piVar4 = (int *)(&DAT_803d7d00 + param_1);
    *piVar3 = *piVar4;
    piVar3[1] = 0;
    if (*piVar3 == 0) {
      (&DAT_803d7d80)[param_1] = piVar3;
      *piVar4 = (int)piVar3;
    }
    else {
      *(int **)(*piVar4 + 4) = piVar3;
      *piVar4 = (int)piVar3;
    }
    piVar3[3] = param_1;
    piVar3[4] = param_2;
    piVar3[5] = param_3;
    zz_02193ec_((int)piVar3);
  }
  gnt4_OSRestoreInterrupts_bl();
  return piVar3;
}



// ==== 8021721c  zz_021721c_ ====

void zz_021721c_(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  
  DAT_804366b8 = 0;
  DAT_804366bc = 0;
  iVar3 = 0x1e;
  DAT_804366c0 = 0;
  puVar2 = &DAT_803d7e00;
  puVar1 = &DAT_803d9480;
  DAT_804366c4 = 0;
  DAT_804366d8 = 0;
  DAT_804366dc = 1;
  DAT_804366e0 = 0;
  DAT_804366e4 = 1;
  DAT_804366e8 = 2;
  do {
    *puVar2 = 0;
    *puVar1 = 0;
    puVar2[1] = 0;
    puVar1[1] = 0;
    puVar2[2] = 0;
    puVar1[2] = 0;
    puVar2[3] = 0;
    puVar1[3] = 0;
    puVar2[4] = 0;
    puVar1[4] = 0;
    puVar2[5] = 0;
    puVar1[5] = 0;
    puVar2[6] = 0;
    puVar1[6] = 0;
    puVar2[7] = 0;
    puVar1[7] = 0;
    puVar2[8] = 0;
    puVar1[8] = 0;
    puVar2[9] = 0;
    puVar1[9] = 0;
    puVar2[10] = 0;
    puVar1[10] = 0;
    puVar2[0xb] = 0;
    puVar1[0xb] = 0;
    puVar2[0xc] = 0;
    puVar1[0xc] = 0;
    puVar2[0xd] = 0;
    puVar1[0xd] = 0;
    puVar2[0xe] = 0;
    puVar1[0xe] = 0;
    puVar2[0xf] = 0;
    puVar2 = puVar2 + 0x10;
    puVar1[0xf] = 0;
    puVar1 = puVar1 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}



// ==== 80217300  zz_0217300_ ====

void zz_0217300_(undefined4 *param_1)

{
  if (DAT_804366b8 != 0) {
    *param_1 = &DAT_803d7e00 + DAT_804366d8 * 0x1e0;
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 80217334  zz_0217334_ ====

void zz_0217334_(int *param_1)

{
  *param_1 = DAT_804366d8 * 0x780 + -0x7fc26680;
  return;
}



// ==== 80217354  zz_0217354_ ====

void zz_0217354_(undefined4 *param_1)

{
  *param_1 = &DAT_803d7e00 + DAT_804366dc * 0x1e0;
  return;
}



// ==== 80217370  zz_0217370_ ====

void zz_0217370_(int *param_1)

{
  *param_1 = DAT_804366dc * 0x780 + -0x7fc27f80;
  return;
}



// ==== 80217390  zz_0217390_ ====

void zz_0217390_(int *param_1)

{
  *param_1 = DAT_804366dc * 0x780 + -0x7fc27d00;
  return;
}



// ==== 802173b0  zz_02173b0_ ====

void zz_02173b0_(int *param_1)

{
  *param_1 = DAT_804366dc * 0x780 + -0x7fc26680;
  return;
}



// ==== 802173d0  zz_02173d0_ ====

void zz_02173d0_(undefined4 *param_1)

{
  if (DAT_804366bc != 0) {
    *param_1 = &DAT_803d9480 + DAT_804366d8 * 0x1e0;
    return;
  }
  *param_1 = 0;
  return;
}



// ==== 80217404  zz_0217404_ ====

void zz_0217404_(undefined4 *param_1)

{
  *param_1 = &DAT_803d9480 + DAT_804366dc * 0x1e0;
  return;
}



// ==== 80217420  zz_0217420_ ====

void zz_0217420_(undefined4 *param_1)

{
  *param_1 = &DAT_803d9480 + DAT_804366e0 * 0x1e0;
  return;
}



// ==== 8021743c  zz_021743c_ ====

void zz_021743c_(undefined4 *param_1)

{
  *param_1 = &DAT_803d9480 + DAT_804366e4 * 0x1e0;
  return;
}



// ==== 80217458  zz_0217458_ ====

void zz_0217458_(void)

{
  int iVar1;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  undefined4 *local_24;
  int local_20;
  int local_1c;
  undefined4 *local_18;
  int local_14;
  int local_10;
  uint local_c;
  
  DAT_804366c8 = &DAT_803d7e00 + DAT_804366d8 * 0x1e0;
  DAT_804366cc = &DAT_803d7e00 + DAT_804366dc * 0x1e0;
  DAT_804366d0 = &DAT_803d9480 + DAT_804366d8 * 0x1e0;
  DAT_804366d4 = &DAT_803d9480 + DAT_804366dc * 0x1e0;
  if (DAT_804366b8 != (code *)0x0) {
    if (DAT_80436700 == 2) {
      iVar1 = DAT_804366e8 * 0x780;
      local_18 = &DAT_803d7e00 + DAT_804366e8 * 0x1e0;
      local_14 = iVar1 + -0x7fc27f80;
      local_10 = iVar1 + -0x7fc27d00;
      local_c = iVar1 + 0x803d9980;
      gnt4_DCInvalidateRange_bl((uint)local_18,0x780);
      gnt4_DCInvalidateRange_bl(local_c,0x280);
      (*DAT_804366b8)(&local_18,DAT_804366c0);
      gnt4_DCFlushRangeNoSync_bl((uint)local_18,0x780);
      gnt4_DCFlushRangeNoSync_bl(local_c,0x280);
    }
    else {
      local_24 = &DAT_803d7e00 + DAT_804366e8 * 0x1e0;
      local_20 = DAT_804366e8 * 0x780 + -0x7fc27f80;
      local_1c = DAT_804366e8 * 0x780 + -0x7fc27d00;
      gnt4_DCInvalidateRange_bl((uint)local_24,0x780);
      (*DAT_804366b8)(&local_24,DAT_804366c0);
      gnt4_DCFlushRangeNoSync_bl((uint)local_24,0x780);
    }
  }
  if ((DAT_804366bc != (code *)0x0) && (DAT_80436700 != 2)) {
    local_30 = &DAT_803d9480 + DAT_804366e8 * 0x1e0;
    local_2c = DAT_804366e8 * 0x780 + -0x7fc26900;
    local_28 = DAT_804366e8 * 0x780 + -0x7fc26680;
    gnt4_DCInvalidateRange_bl((uint)local_30,0x780);
    (*DAT_804366bc)(&local_30,DAT_804366c4);
    gnt4_DCFlushRangeNoSync_bl((uint)local_30,0x780);
  }
  DAT_804366d8 = (DAT_804366d8 + 1) % 3;
  DAT_804366dc = (DAT_804366dc + 1) % 3;
  DAT_804366e0 = DAT_804366e0 + 1 & 1;
  DAT_804366e4 = DAT_804366e4 + 1 & 1;
  DAT_804366e8 = (DAT_804366e8 + 1) % 3;
  return;
}



// ==== 802176ac  zz_02176ac_ ====

undefined4 zz_02176ac_(void)

{
  return DAT_804366f8;
}



// ==== 802176b4  zz_02176b4_ ====

undefined * zz_02176b4_(void)

{
  int iVar1;
  
  iVar1 = DAT_804366f0 * 0x300;
  DAT_804366f0 = DAT_804366f0 + 1 & 1;
  DAT_804366f4 = &DAT_803dab00 + DAT_804366f0 * 0x300;
  return &DAT_803dab00 + iVar1;
}



// ==== 802176f0  zz_02176f0_ ====

void zz_02176f0_(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  undefined2 uVar3;
  undefined4 *local_18 [3];
  
  puVar2 = DAT_804366f4;
  DAT_804366f8 = 0x1a9;
  local_18[0] = zz_0218550_();
  *DAT_804366f4 = 0;
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)local_18[0];
  DAT_804366f4 = DAT_804366f4 + 1;
  DAT_804366f8 = DAT_804366f8 + 0x2e44;
  uVar3 = (undefined2)param_1;
  uVar1 = (undefined2)((uint)param_1 >> 0x10);
  if (DAT_80436700 == 1) {
    *DAT_804366f4 = 0x11;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = uVar1;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = uVar3;
    DAT_804366f4 = DAT_804366f4 + 1;
    DAT_804366f8 = DAT_804366f8 + 0x5e6;
  }
  else if ((DAT_80436700 < 1) && (-1 < DAT_80436700)) {
    *DAT_804366f4 = 7;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = uVar1;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = uVar3;
    DAT_804366f4 = DAT_804366f4 + 1;
    DAT_804366f8 = DAT_804366f8 + 0x546;
  }
  local_18[0] = (undefined4 *)zz_02193e0_();
  *DAT_804366f4 = 2;
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)local_18[0];
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = 3;
  DAT_804366f4 = DAT_804366f4 + 1;
  if (DAT_80436700 == 2) {
    zz_0217300_(local_18);
    if (local_18[0] != (undefined4 *)0x0) {
      *DAT_804366f4 = 0x13;
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217334_((int *)local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217354_(local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217370_((int *)local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217390_((int *)local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_02173b0_((int *)local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      DAT_804366f8 = DAT_804366f8 + 0xded;
    }
    *DAT_804366f4 = 0x10;
    DAT_804366f4 = DAT_804366f4 + 1;
    zz_0217420_(local_18);
    *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = (short)local_18[0];
    DAT_804366f4 = DAT_804366f4 + 1;
    zz_021743c_(local_18);
    *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = (short)local_18[0];
    DAT_804366f4 = DAT_804366f4 + 1;
    DAT_804366f8 = DAT_804366f8 + 0xded;
  }
  else {
    zz_0217300_(local_18);
    if (local_18[0] != (undefined4 *)0x0) {
      *DAT_804366f4 = 4;
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217354_(local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      DAT_804366f8 = DAT_804366f8 + 0xded;
    }
    zz_02173d0_(local_18);
    if (local_18[0] != (undefined4 *)0x0) {
      *DAT_804366f4 = 5;
      DAT_804366f4 = DAT_804366f4 + 1;
      DAT_804366f8 = DAT_804366f8 + 0xded;
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
      zz_0217404_(local_18);
      *DAT_804366f4 = (short)((uint)local_18[0] >> 0x10);
      DAT_804366f4 = DAT_804366f4 + 1;
      *DAT_804366f4 = (short)local_18[0];
      DAT_804366f4 = DAT_804366f4 + 1;
    }
  }
  if (DAT_804366fc != 0) {
    *DAT_804366f4 = 0x12;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = 0x8000;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = 10;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = 0x803a;
    DAT_804366f4 = DAT_804366f4 + 1;
    *DAT_804366f4 = 0x5c80;
    DAT_804366f4 = DAT_804366f4 + 1;
    DAT_804366f8 = DAT_804366f8 + 3000;
  }
  *DAT_804366f4 = 0xe;
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = uVar1;
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = uVar3;
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)((uint)param_2 >> 0x10);
  DAT_804366f4 = DAT_804366f4 + 1;
  *DAT_804366f4 = (short)param_2;
  DAT_804366f4 = DAT_804366f4 + 1;
  DAT_804366f8 = DAT_804366f8 + 10000;
  *DAT_804366f4 = 0xf;
  DAT_804366f4 = DAT_804366f4 + 1;
  DAT_804366f8 = DAT_804366f8 + 2;
  gnt4_DCFlushRange_bl((uint)puVar2,0x300);
  return;
}



// ==== 80217da0  zz_0217da0_ ====

void zz_0217da0_(void)

{
  DAT_80436700 = 0;
  DAT_804366f0 = 0;
  DAT_804366f4 = &DAT_803dab00;
  DAT_804366fc = 1;
  return;
}



// ==== 80217dc4  zz_0217dc4_ ====

void zz_0217dc4_(int param_1)

{
  if (DAT_80436700 == param_1) {
    return;
  }
  DAT_80436700 = param_1;
  return;
}



// ==== 80217dd8  zz_0217dd8_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_0217dd8_(int param_1)

{
  undefined1 *puVar1;
  undefined8 uVar2;
  undefined *puVar3;
  ushort uVar5;
  undefined1 *puVar4;
  undefined1 *puVar6;
  int iVar7;
  undefined8 uVar8;
  
  _DAT_803dfb50 = gnt4_OSGetTime_bl();
  zz_0219168_(param_1);
  zz_021855c_();
  puVar3 = zz_02176b4_();
  zz_021c664_(0xbabe0180);
  do {
    uVar5 = zz_021c62c_();
  } while (uVar5 != 0);
  zz_021c664_(puVar3);
  do {
    uVar5 = zz_021c62c_();
  } while (uVar5 != 0);
  zz_0216e20_();
  _DAT_803dfb58 = gnt4_OSGetTime_bl();
  zz_0217458_();
  uVar8 = gnt4_OSGetTime_bl();
  DAT_803dfb60 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_803dfb64 = (undefined4)uVar8;
  uVar8 = gnt4_OSGetTime_bl();
  DAT_803dfb68 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_803dfb6c = (undefined4)uVar8;
  if (DAT_80436720 != (code *)0x0) {
    (*DAT_80436720)();
    uVar8 = CONCAT44(DAT_803dfb68,DAT_803dfb6c);
  }
  DAT_803dfb68 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_803dfb6c = (undefined4)uVar8;
  uVar8 = gnt4_OSGetTime_bl();
  DAT_803dfb70 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_803dfb74 = (undefined4)uVar8;
  zz_02176f0_(&DAT_803db880,&DAT_803db100 + DAT_80436708 * 0xa0);
  if (DAT_80436738 == 1) {
    DAT_80436708 = (DAT_80436708 + 1) % 3;
  }
  else {
    DAT_80436708 = DAT_80436708 + 1 & 1;
    AIInitDMA(&DAT_803db100 + DAT_80436708 * 0xa0,0x280);
  }
  uVar8 = gnt4_OSGetTime_bl();
  DAT_803dfb78 = (undefined4)((ulonglong)uVar8 >> 0x20);
  DAT_803dfb7c = (undefined4)uVar8;
  DAT_803dfb80 = zz_0218a14_();
  puVar4 = (undefined1 *)zz_0219da4_();
  uVar8 = _DAT_803dfb58;
  uVar2 = _DAT_803dfb50;
  if (puVar4 != (undefined1 *)0x0) {
    iVar7 = 7;
    puVar6 = &DAT_803dfb50;
    do {
      *puVar4 = *puVar6;
      puVar4[1] = puVar6[1];
      puVar4[2] = puVar6[2];
      puVar4[3] = puVar6[3];
      puVar4[4] = puVar6[4];
      puVar4[5] = puVar6[5];
      puVar4[6] = puVar6[6];
      puVar1 = puVar6 + 7;
      puVar6 = puVar6 + 8;
      puVar4[7] = *puVar1;
      puVar4 = puVar4 + 8;
      iVar7 = iVar7 + -1;
      uVar8 = _DAT_803dfb58;
      uVar2 = _DAT_803dfb50;
    } while (iVar7 != 0);
  }
  _DAT_803dfb50 = (undefined4)((ulonglong)uVar2 >> 0x20);
  _DAT_803dfb54 = (undefined4)uVar2;
  _DAT_803dfb58 = (undefined4)((ulonglong)uVar8 >> 0x20);
  _DAT_803dfb5c = (undefined4)uVar8;
  return;
}



// ==== 80217f90  FUN_80217f90 ====

void FUN_80217f90(void)

{
  undefined8 uVar1;
  
  uVar1 = CONCAT44(DAT_80436718,DAT_8043671c);
  if (DAT_80436710 == 0) {
    uVar1 = gnt4_OSGetTime_bl();
  }
  DAT_80436718 = (undefined4)((ulonglong)uVar1 >> 0x20);
  DAT_8043671c = (undefined4)uVar1;
  if (DAT_80436710 == 1) {
    DAT_80436710 = 0;
    zz_0217dd8_(0);
  }
  else {
    DAT_80436710 = 2;
    zz_021c7b4_((int *)&DAT_803dfb00);
  }
  if (DAT_80436738 == 1) {
    AIInitDMA(&DAT_803db100 + DAT_8043670c * 0xa0,0x280);
    DAT_8043670c = (DAT_8043670c + 1) % 3;
  }
  return;
}



// ==== 80218058  FUN_80218058 ====

void FUN_80218058(void)

{
  int extraout_r4;
  
  if (DAT_80436710 == 2) {
    DAT_80436710 = 0;
    gnt4_OSGetTime_bl();
    zz_0217dd8_((uint)(extraout_r4 - DAT_8043671c) >> 2);
  }
  else {
    DAT_80436710 = 1;
  }
  return;
}



// ==== 802180b0  FUN_802180b0 ====

void FUN_802180b0(void)

{
  DAT_80436728 = 1;
  gnt4_OSWakeupThread_bl((int *)&DAT_80436730);
  return;
}



// ==== 802180dc  zz_02180dc_ ====

void zz_02180dc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined8 uVar2;
  
  DAT_803dfb0c = &DAT_803a76c0;
  DAT_803dfb10 = (uint)DAT_80435d38;
  DAT_803dfb14 = 0;
  DAT_803dfb18 = &DAT_803dbb00;
  DAT_803dfb1c = 0x2000;
  DAT_803dfb20 = 0;
  DAT_803dfb24 = 0x10;
  DAT_803dfb26 = 0x30;
  DAT_803dfb28 = &LAB_8021804c;
  DAT_803dfb2c = FUN_80218058;
  DAT_803dfb30 = FUN_802180b0;
  DAT_803dfb34 = 0;
  DAT_803dfb04 = 0;
  DAT_80436724 = 0;
  DAT_80436728 = 0;
  uVar2 = gnt4_OSInitThreadQueue_bl((undefined4 *)&DAT_80436730);
  iVar1 = zz_021c73c_();
  if (iVar1 == 0) {
    zz_021c678_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  zz_021c744_((undefined4 *)&DAT_803dfb00);
  do {
  } while (DAT_80436724 == 0);
  return;
}



// ==== 802181a8  zz_02181a8_ ====

void zz_02181a8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 6;
  DAT_80436708 = 0;
  DAT_8043670c = 0;
  puVar1 = &DAT_803db100;
  DAT_8043672c = 0;
  DAT_80436738 = param_9;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0;
    puVar1[0xf] = 0;
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
    puVar1[0x13] = 0;
    puVar1[0x14] = 0;
    puVar1[0x15] = 0;
    puVar1[0x16] = 0;
    puVar1[0x17] = 0;
    puVar1[0x18] = 0;
    puVar1[0x19] = 0;
    puVar1[0x1a] = 0;
    puVar1[0x1b] = 0;
    puVar1[0x1c] = 0;
    puVar1[0x1d] = 0;
    puVar1[0x1e] = 0;
    puVar1[0x1f] = 0;
    puVar1[0x20] = 0;
    puVar1[0x21] = 0;
    puVar1[0x22] = 0;
    puVar1[0x23] = 0;
    puVar1[0x24] = 0;
    puVar1[0x25] = 0;
    puVar1[0x26] = 0;
    puVar1[0x27] = 0;
    puVar1[0x28] = 0;
    puVar1[0x29] = 0;
    puVar1[0x2a] = 0;
    puVar1[0x2b] = 0;
    puVar1[0x2c] = 0;
    puVar1[0x2d] = 0;
    puVar1[0x2e] = 0;
    puVar1[0x2f] = 0;
    puVar1[0x30] = 0;
    puVar1[0x31] = 0;
    puVar1[0x32] = 0;
    puVar1[0x33] = 0;
    puVar1[0x34] = 0;
    puVar1[0x35] = 0;
    puVar1[0x36] = 0;
    puVar1[0x37] = 0;
    puVar1[0x38] = 0;
    puVar1[0x39] = 0;
    puVar1[0x3a] = 0;
    puVar1[0x3b] = 0;
    puVar1[0x3c] = 0;
    puVar1[0x3d] = 0;
    puVar1[0x3e] = 0;
    puVar1[0x3f] = 0;
    puVar1[0x40] = 0;
    puVar1[0x41] = 0;
    puVar1[0x42] = 0;
    puVar1[0x43] = 0;
    puVar1[0x44] = 0;
    puVar1[0x45] = 0;
    puVar1[0x46] = 0;
    puVar1[0x47] = 0;
    puVar1[0x48] = 0;
    puVar1[0x49] = 0;
    puVar1[0x4a] = 0;
    puVar1[0x4b] = 0;
    puVar1[0x4c] = 0;
    puVar1[0x4d] = 0;
    puVar1[0x4e] = 0;
    puVar1[0x4f] = 0;
    puVar1 = puVar1 + 0x50;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  gnt4_DCFlushRange_bl(0x803db100,0x780);
  iVar2 = 2;
  puVar1 = &DAT_803db880;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
    puVar1[0xb] = 0;
    puVar1[0xc] = 0;
    puVar1[0xd] = 0;
    puVar1[0xe] = 0;
    puVar1[0xf] = 0;
    puVar1[0x10] = 0;
    puVar1[0x11] = 0;
    puVar1[0x12] = 0;
    puVar1[0x13] = 0;
    puVar1[0x14] = 0;
    puVar1[0x15] = 0;
    puVar1[0x16] = 0;
    puVar1[0x17] = 0;
    puVar1[0x18] = 0;
    puVar1[0x19] = 0;
    puVar1[0x1a] = 0;
    puVar1[0x1b] = 0;
    puVar1[0x1c] = 0;
    puVar1[0x1d] = 0;
    puVar1[0x1e] = 0;
    puVar1[0x1f] = 0;
    puVar1[0x20] = 0;
    puVar1[0x21] = 0;
    puVar1[0x22] = 0;
    puVar1[0x23] = 0;
    puVar1[0x24] = 0;
    puVar1[0x25] = 0;
    puVar1[0x26] = 0;
    puVar1[0x27] = 0;
    puVar1[0x28] = 0;
    puVar1[0x29] = 0;
    puVar1[0x2a] = 0;
    puVar1[0x2b] = 0;
    puVar1[0x2c] = 0;
    puVar1[0x2d] = 0;
    puVar1[0x2e] = 0;
    puVar1[0x2f] = 0;
    puVar1[0x30] = 0;
    puVar1[0x31] = 0;
    puVar1[0x32] = 0;
    puVar1[0x33] = 0;
    puVar1[0x34] = 0;
    puVar1[0x35] = 0;
    puVar1[0x36] = 0;
    puVar1[0x37] = 0;
    puVar1[0x38] = 0;
    puVar1[0x39] = 0;
    puVar1[0x3a] = 0;
    puVar1[0x3b] = 0;
    puVar1[0x3c] = 0;
    puVar1[0x3d] = 0;
    puVar1[0x3e] = 0;
    puVar1[0x3f] = 0;
    puVar1[0x40] = 0;
    puVar1[0x41] = 0;
    puVar1[0x42] = 0;
    puVar1[0x43] = 0;
    puVar1[0x44] = 0;
    puVar1[0x45] = 0;
    puVar1[0x46] = 0;
    puVar1[0x47] = 0;
    puVar1[0x48] = 0;
    puVar1[0x49] = 0;
    puVar1[0x4a] = 0;
    puVar1[0x4b] = 0;
    puVar1[0x4c] = 0;
    puVar1[0x4d] = 0;
    puVar1[0x4e] = 0;
    puVar1[0x4f] = 0;
    puVar1 = puVar1 + 0x50;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  gnt4_DCFlushRange_bl(0x803db880,0x280);
  zz_02180dc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_02145f0_(FUN_80217f90);
  if (DAT_80436738 == 1) {
    zz_02176f0_(&DAT_803db880,&DAT_803db600);
  }
  else {
    zz_02176f0_(&DAT_803db880,&DAT_803db380);
  }
  DAT_80436710 = 1;
  DAT_80436720 = 0;
  if (DAT_80436738 == 1) {
    AIInitDMA(&DAT_803db100 + DAT_8043670c * 0xa0,0x280);
    DAT_8043670c = DAT_8043670c + 1 & 1;
  }
  else {
    AIInitDMA(&DAT_803db100 + DAT_80436708 * 0xa0,0x280);
  }
  AIStartDMA();
  return;
}



// ==== 80218548  zz_0218548_ ====

void zz_0218548_(undefined4 param_1)

{
  DAT_80436720 = param_1;
  return;
}



// ==== 80218550  zz_0218550_ ====

undefined4 * zz_0218550_(void)

{
  return &DAT_803dfba0;
}



// ==== 8021855c  zz_021855c_ ====

void zz_021855c_(void)

{
  int iVar1;
  
  iVar1 = DAT_80436740 / 0xa0 + (DAT_80436740 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436740 = 0;
    DAT_803dfba0 = 0;
    DAT_803dfba4 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfba0 = DAT_80436740;
    DAT_803dfba4 = -(short)iVar1;
    DAT_80436740 = DAT_80436740 + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436744 / 0xa0 + (DAT_80436744 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436744 = 0;
    DAT_803dfba6 = 0;
    DAT_803dfbaa = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfba6 = DAT_80436744;
    DAT_803dfbaa = -(short)iVar1;
    DAT_80436744 = DAT_80436744 + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436748 / 0xa0 + (DAT_80436748 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436748 = 0;
    DAT_803dfbac = 0;
    DAT_803dfbb0 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbac = DAT_80436748;
    DAT_803dfbb0 = -(short)iVar1;
    DAT_80436748 = DAT_80436748 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8043674c / 0xa0 + (DAT_8043674c >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8043674c = 0;
    DAT_803dfbb2 = 0;
    DAT_803dfbb6 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbb2 = DAT_8043674c;
    DAT_803dfbb6 = -(short)iVar1;
    DAT_8043674c = DAT_8043674c + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436750 / 0xa0 + (DAT_80436750 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436750 = 0;
    DAT_803dfbb8 = 0;
    DAT_803dfbbc = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbb8 = DAT_80436750;
    DAT_803dfbbc = -(short)iVar1;
    DAT_80436750 = DAT_80436750 + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436754 / 0xa0 + (DAT_80436754 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436754 = 0;
    DAT_803dfbbe = 0;
    DAT_803dfbc2 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbbe = DAT_80436754;
    DAT_803dfbc2 = -(short)iVar1;
    DAT_80436754 = DAT_80436754 + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436758 / 0xa0 + (DAT_80436758 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436758 = 0;
    DAT_803dfbc4 = 0;
    DAT_803dfbc8 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbc4 = DAT_80436758;
    DAT_803dfbc8 = -(short)iVar1;
    DAT_80436758 = DAT_80436758 + iVar1 * -0xa0;
  }
  iVar1 = DAT_8043675c / 0xa0 + (DAT_8043675c >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_8043675c = 0;
    DAT_803dfbca = 0;
    DAT_803dfbce = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbca = DAT_8043675c;
    DAT_803dfbce = -(short)iVar1;
    DAT_8043675c = DAT_8043675c + iVar1 * -0xa0;
  }
  iVar1 = DAT_80436760 / 0xa0 + (DAT_80436760 >> 0x1f);
  iVar1 = iVar1 - (iVar1 >> 0x1f);
  if (iVar1 == 0) {
    DAT_80436760 = 0;
    DAT_803dfbd0 = 0;
    DAT_803dfbd4 = 0;
  }
  else {
    if (0x14 < iVar1) {
      iVar1 = 0x14;
    }
    if (iVar1 < -0x14) {
      iVar1 = -0x14;
    }
    DAT_803dfbd0 = DAT_80436760;
    DAT_803dfbd4 = -(short)iVar1;
    DAT_80436760 = DAT_80436760 + iVar1 * -0xa0;
  }
  gnt4_DCFlushRange_bl(0x803dfba0,0x36);
  return;
}



// ==== 80218954  zz_0218954_ ====

void zz_0218954_(void)

{
  DAT_80436760 = 0;
  DAT_8043675c = 0;
  DAT_80436758 = 0;
  DAT_80436754 = 0;
  DAT_80436750 = 0;
  DAT_8043674c = 0;
  DAT_80436748 = 0;
  DAT_80436744 = 0;
  DAT_80436740 = 0;
  return;
}



// ==== 80218980  zz_0218980_ ====

void zz_0218980_(int param_1)

{
  DAT_80436740 = DAT_80436740 + *(short *)(param_1 + 0x52);
  DAT_8043674c = DAT_8043674c + *(short *)(param_1 + 0x54);
  DAT_80436758 = DAT_80436758 + *(short *)(param_1 + 0x56);
  DAT_80436744 = DAT_80436744 + *(short *)(param_1 + 0x58);
  DAT_80436750 = DAT_80436750 + *(short *)(param_1 + 0x5a);
  DAT_8043675c = DAT_8043675c + *(short *)(param_1 + 0x5c);
  DAT_80436748 = DAT_80436748 + *(short *)(param_1 + 0x5e);
  DAT_80436754 = DAT_80436754 + *(short *)(param_1 + 0x60);
  DAT_80436760 = DAT_80436760 + *(short *)(param_1 + 0x62);
  return;
}



// ==== 80218a14  zz_0218a14_ ====

undefined4 zz_0218a14_(void)

{
  return DAT_80436770;
}



// ==== 80218a1c  zz_0218a1c_ ====

/* WARNING: Removing unreachable block (ram,0x80218c38) */

void zz_0218a1c_(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  uint uVar9;
  
  DAT_80436770 = DAT_80436770 + 1;
  iVar5 = *(int *)(param_1 + 0x18);
  uVar4 = *(uint *)(param_1 + 0x1c);
  iVar6 = iVar5 * 0xf4;
  if (uVar4 == 0) {
    *(undefined2 *)(param_1 + 0x146) = *(undefined2 *)((int)&DAT_803dfbec + iVar6 + 2);
    *(undefined2 *)(param_1 + 0x19c) = *(undefined2 *)(&DAT_803dfc44 + iVar6);
    *(undefined2 *)(param_1 + 0x1b2) = *(undefined2 *)(&DAT_803dfc5a + iVar6);
    *(undefined2 *)(param_1 + 0x1b4) = *(undefined2 *)(&DAT_803dfc5c + iVar6);
    return;
  }
  if ((uVar4 & 0x80000000) != 0) {
    *(undefined4 *)(&DAT_803dfbe0 + iVar5 * 0x7a) = *(undefined4 *)(param_1 + 0x138);
    *(undefined4 *)(&DAT_803dfbe4 + iVar5 * 0x7a) = *(undefined4 *)(param_1 + 0x13c);
    (&DAT_803dfbe8)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x140);
    (&DAT_803dfbec)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x144);
    (&DAT_803dfbf0)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x148);
    (&DAT_803dfbf4)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x14c);
    (&DAT_803dfbf8)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x150);
    (&DAT_803dfbfc)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x154);
    (&DAT_803dfc00)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x158);
    (&DAT_803dfc04)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x15c);
    (&DAT_803dfc08)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x160);
    (&DAT_803dfc0c)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x164);
    (&DAT_803dfc10)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x168);
    (&DAT_803dfc14)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x16c);
    *(undefined4 *)(&DAT_803dfc18 + iVar5 * 0x7a) = *(undefined4 *)(param_1 + 0x170);
    (&DAT_803dfc1c)[iVar5 * 0x3d] = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(&DAT_803dfc20 + iVar6) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(&DAT_803dfc24 + iVar6) = *(undefined4 *)(param_1 + 0x17c);
    *(undefined4 *)(&DAT_803dfc28 + iVar6) = *(undefined4 *)(param_1 + 0x180);
    *(undefined4 *)(&DAT_803dfc2c + iVar6) = *(undefined4 *)(param_1 + 0x184);
    *(undefined4 *)(&DAT_803dfc30 + iVar5 * 0x7a) = *(undefined4 *)(param_1 + 0x188);
    *(undefined4 *)(&DAT_803dfc34 + iVar6) = *(undefined4 *)(param_1 + 0x18c);
    *(undefined4 *)(&DAT_803dfc38 + iVar6) = *(undefined4 *)(param_1 + 400);
    *(undefined4 *)(&DAT_803dfc3c + iVar6) = *(undefined4 *)(param_1 + 0x194);
    *(undefined4 *)(&DAT_803dfc40 + iVar6) = *(undefined4 *)(param_1 + 0x198);
    *(undefined4 *)(&DAT_803dfc44 + iVar6) = *(undefined4 *)(param_1 + 0x19c);
    *(undefined4 *)(&DAT_803dfc48 + iVar6) = *(undefined4 *)(param_1 + 0x1a0);
    *(undefined4 *)(&DAT_803dfc4c + iVar6) = *(undefined4 *)(param_1 + 0x1a4);
    *(undefined4 *)(&DAT_803dfc50 + iVar6) = *(undefined4 *)(param_1 + 0x1a8);
    *(undefined4 *)(&DAT_803dfc54 + iVar6) = *(undefined4 *)(param_1 + 0x1ac);
    *(undefined4 *)(&DAT_803dfc58 + iVar6) = *(undefined4 *)(param_1 + 0x1b0);
    *(undefined4 *)(&DAT_803dfc5c + iVar6) = *(undefined4 *)(param_1 + 0x1b4);
    *(undefined4 *)(&DAT_803dfc60 + iVar6) = *(undefined4 *)(param_1 + 0x1b8);
    *(undefined4 *)(&DAT_803dfc64 + iVar6) = *(undefined4 *)(param_1 + 0x1bc);
    *(undefined4 *)(&DAT_803dfc68 + iVar6) = *(undefined4 *)(param_1 + 0x1c0);
    *(undefined4 *)(&DAT_803dfc6c + iVar6) = *(undefined4 *)(param_1 + 0x1c4);
    *(undefined4 *)(&DAT_803dfc70 + iVar6) = *(undefined4 *)(param_1 + 0x1c8);
    *(undefined4 *)(&DAT_803dfc74 + iVar6) = *(undefined4 *)(param_1 + 0x1cc);
    *(undefined4 *)(&DAT_803dfc78 + iVar6) = *(undefined4 *)(param_1 + 0x1d0);
    *(undefined4 *)(&DAT_803dfc7c + iVar6) = *(undefined4 *)(param_1 + 0x1d4);
    *(undefined4 *)(&DAT_803dfc80 + iVar6) = *(undefined4 *)(param_1 + 0x1d8);
    *(undefined4 *)(&DAT_803dfc84 + iVar6) = *(undefined4 *)(param_1 + 0x1dc);
    *(undefined4 *)(&DAT_803dfc88 + iVar6) = *(undefined4 *)(param_1 + 0x1e0);
    *(undefined4 *)(&DAT_803dfc8c + iVar6) = *(undefined4 *)(param_1 + 0x1e4);
    *(undefined4 *)(&DAT_803dfc90 + iVar6) = *(undefined4 *)(param_1 + 0x1e8);
    *(undefined4 *)(&DAT_803dfc94 + iVar6) = *(undefined4 *)(param_1 + 0x1ec);
    *(undefined4 *)(&DAT_803dfc98 + iVar6) = *(undefined4 *)(param_1 + 0x1f0);
    *(undefined4 *)(&DAT_803dfc9c + iVar6) = *(undefined4 *)(param_1 + 500);
    *(undefined4 *)(&DAT_803dfca0 + iVar6) = *(undefined4 *)(param_1 + 0x1f8);
    *(undefined4 *)(&DAT_803dfca4 + iVar6) = *(undefined4 *)(param_1 + 0x1fc);
    *(undefined4 *)(&DAT_803dfca8 + iVar6) = *(undefined4 *)(param_1 + 0x200);
    *(undefined4 *)(&DAT_803dfcac + iVar6) = *(undefined4 *)(param_1 + 0x204);
    uVar4 = *(uint *)(param_1 + 0x28);
    if (uVar4 == 0) {
      return;
    }
    puVar3 = (undefined4 *)(param_1 + 0x34);
    puVar7 = (undefined4 *)(&DAT_803e48e0 + *(int *)(param_1 + 0x18) * 0x100);
    uVar8 = uVar4 >> 3;
    if (uVar8 != 0) {
      do {
        *puVar3 = *puVar7;
        puVar3[1] = puVar7[1];
        puVar3[2] = puVar7[2];
        puVar3[3] = puVar7[3];
        puVar3[4] = puVar7[4];
        puVar3[5] = puVar7[5];
        puVar3[6] = puVar7[6];
        puVar1 = puVar7 + 7;
        puVar7 = puVar7 + 8;
        puVar3[7] = *puVar1;
        puVar3 = puVar3 + 8;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      uVar4 = uVar4 & 7;
      if (uVar4 == 0) {
        return;
      }
    }
    do {
      uVar2 = *puVar7;
      puVar7 = puVar7 + 1;
      *puVar3 = uVar2;
      puVar3 = puVar3 + 1;
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
    return;
  }
  if ((uVar4 & 1) != 0) {
    *(undefined2 *)(&DAT_803dfbe8 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x140);
    *(undefined2 *)((int)&DAT_803dfbe8 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x142);
  }
  if ((uVar4 & 2) != 0) {
    *(undefined2 *)(&DAT_803dfbec + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x144);
  }
  if ((uVar4 & 4) == 0) {
    *(undefined2 *)(param_1 + 0x146) = *(undefined2 *)((int)&DAT_803dfbec + iVar6 + 2);
  }
  else {
    *(undefined2 *)((int)&DAT_803dfbec + iVar6 + 2) = *(undefined2 *)(param_1 + 0x146);
  }
  if ((uVar4 & 8) != 0) {
    *(undefined2 *)(&DAT_803dfbf0 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x148);
  }
  if ((uVar4 & 0x10) != 0) {
    *(undefined2 *)((int)&DAT_803dfbf0 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x14a);
    *(undefined2 *)(&DAT_803dfbf4 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x14c);
    *(undefined2 *)((int)&DAT_803dfbf4 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x14e);
    *(undefined2 *)(&DAT_803dfbf8 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x150);
    *(undefined2 *)((int)&DAT_803dfbf8 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x152);
    *(undefined2 *)(&DAT_803dfbfc + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x154);
    *(undefined2 *)((int)&DAT_803dfbfc + iVar6 + 2) = *(undefined2 *)(param_1 + 0x156);
    *(undefined2 *)(&DAT_803dfc00 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x158);
    *(undefined2 *)((int)&DAT_803dfc00 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x15a);
    *(undefined2 *)(&DAT_803dfc04 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x15c);
    *(undefined2 *)((int)&DAT_803dfc04 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x15e);
    *(undefined2 *)(&DAT_803dfc08 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x160);
    *(undefined2 *)((int)&DAT_803dfc08 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x162);
    *(undefined2 *)(&DAT_803dfc0c + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x164);
    *(undefined2 *)((int)&DAT_803dfc0c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x166);
    *(undefined2 *)(&DAT_803dfc10 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x168);
    *(undefined2 *)((int)&DAT_803dfc10 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x16a);
    *(undefined2 *)(&DAT_803dfc14 + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x16c);
  }
  if ((uVar4 & 0x40) == 0) {
    if ((uVar4 & 0x20) != 0) {
      *(undefined2 *)((int)&DAT_803dfc14 + iVar6 + 2) = *(undefined2 *)(param_1 + 0x16e);
      (&DAT_803dfc18)[iVar5 * 0x7a] = *(undefined2 *)(param_1 + 0x170);
      (&DAT_803dfc1a)[iVar5 * 0x7a] = *(undefined2 *)(param_1 + 0x172);
      *(undefined2 *)(&DAT_803dfc1c + iVar5 * 0x3d) = *(undefined2 *)(param_1 + 0x174);
      *(undefined2 *)((int)&DAT_803dfc1c + iVar6 + 2) = *(undefined2 *)(param_1 + 0x176);
      *(undefined2 *)(&DAT_803dfc20 + iVar6) = *(undefined2 *)(param_1 + 0x178);
      *(undefined2 *)(&DAT_803dfc22 + iVar6) = *(undefined2 *)(param_1 + 0x17a);
      puVar3 = *(undefined4 **)(param_1 + 0x134);
      *puVar3 = 0;
      puVar3[1] = 0;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[4] = 0;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0;
      puVar3[8] = 0;
      puVar3[9] = 0;
      puVar3[10] = 0;
      puVar3[0xb] = 0;
      puVar3[0xc] = 0;
      puVar3[0xd] = 0;
      puVar3[0xe] = 0;
      puVar3[0xf] = 0;
    }
  }
  else {
    *(undefined2 *)(&DAT_803dfc20 + iVar6) = *(undefined2 *)(param_1 + 0x178);
    *(undefined2 *)(&DAT_803dfc22 + iVar6) = *(undefined2 *)(param_1 + 0x17a);
  }
  if ((uVar4 & 0x80) != 0) {
    *(undefined2 *)(&DAT_803dfc24 + iVar6) = *(undefined2 *)(param_1 + 0x17c);
    *(undefined2 *)(&DAT_803dfc26 + iVar6) = *(undefined2 *)(param_1 + 0x17e);
    *(undefined2 *)(&DAT_803dfc28 + iVar6) = *(undefined2 *)(param_1 + 0x180);
    *(undefined2 *)(&DAT_803dfc2a + iVar6) = *(undefined2 *)(param_1 + 0x182);
    *(undefined2 *)(&DAT_803dfc2c + iVar6) = *(undefined2 *)(param_1 + 0x184);
    uVar8 = *(uint *)(param_1 + 0x28);
    if (uVar8 != 0) {
      puVar3 = (undefined4 *)(param_1 + 0x34);
      puVar7 = (undefined4 *)(&DAT_803e48e0 + *(int *)(param_1 + 0x18) * 0x100);
      uVar9 = uVar8 >> 3;
      if (uVar9 != 0) {
        do {
          *puVar7 = *puVar3;
          puVar7[1] = puVar3[1];
          puVar7[2] = puVar3[2];
          puVar7[3] = puVar3[3];
          puVar7[4] = puVar3[4];
          puVar7[5] = puVar3[5];
          puVar7[6] = puVar3[6];
          puVar1 = puVar3 + 7;
          puVar3 = puVar3 + 8;
          puVar7[7] = *puVar1;
          puVar7 = puVar7 + 8;
          uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
        uVar8 = uVar8 & 7;
        if (uVar8 == 0) goto LAB_80218f14;
      }
      do {
        uVar2 = *puVar3;
        puVar3 = puVar3 + 1;
        *puVar7 = uVar2;
        puVar7 = puVar7 + 1;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
    }
  }
LAB_80218f14:
  if ((uVar4 & 0x100) != 0) {
    *(undefined2 *)(&DAT_803dfc32 + iVar6) = *(undefined2 *)(param_1 + 0x18a);
    *(undefined2 *)(&DAT_803dfc34 + iVar6) = *(undefined2 *)(param_1 + 0x18c);
    *(undefined2 *)(&DAT_803dfc36 + iVar6) = *(undefined2 *)(param_1 + 0x18e);
    *(undefined2 *)(&DAT_803dfc38 + iVar6) = *(undefined2 *)(param_1 + 400);
    *(undefined2 *)(&DAT_803dfc3a + iVar6) = *(undefined2 *)(param_1 + 0x192);
    *(undefined2 *)(&DAT_803dfc3c + iVar6) = *(undefined2 *)(param_1 + 0x194);
    *(undefined2 *)(&DAT_803dfc3e + iVar6) = *(undefined2 *)(param_1 + 0x196);
    *(undefined2 *)(&DAT_803dfc40 + iVar6) = *(undefined2 *)(param_1 + 0x198);
    *(undefined2 *)(&DAT_803dfc42 + iVar6) = *(undefined2 *)(param_1 + 0x19a);
  }
  if ((uVar4 & 0x400) == 0) {
    if ((uVar4 & 0x200) != 0) {
      *(undefined2 *)(&DAT_803dfc44 + iVar6) = *(undefined2 *)(param_1 + 0x19c);
      *(undefined2 *)(&DAT_803dfc46 + iVar6) = *(undefined2 *)(param_1 + 0x19e);
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x19c) = *(undefined2 *)(&DAT_803dfc44 + iVar6);
    *(undefined2 *)(&DAT_803dfc46 + iVar6) = *(undefined2 *)(param_1 + 0x19e);
  }
  if ((uVar4 & 0x800) != 0) {
    *(undefined2 *)(&DAT_803dfc48 + iVar6) = *(undefined2 *)(param_1 + 0x1a0);
    *(undefined2 *)(&DAT_803dfc4a + iVar6) = *(undefined2 *)(param_1 + 0x1a2);
    *(undefined2 *)(&DAT_803dfc4c + iVar6) = *(undefined2 *)(param_1 + 0x1a4);
  }
  if ((uVar4 & 0x1e000) == 0) {
    if ((uVar4 & 0x1000) == 0) {
      *(undefined2 *)(param_1 + 0x1b2) = *(undefined2 *)(&DAT_803dfc5a + iVar6);
      *(undefined2 *)(param_1 + 0x1b4) = *(undefined2 *)(&DAT_803dfc5c + iVar6);
    }
    else {
      *(undefined4 *)(&DAT_803dfc4e + iVar6) = *(undefined4 *)(param_1 + 0x1a6);
      *(undefined4 *)(&DAT_803dfc52 + iVar6) = *(undefined4 *)(param_1 + 0x1aa);
      *(undefined4 *)(&DAT_803dfc56 + iVar6) = *(undefined4 *)(param_1 + 0x1ae);
      *(undefined4 *)(&DAT_803dfc5a + iVar6) = *(undefined4 *)(param_1 + 0x1b2);
    }
  }
  else {
    if ((uVar4 & 0x2000) != 0) {
      *(undefined2 *)(&DAT_803dfc4e + iVar6) = *(undefined2 *)(param_1 + 0x1a6);
    }
    if ((uVar4 & 0x4000) != 0) {
      *(undefined4 *)(&DAT_803dfc52 + iVar6) = *(undefined4 *)(param_1 + 0x1aa);
    }
    if ((uVar4 & 0x8000) != 0) {
      *(undefined4 *)(&DAT_803dfc56 + iVar6) = *(undefined4 *)(param_1 + 0x1ae);
    }
    if ((uVar4 & 0x10000) == 0) {
      *(undefined4 *)(param_1 + 0x1b2) = *(undefined4 *)(&DAT_803dfc5a + iVar6);
    }
    else {
      *(undefined4 *)(&DAT_803dfc5a + iVar6) = *(undefined4 *)(param_1 + 0x1b2);
    }
  }
  if ((uVar4 & 0x20000) != 0) {
    *(undefined4 *)(&DAT_803dfc5e + iVar6) = *(undefined4 *)(param_1 + 0x1b6);
    *(undefined4 *)(&DAT_803dfc62 + iVar6) = *(undefined4 *)(param_1 + 0x1ba);
    *(undefined4 *)(&DAT_803dfc66 + iVar6) = *(undefined4 *)(param_1 + 0x1be);
    *(undefined4 *)(&DAT_803dfc6a + iVar6) = *(undefined4 *)(param_1 + 0x1c2);
    *(undefined4 *)(&DAT_803dfc6e + iVar6) = *(undefined4 *)(param_1 + 0x1c6);
    *(undefined4 *)(&DAT_803dfc72 + iVar6) = *(undefined4 *)(param_1 + 0x1ca);
    *(undefined4 *)(&DAT_803dfc76 + iVar6) = *(undefined4 *)(param_1 + 0x1ce);
    *(undefined4 *)(&DAT_803dfc7a + iVar6) = *(undefined4 *)(param_1 + 0x1d2);
    *(undefined4 *)(&DAT_803dfc7e + iVar6) = *(undefined4 *)(param_1 + 0x1d6);
    *(undefined4 *)(&DAT_803dfc82 + iVar6) = *(undefined4 *)(param_1 + 0x1da);
  }
  if ((uVar4 & 0x80000) == 0) {
    if ((uVar4 & 0x40000) != 0) {
      *(undefined2 *)(&DAT_803dfc86 + iVar6) = *(undefined2 *)(param_1 + 0x1de);
      *(undefined2 *)(&DAT_803dfc88 + iVar6) = *(undefined2 *)(param_1 + 0x1e0);
      *(undefined2 *)(&DAT_803dfc8a + iVar6) = *(undefined2 *)(param_1 + 0x1e2);
      *(undefined2 *)(&DAT_803dfc8c + iVar6) = *(undefined2 *)(param_1 + 0x1e4);
      *(undefined2 *)(&DAT_803dfc8e + iVar6) = *(undefined2 *)(param_1 + 0x1e6);
      *(undefined2 *)(&DAT_803dfc90 + iVar6) = *(undefined2 *)(param_1 + 0x1e8);
      *(undefined2 *)(&DAT_803dfc92 + iVar6) = *(undefined2 *)(param_1 + 0x1ea);
    }
  }
  else {
    *(undefined2 *)(&DAT_803dfc86 + iVar6) = *(undefined2 *)(param_1 + 0x1de);
    *(undefined2 *)(&DAT_803dfc88 + iVar6) = *(undefined2 *)(param_1 + 0x1e0);
  }
  if ((uVar4 & 0x100000) != 0) {
    *(undefined2 *)(&DAT_803dfc94 + iVar6) = *(undefined2 *)(param_1 + 0x1ec);
    *(undefined2 *)(&DAT_803dfc96 + iVar6) = *(undefined2 *)(param_1 + 0x1ee);
    *(undefined2 *)(&DAT_803dfc98 + iVar6) = *(undefined2 *)(param_1 + 0x1f0);
  }
  if ((uVar4 & 0x400000) == 0) {
    if ((uVar4 & 0x200000) != 0) {
      *(undefined2 *)(&DAT_803dfc9a + iVar6) = *(undefined2 *)(param_1 + 0x1f2);
      *(undefined2 *)(&DAT_803dfc9c + iVar6) = *(undefined2 *)(param_1 + 500);
      *(undefined2 *)(&DAT_803dfc9e + iVar6) = *(undefined2 *)(param_1 + 0x1f6);
      *(undefined2 *)(&DAT_803dfca0 + iVar6) = *(undefined2 *)(param_1 + 0x1f8);
      return;
    }
    return;
  }
  *(undefined2 *)(&DAT_803dfc9e + iVar6) = *(undefined2 *)(param_1 + 0x1f6);
  *(undefined2 *)(&DAT_803dfca0 + iVar6) = *(undefined2 *)(param_1 + 0x1f8);
  return;
}



// ==== 80219168  zz_0219168_ ====

void zz_0219168_(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  
  DAT_80436770 = 0;
  gnt4_DCInvalidateRange_bl(0x803dfbe0,0x3d00);
  gnt4_DCInvalidateRange_bl(0x803e38e0,0x1000);
  iVar2 = zz_02176ac_();
  iVar4 = 0x1f;
  uVar5 = iVar2 + param_1 + 0xaa10;
  do {
    puVar3 = (undefined4 *)zz_0216e08_(iVar4);
    while( true ) {
      if (puVar3 == (undefined4 *)0x0) break;
      if (puVar3[8] != 0) {
        zz_0218980_((int)(&DAT_803dfbe0 + puVar3[6] * 0x7a));
      }
      if ((*(short *)((int)puVar3 + 0x146) == 1) || (puVar3[10] != 0)) {
        if (*(short *)(puVar3 + 0x50) != 2) {
          uVar5 = uVar5 + *(int *)(&DAT_803a5b98 + (uint)*(ushort *)((int)puVar3 + 0x1de) * 4);
        }
        if (*(short *)((int)puVar3 + 0x1f2) != 0) {
          uVar5 = uVar5 + 0x22b;
        }
        uVar1 = *(ushort *)(puVar3 + 0x51);
        uVar5 = *(int *)(&DAT_803a5bac + (uVar1 & 0xf) * 4) +
                *(int *)(&DAT_803a5bec + (uVar1 >> 2 & 0x7c)) +
                *(int *)(&DAT_803a5bec + (uVar1 >> 7 & 0x7c)) + 0x8c + uVar5;
        if (uVar5 < DAT_80436768) {
          zz_0218a1c_((int)puVar3);
        }
        else {
          iVar2 = puVar3[6] * 0xf4;
          if (*(short *)((int)&DAT_803dfbec + iVar2 + 2) == 1) {
            zz_0218980_((int)(&DAT_803dfbe0 + puVar3[6] * 0x7a));
          }
          *(undefined2 *)(&DAT_803dfc2c + iVar2) = 0;
          *(undefined2 *)(&DAT_803dfc2a + iVar2) = 0;
          *(undefined2 *)(&DAT_803dfc28 + iVar2) = 0;
          *(undefined2 *)(&DAT_803dfc26 + iVar2) = 0;
          *(undefined2 *)(&DAT_803dfc24 + iVar2) = 0;
          *(undefined2 *)((int)&DAT_803dfbec + iVar2 + 2) = 0;
          *(undefined2 *)((int)puVar3 + 0x146) = 0;
          zz_0216f68_((int)puVar3);
        }
      }
      else {
        zz_0218a1c_((int)puVar3);
      }
      puVar3[7] = 0;
      puVar3[8] = 0;
      puVar3[10] = 0;
      puVar3[9] = 0;
      puVar3[0xc] = puVar3 + 0xd;
      puVar3 = (undefined4 *)*puVar3;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  DAT_8043676c = uVar5;
  for (puVar3 = (undefined4 *)zz_0216e08_(0); puVar3 != (undefined4 *)0x0;
      puVar3 = (undefined4 *)*puVar3) {
    if (puVar3[8] != 0) {
      zz_0218980_((int)(&DAT_803dfbe0 + puVar3[6] * 0x7a));
    }
    puVar3[8] = 0;
    *(undefined2 *)(&DAT_803dfc2c + puVar3[6] * 0xf4) = 0;
    *(undefined2 *)(&DAT_803dfc2a + puVar3[6] * 0xf4) = 0;
    *(undefined2 *)(&DAT_803dfc28 + puVar3[6] * 0xf4) = 0;
    *(undefined2 *)(&DAT_803dfc26 + puVar3[6] * 0xf4) = 0;
    *(undefined2 *)(&DAT_803dfc24 + puVar3[6] * 0xf4) = 0;
    *(undefined2 *)((int)&DAT_803dfbec + puVar3[6] * 0xf4 + 2) = 0;
  }
  gnt4_DCFlushRange_bl(0x803dfbe0,0x3d00);
  gnt4_DCFlushRange_bl(0x803e38e0,0x1000);
  gnt4_DCFlushRange_bl(0x803e48e0,0x4000);
  return;
}



// ==== 802193e0  zz_02193e0_ ====

undefined2 * zz_02193e0_(void)

{
  return &DAT_803dfbe0;
}



// ==== 802193ec  zz_02193ec_ ====

void zz_02193ec_(int param_1)

{
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x16e) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0xa4;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(int *)(param_1 + 0x30) = param_1 + 0x34;
  *(undefined2 *)(param_1 + 0x184) = 0;
  *(undefined2 *)(param_1 + 0x182) = 0;
  *(undefined2 *)(param_1 + 0x180) = 0;
  *(undefined2 *)(param_1 + 0x17e) = 0;
  *(undefined2 *)(param_1 + 0x17c) = 0;
  *(undefined2 *)(param_1 + 0x1f2) = 0;
  return;
}



// ==== 8021942c  zz_021942c_ ====

void zz_021942c_(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined4 *puVar4;
  uint uVar5;
  undefined *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  
  puVar8 = (undefined4 *)&DAT_803dfbe0;
  DAT_80436768 = DAT_800000f8 / 400;
  DAT_8043676c = 0;
  iVar9 = 0x1e8;
  puVar4 = puVar8;
  do {
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4 = puVar4 + 8;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  iVar9 = 0x80;
  puVar4 = &DAT_803e38e0;
  do {
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4 = puVar4 + 8;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  iVar9 = 0x458;
  puVar4 = &DAT_803e88e0;
  do {
    *puVar4 = 0;
    puVar4[1] = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    puVar4[4] = 0;
    puVar4[5] = 0;
    puVar4[6] = 0;
    puVar4[7] = 0;
    puVar4 = puVar4 + 8;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  puVar7 = &DAT_803e38e0;
  puVar6 = &DAT_803e48e0;
  uVar5 = 0;
  puVar4 = &DAT_803e88e0;
  do {
    puVar4[6] = uVar5;
    puVar4[0xc] = puVar4 + 0xd;
    puVar4[0x4d] = puVar7;
    *(undefined2 *)((int)puVar4 + 0x146) = 0;
    *(undefined2 *)((int)puVar4 + 0x16e) = 0;
    puVar4[7] = 0xa4;
    puVar4[10] = 0;
    puVar4[9] = 0;
    puVar4[0xc] = puVar4 + 0xd;
    *(undefined2 *)(puVar4 + 0x61) = 0;
    *(undefined2 *)((int)puVar4 + 0x182) = 0;
    *(undefined2 *)(puVar4 + 0x60) = 0;
    *(undefined2 *)((int)puVar4 + 0x17e) = 0;
    *(undefined2 *)(puVar4 + 0x5f) = 0;
    *(undefined2 *)((int)puVar4 + 0x1f2) = 0;
    if (uVar5 == 0x3f) {
      *(undefined2 *)((int)puVar8 + 2) = 0;
      *(undefined2 *)puVar8 = 0;
      *(undefined2 *)((int)puVar4 + 0x13a) = 0;
      *(undefined2 *)(puVar4 + 0x4e) = 0;
    }
    else {
      puVar4[0x4e] = puVar8 + 0x3d;
      *puVar8 = puVar8 + 0x3d;
    }
    uVar1 = (undefined2)((uint)puVar8 >> 0x10);
    *(undefined2 *)(puVar4 + 0x4f) = uVar1;
    uVar2 = (undefined2)((uint)puVar7 >> 0x10);
    uVar3 = (undefined2)((uint)puVar6 >> 0x10);
    *(short *)((int)puVar4 + 0x13e) = (short)puVar8;
    *(undefined2 *)(puVar8 + 1) = uVar1;
    *(short *)((int)puVar8 + 6) = (short)puVar8;
    *(undefined2 *)(puVar4 + 0x5c) = uVar2;
    *(short *)((int)puVar4 + 0x172) = (short)puVar7;
    *(undefined2 *)(puVar8 + 0xe) = uVar2;
    *(short *)((int)puVar8 + 0x3a) = (short)puVar7;
    *(undefined2 *)((int)puVar4 + 0x186) = uVar3;
    *(short *)(puVar4 + 0x62) = (short)puVar6;
    *(undefined2 *)((int)puVar8 + 0x4e) = uVar3;
    *(short *)(puVar8 + 0x14) = (short)puVar6;
    puVar4[3] = 1;
    zz_0216f48_(puVar4);
    uVar5 = uVar5 + 1;
    puVar8 = puVar8 + 0x3d;
    puVar7 = puVar7 + 0x10;
    puVar6 = puVar6 + 0x100;
    puVar4 = puVar4 + 0x8b;
  } while (uVar5 < 0x40);
  gnt4_DCFlushRange_bl(0x803dfbe0,0x3d00);
  return;
}



// ==== 8021962c  zz_021962c_ ====

void zz_021962c_(int param_1,int param_2)

{
  gnt4_OSDisableInterrupts_bl();
  if (param_2 == 2) {
    *(undefined2 *)(param_1 + 0x140) = 0;
    *(undefined2 *)(param_1 + 0x142) = 0;
  }
  else if (param_2 < 2) {
    if (param_2 == 0) {
      *(undefined2 *)(param_1 + 0x140) = 2;
    }
    else if (-1 < param_2) {
      *(undefined2 *)(param_1 + 0x140) = 1;
    }
  }
  else if (param_2 == 4) {
    *(undefined2 *)(param_1 + 0x140) = 0;
    *(undefined2 *)(param_1 + 0x142) = 2;
  }
  else if (param_2 < 4) {
    *(undefined2 *)(param_1 + 0x140) = 0;
    *(undefined2 *)(param_1 + 0x142) = 1;
  }
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 1;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802196f0  zz_02196f0_ ====

void zz_02196f0_(int param_1,short param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(short *)(param_1 + 0x146) = param_2;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 4;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x20) = 1;
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8021974c  zz_021974c_ ====

void zz_021974c_(int param_1,undefined2 param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined2 *)(param_1 + 0x148) = param_2;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 8;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219798  zz_0219798_ ====

void zz_0219798_(int param_1,short *param_2)

{
  short sVar1;
  ushort uVar2;
  
  gnt4_OSDisableInterrupts_bl();
  sVar1 = *param_2;
  *(short *)(param_1 + 0x14a) = sVar1;
  uVar2 = (ushort)(sVar1 != 0);
  sVar1 = param_2[1];
  *(short *)(param_1 + 0x14c) = sVar1;
  if (sVar1 != 0) {
    uVar2 = 9;
  }
  sVar1 = param_2[2];
  *(short *)(param_1 + 0x14e) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 2;
  }
  sVar1 = param_2[3];
  *(short *)(param_1 + 0x150) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 10;
  }
  sVar1 = param_2[4];
  *(short *)(param_1 + 0x152) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x10;
  }
  sVar1 = param_2[5];
  *(short *)(param_1 + 0x154) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x50;
  }
  sVar1 = param_2[6];
  *(short *)(param_1 + 0x156) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x20;
  }
  sVar1 = param_2[7];
  *(short *)(param_1 + 0x158) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x60;
  }
  sVar1 = param_2[8];
  *(short *)(param_1 + 0x15a) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x200;
  }
  sVar1 = param_2[9];
  *(short *)(param_1 + 0x15c) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0xa00;
  }
  sVar1 = param_2[10];
  *(short *)(param_1 + 0x15e) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x400;
  }
  sVar1 = param_2[0xb];
  *(short *)(param_1 + 0x160) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0xc00;
  }
  sVar1 = param_2[0xc];
  *(short *)(param_1 + 0x162) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x1000;
  }
  sVar1 = param_2[0xd];
  *(short *)(param_1 + 0x164) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x3000;
  }
  sVar1 = param_2[0xe];
  *(short *)(param_1 + 0x166) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 4;
  }
  sVar1 = param_2[0xf];
  *(short *)(param_1 + 0x168) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0xc;
  }
  sVar1 = param_2[0x10];
  *(short *)(param_1 + 0x16a) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x80;
  }
  sVar1 = param_2[0x11];
  *(short *)(param_1 + 0x16c) = sVar1;
  if (sVar1 != 0) {
    uVar2 = uVar2 | 0x180;
  }
  *(ushort *)(param_1 + 0x144) = uVar2;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x12;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802199ec  zz_02199ec_ ====

void zz_02199ec_(int param_1,undefined2 *param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined2 *)(param_1 + 0x19c) = *param_2;
  *(undefined2 *)(param_1 + 0x19e) = param_2[1];
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x200;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219a44  zz_0219a44_ ====

void zz_0219a44_(int param_1,undefined4 *param_2)

{
  ushort uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  *(undefined4 *)(param_1 + 0x1a6) = *param_2;
  *(undefined4 *)(param_1 + 0x1aa) = param_2[1];
  *(undefined4 *)(param_1 + 0x1ae) = param_2[2];
  *(undefined4 *)(param_1 + 0x1b2) = param_2[3];
  uVar1 = *(ushort *)((int)param_2 + 2);
  if (uVar1 == 10) {
    *(undefined4 *)(param_1 + 0x1b6) = 0;
    *(undefined4 *)(param_1 + 0x1ba) = 0;
    *(undefined4 *)(param_1 + 0x1be) = 0;
    *(undefined4 *)(param_1 + 0x1c2) = 0;
    *(undefined4 *)(param_1 + 0x1c6) = 0;
    *(undefined4 *)(param_1 + 0x1ca) = 0;
    *(undefined4 *)(param_1 + 0x1ce) = 0;
    *(undefined4 *)(param_1 + 0x1d2) = 0;
    *(undefined4 *)(param_1 + 0x1d6) = 0x8000000;
    *(undefined4 *)(param_1 + 0x1da) = 0;
  }
  else if ((9 < uVar1) && (uVar1 == 0x19)) {
    *(undefined4 *)(param_1 + 0x1b6) = 0;
    *(undefined4 *)(param_1 + 0x1ba) = 0;
    *(undefined4 *)(param_1 + 0x1be) = 0;
    *(undefined4 *)(param_1 + 0x1c2) = 0;
    *(undefined4 *)(param_1 + 0x1c6) = 0;
    *(undefined4 *)(param_1 + 0x1ca) = 0;
    *(undefined4 *)(param_1 + 0x1ce) = 0;
    *(undefined4 *)(param_1 + 0x1d2) = 0;
    *(undefined4 *)(param_1 + 0x1d6) = 0x1000000;
    *(undefined4 *)(param_1 + 0x1da) = 0;
  }
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfffe1fff;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x21000;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219b54  zz_0219b54_ ====

void zz_0219b54_(int param_1,undefined4 *param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined4 *)(param_1 + 0x1b6) = *param_2;
  *(undefined4 *)(param_1 + 0x1ba) = param_2[1];
  *(undefined4 *)(param_1 + 0x1be) = param_2[2];
  *(undefined4 *)(param_1 + 0x1c2) = param_2[3];
  *(undefined4 *)(param_1 + 0x1c6) = param_2[4];
  *(undefined4 *)(param_1 + 0x1ca) = param_2[5];
  *(undefined4 *)(param_1 + 0x1ce) = param_2[6];
  *(undefined4 *)(param_1 + 0x1d2) = param_2[7];
  *(undefined4 *)(param_1 + 0x1d6) = param_2[8];
  *(undefined4 *)(param_1 + 0x1da) = param_2[9];
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x20000;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219bf8  zz_0219bf8_ ====

void zz_0219bf8_(int param_1,undefined2 *param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined2 *)(param_1 + 0x1de) = *param_2;
  *(undefined2 *)(param_1 + 0x1e0) = param_2[1];
  *(undefined2 *)(param_1 + 0x1e2) = param_2[2];
  *(undefined2 *)(param_1 + 0x1e4) = param_2[3];
  *(undefined2 *)(param_1 + 0x1e6) = param_2[4];
  *(undefined2 *)(param_1 + 0x1e8) = param_2[5];
  *(undefined2 *)(param_1 + 0x1ea) = param_2[6];
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) & 0xfff7ffff;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x40000;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219c90  zz_0219c90_ ====

void zz_0219c90_(double param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  gnt4_OSDisableInterrupts_bl();
  dVar3 = (double)(float)((double)FLOAT_8043caf0 * param_1);
  iVar1 = gnt4___cvt_fp2unsigned_bl(dVar3);
  uVar2 = gnt4___cvt_fp2unsigned_bl(dVar3);
  if (0x40000 < uVar2) {
    iVar1 = 0x40000;
  }
  *(short *)(param_2 + 0x1de) = (short)((uint)iVar1 >> 0x10);
  *(short *)(param_2 + 0x1e0) = (short)iVar1;
  *(uint *)(param_2 + 0x1c) = *(uint *)(param_2 + 0x1c) | 0x80000;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219d28  zz_0219d28_ ====

void zz_0219d28_(int param_1,undefined2 *param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined2 *)(param_1 + 0x1ec) = *param_2;
  *(undefined2 *)(param_1 + 0x1ee) = param_2[1];
  *(undefined2 *)(param_1 + 0x1f0) = param_2[2];
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x100000;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80219d94  zz_0219d94_ ====

undefined4 zz_0219d94_(void)

{
  return DAT_80436768;
}



// ==== 80219d9c  zz_0219d9c_ ====

undefined4 zz_0219d9c_(void)

{
  return DAT_8043676c;
}



// ==== 80219da4  zz_0219da4_ ====

int zz_0219da4_(void)

{
  int iVar1;
  
  if (DAT_80436784 != 0) {
    iVar1 = DAT_80436780 * 0x38;
    DAT_80436780 = (DAT_80436780 + 1U) - ((DAT_80436780 + 1U) / DAT_8043677c) * DAT_8043677c;
    return DAT_80436778 + iVar1;
  }
  return 0;
}



// ==== 80219dec  zz_0219dec_ ====

void zz_0219dec_(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 9; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0xc) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0xc) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 9; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0xc0) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0xc0) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  if (*(int *)(param_1 + 0x1a4) != 0) {
    for (bVar1 = 0; bVar1 < 3; bVar1 = bVar1 + 1) {
      if (*(int *)(param_1 + 0x1ac) != 0) {
        (*DAT_80435d44)();
        *(undefined4 *)(param_1 + 0x1ac) = 0;
      }
      param_1 = param_1 + 4;
    }
  }
  return;
}



// ==== 80219f10  zz_0219f10_ ====

undefined4 zz_0219f10_(int param_1)

{
  gnt4_OSDisableInterrupts_bl();
  zz_0219dec_(param_1);
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 80219f5c  zz_0219f5c_ ====

void zz_0219f5c_(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 6; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0xc) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0xc) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 6; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0x84) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0x84) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  if (*(int *)(param_1 + 0x120) != 0) {
    for (bVar1 = 0; bVar1 < 3; bVar1 = bVar1 + 1) {
      if (*(int *)(param_1 + 0x124) != 0) {
        (*DAT_80435d44)();
        *(undefined4 *)(param_1 + 0x124) = 0;
      }
      param_1 = param_1 + 4;
    }
  }
  return;
}



// ==== 8021a080  zz_021a080_ ====

undefined4 zz_021a080_(int param_1)

{
  gnt4_OSDisableInterrupts_bl();
  zz_0219f5c_(param_1);
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8021a0cc  zz_021a0cc_ ====

undefined4 zz_021a0cc_(undefined4 *param_1)

{
  ulonglong uVar1;
  
  uVar1 = gnt4_OSDisableInterrupts_bl();
  (*DAT_80435d44)(*param_1,(int)uVar1);
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8021a11c  zz_021a11c_ ====

undefined4 zz_021a11c_(int param_1)

{
  ulonglong uVar1;
  
  uVar1 = gnt4_OSDisableInterrupts_bl();
  if (*(int *)(param_1 + 0x30) != 0) {
    (*DAT_80435d44)(*(int *)(param_1 + 0x30),(int)uVar1);
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    (*DAT_80435d44)();
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    (*DAT_80435d44)();
  }
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8021a1bc  FUN_8021a1bc ====

void FUN_8021a1bc(int param_1)

{
  gnt4_OSAllocFromHeap_bl(DAT_80435c60,param_1);
  return;
}



// ==== 8021a1e4  FUN_8021a1e4 ====

void FUN_8021a1e4(int param_1)

{
  gnt4_OSFreeToHeap_bl(DAT_80435c60,param_1);
  return;
}



// ==== 8021a20c  zz_021a20c_ ====

void zz_021a20c_(undefined4 param_1,undefined4 param_2)

{
  DAT_80435d40 = param_1;
  DAT_80435d44 = param_2;
  return;
}



// ==== 8021a218  zz_021a218_ ====

void zz_021a218_(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 0xc; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0xc) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0xc) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 0xc; bVar1 = bVar1 + 1) {
    if (*(int *)(iVar2 + 0xfc) != 0) {
      (*DAT_80435d44)();
      *(undefined4 *)(iVar2 + 0xfc) = 0;
    }
    iVar2 = iVar2 + 0x14;
  }
  if (*(int *)(param_1 + 0x22c) != 0) {
    for (bVar1 = 0; bVar1 < 4; bVar1 = bVar1 + 1) {
      if (*(int *)(param_1 + 0x234) != 0) {
        (*DAT_80435d44)();
        *(undefined4 *)(param_1 + 0x234) = 0;
      }
      param_1 = param_1 + 4;
    }
  }
  return;
}



// ==== 8021a33c  zz_021a33c_ ====

undefined4 zz_021a33c_(int param_1)

{
  gnt4_OSDisableInterrupts_bl();
  zz_021a218_(param_1);
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8021a388  zz_021a388_ ====

void zz_021a388_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_1 + 0x14);
  iVar3 = *(int *)(param_1 + 0x18);
  if (DAT_80436790 == 3) {
    iVar1 = (0x7f - iVar2) * 2;
    *(int *)(param_1 + 0x20) = (int)*(short *)(&DAT_803a9f0c + iVar2 * 2);
    *(int *)(param_1 + 0x24) = (int)*(short *)(&DAT_803a9f0c + iVar1);
    *(int *)(param_1 + 0x28) = (int)*(short *)(&DAT_803a9f0c + (0x7f - iVar3) * 2);
    *(int *)(param_1 + 0x2c) = (int)*(short *)(&DAT_803a9f0c + iVar3 * 2);
    *(int *)(param_1 + 0x30) = (int)*(short *)(&DAT_803aa00c + iVar1);
    *(int *)(param_1 + 0x34) = (int)*(short *)(&DAT_803aa00c + iVar2 * 2);
    return;
  }
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(&DAT_803a9d0c + iVar2 * 4);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(&DAT_803a9d0c + (0x7f - iVar2) * 4);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(&DAT_803a9d0c + (0x7f - iVar3) * 4);
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(&DAT_803a9d0c + iVar3 * 4);
  return;
}



// ==== 8021a444  zz_021a444_ ====

void zz_021a444_(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_803f13e0;
  iVar1 = 0;
  do {
    puVar2[1] = 0x50000000;
    puVar2[2] = 0;
    puVar2[3] = 0xfffffc40;
    puVar2[4] = 0xfffffc40;
    puVar2[7] = 0;
    puVar2[5] = 0x40;
    puVar2[6] = 0x7f;
    *(undefined2 *)(puVar2 + 0x17) = 0;
    *(undefined2 *)(puVar2 + 0x16) = 0;
    *(undefined2 *)(puVar2 + 0x15) = 0;
    *(undefined2 *)(puVar2 + 0x14) = 0;
    *(undefined2 *)(puVar2 + 0x13) = 0;
    *(undefined2 *)(puVar2 + 0x12) = 0;
    *(undefined2 *)(puVar2 + 0x11) = 0;
    *(undefined2 *)(puVar2 + 0x10) = 0;
    *(undefined2 *)(puVar2 + 0xf) = 0;
    *(undefined2 *)(puVar2 + 0xe) = 0;
    zz_021a388_((int)puVar2);
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0x18;
  } while (iVar1 < 0x40);
  DAT_80436788 = 0;
  DAT_8043678c = 0;
  DAT_80436790 = 1;
  return;
}



// ==== 8021a50c  zz_021a50c_ ====

void zz_021a50c_(undefined4 param_1)

{
  DAT_80436790 = param_1;
  return;
}



// ==== 8021a514  zz_021a514_ ====

undefined4 zz_021a514_(void)

{
  return DAT_80436790;
}



// ==== 8021a51c  zz_021a51c_ ====

void zz_021a51c_(int param_1,uint param_2,int param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  short sVar1;
  int iVar2;
  undefined2 uVar4;
  int iVar3;
  int iVar5;
  ushort uVar6;
  
  iVar2 = *(int *)(param_1 + 0x18);
  iVar5 = iVar2 * 0x60;
  (&DAT_803f13e0)[iVar2 * 0x18] = param_1;
  (&DAT_803f13e4)[iVar2 * 0x18] = param_2 & 7;
  (&DAT_803f13e8)[iVar2 * 0x18] = param_3;
  (&DAT_803f13ec)[iVar2 * 0x18] = param_4;
  (&DAT_803f13f0)[iVar2 * 0x18] = param_5;
  (&DAT_803f13f4)[iVar2 * 0x18] = param_6;
  (&DAT_803f13f8)[iVar2 * 0x18] = param_7;
  (&DAT_803f13fc)[iVar2 * 0x18] = param_8;
  zz_021a388_((int)(&DAT_803f13e0 + iVar2 * 0x18));
  if (((&DAT_803f13e4)[iVar2 * 0x18] & 4) == 0) {
    if (param_3 < -0x387) {
      uVar4 = 0;
    }
    else if (param_3 < 0x3c) {
      uVar4 = *(undefined2 *)(&DAT_803a9c90 + param_3 * 2);
    }
    else {
      uVar4 = 0xff64;
    }
    (&DAT_803f1418)[iVar2 * 0x30] = uVar4;
  }
  else {
    (&DAT_803f1418)[iVar2 * 0x30] = 0;
  }
  uVar6 = 0;
  if (DAT_80436790 == 3) {
    iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
            (&DAT_803f1400)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
    if (iVar3 < -0x387) {
      uVar4 = 0;
    }
    else if (iVar3 < 0x3c) {
      uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
    }
    else {
      uVar4 = 0xff64;
    }
    (&DAT_803f141c)[iVar2 * 0x30] = uVar4;
    iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
            (&DAT_803f1404)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
    if (iVar3 < -0x387) {
      uVar4 = 0;
    }
    else if (iVar3 < 0x3c) {
      uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
    }
    else {
      uVar4 = 0xff64;
    }
    (&DAT_803f1420)[iVar2 * 0x30] = uVar4;
    iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
            *(int *)(&DAT_803f1410 + iVar5) + (&DAT_803f140c)[iVar2 * 0x18];
    if (iVar3 < -0x387) {
      uVar4 = 0;
    }
    else if (iVar3 < 0x3c) {
      uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
    }
    else {
      uVar4 = 0xff64;
    }
    (&DAT_803f1434)[iVar2 * 0x30] = uVar4;
    iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
            *(int *)(&DAT_803f1414 + iVar5) + (&DAT_803f140c)[iVar2 * 0x18];
    if (iVar3 < -0x387) {
      uVar4 = 0;
    }
    else if (iVar3 < 0x3c) {
      uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
    }
    else {
      uVar4 = 0xff64;
    }
    (&DAT_803f1438)[iVar2 * 0x30] = uVar4;
    if (((&DAT_803f13e4)[iVar2 * 0x18] & 1) == 0) {
      iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1400)[iVar2 * 0x18] +
              (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
      iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1404)[iVar2 * 0x18] +
              (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
      iVar3 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f13ec)[iVar2 * 0x18] + *(int *)(&DAT_803f1410 + iVar5) +
              (&DAT_803f140c)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f13ec)[iVar2 * 0x18] + *(int *)(&DAT_803f1414 + iVar5) +
              (&DAT_803f140c)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
    }
    else {
      iVar3 = (&DAT_803f13ec)[iVar2 * 0x18] +
              (&DAT_803f1400)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
      iVar3 = (&DAT_803f13ec)[iVar2 * 0x18] +
              (&DAT_803f1404)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
      iVar3 = (&DAT_803f13ec)[iVar2 * 0x18] +
              *(int *)(&DAT_803f1410 + iVar5) + (&DAT_803f140c)[iVar2 * 0x18];
      if (iVar3 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar3 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar3 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] +
              *(int *)(&DAT_803f1414 + iVar5) + (&DAT_803f140c)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
    }
    uVar6 = 0x4000;
  }
  else if (DAT_80436790 < 3) {
    if (DAT_80436790 == 0) {
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f141c)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1420)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1424)[iVar2 * 0x30] = uVar4;
      if (((&DAT_803f13e4)[iVar2 * 0x18] & 1) == 0) {
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      }
      else {
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      }
      if (((&DAT_803f13e4)[iVar2 * 0x18] & 2) == 0) {
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1434)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1438)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
      }
      else {
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1434)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1438)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
      }
    }
    else if (-1 < DAT_80436790) {
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f1400)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f141c)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
              (&DAT_803f1404)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1420)[iVar2 * 0x30] = uVar4;
      iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
      if (iVar5 < -0x387) {
        uVar4 = 0;
      }
      else if (iVar5 < 0x3c) {
        uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
      }
      else {
        uVar4 = 0xff64;
      }
      (&DAT_803f1424)[iVar2 * 0x30] = uVar4;
      if (((&DAT_803f13e4)[iVar2 * 0x18] & 1) == 0) {
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1400)[iVar2 * 0x18] +
                (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f1404)[iVar2 * 0x18] +
                (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      }
      else {
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] +
                (&DAT_803f1400)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1428)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] +
                (&DAT_803f1404)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f142c)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13ec)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1430)[iVar2 * 0x30] = uVar4;
      }
      if (((&DAT_803f13e4)[iVar2 * 0x18] & 2) == 0) {
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1400)[iVar2 * 0x18] +
                (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1434)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f1404)[iVar2 * 0x18] +
                (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1438)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13fc)[iVar2 * 0x18] +
                (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
      }
      else {
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] +
                (&DAT_803f1400)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1434)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] +
                (&DAT_803f1404)[iVar2 * 0x18] + (&DAT_803f1408)[iVar2 * 0x18];
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f1438)[iVar2 * 0x30] = uVar4;
        iVar5 = (&DAT_803f13f0)[iVar2 * 0x18] + (&DAT_803f140c)[iVar2 * 0x18] + -0x1e;
        if (iVar5 < -0x387) {
          uVar4 = 0;
        }
        else if (iVar5 < 0x3c) {
          uVar4 = *(undefined2 *)(&DAT_803a9c90 + iVar5 * 2);
        }
        else {
          uVar4 = 0xff64;
        }
        (&DAT_803f143c)[iVar2 * 0x30] = uVar4;
      }
    }
  }
  gnt4_OSDisableInterrupts_bl();
  *(undefined2 *)(param_1 + 0x19c) = (&DAT_803f1418)[iVar2 * 0x30];
  *(undefined2 *)(param_1 + 0x19e) = 0;
  sVar1 = (&DAT_803f141c)[iVar2 * 0x30];
  *(short *)(param_1 + 0x14a) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 1;
  }
  *(undefined2 *)(param_1 + 0x14c) = 0;
  sVar1 = (&DAT_803f1420)[iVar2 * 0x30];
  *(short *)(param_1 + 0x14e) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 2;
  }
  *(undefined2 *)(param_1 + 0x150) = 0;
  sVar1 = (&DAT_803f1428)[iVar2 * 0x30];
  *(short *)(param_1 + 0x152) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x10;
  }
  *(undefined2 *)(param_1 + 0x154) = 0;
  sVar1 = (&DAT_803f142c)[iVar2 * 0x30];
  *(short *)(param_1 + 0x156) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x20;
  }
  *(undefined2 *)(param_1 + 0x158) = 0;
  sVar1 = (&DAT_803f1434)[iVar2 * 0x30];
  *(short *)(param_1 + 0x15a) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x200;
  }
  *(undefined2 *)(param_1 + 0x15c) = 0;
  sVar1 = (&DAT_803f1438)[iVar2 * 0x30];
  *(short *)(param_1 + 0x15e) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x400;
  }
  *(undefined2 *)(param_1 + 0x160) = 0;
  sVar1 = (&DAT_803f143c)[iVar2 * 0x30];
  *(short *)(param_1 + 0x162) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x1000;
  }
  *(undefined2 *)(param_1 + 0x164) = 0;
  sVar1 = (&DAT_803f1424)[iVar2 * 0x30];
  *(short *)(param_1 + 0x166) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 4;
  }
  *(undefined2 *)(param_1 + 0x168) = 0;
  sVar1 = (&DAT_803f1430)[iVar2 * 0x30];
  *(short *)(param_1 + 0x16a) = sVar1;
  if (sVar1 != 0) {
    uVar6 = uVar6 | 0x80;
  }
  *(undefined2 *)(param_1 + 0x16c) = 0;
  *(ushort *)(param_1 + 0x144) = uVar6;
  *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x212;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8021b398  zz_021b398_ ====

void zz_021b398_(int param_1)

{
  (&DAT_803f13e0)[*(int *)(param_1 + 0x18) * 0x18] = 0;
  return;
}



// ==== 8021b3b8  zz_021b3b8_ ====

void zz_021b3b8_(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  (&DAT_803f13e8)[iVar1 * 0x18] = param_2;
  (&DAT_803f13e4)[iVar1 * 0x18] = (&DAT_803f13e4)[iVar1 * 0x18] | 0x10000000;
  return;
}



// ==== 8021b3e0  zz_021b3e0_ ====

void zz_021b3e0_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (param_2 < 0) {
    param_2 = 0;
  }
  else if (0x7f < param_2) {
    param_2 = 0x7f;
  }
  (&DAT_803f13f4)[iVar1 * 0x18] = param_2;
  zz_021a388_((int)(&DAT_803f13e0 + iVar1 * 0x18));
  (&DAT_803f13e4)[iVar1 * 0x18] = (&DAT_803f13e4)[iVar1 * 0x18] | 0x40000000;
  return;
}



// ==== 8021b44c  zz_021b44c_ ====

void zz_021b44c_(void)

{
  bool bVar1;
  byte *pbVar2;
  short sVar3;
  bool bVar4;
  int *piVar5;
  int iVar6;
  undefined2 uVar8;
  int iVar7;
  ushort uVar9;
  uint uVar10;
  int iVar11;
  
  piVar5 = &DAT_803f13e0;
  iVar11 = 0x40;
  do {
    iVar6 = *piVar5;
    if (iVar6 != 0) {
      uVar9 = 0;
      bVar4 = (piVar5[1] & 0x20000000U) != 0;
      if (bVar4) {
        *(undefined2 *)(piVar5 + 0xe) = *(undefined2 *)((int)piVar5 + 0x3a);
        piVar5[1] = piVar5[1] & 0xdfffffff;
      }
      if ((piVar5[1] & 0x10000000U) != 0) {
        if ((piVar5[1] & 4U) == 0) {
          iVar7 = piVar5[2];
          if (iVar7 < -0x387) {
            uVar8 = 0;
          }
          else if (iVar7 < 0x3c) {
            uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
          }
          else {
            uVar8 = 0xff64;
          }
          *(undefined2 *)((int)piVar5 + 0x3a) = uVar8;
        }
        else {
          *(undefined2 *)((int)piVar5 + 0x3a) = 0;
        }
        bVar4 = true;
        piVar5[1] = piVar5[1] & 0xefffffff;
        piVar5[1] = piVar5[1] | 0x20000000;
      }
      bVar1 = (piVar5[1] & 0x80000000U) != 0;
      if (bVar1) {
        *(undefined2 *)(piVar5 + 0xf) = *(undefined2 *)((int)piVar5 + 0x3e);
        *(undefined2 *)(piVar5 + 0x10) = *(undefined2 *)((int)piVar5 + 0x42);
        *(undefined2 *)(piVar5 + 0x11) = *(undefined2 *)((int)piVar5 + 0x46);
        *(undefined2 *)(piVar5 + 0x12) = *(undefined2 *)((int)piVar5 + 0x4a);
        *(undefined2 *)(piVar5 + 0x13) = *(undefined2 *)((int)piVar5 + 0x4e);
        *(undefined2 *)(piVar5 + 0x14) = *(undefined2 *)((int)piVar5 + 0x52);
        *(undefined2 *)(piVar5 + 0x15) = *(undefined2 *)((int)piVar5 + 0x56);
        *(undefined2 *)(piVar5 + 0x16) = *(undefined2 *)((int)piVar5 + 0x5a);
        *(undefined2 *)(piVar5 + 0x17) = *(undefined2 *)((int)piVar5 + 0x5e);
        piVar5[1] = piVar5[1] & 0x7fffffff;
      }
      if ((piVar5[1] & 0x40000000U) != 0) {
        if (DAT_80436790 == 3) {
          iVar7 = piVar5[7] + piVar5[8] + piVar5[10];
          if (iVar7 < -0x387) {
            uVar8 = 0;
          }
          else if (iVar7 < 0x3c) {
            uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
          }
          else {
            uVar8 = 0xff64;
          }
          *(undefined2 *)((int)piVar5 + 0x3e) = uVar8;
          iVar7 = piVar5[7] + piVar5[9] + piVar5[10];
          if (iVar7 < -0x387) {
            uVar8 = 0;
          }
          else if (iVar7 < 0x3c) {
            uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
          }
          else {
            uVar8 = 0xff64;
          }
          *(undefined2 *)((int)piVar5 + 0x42) = uVar8;
          iVar7 = piVar5[7] + piVar5[0xc] + piVar5[0xb];
          if (iVar7 < -0x387) {
            uVar8 = 0;
          }
          else if (iVar7 < 0x3c) {
            uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
          }
          else {
            uVar8 = 0xff64;
          }
          *(undefined2 *)((int)piVar5 + 0x56) = uVar8;
          iVar7 = piVar5[7] + piVar5[0xd] + piVar5[0xb];
          if (iVar7 < -0x387) {
            uVar8 = 0;
          }
          else if (iVar7 < 0x3c) {
            uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
          }
          else {
            uVar8 = 0xff64;
          }
          *(undefined2 *)((int)piVar5 + 0x5a) = uVar8;
          if ((piVar5[1] & 1U) == 0) {
            iVar7 = piVar5[7] + piVar5[3] + piVar5[8] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
            iVar7 = piVar5[7] + piVar5[3] + piVar5[9] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
            iVar7 = piVar5[7] + piVar5[3] + piVar5[0xc] + piVar5[0xb];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            iVar7 = piVar5[7] + piVar5[3] + piVar5[0xd] + piVar5[0xb];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
          }
          else {
            iVar7 = piVar5[3] + piVar5[8] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
            iVar7 = piVar5[3] + piVar5[9] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
            iVar7 = piVar5[3] + piVar5[0xc] + piVar5[0xb];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            iVar7 = piVar5[3] + piVar5[0xd] + piVar5[0xb];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
          }
          uVar9 = 0x4000;
        }
        else if (DAT_80436790 < 3) {
          if (DAT_80436790 == 0) {
            iVar7 = piVar5[7] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x3e) = uVar8;
            iVar7 = piVar5[7] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x42) = uVar8;
            iVar7 = piVar5[7] + piVar5[0xb] + -0x1e;
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x46) = uVar8;
            if ((piVar5[1] & 1U) == 0) {
              iVar7 = piVar5[7] + piVar5[3] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
              iVar7 = piVar5[7] + piVar5[3] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
              iVar7 = piVar5[7] + piVar5[3] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            }
            else {
              iVar7 = piVar5[3] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
              iVar7 = piVar5[3] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
              iVar7 = piVar5[3] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            }
            if ((piVar5[1] & 2U) == 0) {
              iVar7 = piVar5[7] + piVar5[4] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x56) = uVar8;
              iVar7 = piVar5[7] + piVar5[4] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5a) = uVar8;
              iVar7 = piVar5[7] + piVar5[4] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
            }
            else {
              iVar7 = piVar5[4] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x56) = uVar8;
              iVar7 = piVar5[4] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5a) = uVar8;
              iVar7 = piVar5[4] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
            }
          }
          else if (-1 < DAT_80436790) {
            iVar7 = piVar5[7] + piVar5[8] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x3e) = uVar8;
            iVar7 = piVar5[7] + piVar5[9] + piVar5[10];
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x42) = uVar8;
            iVar7 = piVar5[7] + piVar5[0xb] + -0x1e;
            if (iVar7 < -0x387) {
              uVar8 = 0;
            }
            else if (iVar7 < 0x3c) {
              uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
            }
            else {
              uVar8 = 0xff64;
            }
            *(undefined2 *)((int)piVar5 + 0x46) = uVar8;
            if ((piVar5[1] & 1U) == 0) {
              iVar7 = piVar5[7] + piVar5[3] + piVar5[8] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
              iVar7 = piVar5[7] + piVar5[3] + piVar5[9] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
              iVar7 = piVar5[7] + piVar5[3] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            }
            else {
              iVar7 = piVar5[3] + piVar5[8] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4a) = uVar8;
              iVar7 = piVar5[3] + piVar5[9] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x4e) = uVar8;
              iVar7 = piVar5[3] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x52) = uVar8;
            }
            if ((piVar5[1] & 2U) == 0) {
              iVar7 = piVar5[7] + piVar5[4] + piVar5[8] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x56) = uVar8;
              iVar7 = piVar5[7] + piVar5[4] + piVar5[9] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5a) = uVar8;
              iVar7 = piVar5[7] + piVar5[4] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
            }
            else {
              iVar7 = piVar5[4] + piVar5[8] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x56) = uVar8;
              iVar7 = piVar5[4] + piVar5[9] + piVar5[10];
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5a) = uVar8;
              iVar7 = piVar5[4] + piVar5[0xb] + -0x1e;
              if (iVar7 < -0x387) {
                uVar8 = 0;
              }
              else if (iVar7 < 0x3c) {
                uVar8 = *(undefined2 *)(&DAT_803a9c90 + iVar7 * 2);
              }
              else {
                uVar8 = 0xff64;
              }
              *(undefined2 *)((int)piVar5 + 0x5e) = uVar8;
            }
          }
        }
        bVar1 = true;
        piVar5[1] = piVar5[1] & 0xbfffffff;
        piVar5[1] = piVar5[1] | 0x80000000;
      }
      if (bVar4) {
        *(undefined2 *)(iVar6 + 0x19c) = *(undefined2 *)(piVar5 + 0xe);
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x3a) - (uint)*(ushort *)(piVar5 + 0xe);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x19e) = (short)iVar7 - (short)(iVar7 >> 0x1f);
        *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x200;
      }
      if (bVar1) {
        sVar3 = *(short *)(piVar5 + 0xf);
        *(short *)(iVar6 + 0x14a) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 1;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x3e) - (uint)*(ushort *)(piVar5 + 0xf);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x14c) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 8;
        }
        sVar3 = *(short *)(piVar5 + 0x10);
        *(short *)(iVar6 + 0x14e) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 2;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x42) - (uint)*(ushort *)(piVar5 + 0x10);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x150) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 8;
        }
        sVar3 = *(short *)(piVar5 + 0x12);
        *(short *)(iVar6 + 0x152) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x10;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x4a) - (uint)*(ushort *)(piVar5 + 0x12);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x154) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x40;
        }
        sVar3 = *(short *)(piVar5 + 0x13);
        *(short *)(iVar6 + 0x156) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x20;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x4e) - (uint)*(ushort *)(piVar5 + 0x13);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x158) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x40;
        }
        sVar3 = *(short *)(piVar5 + 0x15);
        *(short *)(iVar6 + 0x15a) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x200;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x56) - (uint)*(ushort *)(piVar5 + 0x15);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x15c) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x800;
        }
        sVar3 = *(short *)(piVar5 + 0x16);
        *(short *)(iVar6 + 0x15e) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x400;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x5a) - (uint)*(ushort *)(piVar5 + 0x16);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x160) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x800;
        }
        sVar3 = *(short *)(piVar5 + 0x17);
        *(short *)(iVar6 + 0x162) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x1000;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x5e) - (uint)*(ushort *)(piVar5 + 0x17);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x164) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x2000;
        }
        sVar3 = *(short *)(piVar5 + 0x11);
        *(short *)(iVar6 + 0x166) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 4;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x46) - (uint)*(ushort *)(piVar5 + 0x11);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x168) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 8;
        }
        sVar3 = *(short *)(piVar5 + 0x14);
        *(short *)(iVar6 + 0x16a) = sVar3;
        if (sVar3 != 0) {
          uVar9 = uVar9 | 0x80;
        }
        iVar7 = (uint)*(ushort *)((int)piVar5 + 0x52) - (uint)*(ushort *)(piVar5 + 0x14);
        iVar7 = iVar7 / 0xa0 + (iVar7 >> 0x1f);
        uVar10 = iVar7 - (iVar7 >> 0x1f);
        *(short *)(iVar6 + 0x16c) = (short)uVar10;
        if ((uVar10 & 0xffff) != 0) {
          uVar9 = uVar9 | 0x100;
        }
        *(ushort *)(iVar6 + 0x144) = uVar9;
        *(uint *)(iVar6 + 0x1c) = *(uint *)(iVar6 + 0x1c) | 0x12;
      }
    }
    piVar5 = piVar5 + 0x18;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  if (DAT_80436788 < DAT_8043678c) {
    pbVar2 = &DAT_803aa10d + DAT_80436788;
    DAT_80436788 = DAT_80436788 + 1;
    zz_0214994_((uint)*pbVar2);
    AISetStreamVolLeft((uint)*(byte *)(DAT_80436788 + -0x7fc55ef4));
  }
  else if (DAT_8043678c < DAT_80436788) {
    pbVar2 = &DAT_803aa10b + DAT_80436788;
    DAT_80436788 = DAT_80436788 + -1;
    zz_0214994_((uint)*pbVar2);
    AISetStreamVolLeft((uint)*(byte *)(DAT_80436788 + -0x7fc55ef4));
  }
  return;
}



// ==== 8021c4c8  zz_021c4c8_ ====

void zz_021c4c8_(void)

{
  DAT_80436798 = 0;
  zz_021c504_((double)FLOAT_8043caf8);
  zz_021c4fc_((double)FLOAT_8043cafc);
  return;
}



// ==== 8021c4fc  zz_021c4fc_ ====

void zz_021c4fc_(double param_1)

{
  FLOAT_804367a0 = (float)param_1;
  return;
}



// ==== 8021c504  zz_021c504_ ====

void zz_021c504_(double param_1)

{
  FLOAT_804367a4 = (float)param_1;
  return;
}



// ==== 8021c50c  zz_021c50c_ ====

void zz_021c50c_(void)

{
  DAT_803f2be8 = 0;
  DAT_803f2c7c = 0;
  DAT_803f2d10 = 0;
  DAT_803f2da4 = 0;
  DAT_803f2e38 = 0;
  DAT_803f2ecc = 0;
  DAT_803f2f60 = 0;
  DAT_803f2ff4 = 0;
  DAT_803f3088 = 0;
  DAT_803f311c = 0;
  DAT_803f31b0 = 0;
  DAT_803f3244 = 0;
  DAT_803f32d8 = 0;
  DAT_803f336c = 0;
  DAT_803f3400 = 0;
  DAT_803f3494 = 0;
  DAT_803f3528 = 0;
  DAT_803f35bc = 0;
  DAT_803f3650 = 0;
  DAT_803f36e4 = 0;
  DAT_803f3778 = 0;
  DAT_803f380c = 0;
  DAT_803f38a0 = 0;
  DAT_803f3934 = 0;
  DAT_803f39c8 = 0;
  DAT_803f3a5c = 0;
  DAT_803f3af0 = 0;
  DAT_803f3b84 = 0;
  DAT_803f3c18 = 0;
  DAT_803f3cac = 0;
  DAT_803f3d40 = 0;
  DAT_803f3dd4 = 0;
  DAT_803f3e68 = 0;
  DAT_803f3efc = 0;
  DAT_803f3f90 = 0;
  DAT_803f4024 = 0;
  DAT_803f40b8 = 0;
  DAT_803f414c = 0;
  DAT_803f41e0 = 0;
  DAT_803f4274 = 0;
  DAT_803f4308 = 0;
  DAT_803f439c = 0;
  DAT_803f4430 = 0;
  DAT_803f44c4 = 0;
  DAT_803f4558 = 0;
  DAT_803f45ec = 0;
  DAT_803f4680 = 0;
  DAT_803f4714 = 0;
  DAT_803f47a8 = 0;
  DAT_803f483c = 0;
  DAT_803f48d0 = 0;
  DAT_803f4964 = 0;
  DAT_803f49f8 = 0;
  DAT_803f4a8c = 0;
  DAT_803f4b20 = 0;
  DAT_803f4bb4 = 0;
  DAT_803f4c48 = 0;
  DAT_803f4cdc = 0;
  DAT_803f4d70 = 0;
  DAT_803f4e04 = 0;
  DAT_803f4e98 = 0;
  DAT_803f4f2c = 0;
  DAT_803f4fc0 = 0;
  DAT_803f5054 = 0;
  DAT_804367a8 = 0;
  return;
}



// ==== 8021c620  zz_021c620_ ====

void zz_021c620_(void)

{
  DAT_804367b0 = 0;
  return;
}



// ==== 8021c62c  zz_021c62c_ ====

ushort zz_021c62c_(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005000;
  return uVar1 >> 0xf;
}



// ==== 8021c63c  zz_021c63c_ ====

ushort zz_021c63c_(void)

{
  ushort uVar1;
  
  uVar1 = DAT_cc005004;
  return uVar1 >> 0xf;
}



// ==== 8021c64c  zz_021c64c_ ====

undefined4 zz_021c64c_(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  
  uVar1 = DAT_cc005004;
  uVar2 = DAT_cc005006;
  return CONCAT22(uVar1,uVar2);
}



// ==== 8021c664  zz_021c664_ ====

void zz_021c664_(undefined4 param_1)

{
  DAT_cc005000 = (short)((uint)param_1 >> 0x10);
  DAT_cc005002 = (short)param_1;
  return;
}



// ==== 8021c678  zz_021c678_ ====

void zz_021c678_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  ushort uVar1;
  undefined4 extraout_r4;
  char *pcVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  pcVar2 = s_12_34_16_803aa1b4;
  uVar3 = zz_021c87c_();
  if (DAT_804367b8 != 1) {
    gnt4_OSRegisterVersion_bl
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435d48,
               extraout_r4,pcVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
    gnt4_OSDisableInterrupts_bl();
    gnt4___OSSetInterruptHandler_bl(7,FUN_8021c8cc);
    gnt4___OSUnmaskInterrupts_bl(0x1000000);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff57 | 0x800;
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff53;
    DAT_804367c8 = 0;
    DAT_804367d4 = 0;
    DAT_804367cc = 0;
    DAT_804367d0 = 0;
    DAT_804367b8 = 1;
    gnt4_OSRestoreInterrupts_bl();
  }
  return;
}



// ==== 8021c73c  zz_021c73c_ ====

undefined4 zz_021c73c_(void)

{
  return DAT_804367b8;
}



// ==== 8021c744  zz_021c744_ ====

undefined4 * zz_021c744_(undefined4 *param_1)

{
  gnt4_OSDisableInterrupts_bl();
  zz_021d01c_((int)param_1);
  *param_1 = 0;
  param_1[2] = 1;
  gnt4_OSRestoreInterrupts_bl();
  if (param_1 == DAT_804367d0) {
    zz_021ce90_((int)param_1);
  }
  return param_1;
}



// ==== 8021c7b4  zz_021c7b4_ ====

int * zz_021c7b4_(int *param_1)

{
  ushort uVar1;
  
  gnt4_OSDisableInterrupts_bl();
  if (DAT_804367d4 == param_1) {
    DAT_804367c0 = 1;
    DAT_804367c4 = param_1;
    gnt4_OSRestoreInterrupts_bl();
  }
  else if ((uint)param_1[1] < (uint)DAT_804367d4[1]) {
    DAT_804367c0 = 1;
    DAT_804367c4 = param_1;
    if (*DAT_804367d4 == 1) {
      gnt4_OSDisableInterrupts_bl();
      uVar1 = DAT_cc00500a;
      DAT_cc00500a = uVar1 & 0xff57 | 2;
      gnt4_OSRestoreInterrupts_bl();
    }
    gnt4_OSRestoreInterrupts_bl();
  }
  else {
    gnt4_OSRestoreInterrupts_bl();
    param_1 = (int *)0x0;
  }
  return param_1;
}



// ==== 8021c87c  zz_021c87c_ ====

void zz_021c87c_(void)

{
  return;
}



// ==== 8021c8cc  FUN_8021c8cc ====

void FUN_8021c8cc(undefined4 param_1,uint param_2)

{
  ushort uVar2;
  int iVar1;
  undefined1 auStack_2d8 [724];
  
  uVar2 = DAT_cc00500a;
  DAT_cc00500a = uVar2 & 0xffd7 | 0x80;
  gnt4_OSClearContext_bl((int)auStack_2d8);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d8);
  do {
    uVar2 = zz_021c63c_();
  } while (uVar2 == 0);
  iVar1 = zz_021c64c_();
  if (((DAT_804367d4[2] & 2U) != 0) && (iVar1 == -0x232efffe)) {
    iVar1 = -0x232efffd;
  }
  if (iVar1 == -0x232efffe) {
    if (DAT_804367c0 == 0) {
      if (DAT_804367d4[0xe] == 0) {
        if (DAT_804367d4 == DAT_804367d0) {
          zz_021c664_(0xcdd10003);
          do {
            uVar2 = zz_021c62c_();
          } while (uVar2 != 0);
          if ((code *)DAT_804367d4[0xb] != (code *)0x0) {
            (*(code *)DAT_804367d4[0xb])();
          }
        }
        else {
          zz_021c664_(0xcdd10001);
          do {
            uVar2 = zz_021c62c_();
          } while (uVar2 != 0);
          zz_021ccf0_((int)DAT_804367d4,DAT_804367d0);
          *DAT_804367d4 = 2;
          DAT_804367d4 = DAT_804367d0;
        }
      }
      else {
        zz_021c664_(0xcdd10001);
        do {
          uVar2 = zz_021c62c_();
        } while (uVar2 != 0);
        zz_021ccf0_((int)DAT_804367d4,(int *)DAT_804367d4[0xe]);
        *DAT_804367d4 = 2;
        DAT_804367d4 = (int *)DAT_804367d4[0xe];
      }
    }
    else if (DAT_804367d4 == DAT_804367c4) {
      zz_021c664_(0xcdd10003);
      do {
        uVar2 = zz_021c62c_();
      } while (uVar2 != 0);
      DAT_804367c4 = (int *)0x0;
      DAT_804367c0 = 0;
      if ((code *)DAT_804367d4[0xb] != (code *)0x0) {
        (*(code *)DAT_804367d4[0xb])();
      }
    }
    else {
      zz_021c664_(0xcdd10001);
      do {
        uVar2 = zz_021c62c_();
      } while (uVar2 != 0);
      zz_021ccf0_((int)DAT_804367d4,DAT_804367c4);
      *DAT_804367d4 = 2;
      DAT_804367c0 = 0;
      DAT_804367d4 = DAT_804367c4;
      DAT_804367c4 = (int *)0x0;
    }
  }
  else if (iVar1 < -0x232efffe) {
    if (iVar1 == -0x232f0000) {
      *DAT_804367d4 = 1;
      if ((code *)DAT_804367d4[10] != (code *)0x0) {
        (*(code *)DAT_804367d4[10])();
      }
    }
    else if (-0x232f0001 < iVar1) {
      *DAT_804367d4 = 1;
      if ((code *)DAT_804367d4[0xb] != (code *)0x0) {
        (*(code *)DAT_804367d4[0xb])();
      }
    }
  }
  else if (iVar1 == -0x232efffc) {
    if ((code *)DAT_804367d4[0xd] != (code *)0x0) {
      (*(code *)DAT_804367d4[0xd])(DAT_804367d4);
    }
  }
  else if (iVar1 < -0x232efffc) {
    if (DAT_804367c0 == 0) {
      if (DAT_804367d4[0xe] == 0) {
        if (DAT_804367d4 == DAT_804367d0) {
          if ((code *)DAT_804367d4[0xc] != (code *)0x0) {
            (*(code *)DAT_804367d4[0xc])(DAT_804367d4);
          }
          zz_021c664_(0xcdd10002);
          do {
            uVar2 = zz_021c62c_();
          } while (uVar2 != 0);
          *DAT_804367d4 = 3;
          zz_021d0bc_(DAT_804367d4);
        }
        else {
          if ((code *)DAT_804367d4[0xc] != (code *)0x0) {
            (*(code *)DAT_804367d4[0xc])(DAT_804367d4);
          }
          zz_021c664_(0xcdd10001);
          do {
            uVar2 = zz_021c62c_();
          } while (uVar2 != 0);
          *DAT_804367d4 = 3;
          zz_021ccf0_(0,DAT_804367d0);
          DAT_804367d4 = DAT_804367d0;
          zz_021d0bc_(DAT_804367cc);
        }
      }
      else {
        if ((code *)DAT_804367d4[0xc] != (code *)0x0) {
          (*(code *)DAT_804367d4[0xc])(DAT_804367d4);
        }
        zz_021c664_(0xcdd10001);
        do {
          uVar2 = zz_021c62c_();
        } while (uVar2 != 0);
        *DAT_804367d4 = 3;
        zz_021ccf0_(0,(int *)DAT_804367d4[0xe]);
        DAT_804367d4 = (int *)DAT_804367d4[0xe];
        zz_021d0bc_((undefined4 *)DAT_804367d4[0xf]);
      }
    }
    else {
      if ((code *)DAT_804367d4[0xc] != (code *)0x0) {
        (*(code *)DAT_804367d4[0xc])(DAT_804367d4);
      }
      zz_021c664_(0xcdd10001);
      do {
        uVar2 = zz_021c62c_();
      } while (uVar2 != 0);
      zz_021ccf0_(0,DAT_804367c4);
      zz_021d0bc_(DAT_804367d4);
      DAT_804367c0 = 0;
      DAT_804367d4 = DAT_804367c4;
      DAT_804367c4 = (int *)0x0;
    }
  }
  gnt4_OSClearContext_bl((int)auStack_2d8);
  gnt4_OSSetCurrentContext_bl(param_2);
  return;
}



// ==== 8021ccf0  zz_021ccf0_ ====

void zz_021ccf0_(int param_1,int *param_2)

{
  ushort uVar1;
  
  if (param_1 == 0) {
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
  }
  else {
    zz_021c664_(*(undefined4 *)(param_1 + 0x18));
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(*(undefined4 *)(param_1 + 0x1c));
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(*(undefined4 *)(param_1 + 0x20));
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
  }
  zz_021c664_(param_2[3]);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(param_2[4]);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(param_2[5]);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  if (*param_2 == 0) {
    zz_021c664_((uint)*(ushort *)(param_2 + 9));
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(0);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
  }
  else {
    zz_021c664_((uint)*(ushort *)((int)param_2 + 0x26));
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(param_2[6]);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(param_2[7]);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
    zz_021c664_(param_2[8]);
    do {
      uVar1 = zz_021c62c_();
    } while (uVar1 != 0);
  }
  return;
}



// ==== 8021ce90  zz_021ce90_ ====

void zz_021ce90_(int param_1)

{
  ushort uVar1;
  
  do {
    uVar1 = zz_021c63c_();
  } while (uVar1 == 0);
  zz_021c64c_();
  zz_021c664_(0x80f3a001);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(*(undefined4 *)(param_1 + 0xc));
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(0x80f3c002);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(*(uint *)(param_1 + 0x14) & 0xffff);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(0x80f3a002);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(*(undefined4 *)(param_1 + 0x10));
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(0x80f3b002);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(0);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_(0x80f3d001);
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c664_((uint)*(ushort *)(param_1 + 0x24));
  do {
    uVar1 = zz_021c62c_();
  } while (uVar1 != 0);
  zz_021c87c_();
  zz_021c87c_();
  zz_021c87c_();
  zz_021c87c_();
  zz_021c87c_();
  zz_021c87c_();
  return;
}



